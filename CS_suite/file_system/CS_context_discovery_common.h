#ifndef CS_context_discovery_commonH
#define CS_context_discovery_commonH
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system.h"
#include "corn/data_source/datarec.h"
class Geolocation;
namespace CS
{
//______________________________________________________________________________
class Context_discovery_common
{
 protected:
   mutable CORN::OS::Directory_name   *leaf; mutable bool leaf_owned;
   mutable CORN::OS::Directory_name   *root; mutable bool root_owned;
 public:
      // Files and directories found in all parent directories
      // up to the project level.
   contribute_ CORN::Bidirectional_list accessible_files; // sorted                          //170627

 public:
   nat8 verbose;                                                                 //170214
 public:
      // The root is a top most directory to search for files.
      // Typically this logical root would be either a project directory (super project)
      // the user's home
      // (For both Linux/Unix and Windows ~ is recognized as home)
      // or less likely to root of the file system,
      // or the same as the leaf to limit discovery to one directory
      // The leaf would typically be the CWD.

   Context_discovery_common();
   Context_discovery_common                                                      //161102
      (const CORN::OS::Directory_name &leaf_
      ,const CORN::OS::Directory_name *root_ = 0);
      // In this case, the leaf is not necessarily the CWD
      // and the root may be known
   virtual ~Context_discovery_common();
   virtual bool initialize()                                    initialization_; //170607
   bool know_leaf(const CORN::OS::Directory_name &leaf_)             cognition_;
   bool know_root(const CORN::OS::Directory_name *root_)             cognition_;
      // passing 0 will set the root to the primary project
      // (or user's home or file system root) which ever is found first
   bool take_leaf(CORN::OS::Directory_name *leaf_);
   bool take_root(CORN::OS::Directory_name *root_);
   const CORN::OS::Directory_name &provide_leaf()                    provision_; //161116

      // Starting in the leaf, directories in the path are recursively
      // searched for files matching the specified extension.
      // File names are appended to the file list as the function
      // recurses back down the path from the logical root.
      // The recursion up the path stops at the logical root.
      // Typically one will use superdirectory_recursion_inclusive
      // so files in the root are included in the search.
      // \returns the number of files found with matching extension
      // that were added to the file_list.
      // Note that there may be multiple files matching the extension in
      // any directory of the path.
      // If unique is true, only the 'closest' files having the same
      // name lastly encountered while traversing down the directory path
      // are added to the list
      // (which would essentially be longest path name) are retained listed.
      // I.e. if  /x/y/1.ext  and /x/y/z/1.ext are found, only /x/y/z/1.ext
      // Any files already in the list may be replaced with a closer filename.
      // (usually the caller will pass and empty list to be filled).

   CORN::OS::File_name * extract_accessible_file_with_pattern                    //170707
      (const std::wstring &pattern)                               contribution_;

   nat16 extract_accessible_files_with_pattern                                   //170628
      (const std::wstring &pattern
      ,modifiable_ CORN::Container &DEN_list)                     contribution_;
   nat16 extract_accessible_files_with_extension                                 //170628
      (const std::wstring &extension
      ,modifiable_ CORN::Container &file_list)                    contribution_;

   nat16 compose_accessible_parameter_files                                      //170629
      (modifiable_ CORN::Data_record &data_rec
      ,const std::wstring &extension
      ,CORN::Container *caller_keeps_filenames)                   contribution_;

   bool get_geolocation
      (const CORN::OS::Directory_entry_name  &file_or_directory

         // check where used, probably can just search from leaf 180501

      ,const char *geolocation_section
      ,modifiable_ Geolocation               &geolocation
      ,modifiable_ std::string               &ISO_6709_annex_D_or_H)      const;
      // CS parameter files and/or directories can be geolocated
      // geolocation data may be stored in a V4 VV_File in a directory
      // (or any parent dir of a file or directory).
      // These files can be 'composable'
      // Alternatively geolocation can be identified in the name
      // of the file, or directory or in a name of the path using ISO

      // NYI need to add: either the file or directory name or extension

   bool reset_missing_with_accessible                                            //170629
      (modifiable_ CORN::OS::File_name &parameter_file_name
      ,const wchar_t *extension_expected
      ,const wchar_t *extension_alternate)                        contribution_;
   nat16 reset_data_record_missing_with_accessible                               //170629
      (CORN::Data_record &data_record)                            contribution_;
};
//_2015-12-06___________________________________________________________________
}
#endif
