#include "weather/parameter/WP_dew_point_temperature.h"
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include <math.h>
#include "corn/math/moremath.h"
#include "weather/weather_types.h"
#include "weather/parameter/WP_vapor_pressure.h"
#include "weather/parameter/WP_vapor_pressure_deficit.h"
#include "weather/parameter/WP_air_temperature.h"
#ifndef qualityHPP
#  include "corn/quality.hpp"
#endif
#ifndef constH
#  include "corn/const.h"
#endif
#include "weather/parameter/WP_relative_humidity.h"

#define value measure.amount
using namespace CORN;
//______________________________________________________________________________

