//LatLong- UTM conversion..h
//definitions for lat/long to UTM and UTM to lat/lng conversions
#include <string.h>
#include "corn/primitive.h"

#ifndef LatLong_UTMconversionH
#define LatLong_UTMconversionH
//______________________________________________________________________________
void LLtoUTM
   (int ReferenceEllipsoid
   , const float32 Lat, const float32 Long
   ,  double &UTMNorthing, double &UTMEasting, char* UTMZone);
void UTMtoLL
   (int ReferenceEllipsoid
   , const double UTMNorthing, const double UTMEasting, const char* UTMZone
   , float32& Lat,  float32& Long );
char UTMLetterDesignator
   (float32 Lat);
void LLtoSwissGrid
(const float32 Lat, const float32 Long
,double &SwissNorthing, double &SwissEasting);
void SwissGridtoLL
(const double SwissNorthing, const double SwissEasting
,float32 & Lat, float32 & Long);
//______________________________________________________________________________
class Ellipsoid
{
public:
   Ellipsoid(){};
   Ellipsoid(int Id, char* name, double radius, double ecc)
   {  id = Id; ellipsoidName = name;
      EquatorialRadius = radius; eccentricitySquared = ecc;
   }
   int id;
   char* ellipsoidName;
   double EquatorialRadius;
   double eccentricitySquared;
};
//______________________________________________________________________________

#endif
