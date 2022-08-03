#ifndef GIF_CONTROL_H
#define GIF_CONTROL_H
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
//#include "corn/format/binary/binfstrm.h"
#include "corn/format/binary/binary_file_fstream.h"
namespace CORN { namespace GIF {
//______________________________________________________________________________
class Extension_control // should be named Extension_control
{
 public:
   enum Disposal_method
   { NO_DISPOSAL
               // 0 No disposal specified. The decoder is
               //   not required to take any action.
   , DONT_DISPOSE
               // 1 Do not dispose. The graphic is to be left in place.
   , RESTORE_TO_BACKGROUND
               // 2 Restore to background color. The area used by the
               //   graphic must be restored to the background color.
   , RESTORE_TO_PREVIOUS
               // 3 Restore to previous. The decoder is required to
               //   restore the area overwritten by the graphic with
               //   what was there prior to rendering the graphic.
               // 4-7 -    To be defined.
   };
 public:
   Disposal_method disposal_method;
   bool user_input;
   bool use_transparent_color;
   nat16 delay_time; // number of hundreths of a second
   uint8 transparent_color;
 public:
   bool enabled;
 public:
   inline Extension_control()
      : enabled(0)
      , disposal_method(NO_DISPOSAL)
      , user_input(0)
      , use_transparent_color(0)
      , delay_time(0) // no delay
      , transparent_color(0)
      {}
   inline Extension_control(const Extension_control &copy)
      : enabled(copy.enabled)
      , disposal_method(copy.disposal_method)
      , user_input(copy.user_input)
      , use_transparent_color(copy.use_transparent_color)
      , delay_time(copy.delay_time)
      , transparent_color(copy.transparent_color)
      {}
   void read(Binary_file_fstream &in_strm);
   void write(Binary_file_fstream &out_strm);
   /*170213
   void read(Binary_fstream &in_strm);
   void write(Binary_fstream &out_strm);
   */
   void copy_from(const Extension_control& to_be_copied);
};
//______________________________________________________________________________
} } // namespace CORN GIF

#endif