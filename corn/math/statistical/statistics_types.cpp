#include "corn/primitive.h"
#include "corn/math/statistical/statistics_types.hpp"
#include "corn/string/strconv.hpp"
namespace CORN {
//______________________________________________________________________________
#include "corn/math/statistical/statistics_types.c_cpp"
//______________________________________________________________________________
nat16 statistic_units_matches_observation_units =
 STAT_value_bit
 //STAT_count_bit
|STAT_sum_bit
|STAT_min_bit
|STAT_max_bit
|STAT_arithmetic_mean_bit
|STAT_std_dev_bit
 //STAT_coef_var_bit
|STAT_sum_sqrs_bit
|STAT_median_bit
|STAT_mode_bit
|STAT_initial_bit
|STAT_final_bit
;
//______________________________________________________________________________
nat32 statistics_string_to_mask(const std::string &options_string)
{  return statistics_ASCIIz_to_mask(options_string.c_str());
}
//_2017-03-18___________________________________________________________________
nat32 statistics_mask_to_string
(nat32 mask,bool code_2digit, std::string &options_string)
{
   for (nat8 bi = 0; bi < 32; bi++)
   {  nat32 mask_bit = 1 << bi;
      if (mask & mask_bit)
      {  options_string
         += (code_2digit)
         ? statistic_code_label_table[bi]
         : statistic_label_table[bi];
         options_string += '|';
      }
   }
   CORN::strip_string(options_string,CORN::Trailing,'|');
   return mask;
}
//_2017-03-18___________________________________________________________________
} // namespace CORN

