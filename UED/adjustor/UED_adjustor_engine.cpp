#include "UED_adjustor_engine.h"
#include "corn/OS/file_system_engine.h"
#include "UED/library/database_file.h"
#include "c:/CS_Suite_4/UED/simple/DLL/UED_codes.h"
#include "corn/seclusion.h"
#include <fstream>
#include <windows.h>
#include <iomanip.h>
namespace UED {
//______________________________________________________________________________
Adjustor_engine::Adjustor_engine()
: interpolations()
{}
//______________________________________________________________________________
nat32 Adjustor_engine::load_adjustments
(const CORN::OS::File_name     &adjustment_file_name
,CORN::Interpolation_curve_type curve_type
,Adjustment_mode                adjustment_mode)
{  float32 adjustments = 0;
   UED::Variable_code var_code = 0;
   std::string var_code_str;
   CORN::wstring_to_string(adjustment_file_name.get_name(),var_code_str); // The filename specifies the variable

   bool special_CAMO = adjustment_file_name.has_extension_ASCII("csv");

   if (special_CAMO)
   {
      // This is special quick and dirty for CAMO project
      var_code = UED_STD_VC_Srad_total;
   }
   else
   {

   if      (var_code_str == "tmax")  var_code = UED_STD_VC_Tmax;
   else if (var_code_str == "tmin")  var_code = UED_STD_VC_Tmin;
   else if (var_code_str == "srad")  var_code =
      #if (CS_VERSION >= 5)
      UED_STD_VC_Srad_total
      #else
      UED_STD_VC_Srad_ERRONEOUS
      #endif
      ;
   else if (var_code_str == "precip")var_code = UED_STD_VC_precip;
   else if (var_code_str == "rhmax") var_code = UED_STD_VC_RHmax;
   else if (var_code_str == "rhmin") var_code = UED_STD_VC_RHmin;
   else if (var_code_str == "dpmax") var_code = UED_STD_VC_Tdewmax;
   else if (var_code_str == "dpmin") var_code = UED_STD_VC_Tdewmin;
   else if (var_code_str == "ws")    var_code = UED_STD_VC_ws;
   else
   {  // raw var code is entered in hexidecimal
      var_code = CORN::cstr_to_nat32(var_code_str.c_str(),16);
   }
   }
   Interpolator *interpolator = dynamic_cast<Interpolator *>
      (interpolations.find(var_code));
   if (!interpolator) // (!interpolation)
   {
      interpolator = new Interpolator
      (curve_type,var_code,adjustment_mode);
      interpolations.append(interpolator);
   }

/*180426 renamed to Interpolator
   Interpolation *interpolation = dynamic_cast<Interpolation *>
      (interpolations.find(var_code));
   if (!interpolation)
   {
      interpolation = new Interpolation
      (curve_type,var_code,adjustment_mode);
      interpolations.append(interpolation);
   }
*/

   std::ifstream adjustment_file(adjustment_file_name.c_str());
   int32    date;
   float32  adjustment;
   if (special_CAMO)
   {
      /* The file has the format (as prepared with R)
      "Period","Ratio"
      */
      std::string unused_header;
      std::getline(adjustment_file,unused_header);
   }
   while (!adjustment_file.eof())
   {
      if (special_CAMO)
      {
         /* Detail lines have the format
         "2021001",0.969298346304244
         */
         char unused_char;
         adjustment_file.get(unused_char); // "
         adjustment_file>> date;
std::clog << date << '\r';
         adjustment_file.get(unused_char); // "
         adjustment_file.get(unused_char); // ,
         adjustment_file>> adjustment;
         adjustment_file.get(unused_char); // new line

      }
      else
         adjustment_file >> date >> adjustment;
      CORN::Date_32_clad obs_date(date);
      interpolator /*ion*/->set_by_date(obs_date, adjustment);
      adjustments++;
   }
   return adjustments;
}
//_2015-03-08_________________________________Adjustor_engine::load_adjustments/
bool Adjustor_engine::adjust_file
(const CORN::OS::File_name_concrete &source_file
,const CORN::OS::File_name_concrete &target_file)
{  bool adjusted = CORN::OS::file_system_engine.copy_file(source_file,target_file,false);
   Sleep(100); // sleep to wait for copy to complete
   Database_file_indexed target(target_file.c_str(),(std::ios_base::in | std::ios_base::out),false);

   CORN::datetime64 earliest_datetime64 = target.get_earliest_date_time();
   //150310 earliest_date_in_UED.set_datetime64(earliest_datetime64);

   std::clog << "adjusting: source=" << source_file << " target="<<target_file.c_str() << std::endl;
   for (Binary_data_record_cowl *data_rec = target.goto_next_data_record()
       ;data_rec
       ;data_rec = target.goto_next_data_record())
   {
      //180426 Interpolation *interpolation = dynamic_cast<Interpolation *>(interpolations.find(data_rec->get_variable_code()));
      Interpolator *interpolation = dynamic_cast<Interpolator *>(interpolations.find(data_rec->get_variable_code()));
         // rename to interpolator 180426
      if (interpolation && interpolation->adjustment_mode)
      {
         //150310 interpolation->set_reference_date(earliest_date_in_UED);
         CORN::datetime64 earliest_date_time_in_rec =  9999365;
         CORN::datetime64 latest_date_time_in_rec   = -9999365;

         CORN::Date_32_clad earliest(data_rec->get_earliest_date_time(earliest_date_time_in_rec));
         CORN::Date_32_clad latest  (data_rec->get_latest_date_time  (latest_date_time_in_rec));
         std::clog << "variable code:"  << std::hex << interpolation->var_code << "\t" << earliest.as_string() << "-" << latest.as_string() << std::endl;

         for (CORN::Date_32_clad date(earliest)
             ;date <= latest
             ;date.inc_day())
         {
            CORN::Quality_clad quality;
            CORN::datetime64 date_as_64 = date.get_datetime64();
            float32 unadjusted_value = data_rec->get_value(quality,date_as_64);
            float32 adjusted_value = unadjusted_value;
            float32 adjustment = interpolation->get_ordinate_by_date(date);
            switch ( interpolation->adjustment_mode)
            {
               case SCALE_ADJUSTMENT :
                  adjusted_value *= adjustment;
               break;
               case DELTA_ADJUSTMENT :
                  // Don't adjust 0 value (I.e. only adjust precipitation there is a value).
                  if (!CORN::is_approximately<float32>(adjusted_value,0.0,0.0000001))
                     adjusted_value += adjustment;
               break;
            } // adjustment mode
            quality.assume_code(CORN::forecasted_quality);
            data_rec->set_value(adjusted_value,quality,date_as_64,true);
         }// for each date in data rec
         adjusted = true;
      } // else no interpolation so do nothing, variable is not adjusted
   } // for data record
   return adjusted;
}
//_2015-03-08______________________________________Adjustor_engine::adjust_file/
nat32 Adjustor_engine::adjust_directory
(const CORN::OS::Directory_name_concrete &source_directory
,const CORN::OS::Directory_name_concrete &target_directory)
{
   CORN::OS::file_system_engine.provide_directory(target_directory);
   nat32 adjusted_files = 0;
   CORN::Unidirectional_list source_files;
   CORN::Unidirectional_list source_dirs;
   nat32 encountered_entries = CORN::OS::file_system_engine
      .list_DENs
      (source_directory
      ,&source_files,&source_dirs
      ,CORN::Inclusion("*",true)
      ,CORN::OS::File_system::none_recursion_inclusive);

      /* 180808
      .list_entry_names
      (source_directory
      ,&source_files,&source_dirs
      ,CORN::OS::File_system::none_recursion_inclusive                           //150909
      ,CORN::OS::Directory_entry_name::full_qualification                        //150909
      );
      */
      // not recurse_subdirectories
      // name_wild_card      = 0
      // extension_filter    = 0

   FOR_EACH_IN(source_file,CORN::OS::File_name,source_files,each_file)
   {  if (source_file->has_extension_ASCII("UED",false))
      {  CORN::OS::File_name_concrete target_UED(target_directory,source_file->get_name(),"UED");
         adjusted_files += adjust_file(*source_file,target_UED);
      }
   } FOR_EACH_END(each_file)

   FOR_EACH_IN(source_subdir,CORN::OS::Directory_name,source_dirs,each_dir)
   {  CORN::OS::Directory_name_concrete target_subdir(target_directory,source_subdir->get_name(),"",CORN::OS::directory_entry);
      adjusted_files += adjust_directory(*source_subdir,target_subdir);
   } FOR_EACH_END(each_dir)
   return adjusted_files;
}
//_2015-03-08_____________________________Adjustor_engine::conadjust_directory_/
} // namespace UED
