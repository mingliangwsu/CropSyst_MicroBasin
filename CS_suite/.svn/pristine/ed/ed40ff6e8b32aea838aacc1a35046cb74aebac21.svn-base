#ifndef soil_water_characteristics_formH
#define soil_water_characteristics_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32Edit.h"
#include "AutoFloat32EditBar.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include "AdvGrid.hpp"
#include "BaseGrid.hpp"
#include <Chart.hpp>
#include <Grids.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
  class Tform_soil_water_characteristics : public TForm
  {
  __published:	// IDE-managed Components
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TGroupBox *GroupBox3;
   TAdvStringGrid *grid_hydraulic_properties;
   TGroupBox *groupbox_texture;
   TAutoFloat32EditBar *edit_sand;
   TAutoFloat32EditBar *edit_clay;
   TPanel *Panel1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *label_potential_axis_50;
   TLabel *label_hydr_cond_axis;
   TLabel *label_potential_axis_1500;
   TImage *image_graph;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TPanel *panel_hydraulic_properties_buttons;
   TBitBtn *button_unlock_user_value;
   TBitBtn *button_lock_user_value;
   TLabel *label_resets;
   TGroupBox *groupbox_effects;
   TBitBtn *button_select_texture;
   TComboBox *combobox_texture;
   TLabel *label_fine_soil_basis;
   TPanel *panel_model;
   TComboBox *combobox_pedotransfer_model;
   TScrollBox *scrollbox_effects;
   TAutoFloat32EditBar *edit_organic_matter;
   TTrackBar *trackbar_organic_matter;
   TAutoFloat32EditBar *edit_salinity;
   TTrackBar *trackbar_salinity;
   TAutoFloat32EditBar *edit_gravel_pct_by_wt;
   TTrackBar *trackbar_gravel_ptc_by_wt;
   TAutoFloat32EditBar *edit_gravel_pct_by_vol;
   TTrackBar *trackbar_gravel_ptc_by_vol;
   TAutoFloat32EditBar *edit_compaction;
   TTrackBar *trackbar_compaction;
   void __fastcall update_hydraulics(TObject *Sender);
   void __fastcall button_select_textureClick(TObject *Sender);
   void __fastcall combobox_textureChange(TObject *Sender);
   void __fastcall combobox_pedotransfer_modelChange(TObject *Sender);
   void __fastcall button_unlock_user_valueClick(TObject *Sender);
   void __fastcall button_lock_user_valueClick(TObject *Sender);
   void __fastcall edit_parameter_adjusted(TObject *Sender);
   void __fastcall trackbar_organic_matterChange(TObject *Sender);
   void __fastcall trackbar_salinityChange(TObject *Sender);
   void __fastcall trackbar_gravel_ptc_by_volChange(TObject *Sender);
   void __fastcall trackbar_gravel_ptc_by_wtChange(TObject *Sender);
   void __fastcall trackbar_compactionChange(TObject *Sender);

private:	// User declarations
   float32 *vol_WC_at_33;
   float32 *vol_WC_at_1500;
   float32 *sand;
   float32 *clay;
   float32 *silt;
   float32 *sat_hydraul_cond_m_day;
   float32 *bulk_density;
   float32 *soil_b;
   float32 *air_entry_pot;

   float32 *availwater;
   float32 *saturation;
//   float32 sat_hydraul_cond_cm_hr;


  public:		// User declarations
     __fastcall Tform_soil_water_characteristics(TComponent* Owner);
     void __fastcall bind_to
     (float32 *vol_WC_at_33
     ,float32 *vol_WC_at_1500
     ,float32 *sand
     ,float32 *clay
     ,float32 *silt
     ,float32 *sat_hydraul_cond_m_day
     ,float32 *bulk_density
     ,float32 *soil_b
     ,float32 *air_entry_pot);
private:
   bool is_cell_locked(int Col, int Row) const;
   void clear_cell_locks();
};
//---------------------------------------------------------------------------
extern PACKAGE Tform_soil_water_characteristics *form_soil_water_characteristics;
//---------------------------------------------------------------------------
#endif
