//---------------------------------------------------------------------------

#ifndef form_triangle_selectorH
#define form_triangle_selectorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32Edit.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class Tform_texture_selector : public TForm
{
__published:	// IDE-managed Components
   TTrackBar *TrackBar1;
   TImage *image_triangle;
   TTrackBar *trackbar_clay;
   TImage *pointer;
   TBitBtn *BitBtn1;
   TPanel *panel_texture_class;
   TComboBox *combobox_texture_class;
   TAutoFloat32Edit *edit_sand;
   TAutoFloat32Edit *edit_clay;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   void __fastcall image_triangleMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall edit_sand_clay_change(TObject *Sender);
private:	// User declarations

   float32 *sand;
   float32 *clay;
public:		// User declarations
   __fastcall Tform_texture_selector(TComponent* Owner);
   void bind_to(float32 *_sand,float32 *_clay);

};
//---------------------------------------------------------------------------
extern PACKAGE Tform_texture_selector *form_texture_selector;
//---------------------------------------------------------------------------
#endif
