#ifndef STATSGO_SSURGO_databaseH
#define STATSGO_SSURGO_databaseH
#include <stdlib.h>
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/format/MicroSoft/Access/import_export_table.h"
#include "corn/container/indexer.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#include "corn/container/search_tree.h"
#include "corn/container/enumlist.h"
#include "USDA/NRCS/soil/survey/database/STATSGO_SSURGO_types.h"
#include "corn/seclusion.h"

namespace CORN {
class Binary_file_interface;
}
//______________________________________________________________________________
namespace USDA_NRCS { namespace STATSGO2_SSURGO {
//______________________________________________________________________________
class Table_indexer
: public CORN::Indexer
, public CORN::Enumeration_list
{
   public: struct Indice : public CORN::Enumeration
   {  // Most STATSGO2 table keys consist two numbers separated by a colon
      nat32 unique_key;
      nat32 MUkey_nat32;
      std::string MUkey_str;                                                     //170903
      contribute_ nat32 file_pos;
   public:
      inline Indice(const std::string &key_) : CORN::Enumeration()
      , file_pos(0)
      {  size_t colonpos = key_.find(":");
         if (colonpos != std::string::npos)
         {
            //170903 std::string MUkey_str(_key,0,colonpos);
            MUkey_str = key_.substr(0,colonpos);                                 //170903
            std::string unique_key_str(key_,colonpos+1);
            MUkey_nat32 = atoi(MUkey_str.c_str());                               //170903
            unique_key = atoi(unique_key_str.c_str());
         }else
         {
            unique_key = MUkey_nat32 = atoi(key_.c_str());
            MUkey_str=key_;                                                       //170903
         }
      }
      inline virtual bool is_key_nat32(nat32 key)                   affirmation_  //180820
         { return unique_key == key; }
      inline virtual nat32 get_key_nat32()           const { return unique_key;}

      virtual nat32 write_binary(CORN::Binary_file_interface &bin_file) stream_IO_; //111015
      virtual nat32 read_binary(CORN::Binary_file_interface &bin_file)  stream_IO_; //111015
   };
   //___________________________________________________________________________
 protected:
   std::string key_field_name;
   contribute_ Indice *curr_key_item;                                            //150731
   CORN::Data_table &indexed_table;
   bool persistent;
   //NYN CORN::Enumeration_list *in_memory;
   contribute_ CORN::Data_record       *record_for_indexing_owned;               //121228
   const CORN::Seclusion &mapunit_seclusion;                                     //170903
   /*170903 replaced by mapunit_seclusion
   const CORN::Dynamic_array<nat32> &mapunit_filter;                             //121229
   */
 public:
   Table_indexer
      (CORN::Data_table &_indexed_table
      ,const char *key_field_name
      ,const CORN::Seclusion &mapunit_seclusion                                  //170903
      //170903 ,const CORN::Dynamic_array<nat32> &mapunit_filter
      ,CORN::Data_record  *_record_for_indexing_owned
      ,const CORN::OS::Directory_name *_persistent_index_files_directory
      ,bool keep_index_in_memory
      ); // may be 0 if not persistent
   nat32 refilter_mapunits();
      /**<
      // Often times, we are only interested in a subset of the
      // available map units.
      // This will remove the specified map units from the index.
      // Indexing will then be much faster, and more space efficient.
      // This optional function is usually called once, but it can be used
      // mulitple time, I to remove map units that have already been processed.
      // \return the number of indices eliminated.
      **/
 protected:
   bool setup_index(const CORN::OS::Directory_name *_persistent_index_files_directory);
   virtual const char *get_key_name(nat8 key_number)                      const;
   virtual nat8       get_key_count()                                     const;
   virtual bool  know_position(nat32 position)                       cognition_;
   virtual bool  know_value
      (const std::string &value //150731 const char *value
      ,  const char *field, const char *section)                     cognition_;
   virtual bool  commit();
   virtual nat8 get_key_sequence(const char *field, const char *section)  const;
   Indice *provide_indice(const char *key)                           provision_;
};
//_2011-10-24___________________________________________________________________
class Database
{protected:
 public:
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Arguments
   {public:
      nat8 aggregation_option;
      /*
         0=Extract map unit soil components
         1=Aggregate soil sequences in each map unit to create an aggregated representitive pseudopedon
         2=Use primary component as a representitive pedon
      */
      //CORN::OS::Directory_name *program_directory;                               //180105
      CORN::Arguments &CORN;

      CORN::OS::Directory_name_concrete *database_directory_nameX;
         // I.e. C:\\Simulation\\Database\\STATSGO2\\gsmsoil_us\\tabular
      CORN::OS::Directory_name_concrete table_index_directory_name;
    public:
      inline Arguments
         (CORN::Arguments &CORN_)
         : CORN(CORN_)
         //180105 abandoned(CORN::OS::Directory_name *program_directory_)                          //180105
         , aggregation_option(2) // use predominate component
         //180105 abandoned , program_directory(program_directory_)
         , database_directory_nameX(0) //("C:\\Simulation\\Database\\STATSGO2\\gsmsoil_us\\tabular")
         , table_index_directory_name()
         {}
      virtual bool recognize_assignment
         (const std::string &variable
         ,const std::string &value)                               modification_;
      virtual bool get_end()                                      modification_;

   };
   //_2017-08-31__ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _Arguments_/
   /*moved to arguments
   CORN::OS::Directory_name_concrete database_directory_name;
   */
   CORN::OS::Directory_name_concrete table_index_directory_name;
   provided_ CORN::MicroSoft::Access::Import_export_table *chorizon_table;     contribute_ Table_indexer *chorizon_indexer;
   provided_ CORN::MicroSoft::Access::Import_export_table *component_table;    contribute_ Table_indexer *component_indexer;
   provided_ CORN::MicroSoft::Access::Import_export_table *mapunit_table;      contribute_ Table_indexer *mapunit_indexer;
   provided_ CORN::MicroSoft::Access::Import_export_table *chtexturegrp_table; contribute_ Table_indexer *chtexturegrp_indexer;//110324
 public:
   const Arguments &arguments;                                                   //170831
   const CORN::Seclusion &mapunit_seclusion;                                     //170903
      // Filters which mapunits to include/exclude
      // Provided by application
      // (optional when empty includes everything)
   /*170903 replaced with mapunit_seclusion
   CORN::Dynamic_array<nat32> mapunit_filter;
   */
 public: // 'structors
   Database
      (const Arguments &arguments_                                               //170831
      ,const CORN::Seclusion &mapunit_seclusion_                                 //170903
      /*170831 moved to arguments
       const char *_database_directory_name
      ,const char *_table_index_directory_name // = 0
      */
      ); // I.e. C:\Simulation\Database\STATSGO2\gsmsoil_us
      // If the table index directory is not specified, then
      // the table index files will be stored in _database_directory_name
      // Often only a small subset of the STATSGO2 map units are needed
      // for a project so only those need to be indexed.
      // When using subsets, it is recommended to store that index files in
      // a special directory.
      // Only store that complete index in the STATSGO database directory.
   virtual ~Database();
 public:
   CORN::Data_table &provide_chorizon_table   ()                     provision_;
   CORN::Data_table &provide_component_table  ()                     provision_;
   CORN::Data_table &provide_mapunit_table    ()                     provision_;
   CORN::Data_table &provide_chtexturegrp_table()                    provision_;                               //110324
   const Table_indexer &provide_chorizon_index     (bool persistent) provision_;
   const Table_indexer &provide_component_index    (bool persistent) provision_;
   const Table_indexer &provide_mapunit_index      (bool persistent) provision_;
   const Table_indexer &provide_chtexturegrp_index (bool persistent) provision_;
   /*170903 now using mapunit_seclusion caller now updates the seclusion and
       calls refilter_mapunits
   nat32 filter_map_units(const CORN::Dynamic_array<nat32> &map_unit_filter);
   */
   nat32 refilter_mapunits();                                                    //170903
      /**<
      // Often times, we are only interested in a subset of the
      // available map units.
      // This will remove the specified map units from all the current indexes.
      // Indexing will then be much faster, and more space efficient.
      // This optional function is usually called once, but it can be used
      // mulitple time, I to remove map units that have already been processed.
      // \return the total number of indices eliminated.
      **/
};
//_2011-10-24___________________________________________________________________
} } //namespace USDA_NRCS STATSGO2_SSURGO

#endif
