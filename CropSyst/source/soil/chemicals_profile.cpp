
#include "cs_accum.h"
#include "sim_param.h"
#include <math.h>
#include "soil/chemicals_profile.h"
#include "soil/soil_base.h"
#include "soil/hydrology.h"
#include "soil/nitrogen_common.h"
#include "soil/infiltration.h"
#include "soil/chemical_profile.h"
#if ((CROPSYST_VERSION==4) && (!REACCH_VERSION))
#  include "cs_report_V4.h"
#endif
#include "watertab.h"
#include "soil/salinity_profile.h"
#include "soil/temperature_profile.h"
#include "soil/chemical_mass_profile.h"
#include "organic_matter/OM_residues_profile_abstract.h"

#include "options.h"
#include "CS_suite/observation/CS_inspector.h"
#include "csvc.h"
#define CSVC_UNKNOWN 0


extern bool quick_and_dirty_disable_chem_balance_when_watertable;
//______________________________________________________________________________
Soil_chemicals_profile::Soil_chemicals_profile
(const Soil_base                    &_soil                                       //020527
,const Soil_layers_interface        &_soil_layers                                //061004
,const Soil_temperature_interface   &_soil_temperature                           //020527
)
:Soil_nitrogen_common(*(_soil.ref_structure()))
,trans_layers(MAX_soil_layers) // actually set below
,soil(_soil)                                                                    //020527
,soil_layers(_soil_layers)                                                       //061004
,soil_temperature(_soil_temperature)                                             //020527
#ifdef NITROGEN
,NH4 ( 0)
,NO3 ( 0)
#endif
#ifdef SALINITY
,salinity_dSm(0)                                                                 //051201
#endif
#ifdef PHOSPHORUS
   float64 phosphorus;                                                           //110801
#endif
#ifdef NITROGEN
,ACC_NH4_released_to_atmosphere(0)
#endif
,chemical_profiles()                                                             //980731
#if (CROPSYST_VERSION == 4)
,max_transform_depth(0.5)                                                        //020620
#endif
,enable_denitrification_with_CO2(false)                                          //080818
{
#ifdef NITROGEN
   clear_layer_array64(total_N_E);
   clear_layer_array64(denitrification_N_E_output);
   clear_layer_array64(nitrification_N_E_output);
   clear_layer_array64(mineralization_N_E_output);
   clear_layer_array64(NO3_N_E_output);
   clear_layer_array64(NH4_N_E_output);
   clear_layer_array64(carbon_E);
#endif
}
//_1998-07-24______________________________________________________constructor_/
#if (DIRECTED_IRRIGATION==2)
Soil_chemicals_profile::Soil_chemicals_profile
(const Soil_chemicals_profile &copy_from
,float32 fraction)
: Soil_nitrogen_common(copy_from,fraction)

/* Need to finish initialization

#ifdef NITROGEN
, NH4(copy_from.NH4 ? NH4->copy(fraction) : 0)
, NO3(copy_from.NO3 ? NO3->copy(fraction) : 0)
#endif


   #ifdef SALINITY
   Soil_salt    *salinity_dSm;   bool owns_salinity;                             //051118
   #endif
#ifdef PHOSPHORUS
   float64 phosphorus;                                                           //110801
      // Not currently distributed by layer because
      // I dont know uptake dynamics.
   //NYI soil_layer_array64(phosphorus);
#endif

 public:
*/
, soilX(copy_from.soilX)
, soil_layers(copy_from.soil_layers)
, soil_temperature(copy_from.soil_temperature)
/*
   bool enable_denitrification_with_CO2;                                         //080818
#ifdef NITROGEN
   float64 ACC_NH4_released_to_atmosphere; // elemental N from NH4 from manure decomposition may be lost to the atmosphere.
#endif
   #if (CROPSYST_VERSION==4)
   float64 max_transform_depth;
   #endif

 public: // so soil profile spreadsheet can see it.
   nat8 trans_layers;
#ifdef NITROGEN
   //130930 Note that layer index 0 is reserved for the profile value
   // (sum of the layers)
   soil_layer_array64(denitrification_N_E_output); // N elemental output only
   soil_layer_array64(nitrification_N_E_output); // N elemental output only
   soil_layer_array64(mineralization_N_E_output); // N elemental output only
   soil_layer_array64(NO3_N_E_output); // N elemental output only
   soil_layer_array64(NH4_N_E_output); // N elemental output only
   soil_layer_array64(total_N_E);
#endif
//    NO3 + NH4 (elemental N) in each layer.
//    This is used for output only
 public:
   NITRO soil_layer_array64(carbon_E);                                           //040206

*/

{

assert(false); // need to finish copy construction
}
#endif
//_2014-06-10_________________________________________________copy_constructor_/
bool  Soil_chemicals_profile::initialize()
{  bool inited = true;
   trans_layers =
      #if (CROPSYST_VERSION == 4)
      !enable_denitrification_with_CO2
      ? soil_layers.get_layer_at_depth_or_last_layer(max_transform_depth/*,true*/) :
      #endif
      soil_layers.get_number_layers();
   // organic matter must preceed pot_mineralizable_N initialization
   #ifdef SALINITY
   if (salinity_dSm) inited &= salinity_dSm->initialize();                                 //051118
   #endif
   #ifdef NITROGEN
   for (int layer = 0 ; layer <= MAX_soil_layers ; layer++)                      //130930 needed to clear layer 0
   {  //130930 denitrified_NO3_M          [layer] = 0.0;
      denitrification_N_E_output [layer] = 0.0;
      nitrification_N_E_output   [layer] = 0.0;
      mineralization_N_E_output  [layer] = 0.0;
      NO3_N_E_output             [layer] = 0.0;
      NH4_N_E_output             [layer] = 0.0;
   }
   #endif
   return inited;
}
//_2009-10-29___________________________________________________________________
#ifdef NITROGEN
bool Soil_chemicals_profile::enable_nitrogen
(bool                               _enable_denitrification_with_CO2             //060508
,Infiltration_model                 infiltration_model                           //041116
,Soil_abiotic_environment_profile  *soil_abiotic_environment_profile             //060510
#if (CROPSYST_VERSION==4)
, float64                          _max_transform_depth
, float64                           adjust_denitrify      // 081013 Using the same variable for V4.1 and latest model
, float64                           adjust_nitrify_V4_1
#endif
, const CropSyst::Denitrification_parameters &denitrification_parameters         //150824
, const float64                   &_ref_water_flux_in_m                          //150925
, soil_horizon_array32             (horizon_N_NO3)
, soil_horizon_array32             (horizon_N_NH4)
, Water_table_curve                *NO3_water_table_curve // may be 0 if no water table consideration 080213
, Water_table_curve                *NH4_water_table_curve // may be 0 if no water table consideration 080213
, const CORN::date32               &today_)
{  enable_denitrification_with_CO2 = _enable_denitrification_with_CO2;           //020620
   if ((infiltration_model == CASCADE_DAILY_INFILTRATION) && _enable_denitrification_with_CO2)
   {
      enable_denitrification_with_CO2 = false;
      std::cout << "Denitrification using CO2 respiration is not available for daily cascade infiltration model. " << std::endl
         << "The nitrogen model should not be used with daily cascade infiltration because WC is never above field capacity."  << std::endl;

      // In version 5 we actually want to disable N model completely

   }
   #if (CROPSYST_VERSION==4)
   max_transform_depth = _max_transform_depth;                                   //020620
   trans_layers =  enable_denitrification_with_CO2                               //020620
      ? soil_layers.get_number_layers()
      : soil_layers.get_layer_at_depth_or_last_layer(max_transform_depth/*,true*/);
   #else
   trans_layers = soil_layers.get_number_layers();
   #endif
   soil_layer_array64(layer_horizon_N_NO3); clear_layer_array64(layer_horizon_N_NO3);  //051120
   #ifndef MICROBASIN_VERSION
   soil.distribute_amount(horizon_N_NO3,layer_horizon_N_NO3);                    //070607
   #else
   copy_layer_array32_to_array64(layer_horizon_N_NO3,horizon_N_NO3);             //150814LML need talk with Roger
   #endif

//011127x We now always create the N budget reporters if we have any report variables
// because the N budget reportes also contain accumulators used for the normal
// nitrogen output vairables.
#ifdef XLS_OUTPUT
   bool DLY_N_budgets = true; // DLY_report;                            //011127
   bool YLY_N_budgets = true; // YLY_report;                            //011127
   bool GS_N_budgets =  true; // GS_report;                             //030516
   bool FLW_N_budgets = true; // FLW_report;                            //011127
#endif
   #if (CROPSYST_VERSION==4)
   if (enable_denitrification_with_CO2 && soil_abiotic_environment_profile)
   #endif
      NO3 = new NO3_with_CO2_Profile
         (today_                                                                 //170425_170425
         ,denitrification_parameters                                             //150824
          #if (CROPSYST_VERSION==4)
         ,adjust_denitrify
         #endif
         ,layer_horizon_N_NO3  // init_chem_profile->chemical,
         ,*(soil.ref_layers())                                                   //150925
         ,*(soil.ref_hydrology())                                                //160412_150925
         ,*(soil.ref_hydraulic_properties())                                     //160412_150925
         ,*(soil.ref_structure())                                                //150925
         ,infiltration_model                                                     //080117
         ,_ref_water_flux_in_m                                                   //150925
         ,soil_abiotic_environment_profile                                       //060510
         ,NO3_water_table_curve);
   #if (CROPSYST_VERSION==4)
   else
      NO3 = new NO3_Profile
         (today_                                                                 //170525_170426
         ,adjust_denitrify    // init_chem_profile->get_adjustment(),  WARNING check if this is indeed denitrify 981211
         ,layer_horizon_N_NO3  // init_chem_profile->chemical,
         ,*(soil.ref_layers())                                                   //150925
         ,*(soil.ref_hydrology())                                                //160412_150925
         ,*(soil.ref_hydraulic_properties())                                     //160412_150925
         ,*(soil.ref_structure())                                                //150925
         ,infiltration_model                                                     //080117
         ,NO3_water_table_curve);
   #endif
   NO3->instanciate_accumulators();                                              //111207
   chemical_profiles.append(NO3);
   // NH4 instanciation must follow NO3 because the new transformation needs to know the NO3
   soil_layer_array64(layer_horizon_N_NH4);                                      //070607
   #ifndef MICROBASIN_VERSION
   soil.distribute_amount(horizon_N_NH4,layer_horizon_N_NH4);                    //070607
   #else
   copy_layer_array32_to_array64(layer_horizon_N_NH4,horizon_N_NH4);             //150814LML need talk with Roger
   #endif

//060510       NYI actually will want to pass a separate bool enable_nitrification_with_pH for this if statement
   #if (CROPSYST_VERSION==4)
   if (enable_denitrification_with_CO2 && soil_abiotic_environment_profile)
   {
   #endif
      soil_layer_array64  (pH); clear_layer_array64(pH);
      for (nat8 lyr = 1; lyr <= soil_layers.get_number_layers(); lyr++)
      {  nat8 horizon = soil_layers.get_horizon_at_layer(lyr);
         pH[lyr] = soil.get_pH(horizon);
      }
      NH4 = new NH4_Profile_with_pH
      (today_                                                                    //170425
       #if (CROPSYST_VERSION==4)
       ,adjust_nitrify_V4_1
       #endif
       ,layer_horizon_N_NH4
      //#ifndef OLD_N_XFER
      //,*NO3                                                                       //170502
      //#endif
         ,*(soil.ref_layers())                                                   //150925
         ,*(soil.ref_hydrology())                                                //160412_150925
         ,*(soil.ref_hydraulic_properties())                                     //160412_150925
         ,*(soil.ref_structure())                                                //150925
      ,infiltration_model                                                        //080117
      ,soil_abiotic_environment_profile                                          //060510
      ,*NO3                                                                       //170502
      ,pH
      ,NH4_water_table_curve // 0802134
      ,3.5   // pH_min
      ,6.5); // pH_max
   #if (CROPSYST_VERSION==4)
   } else
      NH4 = new NH4_Profile
      (today_                                                                    //170528
      ,adjust_nitrify_V4_1                                                       //981211
      ,layer_horizon_N_NH4
      #ifndef OLD_N_XFER
      ,*NO3
      #endif
         ,*(soil.ref_layers())                                                   //150925
         ,*(soil.ref_hydrology())                                                //160412_150925
         ,*(soil.ref_hydraulic_properties())                                     //160412_150925
         ,*(soil.ref_structure())                                                //160412_150925
      ,infiltration_model                                                        //080117
      ,NH4_water_table_curve    );                                               //080213
   #endif
   NH4->instanciate_accumulators();                                              //111207
   // NH4 must be appended after NO3 (NO3 transformation must come before NH4 because NH4 needs NO3 at the beginning of the day (To be compatible with VB version) 060510
   chemical_profiles.append(NH4);
   return NH4 && NO3;                                                            //020620
}
//_2002-06-20___________________________________________________________________
#endif
#ifdef PHOSPHORUS
float32 Soil_chemicals_profile::know_phosphorus_in_profile(float32 phosphorus_in_profile) cognition_
{
   phosphorus = phosphorus_in_profile;
   return phosphorus;
}
/*NYI
bool Soil_chemicals_profile::enable_phosphorus
(  soil_horizon_array32           (horizon_P))
{
   soil.distribute_amount(horizon_P,phosphorus);
}
*/
//_2011-08-01___________________________________________________________________
#endif
#ifdef SALINITY
bool Soil_chemicals_profile::set_salinity(Soil_salt_interface *salinity_dSm_,bool keep_it)
{
   // Normally this is only called one time at the beginning of the simulation.
   // To leave open the option of changing the salinity model in mid run
   // we should delete the current profile (if any)
   if (salinity_dSm )
   {  if (owns_salinity)
           chemical_profiles.remove(salinity_dSm->salinity_profile); // remove checks if salinity is 0 051120
      else chemical_profiles.detach(salinity_dSm->salinity_profile); // remove checks if salinity is 0
   }
   salinity_dSm = dynamic_cast<Soil_salt *>(salinity_dSm_);
   if (keep_it) owns_salinity=true;                                              //051120
   if (salinity_dSm) // could be 0 if clearing
   {
      salinity_dSm->salinity_profile->instanciate_accumulators();                //111207
      chemical_profiles.append(salinity_dSm->salinity_profile);                  //051118
         // salinity profile is relinquished to chemical_profiles
   }
   return true;
}
//_2005-11-20___________________________________________________________________
const       Soil_salt_interface *Soil_chemicals_profile::ref_salinity()    const { return salinity_dSm; }  //160412_051120
modifiable_ Soil_salt_interface *Soil_chemicals_profile::mod_salinity() modification_ { return salinity_dSm; } //160412_051120
#endif
//______________________________________________________________________________
#ifdef PESTICIDE
void Soil_chemicals_profile::enable_pesticides
(Bidirectional_list /*180101 Association_list*/ &initial_chemical_profiles
#ifdef WATER_TABLE
, const char *water_table_filename
, const CORN::Date &start_date
, const CORN::Date &end_date
#endif
)
{
   chemical_uptake_profile_class *chem_profile = 0;
   chemical_kinds kind;
   pesticide_profile_class *pest_profile = 0;
   for ( initial_chemical_profile *init_chem_profile = (initial_chemical_profile *)initial_chemical_profiles.move_to_head()
       ; init_chem_profile
       ; init_chem_profile = (initial_chemical_profile *)initial_chemical_profiles.move_to_next())
      if (init_chem_profile->Xenabled && (run_chemical))
      {  {     Water_table_curve *pesticide_concentration_curve = new Water_table_curve(water_table_filename,init_chem_profile->name.c_str(),start_date,end_date,init_chem_profile->get_water_table_conc());
               kind = CHEM_PESTICIDE;
               pest_profile = new pesticide_profile_class
                 (init_chem_profile->name,
                  init_chem_profile->get_adjustment(),                           //981211
                  init_chem_profile->chemical, get_divisions(),
                  get_num_layers(),get_in_layer_of()
                  ,pesticide_concentration_curve);                               //000504
               chem_profile = pest_profile;
         }
         {  switch (kind)
            { default : //PESTICIDE :
                 if (run_chemical )
                 {
#ifdef XLS_OUTPUT
                        chem_profile->report_DLY = DLY_report && DLY_report->pesticide_budgets;
                        chem_profile->report_YLY = YLY_report && YLY_report->pesticide_budgets;
                        chem_profile->report_HRV = HRV_report && HRV_report->pesticide_budgets;
                        chem_profile->report_FLW = FLW_report && FLW_report->pesticide_budgets;
#endif
                 } else
                 { delete chem_profile;
                   chem_profile = 0;
                 }
              break;
            }
         }
         if (chem_profile)
            chemical_profiles.append(chem_profile);
     }
}
#endif
//_1998-07-03___________________________________________________________________
void Soil_chemicals_profile::chemical_balances()
{

   FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)     //030709
   {  nat8 num_layers_eff = soil_layers.get_number_uninundated_layers();
      // needs to be effectiove layer becase otherwise if watertable there is balance error (salt)
//050428 This temporarily disabled the balance in the case of watertable, it is giving an error
//I dont have time to fix it.  IT NEEDS TO BE FIXED.
if (quick_and_dirty_disable_chem_balance_when_watertable) return;                //150424
      // N chemicals already handled by nitrogen balance
      float64 bal = chem_profile->balance(num_layers_eff);
      if ((! ((chem_profile->chemical_type==CT_NO3) || (chem_profile->chemical_type==CT_NH4))) && (fabs(bal) > 1E-07))
         std::cerr << '!' << chem_profile->name << " BALANCE!" << bal;
   } FOR_EACH_END(each_profile)                                                  //030709
}
//______________________________________________________________________________
void Soil_chemicals_profile::chemical_transformations
   (Seconds preferred_transformation_timestep) // This option is because the hourly moisture function calculation can not be resolved with daily infiltration
{  nat8 layer ;
   soil_layer_array64(transformed_to_chem); clear_layer_array64(transformed_to_chem);
   FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)     //030709
   {  chem_profile->setup_for_transformations();                                 //060608
      if (chem_profile->name != LABEL_salt) {
      //160321LML added MICROBASIN_VERSION condition in the following macro
      #if (defined(VIC_CROPSYST_VERSION) || defined(MICROBASIN_VERSION)) && defined(NITROGEN)
        if(chem_profile->chemical_type == CT_NO3)       denitrification_N_E_output[0] = 0; //150727LML
        else if(chem_profile->chemical_type == CT_NH4)  nitrification_N_E_output[0]   = 0; //150727LML
        else if(chem_profile->chemical_type == CT_PMN)  mineralization_N_E_output[0]  = 0; //160322LML
      #endif
      for (layer = 1; layer <= trans_layers; layer++)
      {  transformed_to_chem[layer] = 0.0;
         float64 liquid_WC          = soil.ref_hydrology()           ->get_liquid_water_content_volumetric(layer);                 //160412_040714
            // RLN 070813 Not sure if liquid or total (probably doesn't matter since temperature would shut down)
         float64 saturation_WC      = soil.ref_hydraulic_properties()->get_saturation_water_content_volumetric(layer,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822);  //160412_040714
         float64 ref_WC             = soil.ref_hydrology()           ->get_reference_water_content(layer);                         //160412_140610
         float64 bulk_density_g_cm3 = soil.ref_structure()           ->get_bulk_density_g_cm3(layer);                             //040714
         float64 temperature        = soil_temperature.get_temperature(layer);                                    //040714
         chem_profile->transformation                                                                             //060510
            (layer,liquid_WC,saturation_WC,ref_WC,temperature,bulk_density_g_cm3
            ,preferred_transformation_timestep
            #ifdef OLD_N_XFER
            ,transformed_to_chem[layer]
            #endif
            );
         chem_profile->mass->commit_diffs();                                     //120731
#ifdef NITROGEN
         switch (chem_profile->chemical_type)
         {
          case CT_NO3 :
            denitrification_N_E_output[layer]
               #ifdef OLD_N_XFER
               = NO3->chem_to_element_factor/*170330RLN element_to_chem_factor*/  * transformed_to_chem[layer]; // need to  check

denitrification_N_E_output[layer] = NO3->denitrified_N_output.get(layer);                           //170502

               #else
               = NO3->denitrified_N_output.get(layer);                           //170502
               #endif
            denitrification_N_E_output[0] += denitrification_N_E_output[layer];  //130930
            //std::cout<<"layer:"<<(int)layer
            //      <<"\ttransformed_to_chem[layer]:"<<transformed_to_chem[layer]
            //      <<"\tdenitrification_N_E_output[0]:"<<denitrification_N_E_output[0]
            //      <<std::endl;
               //index 0 is the sum of the layers for the profile value
          break;
          case CT_NH4 :
            #ifdef OLD_N_XFER
            // I think something is wrong here should already be handled below

            NO3->transformed_from_M[layer]
               = NO3->element_to_chem_factor*(chem_profile->chem_to_element_factor*(transformed_to_chem[layer]));

            nitrification_N_E_output[layer] = chem_profile->chem_to_element_factor*(transformed_to_chem[layer]); //041002
            nitrification_N_E_output[0] += nitrification_N_E_output[layer];      //130930
               //index 0 is the sum of the layers for the profile value
            #else
            nitrification_N_E_output[layer] =NH4->nitrified_N_output.get(layer); //170502
            #endif
          break;
          // Organic matter now puts N directly into the soil
          // PMN only exists in the V4_1 since organic matter pool submodel, in the organic matter pools submodel, this case never occurs
          case CT_PMN :
            #ifdef OLD_N_XFER
            NH4->transformed_from_M[layer] =
            NH4->element_to_chem_factor * (transformed_to_chem[layer]) ;
            mineralization_N_E_output[layer] =(transformed_to_chem[layer]);
            #else
            mineralization_N_E_output[layer] = chem_profile->transformed_E_output.get(layer);//170502
            #endif
            mineralization_N_E_output[0] += mineralization_N_E_output[layer];    //130930
          break;
          default : break;                                                       //170217
         } // switch (chem_profile->chemical_type)
#endif
     // the wrong class virtual methods are being called for transformation.
      }
     }                                                                           //150727LML
  } FOR_EACH_END(each_profile)
  //  This may need to be move some where else in the future if we
  //  want to use transformed_from_M to for other input such as
  //   mineralization of residues (currently we are mineralizing
  //  directly to amount_M).
  #ifdef OLD_N_XFER
   FOR_EACH_IN(chem_profile_to_transform,Chemical_profile,chemical_profiles,each_profile) //030709
   {  if (chem_profile_to_transform->chemical_type != CT_SALT)
      {  for (nat8 layer_trans = 1; layer_trans <= trans_layers ; layer_trans++)
         {  float64 chem_transformed_from = chem_profile_to_transform->transformed_from_M[layer_trans];
            chem_profile_to_transform->mass->inc_layer(layer_trans,chem_transformed_from); //120730
         }
         chem_profile_to_transform->mass->commit_diffs();                        //120730
      }
   } FOR_EACH_END(each_profile)
   #endif
}
//______________________________________________________________________________
bool Soil_chemicals_profile::reinitialize_at_end_season()
{  bool inited = true;
   FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)     //030709
   {  inited &= chem_profile->reinitialize_at_end_season();                      //980730
   } FOR_EACH_END(each_profile)
   return inited;                                                                //131217
}
//_2012-07-04__1996-09-02_______________________________________________________
void Soil_chemicals_profile::chemical_transport_and_exchange
(Infiltration_model    infiltration_model
,nat8                 num_layers_or_nodes_eff           // will be number of nodes for F.D.
,nat8                  number_of_real_plus_extended_nodes // only for F.D.
,Seconds               at_time
,Seconds               duration                          // seconds of duration
,soil_layer_array64   (old_liquid_water_content)         // node based for F.D. otherwise layer base
,soil_layer_array64   (new_liquid_water_content)         // node based for F.D. otherwise layer base
,float64               water_entering_soil               // total water entering (irrig + precip)
,soil_layer_array64   (water_flow)                       // node based for F.D. otherwise layer base
,float64               deferment_fraction
,bool                  override_drainage_depth
,nat8                 leaching_layer
,bool water_table_conditions)
{  FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)     //030709
   {  if (chem_profile->chemical_type != CT_PMN)
      {

//std::cout << "chem:" << chem_profile->name << std::endl;

#ifdef SPLIT_APPLICATION
//080307 becomming obsolete
         chem_profile->defer_surface_mass_infiltration(at_time,duration,deferment_fraction); //071016
#endif
        #ifdef VIC_CROPSYST_VERSION
        chem_profile->transport_unidirectional/*170504LML _4_11_03*/
        ( num_layers_or_nodes_eff
         , water_flow
         ,old_liquid_water_content
         ,new_liquid_water_content
         ,water_entering_soil
         ,at_time
         ,duration // seconds of duration
          ,override_drainage_depth,leaching_layer);
        #else
         switch (infiltration_model)                                             //080114
         { case NO_INFILTRATION : /* if no infiltration then no transport*/  break;
           case CASCADE_DAILY_INFILTRATION : case CASCADE_HOURLY_INFILTRATION:
            chem_profile->transport_unidirectional
               ( num_layers_or_nodes_eff
               , water_flow
               ,old_liquid_water_content
               ,new_liquid_water_content
               ,water_entering_soil
               ,at_time
               ,duration // seconds of duration
               ,override_drainage_depth,leaching_layer);
            break;
            #ifdef FINITE_DIFF
            case FINITE_DIFFERENCE_INFILTRATION :
            chem_profile->transport_bidirectional_by_node
               ( num_layers_or_nodes_eff
               , number_of_real_plus_extended_nodes
               , water_table_conditions
               , water_flow
               ,old_liquid_water_content
               ,new_liquid_water_content
               ,water_entering_soil
               ,at_time
               ,duration // seconds of duration
               ,override_drainage_depth,leaching_layer
               );
            // Exchange is built into transport
            break;
            #endif
            default: break;                                                      //170217
         } // switch(infiltration_model)
         chem_profile->update_balance_pending_infiltration();
         #endif
         chem_profile->update_concentration_for_output(num_layers_or_nodes_eff); // currently only relevent for Salinity
      }
   } FOR_EACH_END(each_profile)
// Note the following is only for output
#ifdef NITROGEN
   if (NO3 && NH4)
   {
      total_N_E[0]      = 0.0;                                                   //131001
      NO3_N_E_output[0] = 0.0;                                                   //131001
      NH4_N_E_output[0] = 0.0;                                                   //131001
      for (nat8 layer = 1; layer <= soil_layers.get_number_layers(); layer++)
      {  total_N_E[layer]      = NO3->chem_to_element_factor * (NO3->mass->get_layer(layer))
                               + NH4->chem_to_element_factor * (NH4->mass->get_layer(layer));
         NO3_N_E_output[layer] = NO3->chem_to_element_factor * (NO3->mass->get_layer(layer));
         NH4_N_E_output[layer] = NH4->chem_to_element_factor * (NH4->mass->get_layer(layer));
       // Sum the profile values (stored in array index 0)                       130930
         total_N_E[0]      += total_N_E[layer];                                  //131001
         NO3_N_E_output[0] += NO3_N_E_output[layer];                             //131001
         NH4_N_E_output[0] += NH4_N_E_output[layer];                             //131001
      }
   }
#endif
}
//_1998-07-24_________________________________chemical_transport_and_exchange__/
bool Soil_chemicals_profile::start_day()                           modification_ //151113_151006_150925
{  bool started = true;                                                          //151113
   FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)
   {  started &= chem_profile->start_day();                                      //151113_151006_150925
   } FOR_EACH_END(each_profile)
   return started;
}
//_2007-10-15___________________________________________________________________
bool Soil_chemicals_profile::end_day()                             modification_
{
   reported_daily_N_leached
      = (NH4 ? (NH4->chem_to_element_factor * NH4->reported_leached_molecular)
             : 0.0)
      + (NO3 ? (NO3->chem_to_element_factor * NO3->reported_leached_molecular)
             : 0.0);
   return true;
}
//_2013-09-11__________________________________________________________________/
#ifdef WATERTABLE
void Soil_chemicals_profile::adjust_water_table_concentration
(nat8 number_FD_soluation_layers
,nat8 number_of_real_plus_extended_layers)
{  FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)
   {  chem_profile->adjust_water_table_concentration
         (number_FD_soluation_layers,number_of_real_plus_extended_layers);
   } FOR_EACH_END(each_profile)
}
#endif
//_2008-02-18____2007-10-15_____________________________________________________
bool Soil_chemicals_profile::reinitialize()
{
   #if (CROPSYST_VERSION == 4)
   float64 depth_at_last_layer = soil_layers.get_depth_profile_m();
   if (max_transform_depth > depth_at_last_layer)
      max_transform_depth = depth_at_last_layer;
   trans_layers = enable_denitrification_with_CO2
      ? soil_layers.get_number_layers()
      : soil_layers.get_layer_at_depth_or_last_layer(max_transform_depth) ;
   #else
   trans_layers = soil_layers.get_number_layers();
   #endif
   return true;
}
//_2008-08-18___1998-07-31______________________________________________________
bool Soil_chemicals_profile::reinitialize_for_crop()
{  bool reinited = true;
   FOR_EACH_IN(chem_profile,Chemical_profile,chemical_profiles,each_profile)
   { reinited &= chem_profile->reinitialize_for_sowing_or_restart();
   } FOR_EACH_END(each_profile)
   return reinited;
}
//_1998-07-24___________________________________________________________________
void Soil_chemicals_profile::commit_diffs()                        modification_
{
   #ifdef NITROGEN
   if (NH4 && NH4->mass) NH4->mass->commit_diffs();
   if (NO3 && NO3->mass) NO3->mass->commit_diffs();
   #endif
   #ifdef SALINITY
   if (salinity_dSm && salinity_dSm->salinity_profile->mass) salinity_dSm->salinity_profile->mass->commit_diffs();
   #endif
}
//_2012-07-30_____________________________________________________commit_diffs_/
#ifdef NITROGEN
//______________________________________________________________________________
float64 Soil_chemicals_profile::get_NH4_N_mass_mineralized_from_PMN_kg_m2_profile() const
{
   #ifdef OLD_N_XFER
   return
   NH4
   ? NH4->chem_to_element_factor*(NH4->profile_transformed_from_M)
   : 0.0;
   #else
   assert(0);

   // I think this is obsolete,  if we get here need to implement this
   // return the mineralized mass

   return 0.0;
   #endif
}
//_2006-01-23___________________________________________________________________
float64 Soil_chemicals_profile::get_NH4_N_mass_mineralized_from_PMN_kg_m2(nat8 layer) const
{
   #ifdef OLD_N_XFER
   return NH4
   ? NH4->chem_to_element_factor*(NH4->transformed_from_M[layer])
   : 0.0;
   #else
   assert(0);

   // I think this is obsolete,  if we get here need to implement this
   // return the mineralized mass

   return 0.0;
   #endif
}
//_2006-01-23___________________________________________________________________
float64 Soil_chemicals_profile::get_elemental_N_from_NO3(nat8 layer) const
{  return NO3 ? NO3->get_N_mass(layer) : 0.0;
}
//_2006-05-03___________________________________________________________________
float64 Soil_chemicals_profile::get_elemental_N_from_NH4(nat8 layer) const
{  return NH4 ? NH4->get_N_mass(layer) : 0.0;
}
//_2006-05-03___________________________________________________________________
float64 Soil_chemicals_profile::set_NO3_N_mass_kg_m2(nat8 layer, float64 elemental_N)
{  float64 result_M = 0.0;
   if (NO3)
      result_M = NO3->mass->set_layer(layer,NO3->element_to_chem_factor * elemental_N);   //080116
   return result_M;
}
//_2003-11-22___________________________________________________________________
float64 Soil_chemicals_profile::set_NH4_N_mass_kg_m2(nat8 layer, float64 elemental_N)
{  float64 result_M = 0.0;
   if (NH4)
      result_M = NH4->mass->set_layer(layer,NH4->element_to_chem_factor * elemental_N);
   return result_M;
}
//_2003-11-22___________________________________________________________________
float64 Soil_chemicals_profile::get_NO3_molecular_mass_kg_m2  (nat8 layer)            const   { return NO3->mass->get_layer(layer);}                                           //040520
float64 Soil_chemicals_profile::get_NH4_molecular_mass_kg_m2  (nat8 layer)            const   { return NH4->mass->get_layer(layer);}                                           //040520
float64 Soil_chemicals_profile::get_NO3_N_mass_kg_m2          (nat8 layer)            const   { return convert_NO3_molecular_to_N_mass(NO3 ? NO3->mass->get_layer(layer) : 0.0);}          //040520
float64 Soil_chemicals_profile::get_NH4_N_mass_kg_m2          (nat8 layer)            const   { return convert_NH4_molecular_to_N_mass(NH4 ? NH4->mass->get_layer(layer) : 0.0);}          //040520
float64 Soil_chemicals_profile::add_NO3_molecular_mass        (nat8 layer,float64 NO3_mass_M) { return NO3->mass->inc_layer(layer,NO3_mass_M); }                               //120730_040520
float64 Soil_chemicals_profile::add_NH4_molecular_mass        (nat8 layer,float64 NH4_mass_M) { return NH4->mass->inc_layer(layer,NH4_mass_M); }                               //120730_040520
float64 Soil_chemicals_profile::subtract_NO3_molecular_mass   (nat8 layer,float64 NO3_mass_M) { return NO3->mass->dec_layer(layer,NO3_mass_M); }                               //120730_040520
float64 Soil_chemicals_profile::subtract_NH4_molecular_mass   (nat8 layer,float64 NH4_mass_M) { return NH4->mass->dec_layer(layer,NH4_mass_M); }                               //120730_040520
void Soil_chemicals_profile::NO3_dec_residue(float64 NO3_amount_change_M)  { NO3->dec_residue(NO3_amount_change_M); }                                                          //040521
void Soil_chemicals_profile::NH4_dec_residue(float64 NH4_amount_change_M)  { NH4->dec_residue(NH4_amount_change_M); }                                                          //040521
float64 Soil_chemicals_profile::get_NO3_molecular_mass_kg_m2(nat8 layer)  { return NO3->mass->get_layer(layer);}                                                               //060122
float64 Soil_chemicals_profile::get_NH4_molecular_mass_kg_m2(nat8 layer)  { return NH4->mass->get_layer(layer);}                                                               //060122
float64 Soil_chemicals_profile::set_NO3_molecular_mass_kg_m2(nat8 layer,float64 new_mass) { return NO3->mass->set_layer(layer,new_mass);}                                      //060122
float64 Soil_chemicals_profile::set_NH4_molecular_mass_kg_m2(nat8 layer,float64 new_mass) { return NH4->mass->set_layer(layer,new_mass);}                                      //060122
//______________________________________________________________________________
float64 Soil_chemicals_profile::uptake_N_mass_from_NO3
(nat8 layer, float64 requested_elemental_N_uptake_kg_m2)
{  // Attempts to removed the requested elemental_N from the NO3 pool.
   // Returns the actual elemental N uptaken from the pool.
   return NO3->uptake_elemental(layer,requested_elemental_N_uptake_kg_m2);
}
//_1998-07-30___________________________________________________________________
float64 Soil_chemicals_profile::uptake_N_mass_from_NH4
(nat8 layer, float64 requested_elemental_N_uptake_kg_m2)
{  // Attempts to removed the requested elemental_N from the NH4 pool.
   // Returns the actual elemental N uptaken from the pool.
   return NH4->uptake_elemental(layer,requested_elemental_N_uptake_kg_m2);
}
//_1998-07-30___________________________________________________________________
float64 Soil_chemicals_profile::sum_NO3_to_depth //  kg/m2
(float64 a_given_depth, bool elemental)                                    const
{  float64 sum_NO3_M // Molecular
   = NO3 ? NO3->mass->sum_to_depth(a_given_depth) : 0.0;                         //080117
   return elemental
   ? (NO3 ? (NO3->chem_to_element_factor * sum_NO3_M) : 0.0)
   : sum_NO3_M;
}
//_1999-02-08________________________________________________sum_NO3_to_depth__/
float64 Soil_chemicals_profile::sum_NH4_to_depth //  kg/m2
(float64 a_given_depth, bool elemental)                                    const
{  float64 sum_NH4_M // Molecular
   = NH4 ? NH4->mass->sum_to_depth(a_given_depth) : -9999;
   return elemental
   ? (NH4 ? NH4->chem_to_element_factor * sum_NH4_M : -9999)
   : sum_NH4_M;
}
//_2012-07-10________________________________________________sum_NH4_to_depth__/
float64 Soil_chemicals_profile::sum_N_to_depth  //  kg/m2
(float64 a_given_depth)                                                    const
{  return sum_NO3_to_depth(a_given_depth, true)
        + sum_NH4_to_depth(a_given_depth, true);
}
//_2017-06-30___________________________________________________sum_N_to_depth_/
bool Soil_chemicals_profile::is_below_critical_N
(float64 critical_N_kg_m2
,float64 sampling_depth)                                            affirmation_
{  bool is_critical = false;
   if (!CORN::is_approximately<float64>(critical_N_kg_m2,0.0))
   {  float64 N_sum = sum_N_to_depth(sampling_depth);
      is_critical = (N_sum < critical_N_kg_m2);
   } // else 0 values disable criticality check.
   return is_critical;
}
//_2017-06-30______________________________________________is_below_critical_N_/
#endif
RENDER_INSPECTORS_DEFINITION(Soil_chemicals_profile)
{
   //uses soil emanator
   inspectors.append(new CS::Inspector_scalar( reported_daily_N_leached      ,UC_kg_m2 ,*context,"leach/N/total"   ,value_statistic,CSVP_soil_N_leached/*171222 CSVC_soil_N_leached_time_step_sum*/));  // sum?
   /*NYI
   inspectors.append(new CS::Inspector_scalar( reported_daily_NO3_N_leached      ,UC_kg_m2 ,*context,"N_leached/NO3"           ,TS_VALUE,??CSVP_soil_NO3_N_leached));
   inspectors.append(new CS::Inspector_scalar( reported_daily_NH4_N_leached      ,UC_kg_m2 ,*context,"N_leached/NH4"           ,TS_VALUE,??CSVPC_soil_NH4_N_leached));
   */
   inspectors.append(new CS::Inspector_scalar(
      #ifdef OLD_N_XFER
      (denitrification_N_E_output[0])
      #else
      NO3->denitrified_N_output.ref_array_sum()                                 //170503
      #endif
      ,UC_kg_m2 ,*context,"denitrification/N"   ,value_statistic,CSVP_soil_N_denitrification /*171222 CSVC_soil_N_denitrification_time_step_sum*/));       // sum?
   // For start of period Not we will want initial and final for the period
   inspectors.append(new CS::Inspector_scalar(total_N_E[0]     ,UC_kg_m2,*context/*emanator*/ ,"N_total/profile"   ,value_statistic,CSVC_UNKNOWN));   //CSVP_soil_N_N_amount      // sum?
   inspectors.append(new CS::Inspector_scalar(NO3_N_E_output[0],UC_kg_m2,*context/*emanator*/ ,"N_NO3/profile"     ,value_statistic,CSVC_UNKNOWN));   //CSVP_soil_N_NO3_amount    // sum?
   inspectors.append(new CS::Inspector_scalar(NH4_N_E_output[0],UC_kg_m2,*context/*emanator*/ ,"N_NH4/profile"     ,value_statistic,CSVC_UNKNOWN));   //CSVP_soil_N_NH4_amount    // sum?
   if (NH4) NH4->render_inspectors(inspectors,context,"NH4");                    //171220
   if (NO3) NO3->render_inspectors(inspectors,context,"NO3");                    //171220
   return 0; // emanator;
}
//_2013-09-11___________________________________________________________________

// 060731 700 lines
// 070607 480

