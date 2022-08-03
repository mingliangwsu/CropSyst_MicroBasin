#pragma hdrstop
#include <UED/spatial/interpolation/UED_database_interpolate_datarec.h>
#include <corn/OS/OS.h>
#ifdef USE_OS_FS
#  include "corn/OS/file_system_engine.h"
#endif

using namespace CORN;
Label_description interpolation_mode_label_table[] =
{{"nearest","Copy each value from nearest station in range having the timestep value."}
,{"inverse_distance","Use inverse distance of each timestep value from stations in range having the timestep value."}
,{0,0}
};
//______________________________________________________________________________
UED_database_interpolate_data_record::UED_database_interpolate_data_record()
:Common_parameters_data_record(REQUIRED_ASSOCIATED_DIRECTORY,0,0,0,"UED_database_interpolate")
,interpolation_mode_labeled(INVERSE_DISTANCE)
,source_UED_filenames(true) // unique key
,exclude_target_UED_filenames() // (true) // unique key
,begin_year(0)
,end_year(9999)
,within_radius_km(50)
,estimate_environmental_lapse_rate_adjustment(true)
,points_dbf_filename
#ifdef USE_OS_FS
("points.dbf")
#else
("dbf","dBase formated table with LATITUDE, LONGITUDE, attributes","*.dbf")
#endif
,selected_elements(0xFFFF)
,target_mode(0)
,target_directory("")
,source_mode(0)
,source_directory("")
,reading_points_table(false)
{  for (int i = 0; i < max_UED_files; i++)
   {  source_UED_filenames_for_IO[i].assign("");
      exclude_target_UED_filenames_for_IO[i].assign("");
   }
}
//______________________________________________________________________________
void UED_database_interpolate_data_record::expect_structure(bool for_write)
{  Common_parameters_data_record::expect_structure(for_write);
   structure_defined = false;                                                    //120314
   if (reading_points_table)
   {
      expect_string (points_table_ID_field_name       .c_str(),geolocation.station_ID_code,255);
      expect_float32(points_table_latitude_field_name .c_str(),geolocation.latitude_dec_deg);
      expect_float32(points_table_longitude_field_name.c_str(),geolocation.longitude_dec_deg);
      expect_float32(points_table_elevation_field_name.c_str(),geolocation.elevation);
   }
   else
   {
   set_current_section("UED_database_interpolate");
   expect_enum("interpolation_mode",interpolation_mode_labeled);
   expect_int16("within_radius",within_radius_km);
   expect_uint32("selected_elements",selected_elements,16);
   #ifdef USE_OS_FS
   expect_directory_entry_name                                                   //130310
   #else
   expect_filename
   #endif
   ("target_UED_filename",current_target_UED_filename);
   expect_bool("estimate_environmental_lapse_rate_adjustment",estimate_environmental_lapse_rate_adjustment);
   expect_int8("target_mode"           ,target_mode);
   expect_int8("copy_or_update_mode"   ,copy_or_update_mode);                    //100926
   expect_int8("generate_points_mode"  ,generate_points_mode);                   //100926
   expect_int8("single_point_mode"     ,single_point_mode);                      //100926
   expect_int8("multiple_points_mode"  ,multiple_points_mode);                   //100926
   #ifdef USE_OS_FS
   expect_directory_entry_name                                                   //130310
   #else
   expect_string
   #endif
   ("target_directory",target_directory,255);
   expect_int8("source_mode",source_mode);
   #ifdef USE_OS_FS
   expect_directory_entry_name                                                   //130310
   #else
   expect_string
   #endif
   ("source_directory",source_directory,255);
   expect_string("target_UED_filename_prefix",target_UED_filename_prefix,255);
   set_current_section("include_data");
      expect_int16("begin_year",begin_year);
      expect_int16("end_year",end_year);
   expect_string_array
      ("source_UED_filenames",source_UED_filenames_for_IO
      ,255
      ,false
      ,(for_write? source_UED_filenames.count() : max_UED_files)
      ,false);
   /*100924 obs now were show exclusions
   expect_string_array
      ("target_UED_filenames",target_UED_filenames_for_IO
      ,255
      ,false
      ,(for_write? target_UED_filenames.count() : max_UED_files)
      ,false);
   */
   expect_string_array
      ("excluded_target_UED_filenames",exclude_target_UED_filenames_for_IO
      ,255
      ,false
      ,(for_write? exclude_target_UED_filenames.count() : max_UED_files)
      ,false);
   set_current_section("points_table");                                          //100926
   {                                                                             //100926
      expect_string("ID_field"         ,points_table_ID_field_name,255);         //100926
      expect_string("latidude_field"   ,points_table_latitude_field_name,255);   //100926
      expect_string("longitude_field"  ,points_table_longitude_field_name,255);  //100926
      expect_string("elevation_field"  ,points_table_elevation_field_name,255);  //100926
   }
   set_current_section("recent");
      #ifdef USE_OS_FS
   expect_directory_entry_name                                                   //130310
   #else
   expect_string
   #endif
   ("points_dbf_filename",points_dbf_filename);
   set_current_section("geolocation");                                           //100926
      geolocation.setup_structure(*this,for_write);                              //100926
   }
   structure_defined = true;                                                     //120314
}
//______________________________________________________________________________
bool UED_database_interpolate_data_record::get_end()
{
   for (int i = 0; i < max_UED_files; i++)
   {
      if (source_UED_filenames_for_IO[i].length())
      {  CORN_File_name_instance *source_fname =  new CORN_File_name_instance(source_UED_filenames_for_IO[i].c_str());
         #ifdef USE_OS_FS
         #else
         source_fname->set_show_path(true);
         source_fname->set_show_extension(true);
         #endif
         source_UED_filenames.append(source_fname);
      };
      source_UED_filenames_for_IO[i].assign(""); // clear because were are done with these arrays for now
   }
   for (int i = 0; i < max_UED_files; i++)
   {
      if (exclude_target_UED_filenames_for_IO[i].length())
         exclude_target_UED_filenames.append(new CORN_File_name_instance(exclude_target_UED_filenames_for_IO[i].c_str()));
      exclude_target_UED_filenames_for_IO[i].assign(""); // clear because were are done with these arrays for now
   }
   return Common_parameters_data_record::get_end();                              //161023
}
//______________________________________________________________________________
bool UED_database_interpolate_data_record::set_start()
{
   int source_count = source_UED_filenames.count();
   for (int i = 0; i < source_count ; i++)
   {  const CORN_File_name *source_UED_filename = dynamic_cast<const CORN_File_name *>// (CORN_File_name *)
         (source_UED_filenames.get_at(i));                                       //130310
      source_UED_filenames_for_IO[i].assign(source_UED_filename->c_str());
   }
   int exclude_target_count = exclude_target_UED_filenames.count();              //100926
   for (int i = 0; i <exclude_target_count; i++)                                 //100926
   {
      CORN_File_name *exclude_target_UED_filename = dynamic_cast<CORN_File_name *>(exclude_target_UED_filenames.get_at(i));   //130310_100926
      exclude_target_UED_filenames_for_IO[i].assign(exclude_target_UED_filename->c_str());   //100926
   }
   return Common_parameters_data_record::set_start();                            //161023
}
//______________________________________________________________________________
nat16 UED_database_interpolate_data_record::get_target_UED_filenames
(
CORN::Text_list
&return_target_UED_filenames
,bool copy_source_to_target_if_necessary)
{
   switch (target_mode)
   {  case 0 : // target directory copying all source UED files
      {  CORN::Association_list source_UED_filename;
         get_source_UED_filenames(source_UED_filenames);
         FOR_EACH_IN(source_UED_filename,CORN_File_name,source_UED_filenames,each_source)
         {
            CORN::OS::File_name_concrete target_UED_filename(target_directory,*source_UED_filename);
            std::wstring name_with_ext; target_UED_filename.get_name_with_extension(name_with_ext);
            return_target_UED_filenames.add_wstring(name_with_ext);
            if (!CORN::OS::file_system_engine.exists(target_UED_filename) &&
                copy_source_to_target_if_necessary)
               CORN::OS::file_system_engine.copy_file(*source_UED_filename,target_UED_filename,true );
         } FOR_EACH_END(each_source)
      } break;
      case 1 :
      {

         150329 need  to use list_file_names which now returns container with qualified filenames.
         CORN::Unidirectional_list target_UED_filenames_qualified

         CORN::OS::file_system_engine.list_file_names_raw                        //130310
            (target_directory
            ,false // not currently recursive but may give the option to the user
            ,target_UED_filenames_qualified
            ,0 // name_wild_card
            ,L"UED"
            ,&exclude_target_UED_filenames);

         continue here:
         loop through  target_UED_filenames_qualified
            return_target_UED_filenames.add_wstring(target_UED_filename_qual->get_name())

      } break;
   } // switch
   // The user may have specifically selected UED files in the
   // target directory to be excluded from interpolation.
   // It is not necessary to removed excluded items because
   // list_file_names_raw can specify items to exclude
   return return_target_UED_filenames.count();
}
//______________________________________________________________________________
nat16 UED_database_interpolate_data_record::get_source_UED_filenames(CORN::Container &return_source_UED_filenames)
{  nat16 source_count = 0;
   switch (source_mode)
   {
      case 0 : // list all files in in the source directory
      {
         #ifdef USE_OS_FS
         source_count =  CORN::OS::file_system_engine.list_file_names                                          //100101
            (source_directory
            ,false // not currently recursive but may give the option to the user
            ,return_source_UED_filenames
            ,0 // name_wild_card
            ,L"UED");
         #else
         CORN_Directory_name_instance source_dir(source_directory);
         source_dir.list_contents_by_type
            (return_source_UED_filenames  // The list to append contents to (association because dirent names are association
            ,false // not currently recursive but may give the option to the user
            ,true                 // true if the known path is prepended to the listed file names (differs from show_path because the path is actually included in the filename)
            ,true          // true if the extension is included with the file name (usually true)
            ,true            // true if the known path is to be prepended when the filename is displayed
            ,true     // true if the extension is to be appended when the filename is displayed
            ,Directory_entry_name::file_entry    // types of files to list (file or directory names)
            ,"UED");
         #endif
      } break;
      case 1 : // list selected filenames
      {
         FOR_EACH_IN(source_UED_filename,CORN_File_name,source_UED_filenames,each_source)
         {
            CORN_File_name_instance *copied_source_UED_filename = new CORN_File_name_instance(*source_UED_filename);
            return_source_UED_filenames.append(copied_source_UED_filename);
         } FOR_EACH_END(each_source)
      }
   }
   #ifndef USE_OS_FS
   source_count = return_source_UED_filenames.count();                           //130310
   #endif
   return source_count;                                                          //130310
}
//______________________________________________________________________________

