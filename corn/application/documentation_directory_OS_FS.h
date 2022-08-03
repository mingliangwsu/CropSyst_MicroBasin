#ifndef documentation_directory_OS_FSH
#define documentation_directory_OS_FSH
#include "corn/application/adjunct_directory_OS_FS.h"
#include "corn/const.h"
namespace CORN    {
namespace OS_FS   {
//______________________________________________________________________________
enum Document_type
{ general_info_doctype
, manual_doctype
, help_doctype
, tutorial_doctype
, FAQ_doctype
, explaination_doctype
, history_doctype
, DOCUMENT_TYPE_COUNT
};
//______________________________________________________________________________
class Documentation_directory
: public Adjunct_directory
{
   // The documenation directory should not be considered a physicial
   // directory, is is a virtual construct,
   // for finding and retrieving documentation associated with a program.
   // Documentation may be associated with programs in a variety of ways.
   // This directory currently supports two modes:

   // 1.  Associated folder
   //     In this mode the program directory is stored in the same
   //     folder as the executable (usually specified in the constructor)
   //     and has the same name (with no extension).
   //     Generally a program is located in an application's installation
   //     folder I.e.                   C:\Programs\applicationX\programy.exe
   //     The associated folder will be C:\Programs\applicationX\programy
   //     and will have files such as   C:\Programs\applicationX\programy\tutorial.htm
   //                                   C:\Programs\applicationX\programy\help.hlp
   //                                   C:\Programs\applicationX\programy\default.ini
   // 2.  Independent folder
   //     In this mode the program directory is not associated with
   //     the program file and may be stored in some other folder.
   //     For example under UNIX conventionally, executables are stored
   //     separate directories from associated files
   //     /usr/local/applicationX/bin/programy
   //     /usr/local/applicationX/man/programy.man
   //     /usr/local/applicationX/help/programy.htm
   //     $home/.applicationX/programy.ini  (user options for the current user)

   // The program directory class necessarily doesn't dictate
   // either of these directory structures, however
   // the associated folder mode is the default and recommended mode of operation
   // and is complete in its implementation.
   // Override this class to create more complicated directory structures
   // for associated application and program files (I.e. for the UNIX example above).

protected:
   // Common files.
   // These files are all optional.
   // You can use the exists() method to check if the file actually exists.
   // The filenames will be setup by the constructor and will be fully qualified
   // Documentation files:
   // You can use the invoke_viewer() method to open the file with a viewing
   // program that has been associated to the file type by the operating system
   // file system or Windows Explorer.
      // The following can actually be Directory_name pointers
      // but using Directory_name_concrete so the filenames can be conveniently
      // seen in the debugger

   provided_ OS::Directory_name_concrete *document_dirname [DOCUMENT_TYPE_COUNT];//141114
   provided_ OS::File_name_concrete      *document_filename[DOCUMENT_TYPE_COUNT];//141114
public:
   Documentation_directory(const OS::File_name &_assoc_program_filename_qual);

      // In Web mode, the filename paths are replaced with URL_root
      // if the respective file(s) are not found on the local machine.
      // This allows the option of not having to install
      // documentation files on the local machine and instead
      // load the most uptodate documentation off the web.
      // Thus you can have a small installation foot print with
      // out local documentation.
      // I.e.  if URL_root is http://X.Y.Z/applicationX/programY
      //    C:\Programs\applicationX\programY\tutorial.htm
      // will become
      //    http://X.Y.Z/applicationX/programY/tutorial.htm
      // if replaces_local_directory is specified
      // the part of the filenames that match the value of replaces_local_directory
      // is replaced

      // I.e.  if URL_root is http://X.Y.Z/path/applicationX
      //    C:\Programs\applicationX
      // will become
      //    http://X.Y.Z/path/applicationX/programY/tutorial.htm
      // This option is useful when the URL path is some what different
      // than the directory structure for the installation.
      // This method can be called multiple times if, for example,
      // web versions of some files are stored in different folders
      // that in the local installation.
public: // fluent interface

   const OS::File_name &provide_document_filename(Document_type doc_type)provision_; //141114

   inline const  OS::File_name &tutorial_document()                    provision_ { return provide_document_filename(tutorial_doctype); }
   inline const  OS::File_name &help_document()                        provision_ { return provide_document_filename(help_doctype); }
   inline const  OS::File_name &manual_document()                      provision_ { return provide_document_filename(manual_doctype); }
   inline const  OS::File_name &FAQ_document()                         provision_ { return provide_document_filename(FAQ_doctype); }
   inline const  OS::File_name &history_document()                     provision_ { return provide_document_filename(history_doctype); }

   const OS::Directory_name &provide_document_dirname(Document_type doc_type)provision_; //141114
   inline const  OS::Directory_name  &tutorial()                       provision_ { return provide_document_dirname(tutorial_doctype); }
   inline const  OS::Directory_name  &help()                           provision_ { return provide_document_dirname(help_doctype); }
   inline const  OS::Directory_name  &manual()                         provision_ { return provide_document_dirname(manual_doctype); }
   inline const  OS::Directory_name  &FAQ()                            provision_ { return provide_document_dirname(FAQ_doctype); }
   inline const  OS::Directory_name  &history()                        provision_ { return provide_document_dirname(history_doctype); }
   inline const  OS::Directory_name  &explaination()                   provision_ { return provide_document_dirname(explaination_doctype); }

   /// The rendered directory name (if found) is reliquished to to the caller.
   CORN::OS::File_name * find_document_filename       (const std::wstring &unqualified_name) rendition_;
   // The following forms of find_document_filename are provided for convenience
   CORN::OS::File_name * find_document_filename_string(const std::string &unqualified_name) rendition_;
   CORN::OS::File_name * find_document_filename_cstr  (const char *unqualified_name) rendition_;
   CORN::OS::File_name * find_document_filename_wstr  (const wchar_t *unqualified_name) rendition_;


      /**<
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

         The #link is optional and would be as in an HTML document anchor/link.
         The optional path may consiste of one or more subdirectories.
         In the %keyword% forms, the target document filename is composed by replacing the
         %keyword% with the respective documentation subdirectory
         and prepending this directory's path.
         If the keyword is omitted, the target document filename is composed
         by simply prepending this directory's path.

         If the composed qualified target document filename is not found,
         the filename.exe is recursively searched in this directory.
         If it is still not found, the program's (usually the parent) directory
         is recursively search.
         If it is still not found, the application's
         (usually the program's parent) directory
         (if any) is recursively search.
         If it is still not found, the Suite directory (if any) is
         recursively searched.

      **/
};
//______________________________________________________________________________
} // namespace OS_FS
} // namespace CORN
#endif

