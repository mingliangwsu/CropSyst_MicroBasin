#include "cropdevelopmentclass.h"
//______________________________________________________________________________
CropDevelopmentClass::CropDevelopmentClass(CropStateClass &_CropStateRef)
    :CropStateRef(_CropStateRef)
{
}
//______________________________________________________________________________
double CropDevelopmentClass::CalculateThermalTime(double Base_Temperature,
  double Maximum_Temperature,double Mean_Temperature)
{
    if (Mean_Temperature > Maximum_Temperature) Mean_Temperature = Maximum_Temperature;
    else if (Mean_Temperature < Base_Temperature) Mean_Temperature = Base_Temperature;
    return Mean_Temperature - Base_Temperature;
}

void CropDevelopmentClass::UpdateDevelopment(WeatherStateDailyClass &Weather,clsSimulation &Simulation,
  clsManagement &Management, CropInputClass &CropParametersRef)
{
    int DACE = Simulation.pTimeState->getDaysAfterCropExists();
    int doy = Simulation.pTimeState->getToday().get_DOY();
    double Degree_Days(0.0);
    if ((DACE == 0) || 
        (CropParametersRef.Perennial_Crop && 
        !CropParametersRef.Tree_Fruit_Crop && 
        CropStateRef.Crop_Dormant)) {
        Degree_Days = 0.0;
    } else {
        double Tmax = Weather.getDailyMaximumTemperature();
        double Tmin = Weather.getDailyMinimumTemperature();
        double tmean = 0.5 * (Tmax + Tmin);
        Degree_Days = CalculateThermalTime(CropParametersRef.Base_Temperature_for_Development,
                                           CropParametersRef.Maximum_Temperature_for_Development,
                                           tmean);
    }
    CropStateRef.Thermal_Time_Today = Degree_Days;
    if (DACE == 0) {
        CropStateRef.Cumulative_Thermal_Time = Degree_Days;   // 'Initiate thermal time when crop is planted
        CropStateRef.Yesterday_Cumulative_Thermal_Time = 0;
    } else {
        CropStateRef.Yesterday_Cumulative_Thermal_Time = CropStateRef.Cumulative_Thermal_Time;
        CropStateRef.Cumulative_Thermal_Time += Degree_Days;
        //CropStateRef.Yesterday_Cumulative_Thermal_Time = CropStateRef.Cumulative_Thermal_Time;  //LML 140826 moved here
    }
    //'Reset thermal time for given conditions
    if (CropParametersRef.Perennial_Crop) {
            if (Management.Clipping_Event) {
                CropStateRef.Yesterday_Cumulative_Thermal_Time = 0;
                CropStateRef.Cumulative_Thermal_Time = Degree_Days;
                Management.Clipping_Event = false;
            }
            if (CropStateRef.First_Day_Of_Dormancy) {
                CropStateRef.Yesterday_Cumulative_Thermal_Time = 0;
                CropStateRef.Cumulative_Thermal_Time = Degree_Days;
                CropStateRef.First_Day_Of_Dormancy = false;
            }
            if (CropStateRef.First_Day_Of_Dormancy_Broken) {
                CropStateRef.Yesterday_Cumulative_Thermal_Time = 0;
                CropStateRef.Cumulative_Thermal_Time = Degree_Days;
                CropStateRef.First_Day_Of_Dormancy_Broken = false;
            }
    }
    double Current_Cumulative_Thermal_Time = CropStateRef.Cumulative_Thermal_Time;
    double Thermal_Time_To_Start_Growing_Season(0.0);
    int Period_Length(0);
    double Period_Mean_Temperature(0.0);
    //'Check for start of growing season
    if (!Simulation.pSimulationRotation->getCropSeasonStarted()) {
        //'Set thermal time required to start growing season for annual && fruit tree crops
        if (CropParametersRef.Perennial_Crop) {
            if (CropParametersRef.Tree_Fruit_Crop) {
                if (CropStateRef.Chill_Requirement_Satisfied)
                    Thermal_Time_To_Start_Growing_Season = 
                        CropParametersRef.Thermal_Time_For_Budbreak_If_Chill_Reached; 
                        //'this is thermal time for budbreak in the case of trees
                else
                    Thermal_Time_To_Start_Growing_Season = 
                        CropParametersRef.Thermal_Time_For_Budbreak_If_Chill_Not_Reached;
            }
        } else {
            Thermal_Time_To_Start_Growing_Season = CropParametersRef.Thermal_Time_for_Emergence;
        } //'End of set thermal time required to start growing season
        //'Search for the start of growing season
        if (CropParametersRef.Perennial_Crop) {
            if (CropParametersRef.Tree_Fruit_Crop) { //' Tree fruit crop
                if (Current_Cumulative_Thermal_Time >= Thermal_Time_To_Start_Growing_Season) {
                    Simulation.pSimulationRotation->setCropSeasonStarted(true);
                    CropStateRef.Crop_Dormant = false;
                    CropStateRef.Dormancy_Broken = true;
                    CropStateRef.First_Day_Of_Dormancy_Broken = true;
                    CropStateRef.Days_After_Crop_Exist_At_Start_Of_Season = 
                        Simulation.pTimeState->getDaysAfterCropExists();
                    CropStateRef.DOY_Start_Growing_Season = doy;
                    CropStateRef.Cumulative_Thermal_Time = 0;
                    Current_Cumulative_Thermal_Time = CropStateRef.Cumulative_Thermal_Time;
                }
            } else {   // 'perennial crop, but not tree fruit crop
                Period_Length = 14;
                if (doy >= CropParametersRef.DOY_End_Dormancy && 
                    Simulation.pSimulationRotation->getNumberOfSimulationDays() >= Period_Length) {
                    Weather.DetermineTimeWindowMeanTemperature(Period_Length, Period_Mean_Temperature);
                    if (Period_Mean_Temperature > CropParametersRef.Base_Temperature_for_Development) {
                        Simulation.pSimulationRotation->setCropSeasonStarted(true);
                        CropStateRef.Crop_Dormant = false;
                        CropStateRef.Days_After_Crop_Exist_At_Start_Of_Season = 
                            Simulation.pTimeState->getDaysAfterCropExists();
                        CropStateRef.DOY_Start_Growing_Season = doy;
                    }
                }
            }
        } else { //'annual crop
                if (Current_Cumulative_Thermal_Time >= Thermal_Time_To_Start_Growing_Season) {
                    Simulation.pSimulationRotation->setCropSeasonStarted(true);
                    CropStateRef.Crop_Emerged = true;
                    Simulation.pSimulationRotation->setCropEmerged(true);   
                    CropStateRef.DOY_Emergence = doy;
                    CropStateRef.Days_After_Crop_Exist_At_Start_Of_Season = 
                        Simulation.pTimeState->getDaysAfterCropExists();
                    CropStateRef.DOY_Start_Growing_Season = doy;
                }
        }
    }   //End of check for start of growing season
    //'Search for harvest of annual crops
    if (!CropParametersRef.Perennial_Crop && CropStateRef.Mature) {
        if (Simulation.pTimeState->getDaysAfterPhysiologicalMaturity() == 10) {   
            // 'Harvest is assumed to occur 10 days after maturity
            CropStateRef.Harvested = true;
            CropStateRef.DOY_Harvest = doy;
            CropStateRef.Days_After_Crop_Exist_At_End_Of_Season = 
                Simulation.pTimeState->getDaysAfterCropExists();
            Simulation.pSimulationRotation->setCropTerminated(true);
            Simulation.pSimulationRotation->setCropExist(false);
            Simulation.pSimulationRotation->setNewCropFound(false);
            Simulation.pSimulationRotation->setCropSeasonStarted(false);
        }
    } //'End of search for harvest of annual crops
    //'Search for harvest of tree fruit crops
    if (CropParametersRef.Tree_Fruit_Crop && CropStateRef.Mature) {
        if (Simulation.pTimeState->getDaysAfterPhysiologicalMaturity() == 5) { 
            //'Harvest is assumed to occur 5 days after maturity
            CropStateRef.Harvested = true;
            CropStateRef.DOY_Harvest = doy;
        }
    }   // 'End of search for harvest of tree fruit crops
    //'Check for beginning of dormancy of perennial crops
    Period_Length = 14;
    if (CropParametersRef.Perennial_Crop && 
      doy >= CropParametersRef.DOY_Start_Dormancy && 
      !CropStateRef.Crop_Dormant &&
      Simulation.pSimulationRotation->getNumberOfSimulationDays() >= Period_Length) {
        Weather.DetermineTimeWindowMeanTemperature(Period_Length, Period_Mean_Temperature);
        if (Period_Mean_Temperature < CropParametersRef.Base_Temperature_for_Development) {
            Simulation.pSimulationRotation->setCropSeasonStarted(false);
            CropStateRef.Harvested = false;
            CropStateRef.Crop_Dormant = true;
            CropStateRef.Dormancy_Broken = false;
            CropStateRef.First_Day_Of_Dormancy = true;
            CropStateRef.Days_After_Crop_Exist_At_End_Of_Season = 
                Simulation.pTimeState->getDaysAfterCropExists();
            Simulation.pTimeState->setDaysAfterPhysiologicalMaturity(0);
            if (CropParametersRef.Tree_Fruit_Crop) {
                CropStateRef.Chill_Requirement_Satisfied = false;
                Weather.setAccumulateChillHours(true);
            }
        }
    }   // 'End of check for beginning of dormancy of perennial crops
    //Define && report crop growth stages
    if (!Simulation.pSimulationRotation->getCropSeasonStarted()) {
        if (!CropParametersRef.Perennial_Crop)
            CropStateRef.Development_Stage = "Pre-emergence";
        else
            CropStateRef.Development_Stage = "Dormant";
    }
    if (Simulation.pSimulationRotation->getCropSeasonStarted() && 
      Current_Cumulative_Thermal_Time < CropParametersRef.Thermal_Time_for_Flowering) {
        CropStateRef.Development_Stage = "Vegetative";
        Simulation.pTimeState->setDaysAfterGrowingSeasonStarted(
            Simulation.pTimeState->getDaysAfterGrowingSeasonStarted() + 1);
    }
    if ((Current_Cumulative_Thermal_Time >= CropParametersRef.Thermal_Time_for_Flowering) &&
        (Current_Cumulative_Thermal_Time < CropParametersRef.Thermal_Time_for_Yield_Formation)) {
        if (CropParametersRef.Tree_Fruit_Crop && 
            !Simulation.pSimulationRotation->getCropSeasonStarted()) {
            CropStateRef.Development_Stage = "Dormant";
        } else {
            CropStateRef.Development_Stage = "Flowering";
            Simulation.pTimeState->setDaysAfterGrowingSeasonStarted(
                Simulation.pTimeState->getDaysAfterGrowingSeasonStarted() + 1);
            if (CropStateRef.Flowering == false) {
                CropStateRef.Flowering = true;
                CropStateRef.DOY_Flowering = doy;
            }
        }
    }
    //std::cout<<" DOY:"<<DOY<<" Current_Cumulative_Thermal_Time:"<<Current_Cumulative_Thermal_Time
            //<<" Thermal_Time_for_Yield_Formation:"<<CropParametersRef.Thermal_Time_for_Yield_Formation
            //<<" Thermal_Time_for_Maturity:"<<CropParametersRef.Thermal_Time_for_Maturity
            //<<std::endl;
    if ((Current_Cumulative_Thermal_Time >= CropParametersRef.Thermal_Time_for_Yield_Formation) &&
        (Current_Cumulative_Thermal_Time < CropParametersRef.Thermal_Time_for_Maturity)) {
            if (CropParametersRef.Root_Crop) CropStateRef.Development_Stage = "Root_Bulking";
            if (CropParametersRef.Grain_Crop) CropStateRef.Development_Stage = "Grain_Filling";
            if (CropParametersRef.Perennial_Crop) {
                if (CropParametersRef.Tree_Fruit_Crop)
                    CropStateRef.Development_Stage = "Fruit_Growth";
                else
                    CropStateRef.Development_Stage = "Seed_Formation";
            }
            Simulation.pTimeState->setDaysAfterGrowingSeasonStarted(
                Simulation.pTimeState->getDaysAfterGrowingSeasonStarted() + 1);
            CropStateRef.Flowering = false;
            if (CropStateRef.Crop_Forming_Yield == false) {
                CropStateRef.Crop_Forming_Yield = true;
                CropStateRef.DOY_Begin_Yield_Formation = doy;
            }
     }
    if (Current_Cumulative_Thermal_Time >= CropParametersRef.Thermal_Time_for_Maturity) {
                CropStateRef.Development_Stage = "Maturity";
                if (!(CropParametersRef.Perennial_Crop && CropStateRef.Crop_Dormant)) {
                    Simulation.pTimeState->setDaysAfterGrowingSeasonStarted(
                        Simulation.pTimeState->getDaysAfterGrowingSeasonStarted() + 1);
                    Simulation.pTimeState->setDaysAfterPhysiologicalMaturity(
                        Simulation.pTimeState->getDaysAfterPhysiologicalMaturity() + 1);
                }
                CropStateRef.Crop_Forming_Yield = false;
                if (CropStateRef.Mature == false) {
                    CropStateRef.Mature = true;
                    CropStateRef.First_Day_Of_Maturity = true;
                    CropStateRef.DOY_Physiological_Maturity = doy - 1;
                    CropStateRef.Days_After_Crop_Exist_At_Maturity = DACE - 1;
                }
    }
    if (CropParametersRef.Perennial_Crop && CropStateRef.Crop_Dormant) 
        CropStateRef.Development_Stage = "Dormant";
    if (!CropParametersRef.Perennial_Crop && CropStateRef.Harvested) 
        CropStateRef.Development_Stage = "Harvested";
    if (CropParametersRef.Perennial_Crop && CropStateRef.Harvested) 
        CropStateRef.Development_Stage = "Harvested";
}
