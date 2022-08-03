#include "common/geomatics/Canada_province_code.h"
#include "corn/string/strconv.hpp"
#include <string.h>
//______________________________________________________________________________
// Note the ordering of these is simply sorted
// I don't know if there is a or what matching code number there may be for the states
Canada_Province_code Canada_province_code[] =
{{"__",""} // Unassigned
,{"AB","Alberta"}
,{"BC","British Columbia"}
,{"MB","Manitoba"}
,{"NB","New Brunswick"}
,{"NL","Newfoundland and Labrador"}
,{"NT","Northwest Territories"}
,{"NS","Nova Scotia"}
,{"NU","Nunavut"}
,{"ON","Ontario"}
,{"PE","Prince Edward Island"}
,{"QC","Quebec"}
,{"SK","Saskatchewan"}
,{"YT","Yukon"}
,{0,0}
};
//______________________________________________________________________________
int lookup_Canada_province_number(const char *province_name_or_code)
{  for (int s = 0; Canada_province_code[s].code; s++)
   {  if (stricmp(Canada_province_code[s].code,province_name_or_code) == 0) return s;
      if (stricmp(Canada_province_code[s].name,province_name_or_code) == 0) return s;
   }
   return 0 ; // did not find
}
//______________________________________________________________________________
