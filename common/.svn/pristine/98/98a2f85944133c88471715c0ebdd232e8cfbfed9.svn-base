#ifndef WORKBOOK_RECORDER_H
#define WORKBOOK_RECORDER_H

030501 This class is not currently needed it can be eventually deleted
if I don't complete it and use it



/*

   This class is used to record variables to a workbook.

   This class extends the Workbook_data_source by specifying
   Variable description, and units rows in addition to field name.

   And also reserves rows for headers, variable descriptions and units .
   The rows for these rows, and origin row are fixed.

*/

#define FIRST_HEADER_LINE_ROW 0
#define FIRST_COLUMN_HEADER_LINE_ROW 5
#define FIRST_FIELD_NAME_ROW 10
#define FIRST_DATA_LINE_ROW 11


class Workbook_recorder_data_source
: public Workbook_data_source
{



public:
   Workbook_recorder_data_source
   (CORN::Workbook   *i_workbook
   ,const char       *i_title_line_0
   ,const char       *i_title_line_1
   ,const char       *i_title_line_2
   ,const char       *i_title_line_3
   ,const char       *i_title_line_4
   ,const char       *i_software_version
   ,const CORN::Date &i_software_version_date
   ,const CORN::Date &i_generation_date
   );

};




#endif
