#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#include <fstream.h>

uint8 hex_digit_to_byte(char hex_digit)
{
   uint8 result = 0;
   if (hex_digit >= 'a')
      result = hex_digit - 'a' +10;
   else if (hex_digit >= 'A')
      result = hex_digit - 'A' +10;
   else
      result = hex_digit -'0';
   return result;
};

uint8 hex_str_to_byte(const char *byte_code)
{
   char upper_nyble_code = byte_code[0];
   char lower_nyble_code = byte_code[1];
   uint8 result = (hex_digit_to_byte(upper_nyble_code) << 4) | hex_digit_to_byte(lower_nyble_code);
   return result;
};

//   static char buffer[14000];

int main(int argc, char *argv[])
{
   string line;

//   ifstream for_header("act_test.xls");
   ofstream xls_out (argv[2],ios::binary);

//   for_header.read(buffer,13824);
//   xls_out.write(buffer,13824);



   ifstream bd5_dump(argv[1]);

//   uint8 header_buffer[1024];
//   for_header.read(header_buffer,512);
//   xls_out.write(header_buffer,512);

   uint32 bytes_written = 0;
   uint32 padding_needed = 4096;
   while (!bd5_dump.eof())
   {
      line.read_line(bd5_dump);
      if (line.c_str()[5] == ' ')
      {
         for (int ci = 0; ci < 16; ci++)
         {
            string byte_code(line.substr((7+ci*3),2));
            if (byte_code != "--")
            {
               uint8 byte = hex_str_to_byte(byte_code.c_str());
               xls_out << byte;
               bytes_written ++;
               padding_needed--;
               if (padding_needed == 0)
                  padding_needed = 4096;
            };
         };
      };
   };
   // Pad to 4096 bytes.

   cout << "Data bytes:" <<bytes_written << endl;
   if (padding_needed)
   for (uint16 i = 0; i < padding_needed; i++)
   {
       xls_out << '.';
       bytes_written ++;
   };
   cout << "total bytes:" <<bytes_written << endl;

};
