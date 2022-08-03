#  include <math.h>
#  include "corn/math/moremath.h"
#  ifndef compareHPP
#     include "corn/math/compare.hpp"
#  endif
#  include "soil/temperature_profile.h"
#  include "soil/soil_interface.h"
#  include "soil/structure_interface.h"
#  include "soil/temperature_profile.h"
#  include "CS_suite/simulation/CS_land_unit_meteorological.h"
#  include "common/residue/residues_interface.h"
#  include "soil/soil_param.h"
#  include "soil/temperature_functions.h"
#  include "soil/hydrology_interface.h"
#  include "weather/parameter/WP_solar_radiation.h"
#  include "weather/snow_pack.h"
#define time_step  86400.0
#define Lf        333700.0
#include "common/physics/standard_constants.h"
//______________________________________________________________________________
Soil_temperature_profile::Soil_temperature_profile
(const Soil_parameters                     &soil_parameters_
,const Soil_layers_interface               &soil_layers_                         //061004
,const Soil_hydrology_interface            &soil_hydrology_                      //061004
,const Soil_structure_interface            &soil_structure_                      //070725
,const CS::Land_unit_meteorological        &meteorological_)                     //151022
:surface_temperature    (0.0)                                                    //970730
,residue_lagging_factor ( 0.0)
,new_temperature_0      ( 0.0)                                                   //151125
,soil_parameters        (soil_parameters_)                                       //061004
,soil_layers            (soil_layers_)                                           //061004
,soil_hydrology         (soil_hydrology_)                                        //061004
,soil_structure         (soil_structure_)                                        //070725
,meteorological         (meteorological_)                                        //151125
,annual_temperature_avg (0)                                                      //151125
,air_temperature_max    (meteorological_.ref_air_temperature_max())              //151125
,air_temperature_min    (meteorological_.ref_air_temperature_min())              //151125
,air_temperature_avg    (meteorological_.ref_air_temperature_avg())              //151125
,solar_radiation        (meteorological_.ref_solar_radiation())                  //151125
{  for (nat8  layer = 0; layer <= MAX_soil_layers; layer++)
   {  temperatures[layer] = 0;
      previous_temperatures[layer] = 0;
      new_temperatures[layer] = 0;                                               //011109
   }
}
//_1997-07-30___________________________________________________________________
bool Soil_temperature_profile::initialize
(float64    initial_soil_temp
,float64    _annual_temperature_avg)                                             //060502
{  surface_temperature = initial_soil_temp;
   annual_temperature_avg = _annual_temperature_avg;                             //060502
   for (nat8  layer = 1; layer <= MAX_soil_layers; layer++)
   {  temperatures[layer] = initial_soil_temp;
      previous_temperatures[layer] = initial_soil_temp;
   }
   return true;
}
//_2001-02-07___________________________________________________________________
float64 Soil_temperature_profile::profile_water_amount()
{  float64  sum = 0.0;
   for (nat8  layer = 1 ; layer <=  soil_layers.get_number_layers(); layer++)
      sum += soil_hydrology.get_water_plus_ice_content_volumetric(layer)
           * soil_layers.get_thickness_m(layer);                                 //990311
   return sum ;
}
//______________________________________________________________________________
float64 Soil_temperature_profile::damping_depth()    // m
{
   float64 avg_bulk_density    //tonne/m3}
      = soil_structure.get_bulk_density_avg_g_cm3();                             //070725
   float64 depth = soil_layers.get_depth_profile_m();
   float64 water_scaling_factor    //unitless? currently mm?
      = profile_water_amount()
       /((0.356 - 0.144 * avg_bulk_density) * depth);                            //980731
   float64 max_damping_depth       //m
      = 1.0+(2.5 * avg_bulk_density)
       / (avg_bulk_density + exp(6.53-5.63 * avg_bulk_density));
   return max_damping_depth
      * exp(CORN_ln(0.5/max_damping_depth)
      * CORN_sqr((1.0-water_scaling_factor)/(1.0+water_scaling_factor)));
}
//______________________________________________________________________________
void Soil_temperature_profile::find_soil_temp
(float64   leaf_area_index                                                       //980601
,bool      water_was_applied                                                     //990202
,const     Residues_interface *residue                                           //060628
,float64   fraction_canopy_interception                                          //990202
,float64   plant_height)                                                         //990202
{
   float64 max_temp = air_temperature_max.Celcius();                             //101006
   float64 min_temp = air_temperature_min.Celcius();                             //101006

   float64 deep_constant_temperature= annual_temperature_avg;
   float64 snow_pack_thickness = meteorological.get_snow_pack_thickness();       //151022_141205_991004
      // snow_depth_m
   float64 solar_rad =
      solar_radiation.get_MJ_m2();                                                //151022
   surface_temperature = actual_surface_temp  //C
      (max_temp,min_temp
      ,solar_rad
      ,snow_pack_thickness
      ,leaf_area_index
      ,residue ? residue->get_surface_all_biomass() : 0.0                        //050726
      ,meteorological.is_winter_time()
      );
   get_temperatures  // _without_freezing
      (deep_constant_temperature
      ,residue
      ,fraction_canopy_interception
      ,plant_height);
}
//______________________________________________________________________________
float64 Soil_temperature_profile::base_line_temperature
(nat8       layer  // sublayer
,float64    deep_constant_temperature
,float64    temperature_influence_from_above)
{  float64 DD = damping_depth();                                                 //990213
   float64 depth_factor = 1.0;                                                   //991021
   if (!CORN::is_approximately<float64>(DD,0.0,0.00000001))                      //981027
   {  float64 depth_layer = soil_layers.get_depth_m(layer);                      //981027
      float64 ZD =  CORN_must_be_less_or_equal_to(((layer == 1)                  //991021
       ? (depth_layer/2.0) / DD                                                  //991021
       : (layer == (soil_layers.get_number_layers() + 1))                        //991021
          ? soil_layers.get_depth_m(layer-1) / DD                                //991021
          : (depth_layer - (soil_layers.get_thickness_m(layer) / 2.0)) / DD      //991021
       ) ,3.0);                                                                  //991021
       depth_factor = ZD / (ZD + exp(-0.867 - 2.08 * ZD)); // unitless
   }                                                                             //981027
   float64 baseline_temp = (depth_factor *                                       //981028
   (deep_constant_temperature - temperature_influence_from_above)                //981028
   + temperature_influence_from_above);                                          //981028
	return baseline_temp;                                                         //050111
}
//_1999-01-20___________________________________________________________________
void Soil_temperature_profile::long_term_initialization
(float64 _annual_temperature_avg // deep_constant_temperature
,float64 temperature_influence_from_above)
{  float64 lag_coefficient = 0.0;  //eventually an input parameter ?
   initialize(temperature_influence_from_above,_annual_temperature_avg);         //040714
   // Note, I am presuming this is called one time
   copy_layer_array64(previous_temperatures,temperatures);
   float64  deep_constant_temperature = annual_temperature_avg;                  //060502
   for (nat8  layer = 1; layer <= soil_layers.get_number_layers(); layer++)
   {  // Once we encounter a layer that is frozen the surface temperature influence is nullified.
      if (soil_hydrology.is_frozen(layer))                                       //981028
         temperature_influence_from_above = 0;
      temperatures[layer]=
      lag_coefficient*
      previous_temperatures[layer]+(1.0-lag_coefficient)*
      base_line_temperature(layer,deep_constant_temperature,temperature_influence_from_above); //981028
   }
}
//_1999-02-13___________________________________________________________________
float64 Soil_temperature_profile::find_heat_source_sink  // J/m2/s
(float64 thickness_sl       // m
,float64 new_ice_content_sl
,float64 old_ice_content_sl)
{  static const float32 ice_density =  920.0; /* kg/m3 */ // this constant should be move to physics
   float64 heat = //  J/(m2 s)
      ice_density * Lf * (new_ice_content_sl - old_ice_content_sl)
      * thickness_sl / time_step;
   return heat;
}
//______________________________________________________________________________
float64 Soil_temperature_profile::albedo_for_soil_temp()
{  float64 FC_1  = soil_parameters.get_horizon_field_capacity_volumetric(1);       // 051204 Note this can be either horizon or layer
   float64 PWP_1 = soil_parameters.get_horizon_permanent_wilt_point_volumetric(1); // If I make this by layer I might not need to pass the soil parameters (other than albedo)
   float64 WC_1  = soil_hydrology .get_liquid_water_content_volumetric(1);       //990311
   float64 albedo =
   (WC_1 >= FC_1)
   ? 0.10
   : (WC_1 <= PWP_1)
     ? 0.18
     : 0.1 + 0.08 * ( (FC_1 - WC_1) / (FC_1 - PWP_1));
   return albedo;                                                                //990309
}
//______________________________________________________________________________
// This is similar to the longwave_net_radiation for ET calculation
// but it doesn't account for elevation, it probably should.
// check with Claudio
// Need to check if this function is check if this is function is OK for non daily time step
// 151022
float64 calc_longwave_net_radiation_for_soil_temp()
{
   assert(false); //need to implement
   return 0;
/*
   float64 delta_emmis = delta_emissivity();
   float64 est_clear_sky_solar_rad;
   est_clear_sky_solar_rad = 0.75 *
      ET_solar_irradiance_new.CS::Solar_irradiance_extraterrestrial_daily::get_MJ_per_m2_day(); //150628
   float64 cloud_factor = get_cloud_factor_for_net_rad
      (est_clear_sky_solar_rad); //041110
   float64 lwnr =
          cloud_factor * delta_emmis * Stephan_Boltzmann_MJ_K4_m2_day
            * pow(ref_air_temperature_avg().kelvin(),4.0);
   //000731 Warning why are we not using the full Stephan Boltzmann law which is the average of the powers of 4?
   return lwnr;
*/
}
//_2015-10-22___________________________________________________________________
float64 Soil_temperature_profile::radiation_load         // J/(m2 sec)
(float64 fract_crop_interception
,float64 fract_residue_interception)
{
   static const float64 residue_albedo = 0.20;
   static const float64 crop_albedo    = 0.22;
   float64 total_albedo =                                                        //990326
       (albedo_for_soil_temp() * (1.0 - fract_residue_interception)
           + residue_albedo * (fract_residue_interception))
         * (1.0 - fract_crop_interception)
       + crop_albedo * fract_crop_interception;
   float64 net_rad =
      meteorological.ref_sky().                                                   //151022
      calc_shortwave_net_radiation
      (total_albedo
      ,solar_radiation                                                           //151022
         .get_MJ_m2()
      )
      - calc_longwave_net_radiation_for_soil_temp();
        //151022  Xweather.longwave_net_radiation_for_soil_temp() ;
   float64  rad_load = (meteorological /*151022 Xweather*/.get_snow_pack_thickness() > 0)                   //141205_991004
   ? 0.0
   : //{ scale down effective energy: }
     ((1-fract_residue_interception) * (1.0 - fract_crop_interception) *net_rad)
     * 1000000.0/86400.0; // { MJ/m2/daytime -> J/(m2 sec)}
   return  rad_load;
}
//______________________________________________________________________________
void Soil_temperature_profile::SolveTemp
(float64 plant_height
,float64 fract_crop_interception
,const   Residues_interface *residue)                                            //050726
{
   static const float64 f =  1.0;
      // { May want to try different values of f. }
   static const float64 snow_thermal_conductivity_J_msC = 0.092048; //J/(m sec'C)

   soil_layer_array64(a); // 0 based, lower diagonal of tridiag matrix
   soil_layer_array64(b); // 0 based, main diagonal of tridiag matrix
   soil_layer_array64(c); // 0 based, upper diagonal of tridiag matrix
   soil_layer_array64(d); // 0 based, vector of known values
   soil_layer_array64(k); // 0 based
   soil_layer_array64(tc_J_m_s_C);
   float64 g = 1.0 - f;
   float64 snow_melted = 0;                                                      //151022
   float64 snow_depth_m = 0;                                                     //151022
   const Snow_pack *snow_pack = meteorological.get_snow_pack();                  //151022
   if (snow_pack)
   {
      snow_depth_m = snow_pack->ref_snow_pack_thickness();                       //151022
      //141205 I should actually pass reference in constructor and use the reference
      // inorder to remove the call (This is all setup to do this, I just need to test it
      snow_melted = snow_pack->get_melted();
   }
   float64 snow_melting_heat = snow_melted /*151022 Xweather.get_snow_melted()*/
      * Lf * water_density / 86400.0;
   for (nat8  sl_tc = 1 ; sl_tc <= soil_layers.get_number_layers(); sl_tc++) // Note this is different from Basic Version
   {  float64 liquid_water_content = soil_hydrology.get_liquid_water_content_volumetric(sl_tc);   //990311
      float64 ice_water_content    = soil_hydrology.get_ice_content_volumetric(sl_tc);      //070808
      float64 bulk_density_g_cm3   = soil_structure.get_bulk_density_g_cm3(sl_tc);//070726
      tc_J_m_s_C[sl_tc] = DeVries_thermal_conductivity
         (liquid_water_content,ice_water_content,bulk_density_g_cm3);
   }
      float64 k_air = 99999.9;                                                   //990311
#ifdef DISABLED_PERMANENT
   static const float64 vol_heat_capacity_air = 1200.0; // J/m3 C

   const Geolocation *geolocation = weather.weather_data->get_geolocation_constant();  //050619
      float64 non_crop_cover_height =  std::max<xxxx>(residue ? residue->get_surface_depth(): 0.0 ,snow_depth_m);
#define           min_cover_height 0.1
      float64 cover_height = std::max<float64>(std::max<float64>(plant_height,non_crop_cover_height),min_cover_height);
      float64 zero_plane_displacement  = 0.65 * std::max<float64>(min_cover_height,cover_height);
      float64 momentum_roughness_param = 0.1 * std::max<float64>(min_cover_height,cover_height);
      float64 wind_speed_m_s = weather.wind_speed_m_d() / 86400.0;
      float64 screening_height_m = geolocation ? geolocation->get_screening_height(): 2.0;   //050916
      static const float64 on_karman_const = 0.4;                  /* unitless */
      CORN::must_be_greater_or_equal_to<float64>                                 //990409
         ((vol_heat_capacity_air * CORN_sqr(von_karman_const) * wind_speed_m_s) /
            CORN_sqr(CORN_ln((screening_height_m - zero_plane_displacement) / momentum_roughness_param))
         ,20.0);                                                                 //990326
#endif
      float64 k_snow = (snow_depth_m > 0.0)
         ? (snow_thermal_conductivity_J_msC) / snow_depth_m                      //990316
         : 99999.9;
      float64 k_residue = 99999.9;
#ifdef DISABLED_PERMANENT
         residue.thermal_conductance(
          (snow_depth_m > 0.0) ||  (plant_height > residue.get_surface_depth() )
          , weather.average_air_temperature
          ,wind_speed_m_s,screening_height_m );
#endif
      float64 k_crop =  99999.9;
#ifdef DISABLED_PERMANENT
      ((plant_height > non_crop_cover_height) &&
         (zero_plane_displacement > non_crop_cover_height) )
      ?    (vol_heat_capacity_air * von_karman_const
           * friction_velocity(momentum_roughness_param,zero_plane_displacement,wind_speed_m_s,screening_height_m)
           * (std::max<float64>(plant_height,min_cover_height) + momentum_roughness_param - zero_plane_displacement))
          / (zero_plane_displacement - non_crop_cover_height)
      :
#endif
   float64 k_ground_cover = std::min<float64>(k_snow,k_residue);                 //990326
   float64 k_total = 1.0/( 1.0/k_air  + 1.0/k_crop+ 1.0/k_ground_cover);         //990326
   nat8  num_layers = soil_layers.get_number_layers();
   for (nat8  sl_k = 1; sl_k <= num_layers -1; sl_k++)//   Note this is different from Basic Version
   {  float64 half_thickness = soil_layers.get_thickness_m(sl_k) / 2.0;
      float64 next_half_thickness = soil_layers.get_thickness_m(sl_k+1) / 2.0;
      float64 distance_to_next_node = (half_thickness + next_half_thickness);
      float64 equiv_tc = distance_to_next_node / (half_thickness / tc_J_m_s_C[sl_k]
      + next_half_thickness/tc_J_m_s_C[sl_k+1]);
      k[sl_k] =// cal /(cm * sec * C') -> J/(m sec 'C)
       equiv_tc / distance_to_next_node;
   }
   k[0] = tc_J_m_s_C[1] / (soil_layers.get_thickness_m(1)/2.0);
   k[num_layers] = tc_J_m_s_C[num_layers] / (soil_layers.get_thickness_m(num_layers)/2);
   nat8  start_sl = 1;                                                           //990611
   float64 k_previous_node = k[0];                                               //990611
   new_temperatures[0] = surface_temperature;                                    //990324
   float64 previous_temperature = surface_temperature;                           //990324
   for (nat8  sl = start_sl; sl <= num_layers; sl++)
      // Note this is different from the VB Version
   {  uint32 node_layer = sl;                                                    //990216
      float64 node_thickness = soil_layers.get_thickness_m(sl);                  //990216
      float64 temperature_sl = temperatures[sl];                                 //990407
      if (sl == 0)
      {   temperature_sl = surface_temperature;                                  //990407
          node_layer = 1;
          node_thickness = 0.005;
      } else
      {  if (sl == 1)                                                            //990407
         {  node_layer = 1;
            node_thickness = soil_layers.get_thickness_m(1) - 0.005;
            //{ We dont allow thickness < 0.01 m }
         }
      }
      float64 liquid_water_content = soil_hydrology.get_liquid_water_content_volumetric(node_layer); //070813
      float64 ice_content = soil_hydrology.get_ice_content_volumetric(node_layer);//070813
      float64 heat_cap_factor = calc_local_heat_capacity_J_m3_C
             (soil_structure.get_bulk_density_g_cm3(node_layer),liquid_water_content,ice_content) //070725
             * node_thickness;                                                   //060509
      c[sl] = -k[sl] * f;
      a[sl + 1] = c[sl];
      b[sl] = f * (k[sl] + k_previous_node) + heat_cap_factor / time_step;
      d[sl] = g * k_previous_node * previous_temperature
            + (heat_cap_factor / time_step
            - g * (k[sl] + k_previous_node)) *  temperature_sl
            + g * k[sl] * temperatures[sl + 1]
            + find_heat_source_sink
               (soil_layers.get_thickness_m(sl)
               ,soil_hydrology.get_ice_content_volumetric(sl)
               ,soil_hydrology.get_ice_content_volumetric_yesterday(sl));        //990315
            ;
      k_previous_node = k[sl];
      previous_temperature = temperature_sl;
   }                 // surface_temperature
   if (start_sl == 0)                                                            //990324
   {  float64 fract_residue_cover = residue ? residue->get_total_fract_ground_cover //990325
         (INCLUDE_POSITION_FLAT_SURFACE| INCLUDE_POSITION_STUBBLE_SURFACE) : 0.0;
      float64 rad_load = radiation_load
         (fract_crop_interception,fract_residue_cover);                          //990315
      d[0] +=
         air_temperature_avg.Celcius()                                           //151022_140527_131104
                                        //
          * k_total  * f                                                         //990315
        + rad_load                                                               //990315
        - snow_melting_heat;                                                     //990315
   } else                                                                        //990325
      d[1] += k[0] * surface_temperature * f;                                    //990324
   d[num_layers] += k[num_layers] * f * new_temperatures[num_layers+1];
   //{ Note m is different from BASIC version}
   for (nat8  sl_finish = start_sl  // These are 0 based indexed
       ; sl_finish <= num_layers-1
       ;sl_finish++) // Note m-2 is different from BASIC version}
   {  c[sl_finish] /= b[sl_finish];
      d[sl_finish] /= b[sl_finish];
      b[sl_finish + 1] -= a[sl_finish + 1] * c[sl_finish];
      d[sl_finish + 1] -= a[sl_finish + 1] * d[sl_finish];
   }
   new_temperatures[num_layers] = d[num_layers] / b[num_layers];
   for (int8 sl_update = num_layers-1; sl_update >= start_sl ; sl_update--)  // <- must be int8!!!
     new_temperatures[sl_update] = d[sl_update] - c[sl_update] * new_temperatures[sl_update + 1];
}
//______________________________________________________________________________
void  Soil_temperature_profile::get_temperatures
(float64 deep_constant_temperature  // C
,const  Residues_interface *residue                                              //050726
,float64 fract_crop_interception
,float64 plant_height)
{
#define        time_step   86400.0
#define        tolerance   0.1
   //130626 // actually const, but some functions do some update need to check carefully.


   // This layering is slightly different from normal we now create a layer 0}
   // to which the normal layer 1 is split between layer 0 and layer 1       }
#ifdef HEAT_SINK_FREEZING
   soil_layer_array_64(heat_source_sink);
   soil_layer_array_64(new_ice_content);
#endif
   nat8  number_layers = soil_layers.get_number_layers();                        //061004
   temperatures[number_layers+1] = base_line_temperature
      (number_layers+1,deep_constant_temperature,surface_temperature);
   copy_layer_array64(new_temperatures, temperatures);
   new_temperatures[0] = new_temperature_0;                                      //990303
#ifdef HEAT_SINK_FREEZING
   clear_layer_array(heat_source_sink);
   copy_layer_array(new_ice_content,ice_content);
#endif
   SolveTemp(plant_height,fract_crop_interception,residue);
#ifdef HEAT_SINK_FREEZING
   bool any_pot_frozen_layers = false;
   int8 last_pot_frozen_layer = -1;
   int8 first_pot_frozen_layer  =  MAX_soil_layers;
   // find if there are frozen layers or potential for freezing.
   for (nat8  layer = 1 ; layer <= number_layers ; layer++)
       if ((ice_content[layer] > 0) || (new_temperatures[layer] < 0))
       {  if (first_pot_frozen_layer == MAX_soil_layers)
               first_pot_frozen_layer = layer;
          last_pot_frozen_layer = layer;
          any_pot_frozen_layers = true;
       }
   if (any_pot_frozen_layers)
   {
     for (nat8  layer = first_pot_frozen_layer ; layer <= last_pot_frozen_layer; layer++)
     { // There could be a layer not frozen, we are only interested in frozen layers.
         if ((ice_content[layer] > 0) || (new_temperatures[layer] < 0) )
         {  float64 temperature_sl = new_temperatures[layer];
            float64 thickness_sl   = get_thickness_m(layer);
            new_ice_content[layer] = find_ice_content(layer, temperature_sl);
            heat_source_sink[layer] =
             find_heat_source_sink(thickness_sl, new_ice_content[layer], ice_content[layer]);
            SolveTemp
            (weather
            ,plant_height
            ,fract_crop_interception
            ,residue
            ,new_ice_content
            ,heat_source_sink
            );
            float64 Thigh = new_temperatures[layer];
            float64 Tlow  = temperature_sl;
            if (temperature_sl > new_temperatures[layer])
            {  Thigh = temperature_sl;
               Tlow  = new_temperatures[layer];
            }
            float64 change = 0.0;
            if (layer > 1)
            {  uint16 iteration = 1;
               do
               {  float64 Teq = (Thigh + Tlow) / 2.0;
                  float64 Teqold = Teq;
                  new_ice_content[layer] = find_ice_content(layer, Teq);
                  heat_source_sink[layer] =
                  find_heat_source_sink(thickness_sl, new_ice_content[layer], ice_content[layer]);
                  SolveTemp
                  (weather
                  ,plant_height
                  ,fract_crop_interception
                  ,residue
                  ,new_ice_content
                  ,heat_source_sink
                  );
                  Teq = new_temperatures[layer];
                  change  = fabs(Teq - Teqold);
                  if (change > tolerance)
                  {
                     if (Teq > Teqold) Tlow = Teqold;
                     else              Thigh = Teqold;
                     if (Tlow > Thigh)
                     {
                        new_temperatures[layer] = Tlow;
                        Tlow = Thigh;
                        Thigh = new_temperatures[layer];
                     }
                  }
                  iteration++;
               } while (change > tolerance); // End DO 4
            }
         }
      }
      SolveTemp   // one last time for final new temperatures.                    //990210
        (weather
        ,plant_height
        ,fract_crop_interception
        ,residue
        ,new_ice_content
        ,heat_source_sink);
   }
   for (nat8  layer = 1; layer <= get_number_layers(); layer++)
      set_liquid_water_content_volumetric(layer, get_liquid_water_content(layer) + (ice_content[layer] - new_ice_content[layer] )); //990311
   copy_layer_array64(ice_content,new_ice_content);
#endif
   copy_layer_array64(temperatures,new_temperatures);                            //061004
   new_temperature_0 = new_temperatures[0];                                      //990311
}
//_1999-01-20___________________________________________________________________
//060726 was 600 lines
//070725 500 lines

