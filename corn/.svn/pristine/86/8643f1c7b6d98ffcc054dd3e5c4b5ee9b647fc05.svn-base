#include "corn/math/statistical/distribution_Weibull.h"

// Weibull related functions,
// I alpha is a unitless shape parameter and beta is the scale
// parameter (same units as the generated value) 070403_
namespace CORN {
//______________________________________________________________________________
float64 Distribution_Weibull::bisection_method(float64 alpha_initial)      const
{  float64 alpha_mid = alpha_initial;
   float64 alpha_upper = alpha_mid * 1.05;
   float64 alpha_lower = alpha_mid * 0.95;
   float64 f_low;
   float64 f_high;
   do
   {  alpha_upper = alpha_upper * 1.05;
      alpha_lower = alpha_lower * 0.95;
       f_low = f(alpha_lower);
       f_high = f(alpha_upper);
   } while ((f_low *f_high > 0.0));//(sign(f_low) == sign(f_high));
   bool negative_end_is_alpha_lower = (f_low < 0);
   int iterations = 0; // to avoid pathologic cases
   bool found = false;
   float64   negative_end =  (negative_end_is_alpha_lower)
      ? alpha_lower
      : alpha_upper;
    float64  positive_end =  (negative_end_is_alpha_lower)
      ? alpha_upper
      : alpha_lower;
   do
   {  alpha_mid = (negative_end + positive_end)/2;
      float64 f_mid = f(alpha_mid);
      if (f_mid <= 0)   negative_end = alpha_mid;
      else              positive_end = alpha_mid;
      if (CORN::is_approximately<float64>(f_mid,0.0,0.001))
         found = true;
      iterations++;
   } while(!found && (iterations <= 100));
   return alpha_mid;
}
//_1998-03-18___________________________________________________________________
float64 Distribution_Weibull::f(float64 alpha)                             const
{  nat32 n = statistical_dataset.get_count();
   float64 sum_q = 0;
   float64 sum_r = 0;
   float64 sum_s = 0;
   for (nat32 i = 0; i < n; i++)
   {  float64 x_i = statistical_dataset.get(i);
      float64 ln_x_i = (x_i > 0) ?  CORN_ln(x_i) :  0.0;                         //030616
      float64 x_i_alpha  = pow(x_i,(float64)alpha);
      sum_q += ln_x_i;
      sum_r += x_i_alpha * ln_x_i;
      sum_s += x_i_alpha;
   }
   return
   (CORN::is_approximately<float64>(alpha,0.0,0.000001) ||                       //980404
    CORN::is_approximately<float64>(sum_s,0.0,0.000001))                         //980404
   ? 0.0                                                                         //980404
   : n / alpha + sum_q - (n * sum_r / sum_s);
}
//_1998-03-18___________________________________________________________________
void Distribution_Weibull::get_shape_scale
(float64 &alpha_shape,  float64 &beta_scale)                               const
{  // First approximation of alpha:
   //I think this is called Maximum Likelihood parameterization method - RLN
   //see http://www.brighton-webs.co.uk/distributions/weibull2.htm
   //
   float64 stddev_ = statistical_dataset.get_standard_deviation();                                   //060118
   float64 mean_   = statistical_dataset.get_mean();                                                 //060118
   if ( CORN::is_approximately<float64>(mean_,0.0,0.0000001 )                    //061217
      ||CORN::is_approximately<float64>(stddev_,0.0,0.0001 ))                    //061217
   {  alpha_shape = 0.0;                                                         //061217
      beta_scale = 0.0;                                                          //061217
      // When Alpha is 0 (I.e. because StDev is 0, Beta cannot be computed either).
      return;                                                                    //061217
   };
   alpha_shape = mean_/stddev_;
   nat32 n = statistical_dataset.get_count();
   alpha_shape = bisection_method(alpha_shape);
   float64 sum_x_pow_alpha = 0;
   for (nat32 i = 0; i < n; i++)  // for each item in the dataset
      sum_x_pow_alpha += pow((float64)statistical_dataset.get(i),(float64)alpha_shape);
   float64 beta64 =  //  avoid div by 0
      (CORN::is_approximately<float64>(alpha_shape,0.0,0.000001) ||              //980404
       CORN::is_approximately<float64>( n,0.0,0.000001))                         //980404
   ? 0.0                                                                         //980404
   : pow(sum_x_pow_alpha / n, (float64)(1.0 / alpha_shape));                     //051025
   beta_scale = beta64;
}
//_1998-03-18___________________________________________________________________
} //namespace CORN


