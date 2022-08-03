
// This code was given to Roger Nelson by Javier Marcos, it was given to him by Ron Bolton
// I don't know where Ron got it

Attribute VB_Name = "UTM"
Option Explicit

Dim spheroid As Integer
Dim OR1 As Double
Dim rad, er, rf, F, esq As Double
Dim eps, pr, en, A, b, C, U, V, W, r, OMO, so As Double
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
Const NAD27Flat = 1# / 294.9786982
Const WGS84EqRad = 6378137#
Const WGS84RF = 298.257223563
Const WGS84Flat = 1# / 298.257223563
Const deltaXtoWGS = -8#
Const deltaYtoWGS = 160#
Const deltaZtoWGS = 176#
Const pi = 3.14159265358979
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
Public Sub MakeLatLonIntoUTM(ByRef someLat As Double, ByRef someLon As Double)
   Dim cmerid As Double
   Dim lod, icm As Integer
   Dim lam As Double, fi, cm As Double
   Dim om As Double, S As Double, sinfi As Double, cosfi As Double, tn As Double
   Dim ts As Double, ets As Double, L As Double, ls As Double, rn As Double
   Dim a1 As Double, a2 As Double, a3 As Double, a4 As Double, a5 As Double, a6 As Double, a7 As Double
   'edit next 3 lines to change reference ellipsoid
   UpdateSpheroidParameters WGS84EqRad, WGS84RF
   er = WGS84EqRad
   rf = WGS84RF
   'end change ellipsoid
   If someLon < 0 Then
        someLon = -someLon
    Else
        someLon = 360# - someLon
    End If
    cmerid = CentralMeridian
    If cmerid < 0 Then
        cmerid = -cmerid
    Else
        cmerid = 360# - cmerid
    End If
    lod = Int(someLon)
    lam = someLon / rad
    fi = someLat / rad
    If lod < 180 Then
    zone = 30 - Int(lod / 6)
    Else
    zone = 90 - Int(lod / 6)
    End If
    If lod < 180 Then
    icm = 183 - 6 * zone
    Else
    icm = 543 - 6 * zone
    End If
    If bUTM = True Then
    cm = icm / rad
    Else
    cm = cmerid / rad
    End If
    
    'TMGRID in Fortran program
    om = fi + A * Sin(2# * fi) + b * Sin(4# * fi) + C * Sin(6# * fi)
    S = r * om * sf
    sinfi = Sin(fi)
    cosfi = Cos(fi)
    tn = sinfi / cosfi
    ts = tn * tn
    ets = eps * cosfi * cosfi
    L = (lam - cm) * cosfi
    ls = L * L
    rn = sf * er / Sqr(1# - esq * sinfi * sinfi)
    a2 = rn * tn / 2#
    a4 = (5# - ts + ets * (9# + 4# * ets)) / 12#
    a6 = (61# + ts * (ts - 58#) + ets * (270# - 330# * ts)) / 360#
    a1 = -rn
    a3 = (1# - ts + ets) / 6#
    a5 = (5# + ts * (ts - 18#) + ets * (14# - 58# * ts)) / 120#
    a7 = (61# - 479# * ts + 179# * ts * ts - ts ^ 3) / 5040#
    someLat = (S - so + a2 * ls * (1# + ls * (a4 + a6 * ls)) - fn)
    someLon = (fe + a1 * L * (1# + ls * (a3 + ls * (a5 + a7 * ls))))
    


End Sub
    

Public Sub MakeUTMIntoLatLon(ByRef ourNorthing As Double, ByRef ourEasting As Double)
   Dim icm As Integer
   Dim cm As Double, cmerid As Double
   Dim Q, qs As Double
   Dim om As Double, sinf As Double, cosf As Double, tn As Double, ts As Double
   Dim ets As Double, L As Double, rn As Double
   Dim b1 As Double, b2 As Double, b3 As Double, b4 As Double, b5 As Double
   Dim b6 As Double, b7 As Double, cosom As Double, foot As Double
    
    zone = 11
     'edit next 3 lines to change reference ellipsoid
   UpdateSpheroidParameters WGS84EqRad, WGS84RF
   er = WGS84EqRad
   rf = WGS84RF
   'end change ellipsoid
    If zone < 30 Then
    icm = 183 - 6 * zone
    Else:
    icm = 543 - 6 * zone
    End If
    If bUTM Then
    cm = icm / rad
    Else
        cmerid = CentralMeridian
        If cmerid < 0 Then
            cmerid = -cmerid
        Else
            cmerid = 360# - cmerid
        End If
    cm = cmerid / rad
    End If
    om = (ourNorthing - fn + so) / (r * sf)
    cosom = Cos(om)
    foot = om + Sin(om) * cosom * (v0 + v2 * cosom * cosom + v4 * cosom ^ 4 + v6 * cosom ^ 6)
    sinf = Sin(foot)
    cosf = Cos(foot)
    tn = sinf / cosf
    ts = tn * tn
    ets = eps * cosf * cosf
    rn = sf * er / Sqr(1# - esq * sinf * sinf)
    Q = (ourEasting - fe) / rn
    qs = Q * Q
    b2 = -tn * (1# + ets) / 2#
    b4 = -(5# + 3# * ts + ets * (1# - 9# * ts) - 4# * ets * ets) / 12#
    b6 = (61# + 45# * ts * (2# + ts) + ets * (46# - 252# * ts - 60# * ts * ts)) / 360#
    b1 = 1#
    b3 = -(1# + ts + ts + ets) / 6#
    b5 = (5# + ts * (28# + 24# * ts) + ets * (6# + 8# * ts)) / 120#
    b7 = -(61# + 662# * ts + 1320# * ts * ts + 720# * ts ^ 3) / 5040#
    ourNorthing = foot + b2 * qs * (1# + qs * (b4 + b6 * qs))
    L = b1 * Q * (1# + qs * (b3 + qs * (b5 + b7 * qs)))
    ourEasting = -L / cosf + cm
    ourNorthing = rad * ourNorthing
    ourEasting = rad * ourEasting
    
    If ourEasting > 180# Then
    ourEasting = 360 - ourEasting
    Else
    ourEasting = -ourEasting
    End If
End Sub
    
Public Function DegMinutes(decDeg As Double) As Double
    If decDeg > 0 Then
    DegMinutes = (decDeg - Int(decDeg)) * 60
    Else
    DegMinutes = (Int(decDeg + 1) - decDeg) * 60
    End If

End Function
Public Function MinSeconds(decMinutes As Double) As Double
    MinSeconds = (decMinutes - Int(decMinutes)) * 60
End Function

Sub UpdateSpheroidParameters(er As Double, rf As Double)
    Dim c2, c4, c6, c8 As Double
    Dim en2, en3, en4 As Double
       OR1 = 0#
    so = 0#
   'parameter block
    fe = 500000#
   fn = 0#
    CentralMeridian = -117#
        'butm=false  KKKKKKKKKKKKKKKKKKKKKKKK
'end parameter block
    rad = 180# / pi

    F = 1# / rf
    esq = F + F - F * F
    eps = esq / (1# - esq)
    pr = (1# - F) * er
    en = (er - pr) / (er + pr)
    en2 = en * en
    en3 = en2 * en
    en4 = en3 * en
    c2 = -3# * en / 2# * 9# * en3 / 16#
    c4 = 15# * en2 / 16# - 15# * en4 / 32#
    c6 = -35# * en3 / 48#
    c8 = 315# * en4 / 512#
    u0 = 2# * (c2 - 2# * c4 + 3# * c6 - 4# * c8)
    u2 = 8# * (c4 - 4# * c6 + 10# * c8)
    u4 = 32# * (c6 - 6# * c8)
    u6 = 128# * c8
    c2 = 3# * en / 2# - 27# * en3 / 32#
    c4 = 21# * en2 / 16# - 55# * en4 / 32#
    c6 = 151# * en3 / 96#
    c8 = 1097# * en4 / 512#
    v0 = 2# * (c2 - 2# * c4 + 3# * c6 - 4# * c8)
    v2 = 8# * (c4 - 4# * c6 + 10# * c8)
    v4 = 32# * (c6 - 6# * c8)
    v6 = 128# * c8

    A = -1.5 * en + (9# / 16#) * en ^ 3
    b = 0.9375 * en * en - (15# / 32#) * en ^ 4
    C = -(35# / 48#) * en ^ 3
    U = 1.5 * en - (27# / 32#) * en ^ 3
    V = 1.3125 * en * en - (55# / 32#) * en ^ 4
    W = (151# / 96#) * en ^ 3
    r = er * (1# - en) * (1# - en * en) * (1# + 2.25 * en * en + (225# / 64#) * en ^ 4)
    'if not UTM, these must be changed:
    'OMO=OR1+A*sin(2.0*OR1) + B*sin(4.0*OR1)+ C*sin(6.0 *OR1)
    'SO=sf*R*OMO
    'sf could be something else
    sf = 0.9996
    OMO = 0
    so = 0
End Sub

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
fromLat = fromLat * pi / 180#
fromLon = fromLon * pi / 180#
deltaFlat = toFlat - fromFlat
deltaEqRad = toEqRad - fromEqRad
sinLat = Sin(fromLat)
sinLon = Sin(fromLon)
cosLat = Cos(fromLat)
cosLon = Cos(fromLon)
bda = 1# - fromFlat
esq = 2# * fromFlat - fromFlat ^ 2
rn = fromEqRad / Sqr(1# - esq * Sin(fromLat) ^ 2)
rm = fromEqRad * ((1# - esq) / (1# - esq * Sin(fromLat) ^ 2) ^ 1.5)
dLat1 = ((-deltaX * sinLat * cosLon - deltaY * sinLat * sinLon) + deltaZ * cosLat) _
+ deltaEqRad * (rn * esq * sinLat * cosLat) / fromEqRad
dLat2 = deltaFlat * (rm / bda + rn * bda) * sinLat * cosLat
deltaLat = (dLat1 + dLat2) / (rm + fromHt)
deltaLon = (-deltaX * sinLon + deltaY * cosLon) / ((rn + fromHt) * cosLat)
deltaHt = deltaX * cosLat * cosLon + deltaY * cosLat * sinLon _
+ deltaZ * sinLat - deltaEqRad * (fromEqRad / rn) + deltaFlat * bda * rn * sinLat ^ 2

toLat = (fromLat + deltaLat) * 180 / pi
toLon = (fromLon + deltaLon) * 180 / pi
toHt = fromHt + deltaHt
End Sub









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
'    OR1 = 0#
'    ReciprocalOfFlattening = 294.978698
'    so = 0#
'    fe = 500000#
'    fn = 0#
'    rad = 180# / pi
'    er = EquatorialRadius
'    rf = ReciprocalOfFlattening
'    F = 1# / rf
'    esq = F + F - F * F
'    eps = esq / (1# - esq)
'    pr = (1# - F) * er
'    en = (er - pr) / (er + pr)
'    en2 = en * en
'    en3 = en2 * en
'    en4 = en3 * en
'    c2 = -3# * en / 2# * 9# * en3 / 16#
'    c4 = 15# * en2 / 16# - 15# * en4 / 32#
'    c6 = -35# * en3 / 48#
'    c8 = 315# * en4 / 512#
'    u0 = 2# * (c2 - 2# * c4 + 3# * c6 - 4# * c8)
'    u2 = 8# * (c4 - 4# * c6 + 10# * c8)
'    u4 = 32# * (c6 - 6# * c8)
'    u6 = 128# * c8
'    c2 = 3# * en / 2# - 27# * en3 / 32#
'    c4 = 21# * en2 / 16# - 55# * en4 / 32#
'    c6 = 151# * en3 / 96#
'    c8 = 1097# * en4 / 512#
'    v0 = 2# * (c2 - 2# * c4 + 3# * c6 - 4# * c8)
'    v2 = 8# * (c4 - 4# * c6 + 10# * c8)
'    v4 = 32# * (c6 - 6# * c8)
'    v6 = 128# * c8
'
'    A = -1.5 * en + (9# / 16#) * en ^ 3
'    b = 0.9375 * en * en - (15# / 32#) * en ^ 4
'    C = -(35# / 48#) * en ^ 3
'    U = 1.5 * en - (27# / 32#) * en ^ 3
'    V = 1.3125 * en * en - (55# / 32#) * en ^ 4
'    W = (151# / 96#) * en ^ 3
'    r = er * (1# - en) * (1# - en * en) * (1# + 2.25 * en * en + (225# / 64#) * en ^ 4)
'    'if not UTM, these must be changed:
'    'OMO=OR1+A*sin(2.0*OR1) + B*sin(4.0*OR1)+ C*sin(6.0 *OR1)
'    'SO=sf*R*OMO
'    'sf could be something else
'    sf = 0.9996
'    OMO = 0
'    so = 0
'    Latitude = 47#
'    Longitude = -117#
'End Sub







