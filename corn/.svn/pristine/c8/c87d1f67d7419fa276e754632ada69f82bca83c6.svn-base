#pragma hdrstop
#pragma argsused

#include <corn/measure/units.h>
#include <corn/string/uiostring.h>
#include <ctype.h>
#include <fstream.h>
/*
iomanip

class Units_constants_generator
{
   ifstream units_h_file;
   ofstream units_const_file;
public:
   Units_constants_generator
   (const char *common_units_h_filename
   ,const char *output_filename
   )
   : units_h_file(common_units_h_filename)
   , units_const_file(output_filename)
   {

   }

   void convert_to()
   {
      write_comment("Don't edit this file it is generated from a master list of units codes and may be overridden at any time");
      write start_sentinal
      write_start namespace
      while not end of file
      {
         get line
         if line defines UC or UE or UT
            write definition



      };
      write_end namespace
      write_end_sentinal
   };

   virtual void write_start_sentinal() = 0;
   virtual void write_end_sentinal() = 0;
   virtual void write_start_namespace() = 0;
   virtual void write_end_namespace() = 0;
   virtual void write_definition() = 0;
   virtual void write_comment(const char *comment) = 0;

}

class Units_constants_generator_CS  // C#
: public  Units_constants_generator
{



};

class Units_constants_generator_Cpp // C++
: public  Units_constants_generator
{



};

class Units_constants_generator_VB  // Visual basic
: public  Units_constants_generator
{



};
*/
void  generate_clean_constants()
{
   ifstream units_H_file("C:\\dev\\corn\\measure\\units.h");
   ofstream clean_units_cpp_file("clean_units.cpp");
   clean_units_cpp_file << "#include \"" << "C:\\dev\\common\\measure\\units.h" << "\"" << endl;
   clean_units_cpp_file << "#include <" << "iomanip.h" << ">" << endl;
   clean_units_cpp_file << "void main()\n {" << endl;
   clean_units_cpp_file << "ofstream CS(\"units_codes.cs\");" <<endl;
   clean_units_cpp_file << "ofstream Cpp(\"units_codes.h\");" <<endl;
   clean_units_cpp_file << "ofstream VB(\"units_code.bas\");" <<endl;

   clean_units_cpp_file << "CS  << \"#pragma once\" << endl;" << endl;
   clean_units_cpp_file << "CS  << \"namespace UED_simple\" << endl;" << endl;
   clean_units_cpp_file << "CS  << \"{\" << endl;" << endl;

   clean_units_cpp_file << "Cpp  << \"#ifndef UED_SIMPLE_UNITS_CODE\" << endl;" << endl;
   clean_units_cpp_file << "Cpp  << \"#define UED_SIMPLE_UNITS_CODE\" << endl;" << endl;
   clean_units_cpp_file << "Cpp  << \"namespace UED_simple\" << endl;" << endl;
   clean_units_cpp_file << "Cpp  << \"{\" << endl;" << endl;

   clean_units_cpp_file << "VB  << \"Option Explicit\" << endl; " << endl;
   clean_units_cpp_file << "VB  << \"Attribute VB_name = \\\"UED_simple\\\"\" << endl; " << endl;
   CORN::UIO_string header_line;

   while (!units_H_file.eof())
   {
      header_line.read_line(units_H_file);
//      char end_of_line;
//      units_H_file >> end_of_line;
      if (header_line.find("#define") != NPOS)    // 070424 these may need to be find_substring
      {
         CORN_pos UC_pos = header_line.rfind("UC_");
         CORN_pos UE_pos = header_line.rfind("UE_");
         CORN_pos UT_pos = header_line.rfind("UT_");

         CORN_pos U_a_pos = header_line.find("U_a");
         CORN_pos IMPERIAL_pos = header_line.find("IMPERIAL");
         CORN_pos US_LIQUID_MEASURE_pos = header_line.find("US_LIQUID_MEASURE");
         CORN_pos US_DRY_MEASURE_pos = header_line.find("US_DRY_MEASURE");
         CORN_pos Ux_pos = NPOS;

         if (UC_pos != NPOS) Ux_pos = UC_pos;
         if (UE_pos != NPOS) Ux_pos = UE_pos;
         if (UT_pos != NPOS) Ux_pos = UT_pos;
         if ((Ux_pos != NPOS)/* && (U_a_pos == NPOS)*/)
         {
            char units_define[100];

            if ((U_a_pos != NPOS) || (IMPERIAL_pos != NPOS) || (US_LIQUID_MEASURE_pos!=NPOS)|| (US_DRY_MEASURE_pos!=NPOS))
            {
               Ux_pos = 8;
            }
            {
               int j = 0;
               for (int i = Ux_pos
                  ; (i < header_line.length()) && !isspace(header_line.c_str()[i])
                  ; i++)
                  units_define[j++] = header_line.c_str()[i];
               units_define[j++] = 0;
            };

            clean_units_cpp_file << "CS  << \"   public const uint "<< units_define << " = \" << hex <<\"0x\"<< " << units_define << " << \" ;\" << endl;" << endl;
            clean_units_cpp_file << "Cpp << \"#define "<< units_define << " \" << hex <<\"0x\"<< " << units_define << " <<  endl;" << endl;
//            clean_units_cpp_file << "Cpp << \"const unsigned long "<< units_define << "= \" << hex <<\"0x\"<< " << units_define << " << \" ;\" << endl;" << endl;
            clean_units_cpp_file << "VB  << \"public const "<< units_define << " as long = \" << " << units_define << " << \" ;\" << endl;" << endl;
         };
      };
   };
   clean_units_cpp_file << "CS  << \"}\" << endl;" << endl;

   clean_units_cpp_file << "Cpp  << \"#endif\" << endl;" << endl;

   clean_units_cpp_file << "};" << endl;
};


int main(int argc, char* argv[])
{
   // First generate a clean C++ header file
   generate_clean_constants();


   return 0;
}
//---------------------------------------------------------------------------