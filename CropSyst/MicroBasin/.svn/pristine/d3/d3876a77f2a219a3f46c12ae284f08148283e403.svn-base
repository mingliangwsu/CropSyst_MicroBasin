#ifndef WEATHERSINGLEYEARHOURLYCLASS_H
#define WEATHERSINGLEYEARHOURLYCLASS_H
#include "weather/weatherlocationinputclass.h"
#include <vector>
//______________________________________________________________________________
class WeatherSingleYearHourlyClass
{
    int num_days;                           //Num of days per year (for array defination)
    //int *Day_Of_Year;                     //(year_day)
    std::vector<std::vector<double> > P;                             //(mm/Time) [year_day][hour]
    std::vector<std::vector<double> > T;                             //(Celsius degree) [year_day][hour]
    std::vector<std::vector<double> > Srad;                          //(MJ/m2/Time)
    std::vector<std::vector<double> > Rel_Hum;                       //(%)
    std::vector<std::vector<double> > Wind;                          //(m/s) wind speed at screening hight
    //LML 140613 for reading daily data, [doy][0] is max value, and [doy][1] is min valye.
    double invalid_met_label;                                                    //160307RLN
public:
    WeatherLocationInputClass &weather_station;

    WeatherSingleYearHourlyClass
       (WeatherLocationInputClass &weather_station_, int ndays_
       ,double invalid_met_label_);                                              //160308
    ~WeatherSingleYearHourlyClass();
    void initHourMet();
    void Read_Weather_File(int year);
    //LML 140815 doy always start from 1
    double getDailyP(int doy);
    double getDailyTmax(int doy);
    double getDailyTmin(int doy);
    double getDailySolRad(int doy);
    double getDailyRelHumMax(int doy);
    double getDailyRelHumMin(int doy);
    double getDailyWind(int doy);
    double getHourlyP(int doy,int hour);    //hour:0-23:59:59
    double getHourlyT(int doy,int hour);
    double getHourlySolRad(int doy,int hour);
    double getHourlyRelHum(int doy,int hour);
    double getHourlyWind(int doy,int hour);
    double calAnnualMeanTemperature();
    std::string getWeatherStationFileName(int year);
};
//______________________________________________________________________________
#endif // WEATHERSINGLEYEARHOURLYCLASS_H
