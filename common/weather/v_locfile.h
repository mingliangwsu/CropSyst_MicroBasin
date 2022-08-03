#ifndef v_locfileH
#define v_locfileH

#include <corn/validate/parameter_file.h>
#include <common/weather/loc_param.h>
//______________________________________________________________________________
class Valid_location_parameters
: public Location_parameters
{public:
   Validation_status weather_file_status;
   CORN::Filtered_file_name v_weather_file_htm;
   Validation_status status;
   Valid_location_parameters(uint8 version_major,uint8 version_release,uint8 version_minor);
   Validation_status validate(const LOC_filename &file_name, bool mean_peak_rainfall_required);
   // Returns true if the file is usable
};
//______________________________________________________________________________
#endif

