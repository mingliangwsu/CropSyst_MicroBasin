#ifndef all_stationsH
#define all_stationsH

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef enumlistH
#  include "corn/container/enumlist.h"
#endif
#ifndef geolocationH
#  include "common/geodesy/geolocation.h"
#endif
#ifndef Geolocation_itemH
#  include "geodesy/geolocation_item.h"
#endif
//______________________________________________________________________________
namespace CORN
{  class Dynamic_string_indexed_dBase_data_source;
   class SDF_List;
}
class Canadian_climatological_station_record;
enum Region_type {all_regions,country_region,state_province_region};
extern   Region_type reporting_agency_region_order[];
//______________________________________________________________________________
class All_known_weather_stations
{
public:  // WARNING  if changing this list don't forget to change UED import wizard page
   enum Reporting_agency
   {UNKNOWN_REPORTING_AGENCY
   ,NCDC_REPORTING_AGENCY
   ,PAWS_REPORTING_AGENCY   // obsolete
   ,AGRIMET_REPORTING_AGENCY
   ,CANADIAN_CLIMATOLOGICAL_REPORTING_AGENCY
   ,INM_ESPANA_REPORTING_AGENCY
   ,UCAR_REPORTING_AGENCY
   ,WMO_REPORTING_AGENCY
   ,AgWeatherNet_REPORTING_AGENCY
   ,WBAN_REPORTING_AGENCY  // "Weather Bureau Air Force Navy"
   ,reporting_agency_count
   };
private:
   Reporting_agency  reporting_agency;
   mutable CORN::Bidirectional_list /*180101 Association_list*/  known_NCDC_stations;  // This is a list of all known NCDC weather stations so we can create location records.
   mutable CORN::Bidirectional_list /*180101 Association_list*/  known_WBAN_stations;  // This is a list of all known NCDC weather stations so we can create location records.
   mutable CORN::Bidirectional_list /*180101 Association_list*/  known_UCAR_stations;  //
   mutable CORN::Enumeration_list  known_WMO_stations;
   mutable CORN::Dynamic_string_indexed_dBase_data_source  *Canadian_Climatological_stations_datasource;
public:
   All_known_weather_stations();
   virtual ~All_known_weather_stations();
   void set_reporting_agency(const char *format_name);
   void set_reporting_agency(Reporting_agency reporting_agency);

   // These used to be named get_XXX_geolocation but they are actually renderes
   Geolocation *render_PAWS_geolocation(uint16 station_ID_number);
   Geolocation *render_AgriMet_geolocation(const char *station_ID_code);
   Geolocation *render_NCDC_geolocation(const char *station_ID_code);
   Geolocation *render_UCAR_geolocation(const char *station_ID_code);
   Geolocation *render_Canadian_Climatological_geolocation(const char *station_ID_code);
   Geolocation *render_WMO_geolocation(uint32 station_ID_number);
   Geolocation *render_WBAN_geolocation(const char *WBAN_station_number );
   Geolocation *render_geolocation(const std::string &station_ID_code);

   Region_type list_regions(Reporting_agency agency, CORN::SDF_List &regions) const;
      // This clears the regions list and then adds a the regions identified
      // that will give a reasonable number of stations to select from
      // returns the type of regions lists.
      // This is used by the import utility to display stations in station selectors.
   int16 render_geolocations_for_region       // was get_geolocations_for_region
      (Reporting_agency agency
      , Region_type region_type
      , const char *region_identification  // (I.e. the country ,  provence or state name
      , CORN::Bidirectional_list /*180101 Association_list*/ &geolocations) performs_IO_;
      // This appends geolocation info (copies) to the geolocations lists
      // (the caller may delete these items because they are copies).
      // You can use list regions to identify the region type suitable for the selection.
   inline Region_type get_reporting_agency_region_order(Reporting_agency agency) const
      { return  reporting_agency_region_order[agency]; }
public:
   bool load_NCDC_WBAN_stations(CORN::Bidirectional_list /*180101 Association_list*/ &locations,bool WBAN_mode);
   bool load_WMO_stations(CORN::Enumeration_list &locations);
private:
   Geolocation *render_NCDC_WBAN_geolocation
      (const char             *station_number
      ,CORN::Bidirectional_list /*180101 Association_list*/ &known_stations);
   bool provide_Canadian_Climatological_datasource();
   void convert_Canadian_climatological_station_record_to_geolocation
      (const Canadian_climatological_station_record &CC_loc
      ,Geolocation &geolocation);
};
//______________________________________________________________________________
#endif

