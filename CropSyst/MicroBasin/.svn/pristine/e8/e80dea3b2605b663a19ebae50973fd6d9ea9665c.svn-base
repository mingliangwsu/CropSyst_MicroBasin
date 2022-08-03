#ifndef WEATHERREADFILESCLASS_H
#define WEATHERREADFILESCLASS_H
#include "weatherlocationinputclass.h"
#include "weathersingleyearclass.h"
#include "weathersingleyearhourlyclass.h"

class WeatherReadFilesClass
{
    int num_years;                              //num of years
#ifdef HOURLY_MET
    WeatherSingleYearHourlyClass *Annual_Weather_Hourly;
#else
    WeatherSingleYearClass *Annual_Weather;     //(100) As New
#endif
    int *Years;                                 //(100) As Integer
    std::string Path,Prefix;
    void initMem();
    void clearMem();

public:
    WeatherLocationInputClass& WeatherLocationInputRef;

public:
    WeatherReadFilesClass(int _nyears,WeatherLocationInputClass &_WeatherLocationInputRef);//WeatherLocationInputClass *_weatherloc);
    ~WeatherReadFilesClass();

    //void setPathPrefix();
    int FindYearIndex(int year);

#ifdef HOURLY_MET
#else
    double getPrecipitation_mm(int year,int doy);
    double getTmax(int year,int doy);
    double getTmin(int year,int doy);
    double getSolRad(int year,int doy);
    double getHumRelMax(int year,int doy);
    double getHumRelMin(int year,int doy);
    double getWind(int year,int doy);
#endif

};

#endif // WEATHERREADFILESCLASS_H
