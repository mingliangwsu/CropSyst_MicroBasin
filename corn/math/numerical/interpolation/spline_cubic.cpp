#include "corn/math/numerical/interpolation/spline_cubic.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#include <math.h>
#include <limits>
#include <assert.h>

namespace CORN
{
//____________________________________________________________
Interpolation_spline_cubic::Spline::Spline
(float32 x_
,float32 y_
,float32 x_next_
,float32 y_next_)
: CORN::Item()
, x                                                                    (x_)
, x_next                                                               (x_next_)
, y                                                                    (y_)
, y_next                                                               (y_next_)
, h                                                               (x_next_ - x_)
, slope                                                                    (0.0)
, curvature                                                                (0.0)
, A                                                                        (1.0)
, B                                                                        (1.0)
, C                                                                        (1.0)
, D                                                                        (1.0)
{
   slope = (y_next_ - y_) / h;
}
//_____________________________________________________________________________)
float32 Interpolation_spline_cubic::Spline::calc_y(float32 x_)              const
{
   float32 y_
     = A * pow(double(x_ - x),3.0)
     + B * pow(double(x_ - x),2.0)
     + C *           (x_ - x)
     + D;
   return y_;
}
//_____________________________________________________________________________)
float64 determinate_value_order_2(float32 **determinant)
{
   return determinant[0][0] * determinant[1][1]
        - determinant[1][0] * determinant[0][1];
}
//_____________________________________________________________________________)
// http://www.tau.ac.il/~tsirel/dump/Static/knowino.org/wiki/Determinant_(mathematics).html
// https://www.khanacademy.org/math/linear-algebra/matrix-transformations/inverse-of-matrices/v/linear-algebra-nxn-determinant

float64 determinant_value_order_N(float32 **major, nat16 order)
{
   float32 value = 0;

   nat16 minor_order = order - 1;
   bool subtract = false;
   for (nat16 i = 0; i < order; i++)
   {

      float32 coef_0i = major[0][i];
      float32 **minor = new float32 *[minor_order];
      for (nat16 minor_r = 0; minor_r < minor_order; minor_r++) //for each row row
      {
         minor[minor_r] = new float32 [minor_order]; // square matrix column
      }

      nat16 minor_r = 0; nat16 minor_c = 0;
      for (nat16 major_r = 1; major_r < order ; major_r++)
      {

//         if (major_r != i)
         {
            nat16 minor_c = 0;
            for (nat16 major_c = 0; major_c < order ; major_c++)
            {

               if (major_c != i)
               {
                  minor[minor_r][minor_c] = major[major_r][major_c];
                  minor_c++;
               } // else column is eliminated
            }
            minor_r ++;
         } // else row is eliminated
      }
      float32 minor_value
         = (minor_order == 2)
         ? determinate_value_order_2(minor)
         : determinant_value_order_N(minor,minor_order);

      if (subtract) value -= coef_0i * minor_value;
      else          value += coef_0i * minor_value;
      subtract = !subtract;
   }
   return value;
}
//_____________________________________________________________________________/
/*      wrong
float64 determinant_value(float32 **determinant, nat16 order)
{
   Dynamic_array<float32> augends(order);
   Dynamic_array<float32> subtrahends(order);
   float32 *product_diag = new float32[order];
   for (nat16 m = 0 ; m < order; m++)
      product_diag[m] = 1.0;

   for (nat16 m = 0 ; m < order; m++)
   {
      nat16 r = m;
      for (nat16 d = 0; d < order; d++) // diagonal index
      {
         nat16 n = m + d;
         nat8 c = n >= order ? n - order : n;
         product_diag[d] *= determinant[r][c];
      }
      augends.append(product_diag[m]);
   }
   float32 augends_sum = augends.sum();

   for (nat16 m = 0 ; m < order; m++)
      product_diag[m] = 1.0;

   for (int16 m = order-1; m > 0; m--)
   {
      nat16 r = m;
      for (nat16 d = 0; d < order; d++)
      {
         nat16 n = m + d;
         nat8 c = n >= order ? n - order : n;
         product_diag[d] *= determinant[r][c];
      }
      subtrahends.append(product_diag[m]);
   }
   float32 subtrahends_sum = subtrahends.sum();
   float32 value = augends_sum - subtrahends_sum;
      // = augends.sum() - subtrahends.sum();
   return value;
}
//_____________________________________________________________________________/
*/

bool Interpolation_spline_cubic::initialize()                    initialization_
{
   Coordinate *prev_obs = 0; // observation

   FOR_EACH_IN(obs,Coordinate,observations,each_obs)
   {
      if (prev_obs)
      {
         splines.append(new Spline
            (prev_obs->get_abscissa(),prev_obs->get_ordinate()
            ,     obs->get_abscissa(),     obs->get_ordinate()));


      }
      prev_obs = obs;
   } FOR_EACH_END(each_obs)

   // build tridiagonal system of equations
   nat16 observation_count_less_2 =  observations.count() -2;

   float32 *S_diff_6 = new float32 [observation_count_less_2];
   float32 *R = new float32 [observation_count_less_2];
   float32 **A /*_determinant*/ = new float32 *[observation_count_less_2]; // exluding the first and last splines
   for (nat16 r = 0; r < observation_count_less_2; r++)
   {
      S_diff_6[r] = 0;
      R[r] = 0;
      A[r] = new float32 [observation_count_less_2];
      for (nat16 c = 0; c < observation_count_less_2; c++)
         A[r][c] = 0;
   }

   // populate A
   int16 a = 0; //

   Spline *prev_spline = 0;
   nat16 prev_h = 1; // This is only for testing
   nat16 curr_h = 2; // This is only for testing
   FOR_EACH_IN(curr_spline,Spline,splines,each_spline)
   {
      if (prev_spline && a < observation_count_less_2 )
      {
         A[a][a] = 2.0 * (prev_spline->h + curr_spline->h);
         if (a < observation_count_less_2-1)
         {
         A[a+1][a] = prev_spline->h;
         A[a][a+1] = prev_spline->h;
         }
         prev_h++; curr_h++; // just for testing

         S_diff_6[a] = 6.0 * (curr_spline->slope - prev_spline->slope);
         // I don't know what 6.0 is but it appears to be constant.
         a++;
      }
      prev_spline = curr_spline;

   //NYI if (clamped) add 1's to h matrix ??

   } FOR_EACH_END(each_spline)

   // Now apply Cramers rule

   // Get determinate of A

   float32 A_value = determinant_value_order_N(A,observation_count_less_2);

   for (nat8 r = 0; r < observation_count_less_2; r++)
   {

      float32 **R_det = new float32 *[observation_count_less_2]; // exluding the first and last splines
      for (nat16 i = 0; i < observation_count_less_2; i++)
      {
         R_det[i] = new float32 [observation_count_less_2];
         for (nat16 j = 0; j < observation_count_less_2; j++)
            R_det[i][j] = A[i][j];

         R_det[i][r] = S_diff_6[i];
      }

      float32 R_value=determinant_value_order_N(R_det,observation_count_less_2);
      R[r+1] = R_value / A_value;

      for (nat16 i = 0; i < observation_count_less_2; i++)
         delete[] R_det[i];

      // NYI delete R_det
   }
   nat16 i = 0;  // this would be k-1 in the original algorithm
   FOR_EACH_IN(spline,Spline,splines,each_spline)
   {
      spline->A = 1.0/(6.0 * spline->h) * (R[i+1] - R[i]);
      spline->B = 1.0/2.0 * R[i];
      spline->C = 1.0/spline->h * (spline->y_next - spline->y)
                 -1.0/6.0 * spline->h * (R[i+1] + 2.0 * R[i]);
      spline->D = spline->y;
      i++;
   } FOR_EACH_END(each_spline)

   // see FORTRAN 7 with numerical methods for engineers and scientists pg 357


   for (nat16 i = 0; i < observation_count_less_2; i++)
      delete[] A[i];
   // crashing delete[] A;
   delete[] S_diff_6;
   delete[] R;

   initialized = true;

   return true;
}
//____________________________________________________________
float32 Interpolation_spline_cubic::get_ordinate
(float32 abscissa
,bool extrapolate_terminal)                                      const//  contribution_
{  float32 y = std::numeric_limits<float32>::quiet_NaN();  // or NAN
   float32 x = abscissa;

      // This is just temporary the Interpolator should have an initialize
      // method which calls the interpolation initialize
      // The user of the Intepolator would call initialize once a
      // all the observations has been loaded. I need to check all current uses

   const Spline *first_spline = dynamic_cast<const Spline *>(splines.get_at(0));
   if (!first_spline) return y; // NaN because no splines (probably because no observed data)
   if (x < first_spline->x)
      return first_spline->x;
      // May want to have an option to return NaN if x is outside obsrvations

   FIND_FOR_EACH_IN(found_spline,spline,Spline,splines,true,each_spline)
   {
      if ((x >= spline->x) && (x <= spline->x_next))
         found_spline = spline;
   } FOR_EACH_END(each_spline)
   if (found_spline)
   {
      y = found_spline->calc_y(x);
      /*moved
        found_spline->A * pow(double(x - found_spline->x),3.0)
        + found_spline->B * pow(double(x - found_spline->x),2.0)
        + found_spline->C *    (x - found_spline->x)
        + found_spline->D;
      */
   }
   // else error abscissa is outside the observations,
   // or the x_high value of the last spline if exceeds
   return y;
}
//____________________________________________________________
} // namespace CORN
