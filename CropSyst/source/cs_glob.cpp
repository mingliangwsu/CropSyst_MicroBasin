120524  This file is now obsolete


#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
#include "cs_glob.h"
//120515 #include <corn/file_sys/dirname.h>
//#include <corn/commontrans.h>
#include <corn/datetime/date.h>
#endif
#pragma hdrstop

using namespace CORN;                                                            //120524

#ifdef MOVE
Don't delete this yet, I have to move these to a file called CS_translator
#ifdef USE_CORN_TRANSLATOR_CLASS

void CORN_NS date_setup_phrases()
{
   date_phrases_setup =true;
   for (uint8 month = 1; month <= 12; month++)
   {
      uint16 month_str_index = L_DATE_January + month -1;
      date_month_names[month] = common_translate(month_str_index);
      date_month_abbrevs[month] = common_translate(L_DATE_Jan_abrv +month -1);
   };
/*
   CORN_date_L_Jan_abrv         = common_translate(L_DATE_Jan);
   CORN_date_L_Feb_abrv         = common_translate(L_DATE_Feb);
   CORN_date_L_Mar_abrv         = common_translate(L_DATE_Mar);
   CORN_date_L_Apr_abrv         = common_translate(L_DATE_Apr);
   CORN_date_L_May_abrv         = common_translate(L_DATE_May);
   CORN_date_L_Jun_abrv         = common_translate(L_DATE_Jun);
   CORN_date_L_Jul_abrv         = common_translate(L_DATE_Jul);
   CORN_date_L_Aug_abrv         = common_translate(L_DATE_Aug);
   CORN_date_L_Spt_abrv         = common_translate(L_DATE_Spt);
   CORN_date_L_Oct_abrv         = common_translate(L_DATE_Oct);
   CORN_date_L_Nov_abrv         = common_translate(L_DATE_Nov);
   CORN_date_L_Dec_abrv         = common_translate(L_DATE_Dec);

   CORN_date_L_January     = common_translate(L_DATE_January);
   CORN_date_L_February    = common_translate(L_DATE_February);
   CORN_date_L_March       = common_translate(L_DATE_March);
   CORN_date_L_April       = common_translate(L_DATE_April);
   CORN_date_L_May         = common_translate(L_DATE_May);
   CORN_date_L_June        = common_translate(L_DATE_June);
   CORN_date_L_July        = common_translate(L_DATE_July);
   CORN_date_L_August      = common_translate(L_DATE_August);
   CORN_date_L_September   = common_translate(L_DATE_September);
   CORN_date_L_October     = common_translate(L_DATE_October);
   CORN_date_L_November    = common_translate(L_DATE_November);
   CORN_date_L_December    = common_translate(L_DATE_December);
*/
   T_date_Day         = common_translate(L_DATE_Day);
   T_date_Days        = common_translate(L_DATE_Days);
   T_date_Day_of_month= common_translate(L_DATE_Day_of_month);
   T_date_Day_of_year = common_translate(L_DATE_Day_of_year);
   T_date_Month       = common_translate(L_DATE_Month);
   T_date_Year        = common_translate(L_DATE_Year);
   T_date_Years       = common_translate(L_DATE_Years);
   T_date_Date        = common_translate(L_DATE_Date);
   T_date_Sunday      = common_translate(L_DATE_Sunday);
   T_date_Monday      = common_translate(L_DATE_Monday);
   T_date_Tuesday     = common_translate(L_DATE_Tuesday);
   T_date_Wednesday   = common_translate(L_DATE_Wednesday);
   T_date_Thursday    = common_translate(L_DATE_Thursday);
   T_date_Friday      = common_translate(L_DATE_Friday);
   T_date_Saturday    = common_translate(L_DATE_Saturday);
};
#endif
#endif

