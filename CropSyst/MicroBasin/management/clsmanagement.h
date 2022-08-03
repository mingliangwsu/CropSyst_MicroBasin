#ifndef CLSMANAGEMENT_H
#define CLSMANAGEMENT_H
#ifndef CROPSYST_PROPER_MANAGEMENT
#include "manageeventstateclass.h"
#include "managescheduleclass.h"
#include "control/clssimulation.h"
#include "weather/weatherstatedailyclass.h"
//140502 RLN #include "crop/clscrop.h"
#include "soil/clssoil.h"
#include "control/allcontrolclass.h"
#include "basin/basinclass.h"
#ifdef CROPSYST_PROPER_CROP
namespace CropSyst
{  interface_ Crop_interfaced;
}
#else
class clsCrop;
#endif
class AllControlClass;
class clsSoil;
class clsSimulation;
class ManageScheduleClass;
class WeatherStateDailyClass;
class BasinClass;
//______________________________________________________________________________
class clsManagement
{
public:
    ManageEventStateClass *pManagementState;        //Current management state
    ManageScheduleClass *pSchedule;                 //LML 140827 is a pointer to global array
    double Fraction_Of_Biomass_To_Standing_Residue;
    double Fraction_Of_Biomass_To_Surface_Residue;
    double Irrigation_Amount;
    bool Clipping_Event;
    int Application_Year;                                                        //FMS Mar 20, 2015
    AllControlClass &ControlRef;
    BasinClass      &BasinRef;
 private:
    const CORN::Date &today;                                                     //150630RLN
public:
    clsManagement
       (AllControlClass &_ControlRef
       ,const CORN::Date &today
       ,BasinClass &_BasinRef);
    ~clsManagement();
    void instantiateManagement();
    void initializeNewDay
        (clsSimulation &Simulation
        #ifdef CROPSYST_PROPER_CROP
        , const CropSyst::Crop_interfaced &crop
        #else
        , clsCrop &Crop
        #endif
        , clsSoil &Soil
        , WeatherStateDailyClass &Weather
        , const int crop_management_zone);
    void DailyManagementEvents
        (clsSimulation &Simulation
        #ifdef CROPSYST_PROPER_CROP
        , const CropSyst::Crop_interfaced &crop
        #else
        , clsCrop &Crop
        #endif
        , clsSoil &Soil
        , WeatherStateDailyClass &Weather
        , int CropManagementZone);
    void FindBiomassToStandingResidue(clsSimulation &Simulation);
    bool FindIrrigation(clsSimulation &Simulation,clsSoil &Soil);
    bool FindFertilization(clsSimulation &Simulation, clsSoil &Soil, int CropManagementZone);
    bool FindManureApplication(clsSimulation &Simulation);
    bool FindAndApplyTillageEvent(clsSimulation &Simulation,clsSoil &Soil);
    bool FindAndApplyClippingEvent
      (
      #ifdef CROPSYST_PROPER_CROP
         modifiable_ CropSyst::Crop_interfaced &crop
      #else
         clsCrop &Crop
      #endif
      );
    void ApplyTillage(clsSoil &Soil, clsSimulation &Simulation);
    void ApplyFertilization
        (bool Crop_Emerged
        #ifdef CROPSYST_PROPER_CROP
        , const CropSyst::Crop_interfaced &crop
        #else
        , clsCrop &Crop
        #endif
        , clsSimulation &Simulation
        , clsSoil &Soil, WeatherStateDailyClass &Weather);
    void ApplyManure
        (bool Crop_Emerged
        #ifdef CROPSYST_PROPER_CROP
        , const CropSyst::Crop_interfaced &crop
        #else
        , clsCrop &Crop
        #endif
        , clsSoil &Soil
        );
    void AutoFertilization(clsSimulation &Simulation
                           , clsSoil &Soil
                           , int k
                           , int CropManagementZone);
};
//_2014-02-??___________________________________________________________________
#endif // CROPSYST_PROPER_MANAGEMENT
#endif // CLSMANAGEMENT_H
