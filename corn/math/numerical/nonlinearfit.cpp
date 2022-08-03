#include <math.h>
#include "corn/math/compare.hpp"
#include "corn/math/numerical/nonlinearfit.h"
namespace CORN
{
Non_linear_curve_fitter::Non_linear_curve_fitter
(nat32  initial_size
,nat32  resize_overage)
: local_X(new Dynamic_float_array(initial_size,resize_overage,0.0))
, local_Y(new Dynamic_float_array(initial_size,resize_overage,0.0))
, X(*local_X)
, Y(*local_Y)
, max_iterations(100)
, error_tolerance(0.00001)
{}
//______________________________________________________________________________
Non_linear_curve_fitter::Non_linear_curve_fitter
(Dynamic_float_array &X_array
,Dynamic_float_array &Y_array)
: local_X(0)
, local_Y(0)
, X(X_array)
, Y(Y_array)
, max_iterations(100)
, error_tolerance(0.00001)
{}
//______________________________________________________________________________
Non_linear_curve_fitter_1::Non_linear_curve_fitter_1
(nat32  initial_size
,nat32  resize_overage)
: Non_linear_curve_fitter(initial_size,resize_overage)
{}
//______________________________________________________________________________
Non_linear_curve_fitter_1::Non_linear_curve_fitter_1
(Dynamic_float_array &X_array
,Dynamic_float_array &Y_array)
: Non_linear_curve_fitter(X_array,Y_array)
{}
//______________________________________________________________________________
Non_linear_curve_fitter_2::Non_linear_curve_fitter_2
(nat32  initial_size
,nat32  resize_overage)
: Non_linear_curve_fitter(initial_size,resize_overage)
{}
//______________________________________________________________________________
Non_linear_curve_fitter_2::Non_linear_curve_fitter_2
(Dynamic_float_array &X_array
,Dynamic_float_array &Y_array)
: Non_linear_curve_fitter(X_array,Y_array)
{}
//______________________________________________________________________________
Non_linear_curve_fitter::~Non_linear_curve_fitter()
{  if (local_X) delete local_X;
   if (local_Y) delete local_Y;
}
//______________________________________________________________________________
bool Non_linear_curve_fitter::append_point(float32 x, float32 y)
{  return (x == X.append(x)) &&
          (y == Y.append(y));
}
//______________________________________________________________________________
bool Non_linear_curve_fitter_1::fit
(float32 initial_b
,float32 &fitted_b)
{  float32 b = initial_b;
   nat32 count = std::min<nat32>(X.get_count(),Y.get_count());
   int i = 0;
   float32 error = 1.0;
   bool converged = false;
   bool maxed_iterations = false;
   do  // Begin iterations
   {  float32 S3 = 0.0;
      float32 S5 = 0.0;
      for (nat32 j = 0; j < count; j++)
      {  float32 x = X.get(j);
         float32 y = f(x,b);
         float32 YD = Y.get(j) - y;
         b *= 1.02;
         y = f(x,b);
         float32 YU = y;
         b *= 0.98 / 1.02;
         y = f(x,b);
         b /= 0.98;
         float32 PB = (YU - y) / (0.04 * b);
         S3 += PB * PB;
         S5 += PB * YD;
      }
      if (!CORN::is_approximately<float32>(S3,0.0,0.000001)) // avoid div 0 error
      {  float32 SB = S5 / S3;
         error = fabs(SB / b);
         b += SB;
      }
      i += 1;
      maxed_iterations = i > max_iterations;
      converged =  error < error_tolerance;
   } while (!maxed_iterations && !converged);
   fitted_b = b;
   return converged;
}
//______________________________________________________________________________
bool Non_linear_curve_fitter_2::fit
(float32 initial_a, float32 initial_b
,float32 &fitted_a, float32 &fitted_b)
{  float32 a = initial_a;
   float32 b = initial_b;
   nat32 count = std::min<float32>(X.get_count(),Y.get_count());
   int i = 0;
   float32 error = 1.0;
   bool converged = false;
   bool maxed_iterations = false;
   do
   {  float32 S1 = 0.0;
      float32 S2 = 0.0;
      float32 S3 = 0.0;
      float32 S4 = 0.0;
      float32 S5 = 0.0;
      float32 S6 = 0.0;
      float32 T1 = 0.0;
      for (nat32 j = 0; j < count; j++)
      {  float32 x = X.get(j);
         float32 y = f(x,a,b);
         float32 YD = Y.get(j) - y;
         float32 T5 = YD;
         T1 += fabs(T5);
         // Try new value of a
         a *= 1.02;
         y = f(x,a,b);
         float32 YU = y;
         a *= 0.98 / 1.02;
         y = f(x,a,b);
         a /= 0.98;
         float32 PA = (YU - y) / (0.04 * a); // Warning potential div0 error
         // Try new value of b
         b *= 1.02;
         y = f(x,a,b);
         YU = y;
         b *= 0.98 / 1.02;
         y = f(x,a,b);
         b /= 0.98;
         float32 PB = (YU - y) / (0.04 * b);
         //unused T3 = 1.0;
         S1 += PA * PA;
         S2 += PA * PB;
         S3 += PB * PB;
         S4 += PA * YD;
         S5 += PB * YD;
         S6 += YD * YD;
      }
      //unused T2 = 6.0 * T1 / count;
      float32 S7 = S1 * S3 - S2 * S2;
      if (!CORN::is_approximately<float32>(S7,0.0,0.000001)) // avoid div 0 error
      {  float32 SA = (S3 * S4 - S2 * S5) / S7;
         float32 SB = (S1 * S5 - S2 * S4) / S7;
         error = fabs (SA /a) + fabs(SB / b);
         a += SA;
         b += SB;
      }
      i += 1;
      maxed_iterations = i > max_iterations;
      converged =  error < error_tolerance;
   } while (!maxed_iterations && !converged);
   fitted_a = a;
   fitted_b = b;
   return converged;
}
//______________________________________________________________________________
} // namespace CORN;

