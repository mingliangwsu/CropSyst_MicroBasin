//---------------------------------------------------------------------------
#ifndef VIC_forcing_readerH
#define VIC_forcing_readerH
#include "corn/primitive.h"
namespace CORN
{
   class Binary_file_fstream;
   class Date;
};
//---------------------------------------------------------------------------
extern bool read_VIC_forcing_file_line
(CORN::Binary_file_fstream &forcing_file
,const CORN::Date &record_date
,nat16 earliest_filter_year
,nat16 latest_filter_year
,float32 &precip
,float32 &tmax
,float32 &tmin
,float32 &wind);

#endif
