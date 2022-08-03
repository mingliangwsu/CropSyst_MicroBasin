#include "STATSGO_SSURGO_types.h"
#include <string.h>
#include <stdlib.h>
namespace USDA_NRCS {
//namespace STATSGO2_SSURGO {
//______________________________________________________________________________
nat32 render_key_ID(const char *key)
{
   const char *colon_char = strchr(key,':'); //
   return atoi(colon_char ? colon_char+1: key);
   /*
         size_t colonpos = _key.find(":");
         if (colonpos != std::string::npos)
         {  std::string MUkey_str(_key,0,colonpos);
            std::string unique_key_str(_key,colonpos+1);
            MUkey = atoi(MUkey_str.c_str());
            unique_key = atoi(unique_key_str.c_str());
         }else
            unique_key = MUkey = atoi(_key.c_str());
*/
}
//_2011-11-08___________________________________________________________________
} // namespace USDA_NRCS

