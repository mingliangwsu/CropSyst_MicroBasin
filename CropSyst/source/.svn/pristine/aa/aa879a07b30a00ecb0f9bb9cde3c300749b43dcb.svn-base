#ifdef USE_PCH
#  include <CropSyst/GUI/OWL/headers.h>
#else
#  include "v_simfile.h"
#  include <corn/validate/parameter_file.h>
#  include <common/weather/v_locfile.h>
#  include "v_soilfile.h"
#  include "v_mgmtfile.h"
#endif
#include "cs_project.h"
  // Enabled for parameter editor
bool load_failure_message(ofstream &vf)
{
#ifdef LOTS_OF_MEMORY
#ifdef USE_CORN_TRANSLATOR_CLASS
   if (common_translator->current_code == "it")
   {
      vf << "Un file di parametri non riesce ad essere caricato nelle seguenti condizioni:" << endl;
      vf << "1. Forse il file di dati ‚ stato aggiornato." << endl;
      vf << "   nuove versioni di CropSyst possono richiedere nuovi formati dei files" << endl;
      vf << "   In questo caso il vecchio file deve essere aggiornato:" << endl;
      vf << "   La nuova versione di CropSyst pu¢ contenere utilities per l'+CHR(39)+'aggiornamento" << endl;
      vf << "   Fare riferimento al file READ.ME e al manuale utente." << endl;
      vf << "2. Forse il file non esiste." << endl;
      vf << "   Controllare i nomi selezionati nel file di controllo della simulazione." << endl;
      vf << "3. Forse il file non Š pi£ leggibile" << endl;
      vf << "   Questo pu¢ essere conseguenza di malfunzionamento del sistema operativo MS-DOS." << endl;
      vf << "   Prova ad inviare il comando DOS CHKDSK per riparare i file di sistema." << endl;
      vf << "   In questo caso, il file di dati Š irrimediabilmente danneggiato." << endl;
   }
   else if (common_translator->current_code == "es")
   {
     vf << "Un archivo de par metros no se puede abrir en los siguientes casos:" << endl;
     vf << "1. Quiz s el archivolde datos debe actualizarse." << endl;
     vf << "   Nueva versi¢n de CropSyst puede usar un nuevo formato." << endl;
     vf << "   En este caso, los archivos antiguos deben reactualizarse:" << endl;
     vf << "   El diskette de distribuci¢n de CropSyst puede contener un" << endl;
     vf << "   programa para actualizar archivos." << endl;
     vf << "   Consulte el archivo LEER.ME y el manual del usuario." << endl;
     vf << "2. Quiz s el archivo no existe." << endl;
     vf << "   Verifique el nombre del los archivos seleccionados en el archivo" << endl;
     vf << "   de control de la simulaci¢n." << endl;
     vf << "3. Quiz s el archivo est‚ corrupto." << endl;
     vf << "   Esto puede resultar como consecuencia de una falla de MS_DOS." << endl;
     vf << "   Trate de utilizar el comando de DOS -CHKDSK- para verificar y " << endl;
     vf << "   reparar el sistema de archivos." << endl;
     vf << "   En este caso, el archivo es irrecuperable." << endl;
   }
   else if (common_translator->current_code == "fr")
   {
     vf << "Un fichier paramêtres ne peut être chargé pour les raisons suivantes:" << endl;
     vf << "1. Soit le fichier de données est mal formaté." << endl;
     vf << "   Les versions récentes de CROPSYST peuvent utiliser de nouveaux formats." << endl;
     vf << "   Dans ce cas, les vieux fichiers doivent ˆtre r‚actualis‚s:" << endl;
     vf << "   CROPSYST fournit le nécéssaire pour réactualizer les fichiers." << endl;
     vf << "   Se référer aux notes de readme.en, et au manuel d'utilisation." << endl;
     vf << "2. Soit le fichier n'existe pas." << endl;
     vf << "   v‚rifier les noms de fichiers sélectionnés dans le fichier de contrôle de simulation." << endl;
     vf << "3. Soit le fichier s'est abim‚." << endl;
     vf << "   Ceci peut être du … un probleme li‚ au systŠme d'op‚ration MS-DOS." << endl;
     vf << "   Essayer la commande DOS CHKDSK pour valider et r‚parer le systŠme de fichier." << endl;
     vf << "   Dans ce ca, le fichier de donn‚es est d‚finitivement abim‚." << endl;
   }
   else
#endif
   {
     vf << "A parameter file fails to load in the following conditions:" << endl;
     vf << "1. Perhaps the data file may be outdated." << endl;
     vf << "   New versions of CROPSYST may use new file formats." << endl;
     vf << "   In this case the old files will need to be updated:" << endl;
     vf << "   The CROPSYST distribution may contain utilities to update files." << endl;
     vf << "   Refer to the RELEASE.TXT release notes file and the user manual." << endl;
     vf << "2. Perhaps the file does not exist." << endl;
     vf << "   Check the filenames selected in the simulation control file." << endl;
     vf << "3. Perhaps the file has become corrupted." << endl;
     vf << "   This may be the result of a failure of the MS-DOS operating system." << endl;
     vf << "   Try running the DOS command CHKDSK to validate and repair the file system." << endl;
     vf << "   In this case, the data file is irrevokably damaged." << endl;
   };
#endif
   return(0);
};
//______________________________________________________________________________
Valid_CropSyst_scenario::Valid_CropSyst_scenario(CropSyst_project  &i_project)
   : CropSyst_scenario()
   , project(i_project)
   , management_file_status(unknown_status)
   , soil_file_status(unknown_status)
   , location_file_status(unknown_status)
   , recalibration_file_status(unknown_status)
   , water_table_file_status(unknown_status)
   , rotation_file_status(unknown_status)
   , format_file_status(unknown_status)
   , rot_management_file_status(unknown_status)
   , rot_crop_file_status(unknown_status)
   , mapunit_dbf_status(unknown_status)
   , v_soil_filename_htm(soil_filename,"htm")
   , v_location_filename_htm(location_filename,"htm")
   , v_management_filename_htm(management_filename,"htm")
   , v_recalibration_filename_htm(recalibration_filename,"htm")
   , v_water_table_filename_htm(water_table_filename,"htm")
   , v_rotation_filename_htm(rotation_filename,"htm")
   {
   };

//______________________________________________________________________________
Validation_status Valid_CropSyst_scenario::validate
(const SIM_filename &file_name)
{
   status = good_status;
   File_name validation_filename_htm(file_name,"htm");

   CORN_string vs;
   ofstream vf(validation_filename_htm.c_str());
   // vf is the validation output file.
   Parameter_file_validation val(file_name,vf);
   val.existence_check();
   val.description_check((description != ""));

   soil_file_status = soil_filename.exists()?unknown_status:missing_status;
   location_file_status = location_filename.exists()?unknown_status:missing_status;
   management_file_status = management_filename.exists()?unknown_status:missing_status;

   uint8 num_soil_layers = 0;
   if (location_filename.exists())
   {  Valid_location_parameters v_loc_params;
      VV_File loc_file(location_filename.c_str());
      loc_file.get(v_loc_params);
      location_file_status = v_loc_params.validate(location_filename,project.run_erosion);
      v_location_filename_htm.set(CORN::File_name(location_filename,"htm").c_str());
   } else
   {  load_failure_message(vf);
      val.set_worst_status(error_status);
   }
 if (soil_filename.exists())
 {  Valid_soil_parameters valid_soil_parameters;
    VV_File soil_file(soil_filename.c_str());
    soil_file.get(valid_soil_parameters);
    soil_file_status = valid_soil_parameters.validate(soil_filename);
    v_soil_filename_htm.set(CORN::File_name(soil_filename,"htm").c_str());
    num_soil_layers = valid_soil_parameters.number_horizons;
 }
 else
   {
      load_failure_message(vf);
      val.set_worst_status(error_status);
   }

   if (management_filename.exists())
   {
      Valid_management_parameters valid_mgmt_params;
      VV_File mgmt_file(management_filename.c_str());
      mgmt_file.get(valid_mgmt_params);
      management_file_status = valid_mgmt_params.validate(management_filename);
      v_management_filename_htm.set(CORN::File_name(management_filename,"htm").c_str());
   };


   if (!recalibration_filename.exists())
   {  // If the recalibration file doesn't exist,
      // try removing the path an see if it is in the current directory
      recalibration_filename.remove_path();
   };

   if (!water_table_filename.exists())
   {  // If the recalibration file doesn't exist,
      // try removing the path an see if it is in the current directory
      water_table_filename.remove_path();
   };
   if (!rotation_filename.exists())
   {  // If the rotation file doesn't exist,
      // try removing the path an see if it is in the current directory
      rotation_filename.remove_path();
   };

    rotation_file_status = (rotation_filename.exists())
   ? ready_status
   : unavailable_status;

   recalibration_file_status = (recalibration_filename.exists())
   ? ready_status
   : unavailable_status;
   water_table_file_status = (water_table_filename.exists())
   ? ready_status
   : unavailable_status;
   status = CORN_min(status,CORN_min(soil_file_status,location_file_status));
   if (project.run_nitrogen)
   {
   val.set_worst_status(v_adjust_mineralize.validate(vs,true));
   val.set_worst_status(v_adjust_nitrify.validate(vs,true));
   val.set_worst_status(v_adjust_denitrify.validate(vs,true));
   val.set_worst_status(v_max_transform_depth.validate(vs,true));
   val.set_worst_status(v_N_conc_residue.validate(vs,true));
   val.set_worst_status(v_N_conc_manure.validate(vs,true));
   }
   else
   {
      v_adjust_mineralize.set_status(disabled_status);
      v_adjust_nitrify.set_status(disabled_status);
      v_adjust_denitrify.set_status(disabled_status);
      v_max_transform_depth.set_status(disabled_status);
      v_N_conc_residue.set_status(disabled_status);
      v_N_conc_residue.set_status(disabled_status);
   };
   val.set_worst_status(v_surface_residue.validate(vs,true));
   val.set_worst_status(v_incorporated_residue.validate(vs,true));
   val.set_worst_status(v_decomposition_time_residue.validate(vs,true));

   val.set_worst_status(v_surface_manure.validate(vs,true));
   val.set_worst_status(v_incorporated_manure.validate(vs,true));
   val.set_worst_status(v_decomposition_time_manure.validate(vs,true));
   if (project.run_salinity)
      val.set_worst_status(v_initial_water_table_salinity.validate(vs,true));
   else
      v_initial_water_table_salinity.set_status(disabled_status);
#ifdef MOVE
This needs to be moved to project
   if (project.simulate_CO2)
   {
   val.set_worst_status(v_annual_CO2_change.validate(vs,true));
   val.set_worst_status(v_initial_CO2_conc.validate(vs,true));
   }
   else
   {
      v_annual_CO2_change.set_status(disabled_status);
      v_initial_CO2_conc.set_status(disabled_status);
   };
#endif
#ifdef SOILR
   val.set_worst_status(v_SoilR_adjust_relative_growth_rate_for_clipping.validate(vs,true));
   val.set_worst_status(v_SoilR_minimum_biomass_required_for_clipping.validate(vs,true));
   val.set_worst_status(v_SoilR_biomass_forces_clipping.validate(vs,true));
   val.set_worst_status(v_SoilR_biomass_removed_clipping.validate(vs,true));
   val.set_worst_status(v_SoilR_max_root_depth.validate(vs,true));
   val.set_worst_status(v_SoilR_max_LAI.validate(vs,true));
   val.set_worst_status(v_SoilR_ET_crop_coef.validate(vs,true));
   val.set_worst_status(v_SoilR_induce_dormancy_temp.validate(vs,true));
#endif
   for (uint8 layer = 1; layer <= MAX_soil_horizons; layer++)
   {
      layer_status[layer] = good_status;
      if (layer <= num_soil_layers)
      {
         layer_status[layer] = CORN_min(layer_status[layer],v_N_NO3[layer]->validate(vs,true));
         layer_status[layer] = CORN_min(layer_status[layer],v_N_NH4[layer]->validate(vs,true));
         layer_status[layer] = CORN_min(layer_status[layer],v_salt[layer]->validate(vs,true));
         layer_status[layer] = CORN_min(layer_status[layer],v_H2O[layer]->validate(vs,true));
//                     layer_status[layer] = CORN_min(layer_status,xxxx.validate(vs,true));
//                     layer_status[layer] = CORN_min(layer_status,xxxx.validate(vs,true));

         val.set_worst_status(layer_status[layer]);
      }
      else
         layer_status[layer] = unavailable_status;
   };
   vf << vs;
//             Need to make sure the recalibration file layering matches the number of layers in the soil file.
   return val.get_status();;
};
//______________________________________________________________________________
void Valid_CropSyst_scenario::get_end()
{  CropSyst_scenario::get_end();
   v_soil_filename_htm           .set(soil_filename.c_str());                         v_soil_filename_htm.set_ext("htm");
   v_location_filename_htm       .set(location_filename.c_str());                     v_location_filename_htm.set_ext("htm");
   v_management_filename_htm     .set(management_filename.c_str());                   v_management_filename_htm.set_ext("htm");
   v_recalibration_filename_htm  .set(recalibration_filename.c_str());                v_recalibration_filename_htm.set_ext("htm");
   v_water_table_filename_htm    .set(water_table_filename.c_str());                  v_water_table_filename_htm.set_ext("htm");
};
//______________________________________________________________________________

