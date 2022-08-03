#include "soil/sublayers.h"
#include "soil/soil_param.h"
#include "corn/math/compare.hpp"
//_____________________________________________________________________________/
Soil_sublayers::Soil_sublayers
(const Soil_parameters &_parameters)                                             //160916
: CropSyst::Soil_layers(_parameters)                                             //131122
, num_sublayers(0)
, num_uninundated_sublayers(0)                                                   //061004
,parameters(_parameters)                                                         //061004
{  for (nat8 sublayer = 0; sublayer <= MAX_soil_sublayers; sublayer ++)
   {  depth[sublayer] = 0;
      thickness[sublayer] = 0;
      in_horizon_of[sublayer] = 0;
   }
}
//_________________________________________________Soil_sublayers_constructor__/
void Soil_sublayers
::expand_last_layer_for_boundary_conditions(nat8 number_layers,nat8 number_expanded_layers)              modification_
{  nat8 pseudo_layer = number_layers+1;
   for (nat8 extend_layer = pseudo_layer; extend_layer <= number_expanded_layers; extend_layer++) //080211
   {  in_horizon_of[extend_layer] = in_horizon_of[num_sublayers];
      // Not adding the pseudo layer to the divisions
      // Not adding the pseudo layer to the depth
      thickness[extend_layer] =thickness[num_sublayers];
   }
}
//_2008-01-30_______________________expand_last_layer_for_boundary_conditions__/
float64 Soil_sublayers::get_depth_m(nat8 sublayer)                         const
{ return depth[sublayer? sublayer : num_sublayers]; };
//________________________________________________________________get_depth_m__/
void Soil_sublayers::copy(const Soil_sublayers &copy_from)
{  num_sublayers = copy_from.num_sublayers;
   num_uninundated_sublayers = copy_from.num_uninundated_sublayers;              //080211
   for (nat8 sublayer = 0; sublayer <= MAX_soil_sublayers; sublayer++)
   {  in_horizon_of[sublayer]   = copy_from.in_horizon_of[sublayer];
      divisions[sublayer]     = copy_from.divisions[sublayer];
      depth[sublayer]         = copy_from.depth[sublayer];
      thickness[sublayer]     = copy_from.thickness[sublayer];
   }
}
//_______________________________________________________________________copy__/
nat8 Soil_sublayers::sublayer_at(float64 a_given_depth_m ,bool  limit_to_MAX_trans_sublayers) const
{  float64 sublayer_depth = 0.0;
   nat8 sublayer = 0;
   if (CORN::is_approximately<float64>(a_given_depth_m,0.0,0.0000001))           //040524
      a_given_depth_m = 9999.9;                                                  //040524
   do
   { sublayer++;
     sublayer_depth += get_thickness_m(sublayer);
   } while ((sublayer_depth < a_given_depth_m) && (sublayer < num_sublayers));
   return sublayer;                                                              //970509
}
//________________________________________________________________sublayer_at__/
float64 Soil_sublayers::distribute_amount
(const      soil_horizon_array32(horizon_amount)
,modifiable_  soil_sublayer_array_64(sublayer_amount))                     const
{  float64 sum = 0;
   clear_layer_array64(sublayer_amount);                                         //070607
   for (nat8 sublayer = 1; sublayer <= get_number_sublayers(); sublayer ++)
   {  nat8 horizon = get_horizon_at_layer(sublayer);
      float64 by_sublayer    = divisions[horizon];
      float64 amount_sl      = ((float64)horizon_amount[horizon]) / by_sublayer;
      sublayer_amount[sublayer] = amount_sl;
      sum += amount_sl;
   }
   return sum;
}
//_2007-06-06_______________________________________________distribute_amount__/
float64 Soil_sublayers::distribute_property
(const     soil_horizon_array32(horizon_property)
,modifiable_ soil_sublayer_array_64(sublayer_property))                    const
{  clear_layer_array64(sublayer_property);                                       //070607
   for (int sublayer = 1; sublayer <= get_number_sublayers(); sublayer ++)
   {  nat8 horizon = in_horizon_of[sublayer];
      sublayer_property[sublayer] = (float64)horizon_property[horizon];
   }
   return 0.0;
}
//_2007-06-06_____________________________________________distribute_property__/

