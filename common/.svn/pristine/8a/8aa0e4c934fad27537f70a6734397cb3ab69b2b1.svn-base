#ifndef event_statusH
#define event_statusH
#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif

// These bit masks added for EVENT SCHEDULER VERSION
/* In V5 event status will be a 32bit mask
bit
// Bits 1-7
// The low byte represents activation and performance control
// Bit set does not necessarily represent an error codition
// unless error bit (7) is set.
// Bit zero is user controlled (I.e. enabled by management scheduling user option)
// In this case all other bits are 0

0 0=performed (remove from event queue) 1=Scheduled not yet completed
1 0=ready to start 1=started
2 0=continuing 1=stopped (could be restarted)
3 0=no postponement 1=postponed
4 0=in season     1=out of season (event is scheduled ok but it actually occured out of season and may also be postponed)
5 0=condition satisfied 1=condition not satisfied
6 (unused)
7 (unused)
// Bits 7-15 are indicators of partial completion due to resource limitation
// This case could either be an error (error bit would be set)
// (These are primarily used for CANMS)
// These bits are cleared at the start of the day.
// (I.e. the event operation may have been partially completed
//  and resecheduled for completion).
 8 1=time limited (the event could not be completed in the allocated time)
 9 1=capacity limited (the event requires more (facility) capacity, I.e. the facility filled up)
10 1=commodity limited     (I.e. ran out of food, manure, water etc.)
11 1=nutrient limited      (I.e. ran of nitrogen, phosphorus)
12 1=fuel limited          (I.e. ran out of biogas)
13 1=electricity limited   (rarely occurs, may also indicate power not applied/available)
// Note that the upper two bits to explaination severity level.
14 0=informational 1=warning
15 0=no error 1=error
*/
#define event_status_pending                1
#define event_status_started                2
#define event_status_stopped                4
#define event_status_postponed              8
#define event_status_out_of_season         16
#define event_condition_unsatisfied        32
//                                         64
//                                        128
#define event_status_time_limited         256
#define event_status_capacity_limited     512
#define event_status_limited_commodity   1024
#define event_status_limited_nutrient    2048
#define event_status_limited_fuel        4096
#define event_status_limited_electricity 8192
#define event_status_warning            16384
#define event_status_error              32768

#define Event_status_indicator nat16
#define ES_COMPLETE 0
#define ES_START        event_status_started
#define ES_DISABLE      event_status_stopped
#define ES_OUTOFSEASON  event_status_out_of_season
#define ES_POSTPONE     event_status_postponed
// ES_COMPLETE indicates there were no errors or special circumstances
#define ES_FAIL         event_status_error
#define ES_ERROR        event_status_error
/*160521 obsolete
#else
// becoming obsolete in V5 (only was V4). Should move to CropSyst_V4 namespace
//______________________________________________________________________________
enum Event_status
{
   ES_COMPLETE
,  ES_START
,  ES_STOP
,  ES_DISABLE
,  ES_POSTPONE
,  ES_OUTOFSEASON
// The following are error
,  ES_ERROR
,  ES_FAIL
,  ES_NOT_YET_IMPLEMENTED
// The following indicate the operation may have been partially completed but limited
// by some condition
,  ES_PARTIAL = 0x10
,  ES_CAPACITY_LIMITED
,  ES_TIME_LIMITED
,  ES_SPACE_LIMITED
,  ES_AVAILABILITY_LIMITED
};
// If these are changed, update schedule_viewer
DECLARE_LABELED_ENUM(Event_status_labeled,Event_status,event_status_label_table)

#define Event_status_indicator Event_status
//______________________________________________________________________________
#endif
*/
extern const char *event_status_label_table[];
//______________________________________________________________________________
#endif
// event_status.h
