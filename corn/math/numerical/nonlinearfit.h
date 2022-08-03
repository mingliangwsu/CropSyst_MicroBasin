#ifndef nonlinearfitH
#define nonlinearfitH
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
//140311 #include <corn/no_ns.h>
#include "corn/dynamic_array/dynamic_array_T.h"
#define Dynamic_float_array Dynamic_array<float32>

namespace CORN {
//forward decl

/*
      To use these classes:

      Derive a class from this Non_linear_curve_fitter_2 class.
      You must override function f().
      (Usually I just have the function f()
      call the actual function that is to be fit.)

      Create an instance of the derived class.

      There are two options to charge the curve with actual data:

      Static curve mode.

         In this case the curve fitter does not maintain the curve,
         it only references the dynamic arrays defining the curve.
         The two dynamic arrays should have the same number
         of items (one x for every y) if this is not the case,
         the minumum count of the array size will be used.

         You can use the append_point() function to add points
         to the curve but make sure that you want to do this because
         the X and Y arrays will be modified accordingly.

      Dynamic curve mode.

         In this case the curve fitter maintains the curve
         and will delete the curves when it goes out of scope.

         When using this mode, you can control
         the the allocation of the point arrays by
         specifying the initial array size and
         the number of points to be reallocated
         when an additional point is added exceeding
         the current array size. (As with dynamic array)

         You charge/populate the curve dataset by calling
         append_point(x,y) for each pair of points on the curve.

      You must use one or the other curve definition mode options.

      Once the curve has been set,
      call the function fit() passing the initial (default) values
      of a and b parameters to fit.
      The fitted values are returned in the next two arguments.
      The fit function returns true if the curve fit was successful
      (which will usually be the case.)

*/
//_____________________________________________________________________________
class Non_linear_curve_fitter
{
protected:
   Dynamic_float_array  *local_X;  // Used in the case of
   Dynamic_float_array  *local_Y;  // dynamic curve mode.
   Dynamic_float_array  &X;
   Dynamic_float_array  &Y;
protected: // Optional adjustments
   nat16   max_iterations;
   float32  error_tolerance;
public:
   // Dynamic curve mode constructuor
   Non_linear_curve_fitter
      (nat32  initial_size   = 100
      ,nat32  resize_overage = 30);
   // Use this constructor if this object is to maintain its own curve arrays.
   // Static curve mode constructor
   Non_linear_curve_fitter
      (Dynamic_float_array &X_array
      ,Dynamic_float_array &Y_array);
   // Use this constructor if this object is to use existing curve arrays.
   virtual ~Non_linear_curve_fitter();
   bool append_point(float32 x, float32 y);
   // Returns true if the point was added to the data set.
};
//______________________________________________________________________________
class Non_linear_curve_fitter_1
: public Non_linear_curve_fitter
{
   /* This class implments non linear curve fitting
      for an equation of 2 parameters.
   */
public:
   // Dynamic curve mode constructuor
   Non_linear_curve_fitter_1
   (nat32  initial_size   = 100
   ,nat32  resize_overage = 30);
   // Use this constructor if this object is to maintain its own curve arrays.

   // Static curve mode constructor
   Non_linear_curve_fitter_1
   (Dynamic_float_array &X_array
   ,Dynamic_float_array &Y_array);
   // Use this constructor if this object is to use existing curve arrays.

   virtual float32 f(float32 x, float32 b ) = 0;
   // This function must be overridden in the derived class.
   // It is a function of x (the independent variable)
   // giving y the dependent variable
   // with parameters a and b which where are trying to fit.

   bool fit(float32 initial_b
           ,float32 &fitted_b);

};
 //_____________________________________________________________________________
class  Non_linear_curve_fitter_2
: public Non_linear_curve_fitter
{
   /* This class implements non linear curve fitting
      for an equation of 2 parameters.
   */
public:
   // Dynamic curve mode constructuor
   Non_linear_curve_fitter_2
   (nat32  initial_size   = 100
   ,nat32  resize_overage = 30);
   // Use this constructor if this object is to maintain its own curve arrays.
   // Static curve mode constructor
   Non_linear_curve_fitter_2
      (Dynamic_float_array &X_array
      ,Dynamic_float_array &Y_array);
   // Use this constructor if this object is to use existing curve arrays.
   virtual float32 f(float32 x, float32 a, float32 b ) = 0;
      // This function must be overridden in the derived class.
      // It is a function of x (the independent variable)
      // giving y the dependent variable
      // with parameters a and b which where are trying to fit.
   bool fit(float32 initial_a, float32 initial_b
           ,float32 &fitted_a,  float32 &fitted_b);
public: // Optional adjustments
   inline void set_max_iterations(nat16 _max_iterations)             assignation_{ max_iterations = _max_iterations;}
   inline void set_error_tolerance(float32 _error_tolerance)         assignation_{error_tolerance = _error_tolerance; }
};
//_____________________________________________________________________________
} // namespace CORN;

#endif
//nonlinearfit.h

