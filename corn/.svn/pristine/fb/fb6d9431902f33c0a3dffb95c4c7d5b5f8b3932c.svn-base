#ifndef appdata_directory_OS_FSH
#define appdata_directory_OS_FSH
//---------------------------------------------------------------------------
/*
Vista  : C:\Users\USERNAME\AppData\Local\APPLICATION_PACKAGE\APPLICATION_NAME.ini
2000/XP: C:\Documents and Settings\rnelson\Local Settings\Application Data\APPLICATION_PACKAGE_SUITE\PROGRAM_NAME.ini
UNIX   : $HOME/.APPLICATION_PACKAGE_SUITE\PROGRAM_NAME.ini
In the INI file that will be a section associated with each file and these settings will be stored under the
[filename] section
(Note that the application .ini file may have other sections which will not be modified by this).

Generally the application's directory structure will mirror how the program is installed.
For example under Windows a program is typically installed in
C:\Program files\APPLICATION_PACKAGE_SUITE\PROGRAM_NAME.exe
C:\Program files\my_package\my_program.exe
will have user local settings stored in

C:\Documents and Settings\rnelson\Local Settings\Application Data\my_package\my_program.ini
*/
#  include "corn/OS/directory_entry_name_concrete.h"

// Eventually move this to file_sys
//______________________________________________________________________________
// Forward declarations
namespace CORN  {
class User_settings;
namespace OS_FS {
//______________________________________________________________________________
class Application_data_directory
: public CORN::OS::Directory_name_concrete
// Eventually may derived from CORN::OS::File_system::Directory
{
private:
   provided_ OS::File_name_concrete *settings_filename;
public:
   Application_data_directory(const
      wchar_t
      *application_package_name);
      // In this case the application package name is explicitly specified
      // I.e. from the example above "my_package"
      // The settings filename defaults to the application directory (I.e. my_package).
      // In most cases, using this constructor, the user will want to
      // call the method the set_settings_filename() to assign the desired
      // settings file name.
   Application_data_directory(const OS::Directory_entry_name &application_path_or_program_name);
      // In this case either application's installed location directory
      // or program file name may be specified.

      // In this  case the application's installed location directory is specified
      // I.e. C:\Program files\my_package
      // and the final directory name in the path will be extracted
      // The settings filename defaults to the application directory (I.e. my_package).
      // In most cases, using this constructor, the user will want to
      // call the method the set_settings_filename() to assign the desired
      // settings file name.

      // In the case the program_name is specified, program's installed directory is extracted
      // and used as the package directory.
      // The specified program_name is usually the application executable
      // but it can be any file in the directory
      // The installed directory may depend on the manner of the program's installation:

      // I.e. C:\Program files\my_package\additional_path\my_program.exe
      // In this case the program is installed in a canonical location
      // (In the case of Windows this will usually be the "Program files" folder),
      // the constructor will check for theses case.
      // There may or may not be additional_path when could be multiple parent directories.
      // Often several programs are installed in a subdirectory that typically denotes the software package (suite)
      // or software company's name.
      // This directory name will be used as the application package name
      // any additional path and the program name will be ignored

      // If the program file is not in a recognized canonical path,
      // but is does specified the path, then
      // the constructor will assume the path is in the form:
      // I.e. C:\additional_path\my_package\my_program.exe (Windows)
      //      /usr/bin/additional_path/my_package/my_program
      // And the applicaton package name will be extracted thusly.
      // There will be no attempt to identify the package other than this assumption.

      // If the program has path
      // I.e.  C:\my_program.exe
      // C:|Program file\my_program.exe
      // my_program.exe
      // my_program
      // Then no application data (sub)directory will be assigned.
      // For example Under Windows XP, application data settings will simply be
      // stored in the file
      // C:\Users\USERNAME\AppData\Local\APPLICATION_NAME.ini
      // We consider this case an anathema and encourage always storing a program
      // in an application folder.
      // But this form is not uncommon especially for simple programs and utilities.

      // When the program_name option is used, the program name will
      // also be used for the settings
public: // Settings file
   void set_settings_filename(const char *settings_filename_with_ext_unqualified);
      /**< This method is options if one does not want to use the default user settings file name.
         The settings_filename is unqualified filename with extension.
         Typically the extension will be .ini
      **/

   void save_user_settings     // Probably should rename to save_user_settings
      ( modifiable_ User_settings &settings
      , const char *user_settings_section_name = "position")               const; // should be performs_IO; but currently data source set() is not so defined

   void load_user_settings     // Probably should rename to load_user_settings
      ( modifiable_ User_settings &settings
      , const char *user_settings_section_name  = "position")              const; // should be performs_IO;
      // user_settings_section_name is the  will designate the [section] under which the settings will be stored.
      // For parameter_file_form applications, user_settings_section_name is typically the name of the data file being edited.
      // For example CropSyst remembers the position of each parameter file.
      OS::File_name &provide_settings_filename()                      provision_;
};
//______________________________________________________________________________
} // namespace OS_FS
} // namespace CORN
#endif
