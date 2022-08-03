
// rename to covertor_arguments.*

#ifndef convert_responseH
#define convert_responseH
#include "corn/application/arguments.h"
#include "common/geodesy/geolocation.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "UED/library/UED_fname.h"
namespace UED {                                                                  //171120
//______________________________________________________________________________
enum DYRESM_vapor_pressure_calculation
   { VP_based_on_mean_relative_humidity_and_air_temperature
   , VP_based_on_min_and_max_relative_humidity
   };
//______________________________________________________________________________
enum DYRESM_net_radiation_option
   { cloud_cover_fraction_option
   , longwave_net_radiation_option
   , incident_longwave_net_radiation_option };
//______________________________________________________________________________
class Convertor_arguments  // was Convert_response_data_record                                                      //171120
: public CORN::Arguments                                                         //170328
{
 public:  // The following responses are sent to the convertor
   std::string       operation;           // "import" or "export"
   CORN::OS::File_name_concrete  UED_filename;        // Used mainly (only?) for export (on import there could be multiple stations (each generating their own UED file)
   CORN::OS::File_name_concrete  target_filename; // Target filename (text file)
   CORN::OS::File_name_concrete  format_filename; // I.e. TDF file
   std::string       station_IDs_filter;  // Now there can be multiple IDs  The station ID are space delimited.  Empty string means import all.
   bool              use_station_name;    // if true the station name will be used instead to create the UED filename of the station ID            //060117
   std::string       format;              // Added for all in one                                                                                  //060616
   std::string       subformat;           // This is any special subformat offered by this convertor
      // Subformat for SWAT corresponds to the version year 1998 1999 2000 2005
   std::string       units_system;        // "intrinsic" or "metric" or "US"  (for US customary / English / Imperial)                              //060613
   int16             year_earliest;       // This allows the user to limit the range                                                               //060119
   int16             year_latest;         // of years to import/export                                                                             //060119
   float64           date_time_earliest;  // This allows the user to limit the range of dates (and or date.times)                                  //070621
   float64           date_time_latest;    // to import/export                                                                                      //070621
   sint16            offset_years;                                                                                                                 //100303
   std::string       prefix;              // currently used only for CropSyst I/O                                                                  //060328
// Station ID code  (used for import)
// if individual records dont specify the station_ID,
// then this is used, the UED filename will be generated from this)
// Note that some weather data only use the station name as the ID
// In this case, make sure to quote the station name on the command line.
   bool              calculate_daily;                                                                                                              //050419
         //       If the format contains time steps shorter than a day,                                                                            //050419
         //       calculate a daily value for the database.                                                                                        //050419
   // Export options                                                                                                                               //080108
   std::string   UED_filenames;                                                                                                                   //080108
      // Some file formats may contain multiple locations,                                                                                            //080108
      // In this case we list the UED files in SDF format.                                                                                            //080108
      // Now mutiple UED files can be used to create on ouput (report)           //171125
   bool allow_16bit_floats_in_UED;                                               //150307
      // In 2014 added the option for UED file to store real number
      // as 16bit floating point if values can be stored with sufficient precision.
 public:  // The following are options for specific models
   int16 vapor_pressure_calculation;  // actually DYRESM_vapor_pressure_calculation                                                                   //070212
   int16 net_radiation_option;         // actually DYRESM_net_radiation_option                                                                        //070212
 public:  // geolocation may be provided by caller but usually it is taken from the database                                                           //080326
   bool        geolocation_is_provided_by_caller;                                                                                                     //080326
   Geolocation geolocation;  // geolocation is currently for VIC                                                                                      //080326
 public:  // Subdaily interval (export) options for format that support it.
   nat32 precipitation_time_step;  // in seconds  (Currently only available in SWAT which allows 1,2,3,4,5,6,10,12,15,20 and 30 minute intervals)
                                    // other models may have a fixed timestep defined by the format, in those cases, this field is ignored
                                    // 0 disabled
 public:  // The following responses returned by the convertor
   bool location_info_imported; // Set to true if the import utility generated a location record in the UED file.
 public:
   Convertor_arguments();
   inline virtual ~Convertor_arguments()                                      {}
   virtual bool expect_structure(bool for_write);
   virtual bool get_end();                                                       //170616
 public:
   bool is_import_mode()            affirmation_ { return operation=="import"; } //171120
 public: // CORN::Arguments reimplementation
   bool recognize
      (const std::string &paramstring)                            modification_; //171120
   virtual bool submit_DEN                                                       //180213
      (CORN::OS::Directory_entry_name *param_DEN)                   submission_;
};
//_2005-04-18___________________________________________________________________
} // namespace UED                                                               //171120
#endif

