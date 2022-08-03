
#include <ued/ued.h>
#include <conio.h>

#include <ued/filefmt.h>
#include <fstream.h>

class SPAW_text_file : public tabular_text_file
{
   int16 year;
   int16 DOY;
public:

   SPAW_text_file(const CORN_filename &i_filename);
   virtual bool read_record();
   // returns true if the read succeeded

};


SPAW_text_file::SPAW_text_file(const CORN_filename &i_filename)
:tabular_text_file
(i_filename
,2
,1 // airtemp has two this will be determined below
,DELIM_SPACE
,NO_QUOTE
,UED_time_day
)
{
   char ext_str[30];
   i_filename.get_ext(ext_str);
   CORN_string ext(ext_str);
   ext.to_lower();

   if (ext == ".air")
   {
      set_variable_code(0,UED_compose_standard_variable_code(UED_time_step_max,UED_climate_air_temperature));
      set_units_code(0,UED_degrees_C);

      set_variable_code(1,UED_compose_standard_variable_code(UED_time_step_min,UED_climate_air_temperature));
      set_units_code(1,UED_degrees_C);
      columns = 2;
   };
   if (ext == ".prc")
   {
      set_variable_code(0,UED_compose_standard_variable_code(UED_time_step_sum,UED_climate_precipitation));
      set_units_code(0,UED_units_mm_water_depth);
   }
   if (ext == ".evp")
   {
      set_variable_code(0,UED_compose_standard_variable_code(UED_time_step_sum,UED_climate_pan_evaporation));
      set_units_code(0,UED_units_mm_water_depth);
   };

   if (!text_stream.good()) return;
   CORN_string description;
   description.read_line(text_stream);
   text_stream >> year;

   text_stream.close();
   text_stream.open(filename.get());
   skip_header();
   DOY = 1;
   // We leave the file pointer ready to read the first record.
};

bool SPAW_text_file::read_record()
{
   //float value1;
   //float value2;
   text_stream >> row_data[0];
   if (columns == 2)
      text_stream >> row_data[1];
#ifdef _Windows
   kbhit();
#endif
   row_date.set(year,DOY);
   DOY++;
   int16 days_in_year = CORN_date_days_in_year(year);
   return (DOY <= days_in_year) && !text_stream.eof();
};

void main(int argc, char *argv[])
{
   CORN_filename ued_filename;
   CORN_filename text_filename;

   if (argc == 1)
   {
      cout << "Enter name of SPAW input file:" << endl;
      cin >> text_filename;
      cout << "Enter name of .UED output file:" << endl;
      cin >> ued_filename;
   }
   else
   {
      text_filename.assign(argv[1]);
      ued_filename.assign(argv[2]);
   };

   ued_filename.set_ext(".ued");

   { // Do the import
      cout << "Importing" << endl;
      UED_indexed_database ued_database(ued_filename);

      {
         SPAW_text_file text_file(text_filename);
         if (text_file.good())
            ued_database.import(text_file);
         else
            cerr << "Unable to open import file:" << text_filename << endl;
      }

   };
#define X_____VERIFY
#ifdef VERIFY
   { // Verify with export
      cout << endl << "Exporting" << endl;
      UED_indexed_database ued_database(ued_filename);
      ofstream export_file("verify.txt");
/*
      CORN_date_time min_date_time(9999999L,0L);
      ued_database.get_earliest_date_time(min_date_time);
      cout << "Earliest date" << min_date_time << endl;
*/
      UED_variable_code tmax_var = UED_compose_standard_variable_code(UED_time_step_max,UED_climate_air_temperature);
      UED_variable_code tmin_var = UED_compose_standard_variable_code(UED_time_step_min,UED_climate_air_temperature);
      UED_variable_code prcp_var = UED_compose_standard_variable_code(UED_time_step_sum,UED_climate_precipitation);
      UED_units_code prcp_units = UED_units_mm_water_depth;

      UED_record_creation_layout prcp_creation_layout
      ( (UED_record_type_code)UED_record::yearly_data_set
      , prcp_var
      , prcp_units
      , UED_time_day
      , UED_valid_attribute
      , 366
      );

/* temp disabled
     { // here we test if we can add a completely new date
         CORN_date date(1970001L);
         UED_quality_attributes prefered_attribute = UED_valid_attribute; // must go inside loop
         ued_database.set(100,prcp_var,date,prcp_units,prefered_attribute,prcp_creation_layout);
      };
*/






      for (CORN_date date(1985001) ; date.get() < 1986001; date.inc())
      {
kbhit();
         cout << date << ' ' << '\r';
         UED_units_code temp_units = UED_degrees_C;
         UED_units_code prcp_units = UED_units_mm_water_depth;
         UED_quality_attributes prefered_attribute = UED_valid_attribute; // must go inside loop
         export_file.precision(2);
         export_file.width(6);
         export_file << date
         << ' ' << ued_database.get(prcp_var,date,prcp_units,prefered_attribute,UED_record::time_stamp_year)
         << ' ' << ued_database.get(tmax_var,date,temp_units,prefered_attribute,UED_record::time_stamp_year)
         << ' ' << ued_database.get(tmin_var,date,temp_units,prefered_attribute,UED_record::time_stamp_year)
         << endl;
      };

   };
#endif
#ifdef _Windows
   PostQuitMessage(0);
#endif
};
