#ifndef file_systemH
#define file_systemH
#include "corn/const.h"
#include "corn/OS/directory_entry_name.h"
#include "corn/chronometry/date_time_64.h"

namespace CORN {
namespace OS {
class Directory_entry_name;
#define FILE_SYSTEM_RECURSION_SUBDIRECTORY   CORN::OS::File_system::subdirectory_recursion_inclusive
#define FILE_SYSTEM_RECURSION_SUPERDIRECTORY CORN::OS::File_system::superdirectory_recursion_inclusive
//#define FILE_SYSTEM_RECURSION_INCLUSIVE
#define FILE_SYSTEM_RECURSION_EXCLUSIVE      CORN::OS::File_system::none_recursion_exclusive
//______________________________________________________________________________
interface_ File_system
{public:
   enum Recursion
      { none_recursion_inclusive             = 0
      , subdirectory_recursion_inclusive     = 1
      , superdirectory_recursion_inclusive   = 2
      , both_recursion_inclusive             = 3
      , none_recursion_exclusive             = 4
      , subdirectory_recursion_exclusive     = 5
      , superdirectory_recursion_exclusive   = 6
      , both_recursion_exclusive             = 7
      };
      // Note these values are bitmasks.
      // In Linux superdirectory_recursion stops in home (inclusive).
      // (could have bits for home inclusive, home exclusive, and follow up to root).
      // When resursing superdirectory recursion only goes up in superdirectories.
      // Exclusive means the start directory file entries are not listed
      // and only once into the recursion are the entries includes.
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class File_type_description : public Item
   {public:
      virtual const std::string &get_extension()                        const=0;
         // Without the dot
      virtual const std::string &get_filter_label()                     const=0;
      virtual const std::string &compose_file_type_pattern_for_Windows
         (std::string &pattern)                                         const=0;
   };
   //___________________________________________________________________________
   class Directory_entry     // interface
   : public extends_interface_ Item  // so it can be listed.
   {public:
      typedef Directory_entry_type Type;
      //________________________________________________________________________
   public:
      virtual bool exists()                                             const=0;
      //conceptual
      virtual const Directory_entry_name &ref_designation()             const=0;
    public:
      virtual const Directory_entry_name &set_wstr
         (const wchar_t *to_copy_from)                          modification_=0;
      virtual const Directory_entry_name &set_cstr
         (const char *to_copy_from)                             modification_=0;
   };
   //_class_Directory_entry____________________________________________________/
   class Directory   // Interface
   : public extends_interface_ Directory_entry
   #ifdef DIRECTORY_ENTRY_IS_A_NAME
   , public extends_interface_ CORN::OS::Directory_entry_name // unqualified
   #endif
   {
   public:  // Note the following functions are actually functions of the operating system's file system, not functions of directory name.
      virtual bool create()                                             const=0;
      inline virtual bool is_directory()            affirmation_{ return  true;} // 130518
      inline virtual bool is_suite()                affirmation_{ return false;} //091109
   public: // The following methods work with the desktop environment
      virtual bool browse                                                        //080929
         (bool open_new_window         = true   ///< Opens a new window otherwise opens and brings to front an existing window that is already open to the directory. //091215_
         ,bool show_directory_tree_view= true   ///< Show directory tree view panel as well as the file list view panel  //091215_
         ,bool show_as_apparent_root   = false  ///< This directory will appear as root (so you can't navigate to parent directories).  //091215_
         ,bool select                  = false  ///< Selects/Highlights this directory in the file list view.
         )                                                              const=0;
         ///< Derived classes should override this.
         ///< In windows, for example, this will launch Windows Explorer
   public:
         /** In the following methods, the rendered file or directory name
             (if found) is reliquished to to the caller.
            \returns null if no such directory entry exists.
         **/
      virtual CORN::OS::File_name *find_file_name
         (const std::wstring    &target_filename
         ,File_system::Recursion recursion)                        rendition_=0;                                       //150908
         ///< The target_filename may be a wildcard pattern.
         ///< There could be multiple files that match the target filename,
         ///< we simply return the first in the list.
      virtual CORN::OS::Directory_name *find_directory_name                      //100107
         (const std::wstring  &target_directory_name
         ,File_system::Recursion recursion                                       //150908
         ,Directory_entry_name::Qualification qualification                      //150908
         )                 rendition_ = 0;
         ///< The rendered directory name (if found) is reliquished to to the caller.
         ///< \return null if no such directory

      /* In the following find_xxx_in_path methods
         The search extends up the to the parent directory.
         If recurse is true the search extends up the parent's parent directory.
         If inclusive is true, the this directory is searched
         (??but not subdirectories??)
      */
      virtual CORN::OS::File_name *find_file_name_in_path                        //110202
         (const std::wstring   &target_file_name_unqualified
         ,bool recurse_up_the_path,bool inclusive)                 rendition_=0;
      virtual CORN::OS::Directory_name *find_directory_name_in_path              //110202
         (const std::wstring   &target_dir_name_unqualified
         ,bool recurse_up_the_path,bool inclusive)                 rendition_=0;
      virtual void reset()                                         provision_=0;
         ///< Clears provided directory and file names.
      #ifdef NYI
      virtual const Directory_entry *provide_resolved_directory_entry
         (const Directory_entry_name &relative_DEN)                provision_=0;
         /**<
         \return
         **/
      #endif

    public:
      #ifdef NYI
      Directory *find_directory(const std::string &unqualified_dir_name,bool recursive) const = 0;   //081211
         ///< NYI unqualified_file_name_to_find may contain wild card characters.
         ///< creates and returns the fully qualified filename if it is found.
         ///< The ownership of the filename is reliquished to the caller.
      bool create()                                          performs_IO_const_;
         ///< Create the directory.
         ///< (although technically could be a const, it does I/O, so don't use const.)
         ///< All parent directories in the path will also be created if they don't already exist.
         ///< Returns true if the directory was newly created or already exists.
         ///< false if it could not be created
      bool set_as_current_working_directory()                performs_IO_const_;
         ///< Returns true if successful.
         ///< (although technically could be a const, it does I/O, so don't use const.)
      virtual int invoke_viewer()                                         const; //011104
         ///< This launches a folder browser opens the folder as a root in a new window with double pane mode
         ///< In windows this is Windows explorer
         ///< Under X-Windows this is the respective browser.
         ///< See also directory_entry::browse();
    #endif
   };
   //_class_Directory__________________________________________________________/
   class File
   : public extends_interface_ Directory_entry
   {
    public: // 'structors
    public:
    private:
   };
   //_class_File_______________________________________________________________/
 public:
   virtual const File_system::Directory *provide_directory                       //120207
      (const CORN::OS::Directory_name &directory_name)             provision_=0;
};
//______________________________________________________________ File_system __/
//extern File_system &file_system;

File_system &file_system();
// The file_system() function is not implemented in the library.
// This method must be implemented by the calling program or derived classes.
// The calling program must include a library that implements a File_system
// (or implement one itself).
// Then implement this function which will return a reference to an
// instance of the file_system.

/* If you don't need a specialized file system, add the following lines
to your main() source file.
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
*/


} } // namespace CORN OS
#endif
