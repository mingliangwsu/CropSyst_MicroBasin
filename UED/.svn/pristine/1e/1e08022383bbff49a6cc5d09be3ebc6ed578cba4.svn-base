#ifndef UED_database_interpolate_datarecH
#define UED_database_interpolate_datarecH

#include "corn/parameters/parameters_datarec.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/chronometry/date_types.hpp"
#include "common/geodesy/geolocation.h"
#include "corn/container/text_list.h"
#define max_UED_files 1000
//______________________________________________________________________________
enum Interpolation_mode
{  ONE_NEAREST_STATION
   // In this mode for each time step the target data value will be
   // (if it isn't already a real data value) copied from the nearest station database
   //  having the respective value for the date.
   //  This searches the next succuessively closest station status until if finds
   //  a value).
,  INVERSE_DISTANCE
   // In this mode, all target stations within the specified radius that have
   // a value for the date are used for the interpolated using inverse distance method.

// In all modes, the target value is interpolated only
// if the target value is not marked as real.
};
extern Label_description interpolation_mode_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(Interpolation_mode_labeled,Interpolation_mode,interpolation_mode_label_table);
//______________________________________________________________________________
class UED_database_interpolate_data_record
: public Common_parameters_data_record
{
   // This record serves both to store selections in the  interpolator GUI
   // and to communicate options to the interpolator program.
 public:
   Interpolation_mode_labeled       interpolation_mode_labeled;
   nat32                            selected_elements;
   int16                            within_radius_km;
   CORN_File_name_instance          current_target_UED_filename;  // This is only used when performing the interpolation.
   //The following modes should be nat8 but I don't yet have expect int parameters in Data_record
   int8 target_mode;
      // 0 = complete existing UED
      // 1 = create points
      // For target directory mode
      int8 copy_or_update_mode; // complete_existing_UED_mode;
         // 0 = copy (or update) selected source UED to target directory
            // In this case all selected source files define
            // the names of the target files, the sources
            // are copied to the target directory and will.
            // be used as targets (Usually the target directory will be empty)
            // any existing file(s) with the same name as the source file(s)
            // will be updated/replaced.
         // 1 = target selected existing UED in target dir
            // In this case a target directory is selected
            // any UED files in this directory may be selected (check boxed)
            // as targets

         // In either case, existing UED files in the target directory
         // with the same name as source files will be updated.

         // 2 = (obsolete) select specific files in any dir.
         // (target filenames are listed in target_UED_filenames)
         // Note that the selected target UED files
         // are copied to the new target directory
         // unless the target directory is the same directory containing the
         // selected target file (so the selected target defines
         // the name of the target file, but it will be put in the target
         // directory.
      int8 generate_points_mode;
         // 0 = single location
         // 1 = multiple points
         int8 single_point_mode;
            // 0 = geocoordinate
            // 1 = centroid
         int8 multiple_points_mode;
            // 0 = entered coordinates
            // 1 = dBase table
      CORN_Directory_name_instance target_directory;
      // For target files mode
   int8 source_mode;
      // For source directory mode
      CORN_Directory_name_instance /*130310 CORN::Ustring */      source_directory;
      // for Source files mode
   CORN::Year                          begin_year;
   CORN::Year                          end_year;
   bool                          estimate_environmental_lapse_rate_adjustment; // For temperature
public:
   Geolocation geolocation;
   bool reading_points_table;
   CORN::Ustring       points_table_ID_field_name;
   CORN::Ustring       points_table_latitude_field_name;
   CORN::Ustring       points_table_longitude_field_name;
   CORN::Ustring       points_table_elevation_field_name;
public:
   #ifdef USE_OS_FS
   CORN::Text_list           //130310 now unqualified
   #else
   CORN::Association_list     exclude_target_UED_filenames;
   #endif
           exclude_target_UED_filenames;
         // Excluded files are unqualified and refer to files in the target directory
   CORN::Association_list     source_UED_filenames;   // source and target file names list have unique keys
         // Source file names may be fully qualified (If they were specifically selected)
         // Or unqualified if a source directory was selected.
public:  // The following are used only in the GUI and are saved simply to remember the previous selection.
   CORN::OS::File_name_concrete points_dbf_filename;
   CORN::Ustring target_UED_filename_prefix;
   // NYI will want to store the points data. (maybe in the dbf file but might want to keep separate

private:
    CORN::Ustring source_UED_filenames_for_IO[max_UED_files];
    CORN::Ustring exclude_target_UED_filenames_for_IO[max_UED_files];
public:
   UED_database_interpolate_data_record();
   virtual void expect_structure(bool for_write) ;
   virtual bool get_end();                                                       //161023
   virtual bool set_start();                                                     //161023
   inline virtual const char *get_primary_section_name() const { return "UED_database_interpolate";};
   inline virtual const char *get_type_label()           const { return "UED database interpolator response file";};
   nat16 get_target_UED_filenames
      (CORN::Text_list &return_target_UED_filenames
      ,bool copy_source_to_target_if_necessary) ;
   nat16 get_source_UED_filenames(CORN::Container &return_source_UED_filenames);
};

#endif

