#ifndef imp_expH
#define imp_expH
#include "UED/convert/ED_tabular_format.h"
// Classes common to both Import and Export
#include "corn/tabular/tabular.h"
#include "corn/container/unilist.h"
#include "UED/library/database_file.h"
using namespace CORN;
namespace UED
{
//______________________________________________________________________________
class Imp_exp_column
: public Tabular_data_column                                                     //050406
{public:
    uint16 check_obs_number;                                                     //020525
    // The index of the column  // was index
    // For database format, this is the field number
    // For spreadsheet files, this is the cell column number
    // For text files this is the data column/field number (not character position)
 public:
    ED_tabular_file_format::Column   &TFFC_layout;
   // Note: layout is also in  Tabular_data_column as CORN::Tabular_column
   // this layout here is the referece in  UED_tabular_file_format::Column
   // which is derived form CORN::Tabular_column
   // (I could use a pointer and caste)
 public: // override pure methods
   inline virtual int compare(const Item &/*other*/)                             const { return 0;}  // Not used
   inline Imp_exp_column(ED_tabular_file_format::Column   &_layout)
      : Tabular_data_column(_layout)                                             //050406
      , TFFC_layout(_layout)                                                    //040928
      , check_obs_number(0)
      {}
   inline Imp_exp_column(const UED::Imp_exp_column &to_copy, int16 layer)
      : Tabular_data_column(to_copy.TFFC_layout)                                 //050406
      , TFFC_layout(to_copy.TFFC_layout)
      , check_obs_number(to_copy.check_obs_number + layer)                       //020525
      {}
 };
//______________________________________________________________________________
/*
050405 This is becomming obsolete

When importing, there may be multiple stations in the file
so multiple station databases.
The databases are stored in the convertor.
If the file being imported doesn't list the station in one of the
columns (I.e. all the data in the file is for a single station)
There will only be the database specified on the command line

In any event I need to UED_imp_exp_database so it does not have the database.
[UED_imp_exp_database may actually become obsolete].
*/

class Imp_exp_database
: public Database_file_indexed
{protected:
   ED_tabular_file_format &format;   // Now made a reference because a single import file may have multiple databases.  //050404
 public:
   Imp_exp_database
      (const char *database_filename                                             //020505
      ,std::ios_base::openmode _openmode                                         //130401
      ,ED_tabular_file_format &_format
      ,bool _auto_float16=true); // caller instanciates                    //050404
};
//_2000-09-01___________________________________________________________________
} // namespace UED
#endif

