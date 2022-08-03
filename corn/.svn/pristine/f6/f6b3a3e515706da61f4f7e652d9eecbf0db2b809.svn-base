#ifndef parameters_directory_OS_FSH
#define parameters_directory_OS_FSH

#  include "corn/parameters/parameters_types.h"

// A parameters directory is a directory that may be associated with a parameter file.
// It will have the same name as the associated parameter file without the extension.
// It may have an optional notes.txt file and an optional backup file

/*
Common_parameters_directory is a directory which is associated with
parameters (usually the parameters are stored in a file, but this does
does not need to be the case, for example the directory could be associated
with a record in a database table.

When associated with a file it may have two forms:
1. The parameter file may have this parameter directory with the same name
   in which additional related files are store.
   This mode is used when the associated directory is optional.
   The associated directory may be optional in cases where the
   may or may not be additional files associated with the parameter file.

2. The parameter file may be stored with in the directory.
   That is the parameter directory is the parent of the parameter file.
   Usually, in this case, the parameter file will have some fixed filename
   (not  necessarily the same name of the parameter directory)
   since the directory specifies the name of the file.
   This mode is used when there will always be additional files.
   I.e. a project directory.           __cplusplus
*/
#include "corn/OS/file_system_logical.h"
#include "corn/OS/file_system_engine.h"
namespace CORN {
namespace OS_FS   {
class Common_project_directory;
//______________________________________________________________________________

class Parameters_directory          // Abstract
: public CORN::OS::File_system_logical::Directory
{
 protected:
   provided_ CORN::OS::File_name_concrete *associated_filename_;
   provided_ CORN::OS::File_name          *details_filename;
   provided_ CORN::OS::File_name          *status_filename;
   provided_ CORN::OS::File_name          *notes_filename;
   provided_ CORN::OS::File_name          *explaination_filename;
 public: // structors
   Parameters_directory
      (const CORN::OS::Directory_entry_name &parameters_directory_entry_name
      ,bool create_now_if_needed);                                               //130116
   Parameters_directory                                                          //130831
      (const CORN::OS::Directory_entry_name &parameters_directory_entry_name
      ,CORN::OS::File_system::Directory_entry::Type type
      ,bool create_now_if_needed);                                               //130116
   virtual ~Parameters_directory();                                              //130215
public:
   virtual const wchar_t *get_associated_file_extension()                  const { return L""; }//120326
   virtual const CORN::OS::File_name &associated_filename()           provision_;//120320
      // Derived classes may override associated_filename()
      // if they will have an associated filename.
      // May return empty filename if there is no associated filename.
      // This is replacing get_associated_filename().
      ///^ The associated_filename is the name of a file that 'goes with' this directory.    //090222
      ///  NULL indicates there is no associated file.                                       //090222
      ///  The filename may either be own and maintained by this                             //090222
      ///  or owned by the caller in which case this only references the associated filename.//090222
#ifdef NYI
   Associated_directory_mode associated_directory_mode;                          //060618
   // continue here reimplement the various methods Common_parameters_directory
   // as needed.
 protected: //  Return buffers for general use when returning filenames and directories      //041018
   CORN::Smart_file_name      mutable filename_return_buffer;                    //041018
   CORN::Smart_directory_name mutable dirname_return_buffer;                     //041018
 public:
   Common_parameters_directory                                                   //060614
      (CORN::Smart_file_name *associated_parameters_filename                     //090830
      ,bool take_filename                                                        //090830
      ,Associated_directory_mode _associated_directory_mode/* = NO_ASSOCIATED_DIRECTORY  */ //060614
      ,bool        create_now /*100729 = false */                  // if associated_parameters_filename!=0 then we may need to create the directory //060614
      );                                                                         //060614
   // Use this constructor when we know the associated filename                  //070717
   Common_parameters_directory                                                   //070717
      (const CORN::Directory_name &_directory_name   // associated_parameters_filename = 0 implies the current working directory to be the parameters directory (it already exists) //070717
      ,Associated_directory_mode _associated_directory_mode/* = NO_ASSOCIATED_DIRECTORY   */  //070717
      ,bool        create_now /*100729 = false   */                              //070717
      );                                                                                                                                                                                        //070717
   // Use this constructor when we are given the directory                                                                                                                                      //070717
   // if associated_parameters_filename!=0 then we may need to create the directory
   virtual ~Common_parameters_directory();                                                                                                                                                      //090222
   void initialize(bool create_now);                                                                                                                                                            //070717
 public:
#endif
   CORN::OS::File_name *render_filename                                          //120323
      (const wchar_t         *unqualified_filename_with_extension)    rendition_;
#ifdef NYI
   // The following methods return fully qualified filenames (with extention) commonly found in parameters directories
   // The return_filename parameter is a return buffer for the composed filename.
   // if check_existance is true, the method will check if the file exists in directory/
   // The methods return true if the check for existence did find the file in the directory.
   // Derived classes may override these methods to change the default filename and/or extension

          virtual bool get_backup_filename                                       //090222
      (CORN::Smart_file_name &return_filename
      ,bool check_existence = false)                                       const;
   inline virtual bool get_notes_filename                                        //090222
      (CORN::Smart_file_name &return_filename
      ,bool check_existence = false)                                       const { return get_filename("notes.txt",return_filename,check_existence); }
#endif
   virtual const CORN::OS::File_name &details()                       provision_;
   virtual const CORN::OS::File_name &status()                        provision_;
   virtual const CORN::OS::File_name &notes()                         provision_;
   virtual const CORN::OS::File_name &explaination()                  provision_;
      // replaces get_details_filename
#ifdef NYI
   // continue here reimplement the various methods Common_parameters_directory
   // as needed.

   CORN::Smart_directory_name &get_qualified()                             const;//050324
   inline virtual bool purge_output()                              rectification_{ return true;}  //050325
   // This deletes all output files from the directory path output.
   // Returns true if successful (usually the case);
   // Derived classes may override to remove/clean up generated files.
#endif
   inline virtual const CORN::OS::File_name_concrete &get_folder_icon_filename(CORN::OS::File_name_concrete &icon_filename,int &icon_index) const { icon_index = 0; return icon_filename;} //130215_060614
   // Derived class may provide this method to give the directory a special icon.
   // If this method is not overridden, no desktop.ini file will be created in this folder so no icon will be assigned.
   // Return name of an icon (.ICO) file
   // icon index is set to the icon index if there are multiple icons in the icon file (use 0 if just one icon).
   // Normally this will have a fully qualified path to a shared/common icon file included in an application's distribution.
   // If the icon file is stored in the directory, it should be unqualified.
   inline virtual const char *get_infotip()                                const { return 0; } //060614
   // Derived class may provide this method to give the directory desktop.ini file in infotip
   // which is displayed in Windows explorer  (web view mode or when mouse hovers).
#ifdef NYI
   // continue here reimplement the various methods Common_parameters_directory
   // as needed.
   virtual bool matches_associated_file(const char *file_name)       affirmation_;//060710
   // Return true is the specified filename has the same path and name as this directory.
   // This is used in parameter file editors when the filename may be changed
   // and then it is necessary to check if (this) associated directory is the same.
   virtual bool get_project_directory                                            //100310
      (CORN::Common_project_directory &project_directory);
   /**< For all CropSyst V4 simulation models, the project directory is always two directories
       up in the from the scenario_directory path.
       Other models may have another project directory structure
       so may need to override this method.
       Recursively searches up the directory tree until
       a valid project directory is found.
       \return true if a project directory is found up the path
          project_directory will be set to the directory name
   **/

public:
   const CORN::Smart_file_name &get_filename(bool fully_qualified,const CORN::Smart_file_name &filename,const CORN::Smart_directory_name &qualifaction_dir) mutates_;   //041030_
   // This is used to compose a filename in a parameter directory subdirectory
   // I.e.   If this is a CropSyst project directory and you want to compose a scenario filename
   // the qualification_dir would be "Scenarios".
   // Note: this may be obsolete or may be made obsolete with
   // the new get_filename method                                                //090222
#endif
public:
   void write_desktop_ini();                                                     //060614
};
//_2012-02-02_____________________________________________________________________________
} // namespace OS_FS
} // namespace CORN
#endif

