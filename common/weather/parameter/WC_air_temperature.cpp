#include "weather/parameter/WC_air_temperature.h"
//______________________________________________________________________________
const CORN::Quality & Air_temperature_average_calculator::update()        rectification_
{  if (is_valid())
   {}
   else
   {  if (updating)
      {  // We are already updating, so don't come here yet again
      } else
      {  updating = true;
         if (air_Tmax && air_Tmin)
         {
            float64 Tavg = ((air_Tmax->Celcius() + air_Tmin->Celcius()) / 2.0);  //150130
            update_value_qualified(Tavg,air_Tmax->worst(*air_Tmin));             //150130 170324LML seems the quality is not correct
         }
         updating = false;
      }
   }
   return get_quality();
}
//______________________________________________________________________________

