#include <corn/math/moremath.h>
#include "pedotransfer_saxton_2006.h"
//One cubic foot (28.32 dm3) of gravel typically weighs about 100 pounds (45 kg)
// http://en.wikipedia.org/wiki/Gravel
//______________________________________________________________________________
Pedotransfer_functions_Saxton_2006::Pedotransfer_functions_Saxton_2006
   (float32 &_sand, float32 &_clay, float32 &_silt
   // The following terms are specific to Saxton2006
   ,float32 &_organic_matter              // Assumed fixed
   // The following are the output terms.
   ,float32 &_saturation                  ,bool saturation_fixed
   ,float32 &_vol_WC_at_1500              ,bool vol_WC_at_1500_fixed
   ,float32 &_vol_WC_at_FC                ,bool vol_WC_at_FC_fixed
//140416  ,float32 &_vol_WC_at_33                ,bool vol_WC_at_33_fixed
   ,float32 &_sat_hydraul_cond_m_d        ,bool sat_hydraul_cond_m_d_fixed
   ,float32 &_bulk_density                ,bool bulk_density_fixed
   ,float32 &_soil_b                     //140416 ,bool soil_b_fixed
   ,float32 &_air_entry_pot               //140416 ,bool air_entry_pot_fixed
   ,float32 &_porosity                    ,bool porosity_fixed
   ,float32 & _water_pot_at_FC         ,bool water_pot_at_FC_fixed               //130326
   )                  //080419
: Pedotransfer_functions_abstract
   (_sand, _clay, _silt
   // The following terms are specific to Saxton2006
   // The following are the output terms.
   ,_saturation                  , saturation_fixed
   ,_vol_WC_at_1500              , vol_WC_at_1500_fixed
   ,_vol_WC_at_FC                , vol_WC_at_FC_fixed
//140416    ,_vol_WC_at_33                , vol_WC_at_33_fixed
   ,_sat_hydraul_cond_m_d        , sat_hydraul_cond_m_d_fixed
   ,_bulk_density                , bulk_density_fixed
   ,_soil_b                      //140416 , soil_b_fixed
   ,_air_entry_pot               //140416 ,air_entry_pot_fixed
   ,_porosity                    , porosity_fixed
   ,_water_pot_at_FC             ,water_pot_at_FC_fixed
   )                               //080419
,organic_matter      (_organic_matter)
{}
//______________________________________________________________________________
float Pedotransfer_functions_Saxton_2006::get_vol_WC_at_1500(bool fixed_or_based_on_texture_only) // similar to PWP
{  // Note these are always based on texture
   // Saxton 2005 equation 1
   if (vol_WC_at_1500_quality.get() != fixed_quality)
   {  float32 S   = sand/100.0;
      float32 C   = clay/100.0;
      float32 OM  = organic_matter/100.0;
      // The following equations and variable names are taken directly from Saxton's 2006 paper.
      float32 vol_WC_at_1500t = -0.024 * S + 0.487 * C + 0.006 * OM + 0.005 * (S * OM) - 0.013 * (C * OM) + 0.068 * (S * C) + 0.031;
      float32 vol_WC_at_1500_calc = vol_WC_at_1500t + 0.14 * vol_WC_at_1500t - 0.02;
      CORN::Quality vol_WC_at_1500_quality = quality_calculated_from(fixed_quality);
      set_vol_WC_at_1500(vol_WC_at_1500_calc,vol_WC_at_1500_quality);
   }
/*
Function Theta_33_Cmpl_newSaxBD(Theta_33 As Double, Theta_s As Double, Theta_s_BD As Double)
'as opposed to the Theta_33_Cmpl_newSax function this function calculates Theta at -33 J/kg
' corrected for (differing-from-average) bulk density BD (g cm-3)

'Old from help-file (is actually not very stable):
'Dim rel_Sand As Single, rel_Clay As Single, rel_Silt As Single
'rel_Sand = Round((Sand / 100), 3)
'rel_Clay = Round((Clay / 100), 3)
'rel_Silt = Round((1 - rel_Sand - rel_Clay), 3)
'If rel_Silt = 0 Then rel_Silt = 0.001
'If Clay > 60 Then
'  Theta_33_Cmpl_newSaxBD = "clay out of defined range"
' Else
  'Theta_33_Cmpl_newSaxBD = Theta_33 + (-0.432 * rel_Clay / rel_Silt - 1.713 * _
  'rel_Clay + 2.102 / rel_Silt + 0.427) * (Theta_s_BD - Theta_s)

'New from paper (seems as if this is the only equation, where helpfile and paper differ - checked it):

Theta_33_Cmpl_newSaxBD = Theta_33 - 0.2 * (Theta_s - Theta_s_BD)

If Theta_s_BD - Theta_33_Cmpl_newSaxBD > 0.5 Then Theta_33_Cmpl_newSaxBD = Theta_s_BD - 0.5
' This is in accordance with descriptions in the helpfile

If Theta_33_Cmpl_newSaxBD > Theta_s_BD Then Theta_33_Cmpl_newSaxBD = 0.9999 * Theta_s_BD
' This I put myself

'End If
End Function
*/
   return vol_WC_at_1500;
}
//______________________________________________________________________________
float Pedotransfer_functions_Saxton_2006::get_vol_WC_at_FC(bool fixed_or_based_on_texture_only)           // m3/m3
{  // Note these are always based on texture
   // RS: NOT valid in case bulk density is adjusted!     RLN: Not sure how to interpret this statement
   // Saxton 2005 equation 2
   if (vol_WC_at_FC_quality.get() != fixed_quality)
   {  float32 S   = sand/100.0;
      float32 C   = clay/100.0;     // Not defined for clay > 60%
      float32 OM  = organic_matter/100.0;
      // The following equations and variable names are taken directly from Saxton's 2006 paper.
      float32 vol_WC_at_FCt = -0.251 * S + 0.195 * C + 0.011 * OM + 0.006 * (S*OM) - 0.027 * (C*OM) + 0.452 * (S*C) + 0.299;
      float32 vol_WC_at_FC_calc  = vol_WC_at_FCt + 1.283 * CORN_sqr(vol_WC_at_FCt) - 0.374 * vol_WC_at_FCt - 0.015;
      // Currently we are ignoring the organic matter quality because
      CORN::Quality vol_WC_at_FC_quality(quality_calculated_from(fixed_quality));
      set_vol_WC_at_FC(vol_WC_at_FC_calc,vol_WC_at_FC_quality);
   }
   return vol_WC_at_FC;
}
//______________________________________________________________________________
float Pedotransfer_functions_Saxton_2006::get_vol_WC_at_S_FC() //mutates_
{    // Not sure exactly what this is (computed from fixed)
   // Saxton 2005 equation 3
   {  float32 S   = sand/100.0;
      float32 C   = clay/100.0;
      float32 OM  = organic_matter/100.0;
      float32 vol_WC_at_S_33t = 0.278 * S + 0.034 * C + 0.022 * OM - 0.018 * (S*OM) - 0.027 * (C*OM) - 0.584 * (S*C) + 0.078;
      float32 vol_WC_at_S_33_calc = vol_WC_at_S_33t + 0.636 * vol_WC_at_S_33t - 0.107;
      // quality is always computed from fixed.
      vol_WC_at_S_FC = vol_WC_at_S_33_calc;
   }
   return vol_WC_at_S_FC;
}
//______________________________________________________________________________
/*140416
float Pedotransfer_functions_Saxton_2006::get_vol_WC_at_33(bool fixed_or_based_on_texture_only)           // m3/m3
{  // Note these are always based on texture
   // RS: NOT valid in case bulk density is adjusted!     RLN: Not sure how to interpret this statement
   // Saxton 2005 equation 2
   if (vol_WC_at_FC_quality.get() != fixed_quality)
   {  float32 S   = sand/100.0;
      float32 C   = clay/100.0;     // Not defined for clay > 60%
      float32 OM  = organic_matter/100.0;
      // The following equations and variable names are taken directly from Saxton's 2006 paper.
      float32 vol_WC_at_33t = -0.251 * S + 0.195 * C + 0.011 * OM + 0.006 * (S*OM) - 0.027 * (C*OM) + 0.452 * (S*C) + 0.299;
      float32 vol_WC_at_33_calc  = vol_WC_at_33t + 1.283 * CORN_sqr(vol_WC_at_33t) - 0.374 * vol_WC_at_33t - 0.015;
      // Currently we are ignoring the organic matter quality because
      CORN::Quality vol_WC_at_33_quality(quality_calculated_from(fixed_quality));
      set_vol_WC_at_33(vol_WC_at_33_calc,vol_WC_at_33_quality);
   }
   return vol_WC_at_33;
}
//______________________________________________________________________________
float Pedotransfer_functions_Saxton_2006::get_vol_WC_at_S_33() //mutates_
{    // Not sure exactly what this is (computed from fixed)
   // Saxton 2005 equation 3
   {  float32 S   = sand/100.0;
      float32 C   = clay/100.0;
      float32 OM  = organic_matter/100.0;
      float32 vol_WC_at_S_33t = 0.278 * S + 0.034 * C + 0.022 * OM - 0.018 * (S*OM) - 0.027 * (C*OM) - 0.584 * (S*C) + 0.078;
      float32 vol_WC_at_S_33_calc = vol_WC_at_S_33t + 0.636 * vol_WC_at_S_33t - 0.107;
      // quality is always computed from fixed.
      vol_WC_at_S_33 = vol_WC_at_S_33_calc;
   }
   return vol_WC_at_S_33;
}
//______________________________________________________________________________




*/
float Pedotransfer_functions_Saxton_2006::calc_saturation_based_on_texture(CORN::Quality &returned_quality)     // m3/m3
{  // Warning I am presuming this is saturation
   // Saxton 2005 equation 5
   if (saturation_quality.get() != fixed_quality)
   {  float32 S   = sand/100.0;
      // float32 C   = clay/100.0;
      // float32 OM  = organic_matter/100.0;
      // The following equations and variable names are taken directly from Saxton's 2006 paper.
      float32 vol_WC_at_satuation_calc  = vol_WC_at_FC + vol_WC_at_S_FC - 0.097 * S + 0.043;
      // Currently we are ignoring the organic matter quality
      CORN::Quality vol_WC_at_satuation_calc_quality(quality_calculated_from(vol_WC_at_FC_quality.worst(worst_quality(calculated_quality,fixed_quality)).get()));
      set_vol_WC_at_FC(vol_WC_at_satuation_calc,vol_WC_at_satuation_calc_quality);
      returned_quality.set(vol_WC_at_satuation_calc_quality);
   }
   return saturation;
}
//______________________________________________________________________________
float Pedotransfer_functions_Saxton_2006::get_air_entry_pot()          // J/kg
{  //Note the difference in UNITS for air entry potential and Tension
   // It appears the unit are equivelent (but only for water_, but
   // we are using a sign change
   // Saxton 2005 equation 4
   float64 air_entry_pot = 0.0;                                                  //101014
//140416 Claudio says now always calculated  if (air_entry_pot_quality.get() != fixed_quality)
   {  float32 S   = sand/100.0;
      float32 C   = clay/100.0;
      float32 air_entry_pot_t =
           - 21.67 * S
           - 27.93 * C - 81.97 * vol_WC_at_S_FC
           + 71.12 * (S * vol_WC_at_S_FC)
           +  8.29 * (C * vol_WC_at_S_FC)
           + 14.05 * (S * C) + 27.16;
      float32 air_entry_pot_calc =
         -(air_entry_pot_t + 0.02 * CORN_sqr(air_entry_pot_t) - 0.113 * air_entry_pot_t - 0.7);
      // Sign change is because CropSyst uses negative value for potentials

      // Limit added by Rolf Sommer (not sure why)
      if (air_entry_pot_calc > -0.5)
         air_entry_pot_calc = -0.5; // 'CHECK WITH Saxton!!!  (RLN check if this occurs)
      CORN::Quality air_entry_pot_calc_quality(quality_calculated_from(vol_WC_at_FC_quality.worst(fixed_quality).get()));
      set_air_entry_pot(air_entry_pot_calc/*140416 ,air_entry_pot_calc_quality*/);
   }
   return air_entry_pot;
}
//______________________________________________________________________________
// The following are adjustements for effects
//______________________________________________________________________________
Pedotransfer_functions_Saxton_2006_effective::Pedotransfer_functions_Saxton_2006_effective
   (float32 &_sand, float32 &_clay, float32 &_silt
   // The following terms are specific to Saxton2006
   ,float32 &_organic_matter              // Assumed fixed
   ,float32 &_salinity                    // Assumed fixed
   ,float32 &_gravel_pct_by_weight        // Assumed fixed
   ,float32 &_compaction                  // Assumed fixed
   // The following are the output terms.
   ,float32 &_saturation                  ,bool saturation_fixed
   ,float32 &_vol_WC_at_1500              ,bool vol_WC_at_1500_fixed
   ,float32 &_vol_WC_at_FC                ,bool vol_WC_at_FC_fixed
//140416   ,float32 &_vol_WC_at_33                ,bool vol_WC_at_33_fixed
   ,float32 &_sat_hydraul_cond_m_d        ,bool sat_hydraul_cond_m_d_fixed
   ,float32 &_bulk_density                ,bool bulk_density_fixed
   ,float32 &_soil_b                      ,bool soil_b_fixed
   ,float32 &_air_entry_pot              // ,bool air_entry_pot_fixed
   ,float32 &_porosity                   // ,bool porosity_fixed
   ,float32 & _water_pot_at_FC            ,bool water_pot_at_FC_fixed               //140416
   )                  //080419
: Pedotransfer_functions_Saxton_2006
   (_sand, _clay, _silt
   // The following terms are specific to Saxton2006
   // The following are the output terms.
   ,_organic_matter
   ,_saturation                  , saturation_fixed
   ,_vol_WC_at_1500              , vol_WC_at_1500_fixed
   ,_vol_WC_at_FC                , vol_WC_at_FC_fixed
   ,_sat_hydraul_cond_m_d        , sat_hydraul_cond_m_d_fixed
   ,_bulk_density                , bulk_density_fixed
   ,_soil_b                      //140416 , soil_b_fixed
   ,_air_entry_pot              //140416 , air_entry_pot_fixed
   ,_porosity                    , porosity_fixed
   ,_water_pot_at_FC             , water_pot_at_FC_fixed               //140416
   )                               //080419
,salinity            (_salinity)
,gravel_pct_by_weight(_gravel_pct_by_weight)
,compaction          (_compaction)
{}
//______________________________________________________________________________
float Pedotransfer_functions_Saxton_2006_effective::get_bulk_density_with_compaction()
{  CORN::Quality bulk_density_quality;
   float normal_bulk_density = Pedotransfer_functions_Saxton_2006::get_bulk_density(bulk_density_quality);
   // compaction ranges between 0.90 and 1.23
   float64 bulk_density_density_adj = normal_bulk_density * compaction; // WARNING I THINK COMPACTION
   return bulk_density_density_adj;                                              //101014
}
//_2008-04-30___________________________________________________________________

/*
Option Explicit

Function VG_m_value(n As Double)
'm = van Genuchten soil water retention curve parameter

VG_m_value = 1 - 1 / n

End Function

Function Theta_h_VG(h As Double, Theta_s As Double, Theta_r As Double, alpha As Double, _
n As Double, m As Double)
'Calculate water content at a certain matric potential (h) according to the classical
'van Genuchten equation (here air entry = 0; as opposed to the so-called 'modified VG'
'where air-entry can be set by the user)

Theta_h_VG = Theta_r + ((Theta_s - Theta_r) / ((1 + (alpha * h) ^ n) ^ m))

End Function

Function Theta_h_Cmpl(h As Double, Theta_s As Double, Air_entry As Double, B As Double)

'Calculate water content at a certain matric potential (h) according to the Campbell model

If h >= Air_entry Then
  Theta_h_Cmpl = Theta_s
Else
   If Theta_s = 0 Or Air_entry = 0 Or B = 0 Then
    Theta_h_Cmpl = ""
   Else
    Theta_h_Cmpl = Theta_s * (h / Air_entry) ^ (-1 / B)
   End If
End If
End Function

Function h_Theta_Cmpl(Theta As Double, Theta_s As Double, Air_entry As Double, B As Double)

'Calculate matric potential (h) at a certain water content according to the Campbell model

If Theta_s = 0 Or Air_entry = 0 Or B = 0 Then
   h_Theta_Cmpl = ""
Else
    h_Theta_Cmpl = Air_entry * (Theta / Theta_s) ^ (-B)
End If

If h_Theta_Cmpl >= Air_entry Then h_Theta_Cmpl = Air_entry

End Function

Function conv_Ks(Ks As Double)
'input unit of Ks is (kg s m-3)
'output unit is (cm day-1)

conv_Ks = Ks / 9.8 / 86400 * 10

End Function

Function B_Cmpl_Rose(Interc_Rose_B As Double, Slope_Rose_B As Double, Sw_match _
As Double, m As Double, n As Double, alpha As Double, Theta_s As Double, Theta_r As Double)
'Unit of result is (cm) or (hPa)

Dim h_match As Double, Theta_match As Double, B_Cmpl_Rose_org As Double

Theta_match = Sw_match * (Theta_s - Theta_r) + Theta_r

h_match = ((((Theta_r - Theta_s) / (Theta_r - Theta_match)) ^ (1 / m) - 1) ^ (1 / n)) / alpha

' old coming from Rolf' previous calculations
' B_Cmpl_Rose = Interc_Rose_B + Slope_Rose_B * (1 / (m / (1 - m) * (1 - Sw_match ^ (1 / m))))

' new:
B_Cmpl_Rose_org = (h_match * alpha * m * n * (alpha * h_match) ^ (n - 1) * (Theta_match - Theta_r)) / _
                 (Theta_match * (1 + (alpha * h_match) ^ n))

B_Cmpl_Rose = Interc_Rose_B + Slope_Rose_B * (1 / B_Cmpl_Rose_org)

'Calculates Campbell Air-Entry value on the basis of van-Genuchten data (in fact m only)
'produced by the Rosetta software (- works however with any van-Genuchten data set).

'See Lenhard et al., 1989 (J. Irrig. & Drain. Engin. 115) page 746, equation 10.

'DESCRIPTION for old: Linear regression on top of this is necessary to account for the fact that the
'Campbell model and not Brooks-Corey was used. (Should be possible to come up with
'a "new" similar equation, though, following the "recipe" of Lenhard et al.)

End Function

Function AE_Cmpl_Rose(Interc_Rose_AE As Double, slope_Rose_AE As Double, _
alpha As Double)

AE_Cmpl_Rose = Interc_Rose_AE + slope_Rose_AE * 1 / alpha

'Calculates Campbell Air-Entry value on the basis of van-Genuchten data (alpha only)
'produced by the Rosetta software (- works however with any van-Genuchten data set).

'This is not based on any previous publication but own "invention"

End Function





Function Theta_1500_Cmpl_newSax(Sand As Double, Clay As Double, SOM As Double)
'New pedotransfer function of Saxton to calculate residual water content (PWP)
' Sand and Clay in %-units, SOM (=soil organic matter) in (gSOM/100gSoil)
' also valid in case bulk density is adjusted

Dim Theta_temp2 As Double, rel_Sand As Double, rel_Clay As Double

rel_Sand = Sand / 100
rel_Clay = Clay / 100

If Clay > 60 Then
  Theta_1500_Cmpl_newSax = "clay out of defined range"
Else

  Theta_temp2 = -0.024 * rel_Sand + 0.487 * rel_Clay + 0.006 * SOM + 0.005 * _
  (rel_Sand * SOM) - 0.013 * (rel_Clay * SOM) + 0.068 * (rel_Sand * rel_Clay) + 0.031

  Theta_1500_Cmpl_newSax = Theta_temp2 + 0.14 * Theta_temp2 - 0.02
End If
End Function

Function Theta_s_Cmpl_newSax(Sand As Double, Clay As Double, SOM As Double, Theta_33 As Double)
'New pedotransfer function of Saxton to calculate saturated water content
' Sand and Clay in %-units, SOM (=soil organic matter) in (gSOM/100gSoil)
' Note: NOT valid in case bulk density is adjusted!

Dim Theta_S_33 As Double, Theta_s_33_t As Double, rel_Sand As Double, rel_Clay As Double

rel_Sand = Sand / 100
rel_Clay = Clay / 100

If Clay > 60 Then
  Theta_s_Cmpl_newSax = "clay out of defined range"
Else
   Theta_s_33_t = 0.278 * rel_Sand + 0.034 * rel_Clay + 0.022 * SOM - 0.018 * _
  (rel_Sand * SOM) - 0.027 * (rel_Clay * SOM) - 0.584 * (rel_Sand * rel_Clay) + 0.078

  Theta_S_33 = Theta_s_33_t + 0.636 * Theta_s_33_t - 0.107
  '???strange equation - why not shorten to 1.636*Theta_S_33_t - 0.107 ????
  '- maybe typo (e.g. missing '^2')

  Theta_s_Cmpl_newSax = Theta_33 + Theta_S_33 - 0.097 * rel_Sand + 0.04

End If
End Function
Function Theta_S_Cmpl_newSaxBD(BD As Double)
'as opposed to the Theta_S_Cmpl_newSax function this function calculates Theta_s based on
'a given bulk density BD (g cm-3)

Theta_S_Cmpl_newSaxBD = 1 - (BD / 2.65)

End Function


Function AirEntry_Cmpl_newSax(Sand As Double, Clay As Double, SOM As Double)

End Function

Function B_Cmpl_newSax(Theta_33 As Double, Theta_1500 As Double)
'New pedotransfer function of Saxton to calculate the Campbell B value
' also valid in case bulk density is adjusted

If Theta_33 = 0 Then
  B_Cmpl_newSax = ""
  Else
  If Theta_33 < Theta_1500 Then
   B_Cmpl_newSax = 13 'high B choosen in this case - quite arbitrarily chosen
   Else
   B_Cmpl_newSax = (Log(1500) - Log(33)) / (Log(Theta_33) - Log(Theta_1500))
  'synonymous to the old procedure in CropSyst
   If B_Cmpl_newSax > 30 Then B_Cmpl_newSax = 30
  End If
End If

End Function

Function A_Cmpl_newSax(Theta_33 As Double, B As Double)
'New pedotransfer function of Saxton to calculate the Campbell A value
' also valid in case bulk density is adjusted

If B = 0 Then
  A_Cmpl_newSax = ""
Else
  A_Cmpl_newSax = Exp(Log(33) + B * Log(Theta_33))
  'synonymous to the old procedure in CropSyst
End If

End Function

Function Ks_Cmpl_newSax(Theta_s As Double, Theta_33 As Double, B As Double)
'New pedotransfer function of Saxton to calculate the saturated hydraulic conductivity
'Ks output unit is (cm/d); note: original output was (mm/hr), factor 2.4 for conversion
' also valid in case bulk density is adjusted

If B = 0 Then
  Ks_Cmpl_newSax = ""
Else
  Ks_Cmpl_newSax = 2.4 * (1930 * (Theta_s - Theta_33) ^ (3 - 1 / B))
End If
End Function

Function HTDUL(Matric_potential_DUL As Double)
'calculates hours to drainage upper limit(DUL)
'it is a simple linear scaling equation
'minimum time for drainage is 48 hours (two days), maximum time (48+192=) 240 hours (ten days)
'minimum matric potential is -45 J/kg (NOT YET TRUE!!!), maximum is -15 J/kg

HTDUL = 48 + 192 * ((-Matric_potential_DUL - 15) / (45 - 15))

End Function

Function KSAP(B, SAT, Theta_DUL, HTDUL)
'calculates the apparent saturated hydraulic conductivity (cm/d)
'B = Campbell B value
'SAT = saturated water content
'FC = field capacity at "Ritchie value"
'HTDUL = hours to drain upper limit (DUL), i.e. field observation of drainage experiments

Dim m, DZ As Double
'DZ is layer thickness in meter
'm also known as Campbell-c

'Const Gr = 9.81  'gravitational acceleration (m/s2)
Const WD = 1000  ' (kg/m3)

DZ = 0.5

m = 2 * B + 3
                
'original was: KSAP = DZ * WD * SAT ^ m * (Theta_DUL ^ (1 - m) - SAT ^ (1 - m)) _
'                    / (Gr * HTDUL * 3600 * (m - 1))

'new - using factor 2.4 for converting from (mm/hr) to (cm/d) - is:

KSAP = 2.4 * DZ * WD * SAT ^ m * (Theta_DUL ^ (1 - m) - SAT ^ (1 - m)) / (HTDUL * (m - 1))

End Function

Function MPFC(Clay As Single, Silt As Single)

'MPFC = Matric potential (J/kg) at drainage upper limit DUL - ???according to Ritchie???

If Clay = 0 Then Clay = 0.1    'RS added to avoid crash of function

MPFC = (-13.833 * Log(Clay) + 10.356)

If Silt > 70 And Clay < 23 Then MPFC = -33

If MPFC > -15 Then MPFC = -15


'??? SHOULD THIS FUNCTION BE RESTRICTED TO LOWEST VALUES NOT LOWER THAN -45 J/kg????

End Function

Function Theta_DUL_Ritchie(Sand As Double, Clay As Double, BD As Double)
'calculate drainage upper limit according to the Ritchie equation (Ritchie et al., 1999
'Transaction of ASAE 42(6), p. 1609-1614
'BD = bulk density (g cm-3)

If Clay = 0 Then Clay = 0.1

Theta_DUL_Ritchie = BD * 0.186 * (Sand / Clay) ^ -0.141

End Function

Function Theta_PWP_Ritchie(Sand As Double)
'calculate PWP according to the Ritchie equation (Ritchie et al., 1999
'Transaction of ASAE 42(6), p. 1609-1614

Theta_PWP_Ritchie = 0.132 - 0.0000025 * Exp(0.105 * Sand)

End Function
*/



