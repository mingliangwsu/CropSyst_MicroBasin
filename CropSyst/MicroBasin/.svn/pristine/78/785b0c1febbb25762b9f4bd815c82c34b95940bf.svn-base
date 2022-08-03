#ifndef CROPSYST_VERSION
// This is becoming obsolete - 150707RLN
#include "simulationrotationclass.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "string.h"
#include "util/pubtools.h"

SimulationRotationClass::SimulationRotationClass
(AllControlClass  &_ControlRef
,const CORN::Date &_today                                                        //150630
,clsManagement    &_ManagementRef)
:ControlRef(_ControlRef)
,today(_today)                                                                   //150630
,ManagementRef(_ManagementRef)                                                   //150522
{
    num_crops = ControlRef.getMaxNumCropsEachGrid();
    num_rotations = 1;                                                           //150511
    //150522 for (int i = 0; i < MAX_ROTATIONS; i++) bmatched_planting_year[i] = false;

    //Crop_Name = new std::string[num_crops];
    //Management_Name = new std::string[num_crops];
    //Planting_Year = new int[num_crops];
    //Planting_DOY = new int[num_crops];

    Crop_Planted = false;
    Crop_Emerged = false;
    Crop_Harvested = false;
    Crop_Stubble_Present = false;
    Surface_Residue_Present = false;
    New_Crop_Found = false;
    Crop_Exist = false;
    Crop_Season_Started = false;
    Crop_Terminated = false;
    Current_Management_Index = -1;                                               //150526
    //Current_Management_Name
}
//______________________________________________________________________________
SimulationRotationClass::~SimulationRotationClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~SimulationRotationClass:"<<std::endl;
#endif
    //LML 14/0607 CHECK!!!
    //delete[] Planting_Year;
    //delete[] Planting_DOY;
    //delete[] Management_Name;     //LML 140609 crash! Need work on it later
    //delete[] Crop_Name;           //LML 140609 crash! Need work on it later

#ifdef Destruct_Monitor
    std::cout<<"~SimulationRotationClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void SimulationRotationClass::setNumberOfSimulationDays(int NSD) {Number_Of_Simulation_Days = NSD;}
int SimulationRotationClass::getNumberOfSimulationDays() {return Number_Of_Simulation_Days;}
std::string SimulationRotationClass::getLocationName() {return Location_Name;}
std::string SimulationRotationClass::getSoilName() {return Soil_Name;}
int SimulationRotationClass::getRotationCycleLength() {return Rotation_Cycle_Length;}
int SimulationRotationClass::getCurrentCrop() {return Current_Crop;}
std::string SimulationRotationClass::getCropName(int X) {return Crop_Name[X];}
std::string SimulationRotationClass::getManagementName(int X) {return Management_Name[X];}
void SimulationRotationClass::setPlantingYear(int X,int PD) {Planting_Year[X] = PD;}
int SimulationRotationClass::getPlantingYear(int X) {return Planting_Year[X];}
bool SimulationRotationClass::getSummaryOutput() {return Summary_Output;}
void SimulationRotationClass::setCropSeasonStarted(bool X) {Crop_Season_Started = X;}
bool SimulationRotationClass::getCropSeasonStarted() {return Crop_Season_Started;}
void SimulationRotationClass::setCropPlanted(bool CP) {Crop_Planted = CP;}
bool SimulationRotationClass::getCropPlanted() {return Crop_Planted;}
void SimulationRotationClass::setCropEmerged(bool CE) {Crop_Emerged = CE;}
bool SimulationRotationClass::getCropEmerged() {return Crop_Emerged;}
void SimulationRotationClass::setCropHarvested(bool CH) {Crop_Harvested = CH;}
bool SimulationRotationClass::getCropHarvested() {return Crop_Harvested;}
void SimulationRotationClass::setCropStubblePresent(bool CSP) {Crop_Stubble_Present = CSP;}
bool SimulationRotationClass::getCropStubblePresent() {return Crop_Stubble_Present;}
void SimulationRotationClass::setSurfaceResiduePresent(bool SRP) {Surface_Residue_Present = SRP;}
bool SimulationRotationClass::getSurfaceResiduePresent() {return Surface_Residue_Present;}
void SimulationRotationClass::setNewCropFound(bool NCF) {New_Crop_Found = NCF;}
bool SimulationRotationClass::getNewCropFound() {return New_Crop_Found;}
void SimulationRotationClass::setCropTerminated(bool CT) {Crop_Terminated = CT;}
bool SimulationRotationClass::getCropTerminated() {return Crop_Terminated;}
void SimulationRotationClass::setPlantingDOY(int X,int PDOY) {Planting_DOY[X] = PDOY;}
int SimulationRotationClass::getPlantingDOY(int X) {return Planting_DOY[X];}
void SimulationRotationClass::setNextPlantingDOY(int NPDOY) {Next_Planting_DOY = NPDOY;}
int SimulationRotationClass::getNextPlantingDOY() {return Next_Planting_DOY;}
void SimulationRotationClass::setCurrentCropName(std::string CrN) {Current_Crop_Name = CrN;}
std::string SimulationRotationClass::getCurrentCropName() {return Current_Crop_Name;}

void SimulationRotationClass::setCropExist(bool CE) {Crop_Exist = CE;}
bool SimulationRotationClass::getCropExist() {return Crop_Exist;}
void SimulationRotationClass::setDeleteAllOutputFiles(bool DAOF) {Delete_All_Output_Files = DAOF;}
bool SimulationRotationClass::getDeleteAllOutputFiles() {return Delete_All_Output_Files;}
//______________________________________________________________________________
std::string SimulationRotationClass::getRotationFileName(int rotation_id)
{
   #ifdef LIU_ENGINE
    std::ostringstream ss("");
    ss<<ControlRef.rotation_prefix_name<<rotation_id<<ControlRef.rotation_suffix_name;
    return ss.str();
   #else
   std::string rotation_ID;
   CORN::wstring_to_string(ControlRef.rotation_filename.get_name(),rotation_ID);
   CORN::append_nat16_to_string((nat16)rotation_id, rotation_ID);
   CORN::OS::File_name_concrete rotation_filename
      (ControlRef.rotation_filename.get_parent_directory_name_qualified()
      ,rotation_ID
      ,ControlRef.rotation_filename.get_extension());
   std::string result(rotation_filename.c_str());
   return result;
   #endif
}
//______________________________________________________________________________
void SimulationRotationClass::ReadParameters(clsSimulation &Simulation)
{
    char errormessage[200];
    int year,doy;
    std::string record_key;
    std::string nameline,dataline;
    std::stringstream ss;
    std::ifstream ifile;
    std::string filename;
    int total_rotations = 0;
    int rotation_id     = -1;
    int rotation_nums   = 0;
    int crop_index      = -1;
    int crop_nums       = 0;

    filename = getRotationFileName(Simulation.pGridCellRef->getCropRotationID());

#ifdef LIU_DEBUG
    //std::cout<<"Rotation file name:"<<filename<<std::endl;
#endif
    New_Crop_Found = false;
    Crop_Exist = false;
    ifile.open(filename.c_str());
    if (ifile.is_open()) {
        while (std::getline(ifile,nameline)) {
            record_key = getKeyWord(nameline);
            if (!record_key.empty()) {
                //read the data line
                std::getline(ifile,dataline);
                ss.clear();
                ss.str(dataline);
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Num_Rotations") == 0) {
                        ss>>total_rotations;
                        num_rotations = total_rotations;
                    } else if (record_key.compare("Years_In_Rotation") == 0) {
                        ss>>Rotation_Cycle_Length;
                    } else if (record_key.compare("Rotation") == 0) {
                        ss>>rotation_id;
                        rotation_nums++;
                    /*150522
                    } else if (record_key.compare("Barren_Management_Name") == 0) {
                        removeWhitespace(dataline);
                        default_Management_Name = dataline;
                    */
#ifdef LIU_DEBUG
                        //std::cout<<"Barren_Management_Name:"<<default_Management_Name<<std::endl;
#endif
                    } else if (record_key.compare("Crop_Name") == 0) {
                        crop_index++;
                        crop_nums++;
                        removeWhitespace(dataline);
                        Crop_Name.push_back(dataline);
                        //150522 Crop_Name[rotation] = dataline;
#ifdef LIU_DEBUG
                        //std::cout<<"Rotation:"<<rotation<<"Crop_Name:"
                        //         <<Crop_Name[rotation]<<std::endl;
#endif
                    } else if (record_key.compare("Management_Name") == 0) {
                        removeWhitespace(dataline);
                        Management_Name.push_back(dataline);
                        //Management_Name[rotation] = dataline;
                    } else if (record_key.compare("Planting_Year_DOY") == 0) {
                        ss>>year>>doy;
                        Planting_Year.push_back(year);
                        Planting_DOY.push_back(doy);
                        //Planting_Year[rotation] = year;
                        //Planting_DOY[rotation] = doy;
                    } else {
                        sprintf(errormessage,"Warning: Cann't find keyword %s",
                            record_key.c_str());
                        //nrerror(errormessage);
                    }
                }
            }
        }
    } else {
        sprintf(errormessage,"Cann't open rotation file %s",filename.c_str());
        nrerror(errormessage);
    }

    //150522 if ((rotation+1) != num_crops) {
    if (rotation_nums != num_rotations) {
        sprintf(errormessage,"Num_rotations in parameter files %s are not consistant",
                filename.c_str());
        nrerror(errormessage);
    }
    //150522
    num_crops = crop_nums;
    bmatched_planting_year.resize(crop_nums);
    for (int i = 0; i < crop_nums; i++) {
        bmatched_planting_year[i] = false;
    }
}
//______________________________________________________________________________
void SimulationRotationClass::DeterminePlantingDate(clsSimulation &Simulation)
{
    //LML 140829 need talk with Claudio to decide which management will be 
    //taken before planting or harvest time 
    /*150701RLN today reference already available
    int year,doy;
    year = Simulation.pTimeState->getToday().get_year();
    doy = Simulation.pTimeState->getToday().get_DOY();
    */
    CORN::Year year = today.get_year();                                          //150701RLN
    CORN::DOY  doy  = today.get_DOY();                                           //150701RLN
    if (/*150630RLN ControlRef.*/today == ControlRef.start_date || !Crop_Exist)
        //150522 Current_Management_Name = default_Management_Name;
        //ControlRef.parrManagementSchedule[0].Management_Name;   //LML 140827
    for (int rotation = 0; rotation < num_crops; rotation ++) {
        if (!bmatched_planting_year[rotation]) {
            bmatched_planting_year[rotation] = 
                FindAndMatchYearForRotationEvents(Planting_Year[rotation]
                                                  ,Planting_DOY[rotation]
                                                  ,year
                                                  ,doy
                                                  ,Rotation_Cycle_Length);
        }
        if ((year == Planting_Year[rotation]) && (doy == Planting_DOY[rotation])) {
            Crop_Exist = true;
            New_Crop_Found = true;
            Current_Crop_Name = Crop_Name[rotation];
            Current_Management_Index = ControlRef.find_management_index(Management_Name[rotation]); //150526
            //150522 Current_Management_Name = Management_Name[rotation];    //LML 140827
            Next_Planting_DOY = Planting_DOY[rotation];
            Planting_Year[rotation] += Rotation_Cycle_Length;
        }
    }
}
//_150522_______________________________________________________________________
void SimulationRotationClass::SetManagementEvents()
{
    //Get management events list from ControlRef parrManagementSchedule
    ManagementRef.pSchedule->Clear_All_Events();
    for (int crop_index = 0; crop_index < num_crops; crop_index ++) {
        int management_index = ControlRef.find_management_index(Management_Name[crop_index]);
        if (management_index < 0) {
            std::cerr<<" Can't find management parameters: "<<Management_Name[crop_index]<<std::endl;
            exit(0);
        }
        ManageScheduleClass *current_schedule = &ControlRef.parrManagementSchedule[management_index];
        ManagementRef.pSchedule->AppendFromOtherSchedule(current_schedule);
    }
}
//______________________________________________________________________________
#endif
