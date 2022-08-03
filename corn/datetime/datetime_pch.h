#ifndef DATETIME_PCH_H
#define DATETIME_PCH_H

// The following includes are OS specific for computer date

#if defined(__MSDOS__) || defined(_Windows) || defined(_WIN32)
// for computer date
#  include <dos.h>
#endif

#ifdef __unix
#  include <time.h>
#endif

#  include "corn/corn_pch.h"

#  include "corn/chronometry/date_types.hpp"
#  include "corn/chronometry/time_types.hpp"
#  include "corn/datetime/temporal_base.h"
#  include "corn/datetime/datetime64.h"
#  include "corn/datetime/date.hpp"
#  include "corn/datetime/time.h"
#endif
