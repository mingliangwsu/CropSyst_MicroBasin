#error 160516 This class is obsolete.  It has been replaced with tabular_file_with_TDF_convertor
/*
This utility exports UED files to a specified format.

Inputs:
   UED database file
   format file

Outputs
   formatted file
*/
#include <C:/dev/UED/convert/text_dBase_Excel_with_TDF/export.h>
#include <C:/dev/UED/convert/text_dBase_Excel_with_TDF/export_column.h>
#include <ued/library/std_codes.h>
#include <UED/library/controls.h>
#include <corn/math/statistical/stats.h>
#include <fstream.h>
#include <corn/std/std_iomanip.h>
#include <corn/data_source/vv_file.h>
#include <corn/container/sdf_list.h>

#define LABEL_statistic "statistic"
#define LABEL_column             "column"
//______________________________________________________________________________
UED_export_database::UED_export_database
(const char *database_filename
    ,ED_tabular_file_format &_format // caller instanciates                      //050404
)
:UED_imp_exp_database(database_filename,true,_format /*format_filename*/)
,export_tuples()
{}
//______________________________________________________________________________
// DECLARE_CONTAINER_ENUMERATED_SECTION(UED_export_column,UED_export_column_VV,0);
void UED_export_database::initialize()
{
  UED_imp_exp_database::initialize();                                            //020512
    start_date_time.set_datetime64(get_earliest_date_time());
    end_date_time.set_datetime64(get_latest_date_time());

   format.metadata_fields_1based/*101018header_fields_1based*/.sort();
};
//______________________________________________________________________________
UED_export_column *UED_export_database::get_export_column(int16 column_number)
{
    UED_export_column *last_matching_data_set_column =0;
    FOR_EACH_IN(column,UED_export_column,export_columns,each_column)
       {  if (column->TFFC_layout.spread_columns && (column->check_obs_number /*index*/ <= column_number))
             last_matching_data_set_column = column;
          if (column->check_obs_number /*index*/ == column_number)
             return column;
       } FOR_EACH_END(each_column);
     return last_matching_data_set_column;
};
//______________________________________________________________________________
#ifdef OLD_STANDALONE
//050901  I am trying now to use   CORN tabular derived classes
//so I can use the new Datasource Data_record model
//Don't delete this until I get Text_dBase_Excel_with_TDF_convertor working

/*040928*/  void UED_export_database::output_header_fields()
/*_______*/ {
            // NYI
            /*_______*/   // currently just write blank lines.
/*_______*/ };
//______________________________________________________________________________
#endif
void UED_export_database::setup_export_columns()
{
   // Now create additional columns for layer variables if column have been reserved for layers
   FOR_EACH_IN(column,ED_tabular_file_format::Column,format.columns_1based,each_col_desc)
   {
      UED_smart_variable_code &smart_var_code = column->smart_variable_code;
      if (smart_var_code.is_layered() && column->spread_columns)
          for (int layer = 0; layer < column->spread_columns; layer++)
            export_columns.append(new UED_export_column(*column));
      else
         export_columns.append(new UED_export_column(*column));
    } FOR_EACH_END(each_col_desc);
};
//_2004-09-28___________________________________________________________________
#ifdef OLD_STANDALONE
//050901  I am trying now to use   CORN tabular derived classes
//so I can use the new Datasource Data_record model
//Don't delete this until I get Text_dBase_Excel_with_TDF_convertor working

/*040928_*/ void UED_export_database::output_column_header_row(int CH_row_number, int col_number,int rows, const char *description_SDF,ED_tabular_file_format::Column &column)
/*_______*/ {
/*
Column headers may have 1 or more rows reserved to fit the column
header description text.  The descriptions may have less than, more than
or equal number of strings

Suppose there are 5 reserved rows
    cases:
ri  equal   ssi  |less    ssi|more
                 |           |
0   string0  0   |        -2 |string0
1   string1  1   |        -1 |string1
2   string2  2   |string1  0 |string2
3   string3  3   |string2  1 |string3  string4


 sss - rows + ri = ssi
  3  -  5   + 0  = -2
  3  -  5   + 2  =  0
*/
/*_______*/    // description is in SDF format, break it appart
/*_______*/    // extracting the row index'th string
/*050902_*/    int CH_row_index = CH_row_number -1;   // row within the column header environment not in the file
/*_______*/    SDF_List col_header_SDF(description_SDF);
/*_______*/    int sub_strings =  col_header_SDF.count();
/*_______*/    int substr_index = CH_row_index;     // if (sub_strings == rows)
/*_______*/    if (sub_strings < rows) substr_index = sub_strings - rows + CH_row_index;
/*_______*/    Ustring row_substring;

/*_______*/    if (substr_index >= 0)
/*_______*/    {
/*_______*/    if (CH_row_number >= rows) // there are more strings than rows, so just concatenate the remaining strings
/*_______*/    {
///*_______*/       for (int i = CH_row_index; i <= sub_strings; i++)
/////*050906_*/       substr_index = CH_row_index;
/*050906_*/       while (substr_index < sub_strings)
/*_______*/       {
///*050906_*/          if (sub_strings < rows) substr_index = sub_strings - rows + CH_row_index;
/*_______*/          SDF_List::Item *ith_item = (SDF_List::Item *)col_header_SDF.get_at(substr_index);
/*050906_*/          if (ith_item)
/*050906_*/          {  ith_item->key_string(row_substring); //180820
/*_______*/             //180820 row_substring.append(ith_item->get_key());
/*_______*/             if (substr_index != sub_strings-1 )
/*_______*/                row_substring.append(" "); // separate appended item by space
/*050906_*/          };
/*050906_*/          substr_index ++;
/*_______*/       };
/*_______*/    }
/*_______*/    else   // actual row index is row index
/*_______*/    {
/*_______*/       SDF_List::Item *ith_item = (SDF_List::Item *)col_header_SDF.get_at(substr_index);
/*_______*/       if (ith_item)
/*_______*/          row_substring.assign(ith_item->get_key());
/*_______*/    };
/*_______*/    }; // else, it is just a blank cell
/*_______*/    const char *delimitor = col_number == 1 ? "" : format.column_headers_delineation.get_delimitor();
/*_______*/    output_file->export_string(row_substring ,column,format.column_headers_delineation.text_quote_mode_labeled.get(),delimitor);
/*_______*/ };
#endif
//______________________________________________________________________________
#ifdef OLD_STANDALONE
//050901  I am trying now to use   CORN tabular derived classes
//so I can use the new Datasource Data_record model
//Don't delete this until I get Text_dBase_Excel_with_TDF_convertor working

/*040928_*/ void UED_export_database::output_column_headers()
/*_______*/ {
/*_______*/     for (int CH_row_number = 1; CH_row_number <= format.column_headers_delineation.rows; CH_row_number++)
/*_______*/     {
/*_______*/        output_file->goto_row(format.column_headers_delineation.start_row_1_based+CH_row_number-1);
/*050902_*/       int column_number = 1;
/*_______*/        FOR_EACH_IN(column,ED_tabular_file_format::Column,format.columns_1based,each_col_desc);
/*_______*/        {
/*_______*/           UED_smart_variable_code &smart_var_code = column->smart_variable_code;
/*_______*/           if (smart_var_code.get() || column->record_date)
/*_______*/           {
/*______*/
                        // The column may have either a fixed description and a variable code
                        // if description is specified it will have presidence over the variable code
                        // definition description
/*_______*/              Ustring description(column->caption/*description*/);
/*_______*/              if (!description.length())
                           description = get_variable_description(smart_var_code.get() );  // Eventually use the abbreviation (caption)
/*_______*/              if (smart_var_code.is_layered() && column->spread_columns/*101018columns*/ > 1)
/*_______*/              {
/*_______*/                 for (int layer = 0; layer < column->spread_columns/*101018columns*/; layer++)
/*_______*/                 {  Ustring enumerated_description(description);
/*_______*/                    enumerated_description.append(",\"");
/*_______*/                    char layer_str[10];
/*_______*/                    enumerated_description.append(itoa(layer,layer_str,10));
/*_______*/                    enumerated_description.append("\"");
/*_______*/                    output_column_header_row(CH_row_number,column_number,format.column_headers_delineation.rows,enumerated_description.c_str(),*column);
/*_______*/                 };
/*_______*/              }
/*_______*/              else
/*_______*/                output_column_header_row(CH_row_number,column_number,format.column_headers_delineation.rows,description.c_str(),*column);
///*_______*/              output_file->export_string(description ,*column);
/*_______*/           };
/*050902_*/          column_number += 1;
/*_______*/        } FOR_EACH_END(each_col_desc);
/*_______*/     };
/*______*/
/*_______*/     // Output column header units description
/*050902_*/    uint16 column_header_number = 1;  // column numbers are 1 based
/*_______*/     output_file->goto_row(format.column_headers_delineation.start_row_1_based + format.column_headers_delineation.units_row_offset); // rows);
/*_______*/     FOR_EACH_IN(column,ED_tabular_file_format::Column,format.columns_1based,each_col_desc);
/*_______*/     {
/*_______*/           Ustring units = column->units_caption/*units_description*/;  // perferred units description if specified
/*_______*/           if (!units.length() && column->units.get() /*101018 smart_units_code_enum.get()*/)  // if not specified derived the units description of units_code
/*_______*/              units =
                           column->get_units_caption(); 
                           //101018get_units_caption/*units_description*/(column->smart_units_code_enum.get(),true);
/*_______*/           UED_smart_variable_code &smart_var_code = column->smart_variable_code;
/*050902*/           const char *delimitor = (column_header_number++ == 1)?  "" :format.column_headers_delineation.get_delimitor() ;  // Don't prepend delimitor for column 0
/*_______*/              if (smart_var_code.is_layered() && column->spread_columns)
/*_______*/              {
/*_______*/                 for (int layer = 0; layer < column->spread_columns; layer++)
/*_______*/                 {
/*050901*/                    output_file->export_string(units ,*column,format.column_headers_delineation.text_quote_mode_labeled.get(),delimitor);  // Note the format may reserve multiple rows for units currently only using a single row
/*_______*/                 };
/*_______*/              }
/*_______*/              else
/*_______*/              output_file->export_string(units ,*column,format.column_headers_delineation.text_quote_mode_labeled.get(),delimitor);  // Note the format may reserve multiple rows for units currently only using a single row
/*_______*/        } FOR_EACH_END(each_col_desc);
/*_______*/ };
#endif
//______________________________________________________________________________
/*_______*/ void UED_export_database::tuplize_database
/*070621_*/ (CORN::datetime64 filter_date_time_low,CORN::datetime64 filter_date_time_high)
/*_______*/ {
/*_______*/     goto_BOF();
/*_______*/     for (UED_data_record * from_record = (UED_data_record *)goto_next_data_record()
/*_______*/           ; from_record
/*_______*/           ; from_record = (UED_data_record *)goto_next_data_record())
/*_______*/     {
/*_______*/        bool column_exported = false;
/*_______*/        //      Year from_rec_year = from_record->get_date_time().get_year();

//if ((from_record->get_date_time().get_year() == 1969))
//cout << "reached" << endl;

#ifdef OBSOLETE
// We can't base this filter on the time stamp because it is often the
// the start of the year, we need to check the tuple date of the individual item
// now only checking out output.

/*040927*/        Date_time_64 rec_time_stamp(from_record->get_time_stamp());
/*_______*/        if ((rec_time_stamp.temporal_compare(start_date_time) >=0 )
/*_______*/         && (rec_time_stamp.temporal_compare(end_date_time) <= 0))
#endif
/*_______*/        {
/*_______*/           int export_column_number = 0;
/*_______*/           FOR_EACH_IN(export_column,UED_export_column,export_columns,each_col_desc)
/*_______*/           {
/*_______*/              // Try each column to see if it can export the data recordexport_grid,the output file, and the data record to be exported.
/*_______*/              if (export_column->tuplize(export_column_number,*from_record,export_tuples,*this
/*_______*/                ,filter_date_time_low,filter_date_time_high
/*_______*/              ))// Just for convert function
/*_______*/                 column_exported = true;
/*_______*/              export_column_number += 1;
/*_______*/           } FOR_EACH_END(each_col_desc);
/*_______*/        };
/*_______*/     }; // each data record
/*_______*/ };

#ifdef OLD_STANDALONE
//______________________________________________________________________________
//050901  I am trying now to use   CORN tabular derived classes
//so I can use the new Datasource Data_record model
//Don't delete this until I get Text_dBase_Excel_with_TDF_convertor working


/*040829*/ void UED_export_database::write_tuple_column
/*_______*/ ( CORN::Date_time_64 &tuple_date_time
/*040929_*/, float32 value
/*_______*/ , uint16 export_column_number
/*_______*/ , UED_export_column  *export_column
/*_______*/ )
/*_______*/ { // CropSyst will override this to output crop name, growth stage and other text
/*_______*/     {           bool date_or_time_printed = false;
/*050902*/              const char *delimitor = export_column_number ? format.detail_lines_delineation.get_delimitor() : "";  // Don't prepend delimitor for column 0
/*041004_*/             if (export_column->TFFC_layout.record_date)
/*041004_*/             {  // Output the tuples date time
/*041004_*/                date_or_time_printed = true;
/*_______*/                 switch (export_column->TFFC_layout.get_units_code() /*101018 smart_units_code_enum.get()*/ )
/*_______*/                 {
/*_______*/                    // Various date variables
/*_______*/                    case UT_date :
/*040931*/                    {
/*040931*/                          CORN::Date tuple_date; tuple_date.set_datetime64(tuple_date_time.get_datetime64());
/*040931*/                             char date_str_buffer[50];
/*040931*/                             if (export_column->TFFC_layout.units_caption/*units_description*/ == "YYYY/MM/DD(DDD)")
/*040931*/                                tuple_date.format(D_YMD,D_YYYY|D_M|D_lead_zero, '/',true);
/*041004*/                             if (export_column->TFFC_layout.units_caption/*units_description*/ == "YYYY/Mmm/DD(DDD)")
/*041004*/                                tuple_date.format(D_YMD,D_YYYY|D_Mmm|D_lead_zero, '/',true);
/*050907*/                             if (export_column->TFFC_layout.units_caption/*units_description*/ == "YYYYDDD")
/*050907*/                                tuple_date.format(D_YD,D_YYYY|D_lead_zero,0,false);
/*040931*/                          output_file->export_string(tuple_date.text_str(date_str_buffer),export_column->TFFC_layout,format.detail_lines_delineation.text_quote_mode_labeled.get(),delimitor);
/*_______*/                    } break;
/*_______*/                    // NYI case UT_time
/*_______*/                    // NYI case UT_date_time
/*_______*/                    case UT_second:         output_file->export_integer((int16)(tuple_date_time.get_second()),export_column->TFFC_layout,delimitor);  /* date_or_time_printed = true;*/ break;
/*_______*/                    case UT_minute :        output_file->export_integer((int16)(tuple_date_time.get_minute()),export_column->TFFC_layout,delimitor);  /* date_or_time_printed = true;*/ break;
/*_______*/                    case UT_hour:           output_file->export_integer((int16)(tuple_date_time.get_hour()),export_column->TFFC_layout,delimitor);    /* date_or_time_printed = true;*/ break;
/*_______*/                    case UT_day_of_year :   output_file->export_integer((int16)(tuple_date_time.get_DOY()),export_column->TFFC_layout,delimitor);     /* date_or_time_printed = true;*/ break;
/*_______*/                    case UT_year   :
/*_______*/                    {
/*_______*/                       int year = tuple_date_time.get_year();
/*_______*/                       // Handle the case of stupid formats with only 2 year digits
/*_______*/                       if (export_column->TFFC_layout.field_width == 2)
/*_______*/                          year = year % 100;
/*_______*/                       output_file->export_integer((int16)year,export_column->TFFC_layout,delimitor);
//041004 moved above/*_______*/                       date_or_time_printed = true;
/*_______*/                    } break;
/*_______*/                    case UT_day_of_month :  output_file->export_integer((int16)(tuple_date_time.get_DOM()),export_column->TFFC_layout,delimitor);    /* date_or_time_printed = true;*/  break;
/*_______*/                    case UT_month :
/*_______*/                            output_file->export_integer((int16)(tuple_date_time.get_month()),export_column->TFFC_layout,delimitor);  /* date_or_time_printed = true;*/ break;
/*_______*/                 };
/*041004_*/             };
/*_______*/              if (!date_or_time_printed)
/*_______*/              {
/*_______*/                if (export_column->TFFC_layout.smart_variable_code.get())
/*_______*/                {
/*_______*/                    if ( export_column->encountered)
/*040931*/                    {  if (export_column->TFFC_layout.get_units_code()/*101018 smart_units_code_enum.get()*/ == UT_date)
/*040931*/                       {
/*040931*/                          CORN::Date date_value; date_value.set_datetime64(value);
/*040931*/                          if (export_column->TFFC_layout.units_caption/*101018 units_description*/ == "YYYY/MM/DD(DDD)")
/*040931*/                             date_value.format(D_YMD,D_YYYY|D_M|D_lead_zero, '/',true);
/*040931*/                          else if (export_column->TFFC_layout.units_caption/*101018 units_description*/ == "YYYY/MM/DD")
/*040931*/                             date_value.format(D_YMD,D_YYYY|D_M|D_lead_zero, '/',false);
/*040931*/                          else if (export_column->TFFC_layout.units_caption/*101018 units_description*/ == "YYYY/Mmm/DD")
/*040931*/                             date_value.format(D_YMD,D_YYYY|D_Mmm|D_lead_zero, '/',false);
/*040931*/                          else if (export_column->TFFC_layout.units_caption/*101018 units_description*/ == "YYYY/Mmm/DD(DDD)")
/*040931*/                             date_value.format(D_YMD,D_YYYY|D_Mmm|D_lead_zero, '/',true);
/*050907*/                          else if (export_column->TFFC_layout.units_caption/*101018 units_description*/ == "YYYYDDD")
/*050907*/                             date_value.format(D_YD,D_YYYY|D_lead_zero, 0,false);
/*040931*/                          else
/*040931*/                             date_value.format(D_YD,D_YYYY|D_lead_zero,'.',false);
/*040931*/                          output_file->export_string(date_value.c_str(),export_column->TFFC_layout,format.detail_lines_delineation.text_quote_mode_labeled.get(),delimitor);
/*040931*/                       } else
/*_______*/                          output_file->export_float(value,export_column->TFFC_layout,delimitor);
/*040930*/                    } else
/*041013*/                    {
/*041013*/                       if (export_column->TFFC_layout.data_type_labeled.get() == CORN/*::Tabular_column*/::DT_string)
/*041013*/                       {
/*041013*/                          //this could be something like Crop name or growing season or growth stage.
/*041013*/                          //check database for period with matching UED code for this date.
/*041014*/                          Ustring period_description("N/A");
/*041013*/                          const UED_period_record *period_rec = get_period(UED_period_variable_code_option|UED_period_start_date_time_option|UED_period_end_date_time_option,tuple_date_time.get_datetime64()
/*041013*/                                ,0,0,0,export_column->TFFC_layout.smart_variable_code.get());
/*041013*/                          if (period_rec) period_description.assign(period_rec->text);
/*041013*/                          output_file->export_string(period_description,export_column->TFFC_layout,format.detail_lines_delineation.text_quote_mode_labeled.get(),delimitor);
/*041013*/                       } else
/*040930*/                       output_file->export_string("N/A",export_column->TFFC_layout,format.detail_lines_delineation.text_quote_mode_labeled.get(),delimitor);
/*041013*/                    };
/*041013*/                 } else
/*040930*/                       output_file->export_string("N/A",export_column->TFFC_layout,format.detail_lines_delineation.text_quote_mode_labeled.get(),delimitor);
/*_______*/              };
/*040930*/     };
/*_______*/ };

#endif
//______________________________________________________________________________
#ifdef OLD_STANDALONE
//050901  I am trying now to use   CORN tabular derived classes
//so I can use the new Datasource Data_record model
//Don't delete this until I get Text_dBase_Excel_with_TDF_convertor working

/*_______*/ void UED_export_database::write_tuples()
/*_______*/ {
/*_______*/     Bidirectional_list sorted_tuples;
/*_______*/     export_tuples.extract_tuples(sorted_tuples);
//*040929*/     int row_offset = 0;
/*_______*/     // Now write out all the tuples.
/*040929*/     output_file->goto_row(format.detail_lines_delineation.start_row_1_based/*_1*/);
/*_______*/     FOR_EACH_IN(tuple,UED_export_tuple,sorted_tuples,each_tuple)
/*_______*/     {
/*040929*/        if ((tuple->date_time.temporal_compare(start_date_time) >= 0) // Tuple index may generate tuple sets for dates not with in the output
/*040929*/          &&(tuple->date_time.temporal_compare(end_date_time) <= 0))
/*040929*/        {
//040929obs /*_______*/        int16 out_row =  get_row_for_date(tuple->date_time);
///*040929_*/          int16 out_row =  start_row_1 + row_offset;
//040929 now just incrementing the output row/*_______*/           if (out_row >= 0) // May be negative if tuple before starting date
/*_______*/        {
//040929 shouldn't be necessary, just go to next row/*_______*/           output_file->goto_row(out_row);
/*_______*/           int tuple_count = tuple->get_count();
/*_______*/           int export_column_number = 0;
/*_______*/           FOR_EACH_IN(export_column,UED_export_column,export_columns,each_column)
/*_______*/           {
/*_______*/              write_tuple_column(tuple->date_time,tuple->data.get(export_column_number,false )/*090714 get_no_resize(export_column_number )*/,export_column_number,export_column);
//*_______*/              {
//*_______*/              };
/*040929_*/             export_column_number += 1;
/*_______*/           } FOR_EACH_END(each_column);
/*_______*/           output_file->goto_next_row();
/*_______*/        }; // if out_row
/*_______*/        }; // tuple in date range
/*_______*/     } FOR_EACH_END(each_tuple);
/*_______*/ };
#else
/*070305_*/ uint32 UED_export_database::write_tuple_records()
/*_______*/ {
/*_______*/     Bidirectional_list sorted_tuples;
/*_______*/     export_tuples.extract_tuples(sorted_tuples);
/*_______*/     FOR_EACH_IN(tuple,UED_export_tuple,sorted_tuples,each_tuple)
/*_______*/     {
/*_______*/          bind the record to the tuple ddata and set data
/*_______*/     } FOR_EACH_END(each_tuple);
/*_______*/
/*_______*/ };
#endif
//______________________________________________________________________________
void UED_export_database::set_date_ranges
(CORN::datetime64 start_datetime64
,CORN::datetime64 end_datetime64)
{
    start_date_time.set_datetime64(start_datetime64);
    end_date_time.set_datetime64(end_datetime64);
}
//_204-10-03____________________________________________________________________
/*_______*/ void UED_export_database::export_to
/*_______*/ (const char *output_filename)
/*_______*/ {
               std::cout << "generating index" << std::endl;
               // Some format may contain only intermittet output, with no fixed time step
               // I presume that in this case the outputs are daily recording.
               // Warning, this may not be the case, I should come up with
               // some heuristic (or better yet) scan the database
               // to see what kind of time stamps and time step are actually
               // used in the database.
               Units_code limit_time_step_units
               = (format.detail_lines_delineation.time_step_units_enum.get() > 0)
               //050830 obs (format.time_step_units > 0)
               ? format.detail_lines_delineation.time_step_units_enum.get() : UT_day;
//050830               ? format.time_step_units : UT_day;
/*_______*/     export_tuples.setup
/*_______*/     (limit_time_step_units // tuple_time_step    // This is the timestep of the output file detail lines
/*_______*/     ,UT_year   // This is the timestep of this index level
/*_______*/     ,start_date_time.get_year()
/*_______*/     ,end_date_time.get_year() - start_date_time.get_year() + 1 // years
/*_______*/     );
/*_______*/
/*_______*/ // open output file
/*_______*/

#ifdef OLD_STANDALONE
//050901  I am trying now to use   CORN tabular derived classes
//so I can use the new Datasource Data_record model
//Don't delete this until I get Text_dBase_Excel_with_TDF_convertor working
/*_______*/     output_file = 0;

//*_______*/     start_date_time.set_datetime64(i_start_date_time.get_datetime64());
//*_______*/     end_date_time.set_datetime64(i_end_date_time.get_datetime64());
/*_______*/     switch (format.format_file_type_labeled.get())
/*_______*/     {
/*_______*/        case FILE_TYPE_text :
/*_______*/           output_file = new UED_text_export_file(output_filename,format);
/*_______*/        break;
#ifdef NYI
/*______*/
/*_______*/        case Lotus_123
/*_______*/        break;
/*_______*/        case dBase
/*_______*/        break;
#endif
/*_______*/        case FILE_TYPE_Excel :
/*_______*/           output_file = new UED_Excel_export_file(output_filename);
/*_______*/        break;
/*_______*/     };
#endif


   #ifdef NYI
//   060223 continue here
/*_______*///   output the header
/*_______*/    cout << "output headers" << endl;
/*040928_*/    output_header_fields();
#endif
/*040928_*/    setup_export_columns();
   #ifdef NYI
//   060223 continue here

/*_______*/     if (format.column_headers_delineation.start_row_1_based/*050830 column_headers.start_row_1*/) output_column_headers();
   #endif
/*_______*/     //      export_columns.sort();
/*_______*/     // determine the time step (seconds) specified in the format.
#ifdef NOT_CURRENTLY_USED
/*______*/
/*_______*/     CORN_seconds time_step_in_seconds = 1800; // Thirty minutes
/*_______*/     // check the desired time step units conversion
/*_______*/     if ((time_step_units >= UT_1_second) && (time_step_units <= UT_60_seconds))
/*_______*/        time_step_in_seconds =  time_step_units - UT_second;
/*_______*/     if (time_step_units == UT_minute)
/*_______*/        time_step_in_seconds =  60;
/*_______*/     if ((time_step_units >= UT_1_minute) && (time_step_units <= UT_60_minutes))
/*_______*/       time_step_in_seconds =  (time_step_units - UT_minute) * 60;
/*_______*/     if (time_step_units == UT_hour)
/*_______*/       time_step_in_seconds =  3600;
/*_______*/     if ((time_step_units >= UT_1_hour) && (time_step_units <= UT_24_hours))
/*_______*/       time_step_in_seconds =  (time_step_units - UT_hour) * 3600;
/*_______*/     if (time_step_units == UT_day)
/*_______*/       time_step_in_seconds =  86400;
/*_______*/     time_step_in_seconds *= time_step; // Adjust by time step selection
#endif
/*_______*/     //   CORN_grid export_grid(output_filename);
#ifdef OLD_STANDALONE
/*_______*/     output_file->start_data();
#else
// NYI need something equivelent ?
#endif
/*_______*/     std::cout << "tuplizing" << std::endl;
/*040928_*/     tuplize_database(start_date_time.get_datetime64(),end_date_time.get_datetime64());
/*_______*/     std::cout << "writing" << std::endl;
#ifdef OLD_STANDALONE
/*040928_*/    write_tuples();
/*_______*/     std::cout << "closing" << std::endl;
/*_______*/     if (output_file)
/*_______*/     switch (format.format_file_type_labeled.get())
/*_______*/     {
/*_______*/        case FILE_TYPE_text :
/*_______*/        {
//070301              shouldn't need cast to delete
//070301                      UED_text_export_file *text_output_file = (UED_text_export_file *)output_file;
//070301 /*_______*/           delete text_output_file;
/*070301_*/          delete  output_file;
/*_______*/        }break;
#ifdef NYI
/*_______*/        case Lotus_123
/*_______*/        break;
/*_______*/        case dBase
/*_______*/        break;
#endif
/*_______*/        case FILE_TYPE_Excel :
/*_______*/        {
/*_______*/           UED_Excel_export_file *excel_output_file = (UED_Excel_export_file *)output_file;
#ifdef DISABLED
//070622  Not working in Vista Office?
/*_______*/           // freeze pane
/*_______*/           excel_output_file->freeze_pane(1 , format.data_delineation?. start_row_1_based-1 );
#endif
/*_______*/           delete excel_output_file;
/*_______*/        }break;
/*_______*/     };
#else
// NYI need something equivelent ?
/*070205_*/    write_tuple_records();
#endif

//#endif

/*_______*/  };
#ifdef OLD_STANDALONE
// UED_text_export_file----------------------------------------------------------------
void UED_text_export_file::start_data()
{  data_started = true;
}
//______________________________________________________________________________
void UED_text_export_file::export_integer
(int16  value
,const ED_tabular_file_format::Column &column_format
,const char *delimitor)
{
   char value_cstr[20];
   itoa(value,value_cstr,10);
   Ustring padded_value;
   if (column_format.field_width)       //101018
   {
      int value_len = strlen(value_cstr);
      int padding = column_format.field_width - value_len;  //101018
      std::string pads(' ',padding);
      padded_value.append(pads);
      padded_value.append(value_cstr);
   };
   export_string(padded_value,column_format,Delineation_layout::NO_QUOTE,delimitor);
};
//______________________________________________________________________________

void UED_text_export_file::export_float
(  float32  value
,  const ED_tabular_file_format::Column  &column_format
/*050901*/     ,const char *delimitor
)
{
   if ((value > 99999.0) || (value < -99999.0))
      std::cout << "export_float value out of range" << std::endl;


   Ustring unpadded_value(CORN_float32_to_str(value, column_format.get_precision()/*101018precision_16*/));
   int padding = column_format.field_width - unpadded_value.length();
   Ustring padded_value;
   if (column_format.field_width)
   {
      std::string pads(' ',padding);
      padded_value.append(pads);
      padded_value.append(unpadded_value);
   };
   export_string(padded_value,column_format/*.start*/,Delineation_layout::NO_QUOTE,delimitor);
};
//______________________________________________________________________________
void UED_text_export_file::export_date
(const Date &date
,const ED_tabular_file_format::Column  &column_format
,const char *delimitor                                                           //050901
)
{
   Ustring date_text(date.c_str());
   int padding = column_format.field_width - date_text.length();
   if (column_format.field_width)
   {

      Ustring pad(' ',padding);
      date_text.append(pad);
   }
   export_string(date_text,column_format,Delineation_layout::NO_QUOTE,delimitor);

};
//______________________________________________________________________________

void UED_text_export_file::export_string
(const Ustring &str
,  const ED_tabular_file_format::Column  &column_format
, Delineation_layout::Text_quote_mode  quote_mode
,const char *delimiter
//,int16 col // 1 based
)
{
   if (column_format.start_1based /*070621 start*/ > 0) // fixed width column
   {
      int str_len = str.length();
      size_t required_curr_line_length = (column_format.start_1based /*070621 start*/  - 1 + str_len);
      if (current_line.length() < required_curr_line_length)
         current_line.resize(required_curr_line_length);
      current_line.replace(column_format.start_1based /*070621 start*/  - 1,str_len,str);
   }
   else
   {

      current_line.append(delimiter);

      switch (quote_mode)
      {  case Delineation_layout::NO_QUOTE : break;  // no quote
         case Delineation_layout::SINGLE_QUOTE : current_line.append("'"); break;
         case Delineation_layout::DOUBLE_QUOTE : current_line.append("\""); break;
//NYI         case ALTERNATING_QUOTE};
         default : current_line.append("\""); break;
      };

      current_line.append(str);
      switch (quote_mode)
      {  case Delineation_layout::NO_QUOTE : break;  // no quote
         case Delineation_layout::SINGLE_QUOTE : current_line.append("'"); break;
         case Delineation_layout::DOUBLE_QUOTE : current_line.append("\""); break;
//NYI         case ALTERNATING_QUOTE};
         default : current_line.append("\""); break;
      };

   };
};
//______________________________________________________________________________

#ifdef NN
void UED_text_export_file::write_string
(const Ustring &str
//,  const ED_tabular_file_format::Column  &column_format
)
{
/*
   if (column_format.start > 0) // fixed width column
   {
      int str_len = str.length();
      int required_curr_line_length = (column_format.start - 1 + str_len);
      if (current_line.length() < required_curr_line_length)
         current_line.resize(required_curr_line_length);
      current_line.replace(column_format.start - 1,str_len,str);
   }
   else
*/
   {
      current_line.append(str);

   };
};
#endif
//______________________________________________________________________________
void UED_text_export_file::goto_next_row()
{
   goto_row(row+1);
};
//______________________________________________________________________________

void UED_text_export_file::goto_row(int16 target_row)
{
   if (!row) {row = 1; return;};
   while (row < target_row)
   {
      int16 column_headers_start_row = format.column_headers_delineation.start_row_1_based;
      int16 detail_lines_start_row   = format.detail_lines_delineation.start_row_1_based;
      if (   (column_headers_start_row && (row < column_headers_start_row))
          && (detail_lines_start_row   && (row < detail_lines_start_row)))
      {  // This must be a header
         tout << header_line[row] << std::endl;
         header_line[row].assign(""); // The header is no longer used, we can delete it.
      }
      else
         tout << current_line << std::endl;
      current_line.assign("");
      row ++;
   };
}; // target row is 1 based

// UED_Excel_export_file----------------------------------------------------------------

UED_Excel_export_file::~UED_Excel_export_file()
{
};

void UED_Excel_export_file::export_integer
(  int16  value
,  const ED_tabular_file_format::Column  &column_format
,  const char *delimitor
)
{
   Biff_file::write_integer(value,column_format.field_width);
};
//______________________________________________________________________________
void UED_Excel_export_file::export_float
(  float32  value
,  const ED_tabular_file_format::Column  &column_format
,  const char *delimitor
)
{
   Biff_file::write_float(value,column_format.field_width,column_format.precision);
};
//______________________________________________________________________________
void UED_Excel_export_file::export_date
(  const Date &date
,  const ED_tabular_file_format::Column  &//column_format
,  const char *delimitor
)
{
   Ustring date_text(date.c_str());
   write_string_aligned(Common_spreadsheet_file::CSS_justify_left,date_text.c_str());
};
//______________________________________________________________________________
void UED_Excel_export_file::export_string
(const Ustring &str
,  const ED_tabular_file_format::Column  &column_format
, Delineation_layout::Text_quote_mode  quote_mode
,const char *delimitor
)
{
//   Common_spreadsheet_file::col = column_format.number - 1;
   Biff_file::write_string_aligned/*101018write_string*/
      (Common_spreadsheet_file::CSS_justify_general,str.c_str());
//already advanced    Common_spreadsheet_file::col += 1; // <- auto advance cell     column_format.number - 1;
};
#endif
//______________________________________________________________________________

// main()--------------------------------------------------------

/*
test command line
database    C:\dev\UED\convert\test\london.ued
format      C:\CS_suite\ued\convert\formats\NOAA_MET.fmt
output      C:\dev\UED\convert\test\london.met
startdate   0

C:\dev\UED\convert\test\london.ued C:\CS_suite\ued\convert\formats\NOAA_MET.fmt C:\dev\UED\convert\test\london.met 0

C:\Simulation\Projects\alfalfa\Scenarios\alfalfa3\Output\harvest.ued C:\Simulation\Database\Output\default\harvest.tdf  C:\Simulation\Projects\alfalfa\Scenarios\alfalfa3\Output\harvest.xls 1993001

C:\Simulation\Projects\alfalfa\Scenarios\alfalfa3\Output\daily.ued C:\Simulation\Database\Format\all\daily.tdf  C:\Simulation\Projects\alfalfa\Scenarios\alfalfa3\Output\daily.xls

// test for luca
D:\Simulation\Projects\prove\Scenarios\mais\Output\daily.ued d:\simulation\database\output\tdf\daily.tdf D:\Simulation\Projects\prove\Scenarios\mais\Output\daily1.xls 1951001 1951365

// test for Tinch
C:\temp\assist\cropsyst\tinch\primaryoutput\season.ued C:\temp\assist\cropsyst\tinch\primaryoutput\season.tdf C:\temp\assist\cropsyst\tinch\primaryoutput\season.txt 1993001 1997365 
*/

#ifdef STANDALONE
void main(int argc, char *argv[])
{
   if ((argc > 1) && (argc <= 6))
   {
      File_name UED_database_filename(argv[1]);
      File_name TDF_format_filename(argv[2]);
      File_name output_filename(argv[3]);
      CORN::datetime64          start_date_num = 0;
      CORN::datetime64          end_date_num = 0;
      if (argc >= 5) // Starting/ending date is optional
      {
         start_date_num = atof(argv[4]);
         end_date_num = atof(argv[5]);
      };

      //NYI if arg3 is not specified use same name as UED but assign appropriate extension

      ED_tabular_file_format format;

      VV_File format_file(TDF_format_filename.c_str());                          //050404
      format_file.get(format);                                                   //050404

      UED_export_database export_DB(UED_database_filename.c_str(),format);       //050404
      cout << "initializing" << endl;
      export_DB.initialize();
#ifdef OUTPUT_VAR_CODES
//varcodes file is temporary just so I can see the UED standard variable codes.
ofstream var_codes("UED_varcodes.txt");
char buf[20];
var_codes << CORN_uint32_to_str(UED_STD_VC_precipitation.code,buf,16) << " precipitation" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_max_temperature.code,buf,16) << " max_temperature" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_min_temperature.code,buf,16) << " min_temperature" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_avg_temperature.code,buf,16) << " avg_temperature" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_obs_temperature.code,buf,16) << " obs_temperature" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_max_dew_point_temperature.code,buf,16) << " max_dew_point_temperature" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_min_dew_point_temperature.code,buf,16) << " min_dew_point_temperature.code" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_max_relative_humidity.code,buf,16) << " max_relative_humidity" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_min_relative_humidity.code,buf,16) << " min_relative_humidity" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_solar_radiation.code,buf,16) << " solar_radiation" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_wind_speed.code,buf,16) << " wind_speed" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_pot_evapotranspiration.code,buf,16) << " pot_evapotranspiration" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_act_evapotranspiration.code,buf,16) << " act_evapotranspiration" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_pan_evaporation.code,buf,16) << " pan evaporation" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_ref_ET_penman_monteith.code,buf,16) << " ref_ET_penman_monteith" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_ref_ET_priestly_taylor.code,buf,16) << " ref_ET_priestly_taylor" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_ref_ET_hargraves.code,buf,16) << " ref_ET_hargraves" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_avg_daytime_vapor_pressure_deficit.code,buf,16) << " avg_daytime_vapor_pressure_deficit" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_avg_fullday_vapor_pressure_deficit.code,buf,16) << " avg_fullday_vapor_pressure_deficit" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_max_vapor_pressure_deficit.code,buf,16) << " max_vapor_pressure_deficit" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_cloud_cover.code,buf,16) << " cloud_cover" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_snow_fall.code,buf,16) << " snow_fall" << endl;
var_codes << CORN_uint32_to_str(UED_STD_VC_snow_depth.code,buf,16) << " snow_depth" << endl;
#endif

   // the following date setting is primarily for CropSyst, we will use the simulation period
   {  const UED_period_record *simulation_period_rec = export_DB.get_period(UED_period_application_code_option/*|UED_period_variable_code_option*/,0,0,0,0,0);
      if (simulation_period_rec)
         export_DB.set_date_ranges(simulation_period_rec->start_date_time,simulation_period_rec->end_date_time);
   };

      if (start_date_num) export_DB.set_date_ranges(start_date_num,end_date_num);

      export_DB.export_to(output_filename.c_str()
//      ,earliest_dt64 // earliest_date_time // export_DB.get_earliest_date_time(earliest_date_time)  // May eventually want this user selectable
//      ,latest_dt64   // latest_date_time
      );
   }
   else
   {
      cout << "Export requires 3 argument: database.UED format.FMT outfile.XLS YYYYDDD YYYYDDD" << endl;
      cout << "where YYYYDDD is year and day of year with no spaces I.e. 1998001 for the start and end dates to export" << endl;
   };
};
#endif
//______________________________________________________________________________

