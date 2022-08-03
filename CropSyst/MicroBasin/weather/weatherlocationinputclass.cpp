#include "weatherlocationinputclass.h"
#include <string>
#include <iostream>
//______________________________________________________________________________
WeatherLocationInputClass::WeatherLocationInputClass()
{
    proj_x = 0;
    proj_y = 0;
    Weather_File_Path.assign("");
    Weather_File_Prefix.assign("");
    Time_Step_Hours = 1;        //LML 140613 default is hourly data
    Start_Hour_Format = 1;      //LML 140723 default hour data is 1-24
}
//______________________________________________________________________________
std::string WeatherLocationInputClass::getWeatherFilePath()
{  return Weather_File_Path; }
//______________________________________________________________________________
std::string WeatherLocationInputClass::getWeatherFilePrefix()
{  return Weather_File_Prefix; }
//______________________________________________________________________________
double WeatherLocationInputClass::getProjX() {return proj_x;}
//______________________________________________________________________________
double WeatherLocationInputClass::getProjY() {return proj_y;}
//______________________________________________________________________________
int WeatherLocationInputClass::getTimeStepHours() {return Time_Step_Hours;}
void WeatherLocationInputClass::setProjX(double data) {proj_x = data;}
//______________________________________________________________________________
void WeatherLocationInputClass::setProjY(double data) {proj_y = data;}
//______________________________________________________________________________
void WeatherLocationInputClass::setWeatherFilePath(std::string path) {Weather_File_Path = path;}
//______________________________________________________________________________
void WeatherLocationInputClass::setWeatherFilePrefix(std::string pref) {Weather_File_Prefix.assign(pref);}
//______________________________________________________________________________
void WeatherLocationInputClass::setInnerID(long _innerID) {inner_id = _innerID;}
//______________________________________________________________________________
long WeatherLocationInputClass::getInnerID() {return inner_id;}
//______________________________________________________________________________
void WeatherLocationInputClass::setTimeStepHours(int time_step) {Time_Step_Hours = time_step;}
//______________________________________________________________________________
int WeatherLocationInputClass::getStartHourFormat() {return Start_Hour_Format;}
//______________________________________________________________________________
void WeatherLocationInputClass::setStartHourFormat(int data) {Start_Hour_Format = data;}
//______________________________________________________________________________
#ifdef MACA_V1_MBMET
void WeatherLocationInputClass::SnapToGridCenter_Lat(double start_lat,double cellsize)
{
    int nlat = (int)floor((Latitude - start_lat) / cellsize + 0.5);
    Latitude = start_lat + cellsize * nlat;
}
//______________________________________________________________________________
void WeatherLocationInputClass::SnapToGridCenter_Lon(double start_lon,double cellsize)
{
    int nlon = (int)floor((Longitude - start_lon) / cellsize + 0.5);
    Longitude = start_lon + cellsize * nlon;
}
//______________________________________________________________________________
#endif
