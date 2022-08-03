#include "directory_entry_name_concrete.h"
#include "corn/OS/file_system_engine.h"
#include "corn/string/strconv.hpp"
#include "corn/container/text_list.h"
#include "directory_entry_name.h"
#include <assert.h>
#if ((__BCPLUSPLUS__ > 0) && (__BCPLUSPLUS__ <= 0x0550))
#include <system.hpp>
#endif

using namespace std;
//_____________________________________________________________________________/
namespace CORN { namespace OS {
//_____________________________________________________________________________/
void Directory_entry_name_concrete::decompose()                    contribution_
{
   clear_decomposition();
   get_path_directory_name();                                                    //131119
   Directory_entry_name_abstract::decompose();                                   //120327
}
//_2011-03-08_______________________________________________________decompose__/
void Directory_entry_name_concrete::construction_compose()         construction_
{  Directory_entry_name_concrete *this_modifiable = const_cast<Directory_entry_name_concrete *>(this);
   const CORN::OS::Directory_name *path_directory_name = get_path_directory_name();
   if (path_directory_name)
   {  std::wstring apparent_preferred_directory_separator;                       //120824
      // we will assume the composed qualified name will have the same
      // directory separator as the parent directory
      path_directory_name->append_separator_to(apparent_preferred_directory_separator);//120824
      this_modifiable->insert(0,apparent_preferred_directory_separator.c_str()); //120824
      this_modifiable->insert(0,path_directory_name->w_str());
   }
}
//_2012-02-10___________________________________________________________________
void Directory_entry_name_concrete::clear_decomposition()         contribution_
{  delete qualified_path_provided;  qualified_path_provided = 0;
   root = false;                                                                 //160126
}
//_2011-03-08_____________________________________________clear_decomposition__/
const char *Directory_entry_name_concrete::c_str()                         const
{  CORN::wstring_to_string(*this,return_buffer_ASCII);
   return return_buffer_ASCII.c_str();
}
//_______________________________________________________________________c_str_/
const wchar_t *Directory_entry_name_concrete::w_str()                      const
{  return std::wstring::c_str();
}
//_2012-02-09____________________________________________________________w_str_/
const std::wstring &Directory_entry_name_concrete::append_components_to
(std::wstring &buffer
,Path_inclusion inclusion
,wchar_t preferred_path_separator                                                //140202
,bool append_trailing_directory_separator)                                 const
{  return Directory_entry_name_abstract::append_components_to
      (buffer,inclusion,preferred_path_separator,append_trailing_directory_separator);
}
//________________________________________________________append_components_to_/
bool Directory_entry_name_concrete::has_relative_path()             affirmation_
{
   bool has_rel_path
      =  has_in_path_cstr("..",include_path_designated,false)
      || has_in_path_cstr("." ,include_path_designated,false);
   return has_rel_path;
}
//_2012-04-30___________________________________________________________________
bool Directory_entry_name_concrete::is_extension_ASCII
(const_ASCIIZ valid_ext,bool case_insensitive) affirmation_
{  if (!extension.length())                                                      //131120
      decompose();                                                               //110307
   return Directory_entry_name_abstract::has_extension_ASCII(valid_ext, case_insensitive); //170224_120206
}
//_1999-07-26_______________________________________________is_extension_ASCII_/
const std::wstring &Directory_entry_name_concrete::get_name()              const
{  if (!name.length())                                                           //121130
      decompose();                                                               //110307
   return Directory_entry_name_abstract::get_name();                             //120226
}
//_2005-02-07________________________________________________________get_name__/
const std::wstring &Directory_entry_name_concrete::get_extension()         const
{  if (!extension.length()) decompose();                                         //131120
   return Directory_entry_name_abstract::get_extension();                        //120206
}
//_2005-02-07___________________________________________________get_extension__/
const CORN::OS::Directory_name &Directory_entry_name_concrete
::get_parent_directory_name_qualified()                                    const
{  return *get_path_directory_name();
}
//_2009-09-24______________________________get_parent_directory_name_qualified_/
const CORN::OS::Directory_name *Directory_entry_name_concrete::get_path_directory_name() const
{  if (!qualified_path_provided)
   {  size_t rightmost_dir_sep_pos = find_right_most_directory_separator_pos();
      if (rightmost_dir_sep_pos == std::string::npos)                            //140104
      {  if ((name == L"..") || (name==L".")
             || is_root()                                                        //140313
            )
            qualified_path_provided = 0;
             // This is the uppermost relative path
         else
         {  std::wstring path(*this,0, 0);
            if (path.length())                                                   //140121
               qualified_path_provided = new Directory_name_concrete(path);
         }
      } else
      {  std::wstring path(*this,0,rightmost_dir_sep_pos);
         qualified_path_provided = new Directory_name_concrete(path);
         // We need to instanciate all the paths up the directory tree           //160126
         //qualified_path->get_path_directory_name();                            //160126
      }
   }
   return qualified_path_provided;
}
//_2012-02-06__________________________________________get_path_directory_name_/
Directory_entry_name_concrete::Directory_entry_name_concrete()
: Directory_entry_name_abstract(L"",unknown_entry)
,qualified_path_provided(0)
{  Directory_name *curr_dir = file_system_engine.render_current_working_directory();
   set_DEN(*curr_dir);                                                           //121121
   identified_type = directory_entry;                                            //160812
   delete curr_dir;
}
//_2012-03-20______________________________________________________________________/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Drive_designator &drive_designator)
: Directory_entry_name_abstract(L"",directory_entry)
,qualified_path_provided(0)
{  Directory_name *curr_dir = file_system_engine.render_current_working_directory_on_drive(drive_designator);
   set_DEN(*curr_dir);                                                           //121121
   identified_type = directory_entry;                                            //161029
   delete curr_dir;
}
//_2012-04-30___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete
(const char *raw_name
,Directory_entry_type type)
:Directory_entry_name_abstract(raw_name,type)
,qualified_path_provided(0)
{}
//_________________________________________________________________constructor_/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const wchar_t *raw_name
,Directory_entry_type type)
:Directory_entry_name_abstract(raw_name,type)
,qualified_path_provided(0)
{}
//_2012-02-02______________________________________________________constructor_/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const std::wstring &raw_name
,Directory_entry_type type)
:Directory_entry_name_abstract(raw_name,type)
,qualified_path_provided(0)
{}
//___________________________________________________________Copy constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const std::wstring *raw_name
,Directory_entry_type type)
:Directory_entry_name_abstract(*raw_name,type)
,qualified_path_provided(0)
{}
//_2012-03-09________________________________________________Copy constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const std::string *raw_name
,Directory_entry_type type)
:Directory_entry_name_abstract(*raw_name,type)
,qualified_path_provided(0)
{}
//_2012-03-09________________________________________________Copy constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const std::string &raw_name
,Directory_entry_type type)
:Directory_entry_name_abstract(raw_name,type)
,qualified_path_provided(0)
{}
//_2012-03-25________________________________________________Copy constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_entry_name &copy_from
,Path_inclusion inclusion)
   :Directory_entry_name_abstract
   (copy_from.get_components
      (inclusion
      ,copy_from.get_separator())                                                //140202
   ,(((inclusion&include_name_extension) == include_name_extension)
      ? copy_from.get_type() : directory_entry))                                 //131120
,qualified_path_provided(0) // provided as needed
{
   preferred_separator = copy_from.get_separator();                              //140202

   // warning, need to set the type

   setup_is_root();
}
//___________________________________________________________Copy constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_entry_name &raw_name
,const Extension &extension
,Directory_entry_type type)
:Directory_entry_name_abstract(raw_name,extension,type)
,qualified_path_provided(get_path_directory_name() ?
                     new Directory_entry_name_concrete
                        (*raw_name.get_path_directory_name())  : 0)              //131011
{}
//_2012-03-21__________________________________________________________________/
Directory_entry_name_concrete::Directory_entry_name_concrete
(nat16 CSIDL
,const std::wstring &_name
,const std::wstring &_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(/*CSIDL,*/_name,_extension,type)
{  Directory_name *CSIDL_dir = file_system_engine.render_CSIDL_directory_name(CSIDL); //100101
   qualified_path_provided = CSIDL_dir;
   construction_compose();
}
//_2009-11-11______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory,const std::wstring &_name_and_ext
,Directory_entry_type type)
:Directory_entry_name_abstract(_name_and_ext,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory.w_str(),CORN::OS::directory_entry))
{  construction_compose();
}
//_2009-11-07______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory,const std::string &_name_and_ext
,Directory_entry_type type)
:Directory_entry_name_abstract(_name_and_ext,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory.c_str(),CORN::OS::directory_entry))
{  construction_compose();
}
//_2012-03-26______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory,const char *_name_and_ext
,Directory_entry_type type)
:Directory_entry_name_abstract(_name_and_ext,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory.c_str(),CORN::OS::directory_entry))
{  construction_compose();
}
//_2009-11-07______________________________________Directory_name:constructor__/
#ifndef DIRECTORY_ENTRY_IS_A_NAME
Directory_entry_name_concrete::Directory_entry_name_concrete
(const File_system::Directory &_path_directory,const std::wstring &_name,const std::wstring &_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory.c_str(),CORN::OS::directory_entry))
,name       (new std::wstring(_name))
,extension  (new std::wstring(_extension))
,root       (false)  // If there is a path, then this cannot be a root
{  construction_compose();
}
//_2009-11-07______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const File_system::Directory &_path_directory,const std::string &_name
,Directory_entry_type type)
:Directory_entry_name_abstract(type)
,qualified_path(new Directory_entry_name_concrete(_path_directory.c_str()))
,name       (new std::wstring(_name))
,extension  (new std::wstring(""))
,root       (false)  // If there is a path then this cannot be a root
{  compose_from_path_name_ext();
}
#endif
//_2009-11-07_____________________________________________________constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory_name,const std::wstring &_name,const std::wstring &_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name,_extension,type)
,qualified_path_provided(0)                                                      //170111
{  qualified_path_provided = new Directory_entry_name_concrete                   //170111
      (_path_directory_name.c_str(),CORN::OS::directory_entry);
   construction_compose();
}
//__2009-11-07_____________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory_name,const wchar_t *_name,const wchar_t *_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name,_extension,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str(),CORN::OS::directory_entry))
{  construction_compose();
}
//_2009-11-07______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(Directory_name *path_directory_name_given,const char *_name,const char *_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name,_extension,type)
,qualified_path_provided(path_directory_name_given)
{  construction_compose();
}
//_2009-11-07______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory_name
,const char *_name
,const char *_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name,_extension,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str()))
{  construction_compose();
}
//_2012-05-18___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory_name
,const std::string &_name
,const char *_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name.c_str(),_extension,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str()))
{  construction_compose();
}
//_2013-09-05___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete                     //130905
      (const Directory_name &_path_directory_name
      ,const char *_name
      ,const std::wstring &_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name,_extension,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str()))
{  construction_compose();
}
//_2013-09-05___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete                     //130905
(const Directory_name &_path_directory_name
,const std::string &_name
,const std::wstring &_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name.c_str(),_extension,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str()))
{  construction_compose();
}
//_2013-09-05___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory
,const wchar_t *_name_and_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name_and_extension,type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory.c_str()))
{  construction_compose();
}
//_2012-03-24______________________________________Directory_name:constructor__/
Directory_entry_name_concrete::Directory_entry_name_concrete
(const Directory_name &_path_directory_name
,const std::wstring &_name
,const char *_extension
,Directory_entry_type type)
:Directory_entry_name_abstract(_name,Extension(_extension),type)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str()))
{  construction_compose();
}
//_2012-11-26___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete                     //130207
(const Directory_name &_path_directory_name
,const File_name      &_file_name)
:Directory_entry_name_abstract(_file_name,include_name_extension,file_entry)
,qualified_path_provided(new Directory_entry_name_concrete(_path_directory_name.c_str()))
{  construction_compose();
}
//_2013-03-10___________________________________________________________________
Directory_entry_name_concrete::Directory_entry_name_concrete
(const CORN::Text_list &orignial_decomposed_name
,Path_inclusion decomposed_name_includes
,Path_inclusion inclusion)
: Directory_entry_name_abstract()
,qualified_path_provided(0)
{  CORN::Text_list decomposed_name(orignial_decomposed_name);                     //170421
   if (decomposed_name_includes & include_extension)
   {  CORN::Item *ext_item = dynamic_cast<CORN::Item *>                          //180119
      (decomposed_name.pop_at_tail());
      if (ext_item && (inclusion & include_extension))
      {  extension.clear();
         ext_item->append_to_wstring(extension);                                 //180115
      }
      delete ext_item;
   }
   CORN::Item *designator_item = 0;
   if ((decomposed_name_includes & include_designator )
         && orignial_decomposed_name.count()==1)
   {  designator_item =
         dynamic_cast<CORN::Item *>
         (decomposed_name.pop_at_head());
      if (designator_item)
      {
         std::string designator; designator_item->append_to_string(designator);
         if (designator.find(":") == std::string::npos)
         {  // The entry isn't a designator so put it back
            decomposed_name.prepend(designator_item);
            designator_item = 0;
         }
      }
   }
   if (decomposed_name_includes & include_name)
   {  CORN::Item *name_item = dynamic_cast<CORN::Item *>
         (decomposed_name.pop_at_tail());
      if (name_item && (inclusion & include_name))
         name_item->append_to_wstring(name);                                     //180115_131120
      delete name_item;
   }
/*
   CORN::Text_list::Item *designator_item = 0;
   if (decomposed_name_includes & include_designator)
   {  designator_item = dynamic_cast<CORN::Text_list::Item *>(decomposed_name.pop_at_head());
      if (designator_item && (designator_item->find(":") == std::string::npos))
      {  // The entry isn't a designator so put it back
         decomposed_name.prepend(designator_item);
         designator_item = 0;
      }
   }
*/
   CORN::Item *parent = dynamic_cast<CORN::Item *>
      (decomposed_name.pop_at_tail());
   if (!(inclusion & include_ancestors_path))
      decomposed_name.delete_all();
   if (parent && (inclusion & include_parent))
      decomposed_name.append(parent);
   else delete parent;
   nat8 decomposed_name_count = decomposed_name.count();
   bool from_root = false;
   if (decomposed_name_count)
   {
      qualified_path_provided = new  CORN::OS::Directory_entry_name_concrete
         (decomposed_name,CORN::OS::Directory_entry_name::include_all_except_extension);
   } else from_root = true;
   //Warning, currently text_list is only std::string
   //
   std::string qualified_name_ASCII;
   if (designator_item)
   {
      designator_item->append_to_string(qualified_name_ASCII);                   //180115
   }
   else // we need to include the root                                           //171130
      #ifdef __linux__
         qualified_name_ASCII += '/';                                            //171130
      #endif
         // For Linux prepend root /
   if (decomposed_name.count())
   {  decomposed_name.string_items(qualified_name_ASCII,DEFAULT_DIRECTORY_SEPARATORa_chr);
   }
   if (name.length())                                                            //131120
   {  qualified_name_ASCII.append(DEFAULT_DIRECTORY_SEPARATORa_str);
      CORN::append_wstring_to_string(name ,qualified_name_ASCII);                //131120
   }
   if (extension.length())                                                       //131120
   {
      qualified_name_ASCII += '.';
      CORN::append_wstring_to_string(extension,qualified_name_ASCII);            //131120
   }
   CORN::string_to_wstring(qualified_name_ASCII, *this);
   delete designator_item;
}
//_2013-11-07__________________________________________________________________/
Directory_entry_name_concrete::~Directory_entry_name_concrete()
{  delete qualified_path_provided; qualified_path_provided = 0;
}
//__________________________________________________Directory_name:destructor__/
const Directory_entry_name &Directory_entry_name_concrete::set_DEN
(const Directory_entry_name &to_copy_from)                         modification_
{  assign(to_copy_from.w_str());
   decompose();
   setup_is_root();                                                              //140208
   return *this;
}
//_2011-12-12__________________________________________________________set_DEN_/
const Directory_entry_name &Directory_entry_name_concrete::set_wstr
(const wchar_t *to_copy_from)                                      modification_
{  clear_decomposition();
   std::wstring to_copy_from_dequoted;                                           //171217
   if (to_copy_from[0] == L'"')                                                  //171217
   {  size_t to_copy_from_len = wcslen(to_copy_from);                            //171217
      std::wstring dequoted = std::wstring(to_copy_from,1,to_copy_from_len-1);   //171217
   } else to_copy_from_dequoted = to_copy_from;                                  //171217
   assign(to_copy_from_dequoted);
   decompose();
   setup_is_root();                                                              //140208
   return *this;
}
//_2012-02-07________________________________________________________set_wchar_/
const Directory_entry_name &Directory_entry_name_concrete::set_cstr
(const char *to_copy_from)                                         modification_
{  clear_decomposition();
   std::string to_copy_from_dequoted;                                            //171217
   if (to_copy_from[0] == '"')                                                   //171217
   {  size_t to_copy_from_len = strlen(to_copy_from);                            //171217
      std::string dequoted = std::string(to_copy_from,1,to_copy_from_len-1);     //171217
   } else to_copy_from_dequoted = to_copy_from;                                  //171217
   CORN::string_to_wstring(to_copy_from_dequoted,*this);
   decompose();
   setup_is_root();                                                              //140208
   return *this;
}
//_2012-02-07_________________________________________________________set_cstr_/
const Directory_entry_name & Directory_entry_name_concrete::replace_name     (const std::wstring &new_name) modification_
{  name = new_name;
   construction_compose();                                                       //140422
   return *this;
}
//_2014-02-14___________________________________________________________________replace_name
const Directory_entry_name & Directory_entry_name_concrete::replace_name_cstr(const char *new_name) modification_
{  CORN::ASCIIZ_to_wstring(new_name,name);
   construction_compose();                                                       //140422
   return *this;
}
//_2014-02-14___________________________________________________________________
const Directory_entry_name & Directory_entry_name_concrete::replace_name_str(const std::string &new_name) modification_
{  CORN::string_to_wstring(new_name,name);
   construction_compose();                                                       //140422
   return *this;
}
//_2014-02-14___________________________________________________________________
//NYI   virtual const Directory_entry_name & replace_extension(std::wstring *new_name) modification_;
//_2014-02-14___________________________________________________________________
//NYI   virtual const Directory_entry_name & replace_extenstion_cstr(std::wstring *new_name) modification_;
//_2014-02-14___________________________________________________________________
} } // namespace CORN OS

