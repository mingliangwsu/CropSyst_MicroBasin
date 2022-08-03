#ifndef image8H
#define image8H

/* This class adds the grid data structure for 8bit images.
*/

//continue here base this on grid/grid_T
#include <corn/image/image_base.h>
/*180130
#include <corn/image/grid/uint8.h>
*/
#include "corn/grid/grid_T.h"

namespace CORN {
//______________________________________________________________________________
class Image_8bit
: public Image_base
, public extends_ Grid<nat8>
/*180130
, public Image_grid_uint8
*/
{
public:
   inline Image_8bit(){}
/*180130 This may be obsolete, may implement copy constructor
   void copy_from(const Image_8bit &to_be_copied)
   {  Image_base::copy_from(to_be_copied);
      Grid<nat8>::copy_from(to_be_copied);
      //180130       Image_grid_uint8::copy_from(to_be_copied);
   };
*/
   inline virtual nat16 get_width()  const { return get_cols();} // in pixels
   inline virtual nat16 get_height() const { return get_rows();} // in pixels
   inline virtual void point(nat16 x, nat16 y, Image_color_index color)
      {  set_at(y,x,(uint8)color); }
};
//____________________________________________________________class Image_8bit_/
} // namespace CORN
#endif

