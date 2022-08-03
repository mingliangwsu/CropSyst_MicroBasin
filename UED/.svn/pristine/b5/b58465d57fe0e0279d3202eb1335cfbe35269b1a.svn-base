#include "UED/library/UED.h"
#include "UED/library/varrec.h"
#include "corn/format/binary/binary_file_interface.h"
namespace UED {
//______________________________________________________________________________
Variable_definition_format_0_record::Variable_definition_format_0_record()
: Record_base(UED_variable_definition_format_0)                                  //990107
, Variable_format_0()
{
// It is dangerous to do anything inside the constructor, this is done by load_variable_definitions
// The record is already read by read_record
}
// This constructor is for reading the variable definition from the database
//_1999?___________________________________Variable_definition_format_0_record_/
Variable_definition_format_0_record::Variable_definition_format_0_record
(UED_variable_code   _code                                                       //990107
,CORN::Units_code    _preferred_units                                            //050631
,float32             _min_warning
,float32             _max_warning
,float32             _min_error
,float32             _max_error
,const char         *_description                                                //040908
,const char         *_abbreviation)                                              //040908
: Record_base(UED_variable_definition_format_0)                                  //990107
, Variable_format_0
   (_code
   ,_preferred_units                                                             //050631
   ,_min_warning,_max_warning,_min_error,_max_error
   ,_description,_abbreviation)
{}
// This constructor is for writing the variable definition to the database
//______________________________________________________________________________
Variable_definition_format_0_record::Variable_definition_format_0_record
(const Variable_format_0 &variable_def)
: Record_base(UED_variable_definition_format_0)                                  //990107
, Variable_format_0(variable_def)
{}
// This constructor is for including standard or other definitions.
//_1999-04-26___________________________________________________________________
Variable_definition_format_0_record* Variable_definition_format_0_record::clone() const
{  return new Variable_definition_format_0_record(*this);
}
//__2014-01-16__________________________________________________________________
void Variable_definition_format_0_record::read_definition
(CORN::Binary_file_interface &parent_database ) // Binary_file_interface_replacing_Binary_fstream
{  code_clad.set(parent_database.read_nat32());
   preferred_units_clad.set(parent_database.read_nat32());                       //021212
   //Note that we cannot get units definition because we may already be in the
   //process of scanning the database for this variable definition
   //get_units_definition adjusts the current pointer.
   min_warning = parent_database.read_float32();
   max_warning = parent_database.read_float32();
   min_error = parent_database.read_float32();
   max_error = parent_database.read_float32();
   parent_database.read_string(description,CORN::ASCII_Z_string);               //030125
   // note that the abbreviation and other description entries are not currently stored in this record format
   // they will need to be entered in future formats
   // Currently setting the abbreviation to the same value as the description
   // In future format records we will store the abbreviation text               //070223
}
//_2001-05-25___________________________________________________________________
void Variable_definition_format_0_record::write_definition
(CORN::Binary_file_interface &parent_database)
{
   parent_database.write_nat32(code_clad.get());                                 //980624
   parent_database.write_nat32(                                                  //980818
#ifdef NYI
This cannot be simply implemented
                  preferred_units_code.get() == 0xFFFFFFFF ? preferred_units_def->get() :
#endif
   preferred_units_clad.get() );                                                 //070216
   parent_database.write_float32(min_warning);
   parent_database.write_float32(max_warning);
   parent_database.write_float32(min_error);
   parent_database.write_float32(max_error);
   parent_database.write_string(description,CORN::ASCII_Z_string);               //100114
}
//_2000-09-08_________________________________________________write_definition_/
bool Variable_definition_format_0_record::read_body
(CORN::Binary_file_interface &parent_database  )
{  read_definition(parent_database);
   return true;                                                                  //100128
}
// This method must be overridden it will be called by read() after reading the record type code
// For unrecognized record types, the data will be read it to unknown data
//_2000-09-08___________________________________________________________________
void Variable_definition_format_0_record::write_body
(CORN::Binary_file_interface    &parent_database) // Binary_file_interface_replacing_Binary_fstream
{  write_definition(parent_database); }
   // This  method must be overridden it will be called by write () after writing the record type code
//_2000-09-08___________________________________________________________________
//______________________________________________________________________________
Variable_definition_format_ontological_record::Variable_definition_format_ontological_record()
: Record_base(UED_variable_definition_format_ontological)
, Variable_format_ontological()
{
// It is dangerous to do anything inside the constructor, this is done by load_variable_definitions
// The record is already read by read_record
}
// This constructor is for reading the variable definition from the database
//_2016-06-19____________________Variable_definition_format_ontological_record_/
Variable_definition_format_ontological_record::Variable_definition_format_ontological_record
(UED_variable_code   code_                                                       //990107
,CORN::Units_code    preferred_units_                                            //050631
,const char         *ontology_)                                                  //040908
: Record_base(UED_variable_definition_format_ontological)                        //990107
, Variable_format_ontological
   (code_
   ,preferred_units_                                                             //050631
   ,ontology_)
{}
// This constructor is for writing the variable definition to the database
//_2016-06-19___________________________________________________________________
Variable_definition_format_ontological_record::Variable_definition_format_ontological_record
(const Variable_format_ontological &variable_def)
: Record_base(UED_variable_definition_format_ontological)                        //990107
, Variable_format_ontological(variable_def)
{}
// This constructor is for including standard or other definitions.
//_2016-06-19___________________________________________________________________
Variable_definition_format_ontological_record* Variable_definition_format_ontological_record::clone() const
{  return new Variable_definition_format_ontological_record(*this);
}
//_2016-06-19___________________________________________________________________
void Variable_definition_format_ontological_record::read_definition
(CORN::Binary_file_interface &parent_database ) // Binary_file_interface_replacing_Binary_fstream
{  code_clad.set(parent_database.read_nat32());
   preferred_units_clad.set(parent_database.read_nat32());                       //021212
   //Note that we cannot get units definition because we may already be in the
   //process of scanning the database for this variable definition
   //get_units_definition adjusts the current pointer.
   parent_database.read_string(ontology,CORN::ASCII_Z_string);
   // note that the abbreviation and other description entries are not currently stored in this record format
   // they will need to be entered in future formats
   // Currently setting the abbreviation to the same value as the description
   // In future format records we will store the abbreviation text
}
//_2016-06-19___________________________________________________________________
void Variable_definition_format_ontological_record::write_definition
(CORN::Binary_file_interface &parent_database)
{
   parent_database.write_nat32(code_clad.get());
   parent_database.write_nat32(
#ifdef NYI
This cannot be simply implemented
    preferred_units_code.get() == 0xFFFFFFFF ? preferred_units_def->get() :
#endif
   preferred_units_clad.get() );
   parent_database.write_string(ontology,CORN::ASCII_Z_string);
}
//_2016-06-19___________________________________________________________________
bool Variable_definition_format_ontological_record::read_body
(CORN::Binary_file_interface &parent_database  )
{  read_definition(parent_database);
   return true;                                                                  //100128
}
// This method must be overridden it will be called by read() after reading the record type code
// For unrecognized record types, the data will be read it to unknown data
//_2016-06-19___________________________________________________________________
void Variable_definition_format_ontological_record::write_body
(CORN::Binary_file_interface    &parent_database) // Binary_file_interface_replacing_Binary_fstream
{  write_definition(parent_database); }
   // This  method must be overridden it will be called by write () after writing the record type code
//_2016-06-19___________________________________________________________________
} //namespace UED

