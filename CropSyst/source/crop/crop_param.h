#ifndef crop_paramH
#define crop_paramH

/* At the moment CropSyst proper V5 is still reading V4 files
#if (CROPSYST_VERSION==5)
#include "crop/crop_param_V5.h"
#else
*/
#if (CROP_EDITOR==5)
#include "crop/crop_param_V5.h"
#else
#include "crop/crop_param_V4.h"
// At the moment V5 is still reading V4 files#endif
#endif
//crop_param.h
#endif
