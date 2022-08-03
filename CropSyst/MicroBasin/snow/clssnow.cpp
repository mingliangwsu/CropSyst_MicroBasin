﻿#ifndef CROPSYST_WEATHER
#include "clssnow.h"
#include "basin/basincellclass.h"
#include "math.h"
#include "util/pubtools.h"
#include "corn/measure/measures.h"
#include <iostream>
#include "CropSyst/source/organic_matter/OM_residues_profile_abstract.h"
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif
#include <vector>
//______________________________________________________________________________
clsSnow::clsSnow
(SoilStateClass               &SoilStateRef_
#ifdef CROPSYST_VERSION
,const CS::Solar_irradiance_extraterrestrial_hourly &extraterrestrial_solar_irradiance_basin_ //151214RLN
#endif
,const WeatherStateDailyClass &weather_                                          //160224RLN
,const double                 &site_latitude_                                    //160224RLN
,const double                 &site_slope_                                       //160224RLN
,const double                 &site_aspect_                                      //160224RLN
,const CORN::Date_const             &today_
,const long                   &RefGridID_)                                       //140221 RLN
:SoilStateRef                 (SoilStateRef_)
,Weather                      (weather_)
,site_latitude                (site_latitude_)                                   //160224RLN
,site_slope                   (site_slope_)                                      //160224RLN
,site_aspect                  (site_aspect_)                                     //160224RLN
#ifdef CROPSYST_VERSION
,extraterrestrial_solar_irradiance_basin(extraterrestrial_solar_irradiance_basin_)//151214
#endif
,Cumulative_New_Snow_Fall     (0)
,Cumulative_Rain_mm           (0)
,Cumulative_Sublimation_mm    (0)
,Cumulative_Re_Sublimation_mm (0)
,today                        (today_)                                                                   //140221
,RefGridID                    (RefGridID_)
,Density_Snow(82.149)                                                            //160219LML
{
    //0: last hour of yesterday
    Energy_Below_Snow_Surface.resize(25,0);
    Fraction_Cover_Snow.resize(25,0);                 
    Hourly_Energy_Below_Snow_Surface.resize(25,0);    
    Hourly_Energy_in_Snow.resize(25,0);               
    Hourly_Energy_In_Snow_Surface.resize(25,0);       
    Hourly_Ice_In_Snow_Amount.resize(25,0);           
    Hourly_Snow_Below_Surface_T.resize(25,0);         
    Hourly_Snow_Depth.resize(25,0);                   
    Hourly_Snow_Melt_Amount.resize(25,0);             
    Hourly_Snow_Amount.resize(25,0);                  
    Hourly_Rain_mm.resize(25,0);                      
    Hourly_Snow_Melt_Depth.resize(25,0);              
    Hourly_Snow_Surface_T.resize(25,0);               
    Hourly_Water_In_Snow_Amount.resize(25,0);         
    Hourly_Precipitation_Is_Snow.resize(25,false);    
    Hourly_Added_Snow_Depth.resize(25,0);             
    Hourly_Sublimation_mm.resize(25,0);               
    Hourly_Snow_Pack_SWE.resize(25,0);                
    Hourly_W_freeze_thaw_mm.resize(25,0);             
    Hourly_QtotalkJm2.resize(25,0);                   
    QtotalkJm2.resize(25,0);                          
    W_freeze_thaw_mm.resize(25,0);                    
    Hourly_Non_Intercepted_Precipitation_mm.resize(25,0);
}
//______________________________________________________________________________
clsSnow::~clsSnow()
{
#ifdef Destruct_Monitor
    std::cout<<"~clsSnow:"<<std::endl;
#endif
    //delete[] Energy_Below_Snow_Surface;
    //delete[] Energy_in_Snow;
    //delete[] Energy_In_Snow_Surface;
    //delete[] Fraction_Cover_Snow;
    //delete[] Hourly_Energy_Below_Snow_Surface;
    //delete[] Hourly_Energy_in_Snow;
    //delete[] Hourly_Energy_In_Snow_Surface;
    //delete[] Hourly_Ice_In_Snow_Amount;
    //delete[] Hourly_Snow_Below_Surface_T;
    //delete[] Hourly_Snow_Depth;
    //delete[] Hourly_Snow_Amount;
    //delete[] Hourly_Snow_Melt_Amount;
    //delete[] Hourly_Rain_mm;
    //delete[] Hourly_Snow_Melt_Depth;
    //delete[] Hourly_Snow_Surface_T;
    //delete[] Hourly_Water_In_Snow_Amount;
    //delete[] Hourly_Precipitation_Is_Snow;
    //delete[] Hourly_Added_Snow_Depth;
    //delete[] Hourly_Sublimation_mm;
    //delete[] Hourly_Snow_Pack_SWE;
    //delete[] Hourly_W_freeze_thaw_mm;
    //delete[] Hourly_QtotalkJm2;
    //delete[] Hourly_Non_Intercepted_Precipitation_mm;
    //delete[] QtotalkJm2;
    //delete[] W_freeze_thaw_mm;
#ifdef Destruct_Monitor
    std::cout<<"~clsSnow done."<<std::endl;
#endif
}

//______________________________________________________________________________
double clsSnow::SaturationVaporPressure(double T_Celsius)
{
    return 0.6108 * exp((17.27 * T_Celsius) / (T_Celsius + 237.3)); //(kPa)
}
//______________________________________________________________________________
double clsSnow::Arcsin(double X)
{
    return atan(X / sqrt(-X * X + 1.));
}
//______________________________________________________________________________
double clsSnow::calHourlyNonInterceptedPrecipitation(double PrecipitationHourly,
  double PrecipitationDaily)
{
    // New Sub add  FMS 10/15/2013
    double Hourly_Non_Intercepted_Precipitation(0.0);
    if (!CORN::is_approximately<double>(PrecipitationDaily,0.0,1e-12))
        Hourly_Non_Intercepted_Precipitation = 
                Non_Intercepted_Precipitation * (PrecipitationHourly / PrecipitationDaily);
    else Hourly_Non_Intercepted_Precipitation = 0.0;
    return Hourly_Non_Intercepted_Precipitation;
}
//______________________________________________________________________________
void clsSnow::HourlySnowRoutine(
int HourOfDay
//160224 WeatherStateDailyClass &Weather,BasinCellClass &BasinCell
)
{
    //int Nenner(0);                                                               //FMS Mar 11, 2015
    //add sub hourly Snow Routine FMS 11/07/2013 according Snow//s Erin Brooks
    //160218LML const double C_air = 1005;                          // specific heat capacity of air (J/(kg C))
    //160218LML const double C_ice = 2027;                          // specific heat capacity of ice (J/(kg C))
    //160218LML const double C_snow = 2100;                         //specif (heat capacity of snow (J/kg C)
    //FMS Jan 16, 2016 (J/(kg C)) const double C_soil = 2100;                         // specific heat capacity of the soil (J/(kg C)) - fixed in this case...
    //160218LML const double C_water = 4200;                        // specific heat capacity of water (J/(kg C))
    //const double Cloud_Cover_Parameter_B = 0.304
    //const double Cloud_Cover_Parameter_C = 1.506
    //160218LML const double D_ice = 918;                           // density of ice (kg/m3)
    //FMS Jan 15, 2016 const double D_snow = 200;                          //kg/m3 'Calonne et al 2011 (refrozen) was 100 'kg/m3; Mölders et al. Meteorol Atmos Phys 84, 115–135 (2003)
    //Density_Snow = D_snow;                              //FMS Mar 28, 2014
    //const double D_soil = 1250;                         // soil bulk density (kg/m3) - fixed in this case...
    const double D_water = 1000;                        //density of water (kg/m3)
    //const double D_air = 1.29  // density of air  kg/m^3
    const double Emissivity_of_Snow = 0.98;
    //const double Forest_Cover = 0
    //160218LML const double Heat_from_Ground = 0;                  //negligible KJ/m^2/day
    //const double Long_Wave_Absorptivity = 0.95 //of the atmosphere; value from SoilTemperatureClass
    //FMS Jan 27, 2016 by Campbell 1998
    const double Lf = 335000;                           //latent heat of fusion (J/kg)
    const double eq_water_mm_per_KJ = 1000.0 / (D_water * Lf / 1000.0);          //(mm H2O/kJ) energy for freeze or melt
    //160218LML const double Lv = 2500000;                          //latent heat of vaporization (J/kg)
    //160218LML const double Molecular_Mass_Air     = 28.97;                                 //g/mol FMS Jan 27, 2016
    //160218LML const double Molecular_Mass_Water   = 18.0;                                  //g/mol FMS Jan 27, 2016
    //160218LML const double LatentHeatFusion       = 6000.0;                                //J/mol FMS Jan 27, 2016 by Campbell 1998
    //160218LML const double LatentHeatVaporization = 44000.0;                               //J/mol FMS Jan 27, 2016 by Campbell 1998
    //double Lf = LatentHeatFusion / Molecular_Mass_Air * 1000.0;                  //J/kg FMS Jan 27, 2016
    //double Lv = LatentHeatVaporization / Molecular_Mass_Air * 1000.0;            //J/kg FMS Jan 27, 2016
    //const double Ls = 2850000 //latent heat of sublimation (J/kg) - which is indeed equal to Lv + Lf
    const double Minimum_Temp_With_Rain = -1;           //C
    const double Maximum_Temp_With_Snow = 3.0;                                   //0.5;          //C
    //160218LML const double Ndlovus_A_parameter = 0.76;
    //const double Ndlovus_B_parameter = 0.172
    //const double Ndlovus_C_parameter = 2
    const double Pi = 3.14159265358979;
    //160218LML const double R_air = 287.058;                       //specific gas constant for dry air J/(kg·K)
    //160218LML const double Sky_View_Factor_for_Reflect_Rad = 0.986;
    //160218LML const double Snow_Water_Holding_Capacity = 0;       //%
    //const double Snowfall_Catch_Adjustment_By_Wind = 0
    //const double Snow_Emissivity = 0.97
    const double StefBoltz = 5.6704e-8;                                          //(W/(m2 K4))
    //160218LML const double Thermo_Vapor_Constant = 461.52;        //Rw specific gas constant for water vapor J/(kg K)
    //160218LML const double Fluctiation           = 86400;
    //const double UEB_roughness_parameter = 0.005;
    //160218LML const double UEB_roughness_parameter[2] = {4.54944091943632e-02,
    //160218LML                                            4.64668738001529e-04};
    //160218LML const double VonKarmon = 0.41;                      // von Karman constant
    //OJO
    //const double Damping_Depth_Soil = 0.4;              // m
    //160218LMLconst double Bulk_Density_soil =
    //160218LML        BasinCell.pSoilProfile->get_bulk_density_kg_m3(1);                   //(kg/m3) 150520 FMS May 1, 2015
    //160218LML const double Damping_Thickness_soil = 0.3;          //m
    //160218LML const double Damping_Thickness_snow = 0.05;         //m
    //160218LML const double Skin_Thickness = 0.003; //0.02;                 //m
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_SWE;
    #endif
    //150520 Avg_Daily_Snow_Surface_T = 0.0;         //LML 140822
    int doy = today.get_DOY();                                                   //140221
    //160218LML const double Cp = 29.3;                                                      //Jmol-1 C-1 specific heat of air at constant pressure ' FMS Jan 27, 2016
    //160218LML Organic_matter_residues_profile_abstract *organic_matter_residues_profile_kg_m2
    //160218LML     = BasinCell.LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;
    //160218LMLdouble Fraction_SOM     = organic_matter_residues_profile_kg_m2->get_percent_organic_matter(1) / 100.0;
    //160218LMLdouble Water_Content    = SoilStateRef.get_liquid_water_content_volumetric(1);
    //160218LMLdouble Ice_Content      = SoilStateRef.get_ice_content_volumetric(1);
    //160218LML double C_Soil = calc_SoilHeatCapacity(Bulk_Density_soil/1000.,Fraction_SOM,Water_Content,Ice_Content) / Bulk_Density_soil;   //J/kg/C FMS Jan 22, 2016
    //160224RLN double Latitude = BasinCell.getLatitude();


    //double Longitude = BasinCell.getLongitude();
    //Longitude_Correction = (120 - Longitude) / 15.0;    //OJO  Consultar de donde viene el 120 y el 15...
                                                        //LML 14/05/09 West longitude is negative
    double Longitude_Correction = 0.0;                     //FMS 141009
    enum Surface {VEG,SNOW};
    //std::clog<<"SET CONSTANT SLOP & ASPECT FOR DEBUGGING!!!";
    //160224RLN double Slope = BasinCell.getSlop(); // %//3.8;//
    //160224RLN double Aspect = BasinCell.getAspect(); // Degree from North//26.58;//

    //std::clog<<"Slop & Aspect has been set constant for debugging!\n";

    //160218LML double Soil_Water_Potential = SoilStateRef.hydrology->get_water_potential(1);//BasinCell.get_soil()->hydrology->get_water_potential(1);           //J/kg FMS Jan 27, 2016  160211LML check unit!!!
    //std::clog<<"NEED CHECK Soil_Water_Potential UNITS!!!"<<std::endl;
    /*160216FMS
    double Roughness[2] = {0.6,0.0};
    double Height_of_Zero_Plane_Displacement[2] = {0.64 * Roughness[VEG],
                                                   0.64 * Roughness[SNOW]};
    double Momentum_Roughness_Parameter[2] = {0.13 * Roughness[VEG],
                                              0.001};
    double Heat_And_Vapor_Roughness_Parameter[2] = {0.2 * Momentum_Roughness_Parameter[VEG],
                                                    0.2 * Momentum_Roughness_Parameter[SNOW]};
    double z_equipment = Weather.getScreeningHeight(); //assuming wind speed and temperature are measured at the same level
    */
    //Simulation_Year = OverallControl.YearCount
    //141222 RLN unused     Current_Year = today.get_year();

    double Daily_Precipitation_mm           = Weather.daily_provider.precipitation_actual.get_mm();                   //141222
    double Solar_Radiation                  = Weather.daily_provider.solar_radiation.get_MJ_m2();              //141222
    double Extraterrestrial_Solar_Radiation = Weather.daily_provider.ET_solar_irradiance.get_MJ_per_m2_day(); //150724  ET_solar_irradiance.get_extraterrestrial_irradiance_today();  //141222RLN
    //160218LML double Atmospheric_Pressure             = Weather.daily_provider.atmospheric_pressure.get_kPa();           //FMS Jan 27, 2016

    int LastHour  = (HourOfDay == 0) ? 23 : (HourOfDay - 1);                     //160211LML
    if (HourOfDay == 0) output_daily_snowfall_on_ground_SWE_mm = 0;              //150909LML
    double D_Snow = 82.149;                               //(kg/(m3 snow) or (mm water / (m snow)) FMS Jan 15, 2016

    //160211LML for (int HourOfDay = 0; HourOfDay <= 23; HourOfDay++) {  //FMS May 14, 2014 1-24 ->0-23
        //std::clog<<"Hour:"<<HourOfDay<<std::endl;
        #ifdef CHECK_MASS_BALANCE
        bal_SWE.ClearPoolAndFluxes();
        bal_SWE.SetInitPool(Previous_Hour_Snow_Pack_SWE_m * 1000.0);
        #endif
        //150921LML if (CORN::is_approximately(Previous_Hour_Snow_Pack_SWE_m,0.0,1e-12))
        //150921LML     U_internal_energy = 0;                                               //150910LML NEED talk with Fidel!!!
        //160218LML double prehour_snow_T(-9999.0);
        //160218LML double prehour_ice_in_snow(-9999.0);
        //160218LML double prehour_water_in_snow(-9999.0);
        //160218LML double prehour_energy_in_snowsurface(-9999.0);
        //160218LML if (HourOfDay == 0) {
            //160218LML prehour_snow_T                  = Hourly_Snow_Surface_T[23];         //140820LML
            //160218LML prehour_ice_in_snow             = Hourly_Ice_In_Snow_Amount[23];     //140820LML
            //160218LML prehour_water_in_snow           = Hourly_Water_In_Snow_Amount[23];   //140820LML
            //160218LML prehour_energy_in_snowsurface   = Hourly_Energy_In_Snow_Surface[23]; //140820LML
            //160128 FMS if (doy == annual_temperature_phase)/*151214RLN doy already set above  today.get_DOY()*/
            //160128 FMS     U_internal_energy = 0;                                           //150715FMS
               //this variable is reset each year when the temperature start to increse
        //160218LML } else {
            //160218LML prehour_snow_T                  = Hourly_Snow_Surface_T[HourOfDay-1];         //140820LML
            //160218LML prehour_ice_in_snow             = Hourly_Ice_In_Snow_Amount[HourOfDay-1];     //140820LML
            //160218LML prehour_water_in_snow           = Hourly_Water_In_Snow_Amount[HourOfDay-1];   //140820LML
            //160218LML prehour_energy_in_snowsurface   = Hourly_Energy_In_Snow_Surface[HourOfDay-1]; //140820LML
        //160218LML }
        double Hourly_Precipitation_mm = Weather.getHourlyPrecipitation(HourOfDay);       //131009FMS
        double Hourly_NonIntercepted_Precipitation = //mm
                calHourlyNonInterceptedPrecipitation
                  (Hourly_Precipitation_mm, Daily_Precipitation_mm);             //131015FMS
        Hourly_Non_Intercepted_Precipitation_mm[HourOfDay] = 
                Hourly_NonIntercepted_Precipitation;                             //140926LML
        double Hourly_Intercepted = Hourly_Precipitation_mm - Hourly_NonIntercepted_Precipitation; //mm
        double Hourly_Temp = Weather.getHourlyTemperature(HourOfDay);                              //C
        //160218LML double Hourly_Relative_Humidity = Weather.getHourlyRelativeHumidity(HourOfDay);            //%
        //160218LML double Hourly_Wind = Weather.getHourlyWind(HourOfDay);                                     // m/s
        //160218LML double Hourly_Soil_Temp = SoilStateRef.Soil_Temperature[HourOfDay][1];   //160211LML
        //160218LML double ConductivityAtm =  BasinCell.pSoil->pSoilTemperature->Boundary_Layer_Heat_Conductance / Cp; //mol/m2/s FMS Jan 27, 2016
        double Sublimation_rate = 0;
        //assert(false);  //160216LML Talk with Fidel!!!
        double W_freeze_thaw = 0;
        double Qtotal = 0;
        //160218LML std::clog<<"NEED CHECK ConductivityAtm UNITS!!!"<<std::endl;
        #ifndef CROPSYST_VERSION
        double Hourly_Fraction_Solar_Irradiance = 
                Weather.getHourlyRadiationFraction(HourOfDay,doy,site_latitude); //160224
        double Hourly_Rs = Hourly_Fraction_Solar_Irradiance 
                           * Solar_Radiation * 1000000.0 / 3600.0;              //solar radiation (W/m2) LML 14/05/09 fixed hourofday
        Weather.setHourlyFractionOfSolarIrradiance(HourOfDay,Hourly_Fraction_Solar_Irradiance);
        double Hourly_Extraterrestrial_Radiation = 
                Weather.getHourlyExtraterrestrialSolarRadiation(HourOfDay);     //(W/m2)
        #endif
        //***************************************
        //Modified Weather Parameters
        //Extraterrestrial_Solar_Radiation = Solar_Radiation / 0.75;
        //std::clog<<"set Extraterrestrial_Solar_Radiation = Solar_Radiation / 0.75!!!"<<std::endl;
        double Cloud_Cover = std::min<double>(1., 
                             std::max<double>(0,(1 - Solar_Radiation / Extraterrestrial_Solar_Radiation)));
        double Hourly_Rain(0.0);
        if (Hourly_Temp < Minimum_Temp_With_Rain) Hourly_Rain = 0;
        else if ((Hourly_Temp >= Minimum_Temp_With_Rain) && 
                 (Hourly_Temp <  Maximum_Temp_With_Snow))
            Hourly_Rain = Hourly_NonIntercepted_Precipitation 
                          * (Hourly_Temp - Minimum_Temp_With_Rain) 
                          / (Maximum_Temp_With_Snow - Minimum_Temp_With_Rain);
        else Hourly_Rain = Hourly_NonIntercepted_Precipitation;
        Hourly_Snow_Amount[HourOfDay] = Hourly_NonIntercepted_Precipitation - Hourly_Rain;
        output_daily_snowfall_on_ground_SWE_mm += Hourly_Snow_Amount[HourOfDay];
        //150527 #if CHECK_MASS_BALANCE
        //150527 bal_SWE.AddFluxIn(Hourly_Snow_Amount[HourOfDay]);
        //150527 #endif
        //**************************************
        //Vapor Density and Roughness Calcs
        //OJO XXXXXXXXXX estimates before Bristow_Kustas_LongWave_Atmospheric_Emissivity,  
        //Hourly_Snow_Surface_T(HourOfDay - 1), Snow_Albedo, U_Internal_Energy

        bool RunningSnow = false;                                                //FMS Feb 12, 2016
        if (Hourly_Snow_Amount[HourOfDay] > 0 || Fraction_Cover_Snow[LastHour] > 0) {
            RunningSnow = true;
        } else {
            RunningSnow = false;
            Hourly_Snow_Melt_Amount[HourOfDay]      = 0;
            Hourly_Ice_In_Snow_Amount[LastHour]     = 0;
            Hourly_Snow_Surface_T[HourOfDay]        = 0;
            Hourly_Energy_in_Snow[HourOfDay]        = 0;
            Hourly_Snow_Below_Surface_T[HourOfDay]  = 0;
            Fraction_Cover_Snow[HourOfDay]          = 0;
            U_internal_energy = 0;
        }
        /*160216LML
        if (Hourly_Wind < 0.1) Hourly_Wind = 0.1;
        double rh_Wind_Roughness(0.0);
        double UEB_rh(0.0);
        Surface surface(VEG);
        if (Previous_Hour_Snow_Pack_SWE_m > 0)
            surface = SNOW;
        else
            surface = VEG;

        rh_Wind_Roughness =
                (log((z_equipment
                      - Height_of_Zero_Plane_Displacement[surface]
                      + Momentum_Roughness_Parameter[surface])
                     / Momentum_Roughness_Parameter[surface])
                 *
                 log((z_equipment
                      - Height_of_Zero_Plane_Displacement[surface]
                      + Heat_And_Vapor_Roughness_Parameter[surface])
                     / (Heat_And_Vapor_Roughness_Parameter[surface])))
                / ((VonKarmon * VonKarmon) * Hourly_Wind);
        UEB_rh = 1.0
                / ((VonKarmon * VonKarmon)
                   * Hourly_Wind
                   / pow((log(z_equipment / UEB_roughness_parameter[surface])),2.0)
                   );
        if (Hourly_Relative_Humidity < 0.01) Hourly_Relative_Humidity = 0.01;   // FMS avoid zero
        double Act_Sat_Vap_Press = (Hourly_Relative_Humidity / 100.0) 
                                   * SaturationVaporPressure(Hourly_Temp);      //(kPa)
        double Dew_Point_T = (log(Act_Sat_Vap_Press) * 237.3 + 116.9) 
                              / (16.78 - log(Act_Sat_Vap_Press));               //C  OJO is different...to result//s Erin
        //double Sat_Vap_Density = SaturationVaporPressure(Hourly_Temp) 
        //                         / (273.16 + Hourly_Temp) 
        //                         / (Thermo_Vapor_Constant / 1000.0); //kg/m3
        double Air_Act_Vap_Density = exp((16.78 * Dew_Point_T - 116.9) 
                                         / (Dew_Point_T + 237.3)) 
                                     / (273.16 + Dew_Point_T) 
                                     / (Thermo_Vapor_Constant / 1000.0);
        //FMS May 14, 2014 new lines for change 24 to 0 hours
        double Act_Vap_Density_Over_Water = exp((16.78 * prehour_snow_T - 116.9) 
                                                / (prehour_snow_T + 237.3))
                                            / (273.15 + prehour_snow_T)
                                            / (Thermo_Vapor_Constant / 1000.0);
        double Act_Vap_Density_Over_Ice = Act_Vap_Density_Over_Water 
                                          * exp(0.018 * Lf * prehour_snow_T
                                                / (8.3143 * pow((273.0 + prehour_snow_T),2.0)));
        */
        //**************************************
        //Solar Radiation Calcs
    if (RunningSnow) {//160218LML should move some calculations into start_day().
        double Hourly_Rs =
                        #ifdef CROPSYST_VERSION
                        //160218LML extraterrestrial_solar_irradiance_basin.get_Watt_per_m2_hour(today.get_DOY(),(CORN::Hour)HourOfDay);
                        Weather.getHourlySolarIrradiance(HourOfDay) * 1.e6 / 3600.; //(W/m2) 160218LML
                        #else
                        Hourly_Extraterrestrial_Radiation * 0.75;
                        #endif
        double Sloping_Measured_Rs(0.0);
        //std::clog<<"Hour:"<<HourOfDay<<"\tHourly_Rs:"<<Hourly_Rs<<std::endl;
        if (Hourly_Rs > 1e-8) {                                                  //160218LML
            double Time_Adjustment_Hour = (279.575 + 0.986 * doy) * (Pi / 180.0);
            double Time_ET_Hour =
                (-104.7 * sin(Time_Adjustment_Hour) 
                 + 596.2 * sin(2.0 * Time_Adjustment_Hour) 
                 + 4.3 * sin(3.0 * Time_Adjustment_Hour) 
                 - 12.7 * sin(4.0 * Time_Adjustment_Hour) 
                 - 429.3 * cos(Time_Adjustment_Hour) 
                 - 2 * cos(2.0 * Time_Adjustment_Hour) 
                 + 19.3 * cos(3.0 * Time_Adjustment_Hour)
                ) / 3600.0;

            double  R_Sun_Solar_Time_Hours = -Longitude_Correction + HourOfDay + Time_ET_Hour; //141222RLN
            if(R_Sun_Solar_Time_Hours > 24) R_Sun_Solar_Time_Hours -= 24;            //141222RLN
        /*141222RLN extremely redundent (replaced with above
        if(-Longitude_Correction + HourOfDay + Time_ET_Hour > 24){
            R_Sun_Solar_Time_Hours = -Longitude_Correction + HourOfDay + Time_ET_Hour - 24;
        }
        else R_Sun_Solar_Time_Hours = -Longitude_Correction + HourOfDay + Time_ET_Hour;
        */
            double  Time_to_Solar_Noon = 12. + Longitude_Correction - Time_ET_Hour;
            double  Solar_Declination_Delta =
                0.4102 * sin(2.0 * Pi / 365.0 * (doy - 80.));// rad
            double  Elev_or_Altitude_Angle = Arcsin(sin(site_latitude * (Pi / 180.0))  //160224RLN
                                                * sin(Solar_Declination_Delta) 
                                                + cos(site_latitude * (Pi / 180.0))    //160224RLN
                                                  * cos(Solar_Declination_Delta) 
                                                  * cos(Pi / 12.0 * (HourOfDay - Time_to_Solar_Noon))); //Rad
            //double  Half_Day_Length = acos(-tan(Solar_Declination_Delta) * tan(site_latitude * Pi / 180.0)); //rad
            double  Zenith_from_due_South = Weather.CalculateSolarZenithAngle
                (doy, HourOfDay, site_latitude) * Pi / 180.0; // rad             //160224RLN
            double Zenith_from_due_North = Pi - Zenith_from_due_South;
            if (HourOfDay > Time_to_Solar_Noon)
                Zenith_from_due_North = Pi + Zenith_from_due_South;
            double Incidence_Angle = std::max<double>
                (0.0
                ,Arcsin(sin(atan(site_slope / 100.0))                            //160224RLN
                 * cos(Elev_or_Altitude_Angle)
                 * cos(Zenith_from_due_North - (site_aspect * Pi / 180.0))       //160224RLN
                 + cos(atan(site_slope / 100.0)) * sin(Elev_or_Altitude_Angle))); //rad //160224RLN
        //double Flat_Surface_Clear_Sky_Radiation =
        //      #ifdef CROPSYST_VERSION
        //      extraterrestrial_solar_irradiance_basin.get_Watt_per_m2_hour((CORN::Hour)HourOfDay)
        //      #else
        //      Hourly_Extraterrestrial_Radiation
        //      #endif
        //      * 0.75; // W/m2
            Sloping_Measured_Rs = Hourly_Rs * std::max<double>(0.0,
                                                                  sin(Incidence_Angle) / sin(Elev_or_Altitude_Angle)
                                                                  );
        }
        if(Hourly_Snow_Amount[HourOfDay] > 0 && 
                CORN::is_approximately<double>(Previous_Hour_Snow_Pack_SWE_m,0.0))
            Age_Of_Snow = 1.0 / 24.0; // differ how Erin did  1 / 24
        else Age_Of_Snow += 1.0 / 24.0;
        D_Snow = 7.4199 * Age_Of_Snow + 82.149;                               //(kg/(m3 snow) or (mm water / (m snow)) FMS Jan 15, 2016
        double Snow_Albedo(0.2);
        if(!CORN::is_approximately<double>(Previous_Hour_Snow_Pack_SWE_m,0.0,1e-12))
            Snow_Albedo = std::min<double>(0.95, 0.7384 * pow(Age_Of_Snow, -0.1908156));
        //R.Sun Calculations
        //Link_Turbidity_Factor=$AN$20*(1-COS(B29/365*2*PI()-$AN$19))+$AN$21

        /*160216LML
        double Td(0.1);
        if (!CORN::is_approximately<double>(Cloud_Cover,1.0,1e-12))
            Td = Ndlovus_A_parameter
                * (1.0 - Cloud_Cover) 
                * (1.0 - exp(-0.6 
                             * Cloud_Cover 
                             / ((Ndlovus_A_parameter - 0.4) * (1.0 - Cloud_Cover))
                             )
                   );
        double Tt = Ndlovus_A_parameter * (1.0 - Cloud_Cover);
        //double C = std::min<double>(1.0, std::max<double>(0, 2.4 - 4.0 * Tt));
        double Coef_dh = Td / 0.1;
        double Coef_bh = std::max<double>(0, (Tt - Td) / (Ndlovus_A_parameter));
        double Rs_diff = Flat_Surface_Clear_Sky_Radiation * Coef_dh * 0.1;      // W/m2
        double Total_Sloping_Clear_Sky = Flat_Surface_Clear_Sky_Radiation 
                                         * std::max<double>(0.0, 
                                                            sin(Incidence_Angle) / sin(Elev_or_Altitude_Angle)
                                                            ); // W/m2
        double Rs_Beam = Total_Sloping_Clear_Sky * Coef_bh; //W/m2
        double Rs_Refl = Flat_Surface_Clear_Sky_Radiation 
                         * (1.0 - Cloud_Cover) 
                         * (1.0 - Sky_View_Factor_for_Reflect_Rad) 
                         * Snow_Albedo; // W/m2
        double Rs_Tot = Rs_diff + Rs_Beam + Rs_Refl; //W/m2
        */

        //**************************************
        //Atmospheric Emissivity Calculations for Longwave Radiation
        double Unsworth_Montieth_LongWave_Atm_Emissivity = 
                                                    ((0.72 + 0.005 * Hourly_Temp) 
                                                    * (1.0 - 0.84 * Cloud_Cover) 
                                                    + 0.84 * Cloud_Cover
                                                    );
        //if (Hourly_Snow_Amount[HourOfDay] > 0 && CORN::is_approximately<double>(Hourly_Rain,0.0)) 
        //Age_Of_Snow = 1.0 / 24.0; // differ how Erin did  1 / 24
        //else Age_Of_Snow += 1.0 / 24.0;
        //if (CORN::is_approximately<double>(Previous_Hour_Snow_Pack_SWE_m,0)) Snow_Albedo = 0.2;
        //else Snow_Albedo = std::min<double>(0.95, 0.7384 * pow(Age_Of_Snow, -0.1908156));
        //    D_air = Atmospheric_Pressure * 1000 / (R_air * (Hourly_Air_Temp(HourOfDay) + 273.13))
        //160218LML double D_air = Atmospheric_Pressure * 1000.0 / (R_air * (Hourly_Temp + 273.13));
        double Measured_Qsolar = ((1.0 - Snow_Albedo) * (Sloping_Measured_Rs * 3600.0 * 1.0)) / 1000.0; // kJ/m2
        double Qlong = CalcLongWaveHeat(StefBoltz, Unsworth_Montieth_LongWave_Atm_Emissivity, Hourly_Temp, Emissivity_of_Snow, Hourly_Snow_Surface_T[LastHour]); //kJ/m2 FMS Feb 13, 2016
        /*160216LML
        double temp_emisivity = Emissivity_of_Snow;
        double temp_hour_snow = Hourly_Snow_Amount[HourOfDay];                   //LML 150527
        if (Previous_Hour_Snow_Pack_SWE_m * 1000.0  <= 1e-8) {
            temp_emisivity                  = 0.0;
            prehour_snow_T                  = 0.0;
            temp_hour_snow                  = 0.0;
        }                                                                        //FMS Mar 11, 2015 added
        double Qlong = (StefBoltz * 3600.0 * 1.0) / 1000.0
                        * (Unsworth_Montieth_LongWave_Atm_Emissivity * pow((Hourly_Temp + 273),4)
                           - temp_emisivity * pow((prehour_snow_T + 273), 4)
                          ); // kJ/m2
        double Qconv = (C_air / 1000.0)
                        * D_air
                        * (Hourly_Temp - prehour_snow_T)
                        / (rh_Wind_Roughness / 3600.0); // kJ/m2
        double Act_Vap_Density(Act_Vap_Density_Over_Water);
        //160128FMS if (U_internal_energy <= 0)
        //160128FMS     Act_Vap_Density = Act_Vap_Density_Over_Ice;
        //160128FMS double Qcond = ((Lf + Lv) / 1000.0)
        //160128FMS                * (Air_Act_Vap_Density - Act_Vap_Density)
        //160128FMS                / (rh_Wind_Roughness / 3600.0); // kJ/m2
        double Qprecip = (C_water / 1000.0 
                          * (Hourly_Rain / 1000.0) 
                          * D_water 
                          * (std::max<double>(0, Hourly_Temp) - prehour_snow_T)
                          )
                          + (C_snow / 1000.0 
                             * D_water 
                             * (temp_hour_snow / 1000.0)
                             * (std::min<double>(0, Hourly_Temp) - prehour_snow_T)
                         ); // kJ/m2
        double Qcond = 0;
        if (Fraction_Cover_Snow[LastHour] > 0) {//FMS Jan 26, 2016
            if (U_internal_energy <= 0)
                Qcond = calc_LatentHeat(LatentHeatFusion, ConductivityAtm, SaturationVaporPressure(Hourly_Snow_Surface_T[LastHour]),
                                    Act_Sat_Vap_Press, Atmospheric_Pressure);    //FMS Jan 26, 2016
            else
                Qcond = calc_LatentHeat(LatentHeatVaporization, ConductivityAtm, SaturationVaporPressure(Hourly_Snow_Surface_T[LastHour]), Act_Sat_Vap_Press, Atmospheric_Pressure);    //FMS Jan 26, 2016
        } else {
            Qcond = -m_to_mm(SoilStateRef.Hourly_Soil_Water_Evaporation_m) * Lv / 1000.;  //kJ/m2 FMS Jan 27, 2016 same of soil Temperature ,negative because is already evaporated
            double Relative_Humedity_Soil = calc_RelativeHumiditySoil(Soil_Water_Potential, Hourly_Soil_Temp, Molecular_Mass_Water, R_air); //FMS Jan 27, 2016
            Qcond += calc_LatentHeatSoil(LatentHeatVaporization, Molecular_Mass_Air, Relative_Humedity_Soil, Hourly_Soil_Temp, Hourly_Temp);  //kJ/m2 FMS Jan 26, 2016
        } //FMS Jan 26, 2016

        double Qground = Heat_from_Ground / 24.0; //kJ/m2
        */
        double Qconv    = 0.;
        double Qcond    = 0.;
        double Qprecip  = 0.;
        double Qground  = 0.;
        Qtotal = Measured_Qsolar + Qlong + Qconv + Qcond + Qprecip + Qground; // kJ/m2
        //std::clog   <<"\tQtotal:"<<Qtotal
        //            <<"\tMeasured_Qsolar:"<<Measured_Qsolar
        //            <<"\tQlong:"<<Qlong
        //            <<"\tU_internal_energy:"<<U_internal_energy
        //            <<std::endl;
                 //<<" Qconv:"<<Qconv<<" Qcond:"<<Qcond<<" Q precip:"<<Qprecip<<" Qground:"<<Qground<<std::endl;
        //if (Today = 296 Then Stop
        //**************************************
        //Incoming Energy Fluxes

        /*160216LML
        double Sublimation_rate(0.0);
        if (Previous_Hour_Snow_Pack_SWE_m * 1000.0 + Hourly_Snow_Amount[HourOfDay] > 0)
            Sublimation_rate = 1000.0 * Qcond / (((Lf + Lv) / 1000.0) * D_water); // mm negative is resublimation
        //Mass is added to the snow pack (condensation) when E (sublimation) is greater than 
        //zero and mass is lost from the snow pack (evaporation) when E is less than zero is desublimation
        Sublimation_rate = std::min<double>(Sublimation_rate, 
                                            (Previous_Hour_Snow_Pack_SWE_m * 1000.0)
                                            );
        //Freezing water in snow (mm/h); energy in snow (J/(h m2)), 
        //energy flux (J/(s m2)),3600 s/h, water density (kg/m3), Lv (J/kg), 1000 (mm/m)
        */
        double Remain_Energy(0);                                                 //FMS Feb 12, 2016
        double W_freeze = -eq_water_mm_per_KJ * Qtotal; //
        W_freeze = std::max<double>(0, W_freeze);                                //no negative amount of freezing water
        double spool_1(0),spool_2(0);
        DistributeExcessEnergyFreezeOrThaw(W_freeze, Remain_Energy, Hourly_Rain, spool_1, spool_2, true);    //FMS Feb 13, 2016
        double W_thaw = eq_water_mm_per_KJ * (U_internal_energy + Qtotal);
        W_thaw = std::max<double>(0, W_thaw);
        double sublim = Sublimation_rate < 0 ? Sublimation_rate : 0;
        DistributeExcessEnergyFreezeOrThaw(W_thaw, Remain_Energy, Hourly_Ice_In_Snow_Amount[LastHour], Hourly_Snow_Amount[HourOfDay], sublim, false);    //FMS Feb 13, 2016
        W_freeze_thaw = W_freeze - W_thaw;

        //160223LML_FMS if (Hourly_Snow_Amount[HourOfDay] > 0 || Fraction_Cover_Snow[LastHour] > 0) //FMS Jan 28, 2016
            U_internal_energy += Qtotal + (W_freeze / eq_water_mm_per_KJ) - (W_thaw / eq_water_mm_per_KJ); //kJ/m2 160218LML talk with Fidel!!!
        //160223LML_FMS else //FMS Jan 28, 2016
        //160223LML_FMS     U_internal_energy  = Qtotal + (W_freeze / eq_water_mm_per_KJ) - (W_thaw / eq_water_mm_per_KJ); //kJ/m2 FMS Jan 28, 2016; 160218LML talk with Fidel!!!
        //std::clog<<"doy:"<<doy
        //         <<" U_internal_energy:"<<U_internal_energy
        //         <<" Qtotal:"<<Qtotal
        //         <<" W_freeze_thaw:"<<W_freeze_thaw
        //         <<" W_thaw:"<<W_thaw
        //         <<" W_freeze:"<<W_freeze
        //         <<" Fraction_Cover_Snow[last_hour]:"<<Fraction_Cover_Snow[LastHour]
        //         <<std::endl;
        /*160216LML
        //Hourly_Energy_in_Snow[HourOfDay] = U_internal_energy * 1000; //J/m2
        if (U_internal_energy > 0.0001) {
            Hourly_Ice_In_Snow_Amount[HourOfDay] = 0;
        } else {
            Hourly_Ice_In_Snow_Amount[HourOfDay] = 
                    prehour_ice_in_snow 
                    + Hourly_Snow_Amount[HourOfDay] 
                    + W_freeze_thaw 
                    - Sublimation_rate;    //LML 14/05/02
            Hourly_Ice_In_Snow_Amount[HourOfDay] = 
                    std::max<double>(0, Hourly_Ice_In_Snow_Amount[HourOfDay]);
        }
        if (fabs(U_internal_energy) < 0.0001) {
            double Potential_Water_Holding_In_Snow =
                    ((Snow_Water_Holding_Capacity / 100.0) 
                     / (1.0 - Snow_Water_Holding_Capacity / 100.0)) 
                    * Hourly_Ice_In_Snow_Amount[HourOfDay];
            Hourly_Water_In_Snow_Amount[HourOfDay] =
                    std::min<double>(Potential_Water_Holding_In_Snow,
                        prehour_water_in_snow + Hourly_Rain - W_freeze_thaw); // mm
            Hourly_Water_In_Snow_Amlount[HourOfDay] =
                    std::max<doube>(0, Hourly_Water_In_Snow_Amount[HourOfDay]);
        } else {
            Hourly_Water_In_Snow_Amount[HourOfDay] = 0;
        }
        */
        Hourly_Ice_In_Snow_Amount[HourOfDay] = Hourly_Ice_In_Snow_Amount[LastHour] + Hourly_Snow_Amount[HourOfDay] + W_freeze_thaw;
        if (Hourly_Ice_In_Snow_Amount[HourOfDay] < 0)
            Hourly_Ice_In_Snow_Amount[HourOfDay] = 0;
        Current_Snow_Pack_SWE_mm = Hourly_Ice_In_Snow_Amount[HourOfDay]; // mm
        //std::clog<<"HourOfDay:"<<HourOfDay<<"\tSWE:"<<Current_Snow_Pack_SWE_mm<<std::endl;
        //if (CORN::is_approximately<double>(Hourly_Snow_Pack_SWE_mm,0.0,1e-12)
        //        && CORN::is_approximately<double>(Previous_Hour_Snow_Pack_SWE_m * 1000.0,0.0,1e-12)
        //        && CORN::is_approximately<double>(Hourly_Snow_Amount[HourOfDay],0.0,1e-12)
        //        && CORN::is_approximately<double>(W_freeze_thaw,0.0,1e-12)) {
        /*
        if (m_to_mm(Previous_Hour_Snow_Pack_SWE_m) <= Hourly_Snow_Pack_SWE_mm) {
            Hourly_Snow_Melt_Amount[HourOfDay] = 0; //mm
        } else {
            //150527 #if CHECK_MASS_BALANCE
            //150527 bal_SWE.AddFluxIn(Hourly_Rain);
            //150527 #endif
            Hourly_Snow_Melt_Amount[HourOfDay] = m_to_mm(Previous_Hour_Snow_Pack_SWE_m) - Hourly_Snow_Pack_SWE_mm; //mm
            //Hourly_Rain = 0;
        }*/
        Hourly_Snow_Melt_Amount[HourOfDay] = W_thaw;    //mm
        Hourly_Snow_Surface_T[HourOfDay] = 0;

        /*160211LML
        if (Hourly_Snow_Melt_Amount[HourOfDay] < 0) {
            Hourly_Snow_Pack_SWE_mm -= Hourly_Snow_Melt_Amount[HourOfDay];
            Hourly_Ice_In_Snow_Amount[HourOfDay] -= Hourly_Snow_Melt_Amount[HourOfDay];
        }
        Hourly_Snow_Melt_Amount[HourOfDay] = 
                std::max<double>(0, Hourly_Snow_Melt_Amount[HourOfDay]);
        //    Hourly_Snow_Surface_T(HourOfDay) = Energy_In_Snow_Surface(HourOfDay) / (D_ice * C_ice * (z_snow_surface / 1000))
        //kJ/m^2
        if (fabs(U_internal_energy) < 0.0001) {
            Hourly_Energy_In_Snow_Surface[HourOfDay] = 0;
        } else {
            if (Hourly_Snow_Pack_SWE_mm > 0) {  //150527 need talk with Fidel!!!
                double Fraction_Energy_In_Snow_Surface = 
                        std::max<double>(Skin_Thickness - Hourly_Snow_Pack_SWE_mm / 1000.0, 0) 
                        / Damping_Thickness_soil
                        + std::min<double>(Hourly_Snow_Pack_SWE_mm / 1000.0, Skin_Thickness) 
                        / Damping_Thickness_snow;
                Hourly_Energy_In_Snow_Surface[HourOfDay] = 
                        Fraction_Energy_In_Snow_Surface 
                        * (Qtotal + W_freeze_thaw * (Lf / 1000.0) * D_water / 1000.0)   //KJ/m2
                        + prehour_energy_in_snowsurface;
                if (Hourly_Snow_Pack_SWE_mm > 0.0)
                  Hourly_Energy_In_Snow_Surface[HourOfDay] =
                        std::min<double>(0, Hourly_Energy_In_Snow_Surface[HourOfDay]);
                else
                  Hourly_Energy_In_Snow_Surface[HourOfDay] = 0.0;                //150603
            }
        }
        Hourly_Energy_in_Snow[HourOfDay] = 
                Hourly_Energy_In_Snow_Surface[HourOfDay] 
                / (D_water 
                   * (C_snow / 1000.0) 
                   * std::min<double>(Hourly_Snow_Pack_SWE_mm / 1000.0, Skin_Thickness) 
                   + C_soil 
                     * std::max<double>(0, Skin_Thickness - Hourly_Snow_Pack_SWE_mm / 1000.0) 
                     * Bulk_Density_soil);
        Hourly_Energy_Below_Snow_Surface[HourOfDay] = 
                Hourly_Energy_in_Snow[HourOfDay] - Hourly_Energy_In_Snow_Surface[HourOfDay];
        double temp_var = C_soil / 1000.0 
                          * std::max<double>(0, Skin_Thickness - Hourly_Snow_Pack_SWE_mm / 1000.0) 
                          * Bulk_Density_soil
                          + std::min<double>(Hourly_Snow_Pack_SWE_mm / 1000.0, Skin_Thickness) 
                            * D_water 
                            * (C_snow / 1000.0);
        */
        //Hourly_Snow_Surface_T[HourOfDay] = U_internal_energy / 10000.;           //160211LML Hourly_Energy_In_Snow_Surface[HourOfDay] / temp_var;
        //if (fabs(Hourly_Snow_Surface_T[HourOfDay]) > 40.)
        //    Hourly_Snow_Surface_T[HourOfDay] = Hourly_Temp;                      //FMS May 1, 2015
        //150520 Avg_Daily_Snow_Surface_T += Hourly_Snow_Surface_T[HourOfDay] / 24.0;     //LML 140822


        //    '################ FMS Feb 18,  2014
        //     'ENERGY content of snow, in total, in surface layer and below (J/m2) at current hour
        /*
        double z_snow_surface = 3.;                                              //(mm water equivalent) according Erin Brooks paper
        double z_snow_damping_depth = 50.;                                       //(mm water equivalent)
        double E_fraction = z_snow_surface / z_snow_damping_depth;
        //surface layer - note that I am using density of ice rather than water (as Erin Brooks did)
        //Hourly_Snow_Surface_T(HourOfDay) = Energy_In_Snow_Surface(HourOfDay) / (D_ice * C_ice * (z_snow_surface / 1000))
        //below surface layer
        double Denominator = (D_ice * C_ice / 1000. * (Hourly_Ice_In_Snow_Amount[HourOfDay] - z_snow_surface)
                              + D_water * C_water / 1000. * Hourly_Water_In_Snow_Amount[HourOfDay]) / 1000.
                             + D_soil * C_soil / 1000. * 0.4; //0.4 m is the consider soil depth interacting with snow as Erin Brooks has defined it
        */
        //Hourly_Snow_Below_Surface_T[HourOfDay] = Hourly_Snow_Surface_T[HourOfDay]; //Energy_Below_Snow_Surface[HourOfDay] / Denominator;
        //FMS Mar 11, 2015 Snow temperature, Daily average
        if (HourOfDay == 0) {
            Nenner                          = 0;
            Avg_Daily_Snow_Surface_T        = 0;
            Avg_Daily_Snow_Below_Surface_T  = 0;
        }
        if (Current_Snow_Pack_SWE_mm > 0) {
            Avg_Daily_Snow_Surface_T       += Hourly_Snow_Surface_T[HourOfDay];
            Avg_Daily_Snow_Below_Surface_T += Hourly_Snow_Below_Surface_T[HourOfDay];
            Nenner++;
        }
        //**************************************
        //Snow Pack Mass and Energy Balance
        //**************************************
    } //end RunningSnow
        Density_Snow = D_Snow;
        Hourly_Snow_Pack_SWE[HourOfDay] = Current_Snow_Pack_SWE_mm;
        Hourly_Snow_Depth[HourOfDay] = (Current_Snow_Pack_SWE_mm / 1000.0) * D_water / D_Snow;     //(m) //140326FMS
        Hourly_Rain_mm[HourOfDay] = Hourly_Rain;
        Hourly_Sublimation_mm[HourOfDay] = Sublimation_rate;
        double Anderson_a = 0.5;                   //just guessing
        double Minimum_Snow_Depth = 1.0;           //(mm water equivalent); just guessing
        Fraction_Cover_Snow[HourOfDay] = 
                std::min<double>(1.0, 
                                 pow((Current_Snow_Pack_SWE_mm / Minimum_Snow_Depth), Anderson_a));
        //160214LML if(HourOfDay == 23) Snow_Amount_Today_mm = Hourly_Snow_Pack_SWE_mm;
        if (HourOfDay == 0) Snow_Amount_Peak_Today_mm = 0;
        if (Current_Snow_Pack_SWE_mm > Snow_Amount_Peak_Today_mm)
            Snow_Amount_Peak_Today_mm = Current_Snow_Pack_SWE_mm;
        /*160214LML
        double Balance_Hourly_Water_System = 
                //150527 (Hourly_Snow_Pack_SWE_mm - Previous_Hour_Snow_Pack_SWE_m * 1000.0)
                //150527 - Hourly_Snow_Melt_Amount[HourOfDay];
                - Hourly_Snow_Pack_SWE_mm
                + m_to_mm(Previous_Hour_Snow_Pack_SWE_m)
                - Hourly_Snow_Melt_Amount[HourOfDay]
                + Hourly_Precipitation_mm
                - Hourly_Rain
                - Sublimation_rate
                - Hourly_Intercepted; //FMS Oct 30, 2014
        */
        double Balance_Hourly_Water_System = Current_Snow_Pack_SWE_mm - m_to_mm(Previous_Hour_Snow_Pack_SWE_m);
        //assert(Balance_Hourly_Water_System <= 1e-6);
        if (HourOfDay == 0) {
            Avg_Daily_Fraction_Cover_Snow           = Fraction_Cover_Snow[HourOfDay] * 1.0/24.0;
            Balance_Daily_Snow_Today                = Balance_Hourly_Water_System;
            Daily_Snow_Melt_Amount_mm                = Hourly_Snow_Melt_Amount[HourOfDay];
            Daily_Sublimation_Or_Desublimation_mm    = Sublimation_rate;
            Daily_Rain_mm                           = Hourly_Rain;
            Daily_Intercepted_Pp_mm                 = Hourly_Intercepted;
            Daily_W_freeze_thaw_mm                  = W_freeze_thaw;
        } else {
            Avg_Daily_Fraction_Cover_Snow          += Fraction_Cover_Snow[HourOfDay] * 1.0/24.0;
            Balance_Daily_Snow_Today               += Balance_Hourly_Water_System;
            Daily_Snow_Melt_Amount_mm              += Hourly_Snow_Melt_Amount[HourOfDay];
            Daily_Sublimation_Or_Desublimation_mm  += Sublimation_rate;
            Daily_Rain_mm                          += Hourly_Rain;
            Daily_Intercepted_Pp_mm                += Hourly_Intercepted;
            Daily_W_freeze_thaw_mm                 += W_freeze_thaw;
        }
        Cumulative_Sublimation_mm       += Sublimation_rate > 0 ?  Sublimation_rate : 0;
        Cumulative_Re_Sublimation_mm    += Sublimation_rate < 0 ? -Sublimation_rate : 0;

        //double Daily_Snow_mm = Hourly_Snow_Pack_SWE_mm;
        Previous_Hour_Snow_Pack_SWE_m = Current_Snow_Pack_SWE_mm / 1000.0;
        QtotalkJm2[HourOfDay] = Qtotal;                                          //131211FMS
        W_freeze_thaw_mm[HourOfDay] = W_freeze_thaw;                             //131211FMS
        //150527 #ifdef CHECK_MASS_BALANCE
        //150527 bal_SWE.SetFinalPool(Hourly_Snow_Pack_SWE_mm);
        //150527 bal_SWE.SetFluxOut(Sublimation_rate + Hourly_Snow_Melt_Amount[HourOfDay]);
        //150527 if ((bal_SWE.GetFinalPool() > 0 || bal_SWE.GetInitPool() > 0) &&
        //150527     !bal_SWE.IsMassBalance())
        //150527     bal_SWE.PrintMassBalanceTerms("SWE during snow routine");
        //150527 //LML 141007 should check the mass balance even if there is no snowpack!
        //150527 #endif
    //160211LML }//Next HourOfDay
    //**************************************
    //Summary
    //Avg_Daily_Fraction_Cover_Snow /= 24; // FMS 12/10/2013
    /*LML 140820
    Hourly_Snow_Surface_T[0] = Hourly_Snow_Surface_T[24];
    Energy_in_Snow[0] = Energy_in_Snow[24];
    Energy_In_Snow_Surface[0] = Energy_In_Snow_Surface[24];
    Energy_Below_Snow_Surface[0] = Energy_Below_Snow_Surface[24];
    Hourly_Water_In_Snow_Amount[0] = Hourly_Water_In_Snow_Amount[24];
    Hourly_Ice_In_Snow_Amount[0] = Hourly_Ice_In_Snow_Amount[24];
    Hourly_Precipitation_Is_Snow[0] = Hourly_Precipitation_Is_Snow[24];
    Hourly_Snow_Surface_T[0] = Hourly_Snow_Surface_T[24];
    Hourly_Snow_Melt_Amount[0] = Hourly_Snow_Melt_Amount[24];
    Hourly_Rain_mm[0] = Hourly_Rain_mm[24];
    Fraction_Cover_Snow[0] = Fraction_Cover_Snow[24];
    */
    //FMS Mar 11, 2015
    //Total_SWE_m = mm_to_m(Hourly_Snow_Amount);
    if (HourOfDay == 23) {
        //Avg_Daily_Fraction_Cover_Snow = Fraction_Cover_Snow[23];                     //160214LML NEED TALK with Fidel!!!
        //OverallControl.BalanceSnowSimulation = OverallControl.BalanceSnowSimulation + Balance_Daily_Snow_Today
        //Total_SWE_m                 = mm_to_m(Snow_Amount_Today_mm); //(m h2o)                       //140501RLN
        Daily_Snow_Peak_Depth_mm         = m_to_mm(Snow_Amount_Peak_Today_mm / D_Snow);  //(m Snow) FMS 10/07/2013
        Daily_Snow_Melt_Depth_mm    = m_to_mm(Daily_Snow_Melt_Amount_mm / D_Snow); // mm of Snow
        if (Nenner > 0) {
            Avg_Daily_Snow_Surface_T       /= (double)Nenner;
            Avg_Daily_Snow_Below_Surface_T /= (double)Nenner;
        } else {
            Avg_Daily_Snow_Surface_T        = 0;
            Avg_Daily_Snow_Below_Surface_T  = 0;
        }
        Cumulative_Rain_mm += Daily_Rain_mm;
    }
    Cumulative_New_Snow_Fall += Hourly_Snow_Amount[HourOfDay];                   ;//FMS Feb 12, 2016

    //Long_Term_Liquid_Budget = Long_Term_Liquid_Budget + Daily_Precipitation_mm - 
    //Snow_Melt_Today - Daily_Intercepted_Pp - Daily_Rain_mm(Today) + Daily_Sublimation_Or_Desublimation(Today) //FMS 12/5/2013
    /*160214LML
    Long_Term_Liquid_Budget += Daily_Precipitation_mm
                               + m_to_mm(Daily_Sublimation_Or_Desublimation_m) 
                               - Snow_Melt_Today_mm 
                               - Daily_Rain_mm;                                  //161205FMS
    */
    Long_Term_Liquid_Budget += Balance_Hourly_Water_System;
    //OverallControl.BalanceSnowSimulation = Long_Term_Liquid_Budget
}
//______________________________________________________________________________
bool clsSnow::initialize()
{
    //Initialize snow for the firstday run
    //M.Liu
    //Hourly_Snow_Amount = 0.;
    Current_Snow_Pack_SWE_mm = 0;
    Long_Term_Liquid_Budget = 0.0;
    Hourly_Snow_Surface_T[23] = 0.;
    Hourly_Water_In_Snow_Amount[23] = 0.;
    Hourly_Ice_In_Snow_Amount[23] = 0.;
    Hourly_Energy_In_Snow_Surface[23] = 0.;
    Fraction_Cover_Snow[23] = 0;
    Hourly_Snow_Below_Surface_T[23] = 0;
    Age_Of_Snow = 0;
    Previous_Hour_Snow_Pack_SWE_m = 0;
    U_internal_energy = 0;
    Avg_Daily_Fraction_Cover_Snow = 0;
    Snow_Amount_Peak_Today_mm          = 0;                                           //160214LML
    return true;                                                                 //141221RLN
}
//______________________________________________________________________________
double clsSnow::CalcLongWaveHeat(const double StefBoltz, const double Unsworth_Montieth_LongWave_Atm_Emissivity, const double Air_Temp, const double Emissivity_of_Snow, const double Surface_Temperature) //FMS New Feb 13, 2016 By Brooks 2003
{
    double LongWaveHeat = (StefBoltz * 3600. * 1.) / 1000. *
            (Unsworth_Montieth_LongWave_Atm_Emissivity * pow(Air_Temp + 273.,4.)
             - Emissivity_of_Snow * pow(Surface_Temperature + 273.,4.));             //kJ/m2
    return LongWaveHeat;
}
//______________________________________________________________________________
bool clsSnow::DistributeExcessEnergyFreezeOrThaw(double &Water_Equivalent_Used_in_Melt_or_Frezzing
                                                , double &Water_Equivalent_Remant_Energy
                                                , double &PoolSWE_1
                                                , double &PoolSWE_2
                                                , double &PoolSWE_3
                                                , const bool UpdatePools) //FMS Feb 13, 2016 Distribute excess Energy in pools
{
    bool distributed = false;
    double Amount_Of_Water_Changes_State(0),Pool[4];
    Pool[1] = PoolSWE_1;
    Pool[2] = PoolSWE_2;
    Pool[3] = PoolSWE_3;
    Water_Equivalent_Remant_Energy = Water_Equivalent_Used_in_Melt_or_Frezzing;       //160218LML
    for (int p = 1; p <= 3; p++) {
        if (Water_Equivalent_Remant_Energy > Pool[p]) {
            Water_Equivalent_Remant_Energy  -= Pool[p];
            Amount_Of_Water_Changes_State   += Pool[p];
            Pool[p] = 0;
        } else {
            Amount_Of_Water_Changes_State   += Water_Equivalent_Remant_Energy;
            Pool[p]                         -= Water_Equivalent_Remant_Energy;
            Water_Equivalent_Remant_Energy   = 0;
            break;
        }
    }
    if (UpdatePools) {
        PoolSWE_1 = Pool[1];
        PoolSWE_2 = Pool[2];
        PoolSWE_3 = Pool[3];
    }
    Water_Equivalent_Used_in_Melt_or_Frezzing = Amount_Of_Water_Changes_State;
    distributed = true;
    return distributed;
}
#endif
