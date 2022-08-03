//---------------------------------------------------------------------------

#include <vcl.h>
#include <corn/corn_pch.h>
#pragma hdrstop
#include <corn/container/container.h>
#include "AutoProfilePlotter.h"
#include <ued/library/ued_types.h>
//#include <corn/compare.h>
//#include <ued/ued.h>
#include <corn/image/clrramp.h>
#pragma link "AutoGraphPlotter"
#pragma link "AutoTimeSeriesPlotter"
#pragma package(smart_init)
#include <corn/no_ns.h>
///*001206*/  namespace_CORN_start;
using namespace CORN;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TAutoProfilePlotter *)
{
   new TAutoProfilePlotter(NULL);
}
//---------------------------------------------------------------------------
__fastcall TAutoProfilePlotter::TAutoProfilePlotter(TComponent* Owner)
   : TAutoTimeSeriesPlotter(Owner)
   , color_ramp(0)
   , help_URL("")
{
//   blackouts_background(false);
}

/*020809_*/ __fastcall TAutoProfilePlotter::~TAutoProfilePlotter()
/*______*/  {
/*______*/     if (color_ramp) delete color_ramp; color_ramp = 0;
//obs/*021124_*/    if (help_URL) delete help_URL; help_URL = 0;
/*______*/  };

/*______*/  void __fastcall TAutoProfilePlotter::Paint()
/*______*/  {
               if (! color_ramp) return;
///*_980817*/    TRect plot_rect (itemRect);
///*_980817*/    plot_rect.SetWH(itemRect.Left(),itemRect.Top(),itemRect.Width(),itemRect.Height()-MONTH_NAME_BAR_HEIGHT); // The plot area must not include the month name bar
/*______*/
/*______*/     int height =  Height; // plot_rect.Height();
/*______*/
/*______*/     int start_pos = top_down
/*______*/           ? 0      // Start at the top of the window
/*______*/           : height; // Start at the bottom of the window

int layers_to_consider =  layers-1; // <- This should be layers
if (layers_to_consider < 0)  // Soil data not found in the file.
   layers_to_consider = 0;
// WARNING there is an invalid number in [num_layers] not sure if
// cropsyst is generating it or what

/*______*/     float total_layer_depth = layering.sum(layers_to_consider);
//010216       If we haven't encountered a soil profile record yet we don't try to draw the profile
/*010216_*/    if (total_layer_depth)
/*010216_*/    {
                  int end_pos[256];
                  float layer_depth = 0;
                  for (int layer = 1; layer <= layers_to_consider; layer++)
                  {
                     layer_depth += layering.get_no_resize(layer);
/*______*/           int layer_draw_length = (int)(layer_depth * height / total_layer_depth);
/*______*/           end_pos[layer] = top_down ? +layer_draw_length : -layer_draw_length;
                  };
/*______*/
/*______*/        for (int ts = 0; ts < values_array[1].get_count() ; ts++)  // ts = timstep
/*______*/        {
/*______*/
/*______*/           Canvas->MoveTo(ts,start_pos);
/*______*/           for (int layer = 1; layer <= layers_to_consider; layer++)
/*______*/           {
/*______*/              {
/*______*/                 float value = values_array[layer].get_no_resize(ts);

if (value > 0.600)
value += 0.000001;
                           TColor clr  = color_ramp->get_RGB_color_of(value);

/*______*/                 {
                              // If there is a missing attributes marked for this date, black out the line
                              // This could be moved to graph plot.
                              if ((attributes[layer].get_no_resize(ts) == CORN::missing_quality))
                                 clr = clGray; // TColor::Gray;
//                              Canvas->Brush->Color = clr;
                              Canvas->Pen->Color = clr;
//                            TBrush brush(clr); OWL
                              Canvas->Pen->Style = psSolid;
///*______*/                    TPen pen(PS_SOLID,1,brush,0,0); OWL
///*______*/                    drawDC.SelectObject(pen); OWL
/*______*/                    Canvas->LineTo(ts,end_pos[layer]);
///*______*/                    drawDC.RestorePen(); OWL // We need to restore the original pen because this pen is going to disappear
/*______*/                 };
/*______*/              };
/*______*/           };
/*______*/        };
                  // Draw layer separators
/*______*/        for (int layer = 1; layer <= layers_to_consider; layer++)
/*______*/        {
/*______*/           Canvas->MoveTo(1,end_pos[layer]);
/*______*/           {  Canvas->Pen->Color = clBlack;
//                        TBrush brush(TColor::Black);
///*______*/              TPen pen(PS_SOLID,1,brush,0,0); OWL
                        Canvas->Pen->Style = psSolid;
///*______*/              drawDC.SelectObject(pen); OWL
/*______*/              Canvas->LineTo(Width,end_pos[layer]);
///*______*/              drawDC.RestorePen(); OWL // We need to restore the original pen because this pen is going to disappear
/*______*/           };
/*______*/        };

/*000428*/        float32 profile_depth = layering.sum(layers_to_consider);
//031204obs/*000428*/        for (Plot *plot =(Plot *)time_series_plots.move_to_head()
//031204obs/*000428*/           ; plot
//031204obs/*000428*/           ; plot=(Plot *)time_series_plots.move_to_next())


/*031204_*/       FOR_EACH_IN(plot,Plot,time_series_plots,each_plot)
/*000428*/           plot->max = profile_depth;
/*031203_*/       FOR_EACH_END(each_plot);
/*010216_*/    };
/*000428*/     TAutoTimeSeriesPlotter::Paint();
/*______*/ };

/*______*/    void TAutoProfilePlotter::ing
/*______*/    (uint8   i_layers
/*______*/    ,float32 i_thickness[]  // The unit thickness of the layer
/*______*/    )
/*______*/    {
/*______*/       layers = i_layers;
/*______*/       layering.set_values(i_thickness,i_layers+1);
/*______*/    };

/*_______*/ void TAutoProfilePlotter::
/*_______*/ (uint8 layer
/*000402*/  ,const Dynamic_array<float32>/*101018 Dynamic_float_array*/ &i_values_array
/*000517*/  ,const Dynamic_array<nat8>/*101018Dynamic_uint8_array*/ &i_attributes
/*_______*/ )
/*_______*/ {  layers = CORN_max(layers,layer);
/*_______*/          values_array[layer].copy(i_values_array);
/*000517_*/        attributes[layer].set(i_attributes);
/*_______*/ };


void TAutoProfilePlotter::bind_to
   (const char */*const CORN_string &*/i_description
   ,CORN_date   *i_display_date  // Eventually this will be a CORN_date_time
   ,float32 i_low_value  // This is a low values for a range of values
   ,float32 i_high_value
   ,uint16  i_colors      // Number of color divisions in color ramp
   ,TColor  i_low_color   // Color of lowest value
   ,TColor  i_med_color   // Color of medium value
   ,TColor  i_high_color  // Color of highest value
   ,bool    i_top_down
   ,uint8   i_layers      // Number of layers
   ,float32 i_thickness[]  // The unit thickness of the layer
   ,const char *i_help_URL
   )
{
   TAutoTimeSeriesPlotter::bind_to(i_display_date);
   layering.set(i_layers,0); // , layering((int16) i_layers,1)
   description = i_description;
   top_down = i_top_down;
   low_value = i_low_value;
   high_value = i_high_value;

   color_ramp = new Scaled_color_ramp(i_low_value,i_high_value,i_colors,i_low_color, i_med_color,i_high_color);

   ing(i_layers,i_thickness);
   if (i_help_URL) help_URL.assign(i_help_URL); //  = new CORN::Smart_file_name(i_help_URL);

};

//---------------------------------------------------------------------------
namespace Autoprofileplotter
{
   void __fastcall PACKAGE Register()
   {
       TComponentClass classes[1] = {__classid(TAutoProfilePlotter)};
       RegisterComponents("UEDControls", classes, 0);
   }
}
//---------------------------------------------------------------------------
