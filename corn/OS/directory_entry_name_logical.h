#ifndef directory_entry_name_logicalH
#define directory_entry_name_logicalH
#include "corn/const.h"
#include "corn/OS/directory_entry_name_abstract.h"
//_Forward declarations_________________________________________________________
namespace CORN {
   class Text_list;
   class Ustring;
namespace OS {
#define Directory_name_logical Directory_entry_name_logical
#define File_name_logical Directory_entry_name_logical
//______________________________________________________________________________
class Directory_entry_name_logical    // rename this to Directory_name_independent
: public extends_ Directory_entry_name_abstract
{  // Implements/Recognizes file and directory names from various OS.
   // The following will be 0 until the path is extracted.
   contribute_ CORN::OS::Directory_entry_name *qualified_path;
public: // 'structors
   Directory_entry_name_logical();                                               //120320
      //defaults to the current working directory
   Directory_entry_name_logical(const Drive_designator &drive_designator);
      // the current working directory on the specified drive
      // (applicable only to Windows/DOS and AmigaDOS directory entry names)
   Directory_entry_name_logical(const char         *raw_name/*=0*/
      ,Directory_entry_type type = unknown_entry);
   Directory_entry_name_logical(const wchar_t      *raw_name/*=0*/
      ,Directory_entry_type type = unknown_entry);                               //120202
   Directory_entry_name_logical(const std::wstring &raw_name
      ,Directory_entry_type type = unknown_entry);
   Directory_entry_name_logical(const std::string  &raw_name
      ,Directory_entry_type type = unknown_entry);
   Directory_entry_name_logical(const std::wstring *raw_name
      ,Directory_entry_type type = unknown_entry);                               //120309
   Directory_entry_name_logical(const std::string  *raw_name
      ,Directory_entry_type type = unknown_entry);                               //120309
   Directory_entry_name_logical
      (const Directory_entry_name &raw_name
      ,Path_inclusion inclusion = CORN::OS::Directory_entry_name::include_copy);
      /**< inclusion can be used when the new directory entry name  is derived
      from parts of the original filename. **/
   Directory_entry_name_logical                                                  //120321
      (const Directory_entry_name &raw_name
      ,const Extension &extension
      ,Directory_entry_type type = file_entry);
      //< Use this constructor to create an copy of the name replacing the extension.
   #ifndef DIRECTORY_ENTRY_IS_A_NAME
   Directory_entry_name_logical                                                  //091107
      (const File_system::Directory &_path_directory
      ,const std::wstring &_name
      ,Directory_entry_type type = unknown_entry);
   Directory_entry_name_logical                                                  //091107
      (const File_system::Directory &_path_directory
      ,const std::wstring &_name
      ,const std::wstring &_extension
      ,Directory_entry_type type = file_entry);
      ///< Used when constructing a new filename and extension in
      ///< the specified directory.
   #endif

   /* Conceptual
   Directory_entry_name_logical                                                  //130123
      (const Directory_name &_path_directory_name
      ,const Directory_entry_name &name_extension);
   */
   Directory_entry_name_logical                                                  //100214
      (const Directory_name &_path_directory_name
      ,const wchar_t *_name
      ,const wchar_t *_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //120213
      (const Directory_name *_path_directory_name
      ,const char *_name
      ,const char *_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //120518
      (const Directory_name &_path_directory_name
      ,const char *_name
      ,const char *_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //130905
      (const Directory_name &_path_directory_name
      ,const std::string &_name
      ,const char *_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //130905
      (const Directory_name &_path_directory_name
      ,const char *_name
      ,const std::wstring &_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //130905
      (const Directory_name &_path_directory_name
      ,const std::string &_name
      ,const std::wstring &_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //091111
      (nat16 CSIDL
      ,const std::wstring &_name
      ,const std::wstring &_extension
      ,Directory_entry_type type = file_entry
//NYI      ,Text_list *additional_path_given = 0   // optional
      );
      // Use when we want a directory in one of the canonical directories
      // I.e. User's home, local settings, program files etc.. denoted by the CSIDL
      // Additional path is in the form   path/path
   Directory_entry_name_logical                                                  //091107
      (const Directory_name &_path_directory
      ,const std::wstring &_name
      ,const std::wstring &_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //110313
      (const Directory_name &_path_directory
      ,const std::wstring &_name_and_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //120321
      (const Directory_name &_path_directory
      ,const std::string &_name_and_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //110313
      (const Directory_name &_path_directory
      ,const char *_name_and_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //120321
      (const Directory_name &_path_directory
      ,const wchar_t *_name_and_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //091107
      (const Directory_name &_path_directory
      ,const std::wstring &_name
      ,const char *_extension
      ,Directory_entry_type type = file_entry);
   Directory_entry_name_logical                                                  //130207
      (const Directory_name &_path_directory
      ,const File_name      &_file_name);

   Directory_entry_name_logical                                                  //130729
      (const CORN::Text_list &decomposed_name
      ,Path_inclusion what_decomposed_name_includes = include_all
      ,Path_inclusion inclusion = include_all);
      // The directory entry name elements are taken from the decomposed name
      // This constructor with the default options is the inverse of get_path_list().


   virtual ~Directory_entry_name_logical();
public: // queries
   virtual const char *c_str()                                            const;
   virtual const wchar_t *w_str()                                         const;
   //__________________________________________________________________________/
   virtual bool is_relative()                                      affirmation_;
      /**< \return true if the name has a relative (or partial) path
         Note that an unqualified name is also considered to be relative.
         Use has_relative_path() if you do not want to consider unqualifed names.
      **/
   virtual bool has_relative_path()                                 affirmation_;
      /**<  \return true if there is a path and it is relative (or partial).
      **/
   bool is_extension_ASCII
      (const_ASCIIZ valid_ext,bool case_insensitive=false)         affirmation_;
public: // name composition  (implements Directory_entry_name)
   virtual const std::wstring &append_components_to
      (std::wstring &buffer
      ,Path_inclusion inclusion = include_all
      ,wchar_t preferred_seperator = DEFAULT_DIRECTORY_SEPARATORw_chr            //140202
      ,bool append_trailing_directory_separator = false)                  const; //091103
   virtual const std::wstring &get_name()                                 const;
   virtual const std::wstring &get_extension()                            const;
   virtual const CORN::OS::Directory_name &get_parent_directory_name_qualified()  const;
public:
   virtual const CORN::OS::Directory_name *get_path_directory_name()      const;
public:  //
   virtual const Directory_entry_name & set_DEN
      (const Directory_entry_name &to_copy_from)                   assignation_;
   virtual const Directory_entry_name & set_cstr
      (const char *to_copy_from)                                   assignation_;
   virtual const Directory_entry_name & set_wstr
      (const wchar_t *to_copy_from)                                assignation_;

   virtual const Directory_entry_name & replace_name     (const std::wstring& new_name) modification_;
   virtual const Directory_entry_name & replace_name_str (const std::string&  new_name) modification_;
   virtual const Directory_entry_name & replace_name_cstr(const char *        new_name) modification_;
//NYI   virtual const Directory_entry_name & replace_extension(std::wstring *new_name) modification_;
//NYI   virtual const Directory_entry_name & replace_extenstion_cstr(std::wstring *new_name) modification_;

 protected: // name assignment
   // These sets should only be used in construction.
   void clear_decomposition()                                     contribution_;
   virtual void decompose()                                       contribution_; //110307
   inline Directory_entry_name_logical *confirm_concrete()                 const
      { return new Directory_entry_name_logical(""); }
   // this constructor is only here for the compiler to ensure this
   // class has all methods implemented
 protected:
   void construction_compose()                                    construction_;
};
//___________________________________________ Directory_entry_name_logical __/
} } // namespace CORN OS

#endif

