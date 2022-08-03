#include "tabular_excel.h"

namespace CORN {
//______________________________________________________________________________
Tabular_file_Excel::Tabular_file_Excel
(const CORN::OS::File_name &_filename
,bool _keep_read_records_in_memory
,std::ios_base::openmode _openmode                                               //130401
,const Common_tabular_file_format &_format)
: Tabular_file(&_filename,_keep_read_records_in_memory)
#ifdef USE_CORN_Excel_workbook
#else
, workbook(_filename.c_str(),_openmode)
#endif
#ifdef USE_CORN_BIFF
, workbook(i_filename.c_str(),
      ,_openmode == std::ios_base::in)                                           //130401
#endif
, data_source
   (&workbook
   ,(nat32)0  // detail_line_col  I think this is 0 because the TDF file already specifies columns indexed from column 0
   ,(nat32)((_format.detail_lines_delineation.start_row_1_based > 0)
      ? (_format.detail_lines_delineation.start_row_1_based - 1) : 1)
   ,false   // expect_field_names TDF file will provide field names
   ,(nat32)0       // TDF file specifies field captions
   )
, format(_format)
, active_sheet(0)                                                                //100110
, openmode(_openmode)                                                            //130401
{
   /* NYI  currently assuming FILE_RELATIVE
   switch  (format.detail_lines_delineation.relative_to_labeled)
   {  case FILE_RELATIVE  :
         Currently set in the data member initialization above
      break;
      case DATA_RELATIVE  :
         NYI.  While this could be applicable to spreadsheets
         where there may be some rows of arbitrary text
         at the top of a sheet with some cell with static text to
         indicate the beginning of the data, I think this to be rarely done.
      break;
      case  PAGE_RELATIVE  :
         // Not applicable because spreadsheets dont have pages.
      break;
      case BLOCK_RELATIVE  :
         // Not currently applicable because spreadsheets, but could be.
      break;
   }
   */
   // Probably not needed,  I am pretty sure in Excel, the decimal mark is set by the current Localization selected in the operating system settings.
}
//______________________________________________________________________________
Tabular_file_Excel::~Tabular_file_Excel()
{
#ifdef USE_CORN_Excel_workbook
#else
//   if (!read_only) // NYI and modified
   if (openmode == std::ios_base::out)
      workbook.save(false);                                                      //120115
#endif
}
//______________________________________________________________________________
const char *Tabular_file_Excel::label_string(std::string &buffer)          const
// probably return unqualified workbook name or the fully qualified filename
{  workbook.get_name(buffer);
   return buffer.c_str();
}
//_2017-04-23___________________________________________________________________
//170424 replaced with label_string
/*
const char *Tabular_file_Excel::label_cstr(char *buffer)        const
// probably return unqualified workbook name or the fully qualified filename
{  std::string workbook_name;
   workbook.get_name(workbook_name);
   strcpy(buffer,workbook_name.c_str());
   return buffer;
}
*/
//______________________________________________________________________________
bool Tabular_file_Excel::goto_sheet(const std::string &sheet_name)
{  active_sheet =  workbook.provide_sheet(sheet_name);
   return active_sheet != NULL;
}
//_2010-01-10___________________________________________________________________
nat32 Tabular_file_Excel::write_field_string(const char *c_str
      ,CORN::Delineation_layout::Text_quote_mode quote_mode)
{  nat32 written_string_length = 0;
   if (active_sheet)
   {  nat16 row = current_raw_line - 1;
      nat16 col = current_field_column - 1;
      active_sheet->set_cell_label (col,row,std::string(c_str));
   }
   return written_string_length;
}
//_2010-01-10___________________________________________________________________
nat32 Tabular_file_Excel::get_record_count()
// should be const need to check ancestors and decendents
{
  // active_sheet =  workbook.provide_sheet(sheet_name);
   nat32 last_data_row =  active_sheet-> get_last_define_row(); // 0 based
   nat32 data_line_count =
      // the number of spreadsheet rows on the active sheet
      // I am not sure how to interpret the DIMENSIONS record.
      // I assume that the first row is the first row with any non cleared/empty cells
      // and similarly for the last.
      // so I think we only need to look at the last defined row
      last_data_row
      - (format.detail_lines_delineation.start_row_1_based - 1);
   return data_line_count;
}
//_2010-01-10___________________________________________________________________
modifiable_ CORN::Workbook &Tabular_file_Excel::get_workbook()     modification_
{  return workbook;
}
//_2011-12-12___________________________________________________________________
const std::string &Tabular_file_Excel::compose_formatted_string_from_cstr                          //140922
      (std::string &formatted_string
      ,const char *c_str
      ,CORN::Delineation_layout::Text_quote_mode quote_mode)               const
{
   // 141003 NYI,  Not sure what I need to do in the case of Excel strings
   formatted_string.assign(c_str);
   return formatted_string;
}
//_2014-10-03___________________________________________________________________
} // namespace CORN;

