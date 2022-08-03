#include <corn/format/binary/binary_file_FILE.h>
#if defined(__MSDOS__) || defined(_Windows) || defined(_WIN32)
// Note this include may be Windows specific, may need to include another file for unix
#  include <io.h>
#endif
#ifdef unix
#  include <unistd.h>
#endif
namespace CORN {
//______________________________________________________________________________
Binary_file_FILE::Binary_file_FILE
(const char *_file_name                                                          //001206
,bool        _big_endian )      // Most MS-DOS or Windows base software files are not big_endian
: Binary_file_abstract(_file_name,_big_endian,std::ios_base::in|std::ios_base::out)//111026
, file(0)
{ bool file_exists =
#if defined(__MSDOS__) || defined(_Windows) || defined(_WIN32)
      access(_file_name, 0) == 0;
   // Note that access may not be available in all OS's (works for Windows and POSIX)
#endif
#ifdef unix
      access(_file_name, F_OK) == 0;
#endif
   file = fopen(_file_name,(file_exists ? "r+b" :"wb"));
}
//________________________________________________________________constructor__/
Binary_file_FILE:: ~Binary_file_FILE()
{  if (file)
   {  fclose(file);
      delete file;
      file = 0;
   }
}
//_________________________________________________________________destructor__/
bool Binary_file_FILE::goto_EOF()                                   performs_IO_
{ return fseek(file,0,SEEK_END) == 0; }
//_1999-01-07________________________________________________________goto_EOF__/
int32 Binary_file_FILE::write_int32(int32 value)                    performs_IO_
{  CORN_endian_correction_32(value);                                             //000129
   fwrite((char *)(&value),sizeof(int32),1,file);
   return value;
}
//________________________________________________________________write_int32__/
nat32 Binary_file_FILE::write_nat32(nat32 value)                    performs_IO_
{  CORN_endian_correction_32(value);                                             //000129
   fwrite((char *)(&value),sizeof(nat32),1,file);
   return value;
}
//________________________________________________________________write_nat32__/
float64 Binary_file_FILE::write_float64(float64 value)              performs_IO_
{  CORN_endian_correction_float64(value);                                        //001214
   fwrite((char *)(&value),sizeof(float64),1,file);
   return value;
}
//______________________________________________________________write_float64__/
float32 Binary_file_FILE::write_float32(float32 value)              performs_IO_
{  CORN_endian_correction_float32(value);                                        //001214
   fwrite((char *)(&value),sizeof(float32),1,file);
   return value;
}
//_1999-01-07___________________________________________________write_float32__/
int16 Binary_file_FILE::write_int16(int16 value)                    performs_IO_
{  CORN_endian_correction_16(value);
   fwrite((char *)(&value),sizeof(int16),1,file);
   return value;
}
//________________________________________________________________write_int16__/
nat8 Binary_file_FILE::write_nat8(nat8 value)                       performs_IO_
{  int result =
   fputc((int)value,file);
   if (result != value)
       result = value;  // this line for debugging only
   return (nat8)result;                                                          //080718
}
//_1999-09-09______________________________________________________write_nat8__/
nat16 Binary_file_FILE::write_nat16(nat16 value)                    performs_IO_
{  CORN_endian_correction_16(value);
   fwrite((char *)(&value),sizeof(nat16),1,file);
   return value;
}
//________________________________________________________________write_nat16__/
int8  Binary_file_FILE::write_int8(int8 value)                      performs_IO_
{  fputc((int)value,file); return value; }
//______________________________________________________________________________
const char *Binary_file_FILE::write_cstr /*120804 write_string */
(const char *str,bool null_terminated)                              performs_IO_
{  fputs(str, file);
   if (null_terminated) write_nat8(0);
   return str;
}
//_1998-01-03______________________________________________________write_cstr__/
int8  Binary_file_FILE::read_int8()                                 performs_IO_
{  int8 value = (int8)fgetc(file);   return value;  }
//__________________________________________________________________read_int8__/
int16  Binary_file_FILE::read_int16()                               performs_IO_
{  int16 value;
   fread((char *)(&value),sizeof(int16),1,file);
   CORN_endian_correction_16(value);                                             //000129
   return value;
}
//_________________________________________________________________read_int16__/
int32 Binary_file_FILE::read_int32()                                performs_IO_
{  int32 value;
   fread((char *)(&value),sizeof(int32),1,file);
   CORN_endian_correction_32(value);                                             //000129
   return value;
}
//_1999-01-03___________________________________________________________________
nat8 Binary_file_FILE::read_nat8()                                  performs_IO_
{  uint8 value = (uint8)fgetc(file); return value;  }
//_1999-09-09_______________________________________________________read_nat8__/
nat16  Binary_file_FILE::read_nat16()                               performs_IO_
{  nat16 value;
   fread((char *)(&value),sizeof(nat16),1,file);
   CORN_endian_correction_16(value);                                             //000129
   return value;
}
//_________________________________________________________________read_nat16__/
nat32 Binary_file_FILE::read_nat32()                                performs_IO_
{  nat32 value;
   fread((char *)(&value),sizeof(nat32),1,file);
   CORN_endian_correction_32(value);                                             //000129
   return value;
}
//_1999-01-03______________________________________________________read_nat32__/
float64 Binary_file_FILE::read_float64()                            performs_IO_
{  float64 value;
   fread((char *)(&value),sizeof(float64),1,file);
   CORN_endian_correction_float64(value);                                        //001214
   return value;
}
//______________________________________________________________________________
float32 Binary_file_FILE::read_float32()                            performs_IO_
{  float32 value;
   fread((char *)(&value),sizeof(float32),1,file);
   CORN_endian_correction_float32(value);                                        //001214
   return value;
}
//_1999-01-07____________________________________________________read_float32__/
bool Binary_file_FILE::seek(nat32 pos, std::ios::seekdir dir)     performs_IO_
{  int seek_mode =  SEEK_SET;
   switch (dir)                                                                  //070622
   {  case std::ios::beg: seek_mode =SEEK_SET; break;
      case std::ios::cur: seek_mode =SEEK_CUR; break;
      case std::ios::end: seek_mode =SEEK_END; break;
   }
   int fseek_result = fseek(file,pos,seek_mode);                                 //050522
   if (fseek_result != 0) return false;                                          //080718
   long tell_pos =  ftell(file) ;                                                //080718
   return tell_pos == (long)pos;
}
//_1999-01-07____________________________________________________________seek__/
nat32 Binary_file_FILE::get_file_length()                           performs_IO_
{  long curr_pos =ftell(file);
   fseek(file,0,SEEK_END);   // temporarily jump to the end of the file to find out how long it is.
   long file_length = ftell(file);
   fseek(file,curr_pos,SEEK_SET);   // Co back where were were
   return file_length;
}
//_1999-01-15_________________________________________________get_file_length__/
nat32 Binary_file_FILE::tell()                                      performs_IO_
{  return (nat32) ftell(file);
}
//_1999-01-03____________________________________________________________tell__/
bool Binary_file_FILE::at_eof()                                     performs_IO_
{ return (file == 0) || feof(file); }
//_2005-05-22__________________________________________________________at_eof__/
bool Binary_file_FILE::good()                                              const
{  return file != 0; }
//_1999-04-09____________________________________________________________good__/
bool Binary_file_FILE::close()                                      performs_IO_
{  return fclose(file) == 0;
}
//_2007-06-22____________________________________________________________________
} // namespace CORN

