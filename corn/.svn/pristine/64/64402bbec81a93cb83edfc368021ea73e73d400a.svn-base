#ifndef CORN_COLOR_RAMP_H
#define CORN_COLOR_RAMP_H
#include "corn/const.h"
#include "corn/primitive.h"

// A color ramp is graduated array of colors ranging from one RGB color to another RGB color.
// This color map is in graphical representations such as Gray scales, elevation, and temperature visualization

#define RGB_to_BGR(color) \
 ((((nat8)(nat16)(((color &0xFF0000) >> 16)) | ((nat16)(((color &0x00FF00) >> 8))<<8)) | (((nat32)(nat8)(nat16)((color &0x0000FF)))<<16)))

// #include <corn/no_ns.h>
namespace CORN {
//_____________________________________________________________________________/
interface_ Color_ramp
{  virtual nat32 get_color(nat16 i)                                     const=0;
   virtual nat16 count_colors()                                         const=0;
};
//_2018-01-30__________________________________________________________________/
class Color_ramp_2points
:public implements_ Color_ramp
{
protected:
   nat32 *color_ramp;
   nat32  low_color;
   nat32  high_color;
   nat16  colors;
public:
   Color_ramp_2points
      (nat16 colors_        // The number of colors in the color ramp.
      ,nat32 low_color_
      ,nat32 high_color_);
   virtual ~Color_ramp_2points();
   inline virtual nat32 get_color(nat16 i)                                 const
      {  i = (i < colors) ? i : colors;
          return  color_ramp[i]; }
   //180218 inline virtual nat16 get_colors()                const { return colors;     }
   inline virtual nat16 count_colors()              const { return colors;}      //180218
   inline nat32 get_low_color()                     const { return low_color;  }
   inline nat32 get_high_color()                    const { return high_color; }
};
//_2006-06-19__________________________________________________________________/
class Color_ramp_3points
: public Color_ramp_2points
{
protected:
   nat32  med_color;
public:
   Color_ramp_3points
      (nat16 i_colors        // The number of colors in the color ramp.
      ,nat32 i_low_color
      ,nat32 i_med_color
      ,nat32 i_high_color
      );
public: // accessors
   inline nat32 get_med_color()                      const { return med_color; }
};
//_____________________________________________________________________________/
class Scaled_color_ramp
: public Color_ramp_3points
{
   // This is a color ramp where the range of values to be colored is specified
private:
   float32  range;
protected:
   float32  lowest_value;
   float32  heighest_value;
public:
   Scaled_color_ramp
      (float32 _lowest_value,float32 _highest_value
      ,nat16 _colors        // The number of colors in the color ramp.
      ,nat32 _low_color
      ,nat32 _med_color
      ,nat32 _high_color);
   nat32 get_RGB_color_of(float32 value)                                  const;
   // returns the color used for the specified by value;
   nat16 get_index_of(float32 value)                                      const;
};
//_____________________________________________________________________________/
} // namespace CORN
#endif

