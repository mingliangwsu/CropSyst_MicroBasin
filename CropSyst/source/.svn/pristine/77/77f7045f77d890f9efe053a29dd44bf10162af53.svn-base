#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#include <math.h>

#include "soil/freezing_numerical.h"
#endif
#ifdef HEAT_SINK_FREEZING
This is old

//______________________________________________________________________________
soil_freezing_profile_numerical::soil_freezing_profile_numerical()
{}
//______________________________________________________________________________
float32 soil_freezing_profile_numerical::get_freezing_depth()              const
{  nat8  first_freezing_sublayer = 0;
   for (nat8  sublayer = 1 ; sublayer < get_num_sublayers(); sublayer++)
      if ((first_freezing_sublayer == 0) && is_frozen(sublayer))
         first_freezing_sublayer = sublayer;
   return (first_freezing_sublayer > 1)
   ? get_depth(first_freezing_sublayer-1)
   :  0.0;
};
//_1999-01-20______________________________________________get_freezing_depth__/
float32 soil_freezing_profile_numerical::get_ultimate_freezing_depth()     const
{  float32 ultimate_freezing_depth = 0.0;
   for (nat8  sublayer = 1; sublayer <= get_num_sublayers(); sublayer++)
      if (is_frozen(sublayer))
      {  float32 max_ice_content = find_ice_content(sublayer,-5.0);              //990210
         float32 max_ice_cont_fract = CORN::must_be_less_or_equal_to<float32>
            (get_ice_content(sublayer) / max_ice_content,1.0);
         ultimate_freezing_depth = get_depth(sublayer)
           - get_thickness(sublayer) * (1.0 - max_ice_cont_fract) ;
      };
   return ultimate_freezing_depth;
};
//_1998-10-15_____________________________________get_ultimate_freezing_depth__/
bool soil_freezing_profile_numerical::is_frozen(nat8  sublayer)            const
{  return get_ice_content(sublayer) > 0.0;
};
//_1999-01-20___________________________________________________________________
float32 soil_freezing_profile_numerical::find_ice_content
(nat8    sublayer
,float32 temperature_sl)
{  float32 ice_content_new = 0.0;
   if (temperature_sl < 0)
   {  float64 water_content = get_water_content(sublayer);
      float64 sat_water_content =  get_saturation_water_content(sublayer);
      ice_content_new =
      (  water_content
           - (sat_water_content *
             pow((Lf * temperature_sl / ((273.15 + temperature_sl) * get_air_entry_pot(sublayer)))
                ,(-1 / get_soil_b(sublayer)))));
   };
   return CORN_must_be_greater_or_equal_to(ice_content_new,0.0);
};
//_1999-02-15________________________________________________find_ice_content__/
#endif

