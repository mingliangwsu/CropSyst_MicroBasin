#include "cell_reader_BIFF.h"
//130829 #include <corn/file_sys/filename.h>
#include <corn/format/excel/BIFF_record.h>
#include <corn/spreadsheet/cell_pump/cell_receiver.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define DEBUG_CELL_READER
#ifdef DEBUG_CELL_READER
#include <iostream>
#endif
bool maybe_Excel_2007_saved_as_2003;
namespace CORN {
extern std::string &wstring_to_string(const std::wstring &wstr,std::string &str);
extern std::wstring &string_to_wstring(const std::string &str,std::wstring &wstr);
//______________________________________________________________________________
class Cell_shared_string
: public Cell_textual
{
public:
   nat32 row;
   nat16 col;
   const std::wstring &text;
public:
   inline Cell_shared_string(nat16  _row,nat16 _col,const std::wstring &_text)
      : row(_row)
      , col(_col)
      , text(_text)
      {}
   inline virtual nat32  get_row()                                         const { return row; }
   inline virtual nat32  get_col()                                         const { return col; }
   inline virtual const std::string  & set_string  (const std::string &value)  modification_ { return value; } // reader has no modification capabilities
   inline virtual const std::wstring & set_wstring (const std::wstring &value) modification_ { return value; } // reader has no modification capabilities
   inline virtual std::string  & get_string  (std::string &value)          const { wstring_to_string(text,value);return value;}
   inline virtual std::wstring & get_wstring (std::wstring &value)         const { value.assign(text);           return value;}
};
//______________________________________________________________________________
Cell_reader_BIFF::Cell_reader_BIFF
(const char *file_name)
//130829 (const CORN::File_name &file_name)
: Binary_record_file_dynamic
   (file_name//130829 .c_str()
   ,false  // not big body sizes// True if record header size field is 32bits
   //130313 ,true   //read_only
   ,std::ios_base::in                                                            //130313
   ,false  /* little endian big_endian */)
, dates_based_1904(true)
, last_formula_string_row(0)
, last_formula_string_col(0)
, current_sheet_index(0) , sheet0_encountered(false)
{}
//______________________________________________________________________________
uint32 Cell_reader_BIFF::read(Cell_receiver &receiver)
{  uint32 records_encountered = 0;
   Binary_file_interface  *binary_file = provide_binary_file();
   nat16 first_word = binary_file->read_nat16();
   nat32 skip_OLE2_document_header = 0x00000200;   // BOF_record_position
   // Most recent XLS files are OLE2 compound documents which have a 512 byte
   // OLE2 document header.

   if ((first_word != 0xD0CF) && (first_word != 0xCFD0))
      // verify this is an OLE2 Compound document
      // The full identifier string is actually  D0CF11E0A1B11AE1 (hex)
      skip_OLE2_document_header = 0; // In older XLS file the first record is as the beginning of the file
   binary_file->seek(skip_OLE2_document_header);


   // The first record must be a BOF record for all versions of BIFF (as of BIFF8)
   Binary_record_without_body *BOF_record_header = new Binary_record_without_body(*binary_file ,false);
   Record_code record_code = BOF_record_header->get_code();
   BIFF_rec_BOF *BOF_record = render_BIFF_BOF_record(record_code,BOF_record_header->get_length_in_file());

   maybe_Excel_2007_saved_as_2003 = false;
   if (!BOF_record)
   {  // I have encountered some XLS files which have a 1536 (0x600)
      // byte OLE header so try again skipping that many bytes
      nat32 skip_OLE2_document_header = 0x00000600;   // BOF_record_position
      binary_file->seek(skip_OLE2_document_header);

      // The first record must be a BOF record for all versions of BIFF (as of BIFF8)
      Binary_record_without_body *BOF_record_header = new Binary_record_without_body(*binary_file ,false);
      Record_code record_code = BOF_record_header->get_code();
      BOF_record = render_BIFF_BOF_record(record_code,BOF_record_header->get_length_in_file());
      maybe_Excel_2007_saved_as_2003 =  BOF_record != 0;
   }
   if (!BOF_record)
   {
      std::cerr << "This does not appear to be an Excel .XLS file." << std::endl;
   }
   BOF_record->read_body(*binary_file);
   format = BOF_record->get_format();
   delete BOF_record;
   for  (bool _at_eof = binary_file == NULL
        ;!_at_eof
        ; _at_eof = _at_eof | binary_file->at_eof())
   {  nat32 file_pos =  binary_file->tell(); //101205
      Binary_record_without_body *record_without_body = new Binary_record_without_body(*binary_file ,false);
      records_encountered += record_without_body != NULL;
      record_code = record_without_body->get_code();
      nat32 record_length = record_without_body->get_length_in_file();

/*
      // 101205 Claudio had a file saved as excel 2003 from 2007
      // that appears to have dropped a byte
      if (record_code == 0x8103)
      {  // This is just a hack.
         binary_file->seek(file_pos+5);
         record_without_body = new Binary_record_without_body(*binary_file ,false);
         records_encountered += record_without_body != NULL;
         record_code = record_without_body->get_code();
         record_length = record_without_body->get_length_in_file();
      };
*/

#ifdef DEBUG_CELL_READER
// The following few lines are for debugging
//file_pos =  binary_file->tell();
std::cout << std::dec << file_pos  << '\t'<< std::hex << record_code << '\t' << std::dec << record_length << "\n";
if (file_pos == 50669)
{
std::cout << "reached"<< "\n"; //100826 std::endl;  borland linker complians
}
#endif
      if ((record_code == 0) &&   // Record code 0 is a valid BIFF2 record (DIMENSION)
          ((record_length == 0) ||  // so we have to check the validity of the length.
           (record_length > format == BIFF8 ? 8224 : 2080) ))
           // BIFF records bodies  are always less than this size
           // so it longer then we need to abort
           // (I am finding some files where the file is getting reset with a large length this will handle that unusual case).
        _at_eof = true;
      else
      {  BIFF_record *record = render_BIFF_record(record_code,record_length,format);
         if (record)   // unrecognized record (not a cell record) so skip the body
         {  if (!read_and_process_record(receiver,record))
               delete record;
         } else binary_file->seek(record_length,ios::cur);
      }
      delete record_without_body;
   }
   return records_encountered;
}
//______________________________________________________________________________
bool Cell_reader_BIFF::read_and_process_record
(Cell_receiver &receiver
,BIFF_record *record)     // record needs to be a pointer because we do dynamic casting and don't want to throw exceptions
{  bool processed = true;
   record->read_body(*binary_file);
   Cell_numeric *numeric_cell = dynamic_cast<Cell_numeric *>(record);
   if (numeric_cell)
   {  BIFF578_rec_FORMULA *formula_rec =dynamic_cast<BIFF578_rec_FORMULA *>(record);
      if (formula_rec && formula_rec->is_string())
      {  // Most often formulas give number, but they can give strings or other
         // In the case of strings Excel stores a STRING record immediately after
         // the formula record, so save the cell coordinates for the string record
         last_formula_string_row = numeric_cell->get_row();
         last_formula_string_col = numeric_cell->get_col();
      } else
      processed = receiver.take_numeric(numeric_cell);
   } else
   {  Cell_textual *textual_cell = dynamic_cast<Cell_textual *>(record);
      if (textual_cell)
         processed =    receiver.take_textual(textual_cell);
      else
      {     processed = true;
            switch (record->get_code())
            {  case BIFF578_CODE_MULRK :
               {  BIFF578_rec_MULRK *multiple_RK = dynamic_cast<BIFF578_rec_MULRK *>(record);
                  if (multiple_RK)
                  for (int RK_i = 0; RK_i < multiple_RK->get_number_records(); RK_i++)
                  {
                     BIFF34578_rec_RK *rec_RK = new BIFF34578_rec_RK
                        (//BIFF34578_CODE_RK,
                        multiple_RK->row_index
                        ,multiple_RK->first_col_index+RK_i
                        ,multiple_RK->records[RK_i].ixfe
                        ,multiple_RK->records[RK_i].RK);
                     receiver.take_numeric(rec_RK);
                  }
               } break;
               case BIFF234578_CODE_1904 : // DATEMODE :
               {  BIFF234578_rec_1904 *date_mode = dynamic_cast<BIFF234578_rec_1904 *>(record);
                  if (date_mode)
                     dates_based_1904 = date_mode->is_data_mode_1904();
               } break;
               case BIFF8_CODE_SST :
               {  shared_string_table = dynamic_cast<BIFF8_rec_SST *>(record);
               } break;
               case BIFF8_CODE_LABELSST :
               {  BIFF8_rec_LABELSST *SST_label = dynamic_cast<BIFF8_rec_LABELSST *>(record);
                  if (SST_label)
                  {  const BIFF8_rec_SST::Item *SST_string = (const BIFF8_rec_SST::Item *)
                        shared_string_table->get_at(SST_label->get_shared_string_table_index());
                     Cell_shared_string *shared_string_cell = new Cell_shared_string
                        (SST_label->get_row(),SST_label->get_col(),*SST_string);
                     receiver.take_textual(shared_string_cell);
                  }
               } break;
               case BIFF2_CODE_STRING :
               {  const BIFF2_rec_STRING *string_rec =  dynamic_cast<BIFF2_rec_STRING *>(record);
                  if (string_rec)
                  {  BIFF2_rec_LABEL *label_rec= new BIFF2_rec_LABEL
                        (last_formula_string_row,last_formula_string_col,0,0,0,string_rec->text);
                     receiver.take_textual(label_rec);
                  } else processed = false;
               } break;
               case BIFF34578_CODE_STRING :
               {  const BIFF8_rec_STRING *string_rec =  dynamic_cast<BIFF8_rec_STRING *>(record);
                  if (string_rec)
                  {  BIFF8_rec_LABEL *label_rec= new BIFF8_rec_LABEL(last_formula_string_row,last_formula_string_col,0,string_rec->text);
                     receiver.take_textual(label_rec);
                  } else
                  {  const BIFF3457_rec_STRING *string_rec =  dynamic_cast<BIFF3457_rec_STRING *>(record);
                     if (string_rec)
                     {  BIFF3457_rec_LABEL *label_rec= new BIFF3457_rec_LABEL(last_formula_string_row,last_formula_string_col,0,string_rec->text);
                        receiver.take_textual(label_rec);
                     } else processed = false;
                  }
                  last_formula_string_row = 0;
                  last_formula_string_col = 0;
               } break;
               // case BIFF2_CODE_BOF :
               //case BIFF3_CODE_BOF
               //case BIFF4_CODE_BOF :
               case BIFF578_CODE_BOF :
               {  // I am currently assuming BOF records encountered are all sheets
                  // And that the sheets are in sequence
                  // What I should do is get the position of the record
                  // and match that with the bound sheet
                  // For BIFF 2-4 There is only one global BOF record and only one sheet so sheet index is always 0 
                  if (sheet0_encountered)
                     current_sheet_index += 1;
                  else
                     sheet0_encountered = true;
                  receiver.recognize_current_sheet_index(current_sheet_index);
               } break;
               default :
               {
                  const BIFF_rec_BOUNDSHEET_common *sheet = dynamic_cast<const BIFF_rec_BOUNDSHEET_common *>(record);
                  if (sheet) // This should pickup either  BIFF5_rec_BOUNDSHEET or BIFF8_rec_BOUNDSHEET
                  {  std::string sheet_name;
                     sheet->get_sheet_name(sheet_name);
                     receiver.recognize_current_sheet_name(sheet_name);
                  } else
                     processed = false;
               } break;

               // NYI if BOF record need to get the format
               // NYI case MULBLANK :

               // NYI In the case of a formula, we need to have to cell coordinate
               // because the next record is a STRING which will store the results
               // of the formula, this should allow us to get the value of the
               // formula result without having to actually compute it.
               // then it is a matter of generating a textual or numeric to send to the receiver.
         } // switch
      } // if textual
   } // if numeric
   return processed;
}
//______________________________________________________________________________
Binary_record *Cell_reader_BIFF::instanciate_record(Record_code code) const
{  // Note that this is only to implement instanciate_record,
   // we don't actually use instanciate_record in this program.
   return render_BIFF_record(code,0,BIFF8);
}
//______________________________________________________________________________
} // namespace CORN

