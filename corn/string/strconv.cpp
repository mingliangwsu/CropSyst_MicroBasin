#include "corn/string/strconv.hpp"
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
// Functions for converting character arrays to integers and vica versa.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "corn/string/strconv.c_cpp"
#include <iostream>
// in UNIX, MSC and BC++ strtoul is in stdlib.h
// it might be in other header files for other compiler vendors
//______________________________________________________________________________
namespace CORN {
std::string &wstring_to_string(const std::wstring &wstr,std::string &str)
{  str.clear();
   for (size_t i = 0; i < wstr.length(); i++)
      str.append(1,(char)wstr.data()[i]);
   return str;
}
//______________________________________________________________________________
std::wstring &string_to_wstring(const std::string &str,std::wstring &wstr)
{  wstr.clear();
   for (size_t i = 0; i < str.length(); i++)
      wstr.append(1,(wchar_t)str.c_str()[i]);
   return wstr;
}
//______________________________________________________________________________
std::string &UnicodeZ_to_string(const_UnicodeZ wstr,std::string &str)
{  str.clear();
   for (size_t i = 0; wstr[i]; i++)
      str.append(1,(char)wstr[i]);
   return str;
}
//_2012-02-05___________________________________________________________________
std::wstring &ASCIIZ_to_wstring(const_ASCIIZ astr,std::wstring &wstr)
{  wstr.clear();
   for (size_t i = 0; astr[i]; i++)
      wstr.append(1,(char)astr[i]);
   return wstr;
}
//_2012-02-05___________________________________________________________________
char * wstring_to_ASCIIZ (const std::wstring &wstr,char         *cstr)
{  cstr[0] = 0;
   return append_wstring_to_ASCIIZ(wstr,cstr);
}
//_2013-08-27___________________________________________________________________
std::string &append_wstring_to_string(const std::wstring &wstr,std::string &str)
{  for (size_t i = 0; i < wstr.length(); i++)
      str.append(1,(char)wstr.data()[i]);
   return str;
}
//_2012-02-09___________________________________________________________________
std::wstring &append_string_to_wstring(const std::string &str,std::wstring &wstr)
{  for (size_t i = 0; i < str.length(); i++)
      wstr.append(1,(wchar_t)str.c_str()[i]);
   return wstr;
}
//_2012-02-09___________________________________________________________________
std::string &append_UnicodeZ_to_string(const_UnicodeZ wstr,std::string &str)
{  for (size_t i = 0; wstr[i]; i++)
      str.append(1,(char)wstr[i]);
   return str;
}
//_2012-02-09___________________________________________________________________
std::wstring &append_ASCIIZ_to_wstring(const_ASCIIZ astr,std::wstring &wstr)
{  for (size_t i = 0; astr[i]; i++)
      wstr.append(1,(char)astr[i]);
   return wstr;
}
//_2012-02-09___________________________________________________________________
std::string &append_ASCIIZ_to_string(const_ASCIIZ astr,std::string &str)
{  for (size_t i = 0; astr[i]; i++)
      str.append(1,(char)astr[i]);
   return str;
}
//_2012-02-09___________________________________________________________________
char *append_wstring_to_ASCIIZ (const std::wstring &wstr,char *cstr)
{  for (size_t i = 0; cstr[i]; i++)
      cstr[i] = (char)wstr.c_str()[i];
   return cstr;
}
//_2013-08-27__________________________________________________________________/
std::string &strip_string(std::string  &astr, StripType s , char c)
{  std::string stripped(astr);
   if ((s == Leading) || (s == Both ))
   {  int strip_count =0;
      for (size_t i =0;i<astr.length() && stripped.c_str()[i] == c; i++)
         strip_count++;
      if (strip_count)                                                           //010311
      {  stripped.assign(std::string(astr,strip_count,astr.length()-strip_count));//010311
         astr.assign(stripped);                                                  //010311
   }  }                                                                          //010311
   if (((s == Trailing) || (s == Both ))  && astr.length())                      //010105
   {  int strip_count =0;
      int start_pos = astr.length();
      for (int i = start_pos-1 ;i && stripped.c_str()[i] == c;i--)
         strip_count++;
      if (strip_count)                                                           //010311
      {  stripped.assign(std::string(astr,0,astr.length() - strip_count));       //001117
         astr.assign(stripped);                                                  //010311
   }  }                                                                          //010311
   return astr;
}
//_2013-09-19___________________________________________________________________
std::wstring &strip_wstring(std::wstring  &astr, StripType s , wchar_t c)
{  std::wstring stripped(astr);
   if ((s == Leading) || (s == Both ))
   {  int strip_count =0;
      for (size_t i =0;i<astr.length() && stripped.c_str()[i] == c; i++)
         strip_count++;
      if (strip_count)                                                           //010311
      {  stripped.assign(std::wstring(astr,strip_count,astr.length()-strip_count)); //010311
         astr.assign(stripped);                                                  //010311
   }  }                                                                          //010311
   if (((s == Trailing) || (s == Both ))  && astr.length())                      //010105
   {  int strip_count =0;
      int start_pos = astr.length();
      for (int i = start_pos-1 ;i && stripped.c_str()[i] == c;i--)
         strip_count++;
      if (strip_count)                                                           //010311
      {  stripped.assign(std::wstring(astr,0,astr.length() - strip_count));      //001117
         astr.assign(stripped);                                                  //010311
   }  }                                                                          //010311
   return astr;
}
//_2014-01-21___________________________________________________________________
std::string &append_SDF_to(const std::string &source_string, std::string &to_string,bool append_to_result)
{
   if (append_to_result)
   {  if (to_string.length())
          to_string.append(",");
   } else to_string.assign("");
   to_string.append("\"");
   for (uint16 i = 0; i < (uint16)source_string.length(); i++)
   {  if (source_string.c_str()[i] == '"')
         to_string.append("\"");
      to_string += source_string.c_str()[i];
   }
   to_string.append("\"");
   return to_string;
}
//_2013-09-19___________________________________________________________________
std::string &replace_character(std::string &original, char current_c, char replacement_c)
{  // This replaces all occurances of the specified character (current_c)
   // to the replacement character.  Self is modified.
   std::string replaced;
   char new_char_buf[2]; new_char_buf[1] = 0;
   const char *current = original.c_str();
   int curr_len = original.length();
   for (int i = 0; i < curr_len; i++)
   {  char curr_char_i = current[i];
      new_char_buf[0] =curr_char_i== current_c ? replacement_c : curr_char_i;
      replaced.append(new_char_buf);
   }
   original.assign(replaced);
   return original;
}
//_2013-10-08__2005-09-29_______________________________________________________
std::string &append_float32_to_string(float32 value,nat8 decimals,std::string &to_string)
{  to_string.append(float32_to_cstr(value,(int)decimals));
   return to_string;
}
//_2013-12-13___________________________________________________________________
std::string &append_float64_to_string(float64 value,nat8 decimals,std::string &to_string)
{  to_string.append(float64_to_cstr(value,(int)decimals));
   return to_string;
}
//_2014-07-05___________________________________________________________________
std::string &append_int8_to_string   (int8    value,std::string &str,int8 radix,nat16 str_width,char leading_char)
{  return append_int32_to_string((int32)value,str,radix,str_width,leading_char);
}
//_2014-06-15___________________________________________________________________
std::string &append_nat8_to_string   (nat8    value,std::string &str,int8 radix,nat16 str_width,char leading_char)
{  return append_int32_to_string((int32)value,str,radix,str_width,leading_char);
}
//_2014-06-15___________________________________________________________________
std::string &append_int16_to_string  (int16   value,std::string &str,int8 radix,nat16 str_width,char leading_char)
{  return append_int32_to_string((int32)value,str,radix,str_width,leading_char);
}
//_2014-06-15___________________________________________________________________
std::string &append_nat16_to_string  (nat16   value,std::string &str,int8 radix,nat16 str_width,char leading_char)
{  return append_nat32_to_string((nat32)value,str,radix,str_width,leading_char);
}
//_2014-06-15___________________________________________________________________
std::string &append_int32_to_string  (int32   value,std::string &str,int8 radix,nat16 str_width,char leading_char)
{  char cstr[20];
   int32_to_cstr (value,cstr,radix,str_width,leading_char);
   str.append(cstr);
   return str;
}
//_2014-02-16___________________________________________________________________
std::string &append_nat32_to_string(nat32   value,std::string &str,int8 radix,nat16 str_width,char leading_char)
{  char cstr[20];
   nat32_to_cstr (value,cstr,radix,str_width,leading_char);
   str.append(cstr);
   return str;
}
//_2014-06-15___________________________________________________________________
std::wstring &append_int32_to_wstring(int32   value,std::wstring &str,int8 radix,nat16 str_width,char leading_char)
{  char cstr[20];
   int32_to_cstr (value,cstr,radix,str_width,leading_char);
   append_ASCIIZ_to_wstring(cstr,str);
   return str;
}
//_2015-04-19___________________________________________________________________
std::wstring &append_nat32_to_wstring(nat32   value,std::wstring &str,int8 radix,nat16 str_width,char leading_char)
{  char cstr[20];
   nat32_to_cstr (value,cstr,radix,str_width,leading_char);
   append_ASCIIZ_to_wstring(cstr,str);
   return str;
}
//_2015-04-19___________________________________________________________________
std::istream  &read_token(std::istream  & strm,std::string &token)
{
#ifdef _MSC_VER
   char to_token[255];
   strm >> to_token;      // Warning not sure if this will work.
   token.assign(to_token);
#else
   strm >> token;
#endif
   return strm;
}
//_2014-01-06___________________________________________________________________
size_t find_case_insensitive(const std::string &in_string,const std::string &sub_string)
{
  char *in_string_cstr = (char *)malloc(in_string.length()+1);
#ifdef __unix
// unix c++ compiler string.h library does not have strupr
   int lngth = in_string.length();                                               //140602_010924
   for (int i = 0; i < lngth; i++)                                               //001117
      in_string_cstr[i] = toupper(in_string.c_str()[i]);                         //140602_001117
   in_string_cstr[lngth] = 0;                                                    //140602_010924
#else
   strcpy(in_string_cstr,in_string.c_str());
   strupr(in_string_cstr); // some compilers use _strupr (define this in strconv.h)
#endif
   std::string in_string_UC(in_string_cstr);
   delete in_string_cstr;                                                         //001117
  char *sub_string_cstr = (char *)malloc(sub_string.length()+1);
#ifdef __unix
// unix c++ compiler string.h library does not have strupr
   lngth = sub_string.length();                                                  //140602_010924
   for (int i = 0; i < lngth; i++)                                               //001117
      sub_string_cstr[i] = toupper(sub_string.c_str()[i]);                       //001117
   sub_string_cstr[lngth] = 0;                                                   //010924
#else
   strcpy(sub_string_cstr,sub_string.c_str());
   strupr(sub_string_cstr); // some compilers use _strupr (define this in strconv.h)
#endif
   std::string sub_string_UC(sub_string_cstr);

   delete sub_string_cstr;                                                       //001117
   return in_string_UC.find(sub_string_UC);
}
//_2014-05_16___________________________________________________________________
} // namespace CORN

