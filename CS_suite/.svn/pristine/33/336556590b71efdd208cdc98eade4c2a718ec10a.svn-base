

//Code fragments common to both the CropSyst V4 and V5 management editor form
#include "CS_suite/CropSyst/form_common_editor_inc.h"
#include "CropSyst/GUI/help/management.h"
//______________________________________________________________________________
#define MANAGEMENT_EDITOR_INCLUDES_AND_FORWARD_DECLS                           \
   COMMON_EDITOR_INCLUDES_AND_FORWARD_DECLS                                    \
   namespace CropSyst {                                                        \
      class Management_parameters;                                             \
      class Operation;                                                         \
   };                                                                          \
   class Common_event_list;                                                    \
   class Common_event;

#define CropSyst_Management_parameters  CropSyst::Management_parameters
//______________________________________________________________________________
#define TManagement_editor_form_USER_DECLARATIONS                              \
public:                                                                        \
   CropSyst_Management_parameters      *management;                            \
   Tparameter_file_form                *parameter_file_form;                   \
   int16 auto_NO3_split_total;                                                 \
public:                                                                        \
   void __fastcall bind_to(CropSyst::Management_parameters   *_management,Tparameter_file_form      *_parameter_file_form); \
   void __fastcall bind_to_V4_and_V5(CropSyst::Management_parameters   *_management,Tparameter_file_form      *_parameter_file_form); \
   virtual void __fastcall Update();                                           \
   void show_hide_auto_NO3_parameters();                                       \
   void Update_VCL_common();                                                   \
   void handle_add_auto_NO3_appl();                                            \
   void handle_listbox_auto_NO3_splitDblClick();                               \
   TModalResult edit_event(Common_event *event,TForm *op_form,const char *help_HTML_filename); \
   Common_event *prompt_and_append_event(CropSyst::Operation *op,TForm *op_form,Common_event_list &event_list,const char *help_HTML_filename); \
public:                                                                        \
   Common_event * add_clipping_event         (const char *help_URL);           \
   Common_event * add_tillage_event          (const char *help_URL);           \
   Common_event * add_residue_event          (const char *help_URL);           \
   Common_event * add_irrigation_event       (const char *help_URL);           \
   Common_event * add_biomatter_event        (const char *help_URL);           \
   Common_event * add_inorganic_event        (const char *help_URL);           \
   Common_event * add_auto_irrigation_mode   (const char *help_URL);           \
   Common_event * add_auto_clipping_mode     (const char *help_URL);           \
   bool verify_crop_associated_event() affirmation_;
/*170705
   Common_event * add_organic_matter_event   (const char *help_URL);           \
*/

//______________________________________________________________________________
#define TManagement_editor_form_CONSTRUCTOR_INITIALIZATION                     \
   , parameter_file_form(0)                                                    \
   , management(0)                                                             \
   , auto_NO3_split_total(0)
//______________________________________________________________________________



