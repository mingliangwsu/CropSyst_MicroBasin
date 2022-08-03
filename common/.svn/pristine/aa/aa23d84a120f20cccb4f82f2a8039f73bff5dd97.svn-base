#ifndef coordinatesH
#define coordinatesH
#include "corn/container/item.h"
#include "geodesy/geocoordinate.h"
#include "geodesy/UTM.h"
#include "corn/container/bilist.h"
#include "corn/application/arguments.h"
namespace geodesy
{
//______________________________________________________________________________
// Need to implement and Extent that uses Coordinate::Item


//______________________________________________________________________________
class Coordinates
: public extends_ CORN::Bidirectional_list
{
 public:
   class Item
   : public implements_ CORN::Item
   {
    protected:
      provided_ Geocoordinate     *geocoordinate;
      provided_ UTM_Coordinate    *UTM_coordinate;
    public:
      Item();
      Item(Geocoordinate     *geocoordinate_);
      Item(UTM_Coordinate    *UTM_coordinate_);
    public:
      Geocoordinate     &geo()                                       provision_;
      UTM_Coordinate    &UTM()                                       provision_;

      virtual bool is_in_northern_hemisphere()                     affirmation_;

   };
   //_class_Item____________________________________________________2018-04-25_/
   struct Cell_dimension    // need name  Cell_topology?  Cell_dimensions?
   {
      float32       length_km; // currently assuming cell is square
      bool          centroid;
    public:
      inline Cell_dimension()
         : length_km(0)
         , centroid(true)
         {}
      inline Cell_dimension(const Cell_dimension &from_copy)
         : length_km(from_copy.length_km)
         , centroid (from_copy.centroid)
         {}
   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Arguments
   : public extends_ CORN::Arguments
   {
    public:
      CORN::OS::File_name *geocoordinates_filename; // Could be DBF or DAT
      std::string    ID_fieldname;                                            //171111
      // Extent         predefined_extent;                                       //170817
      Cell_dimension cell_dimension;
      nat8           precision_latitude;                                      //170829
      nat8           precision_longitude;                                     //170829
      CORN::OS::Directory_name_concrete *CS_geocoordinates_dir;                      //180318

      mutable CORN::Unidirectional_list specific_geocoordinates;                            //180318
         // was specific_points


      sint16 zone;                                                               //180816
      char   zone_designator;                                                    //180816
    public:
      Arguments();
      virtual ~Arguments();

      virtual bool submit_DEN
         (CORN::OS::Directory_entry_name *param_DEN)                submission_; //180213
      virtual bool submit_DEN_unqualified                                        //180213
         (CORN::OS::Directory_entry_name *param_DEN_unqualified)    submission_;

      virtual bool recognize(const std::string &paramstring)      modification_;
      virtual bool recognize_assignment                                          //170816
         (const std::string &variable
         ,const std::string &value)                               modification_;
      virtual bool get_end();                                                    //161023
      bool geocoordinates_find(bool must_exist);
      bool geocoordinates_find_file(const char *extension_raw);
   };

 public:
   inline Coordinates(const Arguments *arguments_=0)
      : CORN::Bidirectional_list(true) // must be unique
/*NYI
      , arguments(arguments_)
      , netCDF_grid_available(false)
      , extent(0)
      , geocoord_fields_dBase (0)
*/
      {}
   inline ~Coordinates()
      {
//NYI         delete geocoord_fields_dBase;
      }
};
//_class_Coordinates________________________________________________2018-04-15_/
} // namespace geodesy

#endif
