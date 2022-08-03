//---------------------------------------------------------------------------

#ifndef form_soil_editorH
#define form_soil_editorH
//---------------------------------------------------------------------------
#include "RNAutoCheckBox.h"
#include "RNAutoIntegerEdit.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RNAutoCheckBox.h"
#include "RNAutoIntegerEdit.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RNAutoCheckBox.h"
#include "RNAutoIntegerEdit.h"
#include "RNAutoParameterEditBar.h"
#include "RNAutoRadioGroup.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RNAutoParameterEditBar.h"
#include <ExtCtrls.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include "RNAutoCheckBox.h"
#include "RNAutoIntegerEdit.h"
#include <Buttons.hpp>
#include <Grids.hpp>
#include "RNAutoRadioGroup.h"
//---------------------------------------------------------------------------
#include "CS_Suite/CropSyst/soil_editor/form_soil_editor_inc.h"
#include "RNAutoRadioGroup.h"
SOIL_EDITOR_INCLUDES_AND_FORWARD_DECLS
//---------------------------------------------------------------------------
class Tsoil_editor_form : public TForm
{
__published:	// IDE-managed Components
   TScrollBox *ScrollBox1;
   TGroupBox *groupbox_surface;
   TPanel *panel_albedo;
   TGroupBox *groupbox_albedo;
   TRNAutoParameterEditBar *edit_albedo_dry;
   TRNAutoParameterEditBar *edit_albedo_wet;
   TPanel *panel_albedo_buttons;
   TButton *button_albedo_dark;
   TButton *button_albedo_med;
   TButton *button_albedo_light;
   TRNAutoParameterEditBar *edit_water_vapor_conductance_atmosphere_adj;
   TLabel *water_vapor_conductance_atmosphere_note;
   TGroupBox *groupbox_runoff;
   TGroupBox *GroupBox3;
   TGroupBox *groupbox_curve_number_notes;
   TLabel *curve_number_note;
   TLabel *Label2;
   TGroupBox *groupbox_numerical_solution_mode;
   TPanel *panel_curve_number_fields;
   TGroupBox *groupbox_hydrologic;
   TGroupBox *GroupBox4;
   TRNAutoParameterEditBar *edit_fallow_curve;
   TRNAutoParameterEditBar *edit_override_curve_number;
   TLabel *numerical_note;
   TRNAutoParameterEditBar *edit_surface_storage;
   TGroupBox *groupbox_RUSLE;
   TRNAutoParameterEditBar *edit_steepness;
   TRNAutoParameterEditBar *edit_slope_length;
   TLabel *erosion_note;
   TRNAutoParameterEditBar *edit_SLPF;
   TGroupBox *groupbox_soil_profile;
   TAdvStringGrid *texture_grid;
   TPanel *panel_profile_notes;
   TRNAutoIntegerEdit *edit_soil_layers;
   TLabel *default_label;
   TLabel *computed_label;
   TLabel *user_label;
   TLabel *estimated_label;
   TLabel *Label3;
   TBitBtn *button_select_texture_triangle;
   TButton *button_hydr_prop_calc;
   TLabel *label_install_hydr_prop_calc;
   TRNAutoRadioGroup *radiogroup_hydro_group;
   TRNAutoRadioGroup *radiogroup_hydro_condition;
   TRNAutoCheckBox *checkbox_fixed_evap;
   TRNAutoCheckBox *checkbox_compute_surface_storage;
   TPanel *panel_jump_to;
   TLabel *Label1;
   TButton *button_texture;
   TButton *button_hydro_prop;
   TButton *button_chemistry;
   TButton *button_surface;
   TButton *button_runoff;
   TButton *button_erosion;
   void __fastcall button_textureClick(TObject *Sender);
   void __fastcall button_hydro_propClick(TObject *Sender);
   void __fastcall button_chemistryClick(TObject *Sender);

   void __fastcall button_runoffClick(TObject *Sender);
   void __fastcall button_erosionClick(TObject *Sender);
   void __fastcall button_albedo_darkClick(TObject *Sender);
   void __fastcall button_albedo_medClick(TObject *Sender);
   void __fastcall button_albedo_lightClick(TObject *Sender);
   void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
   void __fastcall texture_gridAutoDeleteRow(TObject *Sender, int ARow);
   void __fastcall texture_gridAutoInsertRow(TObject *Sender, int ARow);
   void __fastcall texture_gridCellValidate(TObject *Sender, int ACol, int ARow,
          UnicodeString &Value, bool &Valid);
   void __fastcall texture_gridClipboardBeforePasteCell(TObject *Sender, int ACol,
          int ARow, UnicodeString &Value, bool &Allow);
   void __fastcall texture_gridClipboardPaste(TObject *Sender, bool &Allow);
   void __fastcall estimated_labelClick(TObject *Sender);
   void __fastcall button_select_texture_triangleClick(TObject *Sender);
   void __fastcall checkbox_compute_surface_storageClick(TObject *Sender);
   void __fastcall label_install_hydr_prop_calcClick(TObject *Sender);
   void __fastcall button_hydr_prop_calcClick(TObject *Sender);
   void __fastcall edit_soil_layersExit(TObject *Sender);
   void __fastcall button_surfaceClick(TObject *Sender);
private:	// User declarations






   Tsoil_editor_form_USER_DECLARATIONS

public:		// User declarations
   __fastcall Tsoil_editor_form(TComponent* Owner);
public:
   inline virtual TPageControl *get_main_page_control() const { return 0;};
      // The new soil editor doesn't have page control
};
//---------------------------------------------------------------------------
extern PACKAGE Tsoil_editor_form *soil_editor_form;
//---------------------------------------------------------------------------
#endif
