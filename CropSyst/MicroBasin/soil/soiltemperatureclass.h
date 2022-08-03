#ifndef SOILTEMPERATURECLASS_H
#define SOILTEMPERATURECLASS_H

#ifdef MBVB_SOIL_TEMPERATURE

#include "soil/soilstateclass.h"
#include "soil/soilprofileclass2.h"
#include "control/allcontrolclass.h"
#include "weather/weatherstatedailyclass.h"
#include "CS_suite/simulation/CS_simulation_element.h"

#ifdef MBVB_SNOW
#  include "snow/clssnow.h"
#endif

#ifdef CROPSYST_VERSION
#  include "soil/temperature_hourly_interface.h"
#  include "soil/temperature_interface.h"
//151214 #include "common/weather/weather.h"
#else
#  include "control/clssimulation.h"

#  ifdef CROPSYST_PROPER_CROP
#     include "crop/crop_interfaced.h"
#        define clsCrop CropSyst::Crop_interfaced
#  else
#     include "crop/clscrop.h"
      class clsCrop;
#   endif
#endif
class clsSnow;
class WeatherStateDailyClass;
class BasinCellClass;
//______________________________________________________________________________
class SoilTemperatureClass
: public extends_ CS::Simulation_element_abstract                                //150810RLN
#ifdef CROPSYST_VERSION
, public implements_ Soil_temperature_profile_hourly_interface                   //150810RLN
, public implements_ Soil_temperature_interface                                  //150813RLN
#endif
{
    int nmax;
    double Atmospheric_Transmission_Coefficient;
    std::vector<double> Bulk_Density;       //nmax
    std::vector<double> Clay_Fraction;      //(nmax);
    double Cloud_Cover;
    int Current_Year;
    //160412RLN unused double Daily_Soil_Water_Evaporation;
    double Extraterrestrial_Solar_Radiation;
    //int L; //'RS changed: was i
    //std::vector<double> Layer_Thickness;        //(nmax);
    double Long_Wave_Absorptivity;
    std::vector<double> Node_depth;             //(nmax);
    int NuL; //'RS changed: was m
    std::vector<double> PWP_WC;                  //Permanent_Wilting_Point
    double Soil_Depth;
    std::vector<double> SOM_fraction;            //(nmax);
    double Surface_Absorptivity;
    double Surface_Emissivity;
    int year;
    //Temporary variables for calculating soil temperature
    std::vector<double> CP;
    std::vector<double> Ice_Content;
    std::vector<double> Water_Content;
    std::vector<double> k;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;
    std::vector<double> T;
    std::vector<double> Tn;
    std::vector<double> T_freeze_thaw;
    std::vector<double> Remaining_Energy;  //(J/m2)                              //140328FMS
    double calcEnergy2ThawOrFreeze(double m_Water);
    double calcHowMuchWaterCanFreezeOrThaw(double AvailableEnergy);
    double EstimatedSoilTemperature(double Node_depth, int doy);
    double HeatConductivity(double Bulk_Density, double volumetric_WC, double fraction_clay);
    double SoilHeatCapacity(double BD, double SOM_fraction, double volumetric_WC,
                            double volumetric_IceC);
    void FreezingThawing(double &newT,double LayerDepth, double HeatCapacitySoil,
                         double &SoilIceContent, double &SoilWaterContent, double PWP_WC, double Saturation_WC,double &Actual_Release_Energy);
    double nonForFreezingWC(double PWP, double WC_Sat, double newT);
    double potFreezingWater(double nonFreezingWC, double MaxIceContentAtLayer,double SoilWaterContent, double SoilIceContent); //140327FMS
    double calcBoundaryLayerConductance(int hour, double Ts, const double crop_height);                     //140822FMS
    double calcZm(double &d, const double crop_height);                                                    //140822FMS
public:
    const CS::Annual_temperature &annual_temperature;                            //150515LML_141222RLN
    double Boundary_Layer_Heat_Conductance;                                      //(W/m2 K) 160211LML
public:
    AllControlClass& ControlRef;
    SoilProfileClass& SoilProfileRef;
    SoilStateClass& SoilStateRef;
    #ifdef CROPSYST_VERSION
    const Organic_matter_residues_profile_abstract *OM_residues_profile_kg_m2;   //160224RLN
    //160225 BasinCellClass& BasinCellRef;
    #endif
    #ifdef CROPSYST_WEATHER
    const Weather    &weather;  // Now a member instead of passing all the time . //140214
    //const CS::Solar_irradiance_extraterrestrial_hourly &extraterrestrial_solar_irradiance_basin; //151214RLN
    #else
    WeatherStateDailyClass &weather;
    #endif
   mutable bool has_snow_cover;                                                  //160721
 public: // structors
    SoilTemperatureClass
        (AllControlClass               &ControlRef_
        ,SoilProfileClass              &SoilProfileRef_
        ,SoilStateClass                &SoilStateRef_
        ,const CS::Annual_temperature  &annual_temperature_
        #ifdef CROPSYST_WEATHER
        ,const Weather                 &weather_
        #else
        ,WeatherStateDailyClass        &weather_
        #endif
        ,const Organic_matter_residues_profile_abstract *OM_residues_profile_kg_m2_ //160224
        ,const CORN::Date              &today_
        //160225 ,BasinCellClass                &BasinCellRef_
        );
    ~SoilTemperatureClass();
 public: // simulation element implementations
    //150810RLN renamed void InitializeSoilTemperature();
    virtual bool initialize()                                    initialization_;//150810RLN
    //150810RLN renamed void InitializeDayforSoilTemperature();
    virtual bool start_day()                                       modification_;//150810RLN
 public:  // Soil_temperature_profile_interface implementations
    virtual float64 get_temperature(nat8 layer)                            const;//150813RLN
    inline virtual bool know_has_snow_cover(bool has_snow_)            cognition_ //160721
      { return has_snow_cover = has_snow_; }

 public: // Soil_temperature_profile_hourly_interface implementations
   virtual float64 get_temperature(CORN::Hour hour, nat8 layer)            const;//150810RLN
 public:
    void CalculateHourlySoilTemperature
        #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
        (double Fraction_Canopy_Intercepted_Solar_Radiation
        #ifdef MBVB_SNOW
         ,const clsSnow &snow
        #endif
         ,const double crop_height);                    //141204
        #else
        (clsSimulation  &Simulation
        ,clsSnow        &Snow
        ,clsCrop        &crop);
        #endif
};
//______________________________________________________________________________
#endif
#endif // SOILTEMPERATURECLASS_H
