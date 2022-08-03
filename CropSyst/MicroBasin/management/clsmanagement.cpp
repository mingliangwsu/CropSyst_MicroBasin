#include <iostream>
#include "util/pubtools.h"

#ifdef CROPSYST_PROPER_CROP
#  include "crop/crop_interfaced.h"
#else
#  include "crop/clscrop.h"
#endif
#include "clsmanagement.h"
#include <math.h>
//______________________________________________________________________________
clsManagement::clsManagement
(AllControlClass  &_ControlRef
,const CORN::Date &_today                                                        //150630RLN
,BasinClass       &_BasinRef)
:ControlRef (_ControlRef)
,BasinRef   (_BasinRef)
,today      (_today)                                                             //150630RLN
{
    //instantiateManagement();
}
//______________________________________________________________________________
void clsManagement::instantiateManagement()
{
    pManagementState = new ManageEventStateClass;
    pSchedule = new ManageScheduleClass(/*LML 140827 ControlRef*/);
}
//______________________________________________________________________________
clsManagement::~clsManagement()
{
#ifdef Destruct_Monitor
    std::cout<<"~clsManagement:"<<std::endl;
#endif
    delete pManagementState;
    //LML 140827 delete pSchedule;
#ifdef Destruct_Monitor
    std::cout<<"~clsManagement done."<<std::endl;
#endif
}
//______________________________________________________________________________
void clsManagement::initializeNewDay
( clsSimulation &Simulation
#ifdef CROPSYST_PROPER_CROP
,const CropSyst::Crop_interfaced &crop
#else
, clsCrop &crop
#endif
, clsSoil &Soil
, WeatherStateDailyClass &Weather
, const int crop_management_zone)                                                //FMS Mar 19, 2015 added CropManagementZone
{
    DailyManagementEvents(Simulation, crop, Soil, Weather, crop_management_zone);
}
//______________________________________________________________________________
void clsManagement::DailyManagementEvents
(clsSimulation &Simulation
#ifdef CROPSYST_PROPER_CROP
,const CropSyst::Crop_interfaced &crop
#else
, clsCrop &crop
#endif
, clsSoil &Soil
, WeatherStateDailyClass &Weather
, int CropManagementZone)
{
    bool Crop_Emerged = Simulation.pSimulationRotation->getCropEmerged();
    //'Find irrigation events
    //if (Crop_Emerged) {
    /*150522
    int management_index = 
        ControlRef.find_management_index(Simulation.pSimulationRotation->getCurrentManagementName());
    if (management_index >= 0) 
        pSchedule = &(ControlRef.parrManagementSchedule[management_index]);   //LML 140827
    else pSchedule = &(ControlRef.parrManagementSchedule[0]);                                       //LML 140827
    */
    //}
    //pManagementState->current_management_name = Simulation.pSimulationRotation->getManagementName();
    FindIrrigation(Simulation, Soil);
    //'Find fertilization events
    if (FindFertilization(Simulation,Soil,CropManagementZone))
        ApplyFertilization(Crop_Emerged, crop, Simulation, Soil, Weather);
    //'Apply Manure events
    if (FindManureApplication(Simulation)) 
        ApplyManure(Crop_Emerged, crop, Soil);
    //'Find tillage operations
    FindAndApplyTillageEvent(Simulation, Soil);
}
//______________________________________________________________________________
void clsManagement::FindBiomassToStandingResidue(clsSimulation &Simulation)
{
    //int Rotation_Cycle_Length = Simulation.pSimulationRotation->getRotationCycleLength();
    int management_index = Simulation.pSimulationRotation->getCurrentManagementIndex(); //150526
    assert(management_index >= 0);
    ManageScheduleClass &schedule = ControlRef.parrManagementSchedule[management_index];
    double Standing_Fraction = /*150526 pSchedule->parrBiomass_To_Residue_At_Harvest[0].*/schedule.parrBiomass_To_Residue_At_Harvest[0].Standing_Fraction;
    double Surface_Fraction  = /*150526 pSchedule->parrBiomass_To_Residue_At_Harvest[0].*/schedule.parrBiomass_To_Residue_At_Harvest[0].Surface_Fraction;
    Fraction_Of_Biomass_To_Standing_Residue = Standing_Fraction;
    Fraction_Of_Biomass_To_Surface_Residue = Surface_Fraction;
}
//______________________________________________________________________________
bool clsManagement::FindIrrigation(clsSimulation &Simulation,clsSoil &Soil)
{
    bool find(false);
    int year = Simulation.pTimeState->getToday().get_year();
    int doy = Simulation.pTimeState->getToday().get_DOY();
    for (int k = 0; k < pSchedule->parrIrrigation_Event.size(); k++) {
        if (!pSchedule->parrIrrigation_Event[k].b_matched_year)
            pSchedule->parrIrrigation_Event[k].b_matched_year =
                    FindAndMatchYearForRotationEvents(pSchedule->parrIrrigation_Event[k]
                                              .year,pSchedule->parrIrrigation_Event[k].doy
                                              ,year
                                              ,doy
                                              ,Simulation.pSimulationRotation->getRotationCycleLength());
        double Irrigation_Amount(0.0);
        if (!find && (year == pSchedule->parrIrrigation_Event[k].year) &&
                  (doy == pSchedule->parrIrrigation_Event[k].doy)) {
            find = true;
            Irrigation_Amount = pSchedule->parrIrrigation_Event[k].Irrigation_Amount;
            if ((Irrigation_Amount <= 1) && (Irrigation_Amount > 0)) {    //'RS added second condition
                double Efficiency = Irrigation_Amount;
                double Depletion = Soil.pSoilState->Profile_Soil_Water_Depletion;
                Irrigation_Amount = Depletion / Efficiency;
            }
            if (Irrigation_Amount > 0) {
                double Fertilization_NO3_kg_ha = 
                    pSchedule->parrIrrigation_Event[k].Irrigation_NO3;  //'NO3 (kg/ha) 'FMS 10/28/2013
                //'RS changed, also NH4
                //'was: ManagementState.IrrigationNO3Conc = Fertigation_Rate / (Irrigation_Amount * 10000)
                //'now: with IrrigationNO3Conc (kg/m3); fertigation rate (kg/ha), 
                //Irrigation ammount (mm), (1 m/1000 mm), (10000 m2/ha)
                double irrig_NO3_conc = Fertilization_NO3_kg_ha 
                                        / (Irrigation_Amount * (1.0 / 1000.0) * 10000.0);                   
                // 'kg/m3 'FMS 10/28/2013  //140429 RLN there was division by zero error
                pManagementState->Irrigation_NO3_Conc =  irrig_NO3_conc;
                  //140429 Fertilization_NO3_kg_ha / (Irrigation_Amount * (1.0 / 1000.0) * 10000.0);        
                // 'kg/m3 'FMS 10/28/2013
                double Fertilization_NH4_kg_ha = 
                    pSchedule->parrIrrigation_Event[k].Irrigation_NH4;
                // ' NH4 (kg/ha) 'FMS 10/28/2013
                pManagementState->Irrigation_NH4_Conc = 
                        Fertilization_NH4_kg_ha / (Irrigation_Amount * (1.0 / 1000.0) * 10000.0); 
                // 'kg/m3 'FMS 10/28/2013
                //'end changed
                pSchedule->parrIrrigation_Event[k].year += 
                    Simulation.pSimulationRotation->getRotationCycleLength();
            } else {
                pManagementState->Irrigation_NO3_Conc = 0;
                pManagementState->Irrigation_NH4_Conc = 0;
                pSchedule->parrIrrigation_Event[k].year += 
                    Simulation.pSimulationRotation->getRotationCycleLength();
            }
        }
        pManagementState->Irrigation_Amount = Irrigation_Amount;
    }
    return find;
}
//______________________________________________________________________________
bool clsManagement::FindFertilization(clsSimulation &Simulation, clsSoil &Soil, int CropManagementZone) //FMS MAr 19, 2015 added  Soil as clsSoil and CropManagementZone
{
    bool find(false);
    int tyear = /*150630RLN ControlRef.*/today.get_year();
    int tdoy = /*150630RLN ControlRef.*/today.get_DOY();
    pManagementState->Fertilization_Total_Amount = 0;
    pManagementState->Fertilization_NO3_N = 0;
    pManagementState->Fertilization_NH4_N = 0;
    for (int k = 0; k  < pSchedule->parrFertilization_Event.size(); k++) {
        FertilizationEventClass &fer_event = pSchedule->parrFertilization_Event[k];
        if (fer_event.Fertilization_Type == AUTO_FERTILIZATION) {
          AutoFertilization(Simulation, Soil, k, CropManagementZone);            //FMS Mar 19, 2015
        } else {
          if (!fer_event.b_matched_year) {
            fer_event.b_matched_year =
                FindAndMatchYearForRotationEvents(fer_event.year
                                        ,fer_event.doy
                                        ,tyear
                                        ,tdoy
                                        ,Simulation.pSimulationRotation->getRotationCycleLength());
          }
          if (!find &&
              (tyear == fer_event.year) &&
              (tdoy  == fer_event.doy)) {
            find = true;
            pManagementState->Fertilization_Total_Amount = 
                fer_event.Fertilization_Total_Amount;
            pManagementState->Fertilization_NO3_N = 
                fer_event.Fertilization_NO3_N;
            pManagementState->Fertilization_NH4_N = 
                fer_event.Fertilization_NH4_N;
            pManagementState->Fertilization_Source = 
                fer_event.Fertilization_Source;
            pManagementState->Fertilization_Form = 
                fer_event.Fertilization_Form;
            pManagementState->Fertilization_Method = 
                fer_event.Fertilization_Method;
            pManagementState->Fertilization_Type   =
                fer_event.Fertilization_Type;
            fer_event.year +=
                Simulation.pSimulationRotation->getRotationCycleLength();
          }
        }
    }
    return find;
}
//__FMS 19, 2015________________________________________________________________
void clsManagement::AutoFertilization(clsSimulation &Simulation, clsSoil &Soil, int k, int CropManagementZone)
{
    double Nitrate_Apply(0),Ammounium_Apply(0);
    FertilizationEventClass &fer_event = pSchedule->parrFertilization_Event[k];
    int tyear = /*150630RLN ControlRef.*/today.get_year();
    int tdoy  = /*150630RLN ControlRef.*/today.get_DOY();
    int crop_zone_index = BasinRef.getInnerIDFromVectorList<long>(BasinRef.get_crop_management_zone_vector(),CropManagementZone);
    if (tyear == fer_event.year &&
        tdoy  == fer_event.doy-1) { //FMS Mar 19, 2015 1 day before
      for (int layer = 1; layer <= 3; layer++) {
        BasinRef.Nitrate_Content_In_Crop_Management[crop_zone_index] += Soil.pSoilState->Layer_Nitrate_N_Mass[layer] * 10000.;  //kg/ha FMS Mar 19, 2015
        BasinRef.Ammonium_Content_In_Crop_Management[crop_zone_index]+= Soil.pSoilState->Layer_Ammonium_N_Mass[layer] * 10000.; //kg/ha  FMS Mar 19, 2015
      }
      BasinRef.Number_Crop_Management_Zones[crop_zone_index] += 1.0; //LML 150519 need check its usage
    } else if (tyear == fer_event.year &&
               tdoy  == fer_event.doy) { //FMS Mar 19, 2015 1 Right day
      BasinRef.Nitrate_Apply_By_Crop_Management_Zones[crop_zone_index]   = BasinRef.Nitrate_Content_In_Crop_Management[crop_zone_index] / BasinRef.Number_Crop_Management_Zones[crop_zone_index]; //FMS Mar 19, 2015
      BasinRef.Ammounium_Apply_By_Crop_Management_Zones[crop_zone_index] = BasinRef.Ammonium_Content_In_Crop_Management[crop_zone_index] / BasinRef.Number_Crop_Management_Zones[crop_zone_index];

      Nitrate_Apply   = CORN::must_be_greater_or_equal_to(0.0,fer_event.Fertilization_NO3_N - BasinRef.Nitrate_Apply_By_Crop_Management_Zones[crop_zone_index]);
      Ammounium_Apply = CORN::must_be_greater_or_equal_to(0.0,fer_event.Fertilization_NH4_N - BasinRef.Ammounium_Apply_By_Crop_Management_Zones[crop_zone_index]);

      pManagementState->Fertilization_Total_Amount = Nitrate_Apply + Ammounium_Apply;
      pManagementState->Fertilization_NO3_N = Nitrate_Apply;
      pManagementState->Fertilization_NH4_N = Ammounium_Apply;
      pManagementState->Fertilization_Source = fer_event.Fertilization_Source;
      pManagementState->Fertilization_Form   = fer_event.Fertilization_Form;
      pManagementState->Fertilization_Method = fer_event.Fertilization_Method;
      fer_event.year += Simulation.pSimulationRotation->getRotationCycleLength();
      Application_Year = tyear;
    }
    if (tyear == Application_Year &&
        tdoy  == (fer_event.doy + 1)) {  //FMS Mar 19, 2015 1 one day after, set in zero the values
        BasinRef.Nitrate_Apply_By_Crop_Management_Zones[crop_zone_index]   = 0;
        BasinRef.Ammounium_Apply_By_Crop_Management_Zones[crop_zone_index] = 0;
        BasinRef.Number_Crop_Management_Zones[crop_zone_index]             = 0;
    }
}
//______________________________________________________________________________
bool clsManagement::FindManureApplication(clsSimulation &Simulation)
{
    bool find = false;
    int year =/*150630RLN ControlRef.*/today.get_year();
    int doy = /*150630RLN ControlRef.*/today.get_DOY();
    pManagementState->Manure_Amount = 0;
    pManagementState->Manure_Application_Method = 0;
    pManagementState->Manure_Fast_Cycling_Fraction = 0;
    pManagementState->Manure_Slow_Cycling_Fraction = 0;
    pManagementState->Manure_Lignified_Fraction = 0;
    pManagementState->Manure_Fast_Cycling_Decomposition_Rate = 0;
    pManagementState->Manure_Slow_Cycling_Decomposition_Rate = 0;
    pManagementState->Manure_Lignified_Decomposition_Rate = 0;
    pManagementState->Manure_Fast_Cycling_CN = 0;
    pManagementState->Manure_Slow_Cycling_CN = 0;
    pManagementState->Manure_Lignified_CN = 0;
    pManagementState->Manure_Carbon_Fraction = 0;
    pManagementState->Manure_Ammonium_N = 0;
    pManagementState->Manure_Water = 0;
    pManagementState->Manure_Area_To_Mass_Ratio = 0;
    for (int k = 0; k < pSchedule->parrManure_Event.size(); k++) {
        if (!pSchedule->parrManure_Event[k].b_matched_year)
                pSchedule->parrManure_Event[k].b_matched_year =
                    FindAndMatchYearForRotationEvents(pSchedule->parrManure_Event[k].year
                                                      ,pSchedule->parrManure_Event[k].doy
                                                      ,year
                                                      ,doy
                                                      ,Simulation.pSimulationRotation->getRotationCycleLength());
        if (!find && (year == pSchedule->parrManure_Event[k].year) &&
            (doy == pSchedule->parrManure_Event[k].doy)) {
            find = true;
            pManagementState->Manure_Amount = 
                pSchedule->parrManure_Event[k].Manure_Amount;
            pManagementState->Manure_Application_Method = 
                pSchedule->parrManure_Event[k].Manure_Application_Method;
            pManagementState->Manure_Fast_Cycling_Fraction = 
                pSchedule->parrManure_Event[k].Manure_Fast_Cycling_Fraction;
            pManagementState->Manure_Slow_Cycling_Fraction = 
                pSchedule->parrManure_Event[k].Manure_Slow_Cycling_Fraction;
            pManagementState->Manure_Lignified_Fraction = 
                pSchedule->parrManure_Event[k].Manure_Lignified_Fraction;
            pManagementState->Manure_Fast_Cycling_Decomposition_Rate = 
                pSchedule->parrManure_Event[k].Manure_Fast_Cycling_Decomposition_Rate;
            pManagementState->Manure_Slow_Cycling_Decomposition_Rate = 
                pSchedule->parrManure_Event[k].Manure_Slow_Cycling_Decomposition_Rate;
            pManagementState->Manure_Lignified_Decomposition_Rate = 
                pSchedule->parrManure_Event[k].Manure_Lignified_Decomposition_Rate;
            pManagementState->Manure_Fast_Cycling_CN = 
                pSchedule->parrManure_Event[k].Manure_Fast_Cycling_CN;
            pManagementState->Manure_Slow_Cycling_CN = 
                pSchedule->parrManure_Event[k].Manure_Slow_Cycling_CN;
            pManagementState->Manure_Lignified_CN = 
                pSchedule->parrManure_Event[k].Manure_Lignified_CN;
            pManagementState->Manure_Carbon_Fraction = 
                pSchedule->parrManure_Event[k].Manure_Carbon_Fraction;
            pManagementState->Manure_Ammonium_N = 
                pSchedule->parrManure_Event[k].Manure_Ammonium_N;
            pManagementState->Manure_Water = 
                pSchedule->parrManure_Event[k].Manure_Water;
            pManagementState->Manure_Area_To_Mass_Ratio = 
                pSchedule->parrManure_Event[k].Manure_Area_To_Mass_Ratio;
            pSchedule->parrManure_Event[k].year += 
                Simulation.pSimulationRotation->getRotationCycleLength();
        }
    }
    return find;
}
//______________________________________________________________________________
bool clsManagement::FindAndApplyTillageEvent(clsSimulation &Simulation,clsSoil &Soil)
{
    bool find(false);
    int year =/*150630RLN ControlRef.*/today.get_year();
    int doy = /*150630RLN ControlRef.*/today.get_DOY();
    pManagementState->Tillage_Event = false;
    for (int k = 0; k < pSchedule->parrTillage_Event.size(); k++) {
        if (!pSchedule->parrTillage_Event[k].b_matched_year)
                pSchedule->parrTillage_Event[k].b_matched_year =
                    FindAndMatchYearForRotationEvents(pSchedule->parrTillage_Event[k].year
                                                      ,pSchedule->parrTillage_Event[k].doy
                                                      ,year
                                                      ,doy
                                                      ,Simulation.pSimulationRotation->getRotationCycleLength());

        if (!find && (year == pSchedule->parrTillage_Event[k].year) &&
            (doy == pSchedule->parrTillage_Event[k].doy)) {
            find = true;
            pManagementState->Surface_Residue_Fraction_Remaining_After_Tillage = 
                pSchedule->parrTillage_Event[k].Surface_Residue_Fraction_Remaining_On_Soil_Surface;
            pManagementState->Standing_To_Flat_Residue_Fraction = 
                pSchedule->parrTillage_Event[k].Fraction_Standing_Residue_Flatenned_To_Soil_Surface;
            pManagementState->Tillage_Depth = 
                pSchedule->parrTillage_Event[k].Depth_Soil_Disturbance_m;
            pManagementState->Type_Of_Disturbance = 
                pSchedule->parrTillage_Event[k].Type_Of_Disturbance;
            pManagementState->Tillage_Mixing_Fraction = 
                pSchedule->parrTillage_Event[k].Soil_Mixing_Fraction;
            pManagementState->Tillage_Soil_Disturbance_Rate = 
                pSchedule->parrTillage_Event[k].Tillage_Soil_Disturbance_Rating;
            pManagementState->Tillage_Event = true;
            pSchedule->parrTillage_Event[k].year += 
                Simulation.pSimulationRotation->getRotationCycleLength();
        }
    }
    if (pManagementState->Tillage_Event == true) ApplyTillage(Soil, Simulation);
    return find;
}
//______________________________________________________________________________
bool clsManagement::FindAndApplyClippingEvent
(
#ifdef CROPSYST_PROPER_CROP
 modifiable_ CropSyst::Crop_interfaced &crop
#else
 clsCrop &crop
#endif
)
{
    //140502 RLN double Current_Thermal_Time;
    //140502 RLN double Thermal_Time_At_The_End_Of_Canopy_Growth;
    //140502 RLN double Relative_Thermal_Time;
    const double Harvest_Ratio(0.9);
    #ifdef CROPSYST_PROPER_CROP
    double Current_Thermal_Time = crop.get_accum_degree_days(true);              //140502
    double Thermal_Time_At_The_End_Of_Canopy_Growth = crop.param_max_canopy_deg_day(); //140512
    #else
    double Current_Thermal_Time = crop.pCropState->Cumulative_Thermal_Time;
    double Thermal_Time_At_The_End_Of_Canopy_Growth = 
        crop.pCropParameters->Thermal_Time_At_The_End_Of_Canopy_Growth;
    #endif
    double Relative_Thermal_Time = Current_Thermal_Time / Thermal_Time_At_The_End_Of_Canopy_Growth;
    if (Relative_Thermal_Time >= Harvest_Ratio) Clipping_Event = true;
    else Clipping_Event = false;
    //'Apply clipping event
    if (Clipping_Event) {
        #ifdef CROPSYST_PROPER_CROP
        Harvest_amount_mode harvest_amount_mode = HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS; //140511RLN
        Biomass_fate_parameters harvest_biomass_fate_parameters;
        // RLN need to setup biomass fate parameters.
        Crop_mass_fate_biomass_and_nitrogen *crop_fate =crop.harvest_crop        //140511RLN
            (harvest_amount_mode
            ,999999.99  //This should remove everything  remove_amount_kg_m2
            ,0.0        //This should keep nothing       retain_GAI
            ,harvest_biomass_fate_parameters
            ,true /*terminate*/);
        delete crop_fate; //RLN need to do something with the fate
        #else
        crop.pCropState->Fraction_Solar_Rad_Intercepted_Green_Canopy = crop.pCropParameters->Initial_Canopy_Cover;
        crop.pCropState->Yesterday_Fraction_Solar_Rad_Intercepted_Green_Canopy = 0;
        crop.pCropState->Potential_Fraction_Solar_Rad_Intercepted = crop.pCropParameters->Initial_Canopy_Cover;
        crop.pCropState->Fraction_Solar_Rad_Intercepted_Total_Canopy = crop.pCropParameters->Initial_Canopy_Cover;
        crop.pCropState->Development_Stage = "Harvested";
        #endif
    }
    return Clipping_Event;
}
//______________________________________________________________________________
void clsManagement::ApplyTillage(clsSoil &Soil, clsSimulation &Simulation)
{
    int Last_Tilled_Layer(0);
    double Tillage_Depth = pManagementState->Tillage_Depth;
    double Layer_Bottom_Depth(0.0);
    for (int k = 1; k <= Soil.pSoilProfile->NumberOfLayers(); k++) {
        double Soil_Layer_Thickness = Soil.pSoilProfile->get_thickness_m(k);
        Layer_Bottom_Depth += Soil_Layer_Thickness;
        if ((Tillage_Depth <= Layer_Bottom_Depth) && 
            (Tillage_Depth > (Layer_Bottom_Depth - Soil_Layer_Thickness))) {
            Last_Tilled_Layer = k;
            k = Soil.pSoilProfile->NumberOfLayers() + 1;
        }
    }
    pManagementState->Last_Layer_Tilled = Last_Tilled_Layer;
    Soil.pSoilProcesses->TillageEffectOnSoilProperties(*this);
    Soil.pSOMResidueMaster->OrganicCarbonMixingDueToTillage(*this, Simulation);
    Soil.pOrganicResidue->RedistributeResiduesAfterTillage(*this);
    Soil.pSoilState->Surface_Soil_Cover = SSC_BareSoil; //FMS Aug 26, 2014
}
//______________________________________________________________________________
void clsManagement::ApplyFertilization
(bool Crop_Emerged
#ifdef CROPSYST_PROPER_CROP
,const CropSyst::Crop_interfaced &crop                                            //140502
#else
, clsCrop &crop
#endif
, clsSimulation &Simulation
, clsSoil &Soil
, WeatherStateDailyClass &Weather)
{
    int doy = /*150630RLN ControlRef.*/today.get_DOY();
    double Nitrate_N_Fertilization = pManagementState->Fertilization_NO3_N / 10000.0    // 'Convert kgN/ha to kgN/m2
                                     + (pManagementState->Irrigation_Amount * pManagementState->Irrigation_NO3_Conc) / 1000;    // 'FMS 10/28/2013
    double Ammonium_N_Fertilization = pManagementState->Fertilization_NH4_N / 10000.0       // 'Convert kgN/ha to kgN/m2
                                      + (pManagementState->Irrigation_Amount * pManagementState->Irrigation_NH4_Conc) 
                                        / 1000;  // 'FMS 10/28/2013
    int Fertilization_Source = pManagementState->Fertilization_Source;
    int Fertilization_Method = pManagementState->Fertilization_Method;
    double Soil_pH = Soil.pSoilProfile->get_pH(1);
    double Soil_CEC = Soil.pSoilProfile->get_cation_exchange_capacity(1);
    double Crop_LAI(0.0);
    double Crop_Height(0.0);
    if (Crop_Emerged) {
        #ifdef CROPSYST_PROPER_CROP
        Crop_LAI     = crop.get_LAI(true);                                       //140511
        Crop_Height  = crop.get_plant_height_m();                                //140511
        #else
        Crop_LAI = crop.pCropState->Leaf_Area_Index;
        Crop_Height = crop.pCropState->Crop_Height;
        #endif
    } else {
        Crop_LAI = 0;
        Crop_Height = 0;
    }
    //'Determine the maximum fraction of applied ammonia/ammonium nitrogen available for volatilization
    if (Ammonium_N_Fertilization > 0) {
        double Lower_Range(0.0);
        double Upper_Range(0.0);
        if (Soil_pH > 7) {
            Lower_Range = 0.03;
            switch(Fertilization_Source) {
            case 1:
            case 2:
                    if (Fertilization_Method == 1) Upper_Range = 0.4;
                    else Upper_Range = 0.1;
                    break;
            default:    //3
                    if (Fertilization_Method == 1) Upper_Range = 0.5;
                    else Upper_Range = 0.25;
                    break;
            }
        } else {
            Lower_Range = 0.02;
            switch(Fertilization_Source) {
                case 1:
                    if (Fertilization_Method == 1) Upper_Range = 0.4;
                    else Upper_Range = 0.02;
                    break;
                case 2:
                    if (Fertilization_Method == 1) Upper_Range = 0.2;
                    else Upper_Range = 0.02;
                    break;
                default:    //3
                    if (Fertilization_Method == 1) Upper_Range = 0.02;
                    else Upper_Range = 0.02;
            }
        }
        double Ammonia_Fraction_Available_For_Volatilization(0.0);
        if (Soil_CEC > 25) Ammonia_Fraction_Available_For_Volatilization = Lower_Range;
        else if (Soil_CEC <= 10) Ammonia_Fraction_Available_For_Volatilization = Upper_Range;
        else Ammonia_Fraction_Available_For_Volatilization = 
            Upper_Range - (Upper_Range - Lower_Range) * (Soil_CEC - 10.0) / 15.0;
        Soil.pSoilState->Ammonia_Available_For_Volatilization += 
            Ammonia_Fraction_Available_For_Volatilization * Ammonium_N_Fertilization;
        if (Fertilization_Method == 1) {
            Soil.pSoilState->Layer_Ammonium_N_Mass[1] += Ammonium_N_Fertilization;
            //'Applied TAN (kg/m2)
            Soil.pSoilNTransformation->AmmoniaVolatilization(Ammonium_N_Fertilization, 
                                                             0, 0, Crop_Height, Crop_LAI, Simulation, Weather);
        } else {
            //XXXOJO: Layer 1 receives the mass available for volatilization
            Soil.pSoilState->Layer_Ammonium_N_Mass[1] += 
                Ammonium_N_Fertilization * Ammonia_Fraction_Available_For_Volatilization;
            Soil.pSoilState->Layer_Ammonium_N_Mass[2] += 
                Ammonium_N_Fertilization * (1 - Ammonia_Fraction_Available_For_Volatilization);
        }
    }
    if (Nitrate_N_Fertilization > 0) {
        Soil.pSoilState->Layer_Nitrate_N_Mass[1] += Nitrate_N_Fertilization / 2.0;
        Soil.pSoilState->Layer_Nitrate_N_Mass[2] += Nitrate_N_Fertilization / 2.0;
    }
    Soil.pSoilState->Daily_Nitrate_N_Fertilization = Nitrate_N_Fertilization;
    Soil.pSoilState->Daily_Ammonium_N_Fertilization = Ammonium_N_Fertilization;
    if (doy == 1) {
        Soil.pSoilState->Cumulative_Nitrate_N_Fertilization = Nitrate_N_Fertilization;
        Soil.pSoilState->Cumulative_Ammonium_N_Fertilization = Ammonium_N_Fertilization;
    } else {
            Soil.pSoilState->Cumulative_Nitrate_N_Fertilization += Nitrate_N_Fertilization;
            Soil.pSoilState->Cumulative_Ammonium_N_Fertilization += Ammonium_N_Fertilization;
    }
}
//______________________________________________________________________________
void clsManagement::ApplyManure
(bool Crop_Emerged
#ifdef CROPSYST_PROPER_CROP
, const CropSyst::Crop_interfaced &crop                                          //140502RLN
#else
, clsCrop &crop
#endif
, clsSoil &Soil)
{
    double Fresh_Manure_Application_Mass = pManagementState->Manure_Amount / 10000.0;    
    // 'Convert kg/ha to kg/m2 of fresh manure
    if (Fresh_Manure_Application_Mass > 0) {
        double Water_Manure_Ratio = pManagementState->Manure_Water;   // 'This is in kgH2O/kg DM
        //'Convert kg/m2 of fresh manure to kg/m2 of dry manure matter
        double Manure_Application_Mass = Fresh_Manure_Application_Mass / (1.0 + Water_Manure_Ratio);
        //'Calculate manure water depth equivalent in m3/m2 (that is m water depth). Fresh manure is in kg/m2
        //double Manure_Water = Fresh_Manure_Application_Mass / (1.0 + 1.0 / Water_Manure_Ratio) * 0.001;
        //'Note: The water in fresh manure composition is neglected for irrigation or evaporation. If manure is mixed
        //'with irrigation water, the latter amount must be specified as an irrigation event
        double Manure_Fast_Cycling_Mass = pManagementState->Manure_Fast_Cycling_Fraction * Manure_Application_Mass;
        double Manure_Slow_Cycling_Mass = pManagementState->Manure_Slow_Cycling_Fraction * Manure_Application_Mass;
        double Manure_Lignified_Mass = pManagementState->Manure_Lignified_Fraction * Manure_Application_Mass;
        double Manure_Fast_Cycling_CN = pManagementState->Manure_Fast_Cycling_CN;
        double Manure_Slow_Cycling_CN = pManagementState->Manure_Slow_Cycling_CN;
        double Manure_Lignified_CN = pManagementState->Manure_Lignified_CN;
        double Manure_Carbon_Fraction = pManagementState->Manure_Carbon_Fraction;
        //'Account for new organic carbon and nitrogen in the system
        Soil.pOrganicResidueState->New_Soil_Residue_Carbon_Mass += Manure_Application_Mass * Manure_Carbon_Fraction;
        Soil.pOrganicResidueState->Soil_Residue_Carbon_Mass += Manure_Application_Mass * Manure_Carbon_Fraction;
        Soil.pOrganicResidueState->New_Soil_Residue_Nitrogen_Mass +=
                Manure_Fast_Cycling_Mass * Manure_Carbon_Fraction / Manure_Fast_Cycling_CN
                + Manure_Slow_Cycling_Mass * Manure_Carbon_Fraction / Manure_Slow_Cycling_CN
                + Manure_Lignified_Mass * Manure_Carbon_Fraction / Manure_Lignified_CN;
        Soil.pOrganicResidueState->Soil_Residue_Nitrogen_Mass +=
                Manure_Fast_Cycling_Mass * Manure_Carbon_Fraction / Manure_Fast_Cycling_CN
                + Manure_Slow_Cycling_Mass * Manure_Carbon_Fraction / Manure_Slow_Cycling_CN
                + Manure_Lignified_Mass * Manure_Carbon_Fraction / Manure_Lignified_CN;
        Soil.pSoilState->Daily_Organic_N_Fertilization =
                Manure_Fast_Cycling_Mass * Manure_Carbon_Fraction / Manure_Fast_Cycling_CN
                + Manure_Slow_Cycling_Mass * Manure_Carbon_Fraction / Manure_Slow_Cycling_CN
                + Manure_Lignified_Mass * Manure_Carbon_Fraction / Manure_Lignified_CN;
        Soil.pSoilState->Cumulative_Organic_N_Fertilization +=
                Manure_Fast_Cycling_Mass * Manure_Carbon_Fraction / Manure_Fast_Cycling_CN
                + Manure_Slow_Cycling_Mass * Manure_Carbon_Fraction / Manure_Slow_Cycling_CN
                + Manure_Lignified_Mass * Manure_Carbon_Fraction / Manure_Lignified_CN;
        //'Create independent residue pools for fast cycling, slow cycling, and lignified manure fractions
        double Manure_Fast_Cycling_Decomposition_Rate = pManagementState->Manure_Fast_Cycling_Decomposition_Rate;
        double Manure_Slow_Cycling_Decomposition_Rate = pManagementState->Manure_Slow_Cycling_Decomposition_Rate;
        double Manure_Lignified_Decomposition_Rate = pManagementState->Manure_Lignified_Decomposition_Rate;
        //'Convert time constant in days to decomposition constant in 1/days
        Manure_Fast_Cycling_Decomposition_Rate = -log(0.5) / Manure_Fast_Cycling_Decomposition_Rate;
        Manure_Slow_Cycling_Decomposition_Rate = -log(0.5) / Manure_Slow_Cycling_Decomposition_Rate;
        Manure_Lignified_Decomposition_Rate = -log(0.5) / Manure_Lignified_Decomposition_Rate;
        //'Note: Residue pool is currently applied to the top soil layer regardless of application method
        //'This will require modification in the future (OJO XXX)
        Soil.pOrganicResidue->AddResiduePool(0/*150611LML 121*//*FMS 141002 121*/, Manure_Fast_Cycling_Mass,
            Manure_Fast_Cycling_Decomposition_Rate,
            Manure_Fast_Cycling_CN, Manure_Carbon_Fraction, 999.99, true /*FMS Feb 9, 2015 false*/, 121/*150611LML 0*/,
            Soil.pOrganicResidueState->Standing_Stubble_Contact_Fraction,
            Soil.pOrganicResidueState->Surface_Residue_Contact_Fraction);
        Soil.pOrganicResidue->AddResiduePool(0/*150611LML 1*/, Manure_Slow_Cycling_Mass, Manure_Slow_Cycling_Decomposition_Rate,
            Manure_Slow_Cycling_CN, Manure_Carbon_Fraction, 999.99, true /*FMS Feb 9, 2015 false*/, 1/*150611LML 0*/,
            Soil.pOrganicResidueState->Standing_Stubble_Contact_Fraction,
            Soil.pOrganicResidueState->Surface_Residue_Contact_Fraction);
        Soil.pOrganicResidue->AddResiduePool(0/*150611LML 61*//*FMS Feb 9, 2015 FMS 141002 61*/,
            Manure_Lignified_Mass, Manure_Lignified_Decomposition_Rate,
            Manure_Lignified_CN, Manure_Carbon_Fraction, 999.99, true/*FMS Feb 9, 2015 false*/, 61/*150611LML 0*/,
            Soil.pOrganicResidueState->Standing_Stubble_Contact_Fraction,
            Soil.pOrganicResidueState->Surface_Residue_Contact_Fraction);
        //'Dispose ammonium N in manure
        double Ammonium_N_Dry_Manure_Ratio = pManagementState->Manure_Ammonium_N;              // 'This is in kg NH3-N / kg dry manure
        double Manure_Ammonium_N = Manure_Application_Mass * Ammonium_N_Dry_Manure_Ratio;  // 'This is in kg NH3-N / m2
        int Manure_Application_Method = pManagementState->Manure_Application_Method;
        //'    Manure_Water = ManagementState.ManureWater / 10000 'Convert m3/ha to m3/m2 (that is m water depth)
        double Soil_CEC = Soil.pSoilProfile->get_cation_exchange_capacity(1);
        double Lower_Range(0.0);
        double Upper_Range(0.0);
        if (Manure_Ammonium_N > 0) {
            switch(Manure_Application_Method) {
                case 1:
                    Lower_Range = 0.2;
                    Upper_Range = 0.4;
                default:    // Is = 2
                    Lower_Range = 0.01;
                    Upper_Range = 0.05;
            }
            double Ammonia_Fraction_Available_For_Volatilization(0.0);
            if (Soil_CEC > 25) Ammonia_Fraction_Available_For_Volatilization = Lower_Range;
            else if (Soil_CEC <= 10) Ammonia_Fraction_Available_For_Volatilization = Upper_Range;
            else Ammonia_Fraction_Available_For_Volatilization = 
                Upper_Range - (Upper_Range - Lower_Range) * (Soil_CEC - 10.0) / 15.0;
            Soil.pSoilState->Ammonia_Available_For_Volatilization += 
                Ammonia_Fraction_Available_For_Volatilization * Manure_Ammonium_N;
            //'Account for ammonia volatilization on the day of broadcast applications
            double Crop_LAI(0.0);
            double Crop_Height(0.0);
            if (Crop_Emerged) {   // 'Determine crop condition for aerodynamic roughness
                #ifdef CROPSYST_PROPER_CROP
                Crop_LAI     = crop.get_LAI(true);                                       //140511
                Crop_Height  = crop.get_plant_height_m();                                //140511
                #else
                Crop_LAI = crop.pCropState->Leaf_Area_Index;
                Crop_Height = crop.pCropState->Crop_Height;
                #endif
            } else {
                Crop_LAI = 0;
                Crop_Height = 0;
            }
            if (Manure_Application_Method == 1) {
                Soil.pSoilState->Layer_Ammonium_N_Mass[1] += Manure_Ammonium_N;
                //'Applied TAN (kg/m2), Water Volume (m3/m2)
                //Soil.SoilNTransformation.AmmoniaVolatilization(Manure_Ammonium_N, Manure_Water, _
                        //8#, Crop_Height, Crop_LAI, Simulation, Weather)
            } else {       // 'XXXOJO: Layer 1 receives the mass available for volatilization
                Soil.pSoilState->Layer_Ammonium_N_Mass[1] += 
                    Manure_Ammonium_N * Ammonia_Fraction_Available_For_Volatilization;
                Soil.pSoilState->Layer_Ammonium_N_Mass[2] += 
                    Manure_Ammonium_N * (1.0 - Ammonia_Fraction_Available_For_Volatilization);
            }
            Soil.pSoilState->Daily_Ammonium_N_Fertilization = Manure_Ammonium_N;
            Soil.pSoilState->Cumulative_Ammonium_N_Fertilization += Manure_Ammonium_N;
        }
    }
}
//______________________________________________________________________________

