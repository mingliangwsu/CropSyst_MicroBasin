#ifndef CS_simulationH
#define CS_simulationH

#include "CS_suite/simulation/CS_simulation_engine.h"
#include "CS_suite/simulation/CS_land_unit_meteorological.h"

// This class performs triggered synchronizations for all management Land block fragments.
// In CropSyst, there is only one land block fragments
// In CANMS there can be multiple LBFs
//
// Weather databases:
//    Multiple LBFS may share a single weather database (and location)
//       these will be stored here and assigned by the calling application.

#define MAX_LBFS  50
// Forward declarations:

class Weather;
class Location_parameters;
class Geocoordinate;
namespace CS { namespace meteorology { class Storms;}}                               //140217
#include "common/weather/snow_pack.h"

class Weather_database;
namespace CropSyst
{
   class Land_unit_simulation_VX;                                                //141206
}
namespace CropSyst_V4 {                                                          //151003
//______________________________________________________________________________
class Cropping_system_simulation
: public CS::Simulation_engine                                                   //151203
{
 public:
   class Location_weather : public Item
   {
    protected:
      friend class Cropping_system_simulation;
         // This will be provided by the CropSyst_scenario
         // however older version of CropSyst did not specify the site location
         // in the scenario, it was taken from the weather database
         // so I currently preserve that functionality until version 5. RLN
         // At this time I only need geocoordinate, but geolocation
         // could be used instead.
      #if (CROPSYST_VERSION == 4)
      std::string                    location_filename;
         // currently always a file name (for LADSS may be the weather filename)  may either 040909
      Location_parameters           *location;           // May be 0 in the case of UED selected for scenario
      #endif
      Weather_database              *weather_DB;                                 //050307
      Weather                       *weather_extension;                          //060922
         // Now owned by meteorology
      CS::meteorology::Storms       *storms;                                     //140217
      CS::Land_unit_meteorological  *meteorology;                                //151203
    public:
      Location_weather
         (
          #if (CS_VERSION == 4)
          const char                   *location_filename_
         ,  Location_parameters        *location_,
          #endif
          Weather_database             *weather_DB_                              //050307
         ,Weather                      *weather_extension_                       //060922
         ,CS::meteorology::Storms      *storms_                                  //140217
         ,CS::Land_unit_meteorological *meteorology_                             //151203
         );
      virtual ~Location_weather();
      #if (CS_VERSION == 4)
      virtual bool is_key_string(const std::string &key)           affirmation_; //180820
/*180820  was probably only used for find_cstr now using is_key  
      virtual const char *get_key()                                       const; //130406
*/      
      #else
      virtual bool is_key_wstring(const std::wstring &key)         affirmation_; //180820
/*180820  was probably only used for find_cstr now using is_key  
      virtual const wchar_t  *get_key_wide()                              const; //130406
*/
      #endif
   };
   //_______________________________________________________________
   Unidirectional_list  &LBF_sims;                                               //151203
   Bidirectional_list locations_weather;
   std::wstring scenario_extension;                                              //150121

 public:
   Cropping_system_simulation
      (modifiable_  CS::Simulation_control &simulation_control_                  //151128
      ,Command_options_data_source         &command_line_options_);              //160829
   inline virtual ~Cropping_system_simulation()                               {} //151204
   virtual nat16 process_triggered_syncronizations();
   virtual bool add_land_block_fragment(CropSyst::Land_unit_simulation_VX *LBF_sim_i); //141206
   #ifndef USE_CS_LAND_UNIT
   virtual bool setup_location                                                   //030911
      (CropSyst::Land_unit_simulation_VX  *to_lbf                                //141206
      ,Geocoordinate                &geocoordinate_                              //151208
      #if (CS_VERSION==4)
      ,const char                      *location_filename
      #else
      ,CORN::OS::File_name &weather_database_filename
      #endif
      ,Location_parameters             *location_to_use  // specified for LADDS otherwise 0
      ,bool                             extend_available_weather                 //150218
      ,Snow_pack_model                  snowpack_model
      ,float32                          soil_steepness
      ,bool                             hourly);                                 //041111
      ///< Lookup to_lbf in LBF_sims if not found return false
      /// lookup  i_location_filename_or_ID in location_weather;
      /// If exists then assign_environment() must be called
      /// after add_land_block_fragment() and before process_day()
      /// If location is specified, this pointer is relinquished by Location weather
      /// If the location already loaded then location is deleted.
      /// If location_to_use is not specified,
      /// then location is created and loaded.
      ///< \return true if new location weather added
      ///  Otherwise return false indicating the location does not require additional setup
   #endif
 public: // simulation engine implementations

   virtual bool initialize()                                     initialization_;//151203
   virtual bool start()                                            modification_;//130620
   virtual bool start_day()                                        modification_;//130620_041217
   virtual const std::string &get_model_name()                             const;//120925
   inline virtual const std::wstring &get_scenario_file_name_extension()   const //160119
      { return scenario_extension; }
};
//______________________________________________________________________________
} // namespace CropSyst_V4 //CS

#endif

