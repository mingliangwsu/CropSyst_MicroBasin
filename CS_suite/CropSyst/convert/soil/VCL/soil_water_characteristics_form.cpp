#include <vcl.h>
#pragma hdrstop
#include "soil_water_characteristics_form.h"
#include <common/soil/txtrhydr.h>
//120317 #include "CropSyst/source/cs_paths.h>
#include "CropSyst/GUI/help/soil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma link "AutoFloat32EditBar"
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
Tform_soil_water_characteristics *form_soil_water_characteristics;
//---------------------------------------------------------------------------
__fastcall Tform_soil_water_characteristics::Tform_soil_water_characteristics(TComponent* Owner)
   : TForm(Owner)
{};
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::bind_to
(float32 *i_vol_WC_at_33
,float32 *i_vol_WC_at_1500
,float32 *i_sand
,float32 *i_clay
,float32 *i_silt
,float32 *i_sat_hydraul_cond_m_day
,float32 *i_bulk_density
,float32 *i_soil_b
,float32 *i_air_entry_pot)
{  vol_WC_at_33     =  i_vol_WC_at_33;
   vol_WC_at_1500   =  i_vol_WC_at_1500;
   sand             =  i_sand;
   clay             =  i_clay;
   silt             =  i_silt;
   bulk_density     =  i_bulk_density;
   soil_b           =  i_soil_b;
   air_entry_pot    =  i_air_entry_pot;
   sat_hydraul_cond_m_day =  i_sat_hydraul_cond_m_day;
   edit_sand            ->bind_to(sand,3,
                  0
  //NYI                  parameter_form->compose_manual_subdirectory_filename(HELP_P_soil_texture).c_str()
                  //101014 cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_texture)
                  );
/*_______*/    edit_clay            ->bind_to(clay,3,
                  0
   //NYI                  parameter_form->compose_manual_subdirectory_filename(HELP_P_soil_texture).c_str()
                 //101014     cs_suite_paths->get_cropsyst_parameter_help_cstr(HELP_P_soil_texture)
                     );
   update_hydraulics(0);  //101014
};
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::update_hydraulics(TObject *Sender)
{
   *silt = 100.0 - (*clay+*sand);
   Soil_texture_hydraulics hydraulics
   (*sand
   ,*clay
   ,*silt
   ,*saturation,false
   ,*vol_WC_at_1500,false
   ,*vol_WC_at_33,false
   ,*sat_hydraul_cond_m_day,false
   ,*bulk_density,false
   ,*soil_b,false
   ,*air_entry_pot,false
   );
   hydraulics.recompute_every_thing();
   switch (combobox_pedotransfer_model->ItemIndex)
   {
      case 0:
/*090512_*/    // Column 1 is Saxton et al. 1986

         if (!is_cell_locked(1,1))  grid_hydraulic_properties->Floats[1][1] = *bulk_density;
         if (!is_cell_locked(1,2))  grid_hydraulic_properties->Floats[1][2] = *vol_WC_at_1500;
         if (!is_cell_locked(1,3))  grid_hydraulic_properties->Floats[1][3] = *vol_WC_at_33;
         if (!is_cell_locked(1,4))  grid_hydraulic_properties->Floats[1][4] = *sat_hydraul_cond_m_day;
         if (!is_cell_locked(1,5))  grid_hydraulic_properties->Floats[1][5] = *air_entry_pot;
         if (!is_cell_locked(1,6))  grid_hydraulic_properties->Floats[1][6] = *soil_b;
         if (!is_cell_locked(1,7))  grid_hydraulic_properties->Floats[1][7] = *saturation;
//NYI         if (!is_cell_locked(1,8))  grid_hydraulic_properties->Floats[1][7] = *saturation;

      break;
      case 1:
      /*
             //090512 Saxton and Rawls is not yet implemented
         if (!is_cell_locked(2,1))  grid_hydraulic_properties->Floats[1][1] = *bulk_density;
         if (!is_cell_locked(2,2))  grid_hydraulic_properties->Floats[1][2] = *vol_WC_at_1500;
         if (!is_cell_locked(2,3))  grid_hydraulic_properties->Floats[1][3] = *vol_WC_at_33;
         if (!is_cell_locked(2,4))  grid_hydraulic_properties->Floats[1][4] = *sat_hydraul_cond_m_day;
         if (!is_cell_locked(2,5))  grid_hydraulic_properties->Floats[1][5] = *air_entry_pot;
         if (!is_cell_locked(2,6))  grid_hydraulic_properties->Floats[1][6] = *soil_b;
         if (!is_cell_locked(2,7))  grid_hydraulic_properties->Floats[1][7] = *saturation;
//NYI         if (!is_cell_locked(2,8))  grid_hydraulic_properties->Floats[1][7] = *saturation;
*/
      break;
      case 2:
/*
             //090512 Saxton and Rawls is not yet implemented
         if (!is_cell_locked(3,1))  grid_hydraulic_properties->Floats[1][1] = *bulk_density;
         if (!is_cell_locked(3,2))  grid_hydraulic_properties->Floats[1][2] = *vol_WC_at_1500;
         if (!is_cell_locked(3,3))  grid_hydraulic_properties->Floats[1][3] = *vol_WC_at_33;
         if (!is_cell_locked(3,4))  grid_hydraulic_properties->Floats[1][4] = *sat_hydraul_cond_m_day;
         if (!is_cell_locked(3,5))  grid_hydraulic_properties->Floats[1][5] = *air_entry_pot;
         if (!is_cell_locked(3,6))  grid_hydraulic_properties->Floats[1][6] = *soil_b;
         if (!is_cell_locked(3,7))  grid_hydraulic_properties->Floats[1][7] = *saturation;
//NYI         if (!is_cell_locked(3,8))  grid_hydraulic_properties->Floats[1][7] = *saturation;
*/
      break;

   };



//NYI/*090512_*/    grid_hydraulic_properties->Floats[1][8] = available_water; Not sure where to get this from
   edit_clay->Update();
   edit_sand->Update();
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::button_select_textureClick(TObject *Sender)
{
   // NYI show the texture triangle form modally
   // when it closes we update hydraulics
   // Need to unlock the cells in grid_hydraulic_properties

   update_hydraulics(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::combobox_textureChange(TObject *Sender)
{
   // NYI set the percent sand and clay representitive for the selected named texture

   update_hydraulics(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::combobox_pedotransfer_modelChange(TObject *Sender)
{
   update_hydraulics(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::button_unlock_user_valueClick(TObject *Sender)
{
   // NYI set the respective cell in  grid_hydraulic_properties as not modifiable
   // NYI set the respective cell in  grid_hydraulic_properties as modifiable
      int curr_row = grid_hydraulic_properties->Row;
      int curr_col = grid_hydraulic_properties->Col;
      #if (CS_VERSION == 4)
      grid_hydraulic_properties->Colors[curr_col][curr_row] = clWhite;
      #else

      #endif
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::button_lock_user_valueClick(TObject *Sender)
{
   // NYI set the respective cell in  grid_hydraulic_properties as modifiable
      int curr_row = grid_hydraulic_properties->Row;
      int curr_col = grid_hydraulic_properties->Col;
      for (int col = 1; col <= 3; col++) // need to clear the row for each of the models so that the current cell is the only one highlighted
         grid_hydraulic_properties->Colors[col][curr_row] = clWhite;
      grid_hydraulic_properties->Colors[curr_col][curr_row] = clYellow;
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::edit_parameter_adjusted(TObject *Sender)
{
      update_hydraulics(Sender);
      clear_cell_locks();
}
//---------------------------------------------------------------------------
bool Tform_soil_water_characteristics::is_cell_locked(int Col, int Row) const
{
   return grid_hydraulic_properties->Colors[Col][Row] == clYellow;
};
//---------------------------------------------------------------------------
void Tform_soil_water_characteristics::clear_cell_locks()
{
   for (int row = 1; row < 8; row++)
      for (int col =1; col < 3; col++)
      {
         grid_hydraulic_properties->Colors[col][row] = clWhite;
      };
};
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::trackbar_organic_matterChange(
      TObject *Sender)
{
      update_hydraulics(Sender);
      clear_cell_locks();
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::trackbar_salinityChange(TObject *Sender)
{
      update_hydraulics(Sender);
      clear_cell_locks();
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::trackbar_gravel_ptc_by_volChange(TObject *Sender)
{
      update_hydraulics(Sender);
      clear_cell_locks();
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::trackbar_gravel_ptc_by_wtChange(TObject *Sender)
{
      update_hydraulics(Sender);
      clear_cell_locks();
}
//---------------------------------------------------------------------------
void __fastcall Tform_soil_water_characteristics::trackbar_compactionChange(TObject *Sender)
{
      update_hydraulics(Sender);
      clear_cell_locks();
}
//---------------------------------------------------------------------------

