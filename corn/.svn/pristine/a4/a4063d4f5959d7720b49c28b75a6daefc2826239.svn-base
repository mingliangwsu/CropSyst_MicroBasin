#ifndef binary_file_fstreamH
#define binary_file_fstreamH

#include "corn/format/binary/binary_file_abstract.h"

//140119 #include <corn/std/std_fstream.h>
#include <string.h>
// stdlib for string.h   strlen

// Note that Binary_file_FILE is a virtually identical version of this that uses STD C FILE
// As of June 2007, There is a problem in Borland Development suite 2006 (And maybe also BC++Builder 6)
// STD libraries where it is not possible to open an fstream.
// So I had to drop down to using FILE
#ifdef __linux__
#define STREAM_TYPE fstream
#else

//170117 I am not sure why I was using iostream
// I think it should be fstream in all versions

#define STREAM_TYPE iostream
#endif
namespace CORN {
//______________________________________________________________________________
class Binary_file_fstream
: public Binary_file_abstract
{
protected:                                                                       //110927
   mutable std::STREAM_TYPE *strm;
public: // structors
   Binary_file_fstream
      (const char *_file_name
      ,bool        _big_endian
      ,std::ios_base::openmode _openmode);                                       //111026
      // Most MS-DOS or Windows base software files are not big_endian
   virtual ~Binary_file_fstream();                                               //070628
public:
   virtual std::STREAM_TYPE &provide_stream()                        stream_IO_;//111010_080912
public: // write methods declared in Binary_file_interface
   // The write methods simply return the value passed.
   virtual int8      write_int8(int8 value)                          stream_IO_;
   virtual int16     write_int16(int16 value)                        stream_IO_;
   virtual int32     write_int32(int32 value)                        stream_IO_;
   virtual nat8      write_nat8(nat8 value)                          stream_IO_; //990909
   virtual nat16     write_nat16(nat16 value)                        stream_IO_;
   virtual nat32     write_nat32(nat32 value)                        stream_IO_;
   virtual float64   write_float64(float64 value)                    stream_IO_;
   virtual float32   write_float32(float32 value)                    stream_IO_; //990107
   virtual const nat8    *write_nat8_array(const nat8 *values,nat32 array_count)        stream_IO_; //990909
   virtual const int16   *write_int16_array(const int16 *values,nat32 array_count)      stream_IO_; //140129
   virtual const int32   *write_int32_array(const int32 *values,nat32 array_count)      stream_IO_; //110828
   virtual const float32 *write_float32_array(const float32 *values,nat32 array_count)  stream_IO_; //990107
   virtual void write(const char *str,std:: streamsize count)        stream_IO_; //091019
   virtual void read(char *str,std:: streamsize count)               stream_IO_; //091019
public: // read methods declared in Binary_file_interface
   virtual int8    read_int8()                                       stream_IO_;
   virtual int16   read_int16()                                      stream_IO_;
   virtual int32   read_int32()                                      stream_IO_; //990103
   virtual nat8    read_nat8()                                       stream_IO_; //990909
   virtual nat16   read_nat16()                                      stream_IO_;
   virtual nat32   read_nat32()                                      stream_IO_; //990103
   virtual float64 read_float64()                                    stream_IO_;
   virtual float32 read_float32()                                    stream_IO_; //990107
   virtual nat8   *read_nat8_array(nat8 *values,nat32 array_count)   stream_IO_; //100114
   virtual nat16  *read_nat16_array(nat16 *values,nat32 array_count) stream_IO_; //081212
   virtual nat32  *read_nat32_array(nat32 *values,nat32 array_count) stream_IO_; //110827
   virtual int16  *read_int16_array(int16 *values,nat32 array_count) stream_IO_; //140129
   virtual int32  *read_int32_array(int32 *values,nat32 array_count) stream_IO_; //110827
   virtual float32*read_float32_array(float32 *values,nat32 array_count) stream_IO_; //081212
public: // file positioning
   virtual bool seek                                                             //990107
      (nat32 pos
#ifdef __GNUC__
      , std::_Ios_Seekdir dir = std::fstream::beg                                //090305
#else
,std:: ios::seekdir dir =std:: ios::beg
#endif
)          stream_IO_;
   virtual bool goto_EOF()                                           stream_IO_; //990107
 public: // accessors
   virtual nat32  get_file_length()                                  stream_IO_; //990115
   virtual nat32  tell()                                             stream_IO_; //990103
   virtual bool   at_eof()                                           stream_IO_; //050522
   virtual bool close()                                              stream_IO_; //070622
   virtual bool reset()                                              stream_IO_; //111111
};
//_2007-06-22___________________________________________________________________
}  // namespace CORN
#endif

