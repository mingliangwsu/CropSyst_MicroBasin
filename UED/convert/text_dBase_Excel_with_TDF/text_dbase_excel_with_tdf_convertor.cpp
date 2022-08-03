#ifndef __linux__
//140922 I haven't yet tried compiling xlslib in linux
#include "corn/tabular/tabular_excel.h"
#endif
#include "UED/convert/text_dBase_Excel_with_TDF/text_dbase_excel_with_tdf_convertor.h"

#include "corn/spreadsheet/cell_pump/cell_reader_Excel_XLS.h"
#include "common/weather/GEN_DAT_filename.h"
#include "corn/tabular/tabular_text.h"
#include "UED/library/std_codes.h"
#include "UED/library/controls.h"
#include "UED/library/locrec.h"
#include "UED/library/database_file.h"
#include "corn/container/SDF_list.h"
using namespace std;
//______________________________________________________________________________
Text_dBase_Excel_with_TDF_convertor::Text_dBase_Excel_with_TDF_convertor
(Convertor_arguments &arguments_)                                                //170328
: Tabular_file_with_TDF_convertor(arguments_)                                    //170328
, cell_reader(0)                                                                 //011013
, current_sheet_name("")                                                         //011013
{}
//______________________________________________________________________________
CORN::Tabular_file *Text_dBase_Excel_with_TDF_convertor::provide_tabular_file
(Year &file_year)
{

//was debug only Tabular_format_text_file *TFT_placeholder_unused = new Tabular_format_text_file;//17037

   if (!tabular_file)                                                            //141008
   {
   CORN::Tabular_file  *provided_tabular_file = 0;
   switch (format.format_file_type_labeled.get())
   {
      case FILE_TYPE_text      :
      case FILE_TYPE_unknown   : // Default to text output (likely to cout)      //141008
      {  // copy the format column widths to give to tabular_file
         column_start .append(0); // index 0 is unused                           //100104
         column_widths.append(0); // index 0 is unused                           //100104
         FOR_EACH_IN(format_column,ED_tabular_file_format::Column                //050411
            ,format.columns_1based,each_format_column)
         {  column_start.append(format_column->start_1based);                    //100104
            column_widths.append(format_column->field_width);                    //050411
         } FOR_EACH_END(each_format_column)                                      //050411
         provided_tabular_file =
            (parameters.target_filename.length())
            ? new CORN::Tabular_text_file
               (parameters.target_filename
               ,arguments.is_import_mode()                                       //171120
                ? std::ios::in
                : std::ios::out
               ,false
               ,format                                                           //161013
               ,true // Not sure if I need to record data positions (it originally did, I think so)
                        )
            :  // If there is no filename we must be exporting (writing to cout)
               new CORN::Tabular_text_file                                       //141009
               (&std::cout
               ,format                                                           //161013
               ,false); // I currently dont need to record_data_positions
      }
      break;
      case FILE_TYPE_dBase     :
      break;
//NYI      case FILE_TYPE_lotus_123 :
//NYI                tabular_fie = new CORN_tabular_dBase_file
//NYI      break;
      #ifndef __linux__
      //140922 I haven't yet tried compiling xlslib in linux
      case FILE_TYPE_Excel     :
      {
         bool import_mode = (parameters.operation == "import");
         if (import_mode)                                                        //101127
            cell_reader = new Cell_reader_Excel_XLS(parameters.target_filename); //110828_100113
         else                                                                    //101127
            provided_tabular_file = new CORN::Tabular_file_Excel                 //061018
               (parameters.target_filename
               ,true // for now  keep_read_records_in_memory but probably could do without it
               ,std::ios::out                                                    //130402
            ,format);

#ifdef OBSOLETE
But dont delete, I may  eventually implement this because may need to
use COM to read new 2007 Excel.

Currently not using Tabular_file_text because
it is based on Excel_workbook, with implements
the whole workbook and keeps it in memory.
Cell reader is much more lightweight.

#endif
      } break;
      #endif
//      case XML       :
//NYI                provided_tabular_file = new CORN_XML_file
//      break;

   }
   if (!provided_tabular_file && !cell_reader)                                   //070307
   {  cerr << "Unable to determine the file type or open a data source for the file:"
           << parameters.target_filename.c_str() << endl;
      press_return_before_exit = true;
   }
   tabular_file = provided_tabular_file;                                         //101127
   }
   return tabular_file;                                                          //141008
}
//_provide_tabular_file________________________________________________________/
nat32  Text_dBase_Excel_with_TDF_convertor::perform_import()
{  nat32  status = Tabular_file_with_TDF_convertor::perform_import();
   if ((status == EXIT_FAILURE) && cell_reader)
   {  // We must make two passes of a spreadsheet because
                  // cells with header information
                  // (particularly date and geolocation data) are not necessarily
                  // stored first in the the workbook or spreadsheet
      importing_metadata = true;                                                 //100124
      cell_reader->read(*this);
      importing_metadata = false;                                                //100124
      cell_reader->read(*this);
      commit_detail_line_record_if_new_row_encountered(0); // Need to make sure we process the last detail line
      status =  EXIT_SUCCESS;  // actually, I should get status from read()
   }
   return status;
}
//_perform_import______________________________________________________________/
bool Text_dBase_Excel_with_TDF_convertor
::commit_detail_line_record_if_new_row_encountered(nat32 cell_row)
{  bool commited = false;
   if (cell_row != current_sheet_row)  // not necessarily greater than because resets to 1 if a new sheet is encountered
   {  //the row is larger than the current row number
            // indicating we have read all the data on the row so we can
            //set the curr_detail_line_values to the UED file
      if (detail_line_data_record)
      {  import_data_line(*detail_line_data_record,current_sheet_year);
         delete detail_line_data_record;
         detail_line_data_record = 0;
         commited = true;
      }
      current_sheet_row = cell_row;
   }
   return commited;
}
//_commit_detail_line_record_if_new_row_encountered_________________2010-01-16_/
void Text_dBase_Excel_with_TDF_convertor::recognize_current_sheet_name(const std::string &encountered_sheet_name)             modification_
{
   current_sheet_name.assign(encountered_sheet_name);
               // Also clear current date timestamps
   current_sheet_year =0;        // Somehow I will need to compose
   current_sheet_month =0 ;       // detail line dates
   current_sheet_day_of_month =0;
   current_sheet_day_of_year =0;
   commit_detail_line_record_if_new_row_encountered(0);
   current_sheet_row=0;

   if (header_identified_geolocation)
   {  std::string station_ID_or_name(header_identified_geolocation->get_station_ID_code());
      if (!station_ID_or_name.length())
         if (header_identified_geolocation->has_station_name())
            station_ID_or_name.assign(header_identified_geolocation->get_station_name());
      bool station_added_now;
      UED::Database_file_indexed *ued_file = provide_UED_file();
      ued_file->know_geolocation(*header_identified_geolocation);
   }
}
//_recognize_current_sheet_name_____________________________________2010-01-13_/
void Text_dBase_Excel_with_TDF_convertor::recognize_current_sheet_index
(nat16 current_sheet_index)                                        modification_
{

               // Not yet needed?

}
//_recognize_current_sheet_index____________________________________2010-09-22_/
bool Text_dBase_Excel_with_TDF_convertor::assign_numeric_metadata
(Cell_numeric *cell)                                               modification_
// not const because receiver may modify self with
{  bool used = true;
   nat32 cell_row_1_based = cell->get_row()+1;
   nat32 cell_col_1_based = cell->get_col()+1;

   // scan the headers fields for the cell coordinate, if the cell is a header value, then read set the header
   // Currently no need to scan the column headers but eventually may want to handle variable ordered columns
   // scan the columns if the cell is a data column and the row is detail lines
   // For Excel it is valid to assume cells are provided in row major order
   const ED_tabular_file_format::Metadata_field *metadata_field = format.find_metadata_field(current_sheet_name,cell_row_1_based,cell_col_1_based);

   if (metadata_field)
   {
      // Currently the data type for header fields that are numeric are assumed to be
      // float,  however, for Excel cells, the data type could be float or integer
      // We try integer first then try float
      /*
      switch (metadata_field->mode)
      {  case  DT_float32: case DT_float64:
            used = set_imported_float_metadata(*metadata_field,cell->get_float32());
         break;
         case DT_nat8 : case DT_nat16 : case DT_nat32 : case DT_int8 : case DT_int16 : case DT_int32
            used = set_imported_integer_metadata(*metadata_field,cell->get_int32());
         break;
         default : used = false; break;
      }
      */
         used =  set_imported_integer_metadata(*metadata_field,cell->get_int32());
         if (!used)
            used = set_imported_float_metadata(*metadata_field,cell->get_float32(),cell_reader->dates_based_1904);
   }
   // if cell->row is within column header rows
         // {  I could compose column header caption to look for columns if the format allows free ordering of columns
         //    Could also do units conversion if the column header units label does not match the vaue in the TDF
         //    but I am not going to implement these now, requiring constant fixed column layouts
         // } else

   return used;
}
//_assign_numeric_metadata__________________________________________2010-01-13_/
bool Text_dBase_Excel_with_TDF_convertor::assign_numeric_detail (Cell_numeric *cell) modification_ // not const because receiver may modify self with
{  bool used = true;
   nat32 cell_row_1_based = cell->get_row()+1;
   commit_detail_line_record_if_new_row_encountered(cell_row_1_based);
   nat32  actual_detail_line_start_row_1_based = format.detail_lines_delineation.start_row_1_based;
   // WARNING currently simply assuming the start_row_1_base is relative to the top of the of the worksheet
   // (assuming no begin marker etc.)
   if (cell_row_1_based >=actual_detail_line_start_row_1_based)
   {  Delineated_data_record &detail_data_rec = provide_detail_line_data_record();
      detail_data_rec.set_numeric(current_sheet_name,*cell,cell_reader->dates_based_1904);
   } else used=false; // if we are at a detail line row
   return used;
}
//_assign_numeric_detail____________________________________________2010-01-13_/
bool Text_dBase_Excel_with_TDF_convertor::take_numeric
(Cell_numeric *cell)                                               modification_
{  bool taken = (importing_metadata)
      ? assign_numeric_metadata(cell)
      : assign_numeric_detail(cell);
   delete cell; // delete because it was given and we dont need it anymore
   return true; // we took the cell and either used or deleted it
}
//_take_numeric_____________________________________________________2010-01-13_/
bool Text_dBase_Excel_with_TDF_convertor::assign_textual_metadata
(Cell_textual *cell)                                               modification_
{  bool used = true;
   std::string value;     // WARNING currently only handling ASCII
   cell->get_string(value);    // Currently TDF and UED only handle 8bit strings
   nat32 cell_row_1_based = cell->get_row()+1;
   nat32 cell_col_1_based = cell->get_col()+1;
   // scan the headers fields for the cell coordinate, if the cell is a header value, then read set the header
   // Currently no need to scan the column headers but eventually may want to handle variable ordered columns
   // scan the columns if the cell is a data column and the row is detail lines
   // For Excel it is valid to assume cells are provided in row major order
   const ED_tabular_file_format::Metadata_field *metadata_field
      = format.find_metadata_field(current_sheet_name,cell_row_1_based,cell_col_1_based);
   if (metadata_field)
      used = set_imported_textual_metadata(*metadata_field,value);
   // if cell->row is within column header rows
   // {  I could compose column header caption to look for columns if the format allows free ordering of columns
   // Could also do units conversion if the column header units label does not match the vaue in the TDF
   // but I am not going to implement these now, requiring constant fixed column layouts
   // }
   return used;
}
//_assign_textual_metadata__________________________________________2010-01-13_/
bool Text_dBase_Excel_with_TDF_convertor::assign_textual_detail
(Cell_textual *cell)                                                assignation_
{  bool used = false;
   std::string value;
   cell->get_string(value);    // Currently TDF and UED only handle 8bit strings
   nat32 cell_row_1_based = cell->get_row()+1;
   commit_detail_line_record_if_new_row_encountered(cell_row_1_based);
   // Scan the headers fields for the cell coordinate, if the cell is a header value, then read set the header
   // Currently no need to scan the column headers but eventually may want to handle variable ordered columns
   // scan the columns if the cell is a data column and the row is detail lines
   // For Excel it is valid to assume cells are provided in row major order
   nat32  actual_detail_line_start_row_1_based
      = format.detail_lines_delineation.start_row_1_based;
   // WARNING currently simply assuming the start_row_1_base is relative to the top of the of the worksheet
   // (assuming no begin marker etc.)
   if (cell_row_1_based >=actual_detail_line_start_row_1_based)
   {  Delineated_data_record &detail_data_rec=provide_detail_line_data_record();
      detail_data_rec.set_textual(current_sheet_name,*cell);
      used = true;
   }
   return used;
}
//_assign_textual_detail____________________________________________2010-01-13_/
bool Text_dBase_Excel_with_TDF_convertor::take_textual
(Cell_textual *cell)                                               modification_
{  bool taken = (importing_metadata)
      ? assign_textual_metadata (cell)
      : assign_textual_detail   (cell);
   delete cell; // delete because it was given and we dont need it anymore
   return true; // we took the cell and either used or deleted it
}
//_take_textual________________________________________________________________/
nat32  Text_dBase_Excel_with_TDF_convertor::export_metadata_fields()
{  nat32 metadata_fields = 0;
   #ifndef __linux__
   //140922 I haven't yet tried compiling xlslib in linux
   CORN::Tabular_file_Excel *tabular_Excel =
      dynamic_cast<CORN::Tabular_file_Excel *>(tabular_file);
   if (tabular_Excel)
   {  int last_header_row = 0;
      CORN::Workbook &workbook = tabular_Excel->get_workbook();
      CORN::Workbook::Sheet *sheet = workbook.provide_sheet("Sheet 1");
      FOR_EACH_IN(metadata_field                                                 //100107
         ,ED_tabular_file_format::Metadata_field
         ,format.metadata_fields_1based,each_header)
      {  // Write the caption
         // WARNING may need to offset the row to the to after the start data marker  100111
         CORN::Workbook::Sheet *sheet = workbook.provide_sheet(metadata_field->worksheet);
         if (sheet)
         {  size_t caption_length =  metadata_field->caption.length();
            if (caption_length)
            {  sheet->set_cell_label(metadata_field->caption_col,metadata_field->caption_row,metadata_field->caption);
               last_header_row = std::max<uint16>(last_header_row,metadata_field->caption_row);
            }
            // Write the value                                                   //100111
            switch (metadata_field->field_data_labeled.get())
            {  case ED_tabular_file_format::Metadata_field::FD_static_text :
               {  sheet->set_cell_label(metadata_field->col_num_not_pos-1,metadata_field->row_num-1,metadata_field->static_text);
               } break;
               case ED_tabular_file_format::Metadata_field::FD_UED_general_comment :
               {  // get from UED database description record with database_comment_index
                  CORN::Text_list comments;
                  nat16 comment_count = UED_file->get_comments(comments);
                  CORN::Item_string /*180119 Text_list::Item*/ *primary = dynamic_cast<CORN::Item_string /*180119 Text_list::Item*/ *>(comments.get_at(0));
                  if (primary)
                     sheet->set_cell_label(metadata_field->col_num_not_pos-1,metadata_field->row_num-1,*primary);
               } break;
               case ED_tabular_file_format::Metadata_field::FD_UED_database_description :
               {  // get from UED database description record with database_description_index
                  CORN::Text_list descriptions;
                  nat32 description_count = UED_file->get_descriptions(descriptions);
                  CORN::Item_string /*180119 Text_list::Item*/ *primary = dynamic_cast<CORN::Item_string /*180119 Text_list::Item*/ *>(descriptions.get_at(0));
                  if (primary)
                     sheet->set_cell_label(metadata_field->col_num_not_pos-1,metadata_field->row_num-1,*primary);
               } break;
               case ED_tabular_file_format::Metadata_field::FD_UED_generating_application :
               {  // NYI get from UED generating application record
                  const UED::Generating_application_record *gen_app = UED_file->get_generating_application_record();
                  if (gen_app)
                  {  char buffer[10];
                     std::string gen_app_text(gen_app->get_description());
                     gen_app_text.append(" ");
                     //gen_app_text.append(itoa(gen_app->get_version(),buffer,10));
                     //gen_app_text.append(".");
                     gen_app_text.append(itoa(gen_app->get_major(),buffer,10));
                     gen_app_text.append(".");
                     gen_app_text.append(itoa(gen_app->get_minor(),buffer,10));
                     sheet->set_cell_label(metadata_field->col_num_not_pos-1,metadata_field->row_num-1,gen_app_text);
                  }
               } break;
               case ED_tabular_file_format::Metadata_field::FD_UED_location :
               {  const UED::Geolocation_record  *geoloc_rec = UED_file->get_geolocation_record_immutable();
                  if (geoloc_rec)
                  {  char value_buffer[50]; value_buffer[0] = 0;
                     std::string value_buffer_string;
                     switch (metadata_field->location_var_labeled.get())
                     {  case ED_tabular_file_format::Metadata_field::LOC_VAR_station_ID                : sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_station_ID_code());                                         break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_latitude_decimal_degrees  : sheet->set_cell_number   (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,(float64)geoloc_rec->get_latitude_dec_deg(),  metadata_field->precision);   break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_latitude_deg_min_sec      :
                        {  geoloc_rec->decimal_degrees_to_DMS_string(geoloc_rec->get_latitude_dec_deg(),false,metadata_field->precision,value_buffer_string);
                           sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,value_buffer_string);
                        } break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_longitude_decimal_degrees : sheet->set_cell_number   (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,(float64)geoloc_rec->get_longitude_dec_deg(), metadata_field->precision);   break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_longitude_deg_min_sec     :
                        {  geoloc_rec->decimal_degrees_to_DMS_string(geoloc_rec->get_longitude_dec_deg(),true,metadata_field->precision,value_buffer_string);
                           sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,value_buffer_string);
                        } break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_elevation_meters          : sheet->set_cell_number   (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,(float64)geoloc_rec->get_elevation(), metadata_field->precision);           break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_elevation_feet            : sheet->set_cell_number   (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,(float64)m_to_foot(geoloc_rec->get_elevation()),metadata_field->precision); break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_country_name              : sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_country_name());                                           break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_state_name                : sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_state_name());                                             break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_county_name               : sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_county_name());                                            break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_description               : break; //NYI
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_station_name              : sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_station_name());                                          break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_station_number            : sheet->set_cell_number   (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_station_number(),0);                                         break;
                        case ED_tabular_file_format::Metadata_field::LOC_VAR_comment                   : sheet->set_cell_label    (metadata_field->col_num_not_pos-1,metadata_field->row_num-1,geoloc_rec->get_comment());                                                break;
                     } // switch
                  } // if
               } break;
               case ED_tabular_file_format::Metadata_field::FD_UED_scalar_data :
               {
            // NYI,  This option is if there is a scalar record in the UED file we want to output
            // I dont currently have any UED files with scalar record except CropSyst soil outputs with number of layers.
            // Here I would scan (read_next_record) the UED file for matching UED_scalar_record_code, and UED_scalar_variable_code
            // convert the value units to desired UED_scalar_units_code_enum
                  //NYI sheet->set_cell_label(metadata_field->col,metadata_field->row,"N.Y.I");
               } break;
            } // switch field_data_labeled
         } //if sheet
         last_header_row = max<uint16>(last_header_row,metadata_field->row_num);
         metadata_fields++;
      } FOR_EACH_END(each_header)
   } else // not excel
   #endif
       metadata_fields = Tabular_file_with_TDF_convertor::export_metadata_fields(); // probably text file which is handled by superclass
   return metadata_fields;
}
//_export_metadata_fields___________________________________________2011-12-12_/
nat32  Text_dBase_Excel_with_TDF_convertor::export_column_headers()
{
   nat32  exported_col_header_rows = 0;
   #ifndef __linux__
   //140922 I haven't yet tried compiling xlslib in linux

   CORN::Tabular_file_Excel *tabular_Excel = dynamic_cast<CORN::Tabular_file_Excel *>(tabular_file);
   if (tabular_Excel)
   {  CORN::Workbook &workbook = tabular_Excel->get_workbook();

       //   CORN::SDF_List header_rows[20];
          // Allocate a text list for each row (format.column_headers_delineation.rows)
                // HACK: 20 is an arbitrary number should use dynamic allocation with respect to format.column_headers_delineation.rows.
                // For each row there will be one item corresponding to the portion of the caption of that column on that row.
       //      tabular_file->goto_raw_line(format.column_headers_delineation.start_row_1_based);

      FOR_EACH_IN(column,ED_tabular_file_format::Column,format.columns_1based,each_col_desc);
      {  std::string sheet_name(column->sheet); if (!sheet_name.length()) sheet_name.assign("Sheet 1");
         CORN::Workbook::Sheet *sheet = workbook.provide_sheet(sheet_name);
         if (sheet)
         {  SDF_List caption_SDF_list(column->get_caption_SDF());
            for (int8 row_idx = format.column_headers_delineation.rows-1
                ;row_idx >=0
                ;row_idx--)
            {   // For each column header, take the description (caption) and split the text into words
                // and distribute the words two the number of rows allocated for column header.
                // I.e.  If format.column_headers_delineation.rows is 4 and the
                // column header is  "The caption"
                // 'caption' will be appended to the forth row text list,
                // 'The' to the third, and the first and second will have appended empty string.
                // If the caption is "This is a long caption"
                // the text will be distributed as 'This is' 'a' 'long' 'caption'.
                // The caption in the TDF file can have a '_' to prevent word wrap'
                // If the caption is long the TDF caption may
                // indicate the line brakes using system data format for the caption string.
                CORN::Item_string /*180119 Text_list::Item*/ *caption_fragment = dynamic_cast<CORN::Item_string /*180119 Text_list::Item*/ *>
                //171125 SDF_List::Item *caption_fragment = (SDF_List::Item *);
                  (caption_SDF_list.pop_at_tail());
                if (!caption_fragment) caption_fragment = new CORN::Item_string(""); //180119 SDF_List::Item("");
                if (row_idx == 0)
                {  // In this case the caption has more rows than number of rows reserved for column header captions
                   // So will put the remaining caption text on the top line.
                   // (Often occurs when the format designates only one line for column header captions).
                   for (Item *remaining_caption_fragment = dynamic_cast<Item *>(caption_SDF_list.pop_at_tail())
                       ;remaining_caption_fragment
                       ;remaining_caption_fragment = dynamic_cast<Item *>(caption_SDF_list.pop_at_tail()))
                   {
                       //18-82- std::string caption_fragment_value(remaining_caption_fragment->get_key());
                       std::string caption_fragment_value; (remaining_caption_fragment->key_string(caption_fragment_value)); //18-82- 
                       caption_fragment_value.append(" ");                       //131018
                       caption_fragment->append_to_string(caption_fragment_value); //180119
                       //180119 caption_fragment_value.append(*caption_fragment);         //171125
                       //171125 caption_fragment_value.append(caption_fragment->value);   //131018
                       caption_fragment->assign(caption_fragment_value);   //131018
                       //171125 caption_fragment->value.assign(caption_fragment_value);   //131018
                       delete remaining_caption_fragment;
                   }
                }
                std::string cell_label; caption_fragment.key_string(cell_label); //180820
                sheet->set_cell_label(column->start_1based-1,format.column_headers_delineation.start_row_1_based+row_idx-1
                  ,cell_label
                  //180820 ,caption_fragment->get_key()
                  );
             } // for row_idx
          } //if sheet
       } FOR_EACH_END(each_col_desc)
       if (format.column_headers_delineation.units_rows)                         //070307
       {  // Output column header units description
         uint16 column_header_number = 1;  // column numbers are 1 based         //050902
         int curr_col_number = 1; // 1 based
         FOR_EACH_IN(column,ED_tabular_file_format::Column,format.columns_1based,each_col_desc)
         {  std::string sheet_name(column->sheet); if (!sheet_name.length()) sheet_name.assign("Sheet 1");
            CORN::Workbook::Sheet *sheet = workbook.provide_sheet(sheet_name);
            if (sheet)
            {  std::string units = column->get_units_caption();  // preferred units description if specified
               if (!units.length() && column->get_units_code())  // if not specified derived the units description of units_code
                   units = UED_file->get_units_description(column->get_units_code() ,true);
               UED::Variable_code_cowl                                           //170327
                  &smart_var_code = column->smart_variable_code;
   //             if (format.column_headers_delineation.delimit_mode_labeled.get() == Delineation_layout::DELIMIT_fixed_width)   //090712
   //             {  // For fixed column widths delimit mode we set the width of the string to the width of the
   //                // It is possible that the TDF description with fixed column widths, skips character columns and/or has white space.
   //                // we need to account for these                             //100104
   //                tabular_file->goto_field_column(curr_col_number);
   //             }
   //             if (delimitor && curr_col_number > 1)                          //090712
   //                tabular_file->write_delimitor_string(delimitor);
               if (smart_var_code.is_layered() && column->spread_columns)
                  for (int layer = 0; layer < column->spread_columns; layer++)
                     sheet->set_cell_label(column->start_1based-1,format.column_headers_delineation.start_row_1_based-1 + format.column_headers_delineation.units_row_offset,units);
               else
                  sheet->set_cell_label(column->start_1based-1,format.column_headers_delineation.start_row_1_based-1 + format.column_headers_delineation.units_row_offset,units);
                // Note the format may reserve multiple rows for units currently only using a single row
               curr_col_number += 1;                                             //100104
            } // if sheet
         } FOR_EACH_END(each_col_desc)
      } // if units rows
      exported_col_header_rows = format.column_headers_delineation.rows;
   } else // not Excel spreadsheet
   #endif
      exported_col_header_rows = Tabular_file_with_TDF_convertor::export_column_headers(); // probably text file which is handled by superclass
      // Need to check that exported_col_header_rows is correct
   return exported_col_header_rows;                                              //090709
}
//_2011-12-12___________________________________________________________________

