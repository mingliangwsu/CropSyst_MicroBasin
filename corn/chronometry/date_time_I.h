#ifndef date_time_interfaceH
#define date_time_interfaceH
#include "corn/chronometry/date_I.h"
#include "corn/chronometry/time_I.h"
namespace CORN
{
//______________________________________________________________________________
interface_ Date_time
: public extends_interface_ Temporal
{
 public: // accessors
   virtual modifiable_ Time       &mod_time()                   modification_=0;
   virtual const       Time       &ref_time()                           const=0;
   virtual modifiable_ Date       &mod_date()                   modification_=0;
   virtual const       Date_const &ref_date()                           const=0;
   //inline virtual datetime64 get_datetime64()                           const=0;  // may need to move this to temporal
 public: // accessors (date)
   inline virtual Year      get_year()                                     const { return ref_date().get_year(); }

/*NYN
   inline virtual datetime64   get_datetime64()                                const=0;
      ///< \returns the date, time or date time as a 64 bit float (double)
   inline virtual float64 get_time64()                       const { return 0; } //170815
      inline virtual date32       get_date32()                                    const=0;
      inline virtual Year         get_year()                                      const=0;
      // Note that in ISO8601:2004 negative years are 1 - the BC year
      // I.e.  0 is 1BC  -1 is 2BC
*/
   inline virtual DOY          get_DOY()                                   const { return ref_date().get_DOY(); }
   inline virtual Month        get_month()                                 const { return ref_date().get_month(); }
   inline virtual DOM          get_DOM()                                   const { return ref_date().get_DOM(); }
   inline virtual void         gregorian(Year &year, Month &month, DOM &dom)   const { return ref_date().gregorian(year,month,dom); }
/*NYI
   inline virtual Days_of_week day_of_week()                                   const=0;
*/
 public: // accessors (time)
/*
   inline virtual float64 get_time64()                                  const=0; //170815
*/
   inline virtual Hour         get_hour()                                  const { return ref_time().get_hour(); }
   inline virtual Minute       get_minute()                                const { return ref_time().get_minute(); }
   inline virtual Second       get_second()                                const { return ref_time().get_second(); }
   inline virtual Centisecond  get_centisecond()                           const { return ref_time().get_centisecond(); }
   inline virtual Millisecond  get_millisecond()                           const { return ref_time().get_millisecond(); }
   inline virtual Hours        get_hours_after_midnight()                  const { return ref_time().get_hours_after_midnight(); }
   inline virtual Minutes      get_minutes_after_midnight()                const { return ref_time().get_minutes_after_midnight(); }
   inline virtual Seconds      get_seconds_after_midnight()                const { return ref_time().get_seconds_after_midnight(); }
   inline virtual Hours get_hours()                                        const { return ref_time().get_hours(); }
   inline virtual Minutes get_minutes()                                    const { return ref_time().get_minutes(); }
   inline virtual Seconds get_seconds()                                    const { return ref_time().get_seconds(); }
   virtual time_HHMMSS  get_HHMMSS()                                       const { return ref_time().get_HHMMSS(); }
 public: // modifiers (date)
   inline virtual datetime64 set_date32(date32 date32)              assignation_ { return mod_date().set_date32(date32); }
/* specifically implemented in derived classes
   inline virtual datetime64 set_datetime64(datetime64 value)       assignation_ { return mod_date().set_datetime64(value); }
*/
   inline virtual datetime64 set_year(Year year)                    assignation_ { return mod_date().set_year(year); }
   inline virtual datetime64 set_DOY(DOY doy)                       assignation_ { return mod_date().set_DOY(doy); }
   inline virtual datetime64 set_YMD(Year year,Month month,DOM dom) assignation_ { return mod_date().set_YMD(year, month, dom); }
   inline virtual datetime64 set_YD(Year year,DOY doy)              assignation_ { return mod_date().set_YD(year, doy); }
   inline virtual datetime64 set_month(Month month)                 assignation_ { return mod_date().set_month(month); }
   inline virtual datetime64 set_DOM(DOM dom)                       assignation_ { return mod_date().set_DOM(dom); }
   inline virtual datetime64 set(const Temporal &other)             assignation_ { return mod_date().set(other); }
 public: // autoincrement (date)
   inline virtual datetime64 inc_years(int16 years)                modification_ { return mod_date().inc_years(years); }
   inline virtual datetime64 dec_years(int16 years)                modification_ { return mod_date().dec_years(years); }
   inline virtual datetime64 inc_months(int16 months)              modification_ { return mod_date().inc_months(months); }
   inline virtual datetime64 dec_months(int16 months)              modification_ { return mod_date().dec_months(months); }
   inline virtual datetime64 inc_days(int32 days)                  modification_ { return mod_date().inc_days(days); }
   inline virtual datetime64 dec_days(int32 days)                  modification_ { return mod_date().dec_days(days); }
   inline virtual datetime64 inc_day()                             modification_ { return mod_date().inc_day(); }
   inline virtual datetime64 dec_day()                             modification_ { return mod_date().dec_day(); }
 public: // assignations
   virtual datetime64 set_now() = 0;
   inline virtual datetime64 clear()                             initialization_
      {mod_date().clear(); mod_time().clear(); return 0;}
 public: // assignations (time)
   /*NYN
   inline virtual datetime64 set_time(const Time_interface &time_)  assignation_ { return mod_time().set_time(time_); }
   */
   inline virtual datetime64 set_time64(datetime64 time64)          assignation_ { return mod_time().set_time64(time64); }
   inline virtual datetime64 set_datetime64(datetime64 time64)      assignation_=0;
   /*
   inline virtual datetime64 set_datetime64(datetime64 time64)      assignation_ { return mod_time().set_datetime64(time64); }
   */
   inline virtual datetime64 set_S       (Seconds seconds)          assignation_ { return mod_time().set_S(seconds); }
   inline virtual datetime64 set_HHMMSS(time_HHMMSS HHMMSS)         assignation_ { return mod_time().set_HHMMSS(HHMMSS); }
   inline virtual datetime64 set_HMS
      (Hour hour, Minute minute, Second second)                     assignation_ { return mod_time().set_HMS(hour, minute, second); }
   inline virtual datetime64 set_HMSm
      (Hour hour, Minute minute, Second second
      ,Millisecond millisecond)                                     assignation_ { return mod_time().set_HMSm(hour,minute,second,millisecond); }
   inline virtual datetime64 set_HMSc
      (Hour hour, Minute minute, Second second
      ,Centisecond centisecond)                                     assignation_ { return mod_time().set_HMSc(hour,minute,second,centisecond); }
 public: // autoincrement (time)
   inline virtual datetime64   inc_hours(Hours hours)               assignation_ { return mod_time().inc_hours(hours); }
   inline virtual datetime64   inc_minutes(Minutes minutes)         assignation_ { return mod_time().inc_minutes(minutes); }
   inline virtual datetime64   inc_seconds(Seconds seconds)         assignation_ { return mod_time().inc_seconds(seconds); }
 public: // math (date)
/* NYN
   inline virtual nat32 days_between
      (const Date_const_interface &date2,bool inclusive)         calculation_=0;
   inline virtual int32 days_to(const Date_const_interface &date2)      calculation_=0;
 public: // affirmations
   inline virtual bool is_relative()                                    affirmation_=0;
 public: // methods with respect to the current date
   inline virtual bool is_leap_this_year()                              affirmation_=0;
*/
   inline virtual nat16 days_in_this_year()                                const { return ref_date().days_in_this_year(); }
/* NYI
   inline virtual DOM days_in_month()                                          const=0;
 public: // methods for arbitrary date
   inline virtual bool is_leap_year(Year year)                          affirmation_=0;
   */
   inline virtual nat16 days_in_year(Year year)                            const { return ref_date().days_in_year(year); }
   /*NYN
   inline virtual bool is_last_DOY()                                       const
   inline virtual bool is_last_DOM()                                       const
*/
   //inline virtual datetime64 set_DT(const Date &date,const Time &time) assignation_
/*  NYI
   inline virtual datetime64 set_date(const Date_interface &date)       assignation_=0;
   inline virtual datetime64 set_datetime64(datetime64 value)           assignation_=0;
   inline virtual datetime64 set_date32(datetime64 value)               assignation_=0;
 public: // modifiers (time)
 public: // math (time)
 public: // affirmations (time
 public: // methods for arbitrary time
 public: // conversions
*/
};
//_2017-04-26______________________________________________Date_time_interface_/
} // namespace CORN
// Roger Nelson rnelson@wsu.edu
#endif

