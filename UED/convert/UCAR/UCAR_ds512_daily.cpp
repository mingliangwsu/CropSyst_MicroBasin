
/*
   this is coded instead of using TDF because
   1. There are a quality markers
   2. The records are variable length  (for different versions)


UCAR ds512.0 FORMAT NEW DAILY
From WWW page http://dss.ucar.edu/datasets/ds512.0/docs/format_dlynew.html

University Corporation for Atmospheric Research

As of Dec. 9 2005

*/

#include "UED/convert/convertor.h"
#include "UED/convert/station_database.h"
#include <ctype.h>
#include "UED/locrec.h"
//______________________________________________________________________________
struct Sky_and_Wind
{
   char  TOTAL_SKY_COVER[2];
   char  WIND_DIRECTION[2];
   char  WIND_SPEED[3];
};
//______________________________________________________________________________
struct Sky_and_Wind_expanded
{
   char  TOTAL_SKY_COVER[3];
   char  WIND_DIRECTION[3];
   char  WIND_SPEED[4];
};
//______________________________________________________________________________
enum DS512_format
{UNKNOWN_DS512
,DS512_AB_PRE_SEPT_1982
,DS512_AB_POST_SEPT_1982
,DS512_AB_PRE_SEPT_1982_EXPANDED
,DS512_AB_POST_SEPT_1982_EXPANDED
,DS512_PRE_1994
,DS512_POST_1994
,DS512_PRE_1994_EXPANDED
,DS512_POST_1994_EXPANDED
};

/* NYI
Didn't implement this yet because probably obsolete
struct UCAR_ds512_PRE_1994_raw_format
{
};

*/
//______________________________________________________________________________
struct UCAR_ds512_daily_raw_format
{
   char  BLANK_carridge_control;  // 0. BLANK - 1X
   char  IDATE_yyyymmdd;          // GREENWICH MEAN DATE OF DATA, IN THE FORM YYYYMMDD. (RLN I don't think I will need to convert)
   char  BKIDN[5];               // WMO 5-DIGIT STATION IDENTIFIER OR 99 FOLLOWED BY A 3  LETTER AIRWAYS CALLSIGN FOR THOSE LOCATIONS  FOR WHICH NO WMO NUMBER HAS BEEN ASSIGNED.
   char  RMAX[5];                // 24 HOUR MAXIMUM TEMPERATURE DEGREES CELSIUS.  MAY BE ESTIMATED FROM REPORTED SYNOPTIC AIR TEMPERATURES IF SUFFICIENT DATA EXIST. MISSING - -99.9
   char  RMIN[5];                // 24 HOUR MINIMUM TEMPERATURE. MAY BE ESTIMATED FROM REPORTED SYNOPTIC AIR TEMPERATURES IF SUFFICIENT DATA EXIST.                  MISSING - -99.9
   char  RPRCP[6];               // RPRCP-TOTAL OF PRECIPITATION REPORTED DURING THE 24 HOUR PERIOD. MILLIMETERS.
   char  EPRCP[6];               // TOTAL OF PRECIPITATION INCLUDING ESTIMATES FOR ANY PERIOD FOR WHICH THERE WAS NO REPORTED AMOUNT. MILLIMETERS.
   char  VP[6];                  // VP-VAPOR PRESSURE MILLIBARS
   char  POTEV[6];               // POTENTIAL EVAPOTRANSPIRATION MILLIMETERS
   char  VPD[6];                 // VAPOR PRESSURE DEFICIT MILLIBARS
   char  SLP06[6];               // 0600Z SEA LEVEL PRESSURE   MILLIBARS
   char  SLP12[6];               // 1200Z SEA LEVEL PRESSURE   MILLIBARS
   char  SLP18[6];               // 1800Z SEA LEVEL PRESSURE   MILLIBARS
   char  SLP00[6];               // 0000Z SEA LEVEL PRESSURE   MILLIBARS                (note that 00Z is for the following day)

   char  APTMX[6];               // MAXIMUM APPARENT TEMPERATURE   DEGREES CELSIUS
   char  CHILLM[5];              // MINIMUM WIND CHILL  DEGREES CELSIUS
   char  RAD[5];                 // NET RADIATION UNITS - ???
   char  MAXFL;                  // MAXIMUM TEMPERATURE FLAG.
   char  MINFL;                  // INIMUM TEMPERATURE FLAG.
   char  IFPRQ;                  // PRECIPITATION QUALITY FLAG
   char  IFPRT;                  // PRECIPITATION TIME FLAG INDICATING THE ENDING TIME
   char  NOBS;                   // NUMBER OF 3 HOUR PERIODS FOR WHICH AT LEAST ONE
   char  NOBSP;                   // NUMBER OF 3 HOUR PERIODS DURING THE DAY IN WHICH PAST OR PRESENT WEATHER INDICATED PRECIPITATION.
   char  NOPE;                   // NUMBER OF 6 HOUR PERIODS THAT PRECIPITATION WAS ESTIMATED.
   char  NTRACE;                 // PRECIPITATION TRACE INDICATOR

   char  IWW[8];                    // PRESENT/PAST WEATHER CHARACTER FLAGS.
   char  MXRH[3];                // THE MAXIMUM RELATIVE HUMIDITY. %
   char  MNRH[3];                // THE MINIMUM RELATIVE HUMIDITY.
   char  space3;
   char  IFVPQ;                  // VAPOR PRESSURE QUALITY FLAG.

   // The following variables are not included prior to Jan 1994
   Sky_and_Wind sky_and_wind[8];

   char  TOTAL_SNOW_DEPTH[5];     // CENTIMETERS WHEN REPORTED, ZERO SNOW DEPTH IS NOT REPORTED AND IS INDICATED AS MISSING IN THIS FILE
   char  blanks[5];
};
//______________________________________________________________________________

struct UCAR_ds512_daily_raw_format_expanded
{
   char  BLANK_carridge_control;  // 0. BLANK - 1X
   char  IDATE_yyyymmdd[8];          // GREENWICH MEAN DATE OF DATA, IN THE FORM YYYYMMDD. (RLN I don't think I will need to convert)
   char  space1;
   char  BKIDN[5];               // WMO 5-DIGIT STATION IDENTIFIER OR 99 FOLLOWED BY A 3  LETTER AIRWAYS CALLSIGN FOR THOSE LOCATIONS  FOR WHICH NO WMO NUMBER HAS BEEN ASSIGNED.
   char  RMAX[6];                // 24 HOUR MAXIMUM TEMPERATURE DEGREES CELSIUS.  MAY BE ESTIMATED FROM REPORTED SYNOPTIC AIR TEMPERATURES IF SUFFICIENT DATA EXIST. MISSING - -99.9
   char  RMIN[6];                // 24 HOUR MINIMUM TEMPERATURE. MAY BE ESTIMATED FROM REPORTED SYNOPTIC AIR TEMPERATURES IF SUFFICIENT DATA EXIST.                  MISSING - -99.9
   char  RPRCP[7];               // RPRCP-TOTAL OF PRECIPITATION REPORTED DURING THE 24 HOUR PERIOD. MILLIMETERS.
   char  EPRCP[7];               // TOTAL OF PRECIPITATION INCLUDING ESTIMATES FOR ANY PERIOD FOR WHICH THERE WAS NO REPORTED AMOUNT. MILLIMETERS.
   char  VP[7];                  // VP-VAPOR PRESSURE MILLIBARS
   char  POTEV[7];               // POTENTIAL EVAPOTRANSPIRATION MILLIMETERS
   char  VPD[7];                 // VAPOR PRESSURE DEFICIT MILLIBARS
   char  SLP06[7];               // 0600Z SEA LEVEL PRESSURE   MILLIBARS
   char  SLP12[7];               // 1200Z SEA LEVEL PRESSURE   MILLIBARS
   char  SLP18[7];               // 1800Z SEA LEVEL PRESSURE   MILLIBARS
   char  SLP00[7];               // 0000Z SEA LEVEL PRESSURE   MILLIBARS                (note that 00Z is for the following day)

   char  APTMX[7];               // MAXIMUM APPARENT TEMPERATURE   DEGREES CELSIUS
   char  CHILLM[6];              // MINIMUM WIND CHILL  DEGREES CELSIUS
   char  RAD[6];                 // NET RADIATION UNITS - ???
   char  space2;
   char  MAXFL;                  // MAXIMUM TEMPERATURE FLAG.
   char  space3;
   char  MINFL;                  // INIMUM TEMPERATURE FLAG.
   char  space4;
   char  IFPRQ;                  // PRECIPITATION QUALITY FLAG
   char  space5;
   char  IFPRT;                  // PRECIPITATION TIME FLAG INDICATING THE ENDING TIME
   char  space6;
   char  NOBS;                   // NUMBER OF 3 HOUR PERIODS FOR WHICH AT LEAST ONE
   char  space7;
   char  NOBSP;                  // NUMBER OF 3 HOUR PERIODS DURING THE DAY IN WHICH PAST OR PRESENT WEATHER INDICATED PRECIPITATION.
   char  space8;
   char  NOPE;                   // NUMBER OF 6 HOUR PERIODS THAT PRECIPITATION WAS ESTIMATED.
   char  space9;
   char  NTRACE;                 // PRECIPITATION TRACE INDICATOR
   char  space10;
   char  IWW[8];                    // PRESENT/PAST WEATHER CHARACTER FLAGS.
   char  MXRH[4];                // THE MAXIMUM RELATIVE HUMIDITY. %
   char  MNRH[4];                // THE MINIMUM RELATIVE HUMIDITY.
   char  space11;
   char  IFVPQ;                  // VAPOR PRESSURE QUALITY FLAG.

   // The following variables are not included prior to Jan 1994
   Sky_and_Wind_expanded sky_and_wind[8];

   char  TOTAL_SNOW_DEPTH[6];     // CENTIMETERS WHEN REPORTED, ZERO SNOW DEPTH IS NOT REPORTED AND IS INDICATED AS MISSING IN THIS FILE
   //    5 blanks are not in the expanded version
};
//______________________________________________________________________________
class UCAR_ds512_daily_record
{
public:  // imported fields
   CORN::Date  date;
   Ustring     BKIDN;

   float32     RMAX_value;          Units_code RMAX_units;        CORN::Quality_code  RMAX_quality;
   float32     RMIN_value;          Units_code RMIN_units;        CORN::Quality_code  RMIN_quality;
   float32     RPRCP_value;         Units_code RPRCP_units;       CORN::Quality_code  RPRCP_quality;
   float32     EPRCP_value;         Units_code EPRCP_units;       CORN::Quality_code  EPRCP_quality;

   float32     precipitation_mm;    Units_code precipitation_units; CORN::Quality_code  precipitation_quality;
   // Currently we store the base of the two precip values

//NYI need millibar conversion   float32     VP_value;            Units_code VP_units;          CORN::Quality_code  VP_quality;
//NYI  not sure what basis  float32     POTEV_value;         Units_code POTEV_units;       CORN::Quality_code  POTEV_quality;
//NYI need millibar conversion     float32     VPD_value;           Units_code VPD_units;         CORN::Quality_code  VPD_quality;
/* NYI         SLP06
               SLP12
               SLP18
               SLP00
               APTMX
               CHILLM
               RAD
               MAXFL
               MINFL
   float32     xxxxx_value;         Units_code xxxx_units;        CORN::Quality_code  xxxxx_quality;
*/
   float32     MXRH_value;         Units_code MXRH_units;        CORN::Quality_code  MXRH_quality;
   float32     MNRH_value;         Units_code MNRH_units;        CORN::Quality_code  MNRH_quality;

public:  // constructor

   // Need constructors for each format raw record

//NYI   UCAR_ds512_daily_record(UCAR_ds512_daily_raw_format          &raw_record,bool pre1994);
   UCAR_ds512_daily_record(UCAR_ds512_daily_raw_format_expanded &raw_record,bool pre1994);
};
//______________________________________________________________________________
UCAR_ds512_daily_record::UCAR_ds512_daily_record(UCAR_ds512_daily_raw_format_expanded &raw_record,bool pre1994)
{
   // With the expanded formats, the record fields are always followed by a space so we can use str_to_xxx
   // the unexpanded format will need to extract the field carefully;

   char  BKIDN_cstr[6]; strncpy(BKIDN_cstr,raw_record.BKIDN,5);
   BKIDN.assign(BKIDN_cstr);

   date.format(D_YMD, D_YYYY|D_M|D_lead_zero,0,false);
   date.set_c_str(raw_record.IDATE_yyyymmdd);


   RMAX_value = atof(raw_record.RMAX);
   RMAX_units  = UC_celcius;
   RMAX_quality = measured_quality;  // presume measure unless otherwise identified
   int strcmp_result = 0;
   if ((strcmp_result = strncmp(raw_record.RMAX," -99.9",6)) == 0)
   RMAX_quality = missing_quality;
   if (raw_record.MAXFL == '1')                 RMAX_quality = calculated_quality;   // Don't know specifically what these three code are
   if (raw_record.MAXFL == '2')                 RMAX_quality = calculated_quality;   // The docs simply VALUE DERIVED FROM AIR TEMPERATURES
   if (raw_record.MAXFL == '3')                 RMAX_quality = calculated_quality;   // So I am using  calculated_quality but could be interpolated or estimated
   if (raw_record.MAXFL == '9')                 RMAX_quality = missing_quality;

//cout << strcmp_result << endl;

   RMIN_value = atof(raw_record.RMIN);
   RMIN_units  = UC_celcius;
   RMIN_quality = measured_quality;  // presume measure unless otherwise identified
   if ((strcmp_result = strncmp(raw_record.RMIN," -99.9",6)) == 0)
   RMIN_quality = missing_quality;
   if (raw_record.MINFL == '1')                 RMIN_quality = calculated_quality;   // Don't know specifically what these three code are
   if (raw_record.MINFL == '2')                 RMIN_quality = calculated_quality;   // The docs simply VALUE DERIVED FROM AIR TEMPERATURES
   if (raw_record.MINFL == '3')                 RMIN_quality = calculated_quality;   // So I am using  calculated_quality but could be interpolated or estimated
   if (raw_record.MINFL == '9')                 RMIN_quality = missing_quality;


   RPRCP_value = atof(raw_record.RPRCP);
   RPRCP_units = UC_mm;
   RPRCP_quality = measured_quality;  // presume measure unless otherwise identified
   if (strncmp(raw_record.RPRCP,"  -99.9",7) == 0)
   RPRCP_quality = missing_quality;
   if (raw_record.IFPRQ == '3')                 RPRCP_quality = interpolated_quality; // Only some parts of the day were included in the total daily value (there could have been more).
   if (raw_record.IFPRQ == '7')                 RPRCP_quality = missing_quality; // Appears to be a missing code  (maybe trace?)
   if (raw_record.IFPRQ == '9')                 RPRCP_quality = missing_quality;

   EPRCP_value = atof(raw_record.EPRCP);
   EPRCP_units = UC_mm;
   EPRCP_quality = measured_quality;  // presume measure unless otherwise identified
   if (strncmp(raw_record.EPRCP,"  -99.9",7) == 0)
   EPRCP_quality = missing_quality;
   if (raw_record.IFPRQ == '3')                 EPRCP_quality = interpolated_quality; // Only some parts of the day were included in the total daily value (there could have been more).
   if (raw_record.IFPRQ == '7')                 EPRCP_quality = missing_quality; // Appears to be a missing code  (maybe trace?)
   if (raw_record.IFPRQ == '9')                 EPRCP_quality = missing_quality;


   // This is the actual precipitation that will be stored in the database
   precipitation_mm = RPRCP_value;
   precipitation_units = UC_mm;
   precipitation_quality = RPRCP_quality;
   if (RPRCP_quality != measured_quality)
   {  if (quality_is_better_than(EPRCP_quality,RPRCP_quality))
      {  precipitation_mm = EPRCP_value;
         precipitation_quality = EPRCP_quality;
      }
   }

   MXRH_value = atoi(raw_record.MXRH);
   MXRH_units = UC_percent;
   MXRH_quality = measured_quality;
   if ((strcmp_result = strncmp(raw_record.MXRH," -99",3)) == 0)
      MXRH_quality = missing_quality;

   MNRH_value = atoi(raw_record.MNRH);
   MNRH_units = UC_percent;
   MNRH_quality = measured_quality;
   if ((strcmp_result = strncmp(raw_record.MNRH," -99",3)) == 0)
      MNRH_quality = missing_quality;


   // wind and snow not yet imported


//cout << strcmp_result << endl;
   // NYI the other fields...
}
//______________________________________________________________________________
struct UCAR_ds512_daily_AB_raw_format
{
   char  BLANK_carridge_control;  // 0. BLANK - 1X
   char  YY[2];
   char  MM[2];
   char  DD[2];
   char  filler1;
   char  WMO_STATION_ID[5];
   char  filler2;
   char  AIRWAYS_CALLSIGN[4];
   char  LATITUDE_CODE[6];    // latitude in 100ths of degree
   char  LONGITUDE_CODE[6];   // longitude in 100ths of degree
   char  ELEVATION[5];
   char  MAX_TEMPERATURE[5];
   char  MAX_TEMP_FLAGa;
   char  MAX_TEMP_FLAGb;
   char  MIN_TEMPERATURE[6];
   char  MIN_TEMP_FLAGa;
   char  MIN_TEMP_FLAGb;
   char  TOTAL_DAILY_PRECIP[5];
   char  FLAG_24_HR_PRECIP3a;
   char  FLAG_24_HR_PRECIP3b;
   char  PRECIP_TRACE_FLAG;
   char  PRESENT_PAST_WEA_FLAGS[8];
   char  NUMBER_OF_OBS_RCVD[2];
   char  NMBR_OBS_REPORTING_PRESENT_PAST_WEA[2];
   // The following are not included prior to Sept 1982
   char  TOT_PRECIP_RPTD_DURING_24HR[6];
   char  TOT_ESTMTD_PRECIP[6];
   char  NMBR_6HR_PERIODS_DURING_24HR[2];
};
//______________________________________________________________________________
struct UCAR_ds512_daily_AB_raw_format_expanded
{
   char  BLANK_carridge_control;  // 0. BLANK - 1X
   char  YY[3];
   char  MM[3];
   char  DD[3];
   char  filler1;
   char  WMO_STATION_ID[5];
   char  filler2;
   char  AIRWAYS_CALLSIGN[4];
   char  LATITUDE_CODE[7];    // latitude in 100ths of degree
   char  LONGITUDE_CODE[7];    // longitude in 100ths of degree
   char  ELEVATION[6];
   char  MAX_TEMPERATURE[6];
   char  filler3;
   char  MAX_TEMP_FLAGa;
   char  MAX_TEMP_FLAGb;
   char  MIN_TEMPERATURE[6];
   char  filler4;
   char  MIN_TEMP_FLAGa;
   char  MIN_TEMP_FLAGb;
   char  TOTAL_DAILY_PRECIP[6];
   char  filler5;
   char  FLAG_24_HR_PRECIP3a;
   char  FLAG_24_HR_PRECIP3b;
   char  space1[2];
   char  PRECIP_TRACE_FLAG;
   char  space2[1];
   char  PRESENT_PAST_WEA_FLAGS[8];
   char  NUMBER_OF_OBS_RCVD[3];
   char  NMBR_OBS_REPORTING_PRESENT_PAST_WEA[3];
   // The following are not included prior to Sept 1982
   char  TOT_PRECIP_RPTD_DURING_24HR[7];
   char  TOT_ESTMTD_PRECIP[7];
   char  NMBR_6HR_PERIODS_DURING_24HR[3];
   // Remainder filler 6X characters
};
//______________________________________________________________________________

class UCAR_ds512_daily_AB_record
{
public:
   CORN::Date  date;

//   char  YY[2];
//   char  MM[3];
//   char  DD[3];
   Ustring WMO_station_ID;    // Appears to be the same coding a BKIDN
   Ustring airways_callsign;
   float32 latitude_dec_deg;     // from LATITUDE_CODE
   float32 longitude_dec_deg_360;    // from LONGITUDE_CODE  (NOTE degrees west of Greenwich)
   float32 elevation_m;          // from ELEVATION[6]
   float32 max_temperature;   CORN::Quality_code max_temperature_quality; Units_code   max_temperature_units; // celcius
   float32 min_temperature;   CORN::Quality_code min_temperature_quality; Units_code   min_temperature_units; // celcius
   float32 total_daily_precip;CORN::Quality_code precip_quality;          Units_code    precipitation_units;  // mm


// NYI PRESENT_PAST_WEA_FLAGS[8];
// NYI NUMBER_OF_OBS_RCVD[3];
// NYI NMBR_OBS_REPORTING_PRESENT_PAST_WEA[3];
   // The following are not included prior to Sept 1982
   // These totals and estimate precip values appear to be
   // If total_daily_precip is 999.9 there may be avalue in TOT_ESTMTD_PRECIP
   // which we will record in the UED.
   float32 tot_precip_rptd_during_24hr;
   float32 tot_estmtd_precip;
// NYI NMBR_6HR_PERIODS_DURING_24HR[3];
   // Remainder filler 6X characters

public:

//   UCAR_ds512_daily_AB_record(UCAR_ds512_daily_AB_pre_1982_raw_format &raw);
   UCAR_ds512_daily_AB_record(UCAR_ds512_daily_AB_raw_format &raw         ,bool pre_sept_1982);
   UCAR_ds512_daily_AB_record(UCAR_ds512_daily_AB_raw_format_expanded &raw,bool pre_sept_1982);

   void clear();

private:
   Quality_code convert_temperature_quality(char A_flag, char B_flag) const;
   Quality_code convert_precipitation_quality(char A_flag, char B_flag, char trace_flag) const;

};
//______________________________________________________________________________
void UCAR_ds512_daily_AB_record::clear()
{
   WMO_station_ID.assign("");    // Appears to be the same coding a BKIDN
   airways_callsign.assign("");
   latitude_dec_deg= 0;     // from LATITUDE_CODE
   longitude_dec_deg_360 = 0;    // from LONGITUDE_CODE
   elevation_m = 0;          // from ELEVATION[6]
   max_temperature= 0;      // celcius
   max_temperature_quality = missing_quality;
   min_temperature= 0;      // celcius
   min_temperature_quality = missing_quality;
   total_daily_precip= 0;   // mm
   precip_quality = missing_quality;
   tot_precip_rptd_during_24hr = 0;
   tot_estmtd_precip = 0;
}
//______________________________________________________________________________
Quality_code UCAR_ds512_daily_AB_record::convert_temperature_quality(char A_flag, char B_flag) const
{
   Quality_code temperature_quality = measured_quality;
   switch (A_flag)
   {  case '0' :  temperature_quality = measured_quality;            break;   // VALID
      case '1' :  temperature_quality = out_of_range_error_quality;  break;   // invalid extreme temperature report.
      case '2' :  temperature_quality = estimated_quality;           break;
      case '3' :  temperature_quality = estimated_quality;           break;
      case '9' :  temperature_quality = missing_quality;             break;
      default  :  temperature_quality = measured_quality;            break; /*space indicated valid*/
   }
//   if ((A_flag== '1') ||(A_flag == '2') || (A_flag == '3'))
   {
      switch (B_flag)
      {  case '0' : /* Nothing missing */ break;
         case '9' : temperature_quality = missing_quality; break;
         default :  /* Number of missing air temperatures (Not used for UED conversion) */   break;
      }
   }
   if ((A_flag == ' ') && (B_flag == '0') ) temperature_quality = measured_quality;
   return temperature_quality;
}
//______________________________________________________________________________
Quality_code UCAR_ds512_daily_AB_record::convert_precipitation_quality(char A_flag, char B_flag, char trace_flag) const
{
   Quality_code precip_quality = measured_quality;
   switch (A_flag)
   {  case '0' :  precip_quality = measured_quality;            break; // no precipitation event in previous 24 hours.
      case '1' :  precip_quality = measured_quality;            break; // precipitation event occurred in previous 24 hours.
      case '9' :  precip_quality = missing_quality;            break;  // precipitation missing.
      default  :  precip_quality = measured_quality;            break; /*space indicated valid but 0 percipitation */
   }
   if ((A_flag == ' ') && (B_flag > '0'))
      precip_quality = missing_quality;
   /* B flag has no conversion for UED
   switch (B_flag)
   {
      0 - 7 Number of 3 hour periods not convered in previous 24 hours
      8-9 not estimate of amount possible
   }
   */
   switch  (trace_flag)
   {  case 'M' :  precip_quality = missing_quality;      break;
      case 'T' :  precip_quality = trace_quality;        break;
   }
   return precip_quality;
}
//______________________________________________________________________________
UCAR_ds512_daily_AB_record::UCAR_ds512_daily_AB_record(UCAR_ds512_daily_AB_raw_format &raw,bool pre_sept_1982)
: max_temperature_units    (UC_celcius)   , max_temperature_quality  (missing_quality)
, min_temperature_units    (UC_celcius)   , min_temperature_quality  (missing_quality)
, precipitation_units      (UC_mm)        , precip_quality           (missing_quality)
{
   clear();
   char buffer[255];

//Few sample lines  (I think)  Note there is a Fortran carridge control character that doesn't show in the fortran format
// The docs say the record is blank filled to 88 characters
// 82 831 64851 9999 10.45345.75 423. 30.2 0 21.0 0  0.0 2TOOOOOOOO 8 0
// 82 9 1 64851 9999 10.45345.75 423. 31.9 0 22.3 0  0.0 2M-O/OOO-O 5 0   0.0   0.0 0

// 060104 WARNING this format import has not been tested yet,
// it is only taken from documentation

   strncpy(buffer,raw.YY,2);  buffer[2] =0;  Year  year  = atoi(buffer);
   strncpy(buffer,raw.MM,2);  buffer[2] =0;  Month month = atoi(buffer);
   strncpy(buffer,raw.DD,2);  buffer[2] =0;  DOM   dom   = atoi(buffer);
   if (year > 20) year += 1900; // Not sure how new data handled Y2K  I suspect this format was appended for the daily New
   date.set_YMD(year,month,dom);

   strncpy(buffer,raw.WMO_STATION_ID      ,5);  buffer[5] = 0; if (strcmp(buffer,"99999")!= 0) WMO_station_ID.assign(buffer);
   strncpy(buffer,raw.AIRWAYS_CALLSIGN    ,4);  buffer[4] = 0; airways_callsign.assign(buffer); airways_callsign.strip();


   // WARNING not sure if decimal point is in the file  the documentation says it is an integer scaled by 100.
   // but the FORTRAN format seams to imply the decimal point

   strncpy(buffer,raw.LATITUDE_CODE       ,6);  buffer[6] = 0; latitude_dec_deg = atof(buffer) / 100.0;
   strncpy(buffer,raw.LONGITUDE_CODE      ,6);  buffer[6] = 0; longitude_dec_deg_360 = atof(buffer)/100.0;

   strncpy(buffer,raw.ELEVATION           ,5);  buffer[5] = 0; elevation_m = atof(buffer);
   strncpy(buffer,raw.MAX_TEMPERATURE     ,5);  buffer[5] = 0; max_temperature = atof(buffer);
   strncpy(buffer,raw.MIN_TEMPERATURE     ,5);  buffer[5] = 0; min_temperature = atof(buffer);
   strncpy(buffer,raw.TOTAL_DAILY_PRECIP  ,5);  buffer[5] = 0; total_daily_precip = atof(buffer);

   if (!pre_sept_1982)
   {  strncpy(buffer,raw.TOT_PRECIP_RPTD_DURING_24HR,6); buffer[6] = 0; tot_precip_rptd_during_24hr = atof(buffer);
      strncpy(buffer,raw.TOT_ESTMTD_PRECIP,6);           buffer[6] = 0; tot_estmtd_precip = atof(buffer);
   }
   max_temperature_quality = convert_temperature_quality(raw.MAX_TEMP_FLAGa,raw.MAX_TEMP_FLAGb);
   min_temperature_quality = convert_temperature_quality(raw.MIN_TEMP_FLAGa,raw.MIN_TEMP_FLAGb);
   precip_quality          = convert_precipitation_quality(raw.FLAG_24_HR_PRECIP3a,raw.FLAG_24_HR_PRECIP3b,raw.PRECIP_TRACE_FLAG);

   // The past present weather table is not converted
   // Number of observations not converted

   // NMBR_6HR_PERIODS_DURING_24HR not converted at this time.
}
//______________________________________________________________________________
UCAR_ds512_daily_AB_record::UCAR_ds512_daily_AB_record(UCAR_ds512_daily_AB_raw_format_expanded &raw,bool pre_sept_1982)
: max_temperature_units(UC_celcius)    , max_temperature_quality  (missing_quality)
, min_temperature_units(UC_celcius)    , min_temperature_quality  (missing_quality)
, precipitation_units(UC_mm)           , precip_quality           (missing_quality)
{
   clear();
   char buffer[255];

//Few sample lines
//  82  9  4 64851       10.45 345.75  423.  32.0  3  21.0  0  14.0 12    OO---TTT  5  3   14.0   14.0  0
//  82  9  5 64851       10.45 345.75  423.  33.3  0  20.6  0   0.0  2  T OO-UOTTT  7  4    0.0    0.0  0

   strncpy(buffer,raw.YY,3);  buffer[3] =0;  Year  year  = atoi(buffer);
   strncpy(buffer,raw.MM,3);  buffer[3] =0;  Month month = atoi(buffer);
   strncpy(buffer,raw.DD,3);  buffer[3] =0;  DOM   dom   = atoi(buffer);
   if (year > 20) year += 1900; // Not sure how new data handled Y2K  I suspect this format was appended for the daily New
   date.set_YMD(year,month,dom);

   strncpy(buffer,raw.WMO_STATION_ID      ,5);  buffer[5] = 0; if (strcmp(buffer,"99999")!= 0) WMO_station_ID.assign(buffer);
   strncpy(buffer,raw.AIRWAYS_CALLSIGN    ,4);  buffer[4] = 0; airways_callsign.assign(buffer); airways_callsign.strip();
   strncpy(buffer,raw.LATITUDE_CODE       ,7);  buffer[7] = 0; latitude_dec_deg = atof(buffer) ;
   strncpy(buffer,raw.LONGITUDE_CODE      ,7);  buffer[7] = 0; longitude_dec_deg_360 = atof(buffer);
   strncpy(buffer,raw.ELEVATION           ,6);  buffer[6] = 0; elevation_m = atof(buffer);
   strncpy(buffer,raw.MAX_TEMPERATURE     ,6);  buffer[6] = 0; max_temperature = atof(buffer);
   strncpy(buffer,raw.MIN_TEMPERATURE     ,6);  buffer[6] = 0; min_temperature = atof(buffer);
   strncpy(buffer,raw.TOTAL_DAILY_PRECIP  ,6);  buffer[6] = 0; total_daily_precip = atof(buffer);
   if (!pre_sept_1982)
   {
      strncpy(buffer,raw.TOT_PRECIP_RPTD_DURING_24HR,7); buffer[7] = 0; tot_precip_rptd_during_24hr = atof(buffer);
      strncpy(buffer,raw.TOT_ESTMTD_PRECIP,7);           buffer[7] = 0; tot_estmtd_precip = atof(buffer);
   }

   max_temperature_quality = convert_temperature_quality(raw.MAX_TEMP_FLAGa,raw.MAX_TEMP_FLAGb);
   min_temperature_quality  = convert_temperature_quality(raw.MIN_TEMP_FLAGa,raw.MIN_TEMP_FLAGb);
   precip_quality  = convert_precipitation_quality(raw.FLAG_24_HR_PRECIP3a,raw.FLAG_24_HR_PRECIP3b,raw.PRECIP_TRACE_FLAG);

   // The past present weather table is not converted
   // Number of observations not converted

   // NMBR_6HR_PERIODS_DURING_24HR not converted at this time.
}
//______________________________________________________________________________
class UCAR_ds512_format_convertor
: public UED_convertor
{
public:
   UCAR_ds512_format_convertor(int argc, char *argv[]);
   virtual uint32 perform_import() ;
   virtual uint32 perform_export() { /* NYI */ }
private:
   void import_daily_record   (UCAR_ds512_daily_record      &record);
   void import_daily_AB_record(UCAR_ds512_daily_AB_record   &record);
   bool is_data_line(const char *buffer_cstr);
};
//______________________________________________________________________________
UCAR_ds512_format_convertor::UCAR_ds512_format_convertor(int argc, char *argv[])
: UED_convertor(argc, argv)
{
}
//______________________________________________________________________________
bool UCAR_ds512_format_convertor::is_data_line(const char *buffer_cstr)
{
   bool result = false;
   if (strlen(buffer_cstr) < 9) result = false; // definatly not a data line
   else
   {
      int digit_count = 0;
      for (int i = 1; i <= 10; i++)
         if (isdigit(buffer_cstr[i])) digit_count ++;

      result = digit_count >= 4;
// This only work for the daily files not the AB files
//       result = true;
//      for (int i = 1; i <= 8; i++)
//         if (!isdigit(buffer_cstr[i])) result = false;
   }
   return result;
}
//______________________________________________________________________________
void UCAR_ds512_format_convertor::import_daily_record(UCAR_ds512_daily_record &record)
{
   bool added_just_now = false;
   Station_database *station_database = provide_station_database(record.BKIDN,added_just_now);
   UED_indexed_database *ued_file = &(station_database->ued_file);

   Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();
   if (weather_data_validator)
   {  // Double check data quality for erroneous data that has been marked valid
      if (UED_is_valid(record.RMAX_quality))
         record.RMAX_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.RMAX_value ,max_temperature_creation.variable_code,record.RMAX_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF
      if (UED_is_valid(record.RMIN_quality))
         record.RMIN_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.RMIN_value ,min_temperature_creation.variable_code,record.RMIN_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF

      if (UED_is_valid(record.precipitation_quality))
         record.precipitation_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.precipitation_mm ,precipitation_creation.variable_code,record.precipitation_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF
      if (UED_is_valid(record.MXRH_quality))
         record.MXRH_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.MXRH_value ,max_relative_humidity_creation.variable_code,record.MXRH_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF
      if (UED_is_valid(record.MNRH_quality))
         record.MNRH_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.MNRH_value ,min_relative_humidity_creation.variable_code,record.MNRH_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF
   }
   UED_time_query set_query(record.date.get_datetime64(),record.date.get_datetime64(),record.date.get_datetime64(),UED_time_query::at);
   bool created;  // to catch the result of set_values
   ued_file->set_value(record.RMAX_value       ,set_query,record.RMAX_units          ,record.RMAX_quality         ,max_temperature_creation       ,created);
   ued_file->set_value(record.RMIN_value       ,set_query,record.RMIN_units          ,record.RMIN_quality         ,min_temperature_creation       ,created);
   ued_file->set_value(record.precipitation_mm ,set_query,record.precipitation_units ,record.precipitation_quality,precipitation_creation         ,created);
   ued_file->set_value(record.MXRH_value       ,set_query,record.MXRH_units          ,record.MXRH_quality         ,max_relative_humidity_creation ,created);
   ued_file->set_value(record.MNRH_value       ,set_query,record.MNRH_units          ,record.MNRH_quality         ,min_relative_humidity_creation ,created);
//   ued_file->set_value(records.xxxxx_value      ,set_query,records.xxxx_units,xxxxx_value.quality,*XXXX_creation,created);
}
//______________________________________________________________________________
void UCAR_ds512_format_convertor::import_daily_AB_record(UCAR_ds512_daily_AB_record   &record)
{
   Ustring station_ID(record.WMO_station_ID);
   if (station_ID == "99999") // doesn't have WMO station ID so using airways_callsign mode.
      station_ID = record.airways_callsign;

   // get UED file for station ID
   bool added_just_now = false;
   Station_database *station_database = provide_station_database(station_ID,added_just_now);
   UED_indexed_database *ued_file = &(station_database->ued_file);
   if (added_just_now)
   {  // Since this is the first record encountered for this station
      // See if we have already put geolocation data in this database (are we appending records)
cout << station_ID.c_str() << endl;  // just for progress
      UED_geolocation_record  *geolocation = ued_file->get_geolocation_record();
      if (!geolocation)
      {  geolocation = new UED_geolocation_record;
         geolocation->set_latitude_dec_deg_32(record.latitude_dec_deg);
         float32 longitude_dec_deg = record.longitude_dec_deg_360 ;
         // longitude here is in ranges 0 to 360 west of greenwich
         // we need to convert to decimal degrees 0 to 180 where east is positive and west is negative
         if (longitude_dec_deg > 180.0)
            longitude_dec_deg = (360.0 - record.longitude_dec_deg_360);
         else longitude_dec_deg = -longitude_dec_deg;
         geolocation->set_longitude_dec_deg_32(longitude_dec_deg);
         geolocation->set_elevation(record.elevation_m);
         ued_file ->take_geolocation_record(geolocation);
      }  // else we have already put geolocation data in the UED file.
         // presume it is correct.  We could check if this record's values match.
   }
   UED_time_query set_query(record.date.get_datetime64(),record.date.get_datetime64(),record.date.get_datetime64(),UED_time_query::at);
   bool created;  // to catch the result of set_values

   Weather_validator *weather_data_validator = station_database->provide_weather_data_validator();
   if (weather_data_validator)
   {  // Double check data quality for erroneous data that has been marked valid
      if (UED_is_valid(record.max_temperature_quality))
         record.max_temperature_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.max_temperature ,max_temperature_creation.variable_code,record.max_temperature_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF
      if (UED_is_valid(record.min_temperature_quality))
         record.min_temperature_quality =
            weather_data_validator->validate(record.date.get_DOY(),record.min_temperature ,min_temperature_creation.variable_code,record.min_temperature_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF
   }
   ued_file->set_value(record.max_temperature       ,set_query,record.max_temperature_units          ,record.max_temperature_quality         ,max_temperature_creation       ,created);
   ued_file->set_value(record.min_temperature       ,set_query,record.min_temperature_units          ,record.min_temperature_quality         ,min_temperature_creation       ,created);

   float64 precipitation_mm =  record.total_daily_precip;
   Quality_code   precipitation_quality = record.precip_quality;
   if (precipitation_quality != measured_quality)
   {  // We may have the new  tot_precip_rptd_during_24hr or tot_estmtd_precip fields
      if (record.tot_precip_rptd_during_24hr > 0.0)  {precipitation_mm =  record.tot_precip_rptd_during_24hr; precipitation_quality = measured_quality;}
      // if still not valid measured data then it may be estimated
      if (precipitation_quality != measured_quality)
         if (record.tot_estmtd_precip > 0.0)         {precipitation_mm =  record.tot_estmtd_precip; precipitation_quality = estimated_quality;}
   }

   if (UED_is_valid(precipitation_quality))
         precipitation_quality =
            weather_data_validator->validate(record.date.get_DOY(),precipitation_mm ,precipitation_creation.variable_code,record.precipitation_units ,UT_day
            ,CORN::measured_quality,CORN::measured_quality); // <- NYI I should allow the user to specify the data quality in the TDF

   ued_file->set_value(precipitation_mm ,set_query,record.precipitation_units ,precipitation_quality,precipitation_creation         ,created);
}
//______________________________________________________________________________
uint32 UCAR_ds512_format_convertor::perform_import()
{  uint32 record_count = 0;
   ifstream input_file(parameters.target_filename.c_str());

   cout << "Reading input file(s):" <<  parameters.target_filename << endl;
   long buffer_read = 0;
   CORN::Ustring buffer_str;

   bool isa_data_line = false;
   do
   {  // Read any header line
      140516 replace read_to_delim with getline(input_file,buffer_str)

      buffer_str.read_to_delim(input_file);
      buffer_str.strip(); // The files are often space padded, removing these spaces will make it easier to identify the specific format
      isa_data_line = is_data_line(buffer_str.c_str());
   } while (!isa_data_line && !input_file.eof());

   int16 buffer_length = buffer_str.length();

   if (!input_file.eof())
   {
      DS512_format format = UNKNOWN_DS512;
      // Note these lengths are after trailing blanks (which there may be) have been stripped!
      if (buffer_length == 69)         format = DS512_AB_PRE_SEPT_1982;  // Warning not yet tested (don't have sample file)
      if (buffer_length == 83)         format = DS512_AB_POST_SEPT_1982; // Warning not yet tested (don't have sample file)

      if (buffer_length == 86)         format = DS512_AB_PRE_SEPT_1982_EXPANDED;
      if (buffer_length == 103)        format = DS512_AB_POST_SEPT_1982_EXPANDED;


//NYI      if (buffer_length == ???)        format = DS512_PRE_1994;
//NYI      if (buffer_length == ???)        format = DS512_POST_1994;
      if (buffer_length == 144)        format = DS512_PRE_1994_EXPANDED;
      if (buffer_length == 230)        format = DS512_POST_1994_EXPANDED;
//      else // must be post1994
//         if (buffer_str.c_str()[9] == ' ')   format = ;
//         else                                format = DS512_POST_1994;
// NYI

//NYI    UCAR_ds512_daily_post_1994_raw_format          post_1994_raw         ;
      UCAR_ds512_daily_raw_format_expanded            ds512_daily_raw_expanded;

      UCAR_ds512_daily_AB_raw_format                  ds512_daily_AB_raw;
      UCAR_ds512_daily_AB_raw_format_expanded         ds512_daily_AB_raw_expanded;
      int buffer_str_len = buffer_str.length();
      do
      {
         switch (format)
         {
            case DS512_PRE_1994 :
            {  cerr << "This file appears to a UCAR ds512.0 format used before 1994, this format is not implemented (though to be obsolete).  Contact Roger Nelson rnelson@wsu.edu if you need this format. - aborted" << endl;
               return 0;
            } break;
            case DS512_POST_1994 :
            {  cerr << "This file appears to a UCAR ds512.0 used after 1994 unexpanded. This format is not implemented (though to be obsolete).  Contact Roger Nelson rnelson@wsu.edu if you need this format. - aborted" << endl;
               return 0;
            } break;
            case DS512_POST_1994_EXPANDED :
            case DS512_PRE_1994_EXPANDED :
            {
               memset((void *)&ds512_daily_raw_expanded,' ',sizeof(ds512_daily_raw_expanded));
               memcpy((char *)&ds512_daily_raw_expanded,buffer_str.c_str() ,buffer_length /*060104 CORN_min(buffer_str_len,sizeof(ds512_daily_post_1994_raw_expanded))*/);
               UCAR_ds512_daily_record record(ds512_daily_raw_expanded,  format == DS512_PRE_1994_EXPANDED);
               if (  (parameters.station_IDs_filter.length() == 0)
                   ||(parameters.station_IDs_filter.contains(record.BKIDN.c_str()))
                   ||(parameters.station_IDs_filter == "all")
                   ||(parameters.station_IDs_filter == "")
                   )
                  import_daily_record(record);
               record_count++;
            } break;

            case DS512_AB_PRE_SEPT_1982 :
            case DS512_AB_POST_SEPT_1982:
            {
               memset((void *)&ds512_daily_AB_raw,' ',sizeof(ds512_daily_AB_raw));
               memcpy((void *)&ds512_daily_AB_raw,buffer_str.c_str(),buffer_length);
               UCAR_ds512_daily_AB_record record(ds512_daily_AB_raw,format==DS512_AB_PRE_SEPT_1982);
               if (  (parameters.station_IDs_filter.length() == 0)
                   ||(parameters.station_IDs_filter.contains(record.WMO_station_ID.c_str()))
                   ||(parameters.station_IDs_filter.contains(record.airways_callsign.c_str()))
//                   ||(record.WMO_station_ID == parameters.station_ID_filter)
//                   ||(record.airways_callsign == parameters.station_ID_filter)
                   ||(parameters.station_IDs_filter == "all")
                   ||(parameters.station_IDs_filter == "")
                   )
                  import_daily_AB_record(record);
               record_count++;
            } break;

            case DS512_AB_PRE_SEPT_1982_EXPANDED  :
            case DS512_AB_POST_SEPT_1982_EXPANDED :
            {
               memset((void *)&ds512_daily_AB_raw_expanded,' ',sizeof(UCAR_ds512_daily_AB_raw_format_expanded));
               memcpy((void *)&ds512_daily_AB_raw_expanded,buffer_str.c_str(),buffer_length);
               UCAR_ds512_daily_AB_record record_expanded(ds512_daily_AB_raw_expanded,format==DS512_AB_PRE_SEPT_1982_EXPANDED);
               if (  (parameters.station_IDs_filter.length() == 0)
                   ||(parameters.station_IDs_filter.contains(record_expanded.WMO_station_ID.c_str()))
                   ||(parameters.station_IDs_filter.contains(record_expanded.airways_callsign.c_str()))
//                   ||(record.WMO_station_ID == parameters.station_ID_filter)
//                   ||(record.airways_callsign == parameters.station_ID_filter)
                   ||(parameters.station_IDs_filter == "all")
                   ||(parameters.station_IDs_filter == "")
                   )
                  import_daily_AB_record(record_expanded);
               record_count++;
            } break;

            case  UNKNOWN_DS512 : default :
            {  cerr << "Unrecognized DS512.0 format - aborted" << endl;
               return 0;
            } break;
         }
      140516 replace read_to_delim with getline(input_file,buffer_str)

         buffer_str.read_to_delim(input_file);
         isa_data_line = is_data_line(buffer_str.c_str());
         if (isa_data_line);
//         memcpy((char *)&data_buffer,buffer_str.c_str(),buffer_size);
      } while (isa_data_line && !input_file.eof());
   }
   cout << "Writing UED files:" << endl;
   return record_count;
}
//______________________________________________________________________________
int main(int argc, char *argv[])
{
// test command lines
//   C:\dev\UED\convert\test\convert_UCAR_ds512.0.dlynew.rsp

   UCAR_ds512_format_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
}
//______________________________________________________________________________

