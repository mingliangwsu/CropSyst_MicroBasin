#error This class is obsolete replaced with corn/chronometry/temporal.cpp

#include "corn/datetime/temporal_base.h"
#include "corn/string/strconv.hpp"
namespace CORN
{
//______________________________________________________________________________
int8 Temporal_base::temporal_compare(const Temporal_base & second_time)    const
{  float64 time64 = get_datetime64();
   float64 second_time64 = second_time.get_datetime64();
   return (int8)(time64 < second_time64)
	  ? (int8)-1
	  : (int8)((time64 > second_time64)
		 ? 1
		 : 0);
}
//_2003-01-08___________________________________________________________________
std::string Temporal_base::as_string()                                     const
{  std::string buffer;
   append_to_string(buffer);
   return buffer;
}
//_2014-06-14___________________________________________________________________
const std::wstring &Temporal_base::append_to_wstring(std::wstring &target) const
{  CORN::string_to_wstring(as_string(),target);
   return target;
}
//_2014-09-19___________________________________________________________________
} // namespace CORN_end

