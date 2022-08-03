/* date.cpp    C++ version of date library

   Pascal and C versions also available

   Written by Roger Nelson
   Comments, suggestions, questions and bug reports can be sent to:

       Biological Systems Engr. Dept.
       Washington State University
       Pullman, WA 99164-6120

		 rnelson@mail.wsu.edu

       Phone: (509)335-1100
       FAX  : (509)335-2722
*/

#include <assert.h>

#  include "corn/datetime/date.hpp"

#  include "corn/string/strconv.hpp"
#  include <stdlib.h>
         // stdlib for labs
#  include <string.h>
#  include <math.h>  // Only for abs
// The following includes are OS specific for computer date
#  if (defined(__MSDOS__) || defined(__BCPLUSPLUS__))
#     include <dos.h>
#  endif
#  ifdef _MSC_VER
#     include <time.h>
#  endif
#  ifdef __unix
#  include <time.h>
#  endif

#  include <stdio.h>
#include "corn/datetime/date.c_cpp"

namespace CORN {
//______________________________________________________________________________
bool        date_phrases_setup = false;
const char *T_date_Day            = 0;
const char *T_date_Days           = 0;
const char *T_date_Day_of_month   = 0;
const char *T_date_Day_of_year    = 0;
const char *T_date_Month          = 0;
const char *T_date_Year           = 0;
const char *T_date_Years          = 0;
const char *T_date_Date           = 0;
const char *T_date_Sunday         = 0;
const char *T_date_Monday         = 0;
const char *T_date_Tuesday        = 0;
const char *T_date_Wednesday      = 0;
const char *T_date_Thursday       = 0;
const char *T_date_Friday         = 0;
const char *T_date_Saturday       = 0;
//______________________________________________________________________________
Date::Date()
: format(CORN_date_DEFAULT_ORDERING,CORN_date_DEFAULT_STYLES,CORN_date_DEFAULT_SEPARATOR,false)
{  set_now();
}
//_2003-07-13___________________________________________________________________
Date::Date
(const int32 new_date
,nat16 _ordering_BS
,nat16 _styles
,nat8 _separator
,bool  _DOY_indicator)
: format(_ordering_BS,_styles,_separator,_DOY_indicator)
, date_num(new_date)
{}
//_2003-07-13___________________________________________________________________
Date::Date
(const Date &new_date
,nat16 _ordering_BS
,nat16 _styles
,nat8  _separator
,bool   _DOY_indicator)
: format(_ordering_BS,_styles,_separator,_DOY_indicator)                         //030713
, date_num(new_date.date_num)
{}
//______________________________________________________________________________
Date::Date
(Year year
,CORN::DOY doy
,nat16 _ordering_BS
,nat16 _styles
,nat8 _separator
,bool  _DOY_indicator)
: format(_ordering_BS,_styles,_separator,_DOY_indicator)                         //030713
{  date_num = CORN_date_date(year,doy);
}
//_1999-02-14___________________________________________________________________
Date::Date
(const Year year
,const CORN::Month month
,const CORN::DOM   day
,nat16 _ordering_BS
,nat16 _styles
,nat8 _separator
,bool  _DOY_indicator)
: format(_ordering_BS,_styles,_separator,_DOY_indicator)                         //030713
{  set_YMD(year,month,day);                                                      //030713
}
//______________________________________________________________________________
Datetime64 Date::set_YMD(Year year,Month month,DOM day)
{  CORN::DOY     dayofyear;
   CORN::Month   m;
   dayofyear = day;
   for (m = 1 ; m < month ; m++)
      dayofyear += (DOY)date_get_days_in_month(year,m);
   date_num = CORN_date_date(abs(year),dayofyear);                               //990606
   if (year < 0) date_num = -date_num;                                           //990606
   return get_datetime64();                                                      //030714
}
//_1999-02-14__________________________________________________________set_YMD_/
Datetime64 Date::set_YD(Year year,CORN::DOY doy)
{  date_num = CORN_date_date(year,doy);
   return get_datetime64();
}
//______________________________________________________________________________
#ifdef NYI
#  if (__BCPLUSPLUS__ >= 0x0550)
void Date::set(const TDateTime *new_date)
{  int days_since_1899365 = (int)(*new_date);
   set(1899365);
   add(days_since_1899365);
}
//_2001-12-03___________________________________________________________________
TDateTime &Date::get_delphi_date_time(TDateTime &delphi_date_time)         const
{  Date base_1899365(1899365);
   int32 days_since_1899365 = days_between(base_1899365,true);
   if (*this < base_1899365)
       days_since_1899365 = -days_since_1899365;
   TDateTime new_delphi_date_time(days_since_1899365);
   delphi_date_time = new_delphi_date_time;
   return delphi_date_time;
}
//_2001-12-03_____________________________________________get_delphi_date_time_/
#endif
#endif
//______________________________________________________________________________
void Date::set_format                                                            //141120
(nat16   _ordering_BS                                                            //050412
,nat16   _styles
,nat8   _separator                                                               //020127
,bool    _DOY_indicator) const                                                   //020507
{ // These are mutable
   format.ordering_BS  = _ordering_BS;                                           //050412
   format.styles       = _styles;
   format.separator    = _separator;
   format.DOY_indicator= _DOY_indicator;                                         //020507
}
//______________________________________________________________________________
/* Returns 1 for Sunday, 2 Monday etc... */
Date::Days_of_week Date::day_of_week()                                     const
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
   day = (int16)((dom + n1 + n2 - (yr / 100) + (yr / 400) + ZELLER_OFFSET) % 7) ;
   day++;
   return((Date::Days_of_week)day);
}
//______________________________________________________________________________
int32 Date::get_days()                                                     const
{ return days_between((const CORN::Date_time &)Date((Year)0,(DOY)0),false); }
//D           Returns the number of days. (Useful after subtracting dates.)
//_1999-05-06___________________________________________________________________
Year Date::get_year()                                                      const
{  return((int16)(date_num / (int32)1000));
}
//______________________________________________________________________________
CORN::DOY Date::get_DOY()                                                  const
{  CORN::DOY doy = ((int16)(labs(date_num) % (int32)1000));                      //990704
   return doy;
}
//_1999-02-14___________________________________________________________________
CORN::Month Date::get_month()                                              const
{  Year    year;
   CORN::Month   month;
   CORN::DOM     DOM;
   gregorian(year,month,DOM);
   return(month);
}
//______________________________________________________________________________
CORN::DOM Date::get_DOM()                                                  const
{  Year    year;
   CORN::Month   month;
   CORN::DOM     DOM;
   gregorian(year,month,DOM);
   return(DOM);
}
//______________________________________________________________________________
void Date::gregorian(Year &year, CORN::Month &month, CORN::DOM &day)       const
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
//_1999-02-14___________________________________________________________________
const std::string &Date::append_to_string(std::string &target)             const
{  if (!date_phrases_setup)                                                      //000929
      date_setup_phrases();
   nat8 ordering_BS   = format.ordering_BS;                                      //141120
   nat8 styles        = format.styles;                                           //141120
   char separator     = format.separator;                                        //141120
   bool DOY_indicator = format.DOY_indicator;                                    //141120
   char year_str[10];
   char month_str[30];
   char month_num_str[10];
   char doy_str[10];
   char dom_str[10];
   char sep1_str[5];
   char sep2_str[5];
   int year = get_year(); //must be int for printf to work both in 16 and 32 bit //971208
   int month = 0;  // must be int for printf to work both in 16 and 32 bit       //971208
   int dom = 0;    // must be int for printf to work both in 16 and 32 bit       //971208
   int doy = date_num? get_DOY() : 1;    // must be int for printf to work both in 16 and 32 bit //031010
#ifdef DISABLED
  DOY diy = days_in_year();                                                      //041214

//I need to figure out what condition has caused the doy to be greater than diy.
//This is disabled because the method is const

   if (doy > diy) set_DOY(diy); // This should never happen, but I have seen it. //041214
#endif
   if (!date_num)                                                                //990421
   {   target.append("Date omitted");                                            //990421
   } // If not date, return 0

//NYI Not, I how have the ordering sequence using the new bit sequence
// it should be easier to compose the text_str with this
   if ((ordering_BS != D_YD) && (ordering_BS != (D_DY)))
   { Year  year16=0;
     CORN::Month month8=0;
     CORN::DOM   dom8=0;
     gregorian(year16,month8,dom8);
     year = year16;
     month = month8;
     dom = dom8;
   }
   if      (styles & D_YY)   sprintf(year_str,"%02d",(year %100));
   else if (styles & D_YYY)  sprintf(year_str,"'%02d",(year%100));
   else          /* D_YYYY*/ sprintf(year_str,"%04d",year);
   static char lead_space_2[] = "%2d";
   static char lead_zero_2[]  = "%02d";
   static char lead_space_3[] = "%3d";
   static char lead_zero_3[]  = "%03d";
   static char lead_none[]  = "%d";
   char *leading_style_2 = lead_none;
   char *leading_style_3 = lead_none;
   if (styles & D_lead_space)
   { leading_style_2 = lead_space_2;
     leading_style_3 = lead_space_3;
   }
   else if (styles & D_lead_zero)
   { leading_style_2 = lead_zero_2;
     leading_style_3 = lead_zero_3;
   }
   else //(_styles & D_lead_none)
   { leading_style_2 = lead_none;
     leading_style_3 = lead_none;
   }
   sprintf(month_num_str,leading_style_2,month);
   sprintf(dom_str,leading_style_2,dom);
   sprintf(doy_str,leading_style_3,doy);
   if (styles & D_Mmm)
     sprintf(month_str,"%s",date_month_abbrevs[month]);
   else if (styles & D_Mmmm)
     sprintf(month_str,"%s",date_month_names[month]);
   else
      strcpy(month_str,month_num_str);
   if (separator == ',')
   {  strcpy(sep1_str," ");
      strcpy(sep2_str,", ");
   } else
   { sep1_str[0] = separator;
     sep2_str[0] = separator;
     sep1_str[1] = 0;
     sep2_str[1] = 0;
   }
   if (date_num == 0)
   { year_str[0]  = '-'; year_str[1] = 0;
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
   {  char paren_doy_str[10];
      sprintf(paren_doy_str,"(%03d)",doy);
      target.append(paren_doy_str);
   }
   return target;
}
//_2014-06-15___________________________________________________________________
/*140615 replaced by append_to_string
const char *Date::text_str(char *result)                                   const
{  if (!date_phrases_setup)                                                      //000929
      date_setup_phrases();
   char year_str[10];
   char month_str[30];
   char month_num_str[10];
   char doy_str[10];
   char dom_str[10];
   char sep1_str[5];
   char sep2_str[5];
   int year = get_year(); //must be int for printf to work both in 16 and 32 bit //971208
   int month = 0;  // must be int for printf to work both in 16 and 32 bit       //971208
   int dom = 0;    // must be int for printf to work both in 16 and 32 bit       //971208
   int doy = date_num? get_DOY() : 1;    // must be int for printf to work both in 16 and 32 bit //031010
#ifdef DISABLED
  DOY diy = days_in_year();                                                      //041214

//I need to figure out what condition has caused the doy to be greater than diy.
//This is disabled because the method is const

   if (doy > diy) set_DOY(diy); // This should never happen, but I have seen it. //041214
#endif
   if (ordering_BS == D_omit)                                                    //991220
       result[0] = 0; // Date is not to be printed                               //991220
   if (!date_num)                                                                //990421
   {   strcpy(result,"Date omitted");                                            //990421
   } // If not date, return 0

//NYI Not, I how have the ordering sequence using the new bit sequence
// it should be easier to compose the text_str with this
   if ((ordering_BS != D_YD) && (ordering_BS != (D_DY)))                         //041214
   { Year  year16=0;                                                             //971208
     CORN::Month month8=0;                                                       //990216
     CORN::DOM   dom8=0;                                                         //990216
     gregorian(year16,month8,dom8);
     year = year16;                                                              //971208
     month = month8;                                                             //971208
     dom = dom8;                                                                 //971208
   }
   if      (styles & D_YY)   sprintf(year_str,"%02d",(year %100));
   else if (styles & D_YYY)  sprintf(year_str,"'%02d",(year%100));
   else             D_YYYY   sprintf(year_str,"%04d",year); // D_YYYY
   static char lead_space_2[] = "%2d";                                           //010917
   static char lead_zero_2[]  = "%02d";
   static char lead_space_3[] = "%3d";
   static char lead_zero_3[]  = "%03d";
   static char lead_none[]  = "%d";
   char *leading_style_2 = lead_none;
   char *leading_style_3 = lead_none;
   if (styles & D_lead_space)
   { leading_style_2 = lead_space_2;
     leading_style_3 = lead_space_3;
   }
   else if (styles & D_lead_zero)
   { leading_style_2 = lead_zero_2;
     leading_style_3 = lead_zero_3;
   }
   else //(_styles & D_lead_none)
   { leading_style_2 = lead_none;
     leading_style_3 = lead_none;
   }
   sprintf(month_num_str,leading_style_2,month);
   sprintf(dom_str,leading_style_2,dom);
   sprintf(doy_str,leading_style_3,doy);
   if (styles & D_Mmm)
     sprintf(month_str,"%s",date_month_abbrevs[month]);
   else if (styles & D_Mmmm)
     sprintf(month_str,"%s",date_month_names[month]);
   else
      strcpy(month_str,month_num_str);
   if (separator == ',')
   {  strcpy(sep1_str," ");
      strcpy(sep2_str,", ");
   } else
   { sep1_str[0] = separator;
     sep2_str[0] = separator;
     sep1_str[1] = 0;
     sep2_str[1] = 0;
   }
   if (date_num == 0)
   { year_str[0]  = '-'; year_str[1] = 0;
     month_str[0] = '-'; month_str[1]= 0;
     dom_str[0]   = '-'; dom_str[1]  = 0;
     doy_str[0]   = '-'; doy_str[1]  = 0;
     return result;
   }
//NYI Not, I how have the ordering sequence using the new bit sequence
// it should be easier to compose the text_str with this
   switch (ordering_BS)
   {
     case D_YMD : sprintf(result,"%s%s%s%s%s",year_str,sep1_str,month_str,sep2_str,dom_str); break;
     case D_YDM : sprintf(result,"%s%s%s%s%s",year_str,sep1_str,dom_str,sep2_str,month_str); break;
     case D_MYD : sprintf(result,"%s%s%s%s%s",month_str,sep1_str,year_str,sep2_str,dom_str); break;
     case D_MDY : sprintf(result,"%s%s%s%s%s",month_str,sep1_str,dom_str,sep2_str,year_str); break;
     case D_DYM : sprintf(result,"%s%s%s%s%s",dom_str,sep1_str,year_str,sep2_str,month_str); break;
     case D_DMY : sprintf(result,"%s%s%s%s%s",dom_str,sep1_str,month_str,sep2_str,year_str); break;
     case D_MD  : sprintf(result,"%s%s%s",month_str,sep1_str,dom_str); break;
     case D_DM  : sprintf(result,"%s%s%s",dom_str,sep1_str,month_str); break;
     case D_YD  : sprintf(result,"%s%s%s",year_str,sep1_str,doy_str); break;
     case D_DY  : sprintf(result,"%s%s%s",doy_str,sep1_str,year_str); break;
     case D_Y  :  sprintf(result,"%s",year_str); break;
   }
   if (DOY_indicator)                                                             //020507
   {  char paren_doy_str[10];
      sprintf(paren_doy_str,"(%03d)",doy);
      strcat(result,paren_doy_str);
   }
   return(result);
}
*/
//______________________________________________________________________________
#if (__BCPLUSPLUS__ > 0) && (__BCPLUSPLUS__ < 0x0570)
//070305 BDS2006 is doesn't like <iostream>
//090309 This is also not working with GC__
STD_NS istream  &  operator>>(STD_NS istream& s, Date &x)
{  std::string buffer1;                                                          //131115
   s >> buffer1;                                                                 //131115
   if (buffer1.length())  //string was read
   {  if (buffer1[buffer1.length()-1] == x.format.get_separator())  // There may be a leading space
      {                                       // so we'll need to fix it up.
         std::string buffer2;                                                    //131115
         s >> buffer2;                                                           //131115
         buffer1.append(buffer2);
      }
      x.set_c_str(buffer1.c_str());
   }
   return s;
}
//_2007-02-09___________________________________________________________________
std::ostream&  operator<<(std::ostream& s, Date& x)
{  std::string buffer;
   x.append_to_string(buffer);
   s << buffer;
   return s;
}
//_2007-02-09___________________________________________________________________
#endif
nat32 Date::days_between(
//NYI const Date &other
 const Date_time &that_date
,bool inclusive) const
{
//NYI    const Date &earlier_date = (this->get_date32() > other.get_date32()) ? other : dynamic_cast<const Date &>(*this);                                //120109
//NYI    const Date &later_date   = (this->get_date32() > other.get_date32()) ? dynamic_cast<const Date &>(*this) :  other;                                //120109

   const Date_time &earlier_date = (this->get_date32() > that_date.get_date32()) ? that_date : dynamic_cast<const Date_time &>(*this);                                //120109
   const Date_time &later_date = (this->get_date32() > that_date.get_date32()) ? dynamic_cast<const Date_time &>(*this) :  that_date;                                //120109


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
//______________________________________________________________________________
/*170430 unused
bool Date::within_period(const Date &earliest_date , const Date &latest_date) const
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
       result = (get() >= earliest_date.get()) && (get() <= latest_date.get());
   return result;
}
*/
//_1998-09-24___________________________________________________________________
#ifdef OLD_DATE
int32 Date::days_to(const Date &date2)                                     const
{  long diff = days_between(date2,false); // not inclusive
   return (date_num > date2.date_num) ? -diff : diff;
}
#else
int32 Date::days_to(const Date_const_interface &date2)                     const
{  long diff = days_between(date2,false); // not inclusive
   return (get_date32() > date2.get_date32()) ? -diff : diff;
}
#endif
//______________________________________________________________________________
Datetime64 Date::inc()
{  Year year = get_year();
   long next_date = date_num +1;
   nat16 _days_in_year = days_in_year(year);
   if (((int)(next_date % (long)1000)) > (int)(year ? _days_in_year : 365))
      set_YD((Year)(year ? year+1 : 1),(DOY)1);
   else
      date_num = next_date;
   return get_datetime64();
}
//______________________________________________________________________________
Datetime64 Date::dec()
{  if (get_DOY() == 1)
        set_YD((Year)(get_year()-1)
        ,(days_in_year((Year)(get_year()-1))));                                  //120108
   else date_num -= 1;
   return get_datetime64();
}
//______________________________________________________________________________
Datetime64 Date::inc_day(int32 offset)
{  for (int i = 1; i <= offset; i++)
      inc();
#ifdef temp_disabled
not working

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
     set_YD(year,doy);
   }
#endif
   return get_datetime64();
}
//______________________________________________________________________________
Datetime64 Date::dec_day(int32 offset)
{  if (offset < 0)
      inc_day((int32)abs(offset));
   else
   { Year year = get_year();
     DOY  doy = get_DOY();                                                       //990214
     while (offset)
     { if (offset < (int32)doy)
       {  doy -= (DOY)offset;
          offset = 0;
       } else
       { year --;
         offset -= (int32)doy;
         doy = days_in_year(year);
       }
     }
     set_YD(year,doy);
   }
   return get_datetime64();                                                      //030714
}
//_____________________________________________________________________dec_day_/
Datetime64 Date::inc_year(int16 offset)
  // Adds offset years to the date.
  //   If offset is negative, offset years are subtracted
{ Year year = get_year();
  year += offset;
  set_year(year);
   return get_datetime64();                                                      //030714
}
//_1997-09-09_________________________________________________________inc_year_/
Datetime64 Date::dec_year(int16 offset)
  // Adds offset years to the date.
  //   If offset is negative, offset years are subtracted
{ Year year = get_year();
  year -= offset;
  set_year(year);
   return get_datetime64();                                                      //030714
}
//_1997-09-09_________________________________________________________dec_year_/
Datetime64 Date::set_month(Month month)
{  Year year;
   Month old_month;
   DOM   dom;
   gregorian( year,  old_month, dom);
   return set_YMD(year,month,dom);
}
//_2005-04-06________________________________________________________set_month_/
Datetime64 Date::set_DOM(DOM dom)
{  Year year;
   Month month;
   DOM   old_dom;
   gregorian( year,  month, old_dom);
   return set_YMD(year,month,dom);
}
//_2005-04-06__________________________________________________________set_DOM_/
Datetime64 Date::inc_month(int16 offset)
  // Adds offset years to the date.
  //   If offset is negative, offset years are subtracted
{  Year    year;
   CORN::Month   month;                                                          //990214
   CORN::DOM     DOM;                                                            //990214
   gregorian(year,month,DOM);
   int16 run_month = (int16)(month + offset);                                    //990224
   year += (Year)(run_month/ 12);                                                //990224
   month = (CORN::Month)(run_month % 12);                                        //990224
   set_YMD(year,month,DOM);
   return get_datetime64();                                                      //030714
}
//_1997-09-09________________________________________________________inc_month_/
Datetime64 Date::dec_month(int16 offset)
{  // Subtracts offset years to the date.
   //   If offset is negative, offset years are added
    nat8 ordering_BS   = format.ordering_BS;                                      //141120
    nat8 styles        = format.styles;                                           //141120
    char separator     = format.separator;                                        //141120
    bool DOY_indicator = format.DOY_indicator;                                    //141120
   CORN::Year    year;
   CORN::Month   month;                                                           //990214
   CORN::DOM     DOM;                                                             //990214
   gregorian(year,month,DOM);
   int16 run_month = (int16)(month - offset);                                     //990224
   year -= (int16)(run_month / 12);                                               //990224
   month = (CORN::Month)(abs(run_month) % offset);                                //990224
   set_YMD(year,month,DOM);
   return get_datetime64();                                                       //030714
}
//_1997-09-09________________________________________________________dec_month_/
Datetime64 Date::set_c_str(const char *date_str)
{  set_YD((Year)0,(CORN::DOY)0); // initialize
    nat8 ordering_BS   = format.ordering_BS;                                      //141120
    nat8 styles        = format.styles;                                           //141120
    char separator     = format.separator;                                        //141120
    bool DOY_indicator = format.DOY_indicator;                                    //141120

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
          for (i = 1; i<=12;i++)
             if (stricmp(month_str,date_month_abbrevs[i]) == 0) month = i;
     } else
        for (i = 1; i<=12;i++)
           if (stricmp(month_str,date_month_names[i]) == 0) month = i;
  }
  if      (styles & D_YY)   year += 1900;
  else if (styles & D_YYY)  year += 1000;
  switch (ordering_BS)
  {
    case D_YMD : case D_YDM : case D_MYD : case D_MDY :
    case D_DYM : case D_DMY : case D_MD  : case D_DM  :
       set_YMD((Year)year,(CORN::Month)month,(CORN::DOM)day);                    //980206
    break;
    default :
       set_YD((Year)year,(CORN::DOY)day);                                        //980206
    break;
  }
   return get_datetime64();                                                      //030714
}
//_1998_________________________________________________________________________
Datetime64 Date::set_string(const std::string &date_string)                      //140522
{  return set_c_str(date_string.c_str());
}
//______________________________________________________________________________
Date::Date(const char *date_str
,nat16 _ordering_BS
,nat16 _styles
,nat8 _separator
,bool _DOY_indicator)
: format(_ordering_BS,_styles,_separator,_DOY_indicator)
{  set_c_str(date_str);                                                          //030713
}
//______________________________________________________________________________
Datetime64 Date::set_now()
{
#if (defined(__MSDOS__) || defined(__BCPLUSPLUS__))
   // This is available for BC++ builder upto atlease RS2010
   // but no long erin MSC //100928_
  struct date date_struct;
  getdate(&date_struct);
  set_YMD((Year)date_struct.da_year,(CORN::Month)date_struct.da_mon,(CORN::DOM)date_struct.da_day);
#endif
#if defined __unix || defined(_MSC_VER)
     tm *time_struct;
     time_t timer;
     time(&timer);
     time_struct = localtime(&timer);
     set_YD(1900+time_struct->tm_year,time_struct->tm_yday + 1);
#endif
   return get_datetime64();
}
//_2003-07-15__________________________________________________________set_now_/
bool Date::is_leap_year(Year year)                                  affirmation_//130222
{  return date_is_leap_year(year);
}
//______________________________________________________________________________
bool Date::is_leap_this_year()                                      affirmation_//130222
{  return date_is_leap_year(get_year());
}
//_2013-02-25___________________________________________________________________
int8 Date::compare_date(const Date &second_date)                           const
{  return (int8)((date_num < second_date.date_num)                               //970925
   ? -1
   : (date_num >  second_date.date_num)
      ? 1
      : 0); //then date_num should equal second_date.date_num
}
//_2003-01-08_____________________________________________________compare_date_/
Date NO_DATE((Year)0,(CORN::DOY)0);                                              //990610
//______________________________________________________________________________
nat8 Date::get_days_in_month(Year year,Month month)                        const
{  nat8 days_in_month = get_month_lengths_in_year(year)[month];
   return days_in_month;
}
//_2013-02-22___________________________________________________________________
const nat8 *Date::get_month_lengths_in_year(Year year)                     const
{  return (is_leap_year(year))
   ? leap_year_month_lengths
   : common_year_month_lengths;
}
//_2013-02-22___________________________________________________________________
const nat8 *Date::get_month_lengths()                                      const
{  return get_month_lengths_in_year(get_year());
}
//_2013-02-22___________________________________________________________________
#ifdef NYI
Date Date::operator ++() // prefix operator
{  inc();
   return *this;
}
//_2014-02-19___________________________________________________________________
Date Date::operator --() // prex operator, return new value
{  *this = previous_date(*this);
   return *this;
}
//_2014-02-19___________________________________________________________________
Date Date::operator ++(int) // postfix operator
{  Date d = *this;
   inc();
   return d;
}
//_2014-02-19___________________________________________________________________
Date Date::operator --(int) // postx operator, return current value
{  Date d = *this;
   *this = previous_date(*this);
   return d;
}
//_2014-02-19___________________________________________________________________
#endif

#ifndef OLD_DATE
nat32 Date::days_between                                                         //170430
(const Date_const_interface &date2,bool inclusive)                         const
{
   return days_between((const Date_time &)date2,inclusive);
}
/*170430 unused
bool Date::within_period                                                         //170430
      (const Date_interface &earliest_date
      ,const Date_interface &latest_date)                                 const
{
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
#endif


} // namespace CORN

 /*
   Date operator + (Date date1,Date date2);
   Date operator + (Date date1,int16 days);
   Date operator - (Date date1,Date date2);
   Date operator - (Date date1,int16 days);

   Date operator += (Date date1,Date date2);
   Date operator += (Date date1,int16 days);
   Date operator -= (Date date1,Date date2);
   Date operator -= (Date date1,int16 days);

   Date operator ++ ();
	Date operator -- ();
*/

