//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Excel_workbook_with_TDF.res");
USEFORM("Excel_workbook_form.cpp", Form1);
USEUNIT("..\convertor.cpp");
USEUNIT("..\convert_response.cpp");
USEUNIT("..\text_dBase_Excel_with_TDF\tabular_file_with_TDF_convertor.cpp");
USELIB("..\..\..\corn\BCB5\corn_static.lib");
USELIB("..\..\..\corn\container\BCB5\container_static.lib");
USELIB("..\..\..\corn\parameters\BCB5\parameters_static.lib");
USELIB("..\..\..\corn\format\BCB5\format_static.lib");
USELIB("..\..\..\corn\file_sys\BCB5\file_sys_static.lib");
USELIB("..\..\library\BCB5\ued_static.lib");
USEUNIT("..\..\..\common\weather\stations\UCAR_stations.cpp");
USEUNIT("..\..\..\common\weather\stations\AgriMet_stations.cpp");
USEUNIT("..\..\..\common\weather\stations\all_stations.cpp");
USEUNIT("..\..\..\common\weather\stations\CC_station_datarec.cpp");
USEUNIT("..\..\..\common\weather\stations\ncdc_stations.cpp");
USEUNIT("..\..\..\common\weather\stations\PAWS_stations.cpp");
USELIB("..\..\..\corn\datetime\BCB5\datetime_static.lib");
USEUNIT("..\..\..\common\geolocation\geolocation.cpp");
USEUNIT("..\..\..\common\geolocation\USA_state_FIPS_code.cpp");
USEUNIT("..\ED_tabular_format.cpp");
USEUNIT("..\..\..\corn\tabular\delineated_datarec.cpp");
USEUNIT("..\..\..\corn\tabular\tabular.cpp");
USEUNIT("..\text_dBase_Excel_with_TDF\import.cpp");
USEUNIT("..\..\..\corn\tabular\tabular_format.cpp");
USEUNIT("..\..\..\common\weather\validator.cpp");
USEUNIT("..\..\..\corn\format\html\form_IO\content.cpp");
USEUNIT("..\..\..\common\weather\solar_rad.cpp");
USEUNIT("..\station_database.cpp");
USEUNIT("..\..\..\common\weather\sun.cpp");
USEUNIT("..\..\..\Climgen\source\options.cpp");
USEUNIT("..\..\..\common\weather\database\common_weather_creators.cpp");
USEUNIT("..\..\..\common\simulation\paths.cpp");
USEUNIT("..\..\..\CropSyst\cpp\database_dir.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->CreateForm(__classid(TForm1), &Form1);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
