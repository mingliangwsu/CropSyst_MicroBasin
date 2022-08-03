#ifndef application_directory_OS_FSH
#define application_directory_OS_FSH
#include "corn/OS/file_system_logical.h"
#include "corn/application/documentation_directory_OS_FS.h"
//______________________________________________________________________________
namespace CORN    {
namespace OS_FS   {
// Forward declarations
class Suite_directory;
//______________________________________________________________________________
class Application_directory
: public OS::File_system_logical::Directory
{
   // An application in a set of programs with associated files
   // including documentation, and support data.

   // A set of applications that are often integrated or used together
   // provided by a common producer/vender is called a suite.

   // This application directory class defines a top level directory
   // structure for either standalone applications,
   // or a subdirectory of an application suite
   // (in this case the directory containing the application directory
   //  is typically an application 'suite' directory).

   // Generally each application program with have its own set of
   // documentation specific to the program (I.e. context senstive help).
   // However, the application or suite may have documentation that is
   // common to all the programs, thus the application directory
   // can itself also have a documentation directory.
private:
   provided_ const Suite_directory * suite_directory;
   provided_ bool suite_directory_owned;
      // The Suite directory is usually the parent (or ancestor) of the application.
      // May be 0 if no suite directory;
private:
   provided_ Documentation_directory    *documentation_directory;                //141114
   std::wstring preferred_icons_directory_name;  // unqualified
   provided_ OS::Directory_name *icons_directory;
public: // structors
   Application_directory
      (const wchar_t *directory_name);  // fully qualified
   Application_directory
      (const OS::Directory_name &directory_name); // fully qualified
   Application_directory                                                         //140519
      (const Suite_directory &suite_directory_reference
      // The Suite directory is usually the parent (or ansestor) of the application.
      ,const wchar_t *directory_name);  // unqualified
   virtual ~Application_directory();
public:
   const Suite_directory *provide_suite_directory_const()             provision_;//140519
      // Returns the parent directory of this program's application directory.
      // May return 0 if the program is not part of a suite.
      // (This must not be virtual.)
      // Derived classes may have their own version of this function
      // that returns a suite directory specific to that application's context.
      // The derived method would likely call this method to find the directory name,
      // then instanciate the derived Suite_directory.
      // It is highly recommend that the derived class's version of this method
      // have a different name I.e. provide_XXXX_suite_directory to avoid ambiguity.
      //120319 may new to replace qualify_icon_filename with render_icon_filename()
      // but need to check where used

   CORN::OS_FS::Documentation_directory &documentation()              provision_;//141114
   const OS::Directory_name    &icons()                               provision_;
   virtual void reset()                                               provision_; // provides because only modifies provided contributes;
};
//_2012-03-19___________________________________________________________________
} // namespace OS_FS
} // namespace CORN
#endif

