#ifndef SOILOMANDRESIDUEMASTERCLASS_H
#define SOILOMANDRESIDUEMASTERCLASS_H
#include "soil/soilorganiccarbonclass.h"
#include "organicresidual/organicresidueclass.h"
#include "organicresidual/organicresiduestateclass.h"
#include "weather/weatherstatedailyclass.h"
#include "control/debugstateclass.h"
#include "management/clsmanagement.h"
#include "control/clssimulation.h"

class clsManagement;
class SoilOrganicCarbonClass;
class OrganicResidueClass;
class OrganicResidueStateClass;
class clsSimulation;
//______________________________________________________________________________
class SoilOMAndResidueMasterClass
{

public:
    SoilOrganicCarbonClass *parrLayer_SOM_Pools;
    //'referencing
    SoilProfileClass &SoilProfileRef;
    SoilStateClass &SoilStateRef;
    OrganicResidueClass &OrganicResidueRef;
    OrganicResidueStateClass &OrganicResidueStateRef;
    clsSoil &SoilRef;
 private:
    const CORN::Date &today;                                                     //150630RLN
public:
    SoilOMAndResidueMasterClass
       (SoilProfileClass &_SoilProfileRef
       ,SoilStateClass &_SoilStateRef
       ,OrganicResidueClass &_OrganicResidueRef
       ,OrganicResidueStateClass &_OrganicResidueStateRef
       ,clsSoil &_SoilRef
       ,const CORN::Date &today);                                                //150630RLN
    ~SoilOMAndResidueMasterClass();
    void DailyProcess(clsSimulation &Simulation, DebugStateClass &DebugState);
    void OrganicCarbonMixingDueToTillage(clsManagement &Management,clsSimulation &Simulation);
    void InitializeSoilOrganicMatter(clsSimulation &Simulation);
    
    double getProfileSOMCarbonMass();
    double getProfileSOMNitrogenMass();
    double getTotalOrganicCarbonMass();
    double getTotalOrganicNitrogenMass();

};
//______________________________________________________________________________
#endif // SOILOMANDRESIDUEMASTERCLASS_H
