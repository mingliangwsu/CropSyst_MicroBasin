#include "soil_param_with_sublayers.h"
#include <corn/data_source/vv_file.h>

namespace CropSyst_parameters
{
//_____________________________________________________________________________
Soil_with_sublayering
::Soil_with_sublayering()
: Soil_properties_sublayers(&parameters,false)
/*
: Smart_soil_parameters()
, Soil_sublayers(*this)
, Soil_hydraulic_properties((const Soil_layers_interface &)(*this))
*/
{}
//_____________________________________________________________________________
bool Soil_with_sublayering::read_file(const char *filename)
{
   CORN::VV_File param_file(filename);
   bool got =  param_file.get(parameters);
   Soil_properties_sublayers::reinitialize                           //101104
      (true
      ,true/*subdivide_horizons*/
      ,false /*finite_diff*/);
   return got;
};
//_____________________________________________________________________________
};


