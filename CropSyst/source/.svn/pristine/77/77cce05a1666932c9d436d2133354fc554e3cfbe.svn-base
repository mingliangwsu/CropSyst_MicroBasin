#  include "corn/OS/os.h"
#  include "soil/soil_param.h"
#  include "mgmt_param.h"
#  include "common/weather/loc_param.h"
#include "project/GIS/GIS_params.h"

//______________________________________________________________________________
GIS_Project_parameters::GIS_Project_parameters()
: coverage_PAT_filename      ("Coverage polygon attribute table (required).dbf")
, polygon_ID_attribute   ("cell_ID")   // This is a default value incase a PAT file is not specified
, equilibrate_years(0)
, perform_donatelli_analysis(false)
#ifdef NYI_V4
050202 Not yet implemented in V4
, pat(0)
, template_sim(0)
, GIS_parameters_DBF("GIS_parameters.dbf")
#endif
,recalibration_attribute()
,water_table_attribute  ()
{}
//_1999_________________________________________________________________________

#define dBase_field_name_max_len 12

bool GIS_Project_parameters::setup_structure(Data_record &data_rec,bool for_write)
{
   data_rec.set_current_section(LABEL_GIS);
      data_rec.expect_file_name(LABEL_coverage_PAT,            coverage_PAT_filename);
      data_rec.expect_string   (LABEL_polygon_ID_attribute,    polygon_ID_attribute,10);

      data_rec.expect_string   (LABEL_soil_attribute,          soil_attribute,dBase_field_name_max_len);

      data_rec.expect_string   ("uniform_sand_attribute",         uniform_sand_attribute,dBase_field_name_max_len);
      data_rec.expect_string   ("uniform_clay_attribute",         uniform_clay_attribute,dBase_field_name_max_len);
      data_rec.expect_string   ("soil_depth_attribute",        soil_depth_attribute,dBase_field_name_max_len);

      data_rec.expect_string   (LABEL_weather_attribute,       weather_attribute,dBase_field_name_max_len);

      data_rec.expect_string   (LABEL_rotation_attribute,      rotation_attribute,dBase_field_name_max_len);

      data_rec.expect_string   ("recalibration_attribute",     recalibration_attribute,dBase_field_name_max_len);

      data_rec.expect_string   ("water_table_attribute",       water_table_attribute,dBase_field_name_max_len);
      data_rec.expect_string   (LABEL_steepness_attribute,     steepness_attribute,dBase_field_name_max_len);

      data_rec.expect_string   (LABEL_init_PAW_attribute,      init_PAW_attribute,dBase_field_name_max_len);

      data_rec.expect_string   (LABEL_init_NO3_attribute,      init_NO3_attribute,dBase_field_name_max_len);
      data_rec.set_current_section(LABEL_analysis);
      data_rec.expect_bool(LABEL_donatelli,perform_donatelli_analysis,VV_bool_entry::form_true/*CROPSYST_VV_BOOL_FORM*/);
//NYI      data_rec.expect_bool("irrigation_everywhere",                  NYI_irrigation_everywhere);  // NYI currently assume if irrigation capabiliby class is blank, irrigation is infeasable
//NYI      data_rec.expect_bool("assume_irrigation_improves_capability",  NYI_assume_irrigation_improves_capability);  // if irrigation everywhere is enabled if this is true the capability class is improved by 1 class level
	return true;
}
//_2005-02-02___________________________________________________________________
#ifdef NYI_V4
050202 Not yet implemented in V4

void GIS_Project_parameters::setup_common_analysis_structures(const char *template_simulation_filename)
{
   if (!pat && coverage_PAT_filename.exists())
      pat = new Polygon_attribute_table
      (coverage_PAT_filename.c_str()
      ,polygon_ID_attribute.c_str()
      ,soil_attribute.c_str()
      ,steepness_attribute.c_str()
      ,init_PAW_attribute.c_str()
      ,init_NO3_attribute.c_str()
      ,weather_attribute.c_str()
      ,rotation_attribute.c_str()
      );

   VV_File simulation_file(template_simulation_filename);
   template_sim = new CropSyst_scenario;
   simulation_file.get(*template_sim);// Load the template

//000211       In order to prevent filling up the project working directory,
//             We now take move the polygon/cell simulations
//             to the working subdirectory: sim_run
   CORN::Directory_name curr_dir;
   CORN::Smart_directory_name sim_run_dir;
   curr_dir.subdirectory_path("sim_run",sim_run_dir);
   sim_run_dir.create();
}
//______________________________________________________________________________
#ifdef NYI
050202 may do this a different way in V4
void GIS_Project_parameters::set_default_filenames(const ACS_filename &acs_filename)
{
   coverage_PAT_filename.set(acs_filename.c_str()); // default set rotation filename to match simulation
   coverage_PAT_filename.set_ext("dbf");
   template_simulation_filename.set(acs_filename.c_str()); // default set rotation filename to match simulation
   template_simulation_filename.set_ext("sim");
}
#endif
//______________________________________________________________________________
const char *GIS_Project_parameters::get_relative_filename(const char *filename,const char *ext) const
{
   CORN::File_name rel_fname(filename,ext);
   rel_fname.set_path(ARCCS_directory_rel);
   common_return_buffer.assign(rel_fname);
   return rel_fname.c_str();
}
//_2003-02-20___________________________________________________________________
#endif

