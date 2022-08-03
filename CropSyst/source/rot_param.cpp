#include "rot_param.h"
#ifndef PLANTING_SCHEDULER
#include "crop/crop_param.h"
#include "mgmt_param.h"
#endif
#include "common/weather/weather_interface.h"
#include "common/weather/parameter/WC_air_temperature.h"
#include "static_phrases.h"
#include "corn/measure/units.ph"
#include "corn/measure/measures.h"
#include "cs_mgmt.h"
#include "corn/chronometry/date_const.hpp"
#include "corn/math/statistical/stats.h"
#include "UED/library/std_codes.h"
#ifdef LADSS_MODE
   extern bool LADSS_mode;
#endif
namespace CropSyst {
//______________________________________________________________________________
const char *planting_date_mode_label_table[] =
{"fixed_date"     // 0
,"min_temp_req"   // 1
,"days_to_emerge" // 2
,0};
//______________________________________________________________________________
const char *sowing_status_label_table[] =
{"failed"
,"succeeded"
,"delayed"
,"conflict"
,0};
//______________________________________________________________________________
#define NoAltFieldName 0
#define NotYetSubsection "NotYetSubsection"

Parameter_properties_literal PP_sowing_avg_temp         ={LABEL_avg_temp               ,NoAltFieldName,NotYetSubsection,TL_Five_day_mean_temp                  ,""                     ,"",UC_Celcius             ,TU_degrees_C};
Parameter_properties_literal PP_sowing_min_PAW          ={LABEL_min_PAW                ,NoAltFieldName,NotYetSubsection,TL_layer_2_is_greater_than             ,TL_Sow_only_when_PAW   ,"",U_units_not_specified  ,TU_0_1};
Parameter_properties_literal PP_sowing_max_PAW          ={LABEL_max_PAW                ,NoAltFieldName,NotYetSubsection,TL_layer_1_is_less_than                ,TL_Sow_only_when_PAW   ,"",U_units_not_specified  ,TU_0_1};
Parameter_properties_literal PP_expected_days_to_emerge ={LABEL_expected_days_to_emerge,NoAltFieldName,NotYetSubsection,"Typical days for emergence"           ,""                     ,"",UT_day                 ,"Days"/*T_date_Days*/};
Parameter_properties_literal PP_delay_after_precip      ={LABEL_delay_after_precip     ,NoAltFieldName,NotYetSubsection,TL_Number_of_days_to_delay             ,""                     ,"",UT_day                 ,"Days"/*T_date_Days*/};
Parameter_properties_literal PP_appreciable_precip_mm   ={LABEL_appreciable_precip     ,NoAltFieldName,NotYetSubsection,TL_Significant_precipitation_amount    ,""                     ,"",UC_mm                  ,TU_mm};

Parameter_range PPR_sowing_avg_temp         ={0.0 ,30.0,-10.0,40.0};
Parameter_range PPR_sowing_min_PAW          ={0.0 , 1.0,  0.0, 1.0};
Parameter_range PPR_sowing_max_PAW          ={0.0 , 1.0,  0.0, 1.0};
Parameter_range PPR_expected_days_to_emerge ={  0 , 40 ,    0,9999};
Parameter_range PPR_delay_after_precip      ={  0 , 30 ,    0,100 };
Parameter_range PPR_appreciable_precip_mm   ={0.0 ,20.0,  0.0,100.0};

Parameter_format PPF_sowing_avg_temp         ={6,2};
Parameter_format PPF_sowing_min_PAW          ={6,2};
Parameter_format PPF_sowing_max_PAW          ={6,2};
Parameter_format PPF_expected_days_to_emerge ={3,0};
Parameter_format PPF_delay_after_precip      ={3,0};
Parameter_format PPF_appreciable_precip      ={6,1};
//__________________________________________________________________2018-03-26_/
Sowing_operation::Sowing_operation()
: CropSyst_field_operation_VX(CS_OP_ROT_SOWING)
, LADSS_land_use_ID(0)
, LADSS_mgt_ID(0)
, crop_filename("noname.crp")
, management_filename("noname.mgt")
#if (defined (CROPSYST_PROPER) || defined(OFOOT_VERSION))
, seeding_parameters()
#endif
, sowing_date_mode_labeled(FIXED_DATE)
, delay_after_precip    (0)
, appreciable_precip_mm (0)
, sowing_avg_temp       (0)
, sowing_min_PAW        (0.5)
, sowing_max_PAW        (1.0)
, expected_days_to_emerge(0)

, p_sowing_avg_temp         (sowing_avg_temp          ,PP_sowing_avg_temp        ,PPR_sowing_avg_temp          ,PPF_sowing_avg_temp)
, p_sowing_min_PAW          (sowing_min_PAW           ,PP_sowing_min_PAW         ,PPR_sowing_min_PAW           ,PPF_sowing_min_PAW)
, p_sowing_max_PAW          (sowing_max_PAW           ,PP_sowing_max_PAW         ,PPR_sowing_max_PAW           ,PPF_sowing_max_PAW)
, p_expected_days_to_emerge (expected_days_to_emerge  ,PP_expected_days_to_emerge,PPR_expected_days_to_emerge  ,PPF_expected_days_to_emerge)
, p_delay_after_precip      (delay_after_precip       ,PP_delay_after_precip     ,PPR_delay_after_precip       ,PPF_delay_after_precip)
, p_appreciable_precip_mm   (appreciable_precip_mm    ,PP_appreciable_precip_mm  ,PPR_appreciable_precip_mm    ,PPF_appreciable_precip)

/*180326
, v_delay_after_precip      (delay_after_precip                               ,LABEL_delay_after_precip     ,0  ,0   ,30  ,    0,100  ,T_date_Days,TL_Number_of_days_to_delay)
, v_appreciable_precip_mm   (appreciable_precip_mm    ,UC_mm                  ,LABEL_appreciable_precip     ,1,0.0,0.0 ,20.0,0.0  ,100.0,TU_mm,TL_Significant_precipitation_amount)
, v_sowing_avg_temp         (sowing_avg_temp          ,UC_Celcius             ,LABEL_avg_temp               ,2,0  ,0.0 ,30.0,-10.0,40.0 ,TU_degrees_C,TL_Five_day_mean_temp)
, v_sowing_min_PAW          (sowing_min_PAW           ,U_units_not_specified  ,LABEL_min_PAW                ,2,0.5,0.0 , 1.0,  0.0, 1.0 ,TU_0_1,TL_layer_2_is_greater_than,TL_Sow_only_when_PAW)
, v_sowing_max_PAW          (sowing_max_PAW           ,U_units_not_specified  ,LABEL_max_PAW                ,2,1.0,0.0 , 1.0,  0.0, 1.0 ,TU_0_1,TL_layer_1_is_less_than,TL_Sow_only_when_PAW)
, v_expected_days_to_emerge (expected_days_to_emerge                          ,LABEL_expected_days_to_emerge,0  ,0   ,40  ,    0,9999 ,T_date_Days,TL_Typical_number_of_days_for_emergence)
*/
, plant_by_date   (0)                                                            //170331
, management(0)  // Instanciated during simulation run when the rotation is loaded.
, crop_params(0)
, adjusted_for_weather_conditions(false)                                         //170220
{
   #ifdef OFOOT_VERSION
   // typical_relative is used for phenology adjustment in OFoot
   for (nat8 ngs = 0; ngs < NGS_COUNT; ngs++)
      typical_relative[ngs].clear();                                             //140717
   #endif
}
//_constructor_________________________________________________________________/
Sowing_operation::Sowing_operation(const char *_crop_filename,const char *_management_file_name)
: CropSyst_field_operation_VX(CS_OP_ROT_SOWING)
, LADSS_land_use_ID(0)
, LADSS_mgt_ID(0)
, crop_filename(_crop_filename)
, management_filename(_management_file_name)
#if (defined (CROPSYST_PROPER) || defined(OFOOT_VERSION))
, seeding_parameters()
#endif
, sowing_date_mode_labeled(FIXED_DATE)

, sowing_avg_temp       (0)
, sowing_min_PAW        (0.5)
, sowing_max_PAW        (1.0)
, expected_days_to_emerge(0)
, delay_after_precip    (0)
, appreciable_precip_mm (0)

, p_sowing_avg_temp         (sowing_avg_temp          ,PP_sowing_avg_temp        ,PPR_sowing_avg_temp          ,PPF_sowing_avg_temp)
, p_sowing_min_PAW          (sowing_min_PAW           ,PP_sowing_min_PAW         ,PPR_sowing_min_PAW           ,PPF_sowing_min_PAW)
, p_sowing_max_PAW          (sowing_max_PAW           ,PP_sowing_max_PAW         ,PPR_sowing_max_PAW           ,PPF_sowing_max_PAW)
, p_expected_days_to_emerge (expected_days_to_emerge  ,PP_expected_days_to_emerge,PPR_expected_days_to_emerge  ,PPF_expected_days_to_emerge)
, p_delay_after_precip      (delay_after_precip       ,PP_delay_after_precip     ,PPR_delay_after_precip       ,PPF_delay_after_precip)
, p_appreciable_precip_mm   (appreciable_precip_mm    ,PP_appreciable_precip_mm  ,PPR_appreciable_precip_mm    ,PPF_appreciable_precip)

/*180326
, delay_after_precip    (0)   , v_delay_after_precip      (delay_after_precip                               ,LABEL_delay_after_precip     ,0  ,0   ,30  ,    0,100  ,T_date_Days,TL_Number_of_days_to_delay)
, appreciable_precip_mm (0)   , v_appreciable_precip_mm   (appreciable_precip_mm    ,UC_mm                  ,LABEL_appreciable_precip     ,1,0.0,0.0 ,20.0,0.0  ,100.0,TU_mm,TL_Significant_precipitation_amount)
, sowing_avg_temp       (0)   , v_sowing_avg_temp         (sowing_avg_temp          ,UC_Celcius             ,LABEL_avg_temp               ,2,0  ,0.0 ,30.0,-10.0,40.0 ,TU_degrees_C,TL_Five_day_mean_temp)
, sowing_min_PAW        (0.5) , v_sowing_min_PAW          (sowing_min_PAW           ,U_units_not_specified  ,LABEL_min_PAW                ,2,0.5,0.0 , 1.0,  0.0, 1.0 ,TU_0_1,TL_layer_2_is_greater_than,TL_Sow_only_when_PAW)
, sowing_max_PAW        (1.0) , v_sowing_max_PAW          (sowing_max_PAW           ,U_units_not_specified  ,LABEL_max_PAW                ,2,1.0,0.0 , 1.0,  0.0, 1.0 ,TU_0_1,TL_layer_1_is_less_than,TL_Sow_only_when_PAW)
, expected_days_to_emerge(0)  , v_expected_days_to_emerge (expected_days_to_emerge                          ,LABEL_expected_days_to_emerge,0  ,0   ,40  ,    0,9999 ,T_date_Days,TL_Typical_number_of_days_for_emergence)
*/
, plant_by_date   (0)                                                            //170331
, management(0)  // Instanciated during simulation run when the rotation is loaded.
, crop_params(0)
, crop_params_relinquished_to_crop(false)
, adjusted_for_weather_conditions(false)                                         //170220
{}
//_constructor_________________________________________________________________/
Sowing_operation::Sowing_operation(const Sowing_operation &original)
: CropSyst_field_operation_VX(original)
, sowing_date_mode_labeled((Sowing_date_mode)original.sowing_date_mode_labeled.get())
, LADSS_land_use_ID(original.LADSS_land_use_ID)
, LADSS_mgt_ID(original.LADSS_mgt_ID)
, crop_filename(original.crop_filename,CORN::OS::Directory_entry_name::include_copy)
, management_filename(original.management_filename,CORN::OS::Directory_entry_name::include_copy)
#if (defined (CROPSYST_PROPER) || defined(OFOOT_VERSION))
, seeding_parameters(original.seeding_parameters)
#endif
, sowing_avg_temp        (original.sowing_avg_temp)
, sowing_min_PAW         (original.sowing_min_PAW)
, sowing_max_PAW         (original.sowing_max_PAW)
, expected_days_to_emerge(original.expected_days_to_emerge)
, delay_after_precip     (original.delay_after_precip)
, appreciable_precip_mm  (original.appreciable_precip_mm)

, p_sowing_avg_temp         (sowing_avg_temp          ,PP_sowing_avg_temp        ,PPR_sowing_avg_temp          ,PPF_sowing_avg_temp)
, p_sowing_min_PAW          (sowing_min_PAW           ,PP_sowing_min_PAW         ,PPR_sowing_min_PAW           ,PPF_sowing_min_PAW)
, p_sowing_max_PAW          (sowing_max_PAW           ,PP_sowing_max_PAW         ,PPR_sowing_max_PAW           ,PPF_sowing_max_PAW)
, p_expected_days_to_emerge (expected_days_to_emerge  ,PP_expected_days_to_emerge,PPR_expected_days_to_emerge  ,PPF_expected_days_to_emerge)
, p_delay_after_precip      (delay_after_precip       ,PP_delay_after_precip     ,PPR_delay_after_precip       ,PPF_delay_after_precip)
, p_appreciable_precip_mm   (appreciable_precip_mm    ,PP_appreciable_precip_mm  ,PPR_appreciable_precip_mm    ,PPF_appreciable_precip)

/*180326
, sowing_avg_temp        (original.sowing_avg_temp)         , v_sowing_avg_temp         (sowing_avg_temp          ,UC_Celcius             ,LABEL_avg_temp               ,2,0  ,0.0 ,30.0,-10.0,40.0 ,TU_degrees_C,TL_Five_day_mean_temp)
, sowing_min_PAW         (original.sowing_min_PAW)          , v_sowing_min_PAW          (sowing_min_PAW           ,U_units_not_specified  ,LABEL_min_PAW                ,2,0.5,0.0 , 1.0,  0.0, 1.0 ,TU_0_1,TL_layer_2_is_greater_than,TL_Sow_only_when_PAW)
, sowing_max_PAW         (original.sowing_max_PAW)          , v_sowing_max_PAW          (sowing_max_PAW           ,U_units_not_specified  ,LABEL_max_PAW                ,2,1.0,0.0 , 1.0,  0.0, 1.0 ,TU_0_1,TL_layer_1_is_less_than,TL_Sow_only_when_PAW)
, expected_days_to_emerge(original.expected_days_to_emerge) , v_expected_days_to_emerge (expected_days_to_emerge                          ,LABEL_expected_days_to_emerge  ,0  ,0   ,40  ,    0,9999 ,T_date_Days,TL_Typical_number_of_days_for_emergence)
, delay_after_precip     (original.delay_after_precip)      , v_delay_after_precip      (delay_after_precip                               ,LABEL_delay_after_precip       ,0  ,0   ,30  ,    0,100  ,T_date_Days,TL_Number_of_days_to_delay)
, appreciable_precip_mm  (original.appreciable_precip_mm)   , v_appreciable_precip_mm   (appreciable_precip_mm    ,UC_mm                  ,LABEL_appreciable_precip     ,1,0.0,0.0 ,20.0,0.0  ,100.0,TU_mm,TL_Significant_precipitation_amount)
*/
, plant_by_date          (original.plant_by_date)                                //170331
// The following are instanciated during simulation run when the rotation is loaded.
, crop_description       (original.crop_description)                             //130906
, management(0)
, crop_params(0)
, crop_params_relinquished_to_crop(false)
, adjusted_for_weather_conditions(false)                                         //170220
{
 #ifdef OFOOT_VERSION
   for (nat8 gs = 0; gs <= NGS_COUNT; gs++)                                      //140807
      typical_relative[gs].set(original.typical_relative[gs]);                   //140807
      // Currently only emergence, max canopy, and maturity date are used.
 #endif
}
//_constructor_________________________________________________________________/
Sowing_operation::~Sowing_operation()
{  delete management; management = 0;
   if (!crop_params_relinquished_to_crop) delete crop_params;
}
//_destructor_______________________________________________________2002-05-28_/
DECLARE_CONTAINER_ENUMERATED_SECTION(Sowing_event,sowing_operation_section_VV,true);
void Sowing_operation::setup_parameters(Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec,for_write);
   data_rec.expect_string(LABEL_description,description.brief,1024);             //150112_031014
   // although simulation parameters has description,
   // simulation_parameters->setup_parameters does/must not set the description
   // (this is only done by expect structure).
   data_rec.expect_int32("LAND_USE_ID",LADSS_land_use_ID);                       //020811
   data_rec.expect_int32("MGT_ID",LADSS_mgt_ID);                                 //020811
   data_rec.expect_file_name(LABEL_crop,crop_filename);
   data_rec.expect_file_name(LABEL_management,management_filename);
   data_rec.expect_int32("plant_by",plant_by_date);                              //170331
   //Do not record status!
   if (!for_write || (sowing_date_mode_labeled.get() != FIXED_DATE))
   {
   data_rec.expect_enum(
      #ifdef LADSS_MODE
      // In LADSS, sowing mode is FIXED_DATE when sow_ID is loaded
      // In the SOWING parameters table, the mode is specified as "TEMPERATURE_CONDITION"
      (LADSS_mode) ? "TEMPERATURE_CONDITION" :
      #endif
         LABEL_mode
         ,sowing_date_mode_labeled);
   // The following are for conditional sowing mode:

   data_rec.expect_parameter(p_delay_after_precip);
   data_rec.expect_parameter(p_expected_days_to_emerge);
   data_rec.expect_parameter(p_sowing_avg_temp);
   data_rec.expect_parameter(p_sowing_min_PAW);
   data_rec.expect_parameter(p_sowing_max_PAW);
   data_rec.expect_parameter(p_appreciable_precip_mm);

   /*180326
   data_rec.expect_valid_int16(v_delay_after_precip);
   data_rec.expect_valid_int16(v_expected_days_to_emerge);
   data_rec.expect_valid_float32(v_sowing_avg_temp);
   data_rec.expect_valid_float32(v_sowing_min_PAW);
   data_rec.expect_valid_float32(v_sowing_max_PAW);
   data_rec.expect_valid_float32(v_appreciable_precip_mm);
   */
   }
   #if (defined (CROPSYST_PROPER) || defined(OFOOT_VERSION))
   seeding_parameters.setup_parameters(data_rec,for_write);                      //041201
   #endif

   #ifdef OFOOT_VERSION
   data_rec.expect_int32("typical_emergence_date" ,typical_relative[NGS_EMERGENCE]        .ref_date32());
   data_rec.expect_int32("typical_canopy_max_date",typical_relative[NGS_END_CANOPY_GROWTH].ref_date32());
   data_rec.expect_int32("typical_maturity_date"  ,typical_relative[NGS_MATURITY]         .ref_date32());
   #endif
}
//_setup_parameters____________________________________________________________/
const char *Sowing_operation::label_string(std::string &buffer)            const
{
   CropSyst_field_operation_VX::label_string(buffer);
   buffer += "Crop:"
          + crop_description;
   #ifdef LADSS_MODE
   if (!LADSS_mode)
   #endif
   {
        buffer += "(";
        crop_filename.append_to_string(buffer);
        buffer += ")";
   }
   buffer += " Management:";
   if (management)
      buffer += management->description.brief;
#ifdef LADSS_MODE
      if (!LADSS_mode)
#endif
   {
      buffer += "(";
      management_filename.append_to_string(buffer);
      buffer += ")";
   }
   return buffer.c_str();
}
//_label_string_____________________________________________________2017-04-23_/
const wchar_t *Sowing_operation::label_wstring(std::wstring &buffer)       const
{
   std::string buffer_;
   label_string(buffer_);
   CORN::append_string_to_wstring(buffer_,buffer);
   return buffer.c_str();
}
//_label_wstring____________________________________________________2018-02-26_
#ifndef REACCH_PROCEDURES
#if (!defined(AGMIP))
const char *Sowing_operation::get_management_description()                 const
{  return management ? management->description.brief.c_str() : "";               //150112
}
//_get_management_description_______________________________________2002-05-28_/
bool Sowing_operation::good_planting_conditions
(const CORN::Date_const &today
, float64         soil_plant_avail_water_1
, float64         soil_plant_avail_water_2
, float64         crop_est_degday_days_from_now                                  //020220
, float64         crop_deg_day_emerge                                            //020220
,const Weather_spanning_interface &weather)                                      //151130
{  bool determinable = true;
   bool dry_enough =  (soil_plant_avail_water_1 <= (sowing_max_PAW + 0.0001));
   if (!adjusted_for_weather_conditions)                                         //170220
   {
   float64 appreciable_precip_m = mm_to_m(appreciable_precip_mm);                //020220
   // See if there has been any appreciable preciptation in the last X days      //000330
   bool appreciable_rain_in_X_days = false;                                      //000330


   /* NYI
   if (adjusted_for_weather_conditions)                                          //170220
   {
   assert(false); // sowing_precipitation_window_meter hasn't been primed yet
   while (sowing_precipitation_window_meter.get_count()>(Days)delay_after_precip)//141105
      sowing_precipitation_window_meter.remove_at(0);                            //141105
   appreciable_rain_in_X_days = sowing_precipitation_window_meter.provide_max() > appreciable_precip_m; //141105
   } else
   */
   {
   CORN::Date_clad_32 prev_date(today.get_date32());                             //000330
   Precipitation precipitation;                                                  //151119
   for (Days day_ago = 0 ;day_ago < (Days)delay_after_precip ;day_ago++)         //1160331_130120
   {
      if (!weather.get_parameter_on
         (precipitation,UED::STD_VC_precipitation.get(),prev_date))              //151119
      {
         // NYI Need explaination that precipitation is not available
      }
      if (precipitation.get_m() > appreciable_precip_m)                          //151119
         appreciable_rain_in_X_days = true;                                      //000330
      prev_date.dec_day();                                                       //000330
   }
   }
   dry_enough &= !appreciable_rain_in_X_days;                                    //160708_000323_991118
   } // adjusted_for_weather_conditions
   bool damp_enough =
       soil_plant_avail_water_2 >= sowing_min_PAW;

   bool warm_enough = true;                                                      //141216
   switch (sowing_date_mode_labeled.get())
   {
      case MIN_TEMP_REQ    :
      {
         if (!adjusted_for_weather_conditions)                                   //170220
         { // air temperature condition moved to Rotation class
         CORN::Statistical_running_tally avg_air_temp_for_window;
         #define sowing_window_days 15
         Air_temperature_maximum air_temp_max;                                   //151119
         Air_temperature_minimum air_temp_min;                                   //151119
         Air_temperature_average_calculator air_temp_avg                         //151119
            (air_temp_max,air_temp_min);                                         //160204
         for (CORN::Days day_offset = 0; day_offset < sowing_window_days; day_offset++) //131219_131211
         {  CORN::Date_clad_32 lookahead_date(today.get_date32());
            lookahead_date += day_offset;
          air_temp_avg.invalidate();                                           //151120
            // Actually this should now be working is all versions but need to check 151119
            determinable &=
               (   weather.get_parameter_on(air_temp_max,UED::STD_VC_max_temperature.get(),lookahead_date) //151119
                && weather.get_parameter_on(air_temp_min,UED::STD_VC_min_temperature.get(),lookahead_date) //151119
                && air_temp_avg.update().is_valid());                            //151124
            avg_air_temp_for_window.append(air_temp_avg.Celcius());              //151119
         }
         float64 avg_temps = avg_air_temp_for_window.get_mean();                 //131219
         warm_enough = (avg_temps >= sowing_avg_temp);
         }
      } break;
      case DAYS_TO_EMERGE  :
      {  warm_enough = crop_est_degday_days_from_now >= crop_deg_day_emerge;
      } break;
      default: break;
   }
//if (warm_enough && dry_enough &&damp_enough)
//std::clog << "good plant cond:" << today.as_string() << std::endl;
   if (!determinable)
   {
      // Need to explain that could not be accurately determined
      // because weather data unavailable.
      // This is not necessarily an error because we may be nearing
      // the end of a simulation period so planting may not be
      // relevent anyway.
   }
   return (warm_enough && dry_enough &&damp_enough);
}
//_good_planting_conditions____________________________________________________/
#endif
#endif
//______________________________________________________________________________
Rotation_parameters::Rotation_parameters()
: Common_parameters_data_record(NO_ASSOCIATED_DIRECTORY,LABEL_rotation,CS_VERSION)//180626_050323
//180626    ,CS_VERSION_NUMBERS)
, planting_events()
, end_year(Date_clad_32().get_year())
, years(1)
{}
//_constructor______________________________________________________2002-05-30_
nat16 Rotation_parameters::count_computed_plantings()                      const //170310
{  nat16 computed_planting_count = 0;
   FOR_EACH_IN(planting_event,Sowing_event,planting_events,each_planting)
      computed_planting_count
      += planting_event->sowing_op->sowing_date_mode_labeled.get()!=FIXED_DATE;
   FOR_EACH_END(each_planting)
   return computed_planting_count;
}
//_count_computed_plantings__________________________________________2017-3-10_/
bool Rotation_parameters::expect_structure(bool for_write)
{  bool expected = Common_parameters_data_record::expect_structure(for_write);   //161025
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_rotation);
      expect_int16("end_year",end_year);
      expect_int16("years",years);
   EXPECT_ENUMERATED_SECTION(LABEL_sowing,sowing_operation_section_VV,planting_events);
   structure_defined = true;                                                     //120314
   return expected;                                                              //161025
}
//_expect_structure_________________________________________________2002-06-12_/
bool Sowing_event::expect_structure(bool for_write)
{  return                                                                        //170808
   structure_defined = setup_structure(*this,for_write);                         //170808
}
//_expect_structure_________________________________________________2003-10-12_/
bool Sowing_event::setup_structure(Data_record &data_rec,bool for_write) modification_
{  bool satup = Common_event::setup_structure(data_rec,for_write);               //170808
   data_rec.expect_int32(LABEL_date,begin_sync.mod_date32());                    //171115_170525_120518
   data_rec.expect_int32(LABEL_date,      date.mod_date32());                    //171115_170525_120518
   provide_sowing_operation();                                                   //130120
   sowing_op->setup_parameters(data_rec,for_write);
   return satup;                                                                 //170808
}
//_setup_structure__________________________________________________2003-01-13_/
Sowing_operation &Sowing_event::provide_sowing_operation()        /*provision_*/
{  if (!sowing_op)
   {  sowing_op = new Sowing_operation;
      set_operation(sowing_op,true);
   }
   return *sowing_op;
}
//_provide_sowing_operation_____________________________2013-01-18__2003-10-14_/
Common_operation *Sowing_event::set_operation
(Common_operation *_operation ,bool _owns_operation)
{  sowing_op = (Sowing_operation *)_operation;
   return Common_event::set_operation(_operation,_owns_operation);
}
//_2004-12-03___________________________________________________________________
Crop_parameters *Sowing_operation::relinquish_crop_params()
{  if (crop_params)
      crop_params_relinquished_to_crop = true;
   return crop_params;
}
//_2003-07-11___________________________________________________________________
bool Sowing_operation::take_crop_params(Crop_parameters *_crop_params)
{  crop_params = _crop_params;
   crop_params_relinquished_to_crop = false;
   return crop_params_relinquished_to_crop;                                      //160510
}
//_2003-07-11___________________________________________________________________
} // namespace CropSyst


