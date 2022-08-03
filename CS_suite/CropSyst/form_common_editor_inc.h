//______________________________________________________________________________
//Code fragments common to both the CropSyst V4 and V5 parameter editor forms
//______________________________________________________________________________
#if (__BCPLUSPLUS__ >= 0x0610)
   // RadStudio 2009 or greater with RNAutoControls
#  include "GUI/parameter/form_param_file_RS.h"
#else
   // BCB5 with AutoControls
#  include "GUI/parameter/form_param_file.h"
#endif
//______________________________________________________________________________
#define COMMON_EDITOR_INCLUDES_AND_FORWARD_DECLS                               \
   class Tparameter_file_form;                                                 

//______________________________________________________________________________
// In version 5 HELP is kept in the properties and longer passed to bind_to
// This macro will go away when V4 is retired.
#if (CS_VERSION == 4)
#ifndef V4_HELP_URL
#define V4_HELP_URL(help)                                                      \
      ,parameter_file_form->provide_program_directory().Documentation().provide_document_filename(help_doctype).c_str()
#endif
#else
#define V4_HELP_URL(help)
#endif

//170402 ,parameter_file_form->provide_program_directory().Documentation().compose_manual_subdirectory_filename(help,parameter_file_form->composed_filename_buffer).c_str()



// was
//      ,parameter_file_form->compose_manual_subdirectory_filename_cstr(help)
//______________________________________________________________________________
extern bool edit_parameter_file
(const wchar_t *filename // qualified_with_extension
,const_UnicodeZ editor_name  // without .exe extension
,const_UnicodeZ option);

