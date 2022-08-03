using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using UED_simple;

namespace example_weather_UED
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string filename_UED =@"C:\\temp\\300033 - WSU HQ.UED";

            UED_simple.Database UED_file = new UED_simple.Database(filename_UED);
            // Get the range of dates occuring in the database.
            double earliest_date_time = UED_file.get_earliest_date_time();
            long   earliest_date = (long)earliest_date_time;
            double latest_date_time = UED_file.get_latest_date_time();
            long   latest_date = (long)latest_date_time;

           //For the geolocation,
           // The Station ID is required,
           // The descriptive is recommended
           // The geopolitical details and comment are optional
            UED_file.set_geolocation
            (46.5 // latitude
            ,-117.3 // longitude
            ,717 // elevation meter
            ,2  // screening_height  meter
            ,@"987543" // station_ID
            ,@"USDA Experimental station Pullman"  // descriptive name
            ,@"USA"   // country
            ,@"Washington" // state or province
            ,@"Whitman" // county, shire, comte, contea, contado, comtat, condado, Grafschaft, Gau
            ,@"Historical measurements");

            //Dates are represented as 32bit integers   Year * 1000 + DOY  
            // 2011365  is Dec 31, 2011

            Int32 targetdate = 1990 * 1000 + 213; // Aug 1 1990
            float precip_mm = UED_file.get_for_date_quick(targetdate, 0x5820001, 0x2043);   // Precipitation millimeter 
            float Tmax      = UED_file.get_for_date_quick(targetdate, 0x2870001, 0x100);    // Max daily air temperature celcius 
            float Tmin      = UED_file.get_for_date_quick(targetdate, 0x3870001, 0x100);    // Min daily air temperature celcius 
            float RHmax     = UED_file.get_for_date_quick(targetdate, 0x2830001, 0x3);      // Max Relative humidity %
            float RHmin     = UED_file.get_for_date_quick(targetdate, 0x3830001, 0x3);      // Min Relative humidity %    
            float SRad      = UED_file.get_for_date_quick(targetdate, 0x1860201, 0x28804c06);  // Solar radiation (global) MJ/m2 (for the day)
            float windspeed = UED_file.get_for_date_quick(targetdate, 0x1a20001, 0x16802000);  // Windspeed m/sec

            // You will usually need to check the quality of got value:
            // get_last_quality() returns the quality of the last value returned by get_for_date_quick
            
            UInt32 Tdewmax_units = 0x100; // preferred units
            UInt32 Tdewmin_units = 0x100; // preferred units
            float Tdewmax = UED_file.get_for_date_quick(targetdate, 0x2870002, Tdewmax_units);
            UInt32 Tdewmax_quality = UED_file.get_last_quality();
            float Tdewmin = UED_file.get_for_date_quick(targetdate, 0x3870002, Tdewmin_units);
            UInt32 Tdewmin_quality = UED_file.get_last_quality();
        }
    }
}
