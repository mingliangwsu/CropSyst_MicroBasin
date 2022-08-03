//______________________________________________________________________________

#include <vcl.h>
#pragma hdrstop

#include "form_operation_event.h"
#include "CropSyst/source/cs_operation.h"
#include "common/simulation/event.h"
#include "corn/OS/file_system_engine.h"
#include "form_event.h"
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoContainerCheckListBox"
#pragma link "AutoContainerComboBox"
#pragma link "AutoStringEdit"
#pragma link "AutoCheckBox"
#pragma link "AutoRadioGroup"
#pragma link "AutoInt16Edit"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoFloat32Edit"
#pragma resource "*.dfm"
Toperation_event_form *operation_event_form;
//______________________________________________________________________________
__fastcall Toperation_event_form::Toperation_event_form(TComponent* Owner)
: TForm(Owner)
,   op_form(0)
,   schedule_form(0)
{}
//______________________________________________________________________________
/*
Event operation editors:

General form for events:
	Primary operational parameters:

	Destination selector:
	  to indicate the target facility of interest.

	Equipment selector:
	  to indicate which machines to use with this operation.

	Event schedule:
	  to specify application date, or period and/or repetitions

	Farmstead selector:
	  to indicate which farmstead(s) to apply or not apply to.



All Build facility events
	Primary model selector: Model selector
	Farmstead selector: yes
		Facilities must be associated with a farmstead.
	Destination selector: Depends on model
		Some facilities can be build within others facilities, or on fields.
	Equipment selector: No
	Event schedule: yes


Target population event
	Primary: population form
	Farmstead selector: yes
	Destination selector: No 
		(this is for whole farm, added animals will be added to
		 the appropriate respective housing).
	Equipment selector: No
	Event schedule: yes

Buy animals event:
	Primary: Group selection form
	Farmstead selector: yes
		Note that the from location is a selection in the group
		(The from location page will be hidden is is assumed
		bought animals will be from exteral sources,
		animals can be sold between farmsteads with the sell event).
		New Animals must be associated with a farmstead.
	Destination: Yes
	Equipment selector: Yes Hauling
	Event schedule: yes

Sell animals event:
	Primary: Group selection form
	Farmstead selector: Yes
		Animals could be sold to another farmstead (if financially independent
		Note that the from location is a selection in the group.
	Destination: Probably, it would be nice to indicate their initial housing.
	Equipment selector: Yes  Hauling .
	Event schedule: yes

Cull animals event:
	Primary: Group selection form
	Farmstead selector:  Yes
		Although a group can specify a farmstead as a from
		location, a generalized group (with from anywhere)
		could be used in conjuction with the farmstead selector.
		The animals selected from location are specified by the group.
	Destination: Probably, it would be nice to indicate their initial housing.
	Equipment selector: Yes, Hauling, Rendering, Disposal
	Event schedule: yes

Group definition event:
	Primary: Group definition form
	Farmstead selector: No
		Group definitions can be applied to any where,
		although the group may specify a farmstead as
		the from location.
	Destination: No
	Equipment selector: No
	Event schedule: yes

Herd route event:
	Primary: Route form         ; // reliquish op
	Farmstead selector: Yes
		Although a group can specify a farmstead as a from
		location, a generalized group (with from anywhere)
		could be used in conjuction with the farmstead selector.
	Destination: No
		One or more destinations may be specified in the route.
	Equipment selector: No
		It is assumed animals will be walked or herded.
      If equipment needs be used to haul animals, use the move event.
	Event schedule: Yes

Set feed ration event:
	Primary: feed ration form (Don't forget group combobox on this form)
	Farmstead selector: Yes
		Although a group can specify a farmstead as a from
		location, a generalized group (with from anywhere)
		could be used in conjuction with the farmstead selector.
	Destination: Yes
		Although feed is feed to groups it is placed in feeding facilites.
	Equipment: Yes (but only feed handling equipment and engines).
	Event schedule: Yes

Set weight gain mode event:
	Primary: weight gain mode form (Don't forget group combobox on this form)
	Farmstead selector: Yes
		Although a group can specify a farmstead as a from
		location, a generalized group (with from anywhere)
		could be used in conjuction with the farmstead selector.
	Destination: no
	Equipment: no
	Event schedule: yes

Set target milk production event:
	Primary: Target milk production form (Don't forget group combobox on this form)
	Farmstead selector: Yes
		Although a group can specify a farmstead as a from
		location, a generalized group (with from anywhere)
		could be used in conjuction with the farmstead selector.
	Destination: no
	Equipment: no
	Event schedule: yes

- - - - - - - - -
Feed move event
	Primary: Feed selector
	Farmstead selector: Yes (source may only specify types of fields or location)
	Destination: Yes
	Equipment:Yes
	Event schedule: Yes

Feed stow harvested yield event
	Primary: Feed selector
	Farmstead: Yes
	Destination: Yes (limit to any feed location)
	Equipment: Yes
	Event schedule: Yes

Feed Treatment event (Separate event will be added as needed)
	Primary: Feed selector
	Farmstead: Yes
	Destination: Yes (include manure storage, compost storage, fields)
	Equipment: Yes
	Event schedule: Yes

Feed Dispose event
	Primary: Feed selector
	Farmstead: Yes
	Destination: Yes (include manure storage, compost storage, fields)
	Equipment: Yes
	Event schedule: Yes

Set ration event(removed moved to herd operation)

Feed Buy event
	Primary: Feed type (commodity) selector
	Farmstead: Yes (specifies which farmstead is doing the purchasing)
	Destination: Yes  (specifies where purchase feed is stored
	Equipment: Yes
	Event schedule: Yes

Feed Sell event	
	Primary: Feed selector
	Farmstead: Yes (specifies which farmstead is doing the purchasing)
	Destination: Yes  (specifies where purchase feed is stored
	Equipment: Yes
	Event schedule: Yes

- - - - - - - - - -

Manure events (similar to feed)
	Collect
	Move
	Apply to field
	Treatment
	Dispose
	Buy (maybe)
	Sell

- - - - - - - - - -
Bedding events (similar to Manure)

- - - - - - - - - -
Milk events (similar to feed)
- - - - - - - - - -
Equipment

Add XXX equipment event:
	Primary: model selector
	Farmstead selector: Yes (must be associated/owned by a farmstead)
	Destination: Yes (Should be installed or stored in a facility
			eventually limit the appropriate type)
	Equipment: Yes (It may be necessary to haul the equipment
			or use equipment to install the new object).
	Event schedule: Yes.



= = = = = = = = = = = = = = = = =
Feed selector may specify anywhere, anywhere on a farmstead,
any field, any feed storage, any type of facility where feed
may be located, a feed type, various feed conditions
(I.e. fresh, spoiled, low quality, high quality, humidity).

Destination selector may specify a off site location (X miles from the farm).
For example sold feed may be transported as seller's expense to the specified location.

*/
//______________________________________________________________________________
void __fastcall Toperation_event_form::bind_to
(Common_event    *_event
,TForm            *_op_form
,bool             associated_with_crop
,bool             enable_decision_support
,bool              enable_CANMS_support
,const char       *_help_html_filename
)
{
   event = _event;
   if (_help_html_filename)
      help_html_filename.set_cstr(_help_html_filename);
   CropSyst::Operation *_op = (CropSyst::Operation  *)_event->get_operation();
   description_edit->bind_to(&(_op->description.brief),0/*no help yet*/);

//   available_equipment = i_available_equipment;
   // OP should be previosly bound to op_form before calling this method
   op_form = _op_form;
   op_form->Parent = op_param_tabsheet;

   op_form->Show();
   op_form->Top = 0;
   op_form->Left = 0;
   op_form->BorderStyle = bsNone;

   schedule_form = new Tevent_editor_form(this);
   schedule_form->Parent = schedule_tabsheet;
   schedule_form->Show();
   schedule_form->Top = 0;
   schedule_form->Left = 0;
   schedule_form->BorderStyle = bsNone;
   schedule_form->Align = alClient;
   schedule_form->bind_to(event,associated_with_crop,enable_decision_support,enable_CANMS_support);
   event_ID_edit->bind_to(&(event->ID),0 /* No help yet*/);


   edit_duration_hours->bind_to(&(_op->duration_hours),0);
   edit_start_hour->bind_to(&(_op->start_hour),0);
   edit_carbon_footprint->bind_to(&(_op->carbon_footprint_kgCO2e_ha),2,0);
};

/*not needed if Ok is not default contrl
void __fastcall Toperation_event_form::FormKeyPress(TObject *Sender,char &Key)
{
   if ((Key == VK_RETURN))
   {
      Key = 0;
      Perform(WM_NEXTDLGCTL,0,0);
   };

}
*/
//____________________________________________________________________bind_to__/

void __fastcall Toperation_event_form::help_button_onclick(TObject *Sender)
{
   CORN::OS::file_system_engine.view_file(help_html_filename);
//150304 help_html_filename.invoke_viewer();
}
//________________________________________________________help_button_onclick__/
void __fastcall Toperation_event_form::FormClose(TObject *Sender,TCloseAction &Action)
{
   bool sync_is_valid = event->begin_sync.is_valid();
   if (!sync_is_valid)
   {
      int result = Application->MessageBox("This operation has not been scheduled on /Schedule\\ page.\nDo you want to schedule this event?\nYes - schedule the event\nNo - the operation will should not be performed","Operation event not schedule",MB_YESNO	);
      if (result == IDYES)
      {  pagecontrol_operation_event->ActivePage = schedule_tabsheet;
         Action = caNone;
      }  else 
         Action = caFree;
   } else
      Action = caFree;
   bool is_period = event->is_period(false);
   if (is_period)
   {
//NYI       event->period->end_sync
   }
}
//__________________________________________________________________FormClose__/

