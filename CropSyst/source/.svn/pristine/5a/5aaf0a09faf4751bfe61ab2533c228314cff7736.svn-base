#ifndef v_simfileH
#define v_simfileH
#include <corn/validate/parameter_file.h>
#include "cs_scenario.h"
class CropSyst_project;
//______________________________________________________________________________
class Valid_CropSyst_scenario
: public CropSyst_scenario
{
public:
   Validation_status status;
   CropSyst_project  &project; // The associated project

   // Eventually the filename will be loaded like location
    Validation_status management_file_status;
    Validation_status soil_file_status;
    Validation_status location_file_status;
    Validation_status recalibration_file_status;
    Validation_status water_table_file_status;
    Validation_status rotation_file_status;

    Validation_status format_file_status;   // optional presumed valid
    Validation_status rot_management_file_status;
    Validation_status rot_crop_file_status;
    Validation_status mapunit_dbf_status;    // optional presumed valid

   CORN::File_name v_soil_filename_htm;
   CORN::File_name v_location_filename_htm;
   CORN::File_name v_management_filename_htm;
   CORN::File_name v_recalibration_filename_htm;
   CORN::File_name v_water_table_filename_htm;
   CORN::File_name v_format_filename_htm;      // presumed valid
   CORN::File_name v_rotation_filename_htm;
   CORN::File_name v_mapunit_htm; // presumed valid
   Validation_status layer_status[MAX_soil_horizons_alloc];
public:
   Valid_CropSyst_scenario
      (CropSyst_project  &i_project);
   virtual void get_end();
   Validation_status validate(const SIM_filename &file_name);
   // Returns true if the file is usable
   // Also validates all selected parameter files.
};
//______________________________________________________________________________
#endif
//v_simfile.h

