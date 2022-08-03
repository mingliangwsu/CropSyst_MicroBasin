#include "corn/chronometry/date_32.h"
namespace CORN
{
//______________________________________________________________________________
Date_clad_32::Date_clad_32()
   : Date_clad<date32>()
   {}
Date_clad_32::Date_clad_32(date32 date_raw)
   : Date_clad<date32>(date_raw)
   {}
Date_clad_32::Date_clad_32(const Date_clad_32 &other)
   : Date_clad<date32>(other.get_date32())
   {}
Date_clad_32::Date_clad_32(const Temporal &other)
   : Date_clad<date32>(other.get_date32())
   {}
Date_clad_32::Date_clad_32(Year year, DOY doy)
   : Date_clad<date32>(year,doy)
   {}
Date_clad_32::Date_clad_32(Year year, Month month, DOM dom)                      //170717
: Date_clad<date32>(year,month,dom)
{}
//________________________________________________________________constructors_/
} // namespace CORN
