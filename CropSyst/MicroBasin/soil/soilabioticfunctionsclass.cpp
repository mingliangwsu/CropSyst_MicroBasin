#ifndef CROPSYST_VERSION
#include "soilabioticfunctionsclass.h"
#include <math.h>

SoilAbioticFunctionsClass::SoilAbioticFunctionsClass()
{
}
double SoilAbioticFunctionsClass::pHFunction(double pH, clsSimulation &Simulation)
{
    double pH_Min = Simulation.pSimConstants->Minimum_pH;
    double pH_Max = Simulation.pSimConstants->Maximum_pH;
    double pH_Function = (pH - pH_Min) / (pH_Max - pH_Min);
    return pH_Function;
}

double SoilAbioticFunctionsClass::DenitrificationMoistureFunction(double FC, 
  double SAT, double WFP, bool For_N2_N2O_Ratio)
{
    //'Modified from SOILN
    double WFP_Threshold(0.0);
    if (For_N2_N2O_Ratio) WFP_Threshold = FC / SAT - 0.05;
    else WFP_Threshold = 0.01 + FC / SAT;
    double Upper_Threshold = 1. * 0.7 + 0.3 * WFP_Threshold; //FMS Mar 2015
    double DMF(0.0);
    if (WFP > WFP_Threshold) {
        if (WFP < Upper_Threshold) 
            DMF = pow(((WFP - WFP_Threshold) / (Upper_Threshold - WFP_Threshold))
                      , 2.0);
        else DMF = 1.0;
    }
    return DMF;
}

double SoilAbioticFunctionsClass::MoistureFunction(double Function_Value_At_Saturation, double WFP)
{
    //WFP is water-filled porosity
    double Moisture_Function(0.0);
    const double WFP_min = 0.1;
    const double WFP_low = 0.5;
    const double WFP_high = 0.7;
    if (WFP >= WFP_min && WFP < WFP_low)
        Moisture_Function = ((WFP - WFP_min) / (WFP_low - WFP_min));
    else if (WFP >= WFP_low && WFP <= WFP_high)
        Moisture_Function = 1.0;
    else if (WFP > WFP_high && WFP <= 1.0)
        Moisture_Function = Function_Value_At_Saturation + (1 - Function_Value_At_Saturation)
            * pow(((1.0 - WFP) / (1.0 - WFP_high)),2.0);
    if (Moisture_Function < 0) Moisture_Function = 0.0;
    return Moisture_Function;
}

double SoilAbioticFunctionsClass::TemperatureFunction(double T)
{
    double Temperature_Function(0.0);
    //The parameters for this function are used for microbially-mediated N transformations
    //and carbon decomposition
    const double T_min = -5;
    const double T_Opt = 35;
    const double T_max = 50;
    if ((T < T_min) || (T > T_max)) {
        Temperature_Function = 0.0;
    } else {
        double Q = (T_min - T_Opt) / (T_Opt - T_max);
        Temperature_Function = (pow(T - T_min,Q) * (T_max - T)) 
                                / (pow(T_Opt - T_min,Q) * (T_max - T_Opt));
        if (Temperature_Function > 1) Temperature_Function = 1;
        else if (Temperature_Function < 1.0e-7) 
            Temperature_Function = 1.0e-7;
    }
    return Temperature_Function;
}
#endif
