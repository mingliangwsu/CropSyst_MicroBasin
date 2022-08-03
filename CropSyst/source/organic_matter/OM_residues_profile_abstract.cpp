#include "organic_matter/OM_residues_profile_abstract.h"
#include "soil/soil_interface.h"
#include "soil/structure_interface.h"
#include "corn/measure/measures.h"
#include "common/residue/residues_interface.h"
//______________________________________________________________________________
Organic_matter_residues_profile_abstract::Organic_matter_residues_profile_abstract
(Soil_interface   *soil_
,const CORN::date32 &today_)                                                     //140507
: CS::Simulation_element_abstract(today_)                                        //160627
, soil_layers         (*(soil_->ref_layers()))                                   //160412
, soil_texture        (*(soil_->ref_texture()))                                  //160412
, soil_hydrology      (*(soil_->ref_hydrology()))                                //160412
, soil_nitrogen       (  soil_->mod_nitrogen())                                  //160412
, soil_structure      (*(soil_->ref_structure()))                                //160522
{ }
//_2007-07-25_2006-01-22__________________________________________constructor__/
float64 Organic_matter_residues_profile_abstract::get_percent_organic_matter(nat8 in_layer) const
{
   float64 thickness_sl_m = soil_layers.get_thickness_m(in_layer);
   float64 bulk_density_sl_kg_m3 = g_cm3_to_kg_m3(soil_structure.get_bulk_density_g_cm3(in_layer)); //070725
   // 040503 warning density in kg/cm3?  that is what it looks to be in the original CS code,
   // but new C&N model Visual basic shows this term to be on the order of 1200 kg/m3.
   float64 OM_mass = get_organic_matter_mass(in_layer);                          //060401
   return (OM_mass * 100.0) / (thickness_sl_m * bulk_density_sl_kg_m3);
}
//_________________________________________________get_percent_organic_matter__/
bool Organic_matter_residues_profile_abstract::clear_residues()  initialization_
{  bool cleared = true;
   Residues_interface *residues = mod_residues();                                //160627
   if (residues) cleared &= residues->clear_all();
   return cleared;
}
//_2016-01-26___________________________________________________clear_residues_/


