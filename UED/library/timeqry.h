#ifndef timeqryH
#define timeqryH
#include "corn/chronometry/date_time_64.h"
#include "UED/library/UED_options.h"
#include "UED/library/UED_types.h"
#include "corn/measure/units.h"
#define UED_QUERY_ANY_TIME_STEP  0
using namespace CORN;
namespace UED {
//______________________________________________________________________________
class _UED_DLL Time_query
: public CORN::Date_time_clad_64                                                 //050714
{  // This class is used when doing record searches
 public:
   enum query_modes  // Rename this to Query_mode
   { at            // exactly on the target date/time
   , after         // any date after target date/time
   , before        // any date before target date/time
   , between       // any date between inclusive
   , all};
 protected:
   datetime64     low_date_time;
   datetime64     high_date_time;
   UED_units_code time_step; // may be 0 if we don't care                        //040125
 public:
   query_modes    query_mode;
 public: // Constructor for  Time_search and creating new records such as CropSyst soil profile vector
   inline Time_query
      (datetime64       target_date_time_
      ,datetime64       low_date_time_
      ,datetime64       high_date_
      ,UED_units_code   time_step_ // Normally UT_day for daily timestep         //040202
      ,query_modes      query_mode_ =  Time_query::between)
      : Date_time_clad_64(target_date_time_)                                     //050714
      , low_date_time   (low_date_time_)
      , high_date_time  (high_date_)
      , time_step       (time_step_) // Note, I may want to put this in the constructor, but it is not needed know //040125
      , query_mode      (query_mode_)
      {}
 public:
   virtual bool match(datetime64 match_date) ; // cannot be const
      // returns true if the specified date matches the query settings.
   virtual bool match_range
      (datetime64 match_low_date
      ,datetime64 match_high_date);
      // cannot be const
      // return true if both dates match the target
   inline datetime64 get_target_datetime64() const { return get_datetime64();}   //001126
   inline datetime64 get_low_datetime64()    const { return low_date_time   ;}   //001126
   // The following 2 lines are deprecated use get_xxx_datetime64
   inline datetime64 get_target_date_time()  const { return get_datetime64();}   //001126
   inline datetime64 get_low_date_time()     const { return low_date_time   ;}   //001126
   inline UED_units_code get_time_step()     const { return time_step; }         //040125
   bool offset_year(int16 by_years);                                             //141031

   inline virtual Time_query *clone()                                 rendition_ //160331
      {  return new Time_query
            (this->get_datetime64()
            ,this->low_date_time
            ,this->high_date_time
            ,this->time_step
            ,this->query_mode);
      }
};
//_1999-01-18___________________________________________________________________
class _UED_DLL Time_query_single_date
: public Time_query
{ // This class is used for queries at, after, or before
 public:
   Time_query_single_date
      (datetime64       target_date_time
      ,CORN::Units_code time_step = UT_day // Normally UT_day for daily timestep   //040202
      ,query_modes      query_mode =  Time_query::at);
   inline virtual Time_query_single_date *clone()                     rendition_ //160331
      {  return new Time_query_single_date
            (this->get_datetime64()
            ,this->time_step
            ,this->query_mode);
      }
};
//_2004-02-02___________________________________________Time_query_single_date_/
 // This class is used for queries by month at, after, or before
#ifdef REIMPLEMENTED
//170525 This was never used but reimplement for completion
class _UED_DLL Time_query_month
: public Time_query
{public:
   Time_query_month
      (Year        target_year
      ,Month       target_month
      ,query_modes query_mode =  Time_query::at);
};
#endif
//_2009-03-03_________________________________________________Time_query_month_/
class _UED_DLL Time_query_date_range
: public Time_query
{public:
   // Constructor for first_between mode between
   inline Time_query_date_range
      (datetime64       low_date_time_
      ,datetime64       high_date_
      ,UED_units_code   time_step_ = UT_day // Normally UT_day for daily timestep  //040202
      ,query_modes      query_mode_ =  Time_query::between)
      :Time_query(0 // no target date
                  ,low_date_time_
                  ,high_date_
                  ,time_step_
                  ,query_mode_)
      {}
};
//_2004-02-02___________________________________________________________________
class _UED_DLL Time_search
: public Time_query
{public:
   enum search_modes
   {  closest
   ,  earliest
   ,  latest };
protected:
   search_modes search_mode;
public:
   inline Time_search
      (datetime64       target_date_time_
      ,datetime64       low_date_time_
      ,datetime64       high_date_time_
      ,UED_units_code   time_step_ = UT_day  // Normally UT_day for daily timestep //040202
      ,query_modes      query_mode_  = Time_query::between
      ,search_modes     search_mode_ = Time_search::earliest)
      :Time_query(target_date_time_,low_date_time_
                 ,high_date_time_,time_step_,query_mode_)
      ,search_mode(search_mode_)
      {}
   virtual bool match(datetime64 match_date) ; // Cannot be const
   inline datetime64 get_latest_date()                                     const
      { return high_date_time; }
   inline datetime64 get_earliest_date()                                   const
      { return low_date_time; }
// NYI
//   inline const Date_time &get_closest_date();
//   { return high_date_time; };
};
//_1999-01-18______________________________________________________Time_search_/
} // namespace UED
//______________________________________________________________________________
#endif
//timeqry.h

