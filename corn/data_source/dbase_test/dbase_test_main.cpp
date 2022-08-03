#include <corn/data_source/dbase_datasrc.h>
#include <corn/data_source/datarec.h>

using namespace CORN;


class Test_data_record
: public Data_record
{
public:
   Ustring  string_field;
   int16    int16_field;
   float32  float32_field;
   bool     bool_field;
public:
   Test_data_record()
   : Data_record("no_section")
   {};
   void expect_structure(bool for_write)
   {  Data_record::expect_structure(for_write);
      expect_string  ("string"   ,string_field,10);
      expect_int16   ("int16"    ,int16_field);
      expect_float32 ("float32"  ,float32_field);
      expect_bool    ("bool"     ,bool_field);
      structure_defined = true; //120314
   };
};


bool test_write()
{
   Data_source_dBase dBase_test("C:\\dev\\corn\\data_source\\dbase_test\\dBase_test.dbf");
   Test_data_record record_buffer;
   ifstream test_data("C:\\dev\\corn\\data_source\\dbase_test\\test_data.dat");
   while (!test_data.eof())
   {
      test_data >> record_buffer.string_field;
      test_data >> record_buffer.int16_field;
      test_data >> record_buffer.float32_field;
      char bool_string[10];
      test_data >> bool_string;
      record_buffer.bool_field = strcmp(bool_string,"TRUE") == 0;
      dBase_test.append(record_buffer);
   };
   return true;
};
//______________________________________________________________________________
bool test_read()
{
   Data_source_dBase dBase_test("C:\\dev\\corn\\data_source\\dbase_test\\dBase_test.dbf");
   Test_data_record record_buffer;
   ofstream test_data_dump("C:\\dev\\corn\\data_source\\dbase_test\\test_data_dump.dat");
   for (bool good = dBase_test.get_next()
      ;good
      ;good = dBase_test.get_next())
   {
      test_data_dump << record_buffer.string_field;
      test_data_dump << record_buffer.int16_field;
      test_data_dump ,record_buffer.float32_field;
      test_data_dump << bool_string
         record_buffer.bool_field ? "TRUE" : "FALSE"
      test_data_dump << endl;
   };
   return true;
};
//______________________________________________________________________________
void main()
{
   bool write_success = test_write();
   bool read_success = test_read();
};