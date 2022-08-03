#ifndef scenarios_generator_engineH
#define scenarios_generator_engineH
#include "corn/seclusion.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/container/unilist.h"
#include "corn/data_source/generic_datarec.h"
#include "CS_suite/file_system/CS_databases.h"
#include "common/geodesy/geocoordinates.h"
namespace CS {
//______________________________________________________________________________
class Scenarios_generator_engine
{
 private:
   provided_ CORN::Unidirectional_list existing_subscenarios_leaves;
   Databases *databases;
      // List of Database directorys accessable to the CWD
      // (a scenario or predefined subscenario
   provided_ CORN::Unidirectional_list database_subdirectories;
   provided_ CORN::Unidirectional_list database_parameter_files;
   provided_ CORN::Unidirectional_list predefined_scenario_used_parameter_files;
 public:
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   // #define ARGUMENTS_SUPERCLASS  CORN::Arguments
   #define ARGUMENTS_SUPERCLASS  Geocoordinates::Arguments
   class Arguments
   : public extends_ ARGUMENTS_SUPERCLASS
   {
    public:
      CORN::OS::Directory_name_concrete generate_directory;
      provided_ CORN::Seclusion seclusion;
      provided_ CORN::Seclusion scenario_level_recognition;
      std::wstring template_scenario;                                            //170512
         // may have any qualification,
         // but will usually be relative to CWD
      std::wstring target_name_template_composed_checkused;  // unqualified
      std::wstring target_name_specified;          // unqualified
      CORN::Generic_data_record expected_decodings; nat16 expected_decodings_count;
         // expected decodings are optional so the count may be 0.
      std::string ultimates_filename;
         // file listing the generated ultimate scenarios (directories)
         // the directory names are qualified reletive the the current working directory
      bool REACCH_mode;                                                          //170512
    public:
      Arguments();
      virtual ~Arguments();
      virtual bool write_help()                                           const;
      virtual bool get_end()                                      modification_;
      virtual bool get_author_mailto_URI(std::string &email_address)      const;
      virtual bool recognize_option(const std::string &paramstring)modification_;
      virtual bool recognize_assignment
         (const std::string &variable
         ,const std::string &value)                               modification_;
      bool is_scenarios_directory
         (const CORN::OS::Directory_name &directory)               affirmation_;
         // return false if the generated directory cannot be renamed
         // (I.e. target directory already exists,
         // because shouldnot overwrite the target)
      bool load_expected_decodings(const CORN::OS::File_name &decode_file) modification_;
   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Predefined_scenario
      // (although derivied from geocoordinate, the scenario by be simply a
      //  combination of subscenario elements, not necessarily geocoordinate/site/scenario)
   : public extends_ Geocoordinate_item
   {public:
      //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
      class Potential_scenario_element
      : public implements_ CORN::Item
      {public:
         std::string field_name;
         std::string scenario_value;
       public:
         Potential_scenario_element(const CORN::VV_entry_item &item);
         inline Potential_scenario_element
            (const std::string &field_name_
            ,const std::string &scenario_value_)
            : CORN::Item()
            , field_name(field_name_)
            , scenario_value(scenario_value_)
            {}
         inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
            { return field_name == key; }

/*180820  was probably only used for find_cstr now using is_key            
         inline virtual const char *get_key()                              const
            { return field_name.c_str(); }
*/            
      };
      //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
      class Fields_dBase
      : public extends_ Geocoordinates::Fields_dBase
      {public:
         CORN::Data_source_dBase::Field_item *soil_MUKEY_field; // not owned
         CORN::Data_source_dBase::Field_item *ID_field;
         CORN::Data_source_dBase::Field_item *soil_area_field;                   //170518
            // soil_area_field currently only used by REACCH (optional)

         // may need a list of arbitrary fields
         // names which would correspond to Database contexts
       public:
         inline Fields_dBase()
            : Geocoordinates::Fields_dBase()
            , soil_MUKEY_field   (0)
            , ID_field           (0)
            , soil_area_field    (0)                                             //170518
            {}
         inline virtual ~Fields_dBase() {}
      };
      //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
      std::string soil_MUKEY;
      std::string ID;
      float32     soil_area;                                                     //170518
         // soil_area_field currently only used by REACCH (optional)
      CORN::Unidirectional_list other_potential_elements;
         // list of Potential_scenario_element
         // where the scenario_value corresponds to elements from the parameter file Database
      CORN::Unidirectional_list decodings;
         // list of Potential_scenario_element which represents a decoding
         // where the scenario_value is a preestablished scenario subpath.
         // Decoding has field name and decoded value (which currently would corresponse to preestablished scenario)
   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Predefined_scenarios  // rename to Predefined_scenarios
   : public extends_ CS::Geocoordinates
   {public:
      provided_ Predefined_scenario::Fields_dBase *fields_dBase;
      const Scenarios_generator_engine::Arguments &generator_arguments;          //170131
    public:
      inline Predefined_scenarios
         (const Scenarios_generator_engine::Arguments &arguments_)               //170131
          : CS::Geocoordinates (&arguments_)
         , fields_dBase       (0)
         , generator_arguments(arguments_)                                       //170131
         {}
    protected: // Geocoordinate implementation overrides
      virtual bool provide_fields_dBase
         (CORN::Data_source_dBase &DBF_file)                         provision_;
      virtual bool set_from_record
         (CORN::Generic_data_record &geocoord_rec
         ,Geocoordinate &geocoord);
      inline virtual Geocoordinate_item *render_geocoordinate()       rendition_
         { return new Predefined_scenario; };
       inline virtual bool is_geocoordinates_required() affirmation_ { return false;}
     virtual bool setup_DBF_fields(CORN::Data_source_dBase &DBF_file)provision_;
     //171008virtual bool DBF_has_a_geocoordinate_fields()                 affirmation_; //170510
     virtual bool table_has_a_geocoordinate_fields()               affirmation_; //171008_170510
   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Scenario_level;
   class Scenario_levels
   : public CORN::Unidirectional_list
   {
    public:
      Scenarios_generator_engine::Scenario_level *provide_new_scenario_level
         (const std::wstring               &level_name                           //180118
         //170206 ,CORN::Text_list                 &path_list
         ,const CORN::OS::Directory_name &dir_name
         ,const CORN::Seclusion &seclusions
         ,const CORN::Seclusion &recognitions);
      bool is_already_leveled(const std::wstring &level_name)      affirmation_; //180118
   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   class Scenario_level
   : public CORN::Item
   {
    public:
      std::wstring name;                                                         //180118
         // For primary level this will be the Database\subdir name
         // I.e. Soil Rotation Crop Management



      Scenario_levels           sublevels; // list of Scenario_level
      CORN::Unidirectional_list directories; // list of DENs (file or dirs)
         // If there are both files and subdirs in a scenario directory and if
         // there are sublevels, the subscenarios would be the subdir names
      CORN::Unidirectional_list scenario_files;
         // The files are considered inherited in the generated target.
         // Files (are likely parameter file names)
         // that may potentially be inherently subscenarios
         // It is assumed the cases where there are not subdirectories,
         // the files respresent scenarios.
         // (I.e. UED files would be considered as site scenarios).
    public:
      inline Scenario_level(const std::wstring &new_name)                        //180118
         : CORN::Item()
         , name(new_name)
         { sublevels.set_unique_keys(true); }
      virtual bool initialize                                                    //170205
         (const CORN::OS::Directory_name &dir_name
         ,const CORN::Seclusion &seclusions
         ,const CORN::Seclusion &scenario_level_recognition)    initialization_;
      nat32 added_subitems
         (const CORN::OS::Directory_name &dir_name
         ,const CORN::Seclusion &seclusions
         ,const CORN::Seclusion &scenario_level_recognition) ;
      inline virtual const char    *key_string (std::string &buffer)       const //180119
         { CORN::wstring_to_string(name,buffer); return buffer.c_str();}
      inline virtual const wchar_t *key_wstring(std::wstring &buffer)      const //180119
         { buffer = name; return buffer.c_str();}

      /*180119
      inline virtual const char *get_key()                                 const
         { return name.c_str(); }
      */
   };
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 protected:
   provided_ Scenario_levels DB_scenario_levels_primary;
      // list of Scenario level
      // scenario levels defined by database subdirectories (not excluded)
      // (does not include predefined scenarios)
 public:
   Arguments &arguments;
   Predefined_scenarios predefined_combinations;
      // Not necessarity 'site' (with geolocation) but could be simply
      // any scenario combination
   /*171215 Disabled, not really needed (Linux scheduling now uses ls_scenario techinque
      and Windows Explorer will search for scenarios directories
   std::ofstream *ultimates_file;                                                //170223
   */

   #ifdef _Windows
   CORN::Text_list all_scenario_dirs;
   #endif

 public:
   Scenarios_generator_engine(Arguments &arguments_);
   virtual ~Scenarios_generator_engine();                                        //170223
   bool initialize()                                            initialization_;
   bool generate();
 protected:
   Scenario_level *provide_new_scenario_level
      (const CORN::OS::Directory_name &dir_name)                     provision_;
 protected:
   nat32 provide_database_subdirectories()                           provision_;
   nat32 provide_scenario_levels()                                   provision_;
   nat32 provide_database_parameter_files()                          provision_;
   nat32 provide_preestablished_subscenario_directories()            provision_;
   bool generate_scenario_level
      (const Scenario_levels &scenario_levels
      ,nat16 scenario_level_index                                                //170204
      ,const CORN::OS::Directory_name &specific_scenario_path);
   bool generate_predefined_combination_scenario_level
      (const Scenario_levels &scenario_levels
      ,const CORN::OS::Directory_name &specific_scenario_path );
   bool create_best_kind_of_link
      (const CORN::OS::File_name &source_filename
      ,const CORN::OS::File_name &target_filename);
   bool is_VV_file(const CORN::OS::File_name &target_filename)     affirmation_;
   const CORN::OS::File_name &find_most_appropriate_filename
      (const CORN::Text_list &appropriates
      ,const CORN::Container &canidate_filenames)                         const;
   bool decodings_match
      (const CORN::Unidirectional_list &decodings
      ,const CORN::OS::Directory_name  &scenario_to_be_generated)  affirmation_;
   bool is_already_leveled(const std::wstring &level_name)         affirmation_; //180118
 protected: // REACCH specialization
   class REACCH_Predominant_soil
   : public extends_interface_ CORN::Item
   {public:
      std::string ID;         //cell
      std::string MUKEY;
      float32     soil_area;                                                     //170518
    public:
      virtual const char *key_string(std::string &buffer)           const;
      //virtual const char *get_key()                                 const;
   };
   //_2017-05-18________________________________________REACCH_Predominate_soil_
      nat32 generate_REACCH_scenarios();
   nat32 generate_REACCH_cell_scenarios
      (const CORN::OS::Directory_name_concrete  &penulimate_scenario_directory
      ,const CORN::OS::Directory_name_concrete &Database_Weather_scenario_directory //170612
         // These DENS dont need to be concrete
      )   ;
 private:
   nat32 REACCH_get_available_weather_locations     //170612
      (Geocoordinates &available_weather_locations // returned
      ,const CORN::OS::Directory_name &Database_Weather_scenario_dir);
   bool REACCH_inherit_link_weather_if_needed
      (const Geocoordinate &predefined_scenario_geocoord
      ,const CORN::OS::Directory_name_concrete &cell_scenario_directory
      ,const CS::Geocoordinates &available_weather_locations
      ,const CORN::OS::Directory_name_concrete &Database_Weather_scenario_directory);
      // Directory names dont need to be concrete
 private:
   void write_run_scenarios
      (const CORN::OS::Directory_name &specific_scenario_path
      ,const CORN::Text_list scenario_dirs
      ,const char *V);

};
//_2016-10-01___________________________________________________________________
} // namespace CS
#endif
