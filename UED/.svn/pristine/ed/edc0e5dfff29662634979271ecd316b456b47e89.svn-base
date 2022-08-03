//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_sample.h"
#include <UED/convert/ED_tabular_format.h>
#include <corn/string/uiostring.h>
#include <UED/convert/ED_tabular_parser.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGridExcel"
#pragma link "AdvGridWorkbook"
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
Tsample_form *sample_form;
//---------------------------------------------------------------------------
__fastcall Tsample_form::Tsample_form(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Tsample_form::bind_to(ED_tabular_file_format *_format,const char *_sample_file_name)
{
   format = _format;
   sample_file_name = _sample_file_name;
};
//---------------------------------------------------------------------------
bool Tsample_form::update_sample_text_file_grid()
{
   ED_tabular_parser_text parser(*format);
   CORN::Text_list parsing_notes;
   bool parsable = parser.read(sample_file_name.c_str(),parsing_notes);
// NYN   string_grid_for_text->ColCount = known_colcount;

   // Now try to resize the grid columns to match the data
   int grid_col = 1;
   FOR_EACH_IN(column,CORN::Tabular_column,format->columns_1based,each_col)
   {  grid_col ++;
         int col_width_pixels = column->width *
            string_grid_for_text->FixedFont->Size;
         string_grid_for_text->ColWidths[grid_col] = col_width_pixels;
   } FOR_EACH_END(each_col);
   return parsable;
};
//---------------------------------------------------------------------------
void Tsample_form::update_sample_grid()
{

// Cell background color codes
// Beige  header field label
// Yellow header field data
// Darker Green  Column header units
// Light green column header caption
// Light gray  not relevent
// Dark gray extraneous
// Light blue detail line date field
// dark magenta station number
// light magenta station number
// White data

// Cell text color codes
// Dark gray not relevent
// Read unexpected text
// blue undelineated text


   if (!format) return; // should never happen, but just incase form editor calls this
   switch (format->format_file_type_labeled.get())
   {  case FILE_TYPE_text:  update_sample_text_file_grid() ;
         string_grid_for_text->Visible = true;
         string_grid_for_text->Top = 0;
         string_grid_for_text->Left = 0;
//          string_grid_for_text->->Align = alClient;
         workbookgrid_for_excel->Visible = False;
      break;
//NYI      case FILE_TYPE_Excel     :  update_sample_excel_grid() ; break;         format->sample_excel_filename   (CORN::Filtered_file_name )

//NYI      case FILE_TYPE_binary    :  update_sample_excel_grid() ; break;
//NYI      case FILE_TYPE_dBase     :  update_sample_dBase_grid() ; break;
//NYI      case FILE_TYPE_lotus123  :  update_sample_lotus123_grid() ; break;
//NYI      case xxxx:  update_sample_excel_grid() ; break;
//NYN default: FILE_TYPE_unknown
   };
};
//---------------------------------------------------------------------------
