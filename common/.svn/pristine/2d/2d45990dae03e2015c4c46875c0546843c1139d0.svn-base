#include "common/geodesy/geocoordinates.h"
#include "common/geodesy/geometry/terrestrial_geometry.h"
#include "corn/seclusion.h"
#include "corn/OS/file_system_engine.h"
#include "corn/data_source/generic_datarec.h"
#include "corn/string/strconv.hpp"
#include "corn/data_source/VV_file.h"
namespace CS
{
//______________________________________________________________________________
Geocoordinates::Arguments::Arguments()
: geodesy::Coordinates::Arguments()                                              //180425
, predefined_extent()
{}
//_2016-08-25___________________________________________________________________
Geocoordinates::Arguments::~Arguments()
{  delete geocoordinates_filename;
}
//_2016-08-25___________________________________________________________________
bool Geocoordinates::Arguments::recognize(const std::string &paramstring) modification_
{
   bool recognized = geodesy::Coordinates::Arguments::recognize(paramstring);    //180425
   if (!recognized)                                                              //180425
   {
      Geocoordinate_item *geocoord = new Geocoordinate_item(paramstring);
      if (geocoord->is_valid()) // if the argument is a geocoordinate ISO format
      {
         specific_geocoordinates.append(geocoord);
         recognized = true;
      }
      else delete geocoord;
   }
   return recognized || CORN::Arguments::recognize(paramstring);                 //170831
}
//______________________________________________________________________________
bool Geocoordinates::Arguments::recognize_assignment
      (const std::string &variable
      ,const std::string &value)                                  modification_
{  bool recognized = false;
   recognized = geodesy::Coordinates::Arguments::recognize_assignment(variable,value); //180425
   if (!recognized)                                                              //180425
   if (variable == "--extent")                                            //180318
   {  predefined_extent.set(value);
      recognized = true;
   }
  return recognized || CORN::Arguments::recognize_assignment(variable,value);
}
//_2017-08-28___________________________________________________________________
nat32 Geocoordinates::load()
{  if (!arguments) return 0; /*grid file was not specified on command line */    //170817
   // if any (optional) specific points

   transfer_all_from(arguments->specific_geocoordinates);

   nat32 coord_count = 0;
   bool generate_grid = (arguments->cell_dimension.length_km > 0.000001)
       &&(arguments->predefined_extent.corner1.is_valid())
       &&(arguments->predefined_extent.corner2.is_valid());
   if (generate_grid)
   {  if (arguments->is_verbose(3)) //(verbose > 2)
         std::clog << "info: composing grid for specified extent." << std::endl
            << "assume: points are at grid cell centroid." << std::endl;
      coord_count += compose_from_predefined_extent
         (arguments->predefined_extent
         ,arguments->cell_dimension);
   }
   CORN::OS::File_name *geocoordinates_filename = arguments->geocoordinates_filename; //170817
   bool load_file = geocoordinates_filename;
   if (load_file) // filename specified, can probably load
   {  if (generate_grid)
      {  std::clog
            << "warn: both grid extent and grid table filename were specified on the command line, this is not an error but may result in duplicate and/or inconsistent points if the total extent overlaps." << std::endl
            << "file: " << geocoordinates_filename->c_str() << std::endl
            << "conceptual: cells in close proximity could be culled, contact Roger Nelson rnelson@wsu.edu if this needs to be implemented." << std::endl
            << "prompt: use also the table file (Y/N) ?" <<std::endl;
         std::string Y_N = "n";
         std::cin >> Y_N;
         load_file = (Y_N.c_str()[0] == 'Y') || (Y_N.c_str()[0] == 'y');
      }
   }
   if (load_file)
   {  bool load_DBF
         = geocoordinates_filename->has_extension(L"DBF")
         ||geocoordinates_filename->has_extension(L"dbf");
      coord_count += load_DBF
         ?  load_from_DBF(*geocoordinates_filename)                              //170902
         :  load_from_text(*geocoordinates_filename);                            //170902
   }
   if (load_file && (coord_count == 0))
   {  std::clog << "warn: no points loaded from geocoordinate file" << std::endl
            << " user: make sure geocoordinates exist in the file in the prescribed column(s): " << std::endl
            << /*arguments->*/geocoordinates_filename->c_str()
            << std::endl;
   }
   return coord_count;
}
//______________________________________________________________________________
nat32 Geocoordinates::load_from_text
(const CORN::OS::File_name &geocoordinates_filename)                             //170902
{  nat32 coord_count = 0;
/*
std::cout << "geocoord filename:" << geocoordinates_filename.c_str() << std::endl;
*/

   std::ifstream geocoord_strm(geocoordinates_filename.c_str());
   if (geocoord_strm.good())
   {
      std::string col_header;
      getline(geocoord_strm,col_header);
      while (!geocoord_strm.eof())
      {
         // Redo this so that it identifies columns from
         // column header

         Geocoordinate_item *geocoord = new Geocoordinate_item;
         float32 latitude;
         float32 longitude;
         //float32 elevation;
         geocoord_strm >> latitude >> longitude;
         geocoord->set_latitude_dec_deg_f32  (latitude);
         geocoord->set_longitude_dec_deg_f32 (longitude);
         //geocoord->set_elevation_meter       (elevation);
         if (geocoord->is_valid())
         {  append(geocoord);
            coord_count++;
         }
      }
   } else
      std::cerr << "error: unable to find open: "
         << geocoordinates_filename.c_str() << std::endl;
   return coord_count;
}
//______________________________________________________________________________
bool Geocoordinates::provide_fields_dBase(CORN::Data_source_dBase &/*DBF_file*/)  provision_
{  // DBF_file is not used here, but it is used in derived class implementations
   if (!geocoord_fields_dBase)
      geocoord_fields_dBase = new Fields_dBase;
   return geocoord_fields_dBase != 0;
}
//______________________________________________________________________________
bool Geocoordinates::setup_DBF_fields(CORN::Data_source_dBase &DBF_file)  provision_
{
   bool sat_up = provide_fields_dBase(DBF_file);
      geocoord_fields_dBase->geocoordinate_field = DBF_file.lookup_field("COORDINATE");
      if (!geocoord_fields_dBase->geocoordinate_field) geocoord_fields_dBase->geocoordinate_field = DBF_file.lookup_field("ISO6709");
      geocoord_fields_dBase->latitude = DBF_file.lookup_field("LATITUDE");
      if (!geocoord_fields_dBase->latitude)     geocoord_fields_dBase->latitude = DBF_file.lookup_field("LAT");
      if (!geocoord_fields_dBase->latitude)     geocoord_fields_dBase->latitude = DBF_file.lookup_field("YCOORD"); // QGIS (or GRASS) uses this
      geocoord_fields_dBase->longitude = DBF_file.lookup_field("LONGITUDE");
      if (!geocoord_fields_dBase->longitude)    geocoord_fields_dBase->longitude = DBF_file.lookup_field("LONG");
      if (!geocoord_fields_dBase->longitude)    geocoord_fields_dBase->longitude = DBF_file.lookup_field("LON");
      if (!geocoord_fields_dBase->longitude)    geocoord_fields_dBase->longitude = DBF_file.lookup_field("XCOORD"); // QGIS (or GRASS) uses this
      geocoord_fields_dBase->elevation = DBF_file.lookup_field("ELEVATION");
      if (!geocoord_fields_dBase->elevation)    geocoord_fields_dBase->elevation = DBF_file.lookup_field("ELEV");
      // Elevation is essentially optional.
   return sat_up;
}
//______________________________________________________________________________
bool Geocoordinates::table_has_a_geocoordinate_fields()               affirmation_
{     return
        geocoord_fields_dBase->geocoordinate_field
    || (geocoord_fields_dBase->latitude || geocoord_fields_dBase->longitude );
}
//_2017-05-10_____________________________________________________________________________
Geocoordinate_item *Geocoordinates::render_geocoordinate()            rendition_
{  return new Geocoordinate_item;
}
//______________________________________________________________________________
bool Geocoordinates::set_from_record
(CORN::Generic_data_record &geocoord_rec
,Geocoordinate &geocoord)
{
   // dBase records only have one generic aribtrarily named primary section
   CORN::VV_Section *section = geocoord_rec.get_current_section();
         if (geocoord_fields_dBase->geocoordinate_field)
         {  CORN::VV_string_entry *geocoordinate_entry =
               dynamic_cast<CORN::VV_string_entry *>
                  (section->entries. find_cstr(geocoord_fields_dBase->geocoordinate_field-> get_name(),false)); //180827
                  //180827 (section->entries.find_cstr(geocoord_fields_dBase->geocoordinate_field->get_key(),false)); need to replace
            if (geocoordinate_entry)
            {  std::string geocoord_string;
               geocoordinate_entry->append_to_string(geocoord_string);
               geocoord.set_from_ISO_6709(geocoord_string,geocoord_fields_dBase->geocoordinate_format);
            }
         }
         if (geocoord_fields_dBase->latitude)
         {  CORN::VV_float32_entry *latitude_entry =
               dynamic_cast<CORN::VV_float32_entry *>
                  (section->entries.find_cstr(geocoord_fields_dBase->latitude->get_name/*180827 get_key*/(),false));
            if (latitude_entry)
               geocoord.set_latitude_dec_deg_f32(latitude_entry->get_value());
         }
         if (geocoord_fields_dBase->longitude)
         {  CORN::VV_float32_entry *longitude_entry =
               dynamic_cast<CORN::VV_float32_entry *>
                  (section->entries.find_cstr(geocoord_fields_dBase->longitude->get_name/*180827 get_key*/(),false));
            if (longitude_entry)
               geocoord.set_longitude_dec_deg_f32(longitude_entry->get_value());
         }
         if (geocoord_fields_dBase->elevation)
         {  CORN::VV_float32_entry *elevation_entry =
               dynamic_cast<CORN::VV_float32_entry *>
                  (section->entries.find_cstr(geocoord_fields_dBase->elevation->get_name/*180827 get_key*/(),false));
            if (elevation_entry)
               geocoord.set_elevation_meter(elevation_entry->get_value());
         }
   return true;
}
//______________________________________________________________________________
nat32 Geocoordinates::load_from_DBF
(const CORN::OS::File_name &geocoordinates_filename)                             //170902
{
   //170902 if (!arguments) return 0;                                                     //170817
   // DBF field names are case insensitive
   // (although the original file format only stored uppercase
   //170902 CORN::OS::File_name *geocoordinates_filename = arguments->geocoordinates_filename; //170817
   //170902 if (!geocoordinates_filename) return 0;                                       //170817
   nat32 records_read = 0;
   nat32 records_valid = 0;
   nat32 records_unique = 0;                                                     //170902
   nat8 verbose = arguments ? arguments->verbose : 0;                            //170921_170817
   if (verbose > 2) //level
      std::clog << "info: loading geocoordinates from " << std::endl
      << geocoordinates_filename.c_str() << std::endl;
   CORN::Data_source_dBase DBF_file
      (geocoordinates_filename.c_str(),std::ios_base::in);
   DBF_file.initialize();
   bool satup = setup_DBF_fields(DBF_file);                                      //170510
   CORN::Generic_data_record *geocoord_rec = DBF_file.render_generic_data_record();
   if (!table_has_a_geocoordinate_fields())
   {  std::cerr << "warn: no geocoordinate field(s) found in:"
         << geocoordinates_filename.c_str()
         << std::endl
         << "info: not an error because each records could simply represent a point by ID or UTM coordinate."
         << std::endl;
   }
   if (satup && geocoord_rec /*moved && table_has_a_geocoordinate_fields()*/)    //170510
   {  // This table appears to have geocoordinates
      records_unique= load_from_table(DBF_file,records_read,records_valid,*geocoord_rec); //170902
   } else
   {  std::cerr << "error: unabled to setup geocoordinates/points file in:"
         << geocoordinates_filename.c_str()
          << std::endl
         << "info: perhaps not a valid DBF file, or it may be locked (by Excel?)."
         << std::endl;
   }
   delete geocoord_rec;
   return records_unique;
}
//_______________________________________________________________load_from_DBF_/
nat32 Geocoordinates::load_from_table
(CORN::Data_table &table
,nat32 &records_read
,nat32 &records_valid
,CORN::Generic_data_record &geocoord_rec
// geocoord_rec is just a buffer record of the type usable by the database
// so we are not constantly instanciating one (it is merely contributory
// is is not an output!.
)
{
   nat8 verbose = arguments && arguments->verbose;                               //170817
   for (bool more_records = table.goto_first()
       ;more_records
       ;more_records = table.goto_next())
   {  table.get(geocoord_rec);
      Geocoordinate_item *geocoord = render_geocoordinate();
      records_read += set_from_record(geocoord_rec,*geocoord );
      if (!is_geocoordinates_required() || geocoord->is_valid())
      {  append(geocoord);
         records_valid++;
      } else
      {  delete geocoord;
         std::clog << "warn: invalid geocoordinate in record #" << records_read <<std::endl;
      }
   }
   if (records_valid < records_read)
      std::clog << "warn: invalid geocoordinates found, count=" << records_read - records_valid << std::endl;
   nat32 records_unique = count();
   if (records_unique < records_valid)
      std::clog << "warn: duplicate geocoordinates found, unique=" <<  records_unique << std::endl;
   if (verbose > 1) //count
      std::clog << "info: unique valid records encountered=" << records_unique << " out of=" << records_read << std::endl;
   return records_unique;
}
//_2017-09-02__________________________________________________load_from_table_/
nat32 Geocoordinates::load_from_directory(const CORN::OS::Directory_name &dir)
{  nat32 geocoord_count = 0;
   CORN::Text_list potential_geocoord_files;
   CORN::Text_list potential_geocoord_dirs;
      // Lists all DENs in the specified directory, and those
      // where the name  (or extension?) is a geocoordinate will be listed
   CORN::OS::file_system_engine.list_names_in
      (dir,&potential_geocoord_files,&potential_geocoord_dirs);

   FOR_EACH_IN(pot_geocoord_file,CORN::Item ,potential_geocoord_files,each_gf)
   {
      Geocoordinate_item *geocoord = render_geocoordinate();
      {
      std::string pot_geocoord_file_raw;
      pot_geocoord_file->append_to_string(pot_geocoord_file_raw);
      bool name_is_geocoor = geocoord->set_latitude_and_longitude(pot_geocoord_file_raw); //180205

      if (name_is_geocoor)
      {  append(geocoord);
         geocoord_count++;
      } else
      {  delete geocoord;
         // not an error or warning, geocoord named file/dirs are not necessarily expected
      }
      }
   } FOR_EACH_END(each_gf)

   FOR_EACH_IN(pot_geocoord_dir,CORN::Item,potential_geocoord_dirs,each_gd)
   {
      Geocoordinate_item *geocoord = render_geocoordinate();
      std::string pot_geocoord_dir_raw;
      pot_geocoord_dir->append_to_string(pot_geocoord_dir_raw);                   //180205
      if (pot_geocoord_dir_raw.find("_") != std::string::npos)
      {
         // This is an extent which I am currently not processing
      }
      else
      {

      bool name_is_geocoor = geocoord->set_latitude_and_longitude(pot_geocoord_dir_raw); //180205
      if (name_is_geocoor)
      {  append(geocoord);
         geocoord_count++;
      } else
      {  delete geocoord;
         // not an error or warning, geocoord named file/dirs are not necessarily expected
      }
      }
   } FOR_EACH_END(each_gd)
   return geocoord_count;
}
//_load_from_directory______________________________________________2018-01-05_/
class Geocoord_record
: public Geocoordinate_item
, public CORN::Data_record
{
 public:
   inline Geocoord_record()
      : CORN::Data_record("geocoordinate")
      {}
   inline virtual bool expect_structure(bool for_write)
      { return Geocoordinate::setup_structure(*this,for_write);
      }
   virtual int compare(const CORN::Item &other)                            const //180318
      {
         const Geocoordinate &other_as_geocoor = dynamic_cast<const Geocoordinate &>(other);
         return Geocoordinate::compare(other_as_geocoor);
      }
};
//_Geocoord_record__________________________________________________2018-03-18_/
nat32 Geocoordinates::load_CS_geocoordinates()
{  nat32 geocoord_count = 0;
   if (!arguments->CS_geocoordinates_dir) return 0;
   CORN::Unidirectional_list geocoord_files;
   CORN::OS::file_system_engine.list_DENs
      (*(arguments->CS_geocoordinates_dir)
      ,&geocoord_files,0
      ,CORN::Inclusion("*.CS_geocoordinate",false)
      ,CORN::OS::File_system::subdirectory_recursion_inclusive);

   FOR_EACH_IN(geocoord_file_name,CORN::OS::File_name,geocoord_files,each_geocoor)
   {
      Geocoord_record *geocoord_rec = new Geocoord_record;
      CORN::VV_File geocoord_file(geocoord_file_name->c_str());
      if (geocoord_file.get(*geocoord_rec))
      {
         if (geocoord_rec->is_valid())
         {
            geocoord_count++;
            append(geocoord_rec);
         } else
         {
            std::clog << "warn: invalid geocoordinate file "
               << geocoord_file_name->c_str() << std::endl;
         }
      }
   } FOR_EACH_END(each_geocoor)
   return geocoord_count;
}
//_load_CS_geocoordinates___________________________________________2018-03-18_/
nat32 Geocoordinates::compose_from_predefined_extent
(const Extent &predefined_extent                                                 //170817
,const Cell_dimension &cell_dimension)                                           //170818
{
   // Actually could have extent structure which would be member/superclass
   // of Arguments

   nat32 points = 0;

   extent = new Extent(predefined_extent);

   // Actually at this point the corners should be normalized

   Geocoordinate corner_SW
      (std::min<float32>(extent->corner1.get_latitude_dec_deg() ,extent->corner2.get_latitude_dec_deg())
      ,std::min<float32>(extent->corner1.get_longitude_dec_deg(),extent->corner2.get_longitude_dec_deg()));
   Geocoordinate corner_NW
      (std::max<float32>(extent->corner1.get_latitude_dec_deg(), extent->corner2.get_latitude_dec_deg())
      ,std::min<float32>(extent->corner1.get_longitude_dec_deg(),extent->corner2.get_longitude_dec_deg()));
   Geocoordinate corner_SE
      (std::min<float32>(extent->corner1.get_latitude_dec_deg(), extent->corner2.get_latitude_dec_deg())
      ,std::max<float32>(extent->corner1.get_longitude_dec_deg(),extent->corner2.get_longitude_dec_deg()));
   Geocoordinate corner_NE
      (std::max<float32>(extent->corner1.get_latitude_dec_deg(), extent->corner2.get_latitude_dec_deg())
      ,std::max<float32>(extent->corner1.get_longitude_dec_deg(),extent->corner2.get_longitude_dec_deg()));
   Terrestrial_geometry geometry;
   float32 vertical_distance_km   = geometry.distance_between_km(corner_SW,corner_NW);
   float32 horizontal_distance_km = geometry.distance_between_km(corner_SW,corner_SE);
   float32 delta_km = cell_dimension.length_km;
   nat32 rows = vertical_distance_km    / delta_km;
   nat32 cols = horizontal_distance_km  / delta_km;
   float32 centroid_offset = cell_dimension.centroid ? delta_km / 2.0 : 0.0;
   if (arguments && arguments->verbose > 2) //count
      std::clog << "info: rows="<<rows<<" cols="<<cols<< std::endl;
   for (nat32 row = 0; row < rows; row++)
   {  float32 row_offset_km = (row * delta_km) + centroid_offset;
      for (nat32 col = 0; col < cols; col++)
      {  float32 col_offset_km = (col * delta_km) + centroid_offset;
         Geocoordinate cursor(corner_SW);
         geometry.latitude_delta_km(row_offset_km,cursor);
         geometry.longitude_delta_km(col_offset_km,cursor);
         Geocoordinate_item *cursor_item = new Geocoordinate_item(cursor);
         append(cursor_item);
         points ++;
      }
   }
   return points;
}
//_compose_from_predefined_extent___________________________________2016-09-26_/
const Geocoordinate *Geocoordinates::find_nearest
(const Geocoordinate &point
,float32 minimum_inclusion_distance
,float32 maximum_inclusion_distance)                                       const
{  Terrestrial_geometry geometry; // (could be a member)
   float64 nearest_distance = 20100.0; // km
   // (half the circumference of Earth is about 20038.0)
   Geocoordinate *nearest_geocoord = 0;
   FOR_EACH(geocoord,Geocoordinate_item,each_geocoord)
   {
      float64 distance = geometry.distance_between_km(point,*geocoord);
      if (   (distance <  nearest_distance + 0.000000001)
          && (distance >= minimum_inclusion_distance)
          && (distance <= maximum_inclusion_distance))
      {
         nearest_distance = distance;
         nearest_geocoord = geocoord;
      }
   } FOR_EACH_END(each_geocoord)
   return nearest_geocoord;
}
//_find_nearest_____________________________________________________2017-06-12_/
const Geocoordinate_item *Geocoordinates::find_nearest_item
(const Geocoordinate &point
,float32 minimum_inclusion_distance
,float32 maximum_inclusion_distance)                                       const
{  Terrestrial_geometry geometry; // (could be a member)
   float64 nearest_distance = 20100.0; // km
   // (half the circumference of Earth is about 20038.0)
   Geocoordinate_item *nearest_geocoord = 0;
   FOR_EACH(geocoord,Geocoordinate_item,each_geocoord)
   {
      float64 distance = geometry.distance_between_km(point,*geocoord);
      if (   (distance <  nearest_distance + 0.000000001)
          && (distance >= minimum_inclusion_distance)
          && (distance <= maximum_inclusion_distance))
      {
         nearest_distance = distance;
         nearest_geocoord = geocoord;
      }
   } FOR_EACH_END(each_geocoord)
   return nearest_geocoord;
}
//_find_nearest_item________________________________________________2017-06-12_/
const Geocoordinates::Extent &Geocoordinates::provide_extent()        provision_
{  if (!extent)
   //1if (north_west_most < -90.0) // extent not yet identified
   {  extent = new Extent;
      FOR_EACH(geocoord,Geocoordinate_item,each_coord)
      {  extent->north_most  = std::max<float32>(extent->north_most,geocoord->get_latitude_dec_deg());
         extent->south_most  = std::min<float32>(extent->south_most,geocoord->get_latitude_dec_deg());
         extent->east_most   = std::max<float32>(extent->east_most ,geocoord->get_longitude_dec_deg());
         extent->west_most   = std::min<float32>(extent->west_most ,geocoord->get_longitude_dec_deg());
      } FOR_EACH_END(each_coord)
      extent->update_corners_from_extremes();
   }
   return *extent;
}
//_provide_extent___________________________________________________2017-08-17_/
Geocoordinates::Extent *Geocoordinates::Extent::render_little_larger() rendition_
{
   Geocoordinates::Extent *larger_extent = new Geocoordinates::Extent(*this);
   // was 0.01
   // Extend the southmost corner whatever that is
   if (larger_extent->corner1.latitude_dec_deg < larger_extent->corner2.latitude_dec_deg)
        larger_extent->corner1.latitude_dec_deg   -= 0.01;
   else larger_extent->corner2.latitude_dec_deg   -= 0.01;

   larger_extent->corner2.longitude_dec_deg  += 0.01;
   larger_extent->south_most  -= 0.01;
   larger_extent->east_most   += 0.01;
   return larger_extent;
}
//_render_little_larger_____________________________________________2017-10-30_/
bool Geocoordinates::Extent::update_corners_from_extremes()        modification_
{
   corner1.set_latitude_dec_deg_f32   (south_most);
   corner1.set_longitude_dec_deg_f32  (east_most);
   corner2.set_latitude_dec_deg_f32   (north_most);
   corner2.set_longitude_dec_deg_f32  (west_most);
   return true;
}
//_update_corners_from_extremes_____________________________________2018-02-16_/
bool CS::Geocoordinates::Extent::compose_query_NCSS(std::string &query)    const
{  // appends REST query string to the query
   // https://www.unidata.ucar.edu/software/thredds/v5.0/tds/reference/services/NcssGrid.html
   query.append("north=");
   CORN::append_float32_to_string(north_most,6,query);
   query.append("&");
   query.append("west=");
   CORN::append_float32_to_string(west_most,6,query);
   query.append("&");
   query.append("south=");
   CORN::append_float32_to_string(south_most,6,query);
   query.append("&");
   query.append("east=");
   CORN::append_float32_to_string(east_most,6,query);
   return true;
}
//_compose_query_NCSS_______________________________________________2017-08-22_/
bool CS::Geocoordinates::Extent::compose_name
(std::string &name_raw)                                                    const
{  Geocoordinate northwest_most(north_most,west_most);
   Geocoordinate southeast_most(south_most,east_most);
   northwest_most.label_decimal_degrees_with_format(name_raw,true,2,2,'0');
   name_raw.append("_");
   southeast_most.label_decimal_degrees_with_format(name_raw,true,2,2,'0');
   return true;
}
//_compose_name_____________________________________________________2017-08-23_/
bool CS::Geocoordinates::Extent::set(const std::string &name)
{
   std::size_t  underscore_pos = name.find('_');
   bool valid = underscore_pos != std::string::npos;
   if (valid)
   {
      std::string point_1_ISO_6709(name,0,underscore_pos);
      std::string point_2_ISO_6709(name,underscore_pos+1);
      Geocoordinate_format surmised_format;
      corner1.set_from_ISO_6709(point_1_ISO_6709,surmised_format);
      corner2.set_from_ISO_6709(point_2_ISO_6709,surmised_format);
         // This constructor takes an extent name as composed from compose_name()
         // I.e. 29.85N081.56W_29.60N081.44W
      {  north_most  = std::max<float32>(corner1.get_latitude_dec_deg() ,corner2.get_latitude_dec_deg());
         south_most  = std::min<float32>(corner1.get_latitude_dec_deg() ,corner2.get_latitude_dec_deg());
         east_most   = std::max<float32>(corner1.get_longitude_dec_deg(),corner2.get_longitude_dec_deg());
         west_most   = std::min<float32>(corner1.get_longitude_dec_deg(),corner2.get_longitude_dec_deg());
      }
   } // else the extent is not in name format
   return is_valid();
}
//_set______________________________________________________________2017-10-11_/
CS::Geocoordinates::Extent::Extent(const std::string &name)
{  set(name);
}
//_Extent_constructor_______________________________________________2017-10-11_/
CS::Geocoordinates::Extent::Extent(const std::wstring &name)
{  std::string name_str; CORN::wstring_to_string(name,name_str);
   set(name_str);
}
//_Extent_constructor_______________________________________________2017-10-11_/
CS::Geocoordinates::Extent::Extent(const char *name)
{  std::string name_str(name);
   set(name_str);
}
//_Extent_constructor_______________________________________________2017-10-11_/
bool CS::Geocoordinates::Extent::contains_point
(const Geocoordinate &point)                                        affirmation_
{
   float32 latitude  = point.get_latitude_dec_deg();
   float32 longitude = point.get_longitude_dec_deg();
   bool contains =
      ((latitude >= south_most) && (latitude  <= north_most) &&
       (longitude >= west_most) && (longitude <= east_most));
   return contains;
}
//_Extent::contains_point___________________________________________2017_10_11_/
bool CS::Geocoordinates::Extent::is_valid()                         affirmation_
{  return corner1.is_valid() && corner2.is_valid();
}
//_Extent::is_valid()_______________________________________________2017_10_11_/
bool CS::Geocoordinates::Extent::is_single_point()                  affirmation_
{  return corner1.compare(corner2) == 0;
}
//_Extent::is_single_point()________________________________________2017_10_30_/
} // namespace CS

