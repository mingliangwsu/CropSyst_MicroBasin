#include "coordinates.h"
#include "corn/OS/file_system_engine.h"
#include "common/geodesy/geolocation_item.h"
#include "corn/seclusion.h"
#include <assert.h>

namespace geodesy
{
//______________________________________________________________________________
Coordinates::Arguments::Arguments()
: CORN::Arguments()
, geocoordinates_filename(0)
, ID_fieldname("ID")                                                             //171111
//NYI , predefined_extent()
, cell_dimension()
, precision_latitude(2)
, precision_longitude(2)
, CS_geocoordinates_dir(0)                                                       //180318
, zone(0)                                                                        //180816
, zone_designator(0)                                                             //180816
{}
//_2016-08-25___________________________________________________________________
Coordinates::Arguments::~Arguments()
{  delete geocoordinates_filename;
}
//_2016-08-25___________________________________________________________________
//______________________________________________________________________________
bool Coordinates::Arguments::submit_DEN
(CORN::OS::Directory_entry_name *param_DEN)                          submission_
{  bool recognized = false;
   if ( (param_DEN->has_extension(L"DBF"))
      ||(param_DEN->has_extension(L"dbf")))
   {
      if (CORN::OS::file_system_engine.exists(*param_DEN))
      {
         geocoordinates_filename = param_DEN;
         recognized=true;
         recognized_count++;
      }
   }
   return recognized || CORN::Arguments::submit_DEN(param_DEN);
}
//_2018-02-13___________________________________________________________________
bool Coordinates::Arguments::submit_DEN_unqualified
(CORN::OS::Directory_entry_name *param_DEN_unqualified)       submission_
{
   bool recognized = false;
   if ( (param_DEN_unqualified->has_extension(L"DBF"))
      ||(param_DEN_unqualified->has_extension(L"dbf")))
   {
      geocoordinates_filename =
            CORN::OS::file_system_engine.find_file_name
               (param_DEN_unqualified->w_str()
               ,start_directory
               ,CORN::OS::File_system::superdirectory_recursion_inclusive
               //NYI may want to specify logical root
               );
      recognized = geocoordinates_filename != 0;
      recognized_count++;
   }
   return recognized || CORN::Arguments::submit_DEN_unqualified(param_DEN_unqualified);
}
//_2018-02-13___________________________________________________________________
bool Coordinates::Arguments::recognize(const std::string &paramstring) modification_
{  bool recognized = CORN::Arguments::recognize(paramstring);
   Geocoordinate_format surmised_format;                                         //161122
   if (!recognized)
   {
/*180318 now specified with --extent option
   if      (!predefined_extent.corner1.is_valid()) recognized = predefined_extent.corner1.set_from_ISO_6709(paramstring,surmised_format);
   else if (!predefined_extent.corner2.is_valid()) recognized = predefined_extent.corner2.set_from_ISO_6709(paramstring,surmised_format);
*/
        if (paramstring.find("km") != std::string::npos)
   {  std::string length_km_str(paramstring,0,paramstring.length()-2);
      cell_dimension.length_km = CORN::cstr_to_float32(length_km_str.c_str());
      recognized = true;
   }
   else if (paramstring.find("m") != std::string::npos)
   {  std::string length_m_str(paramstring,0,paramstring.length()-1);
      float32 length_m = CORN::cstr_to_float32(length_m_str.c_str());
      cell_dimension.length_km = m_to_km(length_m);
      recognized = true;
   }
   /* conceptual provide option to reference coordinate to
      centroid or SW NW  NE WE corner of grid cell
      (Note that ESRI grids are SW corner oriented
      currently always centroid
   else if (paramstring == "centroid")
   {  centroid = true
      recognized = true;
   }
   */

/* Warning eventually this needs to be Coordinate::Item

   else                                                                          //180318
   {
      // Warning eventually this needs to be Coordinate::Item

      Geocoordinate_item *geocoord = new Geocoordinate_item(paramstring);
      if (geocoord->is_valid()) // if the argument is a geocoordinate ISO format
      {
         specific_geocoordinates.take(geocoord);
         recognized = true;
      }
      else delete geocoord;
   }
*/
   }
   return recognized || CORN::Arguments::recognize(paramstring);                 //170831
}
//______________________________________________________________________________
bool Coordinates::Arguments::recognize_assignment
      (const std::string &variable
      ,const std::string &value)                                  modification_
{  bool recognized = false;
   if (  (variable == "--precision_latitude"))
   {
      precision_latitude = (nat8)CORN::cstr_to_nat16(value.c_str(),10);
      recognized = true;
   } else if (  (variable == "--precision_longitude"))
   {
      precision_longitude = (nat8)CORN::cstr_to_nat16(value.c_str(),10);
      recognized = true;
   } else if (variable == "--ID")
   {  ID_fieldname = value;
      recognized = true;
   } else if (variable == "--UTMzone")
   {  std::string zone_str(value,0,3);
      zone = CORN::cstr_to_int16(zone_str.c_str(),10);
      zone_designator = variable[3];
   } else if (variable == "--CS_geocoordinates")                                 //180318
   {
      CS_geocoordinates_dir = new CORN::OS::Directory_name_concrete(value);
      recognized = true;
   }
/*NYI need Extent using Coordinate::Item
   else if (variable == "--extent")                                            //180318
   {  predefined_extent.set(value);
      recognized = true;
   }
*/
  return recognized || CORN::Arguments::recognize_assignment(variable,value);
}
//_2017-08-28___________________________________________________________________
bool Coordinates::Arguments::get_end()
{  bool ended = CORN::Arguments::get_end();                                      //161023
   if (!geocoordinates_filename && CORN::is_approximately<float32>(cell_dimension.length_km,0.0,0.00000001))
       geocoordinates_find(false);
   return ended;                                                                 //161023
}
//______________________________________________________________________________
bool Coordinates::Arguments::geocoordinates_find_file(const char *extension_raw)
{
   std::clog
      << "info: searching path directories for geocoordinates."
      << extension_raw << std::endl;
   CORN::OS::Directory_entry_name_concrete CWD;
   std::wstring geocoordinate_ext = L"geocoordinates.";
      CORN::append_ASCIIZ_to_wstring(extension_raw,geocoordinate_ext);
   geocoordinates_filename
      =  CORN::OS::file_system_engine.find_file_name
         (geocoordinate_ext.c_str(),CWD
         ,CORN::OS::File_system::superdirectory_recursion_inclusive
         ,0,FILENAME_CASE_INSENSITIVITY);
   if (!geocoordinates_filename) // if still not found
   {
      std::clog << "info: searching path directories for any file(s) with extension:" << extension_raw<< std::endl;
      CORN::Unidirectional_list any_EXT_files;
      std::string wildcard_and_ext = "*.";
      CORN::append_ASCIIZ_to_string(extension_raw,wildcard_and_ext);
      CORN::Inclusion EXT_inclusion(wildcard_and_ext.c_str(),true);
      nat32 matching_file_count = CORN::OS::file_system_engine.list_DENs //list_entry_names
         (CWD,&any_EXT_files,0,EXT_inclusion
         ,CORN::OS::File_system::superdirectory_recursion_inclusive);
      if (matching_file_count == 1)
      {  geocoordinates_filename = dynamic_cast<CORN::OS::File_name *>(any_EXT_files.pop_at_head());
         std::clog
            << "info: presuming the one file found contains point geocoordinates" << std::endl
            << "file: " << geocoordinates_filename->c_str() << std::endl;
      }
      else if (matching_file_count > 1)
      {  // Multiple DBF files were found in the path.
         // List them and prompt user which one
         int32 selection = 0;
         do
         {  int f = 0;
            if (verbose || !quiet)                                               //170223
            {  std::clog << "Multiple potential dbf tables found" << std::endl;
               FOR_EACH_IN(matching_file, CORN::OS::File_name, any_EXT_files, each_matching)
               {  f++;
                  std::clog  << (int) f << '\t' << matching_file->c_str() << std::endl;
               } FOR_EACH_END(each_matching)
            }
            if (quiet)                                                           //170223
               // select the last listed (closest) table file.
               selection = matching_file_count;                                  //170223
            else
            {  std::cout << "Enter file number (enter 0 if none of these)" << std::endl;
               std::cin >> selection;
            }
            if (selection > 0)
            {  nat32 selection_index = selection - 1;
               geocoordinates_filename = dynamic_cast<CORN::OS::File_name *>(any_EXT_files.get_at(selection_index));
               any_EXT_files.detach(geocoordinates_filename);
            }
         } while (selection > (int) matching_file_count);
      }
   }
   return geocoordinates_filename != 0;
}
//______________________________________________________________________________
bool Coordinates::Arguments::geocoordinates_find(bool must_exist)
{  bool provided = false;
   // At this point geocoordinates file was not specified on the command line
   if (!must_exist)
   {  std::clog << "info: searching for optional Geocoordinates (points) file." << std::endl; }
      std::clog
      << "info: Geocoordinates file was not specified on the command line" << std::endl;
   if (! geocoordinates_find_file("dbf"))
   {  if (! geocoordinates_find_file("dat"))
      // if (!geocoordinates_filename) // if still not found
      {  std::clog << "info: no geocoordinate DBF file found in the path." << std::endl;
         if (must_exist)
         {
            std::clog << "prompt: Enter required geocoordinates filename to proceed." << std::endl;
            std::clog << "  this may be a .DBF or .dat tab or space delimited text file with one column header line identifying  ISO6709 geocoordinate or latitude and longitude and elevation (optional)." << std::endl;
            std::string geocoord_filename;
            std::cin >> geocoord_filename;
            bool entered = geocoord_filename.length();
            if (entered)
               geocoordinates_filename = new CORN::OS::File_name_concrete(geocoord_filename);
         }
      }
   }
   provided =
      (geocoordinates_filename != 0)
      && CORN::OS::file_system_engine.exists(*geocoordinates_filename);
   return provided;
}
//______________________________________________________________________________
Coordinates::Item::Item()
: CORN::Item()
, geocoordinate(0)
, UTM_coordinate(0)
{}
//______________________________________________________________________________
Coordinates::Item::Item(Geocoordinate     *geocoordinate_)
: CORN::Item()
, geocoordinate(geocoordinate_)
, UTM_coordinate(0)
{}
//______________________________________________________________________________
Coordinates::Item::Item(UTM_Coordinate    *UTM_coordinate_)
: CORN::Item()
, geocoordinate(0)
, UTM_coordinate(UTM_coordinate_)
{}
//______________________________________________________________________________
Geocoordinate &Coordinates::Item::geo()                               provision_
{  if (!geocoordinate)
      geocoordinate = new Geocoordinate();
   return *geocoordinate;
}
//_Coordinate::Item::geo______________________________________________________________
UTM_Coordinate &Coordinates::Item::UTM()                              provision_
{
   if (!UTM_coordinate)
      UTM_coordinate = new UTM_Coordinate();
   return *UTM_coordinate;
}
//_Coordinate::Item::UTM______________________________________________________________
bool Coordinates::Item::is_in_northern_hemisphere()                     affirmation_
{
   return
      geocoordinate
      ? geocoordinate->is_in_northern_hemisphere()
      : UTM_coordinate
         ? UTM_coordinate->is_in_northern_hemisphere()
         : false;
}
//_Coordinate::Item::is_in_northern_hemisphere______________________________________________________________
} // namespace geodesy
#pragma package(smart_init)
