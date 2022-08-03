#ifndef station_databaseH
#define station_databaseH
#include "UED/library/database_file.h"
#include "common/weather/validator.h"
//180107 #include "corn/container/association.h"
//______________________________________________________________________________
class Station_database
: public CORN::Item //180101 Association
{
private:
   Weather_validator    *weather_data_validator; // may be 0 if we dont have a validator yet.
public:
   std::string        station_ID;
      // The UED filename will be composed from this.
      // For NCDC, this is the coop_ID
   UED::Database_file_indexed ued_file;
public:
   inline Station_database
      (const std::string &_station_ID
      ,const std::string  &_ued_file
      ,std::ios_base::openmode _openmode )
      : ued_file(_ued_file.c_str()                                               //090515
         ,_openmode                                                              //130311
         ,false  // actually may want to allow float16
         )
      , station_ID(_station_ID)
      , weather_data_validator(0)
      {  ued_file.initialize(); }
   virtual ~Station_database();
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return station_ID == key; }

/*180820  was probably only used for find_cstr now using is_key
   
   inline virtual const char *get_key()                                    const
      {  return station_ID.c_str(); }
*/
   Weather_validator    *provide_weather_data_validator();
      // Will return 0 if no location record available in database
};
//______________________________________________________________________________
#endif

