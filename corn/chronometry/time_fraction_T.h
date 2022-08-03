#ifndef time_fractionH
#define time_fractionH
#include "corn/chronometry/time_A.h"
#include "math.h"
//NYN #include "corn/math/compare.hpp"
namespace CORN
{
//______________________________________________________________________________
template <typename timeT> // a floating point
class Time_fraction_cowl
: public extends_ Time_abstract
{
 private:
   timeT &time_ref;
 public:
   Time_fraction_cowl(timeT &time_ref_)
      : Time_abstract()
      , time_ref(time_ref_)
      {}

   virtual datetime64   get_datetime64()                                   const
      { return (datetime64)(time_ref - (nat32)(time_ref)); }
   virtual float64      get_time64()                                       const
      { return (float64)(time_ref - (nat32)(time_ref)); }
   ///< Returns the time (fraction)

   //implemented by Time_abstract virtual Hour         get_hour()                                    const = 0;
   //implemented by Time_abstract    virtual Minute       get_minute()                                  const = 0;
   //implemented by Time_abstract    virtual Second       get_second()                                  const = 0;
   //implemented by Time_abstract    virtual Centisecond  get_centisecond()                             const = 0;
   //implemented by Time_abstract    virtual Millisecond  get_millisecond()                             const = 0;
   //implemented by Time_abstract    virtual Hours        get_hours_after_midnight()                    const = 0;
   //implemented by Time_abstract    virtual Minutes      get_minutes_after_midnight()                  const = 0;
   virtual Seconds      get_seconds_after_midnight()                      const
      {  float64 integral;
         float64 fractional = modf(time_ref,&integral);
         return fractional * 86400.0;
      }
   // essentially aliases
   //implemented by Time_abstract    inline virtual Hours get_hours()                                        const
      // { return this->get_hours_after_midnight(); }
   //implemented by Time_abstract inline virtual Minutes get_minutes()                                    const
      // { return get_minutes_after_midnight(); }
   //implemented by Time_abstract inline virtual Seconds get_seconds()                                    const
      //{ return get_seconds_after_midnight(); }
//implemented by Time_abstract    virtual time_HHMMSS  get_HHMMSS()                                  const = 0;
 public: // assignations
   virtual datetime64 set_time(const Time &time_)                assignation_
      {  float64 preserve_int = (int32) time_ref;
         float64 time_fract = time_.get_time64();
         time_ref = preserve_int + time_fract;
         return get_datetime64();
      }
   virtual datetime64 set_time64(datetime64 time64)              assignation_
      {  float64 preserve_int = (int32) time_ref;
         time_ref = preserve_int + time64;
         return get_datetime64();
      }
   virtual datetime64 set_datetime64(datetime64 time64)          assignation_
      {  time_ref = time64;
         return get_datetime64();
      }
   //implemented by Time_abstract    virtual datetime64 set_now() = 0;
   // Sets to and returns the computer's system date/time.
   virtual datetime64 set_S       (Seconds seconds)              assignation_
      {
         float64  new_fract = seconds/86400.0;
         float64  new_int = (int32) time_ref;
         time_ref = new_int + new_fract;
         return get_datetime64(); }
   //implemented by Time_abstract virtual datetime64 set_HHMMSS  (time_HHMMSS HHMMSS)           assignation_=0;
   //implemented by Time_abstract virtual datetime64 set_HMS
      //(Hour hour, Minute minute, Second second)                  assignation_=0;
   /* implemented by Time_abstract
   virtual datetime64 set_HMSm
      (Hour hour, Minute minute, Second second
      ,Millisecond millisecond)                                  assignation_//NYI
      {
         float64 seconds = second + (minute*60) + (hour*3600) +
            (millisecond/1000.0);
      }
   */
   //implemented by Time_abstract virtual datetime64 set_HMSc
      //(Hour hour, Minute minute, Second second
      //,Centisecond centisecond)                                  assignation_=0;
 public: // autoincrement
   virtual datetime64   inc_hours(Hours hours)                   assignation_
      {  datetime64 addend_fract = (float64)hours / 24.0;
         return inc_fraction(addend_fract);
      }
   virtual datetime64   inc_minutes(Minutes minutes)             assignation_
      {  datetime64 addend_fract = (float64)minutes / 1440.0;
         return inc_fraction(addend_fract);
      }
   virtual datetime64   inc_seconds(Seconds seconds)             assignation_
      {  datetime64 addend_fract = (float64)seconds / 86400.0;
         return inc_fraction(addend_fract);
      }
 public: // math
   virtual datetime64   inc_fraction(float64 day_fraction)       assignation_
      {
         float64 int_part_unused;
         float64 fraction_part = modf(time_ref,&int_part_unused);
         float64 new_time = fraction_part + day_fraction;
         if (new_time > 1)
         {
            date32 day_overflow = (date32)new_time;

//assert(false);

            inc_days(day_overflow);
            new_time -= day_overflow;
         }
         time_ref += (timeT)new_time;
         return time_ref;
      }
};
//_2017-08-24___________________________________________________________________
} // namespace CORN

#endif
