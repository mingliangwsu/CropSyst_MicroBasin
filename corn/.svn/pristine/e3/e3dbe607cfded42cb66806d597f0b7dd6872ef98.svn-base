#include <math.h>
#include "corn/math/numerical/interpolate_2d_3d.h"
#include "corn/math/moremath.h"

/* Shepards method

http://www.ems-i.com/gmshelp/interpolation/interpolation_schemes/inverse_distance_weighted/shepards_method.htm

*/
namespace CORN
{
//______________________________________________________________________________
Inverse_distance_weighted_interpolator::Inverse_distance_weighted_interpolator
(Method _method, float64 _power_parameter)
: method(_method)
, power_parameter(_power_parameter)
,target_point(0)
{ }
//______________________________________________________________________________
float64 Inverse_distance_weighted_interpolator::interpolate()              const
{  float64 sum_wi_fi = 0;
   int i = 0;
   FOR_EACH_IN(point,Weighted_point,points,each_point)
   {  if (point->valid)
      {  float64 fi = calc_prescribed_function(i);
         float64 wi = point->weight;
         sum_wi_fi += wi * fi;
      }
      i++;
   }  FOR_EACH_END(each_point)
   return sum_wi_fi;
}
//______________________________________________________________________________
void Inverse_distance_weighted_interpolator::set_point_valid(uint32 index, bool valid)
{  Weighted_point *point = (Weighted_point *)points.get_at(index);
   if (point) point->valid = valid;
}
//______________________________________________________________________________
void  Inverse_distance_weighted_interpolator::calc_weights_shepard_form()
{  float64 sum_h_P = 0;
   FOR_EACH_IN(point,Weighted_point,points,each_point)
   {  if (point->valid)
      {  point->update_distance_to(*target_point); //point->update_distance_to(target_x,target_y,target_z);
         float64 distance_to_target = point->distance_to_target;
         sum_h_P += pow(distance_to_target,-power_parameter);
      }
   }  FOR_EACH_END(each_point)
   float64 weight_sum = 0; // This is just a check (should add to 1 - I think)
   FOR_EACH_IN(point,Weighted_point,points,each_point)
   {  if (point->valid)
      {  point->update_distance_to(*target_point); //point->update_distance_to(target_x,target_y,target_z);
         float64 distance_to_target = point->distance_to_target;
         float64 hi_P = pow(distance_to_target,-power_parameter);
         float64 wi =  hi_P/sum_h_P;
         point->weight = wi;
         weight_sum += wi; // only for debugging
      }
      else point->weight = 0.0;
   }  FOR_EACH_END(each_point)
//clog << weight_sum << endl; // debugging
}
//______________________________________________________________________________
#ifdef NYI
void  Inverse_distance_weighted_interpolator::calc_weights_frank_and_nielson_form(float64 target_x
   ,float64 target_y
   ,float64 target_z)
{  FOR_EACH_IN(point,Weighted_point,points,each_point)
   {  point->update_distance_to(target_x,target_y,target_z)
   }  FOR_EACH_END(each_point)
   float64 furthest_distance = 0.0;
   FOR_EACH_IN(point,Weighted_point,points,each_point)
   {  furthest_distance = std::max<xxxx>(furthest_distance,point->distance_to_target);
   }  FOR_EACH_END(each_point)
   FOR_EACH_IN(point,Weighted_point,points,each_point)
   {
               continue here...
      point->distance_to_target

      float64 wi =  numerator/denominator;
      point_weight = wi;
   }  FOR_EACH_END(each_point)

}
#endif
//______________________________________________________________________________
Cartesian_inverse_distance_weighted_interpolator::Cartesian_inverse_distance_weighted_interpolator
   (Method _method, float64 _power_parameter )
: Inverse_distance_weighted_interpolator(_method,  _power_parameter)
{}
//______________________________________________________________________________
void Cartesian_inverse_distance_weighted_interpolator::set_target
(float64 _target_x,float64 _target_y,float64 _target_z)
{  if (target_point) delete target_point;
   target_point = new  Weighted_point(_target_x,_target_y,_target_z);
}
//______________________________________________________________________________
void Cartesian_inverse_distance_weighted_interpolator::append_point(float64 x, float64 y, float64 z)
{  Weighted_point *point=new Weighted_point(x,y,z);
   points.append(point);
}
//______________________________________________________________________________
void Cartesian_inverse_distance_weighted_interpolator::Weighted_point::update_distance_to (Inverse_distance_weighted_interpolator::Weighted_point &target_point)
{  Cartesian_inverse_distance_weighted_interpolator::Weighted_point &cartesian_target_point =  (Cartesian_inverse_distance_weighted_interpolator::Weighted_point &)target_point;
   distance_to_target = sqrt(CORN_sqr(cartesian_target_point.x /*target_x*/ - x) + CORN_sqr(cartesian_target_point.y /*target_y*/ - y) + CORN_sqr(cartesian_target_point.z /*target_z*/ -z));
}
//______________________________________________________________________________
} // namespace CORN
