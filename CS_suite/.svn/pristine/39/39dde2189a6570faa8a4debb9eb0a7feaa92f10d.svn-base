//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_planting_event.h"
#include "CropSyst/source/rot_param.h"
#include "CropSyst/source/cs_event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma link "AdvFileNameEdit"
#pragma link "RNAutoDateButton"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma resource "*.dfm"
Tplanting_event_form *planting_event_form;
//______________________________________________________________________________
__fastcall Tplanting_event_form::Tplanting_event_form(TComponent* Owner)
: TForm(Owner)
,sowing_event  (0)
,sowing_op     (0)
{}
//_constructor______________________________________________________2018-03-26_/
void Tplanting_event_form::bind_to
(CropSyst::Sowing_event *sowing_event_
,nat8                    CropSyst_version)                                       //180525
{
/* this was here got get help
   parameter_form =  _parameter_form;
*/
   sowing_event =    sowing_event_;

   if (sowing_event)
   {
      sowing_op = &sowing_event->
         provide_sowing_operation();                                             //130416
         //130416 get_sowing_operation();

      if (sowing_op)
      {

         /*obsolete now simply using file selector
         if (project_database_directory)
         {  project_database_crop_directory        = new CORN::Smart_directory_name(project_database_directory->provide_crop_directory(false));
            project_database_management_directory  = new CORN::Smart_directory_name(project_database_directory->provide_management_directory(false));
         };
         if (scenario_database_directory)
         {  scenario_database_crop_directory       = new CORN::Smart_directory_name(scenario_database_directory->provide_crop_directory(false));
            scenario_database_management_directory = new CORN::Smart_directory_name(scenario_database_directory->provide_management_directory(false));
         };
         */
         planting_date_button      ->bind_to(&(sowing_event->begin_sync),/*"Sowing target date",*/false /* V4_HELP_URL(HELP_P_rotation_planting_date)*/);
         radiogroup_mode  ->bind_to(&(sowing_op->sowing_date_mode_labeled)                 /* V4_HELP_URL(HELP_P_rotation_sowing_date_mode)*/);

         fileedit_crop->Text = sowing_op->crop_filename.c_str();                 //180326
         DragAcceptFiles(fileedit_crop->Handle,true);                            //180326

/*180326 obsolete
         crop_database_dropdownfilebar   ->bind_to
         (&(sowing_op->crop_filename)
         ,"Crop file"
         ,"this parameter is obsolete"
         ,"\\Crop\\"    // i_database_marker
         ,master_database_crop_directory    // I.e. "C:\Simulation\Database\Soil"
         ,project_database_crop_directory   // I.e. "C:\Simulation\projects\database\Soil"
         ,scenario_database_crop_directory  // I.e. "C:\Simulation\projects\Scenarios\senario1\database\Soil"
         V4_HELP_URL(HELP_P_rotation_crop)
         ,0 // NYI CORN::Validation_status   *i_status = 0
         ,0 // NYI CORN::Smart_file_name     *i_validation_filename = 0
         );
         crop_database_dropdownfilebar->set_editor
            (CS::Suite_directory->CropSyst().crop_editor_executable().c_str(),"");
         DragAcceptFiles(crop_database_dropdownfilebar->Handle,true);
*/



         fileedit_management->Text = sowing_op->management_filename.c_str();    //180326
         DragAcceptFiles(fileedit_management->Handle,true);                      //180326
/*180326 obsolete
         management_database_dropdownfilebar   ->bind_to
         (&(sowing_op->management_filename)
         ,"Management file"
         ,"this parameter is obsolete"
         ,"\\Management\\"    // i_database_marker
         ,master_database_management_directory    // I.e. "C:\Simulation\Database\Soil"
         ,project_database_management_directory   // I.e. "C:\Simulation\projects\database\Soil"
         ,scenario_database_management_directory  // I.e. "C:\Simulation\projects\Scenarios\senario1\database\Soil"
          V4_HELP_URL(HELP_P_rotation_management)
         ,0 // NYI CORN::Validation_status   *_status = 0
         ,0 // NYI CORN::Smart_file_name     *_validation_filename = 0
         );
         management_database_dropdownfilebar->set_editor
             (CS::Suite_directory->CropSyst().management_editor_executable().c_str(),"");
         DragAcceptFiles(management_database_dropdownfilebar->Handle,true);
         // sowing conditions
*/
         edit_delay_after_precip ->bind_to(&(sowing_op->p_delay_after_precip)       /* V4_HELP_URL(HELP_P_rotation_sow_delay_after_precip)*/);
         edit_appreciable_precip ->bind_to(&(sowing_op->p_appreciable_precip_mm)    /* V4_HELP_URL(HELP_P_rotation_sow_appreciable_precip)*/);
         edit_min_required_PAW   ->bind_to(&(sowing_op->p_sowing_min_PAW)           /* V4_HELP_URL(HELP_P_rotation_sow_min_required_PAW)*/);
         edit_max_required_PAW   ->bind_to(&(sowing_op->p_sowing_max_PAW)           /* V4_HELP_URL(HELP_P_rotation_sow_max_required_PAW)*/);
         edit_typical_days_emerge->bind_to(&(sowing_op->p_expected_days_to_emerge)  /* V4_HELP_URL(HELP_P_rotation_sow_expected_days_to_emerge)*/);
         edit_temperature_days   ->bind_to(&(sowing_op->p_sowing_avg_temp)          /* V4_HELP_URL(HELP_P_rotation_sow_temperature_5_days)*/);

         edit_temperature_days->Caption =
            (CropSyst_version < 5)
               ?  L"5 day mean temperature required for sowing"
               : L"15 day mean temperature required for sowing";

         radiogroup_temperature_evaluation_mode->bind_to(&(sowing_op->sowing_date_mode_labeled) /*V4_HELP_URL(HELP_P_rotation_sow_temperature_evaluation)*/);
         { // Seeding option
            edit_seeding_rate    ->bind_to(&(sowing_op->seeding_parameters.p_rate_seeds     )/*V4_HELP_URL(HELP_P_rotation_seed_application_rate)*/);
            edit_emergence_rate  ->bind_to(&(sowing_op->seeding_parameters.p_emergence_rate )/*V4_HELP_URL(HELP_P_rotation_seed_emergence_rate)*/);
            edit_sowing_depth    ->bind_to(&(sowing_op->seeding_parameters.p_sowing_depth   )/*V4_HELP_URL(HELP_P_rotation_sowing_depth)*/);
         }

#ifdef obsolete
         edit_delay_after_precip ->bind_to(&(sowing_op->v_delay_after_precip)        /*     V4_HELP_URL(HELP_P_rotation_sow_delay_after_precip)*/);
         edit_appreciable_precip ->bind_to(&(sowing_op->v_appreciable_precip_mm)          V4_HELP_URL(HELP_P_rotation_sow_appreciable_precip));
         edit_min_required_PAW   ->bind_to(&(sowing_op->v_sowing_min_PAW)                 V4_HELP_URL(HELP_P_rotation_sow_min_required_PAW));
         edit_max_required_PAW   ->bind_to(&(sowing_op->v_sowing_max_PAW)                 V4_HELP_URL(HELP_P_rotation_sow_max_required_PAW));
         edit_expected_days_to_emerge  ->bind_to(&(sowing_op->v_expected_days_to_emerge)V4_HELP_URL(HELP_P_rotation_sow_expected_days_to_emerge));
         edit_temperature_5_days       ->bind_to(&(sowing_op->v_sowing_avg_temp)       V4_HELP_URL(HELP_P_rotation_sow_temperature_5_days));
         radiogroup_temperature_evaluation_mode->bind_to(&(sowing_op->sowing_date_mode_labeled)V4_HELP_URL(HELP_P_rotation_sow_temperature_evaluation));
         { // Seeding option
            edit_seeding_rate_edit    ->bind_to(&(sowing_op->seeding_parameters.v_rate_seeds     )V4_HELP_URL(HELP_P_rotation_seed_application_rate));
            edit_emergence_rate_edit  ->bind_to(&(sowing_op->seeding_parameters.v_emergence_rate )V4_HELP_URL(HELP_P_rotation_seed_emergence_rate));
            edit_sowing_depth_edit    ->bind_to(&(sowing_op->seeding_parameters.v_sowing_depth   )V4_HELP_URL(HELP_P_rotation_sowing_depth));
         }
#endif





//NYI dont forget to add plant_by_date 171116


      }
   }
   /* Not sure if still needed
   radiogroup_mode_OnClick(0); //180326 sowing_date_radiogroup_onclick(0);
   */
   groupbox_delay_conditions->Visible = radiogroup_mode->ItemIndex > 0;
}
//_bind_to__________________________________________________________2018-03-26_/
void __fastcall Tplanting_event_form::button_OKClick(TObject *Sender)
{  sowing_op->description.brief.assign("");
   sowing_op->description.brief.append("crop:");
   std::wstring name_buffer;                                                     //140124
   sowing_op->crop_filename.append_name_with_extension_to(name_buffer);          //140124_120625
   CORN::append_wstring_to_string(name_buffer,sowing_op->description.brief);     //140124
   sowing_op->description.brief.append(" | management:");
   sowing_op->management_filename.append_name_with_extension_to(name_buffer);    //140124_120625
   CORN::append_wstring_to_string(name_buffer,sowing_op->description.brief);
}
//_button_OKClick___________________________________________________2018-03-26_/
void __fastcall Tplanting_event_form::button_helpClick(TObject *Sender)
{
/*NYI
   CORN::OS::File_name* sowing_event_docs =
      parameter_file_form->provide_program_directory().Documentation()
      .find_document_filename_cstr("sowing_event.htm");
   if (sowing_event_docs)
   {
      CORN::OS::file_system_engine.view_file(*sowing_event_docs);
      delete sowing_event_docs;
   }
*/
}
//---------------------------------------------------------------------------
extern bool edit_parameter_file
(const wchar_t *filename // qualified_with_extension
,const_UnicodeZ editor_name  // without .exe extension
,const_UnicodeZ option);
//______________________________________________________________________________
void __fastcall Tplanting_event_form::fileedit_cropChange(TObject *Sender)
{  sowing_op->crop_filename.set_wstr(fileedit_crop->Text.c_str()); }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::fileedit_managementChange(TObject *Sender)
{  sowing_op->management_filename.set_wstr(fileedit_management->Text.c_str()); }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::fileedit_cropDblClick(TObject *Sender)
{  edit_parameter_file(fileedit_crop->Text.c_str(),L"crop_editor",L""); }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::fileedit_cropLabelClick(TObject *Sender)
{  edit_parameter_file(fileedit_crop->Text.c_str(),L"crop_editor",L""); }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::fileedit_managementDblClick(TObject *Sender)
{  edit_parameter_file(fileedit_management->Text.c_str(),L"management_editor",L""); }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::fileedit_managementLabelClick(TObject *Sender)
{  edit_parameter_file(fileedit_management->Text.c_str(),L"management_editor",L""); }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::radiogroup_modeClick(TObject *Sender)
{  groupbox_delay_conditions->Visible = radiogroup_mode->ItemIndex > 0; }
//---------------------------------------------------------------------------
void __fastcall Tplanting_event_form::BitBtn1Click(TObject *Sender)
{
   // continue here: set relative filenames for management and rotation
}
//---------------------------------------------------------------------------

