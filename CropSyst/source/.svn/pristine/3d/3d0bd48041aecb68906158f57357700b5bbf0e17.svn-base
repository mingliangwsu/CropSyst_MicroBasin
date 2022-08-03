#ifndef cmmnoptsH
#define cmmnoptsH

// I am replacing the WKS output to UED_output
// This will provide faster runs and smaller output files.

#include "corn/condcomp.h"

// Eventually (in version V) I want to use the label true/false instead of 0/1
#define CROPSYST_VV_BOOL_FORM CORN::VV_bool_entry::form_true
#define CROPSYST_MAX_DESCRIPTION_LENGTH  128

#ifdef SOIL_INFILTRATION
#  define FINITE_DIFF
#  define CASCADE
#endif

#ifdef FINITE_DIFF
#else
// We must have at least the cascade model
#  define CASCADE
#endif

#  define OLD_RESIDUE_BALANCE

#ifdef NITROGEN
#  define CHEM_PROFILE
#endif

#ifdef MANAGEMENT
#  define TILLAGE
#  define AUTOMATIC_IRRIGATION
#endif

#ifdef FRUIT_CROP_MODEL
// Fruit crop model require hourly thermal time
#  define HOURLY_THERMAL_TIME
#endif

#ifdef unix
// We don't need detail file in LADSS
#  undef DETAIL_FILE
#endif

#endif
// cmmnopts.h

