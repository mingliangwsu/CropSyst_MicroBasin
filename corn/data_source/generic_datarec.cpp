#include "corn/data_source/generic_datarec.h"
namespace CORN
{
//________________________________________________________________________________/
Generic_data_record::Generic_data_record(const char *primary_section)
   : Data_record(primary_section)
   , string_count (0)
   , float_count  (0)
   , int_count    (0)
   , bool_count   (0)
{
   for (int i = 0 ;i < 20; i++)
   {  strings[i].assign("");
      bools[i] = 0;
   }
   for (int i = 0 ;i < 200; i++)
   {  floats[i] = 0;
      int32s[i] = 0;
   }
}
//_____________________________________________________________________________/
int16 Generic_data_record::get_as_int16(const char *entry_name)           const
{
   int16 value = 0;
   if (current_section)
   {  VV_int16_entry *entry = (VV_int16_entry *)current_section->entries.find_cstr(entry_name);
      if (entry)
      {
         for (int i = 0; i < int_count; i++)
            if ((int32&)entry->value == (int32&)int32s[i])                       //170511
               return int32s[i];                                                 //170511
      } // else entry not found
   } // else simply return 0
   return value;
}
//________________________________________________________________get_as_int16_/
int32  Generic_data_record::get_as_int32(const char *entry_name)           const
{
   int16 value = 0;
   if (current_section)
   {  VV_int32_entry *entry = (VV_int32_entry *)current_section->entries.find_cstr(entry_name);
      if (entry)
      {
         for (int i = 0; i < int_count; i++)
            if ((int32&)entry->value == (int32&)int32s[i])
               return int32s[i];
      } // else entry not found
   } // else simply return 0
   return value;
}
//_2017-05-11_____________________________________________________get_as_int32_/
int16 Generic_data_record::set_as_int16(const char *entry_name, int16 value)
{
   if (current_section)
   {  VV_int16_entry *entry = (VV_int16_entry *)current_section->entries.find_cstr(entry_name);
      if (entry)
         entry->set(value);
      // else entry not found
   }
   return value;
}
//________________________________________________________________set_as_int16_/
int16 Generic_data_record::set_as_int32(const char *entry_name, int32 value)
{
   if (current_section)
   {  VV_int32_entry *entry = (VV_int32_entry *)current_section->entries.find_cstr(entry_name);
      if (entry)
         entry->set(value);
      // else entry not found
   }
   return value;
}
//________________________________________________________________________________/
/*NYN
const std::string &Generic_data_record::get_as_string(const char *entry_name) const
nat32  get_as_nat32(const char *entry_name) const
{


};
*/
//________________________________________________________________________________/

} // namespace CORN

