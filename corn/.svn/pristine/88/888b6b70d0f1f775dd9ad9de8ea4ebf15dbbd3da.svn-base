#ifndef GIF_fileH
#define GIF_fileH

// Temporary until we switch over to binrec class
#include <stdio.h>
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/image/gif/gif_image.h"

/*
http://www.onicos.com/staff/iz/formats/gif.html
https://www.w3.org/Graphics/GIF/spec-gif89a.txt
*/

namespace CORN { namespace GIF {
//______________________________________________________________________________
class File
{
 protected:
   CORN::OS::File_name_concrete file_name;
   nat16 screen_width;
   nat16 screen_height;
   nat8 background_color;
   nat8 pixel_aspect_ratio;
      // Aspect Ratio = (Pixel Aspect Ratio + 15) / 64

      // The Pixel Aspect Ratio is defined to be the quotient of the pixel's
      // width over its height.  The value range in this field allows
      // specification of the widest pixel of 4:1 to the tallest pixel of
      // 1:4 in increments of 1/64th.
   Color_map              *global_color_table;  // 0 if no color table. (appears to be owned)
   bool                    animation;
   nat16                   animation_iterations;
   Extension_control       last_graphic_control;
 public:
   Bidirectional_list      images;                                               //991115
   Bidirectional_list plain_texts;                                               //180211
 public:
   // Open an existing file
   File(const char *filename_);
   // Create a new file
   File(const char *filename_,nat16 screen_width_ ,nat16 screen_height_ );
   virtual ~File();
   void read();
   void write();
   /*180130 Images are items so append doesnt need to be specialized
   inline void append(GIF_image *image_to_append);
   */
 private:
   /*180213
   void write_animation_control_block  (Binary_fstream &out_strm);
   void write_global                   (Binary_fstream &out_strm);
   */
   void write_animation_control_block  (Binary_file_fstream &out_strm);
   void write_global                   (Binary_file_fstream &out_strm);
   // The GIF header, global color map (if any)
   // and animation control (if any)

   /*180130  This was used for animations but appears to be replaced
      // In any case simply used Item::write
   void write_current_image(Binary_fstream &out_strm);
   */
   //woid read_animation_control_block();  not implemented yet
 public: // Graphic control extension accessors
   inline void set_transparent_color(nat8 color_index)
   {  last_graphic_control.enabled = true;
      last_graphic_control.use_transparent_color = true;
      last_graphic_control.transparent_color = color_index;
   }
   inline Color_map *get_global_color_table() { return global_color_table;};
   inline Color_map *take_global_color_table(Color_map *i_global_color_table)
   {
      global_color_table = i_global_color_table;
      return global_color_table;
   }
};
//______________________________________________________________________________
} } // namespace CORN GIF

/* NYI
Comment Extension Block

Offset   Length   Contents
  0      1 byte   Extension Introducer (0x21)
  1      1 byte   Comment Label (0xfe)
[
         1 byte   Block Size (s)
        (s)bytes  Comment Data
]*
         1 byte   Block Terminator(0x00)

Plain Text Extension Block

Offset   Length   Contents
  0      1 byte   Extension Introducer (0x21)
  1      1 byte   Plain Text Label (0x01)
  2      1 byte   Block Size (0x0c)
  3      2 bytes  Text Grid Left Position
  5      2 bytes  Text Grid Top Position
  7      2 bytes  Text Grid Width
  9      2 bytes  Text Grid Height
 10      1 byte   Character Cell Width(
 11      1 byte   Character Cell Height
 12      1 byte   Text Foreground Color Index(
 13      1 byte   Text Background Color Index(
[
         1 byte   Block Size (s)
        (s)bytes  Plain Text Data
]*
         1 byte   Block Terminator(0x00)


        iv) Text Grid Left Position - Column number, in pixels, of the left
        edge of the text grid, with respect to the left edge of the Logical
        Screen.

        v) Text Grid Top Position - Row number, in pixels, of the top edge
        of the text grid, with respect to the top edge of the Logical
        Screen.

        vi) Image Grid Width - Width of the text grid in pixels.

        vii) Image Grid Height - Height of the text grid in pixels.

        viii) Character Cell Width - Width, in pixels, of each cell in the
        grid.

        ix) Character Cell Height - Height, in pixels, of each cell in the
        grid.

        x) Text Foreground Color Index - Index into the Global Color Table
        to be used to render the text foreground.

        xi) Text Background Color Index - Index into the Global Color Table
        to be used to render the text background.

        xii) Plain Text Data - Sequence of sub-blocks, each of size at most
        255 bytes and at least 1 byte, with the size in a byte preceding
        the data.  The end of the sequence is marked by the Block
        Terminator.




Application Extension Block

Offset   Length   Contents
  0      1 byte   Extension Introducer (0x21)
  1      1 byte   Application Label (0xff)
  2      1 byte   Block Size (0x0b)
  3      8 bytes  Application Identifire
[
         1 byte   Block Size (s)
        (s)bytes  Application Data
]*
         1 byte   Block Terminator(0x00)

*/
#endif

