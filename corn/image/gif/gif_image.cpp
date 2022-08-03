#include "corn/image/gif/gif_image.h"
#include "corn/image/gif/gif_lz.h"
#ifdef _Windows
#include <conio.h>
#endif

namespace CORN { namespace GIF {
//______________________________________________________________________________
Image::Image
(Color_map           *global_color_table_
//180213 ,Binary_fstream          &in_strm
,Binary_file_fstream &in_strm
,Extension_control    graphic_control_)
:Image_8bit()
,left(0)
,top(0)
,width(0)
,height(0)
,local_color_table(0)
,global_color_table(global_color_table_)
,color_table       (global_color_table_)
,interlaced(0)
,modified(0)
,graphic_control(graphic_control_)
{
  read(in_strm);
  // color_table = must follow read
  //color_table = /*local_color_table ? local_color_table : */global_color_table;

}
//______________________________________________________________________________
Image::Image
(Color_map *global_color_table_
,nat16 width_, nat16 height_
,nat16 left_ , nat16 top_ )
:Image_8bit()
,Item()
,width (width_)
,height(height_)
,left  (left_)
,top   (top_)
,local_color_table   (0)
,global_color_table  (global_color_table_)
,color_table         (global_color_table_)
,interlaced          (0)
,modified            (1)
{
   redimension(height_,width_,1.0);                                            //180130
   //180130 dimension(i_height,i_width,1.0,0,0,255);                                   //050513
}
//______________________________________________________________________________
void Image::copy_from(const Image &to_be_copied)
{
   Image_8bit::copy_from(to_be_copied);
   //  do not copy container item
   left = to_be_copied.left;
   top = to_be_copied.top;
   width = to_be_copied.width;
   height = to_be_copied.height;
   local_color_table = 0; //cant copy pointers to_be_copied.local_color_table;
   global_color_table = to_be_copied.global_color_table;
   color_table = to_be_copied.color_table;
   interlaced = to_be_copied.interlaced;
   modified = to_be_copied.modified;
   graphic_control.copy_from(to_be_copied.graphic_control);
}
//______________________________________________________________________________
//180213 void Image::write(Binary_fstream &out_strm)
void Image::write(Binary_file_fstream &out_strm)
{
   if (graphic_control.enabled)
      graphic_control.write(out_strm);
   out_strm.write_nat8(GIF_image_separator);
   out_strm.write_nat16(left);
   out_strm.write_nat16(top);
   out_strm.write_nat16(width);
   out_strm.write_nat16(height);

   nat8 packed
   = (local_color_table ? 0x80 : 0x00)
   | (interlaced ? 0x40 : 0x00)
   | (local_color_table && local_color_table->sorted ? 0x02 : 0x00)
   | (local_color_table ? (local_color_table->bits_per_pixel -1) : 0x00);

   out_strm.write_nat8(packed);

   if (local_color_table)
      local_color_table->write(out_strm.provide_stream()/*180213 strm*/);        //180130

   nat8 bits_per_pixel = color_table->bits_per_pixel;

   nat8 code =(bits_per_pixel < 2) ? 2 : bits_per_pixel;
   out_strm.write_nat8(code);   // min code size

   LZ_compresser *compresser = new LZ_compresser
   (out_strm.provide_stream()/*180213 strm*/,bits_per_pixel// color_table->bits_per_pixel
   ,((long) width * (long) height));  // Reset decompress algorithm parameters.

   nat16 row;
   for (row = 0; row < height; row++)
   {
      /* not needed
      #ifdef _Windows
      kbhit();  // let easywin multitask
      #endif
      */
//     cout << '\r' << row; for debugging
      compresser->PixelCount -= width;
      compresser->compress_line(out_strm.provide_stream()/*181212 strm*/,ref_row(row)/*matrix[row]*/,width);
   }
   delete compresser;
   out_strm.write_nat8(0x00); // Block terminator                                //180214
}
//______________________________________________________________________________
Image::~Image()
{
   delete local_color_table;
}
//______________________________________________________________________________
//180213 void Image::read(Binary_fstream &in_strm)
void Image::read(Binary_file_fstream &in_strm)
{
   left        = in_strm.read_nat16();
   top         = in_strm.read_nat16();
   width       = in_strm.read_nat16();
   height      = in_strm.read_nat16();
   nat8 packed = in_strm.read_nat8();
   nat8 bits_per_pixel  = (packed & 0x07) + 1;
   int color_table_size = (1 << bits_per_pixel);
   interlaced = (packed & 0x40);
   bool has_local_color_table = (packed  & 0x80);
   if (has_local_color_table)
         color_table = local_color_table = new Color_map(in_strm.provide_stream()/*180213 strm*/);             //180130
   else  local_color_table = 0;
   long PixelCount = (long) width * (long) height;
   LZ_decompresser *decompresser = new LZ_decompresser(in_strm.provide_stream()/*180213 strm*/);            //180130
      // Reset decompress algorithm parameters.
   redimension(height,width,1.0);                                                //180130_050513
   //180130 dimension(height,width,1.0,0,0,255);                                          //050513
      // actually highest_value is color_table_size
   nat16 row;
   for (row = 0; row < height; row++)
   {
      /*
      #ifdef _Windows
      kbhit(); // let easywin multitask.
      #endif
      */
        decompresser->decompress_line(in_strm.provide_stream()/*180213 strm*/,mod_row(row),width); //180130
   }
   delete decompresser;
}
//______________________________________________________________________________
void Image::recolor(nat8 new_colors[])
{
  for (nat16 i = 0; i < height; i++)  // rows
     for (nat16 j = 0; j < width; j++) // cols
     { nat8 old_color = get_at(i,j);                                            //000128
       if (old_color > 255) // this shouldn't happen
          old_color = 0;
       nat8 new_color = new_colors[old_color];
       point(j,i,new_color);
     }
}
//______________________________________________________________________________
void Image::overlay_image(Image &image_to_overlay,nat16 col,nat16 row)
{ // static to save stack;
  static nat8 map_colors_1[256];
  static nat8 map_colors_2[256];
  color_table->union_colors(image_to_overlay.color_table,map_colors_1,map_colors_2);
  image_to_overlay.recolor(map_colors_2);
  nat16 i;
  nat16 j;
  for (i = 0; i < image_to_overlay.height; i++)
     for (j = 0; j < image_to_overlay.width; j++)
     {
       set_at(i+row+image_to_overlay.top,j+col+image_to_overlay.left             //000129
       ,image_to_overlay.get_at(i,j));                                           //000129
     }
}
//______________________________________________________________________________
//180213 void Image::quantize(int max_colors = 128)
void Image::quantize(nat8 color_index_max_ = 127)
{
   static nat8 new_colors[256];
   color_table->quantize(color_index_max_/*180213 max_colors*/,new_colors);
   recolor(new_colors);
   color_table->remove_duplicate_colors(new_colors);
   recolor(new_colors);
   //180213 color_table->num_colors = max_colors;
   color_table->color_index_max = color_index_max_;                              //180213
}
//______________________________________________________________________________
void Image::set_torus(int16 col, int16 row,nat8 color) // signed row/col
{
   // This function set the color at x,y
   // if X is < 0 or X > width, the dimensions are wrapped around
   if (row < 0)       row = height + row;
   if (row >= height) row = row - height;
   if (col < 0)       col = width + col;
   if (col >= width)  col = col - width;
   set_at(row,col,color);                                                        //000129
}
//______________________________________________________________________________
nat8 Image::get_torus(int16 col, int16 row) // signed row col
{
   // This function returns the color at x,y
   // if X is < 0 or X > width, the dimensions are wrapped around
   if (row < 0)       row = height + row;
   if (row >= height) row = row - height;
   if (col < 0)       col = width + col;
   if (col >= width)  col = col - width;
   return get_at(row,col);                                                       //000129
}
//______________________________________________________________________________
} } // namespace CORN GIF

