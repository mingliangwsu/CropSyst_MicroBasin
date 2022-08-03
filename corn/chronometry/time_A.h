#ifndef time_AH
#define time_AH
#include "corn/chronometry/time_I.h"
#include "corn/chronometry/time_format.h"
namespace CORN
{
   class Date;                                                                   //170815
//______________________________________________________________________________
class Time_abstract
: public implements_ Time
{protected:

   contribute_ const Time_format *preferred_format; // not owned

   CORN::Date &date_tic;                                                         //170825
      // when adding or subtracting time that would exceed date
      // overflow or underflow it contributed/deducted to date_tick
 public:
   Time_abstract();
   Time_abstract(CORN::Date &date_tic);                                          //170825
 public: // accessors
   virtual Hour            get_hour()                                     const;
   virtual Minute          get_minute()                                   const;
   virtual Second          get_second()                                   const;
   virtual Centisecond     get_centisecond()                              const;
   virtual Millisecond     get_millisecond()                              const;

   inline virtual Hours get_hours_after_midnight()                        const
      { return get_seconds()/(24*60); }
   inline virtual Minutes get_minutes_after_midnight()                    const
      { return get_seconds() / 60; }

   //probably implement here virtual Seconds      get_seconds_after_midnight()                  const = 0;
   inline virtual nat32 get_hour_minute_second()                          const
      { return   (nat32)(get_hour() * 10000)
               + (nat32)(get_minute()* 100)
               + (nat32)(get_second());
      }
   inline virtual DOY get_DOY()                              const { return 0; }
   virtual time_HHMMSS     get_HHMMSS()                                   const;
 public: // assignations
   virtual datetime64 clear()                                   initialization_; //180822
   virtual datetime64 set_HHMMSS (time_HHMMSS HHMMSS)              assignation_;
   virtual datetime64 set_HMS
      (Hour hour, Minute minute, Second second)                    assignation_;
   virtual datetime64 set_HMSc
      (Hour hour, Minute minute, Second second
      ,Centisecond centisecond)                                    assignation_;
   virtual datetime64 set_HMSm
      (Hour hour, Minute minute, Second second
      ,Millisecond millisecond)                                    assignation_;
   virtual datetime64 set_time64 (datetime64 time64)               assignation_;
   virtual datetime64 set_now()                                    assignation_;

 public: // autoincrement
 public: // math
   virtual datetime64 inc_days(int32 days)                        modification_;
 public: // affirmations
 public: // methods for arbitrary time
 public: // string conversation
   virtual void prefer_time_format(const Time_format *format=0)   contribution_;
   virtual const std::string &append_to_string
      (std::string         &target
      ,const Date_format *target_date_format/*=0*/                                     //180624
      ,const Time_format *target_time_format/*=0*/)                                    const;
   virtual datetime64 set_c_str
      (const char *date_str
      ,const Time_format *setting_format)                          assignation_;
};
//_2017-04-26____________________________________________________Time_abstract_/
} // namespace CORN
// Roger Nelson rnelson@wsu.edu

#endif
