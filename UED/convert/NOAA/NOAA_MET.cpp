
#include <ued/ued.h>
#include <ued/locrec.h>
#include <ued/std_codes.h>
#include <corn/std/std_iomanip.h>
#include <corn/measure/measures.h>
#include <corn/math/compare.h>
#include <corn/file_sys/filename.h>
#include <corn/datetime/date.h>

void UED_to_meterology
(
 UED_indexed_database &database
//,UED_location_record &loc_rec
,uint16 years
,Date &earliest_date
,Date &latest_date
)
{
   CORN::File_name filename_met(database.get_file_name(),"met");
   ofstream meterology(filename_met.c_str());

   earliest_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');
   latest_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');

cout << "exporting to file:"<< filename_met << endl;

   for (CORN_date date = earliest_date
       ;date <= latest_date
       ;date++)
   {
      date.format(D_MDY,D_YY|D_M|D_lead_space,0);

      // get the resepctive variable from the database

//040720obs      UED_time_query at_date(date.get_datetime64(),UED_time_query::at);
      UED_time_query_single_date at_date(date.get_datetime64());
//030108obs      CORN_string date_str;
//030108obs      date.text_string(date_str);

      CORN::Quality_code precip_attr        = UED_valid_attribute;
      CORN::Quality_code tmin_attr          = UED_valid_attribute;
      CORN::Quality_code tmax_attr          = UED_valid_attribute;
      CORN::Quality_code U_attr             = UED_valid_attribute;
      CORN::Quality_code rad_attr           = UED_valid_attribute;
//      CORN::Quality_code e_pan_attr         = UED_valid_attribute;
      CORN::Quality_code max_rel_humid_attr = UED_valid_attribute;
      CORN::Quality_code min_rel_humid_attr = UED_valid_attribute;

      float precip         = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_precipitation.get(),at_date,UC_cm/*_depth*/,precip_attr);
      float tmin           = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_min_temperature.get(),at_date,UC_celcius,tmin_attr);
      float tmax           = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_max_temperature.get(),at_date,UC_celcius,tmin_attr);
      float tavg           = (tmax + tmin)/2.0;
      float U              = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_wind_speed.get(),at_date,UC_cm_per_second_,U_attr);

//    Warning, check that wind run conversion is correct.

      float rad            = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_solar_radiation.get(),at_date,UE_Langley_,rad_attr);
      float e_pan          = 0.0;
//      float max_rel_humid  = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_max_relative_humidity.get(),at_date,UED_percent,max_rel_humid_attr);
//      float min_rel_humid  = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_min_relative_humidity.get(),at_date,UED_percent,min_rel_humid_attr);
//      float avg_rel_humid  = (max_rel_humid + min_rel_humid) / 2;



      meterology << setiosflags(ios::showpoint| ios::fixed)
      << ' ' << date.c_str() /*030108date_str*/
      << setw(10) << setprecision(3)
      << precip
      << setw(10) << setprecision(3)
      << e_pan
      << setw(10) << setprecision(3)
      << tavg
      << setw(10) << setprecision(0)
      << (int)U
      << setw(11) << setprecision(2)
      << rad
      << endl;

date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');
cout <<  date.c_str() << "\r";

   };
};

int main(int argc, char *argv[])
{
   // should have precip, tmax, tmin, rel humid (max/min) , wind speed daily records
   // storm interval records

   // Args
   // 1  import/export
   // 2  database.UED
   // 3  start year
   // 4  end year

   CORN_string       command(argv[1]);
   CORN::File_name   database_filename(argv[2]);
   Year         start_year = 0;
   Year         end_year =   9999;
   if (argc > 3)
               start_year = (atoi(argv[3]));
   if (argc > 4)
               end_year = (atoi(argv[4]));

   bool read_mode_of_UED_file = command != "import";
   UED_indexed_database database(database_filename.c_str(),read_mode_of_UED_file);
   database.initialize();
   database.goto_BOF();

   // Import not yet implemented
   if (command == "export")
   {
      Date_time_64 earliest_date_time(database.get_earliest_date_time());
      Date_time_64 latest_date_time(database.get_latest_date_time());

      Year earliest_year = earliest_date_time.get_year();
      Year latest_year   =  latest_date_time.get_year();

      // Limit period to user selection, but also to data available
      earliest_year = CORN_max(start_year,earliest_year);
      latest_year   = CORN_min(latest_year,end_year);

      CORN_date export_start_date(earliest_year,1);
      CORN_date export_end_date(latest_year,CORN_date_days_in_year(latest_year));

      uint16 available_years = latest_year - earliest_year + 1;



      // Need to reload loc rec
      database.goto_BOF();
//      loc_rec = (UED_location_record *)database.goto_next(UED_location_information);
//      if (loc_rec)
      UED_to_meterology(database,/**loc_rec,*/available_years,export_start_date,export_end_date);
   }
   // else  export  (not yet implemented)
};

