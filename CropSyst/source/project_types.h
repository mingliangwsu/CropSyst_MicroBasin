#ifndef project_typesH
#define project_typesH
#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif
//______________________________________________________________________________
enum CropSyst_project_type { CROPSYST_PROJECT,GIS_PROJECT,WATERSHED_PROJECT,GRAZING_PROJECT,LADSS_PROJECT,UNKNOWN_PROJECT_TYPE};
extern const char *CropSyst_project_type_label_table[];
DECLARE_LABELED_ENUM(CropSyst_project_type_labeled,CropSyst_project_type,CropSyst_project_type_label_table);
//_2005-02-02___________________________________________________________________

#endif

