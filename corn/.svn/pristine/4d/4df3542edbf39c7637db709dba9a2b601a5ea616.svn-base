#ifndef distribution_WeibullH
#define distribution_WeibullH
#include "corn/math/statistical/sample_dataset_T.h"
namespace CORN {
//______________________________________________________________________________
// http://en.wikipedia.org/wiki/Weibull_distribution
class Distribution_Weibull
{
   const Statistical_sample_cowl_dataset<float64,float64,float64> &statistical_dataset;
 public:
   inline Distribution_Weibull(const Statistical_sample_cowl_dataset<float64,float64,float64> &_statistical_dataset)
      : statistical_dataset(_statistical_dataset)
      {}
   void get_shape_scale(float64 &alpha_shape, float64 &beta_scale)         const;
   inline void get_alpha_beta(float64 &alpha_shape, float64 &beta_scale)   const { get_shape_scale(alpha_shape,beta_scale); }

 public:
   /* NYI
   probability_density_function(x)
   cumulative_distribution_function(x)
   calc_mean
   calc_median
   calc_mode
   calc_variance
   calc_skewness
   calc_kurtosis
   calc_entropy
   calc_moment_generating_function
   calc_characteristic_function
   calc_quantile(probability?(0 to 1)

   */
 private:
   float64 bisection_method(float64 alpha_initial)                         const;
   float64 f(float64 alpha)                                                const;
};
//_2013-08-01___________________________________________________________________
};
#endif
