#ifndef GIF_animH
#define GIF_animH

#include "corn/image/gif/gif_file.h"
#include "corn/image/gif/gif_image.h"
namespace CORN { namespace GIF {
//______________________________________________________________________________
class Animation_frame
: public Image
{
protected:
   bool new_scene;   // it true this frame will be used as the base (background)
                     // for the optimization of the following frames.
public:
   Animation_frame
      (nat16     width_
      ,nat16     height_
      ,Color_map *global_color_map_ // Animations must all share a common color table
      ,nat16 delay_time
      ,bool       new_scene);
   inline bool is_new_scene()                              { return new_scene; }
   inline void copy_from(const Animation_frame &to_be_copied)
   {
      Image::copy_from(to_be_copied);
      new_scene = to_be_copied.new_scene;
   }
};
//_2000-01-29_______________________________________________________
class Animation : public File
{
 public:
   // Open an existing file
   inline Animation(const char *filename_)
      : File(filename_)
      {}

   // Create a new file
   inline Animation
   (const char *filename_
   ,Color_map *color_map_        // The color map is relinquished to the GIF object
                                  // Do not try to delete/free it.
   ,unsigned int  screen_width_   // should be int16
   ,unsigned int  screen_height_  // should be int16
   ,nat16         iterations_ = 0
      // The number of times to repeat the display of the animation
      // (0 indicates continuous looping)
   )
   : File(filename_,screen_width_,screen_height_)
   {
      animation = true;
      animation_iterations = iterations_;
      global_color_table = color_map_;
   }
   virtual void optimize();
   //  This will modify the images to optimize the overlay images

   Animation_frame &append_frame(nat16 delay_time,bool new_scene);
   // Returns a reference to the current frame
};
//_2000-01-29_______________________________________________________
} } // namespace CORN GIF
#endif
