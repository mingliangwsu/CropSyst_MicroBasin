#ifndef UED_QUALITY_H
#define UED_QUALITY_H
#ifndef condcompH
#  include <corn/condcomp.h>
#endif
#ifndef compareH
#  include <corn/math/compare.h>
#endif
#ifndef validtypH
#  include <corn/validate/validtyp.h>
#endif


//          For valid data qualities, bit 7 will be 0
//             Bit 6 is reserved and should be 0 for individual data value attribute markers
//             We allow up to 3 estimated_form, forecasted_from or generated_from concatenations using the low 6 bits 0-5
//
//             7 6 5 4 3 2 1 0 bit
//             0 _ 0 0 0 0 0 0

//          For invalid data qualities, bit 7 will be 1
//             bits 0-5 denote the problem with the data value

//          For both valid or invalid qualities codes
//             The Bit 6 is reserved for a record attribute marker this may be set to 1 to indicate that there is set of individual data value attribute markers.


//          Note that the closer the attribute is to 0 the better the quality of the data.
//          The larger the number (especially over 0x80) the worse the problem with the data.

// Use UED_attribute_code below
enum UED_quality_attribute
{UED_measured                    = 0
,UED_estimated                   = 1
,UED_forecasted                  = 2
,UED_generated                   = 3

,UED_not_valid                   = 0x80
   //050218    The following are range errors
,UED_out_of_range_depricated     = 0x81   // Becoming obsolete reserve for future use
,UED_missing                     = 0x82
,UED_out_of_range_warning        = 0x83
,UED_out_of_range_low_warning    = 0x84
,UED_out_of_range_high_warning   = 0x85
,UED_out_of_range_pot_error          = 0x86
,UED_out_of_range_pot_low_error      = 0x87
,UED_out_of_range_pot_high_error     = 0x88
,UED_out_of_range_error          = 0x86
,UED_out_of_range_low_error      = 0x87
,UED_out_of_range_high_error     = 0x88
//           reserved for future range errors  0x89- 0x8F
,UED_unknown_quality             = 0xBF
};
// Bit 8 set indicates what ever quality was expected,
// but the value is missing.


// I need also some other qualities, these could be a separate value
//    - not measured but presumed zero (I.e. solar radiation at night)
//    - impreceptiable (essentially 0)


           #define has_attribute_markers_mask 0x40

           #define UED_valid_attribute    (UED_quality_attribute)0x00

           #define UED_real         (UED_quality_attribute)UED_measured
           #define UED_simulated    (UED_quality_attribute)UED_forecasted
           #define UED_calculated   (UED_quality_attribute)UED_estimated

           #define UED_limit_from_quality(new_quality,from_quality) ((new_quality >= UED_not_valid) ? from_quality : new_quality)


//           #define UED_XXX_from_quality(base_quality,from_quality)  
//           (UED_quality_attribute)(((base_quality&0x3F) << 2) | from_quality)

           extern UED_quality_attribute  UED_XXX_from_quality(UED_quality_attribute base_quality, UED_quality_attribute from_quality);

           extern UED_quality_attribute UED_calculated_from(UED_quality_attribute qual);
           extern UED_quality_attribute UED_estimated_from(UED_quality_attribute qual);
           extern UED_quality_attribute UED_forecasted_from(UED_quality_attribute qual);
           extern UED_quality_attribute UED_generated_from(UED_quality_attribute qual);

           UED_quality_attribute UED_invalidate(UED_quality_attribute &quality);
           // sets the quality as not valid and returns the modified quality

            #define UED_estimated_from_real 0x01


           extern UED_quality_attribute validation_status_to_UED_quality_attribute(CORN::Validation_status validation_status);
/*
' The quality codes are
' Hex Dec  Description
'  0h   0  measured/real
'  1h   1  estimated/calculated  (from real)
'  2h   2  forecasted/simulated  (from real)
'  3h   3  generated             (from real)
'  4h   4  reserver (for future use)
' 05h   5  estimated/calculated from estimated/calculated
' 06h   6  forecasted/simulated from estimated/calculated
' 07h   7  generated            from estimated/calculated
' 08h   8  reserved
' 09h   9  estimated/calculated from forecasted/simulated
' 0Ah  10  forecasted/simulated from forecasted/simulated
' 0Bh  11  generated            from forecasted/simulated
' 0Ch  12  reserved
' 0Dh  13  estimated/calculated from generated
' 0Eh  14  forecasted/simulated from generated
' 0Fh  15  generated            from generated

16-63 will be reserved for future valid codes



' 40h  64  (reserved - This value is used for internal processing)
'
' 80h 128  not valid
' 81h 129  out of range
' 82h 130  missing
' BFh 191  unknown quality (presumed erroneous)
*/

//           #define UED_calculated_from(qual)
//           {    UED_quality_attribute calc_from_quality = UED_XXX_from_quality(qual,UED_calculated);
//
//           UED_limit_from_quality(,UED_calculated)
//           #define UED_estimated_from(qual)  UED_limit_from_quality(UED_XXX_from_quality(qual,UED_estimated),UED_estimated)
//           #define UED_forecasted_from(qual) UED_limit_from_quality(UED_XXX_from_quality(qual,UED_forecasted),UED_forecasted)
//           #define UED_generated_from(qual)  UED_limit_from_quality(UED_XXX_from_quality(qual,UED_generated),UED_generated)

//           #define UED_calculated_from(qual) ((UED_quality_attribute)((qual << 2) | UED_calculated))
//           #define UED_estimated_from(qual)  ((UED_quality_attribute)((qual << 2) | UED_estimated))
//           #define UED_forecasted_from(qual) ((UED_quality_attribute)((qual << 2) | UED_forecasted))
//           #define UED_generated_from(qual)  ((UED_quality_attribute)((qual << 2) | UED_generated))


           #define UED_best_quality(q1,q2)  CORN_min(q1,q2)
           #define UED_worst_quality(q1,q2) CORN_max(q1,q2)
           #define UED_is_worse_than(q1,q2) (q1 > q2)
           #define UED_is_same_or_worse_than(q1,q2) (q1 >= q2)
           #define UED_is_better_than(q1,q2) (q1 < q2)
           #define UED_is_same_or_better_than(q1,q2) (q1 <= q2)


           // Note that if a value is calculated,
           // it has the same quality as the value it is calculated from.

#define UED_any_units 0
// any_units is used in get() when conversion does not need to be done.

            #define UED_is_valid(attribute) (attribute < UED_not_valid)

#define UED_quality_attribute_uint8 uint8
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
#define UED_location_information          0x5C
// NYI                                    0x5D
// NYI                                    0x5E
#define UED_free_space                    0x5F

#define UED_variable_definition_format_0  0x60
#define UED_variable_definition_format_1  0x61
#define UED_variable_definition_format_2  0x62
#define UED_variable_definition_format_3  0x63
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

