#ifndef CROPBIOMASSCLASS_H
#define CROPBIOMASSCLASS_H
#include "cropinputclass.h"
#include "cropstateclass.h"
#include "control/clssimulation.h"
#include "weather/weatherstatedailyclass.h"

class CropCanopyGrowthClass;
class CropBiomassClass
{
 public:
    CropStateClass& CropStateRef;
    AllControlClass& ControlRef;
    const CORN::Date &today;                                                     //150630RLN
 public:
    CropBiomassClass
       (CropStateClass& _CropStateRef
       ,AllControlClass& _ControlRef
       ,const CORN::Date &_today);                                               //150630RLN

    void DetermineWaterLimitedBiomassGrowth();
    void DetermineActualBiomassGrowth(CropInputClass &CropParametersRef);
    void DeterminePotentialGrowth(bool Potential, WeatherStateDailyClass &Weather,
                                 clsSimulation &Simulation,CropInputClass &CropParametersRef);
    void DetermineBiosynthesisAndMaintenanceRespiration(WeatherStateDailyClass &Weather,
                                 CropCanopyGrowthClass &CanopyCover, clsSoil &soil, CropInputClass &CropParametersRef);  //NEW FMS Jun 25, 2014
};

#endif // CROPBIOMASSCLASS_H
