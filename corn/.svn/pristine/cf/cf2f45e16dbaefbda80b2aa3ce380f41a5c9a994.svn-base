#ifndef observationH
#define observationH

#include "corn/primitive.h"
#include "corn/container/bilist.h"
namespace CORN
{
//______________________________________________________________________________
class Coordinate     // Rename to Observation
: public Item
{  float32  abscissa;   // X  dependent
   float32  ordinate;   // Y  independent
public:
   Coordinate(float32  _abcissa,float32  _ordinate);
   inline virtual float32  get_abscissa()          mutation_{ return abscissa; }
   inline virtual float32  get_ordinate()      contribution_{ return ordinate; }  // Pure must be provided in derived point class.
   inline virtual int          compare(const Item &other)                 const
   {  float32 other_abscissa = ((Coordinate &)other).get_abscissa();
      return (abscissa < other_abscissa ) ? -1 : (abscissa > other_abscissa ) ? 1 : 0;
   }
};
//_class_Coordinate_________________________________________________2018-04-26_/
class Observations
: public extends_ Bidirectional_list
// container of Interpolation points (bidirectional becuse must be sortabled)
{
 public:
   mutable Coordinate  initial_value;
   mutable Coordinate *last_point;  // actually prev_point
   mutable Coordinate *next_point;
 public:
   Observations
      (float32 initial_abscissa=0
      ,float32 initial_ordinate=0
      );
   Observations
      (const float32 priming_abscissa[]
      ,const float32 priming_ordinates[]
      ,nat32 points_alloc);
   virtual Coordinate */*180430 float32 */append(float32 initial_abscissa, float32 ordinate);
   void setup_current_range(float32 abscissa)                      contribution_;
   virtual nat32 delete_all(Item::Filter filter = Item::filter_all);
   // Returns the number of items deleted
};
//_class_Observations_______________________________________________2018-04-26_/

//______________________________________________________________________________
} // namespace CORN

#endif
