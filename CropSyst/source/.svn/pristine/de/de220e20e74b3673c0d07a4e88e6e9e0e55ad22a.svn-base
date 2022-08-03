//---------------------------------------------------------------------------

#pragma hdrstop

#include "soil/evaporation_vapor_path.h"
#include "soil/soil_base.h"
#include "corn/math/moremath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/*_______*/ Soil_evaporation_without_vapor_path::Soil_evaporation_without_vapor_path
/*_______*/ (
/*_______*/  const Soil_layers_interface           &_soil_layers
/*_______*/ ,const Soil_hydraulic_properties_interface   *_soil_hydraulic_props
//090108       Soil_base                          &_soil
/*_______*/ ,Soil_hydrology_finite_difference   &_hydrology
/*_______*/ ,float64                            &_atmospheric_water_potential
/*_______*/ ,bool                                _only_one_dryable_layer
/*_______*/ )
/*_______*/ : Soil_evaporation_abstract         ()
/*_______*/ , soil_hydraulic_props       (_soil_hydraulic_props)
//*_______*/ , soil_base                         (_soil)
/*_______*/ , soil_layers                       (_soil_layers /**(_soil.get_layers())*/)
/*_______*/ , hydrology                         (_hydrology)
/*_______*/ , atmospheric_water_potential       (_atmospheric_water_potential)
/*_______*/ , only_one_dryable_layer            (_only_one_dryable_layer)
/*090417_*/ , first_day                         (true)
/*090417_*/ , period_evaporation_done           (false)
/*090417_*/ , sum_evaporation_mm_ts                   (0.0)
/*090417_*/ , max_current_period_evaporation    (0.0)
/*090417_*/ , absolute_max_evaporation          (0.0) // setup in initialize()
/*090417_*/ , old_WC                            (0.0)
/*_______*/ {
/*_______*/    clear_layer_array64(vapor_conductance);         // units?
//090504obs/*_______*/    clear_layer_array64(vapor_path_length_upper);   // meter?
//090504obs/*_______*/    clear_layer_array64(vapor_path_length_lower);   // meter?
/*_______*/ };
//______________________________________________________________________________
/*_______*/ void Soil_evaporation_without_vapor_path::initialize(uint8 number_real_plus_extended_layer)        not_const
/*_______*/ {
/*_______*/     // currently doing nothing, but should initialize the vapor_path_length_lower
/*_______*/    // Currently the VB codes does not do this.

/*094054_*/    evaporation_depth = soil_layers.get_thickness_m(1) + soil_layers.get_thickness_m(2);
               if (evaporation_depth > 0.1) evaporation_depth = 0.1;         // Limitive evaporation depth to 10cm.


/*_______*/    for (uint8 layer = 1; layer <= number_real_plus_extended_layer;layer++)
/*_______*/       vapor_conductance[layer] = 9999.0;
/*090417_*/    float64 soil_thickness_1_m = soil_layers.get_thickness_m(1);
/*090417_*/    float64 FC_1   = soil_hydraulic_props->get_field_capacity_volumetric(1);
/*090417_*/    float64 PWP_1  = soil_hydraulic_props->get_permanent_wilt_point_volumetric(1);
/*090417_*/    float64 WC_1   = hydrology.get_liquid_water_content_volumetric(1);
/*090504_*/    float64 WC_sat_1 =  soil_hydraulic_props->get_saturation_water_content(1);
/*090417_*/    absolute_max_evaporation                                                            // Absolute_Max_Evaporation = (Soil.FCValue(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
/*090417_*/       = (WC_sat_1 - PWP_1 / 3.0) * evaporation_depth  * water_density;
//090504 /*090417_*/       = ( FC_1- PWP_1 / 3.0) * soil_thickness_1_m * water_density;
/*090417_*/    max_current_period_evaporation                                                      // Max_Current_Period_Evaporation = (Soil.WaterContent(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
/*090417_*/       = (WC_1 - PWP_1 / 3.0)  * water_density
/*090504_*/          * evaporation_depth;
//090504               * soil_thickness_1_m;
/*090417_*/      /* Max_Current_Period_Evaporation range validation is done in evaporate() */      // If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
/*090417_*/                                                                                        // If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
/*090417_*/     /* Sum_Evaporation set in constructor */                                           // Sum_Evaporation = 0
/*090417_*/     /* Period_Evaporation_Done set in constructor */                                   // Period_Evaporation_Done = False
/*_______*/ };
//______________________________________________________________________________
/*_______*/ float64 Soil_evaporation_without_vapor_path::evaporate                                    // Sub CalculateSoilWaterEvaporation
/*_______*/ ( float64 &water_depth_in_mm_per_ts                                                    // (Flux As Double
/*_______*/    /* I return the actual evaporation not pass by reference                            // , Actual_Evaporation As Double
/*_______*/    /* member reference */                                                              // , Atmospheric_Water_Potential As Double
/*_______*/ , Seconds time_step                                                                    // , Time_Step As Double
/*_______*/ , Hour    hour                                                                         // , Hour As Integer
/*_______*/ , float64 pot_evap_mm_day  /* mm/day */ )                  not_const
/*_______*/   /* Soil is a member  */                                                              // , Soil As SoilClass
/*_______*/   /* weather is a member */                                                            // , Weather As WeatherClass)
/*_______*/ {                                                                                      // Dim Hourly_Relative_Humidity As Double
/*_______*/    float64 evaporation_to_subtract_mm_ts = 0.0;                                        // Dim Evaporation_To_Substract As Double
/*_______*/                                                                                        // Dim Water_Depth_In As Double
/*_______*/                                                                                        // Dim i As Integer
/*090417_*/    float64 new_WC = hydrology.get_liquid_water_content_volumetric(1);                  // New_WC = Soil.WaterContent(1)
/*090417_*/    if (first_day)                                                                      // If Process.FirstDay Then
/*090417_*/    {  /* Absolute_Max_Evaporation setup in initialize() */                             //    Absolute_Max_Evaporation =       (Soil.FCValue(1)      - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
/*090417_*/       /* Max_Current_Period_Evaporation setup in initialize() */                       //    Max_Current_Period_Evaporation = (Soil.WaterContent(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
/*090417_*/       /* Max_Current_Period_Evaporation setup in initialize() */                       //    If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
/*090417_*/                                                                                        //    If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
/*090417_*/       /* Sum_Evaporation setup in constructor */                                       //    Sum_Evaporation = 0
/*090417_*/       /* Period_Evaporation_Done setup in constructor */                               //    Period_Evaporation_Done = False
/*090417_*/       first_day = false;                                                               //    Process.FirstDay = False
/*090417_*/    } else if ((new_WC > old_WC)                                                        // ElseIf New_WC > Old_WC Then
/*090504_*/             && (water_depth_in_mm_per_ts > 0))
/*090417_*/    {  float64 soil_thickness_1_m = soil_layers.get_thickness_m(1);
//090504obs       float64 top_layer_water_depth_gain
//090504obs/*090417_*/          = (new_WC - old_WC) * soil_thickness_1_m * water_density;                     //    Top_Layer_water_Depth_Gain = (New_WC - Old_WC) * Soil.LayerThickness(1) * 1000
//090504obs/*090417_*/       max_current_period_evaporation -= sum_evaporation_mm_ts + top_layer_water_depth_gain;  //    Max_Current_Period_Evaporation = Max_Current_Period_Evaporation - Sum_Evaporation + Top_Layer_water_Depth_Gain
/*090417_*/       /* max_current_period_evaporation range validation is done below */              //    If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
/*090417_*/                                                                                        //    If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
/*090504_*/       float64 PWP_1  = soil_hydraulic_props->get_permanent_wilt_point_volumetric(1);
/*090504_*/       float64 WC_1   = hydrology.get_liquid_water_content_volumetric(1);
/*090504_*/       max_current_period_evaporation                                                      // Max_Current_Period_Evaporation = (Soil.WaterContent(1) - Soil.pwpValue(1) / 3) * Soil.LayerThickness(1) * 1000
/*090504_*/       = (WC_1 - PWP_1 / 3.0)  * water_density   * evaporation_depth;
/*090417_*/       sum_evaporation_mm_ts = 0;                                                       //    Sum_Evaporation = 0
/*090417_*/       period_evaporation_done = false;                                                 //    Period_Evaporation_Done = False
/*090417_*/    };                                                                                  // Endif
/*090417_*/    max_current_period_evaporation = CORN_must_be_between
/*090417_*/          (max_current_period_evaporation                                               //    If Max_Current_Period_Evaporation < 0 Then Max_Current_Period_Evaporation = 0
/*090417_*/          ,0.0,absolute_max_evaporation);                                               //    If Max_Current_Period_Evaporation > Absolute_Max_Evaporation Then Max_Current_Period_Evaporation = Absolute_Max_Evaporation
/*_______*/    float64 actual_evaporation_mm_ts = 0.0;
/*090417_*/    /* actual_evaporation always defaults to 0 and is calculated as needed */           // If Period_Evaporation_Done Then
/*090417_*/                                                                                        //   Actual_Evaporation = 0
/*090417_*/    if (! period_evaporation_done)                                                      // Else
/*090417_*/    {  float64 available_period_evaporation_mm_ts
/*090417_*/          = max_current_period_evaporation - sum_evaporation_mm_ts;                     //    Available_Period_Evaporation = Max_Current_Period_Evaporation - Sum_Evaporation
/*090417_*/       actual_evaporation_mm_ts = calc_actual(time_step, hour,pot_evap_mm_day);         //    Actual_Evaporation = ActualEvaporation(Atmospheric_Water_Potential, Time_Step, Hour, Soil, Weather) 'Return in mm per time step
/*090417_*/       if (actual_evaporation_mm_ts >= available_period_evaporation_mm_ts)              //    If Actual_Evaporation >= Available_Period_Evaporation Then
/*090417_*/       {  actual_evaporation_mm_ts = available_period_evaporation_mm_ts;                //       Actual_Evaporation = Available_Period_Evaporation
/*090417_*/          period_evaporation_done = true;                                               //       Period_Evaporation_Done = True
/*090417_*/       };                                                                               //    End If
/*090417_*/    };                                                                                  // End If
/*090417_*/    sum_evaporation_mm_ts += actual_evaporation_mm_ts;                                  // Sum_Evaporation = Sum_Evaporation + Actual_Evaporation
/*090417_*/    evaporation_to_subtract_mm_ts = actual_evaporation_mm_ts;                           // Evaporation_To_Substract = Actual_Evaporation
/*_______*/    // Reconstitute Flux in kg/m2/s with evaporation flux substracted
               // In the C++ code we are providing  water_depth_in_mm
///*_______*/    flux_mm = water_depth_in_mm_per_ts / time_step;                                   // Flux = Water_Depth_In / Time_Step  'Reconstitute Flux in kg/m2/s with evaporation flux substracted
//090504obs/*_______*/    if (is_approximately(water_depth_in_mm_per_ts,0.0,0.00000001))                      // If Flux = 0 Then
//090504obs/*_______*/    {  for (int i = 1; i <= 2/*3*/; i++)                                                //     For i = 1 To 3
//090504obs/*_______*/       {  /* Change 3 to 2 if only one fully " dryable" layers are desired     */       //          'Change 3 to 2 if only one fully " dryable" layers are desired
//090504obs/*_______*/          /* This is added to hydraulic conductance calculation                */       //          'This is added to hydraulic conductance calculation to control evaporation from deep layers. See Function elementflux
//090504obs/*_______*/          /* to control evaporation from deep layers. See Function elementflux */
//090504obs/*_______*/          vapor_conductance[i] = calc_vapor_conductance(i);                             //             Soil_Vapor_Conductance(i) = SoilVaporConductance(i)
//090504obs/*_______*/       } /*for i */                                                                     //     Next i
//090504obs/*_______*/    } else                                                                              // End If
//090504obs/*_______*/    {  // In the V.B. code vapor conductance is set to 9999 at the beginning of every time step.
//090504obs/*_______*/       for (uint8 layer = 1; layer <= 2/*3*/;layer++)
//090504obs/*_______*/          vapor_conductance[layer] = 9999.0;
//090504obs/*_______*/    };
/*_______*/    /* condition already evaluated in for loop */                                       // If Evaporation_To_Substract > 0 Then
/*_______*/       // RLN not sure if I is node or layer                                            //      i = 1
/*_______*/       for (int i = 1; evaporation_to_subtract_mm_ts > 0.000000001; i++)                //      Do
/*_______*/          subtract_water_from_layer(evaporation_to_subtract_mm_ts, i   );               //         Call SubstractEvaporation(Atmospheric_Water_Potential, Evaporation_To_Substract, i, Soil)
/*_______*/                                                                                        //         i = i + 1
/*_______*/                                                                                        //      Loop Until Evaporation_To_Substract = 0
/*_______*/                                                                                        // End If
/*090417_*/    // water content after this time step evaporation and before next time step infiltration
/*090417_*/    old_WC = hydrology.get_liquid_water_content_volumetric(1);                          // Old_WC = Soil.WaterContent(1)
/*_______*/    return actual_evaporation_mm_ts;   /* flux is also a return */
/*_______*/ };                                                                                     // End Sub
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
   static const uint8 evaporating_layer = 1;                                                       // Evaporating_Layer = 1
   float64 actual_evaporation_kg_m2_s = 0.0;
/*
now a member reference
   const Soil_hydraulic_properties_interface &soil_hydraulic_props
      = *soil_base.get_hydraulic_properties_constant();
*/
   // This data pertains to current evaporating layer                                              //'This data pertains to current evaporating layer
   float64 hourly_fraction_of_demand = get_hourly_fraction_of_daily_demand(hour_0based);           //Hourly_Fraction_Of_Demand = HourlyFractionOfDailyDemand(Hour)

//hourly_fraction_of_demand = 1.0;

//cout << "WARNING hourly fraction of demand set to 1.0 for debugging" << endl;


//   if (hourly_fraction_of_demand > 0.0)   // The V.B. code does not have this optimization
//   {  // We only have actual evaporation if there is hourly demand.
      float64 pot_evap_kg_m2_s = /* 'Pot_Evap must be in kg/m2/s  */                               //Pot_Evap = Weather.DailyPotentialEvaporation _
      pot_evap_mm_day * hourly_fraction_of_demand / time_step;                                     //   * Hourly_Fraction_Of_Demand / Time_Step



pot_evap_kg_m2_s =  1.0/ 3600.0;

cout << "pot_evap_kg_m2_s set to fixed value for debugging" << endl;



      // Potential evaporation is converted from m/hour to kg/m2/s                                 //'Potential evaporation is converted from m/hour to kg/m2/s
      float64 surface_vapor_conductance     /* kg.s / m^4 */                                       //Surface_vapor_Conductance = -Pot_Evap / Atmospheric_Water_Potential 'in kg s / m4
         = -pot_evap_kg_m2_s / atmospheric_water_potential;
      float64 wu_1   = hydrology.get_upper_water_content_liquid(1);
      float64 wu_2   = hydrology.get_upper_water_content_liquid(2);
      float64 wl_1   = hydrology.get_lower_water_content_liquid(1);
      float64 wl_2   = hydrology.get_lower_water_content_liquid(2);
      float64 PWP_1  = soil_hydraulic_props->get_permanent_wilt_point_volumetric(1);

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
         = hydrology.calc_water_potential_with_respect_to_layer(evap_layer_WC,evaporating_layer);  //   (Evap_Layer_WC, PE_Evap_Layer, B_Evap_Layer, WS_Evap_Layer)
      actual_evaporation_kg_m2_s =  surface_vapor_conductance                                      //Actual_Evaporation = Surface_vapor_Conductance
               * (evap_layer_water_potential - atmospheric_water_potential);                       //   * (Evap_Layer_Water_Potential - Atmospheric_Water_Potential)
      actual_evaporation_kg_m2_s =
         CORN_must_be_greater_or_equal_to_f64(actual_evaporation_kg_m2_s,0.0);                     //If Actual_Evaporation < 0 Then Actual_Evaporation = 0
// }; // else no potential evaporation so actual_evaporation_mm_ts remains 0.0;
   return actual_evaporation_kg_m2_s * time_step; /*convert kg/m2/s to mm/time step*/              //ActualEvaporation = Actual_Evaporation * Time_Step 'convert kg/m2/s to mm/time step
};                                                                                                 //End Function
//______________________________________________________________________________/
void Soil_evaporation_without_vapor_path
::subtract_water_from_layer                                                                        //Sub SubstractEvaporation
( /* member reference */                                                                           //(Atmospheric_Water_Potential As Double
  float64 &evaporation_to_subtract                                                                 //, Evaporation_To_Substract As Double
, uint8 i   /* appears to be layer but check that it's not node */                                 //, i As Integer
/* Soil is a member parameter  */                                                                  //, Soil As SoilClass)
)                                                                      not_const
{                                                                                                  //Dim Air_Dry_Water_Content As Double
   // unused                                                                                       // Dim PWP_Water_Content As Double
                                                                                                   //Dim Water_Content_Change_Due_To_Soil_Water_Evaporation As Double
                                                                                                   //Dim Water_Depth_Available_To_Evaporate As Double
   float64 layer_evaporation = 0.0;  /* mm? */                                                     //Dim Half_Layer_Thickness As Double, Layer_Evaporation As Double
                                                                                                   //Const WD = 1000
//   const Soil_hydraulic_properties_interface &soil_hydraulic_props
//      = *soil_base.get_hydraulic_properties_constant();
   float64 Campbell_b_i    = soil_hydraulic_props->get_Campbell_b(i,false);
   float64 air_entry_pot_i = soil_hydraulic_props->get_air_entry_potential(i,false);
//cout << (int)i << endl;
//cout << "AWP:" << atmospheric_water_potential << endl;
//cout << "b:" << Campbell_b_i << endl;
//cout << "AEP:" << air_entry_pot_i << endl;

   float64 air_dry_water_content                                                                   //Air_Dry_Water_Content = Soil.SaturationWaterContent(i)
      = soil_hydraulic_props->get_saturation_water_content_volumetric(i,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822) //   * (Soil.AirEntryPotential(i) / Atmospheric_Water_Potential) ^ (1 / Soil.bValue(i))
        * pow((air_entry_pot_i
               / atmospheric_water_potential)
             , (1.0 /Campbell_b_i ));

//air_dry_water_content = 0.039142169;
//cout << "WARNING setting fixed air_dry_water_content for debugging" << endl;

   float64 half_layer_thickness_m = soil_layers.get_thickness_m(i) / 2.0;                          //Half_Layer_Thickness = Soil.LayerThickness(i) / 2
                                                                                                   //Dim Threshold_WC As Double
   float64 threshold_WC = soil_hydraulic_props->get_field_capacity_volumetric(i);                  //Threshold_WC = Soil.FCValue(i)

//threshold_WC = 0.286083858;
//cout << "WARNING setting fixed threshold_WC for debugging" << endl;

   // Substract evaporation from upper portion of the layer                                        //'Substract evaporation from upper portion of the layer
   float64 wu_i   = hydrology.get_upper_water_content_liquid(i);
   if (wu_i > air_dry_water_content )                                                              //If wu(i) > Air_Dry_Water_Content Then


   {  float64 water_depth_available_to_evaporate   /*in mm?*/                                      //    Water_Depth_Available_To_Evaporate
         = (wu_i - air_dry_water_content) * half_layer_thickness_m * water_density;                //      = (wu(i) - Air_Dry_Water_Content) * Half_Layer_Thickness * WD 'in mm
      if (water_depth_available_to_evaporate > evaporation_to_subtract)                            //    If Water_Depth_Available_To_Evaporate > Evaporation_To_Substract Then
      {    layer_evaporation = evaporation_to_subtract;                                            //        Layer_Evaporation = Evaporation_To_Substract
           evaporation_to_subtract = 0.0;                                                          //        Evaporation_To_Substract = 0
      } else                                                                                       //        Else
      {    layer_evaporation = water_depth_available_to_evaporate;                                 //        Layer_Evaporation = Water_Depth_Available_To_Evaporate
           evaporation_to_subtract = evaporation_to_subtract - layer_evaporation;                  //        Evaporation_To_Substract = Evaporation_To_Substract - Layer_Evaporation
      };                                                                                           //    End If
//090504obs      vapor_path_length_upper[i] =  (wu_i < threshold_WC)                                          //    If wu(i) < Threshold_WC Then
//090504obs                                                                                                   //        Vapor_Path_Length_Upper(i)                         _
//090504obs            ? half_layer_thickness_m                                                               //         = Half_Layer_Thickness  _
//090504obs               * (1.0 - pow(((wu_i - air_dry_water_content)                                        //            * (1 - ((wu(i) - Air_Dry_Water_Content)                _
//090504obs                      / (threshold_WC - air_dry_water_content)) , 0.5))                            //                   / (Threshold_WC - Air_Dry_Water_Content)) ^ 0.5)
//090504obs//090504obs            :                                                                                      //        Else
//090504obs              0.0;                                                                                 //        Vapor_Path_Length_Upper(i) = 0
                                                                                                   //    End If
//090504obs       vapor_path_length_upper[i] = CORN_must_be_between_f64                                       //    If Vapor_Path_Length_Upper(i) > Half_Layer_Thickness Then _
//090504obs            (vapor_path_length_upper[i],0.00001, half_layer_thickness_m                            //      Vapor_Path_Length_Upper(i) = Half_Layer_Thickness
//090504obs            );                                                                                     //    If Vapor_Path_Length_Upper(i) <= 0 Then Vapor_Path_Length_Upper(i) = 0.00001
      float64 water_content_change_due_to_soil_water_evaporation                                   //    Water_Content_Change_Due_To_Soil_Water_Evaporation _
         = layer_evaporation / (half_layer_thickness_m * water_density);                           //      = Layer_Evaporation / (Half_Layer_Thickness * WD)
       wu_i -= water_content_change_due_to_soil_water_evaporation;                                 //    wu(i) = wu(i) - Water_Content_Change_Due_To_Soil_Water_Evaporation
       hydrology.set_upper_water_content_liquid(i,wu_i);
   }                                                                                              //End If
//090504obs   else
//090504obs       vapor_path_length_upper[i] = half_layer_thickness_m;
   // Substract evaporation from lower portion of the layer                                        //'Substract evaporation from lower portion of the layer
   float64 wl_i   = hydrology.get_lower_water_content_liquid(i);
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
      };                                                                                           //    End If
//090504obs      vapor_path_length_lower[i] = (wl_i < threshold_WC )                                          //    If wl(i) < Threshold_WC Then
//090504obs         ?     half_layer_thickness_m *                                                            //        Vapor_Path_Length_Lower(i) = Half_Layer_Thickness * _
//090504obs               (1.0 - pow(((wl_i - air_dry_water_content)                                          //            (1 - ((wl(i) - Air_Dry_Water_Content)           _
//090504obs                         / (threshold_WC - air_dry_water_content)) , 0.5))                         //                  / (Threshold_WC - Air_Dry_Water_Content)) ^ 0.5)
//090504obs        :                                                                                          //        Else
//090504obs          0.0;                                                                                     //        Vapor_Path_Length_Lower(i) = 0
                                                                                                   //    End If
//090504obs       vapor_path_length_lower[i] = CORN_must_be_less_or_equal_to_f64                              //    If Vapor_Path_Length_Lower(i) > Half_Layer_Thickness Then _
//090504obs          (vapor_path_length_lower[i] , half_layer_thickness_m);                                   //       Vapor_Path_Length_Lower(i) = Half_Layer_Thickness
       float64 water_content_change_due_to_soil_water_evaporation                                  //    Water_Content_Change_Due_To_Soil_Water_Evaporation
         = layer_evaporation / (half_layer_thickness_m * water_density);                           //      = Layer_Evaporation / (Half_Layer_Thickness * WD)
       wl_i -= water_content_change_due_to_soil_water_evaporation;                                 //    wl(i) = wl(i) - Water_Content_Change_Due_To_Soil_Water_Evaporation
       hydrology.set_lower_water_content_liquid(i,wl_i);
   }                                                                                              //End If
//090504obs   else
//090504obs       vapor_path_length_lower[i] = half_layer_thickness_m;
};                                                                                                 //End Sub
//______________________________________________________________________________
#ifdef OBSOLETE
090504
float64  Soil_evaporation_without_vapor_path
::calc_vapor_conductance(uint8 i)                                        const                     //Function SoilVaporConductance(i As Integer) As Double
{        // RLN not sure if i is node or path
   float64 vapor_path_length = vapor_path_length_upper[i];                                         //Dim Vapor_Path_Length As Double, SVC As Double
   vapor_path_length +=
       (i == 1)                                                                                    //If i = 1 Then
      ?  0                                                                                         //    Vapor_Path_Length = Vapor_Path_Length_Upper(i)
      :                                                                                            //    Else
         vapor_path_length_lower[i - 1];                                                           //    Vapor_Path_Length = Vapor_Path_Length_Upper(i) + Vapor_Path_Length_Lower(i - 1)
                                                                                                   //End If
   float64 SVC =
      (vapor_path_length > 0.0)                                                                    //If Vapor_Path_Length > 0 Then
      ? 0.0000000000007 / vapor_path_length                                                        //    SVC = 0.0000000000007 / Vapor_Path_Length '0.7 e-12 XXXOJO it might need to change with texture
      :                                                                                            //    Else
        9999.0;                                                                                    //    SVC = 9999#
                                                                                                   //End If
   return SVC;                                                                                     //SoilVaporConductance = SVC
};                                                                                                 //End Function
//______________________________________________________________________________
#endif
