//______________________________________________________________________________

#include <vcl.h>
#pragma hdrstop
#include "CropSyst/source/mgmt_param.h"
//130321 #include "CropSyst/source/cs_paths.h"
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file.h"
#include "form_auto_NO3_appl.h"
#include "form_inorganic_N_appl.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16EditBar"
#pragma resource "*.dfm"
Tform_auto_NO3_application *form_auto_NO3_application;
#define V4_HELP_URL(x) (0)
// help temporarily disabled NYI
//______________________________________________________________________________
__fastcall Tform_auto_NO3_application::Tform_auto_NO3_application(TComponent* Owner)
   : TForm(Owner)
   , inorg_param_form(0)       //120711
{  inorg_param_form = new Tinorganic_N_application_form(this);                   //120711
   inorg_param_form->Parent = panel_auto_N_amount;                               //120711
   inorg_param_form->Show();                                                     //120711
   inorg_param_form->Top = 0;                                                    //120711
   inorg_param_form->Left = 0;                                                   //120711
   inorg_param_form->Align = alClient;                                           //120711
   inorg_param_form->BorderStyle = bsNone;                                       //120711
}                                                                                //120711
//______________________________________________________________________________
void Tform_auto_NO3_application::bind_to
( CropSyst::N_application_soil_observation_mode::Split_application  *_auto_N_appl_op
,Tparameter_file_form       *parameter_file_form)
{  auto_N_appl_op = _auto_N_appl_op;
   percent_of_application_editbar->bind_to(&(auto_N_appl_op->percent_of_application),/*130317  parameter_file_form->compose_manual_subdirectory_filename_cstr */ V4_HELP_URL(HELP_P_mgmt_N_appl_distribute));
   inorg_param_form->bind_to(_auto_N_appl_op,parameter_file_form);               //120711
   inorg_param_form->nitrate_edit->Units_label = "%";                   //120711
   inorg_param_form->ammonium_edit->Units_label = "%";                  //120711
};
//______________________________________________________________________________

