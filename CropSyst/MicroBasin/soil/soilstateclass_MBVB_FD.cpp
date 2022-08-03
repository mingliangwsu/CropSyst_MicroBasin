#include "soilstateclass.h"
//______________________________________________________________________________
#if (!defined (CROPSYST_HYDROLOGY) || defined(MBVB_FD))
void SoilStateClass::setSoilWater()
{
    int NN_max;

    NN_max = SoilProfileRef.Number_Of_Total_Nodes;

    for (int L = 1; L <= NN_max; L++) {

        #ifdef MBVB_FD
        Upper_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        New_Upper_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        Lower_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        New_Lower_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        #endif
        Water_Potential[L] = calc_h_Theta(/*LML 140611 Hourly_*/Water_Content[L]
                                , SoilProfileRef.Air_Entry_Potential[L]
                                , SoilProfileRef.Saturation_Water_Content[L]
                                , SoilProfileRef.b_Value[L]);
    }

    if (SoilProfileRef.Water_Table_Boundary == true) {
        for (int L = SoilProfileRef.Number_Of_Uninundated_Soil_Layers + 1; L <= NN_max; L++) {
          #ifdef MBVB_FD
          Upper_Water_Content[L] = SoilProfileRef.Saturation_Water_Content[L];
          Lower_Water_Content[L] = SoilProfileRef.Saturation_Water_Content[L];
          #endif
          Water_Potential[L] = SoilProfileRef.Air_Entry_Potential[L];
        }
    //Else
      //'RS: not required - is already set earlier (12 lines above)
      //'Water_Potential(Year, DOY, NN_max) = Water_Potential(Year, DOY, NN_max - 1)
    }
}
//______________________________________________________________________________
#endif

//______________________________________________________________________________
#if (!defined (CROPSYST_HYDROLOGY) || defined(MBVB_FD))
void SoilStateClass::setallSoilWater()
{

    int NL_max;

    NL_max = SoilProfileRef.NumberOfLayers();

    //Set all defined layer water contents to current water content of whole layer
    for (int L = 1; L <= NL_max; L++) {
        //Water_Content[L] = Hourly_Water_Content[L];
        set_water_content_volumetric_layer(L,/*LML 140611 Hourly_*/Water_Content[L]);
        Old_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        New_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        #ifdef MBVB_FD
        Upper_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        New_Upper_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        Old_Upper_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        Lower_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        New_Lower_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        Old_Lower_Water_Content[L] = /*LML 140611 Hourly_*/Water_Content[L];
        #endif

        Water_Potential[L] = calc_h_Theta(/*LML 140611 Hourly_*/Water_Content[L],
                                                     SoilProfileRef.Air_Entry_Potential[L],
                                                     SoilProfileRef.Saturation_Water_Content[L],
                                                     SoilProfileRef.b_Value[L]);
    }
}
#endif

//______________________________________________________________________________
#ifndef CROPSYST_FD
#ifdef MBVB_FD
void SoilStateClass::setSoilWaterByNewUpperAndLower(int LastLayer)
{
    for (int layer = 1; layer <= LastLayer; layer++) {
        Water_Content[layer] = (New_Upper_Water_Content[layer] * SoilProfileRef.Upper_Node_Soil_Volume[layer]
                            + New_Lower_Water_Content[layer] * SoilProfileRef.Lower_Node_Soil_Volume[layer])
                           / (SoilProfileRef.Upper_Node_Soil_Volume[layer] + SoilProfileRef.Lower_Node_Soil_Volume[layer]); //FMS Feb 28, 2014
        set_water_content_volumetric_layer(layer,Water_Content[layer]);         //LML 15/05/30
        //Hourly_Water_Content[layer] = get_liquid_water_content_volumetric(layer)/*Water_Content[layer]*/;
        Water_Potential[layer] = calc_h_Theta(Water_Content[layer], SoilProfileRef.Air_Entry_Potential[layer],
                                                    SoilProfileRef.Saturation_Water_Content[layer], SoilProfileRef.b_Value[layer]);
    }
}
#endif
#endif
//______________________________________________________________________________
#ifndef CROPSYST_FD
#ifdef MBVB_FD
double SoilStateClass::calcFDProfileWater()
{
    double sumstore;    //(m)
    int NL_max;
    //int NL;             //MS Feb 28, 2014

    sumstore = 0;
    NL_max = SoilProfileRef.NLmax;
    //NL = SoilProfileRef.NumberOfLayers();   //FMS Feb 28, 2014

    for (int layer = 1; layer <= NL_max; layer++) {
        sumstore += (Upper_Water_Content[layer] * SoilProfileRef.Upper_Node_Soil_Volume[layer]
                     + Lower_Water_Content[layer] * SoilProfileRef.Lower_Node_Soil_Volume[layer]) / WaterDensity_kg_m3;
    }

    return sumstore;
}
#endif
#endif

//______________________________________________________________________________
//140603 #ifndef CROPSYST_HYDROLOGY
#ifdef MBVB_FD
//140511 This is actually not used anymore
void SoilStateClass::ResetSoilWaterStatus(double *Initial_SavePot,double *Initial_Save_wu,double *Initial_Save_wl,
                         double *Upper_WC,double *Lower_WC)
{
    //Implement later M.Liu Jan 31, 2014
    int i;
    int m;
    m = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    for (i = 1; i <= m + 1; i++) {
        Water_Potential[i] = Initial_SavePot[i];
        Upper_Water_Content[i] = Initial_Save_wu[i];
        Lower_Water_Content[i] = Initial_Save_wl[i];
        New_Upper_Water_Content[i] = Upper_WC[i];
        New_Lower_Water_Content[i] = Lower_WC[i];
    }
}
#endif
//140603 #endif


#ifndef CROPSYST_VERSION
double SoilStateClass::getProfileNO3NMass()
{
    double total = 0;
    for (int layer = 1; layer <= SoilProfileRef.NumberOfLayers(); layer++) {
        total += Layer_Nitrate_N_Mass[layer];
    }
    return total;
}
//______________________________________________________________________________
double SoilStateClass::getProfileNH4NMass()
{
    double total = 0;
    for (int layer = 1; layer <= SoilProfileRef.NumberOfLayers(); layer++) {
        total += Layer_Ammonium_N_Mass[layer];
    }
    return total;
}
//______________________________________________________________________________
#endif
#ifndef CROPSYST_VERSION
double SoilStateClass::getTotalSOMCarbonMass()
{
    //(kgC/m2)
    double total = 0;
    for (int layer = 1; layer <= SoilProfileRef.NumberOfLayers(); layer++) {
        total += Layer_Carbon_Mass_In_Organic_Matter[layer];
    }
    return total;
}
//______________________________________________________________________________
double SoilStateClass::getTotalSOMNitrogenMass()
{
    //(kgN/m2)
    double total = 0;
    for (int layer = 1; layer <= SoilProfileRef.NumberOfLayers(); layer++) {
        total += Layer_Nitrogen_Mass_In_Organic_Matter[layer];
    }
    return total;
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SoilStateClass::TransferNutrientsBetweenLayers(Solute nutrient_lable,
  double fraction,int from_layer,int to_layer)
{
    //LML 141205 didn't update concentration, the concentration will be calculated whenever need.
    switch(nutrient_lable){
    case SL_Amonia:
        Layer_Ammonium_N_Mass[to_layer] += fraction * Layer_Ammonium_N_Mass[from_layer];
        Layer_Ammonium_N_Mass[from_layer] *= 1.0 - fraction;
        break;
    case SL_Nitrate:
        Layer_Ammonium_N_Mass[to_layer] += fraction * Layer_Ammonium_N_Mass[from_layer];
        Layer_Ammonium_N_Mass[from_layer] *= 1.0 - fraction;
        break;
    case SL_Phosphate:
        Layer_Phosphorus_Mass[to_layer] += fraction * Layer_Phosphorus_Mass[from_layer];
        Layer_Phosphorus_Mass[from_layer] *= 1.0 - fraction;
        break;
    default:
        std::clog<<"Nutrient doesn't exist!"
                 <<__FILE__
                 <<__LINE__
                 <<std::endl;
        assert(false);
    }
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SoilStateClass::UpdateSoilSoluteStateAfterUptake()
{
    //This is only a partial update that could not be done earlier in the day
    double Total_Potential_Nitrogen_Uptake =
            Total_Potential_Nitrate_N_Uptake + Total_Potential_Ammonium_N_Uptake;
    double NitrogenUptakeRatio(0);
    if (Total_Potential_Nitrogen_Uptake > 0)
        NitrogenUptakeRatio = Total_Actual_Nitrogen_Uptake / Total_Potential_Nitrogen_Uptake;
    assert(NitrogenUptakeRatio >= 0 && NitrogenUptakeRatio <= 1.0);              //140916LML
    double Total_Potential_P_Uptake = Total_Potential_Phosphorus_Uptake;
    double PhosphorusUptakeRatio(0);
    if (Total_Potential_P_Uptake > 0)
        PhosphorusUptakeRatio = Total_Actual_Phosphorus_Uptake / Total_Potential_P_Uptake;
    assert(PhosphorusUptakeRatio >= 0 && PhosphorusUptakeRatio <= 1.0);          //140916LML
    Total_Actual_Nitrate_N_Uptake = Total_Potential_Nitrate_N_Uptake * NitrogenUptakeRatio;
    Total_Actual_Ammonium_N_Uptake = Total_Potential_Ammonium_N_Uptake * NitrogenUptakeRatio;
    for (int L = 1; L <= num_layers; L++) {
        Layer_Actual_Nitrate_N_Uptake[L] = Layer_Potential_Nitrate_N_Uptake[L] * NitrogenUptakeRatio;
        Layer_Actual_Ammonium_N_Uptake[L] = Layer_Potential_Ammonium_N_Uptake[L] * NitrogenUptakeRatio;
        Layer_Actual_Phosphorus_Uptake[L] = Layer_Potential_Phosphorus_Uptake[L] * PhosphorusUptakeRatio;
        Layer_Nitrate_N_Mass[L] -= Layer_Actual_Nitrate_N_Uptake[L];
        Layer_Ammonium_N_Mass[L] -= Layer_Actual_Ammonium_N_Uptake[L];
        Layer_Phosphorus_Mass[L] -= Layer_Actual_Phosphorus_Uptake[L];
        if (Layer_Nitrate_N_Mass[L] < 0) Layer_Nitrate_N_Mass[L] = 0;
        if (Layer_Ammonium_N_Mass[L] < 0) Layer_Ammonium_N_Mass[L] = 0;
        if (Layer_Phosphorus_Mass[L] < 0) Layer_Phosphorus_Mass[L] = 0;
    }
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SoilStateClass::UpdateSoilState()
{
    Total_Nitrate_N_Mass = 0;
    Total_Ammonium_N_Mass = 0;
    Total_Phosphorus_Mass = 0;
    for (int L = 1; L <= num_layers; L++) {
        Total_Nitrate_N_Mass += Layer_Nitrate_N_Mass[L];
        Total_Ammonium_N_Mass += Layer_Ammonium_N_Mass[L];
        Total_Phosphorus_Mass += Layer_Phosphorus_Mass[L];
    }
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SoilStateClass::SetSCSSoilCurveNumbers()
{
    if (Hydrologic_Group.compare("A") == 0) {
        Fallow_CN_I = 59;
        Fallow_CN_II = 77;
        Fallow_CN_III = 89;
        Residue_CN_I_10Mg_per_Ha = 2;
        Residue_CN_II_10Mg_per_Ha = 6;
        Residue_CN_III_10Mg_per_Ha = 15;
    }
    else if (Hydrologic_Group.compare("B") == 0) {
        Fallow_CN_I = 72;
        Fallow_CN_II = 86;
        Fallow_CN_III = 94;
        Residue_CN_I_10Mg_per_Ha = 18;
        Residue_CN_II_10Mg_per_Ha = 35;
        Residue_CN_III_10Mg_per_Ha = 55;
    }
    else if (Hydrologic_Group.compare("C") == 0) {
        Fallow_CN_I = 80;
        Fallow_CN_II = 91;
        Fallow_CN_III = 97;
        Residue_CN_I_10Mg_per_Ha = 51;
        Residue_CN_II_10Mg_per_Ha = 70;
        Residue_CN_III_10Mg_per_Ha = 85;
    }
    else if (Hydrologic_Group.compare("D") == 0) {
        Fallow_CN_I = 85;
        Fallow_CN_II = 94;
        Fallow_CN_III = 98;
        Residue_CN_I_10Mg_per_Ha = 62;
        Residue_CN_II_10Mg_per_Ha = 79;
        Residue_CN_III_10Mg_per_Ha = 91;
    }
}
#endif
//______________________________________________________________________________
