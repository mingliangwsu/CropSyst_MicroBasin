#ifndef codesH
#define codesH
#ifndef validtypH
#  include "corn/validate/validtyp.h"
#endif
#ifndef qualityHPP
#   include "corn/quality.hpp"
#endif

const char *UED_get_quality_attribute_label_abbreviated(CORN::Quality_code,const char *buffer);

// I need also some other qualities, these could be a separate value
//    - not measured but presumed zero (I.e. solar radiation at night)
//    - impreceptiable (essentially 0)

           #define has_attribute_markers_mask 0x40
           #define UED_give_me_best_quality (CORN::Quality_code)0x00



//           #define UED_XXX_from_quality(base_quality,from_quality)
//           (CORN::Quality_code)(((base_quality&0x3F) << 2) | from_quality)


extern CORN::Quality_code validation_status_to_UED_quality_attribute(CORN::Validation_status validation_status);
extern CORN::Validation_status UED_quality_attribute_to_validation_status(CORN::Quality_code quality);
/*
' The quality codes are
' Hex Dec  Description
'  0h   0  measured
'  1h   1  calculated  (from real)
'  2h   2  interpolated (from real)
'  3h   3  estimated/calculated  (from real)

'  4h   4  forecasted/simulated  (from real)

'  5h   5  generated             (from real)
'  4h   4  reserver (for future use)
16-63 will be reserved for future valid codes

' 40h  64  (reserved - This value is used for internal processing)
'
' 80h 128  not valid
' 81h 129  out of range
' 82h 130  missing
' BFh 191  unknown quality (presumed erroneous)
*/

           #define UED_best_quality(q1,q2)  CORN_min(q1,q2)
           #define UED_worst_quality(q1,q2) CORN_max(q1,q2)
           #define UED_is_worse_than(q1,q2) (q1 > q2)
           #define UED_is_same_or_worse_than(q1,q2) (q1 >= q2)
           #define UED_is_better_than(q1,q2) (q1 < q2)
           #define UED_is_same_or_better_than(q1,q2) (q1 <= q2)
/*150805 obsolete, use CORN quality
           #define UED_is_valid(attribute) (attribute < CORN::not_valid_quality)
*/

           // Note that if a value is calculated,
           // it has the same quality as the value it is calculated from.

#define UED_any_units 0
// any_units is used in get() when conversion does not need to be done.


#define UED_quality_attribute nat8
#define UED_any_attributes 0

// The following are UED record types

#define UED_marker_BOF                    0x40
// Markers 1,3,4,5,6 un used
#define UED_marker_1                      0x41
#define UED_marker_end_definitions        0x42
#define UED_marker_3                      0x43
#define UED_marker_4                      0x44
#define UED_marker_5                      0x45
#define UED_marker_6                      0x46
#define UED_marker_EOF                    0x47

#define UED_general_comment               0x58
#define UED_database_description          0x59
#define UED_generating_application        0x5A
#define UED_period                        0x5B
#define UED_geolocation_information       0x5C
// NYI                                    0x5D
// NYI                                    0x5E
#define UED_free_space                    0x5F

#define UED_variable_definition_format_0  0x60
#define UED_variable_definition_format_1  0x61
#define UED_variable_definition_format_2  0x62
#define UED_variable_definition_format_ontological  0x63
#define UED_units_definition_format_0     0x64
#define UED_units_definition_format_1     0x65
#define UED_units_definition_format_2     0x66
#define UED_units_definition_format_3     0x67

// This will be increased when there have been a change of
// UED coding
#     define UED_VERSION_NUMBERS 0, 1, 0
#     define UED_VERSION        "0.01.00"
#     define UED_VERSION_CODE    0x000100

//040720 Version 0,01,00
// The units codes were simplified
//#define UED_standard_version  0

#ifdef UED_DUMP
#   define UEDDUMP
#else
#   define UEDDUMP _COMMENT_
#endif

#endif
//codes.h

