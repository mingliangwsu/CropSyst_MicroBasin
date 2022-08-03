#ifndef CROPPOTSOLUTEUPTAKECLASS_H
#define CROPPOTSOLUTEUPTAKECLASS_H
//#include "cropinputclass.h"
//#include "cropstateclass.h"
#include "soil/clssoil.h"
#include "control/clssimulation.h"

class clsSoil;
//class clsSimulation;
class CropStateClass;
class CropInputClass;
class CropPotSoluteUptakeClass
{
private:
    double CurrentPAW(int layer, clsSoil &Soil);
    double RootSenescenceFactor(CropInputClass &CropParametersRef);
public:
    CropStateClass& CropStateRef;
    CropPotSoluteUptakeClass(CropStateClass &_CropStateRef);
    void PotentialNitrogenUptake(clsSoil &Soil, CropInputClass &CropParametersRef);
};

#endif // CROPPOTSOLUTEUPTAKECLASS_H
