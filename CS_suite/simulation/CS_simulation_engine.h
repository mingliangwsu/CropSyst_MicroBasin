#ifndef CS_simulation_engineH
#define CS_simulation_engineH

#include "CS_suite/simulation/CS_event_scheduler.h"
#include "CS_suite/simulation/CS_simulation_element.h"
#include "corn/OS/file_system.h"
#ifndef exit_codesH
#  include "common/simulation/exit_codes.h"
#endif
#include "CS_suite/observation/CS_examination.h"
#include "CS_suite/simulation/CS_simulation_element_plugin.h"
#include "CS_suite/simulation/CS_simulation_control.h"
#include "CS_suite/file_system/CS_context_discovery.h"
#include "CS_suite/file_system/CS_databases.h"
#include "CS_suite/application/CS_arguments.h"
#include "corn/data_source/command_options_datasrc.h"
#include "CS_suite/observation/CS_desired_vars.h"

class Common_simulation_log;
//______________________________________________________________________________
namespace CS {
class Simulation_control;
//______________________________________________________________________________
#define NO_NEED_TO_LOG 0
// This define can be used when performing operations when it is not necessary to log the event or event parameters/results
//______________________________________________________________________________
class Simulation_engine
: public extends_ Simulation_element_composite
  // Simulation_element_composite now has member event scheduler
{  // This instanciation of the event scheduler has overall
   // control options such as when to start stop
   // and operations between Simulation units
 protected:
   CORN::OS::Directory_entry_name_concrete CWD;                                  //160902
   std::wstring control_filename_extension;                                      //160316_160114
 protected:
   provided_ Context_discovery         *context_discovery;                       //180118_161116

 protected:
   CORN::date32               today_driving_raw;                                 //170524
      // This is the canonical date to which all subelements reference
 protected:
   CORN::Unidirectional_list &simulation_units;
      // reference to Simulation_element:sub_elements
 public:
   provided_ CS::Desired_variables     *desired_variables_daily;                 //180118_170225
      // will be null if no desired variables specified.
 protected: // Databases and stores are optional
   CS::Databases         *databases;                                             //160916
 public:
   nat8 verbose;                                                                 //170211
//170519 replaced with progress_display_global   Progress_indicator   *progress;                                               //170316
   CORN::Command_options_data_source &command_line_options_data_source;          //160826
 private:
   bool can_continue;                                                            //180208 now member
 public:
   Simulation_engine                                                             //160222
      (Command_options_data_source &command_line_options_data_source);           //160826
   virtual ~Simulation_engine();                                                 //151204
 public: // Item implementations
   inline virtual bool is_key_string(const std::string &key)       affirmation_; //180820
   /*180820
   virtual const char *get_key()                                          const; //150917
   */   
 public: // accessor
   // These are references the dates stored in the user parameter:
   inline virtual const CORN::Date_const &ref_start_date()                 const //151008
      { return ref_simulation_control().start_date; }                            //160222
   inline virtual const CORN::Date_const &ref_stop_date()                  const //151008
      { return ref_simulation_control().stop_date; }                             //160222
   Context_discovery         &provide_context_discovery()         provision_/*modification_*/; //170627
 public: // CS::Simulation_element implementations
   virtual bool preinitialize()                                 initialization_; //170227
   virtual bool initialize()                                    initialization_;
   virtual bool start()                                           modification_;
 public:
    virtual Simulation_run_result run()                           modification_;
   /**<\fn This runs the simulation and contains the daily loop.
      Generally it will not be overridden.
      Before the daily loop starts, the starting and ending
      date events will be syncronized (since these will have
      been provided in the constructor.
      \return true if the run completed with no errors.
      \return false if the simulation was aborted
      Note, may want to return error or run result code
   **/
   virtual bool is_rotation_shifting_enabled()                     affirmation_; //151008
 protected: // The following methods may be be overridden by derived classes.
   inline virtual bool end_operation_period
      (Common_operation &op
      , const CORN::Date_const &date_period_ends)  modification_{ return true; }
   /**<\fn This is used to indicate the end of an event period.
      Derived classes may use this method to perform any additional processing to
      discontinue the operation, or as an opportunity to perform the operation "one more time".
      Normally this function should return true since it is intended as a single to the simulation
      that the event is to be disabled, but the derived object may elect to return false
      to 'postpone' the disable.  The simulation will continue to call the end_operation_period
      every time step until this function returns true
   **/
   virtual const CORN::OS::Directory_name &get_output_directory_name()    const=0;
      // rename this to provide_output_directory_name and make it at provision_

   /**<\fn The default output directory is the current working directory.
      However, typically (as in CropSyst), there should be a directory specifically for output,
      so this method should be overloaded.
   **/
   inline nat32 get_ID()                                                   const
      { return (nat32)
         #if (__LP64__ || _M_X64)
         (int64_t)                                                               //120511
         #endif
         this;}
   virtual const std::string &get_model_name()                          const=0; //120925
 protected:
   inline virtual const CORN::OS::Directory_name
      &provide_scenario_directory_name()                              provision_
      { return CWD; }
      // Derived classes often reimplement this method
   inline virtual const std::wstring &get_control_file_name_extension()    const //160505
      {  return control_filename_extension; }
   virtual const std::wstring &get_scenario_file_name_extension()       const=0; //160114
   inline virtual CORN::Data_record &get_control_data_rec()        modification_ //160308
      {return  mod_simulation_control(); }                                       //160621
   inline virtual CORN::Data_record &get_scenario_data_rec()       modification_ //160114
      {return  mod_simulation_scenario();}                                       //160621
      ///< Derived classes will override if

   virtual modifiable_ CS::Arguments *mod_arguments()              modification_ //180118
      { return 0; }
   virtual const CS::Arguments *ref_arguments()                            const //180118
      { return 0; }
      // arguments are optional
   virtual nat16 designate_accessible_files()                     modification_; //170629
   nat16 designate_accessible_scenario_parameter_filenames()      modification_; //170629
   virtual bool apply_command_line_arguments()                    modification_; //160222
   virtual const       Simulation_control &ref_simulation_control()     const=0; //160224
   virtual const       Simulation_control &ref_simulation_scenario()    const=0; //160224
   inline virtual modifiable_ Simulation_control
      &mod_simulation_control()                                    modification_
      { return const_cast<Simulation_control &>(ref_simulation_control()); }
   inline virtual modifiable_ Simulation_control
      &mod_simulation_scenario()                                   modification_
      { return const_cast<Simulation_control &>(ref_simulation_scenario()); }
   nat32 discover_daily_TDF_and_optate_daily_variables
      (Desired_variables &desired_vars)                              provision_; //180118
      ///< /return number of daily_variables added.
   std::ofstream *status_restart()                                modification_; //180208
      ///< /return optionl status stream (if status wanted)
 public:
   Databases         &provide_databases();
   nat8 define_scenario_from_scenario_path()                      modification_; //161031
 protected:
   nat32 resolve_parameter_filenames_kadigins                                    //171117
      (const CORN::Text_list &path_items)                         modification_;
   bool resolve_parameter_filename_kadigins                                      //171117
      (CORN::OS::Directory_entry_name &param_filename // both input and output
      ,const CORN::Text_list &path_items)                                 const;
   CORN::OS::File_name_concrete *resolve_kadagins                                //171117
      (const CORN::Text_list/*NYI _wstring*/ &potential_kadigins
      ,const CORN::Text_list/*NYI _wstring*/ &path_items
      ,const std::wstring                    &extension)                  const;
 public:
   nat32 find_and_reset_missing_parameter_file_names()            modification_; //170211
 protected:
   // The plugin system is currently intended for version 5
   // but I may add it also to V4
   nat8 find_and_load_plugins()                                      provision_; //150915
      // Returns the number of plugins loaded
 public: // inspectors are public because they are general output, not actually part of the model
   inline virtual const Emanator *get_emanator()             const { return 0; } //160606
      // Inspection is optional
   virtual const char *get_ontology()                                     const; //160606
};
//_class_Simulation_engine__________________________________________2013-06-19_/
} // namespace CS
//______________________________________________________________________________
#endif


