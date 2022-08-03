// UED_simple_MSVC_NET.h

#pragma once

#include <UED/library/database_file.h>
#include <string>

// Use only managed C++ in this code!

using namespace System;

namespace UED_simple
{
	public ref class Database
	{
       mutable UED::Database_file_indexed *UED_db ;

      unsigned long latest_units;
      unsigned long latest_status;
	  CORN::Quality *latest_quality;  //110926 unsigned long latest_quality;
   private: //contributes  geolocation accessor return buffers
      UED::Geolocation_record *geoloc_rec;
   public: // construtor
      //Database(const char *UED_filename);
	   
	   Database(System::String ^UED_filename);
      virtual ~Database();
      //void finish();
      void close();
   public: // methods
      double get_earliest_date_time();
      double get_latest_date_time() ;
      /*
         Returns the earliest and latest time stamp encountered in the database
         The integer part of the returned double is the year and day of year.
         I.e.  2003001 is Jan 1, 2003.
         The fraction part of the returned double is the time.

            0 is midnight
            1 second after midnight is 1/86400

            1:00am is 1/24
      */
      bool set_geolocation
         (double latitude_dec_deg    // Input in degrees, minutes decimal
         ,double longitude_dec_deg   // Input in degrees, minutes decimal   
         ,double elevation           // meters                               
         ,double screening_height    // m   The wind measurement  
         ,System::String ^station_ID    // number or code identifying the station
         ,System::String ^station_name  // longer full text name of the station
         ,System::String ^country
         ,System::String ^state_or_province
         ,System::String ^county
         ,System::String ^comment);       // Additional comments
      /* The Station ID is required,
         The descriptive name is recommended
         The geopolitical details and comment are optional
      */
      
      double get_geolocation_latitude_dec_deg();
      double get_geolocation_longitude_dec_deg();
      double get_geolocation_elevation_m();
      double get_geolocation_screening_height_m();
      System::String ^ get_geolocation_station_ID();
      System::String ^ get_geolocation_station_name();
      System::String ^ get_geolocation_country();
      System::String ^ get_geolocation_state_or_province();
      System::String ^ get_geolocation_county();
      System::String ^ get_geolocation_comment();
      

      bool get_period(bool next,double at_date,  nat32 &consider_options, double &start_date_time, double &end_date_time, unsigned long &application_code, unsigned long &enumeration, unsigned long &index, unsigned long &variable_code, char *description, unsigned long max_description_length);
      /* Returns true period if a period matching application code, enumeration, index and variable is found (as specified in consider options).
         Returns false if no period is found.

         The formal parameter (arguments) list for both get_period and set_period are very similar.
         get_period() arguments are pass by reference.
         The values assigned to the get_period arguments should be initialized with the values 
           the get_period function will use to search for a matching period.
         The consider_options parameter specifies which of the parameters are to be compared.
         On return from get_period, the parameters will be set to the values of a period found that matches the search criteria.
         
         The arguments are as follows.
         next
            This argument allows retrieving multiple periods matching the search criteria.
            Use false to search for the first matching period
            Use true to continue the search for successive matching periods. This is usually used within a loop until get_period returns 0.
         at_date 
            If at_date is 0, any date matching the considered options and arguments will be selected.
            If at_date is assigned, then the selection will be limited to periods within which date date falls.
         The following options are both input and output
            On input, this can be used to limited selecting match of the periods according to the specified by consider_options.
            (Use 0 if no consideration is to be made in the selection search).
            On output they return the respective period values and options
            which will be set to 0 if no matching period is found.
         consider_options (See description below)
            You must pass a non 0 value to this parameter.
         start_date_time and/or end_date_time are returned output values.
            These may be one and/or the other set to 0.
            On output, one or both (according to the consider options) will be set to the bounding date times if a matching period is found.
            These are pass by reference, do not try to pass literal constants.
         application_code,enumeration,index and variable_code
            This are used to match the application period code, subcodes and indexing 
            when the respective consider_options are used 
               UED_period_application_code_option,UED_period_enumeration_option, 
               UED_period_index_option, UED_period_variable_code_option.
            
            For CropSyst these selections have the following meaning and values

               Application code          Enumeration code            Index                   Variable_code
               SIMULATION_PERIOD    = 0  (always 0)                  (always 0)              (always 0)
               GROWING_SEASON_PERIOD= 1  (always 0)                  1 based season count    0x80210000
               GROWTH_STAGE_PERIOD  = 2  CropSyst growth stage:      1 based season count    0x8021000e
                                          NGS_SOWING        = 0
                                          NGS_EMERGENCE     = 1
                                          NGS_RESTART       = 2
                                          NGS_ACTIVE_GROWTH = 3
                                          NGS_FLOWERING     = 4
                                          NGS_FILLING       = 5
                                          (reserved)        = 6
                                          (reserved)        = 7
                                          NGS_MATURITY      = 8
                                          NGS_DORMANT       = 9
                                          NGS_HARVESTABLE   = 10
                                          NGS_TERMINATE     = 11

               MANAGEMENT_PERIOD    = 3  CropSyst operation code:    (This is not yet implemented)

         description is text description of the period.
            This is a null terminated character array.
            For the get_period() method:
               The description field is not used as a comparison for searching, even if UED_description_option is included in consider_options.
               It is returned only as output.
               If 0 (null array) is passed, the description will not be assigned as a return value.
               You must pass a character array buffer.
               Also pass the maximum number of characters that can be copied into the desription buffer (the size of the description array )
            For the set_period_method():
               If 0 (null array) is passed and description 
         
         So, to get the second growing season period your would call would be :
         
         nat32 consider_options 
           = UED_period_application_code_option //   We need specifically the GROWING_SEASON_PERIOD
           | UED_period_index_option;
           
         double crop_season_start_datetime = 0;
         double crop_season_end_datetime = 0;
         unsigned long application_code = GROWING_SEASON_PERIOD;  
         unsigned long enumeration = 0;   // There are no enumeration values for the corresponding  GROWING_SEASON_PERIOD
         unsigned long index = 2;         // For season 2
         unsigned long variable_code = 0; // We don't really need to select the variable code is always the same and will be assigned by CropSyst
         char description_dPtr[1000];                                // For C++ only 
         sbyte[] description_sbArray = new sbyte[1000];              // For C# only
         fixed (sbyte* description_dPtr = & description_sbArray[0])  // For C# only
         {
            bool period_found = get_period
            ( false     // Start a new search (also there will only be one period for each season, the Index argument will be used to select the season)
            , 0         // Set at_date to 0 because we want to find the period for a known season, we don't want to retrieve a period for this date.
            , consider_options
            , crop_season_start_datetime
            , crop_season_end_datetime
            , application_code
            , enumeration
            , index
            , variable_code
            , description_dPtr
            , 1000
            );
         }
      */

      bool set_period(nat32 consider_options,double start_date_time, double end_date_time, unsigned long application_code, unsigned long enumeration, unsigned long index, unsigned long variable_code,const char *description);
      // Either appends or updates (an existing period record) with the specified attributes.
      // Returns true if the record is updated or appended (successful), else false.

      /* For the xxx_period() methods, the arguments are as follows:
            consider_options argument is one or of the following | or'ed:

            public const uint UED_period_start_time_option        = 0x01;
            public const uint UED_period_start_date_option        = 0x02;
            public const uint UED_period_start_date_time_option   = 0x03;
            public const uint UED_period_end_time_option          = 0x04;
            public const uint UED_period_end_date_option          = 0x08;
            public const uint UED_period_end_date_time_option     = 0x0C;
            public const uint UED_period_application_code_option  = 0x10;
            public const uint UED_period_enumeration_option       = 0x20;
            public const uint UED_period_index_option             = 0x40;
            public const uint UED_period_variable_code_option     = 0x80;
      */
/* disabled
      unsigned long copy_periods_to_database(Database &target_database);
      // Copies all periods from this database to the specified target database.
*/
      float get_for_date(signed long date, unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status) ;
      // date is in date32 integer format

      float get_for_date_quick(signed long date, unsigned long variable_code, unsigned long units_code) ;
      // date is in date32 integer format

      float get_for_year(signed int year,  unsigned long variable_code, unsigned long &units_code,unsigned long &quality,unsigned long &status) ;
      float get_for_year_quick(signed int year, unsigned long variable_code, unsigned long units_code) ;
      // year is a 16 bit integer format

      float get_for_date_vector(unsigned long index, signed long date, unsigned long variable_code, unsigned long &units_code, unsigned long &quality,unsigned long &status);
      

      /* For all the get_XXXX() methods,
         the method returns the the value for the specified variable on the specified date in the specified units.

         It also returns the quality of the data and the status of the value.
         You should always check the quality of the data returned.

         The get_XXXX_quick() version does not require the quality and status return parameters.
         The actual units, the quality and the status can be retrieved with the get_last_XXX() methods

         The vector get_for_date_vector  methods
         return the values for the matching vector element at index.
         If the index exceeds the number of elements in the vector,
         0 is the value returned, the quality is set to not_valid, and the status is set a none 0 value.
         There is no 'quick' form  for get_for_date_vector because of the possibility of exceeding the vector size
         with the index parameter.
         

      */

      unsigned long get_last_units()  ;
      unsigned long get_last_quality() ;
      unsigned long get_last_status() ;
      const char *get_units_abbreviation(unsigned long units_code);
     
      float set_for_date(float value, signed long date, unsigned long variable_code, unsigned long units_code,unsigned long quality);
      float set_for_date_scalar(float value, signed long date, unsigned long variable_code, unsigned long units_code,unsigned long quality);
      float set_for_year(float value, signed int year, unsigned long variable_code, unsigned long units_code,unsigned long quality);
      // Sets the specified value for the specified date for the specified variable code, with the specified units,
      // and data quality.

      // set_for_date should be used for daily time series data
      // set_for_date_scalar should be used for sparse irregular dates (I.e. harvest and seasonal totals).
      // set_for_year should be used for annual time series data (annual time step I.e annual summaries).

      // These functions return the the value for the specified variable on the specified date in the specified units.
      // Use the functions UED_simple_get_last_units(), UED_simple_get_last_quality() and UED_simple_get_last_status()
      // to check the actual units and quality stored and the status.

      // The data may actually be stored in the database in different units
      // (Depending how values were previously stored) in this case the
      // return value will be the actual value stored and the units
      // passed in the units_code parameter will be updated to indicate the
      // units actually stored. (Generally it is not necessary to check the
      // units and returned variable after calling this function unless you
      // want to confirm the conversion was done correctly).

      // You should specify the quality of the data (0 indicate real data).
      // there may be a quality check (I.e. a check of valid range of input value)
      // Generall the quality will be the same as the passed value, but
      // the quality will be updated if the value is out of range.
      // If a data value already exists in the database the database will only
      // be updated if the specified value has a better quality than the value
      // already in the data base (an existing value of the same quality will be
      // replaced by the specified value)..
      // The value actually stored in the database (and its quality) will be returned,
      // so although, generally the returned value will be the same as the passed value,
      // the returned value will be different if there is a units conversion, or
      // the value in the database is of better quality.

      /*  For all the get...() and set...() data methods, the following notes apply

      date is the date of the data to retrieve expressed as long integer
         (year * 1000) + day_of_year
      datetime is the date and time (or simply time) (year *1000) + day_of_year + day_fraction
      where day_fraction is the timestep index divided by the number of time steps
      (I.e.  for 1:00am, the day fraction would be  1/24 (Midnight would be 0);
         1 minute after midnight would have day fraction 1/1440.)

      variable code is the UED variable code of the data to retrieve.

      units code is the desired units the value is to be returned in.
         The program can specify the desired units.
         UED will try to convert to those units, if it can't units will be set to the units available
         Use the value 0 if you don't know the units (the actual units will be returned).

      quality is the quality of the data that is returned
         0 indicates the data is real measured data,
         any quality < 128 is indicates usable data (see below)
         any quality >= 128 is an an erroneous value (see below)
      status indicates if the data was returned successfully
         0 indicates no error
         any other value should be assumed as an error (the error codes currently are not enumerated).
      */
      /* The quality codes are
      0h   measured/real
      1h   estimated/calculated  (from real)
      2h   forecasted/simulated  (from real)
      3h   generated             (from real)
      
      05h   estimated/calculated from estimated/calculated
      06h   forecasted/simulated from estimated/calculated
      07h   generated            from estimated/calculated
      08h   reserved
      09h   estimated/calculated from forecasted/simulated
      0Ah   forecasted/simulated from forecasted/simulated
      0Bh   generated            from forecasted/simulated
      0Ch   reserved
      0Dh   estimated/calculated from generated
      0Eh   forecasted/simulated from generated
      0Fh   generated            from generated

      40h   (reserved - This value is used for internal processing)

      80h   not valid
      81h   out of range
      82h   missing
      BFh   unknown quality (presumed erroneous)
      */
    private:
       UED::Geolocation_record *Database::provide_geolocation();                //120312
   };
}
