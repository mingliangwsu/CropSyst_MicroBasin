#ifndef temporalH
#define temporalH
#ifndef date_typesHPP
#  include "corn/chronometry/date_types.hpp"
#endif
#ifndef time_typesHPP
#  include "corn/chronometry/time_types.hpp"
#endif
#include "corn/const.h"
#include <string>

#define ISO_FORMAT_DATE_TIME 0,0
#define  _ISO_FORMAT_DATE_TIME ,0,0

namespace CORN {
class Date_format;
class Time_format;
//____________________________________________________________________________
interface_ Temporal
{
 public:
   inline virtual ~Temporal()                                                 {} //130515
      // Compilers complain when base class with virtual does not have virtual destructor
   virtual int8 temporal_compare (const Temporal & second_time)           const; //030108
   virtual const std::string &append_to_string
      (std::string &target
      ,const Date_format *from_date_format/*=0*/                                     //180624
      ,const Time_format *from_time_format/*=0*/)                           const=0; //180624_140614
   virtual const std::wstring &append_to_wstring(std::wstring &target)  const;   //140919
   virtual std::string as_string()                                      const;   //140614
   virtual float64 get_time64()                                         const=0; //170815
   virtual datetime64 get_datetime64()                                  const=0; //030108
      // This returns the date, time or date time as a 64 bit float (double)     //030108
   inline virtual date32 get_date32()                                   const    //090706
      {return (int32) get_datetime64();}
      // returns the date portion as a 32bit integer                             //030717
   inline virtual Minutes get_minutes_after_midnight()     const { return 7200;} // Default to noon (middle of the day)
   inline virtual Minutes get_minutes()                    const { return 7200;} //170523
   virtual DOY get_DOY()                                                const=0;

 public: // operators (these are valid interface implementations because they
      // are implemented with virtual methods.
   inline virtual bool operator <  ( const Temporal & second_date ) const { return get_datetime64() <  second_date.get_datetime64(); }
   inline virtual bool operator <= ( const Temporal & second_date ) const { return get_datetime64() <= second_date.get_datetime64(); }
   inline virtual bool operator >  ( const Temporal & second_date ) const { return get_datetime64() >  second_date.get_datetime64(); }
   inline virtual bool operator >= ( const Temporal & second_date ) const { return get_datetime64() >= second_date.get_datetime64(); }
   inline virtual bool operator == ( const Temporal & second_date ) const { return get_datetime64() == second_date.get_datetime64(); }
   inline virtual bool operator != ( const Temporal & second_date ) const { return get_datetime64() != second_date.get_datetime64(); }
   inline virtual int8 compare(const Temporal &other)               const { return temporal_compare(other);}  //170815
};
//_2017-04-30_2013-05-15______________________________________________Temporal_/
//170430 replaces Temporal_base
} // namespace CORN
#endif
// temporalH

