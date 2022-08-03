#ifndef ustringH
#define ustringH
/*
   This class attempts to emulates some of the Borland cstring string
   class functions based on the string class library:

   Character string manipulation library superclass is based on string class
   by R B Davies 1996  (now using 2005 version)
*/

#include <corn/const.h>
#ifdef unix
#		   define USE_STD_STRING
#endif
#ifdef USTRING_DERIVE_FROM_RDB_STRING
#  define EMULATE_STRING
#  define WANT_STREAM
#  include <corn/string/str/include.h>
#  include <corn/string/str/str.h>
#  define CORN_pos unsigned int
#  define CORN_string_size unsigned int
#  define Super_string RDB_STRING__ String
#  define CORN_npos  (CORN_pos)(-1)
#else
#  ifdef __BCPLUSPLUS__
#     if (__BCPLUSPLUS__ >= 0x0550)
		 // C++ Builder  (I think version 3 0x0530 and version 4 0x0540 for would also work, but haven't tried them
#           define USE_STD_STRING
#     else
#        include <cstring.h>
#        define CORN_pos size_t
#        define CORN_npos  NPOS
#        define CORN_string_size size_t
#        define Super_string string
#     endif
#  else
#     define USE_STD_STRING
#     ifdef _MSC_VER
//#		   define USE_STD_STRING

#        if (_MSC_VER < 1300)
//050812
//       Not sure why __STDC__ gets undefined somewhere
//       I think this define can be deleted, but need to check with MSVS .NET 2002
//       it definitely causes problems with MSVS .NET 2003
#           define   __STDC__ 1
#        endif
#     else
#        include <cstring>
#     endif
#  endif
#endif

#ifdef USE_STD_STRING
#        include <string>
#        define Super_string std::string
#        define EMULATE_STRING
#else
#error reached

#endif

#ifdef EMULATE_STRING
#        define CORN_pos size_t
#        define CORN_npos std::string::npos
                // rename this to CORN_npos

#        define CORN_string_size size_t
#else
#error reached

#endif


//140311 #  include <corn/no_ns.h>

namespace CORN {
//______________________________________________________________________________
class Ustring : public Super_string
{protected:
   contribute_ int skip_white;
   contribute_ bool case_sensitive;                                              //060105
 public:
#ifdef EMULATE_STRING
   enum StripType { Leading, Trailing, Both };                                   //001021
 public:
   inline int get_skip_whitespace_flag()                                   const { return skip_white; };
   inline int set_skip_whitespace_flag(int i_skip_white)           contribution_ //020332
      {  skip_white = i_skip_white;
         return skip_white; };
   char get_at( CORN_pos pos)                                              const;//980403
   void to_upper()                                                 modification_;//980403
   virtual Ustring &prepend(const Ustring &s)                      modification_;//980403
   virtual int contains(const char * pat)                                  const;//001002
   virtual void to_lower()                                         modification_;//001003
   Ustring &strip( StripType s = Trailing, char c=' ')             modification_;//001021
   int set_case_sensitive(int tf = 1)                              contribution_;//060105
#else
///*_______*/    inline int get_skip_whitespace_flag()
///*_______*/    { return  Super_string::get_skipwhitespace_flag(); };
   inline int set_skip_whitespace_flag(int i_skip_white)           contribution_ //020332
      { return skip_whitespace(i_skip_white); };
#endif
   Ustring &strip_self(StripType s = Trailing, char c=' ')         modification_;//001021
      /** This is similar to strip but it modifies itself
          with the stripped string.
      **/
   Ustring &replace_character(char current_c, char replacement_c)  modification_;//050929
//             This replaces all occurances of the specified character (current_c)
//             to the replacement character.  Self is modified.
   const char *get_SDF(Ustring &result,bool append_to_result)              const;//021031
//             Set result to SDF (System Data Format) format of the string:
//             I.e.   the value of     example     -> "example"
//                                     "example"   -> ""example""
//                                     exam"ple    -> "exam""ple"
//             In append mode result will append , and the SDF string to result
//

#if (__BCPLUSPLUS__ < 0x0550)
   // The early BC++ 5.0 string class did not have erase
   Ustring& erase ( size_t pos = 0, size_t n = CORN_npos )         modification_;//091111
#endif
   const wchar_t *w_str()                                                  const;//110103
      // Returns a null terminated wide char representation of the string
#define SUBSTRING_NOT_FOUND 0xFFFFFFFF
   unsigned long find_substring(const char *sub_str)                       const;//040322
      /** \return the index (0 based) where sub_str occurs in the string
          \return FFFFFFFF if the substring does not occur
      **/
 public: // constructors                                                         //020125
   Ustring();
   Ustring(const Super_string& str);  // not explicitly in standard
   Ustring(const Super_string& str, CORN_pos pos, CORN_string_size n = CORN_npos);
   Ustring(const Ustring& str, CORN_pos pos, CORN_string_size n = CORN_npos);
   Ustring(const char *str, CORN_pos pos, CORN_string_size n = CORN_npos);       //030724
   Ustring(const char* s, CORN_pos n);
   Ustring(const char* s);
   Ustring(char c,CORN_string_size n );                                          //040909
   Ustring(const wchar_t *s);                                                    //101015
   Ustring(const std::wstring &s);                                               //120321
};
//______________________________________________________________________________
}; // namespace CORN                                                             //040428
#endif
//ustring

