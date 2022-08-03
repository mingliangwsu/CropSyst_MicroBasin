#include "corn/image/gif/gif_anim.h"
namespace CORN { namespace GIF {
//______________________________________________________________________________
void Animation::optimize()
{  Animation_frame *current_background = 0;
   Bidirectional_list unoptimized_images;
   unoptimized_images.transfer_all_from(images);
   for (Animation_frame *frame = (Animation_frame *)
         unoptimized_images.pop_at_head()
       ; frame
       ; frame = (Animation_frame *)unoptimized_images.pop_at_head())
   {  Animation_frame &optimized_frame = append_frame
         (frame->graphic_control.delay_time,false);
      if (frame->is_new_scene())
      {  if (current_background)
            delete current_background;
         current_background = frame;
         // copy the frame exactly to optimized frame
         optimized_frame.copy_from(*frame);
      }
      else
      {  for (nat16 row = 0; row < frame->get_rows(); row++)
         {  for (nat16 col = 0; col < frame->get_cols(); col++)
            {  nat8 frame_color = frame->get_at(row,col);
               nat8 opt_color = frame_color;
               nat8 back_color = current_background->get_at(row,col);
               if (frame_color == back_color)
                  opt_color = frame->graphic_control.transparent_color;;
               optimized_frame.set_at(row,col,opt_color);
            }
         }
         delete frame;
      }
   }
   if (current_background)
      delete current_background;
}
//______________________________________________________________________________
Animation_frame::Animation_frame
(nat16 width_
,nat16 height_
,Color_map *global_color_table_ // Animations must all share a common color table
,nat16 delay_time
,bool new_scene_)
: Image(global_color_table_,width_, height_,0,0)
, new_scene(new_scene_)
{  color_table = global_color_table_;
   // These image options are required to implement optimized animations
   graphic_control.disposal_method = Extension_control::DONT_DISPOSE;
   graphic_control.user_input = false;
   graphic_control.use_transparent_color = true;
   graphic_control.transparent_color = 0;
   graphic_control.enabled = true;
   graphic_control.delay_time = delay_time;
}
//______________________________________________________________________________
Animation_frame &Animation::append_frame(nat16 delay_time,bool new_scene)
{  bool starting_frame = images.count() == 0;
   if (starting_frame) // First frame must always new a new scene
      new_scene = true;
   Animation_frame *current_frame =                                          //991115
         current_frame = new Animation_frame
         (screen_width,screen_height,global_color_table,delay_time,new_scene);
   images.append(current_frame);
   return *current_frame;
}
//______________________________________________________________________________
} } // namespace CORN GIF


