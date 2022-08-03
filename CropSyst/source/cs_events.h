#ifndef cs_eventsH
#define cs_eventsH

#include "corn/container/bilist.h"
#include "options.h"
#include "common/simulation/event.h"
#include "cs_operation.h"

#define LABEL_growing_season_only   "growing_season_only"
//_Forward declarations_________________________________________________________
class MGS_filename;
class Operation_event_list;
namespace CropSyst                                                               //131101
{
   class Land_unit_simulation_VX; // foward decl.                                //141206
//_______________________________________________________Forward declarations__/
class Event
: public Common_event // Common_event
{
 public: // constructors
   inline Event()                                                                //131101
      : Common_event()
      {}
   inline Event                                                                  //131101
      ( const Synchronization &date_or_sync_
      , void /*Crop_base*/ *associated_crop_ = 0)
      : Common_event(date_or_sync_)
      {}
   inline Event                                                                  //031123
      ( const Event &to_be_copied)
      : Common_event(to_be_copied)
      {}
 public: //
   virtual void synchronize_to   //check used
      (const Synchronization  &from_sync                                         //030605
      , const CORN::Date_const &to_date);
   bool process_matching_date
      (Land_unit_simulation_VX &associated_sim
      ,const CORN::Date_const &process_date
      ,std::ostream &log_stream);
   inline virtual bool process
      (Land_unit_simulation_VX &associated_sim
      ,const CORN::Date_const &act_date)                          {return true;}
         // actually PURE decendents must define
   inline virtual void delay(CORN::Days days)                      modification_
      { date.inc_days((int16)days); }                                            //120314
      // This may be more usable in Common_event
};
//_2001-12-07____________________________________________class CropSyst_event__/
} // namespace CropSyst
#endif
//events.h

