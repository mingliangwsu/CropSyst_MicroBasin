#include <corn/commontrans.h>
CORN_translator_class *common_translator = 0;
//______________________________________________________________________________
const char *common_translate(Phrase_ID  phraseID)
{  return common_translator
      ? common_translator->translate(phraseID)
      : "???";
};
//______________________________________________________________________________

