//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "soil_texture2_form.h"
#include <common/soil/txtrhydr.h>
#include <CropSyst/cpp/cs_paths.h>
#include "CropSyst/GUI/help/soil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma link "AutoFloat32EditBar"
#pragma resource "*.dfm"
Tform_soil_texture2 *form_soil_texture2;
//---------------------------------------------------------------------------
__fastcall Tform_soil_texture2::Tform_soil_texture2(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*______*/  void __fastcall Tform_soil_texture2::bind_to
/*______*/  (
/*______*/   float32 *i_vol_WC_at_33
/*______*/  ,float32 *i_vol_WC_at_1500
/*______*/  ,float32 *i_sand
/*______*/  ,float32 *i_clay
/*______*/  ,float32 *i_silt
/*980526*/  ,float32 *i_sat_hydraul_cond_m_day
/*980526*/  ,float32 *i_bulk_density
/*981030*/  ,float32 *i_soil_b
/*981030*/  ,float32 *i_air_entry_pot
/*______*/  )
/*______*/  {
/*______*/     vol_WC_at_33     =  i_vol_WC_at_33;
/*______*/     vol_WC_at_1500   =  i_vol_WC_at_1500;
/*______*/     sand             =  i_sand;
/*______*/     clay             =  i_clay;
/*______*/     silt             =  i_silt;
/*______*/     bulk_density     =  i_bulk_density;
/*______*/     soil_b           =  i_soil_b;
/*______*/     air_entry_pot    =  i_air_entry_pot;
/*______*/     sat_hydraul_cond_m_day =  i_sat_hydraul_cond_m_day;

/*______*/     availwater_edit      ->bind_to(&availwater,3,0/*No help*/);
/*______*/     sat_hydraul_cond_edit->bind_to(sat_hydraul_cond_m_day,4,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_sat_hydr_cond));
/*______*/     bulk_density_edit    ->bind_to(bulk_density,3,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_bulk_density));
/*______*/     vol_WC_at_33_edit    ->bind_to(vol_WC_at_33,3,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_field_capacity));
/*______*/     vol_WC_at_1500_edit  ->bind_to(vol_WC_at_1500,3,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_perm_wilt_point));
/*______*/     saturation_edit      ->bind_to(&saturation,3,0/*No help*/);
/*______*/     clay_edit            ->bind_to(clay,3,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_texture));
/*______*/     sand_edit            ->bind_to(sand,3,cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_texture));

/*______*/     // Update pointer position.
/*______*/     sand_clay_edit_onchange(0);
/*______*/  };
//---------------------------------------------------------------------------
void __fastcall Tform_soil_texture2::update_hydraulics(TObject *Sender)
{

               *silt = 100.0 - (*clay+*sand);
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
               ,*air_entry_pot,false
               );
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
/*______*/ void __fastcall Tform_soil_texture2::triangle_onmousedown(TObject *Sender,
/*______*/       TMouseButton Button, TShiftState Shift, int X, int Y)
/*______*/ {
/*______*/    pointer->Left = image_triangle->Left + X - 14;
/*______*/    pointer->Top = image_triangle->Top + Y - 14;
/*______*/    float x_scale = (float)(image_triangle->Width) / 100.0;
/*______*/    float y_scale = (float)(image_triangle->Height) / 100.0;
/*______*/    int x = (X /*- x_offset*/)/x_scale;
/*______*/    int y = (Y /*- y_offset*/)/y_scale;
/*______*/
/*______*/    if ((x > 0) && (x <= 100) && (y > 0) && (y < 100))
/*______*/   		  //&& (texttri[100-y][x] != '@'))
/*______*/    {
/*______*/        *sand =   100-y;
/*______*/        *clay =   x;
/*______*/        update_hydraulics(Sender);
/*______*/    };
/*______*/ };
//---------------------------------------------------------------------------
/*______*/ void __fastcall Tform_soil_texture2::sand_clay_edit_onchange(TObject *Sender)
/*______*/ {
/*______*/     update_hydraulics(Sender);
// move pointer
/*______*/     float width_float =  (float)image_triangle->Width ;
/*______*/     float height_float = (float)image_triangle->Height;
/*______*/     float x_scale = width_float/ 100.0;
/*______*/     float y_scale = height_float / 100.0;
/*______*/
/*______*/     int y = 100 - *sand;
/*______*/     int x = *clay;
/*______*/     int X = x * x_scale;
/*______*/     int Y = y * y_scale;
/*______*/     pointer->Left = image_triangle->Left + X - 14;
/*______*/     pointer->Top = image_triangle->Top + Y - 14;
/*______*/ }
//---------------------------------------------------------------------------

