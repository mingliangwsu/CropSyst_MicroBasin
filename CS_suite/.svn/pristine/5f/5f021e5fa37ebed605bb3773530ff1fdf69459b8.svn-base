//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>
#include "corn/file_sys/smart_filename.h"
#include "corn/math/compare.h"
#include "corn/data_source/vv_file.h"
#include "corn/data_source/dbase_datasrc.h"
//130326 #include "CropSyst/source/cs_paths.h"

#include "form_soil_editor.h"

#include "../../help/soil.h"
#include <GUI/parameter/form_param_file.h>

// The following included may no longer be needed (MOVED to form_soil_editor_common.cpp)
#include "CropSyst/source/soil/soil_param.h"

//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16EditBar"
#pragma link "AutoRadioGroup"
#pragma link "AutoStringEdit"
#pragma link "AutoRadioGroup"
#pragma link "AutoStringEdit"
#pragma link "AdvCombo"
#pragma link "AutoFileEditBar"
#pragma link "Lucombo"
#pragma link "SHDocVw_OCX"
#pragma link "Data_table_dataset"
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma link "Single_datarec_dataset"
#pragma link "AutoContainerComboBox"
#pragma link "AutoCheckBox"
#pragma link "AdvDirectoryEdit"
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma link "AutoInt16Edit"
#pragma resource "*.dfm"

Tsoil_editor_form *soil_editor_form;

//______________________________________________________________________________
__fastcall Tsoil_editor_form::Tsoil_editor_form(TComponent* Owner)
   : TForm(Owner)
Tsoil_editor_form_CONSTRUCTOR_INITIALIZATION
{}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::bind_to(Smart_soil_parameters *_soil,Tparameter_file_form *_parameter_form)
{  bind_to_V4_and_V5(_soil,_parameter_form);
   edit_steepness             ->bind_to(&(soil->v_steepness)                 V4_HELP_URL(HELP_P_soil_steepness));
   edit_slope_length          ->bind_to(&(soil->v_slope_length)              V4_HELP_URL(HELP_P_soil_slope_length));
   edit_fallow_curve          ->bind_to(&(soil->v_user_fallow_curve_number)  V4_HELP_URL(HELP_P_soil_fallow_curve_number));
   edit_surface_storage       ->bind_to(&(soil->v_surface_storage_mm)        V4_HELP_URL(HELP_P_soil_surface_storage));
   edit_albedo_dry            ->bind_to(&(soil->v_albedo_dry),0); // NO_HELP_YET) //041203
   edit_albedo_wet            ->bind_to(&(soil->v_albedo_wet),0); // NO_HELP_YET) //041203
   edit_water_vapor_conductance_atmosphere_adj->bind_to(&(soil->v_water_vapor_conductance_atmosphere_adj),0); // NO_HELP_YET) //041206_
   // We must not calculate, we must let values stay as user last saw them!      //981104
   edit_SLPF->bind_to(&(soil->v_SLPF_CropGro),0);                                //071017
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_albedo_dark_onclick(TObject *Sender)
{  soil->albedo_dry = 0.13;   edit_albedo_dry->Update();
   soil->albedo_wet = 0.08;   edit_albedo_wet->Update();
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_albedo_medclick(TObject *Sender)
{  soil->albedo_dry = 0.155;   edit_albedo_dry->Update();
   soil->albedo_wet = 0.09;   edit_albedo_wet->Update();
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::albedo_light_button_onclick(TObject *Sender)
{  soil->albedo_dry = 0.18;   edit_albedo_dry->Update();
   soil->albedo_wet = 0.10;   edit_albedo_wet->Update();
};
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::FormKeyPress(TObject *Sender, char &Key)
{  if (Key==VK_RETURN)
   {  Key = 0;
      Perform(WM_NEXTDLGCTL,0,0);
   };
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_grid_onautodeleterow
(TObject *Sender, int ARow)
{  texture_grid_autodeleterow(ARow);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_grid_onautoinsertrow(TObject *Sender, int ARow)
{  texture_grid_autoinsertrow(ARow);   //101015
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_grid_oncellvalidate
(TObject *Sender, int ACol, int ARow, AnsiString &Value, bool &Valid)
{  update_properties_on_cell_change(  ACol,  ARow);
   Valid = true;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridClipboardBeforePasteCell
(TObject *Sender, int ACol, int ARow, AnsiString &Value, bool &Allow)
{  texture_grid->Cells[ACol][ARow] = Value;
   update_properties_on_cell_change( ACol,ARow);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::texture_gridClipboardPaste(TObject *Sender, bool &Allow)
{  paste_started = true;
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::estimated_label_onclick(TObject *Sender)
{  clear_layer_status();
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_select_texture_triangle_onclick(TObject *Sender)
{  int layer = texture_grid->Row;
   if (layer >= 1) texture_clicked(layer);
}
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_texture_onclick(TObject *Sender)
{  texture_grid->LeftCol = 1; }
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_hydro_propClick(TObject *Sender)
{  texture_grid->LeftCol = 6; }
//______________________________________________________________________________
void __fastcall Tsoil_editor_form::button_chemistry_onclick(TObject *Sender)
{  texture_grid->LeftCol = 15; }
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
void __fastcall Tsoil_editor_form::edit_soil_layers_onexit(TObject *Sender)
{  for (int layer = 1; layer <= MAX_soil_horizons; layer++)
      update_grid_colors(layer);
}
//______________________________________________________________________________

