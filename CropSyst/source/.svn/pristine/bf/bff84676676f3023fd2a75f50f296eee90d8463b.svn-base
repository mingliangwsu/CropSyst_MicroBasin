#ifndef soil_param_V4H
#define soil_param_V4H
#include "soil/soil_param_class.h"
#include "corn/validate/validtyp.h"
//______________________________________________________________________________
class Soil_parameters
: public version4::Soil_parameters_class
{
 public:
   Valid_int16    v_override_curve_number; // runoff curve number (for models without hydro cond/group)
   Valid_int16    v_user_fallow_curve_number; // runoff curve number override for fallow
   Valid_float32  v_surface_storage_mm; // finite difference runoff
   Valid_float32  v_steepness;
   Valid_float32  v_slope_length;      // m
   Valid_float32  v_albedo_dry;
   Valid_float32  v_albedo_wet;
   Valid_float32  v_water_vapor_conductance_atmosphere_adj;
#if (CROPSYST_VERSION == 3)
   Valid_float32  v_leaching_depth; //m
#endif
   Valid_float32  v_SLPF_CropGro;

#if (CROPSYST_VERSION == 3)
   bool         override_leaching_depth;
   float32      leaching_depth_32;  // m This is used for selecting leaching horizon
#endif
   float32  old_pH_32; // We now store pH by horizon
   float32  old_cation_exchange_capacity_32; // (meq/100g) For ammonium volitalization
 public:
   Soil_parameters();
   virtual ~Soil_parameters();
   virtual bool expect_structure(bool for_write = false);                        //981103
   virtual bool set_start();                                                     //161023_010109
   virtual bool get_end();                                                       //161023_010109
#if (CROPSYST_VERSION == 3)
   inline virtual float64 get_leaching_depth()                             const
      { return (float64)leaching_depth_32; }  // This does not need to be 32bit clean  //981231X
#endif
};
//______________________________________________________________________________
#endif
