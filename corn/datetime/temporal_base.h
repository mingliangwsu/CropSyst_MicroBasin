#ifndef temporal_baseH
#define temporal_baseH
#ifndef date_typesHPP
#  include "corn/chronometry/date_types.hpp"
#endif
#ifndef time_typesHPP
#  include "corn/chronometry/time_types.hpp"
#endif
#include "corn/const.h"
#include <string>
namespace CORN {
//____________________________________________________________________________
interface_ Temporal_base
{
 public:
   inline virtual ~Temporal_base() {}                                           //130515
      // Compilers complain when base class with virtual does not have virtual destructor
   virtual int8 temporal_compare (const Temporal_base & second_time)       const;      //030108
   virtual const std::string &append_to_string(std::string &target)        const = 0;  //140614
   virtual const std::wstring &append_to_wstring(std::wstring &target)     const;      //140919
   virtual std::string as_string()                                         const;      //140614
   virtual Datetime64 get_datetime64()                                     const = 0;  //030108
      // This returns the date, time or date time as a 64 bit float (double)           //030108
   inline virtual Date32 get_date32()                                      const       //090706
      {return (int32) get_datetime64();}
      // returns the date portion as a 32bit integer                                   //030717

   inline virtual Minutes get_minutes_after_midnight()                            const { return 7200; } // Default to noon (middle of the day)
   inline virtual DOY get_DOY()                                                   const { return 0; }
};
//____________________________________________________________________________
} // namespace CORN
#endif
// temporal_baseH

