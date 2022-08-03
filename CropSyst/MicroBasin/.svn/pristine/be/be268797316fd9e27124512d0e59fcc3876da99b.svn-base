#ifndef SOILABIOTICFUNCTIONSCLASS_H
#define SOILABIOTICFUNCTIONSCLASS_H
#ifndef CROPSYST_VERSION
#include "control/clssimulation.h"

class SoilAbioticFunctionsClass
{
public:
    SoilAbioticFunctionsClass();
    double pHFunction(double pH, clsSimulation &Simulation);
    double DenitrificationMoistureFunction(double FC, double SAT, double WFP,
                                             bool For_N2_N2O_Ratio);
    double MoistureFunction(double Function_Value_At_Saturation, double WFP);
    double TemperatureFunction(double T);
};
#endif
#endif // SOILABIOTICFUNCTIONSCLASS_H
