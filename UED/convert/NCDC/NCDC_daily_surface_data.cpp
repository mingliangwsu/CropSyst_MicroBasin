
#include <UED/convert/convertor.h>

#include <ued/library/ued_pch.h>
#include <ued/library/std_codes.h>
#include <corn/math/compare.h>
#include <corn/string/strconv.h>
#include <corn/math/statistical/stats.h>
#include <corn/primitive.h>
//#include <ued/convert/ncdc/stations.h>
#include <ued/library/ued_fname.h>
#include <climgen/source/options.h>
#include <corn/data_source/vv_file.h>
#include <corn/datetime/date.h>


using_namespace_CORN;

#include "NCDC_element.h"
//#include "NCDC_UED_element_conv.h"
#include "NCDC_UED_flag_conv.h"
#include "NCDC_UED_units_conv.h"
//#include "UED_element_creation.h"

/*
This convertor requires the format to be
NCDC Space Delimited with data flags


                           APRIL 24, 2001

                          DAILY SURFACE DATA
                           (PRIMARILY U.S.)

                     National Climatic Data Center
                           151 Patton Ave.
                       Asheville, North Carolina


Field numbers are shown with column positions in parenthesis.

FIELD 1 (1-4): DATA ORIGIN

The original NCDC tapedeck of the dataset.  Referred to in some of the tables
below.
*** Important Note:  If tapedeck number is 3201 or 3202, this indicates the data
are preliminary, with less quality control applied than the final data
(indicated by 3200 or 3210).  The 3201/02 data are replaced online by the final
data as soon as final data are available. ***


FIELD 2 (6-11): COOPERATIVE STATION NUMBER

This 6-character alphanumeric station identifier is assigned by the
National Climatic Data Center.  The first two digits refer to a state
code (value range is 01-91; reference Table "A").  The next four
digits refer to the Cooperative Network Index number (value range
is 0001-9999).  Missing/not assigned = 999999.


FIELD 3 (13-17): WBAN STATION NUMBER

This 5-character alphanumeric station identifier is assigned by the
National Climatic Data Center.  It originally referred to Weather Bureau,
Army, and Navy (WBAN) stations which mailed weather observational forms to
NCDC.  These stations normally have more detailed data available than strictly
cooperative stations, so stations with WBAN numbers will usually have
additional data elements.


Optional Field (19 - 48):  STATION NAME

This 30-character alphanumberic field is displayed if the data selection is
for data with Station Name.  Spacing for all fields following are adjusted
31 characters (e.g., Division Number = 50-51).


FIELD 4 (19-20): DIVISION NUMBER

These two digits refer to the Cooperative Network Division Number (value range
is 01-10; 99 = missing Division Number; reference Table "B").


FIELD 5 (22-25): METEOROLOGICAL ELEMENT-TYPE
The type of meteorological elements stored in this data record.  Range of
values are listed below.  Note:  'b' in DATA-VALUE indicates ascii blank.



    ASMM
    Average Cloudiness Midnight to Midnight (begin September 1992 for
    ASOS sites).  This is the average of all available 30-second
    ceilometer data for the 24-hour period expressed in tenths of
    cloud cover at or below 12,000 feet.  The DATA-VALUES are defined
    in Reference Table "C".

    ASSS
    Average Cloudiness Sunrise to Sunset (begin September 1992 for
    ASOS sites).  This is the average of all available 30-second
    ceilometer data for the period from sunrise to sunset expressed
    in tenths of cloud cover at or below  12,000 feet.  The DATA-VALUES
    are defined in Reference Table "C".

    AWND
    Average Daily Wind Speed (begin 1984).  Units expressed in miles
    per hour to tenths.  From January 1984 through June 1987 the
    Element Unit is incorrectly listed as TK (Tenths of Knots), it
    should be MH (Miles per Hour).

    CLDG
    Cooling Degree Day (begin 1984).  Base 65 degrees Fahrenheit.

    DPNT
    Departure from Normal Temperature. DATA-VALUE = -00099 to b00099
    degrees Fahrenheit.

    DPTP
    Average Daily Dew-Point Temperature (begin 1984).  Units
    expressed in tenths of degrees Fahrenheit.

    DYSW
    The different types of weather occurring that day (reference Table
    "D" if FIELD 1 = 3200, Table "E" if FIELD 1 = 3210).

    DYVC
    Days with Weather in the Vicinity (begin July 1996). The present
    (or prevailing) weather occurring at the time of the observation
    in the vicinity of the station, between 5 and 10 statute miles of
    the point of observation.
        NOTE: This element is used beginning July 1996 and is coded in
        the same manner as the element DYSW.  See the description for
        DYSW for details. (Reference Table "E")

    EVAP
    Daily evaporation (not reported when temperature below freezing).
    Unit Measurement, Inches & Hundredths of Inches.

    F2MN
    Fastest 2-minute Wind Direction and Speed (begin September 1992
    for ASOS sites).  Direction is expressed in tens of degree from
    true north.  Speed is expressed in miles per hour.  When two or
    more equal speeds have occurred, the most recent speed and
    direction are entered.
    Example of DATA-VALUE field XXYYY for wind direction and speed:
    22048.  Wind is from 220 degrees at 48 miles per hour.

    F5SC
    Fastest 5-second Wind Direction and Speed (begin September 1992
    for ASOS sites).  Direction is expressed in tens of degrees from
    true north.  Speed is expressed in miles per hour.  When two or
    more equal speeds have occurred, the most recent speed and
    direction are entered.

    FMTM
    Time of Fastest Mile or Fastest 1-minute Wind (begin 1984), or
    Fastest 2-minute Wind (begin September 1992).  Units are
    expressed in hours and minutes.

    FRGB
    Base of Frozen Ground Layer.  The depth below the surface of the
    ground at which frozen ground is last struck.  Data available
    through 1964 only for designated stations.  DATA-VALUE = b00000
    to b00099 expressed in whole inches.

    FRGT
    Top of frozen ground layer.  The depth below the surface of the
    ground at which frozen ground is first struck.  Data available
    through 1964 only for designated stations.  DATA-VALUE = b00000
    to b00099 expressed in whole inches.

    FRTH
    Thickness of Frozen Ground Layer.  Base value minus top value.
    Data available through 1964 only for designated stations.
    DATA-VALUE = b00000 to b00099

    FSIN
    Highest Instantaneous Wind Direction and Speed.  This is the
    highest gust or peak reached by the pen of the gust recorder
    during the 24 hour period.  Direction is expressed in 16 Point
    WBAN Code (Reference Table "F1"). Speed generally expressed in
    miles per hour.  When two or more equal wind speeds occur the
    most recent is archived.

    FSMI
    Fastest Mile Wind Direction and Speed.  Recorded by stations
    having triple or multiple register type recording instruments.
    The speed of a mile of wind occurring in the shortest time is
    used.  This is determined by measuring the jogs on the chart made
    by the one mile contacts of the anemometer.  Speed expressed in
    miles per hour.  Example of value field XXYYY for wind direction
    and speed: 18045; 18 = wind direction from 169 degrees to 191
    degrees.  045 = wind speed 45 miles per hour. FSMI is not
    digitized for Air Weather Service stations.  (Reference Table "F2")

    FSMN
    Fastest Observed One-minute Wind Direction and Speed.  This is
    used at stations not equipped with recording instruments.  It is
    obtained by observation of an indicator for one minute and using
    an average value.  Direction is expressed in Tens of Degrees
    Code.  Speed expressed in miles per hour.  Example of value field
    XXYYY for wind direction and speed:  18045; 18 = wind direction
    from 169 degrees to 191 degrees.  045 = wind speed 45 miles per
    hour.  FSMN is not digitized for Air Weather Service Stations.
    (Reference table "F2")

    GAHT
    River Gauge Height - Below zero gauge readings.  DATA-VALUE =
    negative values of b00000 to b00999, expressed to the nearest
    tenth of a foot.

    HTDG
    Heating Degree Days (begin 1984; however, several stations
    reported this element as early as 1961).  Base 65 whole degrees
    Fahrenheit.

    MNPN
    Daily minimum temperature of water in an evaporation pan (effective
    September 1963). Unit Measurement, Whole Degrees Fahrenheit.
    (Reference Table "P").

    MNRH
    Minimum Relative Humidity (through 1955).  DATA-VALUE = b00000 to
    b00100, expressed in whole percent.  (AWS stations through
    January 1958, NWS, FAA, and Navy stations through December 1964.
    Most stations restarted in 1984; some stations reported this
    element as early as 1961).

    MNTP
    Average Temperature (begin 1984).  The value is the (Max Temp. +
    Min Temp.)/2, expressed in whole degrees Fahrenheit. (Reference Table
    "P").

    MXPN
    Daily maximum temperature of water in an evaporation pan (effective
    September 1963). Unit Measurement, Whole Degrees Fahrenheit.
    (Reference Table "P").

    MXRH
    Maximum Relative Humidity.  DATA-VALUE = b00000 to b00100,
    expressed in whole percent.  (AWS stations through June 1958,
    NWS, FAA, and Navy stations through December 1964. Most stations
    restarted in 1986.)

    PGTM
    Peak Gust Time or Maximum 5-second Wind Speed Time.  Value =
    b00000 to b02359, expressed in hours and minutes. Example: 2359 =
    23 hours and 59 minutes.

    PKGS
    Peak Gust Direction and Speed.  If two or more equal peak gust
    speeds occurred on the same day, the first was digitized for the
    period July, 1968 through December 1972.  Beginning in January
    1973, the last was digitized.  The direction is generally
    expressed in 16 Point WBAN Code, with the following exceptions:

    (1)  Air Force stations used 36 Point code from January, 1964
    through February, 1967, 16 Point WBAN Code from March, 1967
    through June, 1968, and 36 Point code again from July, 1968
    through December, 1970.  Air Force data was generally
    discontinued by December, 1970.

    (2)  Navy stations used 16 Point WBAN Code from the beginning of
    record through January, 1971, and 36 Point Code from February,
    1971 through the present.

    Wind speeds are generally expressed in miles per hour through
    December,  1954, and in knots from January, 1955 to the present.
    A  consistent exception is Navy stations, which used knots for
    the entire period of record.  Example of value field XXYYY after
    1954 for wind direction and speed:  44032; 44 = Wind direction
    from the SE.  032 = Wind speed 032 knots.

    Beginning July 1996, wind direction is expressed in 36 Point
    WBAN Code (Reference Table "F2").

    PRCP
    Daily precipitation.  Precipitation reading for 24 hours ending at
    time of observation.  Trace is less than 0.005 inch.  Unit
    Measurement, Inches to Hundredths.

    PRES
    Average Daily Station Pressure (begin 1984).  Based on eight
    3-hourly observations per day.  Units expressed in thousandths of
    inches of Mercury.

    PSUN
    Daily Percent of Possible Sunshine (begin January 1965).  Data
    Value = b00000 to b00100, expressed in percent.

    RDIR
    Resultant Wind Direction (begin 1984).  DATA-VALUE expressed to
    the nearest whole degree code.  From January 1984 through late
    1994 the Meteorological Element Measurement units code is
    incorrectly recorded as DT (wind direction in tens of degrees).
    It should be DW (wind direction in whole degrees).

    RWND
    Resultant Wind Speed (begin 1984).  DATA-VALUE is expressed in
    miles per hour to tenths.  From January 1984 through June 1987,
    the Meteorological Element Measurement Units Code is incorrectly
    recorded as TK (tenths of knots) and incorrectly recored as MH
    (miles per hour) from July 1987 through late 1994. It should be
    TL tenths of miles per hour.

    SAMM
    Average Cloudiness Midnight to Midnight - (begin September 1992
    for ASOS sites).  This is the average of all available 30-second
    ceilometer data for the 24-hour period expressed in oktas of
    cloud cover at or below 12,000 feet.  The DATA-VALUES are defined
    in Reference Table "C1".

    SASS
    Average Cloudiness Sunrise to Sunset (begin September 1992 for
    ASOS sites). This is the average of all available 30-second
    ceilometer data for the period from sunrise to sunset expressed
    in oktas of cloud cover at or below  12,000 feet.  The DATA-VALUES
    are defined in Reference Table "C1".

    SCMM
    Average Sky Cover Midnight to Midnight (begin January 1965).
    Element not recorded at stations where personnel were not on duty
    24 hours a day.  See Elements ASMM and STMM for ASOS sites.
    DATA-VALUES are expressed in tenths and are defined in Reference
    Table "C".

    SCSS
    Average Sky Cover Sunrise to Sunset - (begin January 1965).
    DATA-VALUES are expressed in tenths and are defined in Reference
    Table "C". See Elements ASSS and STSS for ASOS sites.

    SGMM
    Average Cloudiness Midnight to Midnight (begin September 1992;
    end June 1996; derived from GOES satellite data).  The areal
    coverage is approximately 50km by 50km centered on the ASOS site.
    DATA-VALUE is the average of all satellite scans of the site
    during the 24-hour period, expressed in oktas of cloud cover
    occurring above 12,000 feet.  The DATA-VALUES are defined in
    Reference Table "C1".

    SGSS
    Average Cloudiness Sunrise to Sunset (begin September 1992; end
    June 1996; derived from GOES satellite data).  The areal coverage
    is approximately 50km by 50km centered on the ASOS site.  DATA-VALUE
    is the average of all satellite scans of the site during
    period from sunrise to sunset, expressed in oktas of cloud cover
    occurring above 12,000 feet.  The DATA-VALUES are defined in
    Reference Table "C1".

    SLVP
    Average Daily Sea Level Pressure (begin 1984).  DATA-VALUE
    expressed in tenths of millibars.

    SMMM
    Average Sky Cover Midnight to Midnight (begin January 1965).
    Element not recorded at stations where personnel were not on duty
    24 hours a day.  See Elements SAMM and SGMM for ASOS sites.
    DATA-VALUES are expressed in oktas and are defined in Reference
    Table "C1".

    SMSS
    Average Sky Cover Sunrise to Sunset - (begin January 1965)
    DATA-VALUES are expressed in oktas and are defined in Reference
    Table "C1".  See Elements SASS and SGSS for ASOS sites.

    SNOW
    Daily Snowfall (Snowfall includes sleet).  Amount is for 24-hour
    period ending at observation time.  Hail was included with snowfall
    from July 1948 through December 1955.  Hail occurring alone was not
    included with either snowfall or snow depth before and after that
    period.  Trace is less than 0.05 inch.  Unit Measurement, Inches to
    Tenths.
    Important Note:  For July 1996 to present, this element is not valid
    and should not be used if FIELD 1 = 3210.  NCDC will attempt to correct
    this problem as soon as resources allow.

    SNWD
    Snow depth at observation time.  (Snow depth is depth of snow on
    the ground at time of observation.  Trace is depth less than 0.5
    inch.) Unit Measurement, Whole Inches.  See Table "H".
    Important Note:  For July 1996 to present, this element is not valid
    and should not be used if FIELD 1 = 3210.  NCDC will attempt to correct
    this problem as soon as resources allow.

    SNyz
    Daily minimum soil temperature (see note below).  Unit Measurement,
    whole degrees Fahrenheit. (Reference Table "P").

    SOyz
    Soil temperature at observation time (see note below).  Unit
    Measurement, whole degrees Fahrenheit. (Reference Table "P").

    STMM
    Average Cloudiness Midnight to Midnight (begin September 1992;
    end June 1996; derived from GOES satellite data).  The areal
    coverage is  approximately 50km by 50km centered on the ASOS
    site.  DATA-VALUE is the average of all satellite scans of the
    site during the 24-hour period, expressed in tenths of cloud
    cover occurring above 12,000 feet.

    STSS
    Average Cloudiness Sunrise to Sunset (begin September 1992; end
    June 1996; derived from GOES satellite data).  The areal coverage
    is approximately 50km by 50km centered on the ASOS site.  DATA-VALUE
    is the average of all satellite scans of the site during
    period from sunrise to sunset, expressed in tenths of cloud cover
    occurring above 12,000 feet.

    SXyz
    Daily maximum soil temperature (see note below).  Unit Measurement,
    whole degrees Fahrenheit.  (Reference Table "P").

      Note:    Positions "y" and "z" of the soil temperatures are
      encoded using reference Table "I", e.g., SN12 indicates that
      the daily minimum soil temperatures that follow are measured
      in an area covered with grass and at a depth of four inches
      or 10 centimeters.

    THIC
    Thickness of Ice on Water.  Measured each Monday at noon LST,
    or more frequently if ice conditions are changing rapidly.  Data
    available through December 1964 only for designated stations.
    DATA-VALUE = b00000 to b00999, expressed in tenths of inches.

    TMAX
    Daily maximum temperature.  (Maximum temperature reading for 24
    hours ending at time of observation.) Unit Measurement, Whole
    Degrees Fahrenheit.
    Important Note:  For 1990 - 1994, this element is often shown as
    missing if FIELD 1 = 3210 and the max temperature was reported as
    -10 F or lower.  NCDC will attempt to correct this problem as soon
    as resources allow.

    TMIN
    Daily minimum temperature.  (Minimum temperature reading for 24
    hours ending at time of observation.) Unit Measurement, Whole
    Degrees Fahrenheit.
    Important Note:  For 1990 - 1994, this element is often shown as
    missing if FIELD 1 = 3210 and the min temperature was reported as
    -10 F or lower.  NCDC will attempt to correct this problem as soon
    as resources allow.

    TMPW
    Average Daily Wet-Bulb Temperature (begin 1984).  DATA-VALUE =
    -00199 to b00199, expressed in whole degrees Fahrenheit.
    (Reference Table "P").

    TOBS
    Temperature at observation time. Unit Measurement, Whole Degrees
    Fahrenheit.

    TSUN
    Daily Total Sunshine.  DATA-VALUE = b00000 to b01440, expressed
    in minutes.  (Reference Table "J")

    WDMV
    24-hour wind movement.  Unit Measurement, Whole Miles.

    WTEQ
    Water equivalent of snow depth.  (For principal stations only.
    Effective October 1963 for snow depth equal or greater than 2
    inches). Unit Measurement, Inches to Tenths.



FIELD 6 (27-28): METEOROLOGICAL ELEMENT MEASUREMENT UNITS CODE

The units and decimal position (precision) of the data value for this record
(reference Table "K"). See "Known Uncorrected Problems" for additional
details.


FIELD 7 (30-35): YEAR-MONTH

This is the year and month of the data record.  Range of values is
1850-current year and 01-12.  Example: 199512 = December 1995.


FIELD 8 (37-40): DAY OF MONTH and HOUR OF OBSERVATION

DAY: The day of the month on which the data element was observed.
Range of values is 01-31 LST.  Will always begin with day 01 and end with day
31.

HOUR OF OBSERVATION: Contains the hour of the daily observation.  Hour of
observation is reported using the 24-hour clock with values ranging from 00-23
LST, except in the cases of soil temperatures element-type (where the hour
is 99 to indicate missing) and "days with weather" (where the hour is
24).  Through June 1967 observations were designated as "AM" or "PM";
these values were set to 06 or 18 respectively during the conversion to
TD-3200.  From July 1967 through 1981, all observations were set to
hour 18 (because the majority are p.m. observations).  Beginning January
1982, the actual hour of the observation is indicated.


FIELD 9 (42-47): SIGN AND VALUE OF METEOROLOGICAL ELEMENT

SIGN: The algebraic sign of the meteorological data value is given as either
a blank or a minus sign (-).  Blank indicates a positive value and a
minus sign represents a negative value.

VALUE OF METEOROLOGICAL ELEMENT

The actual data value is given as a five-digit integer.  One major
exception does exist however, for the DYSW (days with weather code)
element-type values as explained in Table "D".  A very small number
of data values are known to have non-numeric entries.

When a data value is missing, the sign of the data value is set to "-", the
data value is set to "99999", flag position 1 is set to "M" and flag position
2 is blank.

Prior to September 1991, when no daily precipitation reading was taken
but the amount from that day (if any) is included in a subsequent value,
the data value of precipitation is set equal to "00000" and flagged with
an "S" in flag position 1.  In turn, the successive accumulated amount
will be flagged with an "A" in flag position 1.  Since September 1991,
it has been a practice at NCDC to set the precipitation value to
"99999" in this situation; the flagging procedure has not changed.


FIELD 10 (49-49): FLAG1

The Data Measurement FLAG (reference Table "N").  This field will not be
present if the user chooses a delimited format without data flags.


FIELD 11 (51-51): FLAG2

The Data Quality FLAG (reference Table "O").  This field will not be
present if the user chooses a delimited format without data flags.


FIELDS 8-11 are then repeated for each day of the month, beginning with 01 in
the DAY field, and ending with 31 in the DAY field.  So, the data for DAY 02
will occupy columns 53-67, DAY 03 = 69-83, etc.



                                TABLES

                        *******TABLE "A"*******

       State-Code Table

01 Alabama                  28 New Jersey
02 Arizona                  29 New Mexico
03 Arkansas                 30 New York
04 California               31 North Carolina
05 Colorado                 32 North Dakota
06 Connecticut              33 Ohio
07 Delaware                 34 Oklahoma
08 Florida                  35 Oregon
09 Georgia                  36 Pennsylvania
10 Idaho                    37 Rhode Island
11 Illinois                 38 South Carolina
12 Indiana                  39 South Dakota
13 Iowa                     40 Tennessee
14 Kansas                   41 Texas
15 Kentucky                 42 Utah
16 Louisiana                43 Vermont
17 Maine                    44 Virginia
18 Maryland                 45 Washington
19 Massachusetts            46 West Virginia
20 Michigan                 47 Wisconsin
21 Minnesota                48 Wyoming
22 Mississippi              49 Not Used
23 Missouri                 50 Alaska
24 Montana                  51 Hawaii
25 Nebraska                 66 Puerto Rico
26 Nevada                   67 Virgin Islands
27 New Hampshire            91 Pacific Islands


                          *******TABLE "B"*******

                   Cooperative Network Division Table

NOTE:  The division number for a station
may change over time.

           HAWAII (STATE 51)*

ISLAND NAME                   DIVISION

   Kauai                           01
   Oahu                            02
   Molokai                         03
   Lanai                           04
   Maui                            05
   Hawaii                          06

*NOTE:  Hawaii (State 51) division numbers
were changed during the initial conversion
of this file.  Divisions within islands no
longer exist.  Division numbers now
represent each island.

          PACIFIC ISLANDS (STATE 91)

Division

02 - East of 180th Meridian - Phoenix
     Islands, Line Islands, and American
     Samoa

03 - Western Pacific Islands, North of
     12N

04 - Caroline and Marshall Islands

 
                   ******** TABLE "C" ********
 
                SKY COVER in TENTHS for ELEMENTS:
                  ASMM/ASSS/SCMM/SCSS/STMM/STSS
 
      DATA-VALUE
      CODE           SKY COVER
      00000     =  Clear or less than .1 coverage
      00001     =  .1 Coverage
      00002     =  .2 Coverage
      00003     =  .3 Coverage
      00004     =  .4 Coverage
      00005     =  .5 Coverage
      00006     =  .6 Coverage
      00007     =  .7 Coverage
      00008     =  .8 Coverage
      00009     =  .9 Coverage
      00010     = 1.0 Coverage - Overcast


                   ******** TABLE "C1" ********

                 SKY COVER in OKTAS for ELEMENTS:
                  SAMM/SASS/SGMM/SGSS/SMMM/SMSS
 
      DATA-VALUE
      CODE           SKY COVER
      00000     =  Clear or less than .1 coverage
      00001     =  .1 Coverage
      00002     =  .3 Coverage
      00003     =  .4 Coverage
      00004     =  .5 Coverage
      00005     =  .6 Coverage
      00006     =  .8 Coverage
      00007     =  .9 Coverage
      00008     = 1.0 Coverage - Overcast


                          *******TABLE "D"*******

                 DYSW - Daily Occurrence of Weather Table

00 - Day of no occurrence
01 - Day with smoke or haze (POR through
     1963 and 1982 to Present)
02 - Day with fog (POR through 1963 and
     1982 to Present)
04 - Day with drizzle (POR through 1963
     and 1982 to Present)
05 - Day with ice pellets (sleet)
06 - Day with glaze
07 - Day with thunder
08 - Day with hail
09 - Day with dust or sand storm (POR
     through 1963 and 1982 to Present)
10 - Day with blowing snow
11 - Day with high wind (POR through 1963
     and 1982 to Present)
12 - Day with tornado (POR through 1963
     and 1982 to Present)
13 - Day with rain (1982 to Present)
14 - Day with snow (1982 to Present)


From 1980 forward, these two-character DYSW
element-type codes are stored into the
rightmost four characters of the data value
portion of the meteorological element.
Within the four characters used, the
weather codes are entered left justified.
Thus, if one type of weather occurs during
a day, the data values would appear as
OXXOO, where XX is the appropriate weather
code.  If two types of weather occur, the
data value will contain OXXYY, where XX is
value 1 and YY is value 2.  If more than
two types of weather occur on the same day,
they will be stored into additional "DLY"
records of the element-type code "DYSW" as
needed.
 
NOTE:  Prior to 1980, each weather code for
DYSW is written as a unique DATA PORTION.
Only the left position (XX) of the DYSW
code is used (e.g., appears as OXXOO).


                   ******** TABLE "E" ********
 
                            DYSW/DYVC

00  No occurrence
01  Day with haze (smoke also included through August 1992; see
    code 30 in this table)
02  Day with fog (ice fog included through 1983; see code 17 in
    this table)
03  Day with heavy fog (heavy ice fog included through 1964)
04  Day with drizzle (begin 1984)
05  Day with ice pellets (sleet and small hail; small hail
    included through June 1996; see code 31 in this table)
06  Day with glaze
07  Day with thunder
08  Day with hail (1/4 inch or larger in diameter beginning July
    1996)
09  Day with volcanic ash (begin September 1992; dust or
    sandstorm with visibility < 5/8 mile was reported as code 09
    through August 1992; see codes 27 and 29 in this table)
10  Day with blowing snow (includes drifting snow beginning July
    1996)
11  Day with high wind (squall; speeds increasing to at least
    16kts/18mph and sustained at 22kts/25mph or more for at least
    one minute; begin July 1996)
12  Day with tornado (funnel cloud, waterspout included through
    Aug 1992; see codes 20 and 21 in this table)
13  Day with snow (snow pellets, snow grains, and ice crystals
    included through Aug 1992; see codes 22, 23, 24 in this
    table)
14  Day with rain (drizzle, freezing drizzle, and freezing rain
    included through 1983)
15  Day with freezing rain (begin 1984)
16  Day with freezing drizzle (begin 1984)
17  Day with ice fog (begin 1984; includes freezing fog beginning
    July 1996)
18  Day with blowing spray (begin 1984; includes spray beginning
    July 1996))
19  Day with unknown source of precipitation (begin 1991 with
    automated stations)
20  Day with funnel cloud (begin September 1992)
21  Day with waterspout (begin September 1992; includes tornado
    beginning July 1996)
22  Day with snow pellets (begin September 1992 through June
    1996; see code 31 in this table)
23  Day with snow grains (begin September 1992)
24  Day with ice crystals (begin September 1992)
25  Day with ground fog (begin September 1992)
26  Day with dust (begin September 1992)
27  Day with blowing dust (begin September 1992; includes
    duststorm when visibility is reduced to less than 5/8 miles
    beginning July 1996)
28  Day with blowing obstruction (begin September 1992 through
    June 1996)
29  Day with blowing sand (begin September 1992); also includes
    sand as well as sandstorm when visibility is reduced to less
    than 5/8 mile (begin July 1996)
30  Day with smoke (begin September 1992)
31  Day with small hail and/or snow pellets (begin July 1996;
    diameter less than 1/4 inch)
32  Day with well developed dust/sand whirls (begin July 1996)
33  Day with mist (begin July 1996)
34  Day with rain or snow shower; used in reference to weather in
    the vicinity only (begin July 1996)


                   ******** TABLE "F1" ********

                               FSIN

 WIND DIRECTION CODE
 (16 Point WBAN Code)
 
 12 = NNE   66 = SW
 22 = NE    76 = WSW
 32 = ENE   77 = W
 33 = E     78 = WNW
 34 = ESE   88 = NW
 44 = SE    18 = NNW
 54 = SSE   11 = N
 55 = S     00 = Calm
 56 = SSW      = Unknown
 
Example of DATA-VALUE field XXYYY for wind direction and speeds:
12037 Wind is from the NNE at 37 miles per hour.


                   ******** TABLE "F2"********
 
       FSMI & FSMN

 WIND DIRECTION CODES
 
 00 =  Calm
 01 =  010
 02 =  020
 "      "
 "    through     "
 36 =  360
 99 =  Unknown
 

                   ******** TABLE "G" ********
                               PKGS
 
 WIND DIRECTION CODE
 (36 Point WBAN Code)

 03 = NNE      21 = SSW
 05 = NE       24 = SW
 07 = ENE      25 = WSW
 09 = E        27 = W
 12 = ESE      30 = WNW
 14 = SE       32 = NW
 16 = SSE      34 = NNW
 18 = S        36 = N


                  ******** TABLE "H" ********

                               SNWD
 
 DEPTH of SNOW OBSERVED AT:
     00:30  GMT prior to July 1952
     12:30  GMT 1 July 1952 to 30 May 1957
     12:00  GMT 1 June 1957 to present
 
DATA-VALUE = b00000 to b09999 in whole inches.  Trace of snow depth
is less than 0.5 inches.  Some Alaska and part-time stations take
snow depth measurements at different hours.


                         *******TABLE "I"*******

                         Soil Temperature Table

          (y = Code for soil cover)
          (z = Code for soil depth)

*******************************************
|Code| Cover | |Code   |  Depth   | Depth |
|    |       | |       | (inches) |  (cm) |

|************| |*******|**********|*******|
|y=1 | Grass | |       |          |       |
|  2 | Fallow| |z = 1  |     2    |    5  |
|  3 | Bare  | |       |          |       |
|    | ground| |    2  |     4    |   10  |
|  4 | Brome | |       |          |       |
|    | grass | |    3  |     8    |   20  |
|  5 | Sod   | |       |          |       |
|  6 | Straw | |       |          |       |
|    | mulc  | |    4  |    20    |   50  |
|  7 | Grass | |       |          |       |
|    | muck  | |    5  |    40    |  100  |
|  8 | Bare  | |       |          |       |
|    | muck  | |    0  | Unknown  |Unknown|
|  0 |Unknown| |       |          |       |
*******************************************

NOTE:  Soil records are kept since 1982.
Some stations may report soil temperatures
at observation time twice a day.  Separate
records will occur for both observation
times.


                  ********  TABLE "J" ********

                               TSUN

 Conversion of minutes to tenths of hours is:
    MIN TENTHS
    1-2   0.0   33-38  0.6
    3-8   0.1   39-44  0.7
    9-14  0.2   45-50  0.8
   15-20  0.3   51-56  0.9
   21-26  0.4   57-60  1.0
   27-32  0.5    A     ASOS


                   ******** TABLE "K" ********

          METEOROLOGICAL ELEMENT MEASUREMENT UNITS CODE

The units and decimal position of the data value for this record.
Range of values is listed below.
*/

#include "NCDC_element.h"

/*
Note:  All single digit Element-Units are left justified and
blank filled.


                   ******** TABLE "N" ********

                     Data Measurement Flag 1

A -   Accumulated amount since last
      measurement.
B -   Accumulated amount includes
      estimated values (since
      last measurement).
E -   Estimated (see Table "O" for
      estimating method).
J -   Value has been manually
      validated.
M -   Flag1 is "M" if the data value
      is missing. In this case, the
      sign of the meteorological value
      is assigned "-" and the value of
      the meteorological element is
      assigned "99999".
S -   Included in a subsequent value.
      (data value = "00000" OR
      "99999").
T -   Trace (data value = 00000 for a
      trace).
( -   Expert system edited value,
      not validated.
) -   Expert system approved
      edited value.
Blank - Flag not needed.

Flag 1 values of "S" and "A" usually occur
in pairs (ie. a daily value will have Flag
1 assigned as "S" and the next daily value
will have Flag 1 assigned as "A").  For
some daily values these flags do not occur
in pairs.

Other values occasionally appear in Data
Measurement Flag 1 for which documentation
is not currently available, e.g., "C" and
"s".


                   ******** TABLE "O" ********

                       Data Quality Flag 2

Some data quality flags are not supported in UED
these flags have to do with typing corrections
(UED presumes that at least the data is free of typographical errors).

I am presuming that the NCDC value is corrected.


*/
struct Quality_conversion
{
   char                    NCDC_quality;  // Flag 2
   CORN::Quality_code  UED_quality;
}  quality_conversion[] =
{{'0',UED_measured         }  //  - Valid data element.
,{'1',UED_measured         }  //  - Valid data element (from "unknown" source, pre-1982).
,{'2',UED_not_valid        }  //  - Invalid data element (subsequent value replaces original value).   RLN not sure what this means
,{'3',UED_not_valid        }  //  - Invalid data element (no replacement value follows).               RLN not sure what this means
,{'4',UED_unknown_quality  }  //  - Validity unknown (not checked).
,{'5',UED_estimated        }  //  - Original non-numeric data value has been replaced by its deciphered numeric value.  RLN not sure what this means
,{'A',UED_forecasted       }  //  - Substituted TOBS for TMAX or TMIN
,{'B',UED_forecasted       }  //  - Time shifted value                          RLN not sure what this means
,{'C',UED_estimated        }  //  - Precipitation estimated from snowfall
,{'D',UED_measured         }  //  - Transposed digits
,{'E',UED_measured         }  //  - Changed units
,{'F',UED_estimated        }  //  - Adjusted TMAX or TMIN by a multiple of + or -10 degrees
,{'G',UED_estimated        }  //  - Changed algebraic sign
,{'H',UED_estimated        }  //  - Moved decimal point
,{'I',UED_estimated        }  //  - Rescaling other than F, G, or H
,{'J',UED_estimated        }  //  - Subjectively derived value
,{'K',UED_forecasted        }  //  - Extracted from an accumulated value
,{'L',UED_estimated        }  //  - Switched TMAX and/or TMIN
,{'M',UED_estimated        }  //  - Switched TOBS with TMAX or TMIN
,{'N',UED_estimated        }  //  - Substitution of "3 nearest station mean"
,{'O',UED_estimated        }  //  - Switched snow and precipitation data value
,{'P',UED_measured         }  //  - Added snowfall to snow depth
,{'Q',UED_estimated        }  //  - Switched snowfall and snow depth
,{'R',CORN::missing_quality          }  //  - Precipitation not reported; estimated as "O"
,{'S',UED_estimated        }  // **- Manually edited value
,{'T',UED_unknown_quality  }  //  - Failed internal consistency check
,{'U',UED_unknown_quality  }  //  - Failed areal consistency check (beginning Oct. 1992)
,{0,0}
};
// ** - Manually edited value could be derived by any of the procedures noted by Flags A-R.
/*

                          ******TABLE "P"******

                       Units of Measurement Table

Range of values where b = Blank:

bF   Whole degrees Fahrenheit (right
     justified
HI   Hundredths of inches
bI   Whole inches (right justified)
bM   Whole miles (right justified)
NA   No units applicable (nondimensional)
TI   Tenths of inches



KNOWN UNCORRECTED PROBLEMS AND DATA CAVEATS:

For maximum and minimum temperature, from 1990 - 1994, the value
is often shown as missing if FIELD 1 = 3210 and the temperature was
reported as -10 F or lower.  NCDC will attempt to correct this problem
as soon as resources allow.

For snowfall and snow depth data:  For July 1996 to present, this element
is not valid and should not be used if FIELD 1 = 3210.  NCDC will
attempt to correct this problem as soon as resources allow.

For October 1990, there are numerous duplicate data records in
the daily data.  In using the data, choose the data record with
the most daily values for the month.

During the period 1984-86 there are numerous entries for element
PRCP of "NA" for the Meteorological Element Units Code.  These
should be coded as "HI".

In 1988 for states 31-91 (North Carolina to Pacific Islands), the
algebraic sign of positive meteorological data values may be coded
as "+" symbols instead of as blanks.

The historical data were converted from existing digital files and
placed in the element structure format in 1983.  At that time these
data were only processed through a gross value check.  In January
1984, NCDC instituted greatly enhanced computer algorithms for
automated validation of digital archives.  The revised edit system
performs internal consistency checks, climatological limits checks
and serial checks.  It is the goal of the NCDC that, as resources
permit, these historical files will be brought up to the same level
of quality as those from 1984 onward.

Quality control "flags" are appended to each element to show how
they fared during the edit procedures and to indicate what, if any,
action was taken.
 
The typical progression of temperature instruments was from
liquid-in-glass thermometers, to (1960 series) Hygrothermometers,
to (1980 series) Hygrothermometers.  Scientists are currently
investigating the effect these instrument changes (especially
the 1980 series) may have on long term temperature records.

Users should also be aware of a potential for a "lag" in the change of
observation times used in the logical record and what is actually in practice
at the site (that is, several months may be archived digitally under an "old"
observation time before NCDC received notification).

Prior to the 1970's, accumulated amounts of precipitation were not always
flagged with the "A".  Instead the convention was to treat the value following
a series of data values flagged with "S" as an accumulated value.

A very small number of data values are known to have non-numeric entries.

Maximum and Minimum Temperature--
 
National Weather Service, and Federal Aviation Stations:  These
values are determined from stations equipped with maximum and
minimum thermometers or recording instruments.  For some sites,
when instruments were inoperative, values were selected from
hourly observations.

Maximum and Minimum Relative Humidity--

For the period July 1996 through December 1998, the twenty four (24) hour
maximum and minimum relative humilities reported as 00000 and 00100
respectively, are incorrect.  These values were incorrectly generated for
stations that did not report relative humidity.

U.S. Air Force Stations:  From May 15, 1955, for stations taking 24
record observations per day, the maximum and minimun temperatures
are determined from hourly observations.  The observations at the
beginning and ending of day are considered.  The values are
reported as missing when more than 3 of the hourly observations
pertinent to the determination of maximum and minimum temperatures
for each 24-hour period are missing or erroneous.

U.S. Navy Stations:  When maximum and minimum thermometer readings
are not available, the data at most stations are reported as
missing.  Some Navy stations determine the maximum and minimum
temperatures from hourly observations when readings from maximum
and minimum thermometers are not available.

Hail and Snowfall Amounts--

Although the inclusion of hail amounts with snowfall amounts was
discontinued after December 31, 1955, some stations may have hail
amounts included with snowfall after this date, as late as 1963 at
a few stations.  This occurred because on the original manuscript
form the same column was used for the entry of snow, sleet and hail,
and the entry was not indicated as hail.  For NWS sites, hail was
again included in snowfall amounts beginning in 1989.

Confidence Factors--

Days with Weather Code:  The "days with weather" element-type (DYSW) cannot be
used with any measure of confidence when FIELD 1 = 3200.  Principal
climatological stations operating 24 hours a day are expected to be the most
reliable source of "days with weather".  Reporting of this element by
cooperative observers is not a requirement and criteria for reporting is not
definitive.  Most cooperative stations do not record this information.

Space delimited format

DSET COOPID WBNID CD ELEM UN YEARMO HOUR  DAY01 F F HOUR  DAY02 F F HOUR  DAY03 F F HOUR  DAY04 F F HOUR  DAY05 F F HOUR  DAY06 F F HOUR  DAY07 F F HOUR  DAY08 F F HOUR  DAY09 F F HOUR  DAY10 F F HOUR  DAY11 F F HOUR  DAY12 F F HOUR  DAY13 F F HOUR  DAY14 F F HOUR  DAY15 F F HOUR  DAY16 F F HOUR  DAY17 F F HOUR  DAY18 F F HOUR  DAY19 F F HOUR  DAY20 F F HOUR  DAY21 F F HOUR  DAY22 F F HOUR  DAY23 F F HOUR  DAY24 F F HOUR  DAY25 F F HOUR  DAY26 F F HOUR  DAY27 F F HOUR  DAY28 F F HOUR  DAY29 F F HOUR  DAY30 F F HOUR  DAY31 F F
---- ------ ----- -- ---- -- ------ ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - - ---- ------ - -
3200 316805 99999 01 PRCP HI 199901 0107  00000   0 0207  00000   0 0307  00272   0 0407  00000   0 0507  00000   0 0607  00000   0 0707  00000 T 0 0807  00009   0 0907  00026   0 1007  00001   0 1107  00000   0 1207  00000   0 1307  00000   0 1407  00050   0 1507  00085   0 1607  00000   0 1707  00000   0 1807  00090   0 1907  00009   0 2007  00000   0 2107  00000   0 2207  00001   0 2307  00015   0 2407  00224   0 2507  00000   0 2607  00000   0 2707  00000   0 2807  00000   0 2907  00000   0 3007  00033   0 3107  00033   0
3200 316805 99999 01 PRCP HI 199902 0107  00061   0 0207  00103   0 0307  00000   0 0407  00002   0 0507  00000   0 0607  00000   0 0707  00000   0 0807  00002   0 0907  00000   0 1007  00068   0 1107  00003   0 1207  00003   0 1307  00001   0 1407  00000   0 1507  00000   0 1607  00000   0 1707  00001   0 1807  00135   0 1907  00003   0 2007  00066   0 2107  00000   0 2207  00000   0 2307  00000   0 2407  00005   0 2507  00000   0 2607  00000   0 2707  00000   0 2807  00062   0 2999 -99999 M   3099 -99999 M   3199 -99999 M
3200 316805 99999 01 PRCP HI 199903 0107  00002   0 0207  00000   R 0307  00017   0 0407  00027   0 0507  00000   0 0607  00010   0 0707  00000   0 0807  00000   0 0907  00030   0 1007  00025   0 1107  00000   0 1207  00000   0 1307  00000   0 1407  00045   0 1507  00070   0 1607  00000   R 1707  00000   0 1807  00000   0 1907  00000   0 2007  00000   0 2107  00027   0 2207  00026   0 2307  00000   0 2407  00000   0 2507  00009   0 2607  00006   0 2707  00078   0 2807  00000   0 2907  00005   0 3007  00008   0 3107  00000   0
3200 316805 99999 01 PRCP HI 199904 0107  00260   0 0207  00001   0 0307  00000   0 0407  00000   0 0507  00000   0 0607  00001   0 0707  00003   0 0807  00000   0 0907  00005   0 1007  00000   0 1107  00000   0 1207  00000   0 1307  00000   0 1407  00000   0 1507  00010   0 1607  00051   0 1707  00000   0 1807  00000   0 1907  00000   0 2007  00000   0 2107  00000   0 2207  00000   0 2307  00000   0 2407  00000   0 2507  00000   0 2607  00009   0 2707  00035   0 2807  00013   0 2907  00086   0 3007  00000   R 3199 -99999 M
3200 316805 99999 01 PRCP HI 199905 0107  00047   0 0207  00000   0 0307  00000   0 0407  00000   0 0507  00005   0 0607  00115   0 0707  00049   0 0807  00081   0 0907  00000   0 1007  00000   0 1107  00000   0 1207  00000   0 1307  00001   0 1407  00010   0 1507  00001   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00010   0 2007  00000   0 2107  00000   0 2207  00000   0 2307  00000   0 2407  00000   0 2507  00000   0 2607  00000   0 2707  00002   0 2807  00000   0 2907  00000   0 3007  00000   0 3107  00000   0
3200 316805 99999 01 PRCP HI 199906 0107  00000   0 0207  00000   0 0307  00030   0 0407  00042   0 0507  00000   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00000   0 1107  00000   0 1207  00000   0 1307  00000   0 1407  00000   0 1507  00000 T 0 1607  00097   0 1707  00133   0 1807  00000   0 1907  00000   0 2007  00000   0 2107  00000   0 2207  00000   0 2307  00002   0 2407  00002   0 2507  00240   0 2607  00016   0 2707  00035   0 2807  00014   0 2907  00014   0 3007  00008   0 3199 -99999 M
3200 316805 99999 01 PRCP HI 199907 0107  00000   0 0207  00000   0 0307  00000   0 0407  00000   0 0507  00000   0 0607  00000   R 0707  00000   0 0807  00007   0 0907  00000   0 1007  00000   0 1107  00058   0 1207  00157   0 1307  00052   0 1407  00000   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00007   0 2007  00000   0 2107  00021   0 2207  00000   0 2307  00000   0 2407  00000   0 2507  00010   0 2607  00000   0 2707  00000   0 2807  00005   0 2907  00000   0 3007  00000   0 3107  00000   0
3200 316805 99999 01 PRCP HI 199908 0107  00000   0 0207  00045   0 0307  00000   0 0407  00000   0 0507  00000   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00005   0 1007  00000   0 1107  00000   0 1207  00000   0 1307  00000   0 1407  00006   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00000   0 2007  00000   0 2107  00001   0 2207  00000   0 2307  00000   0 2407  00158   0 2507  00062   0 2607  00001   0 2707  00000   0 2807  00000   0 2907  00000   0 3007  00000   0 3107  00000   0
3200 316805 99999 01 PRCP HI 199909 0107  00000   0 0207  00000   0 0307  00000   0 0407  00000   0 0507  00000   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00000   0 1107  00000   0 1207  00000   0 1307  00000   0 1407  00000   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00000   0 2007  00000   0 2107  00000   0 2207  00037   0 2307  00000   0 2407  00000   0 2507  00000   0 2607  00000   0 2707  00006   0 2807  00138   0 2907  00058   0 3007  00010   0 3199 -99999 M
3200 316805 99999 01 PRCP HI 199910 0107  00000   0 0207  00000   0 0307  00000   0 0407  00014   0 0507  00156   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00110   0 1107  00130   0 1207  00000   0 1307  00014   0 1407  00019   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00000   0 2007  00030   0 2107  00092   0 2207  00000   0 2307  00000   0 2407  00000   0 2507  00000   0 2607  00000   0 2707  00000   0 2807  00000   0 2907  00000   0 3007  00000   0 3107  00001   0
3200 316805 99999 01 PRCP HI 199911 0107  00001   0 0207  00163   0 0307  00005   0 0407  00000   0 0507  00000   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00000   0 1107  00000   0 1207  00001   0 1307  00000   0 1407  00000   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00000   0 2007  00001   0 2107  00026   0 2207  00000   0 2307  00002   0 2407  00002   0 2507  00010   0 2607  00255   0 2707  00002   0 2807  00000   0 2907  00000   0 3007  00000   0 3199 -99999 M
3200 316805 99999 01 PRCP HI 199912 0107  00000   0 0207  00000   0 0307  00000   0 0407  00000   0 0507  00000   0 0607  00045   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00015   0 1107  00037   0 1207  00000   0 1307  00036   0 1407  00097   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00000   0 1907  00000   0 2007  00020   0 2107  00002   0 2207  00034   0 2307  00000   0 2407  00000   0 2507  00000   0 2607  00000   0 2707  00000   0 2807  00000   0 2907  00000   0 3007  00000   0 3107  00000   0
3200 316805 99999 01 PRCP HI 200001 0107  00000   0 0207  00001   0 0307  00005   0 0407  00012   0 0507  00025   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00003   0 1007  00220   0 1107  00009   0 1207  00000   0 1307  00000   0 1407  00003   0 1507  00000   0 1607  00000   0 1707  00007   0 1807  00028   0 1907  00012   0 2007  00031   0 2107  00000   0 2207  00000   0 2307  00045   0 2407  00005   0 2507  00005   0 2607  00000   0 2707  00000   0 2807  00000   0 2907  00005   0 3007  00070   0 3107  00036   0
3200 316805 99999 01 PRCP HI 200002 0107  00000   0 0207  00000   0 0307  00000   0 0407  00000   0 0507  00001   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00000   0 1107  00000   0 1207  00037   0 1307  00071   0 1407  00148   0 1507  00000   0 1607  00000   0 1707  00000   0 1807  00015   0 1907  00007   0 2007  00000   0 2107  00000   0 2207  00000   0 2307  00001   0 2407  00000   0 2507  00000   0 2607  00000   0 2707  00000   0 2807  00053   0 2907  00000   0 3099 -99999 M   3199 -99999 M
3202 316805 99999 01 PRCP HI 200003 0107  00000   0 0207  00000   0 0307  00000   0 0407  00000   0 0507  00010   0 0607  00000   0 0707  00000   0 0807  00000   0 0907  00000   0 1007  00000   0 1107  00161   0 1207  00062   0 1307  00000   0 1407  00000   0 1507  00000   0 1607  00000   0 1707  00118   0 1807  00000   0 1907  00000   0 2007  00295   0 2107  00000   0 2207  00000   0 2307  00000   0 2407  00000   0 2507  00000   0 2607  00000   0 2707  00000   0 2807  00000   0 2907  00000   0 3007  00001   0 3107  00004   0

Comma delimited format

DSET,COOPID,WBNID,STATION NAME                  ,CD,ELEM,UN,YEARMO,DAHR, DAY01,F,F,DAHR, DAY02,F,F,DAHR, DAY03,F,F,DAHR, DAY04,F,F,DAHR, DAY05,F,F,DAHR, DAY06,F,F,DAHR, DAY07,F,F,DAHR, DAY08,F,F,DAHR, DAY09,F,F,DAHR, DAY10,F,F,DAHR, DAY11,F,F,DAHR, DAY12,F,F,DAHR, DAY13,F,F,DAHR, DAY14,F,F,DAHR, DAY15,F,F,DAHR, DAY16,F,F,DAHR, DAY17,F,F,DAHR, DAY18,F,F,DAHR, DAY19,F,F,DAHR, DAY20,F,F,DAHR, DAY21,F,F,DAHR, DAY22,F,F,DAHR, DAY23,F,F,DAHR, DAY24,F,F,DAHR, DAY25,F,F,DAHR, DAY26,F,F,DAHR, DAY27,F,F,DAHR, DAY28,F,F,DAHR, DAY29,F,F,DAHR, DAY30,F,F,DAHR, DAY31,F,F
----,------,-----,------------------------------,--,----,--,------,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-
3201,456789,99999,PULLMAN 2 NW                  ,10,PRCP,HI,200202,0108, 00012, ,0,0208, 00000,T,0,0399,-99999,M, ,0499,-99999,M, ,0599,-99999,M, ,0699,-99999,M, ,0708, 00006, ,0,0808, 00037, ,0,0908, 00000, ,R,1008, 00000, ,R,1108, 00000, ,R,1208, 00000, ,R,1308, 00000, ,R,1408, 00000, ,R,1508, 00000, ,R,1608, 00000, ,R,1708, 00000, ,R,1808, 00000, ,R,1908, 00000, ,R,2008, 00010, ,0,2108, 00000,T,0,2208, 00002, ,0,2308, 00000, ,R,2408, 00048, ,0,2508, 00003, ,0,2608, 00000, ,R,2708, 00000, ,R,2808, 00000,T,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,
3201,456789,99999,PULLMAN 2 NW                  ,10,SNOW,TI,200202,0108, 00050, ,0,0208, 00050, ,0,0308, 00050, ,0,0408, 00050, ,0,0508, 00050, ,0,0608, 00040, ,0,0708, 00030, ,0,0808, 00030, ,0,0908, 00000, ,R,1008, 00000, ,R,1108, 00000, ,R,1208, 00000, ,R,1308, 00000, ,R,1408, 00000, ,R,1508, 00000, ,R,1608, 00000, ,R,1708, 00000, ,R,1808, 00000, ,R,1908, 00000, ,R,2008, 00000, ,R,2108, 00000, ,R,2208, 00000, ,R,2308, 00000, ,R,2408, 00000, ,R,2508, 00010, ,0,2608, 00000, ,R,2708, 00000, ,R,2808, 00000,T,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,
3201,456789,99999,PULLMAN 2 NW                  ,10,SNWD, I,200202,0108, 00005, ,0,0299,-99999,M, ,0399,-99999,M, ,0499,-99999,M, ,0599,-99999,M, ,0699,-99999,M, ,0799,-99999,M, ,0808, 00000,T,0,0908, 00000, ,R,1008, 00000, ,R,1108, 00000, ,R,1208, 00000, ,R,1308, 00000, ,R,1408, 00000, ,R,1508, 00000, ,R,1608, 00000, ,R,1708, 00000, ,R,1808, 00000, ,R,1908, 00000, ,R,2008, 00000, ,R,2108, 00000, ,R,2208, 00000, ,R,2308, 00000, ,R,2408, 00000, ,R,2508, 00001, ,0,2699,-99999,M, ,2799,-99999,M, ,2808, 00000,T,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,
3201,456789,99999,PULLMAN 2 NW                  ,10,TMAX, F,200202,0108, 00033, ,0,0208, 00034, ,0,0308, 00032, ,0,0408, 00035, ,0,0508, 00036, ,0,0608, 00038, ,0,0708, 00043, ,0,0808, 00042, ,0,0908, 00041, ,0,1008, 00040, ,0,1108, 00043, ,0,1208, 00040, ,0,1308, 00035, ,0,1408, 00040, ,0,1508, 00040, ,0,1608, 00041, ,0,1708, 00044, ,0,1808, 00053, ,0,1908, 00046, ,0,2008, 00044, ,0,2108, 00047, ,0,2208, 00047, ,0,2308, 00053, ,0,2408, 00044, ,0,2508, 00030, ,0,2608, 00029, ,0,2708, 00032, ,0,2808, 00033, ,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,
3201,456789,99999,PULLMAN 2 NW                  ,10,TMIN, F,200202,0108, 00029, ,0,0208, 00023, ,0,0308, 00023, ,0,0408, 00018, ,0,0508, 00022, ,0,0608, 00025, ,0,0708, 00030, ,0,0808, 00031, ,0,0908, 00022, ,0,1008, 00029, ,0,1108, 00029, ,0,1208, 00017, ,0,1308, 00019, ,0,1408, 00019, ,0,1508, 00019, ,0,1608, 00027, ,0,1708, 00028, ,0,1808, 00028, ,0,1908, 00027, ,M,2008, 00029, ,0,2108, 00032, ,0,2208, 00035, ,0,2308, 00041, ,0,2408, 00030, ,0,2508, 00011, ,0,2608, 00019, ,0,2708, 00015, ,0,2808, 00021, ,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,
3201,456789,99999,PULLMAN 2 NW                  ,10,TOBS, F,200202,0108, 00030, ,0,0208, 00024, ,0,0308, 00026, ,0,0408, 00023, ,0,0508, 00027, ,0,0608, 00031, ,0,0708, 00036, ,0,0808, 00032, ,0,0908, 00028, ,0,1008, 00029, ,0,1108, 00030, ,0,1208, 00019, ,0,1308, 00025, ,0,1408, 00019, ,0,1508, 00027, ,0,1608, 00030, ,0,1708, 00030, ,0,1808, 00033, ,0,1908, 00034, ,M,2008, 00033, ,0,2108, 00035, ,0,2208, 00043, ,0,2308, 00044, ,0,2408, 00030, ,0,2508, 00017, ,0,2608, 00022, ,0,2708, 00021, ,0,2808, 00025, ,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,

The NCDC also supplied these formats without the F columns
*/


// A NCDC file can contain multiple stations
// UED can only store one station so we need to have a
// seperate file for each.

#include "../station_database.h"
//______________________________________________________________________________
class NCDC_element_record
{
   // This contains one month of data as read from the input file.
public:
   CORN::Ustring    data_origin;
   CORN::Ustring    cooperative_station_number;
   CORN::Ustring    WBAN_station_number;
   CORN::Ustring    station_name; // optional
   uint8          division_number;
//   CORN_string    meteorological_element_type_str;

   Year           year;
   Month          month;
//   DOM            dom;  Un necessary, we get this from the loop
//   Hour           hour; Not currently used
   Hour           hour[32];
   float32        value[32];
   char           data_measurement_flag[32];
   char           data_quality_flag[32];

   CORN::Quality_code  ued_quality[32];

   UED_units_code    raw_data_units;
public: // Extracted converted fields
   NCDC_element_labeled meteorological_element_type_labeled;
public:
   NCDC_element_record
   (const CORN::Ustring &raw_record
   ,bool  station_name_present
   ,bool  data_flags_present
   ,bool  comma_delimited
   );
   // This constructor is used for reading files.
};
//______________________________________________________________________________
class NCDC_daily_surface_data_format_convertor
: public UED_convertor
{
   // Options
   bool  station_name_present;
   bool  data_flags_present;
   bool  comma_delimited;
public:
   NCDC_daily_surface_data_format_convertor
      (int argc, const char *argv[]);
   virtual int convert();
   virtual uint32 perform_import();
   virtual uint32 perform_export() { return 1; } ; // Not yet implemented for this format
   // these paraemters are not UED_convertor members (const CORN::Ustring &station_ID_filter,Directory_name &ued_file_path);
private:
   void identify_format_options(const CORN::Ustring &header_line);
   // The NCDC format has several optional fields
   // and can be either space or comma delimited
   // this can be determined by reading the header line.
   void import_record(NCDC_element_record &element_record/*050315 now a member ,Directory_name &ued_file_path*/);

//NYI   int export(const CORN::Ustring &station_ID_filter);
};
//______________________________________________________________________________
void NCDC_daily_surface_data_format_convertor::identify_format_options(const CORN::Ustring &header_line)
{
   comma_delimited = header_line.find(",") != NPOS;                  // 070424 these may need to be find_substring
   station_name_present = header_line.find("STATION") != NPOS;
   data_flags_present = (header_line.find(",F,") != NPOS)
                     || (header_line.find(" F ") != NPOS);
};
//______________________________________________________________________________
NCDC_daily_surface_data_format_convertor::NCDC_daily_surface_data_format_convertor
(int argc,const  char *argv[])
:UED_convertor(argc,argv)
, station_name_present(true)
, data_flags_present(true)
, comma_delimited(false)
{
   all_known_weather_stations.set_reporting_agency(All_known_weather_stations::NCDC_REPORTING_AGENCY);
};
//______________________________________________________________________________
NCDC_element_record::NCDC_element_record
(const CORN::Ustring &raw_record
,bool  station_name_present
,bool  data_flags_present
,bool  // Not currently used comma_delimited
)
: meteorological_element_type_labeled(PRCP)
{
/*
W: 4      6     5                             30  2    4  2      6    4      6 1 1
DSET,COOPID,WBNID,STATION NAME                  ,CD,ELEM,UN,YEARMO,DAHR, DAY01,F,F,DAHR, DAY02,F,F,DAHR, DAY03,F,F,DAHR, DAY04,F,F,DAHR, DAY05,F,F,DAHR, DAY06,F,F,DAHR, DAY07,F,F,DAHR, DAY08,F,F,DAHR, DAY09,F,F,DAHR, DAY10,F,F,DAHR, DAY11,F,F,DAHR, DAY12,F,F,DAHR, DAY13,F,F,DAHR, DAY14,F,F,DAHR, DAY15,F,F,DAHR, DAY16,F,F,DAHR, DAY17,F,F,DAHR, DAY18,F,F,DAHR, DAY19,F,F,DAHR, DAY20,F,F,DAHR, DAY21,F,F,DAHR, DAY22,F,F,DAHR, DAY23,F,F,DAHR, DAY24,F,F,DAHR, DAY25,F,F,DAHR, DAY26,F,F,DAHR, DAY27,F,F,DAHR, DAY28,F,F,DAHR, DAY29,F,F,DAHR, DAY30,F,F,DAHR, DAY31,F,F
----,------,-----,------------------------------,--,----,--,------,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-,----,------,-,-
3201,456789,99999,PULLMAN 2 NW                  ,10,PRCP,HI,200202,0108, 00012, ,0,0208, 00000,T,0,0399,-99999,M, ,0499,-99999,M, ,0599,-99999,M, ,0699,-99999,M, ,0708, 00006, ,0,0808, 00037, ,0,0908, 00000, ,R,1008, 00000, ,R,1108, 00000, ,R,1208, 00000, ,R,1308, 00000, ,R,1408, 00000, ,R,1508, 00000, ,R,1608, 00000, ,R,1708, 00000, ,R,1808, 00000, ,R,1908, 00000, ,R,2008, 00010, ,0,2108, 00000,T,0,2208, 00002, ,0,2308, 00000, ,R,2408, 00048, ,0,2508, 00003, ,0,2608, 00000, ,R,2708, 00000, ,R,2808, 00000,T,0,2999,-99999,M, ,3099,-99999,M, ,3199,-99999,M,
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012
         1         2         3         4         5         6         7         8         9
*/
   int record_pos = 0;

   // Sometimes records are truncated (for 3200 records only?)
   // These need to be filled out to prevent substr errors.
   int expected_record_length = 18 + 17 + (station_name_present ? 31 : 0) + (12 * 31) + (data_flags_present ? (4 * 31) : 0);
   int raw_record_length = raw_record.length();
   if (raw_record_length < expected_record_length)
      raw_record.resize(expected_record_length);

   data_origin                   = raw_record.substr(record_pos,4);     record_pos += 5;
   cooperative_station_number    = raw_record.substr(record_pos,6);     record_pos += 7;
   WBAN_station_number           = raw_record.substr(record_pos,5);     record_pos += 6;
   if (station_name_present)
   {  station_name               = raw_record.substr(record_pos,30);     record_pos += 31;}
   CORN::Ustring division_number_str = raw_record.substr(record_pos,2);     record_pos += 3;
   division_number = (uint8)atoi(division_number_str.c_str());
   CORN::Ustring meteorological_element_type_str   = raw_record.substr(record_pos,4);     record_pos += 5;

   meteorological_element_type_labeled.set_label(meteorological_element_type_str.c_str());

   CORN::Ustring units_str         = raw_record.substr(record_pos,2);     record_pos += 3;
   float32 scale_factor = 1.0;
//    if (units_str == "HI")  scale_factor = 0.01;
//    if (units_str == "TI")  scale_factor = 0.1;



   CORN::Ustring year_str = raw_record.substr(record_pos,4);     record_pos += 4;  // These two fields are adjacent
   CORN::Ustring month_str = raw_record.substr(record_pos,2);     record_pos += 3;
   year = (Year)atoi(year_str.c_str());
   month = (Month)atoi(month_str.c_str());

//if (year==1951 && month == 6)
//cout << "reached" << endl;

   bool units_found = false;
   for (int i = 0; element_units_conversion[i].NCDC_units_code && !units_found; i++)
   {
      if (element_units_conversion[i].NCDC_units_code == units_str)
      {
         raw_data_units = element_units_conversion[i].UED_units_code;
         scale_factor     = element_units_conversion[i].scale_factor;
         units_found = true;
      };
   };
	if (meteorological_element_type_labeled.get() == AWND)
   {

            	// According to the NCDC documentation:
					// Units expressed in miles
					// per hour to tenths.  From January 1984 through June 1987 the
					// Element Unit is incorrectly listed as TK (Tenths of Knots), it
					// should be MH (Miles per Hour).

               // I believe this is a typographical error
               // it should be TL tens of miles per hour.
               // However I have encountered data sets where
               // the period July1, 1987 to July 1, 1996 is marked as MH not TL
               // but the data appear to be tens of miles per hour!

               // So I am always ignoring the units code
               // for AWND and always assuming tens of miles per hour
							raw_data_units = UE_miles_per_hour;
                     scale_factor  = 0.100;
	};
   for (DOM dom = 1; dom <= 31; dom++)
   {
      CORN::Ustring da_str = raw_record.substr(record_pos,2);    record_pos += 2;
      CORN::Ustring hr_str = raw_record.substr(record_pos,2);    record_pos += 3;
      hour[dom] = (Hour)atoi(hr_str.c_str());
      // da and hr are not currently used
      // For other records we will want to record the observation time for observed data
      CORN::Ustring value_str = raw_record.substr(record_pos,6); record_pos += 7 ;
      float32 raw_value = (float32)atoi(value_str.c_str());

      ued_quality[dom] = UED_measured;  // If quality flags are not specified, we will presume measured.
      if (data_flags_present)
      {
         char data_measurement = data_measurement_flag[dom] = raw_record.c_str()[record_pos]; record_pos += 2;
         char quality = data_quality_flag[dom] = raw_record.c_str()[record_pos]; record_pos += 2;
         bool quality_found =false;
         for (int i = 0; (quality_conversion[i].NCDC_quality != 0) && !quality_found; i++)
            if (quality_conversion[i].NCDC_quality == quality)
            {
               ued_quality[dom] = quality_conversion[i].UED_quality;
               quality_found = true;
            };

         switch (data_measurement)
         {
         case 'E' : ued_quality[dom] = UED_estimated; break;
         case 'M' : ued_quality[dom] = CORN::missing_quality;  break;
         // trace case 'T' :
         case 'B' : ued_quality[dom] = UED_estimated; break;
         };
         if ((CORN::is_approximately<float32>(raw_value,99999,0.0001)) || (CORN::is_approximately<float32>(raw_value,-99999,0.0001)))
         {
              ued_quality[dom] = CORN::missing_quality;
         };
      };
      value[dom]  = (ued_quality[dom] == CORN::missing_quality)
      	? (float)raw_value   //080711  This is to keep the -99999 value when writing to the database
			: (float)raw_value * scale_factor;
   };
};
//______________________________________________________________________________
void NCDC_daily_surface_data_format_convertor::import_record(NCDC_element_record &element_record)
{
   bool added_just_now = false;
   Station_database *station_database = provide_station_database(element_record.cooperative_station_number,added_just_now);
   UED_indexed_database *ued_file = &(station_database->ued_file);

      Year  year  = element_record.year;
      Month month = element_record.month;

cout << '\r' << (int)year << ' ' << (int)month << ' ' <<element_record.meteorological_element_type_labeled.get_label();

      for (DOM dom = 1; dom <=  date_days_in_month( year, month); dom++)
      {
         CORN::Date date_ymd;
         date_ymd.set_YMD((Year)year,(Month)month,(DOM)dom);
         datetime64 set_date = date_ymd.get_datetime64(); //

         UED::Time_query_single_date set_date_query(set_date);
         bool created;
         CORN::Quality_code attribute = element_record.ued_quality[dom];

         UED_data_record_creation_layout *creation = 0;
         switch (element_record.meteorological_element_type_labeled.get())
         {  case  TMAX : creation = &max_temperature_creation;           break;
            case  TMIN : creation = &min_temperature_creation;           break;
            case  SNOW : creation = &snow_fall_creation;                 break;
            case  SNWD : creation = &snow_depth_creation;                break;
            case  TOBS : creation = &instantaneous_temperature_creation; break;
            case  PRCP : creation = &precipitation_creation;             break;
            case  AWND : creation = &wind_speed_creation;					 break;
            case  DPTP : creation = &avg_dew_point_temperature_creation; break;
            case  MNRH : creation = &min_relative_humidity_creation;		 break;
            case  MXRH : creation = &max_relative_humidity_creation;		 break;
         };
         if (creation)
            ued_file->set_value
            (element_record.value[dom]
            ,set_date_query
            ,element_record.raw_data_units
            ,attribute
            ,*creation
            ,created);
      };
};
//______________________________________________________________________________
uint32 NCDC_daily_surface_data_format_convertor::perform_import()
{
   // Open input file
   ifstream input_file(parameters.target_filename.c_str());

   CORN::Ustring buffer;
   buffer.read_line(input_file);    // The header line
   identify_format_options(buffer);
   buffer.read_line(input_file);    // The dash line
   uint32 record_count = 0;

   while (!input_file.eof())
   {
      buffer.read_line(input_file);
      if (buffer.length())
      {
         NCDC_element_record element_record(buffer,station_name_present,data_flags_present,comma_delimited);
         if (  (parameters.station_IDs_filter.length() == 0)
             ||(parameters.station_IDs_filter.contains(element_record.cooperative_station_number))
             ||(parameters.station_IDs_filter == "all")
             )
         {
            import_record(element_record);
            record_count++;
         };
      };
   };
   return record_count;
};
//______________________________________________________________________________
int NCDC_daily_surface_data_format_convertor::convert()
{
   return UED_convertor::convert();
};
//______________________________________________________________________________
int main(int argc, const char *argv[])
{
   // I.e. import path\filename.ued path\filename.txt 6144475

   NCDC_daily_surface_data_format_convertor convertor(argc,argv);
   int result = convertor.convert();
   convertor.notify_climgen();
   return result;
};
//______________________________________________________________________________
