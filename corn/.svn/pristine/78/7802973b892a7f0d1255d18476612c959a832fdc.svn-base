#include "corn/chronometry/date_format.h"
#include <string.h>
namespace CORN
{
//______________________________________________________________________________
Date_format::Date_format(const char *format_string)
:ordering_BS   (CORN_date_DEFAULT_ORDERING)
,styles        (CORN_date_DEFAULT_STYLES)
,separator     (CORN_date_DEFAULT_SEPARATOR)
,DOY_indicator (false)                                                           //020507
{  set_cstr(format_string); }                                                    //141120
//_2005-04-12______________________________________constructor:given_a_string__/
Date_format::Date_format
(nat16 _ordering                                                                 //050412
,nat16 _styles                                                                   //990225
,nat8  _separator                                                                //990225
,bool  _DOY_indicator)
:ordering_BS   (_ordering)
,styles        (_styles)
,separator     (_separator)
,DOY_indicator (_DOY_indicator)
{}
//____________________________________________constructor:for specific styles__/
Date_format::Date_format
(const Date_format &to_copy_from)
:ordering_BS   (to_copy_from.ordering_BS)
,styles        (to_copy_from.styles)
,separator     (to_copy_from.separator)
,DOY_indicator (to_copy_from.DOY_indicator)
{}
//_2003-07-15________________________________________________constructor:copy__/
Date_format::~Date_format()
{}
//_2013-05-15___________________________________________________________________
bool Date_format::set_string(const std::string &format_string)     contribution_
{   return set_cstr(format_string.c_str());
}
//_2014-11-20__________________________________________________________________/
bool Date_format::set_cstr(const char *format_string)        contribution_
{
   if (!format_string) return false;
   nat16 new_style = 0;
   bool has_4digit_year = false;
   bool has_month_abbr = false;
   bool has_month_name = false;
   bool has_month_number = false;                                                //160606
   bool zero_lead  = false;
   bool space_lead = false;
   nat16 order = 0;
   separator = 0;                                                                //110812
   //default separator must be zero to handle formats such as YYYYMMDD
   for (size_t i = 0; i < strlen(format_string); i++)
   {  switch (format_string[i])
      {  case 'Y' :
            if (format_string[i+3] == 'Y')   { has_4digit_year = true; i+=3; }   //150328
            if ((order & 0x7) != DO_Year) order = (nat16)((order << 3) | DO_Year);
         break;
         case 'M' :
         {  bool probably_minute=false;                                          //050413
            if (i>0)                                                             //050413
            // If this is a date-time format exclude what might be minute indicator
            {  if (format_string[i-1] == ':') probably_minute=true;
               if (format_string[i-2] == ':') probably_minute=true;
               if (format_string[i+1] == ':') probably_minute=true;
               if (format_string[i+2] == ':') probably_minute=true;
               if (format_string[i+2] == 'S') probably_minute=true;
               if (format_string[i+3] == 'S') probably_minute=true;
            }
            if (probably_minute)
                return false;
            {
            if (format_string[i+1] == 'm')
            {   if (format_string[i+3] == 'm') has_month_name=true;
               else                            has_month_abbr=true; }
            if ((i >0) && format_string[i-1] == ' ')     {space_lead= true; }
            if (format_string[i+1] == 'M')     {zero_lead=true; space_lead= false; has_month_number = true; i+=1; } //160606_150328
            //  if (order[order_i] != 'M') order[order_i++] = 'M';
            if ((order & 0x7) != DO_Month) order = (nat16)((order << 3) | DO_Month);
            }
         } break;
         case 'D' :
            if (format_string[i+2] == 'D') // this is day of year
            {  if ((order & 0x7) != DO_DOY) order = (nat16)((order << 3) | DO_DOY);
               i += 2;
               zero_lead = true;                                                 //110812
            }
            else  if (format_string[i+1] == 'D')
            {  if ((order & 0x7) != DO_DOM) order = (nat16)((order << 3) | DO_DOM);
               zero_lead = true;
                i += 1;
            }
            else
            {  if ((order & 0x7) != DO_DOM) order = (nat16)((order << 3) | DO_DOM);
               zero_lead = false;
            }
         break;
         case '/' : separator = '/'; break;
         case '-' : separator = '-'; break;
         case '.' : separator = '.'; break;                                      //160606
         case '0' : new_style |= D_relative; break;
         case '1' : new_style |= D_relative_1; break;
         case '(' :                                                              //171017
         {  DOY_indicator                                                        //171017
               = format_string[i+1] == 'D'                                       //171017
               &&format_string[i+2] == 'O'                                       //171017
               &&format_string[i+3] == 'Y'                                       //171017
               &&format_string[i+4] == ')';                                      //171017
            i += 4;                                                              //171017
         };  break;                                                              //171017
      }
   }
   ordering_BS = order;
   if (has_4digit_year) new_style |= D_YYYY;
   else                 new_style |= D_YY;
   if (zero_lead)       new_style |= D_lead_zero;
   else if (space_lead) new_style |= D_lead_space;
   else                 new_style |= D_lead_none;
   if (has_month_abbr)  new_style |= D_Mmm;
   else if (has_month_name)new_style |= D_Mmmm;
   else if (has_month_number) new_style |= D_M;                                  //160606
   styles = new_style;                                                           //060221

   return true;
}
//_2005-04-12_______________________________________________set_format_string__/
bool Date_format::set_ordering_styles_separator //150310 set_format
(nat16 _ordering
,nat16 _styles                                                                   //990225
,nat8  _separator                                                                //990225
,bool  _DOY_indicator)                                             contribution_
{  ordering_BS  =_ordering;
   styles       =_styles;
   separator    =_separator;
   DOY_indicator=_DOY_indicator;                                                 //020507
   return true;
}
//_2005-04-12______________________________________________________set_format__/
bool Date_format::copy_format(const Date_format &from_copy)        contribution_
{  ordering_BS    = (from_copy.ordering_BS);
   styles         = (from_copy.styles);
   separator      = (from_copy.separator);
   DOY_indicator  = (from_copy.DOY_indicator);
   return true;
}
//_2005-04-12_____________________________________________________copy_format__/
Date_format ISO_8601_date_format;                                                //170428
Date_format year_only_date_format( D_Y,D_YYYY,'-');                              //180108
//______________________________________________________________________________
} // namespace CORN

