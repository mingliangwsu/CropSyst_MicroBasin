#ifndef moremathHPP
#define moremathHPP

#include <math.h>
#ifndef moremathH
#   include "corn/math/moremath.h"
#endif

template <typename T_absisca,typename T_ordinate >
T_ordinate interpolate(T_absisca abscissa, T_absisca *abscissae, T_ordinate *ordinates, int points_count)
{
  int i;
  for (i = 0; i < (points_count -1); i++)
  {
    if ((abscissa >= abscissae[i]) && (abscissa <= abscissae[i+1]))
    { T_ordinate value_range = ordinates[i+1] - ordinates[i];
      T_absisca abscissas_range =abscissae[i+1] - abscissae[i];
      T_absisca xX = abscissa - abscissae[i];
      T_ordinate valueX = (value_range != 0) ? (T_ordinate)xX * (T_ordinate)value_range / (T_ordinate)abscissas_range  : ordinates[i];
      return ordinates[i] + valueX;
    }
  };
  return (ordinates[points_count-1]); // catch all
};

#endif

