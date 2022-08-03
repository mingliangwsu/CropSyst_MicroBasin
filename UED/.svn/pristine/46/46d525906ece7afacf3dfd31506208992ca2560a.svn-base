
#ifdef USE_PCH
#  include <UED/UED_pch.h>
#pragma hdrstop
#else
#  include <corn/primitive.h>
#include <UED/codes.h>
#endif
#ifndef CORN_VALIDTYP_H
#  include <corn/validate/validtyp.h>
#endif

UED_quality_attribute  UED_XXX_from_quality(UED_quality_attribute base_quality, UED_quality_attribute from_quality)
{
   UED_quality_attribute new_quality = base_quality;

   if (UED_is_valid(base_quality))
       new_quality = (UED_quality_attribute)(((base_quality & 0x3F) << 2) | from_quality);
   // else just return in current invalid quality
   return new_quality;
};


UED_quality_attribute UED_calculated_from(UED_quality_attribute  qual)
{  UED_quality_attribute calc_from_quality = UED_XXX_from_quality(qual,UED_calculated);
   UED_quality_attribute result = UED_limit_from_quality(calc_from_quality,qual);
   return result;
};

UED_quality_attribute UED_estimated_from(UED_quality_attribute  qual)
{  UED_quality_attribute est_from_quality = UED_XXX_from_quality(qual,UED_estimated);
   UED_quality_attribute result = UED_limit_from_quality(est_from_quality,qual);
   return result;
};

UED_quality_attribute UED_forecasted_from(UED_quality_attribute  qual)
{  UED_quality_attribute forc_from_quality = UED_XXX_from_quality(qual,UED_forecasted);
   UED_quality_attribute result = UED_limit_from_quality(forc_from_quality,qual);
   return result;
};

UED_quality_attribute UED_generated_from(UED_quality_attribute  qual)
{  UED_quality_attribute gen_from_quality = UED_XXX_from_quality(qual,UED_generated);
   UED_quality_attribute result = UED_limit_from_quality(gen_from_quality,qual);
   return result;
};

UED_quality_attribute UED_invalidate(UED_quality_attribute &quality)
{
   uint32 new_quality =  (uint32)quality | UED_not_valid;
           // sets the quality as not valid and returns the modified quality
   quality = (UED_quality_attribute)new_quality;
   return quality;
};

UED_quality_attribute validation_status_to_UED_quality_attribute(CORN::Validation_status validation_status)
{
   UED_quality_attribute quality = UED_measured;
   switch (validation_status)
   {  case CORN::unavailable_status    : quality = UED_measured;                    break; // with no other information, assume measured;
      case CORN::missing_status        : quality = UED_missing;                     break;
      case CORN::error_low_status      : quality = UED_out_of_range_low_error;      break;
      case CORN::error_status          : quality = UED_out_of_range_error;          break;
      case CORN::error_high_status     : quality = UED_out_of_range_high_error;     break;
      case CORN::pot_error_low_status  : quality = UED_out_of_range_pot_low_error;  break;
      case CORN::pot_error_status      : quality = UED_out_of_range_pot_error;      break;
      case CORN::pot_error_high_status : quality = UED_out_of_range_pot_high_error; break;
      case CORN::warning_low_status    : quality = UED_out_of_range_low_warning;    break;
      case CORN::warning_status        : quality = UED_out_of_range_warning;        break;
      case CORN::warning_high_status   : quality = UED_out_of_range_high_warning;   break;
      case CORN::ready_status          : quality = UED_measured;                    break;
      case CORN::good_status           : quality = UED_measured;                    break;
//NYI      case disabled_status       : quality = UED_xxxxx;           break;
   };
   return quality;
};
