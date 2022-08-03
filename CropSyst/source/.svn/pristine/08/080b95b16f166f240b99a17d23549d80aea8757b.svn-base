#ifndef crop_transpiration_abstractH
#define crop_transpiration_abstractH
namespace CORN { class Enumeration_list; }                                       //130730
#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#include "corn/const.h"
#ifndef mgmt_typesH
#  include "mgmt_types.h"
#endif

#ifndef MAX_soil_layers
// This is needed when compiling under V3 because
// V4 global soil types are confusing the V4 spreadsheet outputs. 
#  include "common/soil/layering.h"
#endif
#include "CS_suite/observation/CS_observation.h"
class Soil_interface;
//______________________________________________________________________________
interface_ Crop_transpiration       // actually this is an interface
{
 public:
   inline Crop_transpiration() {}
   virtual float64 calc_transpiration
      (float64 limited_pot_transpiration                                         //011117
      //160415 ,float64 &attainable_transpiration                                         //160321
      ,float64 fract_canopy_cover                                                //020712
      ,float64 param_max_water_uptake_at_growth_stage_m                          //091208
      ,modifiable_ float64 &interception_canopy_m                                //160414_160318
      ,const soil_sublayer_array_64(total_fract_root_length)                     //050331
      /*160415 moved to actual_uptake
      ,uint8 soil_num_sublayers                                                  //010724
      ,const float64 soil_water_pot[]                                            //010724
      */
      ,soil_sublayer_array_64(water_uptake)                                      //010724
      /*060414 moved to actual uptake
      ,soil_sublayer_array_64(salt_stress_function) = 0                          //020712
         // Optional for salinity. If null, 1.0 will be used for salt stress
      ,soil_sublayer_array_64(soil_osmotic_pot_solution) = 0
      */
//160418      #ifndef __BCPLUSPLUS__
      ,float64 CO2_transpiration_adjustment_factor                               //160418
//160418      #endif
      )                                                        const = 0; //020715 was const
         // Optional for salinity. If null, 0.0 will be used osmotic potential

   virtual float64 get_active_fract_root_length(nat8 sublayer)        const = 0;
   virtual float64 get_leaf_water_pot()                               const = 0; //071114
   virtual float64 get_uptake_actual()                                const = 0; //160414
   #ifdef DIRECTED_IRRIGATION
   virtual bool know_directed_irrigation_soil_wetting                            //130313
      (const Directed_irrigation_soil_wetting *soil_wetting)          cognition_=0;
   #endif
//151106 unused?   virtual float64 &ref_sink_limited_biomass_production_inhibition() modification_=0;//130506
/*160415 decided not to do this
   virtual bool know_soil  // Soil should actually be passed in constructor       //160415
      (
        modifiable_ Soil_interface           *soil_
      ) = 0; // this is just temporary until I have setup soil references in transpiration classes
*/
 public: // observation
   RENDER_INSPECTORS_DECLARATION_PURE;                                           //160627
};
//______________________________________________________________________________
#endif

