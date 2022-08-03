#ifndef SOILNITROGENTRANSFORMATIONCLASS_H
#define SOILNITROGENTRANSFORMATIONCLASS_H
#include "soil/soilprofileclass2.h"
#include "soil/soilstateclass.h"
#include "soil/soilabioticfunctionsclass.h"
#include "weather/weatherstatedailyclass.h"
#if (defined(CROPSYST_PROPER_CROP) || defined(CROPSYST_VERSION))
namespace CropSyst
{
interface_ Crop_interfaced;
}
#else
class clsCrop;
#endif
#include "control/clssimulation.h"

class SoilAbioticFunctionsClass;
//______________________________________________________________________________
class SoilNitrogenTransformationClass
{
private:
    double N2N2ONitrate(double Nitrate_Concentration_Dry_Soil);
    double Minimum(double a, double b, double c);
    double N2N2OResp(double Layer_CO2_Loss);
    double NitrateResponseFunction(double Denitrification_Half_Rate, double Nitrate_Concentration_Dry_Soil);
    double RespirationFunction(double CO2_Loss_Per_Unit_Soil_Mass);
    double TurbulentTransferCoefficient(double Crop_Height, double Canopy_Cover,
                                                  bool Residue_Present,double Wind_Speed_At_10_Meters);
    double PotentialDenitrification(double WFP);                                 //FMS Mar 27, 2015
public:
    SoilProfileClass &SoilProfileRef;
    SoilStateClass &SoilStateRef;
    SoilAbioticFunctionsClass &AbioticFunctionsRef;
public:
    SoilNitrogenTransformationClass(SoilProfileClass &_SoilProfileRef,SoilStateClass &_SoilStateRef,
                SoilAbioticFunctionsClass &_AbioticFunctionsRef);
    void NitrogenTransformation
        (
        #if (defined(CROPSYST_PROPER_CROP) || defined(CROPSYST_VERSION))
          const CropSyst::Crop_interfaced &crop                                             //140502
        #else
          clsCrop &crop
        #endif
        , clsSimulation &Simulation
        , WeatherStateDailyClass &Weather);
    void AmmoniaVolatilization(double New_TAN_Mass, double New_Water_Volume,
                              double pH_Of_Applied_Material, double Crop_Height, double Canopy_Cover,
                              clsSimulation &Simulation, WeatherStateDailyClass &Weather);
};
//______________________________________________________________________________
#endif // SOILNITROGENTRANSFORMATIONCLASS_H

