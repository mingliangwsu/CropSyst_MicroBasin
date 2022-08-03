
#include "corn/image/gif/gif_file.h"
#include "corn/image/gif/common.h"
namespace CORN { namespace GIF {
//______________________________________________________________________________
File::File(const char *filename_)
:file_name           (filename_)
,screen_width        (0)
,screen_height       (0)
,background_color    (0)
,pixel_aspect_ratio  (0)
,global_color_table  (0)
,animation           (false)
,animation_iterations(0)
,last_graphic_control()
,images              ()                                                                        //991115
{  read();
}
//______________________________________________________________________________
// Output file
File::File(const char *filename_,nat16 screen_width_ ,nat16 screen_height_)
:file_name(filename_)
,screen_height(screen_height_)
,screen_width(screen_width_)
,background_color(0)
,pixel_aspect_ratio(0)
,global_color_table(0)
,animation           (false)
,animation_iterations(0)
,last_graphic_control()
,images()                                                                        //991115
{}
//______________________________________________________________________________
int GIF_skip_extension_block(istream &in_strm)
{
    nat8 extension_length = in_strm.get();
    if (extension_length)
    { nat8 buf[256];
      in_strm.read(buf, extension_length);
      if (in_strm.gcount() != extension_length)
         return GIF_ERROR;
      buf[extension_length] = 0;
//      cout << buf << endl; for debugging
    }
    return GIF_OK;
}
//______________________________________________________________________________
int GIF_skip_comment(istream &in_strm)
{
    nat8 extension_code = in_strm.get();
    return GIF_skip_extension_block(in_strm);
}
//______________________________________________________________________________
void File::read()
{
   Binary_file_fstream in_strm(file_name.c_str(),false,std::ios::in);
      // GIF files are little endian
      // See http://www.onicos.com/staff/iz/formats/gif.html
   //180213 Binary_fstream in_strm(file_name.c_str(),true);
   if (in_strm.good())
   {

  char gif_version[7];
  //180213 in_strm.read_cstr((char *)&gif_version,6);                                     //180130
  in_strm.read((char *)&gif_version,6);
  gif_version[6] = 0;
  // Check here for valid gif header

  // read screen width
  screen_width  = in_strm.read_nat16();
  screen_height = in_strm.read_nat16();

  nat8 packed_field  = in_strm.read_nat8();

  nat8 color_resolution = (((packed_field & 0x70) + 1) >> 4) + 1;
  nat8 bits_per_pixel = (packed_field & 0x07) + 1;
  bool global_color_map_enabled = packed_field & 0x80;

  background_color   = in_strm.read_nat8();
  pixel_aspect_ratio = in_strm.read_nat8();

  if (global_color_map_enabled)
  {
     global_color_table = new Color_map(color_resolution,bits_per_pixel);
     global_color_table->read(in_strm.provide_stream()/*180213 strm*/ );         //180130
  }
  else
     global_color_table = 0;

  while (!in_strm.at_eof()) // may need to be while(in_strm.good())   eof())
  {
    nat8 record_type = in_strm.read_nat8();
    switch(record_type)
    {
      case GIF_image_separator :  // ','
         images.append(new Image(global_color_table,in_strm,last_graphic_control));
          last_graphic_control.enabled = false;
      break;
      case GIF_extension_introducer : // '!'
      {
          nat8 extension_code = in_strm.read_nat8();
          switch (extension_code)
          { case GIF_graphic_control_extension :
               last_graphic_control.read(in_strm);
            break;
            case GIF_application_extension :
            {  nat8 length = in_strm.read_nat8();
               char extension_label[50];
               in_strm./*strm.*/read(extension_label,length);                        //180130
               nat8 block_length = in_strm.read_nat8();
               if (strncmp(extension_label,"NETSCAPE2.0",block_length) == 0)
               {  nat8 one = in_strm.read_nat8(); // Should be 1
                  animation_iterations = in_strm.read_nat16();
               }
               else // I don't know what the extension is so just throw it away.
               {  char *buffer = (char *)malloc(block_length +1);
                  in_strm.read(buffer,block_length);
                  free(buffer);
               }
               nat8 block_terminator = in_strm.read_nat8/*get*/(); // should be 0 the block terminator
            }
            break;
            default :
              GIF_skip_extension_block(in_strm.provide_stream()/*180213.strm*/);
              nat8 block_terminator = in_strm.read_nat8(); //180130 get();
            break;
          }
          // num_extensions += 1;
          // extensions[num_extensions] = new extension(in_file);
      }
      break;
      case GIF_comment_extension :
         GIF_skip_comment(in_strm.provide_stream()/*180213 strm*/);
      break;
      case GIF_trailer : // ';'
         // TERMINATE_RECORD_TYPE;
         return;
      default:
//       *Type = UNDEFINED_RECORD_TYPE;
//       RGIFERROR = D_GIF_ERR_WRONG_RECORD;
       return; // GIF_ERROR;
    }
  }
  }
}
//______________________________________________________________________________
//180213 void File::write_global(Binary_fstream &out_strm)
void File::write_global(Binary_file_fstream &out_strm)
{
   char gif_version[7] = "GIF89a";
//180213   out_strm.write_cstr(gif_version,false); //fwrite(&gif_version,1,6,file);
   out_strm.write(gif_version,6); //fwrite(&gif_version,1,6,file);

   // read screen width
   out_strm.write_nat16(screen_width);
   out_strm.write_nat16(screen_height);

   nat8 has_color_table =  global_color_table ? 0x80 : 0x00;
   nat8 color_res_bits = (global_color_table ? ((global_color_table->color_resolution - 1) << 4) : 0x00);
   nat8 color_table_sorted = ((global_color_table && global_color_table->sorted) ? 0x04 : 0x00);
   nat8 color_table_bits_per_pixel = (global_color_table ? (global_color_table->bits_per_pixel -1) : 0x00);

   nat8 packed_field = has_color_table | color_res_bits | color_table_sorted | color_table_bits_per_pixel;

   out_strm.write_nat8(packed_field);

   out_strm.write_nat8(background_color);
   out_strm.write_nat8(pixel_aspect_ratio);

   if (global_color_table)
      global_color_table->write(out_strm.provide_stream()/*180213 strm*/);       //180130

   // Animation control block follows the global color table
   if (animation)
      write_animation_control_block(out_strm);
}
//______________________________________________________________________________
void File::write()
{
   //180213 Binary_fstream out_strm(file_name.c_str(),false);
   Binary_file_fstream out_strm(file_name.c_str(),false,std::ios::out);          //180213
      // GIF files are little endian
      // See http://www.onicos.com/staff/iz/formats/gif.html

   write_global(out_strm);
   /*180130
   for (GIF_image *image = (GIF_image *)images.move_to_head()                    //991115
       ;image                                                                    //991115
       ;image = (GIF_image *)images.move_to_next())                              //991115
   */

   FOR_EACH_IN(image,Image,images,each_image)                                    //180130
   {  image->write(out_strm);                                                    //991115
   } FOR_EACH_END(each_image);                                                   //180130

   /*180211 NYI
   FOR_EACH_IN(text,Plain_text_extension,plain_texts,each_text)                  //180211
   {  text->write(out_strm);
   } FOR_EACH_END(each_text)
   */
  out_strm.write_nat8(GIF_trailer);
}
//______________________________________________________________________________
//180213 void File::write_animation_control_block(Binary_fstream &out_strm)
void File::write_animation_control_block(Binary_file_fstream &out_strm)          //180218
{
  out_strm.write_nat8(GIF_extension_introducer);
  out_strm.write_nat8(GIF_application_extension);
  out_strm.write_nat8((nat8)0x0B); // animation extension length
  char netscape2_0[11] = "NETSCAPE2.0";
  out_strm.write(netscape2_0,11);
  //180213 out_strm.write_cstr(netscape2_0,false);                                        //180130
  out_strm.write_nat8((nat8)0x03); // length of animation block
  out_strm.write_nat8((nat8)0x01);
  out_strm.write_nat16(animation_iterations);
  out_strm.write_nat8((nat8)0x00);
}
//______________________________________________________________________________
/*180130  This was used for animations but appears to be replaced
      // In any case simply used Item::write

void File::write_current_image(Binary_fstream &out_strm)
{
   GIF_image *current_image = (GIF_image *)images.current();                     //991115
   if (current_image)                                                            //991115
      current_image->write(out_strm);
}
//______________________________________________________________________________
*/
/*180130 Images are items so append doesnt need to be specialized
void File::append(GIF_image *image_to_append)
{ images.append(image_to_append); }
*/
//______________________________________________________________________________
File::~File()
{
  delete global_color_table;
  // not needed, lists are cleared when go outof scope images.delete_all();      //991115
}
//______________________________________________________________________________
} } // namespace CORN GIF



