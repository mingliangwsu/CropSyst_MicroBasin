//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
#include "form_soil_editor.h"
#include <cropsyst/source/soil/soil_param.h>
//______________________________________________________________________________
#include "CS_Suite/CropSyst/soil_editor/form_soil_editor_inc.h"
SOIL_EDITOR_INCLUDES_AND_FORWARD_DECLS
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "RNAutoParameterEditBar"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoRadioGroup"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma resource "*.dfm"
Tsoil_editor_form *soil_editor_form;
//______________________________________________________________________________
__fastcall Tsoil_editor_form::Tsoil_editor_form(TComponent* Owner)
   : TForm(Owner)
Tsoil_editor_form_CONSTRUCTOR_INITIALIZATION
{}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::bind_to(Smart_soil_parameters *i_soil,Tparameter_file_form *i_parameter_form)
{
   bind_to_V4_and_V5(i_soil,i_parameter_form);

   edit_steepness             ->bind_to(&(soil->p_steepness)     );
   edit_slope_length          ->bind_to(&(soil->p_slope_length)             );
   edit_fallow_curve          ->bind_to(&(soil->p_user_fallow_curve_number) );
   edit_override_curve_number ->bind_to(&(soil->p_override_curve_number));
   edit_surface_storage       ->bind_to(&(soil->p_surface_storage_mm)       );
   edit_albedo_dry->bind_to(&(soil->p_albedo_dry)); // NO_HELP_YET) //041203_
   edit_albedo_wet->bind_to(&(soil->p_albedo_wet)); // NO_HELP_YET) //041203_
   edit_water_vapor_conductance_atmosphere_adj->bind_to(&(soil->p_water_vapor_conductance_atmosphere_adj)); // NO_HELP_YET) //041206_
   // We must not calculate, we must let values stay as user last saw them! //981104_
   edit_SLPF->bind_to(&(soil->p_SLPF_CropGro));
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_surfaceClick(TObject *Sender)
{  TCustomForm *ParentForm = GetParentForm(this);
   ParentForm-> ActiveControl = groupbox_albedo;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_runoffClick(TObject *Sender)
{  TCustomForm *ParentForm = GetParentForm(this);
   ParentForm-> ActiveControl = groupbox_runoff;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_erosionClick(TObject *Sender)
{  TCustomForm *ParentForm = GetParentForm(this);
   ParentForm-> ActiveControl = groupbox_RUSLE;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_albedo_darkClick(TObject *Sender)
{  soil->albedo_dry = 0.13;   edit_albedo_dry->Update();
   soil->albedo_wet = 0.08;   edit_albedo_wet->Update();
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_albedo_medClick(TObject *Sender)
{  soil->albedo_dry = 0.155;  edit_albedo_dry->Update();
   soil->albedo_wet = 0.09;   edit_albedo_wet->Update();
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_albedo_lightClick(TObject *Sender)
{  soil->albedo_dry = 0.18;   edit_albedo_dry->Update();
   soil->albedo_wet = 0.10;   edit_albedo_wet->Update();
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::FormKeyPress(TObject *Sender, wchar_t &Key)
{  if (Key==VK_RETURN)
   {  Key = 0;
      Perform(WM_NEXTDLGCTL,0,0);
   };
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridAutoDeleteRow(TObject *Sender, int ARow)
{  texture_grid_autodeleterow(ARow);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridAutoInsertRow(TObject *Sender, int ARow)
{  texture_grid_autoinsertrow(ARow);   //101015
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridCellValidate(TObject *Sender, int ACol,
          int ARow, UnicodeString &Value, bool &Valid)
{  update_properties_on_cell_change(  ACol,  ARow);
   Valid = true;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridClipboardBeforePasteCell(TObject *Sender,
          int ACol, int ARow, UnicodeString &Value, bool &Allow)
{  texture_grid->Cells[ACol][ARow] = Value;
   update_properties_on_cell_change( ACol,ARow);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridClipboardPaste(TObject *Sender, bool &Allow)
{  paste_started = true;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::estimated_labelClick(TObject *Sender)
{  clear_layer_status();
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_select_texture_triangleClick(TObject *Sender)
{  int layer = texture_grid->Row;
   if (layer >= 1) texture_clicked(layer);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_textureClick(TObject *Sender)
{  TCustomForm *ParentForm = GetParentForm(this);
   ParentForm-> ActiveControl = texture_grid;
   texture_grid->LeftCol = 1; }
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_hydro_propClick(TObject *Sender)
{  TCustomForm *ParentForm = GetParentForm(this);
   ParentForm-> ActiveControl = texture_grid;
   texture_grid->LeftCol = 6; }
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_chemistryClick(TObject *Sender)
{  TCustomForm *ParentForm = GetParentForm(this);
   ParentForm-> ActiveControl = texture_grid;
   texture_grid->LeftCol = 15; }
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::checkbox_compute_surface_storageClick(TObject *Sender)
{  show_hide_controls();
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::label_install_hydr_prop_calcClick(TObject *Sender)
{  parameter_file_form->view_manual("hydr_prop_calc_download.htm");
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_hydr_prop_calcClick(TObject *Sender)
{  WinExec(SoilWaterCharacteristics_exe.c_str() ,SW_SHOWNORMAL);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::edit_soil_layersExit(TObject *Sender)
{  for (int layer = 1; layer <= MAX_soil_horizons; layer++)
      update_grid_colors(layer);
}
//______________________________________________________________________________


