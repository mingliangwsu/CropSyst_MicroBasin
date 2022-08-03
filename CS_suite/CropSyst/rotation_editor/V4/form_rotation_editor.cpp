//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "form_rotation_editor.h"
#include "form_planting_event.h"
#include "CropSyst/source/rot_param.h"
#include "GUI/parameter/form_param_file.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RNAutoContainerCheckListBox"
#pragma link "RNAutoIntegerEdit"
#pragma resource "*.dfm"
Trotation_editor_form *rotation_editor_form;
//---------------------------------------------------------------------------
__fastcall Trotation_editor_form::Trotation_editor_form(TComponent* Owner)
: TForm(Owner)
, rotation(0)
{  Application->HintHidePause = 8000;                                            //030514
}
//---------------------------------------------------------------------------
void __fastcall Trotation_editor_form::bind_to
(CropSyst::Rotation_parameters   *rotation_
,Tparameter_file_form            *parameter_form_                                //071204
//,const char *_master_dir     // should not be 0
//,const char *_project_dir    // may be 0
//,const char *_scenario_dir   //note/ may be 0
)
{
   rotation = rotation_;
   parameter_form = parameter_form_;                                             //071204

    //master_database_dir = new CS::Database_directory(_master_dir);               //140124_051228
    //if (_project_dir)      project_database_dir = new CS::Database_directory(_project_dir);  //051228
    //if (_scenario_dir)     scenario_database_dir = new CS::Database_directory(_scenario_dir);//051228
    listbox_rotation ->bind_to(&(rotation->planting_events)/*V4_HELP_URL(HELP_P_rotation_build)*/);
    edit_years       ->bind_to(&(rotation->years)        /*V4_HELP_URL(HELP_P_rotation_build)*/); //020910
    edit_end         ->bind_to(&(rotation->end_year)     /*V4_HELP_URL(HELP_P_rotation_build)*/); //020910

//Not available for some reason/*020909*/     rot_listbox->SetMultiSelect(true);
}
//_bind_to__________________________________________________________2018-03-26_/
/*180326 Not sure if needed
void __fastcall Trotation_editor_form::Update()
{  listbox_rotation  ->Update();
   edit_years        ->Update();
   edit_end          ->Update();
}
*/
//---------------------------------------------------------------------------
void __fastcall Trotation_editor_form::button_plantingClick(TObject *Sender)
{  if (rotation)
   {  CropSyst::Sowing_event *planting_event = new CropSyst::Sowing_event();
      planting_event->begin_sync.sync_mode_labeled.set(ACTUAL_DATE_MODE);
      //180326 Tsowing_event_form *sow_event_form = new Tsowing_event_form(this);
      Tplanting_event_form *plant_event_form = new Tplanting_event_form(this);
      plant_event_form->bind_to(planting_event,parameter_form->provide_version());
      if (plant_event_form->ShowModal() == mrOk)
      {  rotation->planting_events.add_sorted(planting_event);
         listbox_rotation->Update();
      }
   }
   listbox_rotation->Update();
}
//_button_plantingClick_____________________________________________2018-03-26_/
void __fastcall Trotation_editor_form::button_editClick(TObject *Sender)
{  listbox_rotationDblClick(Sender); }
//_button_editClick______________________________________2018-03-26_1999-02-23_/
void __fastcall Trotation_editor_form::button_deleteClick(TObject *Sender)
{  listbox_rotation->delete_selected(); }
//_button_deleteClick_______________________________________________1999-02-25_/
//void __fastcall Trotation_editor_form::listbox_rotationClick(TObject *Sender)
void __fastcall Trotation_editor_form::listbox_rotationDblClick(TObject *Sender)
{  if (rotation)
   {  int rot_index = listbox_rotation->ItemIndex;
      CropSyst::Sowing_event *plant_event = dynamic_cast<CropSyst::Sowing_event *>
      (rotation->planting_events.get_at(rot_index));
      if (plant_event)
      {
         Tplanting_event_form *plant_event_form = new Tplanting_event_form(this);
         plant_event_form->bind_to(plant_event,parameter_form->provide_version());
         plant_event_form->ShowModal();
         rotation->planting_events.sort();                                       //020617
      }
   }
   listbox_rotation->Update();
}
//_listbox_rotationClick________________________________2018-03-26__1999-02-25_/
void __fastcall Trotation_editor_form::button_sortClick(TObject *Sender)
{
   rotation->planting_events.sort();
   listbox_rotation->bind_to(&(rotation->planting_events) /*V4_HELP_URL(HELP_P_rotation_build)*/);
      // probably could simply update
}
//_button_sortClick_________________________________________________2018-03-26_/
void __fastcall Trotation_editor_form::button_buildClick(TObject *Sender)
{
   // We don't need to specify the years in rotation, this is computed
   // from the selections that are made in the list box
   int num_slctns = listbox_rotation->SelCount;
   if (listbox_rotation->Items->Count == 0) return;                                   //990528
   if (num_slctns == 0)
   {  // If no items are specially selected, select everything
      num_slctns = listbox_rotation->Items->Count;                                    //990229
      for (int i = 0; i < num_slctns; i++)                                       //990229
      listbox_rotation->Selected[i] = true;                                           //990229
   };
   Year first_slct_year = 0;
   int16 slctn = 0;
   int16 rot= 1;
   Year new_year = 0;                                                            //990224
   while (new_year < rotation->end_year)                                         //020517
   for (nat16 i = 0; i < listbox_rotation->Items->Count; i++)
   {  if (listbox_rotation->Selected[i])                                              //020514
      {  CropSyst::Sowing_event *rot_entry = dynamic_cast<CropSyst::Sowing_event *>
               (rotation->planting_events.get_at(i));                              //120316
         if (rot_entry)                                                          //990223
         {  CORN::Date_clad_32 date(rot_entry->begin_sync/*,D_YMD,D_YYYY|D_M|D_lead_zero,'/'*/);   //180326_990223
            if (!first_slct_year) first_slct_year = date.get_year();             //990223
            new_year = (Year)( (date.get_year() - first_slct_year)
               + (rotation->years* rot) + first_slct_year);                      //980508
            CORN::Date_clad_32 new_entry_date(new_year,date.get_DOY()            //180326_
               /*,D_YMD,D_YYYY|D_M|D_lead_zero,'/'*/);                               //990223
            if (new_entry_date.get_year() <=rotation->end_year)                  //980508
            {  CropSyst::Sowing_event *new_rot_entry = new CropSyst::Sowing_event();
			   /*
				120624 continue here

				give new_rot_entry a new unique event ID
			   */
               CropSyst::Sowing_operation *new_sow_op = new CropSyst::Sowing_operation
                  (rot_entry->provide_sowing_operation());                       //031014_130516 was get_sowing_operation()
               new_rot_entry->set_operation(new_sow_op,true);                    //031014
               new_rot_entry->date.set(new_entry_date);                          //020910
               new_rot_entry->begin_sync.set(new_entry_date);                    //020910
               new_rot_entry->begin_sync.sync_mode_labeled.set(ACTUAL_DATE_MODE);//020910
               rotation->planting_events.append(new_rot_entry);                    //990223
            }
         }                                                                       //980507
         slctn++;
         if (slctn >= num_slctns)
         {  slctn = 0;
            rot++;
         }
      }
   }
   listbox_rotation->Update();                                                        //990223
}
//---------------------------------------------------------------------------

