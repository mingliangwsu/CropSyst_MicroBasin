//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#define ALL_MAP_UNITS      0
#define SPECIFIC_MAP_UNIT  1
#define SPECIFIC_COMPONENT 2

#include "form_soil_convertor_VCL_BCB5.h"
#include <ICASA/library/ICASA_common.h>
#include <ICASA/library/soil/ICASA_soil.h>
#include <CropSyst/cpp/soil/soil_param.h>
#include <corn/data_source/vv_file.h>
#include <common/soil/txtrhydr.h>
#include <STATSGO/soil_convertor/STATSGO_soil_convertor.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvDirectoryEdit"
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma link "AutoInt16Edit"
#pragma link "AutoStringEdit"
#pragma link "StShlCtl"
#pragma resource "*.dfm"
Tsoil_convertor_form *soil_convertor_form;
//---------------------------------------------------------------------------
__fastcall Tsoil_convertor_form::Tsoil_convertor_form(TComponent* Owner)
   : TForm(Owner)
   , destination_dir()
   , STATSGO_sequence_number(0)
//   , STATSGO_soil_generator(0)
//   , STATSGO_soil_convertor(0)
{
   set_destination_dir("C:\\Simulation\\Database\\Soil");
   //110131 now using standard edit STATSGO_sequence_edit->bind_to(&STATSGO_sequence_number,0);
/*110131 obsolete Now simply have Explore button
   #if ((__BCPLUSPLUS__ == xxx))
   shelllistview_destination = new TStShellListView(this)
   #else
   shelllistview_destination = new xxxx(this)
   #endif
   shelllistview_destination->Align = alClient;
*/
   STATSGO_directory_editChange(0); // Setup incase the default folder is already installed
   show_hide_controls();
}
//---------------------------------------------------------------------------
void Tsoil_convertor_form::set_destination_dir(const_ASCIIz destination_dir)
{
   destitation_directory_edit->Text = destination_dir;
   CORN::Smart_directory_name smart_destination_dir(destination_dir);
   smart_destination_dir.set_as_current_working_directory();
};
//---------------------------------------------------------------------------
void __fastcall Tsoil_convertor_form::IBSNAT_import_button_onclick(TObject *Sender)
{  handle_IBSNAT_import_button_onclick();
}
//---------------------------------------------------------------------------
void __fastcall Tsoil_convertor_form::destitation_directory_edit_onchange(TObject *Sender)
{  set_destination_dir(destitation_directory_edit->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall Tsoil_convertor_form::STATSGO_directory_editChange(TObject *Sender)
{
   bool state_2_digit_code_entered = STATSGO_edit_state->Text.Length() == 2;
   STATSGO_groupbox_database_found->Visible = state_2_digit_code_entered;
   if (!state_2_digit_code_entered) return; // This must be a 2 digit code

   CORN::Smart_directory_name STATSGO_state_dir(STATSGO_edit_state->Text.c_str());
   STATSGO_state_dir.set_path(STATSGO_directory_edit->Text.c_str());

   bool STATSGO_stat_dir_exists = STATSGO_state_dir.exists();
   STATSGO_groupbox_database_found->Visible = STATSGO_stat_dir_exists;
   if (!STATSGO_stat_dir_exists)
   {
      Application->MessageBox("This directory does not contain the subdirectory and file spatial\layer.dbf","layer.dbf file not found",MB_OK);
   };
}
//---------------------------------------------------------------------------

void __fastcall Tsoil_convertor_form::STATSGO_radiobutton_aggregation_optionClick(TObject *Sender)
{
   show_hide_controls();
}
//---------------------------------------------------------------------------

void __fastcall Tsoil_convertor_form::STATSGO_sequence_edit_onexit(TObject *Sender)
{
   show_hide_controls();
   STATSGO_sequence_number = atoi(edit_STATSGO_sequence->Text.c_str());

   // NYI could also check that the number is with in the range for this MUI
}
//---------------------------------------------------------------------------
void __fastcall Tsoil_convertor_form::STATSGO_button_convertClick(TObject *Sender)
{
//080303   if (!STATSGO_soil_generator) return;
   CORN::Smart_directory_name destination_dir_name(destitation_directory_edit->Text.c_str());
   uint32 sequences_converted = 0;

   switch (STATSGO_radiobutton_aggregation_option->ItemIndex)
   {
      case 0 : // Extract map unit sequences
      {
         // if (!STATSGO_soil_convertor)
         STATSGO::Soil_convertor STATSGO_soil_convertor(STATSGO_directory_edit->Text.c_str(),destitation_directory_edit->Text.c_str());
         switch (STATSGO_radiobutton_mapunit_selection_mode->ItemIndex)
         {
            case ALL_MAP_UNITS : // process all map units
            {
               sequences_converted = STATSGO_soil_convertor.process_state(STATSGO_edit_state->Text.c_str(),0);
            } break;
            case SPECIFIC_MAP_UNIT:
            {
               sequences_converted =  STATSGO_soil_convertor.convert_map_unit(STATSGO_edit_mapunit->Text.c_str());
            } break;
            case SPECIFIC_COMPONENT:
            {
               sequences_converted = STATSGO_soil_convertor.convert_sequence(STATSGO_edit_mapunit->Text.c_str(),(uint16) STATSGO_sequence_number);

            } break;
         }; // switch MU selection mode

      } break;
      case 1 : // Generate pseudosoil
      {
//         if (!STATSGO_soil_generator)
//            STATSGO_soil_generator = new STATSGO::Map_unit_soil_generator(STATSGO_directory_edit->Text.c_str());
         STATSGO::Map_unit_soil_generator STATSGO_soil_generator(STATSGO_directory_edit->Text.c_str());
         switch (STATSGO_radiobutton_mapunit_selection_mode->ItemIndex)
         {
            case ALL_MAP_UNITS : // process all map units
            {
               STATSGO_soil_generator.process_state(STATSGO_edit_state->Text.c_str(),0);
            } break;
            case SPECIFIC_MAP_UNIT:
            {
               STATSGO_soil_generator.add_map_unit(STATSGO_edit_mapunit->Text.c_str(),0 /*no table generation, only CropSyst files*/ );
            } break;
            // case SPECIFIC_COMPONENT: { } break;  Not applicable in aggregation mode
         }; // switch MU selection mode
      } break;
   }; // switch aggregation option
   destination_dir_name.invoke_viewer();
}
//---------------------------------------------------------------------------

void __fastcall Tsoil_convertor_form::STATSGO_radiobutton_mapunit_selection_modeClick(TObject *Sender)
{
   if (STATSGO_radiobutton_mapunit_selection_mode->ItemIndex == SPECIFIC_COMPONENT)
       STATSGO_radiobutton_aggregation_option->ItemIndex = 0; // Aggregation is not an option
   show_hide_controls();
}
//---------------------------------------------------------------------------
void Tsoil_convertor_form::show_hide_controls()
{
   STATSGO_button_convert ->Visible = (STATSGO_sequence_number > 0) ||
      STATSGO_radiobutton_mapunit_selection_mode->ItemIndex < SPECIFIC_COMPONENT;
//      (STATSGO_radiobutton_aggregation_option->ItemIndex == 1);

   STATSGO_groupbox_datum_selection ->Visible = STATSGO_radiobutton_mapunit_selection_mode->ItemIndex > ALL_MAP_UNITS;
      STATSGO_groupbox_mapunit      ->Visible = STATSGO_radiobutton_mapunit_selection_mode->ItemIndex >= SPECIFIC_MAP_UNIT;
      STATSGO_sequence_groupbox     ->Visible = STATSGO_radiobutton_mapunit_selection_mode->ItemIndex >= SPECIFIC_COMPONENT;
   STATSGO_radiobutton_aggregation_option ->Visible =  STATSGO_radiobutton_mapunit_selection_mode->ItemIndex != SPECIFIC_COMPONENT;



//obs   bool process_one_mapunit = (STATSGO_radiobutton_mapunit_selection_mode->ItemIndex == 0);
//obs   STATSGO_groupbox_mapunit ->Visible = process_one_mapunit || (STATSGO_radiobutton_aggregation_option->ItemIndex == 0);
//obs   STATSGO_sequence_groupbox->Visible = process_one_mapunit;

//obs   STATSGO_sequence_groupbox->Visible = (STATSGO_radiobutton_aggregation_option->ItemIndex == 0);
//   STATSGO_radiobutton_mapunit_selection_mode->Visible = (STATSGO_radiobutton_aggregation_option->ItemIndex > 0);

};
//---------------------------------------------------------------------------
void __fastcall Tsoil_convertor_form::button_exploreClick(TObject *Sender)
{  handle_explore_button_onclick();
/*111024 moved
   CORN::File_name soil_convertor_filename(ParamStr(0).c_str());
   CORN::Directory_name CropSyst_dirname;
   soil_convertor_filename.get_path(CropSyst_dirname);
   CORN::Directory_name CS_suite_dirname;
   CropSyst_dirname.get_path(CS_suite_dirname);
   std::string explorer_command("\"");
   explorer_command.append(CS_suite_dirname);
   explorer_command.append("\\CS_explorer.exe\" ");
   explorer_command.append("\"");
   explorer_command.append(destitation_directory_edit->Text.c_str());
   explorer_command.append("\"");
   WinExec(explorer_command.c_str(),SW_NORMAL);
*/
}
//---------------------------------------------------------------------------
#include "form_soil_convertor_common.cpp"
