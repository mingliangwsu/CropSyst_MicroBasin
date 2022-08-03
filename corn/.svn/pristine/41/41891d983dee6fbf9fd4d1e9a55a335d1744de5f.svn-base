#ifdef unix
#  include <sys/stat.h>
#else
#  include <io.h>
#endif
#include <sys/stat.h>
#include "corn/format/binary/oldbinrec/oldbinrec_s.h"
#include <iomanip>
using namespace CORN;
//______________________________________________________________________________
Old_binary_record_file::~Old_binary_record_file()
{  close();                                                                      //070622
   //161016 #ifndef unix
   #ifdef __BCPLUSPLUS
   // I don't remember why I called _rtl_chmod not sure if I needed to do this in Windows (would need gcc equivelent function)
   _rtl_chmod(get_file_name(), 0);
   #endif
   chmod((char *)get_file_name(), S_IREAD | S_IWRITE);
}
//______________________________________________________________________________
Old_binary_record_file::Old_binary_record_file
(const char *_filename                                                           //001206
,bool _big_body_sizes   // True if record header size field is 32bits
,bool _big_endian
,std::ios_base::openmode _openmode
)      // Most MS-DOS or Windows base software files are not big_endian
: Old_binary_record_header((nat16)0,(nat32)0,(nat32)0)                           //990107
, Binary_file_fstream(_filename,_big_endian,_openmode)                           //111108_070622
, is_at_eof(false)
, big_body_sizes(_big_body_sizes)                                                //990106
{}
//______________________________________________________________________________
void Old_binary_record_file::write_rec_header
(nat16 code,nat32 len)
{  write_nat16(code);
   if (big_body_sizes)  write_nat32(len);                                        //990107
   else                 write_nat16((nat16)len);                                 //990107
}
//______________________________________________________________________________
nat16 Old_binary_record_file::read_rec_header()
{  bool read_successfully = Old_binary_record_header::read_header(*this,big_body_sizes);
   if (!read_successfully)
      is_at_eof = true;
   return read_successfully
   ? rec_code
   : get_EOF_code();
}
//______________________________________________________________________________
bool Old_binary_record_header::read_header
(Binary_file_interface &in_file                                                  //070622
,bool big_body_sizes)
{  length = 0;
   position = in_file.tell();                                                    //070622
   bool successful = true;
   if (in_file.at_eof()|| position == 0xFFFFFFFF)                                //070622
      successful = false;
   else
   {  rec_code = in_file.read_nat16();                                           //000129
      if (in_file.at_eof())                                                      //070622
         successful = false;
      else
      {  length = (big_body_sizes)                                               //990107
         ? in_file.read_nat32()                                                  //000129
         : in_file.read_nat16();                                                 //000129
         if (in_file.at_eof())                                                   //070622
            successful = false;
      }
   }
   return successful;
}
//_1999-01-07___________________________________________________________________
void Old_binary_record_file::read_unknown_record_data()
{  // header with length already read.
   // WARNING actually we will want
   // to load it into a buffer (allocated by this method and released to caller)
   for (nat32 i = 0; (i < length) && (!is_at_eof); i++)
   {  read_nat8();                                                               //070622
      if (at_eof())                                                              //070622
      {  is_at_eof = 1;
         rec_code = get_EOF_code();
      }
   }
}
//_1998010-16___________________________________________________________________
void Old_binary_record_file::skip_to_record_following(const Old_binary_record_header &record_info) // header with length already read
{  seek                                                                          //070622
      (  record_info.get_position()
      + sizeof(record_info.rec_code)
      + (big_body_sizes ? sizeof(nat32) :sizeof(nat16))
      + record_info.length);
}
//_1999-01-19___________________________________________________________________
bool Old_binary_record_file::eof()                                  performs_IO_
{  return at_eof() || is_at_eof;                                                 //070622
}
//_2003-02-07___________________________________________________________________
Old_indexed_binary_record_file::Old_indexed_binary_record_file
(const char *_filename                                                          //001206
,bool _big_body_sizes   // True if record header size field is 32bits
,bool _big_endian
,std::ios_base::openmode _openmode                                               //111108
)      // Most MS-DOS or Windows base software files are not big_endian
: Old_binary_record_file(_filename,_big_body_sizes,_big_endian,_openmode)
, rec_index()                                                                    //001114
{}
//______________________________________________________________________________
void Old_indexed_binary_record_file::initialize()
{  nat32 file_length = get_file_length();
   if (!file_length)                                                             //990426
      openmode = std::ios::out                                                   //111108_990426
      #ifndef unix
      | std::ios::binary
      #endif
      ; // The file doesn't exits, so, this can't be for input
   if ((openmode & std::ios::in) && file_length)                                 //990409
   {  rec_index.delete_all(); // This may actually be a reinitialization, so make sure head list is clear. 001114
      seek(0); // <- go back to be at BOF
      bool local_at_eof = false;                                                 //040510
      while (!local_at_eof)                                                      //040510
      {  Old_binary_header_item *header = new Old_binary_header_item(*this,big_body_sizes);
         rec_index.append(header);                                               //001114
         skip_to_record_following(*header);
         local_at_eof =                                                          //040510
            at_eof()                                                             //070622
            || (header->get_code() == get_EOF_code())
            || (tell() >= file_length); // <- Incase something goes wrong with the file.  //990115
      }
      seek(0);
   }
}
//_1999-01-11___________________________________________________________________

