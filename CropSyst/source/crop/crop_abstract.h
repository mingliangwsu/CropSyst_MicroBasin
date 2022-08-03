#ifndef crop_abstractH
#define crop_abstractH

#include "soil/soil_interface.h"
#include "soil/nitrogen_interface.h"
#include "common/weather/weather_interface.h"
#include "common/residue/residues_interface.h"
#include "crop/crop_interface.h"
#define likely_const_
// Weather should be unmodifiable but I haven't check const correctness
//______________________________________________________________________________
class Crop_abstract             // rename this to Crop_situated
: public Crop_interface
{
public:
   modifiable_    Soil_interface          &soil;
   unmodifiable_  Soil_layers_interface   &soil_layers;
   modifiable_    Soil_nitrogen_interface &soil_chemicals;
   modifiable_    Residues_interface      *residues;
      // Residues is optional (used by the canopy decomposition submodel);
   const CORN::Date                       &today;
public:
   inline Crop_abstract
      (modifiable_   Soil_interface       &_soil_ref
      ,modifiable_   Residues_interface   *_residues
      ,const CORN::Date                   &_today
      )
      : soil            (_soil_ref)
      , residues        (_residues)
      , soil_layers     (*(_soil_ref.get_layers()))
      , soil_chemicals  ((*_soil_ref.mod_nitrogen()))
      , today           (_today)
      {}
   virtual const char* modname() const = 0;
};
//______________________________________________________________________________
#endif

