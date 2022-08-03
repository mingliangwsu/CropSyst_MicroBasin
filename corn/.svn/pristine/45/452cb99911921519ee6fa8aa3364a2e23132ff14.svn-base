#ifndef binrec_fH
#define binrec_fH

// Deprecated use binrec_s.h

#include <stdio.h>
#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#include <corn/file_sys/file.h>
#include <corn/container/bilist.h>
/* Binary record format class is the primitive binary file I/O used for
   both Lotus and Biff file formats.
//990107      Now allows for record body length of either 16 or 32 bits
//            Spreadsheets use 16 bit, UED uses 32bits
*/
//______________________________________________________________________________
class binary_record_header
{protected:
   uint32 position; // MUST BE FIRST The file position (of the header) (to beginning or rec_code)
 public:
   uint16 rec_code;
   uint32 length;    // there is the option of using 16 or 32 bits for length field, in memory it is 32bits
   inline binary_record_header(FILE *in_file,bool big_body_sizes/*,bool big_endian*/ )
      : position(0)
      ,rec_code(0)
      ,length(0)
      {  read(in_file,big_body_sizes); };
   inline binary_record_header
      (uint16 i_rec_code
      ,uint32 i_length
      ,uint32 i_position)
      : rec_code(i_rec_code)
      , length(i_length)
      , position(i_position)
      {};
   bool read(FILE *in_file,bool big_body_sizes);
 public: // accessors
   inline uint16 get_code() { return rec_code; };
   inline uint32 get_length() { return length; };
   inline uint32 get_position() { return position; };
};
//_1999-01-07_____________________________________________________________________________
class binary_record_file
: public binary_record_header // of the latest record read                       //990107
{
protected:
   FILE    *inoutfile;
   CORN::File_name file_name;  // Not absolutely needed, currently used for debugging.
   bool    at_eof;
   bool    for_input;                                                            //981021
   bool    big_body_sizes;                                                       //990106
   bool    endian_swapping;                                                      //990106
public:
   binary_record_file
      (const CORN::File_name &filename
      ,bool i_for_input
      ,bool i_big_body_sizes   // True if record header size field is 32bits
      ,bool i_big_endian);       // Most MS-DOS or Windows base software files are not big_endian
   inline ~binary_record_file()                                                  {  fclose(inoutfile); };
   void write_int32(int32 value);
   void write_int16(int16 value);
   inline void write_int8(int8 value)                                            {  fputc(value,inoutfile);};
   inline void write_uint8(uint8 value)                                          {  fputc(value,inoutfile);};
   inline void write_float32(float32 value)                                      {  fwrite(&value,sizeof(float32),1,inoutfile);};
   inline void write_float32(float32 value)                                      {  fwrite(&value,sizeof(float32),1,inoutfile);}; //990107
   void write_string(const Ustring &str,bool null_terminated = true);            //990103
   inline void write_rec_header(uint16 code,uint32 len)
   {  write_int16(code);
      if (big_body_sizes) write_int32(len);                                      //990107
      else                write_int16((uint16)len);                              //990107
   };
 public:  // reading methods
   virtual uint16 read_rec_header();
   virtual void skip_to_record_following(const binary_record_header &record_info); // header with length already read //981016
   virtual void read_unknown_record_data(); // header with length already read      //981016
   inline int32 read_int32();                                                    //990103
   inline int16 read_int16();
   inline  int8  read_int8()
   {  int8 value = (int8)fgetc(inoutfile);
      return value;
   };
  inline  uint8  read_uint8()
   {  uint8 value = (uint8)fgetc(inoutfile);
      return value;
   };
   inline float32 read_float32()
   {  float32 value;
      fread(&value,sizeof(float32),1,inoutfile);
      return value;
   };
   inline float32 read_float32()                                                 //990107
   {  float32 value;
      fread(&value,sizeof(float32),1,inoutfile);
      return value;
   };
   void read_string(Ustring &str,uint16 max_string_length = 0,bool null_terminated=true); //990103
   // Returns true if the record read is BOF record
 public:  // status methods
   inline bool good()                                                            {return inoutfile != 0;};
   inline bool eof()                                                 performs_IO {return at_eof || !good() || feof(inoutfile); };
 public:  // identification methods
   virtual uint16 get_BOF_code() const = 0; // PURE
   virtual uint16 get_EOF_code() const = 0; // PURE
 public: // accessors
   inline bool seek(uint32 offset) { return fseek(inoutfile,offset,SEEK_SET) == 0;};   //990107
   uint32 get_file_length()                                                      //990115
   {  uint32 curr_pos = tell();
      fseek(inoutfile,0,SEEK_END);
      uint32 file_length = tell();
      seek(curr_pos);
      return file_length;
   };
   inline uint32 tell()                                                          { return ftell(inoutfile); }; //990103
   inline bool goto_EOF()                                                        { return fseek(inoutfile,0,SEEK_END) == 0;};  //990107
   inline CORN::File_name &get_file_name()                                       { return file_name; };     //990107
};
//_1998-10-15___________________________________________________________________
class binary_header_item
: public CORN::Container_item                                                    //000219
, public binary_record_header
{public:
   inline binary_header_item(FILE *in_file,bool big_body_sizes)
      :CORN::Container_item()                                                    //000219
      ,binary_record_header(in_file,big_body_sizes)
      {};
   inline binary_header_item
      (uint16 i_rec_code
      ,uint32 i_length
      ,uint32 i_position)
      : CORN::Container_item()                                                   //000219
      , binary_record_header(i_rec_code,i_length,i_position)
      {};
  inline virtual int compare(const Item &other)                            const //000219
   {  binary_header_item &other_binary_header = (binary_header_item &)other;
      return (rec_code < other_binary_header.get_code())
         ? -1 : (rec_code < other_binary_header.get_code()) ? 1 : 0;
   };
};
//_1999-01-07___________________________________________________________________
class indexed_binary_record_file
: public binary_record_file
, public CORN::Bidirectional_list
{public:
   indexed_binary_record_file
      (const CORN::File_name &filename
      ,bool i_for_input
      ,bool i_big_body_sizes   // True if record header size field is 32bits
      ,bool i_big_endian);       // Most MS-DOS or Windows base software files are not big_endian
   virtual CORN::Container_item *set_current(CORN_unidirectional_list_node *new_current); //000219
   virtual void initialize();
};
//_1999-01-07___________________________________________________________________
#endif
