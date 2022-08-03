#include "corn/format/excel/worksheet_Excel.h"
#include "corn/format/excel/workbook_Excel.h"
#include <assert.h>
namespace CORN {
//______________________________________________________________________________
Excel_worksheet::Excel_worksheet
(const std::string &sheet_name
,BIFF_rec_BOUNDSHEET_common::Sheet_type sheet_type
,BIFF_Format i_format
,BIFF_rec_BOUNDSHEET_common::Hidden_state hidden_state
)
:Workbook::Sheet()
// now a member ,BIFF_record_set(sheet_name)
,format(i_format)
,boundsheet(0)
,bof(0)
#ifdef NYI
,index(0)
#endif
,dimensions(0)
,window2(0)
,window1(0)
,pane(0)
,selection(0)
,eof(new BIFF_rec_EOF())
{
   // Create a boundsheet record if BIFF version > 4
   if ((format == BIFF5) || (format == BIFF7))  boundsheet = new  BIFF57_rec_BOUNDSHEET(sheet_name,sheet_type,hidden_state);
   else if (format >= BIFF8)                    boundsheet = new  BIFF8_rec_BOUNDSHEET(sheet_name,sheet_type,hidden_state);
   else                                         boundsheet = 0; // Boundsheet records apply only to BIFF5>
   // The following are required in the worksheet record set
   create_bof();
   if (format >= BIFF3)
   {
      //NYI create_index();
      create_dimensions();
   }
   if (format < BIFF7)
      create_window1();
      // For later versions, window1 appears in the workbook globals section.
   provide_window2();
   // EOF record will be appended on commit
}
//______________________________________________________________________________
const char *Excel_worksheet::is_key_string(const std::wstring &key)               const
{
   static std::string sheet_name;
   get_name(sheet_name);
   return sheet_name == key;
}
//______________________________________________________________________________
/*180820 
const char *Excel_worksheet::get_key()                                    const
{
   static std::string sheet_name;
   get_name(sheet_name);
   return sheet_name.c_str();
}
*/
//______________________________________________________________________________


#ifdef DISABLED
101127
I can't remember which new BIFF_cell_record_xxx replaced BIFF_cell_record,
in any case, this class is deprecated and is no longer used for reading,
instead, use Cell_reader.
const BIFF_cell_record *Excel_worksheet::Row_set::get_cell(nat16 col)     const
{
   const BIFF_cell_record *found_cell =
   dynamic_cast<const BIFF_cell_record *>(cell_records.find(col));


   return found_cell;
}
#endif
//______________________________________________________________________________
Cell_textual *Excel_worksheet::Row_set::provide_textual_record(nat16 col) provision_
{  Cell_textual *textual_cell = 0;
   BIFF_record *is_cell_at_col = dynamic_cast<BIFF_record *>(cell_records.find(col));
   textual_cell = (is_cell_at_col)
   ? dynamic_cast<Cell_textual *>(is_cell_at_col)  // will return 0 if the existing cell is not textual
   : (format >= BIFF8)  // create a new cell for the format
         ? dynamic_cast<Cell_textual *>(new BIFF8_rec_LABEL(row_record->get_row(),col))
         : dynamic_cast<Cell_textual *>(new BIFF3457_rec_LABEL(row_record->get_row(),col));
   return textual_cell;
}
//_2010-11-27___________________________________________________________________
Cell_numeric *Excel_worksheet::Row_set::provide_numeric_record
(nat16 col,Data_type intended_value_type)                              provision_
{  Cell_numeric *numeric_cell = 0;
   BIFF_record *is_cell_at_col = dynamic_cast<BIFF_record *>(cell_records.find(col));
   numeric_cell = (is_cell_at_col)
   ? dynamic_cast<Cell_numeric *>(is_cell_at_col) // will return 0 if the existing cell is not numeric
   : (format > BIFF2)
     ? dynamic_cast<Cell_numeric *>(new BIFF34578_rec_NUMBER(row_record->get_row(),col))
     : dynamic_cast<Cell_numeric *>(new BIFF2_rec_NUMBER(row_record->get_row(),col));
   return numeric_cell;
}
//_2010-11-27___________________________________________________________________
bool Excel_worksheet::set_range_bool(const char *range, bool value)
{  assert(false);
   // Need to look up how to store bool 111006
   return false;
}
//_2011-10-06___________________________________________________________________
bool Excel_worksheet::set_cell_bool(nat16 col, nat32 row, bool value)
{
   assert(false);
   // Need to look up how to store bool 111006
   return false;
}
//_2011-10-06___________________________________________________________________
//120105 sint16 Excel_worksheet::set_cell_integer(nat16 col, nat32 row, sint16 value)
sint32 Excel_worksheet::set_cell_integer30(nat16 col, nat32 row, sint32 value)
{  redimension_if_necessary(col,row);
   Row_set *row_set = provide_row(row);
   Cell_numeric *numeric_cell = row_set->provide_numeric_record(col,DT_int16);
   return numeric_cell ? numeric_cell->set_int32(value) : 0;                     //120105
}
//______________________________________________________________________________
const std::string & Excel_worksheet::set_cell_label
(nat16 col, nat32 row
,const std::string & value)
//NYI      ,CSS_justifications alignment
{  redimension_if_necessary(col,row);
   Row_set *row_set = provide_row(row);
   Cell_textual *label_record = row_set->provide_textual_record(col);
   if (label_record)
      label_record->set_string(value);
   return value;
}
//______________________________________________________________________________
const std::wstring &Excel_worksheet::set_cell_label_wstring
(nat16 col, nat32 row, const std::wstring &value)
{  redimension_if_necessary(col,row);
   Row_set *row_set = provide_row(row);
   Cell_textual *label_record = row_set->provide_textual_record(col);
   if (label_record)
      label_record->set_wstring(value);
   return value;
}
//_2013-09-01__________________________________________________________________/
float64 Excel_worksheet::set_cell_number(nat16 col, nat32 row, float64 value,uint8 precision)
{
   redimension_if_necessary(col,row);
   Row_set *row_set = provide_row(row);
   Cell_numeric *numeric_record = row_set->provide_numeric_record(col,DT_float64);
   if (numeric_record)                    // I think this need to be written
   {
      numeric_record->set_float64(value);
//      write_cell_record(*numeric_record);
   };
   return numeric_record? numeric_record->set_float64(value) : 0.0;
}
//______________________________________________________________________________
int32 Excel_worksheet::set_cell_date(nat16 col, nat32 row,       const CORN::Date_const &date_value)
{  // I believe dates are stored in cells with a variant,
   // but the Excel documentation doesn't support this.
   // It may be a formated string.
   // currently I am writing a string.
   std::string buffer;
   set_cell_label(col,row,std::string(date_value.append_to_string(buffer)));
   return date_value.get_date32();
}
//______________________________________________________________________________
int32 Excel_worksheet::get_cell_integer30(nat16 col, nat32 row)           const
{  Row_set *row_set = provide_row(row);
   Cell_numeric *numeric_record = row_set->provide_numeric_record
      (col,DT_int32);
   return numeric_record? numeric_record->
      get_int32()
      : 0;
}
//______________________________________________________________________________
bool Excel_worksheet::get_cell_bool(nat16 col, nat32 row)                  const
{  Row_set *row_set = provide_row(row);
   Cell_numeric *numeric_record = row_set->provide_numeric_record
      (col,DT_int32);
   return (bool) numeric_record? numeric_record->
      get_int32()
      : 0;

// WARNING I am not sure how boolean are stored in Excel, I presume an integer with value 0 or 1
}
//_2013-04-01___________________________________________________________________
float64 Excel_worksheet::get_cell_number(nat16 col, nat32 row)             const
{  Row_set *row_set = provide_row(row);
   Cell_numeric *numeric_record = row_set->provide_numeric_record(col,DT_float64);
   return numeric_record ? numeric_record->get_float64() : 0.0;
}
//______________________________________________________________________________
const std::wstring &Excel_worksheet::get_cell_label  (nat16 col, nat32 row,std::wstring &label)   const
{  Row_set *row_set = provide_row(row);
assert(false); // NYI
// NYI   BIFF_rec_LABEL &label_record = row_set->provide_LABEL_record(col);
//NYI   return label_record.get_value().c_str();
   return label;
}
//______________________________________________________________________________
const std::wstring &Excel_worksheet::get_range_label
(const char *range,std::wstring &label)                                    const
{  assert(false); // NYI
   return label;
}
//_2013-04-02___________________________________________________________________
void Excel_worksheet::Row_set::commit(Excel_workbook &workbook)
{  if (row_record)  workbook.append_record(row_record,true); row_record = 0;
   while (Binary_record_index_node_dynamic *record_node = (Binary_record_index_node_dynamic *)cell_records.pop_at_head())
   {  workbook.append_record(record_node->relinquish(),true);
   }
}
//______________________________________________________________________________
void Excel_worksheet::commit(Excel_workbook &workbook)
{
/*
Required Records
(I think INDEX, DIMENSIONS, WINDOW2 may actually only be prefered
BOF - Set the 6 byte offset to 0x0010 (worksheet)
INDEX
DIMENSIONS
WINDOW2
cells
EOF
*/
   if (bof)          workbook.append_record(bof,true);
   // Not all versions have boundsheet
   // Boundsheet has already been appended to workbook
   // but we need to update the BOF pointer.
   if (boundsheet)
   {  nat32 bof_rec_pos = workbook.get_position_of(bof);
      boundsheet->set_BOF_stream_pos(bof_rec_pos);
      workbook.finished_with(boundsheet);
   }
   bof = 0; // Don't clear bof until we have updated boundsheet
   //NYI   if (index)        workbook.append_record(index,true);      index = 0;
   if (dimensions)   workbook.append_record(dimensions,true); dimensions = 0;
   // cells should immediately follow dimensions
   // Pop all the cell records and relinquishes them to the workbook.
   nat32 row_block_count = 0;
   while (Row_set *row_set = (Row_set *)row_sets.pop_at_head())
   {
      row_set->commit(workbook);
      if (format >= BIFF5)
         if (++row_block_count == 24)
         {
            /* NYI need to output DBCELL
            Excel stores cell records in blocks with no more than 32 rows.
            Each row that contains cell records has a corresponding
            ROW record in the block,
            and each block contains a DBCELL record at the end of the block.
            */
            row_block_count = 0;
         }
   }
   // Make sure distinguished records are completely relinquished the to the workbook.
   // We must not attempt to access those records again.
   // We don't delete them because workbook now owns them.
   if (window1)      workbook.append_record(window1,true);       window1     = 0;
   if (window2)      workbook.append_record(window2,true);       window2     = 0;
   if (pane)         workbook.append_record(pane,true);          pane        = 0;
   if (selection)    workbook.append_record(selection,true);     selection   = 0;
   if (eof)          workbook.append_record(eof,true);           eof         = 0;
}
//______________________________________________________________________________
void Excel_worksheet::redimension_if_necessary(nat16 col, nat32 row)
{  if (dimensions)
   {  // When outputting earlier versions of excel, the sheet doesn't have dimensions
      dimensions->redimension(col,row);
   }
}
//______________________________________________________________________________
void Excel_worksheet::create_bof()
{  switch (format)
   {     case BIFF8 :   bof = new BIFF8_rec_BOF(BIFF_rec_BOF::WORKSHEET);  break;
         case BIFF7 :   bof = new BIFF57_rec_BOF(BIFF_rec_BOF::WORKSHEET);  break;
         case BIFF5 :   bof = new BIFF57_rec_BOF(BIFF_rec_BOF::WORKSHEET);  break;
         case BIFF4 :   bof = new BIFF34_rec_BOF(BIFF4); break;
         case BIFF3 :   bof = new BIFF34_rec_BOF(BIFF3); break;
         case BIFF2 :   bof = new BIFF2_rec_BOF; break;
   }
}
//______________________________________________________________________________
#ifdef NYI
void Excel_worksheet::create_index()
{  switch (format)
   {
   // Lower versions do not have index record;
   }
}
#endif
//______________________________________________________________________________
void Excel_worksheet::create_dimensions()
{  switch (format)
   {  case BIFF2 :
         dimensions = new BIFF2_rec_DIMENSIONS();
      break;
      case BIFF5 :  case BIFF7 :  case BIFF4 : case BIFF3 :
         dimensions = new BIFF3457_rec_DIMENSIONS();
      break;
      case BIFF8:
         dimensions = new BIFF8_rec_DIMENSIONS();
      break;
      // earlier versions do not have dimension
   }
}
//______________________________________________________________________________
void Excel_worksheet::create_window1()
{  window1 =  (format <= BIFF4)
   ?  (BIFF_rec_WINDOW1_common *)new BIFF234_rec_WINDOW1
   :  (BIFF_rec_WINDOW1_common *)new BIFF578_rec_WINDOW1;
}
//______________________________________________________________________________
BIFF_rec_WINDOW2_common &Excel_worksheet::provide_window2()             provision_
{  if (!window2)
   switch (format)
   {  case BIFF2:
         window2 = new BIFF2_rec_WINDOW2;
      break;
      case BIFF5 : case BIFF7 :  case BIFF4 : case BIFF3 :
         window2 = new BIFF3457_rec_WINDOW2;
      break;
      case BIFF8:
         window2 = new BIFF8_rec_WINDOW2;
      break;
      // earlier versions do not have window2
   }
  return *window2;
}
//______________________________________________________________________________
BIFF_rec_PANE  &   Excel_worksheet::provide_pane()                      provision_
{  if (!pane) pane = new BIFF_rec_PANE;
   return *pane;
}
//______________________________________________________________________________
void Excel_worksheet::freeze_pane(nat16 i_left_most_column , nat16 i_top_most_row,BIFF_rec_PANE::Panes active_pane )
{  if (!pane)
      pane = new BIFF_rec_PANE();
/*NYI
   if (!selection)
   {
      selection = new BIFF_rec_SELECTION();
      Binary_record_index_node_dynamic *rec_node = new Binary_record_index_node_dynamic(selection);
      append(rec_node);
   };
*/
   provide_window2();
   pane->freeze(i_left_most_column ,  i_top_most_row,active_pane );
   window2->set_has_frozen_panes(true);
}
//______________________________________________________________________________
nat32 Excel_worksheet::get_first_define_row()                             const
{  return dimensions ? dimensions->get_first_define_row() : 0; }
nat32 Excel_worksheet::get_first_define_column()                          const  //  Excel only has 16bit column indexes
{  return dimensions ? dimensions->get_first_define_column() : 0; }
nat32 Excel_worksheet::get_last_define_row()                              const
{  return dimensions ? dimensions->get_last_define_row() : 0; }
nat32 Excel_worksheet::get_last_define_column()                           const  //  Excel only has 16bit column indexes
{  return dimensions ? dimensions->get_last_define_column() : 0; }
//______________________________________________________________________________
nat16 Excel_worksheet::get_row_count()                                    const
{  nat16 row_count = 0;
   return get_last_define_row() - get_first_define_row();
   // note that both get_last_define_row() and get_first_define_row()
   // return 1 more than the actual row index (Don't ask me why Excel did this!)
}
//______________________________________________________________________________
#ifdef DISABLED
101127
This is dependent on get_cell which I needed to disable
This class is deprecated and is not longer used for reading,
instead, use Cell_reader
bool Excel_worksheet::is_cell_empty(nat16 col, nat32 row)                   const
{  bool result = false;
      // returns true if the cell has no data
   Row_set *row_set =  get_row(row);
   if (row_set)
      result = row_set->get_cell(col) != NULL;
   return result;
}
//______________________________________________________________________________
#endif
Excel_worksheet::Row_set *Excel_worksheet::provide_row(nat32 row)                       provision_
{  Row_set *row_set =  (Row_set *)row_sets.find(row);
   if (!row_set)
   {  // we don't yet have the row
      row_set = new Row_set(row,format);
      //CORN::Item *test = row_set;
      row_sets.append(row_set);
   }
   return row_set;
}
//______________________________________________________________________________
Excel_worksheet::Row_set *Excel_worksheet::get_row(nat32 row)
{  Row_set *row_set = (Row_set *)row_sets.find(row);
   return row_set;
}
//______________________________________________________________________________
void Excel_worksheet::freeze_pane(nat16 left_most_column,nat32 top_most_row )
{  provide_pane().freeze(left_most_column,top_most_row,BIFF_rec_PANE::lower_right);
      /*WARNING may need to pass the active pane */
   provide_window2().set_has_frozen_panes(true);
}
//______________________________________________________________________________
const std::string &Excel_worksheet::get_name(std::string &sheet_name)      const   // the name of the sheet
{  boundsheet->get_sheet_name(sheet_name);
   return sheet_name;                                                            //101127
}
//______________________________________________________________________________
Excel_worksheet::Row_set::Row_set(nat32 row_number, BIFF_Format _format)
: Enumeration()
, row_record(0)
, cell_records()
, format(_format)
{  row_record = (format < BIFF3) // WARNING I am not sure when the ROW record format changed!
      ? (BIFF_rec_ROW_abstract*)(new BIFF2_rec_ROW )
      : (BIFF_rec_ROW_abstract*)(new BIFF34578_rec_ROW);
}
// This constructor is used when creating new sheet
//______________________________________________________________________________
Excel_worksheet::Row_set::Row_set(BIFF_rec_ROW_abstract  *_row_record)
: row_record (_row_record)
, cell_records()
{}
//______________________________________________________________________________
nat32 Excel_worksheet::Row_set::get_key_nat32()                            const
{ return row_record->get_row(); } ;
//______________________________________________________________________________
} // namespace CORN;

