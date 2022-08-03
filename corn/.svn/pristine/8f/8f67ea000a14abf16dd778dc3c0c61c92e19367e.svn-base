
#  include "corn/datetime/datetime64.h"
#  include "corn/datetime/date.hpp"
#  include "corn/datetime/time.h"
#  include "corn/math/compare.hpp"
#  if defined(__MSDOS__) || defined(_WIN64) || defined(_WIN32)
// for computer date
#     include <dos.h>
#  endif
#  ifdef __unix
#     include <time.h>
#  endif

#   include <string.h>
#if ((_MSC_VER > 0) && (_MSC_VER < 1700))
#   include <atltime.h>
#else
#include <time.h>
#endif
#include  <assert.h>
namespace CORN {
//______________________________________________________________________________
Date_time_64::Date_time_64(Datetime64 date_time_)
: value(date_time_)
, date_format()                                                                  //141122
, time_format()                                                                  //141122
{}
//______________________________________________________________________________
Date_time_64::Date_time_64(int32 date, Seconds seconds)
: value(date)
, date_format()                                                                  //141122
, time_format()                                                                  //141122
{  if (seconds)
      value += ((float64)seconds/86400.0);
}
//______________________________________________________________________________
Date_time_64::Date_time_64()
: value(0.0)                                                                     //030729
, date_format()                                                                  //141122
, time_format()                                                                  //141122
{  // Current computer's date and time
   set_now();
}
//______________________________________________________________________________
Date_time_64::Date_time_64(const Date &date, const Time &time)
//141120 : Date_time_format(date,time)                                                    //050412
: value(0)
, date_format()                                                                  //141122
, time_format()                                                                  //141122
{  set_DT(date,time);
}
//______________________________________________________________________________
Date_time_64::Date_time_64(const Date_time_64 &to_copy_from)
: Date_time()
, date_format()                                                                  //141122
, time_format()                                                                  //141122
, Temporal()
//170430 , Temporal_base()
, value(to_copy_from.get_datetime64())
{  // Copy constructor
}
//______________________________________________________________________________
Datetime64 Date_time_64::set_now()
{
#if defined(__MSDOS__) || defined(_WIN64) || defined(_WIN32)
   #if (!defined(_MSC_VER) && !defined(__MINGW32__))
      struct date date_struct;
      getdate(&date_struct);
      set_YMD((Year)date_struct.da_year,(CORN::Month)date_struct.da_mon,(CORN::DOM)date_struct.da_day);
      struct time time_struct;
      gettime(&time_struct);
      return set_HMSc((Hour)time_struct.ti_hour,(Minute)time_struct.ti_min,(Second)time_struct.ti_sec,(Centisecond)time_struct.ti_hund);
   #endif
#endif
#if ((_MSC_VER > 0) && (_MSC_VER < 1700))
   // NOTE it may be earier versions that dropped CTime
    CTime theTime;                                                               //040908
    theTime = CTime::GetCurrentTime();                                           //040908
    set_YMD((Year)theTime.GetYear(),(Month)theTime.GetMonth(),(DOM)theTime.GetDay());
    return set_HMS((Hour)theTime.GetHour(),(Minute)theTime.GetMinute(),(Second)theTime.GetSecond());
#else
    time_t     now = time(0);
    struct tm  tstruct;
    tstruct = *localtime(&now);
      // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
      // for more information about date/time format
      //strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

      set_YMD((Year)(tstruct.tm_year + 1900),(Month)(tstruct.tm_mon),(DOM)(tstruct.tm_mday));
      return set_HMS((Hour)(tstruct.tm_hour),(Minute)(tstruct.tm_min),(Second)(tstruct.tm_sec));
#endif
#ifdef __unix
     tm *time_struct;
     time_t timer;
     time(&timer);
     time_struct = localtime(&timer);
     //localtime_r(&timer,&time_struct);
     set_YD(                                                                     //030713
          1900+time_struct->tm_year //according to the docs this is years since 1900 so I hope it is 2000 complient. 990824
         ,time_struct->tm_yday);
      return set_HMS((Hour)time_struct->tm_hour,(Minute)time_struct->tm_min,(Second)time_struct->tm_sec);
#endif
}
//______________________________________________________________________________
// Temporal_base overrides
const std::string &Date_time_64::append_to_string(std::string &target)     const
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((long)date);
   new_date.format.copy_format(date_format);                                     //141120
   new_date.append_to_string(target);
   if (!is_approximately<Datetime64>(time,0.0,0.000000001))
   {
      Time new_time(time);
      new_time.format.copy_format(time_format);                                  //141120
      target.append(" ");
      new_time.append_to_string(target);
   }
   return target;
}
//_3014-06-15___________________________________________________________________
/*1406515
const char  *Date_time_64::text_str(char *result) const
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((long)date); new_date.copy_format(*this);
   Time new_time(time);       new_time.copy_format(*this);
   new_date.text_str(result); strcat(result," ");
   char time_str[50];
   new_time.text_str(time_str);
   strcat(result,time_str);
   return result;
}
*/
//______________________________________________________________________________
void Date_time_64::split(Datetime64 &date_part, Datetime64 &time_fract) const
{  uint32 value_int32 = (uint32)value;                                           //040909
   date_part = value_int32;
   time_fract = value - date_part;;
}
//_2003-07-15___________________________________________________________________
Datetime64 Date_time_64::join(Datetime64 date_part, Datetime64 time_fract)
{  value = date_part + time_fract;
   return value;
}
//_2003-07-15___________________________________________________________________
Datetime64   Date_time_64::get_time64() const
   // Returns the time (fraction)
{  int32 date_part  = (int32)value;
   Datetime64 time_part = value - (Datetime64)date_part;
   return time_part;
}
//______________________________________________________________________________
// The following get from the date part
Year      Date_time_64::get_year() const
  // extracts the year from the Date date
{  Date new_date((int32)value);
   return new_date.get_year();
}
//______________________________________________________________________________
DOY       Date_time_64::get_DOY() const
   // extracts the day of year from the Date date
{  Date new_date((int32)value);
   return new_date.get_DOY();
}
//______________________________________________________________________________
Month     Date_time_64::get_month() const
{  Date new_date((int32)value);
   return new_date.get_month();
}
//______________________________________________________________________________
DOM       Date_time_64::get_DOM() const
{  Date new_date((int32)value);
   return new_date.get_DOM();
}
//______________________________________________________________________________
void       Date_time_64::gregorian(Year &year, Month &month, DOM &dom) const
{  Date new_date((int32)value);
   new_date.gregorian(year,month,dom);
}
  // extracts the year month and day of month from the Date date
//______________________________________________________________________________
// The following get from the time part
int32     Date_time_64::get_HHMMSS() const
{  return(int32)(get_hour() * 10000)
       + (int32)(get_minute()* 100)
       + (int32)(get_second());
}
//______________________________________________________________________________
Millisecond   Date_time_64::get_millisecond() const
{  Datetime64 time = get_time64();
   Millisecond millisecond = (Millisecond)(time / (1.0/86400000.0));
   return millisecond;
}
//______________________________________________________________________________
Centisecond   Date_time_64::get_centisecond() const
{  Datetime64 time = get_time64();
   Centisecond centisecond = (Centisecond)(time / (1.0/8640000.0));
   return centisecond;
}
//______________________________________________________________________________
Second   Date_time_64::get_second() const
{  Datetime64 time = get_time64();
   float64 second = time / (1.0/86400.0);
   return (Second)second;
}
//______________________________________________________________________________
Minute Date_time_64::get_minute() const
{  Datetime64 time = get_time64();
   float64 minute = time / (1.0/1440.0);
   return (Minute)minute;
}
//______________________________________________________________________________
Hour Date_time_64::get_hour() const
{  Datetime64 time = get_time64();
   float64 hour = time / (1.0/24.0);
   return (Hour)hour;
}
//______________________________________________________________________________
Hours     Date_time_64::get_hours_after_midnight()  const   { return (Hours)(get_time64()*24.0); }
Minutes   Date_time_64::get_minutes_after_midnight() const  { return (Minutes)(get_time64()*1440.0); }
Seconds   Date_time_64::get_seconds_after_midnight() const  { return (Seconds)(get_time64()*86400.0); }
//______________________________________________________________________________
// The following reset the entire date time value.
Datetime64 Date_time_64::set_DT(const Date &date, const Time &time)
{  return join(date.get_datetime64(),time.get_datetime64());
}
//_2003-07-17___________________________________________________________________
Datetime64 Date_time_64::set_date(Date i_date32)
{ return value = i_date32.get_datetime64(); }   // add option to set the entire value?
//_2010-01-16_2003-07-17___________________________________________________________________
// The following methods set only the date part of the date time. The updated date time is returned.
Datetime64 Date_time_64::set_year(Year year)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);
   new_date.set_year(year);
   return join(new_date.get_datetime64(),time);
}
//_2003-07-17___________________________________________________________________
Datetime64 Date_time_64::set_month(Month month)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);
   new_date.set_month(month);
   return join(new_date.get_datetime64(),time);
}
//_2005-04-06___________________________________________________________________
Datetime64 Date_time_64::set_DOM(DOM dom)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);
   new_date.set_DOM(dom);
   return join(new_date.get_datetime64(),time);
}
//_2005-04-06___________________________________________________________________
Datetime64 Date_time_64::set_DOY(DOY doy)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);
   new_date.set_DOY(doy);
   return join(new_date.get_datetime64(),time);
}
//_2003-07-13___________________________________________________________________
Datetime64 Date_time_64::set_c_str(const char *date_time_str)
{  //need to implement  expect the string to be in the current format
   Date date; date.format.copy_format(date_format /*141120 *this*/); date.set_c_str(date_time_str);     //141120_110823
      // Warning, need to check to make sure that any time part is handled OK
   Time time; time.format.copy_format(time_format /*141120 *this*/); time.set_c_str(date_time_str);     //141120_110823
      // WARNING  need to check to make sure that any date part is handled OK
   return join(date.get_datetime64(),time.get_datetime64());
}
//_2003-07-13___________________________________________________________________
Datetime64 Date_time_64::set_YMD(Year year,Month month,DOM dom)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.set_YMD(year,month,dom);
   return join(new_date.get_datetime64(),time);
}
//_2003-07-13___________________________________________________________________
Datetime64 Date_time_64::set_YD(Year year,DOY doy)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.set_YD(year,doy);
   return join(new_date.get_datetime64(),time);
}
//_2003-07-13___________________________________________________________________
Datetime64 Date_time_64::inc()
{  // Adds 1 to the date. Returns the new date (datetime)
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.inc();
   return join(new_date.get_datetime64(),time);
}
//______________________________________________________________________________
Datetime64 Date_time_64::dec()
{  // Subtracts one from the date. Returns the new date (datetime)
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.dec();
   return join(new_date.get_datetime64(),time);
}
//______________________________________________________________________________
Datetime64 Date_time_64::inc_day(int32 days)
{  // Adds days to the date incrementing the year if necessary.
   //   If offset is negative, offset days are subtracted
   Datetime64 date = 0;
   Datetime64 time = 0;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.inc_day(days);
   return join(new_date.get_datetime64(),time);
}
//______________________________________________________________________________
Datetime64 Date_time_64::dec_day(int32 days)
{  // Subtracts days from the date decrementing the year if necessary.
   //   If offset is negative, offset days are added
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.dec_day(days);
   return join(new_date.get_datetime64(),time);
}
//______________________________________________________________________________
Datetime64  Date_time_64::inc_year(int16 years)
{ // Adds offset years to the date.
  // If years is negative,  years are subtracted
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //051218
   new_date.inc_year(years);
   return join(new_date.get_datetime64(),time);
}
//_1997-09-09___________________________________________________________________
Datetime64  Date_time_64::dec_year(int16 years)
{ // Subtracts offset years to the date.
  // If years is negative,  years are added
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.dec_year(years);
   return join(new_date.get_datetime64(),time);
}
//_1997-09-09___________________________________________________________________
Datetime64   Date_time_64::inc_month(int16 months)
{ // Adds months to the date.
  //   If months is negative,  months are subtracted
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.inc_month(months);
   return join(new_date.get_datetime64(),time);
}
//_1997-09-09___________________________________________________________________
Datetime64   Date_time_64::dec_month(int16 months)
{ // Subtracts months from the date.
  //   If months is negative,  months are added
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   Date new_date((int32)date);                                                   //040909
   new_date.dec_month(months);
   return join(new_date.get_datetime64(),time);
}
//_1997-09-09___________________________________________________________________
// The following methods set only the time part of the date time. The updated date time is returned.
Datetime64 Date_time_64::set_time64(Datetime64 new_time)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   return join(date,new_time);
}
//______________________________________________________________________________
Datetime64 Date_time_64::set_time(const Time &time)
{  return set_S(time.get_seconds());
}
//_2003-07-17___________________________________________________________________
Datetime64 Date_time_64::set_HHMMSS(int32 HHMMSS)
{  Hour hour = (Hour )(HHMMSS/10000);
   int32 MMSS = HHMMSS%10000;
   Minute minute = (Minute)(MMSS / 100);
   Second second = (Second)(MMSS%100);
   return set_HMS(hour,minute,second);
}
//______________________________________________________________________________
Datetime64 Date_time_64::set_S(Seconds seconds)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   Datetime64 new_time = (float64)seconds/86400.0;
   return join(date,new_time);
}
//______________________________________________________________________________
Datetime64 Date_time_64::set_HMS(Hour hour, Minute minute, Second second)
{  return set_S(second + minute*60 + hour*3600);                                 //131010
/*131010 This was wrong
   Datetime64 date;
   Datetime64 time;
   split(date,time);
   131010 time = (float64)hour / (float64)Hours_per_day + (float64)minute / (float64)Minutes_per_day+ (float64)second/(float64)Seconds_per_day;
   return join(date,time);
*/
}
//______________________________________________________________________________
Datetime64 Date_time_64::set_HMSm(Hour hour, Minute minute, Second second,Millisecond millisecond)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   float64 seconds = second + minute*60 + hour*3600;                             //131010
   float64 milliseconds_after_midnight = seconds *1000 + millisecond;            //131010
   time =  milliseconds_after_midnight / 86400000.0;                             //131010
   //131010 time = (float64)hour / (float64)Hours_per_day + (float64)minute / (float64)Minutes_per_day + (float64)second/(float64)Seconds_per_day + (float64)millisecond/(float64)Milliseconds_per_day;
   return join(date,time);
}
//______________________________________________________________________________
Datetime64 Date_time_64::set_HMSc(Hour hour, Minute minute, Second second,Centisecond centisecond)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   float64 seconds = second + minute*60 + hour*3600;                             //131010
   float64 centiseconds_after_midnight = seconds *100 + centisecond;             //131010
   time = centiseconds_after_midnight / 8640000.0;                               //131010
/*131010
   float64 hour_f64 = (float64)hour;
   float64 hours_per_day_f64 = (float64)Hours_per_day ;
   float64 hour_term    = hour_f64       / hours_per_day_f64;
   float64 minute_f64 = (float64)minute;
   float64 minutes_per_day_f64 = (float64)Minutes_per_day;
   float64 minute_term  = minute_f64     / minutes_per_day_f64;
   float64 second_f64 = (float64)second;
   float64 seconds_per_day_f64 = (float64)Seconds_per_day;
   float64 second_term  = second_f64 / seconds_per_day_f64;
   float64 centisecond_f64 = (float64)centisecond;
   float64 centiseconds_per_day_f64 = (float64)Centiseconds_per_day;
   float64 csecond_term = centisecond_f64/centiseconds_per_day_f64;
   time = hour_term + minute_term + second_term + csecond_term;
*/
   return join(date,time);
}
//_207-06-04_2003-07-14_________________________________________________________
Datetime64 Date_time_64::inc_hour(Hours hours)
{  Datetime64 time_fract = (float64)hours/(24.0);                                //170502
   return inc_time_fract(time_fract);
}
//_2003-07-14___________________________________________________________________
Datetime64 Date_time_64::inc_minute(Minutes minutes)
{  Datetime64 time_fract = (float64)minutes/(1440.0);
   return inc_time_fract(time_fract);
}
//_2003-07-14___________________________________________________________________
Datetime64 Date_time_64::inc_second(Seconds seconds)
{  Datetime64 time_fract = (float64)seconds/(86400.0);
   return inc_time_fract(time_fract);
}
//_2003-07-14___________________________________________________________________
Datetime64 Date_time_64::inc_time_fract(Datetime64 time_fract)
{  Datetime64 date;
   Datetime64 time;
   split(date,time);
   time += time_fract;
   Datetime64 days;
   Datetime64 new_time;
   Date_time_64(time).split(days,new_time);
   Date new_date((int32)date);                                                   //040909
   new_date.inc_day((int32)days);                                                //040909
   return join(new_date.get_datetime64(),new_time);
}
//_2003-07-14___________________________________________________________________
// Date functions
DOY Date_time_64::days_in_this_year()
{  return Date(get_date32()).days_in_this_year();
}
//_1999-02-14___________________________________________________________________
nat32 Date_time_64::days_between(const Date_time &date2,bool inclusive) const
{  Date from_date(get_date32());
   Date to_date(date2.get_date32());
   return from_date.days_between((const CORN::Date_time &)to_date,inclusive);    //170430
}
//______________________________________________________________________________
} // namespace CORN

