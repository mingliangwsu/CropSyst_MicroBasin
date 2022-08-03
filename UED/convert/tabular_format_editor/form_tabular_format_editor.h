//---------------------------------------------------------------------------

#ifndef form_tabular_format_editorH
#define form_tabular_format_editorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoDateButton.h"
#include "AutoStringEdit.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "AutoCheckBox.h"
#include "AutoContainerListBox.h"
#include "AutoInt16Edit.h"
#include "AutoLabeledEnumComboBox.h"
#include "AutoUnitsButton.h"
#include "AdvGrid.hpp"
#include "AdvGridWorkbook.hpp"
#include "AutoFileEditBar.h"
#include "BaseGrid.hpp"
#include <Grids.hpp>
#include "AdvMemo.hpp"
#include <ExtCtrls.hpp>
#include "AutoRadioGroup.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <ued/convert/ED_tabular_format.h>
//NYI #include "form_sample.h"
//---------------------------------------------------------------------------
//Forward declarations
class Tdelineation_layout_form;
class Theader_field_form;
class Tcolumn_field_form;
class Tparameter_file_form;

//---------------------------------------------------------------------------


class Ttabular_format_editor_form: public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl_TDF_editor;
   TTabSheet *tabsheet_information;
   TTabSheet *tabsheet_file_type;
   TTabSheet *tabsheet_header_fields;
   TTabSheet *TabSheet4;
   TTabSheet *tabsheet_columns;
   TTabSheet *tabsheet_detail_lines;
   TLabel *Label1;
   TAutoStringEdit *defined_by_edit;
   TLabel *Label19;
   TAutoDateButton *defined_date_button;
   TLabel *Label20;
   TLabel *Label21;
   TLabel *format_file_type_label;
   TAutoLabeledEnumComboBox *format_file_type_combo;
   TAutoCheckBox *big_endian_checkbox;
   TGroupBox *text_file_type_groupbox;
   TAutoCheckBox *carriage_return_line_feed_checkbox;
   TAutoCheckBox *fortran_carriage_control_checkbox;
   TButton *header_field_add_button;
   TAutoContainerListBox *header_fields_listbox;
   TButton *header_field_delete_button;
   TGroupBox *header_fields_terminator_groupbox;
   TLabel *Label23;
   TLabel *Label24;
   TAutoInt16Edit *header_terminator_character_edit;
   TLabel *Label27;
   TPageControl *PageControl2;
   TTabSheet *tabsheet_column_headers;
   TTabSheet *column_headers_delineation_tabsheet;
   TLabel *Label25;
   TLabel *Label26;
   TButton *Button7;
   TAutoContainerListBox *columns_listbox;
   TButton *Button5;
   TPageControl *PageControl3;
   TTabSheet *tabsheet_text_and_spreadsheet_format;
   TLabel *Label12;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label18;
   TAutoInt16Edit *data_start_row_edit;
   TAutoInt16Edit *records_per_UED_record_edit;
   TAutoInt16Edit *time_step_edit;
   TAutoUnitsButton *record_type_step_units_button;
   TTabSheet *detail_lines_delineation_tabsheet;
   TUpDown *column_up_down_button;
   TScrollBox *column_scrollbox;
   TScrollBox *header_field_scrollbox;
   TAutoRadioGroup *data_start_row_relative_radiogroup;
   TOpenDialog *sample_file_opendialog;
   TLabel *Label3;
   TButton *sample_file_button;
   TLabel *columns_carriage_control_note;
   TButton *Button1;
   TButton *button_ID_column;
   TLabel *Label13;
   TAutoInt16Edit *edit_ID_column;
   TButton *button_name_column;
   TAutoInt16Edit *edit_name_column;
   TTabSheet *tabsheet_parsing;
   TAutoRadioGroup *AutoRadioGroup1;
   TPanel *markers_panel;
   TLabel *label_begin_marker;
   TAutoStringEdit *edit_begin_marker;
   TLabel *label_end_marker;
   TAutoStringEdit *edit_end_marker;
   TLabel *Label14;
   TLabel *Label30;
   TLabel *Label28;
   TLabel *Label29;
   TLabel *Label31;
   TAutoCheckBox *checkbox_paginated;
   TLabel *Label33;
   TRadioGroup *RadioGroup1;
   TLabel *Label22;
   TGroupBox *groupbox_col_headers_text;
   TGroupBox *groupbox_col_headers_start_row;
   TAutoRadioGroup *column_header_start_row_relative_radiogroup;
   TAutoInt16Edit *column_header_start_row_edit;
   TLabel *Label4;
   TGroupBox *groupbox_col_headers_rows;
   TAutoInt16Edit *column_header_rows_edit;
   TLabel *Label6;
   TLabel *Label7;
   TGroupBox *groupbox_col_headers_units;
   TLabel *Label8;
   TAutoInt16Edit *column_header_units_row_edit;
   TLabel *Label9;
   TLabel *Label32;
   TLabel *Label10;
   TAutoInt16Edit *column_header_units_rows_edit;
   TLabel *Label11;
   TAutoCheckBox *column_header_units_parenthesis_checkbox;
   TAutoCheckBox *checkbox_column_headers_every_page;
   TAutoStringEdit *edit_col_headers_text;
   TLabel *Label2;

   void __fastcall record_time_step_combobox_onchange(TObject *Sender);
   void __fastcall format_file_type_combo_onchange(TObject *Sender);
   void __fastcall sample_excel_filebarChange(TObject *Sender);
   void __fastcall header_field_add_button_onclick(TObject *Sender);
   void __fastcall header_field_delete_button_onclick(TObject *Sender);
   void __fastcall column_up_down_buttonClick(TObject *Sender,TUDBtnType Button);
   void __fastcall column_add_button_onclick(TObject *Sender);
   void __fastcall column_delete_button_onclick(TObject *Sender);
   void __fastcall columns_listbox_onclick(TObject *Sender);
   void __fastcall header_fields_listbox_onclick(TObject *Sender);
   void __fastcall sample_file_button_onclick(TObject *Sender);
   void __fastcall fortran_carriage_control_checkboxClick(TObject *Sender);
   void __fastcall button_ID_columnClick(TObject *Sender);
   void __fastcall button_name_columnClick(TObject *Sender);

private:	// User declarations
   ED_tabular_file_format       *format;
   Tdelineation_layout_form      *column_header_delineation_form;
   Tdelineation_layout_form      *detail_line_delineation_form;
   Theader_field_form            *header_field_form;
   Tcolumn_field_form            *column_field_form;
   uint16                         column_headers_start_row; // The delineation is 32bit but I don't have a 32bit int edit yet
   Tparameter_file_form          *parameter_file_form;
//NYI   Tsample_form                  *local_sample_form;

public:		// User declarations
   __fastcall Ttabular_format_editor_form(TComponent* Owner);
   void bind_to(ED_tabular_file_format *i_format,Tparameter_file_form *_parameter_file_form);
   virtual void __fastcall Update();
   inline virtual TPageControl *get_main_page_control() const { return PageControl_TDF_editor;};
private:
   bool __fastcall header_field_edit(ED_tabular_file_format::Metadata_field *field_to_add);
   void show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE Ttabular_format_editor_form *tabular_format_editor_form;
//---------------------------------------------------------------------------
#endif
