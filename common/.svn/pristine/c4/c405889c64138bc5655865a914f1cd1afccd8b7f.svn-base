#ifndef WTHRSPRD_H
#define WTHRSPRD_H
/*
   This is a general object for accessing a weather file.

   One year of data is kept in memory for the weather file.

   Only real weather data can be accessed using this object.

   This class also provides simplely computed daily values
   based on data for the current day.
   For values based on data from more that one day, use the weather class.

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

      Row 0 is reserved for year indicators
          Column 3 should have a description of the file
          (I.e. weather station ID, location etc..)
          If the file contains a single year of data,
          column 0 contains the year as an integer value (4 digits).

          When multiple years in a single file is implemented:
          If the file contains multiple years column 0 and 1 are the
             first and last year respectively
          Column 0 and column 1 are optional, but a Date column must
          then be specified.

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
          ACTEVAPORATION  ACTEVAP substring ACT and EVAP any order
          PANEVAPORATION  PANEVAP substring PAN and EVAP any order

          There might be a DOY (day of year) column, this column is
          ignored as a comment.
          DOY             DOY

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
          kelvin-  kelvin
          m/s   -  Meters/Second
          m/day -  Meters/Day
          mile/day - Miles/Day
          MJ/m2/day -  MegaJoules per square meter per day
          J/m2/day  = Joules per square meter per day
          Langley/day = Langleys per day
          kPa - kilo Pascals
          %     -  percent  1-100

        When we implement multiple years in a single file
        Date format designator
          If the dates have been entered as text strings (I.e. 1996/1/1),
          the date designator must be provided:

          y/m/d  y/d/m  m/d/y  or d/m/y or y_d

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
          When multiple years are implemented:
          If year indicators are specified dates do not have to be specified.
          If no year indicators are given, the DATE column must be given.
          With the date column, date row entries are optional,
          However at least the Row 3 date cell must contain a date value.
          All successive rows following a date entry are assumed to be
          days after the date.
          Leap year is always assumed to be entered correctly.

          Missing values should be left blank.
          If a value is estimated for a missing value, a comment must
          be entered in an empty cell on the row.
          I.e.      Estimated:TMax, Srad

          I.e. The ClimGen weather generator will put the comment
          'ClimGen:SRad' when the solar radiation is generated.
*/



#include <rlib/bsysemod/wthrvirt.h>

#include <rlib/wks_file.h>

// Any columns over 50 will be ignored
#define MAX_columns 50

#define FIRST_DATA_ROW 3
//______________________________________________________________________________
class weather_spreadsheet
{
 public:
   enum units  // valid for
   {UNITLESS
   ,m          // Precip
   ,mm         // precip
   ,cm         // precip
   ,inch       // precip
   ,C          // temperature
   ,kelvin     // temperature
   ,F          // temperature
   ,m_s        // windspeed
   ,m_day      // windspeed
   ,mile_day   // windspeed
   ,MJ_m2_day  // Solar rad
   ,J_m2_day   // Solar rad
   ,Langley_day// Solar rad
   ,percent    // Humidity
   ,kPa        // VPD
   ,y_d, y_m_d, y_d_m, m_d_y, d_m_y   // <- Date format/units (starting with y_d) must always be last!
   };

   enum labels      // When adding labels, make sure to update:
   {UNKNOWN         // - storage_units
   ,DATE            // - recommended labels
   ,PREC            // - read
   ,TMAX            // - write
   ,TMIN
   ,SRAD
   ,VPD
   ,RHMAX
   ,RHMIN
   ,WINDSPEED
   ,ACTEVAP
   ,PANEVAP
   };

   int columns;
   labels column_label[MAX_columns];
   units  column_units[MAX_columns];

 public:
/* Not currently implementing multiple year
   int first_year; // 0 if dates specified for rows (not currently implemented).
   int last_year;  // !=0 if multiple years.
*/
//   void set_DOY(int DOY) {DOY = 1; };  <- Now in RDate superclass
   // goto the current date and recompute fast access variables for the day.

   inline weather_spreadsheet()
   {
   };


   // It may be desirable to add a function set_columns(int columns, int i_column_labels[], int i_column_units[]);
   // To save the file will an new format.

   // The following are pure virtual functions which must be defined:

   //virtual void allocate_memory(); // PURE  because spreadsheed allocates based on columns
};
//______________________________________________________________________________
class weather_input_spreadsheet : public weather_spreadsheet, public weather_input_file , public WKS_input_file
{
 public:
   void preread();
   // Because spreadsheet files can be stored in either row or column major
   // order, it is necessary to preread the file to figure which columns
   // store which values in which units

   virtual void read();

   weather_input_spreadsheet(RLIB_filename &_filename);

   double convert_to_m(double value,units from_units);
   double convert_to_MJ_m2_day(double value, units from_units);
   double convert_to_C(double value, units from_units);
   double convert_to_m_day(double value , units from_units);
};
//______________________________________________________________________________
class weather_output_spreadsheet : public weather_spreadsheet, public weather_output_file, public WKS_output_file
{
 public:
   virtual void write() const;                                                   //990826
   inline weather_output_spreadsheet(RLIB_filename &_filename,int columns, int _column_labels[], int _column_units[])
      : weather_output_file(_filename)
      , WKS_output_file(_filename.c_str())
      {  create(); }
   double convert_m_to        (double value , units from_units);
   double convert_C_to        (double value , units from_units);
   double convert_MJ_m2_day_to(double value , units from_units);
   double convert_m_day_to    (double value , units from_units);
};
//______________________________________________________________________________
#endif
// wthrsprd.h

