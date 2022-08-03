#ifndef convertorH
#define convertorH

#include "UED/library/datasetrec.h"
#include "UED/convert/convert_response.h"
#include "common/CS_parameter_float64.h"
#include "corn/application/arguments.h"

// This base class can be used by all convertors

// It handles the following:


// Command line
// Recording in the .INI file the last UED (and/or LOC) file processed
// for selection in ClimGen.

//_Forward declarations_________________________________________________________
class ED_tabular_file_format;                                                    //160216

namespace CORN {
   class Delineated_data_record;                                                 //160212
}
//______________________________________________________________________________
namespace UED
{
   class Database_file_indexed;                                                  //140527
//______________________________________________________________________________
class Column_elements
: public extends_ CORN::Bidirectional_list
{
 public:
   //___________________________________________________________________________
   class Column
   : public extends_ CORN::Item
   {
      std::string column_label;
    public:
      inline Column(const std::string &_column_label)
         : CORN::Item()
         , column_label       (_column_label)
         {}
      inline virtual bool is_key_string(const std::string &key)     affirmation_ //180820
         { return column_label == key; }

/*180820  was probably only used for find_cstr now using is_key
      inline virtual const char *get_key() const { return column_label.c_str();}
*/
   };

   //___________________________________________________________________________
   class Element
   : public extends_ Column
   {public:
      const UED::Data_record_creation_layout       &creation_layout;
      modifiable_ CS::Parameter                    &parameter;
    public:
      inline Element
         (const std::string                        &_column_label
         ,const UED::Data_record_creation_layout   &_creation_layout
         ,modifiable_ CS::Parameter                &_parameter)
         : Column(_column_label)
         , creation_layout    (_creation_layout)
         , parameter          (_parameter)
         {}
   };
   //___________________________________________________________________________
 public:
   inline Column_elements() : CORN::Bidirectional_list() {};
};
//_2014-05-23___________________________________________________________________
class Convertor
{public: // command line parameters
   //___________________________________________________________________________
   Convertor_arguments &arguments;                                               //171120

   // temporary alias
   Convertor_arguments &parameters;                                              //170328

 protected:
   //170328 moved to Arguments bool import_mode;                                 //150327
   //170328 Arguments handles response files dont delete until checked
   //180106 provided_ CORN::OS::File_name_concrete *response_filenameX;

      // The response_filename is probably obsolete because now there
      // is a generalized mechanism for handing response files


   provided_ CORN::OS::File_name_concrete *this_programs_ini;
   provided_ CORN::OS::Directory_name     *ued_file_path;
   bool                                    press_return_before_exit;
 protected:
   bool response_file_or_command_line_specified_geolocation_parameters;
 protected:
   provided_ UED::Database_file_indexed *UED_file;                               //160214_140527
   CORN::OS::Extension target_file_extension;                                    //140627
      // alias to arguments eventually just use arguments
 public:
   Convertor
      (Convertor_arguments &arguments);                                          //171120
      // This constructor is used when conversion is done as a standalone program.
   virtual ~Convertor();
 protected:
   bool setup_from_command_line()                                 modification_;
      // This option is used when the caller is a command line console mode application
 public:
   virtual int convert();
      // When used as a standalone program, (standalone constructor)
      // import and export function selection is specified on the command line.
      // in this mode simply call convert.
 public:
   virtual nat32 perform_import() = 0;
   virtual nat32 perform_export() = 0;
      // In stand alone mode, import and export are called by convert().
      // But they can be called sepcifically without using convert().
      // Not sure what to return  (returning 0 if nothing imported)
      // Returning the number of records imported
 public:
   // Derived convertors should override the following
   inline virtual nat16 get_version()                   const { return 0x0000; }
   inline virtual const char *get_application_name()                       const
      { return "UED import utility (Roger Nelson rnelson@wsu.edu)"; }
   inline virtual const char *get_target_file_extension() const { return "dat";} //151229_140627
      // This is used to assume a target filename extension
      // when export from UED file doesn't specifiy target filename.
      // (It will be given the same name as the UED file with this extension).
 public: // Methods for handling simple column oriented                          //140523
   Column_elements   column_elements;
   bool              comma_delimited;
   inline virtual bool create_column_elements
      (const CORN::Text_list &column_labels)                       modification_
      { return false;}
      //Derived classes will implement this if they use this new feature
   virtual nat32 import_records
      (std::istream &detail_line_stream)                          modification_;
      // returns the number of records imported
 protected:
   CORN::Date_time_clad_64 row_date_time; // rename this to detail line date time
   virtual bool import_detail_line(const std::string &detail_line)modification_;
   virtual bool import_detail_element
      (const Column_elements::Column &column
      ,const std::string &value)                                  modification_;
   virtual bool import_commit_detail_element
      (const Column_elements::Column &column)                     modification_;
      // Derived classes will implement if supported.
   inline virtual CORN::datetime64 get_detail_line_datetime()             const
      { return row_date_time.get_datetime64(); }
   virtual float32 get_valid_element_amount
      (const UED::Column_elements::Element *element
      ,CORN::Quality_clad &identified_quality)                            const;

   inline virtual const Data_record_creation_layout                              //160212
      *get_recognized_creation_layout(UED::Variable_code variable_code)
      { return 0; } // optional
   virtual UED::Database_file_indexed *provide_UED_file()            provision_; //160212
   inline virtual bool is_import_data_record                                     //160212
      (const CORN::Delineated_data_record &data_rec
      ,const ED_tabular_file_format &format
      ,const Bidirectional_list &import_columns
      ,const UED::Geolocation_record *header_identified_geoloc)    contribution_
      { return true; }
      // Convertor_weather will override and filter weather stations.
   inline virtual bool set_validated_elements
      (const CORN::Date_time &row_date_time
      ,CORN::Delineated_data_record &data_rec
      ,bool calculate_daily_values)
      { return true; }
   inline virtual bool inject_calculated_values() { return true; }               //160212
   inline virtual Geolocation_record *get_geolocation_record()                   //160212
      {  assert(false);
         // Conceptual
         // Not currently needed for generic conversions.
         // weather convertor will provide as needed (I.e. UED location record)
         // but be be needed more generically
         return 0;
      }
   inline virtual Geolocation *render_geolocation                                //160212
      (const std::string &station_ID)                                 rendition_
      {  assert(false);
         // Conceptual
         // Not currently needed for generic conversions.
         // weather convertor will provide as needed (I.e. UED location record)
         // but be be needed more generically
         return 0;
      }
};
//______________________________________________________________________________
} // namespace UED
#endif

