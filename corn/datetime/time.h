#ifndef timeH
#define timeH
#include "corn/chronometry/temporal.h"
/*170430
#ifndef temporal_baseH
#  include "corn/datetime/temporal_base.h"
#endif
#ifndef time_typesHPP
#  include "corn/datetime/time_types.hpp"
#endif
*/

#ifndef time_formatH
#  include "corn/datetime/time_format.h"
#endif
/* 170523
#define get_hours() get_hours_after_midnight()
#define get_minutes() get_minutes_after_midnight()
#define get_seconds() get_seconds_after_midnight()
*/
/* This class is stores time values.
   Time is stored as a 32bit integer in seconds past midnight
   0 = midnight

   any number >= 86400 represents the number of days plus seconds.

   This class does not store fractions of a second.
   To store fractions of a second, use the Time64 class.
   To store dates and times, use the Date64 class.

   Currently we output only one text format
   HH:MM:SS:MMM
*/

namespace CORN {
//______________________________________________________________________________
class Time
: virtual public Temporal                                                        //170430
//170430 : virtual public Temporal_base                                                   //030401
{protected:
   Seconds     seconds;
 public:
   Time_format format;                                                           //141120
 public: // accessors
   inline char get_separator()                                            const { return format.separator; }       //141120_991115
   inline void set_separator(char _separator = ':')                             { format.separator = _separator; } //141120_991115
 public:
   Time();
   inline Time(const Time &copy_from_time)
      : Temporal()                                                               //170430
      //170430 : Temporal_base()                                                          //120511
      , seconds(copy_from_time.get_seconds())                                    //141120
      , format       (copy_from_time.format)                                     //141120
      {}
   Time(Datetime64 time64);                                                      //030714
   inline Time(Hour hour)
      : seconds(0)                                                               //991115
      , format()                                                                 //141120
      { set_HMS(hour,0,0);}
   inline Time(Hour hour, Minute minute)
      : seconds(0)                                                               //991115
      , format()                                                                 //141120
      { set_HMS(hour,minute,0);}
   inline Time(Hour hour, Minute minute, Second second)
      : seconds(0)                                                               //991115
      , format()                                                                 //141120
      { set_HMS(hour,minute,second);}
   inline virtual Seconds get_seconds_after_midnight()                     const
      { return seconds; }
   inline virtual Minutes get_minutes_after_midnight()                     const
      { return seconds / 60; }
   inline virtual Hours get_hours_after_midnight()                         const
      { return seconds/(24*60); }
   inline Second  get_second()                                             const
      { return (Second)(seconds % 60); }
   inline Minute  get_minute()                                             const
      { return (Minute)((seconds/60) % 60);}
   inline Hour get_hour()                                                  const
      { return (Hour)((seconds / 3600) % 24); }
   inline virtual Hours get_hours()                                        const //170523
      { return this->get_hours_after_midnight(); }
   inline virtual Minutes get_minutes()                                    const //170523
      { return get_minutes_after_midnight(); }
   inline virtual Seconds get_seconds()                                    const //170523
      { return get_seconds_after_midnight(); }
   inline virtual void  set_HHMMSS(int32 HHMMSS)
      {  Hour hour = (Hour )(HHMMSS/10000);
         int32 MMSS = HHMMSS%10000;
         Minute minute = (Minute)(MMSS / 100);
         Second second = (Second)(MMSS%100);
         set_HMS(hour,minute,second);
      }
   inline virtual int32 get_hour_minute_second()                           const
      { return   (int32)(get_hour() * 10000)
               + (int32)(get_minute()* 100)
               + (int32)(get_second());
      }
   virtual Datetime64 get_datetime64()                                     const;//030108
      // This returns the date, time or date time as a 64 bit float (double)
   inline void set_HMS(Hour hour, Minute minute, Second second)
      {  seconds = hour * 60 * 60 + minute * 60 + second;}
   inline void set_S(Seconds _seconds)    { seconds = _seconds; }                //990505
   inline void set(const Time &_time)     { seconds =(_time.get_seconds());  }
#ifdef NYI
#  if (__BCPLUSPLUS__ >= 0x0550)
   /*virtual */void set(const TDateTime &new_date);                              //011203
   virtual TDateTime get_delphi_date_time(TDateTime &new_date)             const;//011203
#endif
#endif
   virtual Datetime64 set_datetime64(Datetime64 time64);                         //030714
   inline void  set_format                                                       //141120_991220
      (nat8 i_time_ordering = T_HMS
      ,nat8 i_time_style    = T_24hour
      ,nat8 i_time_separator=':')
      {  format.ordering = i_time_ordering;
         format.styles = i_time_style;
         format.separator = i_time_separator;
      }
   int8 compare_time(const Time &other_time)                               const;
   inline virtual Days plus_hours(Hours hours)                                   //030714
      { // returns the number of days the are too many seconds of
         return
            inc_seconds                                                          //170426
            //170427 plus_seconds                                                //991014
            ((Seconds)(hours * 3600));
      }
   /*170427 inline virtual Days plus_minutes(Minutes more_minutes)
   inline virtual Days plus_minutes(Minutes more_minutes)
      {  // returns the number of days there are too many seconds of
         return plus_seconds((Seconds)(more_minutes * 60));                      //991014
      }
   virtual Days plus_seconds(Seconds more_seconds);
   */
   inline virtual Datetime64 inc_minutes(Minutes more_minutes)                   //170427
      {  // returns the number of days there are too many seconds of
         return inc_seconds((Seconds)(more_minutes * 60));
      }
   virtual Datetime64 inc_seconds(Seconds more_seconds);                         //170427

   virtual const std::string &append_to_string(std::string &target)        const;//140614
   virtual Datetime64 set_c_str(const char *time_str);                           //050413
};
//______________________________________________________________________________
//011212 I think for the << and >> operators to compile in unix and builder
// They cannot be in the class

//  #if defined(VCL_IOSTREAM)
//   ostream & operator <<(ostream& os, const Time& arg);
//   istream & operator >>(istream& is, Time& arg);
///  #endif

extern float32 CORN_time_zone_hours_offset[] ;
//______________________________________________________________________________
class Local_time
: public Time
{
   //120516 check used enum time_zones {GMT,A,B,Ca,Cb,Da,Db,E,Ea,Eb,Fa,Fb,G,H,I,Ia,Ib,Ka,Kb,La,Lb,Ma,Mb,Na,N,O,Pa,Pb,Q,R,S,T,Ua,Ub,Va,Vb,W,X,Y};
   float time_zone_hours_from_UT;
   bool  in_daylight_savings_time;
 public: // constructors
   inline Local_time()
     : Time()
      , time_zone_hours_from_UT(0.0)
      , in_daylight_savings_time(false)
      {
//WARNING         We will want to get the TZ on DLST from the OS time data structure
      }
   // This constructor is used when we don't really care about local time ideosyncroncies and we want the system time
   inline Local_time(const Time &i_time)
      : Time(i_time)
      , time_zone_hours_from_UT(0.0)
      , in_daylight_savings_time(false)
      {}
   // This constructor is used when we don't really care about local time ideosyncroncies
 public: // Accessors
   bool  get_in_daylight_savings_time();
};
//______________________________________________________________________________
}; // namespace CORN
#endif

