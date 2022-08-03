#ifndef units_symbologyH
#define units_symbologyH

#include "corn/primitive.h"
#include "corn/metrology/units_code.h"

// file:///home/rnelson/test/Translator_sample/JsonViewerPackage
#include "string.h"
#ifdef __cplusplus
namespace CORN {
using namespace CORN;
#endif
//______________________________________________________________________________
struct Units_Standard_definition  //091021  was U_standard_definition
{  Units_code   code;
   const char  *description;
   const char  *abbreviation;
};
extern
Units_Standard_definition units_standard_definition_table[];
//______________________________________________________________________________
struct Units_Generalized_measure_definition
{  const char *quantity
;  const char *units_name           // metric
;  const char *units_abbreviation   // metric
;  bool        metric_power         // true if the least significant bit is the metric power
;};
extern Units_Generalized_measure_definition units_generalized_measure_def_table[];
//______________________________________________________________________________
struct Units_Customary_units_definition
{  uint16  subcode            // subcode
;  const char *units_name           // English/US customary
;  const char *units_abbreviation
;};
extern Units_Customary_units_definition units_customary_def_table[];
//______________________________________________________________________________
struct Units_Metric_system_label
{ const char *label
; const char *abbreviation
;};
extern Units_Metric_system_label units_metric_system_label_table_pos[25];
extern Units_Metric_system_label units_metric_system_label_table_neg[25];
//______________________________________________________________________________
struct Units_Other_definition
{  Units_code    code;
   const char           *abbreviation;
};
//______________________________________________________________________________
extern Units_code units_identify_code(const char *units_label);
extern Units_code units_identify_code(const wchar_t *units_label);               //090313

#ifdef __cplusplus
} // namespace CORN 
#endif

#endif
