#include "corn/string/ustring.h"
#include <ctype.h>
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/string/strconv.hpp"
#include <stdlib.h>
//090227 stdlib is needed for malloc

// These functions are based on stringIO.cpp from Borland C++
namespace CORN {
//______________________________________________________________________________
Ustring::Ustring()
   : Super_string(){};
Ustring::Ustring(const    Super_string& str)
   : Super_string(str), skip_white(1){};     // not explicitly in standard
Ustring::Ustring(const   Super_string& str, CORN_pos pos, CORN_string_size n )
   : Super_string(str,pos,n),skip_white(1){};
Ustring::Ustring(const Ustring& str, CORN_pos pos, CORN_string_size n )
   : Super_string(str,pos,n),skip_white(1){};
Ustring::Ustring(const char *str, CORN_pos pos, CORN_string_size n)              //030724
   : Super_string(str,pos,n),skip_white(1){};
Ustring::Ustring(const char* s, CORN_string_size n)
   : Super_string(s,n),skip_white(1){};
Ustring::Ustring(const char* s)
   : Super_string(s), skip_white(1){};
Ustring::Ustring(char c, CORN_string_size n )                                    //040909
   : Super_string(c,n), skip_white(1){};
Ustring::Ustring(const wchar_t *s)                                               //101015
{  std::wstring as_wstring(s);
   wstring_to_string(as_wstring,*this);                                          //101015
};
Ustring::Ustring(const std::wstring &s)                                          //120321
{  wstring_to_string(s,*this);
};
//______________________________________________________________________________
Ustring &Ustring::strip_self( StripType s , char c)     modification_
{  Ustring stripped(c_str());
   if ((s == Leading) || (s == Both ))
   {  int strip_count =0;
      for (CORN_pos i =0;i<length() && stripped.c_str()[i] == c; i++)
         strip_count++;
      if (strip_count)                                                           //010311
      {  stripped.assign(Ustring(*this,strip_count,length()-strip_count));       //010311
         assign(stripped);                                                       //010311
   }; };                                                                         //010311
   if (((s == Trailing) || (s == Both ))  && length())                           //010105
   {  int strip_count =0;
      int start_pos =length();
      for (int i = start_pos-1 ;i && stripped.c_str()[i] == c;i--)
         strip_count++;
      if (strip_count)                                                           //010311
      {  stripped.assign(Ustring(*this,0,length() - strip_count));               //001117
         assign(stripped);                                                       //010311
   }; };                                                                         //010311
   return *this;
};
//_2000-10-21___________________________________________________________________
Ustring &Ustring::replace_character(char current_c, char replacement_c)
{  // This replaces all occurances of the specified character (current_c)
   // to the replacement character.  Self is modified.
   Ustring replaced;
   char new_char_buf[2]; new_char_buf[1] = 0;
   const char *current = c_str();
   int curr_len = length();
   for (int i = 0; i < curr_len; i++)
   {  char curr_char_i = current[i];
      new_char_buf[0] =curr_char_i== current_c ? replacement_c : curr_char_i;
      replaced.append(new_char_buf);
   };
   assign(replaced);
   return *this;
};
//_2005-09-29___________________________________________________________________
#ifdef EMULATE_STRING
Ustring &Ustring::strip( StripType s , char c)                     modification_
{   strip_self(s,c);                                                             //050523
    return *this;                                                                //050523_
};
//_2000-10-21___________________________________________________________________
Ustring &Ustring::prepend(const Ustring &s)
{  Ustring result(s);
   result.append(c_str());
   assign(result);
   return *this;
};
//_1998-04-03___________________________________________________________________
void Ustring::to_upper()
{  char *buffer = (char *)malloc(length()+1);
#ifdef __unix
// unix c++ compiler string.h library does not have strupr
   int lngth = length();                                                         //010924
   for (int i = 0; i < lngth; i++)                                               //001117
      buffer[i] = toupper(c_str()[i]);                                           //001117
   buffer[lngth] = 0;                                                            //010924
#else
   strcpy(buffer,c_str());
   strupr(buffer); // some compilers use _strupr (define this in strconv.h)
#endif
   assign(buffer);
   delete buffer;                                                                //001117
};
//_1998-04-03___________________________________________________________________
void Ustring::to_lower()
{  char *buffer = new char[length()+1];
#if defined (__unix) || defined(unix) || defined(__GNUC__)
// unix c++ compiler string.h library does not have strlwr
   int lngth = length();                                                         //010924
   for (int i = 0; i < lngth; i++)                                               //001117
      buffer[i] = tolower(c_str()[i]);                                           //001117
   buffer[lngth] = 0;                                                            //010924
#else
   strcpy(buffer,c_str());
   strlwr(buffer);          // some compilers use _strlwr (define this in strconv.h)
#endif
   assign(buffer);
   delete [] buffer;                                                             //001117_
};
//_2000-10-03___________________________________________________________________
int Ustring::set_case_sensitive(int tf)                            contribution_
{  case_sensitive = tf;
   // Warning, although I have set this, I am not currently using it
   // would need to override compare functions
   return  case_sensitive;
};
#endif
// end EMULATE_STRING
//_2006-01-05___________________________________________________________________
const char *Ustring::get_SDF(Ustring &result,bool append_to_result) const
{  if (append_to_result)
   {  if (result.length())
          result.append(",");
   } else result.assign("");
   result.append("\"");
   for (uint16 i = 0; i < (uint16)length(); i++)
   {  if (c_str()[i] == '"')
         result.append("\"");
      result += c_str()[i];
   };
   result.append("\"");
   return result.c_str();                                                        //021205_
};
//_2002-10-31___________________________________________________________________
unsigned long Ustring::find_substring(const char *sub_str) const
{  const char *cstr = c_str();
   for (unsigned long cstr_i = 0; cstr[cstr_i] ; cstr_i++)
   {  for (unsigned long sstr_i = 0; (sub_str[sstr_i] == cstr[cstr_i+sstr_i]) || (sub_str[sstr_i] == 0); sstr_i++)
      {  if (sub_str[sstr_i] == 0)
            return cstr_i; // the substring match is found.
   };  };
   return SUBSTRING_NOT_FOUND;
};
//_2004-03-22___________________________________________________________________
#ifdef EMULATE_STRING
char Ustring::get_at( CORN_pos pos)                                        const
{  return at(pos);
};
//_1998-04-03___________________________________________________________________
int Ustring::contains(const char * pat)                                    const
{  return find(pat) != CORN_npos;
};
#endif
//_2000-10-02___________________________________________________________________
#if (__BCPLUSPLUS__ < 0x0550)
   // The early BC++ 5.0 string class did not have erase
Ustring& Ustring::erase ( size_t pos, size_t n)
{  Ustring buffer(*this,n);
   assign(buffer);
   return *this;
};
#endif
//_2009-11-11___________________________________________________________________
const wchar_t *Ustring::w_str()                                            const
{  static std::wstring wide_buffer;
   CORN::string_to_wstring(*this,wide_buffer);
   return wide_buffer.data();
};
//_2011-01-03___________________________________________________________________
/*040428_*/ } // namespace CORN

