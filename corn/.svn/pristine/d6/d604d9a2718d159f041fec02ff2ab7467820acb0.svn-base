#pragma hdrstop
#include "corn/math/compare.h"
//______________________________________________________________________________
int CORN_compare_float(float value1, float value2)
{  int result = 0;
   if (value1 <  value2) result = -1;
   if (value1 >  value2) result = 1;
   // default if (value1 == value2) result = 0;
   return result;
}
//______________________________________________________________________________
int CORN_compare_int(int value1, int value2)
{  int result = 0;
   if (value1 <  value2) result = -1;
   if (value1 >  value2) result = 1;
   // default if (value1 == value2) result = 0;
   return result;
}
//______________________________________________________________________________
#ifdef OBSOLETE
//100326  For C now just using macros in C++ I use template in compare.hpp
float64 min_f64(float64 x, float64 y)  {  return ((x < y) ? x : y);  };
float64 max_f64(float64 x, float64 y)  {  return ((x > y) ? x : y);  };
float32 min_f32(float32 x, float32 y)  {  return ((x < y) ? x : y);  };
float32 max_f32(float32 x, float32 y)  {  return ((x > y) ? x : y);  };
int8 min_i8(int8 x, int8 y)            {  return ((x < y) ? x : y);  };
int8 max_i8(int8 x, int8 y)            {  return ((x > y) ? x : y);  };
int16 min_i16(int16 x, int16 y)        {  return ((x < y) ? x : y);  };
int16 max_i16(int16 x, int16 y)        {  return ((x > y) ? x : y);  };
int32 min_i32(int32 x, int32 y)        {  return ((x < y) ? x : y);  };
int32 max_i32(int32 x, int32 y)        {  return ((x > y) ? x : y);  };
uint32 min_uint32(uint32 x, uint32 y)  {  return ((x < y) ? x : y);  };
uint32 max_uint32(uint32 x, uint32 y)  {  return ((x > y) ? x : y);  };
#endif
//______________________________________________________________________________
