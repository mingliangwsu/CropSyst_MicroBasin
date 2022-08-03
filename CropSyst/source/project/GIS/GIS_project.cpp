

#ifdef USE_PCH
#include "simulation/CropSyst_sim_pch.h"
#else
#include <corn/OS/OS.h>
#include "arccs.h"
#include "soil_param.h"
#include "crop_param.h"
#include "mgmt_param.h"
#include <common/weather/loc_param.h>
#endif

#pragma hdrstop
#include <CropSyst/project/GIS/GIS_project.h>

//050629 This is probably obsolete, now use GIS_simulation and GIS_project_parameters
