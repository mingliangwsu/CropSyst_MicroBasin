#ifndef CROPWATERUPTAKECLASS_H
#define CROPWATERUPTAKECLASS_H
#include "cropstateclass.h"
#include "cropinputclass.h"
#include "soil/clssoil.h"
#include "control/clssimulation.h"
#include "weather/weatherstatedailyclass.h"

class CropStateClass;
class CropInputClass;
class clsSoil;
class CropWaterUptakeClass
{
public:
    CropStateClass &CropStateRef;
    //CropInputClass &CropParametersRef;
public:
    CropWaterUptakeClass(CropStateClass &_CropStateRef);
    void PerformWaterUptake(clsSoil &Soil, CropInputClass &CropParametersRef);
};

#endif // CROPWATERUPTAKECLASS_H
