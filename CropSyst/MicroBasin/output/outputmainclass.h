#ifndef OUTPUTMAINCLASS_H
#define OUTPUTMAINCLASS_H
#ifndef CROPSYST_VERSION
#include "snow/clssnow.h"
#endif
//160722RLN not currently used #include "control/simulationbalanceclass.h"
#include "control/allcontrolclass.h"
#ifndef CROPSYST_VERSION
#  ifdef CROPSYST_PROPER_CROP
#  else
#     include "crop/clscrop.h"
#  endif
#endif
#ifdef MBVB_SOIL
#include "soil/clssoil.h"
#endif
//160225RLN obsolete #include "control/clssimulation.h"
#include "output/outputdailysoilclass.h"
#include "outputgrowthclass.h"
#include "output/outputgrowthseasonclass.h"
#include "output/outputannualclass.h"
#include "output/outputhourclass.h"
#include <vector>
//#include "datetime/date.hpp"                                                     //151005LML

class BasinCellClass;
class SimulationBalanceClass;
#ifdef CROPSYST_PROPER_CROP
/*141005
namespace CropSyst
{
   interface_ Crop_interfaced;
}
*/
#define clsCrop CropSyst::Crop_interfaced
#else
class clsCrop;
#endif
class clsSoil;
class clsSimulation;
class clsSnow;
class OutputDailySoilClass;
class OutputHourClass;
class OutputGrowthClass;
class OutputAnnualClass;
#ifdef VB_SAME_CSV_OUTPUT
//______________________________________________________________________________
class OutputMainClass
{
    bool Daily_Output;
    bool Daily_Soil_Output;
    bool Growing_Season_Output;
    bool Annual_Output;
    bool Carbon_Output;
    //All start from 0
    int Hour_Sequence;
    int Soil_Day_Sequence;
    int Growth_Day_Sequence;    //days with crop growth
    int Growth_Season_Sequence;
    int Annual_Sequence;
    BasinCellClass *gridcell_ref;
//    #ifndef CELL_METEOROLOGY
//    BasinClass     *basin_ref;
//    #endif
    //151002LML TimeStateClass& TimeStateRef;
    //151002LML SimulationBalanceClass& BalanceRef;
    //151002LML AllControlClass& AllcontrolRef;
//151002LML #ifndef CROPSYST_VERSION
// The operator overrides are not working in BC++
//151002LML     int DaysDifference(const CORN::Date &tdate1,const CORN::Date &tdate2);
//151002LML #endif
    const CORN::Date_const &today;                                                     //160225
public:
    //Daily Soil [year][DOY]
    std::vector<OutputDailySoilClass> pDaily_Soil;       //For everyday
    //OutputGrowthClass *pGrowth;              //For everyday after crop exist
    std::vector<OutputGrowthClass> pGrowth;                 //LML 150115
    //OutputGrowthSeasonClass *pGrowth_Season;
    std::vector<OutputGrowthSeasonClass> pGrowth_Season;    //LML 150115
    std::vector<OutputAnnualClass> pAnnual;
    std::vector<OutputHourClass> pHour;
    //151002LML clsSnow *pSnowRef;
public:
    OutputMainClass
       (const CORN::Date_const &today_                                                 //160225RLN
       ,BasinCellClass   *gridcell_ref_
//       #ifndef CELL_METEOROLOGY
//       ,BasinClass     *basin_ref_
//       #endif
       );                                        //151005LML
    ~OutputMainClass();
    //160225RLN obsolete inline bool Set_Gridcell_ref(BasinCellClass *_gridcell_ref)                  {gridcell_ref = _gridcell_ref; return true;}
    void initialize();
    #ifdef VB_SAME_CSV_OUTPUT
    void WriteGrowingSeasonOutput
        (/*clsCrop &Crop
        , clsSoil &Soil*/);
    void WriteDailySoilCropOutput
        (/*clsSoil &Soil
        , WeatherStateDailyClass &Weather
        , clsCrop &Crop*/
        //#ifdef CROPSYST_VERSION
        //const CORN::Date_const &today
        //#endif
         );
    void WriteDailyGrowthOutput
        (/*clsSimulation &Simulation
        #ifdef CROPSYST_PROPER_CROP
        ,const CropSyst::Crop_interfaced &crop                                             //140502
        #else
        , clsCrop &Crop
        #endif
        */);
    void WriteHourlyOutput
       (
       //#ifdef CROPSYST_VERSION
       //160225RLN now referenced const CORN::Date &today,
        const int current_hour
       //#endif
       );
    void WriteAnnualSoilOutput();
    #endif
    int getHourSequence();
    int getSoilDaySequence();
    int getGrowthDaySequence();
    int getGrowthSeasonSequence();
    int getAnnualSequence();
};
//______________________________________________________________________________
#endif
#endif // OUTPUTMAINCLASS_H

