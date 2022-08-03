#include "weatherstateclass.h"
#include "math.h"
#include "stdlib.h"
#include "util/constants.h"
#include "util/pubtools.h"
#include <iostream>

//#include <string>

//extern double **alloc_2d_array<double>(int rows,int columns,const char* varname);
//extern double *alloc_1d_array<double>(int rows,const char* varname);

WeatherStateClass::WeatherStateClass(int _nyear,int _nday,int _nhour)
{
    num_years = _nyear;
    num_days = _nday;
    num_hours = _nhour;

    initMem();
};

WeatherStateClass::~WeatherStateClass()
{
    std::cout<<"~WeatherStateClass"<<std::endl;

    clearMem();
    std::cout<<"~WeatherStateClass done "<<std::endl;
};

void WeatherStateClass::initMem()
{
    Reference_ET = alloc_2d_array<double>(num_years,num_days,"Reference_ET");
    Actual_Crop_Potential_Transpiration = alloc_2d_array<double>(num_years,num_days,"Actual_Crop_Potential_Transpiration");
    Potential_Crop_Potential_Transpiration = alloc_2d_array<double>(num_years,num_days,"Potential_Crop_Potential_Transpiration");
    Actual_Crop_Transpiration = alloc_2d_array<double>(num_years,num_days,"Actual_Crop_Transpiration");
    Day_Time_VPD = alloc_2d_array<double>(num_years,num_days,"Day_Time_VPD");
    VPD_Max = alloc_2d_array<double>(num_years,num_days,"VPD_Max");
    Daily_Wind_Speed_At_10m = alloc_2d_array<double>(num_years,num_days,"Daily_Wind_Speed_At_10m");
    Hourly_Temperature = alloc_1d_array<double>(num_hours,"Hourly_Temperature");
    Stressed_Plant_Hourly_Temperature = alloc_1d_array<double>(num_hours,"Stressed_Plant_Hourly_Temperature");
    Hourly_Fraction_Of_Solar_Irradiance = alloc_1d_array<double>(num_hours,"Hourly_Fraction_Of_Solar_Irradiance");
    Hourly_Solar_Zenith_Angle = alloc_1d_array<double>(num_hours,"Hourly_Solar_Zenith_Angle");
    Hourly_Diffuse_Solar_Irradiance = alloc_1d_array<double>(num_hours,"Hourly_Diffuse_Solar_Irradiance");
    Hourly_Direct_Solar_Irradiance = alloc_1d_array<double>(num_hours,"Hourly_Direct_Solar_Irradiance");
    Hourly_Solar_Irradiance = alloc_1d_array<double>(num_hours,"Hourly_Solar_Irradiance");
    Hourly_Extraterrestrial_Solar_Radiation = alloc_1d_array<double>(num_hours,"Hourly_Extraterrestrial_Solar_Radiation");
    Hourly_Canopy_Solar_Interception_Fraction = alloc_1d_array<double>(num_hours,"Hourly_Canopy_Solar_Interception_Fraction");
    Hourly_Standing_Stubble_Solar_Interception_Fraction = alloc_1d_array<double>(num_hours,"Hourly_Standing_Stubble_Solar_Interception_Fraction");
    Hourly_Surface_Residue_Solar_Interception_Fraction = alloc_1d_array<double>(num_hours,"Hourly_Surface_Residue_Solar_Interception_Fraction");
    Hourly_Sunlit_LAI = alloc_1d_array<double>(num_hours,"Hourly_Sunlit_LAI");
    Hourly_Shaded_LAI = alloc_1d_array<double>(num_hours,"Hourly_Shaded_LAI");
    Hourly_SunlitLAI_Solar_Interception_Fraction = alloc_1d_array<double>(num_hours,"Hourly_SunlitLAI_Solar_Interception_Fraction");
    Hourly_ShadedLAI_Solar_Interception_Fraction = alloc_1d_array<double>(num_hours,"Hourly_ShadedLAI_Solar_Interception_Fraction");
    Daily_Green_Canopy_Solar_Interception_Fraction = alloc_2d_array<double>(num_years,num_days,"Daily_Green_Canopy_Solar_Interception_Fraction");
    Daily_Canopy_Solar_Interception_Fraction = alloc_2d_array<double>(num_years,num_days,"Daily_Canopy_Solar_Interception_Fraction");
    Daily_Standing_Stubble_Solar_Interception_Fraction = alloc_2d_array<double>(num_years,num_days,"Daily_Standing_Stubble_Solar_Interception_Fraction");
    Daily_Surface_Residue_Solar_Interception_Fraction = alloc_2d_array<double>(num_years,num_days,"Daily_Surface_Residue_Solar_Interception_Fraction");
    Daily_Diffuse_Solar_Irradiance = alloc_1d_array<double>(num_days,"Daily_Diffuse_Solar_Irradiance");
    Daily_Direct_Solar_Irradiance = alloc_1d_array<double>(num_days,"Daily_Direct_Solar_Irradiance");
    Daily_Sunlit_LAI = alloc_1d_array<double>(num_days,"Daily_Sunlit_LAI");
    Daily_Shaded_LAI = alloc_1d_array<double>(num_days,"Daily_Shaded_LAI");
    Daily_SunlitLAI_Solar_Interception_Fraction = alloc_1d_array<double>(num_days,"Daily_SunlitLAI_Solar_Interception_Fraction");
    Daily_ShadedLAI_Solar_Interception_Fraction = alloc_1d_array<double>(num_days,"Daily_ShadedLAI_Solar_Interception_Fraction");
    Daily_Extraterrestrial_Solar_Radiation = alloc_1d_array<double>(num_days,"Daily_Extraterrestrial_Solar_Radiation");
};

void WeatherStateClass::clearMem()
{
    delete_2d_array(Reference_ET,num_years);
    delete_2d_array(Actual_Crop_Potential_Transpiration,num_years);
    delete_2d_array(Potential_Crop_Potential_Transpiration,num_years);
    delete_2d_array(Actual_Crop_Transpiration,num_years);
    delete_2d_array(Day_Time_VPD,num_years);
    delete_2d_array(VPD_Max,num_years);
    delete_2d_array(Daily_Wind_Speed_At_10m,num_years);
    free(Hourly_Temperature);
    free(Stressed_Plant_Hourly_Temperature);
    free(Hourly_Fraction_Of_Solar_Irradiance);
    free(Hourly_Solar_Zenith_Angle);
    free(Hourly_Diffuse_Solar_Irradiance);
    free(Hourly_Direct_Solar_Irradiance);
    free(Hourly_Solar_Irradiance);
    free(Hourly_Extraterrestrial_Solar_Radiation);
    free(Hourly_Canopy_Solar_Interception_Fraction);
    free(Hourly_Standing_Stubble_Solar_Interception_Fraction);
    free(Hourly_Surface_Residue_Solar_Interception_Fraction);
    free(Hourly_Sunlit_LAI);
    free(Hourly_Shaded_LAI);
    free(Hourly_SunlitLAI_Solar_Interception_Fraction);
    free(Hourly_ShadedLAI_Solar_Interception_Fraction);
    delete_2d_array(Daily_Green_Canopy_Solar_Interception_Fraction,num_years);
    delete_2d_array(Daily_Canopy_Solar_Interception_Fraction,num_years);
    delete_2d_array(Daily_Standing_Stubble_Solar_Interception_Fraction,num_years);
    delete_2d_array(Daily_Surface_Residue_Solar_Interception_Fraction,num_years);
    free(Daily_Diffuse_Solar_Irradiance);
    free(Daily_Direct_Solar_Irradiance);
    free(Daily_Sunlit_LAI);
    free(Daily_Shaded_LAI);
    free(Daily_SunlitLAI_Solar_Interception_Fraction);
    free(Daily_ShadedLAI_Solar_Interception_Fraction);
    free(Daily_Extraterrestrial_Solar_Radiation);
}

double WeatherStateClass::HourlyVPDAir(double T,double RH)
{
    //RH: relative humidity (%)
    //T: Air temperature (degree)
    double out;     //Hourly air VPD (kPa)

    out = VP(T) * (1 - RH / 100);
    return(out);
};

double WeatherStateClass::VP(double T)
{
    //T: Air temperature (degree)
    const double a = 0.611;
    const double b = 17.502;
    const double c = 240.97;
    double out;         //Saturation vapour pressure of air (kPa)

    out = a * exp(T * b / (T + c));
    return(out);
};

void WeatherStateClass::PassStateToNextDay(int CurrentYearCount,int Today,int LastDOYOfPreviousYear)
{
    //RS changed a little bit
    int Yesterday;
    int YesterdayYearCount;

    if(Today == 1){
        Yesterday = LastDOYOfPreviousYear;
        YesterdayYearCount = CurrentYearCount - 1;
    }
    else{
        Yesterday = Today - 1;
        YesterdayYearCount = CurrentYearCount;
    }


    //RS comment: not sure if these parameters should be Weather properties
    setDailyGreenCanopySolarInterceptionFraction(CurrentYearCount,Today,getDailyGreenCanopySolarInterceptionFraction(YesterdayYearCount, Yesterday));
    setDailyCanopySolarInterceptionFraction(CurrentYearCount, Today,getDailyCanopySolarInterceptionFraction(YesterdayYearCount, Yesterday));
    setDailyStandingStubbleSolarInterceptionFraction(CurrentYearCount,Today,getDailyStandingStubbleSolarInterceptionFraction(YesterdayYearCount, Yesterday));
    setDailySurfaceResidueSolarInterceptionFraction(CurrentYearCount,Today,getDailySurfaceResidueSolarInterceptionFraction(YesterdayYearCount, Yesterday));
};

double WeatherStateClass::DeclinationOfSun(double JulianDay)
{
    //declination of the sun in radians above the celestial equator
    double out;     //Declination of sun (radians)

    out = 0.409 * sin(2 * Pi / 365 * JulianDay - 1.39);
    return(out);
};

double WeatherStateClass::relativeSunEarthDistance(double JulianDay)
{
    double out;     //relative Sun-Earth Distance
    out = 1 + 0.033 * cos(2 * Pi / 365 * JulianDay);
    return(out);
};

double WeatherStateClass::SunsetSunriseHourAngle(double JulianDay,double Lat)
{
    double out;
    out = acos(-tan(Pi / 180 * Lat) * tan(DeclinationOfSun(JulianDay)));
    return(out);
};

double WeatherStateClass::ExTerrRadiation(double JulianDay,double Lat)
{
    //calculates extra-terrestrial radiation (Ra) in (MJ/m2/d)
    //Lat (°)
    double Solar_Constant;      //MJ/m2/d
    double Lat_arc;
    double out;                 //extra-terrestrial radiation (Ra) (MJ/m2/d)

    Lat_arc = Lat * Pi / 180;
    Solar_Constant = Solar_Const_W / 1000000 * 60 * 60 * 24;

    out = Solar_Constant / Pi * relativeSunEarthDistance(JulianDay)
                      * (SunsetSunriseHourAngle(JulianDay, Lat) * sin(DeclinationOfSun(JulianDay)) * sin(Lat_arc)
                         + cos(Lat_arc) * cos(DeclinationOfSun(JulianDay)) * sin(SunsetSunriseHourAngle(JulianDay, Lat)));
    return(out);

};

double WeatherStateClass::maxSunHours(double JulianDay,double Lat)
{
    double out;             //maximum sun hours (hr)
    out = 24.0 / Pi * SunsetSunriseHourAngle(JulianDay, Lat);
    return(out);
};

double WeatherStateClass::WOZ(double JulianDay,int HourOfDay,double Longi,double Longi_timezone)
{
    //out: wahre Ortszeit
    //Longi_timezone;      //standard latitude of time zone (should be timezone*15°)
    double Et;                  //equation of time
    double Lc;                  //longitude correction
    double Be;
    double out;

    //Longi_timezone = 15;        //just for this calculation

    Be = (JulianDay - 1) * 360 / 365;

    Et = 229.2 * (0.000075 + 0.001868 * cos(Be) - 0.032077 * sin(Be)
                  - 0.014615 * cos(2 * Be) - 0.040849 * sin(2 * Be)); //min
    Lc = 4 * (Longi_timezone - Longi); //min

    out = HourOfDay - (Lc + Et) / 60;

    return(out);
};
double WeatherStateClass::SunHourAngle(double HourOfDay)
{
    //sun hour angle (degree)
    double out;
    out = (HourOfDay - 12) * 15;
    return(out);
};


double WeatherStateClass::SunAngle(double JulianDay,int HourOfDay,double Lat)
{
    double DeklSun;
    double SHA;
    double out;

    DeklSun = DeclinationOfSun(JulianDay) * 180 / Pi;
    SHA = SunHourAngle(HourOfDay) * 180 / Pi;

    out = asin(sin(DeklSun) * sin(Lat) + cos(DeklSun) * cos(Lat) * cos(SHA)) * 180 / Pi;
    return(out);
};

double WeatherStateClass::Sonnenscheindauer(double JulianDay, double Lat)
{
    double Lat_arc;
    double out;
    Lat_arc = Lat * Pi / 180;

    out = 2 / 15 * 180 / Pi * acos(-tan(Lat_arc) * tan(DeclinationOfSun(JulianDay)));
    return(out);
};

double WeatherStateClass::calcHourlySolarZenithAngle(double doy,int hour,double Latitude)
{
    //This function calculates the solar zenith angle (°)
    double cosz,sinz,z;
    double Sine_Solar_Declination;
    double Solar_Declination;
    double Lat_rad;

    Lat_rad = Latitude * Pi / 180;

    Sine_Solar_Declination = 0.39785 * sin(4.869 + 0.0172 * doy
                                           + 0.03345 * sin(6.224 + 0.0172 * doy));

    Solar_Declination = asin(Sine_Solar_Declination);

    //Calculate auxiliary trigonometric functions
    cosz = sin(Lat_rad) * sin(Solar_Declination)
            + cos(Lat_rad) * cos(Solar_Declination) * cos(0.2618 * (hour - 12));

    sinz = sqrt(1 - cosz * cosz);

    z = (Pi / 2 - atan(cosz / sinz)) * 180 / Pi;

    if(cosz < 0) z = 90;

    return(z);
};

double WeatherStateClass::calcHourlyExtraterrestrialRadiation(double Solar_Zenith_Angle,double JulianDay,int hour)
{
    double Earth_Sun_Distance;
    double Cosine_Solar_Zenith_Angle;
    double out;

    Earth_Sun_Distance = relativeSunEarthDistance(JulianDay);   //was: = 1 + 0.0334 * Cos(0.01721 * doy - 0.0552)
    Cosine_Solar_Zenith_Angle = cos(Solar_Zenith_Angle * Pi / 180);

    out = Solar_Const_W * Earth_Sun_Distance * Cosine_Solar_Zenith_Angle;
    if(out<0.0) out = 0.0;

    return(out);
    //RS changed: the above equation used to have the square of the earth-sun distance, I have erased this - doesn't seem to follow the underlying physics
};

double WeatherStateClass::getHourlyRadiationFraction(int HourOfDay,double JulianDay,double Latitude)
{
    //this equation uses the solar zenit angle data to derive hourly fraction of radiation
    //these could be used for slicing daily observed Rs data into hourly values

    int h;
    double HourlySunZenitAngle[25];    //(24) As Double
    double SumHourlySZA=0.0;
    double out;

    for(h=1;h<=24;h++){
        HourlySunZenitAngle[h] = calcHourlySolarZenithAngle(JulianDay, h, Latitude);
        if(HourlySunZenitAngle[h] < 90){
            //sum for times when sun has risen
            SumHourlySZA += cos(HourlySunZenitAngle[h] * Pi / 180);
        }
    }

    if(HourlySunZenitAngle[HourOfDay] == 90.0) out = 0.0;
    else out = cos(HourlySunZenitAngle[HourOfDay] * Pi / 180) / SumHourlySZA;

    return(out);
};

double WeatherStateClass::calcSatVP(double T)
{
    //moved here from SoilTemperatureClass
    double out;
    out = 0.6108 * exp(17.27 * T / (T + 237.3));

    return(out);
};

double WeatherStateClass::calcSkyEmissivity(double vapor_pressure,double Tair,double Cloud_Cover)
{
    double clear_sky_emissivity;
    double T_Kelvin;
    double out;

    T_Kelvin = Tair + 273.15;   //Tair in Kelvin

    if(vapor_pressure == -999) clear_sky_emissivity = 0.0000092 * pow(T_Kelvin,2.0);
    else clear_sky_emissivity = 1.72 * pow(vapor_pressure / T_Kelvin, 1.0/7.0);

    out = (1 - 0.84 * Cloud_Cover) * clear_sky_emissivity + 0.84 * Cloud_Cover;

    return(out);
};

double WeatherStateClass::calcHourlyTemperature(int HourOfDay,double Tmax_today,double Tmax_yesterday,
                               double Tmin_today,double Tmin_tomorrow)
{
    double Twf;
    double Tn,Tx;
    double out;

    Twf = 0.44 - 0.46 * sin(HourOfDay * Pi / 12 + 0.9) + 0.11 * sin(2 * HourOfDay * Pi / 12 + 0.9);

    if(HourOfDay <= 5){
        Tn = Tmin_today;
        Tx = Tmax_yesterday;
    }
    else{
            if(HourOfDay > 14){
                Tn = Tmin_tomorrow;
                Tx = Tmax_today;
            }
            else{
                Tn = Tmin_today;
                Tx = Tmax_today;
            }
    }

    out = Twf * Tx + (1 - Twf) * Tn;
    Hourly_Temperature[HourOfDay] = out;
    return(out);
};

double WeatherStateClass::calcHourlyHumidity(int HourOfDay,double RHmax_today,double RHmax_tomorrow,
                            double RHmin_today,double RHmin_yesterday)
{
    double Twf;
    double RHn,RHx;
    double out;

    Twf = 0.44 - 0.46 * sin(HourOfDay * Pi / 12 + 0.9) + 0.11 * sin(2 * HourOfDay * Pi / 12 + 0.9);

    if(HourOfDay <= 5){
        RHn = RHmin_yesterday;
        RHx = RHmax_today;
    }
    else{
        if(HourOfDay > 14){
            RHn = RHmin_today;
            RHx = RHmax_tomorrow;
        }
        else{
            RHn = RHmin_today;
            RHx = RHmax_today;
        }
    }

    out = Twf * RHn + (1 - Twf) * RHx;

    Hourly_Relative_Humidity[HourOfDay] = out;
    return(out);
};
void WeatherStateClass::setReferenceCropET(int Year_Count,int doy,double Ref_ET)
{
    Reference_ET[Year_Count][doy] = Ref_ET;
};
double WeatherStateClass::getReferenceCropET(int Year_Count,int doy)
{
    return(Reference_ET[Year_Count][doy]);
};
void WeatherStateClass::setActualCropPotentialTranspiration(int Year_Count,int doy,double PT)
{
    Actual_Crop_Potential_Transpiration[Year_Count][doy] = PT;
};
double WeatherStateClass::getActualCropPotentialTranspiration(int Year_Count,int doy)
{
    return(Actual_Crop_Potential_Transpiration[Year_Count][doy]);
};
void WeatherStateClass::setPotentialCropPotentialTranspiration(int Year_Count,int doy,double PPT)
{
    Potential_Crop_Potential_Transpiration[Year_Count][doy] = PPT;
};
double WeatherStateClass::getPotentialCropPotentialTranspiration(int Year_Count,int doy)
{
    return(Potential_Crop_Potential_Transpiration[Year_Count][doy]);
};
void WeatherStateClass::setActualCropTranspiration(int Year_Count,int doy,double AT)
{
    Actual_Crop_Transpiration[Year_Count][doy] = AT;
};
double WeatherStateClass::getActualCropTranspiration(int Year_Count,int doy)
{
    return(Actual_Crop_Transpiration[Year_Count][doy]);
};
void WeatherStateClass::setDayTimeVPD(int Year_Count,int doy,double DTVPD)
{
    Day_Time_VPD[Year_Count][doy] = DTVPD;
};
double WeatherStateClass::getDayTimeVPD(int Year_Count,int doy)
{
    return(Day_Time_VPD[Year_Count][doy]);
};
void WeatherStateClass::setVPDMax(int Year_Count,int doy,double DMAX)
{
    VPD_Max[Year_Count][doy] = DMAX;
};
double WeatherStateClass::getVPDMax(int Year_Count,int doy)
{
    return(VPD_Max[Year_Count][doy]);
};
void WeatherStateClass::setDailyWindSpeedAt10m(int Year_Count,int doy,double DWS10)
{
    Daily_Wind_Speed_At_10m[Year_Count][doy] = DWS10;
};
double WeatherStateClass::getDailyWindSpeedAt10m(int Year_Count,int doy)
{
    return(Daily_Wind_Speed_At_10m[Year_Count][doy]);
};
void WeatherStateClass::setHourlyTemperature(int hour,double HT)
{
    Hourly_Temperature[hour] = HT;
};
double WeatherStateClass::getHourlyTemperature(int hour)
{
    return(Hourly_Temperature[hour]);
};
void WeatherStateClass::setHourlyRelativeHumidity(int hour,double HT)
{
    Hourly_Relative_Humidity[hour] = HT;
};
double WeatherStateClass::getHourlyRelativeHumidity(int hour)
{
    return(Hourly_Relative_Humidity[hour]);
};
void WeatherStateClass::setHourlyFractionOfSolarIrradiance(int hour,double HFSI)
{
    Hourly_Fraction_Of_Solar_Irradiance[hour] = HFSI;
};
double WeatherStateClass::getHourlyFractionOfSolarIrradiance(int hour)
{
    return(Hourly_Fraction_Of_Solar_Irradiance[hour]);
};
void WeatherStateClass::setStressedPlantHourlyTemperature(int hour,double SPHT)
{
    Stressed_Plant_Hourly_Temperature[hour] = SPHT;
};
double WeatherStateClass::getStressedPlantHourlyTemperature(int hour)
{
    return(Stressed_Plant_Hourly_Temperature[hour]);
};
void WeatherStateClass::setHourlySolarZenithAngle(int hour,double x)
{
    Hourly_Solar_Zenith_Angle[hour] = x;
};
double WeatherStateClass::getHourlySolarZenithAngle(int hour)
{
    return(Hourly_Solar_Zenith_Angle[hour]);
};
void WeatherStateClass::setHourlyDiffuseSolarIrradiance(int hour,double x)
{
    Hourly_Diffuse_Solar_Irradiance[hour] = x;
};
double WeatherStateClass::getHourlyDiffuseSolarIrradiance(int hour)
{
    return(Hourly_Diffuse_Solar_Irradiance[hour]);
};
void WeatherStateClass::setHourlyDirectSolarIrradiance(int hour,double x)
{
    Hourly_Direct_Solar_Irradiance[hour] = x;
};
double WeatherStateClass::getHourlyDirectSolarIrradiance(int hour)
{
    return(Hourly_Direct_Solar_Irradiance[hour]);
};
void WeatherStateClass::setHourlySolarIrradiance(int hour,double x)
{
    Hourly_Solar_Irradiance[hour] = x;
};
double WeatherStateClass::getHourlySolarIrradiance(int hour)
{
    return(Hourly_Solar_Irradiance[hour]);
};
void WeatherStateClass::setHourlyExtraterrestrialSolarRadiation(int hour,double x)
{
    Hourly_Extraterrestrial_Solar_Radiation[hour] = x;
};
double WeatherStateClass::getHourlyExtraterrestrialSolarRadiation(int hour)
{
    return(Hourly_Extraterrestrial_Solar_Radiation[hour]);
};
void WeatherStateClass::setHourlyCanopySolarInterceptionFraction(int hour,double x)
{
    Hourly_Canopy_Solar_Interception_Fraction[hour] = x;
};
double WeatherStateClass::getHourlyCanopySolarInterceptionFraction(int hour)
{
    return(Hourly_Canopy_Solar_Interception_Fraction[hour]);
};
void WeatherStateClass::setHourlyStandingStubbleSolarInterceptionFraction(int hour,double x)
{
    Hourly_Standing_Stubble_Solar_Interception_Fraction[hour] = x;
};
double WeatherStateClass::getHourlyStandingStubbleSolarInterceptionFraction(int hour)
{
    return(Hourly_Standing_Stubble_Solar_Interception_Fraction[hour]);
};
void WeatherStateClass::setHourlySurfaceResidueSolarInterceptionFraction(int hour,double x)
{
    Hourly_Surface_Residue_Solar_Interception_Fraction[hour] = x;
};
double WeatherStateClass::getHourlySurfaceResidueSolarInterceptionFraction(int hour)
{
    return(Hourly_Surface_Residue_Solar_Interception_Fraction[hour]);
};
void WeatherStateClass::setHourlySunlitLAI(int hour,double x)
{
    Hourly_Sunlit_LAI[hour] = x;
};
double WeatherStateClass::getHourlySunlitLAI(int hour)
{
    return(Hourly_Sunlit_LAI[hour]);
};
void WeatherStateClass::setHourlyShadedLAI(int hour,double x)
{
    Hourly_Shaded_LAI[hour] = x;
};
double WeatherStateClass::getHourlyShadedLAI(int hour)
{
    return(Hourly_Shaded_LAI[hour]);
};
void WeatherStateClass::setHourlySunlitLAISolarInterceptionFraction(int hour,double x)
{
    Hourly_SunlitLAI_Solar_Interception_Fraction[hour] = x;
};
double WeatherStateClass::getHourlySunlitLAISolarInterceptionFraction(int hour)
{
    return(Hourly_SunlitLAI_Solar_Interception_Fraction[hour]);
};
void WeatherStateClass::setHourlyShadedLAISolarInterceptionFraction(int hour,double x)
{
    Hourly_ShadedLAI_Solar_Interception_Fraction[hour] = x;
};
double WeatherStateClass::getHourlyShadedLAISolarInterceptionFraction(int hour)
{
    return(Hourly_ShadedLAI_Solar_Interception_Fraction[hour]);
};
void WeatherStateClass::setDailyExtraterrestrialSolarRadiation(int doy,double ESR)
{
    Daily_Extraterrestrial_Solar_Radiation[doy] = ESR;
};
double WeatherStateClass::getDailyExtraterrestrialSolarRadiation(int doy)
{
    return(Daily_Extraterrestrial_Solar_Radiation[doy]);
};
void WeatherStateClass::setDailyDiffuseSolarIrradiance(int doy,double x)
{
    Daily_Diffuse_Solar_Irradiance[doy] = x;
};
double WeatherStateClass::getDailyDiffuseSolarIrradiance(int doy)
{
    return(Daily_Diffuse_Solar_Irradiance[doy]);
};
void WeatherStateClass::setDailyDirectSolarIrradiance(int doy,double x)
{
    Daily_Direct_Solar_Irradiance[doy] = x;
};
double WeatherStateClass::getDailyDirectSolarIrradiance(int doy)
{
    return(Daily_Diffuse_Solar_Irradiance[doy]);
};
void WeatherStateClass::setDailyCanopySolarInterceptionFraction(int year,int doy,double x)
{
    Daily_Canopy_Solar_Interception_Fraction[year][doy] = x;
};
double WeatherStateClass::getDailyCanopySolarInterceptionFraction(int year,int doy)
{
    return(Daily_Canopy_Solar_Interception_Fraction[year][doy]);
};
void WeatherStateClass::setDailyGreenCanopySolarInterceptionFraction(int year,int doy,double x)
{
    Daily_Green_Canopy_Solar_Interception_Fraction[year][doy] = x;
};
double WeatherStateClass::getDailyGreenCanopySolarInterceptionFraction(int year,int doy)
{
    return(Daily_Green_Canopy_Solar_Interception_Fraction[year][doy]);
};
void WeatherStateClass::setDailyStandingStubbleSolarInterceptionFraction(int year,int doy,double x)
{
    Daily_Standing_Stubble_Solar_Interception_Fraction[year][doy] = x;
};
double WeatherStateClass::getDailyStandingStubbleSolarInterceptionFraction(int year,int doy)
{
    return(Daily_Standing_Stubble_Solar_Interception_Fraction[year][doy]);
};
void WeatherStateClass::setDailySurfaceResidueSolarInterceptionFraction(int year,int doy,double x)
{
    Daily_Surface_Residue_Solar_Interception_Fraction[year][doy] = x;
};
double WeatherStateClass::getDailySurfaceResidueSolarInterceptionFraction(int year,int doy)
{
    return(Daily_Surface_Residue_Solar_Interception_Fraction[year][doy]);
};
void WeatherStateClass::setDailySunlitLAI(int doy,double x)
{
    Daily_Sunlit_LAI[doy] = x;
};
double WeatherStateClass::getDailySunlitLAI(int doy)
{
    return(Daily_Sunlit_LAI[doy]);
};
void WeatherStateClass::setDailyShadedLAI(int doy,double x)
{
    Daily_Shaded_LAI[doy] = x;
};
double WeatherStateClass::getDailyShadedLAI(int doy)
{
    return(Daily_Shaded_LAI[doy]);
};
void WeatherStateClass::setDailySunlitLAISolarInterceptionFraction(int doy,double x)
{
    Daily_SunlitLAI_Solar_Interception_Fraction[doy] = x;
};
double WeatherStateClass::getDailySunlitLAISolarInterceptionFraction(int doy)
{
    return(Daily_SunlitLAI_Solar_Interception_Fraction[doy]);
};
void WeatherStateClass::setDailyShadedLAISolarInterceptionFraction(int doy,double x)
{
    Daily_ShadedLAI_Solar_Interception_Fraction[doy] = x;
};
double WeatherStateClass::getDailyShadedLAISolarInterceptionFraction(int doy)
{
    return(Daily_ShadedLAI_Solar_Interception_Fraction[doy]);
};
void WeatherStateClass::setAnnualAverageTemperature(double AAT)
{
    Annual_Average_Temperature = AAT;
};
double WeatherStateClass::getAnnualAverageTemperature()
{
    return(Annual_Average_Temperature);
};
void WeatherStateClass::setAnnualTemperatureAmplitude(double ATA)
{
    Annual_Temperature_Amplitude = ATA;
};
double WeatherStateClass::getAnnualTemperatureAmplitude()
{
    return(Annual_Temperature_Amplitude);
};
void WeatherStateClass::setAnnualTemperaturePhase(int ATP)
{
    Annual_Temperature_Phase = ATP;
};
int WeatherStateClass::getAnnualTemperaturePhase()
{
    return(Annual_Temperature_Phase);
};
void WeatherStateClass::setPsychrometricConstant(double PC)
{
    Psychrometric_Constant = PC;
};
double WeatherStateClass::getPsychrometricConstant()
{
    return(Psychrometric_Constant);
};
void WeatherStateClass::setSlopeSaturationVaporPressureFunctionOfTemperature(double SSVPTF)
{
    Slope_Saturation_Vapor_Pressure_Function_Of_Temperature = SSVPTF;
};
double WeatherStateClass::getSlopeSaturationVaporPressureFunctionOfTemperature()
{
    return(Slope_Saturation_Vapor_Pressure_Function_Of_Temperature);
};
void WeatherStateClass::setAerodynamicResistance(double AR)
{
    Aerodynamic_Resistance = AR;
};
double WeatherStateClass::getAerodynamicResistance()
{
    return(Aerodynamic_Resistance);
};
void WeatherStateClass::setUnstressedCanopyResistance(double UCR)
{
    Unstressed_Canopy_Resistance = UCR;
};
double WeatherStateClass::getUnstressedCanopyResistance()
{
    return(Unstressed_Canopy_Resistance);
};
void WeatherStateClass::setCumulativeChillHours(double CH)
{
    Cumulative_Chill_Hours = CH;
};
double WeatherStateClass::getCumulativeChillHours()
{
    return(Cumulative_Chill_Hours);
};
void WeatherStateClass::setAccumulateChillHours(bool ACH)
{
    Accumulate_Chill_Hours = ACH;
};
bool WeatherStateClass::getAccumulateChillHours()
{
    return(Accumulate_Chill_Hours);
};













