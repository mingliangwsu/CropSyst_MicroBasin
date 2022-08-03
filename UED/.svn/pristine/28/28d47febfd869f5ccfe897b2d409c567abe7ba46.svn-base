//---------------------------------------------------------------------------
#ifndef Station_database_pointH
#define Station_database_pointH
#include "ued/convert/station_database.h"
//---------------------------------------------------------------------------
class Station_database_point
: public Station_database
{
public:
   bool     geolocated;
   // Currently presuming all points will be relative to the same zone
   float32 distance_km;
public:
   Station_database_point(const char *i_station_ID, const char *i_ued_file
      ,std::ios_base::openmode _openmode /* = (std::ios_base::in | std::ios_base::out)*/); // 130311
      //130311       ,bool read_only);
   float32 get_elevation_m()                                        performs_IO_;
   inline void set_distance(float32 _distance_km) { distance_km = _distance_km; };
   inline virtual int compare(const Item &other_item)                      const
   {  const Station_database_point &other = dynamic_cast<const Station_database_point &>(other_item);
      return (distance_km > other.distance_km)
      ? 1
      : (distance_km < other.distance_km)
         ? -1 : 0 ;
   };
};
//______________________________________________________________________________


#endif
