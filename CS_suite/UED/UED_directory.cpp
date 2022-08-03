#include "UED_directory.h"
//______________________________________________________________________________
namespace UED
{
//______________________________________________________________________________
Application_directory::Application_directory(const wchar_t *directory_name)
: CORN::OS_FS::Application_directory(directory_name)
, convert_dir                          (0)//("convert")
, convert_formats_dir                  (0)//("formats")
, quality_dir                          (0)                                       //140629
, import_wizard_exe                    (0)//("import_wizard.exe")
, export_wizard_exe                    (0)//("export_wizard.exe")
, spatial_interpolator_exe             (0)//("UED_spatial_interpolator.exe")
, convert_export_exe                   (0)//("export.exe")
, convert_tabular_format_editor_exe    (0)//("tabular_format_editor.exe")
, map_google_exe                       (0)
, condense_exe                         (0)
#ifdef __unix
, convert_LADSS_exe                    (0)//("LADSS")  // There is no exe extension (This is used only under UNIX)
#endif

// The following are convertor with import and export
, convert_Excel_workbook_with_TDF_exe  (0)//("Excel_workbook_with_TDF.exe")
, convert_text_dBase_Excel_with_TDF_exe(0)//("text_dBase_Excel_with_TDF.exe")
, convert_CropSyst_exe                 (0)
// The following are convertors with export only
, convert_RZWQM_exe                    (0)
, convert_Canadian_Climatological_exe  (0)
, convert_DYRESM_exe                   (0)
, convert_NOAA_met_exe                 (0)
, convert_LARS_WG_exe                  (0)
, convert_SWAT_exe                     (0)
, quality_import_export_exe            (0)                                       //140629

, UED_compare_exe                      (0)
{}
//________________________________________________________________constructor__/
Application_directory::Application_directory
(const CORN::OS_FS::Suite_directory &_suite_dir
, const wchar_t *_directory_name)
: CORN::OS_FS::Application_directory(_suite_dir,_directory_name)
, convert_dir                          (0)//("convert")
, convert_formats_dir                  (0)//("formats")
, quality_dir                          (0)                                       //140629
, import_wizard_exe                    (0)//("import_wizard.exe")
, export_wizard_exe                    (0)//("export_wizard.exe")
, spatial_interpolator_exe             (0)//("UED_spatial_interpolator.exe")
, convert_export_exe                   (0)//("export.exe")
, convert_tabular_format_editor_exe    (0)//("tabular_format_editor.exe")
, map_google_exe                       (0)
, condense_exe                         (0)
#ifdef __unix
, convert_LADSS_exe                    (0)//("LADSS")  // There is no exe extension (This is used only under UNIX)
#endif

// The following are convertor with import and export
, convert_Excel_workbook_with_TDF_exe  (0)//("Excel_workbook_with_TDF.exe")
, convert_text_dBase_Excel_with_TDF_exe(0)//("text_dBase_Excel_with_TDF.exe")
, convert_CropSyst_exe                 (0)
// The following are convertors with export only
, convert_RZWQM_exe                    (0)
, convert_Canadian_Climatological_exe  (0)
, convert_DYRESM_exe                   (0)
, convert_NOAA_met_exe                 (0)
, convert_LARS_WG_exe                  (0)
, convert_SWAT_exe                     (0)
, quality_import_export_exe            (0)                                       //140629
\
, UED_compare_exe                      (0)
{}
//_2014-05-19_____________________________________________________constructor__/
Application_directory::~Application_directory()
{  reset(); }
//_____________________________________________________~Application_directory__/
void Application_directory::reset()                                    provision_
{
   delete import_wizard_exe;                       import_wizard_exe = 0;
   delete export_wizard_exe;                       export_wizard_exe = 0;
   delete spatial_interpolator_exe;                spatial_interpolator_exe = 0;
   delete convert_export_exe;                      convert_export_exe = 0;
   delete convert_tabular_format_editor_exe;       convert_tabular_format_editor_exe = 0;
   delete convert_Excel_workbook_with_TDF_exe;     convert_Excel_workbook_with_TDF_exe = 0;
   delete convert_text_dBase_Excel_with_TDF_exe;   convert_text_dBase_Excel_with_TDF_exe = 0;
#ifdef __unix
   delete convert_LADSS_exe;                       convert_LADSS_exe = 0;
#endif
   delete convert_CropSyst_exe;                    convert_CropSyst_exe = 0;
   delete convert_RZWQM_exe;                       convert_RZWQM_exe = 0;
   delete convert_Canadian_Climatological_exe;     convert_Canadian_Climatological_exe = 0;
   delete convert_DYRESM_exe;                      convert_DYRESM_exe = 0;
   delete convert_NOAA_met_exe;                    convert_NOAA_met_exe = 0;
   delete convert_LARS_WG_exe;                     convert_LARS_WG_exe = 0;
   delete convert_SWAT_exe;                        convert_SWAT_exe = 0;
   delete quality_import_export_exe;               quality_import_export_exe = 0;//140629

   // Directories should be deallocated last
   delete convert_dir;                             convert_dir = 0;
   delete convert_formats_dir;                     convert_formats_dir = 0;
   delete quality_dir;                             quality_dir = 0;
}
//______________________________________________________________________reset__/
provide_directory_name_implementation  (UED::Application_directory,convert         ,convert_dir         ,"convert");
provide_directory_name_implementation  (UED::Application_directory,quality         ,quality_dir         ,"quality"); //140629
provide_file_name_implementation       (UED::Application_directory,import_wizard_executable     ,import_wizard_exe   ,"import_wizard.exe");
provide_file_name_implementation       (UED::Application_directory,export_wizard_executable     ,export_wizard_exe   ,"export_wizard.exe");
//NYI UED_spatial_interpolator
provide_subdir_file_name_implementation(UED::Application_directory,convert_export_executable    ,convert_export_exe,convert() ,"export.exe");
provide_file_name_implementation       (UED::Application_directory,UED_compare_executable       ,UED_compare_exe              ,"compare.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_tabular_format_editor_executable    ,convert_tabular_format_editor_exe     ,convert(),"tabular_format_editor.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_Excel_workbook_with_TDF_executable  ,convert_Excel_workbook_with_TDF_exe   ,convert(),"Excel_workbook_with_TDF.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_text_dBase_Excel_with_TDF_executable,convert_text_dBase_Excel_with_TDF_exe ,convert(),"text_dBase_Excel_with_TDF.exe");
provide_file_name_implementation       (UED::Application_directory,map_google_executable        ,map_google_exe,"map_google.exe");
provide_file_name_implementation       (UED::Application_directory,condense_executable,condense_exe,"condense.exe");
#ifdef _unix
provide_subdir_file_name_implementation(UED::Application_directory,convert_LADSS_executable,convert_LADSS_exe,"LADSS");
#endif
provide_subdir_file_name_implementation(UED::Application_directory,convert_CropSyst_executable                  ,convert_CropSyst_exe                  ,convert(),"CropSyst.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_RZWQM_executable                     ,convert_RZWQM_exe                     ,convert(),"rzwqm.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_Canadian_Climatological_executable   ,convert_Canadian_Climatological_exe   ,convert(),"canadian_climatological.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_DYRESM_executable                    ,convert_DYRESM_exe                    ,convert(),"DYRESM.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_LARS_WG_executable                   ,convert_LARS_WG_exe                  ,convert(),"LARS-WG.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_NOAA_met_executable                  ,convert_NOAA_met_exe                  ,convert(),"noaa_met.exe");
provide_subdir_file_name_implementation(UED::Application_directory,convert_SWAT_executable                      ,convert_SWAT_exe                      ,convert(),"SWAT.exe");
provide_subdir_file_name_implementation(UED::Application_directory,quality_import_export_executable             ,quality_import_export_exe             ,quality(),"import_export.exe");

//______________________________________________________________________________
const CORN::OS::File_name &Application_directory
::spatial_interpolator_executable()                                    provision_
{  if (!spatial_interpolator_exe)
   {  CORN::OS::Directory_name_concrete spatial_dir(*this,L"spatial");
      CORN::OS::Directory_name_concrete spatial_interpolation_dir(spatial_dir,L"interpolation");
      spatial_interpolator_exe = new CORN::OS::File_name_concrete(spatial_interpolation_dir,L"UED_spatial_interpolator.exe");
   }
   return *spatial_interpolator_exe;
};
//______________________________________________________________________________
const CORN::OS::Directory_name &Application_directory
::convert_formats()                                                    provision_
{  if (!convert_formats_dir)
      convert_formats_dir = new CORN::OS::Directory_name_concrete(convert(),"formats");
   return *convert_formats_dir;
}
//______________________________________________________________________________
} // namespace UED

