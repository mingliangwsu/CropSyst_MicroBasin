#  include "corn/container/container.h"
#  include "corn/container/unilist.h"
#  include <string.h>
#  include "corn/string/strconv.hpp"
namespace CORN {
//______________________________________________________________________________
Container::Node::Node(Item *elmt_data_)
: elmt_data(elmt_data_)
{}
//______________________________________________________________________________
Container::Node::~Node()
{  delete elmt_data;                                                             //170630
   elmt_data = 0;
}
//_1998-02-06___________________________________________________________________
int Container::Node::compare(const Item &other)                            const
{ return elmt_data->compare(other); }
//_1998-02-06___________________________________________________________________
/*170424 replaced with label_string
const char *Container::Node::label_cstr(char *buffer)           const
{  return elmt_data->label_cstr_deprecated(buffer); }
//                For some applications, label should be overridden
//_1997-07-20___________________________________________________________________
*/
const char *Container::Node::label_string(std::string &buffer)             const
{  return elmt_data->label_string(buffer); }
//                For some applications, label should be overridden
//_2017-04-23___________________________________________________________________
bool Container::Node::setup_structure(Data_record &data_rec,bool for_write) modification_
{ return elmt_data->setup_structure(data_rec,for_write); }
//_2001-01-09___________________________________________________________________
Item *  Container::Iterator::Nth(nat32 n)
{  if (n == 0) n = 1;
   return Ith((nat32)(n -1));
}
//_2003-07-07___________________________________________________________________
bool Container::Iterator::delete_current()
{  Item *detached_item = detach_current();
   bool delete_ok = detached_item!=0;
   if (delete_ok)
      delete detached_item;
   return delete_ok;
}
//_2003-07-07___________________________________________________delete_current_/
nat32 Container::clone_from
(const Container &from_copy
,nat32 include_from_item_index                                                   //171117
,nat32 count)                                                                    //171117
{  nat32 cloned = 0;
   nat32 item_index = 0;                                                         //171117
   nat32 count_remaining = count;
   FOR_EACH_IN(from_copy_item,Item,from_copy,each_item)
   {
      if ((item_index >= include_from_item_index)                                //171117
       && count_remaining)                                                       //171117
      {
         if (take(from_copy_item->clone()) != 0)
            cloned++;
         count_remaining--;                                                      //171117
      }
      item_index++;                                                              //171117
   } FOR_EACH_END(each_item)
   return cloned;
}
//_2017-08-17_______________________________________________________clone_from_/
nat32 Container::transfer_all_from                                               //150930
(Container &from_container,Item::Filter filter)                    modification_
{  nat32 transfer_count = 0;                                                     //150930
   nat32 from_container_count = from_container.count();                          //040412
   if (from_container_count)                                                     //040319
   {  Unidirectional_list not_transferred;                                       //040319
      while (!from_container.is_empty())                                         //030707
      {  Item *popped = from_container.pop_first();                              //040318
         if (popped)                                                             //120618
         {
            if ((filter == Item::filter_all) ||                                  //120618
               popped->matches_filter(filter))                                   //040318
            {
               append(popped);                                                   //040318
               transfer_count++;                                                 //150930
            }
            else  not_transferred.append(popped);                                //040318
         }
      }
      // Put back those items not transferred
      if (!not_transferred.is_empty())                                           //120618
         from_container.transfer_all_from(not_transferred);                      //040318
   }
   return transfer_count;                                                        //150930
}
//_2012-06-18__1999-11-22____________________________________transfer_all_from_/
/*This isn't linking, don't know why
nat32 Container::give_to
(Container &receiving_container
,Item::Filter filter )                                             modification_
{  nat32 given_count = 0;
   FOR_EACH(item,Item,each_item)
   {
      if ((filter == Item::filter_all) ||
          item->matches_filter(filter))
      {
         receiving_container.take(each_item->detach_current());
         given_count++;
      }
   } FOR_EACH_END(each_item)
   return given_count;
}
*/
//_2016-11-01__________________________________________________________________/
Item *Container::get_Nth(nat32 element_num)                                const
{  if (element_num == 0) element_num = 1;
   return get_at((nat32)(element_num -1));
}
//_____________________________________________________________________get_Nth_/
bool Container::delete_Nth(nat32 element_num)                     modification_
{  if (element_num == 0) element_num = 1;
   return delete_at((nat32)(element_num -1));                                    //100616
}
//__________________________________________________________________delete_Nth_/
void Container::set_checked(bool i_checked)                        contribution_ //101129
{  FOR_EACH(item,Item,each_item)
      item->set_checked(i_checked);
   FOR_EACH_END(each_item)
// This is used for Container checked list boxes. It sets the checked state of all items.
}
//_2002-01-25______________________________________________________set_checked_/
void Container::set_selected(bool selected_)                       contribution_ //101129
{ // This is used for Container list boxes. It sets the selected state of all items.
   FOR_EACH(item,Item,each_item)
      item->set_selected(selected_);
   FOR_EACH_END(each_item)
}
//_2002-01-25_____________________________________________________set_selected_/
bool Container::delete_at(uint32 index)
{  bool deleted = false;                                                         //100616
   Container::Iterator *deleter = iterator();
   if (deleter->Ith(index))
   {  deleter->delete_current();
      deleted = true;                                                            //100616
   }
   delete deleter;
   return deleted;                                                               //100616
}
//___________________________________________________________________delete_at_/
Item* Container::detach(Item *detach_item)
{  Iterator *iter = iterator();
   if (iter->find(detach_item,true))
      iter->detach_current();
   delete iter;
   return detach_item;
}
//_2003-07-09___________________________________________________________detach_/
bool Container::remove(Item *detach_item)                                        //170701
{  Iterator *iter = iterator();
   bool removed = false;                                                         //170701
   if (iter->find(detach_item))
      removed = iter->delete_current();                                          //170701
   set_modified(true);                                                           //060321
   delete iter;
   return removed;                                                               //170701
}
//_2003-07-09___________________________________________________________remove_/
nat32 Container::prepend_items(Container &take_items)                submission_ //171204
{
   nat32 prepended = 0;
   while (Item *last = take_items.pop_last())
   {
      prepended += 1;  // eventually prepend should return bool
      prepend(last);
   }
   return prepended;
}
//_2017-12-04___________________________________________________________________
Item *Container::add_sorted                                                      //970928
(Item *new_element
, Ordering /*ordering*/)                                                         //971211
{  return append(new_element);                                                   //000211
}
//_1997-09-28_______________________________________________________add_sorted_/
Item *Container::find_matching
(const Item &item_to_match                                                       //030119
,bool from_beginning)                                                      const
{  // Find a node with the same copy
   FIND_FOR_EACH(found_item,local_curr,Item,from_beginning,match_finder)
      if (local_curr->compare(item_to_match) == 0)
          found_item = local_curr;
   FOR_EACH_END(match_finder)
  return(found_item);
};
//_______________________________________________________________find_matching_/
Item *Container::find_comparable
(const Item &comparable_item_to_match
, bool from_beginning) const
{  // Find a node with the same copy
   CORN::Container::Iterator *find_iterator = iterator();
   Item *found_item = find_iterator->find_comparable(comparable_item_to_match,from_beginning);
   delete find_iterator;
   return(found_item);
}
//_____________________________________________________________find_comparable_/
Item *Container::Iterator::find_comparable(const Item &comparable_item,bool from_beginning)
{  if (from_beginning)  first();
   Item * found_item =0;
   for (Item *curr_item = from_beginning?first():current()
       ;curr_item && !found_item
       ;curr_item = next())
      if (curr_item->compare(comparable_item) == 0)
      {  found_item = curr_item;
         return found_item;
      }
   return found_item;
}
//_2005-10-11__________________________________________________find_comparable_/
bool Container::Iterator::has(Item *item_to_find,bool from_beginning)
{  if (from_beginning)  first();
   Item * found_item =0;
   for (Item *curr_item = from_beginning?first():current()
       ;curr_item && !found_item
       ;curr_item = next())
      if (curr_item== item_to_find)
      {  found_item = curr_item;
         return found_item!=0;
      }
   return found_item!=0;
}
//_2005-10-11______________________________________________________________has_/
Item *Container::Iterator::find(Item *item_to_find,bool from_beginning)
{  if (from_beginning)  first();
   Item * found_item =0;
   for (Item *curr_item = from_beginning?first():current()
       ;curr_item && !found_item
       ;curr_item = next())
      if (curr_item== item_to_find)
      {  found_item = curr_item;
         return found_item;
      }
   return found_item;
}
//________________________________________________________________________find_/
nat32 Container::write(std::ostream &strm)                          performs_IO_ //150728
{  nat32 written = 0;                                                            //150728
   FOR_EACH(item,Item,each_item)
   {  item->write(strm); written++;
      if (write_delimiter.length())                                              //171229
         strm << write_delimiter.c_str();                                        //171229
   } FOR_EACH_END(each_item)
   return written;                                                               //150728
}
//_2004-01-08____________________________________________________________write_/
nat32 Container::write_with_format(std::ostream &strm, const Format &format,nat16 indent_level)   performs_IO_
{  nat32 written = 0;                                                            //150728
   if (format.initializer)
   {  if (format.indentor)
         for (int i = 0; i < indent_level; i++)
            strm << format.indentor;
      strm << format.initializer;
   }
   bool successive_item = false;
   FOR_EACH(item,Item,each_item)
   {  if (successive_item && format.items.separator) strm << format.items.separator;
      else successive_item = true;
      item->write_with_format(strm,format.items,indent_level+1);
      written++;                                                                 //150728
   } FOR_EACH_END(each_item)
   if (format.finalizer)
   {  if (format.indentor)
         for (int i = 0; i < indent_level; i++)
            strm << format.indentor;
      strm << format.finalizer;
   }
   return written;                                                               //150728
}
//_2013-02-17________________________________________________write_with_format_/
#ifndef _MSC_VER
nat32 Container::write_binary(Binary_file_interface &bin_file)      performs_IO_
{  nat32 bytes_written = 0;
   FOR_EACH(item,Item,each_item)
   {  bytes_written += item->write_binary(bin_file);
   } FOR_EACH_END(each_item)
   return bytes_written;
}
#endif
//_2011-10-15_____________________________________________________write_binary_/
bool Container::get_modified(bool clear_modified)                          const
{  bool was_modified = modified;
   if (clear_modified)
      modified = false;
   return was_modified;
}
//_2006-03-21_____________________________________________________get_modified_/
bool Container::set_modified(bool _modified)                       contribution_
{ return modified = _modified; }
//_2006-03-21_____________________________________________________set_modified_/
Item *Container::find_cstr(const_ASCIIZ search_key,bool case_sensitive)    const //120921
{  //051011 Note this could now probably simply call find_comparable() but it might be better to keep key separate
   if (!search_key) return 0;                                                    //100518
   if (is_empty()) return 0;                                                     //030709
   FIND_FOR_EACH(found_item,item,Item,true,item_finder)                          //030710
   {
      if (item->is_key_cstr(search_key)                                          //180820
         || item->is_key_string(search_key))                                     //180821
         found_item=item;           //180820
      else                                                                       //180802
      {  // Normally one would use specifically find_wstring                     //180802
         // But it may be the case that the derived item                         //180802
         // recognizes only wstring.                                             //180802
         std::wstring search_key_w;                                              //180802
         CORN::ASCIIZ_to_wstring(search_key,search_key_w);                       //180802
         found_item = item->is_key_wstring(search_key_w) ? item : 0;             //180802
      }

      /*180820
      const char *key = item->get_key();                                         //030117
      if (key)                                                                   //160704_100518
      {
         int compare_result =                                                    //091031
            #if (defined(__unix__) || defined(__linux__))
            (case_sensitive?strcmp(key,search_key):strcasecmp(key,search_key));  //980928
            #else
            (case_sensitive?strcmp(key,search_key):stricmp(key,search_key));
            #endif
         bool keys_match = compare_result  == 0;                                 //091031
         if (keys_match)
            found_item = item;                                                   //030710
      }
      */
    } FOR_EACH_END(item_finder)
   return found_item;
}
//_2014-07-16__1998-02-07____________________________________________find_cstr_/
Item *Container::find_string(const std::string &search_key,bool case_sensitive) const //120921
{
   if (is_empty()) return 0;                                                     //030709
   FIND_FOR_EACH(found_item,item,Item,true,item_finder)                          //030710
   {
/*180820
      std::string item_key;                                                      //180802
      item->key_string(item_key);                                           //180802
      if (search_key.compare(item_key) == 0)                                     //180802
*/
      if (item->is_key_string(search_key)                                        //180820
          || item->is_key_cstr(search_key.c_str()))                              //180821
         found_item = item;                                                      //180802
      else                                                                       //180802
      {  // Normally one would use specifically find_wstring                     //180802
         // But it may be the case that the derived item                         //180802
         // recognizes only wstring.                                             //180802
         std::wstring search_key_w;                                              //180802
         CORN::string_to_wstring(search_key,search_key_w);                       //180802
         found_item = item->is_key_wstring(search_key_w) ? item : 0;             //180802
      }
    } FOR_EACH_END(item_finder)
   return found_item;

//180802   return find_cstr(search_key.c_str(),case_sensitive);
}
//_2014-07-16__2011-10-25__________________________________________find_string_/
Item *Container::find_wstring(const std::wstring &search_key,bool case_sensitive) const //120921
{
   if (is_empty()) return 0;                                                     //030709
   FIND_FOR_EACH(found_item,item,Item,true,item_finder)                          //030710
   {
/*180820
      std::wstring item_key;                                                      //180802
      item->key_wstring(item_key);                                           //180802
      if (search_key.compare(item_key) == 0)                                     //180802
*/
      if (item->is_key_wstring(search_key)                                       //180820
         || item->is_key_wstr(search_key.c_str()))                                 //180821
         found_item = item;                                                      //180820
      else                                                                       //180821
      {  // Normally one would use specifically find_wstring                     //180821
         // But it may be the case that the derived item                         //180821
         // recognizes only wstring.                                             //180821
         std::string search_key_s;                                               //180821
         CORN::wstring_to_string(search_key,search_key_s);                       //180821
         found_item = item->is_key_string(search_key_s) ? item : 0;              //180821
      }
    } FOR_EACH_END(item_finder)
   return found_item;
//180802   return find_wstr(search_key.c_str(),case_sensitive);
}
//_2014-07-16__2003-04-06_________________________________________find_wstring_/
Item *Container::find_wstr(const_UnicodeZ search_key,bool case_sensitive) const //120921
{  //051011 Note this could now probably simply call find_comparable() but it might be better to keep key separate
   if (!search_key) return 0;
   if (is_empty()) return 0;
   FIND_FOR_EACH(found_item,item,Item,true,item_finder)
   {
/*180820 use new is_key()
      const wchar_t *key = item->get_key_wide();
      if (!key) return 0;
      int compare_result =
        #if defined(__MINGW32__)
         (case_sensitive ? wcscmp(key,search_key) : _wcsicmp(key,search_key));   //Liu.M for MinGW problem 09/20/13
        #else
        #if defined (__unix) || defined(unix) || defined(__GNUC__)
         (case_sensitive ? wcscmp(key,search_key) : wcscasecmp(key,search_key));
        #else
         (case_sensitive ? wcscmp(key,search_key) : _wcsicmp(key,search_key));
        #endif
        #endif
      bool keys_match = compare_result  == 0;
      if (keys_match)
*/
      if (  item->is_key_wstr(search_key)                                        //180820
          ||item->is_key_wstring(search_key))                                    //180821
         found_item = item;                                                      //180821
      else
      {  // Normally one would use specifically find_wstring
         // But it may be the case that the derived item
         // recognizes only wstring.
         std::string search_key_s;                                               //180821
         CORN::wstring_to_string(search_key,search_key_s);                       //180821
         found_item = item->is_key_string(search_key_s) ? item : 0;              //180821
      }
   } FOR_EACH_END(item_finder)
   return found_item;
}
//_find_wstr____________________________________________2014-07-16__2011-08-28_/
Item *Container::find_nat32  (nat32 search_key)                            const
{
   if (is_empty()) return 0;
   FIND_FOR_EACH(found_item,item,Item,true,item_finder)
   {
/*180820 use new is_key()
      if (item->get_key_nat32() == search_key)
*/
      if (item->is_key_nat32(search_key))                                              //180820
         found_item = item;
   } FOR_EACH_END(item_finder)
   return found_item;
}
//_2015-06-08_______________________________________________________find_nat32_/
nat32 Container::remove_all_matching_key_cstr
(const char *search_key,bool case_sensitive)                       modification_
{  // Removes all matching entries from the list and deletes the associated data!
   // Returns true if there was a matching deletion.
   nat32 matching_deletions = 0;
   for (Item *matching_item = find_cstr(search_key,case_sensitive)               //120921
       ;matching_item                                                            //010831
      ;matching_item = find_cstr(search_key,case_sensitive))                     //120921
   {  remove(matching_item);
      matching_deletions++;
   }
   return matching_deletions;
}
//_2014-07-16__2001-08-14_________________________remove_all_matching_key_cstr_/
Item *Container::delete_unappropriatabled(Item *new_element)      appropriation_
{  Item *return_element = new_element;                                           //150818
   {  Item *existing_element = unique_keys ? find_comparable(*new_element) : 0;  //150818
      if (existing_element)                                                      //150818
      {  delete new_element;                                                     //150818
         return_element = 0;
      }
   }
   return return_element;
}
//_2016-10-24_________________________________________delete_unappropriatabled_/
nat32 Container::string_items (std::string &string_buffer, char separator) const
{  nat32 strung = 0;
   bool first = true;
   FOR_EACH(item,Item,each_item)
   {  if (!first) string_buffer += separator;
      first = false;
      item->append_to_string(string_buffer);
      strung++;
   } FOR_EACH_END(each_item)
   return strung;
}
//_2017-12-25___________________________________________________________________
nat32 Container::string_items (std::wstring &string_buffer, wchar_t separator) const
{  nat32 strung = 0;
   bool first = true;
   FOR_EACH(item,Item,each_item)
   {  if (!first) string_buffer += separator;
      first = false;
      item->append_to_wstring(string_buffer);
      strung++;
   } FOR_EACH_END(each_item)
   return strung;
}
//_2017-12-25___________________________________________________________________

} // namespace CORN end

