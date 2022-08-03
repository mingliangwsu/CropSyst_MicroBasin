#include <common/weather/wthrdata.h>
#include <corn/measure/measures.h>
#include <corn/math/compare.h>
#include <CropSyst/cpp/LADSS_datasrc.h>
#include <corn/format/datarec.h>
#include <corn/file_sys/smart_dirname.h>

enum SR_selection
{SR_solar_radiation
,SR_woodward
,SR_woodward_mean
,SR_campbell_donatelli
,SR_donatelli_bellocchi
,SR_COUNT
};
const char *SR_selection_label_table[] =
{ "SR_ACT"  //"solar_radiation"
, "SR_W"    //"sr_woodward"
, "SR_WM"   //"sr_woodward_mean"
, "SR_CD"   //"sr_campbell_donatelli"
, "SR_DB"   //"sr_donatelli_bellocchi"
, 0
};
DECLARE_LABELED_ENUM(SR_selection_labeled,SR_selection,SR_selection_label_table)

/*_______*/ using_namespace_CORN;
/*_______*/
/*_______*/ class LADSS_climate_data_record
/*_______*/ : public Data_record
/*_______*/ {
/*_______*/ public:
/*_______*/    // CLIM_ID not used
/*_______*/    CORN::Date     clim_date;
/*_______*/    float32        precipitation;           // mm
/*_______*/    float32        max_temp;                // deg C
/*_______*/    float32        min_temp;                // deg C
/*_______*/    float32        solar_radiation;        // ((MJ/m²)/day),
/*_______*/    // EMPIRICAL_CLOUD_FACTOR  not used
/*031215_*/    float32        sr_woodward;             // ((MJ/m²)/day),
/*031215_*/    float32        sr_woodward_mean;             // ((MJ/m²)/day),
/*031215_*/    float32        sr_campbell_donatelli;   // ((MJ/m²)/day),
/*031215_*/    float32        sr_donatelli_bellocchi;  // ((MJ/m²)/day),
/*_______*/    float32        max_relative_humidity;  // %
/*_______*/    float32        min_relative_humidity;  // %
/*_______*/    float32        windspeed;              // m/sec
/*_______*/    // SUNSHINE_HOURS not used
/*_______*/    // tranmissivity not used
/*_______*/    int32          loc_ID;
/*_______*/ public:
/*_______*/    LADSS_climate_data_record()
/*_______*/    : Data_record("CLIMATE")  // Primary section not significant in LADSS
/*_______*/    {} ;
/*_______*/
/*_______*/    virtual void expect_structure(bool for_write);
/*_______*/ };


/*_______*/ class LADSS_climate_data_source
/*_______*/ : public Database_data_source
/*_______*/ {
/*_______*/ public:
/*_______*/    LADSS_climate_data_source();
/*_______*/ };


/*_______*/ void LADSS_climate_data_record::expect_structure(bool for_write)
/*_______*/ {
/*030207_*/	   Data_record::expect_structure(for_write);
/*030128_*/    set_current_section("CLIMATE");
/*_______*/    expect_date("CLIM_DATE",clim_date);
/*_______*/    expect_float32("PRECIPITATION",precipitation);
/*_______*/    expect_float32("MAX_TEMP",max_temp);
/*_______*/    expect_float32("MIN_TEMP",min_temp);
/*_______*/    expect_float32("SOLAR_RADIATION",solar_radiation);

/*031215_*/    expect_float32("SR_WOODWARD",sr_woodward);             // ((MJ/m²)/day),
/*031215_*/    expect_float32("SR_WOODWARD_MEAN",sr_woodward_mean);             // ((MJ/m²)/day),
/*031215_*/    expect_float32("SR_CAMPBELL_DONATELLI",sr_campbell_donatelli);   // ((MJ/m²)/day),
/*031215_*/    expect_float32("SR_DONATELLI_BELLOCCHI",sr_donatelli_bellocchi);  // ((MJ/m²)/day),

/*_______*/    // EMPIRICAL_CLOUD_FACTOR  not used
/*_______*/    expect_float32("MAX_RELATIVE_HUMIDITY",max_relative_humidity);
/*_______*/    expect_float32("MIN_RELATIVE_HUMIDITY",min_relative_humidity);
/*_______*/    expect_float32("WINDSPEED",windspeed);
/*_______*/    // SUNSHINE_HOURS not used
/*_______*/    // tranmissivity not used
#ifdef TEMP_DISABLED
/*_______*/    expect_int32("LOC_ID",loc_ID);
#endif
               structure_defined = true; //120314
/*_______*/ };

/*_______*/ LADSS_climate_data_source::LADSS_climate_data_source()
/*_______*/ : Database_data_source(LADSS_database_schema table("CLIMATE") ,"LOC_ID"  database_session)
/*_______*/ {
/*_______*/ };

/*_______*/ void import_LADSS
/*_______*/ (Weather_data_base &to_database
/*_______*/ ,int32               loc_ID
/*031215_*/ ,const SR_selection_labeled &sr_selection
/*_______*/ ,Year                start_year
/*_______*/ ,Year                end_year
/*_______*/ )
/*_______*/ {
/*_______*/    Date starting_date(start_year,1);
/*_______*/    Date ending_date(end_year,CORN_date_days_in_year(end_year));
/*_______*/
/*_______*/    LADSS_climate_data_source LADSS_climate_datasrc;
/*_______*/
/*_______*/    LADSS_climate_data_record  ladss_climate_datarec;
/*_______*/
/*_______*/    LADSS_climate_datasrc.where_long("LOC_ID",loc_ID);
/*040401_*/    LADSS_climate_datasrc.order_by("CLIM_DATE");
/*_______*/    bool valid = LADSS_climate_datasrc.get(ladss_climate_datarec);
/*_______*/
/*_______*/    while (valid)
/*_______*/    {
#ifdef DEBUGGING_ONLY
cout << ladss_climate_datarec.loc_ID << endl;
cout << ladss_climate_datarec.clim_date << endl;

cout << "PRECIPITATION        :"<<ladss_climate_datarec.precipitation<< endl;
cout << "MAX_TEMP             :"<<ladss_climate_datarec.max_temp<< endl;
cout << "MIN_TEMP             :"<<ladss_climate_datarec.min_temp<< endl;
cout << "SOLAR_RADIATION      :"<<ladss_climate_datarec.solar_radiation<< endl;
/*_______*/    // EMPIRICAL_CLOUD_FACTOR  not used
/*_______*/    // SR_WOODWARD not used
/*_______*/    // SR_CAMPBELL_DONATELLI not used
/*_______*/    // SR_DONATELLI_BELLOCCHI not used
cout << "MAX_RELATIVE_HUMIDITY:"<<ladss_climate_datarec.max_relative_humidity<< endl;
cout << "MIN_RELATIVE_HUMIDITY:"<<ladss_climate_datarec.min_relative_humidity<< endl;
cout << "WINDSPEED            :"<<ladss_climate_datarec.windspeed<< endl;
#endif

/*_______*/       if ((ladss_climate_datarec.clim_date >= starting_date) &&
/*_______*/           (ladss_climate_datarec.clim_date <= ending_date))
/*_______*/       {
/*_______*/          CORN::Quality_code   max_temperature_quality = UED_real;
/*_______*/          CORN::Quality_code   min_temperature_quality = UED_real;
/*_______*/          CORN::Quality_code   solar_radiation_quality = UED_real;
/*_______*/          CORN::Quality_code   max_relative_humidity_quality = UED_real;
/*_______*/          CORN::Quality_code   min_relative_humidity_quality = UED_real;
/*_______*/          CORN::Quality_code   precipitation_quality = UED_real;
/*_______*/          CORN::Quality_code   wind_speed_quality = UED_real;
/*_______*/          CORN::Quality_code   max_dew_point_temperature_quality = UED_real;
/*_______*/          CORN::Quality_code   min_dew_point_temperature_quality = UED_real;
/*_______*/
/*031215_*/          float32 solar_rad = 0.0;
/*031215_*/          switch (sr_selection.get())
/*031215_*/          {  case SR_solar_radiation       : solar_rad = ladss_climate_datarec.solar_radiation;        break;
/*031215_*/             case SR_woodward              : solar_rad = ladss_climate_datarec.sr_woodward;            break;
/*031215_*/             case SR_woodward_mean         : solar_rad = ladss_climate_datarec.sr_woodward_mean;       break;
/*031215_*/             case SR_campbell_donatelli    : solar_rad = ladss_climate_datarec.sr_campbell_donatelli;  break;
/*031215_*/             case SR_donatelli_bellocchi   : solar_rad = ladss_climate_datarec.sr_donatelli_bellocchi; break;
/*031215_*/             default                       : solar_rad = ladss_climate_datarec.solar_radiation;        break;
/*031215_*/          };
/*_______*/          to_database.set_max_temperature          (ladss_climate_datarec.clim_date,ladss_climate_datarec.max_temp,max_temperature_quality);
/*_______*/          to_database.set_min_temperature          (ladss_climate_datarec.clim_date,ladss_climate_datarec.min_temp,min_temperature_quality);
/*_______*/          to_database.set_solar_radiation          (ladss_climate_datarec.clim_date,solar_rad,solar_radiation_quality);
/*_______*/          to_database.set_max_relative_humidity    (ladss_climate_datarec.clim_date,ladss_climate_datarec.max_relative_humidity,max_relative_humidity_quality);
/*_______*/          to_database.set_min_relative_humidity    (ladss_climate_datarec.clim_date,ladss_climate_datarec.min_relative_humidity,min_relative_humidity_quality);
/*_______*/          to_database.set_precipitation_mm         (ladss_climate_datarec.clim_date,ladss_climate_datarec.precipitation,precipitation_quality);
/*_______*/          to_database.set_wind_speed_m_d           (ladss_climate_datarec.clim_date,m_per_sec_to_m_per_day(ladss_climate_datarec.windspeed),wind_speed_quality);
/*_______*/       };
/*_______*/       // else the date is not to be included as specified by the command line parameters
/*_______*/       valid = LADSS_climate_datasrc.get_next(ladss_climate_datarec);
/*_______*/    };
/*_______*/ };
/*_______*/
/*_______*/ int main(int argc, char *argv[])
/*_______*/ {
/*_______*/    CORN_string          command           (argv[1]);
/*_______*/    Smart_directory_name output_dir        (argv[2]);
/*_______*/    CORN_string          loc_ID_str        (argv[3]); // CLIMATE table is fixed
/*_______*/    Year                 start_year = (atoi(argv[4]));
/*_______*/    Year                 end_year   = (atoi(argv[5]));
/*031215_*/    const char *         solar_rad_selection     (argv[6]);
/*_______*/    const char *         LADSS_database_user_ID  (argv[7]);
/*_______*/    const char *         LADSS_database_password (argv[8]);
/*_______*/    command.to_lower();
/*031215_*/    SR_selection_labeled sr_selection(solar_rad_selection);
/*_______*/
#  ifdef LADSS_ORACLE
/*020611_*/    // In LADSS, parameters are stored in a fixed Oracle database structure.
/*020611_*/    // To use Oracle we first need to open a server session.
/*020611_*/       oracle_session = new Oracle_server_session(LADSS_database_user_ID,LADSS_database_password);
#else
// we presume the input tables will be in the same directory as the output dir
               output_dir.set_as_current_working_directory();
#  endif


/*_______*/    int32 loc_ID = atoi(loc_ID_str.c_str());
/*_______*/    CORN::Smart_file_name ued_filename(loc_ID_str.c_str());  // we give the UED file the same name as the location ID.
/*021214_*/    ued_filename.set_ext("ued");
               ued_filename.set_path(output_dir);
#ifdef unix
// fstream constructor is not creating files for some reason under Solaris
               if (!ued_filename.exists())
               {  //make sure it exists (empty) only only create if it doesn't exist
                  ofstream create_ued(ued_filename.c_str());
               };
#endif
/*_______*/    bool read_mode_of_UED_file = command != "import";
/*_______*/    Weather_data_UED *ued_database = new Weather_data_UED(ued_filename.c_str(),read_mode_of_UED_file,UED_real);
/*_______*/

/*_______*/    if (command == "import")
/*_______*/       import_LADSS(*ued_database,loc_ID,sr_selection, start_year,end_year);
/*_______*/    else
/*_______*/    {
/*_______*/       // export not needed for LADSS.
/*_______*/    };
/*_______*/
/*_______*/    delete ued_database;
/*_______*/ };

