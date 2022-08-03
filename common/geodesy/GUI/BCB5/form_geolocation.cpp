//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "form_geolocation.h"
#ifndef GEOLOCATION_H
#  include <common/geolocation/geolocation.h>
#endif
#ifndef GEOLOCATION_UTM_H
#  include <common/geolocation/UTM.h>
#endif
#include <CropSyst/GUI/help/location.h>

#include <math.h>
#include <corn/string/strconv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AutoFloat32Edit"
#pragma link "AutoFloat32EditBar"
#pragma link "AutoInt16Edit"
#pragma link "AutoStringEdit"
#pragma link "AdvEdit"
#pragma resource "*.dfm"
Tgeolocation_form *geolocation_form;
//---------------------------------------------------------------------------
__fastcall Tgeolocation_form::Tgeolocation_form(TComponent* Owner)
: TForm(Owner)
, geolocation_parameters(0)
//, utm_zone_designator("Z")
{}
//---------------------------------------------------------------------------
void Tgeolocation_form::bind_to
(Geolocation *geolocation_params
//,CORN::Ustring *description          // may be 0
)
{
   geolocation_parameters =geolocation_params;
//   if (description)
      edit_description->bind_to(&(geolocation_params->station_name),HELP_P_loc_description);
//   else
//   {  groupbox_description->Visible = false;
//      geolocation_pagecontrol->Align = alClient;
//   };
   geolocation_parameters->available_data = (avail_geocoordinates|avail_geopolitical_codes|avail_geopolitical_names|avail_station_number|avail_station_name|avail_station_ID_code|avail_comment);

   edit_latitude_decdeg ->bind_to(&geolocation_parameters->latitude_dec_deg_32,8,HELP_P_loc_latitude);
   edit_longitude_decdeg->bind_to(&geolocation_parameters->longitude_dec_deg_32,8,HELP_P_loc_latitude);

//   latitude_edit_bar->bind_to(&geolocation_parameters->v_latitude_dec_deg,HELP_P_loc_latitude);
//   longitude_edit_bar->bind_to(&geolocation_parameters->v_longitude_dec_deg,HELP_P_loc_latitude);
//   elevation_edit_bar->bind_to(&geolocation_parameters->v_elevation,0);
//   screening_height_edit_bar->bind_to(&geolocation_parameters->v_screening_height,HELP_P_loc_windmeasure);
   edit_elevation->bind_to(&geolocation_parameters->elevation,2,0);
   edit_screening_height->bind_to(&geolocation_parameters->screening_height_32,2,HELP_P_loc_windmeasure);

   edit_lat_deg->bind_to(&lat_deg,HELP_P_loc_latitude);
   edit_long_deg->bind_to(&long_deg,HELP_P_loc_latitude);

   edit_lat_min->bind_to(&lat_min,HELP_P_loc_latitude);
   edit_long_min->bind_to(&long_min,HELP_P_loc_latitude);

   edit_lat_sec->bind_to(&lat_sec,4,HELP_P_loc_latitude);
   edit_long_sec->bind_to(&long_sec,4,HELP_P_loc_latitude);

   edit_utm_northing ->bind_to(&utm_northing,8,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);
   edit_utm_easting  ->bind_to(&utm_easting, 8,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);
   edit_utm_zone     ->bind_to(&utm_zone      ,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);
//   utm_zone_designator_edit->bind_to(&utm_zone_designator,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);
//   utm_zone_designator_edit->Text =

//   update_latitude_dec_min_sec(0);
//   update_longitude_dec_min_sec(0);
   latitude_decdeg_onexit(0);
   longitude_decdeg_onexit(0);

   update_UTM();

   edit_country_name ->bind_to(&(geolocation_parameters->country_name),0);
   edit_state_code   ->bind_to(&(geolocation_parameters->state_name),0);
   edit_county_code  ->bind_to(&(geolocation_parameters->county_name),0);

   char buffer[20];
   edit_station_number  ->Text = ltoa(geolocation_parameters->station_number,buffer,10);
   edit_station_ID_code ->bind_to(&(geolocation_parameters->station_ID_code),0);
   edit_station_name    ->bind_to(&(geolocation_parameters->station_name),0);
   edit_comment         ->bind_to(&(geolocation_parameters->comment),0);

   if (geolocation_parameters->country_code_ISO3166)
   {  itoa(geolocation_parameters->country_code_ISO3166,buffer,10);
      combobox_country_ISO3166_code->Text = buffer;
   };
   show_hide_controls();
};
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::latitude_degminsec_onexit(TObject */*Sender unused*/)
{  geolocation_parameters->latitude_dec_deg_32 = deg_minute_second_to_dec_deg
   (lat_deg,lat_min,lat_sec,combobox_lat_dir ->Text == "North");
//   latitude_edit_bar->Update();
   edit_latitude_decdeg->Update();
   update_UTM();
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::longitude_degmin_sec_onexit(TObject */*Sender unused*/)
{  geolocation_parameters->longitude_dec_deg_32 = deg_minute_second_to_dec_deg
   (long_deg,long_min,long_sec,combobox_long_dir->Text == "East");
//   longitude_edit_bar->Update();
   edit_longitude_decdeg->Update();
   update_UTM();
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::utm_onexit(TObject *Sender)
{
   UTM_Geocoordiante utm_geo;

//   char utm_zone_desg = utm_zone_designator.c_str()[0];
   char utm_zone_desg = edit_utm_zone_desg->Text.c_str()[0];

   utm_geo.set_UTM(utm_easting, utm_northing, utm_zone,utm_zone_desg);

   float64 latitude_dec_deg_64;
   float64 longitude_dec_deg_64;
   if (utm_geo.get_degrees(latitude_dec_deg_64,longitude_dec_deg_64))
   {
   geolocation_parameters->latitude_dec_deg_32  = latitude_dec_deg_64;
   geolocation_parameters->longitude_dec_deg_32 = longitude_dec_deg_64;
   }
   edit_latitude_decdeg->Update();
//   latitude_edit_bar->Update();

   bool north;
   dec_deg_to_deg_minute_second
   (geolocation_parameters->latitude_dec_deg_32
   ,lat_deg
   ,lat_min
   ,lat_sec
   ,north);

   edit_lat_deg->Update();
   edit_lat_min->Update();
   edit_lat_sec->Update();
  combobox_lat_dir->Text = north ? "North" : "South";

//   longitude_edit_bar->Update();
   edit_longitude_decdeg->Update();

   bool east;
   dec_deg_to_deg_minute_second
   (geolocation_parameters->longitude_dec_deg_32
   ,long_deg
   ,long_min
   ,long_sec
   ,east);
   edit_long_deg->Update();
   edit_long_min->Update();
   edit_long_sec->Update();

   combobox_long_dir->Text = east ? "East" : "West";
};

//---------------------------------------------------------------------------
void Tgeolocation_form::dec_deg_to_deg_minute_second(float32 dec_deg, int16 &deg,int16 &min, float32 &sec,bool &east_or_north) const
{
/*
 D.d --> DM.m  (45.3772 --> 45o22.6333):
     - Multiply .d by 60 to get M.m (.3772*60=22.6333)
 DM.m --> DMS  (45o22.6333 --> 45o22'38"):
     - Multiply .m by 60 to get S(.6333*60=38)
*/
   east_or_north = (dec_deg > 0);
   dec_deg = fabs(dec_deg);
   deg = (int16)dec_deg;
   float32  d = dec_deg - deg;
   float32  dec_min = d * 60.0;
   min = abs((int16)dec_min);
   float32 m = dec_min - min;
   sec = m * 60.0;
};

float32 Tgeolocation_form::deg_minute_second_to_dec_deg(int16 deg,int16 min, int16 sec,bool east_or_north) const
{
/*
 DMS --> DM.m  (45o22'38" --> 45o22.6333):
     - Divide S by 60 to get .m (38/60=.6333)
     - Add .m to M to get M.m (22+.6333=22.6333)
 DM.m --> D.d  (45o 22.6333 --> 45.3772):
     - Divide M.m by 60 to get .d (22.6333/60=.3772)
     - Add .d to D to get D.d (45+.3772=45.3772)
*/
   float32 min_decimal = (float)sec/60.0;
    min_decimal += min;
   float32 deg_decimal = deg + (min_decimal/60);
   if (!east_or_north) deg_decimal = -deg_decimal;  // west and south are negative
   return deg_decimal;
};
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::latitude_decdeg_onexit(TObject */*Sender unused*/)
{
   bool north;
   dec_deg_to_deg_minute_second
   (geolocation_parameters->latitude_dec_deg_32
   ,lat_deg
   ,lat_min
   ,lat_sec
   ,north);
   combobox_lat_dir->Text = north ? "North" : "South";
   edit_lat_deg->Update();
   edit_lat_min->Update();
   edit_lat_sec->Update();
   update_UTM();
}
//---------------------------------------------------------------------------

void Tgeolocation_form::update_UTM()
{
   UTM_Geocoordiante utm_geo;
   utm_geo.set_degrees(geolocation_parameters->latitude_dec_deg_32,geolocation_parameters->longitude_dec_deg_32);
   utm_northing   = utm_geo.get_northing();
   utm_easting    = utm_geo.get_easting();
   utm_zone       = utm_geo.get_zone();
   char utm_zone_desg[10];
   utm_zone_desg[0] = utm_geo.get_zone_designator();
   utm_zone_desg[1] = 0;
//   utm_zone_designator.assign(utm_zone_desg);

   edit_utm_northing->Update();
   edit_utm_easting->Update();
   edit_utm_zone->Update();
//   utm_zone_designator_edit->Update();
   edit_utm_zone_desg->Text = utm_zone_desg;
};

void __fastcall Tgeolocation_form::longitude_decdeg_onexit(TObject */*Sender unused*/)
{
   bool east;
   dec_deg_to_deg_minute_second
   (geolocation_parameters->longitude_dec_deg_32
   ,long_deg
   ,long_min
   ,long_sec
   ,east);
   combobox_long_dir->Text = east ? "East" : "West";
   edit_long_deg->Update();
   edit_long_min->Update();
   edit_long_sec->Update();
   update_UTM();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::country_ISO3166_code_combobox_onchange(TObject *Sender)
{
   if (geolocation_parameters)
   {  geolocation_parameters->country_code_ISO3166 = atoi(combobox_country_ISO3166_code->Text.c_str());
      show_hide_controls();
   };
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::US_state_FIPS_combobox_onchange(TObject *Sender)
{
   if (geolocation_parameters)
   {  geolocation_parameters->state_code = atoi(combobox_US_state_FIPS->Text.c_str());
      show_hide_controls();
   };
}
//---------------------------------------------------------------------------
void Tgeolocation_form::show_hide_controls()
{  // For United states
   if (geolocation_parameters)
   {
      bool united_states = ((geolocation_parameters->country_code_ISO3166 == 840) || (geolocation_parameters->country_code_ISO3166 == 581));
      combobox_US_state_FIPS->Visible = united_states;
      bool show_country_name = (!geolocation_parameters->country_code_ISO3166 ||
         (!geolocation_parameters->country_code_ISO3166
        && (geolocation_parameters->county_name.length() !=0)));
      edit_country_name->Visible = show_country_name;
      edit_state_code->Visible = !united_states || (geolocation_parameters->state_code == 0);
      combobox_county_code->Visible = false; // Not yet implememented
   };
};
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::station_number_edit_onchange(TObject *Sender)
{  if (geolocation_parameters)
   {  char ID_code[20];
      strcpy(ID_code,edit_station_number->Text.c_str());
      geolocation_parameters->station_number = atol(ID_code);
   };
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::Update()
{
   edit_description->Update();
//   latitude_edit_bar->Update();
   edit_latitude_decdeg->Update();
   edit_longitude_decdeg->Update();
//   longitude_edit_bar->Update();
//   elevation_edit_bar->Update();
//   screening_height_edit_bar->Update();
   edit_elevation->Update();
   edit_screening_height->Update();
   edit_lat_deg->Update();
   edit_long_deg->Update();
   edit_lat_min->Update();
   edit_long_min->Update();
   edit_lat_sec->Update();
   edit_long_sec->Update();
//   update_latitude_dec_min_sec(0);
//   update_longitude_dec_min_sec(0);

   latitude_decdeg_onexit(0);
   longitude_decdeg_onexit(0);

   edit_country_name ->Update();
   edit_state_code   ->Update();
   edit_county_code  ->Update();
   char buffer[20];
   edit_station_ID_code ->Text = ltoa(geolocation_parameters->station_number,buffer,10);
   edit_station_ID_code ->Update();
   edit_station_name    ->Update();
   edit_comment         ->Update();
   update_UTM();
};
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::button_google_mapsClick(TObject *Sender)
{  // Google maps URL with latitude longitude coordinate
   // http://maps.google.com/?ll=45.9300041,-119.480003&spn=1,1
   // the spn is the size of the view port in units of latitude and longitude
   CORN::Ustring google_maps_URL("explorer \"http://maps.google.com/?ll=");
   google_maps_URL.append(CORN_float32_to_str(geolocation_parameters->latitude_dec_deg_32,6));
   google_maps_URL.append(",");
   google_maps_URL.append(CORN_float32_to_str(geolocation_parameters->longitude_dec_deg_32,6));
   google_maps_URL.append("&spn=1,1\"");
   WinExec(google_maps_URL.c_str(),SW_SHOWNORMAL	);
}
//---------------------------------------------------------------------------

