#ifndef UED_ANALYSIS_H
#define UED_ANALYSIS_H

#ifndef CORN_MATH_STATS_H
#  include <corn/math/statistics/stats.h>
#endif
#ifndef UED_UED_H
#include <UED/UED.h>
#endif
/*
   This class prepares a statistical dataset for a variable
   between the specified date period (inclusive).
*/
//140530 using_namespace_CORN;

class UED_statistical_data_set
: public CORN_Statistical_data_set
, public UED_smart_variable_code
, public CORN::Units_clad;

{
public:
   UED_statistical_data_set
   (UED_indexed_database &database // The database to draw the data from
   ,UED_time_search       analysis_period
   ,UED_variable_code      variable_code
   ,UED_units_code         units_code
   );
   // Creates the statistical data set, loading it with
   // the values from all records
};
#endif
//analysis

