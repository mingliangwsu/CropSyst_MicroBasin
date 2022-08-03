#include "ued/convert/text_dBase_Excel_with_TDF/imp_exp.h"

#define LABEL_statistic          "statistic"
#define LABEL_header_field       "header_field"
#define LABEL_number             "number"
#define LABEL_data_type          "data_type"
#define LABEL_col                "col"
#define LABEL_row                "row"
#define LABEL_width              "width"
#define LABEL_records_per_UED_record "records_per_UED_record"

DECLARE_CONTAINER_ENUMERATED_SECTION(ED_tabular_file_format::Column,Column_section_VV,true);
namespace UED
{
//______________________________________________________________________________
Imp_exp_database::Imp_exp_database
(const char *  database_filename                                                 //020505
,std::ios_base::openmode _openmode                                               //130401
,ED_tabular_file_format &_format
,bool _auto_float16 ) // caller instanciates                                     //050404
:Database_file_indexed
   (database_filename,_openmode,_auto_float16 )
,format(_format)                                                                 //050404
{}
}// namespace UED
//______________________________________________________________________________


