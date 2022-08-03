#ifndef ARCCS_COOP_H
#define ARCCS_COOP_H
#include <options.h>
#include "corn/condcomp.h"
#include "CropSyst/project/GIS/GIS_project.h"
#include "CropSyst/project/GIS/GIS_coop.H"
#include "avgprob3/avgprob.h"
#include "rptoptns.h"
#include "fmt_param.h"
#include "CropSyst/project/GIS/GIS_table.h"

#ifdef OWL_API
#   define OWLAPI
#   include <owl\owlpch.h>
#  include "corn/rui/bsysemod/completed.h"
#  define GUI_progress_bar RUI::Completed_gauge
#else
#   define OWLAPI _COMMENT_
#endif

#ifdef BUILDER_API
#  include <ComCtrls.hpp>
#  define GUI_progress_bar TProgressBar
#  define BUILDERAPI
#else
#  define BUILDERAPI _COMMENT_
#endif

class Polygon_attribute_table;

extern void average_years                                                        //981212
(Report_formats_parameters &fmt_file                                             //010111
    // This is the report format used to generate the cropsyst output files
,int16          first_sim_year                                                   //981219
,int16          sim_years                                                        //981219
,int16          years_in_rotation
,int32          *equivalent_to_record  // this is a []                           //010130
,int32          *equivalent_to_polygon                                           //010130
,Polygon_attribute_table  &pat
);
//_1998-12-12___________________________________________________________________
class ArcCS_cooperator_simulation      // Rename this to GIS Tallier
: public GIS_project_parameters                                                  //010111
{
 private:
#define        equivalences_allocate 10000
   int32  record_equivalences[equivalences_allocate]; // eventually make dynamically allocated.
   int32  polygon_equivalences[equivalences_allocate]; // eventually make dynamically allocated.
 public: // Constructors
   ArcCS_cooperator_simulation();                                                //990417
 public: // VV file overrides
   virtual void expect_structure(bool for_write = false);                        //980721
 public:
   virtual void setup_common_analysis_structures                                 //981218
   (bool equivalence_optimization);
   void load_previous_run
   (const File_name &override_dbase_fname
//for GUI /*010608_*/    ,TApplication *app
//for GUI /*010608_*/    ,GUI_progress_bar *progress_gauge
               );
   void run
      (bool &continue_run
      ,bool      equivalence_optimization);                                      //001002
   void compute_relevent_soil_WHC();                                             //981218
   void donatelli_analysis_variable_selection();                                 //991120
   void donatelli_analysis();                                                    //981218

            //             The following are setup in setup_tally_files, but also used in main
   File_name XLH_tally_filename;
   int HRV_num_vars_to_print;                                                    //980721
   int HRV_report_crop_variable_column;                                          //980721
 public :
   void setup_tally_files                                                        //990611
      (bool equivalence_optimization);
 private:
   void copy_results_files(int32 from_polygon_ID,int32 to_polygon_ID);           //010514
   int identify_different_crops                                                  //980721
      (const File_name &WKH_filename                                             //980721
      ,int crop_name_column
      ,Association_list &separate_crop_tallies);                                 //980721
};
//______________________________________________________________________________
#endif
// arccs_coop.h

