#include "corn/parameters/parameters_directory_OS_FS.h"
#if (defined(_WIN32)  || defined(_WIN64) || defined(__MSDOS__))
#  include <windows.h>
#endif
#include "corn/application/project_directory_OS_FS.h"
#include <fstream>
namespace CORN
{
namespace OS_FS
{
//_______________________________________________________________________/
Parameters_directory::Parameters_directory
(const CORN::OS::Directory_entry_name & parameters_directory_entry_name
, bool create_now_if_needed)                                                     //130116
: CORN::OS::File_system_logical::Directory
   (parameters_directory_entry_name.is_directory()
      ? parameters_directory_entry_name
      : *parameters_directory_entry_name.get_path_directory_name()
        // WARNING I am currently not checking for parent existance
        // but it should always be the case that this is not in root.
      //140104: parameters_directory_entry_name.get_parent_directory_name_qualified()
   ,create_now_if_needed)
, associated_filename_(0)
, details_filename(0)
, status_filename(0)
, notes_filename(0)
, explaination_filename(0)
{}
//_______________________________________________________________________/
Parameters_directory::Parameters_directory
(const CORN::OS::Directory_entry_name & parameters_directory_entry_name
,CORN::OS::File_system::Directory_entry::Type type
, bool create_now_if_needed)                                                     //130116
: CORN::OS::File_system_logical::Directory
   (type == CORN::OS::directory_entry
      ? parameters_directory_entry_name
      : *parameters_directory_entry_name.get_path_directory_name()
        // WARNING I am currently not checking for parent existance
        // but it should always be the case that this is not in root.
      //140104: : parameters_directory_entry_name.get_parent_directory_name_qualified()
   ,create_now_if_needed)
, associated_filename_(0)
, details_filename(0)
, status_filename(0)
, notes_filename(0)
, explaination_filename(0)
{}
//_______________________________________________________________________/
Parameters_directory::~Parameters_directory()
{  delete associated_filename_;
   delete details_filename;
   delete status_filename;
   delete notes_filename;
   delete explaination_filename;
}
//_2013-02-15____________________________________________________________/
const CORN::OS::File_name &Parameters_directory::associated_filename() provision_
{  if (!associated_filename_)
   {
      const wchar_t *assoc_file_ext = get_associated_file_extension();
      // first if the file is the same name as the directory with a specific extension
      // (filename directory pair)
      associated_filename_ = new CORN::OS::File_name_concrete(*this,
         std::wstring(L""), OS::Extension(assoc_file_ext));
      if (!OS::file_system_engine.exists(*associated_filename_))
      {
         delete associated_filename_;
         // else assume the associated file is in the directory.
         associated_filename_ = new CORN::OS::File_name_concrete(*this,assoc_file_ext);
      }
   }
   return *associated_filename_;
}
//_2012-03-21_______________________________________associated_filename__/

#ifdef NYI

Need to update to use OS FS
//_________________________
Common_parameters_directory::Common_parameters_directory
   (CORN::Smart_file_name *_associated_parameters_filename                       //090830
   , bool take_filename                                                          //090830
   , Associated_directory_mode _associated_directory_mode                        //060614
   , bool create_now                                                             //060614
   // if associated_parameters_filename!=0 then
   // we may need to create the directory
   ) : Smart_directory_name()                                                    //070717
, associated_filename(_associated_parameters_filename)                           //090222
, associated_filename_owned(take_filename)
, associated_directory_mode(_associated_directory_mode)                          //060614
{  if (!associated_filename->is_qualified())                                     //090222
      associated_filename->set_path(*this);                                      //090222
   File_name param_filename_no_ext(*associated_filename);                        //070629
   switch(associated_directory_mode)                                             //060616
   {case PARENT_ASSOCIATED_DIRECTORY:                                            //060616
      {  param_filename_no_ext.get_path(*this);                                  //060616
      }break;                                                                    //060616
    case REQUIRED_ASSOCIATED_DIRECTORY:                                          //060616
    case OPTIONAL_ASSOCIATED_DIRECTORY:                                          //060616
      {  if (associated_filename->exists()                                       //090820_060614
            || create_now)                                                       //090826
         {  param_filename_no_ext.set_ext("");
            param_filename_no_ext.strip(std::string::Trailing, '.');
            set(param_filename_no_ext.c_str());                                  //030205
         }
      }break;
    case NO_ASSOCIATED_DIRECTORY:                                                //060616
      {
         // This is used with parameter files that do not generally have an associated directory.
         // For example CropSyst parameter files are store in a user specified directory
         // with other related parameter files.
         // In this case the only associated file may be a notes file which has the same name
         // as the parameter file with a .txt extension.
         // The associated directory is simply set to the directory containing the parameter file. 060616
         CORN::Directory_name param_file_dir; // 080610
         param_filename_no_ext.get_path(param_file_dir, false);
         // 080610 Note we want the trailing
         if (associated_filename->exists())                                      //080701
         {  set(param_file_dir.c_str());                                         //080610
         }
      }break;
   }
   initialize(create_now);                                                       //070717
}
//_2006-06-14_______________________________________________constructor__/
Common_parameters_directory::Common_parameters_directory
   (const CORN::Directory_name & _directory_name,
   Associated_directory_mode _associated_directory_mode                    //060614
   , bool create_now                                                       //060614
   // if associated_parameters_filename!=0 then
   // we may need to create the directory                                  //070717
   )                                                                       //060614
: CORN::Smart_directory_name(_directory_name)                              //090222
, associated_directory_mode(_associated_directory_mode)                    //090222
, associated_filename(0), associated_filename_owned(false)                 //070717
{  initialize(create_now);
}
//_2007-07-17_______________________________Common_parameters_directory__/
void Common_parameters_directory::initialize(bool create_now)
{  if (create_now) create();
}
//_2007-07-17____________________________________________________________/
Common_parameters_directory::~Common_parameters_directory()
{  if ((associated_filename) && associated_filename_owned)
      delete associated_filename;
}
//_2009-02-22________________________________________________destructor__/
bool Common_parameters_directory::matches_associated_file
(const char *file_name)                                                    const
{  File_name filename_no_ext(file_name);
   filename_no_ext.set_ext("");
   filename_no_ext.strip(std::string::Trailing, '.');
   return(filename_no_ext == *this);
}
//_2006-07-09___________________________________matches_associated_file__/
const CORN::Smart_file_name &Common_parameters_directory::get_filename
   (bool fully_qualified, const CORN::Smart_file_name &filename,
   const CORN::Smart_directory_name &qualifaction_dir)mutates_
{  filename_return_buffer.set(filename.c_str());
   if (fully_qualified)
   {  if (!filename.is_qualified(true))
      // might only be partially qualified
         filename_return_buffer.set_path(qualifaction_dir);
   } else
      filename_return_buffer.assign(filename.get_name(true));
   return filename_return_buffer;
}
//_2004-10-30______________________________________________get_filename__/
#endif
CORN::OS::File_name *Parameters_directory::render_filename
// 120323
(const wchar_t *unqualified_filename_with_extension)                  rendition_
{  CORN::OS::File_name_concrete *rendered_filename =
      new CORN::OS::File_name_concrete(*this,
      unqualified_filename_with_extension);
   return rendered_filename;
}
//_2009-02-22______________________________________________get_filename__/
provide_file_name_implementation(Parameters_directory,details     ,details_filename     ,L"details.html")
provide_file_name_implementation(Parameters_directory,status      ,status_filename      ,L"status.html")
provide_file_name_implementation(Parameters_directory,notes       ,notes_filename       ,L"notes.txt")
provide_file_name_implementation(Parameters_directory,explaination,explaination_filename,L"explaination.html")
//_2013-02-15___________________________________________________details__/
#ifdef NYI
bool Common_parameters_directory::get_backup_filename
   (CORN::Smart_file_name &return_filename, bool check_existence)          const
{  CORN::File_name unqualified_backup_filename("backup");
   unqualified_backup_filename.set_ext(get_ext().c_str());
   // Assume the backup filename has the same extension as
   return get_filename(unqualified_backup_filename.c_str(),
      return_filename, check_existence);
}
//_2009-02-22_______________________________________get_backup_filename__/
Smart_directory_name &Common_parameters_directory::get_qualified()         const
{  dirname_return_buffer.set(c_str());
   dirname_return_buffer.qualify();
   return dirname_return_buffer;
}
//_2005-03-24______________________________________________get_qualified_/
#endif
void Parameters_directory::write_desktop_ini()
{
   int icon_index = 0;
   CORN::OS::File_name_concrete icon_filename;                                   //130215
   get_folder_icon_filename(icon_filename, icon_index);                          //130215
   if (CORN::OS::file_system_engine.exists(icon_filename))                       //130215_090625
   {
      #ifdef __linux__
      // See documentation on desktop files standard:
      // http://standards.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html#recognized-keys
      CORN::OS::File_name_concrete qualified_directory_filename(this,"",".directory"); //130215
      // Warning, this is always appending to the file.
      // In need to replace this with functions that modify
      // the file like WritePrivateProfileString
      std::ofstream directory_file(qualified_directory_filename.c_str(), std::ios::app);
      directory_file << "[Desktop Entry]" << std::endl;
      directory_file << "Icon=" << icon_filename.c_str()<< std::endl;
      //NYI directory_file << "Comment=" << get_InfoTip << std::endl;
      #endif
      #if (defined(_WIN32)  || defined(_WIN64) || defined(__MSDOS__))
      CORN::OS::File_name_concrete qualfied_desktop_filename(*this,"desktop.ini");
      #ifdef __BCPLUSPLUS__
      char icon_index_str[10];                                                   //090624
      WritePrivateProfileString(".ShellClassInfo", "IconFile",
         icon_filename.c_str(), qualfied_desktop_filename.c_str());
      WritePrivateProfileString(".ShellClassInfo", "IconIndex",
         itoa(icon_index, icon_index_str, 10),
         qualfied_desktop_filename.c_str());                                     //090624
      SetFileAttributes(c_str(), FILE_ATTRIBUTE_SYSTEM);                         //090624
      #else
      wchar_t icon_index_str[10];                                                //090624
      WritePrivateProfileStringW(L".ShellClassInfo", L"IconFile",
         icon_filename.w_str(), qualfied_desktop_filename.w_str());              //090624
      WritePrivateProfileStringW(L".ShellClassInfo", L"IconIndex",
         _itow(icon_index, icon_index_str, 10),
         qualfied_desktop_filename.w_str());                                     //090624
      SetFileAttributesW(w_str(), FILE_ATTRIBUTE_SYSTEM);                        //090624
      #endif
      // NYI       WritePrivateProfileString(".ShellClassInfo","InfoTip"  ,description.c_str()              ,qualfied_desktop_filename.c_str());
      // In windows we need to make this a system file in order to show the folder
#ifdef NYI
      The following can be used to set the background image
      for the file WritePrivateProfileString(".ExtShellFolderViews",
         "{BE098140-A513-11D0-A3A4-00C04FD706EC}",
         "{BE098140-A513-11D0-A3A4-00C04FD706EC}",
         qualfied_desktop_filename.c_str());
      WritePrivateProfileString("{BE098140-A513-11D0-A3A4-00C04FD706EC}",
         "Attributes", "1", qualfied_desktop_filename.c_str());
      WritePrivateProfileString("{BE098140-A513-11D0-A3A4-00C04FD706EC}",
         "IconArea_Image", iconarea_image_filename.c_str(),
         qualfied_desktop_filename.c_str());
      /*
      [ExtShellFolderViews]
      {BE098140-A513-11D0-A3A4-00C04FD706EC}={BE098140-A513-11D0-A3A4-00C04FD706EC}
      [{BE098140-A513-11D0-A3A4-00C04FD706EC}]
      Attributes=1
      IconArea_Image=P1010031.JPG
       */
#endif
#endif
   }
}
#ifdef NYI
//_2006-04-15_________________________________________write_desktop_ini__/
bool Common_parameters_directory::get_project_directory
(CORN::Common_project_directory &project_directory)
{  bool is_project_dir = false;
   bool at_root = false;
   CORN::Directory_name curr_dir(*this);
   do
   {  curr_dir.get_path(project_directory);
      is_project_dir = project_directory.is_valid();
      if (!is_project_dir)
      {  at_root = project_directory.is_root();
         if (!at_root)
            project_directory.get_path(curr_dir);
      }
   }
   while (!is_project_dir && !at_root);
   return is_project_dir;
}
//_2010-03-11_____________________________________get_project_directory__/
#endif
} } // namespace CORN::OS_FS


