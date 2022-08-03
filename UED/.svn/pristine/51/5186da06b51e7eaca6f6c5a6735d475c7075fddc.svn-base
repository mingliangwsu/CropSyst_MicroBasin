
#include <ued/ued.h>
#include <ued/locrec.h>
#include <ued/std_codes.h>
#include <corn/std/std_iomanip.h>
#include <corn/measure/measures.h>
#include <corn/math/compare.h>
#include <corn/file_sys/filename.h>
#include <corn/datetime/date.h>

/*_______*/ void output_RZWQM_location_header
/*_______*/ (
/*_______*/  ofstream &RZWQM_file
/*_______*/ ,UED_location_record &loc_rec
/*_______*/ ,uint16 years
/*_______*/ ,CORN::Year first_year
/*_______*/ ,uint16 years_simulated
/*_______*/ ,const CORN_string &data_set_description
/*_______*/ )
/*_______*/ {
/*_______*/    RZWQM_file
/*_______*/       << "=   Station:  "
/*_______*/ //      << loc_rec.get_station()
/*_______*/ //      << ' '
/*_______*/       << loc_rec.get_station_name()
/*_______*/       << ' '
/*_______*/       << loc_rec.get_state_name()  // warning need to convert to state code
/*_______*/       << "         CLIMGEN VERSION 4.2.0 " << data_set_description << endl;
/*_______*/
/*_______*/    RZWQM_file
/*_______*/       << "= Latitude Longitude Elevation(m)  Obs. Years   Beginning year  Years simulated" << endl;
/*_______*/
/*_______*/    RZWQM_file
/*_______*/       << "=    "
/*_______*/       << loc_rec.get_latitude_dec_deg_32()
/*_______*/       << "       "
/*_______*/       << loc_rec.get_longitude_dec_deg_32()
/*_______*/       << "        "
/*_______*/       << loc_rec.get_elevation()
/*_______*/       << "          "
/*_______*/       << years
/*_______*/       << "        "
/*_______*/       << first_year
/*_______*/       << "               "
/*_______*/       << years_simulated // indicates simulated data
/*_______*/       << endl;
/*_______*/ };
/*_______*/
/*_______*/ void UED_to_meterology
/*_______*/ (
/*_______*/  UED_indexed_database &database
/*_______*/ ,UED_location_record &loc_rec
/*_______*/ ,uint16 years
/*_______*/ ,const CORN::Date &earliest_date
/*_______*/ ,const CORN::Date &latest_date
/*_______*/ )
/*_______*/ {
/*_______*/    CORN::File_name filename_met(database.get_file_name(),"met");
/*_______*/    ofstream meterology(filename_met.c_str());
/*_______*/ 
/*_______*/    output_RZWQM_location_header
/*_______*/    (meterology,loc_rec
/*_______*/    ,years,earliest_date.get_year()
/*_______*/    ,1 // Will want to count none real data years
/*_______*/    ,"Daily Meteorology"
/*_______*/    );
/*_______*/ 
/*_______*/    meterology
/*_______*/    << "=" << endl
/*_______*/    << "=  Earliest Date     Latest Date" << endl
/*_______*/    << "=  yyyy/mm/dd        yyyy/mm/dd" << endl
/*_______*/    << "================================================================================"
/*_______*/    << endl;
/*_______*/ 
/*_______*/    earliest_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');
/*_______*/    latest_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,' ');
/*_______*/ 
/*_______*/    meterology
/*_______*/    << "   "
/*_______*/    << earliest_date
/*_______*/    << "        "
/*_______*/    << latest_date
/*_______*/    << endl
/*_______*/    << "================================================================================" << endl
/*_______*/    << "=  Daily Data" << endl
/*_______*/    << "=" << endl
/*_______*/    << "= each record contains:" << endl
/*_______*/    << "=  Julian day counted from Jan 1st, year, Tmin [C], Tmax [C]," << endl
/*_______*/    << "=  wind run [km/day], sw rad [MJ/m2/day], pan evap [cm H2O/day]," << endl
/*_______*/    << "=   relative humidity [0..100]" << endl
/*_______*/    << "=" << endl
/*_______*/    << "= ...repeat record for each day" << endl
/*_______*/    << "=" << endl
/*_______*/    << "= Day   Year    Tmin    Tmax     U      Rad   E-pan  rel hum" << endl
/*_______*/    << "================================================================================" << endl;
/*_______*/
/*_______*/    for (CORN::Date date = earliest_date
/*_______*/        ;date <= latest_date
/*_______*/        ;date++)
/*_______*/    {
/*_______*/       date.format(D_DY,D_YYYY|D_lead_space,' ');
/*_______*/ 
/*_______*/       // get the resepctive variable from the database
/*_______*/ 
//040720obs/*_______*/       UED_time_query at_date(date.get_datetime64(),UED_time_query::at);
/*040720_*/			UED_time_query_single_date at_date(date.get_datetime64());
/*_______*/ 
/*_______*/       UED_units_code tmin_units          = UC_celcius;
/*_______*/       UED_units_code tmax_units          = UC_celcius;
/*_______*/       UED_units_code U_units             = UC_kilometers_per_day_;
/*_______*/       UED_units_code rad_units           = UC_MJ_m2_solar_radiation_;
/*_______*/ //      UED_units_code e_pan_units         = XXX_units;
/*_______*/       UED_units_code max_rel_humid_units = UC_percent;
/*_______*/       UED_units_code min_rel_humid_units = UC_percent;
/*_______*/
/*_______*/       CORN::Quality_code tmin_attr          = UED_valid_attribute;
/*_______*/       CORN::Quality_code tmax_attr          = UED_valid_attribute;
/*_______*/       CORN::Quality_code U_attr             = UED_valid_attribute;
/*_______*/       CORN::Quality_code rad_attr           = UED_valid_attribute;
/*_______*/ //      CORN::Quality_code e_pan_attr         = UED_valid_attribute;
/*_______*/       CORN::Quality_code max_rel_humid_attr = UED_valid_attribute;
/*_______*/       CORN::Quality_code min_rel_humid_attr = UED_valid_attribute;
/*_______*/
/*_______*/       float tmax           = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_max_temperature.get(),at_date,UC_celcius,tmin_attr);
/*_______*/       float tmin           = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_min_temperature.get(),at_date,UC_celcius,tmax_attr);
/*_______*/       float U              = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_wind_speed.get(),at_date,UC_kilometers_per_day_,U_attr);
/*_______*/
/*_______*/ //    Warning, check that wind run conversion is correct.
/*_______*/ 
/*_______*/       float rad            = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_solar_radiation.get(),at_date,UC_MJ_m2_solar_radiation_,rad_attr);
/*_______*/       float e_pan          = 0.0;
/*_______*/       float max_rel_humid  = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_max_relative_humidity.get(),at_date,UC_percent,max_rel_humid_attr);
/*_______*/       float min_rel_humid  = database.get_no_create(UED_record_type_distinguisher::UED_data_set_year_var_units,UED_STD_VC_min_relative_humidity.get(),at_date,UC_percent,min_rel_humid_attr);
/*_______*/       float avg_rel_humid  = (max_rel_humid + min_rel_humid) / 2;
/*_______*/ 
/*_______*/       meterology << setiosflags(ios::showpoint| ios::fixed)
/*_______*/       << ' ' << setw(3)
/*_______*/       << date.get_DOY()
/*_______*/       << ' ' << setw(7)
/*_______*/       << date.get_year()
/*_______*/       << ' ' << setw(7) << setprecision(1)
/*_______*/       << tmin
/*_______*/       << ' '<< setw(7) << setprecision(1)
/*_______*/       << tmax
/*_______*/       << ' '  << setw(7) << setprecision(1)
/*_______*/       << U
/*_______*/       << ' ' << setw(7) << setprecision(2)
/*_______*/       << rad
/*_______*/       << ' '  << setw(5) << setprecision(1)
/*_______*/       << e_pan
/*_______*/       << ' '  << setw(6) << setprecision(0)
/*_______*/       << avg_rel_humid
/*_______*/       << endl;
/*_______*/    };
/*_______*/ };
/*_______*/ 
/*_______*/ void UED_to_breakpoint
/*_______*/ (
/*_______*/  UED_indexed_database &database
/*_______*/ ,UED_location_record &loc_rec
/*_______*/ ,uint16 years
/*_______*/ ,CORN::Year first_year
/*_______*/ )
/*_______*/ {
/*_______*/    CORN::File_name filename_brk(database.get_file_name(),"brk");
/*_______*/    ofstream breakpoint(filename_brk.c_str());
/*_______*/ 
/*_______*/    output_RZWQM_location_header(breakpoint,loc_rec,years,first_year
/*_______*/    ,1 // Will want to count none real data years
/*_______*/    ,"Break Point Rainfall");
/*_______*/ 
/*_______*/    breakpoint
/*_______*/       << "=" << endl
/*_______*/       << "= Rec 1: calendar code: =1 - date counted as Julian days" << endl
/*_______*/       << "= Rec 2: control info for a breakpoint event:" << endl
/*_______*/       << "=        year, date, no. breakpoints, midnight (day spanning)" << endl
/*_______*/       << "=        code, total storm depth [in]" << endl
/*_______*/       << "= Rec 3: pairs of cum storm dep [in] & clock time [min]" << endl
/*_______*/       << "=" << endl
/*_______*/       << "= REPEAT Records 2 & 3 for subsequent events" << endl
/*_______*/       << "= [ClimGen note: This file may be empty if storm events generation was not enabled.]" << endl
/*_______*/       << "================================================================================" << endl
/*_______*/       << "1" << endl;  // Indicates date stamps are with day of year
/*_______*/ 
/*_______*/     database.goto_BOF();
/*_______*/     //load each storm event interval record
/*_______*/     for (UED_data_record *data_rec = (UED_data_record *)database.goto_next_data_record()
/*_______*/         ;data_rec
/*_______*/         ;data_rec = (UED_data_record *)database.goto_next_data_record()
/*_______*/         )
/*_______*/     {
/*_______*/       if ((data_rec->get_variable_code() == UED_STD_VC_precipitation.get()))
/*_______*/       if (
/*_______*/           (data_rec->get_code() == UED_record_type_distinguisher::UED_data_set_date_time_var_units))
/*_______*/       {
/*_______*/ 
/*_______*/          CORN::Dynamic_float_array   &precip_intervals = data_rec->get_data_values();
/*_______*/          CORN::Date_time_64 record_date(data_rec->get_time_stamp()/*get_date_time()*/);
/*_______*/          breakpoint
/*_______*/             << ' ' // SPACER for FORTRAN
/*_______*/             << record_date.get_year()
/*_______*/             << "  "
/*_______*/             << record_date.get_DOY()
/*_______*/             << ' '
/*_______*/             << (precip_intervals.get_count() + 1)
/*_______*/             << " 0 "
/*_______*/             << ' '  << setw(7) << setprecision(4)
/*_______*/             << mm_to_inch(precip_intervals.sum())  // total precip
/*_______*/             << endl;
/*_______*/ 
/*_______*/          CORN_minutes minutes_from_midnite = record_date.get_minutes();
/*_______*/          breakpoint << "        "
/*_______*/             << "0.0"
/*_______*/             << ' ' << setw(7) << setprecision(4)
/*_______*/             << (float)(minutes_from_midnite);
/*_______*/ 
/*_______*/          // determine precip interval duration in minutes;
/*_______*/ 
/*_______*/          CORN_minutes interval_duration = data_rec->get_time_step_units_code() - UT_0_minutes;
/*_______*/ 
/*_______*/          for (int i = 0; i < precip_intervals.get_count(); i++)
/*_______*/          {
/*_______*/             minutes_from_midnite += interval_duration;
/*_______*/             breakpoint << "   "
/*_______*/                << mm_to_inch( i == 0
/*_______*/                 ?  precip_intervals.get_no_resize(0)
/*_______*/                 :  precip_intervals.sum(i) )
/*_______*/                << ' ' << setw(5) << setprecision(4)
/*_______*/                << (float)minutes_from_midnite;
/*_______*/          };
/*_______*/          breakpoint << endl;
/*_______*/       };
/*_______*/    };
/*_______*/ };
/*_______*/ 
/*_______*/ int main(int argc, char *argv[])
/*_______*/ {
/*_______*/    // should have precip, tmax, tmin, rel humid (max/min) , wind speed daily records
/*_______*/    // storm interval records
/*_______*/
/*_______*/    // Args
/*_______*/    // 1  import/export   Import not yet implemented
/*_______*/    // 2  database.UED
/*_______*/    // 3  start year
/*_______*/    // 4  end year
/*_______*/
//060106_//    Example import command lines
//060106_//    export "C:\temp\ClimGen_assist\Marquez\6034075.ued" 0 9999
//060106_//
/*_______*/    CORN_string       command(argv[1]);
/*_______*/ 	const char *database_filename = argv[2];
/*_______*/    CORN::Year         start_year = (atoi(argv[3]));
/*_______*/    CORN::Year         end_year = (atoi(argv[4]));
/*_______*/
/*_______*/    bool read_mode_of_UED_file = command != "import";
/*_______*/    UED_indexed_database database(database_filename,read_mode_of_UED_file);
/*_______*/    database.initialize();
/*_______*/    database.goto_BOF();
/*_______*/
/*_______*/    if (command == "export")
/*_______*/    {
/*_______*/       Date_time_64 earliest_date_time(database.get_earliest_date_time());
/*_______*/       Date_time_64 latest_date_time(database.get_latest_date_time());
/*_______*/
/*_______*/       Year earliest_year = earliest_date_time.get_year();
/*_______*/       Year latest_year   =  latest_date_time.get_year();
/*_______*/ 
/*_______*/       // Limit period to user selection, but also to data available
/*_______*/       earliest_year = CORN_max(start_year,earliest_year);
/*_______*/       latest_year   = CORN_min(latest_year,end_year);
/*_______*/ 
/*_______*/       Date export_start_date(earliest_year,1);
/*_______*/       Date export_end_date(latest_year,CORN_date_days_in_year(latest_year));
/*_______*/ 
/*_______*/       uint16 available_years = latest_year - earliest_year + 1;
/*_______*/ 
/*_______*/       // read the database location record.
/*_______*/       UED_location_record *loc_rec = 0;
/*_______*/       database.goto_BOF();
/*_______*/       loc_rec = (UED_location_record *)database.goto_next(UED_location_information);
/*_______*/       if (loc_rec)
/*_______*/       UED_to_breakpoint(database,*loc_rec,available_years,earliest_year);
/*_______*/
/*_______*/       // Need to reload loc rec
/*_______*/       database.goto_BOF();
/*_______*/       loc_rec = (UED_location_record *)database.goto_next(UED_location_information);
/*_______*/       if (loc_rec)
/*_______*/       UED_to_meterology(database,*loc_rec,available_years,export_start_date,export_end_date);
/*_______*/    }
/*_______*/    // else  import  (not yet implemented)
/*_______*/ };

