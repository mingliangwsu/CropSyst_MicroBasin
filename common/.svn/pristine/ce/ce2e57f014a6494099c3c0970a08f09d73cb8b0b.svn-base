/* Class for I/O daily weather data in CropSyst text format */
#  include "corn/math/compare.hpp"
#  include "corn/measure/measures.h"
#  include "corn/chronometry/date_const.hpp"
using namespace CORN;
#  include "UED/library/std_codes.h"
#  include "common/weather/database/wthrfile.h"
#  include "common/weather/weather_types.h"
#include "weather/parameter/WP_solar_radiation.h"
#include <stdio.h>
#include "corn/OS/file_system_engine.h"
#include <iostream>

#ifdef unix
#  include <strstream>
#endif
#ifdef _Windows
#  include <strstrea.h>
#  include <windows.h>
#endif
#  ifdef __BCPLUSPLUS__
#     include <float.h>
#  endif
#ifdef USE_CORN_TRANSLATOR_CLASS
#  include "corn/commontrans.h"
#else
#  define L_appears_to_be_corrupt "Appears to be corrupt"
#  define common_translate(x)  x
#endif

using namespace std;

//______________________________________________________________________________
const char *Weather_text_file_format_label_table[] =
{"V4_format"
,"day_precip_temp"
,"day_precip_temp_rad"
,"day_precip_temp_rad_dewpoint"
,"day_precip_temp_rad_humid"
,"day_precip_temp_rad_dewpoint_wind"
,"day_precip_temp_rad_humid_wind"
,"day_precip_temp_rad_VPD"
,0};
//______________________________________________________________________________
// Version 3 preferred units for columns
UED_units_code V3_day_precip_temp_units[]                   = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation };
UED_units_code V3_day_precip_temp_rad_units[]               = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation };
UED_units_code V3_day_precip_temp_rad_dewpoint_units[]      = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation,UC_mm,UC_celcius };
UED_units_code V3_day_precip_temp_rad_humid_units[]         = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation,UC_percent,UC_percent };
UED_units_code V3_day_precip_temp_rad_dewpoint_wind_units[] = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation,UC_mm,UC_celcius,UC_meters_per_second };
UED_units_code V3_day_precip_temp_rad_humid_wind_units[]    = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation,UC_percent,UC_percent,UC_meters_per_second };
// Warning, not sure of units of VPD
UED_units_code V3_day_precip_temp_rad_VPD_units[]           = { UT_day_of_year,UC_mm,UC_celcius,UC_celcius,UC_MJ_per_m2_solar_radiation,UC_kPa};
//______________________________________________________________________________
void Weather_text_file::write_ASCII_line
(ofstream &outfile, DOY doy)
{  // write out all variables as encountered
   //Date date((Year)year,DOY(doy),D_YD,D_lead_zero,0);
   date32 date = year*1000+doy;                                                  //170728
   if (!data_sets.find(UED::STD_VC_date.get())) // Date not present
   {  if (V3_write_format) // Version 3 only had day of year.                    //021216
               outfile << doy<< '\t' ;                                           //021216
      else  outfile << date << '\t';                                             //030108
   }
   int col = 0;                                                                  //021216
   FOR_EACH_IN(dataset,Weather_column_data,data_sets,each_weather)
   {  if (dataset->desired_for_output || (V3_write_format== UNKNOWN_format))     //060119
            // UNKNOWN_format indicated the new Version 4 format
      {  CORN::Quality_clad w_attr;                                              //060119
         UED_units_code w_units =  (write_units) ? write_units[col] : dataset->units.get();  //021218
         float32 w_value = dataset->get(doy,w_units,w_attr);
         if ((w_units == UED::STD_VC_date.get()) || (w_units == UT_day_of_year))
         {  if (V3_write_format) // Version 3 only had day of year.              //021216
                  outfile << doy ;                                               //021216
             else outfile << date;                                               //010308
         }
         else
         {  if (!w_attr.is_valid())
               w_value = -9999;
            outfile << w_value;
         }
         // Delimit by tabs (dont put tab at very end of the line)
         if (col < int(data_sets.count())-1)
         outfile << '\t';
         col ++;
      }
   } FOR_EACH_END(each_weather)
   outfile << endl;
}
//_1998-04-03___________________________________________________________________
void Weather_text_file::write_ASCII_column_headers(std::ostream &outfile)
{
   int col = 0;
   if (!data_sets.find(UED::STD_VC_date.get())) // Date not present
      outfile << UED::standard_variable_abbreviation(UED::STD_VC_date.get())     //140616
         << '\t';
   FOR_EACH_IN(dataset,Weather_column_data,data_sets,each_abbreviation)          //030608
   {  outfile << UED::standard_variable_abbreviation(dataset->variable.get());   //140616
      if (col < (int)data_sets.count()-1)
         outfile << '\t';
      col ++;
   } FOR_EACH_END(each_abbreviation)
   outfile << endl;
   if (!data_sets.find(UED::STD_VC_date.get())) // Date not present
      outfile << "YYYYDDD\t";
   col = 0;
   FOR_EACH_IN(dataset,Weather_column_data,data_sets,each_description)           //030608
   {  char units_desc[100];
      char units_abbrev[100];                                                    //030123
      dataset->units.compose_description(units_desc, units_abbrev);
      outfile << units_abbrev;
      if (col < (int)data_sets.count()-1)
         outfile << '\t';
      col ++;
   } FOR_EACH_END(each_description)                                              //030608
   outfile << endl;
}
//_2002-12-16___________________________________________________________________
void Weather_text_file::write_ASCII()
{  // This will create a single file for the new V4 text files
   // and separate files for the other formats
   ofstream *outfile =
    (single_outfile)
    ? single_outfile
    : new ofstream(file_name->c_str());                                           //060221
   // Write header lines:
   if (!V3_write_format ) // Version 3 files did not have column headers
   {  if (need_to_write_column_headers)
         write_ASCII_column_headers(*outfile);
   } else
   {  switch (V3_write_format)
      {  case day_precip_temp:                  write_units = V3_day_precip_temp_units;                  break;
         case day_precip_temp_rad:              write_units = V3_day_precip_temp_rad_units;              break;
         case day_precip_temp_rad_dewpoint:     write_units = V3_day_precip_temp_rad_dewpoint_units;     break;
         case day_precip_temp_rad_humid:        write_units = V3_day_precip_temp_rad_humid_units;        break;
         case day_precip_temp_rad_dewpoint_wind:write_units = V3_day_precip_temp_rad_dewpoint_wind_units;break;
         case day_precip_temp_rad_humid_wind:   write_units = V3_day_precip_temp_rad_humid_wind_units;   break;
         case day_precip_temp_rad_VPD:          write_units = V3_day_precip_temp_rad_VPD_units;          break;
         default : write_units = 0 ; break;
      }
   }
   if (outfile->good())                                                          //990907
      for (CORN::DOY doy = 1; doy <= date_days_in_year(year) ; doy++)            //990301
         write_ASCII_line(*outfile,doy);                                         //980413
   if (!single_outfile)                                                          //060221
   {  delete outfile; outfile = 0; }                                             //060221
}
//______________________________________________________________________________
void Weather_text_file::read_column_headers(std::ifstream &instrm)
{  std::string variable_line;
   instrm.seekg(0);
   std::getline(instrm,variable_line);                                           //131121
   UED_variable_code var_codes[1000];     int var_code_count = 0;
   UED_units_code    units_codes[1000];   int units_code_count = 0;
   int vli = 0;
   int vci = 0;
   char inchar = variable_line.c_str()[vli++];
   char variable_cstr[255];
   while (inchar) //  != '\n')
   {  if (isspace(inchar))
      {  if (vci != 0) // we've reached end of a variable code
         {  var_codes[var_code_count++] = UED::Identify_standard_variable_code(variable_cstr);
            vci = 0;
         }
      } else
      {  variable_cstr[vci++] = inchar;
         variable_cstr[vci] = 0;
      }
      inchar = variable_line.c_str()[vli++];
   }
   //    Don't forget the last variable on the line
   var_codes[var_code_count++] = UED::Identify_standard_variable_code(variable_cstr); //040427
   var_codes[var_code_count] = 0; // just null terminate the array
   std::string      units_line;                                                  //040909
   std::getline(instrm,units_line);                                              //131121
   // Now read the corresponding units for the variable
   int uli = 0;
   int uci = 0;
   inchar = units_line.c_str()[uli++];
   char units_cstr[255];
   while (inchar) //  != '\n')
   {  if (isspace(inchar))
      {  if (uci != 0)
         {  Units_code units_code = CORN::units_identify_code(units_cstr);
            if (units_code == UT_date)                                           //060220
               date_format.set_string(units_cstr);                               //141203_060220
            units_codes[units_code_count++] = units_code;                        //060220
            uci = 0;
         }
      } else
      {  units_cstr[uci++] = inchar;
         units_cstr[uci] = 0;
      }
      inchar = units_line.c_str()[uli++];
   }
   // Don't forget the last units on the line
   units_codes[units_code_count++] = CORN::units_identify_code(units_cstr);      //040427
   units_codes[units_code_count] = 0; // just null terminate the array
   for (int i = 0 ; i < var_code_count; i++)
     get_data_set(var_codes[i],units_codes[i],false);
     // Get dataset will instanciate and append column if not found
     // unused: Weather_column_data *dataset =
}
//_2002-09-05___________________________________________________________________
void Weather_text_file::create_datasets_for_format
(bool is_english
,bool has_dewpt                                                                                                                     //020903
,bool has_humid                                                                                                                     //020903
,bool has_solrad                                                                                                                    //020903
,bool has_wind)                                                                                                                     //020904
{  Weather_column_data *unused_dataset;
   unused_dataset = get_data_set(UED::STD_VC_date.get(),UT_day_of_year,true);                                                       //020806
   unused_dataset = get_data_set(UED::STD_VC_precipitation.get()  ,is_english ? UE_inch_linear : UC_mm     ,true);                  //020806
   unused_dataset = get_data_set(UED::STD_VC_max_temperature.get(),is_english ? UE_Farenheit   : UC_celcius,true);                  //020806
   unused_dataset = get_data_set(UED::STD_VC_min_temperature.get(),is_english ? UE_Farenheit   : UC_celcius,true);                  //020806
   if (has_solrad)                                                                                                                  //020903
   {  unused_dataset = get_data_set(UED::STD_VC_solar_radiation_ERRONEOUS.get(),is_english ? UE_Langley : UC_MJ_per_m2_solar_radiation,true); //020903
   }                                                                                                                               //020903
   if (has_dewpt)                                                                                                                   //020903
   {  unused_dataset = get_data_set(UED::STD_VC_max_dew_point_temperature.get(),is_english ? UE_Farenheit : UC_celcius,true);       //020903
      unused_dataset = get_data_set(UED::STD_VC_min_dew_point_temperature.get(),is_english ? UE_Farenheit : UC_celcius,true);       //020806
   }                                                                                                                               //020903
   if (has_humid)                                                                                                                   //020903
   {  unused_dataset = get_data_set(UED::STD_VC_max_relative_humidity.get(),UC_percent,true);                                       //020903
      unused_dataset = get_data_set(UED::STD_VC_min_relative_humidity.get(),UC_percent,true);                                       //020806
   }                                                                                                                               //020903
   if (has_wind)                                                                                                                    //020905
   {  unused_dataset = get_data_set(UED::STD_VC_wind_speed.get(),is_english ? UE_miles_per_day : UC_meters_per_second,true);        //020905
   }                                                                                                                               //020905
}
//______________________________________________________________________________
void Weather_text_file::identify_old_file_format(std::ifstream &infile)
{  std::string    in_line;                                                       //040909
   float prcp;           // Must be generic float                                
   float tmax;                                                                   
   float tmin;                                                                   
   float srad;
   float rhmax_dewmax;                                                           //870313
   float rhmin_dewmin;                                                           //870313
   float ws;
   bool has_dewpt = false;                                                       //020903
   bool has_humid = false;                                                       //020903
   bool has_solrad = false;                                                      //020903
   bool has_wind = false;                                                        //020904
   float64 maxTmax= 0;                                                           //020904
   bool format_identified = false;                                               //021011
   //001006       Some times 0 values are entered in a column for missing values
   // So we scan until a identifiable relative humidty or dewpoint is encounted.
   for (int expect_DOY = 1; !format_identified && (expect_DOY <= 365) ; expect_DOY++) //001006
   {  std::getline(infile,in_line);                                              //131121
      int line_DOY;
      columns = (uint8)sscanf(in_line.c_str(),"%d%f%f%f%f%f%f%f"
         ,&line_DOY,&prcp,&tmax,&tmin,&srad,&rhmax_dewmax,&rhmin_dewmin,&ws);
      if ((tmax < 200) && (tmax > -200)) // Anything out of this range is presumed invalid  //020904
         maxTmax = std::max<float>(maxTmax,tmax);                                       //020904
      switch (columns)
      {  case 4  : break; // already set above
         case 5  :
            has_solrad = true;                                                   //020903
         break;
         case 7  :                                                               //870313
            has_solrad = true;                                                   //020903
            if (rhmax_dewmax > 0.00001)                                          //001006
            {  if (rhmax_dewmax < 20) has_dewpt = true;                          //020903
               else                   has_humid = true;                          //020903
            } else                                                               //001211
            if (line_DOY == 365)                                                 //001211
            {  // we got to the end of the year all values are 0 set as rel humidity
               has_dewpt = false;                                                //020903
               has_humid = true;                                                 //020903
            }
         break;                                                                  //870313
         case 8  :                                                               //870313
            has_solrad = true;                                                   //020903
            has_wind = true;                                                     //020903
            if (!(CORN::is_approximately<float>(rhmax_dewmax,0.0,0.00001)))      //001006
            {  if (rhmax_dewmax < 20)  has_dewpt = true;                         //020903
               else                    has_humid = true;                         //020903
               format_identified = true;                                         //021012
            } else                                                               //001211
            if (line_DOY == 365)                                                 //001211
            {  // we got to the end of the year all values are 0 set as rel humidity
               has_dewpt = false;                                                //020903
               has_humid = true;                                                 //020903
               format_identified = true;                                         //021012
            }
            break;                                                               //870313
      }
      if (columns < 6) format_identified = true;                                 //021012
   }
   bool is_english = (maxTmax > 60);                                             //020903
   create_datasets_for_format(is_english,has_dewpt,has_humid,has_solrad,has_wind);//021216
   infile.close();
}
//______________________________________________________________________________
void Weather_text_file::identify_file_format()
{  std::string in_line;                                                          //040909
   ifstream infile(file_name->c_str());                                           //000125
   {  //Check to see if the format has column headers
      std::string    first_line;                                                 //040909
      std::getline(infile,first_line);                                           //131121
      if ((first_line.find("A") != std::string::npos) || (first_line.find("a") != std::string::npos))   // 070424 these may need to be find_substring
      { // Read the column headers
         headers = true;
         read_column_headers(infile);
      } else
      {  // No column headers so rewind the file
         headers = false;
         infile.seekg(0);
         identify_old_file_format(infile);                                       //020903
      }
   }
}
//_2002-08-21_____________________________________________________________________________
void Weather_text_file::read()
{  identify_file_format();
   read_ASCII();
   modified = false; // Sinc we are reading the is not modified even if we are doing a units conversion
}
//______________________________________________________________________________
DOY Weather_text_file::read_ASCII_record
(ifstream &in_file_strm
,CORN::Date &expected_line_date
,CORN::Date &actual_line_date)
{  DOY line_DOY = 0;                                                             //040427
   uint16 line_year = 0;
   char record_buffer[1000];                                                     //060220
   in_file_strm.get(record_buffer,1000);
   strstream line_stream(record_buffer,1000,ios::app);
   char eol_char=0;                                                              //060220
   CORN::Date_clad_32 read_line_date(0);                                         //170525
   FOR_EACH_IN(data,Weather_column_data,data_sets,eachcolumn)                    //030707
   {     if (data->units.get() == UT_day_of_year)                                //020904
         {  line_stream >> line_DOY;                                             //040427
            actual_line_date.set_DOY(line_DOY);                                  //040427
            read_line_date.set_DOY(line_DOY);                                    //060221
            if (line_year && line_DOY )                                          //060221
               // Since we have both the year and DOY we can assume
               // the record is the correct date so expected
               expected_line_date.set_YD(line_year,line_DOY);
         } else if (data->units.get() == UT_year)                                //060220
         {  line_stream >> line_year;                                            //060220
            actual_line_date.set_year(line_year);                                //060220
            read_line_date.set_year(line_year);                                  //060221
            if (line_year && line_DOY )                                          //060221
            // Since we have both the year and DOY we can assume
            //the record is the correct date so expected
               expected_line_date.set_YD(line_year,line_DOY);
         } else if (data->units.get() == UT_date)
         {  CORN::Date_clad_32 line_date;                                        //040427
            //170525 line_date.format.copy_format(date_format);                           //060220
            char line_date_buffer[50];                                           //070515
            line_stream >> line_date_buffer;                                     //070515
            line_date.set_c_str(line_date_buffer);                               //070515
            if (!(line_year && line_DOY))                                        //060221
            { // If we already have the year and day of year                     //060221
              // we just use those and ignore the line date                      //060221
              // It is presumed lesser quality because if may have an            //060221
              // un accounted for format or may not be y2k compliant             //060221
            actual_line_date.set(line_date);                                     //170525_040427
            read_line_date  .set(line_date);                                     //170525_060221
            /*170525
            actual_line_date.set_date32(line_date.get_date32());                        //040427
            read_line_date.set_date32(line_date.get_date32());                          //060221
            */
            line_DOY = actual_line_date.get_DOY();                               //040427
            }
         } else                                                                  //020904
         {  float32 value;                                                       //020904
            line_stream >> value;                                                //020904
            data->set_with_quality(line_DOY,value,file_quality,modified);        //020904
         }
         if (line_stream.fail())                                                 //060220
         {  in_file_strm.get(eol_char);                                          //060220
            return line_DOY;
         }
   }  FOR_EACH_END(eachcolumn)                                                   //020904
   in_file_strm.get(eol_char);                                                   //060220
   return line_DOY;                                                              //051028
}
//_2004-04-27________________________________________________read_ASCII_record_/
bool Weather_text_file::read_ASCII()
{
   #ifdef __BCPLUSPLUS__
   // There is a bug in Win32, one of MicroSoft's DLL's is
   // incorrectly changing floating point formats!
   _fpreset();
   #endif
   if (!CORN::OS::file_system_engine.exists(*file_name))                         //980404
      return false;                                                              //980404
   ifstream in_file(file_name->c_str());                                         //000125
   if (!in_file.good())                                                          //991202
      return false;                                                              //991202
   // If the file has a .GEN extension then we assume it is generated data
   file_quality.assume_code(
   // We need to presume .GEN files have real data                               //021017
       file_name->has_extension_ASCII("gen",true)                                //170224
         ? CORN::generated_quality : CORN::measured_quality);                    //150811
   std::string      error_dates;                                                 //040909
   if (headers) // Skip the first two lines                                      //020904
   {  std::string      header;                                                   //040909
      std::getline(in_file,header); // the first line                            //131121
      std::getline(in_file,header); // the second line                           //131121
      // The new format allows missing records                                   //040427
      CORN::Date_clad_32 expected_line_date;//(0,0);                             //040427
      CORN::Date_clad_32 actual_line_date;//(0,0);                               //040427
      bool at_EOF = false;                                                       //040427
      bool first_line = true;                                                    //040427
      while (!at_EOF)                                                            //040427
      {  DOY read_DOY = read_ASCII_record
            (in_file,expected_line_date,actual_line_date);
         //cout << (int)read_DOY <<"   " << endl; //'\r';
         //cout <<  actual_line_date << endl;
         at_EOF = in_file.eof();
         if (first_line)
            first_line=false;
         else
         {  if (read_DOY && (actual_line_date != expected_line_date) && !at_EOF)
            {  error_dates.append(expected_line_date.as_string());
               error_dates.append(", ");
            }
         }
         expected_line_date.set(actual_line_date); expected_line_date.inc_day(); //170527
      }
   } else                                                                        //040427
   {  DOY line_DOY = 0;                                                          //991202
      DOY days = date_days_in_year(year);                                        //991009
      for (DOY doy = 1; doy <= days; doy++)                                      //980403
      {  CORN::Date_clad_32 expected_line_date(year,doy);                        //040427
         CORN::Date_clad_32 actual_line_date(year,doy);                          //040427
         line_DOY = read_ASCII_record(in_file,expected_line_date,actual_line_date);//051028
         if ((line_DOY != doy))
         {  if ( doy == 366)
            {  // We will tolerate a file with only 365 days in a leap year.
               FOR_EACH_IN(data,Weather_column_data,data_sets,each_weather_column_data)//030707
                  data->fixup_leap_year();                                       //980305
               FOR_EACH_END(each_weather_column_data)                            //030707
            } else
            {  error_dates.append(expected_line_date.as_string());               //040427
               error_dates.append(", ");                                         //040427
            }
         }
      }
   }
   in_file.close();                                                              //040427
   if (error_dates.length() )
   {  cerr << file_name->c_str()
            << ' ' << common_translate(L_appears_to_be_corrupt)
            <<  " or incomplete for the following dates: "
            << error_dates.c_str() << endl;
      #ifdef _Windows
      if (!allow_missing_dates)
      {     strstream strerr;
            strerr << file_name->c_str()
            << ' ' << common_translate(L_appears_to_be_corrupt)
            <<  " or incomplete for the following dates: "
            << error_dates.c_str();
            MessageBox(0,strerr.str(),"",MB_ICONSTOP|MB_OK);
      }
      #endif
   }
   modified = false; // Since we are reading this is not modified even if we are doing a units conversion
   return true;
}
//______________________________________________________________________________
float64 Weather_text_file::get_avg_annual_temperature()                    const
{  float64 sum_annual_temp = 0;
   CORN::Quality_clad(curr_qual);                                                //020905
   for (DOY d = 1; d < date_days_in_year(year); d++)
      sum_annual_temp += (                                                       //980305
           (get_max_temperature(d,curr_qual))                                    //981209
         + (get_min_temperature(d,curr_qual))                                    //981209
         )/2.0;
   avg_annual_temperature = sum_annual_temp / date_days_in_year(year);           //991008
   return avg_annual_temperature;
}
//______________________________________________________________________________
void Weather_text_file::invalidate_DOY(CORN::DOY doy)
{  FOR_EACH_IN(data,Weather_column_data,data_sets,each_weather_column_data)      //030707
      data->invalidate_DOY(doy);                                                 //980305
   FOR_EACH_END(each_weather_column_data);                                       //030707
}
//_1999-10-14___________________________________________________________________
Weather_text_file::Weather_text_file
(const GEN_DAT_UED_filename  &_file_name
,Year                         _year                                              //060221
,bool                         _for_write                                         //000619
,Format_old                   _V3_write_format                                   //021216
,bool                         _allow_missing_dates                               //040427
,bool                         _need_to_write_column_headers                      //060221
,ofstream                    *_single_outfile)                                   //060221
:file_name(new GEN_DAT_UED_filename(_file_name))                                 //150315
,modified(false)                                                                 //990903
,for_write(_for_write)                                                           //000316
,V3_write_format(_V3_write_format)                                               //021216
,write_units(0)                                                                  //021218
,allow_missing_dates(_allow_missing_dates)                                       //040427
,year(_year)                                                                     //060221
,need_to_write_column_headers(_need_to_write_column_headers)                     //060221
,single_outfile(_single_outfile)                                                 //060221
{  if (_for_write && V3_write_format)                                            //021216
   {  // create data sets in the specified format order.
      bool has_dewpt    = (V3_write_format == day_precip_temp_rad_dewpoint) || (V3_write_format == day_precip_temp_rad_dewpoint_wind);    //020903
      bool has_humid    = (V3_write_format == day_precip_temp_rad_humid) || (V3_write_format == day_precip_temp_rad_humid_wind);          //020903
      bool has_solrad   = (V3_write_format >= day_precip_temp_rad);                                                                       //020903
      bool has_wind     = (V3_write_format == day_precip_temp_rad_dewpoint_wind) | (V3_write_format == day_precip_temp_rad_humid_wind);   //020904
      create_datasets_for_format(false,has_dewpt,has_humid,has_solrad,has_wind); // currently always write metric                         //021216
   }                                                                                                                                     //021216
   if (CORN::OS::file_system_engine.exists(*file_name) && ! for_write)
      read();
}
//______________________________________________________________________________
// When we set data, even though the data might not be available,
// we let the derived class use the data is has so dont change quality
Weather_column_data *Weather_text_file::get_data_set
(UED_variable_code   var_code
,UED_units_code      units_code // Optional  (will be 0 when writing)
,bool                desired_for_output)                                mutates_
{  // We can't just use find because we need to look at units code (for dates
   FIND_FOR_EACH_IN(existing_data,column ,Weather_column_data,data_sets,true,each_column) //060220
   {
      UED_variable_code CVcode = column->variable.get();
      if ((column->variable.get() == var_code) && ((column->units.get() == units_code) || (units_code == 0)))
          existing_data = column;
   } FOR_EACH_END(each_column);
   if (!existing_data)  // Allocate as needed
   {       if (var_code == UED::STD_VC_date.get())                       existing_data = new Weather_column_data(UED::STD_VC_date.get(),units_code ? units_code : UT_date,0.0,9999999.0,0.000001);
      else if (var_code == UED::STD_VC_precipitation.get())              existing_data = precip_data              = new Weather_column_data(UED::STD_VC_precipitation.get(),units_code ? units_code : UC_mm/*_depth*/,m_to_mm(min_valid_precipitation_m),m_to_mm(max_valid_precipitation_m),0.000001);
      else if (var_code == UED::STD_VC_max_temperature.get() )           existing_data = max_temp_data              = new Weather_column_data(UED::STD_VC_max_temperature.get(),units_code ? units_code : UC_celcius,min_valid_temperature,max_valid_temperature,0.001)   ;
      else if (var_code == UED::STD_VC_min_temperature.get() )           existing_data = min_temp_data              = new Weather_column_data(UED::STD_VC_min_temperature.get(),units_code ? units_code : UC_celcius,min_valid_temperature,max_valid_temperature,0.001)   ;
      else if (var_code == UED::STD_VC_solar_radiation_ERRONEOUS.get() )           existing_data = solar_rad_data             = new Weather_column_data(UED::STD_VC_solar_radiation_ERRONEOUS.get(),units_code ? units_code : UC_MJ_per_m2_solar_radiation,min_valid_solar_rad,max_valid_solar_rad,0.0001)   ;
      else if (var_code == UED::STD_VC_max_relative_humidity.get() )     existing_data = max_rel_humid_data         = new Weather_column_data(UED::STD_VC_max_relative_humidity.get(),units_code ? units_code : UC_percent,min_valid_relative_humidity,max_valid_relative_humidity,0.0001)   ;
      else if (var_code == UED::STD_VC_min_relative_humidity.get() )     existing_data = min_rel_humid_data         = new Weather_column_data(UED::STD_VC_min_relative_humidity.get(),units_code ? units_code : UC_percent,min_valid_relative_humidity,max_valid_relative_humidity,0.0001)   ;
      // weather database does not use avg rel humid
      else if (var_code == UED::STD_VC_max_dew_point_temperature.get() ) existing_data = max_dew_point_data         = new Weather_column_data(UED::STD_VC_max_dew_point_temperature.get(),units_code ? units_code : UC_celcius,min_valid_temperature,max_valid_temperature,0.0001)   ;
      else if (var_code == UED::STD_VC_min_dew_point_temperature.get() ) existing_data = min_dew_point_data         = new Weather_column_data(UED::STD_VC_min_dew_point_temperature.get(),units_code ? units_code : UC_celcius,min_valid_temperature,max_valid_temperature,0.0001)   ;
      else if (var_code == UED::STD_VC_wind_speed.get() )                existing_data = wind_speed_data            = new Weather_column_data(UED::STD_VC_wind_speed.get(),units_code ? units_code : UC_meters_per_second,m_per_day_to_m_per_sec(min_wind_speed_m_d ),m_per_day_to_m_per_sec(max_wind_speed_m_d ),0.0001)   ;
      else if (var_code == UED::STD_VC_avg_daytime_vapor_pressure_deficit.get() ) existing_data = avg_daytime_VPD_data_kPa   = new Weather_column_data(UED::STD_VC_avg_daytime_vapor_pressure_deficit.get(),units_code ? units_code : UC_kPa/*UC_kilo_pascal_atmospheric_pressure*/,min_valid_avg_vapor_pressure_deficit_kPa,max_valid_avg_vapor_pressure_deficit_kPa,0.0001)   ;
      else if (var_code == UED::STD_VC_avg_fullday_vapor_pressure_deficit.get() ) existing_data = avg_fullday_VPD_data_kPa   = new Weather_column_data(UED::STD_VC_avg_fullday_vapor_pressure_deficit.get(),units_code ? units_code : UC_kPa/*UC_kilo_pascal_atmospheric_pressure*/,min_valid_avg_vapor_pressure_deficit_kPa,max_valid_avg_vapor_pressure_deficit_kPa,0.0001)   ;
      else if (var_code == UED::STD_VC_pot_evapotranspiration.get() )             existing_data = pot_ET_data              = new Weather_column_data(UED::STD_VC_pot_evapotranspiration.get(),units_code ? units_code : UC_mm/*_depth*/,min_valid_pot_ET_m,max_valid_pot_ET_m,0.0001)   ;
      else if (!existing_data) // then this is an unknown column, we need a place holder  //021216
          existing_data = pot_ET_data              = new Weather_column_data(var_code,units_code  ,-999999,999999,0.0001)   ; //021216
      if (existing_data)                                                         //060119
          if (desired_for_output) existing_data->set_desired_for_output();       //060119
      data_sets.append(existing_data);
   }
   return existing_data;
}
//_2002-09-05___________________________________________________________________
float64 Weather_text_file::set_precip_m
(CORN::DOY doy,float64 i_precip_m, CORN::Quality &desired_quality)
{  //  m   (will be written as mm)
   precip_data = get_data_set(UED::STD_VC_precipitation.get());                  //020905
   return precip_data ? precip_data->set_alt_units(doy,i_precip_m,UC_m,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_pot_ET_m
(CORN::DOY doy,float64 i_pot_ET, CORN::Quality &desired_quality)
{  //  m   (will be written as mm)
   pot_ET_data = get_data_set(UED::STD_VC_pot_evapotranspiration.get());         //020905
   return pot_ET_data ? pot_ET_data->set_alt_units(doy,i_pot_ET,UC_m,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_daytime_VPD_kPa
(CORN::DOY doy,float64 i_VPD, CORN::Quality &desired_quality)
{  //  kPa
   avg_daytime_VPD_data_kPa = get_data_set(UED::STD_VC_avg_daytime_vapor_pressure_deficit.get());  //020905
   return avg_daytime_VPD_data_kPa ? avg_daytime_VPD_data_kPa->set_alt_units(doy,i_VPD,UC_kPa,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_fullday_VPD_kPa
(CORN::DOY doy,float64 i_VPD, CORN::Quality &desired_quality)
{  //  kPa
   avg_fullday_VPD_data_kPa = get_data_set(UED::STD_VC_avg_fullday_vapor_pressure_deficit.get());  //020905
   return avg_fullday_VPD_data_kPa ? avg_fullday_VPD_data_kPa->set_alt_units(doy,i_VPD,UC_kPa,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_max_temp
(CORN::DOY doy,float64 i_max_temp, CORN::Quality &desired_quality)
{  //  C
   max_temp_data = get_data_set(UED::STD_VC_max_temperature.get());              //020905
   return max_temp_data ? max_temp_data->set_alt_units(doy,i_max_temp,UC_celcius,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_min_temp
(CORN::DOY doy,float64 i_min_temp, CORN::Quality &desired_quality)
{   //  C
    min_temp_data = get_data_set(UED::STD_VC_min_temperature.get());             //020905
    return min_temp_data ? min_temp_data->set_alt_units(doy,i_min_temp,UC_celcius,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_max_rel_humid
(CORN::DOY doy,float64 i_max_rel_humid, CORN::Quality &desired_quality)
{  max_rel_humid_data = get_data_set(UED::STD_VC_max_relative_humidity.get());
   return max_rel_humid_data ? max_rel_humid_data->set_alt_units(doy,i_max_rel_humid,UC_percent,desired_quality,modified) : 0.0;
}//  %           max_relative_humidity()
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_min_rel_humid
(CORN::DOY doy,float64 i_min_rel_humid, CORN::Quality &desired_quality)
{  min_rel_humid_data = get_data_set(UED::STD_VC_min_relative_humidity.get());   //020905
   return min_rel_humid_data ? min_rel_humid_data->set_alt_units(doy,i_min_rel_humid,UC_percent,desired_quality,modified) : 0.0;
}//  %           min_relative_humidity()
//_1999-10-13___________________________________________________________________
// ClimGen does not use avg rel humid
float64 Weather_text_file::set_max_dew_point
(CORN::DOY doy,float64 _max_dew_point, CORN::Quality &desired_quality)           //991013
{  //010602       Don't allow 0.0 values as missing  (not sure why I was doing this, but probably a div by zero error
   if (is_approximately(_max_dew_point,0.0,0.000001))                            //010602
      _max_dew_point = 0.00001;
   max_dew_point_data = get_data_set(UED::STD_VC_max_dew_point_temperature.get());  //020905
   return max_dew_point_data ? max_dew_point_data->set_alt_units(doy,_max_dew_point,UC_celcius,desired_quality,modified) : 0.0; //991013
}//  C
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::set_min_dew_point
(CORN::DOY doy,float64 i_min_dew_point, CORN::Quality &desired_quality)          //991013
{  //Tag 0.0 values as missing  (not sure why I was doing this, but probably a div by zero error //010602
   if (is_approximately(i_min_dew_point,0.0,0.000001))                           //010602
      i_min_dew_point = 0.00001;
   min_dew_point_data = get_data_set(UED::STD_VC_min_dew_point_temperature.get());  //020905
   return min_dew_point_data ? min_dew_point_data->set_alt_units(doy,i_min_dew_point,UC_celcius,desired_quality,modified) : 0.0;
}
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::set_wind_speed_m_d   //  m/day (stored as m/S)
(CORN::DOY doy,float64 i_windspeed, CORN::Quality &desired_quality)
{  wind_speed_data = get_data_set(UED::STD_VC_wind_speed.get());                 //020905
   return wind_speed_data ? wind_speed_data->set_alt_units(doy,i_windspeed,UC_meters_per_day,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::set_solar_rad   //  MJ/??
(CORN::DOY doy,float64 i_solar_rad, CORN::Quality &desired_quality)
{  solar_rad_data = get_data_set(UED::STD_VC_solar_radiation_ERRONEOUS.get());             //020905
   return solar_rad_data?  solar_rad_data->set_alt_units(doy,i_solar_rad,UC_MJ_per_m2_solar_radiation,desired_quality,modified) : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::get_precipitation_m        (CORN::DOY _DOY, CORN::Quality &quality)  const  //  m
{  quality.assume_code(CORN::unknown_quality);
   precip_data = get_data_set(UED::STD_VC_precipitation.get());                  //020905
   return (precip_data)
   ? precip_data->get(_DOY,UC_m,quality)                                         //040715
   : 0.0;
}
//_1999-10-13___________________________________________________________________
float64 Weather_text_file::get_pot_evapotranspiration_m        (CORN::DOY _DOY, CORN::Quality &quality)  const  //  m
{  quality.assume_code(CORN::unknown_quality);
   pot_ET_data = get_data_set(UED::STD_VC_pot_evapotranspiration.get());         //020905
   float64 value = (pot_ET_data)
   ? pot_ET_data->get(_DOY,UC_m,quality)                                         //040715
   : 0.0;
   return value;
}
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::get_avg_daytime_vapor_pressure_deficit_kPa(CORN::DOY _DOY, CORN::Quality &quality)  const  //  kPa
{  quality.assume_code(CORN::unknown_quality);                                             //081030
   avg_daytime_VPD_data_kPa = get_data_set(UED::STD_VC_avg_daytime_vapor_pressure_deficit.get());  //020905
   float64 value = (avg_daytime_VPD_data_kPa)
   ? avg_daytime_VPD_data_kPa->get(_DOY,UC_kPa,quality)                          //040715
   : 0.0;
   return  value;
}
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::get_avg_fullday_vapor_pressure_deficit_kPa(CORN::DOY _DOY, CORN::Quality &quality)  const  //  kPa
{  quality.assume_code(CORN::unknown_quality);                                   //081030
   avg_fullday_VPD_data_kPa = get_data_set(UED::STD_VC_avg_fullday_vapor_pressure_deficit.get());  //020905
   float64 value = (avg_fullday_VPD_data_kPa)
   ? avg_fullday_VPD_data_kPa->get(_DOY,UC_kPa,quality)                          //040715
   : 0.0;
   return  value;
}
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::get_max_temperature(CORN::DOY _DOY , CORN::Quality &quality)  const  //  C
{  quality.assume_code(CORN::unknown_quality);
   max_temp_data = get_data_set(UED::STD_VC_max_temperature.get());              //020905
   return (max_temp_data)
   ? max_temp_data->get(_DOY,UC_celcius,quality)
   : 0.0;
}
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::get_min_temperature      (CORN::DOY _DOY , CORN::Quality &quality)  const //  C
{  quality.assume_code(CORN::unknown_quality);
   min_temp_data = get_data_set(UED::STD_VC_min_temperature.get());              //020905
   return (min_temp_data)
   ? min_temp_data->get(_DOY,UC_celcius,quality)
   : 0.0;
}
//_1998-03-05_____________________________________________________________________________
float64 Weather_text_file::get_solar_radiation(CORN::DOY _DOY ,modifiable_ Solar_radiation &solar_rad)  const //  MJ/??
{
   CORN::Quality_clad quality(CORN::unknown_quality);
   solar_rad_data = get_data_set(UED::STD_VC_solar_radiation_ERRONEOUS.get());   //020905
   float64 srad = (solar_rad_data)
       ? solar_rad_data->get(_DOY,UC_MJ_per_m2_solar_radiation,quality)
       : 0.0;
   return solar_rad.set_MJ_m2(srad,quality);                                     //141201
}
//_2014-07-16__1998-03-05_______________________________________________________
float64 Weather_text_file::get_max_relative_humidity(CORN::DOY _DOY , CORN::Quality &quality)  const//  %
{  quality.assume_code(CORN::unknown_quality);
   max_rel_humid_data = get_data_set(UED::STD_VC_max_relative_humidity.get());   //020905
   return (max_rel_humid_data)
   ? max_rel_humid_data->get(_DOY,UC_percent,quality)
   : 0.0;
}
//______________________________________________________________________________
float64 Weather_text_file::get_min_relative_humidity(CORN::DOY _DOY , CORN::Quality &quality)  const//  %
{  quality.assume_code(CORN::unknown_quality);                                   //081030
   min_rel_humid_data = get_data_set(UED::STD_VC_min_relative_humidity.get());   //020905
   return (min_rel_humid_data)
   ? min_rel_humid_data->get(_DOY,UC_percent,quality)
   : 0.0;
}
//______________________________________________________________________________
// weather database does not use avg rel humid
float64 Weather_text_file::get_max_dew_point_temperature(CORN::DOY _DOY , CORN::Quality &quality)  const//  C
{  quality.assume_code(CORN::unknown_quality);                                   //081030
   max_dew_point_data = get_data_set(UED::STD_VC_max_dew_point_temperature.get()); //020905
   float64 max_dew_pot = (max_dew_point_data)                                    //001006
      ? max_dew_point_data->get(_DOY,UC_celcius,quality)
   :   0.0;
   // Tag dew points of 0.0 as missing
   if (is_approximately(max_dew_pot,0.0,0.000001))                               //001006
      quality.assume_code(CORN::missing_quality);
   return max_dew_pot;
}
//_1998-03-05___________________________________________________________________
float64 Weather_text_file::get_min_dew_point_temperature(CORN::DOY _DOY , CORN::Quality &quality)  const//  C
{  quality.assume_code(CORN::unknown_quality);                                   //081030
   min_dew_point_data = get_data_set(UED::STD_VC_min_dew_point_temperature.get());//020905
   float64 min_dew_pt = (min_dew_point_data)                                     //001006
   ? min_dew_point_data->get(_DOY,UC_celcius,quality)
   : 0.0;
   // Tag dew points of 0.0 as missing
   if (is_approximately(min_dew_pt,0.0,0.000001))                                //001006
      quality.assume_code(CORN::missing_quality);                                //001006
   return min_dew_pt;
}
//_1998-03-05___________________________________________________________________
float64 Weather_text_file::get_wind_speed_m_d(CORN::DOY DOY_, CORN::Quality &quality)  const// m/d
{  quality.assume_code(CORN::unknown_quality);                                   //081030
   wind_speed_data = get_data_set(UED::STD_VC_wind_speed.get());                 //020905
   return (wind_speed_data)
   ? wind_speed_data->get(DOY_,UC_meters_per_day,quality)                        //040715
   : 0.0;
}
//_1998-03-03___________________________________________________________________
Weather_text_file::~Weather_text_file()
{  if (modified && for_write)
      write_ASCII();
   data_sets.delete_all();                                                       //030711
}
//_1999-09-03___________________________________________________________________
Weather_column_data::Weather_column_data
(UED::Variable_code variable_                                                    //020904
,UED_units_code     units_  // preferred units
,float64            min_range_
,float64            max_range_
,float64            clean_precision_)
:Dynamic_array<float32>((nat32)367,(nat32)367,0.0)
,variable   (variable_)                                                          //020905
,units      (units_)                                                             //020904
,min_range  (min_range_)
,max_range  (max_range_)
,clean_precision(clean_precision_)
,desired_for_output(false)                                                       //060119
{  for (CORN::DOY doy = 0; doy < 367; doy++)
      invalidate_DOY(doy);
}
//______________________________________________________________________________
float64 Weather_column_data::set_alt_units
(CORN::DOY doy
,float64 i_value
,UED_units_code value_units                                                      //020904
,CORN::Quality &desired_quality
,bool &modified)
{  float64 value_set = 0;
   float32 value;
   convert(i_value,value_units,value,units.get());                               //020904
   if (value < min_range)  desired_quality.assume_code(CORN::out_of_range_low_warning_quality);    //081030
   if (value > max_range)  desired_quality.assume_code(CORN::out_of_range_high_warning_quality);   //081030
   if (desired_quality.is_same_or_better_than(quality[doy]))
   {  modified    = true;
      value_set   = Dynamic_array<float32>::set(doy,(float32)value);
      quality[doy]= desired_quality.get_quality_code();                           //150123
   } else
   {  // dont set to a value with worse quality, return the good value and quality
      desired_quality.assume_code(quality[doy]);                                 //081030
      value_set = Dynamic_array<float32>::get(doy);
   }
   return value_set;
}
//_1999-10-13___________________________________________________________________
float64 Weather_column_data::set_with_quality
(CORN::DOY doy
,float64 value
,CORN::Quality  &desired_quality                                                 //081030
,bool &modified)
{  float64 value_set = 0;
   if (quality_is_worse_than(quality[doy],desired_quality.get_quality_code()))   //150123
   {  modified    = true;
      value_set   = Dynamic_array<float32>::set(doy,(float32)value);
      quality[doy]=desired_quality.get_quality_code();
   } else
   {  desired_quality.assume_code(quality[doy]);                                 //081030
      value_set   = Dynamic_array<float32>::get(doy);
   }
   return value_set;
}
//_1999-10-13___________________________________________________________________
float64 Weather_column_data::get(CORN::DOY doy
,UED_units_code _desired_units                                                   //020905
, CORN::Quality &got_quality) //  C                                              //081030
{  float32 value = Dynamic_array<float32>::get(doy);                             //000216
   if  (value < min_range) quality[doy] = CORN::out_of_range_low_warning_quality;//150811_050418
   if  (value > max_range) quality[doy] = CORN::out_of_range_high_warning_quality;//150811_050418
   got_quality.assume_code(quality[doy]);                                        //081030
   float32 desired_value; // must be float32 for convert()                       //020905
   convert(value,units.get(),desired_value,_desired_units);                      //020905
   return (float64) desired_value;                                               //000216
}
//_1998-03-05____________________________________________________________________
void Weather_column_data::fixup_leap_year()
{  CORN::Quality_clad _quality(CORN::interpolated_quality);                      //150811_050609
   bool local_modifyied = false;
   set_with_quality(366,Dynamic_array<float32>::get(365),_quality,local_modifyied);
}
//_1999-10-13___________________________________________________________________
// wthrfile.cpp

