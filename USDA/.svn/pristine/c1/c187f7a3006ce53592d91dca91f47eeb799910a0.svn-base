#include "USDA/NRCS/soil/survey/domains.h"
namespace USDA_NRCS
{
//_____________________________________________________________________________
Label_description capability_class_label_table[] =
{{ " ","STATSGO leaves the field blank when not known"}
,{ "1","Soils in Class 1 (I) have few limitations that restrict their use."}
,{ "2","Soils in Class 2 (II) have some limitations that reduce the choice of plants or require moderate conservation practices."}
,{ "3","Soils in Class 3 (III) have severe limitations that reduce the choice of plants or require special conservation practices, or both."}
,{ "4","Soils in Class 4 (IV) have very severe limitations that restrict the choice of plants, require very careful management, or both."}
,{ "5","Soils in Class 5 (V) have little or no erosion hazard but have other limitations impractical to remove that limit their use."}
,{ "6","Soils in Class 6 (VI) have severe limitations that make them generally unsuited to cultivation and limit their use largely to pasture, etc."}
,{ "7","Soils in Class 7 (VII) have very severe limitations that make them unsuited to cultivation and that restrict their use to grazing, etc."}
,{ "8","Soils (and landforms) in Class 8 (VIII) have limitations that preclude their use for commercial plant production and restrict their use."}
,{0,0}};
//_____________________________________________________________________________
Label_description capability_subclass_label_table[] =
{{" ","Not assigned for capacility class I and often VIII"}
// The following codes are the canonical NRCS codes used in soil surface
,{"E","Erosion"}
,{"W","Excess water (groundwater)"}
,{"S","Soil limitations (such as shallow root zone,stones, moisture deficiency, low fertility, salinity)"}
,{"C","Adverse climate (excluding precipitation)"}
// The following codes are extensions used by the canadian land survey (1999)
// (ref: http://sis.agr.gc.ca/cansis/nsdb/cli/classdesc.html
//  contact: Peter Schut, http://sis.agr.gc.ca.cansis/org/schut.html)
,{"A","Moisture deficiency"}
,{"D","Undesirable soil structure (and/or low permeability)"}
,{"F","Low fertility"}
,{"I","Inundataion (flooding by streams, lakes etc.)"}
,{"M","Moisture limitations"}
,{"N","Salinity"}
,{"P","Stoniness"}
,{"R","Shallow soil over bedrock and/or bedrock outcroppings"}
,{"T","Topography"}
,{"X","Limitation resulting from the cumulative effect of two or more adverse characteristics"}
,{0,0}};
//_____________________________________________________________________________
Label_description component_kind_label_table[] =
{{ "Miscellaneous area","The component is classified and described as a non-soil area."}  // Not sure if STATSGO leaves this field blank when not known
,{ "Series","The component is classified and described at the soil series level, the lowest level of Soil Taxonomy."}
,{ "Family","The component is classified and described at the family level of Soil Taxonomy."}
,{ "Variant","The component is described as being outside the range of the series for which it is named. The differences are great enough to warrant a new series, they do affect the use and management of the soil, but the geographical extent is considered too small to justify creating a new series."}
,{ "Taxadjunct","The component is described slightly outside the Soil Taxomonic limits of the name assigned. However, these differences are not significant enough to affect use and management of the soil."}
,{ "Taxon above family","The component is described and classified at some level of Soil Taxonomy above the family level."}
,{0,0}};
//_____________________________________________________________________________
Label_description hydrologic_group_label_table[] =
{{"A","Low runoff potential"}
,{"B","Moderately low runoff potential"}
,{"C","Moderately high runoff potential"}
,{"D","High runoff potential"}
  // Special cases (converted to A B C in CropSyst)
,{"A/D","Low runoff potential when drained and high runoff potential undrained"}
,{"B/D","Moderately low runoff potential when drained and high runoff potential undrained"}
,{"C/D","Moderately high runoff potential when drained and high runoff potential undrained"}
,0
};
//_2011-02-16___________________________________________________________________
} // namespace USDA_NRCS
