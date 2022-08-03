#include "CS_suite/biometeorology/ETref_injector.h"

namespace CS
{
//______________________________________________________________________________
ETref_Injector::ETref_Injector
(bool                    hourly_aggregation_
,const Geocoordinate    &geocoordinate_
,CORN::date32            start_date_
,CORN::date32            stop_date_)
: today(start_date_)                                                             //170202
,start_date (start_date_)
,stop_date  (stop_date_)
,sun
   (today
   ,geocoordinate_)
,sun_days
   (geocoordinate_.get_longitude_radians()
   ,geocoordinate_.get_longitude_radians())
      // The standard meridian it is not critical for simulation model
,sun_hours
   (sun_days
   ,geocoordinate_.get_longitude_dec_deg())
,ET_solar_irradiance(
/*
   (hourly_aggregation_
   ?
*/
   new CS::Solar_irradiance_extraterrestrial_hourly
         (geocoordinate_,sun_days,sun_hours,today)
/*
   : new CS::Solar_irradiance_extraterrestrial_daily
         (geocoordinate_,today)
*/
)
,provider            (today,geocoordinate_,*ET_solar_irradiance,0)
,ET_ref_calc(geocoordinate_.get_elevation(),sun.ref_day_length_hours_today(),provider)
{

/*
   sun = new Sun
   (today
   ,geocoordinate_);
   sun_days = new Sun_days
   (geocoordinate_.get_longitude_radians()
   ,geocoordinate_.get_longitude_radians());
      // The standard meridian it is not critical for simulation model
   sun_hours = new Sun_hours
   (*sun_days
   ,geocoordinate_.get_longitude_dec_deg());

   ET_solar_irradiance =
   (hourly_aggregation_
   ?
   new CS::Solar_irradiance_extraterrestrial_hourly
         (geocoordinate_,*sun_days,*sun_hours,today);
   : new CS::Solar_irradiance_extraterrestrial_daily
         (geocoordinate_,today));

   ET_ref_calc = new ET_Reference_calculator(geocoordinate_.get_elevation(),sun->ref_day_length_hours_today(),provider);
*/
}
//______________________________________________________________________________
ETref_Injector::~ETref_Injector()
{  delete ET_solar_irradiance;
}
//______________________________________________________________________________
bool ETref_Injector::start_day()                                   modification_
{  bool started = true;
   started &= sun.update();
   provider.update();
   return started;
}
//______________________________________________________________________________
bool ETref_Injector::process()                                     modification_
{  bool processed = true;
   // source and target files will have been open/provided by this points
   ET_solar_irradiance->start();
   for (today.set(start_date)
       ;today <= stop_date
       ;today.inc_day())
   {
      std::clog << today.as_string() << '\r';
      processed &= start_day();
      // update();  <-- if derived from ET_Reference_FAO
      ET_ref_calc.update();
      float32 ETref_mm = ET_ref_calc.get_mm();
        //  = get_mm(enabled_model); <-- if derived from ET_Reference_FAO
      set_ETref_mm(ETref_mm);
      end_day();
   }
   return processed;
}
//______________________________________________________________________________
//______________________________________________________________________________
} // namespace CS

