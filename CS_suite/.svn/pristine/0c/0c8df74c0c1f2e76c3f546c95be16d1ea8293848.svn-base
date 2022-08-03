#ifndef form_crop_editorH
#define form_crop_editorH
#if ((__BCPLUSPLUS__ > 0x0600) && (__BCPLUSPLUS__ < 0x0630))
   // Currently this form has only been tested with
#else
   #error This form has been designed with RadStudio VCL 2010. It is not know if it is compatible with XE
#endif
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvGroupBox.hpp"
#include "RNAutoBitCheckListBox.h"
#include "RNAutoCheckBox.h"
#include "RNAutoFloatEdit.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "RNAutoDateButton.h"
#include <Buttons.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
#include "CS_Suite/CropSyst/crop_editor/form_crop_editor_inc.h"
#include "RNAutoComboBox.h"
CROP_EDITOR_INCLUDES_AND_FORWARD_DECLS
//---------------------------------------------------------------------------

class Tcrop_editor_form : public TForm
{
__published:	// IDE-managed Components
   TScrollBox *scrollbox_parameters;
   TAdvGroupBox *groupbox_jumpto;
   TGroupBox *groupbox_classification;
   TGroupBox *groupbox_layout;
   TGroupBox *groupbox_hydrothermal_time;
   TGroupBox *groupbox_thermal_time;
   TGroupBox *groupbox_transpiration;
   TGroupBox *groupbox_attainable_growth;
   TGroupBox *groupbox_canopy;
   TGroupBox *groupbox_phenology;
   TGroupBox *groupbox_vernalization;
   TGroupBox *groupbox_root;
   TGroupBox *groupbox_harvest;
   TGroupBox *groupbox_dormancy;
   TGroupBox *groupbox_senescence;
   TGroupBox *groupbox_hardiness;
   TGroupBox *groupbox_residue;
   TGroupBox *groupbox_nitrogen;
   TGroupBox *groupbox_salinity;
   TGroupBox *groupbox_CO2;
   TGroupBox *groupbox_fruit;
   TGroupBox *groupbox_CROPGRO;
   TGroupBox *groupbox_photoperiod;
   TRNAutoRadioGroup *radiogroup_landuse;
   TRNAutoRadioGroup *radiogroup_life_cycle;
   TRNAutoRadioGroup *radiogroup_photosynthetic;
   TRNAutoRadioGroup *radiogroup_harvested_biomass;
   TRNAutoCheckBox *checkbox_grape;
   TRNAutoCheckBox *checkbox_tea;
   TLabel *note_harvested_biomass;
   TRNAutoRadioGroup *radiogroup_photoperiod_consideration;
   TGroupBox *groupbox_photoperiod_daylength;
   TLabel *caption_at_which_stopped;
   TLabel *caption_at_which_constrained;
   TRNAutoParameterEditBar *edit_stop_daylength;
   TRNAutoParameterEditBar *edit_constrained_daylength;
   TRNAutoParameterEditBar *edit_initial_reserves_release_rate;
   TRNAutoParameterEditBar *edit_initial_fruit_mass;
   TRNAutoParameterEditBar *edit_fruit_fract_total_solids;
   TRNAutoParameterEditBar *edit_fruit_load_max;
   TGroupBox *groupbox_nitrogen_demand;
   TGroupBox *groupbox_nitrogen_uptake;
   TRNAutoParameterEditBar *edit_demand_adjust;
   TRNAutoParameterEditBar *edit_N_max_stubble;
   TRNAutoParameterEditBar *edit_root_N_conc;
   TRNAutoParameterEditBar *edit_PAW_where_N_uptake_rate_decreases;
   TRNAutoParameterEditBar *edit_residual_N_not_available_for_uptake;
   TRNAutoParameterEditBar *edit_N_max_daily_uptake_rate;
   TRNAutoParameterEditBar *edit_soil_N_conc_where_N_uptake_decreases;
   TPanel *panel_residue_1;
   TPanel *panel_residue_2;
   TRNAutoRadioGroup *radiogroup_RULSE2_residue_type;
   TPanel *residue_panel_1A;
   TRNAutoParameterEditBar *edit_carbon_fraction;
   TRNAutoParameterEditBar *edit_surface_area_covered_to_mass_ratio;
   TRNAutoParameterEditBar *edit_stubble_area_covered_to_mass_ratio;
   TLabel *Label1;
   TLabel *Label4;
   TLabel *Label14;
   TLabel *Label18;
   TLabel *Label15;
   TLabel *Label19;
   TLabel *Label16;
   TLabel *Label20;
   TLabel *Label21;
   TRNAutoFloatEdit *edit_fast_cycling_top_fraction;
   TRNAutoFloatEdit *edit_slow_cycling_top_fraction;
   TRNAutoFloatEdit *edit_lignified_top_fraction;
   TRNAutoFloatEdit *top_biomass_checksum;
   TRNAutoFloatEdit *edit_fast_cycling_root_fraction;
   TRNAutoFloatEdit *edit_slow_cycling_root_fraction;
   TRNAutoFloatEdit *edit_lignified_root_fraction;
   TRNAutoFloatEdit *root_biomass_checksum;
   TPanel *panel_residue_advanced;
   TRNAutoFloatEdit *edit_fast_cycling_decomposition_time_50;
   TRNAutoFloatEdit *edit_slow_cycling_decomposition_time_50;
   TRNAutoFloatEdit *edit_lignified_decomposition_time_50;
   TLabel *Label7;
   TRNAutoFloatEdit *edit_fast_cycling_C_N_ratio;
   TRNAutoFloatEdit *edit_slow_cycling_C_N_ratio;
   TRNAutoFloatEdit *edit_lignified_C_N_ratio;
   TRNAutoParameterEditBar *edit_detrition_time;
   TRNAutoCheckBox *checkbox_sensitive_to_cold;
   TGroupBox *groupbox_cold_temperature_sensitivity;
   TGroupBox *groupbox_hardiness_fruit;
   TRNAutoParameterEditBar *edit_damage_cold_temperature;
   TRNAutoParameterEditBar *edit_lethal_cold_temperature;
   TRNAutoParameterEditBar *edit_salvageable_days_before_maturity;
   TRNAutoFloatEdit *edit_hardiness_fruit_damage;
   TRNAutoFloatEdit *edit_hardiness_fruit_lethal;
   TLabel *Label3;
   TRNAutoParameterEditBar *edit_CO2_baseline_reference_conc;
   TRNAutoParameterEditBar *edit_CO2_elevated_reference_conc;
   TRNAutoParameterEditBar *edit_CO2_growth_ratio_elevated_to_baseline;
   TLabel *Label28;
   TRNAutoParameterEditBar *edit_salt_tolerance_P;
   TRNAutoParameterEditBar *edit_osmotic_pot_50;
   TLabel *Label29;
   TRNAutoCheckBox *checkbox_senesces;
   TLabel *label_senescence_perennial;
   TGroupBox *groupbox_LAI_duration;
   TRNAutoParameterEditBar *edit_leaf_duration_sensitivity_stress;
   TRNAutoParameterEditBar *edit_deg_day_leaf_duration;
   TRNAutoRadioGroup *radiogroup_absission;
   TRNAutoParameterEditBar *edit_linger;
   TRNAutoParameterEditBar *edit_at_pt_root_limit;
   TRNAutoParameterEditBar *edit_root_density_distribution_curvature;
   TRNAutoParameterEditBar *edit_surface_root_density;
   TRNAutoParameterEditBar *edit_root_length_per_unit_mass;
   TRNAutoParameterEditBar *edit_max_root_depth;
   TRNAutoParameterEditBar *edit_HI_unstressed;
   TPageControl *page_control_harvest;
   TTabSheet *tabsheet_harvest_grain;
   TTabSheet *tabsheet_harvest_tuber;
   TTabSheet *tabsheet_harvest_fruit;
   TGroupBox *groupbox_harvest_sensitivity;
   TRNAutoParameterEditBar *edit_HI_filling_sensitivity_obsolete;
   TRNAutoParameterEditBar *edit_HI_flowering_sensitivity;
   TRNAutoParameterEditBar *edit_grain_translocation_fraction;
   TRNAutoParameterEditBar *RNAutoParameterEditBar4_obsolete;
   TRNAutoParameterEditBar *edit_HI_flowering_temperature_sensitivity;
   TRNAutoParameterEditBar *edit_HI_filling_duration_obsolete;
   TRNAutoParameterEditBar *edit_HI_tuber_init_sensitivity;
   TRNAutoParameterEditBar *edit_HI_tuber_growth_sensitivity;
   TRNAutoParameterEditBar *edit_harvest_temperature;
   TRNAutoParameterEditBar *edit_harvest_temperature_days;
   TLabel *Label6;
   TGroupBox *groupbox_harvest_DOY;
   TRNAutoParameterEditBar *edit_harvest_DOY_earliest;
   TRNAutoParameterEditBar *edit_harvest_DOY_latest;
   TGroupBox *groupbox_orientation;
   TGroupBox *groupbox_canopy_characteristics;
   TRNAutoParameterEditBar *edit_tree_spacing;
   TRNAutoParameterEditBar *edit_row_spacing;
   TRNAutoParameterEditBar *edit_row_azimuth;
   TRNAutoParameterEditBar *edit_final_row_height;
   TRNAutoParameterEditBar *edit_final_tree_breadth;
   TRNAutoParameterEditBar *edit_final_row_width;
   TRNAutoFloatEdit *edit_initial_row_width;
   TRNAutoFloatEdit *edit_initial_tree_breadth;
   TRNAutoFloatEdit *edit_initial_row_height;
   TLabel *Label5;
   TLabel *Label8;
   TRNAutoParameterEditBar *edit_branch_insertion_height;
   TRNAutoRadioGroup *radiogroup_emergence_model;
   TRNAutoParameterEditBar *edit_b;
   TRNAutoParameterEditBar *edit_a;
   TRNAutoParameterEditBar *edit_stdev_base_soil_water_pot;
   TRNAutoParameterEditBar *edit_mean_base_soil_water_pot;
   TRNAutoParameterEditBar *edit_germination_base_temperature;
   TRNAutoParameterEditBar *edit_seedling_leaf_area;
   TRNAutoRadioGroup *radiogroup_resolution;
   TRNAutoParameterEditBar *edit_max_water_uptake_mm;
   TRNAutoParameterEditBar *edit_wilt_leaf_water_pot;
   TRNAutoParameterEditBar *edit_leaf_water_pot_stomatal_closure;
   TRNAutoParameterEditBar *edit_ET_crop_coef;
   TRNAutoParameterEditBar *edit_kc;
   TPageControl *pagecontrol_season_dormancy_mode;
   TTabSheet *tabsheet_single_season;
   TTabSheet *tabsheet_multiple_season;
   TTabSheet *tabsheet_dormancy;
   TGroupBox *groupbox_inactive_period;
   TEdit *Edit1;
   TLabel *label_single_season_mode_1;
   TLabel *label_single_season_mode_2;
   TLabel *label_multiple_season_mode_1;
   TLabel *label_multiple_season_mode_2;
   TLabel *label_dormancy_mode;
   TGroupBox *groupbox_chill_requirements;
   TRNAutoParameterEditBar *edit_dormancy_senesce;
   TRNAutoParameterEditBar *edit_chill_threshold;
   TRNAutoParameterEditBar *edit_deg_day_bud_break_chill_req_not_sat;
   TRNAutoParameterEditBar *edit_deg_day_bud_break_chill_req_sat;
   TRNAutoParameterEditBar *edit_chill_requirement;
   TLabel *label_inactivity_days_note;
   TRNAutoParameterEditBar *edit_consider_inactive_days;
   TRNAutoParameterEditBar *edit_inducement_temperature;
   TPanel *panel_leave_valid_date;
   TPanel *panel_start_valid_date;
   TRNAutoDateButton *button_start_valid_date;
   TRNAutoDateButton *button_leave_valid_date;
   TRNAutoCheckBox *checkbox_vernalization;
   TRNAutoParameterEditBar *edit_vern_end;
   TRNAutoParameterEditBar *edit_vern_start;
   TRNAutoParameterEditBar *edit_vern_high_temp;
   TRNAutoParameterEditBar *edit_vern_low_temp;
   TRNAutoParameterEditBar *edit_vern_min_factor;
   TPanel *Panel1;
   TRNAutoCheckBox *checkbox_clipping_resets;
   TRNAutoParameterEditBar *edit_phenologic_sensitivity_water_stress;
   TRNAutoParameterEditBar *edit_deg_day_begin_maturity;
   TRNAutoParameterEditBar *edit_deg_day_begin_rapid_fruit_growth;
   TRNAutoParameterEditBar *edit_deg_day_begin_filling_grain_or_fruit;
   TRNAutoParameterEditBar *edit_deg_day_begin_flower;
   TRNAutoParameterEditBar *edit_deg_day_end_vegetative_growth;
   TRNAutoParameterEditBar *edit_max_root_depth_dd;
   TRNAutoParameterEditBar *edit_deg_day_tuber_initiation;
   TRNAutoParameterEditBar *edit_deg_day_emerge;
   TPanel *panel_maturity_significant;
   TRNAutoCheckBox *checkbox_maturity_significant;
   TRNAutoRadioGroup *radiogroup_canopy_growth;
   TScrollBox *ScrollBox2;
   TRNAutoParameterEditBar *edit_LWP_that_reduces_canopy_expansion;
   TRNAutoParameterEditBar *edit_LWP_that_stops_canopy_expansion;
   TPanel *panel_leaf_area_index_based;
   TRNAutoParameterEditBar *edit_initial_GAI;
   TRNAutoParameterEditBar *edit_regrowth_GAI;
   TRNAutoParameterEditBar *edit_specific_leaf_area;
   TRNAutoParameterEditBar *edit_fract_LAI_mature;
   TRNAutoParameterEditBar *edit_stem_leaf_partition;
   TPanel *panel_canopy_cover_based;
   TRNAutoParameterEditBar *edit_canopy_cover_initial;
   TRNAutoParameterEditBar *edit_canopy_cover_maximum;
   TRNAutoParameterEditBar *edit_canopy_cover_green_mature;
   TRNAutoParameterEditBar *edit_canopy_cover_total_mature;
   TRNAutoParameterEditBar *edit_RTT_at_half_CCmax;
   TRNAutoParameterEditBar *edit_begin_senescence_deg_day;
   TRNAutoParameterEditBar *edit_max_LAI;
   TGroupBox *groupbox_transpiration_dependent_growth;
   TGroupBox *groupbox_seasonal_adjustment;
   TGroupBox *groupbox_radiation_dependent_growth;
   TRNAutoCheckBox *checkbox_WUE_changes;
   TRNAutoParameterEditBar *edit_WUE_change_deg_day;
   TRNAutoRadioGroup *radiogroup_WUE_submodel;
   TScrollBox *scrollbox_WUE;
   TGroupBox *groupbox_tanner_sinclair;
   TGroupBox *groupbox_aquacrop;
   TGroupBox *groupbox_TUE_curve;
   TRNAutoParameterEditBar *edit_reference_biomass_transp_coef_0;
   TRNAutoParameterEditBar *edit_water_productivity;
   TRNAutoParameterEditBar *edit_TUE_scaling_coef;
   TRNAutoParameterEditBar *edit_TUE_at_1kPa_VPD;
   TRNAutoFloatEdit *edit_reference_biomass_transp_coef_vegetative_0;
   TRNAutoFloatEdit *edit_water_productivity_vegetative;
   TRNAutoFloatEdit *edit_TUE_at_1kPa_VPD_vegetative;
   TRNAutoFloatEdit *edit_TUE_scaling_coef_vegetative;
   TRNAutoParameterEditBar *edit_opt_temp_for_growth;
   TRNAutoParameterEditBar *edit_RUE_global_basis;
   TLabel *Label9;
   TRNAutoParameterEditBar *edit_seasonal_adjustment_1;
   TRNAutoParameterEditBar *edit_seasonal_adjustment_2;
   TRNAutoParameterEditBar *edit_seasonal_adjustment_3;
   TRNAutoParameterEditBar *edit_seasonal_adjustment_4;
   TRNAutoParameterEditBar *edit_seasonal_adjustment_5;
   TLabel *label_seasonal_adjustment;
   TPanel *panel_GGD_ranges;
   TRNAutoParameterEditBar *edit_base_temp;
   TRNAutoParameterEditBar *edit_opt_temp;
   TRNAutoParameterEditBar *edit_max_temp;
   TRNAutoParameterEditBar *edit_cutoff_temp;
   TRNAutoCheckBox *button_nitrogen_fixation;
   TPanel *panel_grape_or_other;
   TGroupBox *groupbox_fruit_grape;
   TRNAutoParameterEditBar *edit_clusters_per_vine;
   TRNAutoParameterEditBar *edit_berries_per_cluster;
   TGroupBox *groupbox_grape;
   TRNAutoParameterEditBar *RNAutoParameterEditBar5;
   TRNAutoParameterEditBar *RNAutoParameterEditBar6;
   TGroupBox *groupbox_fruit_other;
   TRNAutoParameterEditBar *edit_fruits_per_tree;
   TRNAutoRadioGroup *radiogroup_stem_type;
   TRNAutoRadioGroup *radiogroup_nitrogen_leaf_stress_mode;
   TScrollBox *scrollbox_jumpto;
   TRNAutoRadioGroup *radiogroup_crop_model;
   TRNAutoBitCheckListBox *checklistbox_view_panels;
   TGroupBox *groupbox_defaults;
   TLabel *Label2;
   TLabel *Label24;
   TLabel *Label25;
   TComboBox *crop_class_combobox;
   TButton *button_calibrate;
   TGroupBox *groupbox_max_water_uptake;
   TRNAutoParameterEditBar *edit_max_water_upake_before_fruit;
   TRNAutoParameterEditBar *edit_max_water_uptake_during_intial_fruit;
   TRNAutoParameterEditBar *edit_max_water_uptake_during_rapid_fruit;
   TRNAutoParameterEditBar *edit_max_water_uptake_during_veraison;
   TRNAutoParameterEditBar *edit_max_water_uptake_after_maturity;
   TRNAutoComboBox *combobox_RUSLE2_description;
   TLabel *label_must_not_be_less_than_base_temperature;
   TPanel *panel_harvest_fruit;
   TRNAutoRadioGroup *radiogroup_fruit_harvest_condition;
   TRNAutoCheckBox *checkbox_HI_adjustments;
   TTabSheet *tabsheet_harvest_other;
   TRNAutoParameterEditBar *edit_HI_growth_sensitivity;
   void __fastcall radiogroup_resolutionClick(TObject *Sender);
   void __fastcall update_root_biomass_checksum(TObject *Sender);
   void __fastcall update_top_biomass_checksum(TObject *Sender);
   void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall checkbox_grapeClick(TObject *Sender);
   void __fastcall radiogroup_life_cycleClick(TObject *Sender);
   void __fastcall radiogroup_emergence_modelClick(TObject *Sender);
   void __fastcall checkbox_maturity_significantClick(TObject *Sender);
   void __fastcall radiogroup_WUE_submodelClick(TObject *Sender);
   void __fastcall radiogroup_max_RUE_modeClick(TObject *Sender);
   void __fastcall radiogroup_absissionClick(TObject *Sender);
   void __fastcall radiogroup_photoperiod_considerationClick(TObject *Sender);
   void __fastcall pagecontrol_season_dormancy_modeChange(TObject *Sender);
   void __fastcall radiogroup_crop_modelClick(TObject *Sender);
   void __fastcall checkbox_vernalizationClick(TObject *Sender);
   void __fastcall radiogroup_harvested_biomassClick(TObject *Sender);
   void __fastcall checkbox_sensitive_to_coldClick(TObject *Sender);
   void __fastcall checklistbox_view_panelsClick(TObject *Sender);
   void __fastcall checklistbox_view_panelsClickCheck(TObject *Sender);
   void __fastcall radiogroup_canopy_growthClick(TObject *Sender);
   void __fastcall button_calibrateClick(TObject *Sender);
   void __fastcall combobox_RUSLE2_descriptionChange(TObject *Sender);
   void __fastcall checkbox_HI_adjustmentsClick(TObject *Sender);
private: // User declarations
public: // User declarations
   __fastcall Tcrop_editor_form(TComponent* Owner);
      Tcrop_editor_form_USER_DECLARATIONS
public:
   inline virtual TPageControl *get_main_page_control() const { return 0;};
};
//---------------------------------------------------------------------------
extern PACKAGE Tcrop_editor_form *crop_editor_form;
//---------------------------------------------------------------------------
#endif
