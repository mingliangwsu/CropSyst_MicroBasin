#ifndef SIMULATIONROTATIONCLASSH
#define SIMULATIONROTATIONCLASSH
#include <string>
#include "control/allcontrolclass.h"
//141222RLN now permanent #ifdef CORN_DATE
#include "datetime/date.hpp"
//141222RLN now permanent #else
//141222RLN now permanent #include "time/BAO_date.h"
//141222RLN now permanent #endif
#include "control/clssimulation.h"
#include <vector>

//150522 #define MAX_ROTATIONS 5

class clsSimulation;
class AllControlClass;
class clsManagement;                                                             //150522
class SimulationRotationClass
{
    int Number_Of_Simulation_Days;
    int num_crops;      //crops
    int num_rotations;                                                           //150522
    std::string Location_Name;
    std::string Soil_Name;
    std::string default_Management_Name;    //LML 140829 management type when no crops there
    //bool bmatched_planting_year[MAX_ROTATIONS];         //LML 141212 check if planting year is matched
    std::vector<bool> bmatched_planting_year;
    int Grid_ID_Row;
    int Rotation_Cycle_Length;
    //std::string *Crop_Name;
    //std::string *Management_Name;
    //int *Planting_Year;
    //int *Planting_DOY;
    std::vector<std::string> Crop_Name;
    std::vector<std::string> Management_Name;
    std::vector<int> Planting_Year;
    std::vector<int> Planting_DOY;
    bool Summary_Output;
    bool Crop_Planted;
    bool Crop_Emerged;
    bool Crop_Harvested;
    bool Crop_Stubble_Present;
    bool Surface_Residue_Present;
    bool New_Crop_Found;
    bool Crop_Exist;
    bool Crop_Season_Started;
    bool Crop_Terminated;
    int Current_Crop;   //M. Liu
    bool Delete_All_Output_Files;
    int Next_Planting_DOY;
    std::string Current_Crop_Name;
    int Current_Management_Index;                                                //150526 Index from global management array if crop is planted
    //150522 std::string Current_Management_Name;    //LML 140827
    clsManagement &ManagementRef;                                                //150522
public:
    AllControlClass &ControlRef;
    const CORN::Date &today;                                                     //150630
    SimulationRotationClass
       (AllControlClass &_ControlRef
       ,const CORN::Date &_today                                                 //150630
       ,clsManagement &_ManagementRef);
    ~SimulationRotationClass();
    void ReadParameters(clsSimulation &Simulation);
    void SetManagementEvents();                                                  //150522 set all managements events
    void DeterminePlantingDate(clsSimulation &Simulation);
    void setNumberOfSimulationDays(int NSD);
    int getNumberOfSimulationDays();
    std::string getLocationName();
    std::string getSoilName();
    int getRotationCycleLength();
    int getCurrentCrop();
    //150522 std::string getCurrentManagementName() {return Current_Management_Name;};
    //150522 void setCurrentManagementName(std::string name) {Current_Management_Name = name;};
    std::string getCropName(int X);
    std::string getManagementName(int X);
    void setPlantingYear(int X,int PD);
    int getPlantingYear(int X);
    bool getSummaryOutput();
    void setCropSeasonStarted(bool X);
    bool getCropSeasonStarted();
    void setCropPlanted(bool CP);
    bool getCropPlanted();
    void setCropEmerged(bool CE);
    bool getCropEmerged();
    void setCropExist(bool CE);
    bool getCropExist();
    void setCropHarvested(bool CH);
    bool getCropHarvested();
    void setCropStubblePresent(bool CSP);
    bool getCropStubblePresent();
    void setSurfaceResiduePresent(bool SRP);
    bool getSurfaceResiduePresent();
    void setNewCropFound(bool NCF);
    bool getNewCropFound();
    void setCropTerminated(bool CT);
    bool getCropTerminated();
    void setPlantingDOY(int X,int PDOY);
    int getPlantingDOY(int X);
    void setNextPlantingDOY(int NPDOY);
    int getNextPlantingDOY();
    void setCurrentCropName(std::string CrN);
    std::string getCurrentCropName();
    void setDeleteAllOutputFiles(bool DAOF);
    bool getDeleteAllOutputFiles();
    std::string getRotationFileName(int rotation_id);
    int getCurrentManagementIndex() {return Current_Management_Index;};
};

#endif // SIMULATIONROTATIONCLASS_H
