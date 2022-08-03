#include "cropbiomassclass.h"
#include "control/clssimulation.h"
#include <math.h>
//______________________________________________________________________________
CropBiomassClass::CropBiomassClass
(CropStateClass& _CropStateRef
,AllControlClass& _ControlRef
,const CORN::Date &_today )   //150630RLN
:CropStateRef(_CropStateRef)
,ControlRef(_ControlRef)
,today(_today)                                                                   //150630
{
}
//______________________________________________________________________________
void CropBiomassClass::DetermineWaterLimitedBiomassGrowth()
{
    //Determine above ground water limited biomass growth. 
    //Water-limited root biomass growth is calculated elsewhere
    if (CropStateRef.Crop_Potential_Transpiration > 0) {
        CropStateRef.Water_Limited_Biomass_Growth = 
            CropStateRef.Yesterday_Water_Stress_Factor * CropStateRef.Attainable_Biomass_Today;
    } else {
        CropStateRef.Water_Limited_Biomass_Growth = 0.0;
    }
}
//______________________________________________________________________________
void CropBiomassClass::DetermineActualBiomassGrowth(CropInputClass &CropParametersRef)
{
    const double Biomass_Partitioning_To_Fruit(1.0);    //#
    //Determine above ground water and nitrogen limited biomass growth. Water&Nitrogen-limited 
    //root biomass growth is calculated elsewhere
    double Water_Limited_Top_Biomass_Growth = CropStateRef.Water_Limited_Biomass_Growth;
    double Water_Limited_Root_Biomass_Growth = CropStateRef.Water_Limited_Root_Biomass_Growth;
    double Top_Nitrogen_Stress_Factor = CropStateRef.Top_Nitrogen_Stress_Factor;
    double Root_Nitrogen_Stress_Factor = CropStateRef.Root_Nitrogen_Stress_Factor;
    double Actual_Top_Biomass_Growth = Water_Limited_Top_Biomass_Growth * Top_Nitrogen_Stress_Factor;
    double Actual_Root_Biomass_Growth = Water_Limited_Root_Biomass_Growth * Root_Nitrogen_Stress_Factor;
    CropStateRef.Biomass_Today = Actual_Top_Biomass_Growth;
    CropStateRef.Actual_Root_Biomass_Growth = Actual_Root_Biomass_Growth;
    //LML 150529 moved CropStateRef.Cumulative_Biomass_Yesterday = CropStateRef.Cumulative_Biomass;
    CropStateRef.Cumulative_Biomass += Actual_Top_Biomass_Growth;
    //150529 CropStateRef.Cumulative_Biomass_Yesterday = CropStateRef.Cumulative_Biomass; //150529 LML
    //LML 150529 moved CropStateRef.Cumulative_Root_Biomass_Yesterday = CropStateRef.Cumulative_Root_Biomass;
    CropStateRef.Cumulative_Root_Biomass += Actual_Root_Biomass_Growth;
    CropStateRef.Cumulative_Root_Biomass_Yesterday = CropStateRef.Cumulative_Root_Biomass; //150529
    //Determine biomass-related yield variables
    if ((CropStateRef.Crop_Forming_Yield == true) &&
       (/*150630 ControlRef.*/today.get_DOY() == CropStateRef.DOY_Begin_Yield_Formation)) {
        CropStateRef.Biomass_Produced_Before_Yield_Formation = CropStateRef.Cumulative_Biomass;
    }
    if (CropStateRef.Crop_Forming_Yield == true) {
        CropStateRef.Biomass_Produced_During_Yield_Formation += Water_Limited_Top_Biomass_Growth;
        CropStateRef.Cumulative_Biomass_Produced_During_Yield_Formation += 
            Water_Limited_Top_Biomass_Growth; //FMS Jun 30, 2014
    }
    if (CropParametersRef.Tree_Fruit_Crop && (CropStateRef.Development_Stage.compare("Fruit_Growth") == 0))
        CropStateRef.Cumulative_Fruit_Biomass_Growth += 
            Water_Limited_Top_Biomass_Growth * Biomass_Partitioning_To_Fruit;
}
//______________________________________________________________________________
void CropBiomassClass::DeterminePotentialGrowth(bool Potential, 
  WeatherStateDailyClass &Weather,clsSimulation &Simulation,CropInputClass &CropParametersRef)
{
    double RUE = CropParametersRef.Radiation_Use_Efficiency / 1000.0;           //Convert g/MJ to Kg/MJ
    double Mean_Temperature_For_Optimum_Growth = CropParametersRef.Optimum_Growth_Mean_Temperature;
    double Tmax = Weather.getDailyMaximumTemperature();
    double Tmin = Weather.getDailyMinimumTemperature();
    double Mean_Temperature = (Tmax + Tmin) / 2.0;
    double Base_Temperature = CropParametersRef.Base_Temperature_for_Development;
    double Temperature_Adjustment_Factor = (Mean_Temperature - Base_Temperature) / (Mean_Temperature_For_Optimum_Growth - Base_Temperature);
    if (Temperature_Adjustment_Factor > 1) Temperature_Adjustment_Factor = 1;
    else if (Temperature_Adjustment_Factor < 0) Temperature_Adjustment_Factor = 0;
    double CO2_Adjustment_Factor_For_RUE = CropStateRef.CO2_Adjustment_To_RUE;
    double CO2_Adjustment_Factor_For_TUE = CropStateRef.CO2_Adjustment_To_TUE;
    double Transpiration_Based_Biomass_Gain(0.0);
    double Radiation_Based_Biomass_Gain(0.0);
    if (Potential) {  //'Potential crop
        if (Simulation.pSimulationRotation->getCropExist() && 
          !CropStateRef.Mature) {
            Radiation_Based_Biomass_Gain = 
                CO2_Adjustment_Factor_For_RUE 
                * RUE 
                * CropStateRef.Potential_Fraction_PAR_Intercepted 
                * (0.5 * Weather.getDailySolarRadiation())
                * Temperature_Adjustment_Factor;
            //Calculate transpiration-based biomass gain for the potential crop
            Transpiration_Based_Biomass_Gain = 
                    CO2_Adjustment_Factor_For_TUE 
                    * CropParametersRef.Water_Use_Efficiency_at_1_kPa 
                    * Weather.getPotentialCropPotentialTranspiration() 
                    / pow(Weather.getDayTimeVPD(),CropParametersRef.Slope_of_Water_Use_Efficiency_Function_of_VPD);
        } else {
            Transpiration_Based_Biomass_Gain = 0;
            Radiation_Based_Biomass_Gain = 0;
        }
        //Today potential biomass is the minimum of radiation and transpiration-based biomass gain
        CropStateRef.Potential_Biomass_Today = (Radiation_Based_Biomass_Gain >= Transpiration_Based_Biomass_Gain) ? Transpiration_Based_Biomass_Gain : Radiation_Based_Biomass_Gain;
        CropStateRef.Potential_Cumulative_Biomass += CropStateRef.Potential_Biomass_Today;
    } else {
        if (Simulation.pSimulationRotation->getCropExist()/*LML 140825 getCropEmerged()*/ && 
          !CropStateRef.Mature) {
            Radiation_Based_Biomass_Gain = 
                CO2_Adjustment_Factor_For_RUE 
                    * RUE 
                    * CropStateRef.Fraction_PAR_Intercepted 
                    * (0.5 * Weather.getDailySolarRadiation())
                    * Temperature_Adjustment_Factor;
            //Calculate transpiration-based biomass gain for the potential crop
            Transpiration_Based_Biomass_Gain = 
                    CO2_Adjustment_Factor_For_TUE 
                    * CropParametersRef.Water_Use_Efficiency_at_1_kPa 
                    * Weather.getActualCropPotentialTranspiration() 
                    / pow(Weather.getDayTimeVPD(), CropParametersRef.Slope_of_Water_Use_Efficiency_Function_of_VPD);
        } else {
            Transpiration_Based_Biomass_Gain = 0.0;
            Radiation_Based_Biomass_Gain = 0.0;
        }
        //'Today attainable biomass is the minimum of radiation and transpiration-based biomass gain
        if (Radiation_Based_Biomass_Gain >= Transpiration_Based_Biomass_Gain) {
            CropStateRef.Attainable_Biomass_Today = Transpiration_Based_Biomass_Gain;
            CropStateRef.Cumulative_Attainable_Biomass += Transpiration_Based_Biomass_Gain;
            if (CropStateRef.Crop_Forming_Yield)
                CropStateRef.Attainable_Biomass_During_Yield_Formation += Transpiration_Based_Biomass_Gain;
        } else {
            CropStateRef.Attainable_Biomass_Today = Radiation_Based_Biomass_Gain;
            CropStateRef.Cumulative_Attainable_Biomass += Radiation_Based_Biomass_Gain;
            if (CropStateRef.Crop_Forming_Yield)
                CropStateRef.Attainable_Biomass_During_Yield_Formation += Radiation_Based_Biomass_Gain;
        }
    }
}
//______________________________________________________________________________
void CropBiomassClass::DetermineBiosynthesisAndMaintenanceRespiration(WeatherStateDailyClass &Weather, 
  CropCanopyGrowthClass &CanopyCover, clsSoil &soil,CropInputClass &CropParametersRef)
{

    //LML 140806 need clean-up the code since units and equations should be double check!
    const double C_Conc_AG = 0.48;              //(g C/g DM AG)
    const double C_Conc_Root = 0.467;           //(g C/g DM root)
    const double C_Conc_CO2 = 12.0/44.0;        //(g C/g CO2)

    double Tmax = Weather.getDailyMaximumTemperature();
    double Tmin = Weather.getDailyMinimumTemperature();
    double GAI = CanopyCover.calc_leaf_green_area_index("GAI");
    double LAI = CanopyCover.calc_leaf_green_area_index("LAI");
    double Tm = CropParametersRef.Temperature_At_Maintenance_Are_Reported;
    double Tw = (Tmax + Tmin) / 2.0;
    double BIOstem = CropStateRef.Cumulative_Biomass * 1000;                    //kg/m2 to g/m2
    double BIOroot = CropStateRef.Cumulative_Root_Biomass * 1000;               //kg/m2 to gDM/m2
    double BIOstor = CropStateRef.Cumulative_Biomass_Produced_During_Yield_Formation 
                     * 1000.0
                     * CropParametersRef.Unstressed_Harvest_Index
                     ; // - CropStateRef.CumulativeBiomassProducedDuringYieldFormation(DACE - 1)
    //Mrroot = CropParametersRef.MaintenanceCoefRoots * 2 * ((Tw - Tm) / 10) / (1000 * 24) * GAI / LAI
    //Mrstem = CropParametersRef.MaintenanceCoefStems * 2 * ((Tw - Tm) / 10) / (1000 * 24) * GAI / LAI
    double t_mr = (exp(0.069 * Tw) / exp(0.069 * Tm)) * GAI / LAI;
    double Mrroot = CropParametersRef.Maintenance_Coef_roots * t_mr;
    double Mrstem = CropParametersRef.Maintenance_Coef_stems * t_mr;
    double Mrstor(0.0);
    if (BIOstor <= 100) Mrstor = CropParametersRef.Maintenance_Coef_stems * t_mr;    //LML 140801 need double check!!!
    else Mrstor = 0;
    double Maintenance_Respiration_Root = Mrroot * BIOroot;
    double Maintenance_Respiration_AG = Mrstem * BIOstem + Mrstor * BIOstor;
    double Maintenance_Respiration = Maintenance_Respiration_Root + Maintenance_Respiration_AG;
    if (Maintenance_Respiration < 0) Maintenance_Respiration = 0;
    double Thermal_Time = CropStateRef.Cumulative_Thermal_Time;
    //double Thermal_time_end_development = CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth;
    double Thermal_time_start_grain = CropParametersRef.Thermal_Time_for_Yield_Formation;
    double Thermal_time_to_Maturity = CropParametersRef.Thermal_Time_for_Maturity;
    //double Partition_Leaves = CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy;
    double Frac_Bioroot(0.0);               //FMS Jul 30, 2014
    double Frac_Biotop(0.0);                //FMS Jul 30, 2014
    double Frac_leaf(0.0);                  //FMS Jul 30, 2014
    double Frac_stem(0.0);                        //LML 140801
    double Frac_stor(0.0);
    double Bio_Top_Today(0.0);                  //(g DM/m2) FMS Jul 24, 2014 g/m2
    double Bio_Root_Today(0.0);
    if (Thermal_Time < Thermal_time_to_Maturity/*FMS Jul 24, 2014*/) {
        Bio_Top_Today = CropStateRef.Biomass_Today * 1000;               //(g DM/m2) FMS Jul 24, 2014 g/m2
        Bio_Root_Today = CORN::must_be_greater_or_equal_to(0.0,CropStateRef.Actual_Root_Biomass_Growth * 1000);    //(g DM/m2) FMS Jul 24, 2014 g/m2
        double SLA = 20.0;                                                      //(m²/kg DM) FMS Jul 30, 2014 Specific leaf area
        //Values of SLA usually range between 15 and 25 (m²/kg)
        double Sup_Leaves = CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy * GAI;    //Superficie of leaves m2 FMS Jul 30, 2014
        //LML 140805 why don't use net expansion in this day?
        double W_leaves = (Sup_Leaves / SLA) * 1000.0;                          //(g DM/m2)
        if (is_approximately<double>(Bio_Root_Today + Bio_Top_Today,0,1e-12)) { //FMS Jul 30, 2014
            Frac_Bioroot = 0;           //FMS Jul 30, 2014
            Frac_Biotop = 0;            //FMS Jul 30, 2014
            Frac_leaf = 0;              //FMS Jul 30, 2014
        } else {
            Frac_Bioroot = Bio_Root_Today / (Bio_Root_Today + Bio_Top_Today);   //FMS Jul 30, 2014
            Frac_Biotop = 1 - Frac_Bioroot;                                     //FMS Jul 30, 2014
            if (W_leaves > Bio_Top_Today) W_leaves = Bio_Top_Today;             //FMS Jul 30, 2014
            if (is_approximately<double>(Bio_Top_Today,0.0,1e-12)) Frac_leaf = 0.0;      //LML 140806 added if
            else Frac_leaf = (W_leaves / Bio_Top_Today) * Frac_Biotop;          //FMS Jul 30, 2014
        }
        assert(Frac_leaf<=1.0);
    }
    if (Thermal_Time < Thermal_time_start_grain) {
        Frac_stem = Frac_Biotop - Frac_leaf;
        Frac_stor = 0.0;                        //LML 140801
    } else {
        Frac_stem = 0.0;                        //LML 140801
        Frac_stor = Frac_Biotop - Frac_leaf;
    }
    double YGroot = CropParametersRef.Biosynthesis_Coef_roots;
    double YGstem = CropParametersRef.Biosynthesis_Coef_stems;
    double YGstor = CropParametersRef.Biosynthesis_Coef_stems;
    double YGleaf = CropParametersRef.Biosynthesis_Coef_leaves;
    double Biosynthesi_Efficiency_Root = YGroot * Frac_Bioroot;
    double Biosynthesi_Efficiency_AG = YGleaf * Frac_leaf + YGstem * Frac_stem + YGstor * Frac_stor;
    double Biosynthesi_Efficiency = Biosynthesi_Efficiency_Root + Biosynthesi_Efficiency_AG;
    double GPP_Root(0.0);
    double GPP_AG(0.0);
    double CO2_production_AG(0.0);
    double CO2_production_Root(0.0);
    if (Thermal_Time <= Thermal_time_to_Maturity) {   //FMS Jul 24, 2014
        double Gross_Production_Dry_Matter_Root(0.0);
        double Gross_Production_Dry_Matter_AG(0.0);
        if (Bio_Root_Today > 0.05 && Biosynthesi_Efficiency_Root > 0)           //FMS Jul 30, 2014  was Biosynthesi_Efficiency_Root > 0.1
            Gross_Production_Dry_Matter_Root = 
                (Bio_Root_Today / Biosynthesi_Efficiency_Root + Maintenance_Respiration_Root) 
                * YGroot;                                                       //(g DM/m2) FMS Jul 30, 2014
        else Gross_Production_Dry_Matter_Root = Maintenance_Respiration_Root * YGroot;               //FMS Jul 30, 2014
        CO2_production_Root = Gross_Production_Dry_Matter_Root * 0.537 * C_Conc_CO2;    //Penning de Vries et al 1989 convert to g CO2 to g Carbon ' FMS Jul 30, 2014
        if (Biosynthesi_Efficiency_AG > 0) {                                    //FMS Jul 30, 2014
            Gross_Production_Dry_Matter_AG = 
                (Bio_Top_Today / Biosynthesi_Efficiency_AG + Maintenance_Respiration_AG) 
                * (YGleaf + YGstem) / 2.0;                                      //(g DM/m2)
            if (CropParametersRef.Leguminous_Crop) 
                CO2_production_AG = Gross_Production_Dry_Matter_AG 
                                    * (Frac_leaf * 0.79 + (Frac_stem + Frac_stor) * 0.54) 
                                    * C_Conc_CO2;                               //Penning de Vries et al 1989 convert to g CO2 to g Carbon
            else CO2_production_AG = Gross_Production_Dry_Matter_AG 
                                     * (Frac_leaf * 0.461 + (Frac_stem + Frac_stor) * 0.4) 
                                     * C_Conc_CO2;                              //Penning de Vries et al 1989 convert to g CO2 to g Carbon ' FMS Jul 30, 2014
        } else {
            Gross_Production_Dry_Matter_AG = (Maintenance_Respiration_AG) * (YGleaf + YGstem) / 2.0;//FMS Jul 30, 2014
            CO2_production_AG = Gross_Production_Dry_Matter_AG * 0.537 * C_Conc_CO2;  //FMS Jul 24, 2014
        }
        GPP_Root = Gross_Production_Dry_Matter_Root * C_Conc_Root;// gC/m2 'FMS Jul 30, 2014
        GPP_AG = Gross_Production_Dry_Matter_AG * C_Conc_AG;//(gC/m2) FMS Jul 30, 2014
    }
    //If -Net_Canopy_Photosynthesis_AG - Net_Canopy_Photosynthesis_Root < -30 Then Stop
    soil.pSoilState->Biosynthesi_Efficiency = Biosynthesi_Efficiency;
    soil.pSoilState->Maintenance_Respiration = Maintenance_Respiration;
    soil.pSoilState->Biomass_Root_Today = -CropStateRef.Cumulative_Root_Biomass * 1000 * C_Conc_Root/*150618LML 0.47*/;  //-Bio_Root_Today // gC/m2
    soil.pSoilState->Biomass_Top_Today = -CropStateRef.Cumulative_Biomass * 1000 * C_Conc_AG/*150618LML 0.47*/;        //-Bio_Top_Today // gC/m2
    soil.pSoilState->Gross_Canopy_Photosynthesis = - GPP_AG - GPP_Root;         // g C/m2
    soil.pSoilState->CO2_by_Plant_Respiration = CO2_production_Root + CO2_production_AG;        //(gC/m2)
    CropStateRef.Green_Area_Index_Today = GAI;
    CropStateRef.Leaf_Area_Index = LAI;                                          //FMS Apr 8, 2015
}
