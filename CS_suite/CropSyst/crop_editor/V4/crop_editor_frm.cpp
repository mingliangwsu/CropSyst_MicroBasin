//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
#include "crop_editor_frm.h"
#include "corn/math/compare.hpp"
#include "corn/application/translations.h"
#if (__BCPLUSPLUS__ < 0x0620)
#include "CropSyst/source/crop/crop_param.h"
#else
// RadStudio of version 4 editor uses new controls
#include "CropSyst/source/crop/crop_param_V5.h"
#endif
#  include "corn/OS/directory_entry_name_concrete.h"
#  include "corn/application/program_directory_OS_FS.h"
#  include "corn/container/text_list.h"
#  include "corn/OS/file_system_engine.h"
#include "corn/string/strconv.hpp"
#include "corn/seclusion.h"

#  define p_filling_sensitivity v_filling_sensitivity
#  define p_filling_duration v_filling_duration
#  define p_biomass_to_start_dilution_max_N_conc   v_biomass_to_start_dilution_max_N_conc
#  define p_demand_adjust                          v_demand_adjust
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "HTMLText"
#pragma link "rtflabel"
#pragma link "AdvGroupBox"
#pragma link "AdvPanel"
#pragma link "AdvOfficePager"
#pragma link "RNAutoCheckBox"
#pragma link "RNAutoContainerCheckListBox"
#pragma link "RNAutoContainerListBox"
#pragma link "RNAutoDateButton"
#pragma link "RNAutoFloatEdit"
#pragma link "RNAutoIntegerEdit"
#pragma link "RNAutoParameterEditBar"
#pragma link "RNAutoRadioGroup"
#pragma link "RNAutoContainerListBox"
#pragma resource "*.dfm"
TCrop_editor_form *Crop_editor_form;
#include "CS_Suite/CropSyst/crop_editor/form_crop_editor_inc.h"
//______________________________________________________________________________
__fastcall TCrop_editor_form::TCrop_editor_form(TComponent* Owner)
   : TForm(Owner)
   , crop(0)
   , crop_directory() // current working directory
   , top_checksum(0)
   , root_checksum(0)
   , adjustment_offset(0)
   , adjustment_thermal_time(0)
   , last_item_index(-1)
{
   designed_deg_day_tuber_initiation_edit_top            = edit_deg_day_tuber_initiation->Top;
   designed_max_root_depth_dd_edit_top                   = edit_max_root_depth_dd->Top;
   designed_deg_day_end_vegetative_growth_edit_top       = edit_deg_day_end_vegetative_growth->Top;
   designed_deg_day_begin_flower_edit_top                = edit_deg_day_begin_flower->Top;
   designed_deg_day_begin_filling_grain_or_fruit_edit_top= edit_deg_day_begin_filling_grain_or_fruit->Top;
   designed_deg_day_begin_rapid_fruit_growth_edit_top    = edit_deg_day_begin_rapid_fruit_growth->Top;
   designed_deg_day_begin_maturity_edit_top              = edit_deg_day_begin_maturity->Top;
   designed_phenologic_sensitivity_water_stress_edit_top = edit_phenologic_sensitivity_water_stress->Top;

   CORN::OS::Directory_name_concrete database_crop_default_dir(*program_directory,L"default");
   CORN::Unidirectional_list default_crops_list;
   CORN::OS::file_system_engine.list_DENs                                        //160814
      (database_crop_default_dir
      ,&default_crops_list,0,CORN::Inclusion("*.crp",false));
   Application->HintHidePause = 8000;
   FOR_EACH_IN(crop_filename,CORN::OS::Directory_entry_name,default_crops_list,Xeach_default_crop)
   {  crop_class_combobox->Items->Append(crop_filename->get_name().c_str());
   } FOR_EACH_END(Xeach_default_crop)
}
//______________________________________________________________________________
__fastcall TCrop_editor_form::~TCrop_editor_form()
{}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::bind_to
(CropSyst::Crop_parameters *_crop,Tparameter_file_form *_parameter_form,const char *_crop_model)
{  bind_to_V4_and_V5(_crop,_parameter_form,_crop_model);
   radiogroup_thermal_response->bind_to(&(crop->thermal_time.thermal_response_cowl),0);       //170402

   edit_carbon_fraction                      ->bind_to(&(crop->residue_decomposition.p_carbon_fraction)                      V4_HELP_URL (HELP_P_crop_residue_carbon_fraction));
   edit_stubble_area_covered_to_mass_ratio   ->bind_to(&(crop->residue_decomposition.p_stubble_area_covered_to_mass_ratio)   V4_HELP_URL (HELP_P_crop_residue_area_mass_ratio));
   edit_surface_area_covered_to_mass_ratio   ->bind_to(&(crop->residue_decomposition.p_surface_area_covered_to_mass_ratio)   V4_HELP_URL (HELP_P_crop_residue_area_mass_ratio));
   edit_detrition_time   ->bind_to(&(crop->residue_decomposition.detrition_time_50)  ,2                                      V4_HELP_URL(HELP_P_crop_residue_detrition_time));
   // season/dormancy
   edit_consider_inactive_days->bind_to(&(crop->quiescence.p_consider_inactive_days));// ,0 /*NO HELP YET parameter_file_form->compose_manual_subdirectory_filename(HELP_P_crop_hardiness_days_salvage).c_str()*/);
   edit_inducement_temperature->bind_to(&(crop->quiescence.p_inducement_temperature) ); //  V4_HELP_URL(HELP_P_crop_dormancy_avg_temp_7day));
   radiogroup_RUE_basis_mode->Update();                                          //110825
   #if (CROPSYST_VERSION < 5)
      radiogroup_RUE_basis_mode->Visible=true;
   #endif

   radiogroup_thermal_response->Update();                                        //171029
   resolution_radiogroup_onclick(0);
   // Only in version 4:
   edit_decomposition_time_50                ->bind_to(&(crop->residue_decomposition.decomposition_time_50)             V4_HELP_URL(HELP_P_crop_residue_decomp_time));
   // In V4 these are dates, in V5 these are DOY
   /*180601 dont delete yet
   edit_quiescence_start_DOY ->bind_to(&(crop->quiescence.p_start_DOY));         //161004
   edit_quiescence_end_DOY   ->bind_to(&(crop->quiescence.p_end_DOY));           //161004
   */
   checkbox_senesces                      ->bind_to(&(crop->senesces)                           V4_HELP_URL(HELP_P_crop_senesces));
   checklistbox_adjustments->bind_to(&(crop->adjustments)/*,0 NO_HELP*/);        //130423
   show_hide_controls();
   edit_adjustment_offset->bind_to(&adjustment_offset /*,0 NO_HELP*/);           //130423
   edit_adjustment_thermal_time->bind_to(&adjustment_thermal_time/*,0NO_HELP*/);//130423
   combobox_adjustment_crop_event->ItemIndex = 0;                                //130429
   combobox_stress_period        ->ItemIndex = 1; //default is after emergence   //130429
   edit_grain_stress_sensitivity_offset      ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.begin_sync.days_offset) /*,0 NO_HELP*/); //130428
   edit_grain_stress_sensitivity_thermal_time->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.begin_sync.thermal_time)/*,0 NO_HELP*/); //130428

   //130429 The following might go in V5
   // But probably will have separate scheduled variables

   edit_heat_stress_no_stress_threshold_temperature   ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.heat.no_stress_threshold_temperature/*v_heat_stress_no_stress_threshold_temperature*/)   ,2/*,0 NO_HELP*/);
   edit_heat_stress_max_stress_threshold_temperature  ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.heat.max_stress_threshold_temperature/*v_heat_stress_max_stress_threshold_temperature*/)  ,2/*,0 NO_HELP*/);
   edit_heat_stress_sensitivity                       ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.heat.sensitivity/*v_heat_stress_sensitivity*/)                      ,2 /*,0NO_HELP*/);
   edit_heat_stress_exposure_damaging_hours           ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_damaging_hours/*v_heat_stress_exposure_damaging_hours*/)         ,2  /*,0 NO_HELP*/);
   edit_heat_stress_exposure_initial_hour->Visible = (crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_initial_hour < 24);
   edit_heat_stress_exposure_initial_hour             ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_initial_hour)           /* ,0 NO_HELP*/); //130628
   edit_cold_stress_no_stress_threshold_temperature   ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.no_stress_threshold_temperature)   ,2/*NO_HELP*/);
   edit_cold_stress_max_stress_threshold_temperature  ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.max_stress_threshold_temperature)  ,2/*NO_HELP*/);
   edit_cold_stress_sensitivity                       ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.sensitivity)                       ,2/*NO_HELP*/);
   edit_cold_stress_exposure_damaging_hours           ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.exposure_damaging_hours)           ,2/*NO_HELP*/);
   edit_cold_stress_exposure_initial_hour             ->bind_to(&(crop->harvest.editor_grain_stress_sensitivity_period.cold.exposure_initial_hour)            /*NO_HELP*/); //130628

   listbox_harvest_temperature_stress_events->bind_to(&(crop->harvest.grain_stress_sensitivity_periods) /*NO_HELP*/);

   radiogroup_canopy_model->bind_to(&(crop->morphology.canopy_growth_cowl),0 /*NO_HELP*/);


   development_fract_biomass_edit   ->bind_to(&(crop->fruit. p_initial_growth_fraction_to_fruit)/*NO_HELP*/); //180601
   veraison_fract_biomass_edit      ->bind_to(&(crop->fruit. p_rapid_growth_fraction_to_fruit) /*NO_HELP*/); //180601


   Update();                                                                     //171123
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::Update(void )
{  if (!crop) return;
   edit_at_pt_root_limit                     ->Update(); //obsolete?
   Update_V4_and_V5();                                                           //110526
   page_canopy_growth->ActivePageIndex =                                         //130614
      (  (crop->morphology.canopy_growth == canopy_cover_based_2017)
       //180601 ||(crop->morphology.canopy_growth == canopy_cover_based_2013)
       )
      ? 1 : 0;

   bool canopy_cover_mode =
      (  (crop->morphology.canopy_growth == canopy_cover_based_2017)             //171219
      //180601  ||(crop->morphology.canopy_growth == canopy_cover_based_2013)
       );           //171123
   tabsheet_canopy_LAI->TabVisible = !canopy_cover_mode;                         //171123
   tabsheet_canopy_cover->TabVisible = canopy_cover_mode;                        //171123

   // Only in V4
   edit_RUE_PAR_basis                        ->Update();                         //110826
   development_fract_biomass_edit   ->Update();
   veraison_fract_biomass_edit      ->Update();
   edit_decomposition_time_50                ->Update();
   pot_N_uptake_model_radio_obsolete         ->Update();
   crop->set_current_section("unused_section_for_editor");                       //150529
   checklistbox_adjustments->Update();                                           //130423

   // The following might go in V5
   edit_heat_stress_no_stress_threshold_temperature   ->Update();                //130429
   edit_heat_stress_max_stress_threshold_temperature  ->Update();                //130429
   edit_heat_stress_sensitivity                       ->Update();                //130429
   edit_heat_stress_exposure_damaging_hours           ->Update();                //130429
   edit_cold_stress_no_stress_threshold_temperature   ->Update();                //130429
   edit_cold_stress_max_stress_threshold_temperature  ->Update();                //130429
   edit_cold_stress_sensitivity                       ->Update();                //130429
   edit_cold_stress_exposure_initial_hour             ->Update();                //130628
   edit_heat_stress_exposure_initial_hour->Visible = (crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_initial_hour < 24);
   edit_heat_stress_exposure_initial_hour             ->Update();                //130628

   edit_cold_stress_exposure_damaging_hours           ->Update();                //130429
   listbox_harvest_temperature_stress_events->Update();                          //130429
   translate_page_controls();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::photoperiod_checkbox_onclick(TObject *Sender)
{  if (crop)    bind_to_photoperiod();          // probably obsolete in V4
   show_hide_controls();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::vernalization_checkbox_onclick(TObject *Sender)
{  if (crop) bind_to_vernalization();
   show_hide_controls();
}
//________________________________________________vernalization_checkbox_onclick
void __fastcall TCrop_editor_form::sensitive_to_cold_edit_onclick(TObject *Sender)
{  if (crop)    bind_to_hardiness();                                    //V4&V5
   show_hide_controls();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::harvested_biomass_radiogroup_onclick(TObject *Sender)
{  show_hide_controls();                                                 //V4&V5
}
//__________________________________________harvested_biomass_radiogroup_onclick
void __fastcall TCrop_editor_form::perennial_checkbox_onclick(TObject *Sender)
{  //V4 (this may actually be obsolete)
   groupbox_LAI_duration->Visible = crop->has_leaf_senescence() &&
     ((crop->morphology.canopy_growth_cowl.get() == leaf_area_index_based) ||
      (crop->morphology.canopy_growth_cowl.get() == canopy_architecture));       //180601
   edit_N_max_stubble->Visible                   = !crop->is_perennial();
   edit_root_N_conc->Visible                     = !crop->is_perennial();
   edit_deg_day_end_vegetative_growth->Visible                  = true;
   edit_max_root_depth_dd->Visible                 = crop->crop_model_labeled.get() != CROPSYST_ORCHARD_MODEL;
   edit_deg_day_begin_maturity->Visible = crop->phenology.maturity_significant;
   // Note that dormancy used to be shown only if perennial,
   // now it is user option.
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::crop_model_radiogroup_onclick(TObject *Sender)
{  handle_crop_model_radiogroup_onclick();                              //V4&5
      bind_to_fruit();
      bind_to_nitrogen();
      bind_to_salinity();
      bind_to_dormancy();
      bind_to_CO2_response();
      show_hide_controls();
}
//______________________________________________________________________________
void TCrop_editor_form::show_hide_controls()
{  if (!crop) return;
   show_hide_controls_V4_and_V5();                                               //110524
   // Currently I assume that cropgro will have all the parameters of CropSyst
   bool CROPSYST_OR_CROPGRO_MODEL = ((crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL) || (crop->crop_model_labeled.get() == CROPGRO_MODEL));
   bool CROPSYST_FRUIT (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL);
   #if (CROP_EDITOR_VERSION==4)
   /*170402 Dont delete yet not sure why compiler is not finding setup_optional_parameters()
   might be obsolete
   crop->setup_optional_parameters();
   */
   #endif
   crop_class_groupbox->Visible  = (crop->crop_model_labeled.get() != CROPGRO_MODEL);
   general_crop_image->Visible   = (crop->crop_model_labeled.get() == CROPSYST_CROP_MODEL) ;
   fruit_image->Visible          = (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL) && !crop->fruit.grape ;
   cropgro_image->Visible        = (crop->crop_model_labeled.get() == CROPGRO_MODEL);
   grape_crop_image->Visible     = (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL && crop->fruit.grape );

//NYI   initial_growth_radiogroup->Visible  = CROPSYST_FRUIT;

   residue_sheet        ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   nitrogen_sheet       ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   salinity_sheet       ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   vernalization_sheet  ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   photoperiod_sheet    ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   layout_sheet         ->TabVisible = CROPSYST_FRUIT;
   tabsheet_fruit       ->TabVisible = CROPSYST_FRUIT;
   salinity_sheet       ->TabVisible = CROPSYST_OR_CROPGRO_MODEL;
   emergence_tabsheet   ->TabVisible = CROPSYST_OR_CROPGRO_MODEL; // does not apply to orchard
#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
   if (CROPSYST_FRUIT)
      crop->life_cycle_labeled.set(PERENNIAL_WOODY);
#endif
   bool is_annual = crop->life_cycle_labeled.get() == annual_life_cycle;         //161004
   tabsheet_seasonal_adjustment->TabVisible = !is_annual;
   bool vernalization_enabled = crop->vernalization.enabled;
   panel_vernalization_parameters->Enabled = vernalization_enabled;
   #if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
   // now always total radiation
   radiogroup_RUE_basis_mode ->bind_to(&(crop->biomass_production.RUE_basis_cowl)/*NO_HELP_YET_*/); //max_RUE_mode_labeled
   edit_RUE_global_basis->Visible
      = crop->biomass_production.RUE_basis_cowl.get() ==total_radiation;         //110907
   edit_RUE_PAR_basis->Visible =  crop->biomass_production.RUE_basis_cowl.get() ==photosynthetically_active_radiation;; //110907
   #else
   // Now always total basis
   edit_RUE_PAR_basis->Visible = false;
   edit_RUE_global_basis->Visible = true;
   #endif

   edit_grain_translocation_fraction->Visible = true;
   groupbox_harvest_index_grain_temperature_stress->Visible =
      true;
   bool use_new_temperature_limitation = true;                                   //170524
   groupbox_flowering_stress->Visible = listbox_harvest_temperature_stress_events->ItemIndex >= 0; //150519

   radiogroup_canopy_model->Items->Clear();                                      //180601

   if (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)                 //180601
         radiogroup_canopy_model->Items->Add(L"LAI: with specified senescence (N/A)"); //180601
   else  radiogroup_canopy_model->Items->Add(L"LAI: with specified senescence"); //180601
   radiogroup_canopy_model->Items->Add(L"canopy cover");                         //180601
   radiogroup_canopy_model->Items->Add(L"LAI: senescence driven by leaf duration"); //180601
   if (crop->crop_model_labeled.get() == CROPSYST_ORCHARD_MODEL)                 //180601
      radiogroup_canopy_model->Items->Add(L"canopy architecture");               //180601
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::crop_class_combobox_onchange(TObject *Sender)
{  handle_crop_class_combobox_onchange();
   crop_pagecontrol->ActivePage = tabsheet_defaults;
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::Crop_editor_form_onactivate(TObject *Sender)
{  CORN::OS::file_system_engine.set_current_working_directory(crop_directory);   //131118
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::calibrate_button_onclick(TObject *Sender)
{  handle_calibrate_button_on_click();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::resolution_radiogroup_onclick(TObject *Sender)
{                                                                          //V4&V5
   // base is always visible
   edit_cutoff_temp->Visible = crop->thermal_time.thermal_response == linear;
   edit_opt_temp   ->Visible = crop->thermal_time.thermal_response == nonlinear;
   edit_max_temp   ->Visible = crop->thermal_time.thermal_response == nonlinear;
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::grape_checkbox_onclick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::FormKeyPress(TObject *Sender, char &Key)
{  if (Key==VK_RETURN)                                                  //V4&V5
   {  Key = 0;
      Perform(WM_NEXTDLGCTL,0,0);
   }
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::life_cycle_radiogroup_onclick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::senesces_checkbox_onclick(TObject *Sender)
{  show_hide_controls();                                                //V4only
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::emergence_model_radiogroupon_onclick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::update_top_biomass_checksum(TObject *Sender)
{  //V4&V5
   if (!crop)  return;
   top_checksum = crop->residue_decomposition.fast_cycling_top_fraction
                + crop->residue_decomposition.slow_cycling_top_fraction
                + crop->residue_decomposition.lignified_top_fraction;
   handle_update_top_biomass_checksum();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::update_root_biomass_checksum(TObject *Sender)
{                                                                       //V4&V5
   if ((!crop))  return;
   root_checksum = crop->residue_decomposition.fast_cycling_root_fraction
                 + crop->residue_decomposition.slow_cycling_root_fraction
                 + crop->residue_decomposition.lignified_root_fraction;
   handle_update_root_biomass_checksum();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::checkbox_advanced_moved_to_param_file_formClick(TObject *Sender)
{  show_hide_controls();                                                //V4only
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::pot_N_uptake_model_radio_onclick(TObject *Sender)
{  show_hide_controls();                                                //obsolete
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::checkbox_maturity_significantClick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::pagecontrol_season_dormancy_mode_onchange(TObject *Sender)
{  crop->season_dormancy_mode_labeled.set_int32
      (pagecontrol_inactivity->ActivePageIndex);                                 //180601
      //180601 (pagecontrol_season_dormancy_mode->ActivePageIndex);
   show_hide_controls();                                                 //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::checkbox_WUE_changesClick(TObject *Sender)
{  show_hide_controls();
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_canopy_modelClick(TObject *Sender)
{  crop->morphology.canopy_growth_cowl.set_int32(radiogroup_canopy_model->ItemIndex);
   tabsheet_canopy_LAI->TabVisible = true;
   tabsheet_canopy_cover->TabVisible = true;
   bool canopy_cover_mode =
      (  (crop->morphology.canopy_growth == canopy_cover_based_2017)             //171219
       //180601 ||(crop->morphology.canopy_growth == canopy_cover_based_2013)
       );
   page_canopy_growth->ActivePageIndex = canopy_cover_mode ? 1 : 0;
   tabsheet_canopy_LAI->TabVisible = !canopy_cover_mode;
   tabsheet_canopy_cover->TabVisible = canopy_cover_mode;
   show_hide_controls();                                                         //150826
}
//_2013-06-14___________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_WUE_submodelClick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_RUE_basis_modeClick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_senesced_biomass_fate_obsoleteClick(TObject *Sender)
{  edit_linger->Visible = (crop->abscission_labeled.get() == semi_deciduous );
}
//_2014-11-21___________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_photoperiod_considerationClick(TObject *Sender)
{  show_hide_controls();                                                //V4&V5
}
//______________________________________________________________________________
void TCrop_editor_form::translate_page_controls()
{                                                                       //V4only
   translate_tabsheets(get_main_page_control());
   translate_tabsheets(crop_pagecontrol);
   translate_tabsheets(page_control_harvest);
   translate_tabsheets(pagecontrol_nitrogen);
   translate_tabsheets(pagecontrol_inactivity); //180610 (pagecontrol_season_dormancy_mode);
   translate_tabsheets(page_canopy_growth);                                      //130614
   translate_tabsheets(page_control_attainable_growth);
}
//______________________________________________________________________________
void TCrop_editor_form::translate_tabsheets(TPageControl *page_control)
{  //V4only
   CORN::Translations_phrases *translation_phrases = parameter_file_form->get_translation_phrases();
   if (!translation_phrases) return;
   const char *translator_target_language = parameter_file_form->get_translation_selected_language();
   for (int ts_i = 0; ts_i < page_control->PageCount; ts_i++)
   {  TTabSheet *tabsheet = page_control->Pages[ts_i];
      const CORN::Translation *translated = dynamic_cast<const CORN::Translation *>
            (translation_phrases->find_wstr(tabsheet->Caption.c_str()));         //161004
      if (translated)
      {  const char *translated_text_ANSI =0;
         const wchar_t *translated_text_Unicode = 0;
#ifdef _UNICODE
            translated_text_Unicode = translated->get_translation(translator_target_language);
               if (translated_text_Unicode)
                  tabsheet->Caption = translated_text_Unicode;

#else
            translated_text_ANSI =  translated->get_translation(translator_target_language);
            if (translated_text_ANSI)
            {
                  tabsheet->Caption = translated_text_ANSI;
            }
      }
#endif
   }
}
//______________________________________________________________________________
void __fastcall TCrop_editor_form::checkbox_HI_extreme_adjustmentsClick(TObject *Sender)
{  show_hide_controls();
}
//_2011-09-07___________________________________________________________________
void __fastcall TCrop_editor_form::checkbox_HI_general_adjustmentsClick(TObject *Sender)
{  show_hide_controls();
}
//_2015-02-10___________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_photosyntheticClick(TObject *Sender)
{  handle_radiogroup_photosynthetic_click();
   int photopath = radiogroup_photosynthetic->ItemIndex;
}
//_2012-05-05___________________________________________________________________
void __fastcall TCrop_editor_form::pagecontrol_dilution_curve_basisChange(TObject *Sender)
{  //V4 only
   #if (CROPSYST_VERSION == 4)
   crop->nitrogen.dilution_curve_based_on_max_conc = (int)pagecontrol_dilution_curve_basis->ActivePageIndex;
   #endif
}
//_2013-03-19___________________________________________________________________
void __fastcall TCrop_editor_form::radiogroup_preset_end_dilutionClick(TObject *Sender)
{  handle_preset_end_dilution();
}
//_2013-04-08___________________________________________________________________
void __fastcall TCrop_editor_form::checklistbox_adjustmentsClick(TObject *Sender)
{  int index=checklistbox_adjustments->ItemIndex; // NYI I need to determine the clicked index
   CropSyst::Crop_parameters::Adjustment_event *adjustment = dynamic_cast<CropSyst::Crop_parameters::Adjustment_event *>(crop->adjustments.get_at(index));
   adjustment_offset = adjustment->begin_sync.days_offset;
   adjustment_thermal_time =  adjustment->begin_sync.thermal_time;
   pagecontrol_adjustment_sync_mode->ActivePageIndex =
      adjustment->begin_sync.sync_mode_labeled.get() == THERMAL_TIME_MODE ? 1 : 0;
   edit_adjustment_offset           ->Update();
   combobox_adjustment_crop_event   ->ItemIndex = adjustment->begin_sync.normal_crop_event_sequence_labeled.get();
   edit_adjustment_thermal_time     ->Update();
   combobox_adjustment_variable     ->Text = adjustment->parameter.c_str();
   edit_adjustment_value            ->Text = adjustment->value.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::listbox_harvest_temperature_stress_eventsClick(TObject *Sender)
{  int index=listbox_harvest_temperature_stress_events->ItemIndex; // NYI I need to determine the clicked index
   if (last_item_index != -1)
   {  replace_harvest_grain_stress_sensitivity(last_item_index);
   }
   groupbox_flowering_stress->Visible = index >= 0;                              //150519
   last_item_index = index;
   CropSyst::Crop_parameters::Harvest::Grain_stress_sensitivity_period  *period = dynamic_cast<CropSyst::Crop_parameters::Harvest::Grain_stress_sensitivity_period *>(crop->harvest.grain_stress_sensitivity_periods.get_at(index));
   pagecontrol_grain_stress_period->ActivePageIndex =
      period->begin_sync.sync_mode_labeled.get() == THERMAL_TIME_MODE ? 1 : 0;
   combobox_stress_period   ->ItemIndex = period->begin_sync.normal_crop_event_sequence_labeled.get();
   crop->harvest.editor_grain_stress_sensitivity_period.copy_from(*period);

   edit_grain_stress_sensitivity_offset               ->Update();
   edit_grain_stress_sensitivity_thermal_time         ->Update();
   edit_heat_stress_no_stress_threshold_temperature   ->Update();
   edit_heat_stress_max_stress_threshold_temperature  ->Update();
   edit_heat_stress_sensitivity                       ->Update();
   edit_heat_stress_exposure_damaging_hours           ->Update();
   edit_cold_stress_no_stress_threshold_temperature   ->Update();
   edit_cold_stress_max_stress_threshold_temperature  ->Update();
   edit_cold_stress_sensitivity                       ->Update();
   edit_cold_stress_exposure_initial_hour             ->Update();                //130628
   edit_heat_stress_exposure_initial_hour->Visible = (crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_initial_hour < 24);
   edit_heat_stress_exposure_initial_hour             ->Update();                //130628
   edit_cold_stress_exposure_damaging_hours           ->Update();
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_adjustment_addClick(TObject *Sender)
{  float32 value =
      (float32)wstr_to_float64
      (edit_adjustment_value->Text.c_str());
   std::wstring adjustment_variableW(combobox_adjustment_variable     ->Text.c_str());
   std::string adjustment_variable;
   CORN::wstring_to_string(adjustment_variableW,adjustment_variable);
   add_adjustment
      ((Synchronization_mode)(pagecontrol_adjustment_sync_mode->ActivePageIndex == 1) ? THERMAL_TIME_MODE : AFTER_NORMAL_CROP_GROWTH_STAGE_MODE
      ,(Normal_crop_event_sequence) combobox_adjustment_crop_event   ->ItemIndex
      ,adjustment_offset
      ,adjustment_thermal_time
      ,adjustment_variable.c_str() //161004 combobox_adjustment_variable     ->Text.c_str()
      ,value);
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_adjustment_replaceClick(TObject *Sender)
{  int replacing_item = checklistbox_adjustments->ItemIndex;
   if (replacing_item >= 0)
   {  CropSyst::Crop_parameters::Adjustment_event *adjustment = dynamic_cast<CropSyst::Crop_parameters::Adjustment_event *>(crop->adjustments.get_at(replacing_item));
      if (adjustment)
      {  adjustment->begin_sync.sync_mode_labeled.set((Synchronization_mode)
            (Synchronization_mode)(pagecontrol_adjustment_sync_mode->ActivePageIndex == 1) ? THERMAL_TIME_MODE : AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);
         adjustment->begin_sync.normal_crop_event_sequence_labeled.set((Normal_crop_event_sequence) combobox_adjustment_crop_event   ->ItemIndex);
         adjustment->begin_sync.thermal_time = adjustment_thermal_time;
         adjustment->begin_sync.days_offset  = adjustment_offset;
         std::wstring adjustment_variableW(combobox_adjustment_variable->Text.c_str());
         std::string adjustment_variable; CORN::wstring_to_string(adjustment_variableW,adjustment_variable);
         size_t left_brace_pos = adjustment->parameter.find("[");
         if (left_brace_pos != std::string::npos) // Trim off the descriptive text
         {  std::string actual_parameter(adjustment->parameter,left_brace_pos);
            size_t right_brace_pos = adjustment->parameter.find("]");
            actual_parameter.resize(right_brace_pos+1);
            adjustment->parameter = actual_parameter;
         }
         float32 value =
            CORN::wstr_to_float64(edit_adjustment_value->Text.c_str());
         adjustment->value =CORN::float32_to_cstr(value,5);
      }
      checklistbox_adjustments->Update();
   } else button_adjustment_addClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_adjustment_deleteClick(TObject *Sender)
{  checklistbox_adjustments->delete_selected();                                  //140416
}
//---------------------------------------------------------------------------
void TCrop_editor_form::add_adjustment
(  Synchronization_mode       sync_mode
,  Normal_crop_event_sequence event_sequence
,  nat32 offset
,  nat32 thermal_time
,  const char * parameter
,  float32 value)
{  CropSyst::Crop_parameters::Adjustment_event *adjustment = new CropSyst::Crop_parameters::Adjustment_event;
   adjustment->begin_sync.sync_mode_labeled.set(sync_mode);
   adjustment->begin_sync.normal_crop_event_sequence_labeled.set(event_sequence);
   adjustment->begin_sync.thermal_time = thermal_time;
   adjustment->begin_sync.days_offset = offset;
   adjustment->parameter = parameter;
   adjustment->value =CORN::float32_to_cstr(value,5);
   crop->adjustments.append(adjustment);
   checklistbox_adjustments->Update();
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_add_temperature_stress_periodClick(TObject *Sender)
{  CropSyst::Crop_parameters::Harvest::Grain_stress_sensitivity_period  *sensitivity_period = new CropSyst::Crop_parameters::Harvest::Grain_stress_sensitivity_period;
   sensitivity_period->copy_from(crop->harvest.editor_grain_stress_sensitivity_period);
   sensitivity_period->begin_sync.sync_mode_labeled.set((Synchronization_mode)
            (Synchronization_mode)(pagecontrol_grain_stress_period->ActivePageIndex == 1) ? THERMAL_TIME_MODE : AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);
   sensitivity_period->begin_sync.normal_crop_event_sequence_labeled.set((Normal_crop_event_sequence) combobox_stress_period->ItemIndex);
   crop->harvest.grain_stress_sensitivity_periods.append(sensitivity_period);
   listbox_harvest_temperature_stress_events->Update();
   groupbox_flowering_stress->Visible = true;                                    //150519
}
//_2013-04-28___________________________________________________________________
void TCrop_editor_form::replace_harvest_grain_stress_sensitivity(int replacing_item)
{  if (replacing_item >= 0)
   {  CropSyst::Crop_parameters::Harvest::Grain_stress_sensitivity_period *sensitivity_period
         = dynamic_cast<CropSyst::Crop_parameters::Harvest::Grain_stress_sensitivity_period *>(crop->harvest.grain_stress_sensitivity_periods.get_at(replacing_item));
      if (sensitivity_period)
      {  sensitivity_period->begin_sync.sync_mode_labeled.set((Synchronization_mode)
            (Synchronization_mode)(pagecontrol_grain_stress_period->ActivePageIndex == 1) ? THERMAL_TIME_MODE : AFTER_NORMAL_CROP_GROWTH_STAGE_MODE);
         sensitivity_period->copy_from(crop->harvest.editor_grain_stress_sensitivity_period);
         sensitivity_period->begin_sync.normal_crop_event_sequence_labeled.set((Normal_crop_event_sequence) combobox_stress_period  ->ItemIndex);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_replace_temperature_stress_periodClick(TObject *Sender)
{  int replacing_item = listbox_harvest_temperature_stress_events->ItemIndex;
   if (replacing_item >= 0)
   {  replace_harvest_grain_stress_sensitivity(replacing_item);
      listbox_harvest_temperature_stress_events->Update();
   } else button_add_temperature_stress_periodClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_delete_temperature_stress_periodClick(TObject *Sender)
{
   listbox_harvest_temperature_stress_events->delete_selected();                 //140416
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_upgrade_limitation_temperaturesClick(TObject *Sender)
{  // Only in V4
   #if (CROPSYST_VERSION == 4)
   if (crop)
       crop->biomass_production.opt_mean_temperature_for_growth_V4 = 0.0;
   groupbox_temperature_limit_new->Visible = true;                               //130513
   edit_opt_temp_for_growth->Enabled = false;
   button_upgrade_limitation_temperatures->Caption = "Upgraded";
   #endif
}
//_2013-05-13___________________________________________________________________
void __fastcall TCrop_editor_form::button_sunriseClick(TObject *Sender)
{  crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_initial_hour = 99;
   Update();
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_arbitraryClick(TObject *Sender)
{  crop->harvest.editor_grain_stress_sensitivity_period.heat.exposure_initial_hour = 6;
   Update();
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_defaults_C3Click(TObject *Sender)
{
   crop->CO2_response.non_rectagular_hyperbola_solution.alpha                   = 0.003836;  edit_CO2_alpha->Update();
   crop->CO2_response.non_rectagular_hyperbola_solution.theta                   = 0.9909;    edit_CO2_theta->Update();
   crop->CO2_response.non_rectagular_hyperbola_solution.growth_ratio_asymptotic = 1.26025;   edit_CO2_growth_ratio_asymptotic->Update();
}
//---------------------------------------------------------------------------
void __fastcall TCrop_editor_form::button_defaults_C4Click(TObject *Sender)
{
   crop->CO2_response.non_rectagular_hyperbola_solution.alpha                   = 0.0038;        ; edit_CO2_alpha->Update();
   crop->CO2_response.non_rectagular_hyperbola_solution.theta                   = 0.977;         ; edit_CO2_theta->Update();
   crop->CO2_response.non_rectagular_hyperbola_solution.growth_ratio_asymptotic = 1.0627;        ; edit_CO2_growth_ratio_asymptotic->Update();
}
//---------------------------------------------------------------------------
//051206 1070 lines
//051207  823 lines
//070820 1095 lines
//090721 1467 lines
//100513 1132 lines
//130318  400 lines
//130428  600 lines


