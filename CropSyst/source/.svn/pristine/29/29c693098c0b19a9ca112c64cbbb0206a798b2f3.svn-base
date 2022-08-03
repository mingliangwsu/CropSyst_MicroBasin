#  ifdef __BCPLUSPLUS__
#     include <float.h>
#  endif
#  include "chemfile.h"
#define PESTICIDE_TXT "PESTICID.TXT"
//______________________________________________________________________________
chemical_properties::chemical_properties()
:CORN::Item() //180101 Association()
,half_life(0)
,Freundlich_N(0)
,activation_energy(0)
,soil_moisture_influence(0)
,linear_sorption_coef(0)
,name("no name")
{
    //This constructor used when reading chemical file
}
//_1999-02-25___________________________________________________________________
chemical_properties::chemical_properties(const char *i_name)
:CORN::Item()  //180101 Association()
,half_life(0)
,Freundlich_N(0)
,activation_energy(0)
,soil_moisture_influence(0)
,linear_sorption_coef(0)
,name(i_name)
{}
//_1999-02-25___________________________________________________________________
bool chemical_properties::read(std::istream &instrm)
{  instrm >> half_life;
   instrm >> linear_sorption_coef;
   instrm >> Freundlich_N;
   instrm >> activation_energy;
   instrm >> soil_moisture_influence;
   std::getline(instrm,name);                                                    //131121
   // Does this appear to be the end of the file?
   bool at_end = name.length() == 0;
   return !at_end;
}
//_1999-02-25___________________________________________________________________
chemical_file::chemical_file(bool add_none_salt)
: CORN::Bidirectional_list /*180101 Association_list*/()
{
#ifdef __BCPLUSPLUS__
   // There is a bug in Win32, one of MicroSoft's DLL's is incorrectly changing floating point formats!
  _fpreset();
#endif
#ifdef REIMPLEMENT
//090625  I have misplaced the pesticide data file, I need to recover it and put it in another directory
   ifstream chemical_file(cs_suite_paths->get_pesticide_txt().c_str());
   bool at_eof = !chemical_file.good();
   UIO_string header;
   header.read_line(chemical_file);
   while (!at_eof)
   {  chemical_properties *new_chem_props = new chemical_properties();
      bool read_ok = new_chem_props->read(chemical_file);
      if (read_ok)   add_sorted(new_chem_props);
      else           delete new_chem_props;
      at_eof = ! read_ok;
   }
   if (add_none_salt)
   {  prepend(new chemical_properties("None"));
      prepend(new chemical_properties("Salt"));
   }
#endif
}
//_1999-02-25___________________________________________________________________
