#ifndef CROPSYST_SIM_PCH_H
#define CROPSYST_SIM_PCH_H
// options.h must be first!
#include <corn/std/std_fstream.h>

#include <options.h>
//090818#include "options.h>
#include <corn/corn_pch.h>
#include <corn/format/format_PCH.h>
#include <UED/library/UED_PCH.h>
#include <corn/data_source/dbase_datasrc.h>
#include <common/recorder/recorder_datasrc.h>
//#include <common/weather/ET_ref.h>
#include <common/weather/weather.h>
#include <common/weather/stormgen.h>
#  include <common/weather/database/weather_database.h>
#include <common/weather/database/weather_UED_database.h>
#include <common/weather/database/weather_DAT_GEN_database.h>

#include "crop/crop_param.h"
#include "mgmt_types.h"
#include "mgmt_param.h"
#include "crop/crop_rows.h"
#include "cs_accum.h"
#include "soil/chemical_profile.h"
#include "cs_chem_pot_mineral_N.h"
#include "crop/crop_interfaced_cropsyst.h"
#include "cs_ET.h"
#include "cs_event.h"
#include "cs_UED_harvest.h"
#include "cs_irrdy.h"
#include "cs_mgmt.h"
#include "cs_operation_codes.h"
//091130#include "cs_rain.h"
//#include "cs_resid.h"
//140203 #include "cs_report.h"
#include "cs_scenario_directory.h"
#include "cs_scenario.h"
#include "cs_simulation.h"
#include "cs_till.h"
#include "cs_UED_daily.h"
#include "cs_vars.h"
#include "csvc.h"
//140203#include "cs_variables.h"

#include "crop/Crop_common.h"
//041207obs#include "crop_interface.h>
//131007 #include "crop/crop_transpiration.h"
#include "crop/crop_cropsyst.h"
//#include "crop_interfaced.h>

#ifdef CO2_V4
#include "crop/crop_CO2.h"
#endif
#include "crop/crop_n.h"
#include "desired_vars.h"

#include "fmt_param.h"
#include "land_unit_sim.h"
#include "mgmtevnt.h"
#include "pond.h"
#include "rot_param.h"
#include "soil/salt_interface.h"
#include "soil.h"
#include "soil/soil_param.h"
#include "soil/chemical_mass_profile.h"
#include "soil/chemicals_profile.h"
#include "soil/dynamic_water_entering.h"
#include "soil/erosion_RUSLE.h"
#ifdef NITROGEN
#  include "soil/nitrogen_profile.h"
#endif
//#include "soilfrzj.h>
//#include "soilfrz.h>
#include "soil/runoff.h"
#include "storm.h"
#include "watertab.h"
#include "wshedio.h"

#ifdef NITROGEN
#  include "organicn.h"
#endif

#  ifdef CHEM_PROFILE
#     include "soil/chemical_profile.h"
#     include "soil/chemicals_profile.h"
#     include "chemfile.h"
//140203 #     include "cs_variables.h"
#  endif
#include "cs_UED_db.h"
//070219 #include "UED_out.h>
#ifdef LADSS_MODE
#  include "LADSS.h"
#endif
////////////////////////////////////////////////
#include <common/recorder/recorder_datarec.h>
#include <common/recorder/recorder.h>
#include "static_phrases.h"
#include "cs_paths.h"
#include "csvc.h"

#  include "organic_matter/OM_residues_profile_abstract.h"
#  include <common/residue/residues_interface.h>

#endif
// cropsyst_sim_pch.h

