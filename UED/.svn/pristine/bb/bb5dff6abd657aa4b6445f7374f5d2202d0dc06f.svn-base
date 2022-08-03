#ifndef IRIMO_CONVERTOR_H
#define IRIMO_CONVERTOR_H

#include <UED/convert/convertor.h>
class Weather_validator;
namespace UED
{
   class Database_file_indexed;

};

class IRIMO_convertor
: public UED_convertor
{
//ISLAMIC REPUBLIC OF IRAN
//METEOROLOGICAL ORGANIZATION (IRIMO)
private:
   enum IRIMO_Record_type
   {  IRIMO_UNKNOWN_record_type
   ,  IRIMO_wind
   ,  IRIMO_temperature
   ,  IRIMO_reletive_humidity_and_precipitation
   ,  IRIMO_soil_temp_radiation_sunshine_evaporation
   ,  IRIMO_pressure
   ,  IRIMO_cloud
   };
private:
      Weather_validator    *weather_data_validator;
      UED::Database_file_indexed *ued_file;  // The Current UED file for the monthly record being processed.
      bool                  at_next_monthly_record;
public:
   IRIMO_convertor(int argc, const char *argv[]);
   virtual uint32 perform_import();
   virtual uint32 perform_export(){ return 0; }; // Cannot be implemented, this format has 3 hour values and other elements not currently created by ClimGen or stored in UED file

   virtual uint16 get_version()                                const { return 0x0100; };
   virtual const char *get_application_name()                  const { return "IRIMO Islamic Republic of Iran Meteorologic Organization - UED import utility (Roger Nelson rnelson@wsu.edu)"; };
private:
   uint32 read_monthly_record(istream &input_file);
   IRIMO_Record_type read_month_record_header
      (istream &input_file
      ,CORN::Ustring &station_ID
      ,Year &year ,Month &month);

   bool read_monthly_wind_record_body                          (istream &input_file,UED::Database_file_indexed &ued_file,Year year,Month month);
   bool read_monthly_temperature_record_body                   (istream &input_file,UED::Database_file_indexed &ued_file,Year year,Month month);
   bool read_monthly_relative_humidity_and_precipitation_body  (istream &input_file,UED::Database_file_indexed &ued_file,Year year,Month month);
   bool read_soil_temp_radiation_sunshine_evaporation_body     (istream &input_file,UED::Database_file_indexed &ued_file,Year year,Month month);
   bool skip_to_next_monthly_record(istream &input_file);
   // reads until 1 is encountered in the first character of a line.
   // returns true if such a record is found.
   // returns false if at eof

};

#endif
