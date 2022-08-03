#ifndef tillage_effectH
#define tillage_effectH
#include "corn/chronometry/date_types.hpp"
#include "corn/chronometry/time_types.hpp"
#include "corn/const.h"
#include "mgmt_param.h"
using namespace CORN;
class Soil_hydraulic_properties;
class Soil_sublayers;
class Soil_interface;
class Soil_disturbance;

class Soil_structure_common;
class Soil_hydrology_interface;
namespace RUSLE
{  class Soil_erosion;
}
//______________________________________________________________________________
#ifdef NYN
interface_ Soil_tillage_interface
{
 public:
   virtual bool process() = 0;
   virtual float64 get_dust_mulch_evaporation_today() const = 0;
};
#endif
//______________________________________________________________________________
class Soil_tillage_effect
{
 private:
   Soil_interface             *soil;                                             //060929
   Soil_sublayers             *layers;                // Owned by soil           //061003
   modifiable_ Soil_structure_common *soil_structure; // Owned by soil           //070726
   Soil_hydraulic_properties  *hydraulic_properties;  // Owned by soil
   RUSLE::Soil_erosion        *erosion;               // optional  owned by soil. 0 if no erosion submodel
 private:
   nat16                      dust_mulch_remaining_days;                         //051205
   float64                    dust_mulch_evaporation_today;                      //051206
   Soil_structure_common      *structure_hold_while_dust_mulch;                  //070725
   Soil_hydraulic_properties  *hydraulic_properties_hold_while_dust_mulch;       //051204
      /**< When dust mulch is present, the normal properties are
           stored here until the dust mulch returns to normal state.
      **/
   Soil_sublayers             *layers_hold_while_dust_mulch;                     //061003
   Soil_disturbance           *disturbance;                                      //060807
      // 0 until field operation disturbs the soil
   bool                        first_tillage;
 public: // structors
   Soil_tillage_effect
      (Soil_interface            *_soil
      ,Soil_sublayers            *_layers                                        //061004
      ,Soil_hydraulic_properties *_hydraulic_properties
      ,RUSLE::Soil_erosion       *_erosion);
   virtual ~Soil_tillage_effect();
 public:
   bool start_day();
   virtual bool process();
      // Called daily
   void clod_the_soil(int16 doy,float64 till_clod_factor);
      // Called in the case of a tillage event.
   bool dust_mulching(float32 to_depth, Days days_mulched,float32 dust_mulch_intensity);  //051203
      // Returns true if dust mulching performed.
   bool respond_to_field_operation                                               //060724
      (float64 tillage_op_depth_m            //VB  T_Depth = ManagementState.TillageDepth
      ,float64 tillage_op_mixing_fraction    //VB  T_Mix = ManagementState.TillageMixingFraction
      ,uint8 field_op_soil_disturbance_rating
      ,const CropSyst::Tillage_operation::Oxidation_effect *oxidation_effect = 0) modification_;
   bool correct_water_content_for_new_soil_properties                            //071212
      ( uint8  layer
      , float64 old_water_content_lyr
      , float64 old_thickness_lyr
      , float64 new_thickness_lyr
      , Soil_hydrology_interface *soil_hydrology);
 public: // accessors
   inline virtual float64 get_dust_mulch_evaporation_today()   const { return dust_mulch_evaporation_today; }
   inline const Soil_disturbance *get_disturbance()            const { return disturbance; }  // May return 0 if not disturbance   //060807
};
//_2010?________________________________________________________________________
#endif

