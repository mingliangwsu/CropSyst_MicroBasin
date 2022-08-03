#ifndef UIOstringH
#define UIOstringH
/*
   This class attempts to emulates some of the Borland cstring string
   class functions based on the string class library:

   Character string manipulation library superclass is based on string class
   by R B Davies 1996
*/
#include <corn/string/ustring.h>
#include <corn/std/std_iostream.h>
namespace CORN {
//______________________________________________________________________________
class  UIO_string : public Ustring
{public:
   inline UIO_string()
   : Ustring(){}
   inline UIO_string(const Ustring& str)
   : Ustring(str){}     // not explicitly in standard
   inline UIO_string(const Ustring& str, CORN_pos pos, CORN_pos n = CORN_npos)
   : Ustring(str,pos,n){}
   inline UIO_string(const UIO_string& str, CORN_pos pos, CORN_pos n = CORN_npos)
   : Ustring(str,pos,n){}
   inline UIO_string(const char *str, CORN_pos pos, CORN_pos n = CORN_npos)             //030724
   : Ustring(str,pos,n){}
   inline UIO_string(const char* s)
   : Ustring(s){}
   inline UIO_string(char c,CORN_pos n)                                                 //040909_
   : Ustring(c,n){}
#ifdef EMULATE_STRING
   // The following functions are not provided by Davies' string class
   STD_NS istream &read_file      (STD_NS istream  &is );
   STD_NS istream &read_string    (STD_NS istream  &is );
   STD_NS istream &read_line      (STD_NS istream  &is );
   STD_NS istream &read_to_delim  (STD_NS istream  &is, char delim = '\n' );
   STD_NS istream &read_token     (STD_NS istream  &is );
#endif
};
//______________________________________________________________________________
} // namespace CORN

#define CORN_string CORN::UIO_string

#endif
//cstrngem

