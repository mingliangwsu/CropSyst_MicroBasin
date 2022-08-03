#ifndef compareH
#define compareH
#ifndef primitiveH
#  include "corn/primitive.h"
#endif

#define CORN_min(x,y)  ((x < y) ? x : y)
#define CORN_max(x,y)  ((x > y) ? x : y)
#define CORN_must_be_between(target,low,high) (CORN_min(CORN_max(target,low),high))
#define CORN_must_be_greater_or_equal_to(x,y) (CORN_max(x,y))
#define CORN_must_be_less_or_equal_to(x,y)    (CORN_min(x,y))
#define CORN_is_essentially(value,target,tolerance) (((value) < ((target) + (tolerance))) && ((value) > ((target) - (tolerance))))
#define CORN_is_approximately(value,target,tolerance) (((value) < ((target) +(tolerance))) && ((value) > ((target) - (tolerance))))

/*050630_*/ extern int CORN_compare_float(float value1, float value2);
/*050630_*/ extern int CORN_compare_int(int value1, int value2);

#ifdef unix
// In Borland  stricmp is the case insensitive version of strcmp,
// under UNIX (at least the SUN Forte compiler) it is called strcasecmp.
#  define stricmp(x,y) strcasecmp(x,y)
#endif

#endif
//compare

