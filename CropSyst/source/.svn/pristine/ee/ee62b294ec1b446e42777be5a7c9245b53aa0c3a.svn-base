#ifndef GIS_paramsH
#define GIS_paramsH

/*
 This is a base class for CropSyst GIS simulation.
 (Formally known as ArcCS cooperator
   It is used by the GIS and watershed models.

   The classes have the following heirarch

   ArcCS_file
      I/O of arccs files

   ArcCS_cooperator
      This has a control loop which goes through each entry in the
      polygon attribute file, generates simulation files
      the control look call the abstract function process_output()
      which collects the output from the simulation run
      Overrides process_output() to perform ArcCS copperator analysis

   ArcCS_watershed
      This has a control loop which goes through each cell,
      the corresponding entry in the PAT is used to derive the simulation file
*/
#include "project/GIS/pat.h"
#include "rptoptns.h"
#include "corn/OS/directory_entry_name_concrete.h"
#define MAPCROP _COMMENT_

#define LABEL_GIS                    "GIS"
#define LABEL_coverage_PAT           "coverage_PAT_filename"
#define LABEL_polygon_ID_attribute   "polygon_ID_attribute"
#define LABEL_soil_filename          "soil_filename"
#define LABEL_soils_mapped           "soils_mapped"
#define LABEL_soil_attribute         "soil_attribute"
#define LABEL_weather_mapped         "weather_mapped"
#define LABEL_weather_attribute      "weather_attribute"
#define LABEL_rotations_mapped       "rotations_mapped"
#define LABEL_rotation_attribute     "rotation_attribute"
#define LABEL_steepness_mapped       "steepness_mapped"
#define LABEL_steepness_attribute    "steepness_attribute"
#define LABEL_init_PAW_mapped        "init_PAW_mapped"
#define LABEL_init_PAW_attribute     "init_PAW_attribute"
#define LABEL_init_NO3_mapped        "init_NO3_mapped"
#define LABEL_init_NO3_attribute     "init_NO3_attribute"

#define LABEL_equilibrate_years      "equilibrate_years"

#define LABEL_analysis               "analysis"
#define LABEL_donatelli              "donatelli"

class CropSyst_scenario; // forward decl
//______________________________________________________________________________
class GIS_Project_parameters
{public:
   CORN::OS::File_name_concrete coverage_PAT_filename;
   std::string polygon_ID_attribute;
   std::string soil_attribute;
   std::string steepness_attribute;
   std::string uniform_sand_attribute;                                           //050505
   std::string uniform_clay_attribute;                                           //050505
   std::string soil_depth_attribute;                                             //050505
   std::string init_PAW_attribute;                                               //971022
   std::string init_NO3_attribute;                                               //971022
   std::string weather_attribute;
   std::string rotation_attribute;
   std::string recalibration_attribute;                                          //050203
   std::string water_table_attribute;                                            //050203
   bool perform_donatelli_analysis;                                              //991120
   int16 equilibrate_years;                                                      //990509
      // The number of years (records) to skip when tallying yearly and harvest
      //  report outputs, effectively to let the simulation equilibriate.
 public:
   GIS_Project_parameters();
   bool setup_structure(CORN::Data_record &data_rec,bool for_write);             //050202
};
//_2001-01-09_1999-03-23_________________________class:GIS_Project_parameters__/
#endif
//arccs

