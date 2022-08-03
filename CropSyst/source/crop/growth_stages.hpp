#ifndef growth_stagesHPP
#define growth_stagesHPP
 
#ifndef growth_stagesH
#  include "growth_stages.h"
#endif
extern Normal_crop_event_sequence index_growth_stage(unsigned long /*nat32 */  growth_stage); //130425
//130425 rename to indexed crop event
                         
#ifndef labeled_enumH                           
#  include "corn/labeled_enum.h"
#endif
DECLARE_LABELED_ENUM(Normal_crop_event_sequence_labeled,Normal_crop_event_sequence ,normal_crop_event_sequence_label_table)
DECLARE_LABELED_ENUM(Fruit_tree_event_sequence_labeled ,Normal_crop_event_sequence ,fruit_tree_event_sequence_label_table)
#endif
//growth_stages.h

