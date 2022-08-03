#ifdef BUILDER_API
#     include <vcl/vcl.h>
#endif
#pragma hdrstop

#include <corn/image/clrramp.h>
namespace CORN
{
//______________________________________________________________________________
Color_ramp_2points::Color_ramp_2points
(nat16 colors_        // The number of colors in the color ramp.
,nat32 low_color_
,nat32 high_color_)
: colors(colors_)
, low_color(low_color_ & 0xFFFFFF)
, high_color(high_color_ & 0xFFFFFF)
, color_ramp(new nat32[colors_])
{  // Create color ramp
   int16 high_red   =  high_color & 0x0000FF;
   int16 high_green = (high_color & 0x00FF00) >> 8;
   int16 high_blue  = (high_color & 0xFF0000) >> 16;

   if (colors_ == 1)
      color_ramp[1] = low_color_;
   else
   { //low to high
      signed int   low_red   =  low_color_  & 0x0000FF;
      signed int   low_green = (low_color_& 0x00FF00) >> 8;
      signed int   low_blue  = (low_color_ & 0xFF0000) >> 16;
      float32 high_red_float = (float32)high_red;
      float32 low_red_float  = (float32)low_red;
      float32 colors_float   = (float32)colors_;
      float32  delta_red     = (high_red_float -low_red_float)/colors_float/2.0;
      float32  delta_green   = (float)(high_green -low_green) /(float)colors_/2;
      float32  delta_blue    = (float)(high_blue  -low_blue)  /(float)colors_/2;

      float32  red_i = low_red;
      float32  green_i = low_green;
      float32  blue_i = low_blue;

      for (int color_i = 0; color_i < colors; color_i++)
      {

         nat32 color_ramp_color_i =  (int32)red_i;
         color_ramp_color_i |= (((int32)green_i) << 8);
         color_ramp_color_i |= (((int32)blue_i) << 16);
         color_ramp[color_i] = color_ramp_color_i;
         red_i  += delta_red;  red_i  += delta_red;
         green_i+=delta_green; green_i+=delta_green;
         blue_i += delta_blue; blue_i += delta_blue;
      }
   }
}
//______________________________________________________________________________
Color_ramp_3points::Color_ramp_3points
(nat16 i_colors        // The number of colors in the color ramp.
,nat32 i_low_color
,nat32 i_med_color
,nat32 i_high_color
)
: Color_ramp_2points(i_colors,i_low_color,i_high_color)
, med_color(i_med_color & 0xFFFFFF)
{  // Create color ramp

#ifdef OWL_API
   int16 med_red   = med_color.Red();
   int16 med_green = med_color.Green();
   int16 med_blue  = med_color.Blue();
#else
//060619 #endif
//060619 #ifdef BUILDER_API
   int16 med_red   = med_color & 0x0000FF;
   int16 med_green = (med_color & 0x00FF00) >> 8;
   int16 med_blue  = (med_color & 0xFF0000) >> 16;
#endif

   int16 half_colors =  i_colors/2;

   if (i_colors == 1)
      color_ramp[1] = i_low_color;
   else
   {
   { //low to medium
#ifdef OWL_API

      signed int low_red    = i_low_color.Red();
      signed int  low_green  = i_low_color.Green();
      signed int  low_blue   = i_low_color.Blue();
      #else
//060619 #endif
//060619 #ifdef BUILDER_API
      signed int   low_red   = i_low_color & 0x0000FF;
      signed int   low_green = (i_low_color & 0x00FF00) >> 8;
      signed int   low_blue  = (i_low_color & 0xFF0000) >> 16;
#endif
      float32  delta_red     = (med_red - low_red)    / i_colors; // 060619 i_colors;
      float32  delta_green   = (med_green - low_green)/ i_colors; // 060619 i_colors;
      float32  delta_blue    = (med_blue - low_blue)  / i_colors; // 060619 i_colors;

      float32  red_i = low_red;
      float32  green_i = low_green;
      float32  blue_i = low_blue;

      for (int color_i = 0; color_i < half_colors; color_i++)
      {
#ifdef OWL_API
            color_ramp[color_i] = CORN_color((int16)red_i,(int16)green_i,(int16)blue_i);
#else

          nat32 color_ramp_color_i =  (int32)red_i;
         color_ramp_color_i |= (((int32)green_i) << 8);
         color_ramp_color_i |= (((int32)blue_i) << 16);
         color_ramp[color_i] = color_ramp_color_i;
#endif
         red_i  += delta_red;  red_i  += delta_red;
         green_i+=delta_green; green_i+=delta_green;
         blue_i += delta_blue; blue_i += delta_blue;
      }
   }

   {// medium to high
#ifdef OWL_API
      signed int  high_red   = i_high_color.Red();
      signed int  high_green = i_high_color.Green();
      signed int  high_blue  = i_high_color.Blue();
#else
//060619 #endif
//060619 #ifdef BUILDER_API
      signed int   high_red   = i_high_color & 0x0000FF;
      signed int   high_green = (i_high_color & 0x00FF00) >> 8;
      signed int   high_blue  = (i_high_color & 0xFF0000) >> 16;
#endif

      signed int  delta_red     = (high_red - med_red)      / i_colors; // 060619 i_colors;
      signed int  delta_green   = (high_green - med_green)  / i_colors; // 060619 i_colors;
      signed int  delta_blue    = (high_blue - med_blue)    / i_colors; // 060619 i_colors;

      signed int  red_i    = med_red;
      signed int  green_i  = med_green;
      signed int  blue_i   = med_blue;
      for (int color_i = half_colors; color_i < colors; color_i++)
      {
         color_ramp[color_i] =
#ifdef OWL_API
         CORN_color(red_i,green_i,blue_i);
#else
         red_i | (green_i << 8) | (blue_i << 16);
#endif
         red_i  += delta_red;   red_i  += delta_red;
         green_i+=delta_green;  green_i+=delta_green;
         blue_i += delta_blue;  blue_i += delta_blue;
      }
   }
   }
}
//______________________________________________________________________________
Color_ramp_2points::~Color_ramp_2points()
{  delete [] color_ramp;
}
//______________________________________________________________________________
Scaled_color_ramp::Scaled_color_ramp
(float32 lowest_value_,float32 highest_value_
,nat16 colors_        // The number of colors in the color ramp.
,nat32 low_color_
,nat32 med_color_
,nat32 high_color_
)
:Color_ramp_3points(colors_,low_color_,med_color_,high_color_)
,range         (highest_value_ - lowest_value_)
,lowest_value  (lowest_value_)
,heighest_value(highest_value_)
{}
//______________________________________________________________________________
nat16 Scaled_color_ramp::get_index_of(float32 value)                       const
{  int color_index = ((value - lowest_value)*(colors- 1))/range ; // Colors are indexed from 0
   if (color_index >= colors)
      color_index = colors-1;
   return color_index;
}
//______________________________________________________________________________
nat32 Scaled_color_ramp::get_RGB_color_of(float32 value)                   const
{  int color_index = get_index_of(value);
   return get_color((nat16)color_index);
}
//______________________________________________________________________________
}



