#include "simulationbalanceclass.h"
#include <math.h>
//______________________________________________________________________________
SimulationBalanceClass::SimulationBalanceClass
(const CORN::Date &_today                                                        //150630RLN
,AllControlClass &_ControlRef
,clsSoil &_SoilRef)
: today(_today)                                                                   //150630RLN
,ControlRef(_ControlRef)
,SoilRef(_SoilRef)
{
}
//______________________________________________________________________________
void SimulationBalanceClass::CalculateDailyWaterBalance()
{
    int doy = today.get_DOY();
    double Final_Soil_Water_Profile = CalculateSoilWaterProfile_mm();
    double Infiltration = SoilRef.pSoilState->Daily_Infiltration;
    double Drainage = SoilRef.pSoilState->Daily_Drainage_m * 1000.0;
    double Soil_Water_Evaporation = SoilRef.pSoilState->Daily_Soil_Water_Actual_Evaporation_m * 1000.0;
    double Crop_Water_Uptake =
    #ifdef CROPSYST_VERSION
         0.0; //RLN NYI, need to get this from land unit
    #else
         SoilRef.pSoilState->Profile_Soil_Water_Uptake;
    #endif
    Daily_Water_Balance = Initial_Soil_Water_Profile 
                          + Infiltration 
                          - Drainage 
                          - Soil_Water_Evaporation
                          - Crop_Water_Uptake 
                          - Final_Soil_Water_Profile;
    if ((doy == 1) || ( today == ControlRef.start_date))
        Cumulative_Water_Balance = Daily_Water_Balance;
    else Cumulative_Water_Balance += Daily_Water_Balance;
}
//______________________________________________________________________________
double SimulationBalanceClass::CalculateSoilWaterProfile_mm()
{
    return SoilRef.pSoilState->getTotalSoilWaterContent_m() * 1000.0;
}
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SimulationBalanceClass::CalculateDailyOrganicResidueBalance()
{
    //end added FMS variables
    //This balance is treated a little bit different to other balances because residue pools are not organized
    //by soil layers but by position
    int doy = /*150630 ControlRef.*/today.get_DOY();
    //Last_DOY_Of_Previous_Year = OverallControl.LastDOYOfPreviousYear;
    double Final_Residue_Carbon_Mass = 
        SoilRef.pOrganicResidueState->Standing_Stubble_Carbon_Mass
        + SoilRef.pOrganicResidueState->Surface_Residue_Carbon_Mass
        + SoilRef.pOrganicResidueState->Soil_Residue_Carbon_Mass;
    //FMS 11/06/2013 add new lines
    double Organic_Residue_Lost_As_CO2 = 
        SoilRef.pSoilState->Profile_Residue_Carbon_Lost_As_CO2;
    //double New_Residue_Carbon = 
    //    SoilRef.pSOMResidueMaster->OrganicResidueStateRef.Cumulative_New_Residue_Organic_Residue_Carbon_Mass;
    double Organic_Matter_Carbon_Transferred_From_Residues = 
        SoilRef.pSoilState->Profile_Carbon_Transferred_From_Residue_To_SOM;
    double Final_Residue_Nitrogen_Mass = 
        SoilRef.pOrganicResidueState->Standing_Stubble_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->Surface_Residue_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->Soil_Residue_Nitrogen_Mass;
    double Daily_New_Residue_Carbon_Mass =
        SoilRef.pOrganicResidueState->New_Standing_Stubble_Carbon_Mass
        + SoilRef.pOrganicResidueState->New_Surface_Residue_Carbon_Mass
        + SoilRef.pOrganicResidueState->New_Soil_Residue_Carbon_Mass;
    double Daily_New_Residue_Nitrogen_Mass = 
        SoilRef.pOrganicResidueState->New_Standing_Stubble_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->New_Surface_Residue_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->New_Soil_Residue_Nitrogen_Mass;
    double Decomposed_Residue_Carbon_Mass = 
        SoilRef.pOrganicResidueState->Decomposed_Standing_Stubble_Carbon_Mass
        + SoilRef.pOrganicResidueState->Decomposed_Surface_Residue_Carbon_Mass
        + SoilRef.pOrganicResidueState->Decomposed_Soil_Residue_Carbon_Mass;
    double Decomposed_Residue_Nitrogen_Mass = 
        SoilRef.pOrganicResidueState->Decomposed_Standing_Stubble_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->Decomposed_Surface_Residue_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->Decomposed_Soil_Residue_Nitrogen_Mass;
    double Daily_Organic_Residue_Carbon_Mass_Balance = 
        Final_Residue_Carbon_Mass 
        - Initial_Residue_Carbon_Mass
        - Daily_New_Residue_Carbon_Mass 
        + Decomposed_Residue_Carbon_Mass;
    double Balance_Daily_Residue_Carbon = 
        Final_Residue_Carbon_Mass 
        - Initial_Residue_Carbon_Mass
        + Organic_Residue_Lost_As_CO2
        - Daily_New_Residue_Carbon_Mass
        + Organic_Matter_Carbon_Transferred_From_Residues; // FMS 11/06/2013
    double Daily_Organic_Residue_Nitrogen_Mass_Balance = 
        Final_Residue_Nitrogen_Mass 
        - Initial_Residue_Nitrogen_Mass
        - Daily_New_Residue_Nitrogen_Mass 
        + Decomposed_Residue_Nitrogen_Mass;
    if ((doy == 1) || (/*150630 ControlRef.*/today == ControlRef.start_date)) {
        Cumulative_Organic_Residue_Carbon_Balance = Daily_Organic_Residue_Carbon_Mass_Balance;
        Cumulative_Organic_Residue_Nitrogen_Balance = Daily_Organic_Residue_Nitrogen_Mass_Balance;
    } else {
        Cumulative_Organic_Residue_Carbon_Balance += Daily_Organic_Residue_Carbon_Mass_Balance;
        Cumulative_Organic_Residue_Nitrogen_Balance += Daily_Organic_Residue_Nitrogen_Mass_Balance;
    }
    //FMS 11/06/2013 add new lines
    Cumulative_Final_Organic_Residue_Carbon_Mass += Final_Residue_Carbon_Mass;
    Cumulative_Initial_Organic_Residue_Carbon_Mass += Initial_Residue_Carbon_Mass;
    Cumulative_New_Residue_Organic_Residue_Carbon_Mass += Daily_New_Residue_Carbon_Mass;
    Cumulative_Decomposed_Organic_Residue_Carbon_Mass += Decomposed_Residue_Carbon_Mass;
    Cumulative_Organic_Residue_Lost_As_CO2 += Organic_Residue_Lost_As_CO2;
    SoilRef.pOrganicResidueState->Cumulative_Final_Organic_Residue_Carbon_Mass = Cumulative_Final_Organic_Residue_Carbon_Mass;
    SoilRef.pOrganicResidueState->Cumulative_Initial_Organic_Residue_Carbon_Mass = Cumulative_Initial_Organic_Residue_Carbon_Mass;
    SoilRef.pOrganicResidueState->Cumulative_New_Residue_Organic_Residue_Carbon_Mass = Cumulative_New_Residue_Organic_Residue_Carbon_Mass;
    SoilRef.pOrganicResidueState->Cumulative_Decomposed_Organic_Residue_Carbon_Mass = Cumulative_Decomposed_Organic_Residue_Carbon_Mass;
    SoilRef.pOrganicResidueState->Cumulative_Organic_Residue_Lost_As_CO2 = Cumulative_Organic_Residue_Lost_As_CO2;
    LongTermBalance += Balance_Daily_Residue_Carbon;
    // end added FMS//s lines
    //If Abs(LongTermBalance) > 0.00000001 Then Stop
    //If Abs(Cumulative_Organic_Residue_Carbon_Balance * 10000) > 1 Then Stop
}
//______________________________________________________________________________
#endif
#ifndef CROPSYST_VERSION
void SimulationBalanceClass::CalculateDailyOrganicMatterBalance()
{
    //Calculate organic matter carbon balance
    int doy = /*150630 ControlRef.*/today.get_DOY();
    double Final_Organic_Matter_Carbon_Profile = calOrganicMatterCarbonProfile();
    double Organic_Matter_Carbon_Decomposed = SoilRef.pSoilState->Profile_SOM_Carbon_Decomposed;
    double Organic_Matter_Carbon_Transferred_From_Residues = 
        SoilRef.pSoilState->Profile_Carbon_Transferred_From_Residue_To_SOM;
    double Organic_Matter_Lost_As_CO2 = SoilRef.pSoilState->Profile_SOM_Carbon_Lost_As_CO2;
    //FMS 11/05/2013 add lines
    SoilRef.pSoilState->Cumulative_Profile_Final_Organic_Matter_Carbon_Mass += 
        Final_Organic_Matter_Carbon_Profile;
    SoilRef.pSoilState->Cumulative_Profile_Initial_Organic_Matter_Carbon_Mass += 
        Initial_Organic_Matter_Carbon_Profile;
    SoilRef.pSoilState->Cumulative_Profile_Carbon_Transferred_From_Residue_To_SOM += 
        Organic_Matter_Carbon_Transferred_From_Residues;
    SoilRef.pSoilState->Cumulative_Profile_SOM_Carbon_Decomposed += 
        Organic_Matter_Carbon_Decomposed;
    //end FMS lines
    Daily_Organic_Matter_Carbon_Balance = 
        Final_Organic_Matter_Carbon_Profile 
        - Initial_Organic_Matter_Carbon_Profile
        - Organic_Matter_Carbon_Transferred_From_Residues 
        + Organic_Matter_Lost_As_CO2;
    //Calculate organic matter nitrogen balance
    double Final_Organic_Matter_Nitrogen_Profile = calOrganicMatterNitrogenProfile();
    double Organic_Matter_Nitrogen_Mineralized = SoilRef.pSoilState->Profile_OM_Mineralization;
    double Organic_Matter_Nitrogen_Transferred_From_Residues = SoilRef.pSoilState->Profile_Nitrogen_Transferred_From_Residue_To_SOM;
    Daily_Organic_Matter_Nitrogen_Balance = Initial_Organic_Matter_Nitrogen_Profile + Organic_Matter_Nitrogen_Transferred_From_Residues
            - Organic_Matter_Nitrogen_Mineralized - Final_Organic_Matter_Nitrogen_Profile;
    if ((doy == 1) || (/*150630 ControlRef.*/today == ControlRef.start_date)) {
        Cumulative_Organic_Matter_Carbon_Balance = Daily_Organic_Matter_Carbon_Balance;
        Cumulative_Organic_Matter_Nitrogen_Balance = Daily_Organic_Matter_Nitrogen_Balance;
    } else {
        Cumulative_Organic_Matter_Carbon_Balance += Daily_Organic_Matter_Carbon_Balance;
        Cumulative_Organic_Matter_Nitrogen_Balance += Daily_Organic_Matter_Nitrogen_Balance;
    }
}
//______________________________________________________________________________
#endif
#ifndef CROPSYST_VERSION
double SimulationBalanceClass::calOrganicMatterNitrogenProfile()
{
    return SoilRef.pSoilState->Profile_SOM_Carbon_Mass;   //Implement Later in SoilState M.Liu
}
//______________________________________________________________________________
double SimulationBalanceClass::calOrganicMatterCarbonProfile()
{
    return SoilRef.pSoilState->Profile_SOM_Nitrogen_Mass;
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
double SimulationBalanceClass::calSoilNitrogenProfile(std::string N_Species)
{
    double Profile_Nitrogen_Mass = 0;

    for (int L = 1; L <= SoilRef.pSoilProfile->NumberOfLayers(); L++) {
        if (N_Species.compare("Nitrate") == 0) Profile_Nitrogen_Mass += SoilRef.pSoilState->Layer_Nitrate_N_Mass[L];
        else if (N_Species.compare("Ammonium") == 0) Profile_Nitrogen_Mass += SoilRef.pSoilState->Layer_Ammonium_N_Mass[L];
    }
    return Profile_Nitrogen_Mass;
}
#endif
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void SimulationBalanceClass::CalculateDailyNitrogenBalance()
{
    int doy = /*150630 ControlRef.*/today.get_DOY();
    //Calculate daily nitrate balance
    double Final_Soil_Nitrate_Profile = calSoilNitrogenProfile("Nitrate");
    double Nitrate_Fertilization = SoilRef.pSoilState->Daily_Nitrate_N_Fertilization;
    double Nitrate_Fertigation = SoilRef.pSoilState->Daily_Nitrate_N_Fertigation;
    double Nitrate_Leaching = SoilRef.pSoilState->Daily_Nitrate_Leaching;
    double Crop_Nitrate_Uptake = SoilRef.pSoilState->Total_Actual_Nitrate_N_Uptake;
    double Denitrification = SoilRef.pSoilState->Profile_Denitrification;
    double Nitrification = SoilRef.pSoilState->Profile_Nitrification;
    double Nitrate_Immobilization = SoilRef.pSoilState->Profile_Nitrate_Immobilization;
    Daily_Nitrate_Balance = Initial_Nitrate_Profile 
                            + Nitrate_Fertilization 
                            + Nitrate_Fertigation 
                            + Nitrification 
                            - Nitrate_Leaching
                            - Crop_Nitrate_Uptake 
                            - Denitrification 
                            - Nitrate_Immobilization 
                            - Final_Soil_Nitrate_Profile;
    //Calculate daily ammonium balance
    double Final_Soil_Ammonium_Profile = calSoilNitrogenProfile("Ammonium");
    double Ammonium_Fertilization = SoilRef.pSoilState->Daily_Ammonium_N_Fertilization;
    double Ammonium_Fertigation = SoilRef.pSoilState->Daily_Ammonium_N_Fertigation;
    double Ammonium_Leaching = SoilRef.pSoilState->Daily_Ammonium_Leaching;
    double Crop_Ammonium_Uptake = SoilRef.pSoilState->Total_Actual_Ammonium_N_Uptake;
    double Organic_Matter_Mineralization = SoilRef.pSoilState->Profile_OM_Mineralization;
    double Organic_Residue_Mineralization = SoilRef.pSoilState->Profile_Residue_Mineralization;
    double Ammonium_Immobilization = SoilRef.pSoilState->Profile_Ammonium_Immobilization;
    double Ammonia_Volatilization = SoilRef.pSoilState->Ammonia_N_Mass_Volatilization;
    Daily_Ammonium_Balance = Initial_Ammonium_Profile 
                             + Ammonium_Fertilization 
                             + Ammonium_Fertigation 
                             + Organic_Matter_Mineralization 
                             + Organic_Residue_Mineralization
                             - Ammonium_Leaching 
                             - Ammonium_Immobilization 
                             - Crop_Ammonium_Uptake 
                             - Ammonia_Volatilization
                             - Nitrification 
                             - Final_Soil_Ammonium_Profile;
     if ((doy == 1) || (/*150630 ControlRef.*/today == ControlRef.start_date)) {
         Cumulative_Nitrate_Balance = Daily_Nitrate_Balance;
         Cumulative_Ammonium_Balance = Daily_Ammonium_Balance;
     } else {
         Cumulative_Nitrate_Balance += Daily_Nitrate_Balance;
         Cumulative_Ammonium_Balance += Daily_Ammonium_Balance;
     }
}
#endif
//______________________________________________________________________________
void SimulationBalanceClass::CalculateDailySoilBalances()
{
    CalculateDailyWaterBalance();
    #ifndef CROPSYST_VERSION
    CalculateDailyNitrogenBalance();
    CalculateDailyOrganicMatterBalance();
    #endif
}
//______________________________________________________________________________
void SimulationBalanceClass::InitializeDailyBalances()
{
    Initial_Soil_Water_Profile = CalculateSoilWaterProfile_mm();
    #ifndef CROPSYST_VERSION
    Initial_Nitrate_Profile = calSoilNitrogenProfile("Nitrate");
    Initial_Ammonium_Profile = calSoilNitrogenProfile("Ammonium");
    Initial_Organic_Matter_Carbon_Profile = calOrganicMatterCarbonProfile();
    Initial_Organic_Matter_Nitrogen_Profile = calOrganicMatterNitrogenProfile();
    Initial_Residue_Carbon_Mass = SoilRef.pOrganicResidueState->Standing_Stubble_Carbon_Mass
        + SoilRef.pOrganicResidueState->Surface_Residue_Carbon_Mass
        + SoilRef.pOrganicResidueState->Soil_Residue_Carbon_Mass;
        //+ SoilRef.pOrganicResidue->getBellowGroungResidueCarbonMass();
    Initial_Residue_Nitrogen_Mass = SoilRef.pOrganicResidueState->Standing_Stubble_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->Surface_Residue_Nitrogen_Mass
        + SoilRef.pOrganicResidueState->Soil_Residue_Nitrogen_Mass;
        //+ SoilRef.pOrganicResidue->getBellowGroungResidueNitrogenMass();
    #endif
}
//______________________________________________________________________________
