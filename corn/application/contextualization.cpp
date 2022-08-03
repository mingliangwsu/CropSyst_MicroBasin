#include "corn/application/contextualization.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/file_system_engine.h"
#include "corn/data_source/VV_file.h"
namespace CORN {
//______________________________________________________________________________
bool Directory_record::expect_structure(bool for_write)
{  bool valid = CORN::Data_record::expect_structure(for_write);
   expect_string("context",context);
   return valid;
}
//_expect_structure_________________________________________________2017-12-31_/
Contextualization::Contextualization()
: active_directory                     (new CORN::OS::Directory_name_concrete()) //180731
, directory_record                                                           (0) //171230
{}
//_Contextualization::constructor_______________________________________________
Contextualization::~Contextualization()
{
   delete active_directory;
   delete directory_record;
}
//_Contextualization::destructor________________________________________________
Directory_record *Contextualization::provide_directory_context() provision_
{
   if (!directory_record)
   {
      directory_record = new Directory_record;
      CORN::OS::File_name_concrete directory_filename
         (get_active_directory()/*180723 get_directory_name_qualified()*/,".directory");
      CORN::VV_File directory_file(directory_filename.c_str());
      directory_file.get(*directory_record);
      if (directory_record->context.empty())
      {  // This file is probably new so set the context if already specified
   // By default assume the CWD is a landmark directory.
   // Derived classes may override this to do more definitive evaluation.
         get_specified_context(directory_record->context);
      }
   }
   return directory_record;
}
//_provide_directory_context________________________________________2017-12-31_/
bool Contextualization::is_within
(const char                      *monument
,const CORN::OS::Directory_name  *specified_dir)                    affirmation_
{
   const CORN::OS::Directory_name &dir = (specified_dir != NULL)
      ? *specified_dir
      : get_active_directory()/*180723 get_directory_name_qualified()*/;
   std::wstring monument_wstring; CORN::ASCIIZ_to_wstring(monument,monument_wstring);
   bool within = dir.get_name() == monument_wstring;
   return within;
   /* Currently assuming landmarks are identified by directory naming
      but may need to superrecursively check for content specification
   */
   /*NYI
      eventually look for context information
   */
}
//_is_within_______________________________________________________2018-03-30__/
bool Contextualization::is_beneath
(const char                      *monument
,const CORN::OS::Directory_name  *specified_dir)                    affirmation_
{
   const CORN::OS::Directory_name &dir = (specified_dir != NULL)
      ? *specified_dir : get_active_directory();

//std::wstring debug(dir.w_str());
//std::clog <<  debug.c_str() << std::endl;
   bool beneath = dir.has_in_path_cstr(monument,CORN::OS::Directory_entry_name::include_all/*180407 _except_extension*/);
      //180407 Output  (actually any mounument)
      // can now be in extension (i.e. backup directory may be named {date}.Output)
   return beneath;
   /* Currently assuming landmarks are identified by directory naming
      but may need to superrecursively check for content specification
   */
   /*NYI
      eventually look for context information
   */
}
//_is_beneath_______________________________________________________2017-12-27_/
bool Contextualization::is_underneath
(const char                      *monument
,const CORN::OS::Directory_name  *specified_dir)                    affirmation_
{
   const CORN::OS::Directory_name &dir
      = (specified_dir == NULL)
         ? *specified_dir : get_active_directory();
   std::string context_ID; get_specified_context(context_ID);
   return (context_ID != monument)
       && is_beneath(monument,&dir);
   /* Currently assuming landmarks are identified by directory naming
      but may need to superrecursively check for content specification
   */

   /*NYI
      eventually look for context information
   */
}
//_is_underneath____________________________________________________2017-12-27_/
bool Contextualization::has_monument
(const char                      *monument // could be pattern
,const CORN::OS::Directory_name  *specified_dir)                    affirmation_
{  bool monument_exists = false;
   const CORN::OS::Directory_name &dir
      = (specified_dir == NULL)
         ? get_active_directory()/*180723 get_directory_name_qualified()*/
         : *specified_dir;
   std::wstring monument_wide; CORN::ASCIIZ_to_wstring(monument,monument_wide);
   CORN::OS::Directory_entry_name *monument_dir
      = CORN::OS::file_system_engine.find_DEN
      (monument_wide
      ,CORN::OS::directory_entry
      ,dir
      ,CORN::OS::File_system::none_recursion_inclusive
      /*
      ,0
      ,FILENAME_CASE_INSENSITIVITY   may want this to be case sensitive
      */
      );
   if (monument_dir)
   {  monument_exists = true;
      delete monument_dir;
   }
   return monument_exists;
}
//_has_monument_____________________________________________________2017-12-27_/
bool Contextualization::directory_context_save(bool if_modified) stream_IO_
{
   bool written = false;
   if (directory_record && directory_record->is_modified())
   {
      CORN::OS::File_name_concrete directory_filename
         (get_active_directory()/*180723 get_directory_name_qualified()*/,".directory");
      CORN::VV_File directory_file(directory_filename.c_str());
      written = directory_file.set(*directory_record);
   }
   return written;
}
//_directory_context_save___________________________________________2017-12-31_/
bool Contextualization::get_specified_context(std::string &context) const
{  // derived class will typically override
   CORN::wstring_to_string(get_active_directory()/*180723 get_directory_name_qualified()*/.get_name(),context);
   return true;
}
//_get_specified_context____________________________________________2017-12-31_/
bool Contextualization::change_active_directory
(const wchar_t *directory_name_fully_qualified)
{
   directory_context_save();                         //180723_171231
   delete active_directory;
   active_directory = new
      CORN::OS::Directory_name_concrete(directory_name_fully_qualified);

/* Not currently done (Explorer_engine_abstract currently handles this)
   if (user_settings && application_data_directory)                              //141020
   {  CORN::UnicodeZ_to_string
         (active_directory
         ,user_settings->most_recent_context_directory);
      application_data_directory->save_user_settings(*user_settings);
   }
*/
   CORN::OS::file_system_engine.provide_directory(*active_directory);
   CORN::OS::file_system_engine.set_current_working_directory(*active_directory);
   return true;
}
//_change_active_directory__________________________________________2014-10-20_/
bool Contextualization::change_active_directory(const CORN::OS::Directory_name &directory_name)
{  return change_active_directory(directory_name.c_str());
}
//_change_active_directory__________________________________________2014-10-20_/
bool Contextualization::change_active_directory(const char *directory_name_fully_qualified)
{  std::wstring directory_name_fully_qualified_wstr;
   CORN::ASCIIZ_to_wstring(directory_name_fully_qualified,directory_name_fully_qualified_wstr);
   return change_active_directory(directory_name_fully_qualified_wstr.c_str());

}
//_change_active_directory__________________________________________2014-10-20_/

//______________________________________________________________________________
} // namespace CORN

