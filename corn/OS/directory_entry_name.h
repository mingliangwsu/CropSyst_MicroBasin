#ifndef directory_entry_nameH
#define directory_entry_nameH
#define DIRECTORY_ENTRY_IS_A_NAME
//____________________________________________________________________________
#include "corn/const.h"
#include "corn/primitive.h"
#include "corn/container/item.h"
#include "corn/container/text_list.h"
#include "corn/string/strconv.hpp"
#include "corn/OS/file_system_types.h"
#include <iostream>
/*
\date 2009-12-09

A:\Temp\File.txt
This path points to a file with the name File.txt, located in the directory Temp, which in turn is located in the root directory of the drive A:.
   C:..\File.txt
This path refers to a file called File.txt located in the parent directory of the current directory on drive C:.
   Folder\SubFolder\File.txt
This path denotes a file called File.txt located in SubFolder directory which in turn is located in Folder directory which is located in the current directory of the current drive (since this example gives no drive-specification).
   File.txt
This rather simple path points to a file named File.txt located in the current directory (since the path lacks a directory-specification) on the current drive (since no drive specification is present).
   \\.\COM1
This path refers to the first serial port (COM1).
*/

#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
   // and DOS, OS2, and Symbian OS
#  define DEFAULT_DIRECTORY_SEPARATORa_str "\\"
#  define DEFAULT_DIRECTORY_SEPARATORw_str L"\\"
#  define DEFAULT_DIRECTORY_SEPARATORa_chr  '\\'
#  define DEFAULT_DIRECTORY_SEPARATORw_chr L'\\'
#  define DEFAULT_DIRECTORY_SEPARATOR_IS_BACKSLASH true
#  define FILENAME_CASE_INSENSITIVITY true
#else
   // Unix, Linux, AmigaDOS, Domain OS,  MenuetOS, KolibriOS,
#  define DEFAULT_DIRECTORY_SEPARATORa_str "/"
#  define DEFAULT_DIRECTORY_SEPARATORw_str L"/"
#  define DEFAULT_DIRECTORY_SEPARATORa_chr  '/'
#  define DEFAULT_DIRECTORY_SEPARATORw_chr L'/'
#  define DEFAULT_DIRECTORY_SEPARATOR_IS_BACKSLASH false
#  define FILENAME_CASE_INSENSITIVITY false
#endif
// Not yet supported TOPS20, RISC OS, RSX-11, OPENVMS, StratusVOS
//______________________________________________________________________________
namespace CORN {
//________________________________________________________forward_declarations__
class Text_list;
namespace OS {
interface_ Directory_entry_name;
class Drive_designator;
typedef  CORN::OS::Directory_entry_name Directory_name;
typedef  CORN::OS::Directory_entry_name File_name;
typedef nat8 Path_inclusion;
//_______________________________________________________forward_declarations__/
interface_ Directory_entry_name
: public extends_interface_ CORN::Item
// Item so the entry name can be listable
// but may want to have a separate class for listables
{public:
   enum Qualification                                                            //121102
      {none_qualification
      ,relative_partial_qualification
      ,relative_strict_qualification
      ,full_qualification};                                                      //150908
      /**
      none (00) - means no path only the directory entry name (and any extension)

       Both partial and strict relative paths will include '..' paths
       to relatively locate directory entries in parent directories.

       When recursing directories, the location of the DEN would not be lost
       (one would only get a unique list of matching file names).

      relative partial (01) - means that when the composed DEN is
         relative to a specified directory (Ie. the current working directory)
         there is no relative directory qualification to specify the current/target directory.
         When recursing directorys:
         - DENs in the start/current directory will not be qualified.
         - DENs is subdirectories will have partial paths.
      relative strict (10) - means the filename always has a path
          relative to the current or specified directory;
          - DENs in the current or specified directory will be relatively qualified with '.'
          - DENS paths from subdirectorys will be prepended with '.'
          - DENs in superdirectories will have relative paths (..)
      full (11) - means an unambiguous path including all directories in the
             path of the current file system
             to the directory entry.
             With Windows filenames, this includes the drive or other
             UNC device designator.
      **/
   static const Path_inclusion include_copy                       ;
   static const Path_inclusion include_designator                 ;
   static const Path_inclusion include_ancestors_path             ;    // without designator
   static const Path_inclusion include_ancestors_path_designated  ;
   static const Path_inclusion include_parent                     ;
   static const Path_inclusion include_path                       ;
   static const Path_inclusion include_path_designated            ;
   static const Path_inclusion include_name                       ;
   static const Path_inclusion include_extension                  ;
   static const Path_inclusion include_extension_dot              ;
   static const Path_inclusion include_extension_with_dot         ;
   static const Path_inclusion include_name_extension             ;              //130123
   static const Path_inclusion include_all                        ;
   static const Path_inclusion include_all_except_extension       ;
 public:
   inline virtual ~Directory_entry_name() {}
      // Directly_entry_name is crashing on destruction, may need virtual destructor
 public:
   virtual const std::wstring &get_Windows_representation(std::wstring &buffer)const=0;
      ///< \remark The buffer is not cleared!
   virtual const std::wstring &get_Unix_representation
      (std::wstring &buffer
      ,bool represent_any_drive_designator_to_root)                     const=0;
      ///< \remark The buffer is not cleared!
   virtual const char *c_str()                                          const=0;
   virtual const wchar_t *w_str()                                       const=0;
 public: // queries
   virtual bool is_in_root()                                     affirmation_=0;
   virtual bool is_root()                                        affirmation_=0;
   virtual bool has_parent_directory()                           affirmation_=0;
   virtual bool has_extension_ASCII
      (const_ASCIIZ   valid_ext,bool case_insensitive=false)     affirmation_=0; //170224
   virtual bool has_extension_Unicode
      (const_UnicodeZ valid_ext,bool case_insensitive=false)     affirmation_=0; //170224
   virtual bool has_extension
      (const std::wstring &valid_ext,bool case_insensitive=false)  affirmation_; //170224
      /**< \return true if the extension matches valid_ext.
      \details valid_ext can be either with . or without.
      \remark case is not significant for OS's without case sensitive filename.
      */
   virtual bool has_extension_any(bool must_be_valid = false)    affirmation_=0; //160121
      ///< Returns true if the filename has a file extension.
      /// Optionally verifies that it is also valid (uses valid characters).
   virtual bool has_name(bool must_be_valid = false)             affirmation_=0; //110313
      ///< \return true if the filename has a file part.
      /// Optionally verifies that it is also valid (uses valid characters).
   virtual Directory_entry_type get_type()                              const=0; //131120  may need to be provision_
   virtual bool is_directory()                                   affirmation_=0; //120214
   virtual bool is_file()                                        affirmation_=0; //120214
   virtual bool has_in_path_wstr
      (const_UnicodeZ name_cstr
      ,Path_inclusion inclusion = include_path_designated
      ,bool substring = true)                                      affirmation_; //121121
   virtual bool has_in_path_cstr
      (const_ASCIIZ name_cstr
      ,Path_inclusion inclusion = include_path_designated
      ,bool substring = true)                                      affirmation_; //121121
      // returns true if the specified name occurs in
      // in the specified elements of the name
      // If substring is true, returns true if name is a substring
      // of any of the elements
   virtual bool find_in_path_wstr
      (const_UnicodeZ name_cstr
      ,std::wstring &found_string_appended
      ,Path_inclusion inclusion = include_path_designated
      ,bool substring = true)                                             const; //121228
   virtual bool find_in_path_cstr
      (const_ASCIIZ name_cstr
      ,std::wstring &found_string_appended
      ,Path_inclusion inclusion = include_path_designated
      ,bool substring = true)                                             const; //121228
      // Search for the specified name in directories names of the and the name itself.
      // If found, it returns the full name of the directory element that matches
      // the specified name.
   virtual bool is_valid_name_component
      (const std::wstring &name_component)                       affirmation_=0; //160121
   virtual bool is_valid()                                       affirmation_=0; //180201

 public: /** Modifiers. Each of these return the composed string
            these set's should probably be private (for VV_entry) */
 public: // gets
   virtual const std::wstring &append_designator_to(std::wstring &buffer)  const = 0; //140202
      // May be drive
   virtual const std::wstring &append_separator_to(std::wstring &buffer)   const = 0; //140202_120824
   virtual wchar_t get_separator()                                 provision_=0; //140202
   virtual const std::wstring &append_components_to
      (std::wstring &buffer
      ,Path_inclusion inclusion                      = include_all
      ,wchar_t preferred_separator = DEFAULT_DIRECTORY_SEPARATORw_chr            //140202
      ,bool append_trailing_directory_separator = false)                const=0;
      /**< \return the path in the passed buffer.
      Note that the passed buffer is not cleared (So the path is conncatenated to the string)
      Optionally the drive designator (or the the UNC) is prepended (If there is one)
      Optionally a trailing directory separator is appended
      if not it returns the same thing as get_dir.
      Trim trailing directory separator is optional.
      Both get_path methods do the same thing, but the second
      provides the return buffer, the first returns the common return buffer
      */
   virtual std::wstring get_components                                           //131119
      (Path_inclusion inclusion = include_all
      ,wchar_t preferred_seperator=DEFAULT_DIRECTORY_SEPARATORw_chr              //140202
      ,bool append_trailing_directory_separator = false)                  const;
      // Like append_components_to but returns a complete string;
   virtual const std::string& append_components_to_string
      (std::string& buffer
      ,Path_inclusion inclusion                   = include_all
      ,wchar_t preferred_seperator           = DEFAULT_DIRECTORY_SEPARATORw_chr  //140202
      ,bool append_trailing_directory_separator = false)                const=0;
      /**< \return the path in the passed buffer.
      Note that the passed buffer is not cleared (So the path is conncatenated to the string)
      Optionally the drive designator (or the the UNC) is prepended (If there is one)
      Optionally a trailing directory separator is appended
      if not it returns the same thing as get_dir.
      Trim trailing directory separator is optional.
      Both get_path methods do the same thing, but the second
      provides the return buffer, the first returns the common return buffer
      */
   inline virtual const std::string &append_to_string(std::string &buffer) const //130103
      { return append_components_to_string(buffer,include_all); }
   virtual std::wstring *render_wstring
      (Path_inclusion inclusion = include_path_designated
      ,wchar_t preferred_seperator=DEFAULT_DIRECTORY_SEPARATORw_chr) rendition_;
      /**< Similar to get_string, but instanciates the string which is returned
      and relinquished to the caller.
      */
   virtual std::wstring *render_relative_to_current_working_directory
      (Qualification qualification = relative_strict_qualification)rendition_=0; //151221
   virtual std::wstring *render_relative_to_current_working_directory_on_drive
      (const Drive_designator &drive_designator
      ,Qualification qualification = relative_strict_qualification)rendition_=0; //151221
   virtual std::wstring *render_relative_to
      (const Directory_name &qualified_reference_directory_name
      ,Qualification qualification = relative_strict_qualification)rendition_=0; //151221
      /**<
         Creates a version of this directory entry name relative to the
         specified directory or file name.

         Conceptual: These methods should take optional Qualification

         \return the rendered relative file name if the filename could be rendered.
         NULL is returned if this name is already relative,
         or if the relative path is not valid in the file system.
         <P>
         Cases
         This = C:\A\B\C\D\E\F.ext
         ref  = C:\A\B\C\X\Y\Z
         rel  = ..\..\..\D\E\F.ext

         This = C:\A\F.ext
         ref  = C:\A\B\C\X\Y\Z
         rel  = ..\..\..\..\..\F.ext

         This = C:\A\B\C\D\E\F.ext
         ref  = C:\A\B\C
         rel  = D\E\F.ext


         This = F.exe
         ref  = C:\A\B
         rel  = C:\A\B\F.exe
      **/

   virtual Directory_entry_name *render_with_respect_to                          //180104
      (const Directory_entry_name &respect_DEN)                    rendition_=0;
      /**<
         This function renders a DEN from old_DEN
         so it is qualified with respect to the respect_DEN.

         This is useful when needing to relocation file names.


   // If old_DEN is
   //    C:\Simulation\Projects\Database\test\aaaa.ext
   // and respect_DEN is
   //    C:\Simulation\Projects\projectA\Scenarios\test\Database\bbbb.ext
   // it will render
   //    C:\Simulation\Projects\projectA\Scenarios\test\Database\aaaa.ext
   // If old_DEN is
   //    C:\Simulation\Projects\projectA\Scenarios\test\Database\aaaa.ext
   // and respect_DEN is
   //    C:\Simulation\Projects\projectB\Scenarios\test\Database\bbbb.ext
   // it will render
   //    C:\Simulation\Projects\projectB\Scenarios\test\Database\aaaa.ext
      **/

   virtual CORN::Text_list & append_path_list_to // was get_path_list
      (CORN::Text_list &buffer
      ,Path_inclusion inclusion = include_path_designated)              const=0;
      /**< A list of the directory names comprising the path is appended to the buffer
      The buffer is NOT cleared so this function can be used to compose paths.
      if (include_designator) is true, the drive designator is appended to the buffer first.
      Note that you will usually not want the designator appended if you are concatentating paths!
      the filename and extension is NOT appended to the buffer
      \return the passed buffer.
      */
   virtual const std::wstring &get_name()                               const=0;
   virtual const std::wstring &get_extension()                          const=0;
   virtual const std::wstring &append_name_with_extension_to
      (std::wstring &result)                                            const=0;
   virtual const std::wstring &append_name_to(std::wstring &result)     const=0; //131007
   virtual const std::wstring &get_name_with_extension(std::wstring &result)const=0;
public:  // Queries:
   virtual bool is_qualified
      (bool and_fully_qualified_with_drive_designator = true)    affirmation_=0;
      /**< \return true if the name is fully or partially qualified
         either relative or fully_qualified .
       With or without the drive designator.
      */
   virtual bool is_relative()                                      affirmation_;
      /**< \return true if the name has a relative path
         Note that an unqualified name is also considered to be relative.
         Use has_relative_path() if you do not want to consider unqualifed names.
      **/
   virtual bool has_relative_path()                              affirmation_=0;
      /**< \return true if there is a path and it is relative.
      **/
   virtual bool has_designator_special()                         affirmation_=0; //171204
      /**< \return true if the first path item is a special designator
         // I.e. ~  or ~CONTEXT:
      **/
   virtual int compare_including
      (const Directory_entry_name &other
      ,Path_inclusion inclusion = include_all )                         const=0;
      /**< \brief Lexicorigraphically compares the respective selected elements specified in the inclusion.
      \details When compiled under Windows, the comparison is case insensitive
      */
   virtual nat16 get_length()                                           const=0; //170225
      /**< \returns the number of character in the filename string;
      */
 public:  //
   virtual const Directory_name &get_parent_directory_name_qualified()  const=0; //110307
        //This should not be used unless it is certain there is parent directory,
        // as there might not be parent path (in the case of relative filenames).
        // use get_path_directory_name if there needs to be a check
 public:
   virtual const Directory_name *get_path_directory_name()              const=0;
   virtual const Directory_entry_name &set_DEN
      (const Directory_entry_name &to_copy_from)                 assignation_=0;
   virtual const Directory_entry_name &set_cstr
      (const char *to_copy_from)                                 assignation_=0;
   virtual const Directory_entry_name &set_wstr
      (const wchar_t *to_copy_from)                              assignation_=0;
   inline virtual const Directory_entry_name &set_str                            //130115
      (const std::string &to_copy_from)                             assignation_
       /*deprecated, use set_string*/
      { return set_cstr(to_copy_from.c_str()); }
   inline virtual const Directory_entry_name &set_wstring                        //131115
      (const std::wstring &to_copy_from)                            assignation_
      { return set_wstr(to_copy_from.c_str()); }                                 //131119
   inline virtual const Directory_entry_name &set_string                         //130115
      (const std::string &to_copy_from)                             assignation_
      { return set_cstr(to_copy_from.c_str()); }
   inline void qualify(){}
      //Qualify is provided for compatability with the old file_sys
      //It is no longer needed in this class because file names are now always
      //qualified.
   friend std::ostream& operator<<(std::ostream& os, const Directory_entry_name& dt);//140124
};
//_2009-12-19____________________________________________Directory_entry_name__/
} } // namespace CORN OS
//_2012-12-29___________________________________________________________________
#define CORN_FILE_NAME_EXISTS(filename) (CORN::OS::file_system_engine.exists(filename))
#endif

