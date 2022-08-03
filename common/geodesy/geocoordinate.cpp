#include "common/geodesy/geocoordinate.h"
#include "corn/math/compare.hpp"
#include "corn/data_source/datarec.h"
#include "corn/string/strconv.hpp"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

float32 geocoordinate_approximation=0.0000001;                                   //180205
//______________________________________________________________________________
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x340))
CORN::Parameter_properties_literal latitude_param_props = {LABEL_latitude,"lat",LABEL_latitude,"latitude",NULL,NULL,UC_degrees_latitude,NULL}; //NYI,"hint"*//*NYI,"%PROG_HOME%:path/document.HTM#anchor"
CORN::Parameter_range latitude_range={-90.0,90.0,-90.0,90.0}; CORN::Parameter_format latitude_format={10,6,10};

CORN::Parameter_properties_literal longitude_param_props = {LABEL_longitude,"lon",LABEL_longitude,"Longitude",NULL,NULL,UC_degrees_longitude,NULL};  //NYI,"hint"*//*NYI,"%PROG_HOME%:path/document.HTM#anchor"
CORN::Parameter_range longitude_range = {-180.0,180.0,-180.0,180.0}; CORN::Parameter_format longitude_format={10,6,10};

CORN::Parameter_properties_literal elevation_param_props = {LABEL_elevation,"elev","elevation","elevation",NULL,NULL,UC_meter,NULL};  //NYI,"hint"*//*NYI,"%PROG_HOME%:path/document.HTM#anchor"
CORN::Parameter_range  elevation_range = {-100.0,9000,-11000.0,9000.0}; CORN::Parameter_format elevation_format={10,1,10};

#endif
//______________________________________________________________________________
Geocoordinate::Geocoordinate()
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x570) || (CS_VERSION==5))
: latitude_parameter (latitude_dec_deg ,latitude_param_props   ,latitude_range   ,latitude_format) //140131_120327
, longitude_parameter(longitude_dec_deg,longitude_param_props  ,longitude_range  ,longitude_format)//140131_090414
, elevation_parameter(elevation        ,elevation_param_props  ,elevation_range  ,elevation_format)//140131_120327
#else
:v_latitude_dec_deg (latitude_dec_deg     ,UC_degrees_latitude  ,LABEL_latitude  ,4,DEF_latitude_dec_deg , -90.0,  90.0, -90.0,  90.0,"-90-90","Latitude")
,v_longitude_dec_deg(longitude_dec_deg    ,UC_degrees_longitude ,LABEL_longitude ,4,DEF_longitude_dec_deg,-180.0, 180.0,-180.0, 180.0,"-180-180","Longitude")        //991004
,v_elevation        (elevation            ,UC_meter             ,LABEL_elevation ,2,DEF_elevation        ,   0.0,9999.0,   0.0,9999.9,"m","Elevation")        //000731
#endif
, ref_preferred_format(0)                                                        //140128

{  latitude_dec_deg  = DEF_latitude_dec_deg;
   longitude_dec_deg = DEF_longitude_dec_deg;
   elevation         = global_elevation_mean_meter;                              //151117
}
//_2012-03-25___________________________________________________________________
Geocoordinate::Geocoordinate
(float32 _latitude_dec_deg
,float32 _longitude_dec_deg
,float32 _elevation)
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x570) || (CS_VERSION==5))
: latitude_parameter (latitude_dec_deg ,latitude_param_props   ,latitude_range   ,latitude_format)    //120327
, longitude_parameter(longitude_dec_deg,longitude_param_props  ,longitude_range  ,longitude_format)   //090414
, elevation_parameter(elevation        ,elevation_param_props  ,elevation_range  ,elevation_format)   //120327
#else
:v_latitude_dec_deg  (latitude_dec_deg  ,UC_degrees_latitude  ,LABEL_latitude  ,4,DEF_latitude_dec_deg , -90.0,  90.0, -90.0,  90.0,"-90-90","Latitude")
,v_longitude_dec_deg (longitude_dec_deg ,UC_degrees_longitude ,LABEL_longitude ,4,DEF_longitude_dec_deg,-180.0, 180.0,-180.0, 180.0,"-180-180","Longitude") //991004
,v_elevation         (elevation         ,UC_meter             ,LABEL_elevation ,2,global_elevation_mean_meter/*151117 DEF_elevation;*/        ,   0.0,9999.0,   0.0,9999.9,"m","Elevation")        //000731
#endif
, ref_preferred_format(0)                                                        //140128
{  latitude_dec_deg = _latitude_dec_deg;
   longitude_dec_deg = _longitude_dec_deg;
   elevation = _elevation;                                                       //150817LML fixed an error
}
//_2012-03-25___________________________________________________________________
Geocoordinate::Geocoordinate(const Geocoordinate &copy_source)
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x570) || (CS_VERSION==5))
: latitude_parameter (latitude_dec_deg ,latitude_param_props ,latitude_range   ,latitude_format)  //120327
, longitude_parameter(longitude_dec_deg,longitude_param_props,longitude_range  ,longitude_format)        //090414
, elevation_parameter(elevation        ,elevation_param_props,elevation_range  ,elevation_format) //120327
#else
:v_latitude_dec_deg  (latitude_dec_deg  ,UC_degrees_latitude  ,LABEL_latitude  ,4,DEF_latitude_dec_deg , -90.0,  90.0, -90.0,  90.0,"-90-90"  ,"Latitude")
,v_longitude_dec_deg (longitude_dec_deg ,UC_degrees_longitude ,LABEL_longitude ,4,DEF_longitude_dec_deg,-180.0, 180.0,-180.0, 180.0,"-180-180","Longitude") //991004_
,v_elevation         (elevation         ,UC_meter             ,LABEL_elevation ,2,DEF_elevation        ,   0.0,9999.0,   0.0,9999.9,"m"       ,"Elevation") //000731
#endif
, ref_preferred_format(copy_source.ref_preferred_format)                         //140128
{  latitude_dec_deg    = copy_source.latitude_dec_deg;
   longitude_dec_deg   = copy_source.longitude_dec_deg;
   elevation           = copy_source.elevation;
   if (CORN::is_approximately<float32>(elevation,0.0,0.00001))                   //151117
      set_elevation_meter(global_elevation_mean_meter);                          //151117
}
//_2012-03-25___________________________________________________________________
Geocoordinate::Geocoordinate                                                     //151026
(const std::string &from_string
,const Geocoordinate_format &known_format)
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x570) || (CS_VERSION==5))
: latitude_parameter (latitude_dec_deg ,latitude_param_props   ,latitude_range   ,latitude_format)    //120327
, longitude_parameter(longitude_dec_deg,longitude_param_props  ,longitude_range  ,longitude_format)   //090414
, elevation_parameter(elevation        ,elevation_param_props  ,elevation_range  ,elevation_format)   //120327
#else
:v_latitude_dec_deg  (latitude_dec_deg  ,UC_degrees_latitude  ,LABEL_latitude  ,4,DEF_latitude_dec_deg , -90.0,  90.0, -90.0,  90.0,"-90-90","Latitude")
,v_longitude_dec_deg (longitude_dec_deg ,UC_degrees_longitude ,LABEL_longitude ,4,DEF_longitude_dec_deg,-180.0, 180.0,-180.0, 180.0,"-180-180","Longitude") //991004
,v_elevation         (elevation         ,UC_meter             ,LABEL_elevation ,2,DEF_elevation        ,   0.0,9999.0,   0.0,9999.9,"m","Elevation")        //000731
#endif
,ref_preferred_format(0)
{
   set_from_ISO_6709_specific_format(from_string,known_format);
}
//_2015-10-26___________________________________________________________________
Geocoordinate::Geocoordinate                                                     //151026
(const std::string &from_string)
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x570) || (CS_VERSION==5))
: latitude_parameter (latitude_dec_deg ,latitude_param_props   ,latitude_range   ,latitude_format)    //120327
, longitude_parameter(longitude_dec_deg,longitude_param_props  ,longitude_range  ,longitude_format)   //090414
, elevation_parameter(elevation        ,elevation_param_props  ,elevation_range  ,elevation_format)   //120327
#else
:v_latitude_dec_deg  (latitude_dec_deg  ,UC_degrees_latitude  ,LABEL_latitude  ,4,DEF_latitude_dec_deg , -90.0,  90.0, -90.0,  90.0,"-90-90","Latitude")
,v_longitude_dec_deg (longitude_dec_deg ,UC_degrees_longitude ,LABEL_longitude ,4,DEF_longitude_dec_deg,-180.0, 180.0,-180.0, 180.0,"-180-180","Longitude") //991004
,v_elevation         (elevation         ,UC_meter             ,LABEL_elevation ,2,DEF_elevation        ,   0.0,9999.0,   0.0,9999.9,"m","Elevation")        //000731
#endif
,ref_preferred_format(0)
{
   Geocoordinate_format surmised_format;                                         //161122
   set_from_ISO_6709(from_string,surmised_format);                               //161122
}
//_2015-10-26___________________________________________________________________
Geocoordinate::~Geocoordinate() {}
//_2013-05-15___________________________________________________________________
void Geocoordinate::copy_from_geocoordinate(const Geocoordinate &copy_source)
{  latitude_dec_deg   =copy_source.latitude_dec_deg;
   longitude_dec_deg  =copy_source.longitude_dec_deg;
   elevation          =copy_source.elevation;
   ref_preferred_format=copy_source.ref_preferred_format;                        //140128
}
//_copy_from_geocoordinate__________________________________________2012-03-25_/
bool Geocoordinate::compares_exactly_to_geocoordinate
(const Geocoordinate &other)                                        affirmation_
{  return
       (CORN::is_approximately<float32>(latitude_dec_deg,other.latitude_dec_deg,geocoordinate_approximation))
     &&(CORN::is_approximately<float32>(latitude_dec_deg,other.latitude_dec_deg,geocoordinate_approximation))
     &&(CORN::is_approximately<float32>(elevation,other.elevation,0.000001));
}
//_compares_exactly_to_geocoordinate________________________________2012-03-25_/
int Geocoordinate::compare(const Geocoordinate &other)              affirmation_
{
   bool lats_equal = CORN::is_approximately<float32>(latitude_dec_deg,other.latitude_dec_deg,geocoordinate_approximation);
   int compare_latitude =
      lats_equal ? 0 : (latitude_dec_deg > other.latitude_dec_deg) ? 1 : -1;
   bool longs_equal = CORN::is_approximately<float32>(longitude_dec_deg,other.longitude_dec_deg,geocoordinate_approximation);
   int compare_longitude =
      longs_equal
      ? 0 : (longitude_dec_deg > other.longitude_dec_deg) ? 1 : -1;
//   int compare = (compare_latitude == 0) && (compare_longitude == 0) ? 0 : compare_latitude;
   int compare =
      (compare_latitude == 0)
      ? (compare_longitude == 0)
         ? 0
         : compare_longitude
      : compare_latitude;
   return compare;
}
//_compare__________________________________________________________2016-09-02_/
float32 Geocoordinate::DMS_to_decimal_degrees(float32 degrees,float32 minutes, float32 seconds) const
{  bool west_south = degrees < 0.0;                                              //050614
   float32 dec_degrees = fabs(degrees) + (minutes / 60.0) + (seconds / 3600.0);  //151115_050614
   if (west_south)  dec_degrees = -dec_degrees;                                  //050614
   return dec_degrees;
}
//_DMS_to_decimal_degrees___________________________________________2005-04-01_/
float64 Geocoordinate::decimal_degrees_to_DMS(float64 decimal_degrees_signed,bool longitude, int16 &degrees,int16 &minutes, float64 &seconds,char &direction) const
{  float64 decimal_degrees = fabs(decimal_degrees_signed);
   degrees = decimal_degrees;
   float64 decimal =  decimal_degrees - degrees;
   float64 minutes_seconds = (decimal * 60.0);
   minutes = (int16)(minutes_seconds);
   float64 seconds_fract = minutes_seconds - minutes;
   seconds = seconds_fract * 60.0;
   direction = longitude
   ? (decimal_degrees < 0.0  ? 'W' : 'E')
   : (decimal_degrees < 0.0  ? 'S' : 'N');
   return decimal_degrees_signed;
}
//_decimal_degrees_to_DMS___________________________________________2005-04-01_/
char * Geocoordinate::decimal_degrees_to_DMS_cstr(float64 decimal_degrees,bool longitude,int decimals, char *buffer) const
{  // DMS will be formated D°M'S"d and will be appended to the buffer
   char direction;
   int16 degrees;
   int16 minutes;
   float64 seconds;
   decimal_degrees_to_DMS(decimal_degrees, longitude,degrees,minutes, seconds,direction);
   char buff[100]; buff[0] = 0;
   strcat(buffer,CORN::int16_to_cstr(degrees,buff,10));
   strcat(buffer,"°");
   strcat(buffer,CORN::int16_to_cstr(minutes,buff,10));
   strcat(buffer,"\'");
   strcat(buffer,CORN::float64_to_cstr(seconds,  decimals));
   strcat(buffer,"\"");
   int bufferlen = strlen(buffer);
   buffer[bufferlen++] = direction;
   buffer[bufferlen] = 0;
   return buffer;
}
//_decimal_degrees_to_DMS_cstr__________________________________________060106_/
std::string &Geocoordinate::decimal_degrees_to_DMS_string(float64 decimal_degrees,bool longitude,int decimals,std::string &append_buffer) const
{  // DMS will be formated D°M'S"d and will be appended to the buffer
   char buffer[100]; buffer[0] = 0;
   append_buffer.append(decimal_degrees_to_DMS_cstr(decimal_degrees, longitude, decimals, buffer));
   return append_buffer;
}
//_2010-01-07___________________________________________________________________
float64  Geocoordinate::get_latitude_radians()                               const
{  return deg_to_rad(latitude_dec_deg); }
//______________________________________________________________________________
float64  Geocoordinate::get_longitude_radians()                              const
{  return deg_to_rad(longitude_dec_deg); }
//_1999-10-04___________________________________________________________________
float32 Geocoordinate::set_latitude_dec_deg_f32  (float32 _latitude)
{  latitude_dec_deg     =_latitude;                                              //050601
   return latitude_dec_deg;
}
//______________________________________________________________________________
float32 Geocoordinate::set_longitude_dec_deg_f32 (float32 _longitude)
{  longitude_dec_deg    =_longitude;                                             //050601
   return longitude_dec_deg;
}
//______________________________________________________________________________
float64 Geocoordinate::set_latitude_dec_deg_f64  (float64 _latitude)
{  latitude_dec_deg     =_latitude;                                              //050601
   return latitude_dec_deg;
}
//______________________________________________________________________________
float64 Geocoordinate::set_longitude_dec_deg_f64 (float64 _longitude)
{  longitude_dec_deg    =_longitude;                                             //050601
   return longitude_dec_deg;
}
//______________________________________________________________________________
float32 Geocoordinate::set_latitude_DMS
(float32 degrees,float32 minutes, float32 seconds)                               //050526
{ return set_latitude_dec_deg_f32
   (DMS_to_decimal_degrees(degrees,minutes,seconds));}
//______________________________________________________________________________
float32 Geocoordinate::set_longitude_DMS
(float32 degrees,float32 minutes, float32 seconds)                               //050526
{ return set_longitude_dec_deg_f32(DMS_to_decimal_degrees(degrees,minutes,seconds));}
//______________________________________________________________________________
const char *Geocoordinate::label_string(std::string &buffer)               const
{
   if (ref_preferred_format)                                                     //140128
   {  std::string label;
      label_decimal_degrees_with_format
         (label
         ,ref_preferred_format->NSEW  // use N S E W  otherwise + -
         ,ref_preferred_format->precision_latitude
         ,ref_preferred_format->precision_longitude
         ,ref_preferred_format->zero_fill_char
         ,ref_preferred_format->elevation_units
         ,ref_preferred_format->separator);
      buffer += label;
   }
   else
   {
      decimal_degrees_to_DMS_string((float64)latitude_dec_deg,false,4,buffer);
      buffer += ", ";
      decimal_degrees_to_DMS_string((float64)longitude_dec_deg,true,4,buffer);
      buffer += ", ";
      CORN::append_float32_to_string(elevation, 2,buffer);
      buffer += "m";
   }
   return buffer.c_str();
}
//_label_string_____________________________________________________2017-04-23_/
std::string &Geocoordinate::label_decimal_degrees_with_format
(std::string &to_buffer
,bool NSEW  // use N S E W  otherwise + -
,nat8 precision_latitude
,nat8 precision_longitude
,char zero_fill_char                /*optional*/
,CORN::Units_code elevation_units   /*optional*/
,char  separator                    /*optional*/)                          const
//171228 ,char *separator                    /*optional*/)                          const
{
   //Latitude
   std::string lat_string;

   /* Conceptual may want to round the value, currently truncating
   float32 latitude_dec_deg_rounded =
   float32 longitude_dec_deg_rounded =
   */


   CORN::append_float32_to_string
      ((float32)fabs(latitude_dec_deg),precision_latitude,lat_string);
   size_t lat_pad_len = zero_fill_char
      ?(precision_latitude+3) - lat_string.length() //2 digits plus decimal point
      :0;
   std::string lat_padding(zero_fill_char,lat_pad_len);                          //140815
   if (lat_pad_len)  to_buffer.append(lat_padding);
   if (!NSEW) to_buffer.append(latitude_dec_deg>0?"+":"-");
   to_buffer.append(lat_string);
   if (NSEW)  to_buffer.append(latitude_dec_deg>0?"N":"S");
   if (separator) to_buffer+=separator; //171228 to_buffer.append(separator);
   //Longitude
   std::string long_string;
   CORN::append_float32_to_string
      ((float32)fabs(longitude_dec_deg),precision_longitude,long_string);        //151116
/*
   int long_pad_len = 0;
   if (zero_fill_char)
   {  long_pad_len += (int)(precision+4);  // 3 digits plus decimal point
      size_t long_str_len = (int)long_string.length();
      long_pad_len -=long_str_len;
   }
*/


   size_t long_pad_len = zero_fill_char
      ?(size_t)(precision_longitude+4) - (size_t)long_string.length()            //151116
         // 3 digits plus decimal point
      :0;

   std::string long_padding((size_t)long_pad_len,zero_fill_char);                //140805
   if (long_pad_len)  to_buffer.append(long_padding);
   if (!NSEW) to_buffer.append(longitude_dec_deg>0?"+":"-");
   to_buffer.append(long_string);
   if (NSEW)  to_buffer.append(longitude_dec_deg>0?"E":"W");
   // NYI may want to have elevation
   if (elevation_units)
   {  float32 elevation_in_preferred_units = elevation;
      if (separator) to_buffer += separator; //171228 to_buffer.append(separator);
      std::string units_code("m");
     /* conceptual not yet implemented
      switch (elevation_units)
      {
        case UC_feet :
         {
            // nyi
            //  elevation_in_preferred_units = convert value
            // units_code = lookup units code of elevation_units
         } break;

         case UC_meter :
         default :
         {
         } break;
      }
      */
      CORN::append_float32_to_string
         ((float32)fabs(elevation_in_preferred_units),0,to_buffer);
      to_buffer.append(units_code);
   }
   return to_buffer;
}
//_label_decimal_degrees_with_format___________________________________________/
bool Geocoordinate::setup_structure(CORN::Data_record &data_rec,bool for_write)  //contribution_
{
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x570) || (CS_VERSION==5))
   data_rec.expect_parameter(latitude_parameter);                                //090414
   data_rec.expect_parameter(longitude_parameter);                               //090414
   data_rec.expect_parameter(elevation_parameter);                               //090414
#else
   data_rec.expect_valid_float32(v_latitude_dec_deg);
   data_rec.expect_valid_float32(v_longitude_dec_deg);
   data_rec.expect_valid_float32(v_elevation);
#endif
   return true;
}
//_setup_structure_____________________________________________________________/
float32 Geocoordinate::set_latitude_dec_deg_cstr(const char *_latitude)
{  return set_latitude_dec_deg_f64(atof (_latitude));
}
//_2009-09-22___________________________________________________________________
float32 Geocoordinate::set_longitude_dec_deg_cstr(const char * _longitude)
{  return set_longitude_dec_deg_f64(atof (_longitude));
}
//_2009-09-22___________________________________________________________________
float32 Geocoordinate::set_elevation_meter_cstr(const char * _elevation)
{  return elevation = atof(_elevation);
}
//_2009-09-22___________________________________________________________________
float32 Geocoordinate::set_elevation_feet_cstr(const char * _elevation_feet)
{  return elevation = foot_to_m(atof(_elevation_feet));
}
//______________________________________________________________________________
float64 Geocoordinate::set_latitude_DMS_str(const char *_latitude)
{  float32 DMS[3] = {0,0,0};
   Coordinate_value coord_value = unknown_value;                                 //120327
   parse_DMS_or_decimal_deg(_latitude,coord_value,DMS);                          //120327
   return set_latitude_DMS(DMS[0],DMS[1],DMS[2]);
}
//______________________________________________________________________________
float64 Geocoordinate::set_longitude_DMS_str(const char *_longitude)
{  float32 DMS[3] = {0,0,0};
   //120327 parse_DMS(_longitude,DMS);
   Coordinate_value coord_value = unknown_value;                                 //120327
   parse_DMS_or_decimal_deg(_longitude,coord_value,DMS);                         //120327
   return set_longitude_DMS(DMS[0],DMS[1],DMS[2]);
}
//______________________________________________________________________________
bool Geocoordinate::parse_DMS_or_decimal_deg
(const char *str, Coordinate_value &value, float32 DMS[3])                 const
{
// value = unknown_value;
//   bool is_coordinate = true;
   bool parsed = false;                                                          //160127
   for (int c = 0; c < 3; c++) DMS[c] = 0;
   int number_index = 0;
   float32 number = 0;
// int whole_index = 0;
   int decimal_index = 0;
   bool in_number = false;
   bool negative = false;
   char str_i = str[0];
   for (int i = 0; str_i != 0 && !parsed; i++)                                   //180205
   {  str_i = str[i];
      if (isdigit(str_i))
      {  int digit = (int)str_i - 48;
         in_number = true;
         if (decimal_index)
         {  number += digit * pow(10.0,-decimal_index);
            decimal_index++;
         }
         else
         {  number *= 10;
//          in_numbertrue;
            number += digit;
         }
         DMS[number_index] = number;
      } else
      {  switch (str_i)
         {  case 'W' :  case 'w' :
               negative = true;  in_number = false; decimal_index = 0;  value = longitude_value; parsed=true;
            break;
            case 'S' :  case 's' :
               negative = true;  in_number = false; decimal_index = 0;  value = latitude_value; parsed=true;
            break;
            case 'N' : case 'n' :
               negative = false; in_number = false; decimal_index = 0;  value = latitude_value; parsed=true;
            break;
            case 'E' : case 'e' :
               negative = false; in_number = false; decimal_index = 0;  value = longitude_value; parsed=true;
            break;
            case  '°' : DMS[0] = number; parsed=in_number; in_number = false; number_index = 1; number = 0; break; //140531
            case '\'' : DMS[1] = number; parsed=in_number; in_number = false; number_index = 2; number = 0; break; //140531
            case '\"' : DMS[2] = number; parsed=in_number; in_number = false; number = 0; break;   //140531
            case '.'  : decimal_index = 1; break;
            case '-'  : negative = true; break;
            case '+'  : negative = false; break;
            default :
            {  // at white space or degree or " or ' indicator, or other.
               if (isalpha(str_i))
               {
                   in_number=false; //180205 ignore the rest of the line // 180205return false;
               }
               decimal_index = 0;
               number = 0;
               if (in_number)
                  number_index++;
               else
                  in_number = false;
            } break;
         }
      }
   }
//   if (number_index)                                                             //151115
//   {
      if (DMS[0] > 90.0)  value = longitude_value;
//   } else value = unknown_value;                                                 //151115
   if (negative) DMS[0] = -DMS[0];
   return parsed; //160127value != unknown_value;
}
//_parse_DMS_or_decimal_deg_________________________________________2012-03-26_/
bool Geocoordinate::has_valid_geocoordinates()                             const
{  bool valid = !(CORN::is_approximately<float32>(latitude_dec_deg ,0.0,0.0001) &&
                  CORN::is_approximately<float32>(longitude_dec_deg,0.0,0.0001));
   return valid;
}
//_has_valid_geocoordinates_________________________________________2010-02-04_/
bool Geocoordinate::set_latitude_and_longitude
(const std::string &lat_long_str, bool coordinate_order_lat_long)   assignation_
{  bool parsed_valid_coords = false;                                             //151115
   size_t lat_end = std::string::npos;                                           //170212
   size_t long_start = std::string::npos;                                        //170212
   size_t delim_pos = lat_long_str.find_first_of(" ,\t");
   if (delim_pos != std::string::npos)                                           //170212
   {
      lat_end = delim_pos;
      long_start = delim_pos+1;
   } else
   {  delim_pos = lat_long_str.find_first_of("NS");
      if (delim_pos != std::string::npos)
      {
         lat_end = delim_pos+1;
         long_start = delim_pos+1;
      }
   }
   if (lat_end == std::string::npos) return false;                               //170212

   std::string coord_1(lat_long_str,0,lat_end);
   std::string coord_2(lat_long_str,long_start);
   float32 DMS_1[3];
   float32 DMS_2[3];
   Coordinate_value coord_1_value = coordinate_order_lat_long ? latitude_value  : longitude_value;
   Coordinate_value coord_2_value = coordinate_order_lat_long ? longitude_value : latitude_value;
   if ( parse_DMS_or_decimal_deg(coord_1.c_str(), coord_1_value, DMS_1)
      &&parse_DMS_or_decimal_deg(coord_2.c_str(), coord_2_value, DMS_2))
   {  parsed_valid_coords = true;                                                //151115
      if (coord_1_value == latitude_value)
      {
         set_latitude_DMS  (DMS_1[0],DMS_1[1],DMS_1[2]);
         set_longitude_DMS (DMS_2[0],DMS_2[1],DMS_2[2]);
      } else
      {  set_latitude_DMS  (DMS_2[0],DMS_2[1],DMS_2[2]);
         set_longitude_DMS (DMS_1[0],DMS_1[1],DMS_1[2]);
      }
   }
   return parsed_valid_coords;                                                   //151115
}
//_set_latitude_and_longitude_______________________________________2012-03-26_/
bool Geocoordinate::surmise_ISO_6709
(Geocoordinate_format &format
,const std::string          &from_string)
{
   bool recognized = false;
   format.order[0] = 0; //lat
   format.order[1] = 1; //long
   format.order[2] = 2; //elev
   format.zero_fill_char = '0';
   format.decimal        = decimal_degrees;
   nat8 leading_digits = 0;
   nat8 leading_digits_latitude_ = 0;
   nat8 leading_digits_longitude_ = 0;
   nat8 precision = 0;
   nat8 sign_count = 0;
   //170217 bool in_longitude = false;
   bool in_elevation = false;
   bool in_decimal = false;

   nat8 order_index = 0;
   for (std::size_t pos = 0; pos < from_string.length(); pos++)
   {
      char char_at_pos = from_string.at(pos);
      switch (char_at_pos)
      {
         case '+' : case '-' :
            recognized = true;
            if (sign_count == 0) {} //in latitude
            if (sign_count == 1) //finishing latitude entering  longitude
               { leading_digits_latitude_ = leading_digits;  format.precision_latitude = precision; }
            if (sign_count == 2) //finishing longitude entering elevation
               { leading_digits_longitude_ = leading_digits; format.precision_longitude = precision; }
            leading_digits = 0;
            precision = 0; ;
            sign_count++;
            in_decimal = false; if (sign_count == 3) in_elevation = true;
         break;
         case 'N' : case 'S' : format.order[order_index++] = 0; format.NSEW = true; in_decimal = false; leading_digits_latitude_  = leading_digits; in_elevation = true; format.precision_latitude  = precision; precision = 0; leading_digits = 0; recognized = true; break;
         case 'E' : case 'W' : format.order[order_index++] = 1; format.NSEW = true; in_decimal = false; leading_digits_longitude_ = leading_digits;                      format.precision_longitude = precision; precision = 0; leading_digits = 0; recognized = true; break;
         case '.' : in_decimal = true; break;
         case ' ' : format.separator = ' '/*171228 " "*/;  break;
         default :
            if (isdigit(char_at_pos) && !in_elevation)
            {
               if (in_decimal)
               {  precision += 1;
                  //if (in_longitude) format.precision_longitude +=1;
                  //else              format.precision_latitude  +=1;
               } else
               {  leading_digits += 1;
                  //if (in_longitude) leading_digits_longitude +=1;
                  // else              leading_digits_latitude  +=1;
               }
            }
         break;
      } // switch
   }
   if (sign_count == 2)
   {  leading_digits_longitude_ = leading_digits;
      format.precision_longitude = precision;
   }
   switch (leading_digits_longitude_)
   {
      case 3 : format.decimal = decimal_degrees; break;
      case 5 : format.decimal = decimal_minutes; break;
      case 7 : format.decimal = decimal_seconds; break;
   }
   if (sign_count >= 2) format.NSEW = false;
   if (in_elevation) format.elevation_units = UC_meter;
   return recognized;
}
//_surmise_ISO_6709_________________________________________________2015-10-26_/
struct Extent_context
{
   bool  negative;
   int   integer;
   nat8  integer_digit_count;
   float fraction;
   float decimal_factor;
   nat8  decimal_digit_count;

//   nat8  decimal_digit;

   bool  in_decimals;
   nat8  integer_digits_max;
 public:
   inline void clear()
      {
         negative    = false;
         integer     = 0;
         integer_digit_count = 0;
         fraction    = 0;
         decimal_factor = 1;
         decimal_digit_count = 0;
         in_decimals = false;
         integer_digits_max = 2;
      }

   inline float to_float()
      {  float as_float = (float)integer + fraction;
         if (negative)  as_float = - as_float;
         return as_float;
      }

   bool take_digit(char digit_ASCII)
   {
      nat8 digit = digit_ASCII - '0';
      bool at_max_integer = false;
      if (in_decimals)
      {  decimal_digit_count ++;
         decimal_factor /= 10.0;
         float decimal_digit = digit * decimal_factor;
         fraction += decimal_digit;
      } else
      {
         integer *= 10;
         integer += digit;
         integer_digit_count += 1;
         at_max_integer = integer_digit_count >= integer_digits_max;
      }
      return at_max_integer;
   }
};
//_Extent_context___________________________________________________2015-10-26_/
bool Geocoordinate::set_from_ISO_6709_specific_format
(const std::string &from_string
,const Geocoordinate_format &known_format)                         modification_
{
   //170217 nat8 in_lat_long_elev = 0; // 0=lat 1=long 2=elevation
   nat8 in_DMSE = 0; // 0 = degree, 1 = minute, 2 = second
   Extent_context context
      [3] // 0=lat 1=long 2=elevation
      [3]; // DMS
   for (nat8 lle = 0; lle <=2; lle++)
      for (nat8 dms = 0; dms <= 2; dms++)
      {
         context[lle][dms].clear();
         context[lle][dms].integer_digits_max = 2;
      }
   context[0][0].integer_digits_max = 2; // latitude degrees
   context[1][0].integer_digits_max = 3; // longitude degress
   context[2][2].integer_digits_max = 9;
   nat8 order_index_ = 0;
   nat8 sign_count = 0;
   for (std::size_t pos = 0; pos < from_string.length(); pos++)
   {
      if (sign_count)
      {  order_index_ = sign_count;
      }
      nat8 lle = known_format.order[order_index_];

         // Currently in the case of +or- always assume lat long elev
      Extent_context &context_curr = context[lle][in_DMSE];                      //160124
      char char_at_pos = from_string.at(pos);
      switch (char_at_pos)
      {
         case '+' :
            context[lle][0].negative = false;
            sign_count++;
            in_DMSE = 0;
         break;
         case '-' :
            context[lle][0].negative = false;
            sign_count++;
            in_DMSE = 0;
         break;
         case 'N' :
            context[0][0].negative     = false;                                  //160123
//            in_lat_long_elev = 1; // we've finished latitude now expecting longitude
            order_index_++;
            in_DMSE = 0;
         break;
         case 'S' :
            context[0][0].negative     = true;
//            in_lat_long_elev = 1; // we've finished latitude now expecting longitude
            order_index_++;
            in_DMSE = 0;
         break;
         case 'E' :
            context[1][0].negative     = false;
//            in_lat_long_elev = 2; // we've finished now expecting elevation
            order_index_++;
            in_DMSE = 0;
         break;
         case 'W' :
            context[1][0].negative     = true;
//            in_lat_long_elev = 2; // we've finished now expecting elevation
            order_index_++;
            in_DMSE = 0;
         break;
         case '.' :
            context_curr.in_decimals = true;                                     //160123
         break;
         /*
         case ' ' : format.separator = ' ';
         break;
         */
         default :
            if (std::isdigit(char_at_pos))
            {
               bool at_max_integer  =
                  //150124 context[in_lat_long_elev][in_DMSE]
                  context_curr.take_digit(char_at_pos);
               char char_next = from_string.at(pos+1);
               bool next_char_is_decimal_point = (char_next == '.') || (char_next == ',');
               if (at_max_integer && !context_curr.in_decimals && !next_char_is_decimal_point)
                  in_DMSE += 1;
            }
         break;
      } // switch
   }
   switch (known_format.decimal)
   {
      case decimal_degrees :
         set_latitude_dec_deg_f32 ((float32)context[0][0].to_float());
         set_longitude_dec_deg_f32((float32)context[1][0].to_float());
      break;
      case decimal_minutes :
         set_latitude_DMS     (context[0][0].to_float(),context[0][1].to_float(),0);
         set_longitude_DMS    (context[1][0].to_float(),context[1][1].to_float(),0);
      break;
      case decimal_seconds :
         set_latitude_DMS     (context[0][0].to_float(),context[0][1].to_float(),context[0][2].to_float());
         set_longitude_DMS    (context[1][0].to_float(),context[1][1].to_float(),context[1][2].to_float());
      break;
   }
   if (known_format.elevation_units == UC_meter)
   {
      float32 elevation = context[2][0].to_float();
      if (elevation) set_elevation_meter(elevation);
   }
   return true;
}
//_set_from_ISO_6709_specific_format________________________________2015-10-26_/
bool Geocoordinate::set_from_ISO_6709
(const std::string &from_string
,Geocoordinate_format &surmised_format) // returned identified format            //161122
{  bool sat = true;
   sat = surmise_ISO_6709(surmised_format,from_string);
   if (sat)                                                                      //160123
      sat = set_from_ISO_6709_specific_format(from_string,surmised_format);
   return sat;
}
//_set_from_ISO_6709________________________________________________2015-10-26_/
bool Geocoordinate::is_valid()                                      affirmation_
{  return
      !CORN::is_approximately<float32>(latitude_dec_deg,DEF_latitude_dec_deg,0.00001)
   && !CORN::is_approximately<float32>(longitude_dec_deg,DEF_longitude_dec_deg,0.0001); //170614
}
//_is_valid_________________________________________________________2015-12-08_/


