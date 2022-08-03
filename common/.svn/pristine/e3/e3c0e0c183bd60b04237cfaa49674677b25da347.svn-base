#ifndef storm_eventH
#define storm_eventH

#include "UED/library/datasetrec_creation.h"
#include "UED/library/datasetrec.h"
#include "corn/measure/units.h"

// There can be two forms of storm event records
// with date-time timestamp   In this case we store only the event time series starting with the time the event starts
// with date only timestamp   This is created by the common UED import utility,
//                            here we dont narrow down the time series for the time the event starts
#define Storm_event_UED_record_type_form1 UED::Record_type_distinguisher_interface::UED_data_set_date_time_var_units
#define Storm_event_UED_record_type_form2 UED::Record_type_distinguisher_interface::UED_data_set_date_var_units
//______________________________________________________________________________
class Storm_event_creation_layout
: public UED::Data_record_creation_layout
{public:
   Storm_event_creation_layout
      (Record_code         storm_event_UED_record_type
      ,Units_code          storage_units = UC_mm
      ,Units_code          interval_time_length = UT_30_minutes
      ,CORN::Quality_code  default_attribute_code = CORN::generated_quality);
};
//______________________________________________________________________________
class Storm_event_data_record
: public UED::Binary_data_record_clad
{public:
   Storm_event_data_record
      (Record_code         storm_event_UED_record_type
      ,datetime64          date_time
      ,Units_code          storage_units          = UC_mm              // This specifies the units the data is to be stored in (primarily in the database,but could also be in memory).
      ,Units_code          interval_time_length   = UT_30_minutes      // Interval time step
      ,CORN::Quality_code  default_attribute_code = CORN::generated_quality   );     // Default generated
      // Constructor for creation
   Storm_event_data_record(const UED::Binary_data_record_cowl *datarec);         //151122
      // Constructor to copy from a UED data set data record.
};
//______________________________________________________________________________
#endif

