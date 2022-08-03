/*
	This program evaluates each data value (scalars and datasets)
   in the database creating an HTML document showing
   potential warnings and errors in the database.
*/


class Variable_status
: CORN_container_item
{
	UED_variable_code 			variable;
   UED_units_code       		time_step;

   CORN_unidirectional_list   values_status;

	void add(const UED_data_record &data_record);
   // For each datum in the data_record append a value status to values_status list

};

class Value_status
: CORN_container_item
{
	CORN:Date_time				date_time;
   UED_quality_attributes	quality;
   float							value;


};

class Values_status
: public CORN_bidirectional_list
{



};

class Variables_status
: public CORN_bidirectional_list  // list of Variable_status
{

	void add(const UED_data_record &data_record);
//       get the variable code and time step for the record
//			Look this pair in this list
//       Add the pair to the list creating a Variable_status if it doesn't exist.
//       Have the located or new Variable_status add(data_record);

   void report(HTML::document &validation_doc);
   //  output a table
   //    Table will include a column for the date
   //    include a header row for each Variable_status in the list
   //    using the variable description for the <TH>
   //    include a header row for the units.
   //    have all variables_status create a list of all unique dates encountered
   //    For each unique date
};


void main(int argc, char *argv[])
{
	Variables_status vars_status;
	for (each data record)
   	vars_status.add(data_rec);

   // Arg1 name of the database
   // arg2 optional name of target directory (otherwise target directory)
   // has same name as database
   CORN::Sub_file_name validation_html_filename(target_directory,"validation.htm");
	ofstream validation_html_stream(validation_html_filename.c_str());
	HTML::document validation_doc(validation_html_stream);
};
