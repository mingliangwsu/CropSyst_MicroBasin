#ifndef CS_project_editor_parametersH
#define CS_project_editor_parametersH
//______________________________________________________________________________
#include "corn/OS/filtered_filename.h"
#  include "project/optimization/carbon_sequestration/carbon_sequestration_param.h"
#  include "project/GIS/GIS_params.h"
#include "cs_project.h"
#include "rptoptns.h"
namespace CropSyst
{
//______________________________________________________________________________
class Project_editor_parameters  //was CropSyst_project_editor_parameters
: public extends_ CropSyst_project
{
public:
/*140309 obsolete
I don't appear to use this anymore,
anyway I want redo how I search/specify the database directory

   Database_location_mode_labeled   STATSGO_database_location_mode_labeled;      //070821 Check if obsolete //020431
#endif
/*140306
   #if (CS_VERSION == 4)
   // in V5 the template_scenario is now defined by the current scenario directory
   CSN_filename         template_scenario_filename;  // This is used when creating new scenario files //051229
   #endif
*/
/*140313 obsolete
   Filtered_file_name   cropping_system_model; // exe filename                   //020430
*/
public: // GIS mode info  (I think for watershed only)
   float32  cell_width;      // Watershed model
   bool     subsurface_flow;                                                     //990604
   bool     watershed_runoff_enabled;                                            //020329
   bool           CPF_water;                                                     //030517
   bool           minimize_runtime_window;                                       //040609
   Filtered_file_name   report_generation_filename_rel;  // check where used, may be obsolete 070425
public:
   // The statistics and probablity selections are unpacked for used in the program
   // These arrays are not stored in the file; instead,
   // they are packed into GS_statistic_selection ANNL_statistic_selection which are stored.
   nat32 GS_statistics       [GS_MAX_IDS];
   nat32 GS_probability_10   [GS_MAX_IDS];
   nat32 GS_probability_5    [GS_MAX_IDS];
   nat32 ANNL_statistics     [MAX_YLY_entries];
   nat32 ANNL_probability_10 [MAX_YLY_entries];
   nat32 ANNL_probability_5  [MAX_YLY_entries];
 public:
   GIS_Project_parameters  GIS;                                                  //140306_050202
         //140306 was GIS_project_params
   Carbon_sequestration_optimization_parameters carbon_sequestration_optimization_parameters; //040810
 public: // 'structors
   Project_editor_parameters();
 public: // data record overrides
   virtual bool set_start();                                                     //161023_010109
   virtual bool get_end() ;                                                      //161023_010109
   virtual bool expect_structure(bool for_write);
};
//_2007-08-21_________________________class CropSyst::Project_editor_parameters_/
} // Namespace CropSyst
#endif

