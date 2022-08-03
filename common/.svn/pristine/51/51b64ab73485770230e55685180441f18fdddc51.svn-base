#ifndef USDA_textureH
#define USDA_textureH
#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif
//______________________________________________________________________________
namespace USDA_texture
{
/*
   I don't know the official source of these codes.
   I have gleaned almost all of these from the STATSGO database documentation.

   It would appear that some of the texture codes are qualifiers identifying the gravel quality of the soil.
   I have not been able to determine if such codes are strickly qualifiers or if they can also
   be used by themselves as a distinct texture
   I have not encountered more than one qualfier

   It appears that texture descriptions that are adjectives are all modifiers
   I.e. with the following adjective suffixes:

   -ceous
   -y
   -ly
   -ery
   -nous
   -gy
   -ky
   -ic
   -al


   Some combinations (I.e. gravely sand loam).
   We will likely be separating 'fine earth' from gravel/stone,
   so we should provide a function that identifies the constituents of the
   soil descriptive code

   Anything with sand/clay/loam/silt is a fine earth texture that may be qualified.

   bedrock types are interpreted as a complete texture at the same level as sand/clay/loam/silt types.
*/
//______________________________________________________________________________
enum Texture_code
{ /*UNK    -*/  unknown
, /*APUM   Q*/  ashy_pumiceous
, /*ASHY   Q*/  ashy
, /*ASK    Q*/  ashy_skeletal
, /*BM     Q*/  bouldery_mucky
, /*BVM    Q*/  very_bouldery_mucky
, /*BXM    Q*/  extremely_bouldery_mucky
, /*BY     Q*/  bouldery
, /*BYV    Q*/  very_bouldery
, /*BYX    Q*/  extremely_bouldery
, /*C      T*/  clay
, /*CAM    Q*/  angular_cobbly_mucky
, /*CB     Q*/  cobbly
, /*CBA    Q*/  angular_cobbly
, /*CBV    Q*/  very_cobbly
, /*CBX    Q*/  extremely_cobbly
, /*CE     Q*/  coprogenous_earth
, /*CEM    Q*/  cemented
, /*CIND   Q*/  cinders
, /*CL     T*/  clay_loam
, /*CM     Q*/  cobbly_mucky
, /*CN     Q*/  channery
, /*CNDY   Q*/  cindery
, /*CNV    Q*/  very_channery
, /*CNX    Q*/  extremely_channery
, /*COS    T*/  coarse_sand
, /*COSL   T*/  coarse_sandy_loam
, /*CR     Q*/  cherty
, /*CRC    Q*/  coarse_cherty
, /*CRV    Q*/  very_cherty
, /*CRX    Q*/  extremely_cherty
, /*CVM    Q*/  very_cobbly_mucky
, /*CXM    Q*/  extremely_cobbly_mucky
, /*DE     Q*/  diatomaceous_earth
, /*FB     Q*/  fibric_material
, /*FL     Q*/  flaggy
, /*FLV    Q*/  very_flaggy
, /*FLX    Q*/  extremely_flaggy
, /*FRAG   Q*/  fragmental_material
, /*FS     T*/  fine_sand
, /*FSL    T*/  fine_sandy_loam
, /*G      Q*/  gravel
, /*GCM    Q*/  coarse_gravelly_mucky
, /*GFM    Q*/  fine_gravelly_mucky
, /*GM     Q*/  gravelly_mucky
, /*GR     Q*/  gravelly
, /*GRC    Q*/  coarse_gravelly
, /*GRF    Q*/  fine_gravelly
, /*GRV    Q*/  very_gravelly
, /*GRX    Q*/  extremely_gravelly
, /*GSL    T*/  gravelly_sand_loam
, /*GVM    Q*/  very_gravelly_mucky
, /*GXM    Q*/  extremely_gravelly_mucky
, /*GYP    Q*/  gypsiferous_material
, /*HM     Q*/  hemic_material
, /*HPUM   Q*/  hydrous_pumiceous
, /*HSK    Q*/  hydrous_skeletal
, /*HYDR   Q*/  hydrous
, /*ICE    Q*/  ice_or_frozen_soil
, /*IND    Q*/  indurated
, /*L      T*/  loam
, /*LCOS   T*/  loamy_coarse_sand
, /*LFS    T*/  loamy_fine_sand
, /*LS     T*/  loamy_sand
, /*LVFS   T*/  loamy_very_fine_sand
, /*MARL   ?*/  marl
, /*MEDL   Q*/  medial
, /*MK     Q*/  mucky
, /*MPT    ?*/  mucky_peat
, /*MPUM   Q*/  medial_pumiceous
, /*MSK    Q*/  medial_skeletal
, /*MUCK   ?*/  muck
, /*PEAT   ?*/  peat
, /*PT     Q*/  peaty
, /*PUM    Q*/  pumiceous
, /*RB     Q*/  rubbly
, /*S      T*/  sand
, /*SC     T*/  sandy_clay
, /*SCL    T*/  sandy_clay_loam
, /*SG     T*/  sand_and_gravel
, /*SH     Q*/  shaly
, /*SHV    Q*/  very_shaly
, /*SHX    Q*/  extremely_shaly
, /*SI     T*/  silt
, /*SIC    T*/  silty_clay
, /*SICL   T*/  silty_clay_loam
, /*SIL    T*/  silt_loam
, /*SL     T*/  sandy_loam
, /*SM     Q*/  stony_mucky
, /*SP     Q*/  sapric_material
, /*SR     Q*/  stratified
, /*ST     Q*/  stony
, /*STL     */  stony_loam
, /*STV    Q*/  very_stony
, /*STX    Q*/  extremely_stony
, /*SVM    Q*/  very_stony_mucky
, /*SXM    Q*/  extremely_stony_mucky
, /*SY     Q*/  slaty
, /*SYV    Q*/  very_slaty
, /*SYX    Q*/  extremely_slaty
// moved to first , /*UNK    -*/  unknown
, /*UWB    T*/  unweathered_bedrock
, /*VAR    -*/  variable
, /*VCOS   T*/  very_coarse_sand
, /*VFS    T*/  very_fine_sand
, /*VFSL   T*/  very_fine_sandy_loam
, /*WB     T*/  weathered_bedrock
, END // mark the end of the list
, IRRELEVENT
};

extern Label_description texture_code_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(Texture_code_labeled,Texture_code,texture_code_label_table);
//______________________________________________________________________________
#ifdef NYI
/*
 In the U.S. the soil texture is classified based on the U.S.D.A. system.
 The classification of particle sizes are the following (units: mm):

clay: < 0.002
silt: 0.002 - 0.05
fine sand: 0.05 - 0.1
medium sand: 0.1 - 0.5
coarse sand: 0.5 - 1.0
very coarse sand: 1.0 - 2.0
Rock fragments: 2.0 - 762.0


(http://www.cartage.org.lb/en/themes/sciences/earthscience/Geology/Soils/SoilMorphology/SoilMorphology/SoilTexture/SoilTexture.htm)

Particles greater than 2 mm are removed from a textural soil classification.
RLN: In this code, these are refered to fine earth textures.
The presence of larger particles (rock fragments)
 is recognized by the use of modifiers added to the textural class

*/

// RLN The ordering of these enumeration is of my own devising
// I am not aware of any actual USDA code enumeration.
// The codes (displayed as adjectives or adverbs are actual USDA terms.

// Code flags
                              // xxxQORLT
#define texture             = 0x01  // xxxxxxx1
#define texture_like        = 0x02  // xxxxxxlx
#define rock                = 0x04  // xxxxx1xx
#define other               = 0x08  // xxxx1xxx
#define qualifier           = 0x10  // xxx1xxxx

#define basic_texture      (texture)
#define qualfied_texture   (texture | qualifier)
#define qualfied_rocky     (rock    | qualifier)
#define qualified_other    (other   | qualifier)

enum Modifier_code
{  not_modified        // Normal
,  un                   // I.e. unweathered
,  minimally           // Not currently used for USED CODES
,  moderately
,  very
,  extremely
};
//______________________________________________________________________________
enum Coarseness_code
{ unspecified_coarseness
, fine_coarseness
, medium_coarseness
, coarse_coarseness
};
//______________________________________________________________________________
enum Texture_range
{ no_range
, clayey  // actually show and clay
, silty
, loamy
, sandy
};
//______________________________________________________________________________
enum Rock_shape_code
{ not_rocky // not a rock
, spherical // or cubelike
, flat
};
//______________________________________________________________________________
// RLN: USDA_organic_soil_code is my own coding system not an actual USDA code
// but these terms appear in the USDA soil descriptions.
// see also file:///C:/Documents%20and%20Settings/rnelson/My%20Documents/Downloads/stolt2.pdf
enum Organic_soil_code   // modifier
{ not_organic // not considered organic
, fibric // muck
, hemic  // mucky-peat
, sapric // peat
/*150904
//, peaty
//, peat
//, mucky_peat
, mucky
*/
/*
National Indicators of Hydric Soils
• Sapric-muck, hemic-mucky peat, fibric-peat
used interchangeably
*/

};
//______________________________________________________________________________
enum Other_soil_code
{  no_other
,  angular
,  hydrous
,  weathered
};
//______________________________________________________________________________
// RLN: the USDA_pedogenis code is entirely of my own devising.
// But the terms do appear in the USDA soil descriptions.
enum Pedogenis_code
{ unspecified_pedogenis
, bedrock
, cherty
, shaly
, slaty
, pumiceous     // from pumic
, cindery       // ?from burned organic material?
, diatomaceous  // from diatomes
, coprogenous   // from fecal matter
, gypsiferous   // from gypsum
, skeletal      // from skeletal remain (endo and exto?)
};
//______________________________________________________________________________
// Denotation indicates if the respective keyword appears at the end of the term
enum Denotation
{ undenoted
, earth
, material
};
//______________________________________________________________________________
/*

The distinction between a mineral and an organic horizon is made by the organic carbon content.
Layers which contain > 20 % organic carbon and are not water saturated for periods more than a few days are classed as organic soil material.
If a layer is saturated for a longer period it is considered to be organic soil material if it has:

= 12 % organic carbon and no clay, or
= 18 % organic carbon and >= 60 % clay, or
12 - 18 % organic carbon and 0 - 60 % clay.

Information provided by: http://www.soils.wisc.edu

*/

080428 I am still in the process of coding these specifications
this is not critical, just for completness

struct Texture_specification
{  Texture_code         texture;       // The full texture code

// eventually I will add here a bit field for code flags
// so I can identify if the texture code is a basic texture,
// some sort of qualifier,
// a 'composite' texture, or other.

   Modifier_code        modifier;
   Other_code           other;
   Coarseness_code      courseness;
   Texture_range        range;
   Texture_code         particle_size; // I.e. for rock fragments
   Rock_shape_code      rock_shape;    // Indicates it is a rock
   Organic_soil_code    organic_soil;
   Pedogenis_code       pedogenis;
   Texture_code         second_texture;
   bool                 earth_denotation;
//NYI bool              impermiable
};
extern struct Texture_specification texture_specification [];
//______________________________________________________________________________
#endif

}; //  namespace USDA texture
#endif

