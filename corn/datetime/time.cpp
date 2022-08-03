
#  include <string.h>
#include <fstream>

#  include <time.h>
#  include <stdio.h>
#  ifdef __unix
#    include <stdlib.h>
#  endif
#  include "corn/string/strconv.hpp"
#  include "corn/datetime/time.h"
#  if defined(__MSDOS__) || defined(_WIN64) || defined(_WIN32)
#     include <dos.h>
#  endif
#ifndef compareHPP
#include "corn/math/compare.hpp"
#endif
/*
#if (__BCPLUSPLUS__ >= 0x0550)
# include <C:/program files/borland/cbuilder5/include/time.h>
#endif
*/
#include <stdio.h> 

#undef ispace

namespace CORN {

#if  (__BCPLUSPLUS__ > 0) && (__BCPLUSPLUS__ < 0x0570)
//______________________________________________________________________________
std::ostream&  operator<<(std::ostream &strm, Time& x)
{  strm << x.as_string();                                                        //030108
   return strm;
}
//_1998-01-29___________________________________________________________________
std::istream&  operator>>(std::istream& s, Time & x)
{  std::string buffer1;
   s >> buffer1;
   int hour;
   int minute;
   sscanf(buffer1.c_str(),"%d:%d",&hour,&minute);
   x.set_HMS((CORN::Hour)hour,(CORN::Minute)minute,0);
   return s;
}
//_1999-03-05___________________________________________________________________
#endif
//______________________________________________________________________________
const std::string &Time::append_to_string(std::string &target)             const //140614
{  char t_buf[10];
   CORN::Hour   h = get_hour();
   CORN::Minute m = get_minute();
   CORN::Second s = get_second();
   //140615 target[0] = 0;
   if (format.ordering == T_omit) return target; // Just return the empty string        //991220
   int8_to_cstr((int8)h,t_buf,10);                                          //990824
   bool military_style = ((format.styles & 0x3) == T_military);                         //050312
   if ((h < 10) && military_style)                                               //050312
      target.append("0");                                                        //140614
   target.append(t_buf);

// Warning NYI the various ordering and style options

   char separator_str[2];                                                        //991115
   separator_str[0] =(char)get_separator();                                      //001126
   separator_str[1] = 0;                                                         //001126
   target.append(separator_str);                                                 //991115
   int8_to_cstr((int8)m,t_buf,10);
   if (m < 10)     // Currently minutes and seconds always have leading zeros
   target.append("0");
   target.append(t_buf);
   target.append(separator_str);                                                 //991115
   int8_to_cstr((int8)s,t_buf,10);
   if (s < 10)    // Currently minutes and seconds always have leading zeros
      target.append("0");
   target.append(t_buf);
   return target;
}
//_1999-05-05___________________________________________________________________
Datetime64 Time::set_c_str(const char *time_str)
{
   nat8 ordering  = format.ordering;                                             //141120
   nat8 separator = format.separator;                                            //141120
   nat8 styles    = format.styles;                                               //141120

   if (!time_str || !format.ordering)  // There may not be ordering if this is part of a date time string
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
      // Now trying to do this without Ustring
      // Now we have just the time and we can parse it.
      int hour  =0;  // Must be int for scanf
      int minute=0;
      int second=0;
      nat32 after_midnight = 0;
      bool pm = false;
      if (styles & T_am_pm)                                               //141120_070417
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
      switch (ordering)
      {  case T_HMS : case T_HM  : case T_MS  : case T_H   : case T_M   : case T_S   : case T_HS  :
               set_HMS((Hour) hour, (Minute) minute, (Second) second);
         break;
         case T_Hours   : seconds = after_midnight * 3600;  break;
         case T_Minutes : seconds = after_midnight * 60;    break;
         case T_Seconds : seconds = after_midnight ;        break;
      }
   }
   return get_datetime64();
}
//_2005-04-13___________________________________________________________________
Datetime64 Time::inc_seconds(Seconds more_seconds)
{  seconds += more_seconds;
   CORN::Hours more_days = seconds / 86400;
   seconds = seconds % 86400;
   return seconds / 86400;
}
//_2014-04-27___________________________________________________________________
/*170426
Days Time::plus_seconds(Seconds more_seconds)
{  seconds += more_seconds;
   CORN::Hours more_days = seconds / 86400;
   seconds = seconds % 86400;
   return more_days;
}
//______________________________________________________________________________
*/

#ifdef NYI
#  if (__BCPLUSPLUS__ >= 0x0550)
//______________________________________________________________________________
void set(const TDateTime &delphi_time)
{  double time_fraction = delphi_time - (int)delphi_time;
   seconds = 86400.0 * time_fraction;
}
//_2001-12-03___________________________________________________________________
TDateTime get_delphi_date_time(TDateTime &delphi_time)                     const
{  double time_fraction = (double)seconds / 86400.0;
   TDateTime new_delphi_time(time_fraction);
   return new_delphi_time;
}
//_2001-12-03___________________________________________________________________
#  endif
#endif
//______________________________________________________________________________
float32 CORN_time_zone_hours_offset[] =
{  0.0   // Z (GMT)
,  1.    // A (GMT + 1:00)
,  2.    // B (GMT + 2:00)
,  3.    // C (GMT + 3:00)
,  3.5   // C* (GMT + 3:30)
,  4.    // D (GMT + 4:00)
,  4.5   // D* (GMT + 4:30)
,  5.    // E (GMT + 5:00)
,  5.5   // E* (GMT + 5:30)
,  6.    // F (GMT + 6:00)
,  6.5   // F* (GMT + 6:30)
,  7.    // G (GMT + 7:00)
,  8.    // H (GMT + 8:00)
,  9.    // I (GMT + 9:00)
,  9.5   // I* (GMT + 9:30)
, 10.    // K (GMT + 10:00)
, 10.5   // K* (GMT + 10:30)
, 11.    // L (GMT + 11:00)
, 11.5   // L* (GMT + 11:30)
, 12.    // M (GMT + 12:00)
, 13.    // M* (GMT + 13:00)
,-1.     // N (GMT - 1:00)
,-2.     // O (GMT - 2:00)
,-3.     // P (GMT - 3:00)
,-3.5    // P* (GMT - 3:30)
,-4.     // Q (GMT - 4:00)
,-5.     // R (GMT - 5:00) US/Eastern
,-6.     // S (GMT - 6:00) US/Central
,-7.     // T (GMT - 7:00) US/Mountain
,-8.     // U (GMT - 8:00) US/Pacific
,-8.5    // U* (GMT - 8:30)
,-9.     // V (GMT - 9:00) US/Yukon
,-9.5    // V* (GMT - 9:30)
,-10.    // W (GMT - 10:00) US/Hawaii
,-11.    // X (GMT - 11:00)
,-12.    // Y (GMT - 12:00)</SELECT>
};
//______________________________________________________________________________
Time::Time()
: format() //141120Time_format()
, seconds(0)
{  time_t timer;
   struct tm *tblock;
   timer = time(NULL);  // gets time of day
   tblock = localtime(&timer);// converts date/time to a structure */
   seconds = tblock->tm_sec;
   seconds += tblock->tm_min * 60;
   seconds += tblock->tm_hour * 3600;
}
//______________________________________________________________________________
Time::Time(Datetime64 time64)
{  set_datetime64(time64);
}
//_2003-07-14___________________________________________________________________
Datetime64 Time::set_datetime64(Datetime64 time64)
{  int32 ignore_date = (int32)time64;  // Ignore any date part
   float64 time_only = (float64)time64 - (float64)ignore_date;
   seconds = (Seconds)(time_only * 86400.0);
   return time64;
}
//_2003-07-14___________________________________________________________________
Datetime64 Time::get_datetime64()                                          const
{   // This returns the date, time or date time as a 64 bit float (double)
   return (double)seconds / (double)86400.0;
}
//_2003-01-08___________________________________________________________________
int8 Time::compare_time(const Time &other_time)                            const
{  return (int8)((seconds < (other_time).get_seconds())
   ? -1 : (seconds > ((Time &)other_time).get_seconds()) ? 1 : 0);
}
//_2003-01-08___________________________________________________________________
} // namespace CORN

