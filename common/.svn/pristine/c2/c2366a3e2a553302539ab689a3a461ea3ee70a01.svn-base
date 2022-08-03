#ifndef UTMH
#define UTMH

#include "corn/primitive.h"
#include "corn/const.h"

// This class provides methods for working with UTM coordinates
// - Conversion between decimal degrees.


// The original BASIC code was given to Roger Nelson by Javier Marcos,
// it was given to him by Ron Bolton I don't know where Ron got it
// Looks like it was originally FORTRAN

/*
   Each zone is 1,000,000 meters wide and 10,000,000 meters long
   The vertical origin for the northern hemisphere is the equator
   and the south pole for the southern hemisphere
*/
//______________________________________________________________________________
class UTM_Coordinate  // was UTM_Geocoordinate was UTM_geolocation                                  //160925
{protected:
   float64  easting;
   float64  northing;
 public:
   sint16   zone;       // negative zones are in the southern hemisphere
   char     zone_designator;
   int      reference_ellipsoid_index;   // parameter
 public:
   UTM_Coordinate();
   bool set_UTM(float64 _easting, float64 _northing, sint16 _zone,char _zone_designator);
   bool set_degrees(float32 latitude, float32 longitude);
      // 32bit floats provide quite adequate precision for geocoordinate 171127
   // The original basic code appears to modify
   // the passed latitude and longitude.  I don't know why.
   inline float64 get_easting()  const { return easting; }
   inline float64 get_northing() const { return northing; }
   inline float64 &mod_easting()       { return easting; }
   inline float64 &mod_northing()      { return northing; }

   inline sint16   get_zone()    const { return zone; }
   // Negative zones are in the southern hemispher
   inline char    get_zone_designator() const { return zone_designator; }
   bool get_degrees(float32 &latitude, float32 &longitude);
      // 32bit floats provide quite adequate precision for geocoordinate 171127

   inline virtual bool is_in_northern_hemisphere()                  affirmation_
      {  return zone_designator == 'N';
         // Warning presuming not military UTM where zone designators are
      }

#ifdef NYI
   bool change_zone(int16 new_zone);
   // Some times it is desirable to have all coordinates in the same zone
   // this will change the current coordinates to the specified zone.
   // Only adjacent zones can be reliably converted.
   // returns false if the zones are not adjacent
#endif
};
//______________________________________________________________________________

// Conceptual has specialized UTM for military where zones are A to Z not N and S

#endif





