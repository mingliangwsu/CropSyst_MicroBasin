#include <common/recorder/workbook/workbook_recorder_datasrc.h>

Workbook_recorder_data_source::Workbook_recorder_data_source
   (CORN::Workbook   *_workbook
   ,const char       *_title_line_0
   ,const char       *_title_line_1
   ,const char       *_title_line_2
   ,const char       *_title_line_3
   ,const char       *_title_line_4
   ,const char       *_software_version
   ,const CORN::Date &_software_version_date
   ,const CORN::Date &_generation_date
   )
:Workbook_data_source(_workbook,0,FIRST_DATA_LINE_ROW,true,10)
{
   workbook->
,i_title_line_0(_title_line_0)
,i_title_line_1(_title_line_1)
,i_title_line_2(_title_line_2)
,i_title_line_3(_title_line_3)
,i_title_line_4(_title_line_4)
,

};
