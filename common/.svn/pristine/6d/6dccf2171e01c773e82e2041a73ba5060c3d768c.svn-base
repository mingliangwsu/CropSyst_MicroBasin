#ifndef weather_generator_databaseH
#define weather_generator_databaseH

#include <common/weather/database/weather_UED_database.h>
#include <ClimGen/source/ClimGen_generator.h>

// This class take as input a ClimGen location parameter file.
// instead of reading data from a file, the data
// is generated on the fly.
// UED in-memory storage.
//______________________________________________________________________________
class Weather_generated_on_the_fly_database
: public Weather_UED_database
{Climate_generator generator;
 public:
   Weather_generated_on_the_fly_database(const char *ClimGen_location_filename);
   inline virtual void start(const CORN::Date &start_date) {};
   void set_today(const CORN::Date &new_today)
};
//_2006-02-13___________________________________________________________________

#endif
