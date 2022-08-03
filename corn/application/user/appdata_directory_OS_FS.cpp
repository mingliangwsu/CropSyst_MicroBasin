#include "appdata_directory_OS_FS.h"
#include "corn/data_source/vv_file.h"
#include "corn/data_source/datarec.h"
#include "corn/application/user/settings.h"
#include "corn/OS/file_system_engine.h"

#if (defined(_WIN32)  || defined(_WIN64) || defined(__MSDOS__))
#  include <windows.h>
#  include <shlobj.h>
#endif
#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif
namespace CORN    {
namespace OS_FS   {
//---------------------------------------------------------------------------
Application_data_directory::Application_data_directory(const wchar_t *application_package_name)
: OS::Directory_name_concrete
(
#if (defined(_WIN32)  || defined(_WIN64) || defined(__MSDOS__))
CSIDL_LOCAL_APPDATA
#endif
#ifdef __linux__
//Unix/Linux home directory
CORN::OS::Directory_name_concrete(getpwuid(getuid())->pw_dir)                    //160812
#endif
,std::wstring(application_package_name),std::wstring(L""))
, settings_filename(0)  // in this version, the filename will be provided as needed
{
   /*
      set_ext("");
         // In this case the application package name is explicitly specified
         // I.e. from the example above "my_package"
      #if defined(_Windows)
      CORN::Smart_directory_name local_appdata_directory(CSIDL_LOCAL_APPDATA);
      #endif
      #ifdef unix
      CORN::Smart_directory_name local_appdata_directory("~/.local");
      #endif
   // WARNING need something for other OSs
      set_path(local_appdata_directory);
      settings_filename.set_path(*this);
   */
}
//______________________________________________________________________________
Application_data_directory::Application_data_directory(const OS::Directory_entry_name &application_path)
: OS::Directory_name_concrete
(
#if (defined(_WIN32)  || defined(_WIN64) || defined(__MSDOS__))
CSIDL_LOCAL_APPDATA
#endif
#ifdef __linux__
//Unix/Linux home directory
CORN::OS::Directory_name_concrete(getpwuid(getuid())->pw_dir)                    //160812
#endif

,application_path.get_name(),std::wstring(L""))
, settings_filename(0)
{}
//_2012-02-14______________________________________________________constructor_/
void Application_data_directory::set_settings_filename(const char *settings_filename_with_ext_unqualified)
{
   if (settings_filename) delete settings_filename;
   settings_filename = new OS::File_name_concrete(*this,settings_filename_with_ext_unqualified);
}
//______________________________________________________________________________
void Application_data_directory::save_user_settings
( modifiable_ User_settings &settings
, const char *user_settings_section_name)                                  const
{
   OS::file_system_engine.provide_directory/*180321 create_directory*/(*this);// Create this application/package directory if it doesn't already exist (otherwise we cannot write the file into it)
   VV_File settings_file(provide_settings_filename().c_str());
   Data_record settings_data_rec(user_settings_section_name);
   settings_data_rec.set_preserve_unexpected_entries(true);
   settings_data_rec.set_current_section(user_settings_section_name);
   settings.setup_structure(settings_data_rec);
   settings_file.set(settings_data_rec);
}
//______________________________________________________________________________
void Application_data_directory::load_user_settings
( modifiable_ User_settings &settings
, const char *user_settings_section_name)                                  const
{  VV_File settings_file(provide_settings_filename().c_str());
   Data_record settings_data_rec(user_settings_section_name);
   settings_data_rec.set_current_section(user_settings_section_name);
   settings.setup_structure(settings_data_rec);
   settings_file.get(settings_data_rec);
}
//__________________________________________________________load_user_settings_/
OS::File_name &Application_data_directory::provide_settings_filename() provision_
{  if (!settings_filename)
      settings_filename = new OS::File_name_concrete(*this,get_name(),L"ini");
   return *settings_filename;
}
//_2013-03-19________________________________________provide_settings_filename_/
} // namespace OS_FS
} // namespace CORN
