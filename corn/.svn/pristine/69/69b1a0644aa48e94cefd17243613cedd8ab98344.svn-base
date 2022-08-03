#ifndef argumentsH
#define argumentsH
#include "corn/data_source/datarec.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/application/verbosity.h"

namespace CORN
{
//______________________________________________________________________________
#define FIND_RESPONSES_FIRST 1
#define FIND_RESPONSES_LAST  3
//______________________________________________________________________________
class Arguments
: public extends_ Data_record
{
 protected:
   nat16 recognized_count; // Check if still used
   cognate_ std::string manual_URI;
 public: // options
   // generally conforms to common/standard command line options (for Linux)
   // http://tldp.org/LDP/abs/html/standard-options.html
   CORN::OS::File_name *program_filename; // fully qualified program
   nat8 verbose;
      // The larger the number the greater the verbose level
      // recommended bit patterns are shown above
   bool wizard;   // write wizard (to std::cout)
   bool quiet;       // no prompts
   bool debug;                                                                   //170317
   bool trial;
   bool force;                                                                   //171030

   nat8 recursion;                                                               //170616
      // bitmask of CORN::OS::File_system_recursion
      // Actually use OS::recursion
   // NYI conceptual
   nat8 recursion_depth;
      // when When
   bool help;
   nat8 find_responses;
      // if enabled (disabled by default)
      // find and process accessible response files.
      // Bit mask
      // Bit 0 (1=enabled)
      // Bit 1 (0=find first, 1=find last)
   std::wstring response_filename_extension;
   bool absolute_filenames;                                                      //170411
         // When creating link filenames, use absolute paths
         // The default is to use relative filenames.
   CORN::Text_list *collect_remaining;
      // Derived classes may set collect_remaining
      // When it has been determined that the remaining arguments
      // are to be collected as one set of related elements
      // The convention is that there would typically be an identifying
      // argument of the form   --XXX:
      // where the colon indicates the following arguments are to be collected.
   std::string success_filename;                                                 //180212
      // This is enabled by default, disable with empty string --success=
      // The default is "success".
      // Derived classes (program) may create a file with this name
      // if completed successfully, the file may contain any status information.
   /*180208 Conceptual
   std::string failure_filename;
      // if not successful, a "failure" file may be created.
   */
   CORN::OS::Directory_entry_name *response_file_encountered;                    //180213

   CORN::Unidirectional_list languages;                                          //180515
      // preferred language codes ISO 639-1.
      // https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
      // The first encountered is presumed default
      // This could move moved to CORN::Arguments
      // If none specified, defaults to the system language.

 public:
   contribute_ OS::Directory_name_concrete  start_directory;
      // initially the current working directory
 private:
   bool prompts_shown;
   bool recurse;                                                                 //180514
      // simple recursion, but will setup
   Unidirectional_list required_arguments; // of Item_string                     //180515
      // Simple (unique) text list of argument names/labels
      // Used when derived classes have required arguments.
      // The list is populated using require() method;
 public:
   Arguments();
   const CORN::OS::File_name * know_program_ASCIIZ  (const char    *program_path_name_);
   const CORN::OS::File_name * know_program_UnicodeZ(const wchar_t *program_path_name_);
   virtual ~Arguments();
 public:
   const CORN::OS::Directory_name *get_program_filename()                 const;
   const CORN::OS::Directory_name *get_program_directory()                const;
   // These get_program_XXXX methods will return 0 if the program is not known.
 public: // Data_record implementations
   virtual bool expect_structure(bool for_write);                                //180514
   virtual bool get_start();
   virtual bool get_end();
 public:
   virtual bool write_help()                                              const;
   // conceptual: add method to render or get command line
   // this would be used to echo back to the user how write
   // where what entered interactively via command line
   virtual bool write_wizard(std::ostream &wizard_stream)            stream_IO_;

   inline virtual bool has_interactive_prompts()                    affirmation_
      { return false; }
   inline virtual bool is_response_file_enabled()                   affirmation_
      { return false; }
      // eventually this should default to true
      // derived classes can override to support response files
   virtual bool interactive_prompt()                              modification_;
      // Prompts user for arguments that have not be
      // provided on the command line (default values not modified).

      // This is now obsolete using wizard
      // or implement using TUI wizard

   nat16 compose_command_line(std::string &command);
      // composes the current command line assignments and setting
      // returns the number of assignments and settings
   inline virtual bool get_author_mailto_URI(std::string &/*email_URI*/)   const
      { return false; }
      // contact email for the author of this program i.e. mailto:rnelson@wsu.edu
      // All program help really should provide a contact email.

   inline virtual bool get_program_version(std::string &version)           const
      { version = "unknown"; return false; }

   /*180515 (never used) and now using require and checking for encountered in get_end
   inline virtual bool are_required_provided()                      affirmation_
      { return true; }
   */

   virtual bool require(const std::string &argument_key_list);
      // Derived class may implement call this
      // usually in set_start to indicate that the specified arguments (keys)
      // are required.
      // When required arguments are not encountered on the command line
      // get_end() will check and return false if required arguments were
      // not encountered.
      // This is also used in wizard file generation to indicate

   inline virtual bool know_manual_URI(const std::string &manual_URI_)cognition_
      {  manual_URI.assign(manual_URI_);
         return true; }
   inline virtual const std::wstring &get_response_file_extension()        const
      { return response_filename_extension;}
   inline virtual bool is_verbose(nat8 level)                       affirmation_ //170317
      { return IS_VERBOSE(verbose,level); }
   inline virtual bool is_verbose_in_depth(nat8 level)              affirmation_ //170317
      { return IS_VERBOSE_IN_DEPTH(verbose,level,global_verbosity_depth); }
   inline virtual bool is_verbose_file_system(nat8 level)           affirmation_ //170317
      { return IS_VERBOSE_FILE_SYSTEM(verbose,level,global_verbosity_depth); }

/*170814RLN not currently used
   inline virtual bool is_verbose_debug(nat8 level)                 affirmation_ //170317
      { return IS_VERBOSE_DEBUG(verbose,level,global_verbosity_depth,debug); }
*/
 public:
      // Novel methods which may be reimplemented by derived class
      // that would likely provide additional arguments.
      // This should intern call these methods to pickup default arguments.
   virtual bool recognize(const std::string &paramstring)         modification_;
   virtual bool recognize_option(const std::string &paramstring)  modification_;
   virtual bool recognize_assignment
      (const std::string &variable
      ,const std::string &value)                                  modification_;
   /*180213 replaced with take_DEN_xxxxx()
   virtual bool recognize_DEN
      (const CORN::OS::Directory_entry_name &param_DEN)           modification_;
   */
   virtual bool read_response_file_potentially
      (const CORN::OS::Directory_entry_name &param_DEN)           modification_;
      // In most cases this will not need to be overridden
   virtual bool submit_DEN                                                       //180213
      (CORN::OS::Directory_entry_name *param_DEN)                   submission_;
   virtual bool submit_DEN_qualified                                             //180213
      (CORN::OS::Directory_entry_name *param_DEN_qualified)         submission_;
   virtual bool submit_DEN_unqualified                                           //180213
      (CORN::OS::Directory_entry_name *param_DEN_unqualified)       submission_;
   /*abandoned
   inline virtual bool qualify_DENs()              affirmation_ { return false;}
      // Derived classes will override to indicate that potential DEN arguments
      // should be qualified.
   */
   void display_interactive_instructions();
 protected:
   bool read_response_file
      (const CORN::OS::File_name &response_filename)              modification_;
   nat32 find_and_read_response_files()                           modification_;
 };
//______________________________________________________________________________
} // namespace CORN
#endif

