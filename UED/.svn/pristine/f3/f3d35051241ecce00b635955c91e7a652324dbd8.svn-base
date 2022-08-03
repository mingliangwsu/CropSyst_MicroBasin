//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "form_column_field.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoCheckBox"
#pragma link "AutoInt16Edit"
#pragma link "AutoRadioGroup"
#pragma link "AutoStringEdit"
#pragma link "AutoLabeledEnumComboBox"
#pragma link "AutoUnitsButton"
#pragma resource "*.dfm"
Tcolumn_field_form *column_field_form;
//---------------------------------------------------------------------------
__fastcall Tcolumn_field_form::Tcolumn_field_form(TComponent* Owner)
   : TForm(Owner)
   ,columns_listbox(0)
{}
//---------------------------------------------------------------------------
void Tcolumn_field_form::bind_to
(ED_tabular_file_format::Column *_column
,ED_tabular_file_format  *_tabular_file_format
,TListBox *_columns_listbox)
{
   column = _column;
   tabular_file_format = _tabular_file_format;
   columns_listbox = _columns_listbox;

   // Continue here
   column_caption_edit           ->bind_to(&(column->caption) ,0);
   column_label_edit             ->bind_to(&(column->short_name),0);
   column_units_description_edit ->bind_to(&(column->units_caption),0);
   radiogroup_column_data_type   ->bind_to(&(column->data_type_labeled),0);
   column_start_edit             ->bind_to(&(column->start_1based),0);  // This edit shares with Sheet edit_column_number start_1based

   field_width_as_int16 = column->field_width;
   column_width_edit             ->bind_to(&(field_width_as_int16),0);
   precision_as_int16 = column->precision;
   column_precision_edit         ->bind_to(&(precision_as_int16),0);

   char var_code_hex[10];
   itoa(column->smart_variable_code.get(),var_code_hex,16);
   Ustring xvar_code("0x");
   xvar_code.append(var_code_hex);
   column_UED_variable_code_combobox->Text = xvar_code.c_str();
// currently bound by hand   column_UED_variable_code_combobox->bind_to(&(column->xxxxx),0);
   column_units_code_button            ->bind_to(&(column->units.smart_units_code),true,true);
   column_spread_over_columns_checkbox ->bind_to(&(column->spread_over_columns),0);
   column_columns_edit                 ->bind_to(&(column->spread_columns),0);
   column_statistic_radios             ->bind_to(&(column->statistic_labeled),0);
   records_date_checkbox               ->bind_to(&(column->record_date),0);
   column_period_edit                  ->bind_to(&(column->period),0);

   missing_value_edit   ->bind_to(&(column->missing_value),0);
   edit_column_sheet_name->bind_to(&(column->sheet),0);
   edit_column_number   ->bind_to(&(column->start_1based),0);    // This edit shares with Fixed width column_start_edit start_1based

   show_hide_controls();
};
//---------------------------------------------------------------------------
void Tcolumn_field_form::show_hide_controls()
{  // Designation page always show
   //    caption Always show
   //    label Always show
   //    preferred units label Always show

   // Variable page always show
   //    UED variable code always show (unless period levels are used)
   //    units code always show        (unless period levels are used)
   //    record's data always show     (unless period levels are used)
   //    period level show only if period levels are used.

   // Data type page Always show
   //    data type always show

   Format_file_type format_file_type = tabular_file_format->format_file_type_labeled.get();

   bool fixed_width_relevent = (format_file_type ==FILE_TYPE_text) &&
   ((tabular_file_format->column_headers_delineation.delimit_mode_labeled.get() == Delineation_layout::DELIMIT_fixed_width )
    ||
    (tabular_file_format->detail_lines_delineation.delimit_mode_labeled.get() == Delineation_layout::DELIMIT_fixed_width )
    );

   bool precision_is_relevent = (format_file_type == FILE_TYPE_dBase) || (format_file_type == FILE_TYPE_lotus123)
   || (format_file_type == FILE_TYPE_Excel)
   || fixed_width_relevent
   || (column->data_type_labeled.get() == DT_float32)
   || (column->data_type_labeled.get() == DT_float64);
   groupbox_precision->Visible = precision_is_relevent;

   label_variable->Visible = !(column->record_date);
   column_UED_variable_code_combobox->Visible = !(column->record_date);

   // Fixed width page
   tabsheet_fixed_width->TabVisible = fixed_width_relevent;

   // Advanced page  currently always show, but could limit to CropSyst mode.
   // Worksheet
   tabsheet_sheet->TabVisible = (format_file_type == FILE_TYPE_Excel);
};
//---------------------------------------------------------------------------
void __fastcall Tcolumn_field_form::column_label_edit_onchange(TObject *Sender)
{  if (columns_listbox)
      columns_listbox->Update();
}
//---------------------------------------------------------------------------
void __fastcall Tcolumn_field_form::column_UED_variable_code_comboboxChange(TObject *Sender)
{  //read the frst word of xxx->Text and convert from hex to variable code
   // strtoul recognizes  0x  prefix
   column->smart_variable_code.set(strtoul(column_UED_variable_code_combobox->Text.c_str(),0,16));
}
//---------------------------------------------------------------------------
void __fastcall Tcolumn_field_form::records_date_checkboxClick(TObject *Sender)
{  show_hide_controls();
}
//---------------------------------------------------------------------------
void __fastcall Tcolumn_field_form::column_width_editExit(TObject *Sender)
{  column->field_width = field_width_as_int16;
}
//---------------------------------------------------------------------------
void __fastcall Tcolumn_field_form::column_precision_editExit(TObject *Sender)
{  column->precision = precision_as_int16;
}
//---------------------------------------------------------------------------
void __fastcall Tcolumn_field_form::radiogroup_column_data_typeClick(TObject *Sender)
{  show_hide_controls();
}
//---------------------------------------------------------------------------

