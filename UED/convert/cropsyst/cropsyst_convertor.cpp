#include "UED/convert/cropsyst/cropsyst_convertor.h"
#include "corn/data_source/vv_file.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system_engine.h"
#include "common/weather/database/weather_UED_database.h"
#include "corn/chronometry/date_const.hpp"
#include "common/weather/weather_provider.h"
#include "common/solar/irradiance_extraterrestrial.h"
#include "corn/seclusion.h"
//______________________________________________________________________________
CropSyst_text_convertor::CropSyst_text_convertor
      (UED::Convertor_arguments/*180101 CropSyst_text_convertor::Arguments*/ &arguments)                            //170725
: UED::Convertor_weather(arguments)                                              //170725
, loc_params ("",true,4,0,0)
{
   bool read_mode_of_UED_file = parameters.operation != "import";
   if (CORN::OS::file_system_engine.exists(parameters.target_filename))
   {  // import now selects .LOC file
      CORN::VV_File loc_file(parameters.target_filename.c_str());
      loc_file.get(loc_params);
   }
}
//______________________________________________________________________________
void CropSyst_text_convertor::transfer
(Weather_database &from_database
,Weather_database &to_database
,Year                start_year
,Year                end_year
,bool                export_more
,Weather_text_file::Format_old  export_format)
{
   CORN::Date_clad_32 starting_date(start_year,1);
   CORN::Date_clad_32 ending_date(end_year,CORN::date_days_in_year(end_year));
   bool exporting_V4_text_format = false;
   if (export_more)
   {  to_database.set_preferred_ext("gen");
      exporting_V4_text_format = export_format == Weather_text_file::V4_format;  //060221
   }
   int last_year = 0;
   CORN::Date_clad_32 today;                                                     //170111
   Geocoordinate geocoordinate_unused;                                           //170111
   CS::Solar_irradiance_extraterrestrial_daily unused_ETrad(geocoordinate_unused,today); //170111
   Weather_provider provider(today,geocoordinate_unused,unused_ETrad,0);         //170111
   CORN::Date_clad_32 earliest_date(from_database.get_earliest_available_date());//170111
   if (earliest_date < starting_date)                                            //170111
      starting_date.set(earliest_date);
   bool got = true;
   for (today.set(starting_date)  ;got  ;today.inc_day())
   {
      if (today.get_year() != last_year)
         std::cout << last_year << '\r';
      last_year = today.get_year();
      got = from_database.get_to(provider);                                            //170111
      if (got)
         to_database.set_from(provider);                                            //170111
   }
}
//______________________________________________________________________________
nat32 CropSyst_text_convertor::perform_import()
{
   //from the location params get the template dat filename
   //look for all years matching.
   //get the min and the max  year
   // The UED filename will be the same as the target file                       //060621

   // Note that the parameters.ued_filename may have been assigned the target output directory by the import Wizard.
   // when we invoke the import wizard from the CropSyst weather database editor //070713
   CORN::OS::File_name_concrete new_UED_filename(parameters.target_filename,L"UED"); //170111
   parameters.UED_filename.set_DEN(new_UED_filename);                            //170111
   Weather_UED_database ued_database
      (parameters.UED_filename.c_str(),std::ios_base::out);

   Weather_data_text dat_database (loc_params,loc_params.weather_filename_V3);
   // Originally the .DAT file selection was in the entry "weather_filename"
   GEN_DAT_UED_filename template_DAT_filename(loc_params.weather_filename_V3.c_str()); //060616
   // Later it was changed to "database"
   // But database could also have been a UED file,  (this utility only imports the .DAT or .GEN files).
   if (!template_DAT_filename.length() &&
       (   loc_params.database_filename.has_extension_ASCII("DAT",true)
        || loc_params.database_filename.has_extension_ASCII("GEN",true)))
      template_DAT_filename.set_DEN(loc_params.database_filename);
   const CORN::OS::Directory_name &weather_dir                                   //170111
      = template_DAT_filename.get_parent_directory_name_qualified();
   std::wstring template_prefix; template_DAT_filename .get_prefix(template_prefix);
   CORN::Unidirectional_list dat_files;
   CORN::Inclusion CS_text_weather_ext("dat",true);
   CS_text_weather_ext.include_pattern_cstr("gen");
   CORN::OS::file_system_engine.list_DENs                                        //170111
      (weather_dir
      ,&dat_files,0,CS_text_weather_ext,CORN::OS::File_system::none_recursion_inclusive);
   Year min_year=9999;
   Year max_year=0;
   FOR_EACH_IN(dat_file,CORN::OS::Directory_entry_name,dat_files,each_dat_file)
   {  GEN_DAT_UED_filename dat_filename(dat_file->c_str());
      std::wstring file_name_prefix;
      if (template_prefix == dat_filename.get_prefix(file_name_prefix))
      {  Year year = dat_filename.get_year();
         min_year = std::min<Year>(min_year,year);
         max_year = std::max<Year>(max_year,year);
      }
   } FOR_EACH_END(each_dat_file)
      // Limit period to user selection, but also to data available
   min_year = std::max<Year>(parameters.year_earliest,min_year);
   max_year   = (max_year)
   ? std::min<Year>(parameters.year_latest,max_year)
   : parameters.year_latest;
   UED::Geolocation_record  *geoloc_rec = const_cast<UED::Geolocation_record  *>(ued_database.get_geolocation_record_immutable()); //110822
   if (!geoloc_rec)
   {   geoloc_rec = new UED::Geolocation_record
            (*(loc_params.geolocation));  // loc_params is guarenteed to have geolocation
          ued_database.take_geolocation_information(geoloc_rec);
   // don't delete geoloc_rec it is relinquished to ued_database;
   }
   else
   {
   // could  update with location file information
   // shouldn't really need to do this because we are probably creating the UED
   // since this is an old format.
   }
   transfer(dat_database,ued_database,min_year,max_year,false,Weather_text_file::UNKNOWN_format);
   return 1;
}
//______________________________________________________________________________
uint32 CropSyst_text_convertor::perform_export()
{
   std::string export_format_code(parameters.subformat);
   Weather_text_file::Format_old  export_format = Weather_text_file::V4_format;
   if (     export_format_code == "DPT")     export_format = Weather_text_file::day_precip_temp;
   else if (export_format_code == "DPTR")    export_format = Weather_text_file::day_precip_temp_rad;
   else if (export_format_code == "DPTRDW")  export_format = Weather_text_file::day_precip_temp_rad_dewpoint_wind;
   else if (export_format_code == "DPTRHW")  export_format = Weather_text_file::day_precip_temp_rad_humid_wind;
   Weather_UED_database ued_database
      (parameters.UED_filename.c_str(),std::ios_base::in,CORN::measured_quality);
   std::string prefix(parameters.prefix);                                        //170111_060328
   std::string template_filename(prefix);                                        //170111
   if (export_format ==  Weather_text_file::V4_format)                           //060221
         template_filename.append(".gen");                                       //060221
   else
         template_filename.append("2000.gen");
   loc_params.weather_filename_V3.set_str(template_filename);                    //170111
   const CORN::OS::Directory_name &target_dir = arguments.start_directory;       //170111
   CORN::OS::File_name_concrete new_weather_filename_V3                          //170111
      (target_dir,template_filename);
   loc_params.weather_filename_V3.set_DEN(new_weather_filename_V3);              //170111
      UED::Geolocation_record  *geoloc_rec = const_cast<UED::Geolocation_record  *>(ued_database.get_geolocation_record_immutable()); //110822
      if (geoloc_rec)
      {  // replace location geolocation with a new copy from UED
         delete loc_params.geolocation;
         loc_params.geolocation = new Geolocation(*geoloc_rec);
      }
      // create a location filename with the same name as ued file with .loc extension
      CORN::OS::File_name_concrete target_filename
         (parameters.target_filename.length() // if target specified in the response file (usually the case)
            ? parameters.target_filename.w_str()
            : parameters.UED_filename.w_str() // else just use the UED filename and append the .loc extension (this is what the export wizard does)
         );
      std::wstring loc_filename_unqual(target_filename.get_name());              //170725
      loc_filename_unqual.append(L".loc");                                       //170725
      CORN::OS::File_name_concrete loc_filename
         (target_dir,loc_filename_unqual);                                       //170725
      {  VV_File loc_file(loc_filename.c_str());
         loc_file.set(loc_params);
      }
   Weather_data_text dat_database (loc_params,target_filename/*171012 loc_params.weather_filename_V3*/);
   dat_database.setup_to_write(export_format);                                   //021212
   CORN::Date_time_clad_64 earliest_date_time(ued_database.get_earliest_date_time());//030729
   CORN::Date_time_clad_64 latest_date_time(ued_database.get_latest_date_time());//030729
   Year earliest_year = earliest_date_time.get_year();
   Year latest_year   =   latest_date_time.get_year();
   // Limit period to user selection, but also to data available
   earliest_year = std::max<Year>(parameters.year_earliest,earliest_year);
   latest_year   = std::min<Year>(parameters.year_latest,latest_year);
   transfer(ued_database,dat_database,earliest_year,latest_year,true,export_format);
   return 1;
};
//______________________________________________________________________________

