
#include "corn/spreadsheet/workbook_datasrc.h"
#include "corn/data_source/vv_entry.h"
#include "corn/data_source/datarec.h"
//170531#include "corn/datetime/date.hh"
#include "corn/tabular/tabular.h"
namespace CORN
{
//______________________________________________________________________________
Workbook_data_source::Workbook_data_source
(CORN::Workbook   *_workbook
,nat32             _detail_line_col
,nat32             _detail_line_row
,bool              _expect_field_names
,nat32             _field_name_row)
: Data_source()
, workbook           (_workbook)
, detail_line_col    (_detail_line_col)
, detail_line_row    (_detail_line_row)
, curr_row           (_detail_line_row)
, expect_field_names (_expect_field_names)
, field_name_row     (_field_name_row)
{}
//______________________________________________________________________________
bool Workbook_data_source::goto_next(int32 skip_records )
{  curr_row +=  skip_records;
   return true;
}
//______________________________________________________________________________
bool Workbook_data_source::goto_first()
{  // Sets the current row index to the first detail line row.
   curr_row =  detail_line_row;
   return true;
}
//______________________________________________________________________________
bool Workbook_data_source::goto_index(nat32  zero_based_index)
{  // Sets the current row index to the first detail line row + zero_based_index;
   curr_row =  detail_line_row + zero_based_index;
   return true;
}
//______________________________________________________________________________
#ifdef DEPRECATED
101124 I am not using this for reading any more, now using Cell_reader
bool Workbook_data_source::get_next(Data_record &data_rec)
{
   // A where clause index more than one record.
   // In this case, use get() to fetch the first record
   // and repeat calling get_next() to fetch remaining records.
   // get_next will return false if there were no
   // additional records returned by the SELECT WHERE statement
   // to fetch.
   // Note that this abstract class ALWAYS returns false because this abstract class does not
   // actually fetch the data, it only set up the the structure.
   // Derived classes must return true unless the data could not be fetched.
   curr_row ++;
   return get(data_rec);      
}
//______________________________________________________________________________
bool Workbook_data_source::get(Data_record &data_rec)
{  bool got =Data_source::get(data_rec);
   got = false;
   FOR_EACH_IN(section,VV_Section,data_rec.sections,each_section)                //100110
   {
/*
100110 I need to remember what I was doing with these fielded sheet
and see if it is still applicable.
*/
      Fielded_sheet *fielded_sheet = get_fielded_sheet(section->get_section_label().c_str()/*180820 get_key()*/ );
      Workbook::Sheet *sheet = fielded_sheet->provide_sheet(); // was get_sheet
      nat32  curr_col = detail_line_col;
            //for each entry in current section:
      FOR_EACH_IN(entry,VV_abstract_entry.,section->entries,each_entry)          //111118_100110
      {  // lookup field in actual fields:
         nat8 curr_col = fielded_sheet->get_column_index(entry->get_variable().c_str()/*180820 get_key()*/);
               // else just read the data from the columns in the same order as the data record.
               // If any one cell for this row has a value, we presume the record is valid.
               if (!sheet->cell_empty(curr_col,curr_row))
                  got = true;
               int16    cell_int;
               float64  cell_float;
               CORN_string cell_label;
               CORN::Date     cell_date;
               // First get the data value from the spreadsheet
               switch (entry->get_type())
               {
                  case VV_int8      :  // Spreadsheet just has one integer type
                  case VV_int16     :
                  case VV_int32     :
                  case VV_uint8     :
                  case VV_uint16    :
                  case VV_uint32    :
                                       cell_int = sheet->get_cell_integer(curr_col,curr_row);
                  break;
                  case VV_float32   : // Spreadsheet just has one float type
                  case VV_float64   :
                                       cell_float = sheet->get_cell_number(curr_col,curr_row);
                  break;
                  case VV_date      :  cell_date.set(sheet->get_cell_date(curr_col,curr_row));
                  break;
                  case VV_bool      :  // The following types are stored in label cells
                  case VV_byte      :
                  case VV_enum      :
                  case VV_char_array:
                  case VV_Filename  :
                  case VV_unknown   :
                  case VV_string    :  cell_label.assign(sheet->get_cell_label(curr_col,curr_row));
                  break;
               }
               // Now store it in the data record.
               switch (entry->get_type())
               {
                  case VV_int8      : ((VV_int8_entry *)entry)->set((int8) cell_int);           break;
                  case VV_int16     : ((VV_int16_entry *)entry)->set((int16) cell_int);         break;
                  case VV_int32     : ((VV_int32_entry *)entry)->set((int32) cell_int);         break;
                  case VV_uint8     : ((VV_uint8_entry *)entry)->set((nat8) cell_int);         break;
                  case VV_uint16    : ((VV_uint16_entry *)entry)->set((uint16) cell_int);       break;
                  case VV_uint32    : ((VV_uint32_entry *)entry)->set((nat32 ) cell_int);       break;
                  case VV_float32   : ((VV_float32_entry *)entry)->set((float32) cell_float);   break;
                  case VV_float64   : ((VV_float64_entry *)entry)->set((float64) cell_float);   break;
                  case VV_date      : ((VV_date_entry *)entry)->set(cell_date);         break;
                  case VV_bool      : ((VV_bool_entry *)entry)->set_str(cell_label.c_str());    break;
                  case VV_byte      : ((VV_byte_entry *)entry)->set(cell_label.c_str()[0]);        break;
                  case VV_enum      : ((VV_enum_entry *)entry)->set(cell_label.c_str());        break;
                  case VV_char_array: ((VV_char_array_entry *)entry)->set(cell_label.c_str());  break;
                  case VV_Filename  : ((VV_Filename_entry *)entry)->set(cell_label.c_str());    break;
                  case VV_unknown   : ((VV_unexpected_entry *)entry)->set(cell_label.c_str(),"","");  break;
                  case VV_string    : ((VV_string_entry *)entry)->set(cell_label.c_str());      break;
               }
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return got;
}
//______________________________________________________________________________
#endif
bool Workbook_data_source::set_data
(Data_record &data_rec,bool append)           //150503
{  FOR_EACH_IN(section,VV_Section,data_rec.sections,each_section)                //100110
   {  Fielded_sheet *fielded_sheet = get_fielded_sheet(section->get_section_labe().c_str()/*180820 get_key()*/);
      Workbook::Sheet *sheet = fielded_sheet->get_sheet();
            //for each entry in current section:
      FOR_EACH_IN(entry,VV_abstract_entry,section->entries,each_entry)           //100110
      {  // lookup field in actual fields:
         std::string sheet_name(entry->get_tabular_column()->sheet);             //111213
         if (sheet_name.length())                                                //111213
         {  // Some formats allow the columns to specify which sheet they are on
            // This will override the default sheet name specified
            // detail lines (data record)
            sheet = workbook->provide_sheet(sheet_name);                         //111213
         }
         nat8 curr_col = entry->get_tabular_column()->start_1based-1;            //111213
         {  std::string get_buf;
            switch (entry->get_type())
            {  case VV_int8      :  sheet->set_cell_integer30 (curr_col,curr_row,(int32)((VV_int8_entry *)entry)->get_value());  break;
               case VV_int16     :  sheet->set_cell_integer30 (curr_col,curr_row,(int32)((VV_int16_entry *)entry)->get_value()); break; //120115
               case VV_int32     :  sheet->set_cell_integer30 (curr_col,curr_row,(int32)((VV_int32_entry *)entry)->get_value()); break; //120115
               case VV_nat8     :  sheet->set_cell_integer30 (curr_col,curr_row,(int32)((VV_nat8_entry *)entry)->get_value());   break; //120115
               case VV_nat16    :  sheet->set_cell_integer30 (curr_col,curr_row,(int32)((VV_nat16_entry *)entry)->get_value());  break; //120115
               case VV_nat32    :  sheet->set_cell_integer30 (curr_col,curr_row,(int32)((VV_nat32_entry *)entry)->get_value());  break; //120115
               case VV_float32   :
               {  float64 value = (float64)(((VV_float32_entry *)entry)->get_value());
                  sheet->set_cell_number  (curr_col,curr_row,value,5);
               } break;
               case VV_float64   :  sheet->set_cell_number  (curr_col,curr_row,((VV_float64_entry *)entry)->get_value(),5);  break;
               //160517 case VV_date      :  sheet->set_cell_date    (curr_col,curr_row,((VV_date_entry *)entry)->get_value().get());  break;
               case VV_date      :
               {  CORN::Date_clad_32 date_to_set(((VV_datetime64_entry *)entry)->get_value().get_datetime64());


                  /* This works for a lot of dates, but it appears that some times XLS lib
                     may be not preserving the date format ??                    //171120
                  sheet->set_cell_date    (curr_col,curr_row,date_to_set);
                  */
                  sheet->set_cell_number  (curr_col,curr_row,date_to_set.get_date32(),5); //171120

               } break;
/*
               case VV_date      :

                  sheet->set_cell_number    (curr_col,curr_row,
                     ((VV_datetime64_entry *)entry)->get_value().get_datetime64(),5);
                     break;
*/

               case VV_bool      :  sheet->set_cell_label   (curr_col,curr_row,((VV_bool_entry *)entry)->append_to_string(get_buf));  break;
               case VV_byte      :  sheet->set_cell_label   (curr_col,curr_row,((VV_byte_entry *)entry)->append_to_string(get_buf));  break;
               case VV_enum      :  sheet->set_cell_label   (curr_col,curr_row,((VV_enum_entry *)entry)->append_to_string(get_buf));  break;
               case VV_char_array:  sheet->set_cell_label   (curr_col,curr_row,((VV_char_array_entry *)entry)->append_to_string(get_buf));  break;
               case VV_filename  :  sheet->set_cell_label   (curr_col,curr_row,((VV_directory_entry_entry *)entry)->append_to_string(get_buf));  break;
               case VV_unknown   :  sheet->set_cell_label   (curr_col,curr_row,((VV_unexpected_entry *)entry)->append_to_string(get_buf));  break;
               case VV_string    :  sheet->set_cell_label   (curr_col,curr_row,((VV_string_entry *)entry)->append_to_string(get_buf));  break;
            }
         }
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   curr_row ++;
   return true; // presume the record was written OK.
}
//______________________________________________________________________________
const char *Workbook_data_source::label_string(std::string &buffer)        const
{  return workbook->get_name(buffer).c_str();
}
//______________________________________________________________________________
/*170424 replaced with label_string
const char *Workbook_data_source::label_cstr(char *buffer)      const
{  std::string name_buffer;                                                      //101127
   strcpy(buffer,workbook->get_name(name_buffer).c_str());
   return buffer;
}
//______________________________________________________________________________
*/
nat8 Workbook_data_source::Fielded_sheet::get_column_index(const char *field_name)
{  // returns the column having the specified field name.
   // If there is no such column then the next available column is assigned.
   nat8 max_index = column_count ? column_count : 255;
   for (int i = 0; i < max_index; i++)
   {  if (column_field_names[i] == field_name)
         return i;
      else if (column_field_names[i].length())
           column_count = i+1;
   }
   // An existing field was not found add it:
   if (column_count == 255)  // We have exceeded the number of columns in the spreadsheet we just keep using the last column
   {  column_field_names[255].assign(field_name);
   } else
   {  column_field_names[column_count].assign(field_name);
      column_count++;
   }
   int col_index = column_count -1;
   // Add the field name to the spreadsheet itself
   if (expect_field_names)
      sheet->set_cell_label(col_index,field_name_row,field_name);
   return column_count -1;
}
//______________________________________________________________________________
Workbook_data_source::Fielded_sheet *Workbook_data_source::get_fielded_sheet
(const char *sheet_name)
{  Fielded_sheet *found_sheet = (Fielded_sheet *)fielded_sheets.find_cstr(sheet_name);
   if (!found_sheet)
   {  CORN::Workbook::Sheet *new_sheet = workbook->provide_sheet(sheet_name);
      found_sheet = new Fielded_sheet(new_sheet,detail_line_col,detail_line_row,expect_field_names,field_name_row);
      fielded_sheets.append(found_sheet);
   }
   return found_sheet;
}
//______________________________________________________________________________
}
