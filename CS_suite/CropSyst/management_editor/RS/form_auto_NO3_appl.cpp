//______________________________________________________________________________

#include <vcl.h>
#include "CropSyst/source/mgmt_param.h"
#pragma hdrstop
#include "CropSyst/GUI/help/management.h"
#include "GUI/parameter/form_param_file_RS.h"
#include "form_auto_NO3_appl.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "RNAutoParameterEditBar"
#pragma resource "*.dfm"
Tform_auto_NO3_application *form_auto_NO3_application;
//______________________________________________________________________________
__fastcall Tform_auto_NO3_application::Tform_auto_NO3_application(TComponent* Owner)
   : TForm(Owner)
{
}
//______________________________________________________________________________
void Tform_auto_NO3_application::bind_to
(CropSyst::N_application_soil_observation_mode::Split_application  *i_auto_NO3_appl_op
,Tparameter_file_form       *parameter_file_form)
{
   auto_NO3_appl_op = i_auto_NO3_appl_op;
/* NYI I am still updating manegement file to V5   110113
   percent_of_application_editbar->bind_to(&(auto_NO3_appl_op->p_percent_of_application)
      // help moved to parameter properties ,parameter_file_form->compose_manual_subdirectory_filename_cstr(HELP_P_mgmt_N_appl_distribute)
      );
*/
};

