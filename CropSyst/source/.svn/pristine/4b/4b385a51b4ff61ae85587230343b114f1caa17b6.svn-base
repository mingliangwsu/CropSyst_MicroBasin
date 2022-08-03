#ifdef USE_PCH
#  include "simulation/CropSyst_sim_pch.h"
#else
//#  include <corn/corn.h>
#endif
#include "organicn.h"
//______________________________________________________________________________
static float32 long_term_retention[][2] = //: ARRAY[SURFACE_BROADCAST_NO_INCORPORATION..KNIFED,FALSE..TRUE]
//solid liquid
{// now 0 indexed {0   ,0   },
 {65.0,70.0}, //broadcast no incororate
 {70.0,70.0}, //Sprinkler   (actually no solid sprinkler)
 {96.5,96.5}, //broadcast incorporated
 {99.0,99.0}  //Knifed      (actually no solid knifing)
};
//______________________________________________________________________________
static float32 short_term_retention[][2] = //: ARRAY[SURFACE_BROADCAST_NO_INCORPORATION..KNIFED,FALSE..TRUE]
//solid liquid
{// now 0 index {0   ,0   },
 {77.5,82.5}, //broadcast no incororate
 {75.0,75.0}, //Sprinkler   (actually no solid sprinkler)
 {97.0,97.0}, //broadcast incorporated
 {99.0,99.0}  //Knifed      (actually no solid knifing)
};
//______________________________________________________________________________
float64 get_long_term_fraction_N_retained
(Org_N_appl_method appl_method
,bool is_liquid)
{  return (long_term_retention[appl_method][is_liquid] / 100.0);
};
//______________________________________________________________________________
float64 get_short_term_fraction_N_retained
(Org_N_appl_method appl_method
,bool is_liquid)
{  return (short_term_retention[appl_method][is_liquid] / 100.0);
};
//______________________________________________________________________________

