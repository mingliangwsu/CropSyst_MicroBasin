//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "UED/convert/text_dBase_Excel_with_TDF/tabular_file_with_TDF_convertor.h"
#include "corn/tabular/file.h"
#include "Excel_workbook_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGridWorkbook"
#pragma link "AdvGrid"
//#pragma link "AdvGridExcel"
#pragma link "BaseGrid"
#pragma link "tmsAdvGridExcel"
#pragma link "AdvObj"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{}

// Note, CORN::Tabular_file assumes the file is only 2 dimensional Rows and Columns
// But Excel also has sheets, the TDF format accomodates sheets
// probably would be better to simply read the workbook directly
//(driven by the TDF format, rather than trying to compose the delineated data record.
//______________________________________________________________________________
class  Tabular_AdvGridExcelIO  // Only handles single sheet
: public CORN::Tabular_file
{
   TAdvGridWorkbook *grid_workbook;
   TAdvGridExcelIO *grid_Excel_IO; // owned by a form
   int curr_row;  // Row in the spreadsheet 0 based
 public:
   Tabular_AdvGridExcelIO
      (const CORN::OS::File_name &filename_
      ,TAdvGridWorkbook *grid_workbook_
      ,TAdvGridExcelIO *grid_Excel_IO_)
      : CORN::Tabular_file(&filename_,false,0)
      , grid_Excel_IO(grid_Excel_IO_)
      , curr_row(0)
      , grid_workbook(grid_workbook_)
      {}
   virtual int get_column_count()                                  { return 0; }
      // Not currently needed for import utility
   // returns the number of columns identified in the table.
   virtual int get_column_width(int column)                         {return 0; } //pure
   // returns the width (in characters of the specified column
   // I think it is OK to return 0 if column width is not significant (I.e. spreadsheets)
   virtual bool get(modifiable_ Data_record &data_rec);
   virtual bool get_next(Data_record &data_rec);
   virtual bool   goto_first()                      {curr_row = 0; return true;}
   // Goto the first line in the text file with detail line data (not header or column header)
   virtual bool   goto_index(nat32 index)   { curr_row = index; ; return true; }
   virtual bool   goto_last() { return false; } // NYI (/NYN)
   virtual bool   goto_next(int32 skip_records = 1)            { return false; } // NYI (/NYN)
   /* 161013 field type is actually format specification,
   virtual uint8 get_field_type(const char *field_name) { return false; }; // NYI (/NYN)
   */
      // returns the filed type corresponding to VV_entry types
   virtual nat32 get_current_index()                           { return false; } // NYI (/NYN)
      // returns the index value for the table's current position.
      // For database tables this is the record number
      // For memory tables, this is the memory location or object pointer);
   virtual nat32 append(Data_record &data_rec)                 { return false; } // NYI (/NYN)
      // This creates a new record at the end of the table and sets data_rec.
      // Returns the record index of the new record that was appended.
   virtual nat32 delete_record()                              { return false; } // NYI (/NYN)
      // This marks the current record as deleted.
      // usually only a flag is set in the record indicating it is deleted
      // so the record is not actually physically deleted.
/*170423 	  
   virtual const char *label_cstr(char *buffer) const
   {
   // NYI NYN
   // Normally (for text output (I.e. Windows title bar)
   // we would want to show the name of the file and the line (actual line or data line?)being processed
   // This currently isn't needed for the UED import utilities
   return buffer;
   };
*/   
   virtual const char *label_cstr(std::string &buffer) const  //170423
   {
   // NYI NYN
   // Normally (for text output (I.e. Windows title bar)
   // we would want to show the name of the file and the line (actual line or data line?)being processed
   // This currently isn't needed for the UED import utilities
   return buffer.c_str();
   }
   

   virtual nat32 get_record_count()                                { return 0; } // NYN
   //               inline virtual int get_data_lines()
 protected:
   inline virtual bool set_data(Data_record &data_rec)             { return false; } // NYN
   inline virtual nat32 write_delimitor_string(const char *c_str)         { return 0; }
   inline virtual nat32 write_raw_string(const char *c_str)                  { return 0; }

      // 180730 probably needs to be implemented

   // This writes the specified string to the current position.
   // returns the actual number of characters written including quotes
   inline virtual nat32 write_field_string(const char *c_str
      ,CORN::Delineation_layout::Text_quote_mode quote_mode)           { return 0; }

      // 180730 probably needs to be implemented


   inline virtual const std::string &compose_formatted_string_from_cstr                 //140922
      (std::string &formatted_string
      ,const char *c_str
      ,CORN::Delineation_layout::Text_quote_mode quote_mode)     const      { return formatted_string; }

      // 180730 probably needs to be implemented


   inline virtual bool reset()                                            stream_IO_
      { return false; }

      // 180730 probably needs to be implemented


   inline virtual const char *label_string(std::string &buffer)
      const { return buffer.c_str(); }

   inline virtual bool set_data
      (Data_record &data_rec
      ,bool         append) { return false; }

      // 180730 probably needs to be implemented

 private:
   inline Tabular_AdvGridExcelIO *check_abstract()
      {return new Tabular_AdvGridExcelIO(CORN::OS::File_name_concrete(""),0,0 ); }

};
//_2005-04-10___________________________________________________________________
bool Tabular_AdvGridExcelIO::get(modifiable_ Data_record &data_rec)
{  CORN::Tabular_file::get(data_rec);
   bool got = false;
   bool all_data_column_cell_values_on_this_row_blank = true;
   // At this point we should be at a data_record row in the spreadsheet

   //             Currently assume no end file marks (I have not provision for specifying the cell column in the TDF format, but could assume marker text in the first column.
   //NYI 050426    if (file_extent_layout.end_marker.length() && record_line_string.find(file_extent_layout.end_marker) != NPOS)
   //NYI 050426          at_end_data_marker  = true;
   //NYI 050426    if (at_end_data_marker)
   //NYI 050426        return false;
   {
   int curr_col = 0;
   FOR_EACH_IN(section,VV_Section,data_rec.sections,each_section)
   {   // This format doesn't really have sections, but the expected data record layout may
      FOR_EACH_IN(entry,VV_base_entry,section->entries,each_entry)
      {
         AnsiString cell_value = grid_workbook->Grid->Cells[curr_col][curr_row];
         if (cell_value.Length())
         {  entry->set_str(cell_value.c_str());
         //NYI  Here we have the raw data as a string
         //NYI   we should check for special markers
         //      we would provide CORN::Tabular_file with marker/code pairs (I.e. validation status)
         //NYI 050518             entry->set_validation_status(validate(/*column_index,*/datum->c_str())); // Here we can check for any attribute markers
         //                      Derived classes can override check_datum_code for missing markers etc...
            all_data_column_cell_values_on_this_row_blank = false;
         };
         got = true;
         curr_col ++;                                                            //061018
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   }
   if (got) curr_row ++;                                                         //061018
   return got;
}
//_2005-04-06___________________________________________________________________
bool Tabular_AdvGridExcelIO::get_next(Data_record &data_rec)
{  bool got = get(data_rec);
   return got;
}
//_2005-04-06___________________________________________________________________
class Excel_workbook_with_TDF_convertor
: public Tabular_file_with_TDF_convertor
{
   TAdvGridWorkbook *grid_workbook;
   TAdvGridExcelIO         *grid_Excel_IO; // owned by a form
   Tabular_AdvGridExcelIO  *tabular_file;
 public:
   Excel_workbook_with_TDF_convertor
      (TAdvGridWorkbook *_grid_workbook,TAdvGridExcelIO *_grid_Excel_IO
      ,UED::Convertor_arguments &arguments_
      );
 protected :
   virtual CORN::Tabular_file *provide_tabular_file
   (
   //180730    const char *target_filename ,
    Year &file_year);
   // file_year is only used by formats that split files into years

};
//______________________________________________________________________________
Excel_workbook_with_TDF_convertor::Excel_workbook_with_TDF_convertor
(TAdvGridWorkbook *_grid_workbook,TAdvGridExcelIO *_grid_Excel_IO
,UED::Convertor_arguments &arguments_
)
: Tabular_file_with_TDF_convertor(arguments_)
, grid_workbook(_grid_workbook)
, grid_Excel_IO(_grid_Excel_IO)
, tabular_file(0)
{
/*180730
   setup_from_filenames(ParamStr(0).c_str(),ParamStr(1).c_str());
*/
}
//______________________________________________________________________________
CORN::Tabular_file *Excel_workbook_with_TDF_convertor::
provide_tabular_file
(
//180730 const char *target_filename,
Year &file_year_not_applicable)
{
   CORN::OS::File_name_concrete target_filename_temp(arguments.target_filename);
   if (!tabular_file) tabular_file = new Tabular_AdvGridExcelIO(target_filename_temp,grid_workbook,grid_Excel_IO);
   return tabular_file;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::continue_buttonClick(TObject *Sender)
{
   UED::Convertor_arguments arguments;
   Excel_workbook_with_TDF_convertor convertor
      (excel_IO_grid_WB,AdvGridExcelIO1,arguments);

   int result =  convertor.convert();
   // convertor.notify_climgen();
}
//---------------------------------------------------------------------------

