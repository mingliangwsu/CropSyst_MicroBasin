#ifndef SDR_field_opsH
#define SDR_field_opsH
#include <ostream>
#include "corn/primitive.h"
#define UNKNOWN_NRCS_SDR_operation_number 0
#include "common/residue/residue_const.h"

#define  USE_NEW_RUSLE2

namespace USDA { namespace NRCS { namespace RUSLE2 {                             //120406
struct SDR_Field_operation_parameters;                                           //120406
//______________________________________________________________________________
enum Soil_disturbance_effect
{ UNKNOWN_EFFECT       // or No effect
, INVERSION_SOME_MIXING
, MIXING_SOME_INVERSION
, MIXING
, NEGLIGIBLE_EFFECT
, LIFTING_FRACTURING    // Not currently handled by tillage submodel
, COMPRESSION           // Not currently handled by tillage submodel
, REMOVE_COVER          // Not currently handled by tillage submodel (removing plastic cover)
, REMOVE_RESIDUE        // Not currently handled by tillage submodel Remove residue
, ADD_OTHER_EFFECT      // Some operations dont disturb
// Added by Stewart or Roger
, COMPRESSION_AERATION
, COUNT_SD_EFFECT
};

// The following were added by RLN to indicate that the disturbances wasn't originally noted
#define MIXING_RLN            MIXING
#define INVERSION_MIXING_RLN  INVERSION_SOME_MIXING
#define COMPRESSION_RLN       COMPRESSION
//#define COMPRESSION_AERATION

enum Disturbance_source { heuristic_source, Armen_source, Stewart_source,Roger_source,UNKNOWN_SOURCE };
struct Disturbance
{  // These were nat8 now float to allow estimation/calculation
   float32 invert;
   float32 mix;
   float32 lift;
   float32 shatter;
   float32 aerate;
   float32 compact;
   Disturbance_source    source;
      // 0 = Heuristics
      // 1 = Armens's estimates
      // 2 = Stewart's estimites
      // 3 = Roger's estimites
public:
   inline float32 sum() { return invert+mix+lift+shatter+aerate+compact;}
};

#define UNSPECIFIED_EFFECT UNKNOWN_EFFECT
//UNSPECIFIED_EFFECT indicates the RUSLE2 database didn't name the effect Need to check with Bryan if the effect is omitted or it didn't go through processing)   130710
//______________________________________________________________________________
struct Field_operation_parameters
{  // The following are from the NRCS_SDR table
   nat16 number_dont_use;                          // field operation number numbers greater than 255 indicate codes we added in CropSyst to accomodate operation not defined by NRCS
   char *operation_name;
   char *ICASA_code;                                                             //150514
   struct Speed
   {  float32  rec_MPH;  // Not sure what rec is
      float32  min_MPH;
      float32  max_MPH;
   } speed_MPH;      // The original data tables were in US units
   float32 intensity_fraction;   //(RLN same as get_mixing_fraction?)
   struct Depth
   {
      float32 rec;   // Not sure what rec stands for
      float32 min;
      float32 max;
   } depth_inch;     // The original data tables were in US units
   float32 ridge_height_inch;
   struct Roughness
   {  float32 initial_inch;
      float32 final_inch;
   } roughness;
   float32 surface_area_distributed; // percent
   // The following arrays have the index
   // 0  reserved for future used  (unknown)
   // 1  fragile_very_small (soybeans)
   // 2  moderately_tough_short (wheat)
   // 3  nonfragile_medium (corn)
   // 4  woody_larg
   // 5  gravel_rock
   float32  residue_flatten_ratio        [RUSLE2_RESIDUE_TYPE_COUNT];
   float32  residue_burial_ratio         [RUSLE2_RESIDUE_TYPE_COUNT];
   float32  residue_resurfacing_fraction [RUSLE2_RESIDUE_TYPE_COUNT];
   bool     kills_vegetation;                  // 080428 want to to modify the management editor interface that if the op kills vegetation then set terminate crop flag (which the user can disable if he wants)
   Soil_disturbance_effect soil_disturbance_effect; // Tillage type

   #ifdef USE_NEW_RUSLE2
   Disturbance disturbance;
   #else
   // In previous versions there was a separate table, but this
   // had redunent description and potential for mismatch
   #endif
};
//_____________________________________________________________________________/
//140515 #if ((CS_VERSION != 4) || defined(OFOOT_VERSION))
#ifdef USE_NEW_RUSLE2
struct Field_operation_composite_parameters
{  // The following are from the NRCS_SDR table
   nat16 number_dont_use;                          // field operation number numbers greater than 255 indicate codes we added in CropSyst to accomodate operation not defined by NRCS
   const char *operation_name;
   struct Speed
   {  float32  rec_MPH;  // Not sure what rec is
      float32  min_MPH;
      float32  max_MPH;
   } speed_MPH;      // The original data tables were in US units
   bool     kills_vegetation;
   const char *operations[12];
};
#endif
//_2013-08-10__________________________________________________________________/
class SDR_Field_operations
{
/*
public:
   class Parameters
   {
   public:
      NRCS_SDR_Field_operation_parameters       &SDR_parameters;
      NRCS_RUSLE2_Field_operation_parameters    &RUSLE2_parameters;

   public:
      Parameters(nat16 number);
   public: // accessors
      float32 get_mixing_fraction()                   const;  // also "Mixing ratio" or "Mmixing efficiency"
      Soil_disturbance_effect get_soil_disturbance_effect()           const;  // This can be an enum
      nat8   get_disturbance_rating()                const;
      float32 get_disturbance_depth_avg_m()               const;
#ifdef NYN
Currently we pass the array because we dont know the residue type
until we process each residue
      float32 get_standing_to_flat_residue_fraction(RUSLE2_Residue_type residue_type) const;
      float32 get_residue_fraction_not_incorporated(RUSLE2_Residue_type residue_type) const;
#endif
   };
*/
 public:
   SDR_Field_operations();
   nat16 lookup_operation_number(const char *_description)                 const;
   const char *get_description(nat16 number)                               const;
   float32 get_mixing_fraction(nat16 number)                       contribution_;  // also "Mixing ratio" or "Mmixing efficiency"
         //141204 was const  actually this is kind of const maybe should be provision
   Soil_disturbance_effect get_soil_disturbance_effect(nat16 number)       const;  // This can be an enum
   nat8   get_disturbance_rating(nat16 number)                             contribution_; //141204 const;
   float32 get_disturbance_depth_avg_m(nat16 number)                       const;
   const float32 *get_residue_flatten_ratio(nat16 number)                  const;
   const float32 *get_residue_burial_ratio(nat16 number)                   const;
   float32 get_roughness_initial_m(nat16 number)                           const;
//140515#if ((CS_VERSION != 4) || defined(OFOOT_VERSION))
#ifdef USE_NEW_RUSLE2
 public:
   const char **lookup_composite_operations(const char *NRCS_operation_description) const; //130710
 private:
   nat16 lookup_composite_operation_number(const char *_description)       const;//130710
   bool  estimate_disturbance_parameters                                         //141023
      (modifiable_ Field_operation_parameters &field_op_param)       contribution_; //141204 was modification_?
 public:      
   nat16 dump_disturbance_ratings(std::ostream &strm)                     const;
#endif
};
//______________________________________________________________________________
extern SDR_Field_operations SDR_field_operations;                                //120406
}}}; // namespace                                                                //120406
#endif


