#ifndef growth_stagesH
#define growth_stagesH

/*
The code in this file is C compilable.
If programming in C++, include the growth_stages.hpp header file.
growth_stages

Growth stage and event triggers
I am in the process of conforming to plant growth stage ontologies
http://www.ncbi.nlm.nih.gov/pmc/articles/PMC1586063/figure/fig1/

If any stages or event triggers are added here
dont forget to update Synchronization constructor
and growth stages.

See also Zadoks scale    http://en.wikipedia.org/wiki/Zadoks_scale

BBCH-scale (cereals)     http://en.wikipedia.org/wiki/BBCH-scale_(cereals)
*/


typedef enum Normal_crop_event_sequence   //130426 rename to Crop_event_sequence
{
NGS_NONE,
   // Note that index 0 reserved for indexing the various phenology arrays for
   // counters/accumulators of the entire life span
   // (but it is not used as this time)                                          //160527
 NGS_PLANTING,
 NGS_GERMINATION
,NGS_EMERGENCE
// Emergence is seedling emergence
,NGS_RESTART
// restart is the restart of active growth in successive season(s)
// this is probably main shoot growth - RLN
,NGS_ACTIVE_GROWTH
   // This is probably auxillary shoot growth
,NGS_END_CANOPY_GROWTH                                                            //130426
,NGS_ANTHESIS // Start of flower organ development
// probably should add here inflorescence visible (sensu Poaceae)  (openning of the flower)     inflorescence
//  and anthesis // when flower if sexually functional
,NGS_FILLING      // Yield/fruit/bulb/tuber formation  infructescence
,NGS_RIPENING     // This growth stage doesn't currently apply to cereal crop but is a place holder for orchard crops
,FGS_RAPID_FRUIT_DEVELOPMENT // Currently applies only to orchard fruit
,NGS_MATURITY
//110513 moved below after harvest ,NGS_DORMANT_or_INACTIVE
,NGS_HARVESTABLE
,NGS_HARVEST
#if (CS_VERSION != 4)
,NGS_POSTHARVEST
#endif
,NGS_DORMANT_or_INACTIVE
,NGS_TERMINATED      // Due to premature death, ploughing under etc.
,NGS_COUNT
} Normal_crop_event_sequence;

#if ((CS_VERSION != 4) || !defined(OLD_TRIGGER_SYNC))
#else
#define NGS_PLANTING           NGS_GERMINATION
#endif
#define NGS_SOWING             NGS_PLANTING

#define NGS_VEGETATIVE_GROWTH  NGS_ACTIVE_GROWTH
#define NGS_BULK_FILLING       NGS_FILLING
#define FGS_PLANTING      NGS_GERMINATION
   // For fruit trees this might conceptually be the period
   // the tree is aclimating to transplant, or graph or other establishment
//#define FGS_reserved_1
   // This is a place holder for future use  (matches emergence) May be needed for seeded starts
#define FGS_BUD_BREAK       NGS_RESTART
#define FGS_ACTIVE_GROWTH   NGS_ACTIVE_GROWTH

#define FGS_ANTHESIS        NGS_ANTHESIS

#define FGS_FRUCTESCENCE  NGS_FILLING
   // was FGS_FRUIT_DEVELOPMENT
#define FGS_VERAISON        NGS_RIPENING
//#define FGS_RAPID_FRUIT_DEVELOPMENT  FGS_RAPID_FRUIT_DEVELOPMENT
#define FGS_MATURITY       NGS_MATURITY

#define FGS_HARVESTABLE    NGS_HARVESTABLE
#define FGS_HARVEST        NGS_HARVEST
#if (CS_VERSION != 4)
#define FGS_POSTHARVEST    NGS_POSTHARVEST
#endif
#define FGS_DORMANT        NGS_DORMANT_or_INACTIVE
#define FGS_TERMINATED     NGS_TERMINATED
extern const char *normal_crop_event_sequence_label_table[];
extern const char *fruit_tree_event_sequence_label_table[];
extern const char *get_growth_stage_description
(Normal_crop_event_sequence growth_stage, bool is_fruit_tree);

/* For more detailed growth stages of cereals,
see BBCH, Feekes, and Zadoks scales
http://en.wikipedia.org/wiki/Feekes_scale
http://en.wikipedia.org/wiki/Zadoks_scale
*/
#endif
//growth_stages.h



