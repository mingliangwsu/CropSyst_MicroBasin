#ifndef CS_OBSERVATIONH
#define CS_OBSERVATIONH

#include "corn/math/statistical/statistics_types.hpp"
#include "CS_suite/observation/CS_emanator.h"

namespace CS
{
//______________________________________________________________________________
class Emanator;
//class Inspectors;
//______________________________________________________________________________
} // namespace CS
#define CS_EPHEMERAL true
#define CS_NOT_EPHEMERAL false
//______________________________________________________________________________
#define RENDER_INSPECTORS_DECLARATION           \
virtual CS::Emanator *render_inspectors         \
(CORN::Container      &inspectors               \
,const CS::Emanator  *context                   \
,const std::string   &instance ) rendition_
//______________________________________________________________________________
#define RENDER_INSPECTORS_DECLARATION_structure \
virtual CS::Emanator *render_inspectors_structure         \
(CORN::Container      &inspectors               \
,const CS::Emanator  *context                   \
,const std::string   &instance                  \
,CORN::Statistic      statistic) rendition_
// This is used where the object is a structure where all items
// have the same statistic.
// Now that recorders have tallies of tallies this
// RENDER_INSPECTORS_DECLARATION_group is probably not applicable
// it is currently only used in
//______________________________________________________________________________
#define RENDER_INSPECTORS_DECLARATION_PURE      \
   RENDER_INSPECTORS_DECLARATION = 0
//______________________________________________________________________________
#define RENDER_INSPECTORS_DEFINITION(rendering_class)    \
CS::Emanator *rendering_class::render_inspectors         \
(CORN::Container      &inspectors                        \
,const CS::Emanator  *context                            \
,const std::string   &instance          ) rendition_
//______________________________________________________________________________
#define RENDER_INSPECTORS_DEFINITION_structure(rendering_class)    \
CS::Emanator *rendering_class::render_inspectors_structure         \
(CORN::Container      &inspectors                        \
,const CS::Emanator  *context                            \
,const std::string   &instance                           \
,CORN::Statistic      statistic) rendition_
//______________________________________________________________________________
#define KNOW_EMANATOR(driving_date,ephemeral)  \
CS::Emanator &emanator \
= CS::get_emanators().know((nat32)this,instance,get_ontology(),ephemeral,context,driving_date)
// The cast (nat32)this is just to get a unique identifier
//______________________________________________________________________________
#endif
