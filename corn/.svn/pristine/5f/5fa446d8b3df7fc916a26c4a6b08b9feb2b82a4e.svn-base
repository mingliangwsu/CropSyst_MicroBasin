#include "corn/chronometry/date_A.h"

// I need to move the datetime functions
#include "corn/chronometry/date.c_cpp"
#include "corn/string/strconv.hpp"
#if (defined(__MSDOS__) || defined(__BCPLUSPLUS__))
#   include <dos.h>
//  for date struct (to get the current real date)
#endif
#  include <stdio.h>
#include <assert.h>
#include <iostream>

namespace CORN
{
#include "corn/chronometry/date_const.h"
//______________________________________________________________________________
Date_const_abstract::Date_const_abstract()
: Date_const()
, preferred_format(&ISO_8601_date_format)
{}
//_constructor______________________________________________________2017-04-28_/
bool Date_const_abstract::is_relative()                             affirmation_
{
   //currently presuming dates < 100 are relative, but should have flag
   Year year = get_year();
   return year < 100;
}
//_is_relative______________________________________________________2017-05-23_/
const nat8 *Date_const_abstract::get_month_lengths_in_year(Year year)      const
{
   assert(false); // Roger needs to implement!
   return 0;
}
//_get_month_lengths_in_year________________________________________2017-05-23_/
nat8 Date_const_abstract::get_days_in_month(Year year,Month month)         const
{  return date_get_days_in_month(year,month);
}
//_get_days_in_month________________________________________________2017-07-17_/
Date_interface::Days_of_week Date_const_abstract::day_of_week()            const
{  CORN::Year   yr ;
   CORN::Month  mn ;
   CORN::DOM    dom;
   int16     day ;
   int16     n1 ;
   int16     n2 ;
   gregorian(yr,mn,dom);
   /* Offset from Zeller to local */
   /* --------------------------- */
   #define ZELLER_OFFSET   -1
   /* January or February? */
   /* -------------------- */
   if (mn < 3)
   {
     /* Yes, make these part of last year */
     /* --------------------------------- */
     mn += (Month)12 ;
     yr -= (Year)1 ;
   }
   n1 = (int16)((26 * (mn + 1)) / 10 );
   n2 = (int16) ((125 * (long) yr) / 100) ;
   day = (int16)((dom + n1 + n2 - (yr / 100) + (yr / 400) + ZELLER_OFFSET) % 7);
   day++;
   return((Date_interface::Days_of_week)day);
}
//_day_of_week_________________________________________________________________/
Year Date_const_abstract::get_year()                                       const
{  return((int16)(get_date32() / (int32)1000));
}
//_get_year____________________________________________________________________/
CORN::DOY Date_const_abstract::get_DOY()                                   const
{  CORN::DOY doy = ((int16)(labs(get_date32()) % (int32)1000));
   return doy;
}
//_get_DOY_______________________________________________1999-07-04_1999-02-14_/
CORN::Month Date_const_abstract::get_month()                               const
{  Year    year;
   CORN::Month   month;
   CORN::DOM     DOM;
   gregorian(year,month,DOM);
   return(month);
}
//___________________________________________________________________get_month_/
Week  Date_const_abstract::get_week()                                      const
{  return get_DOM() / 52;
      //< \returns the week in the year
}
//_get_week_________________________________________________________2018-06-26_/
CORN::DOM Date_const_abstract::get_DOM()                                   const
{  Year    year;
   CORN::Month   month;
   CORN::DOM     DOM;
   gregorian(year,month,DOM);
   return(DOM);
}
//_____________________________________________________________________get_DOM_/
void Date_const_abstract::gregorian
(Year &year, CORN::Month &month, CORN::DOM &day)                           const
{  DOY   dayofyear;
   Month m = 1;
   int16 sum_month = 0;
   DOM   dom;
   year = get_year();
   dayofyear = get_DOY();                                                        //990214
   while (((DOY)(sum_month + date_get_days_in_month((Year)abs(year),m)) < dayofyear))//040909
   {  sum_month += date_get_days_in_month((Year)abs(year),m);
      m++;
   }
   dom = (DOM) (dayofyear-sum_month);
   month = m;
   day = dom;
}
//_gregorian________________________________________________________1999-02-14_/
bool Date_const_abstract::is_leap_year(Year year)                   affirmation_
{  return date_is_leap_year(year);
}
//_is_leap_year_____________________________________________________2013-02-22_/
bool Date_const_abstract::is_leap_this_year()                       affirmation_
{  return date_is_leap_year(get_year());
}
//_is_leap_this_year________________________________________________2013-02-25_/
nat16 Date_const_abstract::days_in_year(Year year)                         const
{ return date_days_in_year(year); }
//_days_in_year_____________________________________________________2012-01-08_/
nat16 Date_const_abstract::days_in_this_year()                             const
{ return days_in_year(get_year()); }
//_days_in_this_year______________________________________130222_120108_990214_/
DOM Date_const_abstract::days_in_month()                                   const
{ return date_get_days_in_month(get_year(),get_month());}
//_days_in_month____________________________________________________1999-02-14_/
nat32 Date_const_abstract::days_between
(const Date_const &that_date,bool inclusive)                               const
{
   const Date_const &earlier_date
      = (this->get_date32() > that_date.get_date32())
      ? that_date
      : dynamic_cast<const Date &>(*this);                                       //120109
   const Date_const &later_date                                                  //120109
      = (this->get_date32() > that_date.get_date32())
      ? dynamic_cast<const Date_interface &>(*this)
      :  that_date;

   nat32 sum_days = 0;
   nat16 earlier_DOY = earlier_date.get_DOY();
   nat16   later_DOY =   later_date.get_DOY();
   Year earlier_year = earlier_date.get_year();
   Year   later_year =   later_date.get_year();
   if (earlier_year == later_year)
   {  sum_days += later_DOY - earlier_DOY;
   } else
   {  for (nat16 y = earlier_year + 1; y < later_year; y++)
      {  // Add all the days in the intervening years
         sum_days += days_in_year(y);
      }
      nat16 earlier_days_in_year = days_in_year(earlier_year);
      nat16 days_till_earlier_endofyear  = earlier_days_in_year - earlier_DOY;
      sum_days += days_till_earlier_endofyear/* + 1*/; // always include the last DOY of earlier year
      sum_days += later_DOY;
   }
   sum_days +=  ((int)inclusive);
   return(sum_days);
}
//_days_between________________________________________________________________/
int32 Date_const_abstract::days_to(const Date_const &date2)                const
{  long diff = days_between(date2,false); // not inclusive
   return (get_date32() > date2.get_date32()) ? -diff : diff;
}
//_days_to_____________________________________________________________________/
/*710430 unused
bool Date_abstract::within_period
(const Date_interface &earliest_date , const Date_interface &latest_date) const
{
//   {If earliest and latest date don't have a year, we only consider the DOY}
   bool result = false;
   if ((earliest_date.get_year() == 0) && (latest_date.get_year() == 0 ))
   {  CORN::DOY earliest_DOY = earliest_date.get_DOY();                          //990214
      CORN::DOY latest_DOY   = latest_date.get_DOY();                            //990214
      CORN::DOY curr_DOY     = get_DOY();                                        //990214
      result = (earliest_DOY > latest_DOY) //{I.e. it occurs in the next year}
      ? (curr_DOY > earliest_DOY) || (curr_DOY < latest_DOY)
      : (curr_DOY > earliest_DOY) && (curr_DOY < latest_DOY);
   } else
       result = (get_date32() >= earliest_date.get_date32()) && (get_date32() <= latest_date.get_date32());
   return result;
}
*/
//_within_period____________________________________________________1998-09-24_/
void Date_const_abstract::prefer_date_format(const Date_format *format_) contribution_
{  // Currently don't own format
   preferred_format = format_ ? format_ : &ISO_8601_date_format;
}
//_prefer_date_format_______________________________________________2017-04-28_/
const std::string &Date_const_abstract::append_to_string
(std::string &target
,const Date_format *preferred_format_                                            //180625
,const Time_format *preferred_time_format_unused)                          const //180625
{
/*now auto initialized
   if (!date_phrases_setup)
      date_setup_phrases();
*/
   // Currently we always have format
   const Date_format *format
      = preferred_format_ ? preferred_format_ : preferred_format;
   nat8 ordering_BS   = format->ordering_BS;
   nat8 styles        = format->styles;
   char separator     = format->separator;
   bool DOY_indicator = format->DOY_indicator;
   std::string year_str;
   std::string month_str;
   std::string month_num_str;
   std::string doy_str;
   std::string dom_str;
   std::string sep1_str;
   std::string sep2_str;
   int year = get_year();
   CORN::Month month = 0;
   DOM dom = 0;
   DOY doy = get_DOY() ? get_DOY() : 1;
#ifdef DISABLED
  DOY diy = days_in_year();                                                      //041214

//I need to figure out what condition has caused the doy to be greater than diy.
//This is disabled because the method is const

   if (doy > diy) set_DOY(diy); // This should never happen, but I have seen it. //041214
#endif
   if (!get_date32())                                                            //990421
   {   target.append("Date omitted");                                            //990421
   } // If not date, return 0

//NYI Not, I how have the ordering sequence using the new bit sequence
// it should be easier to compose the text_str with this
   if ((ordering_BS != D_YD) && (ordering_BS != (D_DY)))
   { Year  year16=0;

     CORN::DOM   dom8=0;
     gregorian(year16,month,dom8);
     year = year16;
     dom = dom8;
   }
   if   (styles & D_YY) append_int16_to_string((year%100),year_str,10,2,'0');
   else if (styles & D_YYY)
      { year_str+="'";  append_int16_to_string((year%100),year_str,10,2,'0'); }
   else                 append_int16_to_string(year      ,year_str,10,4,'0');
   char leading_char
      = (styles & D_lead_space)  ? ' '
      : (styles & D_lead_zero)   ? '0'
      : 0;
   append_nat8_to_string(month,month_num_str ,10,2,leading_char);
   append_nat8_to_string(dom  ,dom_str       ,10,2,leading_char);
   append_int16_to_string(doy ,doy_str       ,10,3,leading_char);

   if (styles & D_Mmm)        month_str.assign(date_month_abbrevs[month]);
   else if (styles & D_Mmmm)  month_str.assign(date_month_names[month]);
   else                       month_str.assign(month_num_str);
   if (separator == ',')
   {  sep1_str.assign(" ");
      sep2_str.assign(", ");
   } else
   { sep1_str += separator;
     sep2_str += separator;
   }
   if (get_date32() == 0)
   { year_str = "-";
     month_str[0] = '-'; month_str[1]= 0;
     dom_str[0]   = '-'; dom_str[1]  = 0;
     doy_str[0]   = '-'; doy_str[1]  = 0;
     return target;
   }
//NYI Not, I how have the ordering sequence using the new bit sequence
// it should be easier to compose the text_str with this
   switch (ordering_BS)
   {
     default :                                                                   //141120
     case D_YMD : target.append(year_str); target.append(sep1_str);target.append(month_str);target.append(sep2_str);target.append(dom_str)  ; break;
     case D_YDM : target.append(year_str); target.append(sep1_str);target.append(dom_str)  ;target.append(sep2_str);target.append(month_str); break;
     case D_MYD : target.append(month_str);target.append(sep1_str);target.append(year_str) ;target.append(sep2_str);target.append(dom_str)  ; break;
     case D_MDY : target.append(month_str);target.append(sep1_str);target.append(dom_str);  target.append(sep2_str);target.append(year_str) ; break;
     case D_DYM : target.append(dom_str);  target.append(sep1_str);target.append(year_str); target.append(sep2_str);target.append(month_str); break;
     case D_DMY : target.append(dom_str);  target.append(sep1_str);target.append(month_str);target.append(sep2_str);target.append(year_str); break;
     case D_MD  : target.append(month_str);target.append(sep1_str);target.append(dom_str);   break;
     case D_DM  : target.append(dom_str);  target.append(sep1_str);target.append(month_str); break;
     case D_YD  : target.append(year_str); target.append(sep1_str);target.append(doy_str);   break;
     case D_DY  : target.append(doy_str);  target.append(sep1_str);target.append(year_str);  break;
     case D_Y  :  target.append(year_str); break;
   }
   if (DOY_indicator)
   {
      target += "(";
      append_int16_to_string(doy,target,10,3,'0');
      target += ")";
   }
   return target;
}
//_append_to_string_____________________________________2017-04-29__2014-06-15_/

//______________________________________________________________________________
Date_abstract::Date_abstract()
: Date_interface()                                                               //170814
{}
//_constructor______________________________________________________2017-05-25_/
datetime64  Date_abstract::inc_day()                               modification_
{
   Year year = get_year();
   long next_date = get_date32() +1;
   int16 _days_in_year = days_in_year(year);                                     //170530brc
   datetime64 result =
      (((int)(next_date % (long)1000)) > (int)(year ? _days_in_year : 365))
      ? set_YD((Year)(year ? year+1 : 1),(DOY)1)
      : set_date32(next_date);
   return result;
}
//_inc_day__________________________________________________________2017-05-23_/
datetime64 Date_abstract::dec_day()
{  datetime64 result=0;
   if (get_DOY() == 1)
        result = set_YD((Year)(get_year()-1)
        ,(days_in_year((Year)(get_year()-1))));
   else
   {  date32 prev_date = get_date32();
      prev_date -= 1;
      result = set_date32(prev_date);
   }
   return result;
}
//_dec_day__________________________________________________________2017-05-23_/
datetime64 Date_abstract::inc_days(int32 days)                     modification_
{  datetime64 result = 0;
   for (int i = 1; i <= days; i++)
      result = inc_day();
#ifdef temp_disabled
not working may want a faster increment such as this
   if (offset < 0)
      dec_day((int32)abs(offset));
   else
   {
     Year year = get_year();
     CORN::DOY  doy = get_DOY();
     while (offset)
     { nat16 days = days_in_year(year);
       if (offset + (int)doy <= days)
       {  doy += (DOY)offset;
          offset = 0;
       }
       else
       { if (offset == 1)
              offset = 0;
         else offset -= days - doy;
         year++;
         doy = 1;
       }
     }
     result = set_YD(year,doy);
   }
#endif
   return result;
}
//_inc_days_________________________________________________________2017-05-23_/
datetime64 Date_abstract::dec_days(int32 days)                     modification_
{  datetime64 result = 0;
   for (int i = 1; i <= days; i++)
      result = dec_day();
   return result;
}
//_dec_days_________________________________________________________2017-06-02_/
datetime64 Date_abstract::set_now()
{
   datetime64 result=0;
#if (defined(__MSDOS__) || defined(__BCPLUSPLUS__))
   // This is available for BC++ builder upto atlease RS2010
   // but no long erin MSC //100928_
  struct date date_struct;
  getdate(&date_struct);
  result = set_YMD((Year)date_struct.da_year,(CORN::Month)date_struct.da_mon,(CORN::DOM)date_struct.da_day);
#endif
#if defined __unix || defined(_MSC_VER)
     tm *time_struct;
     time_t timer;
     time(&timer);
     time_struct = localtime(&timer);
     result = set_YD(1900+time_struct->tm_year,time_struct->tm_yday + 1);
#endif
   return result;
}
//_set_now__________________________________________________________2003-07-15_/
datetime64 Date_abstract::set_c_str
(const char        *date_str
,const Date_format *from_format)
{  datetime64 result=0;
   set_YD((Year)0,(CORN::DOY)0); // initialize

   const Date_format *format = from_format ? from_format
      : preferred_format;
    nat8 ordering_BS   = format->ordering_BS;                                      //141120
    nat8 styles        = format->styles;                                           //141120
    char separator     = format->separator;                                        //141120
    bool DOY_indicator = format->DOY_indicator;                                    //141120

   if (!date_str || ordering_BS == D_omit)
       return get_datetime64();
   int year = 0; // must be int for scanf in both 16 and 32 bit
   int month = 0;  // must be int for scanf
   int day = 0;   // must be int for scanf
   char sep1_fmt[5];
   char sep2_fmt[5];
   char fmt[50];  fmt[0] = 0;

//   if ((separator != 0) && (!(styles & D_lead_space)) && (!(styles &D_M)))
   if (((ordering_BS  == D_unknown_ordering) && (styles == D_unknown_style)) || (ordering_BS == D_YD))
   {  bool YYYYDOY_format = true;
      for (int16 ci = 0; ci < (int16)strlen(date_str); ci++)
      {   bool isdig =
          ((date_str[ci] >= 48) && (date_str[ci] <= 57));
       if (!isdig)
          YYYYDOY_format = false;
      }
      if (YYYYDOY_format)
      {  set_date32(atol(date_str));
         return get_datetime64();
      }
   }
   if ((separator == ',') || strchr(date_str,','))
   {  strcpy(sep1_fmt," ");
      strcpy(sep2_fmt,", ");
   }
   else
   { sep1_fmt[0] = separator;
     sep2_fmt[0] = separator;
      sep1_fmt[1] = 0;
      sep2_fmt[1] = 0;
   }
   char year_format[10]; year_format[0]  = 0;
   char month_number_format[10];month_number_format[0] = 0;
   char month_string_format[10];month_string_format[0] = 0;
   char month_format[10];month_format[0] = 0;
   char dom_format[10];  dom_format[0]   = 0;
   char doy_format[10];  doy_format[0]   = 0;
   if      (styles & D_YY)       strcpy(year_format,"%2d");  // Year always has leading 0
   else if (styles & D_YYY)      strcpy(year_format,"%3d");
   else                          strcpy(year_format,"%4d");
   if      (styles & D_lead_zero)
   {  strcpy (month_number_format,"%2d");
      strcpy (dom_format,"%2d");
      strcpy (doy_format,"%3d");
   }else
   {  strcpy (month_number_format,"%d");
      strcpy (dom_format,"%d");
      strcpy (doy_format,"%d");
   }
   if       (styles & D_Mmm)   strcpy(month_string_format,"%3s");
   if       (styles & D_Mmmm)  strcpy(month_string_format,"%s");  // Note this presumes a separator follows the month
   strcpy(month_format,(styles & D_M)?  month_number_format:  month_string_format);
   switch (ordering_BS)
   {  case D_YMD : strcat(fmt,year_format); strcat(fmt,sep1_fmt); strcat(fmt,month_format); strcat(fmt,sep2_fmt); strcat(fmt,dom_format);  break;
      case D_YDM : strcat(fmt,year_format); strcat(fmt,sep1_fmt); strcat(fmt,dom_format);   strcat(fmt,sep2_fmt); strcat(fmt,month_format);break;
      case D_MYD : strcat(fmt,month_format);strcat(fmt,sep1_fmt); strcat(fmt,year_format);  strcat(fmt,sep2_fmt); strcat(fmt,dom_format);  break;
      case D_MDY : strcat(fmt,month_format);strcat(fmt,sep1_fmt); strcat(fmt,dom_format);   strcat(fmt,sep2_fmt); strcat(fmt,year_format); break;
      case D_DYM : strcat(fmt,dom_format);  strcat(fmt,sep1_fmt); strcat(fmt,year_format);  strcat(fmt,sep2_fmt); strcat(fmt,month_format);break;
      case D_DMY : strcat(fmt,dom_format);  strcat(fmt,sep1_fmt); strcat(fmt,month_format); strcat(fmt,sep2_fmt); strcat(fmt,year_format); break;
      case D_MD  : strcat(fmt,month_format);strcat(fmt,sep1_fmt); strcat(fmt,dom_format);    break;
      case D_DM  : strcat(fmt,dom_format);  strcat(fmt,sep1_fmt); strcat(fmt,month_format);  break;
      case D_YD  : strcat(fmt,year_format); strcat(fmt,sep1_fmt); strcat(fmt,doy_format);    break;
      case D_DY  : strcat(fmt,doy_format);  strcat(fmt,sep1_fmt); strcat(fmt,year_format);   break;
   }
   if (styles & D_M)
   {  switch (ordering_BS)
      {  case D_YMD : sscanf(date_str,fmt,&year,&month,&day); break;
         case D_YDM : sscanf(date_str,fmt,&year,&day,&month); break;
         case D_MYD : sscanf(date_str,fmt,&month,&year,&day); break;
         case D_MDY : sscanf(date_str,fmt,&month,&day,&year); break;
         case D_DYM : sscanf(date_str,fmt,&day,&year,&month); break;
         case D_DMY : sscanf(date_str,fmt,&day,&month,&year); break;
         case D_MD  : sscanf(date_str,fmt,&month,&day); break;
         case D_DM  : sscanf(date_str,fmt,&day,&month); break;
         case D_YD  : sscanf(date_str,fmt,&year,&day); break;
         case D_DY  : sscanf(date_str,fmt,&day,&year); break;
      }
   } else
   {  char month_str[20];
     switch (ordering_BS)
     { case D_YMD : sscanf(date_str,fmt,&year,month_str,&day); break;
       case D_YDM : sscanf(date_str,fmt,&year,&day,month_str); break;
       case D_MYD : sscanf(date_str,fmt,month_str,&year,&day); break;
       case D_MDY : sscanf(date_str,fmt,month_str,&day,&year); break;
       case D_DYM : sscanf(date_str,fmt,&day,&year,month_str); break;
       case D_DMY : sscanf(date_str,fmt,&day,month_str,&year); break;
       case D_MD  : sscanf(date_str,fmt,month_str,&day); break;
       case D_DM  : sscanf(date_str,fmt,&day,month_str); break;
     }
     int8 i;
     if (styles & D_Mmm)
     {  if (stricmp(month_str,"sep") == 0) month = 9;
        else
          for (i = 1; i<=12 && !month ;i++)                                      //180625
          {
            // If this crashes, the date_month_abbrevs need to be setup
            // In main() call
             if (stricmp(month_str,date_month_abbrevs[i]) == 0) month = i;
          }
     } else
        for (i = 1; i<=12 && !month;i++)                                         //180625
           if (stricmp(month_str,date_month_names[i]) == 0) month = i;
  }
  if      (styles & D_YY)   year += 1900;
  else if (styles & D_YYY)  year += 1000;
  switch (ordering_BS)
  {
    case D_YMD : case D_YDM : case D_MYD : case D_MDY :
    case D_DYM : case D_DMY : case D_MD  : case D_DM  :
       result = set_YMD((Year)year,(CORN::Month)month,(CORN::DOM)day);           //980206
    break;
    default :
       result = set_YD((Year)year,(CORN::DOY)day);                               //980206
    break;
  }
  return result;
}
//_set_c_str______________________________________________________________1998_/
datetime64 Date_abstract::set_w_str
(const wchar_t *date_wstr
,const Date_format *from_format)                                    assignation_
{  std::string date_str;
   CORN::UnicodeZ_to_string(date_wstr,date_str);
   return set_c_str(date_str.c_str(),from_format);
}
//_set_w_str________________________________________________________2018-02-18_/
datetime64 Date_abstract::set_YMD(Year year,Month month,DOM day)
{  CORN::DOY     dayofyear;
   CORN::Month   m;
   dayofyear = day;
   for (m = 1 ; m < month ; m++)
      dayofyear += (DOY)date_get_days_in_month(year,m);
   date32 date_num = CORN_date_date(abs(year),dayofyear);                        //170428_990606
   if (year < 0) date_num = -date_num;                                           //990606
   return set_date32(date_num);                                                  //170428_030714
}
//_set_YMD__________________________________________________________1999-02-14_/
datetime64 Date_abstract::set_month(Month month)
{  Year year;
   Month old_month;
   DOM   dom;
   gregorian( year,  old_month, dom);
   return set_YMD(year,month,dom);
}
//_set_month________________________________________________________2005-04-06_/
datetime64 Date_abstract::set_DOM(DOM dom)
{  Year year;
   Month month;
   DOM   old_dom;
   gregorian( year,  month, old_dom);
   return set_YMD(year,month,dom);
}
//_set_DOM__________________________________________________________2005-04-06_/
datetime64 Date_abstract::inc_years(int16 offset)
  // Adds offset years to the date.
  //   If offset is negative, offset years are subtracted
{  Year year = get_year();
   year += offset;
   set_year(year);
   return get_datetime64();                                                      //030714
}
//_inc_year_________________________________________________________1997-09-09_/
datetime64 Date_abstract::dec_years(int16 offset)
  // Adds offset years to the date.
  //   If offset is negative, offset years are subtracted
{ Year year = get_year();
  year -= offset;
  return set_year(year);
}
//_dec_year_________________________________________________________1997-09-09_/
datetime64 Date_abstract::inc_months(int16 offset)
  // Adds offset years to the date.
  //   If offset is negative, offset years are subtracted
{  Year    year;
   CORN::Month   month;                                                          //990214
   CORN::DOM     DOM;                                                            //990214
   gregorian(year,month,DOM);
   int16 run_month = (int16)(month + offset);                                    //990224
   year += (Year)(run_month/ 12);                                                //990224
   month = (CORN::Month)(run_month % 12);                                        //990224
   return set_YMD(year,month,DOM);
}
//_inc_month________________________________________________________1997-09-09_/
datetime64 Date_abstract::dec_months(int16 offset)
{  // Subtracts offset years to the date.
   //   If offset is negative, offset years are added
   CORN::Year    year;
   CORN::Month   month;                                                           //990214
   CORN::DOM     DOM;                                                             //990214
   gregorian(year,month,DOM);
   int16 run_month = (int16)(month - offset);                                     //990224
   year -= (int16)(run_month / 12);                                               //990224
   month = (CORN::Month)(abs(run_month) % offset);                                //990224
   return set_YMD(year,month,DOM);
}
//_dec_month________________________________________________________1997-09-09_/
datetime64 Date_abstract::clear()                                   assignation_
{ return set_datetime64(0); }
//_clear_______________________________________________________________________/
} // namespace CORN
