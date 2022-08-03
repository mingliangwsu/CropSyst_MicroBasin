#include "common/weather/loc_param.h"
#include "CS_suite/application/CS_suite_directory.h"
#include "corn/data_source/vv_file.h"
#include "options.h"
#include "cs_project.h"
#include "land_unit_output_V4.h"
#include "soil.h"
#include "crop/crop_param.h"
#include "crop/crop_interfaced.h"
#include "crop/crop_N_common.h"
#include "soil/chemicals_profile.h"
#include "soil/chemical_balance.h"
#include "soil/nitrogen_profile.h"
#include "cs_accum.h"
#include "LADSS_CropSyst.h"
//______________________________________________________________________________
// These sequence numbers are used to give unique H_OUT_ID and A_OUT_ID
uint16 LADSS_harvest_sequence = 1;                                               //020923
LADSS_CropSyst_Model *LADSS_CropSyst_model = 0;                                  //030810
//______________________________________________________________________________
Location_parameters *LADSS_CropSyst_Model::load_location_parameters()      const
{
   Location_parameters *location = new Location_parameters("",true,CS_VERSION_NUMBERS); //030911
   Database_data_source location_datasrc(LADSS_database_schema table("LOCATION") ,"LOC_ID" ,std::ios_base::in  database_session);   //111108 //020613
   location_datasrc.where_long("LOC_ID",LBF_location.loc_ID);                    //060406
   /*unused bool got = */ location_datasrc.get(*location);                       //021213
   char loc_ID_cstr[10];                                                         //021213
   CORN::int32_to_cstr(LBF_location.loc_ID,loc_ID_cstr,10);                      //030103
#if ((CS_VERSION >= 1) && (CS_VERSION < 5))
#ifdef DISABLED
   location->weather_filename_V3.set_file(loc_ID_cstr);
   location->weather_filename_V3.set_ext("ued");
   location->weather_filename_V3.set_path(weather_directory);
   if (!location->weather_filename_V3.exists())
   {
#ifdef LADSS_UNIX
      Ustring command(CS_Suite_directory->UED_application_directory.convert_LADSS);
      command.append(" import . "); // import to the current directory
      command.append(loc_ID_cstr);
      command.append(" 0 9999 ");
      command.append(LADSS_database->SR_xxx);
      command.append(" ");
      command.append(LADSS_database->user_ID);
      command.append(" ");
      command.append(LADSS_database->password);
      system(command.c_str());
#endif
   }
#endif
#endif
      // Need to convert LADSS altitude to elevation
   location->geolocation->set_elevation_meter(topography.altitude);
VV_File dump_loc("dump.loc");
dump_loc.set(*location);
   return location;
}
//_2002-06-13___________________________________________________________________
LADSS_CropSyst_Model::LADSS_CropSyst_Model
(
//160312 CORN::Date       &_driving_date                                                 //150921
const CropSyst::Arguments_V4 &arguments_                                        //151128
//160312 , modifiable_ Geocoordinate &geocoordinate_                                             //151128
//160311 ,const CORN::OS::Directory_name   &_weather_directory
//151128 ,CropSyst::Land_unit_with_output_V4 &_land_unit_with_output
//160312 ,CropSyst::Scenario &scenario_control_and_model_ops_                       //151128
      //151128 ,CropSyst_Model_options       &_active_model_options
,CropSyst::Desired_variables            &_desired_variables
//151128,Report_formats_parameters    *_reports
//160312 ,bool                          _batch_mode
)
: CropSyst_V4::CropSyst_Model                                                    //151003
   (//151203 Now using Simulation_engine _driving_date,
    arguments_
//160313   ,geocoordinate_
   //151128 ,_land_unit_with_output
   //151128,_active_model_options
   //160312   ,scenario_control_and_model_ops_
   ,_desired_variables
   //151128 ,_reports
   //160312 ,_batch_mode
   )
,topography()
,weather_directory(0)                                                            //160312
//160312 ,weather_directory(weather_dir)
{
}
//______________________________________________________________________________
bool LADSS_CropSyst_Model::initalize()
{
   bool initialized = CropSyst_V4::CropSyst_Model::initialize();                              //160312
   //160311 Moved from CropSyst_main()
      LADSS_database = new LADSS_database_parameters;                            //030110
      {  // Load LADSS response parameters. We need to have the  parameters for
         // opening the Oracle database. These are stored in a response file
         // specified as the first command line argument.
         VV_File LADSS_file(arguments.argv[1]);                                            //020611
         LADSS_file.get(*LADSS_database);                                        //020611
      }
      LADSS_database->scenarios_dir.create();                                    //021214
      LADSS_database->scenarios_dir.set_as_current_working_directory();          //040617
      LADSS_database_daily_output = LADSS_database->daily_output;                //040617
      #  ifdef LADSS_ORACLE
      // In LADSS, parameters are stored in a fixed Oracle database structure.
      // To use Oracle we first need to open a server session.
      oracle_session = new Oracle_server_session(LADSS_database->user_ID.c_str(),LADSS_database->password.c_str()); //020611
      #  endif
      {     // Load Project options
         // We can now load the project options from the project table           //020611
         #  ifdef Database_data_source
         Database_data_source project_datasrc(LADSS_database_schema table("PROJECT"),"PROJ_ID",std::ios_base::in database_session);  //020611
         // Goto the project record specified in the response file and load the project parameters.               //020611
         project_datasrc.where_long("PROJ_ID",LADSS_database->proj_ID);                                           //020611
         project = new CropSyst_project();                                                                        //050325
         project_datasrc.get(*project);                                                                           //020611
         #  endif
      }
      arguments.GIS_override_table.assign("ALLOCATION");                         //150416_020613
      scenario_ID = LADSS_database->alloc_ID;                                    //020611
   weather_directory= &LADSS_database->weather_dir;                              //160312
   return initalized;
}
//______________________________________________________________________________
#ifdef LADSS_MODE
void LADSS_CropSyst_Model::get_parameters_from_GIS_table
(const char *GIS_override_table_name
,uint32 alloc_ID
,CropSyst_project &_project)                                                     //021208
{



     // In LADSS the land block fragment simulation is for a particular
      // allocation (rotation) we need to compose the simulation
      // from a couple of sources.
      LADSS_allocation allocation;
      Database_data_source allocation_datasrc(LADSS_database_schema table("ALLOCATION") ,"ALLOC_ID",std::ios_base::in   database_session);
      // Goto the project record specified in the response file and load the project parameters.
      allocation_datasrc.where_long("ALLOC_ID",LADSS_database->alloc_ID);
      allocation_datasrc.get(allocation);

   {// Get the project parameters to be used for this scenario
      Database_data_source simulation_datasrc(LADSS_database_schema table("SIMULATION") ,"SIM_ID",std::ios_base::in   database_session);
      // Goto the project record specified in the response file and load the project parameters.
      simulation_datasrc.where_long("SIM_ID",allocation.sim_ID);
      CORN::Data_record &project_data_rec = dynamic_cast<CORN::Data_record &>(_project);  //130827
      simulation_datasrc.get(project_data_rec );
   }
   {// Get the start and end dates from the simulation table
      Database_data_source simulation_datasrc(LADSS_database_schema table("SIMULATION") ,"SIM_ID",std::ios_base::in   database_session);
      // Goto the project record specified in the response file and load the project parameters.
      simulation_datasrc.where_long("SIM_ID",allocation.sim_ID);
      simulation_datasrc.get(land_unit_with_output->scenario_control_and_model_options); // for the start and end date. //130827
   }
   {  Database_data_source LBF_location_datasrc(LADSS_database_schema table("LBF_LOCATION"),"LBF_LOC_ID" ,std::ios_base::in database_session);
      LBF_location_datasrc.where_long("LBF_LOC_ID",allocation.LBF_loc_ID);
      LBF_location_datasrc.get(LBF_location);
      //140216 land_unit_with_output.scenario_control_and_model_options.loc_ID_str=LBF_location.loc_ID;
      CORN::append_int32_to_string(LBF_location.loc_ID,land_unit_with_output->scenario_control_and_model_options.loc_ID_str); //140216
   }
   {// Get the LBF_simulation from the LBF table
      Database_data_source LBF_datasrc(LADSS_database_schema table("LBF"),"LBF_ID",std::ios_base::in   database_session);
      LBF_datasrc.where_long("LBF_ID",LBF_location.LBF_ID);
      LBF_datasrc.get(land_unit_with_output->scenario_control_and_model_options);
   }
   {  Database_data_source LBF_datasrc(LADSS_database_schema table("LBF"),"LBF_ID",std::ios_base::in   database_session);
      LBF_datasrc.where_long("LBF_ID",LBF_location.LBF_ID);
      LBF_datasrc.get(LBF);
   }
   CORN:: append_int32_to_string  (allocation.rot_ID,land_unit_with_output->scenario_control_and_model_options.rot_ID_str); //140216
   //Some location parameters are in the LADSS LBF record.
   // Need to convert LADSS aspect to location elevation.
   {// Get the LBF_INIT
      Database_data_source LBF_init_datasrc(LADSS_database_schema table("LBF_INIT") ,"LBF_INIT_ID",std::ios_base::in  database_session);
      LBF_init_datasrc.where_long("LBF_INIT_ID",LBF.LBF_init_ID);
      LBF_init_datasrc.get(land_unit_with_output->scenario_control_and_model_options); //130827
   }
   {// Get the topography
      Database_data_source topography_data_source(LADSS_database_schema table("TOPOGRAPHY") ,"TOPO_ID",std::ios_base::in  database_session);
      topography_data_source.where_long("TOPO_ID",LBF.topo_ID);
      topography_data_source.get(topography);
   }
   CropSyst::Soil *soil = land_unit_with_output->get_soil();
   soil->parameters_ownable->steepness_percent = tan(deg_to_rad(topography.slope)) * 100.0;
#ifdef LADSS_UNIX
// This is for debugging
VV_File dump_csn("dump.csn");
dump_csn.set(land_unit_with_output);
#endif
}
#endif
//______________________________________________________________________________
//040923       Note, I now have a datarecord (see UED_season) for UED output that could also replace this data record for LADSS
LADSS_season_output_data_record::LADSS_season_output_data_record
(int32 _alloc_ID
,CropSyst::Land_unit_simulation &simulation
,const CropSyst::Crop_interfaced *crop                                           //130716  //131008NS
)
: CORN::Data_record("-")
, s_out_ID                 ((int32)_alloc_ID * (int32)10000 + (int32)LADSS_harvest_sequence)
, alloc_ID                 (_alloc_ID)
, land_use_ID              (crop->param_LADSS_land_use_ID())
, rot_comp_ID              (atoi(crop->get_sowing_event_ID()))
, planting_date            (crop->get_planting_date())
, restart_date             (crop->get_restart_date())
, emergence_date           (crop->get_emergence_date())
, flowering_date           (crop->get_flowering_date())
, tuber_init_date          (crop->get_tuber_init_date())
, grain_filling_date       (crop->get_grain_filling_date())
//NYI, initial_fruit_growth_date(simulation.crop->initial_fruit_growth_date)
//NYI, rapid_fruit_growth_date  (simulation.crop->rapid_fruit_growth_date)
, peak_LAI_date            (crop->ref_GAI_max_date()) //180413 get_largest_GAI_date())
, maturity_date            (crop->get_maturity_date())
, harvest_date             (crop->get_harvest_date())


//040728 WARNING need to output biomatter fates
, total_yield              (0)
, dry_biomass              (over_m2_to_ha *crop->get_total_season_biomass_production_kg_m2())
, root_depth               (0.05) // set below crop->get_root_length_m() + simulation.soil->get_thickness_m(1))
, nitrogen_leached_total   (0)  // calculated below
, nitrogen_uptake_total    (0)   // calculated below
, nitrogen_available       (0)      // calculated below
, total_mineralization     (0)    // calculated below
, used_biomass             (0) // set below
, grazed_biomass           (0) // set below
, residue_biomass          (0) // set below
, disposed_biomass         (0) // set below
{
   // Nitrogen values calculations:
   CropSyst::Period_accumulators *GP_accumulators = simulation.GP_accumulators_active;
   const CropSyst::Soil *soil = simulation.get_soil_read_only();
   if (soil)
   {  root_depth =    crop->get_root_length_m() + soil->get_layers()->get_thickness_m(1);//150424
      NO3_Profile *NO3 = soil->chemicals ? soil->chemicals->NO3 : 0;
      NH4_Profile *NH4 = soil->chemicals ? soil->chemicals->NH4 : 0;
      if (NO3 && NH4)
      {
         nitrogen_leached_total  // kg/ha
         = (NO3 && NH4 )
         ?(over_m2_to_ha * (NO3->chem_to_element_factor*(NO3->GP_bal_accums_current->reported_leached_M)
            + NH4->chem_to_element_factor*(NH4->GP_bal_accums_current->reported_leached_M)))
         : 0.0;
      nitrogen_available   // kg/ha
         = over_m2_to_ha *
         (NO3->chem_to_element_factor*(NO3->GP_bal_accums_current->original_profile_content_M)
         +NH4->chem_to_element_factor*(NH4->GP_bal_accums_current->original_profile_content_M)
         +NH4->chem_to_element_factor*(NH4->GP_bal_accums_current->transformed_from_M)
         +NO3->chem_to_element_factor*(NO3->GP_bal_accums_current->applied_M)
         +NH4->chem_to_element_factor*(NH4->GP_bal_accums_current->applied_M)
         +simulation.GP_accumulators_active->N_fert_requirements);

      total_mineralization  // kg/ha
      = over_m2_to_ha *
         (  GP_accumulators->OM_N_mineralization
#ifdef CHECK_OBSOLETE
090818
Don't delete yet
I don't think this is really obsolete because we still have V4.1 model
//050118 we now only have mineralization from organic matter
          + GP_accumulators->manure_mineralization_V4_1
          + GP_accumulators->straw_mineralization_V4_1
#endif
         );
      }
   }
   const CropSyst::Crop_nitrogen_interface *crop_N_kg_m2 = crop->get_nitrogen();
   nitrogen_uptake_total // kg/ha
   = over_m2_to_ha * (crop_N_kg_m2->get_mass_in_plant() - crop_N_kg_m2->get_mass_of_seedling() + GP_accumulators->gaseous_N_loss); //{ 960802 }
   Crop_mass_fate *biomass_fate_season = crop->get_biomass_fate_season();
   total_yield              =over_m2_to_ha *biomass_fate_season->yield;
   used_biomass             =over_m2_to_ha *biomass_fate_season->useful;
   grazed_biomass           =over_m2_to_ha *biomass_fate_season->get_removed_for_grazing();
   residue_biomass          =over_m2_to_ha *biomass_fate_season->chaff_or_leaf_litter + biomass_fate_season->stubble_dead;
   disposed_biomass         =over_m2_to_ha *biomass_fate_season->disposal;
   LADSS_harvest_sequence++;
}
//_2002-09-23___________________________________________________________________
void LADSS_season_output_data_record::expect_structure(bool for_write )
{  CORN::Data_record::expect_structure(for_write);
   structure_defined = false;                                                    //120314
   expect_int32   ("S_OUT_ID",               s_out_ID);
   expect_int32   ("ALLOC_ID",               alloc_ID);
   expect_int32   ("LAND_USE_ID",            land_use_ID);
   expect_int32   ("ROT_COMP_ID",            rot_comp_ID);
   if (!for_write || planting_date.get())       expect_date    ("PLANTING_DATE",          planting_date,false);
   if (!for_write || restart_date.get())        expect_date    ("RESTART_DATE",           restart_date,false);
   if (!for_write || emergence_date.get())      expect_date    ("EMERGENCE_DATE",         emergence_date,false);
   if (!for_write || flowering_date.get())      expect_date    ("FLOWERING_DATE",         flowering_date,false);
   if (!for_write || tuber_init_date.get())     expect_date    ("TUBER_INIT_DATE",        tuber_init_date,false);
   if (!for_write || grain_filling_date.get())  expect_date    ("GRAIN_FILLING_DATE",     grain_filling_date,false);
   if (!for_write || peak_LAI_date.get())       expect_date    ("PEAK_LAI_DATE",          peak_LAI_date,false);
   if (!for_write || maturity_date.get())       expect_date    ("MATURITY_DATE",          maturity_date,false);
   if (!for_write || harvest_date.get())        expect_date    ("HARVEST_DATE",           harvest_date,false);
   expect_float32 ("YIELD",                  total_yield);
   expect_float32 ("DRY_BIOMASS",            dry_biomass);
   expect_float32 ("ROOT_DEPTH",             root_depth);
   expect_float32 ("NITROGEN_LEACHED_TOTAL", nitrogen_leached_total);
   expect_float32 ("NITROGEN_UPTAKE_TOTAL",  nitrogen_uptake_total);
   expect_float32 ("NITROGEN_AVAILABLE",     nitrogen_available);      // seasonal nitrogen available
   expect_float32 ("TOTAL_MINERALIZATION",   total_mineralization);
   expect_float32 ("USED_BIOMASS",           used_biomass);
   expect_float32 ("GRAZED_BIOMASS",         grazed_biomass);
   expect_float32 ("RESIDUE_BIOMASS",        residue_biomass);
   expect_float32 ("DISPOSED_BIOMASS",       disposed_biomass);
   structure_defined = true;                                                     //120314
}
//_2004-04-29___________________________________________________________________
LADSS_annual_output_data_record::LADSS_annual_output_data_record
(int32  i_alloc_ID, Year i_year
,CropSyst::Land_unit_simulation  &simulation)
: CORN::Data_record("-")
, a_out_ID              ((int32)i_alloc_ID * (int32)10000 + (int32)year)  // Note, this now actually generated by Oracle
, alloc_ID              (i_alloc_ID)
, year                  (i_year)
, ET_pot                (m_to_mm(simulation.ANNL_accumulators_active->pot_evapotranspiration))
, ET_act                (m_to_mm(simulation.ANNL_accumulators_active->act_evapotranspiration))
//NYI, ET_ref                (m_to_mm(simulation.ANNL_accumulators_active->ref_evapotranspiration))
, transp_pot            (m_to_mm(simulation.ANNL_accumulators_active->pot_transpiration))
, transp_act            (m_to_mm(CORN_must_be_greater_or_equal_to(simulation.ANNL_accumulators_active->act_transpiration,0.0)))
, evap_soil_pot         (m_to_mm(simulation.ANNL_accumulators_active->pot_soil_evaporation))
, evap_soil_act         (m_to_mm(simulation.ANNL_accumulators_active->act_soil_evaporation))
, precipitation         (m_to_mm(simulation.ANNL_accumulators_active->precip_m))
, crop_water_intrcpt    (m_to_mm(simulation.ANNL_accumulators_active->crop_intercept))
, surface_water_runoff  (m_to_mm(simulation.ANNL_accumulators_active->runoff))
, ponded_water          (m_to_mm(simulation.pond.get_depth()))
, water_enter_soil      (m_to_mm(simulation.ANNL_accumulators_active->act_water_entering_soil))
, soil_water_drainage   (m_to_mm(simulation.ANNL_accumulators_active->reported_drainage))
, soil_water_balance    (m_to_mm(simulation.ANNL_accumulators_active->water_balance))
, nitrogen_applied_total(0) // calculated below
, nitrogen_leached_total(0)
, nitrogen_uptake_total (0)
, total_mineralization  (0)
, organic_N_applied     (0)
{
#ifdef NITROGEN
   const CropSyst::Soil /*130918 Soil_cropsyst_specific*/  *soil = simulation.get_soil_read_only();        //060803
   if (soil)                                                                     //060803
   {
      NO3_Profile *NO3 = soil->chemicals ? soil->chemicals->NO3 : 0;
      NH4_Profile *NH4 = soil->chemicals ? soil->chemicals->NH4 : 0;

      nitrogen_applied_total = NO3 && NH4
      ? over_m2_to_ha *
              (NO3->chem_to_element_factor*(NO3->ANNL_bal_accums->applied_M)
              +NH4->chem_to_element_factor*(NH4->ANNL_bal_accums->applied_M))
      : 0.0;
      nitrogen_leached_total = NO3 && NH4
      ? over_m2_to_ha *
              (NO3->chem_to_element_factor*(NO3->ANNL_bal_accums->reported_leached_M)
              +NH4->chem_to_element_factor*(NH4->ANNL_bal_accums->reported_leached_M))
      : 0.0;
      nitrogen_uptake_total = NO3 && NH4
      ? over_m2_to_ha *
              (NO3->chem_to_element_factor*(NO3->ANNL_bal_accums->uptake_M)
              +NH4->chem_to_element_factor*(NH4->ANNL_bal_accums->uptake_M))
      : 0.0;
   }
   total_mineralization
   = over_m2_to_ha *
            (simulation.ANNL_accumulators_active->OM_N_mineralization /*110918 NH4_mineralization_N*/
#ifdef CHECK_OBSOLETE
090818
Don't delete yet
I don't think this is really obsolete because we still have V4.1 model
// 050118 we now only have mineralization from organic matter
          + simulation.ANNL_accumulators_active->manure_mineralization_V4_1
          + simulation.ANNL_accumulators_active->straw_mineralization_V4_1
#endif
                     );
   organic_N_applied = over_m2_to_ha * simulation.ANNL_accumulators_active->organic_N_applied;
// we just use the year for the sequence /*_______*/    LADSS_annual_sequence++;
#endif
}
//_2002-09-23___________________________________________________________________
void LADSS_annual_output_data_record::expect_structure(bool for_write)
{  CORN::Data_record::expect_structure(for_write);
   expect_int32   ("A_OUT_ID",               a_out_ID);
   expect_int32   ("ALLOC_ID",               alloc_ID);
   expect_int16   ("YEAR",                   year);
   expect_float32 ("ET_POT",                 ET_pot);
   expect_float32 ("ET_ACT",                 ET_act);
//NYI   expect_float32 ("ET_REF",                 ET_ref);                            //130723
   expect_float32 ("TRANSP_POT",             transp_pot);
   expect_float32 ("TRANSP_ACT",             transp_act);
   expect_float32 ("EVAP_SOIL_POT",          evap_soil_pot);   // I would like to rename to soil_evap_pot
   expect_float32 ("EVAP_SOIL_ACT",          evap_soil_act);   // I would like to rename to soil_evap_act
   expect_float32 ("PRECIPITATION",          precipitation);
   expect_float32 ("CROP_WATER_INTRCPT",     crop_water_intrcpt);
   expect_float32 ("SURFACE_WATER_RUNOFF",   surface_water_runoff);
   expect_float32 ("PONDED_WATER",           ponded_water);
   expect_float32 ("WATER_ENTER_SOIL",       water_enter_soil);       // I would like to rename to soil_water_entering
   expect_float32 ("SOIL_WATER_DRAINAGE",    soil_water_drainage);
   expect_float32 ("SOIL_WATER_BALANCE",     soil_water_balance);      // seasonal nitrogen available
   expect_float32 ("NITROGEN_APPLIED_TOTAL", nitrogen_applied_total);  // I would like to rename to N_applied
   expect_float32 ("NITROGEN_LEACHED_TOTAL", nitrogen_leached_total);  // I would like to rename to N_leached
   expect_float32 ("NITROGEN_UPTAKE_TOTAL",  nitrogen_uptake_total);   // I would like to rename to N_uptake
   expect_float32 ("TOTAL_MINERALIZATION",   total_mineralization);
   expect_float32 ("ORGANIC_N_APPLIED",      organic_N_applied);
   structure_defined = true;                                                     //120314
}
//_1998-12-08___________________________________________________________________

