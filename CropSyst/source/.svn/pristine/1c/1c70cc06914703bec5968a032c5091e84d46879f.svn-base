#include "Project/GIS/aggregate.h"
#include "corn/data_source/generic_datarec.h"
#include "corn/data_source/dbase_datasrc.h"
#include "corn/file_sys/smart_dirname.h"
#include "corn/container/enumlist.h"
#include "project/GIS/GIS_table.h"
using namespace std;
//______________________________________________________________________________
Tally_aggregator::Tally_aggregator
(const char          *_tally_table_dbf
,const char          *_polygon_ID_attribute
,Dynamic_int32_indexed_dBase_data_source   &_GIS_table
,STATSGO::Database    &_STATSGO_database
,nat8                _upto_capability_class                                      //051115
,bool                _with_irrigation)                                           //051115
: tally_table_dbf(_tally_table_dbf)
, aggregate_table_dbf(_tally_table_dbf)
, GIS_table(_GIS_table)
, STATSGO_database(_STATSGO_database)
, polygon_ID_attribute(_polygon_ID_attribute)
, upto_capability_class(_upto_capability_class)                                  //051115
, with_irrigation(_with_irrigation)                                              //051115
{
   CORN::Directory_name GIS_directory;
   tally_table_dbf.get_path(GIS_directory/* no \ ,true*/);
   CORN::Smart_directory_name GIS_aggregation_directory("aggregation");          //091030
   GIS_aggregation_directory.set_path(GIS_directory);                            //091030
   GIS_aggregation_directory.create();
   aggregate_table_dbf.set_path(GIS_aggregation_directory.c_str());
}
//______________________________________________________________________________
class Polygon_aggregation
: public Enumeration
{  sint32 polygon_ID; // Signed because negative number is offsite indicator
                     // However we don't currently process offsite polygons
   int16 cropable_percentage;  // This is the sum of the component percentages for components that were run/duplicates.  This should be equivelent to potential_cropland_percent 051116
   int16 percent_covered_check; //checksum should match cropable_percentage when finished aggregating
 public:
   Generic_data_record *weighted_average_data_record;   // owned by this
 public:
   Polygon_aggregation(const char *polygon_ID_attribute,sint32 _polygon_ID,int16 _cropable_percentage,Generic_data_record *_weighted_average_data_record)
      :polygon_ID(_polygon_ID)
      ,cropable_percentage(_cropable_percentage)                                 //051116
      ,weighted_average_data_record(_weighted_average_data_record)
      ,percent_covered_check(0)
      {  weighted_average_data_record->set_as_int32 (polygon_ID_attribute,polygon_ID);
         weighted_average_data_record->expect_int16("pot_cropland",cropable_percentage);
      }
   virtual ~Polygon_aggregation()       { delete weighted_average_data_record; }
   void aggregate(Generic_data_record &data_rec
      ,int16 component_percentage);    // This is the percent of the map unit that has agricultural soils);
   inline virtual bool is_key_string(const std::string &key)       affirmation_  //180820
      { return (nat32)polygon_ID == key; }
   inline virtual uint32 get_key_nat32()      const { return (nat32)polygon_ID;}
      // At this point polygon_ID will be positive because we don't include offsite values
};
//______________________________________________________________________________
void Polygon_aggregation::aggregate
(Generic_data_record &data_rec
,int16 component_percentage)   // This is the COMPPT value from the STATSGO COMP table
{  float32 component_fraction_of_map_unit =(float32)component_percentage/100.0;
   float32 faction_map_unit_cropable      =(float32)cropable_percentage /100.0;  //051116
   percent_covered_check += component_percentage;
   for (int i = 0; i<data_rec.get_floats_count(); i++)
   {  float32 weighted_value = data_rec.floats[i] * component_fraction_of_map_unit/faction_map_unit_cropable;  //051115
      weighted_average_data_record->floats[i] += weighted_value;
   }
}
//______________________________________________________________________________
Polygon_aggregation *Tally_aggregator::provide_polygon_aggregation
(sint32 _polygon_ID,int16 _cropable_percentage
,Generic_data_record *_weighted_average_data_record)
{
   //At this point we have guarenteed that polygon_ID is positive.
   Polygon_aggregation *polygon_aggregation = (Polygon_aggregation *)polygon_aggregations.find((uint32)_polygon_ID);
   if (polygon_aggregation) // we already have an aggregation started for this polygon
      delete _weighted_average_data_record; //Don't need the empty weighted average values.
   else
   {  polygon_aggregation = new Polygon_aggregation(polygon_ID_attribute.c_str(),_polygon_ID, _cropable_percentage,_weighted_average_data_record); //051116
      polygon_aggregations.append(polygon_aggregation);
   }
   return polygon_aggregation;
}
//______________________________________________________________________________
uint32 Tally_aggregator::aggregate()
{
   uint32 polygons_aggregated = 0;
//   Enumeration_list polygon_aggregations;
   // returns the number of polygons
   // Open tally_table
   Data_source_dBase tally_table(tally_table_dbf.c_str(),std::ios::in);
   Generic_data_record *tally_rec = tally_table.render_generic_data_record();
   for (bool more_records = tally_table.goto_BOF()
       ; more_records
       ; more_records = tally_table.goto_next())
   {  tally_table.get(*tally_rec);
      uint16 scenario_ID = tally_rec->get_as_int16("SCENARIO_ID");
      // goto the GIS_scenarios table record for the matching scenario ID
      bool scenario_exists = GIS_table.find_record((int16)scenario_ID);
      if (scenario_exists)
      {  Polygon_simulation_parameters GIS_parameter_overrides_default_options(true); // Not really used in this context, but clears initialial values in datarec
         CropSyst::Simulation_override_record GIS_scenario(scenario_ID,GIS_parameter_overrides_default_options,0);
         bool scenario_read = GIS_table.get(GIS_scenario);
         bool was_valid
         = scenario_read
           && (GIS_scenario.run_it || GIS_scenario.same_as_record_num)
           && (GIS_scenario.parameter_overrides.polygon_ID > 0); // zero and negative values are offsite.
         if (was_valid)
         {  // create a weather_average_data_record for teh aggregated polygon values,
            // this is going to have the exact same fields as the tally tables data records
            // so just create the generic data record
            Generic_data_record *weighted_average_data_record = tally_table.render_generic_data_record();
            // provide  polygon_aggegation for the record's polygon ID.
            sint32 tally_rec_polygon_ID = tally_rec->get_as_int16(polygon_ID_attribute.c_str());
            /*131008 May want to reimplement this for STATSGO2
            STATSGO::Map_unit_component_data_record map_unit_component;
            bool component_exists = STATSGO_database.get_map_unit_component(GIS_scenario.parameter_overrides.MUID.c_str(), GIS_scenario.parameter_overrides.SEQNUM,map_unit_component);
            int16 cropable_percentage = STATSGO_database.get_potential_cropland_percent_deprecated(GIS_scenario.parameter_overrides.MUID.c_str(), upto_capability_class , with_irrigation) ; //051115
            Polygon_aggregation *polygon_aggregation =provide_polygon_aggregation(tally_rec_polygon_ID,cropable_percentage,weighted_average_data_record);
            if (polygon_aggregation)
            {  // Warning, Instead, we may need the area.
               // Get the COMPPCT value for the sequence from statsgo database
               if (component_exists)
                     polygon_aggregation->aggregate(*tally_rec,map_unit_component.COMPPCT);
               else  cerr << "Unable to find STATSGO soil component for MUID:"<<GIS_scenario.parameter_overrides.MUID << " SEQNUM:"<< GIS_scenario.parameter_overrides.SEQNUM << " in scenario:" << scenario_ID << endl;
            }  else  cerr << "Could not find polygon aggregation for polygon:" << tally_rec_polygon_ID <<endl;
            */
         }// if was_valid
      } else  // scenario doesn't exist
         std::cerr << "Could not find CropSyst GIS table scenario ID:" << scenario_ID << std::endl;
   }
   delete tally_rec; tally_rec = 0;
   //   open aggregate_table file
   Data_source_dBase aggregate_table(aggregate_table_dbf.c_str(),std::ios::out);
   FOR_EACH_IN(polygon_aggregation,Polygon_aggregation,polygon_aggregations,each_poly_aggr)
   {  if (aggregate_table.set(*(polygon_aggregation->weighted_average_data_record)))
         polygons_aggregated ++;
   } FOR_EACH_END(each_poly_aggr)
   return polygons_aggregated;
}
//______________________________________________________________________________
