#include "timestateclass.h"
//______________________________________________________________________________
TimeStateClass::TimeStateClass(
#ifndef LIU_ENGINE
const
#endif
   CORN::Date_const_interface &_today,int &_hour)
    :today(_today)
    ,Hour_Of_Day(_hour)
{
    FDHourlyCounter = 0;
}
//______________________________________________________________________________
int TimeStateClass::getFDHourlyCounter() {return FDHourlyCounter;}
//______________________________________________________________________________
void TimeStateClass::initialize()
{
    FDHourlyCounter = 0;
    Days_After_Planting = 0;
    Days_After_Emergence = 0;
    Days_After_Flowering = 0;
    Days_After_Begin_Yield_Formation = 0;
    Days_After_Physiological_Maturity = 0;
    Leaf_Senescence_Day_Pointer = 0;
    Last_Produced_Leaf_Day_Pointer = 0;
    Days_After_Crop_Exist = 0;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterPlanting(int DAP)
{
    Days_After_Planting = DAP;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterPlanting()
{
    return Days_After_Planting;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterEmergence(int DAE)
{
    Days_After_Emergence = DAE;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterEmergence()
{
    return Days_After_Emergence;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterFlowering(int DAF)
{
    Days_After_Flowering = DAF;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterFlowering()
{
    return Days_After_Flowering;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterBeginYieldFormation(int DABGF)
{
    Days_After_Begin_Yield_Formation = DABGF;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterBeginYieldFormation()
{
    return Days_After_Begin_Yield_Formation;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterPhysiologicalMaturity(int DAPM)
{
    Days_After_Physiological_Maturity = DAPM;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterPhysiologicalMaturity()
{
    return Days_After_Physiological_Maturity;
};
//______________________________________________________________________________
void TimeStateClass::setLeafSenescenceDayPointer(int LSDP)
{
    Leaf_Senescence_Day_Pointer = LSDP;
};
//______________________________________________________________________________
int TimeStateClass::getLeafSenescenceDayPointer()
{
    return Leaf_Senescence_Day_Pointer;
};
//______________________________________________________________________________
void TimeStateClass::setLastProducedLeafDayPointer(int LPLDP)
{
    Last_Produced_Leaf_Day_Pointer = LPLDP;
};
//______________________________________________________________________________
int TimeStateClass::getLastProducedLeafDayPointer()
{
    return Last_Produced_Leaf_Day_Pointer;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterCropExists(int DACE)
{
    Days_After_Crop_Exist = DACE;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterCropExists()
{
    return Days_After_Crop_Exist;
};
//______________________________________________________________________________
void TimeStateClass::setDaysAfterGrowingSeasonStarted(int DACE)
{
    Days_After_Growing_Season_Started = DACE;
};
//______________________________________________________________________________
int TimeStateClass::getDaysAfterGrowingSeasonStarted()
{
    return Days_After_Growing_Season_Started;
};
//______________________________________________________________________________
CORN::Date TimeStateClass::getToday() {return today;}
//______________________________________________________________________________
void TimeStateClass::setToday(const CORN::Date &_today) {today = _today;}
//______________________________________________________________________________
void TimeStateClass::setHourOfDay(const int hour) {Hour_Of_Day = hour;}
//______________________________________________________________________________
int TimeStateClass::getHourOfDay() {return Hour_Of_Day;}
