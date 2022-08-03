#ifndef soil_generatorH
#define soil_generatorH
//______________________________________________________________________________
#include "USDA/NRCS/soil/survey/database/STATSGO_SSURGO_database.h"
#include "USDA/NRCS/soil/survey/database/tabular/mapunit.h"
#include "USDA/NRCS/soil/survey/database/tabular/component.h"
#include "common/geodesy/geolocation.h"
#include "common/soil/texture.h"
#include "corn/data_source/datarec.h"
#include "common/database/soil/provider/soil_provider_common.h"

#define SEARCH_CONTAINER CORN::Association_search_tree
namespace CORN
{  class Data_table;
   class Container;
   class Association_search_tree;
}
namespace USDA_NRCS
{
   class CHorizon;
}
extern char *latitude_fieldname;
extern char *longitude_fieldname;
extern char *cell_fieldname;
//______________________________________________________________________________
namespace STATSGO2
{
class Mapunit_composition;
// ______________________________________________________________________________
class Component_composition
: public CS::Component_composition                                               //141015
{
 public:
   USDA_NRCS::Component component;
   USDA_NRCS::Capability_class_labeled &irrcapcl; // for debugging
   USDA_NRCS::Capability_class_labeled &nirrcapcl; // for debugging
   inline Component_composition()
      : CS::Component_composition(component.comppct.repr)                        //141015
      , irrcapcl(component.irrcapcl)
      , nirrcapcl(component.nirrcapcl)
      {}
   bool compose(const USDA_NRCS::CHorizon &chorizon);
   bool compose_meta(const USDA_NRCS::Mapunit &map_unit);
   USDA_texture::Texture_code lookup_texture_description
      (const std::string chorizon_chkey
      ,float32 &horizon_sand
      ,float32 &horizon_clay
      ,float32 &horizon_silt);
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return component.cokey == key; }

/*180820  was probably only used for find_cstr now using is_key
   inline virtual const char *get_key() const { return component.cokey.c_str();}
*/   
};
// ______________________________________________________________________________
class Mapunit_composition
: public CS::Mapunit_composition
{public:
      // Geolocation may be optionally specified in points of filter_intersection table.
   USDA_NRCS::Mapunit mapunit;
   Component_composition *predominate_component;
      // This is the same as predominate_component_composition but
      // as STATSGO::Component_composition.
   bool find_by_component;
 public:
   inline Mapunit_composition()
      : CS::Mapunit_composition()
      , mapunit()
      , find_by_component(false)
      {}
   inline virtual bool is_key(const std::string &key)              affirmation_  //180820
      { return 
         find_by_component && predominate_component
            ? predominate_component->is_key(key) // 180820 get_key()
            : mapunit.mukey == key);      
      }

/*180820  was probably only used for find_cstr now using is_key
   inline virtual const char *get_key()                                    const
      { return find_by_component && predominate_component
            ? predominate_component->get_key()
            : mapunit.mukey.c_str();
      }
*/      
 public:
   Component_composition *provide_component_composition(const std::string &cokey);
   inline void key_on_component()                  { find_by_component = true; }
   inline void key_on_mapunit()                   { find_by_component = false; }
   bool compose(USDA_NRCS::CHorizon &chorizon);
   virtual bool commit();
 public:
   bool is_more_agricultural_than_predominant
      (const USDA_NRCS::Component &new_component)                         const;
};
// ________________________________________________________Mapunit_composition_/
class Soil_generator
: public CS::Soil_provider                                                       //141001
{
/* This is an abstract class
A derived class needs to implement a method to write the soil data
to a target file format.
*/
   USDA_NRCS::STATSGO2_SSURGO::Database STATSGO2_database;   // rename this to database?
 protected:
   const USDA_NRCS::STATSGO2_SSURGO::Database::Arguments &arguments;
   /*moved to arguments
   nat8 aggregation_option;
      //   0=Extract map unit soil components
      //   1=Aggregate soil sequences in each map unit to create an aggregated representitive pseudopedon
      //   2=Use primary component as a representitive pedon
   */
   contribute_ nat32 searching_for_specific_mapunit;
   contribute_ Mapunit_composition *found_specific_mapunit;
 public:
   Soil_generator
      ( const USDA_NRCS::STATSGO2_SSURGO::Database::Arguments &arguments_
      ,const CORN::Seclusion &mapunit_seclusion_                                 //170903
      /*170831 moved to arguments
       const CORN::OS::Directory_name &STATSGO2_database_directory
      ,const CORN::OS::Directory_name &table_index_directory
      ,nat8 aggregation_option
      */
      );
 public:
   /*170903 obsolete because now using mapunit_seclusion
   nat32 filter_mapunits_in_table(CORN::Data_table &table);
   nat32 filter_mapunits_in_list_string(const std::string &mukey_list);
   */
   virtual nat32 generate()                                          rendition_;
      /**<
      This method will render mapunits for all filtered mapunits.
      For each mapunit, the take() method will be called.
      Derived classes should override the take method
      to further process and/or output the map unit composition.
      The derived class is responsible for eventually deleted the
      rendered mapunit composition
              I.e. the take() method may delete it after writing it,
        , or store the composition and a directory structure which will
      be deleted later, or give it to another object for disposal   )
      **/
   virtual Mapunit_composition *render_selected_map_unit
      (const std::string &MUkey)                                     rendition_; //150927
   virtual Mapunit_composition *render_selected_map_unit(nat32 MUkey)rendition_; //150927
      /**< These method can be used to to render a single mapunit composition
       for the specified mapunit key.
      **/
   virtual Mapunit_composition *render_at_geocoordinate
      (const Geocoordinate &geocoordinate)                           rendition_; //150927

   virtual bool take( Mapunit_composition *map_unit)              contribution_; //150927   modification_;
   bool commit( Mapunit_composition &map_unit)                    contribution_; //150927   modification_;
      /**<
      Derived classed may optionally reimplement commit
      to add or augment data to the map_unit composition.
      In this case, the reimplementation will probably want
      to call this superclass's commit() method.
      **/
};
//_2011-10-21___________________________________________________Soil_generator_/
}
#endif
