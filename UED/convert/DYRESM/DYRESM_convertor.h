#ifndef DYRESM_convertor_H
#define DYRESM_convertor_H

#include <UED/convert/convertor.h>
class DYRESM_record; // forward decl

class DYRESM_convertor
: public UED_convertor
{
   bool  metric;  // True if metric units;
public:
   DYRESM_convertor(int argc, const char *argv[]);
   virtual uint32 perform_import()                                               { return 0; /*NYI */};
   virtual uint32 perform_export() ;
private: // Anicillary functions
   virtual uint16 get_version()                                            const { return 0x0100; };
   virtual const char *get_application_name()                              const { return "DYRESM export utility (Roger Nelson rnelson@wsu.edu)"; };
private:
   float32 estimate_vapor_pressure_hPa
      (float32 dry_bulb_temperature, float32 rel_humid)                    const;
   float32 estimate_vapor_pressure_from_min_max_rel_humid_hPa(const DYRESM_record &record)            const;
//private:
//   void import_record(NCDC_NOAA_global_surface_summary_of_the_day_format &element_record,  Directory_name &ued_file_path);
};

#endif

