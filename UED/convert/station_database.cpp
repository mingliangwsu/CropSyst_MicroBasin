#include "UED/convert/station_database.h"
#include "UED/library/locrec.h"
//______________________________________________________________________________
Weather_validator    *Station_database::provide_weather_data_validator()
{  if (!weather_data_validator)
     // We haven't allocated a weather validator yet
      weather_data_validator = new Weather_validator;
   if (!weather_data_validator->has_geolocation())
   {  UED::Geolocation_record *loc_rec = ued_file.get_geolocation_record();
      if (loc_rec) weather_data_validator->set_geolocation(loc_rec);
   }
   return weather_data_validator;
}
//______________________________________________________________________________
Station_database::~Station_database()
{  ued_file.finish();                                                            //090822
}
//______________________________________________________________________________
