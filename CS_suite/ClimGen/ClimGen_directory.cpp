#include "ClimGen_directory.h"
namespace CS
{
//---------------------------------------------------------------------------
ClimGen_Directory::ClimGen_Directory(const CORN::OS::Directory_name &directory_name)
: CORN::OS_FS::Program_directory(directory_name)
,climgen_exe_file (0)// ("climgen.exe")
{}
//________________________________________________________________constructor__/
ClimGen_Directory::ClimGen_Directory()
: CORN::OS_FS::Program_directory(CORN::OS::Directory_name_concrete("ClimGen",CORN::OS::directory_entry)) //161029
,climgen_exe_file (0)
{}
//________________________________________________________________constructor__/
ClimGen_Directory::~ClimGen_Directory()
{  reset();
}
//________________________________________________________________
void ClimGen_Directory::reset()                                        provision_
{  if (climgen_exe_file) delete climgen_exe_file; climgen_exe_file = 0;
}
//________________________________________________________________
#ifdef CHECK_OBS
void ClimGen_Directory::set_path(const CORN::OS_ Directory_name &path_name) modifies_
{  CORN::Program_directory::set_path(path_name);
//   set_paths();
}
#endif
//___________________________________________________________________set_path__/
const CORN::OS::File_name &ClimGen_Directory
::ClimGen_exe()                                                        provision_
{  if (!climgen_exe_file)
      climgen_exe_file = new CORN::OS::File_name_concrete(*this,"climgen.exe");
   return *climgen_exe_file;
}
//________________________________________________________________ClimGen_exe__/
} // namespace CS


