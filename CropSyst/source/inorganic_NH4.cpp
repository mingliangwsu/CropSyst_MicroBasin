#include "land_unit_sim.h"

namespace CropSyst {

//______________________________________________________________________________
float32 humid_MAX_pH_above_7_ammonium_loss [6][4]   =
{// SB  drib  incrp  inject
 {0.20, 0.15, 0.10,   0.01}, // Urea
 {0.20, 0.15, 0.10,   0.01}, // UAN
 {0.40, 0.30, 0.10,   0.01}, // AS    {Dribble estimated}
 {0.20, 0.15, 0.10,   0.01}, // AN    {Dribble estimated}
 {0.02, 0.02, 0.02,   0.02}, // AA    {Gas can only be injected}
 {0.30, 0.20, 0.10,   0.01}  // ANS {Added by RLN these are only estimates}      120402
};
float32 subhumid_MAX_pH_above_7_ammonium_loss [6][4]   =
{// SB  drib  incrp  inject
 {0.30, 0.20, 0.10,   0.01}, // Urea
 {0.30, 0.20, 0.10,   0.01}, // UAN
 {0.50, 0.40, 0.20,   0.01}, // AS   {Dribble estimated}
 {0.25, 0.20, 0.15,   0.01}, // AN   {Dribble estimated}
 {0.03, 0.03, 0.03,   0.03}, // AA   {Gas can only be injected}
 {0.30, 0.30, 0.30,   0.01}  // ANS {Added by RLN these are only estimates}      120402
};
float32 dry_MAX_pH_above_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 {0.40, 0.30, 0.10,   0.01}, // Urea
 {0.40, 0.30, 0.10,   0.01}, // UAN
 {0.60, 0.50, 0.30,   0.01}, // AS    {Dribble estimated}
 {0.30, 0.25, 0.20,   0.01}, // AN    {Dribble estimated}
 {0.05, 0.05, 0.05,   0.05}, // AA    {Gas can only be injected}
 {0.50, 0.30, 0.25,   0.01}  // ANS {Added by RLN these are only estimates}      120402
};
float32 humid_MIN_pH_above_7_ammonium_loss [6][4]   =
{// SB  drib  incrp  inject
 {0.01, 0.01, 0.01,   0.01}, // Urea
 {0.01, 0.01, 0.01,   0.01}, // UAN
 {0.01, 0.01, 0.01,   0.01}, // AS
 {0.01, 0.01, 0.01,   0.01}, // AN
 {0.01, 0.01, 0.01,   0.01}, // AA  {Gas can only be injected}
 {0.01, 0.01, 0.01,   0.01}, // ANS {Added by RLN these are only estimates}      120402

};
float32 subhumid_MIN_pH_above_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 {0.02, 0.02, 0.01,   0.01},  // Urea
 {0.02, 0.02, 0.02,   0.01},  // UAN
 {0.02, 0.01, 0.01,   0.01},  // AS
 {0.02, 0.01, 0.01,   0.01},  // AN
 {0.01, 0.01, 0.01,   0.01},  // AA  {Gas can only be injected}
 {0.02, 0.01, 0.01,   0.01}   // ANS {Added by RLN these are only estimates}     120402
};
float32 dry_MIN_pH_above_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 {0.02, 0.02, 0.01,   0.01}, // Urea
 {0.02, 0.02, 0.01,   0.01}, // UAN
 {0.05, 0.04, 0.01,   0.01}, // AS
 {0.05, 0.04, 0.01,   0.01}, // AN
 {0.01, 0.01, 0.01,   0.01}, // AA  {Gas can only be injected}
 {0.05, 0.04, 0.01,   0.01}  // ANS {Added by RLN these are only estimates}     120402
};
float32 humid_MAX_pH_below_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 { 0.05, 0.05,  0.00, 0.01}, // Urea
 { 0.05, 0.05,  0.00, 0.01}, // UAN
 { 0.00, 0.00,  0.00, 0.00}, // AS
 { 0.00, 0.00,  0.00, 0.00}, // AN
 { 0.00, 0.00,  0.00, 0.00}, // AA
 { 0.00, 0.00,  0.00, 0.00}  // ANS {Added by RLN these are only estimates}     120402
};
float32 subhumid_MAX_pH_below_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 { 0.30, 0.20,  0.02, 0.01}, // Urea
 { 0.15, 0.10,  0.02, 0.01}, // UAN
 { 0.02, 0.02,  0.02, 0.01}, // AS
 { 0.02, 0.02,  0.02, 0.01}, // AN
 { 0.02, 0.02,  0.02, 0.01}, // AA
 { 0.02, 0.02,  0.02, 0.01}  // ANS {Added by RLN these are only estimates}     120402
};
float32 dry_MAX_pH_below_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 { 0.40, 0.30,  0.02, 0.01}, // Urea
 { 0.20, 0.15,  0.02, 0.01}, // UAN
 { 0.02, 0.02,  0.02, 0.01}, // AS
 { 0.02, 0.02,  0.02, 0.01}, // AN
 { 0.02, 0.02,  0.02, 0.01}, // AA
 { 0.02, 0.02,  0.02, 0.01}  // ANS {Added by RLN these are only estimates}     120402
};
float32 humid_MIN_pH_below_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 { 0.01, 0.01,  0.01, 0.01}, // Urea
 { 0.01, 0.01,  0.01, 0.01}, // UAN
 { 0.00, 0.00,  0.00, 0.00}, // AS
 { 0.00, 0.00,  0.00, 0.00}, // AN
 { 0.00, 0.00,  0.00, 0.00}, // AA
 { 0.00, 0.00,  0.00, 0.00}  // ANS {Added by RLN these are only estimates}     120402
};
float32 subhumid_MIN_pH_below_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 { 0.05, 0.02,  0.01, 0.01}, // Urea
 { 0.02, 0.02,  0.01, 0.01}, // UAN
 { 0.01, 0.01,  0.01, 0.01}, // AS
 { 0.01, 0.01,  0.01, 0.01}, // AN
 { 0.01, 0.01,  0.01, 0.01}, // AA
 { 0.01, 0.01,  0.01, 0.01}  // ANS {Added by RLN these are only estimates}     120402
};
float32 dry_MIN_pH_below_7_ammonium_loss[6][4]   =
{// SB  drib  incrp  inject
 { 0.05, 0.02,  0.01, 0.01}, // Urea
 { 0.02, 0.02,  0.01, 0.01}, // UAN
 { 0.01, 0.01,  0.01, 0.01}, // AS
 { 0.01, 0.01,  0.01, 0.01}, // AN
 { 0.01, 0.01,  0.01, 0.01}, // AA
 { 0.01, 0.01,  0.01, 0.01}  // ANS {Added by RLN these are only estimates}      120402
};
//______________________________________________________________________________
float64 CropSyst::Land_unit_simulation_VX::fract_inorganic_NH4_to_soil
(Ammonium_source  ammonium_source
,NH4_Appl_method  NH4_appl_method
,bool NH4_volatilization_calculated                                              //990228
,float64  NH4_volatilization
  //When NH4 is applied with no organic N A number here not 0 will override any
  //selections made by the radio buttons and computed by the model.*/
,float64 soil_cation_exchange_capacity
,float64 soil_pH)
{
   float64 return_fract_inorganic_NH4_to_soil;
   if (!NH4_volatilization_calculated)                                           //990228
     return_fract_inorganic_NH4_to_soil = 1-(NH4_volatilization/100);
   else
   { float64 F_cation_exchange_cap = CORN_must_be_between
       ((1.0 - (soil_cation_exchange_capacity - 10.0)/15.0),   0.0, 1.0);
     // his equation thresholds 10 <= CEC < 25
     float64 WES_in_2_days = m_to_mm(wettings.sum_last(2)); // Water entering the soil in the last 2 days
     float64 WES_in_7_days = m_to_mm(wettings.sum_last(7)); // Water entering the soil in the last 7 days
     float32 range = 0;
     float32 minimum = 0;
     if (soil_pH > 7.00000001)
     {  if (WES_in_7_days < 3.0)
        {  range   = dry_MAX_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method]
                   - dry_MIN_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method];
           minimum = dry_MIN_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method];
        }
        if (WES_in_7_days >= 3.0)
        {  range   = subhumid_MAX_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method]
                   - subhumid_MIN_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method];
           minimum = subhumid_MIN_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method];
        }
        if (WES_in_2_days > 12)
        {  range   = humid_MAX_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method]
                   - humid_MIN_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method];
           minimum = humid_MIN_pH_above_7_ammonium_loss[ammonium_source][NH4_appl_method];
        }
     }
     else
     {  if (WES_in_7_days < 3.0)
        {  range   = dry_MAX_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method]
                   - dry_MIN_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method];
           minimum = dry_MIN_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method];
        }
        if (WES_in_7_days >= 3.0)
        {  range   = subhumid_MAX_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method]
                   - subhumid_MIN_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method];
           minimum = subhumid_MIN_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method];
        }
        if (WES_in_2_days > 12)
        {  range   = humid_MAX_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method]
                   - humid_MIN_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method];
           minimum = humid_MIN_pH_below_7_ammonium_loss[ammonium_source][NH4_appl_method];
        }
     }
     float64 NH4_volatilization = (float64)minimum + (float64)range * F_cation_exchange_cap;
     return_fract_inorganic_NH4_to_soil = 1 - NH4_volatilization;
  }
  return return_fract_inorganic_NH4_to_soil;
}
//______________________________________________________________________________
} // namespace CropSyst

