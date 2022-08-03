#include <string.h>
#include "corn/application/project_directory_OS_FS.h"
#include "corn/OS/file_system_engine.h"
#include <fstream>
namespace CORN    {
namespace OS_FS   {
//______________________________________________________________________________
Project_directory::Project_directory
      (const CORN::OS::Directory_entry_name &project_dir_name
      ,bool create_now_if_needed)                                                //130116
: Parameters_directory(project_dir_name,create_now_if_needed)
, projects_directory(0)
{}
//_2012-03-20___________________________________________________________________
const CORN::OS::File_system::Directory &Project_directory::projects() provision_
{  // The projects directory is is almost always the parent
   // I probably should eventually search up the directory tree to
   // find the projects, just in case we don't have a conventional
   // projects/project directory structure   120320


   //140105  WARNING should actually return a pointer because
   // provide_parent_directory could potentially return 0 (I.e. if in root)


   return *provide_parent_directory();
}
//_2012-03-20___________________________________________________________________
bool  Project_directory::set_projects_as_current_working_directory()
{  return OS::file_system_engine.set_current_working_directory(projects());
}
//_2005-05-31___________________________________________________________________
bool Project_directory::is_valid()                                  affirmation_
{  OS::File_name_concrete project_file_name(*this,"project");
   return OS::file_system_engine.exists(project_file_name);
}
//_2012-03-20__2008-11-30_______________________________________________________
Known_projects::Known_projects()
: CORN::Bidirectional_list /*180101 Association_list*/ (true) // unique
{}
//______________________________________________________________________________
uint16 Known_projects::restore(const OS::Directory_name &users_APPLICATION_working_directory) modification_
      // opens the recognized projects save and restore file in the user's working directory
      // and loads the known packages
{  uint16 project_count = 0;
   OS::File_name_concrete known_projects_filename(users_APPLICATION_working_directory,"known.projects");
   if (OS::file_system_engine.exists(known_projects_filename))
   {
      std::ifstream known_projects_file(known_projects_filename.c_str());
      char filename_buffer[1024];
      bool at_eof = known_projects_file.eof() || !known_projects_file.good();       //090814
      while (!at_eof)
      {  known_projects_file >> filename_buffer;
         if (strlen(filename_buffer))
         {  OS::Directory_entry_name_concrete directory_element_name(filename_buffer);           //090814
            if (recognize_context(directory_element_name))
               project_count++;
         }
         at_eof = known_projects_file.eof() || !known_projects_file.good();         //090314
      }
   }
   return project_count;
}
//______________________________________________________________________________
uint16 Known_projects::save(const OS::Directory_name &users_APPLICATION_working_directory) modification_
{  uint16 project_count = 0;
   OS::File_name_concrete  known_projects_filename(users_APPLICATION_working_directory,"known.projects");
   std::ofstream known_projects_file(known_projects_filename.c_str());
   FOR_EACH(known_project,Project_directory ,each_known_project)
   {  
      //180820 known_projects_file << known_project->get_key();
      known_project->write_key(known_projects_file); //180820
      project_count++;
   } FOR_EACH_END(each_known_project)
   return project_count;
}
//______________________________________________________________________________
Project_directory * Known_projects::recognize_context(const OS::Directory_entry_name &directory_element_name) modification_
{  bool parent_dir_as_project_found = false;
   OS::Directory_entry_name &check_dir = const_cast<OS::Directory_entry_name &>(directory_element_name);
   while (!parent_dir_as_project_found)
   {  Project_directory check_project_dir(check_dir,false);                      //100215
      if (check_project_dir.is_valid())
         parent_dir_as_project_found = true;
      else
      {  const CORN::OS::Directory_name *next_check_dir = check_dir.get_path_directory_name();  //140104
         if (! next_check_dir || next_check_dir->is_root())                      //140104
              return 0;// we are at the root drive and no project found
         else
            check_dir = *next_check_dir;
      }
   }
   // at this point we should had found a project directory
   Project_directory *recognized_project_dir
      = create_project_directory(check_dir);                                     //090103
   if (!append(recognized_project_dir))
   {  delete recognized_project_dir; // already in the list
      recognized_project_dir = dynamic_cast<Project_directory *>(find_cstr(check_dir.c_str())); //081220
      // since it is already listed, find and return it.
   }
      // Give any arbitrary directory name traces up the directory_element_name's path
      // until it find a parent directory that is a project
      // and adds that project to the projects list (if not already listed).
      // Returns true if the project has been added to this projects list
      // (Either now or if it was already listed)
      // Returns false if the directory_element_name is not in a project context
      // (I.e. if the path traced up to a root directory

      // This method is typically called at the start of UPSILON element properties editor
      // passing the UPSILON_home_directory (or the fully qualified UPSILON executable filename)
      // For example UPSILON_home_directory  ("C:\UPSILON\program\properties_editor.exe")
      // will add UPSILON_project_directory for "C:\UPSILON" to projects.

      // This method is also typically called by the UPSILON element properties editor
      // for the properties element file being edited, since this
      // will typically be and element within a project and typically
      // that project will be frequently referenced by the element.

      // This method is also called by restore()for each of the 'remembered' projects
      // stored between sessions.

   return recognized_project_dir;                                                //081130
}
//______________________________________________________________________________
} // namespace OS_FS
} // namespace CORN

