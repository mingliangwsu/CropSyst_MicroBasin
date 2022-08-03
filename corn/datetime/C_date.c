/* datetime.c

   Written by Roger Nelson
   Comments, suggestions, questions and bug reports can be sent to:

		 Biological Systems Engr. Dept.
       Washington State University
       Pullman, WA 99164-6120

		 rnelson@wsuaix.csc.wsu.edu

       Phone: (509)335-1578
		 FAX  : (509)335-2722
*/


#include <rlib/date.h>
#include <stdio.h>
#include <math.h>  // Only for abs
#include <string.h>

#ifdef LANGUAGE_TRANSLATION
#include <language.h>
int DT_month_names[13] =
{0,L_January  ,L_February ,L_March    ,L_April    ,L_May      ,L_June     ,
	L_July     ,L_August   ,L_September,L_October  ,L_November ,L_December };

int DT_month_abbrevs[13] =
{0,L_Jan,L_Feb,L_Mar,L_Apr,L_May,L_Jun,L_Jul,L_Aug,L_Spt,L_Oct,L_Nov,L_Dec};
#else
char *DT_month_names[13] =
{"","January  ","February ","March    ","April    ","May      ","June     ",
	 "July     ","August   ","September","October  ","November ","December "};

char DT_month_abbrevs[13][4] =
{ "???","Jan","Feb","Mar","Apr","May","Jun","Jly","Aug","Sep","Oct","Nov","Dec"};
#endif

int DT_normal_days_in_month[13] =
{    0,   31,   29,   31,   30,   31,   30,   31,   31,   30,   31,   30,  31};

RDate RDate_date(unsigned int year,unsigned int day)
{
   return((long)year *1000 + (long)day);
};

RDate DT_gregorian_julian(unsigned int year,unsigned int month,unsigned int day)
{
	int dayofyear, m;

   dayofyear = day;
	for (m = 1 ; m < month ; m++)
       dayofyear += DT_days_in_month(year,m);
   return(RDate_date(year,dayofyear));
};

/* Returns 1 for Sunday, 2 Monday etc... */
unsigned DT_day_of_week(unsigned int year,unsigned int month,unsigned int DOM)
{
	int     day ;
	int     yr ;
   int     mn ;
	int     n1 ;
   int     n2 ;

   /* Offset from Zeller to local */
   /* --------------------------- */
   #define ZELLER_OFFSET   -1

   yr = year ;
   mn = month ;

   /* January or February? */
	/* -------------------- */
   if (mn < 3)
   {
	  /* Yes, make these part of last year */
     /* --------------------------------- */
     mn += 12 ;
     yr -= 1 ;
   };

   n1 = (26 * (mn + 1)) / 10 ;
   n2 = (int) ((125 * (long) yr) / 100) ;

   day = ((DOM + n1 + n2 - (yr / 100) + (yr / 400) + ZELLER_OFFSET) % 7) ;
/*
   switch (day)
   { case 0 : day = 0; break;
     default :
		  day = day + 1; break;
   };
*/
	day += 1;
   return(day);
}

unsigned RDate_year(RDate date)
{
   return((int)(date / (long)1000));
};

unsigned RDate_day(RDate date)
{
   return((int)(date % (long)1000));
};

void RDate_gregorian(RDate date, unsigned int *year, unsigned int *month, unsigned int *day)
{
   unsigned dayofyear;
	int m = 1;
   int sum_month = 0;
   unsigned dom;

   *year = RDate_year(date);
   dayofyear = RDate_day(date);
	while (((sum_month + DT_days_in_month(*year,m)) < dayofyear))
   {
      sum_month += DT_days_in_month(*year,m);
      m += 1;
   };
   dom = (dayofyear-sum_month);
   *month = m;
	*day = dom;
};

/*
char *RDate_gregorian_str(RDate date,int numeric)
{
  unsigned int year,month,dom;

  static char gregorian_string[20];

  RDate_gregorian(date,&year,&month,&dom);
  if (numeric)
      sprintf(gregorian_string,"%4d%c%2d/%2d",year,
         (year < 1000) ? ':' : '/', month,dom);
  else
      sprintf(gregorian_string,"%4d%c%3s %2d",year,
         (year < 1000) ? ':' : '/',DT_month_abbrevs[month],dom);
  return(gregorian_string);
};
*/

char *DT_date_string(RDate date,char ordering,char styles,char separator)
{
  static char return_str[50];
  char year_str[10];
  char month_str[30];
  char month_num_str[10];
  char doy_str[10];
  char dom_str[10];
  char sep1_str[5];
  char sep2_str[5];
  unsigned int year = 0;
  unsigned int month = 0;
  unsigned int dom = 0;
  unsigned int doy = 0;

  if ((ordering == DT_YD) || (ordering == (DT_DY)))
  { year = RDate_year(date);
    doy = RDate_day(date);
  }
  else
	 RDate_gregorian(date,&year,&month,&dom);

  if  (styles & DT_YY) sprintf(year_str,"%02d",year %100);
  else if (styles & DT_YYY)  sprintf(year_str,"'%02d",year%100);
  else /* DT_YYYY*/ sprintf(year_str,"%04d",year);

  if (styles & DT_lead_none)
  {
    sprintf(month_num_str,"%d",month);
	 sprintf(dom_str,"%d",dom);
    sprintf(doy_str,"%d",doy);
  }
  else if (styles & DT_lead_zero)
  {
    sprintf(month_num_str,"%02d",month);
    sprintf(dom_str,"%02d",dom);
    sprintf(doy_str,"%03d",doy);
  }
  else if (styles & DT_lead_space)
  { sprintf(month_num_str,"%2d",month);
	 sprintf(dom_str,"%2d",dom);
    sprintf(doy_str,"%3d",doy);
  };

  if (styles & DT_Mmm)
    sprintf(month_str,"%s",
#ifdef LANGUAGE_TRANSLATION
         translate(DT_month_abbrevs[month]));
#else
			DT_month_abbrevs[month]);
#endif
  else if (styles & DT_Mmmm)
    sprintf(month_str,"%s",
#ifdef LANGUAGE_TRANSLATION
			translate(DT_month_names[month]));
#else
         DT_month_names[month]);
#endif
  else
     strcpy(month_str,month_num_str);

  if (separator == ',')
  {  strcpy(sep1_str," ");
	  strcpy(sep2_str,", ");
  }
  else
  { sep1_str[0] = separator;
    sep2_str[0] = separator;
    sep1_str[1] = 0;
    sep2_str[1] = 0;
  };

  switch (ordering)
  {
	 case DT_YMD : sprintf(return_str,"%s%s%s%s%s",year_str,sep1_str,month_str,sep2_str,dom_str); break;
	 case DT_YDM : sprintf(return_str,"%s%s%s%s%s",year_str,sep1_str,dom_str,sep2_str,month_str); break;
	 case DT_MYD : sprintf(return_str,"%s%s%s%s%s",month_str,sep1_str,year_str,sep2_str,dom_str); break;
	 case DT_MDY : sprintf(return_str,"%s%s%s%s%s",month_str,sep1_str,year_str,sep2_str,year_str); break;
	 case DT_DYM : sprintf(return_str,"%s%s%s%s%s",dom_str,sep1_str,year_str,sep2_str,month_str); break;
	 case DT_DMY : sprintf(return_str,"%s%s%s%s%s",dom_str,sep1_str,month_str,sep2_str,year_str); break;
	 case DT_MD  : sprintf(return_str,"%s%s%s",month_str,sep1_str,dom_str); break;
	 case DT_DM  : sprintf(return_str,"%s%s%s",dom_str,sep1_str,month_str); break;
	 case DT_YD  : sprintf(return_str,"%s%s%s",year_str,sep1_str,doy_str); break;
	 case DT_DY  : sprintf(return_str,"%s%s%s",doy_str,sep1_str,year_str); break;
  };
  return(return_str);
};

boolean DT_leap_year(unsigned int year)
{
   return((year % 4)   ? 0 :
			 (year % 100) ? 1 :
          (year % 400) ? 0 : 1);
};

unsigned DT_days_in_month(unsigned int year,unsigned int month)
{
	return  ((month == 2) ?
	       ((DT_leap_year(year)) ? 29 : 28) :
	       DT_normal_days_in_month[month]);
};

int DT_days_between_julian(RDate date1,RDate date2)
{
  int days = 0;
  int year;
  int year1, year2;
  int doy1, doy2;
  int yl;
  RDate hold_date;

  if (date1 > date2)
  {
    hold_date = date1;
	 date1 = date2;
    date2 = hold_date;
  };

  year1 = RDate_year(date1);
  year2 = RDate_year(date2);
  doy1 = RDate_day(date1);
  doy2 = RDate_day(date2);
  if (year1 == year2)
    days += doy2 -doy1;
  else
  {
    days = 0;
    for (year = year1+1; year < year2; year++)
		 days += DT_days_in_year(year);
	 yl = DT_days_in_year(year1);
    days += (yl - doy1);
	 days += doy2;
  }
  return(days);
};

RDate DT_day_after(RDate date)
{
   RDate next_date;
	int year;

	year = RDate_year(date);
	next_date = date +1;
   if (RDate_day(next_date) > (year ? DT_days_in_year(year) : 365))
      next_date = RDate_date(year ? year+1 : 1,1);
   return(next_date);
};

RDate DT_day_before(RDate date)
{
	if (RDate_day(date) == 1)
      return(RDate_date(RDate_year(date)-1,DT_days_in_year(RDate_year(date)-1)));
   else
      return(date- 1);
};

RDate RDate_date_plus(RDate date, int offset)
{
   int day_count;
	if (offset < 0)
		return(RDate_date_minus(date,abs(offset)));

   for (day_count = 1 ; day_count <= offset ; day_count ++)
		date = DT_day_after(date);
   return(date);
};

RDate RDate_date_minus(RDate date, int offset)
{
   int day_count;
	if (offset < 0)
      return(RDate_date_plus(date,abs(offset)));
	for (day_count = 1; day_count <= offset; day_count++)
		date = DT_day_before(date);
	return(date);
};

//------------------------------------------------------------------

