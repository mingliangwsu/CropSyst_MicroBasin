#ifndef binary_file_FILEH
#define binary_file_FILEH

#pragma error check obsolete

#include "corn/format/binary/binary_file_abstract.h"
#include <stdio.h>

// Note that Binary_file_FILE is virtually identical to Binary_file_fstream
// but uses FILE instead of fstream.
// As of June 2007, There is a problem in Borland Development suite 2006 (And maybe also BC++Builder 6)
// STD libraries where it is not possible to open an fstream.
// So I had to drop down to using FILE

namespace CORN {
//______________________________________________________________________________
class Binary_file_FILE
: public Binary_file_abstract
{
private:
   FILE *file;
public: // structors
   Binary_file_FILE
      (const char *_file_name
      ,bool        _big_endian );
      // Most MS-DOS or Windows base software files are not big_endian
   virtual ~Binary_file_FILE();
public: // write methods declared in Binary_file_interface
   // The write methods simply return the value passed.
   virtual   int8   write_int8(int8 value)                          performs_IO_;
   virtual  int16   write_int16(int16 value)                        performs_IO_;
   virtual  int32   write_int32(int32 value)                        performs_IO_;
   virtual  nat8    write_nat8(nat8 value)                          performs_IO_;//990909
   virtual nat16    write_nat16(nat16 value)                        performs_IO_;
   virtual nat32    write_nat32(nat32 value)                        performs_IO_;
   virtual float64  write_float64(float64 value)                    performs_IO_;
   virtual float32  write_float32(float32 value)                    performs_IO_;//990107
   virtual const char *write_cstr /*120804 write_string */                       //990103
      (const char *str
      ,bool null_terminated = true)                                 performs_IO_;
public: // read methods declared in Binary_file_interface
   virtual  int8   read_int8()                                      performs_IO_;
   virtual int16   read_int16()                                     performs_IO_;
   virtual int32   read_int32()                                     performs_IO_;//990103
   virtual nat8    read_nat8()                                      performs_IO_;//990909
   virtual nat16   read_nat16()                                     performs_IO_;
   virtual nat32   read_nat32()                                     performs_IO_;//990103
   virtual float64 read_float64()                                   performs_IO_;
   virtual float32 read_float32()                                   performs_IO_;//990107
public: // file positioning
   virtual bool seek                                                             //990107
      (nat32 pos, std::ios::seekdir dir = std::ios::beg)        performs_IO_;
   virtual bool goto_EOF()                                          performs_IO_;//990107
public: // accessors
   virtual nat32 get_file_length()                                  performs_IO_;//990115
   virtual nat32 tell()                                             performs_IO_;//990103
   virtual bool   at_eof()                                          performs_IO_;//050522
   virtual bool good()                                                     const;//990409
   virtual bool close()                                             performs_IO_;//070622
};
//_2007-06-22___________________________________________________________________
} // namespace CORN

#endif

