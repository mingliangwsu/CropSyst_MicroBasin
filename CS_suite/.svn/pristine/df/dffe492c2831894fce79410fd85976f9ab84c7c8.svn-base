//---------------------------------------------------------------------------

#ifndef form_operation_eventH
#define form_operation_eventH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AutoContainerCheckListBox.h"
#include "AutoContainerComboBox.h"
#include "AutoStringEdit.h"
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "AutoCheckBox.h"
#include "AutoRadioGroup.h"
#include "AutoInt16Edit.h"
#include "AutoFloat32EditBar.h"
#include "AutoFloat32Edit.h"
//150403 #include <corn/file_sys/smart_filename.h>
//---------------------------------------------------------------------------

// forward declarations:
namespace CORN
{
   class Association_list;
};

class Tevent_editor_form; 
class Tfarmstead_selection_form;

class Common_event;

//---------------------------------------------------------------------------
class Toperation_event_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *pagecontrol_operation_event;
   TTabSheet *op_param_tabsheet;
   TTabSheet *schedule_tabsheet;
   TTabSheet *tabsheet_duration;
   TLabel *label_note_duration;
   TLabel *Label2;
   TPanel *panel_description;
   TAutoStringEdit *description_edit;
   TPanel *panel_buttons;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TBitBtn *help_button;
   TAutoStringEdit *event_ID_edit;
   TPanel *panel_duration;
   TPanel *panel_start_hour;
   TAutoInt16Edit *edit_start_hour;
   TLabel *Label1;
   TAutoInt16Edit *edit_duration_hours;
   TLabel *label_duration_hours;
   TAutoInt16Edit *AutoInt16Edit2;
   TLabel *label_duration_minutes;
   TTabSheet *tabsheet_LCA;
   TPanel *Panel1;
   TAutoFloat32Edit *edit_carbon_footprint;
   TLabel *Label3;
   void __fastcall help_button_onclick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


//obs   void __fastcall FormKeyPress(TObject *Sender, char &Key);

//   void __fastcall required_equipment_checklistbox_onclick(TObject *Sender);

private:	// User declarations

   TForm                      *op_form;
   Tevent_editor_form         *schedule_form;
   CORN::OS::File_name_concrete help_html_filename;
   Common_event               *event;
public:		// User declarations
   __fastcall Toperation_event_form(TComponent* Owner);

   void __fastcall Toperation_event_form::bind_to
   (Common_event     *i_event
   ,TForm            *i_op_form
   ,bool              associated_with_crop
   ,bool              enable_decision_support
   ,bool              enable_CANMS_support
   ,const char       *_help_html_filename
   );
};
//---------------------------------------------------------------------------
extern PACKAGE Toperation_event_form *operation_event_form;
//---------------------------------------------------------------------------
#endif
