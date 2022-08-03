#ifndef clssimulationH
#define clssimulationH
#include "time/timestateclass.h"
#ifndef CROPSYST_VERSION
#include "control/simulationrotationclass.h"
#include "output/outputmainclass.h"
#endif
#include "control/allcontrolclass.h"
#include "util/simulationdefineconstantsclass.h"
//#include "control/simulationbalanceclass.h"
#include "soil/clssoil.h"
#include "basin/basincellclass.h"

//151015RLN #ifndef CROPSYST_VERSION
class OutputMainClass;
//151015RLN #endif
class SimulationBalanceClass;
class SimulationRotationClass;
class clsSoil;
class BasinCellClass;
//______________________________________________________________________________
class clsSimulation
{
 public:
    AllControlClass &ControlRef;
    const /*modifiable_*/ CORN::Date &today;                                                     //150630
    clsSoil &SoilRef;
    SimulationRotationClass *pSimulationRotation;
    TimeStateClass *pTimeState;
    SimulationDefineConstantsClass *pSimConstants;
    //151015RLN #ifndef CROPSYST_VERSION
    OutputMainClass *pOutput;
    //151015RLN #endif
    SimulationBalanceClass *pBalance;
    BasinCellClass *pGridCellRef;
    //150630RLN CORN::Date     &today;
    clsManagement  &ManagementRef;                                               //150522
 public:
    clsSimulation
       (AllControlClass &_ControlRef
       ,const /*modifiable_*/ CORN::Date &_today                                                 //150630RLN
       ,clsSoil &_SoilRef
       ,clsManagement &_ManagementRef);
    ~clsSimulation();
    void initializeNewDay();
    virtual bool initialize();                                                   //141221RLN
    void instantiateSimulation();

};
//______________________________________________________________________________
#endif // CLSSIMULATION_H

