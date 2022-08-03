#include "model_options.h"
#include "corn/measure/units.h"
#include "corn/data_source/datarec.h"
#ifdef LADSS_MODE
extern bool LADSS_mode;
#endif
//______________________________________________________________________________
const char *rain_event_distribution_label_table[] =
{"realistic"
,"even"
,0 };
//_2008-02-01___________________________________________________________________
const char *infiltration_model_label_table[] =
{"no_infiltration"
,LABEL_cascade
,LABEL_finite_diff
,"cascade_hourly"                                                                //070116
,"no_limitation"                                                                 //070724
,0 };
//_1999-02-13____________________________________________________________________
const char *runoff_model_label_table[] =
{"none"
,LABEL_curve_number
,LABEL_numerical
,0};
//_1999-02-30___________________________________________________________________
const char *leach_observation_depth_mode_label_table[] =
{ "bottom"
, "specified"
, 0};
//_2002-05-19___________________________________________________________________
const char *organic_matter_and_residue_model_label_table[] =
{ "none" // Warning may want better labels for these
, "single_SOM_multiple_residues"                                                 //110928
, "multiple_SOM_multiple_residues" // was V4.4                                   //060327
#if (((CROPSYST_VERSION >0) && (CROPSYST_VERSION < 5)) )
   // The following are deprecated
, "V4.1"  // The original daily timestep   Single mineralizing organic matter pool feed by residue decomposition (original model from Version 3 and 4.1)
, "V4.4" // multiple_SOM_multiple_residues old name
, "V4.9" // Has a single organic matter pool and a single residue pool (per layer)  //070707
, "V4.2" // We used this version for Omaru (daily time step)
, "V4.3" // obsolete
#endif
, 0};
//_2002-05-19___________________________________________________________________
const char *orchard_solid_interception_model_label_table[] =
{ "none"
, "Kemanian-Stockle"
, "Oyarzun-Stockle"
, 0};
//_2007-11-16___________________________________________________________________
const char *moisture_characterization_label_table[] =
{"specific"
,"dry"
,"avg"
,"wet"
,"sat"
,0};
//_2017-03-20___________________________________________________________________

CORN::Parameter_properties_literal  leaching_observation_depth_PP ={"depth", "depth","leaching_observation","Observation depth","(0.0 indicates bottom of soil profile)",""/*"https://en.wikipedia.org/wiki/XXXX"*/ ,UC_meter,0};
CORN:: Parameter_range  leaching_observation_depth_PR ={0.0,10.0,0.0,100.0};
CORN::Parameter_format  leaching_observation_depth_PF ={8,2,10};

CORN::Parameter_properties_literal  event_duration_minutes_PP ={"precipitation_duration", "","submodels","Precipitation event duration",HINT_UNUSED,""/*"https://en.wikipedia.org/wiki/XXXX"*/ ,UT_minute,0};
CORN:: Parameter_range  event_duration_minutes_PR ={60,1440,15,1440};
CORN::Parameter_format  event_duration_minutes_PF ={8,0,10};

CORN::Parameter_properties_literal  initial_CO2_conc_PP ={LABEL_initial_CO2_conc,LABEL_initial_CO2_conc,SUBSECTION_UNUSED,"Initial CO2 concentration",HINT_UNUSED,"https://en.wikipedia.org/wiki/XXXX"       ,UC_parts_per_million,"ppm"};
CORN:: Parameter_range initial_CO2_conc_PR ={200.0,700.0,0.0,1000.0};
CORN::Parameter_format initial_CO2_conc_PF ={5,2,10};

CORN::Parameter_properties_literal  soil_profile_depth_limit_PP ={"profile_depth_limit", "","soil","Precipitation event duration",HINT_UNUSED,""/*"https://en.wikipedia.org/wiki/XXXX"*/ ,UT_minute,0};
CORN:: Parameter_range soil_profile_depth_limit_PR ={0.0,3.0,0.0,10.0};
CORN::Parameter_format soil_profile_depth_limit_PF ={6,2,10};

/*
CORN::Parameter_properties_literal  XXX_PP ={"long_name"          , "short_name",SUBSECTION_UNUSED,"caption",HINT_UNUSED,"https://en.wikipedia.org/wiki/XXXX"       ,UC_XXXXX,0};
CORN::             Parameter_range  XXX_PR ={min_warning,max_warning,min_error,max_error};
CORN::            Parameter_format  XXX_PF ={field_width,precision,radix};
*/

CropSyst_Model_options::CropSyst_Model_options()
:fast_graph(                                                                     //030303
#ifdef LADSS_MODE
   !LADSS_mode
#else
   true
#endif
   )
,display_profile(false)
,minimize_runtime_window(false)                                                  //040609
#if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
,report_format_filename_rel("no_format.fmt")
#endif
,run_nitrogen        (false)
,run_chemical        (false)
,run_salinity        (false)
,run_erosion         (false)                                                     //990227
,run_freezing        (false)                                                     //990618
,erode_soil          (false)                                                     //990227
,subdivide_horizons  (true)                                                      //060229
,hourly_not_in_UI(0x7)                                                           //140529_041104_130415
,organic_matter_and_residue_model_labeled (multiple_SOM_multiple_residues)       //110928(V4_4_ORGANIC_MATTER_AND_RESIDUE) //050726
,infiltration_model_labeled               (CASCADE_DAILY_INFILTRATION)           //990213
,runoff_model_labeled                     (CURVE_NUMBER_RUNOFF_MODEL)
,rain_event_distribution_labeled          (REALISIC_RAIN_EVENT)                  //080201
,snow_pack_model_labeled                  (SIMPLE_SNOW_PACK)                     //991004
,extend_available_weather  (false)                                               //150218
,equilibration             ("")                                                  //170414
,substitute_year_base      (0)
,substitute_year_offset    (0)                                                   //161207
,weather_preclude_date(0)                                                        //170310
,leaching_observation_depth_mode_labeled  (LEACH_BOTTOM_OF_PROFILE)              //140620
#if (CROPSYST_VERSION > 5)
,default_event_duration_minutes(360)
#else
,default_event_duration_minutes(1440)
#endif
,p_default_event_duration_minutes(default_event_duration_minutes,event_duration_minutes_PP,event_duration_minutes_PR,event_duration_minutes_PF)
,CPF_irrigation_disable(false)                                                   //081118
,orchard_solid_interception_model_labeled(Oyarzun_Stockle_orchard_interception)  //071117
#if ((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))
,evapotranspiration_model_labeled(ET_MODEL_AUTOMATIC)                            //051230
,Priestley_Taylor_parameters(VPDmax_parameters.VPDavg_seasonal_fullday_observed) //170808
,VPDmax_parameters()                                                             //170804
#endif
,initial_CO2_conc(350.0)
,p_initial_CO2_conc(initial_CO2_conc,initial_CO2_conc_PP,initial_CO2_conc_PR,initial_CO2_conc_PF) //170604
// 170601 This could be obsolete now use CO2 recalibration files
//#if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
,annual_CO2_change(0.0)          //170604,v_annual_CO2_change  (annual_CO2_change,UC_parts_per_million,LABEL_annual_CO2_change        ,2,  0.0,  0.0,  2.0,0.0,   5.0,"ppm","Annual rate of CO2 concentration change")
//#endif
,leaching_observation_depth(0.0) ,p_leaching_observation_depth(0)//  0.0 indicates the entire profile                            //040714
,soil_profile_depth_limit(0.0)                                                   //170609
,p_soil_profile_depth_limit(soil_profile_depth_limit,soil_profile_depth_limit_PP,soil_profile_depth_limit_PR,soil_profile_depth_limit_PF) //170612
#if (((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))  && !defined(REACCH_VERSION))
,transpiration_model_labeled(LEAF_AND_ROOT_TRANSPIRATION_MODEL ) // eventually make LEAF_AND_ROOT_TRANSPIRATION_MODEL the default //050331
#endif
, total_grazed_biomass(false)
, carbon_sequestered(false)
//#ifdef FLEXCROPPING_VERSION
, FLEXCROPPING_AW_DOY             (0)
//#endif
{
   #ifdef CROPSYST_PROPER
   display_profile =true;
   #endif
}
//______________________________________________________________________________
CropSyst_Model_options::~CropSyst_Model_options()
{  delete p_leaching_observation_depth;
}
//_2004-07-14______________________________________________________destructor__/
bool CropSyst_Model_options::setup_structure(CORN::Data_record &data_rec,bool for_write) modification_
{
   data_rec.set_current_section(LABEL_simulation);
      data_rec.expect_bool("extend_available_weather",extend_available_weather); //150218
      data_rec.expect_string("equilibration",equilibration);                     //170414
   data_rec.set_current_section("weather_substitution");
      data_rec.expect_int8 ("year_offset"    ,substitute_year_offset);           //170323
      data_rec.expect_int16("year_base"      ,substitute_year_base);             //170323
      data_rec.expect_int32("preclude"       ,weather_preclude_date);            //170310
   data_rec.set_current_section(LABEL_output);
      data_rec.expect_bool(LABEL_runtime_graph,fast_graph,VV_bool_entry::form_true );
      data_rec.expect_bool(LABEL_display_profile,display_profile,VV_bool_entry::form_true );  //000406
      #if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
      data_rec.expect_file_name(LABEL_report_format,report_format_filename_rel); //030406
      #endif
      data_rec.expect_file_name("options",output_options_filename_rel);

//170613 #ifdef FLEXCROPPING_VERSION
      data_rec.expect_nat16("AWDOY",FLEXCROPPING_AW_DOY,10);                                  //170531
//170613 #endif

   data_rec.set_current_section(LABEL_submodels);
      data_rec.expect_uint32(LABEL_hourly,hourly_not_in_UI,2);                   //041104
      data_rec.expect_bool(LABEL_run_chemical,run_chemical,VV_bool_entry::form_true );
      data_rec.expect_bool(LABEL_run_nitrogen,run_nitrogen,VV_bool_entry::form_true );
      data_rec.expect_bool(LABEL_run_erosion,run_erosion,VV_bool_entry::form_true );
      data_rec.expect_bool(LABEL_run_freezing,run_freezing,VV_bool_entry::form_true );//990618
      data_rec.expect_bool(LABEL_erode_soil,erode_soil,VV_bool_entry::form_true );   //971117
      data_rec.expect_bool("subdivide_horizons",subdivide_horizons,VV_bool_entry::form_true );   //060229
      data_rec.expect_bool(LABEL_salinity,run_salinity,VV_bool_entry::form_true );
      data_rec.expect_enum(LABEL_infiltration_model,infiltration_model_labeled); //020324
      data_rec.expect_enum(LABEL_snow_pack_model,snow_pack_model_labeled);       //020324
      data_rec.expect_enum("organic_matter_and_residue_model",organic_matter_and_residue_model_labeled);    //050728
      data_rec.expect_enum(LABEL_runoff_model,runoff_model_labeled);
      data_rec.expect_enum("rain_event_distribution",rain_event_distribution_labeled); //080201
      data_rec.expect_parameter(p_default_event_duration_minutes);               //170604_080801
      #if ((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))//  && !defined(REACCH_VERSION))
      data_rec.expect_enum("transpiration_model",transpiration_model_labeled);   //050331
      data_rec.expect_enum("evapotranspiration_model",evapotranspiration_model_labeled);           //051230
      #endif
      data_rec.expect_enum("orchard_interception_model",orchard_solid_interception_model_labeled); //071116
   #if (((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))  && !defined(REACCH_VERSION))
   data_rec.set_current_section("biometeorology");
      Priestley_Taylor_parameters.setup_structure(data_rec,for_write);
      VPDmax_parameters          .setup_structure(data_rec,for_write);
   #endif
   data_rec.set_current_section("CO2");
      data_rec.expect_bool(LABEL_enable,simulate_CO2,VV_bool_entry::form_true );
      data_rec.expect_float32(LABEL_initial_CO2_conc,initial_CO2_conc);
      //deprecated not obsolete #if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
      data_rec.expect_float32(LABEL_annual_CO2_change,annual_CO2_change);
      //#endif
   data_rec.set_current_section("leaching_observation");                         //040714
   if (!p_leaching_observation_depth)
        p_leaching_observation_depth= new Parameter_number(leaching_observation_depth,leaching_observation_depth_PP,leaching_observation_depth_PR,leaching_observation_depth_PF);

      data_rec.expect_enum("mode",leaching_observation_depth_mode_labeled);      //040714
      data_rec.expect_parameter(*p_leaching_observation_depth);                  //170604_040714
   data_rec.set_current_section("optimization_output");                          //040812
      data_rec.expect_bool(LABEL_total_grazed_biomass ,total_grazed_biomass);    //040812
      data_rec.expect_bool(LABEL_carbon_sequestered   ,carbon_sequestered);      //040812
   data_rec.set_current_section("soil");                                         //170609
      data_rec.expect_parameter(p_soil_profile_depth_limit);                     //170612
   return true;
}
//____________________________________________________________setup_structure__/
#if ((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))
bool CropSyst_Model_options::get_end()                             modification_
{
   #if (((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))  && !defined(REACCH_VERSION))
   bool got
   =  VPDmax_parameters          .get_end()
   && Priestley_Taylor_parameters.get_end();
   return got;
   #else
   return true;
   #endif
}
#endif
//_2017-08-11_________________________________________________________get_end__/
void CropSyst_Model_options::copy(const CropSyst_Model_options &from)
{
   fast_graph           = from.fast_graph;
   display_profile      = from.display_profile;                                  //000406
   hourly_not_in_UI     = from.hourly_not_in_UI;                                 //041104
   run_nitrogen         = from.run_nitrogen;
   run_chemical         = from.run_chemical;
   run_salinity         = from.run_salinity;
   run_erosion          = from.run_erosion ;
   run_freezing         = from.run_freezing;                                     //990618
   erode_soil           = from.erode_soil;                                       //971117
   subdivide_horizons   = from.subdivide_horizons;                               //060229
   infiltration_model_labeled.set(from.infiltration_model_labeled.get());        //990213
   runoff_model_labeled    .set(from.runoff_model_labeled.get());                //990220
   rain_event_distribution_labeled.set(from.rain_event_distribution_labeled.get()); //080201
   organic_matter_and_residue_model_labeled.set(from.organic_matter_and_residue_model_labeled.get());    //050726
   snow_pack_model_labeled .set(from.snow_pack_model_labeled.get());             //991004
   extend_available_weather= from.extend_available_weather;                      //150218
   equilibration           = from.equilibration;                                 //170414
   substitute_year_offset  = from.substitute_year_offset;                        //161207
   weather_preclude_date = from.weather_preclude_date;                           //170310
   default_event_duration_minutes = from.default_event_duration_minutes;         //080801
   simulate_CO2            = from.simulate_CO2;
   leaching_observation_depth_mode_labeled.set(from.leaching_observation_depth_mode_labeled.get());      //040714
   leaching_observation_depth = from.leaching_observation_depth;                 //040714
   #if ((CROPSYST_VERSION >= 1) && (CROPSYST_VERSION < 5))
   transpiration_model_labeled.set(from.transpiration_model_labeled.get());      //050331
   evapotranspiration_model_labeled.set(from.evapotranspiration_model_labeled.get()); //051230
   VPDmax_parameters.copy(from.VPDmax_parameters);                               //170804
   Priestley_Taylor_parameters.copy(from.Priestley_Taylor_parameters);           //170808
   //170808 Priestley_Taylor_constant = from.Priestley_Taylor_constant;                   //051230
#endif

   orchard_solid_interception_model_labeled.set(from.orchard_solid_interception_model_labeled.get()); //071121
   initial_CO2_conc= from.initial_CO2_conc;                                      //071121
   //171207 deprecated but not obsolete #if (((CS_VERSION >= 1) && (CS_VERSION <= 4)) && !defined(REACCH_VERSION))
   annual_CO2_change= from.annual_CO2_change;                                    //071121
   //#endif
#if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
   report_format_filename_rel   = from.report_format_filename_rel;               //071121
#endif
   minimize_runtime_window       = from.minimize_runtime_window;                 //071121
   CPF_irrigation_disable = from.CPF_irrigation_disable;                         //081118
   output_options_filename_rel  = from.output_options_filename_rel;              //071121
}
//______________________________________________________________________copy__/
bool CropSyst_Model_options::requires_hourly_soil_profile_temperature()    const
{  return
     ((hourly_not_in_UI & HOURLY_soil_temperature)
      || (organic_matter_and_residue_model_labeled.get() == single_SOM_multiple_residues)  //<- Might not actually need hourly, but need to check
      || (organic_matter_and_residue_model_labeled.get() == multiple_SOM_multiple_residues));
}
//_2006-04-05________________________requires_hourly_soil_profile_temperature__/

