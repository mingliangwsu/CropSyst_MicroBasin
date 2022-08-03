#ifndef COLORMAPH
#define COLORMAPH
#include <istream>
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/image/clrramp.h"
//______________________________________________________________________________
namespace CORN { namespace GIF {
//______________________________________________________________________________
class Color_map
{
public:
  nat8 color_resolution;
   // Used only in GIFs.
   // It appears that color resolution wasn't ever really used.
   // It may have been intended to document when a GIF image is
   // downgraded from an original image that had a richer set of colors.
   // This value represents the size of the entire palette from which the colors
   // in the graphic were selected, not the number of colors actually used in the graphic.
   // This value should be set to indicate the richness of the original palette,
   // even if not every color from the whole palette is available on the source machine.
   // https://stackoverflow.com/questions/7128265/purpose-of-color-resolution-bits-in-a-gif

  nat8 bits_per_pixel; // For GIFs this would be 8 or less

public:
   //180213 nat8 num_colors;
   nat8 color_index_max;                                                         //180213
   nat8 red  [256]; // The array should actually be dynamic based on bits per pixel
   nat8 green[256];
   nat8 blue [256];
   bool sorted;
public:
   inline Color_map(std::istream &in_strm) {read(in_strm);}
   Color_map(nat8 color_resolution_ = 4,nat8 bits_per_pixel_ = 8);

   Color_map(const CORN::Color_ramp &color_ramp);                                //991115
   // Create a color map given a color ramp.
   // Color 0 is reserved for background color.
   // If color ramp has more than 255 colors they will be quantized.

   void read(std::istream &in_strm);  // reads the color map from the GIF file.
   void write(std::ostream &out_strm); // writes the color map to the GIF file.

   void sort(unsigned long count[],unsigned char change_to[]);
   // Count are the number of pixels in the image with the color of
   // the respective index.
   // change_to are the colors the respective index should be changed to
   // after doing the sort.

   //180213 void quantize(int max_colors, nat8 recolor[]);
   void quantize(nat8 max_color_index, nat8 recolor[]);
   void union_colors(Color_map *color_map_2,nat8 recolor1[],nat8 recolor2[]);
   void remove_duplicate_colors(nat8 recolor[]);
   int find(nat8 r, nat8 g, nat8 b);
   void copy_from(Color_map &map);
   inline void set_color(nat8 index, nat8 red_,nat8 green_, nat8 blue_)          //991220
   {  red  [index] = red_;
      green[index] = green_;
      blue [index] = blue_;
      color_index_max = std::max<nat8>(color_index_max,index);                   //180214
   }
   inline void set_color(nat8 index, uint32 rgb)                                 //000129
   {  red[index]   = (rgb & 0x00FF0000) >> 16 ;
      green[index] = (rgb & 0x0000FF00) >> 8;
      blue[index]  = (rgb & 0x000000FF);
   }
   void dither_safe_colors(bool unix_colors,uint8 start_at=40);                  //000129
      //  Palette commonly used for internet colors.
   void grayscale(nat8 colors=256,uint8 start_at=0);                             //000129
   void EGA();                                                                   //180202
      // 16 color palette used by EGA monitors
};
//______________________________________________________________________________
} } // namespace CORN GIF

// EGA palette index
#define EGA_black           0
#define EGA_blue            1
#define EGA_green           2
#define EGA_cyan            3
#define EGA_red             4
#define EGA_magenta         5
#define EGA_brown           6
#define EGA_gray_light      7
#define EGA_gray_dark       8
#define EGA_blue_light      9
#define EGA_green_light    10
#define EGA_cyan_light     11
#define EGA_red_light      12
#define EGA_magenta_light  13
#define EGA_yellow         14
#define EGA_white          15

#endif