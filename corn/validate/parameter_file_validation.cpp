#include <corn/validate/parameter_file.h>
//______________________________________________________________________________
Parameter_file_validation::Parameter_file_validation
(const Smart_file_name &i_parameter_filename
,ostream &i_doc_stream)
: HTML::Document(i_doc_stream)
, body(this)
//, warning_count(0)
//, error_count(0)
, parameter_filename(i_parameter_filename)
, doc_stream(i_doc_stream)
, parameter_table(0)
, status(good_status) // start presuming good then look for error.
{  body.set_text(HTML::Color("BLACK"));
   body.set_bgcolor(HTML::Color("WHITE"));
};
//______________________________________________________________________________
bool Parameter_file_validation::existence_check()
{  HTML::Hx h2(2,this);
   doc_stream << parameter_filename << ':';
   bool file_exists = parameter_filename.exists();
   {  HTML::Font status_color((file_exists ? "GREEN" : "RED"),&h2);
      status_color.start();
      doc_stream << (file_exists ? "Exists" : "Missing");
   };
//   error_count += !file_exists;
    if (!file_exists)
      set_worst_status(missing_status);
   return file_exists;
};
//______________________________________________________________________________
bool Parameter_file_validation::description_check(bool description_provided)
{  if (!description_provided)
   {  HTML::Hx h3(3,this);
      {  HTML::Font status_color("YELLOW",&h3);
         status_color.start();
         doc_stream << "missing description"/*common_translate(TL_missing_description)*/;
      };
      set_worst_status(warning_status);
//      warning_count += 1;
   };
   return description_provided;
};
//______________________________________________________________________________
bool Parameter_file_validation::start_parameter_check_table()
{  parameter_table = new HTML::Table(&body);
   parameter_table->set_border(5);
   {  HTML::Table::Tr header_row(parameter_table);
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_rowspan(2);
         th.start();
         doc_stream << "Variable";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_rowspan(2);
         th.start();
         doc_stream << "Value";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_rowspan(2);
         th.start();
         doc_stream << "Units";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_colspan(2);
         th.set_bgcolor(HTML::Color("YELLOW"));
         th.start();
         doc_stream << "Warning range";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_colspan(2);
         th.set_bgcolor(HTML::Color("RED"));
         th.start();
         doc_stream << "Error range";
      };
   };
   {  HTML::Table::Tr header_row(parameter_table);
/*not needed for row span
      {
         HTML::Table::Tr::Th th(&header_row);
         th.start();
      };
      {
         HTML::Table::Tr::Th th(&header_row);
         th.start();
      };
*/
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_bgcolor(HTML::Color("YELLOW"));
         th.start();
         doc_stream << "Min";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_bgcolor(HTML::Color("YELLOW"));
         th.start();
         doc_stream << "Max";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_bgcolor(HTML::Color("RED"));
         th.start();
         doc_stream << "Min";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.set_bgcolor(HTML::Color("RED"));
         th.start();
         doc_stream << "Max";
      };
      {  HTML::Table::Tr::Th th(&header_row);
         th.start();
         doc_stream << "Notes";
      };
   };
   return true;
};
//______________________________________________________________________________
bool Parameter_file_validation::end_parameter_check_table()
{
   delete parameter_table; // This will put in </TABLE>
   parameter_table = 0;
   return true;
};
//______________________________________________________________________________
