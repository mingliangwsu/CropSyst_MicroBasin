#ifndef strconvH
#define strconvH
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#if defined(__GNUC__)
//#   include <strings.h>
#   include <string.h>
#   include <wchar.h>
#   ifndef __cplusplus
#      include <cstdlib>
#   endif
#endif
#ifdef __cplusplus
namespace CORN {
#endif
extern char *float32_to_cstr(float32 value, int decimals);
extern char *float64_to_cstr(float64 value, int decimals);
extern char *float32_to_cstr_formated(float32 value, char *result_str,nat8 width, nat8 precision_decimals,char decimal_mark,bool allow_scientific_notation);   //070524
extern char *float64_to_cstr_formated(float64 value, char *result_str,nat8 width, nat8 precision_decimals,char decimal_mark,bool allow_scientific_notation);   //070524
// These convert the value to a string with the formatted number
// having the specified field width and precision_decimals.
// If the number converted has a width greater than
// the specified width, the string will be truncated to the width.
// Hopefully the truncation will not truncated to the left of the
// decimal point so only precision is lost, not significant digits.
// Allow scientific notation will format in C style scientific notation if necessary.
//______________________________________________________________________________
extern char *int8_to_cstr   (int8    value,char *str,int8 radix=10,nat16 str_width=0,char leading_char=' '); //140211_980402
extern char *nat8_to_cstr   (nat8    value,char *str,int8 radix=10,nat16 str_width=0,char leading_char=' '); //140211_980402
extern char *int16_to_cstr  (int16   value,char *str,int8 radix=10,nat16 str_width=0,char leading_char=' '); //140211_980402
extern char *nat16_to_cstr  (nat16   value,char *str,int8 radix=10,nat16 str_width=0,char leading_char=' '); //140211_980402
extern char *int32_to_cstr  (int32   value,char *str,int8 radix=10,nat16 str_width=0,char leading_char=' '); //140211_980402
extern char *nat32_to_cstr  (nat32   value,char *str,int8 radix=10,nat16 str_width=0,char leading_char=' '); //140211_120314
//NYN extern wchar_t *CORN_int8_to_wstr    (int8    value,wchar_t *str,int8 radix=10,nat16 str_width=0,wchar_t leading_char=' '); //140211
//NYN extern wchar_t *CORN_nat8_to_wstr    (nat8    value,wchar_t *str,int8 radix=10,nat16 str_width=0,wchar_t leading_char=' '); //140211
//NYN extern wchar_t *CORN_int16_to_wstr   (int16   value,wchar_t *str,int8 radix=10,nat16 str_width=0,wchar_t leading_char=' '); //140211
//NYN extern wchar_t *CORN_nat16_to_wstr   (nat16   value,wchar_t *str,int8 radix=10,nat16 str_width=0,wchar_t leading_char=' '); //140211
//NYN extern wchar_t *CORN_int32_to_wstr   (int32   value,wchar_t *str,int8 radix=10,nat16 str_width=0,wchar_t leading_char=' '); //140211
extern wchar_t *nat32_to_wstr   (nat32   value,wchar_t *str,int8 radix=10,nat16 str_width=0,wchar_t leading_char=' '); //140211

//#define CORN_uint16_to_str CORN_nat16_to_str
//#define CORN_uint32_to_str CORN_nat32_to_str

#ifdef __BCPLUSPLUS__
#  include <stdlib.h>
#else
#  if (!defined ( _MSC_VER)&&!defined (__MINGW32__))
   extern char *strupr(char *s);                                                 //980404
#  endif
#endif
//______________________________________________________________________________
#ifdef _MSC_VER
//040909  MS has used _ with these common C functions!!!
#   define stricmp(x,y) _stricmp(x,y)
#   define stricmpw(x,y) _wcsicmp(x,y)
#   define strupr  _strupr
#   define strlwr  _strlwr
#endif
#if ((defined (__unix) || defined(unix)) && defined(__GNUC__))
#  define stricmp(x,y) strcasecmp(x,y)
#  define stricmpw(x,y) wcscasecmp(x,y)
//170213RLN #  define stricmpw(x,y) wcscmpi(x,y)
#  define strnicmp strncasecmp
#endif
#ifndef stricmpw
#ifdef __BCPLUSPLUS__
#  define stricmpw(x,y) wcscmpi(x,y)
#else
#  define stricmpw(x,y) _wcsicmp(x,y)
#endif
#endif
extern nat8 identify_radix_cstr(const char *str,nat8 radix);                     //170225
extern nat8 identify_radix_wstr(const wchar_t *str,nat8 radix);                  //170225
extern nat32   cstr_to_nat16  (const char *str,nat8 radix);                      //161010
extern int16   cstr_to_int16  (const char *str,nat8 radix);                      //171011
extern nat32   cstr_to_nat32  (const char *str,nat8 radix);                      //991130
extern int32   cstr_to_int32  (const char *str,nat8 radix);                      //150103
extern float32 cstr_to_float32(const char *str);                                 //150103
extern float64 cstr_to_float64(const char *str);                                 //150103
//170225 #define str_to_uint32(str,radix) (str_to_nat32(str,radix))

extern int16   wstr_to_int16  (const wchar_t *str,nat8 radix);                   //180215
extern nat32   wstr_to_nat32  (const wchar_t *str,nat8 radix);                   //150111
extern int32   wstr_to_int32  (const wchar_t *str,nat8 radix);                   //150111
extern float64 wstr_to_float64(const wchar_t *str);                              //150111
extern nat32   wstr_to_nat32  (const wchar_t *str,nat8 radix);                   //151111

extern void shrink_to(nat16  max_size                                            //010307
   , const char *long_name                                                       //030120
   , char *short_name);                                                          //030120
bool isvowel(char ch);

//#define is_number_cstr(number_str)
//#define is_number_wstr(number_str)

bool is_number_cstr(const char *number_str);                                     //050517
bool is_number_wstr(const wchar_t *number_str);                                  //160215

#if (__BCPLUSPLUS__ <= 0x340)
// Borland C++ 5.0 does not have iswspace  (Might only be available in builder
bool iswspace(char ch);                                                          //060719
#endif
//______________________________________________________________________________
extern wchar_t *ASCIIZ_to_UnicodeZ(const_ASCIIZ astr, UnicodeZ wstr);            //140211
//______________________________________________________________________________
#ifdef __cplusplus
} //namespace CORN
#endif
#endif
//strconv

