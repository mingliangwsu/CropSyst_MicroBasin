#ifndef interpolate_2D_3DH
#define interpolate_2D_3DH

#include <corn/container/unilist.h>
namespace CORN
{
//______________________________________________________________________________
class Inverse_distance_weighted_interpolator
{
public:
   enum Method
   {shepards_method
   ,frank_and_nielson
//NYI , gradient_plane_nodal_function_method
//NYI , quadratic_nodal_function_method
   };

   class Weighted_point    // abstract
   : public CORN::Item
   { public:
      float64 weight;
      float64 distance_to_target;
      bool     valid;   // This is special case for UED_database_interpolator where some daily values inthe data set may not be available  in other databases being interpolated
   public:
      inline Weighted_point()
         : CORN::Item()
         , weight(0.0)               // will be calculated later
         , distance_to_target(0.0)   // will be calculated later
         , valid(true)
         {}
      virtual void update_distance_to(Inverse_distance_weighted_interpolator::Weighted_point &target_point) = 0;
   };
   //___________________________________________________________________________
private:
   Method method;
   float64 power_parameter; // typically 2
protected : //
   Unidirectional_list  points;
   Weighted_point       *target_point;
public:
   Inverse_distance_weighted_interpolator
      (Method _method = shepards_method, float64 _power_parameter = 2);

   inline virtual    ~Inverse_distance_weighted_interpolator()
      { if (target_point) delete target_point;  target_point =0 ; }

   void  calc_weights_shepard_form();
      // This is called after all the points have been added.
   virtual float64 calc_prescribed_function(uint32 index) const = 0;
      // Derived classes should override calc_prescribed_function
   float64 interpolate() const;
      // Z coordinate is optional for 3D mode
   void set_point_valid(uint32 index, bool valid);
};
//______________________________________________________________________________
class Cartesian_inverse_distance_weighted_interpolator
: public Inverse_distance_weighted_interpolator
{
private:
   class Weighted_point
   : public Inverse_distance_weighted_interpolator::Weighted_point
   {public:
      float64 x;
      float64 y;
      float64 z;
    public:
      inline Weighted_point(float64 _x, float64 _y, float64 _z = 0)
      : Inverse_distance_weighted_interpolator::Weighted_point()
      , x(_x)
      , y(_y)
      , z(_z)
      {}
      virtual void update_distance_to(Inverse_distance_weighted_interpolator::Weighted_point &target_point); // float64 target_x, float64 target_y, float64 target_z);
    private:
      //180813 NYN inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format

   };
public:
   Cartesian_inverse_distance_weighted_interpolator
      (Method _method = shepards_method, float64 _power_parameter = 2);
   void  append_point(float64 x, float64 y, float64 z = 0);
   void set_target
      (float64 target_x
      ,float64 target_y
      ,float64 target_z = 0);
};
//______________________________________________________________________________
} // namespace CORN
#endif

