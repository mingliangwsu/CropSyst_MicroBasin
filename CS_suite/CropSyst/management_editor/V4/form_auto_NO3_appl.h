//______________________________________________________________________________

#ifndef form_auto_NO3_applH
#define form_auto_NO3_applH
//______________________________________________________________________________
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
//______________________________________________________________________________
//150402 #include "CropSyst/source/mgmt_param.h"
#include "CropSyst/source/management/management_param_V4.h"

#include <ExtCtrls.hpp>
class Tparameter_file_form;
class Tinorganic_N_application_form;
//______________________________________________________________________________
class Tform_auto_NO3_application : public TForm      //120711 rename to Tform_auto_N_application
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TAutoInt16EditBar *percent_of_application_editbar;
   TLabel *Label4;
   TPanel *panel_auto_N_amount;
private:	// User declarations
   CropSyst::N_application_soil_observation_mode::Split_application *auto_N_appl_op;
   Tinorganic_N_application_form *inorg_param_form;                              //120711
public:		// User declarations
   __fastcall Tform_auto_NO3_application(TComponent* Owner);
   void bind_to
      (CropSyst::N_application_soil_observation_mode::Split_application *_auto_N_appl_op
      ,Tparameter_file_form       *_parameter_file_form);
};
//______________________________________________________________________________
extern PACKAGE Tform_auto_NO3_application *form_auto_NO3_application;
//______________________________________________________________________________
#endif

