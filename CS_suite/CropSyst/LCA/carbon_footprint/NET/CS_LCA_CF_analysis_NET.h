#ifndef CropSyst_LCA_carbon_footprint_analysisH
#define CropSyst_LCA_carbon_footprint_analysisH
#include "CS_LCA_CF_receiver_NET.h"

#include "cs_scenario_directory.h"

namespace CropSyst
{
namespace LCA_Carbon_footprint
{
class Event_particulars;
//______________________________________________________________________________
public ref class Analysis
{
   
   CropSyst::Scenario_directory *scenario_directory;
 public:
   Analysis(System::String ^scenario_directory_name);
      /** The name of CropSyst scenario directory.
      The directory must contain the CropSyst run Output directory
      containing the CropSyst output schedule and annual UED files.
      **/
   ~Analysis();

   unsigned int scan(IReceiver ^receiver);
      /**
      Reads the scenario's annual_UED file (Output/annual.UED) 
      recorded variables related to GHG emissions.
      This methods also calls scan_schedule().
      \return the number times the receiver know_xxx() methods were called.
      **/
   unsigned int scan_schedule(IReceiver ^receiver);
      /**
      Reads the scenario's event schedule (Output/schedule.txt) file
      for crop and management operation events an calls
      the method analyze_operation_event for each encountered event.
      \return the number of events for which the receiver know_event() method was called.
      **/
 protected:
    bool emit_event(IReceiver ^receiver,const Event_particulars &event_particulars);
};
//_2012-10-23______________________________class:LCA_Carbon_footprint_analysis_/
}; // namespace LCA_Carbon_footprint
}; // namespace CropSyst



#endif
