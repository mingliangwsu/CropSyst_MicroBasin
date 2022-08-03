//---------------------------------------------------------------------------

#ifndef form_delineation_layoutH
#define form_delineation_layoutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoCheckBox.h"
#include "AutoInt16Edit.h"
#include "AutoRadioGroup.h"
#include <ExtCtrls.hpp>
#include "AutoStringEdit.h"
#include <ComCtrls.hpp>
#include "AdvSelectors.hpp"
namespace CORN { class Delineation_layout; };
//---------------------------------------------------------------------------
class Tdelineation_layout_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *tabsheet_delimiting;
   TTabSheet *tabsheet_quotation;
   TTabSheet *TabSheet3;
   TAutoRadioGroup *column_delimit_mode_radiogroupbox;
   TAutoCheckBox *continuous_delimiter_checkbox;
   TGroupBox *delimiter_groupbox;
   TAutoCheckBox *delimiter_space_checkbox;
   TAutoCheckBox *delimiter_tab_checkbox;
   TAutoCheckBox *delimiter_comma_checkbox;
   TAutoCheckBox *delimiter_other_checkbox;
   TAutoInt16Edit *delimiter_other_edit;
   TButton *Button2;
   TAutoCheckBox *delimiter_semicolon_checkbox;
   TAutoRadioGroup *text_quote_mode_radiogroup;
   TLabel *Label1;
   TAutoStringEdit *edit_end_marker;
   TLabel *Label2;
   TLabel *Label3;
   TAutoStringEdit *edit_begin_marker;
   TLabel *Label4;
   TLabel *Label5;
   TAdvCharacterSelector *AdvCharacterSelector1;
   void __fastcall column_delimit_mode_radiogroupboxClick(TObject *Sender);
   void __fastcall delimiter_other_checkboxClick(TObject *Sender);
private:	// User declarations
   CORN::Delineation_layout *delineation_layout;
public:		// User declarations
   __fastcall Tdelineation_layout_form(TComponent* Owner);
   void  bind_to(CORN::Delineation_layout *i_delineation_layout);
   virtual void __fastcall Update();
   void  show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE Tdelineation_layout_form *delineation_layout_form;
//---------------------------------------------------------------------------
#endif
