#ifndef CROPSYST_WEATHER
#include "weatherstatedailyclass.h"
#include "util/pubtools.h"
#include "util/constants.h"
#include <iostream>
#include <math.h>
#include <assert.h>
#include <algorithm>
#ifdef CROPSYST_VERSION
#include "common/solar/irradiance_extraterrestrial.h"
#include "UED/library/UED_codes.h"
#endif

//______________________________________________________________________________
Weather_provider        *test;

#ifdef WEATHER_PROVIDER_VERSION
WeatherStateDailyClass::WeatherStateDailyClass                                   //150730RLN
(
 const CORN::Date_const                            &today_                             //151222RLN
,const Geocoordinate                         &geocoordinate_                     //150629
,const CS::Solar_irradiance_extraterrestrial/*160808RLN _hourly*/ &ET_solar_irradiance_        //160808RLN_160404LML
,const float64                               &day_length_hours_today_
)
:daily_provider(today_,geocoordinate_,ET_solar_irradiance_,0)                    //151222
,extraterrestrial_solar_irradiance_basin(ET_solar_irradiance_)                   //160404LML
,today(today_)
,ET_reference((float32) geocoordinate_.get_elevation() ,day_length_hours_today_,daily_provider)
,air_temperature_min_tomorrow (9999.9)                                           //151223
,air_temperature_max_yesterday(9999.9)                                           //151223
#ifdef CROPSYST_WEATHER_HOURLY
,subdaily(*this,today_                                                           //151223
   ,daily_provider.air_temperature_max
   ,daily_provider.air_temperature_min
   ,daily_provider.relative_humidity_max
   ,daily_provider.relative_humidity_min)
,hourly(subdaily,geocoordinate_,ET_solar_irradiance_,sun_days)                   //151223
#endif
#else
#error obsolete
WeatherStateDailyClass::WeatherStateDailyClass()
#endif
{  initMem();
}
//______________________________________________________________________________
WeatherStateDailyClass::~WeatherStateDailyClass()
{
    clearMem();
}
//______________________________________________________________________________
void WeatherStateDailyClass::initMem()
{
    const int num_hours = 25;
    #ifdef CROPSYST_WEATHER_HOURLY
    // stored in weather_hours
    #else
    Hourly_Temperature.resize(num_hours,0);
    Hourly_Relative_Humidity.resize(num_hours,0);
    Hourly_Solar_Irradiance.resize(num_hours,0);
    #endif
    Hourly_Precipitation.resize(num_hours,0);
    Hourly_Rainfall.resize(num_hours,0); 
    Hourly_Snowfall.resize(num_hours,0);
    Hourly_Wind_Speed_At_10m.resize(num_hours,0);
    Hourly_Wind.resize(num_hours,0);
    //Hourly_Fraction_Of_Solar_Irradiance.resize(num_hours,0);                     //160404LML
    Hourly_Canopy_Solar_Interception_Fraction.resize(num_hours,0);
    Hourly_Standing_Stubble_Solar_Interception_Fraction.resize(num_hours,0); 
    Hourly_Surface_Residue_Solar_Interception_Fraction.resize(num_hours,0);
    List_Daily_Mean_Temperature.clear();
}
//______________________________________________________________________________
void WeatherStateDailyClass::clearMem()
{
}
//______________________________________________________________________________
double WeatherStateDailyClass::calcSatVP(double T)
{
    //moved here from SoilTemperatureClass
    return 0.6108 * exp(17.27 * T / (T + 237.3));
}
//______________________________________________________________________________
double WeatherStateDailyClass::calcSkyEmissivity(double vapor_pressure,double Tair,double Cloud_Cover)
{
    double T_Kelvin = Tair + 273.15;   //Tair in Kelvin
    double clear_sky_emissivity(0);
    if (vapor_pressure == -999) clear_sky_emissivity = 0.0000092 * pow(T_Kelvin,2.0);
    else clear_sky_emissivity = 1.72 * pow(vapor_pressure / T_Kelvin, 1.0/7.0);
    double out = (1 - 0.84 * Cloud_Cover) * clear_sky_emissivity + 0.84 * Cloud_Cover;
    return out;
}
//______________________________________________________________________________
#ifndef CROPSYST_WEATHER_HOURLY
double WeatherStateDailyClass::calcHourlyTemperature(int HourOfDay,double Tmax_today,double Tmax_yesterday,
                               double Tmin_today,double Tmin_tomorrow)
{
    double Tn(0),Tx(0);
    double Twf = 0.44 - 0.46 * sin(HourOfDay * Pi / 12.0 + 0.9) + 0.11 * sin(2 * HourOfDay * Pi / 12.0 + 0.9);
    if (HourOfDay <= 5) {
        Tn = Tmin_today;
        Tx = Tmax_yesterday;
    } else {
            if (HourOfDay > 14) {
                Tn = Tmin_tomorrow;
                Tx = Tmax_today;
            } else {
                Tn = Tmin_today;
                Tx = Tmax_today;
            }
    }
    double out = Twf * Tx + (1 - Twf) * Tn;
    Hourly_Temperature[HourOfDay] = out;
    return out;
}
//______________________________________________________________________________
double WeatherStateDailyClass::calcHourlyHumidity(int HourOfDay,double RHmax_today,double RHmax_tomorrow,
                            double RHmin_today,double RHmin_yesterday)
{
    //HourOfDay: 0-23
    double RHn(0),RHx(0);
    double Twf = 0.44 - 0.46 * sin(HourOfDay * Pi / 12.0 + 0.9) + 0.11 * sin(2 * HourOfDay * Pi / 12.0 + 0.9);
    if (HourOfDay <= 5) {
        RHn = RHmin_yesterday;
        RHx = RHmax_today;
    } else {
        if (HourOfDay > 14) {
            RHn = RHmin_today;
            RHx = RHmax_tomorrow;
        } else {
            RHn = RHmin_today;
            RHx = RHmax_today;
        }
    }
    double out = Twf * RHn + (1 - Twf) * RHx;
    Hourly_Relative_Humidity[HourOfDay] = out;
    return out;
}
//______________________________________________________________________________
#endif

//160606RLN  Some of the following are obsolete I am moving them into weatherstateclass_MSVB

void WeatherStateDailyClass::setDailyWindSpeedAt10m(double DWS10)
{
    Daily_Wind_Speed_At_10m = DWS10;
}
double WeatherStateDailyClass::getDailyWindSpeedAt10m()
{
    return Daily_Wind_Speed_At_10m;
}
#ifdef CROPSYST_WEATHER_HOURLY
double WeatherStateDailyClass::getHourlyTemperature(int hour)
{  return hourly.get_air_temperature((CORN::Hour)hour); }
double WeatherStateDailyClass::getHourlyRelativeHumidity(int hour)
{  return hourly.get_relative_humidity((CORN::Hour)hour); }
double WeatherStateDailyClass::getHourlySolarIrradiance(int hour)
{  return hourly.get_solar_irradiance_MJ_m2(hour); }
#else
void WeatherStateDailyClass::setHourlyTemperature(int hour,double HT)
{
    Hourly_Temperature[hour] = HT;
}
double WeatherStateDailyClass::getHourlyTemperature(int hour)
{
    return Hourly_Temperature[hour];
}
void WeatherStateDailyClass::setHourlyRelativeHumidity(int hour,double HT)
{
    Hourly_Relative_Humidity[hour] = HT;
}
double WeatherStateDailyClass::getHourlyRelativeHumidity(int hour)
{
    return Hourly_Relative_Humidity[hour];
}
void WeatherStateDailyClass::setHourlySolarIrradiance(int hour,double x)
{
    Hourly_Solar_Irradiance[hour] = x;
}
double WeatherStateDailyClass::getHourlySolarIrradiance(int hour)
{
    return Hourly_Solar_Irradiance[hour];
}
#endif
void WeatherStateDailyClass::setHourlyCanopySolarInterceptionFraction(int hour,double x)
{
    Hourly_Canopy_Solar_Interception_Fraction[hour] = x;
}
double WeatherStateDailyClass::getHourlyCanopySolarInterceptionFraction(int hour)
{
    return Hourly_Canopy_Solar_Interception_Fraction[hour];
}
void WeatherStateDailyClass::setHourlyStandingStubbleSolarInterceptionFraction(int hour,double x)
{
    Hourly_Standing_Stubble_Solar_Interception_Fraction[hour] = x;
}
double WeatherStateDailyClass::getHourlyStandingStubbleSolarInterceptionFraction(int hour)
{
    return Hourly_Standing_Stubble_Solar_Interception_Fraction[hour];
}
void WeatherStateDailyClass::setHourlySurfaceResidueSolarInterceptionFraction(int hour,double x)
{
    Hourly_Surface_Residue_Solar_Interception_Fraction[hour] = x;
}
double WeatherStateDailyClass::getHourlySurfaceResidueSolarInterceptionFraction(int hour)
{
    return Hourly_Surface_Residue_Solar_Interception_Fraction[hour];
}
void WeatherStateDailyClass::setDailyDiffuseSolarIrradiance(double x)
{
    Daily_Diffuse_Solar_Irradiance = x;
}
double WeatherStateDailyClass::getDailyDiffuseSolarIrradiance()
{
    return Daily_Diffuse_Solar_Irradiance;
}
void WeatherStateDailyClass::setDailyDirectSolarIrradiance(double x)
{
    Daily_Direct_Solar_Irradiance = x;
}
double WeatherStateDailyClass::getDailyDirectSolarIrradiance()
{
    return Daily_Diffuse_Solar_Irradiance;
}
void WeatherStateDailyClass::setDailyCanopySolarInterceptionFraction(double x)
{
    Daily_Canopy_Solar_Interception_Fraction = x;
}
double WeatherStateDailyClass::getDailyCanopySolarInterceptionFraction()
{
    return Daily_Canopy_Solar_Interception_Fraction;
}
void WeatherStateDailyClass::setDailyGreenCanopySolarInterceptionFraction(double x)
{
    Daily_Green_Canopy_Solar_Interception_Fraction = x;
}
double WeatherStateDailyClass::getDailyGreenCanopySolarInterceptionFraction()
{
    return Daily_Green_Canopy_Solar_Interception_Fraction;
}
void WeatherStateDailyClass::setDailyStandingStubbleSolarInterceptionFraction(double x)
{
    Daily_Standing_Stubble_Solar_Interception_Fraction = x;
}
double WeatherStateDailyClass::getDailyStandingStubbleSolarInterceptionFraction()
{
    return Daily_Standing_Stubble_Solar_Interception_Fraction;
}
void WeatherStateDailyClass::setDailySurfaceResidueSolarInterceptionFraction(double x)
{
    Daily_Surface_Residue_Solar_Interception_Fraction = x;
}
double WeatherStateDailyClass::getDailySurfaceResidueSolarInterceptionFraction()
{
    return Daily_Surface_Residue_Solar_Interception_Fraction;
}
void WeatherStateDailyClass::setDailySunlitLAI(double x)
{
    Daily_Sunlit_LAI = x;
}
double WeatherStateDailyClass::getDailySunlitLAI()
{
    return Daily_Sunlit_LAI;
}
void WeatherStateDailyClass::setDailyShadedLAI(double x)
{
    Daily_Shaded_LAI = x;
}
double WeatherStateDailyClass::getDailyShadedLAI()
{
    return Daily_Shaded_LAI;
}
void WeatherStateDailyClass::setDailySunlitLAISolarInterceptionFraction(double x)
{
    Daily_SunlitLAI_Solar_Interception_Fraction = x;
}
double WeatherStateDailyClass::getDailySunlitLAISolarInterceptionFraction()
{
    return Daily_SunlitLAI_Solar_Interception_Fraction;
}
void WeatherStateDailyClass::setDailyShadedLAISolarInterceptionFraction(double x)
{
    Daily_ShadedLAI_Solar_Interception_Fraction = x;
}
double WeatherStateDailyClass::getDailyShadedLAISolarInterceptionFraction()
{
    return Daily_ShadedLAI_Solar_Interception_Fraction;
}
void WeatherStateDailyClass::setUnstressedCanopyResistance(double UCR)
{
    Unstressed_Canopy_Resistance = UCR;
}
double WeatherStateDailyClass::getUnstressedCanopyResistance()
{
    return Unstressed_Canopy_Resistance;
}
void WeatherStateDailyClass::setCumulativeChillHours(double CH)
{
    Cumulative_Chill_Hours = CH;
}
double WeatherStateDailyClass::getCumulativeChillHours()
{
    return Cumulative_Chill_Hours;
}
void WeatherStateDailyClass::setAccumulateChillHours(bool ACH)
{
    Accumulate_Chill_Hours = ACH;
}
int WeatherStateDailyClass::getAccumulateChillHours()
{
    return Accumulate_Chill_Hours;
}
//______________________________________________________________________________
void WeatherStateDailyClass::setHourlyPrecipitation(int hour,double ppt) {Hourly_Precipitation[hour] = ppt;}
double WeatherStateDailyClass::getHourlyPrecipitation(int hour) {return(Hourly_Precipitation[hour]);}
void WeatherStateDailyClass::setHourlyRainfall(int hour,double rain){Hourly_Rainfall[hour] = rain;}
double WeatherStateDailyClass::getHourlyRainfall(int hour){return(Hourly_Rainfall[hour]);}
void WeatherStateDailyClass::setHourlySnowfall(int hour,double snow){Hourly_Snowfall[hour] = snow;}
double WeatherStateDailyClass::getHourlySnowfall(int hour){return(Hourly_Snowfall[hour]);}
void WeatherStateDailyClass::setHourlyWind10m(int hour,double wind){Hourly_Wind_Speed_At_10m[hour] = wind;}
double WeatherStateDailyClass::getHourlyWind10m(int hour){return(Hourly_Wind_Speed_At_10m[hour]);}
void WeatherStateDailyClass::setScreeningHeight(double screenheight){Screening_Height = screenheight;}
double WeatherStateDailyClass::getScreeningHeight(){return(Screening_Height);}
//______________________________________________________________________________
void WeatherStateDailyClass::copyHourlyWeatherFromStation
(
const //160308RLN  This must be const otherwise pweather is getting copied
WeatherSingleYearHourlyClass *pweather
)
{
    #ifdef CROPSYST_VERSION
    setScreeningHeight(pweather->weather_station.get_screening_height());        //141222RLN
    remember_weather = pweather;                                                 //160608RLN
    #endif
    int day_of_year = today.get_DOY();
    int yesterday = (day_of_year == 1) ? day_of_year : (day_of_year-1);
    int tomorrow = (today.is_last_DOY()) ? day_of_year : (day_of_year+1);
    Daily_Wind_Speed_At_Screening_Height = 0.0;
    for (int hour = 0; hour < 24; hour++) {
        if (pweather->weather_station.getTimeStepHours() == 1) {
            #ifdef CROPSYST_WEATHER_HOURLY
            hourly.temperature_by_hour.set(pweather->getHourlyT(day_of_year,hour);
            hourly.relative_humidity_by_hour.set(pweather->getHourlyRelHum(day_of_year,hour));
            #else
            Hourly_Temperature[hour] = pweather->getHourlyT(day_of_year,hour);
            Hourly_Relative_Humidity[hour] = pweather->getHourlyRelHum(day_of_year,hour);
            #endif
            Hourly_Precipitation[hour] = pweather->getHourlyP(day_of_year,hour);
            Hourly_Wind[hour] = pweather->getHourlyWind(day_of_year,hour);
            Daily_Wind_Speed_At_Screening_Height += Hourly_Wind[hour] / 24.0;
            Hourly_Solar_Irradiance[hour] = pweather->getHourlySolRad(day_of_year,hour);

            DetermineWindVelocityAtSpecifiedHeight(hour,10,1,0,false,Hourly_Wind_Speed_At_10m[hour]);
        }
        else if (pweather->weather_station.getTimeStepHours() == 24) {
            //Generating hourly data from daily information
            calcHourlyTemperature(hour
                                  ,pweather->getDailyTmax(day_of_year)
                                  ,pweather->getDailyTmax(yesterday)
                                  ,pweather->getDailyTmin(day_of_year)
                                  ,pweather->getDailyTmin(tomorrow));
            #ifdef DIST_DAILY_RAIN_TO_TWO_HOURS
            if (hour >= 7 && hour <= 8) Hourly_Precipitation[hour] = pweather->getDailyP(day_of_year) / 2.0;
            else Hourly_Precipitation[hour] = 0.;
            #else
            Hourly_Precipitation[hour] = pweather->getDailyP(day_of_year) / 24.0;
            #endif
            calcHourlyHumidity(hour
                               ,pweather->getDailyRelHumMax(day_of_year)
                               ,pweather->getDailyRelHumMax(tomorrow)
                               ,pweather->getDailyRelHumMin(day_of_year)
                               ,pweather->getDailyRelHumMin(yesterday));
            Hourly_Wind[hour] = pweather->getDailyWind(day_of_year);
            Daily_Wind_Speed_At_Screening_Height = pweather->getDailyWind(day_of_year);
            #ifdef CROPSYST_VERSION
            //160404LML
            Hourly_Solar_Irradiance[hour] = pweather->getDailySolRad(day_of_year)
                                            * extraterrestrial_solar_irradiance_basin.get_insolation_fraction(day_of_year,hour);
            //std::clog<<"hour:"<<hour
            //         <<"\tFract_Solar_Irrad:"<<extraterrestrial_solar_irradiance_basin.get_insolation_fraction(day_of_year,hour)
            //         <<"\tSolar_Irrad:"<<Hourly_Solar_Irradiance[hour]
            //         <<std::endl;
            #endif
            DetermineWindVelocityAtSpecifiedHeight(hour,10,1,0,true,Hourly_Wind_Speed_At_10m[hour]);
        }
    }
    //Implement other variables later M.Liu
    for (int hour = 0; hour < 24; hour++)
        DetermineWindVelocityAtSpecifiedHeight(hour,10,1,0,true,Hourly_Wind_Speed_At_10m[hour]); //150602 DEBUG ONLY!!! For consistant with VB version. Need talk with Fidel.
    air_temperature_min_tomorrow  = pweather->getDailyTmin(tomorrow);            //151223
    air_temperature_max_yesterday = pweather->getDailyTmax(yesterday);           //151223
    DetermineDailyWeatherFromHourlyData();
    #ifdef WEATHER_PROVIDER_VERSION
    #ifdef CROPSYST_WEATHER_HOURLY
    hourly.update(doy);                                                          //151223
    #endif
    daily_provider.update();
    #else
    #endif
}
//______________________________________________________________________________
void WeatherStateDailyClass::DetermineDailyWeatherFromHourlyData()
{
    //Calculate daily weather information from hourly data

    #ifdef WEATHER_PROVIDER_VERSION
    daily_provider.air_temperature_avg.set_Celcius(MeanOfArray<double>(Hourly_Temperature,-9999,24)  ,CORN::measured_quality); //141222
    daily_provider.air_temperature_min.set_Celcius(MinOfArray<double>(Hourly_Temperature,-9999,24)   ,CORN::measured_quality); //141222
    daily_provider.air_temperature_max.set_Celcius(MaxOfArray<double>(Hourly_Temperature,-9999,24)   ,CORN::measured_quality); //141222
    daily_provider.precipitation_actual.set_mm(SumOfArray<double>(Hourly_Precipitation,-9999,24)            ,CORN::measured_quality); //141222
    daily_provider.wind_speed.set_m_s(MeanOfArray<double>(Hourly_Wind,-9999,24)                      ,CORN::measured_quality); //150814
    assert(daily_provider.air_temperature_avg.Celcius() > -100 && daily_provider.air_temperature_avg.Celcius() < 60);
    assert(daily_provider.precipitation_actual.get_mm() >= 0.0);
    daily_provider.relative_humidity_avg.update_value_qualified_code(MeanOfArray<double>(Hourly_Relative_Humidity,-9999,24)  ,CORN::measured_quality); //141222
    daily_provider.relative_humidity_min.update_value_qualified_code(MinOfArray<double>(Hourly_Relative_Humidity,-9999,24)   ,CORN::measured_quality); //141222
    daily_provider.relative_humidity_max.update_value_qualified_code(MaxOfArray<double>(Hourly_Relative_Humidity,-9999,24)   ,CORN::measured_quality); //141222
    daily_provider.solar_radiation      .update_value_qualified_code(SumOfArray<double>(Hourly_Solar_Irradiance,-9999,24)    ,CORN::measured_quality); //141222 //(MJ/m2/day)
    daily_provider.update();                                                     //150814RLN
    #endif
    Daily_Wind_Speed_At_10m = MeanOfArray<double>(Hourly_Wind_Speed_At_10m,-9999,24);
    //Add list tavg list
    if (List_Daily_Mean_Temperature.size() >= 30) List_Daily_Mean_Temperature.pop_back();    //May change layer M.Liu Jan. 29, 2013
    List_Daily_Mean_Temperature.push_front
        (daily_provider.air_temperature_avg.Celcius());                          //141222RLN
}
//______________________________________________________________________________
void WeatherStateDailyClass::DetermineTimeWindowMeanTemperature(int Period_Length, double &Period_Mean_Temperature)
{
    double mean = 0;
    int periods = 0;
    for (std::list<double>::iterator it = List_Daily_Mean_Temperature.begin(); it != List_Daily_Mean_Temperature.end(); ++it) {
        if (periods < Period_Length) {
            periods++;
            mean += *it;
        }
        else it = List_Daily_Mean_Temperature.end();
    }
    Period_Mean_Temperature = mean/periods;
}
//______________________________________________________________________________
void WeatherStateDailyClass::ProvideChillHours()
{
    //Implement later M.Liu
    //double Twf[25];
    //double Tmin_today, Tmin_tomorrow, Tmax_yesterday, Tmax_today;
    //double Tmax, Tmin;
    //int year,doy;
    //bool End_Of_Year;
    //const double Pi = 3.14159
    double Chill_Hours_Today = 0;
    for (int i = 0;i < 24; i++) {
        //Calculate chill hours
        //tHourly_Temperature = round(Hourly_Temperature[i]*10.)/10.;
        double tHourly_Temperature = Hourly_Temperature[i];
        if (tHourly_Temperature >= 1.5 && tHourly_Temperature <= 2.5) Chill_Hours_Today += 0.5;
        else if (tHourly_Temperature > 2.5 && tHourly_Temperature <= 9.1) Chill_Hours_Today += 1.;
        else if (tHourly_Temperature > 9.1 && tHourly_Temperature <= 12.4) Chill_Hours_Today += 0.5;
        else if (tHourly_Temperature > 16 && tHourly_Temperature <= 18) Chill_Hours_Today -= 0.5;
        else Chill_Hours_Today += 0.;
    }
    Cumulative_Chill_Hours += Chill_Hours_Today;
    if (Cumulative_Chill_Hours < 0) Cumulative_Chill_Hours = 0;
}
//______________________________________________________________________________
// This method is actually already in CropSyst version, but need to check if the same
double WeatherStateDailyClass::CalculateSolarZenithAngle(int doy,int hour,double Latitude_Degrees)
{
      //Note: This function calculates solar zenith angle in radians, but reported back in degrees
      //Note: Latitude must be supplied in degrees
        //Hour: 0-23
      const double dtr = 0.0174533; //Convert degrees to radians
      double Latitude = Latitude_Degrees * dtr; //Convert degrees to radians
      double Sine_Solar_Declination = 0.39785 * sin(4.869 + 0.0172 * doy + 0.03345 * sin(6.224 + 0.0172 * doy));
      double Solar_Declination = Arcsin(Sine_Solar_Declination);
      //Calculate auxiliary trigonometric functions
      double cosz = sin(Latitude) * sin(Solar_Declination) 
                    + cos(Latitude) * cos(Solar_Declination) * cos(0.2618 * (hour - 12));
      double sinz = sqrt(1.0 - cosz * cosz);
      double z = (Pi / 2.0 - atan(cosz / sinz)) / dtr;
      if (cosz < 0) z = 90;
      return z;
}
//______________________________________________________________________________
double WeatherStateDailyClass::Arcsin(double X)
{
    return atan(X / sqrt(-X * X + 1.0));
}
//______________________________________________________________________________
void WeatherStateDailyClass::DetermineFurtherWeatherVariables()
{
    //150601 DetermineWindVelocityAt10m();
    #ifdef WEATHER_PROVIDER_VERSION
    daily_provider.update();
    #else
    #error obsolete
    DetermineDayTimeVPD();
    #endif
    DetermineHourlyRH();
    DetermineHourlyPp();                                                         //130903FMS
}
//______________________________________________________________________________
void WeatherStateDailyClass::DetermineHourlyRH()
{
    //LML NIY 14/04/18

    //RLN I already have this implemented if needed
    assert(false);
}
//______________________________________________________________________________
void WeatherStateDailyClass::DetermineHourlyPp()
{
    //LML NIY 14/04/18
    //RLN I already have this implemented if needed

    assert(false);
}
//______________________________________________________________________________
void WeatherStateDailyClass::DetermineWindVelocityAtSpecifiedHeight(int hour,double Specified_Height
                    ,double Roughness_Length,double Zero_Plane_Displacement,bool Default, double &u)
{
    //default: true: daily met data
    double Wind_Speed_At_Screening_Height(0),Zm(0),d(0);
    if (Default) {                                                               //140826FMS
        Wind_Speed_At_Screening_Height = Daily_Wind_Speed_At_Screening_Height;//WeatherData.GetWind(Year, DOY)
        const double Short_Grass_Height = 0.12;
        d = 0.65 * Short_Grass_Height;
        Zm = 0.1 * Short_Grass_Height;
    } else {
        Wind_Speed_At_Screening_Height = Hourly_Wind[hour];                      //140826FMS
        Zm = Roughness_Length;                                                   //140826FMS
        d = Zero_Plane_Displacement;                                             //140826FMS
    }
    double Short_Grass_Friction_Velocity = 0.4 * Wind_Speed_At_Screening_Height 
                                            / log((Screening_Height - d) / Zm);
    double Wind_Velocity_At_Specified_Height = (Short_Grass_Friction_Velocity / 0.4) 
                                                * log((Specified_Height - d) / Zm);
    u = std::max<double>(Wind_Velocity_At_Specified_Height,0);                                       //140826FMS
}
//______________________________________________________________________________
#ifdef CROPSYST_VERSION
bool WeatherStateDailyClass::get_parameter_on
(modifiable_ CS::Parameter &parameter
,nat32  variable_code // Typically the variable code will be UED variable code
,const CORN::Date_const &on_date)                                       rectification_
{
   //RLN Eventually we will use UED weather
   // where this is already implemented through the UED classes
   // so this would then go away.

   CORN::DOY on_doy = on_date.get_DOY();

   switch (variable_code)
      {  // WARNING these do not cross the year (it uses the value from the same year as today)!!!
         case UED_STD_VC_Tmin :
            parameter.force_amount(remember_weather->getDailyTmin(on_doy)); // daily_provider.air_temperature_min.Celcius());
            parameter.assume_code(CORN::observed_quality);
         break;
         case UED_STD_VC_Tmax :
              parameter.force_amount(remember_weather->getDailyTmax(on_doy)); // daily_provider.air_temperature_max.Celcius());
              parameter.assume_code(CORN::observed_quality);
         break;
         case UED_STD_VC_RHmax :
              parameter.force_amount(remember_weather->getDailyRelHumMax(on_doy));
              parameter.assume_code(CORN::observed_quality);
         break;
         case UED_STD_VC_RHmin :
              parameter.force_amount(remember_weather->getDailyRelHumMin(on_doy));
              parameter.assume_code(CORN::observed_quality);
         break;
         default :
            assert(false); // Currently I don't think I use get_parameter_on for any other elements
         break;
      }
   return true;
}
//_2015-12-15_________________________________________________get_parameter_on_/
float64 WeatherStateDailyClass::get_air_temperature_min_tomorrow()         const
{  return air_temperature_min_tomorrow;                                          //151223
}
//_2015-12-15_________________________________get_air_temperature_min_tomorrow_/
float64 WeatherStateDailyClass::get_air_temperature_max_yesterday()        const
{  return air_temperature_max_yesterday;                                         //151223
}
//_2015-12-15________________________________get_air_temperature_max_yesterday_/
#endif
#endif
