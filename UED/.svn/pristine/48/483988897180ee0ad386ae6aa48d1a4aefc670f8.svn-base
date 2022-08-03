#include <UED/spatial/interpolation/ued_database_interpolator.h>
#include <common/geolocation/geolocation.h>
#include <UED/std_codes.h>


void main()
{

   Geolocation       test_geoloc;
   test_geoloc.station_ID_code.assign("estana");
   test_geoloc.station_name.assign("Estaña");
   test_geoloc.latitude_dec_deg_32    = 42.03361130;
   test_geoloc.longitude_dec_deg_32   = 0.54192960;
   test_geoloc.country_name           = "Spain";


   { // First include the 30 minute data from barbarastro
      Association_list  test_UED_files_to_inteprolated;
      test_UED_files_to_inteprolated.append(new File_name("d:\\Projects\\Manuel\\Weather\\9756.ued"));
      test_UED_files_to_inteprolated.append(new File_name("d:\\Projects\\Manuel\\Weather\\9759E.ued"));

      Association_list  test_UED_files_not_interpolated; // returned
      UED_variable_code variables_to_include[] =
      {UED_STD_VC_max_temperature.get()
      ,UED_STD_VC_min_temperature.get()
      ,UED_STD_VC_precipitation.get()
      ,0
      };
      UED_database_interpolator UED_db_iterpol_test("d:\\Projects\\Manuel\\Weather\\estana.ued",test_geoloc,variables_to_include,test_UED_files_to_inteprolated,test_UED_files_not_interpolated);
      UED_db_iterpol_test.interpolate_all();
   };
   // Currently this does not do anthing, it only tries to programming errors
   { // First include the 30 minute data from barbarastro (only solar radiation, windspeed and relative humidity
      Association_list  test_UED_files_to_inteprolated;
      test_UED_files_to_inteprolated.append(new File_name("d:\\Projects\\Manuel\\Weather\\barbastro.ued"));

      Association_list  test_UED_files_not_interpolated; // returned
      UED_variable_code variables_to_include[] =
      {UED_STD_VC_solar_radiation.get()
      ,UED_STD_VC_max_relative_humidity.get()
      ,UED_STD_VC_min_relative_humidity.get()
      ,UED_STD_VC_wind_speed.get()
      ,0
      };
      UED_database_interpolator UED_db_iterpol_test("d:\\Projects\\Manuel\\Weather\\estana.ued",test_geoloc,variables_to_include,test_UED_files_to_inteprolated,test_UED_files_not_interpolated);
      UED_db_iterpol_test.interpolate_all();
   };

};
