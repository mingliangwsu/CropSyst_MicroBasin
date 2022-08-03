#ifndef canopy_growth_LAI_based_V4H
#define canopy_growth_LAI_based_V4H
#include "crop/canopy_growth_LAI_based.h"

namespace CropSyst {

//______________________________________________________________________________
class Canopy_growth_leaf_area_index_based_V4
: public extends_ Canopy_growth_leaf_area_index_based
{
 public: // structors
   Canopy_growth_leaf_area_index_based_V4
      (const Crop_parameters                                   &_crop_parameters      // Will be owned by this crop object
      ,const Crop_parameters_struct::Canopy_growth_LAI_based   &_parameters
      //151106,const Crop_thermal_time_interface_immutable &_thermal_time
      ,const Thermal_time_immutable          &_thermal_time                      //151106
      ,Residues_interface                    *_residues                          //060816
      ,Crop_nitrogen_interface   *_nitrogen                                      //060816
      ,float64                               &_reported_peak_LAI                 //080725
      ,Crop_CO2_response     *_CO2_response                                      //080728
      ,bool                                   _is_continuous_grass);             //081108
   inline virtual float64 know_above_ground_biomass(float64 _above_ground_biomass_kg_m2) cognition_
      { return _above_ground_biomass_kg_m2; /*not used by this model */} //130625
};
//______________________________________________________________________________
} // namespace CropSyst
#endif



