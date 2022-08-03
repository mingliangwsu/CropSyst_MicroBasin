#ifndef time_formatH
#define time_formatH

#ifndef constH
#  include "corn/const.h"
#endif
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include <string>
// The following are for formatting
// Time ordering
#define T_omit    (uint8)0x0
#define T_HMS     (uint8)0x1
#define T_HM      (uint8)0x2
#define T_MS      (uint8)0x3
#define T_H       (uint8)0x4
#define T_M       (uint8)0x5
#define T_S       (uint8)0x6
// HS prints the number of seconds in the hour
#define T_HS      (uint8)0x7
// The following prints the total number of hours, minutes, or seconds (whole numbers)
#define T_Hours   (uint8)0x8
#define T_Minutes (uint8)0x9
#define T_Seconds (uint8)0xA
//NYI #define T_decimal (uint8)0xB
// This is the time expressed as a decimal I.e. minute of the day / 1440, hour of the day / 24, second of the day / 86400
// Reserved for future use
//#define T_x       (uint8)0xB
//#define T_x       (uint8)0xC
//#define T_x       (uint8)0xD
//#define T_x       (uint8)0xE
//#define T_x       (uint8)0xF

// Time style bitmask
#define T_24hour        0
// 24 hour does not have leading 0 (or space) in hour  I.e. 1:23:45
#define T_12hour        1
#define T_military      2
#define T_scientific    2
// Both military and scientific are the same: 24 hour with leading zero  I.e.   01:23:45
#define T_am_pm         3   /* 12hour with am/pm marker */

#ifdef  NYI
24 hour does not have leading 0, military time does have leading 0
#define T_lead_space_hour   /* I.e.   1:23:45  01:23:45 instead of   */
#define T_lead_space_minute
#define T_lead_space_second
#endif

// Always uses leading 0 for HHMMSS or HH:MM:SS type formats
// For total hours minutes or seconds, the integer is printed with no leading character (or separator)

//#define get_HHMMSS get_hours_minutes_seconds
//#define set_HHMMSS set_hours_minutes_seconds

namespace CORN
{
   class Time; //forward decl                                                    //141120
   class Time_deprecated; //170825
//______________________________________________________________________________
class Time_format
{
 protected: friend class Time; friend class Time_abstract; friend class Time_deprecated; //170427
   contribute_ nat8       ordering;
   contribute_ nat8       styles;
   contribute_ nat8       separator; // normally ':'
 public:
    Time_format                                                                  //991115
      (nat8       _ordering    = T_HMS
      ,nat8       _styles      = T_24hour
      ,nat8       _separator   = ':');
   Time_format(const Time_format &/*to_copy_from*/);                             //030715
      // Copy Constructor
   inline virtual ~Time_format() {}                                              //130515
   Time_format(const char *format_string);                                       //050412
      // This copy Constructor takes a format string
      // This is used in tabular data formats and vv_entries
   virtual bool set_cstr(const char *format_string)                contribution_;//141120_050412
   virtual bool set_string(const std::string &format_string)       contribution_;//141120
   virtual bool clear()                                            contribution_;//160606
   bool copy_format(const Time_format &to_copy_from)               contribution_;//050412
};
//______________________________________________________________________________
// Common time format strings
#define  TF_H_MM_SS     "H:MM:SS"
#define  TF_HH_MM_SS    "HH:MM:SS"
#define  TF_H_MM        "H:MM"
#define  TF_HH_MM       "HH:MM"
#define  TF_H           "H"
#define  TF_HH          "HH"
#define  TF_MM_SS       "MM:SS"

#define  TF_HHMMSS      "HHMMSS"
#define  TF_HHMM        "HHMM"
#define  TF_MMSS        "MMSS"

// Format string also accepts other separators (I.e. HH.MM.SS)
//______________________________________________________________________________
extern Time_format ISO_8601_time_format;                                         //170428
//______________________________________________________________________________
} // namespace CORN
#endif

