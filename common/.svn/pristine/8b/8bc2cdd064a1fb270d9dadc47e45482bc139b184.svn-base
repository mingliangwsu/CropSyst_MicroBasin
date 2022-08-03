//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "geolocation_frm.h"
#ifndef GEOLOCATION_H
#  include <common/geolocation/geolocation.h>
#endif
#ifndef GEOLOCATION_UTM_H
#  include <common/geolocation/UTM.h>
#endif
#include <CropSyst/GUI/help/location.h>
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
{}
//---------------------------------------------------------------------------
void Tgeolocation_form::bind_to
(Geolocation *geolocation_params
,CORN::Ustring *description          // may be 0
)
{
   geolocation_parameters =geolocation_params;
   if (description)
   {  description_edit->bind_to(description,HELP_P_loc_description);
   }
   else
   {  description_label->Visible = false;
      description_edit->Visible = false; // CropSyst stores the description elsewhere
      geolocation_pagecontrol->Align = alClient;
   };
//temp_disabled   latitude_edit_bar->bind_to(&geolocation_parameters->v_latitude_dec_deg,HELP_P_loc_latitude);
//temp_disabled   longitude_edit_bar->bind_to(&geolocation_parameters->v_longitude_dec_deg,HELP_P_loc_latitude);
//temp_disabled   elevation_edit_bar->bind_to(&geolocation_parameters->v_elevation,0);
//temp_disabled   screening_height_edit_bar->bind_to(&geolocation_parameters->v_screening_height,HELP_P_loc_windmeasure);



   lat_deg_edit->bind_to(&lat_deg,HELP_P_loc_latitude);
   long_deg_edit->bind_to(&long_deg,HELP_P_loc_latitude);

   lat_min_edit->bind_to(&lat_min,HELP_P_loc_latitude);
   long_min_edit->bind_to(&long_min,HELP_P_loc_latitude);

   lat_sec_edit->bind_to(&lat_sec,4,HELP_P_loc_latitude);
   long_sec_edit->bind_to(&long_sec,4,HELP_P_loc_latitude);

   utm_northing_edit ->bind_to(&utm_northing,5,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);
   utm_easting_edit  ->bind_to(&utm_easting, 5,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);
   utm_zone_edit     ->bind_to(&utm_zone      ,HELP_P_loc_latitude /*NYI HELP_P_loc_UTM*/);

//   update_latitude_dec_min_sec(0);
//   update_longitude_dec_min_sec(0);
   latitude_decdeg_onexit(0);
   longitude_decdeg_onexit(0);


   update_UTM();

   country_name_edit ->bind_to(&(geolocation_parameters->country_name),0);
   state_code_edit   ->bind_to(&(geolocation_parameters->state_name),0);
   county_code_edit  ->bind_to(&(geolocation_parameters->county_name),0);

   char buffer[20];
   station_ID_code_edit ->Text = ltoa(geolocation_parameters->station_number,buffer,10);
   station_ID_code_edit ->bind_to(&(geolocation_parameters->station_ID_code),0);
   station_name_edit    ->bind_to(&(geolocation_parameters->station_name),0);
   show_hide_controls();
};
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::latitude_degminsec_onexit(TObject */*Sender unused*/)
{  geolocation_parameters->latitude_dec_deg_32 = deg_minute_second_to_dec_deg
   (lat_deg,lat_min,lat_sec,lat_dir_combobox ->Text == "North");
//temp_disabled   latitude_edit_bar->Update();
   update_UTM();
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::longitude_degmin_sec_onexit(TObject */*Sender unused*/)
{  geolocation_parameters->longitude_dec_deg_32 = deg_minute_second_to_dec_deg
   (long_deg,long_min,long_sec,long_dir_combobox->Text == "East");
//temp_disabled   longitude_edit_bar->Update();
   update_UTM();
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::utm_onexit(TObject *Sender)
{
   UTM_Geocoordiante utm_geo;
   utm_geo.set_UTM(utm_easting, utm_northing, utm_zone);

   float64 latitude_dec_deg_64= 0;
   float64 longitude_dec_deg_64= 0;
   if (utm_geo.get_degrees(latitude_dec_deg_64,longitude_dec_deg_64))
   {  geolocation_parameters->latitude_dec_deg_32  = latitude_dec_deg_64;
      geolocation_parameters->longitude_dec_deg_32 = longitude_dec_deg_64;
   };

//temp_disabled   latitude_edit_bar->Update();
   bool north;
   dec_deg_to_deg_minute_second
   (geolocation_parameters->latitude_dec_deg_32
   ,lat_deg
   ,lat_min
   ,lat_sec
   ,north);

   lat_deg_edit->Update();
   lat_min_edit->Update();
   lat_sec_edit->Update();

   lat_dir_combobox->Text = north ? "North" : "South";


//temp_disabled   longitude_edit_bar->Update();

   bool east;
   dec_deg_to_deg_minute_second
   (geolocation_parameters->longitude_dec_deg_32
   ,long_deg
   ,long_min
   ,long_sec
   ,east);
   long_deg_edit->Update();
   long_min_edit->Update();
   long_sec_edit->Update();

   long_dir_combobox->Text = east ? "East" : "West";
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
   lat_dir_combobox->Text = north ? "North" : "South";
   lat_deg_edit->Update();
   lat_min_edit->Update();
   lat_sec_edit->Update();
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
   utm_northing_edit->Update();
   utm_easting_edit->Update();
   utm_zone_edit->Update();
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
   long_dir_combobox->Text = east ? "East" : "West";
   long_deg_edit->Update();
   long_min_edit->Update();
   long_sec_edit->Update();
   update_UTM();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::country_ISO3166_code_combobox_onchange(TObject *Sender)
{
   if (geolocation_parameters)
   {  geolocation_parameters->country_code = atoi(country_ISO3166_code_combobox->Text.c_str());
      show_hide_controls();
   };
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::US_state_FIPS_combobox_onchange(TObject *Sender)
{
   if (geolocation_parameters)
   {  geolocation_parameters->state_code = atoi(US_state_FIPS_combobox->Text.c_str());
      show_hide_controls();
   };
}
//---------------------------------------------------------------------------
void Tgeolocation_form::show_hide_controls()
{  // For United states
   if (geolocation_parameters)
   {
      bool united_states = ((geolocation_parameters->country_code == 840) || (geolocation_parameters->country_code == 581));
      US_state_FIPS_combobox->Visible = united_states;
      bool show_country_name = (!geolocation_parameters->country_code ||
         (!geolocation_parameters->country_code
        && (geolocation_parameters->county_name.length() !=0)));
      country_name_edit->Visible = show_country_name;
      state_code_edit->Visible = !united_states || (geolocation_parameters->state_code == 0);
      county_code_combobox->Visible = false; // Not yet implememented
   };
};
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::station_number_edit_onchange(TObject *Sender)
{  if (geolocation_parameters)
   {  char ID_code[20];
      strcpy(ID_code,station_number_edit->Text.c_str());
      geolocation_parameters->station_number = atol(ID_code);
   };
}
//---------------------------------------------------------------------------
void __fastcall Tgeolocation_form::Update()
{
   description_edit->Update();
//temp_disabled   latitude_edit_bar->Update();
//temp_disabled   longitude_edit_bar->Update();
//temp_disabled   elevation_edit_bar->Update();
//temp_disabled   screening_height_edit_bar->Update();
   lat_deg_edit->Update();
   long_deg_edit->Update();
   lat_min_edit->Update();
   long_min_edit->Update();
   lat_sec_edit->Update();
   long_sec_edit->Update();
//   update_latitude_dec_min_sec(0);
//   update_longitude_dec_min_sec(0);

   latitude_decdeg_onexit(0);
   longitude_decdeg_onexit(0);

   country_name_edit ->Update();
   state_code_edit   ->Update();
   county_code_edit  ->Update();
   char buffer[20];
   station_ID_code_edit ->Text = ltoa(geolocation_parameters->station_number,buffer,10);
   station_ID_code_edit ->Update();
   station_name_edit    ->Update();

   update_UTM();
};



