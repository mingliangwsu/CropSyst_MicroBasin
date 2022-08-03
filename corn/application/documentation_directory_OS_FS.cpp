#include "documentation_directory_OS_FS.h"
#include <string.h>
#include "corn/string/strconv.hpp"
#include "corn/OS/file_system_engine.h"
namespace CORN    {
namespace OS_FS   {
//______________________________________________________________________________
const char *document_type_label_table[] =
{ "info"
, "manual"
, "help"
, "tutorial"
, "FAQ"
, "explaination"
, "history"
};
//______________________________________________________________________________

Documentation_directory::Documentation_directory
(const OS::File_name &_associated_program_filename_qualified)
: Adjunct_directory
   (_associated_program_filename_qualified
   ,false)  // Doc directory is usually preexisting so don't need to create      //130116
{
   for (nat8 dt = 0; dt <= DOCUMENT_TYPE_COUNT; dt++)                            //141114
   {  document_filename[dt] = 0;
      document_dirname[dt] = 0;
   }
}
//______________________________________________________________________________
CORN::OS::File_name *Documentation_directory::find_document_filename(const std::wstring &document_name) rendition_
{
      /* NYI
         The unqualified_URL can have one of the following forms:

         %keyword%/path/filename.exe#link
         %keyword%/filename.exe#link
         path/filename.exe#link
         filename.exe#link
         where %keyword% is one of the following:

         %tutorial%
         %help%
         %manual%
         %FAQ%
         %history%
         %explaination%
      */

      /* NYI
         The #link is optional and would be as in an HTML document anchor/link.
         The optional path may consiste of one or more subdirectories.
         In the %keyword% forms, the target document filename is composed by replacing the
         %keyword% with the respective documentation subdirectory
         and prepending this directory's path.
         If the keyword is omitted, the target document filename is composed
         by simply prepending this directory's path.

      */
      // First search for documents such as XXXX.html
      CORN::OS::File_name *found_document = find_file_name
         (document_name
         ,OS::File_system::subdirectory_recursion_inclusive);                      //150908
      if (!found_document)
      {  // Maybe it is a directory of html documents which should have an
         // index.html (or index.htm) document
         OS::File_system_logical::Directory document_directory(*this,document_name,false);
         if (document_directory.exists())
            found_document = document_directory.find_file_name
               (L"index"
               ,OS::File_system::subdirectory_recursion_inclusive);              //150908
               // I think these were originally fully qualified,
               // but may want the qualifiction mode optional (add parameter)
      }
   return found_document;
}
//_2012-04-02___________________________________________find_document_filename_/
CORN::OS::File_name * Documentation_directory::find_document_filename_string(const std::string &unqualified_URL) rendition_
{  std::wstring unqualified_URL_wstring;  CORN::string_to_wstring(unqualified_URL,unqualified_URL_wstring);
   return find_document_filename(unqualified_URL_wstring);
}
//_2013-02-13____________________________________find_document_filename_string_/
CORN::OS::File_name * Documentation_directory::find_document_filename_cstr(const char *unqualified_URL) rendition_
{  std::wstring unqualified_URL_wstring;  CORN::ASCIIZ_to_wstring(unqualified_URL,unqualified_URL_wstring);
   return find_document_filename(unqualified_URL_wstring);
}
//_2013-02-13____________________________________find_document_filename_string_/
CORN::OS::File_name * Documentation_directory::find_document_filename_wstr(const wchar_t *unqualified_URL) rendition_
{  std::wstring unqualified_URL_wstring(unqualified_URL);
   return find_document_filename(unqualified_URL_wstring);
}
//_2013-02-13____________________________________find_document_filename_string_/
const CORN::OS::File_name &Documentation_directory::provide_document_filename(Document_type doc_type)provision_
{  if (!document_filename[doc_type])
   {  document_filename[doc_type] = dynamic_cast<CORN::OS::File_name_concrete *>
         (find_document_filename_cstr(document_type_label_table[doc_type]));
      if (!document_filename[doc_type])
         document_filename[doc_type] = new CORN::OS::File_name_concrete(*this,document_type_label_table[doc_type],L"htm");
      if (!CORN::OS::file_system_engine.exists(*document_filename[doc_type]))
      {  delete document_filename[doc_type];
         document_filename[doc_type] = new CORN::OS::File_name_concrete(*this,document_type_label_table[doc_type],L"HTML");
      }
   }
   return *document_filename[doc_type];
}
//______________________________________________________________________________
const CORN::OS::Directory_name &Documentation_directory::provide_document_dirname(Document_type doc_type)provision_
{  if (!document_dirname[doc_type])
   {  document_dirname[doc_type] = new CORN::OS::Directory_name_concrete(*this,document_type_label_table[doc_type]);
   }
   return *document_dirname[doc_type];
}
//_2014-11-14___________________________________________________________________
} // namespace OS_FS
} // namespace CORN

