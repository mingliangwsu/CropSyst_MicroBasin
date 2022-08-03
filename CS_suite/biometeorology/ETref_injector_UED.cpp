#include "ETref_injector_UED.h"
#include "common/weather/database/common_weather_creators.h"
#include "UED/library/timeqry.h"
#include "CS_suite/observation/CS_emanator.h"
namespace CS
{
//______________________________________________________________________________
ETref_Injector_UED::ETref_Injector_UED
(CS_UED::Database_file_indexed            *database_file_
,const Geocoordinate                      &geocoordinate_
,modifiable_ UED::Database_file_indexed   *target_biometeorology_
,CORN::date32                              start_date_
,CORN::date32                              stop_date_)
: ETref_Injector(true,geocoordinate_,start_date_,stop_date_)                     //160926
, Weather_database_daily_UED
   (database_file_,ETref_Injector::today.ref_date32(),false,0,0,0,0)             //170717_170313
,source_weather            (*database_file)
,target_biometeorology     (target_biometeorology_)
{
   know_weather_provider(&(ref_provider()));
   if (!target_biometeorology)
      target_biometeorology = &source_weather;
   if (start_date_ == 0)
       start_date.set_datetime64(database_file_->get_earliest_date_time());
   if (stop_date_ == 0)
       stop_date.set_datetime64(database_file_->get_latest_date_time());
}
//______________________________________________________________________________
bool ETref_Injector_UED::start_day()                               modification_
{  bool started = true;
   started &= Weather_database_daily_UED::start_day();
   started &= ETref_Injector::start_day();
   return started;
}
//______________________________________________________________________________
bool ETref_Injector_UED::end_day()                                 modification_
{
   return Weather_database_daily_UED::end_day();
}
//______________________________________________________________________________
Common_weather_creators weather_creators(CORN::calculated_quality);
bool ETref_Injector_UED::process()                                 modification_
{  bool processed = true;
   // source and target files will have been open/provided by this points

   CS::instantiate_emanators(ETref_Injector::today); //180606

   ET_solar_irradiance->start();
   for (ETref_Injector::today.set(start_date)
       ;ETref_Injector::today <= stop_date
       ;ETref_Injector::today.inc_day())
   {
      processed &=  start_day();
      if (!processed && (ETref_Injector::today != stop_date))
      {
         std::clog << std::endl << "warn: "
            << "There appears to be data missing or invalid on date "
            << ETref_Injector::today.as_string()
            << " not necessarily an error "
            << "(make sure this date is available from "
            << "the netCDF data source - NKN REACCH service), "
            << "otherwise something is probably wrong. contact rnelson@wsu.edu"
            << std::endl;
         processed=true; // debug accepting all days need to debug if december 31 is not downloading or not getting into UED file.
      }
      // update();  <-- if derived from ET_Reference_FAO

//if (ETref_Injector::today.get_date32() == 2014356)
//std::clog << "2014356 reached" << std::endl;

      ET_ref_calc.update();
      float32 ETref_mm = ET_ref_calc.get_mm();
        //  = get_mm(enabled_model); <-- if derived from ET_Reference_FAO
      set_ETref_mm(ETref_mm);
      end_day();
   }
   assert(processed);
   return processed;
}
//______________________________________________________________________________
bool ETref_Injector_UED::set_ETref_mm(float64 ETref_mm)
{
   CORN::Units_code ET_ref_units = UC_mm;
   CORN::Quality_clad ET_ref_quality(CORN::calculated_quality);
   UED::Time_query_single_date time_query(ETref_Injector::today.get_datetime64());

   bool record_created = false;
   target_biometeorology->set_value
         (ETref_mm
         ,time_query
         ,ET_ref_units
         ,ET_ref_quality
         ,weather_creators.pot_evapotranspiration_FAO_Penman_Monteith_reference_creation
         ,record_created);
   return true;
};
//_2016-09-26___________________________________________________________________
} // namespace CS

