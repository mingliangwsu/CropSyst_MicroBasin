#ifndef CS_context_discoveryH
#define CS_context_discoveryH
#include "CS_suite/file_system/CS_context_discovery_common.h"
namespace CS
{
//______________________________________________________________________________
class Context_discovery
: public extends_ Context_discovery_common
{public:
   enum Directory_level
      {arbitrary_level  = 0
      ,scenario_level   = 1
      ,project_level    = 2
      //reserved_level  = 4
      };
   enum Landmark
      {not_landmark
      ,Scenarios_landmark
      ,Output_landmark
      //Database_landmark
      };
   enum Specification
      {unspecified  = 0
      ,primary      = 1 // No parent directiories are of the same context
      ,penultimate  = 2 // All subdiretories are ultimates of this context type
      ,ulimate      = 4 // No further sub directories of this context type

      ,landmark     = 8
      };

      #define file_system_root_level ((primary << 4) | arbitrary_level )
      // Additional processing in needed to identify Ultimate
      // (I.e. counting if there are any subdirectories

   // Directory context code (8 bit)
   // The low nybble is Either Directory level or landmark depending  on
   // the upper bit of the Specification nybble (or bit 7 of the context code)
   // The specifictation is the upper nybble of the directory context code

   CORN::Unidirectional_list leaf_to_root_directory_names;                       //161116
   CORN::Dynamic_array<nat8> leaf_to_root_levels;                                //161116

   mutable CORN::OS::Directory_name   *Scenarios;                                //161116
 public:
      // The root is a top most directory to search for files.
      // Typically this logical root would be either a project directory (super project)
      // the user's home
      // (For both Linux/Unix and Windows ~ is recognized as home)
      // or less likely to root of the file system,
      // or the same as the leaf to limit discovery to one directory
      // The leaf would typically be the CWD.

   Context_discovery();
   Context_discovery                                                                //161102
      (const CORN::OS::Directory_name &leaf_
      ,const CORN::OS::Directory_name *root_ = 0);
      // In this case, the leaf is not necessarily the CWD
      // and the root may be known

//   bool know_root(const CORN::OS::Directory_name *root_)             cognition_;
      // passing 0 will set the root to the primary project
      // (or user's home or file system root) which ever is found first
//   bool take_leaf(CORN::OS::Directory_name *leaf_);
//   bool take_root(CORN::OS::Directory_name *root_);
/* check reimplement
   CORN::OS::Directory_name *find_level
      (Directory_level level
      ,const CORN::OS::Directory_name *from_directory = 0)           rendition_;
*/
   CORN::OS::Directory_name *provide_Scenarios()                     provision_; //161116
/*currently only in File_discovery
   CORN::OS::Directory_name *                                                    //160301
      set_level_as_root(Directory_level level)                       rendition_; //160301
*/
      // finds the uppermost specified level searching from the leaf.
      // If such a level is found, it is set at the root.
      // Normally this is called once to replaced the root of the file system
      // with a directory that is expected to be the upper most
      // directory identified as the root for the application.
      // Typically this would be the user's home directory.
/* check reimplement
   bool is_level
      (const CORN::OS::Directory_name &directory
      ,Directory_level level)                                      affirmation_;
      /// \return true if the specified directory is such a level
*/


};
//_2015-12-06___________________________________________________________________
}
#endif
