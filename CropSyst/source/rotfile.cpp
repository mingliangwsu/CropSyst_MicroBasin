#include <stdio.h>
#include "corn/std/std_fstream.h"
#include "corn/OS/file_system_engine.h"
#include "rotfile.h"
#include <stdio.h>
#include "corn/string/uiostring.h"
using namespace std;

//020520  Note this format is obsolete in version 4
//______________________________________________________________________________
Rotation_entry::Rotation_entry
(const CORN::Date    &_planting_date
,const CRP_filename  &_crop_filename
,const MGT_filename  &_management_filename)
: Item()
, planting_date(_planting_date)
, crop_filename(_crop_filename.c_str())
, management_filename(_management_filename.c_str())
{  planting_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,'/',false);                 //001116
   #ifdef USE_OS_FS
   if (!CORN::OS::file_system_engine.exists(management_filename))                //130807_000323
      management_filename.set_cstr("-");                                         //130807_000323
   #else
   if (!management_filename.exists())                                            //000323
      management_filename.assign("-");                                           //000323
   #endif
      // Need to make sure that management doesn't say optional
};
//______________________________________________________________________________
Rotation_entry::Rotation_entry(const Ustring &file_line)
: Item()
, crop_filename("-")
, management_filename("-")
{  int year,month,dom;
	char crop_c[255];
	char mgmt_c[255];
	sscanf(file_line.c_str(),"%d/%d/%d %s %s",&year,&month,&dom,crop_c,mgmt_c);
	planting_date.set_YMD((CORN::Year)year,(CORN::Month)month,(CORN::DOM)dom);
   planting_date.format(D_YMD,D_YYYY|D_M|D_lead_zero,'/',false);                 //001116
   #ifdef USE_OS_FS
   crop_filename.set_cstr(crop_c);
   management_filename.set_cstr(mgmt_c);
   #else
   crop_filename.assign(crop_c);
   management_filename.assign(mgmt_c);
   #endif
};
//_1999-02-23___________________________________________________________________
int Rotation_entry::compare(const Item &other) const
{  Rotation_entry &other_rot = (Rotation_entry &)other;
   return planting_date.temporal_compare(other_rot.planting_date);
};
//_1999-02-23___________________________________________________________________
bool Rotation_entry::qualify()
{  crop_filename.qualify();
   management_filename.qualify();
   return true;
};
//_2000-02-12___________________________________________________________________
const char *Rotation_entry::label_cstr_deprecated(char *buffer) const
{  strcpy(buffer,planting_date.c_str());
   strcat(buffer," ");
   strcat(buffer,crop_filename.c_str());
   strcat(buffer," ");
   strcat(buffer,management_filename.c_str());
   return buffer;
};
//_1999-02-23___________________________________________________________________
const char *Rotation_entry::label_string(std::string &buffer)              const
{  strcpy(buffer,planting_date.c_str());
   strcat(buffer," ");
   strcat(buffer,crop_filename.c_str());
   strcat(buffer," ");
   strcat(buffer,management_filename.c_str());
   return buffer;
};
//_2017-04-23___________________________________________________________________
bool Rotation_entry::write(STD_NS ostream &strm) modification_
{  char buff[512]; //Ustring buff;
   strm << label_cstr(buff) << endl;
};
//_1999-02-23___________________________________________________________________
Rotation_file::Rotation_file()
: Bidirectional_list()
, Data_record("-")
{};
//_1999-02-23___________________________________________________________________
void Rotation_file::load(const ROT_filename &i_file_name)
{
   std::ifstream rot_strm(i_file_name.c_str());
   UIO_string rot_entry_str;
   bool at_eof = false;
   while (!at_eof)
   {  rot_entry_str.read_line(rot_strm);
      if ((rot_entry_str.length() == 0)||
          rot_strm.eof())
        at_eof = true;
      if (!at_eof)
      {  Rotation_entry *rot_entry = new Rotation_entry(rot_entry_str);
         append(rot_entry);
      };
   };
};
//_1999-02-23___________________________________________________________________
void Rotation_file::save(const ROT_filename &i_file_name)
{  ofstream rot_strm(i_file_name.c_str());
   write(rot_strm);
};
//_1999-02-23___________________________________________________________________
bool Rotation_file::qualify(const CORN_Directory_name /*130807 Directory_name*/ &rot_dir_name)
{  // Currently always return true;
   // This makes sure that all file names are qualified.
   // This is needed for generated simulations for
   // Watershed and AcsCS projects where simulation is run
   // in a subdirectory of the project directory.

   // Rotation entries are relative to the rotation file's location
   // We need to first CD to that directory

   // Actually check if I already have a qualify method in file_system_engine
   CORN::OS::Directory_name_concrete curr_dir;                                   //130807_020329
   CORN::OS::Directory_name_concrete smart_rot_dir_name;                         //130807_020329
   CORN::OS::file_system_engine.set_current_working_directory(smart_rot_dir_name);//010209
   FOR_EACH(entry,Rotation_entry,each_rot)                                       //030709
      entry->qualify();
   FOR_EACH_END(each_rot);                                                       //030709
   //             Make sure we go back where we were.
   CORN::OS::file_system_engine.set_current_working_directory(curr_dir);         //010209
   return true;
};
//_2000-02-11___________________________________________________________________

