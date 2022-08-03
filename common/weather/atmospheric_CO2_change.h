#ifndef atmospheric_CO2_changeH
#define atmospheric_CO2_changeH
#include "corn/const.h"
#include "corn/primitive.h"
#include "corn/chronometry/date_types.hpp"
#include "common/biometeorology/parameter/CO2_atmospheric_conc.h"
#include "CS_suite/simulation/CS_simulation_element.h"
//______________________________________________________________________________
namespace CORN
{  class Quality;
}
//______________________________________________________________________________
class Atmospheric_CO2_change_element  // interface   rename to Atmospheric_CO2_change_element was Atmospheric_CO2_change_interface
: public extends_ CS::Simulation_element_abstract                                //171207
{  // This is an superclass for Atomspheric CO2 change models.
   // Note that for CropSyst, the CO2 change in the ET model is optional.
public:
   inline Atmospheric_CO2_change_element(const CORN::date32 &today_raw_)       //171207
      : CS::Simulation_element_abstract(today_raw_)
      {}
   virtual float64 get_current_CO2_conc()                             const = 0;
   virtual const CS::CO2_atmospheric_concentration &ref_CO2_current_conc() const = 0; //150507
};
//_end_class___________________________________________Atmospheric_CO2_change__/
#endif

