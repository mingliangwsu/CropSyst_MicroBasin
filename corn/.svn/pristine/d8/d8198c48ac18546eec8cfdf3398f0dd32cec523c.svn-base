#ifndef delineated_datarecH
#define delineated_datarecH
#include "corn/data_source/datarec.h"
// This format doesn't have sections, but we need a default section name for the section structure used by the the data record class
namespace CORN
{
class Cell_numeric;
class Cell_textual;
class Tabular_data_column;
//______________________________________________________________________________
class Delineated_data_record
: public Data_record
{public:
   Bidirectional_list &tabular_data_columns;   // list of Delineated columns
   sint16 year_offset_for_dates_with_only_two_digits;                            //120331
 public: //constructor
   Delineated_data_record
      (Bidirectional_list &_tabular_data_columns
      ,const char *primary_section
      ,sint16 year_offset_for_dates_with_only_two_digits /* = 0 */);              //120331
 public: // virtual overrides
   virtual bool expect_structure(bool for_write);                                //161023
   inline virtual sint16 get_year_offset_for_dates_with_only_two_digits()  const { return year_offset_for_dates_with_only_two_digits; }
 public:
   bool set_numeric(const std::string &current_sheet_name,const Cell_numeric &cell,bool dates_based_1904);
   bool set_textual(const std::string &current_sheet_name,const Cell_textual &cell);
 private:
   Tabular_data_column *find_tabular_data_column(const std::string &current_sheet_name,nat16 cell_column_1base);
};
//______________________________________________________________________________
}
#endif

