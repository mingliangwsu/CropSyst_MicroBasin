#ifndef binary_file_abstractH
#define binary_file_abstractH

#include "corn/format/binary/binary_file_interface.h"

#ifdef _MSC_VER
//#  include <values_MSC.h>
#  include <string.h>
#else
#ifdef __BCPLUSPLUS__
#  include <values.h>
#endif
#endif

// Note that there is a virtually identical version of this that uses STD C FILE
// As of June 2007, There is a problem in Borland Development suite 2006 (And maybe also BC++Builder 6)
// STD libraries where it is not possible to open an fstream.
// So I had to drop down to using FILE

/* To be implemented




Byte order mark: (endianess and

http://en.wikipedia.org/wiki/Byte_Order_Mark

Add an option for Byte Order Mark to identify the
endianess of the file and the default encoding scheme of text strings.
Include UTF-8 UTF-16 UTF-32 UTF-7 UTF-1 UTF_EBCDIC SCSU BOCU-1

The Byte order marker (if present in a file) will be used to
identify the default size of words

If Byte Order Mark is not present, the user of this class must
ensure the consistency of the endianness of the file.
By default the endianess should be assumed to be in little ending
(since most computers nowadays have little endian processors )
[although UCS-2 is usually specified by in network byte order (Big-endian)].

If Byte Order Mark is not present the default text encoding will be assumed
to be ASCII.

ASCII should be used for meta data text where possible.

String encoding:

   Add write/read various UTF encode strings


Added optional signature
   - This would follow any BOM
   - Would either be a
      - magic number  (UNIX convention uses a 2 byte identifiers at the beginning of the file).
         It is recommend that the magic number be less than 4 bytes.
      - File format identifiers http://en.wikipedia.org/wiki/File_format#File_format_identifiers_.28FFIDs.29
            magicdb.org
      - Document type definition http://en.wikipedia.org/wiki/Document_type_definition





*/







namespace CORN {

//______________________________________________________________________________
#define CORN_endian_correction_float64(Xvalue)     \
if (endian_swapping)                               \
{                                                  \
   nat8 *Pvalue = (nat8 *)&Xvalue;               \
   nat8 v0 = Pvalue[0];                           \
   nat8 v1 = Pvalue[1];                           \
   nat8 v2 = Pvalue[2];                           \
   nat8 v3 = Pvalue[3];                           \
   nat8 v4 = Pvalue[4];                           \
   nat8 v5 = Pvalue[5];                           \
   nat8 v6 = Pvalue[6];                           \
   nat8 v7 = Pvalue[7];                           \
   Pvalue[0]=v7;                                   \
   Pvalue[1]=v6;                                   \
   Pvalue[2]=v5;                                   \
   Pvalue[3]=v4;                                   \
   Pvalue[4]=v3;                                   \
   Pvalue[5]=v2;                                   \
   Pvalue[6]=v1;                                   \
   Pvalue[7]=v0;                                   \
}
//______________________________________________________________________________
#define CORN_endian_correction_float32(Xvalue)     \
if (endian_swapping)                               \
{                                                  \
   char *Pvalue = (char *)&Xvalue;                 \
   nat8 v0 = Pvalue[0];                           \
   nat8 v1 = Pvalue[1];                           \
   nat8 v2 = Pvalue[2];                           \
   nat8 v3 = Pvalue[3];                           \
   Pvalue[0]=v3;                                   \
   Pvalue[1]=v2;                                   \
   Pvalue[2]=v1;                                   \
   Pvalue[3]=v0;                                   \
}
//______________________________________________________________________________
#define CORN_endian_correction_32(Xvalue)          \
if (endian_swapping)                               \
{                                                  \
nat8 v0 = (nat8)((Xvalue & 0x000000FF));         \
nat8 v1 = (nat8)((Xvalue & 0x0000FF00)>>8);      \
nat8 v2 = (nat8)((Xvalue & 0x00FF0000)>>16);     \
nat8 v3 = (nat8)((Xvalue & 0xFF000000)>>24) ;    \
Xvalue = (v0 <<24) | (v1 << 16) | (v2 << 8) | v3;  \
}
//______________________________________________________________________________
#define CORN_endian_correction_16(Xvalue)          \
if (endian_swapping)                               \
{                                                  \
   nat8 v0 = (nat8)((Xvalue & 0x00FF));           \
   nat8 v1 = (nat8)((Xvalue & 0xFF00)>>8);        \
   Xvalue = (int16)((v0 <<8) | v1);                \
}
//______________________________________________________________________________
extern bool CPU_big_endian();  // Maybe this can now be a member method
//______________________________________________________________________________
class Binary_file_abstract
: public Binary_file_interface
{
   // Binary file does not define any structure except
   // - Optional Byte Order Marker (which usually
   // -
private:
    char *file_name;                                                             //020125
protected:
   contribute_ bool    endian_swapping;                                          //990106
      // This indicate if it is necessary to perform endian swapping
                           // because the processor and file format
                           // are not the same endianness
                           // THIS DOES NOT INDICATE THE ENDIANESS OF THE FILE!
   contribute_ std::ios_base::openmode/*170117 int*/ openmode;                   //990412
      // istream indicator of mode is not accessable so it is necessary remember the open mode.
public:  // structors and structors
   Binary_file_abstract
      (const char *_file_name
      ,bool        _big_endian
      ,std::ios_base::openmode _openmode);                                       //111026
      // Most MS-DOS or Windows base software files are not big_endian
   virtual ~Binary_file_abstract();
public: // write methods
   virtual const char *write_c_str // was write_ASCIx                            //050408
      (const char         *cstr
      ,String_format       format      = ASCII_Z_string
      ,nat32               field_length=0)                          performs_IO_;
   virtual const std::string &write_string                                       //050408
      (const std::string  &string
      ,String_format       format      = ASCII_Z_string
      ,nat32               field_length=0)                          performs_IO_;
   virtual const std::wstring &write_wstring                                     //050408
      (const std::wstring &string
      ,String_format       format      = ASCII_Z_string
      ,nat32               field_length=0)                          performs_IO_;
public:  // read methods
   virtual char *read_c_str // read_UTF16LE                                      //050408
      (char         *cstr
      ,String_format format = ASCII_Z_string
      ,nat32         field_length=0)                                performs_IO_;
   virtual std::string &read_string                                              //050408
      (std::string  &str
      ,String_format format = ASCII_Z_string
      ,nat32         field_length=0)                                performs_IO_;
   virtual std::wstring &read_wstring                                            //050408
      (std::wstring &str
      ,String_format format = ASCII_Z_string
      ,nat32         field_length=0)                                performs_IO_;
public: // accessors
   inline virtual const char *get_file_name() const { return file_name; };       //001206
   inline virtual       int   get_open_mode() const { return openmode; };            //990412
   inline virtual       bool  good()          const { return true;  };           //990409
}; // Binary_file_abstract CORN
//_2007-06-22_1999________________________________________Binary_file_abstract_/
};    // namespace CORN
#endif
