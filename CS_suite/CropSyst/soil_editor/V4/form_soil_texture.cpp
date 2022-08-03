#include <vcl.h>
#pragma hdrstop
#include "form_soil_texture.h"
#include <common/soil/txtrhydr.h>
#include "CropSyst/GUI/help/soil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma link "AutoFloat32EditBar"
#pragma resource "*.dfm"
#include "GUI/parameter/form_param_file.h"
Tsoil_texture_form *soil_texture_form;
//---------------------------------------------------------------------------
__fastcall Tsoil_texture_form::Tsoil_texture_form(TComponent* Owner)
   : TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall Tsoil_texture_form::bind_to
(float32 *_vol_WC_at_33
,float32 *_vol_WC_at_1500
,float32 *_sand
,float32 *_clay
,float32 *_silt
,float32 *_sat_hydraul_cond_m_day
,float32 *_bulk_density
,float32 *_soil_b
,float32 *_air_entry_pot
,Tparameter_file_form *_parameter_form)
{  Tparameter_file_form *parameter_file_form = _parameter_form;                  //130326
   vol_WC_at_33     =  _vol_WC_at_33;
   vol_WC_at_1500   =  _vol_WC_at_1500;
   sand             =  _sand;
   clay             =  _clay;
   silt             =  _silt;
   bulk_density     =  _bulk_density;
   soil_b           =  _soil_b;
   air_entry_pot    =  _air_entry_pot;
   sat_hydraul_cond_m_day =  _sat_hydraul_cond_m_day;

   availwater_edit      ->bind_to(&availwater,3,0/*No help*/);
   sat_hydraul_cond_edit->bind_to(sat_hydraul_cond_m_day,4  V4_HELP_URL(HELP_P_soil_sat_hydr_cond));
   bulk_density_edit    ->bind_to(bulk_density,3            V4_HELP_URL(HELP_P_bulk_density));
   vol_WC_at_33_edit    ->bind_to(vol_WC_at_33,3            V4_HELP_URL(HELP_P_soil_field_capacity));
   vol_WC_at_1500_edit  ->bind_to(vol_WC_at_1500,3          V4_HELP_URL(HELP_P_soil_perm_wilt_point));
   saturation_edit      ->bind_to(&saturation,3,0/*No help*/);
   clay_edit            ->bind_to(clay,3                    V4_HELP_URL(HELP_P_soil_texture));
   sand_edit            ->bind_to(sand,3                    V4_HELP_URL(HELP_P_soil_texture));

   // Update pointer position.
   sand_clay_edit_onchange(0);
};
//---------------------------------------------------------------------------
void __fastcall Tsoil_texture_form::update_hydraulics(TObject *Sender)
{  *silt = 100.0 - (*clay+*sand);
   Soil_texture_hydraulics hydraulics
   (*sand
   ,*clay
   ,*silt
   ,saturation,false
   ,*vol_WC_at_1500,false
   ,*vol_WC_at_33,false
   ,*sat_hydraul_cond_m_day,false
   ,*bulk_density,false
   ,*soil_b,false
   ,*air_entry_pot,false);
   hydraulics.recompute_every_thing();
   availwater = (*vol_WC_at_33-*vol_WC_at_1500);
   availwater_edit->Update();
   sat_hydraul_cond_edit->Update();
   bulk_density_edit->Update();
   vol_WC_at_33_edit->Update();
   vol_WC_at_1500_edit->Update();
   saturation_edit->Update();
   clay_edit->Update();
   sand_edit->Update();
}
//---------------------------------------------------------------------------
void __fastcall Tsoil_texture_form::triangle_onmousedown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{  pointer->Left = image_triangle->Left + X - 14;
   pointer->Top = image_triangle->Top + Y - 14;
   float x_scale = (float)(image_triangle->Width) / 100.0;
   float y_scale = (float)(image_triangle->Height) / 100.0;
   int x = (X )/x_scale;
   int y = (Y )/y_scale;
   if ((x > 0) && (x <= 100) && (y > 0) && (y < 100))
  		  //&& (texttri[100-y][x] != '@'))
   {  *sand =   100-y;
      *clay =   x;
      update_hydraulics(Sender);
   };
};
//---------------------------------------------------------------------------
void __fastcall Tsoil_texture_form::sand_clay_edit_onchange(TObject *Sender)
{  update_hydraulics(Sender);
   float width_float =  (float)image_triangle->Width ;
   float height_float = (float)image_triangle->Height;
   float x_scale = width_float/ 100.0;
   float y_scale = height_float / 100.0;
   int y = 100 - *sand;
   int x = *clay;
   int X = x * x_scale;
   int Y = y * y_scale;
   pointer->Left = image_triangle->Left + X - 14;
   pointer->Top = image_triangle->Top + Y - 14;
}
//---------------------------------------------------------------------------

