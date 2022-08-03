


#include "organic_matter/OM_residues_profile_abstract.h"
#include "land_unit_output.h"
#include "UED/library/controls.h"
#include "crop/crop_interfaced.h"
#include "soil/chemicals_profile.h"
#include "soil.h"
#include "common/weather/weather.h"
#include "corn/data_source/vv_file.h"
#include "cs_scenario_directory.h"
#include "output.h"
#include "cs_ET.h"
#include "cs_simulation.h"
#include "crop/crop_cropsyst.h"
#ifdef NITROGEN
#include "soil/nitrogen_profile.h"
#endif
#include <iomanip>
#ifdef RUSLE_DETAIL
#  include "soil/erosion_RUSLE.h"
#include "weather/storms.h"
#endif
#include "csvc.h"

#include "soil/chemical_balance.h"
#ifdef CS_INSPECTOR_VERSION
#  include "CS_suite/observation/CS_UED_recorder.h"
#endif

using namespace std;
extern ofstream dbg_nitr;
extern float64 N2O_from_nitrification_daily;
#include "crop/canopy_growth_cover_based.h"
using namespace CropSyst;  // Note eventually everything will be under Cropsyst



#ifdef DUMP_CURVE_NUMBERS
namespace CropSyst
{
   extern std::ofstream *SCS_runoff_dat_file;                                    //131216
}
#endif
extern CS_UED_variable_code fast_graph_variables[];                              //160303
#ifdef CROPSYST_PROPER
extern bool harvest_event_failed_today ; // this is a check for Mike Rivingtons spreadsheet
#endif
namespace CropSyst {
//______________________________________________________________________________
Land_unit_output::Land_unit_output
( Land_unit_simulation &land_unit_simulation_                                    //161219
, const CS::Identification           &LBF_ID_                                    //151026
, nat32                              cycle_shift_                                //151026
, CropSyst::Scenario                &scenario_control_and_model_options_         //130827
,const CORN::date32                 &today_                                      //170525
, const Geocoordinate               &geocoordinate_                              //151116
,const CS::Land_unit_meteorological &meteorology_                                //151128
#if (CS_VERSION==4)
,Common_simulation_log              &event_log_
#endif
,const CropSyst::Scenario_directory *scenario_directory_                         //050619
,CS::Desired_variables              *daily_desired_vars_)                        //041021
: CS::Simulation_element_abstract(today_)
, land_unit_simulation(land_unit_simulation_)
,harvest_UED_db         (0)
,harvest_data_src_rec   (0)
,season_UED_db          (0)
,season_data_src_rec    (0)
,annual_UED_db          (0)
,annual_data_src_rec    (0)

//180118 restored #ifndef CS_INSPECTOR_VERSION
,daily_UED_db           (0)  // NYI get this from the scenario                   //030715
,daily_UED_data_src     (0)                                                      //030715
,daily_data_rec         (land_unit_simulation_,*daily_desired_vars_)             //161219
//180118 restored #endif
#if (defined(XLS_OUTPUT) || defined(UED_OUTPUT))
,daily_desired_vars           (daily_desired_vars_)                              //041021
#endif
,output_flags           (OUTPUT_COMPLETE)                                        //151227
{

   if (!daily_desired_vars_)  // disable daily output if no desired variable     //151227
   {
      output_flags ^= OUTPUT_DAILY;                                              //151227
   }

   #if (CROPSYST_PROPER == 5)
   //160530 temporarily output everything for debugging
   output_flags ^= OUTPUT_DAILY;
   #endif

   #if (CROPSYST_PROPER == 4)

   // This should be moved to land_unit_output_V4
   // and in V5 use inspector idiom.

   #ifndef __linux
   CORN::OS::File_name_concrete detail_txt_filename(scenario_directory_->Output(),"detail.txt");  //090803
//moved to landunit_output_V4   detail_txt_stream = new std::ofstream(detail_txt_filename.c_str());             //090803
   #endif
#ifdef RUSLE_DETAIL
   CORN::OS::File_name_concrete RUSLE_detail_txt_filename(*scenario_directory_->output_dir,"RUSLE_detail.txt"); //130818
//180418 moved to land_unit_output_V4   RUSLE_detail_txt_file = new std::ofstream(RUSLE_detail_txt_filename.c_str());
#endif
   #endif
}
//_2004-10-21___________________________________________________________________
bool Land_unit_output::stop()                                      modification_ //160306
{  bool stopped = true;
   std::string event_description("Simulation period");
   if (land_unit_simulation.latest_simulated_date < land_unit_simulation.scenario_control_and_model_options.stop_date.get_date32()) //110104
      event_description.append(" (ended prematurely)");
   datetime64 start_date64 = land_unit_simulation.scenario_control_and_model_options.start_date .get_datetime64(); //110104
   datetime64 end_date64 = land_unit_simulation.latest_simulated_date;                                //110104
   UED::Period_record simulation_period                                          //041012
      (event_description.c_str()
      ,(nat32 )(UED_period_start_date_option | UED_period_end_date_option |UED_period_application_code_option)
      ,start_date64
      ,end_date64 // use current date because the simulation may be prematurely terminated
      ,SIMULATION_PERIOD // appl code
      ,0 // no enumeration
      ,0 // no index
      ,0 // no variable code
      );
   // Not sure why this is crashing in REACCH_VERSION (daily output is only for debug)                           160310
//180118 restored    #ifndef CS_INSPECTOR_VERSION
   if (daily_UED_db)
   {
      daily_UED_db   ->set_period(simulation_period);
daily_UED_db->finish();
      delete daily_UED_db;
   }
   delete daily_UED_data_src;
//180118 restored    #endif

   #if (CROPSYST_PROPER==4 )
   // #error obsolete 161219 moved to Land_unit_with_output_V4::stop()
   #ifndef __linux
      #if (!defined(REACCH_VERSION) && !defined(OFOOT_VERSION))
         //180418 moved to land_unit_output-V4delete detail_txt_stream; detail_txt_stream = 0;                              //131216
         #ifdef DUMP_CURVE_NUMBERS
         delete CropSyst::SCS_runoff_dat_file; CropSyst::SCS_runoff_dat_file = 0;                          //131216
         #endif
         #ifdef DETAIL_DENITR
         delete denitr_detail_stream;
         #endif
         /* moved to land_unit_output_V4
         #ifdef RUSLE_DETAIL
         if (RUSLE_detail_txt_file) delete RUSLE_detail_txt_file; RUSLE_detail_txt_file = 0; //120529
         #endif
         */
      #endif
   #endif
   #endif

   if (harvest_UED_db)
   {
      harvest_UED_db ->set_period(simulation_period);                            //041012
      #ifndef REACCH_VERSION
      // Don't know why crashing in REACCH version
      delete harvest_UED_db;        harvest_UED_db = 0;
      #endif
   }
   if (harvest_data_src_rec)  delete harvest_data_src_rec;  harvest_data_src_rec = 0;
   if (season_UED_db)
   {  season_UED_db  ->set_period(simulation_period);                            //041012
      delete season_UED_db;         season_UED_db = 0;
   }
   delete season_data_src_rec;   season_data_src_rec = 0;
   if (annual_UED_db)
   {  annual_UED_db  ->set_period(simulation_period);                            //041012
      delete annual_UED_db;         annual_UED_db = 0;
   }
   delete annual_data_src_rec;   annual_data_src_rec = 0;
   return stopped;                                                               //160306
}
//______________________________________________________________________________
bool Land_unit_output::initialize()                          initialization_ //151227
{  bool inited = true;

   #ifndef linux
   //160303 moved from CS_mod
   #if (defined(XLS_OUTPUT) || defined(UED_OUTPUT))
   if (land_unit_simulation.scenario_control_and_model_options.fast_graph && daily_desired_vars)      //160303
      daily_desired_vars->append_array_null_terminated(fast_graph_variables);    //160303
         // null terminated                                                      //100702
   #endif
   #endif
   if (!inited) std::clog << "CropSyst::Land_unit_simulation::initialize failed" << std::endl;

   #ifndef __linux
   #if (!defined(REACCH_VERSION) && !defined(OFOOT_VERSION))
   #if (CROPSYST_VERSION == 4)
   organic_matter_percents_file.open(scenario_directory->Output().organic_matter_percents_dat().c_str());  //141119
   organic_matter_percents_file << "horizon\torganic_matter_biomass(%)\tmicrobial_C(%)\tlabile_C(%)\tmetastable_C(%)\tpassive_C(%)\tall_residues_biomass(kg/ha)" << std::endl; //070314
   #endif
   #endif
   #endif
   {  // Open output options and get desired variables                           //041031
      Scenario_output_options output_options;                                    //041031
      VV_File output_opts_file                                                   //041031
#if (CROPSYST_VERSION >= 5)
//NYI In version 5 the output options should be (optionally?) specified on the command line
//(or taken from the project).
(land_unit_simulation.scenario_control_and_model_options.output_options_filename_rel.c_str());        //130827_041031
#else
        (land_unit_simulation.scenario_control_and_model_options.output_options_filename_rel.c_str());//130827_041031
#endif
      output_opts_file.get(output_options);                                      //041031
      #if (defined(XLS_OUTPUT) || defined(UED_OUTPUT))
      if (daily_desired_vars)                                                    //140105
      output_options.list_required_variables(*daily_desired_vars);               //140104_041031
      #endif
   }
   if (output_flags & OUTPUT_DAILY && daily_desired_vars)                        //170227_151227
   {
      CORN::OS::File_name_concrete daily_UED_filename_qual
         (land_unit_simulation.get_output_directory_name(),"daily","UED");                            //160309
//180118 restored       #ifndef CS_INSPECTOR_VERSION
      daily_UED_db         = new CropSyst_UED_database
            (daily_UED_filename_qual.c_str()
            ,(std::ios_base::out)
            ,land_unit_simulation.scenario_control_and_model_options.start_date);
      daily_UED_data_src   = new CS_UED_tuple_data_source(daily_UED_db);
      daily_UED_db->write_generating_application((nat16)CS_VERSION_CODE,"CropSyst"); //140105
//180118 restored       #endif
   }
   #ifdef USE_CS_SIMULATION_ROTATOR
   // The simulation rotator doesn't write annual UED files for each scenario
   // The UED records are stored in memory and will be aggregated.                  //140119
   annual_UED_db        = new UED::Database_file_indexed(0,(std::ios_base::out),false);
   CORN::OS::File_name_concrete season_UED_filename(land_unit_simulation.get_output_directory_name()  ,"season.UED"); //160305
   CORN::OS::File_name_concrete harvest_UED_filename(land_unit_simulation.get_output_directory_name() ,"harvest.UED");  //160305
   CORN::OS::File_name_concrete annual_UED_filename(land_unit_simulation.get_output_directory_name()  ,"annual.UED");   //160305
   harvest_UED_db = new UED::Database_file_indexed(harvest_UED_filename.c_str(),(std::ios_base::out),false); //160305
   season_UED_db  = new UED::Database_file_indexed(season_UED_filename .c_str(),(std::ios_base::out),false); //160305
   annual_UED_db  = new UED::Database_file_indexed(annual_UED_filename .c_str(),(std::ios_base::out),false); //160305

   #else
   harvest_UED_db       = new UED::Database_file_indexed(scenario_directory->CS_output_harvest_UED_cstr,(std::ios_base::out),false);
   season_UED_db        = new UED::Database_file_indexed(scenario_directory->CS_output_season_UED_cstr ,(std::ios_base::out),false);
   annual_UED_db        = new UED::Database_file_indexed(scenario_directory->CS_output_annual_UED_cstr ,(std::ios_base::out),false);
   #endif
   harvest_UED_db ->write_generating_application((nat16)CS_VERSION_CODE,"CropSyst");     //140105
   season_UED_db  ->write_generating_application((nat16)CS_VERSION_CODE,"CropSyst");     //140105
   annual_UED_db  ->write_generating_application((nat16)CS_VERSION_CODE,"CropSyst");     //140105

   harvest_data_src_rec = new Harvest_data_source(harvest_UED_db);
   season_data_src_rec  = new Season_data_source(season_UED_db);
   annual_data_src_rec  = new Annual_data_source(annual_UED_db);
   #if ((CROPSYST_VERSION >=5 ) || defined(USE_CS_LAND_UNIT))
   //140918  Soil_interface should work in all versions, but not tested yet
   #else
   const CropSyst::Soil *soil = ref_soil();                                      //060803
   #endif

   #ifdef NITROGEN
   Soil_chemicals_profile *soil_chemicals = land_unit_simulation.get_soil_chemicals();
   Chemical_balance_accumulators *NO3_GP_bal_accums = (soil_chemicals && soil_chemicals ->NO3) ? soil_chemicals->NO3->GP_bal_accums_current: 0;  //050114
   Chemical_balance_accumulators *NH4_GP_bal_accums = (soil_chemicals && soil_chemicals ->NH4) ? soil_chemicals->NH4->GP_bal_accums_current: 0;  //050114
   if (NO3_GP_bal_accums && NH4_GP_bal_accums )
   season_data_src_rec->N_soil_profile_initial                                   //161130
      = NO3_GP_bal_accums->get_current_profile_content(true)
      + NH4_GP_bal_accums->get_current_profile_content(true);
   #endif
   season_data_src_rec->soil_water_profile_init
      = land_unit_simulation.soil->ref_hydrology()->provide_water_depth_profile(true); //160412_151227
      // This is actually only needed for REACCH
   season_data_src_rec->soil_available_water_15_init
      = land_unit_simulation.soil->ref_hydrology()->calc_available_water_depth_to(1.5); //160601
      // Special output
   std::string weather_description;                                              //050916
/*NYI actually should get from weather file is possible  151208
       (scenario_control_and_model_options.provide_geolocation()->get_station_ID_code())
*/
   // Should be able to move this to land_unit_output_V4                         //160529
//180118 restored    #ifndef CS_INSPECTOR_VERSION
   #if (defined(XLS_OUTPUT) || defined(UED_OUTPUT))
   if (daily_UED_data_src)                                                       //140105_111221
       daily_UED_data_src->register_fields
         (*daily_desired_vars,land_unit_simulation.soil->layers->get_number_sublayers(),UT_arbitrary_date);   //140105_041014
   #endif
   if (daily_UED_db)                                                             //111221
       daily_UED_db->initialize_with_descriptions                                //030715
         (land_unit_simulation.scenario_control_and_model_options.description.brief //150112_130827
         ,weather_description
         ,land_unit_simulation.soil->parameters_ownable->description.brief       //150112
         ,land_unit_simulation.scenario_control_and_model_options.fast_graph);
//180118 restored    #endif
   return inited;
}
//_________________________________________________________________initialize__/
void Land_unit_output::harvest_event
(const CropSyst::Crop_interfaced &crop_at_harvest_)                modification_ //131008
{
   harvest_data_src_rec->update(crop_at_harvest_);                               //070228
   harvest_data_src_rec->record((datetime64)land_unit_simulation.get_today_date32());
}
//______________________________________________________________________________
nat32 Land_unit_output::perform_triggered_synchronizations_today()
{
#ifndef REACCH_VERSION
   modifiable_ CropSyst::Crop_interfaced *crop_active = land_unit_simulation.crop_active_or_intercrop;//130719_131008NS
   if (crop_active)
   {
      const CropSyst::Phenology_interface &phenology = crop_active->ref_phenology();
      bool planted_today =
         phenology.started_today((Normal_crop_event_sequence)NGS_PLANTING);      //151005

      if (planted_today) latest_growth_stage_entered = NGS_PLANTING;
      if ((!latest_sync_date) || planted_today)
         latest_sync_date = (datetime64)land_unit_simulation.get_today_date32(); // If we haven't had a period yet, then today is just the start of the period.
      nat32  period_options = UED_period_start_date_option | UED_period_end_date_option |UED_period_application_code_option|UED_period_index_option|UED_period_enumeration_option|UED_period_variable_code_option;
      if (!latest_sync_date) latest_sync_date = (datetime64)land_unit_simulation.get_today_date32(); // If we haven't had a period yet, then today is just the start of the period.
      Normal_crop_event_sequence current_growth_stage
         = phenology.get_growth_stage_sequence();                                //141222
      if ((latest_growth_stage_entered!=NGS_NONE)
           && (current_growth_stage != latest_growth_stage_entered))
      {
         std::string period_description(get_growth_stage_description(latest_growth_stage_entered,false));  //140103 NYI crop_active-> parameters_ownable->is_fruit_tree()
         period_description.append(":");
         period_description.append(crop_active->get_description());
         UED::Period_record growthstage_period
            (period_description.c_str(),period_options,latest_sync_date
            ,today.get_datetime64(),GROWTH_STAGE_PERIOD
            ,latest_growth_stage_entered
            ,phenology.get_initiation_date(NGS_RESTART).get_date32()             //151005
            ,CSVC_crop_base_growth_stage);                                       //140114_050208
         latest_sync_date = (datetime64) today.get_date32();
//180118 restored          #ifndef CS_INSPECTOR_VERSION
         if (daily_UED_db)                                                       //111221
             daily_UED_db->set_period(growthstage_period);
//180118 restored          #endif
         harvest_UED_db->set_period(growthstage_period);                         //041012
         season_UED_db->set_period(growthstage_period);                          //041012
      }
      latest_growth_stage_entered = current_growth_stage;                        //141222
   }
#endif
   return 0;                                                                     //170315
}
//_2014-01-03___________________________________________________________________
bool Land_unit_output::start()                                                   //130620
{
   bool started = true;
#ifdef NYI
080306 This was an attempt to output the initial data for annual reports,
but the output manager or export utility is not setup to process this.
   CORN::Date day_before_start(today); day_before_start.dec();
   DOY doy = today.get_DOY();
   if (doy == 1)
   {  // If the the simulation start date in Jan 1 then we can
      // output the initial values as if for the previous year
      // When the simulation is not started on Jan 1 outputting
      // initial values as if for the previous year would be confusing an misleading
      Year year = day_before_start.get_year();
      if (annual_data_src_rec)
      {  annual_data_src_rec->update(*get_soil() ,*ANNL_accumulators_active
            ,organic_matter_residues_profile_kg_m2 ? organic_matter_residues_profile_kg_m2->ref_residues() : 0
         ,organic_matter_residues_profile_kg_m2
               ,pond,LBF_ID,year );
         annual_data_src_rec->record(day_before_start.get_datetime64());
      }
   }
   // Currently only outputing initial values for annual outputs
   // Eventually we may add others.
#endif
   #if (CROPSYST_PROPER==4)
   #ifdef _Windows
      #ifndef USE_CS_SIMULATION_ROTATOR

         if (detail_txt_stream)
         {
//   const Crop_complete *crop_CropSyst = dynamic_cast<const Crop_complete *>(crop_active_or_intercrop);

           (*detail_txt_stream)
               << "date" << '\t'
               << "accum_deg_days" << '\t'
               << "chill_hours_remaining"<< '\t';
           (*detail_txt_stream)
               << std::endl;
         };
         #ifdef DUMP_CURVE_NUMBERS
         CORN::OS::File_name_concrete SCS_runoff_dat_filename(scenario_directory->Output(),"SCS_runoff.dat"); //131216
         CropSyst::SCS_runoff_dat_file = new std::ofstream(SCS_runoff_dat_filename.c_str());     //131216
//         SCS_runoff_dat_file->open(scenario_directory->Output().SCS_runoff_dat().c_str()); //131216
         (*CropSyst::SCS_runoff_dat_file)                                                        //131216
                     << "date" << '\t'
                     << "CN1" <<  '\t'
                     << "CN2" <<  '\t'
                     << "CN3" <<  '\t'
                     << "surface_storage";
         #endif
      #endif
      #ifdef RUSLE_DETAIL
         if (RUSLE_detail_txt_file)
            (*RUSLE_detail_txt_file)
               << "date" << '\t'
               << "precip_mm" << '\t'
               << "storm_energy" << '\t'
               << "storm_intensity" << '\t'
               << "C_factor" << '\t'
               << "mulch_factor" << '\t'
               << "moisture_factor" << '\t'
               << std::endl;
      #endif
   #endif
   #endif
   return started;                                                               //080929
}
//_2008-03-06___________________________________________________________________
bool Land_unit_output::end_day()
{  // We call Land_unit_simulation_VX:: end_day first because it update accumulators
   bool result = true;

//std::clog << "debug: daily output disabled" << std::endl;

   //#ifdef FLEXCROPPING_VERSION
   //170531 This is temporary special output for Harsimran
   // eventually this will be handled by journal output and collator
   CORN::DOY doy = today.get_DOY() ;
   if (doy == land_unit_simulation.scenario_control_and_model_options.FLEXCROPPING_AW_DOY)    //170531
   {
      std::string fname("AW@");
      CORN::append_nat16_to_string(land_unit_simulation.scenario_control_and_model_options.FLEXCROPPING_AW_DOY,fname);
      CORN::OS::Directory_name_concrete soil_dir
         (land_unit_simulation.get_output_directory_name()
         ,"soil");
      CORN::OS::File_name_concrete AW_filename_special(soil_dir,fname,"dat");
      CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/(soil_dir);                    //170607brc
      std::ofstream AW(AW_filename_special.c_str());
      AW << "year\tDOY\tsoil:AW/150cm/LEQ.value"
         << "\tsoil:water_depth/profile/LEQ.value" << std::endl;
      float64 AW_150cm = land_unit_simulation.soil->ref_hydrology()->calc_available_water_depth_to(1.5);
      float64 AW_profile = land_unit_simulation.soil->ref_hydrology()->calc_water_depth_profile(true);
      AW << today.get_year()  << '\t'
         << doy   << '\t'
         << AW_150cm << '\t'
         << AW_profile
         << std::endl;
   }
   //#endif

//180118 restored    #ifndef CS_INSPECTOR_VERSION
   if (daily_UED_data_src)                                                       //111228
   {
      daily_UED_data_src->set_date(today.get_datetime64());                      //070228
      daily_UED_data_src->set(daily_data_rec);                                   //070228
   }
//180118 restored    #endif
   #if (CROPSYST_PROPER==4)
   #if (!defined(REACCH_VERSION) && !defined(OFOOT_VERSION))
   #ifdef _Windows
      if (detail_txt_stream)
      {
         const CropSyst::Crop_interfaced *crop_active =                          //131008
         #ifdef INTERCROPPING
            get_predominant_crop();  //130716 this is just debugging output so only need predominant crop
         #else
            crop_active_or_intercrop;
         #endif
         #if (CS_VERSION==4)
         if (crop_active)
         {
            (*detail_txt_stream)
            << today.as_string() << '\t'
            << crop_active->get_accum_degree_days(false) << '\t'
            #ifdef CROP_ORCHARD
            << crop_active->get_fruit_chill_hours_remaining() << '\t'
            #endif
             ;
const CropSyst::Crop_complete *crop_activeA = dynamic_cast
   <const CropSyst::Crop_complete *>(crop_active_or_intercrop);
(*detail_txt_stream)
<< '\t' << crop_activeA->output_transpiration_use_eff
<< '\t' << crop_activeA->output_degree_hours_above_30_today;
//<< '\t' << crop_activeA-output_degree_hours_above_34_today


            // << crop_active->get_solid_canopy_interception()
            (*detail_txt_stream)
            << endl;


         }
         #else
         // In V5 (and eventually V4) use explainations
         #endif
      }
   #endif
   #endif
   #endif

   return result;
}
//_2007-02-27___________________________________________________________________
bool Land_unit_output::start_growing_season
      #if ((REACCH_VERSION==2) || (CS_VERSION >= 5) || defined(INTERCROPPING) || defined(OFOOT_VERSION))
      (modifiable_ CropSyst::Crop_interfaced &crop_at_start_season)
      #else
      ()
      #endif
{  bool started = true;
   if (season_data_src_rec && land_unit_simulation.soil)
   {
      #ifdef NITROGEN
      Soil_chemicals_profile *soil_chemicals = land_unit_simulation.get_soil_chemicals();             //161130
      Chemical_balance_accumulators *NO3_GP_bal_accums = (soil_chemicals && soil_chemicals ->NO3) ? soil_chemicals->NO3->GP_bal_accums_current: 0;  //050114
      Chemical_balance_accumulators *NH4_GP_bal_accums = (soil_chemicals && soil_chemicals ->NH4) ? soil_chemicals->NH4->GP_bal_accums_current: 0;  //050114
      if (NO3_GP_bal_accums && NH4_GP_bal_accums)
      season_data_src_rec->N_soil_profile_initial                                //161130
         = NO3_GP_bal_accums->get_current_profile_content(true)
         + NH4_GP_bal_accums->get_current_profile_content(true);
      #endif
      season_data_src_rec->soil_water_profile_init
         = land_unit_simulation.soil->ref_hydrology()->provide_water_depth_profile(true); //160412_160324
      season_data_src_rec->soil_available_water_15_init
         = land_unit_simulation.soil->ref_hydrology()->calc_available_water_depth_to(1.5);//160601
   }
   return started;
}
//_2016-03-23__________________________________________________________________/
bool Land_unit_output::end_growing_season
#if ((REACCH_VERSION==2) || (CROPSYST_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
(CropSyst::Crop_interfaced &_crop_at_end_season)                                 //131008NS
#else
()
#endif
{  bool result = true;

   output_growing_season
   #if ((REACCH_VERSION==2) || (CROPSYST_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
      (_crop_at_end_season);                                                     //130716
   #else
      ();                                                                        //070227
   #endif
   return result;                                                                //070321
}
//______________________________________________________________________________
bool Land_unit_output::output_growing_season
#if ((REACCH_VERSION==2) || (CROPSYST_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
(const CropSyst::Crop_interfaced &_crop_at_end_season)                           //131008NS
#else
()
#endif
{
#if ((REACCH_VERSION==2) || (CROPSYST_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
   const CropSyst::Crop_interfaced *crop_at_end_season = &_crop_at_end_season; // this line is just temporary eventually we will use reference every where in this method //131008NS
#else
   if (!crop_at_end_season) return;                                              //050209
#endif
   datetime64 planting_or_restart_date                                           //041205
      = crop_at_end_season->
         ref_phenology().get_initiation_date(NGS_PLANTING).get_datetime64();     //041205_151005

   /* NYI Output each of the stages
   for each growth_stage
   if the stage start date of growth_stage is valid (started)
   {
      nat32  period_options = UED_period_start_date_option | UED_period_end_date_option |UED_period_application_code_option|UED_period_index_option|UED_period_enumeration_option|UED_period_variable_code_option;
      //if (!latest_sync_date) latest_sync_date = (datetime64)get_today_date32(); // If we haven't had a period yet, then today is just the start of the period.
      //Normal_crop_event_sequence current_growth_stage = crop_active->ref_phenology().get_growth_stage_sequence(); //141222
      {
         std::string period_description(get_growth_stage_description(latest_growth_stage_entered,false)); //140103 NYI crop_active-> parameters_ownable->is_fruit_tree()));
         period_description.append(":");
         period_description.append(crop_active->get_description());
         UED::Period_record growthstage_period
            (period_description.c_str()
            ,period_options
            ,growth stage start date
            ,growth stage end date
            ,GROWTH_STAGE_PERIOD,latest_growth_stage_entered,crop_active->get_restart_date().get_date32(),CSVC_crop_base_growth_stage); //140114_050208
         latest_sync_date = (datetime64)get_today_date32();
         #if ((REACCH_VERSION<2) || defined(_DEBUG))
         if (daily_UED_db)                                                       //111221
         daily_UED_db->set_period(growthstage_period);
         #endif
         harvest_UED_db->set_period(growthstage_period);                         //041012
         season_UED_db->set_period(growthstage_period);                          //041012
      }
   }
   */

   UED::Period_record season_period                                              //041012
      (crop_at_end_season->get_description() // "Growing season"
      ,UED_period_start_date_option|UED_period_end_date_option|UED_period_application_code_option|UED_period_index_option|UED_period_variable_code_option|UED_period_variable_code_option
      ,planting_or_restart_date                                                  //041205
      ,today.get_datetime64()                                                    //140105_070227
      ,GROWING_SEASON_PERIOD
      ,0 // no enumeration
      ,crop_at_end_season->
            ref_phenology().get_initiation_date(NGS_RESTART)                     //151005
            .get_date32() // The start/restart date is not used to uniquely identify the season
      ,CSVC_crop_base_name);  // NO CSVC
   //output growing season period to UED files
   #if (CROPSYST_VERSION >= 5)
   // I want to output the  management file/designation
   #endif
   // Not sure why this is crashing for REACCH //160309
//180118 restored    #ifndef CS_INSPECTOR_VERSION
   if (daily_UED_db)                                                             //111221
       daily_UED_db->set_period(season_period);
//180118 restored    #endif
   harvest_UED_db->set_period(season_period);                                    //041012
   season_UED_db->set_period(season_period);                                     //041012
   annual_UED_db->set_period(season_period);                                     //041012
   #ifdef CHEM_PROFILE
   Soil_chemicals_profile *soil_chemicals = land_unit_simulation.get_soil_chemicals();
   #endif
   #ifdef NITROGEN
   Chemical_balance_accumulators *NO3_GP_bal_accums = (soil_chemicals && soil_chemicals ->NO3) ? soil_chemicals->NO3->GP_bal_accums_current: 0;  //050114
   Chemical_balance_accumulators *NH4_GP_bal_accums = (soil_chemicals && soil_chemicals ->NH4) ? soil_chemicals->NH4->GP_bal_accums_current: 0;  //050114
   #endif
   #if ((CROPSYST_VERSION >=5 ) || defined(USE_CS_LAND_UNIT))
   //140918  Soil_interface should work in all versions, but not tested yet
   #else
   const CropSyst::Soil *soil = ref_soil();                                      //060803
   #endif
   season_data_src_rec->update
      (*crop_at_end_season
      ,*land_unit_simulation.soil
      ,land_unit_simulation.GP_accumulators_active
      #ifdef NITROGEN
      ,NO3_GP_bal_accums                                                         //050114
      ,NH4_GP_bal_accums                                                         //050114
      #endif
      ,land_unit_simulation.pond
      ,(land_unit_simulation.organic_matter_residues_profile_kg_m2
      ? land_unit_simulation.organic_matter_residues_profile_kg_m2->mod_residues() : 0)
      ,land_unit_simulation.ID.number);                                          //151026
   season_data_src_rec->record((datetime64)today.get_date32());
   return true;
}
//_2005-01-14____________________________________________output_growing_season_/
bool Land_unit_output::end_year()
{  bool result = true;
      #if ((CROPSYST_VERSION >=5 ) || defined(USE_CS_LAND_UNIT))
      //140918  Soil_interface should work in all versions, but not tested yet
      #else
       CropSyst::Soil *soil = mod_soil();                                        //060803
      #endif
   if (annual_data_src_rec)                                                      //050114
   {
      annual_data_src_rec->update(land_unit_simulation.soil                      //180106
      ,*land_unit_simulation.ANNL_accumulators_active                            //050114
      ,land_unit_simulation.organic_matter_residues_profile_kg_m2 ? land_unit_simulation.organic_matter_residues_profile_kg_m2->mod_residues() : 0    //050726
      ,land_unit_simulation.organic_matter_residues_profile_kg_m2
      ,land_unit_simulation.pond,land_unit_simulation.ID.number,today.get_year());//151026
      annual_data_src_rec->record(today.get_datetime64());                       //140224_050114
   }
//180118 restored    #ifndef CS_INSPECTOR_VERSION
/*180118 obsolete
   #ifdef REACCH_VERSION
   // This may have been crashing in proper (it was marked as NYI) //160310
   if (daily_UED_db)
       daily_UED_db->finish();
   #endif
*/
//180118 restored    #endif
   #if (CS_VERSION==4)
   #ifdef RUSLE_DETAIL
   if (RUSLE_detail_txt_file && soil && soil->erosion)                           //160506
      soil->erosion->dump_year_days(*RUSLE_detail_txt_file);                     //160506
   #endif
   #endif
   return result;                                                                //111031
}
//_2001-02-02___________________________________________________________________
bool Land_unit_output::start_year()                           modification_
{  bool started = true;

   //170315 What I should do here is have the soil render_layering
   // and render_hydraulic_properties to be give to the global_UED_recorder
   // as the the soil should not need to know about UED database
   // and this should not need to now anything about UED_File_association
   #ifdef CS_INSPECTOR_VERSION
   if (land_unit_simulation.scenario_control_and_model_options.UED_recording)
   {
   CS::Recorder_UED &glob_UED_rec = CS::ref_global_UED_recorder();
   FOR_EACH_IN(file_assoc,CS::Recorder_UED::UED_File_association,glob_UED_rec.UED_files,each_UED)
   {
      UED::Database_file_indexed  *UED_db = dynamic_cast<Database_file_indexed *>
         (file_assoc->UED_file);
      // we only really need to output layering and hydroprops to
      // UED files that store soil profile values
      if (UED_db)                                                                //111221
      {  land_unit_simulation.soil->output_layering            (*UED_db);
         land_unit_simulation.soil->output_hydraulic_properties(*UED_db); // This was added for Marcello and Andrea Di Guardo  //070209
      }
   } FOR_EACH_END(each_UED)
   }
   #else
   if (daily_UED_db)                                                             //111221
   {  land_unit_simulation.soil->output_layering            (*daily_UED_db);
      land_unit_simulation.soil->output_hydraulic_properties(*daily_UED_db); // This was added for Marcello and Andrea Di Guardo  //070209
   }
   #endif

   #ifdef CHEM_PROFILE
   Soil_chemicals_profile *soil_chemicals = land_unit_simulation.get_soil_chemicals();
   #ifdef NITROGEN
   NO3_Profile *NO3 = soil_chemicals ? soil_chemicals->NO3 : 0;
   NH4_Profile *NH4 = soil_chemicals ? soil_chemicals->NH4 : 0;
   if (NO3 && NH4)                                                               //020529
   {  if (NO3) NO3->update_YLY_bal_reporter();
      if (NH4) NH4->update_YLY_bal_reporter();
   }
   // reporters must be updated before we reset accumulators in start_of_year
   #endif
   #endif
   return started;
}
//_2004-10-14___________________________________________________________________
} // namespace CropSyst

//060306 263 lines
//060727 237 lines

