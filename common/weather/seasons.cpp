#include "common/weather/seasons.h"

namespace CS
{
//______________________________________________________________________________
bool is_spring_or_summer_time
(CORN::DOY doy,bool southern_hemisphere
)
{  //  Summer_time is currently used for soil evaporation only.
   return (southern_hemisphere) //140814 (get_latitude_dec_deg() < 0 )
   ? ((doy > 270) || (doy <  90))                                                //980311
   : ((doy >  90) && (doy < 270));                                               //980311
}
//_1998-03-02___________________________________________________________________
nat8 get_season_S_S_F_W(CORN::DOY doy,bool southern_hemisphere)
{  nat8 season_S_S_F_W = SPRING_SEASON;
   if (southern_hemisphere) //140814 (get_latitude_dec_deg() < 0)
   {  if ((doy > 334) || (doy <= 60))  season_S_S_F_W = SUMMER_SEASON;
      if ((doy > 60)  && (doy <= 151)) season_S_S_F_W = FALL_SEASON;             //140813
      if ((doy > 151) && (doy <= 244)) season_S_S_F_W = WINTER_SEASON;           //140813
      if ((doy > 244) && (doy <= 334)) season_S_S_F_W = SPRING_SEASON;           //140813
   } else
   {  if ((doy > 334) || (doy <= 60))  season_S_S_F_W = WINTER_SEASON;
      if ((doy > 60)  && (doy <= 151)) season_S_S_F_W = SPRING_SEASON;           //140813
      if ((doy > 151) && (doy <= 244)) season_S_S_F_W = SUMMER_SEASON;           //140813
      if ((doy > 244) && (doy <= 334)) season_S_S_F_W = FALL_SEASON;             //140813
   }
   return (nat8)season_S_S_F_W;
}
//_2004-09-14___________________________________________________________________
bool Seasons::is_spring_or_summer_time(CORN::DOY doy)                      const
{  if (doy == 0) doy = today.get_DOY();
   return CS::is_spring_or_summer_time(doy,southern_hemisphere);
}
//_2014-08-13___________________________________________________________________
nat8 Seasons::get_season_S_S_F_W(CORN::DOY doy)                                         const
{  if (doy == 0) doy = today.get_DOY();
   return CS::get_season_S_S_F_W(doy,southern_hemisphere);
}
//_2014-08-13___________________________________________________________________
bool Seasons::is_summer_time(CORN::DOY doy_)                        affirmation_
{
   CORN::DOY doy =
      doy_ ? doy_ : today.get_DOY();                                             //990301
   return southern_hemisphere //151028 (get_latitude_dec_deg() < 0 )
   ? ((doy > 330) || (doy < 90))
   : ((doy > 150) && (doy < 270));
}
//_2015-10-28_1999-03-0_________________________________________________________
bool Seasons::is_winter_time(CORN::DOY doy_)                        affirmation_
{
   CORN::DOY doy =
      doy_ ? doy_ : today.get_DOY();                                             //990301
   return southern_hemisphere //151028 (get_latitude_dec_deg() < 0 )
   ? ((doy > 150) && (doy < 270))
   : ((doy > 330) || (doy < 90));
}
//_2015-10-28_1999-03-0_________________________________________________________

} // namespace CS

