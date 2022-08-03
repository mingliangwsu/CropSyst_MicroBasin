#ifndef CROPPOTENTIALTRANSPIRATIONCLASS_H
#define CROPPOTENTIALTRANSPIRATIONCLASS_H
#include "cropinputclass.h"
#include "cropstateclass.h"
#include "weather/weatherstatedailyclass.h"
#include "control/clssimulation.h"

class CropInputClass;
class CropStateClass;
class CropPotentialTranspirationClass
{
    double Max_Unadj_Crop_ET_Coeff_Potential_Crop;
    double Max_Unadj_Crop_ET_Coeff_Actual_Crop;
    double Max_Reached_Height_Potential_Crop;
    double Max_Reached_Height_Actual_Crop;
    double CalculateFullShadingCropETCoeff(double Crop_Height);
    double CalculateWeatherAdjustedCropETCoeff(double Crop_Height,
        double Unajusted_Crop_ET_Full_Shading, WeatherStateDailyClass &Weather);
public:
    //CropInputClass& CropParametersRef;
    CropStateClass& CropStateRef;
    CropPotentialTranspirationClass(CropStateClass &_CropStateRef);
    void DeterminePotentialTranspiration(bool Potential, WeatherStateDailyClass &Weather, CropInputClass &CropParametersRef);
};

#endif // CROPPOTENTIALTRANSPIRATIONCLASS_H
