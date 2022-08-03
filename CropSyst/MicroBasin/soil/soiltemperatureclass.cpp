#ifdef MBVB_SOIL_TEMPERATURE
#include "soiltemperatureclass.h"
#include "util/pubtools.h"
#include "util/constants.h"
#include <iostream>
#include "corn/measure/measures.h"
//160217LML #ifndef CROPSYST_VERSION
#  include "snow/clssnow.h"
//160217LML #endif
#ifdef CROPSYST_PROPER_CROP
#  include "crop/phenology_interface.h"
#endif
#include <math.h>
#ifdef CROPSYST_VERSION
#include "organic_matter/OM_residues_profile_abstract.h"
#endif
//______________________________________________________________________________
SoilTemperatureClass::SoilTemperatureClass
(
AllControlClass               &ControlRef_
,SoilProfileClass             &SoilProfileRef_
,SoilStateClass               &SoilStateRef_
,const CS::Annual_temperature &annual_temperature_                               //141222
#ifdef CROPSYST_WEATHER
,const Weather                &weather_
#else
,WeatherStateDailyClass       &weather_
#endif
 ,const Organic_matter_residues_profile_abstract *OM_residues_profile_kg_m2_     //160224
,const CORN::Date             &today_
//160225 ,BasinCellClass               &BasinCellRef_
)
: CS::Simulation_element_abstract(today_)                                        //150810RLN
#ifdef CROPSYST_VERSION
, Soil_temperature_profile_hourly_interface()                                    //150810RLN
#endif
,ControlRef          (ControlRef_)
,SoilProfileRef      (SoilProfileRef_)
,SoilStateRef        (SoilStateRef_)
,weather             (weather_)
,annual_temperature  (annual_temperature_)                                       //141222
,OM_residues_profile_kg_m2(OM_residues_profile_kg_m2_)                           //160225
,has_snow_cover      (false)                                                     //160721RLN
//160225 ,BasinCellRef        (BasinCellRef_)
{
    nmax = ControlRef.getMaxSoilLayers();
    NuL = SoilProfileRef.NumberOfLayers();
    const int maxlayer = NuL + 5;                                                //150205LML
    Bulk_Density.resize(maxlayer,0);        
    Clay_Fraction.resize(maxlayer,0);       
    Node_depth.resize(maxlayer,0);          
    PWP_WC.resize(maxlayer,0);              
    SOM_fraction.resize(maxlayer,0);        
    CP.resize(maxlayer,0);                  
    Ice_Content.resize(maxlayer,0);         
    Water_Content.resize(maxlayer,0);       
    k.resize(maxlayer,0);                   
    a.resize(maxlayer,0);                   
    b.resize(maxlayer,0);                   
    c.resize(maxlayer,0);                   
    d.resize(maxlayer,0);                   
    T.resize(maxlayer,0);                   
    Tn.resize(maxlayer,0);                  
    T_freeze_thaw.resize(maxlayer,0);       
    Remaining_Energy.resize(maxlayer,0);    
}
//______________________________________________________________________________
SoilTemperatureClass::~SoilTemperatureClass()
{}
//______________________________________________________________________________
//150810RLN void SoilTemperatureClass::InitializeSoilTemperature()
bool SoilTemperatureClass::initialize()                          initialization_ //150810RLN
{
    int doy = today.get_DOY();
    NuL = SoilProfileRef.NumberOfLayers();
    //for(int i = 1; i <= NuL; i++){
    //    DebugPrintVariable(__FILE__,
    //                       __LINE__,
    //                       "WC",
    //                       SoilStateRef.get_liquid_water_content_volumetric(i),
    //                       i);
    //}
    Soil_Depth = 0;
    Node_depth[0] = -0.5 * SoilProfileRef.get_thickness_m(1);
    for (int layer = 1; layer <= NuL; layer++) {
        double Layer_Thickness = SoilProfileRef.get_thickness_m(layer);
        Node_depth[layer] = Soil_Depth + Layer_Thickness / 2.0;
        Soil_Depth += Layer_Thickness;
        PWP_WC[layer] = SoilProfileRef.get_permanent_wilt_point_volumetric(layer);  
        Clay_Fraction[layer] = SoilProfileRef.get_clay_percent(layer)/100.;  
    }
    Node_depth[NuL + 1] = Soil_Depth + SoilProfileRef.get_thickness_m(NuL) / 2.0;
    for (int layer = 1; layer <= NuL + 1; layer++) {
        SoilStateRef.Soil_Temperature[23][layer] = EstimatedSoilTemperature(Node_depth[layer], doy);

        //printf("l:%d SoilStateRef.Soil_Temperature[24][layer]:%f",layer,SoilStateRef.Soil_Temperature[24][layer]);
        //RS added - this needs re-evaluation!!! - water cannot simply turned into ice as a lot of energy is required to thaw it again
        if (SoilStateRef.Soil_Temperature[23][layer] < 0) {
            double SoilT = SoilStateRef.Soil_Temperature[23][layer];
            double ice = 0.0;
            double release_energy = 0.0;
            double water = SoilStateRef.get_liquid_water_content_volumetric(layer);
            FreezingThawing(SoilT,
                            SoilProfileRef.get_thickness_m(layer), 
                            2100, 
                            ice, 
                            water,
                            PWP_WC[layer],
                            SoilProfileRef.get_saturation_water_content_volumetric(layer,-9999.0/*150612LML SoilStateRef.Ice_Content[layer]*/),
                            release_energy);                                     //140313FMS
            SoilStateRef.set_water_content_volumetric_layer(layer,water);
            SoilStateRef.Soil_Temperature[23][layer] = SoilT;
        }
        //'end added
        Remaining_Energy[layer] = 0.0;                                           //140418LML
    }
    //for(int i = 1; i <= NuL; i++){
    //    DebugPrintVariable(__FILE__,
    //                       __LINE__,
    //                       "WC",
    //                       SoilStateRef.get_liquid_water_content_volumetric(i),
    //                       i);
    //}
    return true;                                                                 //150810RLN
}
//______________________________________________________________________________
void SoilTemperatureClass::FreezingThawing(double &newT,double LayerDepth, double HeatCapacitySoil,
  double &SoilIceContent, double &SoilWaterContent, double PWP_WC, double Saturation_WC,double &Actual_Release_Energy)
{
    //'this procedure calculates how much soil water will freeze and how much soil ice will thaw
    //'and how this changes the new soil temperature estimates
    //'old and newT (°C)
    //'LayerDepth (m)
    //'HeatCapacity (J/(m3 °C))
    //'SoilIceContent (m/m) water equivalent
    //'SoilWaterContent (m/m)
    if (ControlRef.run_freezing)                                                 //150721
    {
        if (newT >= 0.0) {
            //'THAWING
            if (SoilIceContent > 0) {
                double SoilLayerEnergy = newT * LayerDepth * HeatCapacitySoil;//(J/m2)
                double Potential_Release_Energy = calcEnergy2ThawOrFreeze(SoilIceContent * LayerDepth); //(J/m2)
                Actual_Release_Energy = std::min<double>(Potential_Release_Energy,SoilLayerEnergy);// J/m2
                double act_Thawing_Water = std::max<double>(SoilIceContent * Actual_Release_Energy / Potential_Release_Energy,0.0);
                SoilIceContent -= act_Thawing_Water;
                SoilWaterContent += act_Thawing_Water;
                Actual_Release_Energy = -Actual_Release_Energy;
            }
        } else {
            //Freezing
            double SoilLayerEnergy = -newT * LayerDepth * HeatCapacitySoil;
            double nonFreezingWaterContent = nonForFreezingWC(PWP_WC, Saturation_WC, newT);//(m3/m3 water equivalent)
            double MaxIceContentAtLayer = Saturation_WC - nonFreezingWaterContent;//(m3/m3 water equivalent)
            double Potential_Freezing_Energy = calcEnergy2ThawOrFreeze((MaxIceContentAtLayer) * LayerDepth); //J/m2
            double Actual_Freezing_Energy = std::min<double>(Potential_Freezing_Energy, SoilLayerEnergy);
            Actual_Release_Energy = Actual_Freezing_Energy;
            double pot_Freezing_Water =//(m3/m3)
                 potFreezingWater
                    (nonFreezingWaterContent ,MaxIceContentAtLayer
                    ,SoilWaterContent        ,SoilIceContent);
            double act_Ice_Increment(0);
            if (Potential_Freezing_Energy > 0) 
                act_Ice_Increment = pot_Freezing_Water * Actual_Freezing_Energy / Potential_Freezing_Energy;
            SoilIceContent += act_Ice_Increment;
            SoilWaterContent -= act_Ice_Increment;
            if (SoilIceContent > (Saturation_WC - PWP_WC)) nrerror("SoilIceContent > (Saturation_WC - PWP_WC)");
        }
    }
}
//______________________________________________________________________________
double SoilTemperatureClass::potFreezingWater(double nonFreezingWC, double MaxIceContentAtLayer,double SoilWaterContent, double SoilIceContent)
{
    double pot_Freezing_Water(0);                                                //141222RLN
    if (nonFreezingWC <= SoilWaterContent)                                       //141222RLN
    {   pot_Freezing_Water = std::min<double>(MaxIceContentAtLayer - SoilIceContent, SoilWaterContent);
        pot_Freezing_Water = std::max<double>(pot_Freezing_Water, 0);
    }
    return pot_Freezing_Water;
}
//______________________________________________________________________________
double SoilTemperatureClass::nonForFreezingWC(double PWP, double WC_Sat, double newT)
{
    double non_For_Freezing_WC = PWP;                                            //141222RLN
    if(newT >= -0.5 && newT <= 0)
    {   double C = 0.14 * pow(10.0,(0.136 * newT));                              //141222RLN
        if (C < PWP) C = PWP;
        non_For_Freezing_WC = (WC_Sat - C) / (0.0 - (-0.5)) * newT + WC_Sat; //Modification Taylor and Luthin 1978
        if(non_For_Freezing_WC < PWP) nrerror("non_For_Freezing_WC < PWP!");
    }
    return non_For_Freezing_WC;
}
//______________________________________________________________________________
double SoilTemperatureClass::calcEnergy2ThawOrFreeze(double m_Water)
{
    //'(J/m2)
    //Const D_water = 1000 'density of water (kg/m3)
    //const double Lf = 334000;       //'latent heat of fusion (J/kg)

    //'      (J/m2)             (m)      (kg/m3)  (J/kg)
    return m_Water * WaterDensity_kg_m3 * Latent_Heat_of_Fusion_J_kg;
}
//______________________________________________________________________________
double SoilTemperatureClass::calcHowMuchWaterCanFreezeOrThaw(double AvailableEnergy)
{   return(AvailableEnergy / (WaterDensity_kg_m3 * Latent_Heat_of_Fusion_J_kg));
}
//______________________________________________________________________________
double SoilTemperatureClass::EstimatedSoilTemperature
(double Node_depth, int doy)
{
    const double dd(2);
    /*160224
    double ann_avg      = ControlRef.v_annual_temperature_avg.get_value();
    double ann_half_amp = ControlRef.v_annual_temperature_avg_half_amplitude.get_value();
    int ann_phase       = ControlRef.v_annual_temperature_phase.value;
    */
    double Estimated_Soil_Temperature =
      annual_temperature.avg //160224RLN ann_avg
      + annual_temperature.avg_half_amplitude //160224RLN . ann_half_amp
         * exp(-Node_depth / dd)
            * sin(2.0 * 3.1416 / 365.0 * (doy - annual_temperature.phase) //160224RLN  ann_phase)
                  - Node_depth / dd);
    return Estimated_Soil_Temperature;
}
//______________________________________________________________________________
double SoilTemperatureClass::HeatConductivity(double Bulk_Density, double volumetric_WC, double fraction_clay)
{
    double C1 = 0.65 - 0.78 * Bulk_Density + 0.6 * pow(Bulk_Density,2);    // 'equation 4.27; coeff of 4.20 A (page 32+ of Campbell 1985)
    double C2 = 1.06 * Bulk_Density;                                       // 'equation 4.25; coeff of 4.20 B (page 32+ of Campbell 1985)
    double C3 = 1.0 + 2.6 / sqrt(fraction_clay);                           // 'equation 4.28; coeff of 4.20 C (page 32+ of Campbell 1985)
    double C4 = 0.03 + 0.1 * pow(Bulk_Density,2);                          // 'equation 4.22; coeff of 4.20 D (page 32+ of Campbell 1985)
    double Heat_Conductivity = C1 + C2 * volumetric_WC - (C1 - C4) * exp(-pow(C3 * volumetric_WC, 4));
    return Heat_Conductivity;
}
//______________________________________________________________________________
double SoilTemperatureClass::SoilHeatCapacity(double BD, double SOM_fraction, double volumetric_WC,
                        double volumetric_IceC)
{
    //'soil heat capacity (J/(m3 °C))
    //'BD = bulk density (g/cm3)
    //'SOM fraction (g/g)
    //'volumetric water and ice content (m/m)
    const double PD = 2.65;         // 'particle density (g/cm3)  - multiply by 1000 gets (kg/m3)
    const double SOM_D = 1.3;         // 'SOM particle density (g/cm3)  - multiply by 1000 gets (kg/m3)
    const double Cm_minerals = 750;         // 'heat capacity of clay, silt and sand (J/(kg °C))
    const double Cm_SOM = 1880;         // 'heat capacity of soil organic matter (J/(kg °C))
    const double Cv_water = 4180000;         // 'volumetric heat capacity of water (J/(m3 °C))
    const double Cv_ice = 1938000;         // 'volumetric heat capacity of ice (J/(m3 °C))
    double Soil_Heat_Capacity = 
                      (PD * 1000. * Cm_minerals * (1 - SOM_fraction) + SOM_D * 1000. * Cm_SOM * SOM_fraction)
                       * BD / (PD * (1 - SOM_fraction) + SOM_D * SOM_fraction)
                      + Cv_water * volumetric_WC
                      + Cv_ice * volumetric_IceC;
    //'old:
    //'Heat_Capacity = 2400000 * Bulk_Density / 2.65 + 4180000 * volumetric_WC
    return Soil_Heat_Capacity;
}
//______________________________________________________________________________
//150810RLN renamed void SoilTemperatureClass::InitializeDayforSoilTemperature()
bool SoilTemperatureClass::start_day()                             modification_ //150810RLN
{

    //Year = Simulation.pTimeState->getToday().get_year();
    //Need check the unit M.Liu Jan. 17, 2014
    #ifdef WEATHER_PROVIDER_VERSION
    double Solar_Irradiance = weather.daily_provider.solar_radiation.get_MJ_m2(); // Need check the unit M.Liu Jan. 17, 2014 Seconds_Per_Day 'Convert from MJ/m2/d to J/m2/s
    double Extraterrestrial_Solar_Radiation = weather.daily_provider.ET_solar_irradiance.get_MJ_per_m2_day(today.get_DOY());//.get_J_per_m2_day();  //150728 daily.ET_solar_irradiance.get_extraterrestrial_irradiance_today();      // '* 1000000# / Seconds_Per_Day 'Convert from MJ/m2/d to J/m2/s
    #else
    #error obsolete
    double Solar_Irradiance = weather.getDailySolarRadiation();    // Need check the unit M.Liu Jan. 17, 2014 Seconds_Per_Day 'Convert from MJ/m2/d to J/m2/s
    double Extraterrestrial_Solar_Radiation = weather.getDailyExtraterrestrialSolarRadiation();    // '* 1000000# / Seconds_Per_Day 'Convert from MJ/m2/d to J/m2/s
    #endif
    //160412unused Daily_Soil_Water_Evaporation = m_to_mm(SoilStateRef.Daily_Soil_Water_Actual_Evaporation_m);
    Surface_Absorptivity = 0.8;
    Surface_Emissivity = 0.95;
    Long_Wave_Absorptivity = 0.95;
    //Extraterrestrial_Solar_Radiation = Solar_Irradiance / 0.75;
    //std::clog<<"Set Extraterrestrial_Solar_Radiation = Solar_Irradiance / 0.75!!!\n";
    Atmospheric_Transmission_Coefficient = Solar_Irradiance / Extraterrestrial_Solar_Radiation;
    if (Atmospheric_Transmission_Coefficient > 0.75) Atmospheric_Transmission_Coefficient = 0.75;
    Cloud_Cover = 2.33 - 3.33 * Atmospheric_Transmission_Coefficient;
    if (Cloud_Cover > 1) Cloud_Cover = 1;
    else if (Cloud_Cover < 0) Cloud_Cover = 0;
    /*160224 now organic_matter_residues_profile_kg_m2 is optional member reference
    #ifdef CROPSYST_VERSION
    Organic_matter_residues_profile_abstract *organic_matter_residues_profile_kg_m2
     = BasinCellRef.LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;
    #endif
    */

    for (int layer = 1; layer <= NuL + 1 ; layer++)                              //150303FMS  added + 1
    {
      if (layer <= NuL) {
        Bulk_Density[layer] = SoilProfileRef.get_bulk_density_g_cm3(layer);      //140424RLN
        SOM_fraction[layer] =
        #ifdef CROPSYST_VERSION
           OM_residues_profile_kg_m2                                             //160224RLN
           ? (OM_residues_profile_kg_m2->get_percent_organic_matter(layer) * 0.01) //std::clog<<"DEBUG::Roger need provide SOM_fraction!!!\n";//assert(false);  //RLN Need to provide this
           : 0.02; // default value when organic matter model is disabled         //160224RLN
        #else
            SoilStateRef.Layer_Organic_Matter_Content[layer] / 100.0;
            // !!! check whether dividing by 100 is correct
        #endif
      } else {
        Bulk_Density[layer] = Bulk_Density[layer-1];                             //150522
        SOM_fraction[layer] = SOM_fraction[layer-1];                             //150522
      }
      SoilStateRef.Avg_Daily_Soil_T[layer] = 0.;
    }
    return true;                                                                 //151116LML
}
//______________________________________________________________________________
void SoilTemperatureClass::CalculateHourlySoilTemperature
#if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
(  double Fraction_Canopy_Intercepted_Solar_Radiation
#ifdef MBVB_SNOW
,const clsSnow &snow
#endif
,const double crop_height)
#else
(clsSimulation &Simulation,clsSnow &Snow, clsCrop &Crop)
#endif
{
#ifdef LIU_DEBUG    
    //LML 140821 for Qt debuging the array values
    //double k[20];
    //double a[20];
    //double b[20];
    //double c[20];
    //double d[20];
    //double T[20];
    //double Tn[20];
    //double T_freeze_thaw[20];
    //double Remaining_Energy[20]; 
    //double CP[20];
    //double Water_Content[20];
    //double Ice_Content[20];        
#endif
    const double f(0.6);    // ' constant for setting forward, backward or centered difference method
    const double G(1 - f);  //
    int hour = ControlRef.hour;                                                  //140814LML
    int doy = today.get_DOY();                                                   //??????LML
    //DebugRunToTime(doy,hour,197,6);
    for (int layer = 1; layer <= NuL; layer++) {
        Water_Content[layer] = SoilStateRef.get_liquid_water_content_volumetric(layer)/*Water_Content[layer]*/;
        Ice_Content[layer] = SoilStateRef.get_ice_content_volumetric(layer);     //141005RLN
        Remaining_Energy[layer] = 0.0;                                           //140821LML
    }
    //'Recalculate bottom boundary condition
    T[NuL + 1] = EstimatedSoilTemperature(Node_depth[NuL + 1], doy);
    Tn[NuL + 1] = T[NuL + 1];
    double Hourly_AirT = weather.getHourlyTemperature(hour);
    //Hourly_Solar_Irradiance = weather.getHourlyFractionOfSolarIrradiance(hour) * Solar_Irradiance * 1.0e6 / Seconds_Per_Hour; // 'Convert MJ/m2/d to J/m2/s
    double Hourly_Solar_Irradiance =
          weather.getHourlySolarIrradiance(hour)
          * 1.0e6 / Seconds_Per_Hour; //Convert MJ/m2/d to J/m2/s                //141202LML
    #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
    // passed parameter
    #else
    double Fraction_Canopy_Intercepted_Solar_Radiation =                         //141204RLN
      (Simulation.pSimulationRotation->getCropEmerged())
      ? Crop.pCropState->Fraction_Solar_Rad_Intercepted_Total_Canopy             //140211LML Need improve later
      : 0.0;
    #endif
    double Fraction_Surface_Residue_Intercepted_Solar_Radiation = 0;//Weather.getHourlySurfaceResidueSolarInterceptionFraction(Hour);  //M.Liu Feb. 11, 2014 Need improve later
    double Fraction_Standing_Stubble_Intercepted_Solar_Radiation = 0;//Weather.getHourlyStandingStubbleSolarInterceptionFraction(Hour);//M.Liu Feb. 11, 2014 Need improve later
    #ifdef MBVB_SNOW
    double Fraction_Snow_Cover = Snow.Fraction_Cover_Snow[hour];
    //Snow_Subsurface_T = SoilStateRef.Soil_Temperature[Hour+1][1]; //Snow.Hourly_Snow_Below_Surface_T[Hour+1];  //140211LML Need improve later
    //double Snow_Subsurface_T = Snow.Hourly_Snow_Surface_T[hour];               //140218FMS
    double Density_Snow = Snow.Density_Snow; // ton/m3                           //140328FMS
    double Depth_Snow = Snow.Hourly_Snow_Depth[hour];                            //140326FMS
    #else
    // Snow not yet implemented
    double Fraction_Snow_Cover  = has_snow_cover ? 1.0 : 0.0;                    //160721
       //160721 snow.Fraction_Cover_Snow[hour]; // Snow.Fraction_Cover_Snow[hour+1];
    //Snow_Subsurface_T = SoilStateRef.Soil_Temperature[Hour+1][1]; //Snow.Hourly_Snow_Below_Surface_T[Hour+1];  //140211LML Need improve later
    //160219LML double Snow_Subsurface_T    = snow.Hourly_Snow_Surface_T[hour]; //Snow.Hourly_Snow_Surface_T[hour+1];        //140218FMS
    //160219LML double Density_Snow         = snow.Density_Snow; //Snow.Density_Snow;    //ton/m3                  //140328FMS
    //160219LML double Depth_Snow           = snow.Hourly_Snow_Depth[hour]; //Snow.Hourly_Snow_Depth[hour+1];                   //140326FMS
    #endif
    //'Include shading by canopy and residues; RS added snow cover
    Hourly_Solar_Irradiance *=
          (1.0 - Fraction_Canopy_Intercepted_Solar_Radiation)
        * (1.0 - Fraction_Standing_Stubble_Intercepted_Solar_Radiation)
        * (1.0 - Fraction_Surface_Residue_Intercepted_Solar_Radiation)
        * (1.0 - Fraction_Snow_Cover)
        ;
    double Combined_Surface_T = Hourly_AirT;
    if (Fraction_Snow_Cover > 0) Combined_Surface_T = 0;//Snow_Subsurface_T * Fraction_Snow_Cover + Hourly_AirT * (1 - Fraction_Snow_Cover); //'taking the weighted average
    double Hourly_Relative_Humidity = weather.getHourlyRelativeHumidity(hour) / 100.0;   // 'Expressed as a fraction
    double Hourly_Vapor_Pressure = Hourly_Relative_Humidity * weather.calcSatVP(Combined_Surface_T); // 'RS exchanged Hourly_Temperatue with Combined_Surface_T
    double Hourly_Latent_Heat =
                         m_to_mm(SoilStateRef.Hourly_Soil_Water_Evaporation_m)
                       * Latent_Heat_of_Vaporization_J_kg / Seconds_Per_Hour;         // 'Convert from kg/m2/h to J/m2/s
    //'Pass previous time step temperatures for all soil layers
    for (int layer = 1; layer <= NuL; layer++) {
        if (hour == 0) T[layer] = SoilStateRef.Soil_Temperature[23][layer];      //140814LML was 24
        else T[layer] = SoilStateRef.Soil_Temperature[hour - 1][layer];
        /*std::clog<<"CHECKING SOIL TEMPERATURE:"
                 <<"\TLayer:"     <<layer
                 <<"\tT:"      <<T[layer]
                 <<std::endl;*/
        //'initialize the freez-thaw old temperature
        T_freeze_thaw[layer] = T[layer];
    }
    Tn[0] = Combined_Surface_T;           // 'RS exchanged Hourly_AirT with Combined_Surface_T
    T[0] = Combined_Surface_T;            // 'RS exchanged Hourly_AirT with Combined_Surface_T
    int iteration = 0;
    while (iteration < 50){
        //140326FMS changed the position the following lines
        for (int layer = 0; layer <= NuL; layer++) {
            //' calculates heat capacity weighted by solid and water and SOM phase
            if (layer == 0) CP[layer] = 0;       // ' heat capacity of boundary layer  = 0
            else CP[layer] = SoilHeatCapacity(Bulk_Density[layer], 
                                              SOM_fraction[layer], 
                                              Water_Content[layer], 
                                              Ice_Content[layer])
                             * SoilProfileRef.get_thickness_m(layer);
            //' calculates conductance per layer, equation 4.20 for thermal conductivity
            if (layer == 0) {
                // Campbell (1986) boundary layer conductance (W/m2 K)
                //k[layer] = 40;                                                 //140902FMS
                k[layer] = calcBoundaryLayerConductance(hour, T[layer + 1],crop_height);     //140822FMS
                //160219LML if (Fraction_Snow_Cover > 0)
                //160219LML     k[layer] = pow((1.0 / k[layer]
                //160219LML                     + 1.0 / (2.5 * (10.0e-6) * (Density_Snow * Density_Snow)
                //160219LML                     - 1.23 * (10.0e-4) * Density_Snow + 0.024) / Depth_Snow),
                //160219LML                    -1.0); //Calonne et al 2011                   //140328FMS
                Boundary_Layer_Heat_Conductance = k[layer];                      //FMS Jan 27, 2016
            } else {
                k[layer] = HeatConductivity(Bulk_Density[layer], 
                                            Water_Content[layer], 
                                            Clay_Fraction[layer])
                           / (Node_depth[layer + 1] - Node_depth[layer]);
            }
            /*std::clog<<"Layer:"     <<layer
                     <<"\tk:"       <<k[layer]
                     <<"\tCP:"      <<CP[layer]
                     <<std::endl;*/

        }
        for (int layer = 1; layer <= NuL; layer++) {
            //'calculate elements of the matrix
            c[layer] = -k[layer] * f;
            a[layer+1] = c[layer];
            b[layer] = f * (k[layer] + k[layer-1]) + CP[layer] / Seconds_Per_Hour;
            d[layer] = G * k[layer-1] * T[layer-1] 
                       + (CP[layer] / Seconds_Per_Hour - G * (k[layer] + k[layer-1])) * T[layer]
                       + G * k[layer] * T[layer+1];
            /*std::clog<<"matrix Layer:"     <<layer
                     <<"\tc:"       <<c[layer]
                     <<"\tb:"       <<b[layer]
                     <<"\td:"       <<d[layer]
                     <<"\tk:"       <<k[layer]
                     <<"\tk[L-1]:"  <<k[layer-1]
                     <<"\tT:"       <<T[layer]
                     <<"\tT[L+1]:"  <<T[layer+1]
                     <<std::endl;*/
        }
        //'as an approximation calculate net radiation (W/m2) here with given surface temperature
        //'recalculate in new loop and repeat the procedure until Tsurface [T(1)] does not oscillate
        double Net_Short_Wave_Radiation_Absorbed = 
                Surface_Absorptivity * Hourly_Solar_Irradiance;
        double Sky_Emissivity = weather.calcSkyEmissivity(Hourly_Vapor_Pressure, T[0], Cloud_Cover);
        double Sky_Long_Wave_Radiation_Absorbed = 
                Long_Wave_Absorptivity * Sky_Emissivity * StefBoltz_W_m2K4 * pow((T[0] + 273.15),4.);
        double Surface_Long_Wave_Radiation_Outgoing = 
                Surface_Emissivity * StefBoltz_W_m2K4 * pow((T[1] + 273.15),4);
        double Rnet = Net_Short_Wave_Radiation_Absorbed 
                      + (1 - Fraction_Snow_Cover)
                        * (Sky_Long_Wave_Radiation_Absorbed - Surface_Long_Wave_Radiation_Outgoing);
        //double d1_old = d[1];
        double total_energy = CORN::is_approximately<double>(Fraction_Snow_Cover,0) ? (Rnet - Hourly_Latent_Heat) : 0;
        if (!CORN::is_approximately<double>(Fraction_Snow_Cover,0)) Tn[0] = 0;      //160218LML_FMS
        d[1] += k[0] * Tn[0] * f + total_energy;         // 'add net radiation and latent heat transfer here
        d[NuL] += k[NuL] * f * Tn[NuL + 1];                         // 'the last term is redundant if Tn(NuL+1) = T(NuL+1) because K(NuL) = 0
        for (int layer = 1; layer <= NuL; layer++) {
            d[layer] += Remaining_Energy[layer] / Seconds_Per_Hour;              //140326FMS
            /*std::clog<<"Layer:"     <<layer
                     <<"\tRemaining_Energy:"<<Remaining_Energy[layer]
                     <<"\td:"               <<d[layer]
                     <<"\tk[0]:"            <<k[0]
                     <<"\tTn[0]:"           <<Tn[0]
                     <<"\tf:"               <<f
                     <<"\tRnet:"            <<Rnet
                     <<"\tHourly_lat_Heat:" <<Hourly_Latent_Heat
                     <<std::endl;*/
            //J/m2/3600---> W/m2
            Remaining_Energy[layer] = 0;
        }
        //'start Thomas algorithm
        for (int layer = 1; layer <= NuL - 1; layer++) {
           c[layer] /= b[layer];
           d[layer] /= b[layer];
           b[layer+1] -= a[layer+1] * c[layer];
           d[layer+1] -= a[layer+1] * d[layer];
           /*std::clog<<"Layer:"     <<layer
                    <<"\tc:"       <<c[layer]
                    <<"\td:"       <<d[layer]
                    <<"\tb:"       <<b[layer]
                    <<"\tb[L+1]:"  <<b[layer+1]
                    <<"\td[L+1]:"  <<d[layer+1]
                    <<std::endl;*/
        }
        Tn[NuL] = d[NuL] / b[NuL];
        for (int layer = NuL - 1; layer >= 1; layer--) {
            Tn[layer] = d[layer] - c[layer] * Tn[layer+1];
            /*std::clog<<"Layer:"     <<layer
                     <<"\tTn:"      <<Tn[layer]
                     <<"\td:"       <<d[layer]
                     <<"\tc:"       <<c[layer]
                     <<"\tTn[L+1]:" <<Tn[layer+1]
                     <<std::endl;*/
        }
        //'end Thomas algorithm
        double Energy_Released_Profile = 0;                                      //140326FMS
        for (int layer = 1; layer <= NuL; layer++) {
            /*std::clog<<"Layer:"     <<layer
                     <<"\tTn:"      <<Tn[layer]
                     <<"\tR_Engy:"  <<Remaining_Energy[layer]
                     <<std::endl;*/
            FreezingThawing(Tn[layer], 
                            SoilProfileRef.get_thickness_m(layer),
                            CP[layer], 
                            Ice_Content[layer], 
                            Water_Content[layer], 
                            PWP_WC[layer],
                            SoilProfileRef.get_saturation_water_content_volumetric(layer,-9999.0/* SoilStateRef.Ice_Content[layer]*/), //150612LML
                            Remaining_Energy[layer]);                            //140409FMS
            if (Ice_Content[layer] > 0.1) {
                int debug = 1;
            }
            Energy_Released_Profile += fabs(Remaining_Energy[layer]);            //140326FMS
            T_freeze_thaw[layer] = Tn[layer];
        }
        //if (fabs(T[1] - Tn[1]) / fabs(T[1] + 0.01) < 0.01) iteration = 100;
        if (CORN::is_approximately<double>(Energy_Released_Profile,0.0,1e-12)) iteration = 50;
        else iteration ++;
        //this loop updates temperatures after the first Thomas loop and is needed
        //T[1] = Tn[1];   //due to the inclusion of Tsurface [T(1)] to calculate net radiation at "exchange" surface
    }    //was 100
    for (int layer = 1; layer <= NuL + 1; layer++) {
        T[layer] = Tn[layer];
        //'update Temperature
        SoilStateRef.Soil_Temperature[hour][layer] = Tn[layer];
        if (ControlRef.hour == 0) SoilStateRef.Avg_Daily_Soil_T[layer] = Tn[layer] / 24.0;
        else SoilStateRef.Avg_Daily_Soil_T[layer] += Tn[layer] / 24.0;
        if (layer < (NuL + 1)) {
            //'update water and ice contents
            SoilStateRef.set_water_content_volumetric_layer(layer,Water_Content[layer]);
            SoilStateRef.Ice_Content[layer] =
                    CORN::is_approximately<double>(Ice_Content[layer],0.0,1e-12) ? 0 : Ice_Content[layer];
            //'update saturated hydraulic conductivity when soil is frozen
            double Ks_ice_reduction_factor = 
                    1.0 / (pow((1.0 + 8.0 * Ice_Content[layer]),2.0));   
                    // 'NOAA Technical Report NWS 52, 2007, p.7 eq. 5 (http://www.nws.noaa.gov/oh/hrl/hsmb/docs/hydrology/PBE_SAC-SMA/NOAA_Technical_Report_NWS_52.pdf)
            SoilProfileRef.K_Sat[layer] = 
                    Ks_ice_reduction_factor * SoilProfileRef.Ks_Unfrozen[layer];  
            SoilProfileRef.Ksat_for_Hr2FC[layer] = 
                    Ks_ice_reduction_factor * SoilProfileRef.Ksat_for_Hr2FC_Unfrozen[layer];
            //'RS and CS decided not to use the following
            //'        'update FC, PWP and SAT when soil is frozen
            //'        SoilProfileRef.FieldCapacity(L) = SoilProfileRef.FCUnfrozen(L) * (1 - Ice_Content(L) / SoilProfileRef.SATUnfrozen(L))
            //'        SoilProfileRef.PermanentWiltingPoint(L) = SoilProfileRef.PWPUnfrozen(L) * (1 - Ice_Content(L) / SoilProfileRef.SATUnfrozen(L))
            //'        SoilProfileRef.SaturationWaterContent(L) = SoilProfileRef.SATUnfrozen(L) - Ice_Content(L)
        }
    }
    SoilProfileRef.setIceContentRef(SoilStateRef.Ice_Content);                   //150612LML
}
//______________________________________________________________________________
double SoilTemperatureClass::calcBoundaryLayerConductance(int hour,double Ts,const double crop_height)
{
    //FMS Aug 22, 2014
    const double v = 1.51e-5;                          //(m2/s)Kinematic viscosity for the air
    const double T_Kelvin = 298.0;              //Dg Kelvin
    const double Cp = 29.3;                     // Jmol-1 C-1 specific heat of air at constant pressure
    //doy = ControlRef.today.get_DOY();
    double Ta = weather.getHourlyTemperature(hour);
    //160217LML double u2 = weather.getHourlyWind(hour);    // m/s wind speed measure at 2 m
    double Zero_Plane_Displacement(0);
    double D_Length = calcZm(Zero_Plane_Displacement,crop_height);
    double z = Zero_Plane_Displacement / 0.65;
    double u(0);
    weather.DetermineWindVelocityAtSpecifiedHeight(hour,z, D_Length, Zero_Plane_Displacement, false, u);
    //D_Length = 1 //MicroBasin.ElementLength
    double u2 = u;                                                               //FMS Feb 12, 2016
    double RaynoldsNumber = u2 * D_Length / v;
    double GrashofNumber = standard_gravity * D_Length * D_Length * D_Length * (Ts - Ta) / (T_Kelvin * v);
    double Kind_Convection(0);
    if (CORN::is_approximately<double>(RaynoldsNumber,0.0,1e-12)) //  need double check!! //140902LML
        Kind_Convection = GrashofNumber / ((RaynoldsNumber + 1) * (RaynoldsNumber + 1));  //OJO check that
    else
        Kind_Convection = GrashofNumber / (RaynoldsNumber * RaynoldsNumber);
    double Threshold = 50;
    double gHa(0.0);                    //mol m-2 s-1
    if (RaynoldsNumber < 4400) {  //  need double check the value!!!             //140902LML
        //If RaynoldsNumber < 3000 Then                                          //140902FMS
        //Laminar flux
        if (Kind_Convection < Threshold)
            //Forced convection
            gHa = 0.135 * pow((u2 / D_Length),0.5);
        else if (CORN::is_approximately<double>(Kind_Convection / GrashofNumber,1.0,1e-12)) {
            //Foced ans free convection
            gHa = (0.135 * pow((u2 / D_Length),0.5) + 0.05 * pow(fabs(Ts - Ta) / D_Length,0.25)) / 2.0;
        } else {
            // Free convection
            if (Ts > Ta) // FMS Aug 29, 2014
                gHa = 0.05 * pow((fabs((Ts - Ta) / D_Length)),0.25);
            else           
                gHa = 20.0 / 29.3; // Default by Campbell 1986                   //140902FMS
        }
    } else if (RaynoldsNumber > 4400) {
        //Turbulent flux
        double Molar_Density_Of_Air = 41.62; // (41.65 mol m-3 at 20// C and 101 Ha)
        double zH = 0.2 * D_Length;
        double diabatic_correction_factors_H(0);
        double diabatic_correction_factors_M(0);
        if ((u2 > 3) && (Ta > 28)) {
            double Atmospheric_Stability = -0.4 * standard_gravity * zH 
                                           / (Molar_Density_Of_Air * Cp * 298.0 * u * u * u);
            diabatic_correction_factors_H = -2 * log((1.0 + pow((1 - 16 * Atmospheric_Stability), 0.5)) / 0.2);
            diabatic_correction_factors_M = 0.6 * diabatic_correction_factors_H;
        } 
        gHa = 0.4 * 0.4 * Molar_Density_Of_Air * u 
              / (log((z - Zero_Plane_Displacement) / D_Length) + diabatic_correction_factors_M) 
              * (log((z - Zero_Plane_Displacement) / zH) + diabatic_correction_factors_H);
    } else {
    //both Flux
        gHa = 20.0 / Cp;  // Default by Campbell 1986
    }
    double BoundaryLayerConductance = gHa * Cp;
    //if (BoundaryLayerConductance < 20) BoundaryLayerConductance = 20;          //140902LML
    return BoundaryLayerConductance;
}
//______________________________________________________________________________
double SoilTemperatureClass::calcZm(double &d, const double crop_height) //(m)   //140826FMS
{  // By Campbell and Norman 1998
    //d: Zero_Plane_Displacement
    double Zm(0);
    double h = 0;                                                                //160219LML_FMS crop_height;
    double Short_Grass_Height(0);
    Surface_Soil_Cover_Type SoilCover = SoilStateRef.Surface_Soil_Cover;
    switch(SoilCover) {
    case SSC_Snow:
        Zm = 0.002;
        h = 0.1;
        //d = h - 2.5 * calcZm
        break;
    case SSC_TreeCrop:
        Zm = 0.35;
        h = 1.8;
        //d = h - 2.5 * calcZm
        break;
    case SSC_SmallCrop:
        Zm = 0.07;
        h = 0.5;
        //d = h - 2.5 * calcZm
        break;
    case SSC_TallCrop:
        Zm = 0.27; //0.41-0.13
        h = 1.3;
        //d = h - 2.5 * calcZm
        break;
    case SSC_BareSoil:
        Zm = 0.004; // 0.002-0.006
        h = 0.05;
        //d = h - 2.5 * calcZm
        break;
    default:
        Short_Grass_Height = 0.12;
        h = Short_Grass_Height;
        Zm = 0.1 * Short_Grass_Height;
        break;
    }
    if (crop_height > 0) h = crop_height;                                        //160219LML_FMS
    d = 0.65 * h;
    return Zm;
}
//______________________________________________________________________________
float64 SoilTemperatureClass::get_temperature(nat8 layer)                            const
{  return SoilStateRef.Soil_Temperature[24][layer];
}
//_2015-08-13RLN________________________________________________________________
float64 SoilTemperatureClass::get_temperature(CORN::Hour hour, nat8 layer) const
{  return SoilStateRef.Soil_Temperature[hour][layer];
}
//_2015-08-10RLN________________________________________________________________
#endif
