//---------------------------------------------------------------------------
#include <vcl.h>
#include <corn/corn_pch.h>
#pragma hdrstop

#include "AutoTimeSeriesPlotter.h"
#pragma link "AutoGraphPlotter"
#pragma package(smart_init)

using namespace CORN;

//______________________________________________________________________________
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TAutoTimeSeriesPlotter *)
{
   new TAutoTimeSeriesPlotter(NULL);
}
//______________________________________________________________________________
__fastcall TAutoTimeSeriesPlotter::TAutoTimeSeriesPlotter(TComponent* Owner)
   : TAutoGraphPlotter(Owner)
//   ,blackouts_background(true)
{
	Width	   = 365;
	Height	= 100;
}
//______________________________________________________________________________
void __fastcall TAutoTimeSeriesPlotter::Paint()
{
   if (blackout_background())
      TAutoGraphPlotter::Paint();
//x/*_980817*/    TRect plot_rect (itemRect);
//x/*_980817*/    plot_rect.SetWH(itemRect.Left(),itemRect.Top(),itemRect.Width(),itemRect.Height()-MONTH_NAME_BAR_HEIGHT); // The plot area must not include the month name bar
//   for (Plot *plot = (Plot *)time_series_plots.move_to_head()
//         ; plot
//         ; plot = (Plot *)time_series_plots.move_to_next())
   FOR_EACH_IN(plot,Plot,time_series_plots,each_plot)
      plot->draw(/*buffer->*/Canvas,Height, display_date ? display_date->days_in_year() : 365);
   FOR_EACH_END(each_plot);
   TAutoGraphPlotter::PaintCalendar(/*drawDC,erase,itemRect*/);
}
//______________________________________________________________________________
void TAutoTimeSeriesPlotter::Plot::draw(TCanvas *on_canvas, int height,int days_in_year)
{
   if (!enabled) return;
   TPoint *points = new TPoint[num_values+1];
   float32 range = (max - min);

   if (range) // if there is no range, there is nothing to graph
   {
      int zero = height - ((0-min) * height / range);
      for (int pt = 0; pt <days_in_year; pt++)
      {
         points[pt].x = pt;
         float32 value = values_array.get_no_resize(pt);// values_array? values_array->get_no_resize(pt) : 0.0;
         value = CORN_must_be_between(value,min,max);
         points[pt].y = inverse_axis
         ? ((value - min) * height / range)
         : height - ((value - min) * height / range);
         on_canvas->Pixels[pt][zero] = clWhite;

         if (!connect_points)
            on_canvas->Pixels[points[pt].x][points[pt].y] = color;
      }
      if (connect_points)
      {  points[days_in_year].x = points[days_in_year-1].x;
         points[days_in_year].y = points[days_in_year-1].y;
         on_canvas->MoveTo(points[1].x,points[1].y);
         on_canvas->Brush->Color = color;
         on_canvas->Pen->Style = psSolid;
         on_canvas->Pen->Color = color;
//         points[num_values].x = points[num_values-1].x;
//          points[num_values].y = points[num_values-1].y;
         on_canvas->Polyline(points,days_in_year);
      }
   }
   delete[] points;
}
//______________________________________________________________________________
void TAutoTimeSeriesPlotter::set
(uint32   variable_code
,const CORN::CORN::Dynamic_array<float32> &i_values
)
{
   FOR_EACH_IN(plot,Plot,time_series_plots,each_plot)
      if (plot->variable_code == variable_code)
         plot->set(i_values);
   FOR_EACH_END(each_plot);
   Invalidate();
}
//______________________________________________________________________________
TAutoTimeSeriesPlotter::Range_plot::Range_plot
      (uint32     i_variable_code
      ,int16      i_num_values
      ,const CORN::CORN::Dynamic_array<float32> &i_values
      ,const CORN::CORN::Dynamic_array<float32> &i_max_values
      ,float32   i_min
      ,float32   i_max
      ,bool       i_connect_points
      ,bool       i_inverse_axis
      ,TColor     i_color
      ,const char * i_description
      ,bool &i_enabled
      )
      :Plot
      (i_variable_code
      ,i_num_values
      ,i_values
      ,i_min
      ,i_max
      ,i_connect_points
      ,i_inverse_axis
      ,i_color
      ,i_description
      ,i_enabled
      )
      , max_values_array(i_max_values)
      {
         is_a_range_plot = true;
      }

//______________________________________________________________________________
/*980817*/ void TAutoTimeSeriesPlotter::Range_plot::draw(TCanvas *on_canvas, int height, int days_in_year)
/*______*/ {
/*000407*/     if (!enabled) return;
///*______*/     TPoint *min_points = new TPoint[num_values];
///*______*/     TPoint *max_points = new TPoint[num_values];
///*______*/     min = 100000;
///*______*/     max = -10000;
///*______*/     for (int pt = 0; pt <num_values; pt++)   // Temporary until I get max and min set correctly
///*______*/     { max = CORN_max(max,values[pt]);
///*______*/       min = CORN_min(min,values[pt]);
///*______*/     }
/*980819*/     float32 range = (max - min);

/*980817*/     if (range) // if there is no range, there is nothing to graph
                {
/*______*/       on_canvas->Pen->Color = color; //TColor::LtRed);
/*______*/       on_canvas->Pen->Style = psSolid;

/*______*/       for (int pt = 0; pt <days_in_year; pt++)
/*______*/       {
/*020121*/           int x = pt;
///*______*/          min_points[pt].x = pt;
//*______*/          max_points[pt].x = pt;
/*000517*/          float32 min_value = values_array.get_no_resize(pt); //values_array? values_array->get_no_resize(pt) : 0.0;
/*000517*/          float32 max_value =  max_values_array.get_no_resize(pt); //max_values_array? max_values_array->get_no_resize(pt) : 0.0;
/*980819*/          min_value = CORN_must_be_between(min_value,min,max);
/*980819*/          max_value = CORN_must_be_between(max_value,min,max);
///*980817*/          min_points[pt].y =
/*020121*/           int min_y =
/*000428*/              inverse_axis
/*000428*/              ? ((min_value - min) * height / range)
/*______*/              : height - ((min_value - min) * height / range);
///*980817*/          max_points[pt].y =
/*020121*/           int max_y =
/*000428*/              inverse_axis
/*000428*/              ? ((max_value - min) * height / range)
/*______*/              : height - ((max_value - min) * height / range);

/*______*/           on_canvas->MoveTo(x,min_y); //min_points[pt]);
/*______*/           on_canvas->LineTo(x,max_y); // max_points[pt]);
/*______*/       }

//*______*/       if (connect_points)
//*______*/       {  TBrush brush(color);
//*______*/          TPen pen(PS_SOLID,1,brush,0,0);
//*______*/          drawDC.SelectObject(pen);
//*______*/          drawDC.Polyline(points,num_values);
//*______*/          drawDC.RestorePen();  // We need to restore the original pen because this pen is going to disappear
//*______*/       }
/*980817*/     }
///*______*/     delete[] min_points;
///*______*/     delete[] max_points;
/*______*/ }
//______________________________________________________________________________
namespace Autotimeseriesplotter
{
   void __fastcall PACKAGE Register()
   {
       TComponentClass classes[1] = {__classid(TAutoTimeSeriesPlotter)}
       RegisterComponents("UEDControls", classes, 0);
   }
}
//______________________________________________________________________________
