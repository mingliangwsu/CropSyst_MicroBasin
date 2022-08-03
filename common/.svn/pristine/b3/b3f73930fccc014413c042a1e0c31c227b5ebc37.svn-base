#  include "corn/primitive.h"
#  include <math.h>
#  include "corn/math/moremath.h"
#  ifndef compareHPP
#     include "corn/math/compare.hpp"
#  endif
#include "soil/txtrhydr.h"
//______________________________________________________________________________
// Calculates hydraulic properties from texture
Soil_texture_hydraulics::Soil_texture_hydraulics
(float32 & _sand, float32 &_clay, float32 &_silt
,float32 & _saturation                  ,bool saturation_fixed
,float32 & _vol_WC_at_1500              ,bool vol_WC_at_1500_fixed
,float32 & _vol_WC_at_33                ,bool vol_WC_at_33_fixed
,float32 & _sat_hydraul_cond_m_d        ,bool sat_hydraul_cond_m_d_fixed
,float32 & _bulk_density                ,bool bulk_density_fixed
,float32 & _Campbell_b                  ,bool Campbell_b_fixed
,float32 & _air_entry_pot               ,bool air_entry_pot_fixed)
: sand(_sand)
, clay(_clay)
, silt(_silt)
, saturation                  (_saturation)
, vol_WC_at_1500              (_vol_WC_at_1500)
, vol_WC_at_33                (_vol_WC_at_33)
, sat_hydraul_cond_m_d        (_sat_hydraul_cond_m_d)
, bulk_density                (_bulk_density)
, geometric_mean_particle_size(0)
, Campbell_b                  (_Campbell_b)
, air_entry_pot               (_air_entry_pot)
, acoef_status                (unknown)
, bcoef_status                (unknown)
, saturation_status           (saturation_fixed?fixed:unknown)
//130326 NYN, water_pot_at_FC_status      (water_pot_at_FC_fixed ? fixed : unknown)          //130326
, water_pot_at_FC_status      (unknown)                                          //130326
, vol_WC_at_1500_status       (vol_WC_at_1500_fixed?fixed:unknown)
, vol_WC_at_33_status         (vol_WC_at_33_fixed?fixed:unknown)
, sat_hydraul_cond_m_d_status (sat_hydraul_cond_m_d_fixed?fixed:unknown)
, bulk_density_status         (bulk_density_fixed?fixed:unknown)
, GM_particle_size_status     (unknown)//geometric_mean_particle_size_fixed)
, Campbell_b_status           (Campbell_b_fixed?fixed:unknown)
, air_entry_pot_status        (air_entry_pot_fixed?fixed:unknown)
//130326, FC_status                   (vol_WC_at_33_fixed?fixed:unknown)                 //040912
//130326, PWP_status                  (vol_WC_at_1500_fixed?fixed:unknown)               //040912
{}
//________________________________________________________________constructor__/
float Soil_texture_hydraulics::get_acoef()
{  if (acoef_status == unknown)
   {  float sand_2 = sand * sand;
      acoef = exp(-4.396 - 0.0715 * clay -
              4.88e-4 * sand_2 - 4.285e-5 * sand_2 * clay);

//assert(false);
     // I think I had an error, the original document multiples the exponent by 100.0      //140419
     // I need to check the results


      acoef_status = computed_from_fixed;
   }
   return acoef;
}
//__________________________________________________________________get_acoef__/
float Soil_texture_hydraulics::get_bcoef()
{  if (bcoef_status == unknown)
   {  float sand_2 = sand * sand;
      float clay_2 = clay * clay;
      bcoef = - 3.140 - 0.00222 * clay_2 - 3.484e-5 * sand_2 * clay;
      bcoef_status = computed_from_fixed;
   }
   return bcoef;
}
//_1998-10-30_______________________________________________________get_bcoef__/
float Soil_texture_hydraulics::get_saturation_based_on_texture()
{  float32 sand_term = 7.251e-4 * sand ;
   float32 clay_term = 0.1276 * log10((double)clay);
   return  0.332 - sand_term+clay_term ;
}
//_1998-10-30_________________________________get_saturation_based_on_texture__/
float Soil_texture_hydraulics::get_saturation()
{  if (saturation_status < computed_from_fixed)
   {  if (saturation_status == unknown)
      {  saturation = get_saturation_based_on_texture();
         saturation_status = estimated;
      };
      if ((saturation_status == estimated) &&
          (bulk_density_status > estimated))
      {  saturation = 1.0 - get_bulk_density() / 2.65;
         saturation_status = computed_from_fixed;
      }
   }
   return saturation;
}
//_1998-10-30__________________________________________________get_saturation__/
float Soil_texture_hydraulics::get_WC_at_based_on_texture(float potential)
{  float result;
   float acoef_ = get_acoef();                                                   //040209
   float bcoef_ = get_bcoef();                                                   //040209
   if ((acoef_ == 0.0) || (bcoef_ == 0.0))                                       //040209
      result = 0.0;
   else  // potential will usually be either  15.0 or 0.33
   {  float32 base = ( (-potential/100.0) / acoef_);                             //040209
      float32 exponent = (1.0 / bcoef_);                                         //040209
      result = pow(base,exponent);
   }
   return result;
}
//_________________________________________________get_WC_at_based_on_texture__/
float  Soil_texture_hydraulics::calc_WC_at
(float potential
,float air_entry_pot_
,float Campbell_b_
,float saturation_)
{  float result =  pow((double)(potential / air_entry_pot_)
                      ,(double)(-1.0/Campbell_b_)) * saturation_;
   return  result;
}
//_________________________________________________________________calc_WC_at__/
float Soil_texture_hydraulics::get_WC_at
(float potential // -1500 or -33
,float current_vol_WC, Status &vol_WC_status
,bool either_fixed_or_based_on_texture)        // When false, the calculate based on texture
{  float result = current_vol_WC;
   if (vol_WC_status != fixed) // always return fixed
   {  if ((    (Campbell_b_status   > unknown)
            && (air_entry_pot_status> unknown)
            && (saturation_status   > unknown))
            && !either_fixed_or_based_on_texture)  // based on texture
      {  result = calc_WC_at(potential,get_air_entry_pot(),get_Campbell_b(),get_saturation());  //990525
         vol_WC_status = std::min<Status>(saturation_status,computed_from_fixed); // was simply saturated status  //080313
      }
      else
      {  result = get_WC_at_based_on_texture( potential);
         vol_WC_status = estimated;
      }
  }
  return result;
}
//__________________________________________________________________get_WC_at__/
float Soil_texture_hydraulics::get_vol_WC_at_1500(bool either_fixed_or_based_on_texture)  // similar to PWP
{  Status compute_status = vol_WC_at_1500_status;
   float64 a_good_WC_at_1500 = get_WC_at(-1500.0,vol_WC_at_1500,compute_status,either_fixed_or_based_on_texture);
   set_vol_WC_at_1500(a_good_WC_at_1500,compute_status);
   return vol_WC_at_1500;
}
//_1998-10-30______________________________________________get_vol_WC_at_1500__/
float Soil_texture_hydraulics::get_vol_WC_at_33(bool either_fixed_or_based_on_texture)  // similar to FC
{  Status compute_status = vol_WC_at_33_status;
   float64 a_good_WC_at_33 = get_WC_at(-33,vol_WC_at_33,compute_status,either_fixed_or_based_on_texture);
   set_vol_WC_at_33(a_good_WC_at_33,compute_status);
   return vol_WC_at_33;
}
//_1998-10-30________________________________________________get_vol_WC_at_33__/
float Soil_texture_hydraulics::get_sat_hydraul_cond_m_d()
{  if (sat_hydraul_cond_m_d_status == unknown)
   {  float sat = get_saturation();
      float clay_2 = clay * clay;
      float sat_hydraul_cond_cm_hr =  (sat != 0.0)
      ?	  exp((12.012 - 0.0755 * (float)sand)  +
             (- 3.895 + 0.03671 * (float)sand -
                        0.1103  * (float)clay +
                        8.7546e-4 * clay_2)
             / sat)
      : 0.0;
      Status new_sat_hydr_cond_status = std::min<Status>(computed_from_fixed,saturation_status);   //080313
      set_sat_hydraul_cond_m_d(sat_hydraul_cond_cm_hr * 24.0 / 100.0 //cm/hr -> m/day
          ,new_sat_hydr_cond_status);
   }
   return  sat_hydraul_cond_m_d;
}
//_1998-10-30________________________________________get_sat_hydraul_cond_m_d__/
float Soil_texture_hydraulics::get_sat_hydraul_cond_cm_hr()
{    return get_sat_hydraul_cond_m_d() / 24.0 * 100.0; // m/d->cm/hr
}
//_1898-10-30______________________________________get_sat_hydraul_cond_cm_hr__/
float Soil_texture_hydraulics::get_bulk_density_based_on_texture()
{  return (1.0 - get_saturation_based_on_texture() ) * 2.65;
}
//__________________________________________get_bulk_density_based_on_texture__/
float Soil_texture_hydraulics::calc_bulk_density_based_on_best_saturation()
{  return (1.0 - get_saturation() ) * 2.65;
}
//_2008-03-13______________________calc_bulk_density_based_on_best_saturation__/
float Soil_texture_hydraulics::get_bulk_density()
{  if (bulk_density_status == unknown)
   {  bulk_density = calc_bulk_density_based_on_best_saturation(); // 080313 was get_bulk_density_based_on_texture();
      bulk_density_status =
           (saturation_status==fixed) ? computed_from_fixed :                    //080313
            saturation_status;                                                   //080313
   }
   return bulk_density;
}
//_1998-10-30________________________________________________get_bulk_density__/
float Soil_texture_hydraulics::set_bulk_density(float _bulk_density, Status _status)
{  if (_status >= bulk_density_status)
   {  bulk_density = _bulk_density;
      bulk_density_status = _status;
   }
   return bulk_density;
}
//___________________________________________________________set_bulk_density__/
float Soil_texture_hydraulics::set_vol_WC_at_1500(float _vol_WC_at_1500,Status _status)
{  if (_status >= vol_WC_at_1500_status)
   {  vol_WC_at_1500 = _vol_WC_at_1500;
      vol_WC_at_1500_status = _status;
   }
   return vol_WC_at_1500;
}
//_________________________________________________________set_vol_WC_at_1500__/
float Soil_texture_hydraulics::set_vol_WC_at_33(float _vol_WC_at_33,Status _status)
{  if (_status >= vol_WC_at_33_status)
   {  vol_WC_at_33 = _vol_WC_at_33;
      vol_WC_at_33_status = _status;
   }
   return vol_WC_at_33;
}
//______________________________________________________________________________
float Soil_texture_hydraulics::set_sat_hydraul_cond_m_d(float _sat_hydraul_cond_m_d,Status _status)
{  if (_status >= sat_hydraul_cond_m_d_status)
   {  sat_hydraul_cond_m_d = _sat_hydraul_cond_m_d;
      sat_hydraul_cond_m_d_status = _status;
   }
   return sat_hydraul_cond_m_d;
}
//___________________________________________________set_sat_hydraul_cond_m_d__/
float Soil_texture_hydraulics::set_saturation(float _saturation,Status _status)
{  if (_status >= saturation_status)
   {  saturation = _saturation;
      saturation_status = _status;
   }
   return saturation;
}
//_2008-03-13__________________________________________________set_saturation__/
float Soil_texture_hydraulics::set_air_entry_pot(float _air_entry_pot,Status _status)
{  if (_status >= air_entry_pot_status)
   {  air_entry_pot = _air_entry_pot;
      air_entry_pot_status = _status;
   }
   return air_entry_pot;
}
//__________________________________________________________set_air_entry_pot__/
float Soil_texture_hydraulics::set_Campbell_b(float _Campbell_b,Status _status)
{  if (_status >= Campbell_b_status)
   {  Campbell_b = _Campbell_b;
      Campbell_b_status = _status;
   }
   return Campbell_b;
}
//_____________________________________________________________set_Campbell_b__/
float Soil_texture_hydraulics::get_geometric_mean_particle_size()
{ // I think in micro meters
  if (GM_particle_size_status == unknown)
  { geometric_mean_particle_size =
    exp(  2.302  * (silt / 100.0)                                                //980528
        - 0.602  * (clay / 100.0)                                                //980528
        + 4.7897 * (sand / 100.0)                                                //980528
        + 1.263  * CORN_sqr((sand/100.0)));                                      //980528
    GM_particle_size_status = computed_from_fixed;
  }
  return geometric_mean_particle_size;
}
//_1998-10-30________________________________get_geometric_mean_particle_size__/
float Soil_texture_hydraulics::calc_Campbell_b
(float WC_at_33_or_FC
,float WC_at_1500_or_PWP)
{  return CORN_ln(soil_water_pot_at_PWP / soil_water_pot_at_FC)
         /CORN_ln(WC_at_33_or_FC / WC_at_1500_or_PWP);
}
//_1999-03-21_________________________________________________calc_Campbell_b__/
float Soil_texture_hydraulics::get_Campbell_b()
{  if ((Campbell_b_status     == unknown) ||
       (vol_WC_at_33_status   == fixed) ||
       (vol_WC_at_1500_status == fixed))
   {  Campbell_b = calc_Campbell_b(get_vol_WC_at_33(true)  , get_vol_WC_at_1500(true));   //990321
      Campbell_b_status = std::min<Status>(estimated,std::min<Status>(vol_WC_at_33_status,vol_WC_at_1500_status));
   }
   return Campbell_b;
}
//_____________________________________________________________get_Campbell_b__/
float Soil_texture_hydraulics::calc_air_entry_pot
(float WC_at_33_or_FC
,float saturation_                                                               //040209
,float Campbell_b_)                                                              //040209
{  return soil_water_pot_at_FC *
       pow((double)(WC_at_33_or_FC / saturation_),(double)Campbell_b_);          //040209
}
//_1999-03-21______________________________________________calc_air_entry_pot__/
float Soil_texture_hydraulics::get_air_entry_pot()
{  if ((air_entry_pot_status == estimated) ||
       (air_entry_pot_status < vol_WC_at_33_status) ||
       (air_entry_pot_status < vol_WC_at_1500_status) ||
       (air_entry_pot_status < saturation_status))
   {  float air_entry_pot_based_on_texture_saturation = calc_air_entry_pot(get_vol_WC_at_33(true),get_saturation_based_on_texture(),get_Campbell_b());
      float new_air_entry_pot = air_entry_pot_based_on_texture_saturation
        * pow((double)(get_bulk_density()/get_bulk_density_based_on_texture()),(double)(0.67 * get_Campbell_b()));
      Status new_air_entry_pot_status = std::min<Status>(computed_from_fixed,std::min<Status>(Campbell_b_status,bulk_density_status)); //081014
      set_air_entry_pot(new_air_entry_pot,new_air_entry_pot_status );
   }
   return air_entry_pot;
}
//_1998-10-30_______________________________________________get_air_entry_pot__/
void Soil_texture_hydraulics::reset_questionable_states()
{  acoef_status                = (acoef_status == fixed)                 ? fixed : unknown;
   bcoef_status                = (bcoef_status == fixed)                 ? fixed : unknown;
   saturation_status           = (saturation_status == fixed)            ? fixed : unknown;
   vol_WC_at_1500_status       = (vol_WC_at_1500_status == fixed)        ? fixed : unknown;
   vol_WC_at_33_status         = (vol_WC_at_33_status == fixed)          ? fixed : unknown;
   bulk_density_status         = (bulk_density_status == fixed)          ? fixed : unknown;
   Campbell_b_status           = (Campbell_b_status == fixed)            ? fixed : unknown;
   air_entry_pot_status        = (air_entry_pot_status == fixed)         ? fixed : unknown;
   GM_particle_size_status     = (GM_particle_size_status == fixed)      ? fixed : unknown;
   sat_hydraul_cond_m_d_status = (sat_hydraul_cond_m_d_status == fixed)  ? fixed : unknown;
}
//______________________________________________________________________________
bool Soil_texture_hydraulics::recompute_every_thing()
{  float total_texture = sand+clay+silt;
   if (!CORN::is_approximately<float>(total_texture,100.0,1.0))
      return false;
   reset_questionable_states();
   get_saturation();
   get_bulk_density();
   get_air_entry_pot();                                                          //980528
   get_vol_WC_at_1500(false);
   get_vol_WC_at_33(false);
   get_sat_hydraul_cond_m_d();                                                   //980528
   //NYI get_geometric_mean_particle_size();
   return true;
}
//______________________________________________________________________________

