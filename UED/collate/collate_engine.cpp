#include "collate_engine.h"
#include "corn/OS/file_system_engine.h"
#include "corn/container/text_list.h"
#include "corn/container/unilist.h"
#include "corn/data_source/vv_file.h"
#include "UED/library/database_file.h"
#include "UED/library/variable_format.h"
#include "UED/library/timeqry.h"
#include "UED/library/controls.h"
#include "UED/convert/ED_tabular_format.h"
#include "UED/convert/text_dBase_Excel_with_TDF/export_column.h"
#include <iomanip>
#include "CropSyst/source/csvc.h"
namespace UED
{
//______________________________________________________________________________
Collate_engine::Collate_engine
(Arguments &arguments_)
:  arguments(arguments_)
{}
//______________________________________________________________________________
bool Collate_engine::process()
{
   if (arguments.is_verbose(2)) //discovery
   {
   std::string UED_names_buffer;arguments.UED_names.string_items(UED_names_buffer,' ');
   std::clog <<  "collate output:"<< UED_names_buffer<< std::endl;
   }
   if (arguments.is_verbose(2)) //inclusion/selection
   {
   std::string level_captions_buffer;arguments.level_captions.string_items(level_captions_buffer,' ') ;
   std::clog << "levels=" << level_captions_buffer << std::endl;
   }
   nat32 total_detail_lines = 0;
   FOR_EACH_IN(UED_name, CORN::Item_wstring/*180119 Text_list::Item*/, arguments.UED_names, each_UED )
   {
      if (arguments.is_verbose(1)) //progression
         std::clog << "collating:" <<  UED_name->c_str() /*180119 (*UED_name)*/ << std::endl;
      total_detail_lines += process_UED(*UED_name);
   } FOR_EACH_END(each_UED)
   return total_detail_lines > 0;
}
//_2014-09-03___________________________________________________________________
nat32 Collate_engine::process_UED(const std::wstring &UED_name)                  //180119
{
   Output_collator collator(arguments,UED_name                                   //160526_170328
      ,arguments.level_captions,arguments.exclude_directories);
   // The variable definition array is instanciated here because it needs
   // to be the same for each set of UED files processed.
   collator.initialize();
   CORN::Text_list parent_level_names;
   nat32 UED_detail_lines = collator.collate_level
      (arguments.start_directory                                                  //170328
      ,0,parent_level_names,true);
   if (CORN::OS::file_system_engine.exists(collator.parameters.format_filename))//160606
   {
      std::clog << "info: "
      << "Format already exists it will not be overwritten" << std::endl
      << collator.parameters.format_filename.c_str() << std::endl;
   }
   else
   {  // No TDF file was specified on the command line
      // so by default the default format (R) is used
      // and columns are derived from variables available in the
      // UED file.
      // We write out the format created and used to the CWD
      // so the user can identify the columns and units.
      CORN::OS::Directory_name_concrete CWD;
      CORN::OS::File_name_concrete TDF_filename_generated(CWD,UED_name,L"TDF");
      CORN::VV_File TDF_file(TDF_filename_generated.c_str());
      collator.format.columns_1based.set_write_delimiter(0);                     //160601
      TDF_file.set(collator.format);                                             //161201
   }
   return UED_detail_lines;
}
//_2014-10-17___________________________________________________________________
Collate_engine::Output_collator::Output_collator
(Arguments &arguments_
,const std::wstring                       &UED_name_                             //180119
,const CORN::Text_list                    &level_captions_
,const CORN::Seclusion                    &seclude_directories_)                 //161201
: Text_dBase_Excel_with_TDF_convertor  (arguments_)                              //170328
, UED_name(UED_name_)
, level_captions           (level_captions_) // derived from the directory heirarchy
, exclude_directories      (seclude_directories_)
, variable_definition_count(0)
, columns_identified       (false)
, inspection_period        (unknown_aggregation)                                 //170410
, inspection_summary       (false)                                               //170410
, leaf_level_names         (0)                                                   //141014
{
   /*170410  I don't remember what was annual_aggr file and
      I don't see any programs generating such a file.
      In any case currently aggregation files probably correspond to
      the new naming convention for CS observation output files named
      with $  I.e. $d is aggregation of daily data where
      ($ means scalar statistical summary )
   if (UED_name_ == "annual_aggr") CS_suite_output_UED_file_type = annual_aggr_aggregation;
   */
   inspection_summary = UED_name_.find(L"$") != std::string::npos;                //170410
   if (
        //170410  (inspection_period != annual_aggr_aggregation_check_obsolete) &&
       (UED_name_.find(L"annual") != std::string::npos))
      inspection_period = annual_period;

   if ((UED_name_.find(L"season")    != std::string::npos) // V4                   //170404
     ||(UED_name_.find(L"seasonal")  != std::string::npos))// V5                   //170404_170314
      inspection_period = seasonal_period;
   if (UED_name_.find(L"harvest")    != std::string::npos)
      inspection_period = harvest_period;
   if ((UED_name_.find(L"daily")     != std::string::npos)  // V4
     ||(UED_name_.find(L"journal")   != std::string::npos)) // V5                 //170314
      inspection_period = daily_period;
   if (UED_name_.find(L"continual")    != std::string::npos)                      //170411
      inspection_period = continual_period;

   parameters.operation = "export";                                              //160606
   //171120 arguments.import_mode = false; // The collator is essentially a UED exporter            //160606
   setup_from_command_line(); //170328 (argc_,argv_);                                         //160606
      // Probably should move this out of constructor
}
//_2014-09-08___________________________________________________________________
bool Collate_engine::Output_collator::initialize()               initialization_
{
   format.default_R_text();
   return true;
}
//_2016-06-06__________________________________________________________________/
nat32 Collate_engine::Output_collator::collate_level
(const CORN::OS::Directory_name  &level_directory
,nat8                             level_index
,CORN::Text_list                 &parent_level_names    //wide
,bool                             work_directory)
{
   if (level_directory.get_name() == L"Comparision")
      return 0;
      // This is an Output Comparison which must not be included in Collation
   if (arguments.is_verbose(3)) // progression?
      std::clog << "subscenario: " << level_directory.c_str() << std::endl;
   bool this_is_output_directory = (level_directory.get_name() == L"Output");
   nat32 detail_lines = 0;
   Year file_year = 0;   // Currently there is no year separation
   tabular_file = provide_tabular_file(file_year);
   if (!tabular_file) return 0; // Probably unable to determine the desired target file type  //070307
   if (!work_directory && !this_is_output_directory)
   {  std::wstring level_name;
      level_directory.get_name_with_extension(level_name);                       //160526
      parent_level_names.add_wstring(level_name);
   }
   std::string names_buffer;
//debug   std::clog << parent_level_names.string_items(names_buffer, ' ') << std::endl;
   // parent_level_names.write(std::clog); std::clog << std::endl;
   leaf_level_names = &parent_level_names;                                       //141014
   CORN::OS::File_name_concrete UED_filename
      (level_directory,UED_name,"UED");
   parameters.UED_filename.set_DEN(UED_filename);                                //170411
      // Currently only used for verbose output.
   if (CORN::OS::file_system_engine.exists(UED_filename))                        //160306
   {
   if (arguments.is_verbose(2)) //discovery
         std::clog << "UED file:" << UED_filename.c_str() << std::endl;
/*
PROCESS_MEMORY_COUNTERS pmc;
GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
SIZE_T physMemUsedByMe_before_open = pmc.WorkingSetSize;
*/


      UED_file = new UED::Database_file_indexed(UED_filename.c_str(),std::ios::in,false);
      UED_file->initialize();                                                    //170404

      if (! columns_identified)
      {
/*
continue here at this point we have setup the format filename.
but it will be over ridden when we initialize export.
if we have the format filename, we shouldnt need to identify_columns,
just initialize export
*/
         if (!CORN::OS::file_system_engine.exists(arguments.format_filename))    //170616
            columns_identified = identify_columns(level_index);                  //141013
        initialize_export();                                                     //160615
      }
      Tuple_index      export_tuples;                                            //180109
      detail_lines += tuplize_opened_UED_file(export_tuples);                    //180109_171130
      nat32 data_line_count = extract_tuples(export_tuples);                     //180109
      commit_export();                                                           //171130
      delete UED_file; UED_file = 0;
/*
GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
std::clog << "before UED:" << physMemUsedByMe_before_open << std::endl;
std::clog << "after  UED:" << physMemUsedByMe << std::endl;
if (physMemUsedByMe != physMemUsedByMe_before_open)
std::clog << "memory leak" << std::endl;
*/
      leaf_level_names = 0;                                                      //141014
   } else
   {
/*
PROCESS_MEMORY_COUNTERS pmc;
GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
SIZE_T physMemUsedByMe_before_open = pmc.WorkingSetSize;
*/
      CORN::Unidirectional_list subdirs; //fully qualified directory names
      CORN::OS::file_system_engine.list_DENs
         (level_directory
         ,0,&subdirs                                                             //161201
         ,exclude_directories                                                    //161201
         ,CORN::OS::File_system::none_recursion_inclusive);
      nat32 subdir_count = subdirs.count();                                      //170305
      if (subdir_count)
      {
         leaf_level_names = 0;                                                   //141014
         FOR_EACH_IN(subdir,CORN::OS::Directory_entry_name,subdirs,each_subdir)
         {
//std::clog << "level:" << (int)level_index << std::endl;
//if (this_is_output_directory)
//std::clog << "outdir" << std::endl;

            {
               detail_lines += collate_level(*subdir,
                  level_index + !this_is_output_directory                        //160601
                  ,parent_level_names,false);
            }
         }
         FOR_EACH_END(each_subdir)
      } // else do nothing we are done with this directory
/*
GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
std::clog << "before CL:" << physMemUsedByMe_before_open << std::endl;
std::clog << "after  CL:" << physMemUsedByMe << std::endl;
if (physMemUsedByMe != physMemUsedByMe_before_open)
std::clog << "memory leak" << std::endl;
*/
   }

   /* For REACCH, the cell directory may have single aggregated UED file
      so, when processing annual_aggr.UED found the target UED file
      and dont descend into the  the cycle directory
   CORN::Unidirectional_list subdirs; //fully qualified directory names
   nat32 subdir_count = CORN::OS::file_system_engine.list_directory_names
      (level_directory
      ,subdirs
      ,CORN::OS::File_system::none_recursion_inclusive
      ,CORN::OS::Directory_entry_name::full_qualification);
   if (subdir_count)
   {
      leaf_level_names = 0;                                                      //141014
      FOR_EACH_IN(subdir,CORN::OS::Directory_entry_name,subdirs,each_subdir)
         detail_lines += collate_level(*subdir,level_index+1,parent_level_names,false);
      FOR_EACH_END(each_subdir)
   } else
   {
      leaf_level_names = &parent_level_names;                                    //141014
      CORN::OS::File_name_concrete UED_filename(level_directory,UED_name,"UED");
      std::clog << "UED file:" << UED_filename.c_str() << std::endl;
      //UED::Database_file UED_file(UED_filename.c_str(),std::ios::in,false);
      UED_file = new UED::Database_file_indexed(UED_filename.c_str(),std::ios::in,false);
      if (! columns_identified)
      {
         columns_identified = identify_columns(level_index);                     //141013
         initialize_export();                                                    //141017
      }
      //151125 ued_file_to_export = UED_file;   // actually just used UED_file
      detail_lines += export_opened_UED_file();
      delete UED_file; UED_file = 0;
      leaf_level_names = 0;                                                      //141014
   }
   */
   if (!this_is_output_directory)                                                //160602
      delete parent_level_names.pop_at_tail();                                   //170630
   return detail_lines;
}
//_2014-09-03___________________________________________________________________
bool Collate_engine::Output_collator::identify_columns(nat8 level_index)
{
   bool annual_mode = (inspection_period == annual_period);
   if (arguments.is_verbose(3))  //discovery/origination
         std::clog << "Identifying columns" << std::endl;
   bool add_level_column_header_to_format = false;
      if (format.columns_1based.count())
      {  // The TDF file was specified and it has identified the columns
         // and variables to be included.
         // The TDF file is optional, if not specified,
         // the columns will be ordered as the variable definitions
         // (which there should now be) appear in the UED file.

         //Shouldn't need to compose variable definition array from format.columns
         //because all we need to read the UED file is the (desired) variable codes.
      } else
      {  add_level_column_header_to_format = true;

         format.columns_1based.set_unique_keys(true);                            //171015
            // shouldn't be needed but current CropSyst crop
            // is dumping many variable definitions with unique variable codes
            // once I fix this
         // Column
         //171017 always have date column if (annual_mode)                                                       //141120
         {
         ED_tabular_file_format::Column *date_column = new
               ED_tabular_file_format::Column() ;
         date_column->record_date = true ;
         date_column->units                 = annual_mode ? UT_year : UT_date;
         date_column->date_time_format      = annual_mode ? "YYYY"  : "YYYY-MM-DD(DOY)";
         date_column->caption               = annual_mode ? "year"  : "YYYY-MM-DD(DOY)";
         date_column->field_width           = 10;
         date_column->data_type_labeled.set(annual_mode ? DT_int16 :
            //170117 DT_float32
            DT_date                                                              //171017
            ); // In because years can be negative
         //NA date_column->name_long
         //NA date_column->name_short
         //NA date_column->name_subsection
         //NA date_column->precision
         //NA date_column->period
         //NA date_column->sheet
         //NA date_column->smart_record_type
         //NA date_column->smart_variable_code.code

         format.columns_1based.append(date_column);
         }
         nat32 defined_variable_codes[varible_definition_ALLOC_arbitrary];
         for (int dvc = 0; dvc <varible_definition_ALLOC_arbitrary; dvc++)       //171015
            defined_variable_codes[dvc] = 0;                                     //171015
         variable_definition_count = UED_file->get_defined_variables_codes
            (defined_variable_codes,(nat16)varible_definition_ALLOC_arbitrary);
         if (arguments.is_verbose(3)) //count
         std::clog << "variable count = " << variable_definition_count << std::endl;
         switch (inspection_period)
         {
            case harvest_period:
            {
               {
               ED_tabular_file_format::Column *variable_column = new
                  ED_tabular_file_format::Column();
               variable_column->caption  = "variable";
               variable_column->data_type_labeled = DT_string;
               variable_column->field_width = 100;
               // This is currently arbitrary,
               // because this is intended to be free form tab or space delimited;
               // but the TDF file could specify a "variable" column format
               format.columns_1based.append(variable_column);
               }
               {
               ED_tabular_file_format::Column *value_column = new
                  ED_tabular_file_format::Column();
               value_column->caption  = "variable";
               value_column->data_type_labeled = DT_string;
               value_column->field_width = 100;
               // This is currently arbitrary,
               // because this is intended to be free form tab or space delimited;
               // but the TDF file could specify a "variable" column format
               format.columns_1based.append(value_column);
               }
             } break;
            case annual_period: case seasonal_period: case daily_period:
            case continual_period :
            default:
            {  for (nat16 vd = 0; vd <variable_definition_count; vd++)
               {
                  const Variable_format_abstract *variable_definition
                      = UED_file->get_variable_definition(defined_variable_codes[vd]);
                  if (arguments.is_verbose(3))  //level?inclusion?
                     std::clog << variable_definition->ref_description()
                     << std::endl;
                  ED_tabular_file_format::Column *column = new
                     ED_tabular_file_format::Column() ;
                  column->caption            = variable_definition->ref_description();
                  column->data_type_labeled  = DT_float32; // UED uses 32 (or 16) bit float.
                  // column->description_URL  eventually will have a complete ontology (for CropSyst output variables)
                  column->field_width        = 30; // will not generally be used for most free form target formats
                  column->name_long          = variable_definition->ref_description();
                  column->name_short         = variable_definition->ref_description();
                  //column->name_subsection    =  not needed for simple 2D table.
                  column->precision          = 6; // approximate precision of 32bit floats
                  // column->period not applicable (-1)

                  column->record_date        = false;
                  //column->sheet               currently only exporting a simple 2D table.
                  //column->smart_record_type only used with importing to UED
                  column->smart_variable_code.set(variable_definition->code_clad.get());
                  column->units.set(variable_definition->preferred_units_clad.get());
                  // column->date_time_format   =  NA because use for dates
                  // column->units_caption Not needed because we get the units from UED record and they would likely be standard
                  format.columns_1based.append(column);
               }
            } break;
         }
      }
   if (add_level_column_header_to_format)
   { // If we dont have predefined format, then add the caption column headers
      for (nat8 il = 0; il < level_index; il++)
      {
         ED_tabular_file_format::Column *column = new
               ED_tabular_file_format::Column               () ;
            const CORN::Item *level_caption = dynamic_cast<const CORN::Item *>(level_captions.get_at(il));
            std::string caption_text;
            if (level_caption)
               level_caption->append_to_string(caption_text);                    //180119
            column->caption = caption_text;
            column->data_type_labeled  = DT_string; // UED uses 32 (or 16) bit float.
            // column->description_URL  eventually will have a complete ontology (for CropSyst output variables)
            column->field_width        = 12;
            column->record_date        = false;
            format.columns_1based.append(column);
      }
   }

// std::clog << "col count: " << format.columns_1based.count() << std::endl;

   return true;
}
//_2014-09-08___________________________________________________________________
bool Collate_engine::Output_collator::transfer_tuple_column
( CORN::Date_time &tuple_date_time
, float32 value
, nat16 export_column_number
, Export_column  *export_column)
{
   bool transferred = (export_column->TC_layout.data_type_labeled.get() == DT_string);

//std::clog << "/" << export_column->TC_layout.name_long << "\\ " << std::endl;

   if (transferred) // So far this column appears could be a directory (scenario) level
   {  transferred = false; // now see if this column is level

         // Probably obsolete (at least in V5) because now for CropSyst crops are
         // in separate files which the collator picks up as a separate output directory.
         if (export_column->TFFC_layout.smart_variable_code.get() == CSVC_crop_base_name)
         {
            const UED::Period_record *growing_season = UED_file->get_period
               (

                  // UED_period_start_date_time_option
                  UED_period_end_date_time_option
                 |UED_period_application_code_option
                 |UED_period_variable_code_option
               //|UED_period_enumeration_option
               //|UED_period_index_option
               ,tuple_date_time.get_datetime64() // at_date
               ,1 // GROWING_SEASON_PERIOD // _application_code  (1)
               ,0 //_enumeration
               ,0 // _index           0X1EE665
               ,CSVC_crop_base_name);

            if (growing_season)
            {
               export_column->value_string.assign(growing_season->get_text());
            }
            else
            {
               export_column->value_string.assign("Unknown");
            }
            transferred = true;
         }
      if (!transferred)                                                          //141201
      {
      nat8 level_i = 0;
      FIND_FOR_EACH_IN(found_level_caption,level_caption,CORN::Item_string/*180119 Text_list::Item*/,level_captions,true,each_level)
      {
         if ((*level_caption) == export_column->TC_layout.caption)
         {
            found_level_caption = level_caption;
            //const char *delimitor = export_column_number ? format.detail_lines_delineation.get_delimitor() : "";  // Don't prepend delimitor for column 0   //050902
            const CORN::/*180119 Text_list::*/Item * level_name = dynamic_cast<const CORN::/*180119 Text_list::*/Item *>(leaf_level_names->get_at(level_i));
            if (level_name)
            {  export_column->value_string.clear();                              //180119
               level_name->append_to_string(export_column->value_string);        //180119
               //180119 export_column->value_string.assign(*level_name);
            }
/*check needed
            else
               assert(false);
*/
            transferred = true;
         }
         level_i ++;
      } FOR_EACH_END(each_level)
      }
   }
   if (!transferred)
      transferred = Tabular_file_with_TDF_convertor::transfer_tuple_column
         (tuple_date_time,value,export_column_number,export_column);
   return transferred;
}
//_2014-10-16___________________________________________________________________
/*180213
bool Collate_engine::Arguments::recognize_DEN
(const CORN::OS::Directory_entry_name &param_DEN)                  modification_
{  bool recognized = false;
   if ( (param_DEN.has_extension(L"UED"))
      ||(param_DEN.has_extension(L"ued"))) // currently accepting lower case
   {  UED_names.add_wstring(param_DEN.get_name());
      recognized = true;
   } else
   if (!top_level_directory && param_DEN.is_directory()
       && CORN::OS::file_system_engine.exists(param_DEN))
   {  top_level_directory
         = new CORN::OS::Directory_name_concrete(param_DEN,CORN::OS::directory_entry);
      recognized = true;
   }
   return recognized || Convertor_arguments::recognize_DEN(param_DEN);
}
//_2017-03-28___________________________________________________________________
*/
bool Collate_engine::Arguments::submit_DEN
(CORN::OS::Directory_entry_name *param_DEN)                          submission_
{  bool recognized = false;
   if ( (param_DEN->has_extension(L"UED"))
      ||(param_DEN->has_extension(L"ued"))) // currently accepting lower case
   {  UED_names.add_wstring(param_DEN->get_name());
      delete param_DEN;
      recognized = true;
   } else
   if (!top_level_directory && param_DEN->is_directory()
       && CORN::OS::file_system_engine.exists(*param_DEN))
   {  top_level_directory =
         dynamic_cast<CORN::OS::Directory_name_concrete *>(param_DEN);
      recognized = true;
   }
   return recognized || Convertor_arguments::submit_DEN(param_DEN);
}
//_2017-03-28___________________________________________________________________
bool Collate_engine::Arguments::recognize_assignment
(const std::string &variable
,const std::string &value)                                         modification_
{  bool recognized = false;

   //180514  Actually seclusion arguments can be handled with seclusion class


   if (variable == "--exclude")
   {  exclude_directories.exclude_pattern_string(value);
      recognized = true;
   }
   return recognized
     || UED::Convertor_arguments::recognize_assignment(variable,value);
}
//_2017-03-28___________________________________________________________________
bool Collate_engine::Arguments::recognize_option
(const std::string &paramstring)                                   modification_
{  bool recognized = false;
   if (paramstring == "captions:")
   {
      collect_remaining = &level_captions;
      // remaining_captions = true;
      recognized = true;
   }
   return recognized
     || UED::Convertor_arguments::recognize_option(paramstring);
}
//_2017-06-16___________________________________________________________________

bool Collate_engine::Arguments::get_end()
{  bool got = true;
   if (level_captions.count() == 0)
   {
      std::cerr
         << "Scenario level captions should be specified on the command line"
         << " (I.e. for REACCH: zone rotation weather,  or zone rotation GCM RCP, followed by cell)"
         << "The captions should ordered matching the directory tree structure." << std::endl;
      got = false; // return EXIT_FAILURE;
   }
   if (!top_level_directory) // then start with CWD
        top_level_directory = new CORN::OS::Directory_name_concrete();
   if (UED_names.count() == 0)
   {
/* conceptual
should search for UED (or rather list the unique UED names as encountered.
*/

      UED_names.add_cstr("annual");
      UED_names.add_cstr("season");                                              //170314
      UED_names.add_cstr("seasonal");
      UED_names.add_cstr("harvest");
      UED_names.add_cstr("daily");
      UED_names.add_cstr("journal");                                             //170314
/*NYI
soil@annual$d.UED
crop@seasonal$d.UED
 organic_matter@annual$d.UED
land_unit@annual$d.UED
meteorology@annual$d.UED
*/
   }
   got &= Convertor_arguments::get_end();
   return got;
}
//_2017-03-28___________________________________________________________________
Collate_engine::Arguments::~Arguments()
{  delete top_level_directory;
}
//_2017-03-28___________________________________________________________________
bool Collate_engine::Arguments::write_help()                               const
{
   std::clog
      << "The collation is written to standard output.\n\n"
      << "Command line arguments (these may be listed in any order):\n\n"
      << "Scenario level directory name (qualified or unqualified).\n"
      << "(optional: If no directory is specified on the command line, the current\n"
      << " working directory is assumed as the upper most scenario level directory.\n\n"
      << "One or more UED filenames to be collated (unqualified with UED extension).\n"
      << "(optional: If no UED file names are specified then (for CropSyst outputs)\n"
      << " annual seasonal harvest and daily are processed each in turn.\n\n"
      << "TDF file name (qualified or unqualified).\n"
      << "(optional: The TDF file can be used to customize the output formant.\n"
      << " If omitted, a TDF corresponding to the default format is created,\n"
      << " this can be customized for future runs. \n"
      << " The default format will be suitable for most cases.  Because the daily output\n"
      << " can be extensive, one should consider a custom format for daily output.\n\n"
      << "Level captions  which correspond to the directory structure.\n"
      << " For CropSyst (REACCH) these would be various levels.\n"
      << " These should be one word with no spaces (use underscores)\n."
      << "(recommended/required: otherwise where would be no column header captions)."
      << std::endl;
   return true;
}
//_2017-03-28___________________________________________________________________
} // namespace UED

