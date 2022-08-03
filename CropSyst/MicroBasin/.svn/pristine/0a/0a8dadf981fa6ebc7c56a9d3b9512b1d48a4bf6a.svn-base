#ifndef CROPDEVELOPMENTCLASS_H
#define CROPDEVELOPMENTCLASS_H
#include "cropinputclass.h"
#include "cropstateclass.h"
#include "weather/weatherstatedailyclass.h"
#include "control/clssimulation.h"
#include "soil/clssoil.h"
#include "management/clsmanagement.h"

class clsSoil;
class clsManagement;
class CropInputClass;
class CropStateClass;
class WeatherStateDailyClass;
class CropDevelopmentClass
{
private:
    double CalculateThermalTime(double Base_Temperature, 
        double Maximum_Temperature, double Mean_Temperature);
public:
    //CropInputClass& CropParametersRef;
    CropStateClass& CropStateRef;
    CropDevelopmentClass(CropStateClass &_CropStateRef);
    void UpdateDevelopment(WeatherStateDailyClass &Weather, clsSimulation &Simulation,
        clsManagement &Management, CropInputClass &CropParameters);
};

#endif // CROPDEVELOPMENTCLASS_H
