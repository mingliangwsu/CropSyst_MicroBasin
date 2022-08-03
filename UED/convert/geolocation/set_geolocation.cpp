#include <UED/library/database_file.h>

090306 actually decided not to use this.
Currently geolocation parameters can be setup using UED convertor programs
the UED_convertor now provides the ability to set geolocation parameters
either in the response file or the command line.


int main(int argc, char *argv[])
{  int return_status = 0;
/* This program is used to set the geolocation
   latitute, longitude ect.
*/
   UED_File_name  UED_filename(argv[1]);
   if (UED_filename.exists())
   {
      Geolocation_record *geolocation = new Geolocation_record(xxx);
      for (int argi = 2; argi <= argc; argi++)
      {
              if (stricmp(argv[i],LABEL_latitude)           == 0)     {  geolocation->latitude_dec_deg_32    = atof(argv[i]);  argi++;  }
         else if (stricmp(argv[i],LABEL_longitude)          == 0)     {  geolocation->longitude_dec_deg_32   = atof(argv[i]);  argi++;  }
         else if (stricmp(argv[i],LABEL_elevation)          == 0)     {  geolocation->elevation              = atof(argv[i]);  argi++;  }
         else if (stricmp(argv[i],LABEL_station_name)       == 0)     {  geolocation->station_name.assign(argv[i]);            argi++;  }
         else if (stricmp(argv[i],"station_number")     == 0)     {  geolocation->station_number         = atoi(argv[i]);  argi++;  }
         else if (stricmp(argv[i],"station_ID")         == 0)     {  geolocation->station_ID_code        = atof(argv[i]);  argi++;  }
         else if (stricmp(argv[i],LABEL_wind_measurement_height)   == 0)     {  geolocation->screening_height_32    = atof(argv[i]);  argi++;  }
         else if (stricmp(argv[i],LABEL_country)            == 0)     {  geolocation->country_name.assign(argv[i]);            argi++;  }
         else if (stricmp(argv[i],LABEL_state)              == 0)     {  geolocation->state_name.assign(argv[i]);              argi++;  }
      };
      UED::Database_file  UED_file(argv ,bool i_read_only);
      UED_file.take_geolocation_record(geolocation) not_const;
   } else
      return_status = 1;
   return return_status;
};