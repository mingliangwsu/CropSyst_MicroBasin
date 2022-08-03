#include "corn/math/moremath.hpp"
//_____________________________________________________________________________
float64 CORN_clean_precision(float32 x,float64 precision_fract)
{
//   _fpreset();
   float64 result = x;
   if (x > 0)
      result += precision_fract/100.0;  /* Round up a bit */
   else
      result -= precision_fract/100.0;  /* Round down a bit */
   result /= precision_fract;
   long big_trunc = (long)result ;
   result = big_trunc * precision_fract;
   return result;
}
//_____________________________________________________________________________
float64 CORN_round_double(float64 number, int precision_digits)
{
   float64 result = number / pow(10.0,precision_digits);
   result = ((float64)(result - ((int)result))) >= 0.5 ? (int) result + 1: (int) result;
   return (result /  pow(10.0,-precision_digits));
};
//_____________________________________________________________________________
float64 CORN_truncate_double(float64 number, int precision_digits)
{
   float64 result = number * pow(10.0,precision_digits);
   result = (float64)((int)result);
   return (result *  pow(10.0,-precision_digits));
};
//_____________________________________________________________________________
