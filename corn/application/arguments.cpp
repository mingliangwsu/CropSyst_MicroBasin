#include "corn/application/arguments.h"
#include "corn/application/progress.h"
#include "corn/OS/file_system_engine.h"
#include "corn/container/text_list.h"

#include "corn/data_source/vv_file.h"
#include "corn/data_source/command_options_datasrc.h"
#include "corn/seclusion.h"
#include "corn/string/strconv.hpp"
#include <iostream>
#ifdef _Windows
#  include <windows.h>
#endif

namespace CORN
{
int8 global_verbosity_depth=0;                                                   //170317
//______________________________________________________________________________
Arguments::Arguments() // NYI (const char *program_path_name_)
: CORN::Data_record("arguments")
, recognized_count         (0)
, program_filename         (0)
, verbose                  (0)                                                   //170217
, quiet                    (false)
, recurse                  (false)                                               //180514
, recursion                (CORN::OS::File_system::none_recursion_inclusive)     //170616
, recursion_depth          (0)                                                   //180801
, trial                    (false)                                               //170822
, force                    (false)
, success_filename
#ifdef __linux__
   ("success")                                                                   //180208
#else
   // Under Windows, not using the status file idiom by default
   ("")
#endif
, response_file_encountered(0)                                                   //180213
, debug                                                                          //170317
   #ifdef DEBUG_
      (true)
   #else
      (false)
   #endif
, help                     (false)
, find_responses           (0)                                                   //170601
, prompts_shown            (false)
, start_directory          () // defaults to CWD
, absolute_filenames       (false)                                               //170411
, collect_remaining        (0)                                                   //170616
, languages                (true) //unique                                             //180515
{
   response_filename_extension = L"rsp";                                         //171110
      // .rsp was used in CS V4
      // From V5 now using .response
      // I need to make sure that any utilities (such as UED import/export)
      // now use response.
      // This assignment is ONLY to support legacy CS suite utilties
}
//_2016-08-25___________________________________________________________________
Arguments::~Arguments()
{
   delete response_file_encountered;
}
//_2019-02-13___________________________________________________________________
const CORN::OS::File_name * Arguments::know_program_ASCIIZ(const char    *program_path_name_)
{  delete program_filename;
   program_filename = new CORN::OS::Directory_name_concrete(program_path_name_);
   return program_filename;
}
//_2017-04-03___________________________________________________________________
const CORN::OS::File_name * Arguments::know_program_UnicodeZ(const wchar_t *program_path_name_)
{  delete program_filename;
   program_filename = new CORN::OS::Directory_name_concrete(program_path_name_);
   return program_filename;
}
//_2017-04-03___________________________________________________________________
const CORN::OS::File_name *Arguments::get_program_filename()               const
{  return  program_filename;
}
//_2017-04-03___________________________________________________________________
const CORN::OS::Directory_name *Arguments::get_program_directory()         const
{  return program_filename
   ?  program_filename->get_path_directory_name()
   : 0;
}
//_2017-04-03___________________________________________________________________
bool Arguments::expect_structure(bool for_write)
{
#ifdef USE_EXPECT_STRUCTURE
   expect_switch("quiet"   ,"q"           ,quite               ,false,caption,hint);
   expect_switch("debug"   ,"debug"       ,debug               ,false,caption,hint);
   expect_switch("absolute","absolute"    ,absolute_filenames  ,false,caption,hint);
   expect_switch("dry-run" ,"trial"       ,trial               ,false,caption,hint);
   expect_switch("force"   ,"f"           ,force               ,false,caption,hint);
   expect_switch("r"       ,"R"           ,recurse             ,false,caption,hint);


   expect_string("--success"      , success_filename            ,caption,hint);
      // doesn't need to be expect_assignment because not required

#endif
   return Data_record::expect_structure(for_write);
}
//_expect_structure_________________________________________________2018-05-14_/
bool Arguments::recognize
      (const std::string &paramstring)                             modification_
{  bool recognized = false;
   bool assignment = false;                                                      //171120
   if (collect_remaining)                                                        //170616
   {  // Must be done first because once we have identified that the remaining
      // args are to be collected, the remaining arguments are not further considered
      collect_remaining->add_string(paramstring);
      recognized = true;
   }
   {  std::size_t equal_pos = paramstring.find('=');
      assignment = equal_pos != std::string::npos;                               //171120
      if (assignment) // 171120 (equal_pos != std::string::npos)
      {  // Appears to be an assignment argument
         std::string variable (paramstring,0,equal_pos);
         std::string value    (paramstring,equal_pos+1);
         recognized = recognize_assignment(variable,value);
      }
   }
   if (! recognized && !program_filename)                                       //171101
   {  // This is most likely arg0 (the program filename)
      program_filename = new
         CORN::OS::Directory_entry_name_concrete(paramstring);
      recognized = true;
   }
   if (! recognized)
   {  if (paramstring[0] == '-')
      {  std::size_t option_pos = 1;
         if (paramstring[1] == '-')  // -- form
            option_pos = 2;
         std::string option(paramstring,option_pos);
         recognized = recognize_option(option);
         if (!recognized)                                                        //170308
         {  // multiple single character options may be strung together
            // I.e.  -xyz is equivelent to -x -y -z
            // So if -xyz is not a recognized specific option
            recognized = true;
            for (nat8 n = 0; n < option.length(); n++)
            {  std::string option_n(option,n,1);
               recognized &= recognize_option(option_n);
            }
         }
      }
   }

   if (!recognized && !assignment)                                               //180213
   {
      CORN::OS::Directory_entry_name_concrete *potential_DEN_potentially_qualified
         = new CORN::OS::Directory_entry_name_concrete(paramstring);
      recognized
      = submit_DEN(potential_DEN_potentially_qualified);
   }
   return recognized;
}
//_2016-03-11___________________________________________________________________
bool Arguments::recognize_option(const std::string &paramstring)   modification_
{  bool recognized = false;
   if (  (paramstring == "verbose")
       ||(paramstring == "v"))
      {  verbose = 1;                   recognized = true; recognized_count++; }
   #ifndef USE_EXPECT_STRUCTURE
   else if (  (paramstring == "recursive")
            ||(paramstring == "r")
            ||(paramstring == "R")
            )
      {  recursion = CORN::OS::File_system::subdirectory_recursion_inclusive;
         recognized = true;
      }
   #endif
/* NYI
   else if (paramstring == "version")
      {  std::clog << "program:" << program_path_name << std::endl;
         std::string program_version; get_program_version(program_version);
         std::clog << "version: "
            << program_version << std::endl;
         recognized = true; recognized_count++; }
*/
   else if (paramstring == "responses")
      {  find_and_read_response_files();
         recognized = true;
      }

   #ifndef USE_EXPECT_STRUCTURE
   else if (  (paramstring == "quiet")
            ||(paramstring == "q"))
      { quiet   = true;                 recognized = true; recognized_count++; }
   else if (  (paramstring == "debug"))                                          //170317
      { debug = true;                   recognized = true; recognized_count++; }
   else if (paramstring == "help")
      { help = true;                    recognized = true; recognized_count++; }
   else if (paramstring == "absolute")                                           //170411
      {  absolute_filenames = true;
         recognized = true;
      }
   else if (  (paramstring == "trial")
            ||(paramstring == "dry-run"))
      {  trial = true;
         recognized=true;
      }
   else if (  (paramstring == "f")                                               //171020
            ||(paramstring == "force"))
      {  force = true;
         recognized=true;
      }

   else if (  (paramstring == "wizard")                                          //171020
            )
      {  wizard = true;
         recognized=true;
      }

   #endif
   else if (paramstring == "progress")                                           //170323
      { provide_progress_display_global();                                       //170519
         recognized = true;
      }
   return recognized;
}
//_2016-10-13___________________________________________________________________
// we read the response when encountered on the command line
// option values will be loaded (overriding any currently set values)
// but any options still on the command line would superceed what is loaded.
// There are two modes for recognizing response file name
// There may be multiple occurances of response files.
// either a unary filename having a recognized reponse file extension,
// or --response={filename} where the {filename} with no or any extension
// is presumed to be a response file.
bool Arguments::recognize_assignment
(const std::string &variable
,const std::string &value)                                         modification_
{  bool recognized = false;
   if (  (variable == "--response"))
   {  CORN::OS::File_name_concrete response_filename(value);
      recognized = read_response_file(response_filename);
   }
   else if (variable == "--verbose")                                           //170207
   {
      /* conceptual
      (There may be multiple --verbose= arguments_

      The value could either be
      verbosity level or a flag or  all
      bits
      0-2  (7 levels)
      3 count     show counts  (I.e. of things process, files openned
      4 progression show step or stage
         (this is separate from --progress)
      5 openning   show when (existing) files/objects openned
      6 creation   show files/object created
      7 discovery/location/origination  show (list) DEN's searched for and discovered
      8 resolution show resolved relative to absolute (or vica versa) DEN's
      9 recursion  show directories entered in recursion
      10 inclusion/selection   show when something deemed relevent/selection.
      11 exclusion/rejection ( elimination) show when something deemed not relevent (also why is known)
      12 Authentication show when handshaking with server or other resource
      13
      14
      15 debug
      Bits in debug mode
      0-2  (7 levels)
      3 enter-program  show methods on entry (debug)
      4 enter-library  show methods on exit  (debug)

      */


      verbose = (nat8)CORN::cstr_to_nat16(value.c_str(),10);
      recognized = true;                                                         //170223
   }
   else if (variable == "--progress")                                          //170519
      recognized
      = provide_progress_display_global().parameter.set_indicator(value);        //170519
   else if (variable.find("--progress") != std::string::npos)                    //170316
      recognized
      = provide_progress_display_global()
         .parameter.recognize_assignment(variable,value);                        //170519
   else if (  (variable == "--recursion")
//            ||(variable == "-R")
            )
      {  // This is additive
         if      (value == "subdirectory")   recursion |= FILE_SYSTEM_RECURSION_SUBDIRECTORY;
         else if (value == "superdirectory") recursion |= FILE_SYSTEM_RECURSION_SUPERDIRECTORY;
         else if (value == "exclusive")      recursion |= FILE_SYSTEM_RECURSION_EXCLUSIVE;
         recognized = true;
      }
   else if (variable == "--depth")                                               //180801
   {  recursion_depth = CORN::cstr_to_nat16(value.c_str(),10);                   //180801
      recognized = true;                                                         //180801
   }
   else if (variable == "--language")
   {  languages.append(new CORN::Item_string(value));
      recognized = true;
   }

   #ifndef USE_EXPECT_STRUCTURE
   else if (  (variable == "--success"))
   {  success_filename = value;
      recognized = true;
   }
   #endif
   return recognized;
}
//_2016-10-13___________________________________________________________________
bool Arguments::read_response_file_potentially
(const CORN::OS::Directory_entry_name &param_DEN)                  modification_
{  bool recognized = false;
   bool response_filename_encountered =
      response_filename_extension.length() &&                                    //170725
      param_DEN.has_extension(response_filename_extension);
   if (response_filename_encountered)
      // Attempt to read the response file
      // (if it is not found it will not be read so considered unrecognized.
      recognized = read_response_file(param_DEN);
   return recognized;
}
//_2016-10-15___________________________________________________________________
bool Arguments::submit_DEN
(CORN::OS::Directory_entry_name *potential_DEN_potentially_qualified)submission_
{
   bool recognized
      = (potential_DEN_potentially_qualified->is_qualified())
      ? submit_DEN_qualified(potential_DEN_potentially_qualified)
      : submit_DEN_unqualified(potential_DEN_potentially_qualified);
   if (!recognized)
      // Nobody accepted then DEN, so just delete it.
      delete potential_DEN_potentially_qualified;
   return recognized;
}
//_2018-02-13_______________________________________________take_DEN_qualified_/
bool Arguments::submit_DEN_qualified
(CORN::OS::Directory_entry_name *param_DEN)                          submission_
{
   bool recognized = read_response_file_potentially(*param_DEN);
   if (recognized)
      response_file_encountered = param_DEN;
      // Not currently using the response filename
      // just keeping it incase a derived class wants to use it.
   // Nobody accepted then DEN, so just delete it.
//   delete param_DEN;
   return recognized;
}
//_2018-02-13_______________________________________________take_DEN_qualified_/
bool Arguments::submit_DEN_unqualified
(CORN::OS::Directory_entry_name *param_DEN_unqual)                   submission_
{
   bool recognized = read_response_file_potentially(*param_DEN_unqual);
   if (recognized)
   {
      response_file_encountered = param_DEN_unqual;
      // Not currently using the response filename
      // just keeping it incase a derived class wants to use it.
      // Nobody accepted then DEN, so just delete it.
   }
   else
   {
      CORN::OS::Directory_entry_name_concrete *param_DEN_qualified
         = new CORN::OS::Directory_entry_name_concrete
            (start_directory,*param_DEN_unqual);
      recognized = submit_DEN_qualified(param_DEN_qualified);
//      delete param_DEN_unqual;
   }
   return recognized;
}
//_2018-02-13_____________________________________________take_DEN_unqualified_/
bool Arguments::read_response_file                                 modification_
(const OS::File_name &response_filename)
{  Command_options_data_source response_file(response_filename);
   return response_file.get(*this); // get arguments
}
//_2016-10-15___________________________________________________________________
nat32 Arguments::find_and_read_response_files()
{  Unidirectional_list response_files_accessible;
   OS::Directory_name_concrete CWD;
   if (verbose > 3) std::clog << "info: Searching for accessible response files." << std::endl;
   nat32 response_file_count = OS::file_system_engine.list_DENs
      (CWD,&response_files_accessible,0,Inclusion("*.response",true)
      ,OS::File_system::superdirectory_recursion_inclusive);
   //161021 warning should have a virtual method to get
   // the response filename pattern from derived classes
   nat8 hold_find_responses = find_responses;
   find_responses = false;
   // while reading the response files disable find otherwise infinite loop.
   if (verbose > 1 && response_file_count)
      std::clog << "info: loading accessible response files." << std::endl;
   FOR_EACH_IN(response_file,CORN::OS::File_name
              ,response_files_accessible,each_response_file)
   {  read_response_file(*response_file);
   } FOR_EACH_END(each_response_file)
   find_responses = hold_find_responses;
   return response_file_count;
}
//_2016-10-21___________________________________________________________________
bool Arguments::get_start()
{  if (find_responses & FIND_RESPONSES_FIRST)
      find_and_read_response_files();
   return true;
}
//_2016-10-21___________________________________________________________________
bool Arguments::get_end()
{
   bool ended = true;
   if (find_responses & FIND_RESPONSES_LAST)                                     //161021
       find_and_read_response_files();

   if (wizard) ended &= write_wizard(std::cout);                                 //180515

   #ifndef USE_EXPECT_STRUCTURE

   // Here we could process verbose progress recursion

   if (recurse)                                                                  //180514
      recursion = CORN::OS::File_system::subdirectory_recursion_inclusive;

   #endif
   if (help) write_help();
   // response files are processed as encountered
   if (!quiet && has_interactive_prompts() && prompts_shown)
   {  // must be after loading response file
      interactive_prompt();
      std::string command_line;
      if (compose_command_line(command_line))
      {  std::string continue_enter;
         std::clog
            << "These options can be specified on the command line as:"
            << std::endl << command_line << std::endl
            << std::endl
            << "Press [Enter] to continue" << std::endl;
         std::getline(std::cin,continue_enter);
      }
   }
   if (!quiet && has_interactive_prompts() && is_response_file_enabled())
   {  std::clog
      << "Write command line and prompted (and loaded response file) options to a response file?" << std::endl;
      if (verbose & VERBOSE_FLAG_EXPLAINATION)
         std::clog
         << "This will allow restarting the program with the same set of options." << std::endl;
      std::clog << "Enter response file name:" << std::endl;
      std::string response_filename;
      std::getline(std::cin,response_filename);
      /* conceptual:
      if CORN::OS::file_system_engine.exists(response_filename);
      if (!yes)
         std::clog << "Replace the response file that already exists (y/n)?"
         replace = get y/n yes/no
      if (replace)
      else response_filename.clear()
      */

      if (response_filename.length())
      {  std::string response_content;
         compose_command_line(response_content);
         std::ofstream response_file(response_filename.c_str());
         response_file << response_content << std::endl;

         // NYI Don't forget unary options
      }
   }
   resolve_directory_entry_names(start_directory);                               //171107
   if (languages.is_empty())                                                     //180515
   {
      // https://msdn.microsoft.com/en-us/library/windows/desktop/dd318139(v=vs.85).aspx
      // https://docs.microsoft.com/en-us/previous-versions/windows/desktop/apps/jj244362(v=vs.105)
      // append the system language of the OS
      #ifdef _Windows
      // sorry for the lapse into Windows API uglyness
      ULONG numLanguages = 0;
      DWORD cchLanguagesBuffer = 0;
      BOOL hr = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &numLanguages, NULL, &cchLanguagesBuffer);
      if (hr)
      {  WCHAR* pwszLanguagesBuffer = new WCHAR[cchLanguagesBuffer];
         hr = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &numLanguages, pwszLanguagesBuffer, &cchLanguagesBuffer);
         if (hr)
         {  char lang[20]; lang[0] = 0; nat32 lang_i = 0;
            for (nat16 i = 0; i < cchLanguagesBuffer; i++)
            {  wchar_t curr_char = pwszLanguagesBuffer[i];
               switch (curr_char)
               {  case L'-':
                  {  lang[lang_i] = 0;
                     languages.append(new CORN::Item_string(lang));
                  } break;
                  case L',':
                  {  lang_i = 0;
                     lang[0] = 0;
                  } break;
                  default :
                  {
                     lang[lang_i++] = (char)curr_char;
                  }  break;
               } // switch
            } // for i
         } // if hr
         delete pwszLanguagesBuffer;
      } // if hr
      #endif
      #ifdef _Linux
      // NYI
      #endif
   }
   return ended;                                                                 //180515
}
//_2016-08-25___________________________________________________________________
bool Arguments::write_help()                                               const
{
   std::string author_mailto_URI;
   if (get_author_mailto_URI(author_mailto_URI))
      std::clog
      << "author: " << author_mailto_URI                          << std::endl;
   std::string manual_URI;
   if (manual_URI.length())
      std::clog
      << "manual: " << manual_URI                                 << std::endl;
   std::clog
      << "general options:"                                       << std::endl
      << "-v or --verbose      enables verbose output"                << std::endl
      << "-q or --quite        disables prompts"                      << std::endl
      << "--trial or --dry-run display what would be done without actually alterning file system or files" << std::endl
      << "-h or --help         displays brief help"                   << std::endl
      << "--response={filename} load arguments from response file"<< std::endl
      << "--responses find accessible response files and loads them"<< std::endl;
   std::clog
      << "variable assigments:"                                   << std::endl;
   FOR_EACH_IN(section,VV_Section,sections,each_section)
   {
      std::clog << "[" << section->get_label/*180821 get_section_label*/() << "]" << std::endl;
      FOR_EACH_IN(entry,VV_base_entry,section->entries,each_entry)
      {
         std::string value;
         entry->append_to_string(value);
         entry->write_key(std::clog); //180820
         std::clog
            //180820 << entry->get_key() 
            << "=" << value // at this point this should be the default value
            << " {"
            << data_type_label_table[entry->get_type()]
            << "}"
            << std::endl;
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return true;
}
//_write_help_______________________________________________________2016-08-25_/
bool Arguments::write_wizard(std::ostream &wizard_stream)            stream_IO_
{
   FOR_EACH_IN(section,VV_Section,sections,each_section)
   {
      /*180820
      std::string section_key;
      section->key_string(section_key);
      if (section_key == "arguments")
      */
      if (section->is_key_cstr("arguments"))                                          //180820
      {  // Normal/generic arguments are stored in the "argument" section
         FOR_EACH_IN(entry,VV_base_entry,section->entries,each_entry)
         {
            entry->write_wizard(wizard_stream);

            /*NYI
               if is_required(entry key)
            wizard_stream << "required: true" << std::endl;
            */

         } FOR_EACH_END(each_entry)
      }
      else
      {
         // Currently VV wizard can't handle data record [section] arguments
      }
   } FOR_EACH_END(each_section)
   return true;
}
//_write_wizard_____________________________________________________2018-05-15_/

void Arguments::display_interactive_instructions()
{
   std::clog
   << "Expected arguments where not given on the command line or response file." << std::endl
   << "Interactive mode will prompt for required arguments." <<std::endl
   << "The command line option: --quite or -q will disabled prompts" << std::endl << std::endl
   << "A prompt is displayed for each option assignment with type and default value." << std::endl
   << "Press [Enter] to accept default value or enter a new value." << std::endl
   << "Enter [,] to accept the current entry even if it is flagged as invalid." << std::endl
   << "Enter [.] to stop prompts (the default values will be retained)";
   if (sections.count() > 1)
   {
      std::clog << " for the current section." << std::endl
      << "enter [:] to stop remaining prompts." << std::endl;
   }
   std::clog
   << std::endl
   << "Dates are entered with format YYYYDDD (year and day of year)" << std::endl
   << "Filenames may be fully qualified or omit the path in the working directory." << std::endl << std::endl;
}
//_display_interactive_instructions_________________________________2016-10-16_/
bool Arguments::interactive_prompt()                               modification_
{
   if (quiet) return false;

   // Currently this only prompts for Data record assignments
   // but should provide a list of option

   bool interactive_instructions_displayed = false;

   FOR_EACH_IN(section,VV_Section,sections,each_section)
   {
      bool skip_section = false;
      std::clog << "section: " << section->get_label/*180821 get_section_label*/() << std::endl;
      /* Conceptual
      if ((section->encountered) and any entries not encountered
      {
         std::clog << "Some of the parameter related to this section have "
         "already been encountered (on the command line or from a file)"

         prompt to display current values
         if (display_current_values)
            section->write(clog);


         prompt the user to skip this section

         skip_section = xxxx
      }
      */
      if (!skip_section)
      FOR_EACH_IN(entry,VV_base_entry,section->entries,each_entry)
      {
         if (!entry->was_encountered())
         {
            if (!interactive_instructions_displayed)
            {
               display_interactive_instructions();
               interactive_instructions_displayed = true;
            }
            prompts_shown = true;
            if (entry->annotation1.length())
               std::clog << entry->annotation1 << std::endl;
            if (entry->annotation2.length())
               std::clog << entry->annotation2 << std::endl;
            std::string value;

            nat8 /*170217 VV_Data_type*/ date_type = entry->get_type();
            if (date_type < DT_COUNT)
               std::clog << "data type:" << data_type_label_table[date_type] << std::endl;
            else
            { }
            // Should also display units
            bool validated = true;
            bool accepted = true;
            do
            {  entry->append_to_string(value);
               entry->write_key(std::clog); //810820 
               std::clog 
               //180820 << entry->get_key() 
               << "=" << value << std::endl;
               std::getline(std::cin,value);
               CORN::strip_string(value,CORN::Both);
               if (value == ".") {each_entry->end(); break; }
               if (value == ":") {each_entry->end(); each_section->end(); break; }
               if (value == ",") { accepted = true; }
               if (value.length())
                  entry->set_str(value.c_str());
               else
               {  entry->set_encountered(true);
                  std::clog << "\r" << value << std::endl; // echo the current/default value
               }
               if (date_type == VV_DEN)
               {  // check file/directory existance
                  entry->append_to_string(value);
                  CORN::OS::Directory_entry_name_concrete value_DEN(value);
                  validated = CORN::OS::file_system_engine.exists(value_DEN);
               }
               /*
               conceptual entries may have validation
               valudation status and is not valid continue prompting
               {
                  show validation status
                  show curent value

               }
            */
            } while (!validated && !accepted);
         }
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return true;
}
//_interactive_prompt_______________________________________________2016-10-14_/
nat16 Arguments::compose_command_line(std::string &command)
{  nat16 count = 0;
   FOR_EACH_IN(section,VV_Section,sections,each_section)
   {
      if (sections.count() > 1)
      {  // We only need section tags if there are multiple sections
         command += "[" + section->get_label/*180821 get_section_label*/() + "]" + " ";
      }
      FOR_EACH_IN(entry,VV_base_entry,section->entries,each_entry)
      {
         std::string value;
         entry->append_to_string(value);
         command.append(entry->get_variable()/*180820 get_key()*/);
         command += "=" + value + " ";
         count++;
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return count;
}
//_compose_command_line_____________________________________________2016-10-14_/
bool Arguments::require(const std::string &argument_key_list)
{
   required_arguments.set_unique_keys(true);
   CORN::Text_list newly_required(argument_key_list.c_str(),' ');
   return required_arguments.transfer_all_from(newly_required) > 0;
}
//_require__________________________________________________________2018-05-15_/

/**  conceptual

   Arguments currently has a simple set of prompts but it would be nice
   to have a more complete editors like this.

   This could be a general data record editor
   that could be expanded for options/arguments/flags


      For each data entry item in the options record that
      has not yet been set either on the command line or
      response file(s) the user will be prompted for data item value.
      If selected_options cstring arrays are provided then
      only those items which match the selected options will be prompted
      (all others will retain the default value).
      The prompt displays the caption, units the hint, and an indicator if
      documentation/help text/URL is available.
      The user can either enter the data value, or press enter to accept the default value.
      The following control keys presses have special functions
      [Esc] to cancel (and return false)
         The caller would then likely exit the program.
      [Backspace] to display previous prompt (only one previous)
      [Tab] or [Space] or [Return] to accept default value and advance to next prompt
      [Home] to prompt all options
         (even if the had been entered on the command line or response file(s)).
      [End] or [Close] discontinue prompts and retain the remaining options with default values.

      [F1] (See help)
      [Ctrl C]  Copies the current item's (default) value to the clipboard.
      [Ctrl V]  Enters the current item values from the clipboard.

      // The following special keys may be avaiable on some keyboard
      [Help] (See help)
      [Open] prompts for a (resonse) file to load additional options.
      [New]  Reset/clears all values (including command line and response file
         and previously entered values) to defaults and starts prompting all options again.


      Help Displays the help context page document (If any) for the current parameter item.
**/

//_2016-10-16___________________________________________________________________

} // namespace CORN

