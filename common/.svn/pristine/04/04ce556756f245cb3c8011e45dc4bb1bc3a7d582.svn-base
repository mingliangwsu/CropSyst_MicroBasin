#include "elevation_service_Google.h"
#include "corn/Internet/HTTP/request.hpp"
namespace CS
{
//______________________________________________________________________________
Elevation_service_Google::Elevation_service_Google()
:host("maps.googleapis.com")
{}
//______________________________________________________________________________
bool Elevation_service_Google::lookup_elevation(modifiable_ Geocoordinate &geocoordinate)
{  bool succeeded = false;
   std::string get_request;
      get_request.append("/maps/api/elevation/json?");
      get_request.append("locations=");
      get_request.append(CORN::float64_to_cstr(geocoordinate.get_latitude_dec_deg(),10));
      get_request.append(",");
      get_request.append(CORN::float64_to_cstr(geocoordinate.get_longitude_dec_deg(),10));

      /* response:
{
   "results" : [
      {
         "elevation" : 1608.637939453125,
         "location" : {
            "lat" : 39.73915360,
            "lng" : -104.98470340
         },
         "resolution" : 4.771975994110107
      }
   ],
   "status" : "OK"
}
      */
   std::string response_JSON;
   succeeded = CORN::Internet::
      REQUEST_TO_STRING
      //170831 request
      (GET,host.c_str(),get_request.c_str(),NULL,NULL,response_JSON);
/*
extern bool WinINet_request_to_cstr
   (int Method
   , const char * Host     //LPCSTR
   , const char * url      //LPCSTR
   , const char * header   //LPCSTR
   ,       char * data     //LPSTR
   ,char *result);
*/
   float32 elevation = 0; //meter
   if (succeeded)
   {  // parse response
      Elevation_response response;
      succeeded = response.read_string(response_JSON);
      if (succeeded)
      {  Elevation_response::Results::Result *result =
            response.results
            ? dynamic_cast<Elevation_response::Results::Result *>(response.results->items.pop_first())
            : 0;
         if (result)
            geocoordinate.set_elevation_meter(result->elevation);
      }
   }
   if (!succeeded)
   {  elevation = 400.0;
      std::cerr
         << "Unable to connect to Google elevation site:" << host << std::endl
         << "Using default mean elevation of Columbia basin and Palouse: 400 meter" <<std::endl;
      geocoordinate.set_elevation_meter(elevation);
   }
   return succeeded;
};
//______________________________________________________________________________
Elevation_response::Elevation_response()
: CORN::JSON::Object("response")
//, results(0)
//, status("status")
{  results = 0;
}
//______________________________________________________________________________
Elevation_response::Results::Results()
: CORN::JSON::Object::Array("results")
{}
//______________________________________________________________________________
Elevation_response::Results::Result::Result()
: CORN::JSON::Object("result")
, Geocoordinate()
, location(0)
{}
//______________________________________________________________________________
bool Elevation_response::Results::Result::expect_structure(bool for_write) //expect_structure(bool for_write)
{  //Geocoordinate::setup_structure(*this,false);
   expect_float32("elevation",elevation);                                        //150903 was float32
   return CORN::JSON::Object::expect_structure(for_write);
}
//______________________________________________________________________________
CORN::JSON::Structure *Elevation_response::Results::Result::provide_substructure
(const std::string &key)                                              provision_
{  CORN::JSON::Structure *substructure = 0;
   if (key == "location")
      substructure = location = new Location((Geocoordinate &)(*this));
   return substructure;
}
//______________________________________________________________________________
bool Elevation_response::Results::Result::Location:: expect_structure(bool for_write) // expect_structure(bool for_write)
{  if (!for_write)
   {  expect_float32("lat",geocoordinate.latitude_dec_deg);                      //150903 was float32
      expect_float32("lng",geocoordinate.longitude_dec_deg);                     //150903 was float32
      // elevation labelis the same as Geocoordinate
   }
   return true;                                                                  //170831
}
//______________________________________________________________________________
Elevation_response::Results::Result::Location::Location(Geocoordinate &_geocoordinate)
: CORN::JSON::Object("location")
, geocoordinate(_geocoordinate)
{}
//______________________________________________________________________________
CORN::JSON::Structure *Elevation_response::provide_substructure(const std::string &key)  provision_
{  CORN::JSON::Structure *substr = 0;
   substr =  (key=="results")
      ? results = new Results
      /* NYN
      : (key == "status")
        ? NYI
      */
      : provide_substructure("key");
   return substr;
}
//______________________________________________________________________________
Elevation_response::Results::~Results()
{ // just for debugging
   std::cout << "Reached" << std::endl;
}
//______________________________________________________________________________
} // CS

