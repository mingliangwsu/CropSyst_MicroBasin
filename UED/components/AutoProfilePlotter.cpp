#include <vcl.h>
#include <corn/corn_pch.h>
#pragma hdrstop
#include "corn/container/container.h"
#include "AutoProfilePlotter.h"
#include <ued/library/ued_types.h>
#include <corn/image/clrramp.h>
#pragma link "AutoGraphPlotter"
#pragma link "AutoTimeSeriesPlotter"
#pragma package(smart_init)
//160208 #include "corn/no_ns.h"
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
//______________________________________________________________________________
__fastcall TAutoProfilePlotter::TAutoProfilePlotter(TComponent* Owner)
   : TAutoTimeSeriesPlotter(Owner)
   , color_ramp(0)
   //160208 , help_URL("")
{
//   blackouts_background(false);
}
//______________________________________________________________________________
__fastcall TAutoProfilePlotter::~TAutoProfilePlotter()
{  if (color_ramp) delete color_ramp; color_ramp = 0;
}
//_2002-08-09___________________________________________________________________
void __fastcall TAutoProfilePlotter::Paint()
{  if (! color_ramp) return;
   int height =  Height; // plot_rect.Height();
   int start_pos = top_down
         ? 0      // Start at the top of the window
         : height; // Start at the bottom of the window

   int layers_to_consider =  layers-1; // <- This should be layers
   if (layers_to_consider < 0)  // Soil data not found in the file.
       layers_to_consider = 0;
// WARNING there is an invalid number in [num_layers] not sure if
// cropsyst is generating it or what

   float total_layer_depth = layering
      .sum_first(layers_to_consider);                                            //160208
      //160208 .sum(layers_to_consider);
   //010216       If we haven't encountered a soil profile record yet we don't try to draw the profile
   if (total_layer_depth)                                                        //010216
   {
      int end_pos[256];
      float layer_depth = 0;
      for (int layer = 1; layer <= layers_to_consider; layer++)
      {
         layer_depth += layering.get/*120322 _no_resize*/(layer);
         int layer_draw_length = (int)(layer_depth * height / total_layer_depth);
         end_pos[layer] = top_down ? +layer_draw_length : -layer_draw_length;
      }

      for (int ts = 0; ts < values_array[1].get_count() ; ts++)  // ts = timstep
      {

         Canvas->MoveTo(ts,start_pos);
         for (int layer = 1; layer <= layers_to_consider; layer++)
         {
            {
               float value = values_array[layer].get/*120322_no_resize*/(ts);

if (value > 0.600)
value += 0.000001;
               TColor clr  = color_ramp->get_RGB_color_of(value);

               {
                  // If there is a missing attributes marked for this date, black out the line
                  // This could be moved to graph plot.
                  if ((attributes[layer].get/*120322 _no_resize*/(ts) == CORN::missing_quality))
                     clr = clGray; // TColor::Gray;
                  Canvas->Pen->Color = clr;
                  Canvas->Pen->Style = psSolid;
                  Canvas->LineTo(ts,end_pos[layer]);
               }
            }
         }
      }
      // Draw layer separators
      for (int layer = 1; layer <= layers_to_consider; layer++)
      {
         Canvas->MoveTo(1,end_pos[layer]);
         {  Canvas->Pen->Color = clBlack;
                        Canvas->Pen->Style = psSolid;
            Canvas->LineTo(Width,end_pos[layer]);
         }
      }
      float32 profile_depth = layering.
         sum_first(layers_to_consider);                                          //160208_000428
         //160208 sum(layers_to_consider);                  //000428
      FOR_EACH_IN(plot,Plot,time_series_plots,each_plot)                         //031204
         plot->max = profile_depth;                                              //000428
      FOR_EACH_END(each_plot);                                                   //031203
   }                                                                             //010216
   TAutoTimeSeriesPlotter::Paint();                                              //000428
}
//______________________________________________________________________________
void TAutoProfilePlotter::ing
(nat8   _layers
,float32 _thickness[])  // The unit thickness of the layer
{  layers = _layers;
   layering.set_values(_thickness,_layers+1);
}
//______________________________________________________________________________
void TAutoProfilePlotter::
(nat8 layer
,const Dynamic_array<float32> &_values_array                                     //000402
,const Dynamic_array<nat8> &_attributes)                                         //000517
{  layers = CORN_max(layers,layer);
   values_array[layer].copy(_values_array);
   attributes[layer].set(_attributes);                                           //000517
}
//______________________________________________________________________________
void TAutoProfilePlotter::bind_to
(
   const char */*const CORN_string &*/i_description
   ,CORN::Date   *i_display_date  // Eventually this will be a CORN_date_time
   ,float32 i_low_value  // This is a low values for a range of values
   ,float32 i_high_value
   ,nat16  i_colors      // Number of color divisions in color ramp
   ,TColor  i_low_color   // Color of lowest value
   ,TColor  i_med_color   // Color of medium value
   ,TColor  i_high_color  // Color of highest value
   ,bool    i_top_down
   ,nat8   i_layers      // Number of layers
   ,float32 i_thickness[]  // The unit thickness of the layer
   ,const char *i_help_URL)
{
   TAutoTimeSeriesPlotter::bind_to(i_display_date);
   layering.set(i_layers,0); // , layering((int16) i_layers,1)
   description = i_description;
   top_down = i_top_down;
   low_value = i_low_value;
   high_value = i_high_value;
   color_ramp = new Scaled_color_ramp(i_low_value,i_high_value,i_colors,i_low_color, i_med_color,i_high_color);
   ing(i_layers,i_thickness);
   //160208 if (i_help_URL) help_URL.assign(i_help_URL); //  = new CORN::Smart_file_name(i_help_URL);
}
//______________________________________________________________________________
namespace Autoprofileplotter
{  void __fastcall PACKAGE Register()
   {  TComponentClass classes[1] = {__classid(TAutoProfilePlotter)};
      RegisterComponents("UEDControls", classes, 0);
   }
}
//______________________________________________________________________________
