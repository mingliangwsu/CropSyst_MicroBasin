#ifndef CROPACTUALNITROGENUPTAKECLASS_H
#define CROPACTUALNITROGENUPTAKECLASS_H
#include "cropstateclass.h"
#include "cropinputclass.h"
#include "soil/clssoil.h"
#include "control/clssimulation.h"

class clsSoil;
class clsSimulation;
class CropStateClass;
class CropInputClass;
class CropActualNitrogenUptakeClass
{
private:
    double Initial_Top_N_Mass;
    double Initial_Root_N_Mass;
    double PotentialNitrogenUptakeUdjustmentFactor();
    double Quadratic(double a,double b,double c,double d);
public:
    CropStateClass &CropStateRef;
public:
    CropActualNitrogenUptakeClass(CropStateClass &_CropStateRef);
    void PlantNProcesses(clsSimulation &Simulation,clsSoil &Soil,CropInputClass &CropParametersRef);
    void CalculateReferencePlantNConcentration(clsSimulation &Simulation,CropInputClass &CropParametersRef);
    void CalculateCropNitrogenDemand(CropInputClass &CropParametersRef);
    void ActualNitrogenUptakeAndCropNConcentration(clsSoil &Soil);
    void CalculateNLimitationToGrowth(CropInputClass &CropParametersRef);

};

#endif // CROPACTUALNITROGENUPTAKECLASS_H
