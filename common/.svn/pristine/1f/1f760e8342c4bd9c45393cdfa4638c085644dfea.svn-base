//UTM Conversion.cpp- test program for lat/long to UTM and UTM to lat/long conversions
#include <corn/std/std_iostream.h>
#include <corn/std/std_iomanip.h>

#include "LatLong-UTMconversion.h"

using namespace std;
//______________________________________________________________________________
void main()
{
   float32 Lat = 47.37816667;                                                    //171128
   float32 Long = 8.23250000;                                                    //171128
   double UTM_northing;
   double UTM_easting;
   double SwissNorthing;
   double SwissEasting;
   char UTM_zone[4];
   int RefEllipsoid = 23;//WGS-84. See list with file "LatLong- UTM conversion.cpp" for id numbers

   cout << "Starting position(Lat, Long):  " << Lat << "   " << Long <<endl;

   LLtoUTM(RefEllipsoid, Lat, Long, UTM_northing, UTM_easting, UTM_zone);
   cout << setiosflags(ios::showpoint | ios::fixed) << setprecision(5);
   cout << "Calculated UTM position(Northing, Easting, Zone):  ";
   cout << UTM_northing << "   " << UTM_easting;
   cout << "   " << UTM_zone <<endl;

   UTMtoLL(RefEllipsoid, UTM_northing, UTM_easting, UTM_zone, Lat, Long);
   cout << "Calculated Lat, Long position(Lat, Long):  " << Lat << "   " << Long << endl <<endl;

   LLtoSwissGrid(Lat, Long, SwissNorthing, SwissEasting);
   cout << setiosflags(ios::showpoint | ios::fixed) << setprecision(5);
   cout << "Calculated Swiss Grid position(Northing, Easting):  ";
   cout << SwissNorthing << "   " << SwissEasting << endl;
}
//______________________________________________________________________________

/* N 47.38195° E 8.54879°  (Swiss Grid: 683.748 248.342)
  N 47°12.625' / E 7° 27.103'= N 47.21041667 E 7.45171667(Swiss Grid = 600920/228685) 
  N 47°22.690' / E 8° 13.950'= N 47.37816667 E 8.23250000 (Swiss Grid = 659879/247637)
*/
