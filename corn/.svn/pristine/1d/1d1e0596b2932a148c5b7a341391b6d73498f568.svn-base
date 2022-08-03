#ifndef file_system_engine_WindowsH
#define file_system_engine_WindowsH

#ifndef _WIN32
//(!defined (_Windows) || !defined(_WIN32) || !defined(_WIN64))
#error The compiler does not appear to be targeting Windows.
#error This file is an implementation of the File_system_engine class specific for Windows.
#error If you are indeed compiling for Windows then you may need to add a #define _Windows to your project or make file compiler command line options.
#error If you are compiling for another OS remove this file from your project/makefile and add the File_system_engine_XXXX file for the target OS.
#endif

#include "corn/const.h"
#include "corn/OS/file_system_engine_common.h"
#ifdef _QT_
#include "corn/OS/file_system_engine_Qt.h"
#endif

namespace CORN { namespace OS {
//_______________________________________________________forward declarations__/
class File_system_engine_Windows
: public extends_
#ifdef _QT_
   File_system_engine_Qt
#else
   File_system_engine_common
   // The file system engine must implement all the methods of the file system
   // even though file systems specific for OSs are not themselves engines
#endif
{
 public:
   virtual bool create_directory
      (const OS::Directory_name &directory_name
      //180321 ,bool create_parents_as_needed
      )                                     const; //130126
      ///< Creates a directory with the specified name in the file system.
      ///< \return the created directory element or null if the operating system
      ///  was unable to create the directory.
   virtual bool create_directory_link
      (const Directory_name &source_directory_name
      ,const Directory_name &target_directory_name
      ,bool symbolic = LINK_SYMBOLIC)                                     const;
      ///< Create a hard or soft link to a directory
      ///\return the created directory element or null if the OS was unable
      /// to create the directory.
   virtual bool create_file_link
      (const File_name &source_directory_name
      ,const File_name &target_directory_name
      ,bool symbolic = LINK_SYMBOLIC)                                     const;
      ///< Create a hard or soft link to a directory
      ///\return the created directory element or null if the OS was unable
      /// to create the directory.
   virtual bool recycle
      (const Directory_entry_name &entry_name, bool delete_forever)       const;
      ///< The file is not deleted unless delete_forever is true;
      ///<\return true if the file was successfully recycled, false if it failed
      /// (nothing happened).
   #ifdef __BCPLUSPLUS__
   //150320 Actually the new implmentation as I have it in File_system_engine_common
   // should replace this, but I need to make sure it is working
   // as before for BC++
   virtual bool delete_directory
      (const Directory_name & directory_name_to_delete
      ,bool recurse_subdirectories
      ,CORN::Container *deleted_file_names_optional         = 0
      ,CORN::Container *not_deleted_file_names_optional     = 0
      ,CORN::Container *deleted_directory_names_optional    = 0
      ,CORN::Container *not_deleted_directory_name_optional = 0
      ,CORN::Text_list *error_log_optional                  = 0
      ,bool delete_only_file_and_preserve_folder_and_subfolders = false)  const;
      ///< Declared and documented in File_system
   #endif
   #ifndef _QT_
   virtual nat32 list_names_in                                                   //161013
      (const Directory_name & directory_name
      ,CORN::Text_list *file_name_list_unqual
      ,CORN::Text_list *directory_name_list_unqual)                       const;
   #endif

   virtual bool browse_directory
      (const Directory_name &dir_name
      ,bool open_new_window
      ,bool show_directory_tree_view
      ,bool show_as_apparent_root
      ,bool select)                                                       const;
      ///< Declared in and documented File_system
   virtual bool edit_file(const File_name &file_name)                     const;
      ///< Edit the file with a suitable  associated program using ShellExecute
   virtual bool view_file  (const File_name &file_name)                   const;
   virtual bool print_file (const File_name &file_name)                   const;
   virtual bool open_file  (const File_name &file_name)                   const;
   virtual bool copy_file
      (const File_name &source, const File_name &destination
      ,bool fail_if_exists)                                               const; //120209
   virtual bool copy_directory                                                   //130215
      (const Directory_name &source, const Directory_name &destination
      ,bool fail_if_exists)                                               const;

   virtual bool move
      (const Directory_entry_name &source_DEN
      ,const Directory_entry_name &destination_DEN
      ,bool force
      ,bool interactive
      ,bool update
      ,bool verbose)                                                      const;

   /*171215  conceptual (abanonded?)
   virtual bool move_file_into_directory                                         //171215
      (const Directory_entry_name &DEN
      ,const Directory_name       &destination_directory
      ,bool  fail_if_exists)                                              const;
      // Moves the specified file to the
      // specified destination directory.

   virtual bool move_directory_into_directory                                    //171215
      (const Directory_entry_name &DEN
      ,const Directory_name       &destination_directory
      ,bool  fail_if_exists)                                              const;
      // Moves the specified directory  to the
      // specified destination directory.
   */
   /* Conceptual
   virtual bool are_in_same_file_system
      (const Directory_entry_name &DEN1
      ,const Directory_entry_name &DEN2)                            affirmation;
      // Returns true if both Directory entries are on the same file system
      // which would be the same drive designator
      // If either is unqualified need to get fully qualified name.
   */

   virtual bool exists(const Directory_entry_name &directory_entry_name)  const;
   virtual datetime64 get_modification_date_time
      (const Directory_entry_name &directory_entry_name)                  const;
   virtual bool is_symbolic_link(const Directory_entry_name &file_name)   const; //121001
   virtual bool is_shortcut(const Directory_entry_name &file_name)        const; //151207
   virtual Directory_name *render_CSIDL_directory_name(nat16 CSIDL)       const;
   virtual Directory_name *render_current_working_directory_on_drive
      (const Drive_designator &logical_drive_name)                        const; //120430
      // Instanciates a directory name corresponding to the
      // the current working directory on the specified drive.
      // The directory name object is relinquished to the caller.

 public: // The following methods are currently unique to Windows
   virtual bool create_shortcut
      (const Directory_entry_name &target_file
         // I think will also work for directory but I haven't tried it
      ,const Directory_name &short_cut_location
         // where the shortcut will be created
      ,const std::wstring &caption
      ,const std::wstring &description)                                   const;
      ///< Return true if the shortcut was created successfully

/* conceptual
   virtual modifiable_ CORN::OS::Directory *create_directory_hard_soft
      (const Directory_name &source_directory_name
      ,const Directory_name &target_directory_name
      , bool take_target_directory_name = false)                        const=0;
*/
   Directory_entry_name *render_resolved_shortcut
      (const Directory_entry_name &shortcut_LNK)                     rendition_;
      /**< Takes an directory entry name or shortcut LNK file name
           if it is of a shortcut link the function returns an
           instanciated directory_entry_name that the shortcut points to.
           \returns the resolved directory_entry_name (fully qualified)
              if the passed filename shortcut, otherwise returns 0.
           The caller is responsible for deleting the rendered object.
           The caller should check that the returned value is not 0.
      **/
   Directory_entry_name *render_resolved_shortcut_or_assume_actual
      (const Directory_entry_name &actual_DE_or_shortcut_LNK)        rendition_;
      /**< First attempts to render_resolved_shortcut
           If the filename is actually a directory entry not a short cut,
           or the shortcut could not be resolved, a copy of the passed
           directory entry name is rendered.
           Note that neither the provided name nor the rendered name necessarily
           exists, the caller can call exists() function to check if the
           directory entry actually exists.
           The caller is responsible for deleting the rendered object.
      */
   virtual bool set_current_working_directory(const Directory_name &name) const; //120217
   virtual Directory_entry_name *render_resolved_symbolic_link_or_shortcut
      (const Directory_entry_name &file_name,bool relative)               const;
      // The link to could be either fully qualified or relative (actually partial)
      // relative is recommended when the source and destination
   virtual nat32 get_file_size_bytes(const File_name &file_name)          const; //121108
   virtual CORN::OS::Directory_name   *render_home()                 rendition_; //161025
 protected:
   int invoke(const File_name &file_name,const char *shell_open_mode)     const;
#ifndef _QT_
/* NYI
   virtual bool matches_any_in                                                   //151212
      (const std::wstring &name_with_ext
      ,const CORN::Text_list &wild_card_patterns_to_compare
      ,bool case_insensitive = false)                              affirmation_;
      // Eventually make this public, put in interface, and/or implement as function in CORN::Text_list
*/
#endif
};
//_________________________________________________File_system_engine_Windows__/
extern File_system_engine_Windows file_system_engine_Windows;                    //170412
} } // namespace CORN OS
//______________________________________________________________________________
#define File_system_engine_of_OS File_system_engine_Windows
#endif
