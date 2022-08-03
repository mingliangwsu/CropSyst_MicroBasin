//---------------------------------------------------------------------------

#ifndef form_header_fieldH
#define form_header_fieldH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "AutoInt16Edit.h"
#include "AutoStringEdit.h"
#include "AutoContainerComboBox.h"
#include "AutoUnitsButton.h"
#include "AutoLabeledEnumComboBox.h"
#include "AutoUint16Edit.h"
#include "AutoRadioGroup.h"
#include <ComCtrls.hpp>
#include "AutoCheckBox.h"
//---------------------------------------------------------------------------

#include <UED/convert/ED_tabular_format.h>

class Theader_field_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *tabsheet_description;
   TAutoStringEdit *header_description_edit;
   TAutoRadioGroup *header_data_radio;
   TTabSheet *tabsheet_header_position;
   TLabel *header_field_position_worksheet_name_label;
   TLabel *header_field_width_label;
   TLabel *header_row_label;
   TLabel *header_col_label;
   TLabel *header_static_text_label;
   TLabel *header_field_width_note;
   TLabel *row_one_based_note;
   TLabel *header_column_note;
   TLabel *header_row_note;
   TAutoStringEdit *header_worksheet_name_edit;
   TAutoUint16Edit *header_field_width;
   TAutoUint16Edit *header_field_row_edit;
   TAutoUint16Edit *header_field_column_edit;
   TAutoStringEdit *header_static_text_edit;
   TTabSheet *tabsheet_header_caption;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *caption_caption_label;
   TLabel *Label2;
   TLabel *Label6;
   TAutoUint16Edit *caption_row_edit;
   TAutoUint16Edit *caption_col_edit;
   TAutoStringEdit *caption_text_edit;
   TTabSheet *tabsheet_header_UED_scalar;
   TLabel *header_UED_scalar_record_code_label;
   TLabel *header_UED_scalar_variable_label;
   TLabel *header_UED_scalar_units_label;
   TLabel *header_UED_scalar_time_stamp_label;
   TAutoLabeledEnumComboBox *scalar_record_code_combobox;
   TAutoInt16Edit *header_UED_variable_code_edit;
   TAutoUnitsButton *header_units_button;
   TAutoContainerComboBox *header_timestep_format_combobox;
   TTabSheet *tabsheet_header_UED_location_variable;
   TAutoRadioGroup *location_variable_radios;
   TTabSheet *tabsheet_header_UED_comment;
   TLabel *comment_index_label;
   TAutoUint16Edit *header_comment_index_edit;
   TTabSheet *tabsheet_header_UED_description;
   TLabel *description_index_label;
   TAutoUint16Edit *header_description_index_edit;
   TTabSheet *tabsheet_header_UED_application;
   TLabel *header_UED_application_note;
   TAutoRadioGroup *generating_application_variable_radios;
   TAutoRadioGroup *radiogroup_relative_to;
   TAutoCheckBox *checkbox_on_every_page;
   TLabel *header_UED_scalar_precision_label;
   TAutoUint16Edit *header_precision_edit;
   void __fastcall header_description_editChange(TObject *Sender);
   void __fastcall header_data_radioClick(TObject *Sender);
private:	// User declarations
   ED_tabular_file_format                *format;
   ED_tabular_file_format::Metadata_field  *field;
   TListBox *header_fields_listbox ;
public:		// User declarations
   __fastcall Theader_field_form(TComponent* Owner);
   void bind_to(ED_tabular_file_format::Metadata_field *_field,ED_tabular_file_format *_format,TListBox *_header_fields_listbox  = 0);
   void show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE Theader_field_form *header_field_form;
//---------------------------------------------------------------------------
#endif
