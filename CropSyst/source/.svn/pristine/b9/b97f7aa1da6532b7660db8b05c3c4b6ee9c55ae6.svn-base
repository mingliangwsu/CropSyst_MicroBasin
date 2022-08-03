#ifndef CS_globH
#define CS_globH
#ifndef primitiveH
#  include "corn/primitive.h"
#endif

#ifndef validtypH
#  include "corn/validate/validtyp.h"
#endif

#define spacer 0
#ifdef SOILR
#define sim_INIx "SOILR.INI"
#define sim_EXE "sr32.exe"
#endif
#if defined(CROPSYST) || defined(WSHEDMOD)
#define sim_INIx "CROPSYST.INI"
#define sim_EXEx "\\cs_suite\\cropsyst\\cropsyst_4.exe"
#endif

#define LABEL_last         "last"
#define LABEL_simulation   "simulation"
#define LABEL_batch        "batch"
#define LABEL_rotation     "rotation"
#define LABEL_all_files    "all_files"

#define LABEL_format       "format"
#define LABEL_options      "options"
#define LABEL_language     "language"

#define LABEL_text_reports "text_reports"

#define  LABEL_salt              "salt"
#define  LABEL_salinity          "salinity"

#define DEFAULT_straw_to_residue          0.95

enum Chemical_kinds {CHEM_SALT,CHEM_FERTILIZER,CHEM_PESTICIDE};

#ifdef USE_CORN_TRANSLATOR_CLASS
#define Valid_float32_translating_optional   Valid_float32_translating
#define Valid_int16_translating_optional      Valid_int16_translating
#define VV_file_translating_optional               VV_file_translating
#else
#define Valid_float32_translating_optional   Valid_float32
#define Valid_int16_translating_optional      Valid_int16
#define VV_file_translating_optional               VV_file
#define Xtranslate(x) x
#endif

#endif
//cs_glob.h

