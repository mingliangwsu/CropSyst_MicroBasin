
#ifndef CORN_VALIDATE_PARAMETER_FILE
#define CORN_VALIDATE_PARAMETER_FILE

#include <corn/format/html/html.h>
#include <corn/file_sys/smart_filename.h>
#include <corn/validate/validtyp.h>
#include <corn/math/compare.h>
#include <corn/std/std_iostream.h>

/*______*/  namespace CORN {
/*______*/  
/*______*/  class Parameter_file_validation
/*______*/  : public HTML::Document
/*______*/  {
/*______*/  private:
/*020424*/     Smart_file_name parameter_filename;
/*______*/     File_name doc_stream_htm;
/*______*/     HTML::Body body;
/*______*/     STD_NS ostream &doc_stream;
/*______*/     HTML::Table *parameter_table;
/*______*/     Validation_status status;
/*______*/  public:
/*______*/     Parameter_file_validation
/*020424*/     (const Smart_file_name &i_parameter_filename
/*______*/     ,STD_NS ostream &i_doc_stream
/*______*/     );
/*______*/     // The parameter_filename is used to check the file's existence
/*______*/     // and as an output in the report.
/*______*/     // doc_stream is the HTML document where to write the report.
/*______*/
/*______*/     inline ~Parameter_file_validation()
/*______*/     {  if (parameter_table)
/*______*/        delete parameter_table;
/*______*/     };
/*______*/     bool existence_check();
/*______*/     // Check that file exists
/*______*/     bool description_check(bool description_provided);
/*______*/     // if no description provided prints warning.
/*______*/     bool start_parameter_check_table();
/*______*/     bool end_parameter_check_table();
/*______*/     inline Validation_status get_status()
/*______*/     {
/*______*/        return status;
/*______*/     };
/*______*/     inline void set_worst_status(Validation_status param_status)
/*______*/     {
/*______*/        status = CORN_min(status,param_status);
/*______*/     };
/*______*/  };
/*061003*/  }; // namespace CORN
#endif

