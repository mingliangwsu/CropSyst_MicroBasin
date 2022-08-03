#ifndef FILE_SYSTEM_ENGINE_QTH
#define FILE_SYSTEM_ENGINE_QTH

#include "corn/OS/file_system_engine_common.h"
#include "corn/container/text_list.h"
namespace CORN { namespace OS {
//_______________________________________________________forward declarations__/

class File_system_engine_Qt
: public extends_ File_system_engine_common  //
{
public:
   File_system_engine_Qt();
   virtual nat32 list_names_in // was list_entry_names_in                                             //160826
      (const Directory_name & directory_name
      ,CORN::Text_list *file_name_list_unqual
      ,CORN::Text_list *directory_name_list_unqual
      )                                         const;
/*161029
   virtual nat32 list_names_in // was list_entry_names_in                                             //160826
      (const Directory_name & directory_name
      ,CORN::Text_list *file_name_list_unqual
      ,CORN::Text_list *directory_name_list_unqual
      ,const Seclusion &seclusion)                                         const;
*/

   virtual nat32 list_entry_names_in_deprecated
      (const Directory_name & directory_name
      ,CORN::Text_list *file_name_list_unqual
      ,CORN::Text_list *directory_name_list_unqual
      ,const wchar_t *name_wild_card
      ,const wchar_t *extension_filter
      ,const CORN::Text_list *exclude_directories)                         const;
      // This method is deprecated, use Seclusion form

 protected:  // Eventually make this public, put in interface, and/or implement as function in CORN::Text_list
   virtual bool matches_any_in                                                   //151212
      (const std::wstring &name_with_ext
      ,const CORN::Text_list &wild_card_patterns_to_compare
      ,bool case_insensitive = false)                                affirmation_;
      // This method is probably obsolete with new Seclusion classes
};
//_2015-03-19___________________________________________File_system_engine_Qt__/
#endif
} } // namespace CORN OS
//______________________________________________________________________________
