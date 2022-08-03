#ifndef CLSCROP_H
#define CLSCROP_H
#include "crop/cropstateclass.h"
#include "crop/cropinputclass.h"
#include "cropcanopygrowthclass.h"
#include "cropdevelopmentclass.h"
#include "croppotentialtranspirationclass.h"
#include "cropbiomassclass.h"
#include "croppotsoluteuptakeclass.h"
#include "croprootclass.h"
#include "cropwateruptakeclass.h"
#include "cropactualnitrogenuptakeclass.h"
#include "weather/weatherstatedailyclass.h"
#include "control/allcontrolclass.h"

class CropDevelopmentClass;
class CropPotSoluteUptakeClass;
class CropRootClass;
class CropWaterUptakeClass;
class CropActualNitrogenUptakeClass;
class CropBiomassClass;
class CropPotentialTranspirationClass;
class CropCanopyGrowthClass;
class clsManagement;
class clsCrop
{
private:
    bool Waiting_For_Emergence;     //RS: now a property
    double CalculateMinimum(double a,double b,double c);
public:
    CropStateClass *pCropState;
    CropInputClass *pCropParameters;
    CropCanopyGrowthClass *pCanopyCover;
    CropRootClass *pRoot;
    CropDevelopmentClass *pCropDevelopment;
    CropPotentialTranspirationClass *pPotTransp;
    CropBiomassClass *pBiomass;
    CropWaterUptakeClass *pWatUpt;
    CropActualNitrogenUptakeClass *pCropNitrogenUptake;
    CropPotSoluteUptakeClass *pCropSoluteUptake;
    AllControlClass &ControlRef;
 private:
    const CORN::Date &today;                                                     //150630RLN
public:
    clsCrop
       (AllControlClass &_ControlRef
       ,const CORN::Date &_today                                                 //150630RLN
       );
    ~clsCrop();
    void setWaitingForEmergence(bool X);
    bool getWaitingForEmergence();
    void DetermineCO2Response(WeatherStateDailyClass &Weather);
    void DetermineClippedYield();
    void DetermineTreeFruitYield();
    void DetermineAnnualCropYield();
    void PerformPotentialProcesses(clsSimulation &Simulation, WeatherStateDailyClass &Weather);
    void SetHarvest(clsSimulation &Simulation, WeatherStateDailyClass &Weather);
    void StartCrop(clsSimulation &Simulation,clsSoil &Soil);
    void initialize(clsSimulation &Simulation, WeatherStateDailyClass &Weather, clsSoil &Soil);
    void PerformDailyProcesses(clsSoil &Soil, WeatherStateDailyClass &Weather,clsSimulation &Simulation,
                              clsManagement &Management);
    void NewCrop(clsSimulation &Simulation);
    void CalculateCropNitrogenPartitioning(clsSimulation &Simulation);      //FMS Jul 11, 2014 From version COS CRopSystVB WCN Aug 4 2012

    void ClearStateForNextCropSeason();
    void DetermineCropCover(clsSoil &Soil);
};

#endif // CLSCROP_H
