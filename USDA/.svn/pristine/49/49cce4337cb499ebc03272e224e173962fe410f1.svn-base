#include "STATSGO_SSURGO_database.h"
#include "corn/parameters/parameter.h"
#include "corn/container/enumlist.h"
#include "corn/OS/directory_entry_name.h"
#include "corn/OS/file_system_engine.h"
#include "soil/survey/database/tabular/chorizon.h"
#include "soil/survey/database/tabular/component.h"
#include "soil/survey/database/tabular/mapunit.h"
#include "soil/survey/database/tabular/chtexturegrp.h"
#include "corn/format/binary/binary_file_fstream.h"
#include "corn/application/URL_link.h"
#include "corn/data_source/VV_file.h"
#include <assert.h>

/*
Need to implement 170907

When setting up index

STATSGO database argument
option to create/use
master index that includes all records
(use this when working throughout the country)

or index only seclusions
(use this when working with various parts of the country).
*/

using namespace CORN;
namespace USDA_NRCS { namespace STATSGO2_SSURGO {
//______________________________________________________________________________
CORN::Parameter_number *chorizon_fields;
CORN::Parameter_number *component_fields;
CORN::Parameter_number *mapunit_fields;
//______________________________________________________________________________
Database::Database
(const Arguments &arguments_                                                     //170831
,const CORN::Seclusion &mapunit_seclusion_                                       //170903
      /*170831 moved to arguments
 const char *_database_directory_name
,const char *_table_index_directory
*/
) // I.e. C:\Simulation\Database\STATSGO2\gsmsoil_us
:arguments(arguments_)
,mapunit_seclusion(mapunit_seclusion_)                                           //170903
/*170831
: database_directory_name(_database_directory_name)
, table_index_directory_name(_table_index_directory ? _table_index_directory : _database_directory_name)
*/
, table_index_directory_name(arguments_.table_index_directory_name.has_name() ? arguments_.table_index_directory_name : (*arguments_.database_directory_nameX)) //170904
//170903 , table_index_directory_name(_table_index_directory ? _table_index_directory : _database_directory_name)
, chorizon_table     (0)   ,chorizon_indexer(0)
, component_table    (0)   ,component_indexer(0)
, mapunit_table      (0)   ,mapunit_indexer(0)
, chtexturegrp_table (0)   ,chtexturegrp_indexer(0)                              //110324
{}
//______________________________________________________________________________
Database::~Database()
{  if (chorizon_table)     delete chorizon_table;     if (chorizon_indexer)      delete chorizon_indexer;
   if (component_table)    delete component_table;
   if (component_indexer)  delete component_indexer;
   if (mapunit_table)      delete mapunit_table;      if (mapunit_indexer)       delete mapunit_indexer;
   if (chtexturegrp_table) delete chtexturegrp_table; if (chtexturegrp_indexer)  delete chtexturegrp_indexer;
}
//______________________________________________________________________________
#define provide_XXXX_table(provide_NAME_table,NAME_table,table_filename)       \
CORN::Data_table &Database::provide_NAME_table()              provision_       \
{  if (!NAME_table)                                                            \
   {  CORN::OS::File_name_concrete qualified_filename_txt((*arguments.database_directory_nameX),table_filename);\
      NAME_table = new CORN::MicroSoft::Access::Import_export_table(qualified_filename_txt,false,0,0 );\
   };                                                                          \
   return *NAME_table;                                                         \
};
provide_XXXX_table(provide_chorizon_table    ,chorizon_table      ,L"chorizon.txt");
provide_XXXX_table(provide_component_table   ,component_table     ,L"comp.txt"    );
provide_XXXX_table(provide_mapunit_table     ,mapunit_table       ,L"mapunit.txt" );
provide_XXXX_table(provide_chtexturegrp_table,chtexturegrp_table  ,L"chtexgrp.txt");
//______________________________________________________________________________
#define provide_XXXX_indexer(provide_NAME_indexer,NAME_indexer,key_field_name,NAME_table,provide_NAME_table,record_type_for_indexing_given)  \
const Table_indexer &Database::provide_NAME_indexer(bool persistent) provision_ \
{  if (!NAME_indexer)                                                           \
   {  if (!NAME_table) provide_NAME_table();                                    \
      {  NAME_indexer = new Table_indexer(*NAME_table,key_field_name,mapunit_seclusion,new USDA_NRCS::record_type_for_indexing_given(),persistent?&arguments.table_index_directory_name:0,false);              \
      }                                                                         \
   }                                                                            \
   return *NAME_indexer;                                                        \
}
provide_XXXX_indexer(provide_chorizon_index     ,chorizon_indexer    ,"chkey"  ,chorizon_table      ,provide_chorizon_table    ,CHorizon)
provide_XXXX_indexer(provide_component_index    ,component_indexer   ,"cokey"  ,component_table     ,provide_component_table   ,Component)
provide_XXXX_indexer(provide_mapunit_index      ,mapunit_indexer     ,"mukey"  ,mapunit_table       ,provide_mapunit_table     ,Mapunit)
provide_XXXX_indexer(provide_chtexturegrp_index ,chtexturegrp_indexer,"chkey" /*"chtgkey"*/,chtexturegrp_table  ,provide_chtexturegrp_table,CHtexturegrp)
                                                                     // for chtexturegrp we index on chkey
//_2011-11-07___________________________________________________________________
Table_indexer::Table_indexer
(CORN::Data_table   &indexed_table_
,const char         *key_field_name_
,const CORN::Seclusion &mapunit_seclusion_                                       //170903
//170903 ,const CORN::Dynamic_array<nat32> &_mapunit_filter                               //121229
,CORN::Data_record  *record_for_indexing_owned_
,const CORN::OS::Directory_name *persistent_index_files_directory_
,bool /*keep_index_in_memory*/)
: CORN::Indexer()
, key_field_name(key_field_name_)
, curr_key_item(0)
, indexed_table(indexed_table_)
, persistent(persistent_index_files_directory_!=NULL)
, record_for_indexing_owned(record_for_indexing_owned_)
, mapunit_seclusion(mapunit_seclusion_)                                          //170903
//170903 , mapunit_filter(_mapunit_filter)
{  setup_index(persistent_index_files_directory_);
}
//_2011-10-24___________________________________________________________________
bool Table_indexer::setup_index
(const CORN::OS::Directory_name *persistent_index_files_directory)
{
   std::string buffer;                                                           //140629
   std::string index_name(record_for_indexing_owned->get_primary_section_name());
   index_name.append("_"); index_name.append(key_field_name);
   CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/(*persistent_index_files_directory); //140929
   CORN::OS::File_name_concrete index_file_name(*persistent_index_files_directory,index_name.c_str(),"index");
   nat32 row = 0;
   nat32 exclude_count = 0; // just informational                                //141211
   nat32 include_count = 0;                                                      //141211
   std::clog << "Index:" << std::endl << index_file_name.c_str() << std::endl;
   if (persistent && CORN::OS::file_system_engine.exists(index_file_name))
   {
      std::clog << "Loading" << std::endl;
      std::clog << "row\tMUKEY\tincl\texcl" << std::endl;
      nat32 last_mukey = 0;
      Binary_file_fstream index_file(index_file_name.c_str(),false,std::ios_base::in);

      index_file.seek(0,std::ios_base::end);
      nat32 index_size = index_file.tell();
      index_file.seek(0,std::ios_base::beg);

      while (!index_file.at_eof())
      {  Indice *indice = new Indice("");
         nat32 found_in_filter_index_unused = 0;
         indice->read_binary(index_file);

         //141218 std::clog << "row:" << row << '\t' << indice->MUkey; // std::endl;
         row++;
         last_mukey = indice->MUkey_nat32;

         if (!mapunit_seclusion.count() || mapunit_seclusion.is_included_string(indice->MUkey_str)) //170903
         //170903 if (mapunit_filter.is_empty() || mapunit_filter.is_in_array(indice->MUkey,found_in_filter_index_unused))
         {  include_count++;                                                     //141211
            append(indice);
         } else
         {  exclude_count++;
         }
         const char *sort_state = "";
         if (indice->MUkey_nat32 < last_mukey)
               sort_state       = "unsorted" ;
         if (row%5000 == 0)
         {
            nat32 curr_pos = index_file.tell();
            std::clog << row << '\t' << indice->MUkey_str;
            float32 percent_done = (float32)curr_pos/(float32)index_size*100.0;
            std::clog << '\t' << (int)include_count << '\t' << (int)exclude_count<< '\t' << percent_done << "%";
            std::clog << '\t' << sort_state;
            std::clog << '\r';                                                   //141211
         }

         /*141218
         std::clog
            << " included: " << (int)include_count                         //141211
            << " ignored:" << (int)exclude_count                        //141211
            << '\r';
         */
      }
   } else
   {  std::clog << "Indexing" << std::endl;
      std::clog << "row\tMUKEY\tincl\texcl" << std::endl;

      Binary_file_fstream *index_file = persistent
         ? new Binary_file_fstream (index_file_name.c_str(),false,std::ios_base::out)
         : 0;
      if (record_for_indexing_owned)
      {  for (bool ok = indexed_table.goto_first();ok;)
         {  nat32 file_pos = dynamic_cast<Tabular_text_file &>(indexed_table).get_file_position();
            ok = indexed_table.get(*record_for_indexing_owned);                  //111106
            FOR_EACH_IN(section,VV_Section,record_for_indexing_owned->sections,each_section)
            { // This format doesn't really have sections, but the expected data record layout may
                  FOR_EACH_IN(entry,VV_abstract_entry,section->entries,each_entry)
                  {  // I could check the field name but they should be in sequence
                     buffer.clear();                                             //140926
                     know_value(entry->append_to_string(buffer).c_str()
                     ,entry->get_variable(),section->section_label()  //180820
                     //180820,entry->get_key(),section->get_key() 
                     );
                  } FOR_EACH_END(each_entry)
            } FOR_EACH_END(each_section)
            know_position(file_pos);
            std::clog <<  row << '\t' << curr_key_item->MUkey_str;
            // Write all indices to the index files.
            // Only keep in memory the items were are currently
            // interested in.
            /*170903 filter is obsolete now using seclusion
            if (!mapunit_filter.is_empty()  &&curr_key_item) // if there are no mapunits in the filter, then we don't apply a filter
            */
            if (!mapunit_seclusion.is_empty()  &&curr_key_item) // if there are  mapunits in the filter, then apply a filter
            {
               /*170903 filter is obsolete now using seclusion
               nat32 found_in_filter_index_unused = 0;
               if (!mapunit_filter.is_in_array(curr_key_item->MUkey,found_in_filter_index_unused))
               */
               if (!mapunit_seclusion.is_included_string(curr_key_item->MUkey_str)) //170903
               {  remove(curr_key_item);
                  curr_key_item = 0;
               }
            }
            if (index_file && curr_key_item)
            {
               curr_key_item->write_binary(*index_file);
               include_count++;                                                  //141211
            } else
            {  exclude_count++;                                                  //141211
            }
            std::clog  << '\t' << (int)include_count << '\t' << (int)exclude_count << '\r'; //141211
            row++;
         }
      }
      std::clog << std::endl << "Indexed." << std::endl;
      delete index_file;
   }
   std::clog << std::endl << "Sorting...." << std::endl;
   sort();
   std::clog << std::endl << "Sorted." << std::endl;
   indexed_table.reset();     // We read to the end of file which will make rdstate not 'good'
   std::clog << std::endl << "Goto first record" << std::endl;
   indexed_table.goto_first();// We want to be in a good state ready to read.
   std::clog << std::endl << "Ready" << std::endl;
   return true;
}
//_2011-11-07___________________________________________________________________
const char *Table_indexer::get_key_name(nat8 /*key_number*/) const
{  return key_field_name.c_str();   // there is only one key field
}
//_2011-10-24___________________________________________________________________
nat8 Table_indexer::get_key_count() const
{  return 1; // there is only a primary key
}
//_2011-10-24___________________________________________________________________
bool  Table_indexer::know_position(nat32 position)                    cognition_
{  assert(curr_key_item); // The caller must previously call know_value
   curr_key_item->file_pos = position;
   return true;
}
//_2011-10-24___________________________________________________________________
bool  Table_indexer::know_value
(const std::string &value                                                        //150730
//150731 const char *value
,  const char *field , const char *section )                          cognition_ //150731
{  bool is_key_field = true;
   if (key_field_name == field)
   {  curr_key_item = provide_indice(value.c_str());                             //150730
      // We assume the caller will next (after calling know_value for all the fields)
      // call know_position where by curr_mukey_item will have been set by this.
   } else is_key_field = false;
   return is_key_field;
}
//_2011-10-24___________________________________________________________________
bool  Table_indexer::commit()
{  //NYN?
   return false;
}
//_2011-10-24___________________________________________________________________
nat8 Table_indexer::get_key_sequence(const char *field, const char */*section*/) const
{  return (key_field_name == field) ? 1 : 0;
}
//_2011-10-24___________________________________________________________________
Table_indexer::Indice *Table_indexer::provide_indice(const char *key) provision_
{
   Table_indexer::Indice *pot_item = new Table_indexer::Indice(key);
   Table_indexer::Indice *existing_key_item = dynamic_cast<Table_indexer::Indice *>(find(pot_item->unique_key));
   if (!existing_key_item)
   {  Table_indexer &modifiable_self = const_cast<Table_indexer &>(*this);       //150903
      modifiable_self.append(pot_item);                                          //150903
      existing_key_item = pot_item;
   } else delete pot_item;
   return existing_key_item;
}
//_2011-10-24___________________________________________________________________
nat32 Table_indexer::Indice::write_binary(CORN::Binary_file_interface &bin_file) stream_IO_
{  bin_file.write_nat32(unique_key);
   bin_file.write_nat32(MUkey_nat32);
   bin_file.write_nat32(file_pos);
   return sizeof(nat32) * 3;                                                     //121126
}
//_2011-11-07___________________________________________________________________
nat32 Table_indexer::Indice::read_binary(CORN::Binary_file_interface &bin_file) stream_IO_
{  unique_key  = bin_file.read_nat32();
   MUkey_nat32 = bin_file.read_nat32();                                          //170903
   MUkey_str.clear();                                                            //170903
   CORN::append_nat32_to_string(MUkey_nat32,MUkey_str);                          //170903
   file_pos    = bin_file.read_nat32();
   return sizeof(nat32) * 3;                                                     //121126
}
//_2011-11-07___________________________________________________________________
/*170903 replaced with mapunit_seclusion and refilter_mapunits()
nat32 Database::filter_map_units(const CORN::Dynamic_array<nat32> &_mapunit_filter)
{  // Note that thiss allows
   mapunit_filter.append_array(_mapunit_filter);  //apply additional filter which may have been previously specified
   return !mapunit_filter.is_empty()
      ? refilter_mapunits()
      //170903  replaced with refilter_mapunits
      //?   chorizon_indexer    ? chorizon_indexer      ->refilter_mapunits() : 0
      //  + component_indexer   ? component_indexer     ->refilter_mapunits() : 0
      //  + mapunit_indexer     ? mapunit_indexer       ->refilter_mapunits() : 0
      //  + chtexturegrp_indexer? chtexturegrp_indexer  ->refilter_mapunits() : 0
      : 0;
}
//_2011-11-07___________________________________________________________________
*/
nat32 Database::refilter_mapunits()
{  // Note that thiss allows
   return !mapunit_seclusion.is_empty()
      ?   chorizon_indexer    ? chorizon_indexer      ->refilter_mapunits() : 0
        + component_indexer   ? component_indexer     ->refilter_mapunits() : 0
        + mapunit_indexer     ? mapunit_indexer       ->refilter_mapunits() : 0
        + chtexturegrp_indexer? chtexturegrp_indexer  ->refilter_mapunits() : 0
      : 0;
}
//_2017-09-03___________________________________________________________________
nat32 Table_indexer::refilter_mapunits()
{  nat32 deletions = 0;
   if (mapunit_seclusion.is_empty() ) return 0;
   FOR_EACH(indice,Table_indexer::Indice,each_indice)
   {
      if (!mapunit_seclusion.is_included_string(indice->MUkey_str))
         deletions +=each_indice->delete_current();
   } FOR_EACH_END(each_indice)
   // else if no mapunits specified, then don't apply this filter
   return deletions;
}
//_2011-11-07___________________________________________________________________
bool Database::Arguments::recognize_assignment
(const std::string &variable
,const std::string &value)                                         modification_
{  bool recognized = false;
   if ((variable == "--STATSGO2-tabular"))
   {
      database_directory_nameX = new CORN::OS::Directory_name_concrete(value);
      //180105 database_directory_nameX.set_string(value);
         // I.e. C:\\Simulation\\Database\\STATSGO2\\gsmsoil_us\\tabular
      recognized = true;
   } else if ((variable == "--STATSGO2-index"))
   {
      table_index_directory_name.set_string(value);
      recognized = true;
   }
   return recognized; //  || xx::recognize_assignment(variable,value);
}
//_2017-12-17________________________Database::Arguments::recognize_assignment_/
bool Database::Arguments::get_end()                                modification_
{
   if (!database_directory_nameX)
   {
      URL_Link tabular_link;
      CORN::OS::File_name_concrete URL_filename
         ((*CORN.get_program_directory()),"STATSGO2-tabular.url");
      CORN::VV_File URL_file(URL_filename.c_str());
      URL_file.get(tabular_link);
      if (tabular_link.WorkingDirectory.empty())
         database_directory_nameX = new CORN::OS::Directory_name_concrete
            ("C:\\Simulation\\Database\\STATSGO2\\gsmsoil_us\\tabular");
      else
         database_directory_nameX = new CORN::OS::Directory_name_concrete
         (tabular_link.WorkingDirectory);
   }
   return true;
}
//_2018-01-05__________________________________________________________________/

}} // namespace

