#ifndef CS_tillH
#define CS_tillH

//#if (CROPSYST_VERSION < 5)
// 070627 In version 5 this will be obsolete

#ifndef Phrase_ID_or_label
#  define Phrase_ID_or_label const char *
#endif
#ifndef primitiveH
#  include <corn/primitive.h>
#endif

// This rather than enumeration simplifies the parameter editor checkboxes
#define NO_OPERATION      0
#define PRIMARY_TILL      1
#define SECONDARY_TILL    2
#define PLANTING_TILL 4
#define NO_TILL_DRILL     8
#define RESIDUE          16
#define EVENT            32
#define FERTILIZATION    64
#define Tillage_kinds_mask uint32

struct operation_practice_layout
{
   Tillage_kinds_mask kind;      // was tillage_kind
   int16 SCS_code;               // Soil Conservation Service code
   char sf;                      // Fraction of surface residue 0-100)
   char sh;                      // Fraction of surf. residue added to shallow residue 0-(100-sh)
   char group;                   // ??? practice classification?
   float32 random_roughness_cm;  // cm  (values of 0.9, 1.9, 1.9, 3.9, 4.9 indicate values I guessed at and unverified)
   Phrase_ID_or_label desc1;     // desc1
   Phrase_ID_or_label desc2;     // desc1 (desc2)
   Phrase_ID_or_label withX;     // desc1 (desc2) withX
   char sp;                      //inches  desc1 (desc2) withX spacing:SP"
};

extern struct operation_practice_layout operation_practices_deprecated_V4_7[];

operation_practice_layout &lookup_SCS_code_deprecated_V4_7(int code);

const char *lookup_SCS_description_deprecated_V4_7(int code);

#define SCS_residue_flail_chop_bust 80
#define SCS_residue_grazing         81
#define SCS_residue_baling          82
#define SCS_residue_burning         83
#define SCS_residue_grazing_corn   100

//#endif
// (CROPSYST_VERSION < 5)
#endif
//cs_till.h

