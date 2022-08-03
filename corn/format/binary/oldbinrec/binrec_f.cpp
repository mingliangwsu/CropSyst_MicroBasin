#include <corn/format/binrec_f.h>

#if defined  (_BIG_ENDIAN) || defined (
#define CPU_big_endian true
#else
#define CPU_big_endian false
#endif

#include <corn/corn.h>
#ifdef USES_STREAMS
#   define STRMS
#   define STDIO _COMMENT_
#else
#   define STRMS _COMMENT_
#   define STDIO
#endif

//______________________________________________________________________________
int32 big_endian_32bit_read(
STRMS      istream &strm
STDIO      FILE *file
)
{  int32 raw;
STDIO         fread(&raw,4,1,file);
STRMS         strm >> raw;
   int32 ready =
#ifdef ENDIAN_SWAP
                ((0x000000FF & raw) << 24)
              & ((0x0000FF00 & raw) << 16)
              & ((0x00FF0000 & raw) >>  8)
              & ((0xFF000000 & raw) >> 24);
#else
   raw;
#endif
   return ready;
};
//______________________________________________________________________________
int32 big_endian_32bit_write(int32 value ,
STRMS      ostream &strm
STDIO      FILE *file
)
{  int32 big_ended =
#ifdef ENDIAN_SWAP
                ((0x000000FF & value) << 24)
              & ((0x0000FF00 & value) << 16)
              & ((0x00FF0000 & value) >>  8)
              & ((0xFF000000 & value) >> 24);
#else
      value;
#endif
STDIO         fwrite(&big_ended,4,1,file);
STRMS         strm << big_ended;
   return value;
};
//______________________________________________________________________________
int16 big_endian_16bit_read
STRMS      (istream &strm)
STDIO      (FILE *file)
{
  int16 raw;
STDIO         fread(&raw,2,1,file);
STRMS         strm >> raw;
  int16 ready =
#ifdef ENDIAN_SWAP
                ((0x00FF & raw) << 8)
              & ((0xFF00 & raw) >> 8);
#else
     raw;
#endif
  return ready;
};
//______________________________________________________________________________
int16 big_endian_16bit_write(int16 value,
STRMS      ostream &strm
STDIO      FILE *file
)
{  int16 big_ended =
#ifdef ENDIAN_SWAP
                ((0x00FF & value) << 8)
              & ((0xFF00 & value) >> 8);
#else
     value;
#endif
STDIO  fwrite(&big_ended,2,1,file);
STRMS  strm << big_ended;
  return value;
};
//______________________________________________________________________________
float big_endian_16bit_float_read(
STRMS      istream &strm
STDIO FILE *file)
{  float raw;
STDIO         int32 bytes_read = fread(&raw,sizeof(float),1,file);
STRMS      strm >> raw;
#ifdef ENDIAN_SWAP
   int16 ready =
                ((0x00FF & raw) << 8)
              & ((0xFF00 & raw) >> 8);
#else
   float ready = raw;
#endif
   return ready;  // Warning need to check that this works
};
//______________________________________________________________________________
float big_endian_16bit_float_write(float value,
STRMS      ostream &strm
STDIO FILE *file
)
{
#ifdef ENDIAN_SWAP
  int big_ended =
              ((0x00FF & value) << 8)
              & ((0xFF00 & value) >> 8);
#else
   float big_ended = value;
#endif
STDIO          int32 bytes_written = fwrite(&big_ended,sizeof(float),1,file);
STRMS       strm << big_ended;
   return value;
};
//______________________________________________________________________________
binary_record_file::binary_record_file
(const CORN_filename &filename
,bool i_for_input
,bool i_big_body_sizes   // True if record header size field is 32bits
,bool i_big_endian       // Most MS-DOS or Windows base software files are not big_endian
)
: binary_record_header((uint16)0,(uint32)0,(uint32)0)
, inoutfile(0)
//, rec_code(0)
, at_eof(false)
, file_name(filename)
, for_input(i_for_input)
, big_body_sizes(i_big_body_sizes)
, endian_swapping(i_big_endian != CPU_big_endian)
{  if (for_input)
   {  if (filename.exists())
      {  inoutfile = fopen(filename.get(),"r+b");
         at_eof = inoutfile == 0;
      }
   } else
      inoutfile = fopen(filename.get(),"wb");
};
//______________________________________________________________________________
uint16 binary_record_file::read_rec_header()
{  bool read_successfully = binary_record_header::read(inoutfile,big_body_sizes);
   if (!read_successfully)
      at_eof = true;
   return read_successfully
   ? rec_code
   : get_EOF_code();
};
//_9199-01-07___________________________________________________________________
int32 primitive_read_int32(FILE *in_file)
{  int32 value;
   fread (&value,sizeof(int32),1,in_file);
   return value;
};
//_1999-01-03___________________________________________________________________
int16 primitive_read_int16(FILE *in_file)
{  int16 value;
   fread (&value,sizeof(int16),1,in_file);
   return value;
};
//______________________________________________________________________________
bool binary_record_header::read(FILE *in_file,bool big_body_sizes)
{  length = 0;
   position = ftell(in_file);
   bool successful = true;
   if (!in_file || feof(in_file))
      successful = false;
   else
   {  rec_code = primitive_read_int16(in_file);
      if (feof(in_file))
         successful = false;
      else
      {  length = (big_body_sizes)
         ? primitive_read_int32(in_file)
         : primitive_read_int16(in_file);
         if (feof(in_file))
            successful = false;
      };
   };
   return successful;
};
//_1999-01-07___________________________________________________________________
void binary_record_file::read_unknown_record_data() // header with length already read
{  // WARNING actually we will want
   // to load it into a buffer (allocated by this method and released to caller)
   for (int16 i = 0; (i < length) && (!at_eof); i++)
   {  fgetc(inoutfile);
      if (feof(inoutfile))
      {  at_eof = 1;
         rec_code = get_EOF_code();
      };
   };
};
//_1998-10-16___________________________________________________________________
void binary_record_file::skip_to_record_following(const binary_record_header &record_info) // header with length already read
{  fseek(inoutfile,record_info.get_position()+
      + sizeof(record_info.rec_code)
      + (big_body_sizes ? sizeof(uint32) :sizeof(uint16))
      + record_info.length
      , SEEK_SET);
};
//_1999-01-19___________________________________________________________________
void binary_record_file::write_int32(int32 value)
{  fwrite(&value,sizeof(int32),1,inoutfile);
};
//______________________________________________________________________________
int32 binary_record_file::read_int32()
{  return primitive_read_int32(inoutfile);
};
//_1999-01-03___________________________________________________________________
void binary_record_file::write_int16(int16 value)
{  fwrite(&value,sizeof(int16),1,inoutfile);
};
//______________________________________________________________________________
int16  binary_record_file::read_int16()
{  return primitive_read_int16(inoutfile);
};
//______________________________________________________________________________
void binary_record_file::write_string(const Ustring &str,bool null_terminated)
{  fwrite(str.c_str(),sizeof(uint8),str.length(),inoutfile);
   if (null_terminated)
      write_int8(0);
};
//_1999-01-03______________________________________________________________________________
void binary_record_file::read_string(Ustring &str,uint16 max_string_length , bool null_terminated )
{  int pos = 0;
   bool at_eos = false;
   str.assign("");
   while (!at_eos)
   {  uint8 ch = fgetc(inoutfile);
      pos++;
      if ((max_string_length) && (pos == max_string_length))   at_eos = true;
      if ((ch == 0) && (null_terminated))                      at_eos = true;
      else                                                     str.append(ch);

   };
};
//_1999-01-03___________________________________________________________________
indexed_binary_record_file::indexed_binary_record_file
(const CORN_filename &filename
,bool i_for_input
,bool i_big_body_sizes   // True if record header size field is 32bits
,bool i_big_endian)       // Most MS-DOS or Windows base software files are not big_endian
: binary_record_file(filename,i_for_input,i_big_body_sizes,i_big_endian)
, CORN_bidirectional_list()
{};
//______________________________________________________________________________
void indexed_binary_record_file::initialize()
{  if (for_input)
   {  delete_all(); // This may actually be a reinitialization, so make sure head list is clear.
      uint32 file_length = get_file_length();
      seek(0); // <- go back to be at BOF
      bool at_eof = false;
      while (!at_eof)
      {  binary_header_item *header = new binary_header_item(inoutfile,big_body_sizes/*,big_endian*/);
         append(header);
         skip_to_record_following(*header);
         at_eof = eof() || (header->get_code() == get_EOF_code())
            || (tell() >= file_length); // <- Incase something goes wrong with the file.  //990115
      };
      seek(0);
   };
};
//_1999-01-11___________________________________________________________________
CORN_container_item *indexed_binary_record_file::set_current(CORN_unidirectional_list_node *new_current)
{  binary_header_item *curr_header = (binary_header_item *)CORN_bidirectional_list::set_current(new_current);
   if (curr_header)
      seek(curr_header->get_position());
   return curr_header;
};
//_1999-01-08___________________________________________________________________





