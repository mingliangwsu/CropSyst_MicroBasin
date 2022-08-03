#ifndef translatorH
#define translatorH
#include "corn/std/std_iostream.h"
/*
   Most of the rlib classes use the common translator
   and the translator_class, however, if you don't want
   to use the translator_class, #undef USE_CORN_TRANSLATOR_CLASS
   The translate() functions will use character strings
   instead of translation phrase_ID tags
*/
#include "corn/language.h"
/*
   list_available_languages lists the codes/names for the languages
   and dialects available in the file to the provided output stream.

   Normally this function can be called on stdout or stderr to display
   the languages to choose from, and the program may then prompt the
   user to enter the code for the language to use.

   When using HARDCODE_PHRASES, the language_init must be called first!
*/
#ifndef PHRASES_FILE
#pragma message "Phrases file not defined using default phrases.lng"
#define PHRASES_FILE "phrases.lng"
#endif
//______________________________________________________________________________
void list_available_languages(STD_NS ostream &dest,const char *phrases_filename);
enum common_phrases {
      COMMON_NO_TRANSLATION,
#include PHRASES_FILE
      COMMON_PHRASES_COUNT
};
extern CORN_translator_class *common_translator;
// Common translator instanciated by the program.
// (I usually do this in main).
const char *common_translate(Phrase_ID  phraseID);
#define T(x) common_translate(x)
//______________________________________________________________________________
#endif
//commontrans
