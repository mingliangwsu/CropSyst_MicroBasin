#ifndef OUTPUTHOURCLASS_H
#define OUTPUTHOURCLASS_H
#include "control/allcontrolclass.h"
#include <vector>
class AllControlClass;
//______________________________________________________________________________
class OutputHourClass
{
    int NuL;
public:
    int Current_Year;
    int Current_DOY;
    int Current_Hour;   //0-23
    bool b_set_vector_size;
    std::vector<double> Node_Depth;
    std::vector<double> Layer_Water_Content;
    std::vector<double> Layer_Ice_Content;      //LML 140814
    std::vector<double> Layer_Temperature;      //LML 140814
    std::vector<double> Layer_Nitrate_N_Mass;   //(kg/m2)
    std::vector<double> Layer_Nitrate_N_Conc;   //(kg/m3)
    std::vector<double> Layer_Ammonium_N_Mass;  //(kg/m2)
    std::vector<double> Layer_Ammonium_N_Conc;  //(kg/m3)
    double Prec_Irrig_SnowMelt_m;   //(m) non-intercepted rain by canopy&snowpack + irrig + snowmelt
    double Ponded_Water;            //(m)
    double Runoff;                  //(m)
    double Drainage;                //(m)
    double Evaporation;             //(m)
    double Temperature;
    double Precipitation;           //(m)
    double Fraction_Cover_Snow;     //(0-1) LML 140821
    double Snow_Water_Equavalent;   //(m H2O) LML 140502
    double Snow_Melt;               //(m H2O) LML 140502
    double Sublimation;             //(m H2O) LML 140502
    double FD_Water_Balance;
    bool Sat_Boundary;
    //LML 14/04/18
    double hourlySurfaceOutFlow_m3;
    double hourlySurfaceInFlow_m3;
    double hourlyDrainage_m3;
    double hourlyLateralInFlow_m3;
    double hourlyLateralOutFlow_m3;
    double hourlyLateralUpFlow_m3;
    std::vector<double> hourlyLateralInFlowSolute_kg;
    std::vector<double> hourlyLateralOutFlowSolute_kg;
    std::vector<double> hourlySurfaceInFlowSolute_kg;
    std::vector<double> hourlySurfaceOutFlowSolute_kg;
public:
    /*AllControlClass &ControlRef;*/
    OutputHourClass(/*AllControlClass &_ControlRef*/);//SoilProfileClass &_SoilProfileRef);
    ~OutputHourClass();
};
//______________________________________________________________________________
#endif // OUTPUTHOURCLASS_H
