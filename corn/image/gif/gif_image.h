#ifndef GIF_imageH
#define GIF_imageH

#include "corn/container/unilist.h"
#include "corn/image/image8.h"
#include "corn/image/gif/control.h"
#include "corn/image/gif/colormap.h"
namespace CORN { namespace GIF {
//______________________________________________________________________________
class Image
: public Image_8bit
, public Item
{
 protected:
   Color_map  *local_color_table;   // 0 if not local color table
   Color_map  *global_color_table;  // Image must point to global color table
   Color_map  *color_table;         // points to either the local or the global color table
 public:
   nat16 left;    // 0 indexed
   nat16 top;   // 0 indexed
   nat16 width;
   nat16 height;
   bool interlaced;
   bool modified;
   Extension_control graphic_control;
 public:
   Image
      (Color_map *global_color_table_
      ,nat16 width_, nat16 height_
      ,nat16 left_ = 0,nat16 top_ = 0);
   Image
      (Color_map *global_color_table_
      //180213 , Binary_fstream &in_strm
      ,Binary_file_fstream &in_strm
      ,Extension_control graphic_control_);
   virtual ~Image();
   void read (Binary_file_fstream &in_strm);  // reads the image from the GIF file
   void write(Binary_file_fstream &out_strm); // writes the image to the GIF file
   /*180213
   void read(Binary_fstream &in_strm);  // reads the image from the GIF file
   void write(Binary_fstream &out_strm); // writes the image to the GIF file
   */

 public: // Image accessors
   void set_torus(int16 col, int16 row,nat8 color);
   nat8 get_torus(int16 col, int16 row);
   // This function returns the color at x,y
   // if X is < 0 or X > width, the dimensions are wrapped around
 public: // Drawing primatives
   inline void set_transparent_color(nat8 color_index)
   {  graphic_control.enabled = true;
      graphic_control.use_transparent_color = true;
      graphic_control.transparent_color = color_index;
   }
   inline virtual Image_color_index get_transparent_color()                                    //000129
   { return graphic_control.transparent_color; }
 public: // Advanced drawing
   void overlay_image(Image &image_to_overlay,nat16 col,nat16 row);
   void copy_from(const Image &to_be_copied);
 public: // Color optimization
   //void change_colors(nat8 new_colors[]);
   void recolor(nat8 new_colors[]);
   void quantize(nat8 max_color_index_);
   //180213 void quantize(int max_colors);
   inline Color_map *take_color_table(Color_map *i_color_table)
   {  color_table = local_color_table = i_color_table;
      return color_table;
   }
 private:
   inline const nat8 *ref_row(nat16 row_index)  const { return grid[row_index];} //180130
   inline       nat8 *mod_row(nat16 row_index)  const { return grid[row_index];} //180130
};
//_1999-11-15______________________________________________________________________________________
} } // namespace CORN GIF

#endif