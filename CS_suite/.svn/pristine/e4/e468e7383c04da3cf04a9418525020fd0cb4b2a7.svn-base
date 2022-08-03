#ifndef UED_directoryH
#define UED_directoryH
//---------------------------------------------------------------------------
#  include "corn/application/application_directory_OS_FS.h"
//---------------------------------------------------------------------------
namespace UED
{
//______________________________________________________________________________
class Application_directory
: public CORN::OS_FS::Application_directory
{
protected:
   provided_ CORN::OS::Directory_name_concrete *convert_dir;
   provided_ CORN::OS::Directory_name_concrete *convert_formats_dir;
   provided_ CORN::OS::Directory_name_concrete *quality_dir;                      //140629
   provided_ CORN::OS::File_name_concrete *import_wizard_exe;
   provided_ CORN::OS::File_name_concrete *export_wizard_exe;
   provided_ CORN::OS::File_name_concrete *spatial_interpolator_exe;
   provided_ CORN::OS::File_name_concrete *convert_export_exe;
   provided_ CORN::OS::File_name_concrete *convert_tabular_format_editor_exe;
   provided_ CORN::OS::File_name_concrete *map_google_exe;
   provided_ CORN::OS::File_name_concrete *condense_exe;
#ifdef __unix
   provided_ CORN::OS::File_name_concrete *convert_LADSS_exe;
#endif

   // The following are convertor with import and export
   provided_ CORN::OS::File_name_concrete *convert_Excel_workbook_with_TDF_exe;
   provided_ CORN::OS::File_name_concrete *convert_text_dBase_Excel_with_TDF_exe;
   provided_ CORN::OS::File_name_concrete *convert_CropSyst_exe;
   // The following are convertors with export only
   provided_ CORN::OS::File_name_concrete *convert_RZWQM_exe;
   provided_ CORN::OS::File_name_concrete *convert_Canadian_Climatological_exe;
   provided_ CORN::OS::File_name_concrete *convert_DYRESM_exe;
   provided_ CORN::OS::File_name_concrete *convert_NOAA_met_exe;
   provided_ CORN::OS::File_name_concrete *convert_LARS_WG_exe;
   provided_ CORN::OS::File_name_concrete *convert_SWAT_exe;
   provided_ CORN::OS::File_name_concrete *quality_import_export_exe;             //140629

#ifdef NYN
   File_name      UED_convert_cropsyst_exe;
   File_name      UED_convert_LADSS_exe;
   File_name      UED_convert_layout_exe;
   File_name      UED_convert_export_exe;
   File_name      UED_convert_noaa_met_exe;
   File_name      UED_convert_VIC_exe;

   File_name      UED_convert_NCDC_daily_surface_data_exe;
   File_name      UED_convert_NCDC_summary_of_the_day_exe;
   File_name      UED_convert_INM_CHE_exe;
   File_name      UED_convert_EarthInfo_daily_binary_exe;
   File_name      UED_convert_UCAR_DS512_daily_exe;
   File_name      UED_convert_WPRO_exe;
   File_name      UED_convert_APSIM_exe;
   File_name      UED_convert_NCDC_NOAA_daily_global_surface_data_exe;
   File_name      UED_convert_IBSNAT_ICASA_DSSAT_exe;
   File_name      UED_convert_IRIMO_exe;
   File_name      UED_convert_with_TDF_exe;
#endif
   provided_ CORN::OS::File_name_concrete *UED_compare_exe;
public: // 'structors
   Application_directory(const wchar_t *directory_name = L"UED");
   Application_directory(const CORN::OS_FS::Suite_directory &suite_dir, const wchar_t *directory_name = L"UED");
   // We override set_path to ensure that the local files are qualified with the new path
   virtual ~Application_directory();
   virtual void reset()                                               provision_;
public:
   const CORN::OS::Directory_name &convert()                          provision_;
   const CORN::OS::Directory_name &quality()                          provision_;//140629
   const CORN::OS::Directory_name &convert_formats()                  provision_;
   const CORN::OS::File_name &import_wizard_executable()              provision_;
   const CORN::OS::File_name &export_wizard_executable()              provision_;
   const CORN::OS::File_name &spatial_interpolator_executable()       provision_;
   const CORN::OS::File_name &map_google_executable()                 provision_;
   const CORN::OS::File_name &condense_executable()                   provision_;
   const CORN::OS::File_name &convert_export_executable()             provision_;
   const CORN::OS::File_name &convert_LADSS_executable()              provision_;

   // The following are convertor with import and export
   const CORN::OS::File_name &convert_Excel_workbook_with_TDF_executable()  provision_;
   const CORN::OS::File_name &convert_text_dBase_Excel_with_TDF_executable()provision_;
   const CORN::OS::File_name &convert_tabular_format_editor_executable()    provision_;
   const CORN::OS::File_name &convert_CropSyst_executable()                 provision_;
   // The following are convertors with export only
   const CORN::OS::File_name &convert_RZWQM_executable()                    provision_;
   const CORN::OS::File_name &convert_Canadian_Climatological_executable()  provision_;
   const CORN::OS::File_name &convert_DYRESM_executable()                   provision_;
   const CORN::OS::File_name &convert_NOAA_met_executable()                 provision_;
   const CORN::OS::File_name &convert_LARS_WG_executable()                  provision_;
   const CORN::OS::File_name &convert_SWAT_executable()                     provision_;
   const CORN::OS::File_name &quality_import_export_executable()            provision_;//140629
   const CORN::OS::File_name &UED_compare_executable()                      provision_;
};
//_class UED::Application_directory_____________________________________________
extern UED::Application_directory *UED_directory;
// This will usually need to be instanciated in the program's main()
} // namespace UED
#endif

