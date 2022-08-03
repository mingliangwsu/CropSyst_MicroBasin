#include "corn/chronometry/time_A.h"
#include <time.h>
#include "corn/chronometry/time_format.h"
#include "corn/chronometry/date_32.h"
#include "corn/string/strconv.hpp"
#include <stdio.h>
#include <assert.h>
namespace CORN
{
CORN::Date_clad_32 irrelevent_date_tic;                                           //170815
//______________________________________________________________________________
Time_abstract::Time_abstract()
: Time()
, preferred_format(&ISO_8601_time_format)
, date_tic(irrelevent_date_tic)
{}
//_Time_abstract:constructor___________________________________________________/
Time_abstract::Time_abstract(CORN::Date_interface  &date_tic_)
: Time()
, preferred_format(&ISO_8601_time_format)
, date_tic(date_tic_)
{}
//_Time_abstract:constructor________________________________________2017-08-15_/
Hour Time_abstract::get_hour()                                             const
{ return (Hour)((get_seconds() / 3600) % 24); }
//_get_hour_____________________________________________________________________
Minute Time_abstract::get_minute()                                         const
{ return (Minute)((get_seconds()/60) % 60);}
//_get_minute___________________________________________________________________
Second Time_abstract::get_second()                                         const
{ return (Second)(get_seconds() % 60); }
//_get_second___________________________________________________________________
Centisecond Time_abstract::get_centisecond()                               const
{  datetime64 time = get_time64();
   Centisecond centisecond = (Centisecond)(time / (1.0/8640000.0));
   return centisecond;
}
//_get_centisecond_____________________________________________________________/
Millisecond Time_abstract::get_millisecond()                               const
{  datetime64 time = get_time64();
   Millisecond millisecond = (Millisecond)(time / (1.0/86400000.0));
   return millisecond;
}
//_get_millisecond_____________________________________________________________/
time_HHMMSS Time_abstract::get_HHMMSS()                                    const
{  return(int32)(get_hour() * 10000)
       + (int32)(get_minute()* 100)
       + (int32)(get_second());
}
//_get_HHMMSS__________________________________________________________________/
datetime64 Time_abstract::set_time64 (datetime64 time64)               assignation_
{
   assert(false); // derived class may need to implement
   return 0;
}
//_set_time64_______________________________________________________2017-04-27_/
datetime64 Time_abstract::clear()                                initialization_
{  return set_S(0); }
//_clear____________________________________________________________2018-08-22_/
datetime64 Time_abstract::set_now()
{  time_t timer;
   struct tm *tblock;
   timer = time(NULL);  // gets time of day
   tblock = localtime(&timer);// converts date/time to a structure */
   nat32 seconds = tblock->tm_sec;
   seconds += tblock->tm_min * 60;
   seconds += tblock->tm_hour * 3600;
   return set_S(seconds);
}
//_set_now__________________________________________________________2017-04-27_/
datetime64 Time_abstract::set_HHMMSS(time_HHMMSS HHMMSS)            assignation_
{  Hour hour = (Hour )(HHMMSS/10000);
   int32 MMSS = HHMMSS%10000;
   Minute minute = (Minute)(MMSS / 100);
   Second second = (Second)(MMSS%100);
   return set_HMS(hour,minute,second);
}
//_set_HHMMSS_______________________________________________________2017-04-27_/
datetime64 Time_abstract::set_HMS(Hour hour, Minute minute, Second second)
{  return set_S(second + minute*60 + hour*3600);
}
//_set_HMS__________________________________________________________2017-04-27_/
datetime64 Time_abstract::set_HMSc
(Hour hour, Minute minute, Second second,Centisecond centisecond)   assignation_
{
   float64 seconds = second + (minute*60) + (hour*3600);
   float64 centiseconds_after_midnight = (seconds *100) + centisecond;
   float64 time = centiseconds_after_midnight / 8640000.0;
   return set_time64(time);
}
//_set_HMSc_________________________________________________________2017-04-27_/
datetime64 Time_abstract::set_HMSm
(Hour hour, Minute minute, Second second
,Millisecond millisecond)                                           assignation_
{
   float64 seconds = second + (minute*60) + (hour*3600);
   float64 milliseconds_after_midnight = (seconds *100) + millisecond;
   float64 time = milliseconds_after_midnight / 86400000.0;
   return set_time64(time);
}
//_set_HMSm_________________________________________________________2017-08-24_/
datetime64 Time_abstract::inc_days(int32 days)                     modification_
{
   // Time classes don't know about days so they just through away the days.
   irrelevent_date_tic.inc_days(days);                                           //170815
   return get_datetime64();
}
//_inc_days_________________________________________________________2017-04-27_/
void Time_abstract::prefer_time_format(const Time_format *format_) contribution_
{  // Currently don't own format
   preferred_format = format_ ? format_ : &ISO_8601_time_format;
}
//_prefer_time_format_______________________________________________2017-04-28_/
const std::string &Time_abstract::append_to_string
(std::string         &target
,const Date_format *from_date_format                                             //180624
,const Time_format *from_time_format)                                      const //180624_170427
{
   const Time_format *format = from_time_format ? from_time_format : preferred_format;    //180624
   CORN::Hour   h = get_hour();
   CORN::Minute m = get_minute();
   CORN::Second s = get_second();
   if (format->ordering == T_omit) return target; // Just return the empty string //991220
   bool military_style = ((format->styles & 0x3) == T_military);                  //050312
   CORN::append_nat8_to_string
      (h,target,10
      ,military_style ? 2 : ((h<10)?1:2)
      ,military_style ? '0' : 0  );
   // Warning NYI the various ordering and style options
   char separator_str[2];                                                        //991115
   separator_str[0] =(char)format->separator;                                    //001126
   separator_str[1] = 0;                                                         //001126
   target.append(separator_str);                                                 //991115
   CORN::append_nat8_to_string(m,target,10,2,'0');                               //170427
   target.append(separator_str);                                                 //991115
   CORN::append_nat8_to_string(s,target,10,2,'0');                               //170427
   return target;
}
//_append_to_string_________________________________________________1999-05-05_/
datetime64 Time_abstract::set_c_str
(const char *time_str
,const Time_format *setting_format)
{
   const Time_format *format
      = setting_format ? setting_format : preferred_format;

   nat8 ordering  = format->ordering;                                            //141120
   nat8 separator = format->separator;                                           //141120
   nat8 styles    = format->styles;                                              //141120

   if (!time_str || !format->ordering)  // There may not be ordering if this is part of a date time string
      set_S(0);
   else
   {  //first skip over any date part  (we may have been passed an entire date time string)
      uint16 time_str_len =  (uint16)strlen(time_str);
      // Assume the first occurance of the separator (i.e. colon)
      // in the string is near the start of the time.
      // (Note: there does not have to be a separator)
      int first_separator_pos = 9999; // arbitrary large number
      for (int i = 0; (i < time_str_len) && (first_separator_pos==9999);i++)
         if (time_str[i] == separator) first_separator_pos = i;
      //NYI if ordering is decimal the find the right most period and
      // read this as double and simply set the time from this
      int time_start_pos = 0;
      for (int scan_from_right = std::min<int>(first_separator_pos,time_str_len) - 1
          ;scan_from_right && !time_start_pos
          ;scan_from_right--)
      {  // presume a space character delimits any date substring that may be in the time_str
         // There could be an am/pm indicator, but if there is the is almost always a (colon)separator character
         // so we should already be left of that
         char time_char = time_str[scan_from_right];
         if ((time_char == ' ') || (time_char == '\t')) // is space is not working! isspace(time_char))
            time_start_pos = scan_from_right;
         // Could also check for any character that is not a separator or digit
      };
      const char *time_only_str = time_str+time_start_pos;                       //070417
      // Now trying to do this without std::string
      // Now we have just the time and we can parse it.
      int hour  =0;  // Must be int for scanf
      int minute=0;
      int second=0;
      nat32 after_midnight = 0;
      bool pm = false;
      if (styles & T_am_pm)                                                      //141120_070417
      {  for (int i = 0; time_only_str[i] != 0; i++)
         {  char time_only_str_i = time_only_str[i] ;
            if ((time_only_str_i == 'P') && (time_only_str_i == 'M'))
                pm = true;
            if ((time_only_str_i == 'p') && (time_only_str_i == 'm'))
                pm = true;
         }
      }
      char fmt[100]; fmt[0] = 0;
      char sep_fmt[2]; sep_fmt[0]=0; sep_fmt[1]=0;
      sep_fmt[0] = separator;
      if ((ordering == T_HMS) | (ordering == T_HM) | (ordering == T_H) )
      {   if (separator) strcat(fmt,"%d"); // for the hour
         else           strcat(fmt,"%2d");  // for formats such as YYMMDD
      };
      if ((ordering == T_HMS) | (ordering == T_HM))
        strcat(fmt,sep_fmt); // hour minute separator
      if ((ordering == T_HMS) | (ordering == T_HM)| (ordering == T_MS) | (ordering == T_M))
      {   if (separator) strcat(fmt,"%d"); // for the minute
         else           strcat(fmt,"%2d");  // for formats such as YYMMDD
      };
      if ((ordering == T_HMS) | (ordering == T_MS))
         strcat(fmt,sep_fmt); // minute second separator
      if ((ordering == T_HMS) | (ordering == T_MS))
         strcat(fmt,"%2d"); // for the second (will always be two digit)
      switch (ordering)
      {  case T_HMS : sscanf(time_only_str,fmt,&hour,&minute,&second);  break;
         case T_HM  : sscanf(time_only_str,fmt,&hour,&minute);          break;
         case T_MS  : sscanf(time_only_str,fmt,&minute,&second);        break;
         case T_H   : sscanf(time_only_str,fmt,&hour);                  break;
         case T_M   : sscanf(time_only_str,fmt,&minute);                break; // don't think this is a valid time format
         case T_S   : sscanf(time_only_str,fmt,&second);                break; // don't think this is a valid time format
         case T_HS  : sscanf(time_only_str,fmt,&hour,&second);          break; // don't think this is a valid time format
         // The following prints the total number of hours, minutes, or seconds (whole numbers after midnight)
          case T_Hours   : case T_Minutes : case T_Seconds :
            after_midnight = cstr_to_nat32(time_only_str,10); break;
      }
      if (pm) hour += 12;
      nat32 seconds = 0;                                                         //170429
      switch (ordering)
      {  case T_HMS : case T_HM  : case T_MS  : case T_H   : case T_M   : case T_S   : case T_HS  :
               set_HMS((Hour) hour, (Minute) minute, (Second) second);
         break;
         case T_Hours   : seconds = after_midnight * 3600;  break;
         case T_Minutes : seconds = after_midnight * 60;    break;
         case T_Seconds : seconds = after_midnight ;        break;
      }
      set_S(seconds);                                                            //170429
   }
   return get_datetime64();
}
//_set_c_str________________________________________________________2005-04-13_/
//_Time_abstract____________________________________________________2017-04-26_/
} // namespace CORN
