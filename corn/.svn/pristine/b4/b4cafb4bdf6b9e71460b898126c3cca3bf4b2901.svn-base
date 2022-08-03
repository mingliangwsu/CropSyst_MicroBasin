#ifndef file_type_descriptionH
#define file_type_descriptionH

#  include "corn/OS/directory_entry_name_concrete.h"
#if ((__BCPLUSPLUS__ > 0) && (__BCPLUSPLUS__ <= 0x0550))
// Still need to have std::string for CropSyst editors
#include <string>
#endif

/*
   Filtered_filename extends the Smart_filename adding the ability
   to recognize different filename extension and type filters.
*/
namespace CORN { namespace OS {       
//______________________________________________________________________________
class File_type_description
: public Item                                                                    //990806
{protected:
   std::wstring preferred_extension;
   std::wstring filter_label;
   std::wstring wildcard_filter;
 public:
   File_type_description
      (const wchar_t *_preferred_extension = 0 // The preferred extension (without DOT)
      ,const wchar_t *_filter_label = 0        // Short description of the file type
      ,const wchar_t *_wildcard_filter = 0);   // I.e.  *.DAT if (0), *. and preferred extension will be used
   File_type_description
      (const char *_preferred_extension = 0 // The preferred extension (without DOT)
      ,const char *_filter_label = 0        // Short description of the file type
      ,const char *_wildcard_filter = 0);   // I.e.  *.DAT if (0), *. and preferred extension will be used
   File_type_description(const File_type_description &to_copy);                  //990227
 public: // Association overrides
   inline virtual bool is_key_wstring(const std::wstring &key)              affirmation_  //180820
      { return preferred_extension == key; }

/*180820  was probably only used for find_cstr now using is_key
 
   inline virtual const wchar_t *get_key_wide()                            const { return preferred_extension.c_str();} //030117
*/
   //170424 replaced with label_string virtual const char *label_cstr(char *buffer)                 const;
   virtual const char *label_string(std::string &buffer)                   const;
   inline const std::wstring  &get_preferred_extension()                   const { return preferred_extension; }
   inline const std::wstring  &get_filter_label()                          const { return filter_label; }
   inline const std::wstring  &get_wildcard_filter()                       const { return wildcard_filter; }

   inline const wchar_t *get_preferred_extension_wstr()                    const { return preferred_extension.c_str(); }
   inline const wchar_t *get_filter_label_wstr()                           const { return filter_label.c_str(); }
   inline const wchar_t *get_wildcard_filter_wstr()                        const { return wildcard_filter.c_str(); }
          void set_filter_label_string(const std::string  &new_filter_label)    modification_;   //000928
   inline void set_filter_label_wstring(const std::wstring  &new_filter_label)    modification_{ filter_label = new_filter_label; }   //131115
 private:
   //180813 NYN inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format

};
//_1999-01-03___________________________________________________________________
//______________________________________________________________________________
} } // namespace CORN OS

#endif
// filtered_filename.h


