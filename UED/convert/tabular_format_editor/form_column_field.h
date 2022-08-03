//---------------------------------------------------------------------------

#ifndef form_column_fieldH
#define form_column_fieldH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include "AutoCheckBox.h"
#include "AutoInt16Edit.h"
#include "AutoRadioGroup.h"
#include "AutoStringEdit.h"
#include "AutoLabeledEnumComboBox.h"
#include "AutoUnitsButton.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <UED/convert/ED_tabular_format.h>
//---------------------------------------------------------------------------
class Tcolumn_field_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TTabSheet *TabSheet2;
   TTabSheet *TabSheet3;
   TTabSheet *TabSheet4;
   TTabSheet *tabsheet_fixed_width;
   TLabel *Label7;
   TAutoInt16Edit *column_start_edit;
   TLabel *Label8;
   TLabel *Label9;
   TAutoInt16Edit *column_width_edit;
   TLabel *label_variable;
   TComboBox *column_UED_variable_code_combobox;
   TAutoUnitsButton *column_units_code_button;
   TLabel *Label14;
   TAutoCheckBox *records_date_checkbox;
   TLabel *Label10;
   TGroupBox *GroupBox1;
   TLabel *column_label_period;
   TAutoInt16Edit *column_period_edit;
   TLabel *column_label_period_note;
   TLabel *Label12;
   TPageControl *PageControl2;
   TTabSheet *TabSheet6;
   TTabSheet *TabSheet7;
   TTabSheet *TabSheet8;
   TAutoStringEdit *column_caption_edit;
   TAutoStringEdit *column_label_edit;
   TAutoStringEdit *column_units_description_edit;
   TTabSheet *tabsheet_sheet;
   TMemo *Memo1;
   TMemo *Memo2;
   TMemo *Memo3;
   TPageControl *PageControl3;
   TTabSheet *TabSheet9;
   TLabel *Label1;
   TAutoRadioGroup *column_statistic_radios;
   TLabel *Label17;
   TAutoInt16Edit *column_columns_edit;
   TAutoCheckBox *column_spread_over_columns_checkbox;
   TLabel *Label16;
   TAutoRadioGroup *radiogroup_column_data_type;
   TPanel *panel_datatype;
   TScrollBox *scrollbox_datatype;
   TLabel *Label15;
   TLabel *Label11;
   TLabel *Label23;
   TGroupBox *groupbox_precision;
   TLabel *Label4;
   TAutoInt16Edit *column_precision_edit;
   TGroupBox *GroupBox2;
   TAutoStringEdit *missing_value_edit;
   TGroupBox *groupbox_column_sheet_name;
   TAutoStringEdit *edit_column_sheet_name;
   TLabel *Label24;
   TLabel *Label2;
   TGroupBox *groupbox_column_number;
   TLabel *Label3;
   TAutoInt16Edit *edit_column_number;
   TLabel *Label5;

   void __fastcall column_label_edit_onchange(TObject *Sender);
   void __fastcall column_UED_variable_code_comboboxChange(TObject *Sender);
   void __fastcall records_date_checkboxClick(TObject *Sender);
   void __fastcall column_width_editExit(TObject *Sender);
   void __fastcall column_precision_editExit(TObject *Sender);
   void __fastcall radiogroup_column_data_typeClick(TObject *Sender);

private:	// User declarations
   ED_tabular_file_format::Column   *column;
   ED_tabular_file_format           *tabular_file_format;
   TListBox                         *columns_listbox;
   int16 field_width_as_int16;
   int16 precision_as_int16;
public:		// User declarations
   __fastcall Tcolumn_field_form(TComponent* Owner);
   void bind_to
   (ED_tabular_file_format::Column *_column
   ,ED_tabular_file_format  *_tabular_file_format
   ,TListBox *_columns_listbox = 0);
   // If  _columns_listbox is specified, the list box is updated when the column name/label changes
   void show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE Tcolumn_field_form *column_field_form;
//---------------------------------------------------------------------------
#endif
