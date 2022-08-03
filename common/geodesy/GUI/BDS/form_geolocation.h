//---------------------------------------------------------------------------

#ifndef form_geolocationH
#define form_geolocationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvEdit.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include "C:\dev\components\RNAutoControls\basic\RNAutoFloatEdit.h"
#include "RNAutoIntegerEdit.h"
#include "RNAutoStringEdit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Geolocation;
class Tgeolocation_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *geolocation_pagecontrol;
   TTabSheet *tabsheet_position;
   TTabSheet *tabsheet_region;
   TTabSheet *tabsheet_station;
   TPageControl *coordinates_pagecontrol;
   TTabSheet *tabsheet_coord_DMS;
   TTabSheet *coord_dec_deg_tabsheet;
   TTabSheet *coord_UTM_tabsheet;
   TGroupBox *groupbox_description;
   TBitBtn *button_google_maps;
   TRNAutoStringEdit *edit_description;
   TScrollBox *scrollbox_region;
   TGroupBox *groupbox_country;
   TComboBox *combobox_country_ISO3166_code;
   TRNAutoStringEdit *edit_country_name;
   TGroupBox *groupbox_state_province;
   TComboBox *combobox_US_state_FIPS;
   TRNAutoStringEdit *edit_state_code;
   TGroupBox *groupbox_region;
   TComboBox *combobox_county_code;
   TRNAutoStringEdit *edit_county_code;
   TGroupBox *groupbox_station_number;
   TGroupBox *groupbox_station_ID_code;
   TGroupBox *goupbox_station_name;
   TEdit *edit_station_number;
   TRNAutoStringEdit *edit_station_ID_code;
   TRNAutoStringEdit *edit_station_name;
   TPanel *panel_latitude_DMS;
   TRNAutoIntegerEdit *edit_lat_deg;
   TLabel *Label55;
   TRNAutoIntegerEdit *edit_lat_min;
   TLabel *Label56;
   TRNAutoFloatEdit *edit_lat_sec;
   TComboBox *combobox_lat_dir;
   TPanel *panel_longitude_DMS;
   TRNAutoIntegerEdit *edit_long_deg;
   TLabel *Label58;
   TRNAutoIntegerEdit *edit_long_min;
   TLabel *Label59;
   TRNAutoFloatEdit *edit_long_sec;
   TLabel *Label60;
   TComboBox *combobox_long_dir;
   TPanel *panel_heights;
   TPanel *panel_elevation;
   TLabel *Label8;
   TRNAutoFloatEdit *edit_elevation;
   TPanel *panel_screening_height;
   TLabel *Label9;
   TRNAutoFloatEdit *edit_screening_height;
   TPanel *panel_latitude_DD;
   TRNAutoFloatEdit *edit_latitude_decdeg;
   TLabel *Label5;
   TPanel *panel_longitude_DD;
   TRNAutoFloatEdit *edit_longitude_decdeg;
   TLabel *Label6;
   TPanel *panel_UTM_zone;
   TRNAutoIntegerEdit *edit_UTM_zone;
   TEdit *edit_UTM_zone_desg;
   TPanel *panel_UTM_xxxing;
   TPanel *panel_UTM_northing;
   TLabel *utm_northing_units;
   TRNAutoFloatEdit *edit_utm_northing;
   TPanel *panel_easting;
   TLabel *Label3;
   TRNAutoFloatEdit *edit_utm_easting;
   TLabel *Label1;
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
   void bind_to(Geolocation *geolocation_params,std::string /*CORN::Ustring*/ *description);
   virtual void __fastcall Update();
private:
   void show_hide_controls();
   void update_UTM();

};
//---------------------------------------------------------------------------
extern PACKAGE Tgeolocation_form *geolocation_form;
//---------------------------------------------------------------------------
#endif
