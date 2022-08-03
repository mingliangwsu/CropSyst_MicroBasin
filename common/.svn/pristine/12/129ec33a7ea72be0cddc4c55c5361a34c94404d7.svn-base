#include <common/geolocation/UTM.h>

#include <corn/measure/measures.h>
#include <corn/math/moremath.h>
#include <math.h>
//______________________________________________________________________________
// This code was given to Roger Nelson by Javier Marcos, it was given to him by Ron Bolton
// I don't know where Ron got it

/*
Dim spheroid As Integer
Dim rad, er, rf, F, esq As Double
Dim eps, pr, en, A, b, C, U, V, W, r, OMO,  As Double
Dim sf, fe, fn As Double
Dim u0, u2, u4, u6 As Double
Dim v0 As Double, v2 As Double, v4 As Double, v6 As Double
Public zone As Integer
Public bUTM As Boolean
Public CentralMeridian As Double
Dim EquatorialRadius As Double
Dim ReciprocalOfFlattening As Double
Dim ddegreesLat As Double, ddegreesLon As Double
Dim calcNorthing As Double, calcEasting As Double
Dim calcNorth As Double, calcSouth As Double, calcEast As Double, calcWest As Double
Dim bUseCenter As Boolean
Dim MinutesLatitude As Double, SecondsLatitude As Double
Dim MinutesLongitude As Double, SecondsLongitude As Double
Dim MinutesLatitude27 As Double, SecondsLatitude27 As Double
Dim MinutesLongitude27 As Double, SecondsLongitude27 As Double
Dim fromEqRad As Double, fromFlat As Double
Dim toEqRad As Double, toFlat As Double
Const NAD27EqRad = 6378206.4
Const NAD27RF = 294.9786982
Const NAD27Flat = 1.0 / 294.9786982
*/
#define WGS84EqRad   6378137
#define WGS84RF      298.257223563
#define WGS84Flat    (1.0/ 298.257223563)
#define deltaXtoWGS  -8.0
#define deltaYtoWGS  160.0
#define deltaZtoWGS  176.0
// Const pi = 3.14159265358979
/*
Dim bToWGS As Boolean
Dim deltaX As Double
Dim deltaY As Double
Dim deltaZ As Double
Dim bLeftToRight As Boolean
Dim bFreeze As Boolean
Dim Lat84 As Double, Lon84 As Double, Ht84 As Double
Dim Lat27 As Double, Lon27 As Double, Ht27 As Double
Dim Northing27 As Double, Easting27 As Double
Dim Northing84 As Double, Easting84 As Double

Dim bUTM27 As Boolean
*/
//______________________________________________________________________________
UTM_geolocation::UTM_geolocation(bool _change_reference_elipsoid)
: zone(0)
, easting(0)
, northing(0)
, sf(0.9996)
, bUTM(false) // Not sure what to init to. VB code didn not init this.
, er(WGS84EqRad)
, rf(WGS84RF)
, change_reference_elipsoid(_change_reference_elipsoid)
, CentralMeridian(-117.0)
{};
//______________________________________________________________________________
bool UTM_geolocation::set_UTM(float64 _easting, float64 _northing, uint16 _zone)
{  easting = _easting;
   northing =  _northing;
   zone = _zone;
   return true;
};
//______________________________________________________________________________
bool UTM_geolocation::set_degrees(float64 latitude, float64 longitude)
{  // The original basic code appears to modify
   // the passed latitude and longitude.
   // I think because the easting and northing were returned in the same passed variabes
   // bad coading
   update_spheroid_parameters(WGS84EqRad, WGS84RF);
   if (!change_reference_elipsoid)
   {  er = WGS84EqRad;
      rf = WGS84RF;
   };
   longitude = (longitude < 0) ? -longitude : 360.0 - longitude;
   float64 cmerid = CentralMeridian;
   cmerid = (cmerid < 0) ? -cmerid : 360.0 - cmerid;
   int32    lod = (int32)longitude;
   float64  lam = deg_to_rad(longitude);   // was longitude / rad;
   float64  fi = deg_to_rad(latitude); // was latitude / rad
   zone = ((lod < 180 ) ? 30 : 90) - (lod / 6);
   int32 icm = ((lod < 180) ? 183 : 543)- 6 * zone;
   float64 cm = deg_to_rad((bUTM) ? icm : cmerid);
   // TMGRID in Fortran program
   float64 om = fi + A * sin(2.0 * fi) + b * sin(4.0 * fi) + C * sin(6.0 * fi);
   float64 S = r * om * sf;
   float64 sinfi = sin(fi);
   float64 cosfi = cos(fi);
   float64 tn = sinfi / cosfi;
   float64 ts = tn * tn;
   float64 ets = eps * cosfi * cosfi;
   float64 L = (lam - cm) * cosfi;
   float64 ls = L * L;
   float64 rn = sf * er / sqrt(1.0- esq * sinfi * sinfi);
   float64 a2 = rn * tn / 2.0;
   float64 a4 = (5.0- ts + ets * (9.0+ 4.0* ets)) / 12.0;
   float64 a6 = (61.0+ ts * (ts - 58.0) + ets * (270.0- 330.0* ts)) / 360.0;
   float64 a1 = -rn;
   float64 a3 = (1.0- ts + ets) / 6.0;
   float64 a5 = (5.0+ ts * (ts - 18.0) + ets * (14.0- 58.0* ts)) / 120.0;
   float64 a7 = (61.0- 479.0* ts + 179.0* ts * ts - pow(ts,3.0)) / 5040.0;
   easting /*latitude*/ = (S - so + a2 * ls * (1.0+ ls * (a4 + a6 * ls)) - fn);
   northing /*longitude*/ = (fe + a1 * L * (1.0+ ls * (a3 + ls * (a5 + a7 * ls))));
   return true; // Currently assumes always successful
};
//______________________________________________________________________________
bool UTM_geolocation::get_degrees(float64 &latitude, float64 &longitude)
{
   //    zone = 11
   // change reference ellipsoid
   update_spheroid_parameters(WGS84EqRad, WGS84RF);
   if (!change_reference_elipsoid)
   {  er = WGS84EqRad;
      rf = WGS84RF;
   };
// er rf already set and now using change_reference_elipsoid option
//   er = WGS84EqRad
//   rf = WGS84RF
   int16  icm = ((zone < 30) ?  183 :  543) - 6 * zone;
   float64 cm = deg_to_rad(icm); // icm / rad
   if (!bUTM )
   {  float64 cmerid = CentralMeridian;
      cmerid = (cmerid < 0) ? -cmerid : 360.0- cmerid;
      cm = deg_to_rad(cmerid); //  / rad
   };
   float64 om = (northing - fn + so) / (r * sf);
   if (om == 0.0) return false;
   float64 cosom = cos(om);
   float64 foot = om + sin(om) * cosom * (v0 + v2 * cosom * cosom + v4 * pow(cosom,4.0) + v6 * pow(cosom,6.0));
   float64 sinf = sin(foot);
   float64 cosf = cos(foot);
   float64 tn = sinf / cosf;
   float64 ts = tn * tn;
   float64 ets = eps * cosf * cosf;
   float64 rn = sf * er / sqrt(1.0- esq * sinf * sinf);
   float64 Q = (easting - fe) / rn;
   float64 qs = Q * Q;
   float64 b2 = -tn * (1.0+ ets) / 2.0;
   float64 b4 = -(5.0+ 3.0* ts + ets * (1.0- 9.0* ts) - 4.0* ets * ets) / 12.0;
   float64 b6 = (61.0+ 45.0* ts * (2.0+ ts) + ets * (46.0- 252.0* ts - 60.0* ts * ts)) / 360.0;
   float64 b1 = 1.0;
   float64 b3 = -(1.0+ ts + ts + ets) / 6.0;
   float64 b5 = (5.0+ ts * (28.0+ 24.0* ts) + ets * (6.0+ 8.0* ts)) / 120.0;
   float64 b7 = -(61.0+ 662.0* ts + 1320.0* ts * ts + 720.0* pow(ts,3)) / 5040.0;
   northing = foot + b2 * qs * (1.0+ qs * (b4 + b6 * qs));
   float64 L = b1 * Q * (1.0+ qs * (b3 + qs * (b5 + b7 * qs)));
   easting = -L / cosf + cm;
   northing = rad_to_deg(northing); // was rad * ourNorthing
   easting = rad_to_deg(easting); // rad * ourEasting
   easting = (easting > 180.0)
   ? 360 - easting
   : -easting;
   return true;
};
//______________________________________________________________________________
void UTM_geolocation::update_spheroid_parameters(float64 er,float64 rf)
{
/*
    Dim c2, c4, c6, c8 As Double
    Dim en2, en3, en4 As Double
*/
//NYI   OR1 = 0.0;
   so = 0.0;
   // parameter block
   fe = 500000.0;
   fn = 0.0;
   CentralMeridian = -117.0;
   // 'butm=false  KKKKKKKKKKKKKKKKKKKKKKKK
   // 'end parameter block
   // use deg_to_rad and rad_to)deg    rad = 180.0 / M_PI

    float64 F = 1.0/ rf;
            esq = F + F - F * F;
            eps = esq / (1.0- esq);
    float64 pr = (1.0- F) * er;
    float64 en = (er - pr) / (er + pr);
    float64 en2 = en * en;
    float64 en3 = en2 * en;
    float64 en4 = en3 * en;
    float64 c2 = -3.0* en / 2.0* 9.0* en3 / 16.0;
    float64 c4 = 15.0* en2 / 16.0- 15.0* en4 / 32.0;
    float64 c6 = -35.0* en3 / 48.0;
    float64 c8 = 315.0* en4 / 512.0;
//unused    float64 u0 = 2.0* (c2 - 2.0* c4 + 3.0* c6 - 4.0* c8);
//unused    float64 u2 = 8.0* (c4 - 4.0* c6 + 10.0* c8);
//unused    float64 u4 = 32.0* (c6 - 6.0* c8);
//unused    u6 = 128.0* c8;
    c2 = 3.0* en / 2.0- 27.0* en3 / 32.0;
    c4 = 21.0* en2 / 16.0- 55.0* en4 / 32.0;
    c6 = 151.0* en3 / 96.0;
    c8 = 1097.0* en4 / 512.0;
    v0 = 2.0* (c2 - 2.0* c4 + 3.0* c6 - 4.0* c8);
    v2 = 8.0* (c4 - 4.0* c6 + 10.0* c8);
    v4 = 32.0* (c6 - 6.0* c8);
    v6 = 128.0* c8;

    A = -1.5 * en + (9.0/ 16.0) * pow(en,3);
    b = 0.9375 * en * en - (15.0/ 32.0) * pow(en,4);
    C = -(35.0/ 48.0) * pow(en,3);
//unused    U = 1.5 * en - (27.0/ 32.0) * pow(en,3);
//unused    V = 1.3125 * en * en - (55.0/ 32.0) * pow(en,4);
//unused    W = (151.0/ 96.0) * pow(en,3);
    r = er * (1.0- en) * (1.0- en * en) * (1.0+ 2.25 * en * en + (225.0/ 64.0) * pow(en,4));
#ifdef NOT_YET_NEEDED
    // if not UTM, these must be changed:
//unused    'OMO=OR1+A*sin(2.0*OR1) + B*sin(4.0*OR1)+ C*sin(6.0 *OR1)
    'SO=sf*R*OMO
    'sf could be something else
#endif
    sf = 0.9996;
//unused    OMO = 0;
    so = 0;
};
//______________________________________________________________________________
#ifdef UNUSED
Not sure what this was for, it is not currently needed.

Public Sub GeoTranslate(ByVal fromLat As Double, ByVal fromLon As Double, _
ByVal fromHt As Double, ByRef toLat As Double, ByRef toLon As Double, _
ByRef toHt As Double)
Dim esq As Double
Dim bda As Double
Dim deltaFlat As Double
Dim deltaEqRad As Double
Dim sinLat As Double
Dim sinLon As Double
Dim cosLat As Double
Dim cosLon As Double
Dim rn As Double
Dim rm As Double
Dim deltaLat As Double
Dim deltaLon As Double
Dim deltaHt As Double
'To convert degrees to radians, multiply degrees by pi/180.
'To convert radians to degrees, multiply radians by 180/pi.
fromLat = fromLat * M_PI / 180.0
fromLon = fromLon * M_PI / 180.0
deltaFlat = toFlat - fromFlat
deltaEqRad = toEqRad - fromEqRad
sinLat = Sin(fromLat)
sinLon = Sin(fromLon)
cosLat = Cos(fromLat)
cosLon = Cos(fromLon)
bda = 1.0- fromFlat
esq = 2.0* fromFlat - fromFlat ^ 2
rn = fromEqRad / Sqr(1.0- esq * Sin(fromLat) ^ 2)
rm = fromEqRad * ((1.0- esq) / (1.0- esq * Sin(fromLat) ^ 2) ^ 1.5)
dLat1 = ((-deltaX * sinLat * cosLon - deltaY * sinLat * sinLon) + deltaZ * cosLat) _
+ deltaEqRad * (rn * esq * sinLat * cosLat) / fromEqRad
dLat2 = deltaFlat * (rm / bda + rn * bda) * sinLat * cosLat
deltaLat = (dLat1 + dLat2) / (rm + fromHt)
deltaLon = (-deltaX * sinLon + deltaY * cosLon) / ((rn + fromHt) * cosLat)
deltaHt = deltaX * cosLat * cosLon + deltaY * cosLat * sinLon _
+ deltaZ * sinLat - deltaEqRad * (fromEqRad / rn) + deltaFlat * bda * rn * sinLat ^ 2

toLat = (fromLat + deltaLat) * 180 / M_PI
toLon = (fromLon + deltaLon) * 180 / M_PI
toHt = fromHt + deltaHt
End Sub
#endif
//______________________________________________________________________________



#ifdef UNUSED
Private Sub MolodenskyFlip(bChangeTo As Boolean)
If bChangeTo = False Then
deltaX = -deltaXtoWGS
deltaY = -deltaYtoWGS
deltaZ = -deltaZtoWGS
fromEqRad = WGS84EqRad
fromFlat = WGS84Flat
toEqRad = NAD27EqRad
toFlat = NAD27Flat
Else
deltaX = deltaXtoWGS
deltaY = deltaYtoWGS
deltaZ = deltaZtoWGS
fromEqRad = NAD27EqRad
fromFlat = NAD27Flat
toEqRad = WGS84EqRad
toFlat = WGS84Flat
End If
bToWGS = bChangeTo
End Sub
#endif
//______________________________________________________________________________
#ifdef OBSOLETE
this was commented out of the original BASIC code.
'Private Sub UserControl_Initialize()
'    Dim c2, c4, c6, c8 As Double
'    Dim en2, en3, en4 As Double
'SwitchLight(0).Visible = True
'For I = 1 To 3
'SwitchLight(I).Visible = False
'Next I
'zone = Val(UTMzone.Text)
'
'fromEqRad = WGS84EqRad
'fromFlat = WGS84Flat
'toEqRad = NAD27EqRad
'toFlat = NAD27Flat
'bToWGS = False
'
'deltaX = -deltaXtoWGS
'deltaY = -deltaYtoWGS
'deltaZ = -deltaZtoWGS
'leftLat = leftLon = leftHt = 0
'rightLat = rightLon = rightHt = 0
'    bUseCenter = True
'    Lon84 = Val(Longitude.Text)
'    Lat84 = Val(Latitude.Text)
'    Northing27 = Val(Northing.Text)
'    Easting27 = Val(Easting.Text)
'    zone = 11 'default location
'    EquatorialRadius = 6378206.4
'    OR1 = 0.0
'    ReciprocalOfFlattening = 294.978698
'    so = 0.0
'    fe = 500000.0
'    fn = 0.0
'    rad = 180.0/ pi
'    er = EquatorialRadius
'    rf = ReciprocalOfFlattening
'    F = 1.0/ rf
'    esq = F + F - F * F
'    eps = esq / (1.0- esq)
'    pr = (1.0- F) * er
'    en = (er - pr) / (er + pr)
'    en2 = en * en
'    en3 = en2 * en
'    en4 = en3 * en
'    c2 = -3.0* en / 2.0* 9.0* en3 / 16.0
'    c4 = 15.0* en2 / 16.0- 15.0* en4 / 32.0
'    c6 = -35.0* en3 / 48.0
'    c8 = 315.0* en4 / 512.0
'    u0 = 2.0* (c2 - 2.0* c4 + 3.0* c6 - 4.0* c8)
'    u2 = 8.0* (c4 - 4.0* c6 + 10.0* c8)
'    u4 = 32.0* (c6 - 6.0* c8)
'    u6 = 128.0* c8
'    c2 = 3.0* en / 2.0- 27.0* en3 / 32.0
'    c4 = 21.0* en2 / 16.0- 55.0* en4 / 32.0
'    c6 = 151.0* en3 / 96.0
'    c8 = 1097.0* en4 / 512.0
'    v0 = 2.0* (c2 - 2.0* c4 + 3.0* c6 - 4.0* c8)
'    v2 = 8.0* (c4 - 4.0* c6 + 10.0* c8)
'    v4 = 32.0* (c6 - 6.0* c8)
'    v6 = 128.0* c8
'
'    A = -1.5 * en + (9.0/ 16.0) * en ^ 3
'    b = 0.9375 * en * en - (15.0/ 32.0) * en ^ 4
'    C = -(35.0/ 48.0) * en ^ 3
'    U = 1.5 * en - (27.0/ 32.0) * en ^ 3
'    V = 1.3125 * en * en - (55.0/ 32.0) * en ^ 4
'    W = (151.0/ 96.0) * en ^ 3
'    r = er * (1.0- en) * (1.0- en * en) * (1.0+ 2.25 * en * en + (225.0/ 64.0) * en ^ 4)
'    'if not UTM, these must be changed:
'    'OMO=OR1+A*sin(2.0*OR1) + B*sin(4.0*OR1)+ C*sin(6.0 *OR1)
'    'SO=sf*R*OMO
'    'sf could be something else
'    sf = 0.9996
'    OMO = 0
'    so = 0
'    Latitude = 47.0
'    Longitude = -117.0
'End Sub

#endif
//______________________________________________________________________________




