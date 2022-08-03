#ifndef WC_vapor_pressureH
#define WC_vapor_pressureH

#include "weather/parameter/WP_vapor_pressure.h"
#include "corn/chronometry/date_types.hpp"
#include "weather/parameter/WP_dew_point_temperature.h"

class Relative_humidity;
class Air_temperature_maximum;
class Air_temperature_minimum;
class Vapor_pressure_actual;
struct Vapor_pressure_night_time_parameters;                                     //091210
//______________________________________________________________________________
class Vapor_pressure_parameter   // Rename this to Vapor_pressure_calculator
{protected:  // These are actually available in vapor_pressure_deficit_max
   Dew_point_temperature_maximum   *dew_point_temperature_max;   // May be 0 if unknown  // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
   Relative_humidity       *relative_humidity_min;       // May be 0 if unknown  // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
   Air_temperature_maximum *air_temperature_max;     // May be 0 if unknown
   Air_temperature_minimum *air_temperature_min;     // May be 0 if unknown
 public: // Constructor
   Vapor_pressure_parameter
      (Dew_point_temperature_maximum   *_dew_point_temperature_max   // May be 0 if unknown  // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
      ,Relative_humidity       *_relative_humidity_min   // May be 0 if unknown
         // used by Vapor_pressure_deficit_parameter and Vapor_pressure_actual_parameter
      ,Air_temperature_maximum *_air_temperature_max     // May be 0 if unknown
      ,Air_temperature_minimum *_air_temperature_min);   // May be 0 if unknown

//081024  this abstract class doesn't have anything to update
};
//_2005-06-02___________________________________________________________________
class Vapor_pressure_daytime_calculator                                          //140220
: public Vapor_pressure_daytime                                                  //140220
{
protected:
   Dew_point_temperature_maximum *dew_point_temperature_max;
   Air_temperature_maximum       *air_temperature_max;   // optional, if not provided we presume non freezing conditions
protected: // While it is sort of possible to estimate the maximum vapor pressure from the Vapor_pressure_nighttime_parameter
            // by 'inverting' the equation of the  vapor_pressure_regression_model
            // This is not done because Vapor_pressure_daytime_parameter is considered the independent variable.
            // Vapor_pressure_daytime_parameter should be calculated from maximum dew pt.
                        // which may inturn come from minimum relative humidity calculated from VPD.
protected: // In the case that minimum  relative humidity is provided
   Relative_humidity             *relative_humidity_min;
public: // Constructor
   Vapor_pressure_daytime_calculator
      (Dew_point_temperature_maximum   *dew_point_temperature_max
      ,Air_temperature_maximum         *air_temperature_max);
      // use this constructor when dew_point_temperature_max is available
   Vapor_pressure_daytime_calculator
      (Relative_humidity               *relative_humidity_min
      ,Air_temperature_maximum         *air_temperature_max);
      // use this constructor when relative humidity min is available
   Vapor_pressure_daytime_calculator
      (Dew_point_temperature_maximum   *dew_point_temperature_max
      ,Relative_humidity               *relative_humidity_min
      ,Air_temperature_maximum         *air_temperature_max);
      // use this constructor when ether dew_point_temperature_max or relative_humidity_minis available
public:
   virtual const CORN::Quality &update()                         rectification_; //080908
   float64 calc_from_RHmin_VPsat_at_Tmax(CORN::Quality &calc_from_RHmin_VPsat_at_Tmax_qual) const; //081024
};
//_2008-10-24___________________________________________________________________
class Vapor_pressure_nighttime_calculator                                        //140220
: public Vapor_pressure_nighttime
{
 protected: // In the case that measure dew point temperature is provided
   Dew_point_temperature_minimum    *dew_point_temperature_min;
   Dew_point_temperature_maximum    *dew_point_temperature_max;                  //081030
   Air_temperature_minimum          *air_temperature_min; // optional, if not provided we presume non freezing conditions
 protected: // In the case that max and min vapor pressure has been correlated by linear regression.
   contribute_ const Vapor_pressure_night_time_parameters  *generation_parameters;
      // optional, needed only for ClimGen  //091210
   Vapor_pressure_daytime           *vapor_pressure_daytime;
   mutable CORN::DOY   curr_DOY_unused;                                          //081030
 protected: // In the case that maximum relative humidity is provided
   Relative_humidity                *relative_humidity_max;
 protected: // In the case specific humidity is provided
 public: // Constructors
   Vapor_pressure_nighttime_calculator  // Use when dew point temperature is known
      (Dew_point_temperature_minimum   *dew_point_temperature_min
      ,Air_temperature_minimum         *air_temperature_min);
   Vapor_pressure_nighttime_calculator  // Use when vapor pressure has been parameterized by ClimGen (for generation)
      (Vapor_pressure_daytime          *vapor_pressure_daytime
      ,Dew_point_temperature_maximum   *dew_point_temperature_max);              //081030

   Vapor_pressure_nighttime_calculator  // Use when relative humidity maximum and min air temperature is known
      (Relative_humidity               *relative_humidity_max
      ,Air_temperature_minimum         *air_temperature_min);
   Vapor_pressure_nighttime_calculator  // Use when there may be dew point temperature and/or ClimGen parameters
      (Dew_point_temperature_minimum   *dew_point_temperature_min
      ,Dew_point_temperature_maximum   *dew_point_temperature_max                //081030
      ,Air_temperature_minimum         *air_temperature_min
      ,Vapor_pressure_daytime          *vapor_pressure_daytime
      ,Relative_humidity               *relative_humidity_max);

 public:
   virtual const CORN::Quality &update()                         rectification_; //080908
   float64 calc_from_RHmax_VPsat_at_Tmin
      (CORN::Quality &calc_from_RHmax_VPsat_at_Tmin_qual)                 const; //081024
   inline CORN::DOY   know_DOY_unused(CORN::DOY new_DOY)         rectification_
      {curr_DOY_unused = new_DOY; return curr_DOY_unused; }                      //081030
public: // For ClimGen
   void know_generation_parameters                                               //091214
      (const Vapor_pressure_night_time_parameters &_generation_parameters) contribution_;
};
//_2008-10-24___________________________________________________________________
#endif

