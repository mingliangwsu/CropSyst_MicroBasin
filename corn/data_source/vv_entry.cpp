#  ifndef compareHPP
#     include "corn/math/compare.hpp"
#  endif
#include "corn/chronometry/date_time_64.h"
#  include "corn/OS/directory_entry_name.h"
#  include "corn/metrology/units_symbology.h"
#include <stdlib.h>
#include "corn/data_source/vv_entry.h"
#include "corn/tabular/tabular.h"
#include "corn/seclusion.h"
namespace CORN {
//______________________________________________________________________________
VV_entry_item::VV_entry_item()
: Item()
, encountered(false)
{}
//_2009-04-14___________________________________________________________________
VV_base_entry::VV_base_entry
(const char *key_
,nat16 max_strlen_                                                               //010104
,const char * annotation1_
,const char * annotation2_)
:variable(key_)                                                                  //980209
,max_strlen(max_strlen_)                                                         //010103
,annotation1(annotation1_ ? annotation1_ : "")
,annotation2(annotation2_ ? annotation2_ : "")
,validation_status(0)                                                            //050517
{}
//______________________________________________________________VV_base_entryX__/
void append_annotation_to(const std::string &annotation,std::string &buffer)
{  if (annotation.length())
   {  buffer.append(" ");
      buffer.append(annotation);
   }
}
//_2015-07-31___________________________________________________________________

//130217 continue here, should be able to use the new Container::Format
/*170424
const char *VV_base_entry::label_cstr(char *buffer)                        const
{  // this function is obsolete, caller should be using label_string
   strcpy(buffer,variable.c_str());                                              //981011
   strcat(buffer,"=");                                                           //981011
   std::string value_buffer;                                                     //150731
   append_to_string(value_buffer);                                               //150731
   append_annotation_to(annotation1,value_buffer);                               //150731_981011
   append_annotation_to(annotation2,value_buffer);                               //150731_981011
   strcat(buffer,value_buffer.c_str());                                           //150803
   return buffer;
}
//______________________________________________________________________________
*/
const char *VV_base_entry::label_string(std::string &buffer)               const
{  buffer += variable;
   buffer += "=";
   append_to_string(buffer);
   append_annotation_to(annotation1,buffer);
   append_annotation_to(annotation2,buffer);
   return buffer.c_str();
}
//_2017-04-23___________________________________________________________________
bool VV_base_entry::write(std::ostream &f)                         modification_ //150728
{
   std::string buffer;                                                           //170424
   f << label_string(buffer)
    //160602 shouldn't be needed because entries container already has new line delimiter << std::endl
     ;
    return true;                                                                 //150728
}
//______________________________________________________________________________
bool VV_base_entry::write_wizard(std::ostream &wizard_stream)         stream_IO_
{
   wizard_stream
      << "[" << variable << "]"   << std::endl
      << "caption:en=" << annotation1 << std::endl;
   if (annotation2.length())
    wizard_stream
      << "hint:en=" << annotation2 << std::endl;
   std::string default_value;
   append_to_string(default_value);
   if (default_value.length())
     wizard_stream
      << "default=" << default_value << std::endl;
   return true;
}
//_VV_base_entry::write_wizard______________________________________2018-05-15_/
 bool VV_base_entry::is_key_string(const std::string &key)              affirmation_  //180820
      { return variable == key; }

/*180820  was probably only used for find_cstr now using is_key


const char *VV_base_entry::get_key()                                       const
{   return variable.c_str();
}
*/
//_2003-01-17_________________________________________________________get_key__/
bool VV_Section::is_key_string(const std::string &key)              affirmation_
{ return label == key; }
//_is_key_string____________________________________________________2018-08-20_/
/*180820  was probably only used for find_cstr now using is_key
const char *VV_Section::get_key()                                          const
{   return section_label.c_str();
}
//_2003-01-17___________________________________________________________________
*/
VV_unexpected_entry::VV_unexpected_entry
(const char *key_
,const std::string &value_
,const char * annotation1_
,const char * annotation2_)
: VV_base_entry(key_
,0 // This does not apply. In the future this may be a blob though which we
   // could expect a length //010104
,annotation1_,annotation2_)
, value(value_)
{}
//_VV_unexpected_entry:constructor__________________________________1997-06-22_/
const std::string &VV_unexpected_entry::append_to_string(std::string &buffer) const
{  buffer = value;
   return buffer;
}
//_append_to_string_________________________________________________2014-06-15_/
VV_string_entry::VV_string_entry
(const char *key_
,modifiable_ std::string &value_                                                 //111104
,nat16 max_strlen_                                                               //010104
,const char * annotation1_,const char * annotation2_)
: VV_base_entry (key_,max_strlen_,annotation1_ ,annotation2_ )
, value(value_)
{}
//_VV_string_entry__________________________________________________1997-06-22_/
const std::string &VV_string_entry::append_to_string(std::string &buffer)  const
{  buffer.append(value);
   return buffer;
}
//_append_to_string_________________________________________________2014-06-15_/
VV_directory_entry_entry::VV_directory_entry_entry
(const char *key_
,modifiable_ OS::Directory_entry_name &value_
,nat16 max_strlen_
,const char * annotation1_
,const char * annotation2_)
: VV_base_entry(key_,max_strlen_,annotation1_ ,annotation2_ )
, value(value_)
{}
//_VV_directory_entry_entry:constructor_____________________________2012-04-13_/
#ifndef _MSC_VER
VV_char_array_entry::VV_char_array_entry
(const char *key_
,modifiable_ char *value_
,nat16 max_strlen_                                                               //010104
,const char * annotation1_
,const char * annotation2_)
: VV_base_entry (key_,max_strlen_,annotation1_ ,annotation2_ )
, value(value_)
{}
//_VV_char_array_entry:constructor__________________________________1997-09-30_/
const std::string &VV_char_array_entry::append_to_string(std::string &buffer) const
{  buffer.append(value);
   return buffer;
}
//_2014-06-15___________________________________________________________________
#endif
//______________________________________________________________________________
VV_int8_entry::VV_int8_entry
(const char *key_
,modifiable_ int8 &value_
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,4,annotation1_ ,annotation2_ )
, value(value_)
{}
//_VV_int8_entry:constructor________________________________________1998-04-05_/
bool VV_int8_entry::set_str(const char *value_str)
{  int value_32 = atoi(value_str);                                               //020329
   value = (int8)value_32;                                                       //020329
   return true;
}
//_set_str__________________________________________________________2001-01-03_/
const std::string &VV_int8_entry::append_to_string(std::string &buffer)    const
{  if (tabular_column)
         append_int8_to_string
         (value,buffer,10,tabular_column->get_field_width(),' ');
   else  append_int8_to_string(value,buffer,10);
   return buffer;
}
//_append_to_string_________________________________________________2014-06-15_/
VV_nat8_entry::VV_nat8_entry
(const char *key_,modifiable_ nat8 &value_,nat8 _radix
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,5,annotation1_ ,annotation2_ )
, value(value_)
, radix(_radix)
{}
//_VV_nat8_entry:constructor________________________________________1997-06-22_/
bool VV_nat8_entry::set_str(const char *value_str)
{  nat8  temp8= (nat8)cstr_to_nat32(value_str,get_radix());
   value = temp8;                                                                //010623
   return true;
}
//_2001-01-03__________________________________________________________________/
const std::string &VV_nat8_entry::append_to_string(std::string &buffer)    const
{  if (tabular_column)                                                           //070524
      append_nat8_to_string                                                      //140210
      ((nat32) value,buffer,radix,tabular_column->get_field_width(),' ');        //140529_070524
   else  append_nat8_to_string((int32)value,buffer,radix);
   return buffer;
}
//_2014-06-15___________________________________________________________________
VV_byte_entry::VV_byte_entry
(const char *key_, modifiable_ unsigned char &value_
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,1,annotation1_ ,annotation2_ )
, value(value_)
{}
//______________________________________________________________VV_byte_entry__/
bool VV_byte_entry::set_str(const char *value_str)
{  value = (unsigned char)(value_str[0]);
   return true;
}
//_2001-01-03__________________________________________________________________/
const std::string &VV_byte_entry::append_to_string(std::string &buffer)    const
{  char result_str[2];
   result_str[1] = 0; result_str[0] = value;
   buffer.append(result_str);
   return buffer;
}
//_2014-06-15___________________________________________________________________
VV_bool_entry::VV_bool_entry
(const char *key_
,modifiable_ bool &value_
,Form    _text_form                                                              //010104
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,1,annotation1_ ,annotation2_ )
, value(value_)
, text_form(_text_form)                                                          //010104
{}
//_1997-06-22___________________________________________________VV_bool_entry__/
bool VV_bool_entry::set_str(const char *value_str)
{  value = false;
   size_t value_length = strlen(value_str);
   if (value_length)
   {  switch (value_str[0])
      {  case 't' : case 'T' : // Handles "t" "T" "true" "True" "TRUE"
            value = true; break;
         case 'f' : case 'F' : // Handles "f" "F" "false" "False" "FALSE"
            value = false; break;
         case 'o' : case 'O' : // Handles "on" "On" "ON" "off" "OFF" "Off"
            value = (value_str[1] == 'n') || (value_str[1] == 'N'); break;
         default : // Handles 0 1
            value = atoi(value_str); break;
      }
   }
   return true;
}
//_VV_bool_entry::set_str________________________________2001-01-03_1998-05-11_/
const std::string &VV_bool_entry::append_to_string(std::string &buffer)    const
{  std::string bool_value;
   bool_value = value ? "1" : "0";
      switch (text_form)
      {  case form_1    : bool_value =(value? "1" : "0"); break;
         case form_t    : bool_value =(value? "t" : "f"); break;
         case form_T    : bool_value =(value? "T" : "F"); break;
         case form_true : bool_value=(value? "true" : "false"); break;
         case form_True : bool_value=(value? "True" : "False"); break;
         case form_TRUE : bool_value=(value? "TRUE" : "FALSE"); break;
      }
   buffer.append(bool_value);
   return buffer;
}
//_VV_bool_entry::append_to_string__________________________________2014-06-15_/
VV_int16_entry::VV_int16_entry
(const char *key_,modifiable_ int16 &value_
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,6,annotation1_ ,annotation2_ )
, value(value_)
{}
//_1997-06-22__________________________________________________VV_int16_entry__/
bool VV_int16_entry::set_str(const char *value_str)
{  value = (int16)atoi(value_str);
   // this won't work if we allow other radix/*050517*/     if (!is_number(value_str)) valid = false;
   return true;
}
//_2001-01-03__________________________________________________________________/
const std::string &VV_int16_entry::append_to_string(std::string &buffer)   const
{  if (tabular_column)
         append_int16_to_string
         ((int32) value,buffer,10,tabular_column->get_field_width(),' ');
   else  append_int16_to_string(value,buffer,10);
   return buffer;
}
//_2014-06-15___________________________________________________________________
VV_nat16_entry::VV_nat16_entry
(const char *key_,modifiable_ nat16 &value_,nat8 _radix
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,5,annotation1_ ,annotation2_ )
, value(value_)
, radix(_radix)
{}
//_1997-06-22__________________________________________________VV_nat16_entry__/
bool VV_nat16_entry::set_str(const char *value_str)
{  nat32  temp32 = cstr_to_nat32(value_str,get_radix());
   set((nat16)temp32);                                                           //000926
   // this won't work if we allow other radix  if (!is_number(value_str)) valid = false;
   return true;
}
//_2001-01-03_________________________________________VV_nat16_entry::set_str__/
const std::string &VV_nat16_entry::append_to_string(std::string &buffer)   const
{  if (tabular_column)
      append_nat16_to_string
      ((nat32) value,buffer,radix,tabular_column->get_field_width(),' ');
   else
      append_nat16_to_string((int32)value,buffer,radix);
   return buffer;
}
//_2014-06-15___________________________________________________________________
VV_int32_entry::VV_int32_entry
(const char *key_,modifiable_ int32 &value_
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,11,annotation1_ ,annotation2_ )
, value(value_)
{}
//_________________________________________________VV_int32_entry_constructor__/
bool VV_int32_entry::set_str(const char *value_str)
{  value = atol(value_str);
   // this won't work if we allow other radix/*050517*/     if (!is_number(value_str)) valid = false;
   return true;                                                                  //090414
}
//_VV_int32_entry::set_str__________________________________________2001-01-03_/
const std::string &VV_int32_entry::append_to_string(std::string &buffer)   const
{  if (tabular_column)
      append_int32_to_string
      (value,buffer,10,tabular_column->get_field_width(),' ');
   else append_int32_to_string(value,buffer,10);
   return buffer;
}
//_2014-06-15___________________________________________________________________
VV_nat32_entry::VV_nat32_entry
(const char *key_,modifiable_ nat32 &value_,nat8 _radix
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,10,annotation1_ ,annotation2_ )
, value(value_)
, radix(_radix)                                                                  //000926
{}
//_VV_nat32_entry_constructor__________________________________________________/
bool VV_nat32_entry::set_str(const char *value_str)
{  value = cstr_to_nat32(value_str,get_radix());
// this won't work if we allow other radix/*050517*/     if (!is_number(value_str)) valid = false;
   return true;
}
//_VV_nat32_entry::set_str__________________________________________2001-01-03_/
const std::string &VV_nat32_entry::append_to_string(std::string &buffer)   const
{  if (tabular_column)
      append_nat32_to_string
        ((nat32) value,buffer,radix ,tabular_column->get_field_width(),' ');
   else append_nat32_to_string(value,buffer,radix);
   return buffer;
}
//_VV_nat32_entry::append_to_string_________________________________2014-06-15_/
VV_float32_entry::VV_float32_entry
(const char *key_,modifiable_ float32 &value_
,const char * annotation1_,const char * annotation2_)
: VV_base_entry(key_,10,annotation1_ ,annotation2_ )
, value(value_)
{}
//_VV_float32_entry_________________________________________________1997-06-22_/
bool VV_float32_entry::set_str(const char *value_str)
{  value = (float32)atof(value_str);
   set_validation_status(!is_number_cstr(value_str)?missing_status:good_status); //160215_050517
   return true;                                                                  //090414
}
//_VV_float32_entry::set_str________________________________________2001-01-03_/
const std::string &VV_float32_entry::append_to_string(std::string &buffer)         const
{  char result_str[50];
   if (tabular_column)
      float32_to_cstr_formated(value, result_str
         ,tabular_column->get_field_width(),tabular_column->get_precision(),'.',false);
   else strcpy(result_str,float32_to_cstr(value,8));
       // float32 is precise to only about 7 digits
   buffer.append(result_str);
   return buffer;
}
//_VV_float32_entry::append_to_string_______________________________2014-06-15_/
VV_float64_entry::VV_float64_entry
(const char *key_,modifiable_ float64 &value_
,const char * annotation1_,const char * annotation2_ )
: VV_base_entry(key_,16,annotation1_ ,annotation2_ )
, value(value_)
{}
//_VV_float64_entry:constructor_____________________________________1997-06-22_/
bool VV_float64_entry::set_str(const char *value_str)
{  value = cstr_to_float64(value_str);
   set_validation_status(!is_number_cstr(value_str)?missing_status:good_status); //160214-050517
   return true;                                                                  //090414
}
//_VV_float64_entry::set_str________________________________________2001-01-03_/
const std::string &VV_float64_entry::append_to_string(std::string &buffer) const
{  char result_str[20]; result_str[0] = 0;                                       //140909
   if (tabular_column)
       float64_to_cstr_formated(value, result_str
       , tabular_column->get_field_width(),  tabular_column->get_precision(),'.' ,false);
   else
       strcpy(result_str,float32_to_cstr(value,10));
   buffer.append(result_str);
   return buffer;
}
//_2014-06-15___________________________________________________________________
VV_date_entry::VV_date_entry
(const char *key_,modifiable_ CORN::Date_clad_32 &value_
,bool _formatted,sint16 _year_offset
,const char * annotation1_ ,const char * annotation2_ )
: VV_base_entry (key_,value_.as_string().length(),annotation1_,annotation2_)     //140615_030801
, value(value_)                                                                  //021212
, formatted(_formatted)                                                          //050412
, year_offset(_year_offset)
{}
//_VV_date_entry____________________________________________________1997-06-22_/
bool VV_date_entry::set_str(const char *value_str)
{  if (formatted) value.set_c_str(value_str);
   else           value.set_date32(atol(value_str));                             //050412
   if (year_offset)                                                              //120331
      value.set_year(value.get_year()%100 + year_offset);                        //120331
   return true;
}
//_VV_date_entry::set_str___________________________________________2001-01-03_/
const std::string &VV_date_entry::append_to_string(std::string &buffer)    const
{  append_int32_to_string(value.get_date32(),buffer);                            //170601
   return buffer;
}
//_VV_date_entry::append_to_string__________________________________2014-06-15_/
long VV_date_entry::get_days_between(const CORN::Date_const&date2,bool inclusive) const
{   return value.days_between(date2,inclusive);                                  //170430
}
//_VV_date_entry::get_days_between__________________________________2003-04-28_/
const Date_format &VV_date_entry::set_cstr
(const char *format_string)                                        modification_
{  //170601 TODO: Roger check //value.format.set_cstr(format_string);
   return *value.preferred_format;
}
//_VV_date_entry::set_cstr______________________________2014-11-20__2011-08-12_/
VV_datetime64_entry::VV_datetime64_entry
(const char *key_,modifiable_ CORN::Date_time_clad_64 &value_
,bool _formatted,sint16 _year_offset
,const char * annotation1_ ,const char * annotation2_ )
: VV_base_entry
   (key_
   ,30                                                                           //140616
   ,annotation1_,annotation2_ )                                                  //030801
, value(value_)                                                                  //021212
, formatted(_formatted)                                                          //050412
, year_offset(_year_offset)
{}
//_VV_datetime64_entry::constructor_________________________________1997-06-22_/
bool VV_datetime64_entry::set_str(const char *value_str)
{  if (formatted) value.set_c_str(value_str);
   else           value.set_datetime64(atof(value_str));  // atof converts to double (might not be the case in old compilers!)   //050411
   if (year_offset)                                                              //120331
      value
      .mod_date()                                                                //170815
      .set_year(value.ref_date().get_year()%100 + year_offset);                  //170815_120331
   set_validation_status(!is_number_cstr(value_str)?missing_status:good_status); //160215_050517
   return true;                                                                  //090414
}
//_VV_datetime64_entry::set_str_____________________________________2001-01-03_/
bool VV_datetime64_entry::set_cstr
(const char *date_format_string
,const char *time_format_string)                                   modification_
{
          date_format.set_cstr(date_format_string)                               //170525_141120
      &&  time_format.set_cstr(time_format_string);                              //170525_141120
   value.ref_date().prefer_date_format(&date_format);                            //170525
   value.ref_time().prefer_time_format(&time_format);                            //170525
   return true;
}
//_VV_datetime64_entry::set_cstr____________________________________2011-08-12_/
const std::string &VV_datetime64_entry::append_to_string(std::string &buffer) const
{  append_float64_to_string(value.get_datetime64(), 30,buffer);
/*actually decided not to append add this comment
   buffer.append(" # (");                                                        //180515
   value.append_to_string(buffer);
   buffer.append(")");
*/
   return buffer;
}
//_VV_datetime64_entry::append_to_string____________________________2014-06-15_/
VV_enum_entry::VV_enum_entry
(const char* key_,Labeled_enum &_labeled_enum
,const char* annotation1_, const char* annotation2_)
: VV_base_entry(key_,80,annotation1_, annotation2_)
, labeled_enum(_labeled_enum)
{   // Now determine the actual max_strlen from the label table
    max_strlen = labeled_enum.get_max_label_length();                            //050929
}
//_VV_enum_entry::constructor_______________________________________1997-07-09_/
void VV_enum_entry::set(const char *value_label_)
{   labeled_enum.set_label(value_label_);                                        //020322
}
//_VV_enum_entry::set_______________________________________________1997-07-09_/
bool VV_enum_entry::set_str(const char *value_str)
{  set(value_str);
   return true;
}
//_VV_enum_entry::set_str___________________________________________2001-01-03_/
const std::string &VV_enum_entry::append_to_string(std::string &buffer)    const
{  buffer.append(labeled_enum.get_label());
   return buffer;
}
//_VV_enum_entry::append_to_string__________________________________2014-06-15_/
VV_units_entry::VV_units_entry(const char *key_,Units_clad &_units_code)
: VV_base_entry(key_,80,"","")
, units_code(_units_code)
{}
//_____________________________________________________________VV_units_entry__/
void VV_units_entry::set(Units_code _code)
{  units_code.set(_code);
}
//______________________________________________________________________________
bool VV_units_entry::set_str(const char *_units_text)
{  units_code.set(CORN::units_identify_code(_units_text));
   return true;
}
//_VV_units_entry::set_str_____________________________________________________/
const std::string &VV_units_entry::append_to_string(std::string &buffer)   const
{  char description_cstr[100];
   char abbreviation_cstr[100];
   bool composed = units_code.compose_description(description_cstr,abbreviation_cstr);
   if (composed)
      buffer.append(abbreviation_cstr);
   else
   {  // use hexidecimal  Actually would prefer a descriptive units abbreviation
      // but this is a stop gap measure
      description_cstr[0] = '0';
      description_cstr[1] = '0';
      CORN::nat32_to_cstr(units_code.get(),description_cstr+2,16);
      buffer.append(description_cstr);
   }
   return buffer;
}
//_VV_units_entry::append_to_string_________________________________2014-06-15_/
VV_Section::VV_Section(const std::string &_section_label)
:Item()
,label(_section_label)                                                           //180821_980209
,entries()
{}
//_VV_Section::constructor_____________________________________________________/
const char *VV_Section::label_string(std::string &buffer)                  const
{ buffer += "["+label+"]";                                                       //180821
  return buffer.c_str();
}
//______________________________________________________________________________
bool VV_Section::write(std::ostream &f)                            modification_ //150728
{  nat32 written = 0;                                                            //150728
   if (!entries.is_empty())                                                      //040109
   { f << '[' << label << ']' << std::endl;                                      //180821
     written = entries.write(f);                                                 //150728
   }
   return written;                                                               //150728
}
//______________________________________________________________________________
VV_base_entry *VV_Section::set_entry
(const char *key                                                                 //030117
,const char *value                                                               //030117
,bool unexpected_only)
{  VV_base_entry *expected_entry = (VV_base_entry *)(entries.find_cstr(key));
   if (expected_entry)
   {  if (!unexpected_only)
         expected_entry->set_str(value);                                         //030117
   } else entries.append(expected_entry = (new VV_unexpected_entry(key,value))); //090306
   expected_entry->set_encountered(true);                                        //121221
   return expected_entry;                                                        //090306
}
//_VV_Section::set_entry____________________________________________1998-04-26_/
bool VV_Section::was_entry_encountered(const char *entry_name)             const
{  VV_base_entry *entry = (VV_base_entry *)entries.find_cstr(entry_name);
   bool entry_encountered = (entry && entry->was_encountered());
   return entry_encountered;
}
//_VV_Section::was_entry_encountered________________________________2005-09-27_/
void VV_directory_entry_entry::set
(const OS::File_name &value_)
{ value.set_cstr(value_.c_str()); }
//______________________________________________________________________________
void VV_directory_entry_entry::set(const std::string &value_)
{  value.set_cstr(value_.c_str());
}
//_1999-08-24___________________________________________________________________
bool VV_directory_entry_entry::set_str(const char *value_str)
{ value.set_cstr(value_str); return true;}
//_2001-01-03___________________________________________________________________
const std::string &VV_directory_entry_entry::append_to_string(std::string &buffer) const
{  value.append_to_string(buffer);
   return buffer;
}
//_VV_directory_entry_entry::append_to_string_______________________2014-06-15_/
Seclusion &VV_directory_entry_entry::provide_seclusion()              provision_
{
   if (!seclusion)
      seclusion = new Seclusion;
   return *seclusion;
}
//_VV_directory_entry_entry::provide_seclusion______________________2018-05_15_/
void VV_date_entry::set(const CORN::Date_const &value_)
{ value.set(value_);}
//______________________________________________________________________________
void VV_datetime64_entry::set(const CORN::Date_time &value_)
{ value.set_datetime64(value_.get_datetime64()); }
//______________________________________________________________________________

#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x340))
VV_parameter_entry::VV_parameter_entry(Parameter_abstract &_parameter)
: VV_abstract_entry()
, parameter(_parameter)
{}
//______________________________________________________________________________
bool VV_parameter_entry::is_key_string(const std::string &key)      affirmation_ //180820
{ return key == parameter.properties.name_long; }

/*180820  was probably only used for find_cstr now using is_key

const char *VV_parameter_entry::get_key()                                  const
{ return parameter.properties.name_long; }
*/
//______________________________________________________________________________
bool VV_parameter_entry::set_str(const char *value_cstr)           modification_
{ return parameter.set_str(value_cstr); }
//______________________________________________________________________________
//190726LML const std::string &VV_parameter_entry::get_variable()                      const
const std::string VV_parameter_entry::get_variable()                      const
{  //return parameter.properties.name_long;
    return std::string(parameter.properties.name_long);
}
//__________________________________________________________________2018-08-20_/
bool VV_parameter_entry::write(std::ostream &  f)                     stream_IO_ //150728
{  std::string buffer;
   parameter.append_VV_to(buffer); // Buffer will include endl;                  //170523
   f << buffer;
   return true;                                                                  //150728
}
//______________________________________________________________________________
bool VV_parameter_entry::write_wizard(std::ostream &wizard_stream)    stream_IO_
{  const Parameter_number & parameter_number = dynamic_cast
      <const Parameter_number &>(parameter);
   const char *param_prop_name_long = parameter.properties.name_long;
   if (param_prop_name_long && strlen(param_prop_name_long))
   {  wizard_stream<< "[" << param_prop_name_long << "]" << std::endl;
      const char* param_prop_caption = parameter.properties.caption;
      if (param_prop_caption && strlen(param_prop_caption))
         wizard_stream << "caption:en=" << param_prop_caption << std::endl;
      const char *param_prop_hint = parameter.properties.hint;
      if (param_prop_hint && strlen(param_prop_hint))
       wizard_stream << "hint:en=" << param_prop_hint << std::endl;
   } else
     VV_abstract_entry::write_wizard(wizard_stream);
   std::string default_value;
   append_to_string(default_value);
   if (default_value.length())
     wizard_stream
      << "default=" << default_value << std::endl;
   Units_clad parameter_units(parameter.properties.units_code);
   if (parameter_units.get())
   {
      std::string units_stored_description; //unused
      std::string units_stored_abbr;
      if (parameter_units.compose_description_str
            (units_stored_description,units_stored_abbr))
         wizard_stream << "units:stored=" << units_stored_abbr << std::endl;
      if (parameter_number.alt_units_codes)
      {  nat16 u = 0;
         wizard_stream << "units:apropos=";
         while (parameter_number.alt_units_codes[u])
         {  Units_clad alt_units(parameter_number.alt_units_codes[u]);
            std::string units_apropos_description; //unused
            std::string units_apropos_abbr;
            if (alt_units.compose_description_str
               (units_apropos_description
               ,units_apropos_abbr))
               wizard_stream << units_apropos_abbr << ", ";
            u++;
         }
      } else
      {  // if metric print all the metric units

         /*  NYI

         wizard_stream << "units:apropos=";

         */
      }
      wizard_stream << std::endl;
   } // else the parameter is unitless so don't show units
   const char* param_prop_descript_URL = parameter.properties.description_URL;
   if (param_prop_descript_URL && strlen(param_prop_descript_URL))
      wizard_stream << "ontology=" << param_prop_descript_URL << std::endl;
   return true;
}
//_VV_parameter_entry::write_wizard_________________________________2018-05-15_/
nat16 VV_parameter_entry::get_max_strlen()                                 const
{ return parameter.format.field_width; }
//_get_max_strlen___________________________________________________2011-11-07_/
unsigned char VV_parameter_entry::get_type()                               const
{  const Parameter_number *parameter_number
      = dynamic_cast<const Parameter_number *>(&parameter);
   return                                                                        //120723
      (parameter_number)
      ? parameter_number->get_mode()
      : DT_not_assigned;
}
//_get_type_________________________________________________________2011-11-07_/
const std::string &VV_parameter_entry::append_to_string(std::string &buffer) const
{  parameter.get_value_as_string(buffer);
   return buffer;
}
//_append_to_string_________________________________________________2014-06-15_/
#endif
} // namespace CORN
