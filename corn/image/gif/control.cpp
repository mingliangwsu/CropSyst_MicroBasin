#include "corn/image/gif/common.h"
#include "corn/image/gif/control.h"
namespace CORN { namespace GIF {
//______________________________________________________________________________
void Extension_control::read(Binary_file_fstream &in_strm)
//180213 void Extension_control::read(Binary_fstream &in_strm)
{
  // extension introducer and graphic control label
  // will already have been read in order to determine
  // that this is a graphic control extension.
  nat8 block_size = in_strm.read_nat8(); //180130 get();
   // block size is not used, should be 4

  nat8 packed = in_strm.read_nat8(); //180130 get();
  disposal_method = (packed & 0x1C) >> 2;
  user_input = (packed & 0x02) != 0;
  use_transparent_color = packed & 0x01;

  delay_time = in_strm.read_nat16();
  transparent_color = in_strm.read_nat8(); //180130 get();
  nat8 block_terminator = in_strm.read_nat8(); //180130 get();
      // block terminator, should be 0
  enabled = true;
}
//______________________________________________________________________________
//180213 void Extension_control::write(Binary_fstream &out_strm)
void Extension_control::write(Binary_file_fstream &out_strm)
{
  out_strm.write_nat8/*180130 put*/(GIF_extension_introducer);
  out_strm.write_nat8/*180130 put*/(GIF_graphic_control_extension);
  out_strm.write_nat8/*180130 put*/((nat8)4); // size of the control block
  nat8 packed
  = ((nat8)disposal_method << 2)
  | (user_input ? 0x02 : 0x00)
  | (use_transparent_color ? 0x01 : 0x00);

  out_strm.write_nat8/*180130 put*/(packed);
  out_strm.write_nat16(delay_time);
  out_strm.write_nat8/*180130 put*/(transparent_color);
  out_strm.write_nat8/*180130 put*/((nat8)0);
}
//______________________________________________________________________________
void Extension_control::copy_from(const Extension_control& to_be_copied)
{
    disposal_method = to_be_copied.disposal_method;
    user_input = to_be_copied.user_input;
    use_transparent_color = to_be_copied.use_transparent_color;
    delay_time = to_be_copied.delay_time; // number of hundreths of a second
    transparent_color = to_be_copied.transparent_color;
    enabled = to_be_copied.enabled;
}
//______________________________________________________________________________
}} // namespace CORN GIF



