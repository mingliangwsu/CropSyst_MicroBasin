#include "CS_suite/observation/CS_reporter.h"

#include "corn/OS/file_system_engine.h"
#include "corn/data_source/vv_file.h"
#include "CS_suite/observation/CS_inspector.h"
#include "corn/dynamic_array/dynamic_array_T.h"
namespace CS {
//______________________________________________________________________________
Reporter::Reporter
(const Inspector                      &_inspector
,const ED_tabular_file_format::Column &_column
)
: CORN::Item()
, inspector (_inspector)
, column    (_column)
{}
//_2015-09-19__________________________________________________________________/
Reporters::Reporters
(
//now use CS::examination_globalconst CORN::Container &_inspectors,
 Output_aggregation         _aggregation
,const CORN::OS::File_name &_TDF_filename)
: CORN::Unidirectional_list(true)
//now use CS::examination_global, inspectors   (_inspectors)
, format       ()
, TDF_filename (_TDF_filename)
, last_known_inspector_count(0)
, aggregation  (_aggregation)
{
   load_TDF_format(TDF_filename);
}
//_2015-09-19__________________________________________________________________/
Reporters::Reporters
(
//now use CS::examination_globalconst CORN::Container     &_inspectors,
Output_aggregation         _aggregation
//,CORN::Units_code           _detail_line_time_step
)
: CORN::Unidirectional_list(true)
//now use CS::examination_global, inspectors(_inspectors)
, format       ()
, TDF_filename ("R.TDF")
, last_known_inspector_count(0)
, aggregation  (_aggregation)
{
   CORN::Units_code detail_line_time_step = UT_day;
   switch (aggregation)
   {
      case annual_aggregation    : detail_line_time_step = UT_year; break;
      case season_aggregation    :
      case harvest_aggregation   :
      case daily_aggregation     :
      default : detail_line_time_step = UT_day; break;
   }
   format.detail_lines_delineation.time_step_units_enum.set(detail_line_time_step);
   load_TDF_format(TDF_filename);
}
//_2015-09-19__________________________________________________________________/
bool Reporters::load_TDF_format(const CORN::OS::File_name &TDF_filename)
{
   predefined_format = CORN::OS::file_system_engine.exists(TDF_filename);
   if (predefined_format)
   {
      CORN::VV_File TDF_file(TDF_filename.c_str());
      TDF_file.get(format);
   } else format.default_R_text();
   return inspectors.count() > 0;
}
//_2015-09-19__________________________________________________________________/
bool Reporters::initialize()                                     initialization_
{
      bool annual_mode = aggregation == annual_aggregation;
         if (annual_mode)                                                       //141120
         {
         ED_tabular_file_format::Column *date_column = new
               ED_tabular_file_format::Column() ;

         date_column->record_date = true ;
         date_column->units                 = annual_mode ? UT_year : UT_date;
         date_column->date_time_format      = annual_mode ? "YYYY"  : "YYYY-MM-DD";
         date_column->caption               = annual_mode ? "year"  : "YYYY-MM-DD";
         date_column->field_width           = 10;
         date_column->data_type_labeled.set(annual_mode ? DT_int16 : DT_float32 ); // In because years can be negative
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
         else                                                                    //141201
         {
            ED_tabular_file_format::Column *crop_name_column = new
               ED_tabular_file_format::Column() ;
            crop_name_column->record_date = false ;
            // NA crop_name_column->units
            // NA crop_name_column->date_time_format
            crop_name_column->caption               = "crop";
            crop_name_column->field_width           = 50;
            crop_name_column->data_type_labeled.set(DT_string); // In because years can be negative
            crop_name_column->name_long= "crop";
            crop_name_column->name_short= "crop";
            //NA crop_name_column->name_subsection
            //NA crop_name_column->precision
            //NA crop_name_column->period
            //NA crop_name_column->sheet
            //NA crop_name_column->smart_record_type
            /*150929
            #if (CS_VERSION < 5)
            // In V5 I am trying to eliminate predefined variable codes
            crop_name_column->smart_variable_code.set(CSVC_crop_base_name);
            #endif
            */
            format.columns_1based.append(crop_name_column);
         }
   return true;
}
//_2015-09-19__________________________________________________________________/
bool Reporters::resync()                                          incorporation_
{  nat32 current_inspectors_count = inspectors.count();
   bool resynced =
      (current_inspectors_count == last_known_inspector_count)
      ? true // insync: no new inspectors since last resync
      : (predefined_format) // we have already loaded format
         ? resync_to_predefined_format()
           // The TDF file was specified and it has identified the columns
           // and variables to be included.
           // The TDF file is optional, if not specified,
           // the columns will be ordered as variable inspectors are identified
           // (which there should now be) appear in the UED file.
         : resync_defining_format();
   last_known_inspector_count = current_inspectors_count;
   return resynced;
}
//_2015-09-19__________________________________________________________________/
bool Reporters::resync_to_predefined_format()                     incorporation_
{
   FOR_EACH_IN(column,ED_tabular_file_format::Column,format.columns_1based,each_column)
   {
      const Reporter *found_matching_reporter = find_reporter_with_properties(*column);
      if (!found_matching_reporter)
      {
         const Inspector *found_inspector = find_inspector_with_properties(*column);
         if (found_inspector)
         {
            Reporter *added_reporter = new Reporter(*found_inspector,*column);
         }
         // else  there is no inspector listed to report
         // I.e. the column is a Crop or other dynamicaly ephemeral object's variable
      }
   } FOR_EACH_END(each_column)
   return true;
}
//_2015-09-19__________________________________________________________________/
bool Reporters::resync_defining_format()
{
         // Column
         std::clog << "Identifing columns" << std::endl;

         switch (aggregation)
         {
            case annual_aggregation : case season_aggregation : case daily_aggregation :
            {
               FOR_EACH_IN(inspector, Inspector, inspectors,each_inspector)
               // for (nat16 vd = 0; vd <variable_definition_count; vd++)
               {
                  if (find_reporter_with_inspector(*inspector) == 0) // in this list of reporters
                  {  // We haven't setup a reporter
                  //const Variable_format_0 *variable_definition = UED_file->get_variable_definition(defined_variable_codes[vd]);
                  //std::clog << variable_definition->description
                  //  //<< " (" << variable_definition->abbreviation << ")"
                  //    << std::endl;
                  ED_tabular_file_format::Column *column = new
                     ED_tabular_file_format::Column() ;

                  column->data_type_labeled  = DT_float32; // UED uses 32 (or 16) bit float.
                  // column->description_URL  eventually will have a complete ontology (for CropSyst output variables)
                  column->field_width        = 30; // will not generally be used for most free form target formats

                  #ifdef PARAMETER_PROPERTY_ONTOLOGICAL
                  // NYI get the properies from properties file
                  // The path of the filename will be provided by
                  // Parameter_property_ontological property
                  #else
                  column->caption            = inspector->ontology;              //160606
                  //160606 column->caption            = inspector->properties.caption;
                  //160606 column->name_long          = inspector->properties.name_long;
                  //160606                   column->name_short         = inspector->properties.name_short;
                  //160606                   column->name_subsection    = inspector->properties.name_subsection; // Not used for this
                  //160606                   column->description_URL    = inspector->properties.description_URL; // Not used for this
                  //160606                   column->hint               = inspector->properties.hint; // Not used for this
                  //column->name_subsection    =  not needed for simple 2D table.
                  column->precision          = 6; // approximate precision of 32bit floats
                  // column->period not applicable (-1)

                  //160606                   column->units_caption      = inspector->properties.prefered_units_caption_or_date_time_format;
                  //160606 column->units           .set(inspector->shown_units_code.get());
                  column->units              .set(inspector->value_units_code);

                  #endif

                  column->record_date        = false;
                  //column->sheet               currently only exporting a simple 2D table.
                  //column->smart_record_type only used with importing to UED
                  column->smart_variable_code.set(0); // variable code is not currently used (In V5)
                  // column->date_time_format   =  NA because use for dates
                  // column->units_caption Not needed because we get the units from UED record and they would likely be standard

                  format.columns_1based.append(column);
                  } // if found inspector
               } FOR_EACH_END(each_inspector) // for each inspector
            } break;
         } // switch
   return format.columns_1based.count() > 0;
}
//_2015-09-19__________________________________________________________________/
const Reporter *Reporters::find_reporter_with_properties
(const Parameter_properties_string &properties)                            const
{
   FIND_FOR_EACH(found_reporter,reporter,Reporter,true,each_reporter)
   {
      //160606 #ifdef PARAMETER_PROPERTY_ONTOLOGICAL
      if (properties.get_description_URL() == reporter->inspector.ontology)      //160604
         // This should be the qualified ontology

      //160606 #else
      //160606 if (reporter->inspector.properties.name_short == properties.name_short)
      //160606 #endif
         found_reporter = reporter;
   } FOR_EACH_END(each_reporter)
   return found_reporter;
}
//_2015-09-19__________________________________________________________________/
const Inspector *Reporters::find_inspector_with_properties
(const Parameter_properties_string &properties)                            const
{
   FIND_FOR_EACH_IN(found_inspector,inspector,Inspector,inspectors,true,each_inspector)
   {
      //160606 #ifdef PARAMETER_PROPERTY_ONTOLOGICAL
      if (properties.get_description_URL() == inspector->ontology)               //160604
         // This should be the qualified ontology

      //160606 #else
      //160606 if (inspector->properties.name_short == properties.name_short)
      //160606 #endif
         found_inspector = inspector;
   } FOR_EACH_END(each_inspector)
   return found_inspector;
}
//_2015-09-19__________________________________________________________________/
const Inspector *Reporters::find_inspector(const Inspector &inspector_to_find)      const
{  FIND_FOR_EACH_IN(found_inspector,inspector,Inspector,inspectors,true,each_inspector)
   {  if (inspector == &inspector_to_find)
         found_inspector = inspector;
   } FOR_EACH_END(each_inspector)
   return found_inspector;
}
//_2015-09-19__________________________________________________________________/
const Reporter *Reporters::find_reporter_with_inspector(const Inspector &inspector_to_find)     const
{  FIND_FOR_EACH(found_reporter,reporter,Reporter,true,each_reporter)
   {  if (&reporter->inspector == &inspector_to_find)
         found_reporter = reporter;
   } FOR_EACH_END(each_reporter)
   return found_reporter;
}
//_2015-09-19__________________________________________________________________/
const Reporter *Reporters::find_reporter_with_column
(const ED_tabular_file_format::Column *column)                             const
{  FIND_FOR_EACH(found_reporter,reporter,Reporter,true,each_reporter)
   {  if (&reporter->column == column)
         found_reporter = reporter;
   } FOR_EACH_END(each_reporter)
   return found_reporter;
}
//_2015-09-19__________________________________________________________________/
bool Reporters::stop()                                              modification_
{
   bool stopped = true;
   if (!predefined_format)
   {
      CORN::OS::Directory_entry_name_concrete format_dir
            (TDF_filename.get_parent_directory_name_qualified());
      CORN::OS::file_system_engine.provide_directory/*180321 create_directory*/(format_dir);
      CORN::VV_File TDF_file(TDF_filename.c_str());
      stopped = TDF_file.set(format);
   }
   return stopped;
}
//_2015-09-19__________________________________________________________________/
bool Reporting::start()                                            modification_
{
   if (reporters.predefined_format)
   {
      /*
         column_start .append(0); // index 0 is unused                           //100104
         column_widths.append(0); // index 0 is unused                           //100104
         FOR_EACH_IN(format_column,ED_tabular_file_format::Column,reporters.format.columns_1based,each_format_column) //050411_
         {  column_start.append(format_column->start_1based);                    //100104
            column_widths.append(format_column->field_width);                    //050411
         } FOR_EACH_END(each_format_column)                                      //050411
      */



     //continue here output headers



   }  // else we can't output headers because we don't necessarily
      // know all the potential columns because there may be ephemeral objects

   return true;
}
//_2015-09-19__________________________________________________________________/
bool Reporting::end_day()                                          modification_
{  bool ended = reporters.resync();
   if (reporters.predefined_format)
   {
      bool first_column = true;
      FOR_EACH_IN(column,ED_tabular_file_format::Column,reporters.format.columns_1based,each_column)
      {
         if (first_column)
            reporters.format.detail_lines_delineation.get_delimitor();
         if (column->record_date)
         {
            report_stream << today.as_string();
         }
         else
         {
            const Reporter *reporter = reporters.find_reporter_with_column(column);
            if (reporter)
            {  std::string value_str;
               reporter->inspector.
                  append_value_in_radix_to(value_str,5,10);                         //160604
                  //160604 append_value(value_str);
               report_stream << value_str;
            } // else // should always find reporter at this point
         }
         first_column = false;
      } FOR_EACH_END(each_column)
      report_stream << std::endl;

   }  // else we don't necessarily know all the potential columns
      // because there may be ephemeral objects
   return ended;
}
//_2015-09-19__________________________________________________________________/
Reporting::Reporting
(Output_aggregation              aggregation
//now use CS::examination_global ,const CS::Inspectors           &inspectors
,const CORN::OS::Directory_name &scenario_output_directory
,const CORN::OS::Directory_name &project_database_format_directory
,const CORN::Date               &_today)
: TDF_filename    (project_database_format_directory,get_aggregation_filename(aggregation),"TDF")
, report_filename (scenario_output_directory        ,get_aggregation_filename(aggregation),"dat")
, report_stream   (report_filename.c_str())
, reporters       (
//now use CS::examination_globalinspectors,
   aggregation,TDF_filename)
, today           (_today)
//, report          (report_stream,reporters,_today)
{
}
//_2015-09-19__________________________________________________________________/
const wchar_t *Reporting::get_aggregation_filename(Output_aggregation aggregation) const
{
   const wchar_t *aggr_filename = L"unknown";
   switch (aggregation)
   {
      case CS::annual_aggregation : aggr_filename = L"annual";    break;
      case CS::daily_aggregation  : aggr_filename = L"daily";     break;
      case CS::season_aggregation : aggr_filename = L"seasonal";  break;
      case CS::harvest_aggregation: aggr_filename = L"harvest";   break;
   }
   return aggr_filename;
}
//_2015-09-19__________________________________________________________________/
bool Reporting::initialize()                                     initialization_
{  return reporters.initialize();
}
//_2015-09-19__________________________________________________________________/
bool Reporting::stop()                                              modification_
{  return reporters.stop();
}
//_2015-09-19__________________________________________________________________/
} // namespace CS
//______________________________________________________________________________
/*150818 Needs to be moved (don't delete)
 *  This was the original variable recording report generation
 *  it is obsolete
 *
bool  Inspectors::write_R_headers
(std::ostream &R_stream
,bool annual_header)                                                performs_IO_
{  R_stream << "Year";
   FOR_EACH (recorder,Inspector,each_recorder)
   {  CORN::Units_clad units_preferred (recorder->display_units_code);
      char units_preferred_cstr[100];
      units_preferred.label_cstr(units_preferred_cstr);
      const char *variable_prefix =lookup_variable_prefix(recorder->variable_code_property);
      for (nat16 stat = 0 ; (stat < STAT_COUNT) && (statistic_label_table[stat]); stat++)
      {  nat32  element = (1 << stat);
         nat32 desired_descriptive_summary_elements_to_outpu =get_desired_descriptive_summary_elements_to_output();
         bool output_this_element =
            (desired_descriptive_summary_elements_to_outpu == STAT_ALL_bits)
            ? recorder->desired_descriptive_summary_elements & element
            : element & desired_descriptive_summary_elements_to_outpu;
         if (output_this_element)
         {  const char *statistic_label = (stat == STAT_value_index)
                ? ""
                : statistic_label_table[stat];
            const char *annual_statistic_label =  annual_header
              ? statistic_label_table[recorder->annual_element_aggregation_statistic]
              : 0;
// Keep for debugging
// std::cout << R_format_Inspectors.items.separator
// << variable_prefix << ":"
// << recorder->properties.name_subsection;
// if (annual_statistic_label)
//   std::cout << "_" << annual_statistic_label;
// std::cout
// << ((statistic_label[0] == 0) ? "" : ".")
// << statistic_label
// << "(" << units_preferred_cstr << ")"
// << std::endl;

//            const char *units_preferred = CORN::lookup_units();
            R_stream << '\t'
                     << variable_prefix << ":"
                     << recorder->properties.name_subsection;
            if (annual_statistic_label)
             R_stream  << "_" << annual_statistic_label;
            R_stream << ((statistic_label[0] == 0) ? "" : ".")
                     << statistic_label
                     << "(" << units_preferred_cstr << ")";
         } // desired stat
      }  // each stat
   } FOR_EACH_END(each_recorder)
   R_stream << std::endl; // R_format_Inspectors.finalizer;
   return true;
}
//______________________________________________________________________________
bool  Season_Inspectors::write_R_headers(std::ostream &R_stream) performs_IO_
{  R_stream << "Crop"
            << '\t'
            << "Year(harvest)";
   return Inspectors::write_R_headers(R_stream,false);
}
//_2013-09-13___________________________________________________________________
nat32 Season_Inspectors::write_R(std::ostream &R_stream)     performs_IO_
{  R_stream << "\"" << associated_crop.get_description() << "\"" << '\t';
   return Inspectors::write_R(R_stream);
}
//_2013-09-13___________________________________________________________________
*/





