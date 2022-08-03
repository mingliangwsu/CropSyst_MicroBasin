//---------------------------------------------------------------------------

#ifndef form_soil_textureH
#define form_soil_textureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "RNAutoFloatEdit.h"
class Tparameter_file_form;
//---------------------------------------------------------------------------
  class Tsoil_texture_form : public TForm
  {
  __published:	// IDE-managed Components
   TImage *image_triangle;
   TLabel *Label1;
   TLabel *Label2;
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TImage *pointer;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   TLabel *Label7;
   TLabel *Label12;
   TLabel *Label13;
   TLabel *Label14;
   TRNAutoFloatEdit *edit_vol_WC_at_1500;
   TRNAutoFloatEdit *edit_vol_WC_at_33;
   TRNAutoFloatEdit *edit_saturation;
   TRNAutoFloatEdit *edit_bulk_density;
   TRNAutoFloatEdit *edit_sand;
   TRNAutoFloatEdit *edit_clay;
   TRNAutoFloatEdit *edit_sat_hydraul_cond;
   TRNAutoFloatEdit *edit_availwater;
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
     __fastcall Tsoil_texture_form(TComponent* Owner);
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
     ,Tparameter_file_form *i_parameter_form
     );
};
//---------------------------------------------------------------------------
extern PACKAGE Tsoil_texture_form *soil_texture_form;
//---------------------------------------------------------------------------
#endif
