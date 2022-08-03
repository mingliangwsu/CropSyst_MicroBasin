#  include "corn/math/compare.h"
#  include "corn/string/strconv.h"
#include "corn/data_source/datarec.h"
#include "corn/data_source/data_table.h"
#include "corn/data_source/datasrc.h"
#include "corn/data_source/datasrc_index.h"

namespace CORN {
//______________________________________________________________________________
Dynamic_data_source_index::Dynamic_data_source_index
(const char *i_index_field_name)
: index_field_name(i_index_field_name)
, Association_list()
{}
//_2002-01-25___________________________________________________________________
bool Dynamic_data_table_index::activate_record(Index_item &index_item)
{  Record_index &record_index = (Record_index &)index_item;
   return table.goto_index(record_index.rec_num);
}
//_2002-11-13___________________________________________________________________
bool Dynamic_data_source_index::find_record(const Index_item &index_to_find,bool from_first_record)
{  if (!index_built())
   {  from_first_record = true;                                                  //021111
 //                We have to goto to the first record if we build the index
 //                otherwise we will be at the end if the index and would never read the record.
       build_index();
   }
   Index_item *found_indice = (Index_item *)find_matching(index_to_find,from_first_record);
   return (found_indice)
    ? activate_record(*found_indice)
    : false;
 }
//_2001-05-09___________________________________________________________________
bool Dynamic_data_source_index::find_record_cstr(const char *search_key_cstr,bool from_first_record)
{  Index_item index_to_find;
   index_to_find.rec_key_value.key_string = new char[strlen(search_key_cstr) + 1];
   strcpy(index_to_find.rec_key_value.key_string,search_key_cstr);
   return find_record(index_to_find,from_first_record);
}
//_2002-09-14___________________________________________________________________
bool Dynamic_data_source_index::find_record_int32(int32 search_key,bool from_first_record)
{  Index_item index_to_find;
   index_to_find.rec_key_value.key_int32 = search_key;
   return find_record(index_to_find,from_first_record);
}
//_2002-09-14___________________________________________________________________
class Index_int32_data_record : public Data_record
{public:
   std::string key_field_name;
   int32 key_field_value;
 public:
    inline Index_int32_data_record(const std::string &i_key_field_name)
       : Data_record("-")
       , key_field_name(i_key_field_name)
       {}
   inline virtual void expect_structure(bool for_write)
      {  Data_record::expect_structure(for_write);                               //120314
         expect_int32(key_field_name.c_str(),key_field_value);
         structure_defined = true;                                               //120314
      }
};
//_2001-05-09___________________________________________________________________
class Index_string_data_record : public Data_record
{public:
   std::string key_field_name;
   std::string key_field_value;
public:
   inline Index_string_data_record(const std::string &i_key_field_name)
      : Data_record("-")
      , key_field_name(i_key_field_name)
      {}
   inline virtual void expect_structure(bool for_write)
   {  Data_record::expect_structure(for_write);                                  //120314
      expect_string(key_field_name.c_str(),key_field_value,255); // Don't care about field length, it will be read from the file
      structure_defined = true;                                                  //120314
   }
};
//_2001-05-09___________________________________________________________________
Index_item::Index_item
(uint8 i_key_type
,const char *i_index_field_name                                                  //020125
,int  string_size)
: Item()
, key_type (i_key_type)
, selected(false)
{  // This constructor is used when we don't read the data source yet for the field info
   if (string_size)
   {  rec_key_value.key_string = new char[string_size];
      rec_key_value.key_string[0] = 0;
   }
}
//______________________________________________________________________________
Index_item::Index_item()
: Item()
, key_type (VV_unknown)
, selected(false)
{} // This constructor is used for searches
//______________________________________________________________________________
Index_item::Index_item
(Data_source &data_source
,uint8 i_key_type
,const char *i_index_field_name)
: Item()
, key_type(i_key_type)
, selected(false)
{
   switch (key_type)
   {
      case VV_string :
      {
         Index_string_data_record rec_to_index(i_index_field_name);
         data_source.get(rec_to_index);
         rec_key_value.key_string = new char[rec_to_index.key_field_value.length()+1];
         strcpy(rec_key_value.key_string,rec_to_index.key_field_value.c_str());
      } break;
      //case VV_int8          NYI
      //case VV_int16
      case VV_int32 :
      {
         Index_int32_data_record rec_to_index(i_index_field_name);
         data_source.get(rec_to_index);
         rec_key_value.key_int32 = rec_to_index.key_field_value;
      } break;
      //case VV_int32          NYI
      //case VV_uint8
      //case VV_uint16
      //case VV_uint32
      //case VV_float32
      //case VV_float64
      //case VV_bool
      //case VV_date
      //case VV_byte
      //case VV_char_array
      //case VV_Filename
      //case VV_enum
   }
}
//_2002-11-11___________________________________________________________________
Record_index::Record_index
(Data_table       &data_table_
,const char       *index_field_name_ // should pass field interface
)
:Index_item
(data_table_
,data_table.get_field_type(index_field_name_)
,index_field_name_)
{  rec_num = data_table_.get_current_index();
}
//_2002-11-11___________________________________________________________________
Index_item::~Index_item()
{
   if ((key_type == VV_string) && (rec_key_value.key_string))
   { delete [] rec_key_value.key_string; rec_key_value.key_string = 0; }
}
//______________________________________________________________________________
int Index_item::compare(const Item &second)                                const
{  int result = 0;
   Index_item &second_item = (Index_item &)second;
   if (second_item.key_type != key_type)
      return 0;
   switch (key_type)
   {
      case VV_string : result = strcmp(rec_key_value.key_string,second_item.rec_key_value.key_string);
      break;
      case VV_int32  : result =
         (rec_key_value.key_int32 < second_item.rec_key_value.key_int32)
         ? -1
         : (rec_key_value.key_int32 > second_item.rec_key_value.key_int32)
         ? 1
         : 0;
      break;
   }
   return result;
}
//_1998-05-11_____________________________________________________________________________
void Dynamic_data_table_index::build_index()                          stream_IO_
{  for (bool at_end = !table.goto_first(); !at_end; at_end = !table.goto_next())
     append(new Record_index(table,index_field_name.c_str()));
}
//_2001-05-09___________________________________________________________________
bool Dynamic_data_source_index::index_built() const
{  return count();
}
//_2001-05-09___________________________________________________________________
#ifdef NYI
possibly not needed
void Dynamic_int32_indexed_dBase_data_source::where_long
(const char *attribute, const long value)                          contribution_
{
   last_where_value = value;
   where_mode = true;
   if (attribute == index_field_name)
      find_record(value);
   else
      Dynamic_indexed_dBase_data_source::where_long(attribute, value);
}
//______________________________________________________________________________
void Dynamic_int32_indexed_dBase_data_source::where_cstr
(const char *attribute, const char *value)                         contribution_
{  if (attribute == index_field_name)
   {  // we presume value is a numeric since this is implied
      long value_int = atol(value);
      where_long(attribute,value_int);
   } else // the where statement is not for the indexed field we will have to do an exhaustive search
      Dynamic_indexed_dBase_data_source::where_cstr(attribute, value);
}
//______________________________________________________________________________
Dynamic_int32_indexed_dBase_data_source::Index_item::Index_item
(Dynamic_indexed_dBase_data_source &file,const char *field_name)
: Item()
, rec_num(file.get_record_number())
{   Index_int32_data_record rec_to_index(field_name);
    rec_num = file.get_record_number();
    file.get(rec_to_index);
    rec_key_value = rec_to_index.key_field_value;
}
//_2001-05-09___________________________________________________________________
Dynamic_string_indexed_dBase_data_source::Index_item::Index_item
(Dynamic_indexed_dBase_data_source &file,const char *field_name)
: Association()
, rec_num(file.get_record_number())
{   Index_string_data_record rec_to_index(field_name);
    rec_num = file.get_record_number();
    file.get(rec_to_index);
    rec_key_value = rec_to_index.key_field_value;                                //020125
}
//______________________________________________________________________________
void Dynamic_string_indexed_dBase_data_source::where_long
(const char *attribute, const long value) not_const
{  if (attribute == index_field_name)
   {  // since value is numeric, we need to convert it to a string.
      char value_str[10];
      CORN_int32_to_str(value,value_str,10);
      where_cstr(attribute,value_str);
   } else
      Dynamic_indexed_dBase_data_source::where_long(attribute, value);
}
//_2002-06-12___________________________________________________________________
void Dynamic_string_indexed_dBase_data_source::where_cstr
(const char *attribute, const char *value) not_const
{  where_mode = true;
   where_found = false;
   if (attribute == index_field_name)
   {  where_found = find_record(value);
   }
   else // the where statement is not for the indexed field we will have to do an exhaustive search
      Dynamic_indexed_dBase_data_source::where_cstr(attribute, value);
}
//_2002-06-12___________________________________________________________________
#endif
} // CORN


