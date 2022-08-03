//---------------------------------------------------------------------------

#include <vcl.h>
#pragma package(smart_init)
#pragma hdrstop
//#include "STATSGO2/soil_generator.h"
#include "USDA/NRCS/soil/generator/soil_generator.h"

#include "form_soil_convertor.h"
#include "cropsyst/source/cs_filenames.h"
#include "corn/data_source/vv_file.h"
#include "CropSyst/source/soil/soil_param.h"
#include "corn/OS/Windows/redirect_IO_to_console.h"
#ifdef USE_OS_FS
#  include "corn/OS/file_system_engine.h"
#else
#  include "corn/file_sys/dirname.h"
#endif
/*130225 moved
#include "corn/data_source/dbase_datasrc.h"
*/
//______________________________________________________________________________
#pragma link "AdvDirectoryEdit"
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma link "AdvFileNameEdit"
#pragma resource "*.dfm"
Tsoil_convertor_form *soil_convertor_form;
char *latitude_fieldname = "latitude";
char *longitude_fieldname= "longitude";
//______________________________________________________________________________
__fastcall Tsoil_convertor_form::Tsoil_convertor_form(TComponent* Owner)
: TForm(Owner)
{
   edit_mapunit_txtChange(0);
   CORN_Directory_name_instance cwd;
   editdir_destination->Text =cwd.c_str();
}
//______________________________________________________________________________
nat32 export_all_map_units(STATSGO2::Soil_generator &generator)
{  nat32 count = 0;
   //11-10-25 continue here
   return count;
};
//______________________________________________________________________________
TLabel *ref_label_STATSGO2_curr_mukey     = 0;
TCheckBox *ref_checkbox_STATSGO2_continue = 0;
TProgressBar *ref_progress_bar = 0;;
//______________________________________________________________________________
void __fastcall Tsoil_convertor_form::button_STATSGO2_convertClick(TObject *Sender)
{
   button_STATSGO2_convert->Visible = false;
   ref_label_STATSGO2_curr_mukey = label_STATSGO2_curr_mukey;
   ref_checkbox_STATSGO2_continue = checkbox_STATSGO2_continue;
   //unused ref_progress_bar = progress_bar;

   soil_convertor_engine.convert_STATSGO2_to_CropSyst(STATSGO_radiobutton_aggregation_option->ItemIndex);
   button_STATSGO2_convert->Visible = true;
}
//______________________________________________________________________________
void Tsoil_convertor_form::set_destination_dir(const wchar_t *destination_dir)
{  destitation_directory_edit->Text = destination_dir;
   CORN_Directory_name_instance destination_dir_name(destination_dir);
   #ifdef USE_OS_FS
   CORN::OS::file_system_engine.set_current_working_directory(destination_dir_name);
   #else
   destination_dir_name.set_as_current_working_directory();
   #endif
};
//______________________________________________________________________________
void __fastcall Tsoil_convertor_form::IBSNAT_import_buttonClick(TObject *Sender)
{  handle_IBSNAT_import_button_onclick();
}
//______________________________________________________________________________
#include "form_soil_convertor_common.cpp"
void __fastcall Tsoil_convertor_form::edit_mapunit_txtChange(TObject *Sender)
{
   soil_convertor_engine.STATSGO2_mapunit_txt_filename.set_wstr(edit_mapunit_txt->Text.c_str());
   STATSGO_groupbox_database_found->Visible =
   #ifdef USE_OS_FS
      CORN::OS::file_system_engine.exists(soil_convertor_engine.STATSGO2_mapunit_txt_filename);
   #else
      soil_convertor_engine.STATSGO2_mapunit_txt_filename.exists();
   #endif
}
//______________________________________________________________________________
void __fastcall Tsoil_convertor_form::button_CanSIS_NSDB_convertClick(TObject *Sender)
{  handle_CanSIS_NSDB_button_onclick();
}
//_2013-02-23__________________________________________________________________/
void __fastcall Tsoil_convertor_form::button_exploreClick(TObject *Sender)
{  handle_explore_button_onclick();
}
//_2013-02-24__________________________________________________________________/
void __fastcall Tsoil_convertor_form::editdir_destinationChange(TObject *Sender)
{  soil_convertor_engine.destination_directory.set_wstr(editdir_destination->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall Tsoil_convertor_form::filenameedit_DBFChange(TObject *Sender)
{  soil_convertor_engine.dBase_table_filename.set_wstr(filenameedit_DBF->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall Tsoil_convertor_form::edit_specific_mapunitsChange(TObject *Sender)
{
  CORN::Unicodez_to_string(edit_specific_mapunits->Text.c_str(),soil_convertor_engine.edit_specific_mapunits);
}
//---------------------------------------------------------------------------

