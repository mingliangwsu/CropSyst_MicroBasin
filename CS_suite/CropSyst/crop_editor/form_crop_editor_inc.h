//Code fragments common to both the CropSyst V4 and V5 soil editor form
#include "CS_suite/CropSyst/form_common_editor_inc.h"
namespace CropSyst
{  class Crop_parameters;
}
   #define CropSyst_Crop_parameters CropSyst::Crop_parameters
//______________________________________________________________________________
#define CROP_EDITOR_INCLUDES_AND_FORWARD_DECLS                                 \
   COMMON_EDITOR_INCLUDES_AND_FORWARD_DECLS                                    \
//______________________________________________________________________________
#define Tcrop_editor_form_USER_DECLARATIONS                                    \
public: /* User declarations*/                                                 \
   void __fastcall bind_to(CropSyst_Crop_parameters *i_crop,Tparameter_file_form *i_parameter_form,const char *i_crop_model=0);\
   void __fastcall bind_to_V4_and_V5(CropSyst_Crop_parameters *i_crop,Tparameter_file_form *i_parameter_form,const char *i_crop_model);\
   virtual void __fastcall Update();                                           \
   virtual void __fastcall Update_V4_and_V5();                                 \
private:                                                                       \
   CropSyst_Crop_parameters *crop;           /* owned by calling program */    \
   Tparameter_file_form *parameter_file_form;                                  \
   CORN::OS::Directory_name_concrete crop_directory;                           \
   bool paste_started;  /* This is needed to validate after paste */           \
   const char                    *crop_model;                                  \
   float32 top_checksum;                                                       \
   float32 root_checksum;                                                      \
/*   bool     has_vernalization;    */                                             \
/*   bool     has_photoperiod;      */                                             \
/*   bool     has_hardiness;        */                                             \
private:                                                                       \
   void show_hide_controls();                                                  \
   void show_hide_controls_V4_and_V5();                                        \
   void __fastcall show_hide_dormancy();                                       \
   void __fastcall bind_to_vernalization();                                    \
   void __fastcall bind_to_photoperiod();                                      \
   void __fastcall bind_to_harvest_index();                                    \
   void __fastcall bind_to_dormancy();                                         \
   void __fastcall bind_to_hardiness();                                        \
   void __fastcall bind_to_orchard();                                          \
   void __fastcall bind_to_fruit();                                            \
   void __fastcall bind_to_nitrogen();                                         \
   void __fastcall bind_to_salinity();                                         \
   void __fastcall bind_to_CO2_response();                                     \
   void handle_update_root_biomass_checksum();                                 \
   void handle_update_top_biomass_checksum();                                  \
   void handle_crop_model_radiogroup_onclick();                                \
   void handle_crop_class_combobox_onchange();                                 \
   void handle_calibrate_button_on_click();                                    \
   void handle_radiogroup_photosynthetic_click();                              \
   void handle_preset_end_dilution();                                          \
//______________________________________________________________________________
#define Tcrop_editor_form_CONSTRUCTOR_INITIALIZATION                           \
   , parameter_file_form(0)                                                    \
   , crop(0)                                                                   \
   , crop_directory()                                                          \
//______________________________________________________________________________
