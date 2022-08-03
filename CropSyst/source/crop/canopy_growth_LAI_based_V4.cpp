#include "crop/canopy_growth_LAI_based_V4.h"

namespace CropSyst {
//______________________________________________________________________________
Canopy_growth_leaf_area_index_based_V4::Canopy_growth_leaf_area_index_based_V4
(const Crop_parameters            &_crop_parameters
,const Crop_parameters_struct::Canopy_growth_LAI_based    &_parameters
//161106 ,const Crop_thermal_time_interface_immutable &_thermal_time
,const Thermal_time_immutable       &_thermal_time                               //151106
,Residues_interface                 *_residues
,Crop_nitrogen_interface            *_nitrogen
,float64 &_reported_peak_LAI
,Crop_CO2_response   *_CO2_response
,bool _is_continuous_grass
)
:Canopy_growth_leaf_area_index_based
(_crop_parameters
,_parameters
,_thermal_time
,_residues
,_nitrogen
,_reported_peak_LAI
,_CO2_response
,_is_continuous_grass)
{}
//_2013-06-10_____________________________________________________constructuor_/
} // namespace CropSyst


