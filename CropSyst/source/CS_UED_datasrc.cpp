#include "options.h"
#include "csvc.h"
#include "UED/library/varrec.h"
#include "UED/library/timeqry.h"
#include "CS_UED_datasrc.h"
#include "common/recorder/recorder.h"
#include "common/recorder/recorder_datarec.h"

#include <stdio.h> // for debug only

#define CROPSYST_major_version   1
#define CROPSYST_minor_version   10
//______________________________________________________________________________
CS_output_variable_layout &lookup_output_variable_definition(CS_UED_variable_code cs_var_code)
{  for (int i = 0; CS_output_variables[i].code; i++)
      if (CS_output_variables[i].code == (cs_var_code/* & 0xFFFFFF00*/))
         return CS_output_variables[i];
   return CS_output_variables[0];   // Warning, should return a dummy variable
}
//------------------------------------------------------------------------------
bool CropSyst_UED_data_source::get(Data_record &/* NYI data_rec*/ )
{  return true;
}
//-2001-01-03-------------------------------------------------------------------
bool CropSyst_UED_data_source::set_data(Data_record &data_rec,bool append)       //170216
{  Recorder_data_record &CS_record = (Recorder_data_record &)data_rec;
   datetime64 low_date (CORN::Date_clad_32 (CS_record.date_time.get_year(),(DOY)1).get_datetime64());  //010216
   datetime64 high_date(CORN::Date_clad_32 (CS_record.date_time.get_year(),CS_record.date_time.days_in_this_year()).get_datetime64()); //130313_010216
   UED::Time_query time_query(CS_record.date_time.get_datetime64(),low_date,high_date,UED::Time_query::at); //010216
   FOR_EACH_IN(section,VV_Section,data_rec.sections,each_section)                //030709
   {  //for each entry in current section
      FOR_EACH_IN(entry,Recorder_float64,section->entries,each_entry)            //030709
      {  // lookup field in actual fields:
         CORN::Units_code preferred_units =  entry->get_value_units_code();
         CORN::Quality_clad attribute(simulated_quality);
         bool created = false;
         float32  store_value = entry->get_value();
         UED_file.set_value(store_value,time_query,preferred_units,attribute,(UED::Data_record_creation_layout &)(*entry),created ,true  );
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return true;
}
//_2001-02-14___________________________________________________________________
