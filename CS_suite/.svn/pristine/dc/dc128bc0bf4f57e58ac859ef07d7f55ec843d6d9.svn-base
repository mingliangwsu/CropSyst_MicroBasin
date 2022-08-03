161029 this program is probably obsolete now that there is the scenarios scheduler
#include "CropSyst/source/cs_scenario_directory.h"
#include "CropSyst/source/project/optimization/crop_production_function/CPF_water.h"
//CropSyst::Scenario_directory *scenario_dir;
//---------------------------------------------------------------------------
#include "CS_Suite/common_program_main_inc.cpp"
//______________________________________________________________________________
/*150419
void clear_CPF_dir(const CropSyst::Scenario_directory  &scenario_dir)
{
   scenario_dir.CPF_dir.recycle(false);
   // We need to make sure the directory exists in order to set the RootFolder
   scenario_dir.CPF_dir .create();
   scenario_dir.CPF_dir .subdirectory_path("water",scenario_dir.CPF_water_dir,false);
   scenario_dir.CPF_water_dir.create();
};
*/
namespace CORN { namespace OS {
File_system &file_system() { return CORN::OS::file_system_logical; }
}}
//________________________________________________________________
int main(int argc, const char *argv[])
{
   INSTANCIATE_CS_SUITE_DIRECTORY(argv[0]);                                      //150419
   nat16 CFP_percents_water = 0;
   CORN::OS::Directory_name_concrete   *scenario_directory = 0;
   CORN::OS::File_name_concrete        *format_filename = 0;
   // Default assumes scenario directory is CWD
   for (nat8 argi = 1; argi < argc; argi++)
   {

      bool arg_is_scenario = false;
      bool arg_is_format = false;

      CORN::OS::File_name_concrete potential_format_filename(argv[argi]);
      if (potential_format_filename.is_extension_ASCII("fmt") || (potential_format_filename.is_extension_ASCII("FMT")))
      {
         format_filename = new CORN::OS::File_name_concrete(potential_format_filename);
         arg_is_format = true;
      }
      else if (!scenario_directory)
      {

         CORN::OS::Directory_name_concrete *potential_scenario_directory = new CORN::OS::Directory_name_concrete(argv[argi],CORN::OS::directory_entry); //161029
         if (CORN::OS::file_system_engine.exists(*potential_scenario_directory))
         {
            scenario_directory = potential_scenario_directory;
            arg_is_scenario = true;
         } else
            delete potential_scenario_directory;
      }
      if (!arg_is_scenario && !arg_is_format)
      {
         if (isdigit(argv[argi][0]))
         {
            nat16 percent = CORN::cstr_to_nat32(argv[argi],10);
            CFP_percents_water |= (1 << (percent/10));
         }
      }
   }
   if (!scenario_directory) // if scenario not specified assume CWD is scenario
        scenario_directory = new CORN::OS::Directory_name_concrete;

   CropSyst::Crop_production_function_simulation *CPF_sim = 0;
   if (CFP_percents_water)
   {
      CPF_sim = new CropSyst::Crop_production_function_simulation
            (*scenario_directory,format_filename,CFP_percents_water);
   } else
   {  CORN::OS::File_name *irrigation_adjustment_filename =
         CORN::OS::file_system_engine.find_qualified_name_in_path
            (L"irrigation_adjustments.dat"
            ,*scenario_directory);
      if (irrigation_adjustment_filename)
         CPF_sim = new CropSyst::Crop_production_function_simulation
            (*scenario_directory,format_filename,*irrigation_adjustment_filename);
      delete irrigation_adjustment_filename;
   }

//150419    clear_CPF_dir(scenario_dir);
   bool CPF_abort = false;
   bool run_from_scenario = true;
   if (CPF_sim)
       CPF_sim->run(CPF_abort);
   delete CPF_sim;

/*150420 obsolete now CPF function is run from CS explorer (Not scenario editor)
  so CS explorer will already be open
   Ustring command("\"");
   command.append(CS::Suite_directory->CS_explorer_executable()); // (cs_suite_paths->get_cropsyst_model_exe());
   command.append("\" ");  //030516
   command.append(" \"");  //030516
   command.append(scenario_dir.CPF_water_dir); // Make sure filenames are quoted
   command.append("\"");
   PROCESS_INFORMATION process_info;
   STARTUPINFO  startup_info;
   GetStartupInfo(&startup_info);
   startup_info.dwFlags |= STARTF_USESHOWWINDOW;
   startup_info.wShowWindow = SW_NORMAL; // SW_HIDE; // SW_NORMAL;
   bool result = true;
      if (CreateProcess
            (0
            ,(char *)command.c_str()
            ,0 // default security
            ,0 // default security
            ,true
            ,CREATE_SEPARATE_WOW_VDM|NORMAL_PRIORITY_CLASS
            ,0  // current environment block
            ,0  // pointer to current directory name  (should be current)
            ,&startup_info // pointer to STARTUPINFO
            ,&process_info // pointer to PROCESS_INFORMATION
            ))
      {}
      else
         result =  false;
      // Must close process and thread handles or you get a memory leak.
      CloseHandle(process_info.hProcess);
      CloseHandle(process_info.hThread);
*/
   delete scenario_directory;
   return EXIT_SUCCESS;
}
//______________________________________________________________________________
