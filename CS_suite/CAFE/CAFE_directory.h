#ifndef CAFE_directoryH
#define CAFE_directoryH
#include "CS_suite/CropSyst/CropSyst_directory.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/const.h"
namespace CS {

//______________________________________________________________________________
class FARM_Directory
: public CS::Application_directory                                               //140111
      // This may eventually be derived from CORN::Application_directory (or Suite directory)
{
 public:
   //___________________________________________________________________________
   class Dairy_directory
   : public CS::Application_directory
   {
    private:
      provided_ CORN::OS::File_name_concrete *scenario_editor_exe;
      provided_ CORN::OS::File_name_concrete *field_editor_exe;
      provided_ CORN::OS::File_name_concrete *scenario_run_exe;                  //110717
    public:
      virtual void reset()                                           provision_;
    public:
      const CORN::OS::File_name &scenario_editor_executable()  provision_;
      const CORN::OS::File_name &field_editor_executable()     provision_;
      const CORN::OS::File_name &scenario_run_executable()     provision_;       //140927
    public: // 'structors
         Dairy_directory
            (const FARM_Directory /*141110 CAFE_Directory */ &path_name                                     //141010
            ,const wchar_t *directory_name);
         virtual ~Dairy_directory();
   };
   //___________________________________________________________________________
 private:
      provided_ Dairy_directory *dairy_dir;                                      //140111
 public:
//   CAFE_Directory();
   FARM_Directory(const wchar_t *dairy_project_name);
   FARM_Directory(const CS::Suite_Directory &path_name,const wchar_t * directory_name);               //140111
   virtual void reset()                                               provision_;
 public:
      const Dairy_directory &Dairy() provision_;                                 //140111
};
//______________________________________________________________________________
//______________________________________________________________________________

class CAFE_Directory
: public FARM_Directory                                                          //141110
      // This may eventually be derived from CORN::Application_directory (or Suite directory)
{
 private:
      provided_ CORN::OS::Directory_name_concrete *cropland_dir;                 //120415
     //provided_ Dairy_directory                  *Xdairy_dir;                    //140111
      provided_ CORN::OS::File_name_concrete *cropland_energy_estimation_xls_file;    //110920
      provided_ CORN::OS::File_name_concrete *cropland_energy_estimation_xlsm_file;   //110920
      provided_ CORN::OS::File_name_concrete *cropland_energy_estimation_exe_file;    //140111
 public:
   CAFE_Directory();
   CAFE_Directory(const CS::Suite_Directory &path_name,const wchar_t * directory_name);               //140111
   virtual void reset()                                               provision_;
 public:
//141110      const Dairy_directory &Dairy()           provision_;//140111
      // These should be moved into cropland directory
      const CORN::OS::Directory_name &cropland()                      provision_;//120415
      const CORN::OS::File_name &cropland_energy_estimation_xls()     provision_;//110920
      const CORN::OS::File_name &cropland_energy_estimation_xlsm()    provision_;//110920
      const CORN::OS::File_name &cropland_energy_estimation_exe()     provision_;//140111

};
//______________________________________________________________________________
class NIFA_Directory
: public FARM_Directory                                                          //141110
      // This may eventually be derived from CORN::Application_directory (or Suite directory)
{
 public:
   class Dairy_directory
   : public extends_ FARM_Directory::Dairy_directory
   {
    private:
      provided_ CORN::OS::File_name_concrete *nutrients_template_xlsm_file;
    public:
      //Dairy_directory();
      Dairy_directory
         (const NIFA_Directory &path_name
         ,const wchar_t *directory_name);
      virtual void reset()                                           provision_;
    public:
      const CORN::OS::File_name &nutrients_template_xlsm()  provision_;

   };
 public:
   NIFA_Directory();
   NIFA_Directory(const CS::Suite_Directory &path_name,const wchar_t * directory_name);               //140111
};
//______________________________________________________________________________

}
#endif
