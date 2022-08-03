

#include <corn/image/gif/gif_file.h>
#include <corn/image/gif/gif_image.h>

void main()
{
   GIF_file test("test.gif",100,100);
   color_map *global_color_map = new color_map();
   global_color_map->setup_internet_colors();
   test.take_global_color_table(global_color_map);
   GIF_image *test_image = new GIF_image(test.get_global_color_table(),100,100);
   test_image->line(0,0,100,100,1);
   test.append(test_image);
   test.write();

};