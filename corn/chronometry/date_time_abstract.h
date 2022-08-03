#ifndef date_time_abstractH
#define date_time_abstractH
#include "corn/chronometry/date_time_I.h"
#include "corn/chronometry/date_abstract.h"
#include "corn/chronometry/time_abstract.h"

namespace CORN
{
//______________________________________________________________________________
class Date_time_abstract
: public implements_ Date_time_interface // Eventually rename to Date_time
, public extends_ Date_abstract
, public extends_ Time_abstract
{
 public:
   inline Date_time_abstract()
      : Date_time_interface()
      , Date_abstract()
      , Time_abstract()
      {}
 public: // accessors date



   /* The following are probably handled OK by Date abstract
      Dont delete until verified
   virtual Year         get_year()                                        const;
   virtual DOY          get_DOY()                                       const=0;
   virtual Month        get_month()                                     const=0;
   virtual DOM          get_DOM()                                       const=0;
   */

   inline virtual DOY get_DOY()       const { return Date_abstract::get_DOY(); } //170602
 public: // accessors time
   virtual Hour         get_hour()                                        const;
   virtual Minute       get_minute()                                      const;
   virtual Second       get_second()                                      const;


   virtual Centisecond  get_centisecond()                                 const;
   virtual Millisecond  get_millisecond()                                 const;
   virtual Hours        get_hours_after_midnight()                        const;
   virtual Minutes      get_minutes_after_midnight()                      const;
   virtual Seconds      get_seconds_after_midnight()                      const;
 public: // assignations (date implementations)
   virtual datetime64 set_now();
//   virtual datetime64 set_date32(Date32 value)                     assignation_;
//   virtual datetime64 set_datetime64(datetime64 value)             assignation_;
   virtual datetime64 set_year(Year year)                          assignation_;
   virtual datetime64 set_DOY(DOY doy)                             assignation_;
   virtual datetime64 set_YMD(Year year,Month month,DOM dom)       assignation_;
   virtual datetime64 set_YD(Year year,DOY doy)                    assignation_;
   virtual datetime64 set_month(Month month)                       assignation_;
   virtual datetime64 set_DOM(DOM dom)                             assignation_;
 public: // assignations (time implementations)
   virtual datetime64 set_time(const Time_interface &_time)        assignation_;
   virtual datetime64 set_time64(datetime64 time64)                assignation_;
   // Sets to and returns the computer's system date/time.
   virtual datetime64 set_S       (Seconds seconds)                assignation_;
   virtual datetime64 set_HHMMSS (time_HHMMSS HHMMSS)              assignation_;
   virtual datetime64 set_HMS
      (Hour hour, Minute minute, Second second)                    assignation_;
   virtual datetime64 set_HMSm
      (Hour hour, Minute minute, Second second
      ,Millisecond millisecond)                                    assignation_;
   virtual datetime64 set_HMSc
      (Hour hour, Minute minute, Second second
      ,Centisecond centisecond)                                    assignation_;


 public: // assignations (date-time implementations)
   virtual datetime64 set_date(const Date_interface &date)         assignation_;
   virtual datetime64 set_DT
      (const Date_interface &date,const Time_interface &time)      assignation_;

 public: // modifiers
 public: // autoincrement (date)
   virtual datetime64 inc_years  (int16 years)                    modification_;
   virtual datetime64 inc_months (int16 months)                   modification_;
   virtual datetime64 inc_days   (int32 days)                     modification_;
   //170430 use interface implementation    virtual datetime64 dec_years  (int16 years)                    modification_;
   //170430 use interface implementation    virtual datetime64 dec_months (int16 months)                   modification_;
   virtual datetime64 dec_days   (int32 days)                     modification_;
 public: // autoincrement (time)
   virtual datetime64   inc_hours(Hours hours)                     assignation_;
   virtual datetime64   inc_minutes(Minutes minutes)               assignation_;
   virtual datetime64   inc_seconds(Seconds seconds)               assignation_;
 public: // math
 public: // affirmations
 public: // methods for arbitrary time
 public: // conversions
   const std::string &append_to_string(std::string &target)               const;
   datetime64 set_c_str(const char *date_time_str)                 assignation_;
 protected: // utility
   virtual void split(datetime64 &date_part, datetime64 &time_fract)    const=0;
   virtual datetime64 join(datetime64 date_part, datetime64 time_fract)      =0;
   virtual datetime64 inc_time_fract(datetime64 time_fract)     modification_=0;

};
//_2017-04-26________________________________________________Date_time_64_cowl_/
} // namespace CORN
// Roger Nelson rnelson@wsu.edu

#endif
