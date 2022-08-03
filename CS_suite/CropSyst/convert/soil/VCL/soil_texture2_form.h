//---------------------------------------------------------------------------

#ifndef soil_texture2_formH
#define soil_texture2_formH
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
//---------------------------------------------------------------------------
  class Tform_soil_texture2 : public TForm
  {
  __published:	// IDE-managed Components
   TImage *image_triangle;
   TAutoFloat32Edit *sand_edit;
   TLabel *Label1;
   TAutoFloat32Edit *clay_edit;
   TLabel *Label2;
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TImage *pointer;
   TAutoFloat32Edit *vol_WC_at_1500_edit;
   TAutoFloat32Edit *vol_WC_at_33_edit;
   TAutoFloat32Edit *saturation_edit;
   TAutoFloat32Edit *bulk_density_edit;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TAutoFloat32Edit *sat_hydraul_cond_edit;
   TAutoFloat32Edit *availwater_edit;
   TLabel *Label7;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *Label14;
   TTrackBar *TrackBar1;
   void __fastcall update_hydraulics(TObject *Sender);
   void __fastcall triangle_onmousedown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall sand_clay_edit_onchange(TObject *Sender);
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

   float32 availwater;
   float32 saturation;                   
//   float32 sat_hydraul_cond_cm_hr;


  public:		// User declarations
     __fastcall Tform_soil_texture2(TComponent* Owner);
     void __fastcall bind_to
     (
      float32 *i_vol_WC_at_33
     ,float32 *i_vol_WC_at_1500
     ,float32 *i_sand
     ,float32 *i_clay
     ,float32 *i_silt
     ,float32 *i_sat_hydraul_cond_m_day
     ,float32 *i_bulk_density
     ,float32 *i_soil_b
     ,float32 *i_air_entry_pot
     );
};
//---------------------------------------------------------------------------
extern PACKAGE Tform_soil_texture2 *form_soil_texture2;
//---------------------------------------------------------------------------
#endif
