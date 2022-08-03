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
static inline void ValidCtrCheck(TAutoTimeSeriesPlotter *)
{
   new TAutoTimeSeriesPlotter(NULL);
}
//______________________________________________________________________________
__fastcall TAutoTimeSeriesPlotter::TAutoTimeSeriesPlotter(TComponent* Owner)
   : TAutoGraphPlotter(Owner)
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
      plot->draw(/*buffer->*/Canvas,Height, display_date ? display_date->days_in_this_year() : 365); //160208
   FOR_EACH_END(each_plot);
   TAutoGraphPlotter::PaintCalendar(/*drawDC,erase,itemRect*/);
};
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
         float32 value = values_array.get/*120322 _no_resize*/(pt);// values_array? values_array->get_no_resize(pt) : 0.0;
         value = CORN_must_be_between(value,min,max);
         points[pt].y = inverse_axis
         ? ((value - min) * height / range)
         : height - ((value - min) * height / range);
         on_canvas->Pixels[pt][zero] = clWhite;

         if (!connect_points)
            on_canvas->Pixels[points[pt].x][points[pt].y] = color;
      };
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
      };
   };
   delete[] points;
};
//______________________________________________________________________________
void TAutoTimeSeriesPlotter::set
(uint32   variable_code
,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_values
)
{
   FOR_EACH_IN(plot,Plot,time_series_plots,each_plot)
      if (plot->variable_code == variable_code)
         plot->set(i_values);
   FOR_EACH_END(each_plot);
   Invalidate();
};
//______________________________________________________________________________
TAutoTimeSeriesPlotter::Range_plot::Range_plot
(uint32     i_variable_code
,int16      i_num_values
,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_values
,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_max_values
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
void TAutoTimeSeriesPlotter::Range_plot::draw(TCanvas *on_canvas, int height, int days_in_year)
{  if (!enabled) return;                                                          //000407
   float32 range = (max - min);                                                   //980819
   if (range) // if there is no range, there is nothing to graph                  //980817
   {  on_canvas->Pen->Color = color; //TColor::LtRed);
      on_canvas->Pen->Style = psSolid;

      for (int pt = 0; pt <days_in_year; pt++)
      {
         int x = pt;                                                              //020121
         float32 min_value = values_array.get/*120322 _no_resize*/(pt); //values_array? values_array->get_no_resize(pt) : 0.0;                 //000517
         float32 max_value =  max_values_array.get/*120322 _no_resize*/(pt); //max_values_array? max_values_array->get_no_resize(pt) : 0.0;    //000517
         min_value = CORN_must_be_between(min_value,min,max);                                                                                  //980819
         max_value = CORN_must_be_between(max_value,min,max);                                                                                  //980819
         int min_y =                                                                                                                          //020121
            inverse_axis                                                                                                                      //000428
            ? ((min_value - min) * height / range)                                                                                            //000428
            : height - ((min_value - min) * height / range);                                                                                  //______
         int max_y =                                                                                                                          //020121
            inverse_axis                                                                                                                      //000428
            ? ((max_value - min) * height / range)                                                                                            //000428
           : height - ((max_value - min) * height / range);
         on_canvas->MoveTo(x,min_y); //min_points[pt]);
         on_canvas->LineTo(x,max_y); // max_points[pt]);
     };
   };
};
//_1998-08-17___________________________________________________________________
namespace Autotimeseriesplotter
{  void __fastcall PACKAGE Register()
   {  TComponentClass classes[1] = {__classid(TAutoTimeSeriesPlotter)};
      RegisterComponents("UEDControls", classes, 0);
   }
}
//______________________________________________________________________________
