#ifndef USE_OS_FS
#ifndef suite_directoryH
#define suite_directoryH
#include "corn/application/documentation_directory.h"
namespace CORN {
   /// Suite: a suite of applications where the seperate applications
   /// share some common directories for example DLLs or common help.
//______________________________________________________________________________
class Suite_directory
: public Smart_directory_name
{
 protected:
   Ustring  documentation_name; // Documentation common to all applications in the suite
   Ustring  manual_name;
   Ustring  icons_name;
   provided_ Documentation_directory    *documentation_directory; // Documentation common to all applications in the suite
   provided_ Smart_directory_name *common_directory;                             //101114
   provided_ Smart_directory_name *manual_directory;
   provided_ Smart_directory_name *icons_directory;
   provided_ File_name            *install_or_update_filename;                   //120112
   CORN::Smart_file_name           current_program;
 public:
   Suite_directory
      (const Directory_name &directory_name
      ,const char *prefered_documentation_dir_name = "Documentation"
      ,const char *prefered_manual_dir_name        = "Manual"
      ,const char *prefered_icons_dir_name         = "Icons");
   Suite_directory
      (const char *prefered_documentation_dir_name = "Documentation"
      ,const char *prefered_manual_dir_name        = "Manual"
      ,const char *prefered_icons_dir_name         = "Icons");
   // Use this constructor when we have a fully qualified filename (typically a program in any subdirectory of the suite);
   // You must then call setup_from_initiating_program(const char *initiating_program);
   bool setup_from_subdirectory_entry(const CORN::Directory_entry_name &directory_entry_name);
      // Returns true if the Suite directory was found as some directory up the path of initiating_program.
   void know_initiating_program(const char *initiating_program);
   inline virtual bool is_valid()                                          const { return true; }
      ///< Derived classes must reimplement is_valid()
      /// This method is often used to determine if a directory is
      /// a suite directory.
      /// Various methods may be employed to signal a suite directory
      /// I.e. the directory may have 'suite' as part of the directory name
      /// or there may be a 'magic' file in the directory
      /// or one or more files or directories with a recognizable name.
      /// \return true if the
 public: // Smart_directory_name reimplementations
      ///< Derived classes should call this.
   virtual void reset()                                                provision_; // provides because only modifies provided contributes;
 public: // Fluent interface
   Documentation_directory    &documentation()                         provision_;
   Smart_directory_name &manual()                                      provision_;
   Smart_directory_name &icons()                                       provision_;
   Smart_directory_name &common()                                      provision_;
   File_name  &install_or_update()                                     provision_;//120112
      ///< Provides the same of a program that is used to install or update the application suite programs;
 public:
   virtual const File_name &qualify_icon_filename
      (const char *icon_filename_unqualified
         ///< This is the name of an icon file that is expected to be in the icons directory
      ,Smart_file_name &icon_filename_qualified)                           const;
      ///< Derived classes are not expected to reimplement this method,
      ///  But may have a different directory to store icons.
};
//______________________________________________________________________________
} // namespace CORN

#endif
#endif
