#include "UED/convert/convert_response.h"
#include "corn/OS/file_system_engine.h"
namespace UED {                                                                  //171120
//______________________________________________________________________________
Convertor_arguments::Convertor_arguments()
: CORN::Arguments()
,UED_filename           ("")
,target_filename        ("")
,format_filename        ("")
,UED_filenames          ()
,calculate_daily        (true)
,location_info_imported (false)
,use_station_name       (false)
,format                 ("")
,subformat              ("")
,units_system           ("intrinsic")
,year_earliest          (0)
,year_latest            (9999)
,date_time_earliest     (0.0)
,date_time_latest       (9999365.999999)
,offset_years           (0)
,prefix                 ("")
,vapor_pressure_calculation(0)
,net_radiation_option   (0)
,geolocation_is_provided_by_caller(false)
,geolocation()
,allow_16bit_floats_in_UED(false)                                                //150307
{
   set_current_section("convert");                                               //170328
}
//______________________________________________________________________________
bool Convertor_arguments::expect_structure(bool for_write)
{
   bool expected = CORN::Data_record::expect_structure(for_write);
   expect_string  ("command"           ,operation,255);   // deprecated
      // This was used by CS_explorer V4
   expect_string  ("operation"         ,operation,255);
   expect_file_name("UED_filename"     ,UED_filename);        // Used mainly (only?) for export (on import there could be multiple stations (each generating their own UED file)
   expect_string  ("UED_filenames"     ,UED_filenames,2048);
   expect_file_name("target_filename"  ,target_filename);        // Target filename (text file)
   expect_string  ("station_ID_filter" ,station_IDs_filter,1024);
   expect_file_name("format_filename"  ,format_filename);     // I.e. TDF file
   expect_string  ("format"            ,format,255);
   expect_string  ("subformat"         ,subformat,255);
   expect_string  ("units_system"      ,units_system,20);
   set_current_section("years");
      expect_int16   ("earliest"          ,year_earliest);
      expect_int16   ("latest"            ,year_latest);
      expect_int16   ("offset"            ,offset_years);
   set_current_section("date_times");
      expect_float64 ("earliest"          ,date_time_earliest);
      expect_float64 ("latest"            ,date_time_latest);
   set_current_section("import");
      expect_bool    ("calculate_daily"   ,calculate_daily);
      expect_bool    ("use_station_name"  ,use_station_name);
   set_current_section("export");
      expect_string("prefix",prefix,255);
      expect_bool    ("allow_16bit_floats",allow_16bit_floats_in_UED);           //150307
   set_current_section("status");
      expect_bool    ("location_info_imported",location_info_imported);
   set_current_section("DYRESM");
      expect_int16("vapor_pressure_calculation",vapor_pressure_calculation);
      expect_int16("net_radiation_option",net_radiation_option);
   if (!for_write || (for_write && geolocation_is_provided_by_caller))
   {
      set_current_section("geolocation");
      /*NYI structure_defined &= */geolocation.setup_structure(*this,for_write);
   }
   set_current_section("convert");                                               //171120
   structure_defined = true;                                                     //120314
   return expected;                                                              //161103
}
//_1998-04-05___________________________________________________________________
bool Convertor_arguments::recognize
(const std::string &paramstring)                                   modification_
{  bool recognized = false;
   // This is an optional mode command line option where the
   // command can be simply specified on the command line instead of command=XXX.
   // This is provided for old export import/export utilities that used this form
   if (paramstring == "import")
   {  operation = paramstring;                                                   //171120
      recognized = true;
   } else if (paramstring=="export")
   {  operation = paramstring;                                                   //171120
      recognized = true;
   }
   return recognized || CORN::Arguments::recognize(paramstring);
}
//_2017-11-20__2017-03-28______________________Convertor::Arguments::recognize_/
/*180213
bool Convertor_arguments::recognize_DEN
(const CORN::OS::Directory_entry_name &param_DEN)                  modification_
{  bool recognized = false;
      // May need to process CORN::Arguments first because
      // need any reponse files processes first
      // (otherwise the EXE filename case will consume the param_DEN//
   if ( (param_DEN.has_extension(L"UED"))
      ||(param_DEN.has_extension(L"ued"))) // currently accepting lower case
   {  UED_filename.set_DEN(param_DEN);
      if (operation.length() == 0) operation = "export";
      else operation = "import";
      recognized = true;
   } else
   if ( param_DEN.has_extension(L"TDF"))
   {  format_filename.set_DEN(param_DEN);
      recognized = true;
   } else
   {
      std::wstring param_name(param_DEN.get_name());                              //170725
      if ((param_name.find('[') != std::string::npos) || (param_name.find('=')!= std::string::npos))                          //170725
      {  // most likely VV entry not a filename
         recognized = false;                                                     //170725
      }
      else                                                                       //170725
      {

// This case should no longer be needed

         // There was a problem in the logic only applicable to when not arg 0.

         if (  !param_DEN.has_extension(L"rsp")                                  //171110
             &&!param_DEN.has_extension(L"RSP"))                                 //171110
         {
            target_filename.set_DEN(param_DEN);
            recognized = true;
         }
      }
   }
   return recognized || CORN::Arguments::recognize_DEN(param_DEN);
}
//_2017-06-16___________________________________________________________________
*/
bool Convertor_arguments::submit_DEN
(CORN::OS::Directory_entry_name *param_DEN)                          submission_
{  bool recognized = false;
      // May need to process CORN::Arguments first because
      // need any reponse files processes first
      // (otherwise the EXE filename case will consume the param_DEN//
   if ( (param_DEN->has_extension(L"UED"))
      ||(param_DEN->has_extension(L"ued"))) // currently accepting lower case
   {
      UED_filename.set_DEN(*param_DEN);
      if (operation.length() == 0) operation = "export";
      else operation = "import";
      delete param_DEN;
      recognized = true;
   } else
   if ( param_DEN->has_extension(L"TDF"))
   {  format_filename.set_DEN(*param_DEN);
      delete param_DEN;
      recognized = true;
   } else
   {
      std::wstring param_name(param_DEN->get_name());                            //170725
      if ((param_name.find('[') != std::string::npos) || (param_name.find('=')!= std::string::npos))                          //170725
      {  // most likely VV entry not a filename
         recognized = false;                                                     //170725
         delete param_DEN;
         return false;                                                           //180309
      }
      else                                                                       //170725
      {

// This case should no longer be needed

         // There was a problem in the logic only applicable to when not arg 0.

         if (  !param_DEN->has_extension(L"rsp")                                  //171110
             &&!param_DEN->has_extension(L"RSP"))                                 //171110
         {
            target_filename.set_DEN(*param_DEN);
            delete param_DEN;
            recognized = true;
         }
      }
   }
   return recognized || CORN::Arguments::submit_DEN(param_DEN);
}
//_2018-02-13___________________________________________________________________



bool Convertor_arguments/*171120 Convert_response_data_record*/::get_end()
{  if (date_time_earliest == 0)
       date_time_earliest = 1;
   return CORN::Arguments::get_end();
}
//_2017-06-16___________________________________________________________________
} // namespace UED                                                               //171120

