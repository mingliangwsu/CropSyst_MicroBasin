#ifndef collate_engineH
#define collate_engineH

#include "corn/chronometry/date_time_64.h"


#include "corn/OS/directory_entry_name.h"
#include "corn/tabular/tabular_format.h"
#include "corn/seclusion.h"
#include "corn/application/arguments.h"
#include "UED/convert/text_dBase_Excel_with_TDF/text_dbase_excel_with_tdf_convertor.h"

namespace UED
{
#define varible_definition_ALLOC_arbitrary 1024
class Database_file;
class Variable_format_0;
//______________________________________________________________________________
enum CS_Suite_Inspection_period
{  unknown_aggregation
,  annual_period
,  seasonal_period
,  harvest_period  // (event,period of one day?)
,  daily_period
,  continual_period                                                              //170411
};
//__________________________________________________CS_Suite_Inspection_period_/
class Collate_engine
{
 public:
   //___________________________________________________________________________
   class Arguments
   : public extends_ Convertor_arguments/*171120 Convert_response_data_record*/ //171120 Convertor::Arguments
   {
    public:
      CORN::OS::Directory_name_concrete  *top_level_directory; //owned
      CORN::Text_list                     UED_names;
      CORN::Text_list                     level_captions; // not wide
      CORN::Exclusion                     exclude_directories;                   //170404
    public:
      inline Arguments()
         : Convertor_arguments/*171120 Convertor::Arguments*/  ()
         , top_level_directory   (0)
         , UED_names             ()
         {}
      virtual ~Arguments();
      virtual bool recognize_option(const std::string &paramstring)  modification_;
      virtual bool recognize_assignment
         (const std::string &variable
         ,const std::string &value)                               modification_;
      /*180213
      virtual bool recognize_DEN
         (const CORN::OS::Directory_entry_name &param_DEN)        modification_;
      */
      virtual bool submit_DEN                                                    //180213
         (CORN::OS::Directory_entry_name *param_DEN)                submission_;
      virtual bool get_end();
      virtual bool write_help()                                           const;
   };
   //___________________________________________________________________________
 protected:
   Arguments &arguments;                                                         //170328
 protected:
   class Output_collator
   : public Text_dBase_Excel_with_TDF_convertor
   {
      std::wstring               UED_name;                                       //180119
         ///< name of current UED files being processed
         /// (I.e. CropSyst annual or seasonal or harvest)
      //Variable_format_0 *variable_definition[varible_definition_ALLOC_arbitrary];
      nat16 variable_definition_count;// the number of entries in the array.
    private:
      contribute_ bool columns_identified;                                       //141013
      CS_Suite_Inspection_period inspection_period;                              //170410
         // Currently UED output files named according to
         // the period of inspection.
      bool inspection_summary;                                                   //170410
         // Currently the UED output files have an indicator in
         // the filename to distinguish statistical summaries ($)
         // or inspected data elements (#).

         // CropSyst proper puts output files in "Output" directory
         // This directory is not considered a level

      // An arbitrary sized array of pointers to
      // the variable defnition records owned by the UED database
      // (so dont delete these).
      // It will only be setup once based of the variables identified in the UED file
      // in the first identified UED file (I.e. annual.UED or season.UED)
    private: // References to Collate_engine or instanciators' members
      const CORN::Text_list             &level_captions;    //string
      contribute_ const CORN::Text_list *leaf_level_names;  //wstring
      const CORN::Seclusion              &exclude_directories;                   //161201

    public:
      Output_collator
         (Arguments &arguments                                                   //170328
         ,const std::wstring                       &UED_name                     //180119
         ,const CORN::Text_list                    &level_captions
         ,const CORN::Seclusion                    &seclude_directories);        //161201
      nat32 collate_level
         (const CORN::OS::Directory_name  &level_directory
         ,nat8                             level_index
         ,CORN::Text_list                 &parent_level_names
         ,bool work_directory = true);
         ///< \returns the number  of detail lines written (excluding header)
      virtual bool initialize()                                  initialization_;//160606
    private:
      bool identify_columns(nat8 level_index);                                   //141013
      virtual bool transfer_tuple_column
         (CORN::Date_time &tuple_date_time
         , float32 value
         , nat16 export_column_number
         , UED::Export_column  *export_column);
   };
   //___________________________________________________________________________
 public:
   Collate_engine
      (Arguments &arguments);                                                    //170328
   bool process();
   nat32 process_UED(const std::wstring &UED_name);                              //180119
};
//_2014-09-03__________________________________________________Collate_engine__/
} // namespace UED


#endif
