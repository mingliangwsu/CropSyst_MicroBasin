#include "UED/convert/convertor.h"
#include "corn/container/SDF_list.h"
#include "corn/container/text_list.h"
#include "corn/data_source/vv_file.h"
#include "corn/OS/file_system_engine.h"
#include "UED/library/timeqry.h"
#include "UED/library/database_file.h"
#include "corn/chronometry/date_const.hpp"

#ifdef _Windows
#include <conio.h>
// for getch
#endif
using namespace std;
//______________________________________________________________________________
namespace UED {                                                                  //140523
//_2012-04-15___________________________________________________________________
Convertor::Convertor
(Convertor_arguments &arguments_)                                                //171120
: arguments(arguments_)                                                          //170328
, parameters(arguments) // temporary alias
,this_programs_ini(0)
,ued_file_path()
,press_return_before_exit(false)
, response_file_or_command_line_specified_geolocation_parameters(false)          //090306
, UED_file(0)                                                                    //140527
, target_file_extension("dat")                                                   //151229_140627
{
/*180629
   CORN::date_setup_phrases();                                                   //070118
*/
}
//______________________________________________________________________________
bool Convertor::setup_from_command_line()                          modification_ //170328
{  bool command_line_setups_complete
      = true;
   //  Now empty target name means cout  141019
    // ued_file_path will be the same as the UED file
    // if it is not specified (for import) then it will be the
    // same directory as the target.
   nat16 ued_filename_length    =  parameters.UED_filename.length();             //151212
   bool  ued_filename_qualified
      = ued_filename_length && parameters.UED_filename.is_qualified();           //151212
   ued_file_path = ued_filename_qualified                                        //151212
      ? new CORN::OS::Directory_name_concrete
       (ued_filename_length
         ? parameters.UED_filename.get_parent_directory_name_qualified()
         : parameters.target_filename.get_parent_directory_name_qualified())
      : new CORN::OS::Directory_name_concrete; // CWD                            //151212
   if (arguments.is_import_mode() && !ued_filename_qualified)                    //151212
   {  // If the UED file was not specified, presume it is in the same as the target filename
      // (This can be the case where UED file is optional on import)
      CORN::OS::File_name_concrete assumed_UED_filename
         (*ued_file_path
         ,parameters.target_filename.get_name()
         ,L"UED");
      parameters.UED_filename.set_DEN(assumed_UED_filename);
   }
   return command_line_setups_complete;
}
//_2006-10-18_________________________________________setup_from_command_line__/
Convertor::~Convertor()
{
   delete this_programs_ini;
   delete ued_file_path;
   delete UED_file;                                                              //171110
}
//_2009-08-21______________________________________________________destructor__/
int Convertor::convert()
{
   setup_from_command_line();                                                    //170328
   int result = arguments.is_import_mode()                                       //171120
   ? perform_import()
   : perform_export();
#ifdef NYI
currently only done by Text_dBase_Excel_with_TDF_convertor
but it would be nice to generalize
   if (perform_import && parameters.calculate_daily)
      calculate_daily_values();
#endif
   if (press_return_before_exit)
   {  cout << "Press [Return] key or click [X] close button." << endl;
      #ifdef _Windows
      getch();
      #endif
   }
   return result;
}
//______________________________________________________________________________
bool Convertor::import_detail_line
(const std::string &detail_line)                                   modification_
{  bool imported_line =  detail_line.length();
   if (imported_line)
   {
         // I.e. 458	Eston - Hayfields	01-JAN-2014	0.0	28.4	14.4	26.9	82	55	205.1
         // or   458,Eston - Hayfields,02-JAN-2014,0.0,28.3,17.2,21.3,64,53,215.9,
      CORN::Text_list element_values(detail_line.c_str(),comma_delimited ? ',' : '\t');
      imported_line = element_values.count();
      FOR_EACH_IN(column,UED::Column_elements::Column,column_elements,each_element)
      {
         Item_string *value
         = dynamic_cast<Item_string *>
            (element_values.pop_at_head());
         if (value)
            imported_line &= import_detail_element(*column,*value);
         // else we reached the end of the detail line
         // normally shouldn't occur unless the CSV or TSV file format
            // allows truncated lines with empty values to be trimmed.
      } FOR_EACH_END(each_element)
      FOR_EACH_IN(column,UED::Column_elements::Column,column_elements,each_element)
      {  imported_line &= import_commit_detail_element(*column);
         // else we reached the end of the detail line
         // normally shouldn't occur unless the CSV or TSV file format
            // allows truncated lines with empty values to be trimmed.
      } FOR_EACH_END(each_element)
   }
   return imported_line;
}
//_2014-05-23__________________________________________________________________/
bool Convertor::import_detail_element
(const Column_elements::Column &column
,const std::string &value_string)
{  bool imported_line = true;
   const Column_elements::Element *element
      = dynamic_cast <const Column_elements::Element *>(&column);
   if (element)
   {  float64 value = atof(value_string.c_str());
      element->parameter.force_amount(value);                                     //150130_140627
   } else imported_line = false;
   return imported_line;
}
//_2014-05-23__________________________________________________________________/
nat32 Convertor::import_records
(istream &detail_line_stream)                                      modification_
{  std::string detail_line;
   nat32 record_count = 0;
   bool detail_line_has_data;
   do
   {  getline(detail_line_stream,detail_line);
      detail_line_has_data =  import_detail_line(detail_line);
      record_count += detail_line_has_data;
   } while (detail_line_has_data); // detail line will be read as emtpy at EOF
   return record_count;
}
//_2014-05-23__________________________________________________________________/
bool Convertor::import_commit_detail_element
(const UED::Column_elements::Column &column)
{  bool committed_element = true;
   const UED::Column_elements::Element *element
      = dynamic_cast <const UED::Column_elements::Element *>(&column);
   if (element)
   {  CORN::datetime64 detail_line_datetime = get_detail_line_datetime();        //140606
      CORN::Date_clad_32 validation_date(detail_line_datetime);                  //140606
      UED::Time_query_single_date set_time_query(detail_line_datetime);          //140606
      CORN::Units_code        value_units(element->parameter.get_units());
      CORN::Quality_clad value_quality(measured_quality);
      CORN::Quality_clad  identified_quality(value_quality);
      bool                    record_created;
      float32 validated_amount
         = get_valid_element_amount(element,identified_quality);                 //151229
      UED_file->set_value
         (validated_amount
         ,set_time_query
         ,value_units
         ,identified_quality                                                     //151229
         ,element->creation_layout
         ,record_created
         ,true );
   }
   // else it is probably metadata so ignore
   return committed_element;
}
//_2014-05-23__________________________________________________________________/
float32 Convertor::get_valid_element_amount
(const UED::Column_elements::Element *element
,CORN::Quality_clad &identified_quality)                               const
{  return (float32) element->parameter.in_prescribed_units();
}
//_2015-12-29___________________________________________________________________
UED::Database_file_indexed *Convertor::provide_UED_file()             provision_
{  if (!UED_file)
   {  UED_file = new UED::Database_file_indexed
         (parameters.UED_filename.c_str()
         ,arguments.is_import_mode()                                             //171120
         ? std::ios_base::in|std::ios_base::out                                  //180312
         //180312 ? std::ios_base::out
         : std::ios_base::in,false);
   }
   return UED_file;
}
//_2016-02-14___________________________________________________________________
} // namespace UED

