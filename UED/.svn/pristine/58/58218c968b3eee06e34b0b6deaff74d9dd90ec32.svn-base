
#include <ued/ued.h>
#include <ued/locrec.h>
#include <ued/std_codes.h>
//060406 #include <iomanip.h>
#include <corn/std/std_iomanip.h>

#include <corn/measures.h>
#include <corn/compare.h>

void output_CLIGEN_3_8_location_header
(
 ofstream &CLIGEN_3_8_file
,UED_location_record &loc_rec
,uint16 years
,Year first_year
,uint16 years_simulated
,const CORN_string &data_set_description
)
{
   CLIGEN_3_8_file
      << "=   Station:  "
//      << loc_rec.get_station()
//      << ' '
      << loc_rec.get_description()
      << ' '
      << loc_rec.get_state_name()  // warning need to convert to state code
      << "         CLIMGEN VERSION 3.8 " << data_set_description << endl;

   CLIGEN_3_8_file
      << "= Latitude Longitude Elevation(m)  Obs. Years   Beginning year  Years simulated" << endl;

   CLIGEN_3_8_file
      << "=    "
      << loc_rec.get_latitude()
      << "       "
      << loc_rec.get_longitude()
      << "        "
      << loc_rec.get_elevation()
      << "          "
      << years
      << "        "
      << first_year
      << "               "
      << years_simulated // indicates simulated data
      << endl;
};

void UED_to_meterology
(
 UED_indexed_database &database
,UED_location_record &loc_rec
,uint16 years
,Date &earliest_date
,Date &latest_date
)
{
   CORN::File_name filename_met(database.get_file_name(),".met");
   ofstream meterology(filename_met.c_str());

   output_CLIGEN_3_8_location_header
   (meterology,loc_rec
   ,years,earliest_date.get_year()
   ,1 // Will want to count none real data years
   ,"Daily Meteorology"
   );

   meterology
   << "=" << endl
   << "=  Earliest Date     Latest Date" << endl
   << "=  yyyy/mm/dd        yyyy/mm/dd" << endl
   << "================================================================================"
   << endl;

   earliest_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');
   latest_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');

   meterology
   << "   "
   << earliest_date
   << "        "
   << latest_date
   << endl
   << "================================================================================" << endl
   << "=  Daily Data" << endl
   << "=" << endl
   << "= each record contains:" << endl
   << "=  Julian day counted from Jan 1st, year, Tmin [C], Tmax [C]," << endl
   << "=  wind run [km/day], sw rad [MJ/m2/day], pan evap [cm H2O/day]," << endl
   << "=   relative humidity [0..100]" << endl
   << "=" << endl
   << "= ...repeat record for each day" << endl
   << "=" << endl
   << "= Day   Year    Tmin    Tmax     U      Rad   E-pan  rel hum" << endl
   << "================================================================================" << endl;

   for (Date date = earliest_date
       ;date <= latest_date
       ;date++)
   {
      date.format(D_DY,D_YYYY|D_lead_space,' ');

      // get the resepctive variable from the database

      UED_time_query at_date(date,UED_time_query::at);

      UED_units_code tmin_units          = UED_units_celcius;
      UED_units_code tmax_units          = UED_units_celcius;
      UED_units_code U_units             = UED_units_kilometers_per_day;
      UED_units_code rad_units           = UED_units_MJ_m2_solar_radiation;
//      UED_units_code e_pan_units         = XXX_units;
      UED_units_code max_rel_humid_units = UED_percent;
      UED_units_code min_rel_humid_units = UED_percent;

      CORN::Quality_code tmin_attr          = UED_valid_attribute;
      CORN::Quality_code tmax_attr          = UED_valid_attribute;
      CORN::Quality_code U_attr             = UED_valid_attribute;
      CORN::Quality_code rad_attr           = UED_valid_attribute;
//      CORN::Quality_code e_pan_attr         = UED_valid_attribute;
      CORN::Quality_code max_rel_humid_attr = UED_valid_attribute;
      CORN::Quality_code min_rel_humid_attr = UED_valid_attribute;

      float tmax           = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_max_temperature.get(),at_date,UED_units_celcius,tmin_attr);
      float tmin           = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_min_temperature.get(),at_date,UED_units_celcius,tmax_attr);
      float U              = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_wind_speed.get(),at_date,UED_units_kilometers_per_day,U_attr);

//    Warning, check that wind run conversion is correct.

      float rad            = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_solar_radiation.get(),at_date,UED_units_MJ_m2_solar_radiation,rad_attr);
      float e_pan          = 0.0;
      float max_rel_humid  = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_max_relative_humidity.get(),at_date,UED_percent,max_rel_humid_attr);
      float min_rel_humid  = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_min_relative_humidity.get(),at_date,UED_percent,min_rel_humid_attr);
      float avg_rel_humid  = (max_rel_humid + min_rel_humid) / 2;

      meterology << setiosflags(ios::showpoint| ios::fixed)
      << ' ' << setw(3)
      << date.get_DOY()
      << ' ' << setw(7)
      << date.get_year()
      << ' ' << setw(7) << setprecision(1)
      << tmin
      << ' '<< setw(7) << setprecision(1)
      << tmax
      << ' '  << setw(7) << setprecision(1)
      << U
      << ' ' << setw(7) << setprecision(2)
      << rad
      << ' '  << setw(5) << setprecision(1)
      << e_pan
      << ' '  << setw(6) << setprecision(0)
      << avg_rel_humid
      << endl;
   };
};

void UED_to_breakpoint
(
 UED_indexed_database &database
,UED_location_record &loc_rec
,uint16 years
,Year first_year
)
{
   CORN::File_name filename_brk(database.get_file_name(),".brk");
   ofstream breakpoint(filename_brk.c_str());

   output_CLIGEN_3_8_location_header(breakpoint,loc_rec,years,first_year
   ,1 // Will want to count none real data years
   ,"Break Point Rainfall");

   breakpoint
      << "=" << endl
      << "= Rec 1: calendar code: =1 - date counted as Julian days" << endl
      << "= Rec 2: control info for a breakpoint event:" << endl
      << "=        year, date, no. breakpoints, midnight (day spanning)" << endl
      << "=        code, total storm depth [in]" << endl
      << "= Rec 3: pairs of cum storm dep [in] & clock time [min]" << endl
      << "=" << endl
      << "= REPEAT Records 2 & 3 for subsequent events" << endl
      << "=" << endl
      << "================================================================================" << endl
      << "1" << endl;  // Indicates date stamps are with day of year

    database.goto_BOF();
    //load each storm event interval record
    for (UED_data_record *data_rec = (UED_data_record *)database.goto_next_data_record()
        ;data_rec
        ;data_rec = (UED_data_record *)database.goto_next_data_record()
        )
    {
      if ((data_rec->get_variable_code() == UED_STD_VC_precipitation.get())
          && (data_rec->get_code() == UED_record_type_distinguisher::UED_data_set_date_time_var_units))
      {

         Dynamic_float_array   &precip_intervals = data_rec->get_data_values();
         Date_time record_date(data_rec->get_date_time());
         breakpoint
            << ' ' // SPACER for FORTRAN
            << record_date.get_year()
            << "  "
            << record_date.get_DOY()
            << ' '
            << (precip_intervals.get_count() + 1)
            << " 0 "
            << ' '  << setw(7) << setprecision(4)
            << mm_to_inch(precip_intervals.sum())  // total precip
            << endl;

         CORN_minutes minutes_from_midnite = record_date.get_minutes();
         breakpoint << "        "
            << "0.0"
            << ' ' << setw(7) << setprecision(4)
            << (float)(minutes_from_midnite);

         // determine precip interval duration in minutes;

         CORN_minutes interval_duration = data_rec->get_time_step_units_code() - UED_time_0_minutes;

         for (int i = 0; i < precip_intervals.get_count(); i++)
         {
            minutes_from_midnite += interval_duration;
            breakpoint << "   "
               << mm_to_inch( i == 0
                ?  precip_intervals.get_no_resize(0)
                :  precip_intervals.sum(i) )
               << ' ' << setw(5) << setprecision(4)
               << (float)minutes_from_midnite;
         };
         breakpoint << endl;
      };
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
   Year         start_year = (atoi(argv[3]));
   Year         end_year = (atoi(argv[4]));

   bool read_mode_of_UED_file = command != "import";
   UED_indexed_database database(database_filename.c_str(),read_mode_of_UED_file);
   database.initialize();
   database.goto_BOF();

   if (command == "export")
   {
      Date_time_64 earliest_date_time(database.get_earliest_date_time());
      Date_time_64 latest_date_time(database.get_latest_date_time());
/*obsolete
030714 now use datetime64
      Date_time earliest_date_time;
      database.get_earliest_date_time(earliest_date_time);

      Date_time latest_date_time;
      database.get_latest_date_time(latest_date_time);
*/
      Year earliest_year = earliest_date_time.get_year();
      Year latest_year   =  latest_date_time.get_year();

      // Limit period to user selection, but also to data available
      earliest_year = CORN_max(start_year,earliest_year);
      latest_year   = CORN_min(latest_year,end_year);

      Date export_start_date(earliest_year,1);
      Date export_end_date(latest_year,CORN_date_days_in_year(latest_year));

      uint16 available_years = latest_year - earliest_year + 1;

      // read the database location record.
      UED_location_record *loc_rec = 0;
      database.goto_BOF();
      loc_rec = (UED_location_record *)database.goto_next(UED_location_information);
      if (loc_rec)
      UED_to_breakpoint(database,*loc_rec,available_years,earliest_year);

      // Need to reload loc rec
      database.goto_BOF();
      loc_rec = (UED_location_record *)database.goto_next(UED_location_information);
      if (loc_rec)
      UED_to_meterology(database,*loc_rec,available_years,export_start_date,export_end_date);
   }
   // else  export  (not yet implemented)
};

