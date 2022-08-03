#ifndef C_DATE_H
#define C_DATE_H

// These are basic date cacluations for C
// Do not include this file if using C++


 enum D_months {NO_MONTH,JANUARY,FEBRUARY,MARCH,APRIL,MAY,JUNE,JULY,
 		   AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER};

 enum Days_of_week {NO_DOW,SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY};


 typedef long CORN_date;     /*  year * 1000 + day */

 CORN_date CORN_date_date(Year year,DOY doy);
 /* take year and day of year and generates a CORN_date date */

 CORN_date D_gregorian_CORN_date(Year year,Month month,DOM dom);
 /* takes year month and day of month and generates a CORN_date date */

 CORN_date CORN_date_date_plus(CORN_date date_num,int32 offset);
 /* takes a CORN_date date and adds offset days to the date incrementing the
  year if necessary.
  If offset is negative, offset days are subtracted (CORN_date_date_minus)*/

 CORN_date CORN_date_date_minus(CORN_date date_num, int32 offset);
 /* takes a CORN_date date and subtracts offset days to the date decrementing
  the year if necessary.
  If offset is negative, offset days are added (CORN_date_date_plus) */

 CORN_DOW D_day_of_week(Year year,Month month,CORN::DOM dom);
 /* returns the day of week (see days_of_week) */

 Year CORN_date_year(CORN_date date_num);
 /* extracts the year from the CORN_date date */

 CORN_DOY CORN_date_DOY(CORN_date date_num);
 /* extracts the day of year from the CORN_date date */

 void CORN_date_gregorian(CORN_date date_num, Year *year, Month *month, CORN::DOM *dom);
 /* extracts the year month and day of month from the CORN_date date */

 int32 D_days_between_CORN_date(CORN_date date1,CORN_date date2);
 /* counts the number of days between the two dates.
    Either date may be greater than the other.
    (result of this function CORN_date_date_plus date1 gives date2.)
 */

 char *D_date_string(CORN_date date_num,uint8 ordering,uint16 styles,uint8 separator);
 /* returns the string representation of the date in practically
 	any date_num format you can think of.

	 ordering is one of the CORN_date or gregorian date orderings.
    styles may be a year format or'ed with a numeric format and month representation.
    separator is the character used to seperate the date fields usually  / - . | or space
       special cases:
 	     if separator is NULL, then no separator is used I.e: 1998Jan01
 				 if separator is ',', then a comma is used only before last
 					 field and spaces are inserted between each field:
 		I.e:  Jan 1, 1993  or  26 January, 1993

 	example CORN_date_gregorian_str(1993020,D_MDY,D_YYYY|D_lead_zero|D_M,'/');
       gives  01/20/1993.
 */

   long CORN_date_computers_date(); obsolete
   /* returns the current system computer date */
#endif
