#include <vcl.h>
#pragma hdrstop
#include "form_triangle_selector.h"
//___________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma resource "*.dfm"
Tform_texture_selector *form_texture_selector;
//___________________________________________________________________________
__fastcall Tform_texture_selector::Tform_texture_selector(TComponent* Owner)
   : TForm(Owner)
{}
//___________________________________________________________________________
void __fastcall Tform_texture_selector::image_triangleMouseDown
(TObject *Sender, TMouseButton Button, TShiftState Shift, int X,int Y)
{  pointer->Left = image_triangle->Left + X - 14;
   pointer->Top = image_triangle->Top + Y - 14;
   float x_scale = (float)(image_triangle->Width) / 100.0;
   float y_scale = (float)(image_triangle->Height) / 100.0;
   int x = (X /*- x_offset*/)/x_scale;
   int y = (Y /*- y_offset*/)/y_scale;
   if ((x > 0) && (x <= 100) && (y > 0) && (y < 100))
  		  //&& (texttri[100-y][x] != '@'))
   {  *sand =   100-y;
      *clay =   x;
   };
}
//___________________________________________________________________________
void __fastcall Tform_texture_selector::edit_sand_clay_change(TObject *Sender)
{  float width_float =  (float)image_triangle->Width ;
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
//___________________________________________________________________________
void Tform_texture_selector::bind_to(float32 *_sand,float32 *_clay)
{  edit_sand->bind_to(_sand,2,0);
   edit_clay->bind_to(_clay,2,0);
};
//___________________________________________________________________________
