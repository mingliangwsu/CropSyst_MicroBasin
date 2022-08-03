/* General weather object
*/
#include <rlib/bsysemod/wthrsprd.h>
#include <rlib/measures.h>
#include <rlib/rlib.h> // for round()
#include <stdio.h>
#include <fstream.h>
//______________________________________________________________________________
char *recommended_label[] =
{""
,"DATE"
,"PRECIPITATION"
,"MAXTEMPERATURE"
,"MINTEMPERATURE"
,"SOLARRADIATION"
,"VAPORPRESDEF"
,"MAXRELHUMID"
,"MINRELHUMID"
,"WINDSPEED"
,"ACTEVAPORATION"
,"PANEVAPORATION"
};
//______________________________________________________________________________
char *recommended_units[] =
{
    "-"
   ,"m"          // Precip
   ,"mm"         // precip
   ,"cm"         // precip
   ,"inch"       // precip
   ,"C"          // temperature
   ,"Kelvin"     // temperature
   ,"F"          // temperature
   ,"m/s"        // windspeed
   ,"m/day"      // windspeed
   ,"mile/day"   // windspeed
   ,"MJ/m2/day"  // Solar rad
   ,"J/m2/day"   // Solar rad
   ,"Langley/day"// Solar rad
   ,"percent"    // Humidity
   ,"kPa"        // VPD
   ,"y/d", "y/m/d", "y/d/m", "m/d/y", "d/m/y"   // <- Date format/units (starting with y_d) must always be last!
};
//______________________________________________________________________________
/* Moved to wthrvirt
void weather_spreadsheet::allocate_memory()
{
  for (int col = 0; col < columns; col++)
    switch (column_label[col])
    {
       case PREC    : precip = (double_float *)malloc(sizeof(double_float)*367);  break;
       case TMAX :     max_temp = (double_float *)malloc(sizeof(double_float)*367); break;
       case TMIN :     min_temp = (double_float *)malloc(sizeof(double_float)*367); break;
       case SRAD :     solar_rad = (double_float *)malloc(sizeof(double_float)*367); break;
       case RHMAX :    max_rel_humid = (double_float *)malloc(sizeof(double_float) *367); break;
       case RHMIN      min_rel_humid = (double_float *)malloc(sizeof(double_float) *367); break;
       case WINDSPEED :windspeed = (double_float *)malloc(sizeof(double_float)*367); break;
       case VPD :      VPD_rad = (double_float *)malloc(sizeof(double_float)*367); break;
       case ACTEVAP :  act_evap = (double_float *)malloc(sizeof(double_float)*367); break;
       case PANEVAP :  pan_evap = (double_float *)malloc(sizeof(double_float)*367); break;
    };

    for (int i = 0; i<367;i++)
    { if (has_precip)        precip[i] = 0;
      if (has_min_temp)      min_temp[i] = 0;
      if (has_max_temp)      max_temp[i] = 0;
      if (has_solar_rad)     solar_rad[i] = 0;
      if (has_max_rel_humid) max_rel_humid[i] = 0;
      if (has_min_rel_humid) min_rel_humid[i] = 0;
      if (has_windspeed)     windspeed[i] = 0;
      if (has_VPD)           VPD[i] = 0;
      if (has_act_evap)      act_evap[i] = 0;
      if (has_pan_evap)      pan_evap[i] = 0;
  };
};
*/

//void weather_spreadsheet::create()
//{
//  allocate_memory();
///};

//______________________________________________________________________________
double weather_output_spreadsheet::convert_m_to(double value,units from_units)
{  double return_value = value;
   switch (from_units)
   {  case inch : return_value = m_inch(value);  break; //Convert inches TO meters
      case mm   : return_value = m_to_mm(value); break;
      case cm   : return_value = m_to_cm(value); break;
   };
   return return_value;
};
//______________________________________________________________________________
double weather_output_spreadsheet::convert_MJ_m2_day_to(double value, units from_units)
{  double return_value = value;
   switch (from_units)
   { case Langley_day : return_value = value / 0.041876; break;//Convert Langleys/day TO MJ/m2/day
     case J_m2_day    : return_value = value * 1000.0;   break;
   };
   return return_value;
};
//______________________________________________________________________________
double weather_output_spreadsheet::convert_C_to(double value, units from_units)
{  double return_value = value;
   switch (from_units)
   { case F : return_value = c_f(value); break;
     case Kelvin : return_value = C_to_Kelvin(value); break;
   };
   return return_value;
};
//______________________________________________________________________________
double weather_output_spreadsheet::convert_m_day_to(double value , units from_units)
{  double return_value = value;
   switch (from_units)
   { case m_s : return_value = value / 86400.0; break;
     case mile_day : return_value = value / 1609.0;  break; //Convert miles/day TO m/day
   };
   return return_value;
};
//______________________________________________________________________________
void weather_output_spreadsheet::write()
{  int col;
   units date_units_format;
   for (col = 0; col < columns; col++)
     write_label_cell(gen_format(0,WKS_format_special,WKS_special_text)
       ,col,0
       ,WKS_justify_center
       ,recommended_label[column_label[col]]);
   for (col = 0; col < columns; col++)
   {  if (column_units[col] >= y_d)
        date_units_format = column_units[col];
      write_label_cell(gen_format(0,WKS_format_special,WKS_special_text)
       ,col,0
       ,WKS_justify_center
       ,recommended_units[column_units[col]]);
   };

   // first write column headers

   int DOY;

   for (DOY = 1; DOY <= days_in_year();  DOY++)
   {
      int row = DOY + 1; // First data line appears in spreadsheet row 2 (numbered from 0)
      int date_format;
      switch (date_units_format)
      {
         case y_d :   date_format = D_YD;  break;
         case y_m_d : date_format = D_YMD; break;
         case y_d_m : date_format = D_YDM; break;
         case m_d_y : date_format = D_MDY; break;
         case d_m_y : date_format = D_DMY; break;
      };
      RDate date_value(get_year(),DOY,date_format,D_YYYY|D_M|D_lead_none,'/');
      string date_str;
      date_str = text_string(date_str);

      for (col = 0; col < columns; col++)
      {  float float_value = 0.0;
         // output the column data here convert to the desired units as we go
         if (column_label[col] == DATE)
            write_label_cell(gen_format(0,WKS_format_special,WKS_special_text)
                     ,col,row,WKS_justify_left,date_str.c_str());
         else
         {
            switch (column_label[col])
            {
               case PREC :     float_value = convert_m_to(precip[DOY],column_units[col]);            break;
               case ACTEVAP :  float_value = convert_m_to(act_evap[DOY],column_units[col]);          break;
               case PANEVAP :  float_value = convert_m_to(pan_evap[DOY],column_units[col]);          break;
               case TMAX :     float_value = convert_C_to(max_temp[DOY],column_units[col]);          break;
               case TMIN :     float_value = convert_C_to(min_temp[DOY],column_units[col]);          break;
               case SRAD :     float_value = convert_MJ_m2_day_to(solar_rad[DOY],column_units[col]); break;
               case VPD :      float_value = convert_C_to(vpd[DOY],column_units[col]);               break;
               case RHMAX :    float_value = max_rel_humid[DOY],column_units[col];                   break;
               case RHMIN :    float_value = min_rel_humid[DOY],column_units[col];                   break;
               case WINDSPEED :float_value = convert_m_day_to(windspeed[DOY],column_units[col]);       break;
            };
            // precision = 3
            write_number_cell(gen_format(0,WKS_format_fixed,3),col,row,float_value);
         };
      };
   };
};
//______________________________________________________________________________

/*
    weather_spreadsheet << DOY << ' ';
    weather_spreadsheet.precision(2);
    weather_spreadsheet.setf(ios::fixed,ios::scientific);
    weather_spreadsheet << m_to_mm(precip[DOY]) << ' ';
    weather_spreadsheet.precision(2);
    weather_spreadsheet << max_temp[DOY] << ' ';
    weather_spreadsheet.precision(2);
    weather_spreadsheet << min_temp[DOY];

    switch (file_format)
    { case day_precip_temp_rad :
        weather_spreadsheet.precision(2);
        weather_spreadsheet << ' ' << solar_rad[DOY];
      break;
      case day_precip_temp_rad_humid_wind :
         weather_spreadsheet.precision(2);
         weather_spreadsheet << ' ' << solar_rad[DOY] << ' ' << max_rel_humid[DOY] << ' ' << min_rel_humid[DOY] << ' ' << windspeed[DOY];
      break;
    };
    weather_spreadsheet << endl;
  };
  weather_spreadsheet.close();
*/
//______________________________________________________________________________
void weather_input_spreadsheet::preread()//(WKS_input_file &i_file)
{
//  reset();
  while (!eof() && (read_record() != WKS_CODE_EOF))
  {
   switch (row)
   { case 0 :  break;  // This row will eventually contain the year
     case 1 :
        strlwr(str_value);
        // For english french italian
        if (strstr(str_value,"dat"))     column_label[col] = DATE;
        // for spanish
        if (strstr(str_value,"fecha"))   column_label[col] = DATE;
        if (strstr(str_value,"temp"))
        {  // For english or french
           if (strstr(str_value,"max"))  column_label[col] = TMAX;
           // For spanish or italian
           if (strstr(str_value,"max"))  column_label[col] = TMAX;
           if (strstr(str_value,"min"))  column_label[col] = TMIN;
        };
        if (strstr(str_value,"prec"))    column_label[col] = PREC;
        if (strstr(str_value,"sol"))
           if (strstr(str_value,"rad"))  column_label[col] = SRAD;
        if (strstr(str_value,"hum"))
        {
           if (strstr(str_value,"max"))  column_label[col] = RHMAX;
           if (strstr(str_value,"mas"))  column_label[col] = RHMAX;
           if (strstr(str_value,"min"))  column_label[col] = RHMIN;
        };
        if (strstr(str_value,"wind"))    column_label[col] = WINDSPEED;
        // for italian french spanish
        if (strstr(str_value,"vent"))    column_label[col] = WINDSPEED;
        if (strstr(str_value,"evap"))
        {
        if (strstr(str_value,"act"))     column_label[col] = ACTEVAP;
        if (strstr(str_value,"pan"))     column_label[col] = PANEVAP;
        }
      break;
      case 2 :
         if (strcmp(str_value,"m"))          column_units[col] = m;
         if (strcmp(str_value,"mm"))         column_units[col] = mm;
         if (strcmp(str_value,"cm"))         column_units[col] = cm;
         if (strstr(str_value,"in"))         column_units[col] = inch;
         if (strcmp(str_value,"C"))          column_units[col] = C;
         if (strcmp(str_value,"F"))          column_units[col] = F;
         if (strcmp(str_value,"Kelvin"))     column_units[col] = Kelvin;
         if (strcmp(str_value,"m/s"))        column_units[col] = m_s;
         if (strcmp(str_value,"m/d"))        column_units[col] = m_day;
         if (strcmp(str_value,"mile/day"))   column_units[col] = mile_day;
         if (strcmp(str_value,"MJ/m2/day"))  column_units[col] = MJ_m2_day;
         if (strcmp(str_value,"J/m2/day"))   column_units[col] = J_m2_day;
         if (strcmp(str_value,"Langley/day"))column_units[col] = Langley_day;
         if (strcmp(str_value,"%"))          column_units[col] = percent;
         if (strcmp(str_value,"kPa"))        column_units[col] = kPa;
      break;
      // The remaining rows are data
   };
  };
};
//______________________________________________________________________________
double weather_input_spreadsheet::convert_to_m(double value,units from_units)
{ double return_value = value;
  switch (from_units)
  { case inch : return_value = inch_m(value);  break; /*Convert inches TO meters*/
    case mm   : return_value = mm_to_m(value); break;
    case cm   : return_value = cm_to_m(value); break;
  };
  return return_value;
};
//______________________________________________________________________________
double weather_input_spreadsheet::convert_to_MJ_m2_day(double value, units from_units)
{ double return_value = value;
  switch (from_units)
  { case Langley_day : return_value = value * 0.041876; break;        /*Convert Langleys/day TO MJ/m2/day*/
    case J_m2_day    : return_value = value / 1000.0;   break;
  };
  return return_value;
};
//______________________________________________________________________________
double weather_input_spreadsheet::convert_to_C(double value, units from_units)
{ double return_value = value;
  switch (from_units)
  { case F : return_value = f_c(value); break;
    case Kelvin : return_value = Kelvin_to_C(value); break;
  };
  return return_value;
};
//______________________________________________________________________________
double weather_input_spreadsheet::convert_to_m_day(double value , units from_units)
{ double return_value = value;
  switch (from_units)
  { case m_s : return_value = value * 86400.0; break;
    case mile_day : return_value = value * 1609.0;  break;       /*Convert miles/day TO m/day*/
  };
  return return_value;
};
//______________________________________________________________________________
void weather_input_spreadsheet::read()
{  preread();
   allocate_memory();  // must be called after identifying the format
   reset(); // need to reset after prescan
   while (!eof() && (read_record() != WKS_CODE_EOF))
   {
      // For multiple years, this must be fixed!!
      if ((row >= FIRST_DATA_ROW) && (col < columns))
      {  int DOY = row = FIRST_DATA_ROW + 1;
         double value = 0.0;
         if (data_type == TYPE_INTEGER) value = int_value;
         if (data_type == TYPE_FLOAT)   value = double_value;

         switch (column_label[col])
         {
         case PREC     : precip[DOY]        = convert_to_m(value,column_units[col]); break;
         case TMAX     : max_temp[DOY]      = convert_to_C(value,column_units[col]); break;
         case TMIN     : min_temp[DOY]      = convert_to_C(value,column_units[col]); break;
         case SRAD     : solar_rad[DOY]     = convert_to_MJ_m2_day(value,column_units[col]); break;
         case RHMAX    : max_rel_humid[DOY] = column_units[col]; //always percent
         case RHMIN    : min_rel_humid[DOY] = column_units[col]; //always percent
         case WINDSPEED: windspeed[DOY]     = convert_to_m_day(value,column_units[col]); break;
         case VPD      : vpd[DOY]           = column_units[col]; // always kPa
         case ACTEVAP  : act_evap[DOY]      = convert_to_m(value,column_units[col]); break;
         case PANEVAP  : pan_evap[DOY]      = convert_to_m(value,column_units[col]); break;
         };
      };
   };
   double_float sum_annual_temp = 0;
   int DOY;
   for (DOY = 1; DOY <= days_in_year(); DOY++)
      sum_annual_temp += (max_temp[DOY] + min_temp[DOY])/2.0;
   avg_annual_temperature = sum_annual_temp / days_in_year();
};
//______________________________________________________________________________


