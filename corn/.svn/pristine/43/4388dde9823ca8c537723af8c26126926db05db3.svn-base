
// This file is intended to be #include into test/example programs.

class Test_record
: public Data_record
{
public:
   CORN_string    test_string;
   char           test_str[20];
   int16          test_int16;
   uint16         test_uint16;
   long           test_int32;
   unsigned long  test_uint32;
   float          test_float32;
   double         test_float64;
   bool           test_bool;
   CORN::Date           test_date;

public:
   Test_record()
   : Data_record("test")
   , test_string("test string value")
   , test_int16(1)
   , test_uint16(2)
   , test_int32(3)
   , test_uint32(4)
   , test_float32(234.567)
   ,test_float64(123.456)
   , test_bool(true)
   , test_date()
   {
      strcpy(test_str,"abc");
   };

   virtual void expect_structure(bool for_write)
   {
      set_current_section("strings");
      expect_char_array("test_str",test_str,20);      //works
      expect_string("test_string",test_string,50);    // works
      set_current_section("integers");
      expect_int16("test_int",test_int16);            //works
//      expect_float32("test_float",test_float32);

      expect_int16("test_int16",test_int16);          // works
      expect_uint16("test_uint16",test_uint16,10);
      expect_int32("test_int32",test_int32);       // works
      expect_uint32("test_uint32",test_uint32,10);
      set_current_section("floats");
      expect_float32("test_float32",test_float32);      // not being displayed, but is inputting
      expect_float64("test_float64",test_float64);
      set_current_section("other");
      expect_bool("test_bool",test_bool,VV_bool_entry::form_true);
      expect_date("test_date",test_date);
      structure_defined = true;                                                  //120314
   };

    virtual void dump()
    {
      cout << test_str << '|' << test_int16 << '|' << test_float32 << '|'
      //<< test_date
       << endl;
    };
    virtual void inc()
    {
      for (int i = 0; i < strlen(test_str); i++)
         test_str[i] += 1;
      test_int16 += 1;
      test_float32 += 111.11;
      test_date.inc();
      position = 0;  // This will force a new record to be appended.
    };
};

