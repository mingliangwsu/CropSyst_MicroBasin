#ifndef soil_param_V5H
#define soil_param_V5H
#include "CropSyst/source/soil/soil_param_class.h"
#define soil_horizon_parameter_array(x)            CORN::Parameter_number *x[MAX_soil_horizons_alloc]
//______________________________________________________________________________
#define Soil_parameters_class_parent version5::Soil_parameters_class

class Soil_parameters
: public Soil_parameters_class_parent                                        //160915
{
public:
   CORN::Parameter_number p_override_curve_number; // runoff curve number (for models without hydro cond/group)
   CORN::Parameter_number p_user_fallow_curve_number; // runoff curve number override for fallow
   CORN::Parameter_number p_surface_storage_mm; // finite difference runoff
   CORN::Parameter_number p_steepness;
   CORN::Parameter_number p_slope_length;      // m
   CORN::Parameter_number p_albedo_dry;
   CORN::Parameter_number p_albedo_wet;
   CORN::Parameter_number p_water_vapor_conductance_atmosphere_adj;
   CORN::Parameter_number p_SLPF_CropGro;

   soil_horizon_parameter_array(p_layer_thickness); // m
   soil_horizon_parameter_array(p_bypass_coef);     // Not entered as a parameter, copied from init H2O,eventauly delete
   soil_horizon_parameter_array(p_bulk_density);    // tonne/m3 = g/cm3
   soil_horizon_parameter_array(p_perm_wilt_point); // m3/m3
   soil_horizon_parameter_array(p_field_capacity);  // m3/m3
   soil_horizon_parameter_array(p_vol_WC_at_1500);  // m3/m3
   soil_horizon_parameter_array(p_vol_WC_at_33);    // m3/m3

   soil_horizon_parameter_array(p_sand);                  // % 0-100
   soil_horizon_parameter_array(p_clay);                  // % 0-100
   soil_horizon_parameter_array(p_silt);                  // % 0-100
   soil_horizon_parameter_array(p_sat_hydraul_cond_m_d);  // m/day
   soil_horizon_parameter_array(p_saturation_WC); // m3/m3
   soil_horizon_parameter_array(p_air_entry_pot);         // J/kg
   soil_horizon_parameter_array(p_Campbell_b);                // -

   soil_horizon_parameter_array(p_pH);                          // -
   soil_horizon_parameter_array(p_cation_exchange_capacity);   // (cMol_c/cg soil) centimole of positive char/ kilogram soil (equivelent to meq/100g) For ammonium volitalization
   soil_horizon_parameter_array(p_organic_matter);
   soil_horizon_parameter_array(p_organic_matter_low);
   soil_horizon_parameter_array(p_organic_matter_high);

public:
   Soil_parameters();
   virtual ~Soil_parameters();                                                   //141228
   virtual bool expect_structure(bool for_write = false);                        //161025_981103
};
//______________________________________________________________________________
#endif
