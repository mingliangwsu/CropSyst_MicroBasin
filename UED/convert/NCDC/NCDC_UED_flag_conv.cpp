
#include "NCDC_UED_flag_conv.h"

struct Flag_conversion
flag_conversion [] =
{
 {    ' ',UED_measured     }
,{    'A',UED_measured     } //Accumulated amount; previous value      010, 011, 012, 159
                 //C or L for elements 010, 011, 012
                 //K or L for elements 159
,{    'B',UED_estimated     } //More than one occurrence & estimated    044, 046, 052, 054,
                 //                                     056, 058, 059
,{    'C',CORN::missing_quality     } //Precipitation occurred, amount          010, 011, 012
                 //uncertain; value is 0
,{    'D',UED_generated     } //Derived                                 061-068
,{    'E',UED_estimated     } //Estimated                               all except 061-068
,{    'F',UED_estimated     } //Accumulated and estimated               010, 011, 012
,{    'G',UED_measured     } //Uncorrected                             107-122
,{    'H',UED_measured     } //Freezing                                123, 125-132
,{    'I',UED_measured     } //Unadjusted                              123, 125-132
,{    'J',UED_measured     } //Freezing and unadjusted                 123, 125-132
,{    'K',CORN::missing_quality     } //First occurrence when precip. may       159
                 //or may not have occurred;
                 //value is 0.
,{    'L',CORN::missing_quality     } //Precipitation may or may not have       010, 011, 012, 159
                 //occurred; value is 0
,{    'M',CORN::missing_quality     } //Missing                                 all
,{    'N',UED_unknown_quality     } //Time uncertain                          159
,{    'N',CORN::missing_quality     } //Temperature missing, but known to be
                 //ABOVE freezing.                         002
,{    'O',UED_unknown_quality     } //Not assigned
,{    'P',UED_unknown_quality     } //Not assigned
,{    'Q',UED_unknown_quality     } //Not assigned
,{    'R',UED_unknown_quality     } //Not assigned
,{    'S',UED_measured     } //More than one occurrence                023, 024, 044, 046,
                 //                                      052, 054, 056, 058,
                 //                                      059, 157, 158
,{    'T',UED_measured     } //Trace.  Value is zero                   006-013, 039, 048-
                 //                                      052, 054, 056
,{    'U',UED_measured     } //Valid datum, unknown snow               061-068
,{    'V',UED_measured     } //Valid datum, no snow cover              061-068
,{    'W',UED_measured     } //Valid datum, with snow cover            061-068
,{    'X',UED_estimated     } //Estimated, unknown snow                 061-068
,{    'Y',UED_estimated     } //Estimated, no snow cover                061-068
,{    'Y',CORN::missing_quality     } //Temperature missing, but known to be
                 //BELOW freezing.                         002
,{    'Z',UED_estimated     } //Estimated, with snow cover              061-068
,{0,UED_not_valid}
};


