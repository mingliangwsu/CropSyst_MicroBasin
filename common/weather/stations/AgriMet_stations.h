#ifndef AgriMet_stationsH
#define AgriMet_stationsH

#include "common/geodesy/geolocation.h"
//______________________________________________________________________________
struct AgriMet_Geolocation
{
   bool      viable;
   char     *station_ID;
   char     *station_name;
   char     *state_FIPS_code;

   float32  elevation_ft;   // I think feet
   float32  latitude_deg; // make sure to set negative
   float32  latitude_min;
   float32  latitude_sec;
   float32  longitude_deg;
   float32  longitude_min;
   float32  longitude_sec;
   char     *install_date;
};
//______________________________________________________________________________
extern Geolocation *render_AgriMet_geolocation(const char *station_ID);

#endif
