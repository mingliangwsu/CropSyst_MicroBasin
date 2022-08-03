#include "ICASA/library/ICASA_common.h"
#include "ICASA/library/soil/ICASA_soil.h"
#include "CanSIS/NSDB/soil_layer_table.h"
#include "cs_suite/CS_suite_directory.h"
#include "corn/data_source/dbase_datasrc.h"


void Tsoil_convertor_form::handle_IBSNAT_import_button_onclick()
{
   if (ICASA_file_open->Execute())
   {

      //130225 Eventually moved this to soil convertor engine

      CORN::OS::File_name_logical ICASA_filename(ICASA_file_open->FileName.c_str()); //111025
      ICASA::File ICASA_file(ICASA_filename,"SOIL");
      ICASA_file.read();
      CORN_Directory_name_instance destination_dir(editdir_destination->Text.c_str());
      for (ICASA::Soil_unit *soil_unit = ICASA_file.pop_soil_unit()
          ;soil_unit
          ;soil_unit = ICASA_file.pop_soil_unit())
      {  for (ICASA::Soil_unit::Group *ICASA_soil = soil_unit->pop_group()
             ;ICASA_soil
             ;ICASA_soil = soil_unit->pop_group())
         {  Smart_soil_parameters cropsyst_soil;
            cropsyst_soil.description = ICASA_soil->description;
            cropsyst_soil.evaporative_layer_thickness_cascade = 0.05;
            cropsyst_soil.evaporative_layer_thickness_finite_difference = 0.05;
            // Properties
            // Not used by CS               int16    SLCM;    int16    &SCOM;      // Colour Munsell hue      Units?
            // ICASA only has one albedo so presuming wet and dry are the same
               cropsyst_soil.albedo_dry = cropsyst_soil.albedo_wet  =  ICASA_soil->properties.SLALB; // Albedo fraction
               // Not used by CS               float32  SLU1; // Evaporation limit cm
               // Not used by CS               float32  SLDR; // Drainage rate fraction day-1
            if (ICASA_soil->properties.SLRO != -99)
               cropsyst_soil.override_curve_number_16 = ICASA_soil->properties.SLRO; // Runoff curve number (Soil Conservation Service) -
               // Not used by CS               float32  SLNF; // Mineralisation factor 0-1 scale
            cropsyst_soil.SLPF_CropGro = ICASA_soil->properties.SLPF; // Photosynthesis factor 0-1 scale
               // Not used by CS               float32  SLDN; // Denitrification factor (0-1)
               // Not used by CS               Ustring  SMHB; // pH in buffer determination method
               // Not used by CS               Ustring  SMPX; // Phosphorus, extractable, determination method
               // Not used by CS               Ustring  SMKE; // Potassium determination method

               // The following are in some databases and used by some models
               // Not used by CS               int16       SLDP;       // Depth cm (of the entire profile?)  WISE:no ICASA:yes
               // I.e.  WISE,  ICASA
               // Not used by CS               Ustring     SOIL_CLASS;  // WISE:no ICASA:yes
               // Not used by CS               Ustring     SCS_FAMILY;   // Family, SCS system     WISE:yes  ICASA:NO
               // SCS_family may be deprecated replaced with SCS_CLASS and or SOIL_CLASS

               // Not used by CS               Ustring     SLSOURCE;   // Source    WISE:no ICASA:yes
               // Not used by CS                           Ustring     SLTX;       // Texture  WISE:no  ICASA:yes

               // SLTX is only a single soil texture description for the entire profile.

               // Not used by CS               Ustring     SLDESCRIP;   // Description or local classification  WISE:no ICASA:no
               // Not used by CS               Ustring     SCS_CLASS;  // Soil Conservation System clasification (text)  (WISE:NO ICASA:Yes

               cropsyst_soil.number_horizons = ICASA_soil->horizon_count;
               // Horizon
               float32 last_horizon_depth_cm=0.0;
               for (int h = 1; h <= ICASA_soil->horizon_count; h++)
               {
                  cropsyst_soil.horizon_thickness[h]        = cm_to_m(ICASA_soil->horizon[h].SLB - last_horizon_depth_cm);
                  last_horizon_depth_cm = ICASA_soil->horizon[h].SLB;
                  // Not used by CS                           int16    SLMH;                      // Master horizon -    (Not sure what this is often has value -99)
                  /*130127 obsolete
                  cropsyst_soil.vol_WC_at_1500[h] =
                  cropsyst_soil.vol_WC_at_33_32[h]   =
                  */
                  cropsyst_soil.horizon_permanent_wilt_point[h]   = ICASA_soil->horizon[h].SLLL;                      // Lower limit cm3 cm-3    (Permanent wilt point?)
                  cropsyst_soil.horizon_field_capacity[h]         = ICASA_soil->horizon[h].SLDUL;    // Soil water at drained upper limit (cm3/cm3)
                  cropsyst_soil.horizon_saturation_WC[h]             = ICASA_soil->horizon[h].SLSAT;    // Soil water at saturation (cm3/cm3)
                  // Not used by CS                 float32  SLRGF;   float32 &SRGF;    //  Root growth factor (0-1)
                  float32 SLSKS_cm_h = ICASA_soil->horizon[h].SLSKS;
                  float32 SLSKS_m_h =  cm_to_m(SLSKS_cm_h);
                  float32 SLSKS_m_d = m_per_hr_to_m_per_day(SLSKS_m_h);
                  cropsyst_soil.sat_hydraul_cond_m_d[h]              = SLSKS_m_d;// Saturated hydraulic conductivity,macropore (cm/h)
                  cropsyst_soil.horizon_bulk_density_g_cm3[h]        = ICASA_soil->horizon[h].SLBDM;      // Bulk density,moist (g/cm3)
                  // Warning I don't know if CropSyst bulk density is dry or wet basis

               // Not used by CS                 float32  SLOC;                      // Organic carbon %
                  cropsyst_soil.horizon_clay[h]                           = ICASA_soil->horizon[h].SLCL;  // Clay (<0.002 mm) %
                  cropsyst_soil.horizon_silt[h]                           = ICASA_soil->horizon[h].SLSI;                      // Silt (0.05 to 0.002 mm) %
                  cropsyst_soil.horizon_sand[h] = 100 - (cropsyst_soil.horizon_clay[h] + cropsyst_soil.horizon_silt[h] );
                  // Not used by CS                 float32  SLCF;                      // Coarse fraction (>2 mm) %   (often has value -99)
                  // Not used by CS                 float32  SLNI;                      // Total nitrogen %
                  cropsyst_soil.pH[h]                                = ICASA_soil->horizon[h].SLPHW;    // pH in water -
                  // Not used by CS                 float32  SLPHB;   float32  &SLHB;   // pH in buffer -
                  cropsyst_soil.cation_exchange_capacity[h]             = ICASA_soil->horizon[h].SLCEC;
                  // milliequivelents of cations per 100 grams soil this equal to cmol/kg (centimole of positive charge)

                  // The following are optional chemical properties.

                  // Not used by CS                 float32  SLPX; //Phosphorus, extractable mg kg-1
                  // Not used by CS                 float32  SLPT; //Phosphorus, total mg kg-l
                  // Not used by CS                 float32  SLPO; //Phosphorus, organic mg kg-1
                  // Not used by CS                 float32  SLCA; //CACO 3 content g kg-l
                  // Not used by CS                 float32  SLAL; //Aluminium
                  // Not used by CS                 float32  SLFE; //Iron
                  // Not used by CS                 float32  SLMN; //Manganese
                  // Not used by CS                 float32  SLBS; //Base saturation cmol kg-l
                  // Not used by CS                 float32  SLPA; //Phosphorus isotherm A mmol kg-l
                  // Not used by CS                 float32  SLPB; //Phosphorus isotherm B mmol kg-l
                  // Not used by CS                 float32  SLKE; //Potassium, exchangeable cmol kg-l
                  // Not used by CS                 float32  SLMG; //Magnesium cmol kg-l
                  // Not used by CS                 float32  SLNA; //Sodium cmol kg-l
                  // Not used by CS                 float32  SLSU; //Sulphur cmol kg-l
                  // Not used by CS                 float32  SLEC; //Electric conductivity seimen
                  cropsyst_soil.user[h] =
                            Soil_parameters::specified_texture
                          | Soil_parameters::specified_FC
                          | Soil_parameters::specified_PWP
                          | Soil_parameters::specified_bulk_density
                          // Soil_parameters::specified_vol_WC_1500
                          // Soil_parameters::specified_vol_WC_33
                          // Soil_parameters::specified_sat_hydraul_cond
                          // Soil_parameters::Saturation is specified
                          // Soil_parameters::specified_air_entry_pot
                       // Soil_parameters::specified_soil_B
                       | Soil_parameters::specified_sand
                       | Soil_parameters::specified_clay
                       | Soil_parameters::specified_silt;
               cropsyst_soil.layer_texture_hydraulics[h]->recompute_every_thing();
               // Make sure these are what were in the ICASA file (incase they are overriden by recompute_every_thing()
               cropsyst_soil.horizon_permanent_wilt_point[h]   = ICASA_soil->horizon[h].SLLL;                      // Lower limit cm3 cm-3    (Permanent wilt point?)
               cropsyst_soil.horizon_field_capacity[h]         = ICASA_soil->horizon[h].SLDUL;    // Soil water at drained upper limit (cm3/cm3)
               cropsyst_soil.horizon_saturation_WC[h]                     = ICASA_soil->horizon[h].SLSAT;    // Soil water at saturation (cm3/cm3)
            };
            #ifdef USE_OS_FS
            CORN::OS::File_name_logical soil_filename(destination_dir,ICASA_soil->identifier.c_str(),"SIL");
            #else
            CORN::File_name soil_filename(ICASA_soil->identifier.c_str(),"SIL");
            #endif
            CORN::VV_File soil_file(soil_filename.c_str());
            cropsyst_soil.save_only_specified_layers = true;                     //130224
            soil_file.set(cropsyst_soil);
         };
      }; // for soil_unit
   };
};
//______________________________________________________________________________
void Tsoil_convertor_form::handle_explore_button_onclick()
{
   std::string explorer_command("\"");
   CORN_File_name_instance soil_convertor_filename(ParamStr(0).c_str());
   CS::Suite_Directory CS_suite_directory(soil_convertor_filename);
   CORN_Directory_name_instance destination_directory(destitation_directory_edit->Text.c_str()); //111025
   explorer_command.append(CS_suite_directory.CS_explorer_executable().c_str());
   explorer_command.append("\" \"");
   explorer_command.append(destination_directory.c_str());
   explorer_command.append("\"");
   WinExec(explorer_command.c_str(),SW_NORMAL);
};
//______________________________________________________________________________
void Tsoil_convertor_form::handle_CanSIS_NSDB_button_onclick()
{
   button_CanSIS_NSDB_convert->Caption = "Working";
   CORN_File_name_instance soil_layer_table_filename(filedit_CanSIS_NSDB->Text.c_str());
   CORN::Data_source_dBase soil_layer_table(soil_layer_table_filename.c_str(),std::ios_base::in,0);


      //130225 Eventually moved this to soil convertor engine


   Smart_soil_parameters *cropsyst_soil = 0;
   std::string prev_soil_layer_type;
   for (bool valid = soil_layer_table.goto_first(); valid
       ;valid = soil_layer_table.goto_next())
   {
      CanSIS::NSDB::Soil_layer_record  curr_soil_layer;
      soil_layer_table.get(curr_soil_layer);
      if (curr_soil_layer.SOILTYPE_OR_ID != prev_soil_layer_type)
      {
         if (cropsyst_soil)
         {
            CORN_Directory_name_instance dest_dir(editdir_destination->Text.c_str());
            CORN::OS::File_name_logical soil_filename(dest_dir,prev_soil_layer_type.c_str(),"CS_soil");
            CORN::VV_File soil_file(soil_filename.c_str());
            cropsyst_soil->save_only_specified_layers = true;                    //130224
            soil_file.set(*cropsyst_soil);
            delete cropsyst_soil; cropsyst_soil = 0;
         }
         cropsyst_soil = new Smart_soil_parameters ;
      }

      nat8 h = curr_soil_layer.LAYER_NO;
      cropsyst_soil->number_horizons = std::max<int16>(cropsyst_soil->number_horizons,h);

      // N/A SOIL_ID
      // N/A PROVINCE
      // N/A SOIL_CODE
      // N/A MODIFIER
      // N/A PROFILE

      // N/A HZN_LIT
      // N/A HZN_MAS
      // N/A HZN_SUF
      // N/A HZN_MOD

      cropsyst_soil->horizon_thickness[h] = cm_to_m(curr_soil_layer.UDEPTH - curr_soil_layer.LDEPTH);
      if (curr_soil_layer.KP1500 > 0)
      {
         cropsyst_soil->horizon_permanent_wilt_point[h] = curr_soil_layer.KP1500 / 100.0;
         cropsyst_soil->user[h] |= Soil_parameters::specified_PWP;
      };


      // N/A KP0
      // N/A KP10
      if (curr_soil_layer.KP33 > 0)
      {
         cropsyst_soil->horizon_field_capacity[h] = curr_soil_layer.KP33 / 100.0;
         cropsyst_soil->user[h] |= Soil_parameters::specified_FC;
      };
      if (curr_soil_layer.BD > 0)
      {
         cropsyst_soil->horizon_bulk_density_g_cm3[h] = curr_soil_layer.BD;
         cropsyst_soil->user[h] |= Soil_parameters::specified_bulk_density;
      };
      if (curr_soil_layer.KSAT > 0)
      {
         float32 KSAT_m_h = cm_to_m(curr_soil_layer.KSAT);
         float32 KSAT_S_m_d = m_per_hr_to_m_per_day(KSAT_m_h);
         cropsyst_soil->sat_hydraul_cond_m_d[h] = KSAT_S_m_d;
         cropsyst_soil->user[h] |= Soil_parameters::specified_sat_hydraul_cond;
      };
      // N/A COFRAG  (probably should add to CropSyst with new Saxton Pedotransfer functions
      // N/A DOMSAND
      // N/A VFSAND
      if (curr_soil_layer.TSAND > 0)
      {  cropsyst_soil->horizon_sand[h] =curr_soil_layer. TSAND;
         cropsyst_soil->user[h] |= Soil_parameters::specified_sand;
      };
      if (curr_soil_layer.TSILT > 0)
      {  cropsyst_soil->horizon_silt[h] = curr_soil_layer.TSILT;
         cropsyst_soil->user[h] |= Soil_parameters::specified_silt;
      };
      if (curr_soil_layer.TCLAY > 0)
      {  cropsyst_soil->horizon_clay[h] = curr_soil_layer.TCLAY;
         cropsyst_soil->user[h] |= Soil_parameters::specified_clay;
      };
      if (curr_soil_layer.ORGCARB > 0)
      {  float32 OM_percent = 1.724 * curr_soil_layer.ORGCARB;
         cropsyst_soil->organic_matter[h] = OM_percent;
      };
      // N/A PHCA
      if (curr_soil_layer.PH2 > 0) cropsyst_soil->pH[h] = curr_soil_layer.PH2;

      /* NYI
      if (BASES > 0)
      {  cropsyst_soil->horizon_saturation_WC =  BASES /  100.0;
         cropsyst_soil->user[h] |= Soil_parameters::Saturation;
      }
      */
      if (curr_soil_layer.CEC > 0) cropsyst_soil->cation_exchange_capacity[h] = curr_soil_layer.CEC;
      // N/A EC
      // N/A CACO3
      // N/A VONPOST
      // N/A WOOD

      cropsyst_soil->layer_texture_hydraulics[h]->recompute_every_thing();
      prev_soil_layer_type = curr_soil_layer.SOILTYPE_OR_ID;
   };
   if (cropsyst_soil)
   {  // Save the last soil

      CORN_Directory_name_instance dest_dir(editdir_destination->Text.c_str());
      #ifdef USE_OS_FS
      CORN::OS::File_name_logical soil_filename(dest_dir,prev_soil_layer_type.c_str(),"CS_soil");
      #else
      CORN::File_name soil_filename(prev_soil_layer_type.c_str(),"CS_soil");
      soil_filename.set_path(dest_dir.c_str());
      #endif
      CORN::VV_File soil_file(soil_filename.c_str());
      cropsyst_soil->save_only_specified_layers = true;                          //130224
      soil_file.set(*cropsyst_soil);
      delete cropsyst_soil; cropsyst_soil = 0;
   };
   button_CanSIS_NSDB_convert->Caption = "Perform conversion";
};
//______________________________________________________________________________
