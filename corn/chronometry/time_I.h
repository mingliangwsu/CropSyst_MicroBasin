#ifndef time_IH
#define time_IH
#include "corn/chronometry/temporal.h"
namespace CORN
{
   typedef float64 datetime64;
   class Time_format;
//______________________________________________________________________________
interface_ Time
: public extends_interface_ Temporal
{
 public: // structors
   inline virtual ~Time() {}                                                     //170825
 public: // accessors
   virtual datetime64   get_datetime64()                              const = 0;
   virtual float64      get_time64()                                  const = 0;
   ///< Returns the time (fraction)

   virtual Hour         get_hour()                                    const = 0;
   virtual Minute       get_minute()                                  const = 0;
   virtual Second       get_second()                                  const = 0;
   virtual Centisecond  get_centisecond()                             const = 0;
   virtual Millisecond  get_millisecond()                             const = 0;
   virtual Hours        get_hours_after_midnight()                    const = 0;
   virtual Minutes      get_minutes_after_midnight()                  const = 0;
   virtual Seconds      get_seconds_after_midnight()                  const = 0;
   // essentially aliases
   inline virtual Hours get_hours()                                        const
      { return this->get_hours_after_midnight(); }
   inline virtual Minutes get_minutes()                                    const
      { return get_minutes_after_midnight(); }
   inline virtual Seconds get_seconds()                                    const
      { return get_seconds_after_midnight(); }
   virtual time_HHMMSS  get_HHMMSS()                                  const = 0;
 public: // assignations
   virtual datetime64 clear()                                 initialization_=0; //180822
   virtual datetime64 set_time(const Time &_time)                assignation_=0;
   virtual datetime64 set_time64(datetime64 time64)              assignation_=0;
   virtual datetime64 set_datetime64(datetime64 time64)          assignation_=0;
   virtual datetime64 set_now() = 0;
   // Sets to and returns the computer's system date/time.
   virtual datetime64 set_S       (Seconds seconds)              assignation_=0;
   virtual datetime64 set_HHMMSS  (time_HHMMSS HHMMSS)           assignation_=0;
   virtual datetime64 set_HMS
      (Hour hour, Minute minute, Second second)                  assignation_=0;
   virtual datetime64 set_HMSm
      (Hour hour, Minute minute, Second second
      ,Millisecond millisecond)                                  assignation_=0;
   virtual datetime64 set_HMSc
      (Hour hour, Minute minute, Second second
      ,Centisecond centisecond)                                  assignation_=0;
 public: // autoincrement
   virtual datetime64   inc_hours(Hours hours)                   assignation_=0;
   virtual datetime64   inc_minutes(Minutes minutes)             assignation_=0;
   virtual datetime64   inc_seconds(Seconds seconds)             assignation_=0;
 public: // math
 public: // affirmations
 public: // methods for arbitrary time
// defined in temporal   virtual int8 compare(const Time_interface &other_time)               const=0;
 public: // string conversion
   virtual void prefer_time_format(const Time_format *format=0) contribution_=0;
   virtual const std::string &append_to_string
      (std::string         &target
      ,const Date_format *target_date_format/*=0*/                                       //180624
      ,const Time_format *target_time_format/*=0*/)                           const=0;
   virtual datetime64 set_c_str
      (const char *date_str
      ,const Time_format *from_format = 0)                       assignation_=0; //180625
   virtual datetime64 set_string
      (const std::string &time_string
      ,const Time_format *from_format = 0)                       assignation_    //180625
      { return set_c_str(time_string.c_str(),from_format); }                     //180625
 public: // operators (these are valid interface implementations because they
      // are implemented with virtual methods.

};
//_2017-04-26___________________________________________________Time_interface_/
} // namespace CORN
// Roger Nelson rnelson@wsu.edu

#endif
