#ifndef export_columnH
#define export_columnH
#include "UED/convert/text_dBase_Excel_with_TDF/imp_exp.h"

namespace UED
{
class Export_tuple;
class Tuple_index;

//______________________________________________________________________________
class Export_column
: public Imp_exp_column
{
   // This class defines the location and property of a data column.
   // variable code is available in the column_record_index
 public:
   Statistic_labeled  statistic_labeled;
   bool generated;  // I.e. due to being a layered variable
   bool encountered;  // set to true if a matching UED record is found in the file (used to indicate N/A)
 private:
   Export_tuple *current_export_tuple;
      //             This is used during tuple generation phase.
   bool set_export_tupple                                                        //990506
      (nat16 column_number                                                       //020525
      ,float32 target_value
      ,const Date_time_clad_64 &index_date_time
         // Probably could be Date_time_interface
      ,Tuple_index &tuples);                                                     //000717
 public:
   inline Export_column
      (ED_tabular_file_format::Column &_column_layout)                           //040928
      : Imp_exp_column(_column_layout)
      , current_export_tuple(0)
      , statistic_labeled(value_statistic)
      , generated(false)
      , encountered(false)                                                       //040930
      {}
      // Constructor for reading column layout from format file.
   bool tuplize                                                                  //990506
      (nat16                              column_number                          //040929
      ,Binary_data_record_cowl           &data_record                            //151125
      ,Tuple_index                       &tuples                                 //000717
      ,const Database_file_indexed       &database // Just for convert function
      ,CORN::datetime64                   date_time_range_low                    //070621
      ,CORN::datetime64                   date_time_range_high);                 //070621
    bool tuplize_data_set                                                        //990506
      (nat16                              column_number                          //020526
      ,Binary_data_record_cowl           &data_record                            //151125
      ,Tuple_index                       &tuples                                 //000717
      ,const Database_file_indexed       &database // Just for convert function
      ,const CORN::Units_clad            &smart_preferred_units
      ,CORN::datetime64                   date_time_range_low                    //070621
      ,CORN::datetime64                   date_time_range_high                   //070621
      );
    bool tuplize_data                                                            //990506
      (nat16 column_number
      ,Binary_data_record_cowl            &data_record                           //151125
      ,Tuple_index                        &tuples                                //000717
      ,const Database_file_indexed        &database // Just for convert function
      ,const CORN::Units_clad             &smart_preferred_units
      ,CORN::datetime64                    filter_date_time_range_low            //070621
      ,CORN::datetime64                    filter_date_time_range_high);         //070621
};
//_1999-05-02___________________________________________________________________
} // namespace UED
#endif

