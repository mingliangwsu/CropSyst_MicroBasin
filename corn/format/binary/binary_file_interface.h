#ifndef binary_file_interfaceH
#define binary_file_interfaceH

// This class replaces Binary_fstream
// Note that there is a virtually identical version of this that uses STD C FILE
// As of June 2007, There is a problem in Borland Development suite 2006 (And maybe also BC++Builder 6)
// STD libraries where it is not possible to open an fstream.
// So I had to drop down to using FILE

//140118 #include <corn/std/std_fstream.h>
#include <iostream>
#include <fstream>
#ifdef unix
// unix doesn't have, or is already, in binary mode?
#  define OR_IOS_BINARY
#else
// I think this may be DOS/Windows specific, so the ifdef would be if not __MSDOS__
#  define OR_IOS_BINARY   |std:: ios::binary
#endif

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef constH
#  include "corn/const.h"
#endif
#ifndef data_type_enumH
#  include "corn/data_type_enum.h"
#endif
#include <string>

#if ((__BCPLUSPLUS__ > 0x000) && (__BCPLUSPLUS__ <= 0x340))
#define seekdir seek_dir
// 051217 Apparently seek_dir was changed to seekdir in std::ios
// Borland C++ 5.0 does not have seekdir
// GNU C++ (or Linux) dont have seek_dir
#define streamsize nat32
#endif
namespace CORN {
//______________________________________________________________________________
interface_ Binary_file_interface
{

/*    String_format move to corn\data_type_enum.h
   ASCII    This format provides no encoded information about the length of the string field.
            The read/write functions must specify the number of characters to read.
            This is not Null terminated
   ASCIZ    This indicates the string is written null (zero) terminated.
   ASCIC8   The first (unsigned) byte specifies the length of the string.
            Can be used with strings up to 256 characters long.
   ASCIC16  The first 16 bit unsigned word specifies the length of the string.
   ASCIC32  The first 32 bit unsigned longword specifies the length of the string.

   For all formats, the string passed to the write_XXX methods
   is always a C/C++ null terminated character array.
   Similarly the string returned by the read_XXX methods will be a null
   terminated character array.

   For the ASCIC formats.
            If length is also specified in read/write functions then
            the string will be right zero filled when read/written.
            the length prefix is not included in the returned
            null terminated character array.
            (The ASCIC formats were used in VAX and PDP computers
             they are not used much anymore today).
*/
   // structors
   inline virtual ~Binary_file_interface() {}  // This appears to be required in order for strm to close correctly and Binary_file_abstract destructor to be called. //070628
   // write methods
   // The write methods simply return the value passed.
   virtual   int8   write_int8(int8 value)              performs_IO_ = 0;
   virtual  int16   write_int16(int16 value)            performs_IO_ = 0;
   virtual  int32   write_int32(int32 value)            performs_IO_ = 0;
   virtual  nat8   write_nat8(nat8 value)             performs_IO_ = 0;   //990909_
   virtual nat16   write_nat16(nat16 value)           performs_IO_ = 0;
   virtual nat32   write_nat32(nat32 value)           performs_IO_ = 0;
   virtual float64  write_float64(float64 value)         performs_IO_ = 0;
   virtual float32  write_float32(float32 value)         performs_IO_ = 0; //990107
   virtual const nat8    *write_nat8_array(const nat8 *values,nat32 array_count)             performs_IO_ = 0; //990909
//NYN   virtual const nat16   *write_nat16_array(const nat16 *values,nat32 array_count)             performs_IO_ = 0; //990909
   virtual const int16   *write_int16_array(const int16 *values,nat32 array_count)             performs_IO_ = 0; //140129
   virtual const float32 *write_float32_array(const float32 *values,nat32 array_count)performs_IO_ = 0;  //990107_

               // NYI may want to have write_wchar_t   but it would probably be better to use wstrings
   virtual const char *write_c_str // was write_ASCIx                            //050408
      (const char   *cstr
      ,String_format format      = ASCII_Z_string
      ,nat32        field_length=0)                     performs_IO_ = 0;
   virtual const std::string &write_string                                      //050408
      (const std::string &string
      ,String_format format      = ASCII_Z_string
      ,nat32        field_length=0)                     performs_IO_ = 0;
   virtual const std::wstring &write_wstring                                     //050408
      (const std::wstring &string
      ,String_format format      = ASCII_Z_string
      ,nat32        field_length=0)                     performs_IO_ = 0;
      // This writes character array (string)
      // str          - is a null terminated string of any length.
      // format       - specifies how the string will be formatted in the output file.
      // field_length - is the number of bytes to reserve for the string
      // If field length is 0 the number of bytes written
      // will be the actual length will be determined based on the
      // format and the number of characters
      // If field length is specified (greater than 0) then
      // this exact number of characters will be written
      // For the ASCIC and ASCIZ format, the field_length includes the bytes
      // required for the formatting information.
      // For example if the string is  "abc" and ASCIZ format is used
      // the field size would have to be at least 4 bytes to accomodate
      // the null terminator.
      // If the ASCIC32 is used then the field length must be at least 7 bytes.
      // for the 32bit integer field size (4 bytes) plus the 3 text characters.
      // The string plus formatting information may be truncated to fit this size).
      // If the string is shorter than the field size null characters will
      // be used to pad the remainder of the field.
      // This is a short version of write_ASCIx(str,ASCIZ or ASCII,0):
      // write_ASCIx(str,ASCIZ,0) if null_terminated = true
      // write_ASCIx(str,ASCII,0) if null_terminated = false
 // read methods
   virtual  int8   read_int8()                          performs_IO_ = 0;
   virtual int16   read_int16()                         performs_IO_ = 0;
   virtual int32   read_int32()                         performs_IO_ = 0;           //990103
   virtual nat8    read_nat8()                          performs_IO_ = 0;   //990909
   virtual nat16   read_nat16()                         performs_IO_ = 0;
   virtual nat32   read_nat32()                         performs_IO_ = 0;   //990103
   virtual float64 read_float64()                        performs_IO_ = 0;
   virtual float32 read_float32()                        performs_IO_ = 0; //990107
   virtual nat8   *read_nat8_array (nat8 *values,nat32 array_count) performs_IO_ = 0;  //100114_
   inline virtual  nat8   *read_uint8_array(nat8 *values,nat32 array_count)      performs_IO_
      { return read_nat8_array(values,array_count); } // deprecated //081212
   virtual nat16   *read_nat16_array(nat16 *values,nat32 array_count)      performs_IO_ = 0; //081212
   virtual nat32   *read_nat32_array(nat32 *values,nat32 array_count)      performs_IO_ = 0; //110827
   virtual int16   *read_int16_array(int16 *values,nat32 array_count)      performs_IO_ = 0; //140129
   virtual int32   *read_int32_array(int32 *values,nat32 array_count)      performs_IO_ = 0; //110827
   virtual float32 *read_float32_array(float32 *values,nat32 array_count)  performs_IO_ = 0; //990107

   // NYI may want to have read_wchar_t  but it would probably be better to use wstrings
   virtual char *read_c_str                                                      //050408
      (char *str
      ,String_format format = ASCII_Z_string
      ,nat32 field_length=0)                            performs_IO_ = 0;
   virtual std::string &read_string                                             //050408
      (std::string &str
      ,String_format format = ASCII_Z_string
      ,nat32 field_length=0)                            performs_IO_ = 0;
   virtual std::wstring &read_wstring                                            //050408
      (std::wstring &str
      ,String_format format = ASCII_Z_string
      ,nat32 field_length=0)                            performs_IO_ = 0;
      // This reads a character array (string)
      // str          - is an allocated character array for a null terminated string of any length.
      //             THE CALLER MUST ENSURE THE BUFFER SIZE IS LARGE ENOUGH TO STORE THE TEXT.
      // format       - specifies how the string has been formatted in the output file.
      // field_length - is the number of bytes reserved for the string if the file (fixed field width)
      // The field length is NOT the allocated size of the array
      // (although for the ASCIZ and ASCIC formats you will be guarenteed
      //  that the buffer will not overflow if the string is at least the field length).
      // field_length it may be 0 but then the format must be ASCIZ or one of the ASCIC formats.
      // If field length is specified (greater than 0) then
      // this exact number of characters will always be read
      // For the ASCII format, make sure the str buffer is allocated the field_length + 1 to accomodate the null terminator appended to the read string.
      // For the ASCIC and ASCIZ format, the field_length includes the bytes
      // required for the formatting information.
      // For example if the string is  "abc" and ASCIZ format is used
      // the field size would have to be at least 4 bytes to accomodate
      // the null terminator.
      // If the ASCIC32 is used then the field length must be at least 7 bytes.
      // for the 32bit integer field size (4 bytes) plus the 3 text characters.
      // The string plus formatting information may be truncated to fit this size).
      // If the string is shorter than the field size null characters will
      // be used to pad the remainder of the field.
      // read_ASCIx will append 0 to the returned str.
      //100114 read_string has been replaced with read_c_str
   virtual void write(const char *str,std::streamsize count) performs_IO_ = 0;   //091019
   virtual void read(char *str,std::streamsize count)        performs_IO_ = 0;   //091019
 // file positioning
   virtual bool seek                                                             //990107
      (nat32 pos
#ifdef __GNUC__
      , std::_Ios_Seekdir dir = std::fstream::beg
#else
      ,std::ios::seekdir dir = std::ios::beg
#endif
      )         performs_IO_ = 0;
   virtual bool goto_EOF()                               performs_IO_ = 0;       //990107
      // Positions the file pointer to the end of file.
      // returns true if successful
// accessors
   virtual nat32 get_file_length()                      performs_IO_ = 0;        //990115
   virtual nat32 tell()                                 performs_IO_ = 0;        //990103
   virtual const char *get_file_name()                         const = 0;        //001206
   virtual int get_open_mode()                                 const = 0;        //990412
   virtual bool good()                                         const = 0;        //990409
   virtual bool at_eof()                                 performs_IO_ = 0;       //050522
   virtual bool close()                                  performs_IO_ = 0;       //070622
   virtual bool reset()                                  performs_IO_ = 0;
};
//_2007-06-22_1999_________________________________________________________________

} // namespace CORN


#endif

