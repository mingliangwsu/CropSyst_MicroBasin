#ifndef qualityH
#define qualityH
#ifndef compareH
#   include "corn/math/compare.h"
#endif

//          For valid data qualities, bit 7 will be 0
//             Bit 6 is reserved and should be 0 for individual data value attribute markers
//             We allow up to 2 estimated_form, forecasted_from or generated_from concatenations using the low 6 bits 0-5
//
//             7 6 5 4 3 2 1 0 bit
//             0 _ 0 0 0 0 0 0

//          For invalid data qualities, bit 7 will be 1
//             bits 0-5 denote the problem with the data value

//          For both valid or invalid qualities codes
//             The Bit 6 is reserved for a record attribute marker this may be set to 1 to indicate that there is set of individual data value attribute markers.

//          Note that the closer the attribute is to 0 the better the quality of the data.
//          The larger the number (especially over 0x80) the worse the problem with the data.

#ifdef __cplusplus
namespace CORN {
#endif

// Use UED_attribute_code below
enum Quality_code
{observed_quality                   = 0
#define measured_quality observed_quality
,calculated_quality                 = 1
,interpolated_quality               = 2
,other_real_quality                 = 3  // This is used for ClimGen when calculating relative humidity from mean dew point.
                                                     // I may want to call this approximate_quality
// For precipitation trace values may be 0.0, very small or unmeasurable
#define      trace_quality  other_real_quality
// Measure, calculated and interpolated are considered real data by ClimGen
,estimated_quality                  = 4
,forecasted_quality                 = 5
,generated_quality                  = 6
// reserved for future                         7

,derived_quality                   = 8 // This is a place holder, it is the start of the composed variable codes
// Note that there are a few composed qualities that will never be used
// (I.e.   Measure from calculated, measured from interpolated , etc..

,default_quality                    = 0x3F
,not_valid_quality                  = 0x80   // (not inviolate)
// The following are range errors
,out_of_range_deprecated_quality    = 0x81   // Becoming obsolete reserve for future use
,missing_quality                    = 0x82
,out_of_range_warning_quality       = 0x83
,out_of_range_low_warning_quality   = 0x84
,out_of_range_high_warning_quality  = 0x85
,out_of_range_pot_error_quality     = 0x86
,out_of_range_pot_low_error_quality = 0x87
,out_of_range_pot_high_error_quality= 0x88
,out_of_range_error_quality         = 0x89
,out_of_range_low_error_quality     = 0x8A
,out_of_range_high_error_quality    = 0x8B
//           reserved for future range errors  0x8C- 0x8F
,unknown_quality                    = 0xBF
};
// Bit 8 set indicates what ever quality was expected,
// but the value is missing.

#define simulated_quality    (CORN::Quality_code)CORN::forecasted_quality

#define best_quality(q1,q2)  CORN_min(q1,q2)
#define worst_quality(q1,q2) CORN_max(q1,q2)
#define worst_quality_of_3(q1,q2,q3)    CORN_max(q1,CORN_max(q2,q3))
#define worst_quality_of_4(q1,q2,q3,q4) CORN_max(q1,CORN_max(q2,CORN_max(q3,q4)))
#define worst_quality_of_5(q1,q2,q3,q4,q5) CORN_max(q1,CORN_max(q2,CORN_max(q3,CORN_max(q4,q5))))
#define quality_is_worse_than(q1,q2) (q1 > q2)
#define quality_is_same_or_worse_than(q1,q2) (q1 >= q2)
#define quality_is_better_than(q1,q2) (q1 < q2)
#define quality_is_same_or_better_than(q1,q2) (q1 <= q2)

extern Quality_code degrade_quality(Quality_code initial_quality, Quality_code degrading_quality);

extern Quality_code quality_calculated_from    (Quality_code qual);
extern Quality_code quality_interpolated_from  (Quality_code qual);
extern Quality_code quality_estimated_from     (Quality_code qual);
extern Quality_code quality_other_real_from    (Quality_code qual);
extern Quality_code quality_forecasted_from    (Quality_code qual);
extern Quality_code quality_generated_from     (Quality_code qual);

extern bool is_optimal_quality(Quality_code qual);

#ifndef __cplusplus
#define is_measured_quality(qual) (qual == observed_quality)
#define is_valid_quality(qual) (qual < not_valid_quality)
#define is_real_quality(qual) is_optimal_quality(qual)
#endif
/* Consider renaming    is_real_quality to
is_optimal()
is_prime()
is_reputable()
is_pristine()
*/

#ifdef __cplusplus
} // namespace CORN
#endif

#endif

