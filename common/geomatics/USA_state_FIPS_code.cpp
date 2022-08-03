#include "common/geomatics/USA_state_FIPS_code.h"
#include <string.h>
#include "corn/string/strconv.h"
// strconv for stricmp
//______________________________________________________________________________
USA_State_FIPS USA_state_FIPS[] =
{{ /*00*/ "__",""} // Unassigned
,{ /*01*/ "AA","Alabama"}
,{ /*02*/ "AL","Alaska"}
,{ /*03*/ "__",""} // Unassigned
,{ /*04*/ "AZ","Arizona"}
,{ /*05*/ "AR","Arkansas"}
,{ /*06*/ "CA","California"}
,{ /*07*/ "__",""} // Unassigned
,{ /*08*/ "CO","Colorado"}
,{ /*09*/ "CT","Connecticut"}
,{ /*10*/ "DE","Deleware"}
,{ /*11*/ "DC","District of Colombia"}
,{ /*12*/ "FL","Florida"}
,{ /*13*/ "GE","Georgia"}
,{ /*14*/ "__",""} // Unassigned
,{ /*15*/ "HA","Hawaii"}
,{ /*16*/ "ID","Idaho"}
,{ /*17*/ "IL","Illinois"}
,{ /*18*/ "IN","Indiana"}
,{ /*19*/ "IA","Iowa"}
,{ /*20*/ "KS","Kansas"}
,{ /*21*/ "KY","Kentucky"}
,{ /*22*/ "LA","Louisiana"}
,{ /*23*/ "ME","Maine"}
,{ /*24*/ "MD","Maryland"}
,{ /*25*/ "MA","Massachusetts"}
,{ /*26*/ "MI","Michigan"}
,{ /*27*/ "MN","Minnesota"}
,{ /*28*/ "MS","Mississippi"}
,{ /*29*/ "MO","Missouri"}
,{ /*30*/ "MT","Montana"}
,{ /*31*/ "NE","Nebraska"}
,{ /*32*/ "NV","Nevada"}
,{ /*33*/ "NH","New Hapshire"}
,{ /*34*/ "NJ","New Jersey"}
,{ /*35*/ "NM","New Mexico"}
,{ /*36*/ "NY","New York"}
,{ /*37*/ "NC","North Carolina"}
,{ /*38*/ "ND","North Dakota"}
,{ /*39*/ "OH","Ohio"}
,{ /*40*/ "OK","Oklahoma"}
,{ /*41*/ "OR","Oregon"}
,{ /*42*/ "PA","Pennsylvania"}
,{ /*43*/ "__",""} // Unassigned
,{ /*44*/ "RI","Rhode Island"}
,{ /*45*/ "SC","South Carolina"}
,{ /*46*/ "SD","South Dakota"}
,{ /*47*/ "TN","Tennessee"}
,{ /*48*/ "TX","Texas"}
,{ /*49*/ "UT","Utah"}
,{ /*50*/ "VT","Vermont"}
,{ /*51*/ "VA","Virginia"}
,{ /*52*/ "__",""} // Unassigned
,{ /*53*/ "WA","Washington"}
,{ /*54*/ "WV","West Virginia"}
,{ /*55*/ "WI","Wisconsin"}
,{ /*56*/ "WY","Wyoming"}
,{ /*57*/ "__",""} // Unassigned
,{ /*58*/ "__",""} // Unassigned
,{ /*59*/ "__",""} // Unassigned
// The following are ofshore US territories
,{ /*60*/ "AS","American Samoa"}
,{ /*61*/ "__",""} // Unassigned
,{ /*62*/ "__",""} // Unassigned
,{ /*63*/ "__",""} // Unassigned
,{ /*64*/ "FM","Federated States of Micronesia"}
,{ /*65*/ "__",""} // Unassigned
,{ /*66*/ "GU","Guam"}
,{ /*67*/ "__",""} // Unassigned
,{ /*68*/ "MH","Marshall Islands"}
,{ /*69*/ "MP","Northern Mariana Islands"}
,{ /*70*/ "PW","Palau"}
,{ /*71*/ "__",""} // Unassigned
,{ /*72*/ "PR","Puerto Rico"}
,{ /*73*/ "__",""} // Unassigned
,{ /*74*/ "UM","U.S. Minor Outlying Islands"}
,{ /*75*/ "__",""} // Unassigned
,{ /*76*/ "__",""} // Unassigned
,{ /*77*/ "__",""} // Unassigned
,{ /*78*/ "VI","Virgin Islands of the U.S."}
,{0,0}
};


int lookup_USA_state_FIPS_number(const char *state_name_or_FIPS_CODE)
{
   for (int s = 0; USA_state_FIPS[s].code; s++)
   {
      if (stricmp(USA_state_FIPS[s].code,state_name_or_FIPS_CODE) == 0) return s;
      if (stricmp(USA_state_FIPS[s].name,state_name_or_FIPS_CODE) == 0) return s;
   };
   return 0 ; // did not find
};

#ifdef OBSOLETE
      char USA_state_FIPS_code[][3] =    // FIPS state codes
      {
        /*00*/ "__",
        /*01*/ "AA",
        /*02*/ "AL",
        /*03*/ "__",
        /*04*/ "AZ",
        /*05*/ "AR",
        /*06*/ "CA",
        /*07*/ "__",
        /*08*/ "CO",
        /*09*/ "CT",
        /*10*/ "DE",
        /*11*/ "DC",
        /*12*/ "FL",
        /*13*/ "GE",
        /*14*/ "__",
        /*15*/ "HA",
        /*16*/ "ID",
        /*17*/ "IL",
        /*18*/ "IN",
        /*19*/ "IA",
        /*20*/ "KA",
        /*21*/ "KY",
        /*22*/ "LA",
        /*23*/ "ME",
        /*24*/ "MD",
        /*25*/ "MA",
        /*26*/ "MI", // Michigan
        /*27*/ "MN",
        /*28*/ "MS", // Mississippi
        /*29*/ "MO",
        /*30*/ "MT",
        /*31*/ "NB",
        /*32*/ "NV",
        /*33*/ "NH",
        /*34*/ "NJ",
        /*35*/ "NM",
        /*36*/ "NY",
        /*37*/ "NC",
        /*38*/ "ND",
        /*39*/ "OH",
        /*40*/ "OK",
        /*41*/ "OR",
        /*42*/ "PN",
        /*43*/ "__",
        /*44*/ "RI",
        /*45*/ "SC",
        /*46*/ "TN",
        /*47*/ "TX",
        /*48*/ "UT",
        /*49*/ "VT",
        /*50*/ "VA",
        /*51*/ "VI",
        /*52*/ "__",
        /*53*/ "WA",
        /*54*/ "WV",
        /*55*/ "WI",
        /*56*/ "WY"
     };
//______________________________________________________________________________
#endif

