//---------------------------------------------------------------------------
#include "VIC_forcing_reader.h"
//---------------------------------------------------------------------------
#include "corn/format/binary/binary_file_fstream.h"
#include "corn/datetime/date.hpp"
//______________________________________________________________________________
bool read_VIC_forcing_file_line
(CORN::Binary_file_fstream &forcing_file
,const CORN::Date &record_date
,nat16 earliest_filter_year
,nat16 latest_filter_year
,float32 &precip
,float32 &tmax
,float32 &tmin
,float32 &wind)
{

      int16 precip_scaled = forcing_file.read_int16();
      int16 tmax_scaled   = forcing_file.read_int16();
      int16 tmin_scaled   = forcing_file.read_int16();
      int16 wind_scaled   = forcing_file.read_int16();
//      int16 Srad_scaled = forcing_file.read_int16();

      precip = (float32)precip_scaled /  40.0;
      tmax   = (float32)tmax_scaled   / 100.0;
      tmin   = (float32)tmin_scaled   / 100.0;
      wind   = (float32)wind_scaled   / 100.0;
//      float32 Srad   = (float32)Srad_scaled   / 100.0;

   return true;
};
//______________________________________________________________________________
