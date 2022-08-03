#ifndef WEATHERLOCATIONINPUTCLASS_H
#define WEATHERLOCATIONINPUTCLASS_H
#include <string>
#  include "common/geodesy/geolocation.h"
//______________________________________________________________________________
class WeatherLocationInputClass
: public extends_ Geolocation
{
    long inner_id;                   //inner ID for locating weather record
    double proj_x;                  //projected x
    double proj_y;
    std::string Weather_File_Path;
    std::string Weather_File_Prefix;
    int Time_Step_Hours;            //LML 140613 24: daily data 1:hourly data
    int Start_Hour_Format;          //LML 140723 hourly data time format (0-23/0 or 1-24/1)?
                                    //LML 150216 if 2: start from "24" which is hour zero
    /*141222RLN moved
    It really isn't necessary to have these values for every site.
    This is just used to initialize soil temperature
    phase and amplitude do not vary much in a region
    The average annual temperature, if significantly varying, should be calculated
    from provided daily data (but this really isn't necessary).
    These parameters have been move to simulation control common to all cells.
    (In CROPSYST_VERSION these are in CropSyst::Scenario).
    */
 public:
    WeatherLocationInputClass();
 public:
    double getProjX();
    double getProjY();
    std::string getWeatherFilePath();
    std::string getWeatherFilePrefix();
    int getTimeStepHours();
    void setProjX(double data);
    void setProjY(double data);
    void setWeatherFilePath(std::string path);
    void setWeatherFilePrefix(std::string pref);
    void setInnerID(long _innerID);
    void setTimeStepHours(int time_step);
    long getInnerID();
    int getStartHourFormat();
    void setStartHourFormat(int data);
    #ifdef MACA_V1_MBMET
    void SnapToGridCenter_Lon(double start_lon,double cellsize);
    void SnapToGridCenter_Lat(double start_lat,double cellsize);
    #endif
};
//______________________________________________________________________________
#endif // WEATHERLOCATIONINPUTCLASS_H
