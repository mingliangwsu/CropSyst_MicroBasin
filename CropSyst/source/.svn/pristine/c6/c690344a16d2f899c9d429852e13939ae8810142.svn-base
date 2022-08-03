
#include "mgmt_types.h"
#include "corn/math/compare.hpp"
#include "corn/measure/measures.h"
using namespace std;
//______________________________________________________________________________
const char *irrigation_application_mode_label_table[] =
{  "fixed_amount"
,  "soil_requirements"  // eventually rename to irrigate_refill
,0};
//_2004-10-28___________________________________________________________________
const char *irrigation_consideration_mode_label_table[] =
{  "soil_water_depletion"
,  "leaf_water_potential"
,0};
//_2009-12-01___________________________________________________________________
const char *V3_automatic_clipping_mode_label_table[] =
{LABEL_disabled
,LABEL_biomass
,LABEL_periodic
,0};
//_1998-08-26___________________________________________________________________
const char *depletion_observation_depth_mode_label_table[] =
{ "constant_fixed_depth"
, "fraction_of_root_depth"
, "soil_profile_depth"
, 0 };
//_20070-06-06__________________________________________________________________
const char *irrigation_system_label_table[] =
{ "none","center_pivot","other"};
//_2011-07-19__________________________________________________________________/
const char *V3_biomass_fate_label_table[] =
{"harvest"
,"remove"
,"residue"
,"graze"                                                                         //040126
,0};
//_1998-08-26___________________________________________________________________
const char *harvest_amount_mode_label_table[] =
{"crop_param"
,"remove_biomass" // fixed biomass
,"percent_biomass"                                                               //051103
,"retain_GAI"     // obsolete
,"other"          // I.e. dormancy
,0};
//_2005-08-22___________________________________________________________________
const char *harvest_mode_and_biomass_fated_cause_label_table[]=
{"harvest_once"                                                                  //040914
,"clipping"
,"last_clipping"
,"grazing"
,"defoliation"
,"harvest_index" // obsolete replaced by harvest_once                            //040914
// The following are biomatter fated causes                                      //050929
,"clip_now_or_never"                                                             //040622
,"insufficient_biomass_for_final_clipping"                                       //040622
,"clipping_due_to_low_growth"                                                    //040622
,"clipping_due_to_max_biomass"                                                   //040830
,"clipping_due_to_max_LAI"                                                       //040830
,"clipping_due_to_days_after_flowering"                                          //040830
,"freezing_damage"                                                               //040622
,"freezing_death"                                                                //040622
,"dormancy"                                                                      //040622
,"natural_expiration"                                                            //040805
,"crop_termination"                                                              //040622
,"multiple"                                                                      //070201
,0};
//______________________________________________________________________________
const char * mass_fate_label_table[] =
{"yield"
,"useful"
,"disposal"
,"chaff"
,"stubble"
,"grazing_to_manure"
,"grazing_to_disposal"
,"uncut_canopy"
,0};
//_2007-02-06___________________________________________________________________
const char *Management_ops_label_table[] =
{"NO_MANAGEMENT"
,LABEL_tillage
,LABEL_residue
,LABEL_irrigation
,LABEL_fertilization
,LABEL_organic_fertilization                                                     //981228
,LABEL_chemical
,LABEL_clipping                                                                  //991122
,LABEL_auto_N_application                                                        //991122
,0
};
//_1997-07-09___________________________________________________________________
const char *automatic_N_mode_label_table[] =
{LABEL_disabled
,LABEL_balance_based
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <= 4))
//120710  Local calibration mode was special for ?Javier?  Claudio decided to remove it. 
,LABEL_local_calibration
#endif
,0                                                                               //990521
};
//_1999-02-25___________________________________________________________________
void Crop_mass_fate::log(ostream &event_log)                               const
{
   event_log << "cause=" << harvest_mode_and_biomass_fated_cause_label_table[cause] << endl; //070205
   if (!CORN::is_approximately<float64>(yield,0.0,0.000001))
      event_log << "primary_yield=" << per_m2_to_per_ha(yield)	<< endl;
   if (!CORN::is_approximately<float64>(useful,0.0,0.000001))
       event_log << "secondary_yield=" << per_m2_to_per_ha(useful)<< endl;
   if (!CORN::is_approximately<float64>(disposal,0.0,0.000001))
       event_log << "loss=" << per_m2_to_per_ha(disposal)<< endl;
   if (!CORN::is_approximately<float64>(get_removed_for_grazing(),0.0,0.000001))
       event_log << "grazing=" << per_m2_to_per_ha(get_removed_for_grazing())		  << " (includes total biomass consumed)" << endl;
   if (!CORN::is_approximately<float64>(chaff_or_leaf_litter,0.0,0.000001))
       event_log << "residue=" << per_m2_to_per_ha(chaff_or_leaf_litter)<< endl;
   if (!CORN::is_approximately<float64>(uncut_canopy,0.0,0.000001))
       event_log << "uncut=" << per_m2_to_per_ha(uncut_canopy)			<< endl;
   if (!CORN::is_approximately<float64>(stubble_dead,0.0,0.000001))
       event_log << "standing_dead=" << per_m2_to_per_ha(stubble_dead)			<< endl;
   if (!CORN::is_approximately<float64>(root_before,0.0,0.000001))               //110814
       event_log << "root_biomass_before=" << per_m2_to_per_ha(root_before)	<< endl; //110814
   /*
   if (!CORN::is_approximately<float64>(remove_roots_to_dead_residue,0.0,0.000001))                            //110814
       event_log << "remove_roots_to_dead_residue=" << per_m2_to_per_ha(remove_roots_to_dead_residue)	<< endl; //110814
   if (!CORN::is_approximately<float64>(remain_roots_live,0.0,0.000001))                                       //110814
       event_log << "remain_roots_live=" << per_m2_to_per_ha(remain_roots_live)			               << endl; //110814
   if (!CORN::is_approximately<float64>(remove_roots_as_loss,0.0,0.000001))                                    //110814
       event_log << "remove_roots_as_loss=" << per_m2_to_per_ha(remove_roots_as_loss)			         << endl; //110814 //110814
   */

   event_log << "units=kg/ha" << endl;
}
//_2004-06-10___________________________________________________________________
static nat8 root_soil_layers_for_dump;
   // This is to remember how many soil layers were requested to dump matching the headers
   // Normally it would be sufficient to get the number of soil layers
   // but in long time simulations with erosion removal,
   // it is possible that the number of layers decreases.
//_2007-02-01___________________________________________________________________
void Crop_mass_fate::dump(ostream &dump_log,bool include_live)             const
{  float64 non_yield = useful + disposal + chaff_or_leaf_litter + stubble_dead + grazing_to_manure + grazing_to_disposal;
   dump_log << harvest_mode_and_biomass_fated_cause_label_table[cause];          //070205
   dump_log << '\t'  <<  per_m2_to_per_ha(yield);
   dump_log << '\t'  <<  per_m2_to_per_ha(useful);
   dump_log << '\t'  <<  per_m2_to_per_ha(disposal);
   dump_log << '\t'  <<  per_m2_to_per_ha(chaff_or_leaf_litter);
   dump_log << '\t'  <<  per_m2_to_per_ha(stubble_dead);
   dump_log << '\t'  <<  per_m2_to_per_ha(grazing_to_manure);
   dump_log << '\t'  <<  per_m2_to_per_ha(grazing_to_disposal);
   dump_log << '\t'  <<  per_m2_to_per_ha(uncut_canopy);
   dump_log << '\t'  <<  per_m2_to_per_ha(non_yield);
   float64 root_balance = root_before;
   for (nat8 layer = 1; layer <= root_soil_layers_for_dump; layer++)
   {  root_balance -= roots_dead[layer];
      dump_log<< '\t'  <<  per_m2_to_per_ha(roots_dead[layer]);
   }
   root_balance -= root_after;
   for (nat8 layer = 1; layer <= root_soil_layers_for_dump; layer++)
      dump_log<< '\t'  <<  per_m2_to_per_ha(roots_live[layer]);
   float64 canopy_balance = canopy_before
         -yield -useful-disposal-chaff_or_leaf_litter-stubble_dead-grazing_to_manure-grazing_to_disposal // removal //070201 - damage_to_residue -death_stubble
         - uncut_canopy; // remaining
   dump_log
   << '\t'  <<  per_m2_to_per_ha(canopy_before)
   << '\t'  <<  per_m2_to_per_ha(canopy_balance)
   << '\t'  <<  per_m2_to_per_ha(root_before)
   << '\t'  <<  per_m2_to_per_ha(root_balance);
}
//_2007-02-01___________________________________________________________________
void Crop_mass_fate::dump_headers(ostream &dump_log,bool include_live,nat8 root_soil_layers,const char *caption_suffix) const
{  root_soil_layers_for_dump = root_soil_layers;
   dump_log << "cause"
    << '\t'  <<  "yield_" << caption_suffix
    << '\t'  <<  "useful_" << caption_suffix
    << '\t'  <<  "dispose_" << caption_suffix
    << '\t'  <<  "chaff_" << caption_suffix
    << '\t'  <<  "stubble_" << caption_suffix
    << '\t'  <<  "grazing_manure_" << caption_suffix
    << '\t'  <<  "grazing_dispose_" << caption_suffix
    << '\t'  <<  "uncut_canopy_" << caption_suffix
    << '\t'  <<  "non_yield_" << caption_suffix ;
   for (nat8 layer = 1; layer <= root_soil_layers_for_dump; layer++)
      dump_log<< '\t'  <<  "root_dead_" << caption_suffix << "_" << (int)layer ;
   if (include_live)
   {  for (nat8 layer = 1; layer <= root_soil_layers_for_dump; layer++)
         dump_log<< '\t'  <<  "root_live_" << caption_suffix << "_" << (int)layer;
   }
   dump_log
   << '\t'  <<  "canopy_mass_before" << caption_suffix
   << '\t'  <<  "canopy_balance" << caption_suffix
   << '\t'  <<  "root_mass_before"<< caption_suffix
   << '\t'  <<  "root_balance"<< caption_suffix;
}
//_2007-02-01___________________________________________________________________
void Crop_mass_fate::add(const Crop_mass_fate &augend)
{  if (cause != augend.cause) cause = MULTIPLE_CAUSES;
   for (nat8 ag = 0; ag < FATE_INDEX_COUNT; ag++)                                //070206
       above_ground[ag] += augend.above_ground[ag];                              //070206
   for (short int sublayer = 1; sublayer <= MAX_soil_sublayers; sublayer++)
       roots_dead[sublayer] += augend.roots_dead[sublayer];
   // For the live materials, we dont add, we just set the value of the augend
   uncut_canopy               = augend.uncut_canopy;
   for (short int sublayer = 1; sublayer <= MAX_soil_sublayers; sublayer++)
       roots_live[sublayer] += augend.roots_live[sublayer];
   // similar for root
// Warning will eventually add root matter
}
//_2004-06-10___________________________________________________________________
float64 Crop_mass_fate::get_dead_roots_residue() const
{
   float64 total = 0.0;
   for (nat8 sl = 0; sl <= MAX_soil_horizons; sl++)
      total += roots_dead[sl];
   return total;
}
//______________________________________________________________________________
float64 Crop_mass_fate::get_total_removed_from_plant(bool include_root) const
{  float64 total_removed
   =    yield
      + useful
      + disposal
      + chaff_or_leaf_litter
      + stubble_dead                                                             //040809
      + (include_root ? get_dead_roots_residue() : 0.0);
    return total_removed;
}
//______________________________________________________________________________
// This constructor is used for Plant N from plant biomass and concentration
//040625    // Currently assuming N concentration is same throughout the plant, but this is probably not the case.
Crop_mass_fate::Crop_mass_fate(const Crop_mass_fate &biomass_fate,float64 top_concentration,float64 root_concentration)
: yield                 (above_ground[INDEX_YIELD])
, useful                (above_ground[INDEX_USED])
, disposal              (above_ground[INDEX_DISPOSAL])
, chaff_or_leaf_litter  (above_ground[INDEX_CHAFF])
, stubble_dead          (above_ground[INDEX_STUBBLE])
, grazing_to_manure     (above_ground[INDEX_GRAZED_MANURE])
, grazing_to_disposal   (above_ground[INDEX_GRAZED_DISPOSAL])
, uncut_canopy          (above_ground[INDEX_UNCUT_CANOPY])
, canopy_before (top_concentration*biomass_fate.canopy_before)
, root_before   (root_concentration*biomass_fate.root_before)
, canopy_after  (top_concentration*biomass_fate.canopy_after)
, root_after    (root_concentration*biomass_fate.root_after)
, cause                 (biomass_fate.cause)                                     //070201
{  for (nat8 ag = 0; ag < FATE_INDEX_COUNT; ag++)                               //070206
      above_ground[ag] =   top_concentration * biomass_fate.above_ground[ag];
   for (nat8 sl = 0; sl <= MAX_soil_sublayers; sl++)
   {     roots_dead[sl] = root_concentration*biomass_fate.roots_dead[sl];
         roots_live[sl] = root_concentration*biomass_fate.roots_live[sl];
   }
}
//_2007-01-31___________________________________________________________________
Crop_mass_fate::Crop_mass_fate(Biomass_fated_cause _cause,float64 _canopy_before,float64 _root_before)
: yield                 (above_ground[INDEX_YIELD])
, useful                (above_ground[INDEX_USED])
, disposal              (above_ground[INDEX_DISPOSAL])
, chaff_or_leaf_litter  (above_ground[INDEX_CHAFF])
, stubble_dead          (above_ground[INDEX_STUBBLE])
, grazing_to_manure     (above_ground[INDEX_GRAZED_MANURE])
, grazing_to_disposal   (above_ground[INDEX_GRAZED_DISPOSAL])
, uncut_canopy           (above_ground[INDEX_UNCUT_CANOPY])
, canopy_before         (_canopy_before)
, root_before   (_root_before)
, canopy_after  (_canopy_before) // at this point we haven't determined a fate
, root_after    (_root_before)     // so simply set after values to the before values
, cause(_cause)                                                                  //070201
{  for (nat8 ag = 0; ag < FATE_INDEX_COUNT; ag++)                               //070206
      above_ground[ag] =   0.0;
   clear_sublayer_array(roots_dead);
   clear_sublayer_array(roots_live);
}
//______________________________________________________________________________
   // Copy constructor
Crop_mass_fate::Crop_mass_fate(const Crop_mass_fate &copy_from_biomass_fate)
: yield                 (above_ground[INDEX_YIELD])
, useful                (above_ground[INDEX_USED])
, disposal              (above_ground[INDEX_DISPOSAL])
, chaff_or_leaf_litter  (above_ground[INDEX_CHAFF])
, stubble_dead          (above_ground[INDEX_STUBBLE])
, grazing_to_manure     (above_ground[INDEX_GRAZED_MANURE])
, grazing_to_disposal   (above_ground[INDEX_GRAZED_DISPOSAL])
, uncut_canopy           (above_ground[INDEX_UNCUT_CANOPY])
, canopy_before (copy_from_biomass_fate.canopy_before)
, root_before   (copy_from_biomass_fate.root_before)
, canopy_after  (copy_from_biomass_fate.canopy_after)
, root_after    (copy_from_biomass_fate.root_after)
, cause                 (copy_from_biomass_fate.cause)                           //070201
{  for (nat8 ag = 0; ag < FATE_INDEX_COUNT; ag++)                               //070206
      above_ground[ag] =   copy_from_biomass_fate.above_ground[ag];
   for (nat8 sl = 0; sl <= MAX_soil_sublayers; sl++)
   {  roots_dead[sl] = copy_from_biomass_fate.roots_dead[sl];
      roots_live[sl] = copy_from_biomass_fate.roots_live[sl];
   }
}
//_2007-01-30___________________________________________________________________
bool Crop_mass_fate::has_any_mass()                            const
{  return get_total_removed_from_plant() > 0.0;
}
//_2007-06-25___________________________________________________________________
void clear_biomass_fate_parameters(Biomass_fate_parameters &BMF_param)
{
   BMF_param.remove_for_use                =0;
   BMF_param.remove_for_grazing            =0;
   BMF_param.remain_as_residue             =0;
   BMF_param.remove_for_disposal           =0;
   BMF_param.remain_as_dead                =0;
   BMF_param.remain_as_live                =0;
   BMF_param.remove_roots_to_dead_residue  =0;
   BMF_param.remain_roots_live             =0;
   BMF_param.remove_roots_as_loss          =0;
   BMF_param.return_as_manure              =0;
}
//_2005-07-18___________________________________________________________________
Crop_mass_fate_biomass_and_nitrogen::Crop_mass_fate_biomass_and_nitrogen
( Crop_mass_fate *biomass_
, Crop_mass_fate *nitrogen_)
: biomass (biomass_)
, nitrogen(nitrogen_)
{}
//______________________________________________________________________________
Crop_mass_fate_biomass_and_nitrogen::~Crop_mass_fate_biomass_and_nitrogen()
{  delete biomass;  biomass = 0;
   delete nitrogen; nitrogen = 0;
}
//______________________________________________________________________________
void Crop_mass_fate_biomass_and_nitrogen::accumulate(const Crop_mass_fate_biomass_and_nitrogen &augend)
{  biomass->add(*augend.biomass);
   if (nitrogen && augend.nitrogen) nitrogen->add(*augend.nitrogen);
}
//_2007-06-27___________________________________________________________________

