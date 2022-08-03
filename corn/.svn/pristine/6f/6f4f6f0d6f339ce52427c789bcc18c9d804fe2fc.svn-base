#include "uniform_resource_identifier.h"
namespace CORN { namespace OS {
//______________________________________________________________________________
Uniform_resource_identifier::Uniform_resource_identifier(const std::wstring &URI)
: std::string()
,schema     (0)
,authority  (0)
,path       (0)
,query      (0)
,fragment   (0)
{  CORN::wstring_to_string(URI,*this);
   construction_decompose();
}
//______________________________________________________________________________
Uniform_resource_identifier::Uniform_resource_identifier(const std::string &URI)
: std::string(URI)
,schema     (0)
,authority  (0)
,path       (0)
,query      (0)
,fragment   (0)
{  construction_decompose();
}
//______________________________________________________________________________
Uniform_resource_identifier::Uniform_resource_identifier(const char *URI)
: std::string(URI)
,schema     (0)
,authority  (0)
,path       (0)
,query      (0)
,fragment   (0)
{  construction_decompose();
}
//______________________________________________________________________________
Uniform_resource_identifier::Uniform_resource_identifier(const OS::File_name &file_name)
: std::string(file_name.c_str())
,schema     (0)
,authority  (0)
,path       (new CORN::OS::Directory_entry_name_concrete(file_name))
,query      (0)
,fragment   (0)
{
//construction_decompose not needed because with a filename, there is only path
}
//______________________________________________________________________________
Uniform_resource_identifier::Uniform_resource_identifier(const Uniform_resource_identifier &URI)
: std::string(URI)
,schema     (0)
,authority  (0)
,path       (0)
,query      (0)
,fragment   (0)
{  construction_decompose();
}
//______________________________________________________________________________// copy constructor
void Uniform_resource_identifier::construction_decompose()         construction_
{
   std::string *remainder = new std::string(*this);
   std::size_t colon_pos = find(':');
   if (colon_pos != std::string::npos)
   {
      schema = new std::string(*this,0,colon_pos);
      std::string *new_remainder = new std::string(*remainder,colon_pos+1);
      delete remainder;
      remainder = new_remainder;
   }
   if ((remainder->c_str()[0] == '/') && (remainder->c_str()[1] == '/'))
   {  std::string *authority_etc = new std::string(*remainder,2);
      delete remainder;
      remainder = authority_etc;
   }
   std::size_t authority_terminator_pos = remainder->find('/');
   if (authority_terminator_pos != npos)
   {  std::string potential_authority(*remainder,0,authority_terminator_pos);
      authority = new Authority(potential_authority);
      if (authority->is_valid())
      {  std::string *path_etc = new std::string(*remainder,authority_terminator_pos+1);
         delete remainder;
         remainder = path_etc;
         // delete path_etc;
      } else
      {  delete authority;
         authority = 0;
      }
   }
   std::string *path_etc = remainder;
   remainder = 0;
   std::size_t  q_pos = path_etc->find('?');
   if (q_pos == std::string::npos)
   {  // there is no query
      std::size_t path_end_pos = path_etc->find('#');
      if (path_end_pos == std::string::npos)
         path= new CORN::OS::Directory_entry_name_concrete(*path_etc);
      else
      {  std::string path_only(*path_etc,0,path_end_pos);
         path = new CORN::OS::Directory_entry_name_concrete(path_only);
         fragment = new std::string(*path_etc,path_end_pos+1);
      }
      //path_etc = 0;
   } else
   {  // there is a query
      std::string path_only(*path_etc,0,q_pos);
      path = new CORN::OS::Directory_entry_name_concrete(path_only);
      std::string *query_etc = new std::string (*path_etc,q_pos+1);
      std::size_t query_end_pos = path_etc->find('#');
      if (query_end_pos == npos)
      {  // No
         query = query_etc;
      } else
      {  query = new std::string(query_etc->c_str(),query_end_pos);
         fragment = new std::string(*query_etc,query_end_pos+1);
      }
   }
   // At this point there shouldn't be any remainder, so this is just
   // cleanup
   delete remainder;
}
//______________________________________________________________________________
bool Uniform_resource_identifier::Authority::is_valid()                                          affirmation_
{  return
      hostname
      //NYI && (!port  || CORN::string_is_integer(*port)  )
      ;
}
//______________________________________________________________________________
void Uniform_resource_identifier::Authority::construction_decompose() construction_
{
   std::size_t port_colon_pos = find(':');
   std::string *authority_without_port = 0;                                      //151016
   if (port_colon_pos != std::string::npos)
   {  // looks even more like an authority
      port = (nat16) CORN::cstr_to_nat32(std::string(*this,port_colon_pos+1).c_str(),10); //160803
         //160803 new std::string(*this,port_colon_pos+1);
      authority_without_port = new std::string(c_str(),0,port_colon_pos);        //160831
   }
   else authority_without_port = new std::string(c_str());                       //160831

   if (authority_without_port)
   {
      size_t rightmost_dot_pos = rfind('.');
      if (rightmost_dot_pos == npos)
      {  // This doesn't appear to be valid authority
         // The URL could have been be of the form  file://path_etc
         hostname = 0;
         delete authority_without_port; //authority_without_port = 0;
      } else
      {  std::string top_level_domain(*authority_without_port,rightmost_dot_pos+1);
         bool has_top_level_domain
         =  (top_level_domain=="com")
         || (top_level_domain=="edu")
         || (top_level_domain=="gov")
         || (top_level_domain=="org")
         || (top_level_domain=="net")
         || (top_level_domain=="mil")
         // less common domains
         || (top_level_domain=="biz")
         || (top_level_domain=="cat")
         || (top_level_domain=="coop")
         || (top_level_domain=="info")
         || (top_level_domain=="jobs")
         || (top_level_domain=="mobi")
         || (top_level_domain=="museum")
         || (top_level_domain=="name")
         || (top_level_domain=="post")
         || (top_level_domain=="pro")
         || (top_level_domain=="tel")
         || (top_level_domain=="travel")
         || (top_level_domain=="xxx");
         if (!has_top_level_domain) // It might be a country code domain
              has_top_level_domain = top_level_domain.length() == 2;
         if (has_top_level_domain) // so far it looks like an authority
         {
            size_t a_pos = authority_without_port->find('@');
            if (a_pos != std::string::npos)
            {
               std::string user_info(authority_without_port->c_str(),0,a_pos);

               // WARNING THE FOLLOWING HAS NOT YET BENN

               size_t colon_pos = user_info.find(':');
               if (colon_pos == std::string::npos) // no password
                  username = new std::string(user_info);
               else
               {  username = new std::string(user_info,0,colon_pos);
                  password = new std::string(user_info,colon_pos+1);
               }
               hostname = new std::string(*authority_without_port,a_pos+1);
               delete authority_without_port;
               //authority_without_port = 0;
            } else
            {  hostname = authority_without_port;
               //authority_without_port = 0;
            }
         }
      }
   } // else no authority
}
//______________________________________________________________________________
const std::string &Uniform_resource_identifier::recompose()
{
   clear();
   if (schema)    { append(*schema); append(":"); };
   append("//");
   if (authority) authority->append_to_string(*this);
   append("/");
   path->append_to_string(*this);
   if (query)     { append("?"); append(*query); }
   if (fragment)  { append("#"); append(*fragment); }
   return *this;
}
//_2015-07-29___________________________________________________________________
const std::string &Uniform_resource_identifier::set_path_string(const std::string &new_path)
{
   if (path) delete path;
   path = new CORN::OS::File_name_concrete(new_path);
   return recompose();
}
//_2015-07-29___________________________________________________________________
const std::string &Uniform_resource_identifier::set_path_filename(const OS::File_name &new_path)
{
   if (path) delete path;
   path = new CORN::OS::File_name_concrete(new_path);
   return recompose();
}
//_2015-07-29___________________________________________________________________
const std::string &Uniform_resource_identifier::set_local_path_string(const std::string &new_path)
{
   // filename is likely fully qualified (put could be relative)
   // The schema is change to 'file'
   // and the domain is cleared
   delete schema;    schema = new std::string("file");
   delete authority; authority = 0;
   return set_path_string(new_path);
}
//_2015-07-29___________________________________________________________________
const std::string &Uniform_resource_identifier::set_local_path_filename(const OS::File_name &new_path)
{
   // filename is likely fully qualified (put could be relative)
   // The schema is change to 'file'
   // and the domain is cleared
   delete schema;    schema = new std::string("file");
   delete authority; authority = 0;
   return set_path_filename(new_path);
}
//_2015-07-29___________________________________________________________________
const std::string &Uniform_resource_identifier::Authority::append_to_string
(std::string &buffer)                                                      const
{
//160803    if(user_info) { buffer.append(*user_info); buffer.append("@"); }
   if (username)
   {  buffer.append(*username);
      if (password)
      {  buffer.append(":");
         buffer.append(*password);
      }
      buffer.append("@");
   }
   if(hostname) { buffer.append(*hostname); }
   if(port)
   {  buffer.append(":");
      CORN::append_nat16_to_string(port,buffer);                                 //160803
      //160803 buffer.append(*port);
   }
   return buffer;
}
//_2015-08-18___________________________________________________________________
const Uniform_resource_identifier::Authority *Uniform_resource_identifier::get_authority()         provision_
{
   return authority;
}
//_2016-08-24___________________________________________________________________
bool Uniform_resource_identifier::get_path_query_fragment_string(std::string &path_query_fragment)   const
{
   std::wstring path_wstring;
   if (path) path->append_components_to(path_wstring);
   CORN::append_wstring_to_string(path_wstring,path_query_fragment);
   if (query) // optional
   {  path_query_fragment.append("?");
      path_query_fragment.append(*query);
   }
   if (fragment) // optional
   {  path_query_fragment.append("#");
      path_query_fragment.append(*fragment);
   }
   return path;
}
//_2016-08-24___________________________________________________________________
}} //namespace CORN::OS

