//---------------------------------------------------------------------------
#ifndef domainsH
#define domainsH

#include <string>
#include "corn/labeled_enum.h"
//---------------------------------------------------------------------------
namespace USDA_NRCS
{

/* I dont currently have all domains in enumerations.
   Most domains are simply fixed sets of names and wouldn't need
   or dont have enumeration codes
   Where domains that dont have or dont need to be enumeration,
   the value is simply stored as a string.
*/

typedef std::string  Aashto_group_classification;
typedef std::string  Algorithm;
typedef std::string  Attributetype;
//______________________________________________________________________________
enum Capability_class
{  capability_class_unknown
,  capability_class_I      //  Soils in Class I have few limitations that  restrict their use.
,  capability_class_II     //  Soils in Class II have some limitations that reduce the choice of plants or require moderate conservation practices.
,  capability_class_III    //  Soils in Class III have severe limitations that reduce the choice of plants or require special conservation practices, or both.
,  capability_class_IV     //  Soils in Class IV have very severe limitations that restrict the choice of plants, require very careful management, or both.
,  capability_class_V      //  Soils in Class V have little or no erosion hazard but have other limitations impractical remove that limit their use.
,  capability_class_VI     //  Soils in Class VI have severe limitations that make them generally unsuited to cultivation and limit their use largely to pasture, etc.
,  capability_class_VII    //  Soils in Class VII have very severe limitations that make them unsuited to cultivation and that restrict their use to grazing, etc.
,  capability_class_VIII   //  Soils (and landforms) in Class VIII have limitations that preclude their use for commercial plant production and restrict their use.
};
extern Label_description capability_class_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(Capability_class_labeled,Capability_class,capability_class_label_table);
//______________________________________________________________________________
enum Capability_subclass
{ capability_subclass_unassigned  // capacility class I and often VIII are not assigned subclass codes
// The following codes are the canonical NRCS codes used in soil surface
, capability_subclass_erosion
, capability_subclass_water
, capability_subclass_soil
, capability_subclass_climate
// The following codes are extensions used by the canadian land survey (1999)
// (ref: http://sis.agr.gc.ca/cansis/nsdb/cli/classdesc.html
//  contact: Peter Schut, http://sis.agr.gc.ca.cansis/org/schut.html)
//  Also: http://www.alc.gov.bc.ca/alr/ag_capability.htm
, capability_subclass_soil_structure
, capability_subclass_fertility
, capability_subclass_inundation
, capability_subclass_moisture
, capability_subclass_salinity
, capability_subclass_stoniness
, capability_subclass_bedrock
, capability_subclass_combination
, capability_subclass_topography
, capability_subclass_cumulative
};
extern Label_description capability_subclass_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(Capability_subclass_labeled,Capability_subclass,capability_subclass_label_table);
//110211 warning, labels need to base case insenstivie
//______________________________________________________________________________
typedef std::string  Cardinality;
typedef std::string  Chorizon_text_kind;
//_____________________________________________________________________________
enum Component_kind
{  miscellaneous_area //(M)
,  series //(S)
,  family //(F)
,  variant //(V)   obsolete
,  taxadjunct //(T)
,  taxon_above_family //(G)
}; // In STATSGO2 the enumeration codes are spelled out.
extern Label_description component_kind_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(Component_kind_labeled,Component_kind,component_kind_label_table);
//_____________________________________________________________________________

//_____________________________________________________________________________
typedef std::string  Component_text_kind
; /* = 
Length of Longest Choice Value: 24
1 No Edit notes Text entries that describe what changes were made to the component object, exclusive of the horizon object, and why those changes were made.
2 No Correlation notes Text entries that document correlation concerns that affect this component. For example, notes about the comparison of this component to the
official series for which it is named.
3 No SOI5 description The SOI-5 description converted from SSSD.
4 No Miscellaneous notes Text entries not related to any of the other choices.
5 obsolete_Nontechnical description
6 obsolete_Certification notes Indicates records that contain notes related to certification of data objects. Typically, data elements certified in the object are listed in the text
attached to this record.
SSURGO Version: 2.2.3 Page 3
*/ //_____________________________________________________________________________


typedef std::string  conservation_tree_shrub_group
; /* = 
Length of Longest Choice Value: 14
1 No 1
2 No 1A
3 No 1H
4 No 1K
5 No 1KK
6 No 1S
7 No 1SK
8 No 1SKK
9 No 2
10 No 2A
11 No 2H
12 No 2K
13 No 2KK
14 No 3
15 No 3A
16 No 4
17 No 4A
18 No 4C
19 No 4CA
20 No 4CC
21 No 4CK
22 No 4K
23 No 5
24 No 5A
25 No 5K
26 No 5KK
27 No 6
28 No 6A
29 No 6D
30 No 6DA
31 No 6DK
32 No 6G
SSURGO Version: 2.2.3 Page 4
*/ //_____________________________________________________________________________


typedef std::string  conservation_tree_shrub_group
; /* = 
Length of Longest Choice Value: 14
33 No 6GA
34 No 6GK
35 No 6GKK
36 No 6K
37 No 6KK
38 No 7
39 No 7A
40 No 8
41 No 8K
42 No 9C
43 No 9L
44 No 9N
45 No 9NW
46 No 9W
47 No 10
48 No Not applicable
*/
//_____________________________________________________________________________
typedef std::string  corrosion_concrete
; /* = 
Length of Longest Choice Value: 8
1 No Low
2 No Moderate
3 No High
*/
//_____________________________________________________________________________
typedef std::string  corrosion_uncoated_steel
; /* = 
Length of Longest Choice Value: 8
1 No Low
2 No Moderate
3 No High
SSURGO Version: 2.2.3 Page 5
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
1 No African stargrass
2 No Alfalfa hay
3 No Alfalfa pasture
4 No Alfalfa seed
5 No Almonds
6 No Annual ryegrass
7 No Apples
8 No Apricots
9 No Artichokes
10 No Asparagus
11 No Avocados
12 No Bahiagrass
13 No Bahiagrass hay
14 No Bananas
15 No Barley
16 No Barley-fallow
17 No Dry lima beans
18 No Dry pinto beans
19 No Dry beans
20 No Snap beans
21 No Unshelled lima beans
22 No Beets
23 No Bentgrass seed
24 No Bermudagrass-clover hay
25 No Bermudagrass-fescue hay
26 No Big bluestem
27 No Blackberries
28 No Blueberries
29 No Bluegrass
30 No Bluegrass seed
31 No Bluegrass-ladino
32 No Bluegrass-ladino hay
SSURGO Version: 2.2.3 Page 6
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
33 No Bluegrass-trefoil
34 No Bluegrass-trefoil hay
35 No Bluegrass-white clover
36 No Bluegrass-white clover hay
37 No Breadfruit
38 No Broccoli
39 No Bromegrass hay
40 No Bromegrass-alfalfa
41 No Bromegrass-alfalfa hay
42 No Bromegrass-alsike
43 No Bromegrass-alsike hay
44 No Bromegrass-ladino
45 No Broomcorn
46 No Brussel sprouts
47 No Buckwheat
48 No Buffel grass
49 No Cabbage
50 No Chinese cabbage
51 No Mustard cabbage
52 No Canarygrass hay
53 No Canarygrass-alsike
54 No Canarygrass-alsike hay
55 No Canarygrass-ladino
56 No Canarygrass-ladino hay
57 No Spring canola
58 No Winter canola
59 No Cantaloupe
60 No Carrots
61 No Cassava
62 No Caucasian bluestem
63 No Caucasian bluestem hay
64 No Cauliflower
SSURGO Version: 2.2.3 Page 7
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
65 obsolete_Causian bluegrass
66 No Celery
67 No Cherries
68 No Clover seed
69 No Coconuts
70 No Coffee
71 No Common bermudagrass
72 No Common bermudagrass hay
73 No Common ryegrass seed
74 No Cool-season grasses
75 No Corn
76 No Corn silage
77 No Sweet corn
78 No Cotton lint
79 No Pima cotton lint
80 No Cowpeas
81 No Cranberries
82 No Crested wheatgrass
83 Crested wheatgrass-alfalfa
hay
No
84 No Crimson clover
85 No Cucumbers
86 No Fescue
87 No Filberts
88 No Fine fescue seed
89 No Flax
90 No Garlic
91 No Garrisongrass
92 No Grain sorghum
93 No Grapefruit
94 No Table grapes
95 No Wine grapes
96 No Grass hay
SSURGO Version: 2.2.3 Page 8
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
97 No Grass silage
98 No Grass seed
99 No Grass-clover
100 No Grass-legume hay
101 No Grass-legume pasture
102 No Green chop
103 No Green needlegrass
104 No Guinea grass
105 No Annual hay crop
106 No Hops
107 No Improved bermudagrass
108 No Improved bermudagrass hay
109 No Indiangrass
110 No Introduced bluestem
111 No Johnsongrass
112 No Kentucky bluegrass
113 No Kincaid red clover
114 No Kleingrass
115 No Kobe lespedeza
116 No Ladino clover
117 No Legume hay
118 No Lemons
119 No Dry lentils
120 No Lettuce
121 No Limes
122 No Loganberries
123 No Macadamia nuts
124 No Mangos
125 No Merkergrass
126 No Millet
127 No Distillate mint
128 No Molassesgrass
SSURGO Version: 2.2.3 Page 9
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
129 No Mungbeans
130 No Oats
131 No Hay oats
132 No Olives
133 No Onions
134 No Green onions
135 No Oranges
136 No Orchardgrass
137 No Orchardgrass hay
138 No Orchardgrass seed
139 No Orchardgrass-alfalfa
140 No Orchardgrass-alfalfa hay
141 No Orchardgrass-alsike
142 No Orchardgrass-alsike hay
143 No Orchardgrass-ladino
144 No Orchardgrass-ladino hay
145 No Orchardgrass-lespedeza
146 No Orchardgrass-lespedeza hay
147 No Orchardgrass-red clover
148 No Orchardgrass-red clover hay
149 No Orchardgrass-trefoil
150 No Orchardgrass-trefoil hay
151 No Pangolagrass
152 No Papaya
153 No Paragrass
154 No Pasture
155 No Peaches
156 No Peanuts
157 No Pears
158 No Winter pears
159 No Canning peas
160 No Dry peas
SSURGO Version: 2.2.3 Page 10
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
161 No Green peas
162 No Pecans
163 No Black pepper
164 No Peppers
165 No Dry chili peppers
166 No Fresh chili peppers
167 No Green peppers
168 No Perennial ryegrass seed
169 No Improved permanent pasture
170 Unimproved permanent
pasture
No
171 No Pigeonpeas
172 No Pineapple
173 No Ratoon pineapple
174 No Pistachios
175 No Plantains
176 No Plums
177 No Irish potatoes
178 No Prunes
179 No Dry prunes
180 No Pubescent wheatgrass
181 No Pumpkins
182 No Raisins
183 No Raspberries
184 No Red clover hay
185 No Red clover seed
186 No Reed canarygrass
187 No Rice
188 No Rye
189 No Rye grazeout
190 No Safflower
191 No Small grains grazeout
192 No Small grains hay
SSURGO Version: 2.2.3 Page 11
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
193 No Small grains silage
194 No Smooth bromegrass
195 No Sorghum grazed
196 No Sorghum hay
197 No Sorghum silage
198 No Soybeans
199 No Spinach
200 No Summer squash
201 No Winter squash
202 No Strawberries
203 No Strawberry plants
204 No Sugar beets
205 No Sugarcane
206 No 18-month sugarcane
207 No Ratoon sugarcane
208 No Spring sugarcane
209 No Sunflowers
210 No Sweet potatoes
211 No Switchgrass
212 No Tall fescue
213 No Tall fescue hay
214 No Tall fescue seed
215 No Tall fescue-alfalfa
216 No Tall fescue-alfalfa hay
217 No Tall fescue-alsike
218 No Tall fescue-alsike hay
219 No Tall fescue-ladino
220 No Tall fescue-ladino hay
221 No Tall fescue-lespedeza
222 No Tall fescue-lespedeza hay
223 No Tall fescue-red clover
224 No Tall fescue-red clover hay
SSURGO Version: 2.2.3 Page 12
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
225 No Tall wheatgrass
226 No Tangelos
227 No Tangerines
228 No Taniers
229 No Taro
230 No Timothy hay
231 No Timothy-alfalfa
232 No Timothy-alfalfa hay
233 No Timothy-alsike
234 No Timothy-alsike hay
235 No Timothy-red clover
236 No Timothy-red clover hay
237 No Tobacco
238 No Burley tobacco
239 No Dark air-cured tobacco
240 No Fire-cured tobacco
241 No Flue-cured tobacco
242 No Light air-cured tobacco
243 No Tomatoes
244 No Trefoil hay
245 No Trefoil-grass
246 No Trefoil-grass hay
247 No Walnuts
248 No Warm season grasses
249 No Watermelons
250 No Weeping lovegrass
251 No Wheat
252 No Wheat grazeout
253 No Wheat (October-March)
254 No Spring wheat
255 No Spring wheat-fallow
256 No Winter wheat
SSURGO Version: 2.2.3 Page 13
*/ //_____________________________________________________________________________


typedef std::string  crop_name
; /* = 
Length of Longest Choice Value: 30
257 No Winter wheat-fallow
258 No Yams

*/
//_____________________________________________________________________________
typedef std::string  crop_yield_units
; /* = 
Length of Longest Choice Value: 9
1 No Cwt 100 pounds/acre
2 No AUM Animal unit months/acre
3 No Boxes Boxes/acre
4 No Bu Bushels/acre
5 No Crates Crates/acre
6 No Lbs Pounds/acre
7 No Sacks Sacks/acre
8 No Thousands Thousands/acre
9 No Tons Tons/acre

*/
//_____________________________________________________________________________
typedef std::string  depthqualmode
; /* = 
Length of Longest Choice Value: 13
1 No Surface Layer
2 No All Layers
3 No Depth Range

*/
//_____________________________________________________________________________
typedef std::string  depthuom
; /* = 
Length of Longest Choice Value: 11
1 No Centimeters
2 No Inches
SSURGO Version: 2.2.3 Page 14
*/ //_____________________________________________________________________________


typedef std::string  diag_horz_feat_kind
; /* = 
Length of Longest Choice Value: 40
1 No Abrupt textural change
2 No Agric horizon
3 No Albic horizon
4 No Albic material
5 No Andic soil properties
6 No Anhydrous conditions
7 No Anthric saturation
8 No Anthropic epipedon
9 No Aquic conditions
10 No Argillic horizon
11 No Calcic horizon
12 No Cambic horizon
13 No Coprogenous earth
14 No Cryoturbation
15 No Densic contact
16 No Densic materials
17 No Diatomaceous earth
18 No Durinodes
19 No Duripan
20 No Endosaturation
21 No Episaturation
22 No Fibric soil material
23 No Folistic epipedon
24 No Fragic soil properties
25 No Fragipan
26 No Gelic materials
27 obsolete_Gilgai
28 No Glacic layer
29 No Glossic horizon
30 No Gypsic horizon
31 No Gypsum accumulations
32 No Hemic soil material
33 No Histic epipedon
34 No Humilluvic material
35 No Interfingering of albic material
36 No Kandic horizon
37 No Lamellae
38 No Limnic material
39 No Lithic contact
40 No Lithologic discontinuity
41 No Marl
42 No Melanic epipedon
43 No Mollic epipedon
44 obsolete_Mottles with chroma 2 or less
45 No n value > 0.7
46 No Natric horizon
47 No Ochric epipedon
48 No Ortstein
49 No Oxic horizon
50 No Paralithic contact
51 No Paralithic materials
52 No Permafrost
53 No Petrocalcic horizon
54 No Petroferric contact
55 No Petrogypsic horizon
56 No Placic horizon
57 No Plaggen epipedon
58 No Plinthite
59 No Redox concentrations
60 Redox depletions with
chroma 2 or less
No
61 No Reduced matrix
62 No Salic horizon
63 No Salt accumulations
64 No Sapric soil material
65 No Secondary carbonates
66 No Slickensides
67 No Sombric horizon
68 No Spodic horizon
69 Strongly contrasting particle
size class
No
70 No Sulfidic material
71 No Sulfuric horizon
72 No Umbric epipedon
73 No Volcanic glass
*/
//_____________________________________________________________________________

typedef std::string  distribution_status
; /* = 
Length of Longest Choice Value: 20
1 No In progress The distribution request has been submitted but the processing of that request is not complete. The request may be being held for processing at
a later time.
2 No Not successful The distribution request failed to run to completion, and no data was exported.
3 No Partially successful The distribution request was processed to completion, but one or more of the legends, map units or components in the original request was not
found in the database at the time the request was ultimately processed.
4 No Successful The distribution request was processed to completetion, and all requested legends, map units and components are present in the exported
dataset.
*/
//_____________________________________________________________________________

typedef std::string  drainage_class
; /* = 
Length of Longest Choice Value: 28
1 No Excessively drained
2 Somewhat excessively
drained
No
3 No Well drained
4 No Moderately well drained
5 No Somewhat poorly drained
6 No Poorly drained
7 No Very poorly drained
*/
//_____________________________________________________________________________

typedef std::string  earth_cover_kind_level_one
; /* = 
Length of Longest Choice Value: 22
1 No Artificial cover Nonvegetative cover either made or modified by human activity and prohibiting or restricting vegetative growth and water penetration.
2 No Barren land Nonvegetative natural cover often having a limited capacity to support vegetation - including construction sites (<5% vegetated).
3 No Crop cover The full cycle, including land preparation and post-harvest residue cover of annual or perennial herbaceous plants that are cultivated or
harvested, or both, for the production of food, feed, oil, and fiber other than wood, and excluding hay and pasture.
4 No Grass/herbaceous cover Non-woody vegetative cover composed of annual or perennial grasses, grass-like plants (sedges/rushes), forbs (including alfalfa and clovers),
lichens, mosses, and ferns (>75% grass, grass-like, forb cover).
5 obsolete_Other
6 No Shrub cover Vegetative cover composed of multi-stemmed and single-stemmed woody plants that attain a mature height of less than four meters (>50%
shrub canopy cover).
7 No Tree cover Vegetative cover recognized as woody plants which usually have one perennial stem, a definitely formed crown of foliage, and a mature height of
at least four meters (including ornamentals and Christmas trees) (>25% tree canopy cover).
8 No Water cover Earth covered by water in a fluid state. This includes seasonally frozen areas.
9 obsolete_Wetlands
10 obsolete_Wetlands, drained

*/
//_____________________________________________________________________________
typedef std::string  earth_cover_kind_level_two
; /* = 
Length of Longest Choice Value: 33
1 No Row crop e.g. corn, soybeans, cotton, tomatoes and other truck crops, tulips
2 No Close-grown crop Wheat, rice, oats, rye, etc.
3 No Grassland rangeland (<10% trees, <20% shrubs) - includes rangeland used for hayland - bluestems, mixed midgrasses, shortgrass, etc.
4 No Savanna rangeland 10 to 25% tree cover
5 No Shrubby rangeland (20 to 50% shrub cover) - sumac, sagebrush, mesquite
6 No Tundra rangeland
7 No Tame pastureland Fescues, bromegrass, timothy, lespedeza, etc.
8 No Hayland Fescues, bromegrass, timothy, alfalfa, etc.
9 No Marshland grass, grass-like plants
SSURGO Version: 2.2.3 Page 18
*/ //_____________________________________________________________________________


typedef std::string  earth_cover_kind_level_two
; /* = 
Length of Longest Choice Value: 33
10 Other grass/herbaceous
cover
No
11 No Crop trees e.g. apples, pecans, date palms, citrus, ornamental nursery stock, Christmas trees
12 No Conifers Spruce, Douglas fur, pine, etc.
13 No Hardwoods Oak, hickory, elm, aspen, etc.
14 Intermixed conifers and
hardwoods
No e.g. oak-pine mix
15 No Tropical Mangrove, royal palm, etc.
16 No Swamp shrubs and trees
17 No Other tree cover
18 No Crop shrubs Filbert, blueberry, and ornamentals, etc. as nursery stock
19 No Crop vines e.g. grapes, blackberries, raspberries
20 No Native shrubs e.g. creosotebush, shrub live oak, sagebrush, mesquite (including rangeland with >50% shrub cover)
21 No Other shrub cover e.g. kudzu, cacti, yucca
22 No Rock
23 No Sand and gravel
24 No Culturally induced barren saline seeps, mines, quarries, oil-waste, etc.
25 No Permanent snow and ice
26 No Other barren salt flats, slickspots, mud flats, badlands, etc.; excludes those in culturally induced earth cover
27 No Rural transportation Highways, railroads, etc.
28 No Urban and built-up Cities, towns, farmsteads, industrial sites

*/
//_____________________________________________________________________________
typedef std::string  erosion_accelerated_kind
; /* = 
Length of Longest Choice Value: 35
1 Highly deforming landslip
erosion
Yes
2 Slightly deforming landslip
erosion
Yes
3 obsolete_Water erosion Soil removal by running water.
4 No Gully erosion Gully erosion is the consequence of water that cuts down into the soil along the line of water concentration and flow. The resulting channels
cannot be obliterated by ordinary tillage operations. (SSM)
5 No Rill erosion Rill erosion is the removal of soil through the cutting of many small, but conspicuous channels where runoff concentrates. The channels are
shallow enough that they can be obliterated with normal tillage operations. (SSM)
6 No Sheet erosion The more or less uniform removal of soil from an area without the development of conspicuous water channels. (SSM)
7 No Tunnel erosion The removal of soil by the formation of subsurface tunnels (often referred to as piping). Free water enters the soil through macropores such as
large desication cracks or rodent burrows. The tunnels tend to enlarge and coelesce.
8 obsolete_Wind and water erosion
9 No Wind erosion Deflation by wind.

*/
//_____________________________________________________________________________
typedef std::string  erosion_class
; /* = 
Length of Longest Choice Value: 17
1 No None - deposition No apparent erosion has occurred. Deposition of soil sediment removed from other areas may have occurred.
2 No Class 1 The soil has lost on the average <25% of the original A and/or E horizons, or of the uppermost 20 cm if the original A and/or E horizons were less
than 20 cm thick. (SSM)
3 No Class 2 The soil has lost, on the average, 25 to 75 percent of the original A and/or E horizons, or of the uppermost 20 cm if the original A and/or E
horizons were less than 20 cm thick.
4 No Class 3 The soil has lost, on the average, more than 75 percent of the original A and/or E horizon, or of the uppermost 20 cm if the original A and/or E
horizons were less than 20 cm thick. (SSM)
5 No Class 4 The soil has lost all of the original A and/or E horizons, or the uppermost 20 cm if the original A and/or E horizons were less than 20 cm thick.
Some of the orginal underlying material may have also been removed. (SSM)

*/
//_____________________________________________________________________________
typedef std::string  excavation_difficulty_class
; /* = 
Length of Longest Choice Value: 14
1 No Low Excavations can be made with a spade using arm-applied pressure only. Neither application of impact energy nor application of foot pressure is
necessary.
2 No Moderate Excavation can be accomplished quite easily by application of impact energy with a spade or by foot applied pressure.
3 No High Excavation with a spade can be accomplished with difficulty. Excavation is easily possible with a full length pick, using an over-the-head swing.
4 No Very high Excavation with a full length pick using an over-the-head swing is moderately to markedly difficult. Excavation is possible in a reasonable period
of time with a backhoe mounted on a 40 to 60 kW (50-80 hp) tractor.
5 No Extremely high Excavation cannot be accomplished in a resonable time period with a backhoe mounted on a 40 to 60 kW (50-80 hp) tractor.
SSURGO Version: 2.2.3 Page 20
*/ //_____________________________________________________________________________


//_____________________________________________________________________________
typedef std::string  export_certification_status
; /* = 
Length of Longest Choice Value: 16
1 No not certified The legend and data mapunits to be included in the export file have been appropriately populated, at least in part, but have not been reviewed or
certified. These are advance data, subject to change.
This certification applies to the whole export package as a single entity.
2 No partly certified The legend and data mapunits to be included in the export file have been appropriately populated and the data have been reviewed. At least
some of the data elements have been certified for use in specific applications. Other data elements in the export have advance data, subject to
change.
This certification applies to the whole export package as a single entity.
3 No fully certified The legend and data mapunits to be included in the export file have been appropriately populated, reviewed, and certified for general use.
This certification applies to the whole export package as a single entity.

*/
//_____________________________________________________________________________
typedef std::string  farmland_classification
; /* = 
Length of Longest Choice Value: 114
1 No Not prime farmland Not prime farmland.
2 No All areas are prime farmland All areas are prime farmland.
3 No Prime farmland if drained Prime farmland if drained.
4 Prime farmland if protected
from flooding or not
frequently flooded during the
growing season
No Prime farmland if protected from flooding, or not frequently flooded during the growing season.
5 No Prime farmland if irrigated Prime farmland if irrigated.
6 Prime farmland if drained
and either protected from
flooding or not frequently
flooded during the growing
season
No Prime farmland if drained and either protected from flooding, or not frequenlty flooded during the growing season.
7 Prime farmland if irrigated
and drained
No Prime farmland if irrigated and drained.
8 Prime farmland if irrigated
and either protected from
flooding or not frequently
flooded during the growing
season
No Prime farmland if irrigated and either protected from flooding or not frequently flooded during the growing season.
Length of Longest Choice Value: 114
9 Prime farmland if subsoiled,
completely removing the root
inhibiting soil layer
No Prime farmland if subsoiled, completely removed the root inhibiting soil layer.
10 Prime farmland if irrigated
and the product of I (soil
erodibility) x C (climate
factor) does not exceed 60
No Prime farmland if irrigated and the product of I (soil erodibility) x C (climate factor) does not exceed 60.
11 Prime farmland if irrigated
and reclaimed of excess
salts and sodium
No Prime farmland if irrigated and reclaimed from excess salts and sodium.
12 Farmland of statewide
importance
No Farmland of statewide importance.
13 No Farmland of local importance Farmland of local importance.
14 Farmland of unique
importance
No Farmland of unique importance.

*/
//_____________________________________________________________________________
typedef std::string  fl_soil_leaching_potential
; /* = 
Length of Longest Choice Value: 6
1 No Low Slowest permeability is 0.6 in/hr or less. Soils with a muck/peat layer are rated "low".
2 No Medium Slowest permeability is between 0.6 and 6.0 in/hr. Soils with a mucky layer are rated "medium" unless the soil has a slowest permeability of less
than 0.6 in/hr. Then the soil is rated "low".
3 No High Slowest permeability is 6.0 in/hr or more.

*/
//_____________________________________________________________________________
typedef std::string  fl_soil_runoff_potential
; /* = 
Length of Longest Choice Value: 6
1 No Low Soils with a hydrological group of A, and soils with a hydrological group of B (in their natural, undrained state) that have a permeability of 6.0 in/hr
or greater in all of the upper 20 inches of the soil.
2 No Medium Soils with a hydrological group of C, and soils with a hydrological group of B (in their natural, undrained state) that have a permeability of less
than 6.0 in/hr within 20 inches of the soil surface. Soils that rate low are changed to a rating of medium where the slope is more than 12 percent.
3 No High Soils with a hydrological group of D in their natural, undrained state. Soils that are frequently flooded during the growing season are rated high.
Soils that rate medium are changed to a rating of high where the slope is more than 8 percent.
SSURGO Version: 2.2.3 Page 22
*/ //_____________________________________________________________________________


typedef std::string  flooding_duration_class
; /* = 
Length of Longest Choice Value: 15
1 No Extremely brief 0.1 to 4 hours
2 No Very brief 4 hours to 48 hours
3 No Brief 2 days to 7 days
4 No Long 7 days to 30 days
5 No Very long More than 30 days


*/
//_____________________________________________________________________________
typedef std::string  flooding_frequency_class
; /* = 
Length of Longest Choice Value: 13
1 No None No reasonable possibility of flooding; near 0 percent chance of flooding in any year or less than 1 time in 500 years.
2 No Very rare Flooding is very unlikely but is possible under unusual weather conditions; less than 1 percent chance in any year (less than 1 time in 100 years,
but more than 1 time in 500 years).
3 No Rare Flooding is unlikely but possible under unusual weather conditions; 1 to 5 percent chance in any year (1 to 5 times in 100 years).
4 No Occasional Flooding is expected infrequently, 5 to 50 percent chance in any year, (5 to 50 times in 100 years).
5 obsolete_Common
6 No Frequent Flooding is likely to occur often under usual weather conditions; more than 50 percent chance of flooding in any year or more than 50 times in
100 years, but less than a 50 percent chance of flooding in all months in any year.
7 No Very frequent Flooding is likey to occur very often under usual weather conditions; more than 50 percent chance in all months of any year.

*/
//_____________________________________________________________________________
typedef std::string  flooding_ponding_month
; /* = 
Length of Longest Choice Value: 9
1 No January
2 No February
3 No March
4 No April
5 No May
6 No June
7 No July
8 No August
9 No September
10 No October
11 No November
12 No December

*/
//_____________________________________________________________________________
typedef std::string  forest_productivity_units
; /* = 
Length of Longest Choice Value: 39
1 No board feet/acre/year Doyle
2 board feet/acre/year
International 1/4
No
3 board feet/acre/year
International 1/8
No
4 No board feet/acre/year Scribner
5 board feet/acre/year Scribner
Decimal C
No
6 board feet/acre/year
Spaulding
No
7 No cords/acre/year
8 No cubic feet/acre
9 No cubic feet/acre/year
10 No tons/acre/year

*/
//_____________________________________________________________________________
typedef std::string  fragment_kind
; /* = 
Length of Longest Choice Value: 58
1 No `A`a lava fragments A type of basaltic lava (material) having a rough, jagged, clinkery surface and a vesicular interior. Compare - block lava, pahoehoe lava, pillow
lava.
2 obsolete_Acidic-ash
3 No Amphibolite fragments
4 No Andesite fragments
5 obsolete_Andesitic-ash
6 No Rock anhydrite fragments A sedimentary rock (evaporite) composed chiefly of mineral anhydrite (anhydrous CaSO4); The rock is generally massive, cryptocrystalline, and
may exhibit rhythmic sedimentation (rhymites). Compare - rock gypsum, rock halite. SW
7 No Anorthosite fragments
8 No Arenite fragments
9 No Argillite fragments
10 No Arkose fragments
11 No Basalt fragments
12 obsolete_Basaltic-ash
13 obsolete_Basic-ash
14 No Bauxite fragments An off-white to dark red brown weathered detritus or rock composed of aluminum oxides (mainly gibbsite with some boehmite and diaspore), iron
hydroxides, silica, silt, and especially clay minerals. Bauxite originates in tropical and subtropical environments as highly weathered residue from
carbonate or silicate rocks and can occur in concretionary, earthy, pisolitic or oolitic forms. SW & GG
15 No Block lava fragments Lava having a surface of angular blocks; it is similar to `a`a lava but the fragments are larger and more regular in shape, somewhat smoother,
and less vesicular. Compare - `a`a lava, pahoehoe lava, pillow lava.
16 Non-volcanic breccia
fragments
No
17 Acidic Non-volcanic breccia
fragments
No
18 Basic Non-volcanic breccia
fragments
No
19 No Calcrete fragments
20 No Carbonate concretions
21 No Carbonate nodules
22 No Carbonate rock fragments
23 No Chalk fragments
24 No Charcoal fragments
25 No Chert fragments A hard, extremely dense or compact, dull to semivitreous, cryptocrystalline sedimentary rock, consisting dominantly of interlocking crystals of
quartz less than about 30 mm in diameter; it may contain amorphous silica (opal). It sometimes contains impurities such as calcite, iron oxide, or
the remains of silicious and other organisims. It has a tough, splintery to conchoidal fracture and may be white or variously colored gray, green,
blue, pink, red, yellow, brown, and black. Chet occurs principally as nodular or concretionary segregations in limestones and dolomites.
26 No Cinders Uncemented vitric, vesicular, pyroclastic material, more than 2.0 mm in at least one dimension, with an apparent specific gravity (including
vesicles) of more than 1.0 and less than 2.0. Compare - ash [volcanic], block [volcanic], lapilli, tephra.
27 No Claystone fragments
28 No Coal fragments
29 Calcareous conglomerate
fragments
No
30 Noncalcareous
conglomerate fragments
Yes
31 No Conglomerate fragments A coarse-grained, clastic sedimentary rock composed of rounded to subangular rock fragments larger than 2 mm, commonly with a matrix of
sand and finer material; cements include silica, calcium carbonate, and iron oxides. The consolidated equivalent of gravel.
32 No Dacite fragments
33 No Diabase fragments
34 No Diorite fragments
35 No Dolomite fragments A carbonate sedimentary rock consisting chiefly (more than 50 percent by weight or by areal percentages under the microscope) of the mineral
dolomite.
36 No Durinodes
37 No Duripan fragments
38 obsolete_Ejecta fragments
39 obsolete_Ejecta-ash
40 No Gabbro fragments
41 No Gibbsite concretions
42 No Gibbsite nodules
43 obsolete_Glauconite fragments
44 No Gneiss fragments
45 No Biotite gneiss fragments
46 Granodioritic gneiss
fragments
No
47 No Hornblende gneiss fragments
48 No Migmatitic gneiss fragments
49 Muscovite-biotite gneiss
fragments
No
50 obsolete_Acidic gneiss fragments
51 obsolete_Basic gneiss fragments
52 No Granite fragments
53 No Granitoid fragments a) In the IUGS classification, a preliminary term for (for field use) for a plutonic rock with Q (quartz) between 20 and 40 (%). b) A general term
for all phaneritic igneous rocks (mineral crystals visible unaided and all about the same size) dominated by quartz and feldspars.
54 No Granodiorite fragments
55 No Granofels fragments
56 No Granulite fragments
57 No Graywacke fragments
58 No Greenstone fragments
59 No Rock gypsum fragments A sedimentary rock (evaporite) composed primarily of mineral gypsum (CaSO4.2H2O). The rock is generally massive, ranges from coarse
crystalline to fine granular, may show disturbed bedding due to hydration expansion of parent anhydrite (anhydrous CaSO4), and may exhibit
rhythmic sedimentation (rhymites). Compare gypsite. GG
60 No Rock halite fragments A sedimentary rock (evaporite) composed primarily of halite (NaCl). SW
61 obsolete_Herbaceous material
62 No Hornfels fragments
63 obsolete_Acid igneous rock fragments
64 obsolete_Basic igneous rock fragments
65 Coarse crystal igneous rock
fragments
Yes
66 Fine crystal igneous rock
fragments
Yes
67 Intermediate igneous rock
fragments
Yes
68 Ultrabasic igneous rock
fragments
Yes
69 No Igneous rock fragments Rock formed by solidification from a molten or partially molten state; major varieties include plutonic and volcanic rocks. Examples: andesite,
basalt, granite. Compare - intrusive, extrusive.
70 No Ignimbrite fragments
71 Interbedded sedimentary
rock fragments
Yes
72 No Iron-manganese concretions
73 No Iron-manganese nodules
74 No Ironstone nodules
75 No Lapilli Non or slightly vesicular pyroclastics, 2.0 to 76 mm in at least one dimension, with an apparent specific gravity of 2.0 or more. Compare - ash
[volcanic], block [volcanic], cinders, tephra.
76 No Latite fragments
77 No Lignite fragments A brownish-black carbon-rich deposit that is a metamorphic intermediate between peat and sub-bituminous coal . Dry lignite typically contains
60-70 % carbon. SW & GG
78 Arenaceous limestone
fragments
No
79 Argillaceous limestone
fragments
No
80 No Cherty limestone fragments
81 No Coral limestone fragments An informal term for massive limestone composed primarily of coral and coral fragments commonly associated with marine islands or coral reefs
in tropical or subtropical waters. Compare - coral island. SW
82 Phosphatic limestone
fragments
No
83 No Limestone fragments A sedimentary rock consisting chiefly (more than 50 percent) of calcium carbonate, primarily in the form of calcite. Limestones are usually
formed by a combination of organic and inorganic processes and include chemical and clastic (soluble and insoluble) constituents; many contain
fossils.
84 Limestone-sandstone
fragments
Yes
85 Limestone-sandstone-shale
fragments
Yes
86 obsolete_Limestone-shale fragments
87 Limestone-siltstone
fragments
Yes
88 obsolete_Logs and stumps
89 No Marble fragments
90 obsolete_Marl fragments An earthy, unconsolidated deposit consisting chiefly of calcium carbonate mixed with clay in approximately equal proportions (35 to 65 percent of
each); formed primarily under freshwater lacustrine conditions, but varieties associated with more saline environments also occur.
91 No Metaconglomerate fragments
92 Foliated metamorphic rock
fragments
No
93 No Metamorphic rock fragments Rock of any origin altered in mineralogical composition, chemical composition, or structure by heat, pressure, and movement at depth in the
earth's crust. Nearly all such rocks are crystalline. Examples: schist, gneiss, quartzite, slate, marble.
94 No Metaquartzite fragments
95 Metasedimentary rock
fragments
No
96 No Metasiltstone fragments
97 No Metavolcanic rock fragments
98 No Migmatite fragments
99 No Mixed rock fragments
100 Mixed calcareous rock
fragments
Yes
101 Mixed igneous and
metamorphic rock fragments
Yes
102 Mixed igneous,
metamorphic, and
sedimentary rock fragments
Yes
103 Mixed igneous and
sedimentary rock fragments
Yes
104 Mixed metamorphic and
sedimentary rock fragments
Yes
105 Mixed noncalcareous rock
fragments
Yes
106 No Monzonite fragments
107 obsolete_Mossy material
108 No Mudstone fragments
109 No Mylonite fragments
110 No Novaculite A dense, extremely finely grained, even-textured, siliceous, sedimentary rock similar to chert. It is hard, white to grayish-black in color,
translucent on thin edges, has a dull to waxy luster, and displays smooth conchoidal fracture when broken.
Novaculite principally occurs in the Marathon Uplift of Texas and Ouachita Mountains of Arkansas and Oklahoma where it forms erosion resistant
ridges. Novaculite appears to form from chert recrystallization with microcrystalline quartz dominant over cryptocrystalline chalcedony. At the
Ouachita Mountains type occurrence, novaculite formed by low-grade, thermal metamorphism of bedded chert. Novaculite is commercially
quarried as a whetstone or oilstone. Compare - chert. GG & SW
111 No Obsidian fragments
112 obsolete_Organic material
113 No Orthoquartzite fragments
114 No Ortstein fragments
115 obsolete_Oxide protected rock
116 No Pahoehoe lava fragments A type of basaltic lava (material) with a characteristically smooth, billowy or rope-like surface and vesicular interior. Compare - `a`a lava, block
lava, pillow lava.
117 No Peridotite fragments
118 No Petrocalcic fragments
119 No Petroferric fragments
120 No Petrogypsic fragments
121 No Phyllite fragments
122 No Pillow lava fragments A general term for lava displaying pillow structure (discontinuous, close-fitting, bun-shaped or ellipsoidal masses, generally < 1 m in diameter);
considered to have formed in a subaqueous environment; such lava is usually basaltic or andesitic. Compare - `a`a lava, block lava, pahoehoe
lava.
123 No Plinthite nodules
124 No Porcellanite fragments
125 No Pumice fragments A light-colored, vesicular, glassy rock commonly having the composition of rhyolite. It commonly has a specific gravity of < 1.0 and is thereby
sufficiently buoyant to float on water.
126 No Pyroclastic rock fragments
127 obsolete_Pyroclastic fragments Fragmental materials produced by usually explosive, aerial ejection of clastic particles from a volcanic vent. Such materials may accumulate on
land or under water.
128 No Pyroxenite fragments
129 No Quartz fragments
130 No Quartz-diorite fragments
131 No Quartzite fragments
132 No Quartz-monzonite fragments
133 No Rhyolite fragments
134 Calcareous sandstone
fragments
No
135 Glauconitic sandstone
fragments
No
136 Noncalcareous sandstone
fragments
Yes
137 No Sandstone fragments Sedimentary rock containing dominantly sand-size clastic particles.
138 Sandstone and shale
fragments
Yes
139 Sandstone and siltstone
fragments
Yes
140 obsolete_Saprolite
141 obsolete_Acidic schist fragments
142 obsolete_Basic schist fragments
143 No Graphitic schist fragments
144 No Mica schist fragments
145 No Schist fragments
146 No Scoria fragments Vesicular, cindery crust or bomb-sized fragments of such material on the surface of andesitic or basaltic lava, the vesicular nature of which is due
to the escape of volcanic gases before solidification; it is usually heavier, darker, and more crystalline than pumice. Synonym - cinder.
147 No Sedimentary rock fragments A consolidated deposit of clastic particles, chemical precipitates, and organic remains accumulated at or near the surface of the earth under
"normal" low temperature and pressure conditions. Sedimentary rocks include consolidated equivalents of alluvium, colluvium, drift, and eolian,
lacustrine, marine deposits; e.g., sandstone, siltstone, mudstone, clay-stone, shale, conglomerate, limestone, dolomite, coal, etc.
148 No Serpentinite fragments
149 No Acid shale fragments
150 No Calcareous shale fragments
151 No Clayey shale fragments
152 Noncalcareous shale
fragments
Yes
153 No Shale fragments Sedimentary rock formed by induration of a clay, silty clay, or silty clay loam deposit and having the tendency to split into thin layers, i.e., fissility.
154 obsolete_Shale-siltstone fragments
155 No Shell fragments
156 No Silica concretions
157 Calcareous siltstone
fragments
No
158 Noncalcareous siltstone
fragments
Yes
159 No Siltstone fragments Sedimentary rock containing dominantly silt-size clastic particles.
160 No Slate fragments
161 No Sulfidic slate fragments
162 No Soapstone fragments
163 No Syenite fragments
164 No Syenodiorite fragments
165 No Tachylite fragments
166 No Tonalite fragments
167 No Trachyte fragments
168 No Travertine fragments
169 No Tripoli fragments A light-colored, porous, friable, siliceous (largely chalcedonic) sedimentary rock, which occurs in powdery or earthy masses that result from the
weathering of siliceous limestone. It has a harsh, rough feel and is used to polish metals and stones.
170 No Tufa fragments
171 No Tuff breccia fragments
172 No Acidic tuff fragments
173 No Basic tuff fragments
174 No Tuff fragments A compacted deposit that is 50 percent or more volcanic ash and dust
175 No Welded tuff fragments
176 No Ultramafic rock fragments
177 No Volcanic bombs
178 Acidic volcanic breccia
fragments
No
179 Basic volcanic breccia
fragments
No
180 No Volcanic breccia fragments
181 No Volcanic rock fragments
182 No Wood fragments
*/
//_____________________________________________________________________________
typedef std::string  fragment_roundness
; /* = 
Length of Longest Choice Value: 12
1 No Very angular Strongly developed faces with very sharp, broken edges.
2 No Angular Strongly developed faces with sharp edges (SSM).
3 No Subangular Detectable flat faces with slightly-rounded corners.
4 No Subrounded Detectable flat faces with well-rounded corners (SSM).
5 No Rounded Flat faces absent or nearly absent with all corners rounded (SSM).
6 No Well rounded Flat faces absent with all corners rounded.
*/
//_____________________________________________________________________________
typedef std::string  fragment_shape
; /* = 
Length of Longest Choice Value: 7
1 No Flat
2 No Nonflat
*/
//_____________________________________________________________________________
typedef std::string  geomor_pos_flat
; /* = 
Length of Longest Choice Value: 4
1 obsolete_Flat default choice, official choices to be determined later
2 No Dip A geomorphic component (characteristic piece) of flat plains (e.g., lake plain, low coastal plain, low-relief till plain) consisting of a shallow and
typically closed depression that tends to be an area of focused groundwater recharge but not a permanent water body and that lies slightly lower
and is wetter than the adjacent talf, and favors the accumulation of fine sediments and organic materials. SW
3 No Rise A geomorphic component of flat plains (e.g., lake plain, low coastal plain, low-gradient till plain) consisting of a slightly elevated but low, broad
area with low slope gradients (e.g. 1-3 % slopes); typically a microfeature but can be fairly extensive. Commonly soils on a rise are better
drained than those on the surrounding talf. Compare - talf. SW
4 No Talf A geomorphic component of flat plains (e.g., lake plain, low coastal plain, low-gradient till plain) consisting of an essentially flat (e.g. 0-1 %
slopes) and broad area dominated by closed depressions and a non-integrated or poorly integrated drainage system. Precipitation tends to pond
locally and lateral transport is slow both above and below ground, which favors the accumulation of soil organic matter and a retention of fine
earth sediments; better drained soils are commonly adjacent to drainageways. Compare - rise. SW
*/
//_____________________________________________________________________________
typedef std::string  geomor_pos_hill
; /* = 
Length of Longest Choice Value: 13
1 No Interfluve An elevated area between two drainageways that sheds water to those drainageways.
2 No Head Slope The concave surface at the head of a drainageway where the flow of water converges downward toward the center and contour lines form
concave curves.
3 No Nose Slope The projecting end of an interfluve, where contour lines connecting the opposing side slopes form convex curves around the projecting end and
lines perpendicular to the contours diverge downward. Overland flow of water is divergent.
4 No Side Slope The slope bounding a drainageway and lying between the drainageway and the adjacent interfluve. It is generally linear along the slope width
and overland flow is parallel down the slope.
5 No Base Slope A geomorphic component of hills consisting of the concave to linear slope (perpendicular to the contour) which, regardless of the lateral shape is
an area that forms an apron or wedge at the bottom of a hillside dominated by colluvial and slope wash processes and sediments (e.g., colluvium
and slope alluvium). Distal base slope sediments commonly grade to, or interfinger with, alluvial fills, or gradually thin to form pedisediment over
residuum. Compare - head slope, side slope, nose slope, interfluve, free face. SW
6 No Crest A geomorphic component of hills consisting of the convex slopes (perpendicular to the contour) that form the narrow, roughly linear top area of a
hill, ridge, or other upland where shoulders have converged to the extent that little or no summit remains; dominated by erosion, slope wash and
mass movement processes and sediments (e.g., slope alluvium, creep). Commonly, soils on crests are more similar to those on side slopes than
to soils on adjacent interfluves. Compare - interfluve, head slope, side slope, nose slope. SW
7 No Free face The part of a hillside or mountainside consisting of an outcrop of bare rock (scarp or cliff) that sheds colluvium to slopes below and commonly
stands more steeply than the angle of repose of the colluvial slope (e.g. talus slope) immediately below. SW & GG
8 obsolete_Crested hills
*/
//_____________________________________________________________________________
typedef std::string  geomor_pos_mountain
; /* = 
Length of Longest Choice Value: 29
1 No Mountaintop
2 No Mountainflank
3 No Mountainbase
4 No Upper third of mountainflank
5 No Center third of mountainflank
6 No Lower third of mountainflank
7 No Free face The part of a hillside or mountainside consisting of an outcrop of bare rock (scarp or cliff) that sheds colluvium to slopes below and commonly
stands more steeply than the angle of repose of the colluvial slope (e.g. talus slope) immediately below. SW & GG
*/
//_____________________________________________________________________________
typedef std::string  geomor_pos_terrace
; /* = 
Length of Longest Choice Value: 5
1 No Riser The vertical or steeply sloping surface, commonly one of a series, of natural steplike landforms, as those of a glacial stairway or of successive
stream terraces.
2 No Tread The flat or gently sloping surface of natural step-like landforms, commonly one of a series, such as successive stream terraces.
*/
//_____________________________________________________________________________
typedef std::string  hillslope_profile
; /* = 
Length of Longest Choice Value: 9
1 No Summit The topographically highest hillslope position of a hillslope profile and exhibiting a nearly level (planar or only slightly convex) surface.
2 No Shoulder The hillslope position that forms the uppermost inclined surface near the top of a hillslope. If present, it comprises the transition zone from
backslope to summit. The surface is dominantly convex in profile and erosional in origin.
3 No Backslope The hillslope profile position that forms the steepest and generally linear, middle portion of the slope. In profile, backslopes are commonly
bounded by a convex shoulder above and a concave footslope below. They may or may not include cliff segments (i.e. free faces). Backslopes
are commonly erosional forms produced by mass movement, colluvial action, and running water.
4 No Footslope The hillslope position that forms the inner, gently inclined surface at the base of a hillslope. In profile, footslopes are commonly concave. It is a
transition zone between upslope sites of erosion and transport (shoulder, backslope) and downslope sites of deposition (toeslope).
5 No Toeslope The hillslope position that forms the gently inclined surface at the base of a hillslope. Toeslopes in profile are commonly gentle and linear, and
are constructional surfaces forming the lower part of a hill-slope continuum that grades to valley or closed-depression floors.
*/
//_____________________________________________________________________________
typedef std::string  horz_desgn_letter_suffix
; /* = 
Length of Longest Choice Value: 2
1 No a Highly decomposed organic matter. This symbol is used with O to indicate the most highly decomposed organic materials, which have a rubbed
fiber content of less than 17 percent of the volume.
2 No b Buried genetic horizon. This symbol is used in mineral soils to indicate identifiable buried horizons with major genetic features that were
developed before burial. Genetic horizons may or may not have formed in the overlying material, which may be either like or unlike the assumed
parent material of the buried soil. This symbol is not used in organic soils or to separate an organic from a mineral layer.
3 No c Concretions or nodules. This symbol indicates a significant accumulation of concretions or nodules. Cementation is required, but the cementing
agent is not specified, except that it cannot be silica. This symbol is not used if the concretions or nodules consist of dolomite or calcite or more
soluble salts, but it is used if the nodules or concretions are enriched with minerals that contain iron, aluminum, manganese, or titanium.
4 obsolete_ca An accumulation of carbonates.
5 No co Used only with the master designation L to indicate a layer dominated by coprogenous material.
6 No d Physical root restriction. This symbol indicates root-restricting layers in naturally occurring or man-made unconsolidated sediments or materials,
such as dense basal till, plow pans, and other mechanically compacted zones.
7 No di Used only with the master designation L to indicate a layer dominated by diatomaceous earth.
8 No e Organic material of intermediate decomposition. This symbol is used with O to indicate organic materials of intermediate decomposition. Their
rubbed fiber content is 17 to 40 percent (by volume).
9 No f Frozen soil or water. This symbol indicates that a horizon or layer contains permanent ice. The symbol is not used for seasonally frozen layers
or for so-called dry permafrost (material that is colder than OC but does not contain ice).
10 No ff Dry permafrost. Used in layers or horizons that are colder than 0 degrees C, but do not contain ice. It is not used for layers or horizons that have
seasonal temperatures below 0 degrees C. The f suffix is used for layers or horizons that contain permanent ice.
11 No g Strong gleying. This symbol indicates either that iron has been reduced and removed during soil formation, or that saturation with stagnant water
has preserved it in a reduced state. Most of the affected layers have a chroma of 2 or less, and many have redox concentrations. The low
chroma can represent either the color of reduced iron or the color of uncoated sand and silt particles from which iron has been removed. The
symbol g is not used for materials of low chroma that have no history of wetness, such as some shales or E horizons. If g is used with B,
pedogenic change in addition to gleying is implied. If no other pedogenic change besides gleying has taken place, the horizon is designated Cg.
12 No h Illuvial accumulation of organic matter. This symbol is used with B to indicate the accumulation of illuvial, amorphous, dispersible organic-mattersesquioxide
complexes if the sesquioxide component is dominated by aluminum but is present only in very small quantities. The organosesquioxide
material coats sand and silt particles. In some horizons, these coatings have coalesced, filled pores, and cemented the horizon.
The symbol h is also used in combination with s as "Bhs" if the amount of sesquioxide component is significant but the color value and chroma,
moist, of the horizon is 3 or less.
13 No i Slightly decomposed organic material. This symbol is used with O to indicate the least decomposed of the organic materials. Its rubbed fiber
content is 40 percent or more (by volume).
14 No j Indicates an accumulation of jarosite. Jarosite is a potassium or sodium iron sulfate mineral that is commonly an alteration product of pyrite upon
exposure in an oxidizing environment. In tidal marshes it is associated with extreme acidity. Jarosite is easily recognized by its yellowish
apperance, often a hue of 2.5Y or yellower and a chroma of 6 or more, although chroma as low as 3 or 4 have been reported.
15 No jj Indicates evidence of cyroturbation. Cryoturbation includes frost stirring, freezing and thawing, and mounding and fissuring. Soils with
cryoturbation often feature thermokarst, ground-ice formation, and patterned ground. Cryoturbation commonly is manifested by irregular and
broken boundaries, sorting of rock fragments, and organic matter in the lower boundaries, especially along the boundary between the active layer
and the permafrost table. The jj suffix can be used with master horizons A, B, or C.
16 No k Accumulation of secondary carbonates. This symbol indicates accumulations of visible pedogenic calcium carbonate (less than 50 % by vol).
Carbonate accumulations occurs as carbonate filaments, coatings, masses, nodules, disseminated carbonate, or other forms.
17 No kk Engulfment of horizon by secondary carbonates. This symbol indicates major accumulations of pedogenic calcium carbonate. The kk suffix is
used when the soil fabric is plugged with fine-grained pedogenic carbonate (50 % or more by vol) that occurs as an essentially continuous
medium. The kk suffix corresponds to the Stage III plugged horizon or higher of the carbonate morphogenetic stages.
18 No m Cementation or induration. This symbol indicates continuous or nearly continuous cementation. It is used only for horizons that are more than
90 percent cemented, although they may be fractured. The cemented layer is physically root-restrictive. The predominant cementing agent (or
the two dominant cementing agents) may be indicated by using defined letter suffixes, singly or in pairs.
19 No ma Used only with the master designation L to indicate a layer dominated by marl.
20 No n Accumulation of sodium. This symbol indicates an accumulation of exchangeable sodium.
21 No o This symbol indicates a residual accumulation of sesquioxides.
22 No p Tillage or other disturbance. This symbol indicates a disturbance of the surface layer by mechanical means, pasturing, or similar uses. A
disturbed organic horizon is designated Op. A disturbed mineral horizon is designated Ap even though it is clearly a former E, B, or C horizon.
23 No q Accumulation of silica. This symbol indicates an accumulation of secondary silica.
24 No r Weathered or soft bedrock. This symbol is used with C to indicate root-restrictive layers of saprolite such as weathered igneous rock, or of soft
bedrock such as partly consolidated sandstone, siltstone, and shale. Excavation difficulty is low to high.
25 No s Illuvial accumulation of sesquioxides and organic matter. This symbol is used with B to indicate an accumulation of illuvial, amorphous,
dispersible organic-matter-sesquioxide complexes if both the organic-matter and sesquioxide components are significant, and if either the color
value or chroma, moist, of the horizon is 4 or more. The symbol is also used in combination with "h" as "Bhs" if both the organic-matter and
sesquioxide components are significant, and if the color value and chroma, moist, is 3 or less.
26 No ss This symbol indicates the presence of slickensides. Slickensides result directly from the swelling of clay minerals and shear failure, commonly at
angles of 20 to 60 degrees above horizontal. They are indicators that other vertic characteristics, such as wedge-shaped peds and surface
cracks, may be present. of slickensides.
27 No t Accumulation of silicate clay. This symbol indicates an accumulation of silicate clay that has either formed and subsequently been translocated
within the horizon or has been moved into the horizon by illuviation, or both. At least some part of the horizon should show evidence of clay
accumulation either as coatings on surfaces of peds or in pores, or as lamellae or as bridges between mineral grains.
28 No u Presence of human-manufactured materials (artifacts). This symbol indicates the presence of human-manufactured artifacts that have been
created or modified by humans, usually for a practical purpose in habitation, manufacturing, excavation, or construction activities.
29 No v Plinthite. This symbol indicates the presence of iron-rich, humus-poor reddish material that is firm or very firm when moist and hardens
irreversibly when exposed to the atmosphere and to repeated wetting and drying.
30 No w Development of color or structure. This symbol is used with B to indicate the development of color or structure, or both, with little or no apparent
illuvial accumulation of material. It should not be used to indicate a transitional horizon.
31 No x Fragipan character. This symbol indicates a genetically developed layer that has a combination of firmness, brittleness, and commonly a higher
bulk density than adjacent layers. Some part of the layer is physically root-restrictive.
32 No y Accumulation of gypsum. This symbol indicates a gypsum accumulation.
33 No z Accumulation of salts more soluble than gypsum. This symbol indicates an accumulation of salts that are more soluble than gypsum.
*/ //_____________________________________________________________________________

typedef std::string  horz_desgn_master
; /* = 
Length of Longest Choice Value: 7
1 No O Layers dominated by organic material. Some are saturated with water for long periods, or were once saturated but are now artificially drained;
others have never been saturated.
2 No A Mineral horizons which have formed at the surface or below an O horizon; they exhibit obliteration of all or much of the original rock structure1
and show one or both of the following: (1) an accumulation of humified organic matter intimately mixed with the mineral fraction and not
dominated by properties characteristic of E or B horizons (defined below), or (2) properties resulting from cultivation, pasturing, or similar kinds of
disturbance.
3 No E Mineral horizons in which the main feature is loss of silicate clay, iron, or aluminum, or some combination of these, leaving a concentration of
sand and silt particles. These horizons exhibit obliteration of all or much of the original rock structure.
4 No B Horizons which have formed below an A, E, or O horizon; they are dominated by the obliteration of all or much of the original rock structure and
show one or more of the following:
(1) Illuvial concentration of silicate clay, iron, aluminum, humus, carbonates, gypsum, or silica, alone or in combination;
(2) Evidence of removal of carbonates;
(3) Residual concentration of sesquioxides;
(4) Coatings of sesquioxides that make the horizon conspicuously lower in color value, higher in chroma, or redder in hue, without apparent
illuviation of iron, than overlying and underlying horizons;
(5) Alteration which forms silicate clay or liberates oxides, or both, and which forms a granular, blocky, or prismatic structure if volume changes
accompany changes in moisture content; or
(6) Brittleness.
5 No C Horizons or layers, excluding hard bedrock, that are little affected by pedogenic processes and lack the properties of O, A, E, or B horizons.
Most are mineral layers. The material of C layers may be either like or unlike the material from which the solum has presumably formed. The C
horizon may have been modified, even if there is no evidence of pedogenesis.
6 No R Hard Bedrock
7 No AB Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
8 No AE Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
9 No AC Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
10 No EA Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
11 No EB Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
12 No BA Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
13 No BE Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
14 No BC Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
15 No CA Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
16 No CB Horizons dominated by properties of one master horizon but having subordinate properties of another. The first of these symbols indicates that
the properties of the horizon so designated dominate the transitional horizon. An AB horizon, for example, has characteristics of both an
overlying A horizon and an underlying B horizon, but it is more like the A than like the B.
17 No A/E Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
18 No A/B Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
19 No A/C Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
20 No E/A Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
21 No E/B Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
22 No B/A Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
23 No B/E Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
24 No B/C Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
25 No C/A Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
26 No C/B Horizons with two distinct parts that have recognizable properties of the two kinds of master horizons indicated by the capital letters. Most of the
individual parts of one horizon component are surrounded by the other.
27 No E and B Horizons that are composed of lamellae that are separated from each other by eluvial layers.
28 obsolete_O'
29 obsolete_A'
30 obsolete_E'
31 obsolete_B'
32 obsolete_C'
33 obsolete_O''
34 obsolete_A''
35 obsolete_E''
36 obsolete_B''
37 obsolete_C''
38 obsolete_H A horizon designation that will only be used for conversion from SSSD layers to NASIS horizons. This designation should never be used aside
for this one purpose.
39 No W Water
40 No L Layers dominated by limnic material. The limnic materials can be either mineral or organic. One and only one of the suffixes ma, co, or di are
used with the L designation.
41 No EC
42 No B and E Horizons that are composed of lamellae that are separated from each other by eluvial layers.
43 No M Root-limiting, subsoil layers consisting of nearly continuous, horizontally oriented, human manufactured materials. Examples of materials
designated by the letter M include geotextile liners, asphalt, concrete, rubber, and plastic.
44 No ^O The "caret" symbol (^) is used as a prefix to master horizon
designations to indicate mineral or organic layers of human-transported
material. This material has been moved horizontally
onto a pedon from a source area outside of that pedon by
directed human activity, usually with the aid of machinery. All
horizons and layers formed in human-transported material are
indicated by a "caret" prefix (e.g., ^A-^C-Ab-Btb).
The "O" indicates layers dominated by organic material. Some are saturated with water for long periods, or were once saturated but are now
artificially drained; others have never been saturated.
45 No ^A The "caret" symbol (^) is used as a prefix to master horizon
designations to indicate mineral or organic layers of human-transported
material. This material has been moved horizontally
onto a pedon from a source area outside of that pedon by
directed human activity, usually with the aid of machinery. All
horizons and layers formed in human-transported material are
indicated by a "caret" prefix (e.g., ^A-^C-Ab-Btb).
The "A" is assigned to mineral horizons which have formed at the surface or below an O horizon; they exhibit obliteration of all or much of the
original rock structure and show one or both of the following: (1) an accumulation of humified organic matter intimately mixed with the mineral
fraction and not dominated by properties characteristic of E or B horizons (defined below), or (2) properties resulting from cultivation, pasturing, or
similar kinds of disturbance.
46 No ^E The "caret" symbol (^) is used as a prefix to master horizon
designations to indicate mineral or organic layers of human-transported
material. This material has been moved horizontally
onto a pedon from a source area outside of that pedon by
directed human activity, usually with the aid of machinery. All
horizons and layers formed in human-transported material are
indicated by a "caret" prefix (e.g., ^A-^C-Ab-Btb).
The "E" is assigned to mineral horizons in which the main feature is loss of silicate clay, iron, or aluminum, or some combination of these, leaving
a concentration of sand and silt particles. These horizons exhibit obliteration of all or much of the original rock structure.
47 No ^B The "caret" symbol (^) is used as a prefix to master horizon
designations to indicate mineral or organic layers of human-transported
material. This material has been moved horizontally
onto a pedon from a source area outside of that pedon by
directed human activity, usually with the aid of machinery. All
horizons and layers formed in human-transported material are
indicated by a "caret" prefix (e.g., ^A-^C-Ab-Btb).
The "B" is assiged to horizons which have formed below an A, E, or O horizon; they are dominated by the obliteration of all or much of the
original rock structure and show one or more of the following:
(1) Illuvial concentration of silicate clay, iron, aluminum, humus, carbonates, gypsum, or silica, alone or in combination;
(2) Evidence of removal of carbonates;
(3) Residual concentration of sesquioxides;
(4) Coatings of sesquioxides that make the horizon conspicuously lower in color value, higher in chroma, or redder in hue, without apparent
illuviation of iron, than overlying and underlying horizons;
(5) Alteration which forms silicate clay or liberates oxides, or both, and which forms a granular, blocky, or prismatic structure if volume changes
accompany changes in moisture content; or
(6) Brittleness.

48 No ^C The "caret" symbol (^) is used as a prefix to master horizon
designations to indicate mineral or organic layers of human-transported
material. This material has been moved horizontally
onto a pedon from a source area outside of that pedon by
directed human activity, usually with the aid of machinery. All
horizons and layers formed in human-transported material are
indicated by a "caret" prefix (e.g., ^A-^C-Ab-Btb).
The "C" is assigned to horizons or layers, excluding hard bedrock, that are little affected by pedogenic processes and lack the properties of O, A,
E, or B horizons. Most are mineral layers. The material of C layers may be either like or unlike the material from which the solum has
presumably formed. The C horizon may have been modified, even if there is no evidence of pedogenesis.
*/
//_____________________________________________________________________________
typedef std::string  horz_desgn_master_prime
; /* = 
Length of Longest Choice Value: 2
1 No '
2 No ''
*/
//_____________________________________________________________________________
typedef std::string  hydric_classification_map_legend
; /* = 
Length of Longest Choice Value: 16
1 No All hydric All components are hydric and no components are unranked.
2 No Not hydric All components are not hydric and no components are unranked.
3 No Partially hydric Some components are hydric and some components are not hydric.
4 No Unknown No components are hydric and some or all components are not ranked.
*/
//_____________________________________________________________________________
typedef std::string  hydric_condition
; /* = 
Length of Longest Choice Value: 52
1 Farmable under natural
conditions
No Farmable under natureal conditions.
2 Neither wooded nor farmable
under natural conditions
No Neither wooded nor farmable under natural conditions.
3 Wooded under natural
conditions
No Wooded under natural conditions.
*/
//_____________________________________________________________________________
typedef std::string  hydric_criteria
; /* = 
Length of Longest Choice Value: 3
1  1 All Histels except Folistels, and all Histosols except Folists.
2  2A Soils in Aquic suborders, great groups, or subgroups, Albolls suborder, Historthels great group, Histoturbels great group, Pachic subgroups, or
Cumulic subgroups that are somewhat poorly drained with a water table equal to 0.0 foot (ft) from the surface during the growing season.
3  2B1 Soils in Aquic suborders, great groups, or subgroups, Albolls suborder, Historthels great group, Histoturbels great group, Pachic subgroups, or
Cumulic subgroups that are poorly drained or very poorly drained and have a water table equal to 0.0 ft during the growing season if textures are
coarse sand, sand, or fine sand in all layers within 20 inches.
4  2B2 Soils in Aquic suborders, great groups, or subgroups, Albolls suborder, Historthels great group, Histoturbels great group, Pachic subgroups, or
Cumulic subgroups that are poorly drained or very poorly drained and have a water table at less than or equal to 0.5 ft from the surface during
the growing season if permeability is equal to or greater than 6.0 in/hour (h) in all layers within 20 inches.
5  2B3 Soils in Aquic suborders, great groups, or subgroups, Albolls suborder, Historthels great group, Histoturbels great group, Pachic subgroups, or
Cumulic subgroups that are poorly drained or very poorly drained and have water table* at less than or equal to 1.0 ft from the surface during the
growing season if permeability is less than 6.0 in/h in any layer within 20 inches.
6  3 Soils that are frequently ponded for long duration or very long duration during the growing season.
7  4 Soils that are frequently flooded for long duration or very long duration during the growing season.
*/
//_____________________________________________________________________________
typedef std::string  hydric_rating
; /* = 
Length of Longest Choice Value: 8
1 No Yes
2 No No
3 No Unranked
*/
//_____________________________________________________________________________
enum Hydrologic_group
{A    // A Soils in this group have low runoff potential when thoroughly wet. Water is transmitted freely through the soil.
,B    // B Soils in this group have moderately low runoff potential when thoroughly wet. Water transmission through the soil is unimpeded.
,C    // C Soils in this group have moderately high runoff potential when thoroughly wet. Water transmission through the soil is somewhat restricted.
,D    // D Soils in this group have high runoff potential when thoroughly wet. Water movement through the soil is restricted or very restricted.
   // The following identifies Drained/undrained hydrology class
   // of soils that can be drained and are classified.
   // These drainage classes are not used in CropSyst or SPAW
,A_D  // A/D These soils have low runoff potential when drained and high runoff potential when undrained.
,B_D  // B/D These soils have moderately low runoff potential when drained and high runoff potential when undrained.
,C_D  // C/D These soils have moderately high runoff potential when drained and high runoff potential when undrained.
};
extern Label_description hydrologic_group_label_table[];
DECLARE_DESCRIPTIVE_LABELED_ENUM(Hydrologic_group_labeled,Hydrologic_group,hydrologic_group_label_table);
//_____________________________________________________________________________
typedef std::string  investigation_intensity
; /* = 
Length of Longest Choice Value: 7
1 No Order 1
2 No Order 2
3 No Order 3
4 No Order 4
5 No Order 5
*/
//_____________________________________________________________________________
typedef std::string  legend_certification_status
; /* = 
Length of Longest Choice Value: 20
1 No not for distribution Data in the legend object, including some mapunits, correlation notes, or area overlaps, have been created but are not fully populated or the data
are preliminary and incomplete. The data are subject to major changes. A legend with this status should not be interpreted, exported, or used by
other applications.
Note that this certification status applies to only the legend object.
2 No not certified The data in the legend object, including mapunits, correlation notes, and area overlaps, have been created and have been appropriately
populated, but data have not been reviewed or certified. These are advance data, subject to change.
Note that this certification status applies to only the legend object.
3 No partly certified The data in the legend object, including mapunits, correlation notes, and area overlaps, have been appropriately populated and the data have
been reviewed. At least some of the data elements have been certified for use in specific applications. Other data elements in the object have
advance data, subject to change.
Note that this certification status applies to only the legend object.
4 No certified The data in the legend object, including mapunits, correlation notes, and area overlaps, have been appropriately populated, reviewed, and
certified for general use.
Note, that this certification status applies to only the legend object.
*/
//_____________________________________________________________________________
typedef std::string  legend_suitability_for_use
; /* = 
Length of Longest Choice Value: 24
1 No not current The legend has been completely replaced by another legend for the survey area. Typically this legend has an out-of-date operational soil survey
status and another survey legend completely covers the geographic area served by this legend.
2 No current for part of area The legend is up-to-date for only part of the geographic area it covers. Another legend is up-to-date for the remaining area. Typically occurs
where an update survey is on-going in a survey area or where a more recent survey covers part of the geographic area.
3 No current wherever mapped The legend is up-to-date wherever it has been mapped in the survey area. If the survey area is completely mapped, the legend applies over the
entire geographic area. If the mapping is on-going, the legend is up-to-date where mapping has been completed.
*/
//_____________________________________________________________________________
typedef std::string  legend_text_kind
; /* = 
Length of Longest Choice Value: 27
1 No Edit notes Text entries that describe what changes were made to the data and why those changes were made.
2 Memorandum of
understanding
No Text entries that include the text of the original MOU for the survey and any amendments to the MOU.
3 No Certification statements Text entries related to certification of this legend. For example, statements of prior survey and legend-wide join statements.
4 No Field reviews Text entries related to initial, progress, and final field reviews. For example, the general text part of a progress field review that applies to the
entire legend.
5 No Correlation notes Text entries related to correlation concerns that affect the entire legend.
6 No Miscellaneous notes Text entries not relate to any of the other choices.
7 obsolete_Nontechnical description
8 obsolete_SOI5 description
*/
//_____________________________________________________________________________
typedef std::string  logical_data_type_ssurgo
; /* = 
Length of Longest Choice Value: 9
1 No Boolean The value of such an attribute is either true or false (or yes or no, or on or off).
2 No Choice The value of such an attribute is restricted to a finite set choices. Typically the set of choices is a set of unique character strings, although the
set may also be a set of unique numbers.
3 No Date/Time The value of such an attribute is either a date, a time, or a range that encompasses both date and time.
4 No Float The value of such an attribute is a floating point (real) number.
5 No Integer The value of such an attribute is an integer (whole) number.
6 No Money The value of such an attribute is a combination of dollars and cents, where cents are represented as the decimal part of the numeric value.
7 No String The value of such an attribute is a string of printable characters. Nonprinting control characters such as "tab" and "paragraph break" cannot be
part of such a string.
8 No Vtext The value of such an attribute is a string of characters that includes both printable characters and control characters such as "tab" and
"paragraph break".
*/
//_____________________________________________________________________________
typedef std::string  manner_of_failure
; /* = 
Length of Longest Choice Value: 17
1 No Brittle The speciman retains its size and shape (no deformation) until it rupture abruptly into subunits or fragments. (SSM)
2 No Semideformable Deformation occurs prior to rupture. Cracks develop and the speciman ruptures before compression to half its original thickness. (SSM)
3 No Deformable The speciman can be compressed to half its original thickness without rupture. Radial cracks may appear and extend inward less than half the
radius normal to compression. (SSM)
4 No Nonfluid None of the speciman flows through the fingers after exerting full compression. (SSM)
5 No Slightly fluid After exerting full compression, some of the speciman flows through the fingers, but most remains in the palm of the hand.
6 No Moderately fluid After exerting full compression, most of the speciman flows through the fingers; a small residue remains in the palm of the hand.
7 obsolete_Strongly fluid
8 No Very fluid Under very gentle pressure most of the speciman flows through the fingers like a slightly viscous fluid; very little or no residue remains in the
palm of the hand. (SSM)
9 No Nonsmeary At failure, the speciman does not chage suddenly to a fluid, the fingers do not skid, and no smearing occurs. (SSM)
10 No Weakly smeary At failure, the speciman changes suddenly to fluid, the fingers skid, and the soil smears. Afterward, little or no free water remains on the fingers.
(SSM)
11 No Moderately smeary At failure, the speciman changes suddenly to fluid, the fingers skid, and the soil smears. Afterward, some free water can be seen on the fingers.
(SSM)               ZZ
12 No Strongly smeary At failure, the speciman suddenly changes to fluid, the fingers skid, the soil smears, and is very slippery. Afterward, free water is easliy seen on
the fingers. (SSM)
13 obsolete_Smeary
SSURGO Version: 2.2.3 Page 45
*/ //_____________________________________________________________________________

typedef std::string  mapunit_certification_status
; /* = 
Length of Longest Choice Value: 20
1 No not for distribution The map unit object has been created, but is not populated or the data are preliminary and incomplete. The data are subject to major changes.
A map unit with this status should not be interpreted, exported, or used by other applications.
2 No not certified The data in the map unit object have been created and have been appropriately populated, at least in part, but the data have not been reviewed
or certified. Data in some data elements in these tables may be more complete than in others. These are advance data, subject to change.
3 No partly certified The data in the map unit object have been appropriately populated and the data have been reveiwed. At least some of the data elements have
been certified for use in specific applications. Other data elements in the object have advance data, subject to change.
4 No certified The data in the map unit object have been appropriately populated, reviewed, and certified for general use.
*/
//_____________________________________________________________________________
typedef std::string  mapunit_hel_class
; /* = 
Length of Longest Choice Value: 32
1 No Not highly erodible land
2 Potentially highly erodible
land
No
3 No Highly erodible land
*/
typedef std::string  mapunit_kind
; /* =                                        ZZ
Length of Longest Choice Value: 22
1 No Association Two or more dissimilar soils that occur in a regularly repeating pattern that could have been separated at the scale of field mapping, but were not
separated due to the intended purpose of the survey.
2 No Complex Two or more dissimilar soils that occur in a regularly repeating pattern, that cannot be separated at the scale of field mapping.
3 No Consociation At least seventy-five percent (75%) of the map unit is within the range of the soil providing the name of the unit, and closely similar soils.
4 No Undifferentiated group Two or more similar soils that are not always geographically associated, and are mapped together due to them having the same or very similar
use and management concerns.
*/
//_____________________________________________________________________________
typedef std::string  mapunit_status
; /* = 
Length of Longest Choice Value: 11
1 No Provisional A map unit used by the soil survey party leader, but that have not been officially approved for use.
2 No Approved A map unit on the current, signed field review report for the survey area.
3 No Correlated A map unit on the signed final correlation document.
4 No Additional A map unit that has been used in the soil survey area, but that has been combined with another unit in the survey.
*/
//_____________________________________________________________________________
typedef std::string  mapunit_text_kind
; /* = 
Length of Longest Choice Value: 24
1 No Edit notes Text entries that describe what changes were made to the data and why those changes were made.
2 No Correlation notes Text entries about correlation concerns related to this mapunit, not including mapunit name or status changes.
3 No Map unit description Map unit descriptions typically used in a descriptive legend.
4 No Nontechnical description Map unit descriptions converted from SSSD and downloaded to FOCS.
5 No Certification statements Text entries related to certification of mapunits.
6 No Miscellaneous notes Text entries not related to any of the other choices.
7 obsolete_SOI5 description
*/
//_____________________________________________________________________________
typedef std::string  mi_soil_management_group
; /* = 
Length of Longest Choice Value: 7
1 No 0a
2 No 0b
3 No 0c
4 No 1.5a
5 No 1.5a-s
6 No 1.5b
7 No 1.5b-s
8 No 1.5c
9 No 1.5c-c
10 No 1/5a
11 No 1/Rbc
12 No 1a
13 No 1b
14 No 1c
15 No 1c-c
16 No 2.5a
17 No 2.5a-a
18 No 2.5a-af
19 No 2.5a-cs
20 No 2.5a-d
21 No 2.5a-s
22 No 2.5b
23 No 2.5b-cd
24 No 2.5b-cs
25 No 2.5b-d
26 No 2.5b-s
27 No 2.5c
28 No 2.5c-c
29 No 2.5c-cs
30 No 2.5c-s
31 No 2/3a-f
32 No 2/Ra
33 No 2/Rb
34 No 2/Rbc
35 No 3/1a
36 No 3/1b
37 No 3/1c
38 No 3/2a
39 No 3/2a-d
40 No 3/2a-f
41 No 3/2b
42 No 3/2b-d
43 No 3/2c
44 No 3/5a
45 No 3/5a-a
46 No 3/5b
47 No 3/5b-c
48 No 3/5c
49 No 3/Ra
50 No 3/Rbc
51 No 3a
52 No 3a-a
53 No 3a-af
54 No 3a-d
55 No 3a-f
56 No 3a-s
57 No 3b
58 No 3b-a
59 No 3b-af
60 No 3b-s
61 No 3c
62 No 3c-s
63 No 4/1a
64 No 4/1b
65 No 4/1c
66 No 4/2a
67 No 4/2a-f
68 No 4/2a-hs
69 No 4/2b
70 No 4/2b-s
71 No 4/2c
72 No 4/2c-c
73 No 4/Ra
74 No 4/Rbc
75 No 4a
76 No 4a-a
77 No 4a-af
78 No 4a-h
79 No 4b
80 No 4c
81 No 5.3a
82 No 5.7a
83 No 5/2a
84 No 5/2b
85 No 5/2b-h
86 No 5/2c
87 No 5a
88 No 5a-a
89 No 5a-h
90 No 5b
91 No 5b-h
92 No 5c
93 No 5c-a
94 No 5c-c
95 No 5c-h
96 No G/Ra
97 No G/Rbc
98 No Ga
99 No Ga-d
100 No Ga-f
101 No Gbc
102 No Gbc-af
103 No Gc-cd
104 No L-2a
105 No L-2b
106 No L-2c
107 No L-2c-c
108 No L-4a
109 No L-4c
110 No L-Mc
111 No M/1c
112 No M/3c
113 No M/3c-a
114 No M/4c
115 No M/4c-a
116 No M/mc
117 No M/Ra
118 No M/Rc
119 No Mc
120 No Mc-a
121 No Ra
122 No Rbc
*/
//_____________________________________________________________________________
typedef std::string  micro_relief_kind
; /* = 
Length of Longest Choice Value: 26
1 No Micro-high A generic microrelief term applied to slightly elevated areas relative to the adjacent ground surface; changes in relief range from several
centimeters to several meters; crossectional profiles can be simple or complex and generally consist of gently rounded, convex tops with gently
sloping sides.
2 No Micro-low A generic microrelief term applied to slightly lower areas relative to the adjacent ground surface; changes in relief range from several centimeters
to several meters; ; crossectional profiles can be simple or complex and generally consist of subdued, concave, open or closed depressions with
gently sloping sides.
3 obsolete_Micro-depression refer to micro-low
4 obsolete_Micro-knoll refer to micro-high.
5 obsolete_Other (specified in notes)
*/
//_____________________________________________________________________________
typedef std::string  mlra_office
; /* = 
Length of Longest Choice Value: 16
1 No Portland, OR
2 No Davis, CA
3 No Reno, NV
4 No Bozeman, MT
SSURGO Version: 2.2.3 Page 51
*/ //_____________________________________________________________________________

typedef std::string  mlra_office
; /* = 
Length of Longest Choice Value: 16
5 No Salina, KS
6 No Lakewood, CO
7 No Bismarck, ND
8 No Phoenix, AZ
9 No Temple, TX
10 No St. Paul, MN
11 No Indianapolis, IN
12 No Amherst, MA
13 No Morgantown, WV
14 No Raleigh, NC
15 No Auburn, AL
16 No Little Rock, AR
17 No Palmer, AK
18 No Lexington, KY
*/
//_____________________________________________________________________________
typedef std::string  mou_agency_responsible
; /* = 
Length of Longest Choice Value: 38
1 No Bureau of Indian Affairs
2 No Bureau of Land Management
3 No County
4 No Divison of Conservation
5 Department of Natural
Resources
No
6 No Department of Defense
7 No Department of Energy
8 Divison of Conservation
Services
No
9 No Indian Nation
10 No North Dakota State University
11 No National Park Service
12 Natural Resources
Conservation Service
No
SSURGO Version: 2.2.3 Page 52
*/ //_____________________________________________________________________________

typedef std::string  mou_agency_responsible
; /* = 
Length of Longest Choice Value: 38
13 No US Air Force
14 No University of Illinois
15 No US Forest Service
16 No Virginia Polytechnic Institute
*/
//_____________________________________________________________________________
typedef std::string  nh_important_forest_soil_group
; /* = 
Length of Longest Choice Value: 9
1 No Group IA Deep, loamy, well drained and moderately well drained soils with few management limitations.
2 No Group IB Deep, loamy or sandy, well drained or moderately well drained soils with few management limitations.
3 No Group IC Deep, sandy and gravelly, excessively drained through moderately well drained outwash soils with few management limitations.
4 No Group IIA Diverse group of soils, generally groups IA and IB soils that have management limitations.
5 No Group IIB Poorly drained soils.
6 No NC Generally unproductive soils or miscellaneous areas.
*/
//_____________________________________________________________________________
typedef std::string  observed_soil_moisture_status
; /* = 
Length of Longest Choice Value: 32
1 No Dry >1500 kPa (>15 bar) suction
2 No Very dry Less than 0.35 of the 15 bar water retention.
3 No Moderately dry 0.35 to 0.8 of the 15 bar water retention.
4 No Slightly dry 0.8 to 1.0 of the 15 bar water retention.
5 No Moist =<1500 to 0.01 kPa ( =<15 bar to 0.00001 bar) suction.
6 No Slightly moist 15 bar suction to MWR (see SSM p 91).
7 No Moderately moist MWR to UWR water content (see SSM p91).
8 No Very moist UWR to 0.01 bar suction (see SSM p91).
9 No Wet <1.0 kPa, or <0.5 for coarse soils, (<0.01 bar or 0.005 for coarse soils) suction.
10 No Wet, non-satiated =>0.01 to 1.0 (0.5 for coarse soils) kPA suction, (=>0.00001 bar to 0.01 bar, 0.005 for coarse soils). Water films are visible, sand grains and
peds glisten, but no free water is present.
11 No Wet, satiated <0.01 kPa (<0.00001 bar) suction; free water present.
12 Saturation from capillary fringe
13 obsolete_Frozen
*/
//_____________________________________________________________________________
typedef std::string  parent_material_kind
; /* = 
Length of Longest Choice Value: 39
1 obsolete_aa
2 No Alluvium Unconsolidated clastic material subaerially deposited by running water, including gravel, sand, silt, clay, and various mixtures of these.
3 obsolete_arkosic-sandstone
4 No Ash flow A highly heated mixture of volcanic gases and ash, traveling down the flank of a volcano or along the surface of the ground; produced by the
explosive disintegration of viscous lava in a volcanic crater, or by the explosive emission of gas-charged ash from a fissure or group of fissures.
The solid materials contained in a typical ash flow are generally unsorted and ordinarily include volcanic dust, pumice, scoria, and blocks in
addition to ash.
5 No Backswamp deposits
6 No Bauxite An off-white to dark red brown weathered detritus or rock composed of aluminum oxides (mainly gibbsite with some boehmite and diaspore), iron
hydroxides, silica, silt, and especially clay minerals. Bauxite originates in tropical and subtropical environments as highly weathered residue from
carbonate or silicate rocks and can occur in concretionary, earthy, pisolitic or oolitic forms. SW & GG
7 No Beach sand Well sorted, sand-sized, clastic material transported, sorted and deposited primarily by wave action and deposited in a shore environment.
Compare - eolian sands.
8 No Block glide deposits
9 obsolete_breccia-acidic
10 obsolete_breccia-basic
11 obsolete_chalk
12 obsolete_charcoal
13 No Cinders Uncemented vitric, vesicular, pyroclastic material, more than 2.0 mm in at least one dimension, with an apparent specific gravity (including
vesicles) of more than 1.0 and less than 2.0.
14 obsolete_coal
15 No Coastal marl An earthy, unconsolidated deposit of gray to buff-colored mud of low bulk density (dry) composed primarily of very fine, almost pure calcium
carbonate formed in subaqueous settings that span freshwater lacustrine conditions (e.g. Florida Everglades) to saline intertidal settings (e.g.
Florida Keys) formed by the chemical action of algal mats and organic detritus (periphyton); other marl varieties associated with different
environments (e.g. freshwater marl, glauconitic marl) also occur. Coastal marl can be quite pure or it can be finely disseminated throughout living
root mats (e.g. mangrove roots) and / or organic soil layers. Compare marl, freshwater marl.
16 No Colluvium Unconsolidated, unsorted earth material being transported or deposited on side slopes and/or at the base of slopes by mass movement (e.g.
direct gravitational action) and by local, unconcentrated runoff.
SSURGO Version: 2.2.3 Page 54
*/ //_____________________________________________________________________________

typedef std::string  parent_material_kind
; /* = 
Length of Longest Choice Value: 39
17 No Complex landslide deposits A category of mass movement processes, associated sediments (complex landslide deposit) or resultant landforms characterized by a composite
of several mass movement processes none of which dominates or leaves a prevailing landform. Numerous types of complex landslides can be
specified by naming the constituent processes evident (e.g. a complex earth spread - earth flow landslide). Compare - fall, topple, slide, lateral
spread, flow, landslide. SW & DV
18 obsolete_conglomerate
19 obsolete_conglomerate-calcareous
20 obsolete_conglomerate-noncalcareous
21 No Coprogenic material
22 No Creep deposits Sediment resulting from slow mass movement of earth material down slopes, caused by gravity but facilitated by saturation with water and
alternate freezing and thawing.
23 No Cryoturbate
24 No Debris avalanche deposits Sediment resulting from the very rapid and usually sudden sliding and flow of incoherent, unsorted mixtures of soil and weathered bedrock.
25 No Debris fall deposits The process, associated sediments (debris fall deposit) or resultant landform characterized by a rapid type of fall involving the relatively free,
downslope movement or collapse of detached, unconsolidated material which falls freely through the air (lacks an underlying slip face);
sediments have substantial proportions of both fine earth and coarse fragments; common along undercut stream banks. Compare - rock fall, soil
fall, landslide. SW
26 No Debris flow deposits Sediment resulting from a mass movement of rock fragments, soil, mud, more than half of the particles being larger than sand size.
27 No Debris slide deposits
28 No Debris spread deposits The process, associated sediments (debris spread deposit) or resultant landforms characterized by a very rapid type of spread dominated by
lateral movement in a soil and rock mass resulting from liquefaction or plastic flow of underlying materials that may be extruded out between
intact units; sediments have substantial proportions of both fine earth and coarse fragments. Compare - earth spread, rock spread, landslide.
SW & DV
29 No Debris topple deposits The process, associated sediments (debris topple deposit) or resultant landform characterized by a localized, very rapid type of topple in which
large blocks of soil and rock material literally fall over, rotating outward over a low pivot point; sediments have substantial proportions of both
fine earth and coarse fragments. Portions of the original material may remain intact, although reoriented, within the resulting debris pile.
Compare - earth topple, rock topple, landslide. SW
30 No Diamicton A nonlithified, nonsorted or poorly sorted sediment that contains a wide range of particle sizes, such as coarse fragments contained within a fine
earth matrix (e.g. till, pebbly mudstone) and used when
31 No Diatomaceous earth
32 obsolete_dolomite
33 No Dredge spoils Unconsolidated, randomly mixed sediments extracted and deposited during dredging and dumping activities (e.g. adjoining the Intracoastal
Waterway). Dredge spoils lie unconformably upon natural, undisturbed soil or regolith and can form anthropogenic landforms (e.g. dredge spoil
bank).
34 No Drift A general term applied to all mineral material (clay, silt, sand, gravel, boulders) transported by a glacier and deposited directly by or from the ice,
or by running water emanating from a glacier. Drift includes unstratified material (till) that forms moraines, and stratified deposits that form
outwash plains, eskers, kames, varves, and glaciofluvial sediments. The term is generally applied to Pleistocene glacial deposits in areas that
no longer contain glaciers.
SSURGO Version: 2.2.3 Page 55
*/ //_____________________________________________________________________________

typedef std::string  parent_material_kind
; /* = 
Length of Longest Choice Value: 39
35 No Earth spread deposits The process, associated sediments (earth spread deposit) or resultant landforms characterized by a very rapid type of spread dominated by
lateral movement in a soil mass resulting from liquefaction or plastic flow of underlying materials that may be extruded out between intact units.
Compare - debris spread, rock spread, landslide. SW & DV
36 No Earth topple deposits The process, associated sediments (earth topple deposit) or resultant landform characterized by a localized, very rapid type of topple in which
large blocks of soil material literally fall over, rotating outward over a low pivot point; sediments < 2 mm predominate. Portions of the original
material may remain intact, although reoriented, within the resulting deposit. Compare - debris topple, rock topple, landslide. SW
37 No Earthflow deposits
38 No Eolian deposits Material transported and deposited by the wind. Includes earth materials such as dune sands, sand sheets, loess deposits, and clay (e.g. parna).
39 No Eolian sands Material transported and deposited by the wind, dominated by particles of sand-size (0.05-2 mm).
40 No Estuarine deposits
41 No Fall deposits (a) A category of mass movement processes, associated sediments (fall deposit), or resultant landforms (e.g., rockfall, debris fall, soil fall)
characterized by very rapid movement of a mass of rock or earth that travels mostly through the air by free fall, leaping, bounding, or rolling, with
little or no interaction between one moving unit and another. Compare - topple, slide, lateral spread, flow, complex landslide, landslide. SW &
DV; (b) The mass of material moved by a fall. GG
42 No Flow deposits A category of mass movement processes, associated sediments (flow deposit) and landforms characterized by slow to very rapid downslope
movement of unconsolidated material which, whether saturated or comparatively dry, behaves much as a viscous fluid as it moves. Types of
flows can be specified based on the dominant particle size of sediments (i.e. debris flow (e.g., lahar), earth flow (creep, mudflow), rock fragment
flow (e.g., rockfall avalanche), debris avalanche]. Compare - fall, topple, slide, lateral spread, complex landslide, landslide. SW & DV
43 No Fluviomarine deposits Stratified materials (clay, silt, sand, or gravel) formed by both marine and fluvial processes, resulting from sea level flucuations and stream
migration (i.e. materials originally deposited in a nearshore environment and subsequently reworked by fluvial processes as sea level fell, or vice
versa as sea level rose).
44 No Freshwater marl A soft, grayish to white, earthy or powdery, usually impure calcium carbonate precipitated on the bottoms of present-day freshwater lakes and
ponds largely through the chemical action of algal mats and organic detritus, or forming deposits that underlie marshes, swamps, and bogs that
occupy the sites of former (glacial) lakes. The calcium carbonate may range from 90% to less than 30%. Freshwater marl is usually gray; it has
been used as a fertilizer for acid soils deficient in lime. Syn.: bog lime. Compare marl, coastal marl.
45 No Glaciofluvial deposits Material moved by glaciers and subsequently sorted and deposited by streams flowing from the melting ice. The deposits are stratified and may
occur in the form of outwash plains, valley trains, deltas, kames, eskers, and kame terraces.
46 No Glaciolacustrine deposits Material ranging from fine clay to sand derived from glaciers and deposited in glacial lakes by water originating mainly from the melting of glacial
ice. Many are bedded or laminated with varves or rhythmites.
47 No Glaciomarine deposits Glacially eroded, terrestrially derived sediments (clay, silt, sand, and gravel) that accumulated on the ocean floor. Sediments may be
accumulated as an ice-contact deposit, by fluvial transport, ice-rafting, or eolian transport.
48 obsolete_glauconite
49 obsolete_gneiss
50 obsolete_gneiss-acidic
51 obsolete_gneiss-basic
SSURGO Version: 2.2.3 Page 56
*/ //_____________________________________________________________________________

typedef std::string  parent_material_kind
; /* = 
Length of Longest Choice Value: 39
52 No Greensands a) An unconsolidated, near-shore marine sediment containing substantial amounts of dark greenish glauconite pellets, often mingled with clay or
sand (quartz may form the dominant constituent); prominent in Cretaceous and Tertiary coastal plain strata of New Jersey, Delaware and
Maryland; has been commercially mined for potassium fertilizer. The term is loosely applied to any glauconitic sediment. b) (Not Preferred - use
glauconitic sandstone) A sandstone consisting of greensand that is commonly poorly cemented, and has a greenish color when unweathered
but an orange or yellow color when weathered. Compare - glauconite pellets. SW
53 No Grus The fragmental products of in situ granular disintegration of granite and granitic rocks, dominated by inter-crystal disintegration.
54 No Gypsite An earthy gypsum (CaSO4.2H2O) variety that contains various quantities (i.e. < 50%) of soil material, silicate clay minerals and sometimes other
salts (e.g. NaCl); found only in arid or semi-arid regions as secondary precipitation concentrations or efflorescence associated with rock gypsum
or gypsum-bearing strata. Compare rock gypsum, rock anhydrite. SW & GG
55 No Human transported material Organic or mineral soil material (or any other material that can function as a soil material) that has been moved horizontally onto a pedon from a
source area outside of that pedon by directed human activity, usually with the aid of machinery. There has been little or no subsequent reworking
by wind, gravity, water, or ice. Human transported materials are most commonly associated with building sites, mining or dredging operations,
land fills, or other similar activities that result in the formation of a constructional anthropogenic landform.
56 obsolete_igneous
57 obsolete_igneous-acid (eg., rhyolite)
58 obsolete_igneous-andesite
59 obsolete_igneous-basalt
60 obsolete_igneous-basic (eg., gabbro)
61 obsolete_igneous-coarse (or intrusive)
62 obsolete_igneous-fine (or extrusive)
63 obsolete_igneous-granite
64 igneous-intermediate (eg.,
diorite)
Yes
65 obsolete_igneous-ultrabasic
66 obsolete_interbedded sedimentary
67 No Lacustrine deposits Clastic sediments and chemical precipitates deposited in lakes.
68 No Lagoonal deposits Sand, silt or clay-sized sediments transported and deposited by wind, currents, and storm washover in the relatively low-energy, brackish to
saline, shallow waters of a lagoon. Compare - marine deposit.
69 No Lahar A term for a mass movement landform and a process characterized by a mudflow composed chiefly of volcaniclastic materials on or near the
flank of a volcano. The debris carried in the flow includes pyroclastic material, blocks from primary lava flows, and epiclastic material.
70 No Lapilli Non or slightly vesicular pyroclastics, 2.0 to 76 mm in at least one dimension, with an apparent specific gravity of 2.0 or more.
71 No Lateral spread deposits
72 obsolete_limestone
73 obsolete_limestone-arenaceous
74 obsolete_limestone-argillaceous
75 obsolete_limestone-cherty
SSURGO Version: 2.2.3 Page 57
*/ //_____________________________________________________________________________

typedef std::string  parent_material_kind
; /* = 
Length of Longest Choice Value: 39
76 obsolete_limestone-phosphatic
77 obsolete_limestone-sandstone
78 obsolete_limestone-sandstone-shale
79 obsolete_limestone-shale
80 obsolete_limestone-siltstone
81 No Limonite A general 'field' term for various brown to yellowish brown, amorphous- to- cryptocrystalline hydrous ferric oxides that are an undetermined
mixture of goethite, hematite, and lepidocrocite formed by weathering and iron oxidation from iron-bearing, rocks and minerals. SW & GG
82 No Loess Material transported and deposited by wind and consisting predominantly of silt size.
83 No Calcareous loess
84 No Noncalcareous loess Noncalcareous material transported and deposited by wind and consisting predominantly of silt size (0.002-0.05 mm).
85 obsolete_logs and stumps
86 obsolete_marble
87 No Marine deposits
88 No Marl A generic term loosely applied to a variety of materials, most of which occur as an earthy, unconsolidated deposit consisting chiefly of an intimate
mixture of clay and calcium carbonate formed commonly by the chemical action of algae mats and organic detritus (periphyton); specifically an
earthy substance containing 35-65% clay and 65-35% calcium carbonate mud; formed primarily under freshwater lacustrine conditions, but
varieties associated with more saline environments and higher carbonate contents also occur. Compare coastal marl, freshwater marl,
89 No Mass movement deposits Sediment resulting from the dislodgement and downslope transport of soil and rock material as a unit under direct gravitational stress. The
process includes slow displacements such as creep and solifluction, and rapid movements such as landslides, rock slides, and falls, earthflows,
debris flows, and avalanches. Agents of fluid transport (water, ice, air) may play an important, if subordinate role in the process.
90 obsolete_metamorphic
91 No Mine spoil or earthy fill
92 No Coal extraction mine spoil Randomly mixed, earthy materials artificially deposited as a result of either surficial or underground coal mining activities.
93 Metal ore extraction mine
spoil
No Randomly mixed, earthy materials artificially deposited as a result of either surficial or underground metal-ore mining activities.
94 obsolete_mixed
95 obsolete_mixed-calcareous
96 mixed-igneous &
metamorphic
Yes
97 obsolete_mixed-igneous & sedimentary
98 mixed-igneous-metamorphic
& sedimentary
Yes
99 mixed-metamorphic &
sedimentary
Yes
100 obsolete_mixed-noncalcareous
SSURGO Version: 2.2.3 Page 58
*/ //_____________________________________________________________________________

typedef std::string  parent_material_kind
; /* = 
Length of Longest Choice Value: 39
101 No Mudflow deposits
102 No Grassy organic material
103 No Herbaceous organic material
104 No Mossy organic material
105 No Organic material
106 No Woody organic material
107 No Outwash (a) Stratified detritus (chiefly sand and gravel) removed or "washed out" from a glacier by melt-water streams and deposited in front of or beyond
the end moraine or the margin of an active glacier. The coarser material is deposited nearer to the ice.
108 No Overbank deposits
109 obsolete_pahoehoe
110 No Parna A term used, especially in southeast Australia, for silt and sand-sized aggregates of eolian clay occurring in sheets.
111 No Pedisediment A layer of sediment, eroded from the shoulder and back slope of an erosional slope, that lies on and is, or was, being transported across a
pediment.
112 No Pumice
113 obsolete_pyroclastic
114 No Pyroclastic flow A fast density current of pyroclastic material, usually very hot, composed of a mixture of gasses and a variety of pyroclastic particles (ash,
pumice, scoria, lava fragments, etc.); produced by the explosive disintegration of viscous lava in a volcanic crater or by the explosive emission of
gas-charged ash from a fissure and which tends to follow topographic lows (e.g. valleys) as it moves; used in a more general sense than ash
flow. Compare - pyroclastic surge, ash flow, nue ardente, lahar. SW, SN, GG
115 No Pyroclastic surge A low density, dilute, turbulent pyroclastic flow, usually very hot, composed of a generally unsorted mixture of gases, ash, pumice and dense
rock fragments that travels across the ground at high speed and less constrained by topography than a pyroclastic flow; several types of
pyroclastic surges can be specified (e.g. base surge, ash-cloud-surge). Compare - pyroclastic flow. SW, SN, GG
116 obsolete_quartzite
117 No Residuum Unconsolidated, weathered, or partly weathered mineral material that accumulates by disintegration of bedrock in place.
118 No Rock spread deposits The process, associated sediments (rock spread deposit) or resultant landforms characterized by a very rapid type of spread dominated by
lateral movement in a rock mass resulting from liquefaction or plastic flow of underlying materials that may be extruded out between intact units;
rock bodies predominate. Compare - debris spread, earth spread, landslide. SW & DV
119 No Rock topple deposits The process, associated sediments (rock topple deposit) or resultant landform characterized by a localized, very rapid type of fall in which large
blocks of rock material literally fall over, rotating outward over a low pivot point; rock bodies predominate (little fine earth). Portions of the original
material may remain intact, although reoriented, within the resulting deposit. Compare - earth topple, debris topple, landslide. SW
120 No Rockfall avalanche deposits
121 No Rockfall deposits
122 Rotational debris slide
deposits
No The process, associated sediments (rotational debris slide deposit) or resultant landform characterized by an extremely slow to moderately rapid
type of slide, composed of comparatively dry and largely unconsolidated earthy material, portions of which remain largely intact and in which
movement occurs along a well-defined, concave shear surface and resulting in a backward rotation of the displaced mass; sediments have
substantial proportions of both fine earth and coarse fragments. The landform may be single, successive (repeated up and down slope), or
multiple (as the number of slide components increase). Compare - rotational earth slide, rotational rock slide, translational slide, lateral spread,
landslide. SW & DV
123 Rotational earth slide
deposits
No The process, associated sediments (rotational earth slide deposit) or resultant landform characterized by an extremely slow to moderately rapid
type of slide, composed of comparatively dry and largely unconsolidated earthy material, portions of which remain largely intact and in which
movement occurs along a well-defined, concave shear surface and resulting in a backward rotation of the displaced mass; sediments
predominantly fine earth (< 2 mm). The landform may be single, successive (repeated up and down slope), or multiple (as the number of slide
components increase). Compare - rotational debris slide, rotational rock slide, translational slide, lateral spread, landslide. SW & DV
124 No Rotational rock slide deposits The process, associated sediments (rotational rock slide deposit) or resultant landform characterized by an extremely slow to moderately rapid
type of slide, composed of comparatively dry and largely consolidated rock bodies, portions of which remain largely intact but reoriented, and in
which movement occurs along a well-defined, concave shear surface and resulting in a backward rotation of the displaced mass. The landform
may be single, successive (repeated up and down slope), or multiple (as the number of slide components increase). Compare - rotational debris
slide, rotational earth slide, translational slide, lateral spread, landslide. SW & DV
125 No Rotational slide deposits An accumlation of sediment resulting from a mass movement and a process characterized by a slide in which shearing takes place on a well
defined, curved shear surface, concave upward, producing a backward rotation in the displaced mass.
126 No Sand flow deposits A flow of wet sand, as along banks of noncohesive clean sand that is subject to scour and to repeated fluctuations in pore-water pressure due to
rise and fall of the tide. GG
127 obsolete_sandstone
128 obsolete_sandstone-calcareous
129 obsolete_sandstone-noncalcareous
130 obsolete_sandstone-shale
131 obsolete_sandstone-siltstone
132 No Saprolite - (Provisional definition) Soft, friable, isovolumetrically weathered bedrock that retains the fabric and structure of the parent rock (Colman and
Dethier, 1986) exhibiting extensive inter-crystal and intra-crystal weathering.
In pedology, saprolite was formerly applied to any unconsolidated residual material underlying the soil and grading to hard bedrock below.
133 obsolete_schist
134 obsolete_schist-acidic
135 obsolete_schist-basic
136 No Scoria Vesicular, cindery crust or bomb-sized fragments of such material on the surface of andesitic or basaltic lava, the vesicular nature of which is due
to the escape of volcanic gases before solidification; it is usually heavier, darker, and more crystalline than pumice. Synonym - cinder.
137 No Scree A collective term for an accumulation of coarse rock debris or a sheet of coarse debris mantling a slope. Scree is not a synonym of talus, as
scree includes loose, coarse fragment material on slopes without cliffs.
138 obsolete_sedimentary
139 obsolete_serpentine
140 obsolete_shale
141 obsolete_shale-calcareous
142 obsolete_shale-clay
143 obsolete_shale-noncalcareous
144 obsolete_shale-siltstone
145 obsolete_siltstone
146 obsolete_siltstone-calcareous
147 obsolete_siltstone-noncalcareous
148 obsolete_slate
149 No Slide deposits A category of mass movement processes, associated sediments (slide deposit) or resultant landforms (e.g., rotational slide, translational slide,
and snowslide) characterized by a failure of earth, snow, or rock under shear stress along one or several surfaces that are either visible or may
reasonably be inferred. The moving mass may or may not be greatly deformed, and movement may be rotational (rotational slide) or planar
(translational slide). A slide can result from lateral erosion, lateral pressure, weight of overlying material, accumulation of moisture,
earthquakes, expansion owing to freeze-thaw of water in cracks, regional tilting, undermining, fire, and human agencies. Compare -fall, topple,
lateral spread, flow, complex landslide. SW & DV (b) The track of bare rock or furrowed earth left by a slide. (c) The mass of material moved in
or deposited by a slide. Compare - fall, flow, complex landslide, landslide. SW & GG
150 No Slope alluvium Sediment gradually transported on mountain or hill slopes primarily by alluvial processes and characterized by particle sorting. In a profile
sequence, sediments may be distinguished by differences in size and/or specific gravity of coarse fragments and may be separated by stone
lines. Sorting of rounded or subrounded pebbles or cobbles and burnished peds distinguish these materials from unsorted colluvial deposits.
151 No Slump block TheA mass of material torn away as a coherent unit during a landslide; a largely intact but displaced and commonly reoriented body of rock or
soil. SW & GG
152 No Soil fall deposits
153 obsolete_Solid rock
154 obsolete_Solifluctate
155 No Solifluction deposits A deposit of nonsorted, water-saturated, locally derived earthy material that is moving or has moved downslope, en masse, caused by the
melting of seasonal frost or permafrost.
156 No Supraglacial debris-flow
157 No Talus Rock fragments of any size or shape (usually coarse and angular) derived from and lying at the base of a cliff or very steep rock slope. The
accumulated mass of such loose broken rock formed chiefly by falling, rolling, or sliding.
158 No Tephra A collective term for all clastic volcanic materials that are ejected from a vent during an eruption and transported through the air, including ash
[volcanic ], blocks [volcanic], cinders, lapilli, scoria, and pumice. Tephra is a general term which, unlike many volcaniclastic terms, does not
denote properties of composition, visicularity, or grain size.
159 No Ablation till A general term for loose, relatively permeable material deposited during the downwasting of nearly static glacial ice, either contained within or
accumulated on the surface of the glacier.
160 No Basal till Unconsolidated material of mixed composition deposited at the base (bottom) of a glacier [ The term emphaizes the e.g. subglacial till. Types of
basal till include lodgment, melt-out, and flow till.
161 No Flow till A till, commonly supraglacial, that is modified and transported by plastic mass flow; also spelled flow till. Compare - ablation till, basal till,
lodgment till, mass-movement till, slump-till, supraglacial melt-out till.
162 No Lodgment till A basal till commonly characterized by compact, fissile ("platy") structure and containing coarse fragments oriented with their long axes generally
parallel to the direction of ice movement.
163 No Melt-out till Till derived from slow melting of debris-rich stagnant ice buried beneath sufficient overburden to inhibit deformation under gravity, thus preserving
structures derived from the parent ice.
164 obsolete_Slump till
165 No Subglacial till Till deposited in or by the bottom parts of a glacier or ice sheet; types include lodgement till, subglacial flow till; synonym (not preferred;
obsolete): basal till. SW & GM
166 No Supraglacial till
167 No Supraglacial meltout till
168 No Till Dominantly unsorted and unstratified drift, generally unconsolidated and deposited directly by a glacier without subsequent reworking by
meltwater, and consisting of a heterogeneous mixture of clay, silt, sand, gravel, stones, and boulders; rock fragments of various lithologies are
imbedded within a finer matrix that can range from clay to sandy loam. Compare - ablation till, basal till, flowtill, lodgment till, drift, moraine.
169 No Topple deposits
170 Translational debris slide
deposits
No The process, associated sediments (translational debris slide deposit) or resultant landform characterized by an extremely slow to moderately
rapid type of slide, composed of comparatively dry and largely unconsolidated earthy material, portions or blocks of which remain largely intact
and in which movement occurs along a well-defined, planar slip face roughly parallel to the ground surface and resulting in lateral displacement
but no rotation of the displaced mass; sediments have substantial proportions of both fine earth and coarse fragments. The landform may be
single, successive (repeated up and down slope), or multiple (as the number of slide components increase). Compare - translational earth slide,
translational rock slide, rotational slide lateral spread, landslide. SW & DV
171 Translational earth slide
deposits
No The process, associated sediments (translational earth slide deposit) or resultant landform characterized by an extremely slow to moderately
rapid type of slide, composed of comparatively dry and largely unconsolidated earthy material, portions or blocks of which remain largely intact
and in which movement occurs along a well-defined, planar slip face roughly parallel to the ground surface and resulting in lateral displacement
but no rotation of the displaced mass; sediments predominantly fine earth (< 2 mm). The landform may be single, successive (repeated up and
down slope), or multiple (as the number of slide components increase). Compare translational debris slide, translational rock slide, rotational
slide, lateral spread, landslide. SW & DV
172 Translational rock slide
deposits
No The process, associated sediments (translational rock slide deposit) or resultant landform characterized by an extremely slow to moderately rapid
type of slide, composed of comparatively dry and largely consolidated rock bodies, portions or blocks of which remain largely intact and in which
movement occurs along a well-defined, planar slip face roughly parallel to the ground surface and resulting in lateral displacement but no rotation
of the displaced mass; sediments predominantly fine earth (< 2 mm). The landform may be single, successive (repeated up and down slope), or
multiple (as the number of slide components increase). Compare translational debris slide, translational earth slide, rotational slide, lateral
spread, landslide. SW & DV
173 No Translational slide deposits A category of mass movement processes, associated sediments (translational slide deposit) or resultant landforms characterized by the
extremely slow to moderately rapid downslope displacement of comparatively dry soil-rock material on a surface (slip face) that is roughly parallel
to the general ground surface, in contrast to falls topples, and rotational slides. The term includes such diverse slide types as translational debris
slides, translational earth slide, translational rock slide, block glides, and slab or flake slides. . Compare - rotational slide, slide, landslide. SW,
DV, GG
174 obsolete_tuff
175 obsolete_tuff-acidic
176 obsolete_tuff-basic
177 obsolete_tuff-breccia
178 obsolete_Unconsolidated sediments
179 No Valley side alluvium
180 No Volcanic ash Unconsolidated, pyroclastic material less than 2 mm in all dimensions.
181 No Acidic volcanic ash
182 No Andesitic volcanic ash
183 No Basaltic volcanic ash
184 No Basic volcanic ash
185 No Volcanic bombs
186 obsolete_Volcanic breccia
187 obsolete_Wood fragments
*/
//_____________________________________________________________________________
typedef std::string  parent_material_modifier
; /* = 
Length of Longest Choice Value: 18
1 No Clayey The soil texture class is clay, sandy clay, or silty clay.
2 No Coarse-loamy The material contains less than 18 percent clay and 15 percent or more particles that are 0.1 to 75.0 mm in size. The soil texture class is loamy
very fine sand, very fine sand, or finer.
3 No Coarse-silty The material contains less than 18 percent clay and less than 15 percent particles that are 0.1 to 75.0 mm in size.
4 No Fine-loamy The material contains 18 to 35 percent clay and 15 percent or more particles that are 0.1 to 75.0 mm in size.
5 No Fine-silty The material contains 18 to 35 percent clay and less than 15 percent particles that are 0.1 to 75.0 mm in size.
6 No Gravelly The material contains 15 percent or more rock fragments.
7 No Loamy The soil texture class is sandy loam, sandy clay loam, clay loam, silt, silt loam, or silty clay loam.
8 No Sandy The soil texture class is sand or loamy sand.
9 No Sandy and gravelly The soil texture class contains sand or loamy sand, and the material contains 15 percent or more rock fragments.
10 No Sandy and silty The soil texture class is sand or loamy sand and silt or silt loam.
11 No Silty The soil texture class is silt or silt loam.
12 No Silty and clayey The soil texture class is silt or silt loam and clay, sandy clay, or silty clay.
SSURGO Version: 2.2.3 Page 63
*/ //_____________________________________________________________________________

typedef std::string  parent_material_origin
; /* =
Length of Longest Choice Value: 41
1 No `A`a lava A type of lava flow having a rough, jagged, clinkery surface. Compare - pahoehoe lava. GG & MA
2 obsolete_Acidic-ash
3 No Amphibolite
4 No Andesite
5 obsolete_Andesitic-ash
6 No Rock anhydrite A sedimentary rock (evaporite) composed chiefly of mineral anhydrite (anhydrous CaSO4); The rock is generally massive, cryptocrystalline, and
may exhibit rhythmic sedimentation (rhymites). Compare - rock gypsum, rock halite. SW
7 No Anorthosite
8 No Arenite
9 No Argillite
10 No Arkose
11 No Basalt
12 obsolete_Basaltic-ash
13 obsolete_Basic-ash
14 No Bauxite An off-white to dark red brown weathered detritus or rock composed of aluminum oxides (mainly gibbsite with some boehmite and diaspore), iron
hydroxides, silica, silt, and especially clay minerals. Bauxite originates in tropical and subtropical environments as highly weathered residue from
carbonate or silicate rocks and can occur in concretionary, earthy, pisolitic or oolitic forms. SW & GG
15 No Non-volcanic breccia
16 No Acidic Non-volcanic breccia
17 No Basic Non-volcanic breccia
18 No Chalk
19 No Chert A hard, extremely dense or compact, dull to semivitreous, cryptocrystalline sedimentary rock, consisting dominantly of interlocking crystals of
quartz less than about 30 mm in diameter; it may contain amorphous silica (opal). It sometimes contains impurities such as calcite, iron oxide, or
the remains of silicious and other organisims. It has a tough, splintery to conchoidal fracture and may be white or variously colored gray, green,
blue, pink, red, yellow, brown, and black. Chet occurs principally as nodular or concretionary segregations in limestones and dolomites.
20 obsolete_Cinders Uncemented vitric, vesicular, pyroclastic material, more than 2.0 mm in at least one dimension, with an apparent specific gravity (including
vesicles) of more than 1.0 and less than 2.0. Compare - ash [volcanic], block [volcanic], lapilli, tephra. KST
21 No Claystone
22 No Coal
23 No Calcareous conglomerate A coarse-grained, clastic sedimentary rock composed of rounded to subangular rock fragments larger than 2 mm, commonly with a matrix of
sand and finer material; cements include silica, calcium carbonate, and iron oxides. The consolidated equivalent of gravel.
24 obsolete_Noncalcareous conglomerate A coarse-grained, clastic sedimentary rock composed of rounded to subangular rock fragments larger than 2 mm, commonly with a matrix of
sand and finer material; cements include silica, calcium carbonate, and iron oxides. The consolidated equivalent of gravel.
25 No Conglomerate
26 No Dacite
27 No Diabase
28 No Diorite
29 No Dolomite A carbonate sedimentary rock consisting chiefly (more than 50 percent by weight or by areal percentages under the microscope) of the mineral
dolomite.
30 obsolete_Ejecta-ash Unconsolidated, pyroclastic material less than 2 mm in all dimensions. Commonly called "volcanic ash". Compare - block [volcanic], cinders,
lapilli, tephra.
31 No Fanglomerate
32 No Gabbro
33 obsolete_Glauconite
34 No Gneiss
35 No Biotite gneiss
36 No Granodioritic gneiss
37 No Hornblende gneiss
38 No Migmatitic gneiss
39 No Muscovite-biotite gneiss
40 obsolete_Gneiss-acidic
41 obsolete_Gneiss-basic
42 No Granite
43 No Granite and gneiss
44 No Granitoid a) In the IUGS classification, a preliminary term for (for field use) for a plutonic rock with Q (quartz) between 20 and 40 (%). b) A general term
for all phaneritic igneous rocks (mineral crystals visible unaided and all about the same size) dominated by quartz and feldspars.
45 No Granodiorite
46 No Granofels
47 No Granulite
48 No Graywacke
49 No Greenstone
50 No Rock gypsum A sedimentary rock (evaporite) composed primarily of mineral gypsum (CaSO4.2H2O). The rock is generally massive, ranges from coarse
crystalline to fine granular, may show disturbed bedding due to hydration expansion of parent anhydrite (anhydrous CaSO4), and may exhibit
rhythmic sedimentation (rhymites). Compare - gypsite. GG
51 No Rock halite A sedimentary rock (evaporite) composed primarily of halite (NaCl). SW
52 No Hornfels
53 Igneous and metamorphic rock No
54 Igneous and sedimentary rock No
55 obsolete_Acid igneous rock
56 obsolete_Basic igneous rock
57 obsolete_Coarse igneous crystal
58 obsolete_Fine igneous crystal
59 obsolete_Intermediate igneous rock
60 Igneous, metamorphic and sedimentary rock No
61 obsolete_Ultrabasic igneous rock
62 No Igneous rock
63 No Ignimbrite
64 Interbedded sedimentary rock No
65 No Latite
66 No Limestone and dolomite
67 No Limestone and sandstone
68 No Limestone and shale
69 No Limestone and siltstone
70 No Arenaceous limestone
71 No Argillaceous limestone
72 No Cherty limestone
73 No Coral limestone An informal term for massive limestone composed primarily of coral and coral fragments commonly associated with marine islands or coral reefs
in tropical or subtropical waters. Compare - coral island. SW
74 No Phosphatic limestone
75 Limestone, sandstone, and shale No
76 No Limestone A sedimentary rock consisting chiefly (more than 50 percent) of calcium carbonate, primarily in the form of calcite. Limestones are usually
formed by a combination of organic and inorganic processes and include chemical and clastic (soluble and insoluble) constituents; many contain
fossils.
77 No Limonite A general 'field' term for various brown to yellowish brown, amorphous- to- cryptocrystalline hydrous ferric oxides that are an undetermined
mixture of goethite, hematite, and lepidocrocite formed by weathering and iron oxidation from iron-bearing, rocks and minerals. SW & GG
78 No Marble
79 obsolete_Marl An earthy, unconsolidated deposit consisting chiefly of calcium carbonate mixed with clay in approximately equal proportions (35 to 65 percent of
each); formed primarily under freshwater lacustrine conditions, but varieties associated with more saline environments also occur.
80 No Metaconglomerate
81 Metamorphic and sedimentary rock
No
82 obsolete_Acidic metamorphic rock
83 obsolete_Basic metamorphic rock
84 No Metamorphic rock Rock of any origin altered in mineralogical composition, chemical composition, or structure by heat, pressure, and movement at depth in the
earth's crust. Nearly all such rocks are crystalline. Examples: schist, gneiss, quartzite, slate, marble.
85 No Metaquartzite
86 No Metasedimentary rock
87 No Metasiltstone
88 No Metavolcanics
89 No Migmatite
90 obsolete_Mixed
91 obsolete_Mixed-calcareous
92 obsolete_Mixed-noncalcareous
93 No Monzonite
94 No Mudstone a) a blocky or massive, fine-grained sedimentary rock in which the proportions of clay and silt are approximately equal b) A general term that
includes clay, silt, claystone, siltstone, shale, and argillite, and that should be used only when the amounts of clay and silt are not known or
cannot be precisely identified.
95 No Mylonite
96 No Novaculite A dense, extremely finely grained, even-textured, siliceous, sedimentary rock similar to chert. It is hard, white to grayish-black in color,
translucent on thin edges, has a dull to waxy luster, and displays smooth conchoidal fracture when broken.
Novaculite principally occurs in the Marathon Uplift of Texas and Ouachita Mountains of Arkansas and Oklahoma where it forms erosion resistant
ridges. Novaculite appears to form from chert recrystallization with microcrystalline quartz dominant over cryptocrystalline chalcedony. At the
Ouachita Mountains type occurrence, novaculite formed by low-grade, thermal metamorphism of bedded chert. Novaculite is commercially
quarried as a whetstone or oilstone. Compare - chert. GG & SW
97 No Obsidian
98 No Orthoquartzite
99 No Pahoehoe lava A type of basaltic lava flow having a smooth, billowy or rope-like surface. Compare - a'a lava.
100 No Peridotite
101 No Phyllite
102 No Porcellanite An indurated or baked clay or shale with a dull, light-colored, cherty appearance, often found in the roof or floor of a burned-out coal seam.
103 No Pumice A light-colored, vesicular, glassy rock commonly having the composition of rhyolite. It commonly has a specific gravity of < 1.0 and is thereby
sufficiently buoyant to float on water. Compare - scoria, tephra.
104 No Pyroclastic rock
105 No Pyroxenite
106 No Quartz-diorite
107 No Quartzite
108 No Quartz-monzonite
109 No Rhyolite
110 No Sandstone and shale
111 No Sandstone and siltstone
112 No Calcareous sandstone
113 No Glauconitic sandstone
114 obsolete_Noncalcareous sandstone
115 No Sandstone Sedimentary rock containing dominantly sand-size clastic particles.
116 No Volcanic sandstone
117 obsolete_Schist and phyllite
118 obsolete_Acidic schist
119 obsolete_Basic schist
120 No Graphitic schist
121 No Mica schist
122 No Schist
123 No Scoria Vesicular, cindery crust or bomb-sized fragments of such material on the surface of andesitic or basaltic lava, the vesicular nature of which is due
to the escape of volcanic gases before solidification; it is usually heavier, darker, and more crystalline than pumice. Synonym - cinder.
Compare - pumice, tephra.
124 No Sedimentary rock A consolidated deposit of clastic particles, chemical precipitates, and organic remains accumulated at or near the surface of the earth under
"normal" low temperature and pressure conditions. Sedimentary rocks include consolidated equivalents of alluvium, colluvium, drift, and eolian,
lacustrine, marine deposits; e.g., sandstone, siltstone, mudstone, clay-stone, shale, conglomerate, limestone, dolomite, coal, etc. Compare -
sediment.
125 No Serpentinite
126 No Shale and siltstone
127 No Acid shale
128 No Calcareous shale
129 No Clayey shale
130 obsolete_Noncalcareous shale
131 No Shale Sedimentary rock formed by induration of a clay, silty clay, or silty clay loam deposit and having the tendency to split into thin layers, i.e., fissility.
132 No Calcareous siltstone
133 obsolete_Noncalcareous siltstone
134 No Siltstone Sedimentary rock containing dominantly silt-size clastic particles.
135 No Slate
136 No Sulfidic slate
137 No Soapstone
138 No Syenite
139 No Syenodiorite
140 No Tachylite
141 No Tonalite
142 No Trachyte
143 No Travertine
144 No Tufa
145 No Tuff breccia
146 No Acidic tuff
147 No Basic tuff
148 No Tuff A compacted deposit that is 50 percent or more volcanic ash and dust.
149 No Welded tuff
150 No Ultramafic rock
151 Volcanic and metamorphic rock No
152 Volcanic and sedimentary rock  No
153 obsolete_Volcanic bombs
154 No Acidic volcanic breccia
155 No Basic volcanic breccia
156 No Volcanic breccia
157 No Volcanic rock A generally fine-grained or glassy igneous rock resulting from volcanic action at or near the Earth's surface, either ejected explosively or extruded
as lava. The term includes near-surface intrusions that form a part of the volcanic structure.
*/
//_____________________________________________________________________________
typedef std::string  plasticity
; /* =
Length of Longest Choice Value: 18
1 No Nonplastic A roll of soil 4cm long x 6mm diameter cannot support itself when held on end.
2 No Slightly plastic A roll of soil 4cm long x 6mm diameter supports itself when held on end; a 4mm roll does not.
3 No Moderately plastic A roll of soil 4cm long x 4mm diameter supports itself when held on end; a 2mm roll does not.
4 No Very plastic A roll of soil 4cm long x 2mm diameter supports itself when held on end.
*/
//_____________________________________________________________________________
typedef std::string  ponding_duration_class
; /* = 
Length of Longest Choice Value: 10
1 No Very brief 4 hours to 48 hours
2 No Brief 2 days to 7 days
3 No Long 7 days to 30 days
4 No Very long More than 30 days
*/ //_____________________________________________________________________________
typedef std::string  ponding_frequency_class
; /* = 
Length of Longest Choice Value: 10
1 No None No reasonable possibility of ponding, near 0 percent chance on ponding in any year.
2 No Rare Ponding unlikely but possible under unusual weather conditions; from nearly 0 to 5 percent chance of ponding in any year, or nearly 0 to 5 times
in 100 years.
3 No Occasional Ponding is expected infrequently under usual weather conditions; 5 to 50 percent chance of ponding in any year, or 5 to 50 times in 100 years.
4 obsolete_Common
5 No Frequent Ponding is likely to occur under usual weather conditions; more than 50 percent chance in any year, or more than 50 times in 100 years.
*/ //_____________________________________________________________________________
typedef std::string  ponding_frequency_map_legend
; /* = 
Length of Longest Choice Value: 7
1 No 0-14%
2 No 15-49%
3 No 50-74%
4 No 75-100%
SSURGO Version: 2.2.3 Page 70
*/ //_____________________________________________________________________________

typedef std::string  pore_continuity_vertical
; /* = 
Length of Longest Choice Value: 8
1 No Low <1 cm vertical distance
2 No Moderate 1 to <10 cm vertical distance.
3 No High =>10 cm vertical distance.
*/ //_____________________________________________________________________________
typedef std::string  pore_root_size
; /* = 
Length of Longest Choice Value: 19
1 obsolete_Micro
2 obsolete_Micro and fine
3 obsolete_Micro to medium
4 No Very fine <1 mm in diameter.
5 obsolete_Very fine and fine <2 mm in diameter
6 obsolete_Very fine to medium <5 mm in diameter
7 obsolete_Very fine to coarse <10 mm in diameter
8 No Fine 1 to <2 mm in diameter.
9 obsolete_Fine and medium 1 to <5 mm in diameter
10 obsolete_Fine to coarse 1 to <10 mm in diameter
11 No Medium 2 to <5 mm in diameter.
12 obsolete_Medium and coarse 2 to <10 mm in diameter
13 No Coarse 5 to <10 mm in diameter.
14 No Very coarse =>10 mm in diameter.
*/ //_____________________________________________________________________________
typedef std::string  pore_shape
; /* = 
Length of Longest Choice Value: 27
1 obsolete_Constricted tubular
2 obsolete_Continuous tubular
3 No Dendritic tubular Cylindrical, elongated, branching voids (e.g. empty root channels).
4 obsolete_Discontinuous tubular
5 obsolete_Filled with coarse material
6 No Interstitial Primary packing voids between soil particles (e.g. voids between sand grains and rock fragments).
7 obsolete_Interstitial and tubular
8 No Irregular Non-connected cavities or chambers of various shapes (e.g. vughs).
9 obsolete_Total porosity
10 No Tubular Cylindrical, elongated voids (e.g. worm tunnels).
11 No Vesicular Ovoid to spherical shaped voids (e.g. solidified gaseous bubbles concentrated just below a crust).
12 obsolete_Vesicular and tubular
13 obsolete_Void between rock fragments
*/ //_____________________________________________________________________________
typedef std::string  potential_frost_action
; /* = 
Length of Longest Choice Value: 8
1 No None
2 No Low
3 No Moderate
4 No High
*/ //_____________________________________________________________________________
typedef std::string  restriction_kind
; /* = 
Length of Longest Choice Value: 44
1 No Abrupt textural change This term is meant to be used as defined in Soil Taxonomy excluding the control section requirement, i.e. this term applies to the entire soil
profile. It is characterized by a considerable increase in clay content within a very short vertical distance in the zone of contact. In the context of
how it is to be used for identifying a kind of restriction, it is root restrictive. See the Keys to Soil Taxonomy for additional details.
2 No Densic bedrock This is composed of non-cemented material that is commonly or locally referred to as "bedrock". It meets the criteria of "densic materials" as
defined in Soil Taxonomy.
3 No Lithic bedrock Material underlying a Lithic Contact as defined in Soil Taxonomy.
The material is virtually continuous within the limits of a pedon. Cracks that can be penetrated by roots are 10 cm or more apart. When moist,
hand digging with a spade is impractical although the material may be chipped or scratched. Rupture resistance class is at least strongly
cemented. Commonly, the material is indurated.
4 No Paralithic bedrock Material underlying a Paralithic Contact as defined in Soil Taxonomy.
The material is virtually continuous within the limits of a pedon. Cracks that can be penetrated by roots are 10 cm or more apart. Rupture
resistance is extremely weakly cemented to moderately cemented. Commonly, the material is partially weathered bedrock or weakly
consolidated bedrock such as sandstone, siltstone or shale.
5 No Cemented horizon Cemented earthy material that does not meet the criteria for any other specificly defined types. This material does not slake in water.
6 No Dense material Material underlying a densic contact as defined in Soil Taxonomy.
The material is virtually continuous within the limits of a pedon. Cracks that can be penetrated by roots are 10 cm or more apart. The material is
relatively unaltered and has a noncemented rupture resistance class. Commonly, the material is earthy material such as till, volcanic mudflows,
and mechanically compacted materials, but noncemented rocks can be densic materials if they are dense or resistance enough to keep roots
from entering, except in cracks.
7 No Duripan
8 No Fragipan
9 Human-manufactured
materials
No Nearly continuous, horizontally oriented human-manufactured materials. Examples include geotextile liners, asphalt, concrete, rubber, and plastic.
10 No Natric
11 No Ortstein
12 No Permafrost
13 No Petrocalcic
14 No Petroferric
15 No Petrogypsic
16 No Placic
17 No Plinthite
18 No Salic
19 Strongly contrasting textural
stratification
No 1) The same as "strongly contrasting particle-size classes" described in the Keys to Soil Taxonomy except that the thickness requirement of
12.5 cm or more for each of the contrasting particle-size classes is waived. The term is applied to the entire soil profile not just the particle-size
control section. In the context of how it is to be used for identifying a kind of restriction, it is root restrictive. 2) Stratified soil textures that differ
significantly enough as to restrict the movement of water and air through the soil, or that provide an unfavorable root environment. It is in all
cases root restrictive.
20 No Sulfuric
21 obsolete_Undefined
*/
//_____________________________________________________________________________
typedef std::string  rule_design
; /* = 
Length of Longest Choice Value: 11
1 No class The rule is designed to result in the soil being interpreted as a member of a discrete class. Reportable features are those with fuzzy values
closest to 1. The fuzzy values of child-rules will be sorted in descending order.
2 No limitation The rule is designed in a manner such that the higher the fuzzy value, the more limited the soil is for the stated use. The fuzzy values, of childrules,
closest to 1 represent the most limiting features and will be sorted in descending order.
3 No suitability The rule is designed in a manner such that the higher the fuzzy value, the better suited the soil is for the stated use. The fuzzy values, of childrules,
closest to 0 represent the most limiting features and will be sorted in ascending order.
*/
//_____________________________________________________________________________
typedef std::string  runoff
; /* = 
Length of Longest Choice Value: 10
1 obsolete_Ponded
2 No Negligible
3 No Very low
4 No Low
5 No Medium
6 No High
7 No Very high
*/
//_____________________________________________________________________________
typedef std::string  rupture_resist_block_cem
; /* = 
Length of Longest Choice Value: 25
1 No Noncemented Stress applied ranges from 0 to 8 newtons. (SSM)
2 No Extremely weakly cemented Stress applied ranges from 8 to 20 newtons. (SSM)
3 No Very weakly cemented Stress applied ranges from 20 to 40 newtons. (SSM)
4 No Weakly cemented Stress applied ranges from 40 to 80 newtons. (SSM)
5 obsolete_Weakly cemented* Stress applied ranges from 8 to 80 newtons. (SSM)
6 No Moderately cemented Stress applied ranges from 80 to 160 newtons. (SSM)
7 obsolete_Moderately cemented* Stress applied ranges from 80 to 800 newtons. (SSM)
8 No Strongly cemented Stress applied ranges from 160 to 800 newtons. (SSM)
9 obsolete_Strongly cemented* Stress applied ranges from 800 newtons to 3 joules. (SSM)
10 No Very strongly cemented Stress applied ranges from 800 newtons to 3 joules. (SSM)
11 No Indurated Stress applied is greater than or equal 3 joules. (SSM)
12 obsolete_Extremely strong
13 obsolete_hard
14 obsolete_soft
SSURGO Version: 2.2.3 Page 74
*/ //_____________________________________________________________________________

typedef std::string  rupture_resist_block_dry
; /* = 
Length of Longest Choice Value: 15
1 No Loose Aggregated or block-type specimen not obtainable.
2 No Soft Stress applied ranges from 0 to 8 newtons. (SSM)
3 No Slightly hard Stress applied ranges from 8 to 20 newtons. (SSM)
4 obsolete_Somewhat hard
5 No Moderately hard Stress applied ranges from 20 to 40 newtons. (SSM)
6 No Hard Stress applied ranges from 40 to 80 newtons. (SSM)
7 No Very hard Stress applied ranges from 80 to 160 newtons. (SSM)
8 No Extremely hard Stress applied ranges from 160 to 800 newtons. (SSM)
9 No Rigid Stress applied ranges from 800 newtons to 3 joules. (SSM)
10 No Very rigid Stress applied is greater than or equal 3 joules. (SSM)
11 obsolete_Hard when dry Stress applied ranges from 20 to 80 newtons. (SSM)
*/
//_____________________________________________________________________________
typedef std::string  rupture_resist_block_moist
; /* = 
Length of Longest Choice Value: 25
1 No Loose Aggregated or block-type specimen not obtainable.
2 No Very friable Stress applied ranges from 0 to 8 newtons. (SSM)
3 No Friable Stress applied ranges from 8 to 20 newtons. (SSM)
4 obsolete_Slightly firm
5 No Firm Stress applied ranges from 20 to 40 newtons. (SSM)
6 No Very firm Stress applied ranges from 40 to 80 newtons. (SSM)
7 No Extremely firm Stress applied ranges from 80 to 160 newtons. (SSM)
8 obsolete_Extremely firm when moist Stress applied ranges from 80 to 800 newtons. (SSM)
9 obsolete_Extremely firm*
10 No Slightly rigid Stress applied ranges from 160 to 800 newtons. (SSM)
11 No Rigid Stress applied ranges from 800 newtons to 3 joules. (SSM)
12 No Very rigid Stress applied is greater than or equal 3 joules. (SSM)
*/
//_____________________________________________________________________________
typedef std::string  rupture_resist_plate
; /* = 
1 No Extremely weak
2 No Very weak
3 No Weak
4 No Moderate
5 No Moderately strong
6 No Strong
7 No Very strong
8 No Extremely strong
*/
//_____________________________________________________________________________
typedef std::string  sdv_attribute_logical_data_type
; /* = 
Length of Longest Choice Value: 7
1 No Choice
2 No Float
3 No Integer
4 No String
5 No Vtext
*/
//_____________________________________________________________________________
typedef std::string  site_index_curves
; /* = 
Length of Longest Choice Value: 53
1 No Gevorkiantz 1956a (010)
2 No Carmean, Hahn 1981 (011)
3 No Lloyd 1970a (020)
4 No Schumacher 1926 (030)
5 No Cochran 1979a (031)
6 No Dolph 1987 (032)
7 No SCS 1988a (035)
8 No Hoyer, Herman 1989 (05)
9 No Schumacher 1928 (050)
10 No Dolph 1991 (055)
11 Herman, Curtis, DeMars 1978 (060) No
12 No Lloyd 1971a (070)
13 No Carmean 1978 (071)
14 Brendemuehl, McComb, Thomson 1961 (075) No
15 No Lloyd 1971b (094)
16 No Carmean 1978 (095)
17 Worthington, Johnson, Staebler, Lloyd 1960 (100) No
18 No Harrington, Curtis 1986 (105)
19 No Lloyd 1971a (120)
20 No Carmean 1978 (121)
21 No Cooley 1958, 1962 (130)
22 No Carmean 1978 (131)
23 No Lloyd 1971a (140)
24 No Gregory, Haack 1965 (141)
25 No Boisen 1910 (150)
26 No Boisen 1910 (151)
27 No Boisen 1910 (153)
28 No Boisen 1910 (154)
29 No Boisen 1910 (155)
30 No Boisen 1910 (156)
31 No Boisen, Newlin 1910 (157)
32 No Boisen, Newlin 1910 (158)
33 No Korstian, Brush 1931 (160)
34 No Hampf 1965 (165)
35 No Carmean 1978 (166)
36 No Lloyd 1971a (170)
37 No Carmean 1978 (171)
38 No Kellog 1939a (190)
39 No Losche, Schlesinger (191)
40 Losche, Schlesinger 1975 (192)
41 No Howell 1940 (200)
42 No Chojnacky 1986 (202)
43 Barrett, Sauerwein 1982 (210)
44 No T.V.A. 1948 (220)
45 No Stone 1957 (230)
46 No Gevorkiantz 1957a (235)
47 No Aird, Stone 1955 (240)
48 No Cummings 1937 (260)
49 No Cochran 1985 (261)
50 Schmidt, Shearer, Roe 1976 (265) No
51 No Dolph 1983 (300)
52 No Broadfoot, Krinard 1959 (330)
53 No Carmean 1978 (331)
54 No Broadfoot 1969 (332)
55 No Trenk 1929 (340)
56 No Beck 1962 (350)
57 Schlaegel, Kulow, Baughman 1969 (355) No
58 No Beck 1962 (360)
59 No Applequist 1959 (390)
60 No Applequist 1959 (395)
61 No Brickell 1966 (410) (obsolete)
62 No Wlde 1965 (411)
63 No Alexander 1967 (412)
64 No Lloyd 1970a (420)
65 No Gevorkiantz 1957b (421)
66 No Carmean, Hahn 1981 (422)
67 No Ferber 1971 (430)
68 No Farr 1967 (440)
69 No Bevorkiantz 1957c (450)
70 No Lloyd 1970b (470)
71 No Meyer 1961 (490)
72 No Farr 1984 (491)
73 No Gevorkiantz 1956b (500)
74 Wilde, Lyer, Tanser, Trautmann, Watterston 1965 (501) No
75 No Wilde 1965 (502)
76 Schumancher, Coile 1960 (510) No
77 No Alexander 1966 (520)
78 No Hegyi 100TA 1979 (525)
79 Coile, Schumacher 1953 (530) No
80 No Nash 1963 (531)
81 No Gilmore, Metcalf 1961 (532)
82 No Langdon 1961 (540)
83 No Langdon 1959 (541)
84 No USDA 1929 (550)
85 No Barnes 1955 (555)
86 No Haig 1932 (570)
87 No USDA 1929 (580)
88 No Meyer 1961 (600)
89 No Minor 1964 (601)
90 No Dunning 1942 (605)
91 Biging and Wensel 1984 (615) No
92 Nelson, Clutter, Chaiken 1961 (620) No
93 Kulow, Sowers, Heesch 1966 (621) No
94 No Gevorkiantz 1957d (630)
95 No Wilde 1965 (631)
96 No Gilmore 1967 (632)
97 Illick, Aughanbaugh 1930 (635) No
98 Schumacher, Coile 1960 (640) No
99 No Doolittle 1960 (650)
100 No Gilmore 1968 (651)
101 No Lloyd 1970b (660)
102 No Gevorkiantz 1957e (670)
103 Coile, Schumacher 1953 (690) No
104 No Gilmore, Metcalf 1961 (691)
105 No Briscoe, Ferrill 1958 (700)
106 No Broadfoot 1960 (710)
107 No Neebe, Boyce 1959 (711)
108 No Brendemuehl 1965 (712)
109 No Gevorkiantz 1956c (720)
110 No Carmean 1978 (721)
111 No Gregory, Haack 1965 (725)
112 No Baker 1925 (730)
113 Edminster, Mowrer, Shepperd 1985 (735) No
114 No BCFS 1977 (740)
115 No Defler 1937 (750)
116 No Carmean 1978 (751)
117 Auchmoody, Rexrode 1984 (752) No
118 No SCS 1988b (765)
119 No Brickell 1968 (770)
120 No Monserud 1985 (771)
121 No Edminster Jump 1976 (775)
122 Curtis, Herman, DeMars
1974 (780) (obsolete) No
123 No DeMars, Herman 1987 (781)
124 McArdle, Meyer, Bruce 1961 (790) No
125 No King 1966 (795)
126 No Gevorkiantz 1957f (800)
127 No Grane, Bower 1971 (801)
128 No McQuilkin 1974, 1978 (802)
129 No Graney, Bower 1971 (803)
130 No Carmean 1971, 1972 (804)
131 No Carmean 1971, 1972 (805)
132 No Carmean 1971, 1972 (806)
133 No Carmean 1978 (807)
134 No Carmean 1971, 1972 (808)
135 No Carmean 1978 (809)
136 No Olson 1959 (810)
137 DeLasaux Pillsbury 1987 (811) No
138 No Sauerwein 1983 (812)
139 No Schnur 1937 (820)
140 No Broadfoot 1961 (840)
141 No Broadfoot 1963 (860)
142 No Powers 1972 (880)
143 No Kellogg 1939b (900)
144 No Lindquist, Palley 1963 (930)
145 Krumland, Wensel 1986 (935) No
146 Gevorkiantz 1957g (960) (obsolete) No
147 No Kurucz 50BH, 1978 (970)
148 No Barnes 1962 (990)
149 No Frothingham 1915 (991)
150 No Wiley 1978 (995)
*/
//_____________________________________________________________________________
typedef std::string  slope_shape
; /* = 
1 No Concave The land surface is shaped such that the slope gradient decreases down the slope, and runoff tends to decelerate as it flows down the slope. In
profile, the surface bows downward in the mid-section.
2 No Convex The land surface is shaped such that the slope gradient increases down the slope, and runoff tends to accelerate as it flows down the slope. In
profile, the surface bows upward in the mid-section.
3 No Linear The land surface is substantially a straight line when seen in profile at right angles to the contours -- planar.
4 obsolete_Undulating
5 obsolete_Complex
*/
//_____________________________________________________________________________
typedef std::string  soil_erodibility_factor
; /* = 
Length of Longest Choice Value: 3
1 No .02
2 No .05
3 No .10
4 No .15
5 No .17
6 No .20
7 No .24
8 No .28
9 No .32
10 No .37
11 No .43
12 No .49
13 No .55
14 No .64
*/
//_____________________________________________________________________________
typedef std::string  soil_moisture_status
; /* = 
Length of Longest Choice Value: 32
1 No Dry >1500 kPa (>15 bar) suction
2 No Moist =<1500 to 0.01 kPa ( =<15 bar to 0.00001 bar) suction.
3 Yes Saturation from capillary fringe
4 No Wet <0.01 kPa ( <0.00001 bar) suction; free water present (satiated wet).
5 obsolete_Frozen
*/
//_____________________________________________________________________________
typedef std::string  soil_slippage_potential
; /* = 
Length of Longest Choice Value: 15
1 No Low Low potential of slippage.
2 obsolete_Moderately low Moderately low hazzard of slippage.
3 No Medium Medium potential of slippage.
4 obsolete_Moderately high Moderately high hazard of slippage.
5 No High High potential of slippage.
*/
//_____________________________________________________________________________
typedef std::string  soil_survey_area_status
; /* = 
Length of Longest Choice Value: 18
1 No Extensive revision Soil Survey area has a published report that requires extensive revision, as defined in NSSH Part 610.06. The Director, Soil Survey Division,
has approved the survey area for updating and republication, and the survey area has a signed memorandum of understanding and staffing to
complete the fieldwork in 2 to 4 years.
2 No Initial Soil survey area has a signed Memorandum of Understanding and assigned staffing to complete the initial mapping and field documentation in 3
to 5 years.
3 No Nonproject Soil survey area has neither the initial mapping complete nor a signed correlation document.
4 No Out-of-date Soil survey area has a published report, but it no longer meets user needs; it requires extensive revision, as defined in NSSH Part 610.06.
5 No Published Soil survey area has been printed, or otherwise reproduced and issued by a Federal or State agency, and meets the current needs of users.
Publication is defined as a traditional hard copy printed report, CD-ROM, web publication, or other media as agreed to by the National
Cooperative Soil Survey cooperators in the memorandum of understanding.
6 No Update Soil survey area has a published report that requires some degree of revision (primarily to soil maps), as defined in NSSH Part 610.06. A
comprehensive evaluation documents deficiencies for the entire survey area, and National Cooperative Soil Survey cooperators have agreed on
the evaluation; staffing is assigned and other necessary resources are available to complete all revisions within 2 years or less.
7 No Update needed Soil survey area has a published report that requires some degree of revision (primarily to soil maps), as defined in NSSH Part 610.06. A
comprehensive evaluation documents deficiencies for the entire survey area, and National Cooperative Soil Survey cooperators have agreed on
the evaluation; however available resources do not dictate immediate project activities and a change to Maintenance status.
SSURGO Version: 2.2.3 Page 83
*/ //_____________________________________________________________________________

typedef std::string  soil_taxonomy_edition
; /* = 
Length of Longest Choice Value: 15
1 No tenth edition
2 No ninth edition
3 No eighth edition
4 No seventh edition
5 No sixth edition
6 No fifth edition
7 No fourth edition
8 No third edition
9 No second edition
10 No first edition
*/
//_____________________________________________________________________________
typedef std::string  stickiness
; /* = 
Length of Longest Choice Value: 17
1 No Nonsticky After release of pressure, practically no soil material adheres to the thumb or forefinger. (SSM)
2 No Slightly sticky After release of pressure, soil material adheres perceptible to both digits. As the digits are separated, the material tends to come off one or the
other rather cleanly. The material does not stretch appreciably on separation of the digits.
3 No Moderately sticky After release of pressure, soil material adheres to both digits and tends to stretch slightly rather than pull completely free from either digit.
4 No Very sticky After release of pressure, soil material adheres so strongly to both digits that it stretches decidely when the digits are separated. Soil material
remains on both digits.
*/
//_____________________________________________________________________________
typedef std::string  structure_grade
; /* =
Length of Longest Choice Value: 19
1 No Weak Individual soil units or aggregates are barely observable in place. When gently disturbed, the soil material parts into a mixture of whole and
broken units and much material that exhibits no planes of weakness. (SSM)
2 No Moderate Individual soil units or aggregates are well formed and evident in undisturbed soil. When disturbed, the soil material parts into a mixture of
mostly whole units, some broken units, and material not in units. (SSM)
3 No Strong Individual soil units or aggregates are distinct in undisturbed soil. When removed, the soil material parts mainly into whole units. (SSM)
4 obsolete_Weak and moderate
5 obsolete_Moderate and strong
6 No Structureless No individual soil units or aggregates are observable, either in place or following disturbance. (SSM)
7 obsolete_Very strong
*/
//_____________________________________________________________________________
typedef std::string  structure_size
; /* = 
Length of Longest Choice Value: 22
1 No Very fine Granular or platy: <1 mm
Columnar or prismatic: <10 mm
Angular or subangular blocky: <5 mm
2 obsolete_Very fine and fine
3 No Fine Granular: 1 to <2 mm
Columnar or prismatic: 10 to <20 mm
Angular or subangular blocky: 5 to <10 mm
4 obsolete_Fine and medium
5 No Medium Granular or platy: 2 to <5 mm
Columnar or prismatic: 20 to <50 mm
Angular or subangular blocky: 10 to <20 mm
6 obsolete_Medium and coarse
7 No Coarse Granular: 5 to <10 mm
Columnar or prismatic: 50 to <100mm
Angular or subangular blocky: 20 to <50mm
8 obsolete_Coarse and very coarse
9 No Very coarse Granular: =>10mm
Columnar or prismatic: 100 to <500mm
Angular or subangular blocky: =>50mm
10 No Very thin <1mm
11 No Thin 1 to <2mm
12 No Thick 5 to <10mm
13 No Very thick =>10mm
14 No Extremely coarse Granular: n/a
Columnar or prismatic: =>500mm
Angular or subangular blocky: n/a
15 obsolete_Extremely fine
16 obsolete_Fine to coarse
*/
//_____________________________________________________________________________
typedef std::string  structure_type
; /* = 
Length of Longest Choice Value: 17
1 No Angular blocky Polyhedrals with faces that intersect at sharp angles (planes).
2 obsolete_Blocky
3 No Cloddy Irregular blocks created by artificial disturbance - i.e. tillage operations or compaction.
4 No Columnar Vertically elongated units with rounded tops which commonly are "bleached".
5 obsolete_Crumb
6 No Granular Small polyhedrals with curved or very irregular faces.
7 No Lenticular platy
8 No Massive No structural units. Material is a coherent mass (not necessarily cemented).
9 No Platy Flat or tabular-like units.
10 No Prismatic Vertically elongated units with flat tops.
11 No Single grain No structural units. Material is entirely noncoherent.
12 No Subangular blocky Polyhedrals with sub-rounded and planar faces, lacking sharp angles.
13 No Wedge Elliptical, interlocking lenses that teminate in acute angles, bounded by slickensides; not limited to vertic materials.
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_c_e_act_class
; /* = 
Length of Longest Choice Value: 11
1 No not used
2 No subactive The CEC7 to clay ratio is less than 0.24.
3 No semiactive The CEC7 to clay ratio is 0.24 to 0.40.
4 No active The CEC7 to clay ratio is 0.40 to 0.60.
5 No superactive The CEC7 to clay ratio is greater than or equal to 0.60.
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_mineralogy
; /* = 
Length of Longest Choice Value: 29
1 No allitic
2 No amorphic
3 obsolete_calcareous
4 No carbonatic
5 obsolete_chloritic
6 obsolete_clastic
7 No coprogenous
8 No diatomaceous
9 No ferrihumic
10 No ferrihydritic
11 No ferritic
12 No ferruginous
13 No gibbsitic
14 No glassy
15 No glauconitic
16 No gypsic
17 No halloysitic
18 No illitic
19 obsolete_illitic (calcareous)
20 No isotic
21 No kaolinitic
22 No magnesic
23 No marly
24 No micaceous
25 obsolete_micaceous (calcareous)
26 No mixed
27 obsolete_mixed (calcareous)
28 obsolete_montmorillonitic
29 obsolete_montmorillonitic (calcareous)
30 No not used
31 obsolete_oxidic
32 No paramicaceous
33 No parasesquic
34 obsolete_sepiolitic
35 obsolete_serpentinitic
36 No sesquic
37 No siliceous
38 obsolete_siliceous (calcareous)
39 No smectitic
40 obsolete_unclassified
41 No vermiculitic
42 obsolete_vermiculitic (calcareous)
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_other
; /* = 
Length of Longest Choice Value: 18
1 No coated
2 No cracked
3 obsolete_level
4 No micro
5 No not used
6 No ortstein
7 obsolete_ortstein & shallow
8 No shallow
9 obsolete_shallow & coated
10 obsolete_shallow & uncoated
11 obsolete_sloping
12 obsolete_unclassified
13 No uncoated
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_part_size_mod
; /* =
Length of Longest Choice Value: 9
1 No aniso This is used only to indicate that more than one pair of contrasting particle size families exist within the control section. (see Soil Taxonomy)
2 obsolete_not aniso
3 No not used Used to indicate that the soil does not qualify as "aniso".
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_particle_size
; /* =
Length of Longest Choice Value: 56
1 No ashy
2 No ashy over clayey
3 No ashy over clayey-skeletal
4 No ashy over loamy
5 No ashy over loamy-skeletal
6 No ashy over medial
7 No ashy over medial-skeletal
8 ashy over pumiceous or cindery No
9 ashy over sandy or sandyskeletal No
10 No ashy-pumiceous
11 No ashy-skeletal
12 ashy-skeletal over
fragmental or cindery
No
13 ashy-skeletal over loamyskeletal
No
14 ashy-skeletal over sandy or
sandy-skeletal
No
15 No cindery
16 No cindery over loamy
17 No cindery over medial
18 No cindery over medial-skeletal
19 cindery over sandy or sandyskeletal Yes
20 No clayey
21 obsolete_clayey over fine-silty
22 No clayey over fragmental
23 No clayey over loamy
24 No clayey over loamy-skeletal
25 clayey over sandy or sandyskeletal No
26 No clayey-skeletal
27 clayey-skeletal over sandy or sandy-skeletal No
28 No coarse-loamy
29 No coarse-loamy over clayey
30 No coarse-loamy over fragmental
31 coarse-loamy over sandy or sandy-skeletal No
32 No coarse-silty
33 No coarse-silty over clayey
34 obsolete_coarse-silty over fragmental
35 coarse-silty over sandy or sandy-skeletal No
36 No fine
37 No fine-loamy
38 No fine-loamy over clayey
39 No fine-loamy over fragmental
40 fine-loamy over sandy or sandy-skeletal No
41 No fine-silty
42 No fine-silty over clayey
43 No fine-silty over fragmental
44 fine-silty over sandy or sandy-skeletal No
45 No fragmental
46 No hydrous
47 No hydrous over clayey
48 No hydrous over clayey-skeletal
49 No hydrous over fragmental
50 No hydrous over loamy
51 No hydrous over loamy-skeletal
52 hydrous over sandy or sandyskeletal No
53 No hydrous-pumiceous
54 No hydrous-skeletal
55 No loamy
56 loamy over ashy or ashypumiceous No
57 loamy over pumiceous or cindery No
58 loamy over sandy or sandyskeletal No
59 No loamy-skeletal
60 loamy-skeletal or clayeyskeletal Yes
61 No loamy-skeletal over cindery
62 No loamy-skeletal over clayey
63 loamy-skeletal over fragmental No
64 loamy-skeletal over sandy or sandy-skeletal No
65 No medial
66 No medial over ashy
67 medial over ashy-pumiceous or ashy-skeletal No
68 No medial over clayey
69 No medial over clayey-skeletal
70 No medial over fragmental
71 No medial over hydrous
72 No medial over loamy
73 No medial over loamy-skeletal
74 medial over pumiceous or cindery No
75 medial over sandy or sandyskeletal No
76 obsolete_medial over thixotropic
77 No medial-pumiceous
78 No medial-skeletal
79 medial-skeletal over fragmental or cindery No
80 medial-skeletal over loamyskeletal No
81 medial-skeletal over sandy or sandy-skeltal No
82 No not used
83 No pumiceous
84 pumiceous or ashypumiceous over loamy No
85 pumiceous or ashypumiceous over loamy-skeltal No
86 pumiceous or ashypumiceous over medial No
87 pumiceous or ashypumiceous over medialskeletal No
88 pumiceous or ashypumiceous over sandy or sandy-skeletal No
89 No sandy
90 No sandy or sandy-skeletal
91 No sandy over clayey
92 No sandy over loamy
93 No sandy-skeletal
94 obsolete_sandy-skeletal over clayey
95 No sandy-skeletal over loamy
96 obsolete_thixotropic
97 obsolete_thixotropic over fragmental
98 obsolete_thixotropic over loamy
99 thixotropic over loamyskeletal Yes
100 thixotropic over sandy or sandy-skeletal Yes
101 obsolete_thixotropic-skeletal
102 obsolete_unclassified
103 No very-fine
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_reaction
; /* =
Length of Longest Choice Value: 13
1 No acid
2 No allic
3 No calcareous
4 No dysic
5 No euic
6 No nonacid
7 obsolete_noncalcareous
8 No not used
9 obsolete_unclassified
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_family_temp_class
; /* = 
Length of Longest Choice Value: 15
1 No frigid
2 No hypergelic
3 No hyperthermic
4 No isofrigid
5 No isohyperthermic
6 No isomesic
7 No isothermic
8 No mesic
9 No not used
10 No pergelic
11 No subgelic
12 No thermic
13 obsolete_unclassified
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_great_group
; /* = 
Length of Longest Choice Value: 16
1 No Acraquox
2 obsolete_Acrohumox
3 No Acroperox
4 obsolete_Acrorthox
5 No Acrotorrox
6 No Acrudox
7 No Acrustox
8 obsolete_Agrudalfs
9 No Alaquods
10 No Albaqualfs
11 No Albaquults
12 No Alorthods
13 obsolete_Andaquepts
14 No Anhyorthels
15 No Anhyturbels
16 No Anthracambids
17 No Aquicambids
18 No Aquisalids
19 No Aquiturbels
20 No Aquorthels
21 obsolete_Arents
22 No Argialbolls
23 No Argiaquolls
24 obsolete_Argiborolls
25 No Argicryids
26 No Argicryolls
27 No Argidurids
28 No Argigypsids
29 No Argiorthels
30 No Argiudolls
31 No Argiustolls
32 No Argixerolls
33 obsolete_Borofibrists
34 obsolete_Borofolists
35 obsolete_Borohemists
36 obsolete_Borosaprists
37 No Calciaquerts
38 No Calciaquolls
39 No Calciargids
40 obsolete_Calciborolls
41 No Calcicryepts
42 No Calcicryids
43 No Calcicryolls
44 No Calcigypsids
45 obsolete_Calciorthids
46 No Calcitorrerts
47 No Calciudolls
48 No Calciustepts
49 No Calciusterts
50 No Calciustolls
51 No Calcixerepts
52 No Calcixererts
53 No Calcixerolls
54 obsolete_Camborthids
55 obsolete_Chromoxererts
56 obsolete_Chromuderts
57 obsolete_Chromusterts
58 obsolete_Cryandepts
59 No Cryaqualfs
60 No Cryaquands
61 No Cryaquents
62 No Cryaquepts
63 No Cryaquods
64 No Cryaquolls
65 obsolete_Cryoboralfs
66 obsolete_Cryoborolls
67 obsolete_Cryochrepts
68 No Cryofibrists
69 No Cryofluvents
70 No Cryofolists
71 No Cryohemists
72 obsolete_Cryohumods
73 No Cryopsamments
74 No Cryorthents
75 obsolete_Cryorthods
76 No Cryosaprists
77 No Cryrendolls
78 obsolete_Cryumbrepts
79 obsolete_Durandepts
80 No Duraqualfs
81 No Duraquands
82 No Duraquerts
83 No Duraquods
84 No Duraquolls
85 obsolete_Durargids
86 No Duricryands
87 No Duricryods
88 No Duricryolls
89 No Durihumods
90 No Duritorrands
91 No Durixeralfs
92 No Durixerepts
93 No Durixererts
94 No Durixerolls
95 obsolete_Durochrepts
96 obsolete_Durorthids
97 No Durorthods
98 No Durudands
99 No Durudepts
100 No Durustalfs
101 No Durustands
102 No Durustepts
103 No Durustolls
104 obsolete_Dystrandepts
105 No Dystraquerts
106 obsolete_Dystrochrepts
107 No Dystrocryepts
108 No Dystrogelepts
109 obsolete_Dystropepts
110 No Dystroxerepts
111 No Dystrudepts
112 No Dystruderts
113 No Dystrustepts
114 No Dystrusterts
115 No Endoaqualfs
116 No Endoaquands
117 No Endoaquents
118 No Endoaquepts
119 No Endoaquerts
120 No Endoaquods
121 No Endoaquolls
122 No Endoaquults
123 No Epiaqualfs
124 No Epiaquands
125 No Epiaquents
126 No Epiaquepts
127 No Epiaquerts
128 No Epiaquods
129 No Epiaquolls
130 No Epiaquults
131 obsolete_Eutrandepts
132 No Eutraquox
133 obsolete_Eutroboralfs
134 obsolete_Eutrochrepts
135 obsolete_Eutrocryepts
136 No Eutrogelepts
137 obsolete_Eutropepts
138 No Eutroperox
139 obsolete_Eutrorthox
140 No Eutrotorrox
141 No Eutrudepts
142 No Eutrudox
143 No Eutrustox
144 obsolete_Ferrods
145 No Ferrudalfs
146 No Fibristels
147 No Fluvaquents
148 No Folistels
149 No Fragiaqualfs
150 No Fragiaquepts
151 No Fragiaquods
152 No Fragiaquults
153 obsolete_Fragiboralfs
154 No Fragihumods
155 obsolete_Fragiochrepts
156 No Fragiorthods
157 No Fragiudalfs
158 No Fragiudepts
159 No Fragiudults
160 obsolete_Fragiumbrepts
161 No Fragixeralfs
162 No Fragixerepts
163 No Fraglossudalfs
164 No Fulvicryands
165 No Fulvudands
166 No Gelaquands
167 No Gelaquents
168 No Gelaquepts
169 obsolete_Gelicryands
170 No Gelifluvents
171 No Gelorthents
172 obsolete_Gibbsiaquox
173 obsolete_Gibbsihumox
174 obsolete_Gibbsiorthox
175 No Glacistels
176 No Glossaqualfs
177 obsolete_Glossoboralfs
178 No Glossocryalfs
179 No Glossudalfs
180 No Gypsiargids
181 No Gypsicryids
182 obsolete_Gypsiorthids
183 No Gypsitorrerts
184 No Gypsiusterts
185 No Halaquepts
186 No Haplanthrepts
187 obsolete_Haplaquands
188 obsolete_Haplaquents
189 obsolete_Haplaquepts
190 obsolete_Haplaquods
191 obsolete_Haplaquolls
192 No Haplaquox
193 No Haplargids
194 obsolete_Haploborolls
195 No Haplocalcids
196 No Haplocambids
197 No Haplocryalfs
198 No Haplocryands
199 No Haplocryepts
200 No Haplocryerts
201 No Haplocryids
202 No Haplocryods
203 No Haplocryolls
204 No Haplodurids
205 No Haplofibrists
206 No Haplogelods
207 No Haplogelolls
208 No Haplogypsids
209 No Haplohemists
210 No Haplohumods
211 obsolete_Haplohumox
212 No Haplohumults
213 No Haploperox
214 No Haplorthels
215 No Haplorthods
216 obsolete_Haplorthox
217 No Haplosalids
218 No Haplosaprists
219 No Haplotorrands
220 No Haplotorrerts
221 No Haplotorrox
222 No Haploturbels
223 No Haploxeralfs
224 No Haploxerands
225 No Haploxerepts
226 No Haploxererts
227 No Haploxerolls
228 No Haploxerults
229 No Hapludalfs
230 No Hapludands
231 obsolete_Hapludepts
232 No Hapluderts
233 No Hapludolls
234 No Hapludox
235 No Hapludults
236 obsolete_Haplumbrepts
237 No Haplustalfs
238 No Haplustands
239 No Haplustepts
240 No Haplusterts
241 No Haplustolls
242 No Haplustox
243 No Haplustults
244 No Haprendolls
245 No Hemistels
246 No Historthels
247 No Histoturbels
248 No Humaquepts
249 No Humicryepts
250 No Humicryerts
251 No Humicryods
252 No Humigelods
253 obsolete_Humitropepts
254 obsolete_Hydrandepts
255 No Hydraquents
256 No Hydrocryands
257 No Hydrudands
258 No Kandiaqualfs
259 No Kandiaquults
260 No Kandihumults
261 No Kandiperox
262 No Kandiudalfs
263 No Kandiudox
264 No Kandiudults
265 No Kandiustalfs
266 No Kandiustox
267 No Kandiustults
268 No Kanhaplaquults
269 No Kanhaplohumults
270 No Kanhapludalfs
271 No Kanhapludults
272 No Kanhaplustalfs
273 No Kanhaplustults
274 obsolete_Luvifibrists
275 No Luvihemists
276 obsolete_Medifibrists
277 obsolete_Medifolists
278 obsolete_Medihemists
279 obsolete_Medisaprists
280 No Melanaquands
281 No Melanocryands
282 No Melanoxerands
283 No Melanudands
284 No Molliturbels
285 No Mollorthels
286 obsolete_Nadurargids
287 No Natralbolls
288 No Natraqualfs
289 No Natraquerts
290 No Natraquolls
291 No Natrargids
292 obsolete_Natriboralfs
293 obsolete_Natriborolls
294 No Natricryolls
295 No Natridurids
296 No Natrigypsids
297 No Natrixeralfs
298 No Natrixerolls
299 No Natrudalfs
300 No Natrudolls
301 No Natrustalfs
302 No Natrustolls
303 obsolete_Ochraqualfs
304 obsolete_Ochraquox
305 obsolete_Ochraquults
306 No Paleaquults
307 No Paleargids
308 obsolete_Paleboralfs
309 obsolete_Paleborolls
310 No Palecryalfs
311 No Palecryolls
312 No Palehumults
313 obsolete_Paleorthids
314 No Paleudalfs
315 No Paleudolls
316 No Paleudults
317 No Paleustalfs
318 No Paleustolls
319 No Paleustults
320 No Palexeralfs
321 No Palexerolls
322 No Palexerults
323 obsolete_Pelloxererts
324 obsolete_Pelluderts
325 obsolete_Pellusterts
326 No Petraquepts
327 No Petroargids
328 No Petrocalcids
329 No Petrocambids
330 No Petrocryids
331 No Petrogypsids
332 obsolete_Placandepts
333 No Placaquands
334 obsolete_Placaquepts
335 No Placaquods
336 No Placocryods
337 No Placohumods
338 No Placorthods
339 No Placudands
340 No Plagganthrepts
341 obsolete_Plaggepts
342 No Plinthaqualfs
343 obsolete_Plinthaquepts
344 No Plinthaquox
345 No Plinthaquults
346 No Plinthohumults
347 No Plinthoxeralfs
348 No Plinthudults
349 No Plinthustalfs
350 No Plinthustults
351 No Psammaquents
352 No Psammorthels
353 No Psammoturbels
354 No Quartzipsamments
355 obsolete_Rendolls
356 No Rhodoxeralfs
357 No Rhodudalfs
358 No Rhodudults
359 No Rhodustalfs
360 No Rhodustults
361 No Salaquerts
362 No Salicryids
363 No Salitorrerts
364 obsolete_Salorthids
365 No Salusterts
366 No Sapristels
367 obsolete_Sideraquods
368 obsolete_Sombrihumox
369 No Sombrihumults
370 obsolete_Sombriorthox
371 No Sombriperox
372 obsolete_Sombritropepts
373 No Sombriudox
374 No Sombriustox
375 No Sphagnofibrists
376 No Sulfaquents
377 No Sulfaquepts
378 No Sulfaquerts
379 No Sulfihemists
380 No Sulfisaprists
381 obsolete_Sulfochrepts
382 No Sulfohemists
383 No Sulfosaprists
384 No Sulfudepts
385 obsolete_Torrerts
386 No Torriarents
387 No Torrifluvents
388 No Torrifolists
389 No Torriorthents
390 No Torripsamments
391 obsolete_Torrox
392 obsolete_Tropaqualfs
393 obsolete_Tropaquents
394 obsolete_Tropaquepts
395 obsolete_Tropaquods
396 obsolete_Tropaquults
397 obsolete_Tropofibrists
398 obsolete_Tropofluvents
399 obsolete_Tropofolists
400 obsolete_Tropohemists
401 obsolete_Tropohumods
402 obsolete_Tropohumults
403 obsolete_Tropopsamments
404 obsolete_Troporthents
405 obsolete_Troporthods
406 obsolete_Troposaprists
407 obsolete_Tropudalfs
408 obsolete_Tropudults
409 No Udarents
410 No Udifluvents
411 No Udifolists
412 No Udipsamments
413 No Udivitrands
414 No Udorthents
415 obsolete_Umbraqualfs
416 obsolete_Umbraquox
417 No Umbraquults
418 obsolete_Umbriorthox
419 No Umbriturbels
420 No Umbrorthels
421 No Ustarents
422 No Ustifluvents
423 No Ustifolists
424 No Ustipsamments
425 No Ustivitrands
426 obsolete_Ustochrepts
427 No Ustorthents
428 obsolete_Ustropepts
429 No Vermaqualfs
430 No Vermaquepts
431 obsolete_Vermiborolls
432 No Vermudolls
433 No Vermustolls
434 obsolete_Vitrandepts
435 No Vitraquands
436 No Vitricryands
437 No Vitrigelands
438 No Vitritorrands
439 No Vitrixerands
440 No Xerarents
441 obsolete_Xerochrepts
442 No Xerofluvents
443 No Xeropsamments
444 No Xerorthents
445 obsolete_Xerumbrepts
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_moisture_class
; /* = 
Length of Longest Choice Value: 15
1 No Aquic
2 No Aridic (torric)
3 No Peraquic
4 No Perudic
5 No Udic
6 No Ustic
7 No Xeric
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_moisture_subclass
; /* = 
Length of Longest Choice Value: 15
1 No Aeric
2 No Anthraquic
3 No Aquic
4 No Aridic (torric)
5 No Oxyaquic
6 No Typic
7 No Udic
SSURGO Version: 2.2.3 Page 108
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_moisture_subclass
; /* = 
Length of Longest Choice Value: 15
8 No Ustic
9 No Xeric
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_order
; /* = 
Length of Longest Choice Value: 11
1 No Alfisols
2 No Andisols
3 No Aridisols
4 No Entisols
5 No Gelisols
6 No Histosols
7 No Inceptisols
8 No Mollisols
9 No Oxisols
10 No Spodosols
11 No Ultisols
12 No Vertisols
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1 No Abruptic Argiaquolls
2 obsolete_Abruptic Argiborolls
3 No Abruptic Argicryolls
4 Abruptic Argiduridic
Durixerolls
No
5 No Abruptic Argidurids
6 No Abruptic Argiudolls
7 obsolete_Abruptic Aridic Argiborolls
8 obsolete_Abruptic Aridic Argixerolls
SSURGO Version: 2.2.3 Page 109
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
9 obsolete_Abruptic Aridic Durixerolls
10 obsolete_Abruptic Cryic Paleborolls
11 obsolete_Abruptic Cryoborolls
12 obsolete_Abruptic Durargids
13 No Abruptic Durixeralfs
14 obsolete_Abruptic Durixerolls
15 No Abruptic Haplic Durixeralfs
16 obsolete_Abruptic Paleboralfs
17 obsolete_Abruptic Paleborolls
18 No Abruptic Palecryolls
19 obsolete_Abruptic Udic Argiborolls
20 No Abruptic Xeric Argidurids
21 obsolete_Abruptic Xerollic Durargids
22 No Acraquoxic Duraquands
23 No Acraquoxic Kandiaquults
24 No Acraquoxic Melanaquands
25 obsolete_Acric Kandiaquults
26 obsolete_Acric Plinthic
27 No Acrudoxic Durudands
28 No Acrudoxic Fulvudands
29 No Acrudoxic Haplocryands
30 No Acrudoxic Hapludands
31 obsolete_Acrudoxic Hydric Fulvudands
32 No Acrudoxic Hydric Hapludands
33 Acrudoxic Hydric
Melanudands
No
34 obsolete_Acrudoxic Hydric Placudands
35 No Acrudoxic Hydrudands
36 No Acrudoxic Kandiudults
37 No Acrudoxic Kanhapludults
38 No Acrudoxic Melanudands
39 No Acrudoxic Placudands
SSURGO Version: 2.2.3 Page 110
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
40 Acrudoxic Plinthic
Kandiudults
No
41 Acrudoxic Thaptic
Hapludands
No
42 Acrudoxic Thaptic
Hydrudands
No
43 obsolete_Acrudoxic Ultic Fulvudands
44 No Acrudoxic Ultic Hapludands
45 No Acrudoxic Vitric Melanudands
46 No Acrustoxic Kandiustults
47 No Acrustoxic Kanhaplustults
48 No Aeric Acraquox
49 No Aeric Alaquods
50 No Aeric Albaqualfs
51 No Aeric Albaquults
52 obsolete_Aeric Andaquepts
53 obsolete_Aeric Arenic
54 No Aeric Calciaquerts
55 No Aeric Calciaquolls
56 Aeric Chromic Vertic
Epiaqualfs
No
57 No Aeric Cryaquepts
58 obsolete_Aeric Cryaquods
59 No Aeric Duraquerts
60 No Aeric Dystraquerts
61 No Aeric Endoaqualfs
62 No Aeric Endoaquents
63 No Aeric Endoaquepts
64 No Aeric Endoaquerts
65 No Aeric Endoaquults
66 No Aeric Epiaqualfs
67 No Aeric Epiaquents
68 No Aeric Epiaquepts
69 No Aeric Epiaquerts
SSURGO Version: 2.2.3 Page 111
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
70 No Aeric Epiaquults
71 No Aeric Eutraquox
72 No Aeric Fluvaquents
73 No Aeric Fragiaqualfs
74 No Aeric Fragiaquepts
75 No Aeric Fragiaquults
76 No Aeric Fragic Endoaqualfs
77 No Aeric Fragic Epiaqualfs
78 No Aeric Fragic Epiaquults
79 No Aeric Fragic Glossaqualfs
80 No Aeric Glossaqualfs
81 obsolete_Aeric Grossarenic
82 No Aeric Halaquepts
83 obsolete_Aeric Haplaquents
84 obsolete_Aeric Haplaquepts
85 obsolete_Aeric Haplaquods
86 No Aeric Haplaquox
87 No Aeric Humaquepts
88 No Aeric Humic Cryaquepts
89 No Aeric Kandiaqualfs
90 No Aeric Kandiaquults
91 No Aeric Kanhaplaquults
92 obsolete_Aeric Mollic
93 obsolete_Aeric Ochraqualfs
94 obsolete_Aeric Ochraquults
95 No Aeric Paleaquults
96 No Aeric Plinthaquox
97 obsolete_Aeric Plinthic Fragiaquults
98 obsolete_Aeric Tropaqualfs
99 obsolete_Aeric Tropaquepts
100 obsolete_Aeric Tropaquods
101 obsolete_Aeric Tropic Fluvaquents
SSURGO Version: 2.2.3 Page 112
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
102 No Aeric Umbric Endoaqualfs
103 No Aeric Umbric Epiaqualfs
104 No Aeric Umbric Kandiaqualfs
105 No Aeric Umbric Kanhaplaquults
106 obsolete_Aeric Umbric Ochraqualfs
107 No Aeric Vertic Albaqualfs
108 No Aeric Vertic Epiaqualfs
109 obsolete_Aeric Xeric
110 obsolete_Albaquic Fragiudalfs
111 No Albaquic Hapludalfs
112 No Albaquic Paleudalfs
113 No Albaquultic Hapludalfs
114 obsolete_Albic Argiborolls
115 obsolete_Albic Argiudolls
116 obsolete_Albic Argixerolls
117 obsolete_Albic Cryoborolls
118 No Albic Glossic Natraqualfs
119 No Albic Natraqualfs
120 obsolete_Albollic Argiborolls
121 No Alfic Alaquods
122 No Alfic Alorthods
123 obsolete_Alfic Andeptic
124 obsolete_Alfic Andeptic Cryorthents
125 No Alfic Arenic Alaquods
126 obsolete_Alfic Arenic Haplaquods
127 No Alfic Argicryolls
128 No Alfic Argiudolls
129 No Alfic Argiustolls
130 No Alfic Argixerolls
131 obsolete_Alfic Cryochrepts
132 obsolete_Alfic Cryopsamments
133 obsolete_Alfic Cryorthents
SSURGO Version: 2.2.3 Page 113
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
134 No Alfic Epiaquods
135 No Alfic Fragiorthods
136 obsolete_Alfic Haplaquods
137 No Alfic Haplorthods
138 No Alfic Haploxerands
139 No Alfic Hapludands
140 No Alfic Haplustands
141 No Alfic Humic Haploxerands
142 No Alfic Humic Vitrixerands
143 No Alfic Lithic Argiustolls
144 No Alfic Oxyaquic Fragiorthods
145 No Alfic Oxyaquic Haplorthods
146 obsolete_Alfic Sideraquods
147 No Alfic Udarents
148 obsolete_Alfic Udipsamments
149 No Alfic Udivitrands
150 obsolete_Alfic Ustipsamments
151 No Alfic Vertic Argiudolls
152 No Alfic Vitricryands
153 No Alfic Vitrixerands
154 No Alfic Xerarents
155 obsolete_Alfic Xeropsamments
156 obsolete_Alic Aquic Melanudands
157 obsolete_Alic Dystraquerts
158 obsolete_Alic Dystruderts
159 No Alic Endoaquands
160 No Alic Epiaquands
161 obsolete_Alic Fulvudands
162 obsolete_Alic Haplaquands
163 No Alic Haplocryands
164 No Alic Hapludands
165 obsolete_Alic Melanocryands
SSURGO Version: 2.2.3 Page 114
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
166 obsolete_Alic Melanudands
167 obsolete_Alic Pachic Melanudands
168 obsolete_Alic Thaptic Melanudands
169 obsolete_Andaqueptic
170 obsolete_Andaqueptic Cryaquents
171 obsolete_Andaqueptic Fluvaquents
172 obsolete_Andaqueptic Haplaquolls
173 obsolete_Andaqueptic Ochraqualfs
174 obsolete_Andaquic
175 obsolete_Andeptic
176 obsolete_Andeptic Cryoboralfs
177 obsolete_Andeptic Cryoborolls
178 obsolete_Andeptic Cryofluvents
179 obsolete_Andeptic Cryorthents
180 obsolete_Andeptic Glossoboric
181 obsolete_Andeptic Haplohumults
182 obsolete_Andeptic Palehumults
183 obsolete_Andeptic Udorthents
184 No Andic Aquorthels
185 obsolete_Andic Argiborolls
186 No Andic Argicryolls
187 No Andic Argiudolls
188 No Andic Argiustolls
189 No Andic Argixerolls
190 obsolete_Andic Cryaquepts
191 No Andic Cryaquods
192 obsolete_Andic Cryoboralfs
193 obsolete_Andic Cryoborolls
194 obsolete_Andic Cryochrepts
195 No Andic Cryofluvents
196 obsolete_Andic Cryorthods
197 obsolete_Andic Cryumbrepts
SSURGO Version: 2.2.3 Page 115
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
198 No Andic Duraquods
199 No Andic Duricryods
200 No Andic Durihumods
201 No Andic Durixerepts
202 obsolete_Andic Durochrepts
203 No Andic Durorthods
204 No Andic Durudepts
205 obsolete_Andic Dystric
206 obsolete_Andic Dystric Eutrochrepts
207 obsolete_Andic Dystrochrepts
208 No Andic Dystrocryepts
209 No Andic Dystrogelepts
210 obsolete_Andic Dystropepts
211 No Andic Dystroxerepts
212 No Andic Dystrudepts
213 No Andic Dystrustepts
214 No Andic Endoaquods
215 obsolete_Andic Epiaquic
216 No Andic Epiaquods
217 obsolete_Andic Eutroboralfs
218 obsolete_Andic Eutrochrepts
219 obsolete_Andic Eutrocryepts
220 No Andic Eutrogelepts
221 obsolete_Andic Eutropepts
222 No Andic Eutrudepts
223 obsolete_Andic Fragiboralfs
224 obsolete_Andic Fragiochrepts
225 No Andic Fragiudalfs
226 No Andic Fragiudepts
227 obsolete_Andic Fragiumbrepts
228 No Andic Fragixeralfs
229 No Andic Fragixerepts
SSURGO Version: 2.2.3 Page 116
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
230 No Andic Fraglossudalfs
231 obsolete_Andic Glossoboralfs
232 No Andic Glossocryalfs
233 No Andic Glossudalfs
234 obsolete_Andic Haploborolls
235 No Andic Haplocryalfs
236 No Andic Haplocryepts
237 No Andic Haplocryods
238 No Andic Haplocryolls
239 No Andic Haplogelods
240 No Andic Haplogelolls
241 No Andic Haplohumods
242 No Andic Haplohumults
243 No Andic Haploperox
244 No Andic Haplorthods
245 No Andic Haploxeralfs
246 No Andic Haploxerepts
247 No Andic Haploxerolls
248 No Andic Haploxerults
249 No Andic Hapludalfs
250 No Andic Hapludolls
251 No Andic Hapludox
252 obsolete_Andic Haplumbrepts
253 No Andic Haplustepts
254 No Andic Haplustolls
255 No Andic Humicryepts
256 No Andic Humicryods
257 No Andic Humigelods
258 obsolete_Andic Humitropepts
259 No Andic Kandihumults
260 No Andic Kandiperox
261 No Andic Kandiudox
SSURGO Version: 2.2.3 Page 117
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
262 No Andic Kandiudults
263 No Andic Kandiustults
264 No Andic Kanhaplohumults
265 No Andic Kanhapludults
266 No Andic Kanhaplustults
267 No Andic Molliturbels
268 No Andic Mollorthels
269 Andic Ombroaquic
Kandihumults
No
270 No Andic Oxyaquic Dystrudepts
271 No Andic Oxyaquic Haploxerepts
272 obsolete_Andic Paleboralfs
273 No Andic Palecryalfs
274 No Andic Palehumults
275 No Andic Paleudalfs
276 No Andic Paleustolls
277 No Andic Palexeralfs
278 No Andic Palexerults
279 No Andic Placaquods
280 No Andic Placocryods
281 No Andic Placohumods
282 obsolete_Andic Troporthents
283 obsolete_Andic Udic
284 No Andic Udifluvents
285 obsolete_Andic Udorthents
286 No Andic Umbriturbels
287 No Andic Umbrorthels
288 obsolete_Andic Ustic
289 obsolete_Andic Ustic Humitropepts
290 obsolete_Andic Ustochrepts
291 obsolete_Andic Xerochrepts
292 No Andic Xerofluvents
293 obsolete_Andic Xerorthents
SSURGO Version: 2.2.3 Page 118
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
294 obsolete_Andic Xerumbrepts
295 No Anionic Acroperox
296 No Anionic Acrudox
297 No Anionic Acrustox
298 No Anionic Aquic Acrudox
299 No Anionic Aquic Acrustox
300 obsolete_Anthraquic Eutrochrepts
301 No Anthraquic Eutrudepts
302 No Anthraquic Hapludalfs
303 No Anthraquic Hapludands
304 No Anthraquic Haplustepts
305 No Anthraquic Haplustolls
306 No Anthraquic Melanudands
307 No Anthraquic Paleudalfs
308 No Anthraquic Paleudults
309 No Anthraquic Ustifluvents
310 obsolete_Anthraquic Ustochrepts
311 No Anthraquic Ustorthents
312 obsolete_Anthropic Camborthids
313 No Anthropic Kandihumults
314 No Anthropic Kanhaplohumults
315 obsolete_Anthropic Paleudalfs
316 No Anthropic Torrifluvents
317 obsolete_Aqualfic Argixerolls
318 No Aqualfic Haplorthods
319 No Aquandic Albaqualfs
320 No Aquandic Argialbolls
321 No Aquandic Cryaquents
322 No Aquandic Cryaquepts
323 No Aquandic Cryaquolls
324 No Aquandic Duricryods
325 No Aquandic Durixerepts
SSURGO Version: 2.2.3 Page 119
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
326 obsolete_Aquandic Durochrepts
327 No Aquandic Durudepts
328 obsolete_Aquandic Dystrochrepts
329 No Aquandic Dystrocryepts
330 No Aquandic Dystroxerepts
331 No Aquandic Dystrudepts
332 No Aquandic Endoaqualfs
333 No Aquandic Endoaquepts
334 No Aquandic Endoaquolls
335 No Aquandic Epiaqualfs
336 No Aquandic Epiaquepts
337 No Aquandic Epiaquolls
338 No Aquandic Fluvaquents
339 No Aquandic Gelaquepts
340 No Aquandic Glossudalfs
341 No Aquandic Halaquepts
342 obsolete_Aquandic Haplaquolls
343 No Aquandic Haplocryepts
344 No Aquandic Haplocryods
345 No Aquandic Haplohumults
346 No Aquandic Haploxeralfs
347 No Aquandic Haploxerepts
348 obsolete_Aquandic Hapludults
349 obsolete_Aquandic Haplumbrepts
350 No Aquandic Humaquepts
351 No Aquandic Humicryepts
352 No Aquandic Humicryods
353 No Aquandic Kandiudults
354 No Aquandic Kanhaplaquults
355 No Aquandic Palehumults
356 No Aquandic Palexeralfs
357 No Aquandic Palexerults
SSURGO Version: 2.2.3 Page 120
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
358 obsolete_Aquandic Placaquepts
359 obsolete_Aquandic Tropaquepts
360 obsolete_Aquandic Umbraqualfs
361 obsolete_Aquandic Xerochrepts
362 No Aquandic Xerofluvents
363 obsolete_Aquandic Xerorthents
364 obsolete_Aquentic Chromuderts
365 obsolete_Aquentic Durorthids
366 obsolete_Aquentic Fragiorthods
367 No Aquentic Haplorthods
368 obsolete_Aqueptic Fragiudalfs
369 No Aqueptic Haplustox
370 obsolete_Aquertic Argiborolls
371 No Aquertic Argiudolls
372 No Aquertic Argiustolls
373 No Aquertic Chromic Hapludalfs
374 obsolete_Aquertic Eutroboralfs
375 obsolete_Aquertic Eutropepts
376 No Aquertic Eutrudepts
377 No Aquertic Glossudalfs
378 obsolete_Aquertic Haploborolls
379 No Aquertic Hapludalfs
380 No Aquertic Hapludolls
381 No Aquertic Haplustalfs
382 No Aquertic Haplustolls
383 obsolete_Aquertic Humitropepts
384 No Aquertic Natrustalfs
385 No Aquertic Paleustalfs
386 No Aquertic Udifluvents
387 No Aquertic Ustifluvents
388 No Aquic Acroperox
389 No Aquic Acrudox
SSURGO Version: 2.2.3 Page 121
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
390 No Aquic Acrustox
391 obsolete_Aquic Anionic
392 obsolete_Aquic Arenic Eutroboralfs
393 No Aquic Arenic Glossudalfs
394 No Aquic Arenic Hapludalfs
395 No Aquic Arenic Hapludults
396 No Aquic Arenic Haplustalfs
397 No Aquic Arenic Kandiudults
398 No Aquic Arenic Kandiustalfs
399 No Aquic Arenic Natrustalfs
400 No Aquic Arenic Paleudults
401 No Aquic Arenic Paleustalfs
402 obsolete_Aquic Argiborolls
403 No Aquic Argicryolls
404 No Aquic Argidurids
405 No Aquic Argiudolls
406 No Aquic Argiustolls
407 No Aquic Argixerolls
408 No Aquic Calciargids
409 obsolete_Aquic Calciborolls
410 obsolete_Aquic Calciorthids
411 No Aquic Calciudolls
412 No Aquic Calciustepts
413 No Aquic Calciustolls
414 No Aquic Calcixerepts
415 No Aquic Calcixerolls
416 obsolete_Aquic Camborthids
417 obsolete_Aquic Chromoxererts
418 obsolete_Aquic Chromuderts
419 obsolete_Aquic Cryoboralfs
420 obsolete_Aquic Cryoborolls
421 obsolete_Aquic Cryochrepts
SSURGO Version: 2.2.3 Page 122
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
422 No Aquic Cryofluvents
423 No Aquic Cryopsamments
424 No Aquic Cryorthents
425 obsolete_Aquic Cryumbrepts
426 obsolete_Aquic Cumulic Cryoborolls
427 obsolete_Aquic Cumulic Haploborolls
428 No Aquic Cumulic Haplocryolls
429 No Aquic Cumulic Haploxerolls
430 No Aquic Cumulic Hapludolls
431 No Aquic Cumulic Haplustolls
432 obsolete_Aquic Durargids
433 obsolete_Aquic Duric Calciorthids
434 obsolete_Aquic Duric Camborthids
435 No Aquic Duric Haploxerolls
436 No Aquic Duric Hapludands
437 No Aquic Duric Natrixerolls
438 obsolete_Aquic Duric Torriorthents
439 No Aquic Duricryands
440 No Aquic Duricryods
441 No Aquic Durinodic Haplocalcids
442 Aquic Durinodic
Xeropsamments
No
443 obsolete_Aquic Durinodic Xerorthents
444 No Aquic Durixeralfs
445 No Aquic Durixerepts
446 No Aquic Durixererts
447 No Aquic Durixerolls
448 obsolete_Aquic Durochrepts
449 Aquic Durorthidic
Torriorthents
Yes
450 Aquic Durorthidic
Xeropsamments
Yes
451 obsolete_Aquic Durorthidic Xerorthents
SSURGO Version: 2.2.3 Page 123
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
452 obsolete_Aquic Durorthids
453 No Aquic Durudands
454 No Aquic Durudepts
455 No Aquic Durustands
456 obsolete_Aquic Dystrandepts
457 obsolete_Aquic Dystric Eutrochrepts
458 No Aquic Dystric Eutrudepts
459 obsolete_Aquic Dystric Xerochrepts
460 obsolete_Aquic Dystrochrepts
461 No Aquic Dystrocryepts
462 No Aquic Dystrogelepts
463 obsolete_Aquic Dystropepts
464 No Aquic Dystroxerepts
465 No Aquic Dystrudepts
466 No Aquic Dystruderts
467 No Aquic Dystrustepts
468 No Aquic Dystrusterts
469 obsolete_Aquic Eutroboralfs
470 obsolete_Aquic Eutrochrepts
471 obsolete_Aquic Eutrocryepts
472 No Aquic Eutrogelepts
473 obsolete_Aquic Eutropepts
474 No Aquic Eutroperox
475 No Aquic Eutrudepts
476 No Aquic Eutrudox
477 No Aquic Eutrustox
478 No Aquic Ferrudalfs
479 obsolete_Aquic Fragiboralfs
480 obsolete_Aquic Fragiochrepts
481 No Aquic Fragiorthods
482 No Aquic Fragiudalfs
483 No Aquic Fragiudepts
SSURGO Version: 2.2.3 Page 124
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
484 No Aquic Fragiudults
485 obsolete_Aquic Fragiumbrepts
486 No Aquic Fragixeralfs
487 No Aquic Fragixerepts
488 No Aquic Fraglossudalfs
489 No Aquic Fulvudands
490 No Aquic Gelifluvents
491 obsolete_Aquic Glossoboralfs
492 No Aquic Glossocryalfs
493 No Aquic Glossudalfs
494 No Aquic Gypsiargids
495 No Aquic Haplargids
496 obsolete_Aquic Haplic Nadurargids
497 obsolete_Aquic Haploborolls
498 No Aquic Haplocalcids
499 No Aquic Haplocryalfs
500 No Aquic Haplocryands
501 No Aquic Haplocryepts
502 No Aquic Haplocryods
503 No Aquic Haplocryolls
504 Aquic Haploduridic
Torriorthents
Yes
505 No Aquic Haplodurids
506 No Aquic Haplogelods
507 No Aquic Haplogelolls
508 No Aquic Haplohumults
509 No Aquic Haploperox
510 No Aquic Haplorthels
511 No Aquic Haplorthods
512 No Aquic Haploturbels
513 No Aquic Haploxeralfs
514 No Aquic Haploxerands
515 No Aquic Haploxerepts
SSURGO Version: 2.2.3 Page 125
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
516 No Aquic Haploxererts
517 No Aquic Haploxerolls
518 No Aquic Haploxerults
519 No Aquic Hapludalfs
520 No Aquic Hapludands
521 No Aquic Hapluderts
522 No Aquic Hapludolls
523 No Aquic Hapludox
524 No Aquic Hapludults
525 obsolete_Aquic Haplumbrepts
526 No Aquic Haplustalfs
527 No Aquic Haplustands
528 No Aquic Haplustepts
529 No Aquic Haplustolls
530 No Aquic Haplustox
531 No Aquic Haplustults
532 No Aquic Humic Dystrudepts
533 No Aquic Humicryepts
534 No Aquic Humicryods
535 No Aquic Humigelods
536 obsolete_Aquic Humitropepts
537 No Aquic Hydrocryands
538 No Aquic Hydrudands
539 No Aquic Kandihumults
540 No Aquic Kandiperox
541 No Aquic Kandiudalfs
542 No Aquic Kandiudox
543 No Aquic Kandiudults
544 No Aquic Kandiustalfs
545 No Aquic Kandiustox
546 No Aquic Kandiustults
547 No Aquic Kanhaplohumults
SSURGO Version: 2.2.3 Page 126
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
548 No Aquic Kanhapludalfs
549 No Aquic Kanhapludults
550 No Aquic Kanhaplustalfs
551 No Aquic Kanhaplustults
552 No Aquic Lithic Acroperox
553 No Aquic Lithic Acrudox
554 No Aquic Lithic Acrustox
555 No Aquic Lithic Eutroperox
556 No Aquic Lithic Eutrudox
557 No Aquic Lithic Eutrustox
558 No Aquic Lithic Haploperox
559 obsolete_Aquic Lithic Hapludalfs
560 No Aquic Lithic Hapludox
561 No Aquic Lithic Haplustox
562 No Aquic Lithic Kandiperox
563 No Aquic Lithic Kandiudox
564 No Aquic Lithic Kandiustox
565 No Aquic Melanudands
566 No Aquic Molliturbels
567 No Aquic Mollorthels
568 obsolete_Aquic Nadurargids
569 No Aquic Natrargidic Natridurids
570 No Aquic Natrargids
571 No Aquic Natridurids
572 No Aquic Natrixeralfs
573 No Aquic Natrixerolls
574 No Aquic Natrudalfs
575 No Aquic Natrustalfs
576 No Aquic Natrustolls
577 No Aquic Pachic Argiudolls
578 No Aquic Pachic Hapludolls
579 No Aquic Pachic Paleudolls
SSURGO Version: 2.2.3 Page 127
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
580 No Aquic Paleargids
581 obsolete_Aquic Paleboralfs
582 obsolete_Aquic Paleborolls
583 No Aquic Palecryalfs
584 No Aquic Palecryolls
585 No Aquic Palehumults
586 obsolete_Aquic Paleorthids
587 No Aquic Paleudalfs
588 No Aquic Paleudolls
589 No Aquic Paleudults
590 No Aquic Paleustalfs
591 No Aquic Paleustolls
592 No Aquic Palexeralfs
593 No Aquic Palexerolls
594 No Aquic Palexerults
595 No Aquic Petrocalcids
596 No Aquic Petroferric Acroperox
597 No Aquic Petroferric Acrudox
598 No Aquic Petroferric Acrustox
599 No Aquic Petroferric Eutroperox
600 No Aquic Petroferric Eutrudox
601 No Aquic Petroferric Eutrustox
602 No Aquic Petroferric Haploperox
603 No Aquic Petroferric Hapludox
604 No Aquic Petroferric Haplustox
605 No Aquic Petroferric Kandiperox
606 No Aquic Petroferric Kandiudox
607 No Aquic Petroferric Kandiustox
608 No Aquic Placudands
609 obsolete_Aquic Psammentic
610 No Aquic Quartzipsamments
611 No Aquic Salicryids
SSURGO Version: 2.2.3 Page 128
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
612 No Aquic Salitorrerts
613 No Aquic Salusterts
614 No Aquic Torrifluvents
615 No Aquic Torriorthents
616 obsolete_Aquic Tropopsamments
617 obsolete_Aquic Tropudalfs
618 obsolete_Aquic Tropudults
619 No Aquic Udifluvents
620 No Aquic Udipsamments
621 No Aquic Udivitrands
622 No Aquic Udorthents
623 No Aquic Umbriturbels
624 No Aquic Umbrorthels
625 No Aquic Ustifluvents
626 No Aquic Ustipsamments
627 No Aquic Ustivitrands
628 obsolete_Aquic Ustochrepts
629 No Aquic Ustorthents
630 obsolete_Aquic Ustropepts
631 No Aquic Vermustolls
632 obsolete_Aquic Vitrandepts
633 No Aquic Vitricryands
634 No Aquic Vitritorrands
635 No Aquic Vitrixerands
636 obsolete_Aquic Xerochrepts
637 No Aquic Xerofluvents
638 No Aquic Xeropsamments
639 No Aquic Xerorthents
640 obsolete_Aquic Xerumbrepts
641 No Aquicambidic Haplodurids
642 No Aquodic Quartzipsamments
643 No Aquollic Hapludalfs
SSURGO Version: 2.2.3 Page 129
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
644 obsolete_Aquollic Salorthids
645 No Aquultic Argixerolls
646 No Aquultic Haploxeralfs
647 No Aquultic Haploxerolls
648 No Aquultic Hapludalfs
649 No Aquultic Haplustalfs
650 No Arenic Alaquods
651 No Arenic Albaqualfs
652 No Arenic Alorthods
653 No Arenic Argiaquolls
654 obsolete_Arenic Argiborolls
655 No Arenic Argiudolls
656 No Arenic Aridic Haplustalfs
657 No Arenic Aridic Kandiustalfs
658 No Arenic Aridic Paleustalfs
659 obsolete_Arenic Aridic Paleustolls
660 No Arenic Calciargids
661 No Arenic Endoaqualfs
662 No Arenic Endoaquults
663 No Arenic Epiaqualfs
664 No Arenic Epiaquults
665 obsolete_Arenic Eutroboralfs
666 obsolete_Arenic Eutrochrepts
667 No Arenic Eutrudepts
668 No Arenic Fragiudults
669 No Arenic Glossaqualfs
670 No Arenic Glossudalfs
671 obsolete_Arenic Haplaquods
672 No Arenic Haplargids
673 obsolete_Arenic Haplohumods
674 No Arenic Haploxerults
675 No Arenic Hapludalfs
SSURGO Version: 2.2.3 Page 130
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
676 No Arenic Hapludults
677 No Arenic Haplustalfs
678 No Arenic Haplustults
679 No Arenic Kandiaqualfs
680 No Arenic Kandiaquults
681 No Arenic Kandiudalfs
682 No Arenic Kandiudults
683 No Arenic Kandiustalfs
684 No Arenic Kandiustults
685 No Arenic Kanhapludults
686 No Arenic Kanhaplustults
687 No Arenic Natrustalfs
688 obsolete_Arenic Ochraqualfs
689 obsolete_Arenic Ochraquults
690 obsolete_Arenic Orthoxic
691 obsolete_Arenic Oxyaquic Eutroboralfs
692 No Arenic Oxyaquic Glossudalfs
693 No Arenic Oxyaquic Hapludalfs
694 No Arenic Paleaquults
695 No Arenic Paleargids
696 No Arenic Paleudalfs
697 No Arenic Paleudults
698 No Arenic Paleustalfs
699 No Arenic Palexeralfs
700 Arenic Plinthaquic
Kandiudults
No
701 No Arenic Plinthaquic Paleudults
702 No Arenic Plinthic Kandiaquults
703 No Arenic Plinthic Kandiudalfs
704 No Arenic Plinthic Kandiudults
705 No Arenic Plinthic Kandiustults
706 No Arenic Plinthic Kanhapludults
707 No Arenic Plinthic Paleaquults
SSURGO Version: 2.2.3 Page 131
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
708 No Arenic Plinthic Paleudalfs
709 No Arenic Plinthic Paleudults
710 No Arenic Rhodic Kandiudults
711 No Arenic Rhodic Paleudults
712 No Arenic Ultic Alaquods
713 No Arenic Ultic Alorthods
714 obsolete_Arenic Ultic Haplaquods
715 obsolete_Arenic Ultic Haplohumods
716 obsolete_Arenic Umbraqualfs
717 No Arenic Umbric Alaquods
718 obsolete_Arenic Umbric Haplaquods
719 No Arenic Umbric Kandiaquults
720 No Arenic Umbric Paleaquults
721 obsolete_Arenic Ustalfic Haplargids
722 No Arenic Ustic Calciargids
723 No Arenic Ustic Haplargids
724 No Arenic Ustic Paleargids
725 obsolete_Arenic Ustollic Haplargids
726 No Argiaquic Argialbolls
727 obsolete_Argiaquic Cryoborolls
728 No Argiaquic Xeric Argialbolls
729 obsolete_Argic Calciorthids
730 No Argic Cryaquolls
731 obsolete_Argic Cryoborolls
732 obsolete_Argic Cryopsamments
733 No Argic Duraquolls
734 No Argic Duricryolls
735 obsolete_Argic Durixerolls
736 No Argic Endoaquods
737 No Argic Fragiaquods
738 obsolete_Argic Lithic Cryoborolls
739 obsolete_Argic Pachic Cryoborolls
SSURGO Version: 2.2.3 Page 132
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
740 No Argic Petrocalcids
741 obsolete_Argic Quartzipsamments
742 obsolete_Argic Udipsamments
743 Argic Ustic
Quartzipsamments
Yes
744 obsolete_Argic Ustipsamments
745 obsolete_Argic Vertic Cryoborolls
746 obsolete_Argic Xeropsamments
747 obsolete_Argidic
748 No Argidic Argidurids
749 No Argidic Durixerolls
750 No Argiduridic Argixerolls
751 No Argiduridic Durixerolls
752 No Argiduridic Durustolls
753 obsolete_Argixerollic
754 obsolete_Aridic Argiborolls
755 No Aridic Argiustolls
756 No Aridic Argixerolls
757 obsolete_Aridic Calciborolls
758 obsolete_Aridic Calcic Argixerolls
759 No Aridic Calciustepts
760 No Aridic Calciusterts
761 No Aridic Calciustolls
762 No Aridic Calcixererts
763 No Aridic Calcixerolls
764 No Aridic Duraquerts
765 obsolete_Aridic Duric Haploxerolls
766 obsolete_Aridic Duric Haplustolls
767 No Aridic Durixererts
768 obsolete_Aridic Durixerolls
769 obsolete_Aridic Durochrepts
770 obsolete_Aridic Durustolls
771 No Aridic Dystraquerts
SSURGO Version: 2.2.3 Page 133
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
772 No Aridic Dystrustepts
773 No Aridic Dystrusterts
774 No Aridic Endoaquerts
775 No Aridic Epiaquerts
776 obsolete_Aridic Eutroboralfs
777 No Aridic Glossic Natrustalfs
778 No Aridic Gypsiusterts
779 obsolete_Aridic Haploborolls
780 No Aridic Haploxererts
781 No Aridic Haploxerolls
782 No Aridic Haplustalfs
783 No Aridic Haplustepts
784 No Aridic Haplusterts
785 No Aridic Haplustolls
786 No Aridic Kandiustalfs
787 No Aridic Kandiustults
788 No Aridic Kanhaplustalfs
789 No Aridic Kanhaplustults
790 No Aridic Leptic Haplusterts
791 No Aridic Leptic Natrustalfs
792 No Aridic Leptic Natrustolls
793 No Aridic Lithic Argiustolls
794 No Aridic Lithic Haplustepts
795 No Aridic Lithic Haplustolls
796 obsolete_Aridic Lithic Ustochrepts
797 No Aridic Lithic Ustorthents
798 obsolete_Aridic Natrargids
799 obsolete_Aridic Natriborolls
800 No Aridic Natrixerolls
801 No Aridic Natrustalfs
802 No Aridic Natrustolls
803 obsolete_Aridic Pachic
SSURGO Version: 2.2.3 Page 134
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
804 No Aridic Paleustalfs
805 No Aridic Paleustolls
806 No Aridic Palexerolls
807 obsolete_Aridic Petrocalcic Palexerolls
808 No Aridic Salaquerts
809 No Aridic Salusterts
810 obsolete_Aridic Torriorthents
811 No Aridic Ustifluvents
812 No Aridic Ustipsamments
813 obsolete_Aridic Ustochrepts
814 No Aridic Ustorthents
815 obsolete_Aridic Ustropepts
816 obsolete_Aridic Vermiborolls
817 obsolete_Boralfic Argiborolls
818 obsolete_Boralfic Argiustolls
819 obsolete_Boralfic Argixerolls
820 obsolete_Boralfic Cryoborolls
821 obsolete_Boralfic Cryorthods
822 obsolete_Boralfic Lithic Cryoborolls
823 obsolete_Boralfic Udertic Argiborolls
824 obsolete_Boralfic Udic Argiborolls
825 obsolete_Borollic Calciorthids
826 obsolete_Borollic Camborthids
827 obsolete_Borollic Glossic Natrargids
828 obsolete_Borollic Haplargids
829 obsolete_Borollic Lithic Calciorthids
830 obsolete_Borollic Lithic Camborthids
831 obsolete_Borollic Lithic Haplargids
832 obsolete_Borollic Natrargids
833 obsolete_Borollic Paleargids
834 obsolete_Borollic Paleorthids
835 obsolete_Borollic Torriorthents
SSURGO Version: 2.2.3 Page 135
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
836 obsolete_Borollic Vertic Camborthids
837 obsolete_Borollic Vertic Haplargids
838 obsolete_Borollic Vertic Paleargids
839 No Calciargidic Argixerolls
840 obsolete_Calciargidic Paleustolls
841 No Calcic Anhyorthels
842 No Calcic Anhyturbels
843 No Calcic Aquisalids
844 No Calcic Argicryolls
845 No Calcic Argigypsids
846 No Calcic Argiudolls
847 No Calcic Argixerolls
848 No Calcic Cryaquolls
849 obsolete_Calcic Cryoborolls
850 No Calcic Duricryolls
851 No Calcic Gypsicryids
852 obsolete_Calcic Gypsiorthids
853 No Calcic Haplocryepts
854 No Calcic Haplocryolls
855 No Calcic Haplosalids
856 No Calcic Haplotorrands
857 No Calcic Haploxeralfs
858 No Calcic Haploxerands
859 No Calcic Haploxerepts
860 No Calcic Haploxerolls
861 No Calcic Hapludolls
862 No Calcic Haplustalfs
863 No Calcic Haplustands
864 No Calcic Haplustepts
865 No Calcic Haplusterts
866 No Calcic Lithic Petrocalcids
867 No Calcic Natrudolls
SSURGO Version: 2.2.3 Page 136
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
868 No Calcic Pachic Argicryolls
869 No Calcic Pachic Argixerolls
870 obsolete_Calcic Pachic Cryoborolls
871 No Calcic Pachic Haplocryolls
872 No Calcic Pachic Haploxerolls
873 No Calcic Paleargids
874 No Calcic Paleudolls
875 No Calcic Paleustolls
876 No Calcic Palexeralfs
877 No Calcic Petrocalcids
878 No Calcic Petrogypsids
879 No Calcic Rhodoxeralfs
880 No Calcic Udic Haplustalfs
881 No Calcic Udic Haplustepts
882 obsolete_Calcic Udic Ustochrepts
883 No Calcic Ustivitrands
884 obsolete_Calcic Ustochrepts
885 No Calcic Vitritorrands
886 No Calcidic Argiustolls
887 No Calcidic Haploxerolls
888 No Calcidic Haplustalfs
889 No Calcidic Paleustalfs
890 No Calcidic Paleustolls
891 obsolete_Calciorthidic Haploxerolls
892 obsolete_Calciorthidic Paleustalfs
893 obsolete_Calciorthidic Paleustolls
894 obsolete_Calciorthidic Ustochrepts
895 obsolete_Calcixerollic Xerochrepts
896 obsolete_Cambic Gypsiorthids
897 No Cambidic Durixerolls
898 No Cambidic Haplodurids
899 No Chromic Calcitorrerts
SSURGO Version: 2.2.3 Page 137
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
900 No Chromic Calciusterts
901 No Chromic Calcixererts
902 No Chromic Duraquerts
903 No Chromic Durixererts
904 No Chromic Dystraquerts
905 No Chromic Dystruderts
906 No Chromic Dystrusterts
907 No Chromic Endoaquerts
908 No Chromic Epiaquerts
909 No Chromic Gypsitorrerts
910 No Chromic Gypsiusterts
911 No Chromic Haplocryerts
912 No Chromic Haplotorrerts
913 No Chromic Haploxererts
914 No Chromic Hapluderts
915 No Chromic Haplusterts
916 obsolete_Chromic Pelloxererts
917 No Chromic Salaquerts
918 No Chromic Salitorrerts
919 No Chromic Salusterts
920 No Chromic Udic Haplusterts
921 No Chromic Vertic Albaqualfs
922 No Chromic Vertic Endoaqualfs
923 No Chromic Vertic Epiaqualfs
924 No Chromic Vertic Hapludalfs
925 obsolete_Chromudic
926 obsolete_Cryic Fragiorthods
927 obsolete_Cryic Lithic Rendolls
928 obsolete_Cryic Pachic Paleborolls
929 obsolete_Cryic Paleborolls
930 obsolete_Cryic Placohumods
931 obsolete_Cryic Rendolls
SSURGO Version: 2.2.3 Page 138
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
932 obsolete_Cryic Sphagnofibrists
933 No Cumulic Cryaquolls
934 obsolete_Cumulic Cryoborolls
935 No Cumulic Endoaquolls
936 No Cumulic Epiaquolls
937 obsolete_Cumulic Haplaquolls
938 obsolete_Cumulic Haploborolls
939 No Cumulic Haplocryolls
940 No Cumulic Haplogelolls
941 No Cumulic Haploxerolls
942 No Cumulic Hapludolls
943 obsolete_Cumulic Haplumbrepts
944 No Cumulic Haplustolls
945 No Cumulic Humaquepts
946 No Cumulic Molliturbels
947 No Cumulic Mollorthels
948 obsolete_Cumulic Udertic Haploborolls
949 obsolete_Cumulic Udic Haploborolls
950 No Cumulic Ultic Haploxerolls
951 No Cumulic Umbriturbels
952 No Cumulic Umbrorthels
953 No Cumulic Vertic Endoaquolls
954 No Cumulic Vertic Epiaquolls
955 obsolete_Cumulic Vertic Haploborolls
956 obsolete_Durargidic Argixerolls
957 No Duric Alaquods
958 No Duric Argiustolls
959 No Duric Argixerolls
960 obsolete_Duric Calciorthids
961 obsolete_Duric Camborthids
962 No Duric Cryaquods
963 obsolete_Duric Cryoborolls
SSURGO Version: 2.2.3 Page 139
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
964 No Duric Endoaquands
965 No Duric Endoaquolls
966 No Duric Epiaquands
967 No Duric Epiaquolls
968 No Duric Halaquepts
969 obsolete_Duric Haplaquolls
970 obsolete_Duric Haplargids
971 No Duric Haplocalcids
972 obsolete_Duric Haplorthods
973 No Duric Haplosalids
974 No Duric Haplotorrands
975 No Duric Haploxerolls
976 No Duric Hapludands
977 No Duric Haplustolls
978 No Duric Histic Placaquands
979 obsolete_Duric Natrargids
980 No Duric Natrixerolls
981 No Duric Natrustolls
982 obsolete_Duric Paleargids
983 No Duric Palexerolls
984 No Duric Petroargids
985 No Duric Petrocryids
986 No Duric Placaquands
987 No Duric Torriarents
988 No Duric Torrifluvents
989 No Duric Torriorthents
990 obsolete_Duric Torripsamments
991 No Duric Vitraquands
992 No Duric Vitritorrands
993 No Duric Xerarents
994 No Duric Xeric Haplocalcids
995 No Duric Xeric Petroargids
SSURGO Version: 2.2.3 Page 140
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
996 No Duric Xeric Petrocryids
997 No Duric Xeric Torrifluvents
998 obsolete_Duric Xeric Torriorthents
999 obsolete_Duric Xeric Torripsamments
1000 No Duridic Haploxerolls
1001 obsolete_Duridic Torrifluvents
1002 obsolete_Duridic Xeric Torrifluvents
1003 obsolete_Durinodic Albaqualfs
1004 No Durinodic Aquicambids
1005 No Durinodic Calciargids
1006 No Durinodic Gypsiargids
1007 No Durinodic Haplargids
1008 No Durinodic Haplocalcids
1009 No Durinodic Haplocambids
1010 No Durinodic Natrargids
1011 No Durinodic Paleargids
1012 No Durinodic Ustorthents
1013 No Durinodic Xeric Aquicambids
1014 No Durinodic Xeric Calciargids
1015 No Durinodic Xeric Haplargids
1016 No Durinodic Xeric Haplocalcids
1017 Durinodic Xeric
Haplocambids
No
1018 No Durinodic Xeric Natrargids
1019 No Durinodic Xeric Paleargids
1020 No Durinodic Xerofluvents
1021 No Durinodic Xeropsamments
1022 No Durinodic Xerorthents
1023 obsolete_Durixerollic Calciorthids
1024 obsolete_Durixerollic Camborthids
1025 obsolete_Durixerollic Haplargids
1026 Durixerollic Lithic
Camborthids
Yes
SSURGO Version: 2.2.3 Page 141
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1027 obsolete_Durixerollic Natrargids
1028 obsolete_Durochreptic
1029 obsolete_Durorthidic Albaqualfs
1030 obsolete_Durorthidic Torrifluvents
1031 obsolete_Durorthidic Torriorthents
1032 obsolete_Durorthidic Torripsamments
1033 obsolete_Durorthidic Ustorthents
1034 obsolete_Durorthidic Xeric Torrifluvents
1035 Durorthidic Xeric
Torriorthents
Yes
1036 Durorthidic Xeric
Torripsamments
Yes
1037 obsolete_Durorthidic Xerofluvents
1038 obsolete_Durorthidic Xeropsamments
1039 obsolete_Durorthidic Xerorthents
1040 obsolete_Dystric Cryandepts
1041 obsolete_Dystric Cryochrepts
1042 obsolete_Dystric Cryumbrepts
1043 obsolete_Dystric Durochrepts
1044 obsolete_Dystric Entic Durochrepts
1045 obsolete_Dystric Eutrochrepts
1046 No Dystric Eutrudepts
1047 Dystric Fluventic
Eutrochrepts
Yes
1048 No Dystric Fluventic Eutrudepts
1049 obsolete_Dystric Fluventic Xerochrepts
1050 No Dystric Haplustands
1051 No Dystric Haplustepts
1052 obsolete_Dystric Lithic Cryandepts
1053 obsolete_Dystric Lithic Xerochrepts
1054 obsolete_Dystric Ustochrepts
1055 No Dystric Vitric Haplustands
1056 obsolete_Dystric Xerochrepts
SSURGO Version: 2.2.3 Page 142
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1057 No Dystric Xeropsamments
1058 No Dystric Xerorthents
1059 obsolete_Dystropeptic
1060 No Entic Alorthods
1061 No Entic Calcitorrerts
1062 No Entic Calciusterts
1063 No Entic Calcixererts
1064 obsolete_Entic Chromoxererts
1065 obsolete_Entic Chromuderts
1066 obsolete_Entic Chromusterts
1067 obsolete_Entic Cryandepts
1068 No Entic Cryaquods
1069 obsolete_Entic Cryorthods
1070 obsolete_Entic Cryumbrepts
1071 No Entic Durixerepts
1072 obsolete_Entic Durixerolls
1073 obsolete_Entic Durochrepts
1074 obsolete_Entic Durorthids
1075 No Entic Durustolls
1076 obsolete_Entic Dystrandepts
1077 No Entic Dystraquerts
1078 No Entic Dystruderts
1079 No Entic Dystrusterts
1080 No Entic Endoaquerts
1081 No Entic Epiaquerts
1082 obsolete_Entic Eutrandepts
1083 No Entic Fragiorthods
1084 No Entic Grossarenic Alorthods
1085 No Entic Gypsiusterts
1086 obsolete_Entic Haplaquepts
1087 obsolete_Entic Haplaquods
1088 obsolete_Entic Haploborolls
SSURGO Version: 2.2.3 Page 143
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1089 No Entic Haplocryods
1090 obsolete_Entic Haplohumods
1091 No Entic Haplorthods
1092 No Entic Haplotorrerts
1093 No Entic Haploxererts
1094 No Entic Haploxerolls
1095 No Entic Hapluderts
1096 No Entic Hapludolls
1097 obsolete_Entic Haplumbrepts
1098 No Entic Haplusterts
1099 No Entic Haplustolls
1100 No Entic Haprendolls
1101 No Entic Lithic Haplorthods
1102 No Entic Paleustolls
1103 obsolete_Entic Pelloxererts
1104 obsolete_Entic Pelluderts
1105 obsolete_Entic Pellusterts
1106 obsolete_Entic Rendolls
1107 No Entic Salaquerts
1108 No Entic Salitorrerts
1109 No Entic Salusterts
1110 obsolete_Entic Sideraquods
1111 No Entic Udic Haplusterts
1112 No Entic Ultic Haploxerolls
1113 obsolete_Entic Vermudolls
1114 No Entic Vermustolls
1115 obsolete_Entic Xerumbrepts
1116 obsolete_Epiaquic
1117 obsolete_Epiaquic Haplustults
1118 obsolete_Epiaquic Orthoxic
1119 No Eutric Acrudox
1120 No Eutric Acrustox
SSURGO Version: 2.2.3 Page 144
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1121 No Eutric Duricryands
1122 No Eutric Durudands
1123 No Eutric Dystrocryepts
1124 No Eutric Fulvicryands
1125 No Eutric Fulvudands
1126 obsolete_Eutric Glossoboralfs
1127 No Eutric Glossocryalfs
1128 No Eutric Haplocryalfs
1129 No Eutric Hapludands
1130 No Eutric Humicryepts
1131 obsolete_Eutric Hydric Melanudands
1132 No Eutric Hydrudands
1133 No Eutric Lithic Fulvudands
1134 No Eutric Melanudands
1135 No Eutric Oxyaquic Duricryands
1136 No Eutric Pachic Fulvicryands
1137 No Eutric Pachic Fulvudands
1138 obsolete_Eutric Placudands
1139 No Eutric Thaptic Hapludands
1140 obsolete_Eutric Vitric Melanudands
1141 obsolete_Eutric Vitric Placudands
1142 obsolete_Eutrochreptic Rendolls
1143 obsolete_Eutropeptic Rendolls
1144 obsolete_Ferrudalfic Umbraqualfs
1145 obsolete_Fibric Borohemists
1146 obsolete_Fibric Borosaprists
1147 No Fibric Haplohemists
1148 obsolete_Fibric Medihemists
1149 obsolete_Fibric Medisaprists
1150 obsolete_Fibric Terric Borohemists
1151 obsolete_Fibric Terric Borosaprists
1152 obsolete_Fibric Terric Medihemists
SSURGO Version: 2.2.3 Page 145
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1153 obsolete_Fibric Terric Medisaprists
1154 obsolete_Fibric Terric Tropohemists
1155 obsolete_Fibric Terric Troposaprists
1156 obsolete_Fibric Tropohemists
1157 obsolete_Fibric Troposaprists
1158 No Fluvaquentic Aquorthels
1159 obsolete_Fluvaquentic Borofibrists
1160 obsolete_Fluvaquentic Borohemists
1161 obsolete_Fluvaquentic Borosaprists
1162 No Fluvaquentic Cryaquepts
1163 obsolete_Fluvaquentic Cryoborolls
1164 No Fluvaquentic Cryofibrists
1165 No Fluvaquentic Cryohemists
1166 No Fluvaquentic Cryosaprists
1167 obsolete_Fluvaquentic Dystrochrepts
1168 No Fluvaquentic Dystrocryepts
1169 No Fluvaquentic Dystroxerepts
1170 No Fluvaquentic Dystrudepts
1171 No Fluvaquentic Endoaquepts
1172 No Fluvaquentic Endoaquolls
1173 No Fluvaquentic Epiaquepts
1174 No Fluvaquentic Epiaquolls
1175 obsolete_Fluvaquentic Eutrochrepts
1176 obsolete_Fluvaquentic Eutropepts
1177 No Fluvaquentic Eutrudepts
1178 No Fluvaquentic Fibristels
1179 No Fluvaquentic Gelaquepts
1180 obsolete_Fluvaquentic Haplaquepts
1181 obsolete_Fluvaquentic Haplaquolls
1182 obsolete_Fluvaquentic Haploborolls
1183 No Fluvaquentic Haplocryepts
1184 No Fluvaquentic Haplocryolls
SSURGO Version: 2.2.3 Page 146
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1185 No Fluvaquentic Haplofibrists
1186 No Fluvaquentic Haplohemists
1187 No Fluvaquentic Haplorthels
1188 No Fluvaquentic Haplosaprists
1189 No Fluvaquentic Haploxerolls
1190 No Fluvaquentic Hapludolls
1191 No Fluvaquentic Haplustolls
1192 No Fluvaquentic Hemistels
1193 No Fluvaquentic Historthels
1194 No Fluvaquentic Humaquepts
1195 No Fluvaquentic Humicryepts
1196 obsolete_Fluvaquentic Medifibrists
1197 obsolete_Fluvaquentic Medihemists
1198 obsolete_Fluvaquentic Medisaprists
1199 No Fluvaquentic Sapristels
1200 No Fluvaquentic Sphagnofibrists
1201 obsolete_Fluvaquentic Tropofibrists
1202 obsolete_Fluvaquentic Tropohemists
1203 obsolete_Fluvaquentic Troposaprists
1204 Fluvaquentic Vertic
Endoaquolls
No
1205 Fluvaquentic Vertic
Epiaquolls
No
1206 obsolete_Fluvaquentic Xerochrepts
1207 No Fluventic Aquicambids
1208 No Fluventic Calciudolls
1209 obsolete_Fluventic Camborthids
1210 obsolete_Fluventic Cryoborolls
1211 obsolete_Fluventic Dystrochrepts
1212 No Fluventic Dystrocryepts
1213 obsolete_Fluventic Dystropepts
1214 No Fluventic Dystroxerepts
1215 No Fluventic Dystrudepts
SSURGO Version: 2.2.3 Page 147
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1216 No Fluventic Dystrustepts
1217 No Fluventic Endoaquepts
1218 obsolete_Fluventic Eutrochrepts
1219 obsolete_Fluventic Eutropepts
1220 No Fluventic Eutrudepts
1221 obsolete_Fluventic Haplaquolls
1222 obsolete_Fluventic Haploborolls
1223 No Fluventic Haplocambids
1224 No Fluventic Haplocryepts
1225 No Fluventic Haplocryolls
1226 No Fluventic Haplorthels
1227 No Fluventic Haploxerepts
1228 No Fluventic Haploxerolls
1229 No Fluventic Hapludolls
1230 obsolete_Fluventic Haplumbrepts
1231 No Fluventic Haplustepts
1232 No Fluventic Haplustolls
1233 No Fluventic Historthels
1234 Fluventic Humic
Dystroxerepts
No
1235 No Fluventic Humic Dystrudepts
1236 No Fluventic Humicryepts
1237 obsolete_Fluventic Humitropepts
1238 obsolete_Fluventic Medihemists
1239 Fluventic Umbric
Dystrochrepts
Yes
1240 obsolete_Fluventic Ustochrepts
1241 obsolete_Fluventic Ustropepts
1242 obsolete_Fluventic Xerochrepts
1243 obsolete_Fluventic Xerumbrepts
1244 obsolete_Fragiaquic Dystrochrepts
1245 No Fragiaquic Dystroxerepts
1246 No Fragiaquic Dystrudepts
SSURGO Version: 2.2.3 Page 148
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1247 obsolete_Fragiaquic Eutroboralfs
1248 obsolete_Fragiaquic Eutrochrepts
1249 No Fragiaquic Eutrudepts
1250 obsolete_Fragiaquic Glossoboralfs
1251 No Fragiaquic Glossudalfs
1252 No Fragiaquic Haplorthods
1253 No Fragiaquic Haploxeralfs
1254 No Fragiaquic Hapludalfs
1255 No Fragiaquic Hapludults
1256 No Fragiaquic Kanhapludults
1257 No Fragiaquic Paleudalfs
1258 No Fragiaquic Paleudults
1259 No Fragiaquic Palexeralfs
1260 obsolete_Fragiaquic Xerochrepts
1261 obsolete_Fragic Dystrochrepts
1262 No Fragic Dystroxerepts
1263 No Fragic Dystrudepts
1264 No Fragic Endoaqualfs
1265 No Fragic Endoaquepts
1266 No Fragic Epiaqualfs
1267 No Fragic Epiaquepts
1268 No Fragic Epiaquults
1269 obsolete_Fragic Eutroboralfs
1270 obsolete_Fragic Eutrochrepts
1271 No Fragic Eutrudepts
1272 No Fragic Glossaqualfs
1273 obsolete_Fragic Glossoboralfs
1274 No Fragic Glossocryalfs
1275 No Fragic Glossudalfs
1276 No Fragic Haplorthods
1277 No Fragic Haploxeralfs
1278 No Fragic Haploxerepts
SSURGO Version: 2.2.3 Page 149
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1279 No Fragic Hapludalfs
1280 No Fragic Hapludults
1281 No Fragic Kanhapludults
1282 No Fragic Oxyaquic Hapludalfs
1283 No Fragic Paleudalfs
1284 No Fragic Paleudults
1285 No Fragic Palexeralfs
1286 obsolete_Fragic Xerochrepts
1287 No Glacic Anhyorthels
1288 No Glacic Anhyturbels
1289 No Glacic Aquiturbels
1290 No Glacic Aquorthels
1291 No Glacic Argiorthels
1292 No Glacic Folistels
1293 No Glacic Haplorthels
1294 No Glacic Haploturbels
1295 No Glacic Historthels
1296 No Glacic Histoturbels
1297 No Glacic Molliturbels
1298 No Glacic Mollorthels
1299 No Glacic Psammorthels
1300 No Glacic Psammoturbels
1301 No Glacic Umbriturbels
1302 No Glacic Umbrorthels
1303 obsolete_Glossaquic Eutroboralfs
1304 obsolete_Glossaquic Fragiudalfs
1305 No Glossaquic Fragiudults
1306 No Glossaquic Hapludalfs
1307 No Glossaquic Natrudalfs
1308 No Glossaquic Paleudalfs
1309 obsolete_Glossic Cryoboralfs
1310 obsolete_Glossic Eutroboralfs
SSURGO Version: 2.2.3 Page 150
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1311 obsolete_Glossic Fragiudalfs
1312 No Glossic Fragiudults
1313 No Glossic Hapludalfs
1314 No Glossic Natraqualfs
1315 No Glossic Natraquolls
1316 No Glossic Natrargids
1317 obsolete_Glossic Natriborolls
1318 obsolete_Glossic Natrudalfs
1319 No Glossic Natrudolls
1320 No Glossic Natrustolls
1321 Glossic Oxyaquic
Eutroboralfs
Yes
1322 No Glossic Paleudalfs
1323 obsolete_Glossic Udic Natriborolls
1324 No Glossic Ustic Natrargids
1325 obsolete_Glossic Ustollic Natrargids
1326 No Glossic Vertic Natrudolls
1327 No Glossic Vertic Natrustolls
1328 obsolete_Glossoboralfic
1329 obsolete_Glossoboric Hapludalfs
1330 No Grossarenic Alaquods
1331 No Grossarenic Alorthods
1332 No Grossarenic Argiaquolls
1333 No Grossarenic Endoaqualfs
1334 No Grossarenic Endoaquults
1335 obsolete_Grossarenic Entic Alorthods
1336 Grossarenic Entic
Haplohumods
Yes
1337 No Grossarenic Epiaqualfs
1338 No Grossarenic Epiaquults
1339 obsolete_Grossarenic Glossaqualfs
1340 obsolete_Grossarenic Haplaquods
1341 obsolete_Grossarenic Haplohumods
SSURGO Version: 2.2.3 Page 151
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1342 No Grossarenic Haploxerults
1343 No Grossarenic Hapludults
1344 No Grossarenic Kandiaqualfs
1345 No Grossarenic Kandiaquults
1346 No Grossarenic Kandiudalfs
1347 No Grossarenic Kandiudults
1348 No Grossarenic Kandiustalfs
1349 obsolete_Grossarenic Natrustalfs
1350 obsolete_Grossarenic Ochraqualfs
1351 No Grossarenic Paleaquults
1352 No Grossarenic Paleudalfs
1353 No Grossarenic Paleudults
1354 No Grossarenic Paleustalfs
1355 Grossarenic Plinthic
Kandiudalfs
No
1356 Grossarenic Plinthic
Kandiudults
No
1357 Grossarenic Plinthic
Paleudalfs
No
1358 Grossarenic Plinthic
Paleudults
No
1359 obsolete_Grossarenic Umbraqualfs
1360 No Gypsic Anhyorthels
1361 No Gypsic Anhyturbels
1362 No Gypsic Aquisalids
1363 No Gypsic Calciustepts
1364 No Gypsic Calciustolls
1365 No Gypsic Haplosalids
1366 No Gypsic Haploxerepts
1367 No Gypsic Haplustepts
1368 No Gypsic Haplusterts
1369 obsolete_Gypsic Ustochrepts
1370 obsolete_Gypsic Xerochrepts
1371 No Halic Calciusterts
SSURGO Version: 2.2.3 Page 152
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1372 No Halic Durixererts
1373 No Halic Endoaquerts
1374 No Halic Epiaquerts
1375 No Halic Gypsiusterts
1376 No Halic Haplosaprists
1377 No Halic Haplotorrerts
1378 No Halic Haploxererts
1379 No Halic Haplusterts
1380 No Halic Terric Haplosaprists
1381 obsolete_Haplaquic
1382 obsolete_Haplaquodic
1383 obsolete_Haplaquodic Humaquepts
1384 Haplaquodic
Quartzipsamments
Yes
1385 No Haplargidic Natrustalfs
1386 obsolete_Haplic Acrorthox
1387 obsolete_Haplic Andaquepts
1388 obsolete_Haplic Cryohumods
1389 obsolete_Haplic Durargids
1390 No Haplic Durixeralfs
1391 No Haplic Durixererts
1392 No Haplic Durixerolls
1393 No Haplic Durustolls
1394 No Haplic Glossudalfs
1395 Haplic Haploxerollic
Durixerolls
No
1396 obsolete_Haplic Nadurargids
1397 No Haplic Natrargids
1398 No Haplic Palexeralfs
1399 No Haplic Palexerollic Durixerolls
1400 No Haplic Palexerolls
1401 obsolete_Haplic Placaquepts
1402 No Haplic Plinthustults
SSURGO Version: 2.2.3 Page 153
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1403 No Haplic Sulfaquents
1404 No Haplic Torriarents
1405 No Haplic Udarents
1406 No Haplic Ustarents
1407 No Haplic Ustic Natrargids
1408 obsolete_Haplic Vermiborolls
1409 No Haplic Vermudolls
1410 obsolete_Haplic Vermustolls
1411 No Haplic Xerarents
1412 No Haplocalcidic Haplustepts
1413 obsolete_Haplocalcidic Ustochrepts
1414 No Haploduridic Durixerolls
1415 No Haploduridic Durustolls
1416 obsolete_Haploduridic Torriorthents
1417 No Haploduridic Torripsamments
1418 Haploduridic Xeric
Torriorthents
Yes
1419 Haploduridic Xeric
Torripsamments
Yes
1420 No Haploxeralfic Argidurids
1421 No Haploxeralfic Natrargids
1422 No Haploxerandic Dystrocryepts
1423 No Haploxerandic Haplocryepts
1424 No Haploxerandic Humicryepts
1425 obsolete_Haploxerollic Durargids
1426 No Haploxerollic Durixerolls
1427 obsolete_Haploxerollic Durorthids
1428 obsolete_Haploxerollic Nadurargids
1429 obsolete_Haploxerollic Natrargids
1430 obsolete_Hapludic Vermiborolls
1431 obsolete_Hapludollic
1432 obsolete_Hapludollic Arents
1433 No Haplustandic Haplocryepts
SSURGO Version: 2.2.3 Page 154
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1434 obsolete_Haplustollic Durorthids
1435 obsolete_Haplustollic Natrargids
1436 obsolete_Hemic Borofibrists
1437 obsolete_Hemic Borosaprists
1438 No Hemic Glacistels
1439 No Hemic Haplofibrists
1440 No Hemic Haplosaprists
1441 obsolete_Hemic Medifibrists
1442 obsolete_Hemic Medisaprists
1443 No Hemic Sphagnofibrists
1444 obsolete_Hemic Terric Borofibrists
1445 obsolete_Hemic Terric Borosaprists
1446 obsolete_Hemic Terric Medifibrists
1447 obsolete_Hemic Terric Medisaprists
1448 obsolete_Hemic Terric Tropofibrists
1449 obsolete_Hemic Terric Troposaprists
1450 obsolete_Hemic Tropofibrists
1451 obsolete_Hemic Troposaprists
1452 No Histic Alaquods
1453 obsolete_Histic Andaquepts
1454 No Histic Cryaquands
1455 No Histic Cryaquepts
1456 No Histic Cryaquolls
1457 No Histic Duraquands
1458 No Histic Duraquods
1459 No Histic Endoaquands
1460 No Histic Endoaquods
1461 No Histic Endoaquolls
1462 No Histic Epiaquands
1463 No Histic Epiaquods
1464 No Histic Epiaquolls
1465 No Histic Eutraquox
SSURGO Version: 2.2.3 Page 155
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1466 obsolete_Histic Fluvaquents
1467 No Histic Fragiaquods
1468 No Histic Gelaquands
1469 No Histic Gelaquepts
1470 No Histic Glossaqualfs
1471 obsolete_Histic Haplaquods
1472 obsolete_Histic Haplaquolls
1473 No Histic Haplaquox
1474 No Histic Humaquepts
1475 No Histic Lithic Cryaquepts
1476 obsolete_Histic Pergelic Cryaquepts
1477 No Histic Placaquands
1478 obsolete_Histic Placaquepts
1479 No Histic Placic Petraquepts
1480 No Histic Sulfaquents
1481 obsolete_Histic Tropaquepts
1482 obsolete_Histic Tropaquods
1483 No Histic Vitraquands
1484 No Humaqueptic Endoaquents
1485 No Humaqueptic Epiaquents
1486 No Humaqueptic Fluvaquents
1487 No Humaqueptic Psammaquents
1488 No Humic Acroperox
1489 No Humic Acrudox
1490 No Humic Acrustox
1491 No Humic Cryaquepts
1492 obsolete_Humic Cryorthods
1493 No Humic Duricryods
1494 No Humic Durustands
1495 obsolete_Humic Dystrocryepts
1496 No Humic Dystrogelepts
1497 No Humic Dystroxerepts
SSURGO Version: 2.2.3 Page 156
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1498 No Humic Dystrudepts
1499 No Humic Dystrustepts
1500 No Humic Endoaquepts
1501 No Humic Epiaquepts
1502 No Humic Eutraquox
1503 obsolete_Humic Eutrocryepts
1504 No Humic Eutrogelepts
1505 No Humic Eutroperox
1506 No Humic Eutrudepts
1507 No Humic Eutrudox
1508 No Humic Eutrustox
1509 No Humic Fragiaqualfs
1510 No Humic Fragiaquepts
1511 obsolete_Humic Fragiorthods
1512 No Humic Fragiudepts
1513 No Humic Fragiudults
1514 No Humic Fragixerepts
1515 No Humic Gelaquepts
1516 obsolete_Humic Haplaquepts
1517 No Humic Haplaquox
1518 No Humic Haploperox
1519 obsolete_Humic Haplorthods
1520 No Humic Haploxerands
1521 No Humic Haploxerepts
1522 No Humic Hapludox
1523 No Humic Hapludults
1524 No Humic Haplustands
1525 No Humic Haplustox
1526 No Humic Inceptic Eutroperox
1527 No Humic Inceptic Eutrudox
1528 No Humic Inceptic Eutrustox
1529 No Humic Kandiperox
SSURGO Version: 2.2.3 Page 157
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1530 No Humic Kandiudox
1531 No Humic Kandiustox
1532 obsolete_Humic Lithic
1533 obsolete_Humic Lithic Cryorthods
1534 obsolete_Humic Lithic Dystrocryepts
1535 No Humic Lithic Dystroxerepts
1536 No Humic Lithic Dystrudepts
1537 obsolete_Humic Lithic Eutrocryepts
1538 No Humic Lithic Eutrudepts
1539 No Humic Lithic Haploxerepts
1540 No Humic Pachic Dystrudepts
1541 obsolete_Humic Pergelic Cryaquepts
1542 No Humic Placocryods
1543 Humic Psammentic
Dystrudepts
No
1544 obsolete_Humic Rhodic
1545 No Humic Rhodic Acroperox
1546 No Humic Rhodic Acrudox
1547 No Humic Rhodic Acrustox
1548 No Humic Rhodic Eutroperox
1549 No Humic Rhodic Eutrudox
1550 No Humic Rhodic Eutrustox
1551 No Humic Rhodic Haploperox
1552 No Humic Rhodic Hapludox
1553 No Humic Rhodic Haplustox
1554 No Humic Rhodic Kandiperox
1555 No Humic Rhodic Kandiudox
1556 No Humic Rhodic Kandiustox
1557 No Humic Sombriperox
1558 No Humic Sombriudox
1559 No Humic Sombriustox
1560 No Humic Udivitrands
1561 No Humic Ustivitrands
SSURGO Version: 2.2.3 Page 158
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1562 No Humic Vitricryands
1563 No Humic Vitrigelands
1564 No Humic Vitrixerands
1565 No Humic Xanthic Acroperox
1566 No Humic Xanthic Acrudox
1567 No Humic Xanthic Acrustox
1568 No Humic Xanthic Eutroperox
1569 No Humic Xanthic Eutrudox
1570 No Humic Xanthic Eutrustox
1571 No Humic Xanthic Haploperox
1572 No Humic Xanthic Hapludox
1573 No Humic Xanthic Haplustox
1574 No Humic Xanthic Kandiperox
1575 No Humic Xanthic Kandiudox
1576 No Humic Xanthic Kandiustox
1577 No Humic Xeric Vitricryands
1578 obsolete_Humoxic
1579 obsolete_Humoxic Tropohumults
1580 No Hydraquentic Humaquepts
1581 No Hydraquentic Sulfaquepts
1582 obsolete_Hydric Borofibrists
1583 obsolete_Hydric Borohemists
1584 No Hydric Cryofibrists
1585 No Hydric Cryohemists
1586 No Hydric Durudands
1587 obsolete_Hydric Dystrandepts
1588 No Hydric Endoaquands
1589 No Hydric Epiaquands
1590 No Hydric Fulvudands
1591 No Hydric Haplofibrists
1592 No Hydric Haplohemists
1593 No Hydric Hapludands
SSURGO Version: 2.2.3 Page 159
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1594 obsolete_Hydric Lithic Dystrandepts
1595 obsolete_Hydric Lithic Fulvudands
1596 obsolete_Hydric Medifibrists
1597 obsolete_Hydric Medihemists
1598 No Hydric Melanaquands
1599 No Hydric Melanudands
1600 obsolete_Hydric Pachic Durudands
1601 obsolete_Hydric Pachic Fulvudands
1602 No Hydric Pachic Melanaquands
1603 No Hydric Pachic Melanudands
1604 No Hydric Pachic Placudands
1605 No Hydric Placudands
1606 No Hydric Sphagnofibrists
1607 obsolete_Hydric Thaptic Fulvudands
1608 No Hydric Thaptic Hapludands
1609 obsolete_Hydric Tropofibrists
1610 obsolete_Hydric Tropohemists
1611 No Inceptic Eutroperox
1612 No Inceptic Eutrudox
1613 No Inceptic Eutrustox
1614 No Inceptic Fragixeralfs
1615 No Inceptic Haplocryalfs
1616 No Inceptic Haploxeralfs
1617 No Inceptic Hapludalfs
1618 No Inceptic Hapludox
1619 No Inceptic Hapludults
1620 No Inceptic Haplustalfs
1621 No Inceptic Haplustox
1622 No Inceptic Haprendolls
1623 No Inceptic Rhodoxeralfs
1624 No Kandic Albaquults
1625 No Kandic Paleustalfs
SSURGO Version: 2.2.3 Page 160
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1626 No Kandic Plinthaquults
1627 obsolete_Kandic Plinthustalfs
1628 No Kandiudalfic Eutroperox
1629 No Kandiudalfic Eutrudox
1630 No Kandiustalfic Eutrustox
1631 No Kanhaplic Haplustalfs
1632 No Kanhaplic Haplustults
1633 No Kanhaplic Rhodustalfs
1634 No Lamellic Argiudolls
1635 obsolete_Lamellic Cryoboralfs
1636 obsolete_Lamellic Cryochrepts
1637 No Lamellic Cryopsamments
1638 No Lamellic Cryorthents
1639 obsolete_Lamellic Dystrochrepts
1640 No Lamellic Dystrocryepts
1641 No Lamellic Dystrudepts
1642 obsolete_Lamellic Eutroboralfs
1643 obsolete_Lamellic Eutrochrepts
1644 obsolete_Lamellic Eutrocryepts
1645 No Lamellic Eutrudepts
1646 obsolete_Lamellic Glossoboralfs
1647 No Lamellic Haplocryalfs
1648 No Lamellic Haplocryepts
1649 No Lamellic Haplorthods
1650 No Lamellic Haploxeralfs
1651 No Lamellic Haploxerepts
1652 No Lamellic Haploxerults
1653 No Lamellic Hapludalfs
1654 No Lamellic Hapludults
1655 No Lamellic Haplustalfs
1656 No Lamellic Haplustepts
1657 No Lamellic Humicryepts
SSURGO Version: 2.2.3 Page 161
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1658 Lamellic Oxyaquic
Eutroboralfs
Yes
1659 Lamellic Oxyaquic
Haplorthods
No
1660 No Lamellic Paleudalfs
1661 No Lamellic Paleudults
1662 No Lamellic Paleustalfs
1663 No Lamellic Palexeralfs
1664 No Lamellic Quartzipsamments
1665 No Lamellic Udipsamments
1666 Lamellic Ustic
Quartzipsamments
No
1667 No Lamellic Ustipsamments
1668 obsolete_Lamellic Ustochrepts
1669 obsolete_Lamellic Xerochrepts
1670 No Lamellic Xeropsamments
1671 No Leptic Calcitorrerts
1672 No Leptic Calciusterts
1673 No Leptic Calcixererts
1674 No Leptic Dystraquerts
1675 No Leptic Dystruderts
1676 No Leptic Dystrusterts
1677 No Leptic Endoaquerts
1678 No Leptic Epiaquerts
1679 No Leptic Gypsiusterts
1680 No Leptic Haplogypsids
1681 No Leptic Haplotorrerts
1682 No Leptic Haploxererts
1683 No Leptic Hapluderts
1684 No Leptic Haplusterts
1685 No Leptic Natralbolls
1686 obsolete_Leptic Natriborolls
1687 No Leptic Natrudolls
SSURGO Version: 2.2.3 Page 162
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1688 No Leptic Natrustalfs
1689 No Leptic Natrustolls
1690 No Leptic Salaquerts
1691 No Leptic Salitorrerts
1692 No Leptic Salusterts
1693 No Leptic Torrertic Natrustalfs
1694 No Leptic Torrertic Natrustolls
1695 No Leptic Udic Haplusterts
1696 obsolete_Leptic Vertic Natriborolls
1697 No Leptic Vertic Natrudolls
1698 No Leptic Vertic Natrustolls
1699 obsolete_Limnic Borofibrists
1700 obsolete_Limnic Borohemists
1701 obsolete_Limnic Borosaprists
1702 No Limnic Cryosaprists
1703 No Limnic Haplofibrists
1704 No Limnic Haplohemists
1705 No Limnic Haplosaprists
1706 obsolete_Limnic Medifibrists
1707 obsolete_Limnic Medihemists
1708 obsolete_Limnic Medisaprists
1709 No Limnic Sphagnofibrists
1710 obsolete_Limnic Tropofibrists
1711 obsolete_Limnic Tropohemists
1712 obsolete_Limnic Troposaprists
1713 No Lithic Acroperox
1714 No Lithic Acrotorrox
1715 No Lithic Acrudox
1716 No Lithic Acrustox
1717 No Lithic Alaquods
1718 No Lithic Anhyorthels
1719 No Lithic Anhyturbels
SSURGO Version: 2.2.3 Page 163
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1720 No Lithic Aquiturbels
1721 No Lithic Aquorthels
1722 obsolete_Lithic Argiborolls
1723 No Lithic Argicryids
1724 No Lithic Argicryolls
1725 No Lithic Argigypsids
1726 No Lithic Argiorthels
1727 No Lithic Argiudolls
1728 No Lithic Argiustolls
1729 No Lithic Argixerolls
1730 obsolete_Lithic Borofibrists
1731 obsolete_Lithic Borofolists
1732 obsolete_Lithic Borohemists
1733 obsolete_Lithic Borosaprists
1734 No Lithic Calciargids
1735 obsolete_Lithic Calciborolls
1736 No Lithic Calcicryepts
1737 No Lithic Calcicryids
1738 No Lithic Calcicryolls
1739 No Lithic Calcigypsids
1740 obsolete_Lithic Calciorthids
1741 No Lithic Calciudolls
1742 No Lithic Calciustepts
1743 No Lithic Calciusterts
1744 No Lithic Calciustolls
1745 No Lithic Calcixerepts
1746 No Lithic Calcixererts
1747 No Lithic Calcixerolls
1748 obsolete_Lithic Camborthids
1749 obsolete_Lithic Cryandepts
1750 No Lithic Cryaquands
1751 No Lithic Cryaquepts
SSURGO Version: 2.2.3 Page 164
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1752 No Lithic Cryaquods
1753 obsolete_Lithic Cryoboralfs
1754 obsolete_Lithic Cryoborolls
1755 obsolete_Lithic Cryochrepts
1756 No Lithic Cryofibrists
1757 No Lithic Cryofolists
1758 No Lithic Cryohemists
1759 obsolete_Lithic Cryohumods
1760 No Lithic Cryopsamments
1761 No Lithic Cryorthents
1762 obsolete_Lithic Cryorthods
1763 No Lithic Cryosaprists
1764 No Lithic Cryrendolls
1765 obsolete_Lithic Cryumbrepts
1766 obsolete_Lithic Dystrandepts
1767 obsolete_Lithic Dystrochrepts
1768 No Lithic Dystrocryepts
1769 No Lithic Dystrogelepts
1770 obsolete_Lithic Dystropepts
1771 No Lithic Dystroxerepts
1772 No Lithic Dystrudepts
1773 No Lithic Dystrustepts
1774 No Lithic Dystrusterts
1775 No Lithic Endoaquands
1776 No Lithic Endoaquents
1777 No Lithic Endoaquepts
1778 No Lithic Endoaquods
1779 No Lithic Endoaquolls
1780 No Lithic Epiaquods
1781 obsolete_Lithic Eutrandepts
1782 obsolete_Lithic Eutroboralfs
1783 obsolete_Lithic Eutrochrepts
SSURGO Version: 2.2.3 Page 165
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1784 obsolete_Lithic Eutrocryepts
1785 No Lithic Eutrogelepts
1786 obsolete_Lithic Eutropepts
1787 No Lithic Eutroperox
1788 No Lithic Eutrotorrox
1789 No Lithic Eutrudepts
1790 No Lithic Eutrudox
1791 No Lithic Eutrustox
1792 No Lithic Fibristels
1793 No Lithic Folistels
1794 No Lithic Fulvicryands
1795 No Lithic Fulvudands
1796 No Lithic Gelaquepts
1797 obsolete_Lithic Glossoboralfs
1798 No Lithic Glossocryalfs
1799 No Lithic Gypsiusterts
1800 obsolete_Lithic Haplaquepts
1801 obsolete_Lithic Haplaquolls
1802 No Lithic Haplargids
1803 obsolete_Lithic Haploborolls
1804 No Lithic Haplocalcids
1805 No Lithic Haplocambids
1806 No Lithic Haplocryalfs
1807 No Lithic Haplocryands
1808 No Lithic Haplocryepts
1809 No Lithic Haplocryids
1810 No Lithic Haplocryods
1811 No Lithic Haplocryolls
1812 No Lithic Haplofibrists
1813 No Lithic Haplogelods
1814 No Lithic Haplogelolls
1815 No Lithic Haplogypsids
SSURGO Version: 2.2.3 Page 166
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1816 No Lithic Haplohemists
1817 No Lithic Haplohumods
1818 No Lithic Haplohumults
1819 No Lithic Haploperox
1820 No Lithic Haplorthels
1821 No Lithic Haplorthods
1822 No Lithic Haplosaprists
1823 No Lithic Haplotorrands
1824 No Lithic Haplotorrox
1825 No Lithic Haploturbels
1826 No Lithic Haploxeralfs
1827 No Lithic Haploxerands
1828 No Lithic Haploxerepts
1829 No Lithic Haploxererts
1830 No Lithic Haploxerolls
1831 No Lithic Haploxerults
1832 No Lithic Hapludalfs
1833 No Lithic Hapludands
1834 No Lithic Hapluderts
1835 No Lithic Hapludolls
1836 No Lithic Hapludox
1837 No Lithic Hapludults
1838 obsolete_Lithic Haplumbrepts
1839 No Lithic Haplustalfs
1840 No Lithic Haplustands
1841 No Lithic Haplustepts
1842 No Lithic Haplusterts
1843 No Lithic Haplustolls
1844 No Lithic Haplustox
1845 No Lithic Haplustults
1846 No Lithic Haprendolls
1847 No Lithic Hemistels
SSURGO Version: 2.2.3 Page 167
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1848 No Lithic Historthels
1849 No Lithic Histoturbels
1850 No Lithic Humicryepts
1851 No Lithic Humicryods
1852 No Lithic Humigelods
1853 obsolete_Lithic Humitropepts
1854 obsolete_Lithic Hydrandepts
1855 No Lithic Hydrocryands
1856 No Lithic Hydrudands
1857 No Lithic Kandiperox
1858 No Lithic Kandiudox
1859 No Lithic Kandiustox
1860 No Lithic Kanhaplohumults
1861 No Lithic Kanhapludalfs
1862 No Lithic Kanhapludults
1863 No Lithic Kanhaplustalfs
1864 No Lithic Kanhaplustults
1865 obsolete_Lithic Medifibrists
1866 obsolete_Lithic Medifolists
1867 obsolete_Lithic Medihemists
1868 obsolete_Lithic Medisaprists
1869 No Lithic Melanaquands
1870 No Lithic Melanocryands
1871 No Lithic Melanudands
1872 obsolete_Lithic Mollic Cryoboralfs
1873 No Lithic Mollic Haploxeralfs
1874 obsolete_Lithic Mollic Vitrandepts
1875 No Lithic Molliturbels
1876 No Lithic Mollorthels
1877 No Lithic Natrargids
1878 No Lithic Natrigypsids
1879 Lithic Petrocalcic
Calciustepts
No
SSURGO Version: 2.2.3 Page 168
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1880 No Lithic Petrocalcic Calciustolls
1881 No Lithic Placaquands
1882 No Lithic Placudands
1883 No Lithic Psammaquents
1884 No Lithic Psammorthels
1885 No Lithic Psammoturbels
1886 No Lithic Quartzipsamments
1887 obsolete_Lithic Rendolls
1888 No Lithic Rhodoxeralfs
1889 No Lithic Rhodudults
1890 No Lithic Rhodustalfs
1891 No Lithic Rhodustults
1892 Lithic Ruptic-Alfic
Dystrochrepts
Yes
1893 Lithic Ruptic-Alfic
Eutrochrepts
Yes
1894 Lithic Ruptic-Argic
Cryoborolls
Yes
1895 obsolete_Lithic Ruptic-Entic
1896 Lithic Ruptic-Entic
Cryoborolls
Yes
1897 Lithic Ruptic-Entic
Cryumbrepts
Yes
1898 No Lithic Ruptic-Entic Haplargids
1899 obsolete_Lithic Ruptic-Entic Hapludults
1900 obsolete_Lithic Ruptic-Entic Haplustolls
1901 Lithic Ruptic-Entic Xerollic
Haplargids
Yes
1902 Lithic Ruptic-Inceptic
Haploxeralfs
No
1903 Lithic Ruptic-Inceptic
Haploxerults
No
1904 Lithic Ruptic-Ultic
Dystrochrepts
Yes
SSURGO Version: 2.2.3 Page 169
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1905 Lithic Ruptic-Xerochreptic
Haploxeralfs
Yes
1906 Lithic Ruptic-Xerochreptic
Haploxerults
Yes
1907 Lithic Ruptic-Xerorthentic
Xerochrepts
Yes
1908 No Lithic Salusterts
1909 No Lithic Sapristels
1910 No Lithic Sombriperox
1911 No Lithic Sombriudox
1912 No Lithic Sombriustox
1913 No Lithic Sphagnofibrists
1914 No Lithic Torrifolists
1915 No Lithic Torriorthents
1916 No Lithic Torripsamments
1917 obsolete_Lithic Tropaquepts
1918 obsolete_Lithic Tropofibrists
1919 obsolete_Lithic Tropofolists
1920 obsolete_Lithic Tropohemists
1921 obsolete_Lithic Tropopsamments
1922 obsolete_Lithic Troporthents
1923 obsolete_Lithic Troposaprists
1924 obsolete_Lithic Tropudalfs
1925 obsolete_Lithic Udic
1926 No Lithic Udifolists
1927 No Lithic Udipsamments
1928 No Lithic Udivitrands
1929 No Lithic Udorthents
1930 No Lithic Ultic Argixerolls
1931 No Lithic Ultic Haploxerolls
1932 obsolete_Lithic Umbric
1933 obsolete_Lithic Umbric Vitrandepts
1934 No Lithic Umbriturbels
SSURGO Version: 2.2.3 Page 170
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1935 No Lithic Umbrorthels
1936 obsolete_Lithic Ustic Calciorthids
1937 No Lithic Ustic Haplargids
1938 No Lithic Ustic Haplocalcids
1939 No Lithic Ustic Haplocambids
1940 No Lithic Ustic Natrargids
1941 No Lithic Ustic Torriorthents
1942 No Lithic Ustifolists
1943 No Lithic Ustipsamments
1944 No Lithic Ustivitrands
1945 obsolete_Lithic Ustochrepts
1946 obsolete_Lithic Ustollic Calciorthids
1947 obsolete_Lithic Ustollic Haplargids
1948 No Lithic Ustorthents
1949 obsolete_Lithic Ustropepts
1950 obsolete_Lithic Vermiborolls
1951 No Lithic Vermudolls
1952 No Lithic Vermustolls
1953 obsolete_Lithic Vertic
1954 obsolete_Lithic Vertic Argiustolls
1955 obsolete_Lithic Vertic Ustropepts
1956 obsolete_Lithic Vitrandepts
1957 No Lithic Vitraquands
1958 No Lithic Vitricryands
1959 No Lithic Vitritorrands
1960 No Lithic Vitrixerands
1961 No Lithic Xeric Haplargids
1962 No Lithic Xeric Haplocalcids
1963 No Lithic Xeric Haplocambids
1964 No Lithic Xeric Natrargids
1965 No Lithic Xeric Torriorthents
1966 obsolete_Lithic Xerochrepts
SSURGO Version: 2.2.3 Page 171
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1967 obsolete_Lithic Xerollic Calciorthids
1968 obsolete_Lithic Xerollic Camborthids
1969 obsolete_Lithic Xerollic Haplargids
1970 obsolete_Lithic Xerollic Natrargids
1971 No Lithic Xeropsamments
1972 No Lithic Xerorthents
1973 obsolete_Lithic Xerumbrepts
1974 No Lithic-Ruptic-Entic Hapludults
1975 No Mollic Albaqualfs
1976 obsolete_Mollic Andaquepts
1977 obsolete_Mollic Cryoboralfs
1978 No Mollic Cryofluvents
1979 No Mollic Endoaqualfs
1980 No Mollic Endoaquents
1981 No Mollic Endoaquepts
1982 No Mollic Epiaqualfs
1983 No Mollic Epiaquents
1984 No Mollic Epiaquepts
1985 obsolete_Mollic Eutroboralfs
1986 No Mollic Fluvaquents
1987 obsolete_Mollic Fragiudalfs
1988 No Mollic Fragixeralfs
1989 No Mollic Glossaqualfs
1990 No Mollic Glossocryalfs
1991 obsolete_Mollic Halaquepts
1992 obsolete_Mollic Haplaquents
1993 obsolete_Mollic Haplaquepts
1994 No Mollic Haplocryalfs
1995 No Mollic Haploxeralfs
1996 No Mollic Hapludalfs
1997 No Mollic Kandiudalfs
1998 No Mollic Natraqualfs
SSURGO Version: 2.2.3 Page 172
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
1999 obsolete_Mollic Natrudalfs
2000 No Mollic Natrustalfs
2001 obsolete_Mollic Ochraqualfs
2002 No Mollic Oxyaquic Hapludalfs
2003 obsolete_Mollic Paleboralfs
2004 No Mollic Palecryalfs
2005 No Mollic Paleudalfs
2006 No Mollic Palexeralfs
2007 No Mollic Psammaquents
2008 obsolete_Mollic Torrerts
2009 No Mollic Udarents
2010 No Mollic Udifluvents
2011 No Mollic Ustifluvents
2012 obsolete_Mollic Vitrandepts
2013 obsolete_Mollic Vitrixerands
2014 No Mollic Xerofluvents
2015 No Natrargidic Natridurids
2016 No Natric Argicryids
2017 No Natric Argiorthels
2018 obsolete_Natric Camborthids
2019 obsolete_Natric Cryoborolls
2020 No Natric Duraquolls
2021 No Natric Durixeralfs
2022 No Natric Durustolls
2023 No Natric Haploxeralfs
2024 No Natric Palexeralfs
2025 obsolete_Natric Palexerolls
2026 No Natric Petroargids
2027 No Natric Petrocalcids
2028 No Natric Vermaqualfs
2029 No Natrixeralfic Natridurids
2030 No Nitric Anhyorthels
SSURGO Version: 2.2.3 Page 173
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2031 No Nitric Anhyturbels
2032 obsolete_Ochreptic Cryoboralfs
2033 obsolete_Ochreptic Eutroboralfs
2034 obsolete_Ochreptic Fragiudalfs
2035 obsolete_Ochreptic Fragixeralfs
2036 obsolete_Ochreptic Glossoboralfs
2037 obsolete_Ochreptic Haploxeralfs
2038 obsolete_Ochreptic Hapludalfs
2039 obsolete_Ochreptic Hapludults
2040 obsolete_Ochreptic Haplustalfs
2041 obsolete_Ochreptic Rhodoxeralfs
2042 No Ombroaquic Haplustults
2043 No Ombroaquic Kandihumults
2044 No Ombroaquic Kandiudults
2045 Ombroaquic
Kanhaplohumults
No
2046 No Ombroaquic Kanhapludults
2047 No Ombroaquic Kanhaplustults
2048 obsolete_Orthic
2049 obsolete_Orthidic Durixerolls
2050 obsolete_Orthidic Durustolls
2051 obsolete_Orthoxic
2052 obsolete_Orthoxic Palehumults
2053 obsolete_Orthoxic Tropohumults
2054 No Oxic Argiudolls
2055 obsolete_Oxic Dystrandepts
2056 obsolete_Oxic Dystropepts
2057 No Oxic Dystrudepts
2058 No Oxic Dystrustepts
2059 No Oxic Hapludands
2060 obsolete_Oxic Haplustalfs
2061 No Oxic Haplustands
2062 No Oxic Haplustepts
SSURGO Version: 2.2.3 Page 174
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2063 No Oxic Haplustolls
2064 obsolete_Oxic Haplustults
2065 obsolete_Oxic Humitropepts
2066 obsolete_Oxic Paleustalfs
2067 obsolete_Oxic Plinthaquults
2068 obsolete_Oxic Rhodustalfs
2069 obsolete_Oxic Tropudalfs
2070 obsolete_Oxic Ustropepts
2071 No Oxyaquic Alorthods
2072 obsolete_Oxyaquic Argiborolls
2073 No Oxyaquic Argicryolls
2074 No Oxyaquic Argiudolls
2075 No Oxyaquic Argiustolls
2076 No Oxyaquic Argixerolls
2077 obsolete_Oxyaquic Calciborolls
2078 No Oxyaquic Calcicryepts
2079 No Oxyaquic Calciustolls
2080 No Oxyaquic Calcixerolls
2081 obsolete_Oxyaquic Cryoboralfs
2082 obsolete_Oxyaquic Cryoborolls
2083 obsolete_Oxyaquic Cryochrepts
2084 No Oxyaquic Cryofluvents
2085 No Oxyaquic Cryopsamments
2086 No Oxyaquic Cryorthents
2087 obsolete_Oxyaquic Cryumbrepts
2088 No Oxyaquic Duricryands
2089 No Oxyaquic Duricryods
2090 obsolete_Oxyaquic Dystrochrepts
2091 No Oxyaquic Dystrocryepts
2092 obsolete_Oxyaquic Dystropepts
2093 No Oxyaquic Dystroxerepts
2094 No Oxyaquic Dystrudepts
SSURGO Version: 2.2.3 Page 175
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2095 No Oxyaquic Dystruderts
2096 obsolete_Oxyaquic Eutroboralfs
2097 obsolete_Oxyaquic Eutrochrepts
2098 obsolete_Oxyaquic Eutrocryepts
2099 obsolete_Oxyaquic Eutropepts
2100 No Oxyaquic Eutrudepts
2101 obsolete_Oxyaquic Fragiboralfs
2102 No Oxyaquic Fragiorthods
2103 No Oxyaquic Fragiudalfs
2104 No Oxyaquic Fraglossudalfs
2105 No Oxyaquic Fulvudands
2106 No Oxyaquic Gelorthents
2107 obsolete_Oxyaquic Glossoboralfs
2108 No Oxyaquic Glossocryalfs
2109 No Oxyaquic Glossudalfs
2110 obsolete_Oxyaquic Haploborolls
2111 No Oxyaquic Haplocryalfs
2112 No Oxyaquic Haplocryands
2113 No Oxyaquic Haplocryepts
2114 No Oxyaquic Haplocryods
2115 No Oxyaquic Haplocryolls
2116 No Oxyaquic Haplohumults
2117 No Oxyaquic Haplorthods
2118 No Oxyaquic Haploxerepts
2119 No Oxyaquic Haploxerolls
2120 No Oxyaquic Hapludalfs
2121 No Oxyaquic Hapludands
2122 No Oxyaquic Hapluderts
2123 No Oxyaquic Hapludolls
2124 No Oxyaquic Hapludults
2125 obsolete_Oxyaquic Haplumbrepts
2126 No Oxyaquic Haplustalfs
SSURGO Version: 2.2.3 Page 176
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2127 No Oxyaquic Haplustepts
2128 No Oxyaquic Haplustolls
2129 No Oxyaquic Haplustox
2130 No Oxyaquic Humicryepts
2131 No Oxyaquic Humicryods
2132 obsolete_Oxyaquic Humitropepts
2133 No Oxyaquic Kandiudalfs
2134 No Oxyaquic Kandiudults
2135 No Oxyaquic Kanhapludalfs
2136 No Oxyaquic Kanhapludults
2137 obsolete_Oxyaquic Paleboralfs
2138 obsolete_Oxyaquic Paleborolls
2139 No Oxyaquic Palecryalfs
2140 No Oxyaquic Palecryolls
2141 No Oxyaquic Palehumults
2142 No Oxyaquic Paleudalfs
2143 No Oxyaquic Paleudolls
2144 No Oxyaquic Paleudults
2145 No Oxyaquic Paleustalfs
2146 Oxyaquic Psammentic
Eutroboralfs
Yes
2147 No Oxyaquic Quartzipsamments
2148 No Oxyaquic Torrifluvents
2149 No Oxyaquic Torriorthents
2150 No Oxyaquic Torripsamments
2151 obsolete_Oxyaquic Tropopsamments
2152 No Oxyaquic Udifluvents
2153 No Oxyaquic Udipsamments
2154 No Oxyaquic Udivitrands
2155 No Oxyaquic Udorthents
2156 No Oxyaquic Ultic Haplorthods
2157 No Oxyaquic Ustifluvents
2158 No Oxyaquic Ustipsamments
SSURGO Version: 2.2.3 Page 177
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2159 No Oxyaquic Ustorthents
2160 obsolete_Oxyaquic Ustropepts
2161 No Oxyaquic Vertic Argiudolls
2162 No Oxyaquic Vertic Glossudalfs
2163 No Oxyaquic Vertic Hapludalfs
2164 No Oxyaquic Vertic Haplustalfs
2165 No Oxyaquic Vertic Paleustalfs
2166 Oxyaquic Vitrandic
Haploxerepts
No
2167 No Oxyaquic Vitricryands
2168 No Oxyaquic Xerofluvents
2169 No Oxyaquic Xeropsamments
2170 No Oxyaquic Xerorthents
2171 obsolete_Pachic Argiborolls
2172 No Pachic Argicryolls
2173 No Pachic Argiudolls
2174 No Pachic Argiustolls
2175 No Pachic Argixerolls
2176 No Pachic Calcicryolls
2177 No Pachic Calciustolls
2178 No Pachic Calcixerolls
2179 obsolete_Pachic Cryoborolls
2180 No Pachic Durudands
2181 No Pachic Fulvicryands
2182 No Pachic Fulvudands
2183 obsolete_Pachic Haploborolls
2184 No Pachic Haplocryolls
2185 No Pachic Haploxerolls
2186 No Pachic Hapludolls
2187 obsolete_Pachic Haplumbrepts
2188 No Pachic Haplustands
2189 No Pachic Haplustolls
2190 No Pachic Melanaquands
SSURGO Version: 2.2.3 Page 178
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2191 No Pachic Melanoxerands
2192 No Pachic Melanudands
2193 obsolete_Pachic Paleborolls
2194 No Pachic Palecryolls
2195 No Pachic Paleudolls
2196 No Pachic Paleustolls
2197 No Pachic Palexerolls
2198 obsolete_Pachic Placudands
2199 obsolete_Pachic Udertic Argiborolls
2200 No Pachic Udertic Argiustolls
2201 obsolete_Pachic Udertic Haploborolls
2202 No Pachic Udertic Haplustolls
2203 obsolete_Pachic Udic Argiborolls
2204 obsolete_Pachic Udic Haploborolls
2205 No Pachic Ultic Argixerolls
2206 No Pachic Ultic Haploxerolls
2207 No Pachic Vermustolls
2208 obsolete_Pachic Vertic Argiborolls
2209 No Pachic Vertic Argiudolls
2210 No Pachic Vertic Argiustolls
2211 obsolete_Pachic Vertic Haploborolls
2212 No Pachic Vertic Hapludolls
2213 No Pachic Vertic Haplustolls
2214 No Pachic Vitric Melanudands
2215 obsolete_Pachic Xerumbrepts
2216 obsolete_Paleargidic Argiborolls
2217 No Paleargidic Durixerolls
2218 obsolete_Paleustollic
2219 obsolete_Paleustollic Chromusterts
2220 obsolete_Palexerollic
2221 obsolete_Palexerollic Chromoxererts
2222 No Palexerollic Durixerolls
SSURGO Version: 2.2.3 Page 179
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2223 obsolete_Paralithic Vertic
2224 obsolete_Paralithic Vertic Haplustolls
2225 obsolete_Pergelic Cryaquands
2226 obsolete_Pergelic Cryaquepts
2227 obsolete_Pergelic Cryaquods
2228 obsolete_Pergelic Cryaquolls
2229 obsolete_Pergelic Cryoborolls
2230 obsolete_Pergelic Cryochrepts
2231 obsolete_Pergelic Cryofibrists
2232 obsolete_Pergelic Cryohemists
2233 obsolete_Pergelic Cryopsamments
2234 obsolete_Pergelic Cryorthents
2235 obsolete_Pergelic Cryorthods
2236 obsolete_Pergelic Cryosaprists
2237 obsolete_Pergelic Cryumbrepts
2238 obsolete_Pergelic Haplocryods
2239 obsolete_Pergelic Humicryods
2240 Pergelic Ruptic-Histic
Cryaquepts
Yes
2241 obsolete_Pergelic Sideric
2242 obsolete_Pergelic Sphagnofibrists
2243 No Petrocalcic Calciaquolls
2244 obsolete_Petrocalcic Calciborolls
2245 No Petrocalcic Calcicryolls
2246 No Petrocalcic Calcitorrerts
2247 No Petrocalcic Calciustepts
2248 No Petrocalcic Calciusterts
2249 No Petrocalcic Calciustolls
2250 No Petrocalcic Calcixerepts
2251 No Petrocalcic Calcixererts
2252 No Petrocalcic Duritorrands
2253 No Petrocalcic Haplusterts
2254 No Petrocalcic Natrudolls
SSURGO Version: 2.2.3 Page 180
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2255 No Petrocalcic Natrustalfs
2256 obsolete_Petrocalcic Paleargids
2257 No Petrocalcic Paleudolls
2258 No Petrocalcic Paleustalfs
2259 No Petrocalcic Paleustolls
2260 No Petrocalcic Palexeralfs
2261 No Petrocalcic Palexerolls
2262 No Petrocalcic Petrogypsids
2263 No Petrocalcic Rhodoxeralfs
2264 Petrocalcic Ustalfic
Paleargids
Yes
2265 Petrocalcic Ustollic
Paleargids
Yes
2266 Petrocalcic Ustollic
Paleustolls
Yes
2267 obsolete_Petrocalcic Vitritorrands
2268 obsolete_Petrocalcic Xerochrepts
2269 Petrocalcic Xerollic
Paleargids
Yes
2270 No Petrocalcidic Palexerolls
2271 No Petroferric Acroperox
2272 No Petroferric Acrotorrox
2273 No Petroferric Acrudox
2274 No Petroferric Acrustox
2275 obsolete_Petroferric Dystropepts
2276 obsolete_Petroferric Endoaquands
2277 obsolete_Petroferric Epiaquands
2278 No Petroferric Eutroperox
2279 No Petroferric Eutrotorrox
2280 No Petroferric Eutrudox
2281 No Petroferric Eutrustox
2282 No Petroferric Haploperox
2283 No Petroferric Haplotorrox
2284 obsolete_Petroferric Hapludands
SSURGO Version: 2.2.3 Page 181
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2285 No Petroferric Hapludox
2286 No Petroferric Haplustox
2287 No Petroferric Haplustults
2288 No Petroferric Kandiperox
2289 No Petroferric Kandiudox
2290 No Petroferric Kandiustox
2291 No Petroferric Sombriperox
2292 No Petroferric Sombriudox
2293 No Petroferric Sombriustox
2294 No Petrogypsic Anhyorthels
2295 No Petrogypsic Anhyturbels
2296 obsolete_Petrogypsic Gypsiorthids
2297 No Petrogypsic Haplosalids
2298 No Petrogypsic Petroargids
2299 No Petrogypsic Petrocryids
2300 No Petrogypsic Ustic Petroargids
2301 No Petronodic Aquicambids
2302 No Petronodic Argigypsids
2303 No Petronodic Calciargids
2304 No Petronodic Calcigypsids
2305 No Petronodic Haplargids
2306 No Petronodic Haplocalcids
2307 No Petronodic Haplocambids
2308 No Petronodic Haplogypsids
2309 No Petronodic Natrargids
2310 No Petronodic Natrigypsids
2311 No Petronodic Paleargids
2312 No Petronodic Ustic Calciargids
2313 No Petronodic Ustic Haplargids
2314 Petronodic Ustic
Haplocalcids
No
2315 Petronodic Ustic
Haplocambids
No
SSURGO Version: 2.2.3 Page 182
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2316 No Petronodic Ustic Paleargids
2317 No Petronodic Xeric Calciargids
2318 Petronodic Xeric
Haplocalcids
No
2319 Petronodic Xeric
Haplocambids
No
2320 No Placic Cryaquods
2321 obsolete_Placic Haplaquods
2322 No Placic Hydrocryands
2323 No Placic Petraquepts
2324 No Plagganthreptic Alorthods
2325 No Plagganthreptic Fragiaquods
2326 No Plagganthreptic Fragiorthods
2327 Plagganthreptic
Haplohumods
No
2328 Plagganthreptic
Udipsamments
No
2329 obsolete_Plaggeptic Alorthods
2330 obsolete_Plaggeptic Fragiaquods
2331 obsolete_Plaggeptic Fragiorthods
2332 obsolete_Plaggeptic Haplohumods
2333 obsolete_Plaggeptic Udipsamments
2334 obsolete_Plaggic
2335 No Plinthaquic Eutroperox
2336 No Plinthaquic Eutrudox
2337 No Plinthaquic Eutrustox
2338 No Plinthaquic Fragiudults
2339 No Plinthaquic Haploperox
2340 No Plinthaquic Hapludox
2341 No Plinthaquic Haplustox
2342 No Plinthaquic Kandiperox
2343 No Plinthaquic Kandiudalfs
2344 No Plinthaquic Kandiudox
2345 No Plinthaquic Kandiudults
SSURGO Version: 2.2.3 Page 183
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2346 No Plinthaquic Kandiustox
2347 No Plinthaquic Kanhapludults
2348 No Plinthaquic Paleudalfs
2349 No Plinthaquic Paleudults
2350 No Plinthic Acraquox
2351 No Plinthic Acroperox
2352 obsolete_Plinthic Acrorthox
2353 No Plinthic Acrudox
2354 No Plinthic Acrustox
2355 No Plinthic Eutraquox
2356 No Plinthic Eutroperox
2357 No Plinthic Eutrudox
2358 No Plinthic Eutrustox
2359 No Plinthic Fragiaqualfs
2360 No Plinthic Fragiaquults
2361 No Plinthic Fragiudults
2362 No Plinthic Haplaquox
2363 No Plinthic Haplohumults
2364 No Plinthic Haploperox
2365 obsolete_Plinthic Haplorthox
2366 No Plinthic Haploxeralfs
2367 No Plinthic Hapludox
2368 No Plinthic Haplustox
2369 No Plinthic Haplustults
2370 No Plinthic Kandiaqualfs
2371 No Plinthic Kandiaquults
2372 No Plinthic Kandihumults
2373 No Plinthic Kandiperox
2374 No Plinthic Kandiudalfs
2375 No Plinthic Kandiudox
2376 No Plinthic Kandiudults
2377 No Plinthic Kandiustalfs
SSURGO Version: 2.2.3 Page 184
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2378 No Plinthic Kandiustox
2379 No Plinthic Kandiustults
2380 No Plinthic Kanhaplaquults
2381 No Plinthic Kanhapludults
2382 No Plinthic Kanhaplustults
2383 No Plinthic Paleaquults
2384 No Plinthic Palehumults
2385 No Plinthic Paleudalfs
2386 No Plinthic Paleudults
2387 No Plinthic Paleustalfs
2388 No Plinthic Palexeralfs
2389 No Plinthic Petraquepts
2390 No Plinthic Quartzipsamments
2391 obsolete_Plinthic Tropaquepts
2392 No Plinthic Umbraquults
2393 obsolete_Plinthudic Fragiaquults
2394 obsolete_Psammaquentic Hapludalfs
2395 obsolete_Psammaquentic Paleudults
2396 No Psammentic Aquiturbels
2397 No Psammentic Aquorthels
2398 No Psammentic Argiudolls
2399 obsolete_Psammentic Cryoboralfs
2400 obsolete_Psammentic Eutroboralfs
2401 obsolete_Psammentic Glossoboralfs
2402 No Psammentic Haplocryalfs
2403 No Psammentic Haploxeralfs
2404 No Psammentic Haploxerolls
2405 No Psammentic Haploxerults
2406 No Psammentic Hapludalfs
2407 No Psammentic Hapludults
2408 obsolete_Psammentic Haplumbrepts
2409 No Psammentic Haplustalfs
SSURGO Version: 2.2.3 Page 185
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2410 No Psammentic Paleudalfs
2411 No Psammentic Paleudults
2412 No Psammentic Paleustalfs
2413 No Psammentic Palexeralfs
2414 No Psammentic Rhodudults
2415 No Psammentic Rhodustults
2416 Quartzipsammentic
Haplumbrepts
Yes
2417 obsolete_Rendollic Eutrochrepts
2418 No Rendollic Eutrudepts
2419 No Rhodic Acroperox
2420 No Rhodic Acrudox
2421 No Rhodic Acrustox
2422 No Rhodic Eutroperox
2423 No Rhodic Eutrudox
2424 No Rhodic Eutrustox
2425 No Rhodic Haploperox
2426 No Rhodic Hapludox
2427 No Rhodic Haplustox
2428 No Rhodic Kandiperox
2429 No Rhodic Kandiudalfs
2430 No Rhodic Kandiudox
2431 No Rhodic Kandiudults
2432 No Rhodic Kandiustalfs
2433 No Rhodic Kandiustox
2434 No Rhodic Kandiustults
2435 No Rhodic Kanhapludalfs
2436 No Rhodic Kanhapludults
2437 No Rhodic Kanhaplustalfs
2438 No Rhodic Kanhaplustults
2439 No Rhodic Paleudalfs
2440 No Rhodic Paleudults
2441 No Rhodic Paleustalfs
SSURGO Version: 2.2.3 Page 186
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2442 No Rhodic Torripsamments
2443 No Rhodic Ustipsamments
2444 No Ruptic Historthels
2445 No Ruptic Histoturbels
2446 obsolete_Ruptic-Alfic Dystrochrepts
2447 No Ruptic-Alfic Dystrudepts
2448 obsolete_Ruptic-Alfic Eutrochrepts
2449 No Ruptic-Alfic Eutrudepts
2450 obsolete_Ruptic-Alfic Lithic
2451 obsolete_Ruptic-Entic Lithic
2452 No Ruptic-Histic Aquiturbels
2453 No Ruptic-Histic Aquorthels
2454 obsolete_Ruptic-Lithic Cryumbrepts
2455 obsolete_Ruptic-Lithic Haploborolls
2456 No Ruptic-Lithic Haplustolls
2457 obsolete_Ruptic-Lithic Xerochrepts
2458 obsolete_Ruptic-Lithic-Entic Hapludults
2459 Ruptic-Lithic-Xerochreptic
Haploxeralfs
Yes
2460 Ruptic-Lithic-Xerochreptic
Haploxerults
Yes
2461 obsolete_Ruptic-Ultic Dystrochrepts
2462 No Ruptic-Ultic Dystrudepts
2463 obsolete_Ruptic-Vertic Albaqualfs
2464 No Salic Anhyorthels
2465 No Salic Anhyturbels
2466 No Salic Aquorthels
2467 No Salic Sulfaquerts
2468 No Salidic Calciustolls
2469 obsolete_Salidic Haploborolls
2470 No Salidic Haplustolls
2471 No Salidic Natrustalfs
2472 No Salidic Sulfaquepts
SSURGO Version: 2.2.3 Page 187
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2473 obsolete_Salorthidic Calciustolls
2474 obsolete_Salorthidic Haploborolls
2475 obsolete_Salorthidic Haplustolls
2476 obsolete_Salorthidic Natrustalfs
2477 obsolete_Salorthidic Sulfaquepts
2478 obsolete_Sapric Borofibrists
2479 obsolete_Sapric Borohemists
2480 No Sapric Glacistels
2481 No Sapric Haplohemists
2482 obsolete_Sapric Medifibrists
2483 obsolete_Sapric Medihemists
2484 obsolete_Sapric Sphagnofibrists
2485 obsolete_Sapric Terric Borofibrists
2486 obsolete_Sapric Terric Borohemists
2487 obsolete_Sapric Terric Medifibrists
2488 obsolete_Sapric Terric Medihemists
2489 obsolete_Sapric Terric Tropofibrists
2490 obsolete_Sapric Terric Tropohemists
2491 obsolete_Sapric Tropofibrists
2492 obsolete_Sapric Tropohemists
2493 obsolete_Sideric
2494 obsolete_Sideric Cryaquods
2495 obsolete_Sideric Tropaquods
2496 No Sodic Aquicambids
2497 No Sodic Calciusterts
2498 No Sodic Calcixerepts
2499 No Sodic Durixererts
2500 No Sodic Endoaquents
2501 No Sodic Endoaquerts
2502 No Sodic Epiaquerts
2503 No Sodic Gypsiusterts
2504 No Sodic Haplocalcids
SSURGO Version: 2.2.3 Page 188
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2505 No Sodic Haplocambids
2506 No Sodic Haplocryerts
2507 No Sodic Haplogypsids
2508 No Sodic Haplotorrerts
2509 No Sodic Haploxererts
2510 No Sodic Haplusterts
2511 No Sodic Humicryerts
2512 No Sodic Hydraquents
2513 No Sodic Petrocambids
2514 No Sodic Psammaquents
2515 No Sodic Salusterts
2516 No Sodic Torriarents
2517 No Sodic Ustic Haplocalcids
2518 No Sodic Ustic Haplocambids
2519 No Sodic Vermaquepts
2520 No Sodic Xerarents
2521 No Sodic Xeric Haplocalcids
2522 No Sodic Xeric Haplocambids
2523 No Sombric Kandiudults
2524 obsolete_Sombrihumic
2525 obsolete_Sphagnic Borofibrists
2526 No Sphagnic Cryofibrists
2527 No Sphagnic Fibristels
2528 obsolete_Sphagnic Medifibrists
2529 obsolete_Sphagnic Terric Borofibrists
2530 obsolete_Sphagnic Terric Medifibrists
2531 No Spodic Cryopsamments
2532 No Spodic Dystrocryepts
2533 No Spodic Dystrudepts
2534 No Spodic Haplocryands
2535 No Spodic Humicryepts
2536 No Spodic Paleudults
SSURGO Version: 2.2.3 Page 189
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2537 No Spodic Psammaquents
2538 No Spodic Psammorthels
2539 No Spodic Psammoturbels
2540 No Spodic Quartzipsamments
2541 No Spodic Udipsamments
2542 No Spodic Vitricryands
2543 obsolete_Spodic Vitrixerands
2544 No Sulfaqueptic Dystraquerts
2545 No Sulfic Cryaquepts
2546 No Sulfic Endoaquents
2547 No Sulfic Endoaquepts
2548 No Sulfic Fluvaquents
2549 obsolete_Sulfic Haplaquepts
2550 No Sulfic Hydraquents
2551 No Sulfic Sulfaquerts
2552 obsolete_Sulfic Tropaquepts
2553 No Sulfuric Aquiturbels
2554 No Sulfuric Aquorthels
2555 obsolete_Terric Borofibrists
2556 obsolete_Terric Borohemists
2557 obsolete_Terric Borosaprists
2558 No Terric Cryofibrists
2559 No Terric Cryohemists
2560 No Terric Cryosaprists
2561 No Terric Fibristels
2562 No Terric Haplofibrists
2563 No Terric Haplohemists
2564 No Terric Haplosaprists
2565 No Terric Hemistels
2566 obsolete_Terric Medifibrists
2567 obsolete_Terric Medihemists
2568 obsolete_Terric Medisaprists
SSURGO Version: 2.2.3 Page 190
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2569 No Terric Sapristels
2570 No Terric Sphagnofibrists
2571 No Terric Sulfihemists
2572 No Terric Sulfisaprists
2573 obsolete_Terric Tropofibrists
2574 obsolete_Terric Tropohemists
2575 obsolete_Terric Troposaprists
2576 No Thaptic Cryaquands
2577 No Thaptic Duraquands
2578 obsolete_Thaptic Durudands
2579 No Thaptic Durustands
2580 No Thaptic Endoaquands
2581 No Thaptic Epiaquands
2582 No Thaptic Fulvudands
2583 No Thaptic Gelaquands
2584 No Thaptic Haplocryands
2585 No Thaptic Haploxerands
2586 No Thaptic Hapludands
2587 No Thaptic Haplustands
2588 No Thaptic Hydrocryands
2589 No Thaptic Hydrudands
2590 No Thaptic Melanaquands
2591 No Thaptic Melanudands
2592 No Thaptic Placaquands
2593 obsolete_Thaptic Placudands
2594 No Thaptic Udivitrands
2595 No Thaptic Ustivitrands
2596 No Thaptic Vitraquands
2597 No Thaptic Vitricryands
2598 No Thaptic Vitrixerands
2599 No Thapto-Histic Cryaquolls
2600 No Thapto-Histic Endoaquolls
SSURGO Version: 2.2.3 Page 191
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2601 No Thapto-Histic Epiaquolls
2602 No Thapto-Histic Fluvaquents
2603 obsolete_Thapto-Histic Haplaquolls
2604 No Thapto-Histic Hydraquents
2605 No Thapto-Histic Sulfaquents
2606 Thapto-Histic Tropic
Fluvaquents
Yes
2607 obsolete_Torrertic Argiborolls
2608 No Torrertic Argiustolls
2609 No Torrertic Argixerolls
2610 No Torrertic Calciustepts
2611 No Torrertic Calciustolls
2612 No Torrertic Dystrustepts
2613 No Torrertic Haploxerolls
2614 No Torrertic Haplustalfs
2615 No Torrertic Haplustepts
2616 No Torrertic Haplustolls
2617 obsolete_Torrertic Natriborolls
2618 No Torrertic Natrustalfs
2619 No Torrertic Natrustolls
2620 No Torrertic Paleustolls
2621 No Torrertic Ustifluvents
2622 obsolete_Torrertic Ustochrepts
2623 No Torrertic Ustorthents
2624 obsolete_Torrifluventic Haploborolls
2625 No Torrifluventic Haploxerolls
2626 No Torrifluventic Haplustepts
2627 No Torrifluventic Haplustolls
2628 obsolete_Torrifluventic Ustochrepts
2629 obsolete_Torriorthentic Haploborolls
2630 No Torriorthentic Haploxerolls
2631 No Torriorthentic Haplustolls
2632 No Torripsammentic Haploxerolls
SSURGO Version: 2.2.3 Page 192
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2633 No Torroxic Haplustolls
2634 obsolete_Tropaquodic
2635 obsolete_Tropeptic
2636 obsolete_Tropeptic Eutrorthox
2637 obsolete_Tropeptic Eutrustox
2638 obsolete_Tropeptic Haplorthox
2639 obsolete_Tropeptic Haplustox
2640 obsolete_Tropeptic Umbriorthox
2641 obsolete_Tropic Fluvaquents
2642 No Typic Acraquox
2643 obsolete_Typic Acrohumox
2644 No Typic Acroperox
2645 obsolete_Typic Acrorthox
2646 No Typic Acrotorrox
2647 No Typic Acrudox
2648 No Typic Acrustox
2649 obsolete_Typic Agrudalfs
2650 No Typic Alaquods
2651 No Typic Albaqualfs
2652 No Typic Albaquults
2653 No Typic Alorthods
2654 obsolete_Typic Andaquepts
2655 No Typic Anhyorthels
2656 No Typic Anhyturbels
2657 No Typic Anthracambids
2658 No Typic Aquicambids
2659 No Typic Aquisalids
2660 No Typic Aquiturbels
2661 No Typic Aquorthels
2662 No Typic Argialbolls
2663 No Typic Argiaquolls
2664 obsolete_Typic Argiborolls
SSURGO Version: 2.2.3 Page 193
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2665 No Typic Argicryids
2666 No Typic Argicryolls
2667 No Typic Argidurids
2668 No Typic Argigypsids
2669 No Typic Argiorthels
2670 No Typic Argiudolls
2671 No Typic Argiustolls
2672 No Typic Argixerolls
2673 obsolete_Typic Borofibrists
2674 obsolete_Typic Borofolists
2675 obsolete_Typic Borohemists
2676 obsolete_Typic Borosaprists
2677 No Typic Calciaquerts
2678 No Typic Calciaquolls
2679 No Typic Calciargids
2680 obsolete_Typic Calciborolls
2681 No Typic Calcicryepts
2682 No Typic Calcicryids
2683 No Typic Calcicryolls
2684 No Typic Calcigypsids
2685 obsolete_Typic Calciorthids
2686 No Typic Calcitorrerts
2687 No Typic Calciudolls
2688 No Typic Calciustepts
2689 No Typic Calciusterts
2690 No Typic Calciustolls
2691 No Typic Calcixerepts
2692 No Typic Calcixererts
2693 No Typic Calcixerolls
2694 obsolete_Typic Camborthids
2695 obsolete_Typic Chromoxererts
2696 obsolete_Typic Chromuderts
SSURGO Version: 2.2.3 Page 194
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2697 obsolete_Typic Chromusterts
2698 obsolete_Typic Cryandepts
2699 No Typic Cryaqualfs
2700 No Typic Cryaquands
2701 No Typic Cryaquents
2702 No Typic Cryaquepts
2703 No Typic Cryaquods
2704 No Typic Cryaquolls
2705 obsolete_Typic Cryoboralfs
2706 obsolete_Typic Cryoborolls
2707 obsolete_Typic Cryochrepts
2708 No Typic Cryofibrists
2709 No Typic Cryofluvents
2710 No Typic Cryofolists
2711 No Typic Cryohemists
2712 obsolete_Typic Cryohumods
2713 No Typic Cryopsamments
2714 No Typic Cryorthents
2715 obsolete_Typic Cryorthods
2716 No Typic Cryosaprists
2717 No Typic Cryrendolls
2718 obsolete_Typic Cryumbrepts
2719 No Typic Duraqualfs
2720 No Typic Duraquands
2721 No Typic Duraquerts
2722 No Typic Duraquods
2723 No Typic Duraquolls
2724 obsolete_Typic Durargids
2725 No Typic Duricryands
2726 No Typic Duricryods
2727 No Typic Duricryolls
2728 No Typic Durihumods
SSURGO Version: 2.2.3 Page 195
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2729 No Typic Duritorrands
2730 No Typic Durixeralfs
2731 No Typic Durixerepts
2732 No Typic Durixererts
2733 No Typic Durixerolls
2734 obsolete_Typic Durochrepts
2735 obsolete_Typic Durorthids
2736 No Typic Durorthods
2737 No Typic Durudands
2738 No Typic Durudepts
2739 No Typic Durustalfs
2740 No Typic Durustands
2741 No Typic Durustepts
2742 No Typic Durustolls
2743 obsolete_Typic Dystrandepts
2744 No Typic Dystraquerts
2745 obsolete_Typic Dystrochrepts
2746 No Typic Dystrocryepts
2747 No Typic Dystrogelepts
2748 obsolete_Typic Dystropepts
2749 No Typic Dystroxerepts
2750 No Typic Dystrudepts
2751 No Typic Dystruderts
2752 No Typic Dystrustepts
2753 No Typic Dystrusterts
2754 No Typic Endoaqualfs
2755 No Typic Endoaquands
2756 No Typic Endoaquents
2757 No Typic Endoaquepts
2758 No Typic Endoaquerts
2759 No Typic Endoaquods
2760 No Typic Endoaquolls
SSURGO Version: 2.2.3 Page 196
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2761 No Typic Endoaquults
2762 No Typic Epiaqualfs
2763 No Typic Epiaquands
2764 No Typic Epiaquents
2765 No Typic Epiaquepts
2766 No Typic Epiaquerts
2767 No Typic Epiaquods
2768 No Typic Epiaquolls
2769 No Typic Epiaquults
2770 obsolete_Typic Eutrandepts
2771 No Typic Eutraquox
2772 obsolete_Typic Eutroboralfs
2773 obsolete_Typic Eutrochrepts
2774 obsolete_Typic Eutrocryepts
2775 No Typic Eutrogelepts
2776 obsolete_Typic Eutropepts
2777 No Typic Eutroperox
2778 obsolete_Typic Eutrorthox
2779 No Typic Eutrotorrox
2780 No Typic Eutrudepts
2781 No Typic Eutrudox
2782 No Typic Eutrustox
2783 No Typic Ferrudalfs
2784 No Typic Fibristels
2785 No Typic Fluvaquents
2786 No Typic Folistels
2787 No Typic Fragiaqualfs
2788 No Typic Fragiaquepts
2789 No Typic Fragiaquods
2790 No Typic Fragiaquults
2791 obsolete_Typic Fragiboralfs
2792 No Typic Fragihumods
SSURGO Version: 2.2.3 Page 197
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2793 obsolete_Typic Fragiochrepts
2794 No Typic Fragiorthods
2795 No Typic Fragiudalfs
2796 No Typic Fragiudepts
2797 No Typic Fragiudults
2798 obsolete_Typic Fragiumbrepts
2799 No Typic Fragixeralfs
2800 No Typic Fragixerepts
2801 No Typic Fraglossudalfs
2802 No Typic Fulvicryands
2803 No Typic Fulvudands
2804 No Typic Gelaquands
2805 No Typic Gelaquents
2806 No Typic Gelaquepts
2807 obsolete_Typic Gelicryands
2808 No Typic Gelifluvents
2809 No Typic Gelorthents
2810 obsolete_Typic Gibbsihumox
2811 obsolete_Typic Gibbsiorthox
2812 No Typic Glacistels
2813 No Typic Glossaqualfs
2814 obsolete_Typic Glossoboralfs
2815 No Typic Glossocryalfs
2816 No Typic Glossudalfs
2817 No Typic Gypsiargids
2818 No Typic Gypsicryids
2819 obsolete_Typic Gypsiorthids
2820 No Typic Gypsitorrerts
2821 No Typic Gypsiusterts
2822 No Typic Halaquepts
2823 No Typic Haplanthrepts
2824 obsolete_Typic Haplaquands
SSURGO Version: 2.2.3 Page 198
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2825 obsolete_Typic Haplaquents
2826 obsolete_Typic Haplaquepts
2827 obsolete_Typic Haplaquods
2828 obsolete_Typic Haplaquolls
2829 No Typic Haplaquox
2830 No Typic Haplargids
2831 obsolete_Typic Haploborolls
2832 No Typic Haplocalcids
2833 No Typic Haplocambids
2834 No Typic Haplocryalfs
2835 No Typic Haplocryands
2836 No Typic Haplocryepts
2837 No Typic Haplocryerts
2838 No Typic Haplocryids
2839 No Typic Haplocryods
2840 No Typic Haplocryolls
2841 No Typic Haplodurids
2842 No Typic Haplofibrists
2843 No Typic Haplogelods
2844 No Typic Haplogelolls
2845 No Typic Haplogypsids
2846 No Typic Haplohemists
2847 No Typic Haplohumods
2848 No Typic Haplohumults
2849 No Typic Haploperox
2850 No Typic Haplorthels
2851 No Typic Haplorthods
2852 obsolete_Typic Haplorthox
2853 No Typic Haplosalids
2854 No Typic Haplosaprists
2855 No Typic Haplotorrands
2856 No Typic Haplotorrerts
SSURGO Version: 2.2.3 Page 199
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2857 No Typic Haplotorrox
2858 No Typic Haploturbels
2859 No Typic Haploxeralfs
2860 No Typic Haploxerands
2861 No Typic Haploxerepts
2862 No Typic Haploxererts
2863 No Typic Haploxerolls
2864 No Typic Haploxerults
2865 No Typic Hapludalfs
2866 No Typic Hapludands
2867 No Typic Hapluderts
2868 No Typic Hapludolls
2869 No Typic Hapludox
2870 No Typic Hapludults
2871 obsolete_Typic Haplumbrepts
2872 No Typic Haplustalfs
2873 No Typic Haplustands
2874 No Typic Haplustepts
2875 No Typic Haplusterts
2876 No Typic Haplustolls
2877 No Typic Haplustox
2878 No Typic Haplustults
2879 No Typic Haprendolls
2880 No Typic Hemistels
2881 No Typic Historthels
2882 No Typic Histoturbels
2883 No Typic Humaquepts
2884 No Typic Humicryepts
2885 No Typic Humicryerts
2886 No Typic Humicryods
2887 No Typic Humigelods
2888 obsolete_Typic Humitropepts
SSURGO Version: 2.2.3 Page 200
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2889 obsolete_Typic Hydrandepts
2890 No Typic Hydraquents
2891 No Typic Hydrocryands
2892 No Typic Hydrudands
2893 No Typic Kandiaqualfs
2894 No Typic Kandiaquults
2895 No Typic Kandihumults
2896 No Typic Kandiperox
2897 No Typic Kandiudalfs
2898 No Typic Kandiudox
2899 No Typic Kandiudults
2900 No Typic Kandiustalfs
2901 No Typic Kandiustox
2902 No Typic Kandiustults
2903 No Typic Kanhaplaquults
2904 No Typic Kanhaplohumults
2905 No Typic Kanhapludalfs
2906 No Typic Kanhapludults
2907 No Typic Kanhaplustalfs
2908 No Typic Kanhaplustults
2909 obsolete_Typic Luvifibrists
2910 No Typic Luvihemists
2911 obsolete_Typic Medifibrists
2912 obsolete_Typic Medifolists
2913 obsolete_Typic Medihemists
2914 obsolete_Typic Medisaprists
2915 No Typic Melanaquands
2916 No Typic Melanocryands
2917 No Typic Melanoxerands
2918 No Typic Melanudands
2919 No Typic Molliturbels
2920 No Typic Mollorthels
SSURGO Version: 2.2.3 Page 201
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2921 obsolete_Typic Nadurargids
2922 No Typic Natralbolls
2923 No Typic Natraqualfs
2924 No Typic Natraquerts
2925 No Typic Natraquolls
2926 No Typic Natrargids
2927 obsolete_Typic Natriboralfs
2928 obsolete_Typic Natriborolls
2929 No Typic Natricryolls
2930 No Typic Natridurids
2931 No Typic Natrigypsids
2932 No Typic Natrixeralfs
2933 No Typic Natrixerolls
2934 No Typic Natrudalfs
2935 No Typic Natrudolls
2936 No Typic Natrustalfs
2937 No Typic Natrustolls
2938 obsolete_Typic Ochraqualfs
2939 obsolete_Typic Ochraquults
2940 No Typic Paleaquults
2941 No Typic Paleargids
2942 obsolete_Typic Paleboralfs
2943 obsolete_Typic Paleborolls
2944 No Typic Palecryalfs
2945 No Typic Palecryolls
2946 No Typic Palehumults
2947 obsolete_Typic Paleorthids
2948 No Typic Paleudalfs
2949 No Typic Paleudolls
2950 No Typic Paleudults
2951 No Typic Paleustalfs
2952 No Typic Paleustolls
SSURGO Version: 2.2.3 Page 202
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2953 No Typic Paleustults
2954 No Typic Palexeralfs
2955 No Typic Palexerolls
2956 No Typic Palexerults
2957 obsolete_Typic Pelloxererts
2958 obsolete_Typic Pelluderts
2959 obsolete_Typic Pellusterts
2960 No Typic Petraquepts
2961 No Typic Petroargids
2962 No Typic Petrocalcids
2963 No Typic Petrocambids
2964 No Typic Petrocryids
2965 No Typic Petrogypsids
2966 obsolete_Typic Placandepts
2967 No Typic Placaquands
2968 obsolete_Typic Placaquepts
2969 No Typic Placaquods
2970 No Typic Placocryods
2971 No Typic Placohumods
2972 No Typic Placorthods
2973 No Typic Placudands
2974 No Typic Plagganthrepts
2975 obsolete_Typic Plaggepts
2976 No Typic Plinthaqualfs
2977 obsolete_Typic Plinthaquepts
2978 No Typic Plinthaquox
2979 No Typic Plinthaquults
2980 No Typic Plinthohumults
2981 No Typic Plinthoxeralfs
2982 No Typic Plinthudults
2983 No Typic Plinthustalfs
2984 No Typic Plinthustults
SSURGO Version: 2.2.3 Page 203
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
2985 No Typic Psammaquents
2986 No Typic Psammorthels
2987 No Typic Psammoturbels
2988 No Typic Quartzipsamments
2989 obsolete_Typic Rendolls
2990 No Typic Rhodoxeralfs
2991 No Typic Rhodudalfs
2992 No Typic Rhodudults
2993 No Typic Rhodustalfs
2994 No Typic Rhodustults
2995 No Typic Salaquerts
2996 No Typic Salicryids
2997 No Typic Salitorrerts
2998 obsolete_Typic Salorthids
2999 No Typic Salusterts
3000 No Typic Sapristels
3001 obsolete_Typic Sideraquods
3002 obsolete_Typic Sombrihumox
3003 No Typic Sombrihumults
3004 No Typic Sombriperox
3005 obsolete_Typic Sombritropepts
3006 No Typic Sombriudox
3007 No Typic Sombriustox
3008 No Typic Sphagnofibrists
3009 No Typic Sulfaquents
3010 No Typic Sulfaquepts
3011 No Typic Sulfaquerts
3012 No Typic Sulfihemists
3013 No Typic Sulfisaprists
3014 obsolete_Typic Sulfochrepts
3015 No Typic Sulfohemists
3016 No Typic Sulfosaprists
SSURGO Version: 2.2.3 Page 204
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3017 No Typic Sulfudepts
3018 obsolete_Typic Torrerts
3019 No Typic Torrifluvents
3020 No Typic Torrifolists
3021 No Typic Torriorthents
3022 No Typic Torripsamments
3023 obsolete_Typic Torrox
3024 obsolete_Typic Tropaqualfs
3025 obsolete_Typic Tropaquents
3026 obsolete_Typic Tropaquepts
3027 obsolete_Typic Tropofibrists
3028 obsolete_Typic Tropofluvents
3029 obsolete_Typic Tropofolists
3030 obsolete_Typic Tropohemists
3031 obsolete_Typic Tropohumods
3032 obsolete_Typic Tropohumults
3033 obsolete_Typic Tropopsamments
3034 obsolete_Typic Troporthents
3035 obsolete_Typic Troposaprists
3036 obsolete_Typic Tropudalfs
3037 obsolete_Typic Tropudults
3038 No Typic Udifluvents
3039 No Typic Udifolists
3040 No Typic Udipsamments
3041 No Typic Udivitrands
3042 No Typic Udorthents
3043 obsolete_Typic Umbraqualfs
3044 No Typic Umbraquults
3045 No Typic Umbriturbels
3046 No Typic Umbrorthels
3047 No Typic Ustifluvents
3048 No Typic Ustifolists
SSURGO Version: 2.2.3 Page 205
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3049 No Typic Ustipsamments
3050 No Typic Ustivitrands
3051 obsolete_Typic Ustochrepts
3052 No Typic Ustorthents
3053 obsolete_Typic Ustropepts
3054 No Typic Vermaqualfs
3055 No Typic Vermaquepts
3056 obsolete_Typic Vermiborolls
3057 No Typic Vermudolls
3058 No Typic Vermustolls
3059 obsolete_Typic Vitrandepts
3060 No Typic Vitraquands
3061 No Typic Vitricryands
3062 No Typic Vitrigelands
3063 No Typic Vitritorrands
3064 No Typic Vitrixerands
3065 obsolete_Typic Xerochrepts
3066 No Typic Xerofluvents
3067 No Typic Xeropsamments
3068 No Typic Xerorthents
3069 obsolete_Typic Xerumbrepts
3070 obsolete_Udalfic
3071 obsolete_Udalfic Arents
3072 obsolete_Udalphic Argiustolls
3073 No Udandic Kandiustults
3074 No Udandic Kanhaplustults
3075 obsolete_Udarents
3076 obsolete_Udertic Argiborolls
3077 No Udertic Argiustolls
3078 No Udertic Calciustolls
3079 obsolete_Udertic Haploborolls
3080 No Udertic Haplustalfs
SSURGO Version: 2.2.3 Page 206
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3081 No Udertic Haplustepts
3082 No Udertic Haplustolls
3083 obsolete_Udertic Natriborolls
3084 No Udertic Paleustalfs
3085 No Udertic Paleustolls
3086 obsolete_Udertic Ustochrepts
3087 obsolete_Udic Argiborolls
3088 No Udic Argiustolls
3089 obsolete_Udic Calciborolls
3090 No Udic Calciustepts
3091 No Udic Calciusterts
3092 No Udic Calciustolls
3093 obsolete_Udic Chromusterts
3094 No Udic Durixererts
3095 No Udic Dystrusterts
3096 obsolete_Udic Eutrandepts
3097 No Udic Gypsiusterts
3098 obsolete_Udic Haploborolls
3099 No Udic Haploxererts
3100 No Udic Haplustalfs
3101 No Udic Haplustepts
3102 No Udic Haplusterts
3103 No Udic Haplustolls
3104 No Udic Kandiustalfs
3105 No Udic Kandiustults
3106 No Udic Kanhaplustalfs
3107 No Udic Kanhaplustults
3108 obsolete_Udic Natriborolls
3109 No Udic Paleustalfs
3110 No Udic Paleustolls
3111 obsolete_Udic Pellusterts
3112 No Udic Rhodustalfs
SSURGO Version: 2.2.3 Page 207
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3113 No Udic Ustifluvents
3114 obsolete_Udic Ustochrepts
3115 No Udic Ustorthents
3116 obsolete_Udic Vermiborolls
3117 No Udifluventic Haplustepts
3118 obsolete_Udifluventic Ustochrepts
3119 No Udollic Albaqualfs
3120 No Udollic Endoaqualfs
3121 No Udollic Epiaqualfs
3122 obsolete_Udollic Ochraqualfs
3123 obsolete_Udorthentic Chromusterts
3124 obsolete_Udorthentic Haploborolls
3125 No Udorthentic Haplustolls
3126 obsolete_Udorthentic Pellusterts
3127 No Udoxic Quartzipsamments
3128 No Ultic Alaquods
3129 No Ultic Alorthods
3130 No Ultic Argixerolls
3131 No Ultic Epiaquods
3132 No Ultic Fragiorthods
3133 No Ultic Fulvudands
3134 obsolete_Ultic Haplaquods
3135 obsolete_Ultic Haplohumods
3136 No Ultic Haplorthods
3137 No Ultic Haploxeralfs
3138 No Ultic Haploxerands
3139 No Ultic Haploxerolls
3140 No Ultic Hapludalfs
3141 No Ultic Hapludands
3142 No Ultic Haplustalfs
3143 No Ultic Haplustands
3144 obsolete_Ultic Haplustox
SSURGO Version: 2.2.3 Page 208
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3145 No Ultic Hydrudands
3146 No Ultic Melanudands
3147 No Ultic Paleustalfs
3148 No Ultic Palexeralfs
3149 No Ultic Palexerolls
3150 obsolete_Ultic Tropudalfs
3151 No Ultic Udarents
3152 No Ultic Udivitrands
3153 obsolete_Ultic Vitric
3154 obsolete_Ultic Vitric Haploxerands
3155 No Ultic Vitricryands
3156 No Ultic Vitrixerands
3157 obsolete_Umbreptic Eutroperox
3158 obsolete_Umbreptic Eutrudox
3159 obsolete_Umbreptic Eutrustox
3160 obsolete_Umbreptic Fragiudalfs
3161 No Umbric Albaqualfs
3162 obsolete_Umbric Dystrochrepts
3163 obsolete_Umbric Dystropepts
3164 No Umbric Endoaqualfs
3165 No Umbric Endoaquods
3166 No Umbric Epiaqualfs
3167 No Umbric Epiaquods
3168 obsolete_Umbric Fragiaqualfs
3169 No Umbric Fragiaquults
3170 obsolete_Umbric Fragiochrepts
3171 No Umbric Glossocryalfs
3172 No Umbric Haplocryalfs
3173 obsolete_Umbric Haploxerands
3174 obsolete_Umbric Haplustands
3175 No Umbric Kandiaqualfs
3176 No Umbric Kandiaquults
SSURGO Version: 2.2.3 Page 209
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3177 No Umbric Kanhaplaquults
3178 obsolete_Umbric Ochraqualfs
3179 No Umbric Paleaquults
3180 No Umbric Palecryalfs
3181 obsolete_Umbric Vitrandepts
3182 obsolete_Umbric Vitrixerands
3183 No Umbric Xeric Glossocryalfs
3184 No Umbric Xeric Haplocryalfs
3185 obsolete_Ustalfic Argiustolls
3186 obsolete_Ustalfic Durargids
3187 obsolete_Ustalfic Haplargids
3188 obsolete_Ustalfic Paleargids
3189 No Ustalfic Petrocalcids
3190 obsolete_Ustandic Humitropepts
3191 No Ustandic Kandihumults
3192 No Ustandic Kanhaplohumults
3193 obsolete_Ustertic Argiborolls
3194 No Ustertic Calciargids
3195 obsolete_Ustertic Camborthids
3196 No Ustertic Haplargids
3197 No Ustertic Haplocambids
3198 No Ustertic Natrargids
3199 No Ustertic Torrifluvents
3200 No Ustertic Torriorthents
3201 No Ustic Aquicambids
3202 No Ustic Argicryids
3203 No Ustic Argicryolls
3204 No Ustic Argidurids
3205 No Ustic Argigypsids
3206 No Ustic Calciargids
3207 No Ustic Calcicryepts
3208 No Ustic Calcicryids
SSURGO Version: 2.2.3 Page 210
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3209 No Ustic Calcicryolls
3210 No Ustic Calcigypsids
3211 obsolete_Ustic Calciorthids
3212 No Ustic Duraquerts
3213 obsolete_Ustic Durochrepts
3214 No Ustic Dystraquerts
3215 No Ustic Dystrocryepts
3216 obsolete_Ustic Dystropepts
3217 No Ustic Endoaquerts
3218 No Ustic Epiaquerts
3219 obsolete_Ustic Eutrocryepts
3220 No Ustic Glossocryalfs
3221 No Ustic Gypsiargids
3222 No Ustic Haplargids
3223 No Ustic Haplocalcids
3224 No Ustic Haplocambids
3225 No Ustic Haplocryalfs
3226 No Ustic Haplocryepts
3227 No Ustic Haplocryids
3228 No Ustic Haplocryolls
3229 No Ustic Haplodurids
3230 No Ustic Haplogypsids
3231 No Ustic Haplohumults
3232 obsolete_Ustic Humitropepts
3233 No Ustic Kandihumults
3234 No Ustic Kanhaplohumults
3235 No Ustic Natrargids
3236 No Ustic Natrigypsids
3237 No Ustic Paleargids
3238 No Ustic Palecryalfs
3239 No Ustic Palecryolls
3240 No Ustic Palehumults
SSURGO Version: 2.2.3 Page 211
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3241 No Ustic Petroargids
3242 No Ustic Petrocalcids
3243 No Ustic Petrocambids
3244 No Ustic Petrocryids
3245 No Ustic Petrogypsids
3246 No Ustic Quartzipsamments
3247 No Ustic Salaquerts
3248 No Ustic Torrifluvents
3249 No Ustic Torriorthents
3250 No Ustic Torripsamments
3251 obsolete_Ustic Tropohumults
3252 No Ustifluventic Haplocambids
3253 obsolete_Ustivitrandic Camborthids
3254 obsolete_Ustivitrandic Durargids
3255 obsolete_Ustivitrandic Durorthids
3256 No Ustivitrandic Haplocryepts
3257 obsolete_Ustochreptic Calciorthids
3258 obsolete_Ustochreptic Camborthids
3259 obsolete_Ustochreptic Durorthids
3260 obsolete_Ustochreptic Paleorthids
3261 obsolete_Ustollic Calciorthids
3262 obsolete_Ustollic Camborthids
3263 obsolete_Ustollic Durorthids
3264 obsolete_Ustollic Eutrandepts
3265 No Ustollic Glossocryalfs
3266 obsolete_Ustollic Haplargids
3267 No Ustollic Haplocryalfs
3268 obsolete_Ustollic Natrargids
3269 obsolete_Ustollic Paleargids
3270 obsolete_Ustollic Paleorthids
3271 obsolete_Ustoxic Dystropepts
3272 obsolete_Ustoxic Humitropepts
SSURGO Version: 2.2.3 Page 212
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3273 No Ustoxic Quartzipsamments
3274 obsolete_Ustoxic Tropohumults
3275 No Vermic Calcixerolls
3276 No Vermic Fragiaqualfs
3277 No Vermic Haploxerolls
3278 No Vermic Hapludolls
3279 No Vermic Natraqualfs
3280 No Vermic Udorthents
3281 No Vermic Ustorthents
3282 No Vertic Albaqualfs
3283 No Vertic Albaquults
3284 No Vertic Argialbolls
3285 No Vertic Argiaquolls
3286 obsolete_Vertic Argiborolls
3287 No Vertic Argicryids
3288 No Vertic Argicryolls
3289 No Vertic Argidurids
3290 No Vertic Argigypsids
3291 No Vertic Argiudolls
3292 No Vertic Argiustolls
3293 No Vertic Argixerolls
3294 No Vertic Calciargids
3295 No Vertic Calciudolls
3296 No Vertic Calciustepts
3297 No Vertic Calciustolls
3298 No Vertic Calcixerepts
3299 No Vertic Calcixerolls
3300 obsolete_Vertic Camborthids
3301 No Vertic Cryaquepts
3302 No Vertic Cryaquolls
3303 obsolete_Vertic Cryoboralfs
3304 obsolete_Vertic Cryoborolls
SSURGO Version: 2.2.3 Page 213
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3305 No Vertic Duraquolls
3306 obsolete_Vertic Durargids
3307 No Vertic Durixeralfs
3308 No Vertic Durixerolls
3309 obsolete_Vertic Dystropepts
3310 No Vertic Dystrudepts
3311 No Vertic Dystrustepts
3312 No Vertic Endoaqualfs
3313 No Vertic Endoaquepts
3314 No Vertic Endoaquolls
3315 No Vertic Epiaqualfs
3316 No Vertic Epiaquepts
3317 No Vertic Epiaquolls
3318 No Vertic Epiaquults
3319 obsolete_Vertic Eutroboralfs
3320 obsolete_Vertic Eutrochrepts
3321 obsolete_Vertic Eutropepts
3322 No Vertic Eutrudepts
3323 No Vertic Fluvaquents
3324 No Vertic Glossocryalfs
3325 No Vertic Glossudalfs
3326 No Vertic Halaquepts
3327 obsolete_Vertic Haplaquepts
3328 obsolete_Vertic Haplaquolls
3329 No Vertic Haplargids
3330 obsolete_Vertic Haploborolls
3331 No Vertic Haplocalcids
3332 No Vertic Haplocambids
3333 No Vertic Haplocryalfs
3334 No Vertic Haplocryids
3335 No Vertic Haplocryolls
3336 No Vertic Haploxeralfs
SSURGO Version: 2.2.3 Page 214
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3337 No Vertic Haploxerepts
3338 No Vertic Haploxerolls
3339 No Vertic Hapludalfs
3340 No Vertic Hapludolls
3341 No Vertic Hapludults
3342 No Vertic Haplustalfs
3343 No Vertic Haplustepts
3344 No Vertic Haplustolls
3345 No Vertic Haprendolls
3346 obsolete_Vertic Humitropepts
3347 No Vertic Molliturbels
3348 No Vertic Mollorthels
3349 obsolete_Vertic Nadurargids
3350 No Vertic Natraqualfs
3351 No Vertic Natraquolls
3352 No Vertic Natrargids
3353 obsolete_Vertic Natriborolls
3354 No Vertic Natridurids
3355 No Vertic Natrigypsids
3356 No Vertic Natrixeralfs
3357 No Vertic Natrixerolls
3358 No Vertic Natrudalfs
3359 No Vertic Natrudolls
3360 No Vertic Natrustalfs
3361 No Vertic Natrustolls
3362 obsolete_Vertic Ochraqualfs
3363 No Vertic Paleaquults
3364 No Vertic Paleargids
3365 obsolete_Vertic Paleborolls
3366 No Vertic Paleudalfs
3367 No Vertic Paleudolls
3368 No Vertic Paleudults
SSURGO Version: 2.2.3 Page 215
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3369 No Vertic Paleustalfs
3370 No Vertic Paleustolls
3371 No Vertic Palexeralfs
3372 No Vertic Palexerolls
3373 obsolete_Vertic Rendolls
3374 No Vertic Rhodoxeralfs
3375 No Vertic Torrifluvents
3376 No Vertic Torriorthents
3377 obsolete_Vertic Tropaquepts
3378 obsolete_Vertic Tropudalfs
3379 No Vertic Udifluvents
3380 No Vertic Umbriturbels
3381 No Vertic Umbrorthels
3382 No Vertic Ustifluvents
3383 obsolete_Vertic Ustochrepts
3384 No Vertic Ustorthents
3385 obsolete_Vertic Ustropepts
3386 obsolete_Vertic Xerochrepts
3387 No Vertic Xerofluvents
3388 No Vitrandic Aquicambids
3389 No Vitrandic Aquorthels
3390 obsolete_Vitrandic Argiborolls
3391 No Vitrandic Argicryids
3392 No Vitrandic Argicryolls
3393 No Vitrandic Argidurids
3394 No Vitrandic Argigypsids
3395 No Vitrandic Argiudolls
3396 No Vitrandic Argiustolls
3397 No Vitrandic Argixerolls
3398 No Vitrandic Calciargids
3399 No Vitrandic Calcicryids
3400 No Vitrandic Calcicryolls
SSURGO Version: 2.2.3 Page 216
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3401 No Vitrandic Calcigypsids
3402 No Vitrandic Calcixerepts
3403 No Vitrandic Calcixerolls
3404 obsolete_Vitrandic Cryoboralfs
3405 obsolete_Vitrandic Cryoborolls
3406 obsolete_Vitrandic Cryochrepts
3407 No Vitrandic Cryofluvents
3408 No Vitrandic Cryopsamments
3409 No Vitrandic Cryorthents
3410 obsolete_Vitrandic Cryumbrepts
3411 No Vitrandic Durixerepts
3412 No Vitrandic Durixerolls
3413 obsolete_Vitrandic Durochrepts
3414 No Vitrandic Durudepts
3415 obsolete_Vitrandic Dystrochrepts
3416 No Vitrandic Dystrocryepts
3417 obsolete_Vitrandic Dystropepts
3418 No Vitrandic Dystroxerepts
3419 No Vitrandic Dystrudepts
3420 No Vitrandic Dystrustepts
3421 obsolete_Vitrandic Eutroboralfs
3422 obsolete_Vitrandic Eutrochrepts
3423 obsolete_Vitrandic Eutrocryepts
3424 obsolete_Vitrandic Eutropepts
3425 No Vitrandic Eutrudepts
3426 obsolete_Vitrandic Fragiboralfs
3427 obsolete_Vitrandic Fragiochrepts
3428 No Vitrandic Fragiudalfs
3429 No Vitrandic Fragiudepts
3430 obsolete_Vitrandic Fragiumbrepts
3431 No Vitrandic Fragixeralfs
3432 No Vitrandic Fragixerepts
SSURGO Version: 2.2.3 Page 217
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3433 No Vitrandic Fraglossudalfs
3434 obsolete_Vitrandic Glossoboralfs
3435 No Vitrandic Glossocryalfs
3436 No Vitrandic Glossudalfs
3437 No Vitrandic Gypsiargids
3438 No Vitrandic Gypsicryids
3439 No Vitrandic Haplargids
3440 obsolete_Vitrandic Haploborolls
3441 No Vitrandic Haplocalcids
3442 No Vitrandic Haplocambids
3443 No Vitrandic Haplocryalfs
3444 No Vitrandic Haplocryepts
3445 No Vitrandic Haplocryids
3446 No Vitrandic Haplocryolls
3447 No Vitrandic Haplodurids
3448 No Vitrandic Haplogypsids
3449 No Vitrandic Haploxeralfs
3450 No Vitrandic Haploxerepts
3451 No Vitrandic Haploxerolls
3452 No Vitrandic Hapludalfs
3453 No Vitrandic Hapludolls
3454 obsolete_Vitrandic Haplumbrepts
3455 No Vitrandic Haplustalfs
3456 No Vitrandic Haplustepts
3457 No Vitrandic Haplustolls
3458 No Vitrandic Humicryepts
3459 obsolete_Vitrandic Humitropepts
3460 No Vitrandic Molliturbels
3461 No Vitrandic Mollorthels
3462 No Vitrandic Natrargids
3463 No Vitrandic Natridurids
3464 No Vitrandic Natrigypsids
SSURGO Version: 2.2.3 Page 218
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3465 No Vitrandic Paleargids
3466 obsolete_Vitrandic Paleboralfs
3467 No Vitrandic Palecryalfs
3468 No Vitrandic Paleudalfs
3469 No Vitrandic Palexeralfs
3470 No Vitrandic Palexerolls
3471 obsolete_Vitrandic Petrocalcids
3472 No Vitrandic Petrocambids
3473 No Vitrandic Petrogypsids
3474 No Vitrandic Torrifluvents
3475 No Vitrandic Torriorthents
3476 No Vitrandic Torripsamments
3477 obsolete_Vitrandic Troporthents
3478 No Vitrandic Udifluvents
3479 No Vitrandic Udorthents
3480 No Vitrandic Umbriturbels
3481 No Vitrandic Umbrorthels
3482 obsolete_Vitrandic Ustochrepts
3483 No Vitrandic Ustorthents
3484 obsolete_Vitrandic Xerochrepts
3485 No Vitrandic Xerofluvents
3486 No Vitrandic Xeropsamments
3487 No Vitrandic Xerorthents
3488 obsolete_Vitrandic Xerumbrepts
3489 No Vitric Duritorrands
3490 No Vitric Fulvicryands
3491 No Vitric Haplocryands
3492 obsolete_Vitric Haploxerands
3493 No Vitric Hapludands
3494 No Vitric Haplustands
3495 No Vitric Melanocryands
3496 No Vitric Melanudands
SSURGO Version: 2.2.3 Page 219
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3497 obsolete_Vitric Placudands
3498 No Vitritorrandic Argiustolls
3499 No Vitritorrandic Argixerolls
3500 No Vitritorrandic Durixerolls
3501 No Vitritorrandic Haploxerolls
3502 No Vitritorrandic Haplustolls
3503 No Vitritorrandic Ustorthents
3504 No Vitrixerandic Aquicambids
3505 No Vitrixerandic Argicryids
3506 No Vitrixerandic Argidurids
3507 No Vitrixerandic Argigypsids
3508 No Vitrixerandic Calciargids
3509 No Vitrixerandic Calcicryids
3510 No Vitrixerandic Calcigypsids
3511 obsolete_Vitrixerandic Camborthids
3512 obsolete_Vitrixerandic Durargids
3513 obsolete_Vitrixerandic Durorthids
3514 No Vitrixerandic Dystrocryepts
3515 No Vitrixerandic Gypsiargids
3516 No Vitrixerandic Gypsicryids
3517 No Vitrixerandic Haplargids
3518 No Vitrixerandic Haplocalcids
3519 No Vitrixerandic Haplocambids
3520 No Vitrixerandic Haplocryepts
3521 No Vitrixerandic Haplocryids
3522 No Vitrixerandic Haplodurids
3523 No Vitrixerandic Haplogypsids
3524 No Vitrixerandic Humicryepts
3525 No Vitrixerandic Natrargids
3526 No Vitrixerandic Natridurids
3527 No Vitrixerandic Natrigypsids
3528 No Vitrixerandic Paleargids
SSURGO Version: 2.2.3 Page 220
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3529 obsolete_Vitrixerandic Petrocalcids
3530 No Vitrixerandic Petrocambids
3531 No Vitrixerandic Petrogypsids
3532 No Vitrixerandic Torrifluvents
3533 obsolete_Vitrustandic
3534 No Xanthic Acroperox
3535 No Xanthic Acrudox
3536 No Xanthic Acrustox
3537 No Xanthic Eutroperox
3538 No Xanthic Eutrudox
3539 No Xanthic Eutrustox
3540 No Xanthic Haploperox
3541 No Xanthic Hapludox
3542 No Xanthic Haplustox
3543 No Xanthic Kandiperox
3544 No Xanthic Kandiudox
3545 No Xanthic Kandiustox
3546 obsolete_Xeralfic Haplargids
3547 obsolete_Xeralfic Paleargids
3548 obsolete_Xeralfic Paleorthids
3549 No Xeralfic Petrocalcids
3550 obsolete_Xerarents
3551 No Xereptic Haplodurids
3552 No Xereptic Petrocryids
3553 No Xerertic Argialbolls
3554 No Xerertic Calciargids
3555 obsolete_Xerertic Camborthids
3556 No Xerertic Haplargids
3557 No Xerertic Haplocambids
3558 No Xerertic Natrargids
3559 No Xerertic Torriorthents
3560 No Xeric Aquicambids
SSURGO Version: 2.2.3 Page 221
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3561 No Xeric Argialbolls
3562 No Xeric Argicryids
3563 No Xeric Argicryolls
3564 No Xeric Argidurids
3565 No Xeric Argigypsids
3566 No Xeric Calciargids
3567 No Xeric Calcicryepts
3568 No Xeric Calcicryids
3569 No Xeric Calcicryolls
3570 No Xeric Calcigypsids
3571 obsolete_Xeric Durandepts
3572 No Xeric Duraquerts
3573 No Xeric Dystrocryepts
3574 No Xeric Endoaquerts
3575 No Xeric Epiaquerts
3576 obsolete_Xeric Eutrocryepts
3577 No Xeric Glossocryalfs
3578 No Xeric Gypsiargids
3579 No Xeric Haplargids
3580 No Xeric Haplocalcids
3581 No Xeric Haplocambids
3582 No Xeric Haplocryalfs
3583 No Xeric Haplocryands
3584 No Xeric Haplocryepts
3585 No Xeric Haplocryids
3586 No Xeric Haplocryolls
3587 No Xeric Haplodurids
3588 No Xeric Haplogypsids
3589 No Xeric Haplohumults
3590 No Xeric Humicryepts
3591 No Xeric Kandihumults
3592 No Xeric Kanhaplohumults
SSURGO Version: 2.2.3 Page 222
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3593 No Xeric Natrargids
3594 No Xeric Natridurids
3595 No Xeric Natrigypsids
3596 No Xeric Paleargids
3597 No Xeric Palecryalfs
3598 No Xeric Palecryolls
3599 No Xeric Palehumults
3600 No Xeric Petroargids
3601 No Xeric Petrocalcids
3602 No Xeric Petrocambids
3603 No Xeric Petrocryids
3604 No Xeric Petrogypsids
3605 No Xeric Quartzipsamments
3606 No Xeric Torrifluvents
3607 No Xeric Torriorthents
3608 No Xeric Torripsamments
3609 No Xeric Vitricryands
3610 obsolete_Xerochreptic Calciorthids
3611 obsolete_Xerochreptic Camborthids
3612 obsolete_Xerochreptic Durorthids
3613 obsolete_Xerochreptic Haplodurids
3614 obsolete_Xerochreptic Paleorthids
3615 No Xerofluventic Haplocambids
3616 obsolete_Xerollic Calciorthids
3617 obsolete_Xerollic Camborthids
3618 obsolete_Xerollic Durargids
3619 obsolete_Xerollic Durorthids
3620 No Xerollic Glossocryalfs
3621 obsolete_Xerollic Haplargids
3622 No Xerollic Haplocryalfs
3623 obsolete_Xerollic Nadurargids
3624 obsolete_Xerollic Natrargids
SSURGO Version: 2.2.3 Page 223
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_subgroup
; /* = 
Length of Longest Choice Value: 39
3625 obsolete_Xerollic Paleargids
3626 obsolete_Xerollic Paleorthids
*/

//_____________________________________________________________________________
typedef std::string  taxonomic_suborder
; /* = 
Length of Longest Choice Value: 9
1 No Albolls
2 obsolete_Andepts
3 No Anthrepts
4 No Aqualfs
5 No Aquands
6 No Aquents
7 No Aquepts
8 No Aquerts
9 No Aquods
10 No Aquolls
11 No Aquox
12 No Aquults
13 No Arents
14 No Argids
15 obsolete_Boralfs
16 obsolete_Borolls
17 No Calcids
18 No Cambids
19 No Cryalfs
20 No Cryands
21 No Cryepts
22 No Cryerts
23 No Cryids
24 No Cryods
25 No Cryolls
26 No Durids
SSURGO Version: 2.2.3 Page 224
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_suborder
; /* = 
Length of Longest Choice Value: 9
27 obsolete_Ferrods
28 No Fibrists
29 No Fluvents
30 No Folists
31 No Gelands
32 No Gelepts
33 No Gelods
34 No Gelolls
35 No Gypsids
36 No Hemists
37 No Histels
38 No Humods
39 obsolete_Humox
40 No Humults
41 obsolete_Ochrepts
42 No Orthels
43 No Orthents
44 obsolete_Orthids
45 No Orthods
46 obsolete_Orthox
47 No Perox
48 obsolete_Plaggepts
49 No Psamments
50 No Rendolls
51 No Salids
52 No Saprists
53 No Torrands
54 No Torrerts
55 No Torrox
56 obsolete_Tropepts
57 No Turbels
58 No Udalfs
SSURGO Version: 2.2.3 Page 225
*/ //_____________________________________________________________________________

typedef std::string  taxonomic_suborder
; /* = 
Length of Longest Choice Value: 9
59 No Udands
60 No Udepts
61 No Uderts
62 No Udolls
63 No Udox
64 No Udults
65 obsolete_Umbrepts
66 No Ustalfs
67 No Ustands
68 No Ustepts
69 No Usterts
70 No Ustolls
71 No Ustox
72 No Ustults
73 No Vitrands
74 No Xeralfs
75 No Xerands
76 No Xerepts
77 No Xererts
78 No Xerolls
79 No Xerults
*/
//_____________________________________________________________________________
typedef std::string  taxonomic_temp_regime
; /* = 
Length of Longest Choice Value: 19
1 No cryic
2 obsolete_Cryic (PDP code)
3 No frigid
4 No hyperthermic
5 No isofrigid
6 No isohyperthermic
7 No isomesic
8 No isothermic
9 No mesic
10 obsolete_pergelic
11 obsolete_Pergelic (PDP code)
12 No thermic
*/
typedef std::string  terms_used_in_lieu_of_texture
; /* =
Length of Longest Choice Value: 36
1 obsolete_Ashy-pumiceous Ashy-pumiceous
2 No Artifacts Dominated by human artifacts with too little fine-earth to determine the textural class (less than about 10 percent fine-earth, by volume)
3 obsolete_Ashy Ashy
4 obsolete_Ashy-skeletal Ashy-skeletal
5 No Bedrock Bedrock
6 No Boulders Boulders
7 No Cobbles Cobbles
8 obsolete_Coprogenous earth Coprogenous earth
9 obsolete_Cemented Cemented
10 obsolete_Cinders Cindery
11 No Channers Channers
12 obsolete_Cindery Cindery
13 Consolidated permafrost (ice rich) obsolete_Consolidated permafrost (ice rich)
14 obsolete_Diatomaceous earth Diatomaceous earth
15 obsolete_Duripan Duripan
16 No Flagstones Flagstones
17 obsolete_Fragmental material Fragmental material
18 No Gravel Gravel
19 obsolete_Gypsiferous material Gypsiferous material
20 Highly decomposed plant material No Highly decomposed plant material that is saturated with water for less than 30 cumulative days in normal years (and is not artificially drained).
21 obsolete_Hydrous-pumiceous Hydrous-pumiceous
22 obsolete_Hydrous-skeletal Hydrous-skeletal
23 obsolete_Hydrous Hydrous
24 obsolete_Indurated Indurated
25 obsolete_Marl Marl
26 No Material Material
27 obsolete_Medial Medial
28 Moderately decomposed plant material Moderately decomposed plant material that is saturated with water for less than 30 cumulative days in normal years (and is not artificially drained).
29 No Mucky peat Moderately decomposed organic material of any thickness that is saturated with water for 30 or more cumulative days in normal years (or is artificially drained), including that in Histels and Histosols, except for Folists.
30 obsolete_Medial-pumiceous Medial-pumiceous
31 obsolete_Medial-skeletal Medial-skeletal 32 No Muck Highly decomposed organic material of any thickness that is saturated with water for 30 or more cumulative days in normal years (or is artificially drained), including that in Histels and Histosols, except for Folists.
33 Oxide protected weathered bedrock obsolete_Oxide protected weathered bedrock
34 obsolete_Ortstein Ortstein
35 No Paraboulders Paraboulders
36 obsolete_Petrocalcic Petrocalcic
37 No Paracobbles Paracobbles
38 No Parachanners Parachanners
39 Partially decomposed organic matter obsolete_Partially decomposed organic matter.
40 No Peat Slightly decomposed organic material of any thickness that is saturated with water for 30 or more cumulative days in normal years (or is artificially drained), including that in Histels and Histosols, except for Folists.
41 obsolete_Petroferric Petroferric
42 No Paraflagstones Paraflagstones
43 No Paragravel Paragravel
44 obsolete_Petrogypsic Petrogypsic
45 obsolete_Placic Placic
46 No Parastones Parastones
47 obsolete_Pumiceous Pumiceous
48 obsolete_Sand and gravel Sand and gravel
49 Slightly decomposed plant material No Slightly decomposed plant material that is saturated with water for less than 30 cumulative days in normal years (and is not artificially drained).
50 No Stones Stones
51 obsolete_Unknown texture Unknown texture
52 Undecomposed organic matter obsolete_Undecomposed organic matter
53 obsolete_Unweathered bedrock Unweathered bedrock
54 obsolete_Variable Variable
55 No Water Water
56 obsolete_Weathered bedrock Weathered bedrock
*/
//_____________________________________________________________________________
typedef std::string  texture_class
; /* = 
Length of Longest Choice Value: 20
1 No Clay
2 No Clay loam
3 No Coarse sand
4 No Coarse sandy loam
5 No Fine sand
6 No Fine sandy loam
7 No Loam
8 No Loamy coarse sand
9 No Loamy fine sand
10 No Loamy sand
11 No Loamy very fine sand
12 No Sand
13 No Sandy clay
14 No Sandy clay loam
15 No Silt
16 No Silty clay
17 No Silty clay loam
18 No Silt loam
19 No Sandy loam
20 No Very fine sand
21 No Very fine sandy loam
*/
typedef std::string  texture_modifier
; /* =
1 No Artifactual 15 to 35 percent human artifacts, by volume
2 No Very artifactual 35 to 60 percent human artifacts, by volume
3 No Extremely artifactual 60 to 90 percent human artifacts, by volume
4 No Ashy Ashy
5 No Bouldery Bouldery
6 No Very bouldery Very bouldery
7 No Extremely bouldery Extremely bouldery
8 No Cobbly Cobbly
9 obsolete_Angular cobbly Angular cobbly
10 No Very cobbly Very cobbly
11 No Extremely cobbly Extremely cobbly
12 No Cemented The material being modified is cemented by one or more cementing agents such that it does not slake in water.
13 No Channery Channery
14 No Very channery Very channery
15 No Extremely channery Extremely channery
16 No Coprogenous Coprogenous
17 obsolete_Cherty
18 obsolete_Very cherty
19 obsolete_Extremely cherty
20 obsolete_Cindery
21 No Diatomaceous Diatomaceous
22 No Flaggy Flaggy
23 No Very flaggy Very flaggy
24 No Extremely flaggy Extremely flaggy
25 No Gravelly Gravelly
26 No Coarse gravelly Coarse gravelly
27 No Fine gravelly Fine gravelly
28 No Medium gravelly Medium gravelly
29 No Very gravelly Very gravelly
30 No Extremely gravelly Extremely gravelly
31 No Grassy Grassy
32 obsolete_Gritty
33 No Gypsiferous Gypsiferous
34 No Herbaceous Herbaceous
35 obsolete_Hemic
36 No Highly organic Highly organic is used to modify near surface horizons of mineral soils that are saturated with water for less than 30 cumulative days in normal
years (and are not artificially drained). Excluding live roots, the horizon has organic carbon content (by weight) of: 5 to < 20 percent if the mineral
fraction contains no clay; or 12 to < 20 percent if the mineral fraction contains 60 percent or more clay; or ((5 + (clay percentage multiplied by
0.12)) to < 20 percent if the mineral fraction contains less than 60 percent clay. The organic material is at least partially decomposed.
37 No Hydrous Hydrous
38 obsolete_Indurated
39 No Medial Medial
40 No Mucky Mucky is used to modify near surface horizons of mineral soils that are saturated with water for 30 or more cumulative days in normal years (or
are artificially drained). An example is mucky loam. Excluding live roots, the horizon has organic carbon content (by weight) of 5 to < 12 percent if
the mineral fraction contains no clay; or 12 to < 18 percent if the mineral fraction contains 60 percent or more clay; or (5 + (clay percentage
multiplied by 0.12)) to < (12 + (clay percentage multiplied by 0.10)) if the mineral fraction contains less than 60 percent clay. The organic
material is highly decomposed.
41 obsolete_Mucky*
42 No Marly Marly
43 No Mossy Mossy
44 No Parabouldery Parabouldery
45 No Very parabouldery Very parabouldery
46 No Extremely parabouldery Extremely parabouldery
47 No Paracobbly Paracobbly
48 No Very paracobbly Very paracobbly
49 No Extremely paracobbly Extremely paracobbly
50 No Parachannery Parachannery
51 No Very parachannery Very parachannery
52 No Extremely parachannery Extremely parachannery
53 No Permanently frozen Permanently frozen
54 No Paraflaggy Paraflaggy
55 No Very paraflaggy Very paraflaggy
56 No Extremely paraflaggy Extremely paraflaggy
57 No Paragravelly Paragravelly
58 No Very paragravelly Very paragravelly
59 No Extremely paragravelly Extremely paragravelly
60 No Parastony Parastony
61 No Very parastony Very parastony
62 No Extremely parastony Extremely parastony
63 No Peaty Peaty is used to modify near surface horizons of mineral soils that are saturated with water for 30 or more cumulative days in normal years (or
are artificially drained). An example is peaty loam. Excluding live roots, the horizon has organic carbon content (by weight) of: 5 to < 12 percent if
the mineral fraction contains no clay; or 12 to < 18 percent if the mineral fraction contains 60 percent or more clay; or (5 + (clay percentage
multiplied by 0.12)) to < (12 + (clay percentage multiplied by 0.10)) if the mineral fraction contains less than 60 percent clay. The organic material
is slightly decomposed.
64 obsolete_Shaly
65 obsolete_Very shaly
66 obsolete_Extremely shaly
67 obsolete_Stratified Stratified
68 No Stony Stony
69 No Very stony Very stony
70 No Extremely stony Extremely stony
71 obsolete_slaty
72 obsolete_Very slaty
73 obsolete_Extremely slaty
74 No Woody Woody
*/
//_____________________________________________________________________________
typedef std::string  tiebreakrule
; /* = 
Length of Longest Choice Value: 19
1 No Select Lower Value
2 No Select Higher Value
SSURGO Version: 2.2.3 Page 232
*/ //_____________________________________________________________________________

typedef std::string  unified_soil_classification
; /* = 
Length of Longest Choice Value: 15
1 No CH FINE-GRAINED SOILS, Silts and clays (liquid limit is 50% or more), Fat Clay.
2 No CL FINE-GRAINED SOILS, Silts and clays (liquid limit is less than 50%), Lean Clay.
3 No CL-A (proposed)
4 No CL-K (proposed)
5 No CL-ML
6 No CL-O (proposed)
7 No CL-T (proposed)
8 No GC COARSE-GRAINED SOILS, Gravels, gravel with fines, Clayey Gravel.
9 No GC-GM
10 No GM COARSE-GRAINED SOILS, Gravels, Gravels with fines, Silty Gravel
11 No GP COARSE-GRAINED SOILS, Gravels, clean gravels, Poorly Graded Gravel.
12 No GP-GC
13 No GP-GM
14 No GW COARSE-GRAINED SOILS, Gravels, clean gravels, Well-Graded Gravel.
15 No GW-GC
16 No GW-GM
17 No MH FINE-GRAINED SOILS, Silts and clays, (liquid limit is 50% or more), Elastic Silt.
18 No MH-A (proposed)
19 No MH-K (proposed)
20 No MH-O (proposed)
21 No MH-T (proposed)
22 No ML FINE-GRAINED SOILS, Silts and clays, (liquid limit is less than 50%), Silt.
23 No ML-A (proposed)
24 No ML-K (proposed)
25 No ML-O (proposed)
26 No ML-T (proposed)
27 No OH FINE-GRAINED SOILS, Silts and clays, (liquid limit is 50% or more), Organic Clay or Organic Silt
28 No OH-T (proposed)
29 No OL FINE-GRAINED SOILS, Silts and clays (liquid limit is less than 50%), Organic Clay or Organic Silt.
30 No PT Highly organic soils, Peat.
31 No SC COARSE-GRAINED SOILS, Sands, sands with fines, Clayey Sand.
32 No SC-SM
33 No SM COARSE-GRAINED SOILS, Sands, Sands with fines, Silty Sand.
34 No SP COARSE-GRAINED SOILS, Sands, Clean Sands, Poorly Graded Sand,
35 No SP-SC
36 No SP-SM
37 No SW COARSE-GRAINED SOILS, Sands, Clean Sands, Well-graded Sand.
38 No SW-SC
39 No SW-SM
*/
//_____________________________________________________________________________
typedef std::string  va_soil_management_group
; /* =
Length of Longest Choice Value: 2
1 No QQ
2 No PP
3 No OO
4 No NN
5 No MM
6 No LL
7 No KK
8 No JJ
9 No II
10 No HH
11 No GG
12 No FF
13 No EE
14 No DD
15 No CC
16 No BB
17 No AA
18 No Z
19 No Y
20 No X
21 No W
22 No V
23 No U
24 No T
25 No S
26 No R
27 No Q
28 No P
29 No O
30 No N
31 No M
32 No L
33 No K
34 No J
35 No I
36 No H
37 No G
38 No F
39 No E
40 No D
41 No C
42 No B
43 No A
*/
//_____________________________________________________________________________
typedef std::string  va_soil_productivity_group
; /* = 
Length of Longest Choice Value: 4
1 No NS Not suited.
2 No Vb
3 No Va
4 No V
5 No IVb
6 No IVa
7 No IV
8 No IIIb
9 No IIIa
10 No III
11 No IIb
12 No IIa
13 No II
14 No Ib
15 No Ia
16 No I
*/
//_____________________________________________________________________________
typedef std::string  vt_septic_system_class
; /* = 
Length of Longest Choice Value: 29
1 Conventional/Soil
Replacement
No Map units that will support a conventional inground septic system with some soil backfilling of finer textured soil material.
2 No Conventional Map units will support a conventional inground septic system with little or no site modification.
3 No Mound Mapunits that normally require a mound system.
4 No Test, Mound, Curtain Drain Map units that normally require a mound septic system with a curtain drain.
5 No Marginally Suitable Map units with soil conditions that make it difficult to locate an acceptable site for a septic system.
6 No Unsuitable Map units that are unsuitable for a septic system.
7 No Not Rated Map units that are not rated because of lack of soil material.
*/
typedef std::string  wildlife_rating
;/*
Length of Longest Choice Value: 9
1 No Very poor
2 No Poor
3 No Fair
4 No Good
SSURGO Version: 2.2.3 Page 236
*/ //_____________________________________________________________________________
typedef std::string  wind_erodibility_group
; /* =
Length of Longest Choice Value: 2
1 No 1 Surface texture - Very fine sand, fine sand, sand or coarse sand. Percent aggregates - 1 to 7. Wind erodibility index - 160 to 310 t/a/yr, use 220
as average.
2 No 2 Surface texture - Loamy very fine sand, loamy fine sand, loamy sand, loamy coarse sand; very fine sandy loam and silt loam with 5 or less
percent clay and 25 or less percent very fine sand; and sapric soil materials (as defined in Soil Taxonomy); except Folists. Percent aggregates -
10. Wind erodibility index - 134 t/a/yr.
3 No 3 Surface texture - Very fine sandy loam, fine sandy loam, sandy loam, coarse sandy loam, and noncalcareous silt loam that has 20 to 50 percent
very fine sand and 5 to 12 percent clay. Percent aggregates - 25. Wind Erodibility Index - 86 t/a/yr.
4 No 4 Surface texture - Clay, silty clay, noncalcareous clay loam that has more than 35 percent clay, and noncalcareous silty clay loam that has more
than 35 percent clay. All of these do not have sesquic, parasesquic, ferritic, ferruginous, or kaolinitic mineralogy (high iron oxide content).
Percent aggregates - 25. Wind erodibility index - 86 t/a/yr.
5 No 4L Surface texture - Calcareous loam, calcareous silt loam, calcareous silt, calcareous sandy clay, calcareous sandy clay loam, calcareous clay
loam and calcareous silty clay loam. Percent aggregates - 25 .Wind Erodibility Index - 86 t/a/yr.
6 No 5 Surface texture - Noncalcareous loam that has less than 20 percent clay; noncalcareous silt loam with 12 to 20 percent clay; noncalcareous
sandy clay loam; noncalcareous sandy clay; and hemic materials (as defined in Soil Taxonomy). Percent aggregates - 40. Wind Erodibility
Index - 56 t/a/yr.
7 No 6 Surface texture - Noncalcareous loam and silt loam that have more than 20 percent clay; noncalcareous clay loam and noncalcareous silty clay
loam that has less than 35 percent clay; silt loam that has parasesquic, ferritic, or kaolinitic mineralogy (high iron oxide content). Percent
aggregates - 45. Wind Erodibility Index - 48 t/a/yr.
8 No 7 Surface texture - Noncalcareous silt; noncalcareous silty clay, noncalcareous silty clay loam, and noncalcareous clay that have sesquic,
parasesquic, ferritic, ferruginous, or kaolinitic mineralogy (high content of iron oxide) and are Oxisols or Ultisols; and fibric material (as defined in
Soil Taxonomy). Percent aggregates - 50. Wind Erodibility Index - 48 t/a/yr.
9 No 8 Soils not susceptible to wind erosion due to rock and pararock fragments at the surface and/or wetness; and Folists
*/
//_____________________________________________________________________________
typedef std::string  wind_erodibility_index
; /* =
Length of Longest Choice Value: 3
1 No 0 Soils not susceptible to wind erosion due to coarse fragments on the surface or wetness.
2 No 38 Silt, noncalcareous silty clay loam that has less than 35 percent clay content, and fibric organic soil material. Dry soil aggregates more than .84
mm are more than 50 percent by weight.
3 No 48 Noncalcareous loam and silt loam that has more than 20 percent clay content or noncalcareous clay loam that has less than 35 percent clay
content. Dry soil aggregates more than .84 mm are 45 to 50 percent by weight.
4 No 56 Noncalcareous loam and silt loam that has less than 20 percent clay content or sandy clay loam, sandy clay, and hemic organic soil materials.
Dry soil aggregates more than .84 mm are 40 to 45 percent by weight.
5 No 86 Very fine sandy loam, fine sandy loam, sandy loam, coarse sandy loam, or ash material. Clay, silty clay, noncalcareous clay loam, or
noncalcareous silty clay loam that has more than 35 percent clay content. Calcareous loam and silt loam or calcareous clay loam and silty clay
loam. Dry soil aggregates more than .84 mm are 25 to 40 percent by weight.
6 No 134 Loamy very fine sand, loamy fine sand, loamy sand, loamy coarse sand, or sapric organic soil material. Dry soil aggregates more than .84 mm
are 10 to 25 percent by weight.
7 No 160 Very fine sand, fine sand, sand, or coarse sand. Dry soil aggregates more than .84 mm are 7 to 10 percent by weight.
8 No 180 Very fine sand, fine sand, sand, or coarse sand. Dry soil aggregates more than .84 mm are 5 to 7 percent by weight.
9 No 220 Very fine sand, fine sand, sand, or coarse sand. Dry soil aggregates more than .84 mm area 3 to 5 percent by weight.
10 No 250 Very fine sand, fine sand, sand, or coarse sand. Dry soil aggregates more than .84 mm are 1 percent by weight.
11 No 310 Very fine sand, fine sand, sand, or coarse sand. Dry soil aggregates more than .84 mm are 1 percent by weight.

*/
//_____________________________________________________________________________
typedef std::string  windbreak_suitability_group
; /* =
Length of Longest Choice Value: 4
1 No 1
2 No 1H
3 No 1K
4 obsolete_1KW
5 No 1KK
6 No 2
7 No 2K
8 obsolete_2KW
9 No 2KK
10 No 2H
11 No 3
12 No 4
13 No 4K
14 No 4C
15 No 4CK
16 No 5
17 No 5K
18 No 5KK
19 No 6
20 No 6K
21 No 6KK
22 No 6D
23 No 6DK
24 No 6G
25 No 6GK
26 No 6GKK
27 No 7
28 No 8
29 No 8K
30 obsolete_9
31 No 9C
32 No 9W
33 No 9L
34 No 10
35 No 1A
36 No 2A
37 No 1S
38 No 1SK
39 No 1SKK
40 No 3A
41 No 4A
42 No 4CA
43 No 4CC
44 No 5A
45 No 6A
46 No 6DA
47 No 6GA
48 No 7A
49 No 9N
50 No 9NW
SSURGO Version: 2.2.3 Page 239
*/
//_____________________________________________________________________________
}; // namespace USDA_NRCS
#endif
