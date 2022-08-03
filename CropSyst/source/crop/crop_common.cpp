#include <options.h>
#include "crop/crop_param.h"
#include "crop/crop_common.h"
#include "soil/soil_interface.h"
#include "soil/hydrology_interface.h"
#include "crop/growth_stages.hpp"
#include "crop/transpiration.h"
#include <math.h>
#include "corn/math/compare.h"
#include "crop/transpiration.h"
#include "corn/measure/measures.h"
#include "common/weather/parameter/WC_vapor_pressure_deficit.h"
#include "crop/CO2_response.h"

// For inspection:
#include "CS_suite/observation/CS_inspector.h"
#include "csvc.h"
#define CSVP_crop_base_transp_pot_CO2_adjusted                          0x21FFFA

namespace CropSyst {

#ifdef DEBUG_INTERCEPTION
ofstream debug_interception("debug_interception.dat");
#endif
//______________________________________________________________________________
Crop_common::Crop_common
(Crop_parameters                       *parameters_
,bool                                   owns_parameters_
,const Vapor_pressure_deficit_daytime  &daytime_vapor_pressure_deficit_          //140812
,Soil_interface                        *soil_                                    //160415
,modifiable_ Crop_CO2_response         *Crop_CO2_response_given_optional         //160418
,const CORN::date32                    &today_                                   //170525
,CORN::Unidirectional_list             &performable_operations_
,float64 param_dry_soil_root_activity_coef_                                      //170518
,float64 param_saturated_soil_root_activity_coef_)                               //170518
: Crop_element                         (today_)                                  //171212
, parameters                           (parameters_)
, owns_parameters                      (owns_parameters_)
, soil                                 (soil_)                                   //160415
, daytime_vapor_pressure_deficit       (daytime_vapor_pressure_deficit_)         //140812
, CO2_response(Crop_CO2_response_given_optional)                                 //160418
, intercepted_precipitation_m_today    (0)                                       //160416
, intercepted_precipitation_m_stored   (0)
// transpiration
, ET_ref                               (0)                                       //171031
, act_transpiration_m                  (0)                                       //171031
, report_transpiration_act_m           (0)                                       //171031
, reported_ET_pot_m                    (0)                                       //171031
, reported_ET_act_m                    (0)                                       //171031
, transpiration                        (0)
, water_stress_stats(STAT_arithmetic_mean_bit)                                   //160803
//, water_stress_index_test(999.999)
{  transpiration = new Crop_transpiration_2
      (parameters->transpiration
      ,soil_                                                                     //160415
      ,parameters->salinity.osmotic_pot_50                                       //160415
      ,parameters->salinity.salt_tolerance_P                                     //160415
      ,param_dry_soil_root_activity_coef_                                        //170518
      ,param_saturated_soil_root_activity_coef_);                                //170518
   delete event_scheduler;                                                       //151127
   event_scheduler = new Event_scheduler_crop(today,performable_operations_);    //151127
   pot_transpiration_m[0] = pot_transpiration_m[1] = 0.0;                        //171031
}
//_2004-01-21___________________________________________________________________
Crop_common::~Crop_common()
{
// this is crashing   delete transpiration; transpiration = 0;                   //141103
   parameters = 0;
}
//_2004-01-21_2003-07-10________________________________________________________
bool Crop_common::start_day()                                      modification_ //150930
{  bool started = true;
   started &= CS::Simulation_element_composite::start_day();
   intercepted_precipitation_m_today = 0;                                        //160414
   return started;
}
//_2005-10-28___________________________________________________________________
float64 Crop_common::update_pot_evapotranspiration
(float64 pot_ref_evapotranspiration)
{  ET_ref = pot_ref_evapotranspiration;  // meter
   float64 adjusted_ET_coef = get_adjusted_ET_crop_coefficient();                //080811
   // This is a special test for Jordi Marsal for fruits, this method
   // should be reimplemented with this in Crop_fruit if it is decided to keep it

   //std::clog << "adjusted_ET_coef:" << adjusted_ET_coef << std::endl;

   if (!CORN::is_approximately<float64>(parameters->transpiration.a2,0.0,0.0000001))   //121115
   {  float64 vapor_pressure_deficit_daytime_avg = daytime_vapor_pressure_deficit.get_kPa();//140812
      adjusted_ET_coef += parameters->transpiration.a1 + parameters->transpiration.a2 * vapor_pressure_deficit_daytime_avg;
   }
   float64 ET_pot_m = ET_ref * adjusted_ET_coef;
   if (ET_pot_m < 0.0)  ET_pot_m = 0.0;
   float64 global_solar_rad_inter_green_canopy = global_solar_rad_intercepted_green_canopy();
   float64 pot_transpiration_m_unadj
      = (global_solar_rad_inter_green_canopy * ET_pot_m);                        //051028
   pot_transpiration_m[1] = pot_transpiration_m[0] = pot_transpiration_m_unadj;  //151031

   //180122 ET_pot_m is actually more like potential atmospheric demand for ET???


   /*std::clog<<"pot_crop_ET_mm:"<<m_to_mm(ET_pot_m)
            <<"\tpot_ref_et_local:"<<m_to_mm(pot_ref_evapotranspiration_local)
            <<"\tadj_ET_coef:"<<adjusted_ET_coef
            <<"\tLAI:"<<get_LAI(true)
            <<"\tfGreen:"<<global_solar_rad_intercepted_green_canopy()
            <<"\tpot_transpiration_m_unadj(mm):" << m_to_mm(pot_transpiration_m_unadj)
            <<std::endl;*/
   reported_ET_pot_m = ET_pot_m;                                                 //171031
   return ET_pot_m;
}
//_2001-09-10___________________________________________________________________
float64 Crop_common::process_transpiration_m
( float64 &limited_pot_transpiration)                              modification_
{  soil_sublayer_array_64(water_uptake_demand);                                  //010724
   clear_sublayer_array(water_uptake_demand);                                    //010724
   float64 water_limited_act_transpiration = 0.0;                                //011118
   Normal_crop_event_sequence growth_stage = get_growth_stage_sequence();        //130902
   if ((growth_stage > NGS_GERMINATION) && (growth_stage <= NGS_MATURITY))
   {
      {                                                                          //080205
         float64 water_uptake_max_mm =
            #if (CROPSYST_VERSION == 4)
            m_to_mm(parameters->param_max_water_uptake_m
                (get_growth_stage_sequence()));                                  //130902
            #else
            parameters->transpiration.normal_max_water_uptake_mm;
            //130406  Warning we need to make sure that
            // normal_max_water_uptake_mm is updated dynamically as needed
            // especially for fruit trees
            #endif
         act_transpiration_m =                                                   //011022
           transpiration->calc_transpiration                                     //050331
               (limited_pot_transpiration
               ,global_solar_rad_intercepted_green_canopy()                      //081105
               ,water_uptake_max_mm                                              //130406_091222
               ,intercepted_precipitation_m_stored                               //160414
               ,get_total_fract_root_length()                                    //050331
               ,water_uptake_demand
               , CO2_response
                  ? CO2_response->get_transpiration_adjustment_factor() : 1.0);  //160418
         }
         report_transpiration_act_m = water_limited_act_transpiration =
            CORN::must_be_greater_or_equal_to<float64>(act_transpiration_m,0.0); //011022
       }
       else
       {  act_transpiration_m = 0.0;                                             //000323
          report_transpiration_act_m = water_limited_act_transpiration = 0.0;    //011117
       }                                                                         //000323
      float64 water_stress = (limited_pot_transpiration > 0.0)                   //011117
      ? water_limited_act_transpiration
         /// attainable_transpiration attainable_transpiration_deleteme          //160321
         / limited_pot_transpiration                                             //011117
      : 1.0;
/* abandoned
  if ((parameters_->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)
          && (phenology.harvested))                                          //
     //NYI     and adjustment applied
      water_stress_stats
         water_stress = 1.0;                                                     //180726
*/


        water_stress_stats.append((float32)water_stress);                        //011023
/* NYI if water_stress
   canopy_warming_equiv_water_depth =  limited_pot_transpiration - water_limited_act_transpiration;
   This would be an output column in the report (we dont do anything with this)
*/
   float64 act_extracted_unused = // the result not specifically used            //051013
   (soil)                                                                        //020711
   ? soil->mod_hydrology()->extract_water(water_uptake_demand,2)                 //160412_010724
   : act_transpiration_m; // <- This is the case for crop calibrator (or when soil is not a limitation).  //060615
   report_transpiration_act_m = act_transpiration_m;                             //051014
   return report_transpiration_act_m;                                            //031201
}
//______________________________________________________________________________
float64 Crop_common::intercept_precipitation(float64 water_reaching_plant)
{  // water_reaching_plant in meters
   float64 water_leaving_plant = 0.0;
   float64 intercepted_precipitation_m_old = intercepted_precipitation_m_stored;
   float64 on_plant = water_reaching_plant + intercepted_precipitation_m_stored;
   float64 max_store = 0.001 * get_fract_canopy_cover_total();
   if (on_plant > max_store)
   {  intercepted_precipitation_m_stored = max_store;
      water_leaving_plant = on_plant - max_store;
   }
   else
   {  intercepted_precipitation_m_stored =  on_plant;
      water_leaving_plant = 0;
   }
   intercepted_precipitation_m_today
      = intercepted_precipitation_m_stored - intercepted_precipitation_m_old;
   return  water_leaving_plant;
}
//_2016-04-14_2014-03-20_______________________________________________________/
RENDER_INSPECTORS_DEFINITION(Crop_common)
{
   KNOW_EMANATOR(today,true);                                                    //171114
   emanator_known = &emanator;                                                   //160613

   inspectors.append(new CS::Inspector_scalar(pot_transpiration_m[false/*unadjusted */] ,UC_meter,  emanator,/*check ontology*/"transpiration/potential/unadjusted"   ,value_statistic,CSVP_crop_base_transp_pot              /*171222 CSVC_crop_base_transp_pot_time_step_sum*/));
   inspectors.append(new CS::Inspector_scalar(pot_transpiration_m[true /*CO2adjusted*/] ,UC_meter,  emanator,/*check ontology*/"transpiration/potential/CO2_adjusted" ,value_statistic,CSVP_crop_base_transp_pot_CO2_adjusted /*171222 CSVC_crop_base_transp_pot_CO2_adjusted_time_step_sum*/));
   inspectors.append(new CS::Inspector_scalar(report_transpiration_act_m                ,UC_meter,  emanator,/*check ontology*/"transpiration/actual"                   ,value_statistic,CSVC_crop_base_transp_act_time_step_sum));
   inspectors.append(new CS::Inspector_scalar(water_stress_stats.ref_current() ,UC_factor  ,emanator,/*check ontology*/"water/stress/factor"     ,value_statistic,CSVP_crop_base_water_stress_factor));

   inspectors.append(new CS::Inspector_scalar(water_stress_stats.index         ,UC_index   ,emanator,"water/stress/index"      ,value_statistic,CSVP_crop_base_water_stress_index)); //check ontology
   //inspectors.append(new CS::Inspector_scalar(water_stress_index_test         ,UC_index   ,emanator,/*check ontology*/"water/stress/index"      ,value_statistic,CSVP_crop_base_water_stress_index));
   return emanator_known;
}
//_2013-07-30_______________________________________________render_inspectors_/

} // namespace CropSyst

