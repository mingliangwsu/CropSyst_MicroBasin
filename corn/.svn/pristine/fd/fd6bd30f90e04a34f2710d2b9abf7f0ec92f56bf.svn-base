#ifndef units_code_CUH
#define units_code_CUH

#ifndef units_measureH
#  include <corn/metrology/units_measure.h>
#endif
#ifndef units_code_commonH
#   include <corn/metrology/units_code_common.h>
#endif
#ifndef units_code_temporalH
#   include <corn/metrology/units_code_temporal.h>
#endif

// UE_      Units code           (English or US customary or Imperial standard)
// SUE_     Subunits code (english customary)

#define IMPERIAL(x)  ((nat16)0x8040 |(nat16)x)
#define US_CU(x)     ((nat16)0x8000 |(nat16)x)
#define CU(x)        ((nat16)0x8000 |(nat16)x)

#define US_CM(x)     ((nat16)0x80   | (nat16)x)
#define CM(x)        ((nat16)0x80   | (nat16)x)

// UM_temperature                (nat8) 0x01
#define UE_Farenheit                          CU(0x0100)

// UM_thermaldynamic_temperature (nat8) 0x02
#define UE_Rankine                            CU(0x0200)
//The Rankine scale has the same size of degree as the Fahrenheit,
//but with its zero at absolute zero - so the 'boiling point' (212°F) is 671.67°R.

// UM_XXXXX not currently used        (nat8) 0x03   (was thermal time)

// UM_chemical_weight            (nat8) 0x04
// I haven't seen  Engish units of chemical weight

// UM_amount_of_substance        (nat8) 0x05
// I haven't seen  Engish units of amount of substance

// UM_mass                       (nat8) 0x06
#define AVOIRDUPOIS(x) ((nat16)0x8000 | (nat16)x)
#define TROY(x)        ((nat16)0x8010 | (nat16)x)
#define WOOL(x)        ((nat16)0x8020 | (nat16)x)
// 0x30 unused
#define IMPERIAL_AVOIRDUPOIS(x) ((nat16)0x8040 | (nat16)x)
#define TRADE(x)       ((nat16)0x8050 | (nat16)x)
#define TOWER(x)       ((nat16)0x8060 | (nat16)x)
// 0x70 unused

// Note that grain (barley grain) is always the same for avoirdupois, troy, tower, london and wool weights
#define UE_grain                                    AVOIRDUPOIS(0x0600)
// scrupple                                                      0x0601
// penny                                                         0x0602
#define UE_avoirdupois_dram                         AVOIRDUPOIS(0x0603)
#define UE_avoirdupois_ounce                        AVOIRDUPOIS(0x0604)
//#define unused                                    AVOIRDUPOIS(0x0605)
#define UE_avoirdupois_pound                        AVOIRDUPOIS(0x0606)
#define UE_avoirdupois_clove                        AVOIRDUPOIS(0x0607)
#define UE_avoirdupois_butchers_stone               AVOIRDUPOIS(0x0608)
// butchers_stone  8 pounds
#define UE_avoirdupois_stone                        AVOIRDUPOIS(0x0609)
// stone  unit of weight equal to 14 pounds
#define UE_avoirdupois_tod                          AVOIRDUPOIS(0x060A)
#define UE_avoirdupois_quarter                      AVOIRDUPOIS(0x060B)
#define UE_avoirdupois_hundredweight_US             AVOIRDUPOIS(0x060C)
// hundredweight  unit of weight of 100 pounds US.
#define UE_avoirdupois_hundredweight_Imperial IMPERIAL_AVOIRDUPOIS(0x060C)
// hundredweight  unit of weight of 112 pounds in UK.
#define UE_avoirdupois_sack                         AVOIRDUPOIS(0x060D)
#define UE_avoirdupois_kip                          AVOIRDUPOIS(0x060E)
#define UE_avoirdupois_ton_US                       AVOIRDUPOIS(0x060F)
#define UE_avoirdupois_ton_Imperial        IMPERIAL_AVOIRDUPOIS(0x060F)
#define UE_tower_penny                                     TOWER(0x0602)
#define UE_tower_pound                                     TOWER(0x0605)
#define UE_trade_pound                                     TRADE(0x0605)
#define UE_trade_stone                                     TRADE(0x0609)
#define UE_troy_scruple                                     TROY(0x0601)
#define UE_troy_pennyweight                                 TROY(0x0602)
#define UE_troy_dram                                        TROY(0x0603)
// 0.125 troy ounce
#define UE_troy_ounce                                       TROY(0x0604)
#define UE_troy_pound                                       TROY(0x0605)
#define UE_wool_pound                                       WOOL(0x0605)
#define UE_wool_clove                                       WOOL(0x0607)
#define UE_wool_stone                                       WOOL(0x0609)
#define UE_wool_tod                                         WOOL(0x060A)
// tod  old unit of weight of wool equal to 28 pounds

// UM_weight_liquid              (nat8) 0x07
//Reserved There may be english units of liquid weight

// UM_weight_dry                 (nat8) 0x08
//obsolete?
 
// not currently used  (nat8) 0x09
// not currently used  (nat8) 0x0A
// not currently used  (nat8) 0x0B

// UM_luminous_intensity         (nat8) 0x0C
// No Engish units?
//#define UM_luminous_flux              (nat8) 0x0D

// UM_illuminance                (nat8) 0x0E

// not currently used  (nat8) 0x0F

// 1C00 to 1FFF are currently free,

// UM_linear                     (nat8) 0x20

#define SUE_inch                 0x01
#define SUE_nail                 0x02
#define SUE_hand                 0x03
#define SUE_link                 0x04


//NYI span    (9 inches)
//NYI pace (30 inches)

#define SUE_foot                 0x05
#define SUE_yard                 0x06
#define SUE_rod                  0x07
//The following are the same as rod:
#define SUE_pole                 0x07
#define SUE_perch                0x07
#define SUE_lugg                 0x07
#define SUE_fathom               0x08
#define SUE_chain                0x09
//NYI SUE_cable  120 fathms
#define SUE_furlong              0x0A
#define SUE_statute_mile         0x0B
#define SUE_nautical_mile        0x0C
// rename statute_mile to mile_statute
// rename nautical_mile to mile_nautical
// NYI SUE_league_statute
// NYI SUE_league_nautical
// reserved                  0x0E
// reserved                  0x0F

#define UE_inch_linear                   CU(UC_length) | SUE_inch
#define UE_nail_linear                   CU(UC_length) | SUE_nail
#define UE_hand_linear                   CU(UC_length) | SUE_hand
#define UE_link_linear                   CU(UC_length) | SUE_link
#define UE_foot_linear                   CU(UC_length) | SUE_foot
#define UE_yard_linear                   CU(UC_length) | SUE_yard
#define UE_rod_linear                    CU(UC_length) | SUE_rod
#define UE_pole_linear                   CU(UC_length) | SUE_pole
#define UE_perch_linear                  CU(UC_length) | SUE_perch
#define UE_lugg_linear                   CU(UC_length) | SUE_lugg
#define UE_fathom_linear                 CU(UC_length) | SUE_fathom
#define UE_chain_linear                  CU(UC_length) | SUE_chain
#define UE_furlong_linear                CU(UC_length) | SUE_furlong
#define UE_statute_mile_linear           CU(UC_length) | SUE_statute_mile
#define UE_nautical_mile_linear          CU(UC_length) | SUE_nautical_mile
//#define UE_nautical_mile_historic_linear          CU(UC_length) | SUE_nautical_mile_historic

// ! NYI UE_twain_depth (12 feet)

//UM_land_area                  (nat8) 0x2A   // 00101010 00000000

#define UE_acre                              CU(0x2A00)
#define UE_rood                              CU(0x2A01)
//rood  old unit of land area equal to 1/4 acre
#define UE_arpent_area                       CU(0x2A02)
//arpent  unit of land area slightly smaller than an acre
// Note that there is also an arpent distance

//NYI  UE_section  1mile^2 or 640 acres
//NYI  UE_township   36mile^2

#define UE_virgate                           CU(0x2A04)
// virgate  old unit of land area usually equal to 30 acres or 1/4 hide

#define UE_hide                              CU(0x2A05)
// hide  old unit of land area equal to 120 acres

#define UE_morgen_scandinavian               CU(0x2A06)
#define UE_morgen_prussian                   CU(0x2A07)
#define UE_morgen_dutch                      CU(0x2A08)
#define UE_morgen_south_african              CU(0x2A09)
// morgen  unit of land area slightly more than two acres
//          There are serveral morgen units

// UM_volume                     (nat8) 0x30   // 00101100 00000000

// UM_liquid                     (nat8) 0x34   // 00101110 00000000
#define IMPERIAL_LIQUID_MEASURE(x) ((nat16)0x8040 | (((nat16)UM_liquid)<<8) | (nat16)x)
#define US_LIQUID_MEASURE(x)       ((nat16)0x8000 | (((nat16)UM_liquid)<<8) | (nat16)x)

#define SUE_minim        0x00
#define SUE_drachm       0x01
#define SUE_ounce        0x02
#define SUE_gill         0x03
#define SUE_mutchkin     0x04
#define SUE_pint         0x05
#define SUE_fifth        0x06
#define SUE_quart        0x07
#define SUE_gallon       0x08
#define SUE_peck         0x09
#define SUE_bushel       0x0A
#define SUE_quarter      0x0B
#define SUE_tun          0x0C
#define SUE_chaldron     0x0D
//NUI SUE_dram

#define UE_fluid_minim_Imperial       IMPERIAL_LIQUID_MEASURE(SUE_minim)
#define UE_fluid_drachm_Imperial      IMPERIAL_LIQUID_MEASURE(SUE_drachm)
#define UE_fluid_ounce_Imperial       IMPERIAL_LIQUID_MEASURE(SUE_ounce)
#define UE_fluid_gill_Imperial        IMPERIAL_LIQUID_MEASURE(SUE_gill)
#define UE_fluid_mutchin_Imperial     IMPERIAL_LIQUID_MEASURE(SUE_mutchkin)
#define UE_fluid_pint_Imperial        IMPERIAL_LIQUID_MEASURE(SUE_pint)
#define UE_fluid_fifth_Imperial       IMPERIAL_LIQUID_MEASURE(SUE_fifth)
#define UE_fluid_quart_Imperial       IMPERIAL_LIQUID_MEASURE(SUE_quart)
#define UE_fluid_gallon_Imperial      IMPERIAL_LIQUID_MEASURE(SUE_gallon)
#define UE_fluid_peck_Imperial        IMPERIAL_LIQUID_MEASURE(SUE_peck)
#define UE_fluid_bushel_Imperial      IMPERIAL_LIQUID_MEASURE(SUE_bushel)
#define UE_fluid_quarter_Imperial     IMPERIAL_LIQUID_MEASURE(SUE_quarter)
#define UE_fluid_tun_Imperial         IMPERIAL_LIQUID_MEASURE(SUE_tun)
#define UE_fluid_chaldron_Imperial    IMPERIAL_LIQUID_MEASURE(SUE_chaldron)

// Ale and wine measures not implemented
//NYI UE_fluid_firkin      IMPERIAL_LIQUID_MEASURE(0)
//NYI UE_fluid_barrel      IMPERIAL_LIQUID_MEASURE(0)
//NYI UE_fluid_hogshead    IMPERIAL_LIQUID_MEASURE(0)
//NYI UE_fluid_bottle      IMPERIAL_LIQUID_MEASURE(0)

#define UE_fluid_minim_US       US_LIQUID_MEASURE(SUE_minim)
#define UE_fluid_drachm_US      US_LIQUID_MEASURE(SUE_drachm)
#define UE_fluid_ounce_US       US_LIQUID_MEASURE(SUE_ounce)
//NYI UE_fluid_dram_US US_LIQUID_MEASURE(SUE_dram)
// 0.125 fluid ounce
#define UE_fluid_pint_US        US_LIQUID_MEASURE(SUE_pint)
#define UE_fluid_gill_US        US_LIQUID_MEASURE(SUE_gill)
#define UE_fluid_fifth_US       US_LIQUID_MEASURE(SUE_fifth)
#define UE_fluid_quart_US       US_LIQUID_MEASURE(SUE_quart)
#define UE_fluid_gallon_US      US_LIQUID_MEASURE(SUE_gallon)
// United States does not use peck and bushel system for liquid measure
//  UE_fluid_peck_US        US_LIQUID_MEASURE(UE_peck)
//  UE_fluid_bushel_US      US_LIQUID_MEASURE(UE_bushel)
//  UE_fluid_quarter_US     US_LIQUID_MEASURE(UE_quarter)
//  UE_fluid_tun_US         US_LIQUID_MEASURE(UE_tun)
//  UE_fluid_chaldron_US    US_LIQUID_MEASURE(UE_chaldron)

// UM_dry                        (nat8) 0x35

#define  IMPERIAL_DRY_MEASURE(x) ((nat16)0x8040 | (((nat16)UM_dry)<<8) | (nat16)x)
#define US_DRY_MEASURE(x)       ((nat16)0x8000 | (((nat16)UM_dry)<<8) | (nat16)x)

#define UE_dry_minim_Imperial       IMPERIAL_DRY_MEASURE(SUE_minim)
#define UE_dry_drachm_Imperial      IMPERIAL_DRY_MEASURE(SUE_drachm)
#define UE_dry_ounce_Imperial       IMPERIAL_DRY_MEASURE(SUE_ounce)
#define UE_dry_pint_Imperial        IMPERIAL_DRY_MEASURE(SUE_pint)
#define UE_dry_gill_Imperial        IMPERIAL_DRY_MEASURE(SUE_gill)
#define UE_dry_fifth_Imperial       IMPERIAL_DRY_MEASURE(SUE_fifth)
#define UE_dry_quart_Imperial       IMPERIAL_DRY_MEASURE(SUE_quart)
#define UE_dry_gallon_Imperial      IMPERIAL_DRY_MEASURE(SUE_gallon)
#define UE_dry_peck_Imperial        IMPERIAL_DRY_MEASURE(SUE_peck)
#define UE_dry_bushel_Imperial      IMPERIAL_DRY_MEASURE(sUE_bushel)
#define UE_dry_quarter_Imperial     IMPERIAL_DRY_MEASURE(SUE_quarter)
#define UE_dry_tun_Imperial         IMPERIAL_DRY_MEASURE(SUE_tun)
// note tun may be liquid measure only
#define UE_dry_chaldron_Imperial    IMPERIAL_DRY_MEASURE(SUE_chaldron)

#define UE_dry_minimUS        US_DRY_MEASURE(SUE_minim)
#define UE_dry_drachm_US      US_DRY_MEASURE(SUE_drachm)
#define UE_dry_ounce_US       US_DRY_MEASURE(SUE_ounce)
#define UE_dry_pint_US        US_DRY_MEASURE(SUE_pint)
#define UE_dry_gill_US        US_DRY_MEASURE(SUE_gill)
#define UE_dry_fifth_US       US_DRY_MEASURE(SUE_fifth)
#define UE_dry_quart_US       US_DRY_MEASURE(SUE_quart)
#define UE_dry_gallon_US      US_DRY_MEASURE(SUE_gallon)
#define UE_dry_peck_US        US_DRY_MEASURE(SUE_peck)
#define UE_dry_bushel_US      US_DRY_MEASURE(SUE_bushel)
#define UE_dry_quarter_US     US_DRY_MEASURE(SUE_quarter)
#define UE_dry_tun_US         US_DRY_MEASURE(SUE_tun)
#define UE_dry_chaldron_US    US_DRY_MEASURE(SUE_chaldron)

// NYI  Reserved codes                    (nat8) 0x36  - 0x3F

// Note calories are US customary units.
#define UE_calorie_energy                 CU(0x4C00)
// Currently (I think, need to check my conversion of Langley units which would be 4.184J)
// assuming thermochemical calorie  cal_th   (gram calorie)  denoted as  cal
// [kilogram calorie called Calorie is denoted as either C (sometimes c)]
// other variations are:
// 4 °C calorie           cal_4
// 15 °C calorie          cal_15
// 20 °C calorie          cal_20
// Mean calorie            cal_mean
// International Steam Table calorie (1929)
// International Steam Table calorie (1956)  cal_IT
// IUNS calorie
#define UE_mega_calorie_energy            CU(0x4C03)

//UM_force                      (nat8) 0x50
#define UE_poundal                            CU(0x5000)
// poundal  unit of force that accelerates 1 pound to 1 foot / second / second

// Not sure to use for inches of mercury and bars
// NYI  UE_bars_atmospheric_pressure       ???   CU(0x5900)

// UM_electric_charge            (nat8) 0x71
//NYI    UE_franklin                     US_CU(0x7100)

//> Do not delete this line, it is used by the units code constant generator

#define UE_Farenheit_degree_days         U_a_b(UE_Farenheit,UT_day)
#define UE_miles_per_hour                 U_a_per_b(UE_statute_mile_linear,UT_hour)
#define UE_miles_per_day                  U_a_per_b(UE_statute_mile_linear,UT_day)
#define UE_knots                          U_a_per_b(UE_nautical_mile_linear,UT_hour)

#define UE_Langley                        U_a_per_b(UE_calorie_energy,UC_square_cm_area)
//No abbreviation named after Samuel P. Langley  energy flux per area  cal/cm2
//used as unit of solar radiation

// Rates  gallons are presume US customary liquid measure
// the US is the only country currently using gallon measure
// it is presumed liquid because flow rates are almost always liquid.
#define UE_gallon_per_minute              U_a_per_b(UE_fluid_gallon_US,UT_minute)
#define UE_gallon_per_hour                U_a_per_b(UE_fluid_gallon_US,UT_hour)

// Entropy units:
#define UE_clausius                       U_a_per_b(UE_calorie_energy,UC_kelvin)
// clausius  (abbr: Cl)  Rudolf Julius Emanuel Clausius  entropy  cal/K

//NYI footlambert  unit of luminance of a surface emitting one lumen per square foot (this could be implemented as a composite unit

#define UE_ton_per_acre                   U_a_per_b(UE_avoirdupois_ton_US,UE_acre)
#define UE_pound_per_acre                 U_a_per_b(UE_avoirdupois_pound,UE_acre)

/*
X = implemented
 barleycorn  old unit of length equal to one-third inch

 centner  old unit of weight equal to about 110 pounds
 chaldron  old unit of dry volume equal to between 32 and 72 bushels
 cord  unit of wood equal to 128 cubic feet
 cubit  unit of length equal to 18 inches
 cusec  unit of liquid flow equal to one cubic foot per second
 denier  unit of yarn fineness
 digit  unit of length equal to 3/4 of an inch
X dram  unit of weight equal to 1/16 of an ounce
 ell  old unit of length equal to 45 inches
 em  unit of measuring width of typeface where width of letters equals height

 firkin  old unit of capacity equal to one quarter of a barrel
 hogshead  unit of capacity equal to 63 gallons
 horsepower  unit of power equal to 550 foot-pounds of work per second

*/

#endif
