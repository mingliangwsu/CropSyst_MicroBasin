#include "corn/container/text_list.h"
#include "corn/string/strconv.hpp"
namespace CORN {
//______________________________________________________________________________
Text_list::Text_list
(const char *initial_text
, char separator_character)                                                      //090919
{
   // This constructor takes all_text which contains \n separates text strings and composes
   // an initial list of text.
   if (initial_text && (initial_text[0] != 0))                                   //050618
   {  size_t start_pos = 0;
      size_t run_length = 0;
      for (int i = 0; initial_text[i] != 0; i++)
      {  if ((initial_text[i] == separator_character) || (initial_text[i+1] == 0))
         {  if (initial_text[i+1] == 0) run_length +=1; /*at the end of the string*/ //130103
            if (run_length)
               append(new Item_string(initial_text, start_pos, run_length ));    //180822_090922
            start_pos = i+1;
            run_length = 0;
         } else run_length += 1;
      }
   }
}
//______________________________________________________________________________
Text_list::Text_list
(const Text_list &copy_from)
{  copy(copy_from);
}
//_2017-01-01___________________________________________________________________
nat32 Text_list::copy(const Text_list &copy_from)                                //170101
{  nat32 copied = 0;
   FOR_EACH_IN(item,CORN::Item,copy_from,each_item)
   {
      Item_string *as_string = dynamic_cast<Item_string *>(item);
      if (as_string)
         append(new Item_string(*as_string));
      else
      {  Item_wstring *as_wstring = dynamic_cast<Item_wstring *>(item);
         append(new Item_string(*as_wstring));
      }
      copied ++;
   } FOR_EACH_END(each_item)
   return copied;
}
//_2017-01-01___________________________________________________________________
bool Item_string::write(std::ostream &strm)                        performs_IO_ //150728
{  strm << c_str(); // delimiting has been moved to container write()            //151002
   return true;                                                                  //150728
}
//_write____________________________________________________________2009-12-22_/
Item *Text_list::find(const char *search_key,bool case_sensitive)          const //180119
{  if (is_empty()) return 0;                                                     //030709
   FIND_FOR_EACH(found_item,item,Item ,true,item_finder)                         //030709
   {
      std::string item_string; item->append_to_string(item_string);              //180115
      const char *key = item_string.c_str();                                     //030117
      bool keys_match = ((case_sensitive ? strcmp(key,search_key) :
         #if defined(__unix)
         strcasecmp(key,search_key)) == 0);   //980928
         #else
         stricmp(key,search_key)) == 0);
         #endif
      if (keys_match)
         found_item = item;                                                      //030710
   } FOR_EACH_END(item_finder)                                                   //030707
   return found_item;
}
//_______________________________________________________________________find__/
Item_string                                                                      //180119
*Text_list::add_cstr(const char *text_to_add)
{  Item_string
      *added = 0;
   if (!unique_keys || !find(text_to_add))                                       //110228
   {  added = new Item_string(text_to_add);
      append(added);
   }
   return added;
}
//_2006-09-10_____________________________________________________________add__/
Item_wstring
*Text_list::add_wstr(const wchar_t *text_to_add)
{
///*171225 text list items can now be either string or wstring
   // This is currently just a hack
   // It is used by Directory_entry_name_abstract which supports
   // Unicode
   // Text_list currently does not support Unicode, so this current
   // implementation has a potential loss of data


   Item_wstring *added = new Item_wstring(text_to_add);
   append(added);
   return added;

//*/

//17126 could be this:   return dynamic_cast<Text_list::Item *>(append(new Item_wstring(text_to_add)));  //171225
}
//_2012-02-09___________________________________________________________________
Item_string
*Text_list::add_string (const std::string &text_to_add)          //130123
{  return add_cstr(text_to_add.c_str()); }
//_2012-01-23___________________________________________________________________
Item_wstring
*Text_list::add_wstring(const std::wstring &text_to_add)         //130123
{  return add_wstr(text_to_add.c_str()); }
//_2012-01-23___________________________________________________________________
/* conceptual
bool Text_list::append_text(const char         *text_to_append);                         //171226
bool Text_list::append_text(const wchar_t      *text_to_append);                         //171226
bool Text_list::append_text(const std::string  &text_to_append);                         //171226
bool Text_list::append_text(const std::wstring &text_to_append);                         //171226
*/
//______________________________________________________________________________
Item *Text_list::find_wstring(const std::wstring &search_key,bool case_sensitive) const
{  // This is currently just a hack until I have created wide version
   // of text list
   std::string search_key_string;
   CORN::wstring_to_string(search_key,search_key_string);
   return find(search_key_string.c_str(),case_sensitive);
}
//_2013-03-04___________________________________________________________________
Item *Text_list::find_string(const std::string &search_key,bool case_sensitive) const
{  // This is currently just a hack until I have created wide version
   // of text list
   return find(search_key.c_str(),case_sensitive);
}
//_2013-03-10___________________________________________________________________
} // namespace CORN

