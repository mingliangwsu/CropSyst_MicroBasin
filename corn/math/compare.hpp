#ifndef compareHPP
#define compareHPP

#ifndef _ALGORITHM_
#  include <algorithm>
#endif

namespace CORN
{
//______________________________________________________________________________
template <typename T> inline
int compare(const T &  value1, const T &  value2)
{  int result = 0;
   if (value1 <  value2) result = -1;
   if (value1 >  value2) result = 1;
   // default if (value1 == value2) result = 0;
   return result;
}
//______________________________________________________________________________
template <typename T> inline
const T & must_be_less_or_equal_to(const T & left, const T & right)
{ return (std::min<T>(left,right)); }
//______________________________________________________________________________
template <typename T> inline
const T & must_be_greater_or_equal_to(const T & left, const T & right)
{ return (std::max<T>(left,right)); }
//______________________________________________________________________________
template <typename T> inline
const T & must_be_0_or_greater(const T & value)
{ return (std::max<T>(value,0.0)); }
//_2015-11-09___________________________________________________________________
template <typename T> inline
const T & must_be_0_or_less(const T & value)
{ return (std::min<T>(value,0.0)); }
//_2015-11-09___________________________________________________________________
template <typename T> inline
const T & must_be_between(const T &value, const T & left, const T & right)
{ return (std::min<T>((std::max<T>(value,left)),right)); }
//______________________________________________________________________________
template <typename T> inline
bool is_approximately(const T &value,const T &target,const T &tolerance=0.0000001) //170614_141222
{
   T abs_diff = (target - value);
   if (abs_diff < 0.0) abs_diff = -abs_diff;
   bool it_is = (abs_diff <= tolerance) ;
   return it_is;
}
//______________________________________________________________________________
} // namespace CORN
#endif
//compare

