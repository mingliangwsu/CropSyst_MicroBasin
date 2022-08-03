/*
This program dumps standard variable codes and units
to a C/C++ header file and a Visual Basic module
for use with UED dlls


*/

#include <UED/library/std_codes.h>
#include <corn/datetime/date.h>
#include <stdlib.h>
   // for ltoa
using namespace UED;
using namespace std;
ofstream ued_codes_h;
ofstream ued_codes_bas;


void dump_VC(const Variable_format_0 &UED_STD_VD)
{

   char code_hex[10];
   ltoa(UED_STD_VD.code.get(),code_hex,16);


   ued_codes_h << "#define UED_STD_VC_" << UED_STD_VD.abbreviation << " 0x" << code_hex << "\t/* " << UED_STD_VD.description << "*/" << endl;

   ued_codes_bas << "Public Const VC_" << UED_STD_VD.abbreviation << " As Long = " << UED_STD_VD.code.get() <<  " ' " << UED_STD_VD.description <<  endl;
};

void dump_UC(const char *units_name, unsigned long units_code)
{

   char code_hex[10];
   ltoa(units_code,code_hex,16);

// For C++ use the UED_units.h file
//   ued_codes_h << "#define UED_STD_UC_" << units_name << " 0x" <<code_hex << endl;

   ued_codes_bas << "Public Const " << units_name << " As Long = " << units_code << endl;
};

void main()
{
    ued_codes_h.open("UED_codes.h");
    ued_codes_bas.open("UED_codes.bas");

   CORN::Date today; char today_cstr[80]; today.text_str(today_cstr);

   ued_codes_h << "#ifndef UED_CODES_H" << endl;
   ued_codes_h << "#define UED_CODES_H" << endl;
   ued_codes_h << "/* As of " <<  today_cstr << "*/" << endl;

   ued_codes_bas << "Option Explicit" << endl;
   ued_codes_bas << "Attribute VB_name = \"UED_STD\"" <<endl;
   ued_codes_bas << "! As of " <<  today_cstr << endl;


   // dump variable codes

   dump_VC(UED::STD_VD_date                               );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_precipitation                      );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_max_temperature                    );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_min_temperature                    );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_avg_temperature                    );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_obs_temperature                    );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_max_dew_point_temperature          );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_min_dew_point_temperature          );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_avg_dew_point_temperature          );//,ued_codes_h,ued_codes_bas);

   dump_VC(UED::STD_VD_max_relative_humidity              );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_min_relative_humidity              );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_avg_relative_humidity              );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_solar_radiation                    );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_isothermal_longwave_net_radiation  );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_net_radiation                      );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_wind_speed                         );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_wind_direction                     );//,ued_codes_h,ued_codes_bas);


   dump_VC(UED::STD_VD_pot_evapotranspiration             );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_act_evapotranspiration             );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_pan_evaporation                    );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_ref_ET_Penman_Monteith             );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_ref_ET_Priestly_Taylor             );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_ref_ET_Hargreaves                  );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_avg_daytime_vapor_pressure_deficit );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_avg_fullday_vapor_pressure_deficit );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_max_vapor_pressure_deficit         );//,ued_codes_h,ued_codes_bas);

   dump_VC(UED::STD_VD_cloud_cover                        );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_snow_fall                          );//,ued_codes_h,ued_codes_bas);
   dump_VC(UED::STD_VD_snow_depth                         );//,ued_codes_h,ued_codes_bas);

// now need to dump units codes


   ued_codes_h  << endl;
   ued_codes_bas << endl;
/*
   dump_UC("date"                           ,UED_time_unit_date);
   dump_UC("celcius"                            ,UED_units_celcius);
   dump_UC("percent"                                  ,UED_percent);
   dump_UC("MJ_per_m2_solar_radiation"              ,UED_units_MJ_m2_solar_radiation);
   dump_UC("meters_per_second"                  ,UED_units_meters_per_second);
   dump_UC("mm_depth"                           ,UED_units_mm_depth);
   dump_UC("kilo_pascal_atmospheric_pressure"   ,UED_units_kilo_pascal_atmospheric_pressure);
*/
   dump_UC("UT_date"                               ,UT_date);
   dump_UC("UC_celcius"                            ,UC_celcius);
   dump_UC("UC_percent"                            ,UC_percent);
   dump_UC("UC_MJ_m2_solar_radiation"              ,UC_MJ_per_m2_solar_radiation);
   dump_UC("UC_meters_per_second"                  ,UC_meters_per_second);
   dump_UC("UC_mm_depth"                           ,UC_mm);   // mm_depth is obsolete
   dump_UC("UC_mm"                                 ,UC_mm);
   dump_UC("UC_kP_atmospheric_pressure"            ,UC_kPa); // obsolete
   dump_UC("UC_kPa"                                ,UC_kPa);

   ued_codes_h << "#endif" << endl << endl;
   ued_codes_bas << endl;
};

