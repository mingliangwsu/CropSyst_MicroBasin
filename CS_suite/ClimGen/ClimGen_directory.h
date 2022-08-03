#ifndef ClimGen_directoryH
#define ClimGen_directoryH
#include "corn/application/program_directory_OS_FS.h"
using namespace CORN::OS_FS;
namespace CS
{
//______________________________________________________________________________
// Forward declarations
class Suite_directory;
//_______________________________________________________Forward_declarations__/
class ClimGen_Directory
: public CORN::OS_FS::Program_directory
{
protected:
   provided_ CORN::OS::File_name_concrete *climgen_exe_file;
public:
   ClimGen_Directory(const CORN::OS:: Directory_name &directory_name);
   // Use this constructor when we know the directory ClimGen is in
   ClimGen_Directory();
   // This construtor is used by CS_suite when in discovery mode construction
   virtual ~ClimGen_Directory();
public: // fluent interfaces
   const CORN::OS::File_name &ClimGen_exe()                            provision_;
   virtual void reset()                                                provision_;
};
//______________________________________________________________________________
extern ClimGen_Directory *ClimGen_directory;
// This must be instanciated in the 'main' for the CropSyst application that uses it.

} // namespace CS
//______________________________________________________________________________
#endif

