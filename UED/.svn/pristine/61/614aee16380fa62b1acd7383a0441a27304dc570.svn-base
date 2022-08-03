//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_tabular_format_editor.h"
#include "form_delineation_layout.h"
#include "form_column_field.h"
#include "form_header_field.h"
#include <corn/tabular/tabular_format_identifier.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoDateButton"
#pragma link "AutoStringEdit"
#pragma link "AutoCheckBox"
#pragma link "AutoContainerListBox"
#pragma link "AutoInt16Edit"
#pragma link "AutoLabeledEnumComboBox"
#pragma link "AutoUnitsButton"
#pragma link "AdvGrid"
#pragma link "AdvGridWorkbook"
#pragma link "AutoFileEditBar"
#pragma link "BaseGrid"
#pragma link "AdvMemo"
#pragma link "AutoRadioGroup"
#pragma resource "*.dfm"
Ttabular_format_editor_form *tabular_format_editor_form;
//---------------------------------------------------------------------------
__fastcall Ttabular_format_editor_form::Ttabular_format_editor_form(TComponent* Owner)
   : TForm(Owner)
   , header_field_form(0)
{
}
//---------------------------------------------------------------------------
void Ttabular_format_editor_form::bind_to(ED_tabular_file_format *i_format,Tparameter_file_form *_parameter_file_form)
{
   format = i_format;
   parameter_file_form = _parameter_file_form;
   #define NO_HELP_YET 0
   // Information
   defined_by_edit                  ->bind_to(&(format->defined_by         ),NO_HELP_YET);
   defined_date_button              ->bind_to(&(format->defined_date)       ,"Definition date (usually today)",false,NO_HELP_YET);

   // File type
   format_file_type_combo           ->bind_to(&(format->format_file_type_labeled ),NO_HELP_YET);
   big_endian_checkbox              ->bind_to(&(format->big_endian               ),NO_HELP_YET);
   carriage_return_line_feed_checkbox               ->bind_to(&(format->carriage_return_line_feed                ),NO_HELP_YET);
   fortran_carriage_control_checkbox->bind_to(&(format->FORTRAN_carriage_control ),NO_HELP_YET);

   checkbox_paginated                        ->bind_to(&(format->paginated               ),NO_HELP_YET);
   checkbox_column_headers_every_page        ->bind_to(&(format->column_headers_every_page               ),NO_HELP_YET);


   edit_begin_marker ->bind_to(&(format->begin_marker),NO_HELP_YET);
   edit_end_marker   ->bind_to(&(format->end_marker)  ,NO_HELP_YET);

   // Metastructure:
//050321 Add here begin_data_maker  (character string)
//050321 Add here end_data_maker  (character string)

   //Header fields
   {
      header_terminator_character_edit ->bind_to(&(format->header_terminator       ),NO_HELP_YET);
      header_fields_listbox            ->bind_to(&(format->metadata_fields_1based            ),NO_HELP_YET);
      header_field_form = new Theader_field_form(this);
      header_field_form->Parent = header_field_scrollbox;
      header_field_form->Show();
      header_field_form->Top = 0;
      header_field_form->Left = 0;
      header_field_form->BorderStyle = bsNone;
      header_field_form->Align= alClient;
   }
   // Column headers: Text and spreadsheet format
   column_header_start_row_relative_radiogroup ->bind_to(&(format->column_headers_delineation.relative_to_labeled),NO_HELP_YET);
   column_header_start_row_edit     ->bind_to(&(format->column_headers_delineation.start_row_1_based       ),NO_HELP_YET);
   column_header_rows_edit          ->bind_to(&(format->column_headers_delineation.rows               ),NO_HELP_YET);
   column_header_units_row_edit     ->bind_to(&(format->column_headers_delineation.units_row_offset   ),NO_HELP_YET);
   column_header_units_rows_edit    ->bind_to(&(format->column_headers_delineation.units_rows         ),NO_HELP_YET);
   column_header_units_parenthesis_checkbox->bind_to(&(format->column_headers_delineation.units_parenthesis ),NO_HELP_YET);

   edit_col_headers_text->bind_to(&(format->column_header_static ),NO_HELP_YET);

   column_header_delineation_form = new Tdelineation_layout_form(this);
   column_header_delineation_form->bind_to(&(format->column_headers_delineation));
   column_header_delineation_form->Parent = column_headers_delineation_tabsheet;
   column_header_delineation_form->Show();
   column_header_delineation_form->Top = 0;
   column_header_delineation_form->Left = 0;
   column_header_delineation_form->BorderStyle = bsNone;
   column_header_delineation_form->Align= alClient;
   columns_listbox                  ->bind_to(&(format->columns_1based                  ),NO_HELP_YET);

/*
   // Column headers: Text format
   //Columns text format options
*/
   {
   column_field_form = new Tcolumn_field_form(this);
// column_field_form->bind_to(xxx); can't bind until selected
   column_field_form->Parent = column_scrollbox;
   column_field_form->Show();
   column_field_form->Top = 0;
   column_field_form->Left = 0;
   column_field_form->Width = column_scrollbox->Width;
   column_field_form->Height= column_scrollbox->Height;
   column_field_form->BorderStyle = bsNone;
   column_field_form->Align = alClient;
   }
   // Detail lines page

   data_start_row_relative_radiogroup  ->bind_to(&(format->detail_lines_delineation.relative_to_labeled),NO_HELP_YET);
   data_start_row_edit                 ->bind_to(&(format->detail_lines_delineation.start_row_1_based       ),NO_HELP_YET);
   records_per_UED_record_edit         ->bind_to(&(format->records_per_UED_record       ),NO_HELP_YET);
   time_step_edit                      ->bind_to(&(format->detail_lines_delineation.time_step             ),NO_HELP_YET);
   record_type_step_units_button       ->bind_to(&(format->detail_lines_delineation.time_step_units_enum.smart_units_code       ),true,false);
   detail_line_delineation_form = new Tdelineation_layout_form(this);
   detail_line_delineation_form->bind_to(&(format->detail_lines_delineation));
   detail_line_delineation_form->Parent = detail_lines_delineation_tabsheet;
   detail_line_delineation_form->Show();
   detail_line_delineation_form->Top = 0;
   detail_line_delineation_form->Left = 0;
   detail_line_delineation_form->BorderStyle = bsNone;
   detail_line_delineation_form->Align= alClient;

   edit_ID_column->bind_to(&(format->ID_column_number_1based),NO_HELP_YET);
   edit_name_column->bind_to(&(format->name_column_number_1based),NO_HELP_YET);
/*
//NYI    ->bind_to(&(format->variable_order_labeled       ),NO_HELP_YET);
*/

//   sample_excel_filebar->bind_to(&(format->sample_excel_filename),0);

}
//---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::Update()
{
   defined_by_edit->Update();
   format_file_type_combo->Update();
   big_endian_checkbox->Update();
   carriage_return_line_feed_checkbox->Update();
   fortran_carriage_control_checkbox->Update();
   checkbox_paginated                        ->Update();
   checkbox_column_headers_every_page        ->Update();

   edit_begin_marker->Update();
   edit_end_marker->Update();

   columns_listbox->Update();

   // Metastructure

//050321 Add begin_data_maker_edit->Update()
//050321 Add end_data_maker->Update()

   header_terminator_character_edit->Update();
   header_fields_listbox->Update();

   column_header_start_row_edit->Update();
   column_header_rows_edit->Update();
   column_header_units_row_edit->Update();
   column_header_units_rows_edit->Update();
   column_header_delineation_form->Update();
   detail_line_delineation_form->Update();
   data_start_row_edit->Update();
   records_per_UED_record_edit->Update();
   time_step_edit->Update();

   record_type_step_units_button->Update();

   edit_ID_column->Update();
   edit_name_column->Update();

   edit_col_headers_text->Update();

   // 060223 The following switch is obsolete delete once I check the  record_type_step_units_button works for this
   /*
   switch (format->detail_lines_delineation.time_step_units)
   {
      case  UT_second   : record_time_step_combobox->Text = "0x1600 Second"; break;
      case  UT_minute   : record_time_step_combobox->Text = "0x1700 Minute"; break;
      case  UT_hour     : record_time_step_combobox->Text = "0x1800 Hour"  ; break;
      case  UT_day      : record_time_step_combobox->Text = "0x1900 Day"   ; break;
      case  UT_year     : record_time_step_combobox->Text = "0x1A00 Year"  ; break;
   };
   */

//NYI   if (local_sample_form) local_sample_form->update_sample_grid();
   show_hide_controls();
};
void __fastcall Ttabular_format_editor_form::record_time_step_combobox_onchange(TObject *Sender)
{  // 060223 This method is obsolete delete once I check the  record_type_step_units_button works for this
   // Need to read the time step  units code and set the selected UED code for the timestep
   int variable_code =0;
//   sscanf(record_time_step_combobox_obsolete ->Text.c_str(),"0x%x",&variable_code);
   if (format)
      format->detail_lines_delineation.time_step_units_enum.set_int32((Units_code)variable_code);
}
//---------------------------------------------------------------------------
void Ttabular_format_editor_form::show_hide_controls()
{
   if (format)
   {
      switch (format->format_file_type_labeled.get())
      {
         case FILE_TYPE_unknown  :
                                    tabsheet_header_fields->TabVisible=true;
                                    tabsheet_column_headers->TabVisible=true;
                                    tabsheet_parsing->TabVisible = true;
                                    checkbox_paginated->Visible = false;
         break;
         case FILE_TYPE_text     :
                                    tabsheet_header_fields->TabVisible=true;
                                    tabsheet_column_headers->TabVisible=true;
                                    tabsheet_parsing->TabVisible = true;
                                    checkbox_paginated->Visible = true;
         break;
         case FILE_TYPE_binary   :
                                    tabsheet_header_fields->TabVisible=false; // May be true
                                    tabsheet_column_headers->TabVisible=false;// May be true
                                    tabsheet_parsing->TabVisible = true; // Because we may want to skip to some point in the binary file
                                    checkbox_paginated->Visible = false;
         break;
         case FILE_TYPE_dBase    :
                                    tabsheet_header_fields->TabVisible=false;
                                    tabsheet_column_headers->TabVisible=false;
                                    tabsheet_parsing->TabVisible = false;
                                    checkbox_paginated->Visible = false;
         break;
         case FILE_TYPE_lotus123 :
                                    tabsheet_header_fields->TabVisible=true;
                                    tabsheet_column_headers->TabVisible=true;
                                    tabsheet_parsing->TabVisible = true; // May want to skip cells
                                    checkbox_paginated->Visible = false;
         break;
         case FILE_TYPE_Excel    :
                                    tabsheet_header_fields->TabVisible=true;
                                    tabsheet_column_headers->TabVisible=true;
                                    tabsheet_parsing->TabVisible = true; // May want to skip cells
                                    checkbox_paginated->Visible = false;
         break;
         default :
                                    tabsheet_header_fields->TabVisible=true;
                                    tabsheet_column_headers->TabVisible=true;
                                    tabsheet_parsing->TabVisible = true; // May want to skip cells
                                    checkbox_paginated->Visible = false;
         break;
      };

      // tabsheet_columns is always visible
      // tabsheet_detail_lines is always visible

      big_endian_checkbox->Visible                 = format->format_file_type_labeled.get() == FILE_TYPE_binary;
      text_file_type_groupbox->Visible             = format->format_file_type_labeled.get() == FILE_TYPE_text;
//      sample_excel_tabsheet->TabVisible            = format->format_file_type_labeled.get() == FILE_TYPE_Excel;
//      sample_text_tabsheet->TabVisible             = format->format_file_type_labeled.get() == FILE_TYPE_text;
      header_fields_terminator_groupbox->Visible   = format->format_file_type_labeled.get() == FILE_TYPE_text;

      markers_panel->Visible = format->relative_to_labeled.get() == DATA_RELATIVE;

      columns_carriage_control_note->Visible = format->FORTRAN_carriage_control;
   };
};
void __fastcall Ttabular_format_editor_form::format_file_type_combo_onchange(TObject *Sender)
{
   if (format) format->reset_for_file_type();
   show_hide_controls();
}
//---------------------------------------------------------------------------

void __fastcall Ttabular_format_editor_form::sample_excel_filebarChange(TObject *Sender)
{
   const char *sample_filename = format->sample_excel_filename.c_str();
/*
   sample_excel_workbook->AddSheet("Phenology");
   sample_excel_workbook->Grid->LoadFromXLSSheet(sample_filename, "Phenology");
   sample_excel_workbook->AddSheet("Biomass LAI");
   sample_excel_workbook->Grid->LoadFromXLSSheet(sample_filename, "Biomass LAI");
*/

//   AdvStringGrid1-> LoadFromXLSSheet(sample_filename, "Phenology");
}
//---------------------------------------------------------------------------
bool __fastcall Ttabular_format_editor_form::header_field_edit(ED_tabular_file_format::Metadata_field *field_to_add)
{  bool edit_ok = false;
   Theader_field_form *header_field_form = new Theader_field_form(this);
   header_field_form->bind_to(field_to_add,format);

   header_fields_listbox->Update();
   return edit_ok; //
}  //---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::header_field_add_button_onclick(TObject *Sender)
{  if (!format) return;
   ED_tabular_file_format::Metadata_field *field_to_add = new ED_tabular_file_format::Metadata_field;
   if (field_to_add)
      format->metadata_fields_1based.append(field_to_add); // relinquish to format->header_fields_1based
   header_fields_listbox->Update();
   int metadata_field_count = format->metadata_fields_1based.count();
   header_fields_listbox->ItemIndex = metadata_field_count - 1;     // focus on the added column and call
   header_fields_listbox_onclick(Sender);
//      header_fields_listbox_onclick
//      header_field_form->bind_to(field_to_add,format,header_fields_listbox);
//   }; // unable to allocate (should never happen)
}  //---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::header_fields_listbox_onclick(TObject *Sender)
{  ED_tabular_file_format::Metadata_field *field_to_edit = (ED_tabular_file_format::Metadata_field *)
   format->metadata_fields_1based.get_at(header_fields_listbox->ItemIndex);
   if (field_to_edit)
   {  header_field_scrollbox->Visible = true;
      header_field_form->bind_to(field_to_edit,format,header_fields_listbox);
   };
}//---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::header_field_delete_button_onclick(TObject *Sender)
{  header_fields_listbox->delete_selected();
   header_field_scrollbox->Visible = false;
   header_fields_listbox_onclick(Sender);
}  //---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::column_up_down_buttonClick(TObject *Sender, TUDBtnType Button)
{  switch (Button)
   { case Comctrls::btNext : columns_listbox->move_selected_to_first(); break;
     case Comctrls::btPrev : columns_listbox->move_selected_to_last();  break;
   };
} //---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::column_add_button_onclick(TObject *Sender)
{  ED_tabular_file_format::Column *added_column = new ED_tabular_file_format::Column;
   if (added_column)
      format->columns_1based.append(added_column);
   columns_listbox->Update();
   int column_count =  format->columns_1based.count();
   columns_listbox->ItemIndex = column_count - 1;     // focus on the added column and call
   columns_listbox_onclick(Sender);
} //---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::column_delete_button_onclick(TObject *Sender)
{  columns_listbox->delete_selected();
   column_scrollbox->Visible = false;
}  //---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::columns_listbox_onclick(TObject *Sender)
{
   ED_tabular_file_format::Column *column_to_edit = (ED_tabular_file_format::Column *)
   format->columns_1based.get_at(columns_listbox->ItemIndex);
   if (column_to_edit)
   {
      column_scrollbox->Visible = true;
      column_field_form->bind_to(column_to_edit,format,columns_listbox);
   };
}
//---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::sample_file_button_onclick(TObject *Sender)
{
#ifdef NYI
   if (!format) return;
   if (sample_file_opendialog->Execute())
   {
      Tabular_format_identifier format_identifier;
      if (!local_sample_form) local_sample_form = new Tsample_form(this);
      local_sample_form->Show();

      local_sample_form->bind_to(format,sample_file_opendialog->FileName.c_str());

      format_identifier.identify
         (*format
         ,sample_file_opendialog->FileName.c_str()
         ,local_sample_form
         );
      Update();
   };
#endif
}
//---------------------------------------------------------------------------

void __fastcall Ttabular_format_editor_form::fortran_carriage_control_checkboxClick(TObject *Sender)
{
   show_hide_controls();
}
//---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::button_ID_columnClick(TObject *Sender)
{
   format->ID_column_number_1based = columns_listbox->ItemIndex+1;
   edit_ID_column->Update();
   edit_name_column->Update();
}
//---------------------------------------------------------------------------
void __fastcall Ttabular_format_editor_form::button_name_columnClick(TObject *Sender)
{
   format->name_column_number_1based = columns_listbox->ItemIndex+1;
   edit_name_column->Update();
}
//---------------------------------------------------------------------------

