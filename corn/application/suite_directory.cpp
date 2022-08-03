#ifndef USE_OS_FS
#include "suite_directory.h"
namespace CORN {
//______________________________________________________________________________
Suite_directory::Suite_directory
(const Directory_name &directory_name
,const char *prefered_documentation_dir_name
,const char *prefered_manual_dir_name
,const char *prefered_icons_dir_name)
: Smart_directory_name     (directory_name)
, documentation_name       (prefered_documentation_dir_name ? prefered_documentation_dir_name : "" )
, manual_name              (prefered_manual_dir_name ? prefered_manual_dir_name : "")
, icons_name               (prefered_icons_dir_name ? prefered_icons_dir_name:"")
, common_directory         (0)
, documentation_directory  (0)
, manual_directory        (0)
, icons_directory          (0)
, install_or_update_filename(0)                                                  //120112
{}
//________________________________________________________________constructor__/
Suite_directory::Suite_directory
(const char *prefered_documentation_dir_name
,const char *prefered_manual_dir_name
,const char *prefered_icons_dir_name)
: Smart_directory_name     ()
   // NOTE: is am just temporarily using the icons_directory as a buffer to to store the initiating_program_qual path
, documentation_name       (prefered_documentation_dir_name ? prefered_documentation_dir_name : "")
, manual_name              (prefered_manual_dir_name        ? prefered_manual_dir_name        : "")
, icons_name               (prefered_icons_dir_name         ? prefered_icons_dir_name         : "")
, common_directory         (0)
, documentation_directory  (0)
, manual_directory         (0)
, icons_directory          (0)
, install_or_update_filename(0)                                                  //120112
{}
//___________________________constructor given an initiating program filename__/
bool Suite_directory
::setup_from_subdirectory_entry(const CORN::Directory_entry_name &directory_entry_name)
{  bool setup_successful = false;
   if (is_root()) return false;
   CORN::Smart_directory_name parent_dir;
   directory_entry_name.get_path(parent_dir);
   if (!parent_dir.exists())
      return false; // will occur if we have trailed up past the root
   if (CORN::Ustring::compare(
      #ifdef SINGLE_INHERITENCE
      std::string(parent_dir.c_str())
      #else
      parent_dir.c_str()
      #endif
         ) != 0)  // It is possible that the default directory is the directory we are trying to compare, in this case set path is not valid.
   {  set_DEN(parent_dir);                                                       //121126
      reset();
   }
   setup_successful = (is_valid())
      ?  true
      : setup_from_subdirectory_entry(parent_dir);
   return setup_successful;
}
//______________________________________________setup_from_initiating_program__/
void Suite_directory::know_initiating_program(const char *initiating_program)
{  current_program.set_cstr(initiating_program);                                 //121126
};
//____________________________________________________know_initiating_program__/
const CORN::File_name &Suite_directory
::qualify_icon_filename
(const char *icon_filename_unqualified
,CORN::Smart_file_name &icon_filename_qualified)                           const
{  icon_filename_qualified.set_DEN(icon_filename_unqualified);                   //121126
   icon_filename_qualified.set_path(icons());
   return icon_filename_qualified;
}
//______________________________________________________qualify_icon_filename__/
Documentation_directory    &Suite_directory
::documentation()                                                      provision_
{  if (!documentation_directory)
   {  CORN::Directory_name dir(documentation_name);  dir.set_path(*this);
      documentation_directory = new Documentation_directory(dir);
   }
   return *documentation_directory;
}
//______________________________________________________________documentation__/
CORN::Smart_directory_name &Suite_directory
::manual()                                                             provision_
{  if (!manual_directory)
   {  CORN::Directory_name dir(documentation_name);  dir.set_path(*this);
      manual_directory = new CORN::Smart_directory_name(dir);
   }
   return *manual_directory;
}
//_____________________________________________________________________manual__/
CORN::Smart_directory_name &Suite_directory
::icons()                                                              provision_
{  if (!icons_directory)
   {  CORN::Directory_name dir(icons_name);  dir.set_path(*this);
      icons_directory = new CORN::Smart_directory_name(dir);
   }
   return *icons_directory;
}
//______________________________________________________________________icons__/
void Suite_directory::reset()                                          provision_ // provides because only modifies provided contributes;
{  if (documentation_directory)  delete documentation_directory;  documentation_directory = 0;
   if (manual_directory)         delete manual_directory;         manual_directory=0;
   if (icons_directory)          delete icons_directory;          icons_directory = 0;
   if (common_directory)         delete common_directory;         common_directory = 0;   //101114
   if (install_or_update_filename)delete install_or_update_filename; install_or_update_filename=0;      //120112
}
//___________________________________________________________reset_subentries__/
CORN::Smart_directory_name &Suite_directory
::common()                                                             provision_
{  if (!common_directory)
   {  CORN::Directory_name dir("common"); dir.set_path(*this);
      common_directory = new Smart_directory_name(dir);
   }
   return *common_directory;
}
//_2010-11-14__________________________________________________________common__/
File_name &Suite_directory::install_or_update()                        provision_
{  if (!install_or_update_filename)
   {  install_or_update_filename = new File_name("install_or_update");
      #ifdef _Windows
         install_or_update_filename->set_ext("exe");
      #endif
      Smart_directory_name installation_dir("installation");
      installation_dir.set_path(*this);
      if (installation_dir.exists())
         install_or_update_filename->set_path(installation_dir);
   }
   return *install_or_update_filename;
}
//_2012-01-12___________________________________________________________________
} // namespace CORN
#endif
