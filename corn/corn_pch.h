#ifndef CORN_PCH_H
#define CORN_PCH_H

#  ifdef __BCPLUSPLUS__
#     include <float.h>
#  endif

#  include <math.h>
#  include <stdlib.h>
#  include <string.h>
//140313 #  include <corn/no_ns.h>
#  include <corn/primitive.h>

#  include <corn/string/strconv.h>
//131115 #  include <corn/string/uiostring.h>

#  include <corn/validate/validtyp.h>
#  include <corn/chronometry/date_types.hpp>
#  include <corn/chronometry/time_types.hpp>
//170926LML #  include <corn/datetime/date.hpp>
//170926LML #  include <corn/datetime/time.h>
//170926LML #  include <corn/datetime/datetime64.h>

#  include <corn/data_source/vv_file.h>
#  include <corn/format/spreadsheet/biff.h>

#  include <corn/math/compare.h>
#  include <corn/math/compare.hpp>
#  include <corn/math/moremath.h>
//#  include <corn/math/numerical/linrregr.h>
#  include <corn/math/random.hpp>
#  include <corn/math/statistical/stats.h>
#  include <corn/math/statistical/stats_best.h>
#  include <corn/math/statistical/stats.h>
#  include <corn/math/statistical/distribution_normal.h>

#  include <corn/OS/OS.h>

#endif
