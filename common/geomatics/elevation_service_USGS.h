#ifndef USGS_elevation_serviceH
#define USGS_elevation_serviceH
#include "common/geodesy/geocoordinate.h"
//#include "corn/const.h"
//---------------------------------------------------------------------------
/* This class uses the USGS elevation Web service to lookup elevation for a geocoordinate


http://gisdata.usgs.gov/xmlwebservices2/elevation_service.asmx?op=getElevation

http://ned.usgs.gov/epqs/

*/

#define USGS_Elevation_Web_service         0
#define USGS_Elevation_Point_Query_Service 1

namespace CS
{
//______________________________________________________________________________
class Elevation_service_USGS
{
 public:
   nat8 service;
   std::string host;
 public:
   //Elevation_service_USGS(const std::string &host);
   Elevation_service_USGS
      (nat8 service = USGS_Elevation_Web_service);
      //(const char *host="epqsl.er.usgs.gov" /*140805 "gisdata.usgs.gov"*/);
   bool lookup_elevation(modifiable_ Geocoordinate &geocoordinate);
      // Returns true if successfull
};
//_2014-06-26___________________________________________________________________
}


#endif

