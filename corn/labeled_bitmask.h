#ifndef labeled_bitmaskH
#define labeled_bitmaskH
#include "corn/const.h"
#include "corn/primitive.h"
#include <string>
namespace CORN {
//______________________________________________________________________________
interface_ Labeled_bitmask
{
   virtual bool  is (nat32 other_bitmask)                        affirmation_=0;
   virtual nat32 has(nat32 other_bitmask)                        affirmation_=0;
   virtual nat32 set(nat32 other_bitmask)                       modification_=0;
   // The set string methods take one or more space delimited labels
   virtual nat32 set_wstring(const std::wstring &labels)        modification_=0;
   virtual nat32 set_string (const std::string  &labels)        modification_=0;
   virtual nat32 set_wstr   (const wchar_t      *labels)        modification_=0;
   virtual nat32 set_cstr   (const char         *labels)        modification_=0;
   // The following compose space labels
   virtual const std::wstring &append_to_wstring(std::wstring &buffer)  const=0;
   virtual const std::string &append_to_string(std::string &buffer)     const=0;
};
//_2015-08-04___________________________________________________________________
} // namespace CORN
#endif
