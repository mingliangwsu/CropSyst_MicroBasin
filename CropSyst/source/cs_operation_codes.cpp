
#include "cs_operation_codes.h"
//______________________________________________________________________________
const char *CropSyst_op_text[] =
{
 "Unknown"
,"Sowing"
,"Harvest"
,"Tillage"
,"Residue"
,"Irrigation"
,"Inorganic nitrogen"
,"Organic nitrogen"
,"Biomatter (manure) application"
,"Chemical application"
,"Auto irrigation mode"
,"Auto nitrogen mode: optimal"
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <= 4))
,"Auto nitrogen mode: NO3"    // This is a place holder for LADSS
,"Auto nitrogen mode: NO3 balanced based"
,"Auto nitrogen mode: NO3 local calibration"
,"Auto nitrogen mode: NO3 split application"
#else
,"Auto nitrogen mode: N"    // This is a place holder for LADSS
,"Auto nitrogen mode: N balanced based"
,"Auto nitrogen mode: N split application"
#endif
//obs ,  CS_OP_MGMT_AUTO_NO3_DISABLE   auto NO3 period now includes end period event
,"Soil N sampling"
,"Auto clip biomass mode"
//obs ,  CS_OP_MGMT_AUTO_CLIP_PERIODIC replaced by CS_OP_MGMT_CLIPPING as a repeated operation
//obs ,  CS_OP_MGMT_AUTO_CLIP_DISABLE  now uses event period
,"Recalibration"
,"Profile print"
,0
};
//______________________________________________________________________________
const char *CropSyst_operation_codes[] =
{ // Note that these codes match the entity tables in LADSS. The codes much not exceed 30 characters
 "UNKNOWN"
,"SOWING"
,"HARVEST"
,"TILLAGE"
,"RESIDUE"
//031013obs ,"CLIPPING"
,"IRRIGATION"
,"INORGANIC_NITROGEN"
,"ORGANIC_NITROGEN"
,"BIOMATTER_APPLICATION"
,"CHEMICAL"
,"AUTO_IRRIGATION"
//obs ,  CS_OP_MGMT_AUTO_IRRIGATION_DISABLE  auto irrig period now includes end period event
,"AUTO_N_OPTIMAL"
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <= 4))
,"AUTO_NO3"
,"AUTO_NO3_BALANCED"      // These codes are not used by LADSS mode
,"AUTO_NO3_CALIBRATED"    // until after the operation parameters are loaded
,"AUTO_NO3_APPL"
#else
,"AUTO_N"
,"AUTO_N_BALANCED"      // These codes are not used by LADSS mode
,"AUTO_N_APPL"
#endif
//obs ,  CS_OP_MGMT_AUTO_NO3_DISABLE   auto NO3 period now includes end period event
,"SOIL_N_SAMPLING"
,"AUTO_CLIP_BIOMASS"
//obs ,  CS_OP_MGMT_AUTO_CLIP_PERIODIC replaced by CS_OP_MGMT_CLIPPING as a repeated operation
//obs ,  CS_OP_MGMT_AUTO_CLIP_DISABLE  now uses event period
,"RECALIBRATION"
,"PROFILE_PRINT"
,0
};
//______________________________________________________________________________
const char *CropSyst_operation_icons[] =
{
 "unknown.bmp"
,"sowing.bmp"
,"harvest.bmp"
,"tillage.bmp"
,"burning.bmp"
,"irrig.bmp"
,"ferti_inject.bmp"
,"cattle.bmp"
,"cattle.bmp"
,"ferti_inject.bmp"   // need a better icon with sprayer
,"center_pivot2.bmp"
,"ferti_inject.bmp" // auto N optimals
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <= 4))
,"ferti_inject.bmp" // AUTO_NO3
,"ferti_inject.bmp" // AUTO_NO3_BALANCED
,"ferti_inject.bmp" // AUTO_NO3_CALIBRATED
,"ferti_inject.bmp" // AUTO_NO3_APPL
#else
,"ferti_inject.bmp" // AUTO_N
,"ferti_inject.bmp" // AUTO_N_BALANCED
,"ferti_inject.bmp" // AUTO_N_APPL
#endif
,"ferti_inject.bmp"    // need better icon  (SOIL_N_SAMPLING
,"hay.bmp"     //AUTO_CLIP_BIOMASS
,"soil.bmp"    // need better icon
,"PROFILE_PRINT" //
,0
};
//______________________________________________________________________________



