#error check obsolete
#ifndef parameter_interpolationH
#define parameter_interpolationH
#include "corn/math/numerical/interpolator.h"
#include "corn/parameters/number_keyed.h"
namespace CORN
{
//______________________________________________________________________________
class Parameter_interpolation_dated  // rename to Parameter_interpolator_temporal
: public implements_ CORN::Item
{
   const       CORN::Date   &today;
   modifiable_ Number_keyed &parameter;
   //180426 Interpolation_curve_dated curve;   // owned always instanciated
   Interpolation_temporal curve;   // owned always instanciated
 public:
   Parameter_interpolation_dated
      (Interpolation_curve_type curve_type
      ,const CORN::Date     &_today
      ,Number_keyed  &_parameter);

   bool update();
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return parameter == key; }
   inline virtual bool is_key_wstring(const std::wstring &key)              affirmation_  //180820
      { return parameter == key; } NYI

/*180820  was probably only used for find_cstr now using is_key

   inline virtual const char *get_key()                                    const { return parameter.get_key(); }
   inline virtual const wchar_t  *get_key_wide()                           const { return parameter.get_key_wide(); } //110828
*/   

};
//_2015-01-11__________________________________________Parameter_interpolation_/
} // namespace CORN
#endif // PARAMETER_INTERPOLATION_H
