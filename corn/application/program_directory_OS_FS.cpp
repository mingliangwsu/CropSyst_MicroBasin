#include "corn/application/program_directory_OS_FS.h"
#include "corn/application/application_directory_OS_FS.h"
#include "corn/application/suite_directory_OS_FS.h"
#include "corn/OS/file_system_engine.h"
namespace CORN    {
namespace OS_FS   {
//______________________________________________________________________________
Program_directory::Program_directory
(const OS::Directory_name &associated_program_filename_or_program_dir_qualified
,bool        _find_file_extensions)
: Adjunct_directory
   (associated_program_filename_or_program_dir_qualified
   ,false) // program directory is usually prexisting                            //130116
, documentation_directory(0)
, default_ini_file   (0) //(*this,"default.ini")
, Xsuite_directory       (0),  suite_directory_owned(false)
, Xapplication_directory (0),  application_directory_owned(false)
, find_file_extensions(_find_file_extensions)
{}
//_2012-03-19___________________________________________________________________
Program_directory::Program_directory
(const wchar_t * _associated_program_filename_qualified
,bool        find_file_extensions)
: Adjunct_directory
   (OS::File_name_concrete(_associated_program_filename_qualified)
   ,false) // program directory is usually prexisting                            //130116
, documentation_directory(0)
, default_ini_file(0)
, Xsuite_directory       (0),  suite_directory_owned(false)
, Xapplication_directory (0),  application_directory_owned(false)
{}
//______________________________________________________________________________
const OS::File_name &Program_directory::default_ini()                 provision_
{  if (!default_ini_file)
   {  if (find_file_extensions)
           default_ini_file = find_and_render_file_extension(L"default.ini");
      else default_ini_file = new CORN::OS::File_name_concrete(*this,"default.ini");
   }
   return *default_ini_file;
}
//_120319_____________________________________________________________________________
Program_directory::~Program_directory()
{  if (/*141119 Xsuite_directory && */suite_directory_owned) delete Xsuite_directory;
   if (/*141119 Xapplication_directory && */application_directory_owned) delete Xapplication_directory;
}
//______________________________________________________________________________
const //141119
Suite_directory *Program_directory
::provide_suite_directory()                                           provision_
{  if (!Xsuite_directory)
   {  // It is possible this program is in the suite directory
      const CORN::OS::Directory_name *parent_dir = get_path_directory_name();    //140104
      if (parent_dir)
      {

         Xsuite_directory = new Suite_directory(*parent_dir);                     //140104
         if (!Xsuite_directory->is_valid())                                       //120112
         {  // It isn't so try assuming the parent is an application directory in a suite directory
            delete Xsuite_directory;                                              //120112
            Xsuite_directory = 0;                                                 //120112
            provide_application_directory();
            if (Xapplication_directory)
               Xsuite_directory =
                  const_cast<Suite_directory *> //141119
                  (Xapplication_directory->provide_suite_directory_const());  //141119
               // note that the application directory is
               // not necessarily in a suite directory
               // in which case there is not suite directory.
         }
      }
   }
   return Xsuite_directory;
}
//______________________________________________________________________________
Application_directory *Program_directory
::provide_application_directory()                                     provision_
{  if (! Xapplication_directory)
   {
      const CORN::OS::Directory_name *parent_dir = get_path_directory_name();    //140104
      if (parent_dir)                                                            //140104
         Xapplication_directory = new Application_directory(*parent_dir,0 );      //140104_120319
      //140104 application_directory = new Application_directory(get_parent_directory_name_qualified(),0 ); //120319
      // Currently assuming the program directory always has an application directory
      // but that might not be the case.
      // May want to validate that the application_directory is a valid application directory.
      // and if not delete and set to null.
   }
   return Xapplication_directory;
}
//______________________________________________________________________________
const Documentation_directory  &Program_directory::Documentation()    provision_
{
   if (!documentation_directory)
      documentation_directory = new Documentation_directory(*this);
   if (!OS::file_system_engine.exists(*documentation_directory))
   {
       const CORN::OS::Directory_name *parent_dir = associated_program_filename_qualified->get_path_directory_name();    //140104
       if (parent_dir)
          documentation_directory = new Documentation_directory(*parent_dir);
       //140104     documentation_directory = new Documentation_directory(associated_program_filename_qualified->get_parent_directory_name_qualified());
      // There is no associated directory so we will assume the
      // program's directory is the documentation directory.
   }
   return *documentation_directory;
}
//_2012-03-19____________________________________________________Documentation_/
Program_directory *program_directory = 0;
// The optional program directory is used by the Explaination engine
// This will usually be instanciated in main using argv[0]
}} // namespace OS_FS CORN

