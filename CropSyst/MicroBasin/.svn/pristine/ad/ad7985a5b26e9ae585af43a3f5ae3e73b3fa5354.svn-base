#ifndef WEATHERPMETCLASS_H
#define WEATHERPMETCLASS_H
//#include "weatherreadfilesclass.h"
//#include "weatherstateclass.h"
//#include "weatherlocationinputclass.h"
#include "weatherstatedailyclass.h"

class WeatherStateDailyClass;
//______________________________________________________________________________
class WeatherPMETClass
{
    double PM_ET;
    //referencing
public:
    //WeatherReadFilesClass& WeatherDataRef;
    //WeatherStateClass& WeatherStateRef;
    //WeatherLocationInputClass& WeatherLocationInputRef;
public:
    //WeatherPMETClass(WeatherReadFilesClass *_wDataRef,
                     //WeatherStateClass *_wStateRef,
                     //WeatherLocationInputClass *_wLocRef);
    WeatherPMETClass();
    void DeterminePMET(WeatherStateDailyClass &weather_daily,double latitude,
                       double elevation, double albedo);
    double SatVP(double T);
    double VP(double esTmax,double esTmin,double RHmax, double RHmin);
    double VPD(double esTmax,double esTmin,double ea);
    double PotRad(double Lat,int doy);
    double f_arccos(double x);
    double NetRad(double Albedo,double Pot_Rad,double Solar_Rad,
                                    double Actual_VP,double Tmax,double Tmin);
    double AeroRes(double Uz,double z);
    double delta(double tmean,double esTmean);
    double Lambda(double tmean);
    double gamma(double Lambda,double Altitude);
    double ETRadTerm(double delta,double gamma,double Lambda,
                     double Rn,double rc,double ra);
    double ETAeroTerm(double delta,double gamma,double Lambda,
                                        double rc,double ra,double VPD,double tmean,
                                        double Elev);
    double getPMReferenceET();
};
//_2014_________________________________________________________________________
#endif // WEATHERPMETCLASS_H
