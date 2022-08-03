//---------------------------------------------------------------------------

#ifndef form_soil_convertorH
#define form_soil_convertorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvDirectoryEdit.hpp"
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include "AdvFileNameEdit.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//130223#include <STATSGO/soil_generator/soil_generator.h>
#include "soil_convertor_engine.h"
/* moved
#ifdef USE_OS_FS
#include "corn/OS/directory_entry_name_logical.h"
#else
#include "corn/file_sys/smart_filename.h"
#endif
*/
//---------------------------------------------------------------------------
class Tsoil_convertor_form : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label4;
   TPanel *Panel2;
   TAdvDirectoryEdit *destitation_directory_edit;
   TBitBtn *button_explore;
   TPageControl *format_page_control;
   TTabSheet *TabSheet1;
   TLabel *Label1;
   TLabel *Label6;
   TBitBtn *IBSNAT_import_button;
   TTabSheet *chemflow_tabsheet;
   TLabel *Label2;
   TTabSheet *tabsheet_STATSGO2;
   TPanel *panel_bottom;
   TLabel *Label5;
   TBitBtn *close_button;
   TOpenDialog *ICASA_file_open;
   TAdvDirectoryEdit *editdir_destination;
   TScrollBox *ScrollBox1;
   TPanel *panel_statsgo_folder;
   TGroupBox *groupbox_mapunix_selection;
   TLabel *Label3;
   TLabel *Label7;
   TAdvFileNameEdit *filenameedit_DBF;
   TEdit *edit_specific_mapunits;
   TGroupBox *STATSGO_groupbox_database_found;
   TRadioGroup *STATSGO_radiobutton_aggregation_option;
   TAdvFileNameEdit *edit_mapunit_txt;
   TPanel *panel_STATSGO2_converting;
   TButton *button_STATSGO2_convert;
   TLabel *label_STATSGO2_curr_mukey;
   TCheckBox *checkbox_STATSGO2_continue;
   TProgressBar *progress_bar;
   TTabSheet *tabsheet_CanSIS_NSDB;
   TGroupBox *groupbox_CanSIS_soil_layer_table;
   TAdvFileNameEdit *filedit_CanSIS_NSDB;
   TLabel *Label8;
   TLabel *Label9;
   TButton *button_CanSIS_NSDB_convert;
   void __fastcall button_STATSGO2_convertClick(TObject *Sender);
   void __fastcall IBSNAT_import_buttonClick(TObject *Sender);
   void __fastcall edit_mapunit_txtChange(TObject *Sender);
   void __fastcall button_CanSIS_NSDB_convertClick(TObject *Sender);
   void __fastcall button_exploreClick(TObject *Sender);
   void __fastcall editdir_destinationChange(TObject *Sender);
   void __fastcall filenameedit_DBFChange(TObject *Sender);
   void __fastcall edit_specific_mapunitsChange(TObject *Sender);

private:	// User declarations
//   CORN::Directory_name destination_directory;
   Soil_convertor_engine soil_convertor_engine;

   //130225 moved to soil convertor engine   CORN_File_name_instance /*130224 CORN::Smart_file_name*/ STATSGO2_mapunit_txt_filename;
//   CORN::Directory_name  table_index_dirname;
public:		// User declarations
   __fastcall Tsoil_convertor_form(TComponent* Owner);
   #include "form_soil_convertor_inc.h"
   void set_destination_dir(const wchar_t *destination_dir);
};
//---------------------------------------------------------------------------
extern PACKAGE Tsoil_convertor_form *soil_convertor_form;
//---------------------------------------------------------------------------
#endif
