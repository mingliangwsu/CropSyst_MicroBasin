//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_header_field.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoInt16Edit"
#pragma link "AutoStringEdit"
#pragma link "AutoContainerComboBox"
#pragma link "AutoUnitsButton"
#pragma link "AutoLabeledEnumComboBox"
#pragma link "AutoUint16Edit"
#pragma link "AutoRadioGroup"
#pragma link "AutoCheckBox"
#pragma resource "*.dfm"
Theader_field_form *header_field_form;

//---------------------------------------------------------------------------
__fastcall Theader_field_form::Theader_field_form(TComponent* Owner)
   : TForm(Owner)
{
   checkbox_on_every_page->Top = 4;
} //---------------------------------------------------------------------------
void Theader_field_form::bind_to
(ED_tabular_file_format::Metadata_field *_field
,ED_tabular_file_format               *_format
,TListBox                              *_header_fields_listbox
)
{
   field  = _field;
   format = _format;
   header_fields_listbox = _header_fields_listbox;

   header_description_edit          ->bind_to(&field->description,0);
   header_worksheet_name_edit       ->bind_to(&field->worksheet,0);

   caption_text_edit                ->bind_to(&field->caption,0);
   caption_row_edit                 ->bind_to(&field->caption_row,0);
   caption_col_edit                 ->bind_to(&field->caption_col,0);

   header_field_row_edit            ->bind_to(&field->row_num,0);
   header_field_column_edit         ->bind_to(&field->col_num,0);
   header_precision_edit            ->bind_to(&field->precision,0);

   header_field_width               ->bind_to(&field->field_width,0);
   header_static_text_edit          ->bind_to(&field->static_text,0);

   header_data_radio                ->bind_to(&field->field_data_labeled,0);

   header_comment_index_edit        ->bind_to(&field->database_comment_index,0);
   header_description_index_edit    ->bind_to(&field->database_description_index,0);

   generating_application_variable_radios->bind_to(&field->generating_application_var_labeled,0);
   location_variable_radios         ->bind_to(&field->location_var_labeled,0);

   radiogroup_relative_to           ->bind_to(&field->relative_to_labeled,0);
   checkbox_on_every_page           ->bind_to(&field->every_page,0);


#ifdef NYI
060626 The following are not yet implemented,  will finish when I have more time.

   scalar_record_code_combobox      ->bind_to(&field->UED_scalar_record_code,0)

   header_timestep_format_combobox



/*______*/
/*______*/        // The following are for UED scalar records
/*______*/        Record_code       ;
/*______*/        UED_variable_code UED_scalar_variable_code;
/*______*/        UED_units_code    UED_scalar_units_code;
/*______*/        UED_units_code    UED_scalar_time_stamp;
/*______*/        uint8             UED_scalar_precision; // Used for output
/*______*/

   TAutoUnitsButton *header_units_button;
   TAutoInt16Edit *header_precision_edit;
   TAutoInt16Edit *header_UED_record_code_edit;
   TAutoInt16Edit *header_UED_variable_code_edit;
#endif
   show_hide_controls();
} //---------------------------------------------------------------------------

void __fastcall Theader_field_form::header_description_editChange(TObject *Sender)
{  if (header_fields_listbox)
      header_fields_listbox->Update();
}
//---------------------------------------------------------------------------
void Theader_field_form::show_hide_controls()
{
   Format_file_type format_file_type = format->format_file_type_labeled.get();
   bool can_have_caption =!((format_file_type == FILE_TYPE_dBase)
                          ||(format_file_type == FILE_TYPE_binary));
   bool is_spreadsheet_file_type = (format_file_type == FILE_TYPE_Excel) ||(format_file_type == FILE_TYPE_lotus123) ;
   bool is_text_file_type  = (format_file_type == FILE_TYPE_text);
   ED_tabular_file_format::Metadata_field::Field_data field_date_type =  field->field_data_labeled.get();;

   checkbox_on_every_page->Visible = is_text_file_type;


   // always visible   tabsheet_description;
   // always visible   tabsheet_header_position;
   header_field_position_worksheet_name_label->Visible = is_spreadsheet_file_type;
   header_worksheet_name_edit ->Visible = is_spreadsheet_file_type;
   header_static_text_edit    ->Visible = field_date_type  == ED_tabular_file_format::Metadata_field::FD_static_text;
   header_static_text_label   ->Visible = field_date_type  == ED_tabular_file_format::Metadata_field::FD_static_text;
   header_field_width_label   ->Visible = format_file_type == FILE_TYPE_text;
   header_field_width         ->Visible = format_file_type == FILE_TYPE_text;
   header_field_width_note    ->Visible = format_file_type == FILE_TYPE_text;

   tabsheet_header_caption                ->TabVisible = can_have_caption;
   bool has_caption = field->caption_row && field->caption_col;
   caption_caption_label   ->Visible = has_caption;
   caption_text_edit         ->Visible = has_caption;

   tabsheet_header_UED_scalar             ->TabVisible = field_date_type == ED_tabular_file_format::Metadata_field::FD_UED_scalar_data;
   tabsheet_header_UED_location_variable  ->TabVisible = field_date_type == ED_tabular_file_format::Metadata_field::FD_UED_location;
   tabsheet_header_UED_comment            ->TabVisible = field_date_type == ED_tabular_file_format::Metadata_field::FD_UED_general_comment;
   tabsheet_header_UED_description        ->TabVisible = field_date_type == ED_tabular_file_format::Metadata_field::FD_UED_database_description;
   tabsheet_header_UED_application        ->TabVisible = field_date_type == ED_tabular_file_format::Metadata_field::FD_UED_generating_application;
};

void __fastcall Theader_field_form::header_data_radioClick(TObject *Sender)
{
   show_hide_controls();
}
//---------------------------------------------------------------------------

