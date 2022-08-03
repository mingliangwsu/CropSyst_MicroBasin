#ifndef WEATHERSINGLEYEARCLASS_H
#define WEATHERSINGLEYEARCLASS_H

class WeatherSingleYearClass
{
    int num_days;           //Num of days per year (for array defination)

    //double *Day_Of_Year;                //(370) As Double
    double *P;                     //(370) As Double
    double *T_max;                      //(370) As Double
    double *T_min;                      //(370) As Double
    double *Srad;                       //(370) As Double
    double *Rel_Hum_Max;                //(370) As Double
    double *Rel_Hum_Min;                //(370) As Double
    double *Wind;                      //(370) As Double
    void initMem();
    void clearMem();
public:
    WeatherSingleYearClass(int _ndays);
    ~WeatherSingleYearClass();

    void initDayMet();
    void Read_Weather_File(const char* filename);
    double getPrecipitation(int doy);
    double getTmax(int doy);
    double getTmin(int doy);
    double getSolRad(int doy);
    double getRelHumMax(int doy);
    double getRelHumMin(int doy);
    double getWind(int doy);
};

#endif // WEATHERSINGLEYEARCLASS_H
