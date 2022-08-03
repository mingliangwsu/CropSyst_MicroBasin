#include <ued/convert/formats/nrcs.h>

///////////////////////////////////////////////////////////////////////////////

//CORN_delineation_layout NRCS_delineation_layout

NRCS_text_file::NRCS_text_file
(const CORN_filename &i_filename
//,CORN_delineation_layout &i_NRCS_delineation_layout
)
:UED_tabular_text_file
(i_filename
//,false
//,i_NRCS_delineation_layout
,1
,0 // don't know yet
,DELIM_TAB
,NO_QUOTE
,UED_time_day
)
{
	if (!text_stream.good()) return;
	//The first thing on the line is the weather station code
	CORN_string code;

         140516 replace read_to_delim with getline(input_file,buffer_str)

	code.read_to_delim(text_stream,'-');
	//The remaining items are the column labels;
   CORN_string label;
	int8 label_index = 0;
   date_column = 0;
   do
	{
		label.read_token(text_stream);
		if (!isdigit(label.c_str()[0]))
			labels[label_index] = label;
		if (label == "date")
			date_column = label_index;

		// This file is in english units
		bool english_units = false;
		UED_units_code Xunits_code = 0;
		UED_variable_code variable_code = 0;
		//determine variable code for the column from the label
		if (label == "tmax")
		{
			//int32 qual = UED_time_step_max;  // for debugging only
			//qual  = qual << 24;
			UED_smart_variable_code smart_var_code
			(UED_climate_air_temperature
			,UED_time_step_max
			,true
			);
			variable_code = smart_var_code.get();
//       UED_compose_standard_variable_code(UED_time_step_max,UED_climate_air_temperature)  ;
			Xunits_code = UED_OLD_degrees_F;
			english_units = true;
		}
		if (label == "tmin")
		{
			UED_smart_variable_code smart_var_code
			(UED_climate_air_temperature
			,UED_time_step_min
			,true
			);

			variable_code = smart_var_code.get();
//			UED_compose_standard_variable_code(UED_time_step_min,UED_climate_air_temperature)  ;
			Xunits_code = UED_OLD_degrees_F;
			english_units = true;
		}
		if (label == "tavg")
		{
			UED_smart_variable_code smart_var_code
			(UED_climate_air_temperature
			, UED_time_step_avg
			,true
			);
			variable_code = smart_var_code.get();
//			variable_code = UED_compose_standard_variable_code(UED_time_step_avg,UED_climate_air_temperature)  ;
			Xunits_code = UED_OLD_degrees_F;
			english_units = true;
		}
		if (label == "prcp")
		{
			UED_smart_variable_code smart_var_code
			(UED_climate_precipitation
			,UED_time_step_sum
			,true
			);
			variable_code = smart_var_code.get();
//			variable_code = UED_compose_standard_variable_code(UED_time_step_sum,UED_climate_precipitation)  ;
			Xunits_code = UED_OLD_units_inch_water_depth;
			english_units = true;

		}
		if (label == "snwd")
		{
			UED_smart_variable_code smart_var_code
			(UED_climate_snow_depth
			,UED_at_time_step
			,true
			);
			variable_code = smart_var_code.get();
//			variable_code = UED_compose_standard_variable_code(UED_at_time_step,UED_climate_snow_depth)  ;
			Xunits_code = UED_OLD_units_inch_water_depth;
			english_units = true;

		}
		if (label == "snow")
		{
			UED_smart_variable_code smart_var_code
			(UED_climate_snow_fall
			,UED_time_step_sum
			,true
			);
			variable_code = smart_var_code.get();
//			variable_code = UED_compose_standard_variable_code(UED_time_step_sum,UED_climate_snow_fall)  ; // I presume this is accumulation during the time step
			Xunits_code = UED_OLD_units_inch_water_depth;
			english_units = true;
		}
		if (label == "evap")
		{
			UED_smart_variable_code smart_var_code
			(UED_climate_pan_evaporation
			,UED_time_step_sum
			,true
			);
			variable_code = smart_var_code.get();
//			variable_code = UED_compose_standard_variable_code(UED_time_step_avg,UED_climate_pan_evaporation);
			Xunits_code = UED_OLD_units_inch_water_depth;
			english_units = true;
		}
		/* I don't know what these are
		if (label == "stn1")
		if (label == "stn2")
		if (label == "stn3")
		if (label == "stx1")
		if (label == "stx2")
		if (label == "stx3")
		*/

		set_variable_code(label_index,variable_code);
		set_units_code(label_index,Xunits_code,english_units);

		label_index++;
	}
	while (! isdigit(label.c_str()[0]));
	// When we reach a number, we are at the first record.

	columns = label_index - 1;
	//text_stream.seekg(0);
	text_stream.close();
	text_stream.open(filename.get());
	skip_header();
	// We leave the file pointer ready to read the first record.
};

bool NRCS_text_file::read_record()
{
	bool result = UED_tabular_text_file::read_record();

	int32 date_int = row_data16[date_column];
	CORN_year year = (date_int % 100) + 1900;
	CORN::DOM DOM = (date_int / 100) % 100;
	CORN_month month = date_int/10000;
	row_date.set(year,month,DOM);

	return result;
};

///////////////////////////////////////////////////////////////

UED_tabular_text_file::UED_tabular_text_file
(const CORN_filename &i_filename
,int16           i_header_lines
,int16           i_columns
,delimiter_mode i_delimiter
,UED_text_quote_mode i_text_quote_mode
,UED_units_code i_time_step_units)
:UED_tabular_file_format
(i_header_lines
,i_columns
,i_delimiter
,i_text_quote_mode
,i_time_step_units
,-1
)
, filename(i_filename)
//, header_lines(i_header_lines)
//, columns(i_columns)
//, delimiter(i_delimiter)
//, text_quote(i_text_quote_mode)
, text_stream(i_filename.get())
//, time_step_units(i_time_step_units)
//, date_column(-1)
, is_good(false)
{
	is_good = text_stream.good();
};


void UED_tabular_text_file::skip_header()
{
	CORN_string header;
	for (int header_line = 0; header_line < header_lines; header_line++)
		header.read_to_delim(text_stream,'\n');
      140516 replace read_to_delim with getline(input_file,buffer_str)

};


bool UED_tabular_text_file::read_record()
{
   for (int col = 0; col < columns; col++)
   {
      switch (delimiter)
      {
      case DELIM_FIXED_WIDTH :
         {  char number[255];
            for (int pos = 0; pos < column_width[col] ; pos++)
				{
               text_stream >> number[pos];
               number[pos+1] = 0;
            };
         };
         break;
      case DELIM_SPACE :
			text_stream >> row_data16[col];
      break;
      case DELIM_COMMA : case DELIM_TAB :
      {
         char delim_char = '\t';
			if (delimiter == DELIM_COMMA)
            delim_char = ',';
         if (col == columns-1)
            delim_char = '\n';

         CORN_string number_string;
      140516 replace read_to_delim with getline(input_file,buffer_str)

			number_string.read_to_delim(text_stream,delim_char);
         number_string.strip(string::Both,' ');
         bool has_digit = false;
         for (int i = 0; i < number_string.length(); i++)
            if (isdigit(number_string.c_str()[i]))
               has_digit = true;
			attributes[col] = has_digit // (number_string.length() == 0)
			? UED_valid_attribute
			: UED_missing_attribute;

			row_data16[col] = atof(number_string.c_str());
      };
      break;
      };
   };
   return (!text_stream.eof());
};
