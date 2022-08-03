#ifndef ETref_injector_UEDH
#define ETref_injector_UEDH
#include "CS_suite/biometeorology/ETref_injector.h"
namespace CS
{
/*
//______________________________________________________________________________
interface_ Daily_weather_source
{

//   bool get_daily_weawther

};
//______________________________________________________________________________
*/
class ETref_Injector_UED
: public extends_ ETref_Injector
, public extends_ Weather_database_daily_UED
{
 protected:
   modifiable_ UED::Database_file_indexed    &source_weather;
   modifiable_ UED::Database_file_indexed    *target_biometeorology; //optional reference (not owned)
   // The Source and the target may be the same
 public: // structors
   ETref_Injector_UED
      (CS_UED::Database_file_indexed            *database_file    // rename to source_weather
      ,const Geocoordinate                      &geocoordinate_
      ,modifiable_ UED::Database_file_indexed   *target_biometeorology_ = 0
      ,CORN::date32                              start_date_ = 0
      ,CORN::date32                              stop_date_ = 0);
      // The geocoordinate doesn't necessarily have to be
      // the same as source or target UED geocoordinate
      // (I.e. one may want use a source site weather data to generate
      // ET for the target site).
   virtual bool process()                                         modification_;
 protected:
   virtual bool start_day()                                       modification_;
   virtual bool end_day()                                         modification_;
   virtual bool set_ETref_mm(float64 ETref_mm);
};
//_2016-07-27_______________________________________________UED_ETref_injector_/
} // namespace CS
#endif
