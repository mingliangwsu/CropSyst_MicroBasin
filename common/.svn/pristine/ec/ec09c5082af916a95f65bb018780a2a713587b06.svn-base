//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
#include "geolocation_frm.h"
#ifndef GEOLOCATION_H
#  include <common/geolocation/geolocation.h>
#endif
#ifndef GEOLOCATION_UTM_H
#  include <common/geolocation/UTM.h>
#endif

#include <corn/string/strconv.h>
#include <corn/string/ustring.h>
//______________________________________________________________________________
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16Edit"
#pragma link "AutoStringEdit"
#pragma link "AdvEdit"
#pragma resource "*.dfm"
Tgeolocation_form *geolocation_form;
//______________________________________________________________________________
__fastcall Tgeolocation_form::Tgeolocation_form(TComponent* Owner)
: TForm(Owner)
, geolocation_parameters(0)
//, utm_zone_designator("Z")
{}
//______________________________________________________________________________
void __fastcall Tgeolocation_form::latitude_degminsec_onexit(TObject */*Sender unused*/)
{  handle_latitude_degminsec_onexit();
}
//______________________________________________________________________________
void __fastcall Tgeolocation_form::longitude_degmin_sec_onexit(TObject */*Sender unused*/)
{   handle_longitude_degmin_sec_onexit();
}
//______________________________________________________________________________
void __fastcall Tgeolocation_form::utm_onexit(TObject *Sender)
{  handle_utm_onexit();
};

//______________________________________________________________________________
void __fastcall Tgeolocation_form::latitude_decdeg_onexit(TObject */*Sender unused*/)
{  handle_latitude_decdeg_onexit();
}
//______________________________________________________________________________
void __fastcall Tgeolocation_form::country_ISO3166_code_combobox_onchange(TObject *Sender)
{  handle_country_ISO3166_code_combobox_onchange();
}
//______________________________________________________________________________
void __fastcall Tgeolocation_form::US_state_FIPS_combobox_onchange(TObject *Sender)
{  handle_US_state_FIPS_combobox_onchange();
}
//______________________________________________________________________________
void __fastcall Tgeolocation_form::button_google_mapsClick(TObject *Sender)
{  handle_button_google_mapsClick();
}
//______________________________________________________________________________

