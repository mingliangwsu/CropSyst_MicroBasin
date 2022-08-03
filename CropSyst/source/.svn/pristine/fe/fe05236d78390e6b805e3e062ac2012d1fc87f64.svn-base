#ifndef soil_freezing_interfaceH
#define soil_freezing_interfaceH
#include "corn/const.h"
#include "corn/primitive.h"
class Snow_pack;                                                                 //151128
//______________________________________________________________________________
class Soil_freezing_profile_interface
{
 public: // process
   virtual void freezing_and_thawing   // This could be renamed update()   //981015
      (
       const Snow_pack *snow_pack                                                //151128
      /*151128
      float64 avg_temp      // average temp in 'celcius }
      ,float64 snow_storage  // current accum precip in snow }
      ,bool melting_snow
      */
      )                                           modification_= 0;  //981005
 public: // accessors
   virtual bool is_frozen(nat8 layer)                               affirmation_ = 0;  //981014
   virtual float64 get_ultimate_freezing_depth()                           const = 0;  //981014
   virtual float64 calc_liquid_and_ice_water_content_volumentric           //070825
      (nat8 layer
      ,float64 &vol_liquid_water_content
      ,float64 &vol_ice_content)                                           const = 0;
      ///< Partitions the full water content of the sublayer into ice and water
      /// (liquid_water_content and ice_content are modified), the values are also returned.
      /// \return the fraction of the layer that is frozen.
   virtual bool freeze_or_thaw_occured(nat8 layer)                         const = 0;  //070827
};
//_20-07-08-24__________________________________________________________________

#endif

