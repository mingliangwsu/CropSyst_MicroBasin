#pragma hdrstop
#include <UED/convert/DYRESM/DYRESM_convertor.h>
#include <UED/convert/station_database.h>
#include <corn/string/uiostring.h>
#include <iomanip>
//#include <common/geolocation/geolocation.h>
#include <UED/library/UED.h>
#include <UED/library/locrec.h>
#include <UED/library/std_codes.h>
#include <math.h>
#include <common/weather/loc_param.h>
#include <common/weather/parameter/WP_air_temperature.h>
#include <common/weather/parameter/WP_vapor_pressure_act.h>
#include <common/weather/parameter/WP_relative_humidity.h>
#include <common/weather/parameter/WP_vapor_pressure_deficit.h>
// loc_param included only for Season.


/*
<#3>
Comment line: dy_basic test case - daily met forcing
86400              # met data input time step (seconds)
CLOUD_COVER        # longwave radiation type (NETT_LW, INCIDENT_LW, CLOUD_COVER)
FIXED_HT  10       # sensor type (FLOATING; FIXED_HT),  height in m (above water surface; above lake bottom)
JulDay     SW_[W/m2]    Cloud-Cover  Tair_[C]   Vapour_Press_[hPa]   Wind_Speed_[m/s]   Rain_[m]
1990001   293.0555556     0.25         29.45          19.99              0.78            0
1990002   309.2592593     0.59         24.13          14.54              1               0
1990003   370.2546296     0.08         33.8           18.71              1.28            0
1990004   107.6388889     0.8          20.85          13.75              2.58            0
*/
//______________________________________________________________________________
//______________________________________________________________________________
class DYRESM_record
: public CORN::Enumeration
{
public: // attributes
   Date32   date;
   float32  SW;            // W/m2
   float32  NET_LW;        // W/m2
   float32  cloud_cover_fraction;
//NYI   float32  INCIDENT_LW;   // W/m2
//NYI   float32  Cloud_Cover;   // fraction
   float32  Tair;                    // Deg C
   float32  Vapour_Press;  // hPa
   float32  Wind_Speed;    // m/s
   float32  Rain;          // m
public: // incase we don't have daily average
   float32  Tair_max;          CORN::Quality_code Tair_max_quality;// Deg C
   float32  Tair_min;          CORN::Quality_code Tair_min_quality;// Deg C
   float32  relative_humidity_max;  CORN::Quality_code relative_humidity_max_quality;
   float32  relative_humidity_min;  CORN::Quality_code relative_humidity_min_quality;
public:
   inline DYRESM_record(Date32   _date)
      : CORN::Enumeration()
      , date(_date)
      , SW           (0)
      , cloud_cover_fraction(0)
      , NET_LW       (0)
      , Tair         (0)
      , Vapour_Press (0)
      , Wind_Speed   (0)
      , Rain         (0)                           
      , Tair_max     (0)         , Tair_max_quality(CORN::missing_quality)
      , Tair_min     (0)         , Tair_min_quality(CORN::missing_quality)
      , relative_humidity_max (0),relative_humidity_max_quality(CORN::missing_quality)
      , relative_humidity_min (0),relative_humidity_min_quality(CORN::missing_quality)
      {}
   inline virtual bool is_key_nat32(nat32 key)              affirmation_  //180820
      { return date == key; }

/*180820  was probably only used for find_cstr now using is_key
   virtual uint32 get_key() const { return date;}
*/
};
//______________________________________________________________________________
nat32 DYRESM_convertor::perform_export()
{
   uint32 records_exported = 0;
   char filename_only[255];
   Ustring       export_station_ID;
   strcpy(filename_only,parameters.ued_filename.get_name(false).c_str());
   export_station_ID.assign(filename_only);

   UED_indexed_database ued_file(parameters.ued_filename.c_str(),true);

   UED_geolocation_record  *location_rec= ued_file.get_geolocation_record();  //060616
   #ifdef NYI
   currently just    using the UED filename,
   if (location_rec) // if it exists
   {  // extract the station ID from the location record
      // if the extracted ID is value then use that IDo
          if (strlen(location_rec->get_station_ID_code()))
             export_station_ID.assign(location_rec->get_station_ID_code());
   }
   #endif
   ued_file.goto_BOF();
   cout << "Indexing completed." << endl;

   CORN::File_name DYRESM_filename(parameters.ued_filename.c_str());
   DYRESM_filename.set_name(filename_only);
   DYRESM_filename.set_ext("met");

   ofstream DYRESM_file(DYRESM_filename.c_str());
   DYRESM_file << "<#3>" << endl; // Not sure what this is
   DYRESM_file << "Comment line: " <<  location_rec->get_station_name() << endl;
   DYRESM_file << "86400              # met data input time step (seconds)" << endl;
      switch (parameters.net_radiation_option)                                               //070212                                                
      {  case cloud_cover_fraction_option             : DYRESM_file << "CLOUD_COVER            # longwave radiation type (NETT_LW, INCIDENT_LW, CLOUD_COVER)" << endl; break;
         case longwave_net_radiation_option           : DYRESM_file << "NETT_LW            # longwave radiation type (NETT_LW, INCIDENT_LW, CLOUD_COVER)" << endl; break;
         case incident_longwave_net_radiation_option  : default : DYRESM_file << "INCIDENT_LW            # longwave radiation type (NETT_LW, INCIDENT_LW, CLOUD_COVER)" << endl; break;
      }


   DYRESM_file << "FIXED_HT  " << location_rec->get_screening_height() << "       # sensor type (FLOATING; FIXED_HT),  height in m (above water surface; above lake bottom)" << endl;
   DYRESM_file << "JulDay     SW_[W/m2]  ";
      switch (parameters.net_radiation_option)                                                                 //070212
      {  case cloud_cover_fraction_option             : DYRESM_file << "Cloud-Cover [%]"  ; break;             //070212
         case longwave_net_radiation_option           : DYRESM_file << "  NETT_LW[W/m2] "; break;              //070212
         case incident_longwave_net_radiation_option  : default : DYRESM_file << "INCIDENT_LW[W/m2]" ; break;  //070212
      }
   DYRESM_file << " Tair_[C]   Vapour_Press_[hPa]   Wind_Speed_[m/s]   Rain_[m]" << endl;
   Enumeration_list DYRESM_records;
   Units_convertor units_convertor;
   cout << "Tuplizing data" << endl;
   // for each data record record in the database.
   for  (UED_data_record *data_rec = ued_file.goto_next_data_record();data_rec ;data_rec = ued_file.goto_next_data_record())
   {
      Date_time_64 for_time(data_rec->get_time_stamp());
      uint16 num_values = data_rec->get_num_values();
      UED_units_code &time_step_units_code = data_rec->get_time_step_units_code();
      UED_variable_code variable_code = data_rec->get_variable_code();

      //debug cout << for_time.c_str() << '\t' << ((int32) variable_code) << '\r';

      UED_units_code value_units = data_rec->get_units_code();
      if (time_step_units_code == UT_day)
      {
         for (int TS_count = 1; TS_count <= for_time.days_in_year(); TS_count++)
         {
            DYRESM_record *record = (DYRESM_record *)DYRESM_records.find(for_time.get_date32());
            if (!record)
            {
               record = new DYRESM_record(for_time.get_date32());
               DYRESM_records.append(record);
            };
            CORN::Quality_code datum_attribute;
            float32 value = data_rec->get_value
            (datum_attribute
            ,for_time.get_datetime64());
            if (variable_code == UED_STD_VC_solar_radiation.get())
                  record->SW = value * 1000000.0/86400.0;
            else if (variable_code == UED_STD_VC_isothermal_longwave_net_radiation.get())  //NET_LW;        // W/m2
                  record->NET_LW = value * 1000000.0/86400.0;
            else if (variable_code == UED_STD_VC_cloud_cover.get())                                   //070212
                  record->cloud_cover_fraction = value / 100.0;                                       //070212
            else if (variable_code == UED_STD_VC_avg_temperature.get()) // Tair;          // Deg C
            {  units_convertor.convert(value,value_units,record->Tair,UC_celcius);
               //NYN     record->Tair_quality = datum_attribute;
            } else if (variable_code == UED_STD_VC_max_temperature.get())   //Tmax
            {  units_convertor.convert(value,value_units,record->Tair_max,UC_celcius);
               record->Tair_max_quality = datum_attribute;
            } else if (variable_code == UED_STD_VC_min_temperature.get()) //Tmin
            {  units_convertor.convert(value,value_units,record->Tair_min,UC_celcius);
               record->Tair_min_quality = datum_attribute;
            }
            #ifdef NYI
            currently calculating using estimation equation
               case xxxxx :  // Vapour_Press;  // hPa
               {
                  record->Vapour_Press = xxxx;
               } break;
            #endif
             else if (variable_code == UED_STD_VC_precipitation.get())   //  Rain;          // m
                  units_convertor.convert(value,value_units,record->Rain,UC_meter);
            else if (variable_code == UED_STD_VC_wind_speed.get())   // Wind_Speed;    // m/s
                  units_convertor.convert(value,value_units,record->Wind_Speed,UC_meters_per_second);
            #ifdef NYI
            else if (variable_code == xxxxx.get())        // INCIDENT_LW;   // W/m2
                  record->INCIDENT_LW = value * 1000000.0/86400.0;
            else if (variable_code == xxxxx.get()) //   cloud cover // fraction
                  units_convertor.convert(value,value_units,record->Cloud_Cover,UC_fraction);
            #endif
            else if (variable_code == UED_STD_VC_max_relative_humidity.get())
            {  record->relative_humidity_max_quality = datum_attribute;
                 record->relative_humidity_max = value;           // always %
            } else if (variable_code == UED_STD_VC_min_relative_humidity.get())
            {  record->relative_humidity_min_quality = datum_attribute;
               record->relative_humidity_min = value;          // always %
            }
            // else ignore all other element
            for_time.inc();
         }
      }
   }
   // Now write the DYRESM file record
   cout << endl <<"writing DYRESM file:" << endl;
   FOR_EACH_IN(record,DYRESM_record,DYRESM_records,each_record)
   {
      cout << record->date << '\r';
      if (is_essentially(record->Tair,0.0,0.000001))
         record->Tair = (record->Tair_max + record->Tair_min)/2.0;
      float32 rel_humid_avg = (record->relative_humidity_max + record->relative_humidity_min)/2.0;
      float32 vapor_pressure = 0.0;

      switch (parameters.vapor_pressure_calculation)
      {  case VP_based_on_mean_relative_humidity_and_air_temperature : vapor_pressure =  estimate_vapor_pressure_hPa(record->Tair,rel_humid_avg); break;
         case  VP_based_on_min_and_max_relative_humidity : default   : vapor_pressure = estimate_vapor_pressure_from_min_max_rel_humid_hPa(*record); break;
      }

      DYRESM_file << record->date
      << "   "
      << setw(11) << setprecision(7) << record->SW
      << "   ";
   Note here there is an option of cloud cover fraction or incident LW net rad.
      float32 net_option_value = 0.0;                                                                             //070212
      switch (parameters.net_radiation_option)                                                                    //070212   
      {  case cloud_cover_fraction_option             : net_option_value = record->cloud_cover_fraction; break;   //070212
         case longwave_net_radiation_option           : net_option_value =record->NET_LW; break;                  //070212
         case incident_longwave_net_radiation_option  : default : net_option_value = 0.0; break;                  //070212
      }
      if (net_option_value < 0.00001)                                                                             //070212
          net_option_value = 0.0000;                                                                              //070212
      DYRESM_file << setw(11) << setprecision(2) << net_option_value
      << "   "
      << setw(7) << setprecision(2) << record->Tair
      << "         "
      << setw(6) << setprecision(2) << vapor_pressure
      << "            "
      << setw(6) << setprecision(2) << record->Wind_Speed
      << "            "
      << setw(6) << setprecision(2) << record->Rain
      << endl;
      records_exported++;
   } FOR_EACH_END(each_record)
   cout << endl <<"completed." << endl;
   press_return_before_exit = true;
   return records_exported;
}
//______________________________________________________________________________
float32 DYRESM_convertor::estimate_vapor_pressure_hPa(float32 dry_bulb_temperature, float32 rel_humid) const
{  // Note this is in hecto pascals
   static const float32 a = 7.5;
   static const float32 b = 237.3;
   static const float32 c = 0.7858;
   float32 vp_est =  (rel_humid/100.0) * exp(2.303 * (( a * dry_bulb_temperature / (dry_bulb_temperature + b)) + c));
   return vp_est;
}
//______________________________________________________________________________
float32 DYRESM_convertor::estimate_vapor_pressure_from_min_max_rel_humid_hPa(const DYRESM_record &record) const
{  // Note this is in hecto pascals
   Season season_irrelevent; // need default value
   Air_temperature_maximum_parameter      T_max_param          (record.Tair,record.Tair_max_quality);
   Air_temperature_minimum_parameter      T_min_param          (record.Tair,record.Tair_min_quality);
   Relative_humidity_maximum_parameter    rel_humid_max_param  (record.relative_humidity_max,record.relative_humidity_max_quality);
   Relative_humidity_minimum_parameter    rel_humid_min_param  (record.relative_humidity_min,record.relative_humidity_min_quality);
   Vapor_pressure_deficit_max_parameter   vpd_max_param        (season_irrelevent,rel_humid_min_param,T_max_param);
   Vapor_pressure_actual_parameter vapor_pressure_act_param(vpd_max_param,rel_humid_max_param,rel_humid_min_param,T_max_param,T_min_param);
   vapor_pressure_act_param.update();
   float32 VP_act_kPa = vapor_pressure_act_param.get() * 10.0;
   return VP_act_kPa; // kilo to hecto
}
//______________________________________________________________________________
DYRESM_convertor::DYRESM_convertor(int argc, const char *argv[])
:UED_convertor(argc,argv)
{}
//______________________________________________________________________________

