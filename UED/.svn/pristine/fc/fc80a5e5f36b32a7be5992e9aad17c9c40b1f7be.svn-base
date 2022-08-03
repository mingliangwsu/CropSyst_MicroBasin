//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_delineation_layout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoCheckBox"
#pragma link "AutoInt16Edit"
#pragma link "AutoRadioGroup"
#pragma link "AutoStringEdit"
#pragma link "AdvSelectors"
#pragma resource "*.dfm"
#include <corn/tabular/delineation.h>
Tdelineation_layout_form *delineation_layout_form;
//---------------------------------------------------------------------------
__fastcall Tdelineation_layout_form::Tdelineation_layout_form(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void  Tdelineation_layout_form::bind_to(CORN::Delineation_layout *i_delineation_layout)
{
   delineation_layout = i_delineation_layout;
#define NO_HELP_YET 0
   continuous_delimiter_checkbox    ->bind_to(&(delineation_layout->continuous_delimiter     ),NO_HELP_YET);
   delimiter_space_checkbox         ->bind_to(&(delineation_layout->delimiter_space          ),NO_HELP_YET);
   delimiter_tab_checkbox           ->bind_to(&(delineation_layout->delimiter_tab            ),NO_HELP_YET);
   delimiter_comma_checkbox         ->bind_to(&(delineation_layout->delimiter_comma          ),NO_HELP_YET);
   delimiter_semicolon_checkbox     ->bind_to(&(delineation_layout->delimiter_semicolon      ),NO_HELP_YET);
   delimiter_other_checkbox         ->bind_to(&(delineation_layout->delimiter_other          ),NO_HELP_YET);
   delimiter_other_edit             ->bind_to(&(delineation_layout->other_delimiter_16       ),NO_HELP_YET);
   text_quote_mode_radiogroup       ->bind_to(&(delineation_layout->text_quote_mode_labeled  ),NO_HELP_YET);
   column_delimit_mode_radiogroupbox->bind_to(&(delineation_layout->delimit_mode_labeled     ),NO_HELP_YET);
   edit_begin_marker                ->bind_to(&(delineation_layout->begin_marker             ) NO_HELP_YET);
   edit_end_marker                  ->bind_to(&(delineation_layout->end_marker             ),NO_HELP_YET);
};
void __fastcall Tdelineation_layout_form::Update()
{
   continuous_delimiter_checkbox    ->Update();
   delimiter_space_checkbox         ->Update();
   delimiter_tab_checkbox           ->Update();
   delimiter_comma_checkbox         ->Update();
   delimiter_semicolon_checkbox     ->Update();
   delimiter_other_checkbox         ->Update();
   delimiter_other_edit             ->Update();
   text_quote_mode_radiogroup       ->Update();
   column_delimit_mode_radiogroupbox->Update();
   edit_begin_marker                ->Update();
   edit_end_marker                  ->Update();
   show_hide_controls();
};
void __fastcall Tdelineation_layout_form::column_delimit_mode_radiogroupboxClick(
      TObject *Sender)
{
   show_hide_controls();
}
//---------------------------------------------------------------------------

void  Tdelineation_layout_form::show_hide_controls()
{
   bool show_character_delimiter_option = delineation_layout->delimit_mode_labeled.get() == CORN::Delineation_layout::DELIMIT_character;
   continuous_delimiter_checkbox->Visible = show_character_delimiter_option;
   delimiter_groupbox->Visible = show_character_delimiter_option;

   delimiter_other_edit->Visible = delineation_layout->delimiter_other ;
};
void __fastcall Tdelineation_layout_form::delimiter_other_checkboxClick(TObject *Sender)
{
   show_hide_controls();
}
//---------------------------------------------------------------------------

