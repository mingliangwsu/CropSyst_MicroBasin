#ifndef uniform_resource_identifierH
#define uniform_resource_identifierH
#include <string>
#include "corn/OS/directory_entry_name_concrete.h"
// Reference: http://en.wikipedia.org/wiki/URI_scheme#Generic_syntax
namespace CORN { namespace OS {
//______________________________________________________________________________
class Uniform_resource_identifier
: public std::string
{
 public:
   struct Authority
   : public std::string
   {
      //160802 std::string *user_info;
      std::string *username;                                                     //160802
      std::string *password;                                                     //160802
         // Currently password is optional
      std::string *hostname;
      nat16        port; // std::string *port;
      inline Authority(const std::string &complete)
         : std::string(complete)
         , hostname(0)
         , port(0)
         //160802, user_info()
         , username(0)                                                            //160802
         , password(0)                                                            //160802
         { construction_decompose(); }
      void construction_decompose()                                construction_;
      bool is_valid()                                               affirmation_;
      virtual const std::string &append_to_string(std::string &buffer) const; //130103
   };
   //___________________________________________________________________________
 protected:
   // Currently URIs don't recognize non ASCII characters
   std::string *schema;     // I.e. http  ftp   (trailing : not included)
   Authority   *authority;
      // I.e. domain name (leading // not included)
      // username:password@example.com:8042
   OS::Directory_entry_name  *path;
      // I.e. file name (optional leading / not included)
      // Can be qualified, relative, fully qualified (for a local file)
      // Actually I think the path could be a directory name or a filename
      // because the Web server with load by default index.html file
      // if filename is not specified
   std::string *query;      // (leading ? not included)
   std::string *fragment;   // (leading # not included);
 public: // structors
   Uniform_resource_identifier(const std::wstring &URI);
   Uniform_resource_identifier(const std::string &URI);
   Uniform_resource_identifier(const char *URI);
   Uniform_resource_identifier(const OS::File_name &file_name);
   Uniform_resource_identifier(const Uniform_resource_identifier &URI); // copy constructor
 public:
   inline const OS::Directory_entry_name &ref_path()                       const { return *path; }
      // I am pretty sure that constructor alway allocates path, but I haven't checked
   const std::string &set_path_string(const std::string &new_path);
   const std::string &set_path_filename(const OS::File_name &new_path);
      // filename is not fully qualified and not necessarily a local filename
   const std::string &set_local_path_string(const std::string &new_path);
   const std::string &set_local_path_filename(const OS::File_name &new_path);
      // filename is likely fully qualified (put could be relative)
      // The schema is change to 'file'
      // and the domain is cleared
   Authority &provide_authority()                                     provision_;
   const Authority *get_authority()                                   provision_;
   bool get_path_query_fragment_string(std::string &path_query_fragment)   const;
 private:
   void construction_decompose()                                   construction_;
   const std::string & recompose();
};
//_2013-11-18___________________________________________________________________
} } //namespace CORN::OS
#endif
