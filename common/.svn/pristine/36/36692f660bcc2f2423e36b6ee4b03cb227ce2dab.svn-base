//---------------------------------------------------------------------------

#ifndef form_geolocation_VCL_RSH
#define form_geolocation_VCL_RSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <RNAutoFloatEdit.h>
#include <RNAutoIntegerEdit.h>
#include <RNAutoStringEdit.h>
#include "AdvEdit.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
//#include <corn/string/ustring.h>
//---------------------------------------------------------------------------
class Geolocation;
class Tgeolocation_form : public TForm
{
__published:	// IDE-managed Components
   TPageControl *geolocation_pagecontrol;
   TTabSheet *position_tabsheet;
   TTabSheet *region_tabsheet;
   TRNAutoStringEdit *country_name_edit;
   TLabel *country_label;
   TLabel *state_label;
   TRNAutoStringEdit *state_code_edit;
   TLabel *Label1;
   TRNAutoStringEdit *county_code_edit;
   TComboBox *country_ISO3166_code_combobox;
   TComboBox *US_state_FIPS_combobox;
   TComboBox *county_code_combobox;
   TTabSheet *station_tabsheet;
   TRNAutoStringEdit *station_ID_code_edit;
   TRNAutoStringEdit *station_name_edit;
   TLabel *station_ID_code_label;
   TLabel *station_name_label;
   TEdit *station_number_edit;
   TLabel *station_number_label;
   TLabel *elevation_label;
   TRNAutoFloatEdit *elevation_edit;
   TLabel *Label8;
   TLabel *screening_height_label;
   TRNAutoFloatEdit *screening_height_edit;
   TLabel *Label9;
   TPageControl *coordinates_pagecontrol;
   TTabSheet *coord_DMS_tabsheet;
   TTabSheet *coord_dec_deg_tabsheet;
   TTabSheet *coord_UTM_tabsheet;
   TLabel *latitude_DMS_label;
   TRNAutoIntegerEdit *lat_deg_edit;
   TLabel *Label55;
   TRNAutoIntegerEdit *lat_min_edit;
   TLabel *Label56;
   TRNAutoFloatEdit *lat_sec_edit;
   TLabel *Label57;
   TComboBox *lat_dir_combobox;
   TRNAutoIntegerEdit *long_deg_edit;
   TLabel *Label58;
   TRNAutoIntegerEdit *long_min_edit;
   TLabel *Label59;
   TRNAutoFloatEdit *long_sec_edit;
   TLabel *Label60;
   TComboBox *long_dir_combobox;
   TLabel *longitude_DMS_label;
   TLabel *Label4;
   TRNAutoFloatEdit *latitude_decdeg_edit;
   TLabel *Label5;
   TLabel *Label7;
   TRNAutoFloatEdit *longitude_decdeg_edit;
   TLabel *Label6;
   TLabel *Label2;
   TRNAutoFloatEdit *utm_northing_edit;
   TLabel *utm_northing_units;
   TLabel *utm_zone_label;
   TRNAutoIntegerEdit *utm_zone_edit;
   TEdit *utm_zone_desg_edit;
   TLabel *Label3;
   TRNAutoFloatEdit *utm_easting_edit;
   TLabel *utm_easting_label;
   TGroupBox *groupbox_description;
   TRNAutoStringEdit *description_edit;
   TBitBtn *button_google_maps;
   void __fastcall latitude_degminsec_onexit(TObject *Sender);
   void __fastcall longitude_degmin_sec_onexit(TObject *Sender);
   void __fastcall latitude_decdeg_onexit(TObject *Sender);
   void __fastcall longitude_decdeg_onexit(TObject *Sender);
   void __fastcall country_ISO3166_code_combobox_onchange(TObject *Sender);
   void __fastcall US_state_FIPS_combobox_onchange(TObject *Sender);
   void __fastcall station_number_edit_onchange(TObject *Sender);
   void __fastcall utm_onexit(TObject *Sender);

   void __fastcall button_google_mapsClick(TObject *Sender);

private: // User declarations
   float32 deg_minute_second_to_dec_deg(int16 deg,int16 min, int16 sec,bool east_or_north) const;
   void dec_deg_to_deg_minute_second(float32 dec_dec, int16 &deg,int16 &min, float32 &sec,bool &east_or_north) const;

   Geolocation *geolocation_parameters;
   int16 long_deg;int16 long_min;float32 long_sec; // Used for deg min sec input mode
   int16 lat_deg; int16 lat_min; float32 lat_sec;

   float32  utm_northing;
   float32  utm_easting;
   int16    utm_zone;

public: // User declarations
   __fastcall Tgeolocation_form(TComponent* Owner);
   void bind_to(Geolocation *geolocation_params,std::string *description);
   virtual void __fastcall Update();
private:
   void show_hide_controls();
   void update_UTM();
   #include "common/geodesy/GUI/form_geolocation_common_inc.h"

};
//---------------------------------------------------------------------------
extern PACKAGE Tgeolocation_form *geolocation_form;
//---------------------------------------------------------------------------
#endif
