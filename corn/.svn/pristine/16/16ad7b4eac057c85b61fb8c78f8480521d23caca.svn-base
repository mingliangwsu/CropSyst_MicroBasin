#ifdef _MSC_VER
// MSC does not have values.h?!?!
#  define MAXLONG 0x7FFFFFFF
#  include <string.h>
#else
#  include <values.h>
#endif
#include "corn/format/binary/binfstrm.h"
#ifdef unix
// unix doesn't have, or is already, in binary mode?
#  define OR_IOS_BINARY
#else
// I think this may be DOS/Windows specific, so the ifdef would be if not __MSDOS__
#  define OR_IOS_BINARY   |std:: ios::binary
#endif
namespace CORN {
//______________________________________________________________________________
bool CPU_is_big_endian()
{  nat16 i = 1;                                                                  //020204
   return ((*(char *)&i) == 0);
}
//_2001-06-08___________________________________________________________________
Binary_fstream::~Binary_fstream()
{  delete [] file_name;
   file_name = 0;
}
//_2002-01-25___________________________________________________________________
bool Binary_fstream::goto_EOF() performs_IO_ { return STRM seekg(0,std::istream::end) == 0;}
Binary_fstream::Binary_fstream
(const char *_file_name                                                          //001206
,bool        _big_endian)       // Most MS-DOS or Windows base software files are not big_endian
: strm(_file_name,(std::ios::in)|(std::ios::out) OR_IOS_BINARY)
, file_name(0)                                                                   //981019
, endian_swapping(_big_endian != CPU_is_big_endian())                            //990106
, mode(std::ios::in|std::ios::out  OR_IOS_BINARY)                                //990521
{  file_name = new char[strlen(_file_name) + 1]; // should only need to add 1
   strcpy(file_name,_file_name);
}
//_1999-01-07___________________________________________________________________
#define CORN_endian_correction_float64(Xvalue)                 \
if (endian_swapping)                                 \
{                                                    \
   nat8 *Pvalue = (nat8 *)&Xvalue;       \
   nat8 v0 = Pvalue[0];            \
   nat8 v1 = Pvalue[1];         \
   nat8 v2 = Pvalue[2];        \
   nat8 v3 = Pvalue[3];        \
   nat8 v4 = Pvalue[4];        \
   nat8 v5 = Pvalue[5];        \
   nat8 v6 = Pvalue[6];        \
   nat8 v7 = Pvalue[7];        \
   Pvalue[0]=v7;            \
   Pvalue[1]=v6;         \
   Pvalue[2]=v5;        \
   Pvalue[3]=v4;        \
   Pvalue[4]=v3;        \
   Pvalue[5]=v2;        \
   Pvalue[6]=v1;        \
   Pvalue[7]=v0;        \
}

#define CORN_endian_correction_float32(Xvalue)                 \
if (endian_swapping)                                 \
{                                                    \
   char *Pvalue = (char *)&Xvalue;       \
   nat8 v0 = Pvalue[0];            \
   nat8 v1 = Pvalue[1];         \
   nat8 v2 = Pvalue[2];        \
   nat8 v3 = Pvalue[3];        \
   Pvalue[0]=v3;        \
   Pvalue[1]=v2;        \
   Pvalue[2]=v1;        \
   Pvalue[3]=v0;        \
}

#define CORN_endian_correction_32(Xvalue)                 \
if (endian_swapping)                                 \
{                                                    \
nat8 v0 = (nat8)((Xvalue & 0x000000FF));                    \
nat8 v1 = (nat8)((Xvalue & 0x0000FF00)>>8);                 \
nat8 v2 = (nat8)((Xvalue & 0x00FF0000)>>16);                \
nat8 v3 = (nat8)((Xvalue & 0xFF000000)>>24) ;               \
Xvalue = (v0 <<24) | (v1 << 16) | (v2 << 8) | v3;    \
}

#define CORN_endian_correction_16(Xvalue)     \
if (endian_swapping)                     \
{                                        \
   nat8 v0 = (nat8)((Xvalue & 0x00FF));      \
   nat8 v1 = (nat8)((Xvalue & 0xFF00)>>8);   \
   Xvalue = (int16)((v0 <<8) | v1);                \
}
//_1999-01-07___________________________________________________________________
int32 Binary_fstream::write_int32(int32 value)
{  CORN_endian_correction_32(value);                                             //000129
   STRM write((char *)(&value),sizeof(int32));
   return value;
}
//_1999-01-07___________________________________________________________________
nat32 Binary_fstream::write_nat32(nat32 value)
{  CORN_endian_correction_32(value);                                             //000129
   STRM write((char *)(&value),sizeof(nat32));
   return value;
}
//_1999-01-07___________________________________________________________________
float64 Binary_fstream::write_float64(float64 value)
{  CORN_endian_correction_float64(value);                                        //001214
   STRM write((char *)(&value),sizeof(float64));
   return value;
}
//_1999-01-07___________________________________________________________________
float32 Binary_fstream::write_float32(float32 value)
{  CORN_endian_correction_float32(value);                                        //001214
   STRM write((char *)(&value),sizeof(float32));
   return value;
}
//_1999-01-07___________________________________________________________________
float64 Binary_fstream::read_float64()
{  float64 value;
   STRM read((char *)(&value),sizeof(float64));
   CORN_endian_correction_float64(value);                                        //001214
   return value;
}
//_1999-01-07___________________________________________________________________
float32 Binary_fstream::read_float32()
{  float32 value;
   STRM read((char *)(&value),sizeof(float32));
   CORN_endian_correction_float32(value);                                        //001214
   return value;
}
//_1999-01-07___________________________________________________________________
int32 Binary_fstream::read_int32()
{  int32 value;
   STRM read((char *)(&value),sizeof(int32));
   CORN_endian_correction_32(value);                                             //000129
   return value;
}
//_1999-01-03___________________________________________________________________
nat32 Binary_fstream::read_nat32()
{  nat32 value;
   STRM read((char *)(&value),sizeof(nat32));
   CORN_endian_correction_32(value);                                             //000129
   return value;
}
//_1999-01-03___________________________________________________________________
 int16 Binary_fstream::write_int16(int16 value)
{  CORN_endian_correction_16(value);
   STRM write((char *)(&value),sizeof(int16));
   return value;
}
//_1999-01-07___________________________________________________________________
nat16 Binary_fstream::write_nat16(nat16 value)
{  CORN_endian_correction_16(value);
   STRM write((char *)(&value),sizeof(nat16));
   return value;
}
//______________________________________________________________________________
int16  Binary_fstream::read_int16()
{  int16 value;
   STRM read((char *)(&value),sizeof(int16));
   CORN_endian_correction_16(value);                                             //000129
   return value;
}
//_1999-01-07___________________________________________________________________
nat16  Binary_fstream::read_nat16()
{  nat16 value;
   STRM read((char *)(&value),sizeof(nat16));
   CORN_endian_correction_16(value);                                             //000129
   return value;
}
//_1999-01-07___________________________________________________________________
const char *Binary_fstream::write_ASCIx(const char *str,String_format format ,nat32 field_length)
{
/*
   This writes character array (string)
   str          - is a null terminated string of any length.
   format       - specifies how the string will be formatted in the output file.
   field_length - is the number of bytes to reserve for the string
   If field length is 0 the number of bytes written
   will be the actual length will be determined based on the
   format and the number of characters
   If field length is specified (greater than 0) then
   this exact number of characters will be written
   For the ASCIC and ASCIZ format, the field_length includes the bytes
   required for the formatting information.
   For example if the string is  "abc" and ASCIZ format is used
   the field size would have to be at least 4 bytes to accomodate
   the null terminator.
   If the ASCIC32 is used then the field length must be at least 7 bytes.
   for the 32bit integer field size (4 bytes) plus the 3 text characters.
   The string plus formatting information may be truncated to fit this size).
   If the string is shorter than the field size null characters will
   be used to pad the remainder of the field.
*/
   nat32 str_length = strlen(str);
   nat32 remaining_field_length = field_length;
   // ASCIC format have preceding string length
   Data_type character_count_datatype = (Data_type)(format &CORN_len_data_type_bitmask);
   switch (character_count_datatype)
   {  case DT_nat8 :  {  nat8 act_len = (str_length>(nat32)  255)   ? (nat8)    255  : (nat8)str_length; write_nat8 (act_len); str_length=act_len; remaining_field_length-=1;} break;
      case DT_nat16:  { nat16 act_len = (str_length>(nat32)65535)   ? (nat16) 65535  : (nat16)str_length; write_nat16(act_len); str_length=act_len; remaining_field_length-=2;} break;
      case DT_nat32:  { nat32 act_len = (str_length>   4294967295UL) ?     4294967295UL: str_length; write_nat32(act_len); str_length=act_len; remaining_field_length-=4;} break;
      default : /*no need to adjust string length because we are not limiting the field size */ break;
   }
   bool null_terminate = format & CORN_null_term_bitmask;                        //100114
   for (nat32 i = 0; i<str_length; i++)
   {  if (!field_length || remaining_field_length)
      {  nat8 str_i = str[i];
         if (null_terminate /*100114 (format==ASCIZ_string)*/ && (i == remaining_field_length))
            str_i = 0; // We need to leave room for the null terminator in ASCIZ format, even it is trucates the string.
         write_nat8(str_i);
         remaining_field_length -= 1;
      }
   }
   if (field_length)
   {  while (remaining_field_length)
      {  write_nat8(0);  // zero fill
         remaining_field_length--;
      }
   } else if (null_terminate /*100114 (format==ASCIZ_string)*/) write_nat8(0); // null terminator
   return str;
}
//_2005-04-08___________________________________________________________________
const char *Binary_fstream::read_ASCIx(char *str,String_format format ,nat32 field_length)
{
/*
   This reads a character array (string)
   str          - is an allocated character array for a null terminated string of any length.
               THE CALLER MUST ENSURE THE BUFFER SIZE IS LARGE ENOUGH TO STORE THE TEXT.
   format       - specifies how the string has been formatted in the output file.
   field_length - is the number of bytes reserved for the string if the file (fixed field width)
   The field length is NOT the allocated size of the array
   (although for the ASCIZ and ASCIC formats you will be guarenteed
    that the buffer will not overflow if the string is at least the field length).
   field_length it may be 0 but then the format must be ASCIZ or one of the ASCIC formats.
   If field length is specified (greater than 0) then
   this exact number of characters will always be read
   For the ASCII format, make sure the str buffer is allocated the field_length + 1 to accomodate the null terminator appended to the read string.
   For the ASCIC and ASCIZ format, the field_length includes the bytes
   required for the formatting information.
   For example if the string is  "abc" and ASCIZ format is used
   the field size would have to be at least 4 bytes to accomodate
   the null terminator.
   If the ASCIC32 is used then the field length must be at least 7 bytes.
   for the 32bit integer field size (4 bytes) plus the 3 text characters.
   The string plus formatting information may be truncated to fit this size).
   If the string is shorter than the field size null characters will
   be used to pad the remainder of the field.
*/
   nat32 remaining_field_length = field_length ? field_length : 0xFFFFFFFF;
   nat32 str_length = 0xFFFFFFFF; // Essentially infinate
   Data_type character_count_datatype = (Data_type)(format &CORN_len_data_type_bitmask);
   switch (character_count_datatype)
   {  case DT_nat8 :  { str_length = (nat32)read_nat8(); remaining_field_length-=1;} break;
      case DT_nat16:  { str_length = (nat32)read_nat16();remaining_field_length-=2;} break;
      case DT_nat32:  { str_length = (nat32)read_nat32();remaining_field_length-=4;} break;
      default : /*no need to adjust string length because we are not limiting the field size */ break;
   }
   bool null_terminate = format & CORN_null_term_bitmask;                        //100114
   bool continue_reading = str_length && remaining_field_length;
   nat32 i = 0;
   while (continue_reading)
   {  nat8 char_in = read_nat8();
      str[i] = char_in;
      i++;
      remaining_field_length--;
      if (i == str_length)                      { continue_reading = false; str[str_length] = 0; }
      if (null_terminate /*100114 (format==ASCIZ_string)*/ && (char_in == 0))  { continue_reading = false; }
      if (remaining_field_length == 0)          { continue_reading = false; str[i] = 0; }
   }
   return str;
}
//_2005-04-08___________________________________________________________________
///////////////////////////////////////////////////////////////////
const char *Binary_fstream::write_cstr(const char *str,bool null_terminated)
{  STRM write(str,strlen(str));
   if (null_terminated)
      write_nat8(0);
   return str;
}
//_1999-01-03___________________________________________________________________
const char * Binary_fstream::read_cstr(char *cstr,nat16 max_string_length , bool null_terminated )
{  nat32 pos = 0;                                                                //050110
   bool at_eos = false;
   nat32 maxpos = max_string_length?max_string_length-1:MAXLONG;                 //030716
   while (!at_eos)
   {  nat8 ch = (nat8)STRM get();
      if (pos == maxpos)                  at_eos = true;
      if ((ch == 0) && (null_terminated)) at_eos = true;
      else  cstr[pos++] = ch;   // <- this should be faster
   }
   cstr[pos] = 0;
   return cstr;
}
//_1999-01-03___________________________________________________________________
nat32 Binary_fstream::get_file_length()
{
// Note, that I think I need to use both xxxp() and xxxg()
// depending on the I/O mode, but I haven't figured out how to select this.
//021212 update: tellg seems to be working irregardless of the open mode
// Note in Borland compilers a newly open file return 0
// in unix it returns -1 (an error condition?)
// therefore curr_pos and file_length must be long and not unsigned!
   long curr_pos =STRM tellg();
   STRM seekg(0,std::istream::end);
   long file_length = STRM tellg();
   STRM seekg(curr_pos);
   return file_length;
}
//_1999-01-15___________________________________________________________________
bool Binary_fstream::seek(nat32 pos, std::ios::seekdir dir )
{
#ifdef unix
// UNIX usually needs long instead of streamoff
   long seek_pos = pos;                                                          //021212
#else
   std::streamoff seek_pos = pos;                                                //021212
#endif
   STRM seekg(seek_pos,dir);                                                     //050522
   nat32 tell_pos = tell(); // was long                                          //080417
   return tell_pos == pos;
}
//_1999-01-07___________________________________________________________________
nat32 Binary_fstream::tell()
{  return (nat32) STRM tellg();                                                  //021212
}
//_1999-01-03___________________________________________________________________
} // namespace CORN

