//---------------------------------------------------------------------------

#ifndef form_geolocationH
#define form_geolocationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <AutoFloat32Edit.h>
#include <AutoFloat32EditBar.h>
#include "AutoInt16Edit.h"
#include "AutoStringEdit.h"
#include "AdvEdit.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Geolocation;
class Tgeolocation_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *geolocation_pagecontrol;
   TTabSheet *position_tabsheet;
   TTabSheet *region_tabsheet;
   TAutoStringEdit *edit_country_name;
   TLabel *country_label;
   TLabel *state_label;
   TAutoStringEdit *edit_state_code;
   TLabel *Label1;
   TAutoStringEdit *edit_county_code;
   TComboBox *combobox_country_ISO3166_code;
   TComboBox *combobox_US_state_FIPS;
   TComboBox *combobox_county_code;
   TTabSheet *station_tabsheet;
   TAutoStringEdit *edit_station_ID_code;
   TAutoStringEdit *edit_station_name;
   TLabel *station_ID_code_label;
   TLabel *station_name_label;
   TEdit *edit_station_number;
   TLabel *station_number_label;
   TLabel *elevation_label;
   TAutoFloat32Edit *edit_elevation;
   TLabel *Label8;
   TLabel *screening_height_label;
   TAutoFloat32Edit *edit_screening_height;
   TLabel *Label9;
   TPageControl *coordinates_pagecontrol;
   TTabSheet *coord_DMS_tabsheet;
   TTabSheet *coord_dec_deg_tabsheet;
   TTabSheet *coord_UTM_tabsheet;
   TLabel *Label4;
   TAutoFloat32Edit *edit_latitude_decdeg;
   TLabel *Label5;
   TLabel *Label7;
   TAutoFloat32Edit *edit_longitude_decdeg;
   TLabel *Label6;
   TLabel *Label2;
   TAutoFloat32Edit *edit_utm_northing;
   TLabel *utm_northing_units;
   TLabel *utm_zone_label;
   TAutoInt16Edit *edit_utm_zone;
   TEdit *edit_utm_zone_desg;
   TLabel *Label3;
   TAutoFloat32Edit *edit_utm_easting;
   TLabel *utm_easting_label;
   TGroupBox *groupbox_description;
   TAutoStringEdit *edit_description;
   TBitBtn *button_google_maps;
   TLabel *label_comment;
   TAutoStringEdit *edit_comment;
   TPanel *panel_latitude;
   TLabel *Label57;
   TLabel *Label56;
   TLabel *Label55;
   TComboBox *combobox_lat_dir;
   TAutoFloat32Edit *edit_lat_sec;
   TAutoInt16Edit *edit_lat_min;
   TAutoInt16Edit *edit_lat_deg;
   TPanel *panel_longitude;
   TAutoInt16Edit *edit_long_deg;
   TLabel *Label58;
   TAutoInt16Edit *edit_long_min;
   TLabel *Label59;
   TAutoFloat32Edit *edit_long_sec;
   TLabel *Label60;
   TComboBox *combobox_long_dir;
   void __fastcall latitude_degminsec_onexit(TObject *Sender);
   void __fastcall longitude_degmin_sec_onexit(TObject *Sender);
   void __fastcall latitude_decdeg_onexit(TObject *Sender);
   void __fastcall longitude_decdeg_onexit(TObject *Sender);
   void __fastcall country_ISO3166_code_combobox_onchange(TObject *Sender);
   void __fastcall US_state_FIPS_combobox_onchange(TObject *Sender);
   void __fastcall station_number_edit_onchange(TObject *Sender);
   void __fastcall utm_onexit(TObject *Sender);
   void __fastcall button_google_mapsClick(TObject *Sender);

private:	// User declarations
   float32 deg_minute_second_to_dec_deg(int16 deg,int16 min, int16 sec,bool east_or_north) const;
   void dec_deg_to_deg_minute_second(float32 dec_dec, int16 &deg,int16 &min, float32 &sec,bool &east_or_north) const;

   Geolocation *geolocation_parameters;
   int16 long_deg;int16 long_min;float32 long_sec; // Used for deg min sec input mode
   int16 lat_deg; int16 lat_min; float32 lat_sec;

   float32  utm_northing;
   float32  utm_easting;
   int16    utm_zone;

public:		// User declarations
   __fastcall Tgeolocation_form(TComponent* Owner);
   void bind_to(Geolocation *geolocation_params/*,CORN::Ustring *description*/);
   virtual void __fastcall Update();
private:
   void show_hide_controls();
   void update_UTM();

};
//---------------------------------------------------------------------------
extern PACKAGE Tgeolocation_form *geolocation_form;
//---------------------------------------------------------------------------
#endif
