#error Remove this file from your project

// Not currently used

#ifndef SIMULATIONBALANCECLASS_H
#define SIMULATIONBALANCECLASS_H
#include "soil/clssoil.h"

//160226RLN Unused: #include "time/timestateclass.h"
//160226RLN Unused: #include "control/clssimulation.h"
#include "string.h"

class clsSoil;
class clsSimulation;
//______________________________________________________________________________
class SimulationBalanceClass
{
private:
    double calOrganicMatterNitrogenProfile();
    double calOrganicMatterCarbonProfile();
    double calSoilNitrogenProfile(std::string N_Species);
public:
    double Initial_Soil_Water_Profile;
    double Initial_Ammonium_Profile;
    double Initial_Nitrate_Profile;
    double Initial_Organic_Matter_Carbon_Profile;
    double Initial_Organic_Matter_Nitrogen_Profile;
    double Initial_Residue_Carbon_Mass;
    double Initial_Residue_Nitrogen_Mass;
    double Daily_Water_Balance;
    double Daily_Nitrate_Balance;
    double Daily_Ammonium_Balance;
    double Daily_Organic_Matter_Carbon_Balance;
    double Daily_Organic_Matter_Nitrogen_Balance;
    double Cumulative_Water_Balance;
    double Cumulative_Nitrate_Balance;
    double Cumulative_Ammonium_Balance;
    double Cumulative_Organic_Matter_Carbon_Balance;
    double Cumulative_Organic_Matter_Nitrogen_Balance;
    double Cumulative_Organic_Residue_Carbon_Balance;
    double Cumulative_Organic_Residue_Nitrogen_Balance;
    //FMS 11/06/2013 new variables
    double Cumulative_Final_Organic_Residue_Carbon_Mass;
    double Cumulative_Initial_Organic_Residue_Carbon_Mass;
    double Cumulative_New_Residue_Organic_Residue_Carbon_Mass;
    double Cumulative_Decomposed_Organic_Residue_Carbon_Mass;
    double Cumulative_Organic_Residue_Lost_As_CO2;
    double LongTermBalance;
    //160226RLN Unused: TimeStateClass &TimeStateRef;
    const CORN::Date &today;                                                     //150630RLN
    AllControlClass &ControlRef;
    clsSoil &SoilRef;
public:
    SimulationBalanceClass
       (
       #ifndef CROPSYST_VERSION
       //160226RLN Unused: TimeStateClass &_TimeStateRef,
       #endif
       const CORN::Date &_today                                                 //150630RLN
       ,AllControlClass &_ControlRef
       ,clsSoil &_SoilRef);
    double CalculateSoilWaterProfile_mm();
    void CalculateDailySoilBalances();
    void InitializeDailyBalances();
    #ifndef CROPSYST_VERSION
    void CalculateDailyOrganicResidueBalance();
    #endif
    void CalculateDailyWaterBalance();
    #ifndef CROPSYST_VERSION
    void CalculateDailyOrganicMatterBalance();
    void CalculateDailyNitrogenBalance();
    #endif
};
//______________________________________________________________________________
#endif // SIMULATIONBALANCECLASS_H
