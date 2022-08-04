#include "cs_event.h"
#include "crop/crop_param.h"
#include "land_unit_sim.h"
#include "static_phrases.h"
#include "corn/data_source/vv_file.h"
#include "cs_mgmt.h"
#include "cs_scenario_directory.h"
#ifdef LADSS_MODE
#  include "LADSS.h"
#endif
#include "corn/measure/measures.h"
#include <string>

using namespace std;
#include "common/simulation/log.h"
#include "corn/OS/file_system_engine.h"
#include "corn/OS/directory_entry_name_concrete.h"
#  include"rot_param.h"

#include "rotation.h"
#define ASSOCIATE_THIS
#ifdef MICROBASIN_VERSION
#include "CropSyst/source/mgmtevnt.h"
#endif
/*180403 Obsolete Claudio decided to not have this model in CropSyst
#ifdef LIU_XIAO_CROP
#  include "crop/Liu_Xiao/crop_parameters_Liu_Xiao.h"
#endif
*/
#include "CS_suite/application/CS_arguments.h"

bool global_crop_planted = 0;
extern bool LADSS_mode;
//extern const CS::Arguments *CS::global_arguments;
namespace CropSyst {
//______________________________________________________________________________
#ifdef MANAGEMENT
int auto_event_count = 0;                                                        //020913
void Land_unit_simulation_VX::log_automatic_irr_event
(const CORN::Date_const &date , float64 amount)
{
   #if (CS_VERSION==4)
   event_log_ref << "[auto_event_" << (++auto_event_count) << "]" << endl;       //020913
   //170525 now using ISO format date.set_format(D_YMD,D_YYYY|D_Mmm|D_lead_zero,'/',true); //030614
   event_log_ref << "date=" << date.get_date32() << endl;                        //030108
   event_log_ref << "type=Auto irrigation" <<endl;  //TL_Automatic_irrigation    //020913
   event_log_ref << "description=" << curr_automatic_irrigation_mode->description.brief << endl;//150112RLN_020913
   event_log_ref << "amount=" << m_to_mm(amount) << endl;                        //020913
   event_log_ref << "amount_units=mm" << endl;                                   //020913
   event_log_ref << "model=CropSyst" << endl;                                    //020913
   #else
   // eventuall all versions will use explainations
   #endif
}
// end of management specific
//_____________________________________________________log_automatic_irr_event_/
#endif
//______________________________________________________________________________
void Land_unit_simulation_VX::schedule_planting_event
(date32                       planting_date_raw
,CropSyst::Sowing_operation  &sowing_op
,const char                  *sowing_event_ID )
{  // Sowing op will be modified with the loaded crop and management
      // We can exclude sowing events that are outside the simulation period
   #ifdef USE_CS_SIMULATION_ROTATOR
   if (   (planting_date_raw >=simulation_control.start_date.get_date32())
       && (planting_date_raw <= simulation_control.stop_date.get_date32()))      //110104
   #else
   if (   (planting_date_raw >= scenario_control_and_model_options.start_date.get_date32())
       && (planting_date_raw <= scenario_control_and_model_options.stop_date .get_date32())) //110104
   #endif
   {
      CropSyst::Crop_parameters *crop_params = 0;                                //030611
      if (
#ifdef LADSS_MODE
         LADSS_mode ? (sowing_op.LADSS_land_use_ID) :                            //020811
#endif
         sowing_op.crop_filename.length())
      {  //bool is_perennial = false;                                            //021217
         if (                                                                    //030215
#ifdef LADSS_MODE
             !LADSS_mode &&
#endif
             !CORN::OS::file_system_engine.exists(sowing_op.crop_filename)
             && (sowing_op.crop_filename != L"-"))
         {
#ifdef LADSS_MODE
COUTSAFE                   cout << endl;
COUTSAFE                   cout << TL_Crop_file;
COUTSAFE                   cout << ' ';
COUTSAFE                   cout << TL_file_may_not_exist;
COUTSAFE                   cout << ' '<< sowing_op.crop_filename.c_str();
COUTSAFE                   cout << endl;
#endif
#if (defined(MICROBASIN_VERSION) || defined(VIC_CROPSYST_VERSION))
            std::clog<<"\nCan't open crop parameter file:"
                     <<sowing_op.crop_filename.c_str()
                     <<std::endl;
            exit(0);
#endif
         }
         else
         {
            crop_params = new CropSyst::Crop_parameters                          //030611
            (scenario_control_and_model_options.run_nitrogen
            ,scenario_control_and_model_options.run_salinity
            ,true // (Residue)
            ,scenario_control_and_model_options.simulate_CO2);
            sowing_op.take_crop_params(crop_params);                             //030711
            bool crop_loaded = true;                                             //180419_020409
            if (crop_params)                                                     //030611
            {                                                                    //980519
            #ifdef LADSS_MODE
            if (LADSS_mode)
            {  LADSS_crop_data_source crop_data_source(sowing_op.LADSS_land_use_ID); //030611
                  crop_loaded = crop_data_source.get(*crop_params);              //020409
                  // I need to set the crop land_use_ID
            } else
            #endif
            {
               /*180403 Obsolete Claudio decided to not have this model in CropSyst
               #ifdef LIU_XIAO_CROP
               if (sowing_op.crop_filename.has_extension_ASCII("crop_LX"))       //180117
               {
                  VV_File crop_data_source(sowing_op.crop_filename.c_str(),true);//180117
                  crop_params->parameters_Liu_Xiao                               //180117
                     = new Liu_Xiao::Crop_parameters_struct;                     //180117
                  Liu_Xiao::Crop_parameters_data_record Liu_Xiao_crop_params_data_rec //180117
                     (*crop_params->parameters_Liu_Xiao); //180117
                  crop_loaded &= crop_data_source.get(Liu_Xiao_crop_params_data_rec);         //180106
                  Liu_Xiao_crop_params_data_rec.resolve_directory_entry_names
                  (sowing_op.crop_filename.get_parent_directory_name_qualified());//180117

                  sowing_op.crop_filename.set_DEN(Liu_Xiao_crop_params_data_rec.inheritX);//180117

//std::cout << "WARNING hardcoded crop filename" << std::endl;
//sowing_op.crop_filename.set_cstr("W:\\CAMO\\FVSC\\potato\\Simulation\\Russet.crp");

                  //sowing_op.crop_filename = Liu_Xiao_crop_params_data_rec.inherit;
               }
               #endif
               */
               VV_File crop_data_source(sowing_op.crop_filename.c_str(),true);   //120720_010110
               crop_loaded &= crop_data_source.get(*crop_params);                 //020409
               sowing_op.crop_filename.append_to_wstring(crop_params->data_source_URL);  //140731
               //std::clog << "End_DOY:" << crop_params->quiescence.end_DOY << std::endl;

               #if defined(VIC_CROPSYST_VERSION) || defined(MICROBASIN_VERSION)
               // This may be generally applicable for all version
               // In VIC3, crop files are stored in the database directory
               // with descriptive filenames, however, VIC3 uses vegitation codes to identify
               // the crop (single crop) so symbolic links from files named with
               // the crop code to the descriptive filenames have been used.
               // In order to get the descriptive filename, it is necessary
               // to lookup the symbolic link
               #ifdef __linux__
               CORN::OS::Directory_entry_name *resolved_actual_crop_filename =   //150727
                     CORN::OS::file_system_engine.
                        render_resolved_symbolic_link_or_shortcut
                        (sowing_op.crop_filename,false) ;
               if (resolved_actual_crop_filename)                                //150727
               {  crop_params->name =resolved_actual_crop_filename->get_name();
                  delete resolved_actual_crop_filename;
               } else
               #endif
                   crop_params->name = sowing_op.crop_filename.get_name();        //150720
               #endif
               #if (CROPSYST_VERSION==4)
               if (crop_params->adjustments.count() == 0)                        //120720
                   crop_params->delete_structure();                              //120720
               #endif
            }
            }
         }
         #ifdef LADSS_MODE
         if (crop_params)                                                        //051129
         {
            crop_params->sowing_event_ID = sowing_event_ID;                      //051129
            // This is currently only needed for LADSS, but may be useful in the future

            // Crop now has its own event scheduler so adjustments and harvest
            // sensitivity parameter have been moved to Crop_common::initialize()//151004
         }
         #endif
         if (                                                                    //021217
               #ifdef LADSS_MODE
                LADSS_mode ? (sowing_op.LADSS_mgt_ID) :
               #endif
               (sowing_op.management_filename.length() &&
                  CORN::OS::file_system_engine.exists(sowing_op.management_filename))) //000313
         {
            sowing_op.management = new Management;                               //020528
            Management &rot_mgmt = *sowing_op.management; // for consistent pointer dereference compatilibity with OLD_ROTATION  //020528
            #ifdef LADSS_MODE
            if (LADSS_mode)                                                      //020915
            {  LADSS_management_data_source mgmt_DS(sowing_op.LADSS_mgt_ID);     //020915
               mgmt_DS.get(rot_mgmt );                                           //020915
            } else                                                               //020915
            #endif
            {  VV_File rot_mgmt_file(sowing_op.management_filename.c_str());     //020915
               rot_mgmt_file.get(rot_mgmt);                                      //010109
#ifdef MICROBASIN_VERSION
               if (rot_mgmt.N_application_soil_observation_event) {
                   std::string sfilename;
                   CORN::wstring_to_string(sowing_op.management_filename.get_name(),sfilename);
                   rot_mgmt.N_application_soil_observation_event->name = sfilename;
               }
#endif
            }                                                                    //020915
            rot_mgmt.transfer_all                                                //030611
               (scenario_event_list                                              //131020
               ,scenario_control_and_model_options.run_nitrogen                  //130826
               ,BEFORE_PLANTING_MODE
               ,sowing_op.management_filename.c_str());
            rot_mgmt.transfer_all                                                //161009
               (scenario_event_list
               ,scenario_control_and_model_options.run_nitrogen
               ,RELATIVE_TO_SIMULATION_EVENT_MODE
               ,sowing_op.management_filename.c_str());
            rot_mgmt.transfer_all                                                //161009
               (scenario_event_list
               ,scenario_control_and_model_options.run_nitrogen
               ,ACTUAL_DATE_MODE
               ,sowing_op.management_filename.c_str());
            rot_mgmt.transfer_all                                                //030611
               (crop_params->associated_events                                   //151004
               ,scenario_control_and_model_options.run_nitrogen                  //130826
               ,ANY_SYNC_MODE
               ,sowing_op.management_filename.c_str());
            CORN::Date_clad_32 planting_date(planting_date_raw);                 //170525
            crop_params->associated_events.synchronize
               (Synchronization(RELATIVE_TO_SOWING_MODE)   ,planting_date );     //170525_130827_030611
            scenario_event_list.synchronize(Synchronization(BEFORE_PLANTING_MODE) ,planting_date);  //130827_030611
               // Events before planting have to go on the master
               // scheduler event because the crop's event scheduler doesn't
               // exist until the crop is planted
         }
         #if (defined(MICROBASIN_VERSION) || defined(VIC_CROPSYST_VERSION))
         else {
            std::clog<<"\nCan't open management parameter file:"
                     <<sowing_op.management_filename.c_str()
                     <<std::endl;
            exit(0);
         }
         #endif
      }
   }
}
//_2005-01-03__________________________________________schedule_planting_event_/
bool Land_unit_simulation_VX::resolve_and_schedule
(const CORN::Date_clad_32 &planting_date
,modifiable_ CropSyst::Sowing_operation &sowing_op
,const std::string &ID
,const CORN::OS::Directory_name &rotation_dir)
{
/* this should be needed
// I have moved this to rot_param, but I havent tested it yet
// so this is still here for now  171204
*/

   {  // resolve crop file name
      CORN::OS::Directory_entry_name *crop_filename_reset
      = CORN::OS::file_system_engine.render_resolved_absolute_DEN
         (sowing_op.crop_filename,rotation_dir);
      if (crop_filename_reset)
      {  sowing_op.crop_filename.set_DEN(*crop_filename_reset);
         delete crop_filename_reset;
      }
   }
   {  // resolve management filename
      CORN::OS::Directory_entry_name *management_filename_reset
      = CORN::OS::file_system_engine.render_resolved_absolute_DEN
         (sowing_op.management_filename,rotation_dir);
      if (management_filename_reset)
      {  sowing_op.management_filename.set_DEN(*management_filename_reset);
         delete management_filename_reset;
      }
   }
   schedule_planting_event(planting_date.get_date32(),sowing_op,ID.c_str());     //060103
   return true;
}
//_2016-05-12_____________________________________________resolve_and_schedule_/
bool Land_unit_simulation_VX::load_rotation_planting_events()
{
   #ifdef VERBOSE
   if (CS::global_arguments->is_verbose(1))
   {
      std::clog << scenario_control_and_model_options.get_description() << endl; //130827
      std::clog << "Preloading sowing and management operations:" << endl;
   }
   #endif
   CropSyst::Rotation_parameters rotation_params;
   #ifdef LADSS_MODE
   if (LADSS_mode)
   {
      LADSS_rotation_components_data_source rotation_components_DS(rot_ID);      //020811
      rotation_components_DS.get(rotation_params);                               //020811
   } else
   #endif
   {
      if (!scenario_control_and_model_options.rotation_filename.length()) //if rotation file name is not specified  //130827_120909
      {  // assume the sowing events are stored in the scenario file.            //120909
         // (as is the case for OFoot scenarios also for REACCH)                 //120909

         scenario_control_and_model_options.rotation_filename.                   //130827
            set_DEN(scenario_directory->associated_filename());                  //121121
      }                                                                          //120909
      //NYI if (scenario_control_and_model_options.rotation_filename.is_valid())       //160126
      {
         VV_File rotation_file(scenario_control_and_model_options.rotation_filename.c_str());//130827
         #if (defined(MICROBASIN_VERSION) || defined(VIC_CROPSYST_VERSION))
         if (!OS::file_system_engine.exists(scenario_control_and_model_options.rotation_filename)) {
             std::cerr << "Error!!!\t"
                       << "Rotation_file name:" << scenario_control_and_model_options.rotation_filename.c_str()
                       << " DO NOT Exist!"
                       << std::endl;
             exit(0);
         }
         #endif
         rotation_file.get(rotation_params);
      }
   }
   const CORN::OS::Directory_name &rotation_dir = scenario_control_and_model_options.rotation_filename.
            get_parent_directory_name_qualified();

   //nat16 entry_index = 0;
   for (CropSyst::Sowing_event *entry = dynamic_cast<CropSyst::Sowing_event *>(rotation_params.planting_events.pop_at_head())
       ;entry
       ;entry = dynamic_cast<CropSyst::Sowing_event *>(rotation_params.planting_events.pop_at_head()))
   {
   if (entry->is_checked())                                                      //111025
   {  CropSyst::Sowing_operation *sowing_op = entry->sowing_op;
      // For CANMS, we associate the event to this LBF
      // so we can route events to this LBF
      //Sowing dates will only be relative to simulation mode or actual dates this should do both

      if (entry->begin_sync.is_relative())                                       //150217
      {  // This is just a hack to allow CropSyst proper to use OFoot scenarios (with relative date).
         // Relative dates should also be supported By CropSyst proper.
         // Eventually V5 will have a better event parameterization

         nat16 year_index = 0;                                                   //160511
         for (CORN::Year year = scenario_control_and_model_options.start_date.get_year()
             ;year <= scenario_control_and_model_options.stop_date.get_year()
             ;year++)
         {  CORN::Year relative_sow_year = entry->begin_sync.get_year();
            if ((year_index % rotation_params.years) == relative_sow_year)
            {  Sowing_event *planting_event = new Sowing_event(*entry);
               CORN::Year actual_plant_year = year;
               CORN::Date_clad_32 actual_plant_date(actual_plant_year,entry->begin_sync.get_DOY());
               Sowing_operation *actual_op = planting_event->sowing_op;


               resolve_and_schedule(actual_plant_date,*actual_op,entry->ID.c_str(),rotation_dir);
               planting_event->begin_sync.sync_mode_labeled.set(ACTUAL_DATE_MODE);
               planting_event->begin_sync.set(actual_plant_date);
               planting_event->date.set(actual_plant_date);
               scenario_event_list.append(planting_event);
            }
            year_index++;
         }
         delete entry;
      }
      else
      {
      entry->synchronize(Synchronization(SIMULATION_BEGIN_DATE,0),scenario_control_and_model_options.start_date ASSOCIATE_THIS); //030609
      entry->synchronize(Synchronization(ACTUAL_DATE_MODE),scenario_control_and_model_options.start_date ASSOCIATE_THIS);     //030609
      date32 planting_date(entry->date.get_date32());                            //120314_050103
      resolve_and_schedule(planting_date,*sowing_op,entry->ID.c_str(),rotation_dir); //150623
      scenario_event_list.append(entry);
      }
   } else
      delete entry;                                                              //160512
   } // for each entry


/*NYI
   const CropSyst::Rotation *rotation = CropSyst::rotations_global.provide
      (scenario_control_and_model_options.rotation_filename,false); // V4 doesnt have cycling               //160708

   CORN::Unidirectional_list plantings;
      rotation->render_planting_events_adjusted_for_weather_conditions
         (*weather_daily
         ,plantings
         ,ref_start_date().get_year()
         ,ref_stop_date().get_year()
         ,cycle);

      CropSyst::Sowing_event *cycled_planting = 0;
      while (cycled_planting = dynamic_cast<CropSyst::Sowing_event *>(cycled_plantings.pop_at_head()))
      {  cycled_scenario->scenario_event_list.append(cycled_planting);
         CropSyst::Sowing_operation *sow_op = cycled_planting->sowing_op;
         cycled_scenario->schedule_planting_event
            (cycled_planting->date.get_date32(),*sow_op,cycled_planting->ID.c_str());
         know_sowing_for_phenology_adjustment(*sow_op,cycled_planting->date.get_date32());
      }

   #ifdef VERBOSE
   if (plantings.count() == 0)
      cout << "No sowing events specified" << endl;
   #endif
*/
   //NYI if (arguments.verbose_level(1))
   if (global_arguments) {
     if (global_arguments->is_verbose(1))
     {
      cout << "Sowing and management operations loaded" << endl;
     }
   }
   return true;
}
//_______________________________________________load_rotation_planting_events_/

} //namespace CropSyst
//______________________________________________________________________________
#if ( !defined(ADJIRRIG) && !defined(CIROTLLY) && defined(CROPSYST))
profile_print_event::profile_print_event
(const CORN::Date_const &_date
,bool             &_record_soil_profile_today)
: CropSyst::Event(Synchronization(_date))                                        //011207
{  set_operation(new Print_operation(_record_soil_profile_today),true);          //051201
   date.set(_date);                                                              //120314 051201
}
//____________________________________profile_print_event::profile_print_event_/
const char * profile_print_event::label_string(std::string &buffer)        const
{  CropSyst::Event::label_string(buffer);
   buffer += "Soil profile output";
   return buffer.c_str();
}
//_2017-04-23________________________________profile_print_event::label_string_/
bool profile_print_event::Print_operation::process()
{  record_soil_profile_today = true;
   return true;
}
//_2001-02-02____________________profile_print_event::Print_operation::process_/
#endif
//endif PARAMS

