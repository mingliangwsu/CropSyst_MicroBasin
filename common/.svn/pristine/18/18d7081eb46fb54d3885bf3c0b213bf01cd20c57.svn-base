#ifndef wthrfileH
#define wthrfileH

// experiencing a problement with BC5.0 bool type when under windows NT
/*
   This is a general object for accessing a weather file.

   One year of data is kept in memory for the weather file.

   Only real weather data can be accessed using this object.

   This class also provides simplely computed daily values
   based on data for the current day.
   For values based on data from more that one day, use the weather class.

   Under development:
   Spreadsheet weather file format:

      This format is being designed to solve the following problems with
      the text file format:
      - It is not possible to identify which format the file is without
        scanning some of the file
      - It is not possible to quickly identify the units of the columns
      - There is not indication of what columns hold what data.
      - It is not possible to tell if the file is real or generated data
        unless using the .DAT .GEN extensions as recommended by CropSyst
      - It is not permitted to have missing data.

      The format
      The columns may be arranged in any order.
      Row 1 is reserved for column labels.

      Recognized column labels (not case sensitive) are:

          Recommended     Abbrev  Acceptable
          -----------     ------  ----------
          DATE
          PRECIPITATION   PREC    substring 'PREC'
          MAXTEMPERATURE  TMAX    substrings TEMP and MAX (or MAS) any order I.e. Maximum temperature is valid
          MINTEMPERATURE  TMIN    substrings TEMP and MIN any order
          SOLARRADIATION  SRAD    substrings SOLAR and RAD any order
          VAPORPRESDEF    VPD     letters V P and D in that order I.e. Vapor pressure deficit is valid
          MAXRELHUMID     RHMAX   substrings MAX (or MAS) REL and HUM in any order
          MINRELHUMID     RHMIN   substrings MIN REL and HUM in any order
          WINDSPEED       WS      substrings WIND or VENT

      A cell in any column without a column label or a label that does
      not match one of these codes in row 1 is assumed to be a comment.

      Row 2 is reserved for units.
      The following units which are case sensitive are recognized:

          m     -  Meters
          mm    -  Millimeters
          cm    -  Centimeters
          in    -  Inchs
          C     -  Degrees Centigrade
          F     -  Degrees Farenheit
          m/s   -  Meters/Second
          MJ/m2 -  MegaJoules per square meter
          %     -  percent  1-100

        Date format designator
          If the dates have been entered as text strings (I.e. 1996/1/1),
          the date designator must be provided:

          y/m/d  y/d/m  m/d/y  or d/m/y

			 Months may be entered as numbers or month abbreviations
          (sep or spt for september) in english, french, italian, spanish
          catalan, danish, swedish or norwegian are supported at this time.

          If the dates have been entered at spread sheet date fields,
          or as yyyy.ddd the date designator can be ommited.

          The years must contain the full year I.e. 1996 not 96
          except when entered spreadsheet date values (The spreadsheet
          date type does not permit dates < 1990).

        To be added
          K     -  kelvin
          kPa   -  KiloPascals  -- or what ever radiation value this is

      Row 3 and on contain the daily data.
          Dates do not have to be specified.
          However at least the Row 3 date cell must contain a date value.
          All successive rows following a date entry are assumed to be
          days after the date.
          Leap year is always assumed to be entered correctly.

          Missing values can be left blank.
          If a value is estimated for a missing value, a comment must
          be entered in an empty cell on the row.
          I.e.      Estimated:TMax, Srad

          I.e. The ClimGen weather generator will put the comment
          'ClimGen:SRad' when the solar radiation is generated.

*/
#include "corn/const.h"
#include "corn/container/enumlist.h"
#ifndef dynamic_array_TH
#  include "corn/dynamic_array/dynamic_array_T.h"
#endif
#include "corn/measure/unitconv.h"
#include "common/weather/GEN_DAT_filename.h"
#include "corn/chronometry/date_32.h"
#define MIN_MIN_TEMP_THRESHOLD  -50.0
#define MIN_MAX_TEMP_THRESHOLD  -40.0
#ifdef CLIMGEN
#  define CG
#else
#  define CG _COMMENT_
#endif

class Solar_radiation;

extern const char *Weather_text_file_format_label_table[];
//______________________________________________________________________________
class Weather_column_data
: public Enumeration
, public CORN::Dynamic_array<float32>
, public Units_convertor
{public:
   UED::Variable_code_clad variable;
   CORN::Units_clad     units; // preferred units
   CORN::Quality_code   quality[367];
   float64              min_range;
   float64              max_range;
   float64              clean_precision;

   bool                 desired_for_output;                                      //060119_
   // When writing text file format (I.e. export)
   // we only want to write those in the desired format.
   // however, caculation ext may also add additional
   // columns we need these for storage even though we are
   // not going to write them.
 public:
   Weather_column_data
      (UED::Variable_code  variable
      ,Units_code          units
      ,float64             min_range
      ,float64             max_range
      ,float64             clean_precision);
   float64 get
      (CORN::DOY        DOY
      ,Units_code       units
      ,CORN::Quality   &quality);
   float64 set_with_quality(CORN::DOY DOY,float64 value, CORN::Quality &desired_quality,bool &modified);
   float64 set_alt_units   (CORN::DOY DOY,float64 value,Units_code i_units, CORN::Quality &desired_quality,bool &modified);
   void fixup_leap_year();
   inline void invalidate_DOY(CORN::DOY doy) {quality[doy]=CORN::unknown_quality;};  //150811_010306
   inline virtual bool is_key_nat32(nat32 key) affirmation_ { return variable.get() == key; } //180822
   inline virtual uint32 get_key_nat32()          const {return variable.get();} //020905
   inline bool set_desired_for_output()    { return desired_for_output = true;}; //060119
};
//_1999-10-13___________________________________________________________________
/*
Bit
0     DOY
1     precipitation
2     TMax
3     TMin
4     SRad
5     RHmax
6     RHmin
7     DPTmax
8     DPTmin
9     wind_speed
10    VPD
11    ET
12    snow
13    rain
14    cloud_cover
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
*/
//______________________________________________________________________________
class Weather_text_file
{  CORN::Quality_clad file_quality;                                              //991012
 public:
   GEN_DAT_UED_filename *file_name;                                              //000125
 public:
   enum Format_old                                                               //020903_980303
   {UNKNOWN_format
   ,day_precip_temp
   ,day_precip_temp_rad
   ,day_precip_temp_rad_dewpoint
   ,day_precip_temp_rad_humid      // This format is no longer available for estimated output
   ,day_precip_temp_rad_dewpoint_wind
   ,day_precip_temp_rad_humid_wind      // This format is no longer available for estimated output
   ,day_precip_temp_rad_VPD  // Special format for Mohammad Bannayan Avval
   ,END_formats
   };
 //020903       The format is now going to be dynamic
#define        V4_format UNKNOWN_format
   Year    year;  // We must have this in addition to CORN_Date because when we
                // increment year, we need to be able to trigger new year load.
 private:  // now private, use get_avg_annual_temperature
   mutable float64   avg_annual_temperature;  // 'C computed as the data is loaded.
 private:
   bool              modified;                                                      //990903
   bool              for_write;                                                     //000316
   Format_old        V3_write_format; // for CropSyst and ClimGen V3 compatibility  //021216
   CORN::Date_format date_format; // In the case where the new text format specifies a date column (I.e. YYYY/MM/DD) we record the format of the date. 060220
// The following arrays are from the data file
// If the data file does not have a value, the pointer is 0
                            //  Units       Accessor
 private:
   bool     allow_missing_dates;                                                 //040427
#define max_columns 20
#define max_column_alloc 21
    bool     headers;    // true if input files has variable and units column headers.  //020821
    uint8    columns;                                                            //020904
//             The following are in order encountered either as read from the file
//             or as variables are added with setXXX() method calls;
    mutable Enumeration_list  data_sets;  // List of Weather_column_data  Note that the data sets must be kept in order
    // The following are quick pointers to the respective data_sets items.
    mutable Weather_column_data *max_temp_data;          // C or F  The units will depend on the input format            //991013
    mutable Weather_column_data *min_temp_data;          // C or F  The units will depend on the input format            //991013
    mutable Weather_column_data *max_rel_humid_data;     // %                                                            //991013
    mutable Weather_column_data *min_rel_humid_data;     // %                                                            //991013
    mutable Weather_column_data *max_dew_point_data;     // C or F  The units will depend on the input format            //991013
    mutable Weather_column_data *min_dew_point_data;     // C or F  The units will depend on the input format            //991013
    mutable Weather_column_data *wind_speed_data;        // m/sec m/day miles/day units will depend on the input format  //991013
    mutable Weather_column_data *avg_daytime_VPD_data_kPa;           // kPa                                              //991109
    mutable Weather_column_data *avg_fullday_VPD_data_kPa;           // kPa                                              //011009
    mutable Weather_column_data *pot_ET_data;          // depth/day   // The units will depend on the input format       //991109
 public:  // public for wthr.h                                                                                            //
    mutable Weather_column_data *precip_data;          // depth // The units will depend on the input format             //991013
    mutable Weather_column_data *solar_rad_data;                                                                         //991013
//             The following lists the variables as desired for writing.
//             If null arrays are specified, variables will written as encountered above.
    Units_code    *write_units;        //   // will be null if units are to be output as stored. //020904*
 private:
   float64 avg_temp_CHECK_USED;               // C            avg_temperature()
	float64 atmos_transmit;
	float64 snow_storage;
	float64 daily_snowfall;
	float64 snow_melted;
   bool     need_to_write_column_headers; // In V4 text format we can have all data in one file  we still open the file for each year buffer, but we only need to write the headers once  //060221
   std::ofstream *single_outfile;  // if storing all data in a single output file.  Owned by caller (dont delete)    //060221
 public:
   Weather_text_file
      (const GEN_DAT_UED_filename &i_filename                                    //000125
      ,Year _year                                                                //060221
      ,bool i_for_write                                                          //000619
      ,Format_old i_V3_write_format                                              //021216
      ,bool i_allow_missing_dates                                                //040427
      ,bool _need_to_write_column_headers                                        //060221
      ,std::ofstream *_single_outfile);                                        //060221
   virtual ~Weather_text_file();                                                 //990903
   Weather_text_file();
      //             If  target_variable_order array is specified
      //             columns will be written in this order
      //             If units are specified then the stored values will be converted
      //             to these units
   inline void set_year(Year i_year)
      {  year = i_year;
         file_name->set_year(i_year);                                             //000125
      };
   virtual void invalidate_DOY(CORN::DOY doy);                                   //030106
   bool solar_radiation_is_real()                                          const;
//NYI needs to be reimplemented /*_______*/    { return (file_format >= day_precip_temp_rad); };
   float64 get_precipitation_m              (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  m                  //991013
   float64 get_max_temperature              (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  C                  //991013
   float64 get_min_temperature              (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  C                  //991013
//140716    float64 get_solar_radiation              (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  MJ/m2/day          //991013
   float64 get_solar_radiation              (CORN::DOY i_DOY, modifiable_ Solar_radiation &solar_rad)    const ; //  MJ/m2/day          //140716)991013
   float64 get_max_relative_humidity        (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  %                  //991013
   float64 get_min_relative_humidity        (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  %                  //991013
   float64 get_max_dew_point_temperature    (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  C                  //991013
   float64 get_min_dew_point_temperature    (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  C                  //991013
   float64 get_wind_speed_m_d               (CORN::DOY i_DOY, CORN::Quality &quality) const ; // m/d                 //991013
   float64 get_cloud_cover_percent          (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  %                  //991022
   float64 get_pot_evapotranspiration_m     (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  m                  //991109
   float64 get_avg_daytime_vapor_pressure_deficit_kPa   (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  kPa    //010125
   float64 get_avg_fullday_vapor_pressure_deficit_kPa   (CORN::DOY i_DOY, CORN::Quality &quality) const ; //  kPa    //011009
 public: // computed values
   void read();
 public: 	   // The following sets do not let inferior quality values to be assigned
   // The actual value set will be returned and the quality of the current value
   float64 set_precip_m     (CORN::DOY i_DOY,float64 i_precip         , CORN::Quality &quality); //  m   (stored as mm)
   float64 set_max_temp     (CORN::DOY i_DOY,float64 i_max_temp       , CORN::Quality &quality); //  C
   float64 set_min_temp     (CORN::DOY i_DOY,float64 i_min_temp       , CORN::Quality &quality); //  C
   float64 set_max_rel_humid(CORN::DOY i_DOY,float64 i_max_rel_humid  , CORN::Quality &quality); //  %
   float64 set_min_rel_humid(CORN::DOY i_DOY,float64 i_min_rel_humid  , CORN::Quality &quality); //  %
   float64 set_max_dew_point(CORN::DOY i_DOY,float64 i_max_dew_point  , CORN::Quality &quality); //  C                     //980305
   float64 set_min_dew_point(CORN::DOY i_DOY,float64 i_min_dew_point  , CORN::Quality &quality); //  C                     //980305
   float64 set_wind_speed_m_d (CORN::DOY i_DOY,float64 i_windspeed    , CORN::Quality &quality); //  m/day (stored as m/S) //______
   float64 set_solar_rad    (CORN::DOY i_DOY,float64 i_solar_rad      , CORN::Quality &quality); //  MJ/m2/day             //______
   float64 set_cloud_cover_percent(CORN::DOY i_DOY,float64 i_cloud_cover_percent , CORN::Quality &quality); //  %          //991022
   float64 set_pot_ET_m     (CORN::DOY i_DOY,float64 i_pot_ET         , CORN::Quality &quality); //  m   (stored as mm)    //______
   float64 set_daytime_VPD_kPa      (CORN::DOY i_DOY,float64 i_VPD_kPa , CORN::Quality &quality); //  kPa                  //011009
   float64 set_fullday_VPD_kPa      (CORN::DOY i_DOY,float64 i_VPD_kPa , CORN::Quality &quality); //  kPa                  //011009
   void write_ASCII();                                                                                                     //980413
   void write_ASCII_column_headers(std::ostream &outfile);                                                               //021216
   void write_ASCII_line                                                                                                   //980413
      (std::ofstream &Weather_text_file,CORN::DOY doy);
   float64  get_avg_annual_temperature() const;  // 'C computed as the data is loaded.
 private:
   DOY read_ASCII_record                                                         //040427
       (std::ifstream &in_file
       ,CORN::Date_interface /*170525 Date */ &expected_line_date    // Not const because we relax if the full date was read (V4 text files)
       ,CORN::Date_interface /*170525 Date */ &actual_line_date);
   bool read_ASCII();
   void read_column_headers                                                      //020905
      (std::ifstream &instrm);
   void identify_file_format();                                                  //020903
   void identify_old_file_format
      (std::ifstream &infile);
   bool is_english_units();
   void create_datasets_for_format                                               //021216
       (bool is_english
       ,bool has_dewpt
       ,bool has_humid
       ,bool has_solrad
       ,bool has_wind);
   Weather_column_data *get_data_set
      (UED_variable_code var_code,Units_code units_code = 0
      , bool desired_for_output =false)                               mutation_; //020905
               // Allocate if necessary
};
//______________________________________________________________________________
#endif
// wthrfile.h

