#ifndef CROPSYST_VERSION
#include "soilnitrogentransformationclass.h"
#include "math.h"
#include "util/constants.h"
#include "util/pubtools.h"
//______________________________________________________________________________
SoilNitrogenTransformationClass::SoilNitrogenTransformationClass(
  SoilProfileClass &_SoilProfileRef,SoilStateClass &_SoilStateRef,
  SoilAbioticFunctionsClass &_AbioticFunctionsRef)
    :SoilProfileRef(_SoilProfileRef)
    ,SoilStateRef(_SoilStateRef)
    ,AbioticFunctionsRef(_AbioticFunctionsRef)
{
}
//______________________________________________________________________________
double SoilNitrogenTransformationClass::N2N2ONitrate(double Nitrate_Concentration_Dry_Soil)
{
    //'Calculate nitrate-N-based potential N2/N20
    //' From Parton et al, 1996 Global Biogeochemical Cycles
    //const double Pi = 3.141593;
    //'Convert nitrate mass from kgN/kg Soil to ppm
    double NO3_N = Nitrate_Concentration_Dry_Soil * 1000000.0;   //#
    //'Nitrate content must be in PPM NO3-N
    double N2N2O_Nitrate = (1.0 - (0.5 + atan(Pi * 0.01 * (NO3_N - 190.0)) / Pi)) * 25.0;
    return N2N2O_Nitrate;
}
//______________________________________________________________________________
double SoilNitrogenTransformationClass::Minimum(double a, double b, double c)
{
    double Temporary_Minimum = std::min<double>(std::min<double>(a,b),c);
    return Temporary_Minimum;
}
//______________________________________________________________________________
double SoilNitrogenTransformationClass::N2N2OResp(double Layer_CO2_Loss)
{
    //'Calculate respiration-based potential N2/N20
    //'From Parton et al, 1996 Global Biogeochemical Cycles
    //'Convert respiration from kg CO2-C/m2/day to kg CO2-C/ha/day
    double Respiration = Layer_CO2_Loss * 10000.0;
    //'Respiration must be in kg C/ha/day
    double N2N2O_Resp = 13.0 + (30.78 * atan(Pi * 0.07 * (Respiration - 13.0))) / Pi;
    return N2N2O_Resp;
}
//______________________________________________________________________________
double SoilNitrogenTransformationClass::NitrateResponseFunction(double Denitrification_Half_Rate,
  double Nitrate_Concentration_Dry_Soil)
{
    //'Based on data from Del Grosso 2000 Global Biogeochemical Cycles
    //'Nitrate_Concentration_Dry_Soil is in kgN/kg soil
    return Nitrate_Concentration_Dry_Soil / (Nitrate_Concentration_Dry_Soil + Denitrification_Half_Rate);
}
//______________________________________________________________________________
double SoilNitrogenTransformationClass::RespirationFunction(double CO2_Loss_Per_Unit_Soil_Mass)
{
    //'Modified equation (and normalized) from Del Grosso et al 2000 Global Biogeochemical Cycles
    const double Standardize_Respiration_For_Potential_Denitrification = 75. /*FMS Mar 26, 2015 50.0*/;    // 'mg C/kg Soil/day
    double Respiration = CO2_Loss_Per_Unit_Soil_Mass * 1000000 * 24;       // ' convert kg C/kg Soil /hour to mg C/kg Soil /day
    //'This function provides values from 0 to 1 and was adapted using data 
    //from del Grosso et al 2000 Global Biogeochemical Cycles
    double Respiration_Function = 
            pow((Respiration / Standardize_Respiration_For_Potential_Denitrification), 1.3 /*FMS Mar 27, 2015 1.5*/);
    if (Respiration_Function > 1) Respiration_Function = 1;
    return Respiration_Function;
}
//______________________________________________________________________________
void SoilNitrogenTransformationClass::NitrogenTransformation
(
#if (defined(CROPSYST_PROPER_CROP) || defined(CROPSYST_VERSION))
const CropSyst::Crop_interfaced &crop
#else
clsCrop &crop
#endif
,clsSimulation &Simulation
,WeatherStateDailyClass &Weather)
{
    const double Nitrification_NO3_NH4_Ratio = 8.0;         //NO3-N / NH4-N = 27 NO3/NH4
    int doy = Simulation.pTimeState->getToday().get_DOY();
    const int Number_Of_Layers = SoilProfileRef.NumberOfLayers();
    #ifndef CROPSYST_VERSION
    bool Crop_Emerged = Simulation.pSimulationRotation->getCropEmerged();
    double Canopy_Cover(0.0);
    double Crop_Height(0.0);
    if (Crop_Emerged)
    {
        #ifdef CROPSYST_PROPER_CROP
        Canopy_Cover = crop.get_fract_canopy_cover();
           //RLN This is cover_actual.get_global_solar_rad_intercepted_total_canopy();
           //141005 I need to eventually rename this function.
        Crop_Height = crop.get_plant_height_m();                                 //140511
        #else
        Canopy_Cover = crop.pCropState->Fraction_Solar_Rad_Intercepted_Total_Canopy;
        Crop_Height = crop.pCropState->Crop_Height;
        #endif
    } else {
        Canopy_Cover = 0;
        Crop_Height = 0;
    }
    #endif
    double Profile_N_Nitrified = 0;
    double Profile_N_Denitrified = 0;
    double Profile_N2O_Loss = 0;
    double Nitrification_Constant = 
            Simulation.pSimConstants->Nitrification_Constant / Hours_Per_Day;
    double Potential_Denitrification_Constant = 
            Simulation.pSimConstants->Potential_Denitrification / Hours_Per_Day;        //kg N/kg Soil/hour
    double Daily_Layer_Nitrification[30];
    double Daily_Layer_Denitrification[30];
    double Daily_Layer_N2O_Loss_From_Denitrification[30];
    double Daily_Layer_N2O_Loss_From_Nitrification[30];
    double Hourly_Soil_Temperature_Function[30][25];
    for (int L = 1; L <= Number_Of_Layers; L++) {
        double Layer_CO2_Loss = SoilStateRef.Layer_Total_CO2_Loss[L];         //XXX OJO Units??? Assume kg CO2-C/m2/day
        double Bulk_Density = SoilProfileRef.get_bulk_density_g_cm3(L);
        double Layer_Thickness = SoilProfileRef.get_thickness_m(L);
        double Soil_Mass_Dry = Bulk_Density * 1000.0 * Layer_Thickness; //(kg/m2)
        double Saturation_Water_Content = SoilProfileRef.get_saturation_water_content_volumetric(L,0.0);   //Saturation_Water_Content[L];
        //FMS Apr 9, 2015 double Current_Water_Content = SoilStateRef.get_liquid_water_content_volumetric(L);
        //FMS Apr 9, 2015 double Water_Filled_Porosity = Current_Water_Content / Saturation_Water_Content;
        double Field_Capacity = SoilProfileRef.get_field_capacity_volumetric(L);
        double Soil_pH = SoilProfileRef.get_pH(L);
        double pH_Function = AbioticFunctionsRef.pHFunction(Soil_pH, Simulation);
        double Layer_Nitrate_N_Mass = SoilStateRef.Layer_Nitrate_N_Mass[L];
        double Layer_Ammonium_N_Mass = SoilStateRef.Layer_Ammonium_N_Mass[L];
        double Nitrate_Concentration_Dry_Soil = Layer_Nitrate_N_Mass / Soil_Mass_Dry;
        //FMS Apr 9, 2015 double Nitrification_Moisture_Function = AbioticFunctionsRef.MoistureFunction(0, Water_Filled_Porosity);
        double Sum_Hourly_Temperature_Function = 0;
        Daily_Layer_Nitrification[L] = 0;
        Daily_Layer_Denitrification[L] = 0;
        Daily_Layer_N2O_Loss_From_Denitrification[L] = 0;
        for (int hour = 0; hour <= 23; hour++) {
            //Determine soil temperature function for each soil layer
            double Soil_Temperature = SoilStateRef.Soil_Temperature[hour][L];
            Hourly_Soil_Temperature_Function[L][hour] = 
                AbioticFunctionsRef.TemperatureFunction(Soil_Temperature);
            Sum_Hourly_Temperature_Function += 
                Hourly_Soil_Temperature_Function[L][hour];
        }
        for (int hour = 0; hour <= 23; hour++) {
            //New lines FMS Apr 9, 2015
            double Previous_Time_Step_Soil_Layer_Vol_Water_Content(0);
            if (hour == 0)
                Previous_Time_Step_Soil_Layer_Vol_Water_Content = SoilStateRef.Yesterday_WC[L];
            else
                Previous_Time_Step_Soil_Layer_Vol_Water_Content = SoilStateRef.Today_Hourly_WC[L][hour-1];
            Previous_Time_Step_Soil_Layer_Vol_Water_Content = CORN::must_be_greater_or_equal_to(1.e-8,Previous_Time_Step_Soil_Layer_Vol_Water_Content);
            double Current_Water_Content = SoilStateRef.Today_Hourly_WC[L][hour];
            double Water_Filled_Porosity = Current_Water_Content / Saturation_Water_Content;
            double Nitrification_Moisture_Function = AbioticFunctionsRef.MoistureFunction(0.0, Water_Filled_Porosity);
            double Potential_Denitrification_Rate = PotentialDenitrification(Previous_Time_Step_Soil_Layer_Vol_Water_Content / Saturation_Water_Content);
            //NITRIFICATION
            if (Layer_Ammonium_N_Mass > 0) {
                double Layer_N_Nitrified(0.0);
                if ((Layer_Nitrate_N_Mass / Layer_Ammonium_N_Mass) 
                    < Nitrification_NO3_NH4_Ratio
                    )
                    Layer_N_Nitrified = 
                        (Layer_Ammonium_N_Mass - Layer_Nitrate_N_Mass / Nitrification_NO3_NH4_Ratio) 
                        * (1.0 - exp(-Nitrification_Constant * pH_Function
                                     * Hourly_Soil_Temperature_Function[L][hour])
                          ) 
                        * Nitrification_Moisture_Function;
                else Layer_N_Nitrified = 0;
                //Check that nitrification is limited to existing ammonium 
                //N mass and update local ammonium N mass
                if (Layer_N_Nitrified > Layer_Ammonium_N_Mass) {
                    Layer_N_Nitrified = Layer_Ammonium_N_Mass;
                    Layer_Ammonium_N_Mass = 0;
                } else {
                    Layer_Ammonium_N_Mass -= Layer_N_Nitrified;
                }
                Daily_Layer_Nitrification[L] += Layer_N_Nitrified;
                //Determine N2O losses associated with nitrification
                double N2O_In_Nitrification_Temperature_Function = 
                        1.197 - 0.0439 * Hourly_Soil_Temperature_Function[L][hour];
                if (N2O_In_Nitrification_Temperature_Function < 0.1) 
                    N2O_In_Nitrification_Temperature_Function = 0.1;
                else if (N2O_In_Nitrification_Temperature_Function > 1) 
                    N2O_In_Nitrification_Temperature_Function = 1;
                double Layer_N2O_Loss_From_Nitrification = 
                        Layer_N_Nitrified 
                        * 0.009 
                        * Nitrification_Moisture_Function 
                        * N2O_In_Nitrification_Temperature_Function;
                Daily_Layer_N2O_Loss_From_Nitrification[L] += 
                        Layer_N2O_Loss_From_Nitrification;
            }

            //End Nitrification
            //DENITRIFICATION
            if (Layer_Nitrate_N_Mass > 0) {
                 double Denitrification_Nitrate_Function = 
                         NitrateResponseFunction(Simulation.pSimConstants->Denitrification_Half_Rate, 
                                                 Nitrate_Concentration_Dry_Soil);
                 double Denitrification_Moisture_Function =
                         AbioticFunctionsRef.DenitrificationMoistureFunction(Field_Capacity, 
                                                                             Saturation_Water_Content, 
                                                                             Water_Filled_Porosity, 
                                                                             false);
                 if (Denitrification_Moisture_Function > 0) {
                    double Respiration_Response_Function(0.0);
                    if (Sum_Hourly_Temperature_Function > 0) {
                        double Hourly_Respiration_Weighting_Factor = 
                            Hourly_Soil_Temperature_Function[L][hour] / Sum_Hourly_Temperature_Function;
                        double CO2_Loss_Per_Unit_Soil_Mass =
                            (Layer_CO2_Loss / Soil_Mass_Dry) * Hourly_Respiration_Weighting_Factor;         //Conversion kg CO2-C / Kg Soil/day to kg CO2-C / Kg Soil/hour
                        Respiration_Response_Function =
                            RespirationFunction(CO2_Loss_Per_Unit_Soil_Mass);
                    }
                    else Respiration_Response_Function = 0;
                    double Nitrate_Response_Function = Denitrification_Nitrate_Function; //FMS Oct 10, 2014
                    double Denitrification_Factor = 
                            Minimum(Denitrification_Nitrate_Function, Respiration_Response_Function, 9999)
                            * Denitrification_Moisture_Function;                  //FMS Mar 30, 2015
                    double Layer_N_Denitrified = 
                            Potential_Denitrification_Rate /*150520 Constant*/
                            * Soil_Mass_Dry 
                            * Denitrification_Factor;        //kgN/m2/hour FMS Mar, 31, 2015
                    //Check to ensure that denitrification is limited to 
                    //existing nitrate N mass and update local nitrate N mass
                    if (Layer_N_Denitrified > Layer_Nitrate_N_Mass) {
                        Layer_N_Denitrified = Layer_Nitrate_N_Mass;
                        Layer_Nitrate_N_Mass = 0;
                    } else {
                        Layer_Nitrate_N_Mass -= Layer_N_Denitrified;
                    }
                    //Determine N2 to N2O ratio
                    double N2_To_N2O_Ratio_Moisture_Function =
                            AbioticFunctionsRef.DenitrificationMoistureFunction(Field_Capacity,
                                                                                Saturation_Water_Content,
                                                                                Water_Filled_Porosity,
                                                                                true);
                    double N2_To_N2O_Nitrate_Function = N2N2ONitrate(Nitrate_Concentration_Dry_Soil);
                    double N2_To_N2O_Respiration_Function = N2N2OResp(Layer_CO2_Loss);
                    double N2_N2O_Ratio = Minimum(N2_To_N2O_Nitrate_Function, 
                                                  N2_To_N2O_Respiration_Function, 
                                                  9999)
                                          * N2_To_N2O_Ratio_Moisture_Function;   //FMS Apr 9, 2015
                    double N2O_Fraction_Of_Denitrification = 1.0 / (1.0 + N2_N2O_Ratio);
                    double Layer_N2O_Loss = Layer_N_Denitrified * N2O_Fraction_Of_Denitrification;
                    Daily_Layer_Denitrification[L] += Layer_N_Denitrified;
                    Daily_Layer_N2O_Loss_From_Denitrification[L] += Layer_N2O_Loss;
                 } 
            }
            //End Denitrification
        }//hour
    }//L
    //Ammonia volatilization
    AmmoniaVolatilization(0, 0, 0, Crop_Height, Canopy_Cover, Simulation, Weather);
    //Update pools after transformation and before residue mineralization
    for (int L = 1; L <= Number_Of_Layers; L++) {
        double Layer_Ammonium_N_Mass = 
                SoilStateRef.Layer_Ammonium_N_Mass[L] - Daily_Layer_Nitrification[L];
        if (Layer_Ammonium_N_Mass < 0) {
            Daily_Layer_Nitrification[L] += Layer_Ammonium_N_Mass;
            Layer_Ammonium_N_Mass = 0;
        }
        SoilStateRef.Layer_Ammonium_N_Mass[L] = Layer_Ammonium_N_Mass;
        assert(SoilStateRef.Layer_Ammonium_N_Mass[L] >= 0.0);
        double Layer_Nitrate_N_Mass = SoilStateRef.Layer_Nitrate_N_Mass[L]
                               + Daily_Layer_Nitrification[L] 
                               - Daily_Layer_Denitrification[L];
        if (Layer_Nitrate_N_Mass < 0) {
            Daily_Layer_Denitrification[L] += Layer_Nitrate_N_Mass;
            Layer_Nitrate_N_Mass = 0;
        }
        SoilStateRef.Layer_Nitrate_N_Mass[L] = Layer_Nitrate_N_Mass;
        assert(SoilStateRef.Layer_Nitrate_N_Mass[L] >= 0.0);
        SoilStateRef.Layer_Nitrified_N_Mass[L] += Daily_Layer_Nitrification[L];
        assert(SoilStateRef.Layer_Nitrified_N_Mass[L] >= 0.0);
        SoilStateRef.Layer_Denitrified_N_Mass[L] += Daily_Layer_Denitrification[L];
        assert(SoilStateRef.Layer_Denitrified_N_Mass[L] >= 0.0);
        //Register soil profile N transformations
        Profile_N_Nitrified += Daily_Layer_Nitrification[L];
        Profile_N_Denitrified += Daily_Layer_Denitrification[L];
        Profile_N2O_Loss += Daily_Layer_N2O_Loss_From_Denitrification[L];
    }
    #ifndef CROPSYST_VERSION
    SoilStateRef.Profile_Nitrification = Profile_N_Nitrified;
    SoilStateRef.Profile_Denitrification = Profile_N_Denitrified;
    #endif
    if (doy == 1) {
        SoilStateRef.Cumulative_Profile_Nitrification = Profile_N_Nitrified;
        SoilStateRef.Cumulative_Profile_Denitrification = Profile_N_Denitrified;
        SoilStateRef.Cumulative_Profile_N2O_Loss = Profile_N2O_Loss;
    } else {
        SoilStateRef.Cumulative_Profile_Nitrification += Profile_N_Nitrified;
        SoilStateRef.Cumulative_Profile_Denitrification += Profile_N_Denitrified;
        SoilStateRef.Cumulative_Profile_N2O_Loss += Profile_N2O_Loss;
    }
    SoilStateRef.Daily_Profile_N2O_Loss = Profile_N2O_Loss;
}
//______________________________________________________________________________
void SoilNitrogenTransformationClass::AmmoniaVolatilization(double New_TAN_Mass, 
  double New_Water_Volume, double pH_Of_Applied_Material, double Crop_Height, 
  double Canopy_Cover, clsSimulation &Simulation, WeatherStateDailyClass &Weather)
{
    //'New_TAN_Mass must be in kgTAN/m2 ground area and New_Water_Volume in m3H2O/m2 ground area
    int doy = Simulation.pTimeState->getToday().get_DOY();
    double Ammonia_N_Mass_Available_For_Volatilization =
        #ifdef CROPSYST_VERSION
        0.0;
        assert(false); //140604 need to provide this (however this entire class may be replaced)
        #else
        SoilStateRef.Ammonia_Available_For_Volatilization;
        #endif
    double Daily_NH3_Volatilization(0.0);
    if (Ammonia_N_Mass_Available_For_Volatilization > 0) {
        double Time_Step = 3600;   // 's
        //'OJO: Volatilization: Bring in input parameter
        double Atmospheric_Pressure = 100; // 'kPa
        //'Only NH3 volatilization from top layer is considered
        //'pH = SoilProfileRef.SoilpH(1)
        double Soil_Bulk_Density = SoilProfileRef.get_bulk_density_g_cm3(1) * 1000;       // 'Convert to kg/m3
        double Volumetric_Water_Content = SoilStateRef.get_liquid_water_content_volumetric(1);
        //'For first day of ammonia/ammonium application, pH is that of the applied material 
        //in the case of manure. For ammonium/urea
        //'fertilization, pH of applied material is zero (soil pH is used) and the fertilizer 
        //is only mixed with the
        //'top 2 cms of soil on the first day.  For all first day applications, 
        //no absorption is allowed (Kd = 0).
        double Kd(0),TAN_Mass(0),Water_Volume(0),pH(7);
        if (New_TAN_Mass > 0) {
            Kd = 0;
            TAN_Mass = New_TAN_Mass;        //  'm3 H2O / m2 ground area
            if (CORN::is_approximately<double>(pH_Of_Applied_Material,0.0,1e-12)) {    
                // Then 'This corresponds to broadcast application of ammonium/urea fertilizer
                pH = SoilProfileRef.get_pH(1);
                Water_Volume = (Volumetric_Water_Content + Kd * Soil_Bulk_Density / WaterDensity_kg_m3) 
                               * 0.02;
            } else { //This corresponds to broadcast application of manure ammonia
                pH = pH_Of_Applied_Material;
                Water_Volume = New_Water_Volume;
            }
        } else {
            pH = SoilProfileRef.get_pH(1);
            Kd = 5.6;       // 'Partitioning coefficient for ammonium (kg H2O/kg Soil)
            double Soil_Thickness = SoilProfileRef.get_thickness_m(1);
            //'m3 H2O / m2 ground area
            Water_Volume = (Volumetric_Water_Content + Kd * Soil_Bulk_Density / WaterDensity_kg_m3) 
                           * Soil_Thickness;
            TAN_Mass = SoilStateRef.Layer_Ammonium_N_Mass[1];
        }
        double Wind_Speed_At_10_Meters = Weather.getDailyWindSpeedAt10m();
        #ifndef CROPSYST_VERSION
        // This entire class will probably be replaced
        bool Residue_Present(false);
        if ((Simulation.pSimulationRotation->getCropStubblePresent() == true)
            || (Simulation.pSimulationRotation->getSurfaceResiduePresent() == true))
            Residue_Present = true;
        else
        #endif
            Residue_Present = false;
        //'mol/m2/s
        double Turbulent_Transfer_Coefficient = 
                TurbulentTransferCoefficient(Crop_Height, 
                                             Canopy_Cover, 
                                             Residue_Present, 
                                             Wind_Speed_At_10_Meters);
        double Daily_NH3_Volatilization = 0;
        for (int hour = 0; hour < 24; hour++) {
            double Hourly_Temperature = Weather.getHourlyTemperature(hour);
            double pK = -(-0.09018 - 2729.92 / (Hourly_Temperature + 273.1));
            double Henrys_Coefficient = pow(10.0, (1477.7 / (273.1 + Hourly_Temperature) - 1.69));
            //'Henry's Constant in mol/m3/Pa
            double Henrys_Constant = Henrys_Coefficient / (8.31 * (273.1 + Hourly_Temperature));
            //' Convert Henry's Constant to (L Pa)/mol
            Henrys_Constant = (1.0 / Henrys_Constant) * 1000.0;
            //'OJO: This definition might be different for the first day after 
            //NH4/NH3 application before entering the soil
            //'TAN_Mass is in kg/m2 of ground area and Water_Volume is in m3H2O / m2 ground area
            double TAN_Concentration = TAN_Mass / Water_Volume;        // 'kg/m3 or g/l
            double NH3_Concentration = TAN_Concentration / (1.0 + pow(10.0,(pK - pH)));   // 'kg/m3 or g/l
            NH3_Concentration /= Grams_Per_Mol_NH3;  //mol/l
            double NH3_Gas_Partial_Pressure = Henrys_Constant * NH3_Concentration;  // 'Pa
            double NH3_Mol_Fraction = NH3_Gas_Partial_Pressure / (Atmospheric_Pressure * 1000.0);  // 'Pa/Pa
            double NH3_Volatilization = NH3_Mol_Fraction * Turbulent_Transfer_Coefficient;  // 'mol/m2/s
            NH3_Volatilization *= Grams_Per_Mol_NH3 * Time_Step / 1000.0;  // 'kg/m2
            if (NH3_Volatilization <= TAN_Mass) {
                TAN_Mass -= NH3_Volatilization;
            } else {
                NH3_Volatilization = TAN_Mass;
                TAN_Mass = 0;
            }
            Daily_NH3_Volatilization += NH3_Volatilization;
        }//Next Hour
        if (Daily_NH3_Volatilization > Ammonia_N_Mass_Available_For_Volatilization) {
            Daily_NH3_Volatilization = Ammonia_N_Mass_Available_For_Volatilization;
            Ammonia_N_Mass_Available_For_Volatilization = 0;
        } else {
            Ammonia_N_Mass_Available_For_Volatilization -= Daily_NH3_Volatilization;
        }
        #ifndef CROPSYST_VERSION
        SoilStateRef.Ammonia_Available_For_Volatilization = 
            Ammonia_N_Mass_Available_For_Volatilization;
        #endif
        //'OJO: Volatilization: This is a problem if this pool is updated again today!!!!!
        SoilStateRef.Layer_Ammonium_N_Mass[1] -= Daily_NH3_Volatilization;
    } 
    #ifndef CROPSYST_VERSION
    SoilStateRef.Ammonia_N_Mass_Volatilization += Daily_NH3_Volatilization;
    if (doy == 1) SoilStateRef.Cumulative_Ammonia_N_Mass_Volatilization = Daily_NH3_Volatilization;
    else SoilStateRef.Cumulative_Ammonia_N_Mass_Volatilization += Daily_NH3_Volatilization;
    #endif
    //'This is needed to account for days where the volatilization procedure is invoked more than once
    //Last_DOY = DOY;
}
//______________________________________________________________________________
double SoilNitrogenTransformationClass::TurbulentTransferCoefficient(double Crop_Height, 
  double Canopy_Cover, bool Residue_Present,double Wind_Speed_At_10_Meters)
{
    double Wind_Speed_For_Volatilization_Without_Crop;
    double Wind_Speed_For_Volatilization_With_Fully_Developed_Crop;
    double Wind_Speed_For_Volatilization;
    double Wind_Speed_At_Top_Of_Crop;
    double Crop_Friction_Velocity;
    double Residue_Friction_Velocity;
    double Soil_Friction_Velocity;
    double Full_Sheltering_Canopy_Cover;
    double Available_Sheltering_Canopy_Cover;
    double Residue_Roughness_Height;
    double Crop_d,Crop_Zm;
    double Residue_d,Residue_Zm;
    double Soil_d,Soil_Zm,Soil_Zv;
    double Turbulent_Transfer_Coefficient;
    const double Attenuation_Coefficient = 2;//#
    const double Soil_Roughness_Height = 0.05;
    Soil_d = 0.65 * Soil_Roughness_Height;
    Soil_Zm = 0.1 * Soil_Roughness_Height;
    Soil_Zv = 0.2 * Soil_Zm;
    if (Residue_Present == true) {
        Residue_Roughness_Height = 0.3;
        Residue_d = 0.65 * Residue_Roughness_Height;
        Residue_Zm = 0.1 * Residue_Roughness_Height;
        Residue_Friction_Velocity = 0.4 
                                    * Wind_Speed_At_10_Meters 
                                    / log((10.0 - Residue_d + Residue_Zm) / Residue_Zm);
        Wind_Speed_For_Volatilization_Without_Crop = (Residue_Friction_Velocity / 0.4)
            * log((Soil_Roughness_Height - Soil_d + Soil_Zm) / Soil_Zm);
    } else {
        Soil_Friction_Velocity = 0.4 
                                 * Wind_Speed_At_10_Meters 
                                 / log((10.0 - Soil_d + Soil_Zm) / Soil_Zm);
        Wind_Speed_For_Volatilization_Without_Crop = (Soil_Friction_Velocity / 0.4)
            * log((Soil_Roughness_Height - Soil_d + Soil_Zm) / Soil_Zm);
    }
    if (Crop_Height > 0) {    // Then 'Crop exist
        Crop_d = 0.65 * Crop_Height;
        Crop_Zm = 0.1 * Crop_Height;
        Crop_Friction_Velocity = 0.4 
                                 * Wind_Speed_At_10_Meters 
                                 / log((10.0 - Crop_d + Crop_Zm) / Crop_Zm);
        Wind_Speed_At_Top_Of_Crop = (Crop_Friction_Velocity / 0.4) 
                                    * log((Crop_Height - Crop_d + Crop_Zm) / Crop_Zm);
        Wind_Speed_For_Volatilization_With_Fully_Developed_Crop = 
                Wind_Speed_At_Top_Of_Crop
                * exp(Attenuation_Coefficient * (Soil_Roughness_Height / Crop_Height - 1.0));
        Full_Sheltering_Canopy_Cover = 0.9;
        if (Canopy_Cover >= Full_Sheltering_Canopy_Cover)
            Available_Sheltering_Canopy_Cover = Full_Sheltering_Canopy_Cover;
        else Available_Sheltering_Canopy_Cover = Canopy_Cover;
        Wind_Speed_For_Volatilization = 
                (Wind_Speed_For_Volatilization_Without_Crop 
                 - Wind_Speed_For_Volatilization_With_Fully_Developed_Crop
                )
                * (1.0 - Available_Sheltering_Canopy_Cover / Full_Sheltering_Canopy_Cover) 
                + Wind_Speed_For_Volatilization_With_Fully_Developed_Crop;
    }
    else Wind_Speed_For_Volatilization = Wind_Speed_For_Volatilization_Without_Crop;
    //'mol/m2/s
    Turbulent_Transfer_Coefficient = 0.4 * 0.4 * 41.4 * Wind_Speed_For_Volatilization
        / (log((Soil_Roughness_Height - Soil_d + Soil_Zm) / Soil_Zm)
        * log((Soil_Roughness_Height - Soil_d + Soil_Zv) / Soil_Zv));
    return Turbulent_Transfer_Coefficient;
}
//_FMS Mar 27, 2015__ __________________________________________________________
double SoilNitrogenTransformationClass::PotentialDenitrification(double WFP)
{
    double pot_den(0);
    if (WFP < 0.1)
        pot_den = 5.;                                                            //(mgN/hr)
    else
        pot_den = 0.75 + (0.4622 * WFP * WFP - 0.0893 * WFP + 0.0523);           //(mgN/hr)
    return pot_den / 1.e6;                                                       //mgN to kg N ' FMs Mar 31, 2015
}
//______________________________________________________________________________
#endif

