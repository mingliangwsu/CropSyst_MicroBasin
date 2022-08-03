#ifndef CROPROOTCLASS_H
#define CROPROOTCLASS_H
#include "cropstateclass.h"
#include "cropinputclass.h"
#include "control/clssimulation.h"
#include "soil/clssoil.h"

class CropStateClass;
class CropInputClass;
class CropRootClass
{
public:
    CropStateClass &CropStateRef;
    //CropInputClass &CropParametersRef;
public:
    CropRootClass(CropStateClass &_CropStateRef);
    void DetermineRootGrowth(bool Emerging,clsSoil &Soil,CropInputClass &CropParametersRef);
};

#endif // CROPROOTCLASS_H
