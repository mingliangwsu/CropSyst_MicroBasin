#ifndef SOLVER_H
#define SOLVER_H
#ifndef primitiveH
#  include <corn/primitive.h>
#endif

namespace CORN {
//______________________________________________________________________________
class Solver
{
protected:
   mutable bool solved;
public:
   inline Solver()
      : solved(false)
      {}
   virtual float64 f(float64 x)                                            const = 0;
   // F(x) is the function to solve
public:
   virtual float64 solve
      (float64 y
      , float64 min_x, float64 max_x
      , float64 precision = 0.000001
      , uint16 iterations = 32768)                                         const = 0;
   // returns a value of x such that y = f(x).
protected:
   inline float64 general_form_f(float64 y, float64 x )                    const
      { return f(x) -y; }
};
//______________________________________________________________________________
class Solver_bisection_method
: public Solver
{public:
   inline Solver_bisection_method()
   : Solver()
   {};
 public:
   virtual float64 solve
      (float64 y
      , float64 min_x, float64 max_x
      , float64 precision = 0.00001
      , uint16 iterations = 32768)                                         const;
};

//      Bisection method  (Simplest, assumes that you know the target range (min X and max X).  Gain about 1 decimal digit of accuracy each 3 iterations.)
// NYI  False-position  (Not as efficient as bisection. Slower than secant, but converges substatially faster and convergence is assured)
// NYI  Secant method   (Works best when already close to the solution. In certain conditions can perform worse than B.S. and fail to converge. When close to the root, can double the number of digits of accuracy every two interations).
// NYI  Newton-Raphson  (Efficient, converges rapidly, but need the function's derivative, unstable if starting far from the root )

// Could start with bisection method then
// get greater precision (refine) with one of the others
//______________________________________________________________________________
} // namespace CORN;
#endif
// solver.h

