#ifndef WEATHERSTATECLASS_H
#define WEATHERSTATECLASS_H

class WeatherStateClass
{
    //Storage and calculate hourly meterology for each grid cell
    int num_years;          //Num of years
    int num_days;           //Num of days per year (for array defination)
    int num_hours;          //Num of hours per day (for array defination)

    double **Reference_ET;                                          //(100, 367);
    double **Actual_Crop_Potential_Transpiration;                   //(100, 367);
    double **Potential_Crop_Potential_Transpiration;                //(100, 367);
    double **Actual_Crop_Transpiration;                             //(100, 367);
    double **Day_Time_VPD;                                          //(100, 367);
    double **VPD_Max;                                               //(100, 367);
    double **Daily_Wind_Speed_At_10m;                               //(100, 367);

    double *Hourly_Temperature;                                     //(25);
    double *Hourly_Relative_Humidity;                               //(25);
    double *Stressed_Plant_Hourly_Temperature;                      //(25);
    double *Hourly_Fraction_Of_Solar_Irradiance;                    //(25);
    double *Hourly_Solar_Zenith_Angle;                              //(25);
    double *Hourly_Diffuse_Solar_Irradiance;                        //(25);
    double *Hourly_Direct_Solar_Irradiance;                         //(25);
    double *Hourly_Solar_Irradiance;                                //(25);
    double *Hourly_Extraterrestrial_Solar_Radiation;                //(25);
    double *Hourly_Canopy_Solar_Interception_Fraction;              //(25);
    double *Hourly_Standing_Stubble_Solar_Interception_Fraction;    //(25);
    double *Hourly_Surface_Residue_Solar_Interception_Fraction;     //(25);
    double *Hourly_Sunlit_LAI;                                      //(25);
    double *Hourly_Shaded_LAI;                                      //(25);
    double *Hourly_SunlitLAI_Solar_Interception_Fraction;           //(25);
    double *Hourly_ShadedLAI_Solar_Interception_Fraction;           //(25);

    double **Daily_Green_Canopy_Solar_Interception_Fraction;        //(100, 367);
    double **Daily_Canopy_Solar_Interception_Fraction;              //(100, 367);
    double **Daily_Standing_Stubble_Solar_Interception_Fraction;    //(100, 367);
    double **Daily_Surface_Residue_Solar_Interception_Fraction;     //(100, 367);
    double *Daily_Diffuse_Solar_Irradiance;                        //(367);
    double *Daily_Direct_Solar_Irradiance;                         //(367);
    double *Daily_Sunlit_LAI;                                      //(367);
    double *Daily_Shaded_LAI;                                      //(367);
    double *Daily_SunlitLAI_Solar_Interception_Fraction;           //(367);
    double *Daily_ShadedLAI_Solar_Interception_Fraction;           //(367);

    double *Daily_Extraterrestrial_Solar_Radiation;                //(367);


    double Annual_Average_Temperature;                              // As Double
    double Annual_Temperature_Amplitude;                            // As Double
    int Annual_Temperature_Phase;                                   // As Integer
    double Psychrometric_Constant;                                  // As Double
    double Slope_Saturation_Vapor_Pressure_Function_Of_Temperature; // As Double
    double Aerodynamic_Resistance;                                  // As Double
    double Unstressed_Canopy_Resistance;                            // As Double

    double Cumulative_Chill_Hours;                // As Double
    double Accumulate_Chill_Hours;                // As Boolean

    void initMem();
    void clearMem();

private:
    double HourlyVPDAir(double T,double RH);
    double VP(double T);

public:
    WeatherStateClass(int _nyear,int _nday,int _nhour);
    ~WeatherStateClass();


    void PassStateToNextDay(int CurrentYearCount,int Today,int LastDOYOfPreviousYear);
    double DeclinationOfSun(double JulianDay);
    double relativeSunEarthDistance(double JulianDay);
    double SunsetSunriseHourAngle(double JulianDay,double Lat);
    double ExTerrRadiation(double JulianDay,double Lat);
    double maxSunHours(double JulianDay,double Lat);
    double WOZ(double JulianDay,int HourOfDay,double Longi,double Longi_timezone);
    double SunHourAngle(double HourOfDay);
    double SunAngle(double JulianDay,int HourOfDay,double Lat);
    double Sonnenscheindauer(double JulianDay, double Lat);
    double calcHourlySolarZenithAngle(double doy,int hour,double Latitude);
    double calcHourlyExtraterrestrialRadiation(double Solar_Zenith_Angle,double JulianDay,int hour);
    double getHourlyRadiationFraction(int HourOfDay,double JulianDay,double Latitude);
    double calcSatVP(double T);
    double calcSkyEmissivity(double vapor_pressure,double Tair,double Cloud_Cover);
    double calcHourlyTemperature(int HourOfDay,double Tmax_today,double Tmax_yesterday,
                                   double Tmin_today,double Tmin_tomorrow);
    double calcHourlyHumidity(int HourOfDay,double RHmax_today,double RHmax_tomorrow,
                                double RHmin_today,double RHmin_yesterday);

    void setReferenceCropET(int Year_Count,int doy,double Ref_ET);
    double getReferenceCropET(int Year_Count,int doy);
    void setActualCropPotentialTranspiration(int Year_Count,int doy,double PT);
    double getActualCropPotentialTranspiration(int Year_Count,int doy);
    void setPotentialCropPotentialTranspiration(int Year_Count,int doy,double PPT);
    double getPotentialCropPotentialTranspiration(int Year_Count,int doy);
    void setActualCropTranspiration(int Year_Count,int doy,double AT);
    double getActualCropTranspiration(int Year_Count,int doy);
    void setDayTimeVPD(int Year_Count,int doy,double DTVPD);
    double getDayTimeVPD(int Year_Count,int doy);
    void setVPDMax(int Year_Count,int doy,double DMAX);
    double getVPDMax(int Year_Count,int doy);
    void setDailyWindSpeedAt10m(int Year_Count,int doy,double DWS10);
    double getDailyWindSpeedAt10m(int Year_Count,int doy);
    void setHourlyTemperature(int hour,double HT);
    double getHourlyTemperature(int hour);
    void setHourlyRelativeHumidity(int hour,double HT);
    double getHourlyRelativeHumidity(int hour);
    void setHourlyFractionOfSolarIrradiance(int hour,double HFSI);
    double getHourlyFractionOfSolarIrradiance(int hour);
    void setStressedPlantHourlyTemperature(int hour,double SPHT);
    double getStressedPlantHourlyTemperature(int hour);
    void setHourlySolarZenithAngle(int hour,double x);
    double getHourlySolarZenithAngle(int hour);
    void setHourlyDiffuseSolarIrradiance(int hour,double x);
    double getHourlyDiffuseSolarIrradiance(int hour);
    void setHourlyDirectSolarIrradiance(int hour,double x);
    double getHourlyDirectSolarIrradiance(int hour);
    void setHourlySolarIrradiance(int hour,double x);
    double getHourlySolarIrradiance(int hour);
    void setHourlyExtraterrestrialSolarRadiation(int hour,double x);
    double getHourlyExtraterrestrialSolarRadiation(int hour);
    void setHourlyCanopySolarInterceptionFraction(int hour,double x);
    double getHourlyCanopySolarInterceptionFraction(int hour);
    void setHourlyStandingStubbleSolarInterceptionFraction(int hour,double x);
    double getHourlyStandingStubbleSolarInterceptionFraction(int hour);
    void setHourlySurfaceResidueSolarInterceptionFraction(int hour,double x);
    double getHourlySurfaceResidueSolarInterceptionFraction(int hour);
    void setHourlySunlitLAI(int hour,double x);
    double getHourlySunlitLAI(int hour);
    void setHourlyShadedLAI(int hour,double x);
    double getHourlyShadedLAI(int hour);
    void setHourlySunlitLAISolarInterceptionFraction(int hour,double x);
    double getHourlySunlitLAISolarInterceptionFraction(int hour);
    void setHourlyShadedLAISolarInterceptionFraction(int hour,double x);
    double getHourlyShadedLAISolarInterceptionFraction(int hour);
    void setDailyExtraterrestrialSolarRadiation(int doy,double ESR);
    double getDailyExtraterrestrialSolarRadiation(int doy);
    void setDailyDiffuseSolarIrradiance(int doy,double x);
    double getDailyDiffuseSolarIrradiance(int doy);
    void setDailyDirectSolarIrradiance(int doy,double x);
    double getDailyDirectSolarIrradiance(int doy);
    void setDailyCanopySolarInterceptionFraction(int year,int doy,double x);
    double getDailyCanopySolarInterceptionFraction(int year,int doy);
    void setDailyGreenCanopySolarInterceptionFraction(int year,int doy,double x);
    double getDailyGreenCanopySolarInterceptionFraction(int year,int doy);
    void setDailyStandingStubbleSolarInterceptionFraction(int year,int doy,double x);
    double getDailyStandingStubbleSolarInterceptionFraction(int year,int doy);
    void setDailySurfaceResidueSolarInterceptionFraction(int year,int doy,double x);
    double getDailySurfaceResidueSolarInterceptionFraction(int year,int doy);
    void setDailySunlitLAI(int doy,double x);
    double getDailySunlitLAI(int doy);
    void setDailyShadedLAI(int doy,double x);
    double getDailyShadedLAI(int doy);
    void setDailySunlitLAISolarInterceptionFraction(int doy,double x);
    double getDailySunlitLAISolarInterceptionFraction(int doy);
    void setDailyShadedLAISolarInterceptionFraction(int doy,double x);
    double getDailyShadedLAISolarInterceptionFraction(int doy);
    void setAnnualAverageTemperature(double AAT);
    double getAnnualAverageTemperature();
    void setAnnualTemperatureAmplitude(double ATA);
    double getAnnualTemperatureAmplitude();
    void setAnnualTemperaturePhase(int ATP);
    int getAnnualTemperaturePhase();
    void setPsychrometricConstant(double PC);
    double getPsychrometricConstant();
    void setSlopeSaturationVaporPressureFunctionOfTemperature(double SSVPTF);
    double getSlopeSaturationVaporPressureFunctionOfTemperature();
    void setAerodynamicResistance(double AR);
    double getAerodynamicResistance();
    void setUnstressedCanopyResistance(double UCR);
    double getUnstressedCanopyResistance();
    void setCumulativeChillHours(double CH);
    double getCumulativeChillHours();
    void setAccumulateChillHours(bool ACH);
    bool getAccumulateChillHours();
};

#endif // WEATHERSTATECLASS_H
