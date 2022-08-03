#include "Station_database_point.h"
#include <UED/library/locrec.h>
//---------------------------------------------------------------------------
Station_database_point::Station_database_point
(const char *_station_ID, const char *_ued_file
,std::ios_base::openmode _openmode)                                              //130311
//130311 ,bool read_only)
: Station_database(_station_ID, _ued_file,_openmode)                             //130311
//130311,read_only)
{
      UED_geolocation_record *geolocation_record = ued_file.get_geolocation_record();
      geolocated=  (geolocation_record != 0);
};
//______________________________________________________________________________
float32 Station_database_point::get_elevation_m()                    performs_IO_
{
   const UED_geolocation_record *geolocation_record = ued_file.get_geolocation_record_immutable(); //100924 get_geolocation_record()
   return geolocation_record->get_elevation();
};
//______________________________________________________________________________