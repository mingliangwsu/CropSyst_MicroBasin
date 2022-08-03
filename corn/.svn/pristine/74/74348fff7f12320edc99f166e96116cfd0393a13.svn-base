#ifndef translationH
#define translationH
#include <corn/container/association.h>
#include <corn/container/search_tree.h>
namespace CORN {
class Program_directory;
//______________________________________________________________________________
class Translation
: public CORN::Association
{
public:
   std::string english;
   bool translation_is_Unicode;
   std::string translation_ANSI;
   //NYI std::wstring translation_Unicode;
public:
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return english == key; }

/*180820  was probably only used for find_cstr now using is_key
   virtual const char *get_key() const {return english.c_str(); };
*/   
   const char *get_translation_ANSI() const { return translation_ANSI.c_str(); };
   // NYI const char *get_translation_Unicode() const { return translation_Unicode.c_str(); };
};
//______________________________________________________________________________
class Translation_phrases
: public CORN::Association_search_tree
{
public:
   void load_phrases
      (const char *language_codes
      ,const CORN::Program_directory &program_directory
      );
   void load_translation_ANSI(const char *language_code,const char *filename);
   // NYI void load_translation_Unicode(const char *language_code,const char *filename);
};
//________________________________________________________Translation_phrases__/
}; // namespace CORN

#endif

