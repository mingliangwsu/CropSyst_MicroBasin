#include "CS_suite/file_system/CS_file_discovery.h"
#include "corn/data_source/vv_file.h"
#include "corn/OS/file_system_engine.h"
#include "corn/container/bilist.h"
#include "corn/container/text_list.h"
#include "common/geodesy/geolocation.h"
#include "corn/seclusion.h"
namespace CS
{
//______________________________________________________________________________


/* conceptual
File_discovery::File_discovery
(directory_level leaf_
,directory_level root_)
{

      // The root is a top most directory to search for files.
      // Typically this logical root would be either a project directory (super project)
      // the user's home
      // (For both Linux/Unix and Windows ~ is recognized as home)
      // or less likely to root of the file system,
      // or the same as the leaf to limit discovery to one directory
      // The leaf would typically be the CWD.


   continue here
}
*/
//_2015-12-06_____________________________________________________constructor__/
/*NYN
File_discovery::File_discovery
(const CORN::OS::Directory_name &leaf_
,const CORN::OS::Directory_name &root_)
: leaf(leaf_)
, root(root_)
{
}
*/
//_2015-12-06___________________________________________________________________
File_discovery::File_discovery()
: Context_discovery_common()
{
   root = find_level(file_system_root_level,leaf);
   // root_level currently always going to be the root of the drive.
}
//_2015-12-06___________________________________________________________________
File_discovery::File_discovery
(const CORN::OS::Directory_name &leaf_
,const CORN::OS::Directory_name *root_)
: Context_discovery_common(leaf_,root_)
/*moved
: leaf(const_cast<CORN::OS::Directory_name *>(&leaf_)),leaf_owned(false)
, root(const_cast<CORN::OS::Directory_name *>(root_)),root_owned(false)
*/
{
   if (!root_)
   {  root = find_level(file_system_root_level,leaf);
      root_owned = true;
   }
   // root_level currently always going to be the root of the drive.
}
//_2016-11-02___________________________________________________________________
CORN::OS::Directory_name * File_discovery::find_level
(Directory_level level
,const CORN::OS::Directory_name *from_directory)                      rendition_
{
   CORN::OS::Directory_name *found_level_rendered = 0;
   if (from_directory->is_root())
   {  found_level_rendered =
       (level == file_system_root_level)
         ? new CORN::OS::Directory_name_concrete(*from_directory)
         : 0; // we are at the root so the level was not found;
   } else
   {  found_level_rendered = find_level                                          //160307
         (level,from_directory->get_path_directory_name());
      if (!found_level_rendered)
      {
         if (is_level(*from_directory,level))
            found_level_rendered = new CORN::OS::Directory_name_concrete(*from_directory);
         else // recurse
         {  const CORN::OS::Directory_name *parent = from_directory->get_path_directory_name();
            found_level_rendered = (parent)
               ? find_level(level,parent)
               : 0;
         }
      }
   }
   return found_level_rendered;
}
//_2015-12-08___________________________________________________________________
CORN::OS::Directory_name *File_discovery::set_level_as_root(Directory_level level) rendition_
{
   CORN::OS::Directory_name *found_level_rendered = find_level(level,leaf);
   if (found_level_rendered)
      know_root(found_level_rendered);
   return found_level_rendered;
}
//_2015-12-08___________________________________________________________________
/*160301 RLN
bool File_discovery::set_level_as_root(Directory_level level)         rendition_
{  bool was_set = false;
   CORN::OS::Directory_name *found_level_rendered = find_level(level,leaf);
   if (found_level_rendered)
      was_set = take_root(found_level_rendered);
   if (!was_set)
      delete found_level_rendered;
   return was_set;
}
//_2015-12-08___________________________________________________________________
*/
bool File_discovery::is_level
(const CORN::OS::Directory_name &directory
,Directory_level level)                                             affirmation_
{  bool it_is
   =  ((directory.is_root()) && (level == file_system_root_level))
   || ((directory.get_name() == L"Scenarios") && (level == scenarios_level));
   if (!it_is && (level == project_level))
   {  // Check if this is project
      CORN::OS::File_name_concrete project_file(directory,".CS_project");
      it_is = CORN::OS::file_system_engine.exists(project_file) ;
      if (!it_is)                                                                //160307
      {  CORN::OS::Directory_name_concrete database_dir(directory,"Database");   //160307
         it_is = CORN::OS::file_system_engine.exists(database_dir);              //160307
      }
   }
   if (!it_is && (level == scenario_level))
   {
      CORN::OS::File_name_concrete scenario_file(directory,".CropSyst_scenario");
      it_is = CORN::OS::file_system_engine.exists(scenario_file);
   }
   return it_is;
}
//_2015-12-08___________________________________________________________________
} // namespace CS

