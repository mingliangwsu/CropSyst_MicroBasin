#if (CS_VERSION != 4)
#error This class is obsolete removed evaporation_abstract from your project
// now using soil_evaporator.cpp which should be added to your project
#endif

#include "soil/evaporation_abstract.h"
//______________________________________________________________________________
float64 Soil_evaporation_abstract
::get_hourly_fraction_of_daily_demand(CORN::Hour hour_0based)                const
{  // probably already have this somewhere for actually 30min
   int Hour_1based = hour_0based + 1;
   // 'This is a Mickey Mouse function to avoid implementing a real one - Claudio
   float64 fraction = 0.0;
   switch (Hour_1based)
   {  case 5:  case 19 : fraction = 0.014; break;
      case 6:  case 18 : fraction = 0.033; break;
      case 7:  case 17 : fraction = 0.051; break;
      case 8:  case 16 : fraction = 0.069; break;
      case 9:  case 15 : fraction = 0.084; break;
      case 10: case 14 : fraction = 0.095; break;
      case 11: case 12:  case  13:  fraction = 0.1; break;
      default : 0.0;  break; // all other hours
   };
   return  fraction;
};
//_2005-11-30_____________________________get_hourly_fraction_of_daily_demand__/
