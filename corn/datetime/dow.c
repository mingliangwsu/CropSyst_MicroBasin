/*----------------------------------------------------------------------
 *
 *  Compute_Day
 *  Compute Day of Week
 *
 *  Usage
 *
 *      int
 *      Compute_Day(date, month, year)
 *      int     date ;
 *      int     month ;
 *      int     year ;
 *
 *  Parameters
 *
 *      date            Date of Month (1 - 31)
 *      month           Month of Year (1 - 12)
 *      year            Year (e.g., 1989)
 *
 *  Description
 *
 *      Compute_Day() computes the day of the week for the given date
 *      using the Zeller Congruence.  It returns a positive value from
 *      0 to 6 for the day of the week
 *
 *  Notes
 *
 *      The Zeller Congruence maps Saturday as day 0.  Most applications
 *      treat Sunday as day 0.  The parameter ZELLER_OFFSET is used to
 *      convert the day of the week from Zeller to local.
 *
 *-
 */

int Compute_Day(date, month, year)
int     date ;
int     month ;
int     year ;

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
        }

n1 = (26 * (mn + 1)) / 10 ;
n2 = (int) ((125 * (long) yr) / 100) ;

day = ((date + n1 + n2 - (yr / 100) + (yr / 400) + ZELLER_OFFSET) % 7) ;
return day ;
}



