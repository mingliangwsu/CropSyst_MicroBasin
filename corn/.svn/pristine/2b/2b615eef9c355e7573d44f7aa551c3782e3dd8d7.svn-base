#ifndef date_time_TH
#define date_time_TH
#include "corn/chronometry/date_time_A.h"
#include "corn/chronometry/time_fraction_T.h"
#include "corn/chronometry/date_T.h"
#include "corn/math/compare.hpp"
namespace CORN
{
//______________________________________________________________________________
template <typename datetimeT> // a floating point
class Date_time_cowl
: public extends_ Date_time_abstract
{
 private:
   datetimeT &datetime_ref;
   Time_fraction_cowl<datetimeT> time_fraction;
   Date_cowl         <datetimeT> date_number;
 public:
   inline Date_time_cowl(datetimeT &datetime_ref_)
      : Date_time_abstract()
      , datetime_ref(datetime_ref_)
      , time_fraction(datetime_ref_)
      , date_number(datetime_ref_)
      {}
 public: // accessors
   virtual modifiable_ Time     &mod_time() modification_{return time_fraction;}
   virtual const       Time     &ref_time()       const { return time_fraction;}
   virtual modifiable_ Date     &mod_date()   modification_{return date_number;}
   virtual const       Date_const &ref_date()       const { return date_number;}

   virtual datetime64 get_datetime64()             const { return datetime_ref;}
   virtual date32     get_date32()         const { return (date32)datetime_ref;}
   virtual float64    get_time64()        const { return (float64)datetime_ref;}

 public: // assignations (date implementations)
   virtual datetime64 set_date32(date32 value)                      assignation_
      {  datetime_ref = (datetimeT) value;
         return (datetime64)datetime_ref;
      }
   virtual datetime64 set_datetime64(datetime64 value)              assignation_
      { return datetime_ref = (datetimeT) value; }
   inline virtual datetime64 set(const Temporal &other)             assignation_
      { return datetime_ref = other.get_datetime64(); }
 public: // assignations (date-time implementations)
   virtual datetime64 set_date(const Date_interface &new_date)      assignation_
      { return datetime_ref = new_date.get_datetime64(); } // add option to set the entire value?
 public: // modifiers
 public: // autoincrement
 public: // math
 public: // affirmations
 public: // methods for arbitrary time
 public: // conversions
 protected: // utility
   virtual void split(datetime64 &date_part, datetime64 &time_fract)       const
   {  nat32 value_int32 = (nat32)datetime_ref;
      date_part = value_int32;
      time_fract = datetime_ref - date_part;
   }
   //_2017-04-30_2004-09-09_2003-07-15___________________________________split_/
   virtual datetime64 join(datetime64 date_part, datetime64 time_fract)
   {  datetime_ref = date_part + time_fract;
      return (datetime64)datetime_ref;
   }
   //_2017-04-30_2003-07-15__________________________________________________join_/
   virtual datetime64 inc_time_fract(datetime64 time_fract)        modification_
   {  datetime64 date;
      datetime64 time;
      split(date,time);
      time += time_fract;
      if (CORN::is_approximately<double>(time,1)) time = 1.0;                       //170621LML
      datetime64 days;
      datetime64 new_time;
      Date_time_cowl<datetimeT>(time).split(days,new_time);
      Date_clad<date32> new_date(date);
      new_date.inc_days((int32)days);
      return join(new_date.get_datetime64(),new_time);
   }
   //_2017-04-30_2004-09-09_040909_2003-07-14______________________inc_time_fract_/

   virtual datetime64 set_now() { return Date_time_abstract::set_now(); }        //170815

public: // the following are temporary as I transition to new Date_time
/*delete this

*/
   virtual datetime64 set_DT
      (const Date &date,const Time &time)                           assignation_
      {
         datetime_ref = date.get_date32() + time.get_time64();
         return get_datetime64();
      }

   //   virtual datetime64 set_date(const Date_interface &date)       assignation_;
   //_2017-04-30_2010-01-16_2003-07-17___________________________________set_date_/
   //   virtual datetime64 set_datetime64(datetime64 value)           assignation_;
   //   virtual datetime64 set_date32(datetime64 value)               assignation_;
};
//_2017-04-26________________________________________________Date_time_64_cowl_/
template <typename datetimeT>
class Date_time_clad
: public extends_ Date_time_cowl<datetimeT>
{protected:
   datetimeT datetime;  // A float
 private:// not sure why gcc compiler complains if I don't define set_now and join
   virtual datetime64 set_now() { return Date_time_abstract::set_now(); }        //170815
   virtual datetime64 join(datetime64 date_part, datetime64 time_fract)
   {  return datetime = date_part + time_fract;
      return (datetime64)datetime;
   }
 public:
   Date_time_clad()
   : Date_time_cowl<datetimeT>(datetime)
   , datetime(0)
   {  set_now(); // Current computer's date and time
   }
   //_2017-04-30__________________________________________________constructor__/
   Date_time_clad(datetime64 value)
   : Date_time_cowl<datetimeT>(datetime)
   , datetime(value)
   {}
   //_2017-05-23__________________________________________________constructor__/
   Date_time_clad(date32 date_, nat32 time_)
   : Date_time_cowl<datetimeT>(datetime)
   , datetime(0)
   {  join(date_,(float32) time_ / Seconds_per_day);
   }
   //_2017-05-23__________________________________________________constructor__/
 public: // assignations
   inline virtual datetime64 set(const Temporal &other)             assignation_
      { return datetime = other.get_datetime64(); }
 private:
   Date_time_clad *check_abstract() { return new Date_time_clad<datetime64>(); }
};
//_2017-04-26________________________________________________Date_time_64_clad_/
} // namespace CORN
// Roger Nelson rnelson@wsu.edu

#endif
