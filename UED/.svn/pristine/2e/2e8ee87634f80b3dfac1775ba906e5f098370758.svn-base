#ifndef CANADIAN_CLIMATOLOGICAL_CONVERTOR_H
#define CANADIAN_CLIMATOLOGICAL_CONVERTOR_H

#include "UED/convert/convertor.h"
#define Element uint16

#include <corn/data_source/dbase_datasrc.h>
namespace canadian_climatological_convertor_NS
{
//______________________________________________________________________________
Forward declarations
class Canadian_daily_by_month_data_record;
class Canadian_hourly_data_record;
class Canadian_15min_data_record;
//______________________________________________________________________________
class Canadian_climatological_format_convertor
: public UED_convertor                                                           //060616
{
   std::string       export_station_ID; // used for export          //031208_060616  check how used migh be obsolete
public:  // constructor
   Canadian_climatological_format_convertor
      (int argc, const char *argv[]);                                            //060616
   virtual int convert();
   virtual uint32 perform_import();
   virtual uint32 perform_export();
private:
   //NYI /*_______*/    Unidirectional_list  pending_export_annual_records;  Not yet implemented because monthly not needed yet

   // I am now using arrays to help cut down on the number of records scanned.
   // There is no logical reason for arrays by month or day
   // it is simply a convenient index that doesn't require resizing the array.   //040104
   bool export_month_daily_records_encountered;                                  //040104
   bool export_day_hourly_records_encountered;                                   //040104
   bool export_day_15min_records_encountered;                                    //040104
   Binary_tree pending_export_month_daily_records[13];  // 1 based
   Binary_tree pending_export_day_hourly_records[367];  // 1 based
   Binary_tree pending_export_day_15min_records[367];  // 1 based

   //NYI/*_______*/    xxxx get_monthly_record(datetime64 date_time);
   // These methods lookup the pending export records creating the a record to store the date/time as needed
   Canadian_daily_by_month_data_record *get_month_daily_record(Element search_element,const Date_time_64 &date_time);
   Canadian_hourly_data_record         *get_day_hourly_record(Element search_element,const Date_time_64 &date_time);
   Canadian_15min_data_record          *get_day_15min_record(Element search_element,const Date_time_64 &date_time);
   void append_or_update_record
      (UED_indexed_database *ued_file
      ,UED_data_record      *ued_record);
  inline virtual uint16 get_version()                                      const { return 0x0100; };
  inline virtual const char *get_application_name()                        const
      { return "Canadian Climatological UED import utility (Roger Nelson rnelson@wsu.edu"; };
};
//______________________________________________________________________________
}
//______________________________________________________________________________
#endif

