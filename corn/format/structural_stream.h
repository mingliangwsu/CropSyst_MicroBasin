#ifndef structural_streamH
#define structural_streamH
#include <fstream>
#include <string>
#include "corn/const.h"
#include "corn/format/structural.h"
//#include "corn/OS/directory_entry_name.h"
#include "corn/OS/directory_entry_name_concrete.h"
namespace CORN
{
//______________________________________________________________________________
enum Parse_error_code
{ ERROR_none
, ERROR_unknown
};
//______________________________________________________________________________
struct Error
: public extends_ CORN::Item
{
   nat8                     code;
   structural::Construct   *in_construct;
   nat32                    line;
};
//______________________________________________________________________________
interface_ Structural_istream
{
   inline virtual nat8 get(structural::Construct &document)        modification_
      { return parse_document(document); }
   virtual nat8 parse_document
      (structural::Construct     &document)                   modification_ = 0;
      /// \returns error code or 0 if no error
};
//_2017-01-28___________________________________________________________________
template <typename  ifstream_T,/*170305  typename Char_T, */typename  String_T >
class Structural_ifstream_generic
: public extends_ ifstream_T
, public implements_ Structural_istream
{
 protected:
   CORN::OS::File_name_concrete filename;                                        //170305
 public:
/*170305
   Structural_ifstream_generic() //170305 (const Char_T *filename)
      : ifstream_T() //170305 (filename)
      {}
*/

   Structural_ifstream_generic(const CORN::OS::File_name &filename_)
      : ifstream_T()
//      : ifstream_T(filename_.c_str())
      , filename(filename_)
      {
         this->open(filename_.c_str());
      }
};
//_2017-01-28___________________________________________________________________
class Structural_ifstream_ASCII
: public extends_ Structural_ifstream_generic<std::ifstream/*,char*/,std::string>
{
 public:
   inline Structural_ifstream_ASCII(const CORN::OS::File_name &filename)
      : Structural_ifstream_generic<std::ifstream,/*char,*/std::string >(filename)
      {}
};
//_2017-01-28___________________________________________________________________
class Structural_ifstream_Unicode
: public extends_ Structural_ifstream_generic<std::wifstream ,/*wchar_t,*/std::wstring>
{
 public:
   inline Structural_ifstream_Unicode(const CORN::OS::File_name &filename)
      : Structural_ifstream_generic<std::wifstream,/*wchar_t,*/std::wstring>(filename)
      {}
};
//_2017-01-28___________________________________________________________________
//______________________________________________________________________________
} // namespace CORN

#endif
