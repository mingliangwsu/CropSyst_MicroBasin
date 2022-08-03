#ifndef explaination_locationH
#define explaination_locationH
#include "corn/container/text_list.h"
#include "corn/labeled_enum.h"
#include "corn/dynamic_array/dynamic_array_T.h"
//170525 #include "corn/datetime/date.hpp"
#include "corn/OS/uniform_resource_locator.h"
//---------------------------------------------------------------------------
namespace CORN
{
struct Documentation_paths_fully_qualified
{
   cognate_ const CORN::OS::Directory_name *program;
   cognate_ const CORN::OS::Directory_name *application;
   cognate_ const CORN::OS::Directory_name *suite;
   cognate_ const CORN::OS::Uniform_resource_identifier *Web_root_URI;
   cognate_ const CORN::OS::Directory_name *local_root;
};
//______________________________________________________________________________
class Explaination //_location
: public implements_ Item
{
public:
   enum Severity {severity_information, severity_warning, severity_error};       //151003
   static Label_description severity_label_table[];
   DECLARE_DESCRIPTIVE_LABELED_ENUM(Severity_labeled,Severity,severity_label_table)
public:  // This class is used for internal communication of error information
         // so data members are public
   Severity severity;

   /**
   // Parts of the URI of the document ANCHOR is used as the caption
   // when presenting explainations in lists (and to index the explaination);
   // All explainations may be stored in a single file
   // or they may be stored in separate files.

   **/
   contribute_ OS::Uniform_resource_locator document_URL;
      /** This is a URI to a document that gives a detailed description
      // of the error.
      // Typically this will be in the form:
      // Web document         HTTP://address/path/document.ext#anchor
      //    This is for help that is available on the Web
      // Installed document   d:\path\document.ext
      //    This is for help installed with an application that may or may not be HTML
      //    (The help viewer will attempt to open the file with Invoke_viewer.

      //obsolete  Installed help       %EXE_HOME%/path/document.ext#anchor
      // Installed help       %PROG_DOC%/path/document.ext#anchor
      //    This indicates that the document path is relative to the current executable's
      //    directory. (I.e. argv[0] without the executable's file name)
      // Installed help       %APP_DOC%/path/document.ext#anchor
      //    This indicates that the document path is relative to the application's
      //    home directory.
      // Installed help       %SUITE_DOC%/path/document.ext#anchor
      //    This indicates that the document path is relative to the application suite's
      //    home directory.

      //    The home directory may be on the local machine
      //    or on the web, the application will provide the local home directory
      //    or optionally the Web URL root directory.

      // The .ext extension can actually be any document that can be openned
      // in a web browser such as Microsoft compiled help (CHM).
      // (HTM, HTML, TXT, DOC, PDF, etc...)

      // The path may be omitted,  In this case resolve_URL() will
      // Search from the program's directory and its subdirectories for the documents.
      **/
      /**
      When explainations stored in separate files, the explaination URI
      document file name (without the file name extension)
      will be considered as the caption text when displaying
      explainations in lists.

      When explainations are stored in a single file, the anchor label/ID
      is used as the caption.
      **/

   std::string     additional_comment;
      // Additional information that may be relevent to the context where the
      // error occurred.
   Text_list   context_URIs;
      // This will be one or more URIs typically a local file where the error occured.
      // For database files this may be the fully qualified name of the table where
      // anchor is the record number.
      // For VV/parameter files this may the the fully qualified name of the parameter file
      // and the name of the edit control this way the help viewer can
      // open the problem file and focus on the edit control where the error
      // in data is likely to be. If the name of the edit control is not known,
      // the anchor can be omitted and at least the file can be openned.
      // The error could be nested within a number of function calls
      // and/or cascading failures of related file locations,
      // thus there could be multiple error contexts.
      // Typically as function returns with an error indication.
      // The calling function may append additional context information
      // so the user can track the progression of the error condition with
      // the cascading contexts precipitating the error.

   CORN::Dynamic_array<datetime64>occurance_datetimes;
      // Optional list of date and/or times the event occured.
 public:
   Explaination
      (const Severity     serverity
      ,const std::string &document_URI
      ,const std::string &additional_comment
      ,const std::string &context_URI);
   Explaination
      (const Severity     serverity
      ,const std::string &document_URI
      ,const std::string &additional_comment
      ,const OS::File_name &file_name);
   Explaination                                                                  //140620
      (const Severity     severity
      ,const std::string &document_URI
      ,const std::string &additional_comment
      ,const std::string &context_URI
      ,const datetime64 occurance_datetime);
   inline virtual ~Explaination() {}                                             //151204
   void append_context(const std::string &_context_URI);
   void render(std::string &as_string,const char *delimiter)               const;
   //void render_HTML(Ustring &as_string,char *delimiter)                    const;
   virtual int   compare(const Item &)                                     const;//110622
   virtual bool  write(std::ostream &)                              performs_IO_;//150728_110811
   bool is_resolved()                                               affirmation_;//150729
   bool resolve_URL
      (const Documentation_paths_fully_qualified &doc_paths
      ,bool  find_unqualified_filenames)                           contribution_;//150729
 private:
   bool replace_variable                                                         //150729
      (const char *variable
      ,const CORN::OS::Directory_name &doc_path
      ,bool find_unqualified_filenames
      ,const CORN::OS::Uniform_resource_identifier *Web_root_URI
      ,const CORN::OS::Directory_name *local_root)                 contribution_;
/*
 protected:
   nat32 resolve_URLs()                                            contribution_;//150727
*/
};
//______________________________________________________________________________
} // namespace CORN;
#endif
