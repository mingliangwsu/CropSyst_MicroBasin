# ifndef units_code_SIH
#define units_code_SIH

#ifndef units_code_commonH
#   include "corn/metrology/units_code_common.h"
#endif

#ifndef units_code_temporalH
#   include "corn/metrology/units_code_temporal.h"
#endif

// SUC_     Subunits code (metric standard)

// There are two basis for the metric system
// MKS system based on the meter, kilogram, and second.
// CGS system based on the centimeter, the gram, and the second.
// See http://www.unc.edu/~rowlett/units/cgsmks.html
// The ratio between a CGS unit and the corresponding MKS unit is usually a power of 10
// (exception is 1000 Newtons per dyne)
// The MKS system is now generally the preferred system

/*
CGS unit       measuring   SI(MKS) equivalent
(CGS) barye (ba)     pressure                0.1 pascal (Pa)
(CGS) biot (Bi)      electric current        10 amperes (A)
(CGS) calorie (cal)  heat energy             4.1868 joule (J)
(CGS) darcy          permeability            0.98692 x 10-12 square meter (m2)
(CGS) debye (D)      electric dipole moment  3.33564 x 10-30 coulomb meter (C·m)
(CGS) dyne (dyn)     force                   10-5 newton (N)
(CGS) emu            magnetic dipole moment  0.001 ampere square meter (A·m2)
(CGS) erg            work, energy            10-7 joule (J)
(CGS) franklin (Fr)  electric charge         3.3356 x 10-10 coulomb (C)
(CGS) galileo (Gal)  acceleration            0.01 meter per second squared (m·s-2)
(CGS) gauss (G)      magnetic flux density   10-4 tesla (T)
(CGS) gilbert (Gi)   magnetomotive force     0.795 775 ampere-turns (A)
(CGS) kayser (K)     wave number             100 per meter (m-1)
(CGS) lambert (Lb)   luminance               3183.099 candelas per square meter (cd·m-2)
(CGS) langley        heat transmission       41.84 kilojoules per square meter (kJ·m-2)
(CGS) line (li)      magnetic flux           10-8 weber (Wb)
(CGS) maxwell (Mx)   magnetic flux           10-8 weber (Wb)
(CGS) oersted (Oe)   magnetic field strength 79.577 472 ampere-turns per meter (A·m-1)
(CGS) phot (ph)      illumination            104 lux (lx)
(CGS) poise (P)      dynamic viscosity       0.1 pascal second (Pa·s)
(CGS) stilb (sb)     luminance               104 candelas per square meter (cd·m-2)
(CGS) stokes (St)    kinematic viscosity     10-4 square meters per second (m2·s-1)
(CGS) unit pole      magnetic flux           1.256 637 x 10-7 weber (Wb)
 */

// UM_temperature                (nat8) 0x01
#if (CS_VERSION==4)
#define UC_celcius                       (nat16)0x0100 // degrees C
#define UC_decicelcius                   (nat16)0x0141
#endif

#define UC_Celcius                       ((nat16)0x0100) // degrees C
#define UC_deciCelcius                   ((nat16)0x0141)
// Celcius is conventionally capitalized

// UM_thermaldynamic_temperature (nat8) 0x02
#define UC_kelvin                        (nat16)0x0200 // K
// Thermal dynamic temperature
// kelvin  K William Thompson, Lord Kelvin  temperature
// kelvin is conventionally lower case

// UM_XXXXX not currently used        (nat8) 0x03   (was thermal time)

// UM_chemical_weight            (nat8) 0x04
#define UC_Equivelent_weight             (nat16)0x0400
#define UC_mEq                           (nat16)0x0443

// UM_amount_of_substance        (nat8) 0x05
#define UC_mole                          (nat16)0x0500
#define UC_cmole                          (nat16)0x0542
#define UC_mmole                          (nat16)0x0543

// UM_mass                       (nat8) 0x06
// extensive
// Presumed as weight
#define UC_nanogram_mass                 (nat16)0x0649
#define UC_microgram_mass                (nat16)0x0646
#define UC_mg_mass                       (nat16)0x0643
#define UC_cg_mass                       (nat16)0x0642
#define UC_dg_mass                       (nat16)0x0641
#define UC_gram_mass                     (nat16)0x0600
#define UC_g                             (nat16)0x0600
#define UC_g_mass                        (nat16)0x0600
#define UC_Dg_mass                       (nat16)0x0601
#define UC_hg_mass                       (nat16)0x0602
#define UC_kg_mass                       (nat16)0x0603
#define UC_quintal                       (nat16)0x0605
// quintal  unit of weight equal to 100 kilograms
#define UC_tonne_mass                    (nat16)0x0606
// Metric tonne is 1000 kg or Mg
#define UC_Mg_mass                       (nat16)0x0606

// Liquid weight
// UM_weight_liquid              (nat8) 0x07
// These are used for liquid
// 040715obsolete  UC_gram_liquid                   (nat16)0x0700
// 040715obsolete  UC_kg_liquid                     (nat16)0x0703
// Occasionally liquid is measured in terms of mass

// UM_weight_dry                 (nat8) 0x08
// obsolete?

// not currently used  (nat8) 0x09
// not currently used  (nat8) 0x0A
// not currently used  (nat8) 0x0B

// UM_luminous_intensity         (nat8) 0x0C
#define UC_candela                       (nat16)0x0C00
// candela  unit of luminous intensity

// UM_luminous_flux              (nat8) 0x0D
#define UC_lumen                         (nat16)0x0D00
// lumen  unit of luminous flux
// (unit of brightness of light?)

// UM_illuminance                (nat8) 0x0E

// lux  unit of illumination equal to one lumen per square meter
// I think this may need to have its own measure (not a composite)
#define UC_lux                           (nat16)0x0E00
#define UC_kilo_lux                      (nat16)0x0E03
#define UC_phot                          (nat16)0x0E04
#define UC_stilb                         (nat16)0x0E04
// lambert stilb = phot = 10^4 lux

// not currently used  (nat8) 0x0F

// 1C to 1F are currently free,

// UM_linear                     (nat8) 0x20
// extensive
#define UC_length                        (nat16)0x2000 // Can be use for any general measure of length  <- This is probably obsolete
#define UC_meter                         (nat16)0x2000 // Can be use for any general measure of length
#define UC_km                            (nat16)0x2003
#define UC_m                             (nat16)0x2000
#define UC_cm                            (nat16)0x2042
#define UC_mm                            (nat16)0x2043
#define UC_tenth_mm                      (nat16)0x2044
#define UC_micro_meter                   (nat16)0x2046
#define UC_micron       UC_micro_meter

#define UC_angstrom                      (nat16)0x204A
// angstrom (abbr: Å) unit of length one ten-billionth of a meter ( 10e-10 m) named after Anders Jonas Ångström

#define UC_fermi                         (nat16)0x204F
// fermi (abbr: fm) unit of length equal to one quadrillionth  of a meter (10^-15 m) named after  Enrico Fermi

// UM_rectangular_area           (nat8) 0x28   // 00101000 00000000
// UM_area                       (nat8) 0x28   // 00101000 00000000
// obsolete#define UC_square_meter_flat_area_obs    (nat16)0x2800
#define UC_square_meter_area             (nat16)0x2800
#define UC_square_m_area                 (nat16)0x2800
#define UC_square_cm_area                (nat16)0x2842
// I.e. generally considered flat surfaces (I.e. floor space, walls, farm fields)

// UM_land_area                  (nat8) 0x2A   // 00101010 00000000
#define UC_are                           (nat16)0x2A00
#define UC_hectare                       (nat16)0x2A02

// UM_volume                     (nat8) 0x30   // 00110000 00000000
#define UC_cubic_meter_volume            (nat16)0x3000
#define UC_cubic_cm_volume               (nat16)0x3042

#define UC_stere UC_cubic_meter_volume

// UM_liquid                     (nat8) 0x34   // 00101110 00000000
#define UC_liter                         (nat16)0x3400
#define UC_ml                            (nat16)0x3443

// UM_dry                        (nat8) 0x35

// NYI  Reserved codes                    (nat8) 0x36  - 0x3F

// UM_plane_angle                (nat8) 0x40
// plane angles do not have metric powers
#define UC_radian_angle                  (nat16)0x4000
#define UC_degree_angle                  (nat16)0x4001
// Right is  0, Up/Forward is 90, Left is 180, Down/backward is 270
// NYI   Reserved  code                        (nat16)0x4002
// The following are bounded degrees
#define UC_degrees_longitude             (nat16)0x4003
#define UC_degrees_latitude              (nat16)0x4004

#define UC_degree_from_east              (nat16)0x4005
// East is  0, North is 90, West is 180, South is 270
#define UC_degree_from_north             (nat16)0x4006
// North is 0,  East is 90, South is 180, West is 270
// Cardinal  or azimuth

#define UC_gradian_angle                 (nat16)0x4010
#define UC_gon                           UC_gradian_angle
#define UC_grade                         UC_gradian_angle
// Gradian is a unit of angular measure in which the angle of an entire circle is 400 gradians.
// A right angle is therefore 100 gradians.
// A gradian is sometimes also called a gon or a grade.

// UM_solid_angle                (nat8) 0x41
// not sure but I thing  solid_angle will not have metric powers
#define UC_steradian                     (nat16)0x4100

// UM_frequency                  (nat8) 0x42
#define UC_hertz                         (nat16)0x4200
// hertz unit of frequency equal to one cycle per second.  Named after Heinrich R. Hertz
#define UC_fresnel                       (nat16)0x420C
// fresnel  unit of optical frequency equal to one terahertz

// NYI       Reserved  codes                          (nat8) 0x43 - 0x47

// UM_specific_heat              (nat8) 0x48

// Specific heat is actually Joules per kg times kelvin
// since this is a complex unit, I create a new unit of measure

// UM_thermal_conductivity       (nat8) 0x49
#define UC_W_per_m_K_thermal_conductivity (nat16)0x4900
// Thermal conductivity is actually Watts per meter times kelvin
// since this is a complex unit, I create a new unit of measure

// 040715  We now have a single unit for Joule (we will use energy)
// quality of heat will be simply a modifier
// Joules may have the following qualifications:
// quality of heat
// work
// energy
// ! 040715 depricated        UM_quality_of_heat_D   0x4A
// ! 040715 depricated        UM_work_D   0x4B

// UM_energy                     (nat8) 0x4C
// extensive (Enthalpy)
#define UC_joule_energy                  (nat16)0x4C00
#define UC_kilo_joule_energy             (nat16)0x4C03
#define UC_mega_joule_energy             (nat16)0x4C06
#define UC_erg                           (nat16)0x4C47
// 1 erg = 1/10000000 joules
// erg  CGS unit of work measuring force of one dyne applied over one centimeter

// joule  unit of work done by force of one newton over a distance of one meter
// joule  J  James Prescott Joule  energy  (kg·m²)/s²
// Although a joule is one newton over one meter we derive a distinct units for
// joule because it is often used in a numerator
// 1 Joule = 1 newton meter

// Not sure the unit of measure here   (energy rate?)
#define UC_watt_second                         UC_joule_energy
#define UC_watt_hour                           0x4D00
#define UC_Board_of_Trade_unit                 (U_metric_kilo | UC_watt_hour)
// The Board of Trade unit (B.O.T.U.) is an obsolete UK synonym for kilowatt hour.
#define UC_watt_day                            0x4E00
// I have not used composition to represent watt hour because
// watt hr/m^2 is commonly used
// I have also see where solar radiation is in the units of watt hour but is the daily average of the hourly values

// UM_force                      (nat8) 0x50
#define UC_newton_force                  (nat16)0x5000
#define UC_newton                        (nat16)0x5000
// newton  unit of force that accelerates 1 kilogram to  meter / second / second
// (abbr: N) named after Isaac Newton  force kg·m·s-2 (kg·m/s²)
// Because newton is frequently used and has 2 numerators and one denominator,
// a distinct measure is defined. (Note we cannot cancel the seconds in the numerator and denominator

// UM_radiant_flux               (nat8) 0x55
#define UC_watt_radiant_flux             (nat16)0x5500
// This is also power

// UM_pressure                   (nat8) 0x58
// intensive
// pascal (abbr: Pa) unit of pressure equal to one newton meter squared ( N m2) named after  Blaise Pascal
// Because pressure is the basis for other units we give it its own measure
// instead of using U_a_b(UC_newton UC_meter_length)
// Pressure may have the following qualifications
// atmospheric
// stress
#define UC_pascal_pressure               (nat16)0x5800
#define UC_hPa                           (nat16)0x5802
#define UC_kPa                           (nat16)0x5803
#define UC_barye                         (nat16)0x5841
// 1 barye = 0.1 pascal
#define UC_millibar                      (nat16)0x5802
// 1 millibar (millibarye) = 1 hectopascal

// Note barametric pressure can be represented with inches of mercury ("pascals")
// but it may (I think) be either normalized to sea level or at altitude.
// Note sure if I wan't to make a separate variable code for barametric pressure
// at altitude (?) and one for normalized to sea level
// This should probably be variable code property

// NYI UC_torr  (nonstandard)
// NYI torr  unit of pressure equal to 1/760 of standard atmospheric pressure
// NYI torr  - Evangelista Torricelli  pressure  133.32 Pa

// UM_osmotic_pressure             (nat8) 0x5B
#define UC_osmol                          (nat8) 0x5B00

// UM_viscosity_dynamic           (nat8) 0x5E
// Although dynamic viscosity is a composed unit of measure, it is given its own measure
// because it is a commonly used unit and there are special named units derived
#define UC_pascal_second_dynamic_viscosity  (nat16)0x5E00
#define UC_poise                            (nat16)0x5E41
// poise (abbr: P) dynamic viscosity, unit of viscosity of liquids (CGS) = 0.1 pascal second (0.1 Pa·s) named after Jean-Louis-Marie Poiseuille

// UM_viscosity_kinematic         (nat8) 0x5F
// Although kinematic viscosity is a composed unit of measure, it is given its own measure
// because it is a commonly used unit and there are special named units derived
#define UC_m2_per_sec_kinematic_viscosity    (nat16)0x5F00
#define UC_stock                             (nat16)0x5F44
// stock St  (CGS) kinematic viscosity = 10^-4 square meters per second

// UM_electrical_current         (nat8) 0x70
// or UM_magnetomotive_force UM_electrical_current
// I think magnetomotive force is the same as current since it's measure in amphere
#define UC_ampere_current               (nat16)0x7000
// ampere  (abbr: A)unit for measuring amount of electrical current  (C/s)  named after  André-Marie Ampère
// could be a composite code, but it is fairly common so we give it its on code
#define UC_biot                         (nat16)0x7001
// biot (abbr: Bi)  Jean Baptiste Biot (CGS) electric current = 10 A

// UM_electric_charge            (nat8) 0x71
#define UC_faraday_charge               (nat16)0x7100
// faraday  (abbr: Fd) Michael Faraday  electric charge the charge of a mole of electrons

// UM_electric_potential         (nat8) 0x73
// UM_voltage                        UM_electric_potential
// UM_electric_potential_difference  UM_electric_potential
#define UC_volt_electric_potential       (nat16)0x7300
#define UC_volt                          (nat16)0x7300
// volt (abbr: V) unit of electrical potential difference and electromotive force W/A  watt/amphere  Alessandro Volta
// although this is a composite unit (J/s)
// volt is also widely used as a base units so  we give it a separate measure

// 040715 depricated because volt is electic potential
// UM_electromotive_force_Depricated        (nat8) 0x74
#define UC_volt_electromotive_force_Depricated      (nat16)0x7400

// UM_electric_capacitance       (nat8) 0x75
#define UC_farad                         (nat16)0x7500
// farad (abbr: F) unit measuring electrical capacitance (A·s/V) named after Michael Faraday
// because this is a complex composite unit, we give it its own units code

// UM_electric_resistance         (nat8) 0x76
#define UC_ohm                           (nat16)0x7600
// ohm  unit of electrical resistance of circuits. named after George Simon Ohm

// UM_electric_conductance        (nat8) 0x77
#define UC_siemens                       (nat16)0x7700
#define UC_decisiemens                   (nat16)0x7741
#define UC_millisiemens                  (nat16)0x7743
#define UC_mho                           (nat16)0x7700
#define UC_millimho                      (nat16)0x7743
// siemens  unit of electrical conductance equivalent to one ampere per volt
// Although this is A/V, these units are used also for salinity so we give it its own measure.
// It is also a complex SI unit based on several subunits.
// siemens S  named after Ernst Werner von Siemens electric conductance  W-1

// The siemens (symbolized S) is the Standard International (SI) unit of electrical conductance.
// The archaic term for this unit is the mho (ohm spelled backwards).
// Siemens are also used, when multiplied by imaginary numbers,
// to denote susceptance in alternating current (AC) and radio frequency (RF) applications.
// Reduced to base SI units, 1 S is the equivalent of one second cubed ampere squared per kilogram per meter squared (1 s3 · A2 · kg-1 · m-2).
// The siemens is also the equivalent of an ampere per volt (A/V).

// UM_electric_inductance        (nat8) 0x78
#define UC_henry                         (nat16) 0x7800
// henry (H)  Joseph Henry  unit of electrical inductance V·s/A
// This is a complex composed unit so we give it its own unit of measure

// UM_magnetic_flux              (nat8) 0x79
#define UC_maxwell                       (nat16)0x7900
// maxwell  (abbr: Mx or M) unit of magnetic flux  ( 10e-8 Wb) named after James Clerk Maxwell
#define UC_line  UC_maxwell
// I think 1 line = 1 maxwell
#define UC_weber                         (nat16)0x7908
// weber (abbr: Wb) unit of magnetic flux  V·s  (volt time second) equal to 100 million maxwells. named after Wilhelm Eduard Weber

// UM_magnetic_flux_density      (nat8) 0x7A
// intensive?
#define UC_tesla                        (nat16)0x7A00
// tesla (abbr: T) unit of magnetic flux density equal to one weber per square meter kg/A·s2. named after Nicola Tesla
// Could be U_a_per_b(UC_weber,UC_square_meter_surface_area)
// but because this is a base unit for magentic flux density, we assign its own measure
#define UC_gauss                        (nat16)0x7A44
// gauss  (abbr; G) unit of magnetic flux density equal to 1/10000 tesla
// named after Carl Friedrich Gauss  magnetic induction  10e-4 T
#define UC_gamma                        (nat16)0x7A49
// gamma  unit of magnetic flux density equal to one nanotesla

// Perhaps add  magnetic dipole moment emu in the CGS system

// UM_radionuclide_activity      (nat8) 0x7D
#define UC_becquerel                     (nat16)0x7D00

// UM_absorbed_dose              (nat8) 0x7E
#define UC_gray                          (nat16)0x7E00

// UM_dose_equivalent            (nat8) 0x7F
#define UC_sievert                        (nat16)0x7F00
// Note that a sievert (Sv) is J/kg dose equivalent of radiation
// sievert Sv  R. M. Sievert  dose equivalent of radiation  J/kg

// NYI roentgen R William Conrad Röntgen radiation exposure  2.58e4 A·s/kg
// NYI roentgen  unit of x-radiation or gamma radiation

// > Do not delete this line, it is used by the units code constant generator

#define UC_Celcius_degree_days            U_a_b(UC_Celcius,UT_day)
#define UC_Celcius_degree_hours           U_a_b(UC_Celcius,UT_hour)
#define UC_cm_per_second                  U_a_per_b(UC_cm,UT_second)
#define UC_cm_per_hour                    U_a_per_b(UC_cm,UT_hour)

#define UC_second_per_meter               U_a_per_b(UT_second,UC_meter)
#define UC_day_per_meter                  U_a_per_b(UT_day,UC_meter)
// used for aerodynamic resistance 110910

#define UC_meters_per_second              U_a_per_b(UC_meter,UT_second)
#define UC_meters_per_day                 U_a_per_b(UC_meter,UT_day)
#define UC_m_per_day                      U_a_per_b(UC_meter,UT_day)
#define UC_mm_per_day                     U_a_per_b(UC_mm,UT_day)
#define UC_mm_per_second                  U_a_per_b(UC_mm,UT_second)
#define UC_micrometer_per_second          U_a_per_b(UC_micro_meter,UT_second)
#define UC_kilometers_per_day             U_a_per_b(UC_km,UT_day)
#define UC_kilometers_per_hour            U_a_per_b(UC_km,UT_hour)

#define UC_m2_per_kg                      U_a_per_b(UC_square_meter_area,UC_kg_mass)
#define UC_km_per_kg                      U_a_per_b(UC_km,UC_kg_mass)

// These are used for miniscule concentration
// these fit within the metric system
// Parts per million is milligrams / kilogram of mass
#define UC_parts_per_hundred              U_a_per_b(UC_dg_mass,UC_kg_mass)
#define UC_parts_per_thousand             U_a_per_b(UC_gram_mass,UC_kg_mass)
#define UC_parts_per_million              U_a_per_b(UC_mg_mass,UC_kg_mass)
#define UC_ppm                            U_a_per_b(UC_mg_mass,UC_kg_mass)
#define UC_parts_per_billion              U_a_per_b(UC_microgram_mass,UC_kg_mass)
#define UC_parts_per_trillion             U_a_per_b(UC_nanogram_mass,UC_kg_mass)

// UC_newton_meter_torque           U_a_b(UC_newton_force,UC_meter_radial)
// Need to disabiguate with Joule

// The trailing understore in the following units is temporary so I make sure I have
// used the correct units everywhere.
// Note that solar radiation is measured (accumulation?) for the time step
// In CropSyst and ClimGen the time step is implicit in the file storage so generally
// so time step is not specified.

// Any units of mass per time squared  represent either:
// elasticity,
// intensity of force
// interfacial tension
// specific impact entery
// surface pressure
// surface tension
// tension

// Composite units of measure
// specific volume per mass I.e. m3/kg
// density  mass per volume I.e. kg/m3 (extensive)
// entropy I.e. J/K  (extensive)

// (radient heat per square meter surface area)
#define UC_MJ_per_m2                      U_a_per_b(UC_mega_joule_energy,UC_square_meter_area)
#define UC_J_per_m2                       U_a_per_b(UC_joule_energy,UC_square_meter_area)
#define UC_MJ_per_m2_solar_radiation      UC_MJ_m2
// These are measures of irradiance not radiation!
// Note that solar radiation is MJ/(m2.day) but the day is implicit in the time step.

#define UC_MJ_per_kg                      U_a_per_b(UC_mega_joule_energy,UC_kg_mass)

#define UC_kg_per_MJ                      U_a_per_b(UC_kg_mass,UC_mega_joule_energy)
#define UC_g_per_MJ                       U_a_per_b(UC_gram_mass,UC_mega_joule_energy)
#define UC_kJ_per_mole                    U_a_per_b(UC_kilo_joule_energy,UC_mole)
#define UC_watt_day_per_m2                U_a_per_b(UC_watt_day,UC_square_meter_area)
// Not sure where I needed Watt-day/m2
#define UC_watt_hour_per_m2             U_a_per_b(UC_watt_hour,UC_square_meter_area)
#define UC_watt_second_per_m2             U_a_per_b(UC_watt_second,UC_square_meter_area)

#define UC_kg_per_kg                      U_a_per_b(UC_kg_mass,UC_kg_mass)
#define UC_kg_per_ha                      U_a_per_b(UC_kg_mass,UC_hectare)
#define UC_kg_per_m2                      U_a_per_b(UC_kg_mass,UC_square_meter_area)
#define UC_kg_per_m3                      U_a_per_b(UC_kg_mass,UC_cubic_meter_volume)
#define UC_tn_per_ha                      U_a_per_b(UC_tonne_mass,UC_hectare)
#define UC_ml_per_g                       U_a_per_b(UC_ml,UC_g)
#define UC_m3_per_m3                      U_a_per_b(UC_cubic_meter_volume,UC_cubic_meter_volume)
#define UC_cm3_per_cm3                    U_a_per_b(UC_cubic_cm_volume,UC_cubic_cm_volume)
// Should actually create a new units Volumetric  for soil

#define UC_g_per_cm                      U_a_per_b(UC_gram_mass,UC_cm)
#define UC_g_per_cm3                      U_a_per_b(UC_gram_mass,UC_cubic_cm_volume)
#define UC_cmole_per_kg                   U_a_per_b(UC_cmole,UC_kg_mass)
// used for cation exchange capacity
#define UC_mmole_per_kg                   U_a_per_b(UC_mmole,UC_kg_mass)

// Concentrations
#define UC_m2_per_m2                      U_a_per_b(UC_square_meter_area,UC_square_meter_area)
#define UC_kg_solid_per_kg_liquid         U_a_per_b(UC_kg_mass,UC_kg_mass)
#define UC_kg_per_kg                      U_a_per_b(UC_kg_mass,UC_kg_mass)
#define UC_g_per_kg                       U_a_per_b(UC_g_mass,UC_kg_mass)
#define UC_mg_per_kg                      U_a_per_b(UC_mg_mass,UC_kg_mass)
#define UC_g_per_unit                     U_a_per_p(UC_g_mass,UC_unit)

#define UC_J_per_kg                       U_a_per_b(UC_joule_energy, UC_kg_mass)
// (when not a Gray)

#define UC_mEq_per_100g                   U_a_per_b(UC_mEq, UC_hg_mass)
// I think milliequivelent per 100 gram is the same as milliequivelent per hecto gram

#define UC_liter_per_minute               U_a_per_b(UC_liter,UT_minute)
#define UC_liter_per_hour                 U_a_per_b(UC_liter,UT_hour)
#define UC_kg_per_day                     U_a_per_b(UC_kg_mass,UT_day)
#define UC_m3_per_minute                  U_a_per_b(UC_cubic_meter_volume,UT_minute)
#define UC_m3_per_hour                    U_a_per_b(UC_cubic_meter_volume,UT_hour)
#define UC_count_per_day                  U_a_per_b(UC_count,UT_hour)
#define UC_count_per_m2                   U_a_per_b(UC_count,UC_square_meter_area)
#define UC_dS_per_m                       U_a_per_b(UC_decisiemens,UC_meter)
#define UC_mS_per_cm                      U_a_per_b(UC_millisiemens,UC_cm)

#define UC_coulumb                        U_a_b(UC_ampere_current,UT_second)
// coulomb (abbr: C)  unit of electrical chargeof one ampere over period of one second ( A·s) named after Charles-Augustin de Coulomb
#define UC_planck                         U_a_b(UC_joule_energy,UT_second)
// (abbr J·s)  - Max K. E. L. Planck action

// Luminance:
#define UC_luminance_c_per_m2             (nat16)U_a_per_b(UC_candela,UC_square_cm_area)
// Luminance (brightness) in a given direction = luminous intensity emitted per unit area per steradian of solid angle of the receiver = candles/cm²
#define UC_lambert                        (nat16)U_a_per_b(UC_candela,UC_square_cm_area)
#define UC_meter_lambert                  (nat16)U_a_per_b(UC_candela,UC_square_m_area)
#define UC_nit UC_meter_lambert
// lambert (abrevlam Johann Heinrich Lambert luminance lumen/cm2
// is  brightness of a perfectly diffused surface emitting or scattering 1 lumen/cm²
// candles/cm² = Lambert
// candles/m² = meter-Lambert = nit
// candles/ft² = foot-Lambert

// Entropy units:
#define UC_J_per_K_entropy                U_a_per_b(UC_joule_energy,UC_kelvin)
//extensive

#define UC_watt_power                     U_a_per_b(UC_joule_energy,UT_second)
// energy per time
// A watt is J/sec (abbr: W) unit of power equal to one joule per second named after James Watt

#define UC_watt_per_m2_flux_density       U_a_per_b(UC_watt_radiant_flux,UC_square_m_area)
// W/m2

#define UC_W_per_steradian_radiant_intensity U_a_per_b(UC_watt_power,UC_steradian)
// radient intensity

#define UC_oersted                        U_a_per_b(UC_maxwell,UC_cm)
// oersted  (abbr: Oe)  H. C. Oersted  magnetic field strength in the CGS system  = maxwell/cm
// note that magnetic field strength used by ASAE is volt per meter (MKS)
#define UC_volt_per_meter                 U_a_per_b(UC_volt,UC_m)

#define UC_kPa_per_C                      U_a_per_b(UC_kPa,UC_Celcius)

/*
X = implemented
bar  unit of pressure of one million dynes per square centimeter
galileo (gal)  unit of acceleration of one centimeter per second per second
gilbert  unit of magnetomotive force
carat  unit of weight of precious stones equal to 200 milligrams

chain  unit of length equal to 20 metres
curie  unit of radioactive decay and intensity
dalton  unit of atomic mass
darcy  unit of permeability of rock to various substances  = 0.98692x10^-12 square meter
decibel  unit for measuring sound intensity
dioptre  unit of measurement of power of lens or eye
dol  unit for measuring intensity of pain
dyne  unit of force to accelerate 1 gram to 1 cm per second per second
baud  unit of data transmission speed of one bit per second
bel  unit of noise intensity equal to ten decibels
yrneh  unit of reciprocal inductance
 */

 /*
refractive index (intensive)
 */

#endif

