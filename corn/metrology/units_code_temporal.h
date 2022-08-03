#ifndef units_code_temporalH
#define units_code_temporalH
// UT_      Temporal units code (same as a UC_ but for dates and time)

#define UT_arbitrary_time           0
#define UT_arbitrary_date           0
#define UT_arbitrary_datetime       0
// aribtrary time is used in UED creation layouts to specify arbitrary time stamp record stepping.

#define UT_unit_time                0

// Time                                      // 0001xxxx xxxxxxxxb

// Time periods greater than 1 day (bit 12=0)// 00010xxx xxxxxxxxb

// In time periods greather than 1 day,
// Bits 8-11 (4 bits) denote the following:

#define UT_time       (nat16)0x1000      // 00010000 00000000b 1000x
//This time is a 64bit float represented as the fraction of the day
//Also applies to date time where the whole number is the date  YYYYDDD and the decimal is the fraction of the day
#define UT_date       (nat16)0x1001
//This date is a integer represented as YYYYDDD

#define UT_day_of_week     (nat16)0x1010      // Sort of a place holder
#define   UT_sunday        (nat16)0x1011      // 00010000 00010001b
#define   UT_monday        (nat16)0x1012      // 00010000 00010010b
#define   UT_tuesday       (nat16)0x1013      // 00010000 00010011b
#define   UT_wednesday     (nat16)0x1014      // 00010000 00010100b
#define   UT_thursday      (nat16)0x1015      // 00010000 00010101b
#define   UT_friday        (nat16)0x1016      // 00010000 00010110b
#define   UT_saturday      (nat16)0x1017      // 00010000 00010111b

#define UT_day_of_month    (nat16)0x1020      // 00010000 00100000b
// 0x1091 to 0x10AF are reserved for the 31 days of the month.
#define UT_day_of_month_1  (nat16)0x1021      // 00010000 00100001b
// :
#define UT_day_of_month_31 (nat16)0x103F      // 00010000 00111111b

#define UT_day_of_year     (nat16)0x1040      // as part of a date, not as a unit of time.
//                                              00010000 10000000 <- Not usable  (denominator

#define UT_week            (nat16)0x1100      // 00010001 00000000b
// 0x1101 to 0x1134 are reserved for the 52 weeks of the year (indexed from 1)
// 0x1101                                    // 00010001 00000001b
// :
// 0x1134                                    // 00010001 00110100b

#define UT_fortnight       (nat16)0x1140      // 00010001 01000000b
// 0x1141 to 0x115A are reserved for th 26 fortnights of the year (indexed from 1)
// 0x1141                        (nat16)0x1141      // 00010001 01000001b
//                                  :
// 0x115A                        (nat16)0x115A     //  00010001 01011010b

// There is also a ten day unit (in spanish is it called ?decenas?

#define UT_month           (nat16)0x1200      // 00010010 00000000b
#define   UT_january       (nat16)0x1201      // 00010010 00000001b 1201x
#define   UT_february      (nat16)0x1202      // 00010010 00000010b 1202x
#define   UT_march         (nat16)0x1203      // 00010010 00000011b 1203x
#define   UT_april         (nat16)0x1204      // 00010010 00000100b 1204x
#define   UT_may           (nat16)0x1205      // 00010010 00000101b 1205x
#define   UT_june          (nat16)0x1206      // 00010010 00000110b 1206x
#define   UT_july          (nat16)0x1207      // 00010010 00000111b 1207x
#define   UT_august        (nat16)0x1208      // 00010010 00001000b 1208x
#define   UT_september     (nat16)0x1209      // 00010010 00001001b 1209x
#define   UT_october       (nat16)0x120A      // 00010010 00001010b 120ax
#define   UT_november      (nat16)0x120B      // 00010010 00001011b 120bx
#define   UT_december      (nat16)0x120C      // 00010010 00001100b 120cx

#define UT_quarter         (nat16)0x1210      // 00010010 00010000b
// 1211 to 1214 are reserver for quarters 1 through 4
#define UT_quarter_1       (nat16)0x1211      // 00010010 00010001b
#define UT_quarter_2       (nat16)0x1212      // 00010010 00010010b
#define UT_quarter_3       (nat16)0x1213      // 00010010 00010011b
#define UT_quarter_4       (nat16)0x1214      // 00010010 00010100b

#define UT_trimester       (nat16)0x1215      // 00010010 00010101b
// 1301 to 1303 are reserved for trimesters 1 through 3
#define UT_trimester_1     (nat16)0x1216      // 00010010 00010110b
#define UT_trimester_2     (nat16)0x1217      // 00010010 00010111b
#define UT_trimester_3     (nat16)0x1218      // 00010010 00011000b

// Note b biannum I mean 6 months
#define UT_biannum         (nat16)0x1219      // 00010010 00011001b
// biannum1 is the first have, biannum2 is the second
#define UT_biannum_1       (nat16)0x121A      // 00010010 00011010b
#define UT_biannum_2       (nat16)0x121B      // 00010010 00011011b

// Bienium is every 2 years (not currently implemented)

// The following units can be used for timesteps:
// Either cardinal or ordianal values.
#define UT_seconds         (nat16)0x13
#define UT_0_seconds       (nat16)0x1300      // 00010011 00000001b
#define UT_1_second        (nat16)0x1301      // 00010011 00000001b
// :
#define UT_30_seconds      (nat16)0x131E      // 00010011 00011110b
// :
#define UT_60_seconds      (nat16)0x133C      // 00010011 00111100b

#define UM_minutes         (nat8)0x14
#define UT_0_minutes       (nat16)0x1400      // 00010100 00000000b
#define UT_1_minute        (nat16)0x1401      // 00010100 00000001b
// :
#define UT_5_minutes       (nat16)0x1405      // 00010100 00001010b
// :
#define UT_10_minutes      (nat16)0x140A      // 00010100 00001010b
// :
#define UT_15_minutes      (nat16)0x140F

#define UT_30_minutes      (nat16)0x141E      // 00010100 00011100b
#define UT_half_hour       (nat16)0x141E      // identical to 30 minutes
// :
#define UT_60_minutes      (nat16)0x143C      // 00010100 00111100b

#define UM_hours           (nat8)0x15
#define UT_0_hours         (nat16)0x1500      // 00010101 00000001b
#define UT_1_hour          (nat16)0x1501      // 00010101 00000001b
// :
#define UT_24_hours        (nat16)0x1518      // 00010101 00011000b

// The following are metric time compositions
// These can be used in rates
// Also for counters  (I.e. a time step of 5 days  the days units would be UT_day)
// metric system base 10 exponents for the low byte apply

#define UM_second      (nat8) 0x16
#define UT_second          (nat16)0x1600      // 00010110 00000000b
// The lower word is the metric exponent so
// reserverd                     0x1601
// to                            0x16FF
#define UT_jiffy_AC        (UT_second | U_metric_centi)
// Jiffy is also the duration of one tick of a computer's system clock
// Jiffy in reference to alternating current previously was 1/60 second in the US and Canada
// and 1/50 second in other places.
// Some physisists call give the time for light o travel one foot in a vacuum a Jiffy
// which is close to one nanosecond.
#define UT_millisecond     (UT_second | U_metric_milli)
#define UT_jiffy_real_time (UT_second | U_metric_milli)

#define UM_minute      (nat8) 0x17
#define UT_minute          (nat16)0x1700      // 00010111 00000000b
// The lower word is the metric exponent so
// reservered                    0x1701
// to                            0x17FF

#define UM_hour        (nat8) 0x18
#define UT_hour            (nat16)0x1800      // 00011000 00000000b
// The lower word is the metric exponent so
// reservered                    0x1801
// to                            0x18FF

#define UM_day         (nat8) 0x19
#define UT_day             (nat16)0x1900      // 00011001 00000000b // was1080x
// The lower word is the metric exponent so
// reservered                    0x1901
// to                            0x19FF

#define UM_year        (nat8) 0x1A
#define UT_year            (nat16)0x1A00      // 00011010 00000000b
// The lower word is the metric exponent so  //
// reservered                    0x1A01
// to                            0x1AFF
// The following are of significance, they are powers of 10 thus can have
// metric in the lower byte
#define UT_decade          (nat16)0x1A01      // 00011010 00000001b
#define UT_century         (nat16)0x1A02      // 00011010 00000010b
#define UT_millenium       (nat16)0x1A03      // 00011010 00000011b

#define UT_END_TIME_CODES  (nat16)0x1AFF
// UT_END_TIME_CODES is just a place holder

#define UT_date_time       (nat16)0x1B00
// Date represented by a floating point number where the integer portion is YYYYDDD and the fraction is fraction of a day.
// 0x1B01-0x1BFF Continue here with comuter date and and times represented by seconds milliseconds or other metric seconds from various reference date (epoch)
// #define UT_date_time_epoch_XXXX
//http://en.wikipedia.org/wiki/Epoch_(reference_date)

//> Do not delete this line, it is used by the units code constant generator
#define UC_1_per_day                      U_a_per_b(UC_1,UT_day)

#endif
