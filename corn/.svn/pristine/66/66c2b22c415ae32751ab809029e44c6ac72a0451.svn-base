#include <corn/string/uiostring.h>
#include <ctype.h>
// These functions are based on stringIO.cpp from Borland C++

// Read to EOF, or null terminator, whichever comes first:

namespace CORN {
#ifdef EMULATE_STRING
//______________________________________________________________________________
STD_NS istream  & UIO_string::read_file( STD_NS istream  & strm )
{  read_to_delim(strm, '\0');
   return strm;
}
//______________________________________________________________________________
// Identical to above:
STD_NS istream  & UIO_string::read_string( STD_NS istream  & strm )
{  read_to_delim(strm, '\0');
   return strm;
}
//______________________________________________________________________________
STD_NS istream  & UIO_string::read_line( STD_NS istream  & strm )
{  // If the skipWhite flag has been set, then skip any leading whitespace
   if(get_skip_whitespace_flag())
   {  char ch;
      do
      { strm.get(ch); }
      while(strm.good() && isspace(ch) && ch != '\n');
      strm.putback(ch);
   }
   read_to_delim(strm, '\n');
   // consider using getline() because read_line has problems with blank lines.
   return strm;
}
//______________________________________________________________________________
// Read to EOF or delimitor.
STD_NS istream  & UIO_string::read_to_delim(STD_NS  istream  & strm, char delim )
{  // consider using getline() because read_line has problems with blank lines.
   char buffer[256];
   char ch;
   assign("");
   while ( 1 )
   {  // Read as many characters as we can, up to the delimitor:
        strm.get(buffer, 255, delim );
        append(buffer);
        // What stopped us?  An EOF?
        if( !strm.good() )
            break;          // EOF encountered (or worse!)
        // Nope.  Was it the delimiter?
        strm.get(ch);
        if(ch==delim)
            break;  // Yup. We're done.  Don't put it back on the stream.
        else
        strm.putback(ch);   // Nope, Put it back and keep going.
        // If we got here, the read must have stopped because the buffer
        // was going to overflow.  Resize and keep going.
        //grow_to( round_capacity(nchars + string::get_resize_increment()) );
/*
        // Read as many characters as we can, up to the delimitor:
        strm.get( array+nchars, capacity-nchars+1, delim );

        // This is the new string length:
        nchars += strlen( array+nchars );

        // What stopped us?  An EOF?
        if( !strm.good() )
            break;          // EOF encountered (or worse!)

        // Nope.  Was it the delimiter?
        strm.get(ch);
        if(ch==delim)
            break;  // Yup. We're done.  Don't put it back on the stream.
        else
        strm.putback(ch);   // Nope, Put it back and keep going.

        // If we got here, the read must have stopped because the buffer
        // was going to overflow.  Resize and keep going.
        grow_to( round_capacity(nchars + string::get_resize_increment()) );
*/
   }
   return strm;
}
//______________________________________________________________________________
STD_NS istream  & UIO_string::read_token(STD_NS  istream  & strm )
{
#ifdef _MSC_VER
   char to_token[255];
   strm >> to_token;      // Warning not sure if this will work.
   this->assign(to_token);
#else
   strm >> *this;
#endif
   return strm;
}
//______________________________________________________________________________
} // namespace CORN

#endif

