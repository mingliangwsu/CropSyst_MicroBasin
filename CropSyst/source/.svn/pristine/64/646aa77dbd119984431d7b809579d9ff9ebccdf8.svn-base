/*

   This program is used to test the GIS run.

   It should do the same thing as the GIS_runner
   but since it doesn't have the GUI it sould compile faster.

   I use this to test that the processing is correct before having
   to compile it in Builder which is slow.

*/
#include <CropSyst/Project/multirun/multi_run_console.h>
#include <cropsyst/cpp/cs_paths.h>
#include "CropSyst/source/cs_project_directory.h"
#include <CropSyst\cpp\cs_project.h>
#include <corn/data_source/vv_file.h>
#include <CropSyst/project/GIS/GIS_simulation.h>

class   LADSS_Cropsyst_model;
LADSS_Cropsyst_model *LADSS_cropsyst_model = 0;


void main(int argc, const char *argv[])
{

// Test command line:
//    "C:\Simulation\Projects\PM-10Simulation.csp"
// D:\javier\PM-10Project\PM-10Simulation.csp

   TMulti_run_form  *multi_run_form = new TMulti_run_form;

   setup_CS_suite_paths("C:\\CS_suite_4\\CropSyst\\Cropsyst_4.exe");
       #define project_filename argv[1]

       CropSyst_project project_params; // (cs_proj_dir);
       project_params.set_file_name(project_filename,false);
       VV_File GIS_project_file(project_filename);
       GIS_project_file.get(project_params);
       GIS_simulation GIS_simulator(project_params,project_filename,0/*check needed GIS_run_form for console*/);
      GIS_simulator.set_run_form(multi_run_form);

      multi_run_form->bind_to(&GIS_simulator/*,GIS_run_form*/);

      GIS_simulator.run();
   setdown_CS_suite_paths();
};
