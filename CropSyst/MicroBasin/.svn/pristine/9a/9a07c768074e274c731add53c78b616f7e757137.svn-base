#ifndef MicroBasin_engineH
#define MicroBasin_engineH
#  include "CS_suite/simulation/CS_simulation_engine.h"
#  include "CS_suite/simulation/CS_land_unit.h"
#  include "cs_scenario_directory.h"
#  include "land_unit_sim.h"

#  include "common/simulation/log.h"
namespace CropSyst
{
//______________________________________________________________________________
class MicroBasin_Engine
: public extends_ CS::Simulation_engine
, public extends_ CS::Land_unit  // eventually rename to Land_unit_weather
{
 public:
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   /* At this time I don't really need specialization of Scenario directory
   // but might have additional files in the
   class Scenario_directory
   : public extends_ CropSyst::Scenario_directory
   {
    public:
      Scenario_directory(const CORN::OS::Directory_name &_scenario_directory);
   };
   */
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Simulation_control
   : public extends_ CS::Simulation_control
   {
    public:
      Simulation_control(nat8  major,nat8  release,nat8  minor);
      virtual Common_operation *get_operation                                    //030808
         (const char *operation_type_str
         ,const std::string &operation_ID
         ,modifiable_
            CORN::OS::File_name                                                  //120913
            &operation_filename // the fully qualified operation filename may be returned (to be output to the schedule)
         ,int32 resource_set_ID,bool &relinquish_op_to_event)
         { return 0; }
         // NYN in this model
      inline virtual const char *get_type_label()                          const { return "MicroBasin";}

   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Cell
   : public extends_ Land_unit_simulation
   {
    public:
      //141212 Cannot have an event log for every cell there will be a single event log for the run
      // Common_simulation_log            event_log;
      // Each cell must have its own event log which we will
      // transfer from at the end of the day
    protected:
      CORN::OS::Directory_name_concrete output_directory_name;
    public:
      Cell
         (sint32                        _LBF_ID                                     //020504
         ,CropSyst::Scenario           &_scenario_control_and_model_options         //130827
         ,const CORN::Date             &_today                                      //130619
         ,Scenario_directory           *_scenario_directory);                       //050619
      inline virtual const CORN::OS::Directory_name &get_output_directory_name()const { return output_directory_name; }
    public: //Event scheduler overrides
      virtual Common_operation *get_operation                                       //030808
         (const char *operation_type_str
         ,const std::string &operation_ID
         ,modifiable_
            CORN::OS::File_name                                                  //120913
            &operation_filename // the fully qualified operation filename may be returned (to be output to the schedule)
         ,int32 resource_set_ID,bool &relinquish_op_to_event)
         { return 0; }
    public:
      bool process_hourly(CORN::Hour hour);

   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 private:
   CropSyst::Scenario_directory scenario_directory;
   CropSyst::Scenario cell_scenario; // shared/referenced by all cells
   Simulation_control simulation_control;
   std::string model_name;
 protected:
   CORN::Unidirectional_list &cells;    // reference to subelements
 public:
   MicroBasin_Engine
      (const CORN::OS::Directory_name_concrete &_scenario_directory);
   bool start()                                                    modification_;
 public: // CS::Simulation_engine implementations/overrides
   inline virtual const CORN::OS::Directory_name &get_output_directory_name()const {  return scenario_directory.Output(); }
   inline virtual const std::string &get_model_name()                      const { return model_name; }
   inline virtual const CORN::OS::File_system::Directory &provide_scenario_directory() provision_ { return scenario_directory;}
   inline virtual const std::wstring &get_control_file_name_unqual()       const { return L"MicroBasic.CropSyst_scenario" ; }
 public: // CS::Event scheduler implementations/overrides
   inline virtual Common_operation *get_operation
      (const char                   *operation_type_str
      ,const std::string            &operation_ID  // filename may be updated with qualification so not const
      ,modifiable_ CORN::OS::File_name &operation_filename
         // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32       resource_set_ID,  bool &relinquish_op_to_event)
      {return 0; }
      //Not currently needed by this model
   inline virtual Event_status perform_operation
      (Common_operation &op
      ,const void *associated_with_obj)                            modification_
      { return EXIT_SUCCESS; }
      //Not currently needed by this model
   inline virtual Event_status process_model_specific_event
      (const Simple_event *event)                                  modification_
      { return EXIT_SUCCESS; }
      //Not currently needed by this model
   virtual bool process_day()                                      modification_;//150611RLN   
 protected: // member
   bool lateral_flow()                                             modification_;
};
//_2013-11-01_______________________________________________MicroBasin_Engine__/
} // namespace CropSyst
#endif
