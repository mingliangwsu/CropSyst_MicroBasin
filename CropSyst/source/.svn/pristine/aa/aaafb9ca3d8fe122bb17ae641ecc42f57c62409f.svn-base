#ifndef event_scheduler_cropH
#define event_scheduler_cropH

#include "CS_suite/simulation/CS_event_scheduler.h"
#ifdef YAML_PARAM_VERSION
#include "crop/crop_param_YAML.h"
#else
#include "crop/crop_param.h"
#endif

namespace CropSyst {
class Crop_complete;

//______________________________________________________________________________
class Event_scheduler_crop
: public extends_ CS::Event_scheduler_common
{
 public:
   inline Event_scheduler_crop
      (const CORN::Date_const &today_
      ,CORN::Unidirectional_list &performable_operations_)
      : CS::Event_scheduler_common(today_,performable_operations_)
      {}
   inline virtual ~Event_scheduler_crop()                                     {}
   nat16 synchronize_thermal_time(float32 thermal_time_today)     modification_;
   virtual bool end_season()                                      modification_;
};
//_2015-09-30___________________________________________________________________
class Event_scheduler_crop_complete
: public extends_ Event_scheduler_crop
{
   modifiable_ Crop_complete &crop;
 public:
   inline Event_scheduler_crop_complete
      (modifiable_ Crop_complete &crop_
      ,const CORN::Date_const &today_
      ,CORN::Unidirectional_list &performable_operations_)
      : Event_scheduler_crop(today_,performable_operations_)
      , crop(crop_)
      {}
   #ifdef YAML_PARAM_VERSION
   // parameter adjustment will be handled by the interpolator
   #else
   virtual Event_status_indicator process_model_specific_event(const Simple_event *event);
   Event_status_indicator perform_crop_adjustment
      (const CropSyst::Crop_parameters::Adjustment &adjustment_event);
   #endif
};
//_2015-11-27__________________________________________________________________/
} // namespace CropSyst
#endif

