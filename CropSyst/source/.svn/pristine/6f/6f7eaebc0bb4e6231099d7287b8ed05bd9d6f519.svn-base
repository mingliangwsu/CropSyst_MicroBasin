#ifndef infiltration_cascade_commonH
#define infiltration_cascade_commonH
#include "soil/infiltration.h"
#include "soil/hydrology_cascade.h"
#include "common/evaporator.h"
namespace MicroBasin
{
class SoilProcessesClass;                                                        //141005
}
//______________________________________________________________________________
class Soil_infiltration_cascade_common
: public  Soil_infiltration
{
 protected: friend class MicroBasin::SoilProcessesClass;                         //141005
   Soil_hydrology_interface &hydrology;
 public:
   soil_layer_array64(water_flow);              // m (I believe positive values are flow down)   //070117
 public: // Constructor
   Soil_infiltration_cascade_common
      (const Soil_layers_interface      &soil_layers                             //140424
      ,const Soil_hydraulic_properties_interface &soil_hydraulic_properties      //140423
      ,Soil_hydrology_interface  &hydrology
      ,CropSyst::Soil_runoff     *runoff                                         //131101_130308
      ,CropSyst::Pond            &pond);                                         //130308
   inline virtual bool initialize()                                modification_
      { return Soil_infiltration::initialize(); }                                //131217
   inline virtual bool reinitialize(const soil_horizon_array32(H2O))modification_
      {  /* May eventually move some soil variables here in this case, will need to reinitialize */
         return true;                                                            //131217
      }
 public:
   inline virtual float64 get_water_table_input()          const { return 0.0; }  //might want to return NaN
   inline virtual float64 get_water_table_depth()          const { return 0.0; }  //070309
   virtual float64 calc_evaporation_potential()                     calculation_ //160603
      { assert(false); return 0; }
};
//_2007?_____________________________________Soil_infiltration_cascade_common__/
#endif

