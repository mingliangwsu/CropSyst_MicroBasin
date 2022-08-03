//---------------------------------------------------------------------------

#include <vcl.h>
#include <corn/corn_pch.h>
#pragma hdrstop

#include "AutoGraphPlotter.h"
//#include <corn/datetime/date.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

//#define MONTH_NAME_BAR_HEIGHT 16

static inline void ValidCtrCheck(TAutoGraphPlotter *)
{
   new TAutoGraphPlotter(NULL);
}
//---------------------------------------------------------------------------
__fastcall TAutoGraphPlotter::TAutoGraphPlotter(TComponent* Owner)
   : TGraphicControl(Owner)
   , display_date(0)
{
/*
   buffer = new Graphics::TBitmap;

	buffer->Width	  = Width;
	buffer->Height  = Height;
*/
}


void __fastcall TAutoGraphPlotter::Paint()
{
   TRect LayoutRect;
	LayoutRect.Left	  = 0;
	LayoutRect.Top	  = 0;
	LayoutRect.Right  = Width;
	LayoutRect.Bottom = Height;

	// paint the background
	/*buffer->*/Canvas->Brush->Color = clBlack;
   /*buffer->*/Canvas->Brush->Style = bsSolid;
	/*buffer->*/Canvas->FillRect(LayoutRect);

   // draw horizontal decade lines
   /*buffer->*/Canvas->Pen->Color = clGray;

   int month_text_height = 10;
   int plot_area_height = Height/* - month_text_height*/;
   for (int i = 1 ; i < 10; i++)
   {  // Make sure that we start drawing lines below the month labels
      int r = Height * i / 10 /*+ month_text_height*/;
      /*buffer->*/Canvas->MoveTo(0,r);
      /*buffer->*/Canvas->LineTo(Width,r);
   };
//NYI/*______*/     TUIBorder border(itemRect, TUIBorder::TEdge(TUIBorder::SunkenOuter));
//NYI/*______*/     border.Paint(drawDC);

//	buffer->Canvas->CopyMode = cmSrcCopy;
//	Canvas->Draw(0, 0, buffer);

}
void TAutoGraphPlotter::PaintCalendar(/*TDC &drawDC,bool erase, TRect &itemRect*/)
{
//   int month_top_line = Height - MONTH_NAME_BAR_HEIGHT;
   // Gray out any period out of range
   int month_left = 1;
#ifdef OBSOLETE
we now have separate month bar control
   TRect gray_out_first(0,0,first_valid_value-1,Height);
	/*buffer->*/Canvas->Brush->Color = clGray;
	/*buffer->*/Canvas->FillRect(gray_out_first);

   TRect gray_out_last(last_valid_value+1,0,Width,Height);
	/*buffer->*/Canvas->FillRect(gray_out_last);

   // NYI Need to set text print alignment to center is month box
#endif
   CORN::Year year = display_date ? display_date->get_year() : 1;
   for (CORN::Month month = 1; month <= 12; month++)
   {  int month_right = month_left +
         CORN::date_get_days_in_month(year,month); // Should pass the year       //160208
         //160802 CORN::date_days_in_month(year,month); // Should pass the year

//Currently we let the programmer draw month bars
//      TRect monthRect(month_left,month_top_line,month_right,Height);

//      // Draw a rectangle for the month
//      TColor month_color = (month & 1) ? clGray : clLtGray;
//      /*buffer->*/Canvas->Brush->Color = month_color;
//      /*buffer->*/Canvas->FillRect(monthRect);

//      // Output the month abreviatnios
//      /*buffer->*/Canvas->Pen->Color = clBlack;
//      AnsiString month_str(CORN::date_month_abbrev(month));
//      /*buffer->*/Canvas->TextRect(monthRect,month_left,month_top_line,month_str);
//      /*buffer->*/Canvas->TextOut(1,1,month_str);


      month_left = month_right;

      // Draw dotted lines between months

      /*buffer->*/Canvas->Pen->Color = clBlack;
      /*buffer->*/Canvas->MoveTo(month_right,Top);
      /*buffer->*/Canvas->Pen->Color = clGray;
      /*buffer->*/Canvas->Pen->Style = psDot;
      /*buffer->*/Canvas->Pen->Mode  = pmCopy;
//      /*buffer->*/Canvas->LineTo(month_right,month_top_line);
      /*buffer->*/Canvas->LineTo(month_right,Height);
   };
   // Draws the highlighted line
   int doy = display_date ? display_date->get_DOY() : 0;
   if (doy >= 1)
   {
      /*buffer->*/Canvas->Pen->Color = clBlack;
      /*buffer->*/Canvas->MoveTo(doy,Top);
      /*buffer->*/Canvas->Pen->Color = clYellow;
      /*buffer->*/Canvas->Pen->Style = psSolid;
      /*buffer->*/Canvas->Pen->Mode = pmMergePenNot; 
      /*buffer->*/Canvas->LineTo(doy,Height);
      /*buffer->*/Canvas->Pen->Mode = pmCopy; 
   };
   /*buffer->*/Canvas->Pen->Color = clBlack;

//	/*buffer->*/Canvas->CopyMode = cmSrcCopy;
//	Canvas->Draw(0, 0, buffer);

};

//---------------------------------------------------------------------------
namespace Autographplotter
{
   void __fastcall PACKAGE Register()
   {
       TComponentClass classes[1] = {__classid(TAutoGraphPlotter)};
       RegisterComponents("UEDControls", classes, 0);
   }
}
//---------------------------------------------------------------------------
