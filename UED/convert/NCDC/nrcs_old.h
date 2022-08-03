#ifndef UED_NRCS_H
#define UED_NRCS_H
#include <ued/units.h>
#include <ued/varcodes.h>
#include <corn/filename.h>
#include <corn/tabular/text.h>
#define MAX_COLUMNS 100
//______________________________________________________________________________
/*______*/ enum UED_format_file_types {FILE_TYPE_unknown,FILE_TYPE_text, FILE_TYPE_dBase, FILE_TYPE_lotus_123, FILE_TYPE_Excel};
/*______*/ enum UED_text_quote_mode   { NO_QUOTE, SINGLE_QUOTE, DOUBLE_QUOTE };
//______________________________________________________________________________
/*______*/ class UED_tabular_file_format
/*______*/ {
/*______*/  public:
/*______*/    enum delimiter_mode    { DELIM_FIXED_WIDTH,DELIM_SPACE,DELIM_COMMA,DELIM_TAB};
/*______*/  public:
/*______*/    int16              header_lines;    // This is the number of rows at the beginning of the file
/*______*/                         // that has comments layout info etc..
/*______*/    int16              columns;
/*______*/    delimiter_mode     delimiter ;      // This specifies the kind of delimitor
/*______*/    UED_text_quote_mode    text_quote;      // This specifies the type of quoting to expect for text.
/*______*/    UED_units_code     time_step_units;
/*______*/    int16              date_column;  // must be signed
/*990307*/    int16              column_width[20];
/*990307*/    UED_variable_code  variable_codes[20];
/*______*/	  // mark as english or metric
/*______*/	  bool					english_units[20];
/*990307*/    UED_units_code 		units_codes[20];
/*990314*/    UED_quality_attributes attributes[20];
/*______*/	public:
/*______*/    UED_tabular_file_format
/*______*/    (int16          i_header_lines
/*______*/    ,int16				i_columns
/*______*/    ,delimiter_mode i_delimiter
/*______*/    ,UED_text_quote_mode    i_text_quote
/*______*/    ,UED_units_code     i_time_step_units
/*______*/    ,int16              i_date_column
/*______*/    )
/*______*/    : header_lines(i_header_lines)
/*______*/    , columns(i_columns)
/*______*/    , delimiter(i_delimiter)
/*______*/    , text_quote(i_text_quote)
/*______*/    ,time_step_units(i_time_step_units)
/*______*/    , date_column(i_date_column)
/*______*/    {};
/*______*/
/*______*/    inline void set_column_width(int column, int width)
/*______*/    { column_width[column] = width; };
/*______*/
/*______*/    inline void set_variable_code(int8 index, UED_variable_code variable_code)
/*______*/    { variable_codes[index] = variable_code; };
/*______*/
/*______*/    inline void set_units_code(int8 index, UED_units_code units_code, bool english)
/*______*/    { units_codes[index] = units_code;
/*990618*/      english_units[index] = english;
/*______*/    };
/*______*/ };
//______________________________________________________________________________
/*______*/ class UED_tabular_text_file : public UED_tabular_file_format
/*______*/ {
/*______*/ private:
/*______*/    bool is_good;
/*______*/ public:
/*______*/    File_name      filename;
/*______*/    ifstream           text_stream;
/*______*/
/*______*/ public:
/*______*/    float32            row_data16[MAX_COLUMNS];
/*______*/    CORN_date          row_date;  // WARNING we may need to make this a CORN_date_time
//______*/    int16              column_width[MAX_COLUMNS]; // With of columns in fixed width delimitation
//______*/    UED_variable_code  variable_codes[MAX_COLUMNS];
//______*/    UED_units_code     units_codes[MAX_COLUMNS];
/*______*/
/*______*/ public:
/*______*/     UED_tabular_text_file
/*______*/        (const char         *i_filename
/*______*/        ,int16               i_header_lines
/*______*/        ,int16               i_columns
/*______*/        ,delimiter_mode      i_delimiter
/*______*/        ,UED_text_quote_mode i_text_quote_mode
/*______*/        ,UED_units_code      i_time_step_units
/*______*/        );
/*______*/    virtual bool read_record();
/*______*/    // returns true if the read succeeded
/*______*/
/*______*/    void skip_header();
/*______*/    // moves the file pointer to the line of the file with the first record.
/*______*/
/*______*/    inline bool good() { return is_good; };
/*______*/ };
//______________________________________________________________________________
/*______*/ class NRCS_text_file : public UED_tabular_text_file
/*______*/ {
/*______*/    CORN_string labels[MAX_COLUMNS];
/*______*/ public:
/*______*/    NRCS_text_file(const char *i_filename);
/*______*/    virtual bool read_record();
/*______*/ };
//______________________________________________________________________________
#endif
