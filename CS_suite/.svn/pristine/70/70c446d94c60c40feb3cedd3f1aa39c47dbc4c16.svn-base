
#include "common/weather/database/weather_UED_database.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system_engine.h"
#include "UED/library/database_file.h"
#include "UED/library/timeqry.h"
#include "common/weather/weather_provider.h"
//#include "common/biometeorology/ET_reference_FAO.h"
#include "common/solar/irradiance_extraterrestrial.h"
#include "CS_suite/biometeorology/ETref_injector_UED.h"

#ifdef OBSOLETE
I now have netCDF_to_UED_engine class.


//______________________________________________________________________________
class UED_ETref_calculator
{
   CORN::OS::Directory_name_concrete source_directory;
   CORN::OS::Directory_name_concrete *target_directory;
 public:
   UED_ETref_calculator
      (const CORN::OS::Directory_name_concrete &source_directory_
      ,const CORN::OS::Directory_name_concrete *target_directory_);
   nat32 process_UED_files();
   nat32 process_UED_file_to_UED_file
      (const CORN::OS::File_name &source_file
      ,const CORN::OS::File_name &target_file);
   nat32 process_UED_file
      (const CORN::OS::File_name &source_and_target_file);
   nat32 process_UED_to_UED
      (UED::Database_file_indexed  &source_UED
      ,UED::Database_file_indexed  &target_UED);
      ///< \return the number of days ETref is provided.
   nat32 process_UED
      (UED::Database_file_indexed  &source_and_target_UED);
      ///< \return the number of days ETref is provided.
};
//______________________________________________________________________________
nat32 UED_ETref_calculator::process_UED_file_to_UED_file
      (const CORN::OS::File_name &source_file
      ,const CORN::OS::File_name &target_file)
{  UED::Database_file_indexed source_UED
      (source_file.c_str(),(std::ios_base::in),true);
   UED::Database_file_indexed target_UED
      (target_file.c_str(),(std::ios_base::in | std::ios_base::out),true);
   return process_UED_to_UED(source_UED,target_UED);
}
//______________________________________________________________________________
nat32 UED_ETref_calculator::process_UED_file
(const CORN::OS::File_name &source_and_target_file)
{
   UED::Database_file_indexed source_and_target_UED
      (source_and_target_file.c_str(),(std::ios_base::in | std::ios_base::out),true);
   return process_UED(source_and_target_UED);
}
//______________________________________________________________________________
nat32 UED_ETref_calculator::process_UED
(UED::Database_file_indexed  &source_and_target_UED)
{
   return process_UED_to_UED(source_and_target_UED,source_and_target_UED);
}
//______________________________________________________________________________
nat32 UED_ETref_calculator::process_UED_to_UED
(UED::Database_file_indexed  &source_UED
,UED::Database_file_indexed  &target_UED)
{  nat32 processed = 0;

   const UED::Geolocation_record *source_geoloc = source_UED.get_geolocation_record_immutable();
   if (source_geoloc)
   {
      CORN::Date earliest_date(source_UED.get_earliest_date_time());
      CORN::Date latest_date  (source_UED.get_latest_date_time());
      Weather_UED_database source_weather_UED_database(&source_UED,false);
      //decided not to use   Weather_UED_database target_weather_UED_database(&target_UED,false);
      CORN::Date today(earliest_date);
      CS::Solar_irradiance_extraterrestrial_daily ET_solar_irriad(*source_geoloc,today);
      Weather_provider weather_provider(today,*source_geoloc,ET_solar_irriad,0);

      continue here, need day length hours

      ET_Reference_calculator ET_ref
         ((float32)source_geoloc->get_elevation()
         ,const float64 &_day_length_hours_today                                    //150627
         ,weather_provider);

      for (;today <= latest_date
           ;today.inc())
      {  // for each date in UED file
         UED::Time_query_single_date time_query(today.get_datetime64());

         source_weather_UED_database.get_to(weather_provider);
         weather_provider.update();
         ET_ref.update();
         processed += target_UED.set_parameter_on
            (weather_provider.ET_ref
            ,UED::STD_VC_ref_ET_Penman_Monteith.get()
            ,time_query
            ,UED::Record_type_distinguisher_interface::UED_data_set_year_var_units);
         /* Conceptual may provide option for ET model
         STD_VC_ref_ET_Priestly_Taylor
         STD_VC_ref_ET_Hargreaves
         STD_VC_ref_ET_ASCE_EWRI_short_crop
         STD_VC_ref_ET_ASCE_EWRI_tall_crop
         */
         /*151221 decided to use set_parameter_on
         target_weather_UED_database.set_pot_evapotranspiration_mm
               (today,weawther_provider.ETref.get_mm());          //991109
         */
         }
   } else
   {
      std::cerr << "Error: UED file has no geolocation (required)" << std::endl;
      processed = 0;
   }
   return processed;
}
//______________________________________________________________________________
nat32 UED_ETref_calculator::process_UED_files()
{
   nat32 processed = 0;
   recursively list UED files is source directory
   CORN::Unidirectional_list UED_filenames;
   CORN::OS::file_system_engine.list_file_names
      (REACCH_database_weather
      ,UED_filenames
      ,CORN::OS::File_system::subdirectory_recursion_inclusive
      ,CORN::OS::Directory_entry_name::relative_partial_qualification
      ,0
      ,L"UED");
   FOR_EACH_IN(source_UED_filename,CORN::OS::File_name,UED_filenames,each_UED)
   {
      if (target_directory)
      {  Database_file_indexed  target_UED = &source_UED;
         std::wstring *target_UED_filename_wstring =
            source_UED_filename->render_relative_to (target_directory,CORN::OS::relative_strict_qualification)
         if (target_UED_filename_wstring)
         {
            CORN::OS::File_name_concrete target_UED_filename
               (*target_UED_filename_wstring); delete target_UED_filename_wstring;
            processed += process_UED_file_to_UED_file
               (*source_UED_filename,target_UED_filename) != 0;
         }
      }
      else
      {  processed += process_UED_file(*source_UED_filename) != 0;
      }
   } FOR_EACH_END(each_UED)
   return processed;
}
//______________________________________________________________________________
#endif
//______________________________________________________________________________
bool add_ETref_to_UED
(UED::Database_file_indexed &source_UED_file
,UED::Database_file_indexed &target_UED_file)
{
   bool added = false;
      const UED::Geolocation_record *geoloc = source_UED_file.get_geolocation_record_immutable();
      if (geoloc)
      {
         CS::ETref_Injector_UED injector
            (&source_UED_file
            ,*geoloc
            ,&target_UED_file
            // the calculated value is put back in the source file.
            // process all dates encountered in the file
            );
         added = injector.process();
      } else
      {
         std::cerr
            << "error: unable to inject ETref, UED file is missing geolocation:";
      }
   return added;
}
//______________________________________________________________________________
bool add_ETref_to_named_UED
(const CORN::OS::File_name &source_filename
,const CORN::OS::File_name &target_filename
, bool copy_source_file_if_no_preexisting_target
)
{  bool added = false;
   UED::Database_file_indexed source_UED_file
      (source_filename.c_str(),std::ios::in |std::ios::out,false);

   if (source_filename.compare(target_filename) == std::string::npos)
   {  // target output back into the source file
      added = add_ETref_to_UED(source_UED_file,source_UED_file);
   }
   else
   {  // put the output an a separate target file.
      //not needed because copy_file checks existance if (copy_source_file_if_no_preexisting_target
      //    && !CORN::OS::file_system_engine.exists(target_filename))
      bool donot_overwrite_existing_target = copy_source_file_if_no_preexisting_target;
      CORN::OS::file_system_engine.copy_file
         (source_filename,target_filename,donot_overwrite_existing_target);
      UED::Database_file_indexed target_UED_file
         (target_filename.c_str(),std::ios::in | std::ios::out,false);
      added = add_ETref_to_UED(source_UED_file,target_UED_file);
   }
   if (!added)
      std::cerr << source_filename.c_str() << std::endl;
   return added;
}
//______________________________________________________________________________
nat32 add_ETref_to_REACCH2_weather
(const CORN::OS::Directory_name &source_database_weather_directory
,const CORN::OS::Directory_name *target_database_weather_directory_optional
, bool copy_source_file_if_no_preexisting_target
)
{
   nat32 UED_files_processed = 0;
   CORN::Unidirectional_list source_UED_filenames;
   CORN::OS::file_system_engine.list_file_names_deprecated
      (source_database_weather_directory
      ,source_UED_filenames
      ,CORN::OS::File_system::subdirectory_recursion_inclusive
      ,CORN::OS::Directory_entry_name::full_qualification
      ,0
      ,L"*.UED");
   FOR_EACH_IN(source_UED_filename,CORN::OS::File_name,source_UED_filenames,each_UED)
   {
      if (target_database_weather_directory_optional)
      {
         std::wstring name_with_extension;
         source_UED_filename->get_name_with_extension(name_with_extension);
         CORN::OS::File_name_concrete target_UED_filename
            (*target_database_weather_directory_optional,name_with_extension);
         UED_files_processed = add_ETref_to_named_UED
            (*source_UED_filename,target_UED_filename
            ,copy_source_file_if_no_preexisting_target);
      } else
      {
         UED_files_processed = add_ETref_to_named_UED(*source_UED_filename,*source_UED_filename,false);
      }

   } FOR_EACH_END(each_UED)
   return UED_files_processed;
}
//______________________________________________________________________________

int main(int argc, char *argv[])
{
   // This program calculates ETref for all specified dates
   //    in UED files found in the current directory and subdirectories
   //    Calculates ETref (Penman-Monteith if data is available)
   //    Adds ETref records to a UED file.
   //    If a target directory is specified, the ETref value are written
   //    to a matching file in the target directory.
   //    Outputs quality files in target directory where data is not available.

   // Options:
   //    source UED file name (Default is all found UED files)
   //    target directory (Default is to update source UED file)

   // Conceptual options
   //    Specify the dates to include (rather than everything).
   //    Specify ETref model (or best).
   //    Instead of populating UED file, either output
   //       to stdout (UED name, date (YYYYDDD), ET_ref (mm))
   //       to text (.dat) file(s)

   CORN::OS::Directory_name_concrete CWD;

}
//______________________________________________________________________________
