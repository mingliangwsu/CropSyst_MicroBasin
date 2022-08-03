#  include <string.h>
#  include <math.h>
#  include "corn/math/moremath.h"
#  include "UED/library/units_def.h"

// for fpreset
#include <float.h>
namespace UED {                                                                  //070718
//______________________________________________________________________________
#ifdef UED_DUMP
using namespace std;
void Units_definition::dumpX(std::ostream &txt_strm)
{
   std::string units_code_label;                                                 //170425
   label_string(units_code_label);                                               //170826
   txt_strm << units_code_label << " | Units code " << endl;
   txt_strm << description.c_str() << " | Description" << endl;
}
#endif
//_1998-08-05___________________________________________________________________
void Units_definition::write_YAML(std::ostream &YAML_strm,nat16 indent_level)
{
   std::string indent(indent_level,' ');

   std::string units_code_label;
   label_string(units_code_label);
   YAML_strm<< indent << "units:"  << std::endl;
   YAML_strm<< indent << " code:"        << units_code_label << std::endl;
   YAML_strm<< indent << " description:" << description.c_str() << std::endl;
}
//_2018-01-08__________________________________________________________________/
const char *Units_definition::label_string(std::string &buffer)            const
{  if (!description.empty())
      buffer += description;
   else Units_clad::label_string(buffer);
   return buffer.c_str();
}
//_2017-04-23___________________________________________________________________
const std::string &Units_definition::get_abbreviation(std::string &result) const
{  result.assign(abbreviation);
   return result;
}
//_1999-05-07__2002-01-30_______________________________________________________
Units_definition::Units_definition(UED_units_code _code)
:Item()
,Units_clad(_code)
,description()
,abbreviation()
{  char desc_cstr[100]; desc_cstr[0] = 0;                                        //030123
   char abbr_cstr[100]; abbr_cstr[0] = 0;
   compose_description(desc_cstr,abbr_cstr);
   description.assign(desc_cstr);                                                //030123
   abbreviation.assign(abbr_cstr);                                               //030123
}
//_1999-04-12___________________________________________________________________
nat32 Units_definition::compute_units_format_size() const
{  return sizeof(UED_units_code)
      + description.length()+1
      + abbreviation.length()+1;
}
//_1998-06-24___________________________________________________________________
} // namespace UED

