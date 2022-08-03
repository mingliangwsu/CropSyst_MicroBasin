
#include "UED/library/marker.h"
#include "UED/library/controls.h"
#include "corn/format/binary/binary_file_interface.h"
#ifdef UED_DUMP
#include <stdlib.h>
#endif
#include <iomanip>
#include "corn/string/strconv.hpp"
namespace UED {
//______________________________________________________________________________
bool Marker_BOF_record::read_body(CORN::Binary_file_interface &parent_database)
{ database_version =parent_database.read_nat16(); return true;}
//_1997-11-03___________________________________________________________________
void Marker_BOF_record::write_body(CORN::Binary_file_interface &parent_database)
{ parent_database.write_nat16(database_version); }
//_1997-11-03___________________________________________________________________
bool Generating_application_record::read_body(CORN::Binary_file_interface &parent_database)
{ version = parent_database.read_nat16(); return Text_record::read_body(parent_database);}
//______________________________________________________________________________
void Generating_application_record::write_body(CORN::Binary_file_interface &parent_database)
{ parent_database.write_nat16(version); Text_record::write_body(parent_database);}
//______________________________________________________________________________
bool Text_record::read_body(CORN::Binary_file_interface&parent_database)
{  parent_database.read_string(text,CORN::ASCII_Z_string,(nat16)rec_length);    //100114
   return true;                                                                  //100128
}
//_1997-11-03___________________________________________________________________
void Text_record::write_body(CORN::Binary_file_interface &parent_database)
{  parent_database.write_string(text,CORN::ASCII_Z_string);                      //100114
}
//_1997-11-03___________________________________________________________________
Period_record::Period_record
(const char         *description_
,nat32               options_
,CORN::datetime64    start_date_time_
,CORN::datetime64    end_date_time_
,nat32               application_code_
,nat32               enumeration_
,nat32               index_
,UED_variable_code   variable_code_)
: Text_record     ((CORN::Record_code)(UED_period ),description_)
, options         (options_)
, start_date_time (start_date_time_)
, end_date_time   (end_date_time_)
, application_code(application_code_)
, enumeration     (enumeration_)
, index           (index_)
, variable_code   (variable_code_)
{}
//_________________________________________________________________constructor_/
Period_record::Period_record(const Period_record &from_copy)
: Text_record     (from_copy)
, options         (from_copy.options)
, start_date_time (from_copy.start_date_time)
, end_date_time   (from_copy.end_date_time)
, application_code(from_copy.application_code)
, enumeration     (from_copy.enumeration)
, index           (from_copy.index)
, variable_code   (from_copy.variable_code)                                      //041012
{}
//____________________________________________________________copy constructor_/
uint32 Period_record::compute_record_body_size() const
{  uint32 record_body_size = Text_record::compute_record_body_size();
   record_body_size += sizeof(options);
   record_body_size += (options & UED_period_start_date_time_option)    ? sizeof(start_date_time)  : 0;
   record_body_size += (options & UED_period_end_date_time_option)      ? sizeof(end_date_time)    : 0;
   record_body_size += (options & UED_period_application_code_option)   ? sizeof(application_code) : 0;
   record_body_size += (options & UED_period_enumeration_option)        ? sizeof(enumeration)      : 0;
   record_body_size += (options & UED_period_index_option)              ? sizeof(index)            : 0;
   record_body_size += (options & UED_period_variable_code_option)      ? sizeof(variable_code)    : 0;
   return record_body_size;
}
// Returns the size of the record body (not including the header).
//___________________________________________________compute_record_body_size__/
bool Period_record::read_body(CORN::Binary_file_interface &parent_database)
{  options =                                                              parent_database.read_nat32();
   if (options & UED_period_start_date_time_option)   start_date_time   = parent_database.read_float64();
   if (options & UED_period_end_date_time_option)     end_date_time     = parent_database.read_float64();
   if (options & UED_period_application_code_option)  application_code  = parent_database.read_nat32();
   if (options & UED_period_enumeration_option)       enumeration       = parent_database.read_nat32();
   if (options & UED_period_index_option)             index             = parent_database.read_nat32();
   if (options & UED_period_variable_code_option)     variable_code     = parent_database.read_nat32();
   return Text_record::read_body(parent_database);
}
//_2004-10-11_______________________________________________________read_body__/
void Period_record::write_body(CORN::Binary_file_interface &parent_database)
{  parent_database.write_nat32(options);
   if (options & UED_period_start_date_time_option)   parent_database.write_float64(start_date_time);
   if (options & UED_period_end_date_time_option)     parent_database.write_float64(end_date_time);
   if (options & UED_period_application_code_option)  parent_database.write_nat32(application_code);
   if (options & UED_period_enumeration_option)       parent_database.write_nat32(enumeration);
   if (options & UED_period_index_option)             parent_database.write_nat32(index);
   if (options & UED_period_variable_code_option)     parent_database.write_nat32(variable_code);
   Text_record::write_body(parent_database);
}
//_1997-11-03_______________________________________________________write_body_/
#ifdef UED_DUMP

using namespace std;
void Period_record::dumpX(std::ostream &txt_strm)
{  // Don't call Text_record::dump(txt_strm) here because the text is actually stored last
   Record_base::dumpX(txt_strm);
   char options_hex_str[60];
   char options_bin_str[60];
   //               CORN::Date start_date_time_DT(start_date_time);
   //               CORN::Date end_date_time_DT(end_date_time);
   txt_strm << CORN::nat32_to_cstr(options,options_hex_str,16) << 'h' << ' '
            << CORN::nat32_to_cstr(options,options_bin_str,2)  << 'b' << " options" << endl;
   txt_strm.precision(10);
   if ((options & UED_period_start_date_time_option) == UED_period_start_date_time_option)   txt_strm << start_date_time << "| start date.time" << endl;
   else if ((options & UED_period_start_time_option) == UED_period_start_time_option)        txt_strm << start_date_time << "| start time"      << endl;
   else if ((options & UED_period_start_date_option) == UED_period_start_date_option)        txt_strm << start_date_time << "| start date"      << endl;
   if ((options & UED_period_end_date_time_option) == UED_period_end_date_time_option)   txt_strm <<end_date_time << "| end date.time" << endl;
   else if ((options & UED_period_end_time_option) == UED_period_end_time_option)        txt_strm << end_date_time << "| end time"      << endl;
   else if ((options & UED_period_end_date_option) == UED_period_end_date_option)        txt_strm << end_date_time << "| end date"      << endl;
   if (options & UED_period_application_code_option)  txt_strm << application_code << "| application code" << endl;
   if (options & UED_period_enumeration_option)  txt_strm << enumeration << "| enumeration"<< endl;
   if (options & UED_period_index_option)  txt_strm << index << "| index"<< endl;
   if (options & UED_period_variable_code_option)  txt_strm << variable_code << "| variable code"<< endl;
   txt_strm << text << endl;
}
//_______________________________________________________________________dump__/
#endif

void Period_record::write_YAML(std::ostream &YAML_strm,nat16 indent_level)
{  // Don't call Text_record::dump(txt_strm) here because the text is actually stored last
   Record_base::write_YAML(YAML_strm,indent_level);
   std::string indent(indent_level,' ');
   //char options_hex_str[60]; options_hex_str[0] = 0;
   std::string options_hex_str;
   CORN::append_nat32_to_string(options,options_hex_str,16);
   //char options_bin_str[60];   CORN::nat32_to_cstr(options,options_bin_str,2);
   YAML_strm<<indent << "options: " << "0x" << options_hex_str << std::endl;
   YAML_strm.precision(10);
   if (   (options & UED_period_start_date_time_option)
       || (options & UED_period_start_time_option)
       || (options & UED_period_start_date_option))
      YAML_strm<<indent << "start:" << start_date_time << std::endl;
      // Conceptual may want to change the format of the date depending on the start option

   if (   (options & UED_period_end_date_time_option)
       || (options & UED_period_end_time_option)
       || (options & UED_period_end_date_option))
      YAML_strm<<indent << "stop:" << end_date_time << std::endl;
      // Conceptual may want to change the format of the date depending on the start option

   if (options & UED_period_application_code_option)
      YAML_strm<<indent << "application: " << application_code << std::endl;
   if (options & UED_period_enumeration_option)
      YAML_strm<<indent << "enumeration: " << enumeration<< std::endl;
   if (options & UED_period_index_option)
      YAML_strm<<indent << "index: " <<  index << std::endl;
   if (options & UED_period_variable_code_option)
      YAML_strm<<indent << "variable: " << "0x" << std::hex << variable_code << std::endl;
}
//_______________________________________________________________________dump__/


} //namespace UED

