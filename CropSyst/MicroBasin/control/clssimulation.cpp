#include "clssimulation.h"
#include "control/allcontrolclass.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//______________________________________________________________________________
clsSimulation::clsSimulation
( AllControlClass &_ControlRef
, /*modifiable_ */ const CORN::Date &_today                                                       //150630RLN
, clsSoil &_SoilRef, clsManagement &_ManagementRef)
: today(_today)                                                                   //150630RLN
, ControlRef(_ControlRef)
,SoilRef(_SoilRef)
//150630 ,today(_ControlRef.today)                                                        //141222
,ManagementRef(_ManagementRef)                                                   //150522
{
   instantiateSimulation();
}
//______________________________________________________________________________
clsSimulation::~clsSimulation()
{
#ifdef Destruct_Monitor
    std::cout<<"~clsSimulation:"<<std::endl;
#endif
    delete pSimConstants;
    delete pTimeState;
    delete pBalance;
#ifndef CROPSYST_VERSION
    delete pOutput;
    delete pSimulationRotation;
#endif
#ifdef Destruct_Monitor
    std::cout<<"~clsSimulation done."<<std::endl;
#endif
}
//______________________________________________________________________________
void clsSimulation::initializeNewDay()
{
    //Initialize soil water, carbon, and nitrogen balance
    pTimeState->setToday(today);    //141222 RLN this is redundent pTimeState should reference today
    pTimeState->setHourOfDay(0);    //start of day is zero
    pBalance->InitializeDailyBalances();
    #ifndef CROPSYST_VERSION
    //Find planting date for next crop
    if (pSimulationRotation->getNewCropFound() == false)
        pSimulationRotation->DeterminePlantingDate(*this);
    #endif
}
//______________________________________________________________________________
bool clsSimulation::initialize()                                                 //141221RLN
{
#ifdef LIU_DEBUG
    //std::cout<<"clsSimulation initializing..."<<std::endl;
#endif
    #ifndef CROPSYST_VERSION
    pSimulationRotation->ReadParameters(*this);
    pSimulationRotation->SetManagementEvents();                                  //150522
    #endif
    pTimeState->initialize();
    #ifndef CROPSYST_VERSION
    //RLN output disabled
    pOutput->initialize();
    #endif
#ifdef LIU_DEBUG
    //std::cout<<"clsSimulation Initialized."<<std::endl;
#endif
   return true;                                                                  //141221
}
//______________________________________________________________________________
void clsSimulation::instantiateSimulation()
{
    #ifndef CROPSYST_VERSION
    // CropSyst proper simulation engine has its own rotation management and scheduling
    pSimulationRotation = new SimulationRotationClass(ControlRef,today,ManagementRef); //150630
    #endif
    pSimConstants = new SimulationDefineConstantsClass;
    pTimeState = new TimeStateClass(/*150630 ControlRef.*/today,ControlRef.hour);
    pBalance = new SimulationBalanceClass(/**pTimeState,*/today,ControlRef,SoilRef); //150630
    #ifndef CROPSYST_VERSION
    //RLN output disabled
    pOutput = new OutputMainClass(*pTimeState,*pBalance,ControlRef);
    #endif
}
//______________________________________________________________________________
