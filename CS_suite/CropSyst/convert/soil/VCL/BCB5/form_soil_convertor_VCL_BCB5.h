//---------------------------------------------------------------------------

#ifndef form_soil_convertor_VCL_BCB5H
#define form_soil_convertor_VCL_BCB5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>

#include "AdvDirectoryEdit.hpp"
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include "AutoInt16Edit.h"
#include "AutoStringEdit.h"
#include <ExtCtrls.hpp>
#include "StShlCtl.hpp"
//---------------------------------------------------------------------------
#include <corn/file_sys/dirname.h>
#include <STATSGO/soil_generator/soil_generator.h>
//#include <STATSGO/soil_convertor/STATSGO_soil_convertor.h>
class Tsoil_convertor_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *format_page_control;
   TTabSheet *TabSheet1;
   TTabSheet *chemflow_tabsheet;
   TLabel *Label1;
   TBitBtn *IBSNAT_import_button;
   TOpenDialog *ICASA_file_open;
   TTabSheet *STATSGO;
   TLabel *Label2;
   TLabel *Label4;
   TLabel *Label6;
   TGroupBox *STATSGO_groupbox_database_found;
   TRadioGroup *STATSGO_radiobutton_aggregation_option;
   TRadioGroup *STATSGO_radiobutton_mapunit_selection_mode;
   TPanel *Panel1;
   TAdvDirectoryEdit *destitation_directory_edit;
   TPanel *panel_bottom;
   TLabel *Label5;
   TBitBtn *close_button;
   TPanel *panel_statsgo_folder;
   TAdvDirectoryEdit *STATSGO_directory_edit;
   TPanel *panel_select_state;
   TEdit *STATSGO_edit_state;
   TGroupBox *STATSGO_groupbox_datum_selection;
   TGroupBox *STATSGO_groupbox_mapunit;
   TLabel *STATSGO_label_mapunit;
   TGroupBox *STATSGO_sequence_groupbox;
   TLabel *STATSGO_sequence_label;
   TButton *STATSGO_button_convert;
   TEdit *STATSGO_edit_mapunit;
   TEdit *edit_STATSGO_sequence;
   TBitBtn *button_explore;
   void __fastcall IBSNAT_import_button_onclick(TObject *Sender);
   void __fastcall destitation_directory_edit_onchange(TObject *Sender);
   void __fastcall STATSGO_directory_editChange(TObject *Sender);
   void __fastcall STATSGO_radiobutton_aggregation_optionClick(
          TObject *Sender);
   void __fastcall STATSGO_sequence_edit_onexit(TObject *Sender);
   void __fastcall STATSGO_button_convertClick(TObject *Sender);
   void __fastcall STATSGO_radiobutton_mapunit_selection_modeClick(
          TObject *Sender);
   void __fastcall button_exploreClick(TObject *Sender);
private:	// User declarations
   CORN::Directory_name destination_dir; // should be the current working directory
private: // STATSGO convertor
   int16           STATSGO_sequence_number;
   STATSGO::Map_unit_soil_generator  *STATSGO_soil_generator;
//   STATSGO::Soil_convertor  *STATSGO_soil_convertor;
public:		// User declarations
   __fastcall  Tsoil_convertor_form(TComponent* Owner);
   #include "form_soil_convertor_inc.h"

   void set_destination_dir(const_ASCIIz destination_dir);

   private:
   void show_hide_controls();
};
//---------------------------------------------------------------------------
extern PACKAGE Tsoil_convertor_form *soil_convertor_form;
//---------------------------------------------------------------------------
#endif
