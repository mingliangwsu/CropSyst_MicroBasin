#ifndef __cplusplus
#include "corn/math/statistical/statistics_types.h"
#endif
//______________________________________________________________________________
const char *statistic_label_table[] =
{ "value"
, "count"
, "sum"
, "min"
, "max"
, "mean"
, "stddev"   //160305 was std_dev
, "coefvar"  //160305 was coef_var
, "sumsqrs"  //160305 was sum_sqrs
, "median"
, "mode"
, "initial"                                                                      //131017
, "final"                                                                        //160626
,0
};
//_2002-12-16___________________________________________________________________
const char *statistic_probablity_10_label_table[] =
{ "10%"
, "20%"
, "30%"
, "40%"
, "50%"
, "60%"
, "70%"
, "80%"
, "90%"
, "100%"
,0
};
//_2005-01-30___________________________________________________________________
const char *statistic_probablity_5_label_table[] =
{ "5%"
, "15%"
, "25%"
, "35%"
, "45%"
, "55%"
, "65%"
, "75%"
, "85%"
, "95%"
,0
};
//_2005-01-30___________________________________________________________________
const char *statistic_code_label_table[] = // These are currently only used by ArcCS:avg_prob
{ "vl"
, "ct"
, "sm"
, "mn"
, "mx"
, "av"
, "sd"
, "cv"
, "ss"
, "md"
, "in"                                                                           //131017
, "fn"                                                                           //160626
,0
};
//_2002-12-16___________________________________________________________________
nat8 statistic_flag_to_index(nat32 flag)
{  int8 index = flag;
   if (flag)
   {  int i =0;
      index = 1;
      for ( i = 0; i < 16; i++)
      {  if (flag & 1)
            return index;
         else
         {  index += (uint8)1;
            flag >>= 1;
   }  }  }
   return index;
}
//_2001-08-15___________________________________________________________________
nat32 statistics_ASCIIz_to_mask(const char *options_ASCIIz)
{
   nat32 mask = 0;
   for (nat8 si = 0; si <
      #ifdef __cplusplus
      // This shouldn't be needed. I need to track down header includes
      // I probably need to rename this file extension to c_cpp and include in the cpp file
      CORN::
      #endif
         statistic_COUNT; si++)
   {  nat32 stat_flag = 1 << si;
      if (  (strstr(options_ASCIIz, statistic_label_table[si] ) != NULL)
          ||(strstr(options_ASCIIz,statistic_code_label_table[si]) != NULL))
         mask |= stat_flag;
   } // for si
   return mask;
}
//_2017-03-18___________________________________________________________________
