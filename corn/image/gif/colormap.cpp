#include "corn/image/gif/colormap.h"

static bool deleted_colors[256];
namespace CORN { namespace GIF {
//______________________________________________________________________________
Color_map::Color_map(nat8 color_resolution_,nat8 bits_per_pixel_)
:color_resolution (color_resolution_)
,bits_per_pixel   (bits_per_pixel_)
,color_index_max  ((1 << bits_per_pixel_)-1)                                   //180213
//180213 ,num_colors       (1 << bits_per_pixel_)
{}
//______________________________________________________________________________
Color_map::Color_map(const CORN::Color_ramp &color_ramp)
:color_resolution (4)  // I think
,bits_per_pixel   (8)
,color_index_max  ((1 << 8)-1)                                                   //180213
//180213 ,num_colors  ((1 << 8)-1)
{
   nat16 colors_in_ramp = color_ramp.count_colors();
   float color_ramp_step  // float because
      = (colors_in_ramp > color_index_max /*180213 num_colors*/)
      ? (float)colors_in_ramp / (float)color_index_max /*180213 num_colors*/
      : 1.0;
   red  [0] = 0;  // Default background color is black.
   green[0] = 0;
   blue [0] = 0;
   float color_ramp_index = 1;
   for (nat8 color_map_index = 1 // Leave index 0 for background color
       ;color_map_index <= color_index_max //180213 < num_colors
       ;color_map_index++)
   {
      red  [color_map_index] = (color_ramp.get_color((nat16)color_ramp_index) & 0x0000FF);
      green[color_map_index] = (color_ramp.get_color((nat16)color_ramp_index) & 0x00FF00) >> 8;
      blue [color_map_index] = (color_ramp.get_color((nat16)color_ramp_index) & 0xFF0000) >> 16;
      /* I think this syntax was for OWL UI
      red  [color_map_index] = color_ramp.get_color((nat16)color_ramp_index).Red();
      green[color_map_index] = color_ramp.get_color((nat16)color_ramp_index).Green();
      blue [color_map_index] = color_ramp.get_color((nat16)color_ramp_index).Blue();
      */
      color_ramp_index += color_ramp_step;
   }
}
//______________________________________________________________________________
void Color_map::read(istream  &in_strm)
{
   for (nat8 i = 0; i <= color_index_max /*180213 < num_colors*/; i++)
   { red  [i] = in_strm.get();
     green[i] = in_strm.get();
     blue [i] = in_strm.get();
   }
}
//______________________________________________________________________________
void Color_map::write(ostream &out_strm)
{
   for (nat8 i = 0; i <= color_index_max /*180213 < num_colors*/; i++)
   { out_strm.put(red  [i]);
     out_strm.put(green[i]);
     out_strm.put(blue [i]);
   }
}
//______________________________________________________________________________
int Color_map::find(nat8 r, nat8 g, nat8 b)
{  nat8 min_avg = 0xff;
   nat8 index = 0;
   for (nat8 i = 0; i <= color_index_max /*180213 < num_colors*/; i++)
   {  int dr = abs(r - red[i]);
      int dg = abs(g - green[i]);
      int db = abs(b - blue[i]);
      int avg = (dr + dg + db) /3;
      if (avg < min_avg)
      {  min_avg = avg;
         index = i;
      }
   }
   return index;
}
//______________________________________________________________________________
void Color_map::union_colors(Color_map *color_map_2,nat8 recolor1[],nat8 recolor2[])
{
  // At this time I am not modifying the base image's color map
   for (nat8 i = 0; i <= color_index_max /*180213 < num_colors*/; i++)
   {  recolor1[i] = i;
      recolor2[i] = i;
   }
   //180213 if ((num_colors + color_map_2->num_colors) <= 256)
   nat16 new_color_index_max                                                     //180213
      = (color_index_max+1) + (color_map_2->color_index_max+1) -1;                //180213
   //180213 if ((num_colors + color_map_2->num_colors) <= 256)
   if (new_color_index_max <= 255)
   {  // Add the second color map to the end of the color map.
      //180213 for (i = 0; i < color_map_2->num_colors; i++)
      nat8 append_index = color_index_max+1;                                     //180213
      for (nat8 i = 0; i <= color_map_2->color_index_max; i++)                   //180213
      {
         recolor2[i] = append_index;
         color_map_2->red  [append_index] = color_map_2->red  [i];
         color_map_2->green[append_index] = color_map_2->green[i];
         color_map_2->blue [append_index] = color_map_2->blue [i];
         red   [append_index] = color_map_2->red   [i];
         green [append_index] = color_map_2->green [i];
         blue  [append_index] = color_map_2->blue  [i];
         if (append_index < 255)
            append_index++;
     }
     color_index_max = append_index;
     //180213 num_colors = num_colors + color_map_2->num_colors;
  }
  else
  { int colors_reused = 0;
    for (nat8 i = 0; i <= color_map_2->color_index_max/*180213 < color_map_2->num_colors*/; i++)
    { recolor2[i] = 255;
      int min_dr = 256;
      int min_dg = 256;
      int min_db = 256;
      //180213 for (int j = 0; j < num_colors; j++)
      for (nat8 j = 0; j <= color_index_max; j++)                                //180213
      {  int dr = abs(red[j]   - color_map_2->red[i]);
         int dg = abs(green[j] - color_map_2->green[i]);
         int db = abs(blue[j]  - color_map_2->blue[i]);
         #define SAME_COLOR_RANGE 10
        if (dr < min_dr && dg < min_dg && db < min_db)
        {
           // If the second image color is similar to this first color
           // then substitute the color
           recolor2[i] = j;
           colors_reused += 1;
           min_dr = dr;
           min_dg = dg;
           min_db = db;
        }
      // else // can't permit more than 255 color.
      //    recolor2[i] = (num_colors < 256) ? num_colors++ : 255;
      }
    }
   // std::clog << "Colors reused:" << colors_reused << endl; for debugging
  }
}
//______________________________________________________________________________
void Color_map::copy_from(Color_map &map)
{
   for (nat16 i = 0; i < 256; i++)
   {  red  [i] = map.red  [i];
      green[i] = map.green[i];
      blue [i] = map.blue [i];
   }
   color_resolution = map.color_resolution;
   bits_per_pixel = map.bits_per_pixel;
   //180213 num_colors = map.num_colors;
   color_index_max = map.color_index_max;
   sorted = map.sorted;
}
//______________________________________________________________________________

void Color_map::remove_duplicate_colors(nat8 recolor[])
{
   for (nat16 i = 0; i < 256; i++)
      recolor[i] = i;
  //180213 int new_num_colors = num_colors;
  //180213   new_num_colors = 255;
  //180223 int new_color_index_max = color_index_max;
   nat8 new_color_index_max = 255;
   for (nat16 i = 0 ;i < 255; i++)
   {
      if (deleted_colors[i])
      {
         new_color_index_max --;
         //180213 new_num_colors -= 1;

         for (nat16 j = i; j <  255; j++)
         {  red  [j] =   red[j+1];
            green[j] = green[j+1];
            blue [j] =  blue[j+1];
            if (recolor[j] > i)
               recolor[j] = recolor[j] -1;
            deleted_colors[j] = deleted_colors[j+1];
            deleted_colors[255] = 0;
         }
         i--;
     }
  }
  //180213 num_colors = new_num_colors;
  color_index_max = new_color_index_max;
}
//______________________________________________________________________________
void Color_map::quantize(nat8 max_color_index/*180213 int max_colors*/, nat8 recolor[])
{
//     not used
//    static long frequency[256];
//    for (i = 0; i < 256; i++)
//      frequence[i] = 0;
//
//    for (i = 0; i < height; i++)
//      for (j = 0; j < width ; j++)
//         frequency[matrix[i][j]] += 1;

   for (nat16 i = 0; i < 256; i++)
   {
      deleted_colors[i] = 0;
      recolor[i] = i;
   }
   int num_deleted = 0;
   int tolerance = 10;
   //180213 while ((num_colors - num_deleted) > max_colors)
   while ((color_index_max - num_deleted) > max_color_index)
   {  for (nat16 i = 0; (i < 256) ; i++)
      if (!deleted_colors[i])
      {  nat8 min_dr = 255; nat8 min_dg = 255; nat8 min_db = 255;
         int min_index = 255;
         for (nat16 j = i+1; j < 256; j++)
         {  if (i != j)
            {  nat8 dr = abs(red[j] - red[i]);
               nat8 dg = abs(green[j] - green[i]);
               nat8 db = abs(blue[j] - blue[i]);
               if ((dr < min_dr) && (dg < min_dg) && (db < min_db) &&
                   (dr < tolerance) && (dg < tolerance) && (db < tolerance)
                   && (!deleted_colors[j]))
               {  min_dr = dr; min_dg = dg; min_db = db;
                  min_index = j;
         }  }  }
         if (min_index < 255)
         {  deleted_colors[min_index] = 1;
            recolor[min_index] = i;
      }  }
      tolerance += 1;
      num_deleted = 0;
      for (nat16 i = 0; i < 256; i++)
         num_deleted += deleted_colors[i];
}  }
//______________________________________________________________________________
void Color_map::dither_safe_colors(bool unix_colors,uint8 start_at)
{  nat8 incr = unix_colors ? 0x33 : 0x40;
   nat8 index = 0;
   bits_per_pixel = 8;
   for (nat16 r = 0; r <= 0xff; r+=incr)
   {  for (nat16 g = 0; g <= 0xff; g+=incr)
      {  for (nat16 b = 0; b <= 0xff; b+=incr)
         {  set_color(index,r,g,b);
            index ++;
}  }  }  }
//_2000-01-29___________________________________________________________________
void Color_map::grayscale(nat8 colors,uint8 start_at)
{  nat8 incr = 256 / colors;
   bits_per_pixel = 8;
   for (nat16 index = start_at; index < 256; index += incr)
      set_color(index,index,index,index);
}
//_2000-01-29___________________________________________________________________

#define EGA_RGB_black         0x000000
#define EGA_RGB_blue          0x0000AA
#define EGA_RGB_green         0x00AA00
#define EGA_RGB_cyan          0x00AAAA
#define EGA_RGB_red           0xAA0000
#define EGA_RGB_magenta       0xAA00AA
#define EGA_RGB_brown         0xAA5500
#define EGA_RGB_gray_light    0xAAAAAA
#define EGA_RGB_gray_dark     0x555555
#define EGA_RGB_blue_light    0x5555FF
#define EGA_RGB_green_light   0x55FF55
#define EGA_RGB_cyan_light    0x55FFFF
#define EGA_RGB_red_light     0xFF5555
#define EGA_RGB_magenta_light 0xFF55FF
#define EGA_RGB_yellow        0xFFFF55
#define EGA_RGB_white         0xFFFFFF

//______________________________________________________________________________
void Color_map::EGA()
{  // http://www.shikadi.net/moddingwiki/EGA_Palette
   //180213 num_colors = 16;
   color_index_max = 15;
   static const nat8 EGA_palette[16] =
      {0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63 };
   bits_per_pixel = 4;
   for (nat8 index = 0; index < 16; index++)
   {
      nat8 ega = EGA_palette[index];
      nat8 red   = 85 * (((ega >> 4) & 2) | (ega >> 2) & 1);
      nat8 green = 85 * (((ega >> 3) & 2) | (ega >> 1) & 1);
      nat8 blue  = 85 * (((ega >> 2) & 2) |  ega       & 1);
      set_color (index,red,green,blue);
   }
   set_color(6,0xAA,0x55,0x00); //brown
}
//_2018-02-02__________________________________________________________________/

}} // namespace CORN GIF

