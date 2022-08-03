#ifndef statistics_typesH
#define statistics_typesH

#include "corn/primitive.h"
//______________________________________________________________________________

//070219  The following are bitmasks
// Note: when adding a stat make sure the bitmasks
//       and indexes match respectively!

// The following can be calculated in the descriptive_cumulative
#define  STAT_value_bit      1
#define  STAT_count_bit      2
#define  STAT_sum_bit        4
#define  STAT_min_bit        8
#define  STAT_max_bit       16
#define  STAT_arithmetic_mean_bit      32
#define  STAT_std_dev_bit   64
#define  STAT_coef_var_bit 128
#define  STAT_sum_sqrs_bit 256
// The following require dataset
#define  STAT_median_bit    512
#define  STAT_mode_bit     1024
#define  STAT_initial_bit  2048
#define  STAT_final_bit    4096

//140817  Conceptional:  STAT_skewness STAT_kurtosis STAT_kurtosis_excess STAT_variance
// Higher order bits (16bit are valid but not yet defined)

#define  STAT_ALL_bits  0xFFFF
#define  STAT_BASIC_ELEMENTS_bits 0x3F
#define  STAT_BASIC_ELEMENTS_INIT_FINAL_bits (STAT_BASIC_ELEMENTS_bits | STAT_initial_bit | STAT_final_bit)

// aliases
#define STAT_mean_bit STAT_arithmetic_mean_bit
/*
STAT_value_bit
STAT_count_bit
STAT_sum_bit
STAT_min_bit
STAT_max_bit
STAT_arithmetic_mean_bit
*/

#define  STAT_COUNT 16
// Currently only 16 descriptive statistical elements
// but could be extended to 32 if needed

//091217 replaced with order member #define  STAT_SORTED       0x8000
#define  STAT_NEEDS_RECALC 0xFFFF

// The following are probabilities
// Use by ArcCS
#define STAT_PROB_10    1
#define STAT_PROB_20    2
#define STAT_PROB_30    4
#define STAT_PROB_40    8
#define STAT_PROB_50   16
#define STAT_PROB_60   32
#define STAT_PROB_70   64
#define STAT_PROB_80  128
#define STAT_PROB_90  256
#define STAT_PROB_100 512

#define STAT_PROB_05    1
#define STAT_PROB_15    2
#define STAT_PROB_25    4
#define STAT_PROB_35    8
#define STAT_PROB_45   16
#define STAT_PROB_55   32
#define STAT_PROB_65   64
#define STAT_PROB_75  128
#define STAT_PROB_85  256
#define STAT_PROB_95  512

#define  STAT_value_index        0
#define  STAT_count_index        1
#define  STAT_sum_index          2
#define  STAT_min_index          3
#define  STAT_max_index          4
#define  STAT_mean_index         5
#define  STAT_std_dev_index      6
#define  STAT_coef_var_index     7
#define  STAT_sum_sqrs_index     8
// The following stats require dataset
#define  STAT_median_index       9
#define  STAT_mode_index        10
#define  STAT_initial_index     11
#define  STAT_final_index       12
#define  STAT_13_index          13
#define  STAT_14_index          14
#define  STAT_15_index          15
// stat indices 13 to 15 are reserved for future use

//______________________________________________________________________________
typedef  nat16 STAT_mask;                                                        //170319

enum Statistic                                                                   //040926
{value_statistic     //0 // This might be better named observation
,count_statistic     //1
,sum_statistic       //2
,min_statistic       //3
,max_statistic       //4
,mean_statistic      //5
,std_dev_statistic   //6
,coef_var_statistic  //7
,sum_sqrs_statistic  //8
,median_statistic    //9
,mode_statistic      //10
,initial_statistic   //11                                                        //130918
   // The first/initial observation entered in the dataset
,final_statistic     //12                                                        //160604
   // The final observation entered in the dataset
,statistic_COUNT
};
#define UNKNOWN_statistic value_statistic

extern const char *statistic_label_table[];                                      //010815
extern const char *statistic_probablity_10_label_table[];                        //050204
extern const char *statistic_probablity_5_label_table[];                         //050130
extern const char *statistic_code_label_table[];                                 //021216

extern nat8 statistic_flag_to_index(STAT_mask flag);                             //170318_010815
#define     statistic_index_to_flag(index) (index ? (1 << (index-1)): index)

extern STAT_mask statistics_ASCIIz_to_mask(const char *options_ASCIIz);          //170318

//______________________________________________________________________________
#endif
