//---------------------------------------------------------------------------

#ifndef form_soil_editorH
#define form_soil_editorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoFloat32Edit.h"
#include "AutoFloat32EditBar.h"
#include "AutoInt16EditBar.h"
#include "AutoRadioGroup.h"
#include "AutoStringEdit.h"
//obs #include "SoilProfileFloat32Edit.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//obs #include <SoilProfileFloat32Edit.h>
//#include "AutoRadioGroup.h"
//#include "AutoStringEdit.h"
//#include <Buttons.hpp>
//#include <ComCtrls.hpp>
//#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "AdvCombo.hpp"
#include "AutoFileEditBar.h"
//checkneeded #include "dblucomb.hpp"
#include "Lucombo.hpp"
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include "Data_table_dataset.h"
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "AdvGrid.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
#include "Single_datarec_dataset.h"
#include "AutoContainerComboBox.h"
#include "AutoCheckBox.h"
#include "AdvDirectoryEdit.hpp"
#include "AdvEdBtn.hpp"
#include "AdvEdit.hpp"
#include "AutoInt16Edit.h"
//---------------------------------------------------------------------------
#include "CS_Suite/CropSyst/soil_editor/form_soil_editor_inc.h"
SOIL_EDITOR_INCLUDES_AND_FORWARD_DECLS
/*101014 moved to  SOIL_EDITOR_INCLUDES_AND_FORWARD_DECLS
#include <common/soil/txtrhydr.h>
class Tparameter_file_form;
class Smart_soil_parameters;
namespace CORN
{
   class File_name;
};
*/
/*
class Mapunit_data_record_generator
: public Data_record_generator
{
public:
   virtual CORN::Data_record *create_data_record() ;
   virtual void delete_data_record(CORN::Data_record *data_rec_to_delete) ;
};

class Comp_data_record_generator
: public Data_record_generator
{
public:
   virtual CORN::Data_record *create_data_record() ;
   virtual void delete_data_record(CORN::Data_record *data_rec_to_delete) ;
};
*/
//---------------------------------------------------------------------------
class Tsoil_editor_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *soil_pagecontrol;
   TTabSheet *runoff_tabsheet;
   TTabSheet *erosion_tabsheet;
   TTabSheet *profile_tabsheet;
   TLabel *default_label;
   TLabel *estimated_label;
   TLabel *computed_label;
   TLabel *user_label;
   TGroupBox *curve_number_groupbox;
   TLabel *RUSLE_label;
   TAutoFloat32EditBar *edit_steepness;
   TAutoFloat32EditBar *edit_slope_length;
   TLabel *erosion_note;
   TAutoInt16EditBar *edit_fallow_curve;
   TGroupBox *numerical_groupbox;
   TAutoFloat32EditBar *edit_surface_storage;
   TLabel *numerical_note;
   TTabSheet *surface_tabsheet;
   TAutoFloat32EditBar *edit_albedo_dry;
   TAutoFloat32EditBar *edit_albedo_wet;
   TAutoFloat32EditBar *edit_water_vapor_conductance_atmosphere_adj;
   TLabel *water_vapor_conductance_atmosphere_note;
   TButton *button_albedo_dark;
   TButton *button_albedo_med;
   TButton *button_albedo_light;
   TAutoCheckBox *checkbox_fixed_evap;
   TAdvStringGrid *texture_grid;
   TButton *button_texture;
   TButton *button_hydro_prop;
   TButton *button_chemistry;
   TLabel *jump_to_button;
   TLabel *Label3;
   TAutoCheckBox *checkbox_compute_surface_storage;
   TTabSheet *tabsheet_other;
   TAutoFloat32EditBar *edit_SLPF;
   TLabel *label_install_hydr_prop_calc;
   TButton *button_hydr_prop_calc;
   TAutoInt16Edit *edit_soil_layers;
   TLabel *label_fine_soil_basis;
   TPanel *panel_SCS_hydroXXX;
   TAutoRadioGroup *radiogroup_hydro_group;
   TAutoRadioGroup *radiogroup_hydro_condition;
   TLabel *curve_number_note;
   TAutoInt16EditBar *edit_override_curve_number;
   TLabel *Label2;
   TBitBtn *BitBtn1;
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TLabel *Label4;
   TAutoFloat32Edit *edit_evaporative_layer_thickness_cascade;
   TAutoFloat32Edit *edit_evaporative_layer_thickness_finite_difference;
   void __fastcall FormKeyPress(TObject *Sender, char &Key);
   void __fastcall texture_grid_oncellvalidate(TObject *Sender, int ACol,
          int ARow, AnsiString &Value, bool &Valid);
   void __fastcall button_albedo_dark_onclick(TObject *Sender);
   void __fastcall button_albedo_medclick(TObject *Sender);
   void __fastcall albedo_light_button_onclick(TObject *Sender);
   void __fastcall estimated_label_onclick(TObject *Sender);
   void __fastcall button_select_texture_triangle_onclick(TObject *Sender);
   void __fastcall button_texture_onclick(TObject *Sender);
   void __fastcall button_hydro_propClick(TObject *Sender);
   void __fastcall button_chemistry_onclick(TObject *Sender);
   void __fastcall texture_grid_onautodeleterow(TObject *Sender, int ARow);
   void __fastcall texture_grid_onautoinsertrow(TObject *Sender, int ARow);
   void __fastcall texture_gridClipboardPaste(TObject *Sender,
          bool &Allow);
   void __fastcall texture_gridClipboardBeforePasteCell(TObject *Sender,
          int ACol, int ARow, AnsiString &Value, bool &Allow);
   void __fastcall checkbox_compute_surface_storageClick(TObject *Sender);
   void __fastcall label_install_hydr_prop_calcClick(
          TObject *Sender);
   void __fastcall button_hydr_prop_calcClick(TObject *Sender);
   void __fastcall edit_soil_layers_onexit(TObject *Sender);

public:
   __fastcall Tsoil_editor_form(TComponent* Owner);
public:
   inline virtual TPageControl *get_main_page_control() const { return soil_pagecontrol;};
 private:	// User declarations
   Tsoil_editor_form_USER_DECLARATIONS
};
//---------------------------------------------------------------------------
extern PACKAGE Tsoil_editor_form *soil_editor_form;
//---------------------------------------------------------------------------
#endif
