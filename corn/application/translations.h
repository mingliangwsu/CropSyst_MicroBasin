#ifndef translationsH
#define translationsH
//#include "corn/container/association.h"
#include "corn/container/bilist.h"
#include "corn/container/search_tree.h"
namespace CORN {
namespace OS_FS {
class Program_directory;
class Application_directory;                                                     //141119
class Suite_directory;                                                           //141119
}
#define TRANSLATIONS_AUTOLOAD_PHRASES
//#define CORN_TRANSLATION_SUPPORT_UNICODE
//______________________________________________________________________________
class Translation  // The phrase that have translations
: public CORN::Item
{
   public:
   class Translated
   : public CORN::Item
   {
   public:
      bool is_Unicode;
      std::string language;
      #ifdef _UNICODE
      std::wstring text;
      #else
      std::string text;
      #endif
   public:
      Translated
         (const std::string &_language
         ,const std::string &_text);
      #ifdef _UNICODE
      Translated
         (const std::string &_language
         ,const std::wstring &_text);
      #endif

   inline virtual bool is_key_string(const std::string &key)        affirmation_  //180820
      { return language.compare(key) == 0; }

/*180820  was probably only used for find_cstr now using is_key
      inline virtual const char *get_key() const {return language.c_str(); };
*/      
      #ifdef _UNICODE
      inline const std::wstring *get_text() const { return &text; };
      #else
      inline const std::string *get_text() const { return &text; };
      #endif
    private:
      inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format

   };
public:
   std::string ID; // This is the constant for the phrase usually of the form L_xxxxxx
   // Warning currently the primary text must be ANSI
   // In order to allow Unicode, I will need to add get_key() that takes wchar_t

   std::string notes;

   #ifdef _UNICODE
   std::string primary_text;
      // Currently in the case of Unicode support, the primary text must be ANSI for the lookup
   // NUI   const std::wstring *primary_text; // nilable reference to the Translated for en
   #else
   const std::string *primary_text; // nilable reference to the Translated for en
   #endif
   CORN::Bidirectional_list translations; // list of translated

public:
   inline Translation(const std::string _ID)
      : CORN::Item()
      , ID(_ID)
      #ifdef _UNICODE
      , primary_text()
      #else
      , primary_text(0)
      #endif
      , translations()
      {}
public:
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return 
   #ifdef _UNICODE
      key == primary_text;
   #else
      primary_text ? (key.compare(*primary_text) ==0) : false;
   #endif
      
       }

/*180820  was probably only used for find_cstr now using is_key

   virtual const char *get_key() const
   #ifdef _UNICODE
      {return primary_text.c_str(); }
   #else
      {return primary_text ? primary_text->c_str() : 0; }
   #endif
*/      
   
   #ifdef _UNICODE
   const wchar_t
   #else
   const char
   #endif
      *get_translation(const char *language_code) const;
   // obs const char *get_translation_Unicode() const { return translation_Unicode.c_str(); };
 private:
   inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format

};
//______________________________________________________________________________
class Translations_phrases
: public CORN::Bidirectional_list /*180101 Association_list*/ // List of Translation
{
public:
   std::string primary_language_code;
public:
#ifdef TRANSLATIONS_AUTOLOAD_PHRASES

   unsigned long load_phrases
      (const char *_primary_language_code
      ,const CORN::OS_FS::Program_directory     &program_directory
      ,const CORN::OS_FS::Application_directory  *application_directory =0 // Optional          //141119
      ,const CORN::OS_FS::Suite_directory        *suite_directory       =0 // Optional          //141119
      );
#endif      
public:
   unsigned long load_translations_ANSI
      (const char *primary_language_code,const char *filename);
   unsigned long load_translations_Unicode
      (const char *primary_language_code,const char *filename);
   void load_translation_Unicode
      (const char *language_code,const char *filename);
private:
   std::string &Unicode_to_codepageXXXX
   (const std::wstring &str_Unicode,std::string &str_codepage
   ,int unicode_codepage[][2]                                                    //101116
   ,int codes);
};
//________________________________________________________Translation_phrases__/
}; // namespace CORN

#endif

