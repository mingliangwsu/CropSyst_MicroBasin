#ifndef PAWS_stationsH
#define PAWS_stationsH

#include "common/geodesy/geolocation.h"
//______________________________________________________________________________
struct PAWS_Geolocation
{
   bool     viable;
   nat16   unit_ID;
   char     *station_name;
   float32  latitude_dec_deg;
   float32  longitude_dec_deg;
   float32  elevation_m;
   char     *start_date;
   char     *location;
   char     *state;
};
//______________________________________________________________________________
extern Geolocation *render_PAWS_geolocation(uint16 unit_ID);

#endif
