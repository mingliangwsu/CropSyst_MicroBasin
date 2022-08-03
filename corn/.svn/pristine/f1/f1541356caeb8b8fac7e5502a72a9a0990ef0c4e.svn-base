#ifndef dateHH
#define dateHH
#ifndef __cplusplus
#include "corn/primitive.h"
#endif
// check needed class Event_data_record;   // This is only for LADSS

#define CORN_date_date(year,doy) ((int32)((year < 0)? -(labs(year *1000) + (int32)labs(doy)): year *1000 + (int32)labs(doy)))
//130226 rename to CALC_DATE_NUMBER

#ifndef date_typesHH
#  include "CORN/chronometry/date_types.hh"
#endif

#ifdef __cplusplus
namespace CORN {
#endif
extern nat8 common_year_month_lengths[13];
extern nat8 leap_year_month_lengths[13];
extern bool date_is_leap_year(Year year);
extern DOM date_get_days_in_month(Year year,Month month);
extern const char *date_get_month_abbrev(Month month);
extern const char *date_get_month_name(Month month);
#ifdef __cplusplus
}
#endif

#endif

