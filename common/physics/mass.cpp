#include "mass.h"
#include "corn/measure/measures.h"
#include "corn/math/compare.hpp"
#include "physics/mass_common.h"
namespace Physical
{
//______________________________________________________________________________
const float64 Gas::ideal_constant_m3_mol = 8.314472;   // 8.314472 J/(K mol)
const float64 Gas::ideal_gas_pressure = 1.0;   // 1.0 pascals
   //Nicole is going to change to temperature reference point
const float64 Gas::ideal_gas_temperature_C = 5.0;// 5'C   This is too low for most uses
//______________________________________________________________________________
float64 Matter::calc_concentration_kg_m3(float64 quantity_kg)              const
{  float64 volume_m3 =  get_volume_m3();
   float64 conc_kg_m3
      = volume_m3 ? (quantity_kg / volume_m3) : 0.0;                             //030227
   return conc_kg_m3;
}
//_2002-10-18___________________________________________________________________
float64 Matter::calc_concentration_g_m3(float64 quantity_kg)               const
{  return kg_to_g(calc_concentration_kg_m3(quantity_kg));
}
//_2002-10-18___________________________________________________________________
float64 Matter_wet::get_moisture_percent()                                 const // (was in Biomatter_abstract
{  return convenient_mass_dry() / wet_kg() * 100.0;
}
//_2010-08-20_____________________________________________get_moisture_percent_/
float64 Matter_wet::calc_wet_weight_kg_from_volume_m3(float64 volume_m3)   const
{  // this is used when creating biomatter pool for filling a facility based on volume.
   float64 density_kg_m3 =  get_density_kg_m3();
   float64 wet_weight_kg =  volume_m3 * density_kg_m3;
   return wet_weight_kg;
}
//_2004-04-04________________________________calc_wet_weight_kg_from_volume_m3_/
float64 Matter_wet::calc_volume_m3_from_wet_weight_kg(float64 wet_weight_kg) const
{  //Warning check this
   // Note that density will never be 0.0
   float64 density_kg_m3 = get_density_kg_m3();
   float64 volume = ((density_kg_m3 == 0) || (wet_weight_kg == 0)) ? 0.0 :
       wet_weight_kg  / density_kg_m3;
   return volume;
}
//_2004-04-04___________________________________________________________________
float64 Matter_wet::get_density_kg_m3()                                    const
{  return
      has_known_specific_gravity()
      ? get_specific_gravity_true() * water_density_kg_m3  // based on SG
      : Matter::get_density_kg_m3();                        // base on mass/vol
}
      // Warning derived classes must either implement get_density_kg_m3()
      // or get_specific_gravity_true();
//______________________________________________________________________________
float64 Matter_wet::get_volume_m3()                                        const
{  float64 mass_wet_kg = wet_kg();
   return has_known_specific_gravity()
      ? water_density_kg_m3 / get_specific_gravity_true() * mass_wet_kg
      : calc_volume_m3_from_wet_weight_kg(mass_wet_kg);
}
//______________________________________________________________________________
float64 Matter_wet::wet_kg()                                               const
{  return get_wet_in(UC_kg_mass);
}
//______________________________________________________________________________
float64 Matter_wet::get_wet_in(CORN::Units_code preferred_units)           const
{  return
      ref_mass().get_in_units(preferred_units)
         + get_water().get_in_units(preferred_units);                            //110727
}
//_2011-07-31___________________________________________________________________
const Water &Matter_wet::add_water
(const Water &water_to_add)                                        modification_
{
   // NYI adjust the biomatter temperature by the water temperature
   // proportionally. May need to adjust by ?latent heat?,
   // but I think it is sufficient to do a simple proportion since the biomatter
   // is likely going to be lagoon manure which is mostly water already. - RLN

   // Actually I think this should use specific heat
   //  something like: energy_kW = mass * specific_heat_water * (curr mass / added mass)
   mod_water().add(water_to_add);                                                //110701
   return get_water();
}
//______________________________________________________________________________
float64 Physical::Mass::merge_intensive_property
(float64 augend_quality
,float64 addend_quality
,float64 addend_mass)                                                      const
{  // addend it the number to be added,  augend is the number to be added to. (this is the augend)
   float64 result = augend_quality;
   if (addend_quality != augend_quality)                                         //050211
   {  // The qualities dont match so we use a weighted average                  //050211
      //Not sure if I want to have the augend keep it's intensive property if the addend_quality is 0.0 (which might be a default unknown value) //100316
      float64 augend_mass = kg();
      if (CORN::is_approximately<float64>(addend_mass,0.0,0.000001))
         result = augend_quality;
      else  if (CORN::is_approximately<float64>(augend_mass,0.0,0.000001))
         result = addend_quality; // no change
      else
      {
         float64 sum_mass = addend_mass + augend_mass;

         //100901 Need to check this,
         // it may need to be  (augend_quality * get_mass() + addend_quality*addend_mass) / sum_mass

         float64 addend_fract_of_sum = !CORN::is_approximately<float64>(sum_mass,0.0,0.000001) ? addend_mass / sum_mass : 0.0;
         float64 augend_fract_of_sum = !CORN::is_approximately<float64>(sum_mass,0.0,0.000001) ? augend_mass / sum_mass : 0.0;
         float64 weighted_avg = addend_quality * addend_fract_of_sum + augend_quality * augend_fract_of_sum;
         result = weighted_avg;                                                  //050303
      }
   }
   return result;
}
//_2003-09-16______________________________________________________________________________
} // namespace Physical
