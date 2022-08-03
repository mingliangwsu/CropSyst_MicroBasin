#ifndef date_abstractH
#define date_abstractH

#include "corn/chronometry/date_I.h"
#include "corn/chronometry/date_format.h"
namespace CORN
{
   class Time_interface;
//______________________________________________________________________________
class Date_const_abstract
: public implements_ Date_const_interface // Eventually rename to Date_const
{
 public:
   contribute_ const Date_format *format; // Not owned
 public: // structors
   Date_const_abstract();
 public: // accessors
   bool is_relative()                                              affirmation_;
   /*170428 appears to be obsolete
   virtual bool is_1_based()                                       affirmation_;
   */
 protected:
   //NYI const nat8 *get_month_lengths()                                        const;
      // for current_year
   virtual const nat8 *get_month_lengths_in_year(Year year)               const;
   nat8 get_days_in_month(Year year,Month month)                          const;
 public: // accessors
   virtual Days_of_week day_of_week()                                     const;
      ///< \returns the day of week (see days_of_week)
   virtual Year         get_year()                                        const;
      ///< \returns the year from the date
   virtual DOY get_DOY()                                                  const;
      ///< \returns the day of year from the date
   virtual Month get_month()                                              const;
   virtual DOM   get_DOM()                                                const;
   virtual void gregorian(Year &year, Month &month, DOM &dom)             const;
   virtual bool is_leap_year(Year year)                            affirmation_;
   virtual bool is_leap_this_year()                                affirmation_;
   virtual nat16 days_in_year(Year year)                                  const;
   virtual nat16 days_in_this_year()                                      const;
   virtual DOM days_in_month()                                            const;
 public: // math
   virtual nat32 days_between
      (const Date_const_interface &date2,bool inclusive=false)     calculation_;
   virtual int32 days_to(const Date_const_interface &date2)        calculation_;
   /*170430 unsued
   virtual bool within_period
      (const Date_interface &earliest_date
      ,const Date_interface &latest_date)                           affiration_;
   */
 public: // string conversion
   virtual void prefer_date_format(const Date_format *format=0)   contribution_;
   virtual const std::string &append_to_string(std::string &target)       const;
};
//______________________________________________________________________________
class Date_abstract
: public extends_ Date_const_abstract
//170525 , public implements_ Date_mod_interface
, public implements_ Date_interface
//170524 : public implements_ Date_interface // Eventually rename to Date
{
 public: // structors
   Date_abstract();
 public: // accessors
   /*170428 appears to be obsolete
   virtual bool is_1_based()                                       affirmation_;
   */
 public: // assignation
   virtual Datetime64 set_now()                                    assignation_;
   inline virtual Datetime64 set_DOY(DOY doy)                      assignation_
      { return set_YD(get_year(),doy); }                                         //030713
   inline virtual Datetime64 set_year(Year year)                   assignation_
      { return set_YD(year,get_DOY()); }                                         //030713
   virtual Datetime64 set_c_str(const char *date_str)              assignation_;
   //NYI virtual Datetime64 set_string(const std::string &date_string)   assignation_;
   virtual Datetime64 set_YMD(Year year,Month month,DOM dom)       assignation_;
      // takes year month and day of month and generates a Date date
   virtual Datetime64 set_month(Month month)                       assignation_;
   virtual Datetime64 set_DOM(DOM dom)                             assignation_;
   virtual Datetime64 clear()                                      assignation_;
 public: // autoincrement
   virtual Datetime64 inc_years(int16 years)                      modification_;
   virtual Datetime64 dec_years(int16 years)                      modification_;
   virtual Datetime64 inc_months(int16 month)                     modification_;
   virtual Datetime64 dec_months(int16 months)                    modification_;
   virtual Datetime64 inc_days(int32 days)                        modification_;
   virtual Datetime64 dec_days(int32 days)                        modification_;
//      { return this->inc_days(-days); }
   virtual Datetime64  inc_day()                                  modification_;
      // Adds days to the date incrementing the year if necessary.
      // If offset is negative, offset days are subtracted.
   virtual Datetime64 dec_day()                                   modification_;
};
//_2017-04-26____________________________________________________Date_abstract_/

} // namespace CORN
// Roger Nelson rnelson@wsu.edu

#endif
