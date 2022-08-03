#ifndef UED_adjustor_engineH
#define UED_adjustor_engineH
#include "UED/library/varcodes.h"
#include "corn/math/numerical/interpolation/interpolator_temporal.h"
#include "corn/OS/file_system.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/container/enumlist.h"
namespace UED {
enum Adjustment_mode
{  UNKNOWN_ADJUSTMENT
,  DELTA_ADJUSTMENT
,  SCALE_ADJUSTMENT
};
using namespace CORN;
//______________________________________________________________________________
class Adjustor_engine
{
   //___________________________________________________________________________
   class Interpolator
   : public extends_    CORN::Interpolator_temporal 
   , public implements_ CORN::Enumeration // by var_code
   {
    public:
      UED::Variable_code var_code;
      bool adjustment_mode; // either SCALE_ADJUSTMENT or DELTA_ADJUSTMENT
    public:
      inline Interpolator
         (Interpolation_curve_type  curve_type_
         ,UED::Variable_code        var_code_
         ,bool                      adjustment_mode_)
         : CORN::Interpolator_temporal
            (curve_type_,0.0)
         , var_code        (var_code_)
         , adjustment_mode (adjustment_mode_)
         {}
      inline virtual bool is_key_nat32(nat32 key)                  affirmation_  //180820
         { return var_code == key; }
      inline virtual nat32 get_key_nat32()     const { return (nat32)var_code; }
   };
   //___________________________________________________________________________
   CORN::Enumeration_list interpolations;  // rename to interpolators

 public:
   Adjustor_engine();
   nat32 load_adjustments
      (const CORN::OS::File_name     &adjustment_file_name
      ,CORN::Interpolation_curve_type interpolation_mode
      ,Adjustment_mode                adjustment_mode);
   bool adjust_file
      (const CORN::OS::File_name_concrete &source_file
      ,const CORN::OS::File_name_concrete &target_file);
   nat32 adjust_directory
      (const CORN::OS::Directory_name_concrete &source_directory
      ,const CORN::OS::Directory_name_concrete &target_directory);
};
//_2015-03-08__________________________________________________Adjustor_engine_/
} // namespace UED
#endif