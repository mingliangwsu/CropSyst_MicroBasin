#ifndef ET_modelH
#define ET_modelH

#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif

#define   LABEL_PRIESTLEY_TAYLOR   "PRIESTLEY-TAYLOR"
#define   LABEL_PENMAN_MONTEITH    "PENMAN-MONTEITH"
#define GUI_ET_MODEL_COUNT  3

#define ET_MODEL_BEST ET_MODEL_AUTOMATIC
//                NOTE!  PENMAN_MONTEITH_MODEL must have the same value as
//                FAO_PENMAN_MONTEITH in ET_ref.h so insert any new
//                models before PM in both places!

#define  LABEL_PT_constant             "PT_constant"
#define DEF_PT_constant                1.26
//______________________________________________________________________________
enum ET_Model
{ET_all_models
,ET_recorded // Indicates the ET may be recorded (in weather files)              //180805
,ET_Priestley_Taylor
,ET_FAO_56_Penman_Monteith_CropSyst
,ET_Hargreaves_unadjusted
,ET_Hargreaves_adjusted
,ET_ASEC_EWRI_Penman_Monteith_short_crop
,ET_ASEC_EWRI_Penman_Monteith_tall_crop
,ET_ASCE_Penman_Monteith
,ET_FAO_56_Penman_Monteith
,ET_Penman_Monteith
,ET_Penman
,ET_radiation_Penman_Monteith    // Considering only the radiation numerator term
,ET_aerodynamic_Penman_Monteith  // Considering only the vapor pressure term
,ET_CropSyst_VB
//NYI ,ET_Wright_Kimberley_Penman                                                      //110415
//NYI ,ET_Jensen_Haise                                                                 //110415
,ET_Model_COUNT};

#define ET_MODEL_AUTOMATIC       ET_all_models
#if (CS_VERSION==4)
#define PRIESTLEY_TAYLOR_MODEL   ET_Priestley_Taylor
#define PENMAN_MONTEITH_MODEL    ET_FAO_56_Penman_Monteith_CropSyst
#endif
extern  Label_description CS_ET_model_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(LOC_ET_Model_labeled,ET_Model,CS_ET_model_label_table)
//_2009-09-28______________________________________________________________
#endif
