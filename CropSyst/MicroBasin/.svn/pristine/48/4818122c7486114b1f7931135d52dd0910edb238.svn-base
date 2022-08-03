#include "weathersingleyearhourlyclass.h"
#include "util/pubtools.h"
#include "control/allcontrolclass.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <assert.h>     /* assert */
#include <sstream>

#include <cstring>

//160308RLN extern AllControlClass *control;
// Now just pass the invalid_met_label to constructor
//______________________________________________________________________________
WeatherSingleYearHourlyClass::WeatherSingleYearHourlyClass
(WeatherLocationInputClass &weather_station_
,int     ndays_
,double  invalid_met_label_)                                                     //160308
:weather_station  (weather_station_)
,invalid_met_label(invalid_met_label_)                                           //160308
,num_days         (ndays_)                                                       //160308
{
    //160308 num_days = ndays_;
    int numhours(0);
    if (weather_station.getTimeStepHours() == 24) numhours = 2;
    else numhours = 24;
    P.resize(num_days); // = alloc_2d_array<double>(num_days,numhours,"WeatherSingleYearHourlyClass::P");
    T.resize(num_days); // = alloc_2d_array<double>(num_days,numhours,"WeatherSingleYearHourlyClass::T");
    Srad.resize(num_days); // = alloc_2d_array<double>(num_days,numhours,"WeatherSingleYearHourlyClass::Srad");
    Rel_Hum.resize(num_days); // = alloc_2d_array<double>(num_days,numhours,"WeatherSingleYearHourlyClass::Rel_Hum");
    Wind.resize(num_days); // = alloc_2d_array<double>(num_days,numhours,"WeatherSingleYearHourlyClass::Wind");
    
    for (int i = 0; i < num_days; ++i){
        P[i].resize(numhours);
        T[i].resize(numhours);
        Srad[i].resize(numhours);
        Rel_Hum[i].resize(numhours);
        Wind[i].resize(numhours);
    }
    //initHourMet();
}
//______________________________________________________________________________
WeatherSingleYearHourlyClass::~WeatherSingleYearHourlyClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~WeatherSingleYearHourlyClass:"<<std::endl;
#endif
    //delete_2d_array(P,366);
    //delete_2d_array(T,366);
    //delete_2d_array(Srad,366);
    //delete_2d_array(Rel_Hum,366);
    //delete_2d_array(Wind,366);
#ifdef Destruct_Monitor
    std::cout<<"~WeatherSingleYearHourlyClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void WeatherSingleYearHourlyClass::initHourMet()
{
    //double tt = control->getInvalidMetLabel();
    //Initialize hourly data with invalid data at first
    int numhours(0);
    if (weather_station.getTimeStepHours() == 24) numhours = 2;
    else numhours = 24;
    for (int yday = 0; yday < num_days; yday++) {
        for (int h = 0;h < numhours; h++) {
            P[yday][h] = invalid_met_label; //160308RLN control->getInvalidMetLabel();
            T[yday][h] = invalid_met_label; //160308RLN control->getInvalidMetLabel();
            Srad[yday][h] = invalid_met_label; //160308RLN control->getInvalidMetLabel();
            Rel_Hum[yday][h] = invalid_met_label; //160308RLN control->getInvalidMetLabel();
            Wind[yday][h] = invalid_met_label; //160308RLN control->getInvalidMetLabel();
        }
    }
}
//______________________________________________________________________________
void WeatherSingleYearHourlyClass::Read_Weather_File(int year)
{
    //read hourly climate data
    //format & unit
    //DOY hour ppt(mm/hr) temp(celsius degree) srad(MJ/hr) RH(%) wind(m/s)
    const int start_hour = weather_station.getStartHourFormat();      //LML 140723 for different hourly data format
    initHourMet();
    std::string weatherstationfilename = getWeatherStationFileName(year);
    std::ifstream metFile(weatherstationfilename.c_str());

    if (metFile.is_open()) {
        std::string line("");
        while (std::getline(metFile,line)) {
            std::stringstream ss("");
            ss.str(line);
            int time_step(weather_station.getTimeStepHours());
            if (time_step == 1) {
                int doy(0),hour(0);
                double prec(-9999),Tp(-9999),SR(-9999),HR(-9999),WS(-9999);
                if (ss >> doy >> hour >> prec >> Tp >> SR >> HR >> WS) {
                    assert(prec >= 0.0);
                    assert(HR >= 0.0 && HR <= 100.0);
                    assert(Tp >= -50 && Tp <= 50);
                    assert(WS >= 0.0);
                    assert(SR >= 0.0);
                    int real_hour(0);   //LML 150216
                    if (doy < 0   ||
                        hour < 0  ||
                        hour > 24 ||
                        (hour == 24 && start_hour == 0)) {
                        std::clog<<"Weather data error in date format!"<<std::endl;
                    }
                    if (start_hour < 2) {
                        real_hour = hour-start_hour;
                    } else {
                        if (hour == 24) real_hour = 0;
                        else real_hour = hour;
                    }
                    P[doy-1][real_hour] = prec;



                    //double temp_coefficient = 10.0;
                    //P[doy-1][real_hour] *= temp_coefficient;
                    //std::cerr<<"DEBUG:hourly PPT multiplied by " << temp_coefficient << " times!!\n";




                    #if (defined(CHECK_OVERLANDFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_HOURLY_CASCADE_FOR_DEBUG))
                    //P[doy-1][real_hour] = 0;//prec; //DEBUGING!
                    //std::cout<<"PREC IS SETTING ZERO!!!\n";
                    if (real_hour == 0 && (doy == control->start_date.get_DOY())
                                       && ((year) == control->start_date.get_year()))
                        P[doy-1][real_hour] = 100;
                    else P[doy-1][real_hour] = 0;
                    std::clog<<"PREC IS SETTING 100 mm for first hour and zero for other hours!!!\n";
                    #else
                    #if (defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_EVAPORATION_FOR_DEBUG))
                    P[doy-1][real_hour] = 0;
                    static bool printed = false;
                    if (!printed) {
                        std::clog<<"PREC IS SETTING 0 FOR DEBUG!!!\n";
                        printed = true;
                    }
                    #endif
                    #endif


                    T[doy-1][real_hour] = Tp;
                    Srad[doy-1][real_hour] = SR;
                    Rel_Hum[doy-1][real_hour] = HR;
                    Wind[doy-1][real_hour] = WS;

                    /*std::cout<<"Year:"<<year<<" DOY:"<<doy<<" Hour:"<<hour
                            <<" prec:"<<P[doy-1][hour-start_hour]
                            <<" T:"<<T[doy-1][hour-start_hour]
                            <<std::endl;
                    */
                }
            } else if (time_step == 24) {
                int doy(0);
                double prec(-9999),Tmax(-9999),Tmin(-9999),SR(-9999),
                       HRmax(-9999),HRmin(-9999),WS(-9999);
                if (ss >> doy >> prec >> Tmax >> Tmin >> SR >> HRmax >> HRmin >> WS) {
                    //Day_Of_Year[i] = d;
                    assert(doy >= 0 && doy <= 366);
                    assert(prec >= 0.0);
                    assert(Tmax > -50.0 && Tmax < 50.0);
                    assert(Tmin > -50.0 && Tmin < 50.0);
                    assert(HRmax >= 0 && HRmax <= 100.0);
                    assert(HRmin >= 0 && HRmin <= 100.0);
                    assert(HRmax >= HRmin);
                    assert(SR >= 0.0);
                    assert(WS >= 0.0);
                    P[doy-1][0] = prec;

                    //double temp_coefficient = 20.0;
                    //P[doy-1][0] *= temp_coefficient;
                    //std::cerr<<"DEBUG:daily PPT multiplied by " << temp_coefficient << " times!!\n";

                    T[doy-1][0] = Tmax;
                    T[doy-1][1] = Tmin;
                    Srad[doy-1][0] = SR;
                    Rel_Hum[doy-1][0] = HRmax;
                    Rel_Hum[doy-1][1] = HRmin;
                    Wind[doy-1][0] = WS;
                    //std::cout<<"Year:"<<year<<" DOY:"<<doy<<" Hour:"<<hour<<" prec:"<<P[doy-1][hour-1]<<std::endl;
                }
            }
        }//end line
    } else {
        char errormessage[200];
        sprintf(errormessage,"Can't open weather file %s",weatherstationfilename.c_str());
        nrerror(errormessage);
    }
    metFile.close();
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailyP(int doy)
{
    //DOY: day of year from 1 to 365 for normal year
    if (weather_station.getTimeStepHours() == 1)
        return SumOfArray(P[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return P[doy-1][0];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailyTmax(int doy)
{
    //DOY: day of year from 1 to 365 for normal year
    if (weather_station.getTimeStepHours() == 1)
        return MaxOfArray(T[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return T[doy-1][0];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailyTmin(int doy)
{
    //doy: day of year from 1 to 365 for normal year
    if (weather_station.getTimeStepHours() == 1)
        return MinOfArray(T[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return T[doy-1][1];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailySolRad(int doy)
{
    //doy: day of year from 1 to 365 for normal year
    //(MJ/day)
    if (weather_station.getTimeStepHours() == 1)
        return SumOfArray(Srad[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return Srad[doy-1][0];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailyRelHumMax(int doy)
{
    if (weather_station.getTimeStepHours() == 1)
        return MaxOfArray(Rel_Hum[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return Rel_Hum[doy-1][0];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailyRelHumMin(int doy)
{
    if (weather_station.getTimeStepHours() == 1)
        return MinOfArray(Rel_Hum[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return Rel_Hum[doy-1][1];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getDailyWind(int doy)
{
    if (weather_station.getTimeStepHours() == 1)
        return MeanOfArray(Wind[doy-1],invalid_met_label /*160308RLN control->getInvalidMetLabel()*/,24);
    else return Wind[doy-1][0];
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getHourlyP(int doy,int hour)
{
    //doy: 1-365(366) hour:1-24
    if (weather_station.getTimeStepHours() == 1) {
        return P[doy-1][hour];
    } else {
        return -9999.0;
        assert(false);
    }
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getHourlyT(int doy,int hour)
{
    if (weather_station.getTimeStepHours() == 1) {
        return T[doy-1][hour];
    } else {
        return -9999.0;
        assert(false);
    }
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getHourlySolRad(int doy,int hour)
{
    if (weather_station.getTimeStepHours() == 1) {
        return Srad[doy-1][hour];
    } else {
        return -9999.0;
        assert(false);
    }
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getHourlyRelHum(int doy,int hour)
{
    if (weather_station.getTimeStepHours() == 1) {
        return Rel_Hum[doy-1][hour];
    } else {
        return -9999.0;
        assert(false);
    }
}
//______________________________________________________________________________
double WeatherSingleYearHourlyClass::getHourlyWind(int doy,int hour)
{
    if (weather_station.getTimeStepHours() == 1) {
        return Wind[doy-1][hour];
    } else {
        return -9999.0;
        assert(false);
    }
}
//______________________________________________________________________________
std::string WeatherSingleYearHourlyClass::getWeatherStationFileName(int year)
{
    std::ostringstream ss("");
    ss<<weather_station.getWeatherFilePath()<<weather_station.getWeatherFilePrefix()
      #ifdef CROPSYST_VERSION
      <<weather_station.get_ID()                                                 //141222
      #else
      <<weather_station.getStationID()
      #endif
      <<"_"<<year<<".dat";
    return ss.str();
}
//______________________________________________________________________________
#ifdef UNUSED
//141222RLN doesn't appear to be used anywhere probably can be deleted
double WeatherSingleYearHourlyClass::calAnnualMeanTemperature()
{
    double atavg = 0;
    int nums = 0;
    int numhours;
    if (weather_station.getTimeStepHours() == 24) numhours = 2;
    else numhours = 24;
    for (int doy = 0; doy < 366; doy++) {
        for (int hour = 0; hour < numhours; hour++) {
            if (!is_approximately<double>(T[doy][hour],control->getInvalidMetLabel())) {
                atavg += T[doy][hour];
                nums++;
            }
        }
    }
    if (nums >= 270) return atavg;
    else return control->getInvalidMetLabel();
}
#endif
//______________________________________________________________________________
