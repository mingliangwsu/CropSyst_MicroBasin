#ifndef soilprocessesclassH
#define soilprocessesclassH

#ifndef MBVB_FD
// Added by RLN
#undef LIU_FD_RICHARD
#endif
//#include "datetime/date.hpp"
#ifdef CROPSYST_WEATHER
#include "weather/parameter/WP_precipitation.h"
#include <vector>
#else
#include "weather/weatherstatedailyclass.h"
#endif
#ifdef MBVB_SNOW
#   include "snow/clssnow.h"
#endif
#include "control/allcontrolclass.h"

class Soil_chemicals_profile;

#ifdef CHEMICAL_TRANSPORT
#include "soil/soilchemicaltransportclass.h"
#endif

#ifndef MSVB_CASCADE_INFILTRATION_HOUR
#include "soil/infiltration_cascade_hourly.h"
#else
#define MBVB_INFILTRATION
#endif

#ifndef MBVB_INFILTRATION
#include "soil/infiltration_cascade_hourly.h"
#include "pond.h"
#include "soil/runoff.h"
#endif
#include "soil/runoff.h"
#ifndef MBVB_FD
#include "soil/infiltration_finite_diff.h"
#define CROPSYST_INFILTRATION
#endif
class SoilStateClass;
class SoilProfileClass;

#ifdef CROPSYST_PROPER_CROP
namespace CropSyst
{
   interface_ Crop_interfaced;                                                   //140502
}
#else
class clsCrop;
#endif
class clsSimulation;
#ifndef CROPSYST_VERSION
class clsSnow;
#endif
class clsManagement;
class SoilChemicalTransportClass;
#ifdef CROPSYST_VERSION
class ET_Reference_FAO;
class Relative_humidity;                                                         //151222
class HourlySoilProcesses;                                                       //160606
namespace CS
{
   //class Solar_irradiance_extraterrestrial_hourly;                             //160810
   class Solar_irradiance_extraterrestrial;
}
#endif
// ______________________________________________________________________________
class SoilProcessesClass
{
 protected: friend class OutputMainClass; friend class HourlySoilProcesses;
   Soil_infiltration_cascade_hourly    *infiltration_cascade_hourly;
      // We always have infiltration_cascade_hourly because
      // infiltration_finite_difference may need to drop down if it can't converge
   Soil_infiltration_finite_difference *infiltration_finite_difference;
 protected:  Soil_infiltration                   *infiltration;                  //140527
   //160720RLN modifiable_ Physical::Water_depth &evaporation_potential_remaining;           //160414RLN
//160722 moved to evaporator   modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining;    //160720RLN
 public:
   Evaporator_soil *evaporator;                                                  //160608
 private:
   ET_Reference_FAO                 *ET_ref;                                     //150804
   const CS::Solar_irradiance_extraterrestrial/*160808RLN _hourly*/ &solar_irradiance_extraterrestrial_basin; //160808_151214RLN
   const Relative_humidity          &relative_humidity_min_ref;                  //151222
   void DetermineHourlyWaterRedistribution(int hour, double WaterIn_m_hr);       //140201
      // COS-FMS New vertical infiltration routine 01/02/2014
   void SaveResultsVerticalFlow(int hour, double hourly_drainage,                //140310FMS
      double hourly_ponded, double hourly_runoff, double hourly_water_in,
      double gross_water_in);
#ifdef MBVB_INFILTRATION
   void DistributeExcessFlowUpwards(int tolayer, double&Excess_Flow_In,
      double&Sum_Ponded);

   void initMem();
   void clearMem();
#endif

   int Num_Soil_Layers;

#ifdef MBVB_INFILTRATION
   // 140303 obsolete
   // global variables for FD routine
   std::vector<double> b;
   std::vector<double> Jl;
   std::vector<double> KS;
   std::vector<double> N;
   std::vector<double> p;
   std::vector<double> pe;
   std::vector<double> Soil_Vapor_Conductance;
   std::vector<double> wl;
#ifndef FD_PROPER
   std::vector<double> wnl;
   std::vector<double> wnu;
#endif
   std::vector<double> WS;
   std::vector<double> wu;
   std::vector<double> z;
   std::vector<double> WC_ICE; // FMS Mar 14, 2014
#endif
#ifdef MBVB_INFILTRATION
   // for redistribution
   std::vector<double> WC_Temp;
   std::vector<double> Air_Entry_Potential;
   std::vector<double> b_Value;
   std::vector<double> m;
   std::vector<double> K_Sat;
   std::vector<double> Apparent_K_Sat;
   std::vector<double> WC_Sat;
   std::vector<double> FC;
   std::vector<double> WPFC;
   std::vector<double> Water_Content;
   std::vector<double> WC_Max;
   std::vector<double> Layer_Thickness;
   std::vector<double> Soil_Depth;
#endif
#ifdef MBVB_INFILTRATION
   std::vector<double> Ponded_Initial; // 24                                     //140121FMS
   std::vector<double> Ponded_Final; // 24
   double All_Hourly_Water_In;                                                   //140221FMS debug
   double Balance_Profile_FD;                                                    //140226FMS
#endif
#ifdef MBVB_INFILTRATION
   bool First_Hour_Of_Watering;
   double Top_Water_Potential_m; // in m                                         //130731
   double Average_Water_Potential_Wetting_Front_m; // in m                       //130731
   double Wetting_Front_Depth; // in m                                           //130731
#endif

public:

   CropSyst::Pond &pond;

   double Canopy_Intercepted_Precipitation;
   double cum_Infiltrated_Water;
   double Cumulative_Gross_Water_In; // (m)
#ifdef MBVB_INFILTRATION
   double Finite_Difference_Error_mm;
#endif

   double Hourly_Non_Intercepted_Rain_m;    //(m/h) not intercepted by the canopy & snow.
                                            //Assume all rain is intercepted by snow if there is snowpack.
   double Hourly_Ponded_m;                  // (m/h)
   double Hourly_Irrigation_m;              // (m/h)
   double Hourly_Snow_Melt_m;               // (m/h)
   double Hourly_Drainage_m;                // (m/h)
   double Hourly_Water_In_m;                // (m/h)
   double Hourly_Runoff_m;                  // (m/h)

   double Hourly_Prec_Irrig_SnowMelt_m;
   double Hourly_Non_Intercepted_Precipitation[25];
   double Hourly_Infiltration_Capacity_Limited_Runoff; // (mm/T)
   double Hourly_Excess_Infiltration_Runoff; // (mm/T) Infiltrated water greater than available porosity
   double Gross_Water_In_m;

   double Daily_Soil_Water_Actual_Evaporation; // (mm/day)
   double Daily_Soil_Water_Potential_Evaporation_m;
   
   //Tillage process
  
   double Layer_Soil_Mass[6];                         //(kg/m2)                  //140820FMS Changed to global variable
   double Layer_Soil_Mass_Remaining_After_Tillage[6]; //(kg/m2)                  //140820FMS Changed to global variable
   double Layer_Soil_Mass_Mixed_After_Tillage[6];     //(kg/m2)                  //140820FMS Changed to global variable
   
#ifdef MBVB_INFILTRATION
   double Hourly_Infiltration_m; // (m)
   bool Sat_BC; // true: saterated boundary (top node) false: real infiltration
#endif
   double Water_In; // (mm)
   SoilProfileClass& SoilProfileRef;
   SoilStateClass& SoilStateRef;
#ifdef CROPSYST_WEATHER
   const Precipitation &precipitation;
#else
   #ifdef MBVB_SNOW
   clsSnow &SnowRef;
   #endif
#endif

   AllControlClass &control;
   const CORN::Date_const/*170615LML _const_interface*/ &today;                      //150630
   #ifdef CROPSYST_VERSION
   Soil_chemicals_profile     *chemicals_optional; // 0 if not running chemicals
   #endif
   #ifndef CROPSYST_CHEMICAL_TRANSPORT
   SoilChemicalTransportClass *pChemTransport_optional;
   #endif
   SoilProcessesClass
      ( SoilStateClass &_SoilStateRef
      ,AllControlClass &_control
      ,const CORN::Date_const/*170615LML _const_interface*/ &today                   //150630RLN
      ,SoilProfileClass &_soilpf
      //160720RLN,modifiable_ Physical::Water_depth &evaporation_potential_remaining       //160414RLN
      ,modifiable_ CORN::Dynamic_array<float64> &evaporation_potential_remaining //160720RLN
        #ifdef MBVB_SNOW
      , clsSnow &_SnowRef
        #endif
      ,CropSyst::Pond &_pond
      ,CropSyst::Soil_runoff *_runoff
      #if (defined(CHEMICAL_TRANSPORT) && defined(CROPSYST_VERSION))
      ,Soil_chemicals_profile     *chemicals // 0 if not running chemicals
      #endif
      #ifdef CROPSYST_VERSION
      //,ET_Reference_FAO *ET_ref
      ,const CS::Solar_irradiance_extraterrestrial/*160808RLN _hourly*/  &solar_irradiance_extraterrestrial_basin //160808RLN
      ,const Relative_humidity &relative_humidity_min_ref                        //151222
      #endif
      );
   ~SoilProcessesClass();
   virtual bool initialize()                                     initialization_;//140502RLN

   void UpdateSoilAndCropOutputsOnSoilEvap(
                                            int hour_of_day
                                            #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
                                            #else
                                            ,bool crop_emerged
                                            ,clsCrop & Crop
                                            #endif
                                            ,double soil_evap_mm);

   //160414RLN UpdateSoilAndCropOutputsOnSoilPotEvap is probably obsolete
   void UpdateSoilAndCropOutputsOnSoilPotEvap(
                                            int hour_of_day
                                            #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
                                            #else
                                            ,bool crop_emerged
                                            ,clsCrop & Crop
                                            #endif
                                            ,double Pot_soil_evap_mm);

   inline double getCropSystFDReportedDrainage_m()  {return infiltration_finite_difference ? infiltration_finite_difference->get_reported_drainage() : 0;} //160606RLN
   inline double getCropSystFDBalancedDrainage_m()  {return infiltration_finite_difference ? infiltration_finite_difference->get_balance_drainage()  : 0;} //160606RLN

   // void assignApparentKsat();
   double calDeltaVWC(const double tvwc, const int layer, const double timestep_s); // (m3/m3)
   #ifdef MBVB_INFILTRATION
   void initHourlyFluxes();
   #endif
   #ifndef CROPSYST_WEATHER
   void DetermineEffectivePrecipitation(WeatherStateDailyClass & Weather
      #ifndef CROPSYST_VERSION
      , clsSimulation & Simulation
      #ifdef CROPSYST_PROPER_CROP
      , const CropSyst::Crop_interfaced & crop                                   //140502
      #else
      , clsCrop & Crop
      #endif
      #else
      ,const double fraction_cover_total_canopy                                  //150909LML
      #endif
      );
   #endif
   double CalculateMaximumWaterContentDuringInfiltration(double Win,
      double KSat, double AirEntryPotential, double bValue, double WCSat,
      int Time_Step);
   bool performFD_InfiltrationAndTransport(bool Run_Chemical_Transport
      ,float64 eff_rain_m_ts
      ,float64 irrig_m_ts
      ,float64 runon_m_ts   
      ,float64 &actually_infiltrated_time_step_m
      ,float64 &actually_evaporated_time_step_m_ts
      ,float64 &actually_balance_drainage_m_ts
      ,float64 &surface_runoff_m_ts
      ,float64 &error_FD_m_ts);
   void PerformHourlyCascadeInfiltrationAndTransport(
      float64 eff_rain_m_ts
      ,float64 irrig_m_ts
      ,float64 runon_m_ts
      ,float64 &actually_infiltrated_time_step_m
      ,float64 &actually_balance_drainage_m_ts
      ,float64 &surface_runoff_m_ts
      ,float64 &balance_leached_NH4_N_kg_ts                                      //170417LML
      ,float64 &balance_leached_NO3_N_kg_ts                                      //170417LML
      #ifndef CROPSYST_VERSION
      ,clsSimulation & Simulation
      ,clsManagement & Management
      #endif
      );
#ifdef CHEMICAL_TRANSPORT
   double getFlow(int layer);
#endif
   void setNumSoilLayers(int soil_num);
   inline bool is_using_infiltration_finite_difference()                         //160606RLN
      { return infiltration_finite_difference != 0; }
};
// ______________________________________________________________________________
#endif // SOILPROCESSESCLASS_H
