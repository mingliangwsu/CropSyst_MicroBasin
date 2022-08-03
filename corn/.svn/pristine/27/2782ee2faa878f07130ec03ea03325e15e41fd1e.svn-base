#include <corn/format/binary/binary_file_abstract.h>
#include <string.h>
// string.h for strlen

namespace CORN {

#ifdef __unix
typedef nat32 Unicode_storage_type;
#else
typedef nat16 Unicode_storage_type;
#endif

//______________________________________________________________________________
bool CPU_is_big_endian()
{  uint16 i = 1;
   return ((*(char *)&i) == 0);
}
//_2001-06-08___________________________________________________________________
Binary_file_abstract::Binary_file_abstract
(const char *i_file_name                                                         //001206
,bool i_big_endian
,std::ios_base::openmode _openmode)                                              //111026
: file_name(0)                                                                   //981019
, endian_swapping(i_big_endian != CPU_is_big_endian())                           //990106
, openmode(_openmode|std::ios::binary)                                           //160927_111026
//111026, mode(STD_NS ios::in|STD_NS ios::out)                                           //990521
 // was i_mode
{
   file_name = new char[strlen(i_file_name) + 1]; // should only need to add 1
   strcpy(file_name,i_file_name);
}
//______________________________________________________________________________
Binary_file_abstract::~Binary_file_abstract()
{  if (file_name) delete [] file_name; file_name = 0;
}
//_2002-01-25___________________________________________________________________
/*
   This writes character array (string)
   str          - is a null terminated string of any length.
   format       - specifies how the string will be formatted in the output file.
   field_length - is the number of bytes to reserve for the string (This is not the length of the string, this is used when writing dBase fields)
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
#define write_Xstring_implementation(write_Xstring_method_name,string_class,string_char_type,c_array_array_accessor)                     \
const string_class &Binary_file_abstract::write_Xstring_method_name                                   \
(const string_class &str,String_format format ,nat32 field_length) performs_IO_                       \
{                                                                                                     \
   nat32 str_length = str.length();                                                                   \
   nat32 remaining_field_length = field_length;                                                       \
   Data_type character_count_datatype = (Data_type)(format & CORN_len_data_type_bitmask);             \
   switch (character_count_datatype)  /* for string formats where the run length preceeds the string*/\
   {  case DT_nat8 :  {  nat8 act_len = (str_length>(nat32)  255) ? (nat8)    255 : (nat8)str_length; \
         write_nat8 (act_len);                                                                        \
         str_length=act_len; remaining_field_length-=1;} break;                                       \
      case DT_nat16:  { uint16 act_len = (str_length>(nat32)65535)? (uint16) 65535 : (uint16)str_length; \
         write_nat16(act_len); str_length=act_len; remaining_field_length-=2;} break;                 \
      case DT_nat32:  { nat32 act_len = (str_length>   4294967295UL) ?     4294967295UL: str_length;  \
         write_nat32(act_len); str_length=act_len; remaining_field_length-=4;} break;                 \
      default : /*no need to adjust string length because we are not limiting the field size */ break;\
   }                                                                                                  \
   bool null_terminate = format & CORN_null_term_bitmask;                                             \
   nat8 char_code_data_size_in_the_file = (format & CORN_char_size_bitmask) >> 8;                     \
   if (char_code_data_size_in_the_file == 0) char_code_data_size_in_the_file = DT_nat8;               \
   for (nat32 i = 0; i < str_length; i++)                                                             \
   {                                                                                                  \
      if (!field_length || remaining_field_length)                                                    \
      {                                                                                               \
         string_char_type str_i = str.c_array_array_accessor()[i];                                    \
       /*  if (null_terminate && (i == remaining_field_length)) */                                    \
       /*     str_i = 0;                                        */                                    \
         /* We need to leave room for the null terminator in ASCIZ format,*/                          \
         /* even it is trucates the string. */                                                        \
         switch (char_code_data_size_in_the_file)                                                     \
         {  /* The data in the file may be either UTF8, UTF16 UTF32 */                                \
            case DT_nat16  : write_nat16((uint16)str_i);         break;                               \
            case DT_nat32  : write_nat32((nat32)str_i);         break;                                \
            case DT_nat8   : default :                                                                \
               /* NYI I don't yet have a method for writing UTF-8 encoded charaters */                \
               /* bool write_Unicode = format & CORN_char_code_bitmask; */                            \
               /* if ((write_Unicode) == 1) write_UTF8( (nat32)str_i) */                              \
               /* else it is an ASCII character */                                                    \
                  write_nat8((nat8)str_i);                                                            \
            break;                                                                                    \
         }                                                                                            \
         remaining_field_length -= char_code_data_size_in_the_file;                                   \
      }                                                                                               \
   }                                                                                                  \
   if (field_length)                                                                                  \
   {  while (remaining_field_length)  /* zero fill the string to fill the field */                    \
      {                                                                                               \
         switch (char_code_data_size_in_the_file)                                                     \
         {  /* The data in the file may be either UTF8, UTF16 UTF32 */                                \
            case DT_nat16  : write_nat16((uint16)0);         break;                                   \
            case DT_nat32  : write_nat32((nat32)0);         break;                                    \
            case DT_nat8   : default : write_nat8((nat8)0);  break;                                   \
         }                                                                                            \
         remaining_field_length -= char_code_data_size_in_the_file;                                   \
      }                                                                                               \
   } else if (null_terminate) /* null terminator */                                                   \
         switch (char_code_data_size_in_the_file)                                                     \
         {  /* The data in the file may be either UTF8, UTF16 UTF32 */                                \
            case DT_nat16  : write_nat16((uint16)0);         break;                                   \
            case DT_nat32  : write_nat32((nat32)0);         break;                                    \
            case DT_nat8   : default : write_nat8((nat8)0);  break;                                   \
         }                                                                                            \
   return str;                                                                                        \
}
//______________________________________________________________________________
const std::string &Binary_file_abstract::write_string
(const std::string &str,String_format format ,nat32 field_length) performs_IO_
{
   nat32 str_length = str.length();
   nat32 remaining_field_length = field_length;
   Data_type character_count_datatype = (Data_type)(format & CORN_len_data_type_bitmask);
   switch (character_count_datatype)  /* for string formats where the run length preceeds the string*/
   {  case DT_nat8 :  {  nat8 act_len = (str_length>(nat32)  255) ? (nat8)    255 : (nat8)str_length;
         write_nat8 (act_len);
         str_length=act_len; remaining_field_length-=1;} break;
      case DT_nat16:  { uint16 act_len = (str_length>(nat32)65535)? (uint16) 65535 : (uint16)str_length;
         write_nat16(act_len); str_length=act_len; remaining_field_length-=2;} break;
      case DT_nat32:  { nat32 act_len = (str_length>   4294967295UL) ?     4294967295UL: str_length;
         write_nat32(act_len); str_length=act_len; remaining_field_length-=4;} break;
      default : /*no need to adjust string length because we are not limiting the field size */ break;
   }
   bool null_terminate = format & CORN_null_term_bitmask;
   nat32 format_masked = (format & CORN_char_size_bitmask);
   nat8 char_code_data_size_in_the_file = format_masked >> 8;
   if (char_code_data_size_in_the_file == 0) char_code_data_size_in_the_file = DT_nat8;
   for (nat32 i = 0; i < str_length; i++)
   {
      if (!field_length || remaining_field_length)
      {
         char str_i = str.c_str()[i];
//         if (null_terminate && (i == remaining_field_length))
//            str_i = 0;
         /* We need to leave room for the null terminator in ASCIZ format,*/
         /* even it is trucates the string. */
         switch (char_code_data_size_in_the_file)
         {  /* The data in the file may be either UTF8, UTF16 UTF32 */
            case DT_nat16  : write_nat16((uint16)str_i);         break;
            case DT_nat32  : write_nat32((nat32)str_i);         break;
            case DT_nat8   : default :
               /* NYI I don't yet have a method for writing UTF-8 encoded charaters */
               /* bool write_Unicode = format & CORN_char_code_bitmask; */
               /* if ((write_Unicode) == 1) write_UTF8( (nat32)str_i) */
               /* else it is an ASCII character */
                  write_nat8((nat8)str_i);
            break;
         }
         remaining_field_length -= char_code_data_size_in_the_file;
      }
   }
   if (field_length)
   {  while (remaining_field_length)  /* zero fill the string to fill the field */
      {
         switch (char_code_data_size_in_the_file)
         {  /* The data in the file may be either UTF8, UTF16 UTF32 */
            case DT_nat16  : write_nat16((uint16)0);         break;
            case DT_nat32  : write_nat32((nat32)0);         break;
            case DT_nat8   : default : write_nat8((nat8)0);  break;
         }
         remaining_field_length -= char_code_data_size_in_the_file;
      }
   } else if (null_terminate) /* null terminator */
         switch (char_code_data_size_in_the_file)
         {  /* The data in the file may be either UTF8, UTF16 UTF32 */
            case DT_nat16  : write_nat16((uint16)0);         break;
            case DT_nat32  : write_nat32((nat32)0);         break;
            case DT_nat8   : default : write_nat8((nat8)0);  break;
         }
   return str;
}
//_2010-01-14___________________________________________________________________
//write_Xstring_implementation(write_string,std::string,char,c_str)
write_Xstring_implementation(write_wstring,std::wstring,Unicode_storage_type,data)
const char *Binary_file_abstract::write_c_str
(const char *c_str,String_format format ,nat32 field_length) performs_IO_
{
   std::string str(c_str);
   write_string(str,format,field_length);
   return c_str;
}
//_2010-01-14___________________________________________________________________
/*
   This reads a string. The implementation is the same for string and wstring with minor type adjustments
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
#define     read_Xstring_implementation(read_Xstring_method_name,string_class,string_char_type)       \
string_class &Binary_file_abstract::read_Xstring_method_name                                          \
(string_class &str                                                                                    \
,String_format format                                                                                 \
,nat32        field_length)                     performs_IO_                                          \
{                                                                                                     \
   nat32 remaining_field_length = field_length ? field_length : 0xFFFFFFFF;                           \
   nat32 str_length = 0xFFFFFFFF; /* Essentially infinate */                                          \
   Data_type character_count_datatype = (Data_type)(format &CORN_len_data_type_bitmask);              \
   switch (character_count_datatype)  /* for string formats where the run length preceeds the string*/\
   {  case DT_nat8 :  { str_length = (nat32)read_nat8(); remaining_field_length-=1;} break;           \
      case DT_nat16:  { str_length = (nat32)read_nat16();remaining_field_length-=2;} break;           \
      case DT_nat32:  { str_length = (nat32)read_nat32();remaining_field_length-=4;} break;           \
      default : /*no need to adjust string length because we are not limiting the field size */ break;\
   }                                                                                                  \
   bool null_terminate = format & CORN_null_term_bitmask;                                             \
   bool continue_reading = str_length && remaining_field_length;                                      \
   nat32 i = 0;                                                                                       \
   nat8 char_code_data_size_in_the_file = (format & CORN_char_size_bitmask) >> 8;                     \
   if (char_code_data_size_in_the_file == 0)  /* Could be 0 if simple ASCII*/                         \
      char_code_data_size_in_the_file = 1;                                                            \
   while (continue_reading)                                                                           \
   {                                                                                                  \
      string_char_type  char_in = 0;                                                                  \
      switch (char_code_data_size_in_the_file)                                                        \
      {  /* The data in the file may be either UTF8, UTF16 UTF32 */                                   \
         case DT_nat16  : char_in = read_nat16();   break;                                            \
         case DT_nat32  : char_in = read_nat32();   break;                                            \
         case DT_nat8   : default : char_in = read_nat8();  break;                                    \
      }                                                                                               \
      /* Currently I am only implementing UTF16 and UTF32,                              */            \
      /* UTF8 has a more complicated parsing and I don't think any Windows apps use it. */            \
      /* NYI endian swapping: look at the CORN_endian_bitmask bit of the format.  */                  \
      /* Currently assuming the endienness of the record is the same as the file itself which is */   \
      /* probably always going to be the case.*/                                                      \
      if (char_in)                                                                                    \
         str.append(1,char_in);                                                                       \
      i++;                                                                                            \
      remaining_field_length -= char_code_data_size_in_the_file;                                      \
      if (i == str_length)                    { continue_reading = false; }                           \
      if ((null_terminate) && (char_in == 0)) { continue_reading = false; }                           \
      if (remaining_field_length == 0)        { continue_reading = false; }                           \
   }                                                                                                  \
   return str;                                                                                        \
}
//______________________________________________________________________________
std::wstring &Binary_file_abstract::read_wstring
(std::wstring &str
,String_format format
,nat32        field_length)                     performs_IO_
{
   nat32 remaining_field_length = field_length ? field_length : 0xFFFFFFFF;
   nat32 str_length = 0xFFFFFFFF; /* Essentially infinate */
   Data_type character_count_datatype = (Data_type)(format &CORN_len_data_type_bitmask);
   switch (character_count_datatype)  /* for string formats where the run length preceeds the string*/
   {  case DT_nat8 :  { str_length = (nat32)read_nat8(); remaining_field_length-=1;} break;
      case DT_nat16:  { str_length = (nat32)read_nat16();remaining_field_length-=2;} break;
      case DT_nat32:  { str_length = (nat32)read_nat32();remaining_field_length-=4;} break;
      default : /*no need to adjust string length because we are not limiting the field size */ break;
   }
   bool null_terminate = format & CORN_null_term_bitmask;
   bool continue_reading = str_length && remaining_field_length;
   nat32 i = 0;
   nat8 char_code_data_size_in_the_file = (format & CORN_char_size_bitmask) >> 8;
   if (char_code_data_size_in_the_file == 0)
      char_code_data_size_in_the_file = 1;
   while (continue_reading)
   {
      Unicode_storage_type  char_in = 0;
      switch (char_code_data_size_in_the_file)
      {  /* The data in the file may be either UTF8, UTF16 UTF32 */
         case DT_nat16  : char_in = read_nat16();   break;
         case DT_nat32  : char_in = read_nat32();   break;
         case DT_nat8   : default : char_in = read_nat8();  break;
      }
      /* Currently I am only implementing UTF16 and UTF32,                              */
      /* UTF8 has a more complicated parsing and I don't think any Windows apps use it. */
      /* NYI endian swapping: look at the CORN_endian_bitmask bit of the format.  */
      /* Currently assuming the endienness of the record is the same as the file itself which is */
      /* probably always going to be the case.*/
      if (char_in)
         str.append(1,char_in);
      i++;
      remaining_field_length -= char_code_data_size_in_the_file;
      if (i == str_length)                    { continue_reading = false; }
      if ((null_terminate) && (char_in == 0)) { continue_reading = false; }
      if (remaining_field_length == 0)        { continue_reading = false; }
   }
   return str;
}
//_2010-01-14_2005-04-08________________________________________________________

#ifdef FOR_DEBUGGING

std::string &Binary_file_abstract::read_string
(std::string &str
,String_format format
,nat32        field_length)                     performs_IO_
{
   nat32 remaining_field_length = field_length ? field_length : 0xFFFFFFFF;
   nat32 str_length = 0xFFFFFFFF; /* Essentially infinate */
   Data_type character_count_datatype = (Data_type)(format &CORN_len_data_type_bitmask);
   switch (character_count_datatype)  /* for string formats where the run length preceeds the string*/
   {  case DT_nat8 :  { str_length = (nat32)read_nat8(); remaining_field_length-=1;} break;
      case DT_nat16:  { str_length = (nat32)read_nat16();remaining_field_length-=2;} break;
      case DT_nat32:  { str_length = (nat32)read_nat32();remaining_field_length-=4;} break;
      default : /*no need to adjust string length because we are not limiting the field size */ break;
   }
   bool null_terminate = format & CORN_null_term_bitmask;
   bool continue_reading = str_length && remaining_field_length;
   nat32 i = 0;
   nat8 char_code_data_size_in_the_file = (format & CORN_char_size_bitmask) >> 8;
   if (char_code_data_size_in_the_file == 0)
      char_code_data_size_in_the_file = 1;

   while (continue_reading)
   {
      char  char_in = 0;
      switch (char_code_data_size_in_the_file)
      {  /* The data in the file may be either UTF8, UTF16 UTF32 */
         case DT_nat16  : char_in = read_nat16();   break;
         case DT_nat32  : char_in = read_nat32();   break;
         case DT_nat8   : default : char_in = read_nat8();  break;
      }
      /* Currently I am only implementing UTF16 and UTF32,                              */
      /* UTF8 has a more complicated parsing and I don't think any Windows apps use it. */
      /* NYI endian swapping: look at the CORN_endian_bitmask bit of the format.  */
      /* Currently assuming the endienness of the record is the same as the file itself which is */
      /* probably always going to be the case.*/
      if (char_in)
         str.append(1,char_in);
      i++;
      remaining_field_length -= char_code_data_size_in_the_file;
      if (i == str_length)                    { continue_reading = false; }
      if ((null_terminate) && (char_in == 0)) { continue_reading = false; }
      if (remaining_field_length == 0)        { continue_reading = false; }
   }
   return str;
}
#endif
//_2005-04-08___________________________________________________________________
//read_Xstring_implementation(read_string   ,std::string,  char);


#define string_class     std::string
#define string_char_type char
string_class &Binary_file_abstract::read_string \
(string_class &str                                                                                    \
,String_format format                                                                                 \
,nat32        field_length)                     performs_IO_                                          \
{                                                                                                     \
   nat32 remaining_field_length = field_length ? field_length : 0xFFFFFFFF;                           \
   nat32 str_length = 0xFFFFFFFF; /* Essentially infinate */                                          \
   Data_type character_count_datatype = (Data_type)(format &CORN_len_data_type_bitmask);              \
   switch (character_count_datatype)  /* for string formats where the run length preceeds the string*/\
   {  case DT_nat8 :  { str_length = (nat32)read_nat8(); remaining_field_length-=1;} break;           \
      case DT_nat16:  { str_length = (nat32)read_nat16();remaining_field_length-=2;} break;           \
      case DT_nat32:  { str_length = (nat32)read_nat32();remaining_field_length-=4;} break;           \
      default : /*no need to adjust string length because we are not limiting the field size */ break;\
   }                                                                                                  \
   bool null_terminate = format & CORN_null_term_bitmask;                                             \
   bool continue_reading = str_length && remaining_field_length;                                      \
   nat32 i = 0;                                                                                       \
   nat8 char_code_data_size_in_the_file = (format & CORN_char_size_bitmask) >> 8;                     \
   if (char_code_data_size_in_the_file == 0)  /* Could be 0 if simple ASCII*/                         \
      char_code_data_size_in_the_file = 1;                                                            \
   while (continue_reading)                                                                           \
   {                                                                                                  \
      string_char_type  char_in = 0;                                                                  \
      switch (char_code_data_size_in_the_file)                                                        \
      {  /* The data in the file may be either UTF8, UTF16 UTF32 */                                   \
         case DT_nat16  : char_in = read_nat16();   break;                                            \
         case DT_nat32  : char_in = read_nat32();   break;                                            \
         case DT_nat8   : default : char_in = read_nat8();  break;                                    \
      }                                                                                               \
      /* Currently I am only implementing UTF16 and UTF32,                              */            \
      /* UTF8 has a more complicated parsing and I don't think any Windows apps use it. */            \
      /* NYI endian swapping: look at the CORN_endian_bitmask bit of the format.  */                  \
      /* Currently assuming the endienness of the record is the same as the file itself which is */   \
      /* probably always going to be the case.*/                                                      \
      if (char_in)                                                                                    \
         str.append(1,char_in);                                                                       \
      i++;                                                                                            \
      remaining_field_length -= char_code_data_size_in_the_file;                                      \
      if (i == str_length)                    { continue_reading = false; }                           \
      if ((null_terminate) && (char_in == 0)) { continue_reading = false; }                           \
      if (remaining_field_length == 0)        { continue_reading = false; }                           \
   }                                                                                                  \
   return str;                                                                                        \
}


//______________________________________________________________________________
char *Binary_file_abstract::read_c_str
(char *cstr,String_format format ,nat32 field_length)                performs_IO_
{  std::string buffer;
   read_string(buffer,format,field_length);
   strncpy(cstr,buffer.c_str(),buffer.length());
   bool null_terminate = format & CORN_null_term_bitmask;
   if (null_terminate) cstr[buffer.length()] = 0;
   return cstr;
}
//______________________________________________________________________________
} // namespace CORN


