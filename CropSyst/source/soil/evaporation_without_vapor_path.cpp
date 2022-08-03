//#pragma hdrstop
#include "evaporation_without_vapor_path.h"
#include "soil/soil_base.h"
#include <math.h>
#ifndef moremathH
#  include "corn/math/moremath.h"
   using namespace std;
#endif
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include "common/physics/standard_constants.h"
#include "soil/hydrology_finite_diff.h"
//160804#ifndef OLD_EVAPORATE
#include "common/weather/hour/weather_hours.h"
//160804#endif
//______________________________________________________________________________
Soil_evaporation_without_vapor_path::Soil_evaporation_without_vapor_path
(

//160804#ifndef OLD_EVAPORATE
//160717 modifiable_ Physical::Water_depth       &evaporation_potential_remaining_, //160609
modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining_, //160717
//160804#endif

 const Soil_layers_interface                 &soil_layers_
,const Soil_hydraulic_properties_interface   *soil_hydraulic_props_
,Soil_hydrology_finite_difference            &hydrology_
/*//160804
#ifdef OLD_EVAPORATE
,const float64                               &atmospheric_water_potential_
#endif
*/
)
/*//160804
#ifdef OLD_EVAPORATE
: Soil_evaporation_abstract         ()
, soil_hydraulic_props              (soil_hydraulic_props_)
, soil_layers                       (soil_layers_)
#else
*/
: Evaporator_soil
   (evaporation_potential_remaining_
   ,soil_layers_
   ,*soil_hydraulic_props_       //160606 Warning this actually should be point Need to modify Evaporator_soil
   ,hydrology_
   //,atmospheric_water_potential_
   )
//160804#endif
, hydrology_FD                      (hydrology_)
//160804#ifdef OLD_EVAPORATE
//160804, atmospheric_water_potential       (atmospheric_water_potential_)
//160804#endif
, first_day                         (true)                                       //090417
, period_evaporation_done           (false)                                      //090417
, evaporation_depth                 (0.1)                                        //090504
, sum_evaporation_mm_ts             (0.0)                                        //090417
, max_current_period_evaporation    (0.0)                                        //090417
, absolute_max_evaporation          (0.0) // setup in initialize()               //090417
, old_WC                            (0.0)                                        //090417
, mulch_cover_fraction              (0.0)
{}
//______________________________________________________________________________
void Soil_evaporation_without_vapor_path::initialize(uint8 number_real_plus_extended_layer)        modification_
{
   // currently doing nothing, but should initialize the vapor_path_length_lower
   // Currently the VB codes does not do this.
   evaporation_depth = soil_layers.get_thickness_m(1);                           //090504
   //090504 if (evaporation_depth > 0.1) evaporation_depth = 0.1;         // Limitive evaporation depth to 10cm. //090504_
   //170217unused float64 soil_thickness_1_m = soil_layers.get_thickness_m(1);
   float64 PWP_1  =
      //160804#ifdef OLD_EVAPORATE
      //160804soil_hydraulic_props->
      //160804#else
      soil_hydraulic_properties.
      //160804#endif
      get_permanent_wilt_point_volumetric(1);
   float64 WC_1   = hydrology_FD.get_liquid_water_content_volumetric(1);
   float64 WC_sat_1 =
      //160804#ifdef OLD_EVAPORATE
      //160804soil_hydraulic_props->
      //160804#else
      soil_hydraulic_properties.
      //160804#endif
      get_saturation_water_content_volumetric(1,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);  //090504
   absolute_max_evaporation                                                            // Absolute_Max_Evaporation = (Soil.FCValue(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
      = (WC_sat_1 - PWP_1 / 3.0) * evaporation_depth  * water_density;
   max_current_period_evaporation                                                      // Max_Current_Period_Evaporation = (Soil.WaterContent(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
      = (WC_1 - PWP_1 / 3.0)  * water_density * evaporation_depth;
     /* Max_Current_Period_Evaporation range validation is done in evaporate() */      // If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
                                                                                       // If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
    /* Sum_Evaporation set in constructor */                                           // Sum_Evaporation = 0
    /* Period_Evaporation_Done set in constructor */                                   // Period_Evaporation_Done = False
}
//_2009-04-17______________________________________________________initialize__/
 float64 Soil_evaporation_without_vapor_path::evaporate                                 //     Sub CalculateSoilWaterEvaporation
 ( float64 &water_depth_in_mm_per_ts                                                    //     (Flux As Double
    /* I return the actual evaporation not pass by reference */                         //     , Actual_Evaporation As Double
    /* member reference */                                                              //     , Atmospheric_Water_Potential As Double
 , Seconds time_step                                                                    //     , Time_Step As Double
 , Hour    hour                                                                         //     , Hour As Integer
 , float64 pot_evap_mm_day  /* mm/day */ )                  modification_
   /* Soil is a member  */                                                              //     , Soil As SoilClass
   /* weather is a member */                                                            //     , Weather As WeatherClass)
 {                                                                                      //       Dim Hourly_Relative_Humidity As Double
    float64 evaporation_to_subtract_mm_ts = 0.0;                                        //       Dim Evaporation_To_Substract As Double
                                                                                        //       Dim Water_Depth_In As Double
                                                                                        //       Dim i As Integer
    float64 new_WC = hydrology_FD.get_liquid_water_content_volumetric(1);                  //090417 New_WC = Soil.WaterContent(1)
    if (first_day)                                                                      //090417 If Process.FirstDay Then
    {  /* Absolute_Max_Evaporation setup in initialize() */                             //090417    Absolute_Max_Evaporation =       (Soil.FCValue(1)      - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
       /* Max_Current_Period_Evaporation setup in initialize() */                       //090417    Max_Current_Period_Evaporation = (Soil.WaterContent(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
       /* Max_Current_Period_Evaporation setup in initialize() */                       //090417    If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
                                                                                        //090417    If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
       /* Sum_Evaporation setup in constructor */                                       //090417    Sum_Evaporation = 0
       /* Period_Evaporation_Done setup in constructor */                               //090417    Period_Evaporation_Done = False
       first_day = false;                                                               //090417    Process.FirstDay = False
    } else if ((new_WC > old_WC)                                                        //090417 ElseIf New_WC > Old_WC Then
             && (water_depth_in_mm_per_ts > 0))                                         //090504
    {  //170217unused float64 soil_thickness_1_m = soil_layers.get_thickness_m(1);                     //090417
       /* max_current_period_evaporation range validation is done below */              //090417    If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
                                                                                        //090417    If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
       float64 PWP_1 = soil_hydraulic_properties.
         get_permanent_wilt_point_volumetric(1);                                 //090504
       float64 WC_1   = hydrology_FD.get_liquid_water_content_volumetric(1);               //090504
       max_current_period_evaporation                                                   //090504 Max_Current_Period_Evaporation = (Soil.WaterContent(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
       = (WC_1 - PWP_1 / 3.0)  * water_density   * evaporation_depth;                   //090504
       sum_evaporation_mm_ts = 0;                                                       //090417    Sum_Evaporation = 0
       period_evaporation_done = false;                                                 //090417    Period_Evaporation_Done = False
    }                                                                                   //090417 Endif
    max_current_period_evaporation = CORN_must_be_between                               //090417
          (max_current_period_evaporation                                               //090417    If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
          ,0.0,absolute_max_evaporation);                                               //090417    If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
    float64 actual_evaporation_mm_ts = 0.0;
    /* actual_evaporation always defaults to 0 and is calculated as needed */           //090417 If Period_Evaporation_Done Then
                                                                                        //090417   Actual_Evaporation = 0
    if (! period_evaporation_done)                                                      //090417 Else
    {  float64 available_period_evaporation_mm_ts                                       //090417
          = max_current_period_evaporation - sum_evaporation_mm_ts;                     //090417    Available_Period_Evaporation = Max_Current_Period_Evaporation - Sum_Evaporation
       actual_evaporation_mm_ts = calc_actual(time_step, hour,pot_evap_mm_day);         //090417    Actual_Evaporation = ActualEvaporation(Atmospheric_Water_Potential, Time_Step, Hour, Soil, Weather) 'Return in mm per time step
       if (actual_evaporation_mm_ts >= available_period_evaporation_mm_ts)              //090417    If Actual_Evaporation >= Available_Period_Evaporation Then
       {  actual_evaporation_mm_ts = available_period_evaporation_mm_ts;                //090417       Actual_Evaporation = Available_Period_Evaporation
          period_evaporation_done = true;                                               //090417       Period_Evaporation_Done = True
       }                                                                                //090417    End If
    }                                                                                   //090417 End If
    actual_evaporation_mm_ts *= (1.0 - mulch_cover_fraction);                           //100610
    sum_evaporation_mm_ts += actual_evaporation_mm_ts;                                  //090417 Sum_Evaporation = Sum_Evaporation + Actual_Evaporation
    evaporation_to_subtract_mm_ts = actual_evaporation_mm_ts;                           //090417 Evaporation_To_Substract = Actual_Evaporation
    // Reconstitute Flux in kg/m2/s with evaporation flux substracted
    // In the C++ code we are providing  water_depth_in_mm
    // flux_mm = water_depth_in_mm_per_ts / time_step;                                  //       Flux = Water_Depth_In / Time_Step  'Reconstitute Flux in kg/m2/s with evaporation flux substracted
    /* condition already evaluated in for loop */                                       //       If Evaporation_To_Substract > 0 Then
       // RLN not sure if I is node or layer                                            //            i = 1
       for (int i = 1; evaporation_to_subtract_mm_ts > 0.000000001; i++)                //            Do
          subtract_water_from_layer(evaporation_to_subtract_mm_ts, i   );               //               Call SubstractEvaporation(Atmospheric_Water_Potential, Evaporation_To_Substract, i, Soil)
                                                                                        //               i = i + 1
                                                                                        //            Loop Until Evaporation_To_Substract = 0
                                                                                        //       End If
    // water content after this time step evaporation and before next time step infiltration
    old_WC = hydrology_FD.get_liquid_water_content_volumetric(1);                       //090417 Old_WC = Soil.WaterContent(1)
    return actual_evaporation_mm_ts;   /* flux is also a return */                      //  090417
 }                                                                                      //       End Sub
//______________________________________________________________________________
float64  Soil_evaporation_without_vapor_path
::calc_actual                                                                                      //Function ActualEvaporation
( /* member reference */                                                                           //(Atmospheric_Water_Potential As Double
  Seconds time_step   /* May need to be integer */
                                             //, Time_Step As Double
, Hour    hour_0based                                                                              //, Hour As Integer
, float64 pot_evap_mm_day /* mm/day */
//, Soil As SoilClass                                                                              //, Soil As SoilClass
//, Weather As WeatherClass                                                                        //, Weather As WeatherClass) As Double
)                                                                          const
{  // unused                                                                                       //Dim Minimum_Relative_Humidity As Double
                                                                                                   //Dim Surface_vapor_Conductance As Double
                                                                                                   //Dim Evap_Layer_Water_Potential As Double
                                                                                                   //Dim Actual_Evaporation As Double
                                                                                                   //Dim Pot_Evap As Double 'Pot_Evap must be in kg/m2/s
   // unused                                                                                       //Dim Daily_Potential_Evaporation As Double
                                                                                                   //Dim WS_Evap_Layer As Double, PE_Evap_Layer As Double, B_Evap_Layer As Double
   // unused                                                                                       //Dim Total_Soil_Vapor_Conductance As Double
   static const nat8 evaporating_layer = 1;                                                        // Evaporating_Layer = 1
   float64 actual_evaporation_kg_m2_s = 0.0;
/*
now a member reference
   const Soil_hydraulic_properties_interface &soil_hydraulic_props
      = *soil_base.get_hydraulic_properties_constant();
*/
   // This data pertains to current evaporating layer                                              //'This data pertains to current evaporating layer
   /*160804
      #ifdef OLD_EVAPORATE
   float64 hourly_fraction_of_demand =
      get_hourly_fraction_of_daily_demand(hour_0based);           //Hourly_Fraction_Of_Demand = HourlyFractionOfDailyDemand(Hour)
      float64 pot_evap_kg_m2_s = // Pot_Evap must be in kg/m2/s                                 //Pot_Evap = Weather.DailyPotentialEvaporation _
      pot_evap_mm_day * hourly_fraction_of_demand / time_step;                                     //   * Hourly_Fraction_Of_Demand / Time_Step
      #else
      */
      //160719 weather_hourly->get_insolation_fraction(hour_0based);                      //160606
      float64 pot_evap_kg_m2_s
         = m_to_mm(evaporation_potential.get(hour_0based)) / time_step;          //160719
      //160804#endif

//hourly_fraction_of_demand = 1.0;

//cout << "WARNING hourly fraction of demand set to 1.0 for debugging" << endl;


//   if (hourly_fraction_of_demand > 0.0)   // The V.B. code does not have this optimization
//   {  // We only have actual evaporation if there is hourly demand.


//pot_evap_kg_m2_s =  0.15/ 3600.0;   this like was for comparing against V.B version
// cout << "pot_evap_kg_m2_s set to fixed value for debugging" << endl;


      // Potential evaporation is converted from m/hour to kg/m2/s                                 //'Potential evaporation is converted from m/hour to kg/m2/s
      float64 surface_vapor_conductance     /* kg.s / m^4 */                                       //Surface_vapor_Conductance = -Pot_Evap / Atmospheric_Water_Potential 'in kg s / m4
         = -pot_evap_kg_m2_s / atmospheric_water_potential;
      float64 wu_1   = hydrology_FD.get_upper_water_content_liquid(1);
      float64 wl_1   = hydrology_FD.get_lower_water_content_liquid(1);
      float64 PWP_1  =
         //160804#ifdef OLD_EVAPORATE
         //160804soil_hydraulic_props->
         //160804#else
         soil_hydraulic_properties.
         //160804#endif
         get_permanent_wilt_point_volumetric(1);

      float64 evap_layer_WC =                                                                      //Dim Evap_Layer_WC As Double
      // 090417 changed back to only one fully 'dryable' layer                                     //'Activate this if only one fully " dryable" layer is desired
      (wu_1 > PWP_1)                                                                               //If wu(1) > Soil.pwpValue(1) Then
      ? wu_1                                                                                       //    Evap_Layer_WC = wu(1)
                                                                                                   //    Else
      : 0.5 * wu_1 + wl_1 * 0.5;                                                                   //    Evap_Layer_WC = 0.8 * wu(1) + wl(1) * 0.2 'Could be 0.5 and 0.5 as well 'Roger 040909
//090504      : 0.8 * wu_1 + wl_1 * 0.2; // Could be 0.5 and 0.5                                           //    Evap_Layer_WC = 0.8 * wu(1) + wl(1) * 0.2 'Could be 0.5 and 0.5 as well 'Roger 040909
                                                                                                   //End If
#ifdef OBSOLETE
090417 now only one dryable layer done above
      float64 wu_2   = hydrology_FD.get_upper_water_content_liquid(2);
      float64 wl_2   = hydrology_FD.get_lower_water_content_liquid(2);
      float64 evap_layer_WC =                                                                      //Dim Evap_Layer_WC As Double
         (wu_1 > PWP_1)                                                                            //If wu(1) > Soil.pwpValue(1) Then
         ?  wu_1                                                                                   //    Evap_Layer_WC = wu(1)
         :                                                                                         //    Else
            only_one_dryable_layer                                                                 // In the V.B. code this option
            ?  0.5 * (wl_1 + wu_2) :                                                               // is selected by modifying the code
               (wl_1 > PWP_1)                                                                      //    If wl(1) > Soil.pwpValue(1) Then
               ? wl_1                                                                              //        Evap_Layer_WC = wl(1)
               :                                                                                   //        Else
                  0.5 * (wu_2 + wl_2);                                                             //        Evap_Layer_WC = 0.5 * (wu(2) + wl(2))
                                                                                                   //    End If
                                                                                                   //End If
      // The one dryable layer option has been incorporated into the                               //'Activate this if only one fully " dryable" layer is desired
      // expression above and selected with only_one_dryable_layer                                 //'If wu(1) > Soil.pwpValue(1) Then
                                                                                                   //'    Evap_Layer_WC = wu(1)
                                                                                                   //'    Else
                                                                                                   //'    Evap_Layer_WC = 0.5 * (wl(1) + wu(2))
                                                                                                   //'End If
#endif
      float64 evap_layer_water_potential                                                           //Evap_Layer_Water_Potential = Soil.WaterPotential
         = hydrology_FD.calc_water_potential_with_respect_to_layer(evap_layer_WC,evaporating_layer);  //   (Evap_Layer_WC, PE_Evap_Layer, B_Evap_Layer, WS_Evap_Layer)
      actual_evaporation_kg_m2_s =  surface_vapor_conductance                                      //Actual_Evaporation = Surface_vapor_Conductance
               * (evap_layer_water_potential - atmospheric_water_potential);                       //   * (Evap_Layer_Water_Potential - Atmospheric_Water_Potential)
      actual_evaporation_kg_m2_s =
         CORN::must_be_greater_or_equal_to<float64>(actual_evaporation_kg_m2_s,0.0);                     //If Actual_Evaporation < 0 Then Actual_Evaporation = 0
// }  // else no potential evaporation so actual_evaporation_mm_ts remains 0.0;
   return actual_evaporation_kg_m2_s * time_step; /*convert kg/m2/s to mm/time step*/              //ActualEvaporation = Actual_Evaporation * Time_Step 'convert kg/m2/s to mm/time step
}                                                                                                  //End Function
//______________________________________________________________________________/
void Soil_evaporation_without_vapor_path
::subtract_water_from_layer                                                                        //Sub SubstractEvaporation
( /* member reference */                                                                           //(Atmospheric_Water_Potential As Double
  float64 &evaporation_to_subtract                                                                 //, Evaporation_To_Substract As Double
, nat8 i   /* appears to be layer but check that it's not node */                                  //, i As Integer
/* Soil is a member parameter  */                                                                  //, Soil As SoilClass)
)                                                                  modification_
{                                                                                                  //Dim Air_Dry_Water_Content As Double
   // unused                                                                                       // Dim PWP_Water_Content As Double
                                                                                                   //Dim Water_Content_Change_Due_To_Soil_Water_Evaporation As Double
                                                                                                   //Dim Water_Depth_Available_To_Evaporate As Double
   float64 layer_evaporation = 0.0;  /* mm? */                                                     //Dim Half_Layer_Thickness As Double, Layer_Evaporation As Double
                                                                                                   //Const WD = 1000
//   const Soil_hydraulic_properties_interface &soil_hydraulic_props
//      = *soil_base.get_hydraulic_properties_constant();
   #ifdef OLD_EVAPORATE
   float64 Campbell_b_i    = soil_hydraulic_props->get_Campbell_b(i,false);
   float64 air_entry_pot_i = soil_hydraulic_props->get_air_entry_potential(i,false);
   #else
   float64 Campbell_b_i    = soil_hydraulic_properties.get_Campbell_b(i,false);
   float64 air_entry_pot_i = soil_hydraulic_properties.get_air_entry_potential(i,false);
   #endif
//cout << (int)i << endl;
//cout << "AWP:" << atmospheric_water_potential << endl;
//cout << "b:" << Campbell_b_i << endl;
//cout << "AEP:" << air_entry_pot_i << endl;
   float64 air_dry_water_content =                                                                  //Air_Dry_Water_Content = Soil.SaturationWaterContent(i)
      //160804#ifdef OLD_EVAPORATE
      //160804soil_hydraulic_props->
      //160804#else
      soil_hydraulic_properties.                                                 //106060
      //160804#endif
         get_saturation_water_content_volumetric(i,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822)                           //   * (Soil.AirEntryPotential(i) / Atmospheric_Water_Potential) ^ (1 / Soil.bValue(i))
        * pow((air_entry_pot_i
               / atmospheric_water_potential)
             , (1.0 /Campbell_b_i ));
//air_dry_water_content = 0.039142169;
//cout << "WARNING setting fixed air_dry_water_content for debugging" << endl;
   float64 half_layer_thickness_m = soil_layers.get_thickness_m(i) / 2.0;                          //Half_Layer_Thickness = Soil.LayerThickness(i) / 2
/*170217unused                                                                                                   //Dim Threshold_WC As Double
   float64 threshold_WC =
      soil_hydraulic_properties.                                                 //160606
      get_field_capacity_volumetric(i);                  //Threshold_WC = Soil.FCValue(i)
*/
//threshold_WC = 0.286083858;
//cout << "WARNING setting fixed threshold_WC for debugging" << endl;
   // Substract evaporation from upper portion of the layer                                        //'Substract evaporation from upper portion of the layer
   float64 wu_i   = hydrology_FD.get_upper_water_content_liquid(i);
   if (wu_i > air_dry_water_content )                                                              //If wu(i) > Air_Dry_Water_Content Then
   {  float64 water_depth_available_to_evaporate   /*in mm?*/                                      //    Water_Depth_Available_To_Evaporate
         = (wu_i - air_dry_water_content) * half_layer_thickness_m * water_density;                //      = (wu(i) - Air_Dry_Water_Content) * Half_Layer_Thickness * WD 'in mm
      if (water_depth_available_to_evaporate > evaporation_to_subtract)                            //    If Water_Depth_Available_To_Evaporate > Evaporation_To_Substract Then
      {    layer_evaporation = evaporation_to_subtract;                                            //        Layer_Evaporation = Evaporation_To_Substract
           evaporation_to_subtract = 0.0;                                                          //        Evaporation_To_Substract = 0
      } else                                                                                       //        Else
      {    layer_evaporation = water_depth_available_to_evaporate;                                 //        Layer_Evaporation = Water_Depth_Available_To_Evaporate
           evaporation_to_subtract = evaporation_to_subtract - layer_evaporation;                  //        Evaporation_To_Substract = Evaporation_To_Substract - Layer_Evaporation
      }                                                                                            //    End If
                                                                                                   //    End If
      float64 water_content_change_due_to_soil_water_evaporation                                   //    Water_Content_Change_Due_To_Soil_Water_Evaporation _
         = layer_evaporation / (half_layer_thickness_m * water_density);                           //      = Layer_Evaporation / (Half_Layer_Thickness * WD)
       wu_i -= water_content_change_due_to_soil_water_evaporation;                                 //    wu(i) = wu(i) - Water_Content_Change_Due_To_Soil_Water_Evaporation
       hydrology_FD.set_upper_water_content_liquid(i,wu_i);
   }                                                                                               //End If
   // Substract evaporation from lower portion of the layer                                        //'Substract evaporation from lower portion of the layer
   float64 wl_i   = hydrology_FD.get_lower_water_content_liquid(i);
   if (wl_i > air_dry_water_content )                                                              //If wl(i) > Air_Dry_Water_Content Then

      // Even when  wu_i is infintesimally greater than  air_dry_water_content
      // this will cause all evaporation_to_subtract to be subtracted
      // This correction should also needed in V.B. code although
      // in these case were this condition occurs

   {  float64 water_depth_available_to_evaporate =  /* in mm */                                    //    Water_Depth_Available_To_Evaporate = (wl(i) - Air_Dry_Water_Content) _
         (wl_i - air_dry_water_content) * half_layer_thickness_m * water_density;                  //      * Half_Layer_Thickness * WD 'in mm
      if (water_depth_available_to_evaporate > evaporation_to_subtract)                            //    If Water_Depth_Available_To_Evaporate > Evaporation_To_Substract Then
      {    layer_evaporation = evaporation_to_subtract;                                            //        Layer_Evaporation = Evaporation_To_Substract
           evaporation_to_subtract = 0.0;                                                          //        Evaporation_To_Substract = 0
      } else                                                                                       //        Else
      {    layer_evaporation = water_depth_available_to_evaporate;                                 //        Layer_Evaporation = Water_Depth_Available_To_Evaporate
           evaporation_to_subtract -= layer_evaporation;                                           //        Evaporation_To_Substract = Evaporation_To_Substract - Layer_Evaporation
      }                                                                                            //    End If
                                                                                                   //    End If
       float64 water_content_change_due_to_soil_water_evaporation                                  //    Water_Content_Change_Due_To_Soil_Water_Evaporation
         = layer_evaporation / (half_layer_thickness_m * water_density);                           //      = Layer_Evaporation / (Half_Layer_Thickness * WD)
       wl_i -= water_content_change_due_to_soil_water_evaporation;                                 //    wl(i) = wl(i) - Water_Content_Change_Due_To_Soil_Water_Evaporation
       hydrology_FD.set_lower_water_content_liquid(i,wl_i);
   }                                                                                              //End If
}                                                                                                 //End Sub
//______________________________________________________________________________

