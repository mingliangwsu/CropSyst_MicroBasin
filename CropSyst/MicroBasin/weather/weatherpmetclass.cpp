#ifdef WEATHER_PROVIDER_VERSION
#error The weather provider provides Reference ET this file is not needed
#endif

#include "weatherpmetclass.h"
#include "util/constants.h"
#include "util/pubtools.h"
#include "math.h"

/*
WeatherPMETClass::WeatherPMETClass(WeatherReadFilesClass *_wDataRef,
                                   WeatherStateClass *_wStateRef,
                                   WeatherLocationInputClass *_wLocRef)
    :WeatherDataRef(*_wDataRef),WeatherStateRef(*_wStateRef),WeatherLocationInputRef(*_wLocRef)
{

};
*/
//______________________________________________________________________________
WeatherPMETClass::WeatherPMETClass() {};
//______________________________________________________________________________
void WeatherPMETClass::DeterminePMET(WeatherStateDailyClass &weather_daily,double latitude,
                                     double elevation, double albedo)
{
    const double rc = 0.00081;                           //day/m 'RS added
    const int doy = weather_daily.getCurrentDate().get_DOY();    //1-365/366
    //Read in weather data
    const double Lat = latitude;
    const double Altitude = elevation;
    const double Screening_Height = weather_daily.getScreeningHeight();
    const double Tmax = weather_daily.getDailyMaximumTemperature();
    const double Tmin = weather_daily.getDailyMinimumTemperature();
    const double Srad = weather_daily.getDailySolarRadiation();         //(MJ/m2/day)
    const double RHmax = weather_daily.getDailyMaximumRelativeHumidity();
    const double RHmin = weather_daily.getDailyMinimumRelativeHumidity();
    const double Wind = weather_daily.getDailyWindSpeed();
    if ( Tmax < -99  ||
         Tmin < -99  ||
         Srad < -99  ||
         RHmax < -99 ||
         RHmin < -99 ||
         Wind < -99) {
        std::clog<<"Weather data has problems!!!\n";
        exit(1);
    }
    double tmean = (Tmax + Tmin) / 2.0;
    double Es_Tmean = SatVP(tmean);
    double Es_Tmax = SatVP(Tmax);  //(kPa)
    double Es_Tmin = SatVP(Tmin);  //(kPa)
    double Actual_VP = VP(Es_Tmax, Es_Tmin, RHmax, RHmin);
    double Vap_Pres_Def = VPD(Es_Tmax, Es_Tmin, Actual_VP);
    double Pot_Rad = PotRad(Lat, doy);
    double Net_Rad = NetRad(albedo,Pot_Rad, Srad, Actual_VP, Tmax, Tmin);
    double Aero_Res = AeroRes(Wind, Screening_Height);
    double Slope_Sat_FN = delta(tmean, Es_Tmean);
    double Latent_Heat_Vap = Lambda(tmean);
    const double Psychrometric_Constant = gamma(Latent_Heat_Vap, Altitude);
    double Aero_Term = ETAeroTerm(Slope_Sat_FN, Psychrometric_Constant, Latent_Heat_Vap,
                           rc, Aero_Res, Vap_Pres_Def, tmean, Altitude);
    double Rad_Term = ETRadTerm(Slope_Sat_FN, Psychrometric_Constant, Latent_Heat_Vap,
                         Net_Rad, rc, Aero_Res);
    PM_ET = Aero_Term + Rad_Term;
    if (PM_ET < 1e-8) PM_ET = 1e-8;
    weather_daily.setReferenceCropET(PM_ET);   
    //Miscellanous variables used to adjust potential transpiration in response to factors increasing canopy resistance
    weather_daily.setPsychrometricConstant(Psychrometric_Constant);
    weather_daily.setSlopeSaturationVaporPressureFunctionOfTemperature(Slope_Sat_FN);
    weather_daily.setAerodynamicResistance(Aero_Res);
    weather_daily.setUnstressedCanopyResistance(rc);
}
//______________________________________________________________________________
double WeatherPMETClass::SatVP(double T)
{
    return 0.6108 * exp(17.27 * T / (T + 237.3));
}
//______________________________________________________________________________
double WeatherPMETClass::VP(double esTmax,double esTmin,double RHmax, double RHmin)
{
    return (esTmin * RHmax / 100.0 + esTmax * RHmin / 100.0) / 2.0;
}
//______________________________________________________________________________
double WeatherPMETClass::VPD(double esTmax,double esTmin,double ea)
{
    return (esTmax + esTmin) / 2.0 - ea;
}
//______________________________________________________________________________
double WeatherPMETClass::PotRad(double Lat,int doy)
{
    double Lat_rad = Lat * Pi / 180.0;
    double DR = 1.0 + 0.033 * cos(2.0 * Pi * (double)doy / 365.0);
    double SolDec = 0.409 * sin(2.0 * Pi * (double)doy / 365.0 - 1.39);
    double SunsetHourAngle = f_arccos(-tan(Lat_rad) * tan(SolDec));
    double Term = SunsetHourAngle * sin(Lat_rad) * sin(SolDec)
            + cos(Lat_rad) * cos(SolDec) * sin(SunsetHourAngle);
    return Solar_Constant_MJ * DR * Term / Pi;
}
//______________________________________________________________________________
double WeatherPMETClass::f_arccos(double x)
{
    return atan(-x / sqrt(-x * x + 1)) + 2 * atan((double)1);
}
//______________________________________________________________________________
double WeatherPMETClass::NetRad(double Albedo,double Pot_Rad,double Solar_Rad,
                                double Actual_VP,double Tmax,double Tmin)
{
    //Calculate shortwave net radiation
    //Const Albedo = 0.23
    double Rns = (1 - Albedo) * Solar_Rad;
    //Calculate cloud factor
    double F_Cloud = 1.35 * (Solar_Rad / (Pot_Rad * 0.75)) - 0.35;
    //Calculate humidity factor
    double F_Hum = (0.34 - 0.14 * sqrt(Actual_VP));
    //Calculate Isothermal LW net radiation
    double LWR = 0.000000004903 * (pow(Tmax + 273,4) + pow(Tmin + 273,4)) / 2.0;
    double Rnl = LWR * F_Cloud * F_Hum;
    //Calculate Rn
    return Rns - Rnl;
}
//______________________________________________________________________________
double WeatherPMETClass::AeroRes(double Uz,double z)
{
    double U2(0);
    const double VK = 0.41;
    if (CORN::is_approximately<double>(z,2.0,1e-12)) U2 = Uz;
    else U2 = Uz * (4.87 / (log(67.8 * z - 5.42)));
    if (U2 < 0.1) U2 = 0.1;       //FMS 8/27/2013 limit of U2
    U2 *= 86400;            //Convert to m/day
    double d = 0.08;
    const double zom = 0.01476;
    const double zoh = 0.001476;
    double Zm = 2;
    double zh = 2;
    double Term1 = log((Zm - d) / zom);
    double Term2 = log((zh - d) / zoh);
    return Term1 * Term2 / (VK * VK * U2);
}
//______________________________________________________________________________
double WeatherPMETClass::delta(double tmean,double esTmean)
{
    return 4098 * esTmean / pow(tmean + 237.3,2);
}
//______________________________________________________________________________
double WeatherPMETClass::Lambda(double tmean)
{
    return 2.501 - 0.002361 * tmean;
}
//______________________________________________________________________________
double WeatherPMETClass::gamma(double Lambda,double Altitude)
{
    double p = 101.3 * pow(((293 - 0.0065 * Altitude) / 293),5.26);
    return CP * p / (0.622 * Lambda);
}
//______________________________________________________________________________
double WeatherPMETClass::ETRadTerm(double delta,double gamma,double Lambda,
                 double Rn,double rc,double ra)
{
    double out = delta * Rn / (delta + gamma * (1.0 + rc / ra));
    out /= Lambda;
    return out;
}
//______________________________________________________________________________
double WeatherPMETClass::ETAeroTerm(double delta,double gamma,double Lambda,
                                    double rc,double ra,double VPD,double tmean,
                                    double Elev)
{
    double p = 101.3 * pow(((293.0 - 0.0065 * Elev) / 293.0),5.26);
    double Tkv = 1.01 * (tmean + 273);
    double AirDensity = 3.486 * p / Tkv;
    double VolHeatCap = CP * AirDensity;
    double out = (VolHeatCap * VPD / ra) / (delta + gamma * (1.0 + rc / ra));
    out /= Lambda;
    return out;
};
//______________________________________________________________________________
double WeatherPMETClass::getPMReferenceET()
{
        return PM_ET;
};
