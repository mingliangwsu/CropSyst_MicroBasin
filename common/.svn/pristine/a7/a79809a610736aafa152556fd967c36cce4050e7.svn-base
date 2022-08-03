#include "ammonical_N.h"
#include <math.h>
//______________________________________________________________________________
static const float64 adapted_acid_dissociation_constant_for_NH3 = 8.10E-11;  //100702 4.04e-10;
   // adapted_acid_dissociation_constant_for_NH3 (Ka) was in cell Main:[N4] in Nicole's spreadsheet

//______________________________________________________________________________
Ammoniacal_nitrogen::Ammoniacal_nitrogen
(const Physical::Temperature  & _ambient_temperature
//160105BRC //,const float64 &_pH
,float64 &_pH  //160105BRC removed const
,const Physical::Matter &of_matter
)                                                                                //100819
: Mass_nitrogen(0,UC_kg_mass,of_matter)
, ambient_temperature(_ambient_temperature)
, pH(_pH) // Currently this is a constant, but it is likely to be adjustable and will be adjusted by CANMS
, TAN_N_mass(mod_amount())                                                       //150215
{}
//______________________________________________________________________________
void Ammoniacal_nitrogen::update()
{  // fraction existing as NH3-N  (Monteny, 1998)
   //141125BRC This function assigns a wrong number to NH3_N, cannot use fract_NH3_N on a mass
   /*float64 Ka = adapted_acid_dissociation_constant_for_NH3;
   float64 fract_NH3_N
    = 1.0 / (1.0 + (pow(10.0 ,-pH)
      / (Ka * pow(1.07 , ((ambient_temperature + 273.0) - 293.0)))));
   NH3_N = TAN_N_mass * fract_NH3_N;                                             //141125BRC fract_NH3_N is concentration fraction, not mass
   NH4_N = TAN_N_mass - NH3_N;
*/
}
//______________________________________________________________________________
float64 Ammoniacal_nitrogen::calc_fraction_ammonia()                       const//141125BRC
{
   float64 Ka = adapted_acid_dissociation_constant_for_NH3;
   float64 fract_NH3_N
   //160106BRC// = 1.0 / (1.0 + (pow(10.0 ,-pH)
   = 1.0 / (1.0 + (pow(10.0 ,-get_pH())   //160106BRC
      / (Ka * pow(1.07 , ((ambient_temperature.kelvin()/*150217 + 273.0*/ ) - 293.0)))));
   return fract_NH3_N;
}
//______________________________________________________________________________
float64 Ammoniacal_nitrogen::multiply_by(float64 multiplier)       modification_
{  //NH4_N *= multiplier;  //141125BRC
   //NH3_N *= multiplier; //141125BRC
   return Physical::Mass_common::multiply_by(multiplier);                        //150215
}
//_2011-07-27___________________________________________________________________
float64 Ammoniacal_nitrogen::add(const Physical::Mass &addend)     modification_
{  const Ammoniacal_nitrogen *as_ammonical_N = dynamic_cast<const Ammoniacal_nitrogen *>(&addend);
   /*if (as_ammonical_N) //141125BRC
   {  NH4_N += as_ammonical_N->NH4_N; //141125BRC
      NH3_N += as_ammonical_N->NH3_N; //141125BRC
   };*/
   return Physical::Mass_common::add(addend);
}
//_2011-07-27___________________________________________________________________
float64 Ammoniacal_nitrogen::take_NH4_N_mass
(float64 NH4_N_mass_given)                                         modification_
{  TAN_N_mass += NH4_N_mass_given;
         //NH4_N += NH4_N_mass_given; //141125BRC
         return NH4_N_mass_given;
}
//_________________________________________________________________141201BRC____
float64 Ammoniacal_nitrogen::give_N_mass
(float64 N_mass_requested)                                         modification_
{  float64 N_given =
                  std::min<float64>(N_mass_requested,TAN_N_mass);
         TAN_N_mass -= N_given;
         return N_given;
}
//______________________________________________________________________________
float64 Ammoniacal_nitrogen::give_NH4_N_mass
(float64 NH4_N_mass_requested)                                     modification_
{  float64 NH4_N_given =
                  std::min<float64>(NH4_N_mass_requested,get_NH4_N());
         TAN_N_mass -= NH4_N_given;
         //NH4_N -= NH4_N_given; //141125BRC
         return NH4_N_given;
}
//______________________________________________________________________________
float64 Ammoniacal_nitrogen::give_NH3_N_mass
(float64 NH3_N_mass_requested)                                     modification_
{  float64 NH3_N_given =
                  std::min<float64>(NH3_N_mass_requested,get_NH3_N());
         TAN_N_mass -= NH3_N_given;
         //NH3_N -= NH3_N_given;                                                 //141125BRC
         return NH3_N_given;
}
//______________________________________________________________________________

