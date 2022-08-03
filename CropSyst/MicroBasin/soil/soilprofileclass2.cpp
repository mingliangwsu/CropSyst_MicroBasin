#include "soilprofileclass2.h"
#include "util/pubtools.h"
#include "util/constants.h"
#include "common/physics/standard_constants.h"
#include "math.h"
#include <math.h>
#include "stdlib.h"
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define SOIL_PARAMETER_NUMBERS_FOR_ARRAY 30
//______________________________________________________________________________
SoilProfileClass::SoilProfileClass(
        AllControlClass &_ControlRef)
    :ControlRef(_ControlRef)
#ifndef MSVB_CASCADE_INFILTRATION_HOUR
, parameters_currently_not_used(0)
, Soil_layers(/*LML 150515 (Soil_parameters_class &)*/*this)//141208 LML 141210 added the cast (Soil_parameters_class &) for gcc
, Soil_structure_common((const Soil_layers_interface &)*this)
#else
#endif
{
    //MaxLayers = _nmaxlayers;
    //NuL = soil.properties.layers.count();
    initMem();
    //assignHoursToFieldCapacity();
    //assignApparentKsat();
}
//______________________________________________________________________________
/*
void SoilProfileClass::AssignSoilProperties()
{
    //obsolete M.Liu Feb 10, 2014
    CopyValueFromSoilComplete();
    assignHoursToFieldCapacity();
    assignApparentKsat();
    CalculateNodeDepth();
}
*/
//______________________________________________________________________________
/*140511 #ifdef CROPSYST_SOIL
void SoilProfileClass::CopyValueFromSoilProperties()
{
    NuL = soil_properties_ref.get_layers()->count();
    Control_Layer = NuL;                //LML 14/04/07 soil_properties_ref does't have this value
    Water_Table_Layer = 0;              //LML 14/04/07 soil_properties_ref does't have this value
    Free_Drainage_Boundary = true;      //LML 14/04/07 soil_properties_ref does't have this value
    Manning_coef = getManningCoef();    //LML 14/04/07 soil_properties_ref does't have this value
    setSurfaceStorageCoef();
    for (int layer = 1; layer <= NuL; layer++) {
        Layer_Thickness_m[layer] = soil_properties_ref.get_layers()->get_thickness_m(layer);
        Clay_Percentage[layer] = soil_properties_ref.get_texture()->get_clay_percent(layer);
        Sand_Percentage[layer] = soil_properties_ref.get_texture()->get_sand_percent(layer);
        Soil_pH[layer] = 6.0;                   //LML 14/04/07 soil_properties_ref does't have this value
        Cation_Exchange_Capacity[layer] = 7.0;  //LML 14/04/07 soil_properties_ref does't have this value
        FC_WPot[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_water_pot_at_FC(layer);
        PWP_WPot[layer] = -1500.0;              //LML 14/04/07 soil_properties_ref does't have this value
        bulk_density_g_cm3[layer] = 1.38;          //LML 14/04/07 soil_properties_ref does't have this value
        Air_Entry_Potential[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_air_entry_potential(layer,false);
        b_Value[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_Campbell_b(layer,false);
        K_Sat[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_sat_hydraul_cond_kg_s_m3(layer);
        Saturation_Water_Content[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_saturation_water_content_volumetric(layer);
        Field_Capacity[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_field_capacity_volumetric(layer);
        Permanent_Wilting_Point[layer] = soil_properties_ref.get_hydraulic_properties_constant()->get_permanent_wilt_point_volumetric(layer);
        #ifdef OBSOLETE
        std::cout<<layer<<" clay:"<<Clay_Percentage[layer]
                   <<" Air_Entry_Potential:"<<Air_Entry_Potential[layer]
                   <<" b:"<<b_Value[layer]
                   <<" K_Sat:"<<K_Sat[layer]
                   <<" Permanent_Wilting_Point:"<<Permanent_Wilting_Point[layer]
                   <<" Field_Capacity:"<<Field_Capacity[layer]
                   <<" Saturation_Water_Content:"<<Saturation_Water_Content[layer]
                   <<std::endl;
       #endif
    }
}
#endif
*/
//______________________________________________________________________________
SoilProfileClass::~SoilProfileClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~SoilProfileClass:"<<std::endl;
#endif
    clearMem();
#ifdef Destruct_Monitor
    std::cout<<"~SoilProfileClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void SoilProfileClass::initMem()
{
    const int MaxLayers = ControlRef.getMaxSoilLayers();
    Theta_b.resize(MaxLayers,0);
#ifdef MSVB_CASCADE_INFILTRATION_HOUR
//140429 RLN this should eventually be replaced by Roger's code
    Apparent_K_Sat.resize(MaxLayers,0);           
    Hours_To_Field_Capacity .resize(MaxLayers,0); 
#endif
    K_Sat.resize(MaxLayers,0);                    
    K_Sat_Lateral_Flow.resize(MaxLayers,0);
    Ks_Unfrozen.resize(MaxLayers,0);              
    Ksat_for_Hr2FC.resize(MaxLayers,0);           
    Ksat_for_Hr2FC_Unfrozen.resize(MaxLayers,0);  
#ifndef CROPSYST_SOILFILE
    Soil_pH.resize(MaxLayers,0);                  
    Cation_Exchange_Capacity.resize(MaxLayers,0); 
    Clay_Percentage.resize(MaxLayers,0);          
    Sand_Percentage.resize(MaxLayers,0);          
    #ifdef MSVB_CASCADE_INFILTRATION_HOUR
    bulk_density_g_cm3.resize(MaxLayers,0);       
    #else
    // bulk density data is maintained by Soil_structure common.                 //140425
    #endif
    Air_Entry_Potential.resize(MaxLayers,0);          
    b_Value.resize(MaxLayers,0);                      
    //170503LML FC_WPot.resize(MaxLayers,0);
    Field_Capacity.resize(MaxLayers,0);               
    Layer_Thickness_m.resize(MaxLayers,0);            
    Permanent_Wilting_Point.resize(MaxLayers,0);      
    Saturation_Water_Content.resize(MaxLayers,0);     
#endif
    Layer_Bottom_Depth_m.resize(MaxLayers,0);         
    Lower_Node_Soil_Volume.resize(MaxLayers,0);       
    m_Value.resize(MaxLayers,0);                      
    n_Value.resize(MaxLayers,0);                      
    Node_Depth.resize(MaxLayers,0);                   
    Node_Soil_Volume.resize(MaxLayers,0);             
    PWP_WPot.resize(MaxLayers,0);                     
    Upper_Node_Soil_Volume.resize(MaxLayers,0);       
    FC_Unfrozen.resize(MaxLayers,0);                  
    PWP_Unfrozen.resize(MaxLayers,0);                 
    SAT_Unfrozen.resize(MaxLayers,0);                 
    n1_Value.resize(MaxLayers,0);                     
    B_Inverse.resize(MaxLayers,0);                    
#ifdef FROZEN_SOIL
    ice_content.resize(MaxLayers,0);
#endif
}
//
//______________________________________________________________________________
void SoilProfileClass::clearMem()
{
}
//______________________________________________________________________________
//

/*131122 RLN This is now obsolete because Apparent_K_Sat is currently
 being calculated as needed, it will also be handled by the
 hourly cascade model.
*/
//______________________________________________________________________________
double SoilProfileClass::calc_h_Theta_b(double Air_Entry)
{
    //using empirical function to calculate h(Theta_b)
    //air_entry [J/kg] - updated from (cm)
    double h_Theta_b(0);
    if (Air_Entry < -7.7) h_Theta_b = -10;
    else
        h_Theta_b = -(-0.0179 * pow((Air_Entry * (-10.0)),2) + 2.67 * (Air_Entry * (-10.0))) 
                    / 10.0;
    return h_Theta_b;
}
//______________________________________________________________________________
double SoilProfileClass::calcTheta_h_Campbell(double h, double Air_Entry,
  double Theta_s, double Campbell_b)
{
    //air_entry [J/kg]
    //Theta_s [cm/cm]
    //Campbell b [unitless]
    //h [J/kg] negative values
    double Theta_h_Campbell(0);
    if (h > Air_Entry) Theta_h_Campbell = Theta_s;
    else Theta_h_Campbell = Theta_s * pow((Air_Entry / h),(1.0 / Campbell_b));
    return Theta_h_Campbell;
}
//______________________________________________________________________________
/*
void SoilProfileClass::assignParametersValues(bool FC_PWP_based)
{
    //Need check which b_value should be used!!!
    double h;
    setManningCoef();
    setSurfaceStorageCoef();
    for (int i = 1; i <= NuL; i++) {
        h = calc_h_Theta_b(Air_Entry_Potential[i]);//soil.properties.hydraulics.get_air_entry_potential(i,FC_PWP_based));
        Theta_b[i] = calcTheta_h_Campbell(h,Air_Entry_Potential[i],Saturation_Water_Content[i],b_Value[i]);
                                          //soil.properties.hydraulics.get_air_entry_potential(i,FC_PWP_based)
                                          //,soil.properties.hydraulics.get_saturation_water_content_volumetric(i)
                                          //,soil.properties.hydraulics.get_Campbell_b(i,FC_PWP_based));
    }
}
*/
//______________________________________________________________________________
void SoilProfileClass::setManningCoef()
{
    switch(soilID) {
    case 1: Manning_coef = 0.04;
        break;
    default: Manning_coef = 0.04;
        break;
    }
}
//______________________________________________________________________________
void SoilProfileClass::setSurfaceStorageCoef()
{
    switch(soilID) {
    case 1: SurfaceStorage = 0.0;       //(mm)
        break;
    default: SurfaceStorage = 0.0;
        break;
    }
}
//______________________________________________________________________________
void SoilProfileClass::setSoilID(int _soilID) {soilID = _soilID;}
int SoilProfileClass::getSoilID() {return soilID;}
//______________________________________________________________________________
double SoilProfileClass::calHoursToFieldCapacity(double Percent_Clay)
{
    //Verhulst-Pearl: f(t)=L0/(L0+(Lm-L0)*e^-rt)

    const double L0 = 0.05;      // //initial value
    const double Lm = 1.0;         // //max_value
    double x_known = (Lm + L0) / 1.1;
    const double rtm = 70.0 / 2.0;
    double xR = x_known / Lm;
    //calculating r based on the known values
    double r = -(1.0 / rtm) * log(((L0 / xR) - L0) / (Lm - L0));
    double Tt = (Percent_Clay - 12.0);
    double HTFC = (L0 / (L0 + (Lm - L0) * exp(-r * Tt))) * 20.0 * 24.0;
    /*std::cout<<" Percent_Clay:"<<Percent_Clay
            <<"HoursToFieldCapacity:"<<HTFC
              <<std::endl;*/
    if (HTFC < 24) HTFC = 24;
    return HTFC;
}
//______________________________________________________________________________
int SoilProfileClass::NumberOfLayers()
{
    return NuL;
}
//______________________________________________________________________________
#ifdef CROPSYST_SOILFILE
float32 consistent_layer_thickness[14] =
{ 0,   0.05,0.05,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.3,0.3,    0};
bool SoilProfileClass::initialize_soil_parameters(const Soil_parameters_class &soil_parameters)modification_
{
   clear();
   float64 layer_center_depth = consistent_layer_thickness[1] / 2.0;
   float64 last_layer_bottom_depth = 0;
   NuL = number_horizons = 12;
   SurfaceStorage = m_to_mm(soil_parameters.surface_storage_mm_32);
   /* Not applicable
   evaporative_layer_thickness_cascade             =
   evaporative_layer_thickness_finite_difference   =
   hydrologic_group_labeled
   hydrologic_condition_labeled
   override_curve_number_16
   user_fallow_curve_number_16
   steepness_percent
   slope_length
   albedo_dry
   albedo_wet
   water_vapor_conductance_atmosphere_adj
   SLPF_CropGro
   */
//   float64 horizon_top_depth = 0.0;
   float64 parameters_profile_depth = soil_parameters.get_horizon_depth(soil_parameters.number_horizons);
   for (nat8 layer = 1; layer <=number_horizons; layer++)
   {
      nat8 from_horizon = soil_parameters.get_horizon_at(layer_center_depth);


      if (last_layer_bottom_depth > parameters_profile_depth)
      {
      horizon_bulk_density_g_cm3    [layer] = 1.5;
      horizon_permanent_wilt_point  [layer] = 0.025;
      horizon_field_capacity        [layer] = 0.05;
      water_pot_at_FC               [layer] = 0.0;
      horizon_sand                  [layer] = 5.0;
      horizon_clay                  [layer] = 90.0;
      horizon_silt                  [layer] = 5.0;
      sat_hydraul_cond_m_d          [layer] = 0.000001;
      horizon_saturation_WC         [layer] = 0.06;
      horizon_air_entry_pot         [layer] = -0.05;
      horizon_Campbell_b            [layer] = 4.0;
      pH                            [layer] = 7.0;
      cation_exchange_capacity      [layer] = 1.0;
      organic_matter                [layer] = 0.0;
      }
      else
      {
      horizon_bulk_density_g_cm3    [layer] = soil_parameters.get_horizon_bulk_density_g_cm3                (from_horizon);
      horizon_permanent_wilt_point  [layer] = soil_parameters.get_horizon_permanent_wilt_point_volumetric   (from_horizon);
      horizon_field_capacity        [layer] = soil_parameters.get_horizon_field_capacity_volumetric         (from_horizon);
      water_pot_at_FC               [layer] = soil_parameters.water_pot_at_FC                               [from_horizon];
      horizon_sand                  [layer] = soil_parameters.get_horizon_sand                              (from_horizon);
      horizon_clay                  [layer] = soil_parameters.get_horizon_clay                              (from_horizon);
      horizon_silt                  [layer] = soil_parameters.get_horizon_silt                              (from_horizon);
      sat_hydraul_cond_m_d          [layer] = soil_parameters.get_horizon_sat_hydraul_cond_m_d              (from_horizon);
      horizon_saturation_WC         [layer] = soil_parameters.get_horizon_saturation_WC                     (from_horizon);
      horizon_air_entry_pot         [layer] = soil_parameters.get_horizon_air_entry_pot                     (from_horizon);
      horizon_Campbell_b            [layer] = soil_parameters.get_horizon_Campbell_b                        (from_horizon);
      pH                            [layer] = soil_parameters.get_pH                                        (from_horizon);
      cation_exchange_capacity      [layer] = soil_parameters.get_cation_exchange_capacity                  (from_horizon);
      organic_matter                [layer] = soil_parameters.organic_matter                                [from_horizon];

      };

      /* Not applicable
      organic_matter_low            [layer] =
      organic_matter_high           [layer] =
      bypass_coef                   [layer] =  get_horizon_bypass_coef
      */

      horizon_thickness[layer] = consistent_layer_thickness[layer];

      // Calculated:
      K_Sat[layer] =                                                                                                                           //051205
                CORN::is_approximately<float32>(sat_hydraul_cond_m_d[layer],0.0,0.000001)                                                                                              //980526
                ? 1.0e-3 / CORN_sqr(horizon_air_entry_pot[layer]) //saturated hydraulic conductivity, Kgsec/m3                                                       //990331
                : sat_hydraul_cond_m_d[layer] / (
                standard_gravity
                * 86.4); // convert to flux unit?                                                                                    //980526
        PWP_WPot[layer] = -1500;    //test only!
        if (CORN::is_approximately<float32>(water_pot_at_FC[layer],0.0,0.000001))
            water_pot_at_FC[layer] = -33.0;
      last_layer_bottom_depth += consistent_layer_thickness[layer];
      layer_center_depth = last_layer_bottom_depth + (consistent_layer_thickness[layer+1]/2.0);
//      horizon_top_depth += soil_parameters.horizon_thickness[from_horizon];
   }
   Manning_coef = 0.04;            //test only!
   Free_Drainage_Boundary =
           #ifdef NONE_DRINAGE
           false;
           #else
           true;  //test only!
           #endif
   Water_Table_Layer = NuL;        //test only!
   return true;
}
//_2014-12-09_RLN______________________________________________________________/

/*141209
void SoilProfileClass::get_end()
{
    NuL = number_horizons;                                                       //141209RLN
    for (int layer=1; layer <= number_horizons; layer++) {                           //141209RLN
        K_Sat[layer] =                                                                                                                           //051205
                CORN::is_approximately<float32>(sat_hydraul_cond_m_d[layer],0.0,0.000001)                                                                                              //980526
                ? 1.0e-3 / CORN_sqr(horizon_air_entry_pot[layer]) //saturated hydraulic conductivity, Kgsec/m3                                                       //990331
                : sat_hydraul_cond_m_d[layer] / (
                standard_gravity                                                        //140418
                * 86.4); // convert to flux unit?                                                                                    //980526
        PWP_WPot[layer] = -1500;    //test only!
        if (CORN::is_approximately<float32>(water_pot_at_FC[layer],0.0,0.000001))//141209RLN
            water_pot_at_FC[layer] = -33.0;                                      //141209RLN
    }
    SurfaceStorage = 0.0;           //default
    Manning_coef = 0.04;            //test only!
    Free_Drainage_Boundary = true;  //test only!
    Water_Table_Layer = NuL;        //test only!
}
*/
#else
void SoilProfileClass::ReadSoilProfileParameters
(const CORN::OS::File_name &file_name)                                           //160307RLN
//160307(int SoilID)
{
   //160307RLN std::string file_name = FindSoilProfileFileName(SoilID);
#ifdef LIU_DEBUG
    //std::cout<<"Soil Profile name:"<<file_name<<std::endl;
#endif
    std::ifstream ifile(file_name.c_str());
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
                //std::cout<<"Key:"<<record_key<<" Data:"<<dataline<<std::endl;
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    char errormessage[200];
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Soil_Profile_Num_Layers") == 0) {
                        ss>>NuL;
                    } else if (record_key.compare("Soil_Profile_Control_Chemical") == 0) {
                        //ss>>Control_Layer;
                        ss>>Control_Layer;
                    } else if (record_key.compare("Water_Table_At_Layer") == 0) {
                        //ss>>Water_Table_Layer;
                        ss>>Water_Table_Layer;
                    } else if (record_key.compare("Free_Drainage") == 0) {
                        //ss>>Free_Drainage_Boundary;
                        ss>>Free_Drainage_Boundary;
                    } else if (record_key.compare("Surface_Water_Store") == 0) {
                        ss>>SurfaceStorage;
                    } else if (record_key.compare("Manning_Coef") == 0) {
                        ss>>Manning_coef;
                    } else if (record_key.compare("Max_Number_Of_Layer_Pot_Explored_By_Roots") == 0) {
                        ss>>Max_Number_Of_Layer_Pot_Explored_By_Roots;
                        if (Max_Number_Of_Layer_Pot_Explored_By_Roots > NuL)
                            Max_Number_Of_Layer_Pot_Explored_By_Roots = NuL;
                    } else if (record_key.compare("Layer")  == 0 ||
                               record_key.compare("Layers") == 0) {
                      bool multilayer = (record_key.compare("Layers") == 0);
                      int totallayers = layer + 1;
                      if (multilayer) totallayers = NuL;
                      while (layer < totallayers) {
                        layer++;
                        double fdata[SOIL_PARAMETER_NUMBERS_FOR_ARRAY];
                        for (int i = 1; i <= SOIL_PARAMETER_NUMBERS_FOR_ARRAY-1; i++) {
                            ss>>fdata[i];
                        }
                        ss.clear();
                        Layer_Thickness_m[layer] = fdata[2];
                        Sand_Percentage[layer] = fdata[3];
                        Clay_Percentage[layer] = fdata[4];
                        Soil_pH[layer] = fdata[6];
                        Cation_Exchange_Capacity[layer] = fdata[7];
                        //170503LML FC_WPot[layer] = fdata[8];
                        water_pot_at_FC[layer] = fdata[8];
                        PWP_WPot[layer] = fdata[9];
                        //all parameers come from parameter file M.Liu
                        bulk_density_g_cm3[layer] = fdata[20];
                        Air_Entry_Potential[layer] = fdata[21];
                        b_Value[layer] = fdata[22];
                        K_Sat[layer] = fdata[23];
                        Saturation_Water_Content[layer] = fdata[24];
                        Field_Capacity[layer] = fdata[25];
                        Permanent_Wilting_Point[layer] = fdata[26];
                        K_Sat_Lateral_Flow[layer] = fdata[29];                   //150518
                        assert(Saturation_Water_Content[layer] > Field_Capacity[layer] &&
                               Field_Capacity[layer] > Permanent_Wilting_Point[layer]);
                        if (layer < totallayers) {
                            dataline.clear();
                            std::getline(ifile,dataline);
                            ss.str(dataline);
                        }
                        estimateSoilProfileProperties();                         //170404LML
                      }
                    } else {
                        char errormessage[200];
                        sprintf(errormessage,"Warning: Cann//t find keyword %s",record_key.c_str());
                        //nrerror(errormessage);
                    }
                }
            }
        }
    } else {
        char errormessage[200];
        sprintf(errormessage,"Cann't open file %s",file_name.c_str());
        nrerror(errormessage);
    }
    ifile.close();
}
#endif

//______________________________________________________________________________
/*160307RLN obsolete, now composing the soil filename in BasinClass
std::string SoilProfileClass::FindSoilProfileFileName(int SoilID)
{
   // The soils profile and the soil state were actually the same
   // Now this is stored in soil_filename
   // Eventually the file will use CropSyst file format.
   std::string soil_profile_ID;
   //CORN::wstring_to_string(ControlRef.soil_filename.get_name(),soil_profile_ID); //150917RLN
   //150917RLN CORN::wstring_to_string(ControlRef.soilproperty_filename.get_name(),soil_profile_ID);
   CORN::append_nat16_to_string((nat16)SoilID, soil_profile_ID);
   CORN::OS::File_name_concrete soil_profile_filename
      (ControlRef.soil_filename.get_parent_directory_name_qualified()            //150917RLN
      ,soil_profile_ID

      // Currently we are still using soil state file format
      // Eventually this will be replaced with CropSyst soil parameter files
      // so this will be the default common simulation file name
      ,"SoilState"
      // 150917 ,ControlRef.soil_filename.get_extension()


      );                                //150917RLN
   std::string result(soil_profile_filename.c_str());
   return result;
}
*/
//______________________________________________________________________________
void SoilProfileClass::estimateSoilProfileProperties()
{
    //double a_value;
    //const double WD = 1000; //water density
    Layer_Bottom_Depth_m[0] = 0.;
    for (nat8 L = 1; L <= NuL; L++) {
        ////Sa_nd(L) = Sand(L)
#ifndef CROPSYST_SOILFILE
        double Silt_percent = 100 - Sand_Percentage[L] - Clay_Percentage[L];
#endif
        Layer_Bottom_Depth_m[L] = Layer_Bottom_Depth_m[L - 1] + get_thickness_m(L);
        //EstimateHydraulicProperties(Sand_Percentage[L], Clay_Percentage[L]);
        //Saturation_Water_Content[L] = est_Saturation_WC;
        //bulk_density_g_cm3[L] = est_Bulk_Density;
        //Air_Entry_Potential[L] = est_Air_Entry_Potential;
        //b_Value[L] = est_B_value;
        //K_Sat[L] = est_K_Sat;
        //est_Wat_Pot_FC = calcSoilWaterPotentialAtFC(Clay_Percentage[L], Silt_percent);
        //FC_WPot[L] = est_Wat_Pot_FC;
        //a_value = 100 * exp(-4.396 - 0.0715 * Clay_Percentage[L]
                            //- 0.000488 * pow(Sand_Percentage[L],2)
                            //- 0.00004285 * pow(Sand_Percentage[L],2) * Clay_Percentage[L]);
        //FC(L) = est_Saturation_WC * (est_Air_Entry_Potential / est_Wat_Pot_FC) ^ (1 / est_B_value)
        //RS: above can be simplified to:
        //Field_Capacity[L] = pow((-a_value / est_Wat_Pot_FC), (1 / est_B_value));
        //est_Wat_Pot_PWP = -1500;
        //PWP_WPot[L] = est_Wat_Pot_PWP;
        //Permanent_Wilting_Point[L] = est_Saturation_WC * pow((est_Air_Entry_Potential / est_Wat_Pot_PWP), (1 / est_B_value));
        m_Value[L] = 2.0 * get_Campbell_b(L,UNKNOWN_FC_PWP_based) + 3.0;
        n_Value[L] = 2.0 + 3.0 / get_Campbell_b(L,UNKNOWN_FC_PWP_based);
        //Hours_To_Field_Capacity(L) = CalculateHoursToFieldCapacity(est_Wat_Pot_FC) // FMS removed 10/24/2013
        #ifdef MSVB_CASCADE_INFILTRATION_HOUR
        Hours_To_Field_Capacity[L] = calHoursToFieldCapacity(Clay_Percentage[L]);
        #endif
        //double t = get_air_entry_potential(L,UNKNOWN_FC_PWP_based);
        //double tt = calc_h_Theta_b(get_air_entry_potential(L,UNKNOWN_FC_PWP_based));
        //double t4 = ice_content[1];
        //double ttt = get_saturation_water_content_volumetric(L,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);
        double air_entry_potential = get_air_entry_potential(L,UNKNOWN_FC_PWP_based);
        Theta_b[L] = calcTheta_h_Campbell(calc_h_Theta_b(air_entry_potential), 
                                          air_entry_potential, 
                                          get_saturation_water_content_volumetric(L,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822), 
                                          get_Campbell_b(L,UNKNOWN_FC_PWP_based));
        #ifdef MSVB_CASCADE_INFILTRATION_HOUR
        Ksat_for_Hr2FC[L] = calcK_satForHr2FC(L);
        #endif
        //save unfrozen Ks, FC, PWP and saturated water content (porosity)
        Ksat_for_Hr2FC_Unfrozen[L] = Ksat_for_Hr2FC[L];
        Ks_Unfrozen[L] = K_Sat[L];
        #ifdef CROPSYST_SOILFILE
        FC_Unfrozen[L] = horizon_field_capacity[L];
        PWP_Unfrozen[L] = horizon_permanent_wilt_point[L];
        SAT_Unfrozen[L] = horizon_saturation_WC[L];
        #else
        FC_Unfrozen[L] = Field_Capacity[L];
        PWP_Unfrozen[L] = Permanent_Wilting_Point[L];
        SAT_Unfrozen[L] = Saturation_Water_Content[L]; 
        #endif
    }
    //RS: below additional parameters are calculated for the FD-routine
    NLmax = NuL + 2; //Two extra soil layers to extend the soil profile for better free drainage boundary
                    // condition plus one additional layer to provide soil properties to the last effective
                    // node with free drainage BC
    Number_Of_Total_Nodes = NuL + 3; //The actual last effective node with free drainage BC is equal to NLmax. The extra node is needed
                    // only to calculate domain thickness of the last effective node when free drainage BC is used
   #ifdef MBVB_FD
    if (Free_Drainage_Boundary) {
        Water_Table_Boundary = false;
        Number_Of_Effective_Soil_Layers = NuL + 2; //number of effective soil layers (free drainage condition)
        Number_Of_Uninundated_Soil_Layers = NuL; //Number of real soil layers free of water table
    } else {
        Water_Table_Boundary = true;
        Number_Of_Effective_Soil_Layers = Water_Table_Layer - 1;  //m is the number of effective layers. Layers below this are at or below water table depth
        Number_Of_Uninundated_Soil_Layers = Number_Of_Effective_Soil_Layers; //Number of real soil layers free of water table
    }
    Number_Of_Effective_Soil_Nodes = Number_Of_Effective_Soil_Layers + 1; //number of effective nodes
    #endif
    for (int layer = NuL + 1; layer <= Number_Of_Total_Nodes;         layer++) {
#ifdef CROPSYST_SOILFILE
        horizon_thickness           [layer] = horizon_thickness             [layer-1];
        horizon_bulk_density_g_cm3  [layer] = horizon_bulk_density_g_cm3    [layer-1];  //140502
        set_bulk_density_g_cm3(layer,horizon_bulk_density_g_cm3[layer-1]);
        horizon_air_entry_pot       [layer] = horizon_air_entry_pot[layer-1];
        horizon_Campbell_b          [layer] = horizon_Campbell_b[layer-1];
        horizon_sand                [layer] = horizon_sand                  [layer-1]; //141209RLN
        horizon_clay                [layer] = horizon_clay                  [layer-1];
        pH                          [layer] = pH                            [layer-1]; //141209RLN
        cation_exchange_capacity    [layer] = cation_exchange_capacity      [layer-1]; //141209RLN
        water_pot_at_FC             [layer] = water_pot_at_FC               [layer-1]; //141209RLN
        horizon_field_capacity      [layer] = horizon_field_capacity        [layer-1];
        horizon_permanent_wilt_point[layer] = horizon_permanent_wilt_point  [layer-1];
        horizon_saturation_WC       [layer] = horizon_saturation_WC         [layer-1];
        #else
        Layer_Thickness_m        [layer] = Layer_Thickness_m         [layer-1];
        bulk_density_g_cm3       [layer] = bulk_density_g_cm3        [layer-1];  //140502
        Air_Entry_Potential      [layer] = Air_Entry_Potential       [layer-1];
        b_Value                  [layer] = b_Value                   [layer-1];
        Clay_Percentage          [layer] = Clay_Percentage           [layer-1];
        Field_Capacity           [layer] = Field_Capacity            [layer-1];
        Permanent_Wilting_Point  [layer] = Permanent_Wilting_Point   [layer-1];
        Saturation_Water_Content [layer] = Saturation_Water_Content  [layer-1];
        // The following were added by RLN                                       //141209
        //170503LML FC_WPot                  [layer] = FC_WPot                     [layer-1];
        water_pot_at_FC          [layer] = water_pot_at_FC             [layer-1]; //170503LML
        PWP_WPot                 [layer] = PWP_WPot                    [layer-1];
        Soil_pH                  [layer] = Soil_pH                     [layer-1];
        Cation_Exchange_Capacity [layer] = Cation_Exchange_Capacity    [layer-1];
#endif
        FC_Unfrozen[layer] = FC_Unfrozen[layer-1];
        PWP_Unfrozen[layer] = PWP_Unfrozen[layer-1];
        SAT_Unfrozen[layer] = SAT_Unfrozen[layer-1];
        Ks_Unfrozen[layer] = Ks_Unfrozen[layer-1];
        Theta_b[layer] = Theta_b[layer-1];
        Ksat_for_Hr2FC_Unfrozen[layer] = Ksat_for_Hr2FC_Unfrozen[layer-1];
        m_Value                  [layer] = m_Value                   [layer-1];  //LML 14/04/18
        K_Sat                    [layer] = K_Sat                     [layer-1];
        n_Value                  [layer] = n_Value[layer-1];        //2.0 + 3.0 / get_Campbell_b(layer,UNKNOWN_FC_PWP_based);
        n1_Value                 [layer] = n1_Value[layer-1];       //1.0 - n_Value             [layer];
        B_Inverse                [layer] = B_Inverse[layer-1];      //1.0 / get_Campbell_b(layer,UNKNOWN_FC_PWP_based);
        #ifdef MSVB_CASCADE_INFILTRATION_HOUR
        Hours_To_Field_Capacity  [layer] = Hours_To_Field_Capacity   [layer-1];  //LML 14/04/18
        Ksat_for_Hr2FC[layer] = Ksat_for_Hr2FC[layer-1];
        #endif
    }
    #ifdef MBVB_FD
    //Determine depth from the soil surface of each node. This is done for a number of nodes equal to
    //number of real soil layers + 2 extra layers for free drainage + 1 artificial layer for last maximum
    //number of nodes active in FD solution + 1 (one node more than layers)
    CalculateNodeDepth();

    //Determine soil thickness of influence for each node (node domain)
    //z(L) is the depth of node L measured from soil surface
    //Water density (wd) is added for convenience only, but has no physical
    //meaning here. The last node (NNmax) is never part of the FD solution
    for (int layer = 1; layer <= Number_Of_Total_Nodes; layer++) {
        Node_Soil_Volume[layer] = WD * (Node_Depth[layer + 1] - Node_Depth[layer - 1]) / 2.0;
    }
    //Determine thickness of upper and lower element in each soil layer
    for (int layer = 1; layer <= Number_Of_Total_Nodes; layer++) {
        Upper_Node_Soil_Volume[layer] = WD * get_thickness_m(layer) / 2.0;
        Lower_Node_Soil_Volume[layer] = WD * get_thickness_m(layer) / 2.0;
    }
   #endif
#ifdef MSVB_CASCADE_INFILTRATION_HOUR
//140429 RLN this should eventually be replaced by Roger's code
   assignApparentKsat();
#endif
}
//______________________________________________________________________________
void SoilProfileClass::CalculateNodeDepth()
{
    Node_Depth[0] = 0;
    Node_Depth[1] = 0;
    for (int L = 1;L <= Number_Of_Total_Nodes; L++) {
        Node_Depth[L+1] = Node_Depth[L] + get_thickness_m(L);
    }
}
//______________________________________________________________________________
void SoilProfileClass::EstimateHydraulicProperties(double Sand,double Clay)
{
//RLN 140506    const double G = 9.81;              //  //gravitational acceleration (m/s2)
    const double Water_Density = 1000;  //  // (kg/m3)
    ////RS added
    double temp_Clay(0);
    if (Clay > 60) {
        temp_Clay = Clay;
        Clay = 60;
    }
    else temp_Clay = Clay;
    //Calculate saturation water content (m3/m3)
    est_Saturation_WC = 0.332 - 0.0007251 * Sand + (log(temp_Clay) / log(10.0)) * 0.1276;
    //Calculate bulk density (Mg/m3)
    est_Bulk_Density = 2.65 * (1 - est_Saturation_WC);
    //Calculate a value
    est_A_Value = 100 * exp(-4.396 - 0.0715 * Clay - 0.000488 * Sand * Sand - 0.00004285 * Sand * Sand * Clay);
    //Calculate b value
    est_B_value = -(-3.14 - 0.00222 * Clay * Clay - 0.00003484 * Sand * Sand * Clay);
    //Calculate Air Entry Potential
    est_Air_Entry_Potential = -est_A_Value * pow(est_Saturation_WC, (-est_B_value));
    //RS added - this addition makes sure that the Ksat value for clay contents above ~55 % does not start increasing
    // the addition will decrease Ksat starting from the lowest Saxton-Ksat linearly down to 0 at 100 % clay
    double ClayMin = ClayContentForMinimumKsat(Sand);
    double reductionFactor(0);
    if (temp_Clay > ClayMin) {
        reductionFactor = 1 - (temp_Clay - ClayMin) / (100.0 - ClayMin);
        temp_Clay = ClayMin;
    }
    else reductionFactor = 1;
    //end added
    //Calculate saturated hydraulic conductivity (kg s/m3); RS added //reductionFactor//
    double Factor = Water_Density / (standard_gravity * 100.0 * 3600.0);  //converts cm/h to Kg s / m3 //140506 RLN
    est_K_Sat = Factor * reductionFactor * exp(12.012 - 0.0755 * Sand
                + (-3.895 + 0.03671 * Sand - 0.1103 * temp_Clay + 0.00087546 * temp_Clay * temp_Clay) * (1.0 / est_Saturation_WC));
}
//______________________________________________________________________________
double SoilProfileClass::ClayContentForMinimumKsat(double Sand)
{
    //based on the saxton equation, this empirical linear relationship between sand and clay makes sure that Ksat is the lowest possible
    double Clay_Content_For_Minimum_Ksat(0);
    if (Sand > 43) Clay_Content_For_Minimum_Ksat = 100 - Sand;
    else Clay_Content_For_Minimum_Ksat = 0.0332 * Sand + 55.458;
    return Clay_Content_For_Minimum_Ksat;
}
//______________________________________________________________________________
double SoilProfileClass::calcSoilWaterPotentialAtFC(double Clay_percent, double Silt_percent)
{
    //(kPa)
    //this is an improved empirical equation that may substitute the old Ln equation that was somewhat limited
    const double a = 0.0044;
    const double b = -0.78;
    const double C = -16;
    const double s_shape = 4;
    double Soil_Water_Potential_At_FC = a * pow(Clay_percent,2) 
                                        + b * Clay_percent 
                                        + C 
                                        + pow((Silt_percent / 93.5),s_shape) * C;
    return Soil_Water_Potential_At_FC;
}
//______________________________________________________________________________
double SoilProfileClass::getTotoalSoilDepth_m()                            const //140429 made const
{
    return Layer_Bottom_Depth_m[NuL];
}
//______________________________________________________________________________
void SoilProfileClass::copy_soilprofile(SoilProfileClass &copy_from) {

    //LML 140815
    soilID = copy_from.getSoilID();
    NuL = copy_from.NumberOfLayers();
    Manning_coef = copy_from.Manning_coef;
    SurfaceStorage = copy_from.SurfaceStorage;
    Free_Drainage_Boundary = copy_from.Free_Drainage_Boundary;
    Water_Table_Layer = copy_from.Water_Table_Layer;
    Control_Layer = copy_from.Control_Layer;
    Max_Number_Of_Layer_Pot_Explored_By_Roots = copy_from.Max_Number_Of_Layer_Pot_Explored_By_Roots; //150526
    for (int layer = 1; layer <= NuL; layer++) {
#ifdef CROPSYST_SOILFILE
        horizon_thickness           [layer] = copy_from.horizon_thickness           [layer];
        //set_sand_clay(layer,copy_from.horizon_sand[layer],copy_from.horizon_clay[layer]);
        horizon_sand                [layer] = copy_from.horizon_sand                [layer];
        horizon_clay                [layer] = copy_from.horizon_clay                [layer];
        pH                          [layer] = copy_from.pH                          [layer];
        cation_exchange_capacity    [layer] = copy_from.cation_exchange_capacity    [layer];
        water_pot_at_FC             [layer] = copy_from.water_pot_at_FC             [layer];
        horizon_air_entry_pot       [layer] = copy_from.horizon_air_entry_pot       [layer];
        horizon_Campbell_b          [layer] = copy_from.horizon_Campbell_b          [layer];
        horizon_bulk_density_g_cm3  [layer] = copy_from.horizon_bulk_density_g_cm3  [layer];//141209RLN
        set_bulk_density_g_cm3(layer,copy_from.horizon_bulk_density_g_cm3  [layer]);
        horizon_field_capacity      [layer] = copy_from.horizon_field_capacity      [layer];
        horizon_permanent_wilt_point[layer] = copy_from.horizon_permanent_wilt_point[layer];
        horizon_saturation_WC       [layer] = copy_from.horizon_saturation_WC       [layer];
        sat_hydraul_cond_m_d        [layer] = copy_from.sat_hydraul_cond_m_d        [layer];//141209RLN
        organic_matter              [layer] = copy_from.organic_matter              [layer];//141209RLN
        // Organic matter low and high are not copied because they
        // are not used in this mode (informational from STATSGO2).
#else
        Layer_Thickness_m           [layer] = copy_from.Layer_Thickness_m[layer];
        Sand_Percentage             [layer] = copy_from.Sand_Percentage[layer];
        Clay_Percentage             [layer] = copy_from.Clay_Percentage[layer];
        Soil_pH                     [layer] = copy_from.Soil_pH[layer];
        Cation_Exchange_Capacity    [layer] = copy_from.Cation_Exchange_Capacity[layer];
        //170503LML FC_WPot                     [layer] = copy_from.FC_WPot[layer];
        water_pot_at_FC             [layer] = copy_from.water_pot_at_FC[layer];
        Air_Entry_Potential         [layer] = copy_from.Air_Entry_Potential[layer];
        b_Value                     [layer] = copy_from.b_Value[layer];
        bulk_density_g_cm3          [layer] = copy_from.bulk_density_g_cm3[layer];
        Field_Capacity              [layer] = copy_from.Field_Capacity[layer];
        Permanent_Wilting_Point     [layer] = copy_from.Permanent_Wilting_Point[layer];
        Saturation_Water_Content    [layer] = copy_from.Saturation_Water_Content[layer];
#endif
        K_Sat_Lateral_Flow          [layer] = copy_from.K_Sat_Lateral_Flow[layer]; //150611 LML
        PWP_WPot[layer] = copy_from.PWP_WPot[layer];
        //all parameers come from parameter file M.Liu
        K_Sat[layer] = copy_from.K_Sat[layer];
    }
    //copy(copy_from);    //copy Soil_structure_common structure LML 140815 need check with Roger!!!
    estimateSoilProfileProperties();
}
//______________________________________________________________________________
#ifndef MSVB_CASCADE_INFILTRATION_HOUR
bool SoilProfileClass::initialize()
{
   //RLN NYN Soil_layers::initialize();
   //RLN NYN    Soil_texture_interface::initialize();
   //RLN NYN    Soil_hydraulic_properties_interface::initialize();
   //RLN NYN    Soil_structure_common::initialize();
    return true;
}
//_2014-05-06___________________________________________________________________

//140424 These functions are here temporarily until we clean up the soil layers in Mingliang's code
// These functions are calling assert to see if they are actually needed/used yet
 // Soil layering interface methods
nat8   SoilProfileClass::get_max_number_layers()                           const { return ControlRef.getMaxSoilLayers(); }
nat8   SoilProfileClass::get_number_layers()                               const
{
    return NuL;
}
//______________________________________________________________________________
inline float64 SoilProfileClass::get_saturation_water_content_volumetric( nat8 layer, float64 current_ice_water_content) const{
     double c_ice_content(0);
     #ifdef FROZEN_SOIL
     if (current_ice_water_content == 0.0)
         c_ice_content = layer <= NuL ? ice_content[layer]:ice_content[NuL];
     else if (current_ice_water_content > 0.0)
         c_ice_content = current_ice_water_content;
     #else
     c_ice_content = current_ice_water_content;
     #endif
#ifdef CROPSYST_SOILFILE
     assert((get_horizon_saturation_WC(layer) - c_ice_content) >= 0);
     return (get_horizon_saturation_WC(layer) - c_ice_content);       //LML 140820: should be fixed after implementaing freezing class
#else
     assert((Saturation_Water_Content[layer] - c_ice_content) >= 0);
     return (Saturation_Water_Content[layer] - c_ice_content);       //LML 140820: should be fixed after implementaing freezing class
#endif
}
//______________________________________________________________________________
#ifdef FROZEN_SOIL
void SoilProfileClass::setIceContentRef(std::vector<double> &_ice_content)
{              //LML 140820
    int size = std::min<int>(_ice_content.size(),ice_content.size());
    for (int i = 0; i < size; i++)
      ice_content[i] = _ice_content[i];
}
//______________________________________________________________________________
double SoilProfileClass::getIceContentAtLayer(int layer) {return ice_content[layer];}
#endif

//______________________________________________________________________________
/*
nat8   SoilProfileClass::get_layer_at_depth(float64 a_given_depth_m)              const { assert(false); return 0; }
nat8   SoilProfileClass::get_layer_at_depth_or_last_layer(float64 a_given_depth_m)const { assert(false); return 0; }
nat8   SoilProfileClass::get_horizon_at_layer(nat8 layer)                         const { assert(false); return 0; }
float64 SoilProfileClass::get_thickness_m                      (nat8  layer)      const { assert(false); return 0; }
float64 SoilProfileClass::get_depth_m(nat8  layer = 0)                            const { assert(false); return 0; }
float64 SoilProfileClass::get_depth_profile_m                  ()                 const { assert(false); return 0; }
nat8    SoilProfileClass::closest_layer_at(float64 a_given_depth)                 const { assert(false); return 0; }
void SoilProfileClass::copy_array64(soil_layer_array64(target),const soil_layer_array64(source)) const { assert(false); }
void SoilProfileClass::copy_array32(soil_layer_array32(target),const soil_layer_array32(source)) const { assert(false); }

#ifdef USE_VARIABLE_RECORDERS
bool SoilProfileClass::render_variable_recorders
      (CS::Variable_recorders &recorders
      ,nat32 desired_descriptive_summary_elements)                { assert(false); return 0; } //130924
#endif
 // Soil_hydraulic_properties_interface methods
float64 SoilProfileClass::get_field_capacity_volumetric             ( nat8 layer) const { assert(false); return 0; }
float64 SoilProfileClass::get_permanent_wilt_point_volumetric       ( nat8 layer) const { assert(false); return 0; }
float64 SoilProfileClass::get_drained_upper_limit_volumetric        ( nat8 layer) const { assert(false); return 0; }
float64 SoilProfileClass::get_lower_limit_volumetric                ( nat8 layer) const { assert(false); return 0; }
float64 SoilProfileClass::get_saturation_water_content_volumetric   ( nat8 layer) const { assert(false); return 0; }
*/
float64 SoilProfileClass::get_unsaturated_conductivity_function_slope( nat8 layer)const {return n_Value[layer];}
/*
float64 SoilProfileClass::get_bypass_coef                           ( nat8 layer) const { assert(false); return 0; }
float64 SoilProfileClass::get_sat_hydraul_cond_kg_s_m3              ( nat8 layer) const { assert(false); return 0; }
float64 SoilProfileClass::get_Campbell_b          ( nat8 layer,bool FC_PWP_based) const { assert(false); return 0; }
float64 SoilProfileClass::get_air_entry_potential ( nat8 layer,bool FC_PWP_based) const { assert(false); return 0; }
float64 SoilProfileClass::get_water_pot_at_FC     ( nat8 layer)                   const { assert(false); return 0; }

 // Soil_texture_interface methods
float64 SoilProfileClass::get_clay_percent                      (nat8 layer)      const { assert(false); return 0; }
float64 SoilProfileClass::get_sand_percent                      (nat8 layer)      const { assert(false); return 0; }
float64 SoilProfileClass::get_silt_percent                      (nat8 layer)      const { assert(false); return 0; }
void SoilProfileClass::set_sand_clay
      (nat8 layer, float64 _sand, float64 _clay)                   modification_ { assert(false); }
*/
//______________________________________________________________________________

#endif

