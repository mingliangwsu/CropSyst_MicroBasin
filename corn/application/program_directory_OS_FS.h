#ifndef program_directory_OS_FSH
#define program_directory_OS_FSH
#include <corn/application/adjunct_directory_OS_FS.h>
#include <corn/application/documentation_directory_OS_FS.h>
namespace CORN    {
namespace OS_FS   {
// Forward class declarations
class Suite_directory;
class Application_directory;
//___________________________________________________________________________
class Program_directory
: public Adjunct_directory
{
private:
   // This class defines a directory associated with a application program
   // that has common associated files and subdirectories.
   // such as program defaults, and configuration.
   // and documentation such as help files, tutorials, FAQ etc..

   // Typically the program directory is located in the same directory
   // as the .EXE file and has the same name as the .EXE file without the .EXE extension.
   // Often the directory containing the program directory is the application directory.
   provided_ Documentation_directory *documentation_directory;
      // Can either be the same directory where the associated program
      // is found, or a subdirectory having the same name as the program.

protected:
   provided_ Suite_directory         *Xsuite_directory;       bool suite_directory_owned;
   // Typically the parent directory of this program's application directory.
   // May be 0 if the program is not part of a suite.
   provided_ Application_directory   *Xapplication_directory; bool application_directory_owned;
   // Typically the parent directory of the program directory.
   // May be 0 if the program is not in and application directory (I.e. there is only the program directory).
   // Parameter files:
   provided_ const CORN::OS::File_name *default_ini_file;
   bool find_file_extensions;                                                    //120319

   // This is default user parameters that is often copied into the user's
   // private settings folder.
   // Usually ini default settings are setup in the program.
   // but often it is desirable to allow default settings for user's
   // to be set up after installation. The default.ini file is often
   // included with the program's distribution so it can be
   // used by administrators to adjust default values.
public:
   Program_directory
      (const wchar_t * _associated_program_filename_qualified                    //120320
      ,bool        find_file_extensions = false);
   Program_directory                                                             //120319
      (const OS::Directory_entry_name &associated_program_filename_or_program_dir_qualified
      ,bool find_file_extensions=false);
      // Constructor for associated program mode
      // The associated program should be fully qualified
      // Usually simply pass  argv[0]
      // The default extension for the common documentation files is .htm for HTML,
      // but the common files could have any extension and be any file type.
      // If find_file_extensions is true the constructor will search the program
      // directory for file having the default filename with any extension and assign that name.
      // This option is convenient if at any time you decide to change the
      // file type of the common files.
   virtual ~Program_directory();
public:
   const //141119
   Suite_directory *provide_suite_directory()                          provision_;
   // Returns the parent directory of this program's application directory.
   // May return 0 if the program is not part of a suite.

   Application_directory *provide_application_directory()              provision_;
   // Return the application directory.
   // May return 0 if is not in an application (which I think may be the case, I need to check 120319).
   // Typically the application directory is the parent directory of this program directory
   // (which inturn may have a suite directory as the application directory's parent).
   const Documentation_directory  &Documentation()                    provision_;
#ifdef CONCEPTUAL
   const OS::File_name *find_file_name(const char *unqualified_URL,OS::File_name &found_document_filename);
      /**<
         The unqualified_URL can have one of the following forms:

         %suite%\path\filename.exe#link
         %appl%\path\filename.exe#link
         %prog%\path\filename.exe#link
         filename.exe#link

         The #link is optional.
         In the %xxx% forms, the directory is composed by replacing the
         respective suite, application, or program directory

         The filename is return
      **/
#endif
 public:
   const OS::File_name &default_ini()                                 provision_;
};
//_____________________________________________________________________________/
extern Program_directory *program_directory;
} // namespace OS_FS
} // namespace CORN
//______________________________________________________________________________
#endif

