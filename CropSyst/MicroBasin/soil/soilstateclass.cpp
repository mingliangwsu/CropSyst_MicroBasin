﻿#include "soilstateclass.h"
#include "util/pubtools.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "corn/OS/file_system_engine.h"                                          //160617LML
#define SOIL_PARAMETER_NUMBERS_FOR_ARRAY 30

//______________________________________________________________________________
#ifdef MBVB_SOIL
SoilStateClass::SoilStateClass
(AllControlClass &_ControlRef
,SoilProfileClass &_SoilProfileRef
,CropSyst::Pond &_pond
#ifdef CROPSYST_VERSION
,Soil_chemicals_profile *_chemical
#endif
,InitialSoilStateClass &initSoilStateRef_                                        //160317LML
)
:ControlRef(_ControlRef)
,SoilProfileRef(_SoilProfileRef)
,pond(_pond)
,hydrology_cascade   (0)                                                         //160606RLN
,hydrology_FD        (0)                                                         //160606RLN
,hydrology           (0)                                                         //160606RLN
#ifdef CROPSYST_VERSION
,chemicals_optional(_chemical)                                                   //151212RLN
#endif
,initSoilStateRef(initSoilStateRef_)                                             //160317LML
//,growth_season_N_leached (0)                                                     //170207LML
,growth_season_N_uptake  (0)                                                     //170417LML
//,growth_season_N_runon(0)                                                        //170417LML
//,growth_season_N_runoff(0)                                                       //170417LML
{
   if (_ControlRef.infiltration_model_labeled.get() == FINITE_DIFFERENCE_INFILTRATION) //160606RLN
   {
      hydrology = hydrology_FD =new Soil_hydrology_finite_difference
         (_SoilProfileRef
         ,_SoilProfileRef //hydraulic properies
         ,_SoilProfileRef );
   } else
   {
      hydrology = hydrology_cascade = new Soil_hydrology_cascade
         (_SoilProfileRef  // layers
         ,_SoilProfileRef  // hydraulic properies
         ,_SoilProfileRef );// soil structure
   }
    num_layers = SoilProfileRef.NumberOfLayers();
    Surface_Soil_Cover = SSC_Default;                                            //140902LML
    initMem();
}
//______________________________________________________________________________
void SoilStateClass::ClearStateVariables()
{
    //int YC,d;
    //Hourly_Ponded_Water_m = 0;
    #ifndef CROPSYST_VERSION
    Ammonia_Available_For_Volatilization = 0;
    #endif
    Cumulative_Runoff = 0;
    Surface_Water_Store = 0.0;
    //Sheet_Of_Water_Available_To_Infiltrate_m = 0.0;
	#ifndef CROPSYST_VERSION
    //for (h = 0; h <= 24; h++) {
        //Hourly_Canopy_Solar_Radiation_Interception_Fraction[h] = 0;
        //Hourly_Standing_Stubble_Solar_Radiation_Interception_Fraction[h] = 0;
        //Hourly_Surface_Residue_Solar_Radiation_Interception_Fraction[h] = 0;
    //}
    #endif
    #ifndef CROPSYST_VERSION
    for (int layer = 0; layer <= num_layers; layer++) {
        Soil_Disturbance_Rating[layer] = 0;
        Tillage_Decomposition_Adjustment_Factor[layer] = 1;
    }
    #endif
    #ifdef MBVB_SOIL_TEMPERATURE
     for (int h = 0; h <= 24; h++) {
        for (int layer = 0; layer <= num_layers; layer++) {
            Soil_Temperature[h][layer] = 0;
        }
    }
    #endif
    for (int layer = 0; layer <= num_layers; layer++) {
        Ice_Content[layer] = 0;
        #if (!defined (CROPSYST_HYDROLOGY) || defined(MBVB_FD))
        Water_Potential[layer] = 0;
        Water_Content[layer] = 0;
        #endif
        #ifndef CROPSYST_VERSION
        Layer_Soil_Water_Uptake[layer] = 0;
        Layer_Potential_Nitrate_N_Uptake[layer] = 0;
        Layer_Actual_Nitrate_N_Uptake[layer] = 0;
        Layer_Potential_Ammonium_N_Uptake[layer] = 0;
        Layer_Actual_Ammonium_N_Uptake[layer] = 0;
        Layer_Potential_Phosphorus_Uptake[layer] = 0;
        Layer_Actual_Phosphorus_Uptake[layer] = 0;
        #endif
        #ifndef CROPSYST_VERSION
        Layer_Nitrate_N_Mass[layer] = 0;
        Layer_Ammonium_N_Mass[layer] = 0;
        Layer_Nitrate_N_Conc[layer] = 0;
        Layer_Ammonium_N_Conc[layer] = 0;
        Layer_Phosphorus_Mass[layer] = 0;
        Layer_Phosphorus_Conc[layer] = 0;
        #endif
        #ifndef CROPSYST_VERSION
        //150522 Layer_Organic_Residue_Mass[layer] = 0;
        Layer_Organic_Matter_Content[layer] = 0;
        #endif
        #ifndef CROPSYST_VERSION
        Layer_Nitrified_N_Mass[layer] = 0;
        Layer_Denitrified_N_Mass[layer] = 0;
        Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = 0;
        Layer_Mineralized_N_Mass_From_Organic_Residues[layer] = 0;
        Layer_Nitrogen_Mass_In_Organic_Matter[layer] = 0;
        Layer_Carbon_Mass_In_Organic_Matter[layer] = 0;
        //Layer_Carbon_Mass_In_Organic_Residue[layer] = 0;
        //Layer_Nitrogen_Mass_In_Organic_Residue[layer] = 0;
        //Layer_Nitrogen_Mass_Immobilized[layer] = 0;
        //Layer_Carbon_Mass_In_Organic_Residue_Plus_Microbes[layer] = 0;
        Layer_Total_CO2_Loss[layer] = 0;
        Layer_SOM_CO2_Loss[layer] = 0;
        Layer_Residue_CO2_Loss[layer] = 0;
        Layer_SOM_C_Balance[layer] = 0;
        Layer_SOM_N_Balance[layer] = 0;
        Layer_Residue_C_Balance[layer] = 0;
        Layer_Residue_N_Balance[layer] = 0;
        Layer_Carbon_Transfer_From_Residue_To_SOM[layer] = 0;
        Layer_Nitrogen_Transfer_From_Residue_To_SOM[layer] = 0;
        #endif
    }
    Drainage = 0;
    Cumulative_Drainage = 0;
    Cumulative_Drainage_m = 0;                                                   //150921LML
    Non_Intercepted_Precipitation_mm = 0;
	#ifndef CROPSYST_VERSION
    Profile_Soil_Water_Uptake = 0;
    #endif
    Profile_Soil_Water_Depletion = 0;
    #ifndef CROPSYST_VERSION
    Standing_Stubble_Fraction_Solar_Radiation_Interception = 0;
    Surface_Residue_Fraction_Solar_Radiation_Interception = 0; //'- n//ot used!
    #endif
    #ifndef CROPSYST_VERSION
    Ammonia_N_Mass_Volatilization = 0;
    Total_Potential_Phosphorus_Uptake = 0;
    Total_Potential_Nitrate_N_Uptake = 0;
    Total_Potential_Ammonium_N_Uptake = 0;
    Total_Actual_Phosphorus_Uptake = 0;
    Total_Actual_Nitrogen_Uptake = 0;
    Total_Actual_Nitrate_N_Uptake = 0;
    Total_Actual_Ammonium_N_Uptake = 0;
    Total_Nitrate_N_Mass = 0;
    Total_Ammonium_N_Mass = 0;
    Total_Phosphorus_Mass = 0;
    Profile_OM_Mineralization = 0;
    Profile_Nitrification = 0;
    Profile_Denitrification = 0;
    Profile_Residue_Mineralization = 0;
    Profile_Ammonium_Immobilization = 0;
    Profile_Nitrate_Immobilization = 0;
    Profile_Carbon_Transferred_From_Residue_To_SOM = 0;
    Profile_Nitrogen_Transferred_From_Residue_To_SOM = 0;
    Profile_SOM_Carbon_Decomposed = 0;
    Profile_SOM_Nitrogen_Decomposed = 0;
    Profile_SOM_Carbon_Lost_As_CO2 = 0;
    Profile_Residue_Carbon_Lost_As_CO2 = 0;
    Cumulative_Profile_OM_Mineralization = 0;
    Cumulative_Profile_Residue_Mineralization = 0;
    Cumulative_Profile_Nitrification = 0;
    Cumulative_Profile_Denitrification = 0;
    Cumulative_Profile_N2O_Loss = 0;
    Cumulative_Profile_Nitrogen_Immobilization = 0;
    Cumulative_Profile_Residue_Carbon_Lost_As_CO2 = 0;
    Cumulative_Profile_SOM_Carbon_Lost_As_CO2 = 0;
    Cumulative_Ammonia_N_Mass_Volatilization = 0;
    Profile_SOM_Carbon_Mass = 0;
    Profile_SOM_Nitrogen_Mass = 0;
    Profile_Residue_Carbon_Mass = 0;
    Profile_Residue_Nitrogen_Mass = 0;
    Profile_SOM_Carbon_Mass_Balance = 0;
    Profile_SOM_Nitrogen_Mass_Balance = 0;
    Profile_Microbial_Carbon_Mass = 0;
    Profile_Labile_Carbon_Mass = 0;
    Profile_Metastable_Carbon_Mass = 0;
    Profile_Passive_Carbon_Mass = 0;
    Cumulative_Nitrate_N_Fertigation = 0;
    Cumulative_Ammonium_N_Fertigation = 0;
    Cumulative_Ammonium_N_Fertilization = 0;
    Cumulative_Nitrate_N_Fertilization = 0;
    Cumulative_Organic_N_Fertilization = 0;
    Cumulative_Phosphorus_Leaching = 0;
    #endif
#ifndef CROPSYST_CHEMICAL_TRANSPORT
    Cumulative_Ammonium_Leaching = 0;
#endif
    Cumulative_Nitrate_Leaching = 0;
    Cumulative_Phosphorus_Leaching = 0;
    Cumulative_Actual_Soil_Evaporation_m = 0.0;
    Cumulative_Actual_Crop_Transpiration_m = 0.0;
    //SheetOfWaterAvailableToInfiltrate_mm = 0;
}
//______________________________________________________________________________
void SoilStateClass::initMem()
{
    const int maxlayers = SoilProfileRef.NumberOfLayers() + 5;                   //140607LML
    #if (!defined (CROPSYST_HYDROLOGY) || defined(MBVB_FD))
    Water_Content.resize(maxlayers,0);
    #endif
    Ice_Content.resize(maxlayers,0);
    Hydro_Standard_Slope.resize(maxlayers,0);               
    #ifndef CROPSYST_CHEMICAL_TRANSPORT
    Layer_Nitrate_N_Conc.resize(maxlayers,0);               
    Layer_Ammonium_N_Conc.resize(maxlayers,0);
    Layer_Phosphorus_Conc.resize(maxlayers,0);
    #endif
//140305 Claudio decided to removed this     Mac_Po_Fac = alloc_1d_array<double>(maxlayers,"SoilStateClass::MacPoFac");
    comb_Share_Flow.resize(maxlayers);
    for (int i = 0; i < maxlayers; i++) comb_Share_Flow[i].resize(9);
    #ifdef MBVB_SOIL_TEMPERATURE
    Avg_Daily_Soil_T.resize(maxlayers,0);                    
    Soil_Temperature.resize(25);
    for (int i = 0; i < 25; i++) Soil_Temperature[i].resize(maxlayers);
    #endif
    #ifndef CROPSYST_VERSION
    Water_Flow.resize(maxlayers,0);
    Layer_Organic_Matter_Content.resize(maxlayers,0);
    Soil_Disturbance_Rating.resize(maxlayers,0);       
    Tillage_Decomposition_Adjustment_Factor.resize(maxlayers,0);         
    #endif                                                             
    #ifndef CROPSYST_VERSION
    //150811RLN these are never used:
    Denitrification_Event.resize(maxlayers,0);                         
    Denitrification_Event_Second_Day.resize(maxlayers,0);              
    #endif
    #ifndef CROPSYST_VERSION
    Initial_C_Fraction_To_Active_Labile_SOM.resize(maxlayers,0);       
    Initial_C_Fraction_To_Active_Metastable_SOM.resize(maxlayers,0);   
    Initial_C_Fraction_To_Microbial_Biomass.resize(maxlayers,0);       
    Initial_C_Fraction_To_Passive_SOM.resize(maxlayers,0);             
    Initial_Soil_Residue_Mass.resize(maxlayers,0);                     
    Layer_Actual_Ammonium_N_Uptake.resize(maxlayers,0);                
    Layer_Actual_Nitrate_N_Uptake.resize(maxlayers,0);                 
    Layer_Actual_Phosphorus_Uptake.resize(maxlayers,0);                
    #endif
    #ifdef MBVB_FD
    //140508 RLN moved here
    Old_Lower_Water_Content.resize(maxlayers,0); 
    Old_Upper_Water_Content.resize(maxlayers,0); 
    #endif
    #ifndef CROPSYST_VERSION
    Initial_NO3.resize(maxlayers,0);
    Initial_NH4.resize(maxlayers,0);
    #else
    Layer_Ammonium_N_Mass.resize(maxlayers,0);
    Layer_Nitrate_N_Mass.resize(maxlayers,0);
    #endif
    Layer_Phosphorus_Mass.resize(maxlayers,0);
    #ifndef CROPSYST_VERSION
    Layer_Carbon_Mass_In_Organic_Matter.resize(maxlayers,0);            
    Layer_Carbon_Transfer_From_Residue_To_SOM.resize(maxlayers,0);      
    Layer_Denitrified_N_Mass.resize(maxlayers,0);
    Layer_Mineralized_N_Mass_From_Organic_Matter.resize(maxlayers,0);
    Layer_Mineralized_N_Mass_From_Organic_Residues.resize(maxlayers,0); 
    Layer_Nitrified_N_Mass.resize(maxlayers,0);
    Layer_Nitrogen_Mass_In_Organic_Matter.resize(maxlayers,0);
    Layer_Nitrogen_Transfer_From_Residue_To_SOM.resize(maxlayers,0); 
    //150522 Layer_Organic_Residue_Mass.resize(maxlayers,0);
    Layer_Potential_Ammonium_N_Uptake.resize(maxlayers,0);           
    Layer_Potential_Nitrate_N_Uptake.resize(maxlayers,0);            
    Layer_Potential_Phosphorus_Uptake.resize(maxlayers,0);           
    Layer_Residue_C_Balance.resize(maxlayers,0);                     
    Layer_Residue_CO2_Loss.resize(maxlayers,0);                      
    Layer_Residue_N_Balance.resize(maxlayers,0);                     
    Layer_Soil_Water_Uptake.resize(maxlayers,0);                     
    Layer_SOM_C_Balance.resize(maxlayers,0);                         
    Layer_SOM_CO2_Loss.resize(maxlayers,0);                          
    Layer_SOM_N_Balance.resize(maxlayers,0);                         
    Layer_Total_CO2_Loss.resize(maxlayers,0);                        
    New_Water_Content.resize(maxlayers,0);                  
    Old_Water_Content.resize(maxlayers,0);                  
    #endif
    Delta_Water_Content.resize(maxlayers,0);
    #ifndef CROPSYST_VERSION
    Initial_OM.resize(maxlayers,0);
    Initial_Phosphorus.resize(maxlayers,0);
    #endif
    Yesterday_WC.resize(maxlayers,0);                                            //150520
    Today_Hourly_WC.resize(maxlayers);                                           //150520
    for (int i = 0; i < maxlayers; i++)                                          //150520
        Today_Hourly_WC[i].resize(24);                                              //150520
    #if (!defined (CROPSYST_HYDROLOGY) || defined(MBVB_FD))
    Water_Potential.resize(maxlayers,0);                    
    #endif
    #ifdef MBVB_FD
    Upper_Water_Content.resize(maxlayers,0);                
    Lower_Water_Content.resize(maxlayers,0);                
    New_Upper_Water_Content.resize(maxlayers,0);            
    New_Lower_Water_Content.resize(maxlayers,0);            
	#endif
    //150522 Factor_Calibration_Later_Flow.resize(maxlayers,0);
    #ifndef CROPSYST_VERSION
    Soil_Microbial_Carbon_Mass.resize(maxlayers,0);                              //150522
    Soil_Labile_Carbon_Mass.resize(maxlayers,0);                                 //150522
    Soil_Passive_Carbon_Mass.resize(maxlayers,0);                                //150522
    Soil_Metastable_Carbon_Mass.resize(maxlayers,0);                             //150522
    #endif
}
//______________________________________________________________________________
SoilStateClass::~SoilStateClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~SoilStateClass:"<<std::endl;
#endif
    #if (!defined (CROPSYST_HYDROLOGY) || defined(MBVB_FD))
    delete[] Water_Content;
    #endif
#ifdef MBVB_FD
    delete[] Old_Lower_Water_Content;
    delete[] Old_Upper_Water_Content;
#endif
#ifdef Destruct_Monitor
    std::cout<<"~SoilStateClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void SoilStateClass::printSoilState()
{
    std::cout<<"------Soil State:-----\n";
    std::cout<<"Hourly Ponded Water (mm):"
       << pond.ref_depth().get_mm() << std::endl;                                  //160411RLN
       //160411RLN <<pondX.get_depth() * 1000.0<<std::endl;
    for (int L = 1; L <= num_layers; L++) {
        std::cout<<" Layer:"<<L
                    <<"\tVWC:"<<get_liquid_water_content_volumetric(L)
                    <<"\tVWC_FC:"<<SoilProfileRef.get_field_capacity_volumetric(L)
                    <<"\tVWC_SAT:"<<SoilProfileRef.get_saturation_water_content_volumetric(L,Ice_Content[L])
                    <<"\tK_min:"<<Minimum_Hydraulic_Conductivity
                    <<"\tC_Inf:"<<Current_Infiltration_Rate
                    <<"\tWet_Front_Dep:"<<Wetting_Front_Depth
                    <<std::endl;
    }
    std::cout<<"------End Soil State:-----\n";
}
//______________________________________________________________________________
int SoilStateClass::getSoilLayers() {return num_layers;}
//______________________________________________________________________________
double SoilStateClass::getTotalSoilLiqWaterContent_m()
{
    double tw(0);
    for (int layer = 1; layer <= num_layers; layer++) {
        tw += get_liquid_water_content_volumetric(layer) * SoilProfileRef.get_thickness_m(layer);
    }
    return tw;
}
//______________________________________________________________________________
double SoilStateClass::getTotalSoilIceContent_m()
{
    double tw(0);
    for (int layer = 1; layer <= num_layers; layer++) {
        tw += Ice_Content[layer] * SoilProfileRef.get_thickness_m(layer);
    }
    return tw;
}
//______________________________________________________________________________
double SoilStateClass::getTotalSoilWaterContent_m()
{
    return getTotalSoilLiqWaterContent_m() + getTotalSoilIceContent_m();
}
//______________________________________________________________________________
double SoilStateClass::getProfileSoilVWC()
{
    return getTotalSoilWaterContent_m() / SoilProfileRef.getTotoalSoilDepth_m();
}
//______________________________________________________________________________
double SoilStateClass::calc_h_Theta(double Theta,double Air_Entry,double Theta_s,double Campbell_b)
{
    //Theta [cm/cm]
    //air_entry []
    //Theta_s [cm/cm]
    //Campbell b [unitless]
    //h [same unit as air_entry]
    if (Theta > Theta_s) Theta = Theta_s;
    else if (Theta < 0.0) Theta = 1.0e-6;
    return Air_Entry * pow((Theta / Theta_s),(-Campbell_b));
}
//______________________________________________________________________________
void SoilStateClass::UpdateProfileState()
{
    //from layer to profile
    //Implement later M.Liu Jan 31, 2014
}
//______________________________________________________________________________
std::string SoilStateClass::FindSoilStateParameterFileName(int SoilID)
{
   std::string soil_state_ID;
   CORN::wstring_to_string(ControlRef.soilstate_filename.get_name(),soil_state_ID);
   CORN::append_nat16_to_string((nat16)SoilID, soil_state_ID);
   CORN::OS::File_name_concrete soil_state_filename
      (ControlRef.soilstate_filename.get_parent_directory_name_qualified()
      ,soil_state_ID
      ,ControlRef.soilstate_filename.get_extension());
   std::string result(soil_state_filename.c_str());
   return result;
}
//LML 141210 ___________________________________________________________________
#ifdef CROPSYST_SOILFILE
void SoilStateClass::SetDefaultSoilState()
{
    //LML 141210 quick & dirty solution now. An input file for initialization is needed later.
    #ifndef CROPSYST_VERSION
    Bypass_Coefficient = 0.0;
    Initial_Standing_Stubble_Residue_Label = "Winter_Wheat";
    Initial_Standing_Stubble_Residue_Mass = 200.0;
    Initial_Surface_Residue_Label = "Winter_Wheat";
    Initial_Surface_Residue_Mass = 4500.0;
    Initial_Soil_Residue_Label = "Garbanzo";
    Bare_Soil_CN_Adjustment_Factor = 1.0;
    Residue_Cover_CN_Adjustment_Factor = 1.0;
    Hydrologic_Group = "A";
    #endif
    #ifdef MBVB_FD
    Water_Table_Layer = 1;
    WT_Solute_Conc = 0;
    #endif
    for (nat8 layer = 1; layer <= num_layers; layer++) {
        #ifndef CROPSYST_VERSION
        Tillage_Decomposition_Adjustment_Factor[layer] = 1; //note, when clearing variable value is set to equal 0
        Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = 0;  //not cleared in Sub ClearStateVariables!
        Initial_OM[layer] = SoilProfileRef.organic_matter[layer];
        Initial_Soil_Residue_Mass[layer] = 0.01; 
        Layer_Organic_Residue_Mass[layer] = Initial_Soil_Residue_Mass[layer];
        Initial_C_Fraction_To_Microbial_Biomass[layer] = 2.0e-4;
        Initial_C_Fraction_To_Active_Labile_SOM[layer] = 5.0e-4;
        Initial_C_Fraction_To_Active_Metastable_SOM[layer] = 0.001;
        Initial_C_Fraction_To_Passive_SOM[layer] = 0.001;
        #endif
        #ifndef CROPSYST_VERSION
        //150811RLN these are never used so can be deleted:
        Denitrification_Event[layer] = false;
        Denitrification_Event_Second_Day[layer] = false;    //not "cleared" in Sub ClearStateVariables!
        #endif
        set_liquid_water_content_volumetric_layer(layer,SoilProfileRef.get_field_capacity_volumetric(layer));
        Ice_Content[layer] = 0.0;
        #ifndef CROPSYST_HYDROLOGY
        Old_Water_Content[layer] = Water_Content[layer];
        New_Water_Content[layer] = Water_Content[layer];
        #endif
        #ifndef CROPSYST_VERSION
        Layer_Nitrate_N_Mass[layer] = 0.05; 
        Total_Nitrate_N_Mass += Layer_Nitrate_N_Mass[layer];
        Layer_Ammonium_N_Mass[layer] = 0.0;  
        Total_Ammonium_N_Mass += Layer_Ammonium_N_Mass[layer];
        Layer_Phosphorus_Mass[layer] = 0.0;
        Total_Phosphorus_Mass += Layer_Phosphorus_Mass[layer];
        #endif
        //150522RLN obsolete ?Factor_Calibration_Later_Flow[layer] = 1.0;
    }
    #ifdef MBVB_FD
    for (nat8 L=num_layers + 1; L <= num_layers + 3; L++) {
        //Water_Content[L] = Water_Content[L - 1];
        double wc_upper = get_liquid_water_content_volumetric(L-1);
        set_water_content_volumetric_layer(L,wc_upper);
        Old_Water_Content[L] = Water_Content[L];
        New_Water_Content[L] = Water_Content[L];
    }
    setSoilWater();     //Calculate upper and lower water content for each soil layer
                        //and water potential for each node (one more than number of
                        //effective layers
    #endif
    #ifdef CROPSYST_FD
    if (hydrology_FD)
        hydrology_FD->expand_last_layer_for_boundary_conditions
         (num_layers,num_layers + 3);
    #endif
}
#endif
//______________________________________________________________________________
#ifdef OBS_READ_SOIL_State
void SoilStateClass::ReadSoilStateParameters
#ifdef CROPSYST_VERSION
(const CORN::OS::File_name &file_name
,CropSyst::Scenario &initial_profile)                                        //150723RLN
#else
(int SoilID)
#endif
{
    #ifdef CROPSYST_VERSION
    std::string Initial_Standing_Stubble_Residue_Label;
    std::string Initial_Surface_Residue_Label;
    std::string Initial_Soil_Residue_Label;
    double Initial_Standing_Stubble_Residue_Mass = 0;                            //（kg DM/m2)
    double Initial_Surface_Residue_Mass = 0;                                     //（kg DM/m2)
    #else
    std::string file_name = FindSoilStateParameterFileName(SoilID);
    #endif
    std::ifstream ifile(file_name.c_str());

    //std::clog<<"Soil file:"<<file_name.c_str()<<std::endl;
    if (ifile.is_open()) {
        int layer = 0;
        std::string nameline("");
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            if (!record_key.empty()) {
                //read the data line
                std::string dataline("");
                std::getline(ifile,dataline);
                std::stringstream ss("");
                ss.str(dataline);
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    char errormessage[200];
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Soil_Profile_Bypass") == 0) {
                        ss>>Bypass_Coefficient;
                    }
                    else if (record_key.compare("Initial_Residue") == 0) {
                        std::string residue_type_label("");
                        std::string residue_label("");
                        double amount(0);
                        ss>>residue_label>>amount>>residue_type_label;
                        if (residue_label.compare("Initial_Standing_Stubble") == 0) {
                            Initial_Standing_Stubble_Residue_Label = residue_type_label;
                            Initial_Standing_Stubble_Residue_Mass = amount;
                            //residue types M.Liu
                        } else if (residue_label.compare("Initial_Surface_Residue") == 0) {
                            Initial_Surface_Residue_Label = residue_type_label;
                            Initial_Surface_Residue_Mass = amount;
                        } else if (residue_label.compare("Initial_Soil_Root_Residues") == 0) {
                            Initial_Soil_Residue_Label = residue_type_label;
                        }
                    }
                    #ifndef CROPSYST_VERSION
                    else if (record_key.compare("SCS_CN_Soil_Adjust") == 0) {
                        ss>>Bare_Soil_CN_Adjustment_Factor;
                    }
                    else if (record_key.compare("SCS_CN_Residue_Adjust") == 0) {
                        ss>>Residue_Cover_CN_Adjustment_Factor;
                    }
                    else if (record_key.compare("SCS_CN_Hydro_Group") == 0) {
                        removeWhitespace(dataline);
                        Hydrologic_Group = dataline;
                    }
                    #endif
                    #ifdef MBVB_FD
                    else if (record_key.compare("Water_Table_At_Layer") == 0) {
                        ss>>Water_Table_Layer;
                    } else if (record_key.compare("WT_Solute_Conc") == 0) {
                        ss>>WT_Solute_Conc;
                    }
					#endif
                    else if (record_key.compare("Layer")  == 0 ||
                               record_key.compare("Layers") == 0) {
                      bool multilayer = (record_key.compare("Layers") == 0);
                      int totallayers = layer + 1;
                      if (multilayer) totallayers = SoilProfileRef.get_number_layers();
                      while (layer < totallayers) {
                        layer++;
                        double fdata[SOIL_PARAMETER_NUMBERS_FOR_ARRAY];
                        for (int i = 1; i <= SOIL_PARAMETER_NUMBERS_FOR_ARRAY-1; i++) {
                            ss>>fdata[i];
                            //std::cout<<"i:"<<i<<" value:"<<fdata[i]<<std::endl;
                        }
                        ss.clear();
                        #ifndef CROPSYST_VERSION
                        Tillage_Decomposition_Adjustment_Factor[layer] = 1; //note, when clearing variable value is set to equal 0
                        #endif
                        #ifndef CROPSYST_VERSION
                        //150811RLN these are never used:
                        Denitrification_Event[layer] = false;
                        Denitrification_Event_Second_Day[layer] = false;    //not "cleared" in Sub ClearStateVariables!
                        #endif
                        #ifdef CROPSYST_VERSION
                        initial_profile.horizon_percent_organic_matter[layer] = fdata[5];
                        initial_profile.organic_matter_initialization_parameters.microbial_biomass_percent[layer]   = fdata[15] * 100.;
                        initial_profile.organic_matter_initialization_parameters.labile_SOM_percent[layer]          = fdata[16] * 100.;
                        initial_profile.organic_matter_initialization_parameters.metastable_SOM_percent[layer]      = fdata[17] * 100.;
                        initial_profile.organic_matter_initialization_parameters.passive_SOM_percent[layer]         = fdata[18] * 100.;
//170404LML #ifdef HARD_CODED_INITIAL_MINERAL_NITROGEN_AND_MOISTURE
                        if (ControlRef.use_even_soil_N_and_FC) {                 //170404LML
                        std::clog << "Macro HARD_CODED_INITIAL_MINERAL_NITROGEN is defined!\n";
                        initial_profile.horizon_N_NH4[layer] = 0.0;
                        if (layer >= 1 && layer <= 3) {
                            initial_profile.horizon_N_NO3[layer] = 10.0;
                            if (layer < 3) initial_profile.horizon_N_NH4[layer] = 10.0;
                            else initial_profile.horizon_N_NH4[layer] = 5.0;
                        } else if (layer >= 4 && layer <= 5) {
                            initial_profile.horizon_N_NO3[layer] = 15.0;
                            if (layer == 4) initial_profile.horizon_N_NH4[layer] = 5;
                        } else if (layer >= 6) {
                            initial_profile.horizon_N_NO3[layer] = 20.0;
                        }
                        double field_capacity = SoilProfileRef.get_field_capacity_volumetric(layer);
                        set_water_content_volumetric_layer(layer,field_capacity);
                        } else {
//170404LML #else
                        initial_profile.horizon_N_NO3[layer] = fdata[12];
                        initial_profile.horizon_N_NH4[layer] = fdata[13];
                        set_water_content_volumetric_layer(layer,fdata[10]);
//170404LML #endif
                        }
                        initial_profile.horizon_incorporated_residue[layer] = fdata[14] / 10000.0;
                        #ifdef CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG
                        initial_profile.horizon_N_NO3[layer] = 1.0;
                        initial_profile.horizon_N_NH4[layer] = 1.0;
                        #endif
                        #else
                        Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = 0;  //not cleared in Sub ClearStateVariables!
                        Initial_OM[layer] = fdata[5];
                        Initial_Soil_Residue_Mass[layer] = fdata[14] / 10000.0; //Converts kg/ha to kg/m2
                        //FMS Apr 21, 2015 deleted this varaible, does not used
                        //Layer_Organic_Residue_Mass[layer] = Initial_Soil_Residue_Mass[layer];
                        Initial_C_Fraction_To_Microbial_Biomass[layer] = fdata[15];
                        Initial_C_Fraction_To_Active_Labile_SOM[layer] = fdata[16];
                        Initial_C_Fraction_To_Active_Metastable_SOM[layer] = fdata[17];
                        Initial_C_Fraction_To_Passive_SOM[layer] = fdata[18];
                        #endif

                        //DEBUG!!!
                        #if (defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_EVAPORATION_FOR_DEBUG))
                        double vwc = SoilProfileRef.get_saturation_water_content_volumetric(layer,0);
                        set_water_content_volumetric_layer(layer,vwc);
                        std::clog<<"DEBUG!!! setting saturated soil moisture for initial condition!\n";
                        #elif defined(CHECK_HOURLY_CASCADE_FOR_DEBUG)
                        double vwc = SoilProfileRef.get_field_capacity_volumetric(layer);
                        set_water_content_volumetric_layer(layer,vwc);
                        std::clog<<"DEBUG!!! setting field capacity for initial condition!\n";
                        #endif

                        //DebugPrintVariable(__FILE__,__LINE__,"WC",get_liquid_water_content_volumetric(layer),layer);
                        Ice_Content[layer] = 0.0;                        //Need check M.Liu
                        Yesterday_WC[layer] = fdata[10];                         //150521
                        assert(get_liquid_water_content_volumetric(layer) <= SoilProfileRef.get_saturation_water_content_volumetric(layer,0)); //FMS Mar 30, 2015
                        #ifndef CROPSYST_HYDROLOGY
                        Old_Water_Content[layer] = Water_Content[layer];
                        New_Water_Content[layer] = Water_Content[layer];
                        #endif
                        //LML 140606 xHourly_Water_Content[layer] = fdata[10];//Water_Content[layer];
                        #ifndef CROPSYST_VERSION
                        Layer_Nitrate_N_Mass[layer] = fdata[12] / 10000.0;       //nitrate mass 3D array
                        Layer_Ammonium_N_Mass[layer] = fdata[13] / 10000.0;      //ammonium mass 3D array
                        #endif
                        #ifndef CROPSYST_VERSION
                        //NO3[layer] = fdata[12] / 10000;  //Converts kg/ha to kg/m2 - initial nitrate mass
                        Total_Nitrate_N_Mass += Layer_Nitrate_N_Mass[layer];
                        //NH4[layer] = fdata[13] / 10000;         //Converts kg/ha to kg/m2 - initial ammonium mass
                        Total_Ammonium_N_Mass += Layer_Ammonium_N_Mass[layer];
                        //2013? RS edited; was:
                        //Phosphorus(L) = Cells(StartReadRow + L, 11) / 10000 'Converts kg/ha to kg/m2
                        //Total_Phosphorus_Mass(Year, DOY) = Total_Phosphorus_Mass(Year, DOY) + Phosphorus(L)
                        //now:
                        Layer_Phosphorus_Mass[layer] = fdata[11] / 10000.0; //Converts kg/ha to kg/m2
                        Total_Phosphorus_Mass += Layer_Phosphorus_Mass[layer];
                        //end edited
                        #endif
                        //Mac_Po_Fac[layer] = 0.0;
                        //FMS Mar 12, 2015
                        //Factor_Calibration_Later_Flow[layer] = fdata[29];
                        if (layer < totallayers) {
                            std::getline(ifile,dataline);
                            ss.str(dataline);
                        }
                      }
                    } else {
                        char errormessage[200];
                        sprintf(errormessage,"Warning: Can't find keyword %s",record_key.c_str());
                        //nrerror(errormessage);
                    }
                }
            }
        }
        #ifdef CROPSYST_VERSION
        CORN::OS::Directory_entry_name_concrete actual_residue_crop_filename(initial_profile.previous_residue_crop_filename,Initial_Standing_Stubble_Residue_Label);
        initial_profile.previous_residue_crop_filename.set_DEN(actual_residue_crop_filename);
        initial_profile.stubble_residue_32 = Initial_Standing_Stubble_Residue_Mass;
        initial_profile.surface_residue_32 = Initial_Surface_Residue_Mass;
        #endif
    } else {
        char errormessage[200];
        sprintf(errormessage,"Cann't open soil state file %s",file_name.c_str());
        nrerror(errormessage);
    }
    ifile.close();
    //For FD-method
    //#ifndef CROPSYST_HYDROLOGY
     #ifdef MBVB_FD
    for (int L = num_layers + 1; L <= num_layers + 3; L++) {
        //Water_Content[L] = Water_Content[L - 1];
        double wc_upper = get_liquid_water_content_volumetric(L-1);
        set_water_content_volumetric_layer(L,wc_upper);
         Old_Water_Content[L] = Water_Content[L];
        New_Water_Content[L] = Water_Content[L];
        //Hourly_Water_Content[L] = get_liquid_water_content_volumetric(L);//Water_Content[L];
     }
     setSoilWater();     //Calculate upper and lower water content for each soil layer
                        //and water potential for each node (one more than number of
                        //effective layers
    #endif
    #ifdef CROPSYST_FD
    if (hydrology_FD)
      hydrology_FD->expand_last_layer_for_boundary_conditions
         (num_layers,num_layers + 3);
    #endif
}
//______________________________________________________________________________
void SoilStateClass::ReadSoilStateParameters
#ifdef CROPSYST_VERSION
(const CORN::OS::File_name &file_name
,InitialSoilStateClass &initial_profile)                                        //150723RLN
#else
(int SoilID)
#endif
{
    #ifdef CROPSYST_VERSION
    std::string Initial_Standing_Stubble_Residue_Label;
    std::string Initial_Surface_Residue_Label;
    std::string Initial_Soil_Residue_Label;
    double Initial_Standing_Stubble_Residue_Mass = 0;                            //（kg DM/m2)
    double Initial_Surface_Residue_Mass = 0;                                     //（kg DM/m2)
    #else
    std::string file_name = FindSoilStateParameterFileName(SoilID);
    #endif
    std::ifstream ifile(file_name.c_str());

    //std::clog<<"Soil file:"<<file_name.c_str()<<std::endl;
    if (ifile.is_open()) {
        int layer = 0;
        std::string nameline("");
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            if (!record_key.empty()) {
                //read the data line
                std::string dataline("");
                std::getline(ifile,dataline);
                std::stringstream ss("");
                ss.str(dataline);
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    char errormessage[200];
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Soil_Profile_Bypass") == 0) {
                        ss>>Bypass_Coefficient;
                    }

                    else if (record_key.compare("Initial_Residue") == 0) {
                        std::string residue_type_label("");
                        std::string residue_label("");
                        double amount(0);
                        ss>>residue_label>>amount>>residue_type_label;
                        if (residue_label.compare("Initial_Standing_Stubble") == 0) {
                            Initial_Standing_Stubble_Residue_Label = residue_type_label;
                            Initial_Standing_Stubble_Residue_Mass = amount;
                            //residue types M.Liu
                        } else if (residue_label.compare("Initial_Surface_Residue") == 0) {
                            Initial_Surface_Residue_Label = residue_type_label;
                            Initial_Surface_Residue_Mass = amount;
                        } else if (residue_label.compare("Initial_Soil_Root_Residues") == 0) {
                            Initial_Soil_Residue_Label = residue_type_label;
                        }
                    }
                    #ifndef CROPSYST_VERSION
                    else if (record_key.compare("SCS_CN_Soil_Adjust") == 0) {
                        ss>>Bare_Soil_CN_Adjustment_Factor;
                    }
                    else if (record_key.compare("SCS_CN_Residue_Adjust") == 0) {
                        ss>>Residue_Cover_CN_Adjustment_Factor;
                    }
                    else if (record_key.compare("SCS_CN_Hydro_Group") == 0) {
                        removeWhitespace(dataline);
                        Hydrologic_Group = dataline;
                    }
                    #endif
                    #ifdef MBVB_FD
                    else if (record_key.compare("Water_Table_At_Layer") == 0) {
                        ss>>Water_Table_Layer;
                    } else if (record_key.compare("WT_Solute_Conc") == 0) {
                        ss>>WT_Solute_Conc;
                    }
                    #endif
                    else if (record_key.compare("Layer")  == 0 ||
                               record_key.compare("Layers") == 0) {
                      bool multilayer = (record_key.compare("Layers") == 0);
                      int totallayers = layer + 1;
                      if (multilayer) totallayers = SoilProfileRef.get_number_layers();
                      while (layer < totallayers) {
                        layer++;
                        double fdata[SOIL_PARAMETER_NUMBERS_FOR_ARRAY];
                        for (int i = 1; i <= SOIL_PARAMETER_NUMBERS_FOR_ARRAY-1; i++) {
                            ss>>fdata[i];
                            //std::cout<<"i:"<<i<<" value:"<<fdata[i]<<std::endl;
                        }
                        ss.clear();
                        #ifndef CROPSYST_VERSION
                        Tillage_Decomposition_Adjustment_Factor[layer] = 1; //note, when clearing variable value is set to equal 0
                        #endif
                        #ifndef CROPSYST_VERSION
                        //150811RLN these are never used:
                        Denitrification_Event[layer] = false;
                        Denitrification_Event_Second_Day[layer] = false;    //not "cleared" in Sub ClearStateVariables!
                        #endif
                        #ifdef CROPSYST_VERSION
                        initial_profile.horizon_percent_organic_matter[layer] = fdata[5];
                        initial_profile.organic_matter_initialization_parameters.microbial_biomass_percent[layer]   = fdata[15] * 100.;
                        initial_profile.organic_matter_initialization_parameters.labile_SOM_percent[layer]          = fdata[16] * 100.;
                        initial_profile.organic_matter_initialization_parameters.metastable_SOM_percent[layer]      = fdata[17] * 100.;
                        initial_profile.organic_matter_initialization_parameters.passive_SOM_percent[layer]         = fdata[18] * 100.;
                        initial_profile.horizon_N_NO3[layer] = fdata[12];
                        initial_profile.horizon_N_NH4[layer] = fdata[13];
                        initial_profile.horizon_incorporated_residue[layer] = fdata[14] / 10000.0;
                        #ifdef CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG
                        initial_profile.horizon_N_NO3[layer] = 1.0;
                        initial_profile.horizon_N_NH4[layer] = 1.0;
                        #endif
                        #else
                        Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = 0;  //not cleared in Sub ClearStateVariables!
                        Initial_OM[layer] = fdata[5];
                        Initial_Soil_Residue_Mass[layer] = fdata[14] / 10000.0; //Converts kg/ha to kg/m2
                        //FMS Apr 21, 2015 deleted this varaible, does not used
                        //Layer_Organic_Residue_Mass[layer] = Initial_Soil_Residue_Mass[layer];
                        Initial_C_Fraction_To_Microbial_Biomass[layer] = fdata[15];
                        Initial_C_Fraction_To_Active_Labile_SOM[layer] = fdata[16];
                        Initial_C_Fraction_To_Active_Metastable_SOM[layer] = fdata[17];
                        Initial_C_Fraction_To_Passive_SOM[layer] = fdata[18];
                        #endif
                        //Water_Content[layer] = fdata[10]; //initial Water content
                        set_water_content_volumetric_layer(layer,fdata[10]);
                        initial_profile.vwc[layer] = fdata[10];
                        //DEBUG!!!
                        #if (defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_EVAPORATION_FOR_DEBUG))
                        double vwc = SoilProfileRef.get_saturation_water_content_volumetric(layer,0);
                        set_water_content_volumetric_layer(layer,vwc);
                        std::clog<<"DEBUG!!! setting saturated soil moisture for initial condition!\n";
                        #elif defined(CHECK_HOURLY_CASCADE_FOR_DEBUG)
                        double vwc = SoilProfileRef.get_field_capacity_volumetric(layer);
                        set_water_content_volumetric_layer(layer,vwc);
                        std::clog<<"DEBUG!!! setting field capacity for initial condition!\n";
                        #endif

                        //DebugPrintVariable(__FILE__,__LINE__,"WC",get_liquid_water_content_volumetric(layer),layer);
                        Ice_Content[layer] = 0.0;                        //Need check M.Liu
                        Yesterday_WC[layer] = fdata[10];                         //150521
                        assert(get_liquid_water_content_volumetric(layer) <= SoilProfileRef.get_saturation_water_content_volumetric(layer,0)); //FMS Mar 30, 2015
                        #ifndef CROPSYST_HYDROLOGY
                        Old_Water_Content[layer] = Water_Content[layer];
                        New_Water_Content[layer] = Water_Content[layer];
                        #endif
                        //LML 140606 xHourly_Water_Content[layer] = fdata[10];//Water_Content[layer];
                        #ifndef CROPSYST_VERSION
                        Layer_Nitrate_N_Mass[layer] = fdata[12] / 10000.0;       //nitrate mass 3D array
                        Layer_Ammonium_N_Mass[layer] = fdata[13] / 10000.0;      //ammonium mass 3D array
                        #endif
                        #ifndef CROPSYST_VERSION
                        //NO3[layer] = fdata[12] / 10000;  //Converts kg/ha to kg/m2 - initial nitrate mass
                        Total_Nitrate_N_Mass += Layer_Nitrate_N_Mass[layer];
                        //NH4[layer] = fdata[13] / 10000;         //Converts kg/ha to kg/m2 - initial ammonium mass
                        Total_Ammonium_N_Mass += Layer_Ammonium_N_Mass[layer];
                        //2013? RS edited; was:
                        //Phosphorus(L) = Cells(StartReadRow + L, 11) / 10000 'Converts kg/ha to kg/m2
                        //Total_Phosphorus_Mass(Year, DOY) = Total_Phosphorus_Mass(Year, DOY) + Phosphorus(L)
                        //now:
                        Layer_Phosphorus_Mass[layer] = fdata[11] / 10000.0; //Converts kg/ha to kg/m2
                        Total_Phosphorus_Mass += Layer_Phosphorus_Mass[layer];
                        //end edited
                        #endif
                        //Mac_Po_Fac[layer] = 0.0;
                        //FMS Mar 12, 2015
                        //Factor_Calibration_Later_Flow[layer] = fdata[29];
                        if (layer < totallayers) {
                            std::getline(ifile,dataline);
                            ss.str(dataline);
                        }
                      }
                    } else {
                        char errormessage[200];
                        sprintf(errormessage,"Warning: Can't find keyword %s",record_key.c_str());
                        //nrerror(errormessage);
                    }
                }
            }
        }
        #ifdef CROPSYST_VERSION
        CORN::OS::Directory_entry_name_concrete actual_residue_crop_filename(initial_profile.previous_residue_crop_filename,Initial_Standing_Stubble_Residue_Label);
        initial_profile.previous_residue_crop_filename.set_DEN(actual_residue_crop_filename);
        initial_profile.stubble_residue_32 = Initial_Standing_Stubble_Residue_Mass;
        initial_profile.surface_residue_32 = Initial_Surface_Residue_Mass;
        #endif
    } else {
        char errormessage[200];
        sprintf(errormessage,"Cann't open soil state file %s",file_name.c_str());
        nrerror(errormessage);
    }
    ifile.close();
    //For FD-method
    //#ifndef CROPSYST_HYDROLOGY
     #ifdef MBVB_FD
    for (int L = num_layers + 1; L <= num_layers + 3; L++) {
        //Water_Content[L] = Water_Content[L - 1];
        double wc_upper = get_liquid_water_content_volumetric(L-1);
        set_water_content_volumetric_layer(L,wc_upper);
         Old_Water_Content[L] = Water_Content[L];
        New_Water_Content[L] = Water_Content[L];
        //Hourly_Water_Content[L] = get_liquid_water_content_volumetric(L);//Water_Content[L];
     }
     setSoilWater();     //Calculate upper and lower water content for each soil layer
                        //and water potential for each node (one more than number of
                        //effective layers
    #endif
    #ifdef CROPSYST_FD
    if (hydrology_FD)
      hydrology_FD->expand_last_layer_for_boundary_conditions
         (num_layers,num_layers + 3);
    #endif
}
#endif
//______________________________________________________________________________
void SoilStateClass::CopySoilStateParameters
(const InitialSoilStateClass &from_initial_profile
,CropSyst::Scenario    &initial_profile_scen)
{
    //160317LML for each soil type, only read once.
    Bypass_Coefficient = from_initial_profile.Bypass_Coefficient;
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (int layer = 0; layer <= num_layers; layer++) {
        initial_profile_scen.horizon_percent_organic_matter[layer]                                       = from_initial_profile.horizon_percent_organic_matter[layer];
        initial_profile_scen.organic_matter_initialization_parameters.microbial_biomass_percent[layer]   = from_initial_profile.organic_matter_initialization_parameters.microbial_biomass_percent[layer];
        initial_profile_scen.organic_matter_initialization_parameters.labile_SOM_percent[layer]          = from_initial_profile.organic_matter_initialization_parameters.labile_SOM_percent[layer];
        initial_profile_scen.organic_matter_initialization_parameters.metastable_SOM_percent[layer]      = from_initial_profile.organic_matter_initialization_parameters.metastable_SOM_percent[layer];
        initial_profile_scen.organic_matter_initialization_parameters.passive_SOM_percent[layer]         = from_initial_profile.organic_matter_initialization_parameters.passive_SOM_percent[layer];
        initial_profile_scen.horizon_N_NO3[layer] = from_initial_profile.horizon_N_NO3[layer];
        initial_profile_scen.horizon_N_NH4[layer] = from_initial_profile.horizon_N_NH4[layer];
        initial_profile_scen.horizon_incorporated_residue[layer] = from_initial_profile.horizon_incorporated_residue[layer];
        #ifdef CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG
        initial_profile_scen.horizon_N_NO3[layer] = 1.0;
        initial_profile_scen.horizon_N_NH4[layer] = 1.0;
        #endif
        double vwc = from_initial_profile.vwc[layer];
        set_water_content_volumetric_layer(layer,vwc);
        #if (defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_EVAPORATION_FOR_DEBUG))
        vwc = SoilProfileRef.get_saturation_water_content_volumetric(layer,0);
        set_water_content_volumetric_layer(layer,vwc);
        std::clog<<"DEBUG!!! setting saturated soil moisture for initial condition!\n";
        #elif defined(CHECK_HOURLY_CASCADE_FOR_DEBUG)
        vwc = SoilProfileRef.get_field_capacity_volumetric(layer);
        set_water_content_volumetric_layer(layer,vwc);
        std::clog<<"DEBUG!!! setting field capacity for initial condition!\n";
        #endif
        Ice_Content[layer] = 0.0;
        Yesterday_WC[layer] = vwc;
    }
    #ifdef CROPSYST_VERSION
    initial_profile_scen.previous_residue_crop_filename.set_DEN(from_initial_profile.previous_residue_crop_filename); //160406RLN
    initial_profile_scen.stubble_residue_32 = from_initial_profile.stubble_residue_32;
    initial_profile_scen.surface_residue_32 = from_initial_profile.surface_residue_32;
    #endif
    #ifdef CROPSYST_FD
    if (hydrology_FD)
      hydrology_FD->expand_last_layer_for_boundary_conditions
         (num_layers,num_layers + 3);
    #endif
}
//______________________________________________________________________________
//160722RLN void SoilStateClass::InitDailyFluxes()
bool SoilStateClass::start_day()                                   modification_ //160722
{
    Daily_Drainage_m   = 0;                                                      //LML 150527
    Daily_Irrigation_m = 0;
    Daily_Infiltration = 0;
    Daily_Runoff_infiltration_excess_m = 0;
    #ifndef CROPSYST_VERSION
    Daily_Ammonium_Leaching = 0;
    Daily_Ammonium_N_Fertigation = 0;
    Daily_Ammonium_N_Fertilization = 0;
    Daily_Nitrate_Leaching = 0;
    Daily_Nitrate_N_Fertigation = 0;
    Daily_Nitrate_N_Fertilization = 0;
    Daily_Organic_N_Fertilization = 0;
    Daily_Phosphorus_Leaching = 0;
    #endif
    Daily_Ponded_Water = 0;
    Daily_Runoff_m = 0;
    Daily_Runon_m = 0;
    Daily_LaterFlowIn_m = 0;
    Daily_LaterFlowOut_m = 0;
    //Daily_PET_MB = 0;                                                            //160407LML
    return true;                                                                 //160722RLN
}
//______________________________________________________________________________
void SoilStateClass::InitHourlyFluxes()  // rename to start_hour
{
    Hourly_Drainage_m = 0.0;
    Hourly_Irrigation_m = 0.0;
    Hourly_Runoff_m = 0.0;
    Hourly_Runon_m = 0.0;
    Hourly_Infiltration_m = 0.0;
    Hourly_Prec_Irrig_SnowMelt_m = 0.0;
}
//______________________________________________________________________________
float64 SoilStateClass::get_liquid_water_content_volumetric      ( nat8 layer)  const
#if (defined(CROPSYST_HYDROLOGY) || defined(CROPSYST_FD)) && (!defined(LIU_FD_RICHARD))
{ return hydrology->get_liquid_water_content_volumetric(layer); }                //140429RLN
#else
{ return Water_Content[layer]; }                                                 //140429RLN
#endif
//______________________________________________________________________________
float64 SoilStateClass::set_water_content_volumetric_layer( nat8 layer, float64 new_water_content)
{  float64 return_new_water_content = 0.0;
   return_new_water_content = hydrology->set_water_content_volumetric_layer(layer,new_water_content);  //140429RLN
#ifdef MBVB_FD
   //Hourly_Water_Content[layer] = new_water_content;
   return_new_water_content = Water_Content[layer] = new_water_content;
#endif
   return return_new_water_content;
}
//_2014-04-29RLN_____________________________________________________________________________
float64 SoilStateClass::set_liquid_water_content_volumetric_layer( nat8 layer, float64 new_water_content)
{
    float64 old_liq_water = hydrology->get_liquid_water_content_volumetric(layer);
    float64 change = new_water_content - old_liq_water;
    float64 return_new_water_content = hydrology->change_liquid_water_content_by_volumetric(layer,change);
    return return_new_water_content;
}
//_2014-09-03LML_____________________________________________________________________________
float64 SoilStateClass::change_liquid_water_content_by_volumetric( nat8 layer, float64 change_WC) modification_
{  
   // This function is only temporary until CropSyst hydrology classes are implemented
   float64 new_water_content = hydrology->change_liquid_water_content_by_volumetric(layer,change_WC);
   #ifdef MBVB_FD
   Water_Content[layer] += change_WC;                                            //070824
   new_water_content = Water_Content[layer] ;                                    //070824
   #endif
   return new_water_content;
}
//______________________________________________________________________________
//______________________________________________________________________________
void SoilStateClass::ClearMaintenanceFluxes() {
    Maintenance_Respiration = 0.0;             
    Biosynthesi_Efficiency = 0.0;              
    Gross_Canopy_Photosynthesis = 0.0;         
    CO2_by_Plant_Respiration = 0.0;            
    Biomass_Root_Today = 0.0;                  
    Biomass_Top_Today = 0.0; 
}
//______________________________________________________________________________

#ifndef MSVB_CASCADE_INFILTRATION_HOUR
bool SoilStateClass::initialize()
{  //RLN NYN Soil_hydrology_cascade::initialize();
/*NYI
   #ifdef CROPSYST_FD
   //RLN NYN eventually hydrology will be instanciated according
   // to the infiltation model used.
   // But currently always instanciating FD hydrology
   hydrology = new Soil_hydrology_finite_difference
      (SoilProfileRef
      ,SoilProfileRef //hydraulic properies
      ,soil_structure);
   #endif
*/
   return true;
}
//_2014-05-06___________________________________________________________________


//140424 These functions are here temporarily until we clean up the soil layers in Mingliang's code
// These only need to be implemented as needed.

/*
float64 SoilStateClass::get_water_plus_ice_content_gravimetric   ( nat8 layer)  const { assert(false); return 0; }
*/

/*
float64 SoilStateClass::get_water_plus_ice_content_volumetric_at ( nat8 layer,CORN::Hour hour)  const { assert(false); return 0; }
float64 SoilStateClass::get_water_plus_ice_content_volumetric    ( nat8 layer)  const { assert(false); return 0; }
float64 SoilStateClass::get_water_filled_porosity( nat8 layer, CORN::Hour for_hour)   const { assert(false); return 0; }
float64 SoilStateClass::get_water_potential                      ( nat8 layer)  const { assert(false); return 0; }
float64 SoilStateClass::provide_water_depth_profile(bool all_water)        provision_ { assert(false); return 0; }
float64 SoilStateClass::get_plant_avail_water( nat8 layer)                      const { assert(false); return 0; }
float64 SoilStateClass::calc_available_water_fraction( nat8 layer, bool real_wilt_based) const { assert(false); return 0; }
float64 SoilStateClass::get_K_Theta
 (nat8 layer
 ,float64 Theta, float64 Theta_s)                                     const { assert(false); return 0; }
float64 SoilStateClass::get_ice_content                           ( nat8 layer) const { assert(false); return 0; }
float64 SoilStateClass::get_ice_content_yesterday                 ( nat8 layer) const { assert(false); return 0; }
bool SoilStateClass::is_frozen                                    ( nat8 layer) const { assert(false); return 0; }
*/

/*
float64 SoilStateClass::extract_water(float64 water_uptake_m[] , nat8 start_layer) { assert(false); return 0; }
bool SoilStateClass::start_day()                                        modification_ { assert(false); return 0; }
void SoilStateClass::update_liquid_and_ice_water_content()              modification_ { assert(false);  }

#ifdef USE_VARIABLE_RECORDERS
bool SoilStateClass::render_variable_recorders
      (CS::Variable_recorders &recorders
      ,nat32 desired_descriptive_summary_elements)                { assert(false); return 0; } //130924
#endif
*/
#endif
//______________________________________________________________________________
bool SoilStateClass::start_year()                                  modification_ //160404LML InitAnnualFluxes()
{
    bool ended = false;
    Annual_Precipitation_m              = 0;                                     //161101LML
    Annual_Actual_Soil_Evaporation_m    = 0;
    Annual_Actual_Crop_Transpiration_m  = 0;
    Annual_Drainage_m                   = 0;
    Annual_Irrigation_m                 = 0;
    Annual_Ammonium_Leaching            = 0;
    //Annual_Ammonium_N_Fertigation       = 0;
    Annual_Ammonium_N_Fertilization     = 0;
    Annual_Nitrate_Leaching             = 0;
    //Annual_Nitrate_N_Fertigation        = 0;
    Annual_Nitrate_N_Fertilization      = 0;
    Annual_Organic_N_Fertilization      = 0;
    Annual_Nitrification                = 0;
    Annual_Denitrification              = 0;
    Annual_N_uptake                     = 0;
    ended = true;
    return ended;
}
//______________________________________________________________________________
double SoilStateClass::get_K_Theta_Lateralflow(nat8 layer, double Theta,
  double Theta_s,double K_sat_input,double Theta_b_input)
{
    float64 K_sat             = K_sat_input;
    float64 Campbell_b        = SoilProfileRef.get_Campbell_b(layer,false);
    float64 Theta_b           = Theta_b_input;
    float64 K_Theta_b         = K_sat *
                                pow(Theta_b / Theta_s
                                    ,(2.0 * Campbell_b + 3.0));
    if(CORN::is_approximately<float64>(Theta_b,0.0,1E-8)) Theta_b = Theta_s;
    //140305 claudio says we won't use this     macro_pore_factor = hydraulic_properties_ref.get_macro_pore_factor();
    float64 K_Theta =
      (Theta < Theta_b)
      ? K_sat * pow(Theta / Theta_s, (2.0 * Campbell_b + 3.0))
      : CORN::is_approximately<float64>(Theta_b,Theta_s,1E-8)
         ?  /*macro_pore_factor * */ K_sat
         :  (Theta - Theta_b) / (Theta_s - Theta_b) * (/*macro_pore_factor * */  K_sat - K_Theta_b) + K_Theta_b;
            //analogous to the approach described in Mehta et al. 2004 Environmental Modeling and Assessment 9: 77-89, 2004.
    return K_Theta;
}
//______________________________________________________________________________
#endif
//______________________________________________________________________________
InitialSoilStateClass::InitialSoilStateClass(SoilProfileClass &SoilProfileRef_, AllControlClass &ControlRef_)
:previous_residue_crop_filename("<unknown or no previous crop residue>.crp")
,SoilProfileRef(SoilProfileRef_)
,ControlRef(ControlRef_)
{}
//______________________________________________________________________________
void InitialSoilStateClass::ReadSoilStateParameters(const CORN::OS::File_name &file_name)
{
    #ifdef CROPSYST_VERSION
    std::string Initial_Standing_Stubble_Residue_Label;
    std::string Initial_Surface_Residue_Label;
    std::string Initial_Soil_Residue_Label;
    double Initial_Standing_Stubble_Residue_Mass = 0;                            //（kg DM/m2)
    double Initial_Surface_Residue_Mass = 0;                                     //（kg DM/m2)
    #else
    std::string file_name = FindSoilStateParameterFileName(SoilID);
    #endif
    std::ifstream ifile(file_name.c_str());

    //std::clog<<"Soil file:"<<file_name.c_str()<<std::endl;
    if (ifile.is_open()) {
        int layer = 0;
        std::string nameline("");
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            if (!record_key.empty()) {
                //read the data line
                std::string dataline("");
                std::getline(ifile,dataline);
                std::stringstream ss("");
                ss.str(dataline);
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    char errormessage[200];
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Soil_Profile_Bypass") == 0) {
                        ss>>Bypass_Coefficient;
                    }

                    else if (record_key.compare("Initial_Residue") == 0) {
                        std::string residue_type_label("");
                        std::string residue_label("");
                        double amount(0);
                        ss>>residue_label>>amount>>residue_type_label;
                        if (residue_label.compare("Initial_Standing_Stubble") == 0) {
                            Initial_Standing_Stubble_Residue_Label = residue_type_label;
                            Initial_Standing_Stubble_Residue_Mass = amount;
                            //residue types M.Liu
                        } else if (residue_label.compare("Initial_Surface_Residue") == 0) {
                            Initial_Surface_Residue_Label = residue_type_label;
                            Initial_Surface_Residue_Mass = amount;
                        } else if (residue_label.compare("Initial_Soil_Root_Residues") == 0) {
                            Initial_Soil_Residue_Label = residue_type_label;
                        }
                    }
                    #ifndef CROPSYST_VERSION
                    else if (record_key.compare("SCS_CN_Soil_Adjust") == 0) {
                        ss>>Bare_Soil_CN_Adjustment_Factor;
                    }
                    else if (record_key.compare("SCS_CN_Residue_Adjust") == 0) {
                        ss>>Residue_Cover_CN_Adjustment_Factor;
                    }
                    else if (record_key.compare("SCS_CN_Hydro_Group") == 0) {
                        removeWhitespace(dataline);
                        Hydrologic_Group = dataline;
                    }
                    #endif
                    #ifdef MBVB_FD
                    else if (record_key.compare("Water_Table_At_Layer") == 0) {
                        ss>>Water_Table_Layer;
                    } else if (record_key.compare("WT_Solute_Conc") == 0) {
                        ss>>WT_Solute_Conc;
                    }
                    #endif
                    else if (record_key.compare("Layer")  == 0 ||
                               record_key.compare("Layers") == 0) {
                      bool multilayer = (record_key.compare("Layers") == 0);
                      int totallayers = layer + 1;
                      if (multilayer) totallayers = SoilProfileRef.get_number_layers();
                      while (layer < totallayers) {
                        layer++;
                        double fdata[SOIL_PARAMETER_NUMBERS_FOR_ARRAY];
                        for (int i = 1; i <= SOIL_PARAMETER_NUMBERS_FOR_ARRAY-1; i++) {
                            ss>>fdata[i];
                            //std::cout<<"i:"<<i<<" value:"<<fdata[i]<<std::endl;
                        }
                        ss.clear();
                        #ifndef CROPSYST_VERSION
                        Tillage_Decomposition_Adjustment_Factor[layer] = 1; //note, when clearing variable value is set to equal 0
                        #endif
                        #ifndef CROPSYST_VERSION
                        //150811RLN these are never used:
                        Denitrification_Event[layer] = false;
                        Denitrification_Event_Second_Day[layer] = false;    //not "cleared" in Sub ClearStateVariables!
                        #endif
                        #ifdef CROPSYST_VERSION
                        horizon_percent_organic_matter[layer] = fdata[5];
                        organic_matter_initialization_parameters.microbial_biomass_percent[layer]   = fdata[15] * 100.;
                        organic_matter_initialization_parameters.labile_SOM_percent[layer]          = fdata[16] * 100.;
                        organic_matter_initialization_parameters.metastable_SOM_percent[layer]      = fdata[17] * 100.;
                        organic_matter_initialization_parameters.passive_SOM_percent[layer]         = fdata[18] * 100.;


                        //170404LML
                        if (!ControlRef.use_even_soil_N_and_FC) {
                            horizon_N_NO3[layer] = fdata[12];
                            horizon_N_NH4[layer] = fdata[13];
                            vwc[layer] = fdata[10];
                        } else {
                            horizon_N_NO3[layer] = 0;
                            horizon_N_NH4[layer] = 0;
                            vwc[layer] = 0;
                            double avg_avail_vwc = 0;
                            double field_capacity = SoilProfileRef.get_field_capacity_volumetric(layer);
                            double wilt_point = SoilProfileRef.get_permanent_wilt_point_volumetric(layer);
                            double avail_vwc = field_capacity - wilt_point;
                            double depth_m = SoilProfileRef.get_depth_m(layer);
                            int total_initial_layers = ControlRef.initial_N_and_water.size();
                            int layer_initial_soil = ControlRef.getInitializationLayer(depth_m, 0, total_initial_layers - 1);
                            double top_depth = (layer_initial_soil > 0) ? ControlRef.initial_N_and_water[layer_initial_soil - 1].depth : 0;
                            double bottom_depth = (layer_initial_soil > 0) ? ControlRef.initial_N_and_water[layer_initial_soil].depth : 0;
                            if ((layer_initial_soil > 0)
                                 && (layer_initial_soil <= (total_initial_layers - 1))
                                 && (depth_m <= ControlRef.initial_N_and_water[total_initial_layers - 1].depth)) {
                                double weight[2] = {0,1};                        //[0]: top; [1]: bottom
                                double depth[2] = {ControlRef.initial_N_and_water[layer_initial_soil - 1].depth,
                                                   ControlRef.initial_N_and_water[layer_initial_soil].depth};
                                double thickness = depth[1] - depth[0];
                                if (thickness > 1e-5)
                                  weight[0] = 1.0 - (depth_m - depth[0]) / thickness;
                                weight[1] = 1.0 - weight[0];
                                for (int bound = 0; bound <= 1; bound++) {
                                    horizon_N_NO3[layer] += weight[bound] * ControlRef.initial_N_and_water[layer_initial_soil - 1 + bound].NO3_N;
                                    horizon_N_NH4[layer] += weight[bound] * ControlRef.initial_N_and_water[layer_initial_soil - 1 + bound].NH4_N;
                                    avg_avail_vwc += weight[bound] * ControlRef.initial_N_and_water[layer_initial_soil -1 + bound].avail_water;
                                }
                                vwc[layer] = wilt_point + avg_avail_vwc * avail_vwc;
                            } else if (layer_initial_soil != -1) {
                                horizon_N_NO3[layer] = ControlRef.initial_N_and_water[layer_initial_soil].NO3_N;
                                horizon_N_NH4[layer] = ControlRef.initial_N_and_water[layer_initial_soil].NH4_N;
                                vwc[layer] = wilt_point + ControlRef.initial_N_and_water[layer_initial_soil].avail_water * avail_vwc;
                            } else {
                                std::cerr << "Error in initializing soil N and moisture from input file!!!\n";
                                exit(0);
                            }
                            /*std::clog << "layer:" << layer
                                      << "\tinitial_soil_layer:" << layer_initial_soil
                                      << "\tNO3:" << horizon_N_NO3[layer]
                                      << "\tNH4:" << horizon_N_NH4[layer]
                                      << std::endl;*/
                        }


                        horizon_incorporated_residue[layer] = fdata[14] / 10000.0;
                        #ifdef CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG
                        horizon_N_NO3[layer] = 1.0;
                        horizon_N_NH4[layer] = 1.0;
                        #endif
                        #else
                        Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = 0;  //not cleared in Sub ClearStateVariables!
                        Initial_OM[layer] = fdata[5];
                        Initial_Soil_Residue_Mass[layer] = fdata[14] / 10000.0; //Converts kg/ha to kg/m2
                        //FMS Apr 21, 2015 deleted this varaible, does not used
                        //Layer_Organic_Residue_Mass[layer] = Initial_Soil_Residue_Mass[layer];
                        Initial_C_Fraction_To_Microbial_Biomass[layer] = fdata[15];
                        Initial_C_Fraction_To_Active_Labile_SOM[layer] = fdata[16];
                        Initial_C_Fraction_To_Active_Metastable_SOM[layer] = fdata[17];
                        Initial_C_Fraction_To_Passive_SOM[layer] = fdata[18];
                        #endif
                        //170404LML vwc[layer] = fdata[10];
                        //DEBUG!!!
                        #if (defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_EVAPORATION_FOR_DEBUG))
                        double vwc = SoilProfileRef.get_saturation_water_content_volumetric(layer,0);
                        std::clog<<"DEBUG!!! setting saturated soil moisture for initial condition!\n";
                        #elif defined(CHECK_HOURLY_CASCADE_FOR_DEBUG)
                        double vwc = SoilProfileRef.get_field_capacity_volumetric(layer);
                        std::clog<<"DEBUG!!! setting field capacity for initial condition!\n";
                        #endif
                        #ifndef CROPSYST_HYDROLOGY
                        Old_Water_Content[layer] = Water_Content[layer];
                        New_Water_Content[layer] = Water_Content[layer];
                        #endif
                        //LML 140606 xHourly_Water_Content[layer] = fdata[10];//Water_Content[layer];
                        #ifndef CROPSYST_VERSION
                        Layer_Nitrate_N_Mass[layer] = fdata[12] / 10000.0;       //nitrate mass 3D array
                        Layer_Ammonium_N_Mass[layer] = fdata[13] / 10000.0;      //ammonium mass 3D array
                        #endif
                        #ifndef CROPSYST_VERSION
                        //NO3[layer] = fdata[12] / 10000;  //Converts kg/ha to kg/m2 - initial nitrate mass
                        Total_Nitrate_N_Mass += Layer_Nitrate_N_Mass[layer];
                        //NH4[layer] = fdata[13] / 10000;         //Converts kg/ha to kg/m2 - initial ammonium mass
                        Total_Ammonium_N_Mass += Layer_Ammonium_N_Mass[layer];
                        //2013? RS edited; was:
                        //Phosphorus(L) = Cells(StartReadRow + L, 11) / 10000 'Converts kg/ha to kg/m2
                        //Total_Phosphorus_Mass(Year, DOY) = Total_Phosphorus_Mass(Year, DOY) + Phosphorus(L)
                        //now:
                        Layer_Phosphorus_Mass[layer] = fdata[11] / 10000.0; //Converts kg/ha to kg/m2
                        Total_Phosphorus_Mass += Layer_Phosphorus_Mass[layer];
                        //end edited
                        #endif
                        //Mac_Po_Fac[layer] = 0.0;
                        //FMS Mar 12, 2015
                        //Factor_Calibration_Later_Flow[layer] = fdata[29];
                        if (layer < totallayers) {
                            std::getline(ifile,dataline);
                            ss.str(dataline);
                        }
                      }
                    } else {
                        char errormessage[200];
                        sprintf(errormessage,"Warning: Can't find keyword %s",record_key.c_str());
                        //nrerror(errormessage);
                    }
                }
            }
        }
        #ifdef CROPSYST_VERSION
        //160617LML CORN::OS::Directory_entry_name_concrete actual_residue_crop_filename(previous_residue_crop_filename,Initial_Standing_Stubble_Residue_Label);
        //160617LML previous_residue_crop_filename.set_DEN(actual_residue_crop_filename);



        //160617LML Temporary solution!!!

        //160720 I don't see what was the problem

        if (CORN::OS::file_system_engine.exists(SoilProfileRef.ControlRef.rotation_filename)) //160720RLN
        {
        const CORN::OS::Directory_name &rotation_dir = SoilProfileRef.ControlRef.rotation_filename.get_parent_directory_name_qualified().get_parent_directory_name_qualified();
        std::string database_dir(rotation_dir.c_str());
        std::string crop_file_name_with_dir = database_dir + "\\Crop\\" + Initial_Standing_Stubble_Residue_Label + ".crp";
        previous_residue_crop_filename.set_cstr(crop_file_name_with_dir.c_str());
        }
        //std::clog << "\nprevious_residue_crop_filename:\t" << previous_residue_crop_filename.c_str()
        //          << std::endl;



        stubble_residue_32 = Initial_Standing_Stubble_Residue_Mass;
        surface_residue_32 = Initial_Surface_Residue_Mass;
        #endif
    } else {
        char errormessage[200];
        sprintf(errormessage,"Can't open soil state file %s",file_name.c_str());
        nrerror(errormessage);
    }
    ifile.close();
}
//______________________________________________________________________________
