#include <UED/library/database_file.h>
#include <UED/library/locrec.h>
#include <common/geolocation/geolocation.h>
#include <corn/container/association.h>
#include <corn/container/text_list.h>
#include <corn/math/statistical/stats.h>
#include <corn/file_sys/smart_filename.h>
#include <corn/file_sys/smart_dirname.h>
#include <UED/library/controls.h>
#include <fstream>
using namespace std;
//______________________________________________________________________________
class Geolocation_item : public CORN::Item, public Geolocation
{  // Geolocation as a container item


public:
   inline Geolocation_item() : CORN::Item() , Geolocation() {};
   inline Geolocation_item(const Geolocation &copy_from) : CORN::Item() , Geolocation(copy_from) {};  //050307
};
//_2009-09-14___________________________________________________________________
void write_start
(ofstream &map_file
,const Geolocation &center_point
)
{   // http://code.google.com/apis/maps/documentation/javascript/v2/overlays.html

   /* Various map icons https://sites.google.com/site/gmapicons/
 http://labs.google.com/ridefinder/images/mm_20_purple.png

 http://labs.google.com/ridefinder/images/mm_20_yellow.png

 http://labs.google.com/ridefinder/images/mm_20_blue.png

 http://labs.google.com/ridefinder/images/mm_20_white.png

 http://labs.google.com/ridefinder/images/mm_20_green.png

 http://labs.google.com/ridefinder/images/mm_20_red.png

 http://labs.google.com/ridefinder/images/mm_20_black.png

 http://labs.google.com/ridefinder/images/mm_20_orange.png

 http://labs.google.com/ridefinder/images/mm_20_gray.png

 http://labs.google.com/ridefinder/images/mm_20_brown.png

 http://labs.google.com/ridefinder/images/mm_20_shadow.png
   */


   map_file << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">" << endl;
   map_file << "<html>" << endl;
   map_file << "  <head>" << endl;
   map_file << "    <title>Google Maps</title>" << endl;
   map_file << "    <script src=\"http://maps.google.com/maps?file=api&amp;v=2&amp;sensor=false&amp;key=ABQIAAAAPDUET0Qt7p2VcSk6JNU1sBSM5jMcmVqUpI7aqV44cW1cEECiThQYkcZUPRJn9vy_TWxWvuLoOfSFBw\" type=\"text/javascript\"></script>" << endl;
   map_file << "    <STYLE TYPE=\"text/css\">" << endl;
   map_file << "    <!--" << endl;
   map_file << "    TD{font-family: Arial; font-size: 9pt;}" << endl;
   map_file << "    --->" << endl;
   map_file << "    </STYLE>" << endl;
   map_file << "  </head>" << endl;
   map_file << "  <body onunload=\"GUnload()\" >" << endl;
   map_file << "    <!-- you can use tables or divs for the overall layout -->" << endl;
   map_file << "    <table border=1>" << endl;
   map_file << "      <tr>" << endl;
   map_file << "        <td id=\"map\" WIDTH=90% HEIGHT=100%>" << endl;
//<!--           <div id="map" style="width: 550px; height: 450px"></div>  -->
   map_file << "        </td>" << endl;
   map_file << "        <td width = 150 valign=\"top\" style=\"text-decoration: underline; color: #4444ff;\">" << endl;
   map_file << "           <!-- =========== side_bar with scroll bar ================= -->" << endl;
   map_file << "           <div id=\"side_bar\"  style=\"overflow:auto; height:800px;\"></div>" << endl;
   map_file << "           <!-- ===================================================== -->" << endl;
   map_file << "        </td>" << endl;
   map_file << "      </tr>" << endl;
   map_file << "    </table>" << endl;
   map_file << "    <noscript><b>JavaScript must be enabled in order for you to use Google Maps.</b>" << endl;
   map_file << "      However, it seems JavaScript is either disabled or not supported by your browser." << endl;
   map_file << "      To view Google Maps, enable JavaScript by changing your browser options, and then" << endl;
   map_file << "      try again." << endl;
   map_file << "    </noscript>" << endl;
   map_file << "    <script type=\"text/javascript\">" << endl;
   map_file << "    //<![CDATA[" << endl;
   map_file << "    if (GBrowserIsCompatible()) {" << endl;
   map_file << "      var side_bar_html = \"\";" << endl;
   map_file << "      var gmarkers = [];" << endl;
   map_file << "      var htmls = [];" << endl;
   map_file << "      var i = 0;" << endl;
   map_file << "      var baseIcon = new GIcon(G_DEFAULT_ICON);" << endl;
//disabled shadow   map_file << "      baseIcon.shadow = \"http://www.google.com/mapfiles/shadow50.png\";" << endl;
   map_file << "      baseIcon.iconSize = new GSize(20, 34);" << endl;
   map_file << "      baseIcon.shadowSize = new GSize(37, 34);" << endl;
   map_file << "      baseIcon.iconAnchor = new GPoint(9, 34);" << endl;
   map_file << "      baseIcon.infoWindowAnchor = new GPoint(9, 2);" << endl;
   map_file << "      // A function to create the marker and set up the event window" << endl;
   map_file << "      function createMarker(point,marker_image,name,html) {" << endl;
   map_file << "         var pointicon  = new GIcon(baseIcon);" << endl;
   map_file << "           pointicon.image = marker_image; " << endl;
  // Set up our GMarkerOptions object
   map_file << "           markerOptions = { icon:pointicon };" << endl;
   map_file << "        var marker = new GMarker(point,pointicon);" << endl;
   map_file << "        GEvent.addListener(marker, \"click\", function() {" << endl;
   map_file << "          marker.openInfoWindowHtml(html);" << endl;
   map_file << "        });" << endl;
   map_file << "        gmarkers[i] = marker;" << endl;
   map_file << "        htmls[i] = html;" << endl;
   map_file << "        side_bar_html += '<a href=\"javascript:myclick(' + i + ')\">' + name + '</a><br>';" << endl;
   map_file << "        i++;" << endl;
   map_file << "        return marker;" << endl;
   map_file << "      }" << endl;
   map_file << "      function myclick(i) { gmarkers[i].openInfoWindowHtml(htmls[i]); }" << endl;
   map_file << "      // create the map" << endl;
   map_file << "      var map = new GMap2(document.getElementById(\"map\"));" << endl;
   map_file << "      map.addControl(new GLargeMapControl());" << endl;
   map_file << "      map.addControl(new GMapTypeControl());" << endl;

   map_file << "map.setCenter(new GLatLng( "
            << center_point.get_latitude_dec_deg()
            << ","
            << center_point.get_longitude_dec_deg()
            << "), 6);"   // Zoom level 6 is good for most US states.
            << endl;
};
//______________________________________________________________________________
void generate_point(ofstream &map_file
,const Geolocation &geoloc
,const CORN::Text_list::Item &marker)
{
      CORN::Ustring station_name(geoloc.get_station_name());
      station_name.replace_character('\'',' ');
      station_name.replace_character('\"',' ');

   map_file << "    var point = new GLatLng("
      << geoloc.get_latitude_dec_deg()
      << ","
      << geoloc.get_longitude_dec_deg()
      << ");" << endl
      << "      var marker = createMarker(point,\"" <<marker<< "\",\""
      << station_name
      << "("
      <<  geoloc.get_state_name()
      << ")"      
      << "\",'<div style=\"width:240px\">"


      << "<B>"
      << station_name
      << "</B> ("
      << geoloc.get_station_ID_code()
      << ") - ("
      << geoloc.get_station_number()
      << ")<BR>"

//      << "<A HREF=\"http://en.wikipedia.org/wiki/"
//      << geoloc.get_country_name()
//      << "\">"
      << geoloc.get_country_name()
      << "("
      << geoloc.get_country_code_ISO3166()
      << ")"
//      << "</A>
      << "<BR> "

//      << "<A HREF=\"http://en.wikipedia.org/wiki/"
//      << geoloc.get_state_name()
//      << "\">"
      << geoloc.get_state_name()
      << "("
      << geoloc.get_state_code()
      << ")"
//      << "</A>
      << "<BR> "

//      << "<A HREF=\"http://en.wikipedia.org/wiki/"
//      << geoloc.get_county_name()
//      << "\">"
      << geoloc.get_county_name()
      << "("
      << geoloc.get_county_code()
      << ")"
//      << "</A>
      << "<BR> "

      << "Latitude:"
      << geoloc.get_latitude_dec_deg_32()
      << "<BR>"

      << "Longitude:"
      << geoloc.get_longitude_dec_deg_32()
      << "<BR>"

      << "Elevation:"
      << geoloc.get_elevation()
      << "<BR>" 

      << "<\/div>')" << endl
      << "      map.addOverlay(marker);" << endl;
};
//______________________________________________________________________________
void generate_points(ofstream &map_file
,const CORN::Unidirectional_list &locations
,CORN::Text_list &markers)                                                       //110611
{
   CORN::Container::Iterator *each_marker = markers.iterator();
   Text_list::Item *marker = (Text_list::Item *)each_marker->first();
   FOR_EACH_IN(geoloc_item, Geolocation_item, locations, each_location)
   {
      generate_point(map_file,*(geoloc_item),*(marker));
      marker =  (Text_list::Item *)each_marker->next();
   } FOR_EACH_END(each_location);
   delete each_marker; each_marker = 0;
};
//______________________________________________________________________________
void write_end(ofstream &map_file)
{
   map_file << "        document.getElementById(\"side_bar\").innerHTML = side_bar_html;" << endl;
   map_file << "    }" << endl;
   map_file << "    else {" << endl;
   map_file << "      alert(\"Sorry, the Google Maps API is not compatible with this browser\");" << endl;
   map_file << "    }" << endl;
//   map_file << "    // This Javascript is based on code provided by the
//   map_file << "    // Community Church Javascript Team
//   map_file << "    // http://www.bisphamchurch.org.uk/
//   map_file << "    // http://econym.org.uk/gmap/
   map_file << "    //]]>" << endl;
   map_file << "    </script>" << endl;
   map_file << "  </body>" << endl;
   map_file << "</html>" << endl;
};
//______________________________________________________________________________
uint32 get_locations
(CORN::Association_list &UED_filenames
,CORN::Unidirectional_list &locations
,CORN::Text_list &markers
,Geolocation &center_point)
{  uint32 location_count = 0;
   CORN::Statistical_running_tally latitudes;
   Statistical_running_tally longitudes;
   cout << "Identifying locations:" << endl;
   FOR_EACH_IN(uedfilename,CORN::File_name,UED_filenames,each_ued_fname)
   {  cout << uedfilename->c_str() << "         \r";
      UED::Database_file ued_file(uedfilename->c_str(),true);
      const UED::Geolocation_record *UED_geoloc = ued_file.get_geolocation_record_immutable();
      if (UED_geoloc)
      {
         latitudes.append(UED_geoloc->get_latitude_dec_deg());
         longitudes.append(UED_geoloc->get_longitude_dec_deg());
         locations.append(new Geolocation_item(*UED_geoloc));
         const UED::Generating_application_record *gen_app_rec = ued_file.get_generating_application_record();
         if (gen_app_rec)
         {  CORN::Ustring generator_caption(gen_app_rec->get_description());

            if      (generator_caption.find("AgWeatherNet")!=CORN::Ustring::npos) markers.add("http://labs.google.com/ridefinder/images/mm_20_green.png");
            else if (generator_caption.find("NCDC")!=CORN::Ustring::npos) markers.add("http://labs.google.com/ridefinder/images/mm_20_orange.png");
            else if (generator_caption.find("AgriMet")!=CORN::Ustring::npos) markers.add("http://labs.google.com/ridefinder/images/mm_20_yellow.png");
            else     markers.add("http://labs.google.com/ridefinder/images/mm_20_red.png");
         };
         location_count ++;
      };
   } FOR_EACH_END(each_ued_fname);
   // Warning, this doesn't work on if points are on either side of the international date lines (180th meridian)
   center_point.set_latitude_dec_deg_32(latitudes.get_mean());
   center_point.set_longitude_dec_deg_32(longitudes.get_mean());
   cout << endl;
   return location_count;
};
//______________________________________________________________________________
uint32 map_UED_locations
(const CORN::Smart_directory_name &UED_data_dir
,const char *map_name_unqual_no_ext)
{
   // Get list of UED files in the directory.
   CORN::Association_list UED_filenames;
   UED_data_dir.list_contents_by_type
       (UED_filenames   // The list to append contents to (association because dirent names are association
       ,false // not recursive
       ,true // qualify                 // true if the known path is prepended to the listed file names (differs from show_path because the path is actually included in the filename)
       ,true // with_extension          // true if the extension is included with the file name (usually true)
       ,true // show_path             // true if the known path is to be prepended when the filename is displayed
       ,true // show_extension        // true if the extension is to be appended when the filename is displayed
       ,Directory_entry_name::file_entry    // types of files to list (file or directory names)
       ,"UED" // This can be used to limit the list to certain extensions  (without dot)
       // , const char *unqualified_path = 0 // used for recursion (don't pass anything).
       );
   CORN::Smart_file_name map_file_name(map_name_unqual_no_ext,"htm");
   map_file_name.set_path(UED_data_dir);
   ofstream map_file(map_file_name.c_str());

   Geolocation center_point;
   CORN::Unidirectional_list locations; // List of geolocations
   CORN::Text_list markers;
   get_locations(UED_filenames,locations,markers,center_point);
   write_start(map_file,center_point);
   generate_points(map_file,locations,markers);
   write_end(map_file);
};
//______________________________________________________________________________
int main(int argc, const char *argv[])
{
   CORN::Smart_directory_name UED_data_dir
      ((argc == 2)
         ? argv[1]   // Optional directory name that is expected to contain UED files
         : "");      // If no directory name is specified, then the current working directory is used.
   return UED_data_dir.exists()
   ? (map_UED_locations(UED_data_dir,"locations_map") > 0) ? 0 : 1
   : 1;
};
//______________________________________________________________________________
