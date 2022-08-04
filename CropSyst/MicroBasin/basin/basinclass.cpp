#include "basinclass.h"
#include "basincellclass.h"
#include "util/pubtools.h"
//#include "corn/datetime/date.hpp"
#include "control/allcontrolclass.h"
#include "stdlib.h"
#include "stdio.h"
#include <vector>
#include "math.h"
#include "soil/hydraulic_properties.h"
#include "chemical_types.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "common/biometeorology/ET_reference_FAO.h"
#ifndef __BCPLUSPLUS__
#include <omp.h>
#endif
#include <iomanip>

#if (defined(TRIVIAL_TEST))
#include "corn/data_source/vv_file.h"
#endif

#include "util/constants.h"
#include "util/pubtools.h"
#ifdef MBVB_SOIL
#  include "soil/clssoil.h"
#else
#  include "soil.h"
#endif
#ifdef MBVB_INFILTRATION
#else
#include "pond.h"
#endif

#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif

#ifdef CROPSYST_VERSION
#include "common/residue/residues_interface.h"                                   //160616LML
#include "soil/chemicals_profile.h"
#include "soil/chemical_mass_profile.h"
#include "crop/crop_N_interface.h"
#include "corn/data_source/vv_file.h"
#include "chemical_types.h"
#endif
#include "corn/container/unilist.h"

#ifdef CROPSYST_SOILFILE
#include "CORN/data_source/vv_file.h"
#endif

#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/data_source/command_options_datasrc.h"                            //190909LML
#include "corn/OS/file_system_engine.h"
#include "corn/chronometry/date_32.h"
#ifdef DEBUG_LIU_OUT_CSV
std::ofstream fstm_daily_basin_out;
bool cell_output_head_printed = false;
bool basin_output_head_printed = false;                                          //150918LML
void print_cell_daily_for_debug_head(std::ofstream &outf,BasinCellClass *cell);
void print_cell_daily_for_debug(std::ofstream &outf, const Date &day, const BasinCellClass *cell);
void print_basin_daily_for_debug_head(std::ofstream &outf);
void print_basin_daily_for_debug(std::ofstream &outf, const Date &day, const BasinClass &basin);
#endif

#include "CropSyst/source/organic_matter/OM_residues_profile_abstract.h"

#ifdef VB_SAME_CSV_OUTPUT
#include "CropSyst/MicroBasin/output/outputmainclass.h"
#endif

//______________________________________________________________________________
BasinClass::BasinClass
( int argc, const char *argv[])                                                  //160406RLN
:
command_line_options(argc,argv)
, CS::Simulation_engine(command_line_options)                                    //160909LML added arguments
, command_line_arguments(ControlRef.ID/*160909LML ,argc,argv*/)                  //160406RLN 160909LML obs?
, ControlRef(scenario_directory_name)                                            //160301
, scenario_directory_name() // default to CWD
, output_directory_name(scenario_directory_name,L"Output")
,control_file_name_unqual(L"MicroBasin.CropSyst_scenario")                       //150629RLN
,total_hourth(-1L)                                                               //150701 (RLN moved from start)
,model_name("CropSyst MicroBasin")
,Hour_Head_Printed(false)
,Daily_Head_Printed(false)
,Daily_Growth_Head_Printed(false)
#ifdef CROPSYST_VERSION
, project_database_directory(0)                                                  //160301RLN
,basin_area_km2(0.0)                                                             //150921LML
,scenario_filename_extension(L"CropSyst_scenario")                               //160118RLN
#ifdef CELL_METEOROLOGY
   //160808 becoming obsolete eventually delete
, sun(today_driving,centroid)                                                    //151206_150730RLN
, sun_days
   (centroid.get_longitude_radians()
   ,centroid.get_longitude_radians())                                            //150708RLN
, sun_hours(sun_days, centroid.get_latitude_dec_deg())                           //151206RLN_160119LML_150708RLN
/*160810 RLN now pointer
,extraterrestrial_solar_irradiance
   (centroid                                                                     //151206RLN
   ,sun_days
   ,sun_hours
   ,today_driving)
*/
#else
, meteorology(0)                                                                 //160808
#endif
, extraterrestrial_solar_irradiance(0)                                           //160810
#endif
{}
//______________________________________________________________________________
BasinClass::~BasinClass()
{
    #ifdef Destruct_Monitor
    std::clog<<"~BasinClass:"<<std::endl;
    #endif
    clearMem();
    #ifdef Destruct_Monitor
    std::clog<<"~BasinClass done."<<std::endl;
    #endif
    #ifndef CELL_METEOROLOGY
    delete pWeatherDaily;
    #endif
}
//______________________________________________________________________________
void BasinClass::initMem()
{
    std::clog<<"initMem...\n";
    basin_cells.resize(num_cells,NULL);
    //160317LML long innerid(0);
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (int row = 0; row < nrows; row++) {
        for (int col = 0; col < ncols; col++) {
            if (gGridMask.IsValidCell(row,col)) {
                long idindex = inner_id[row][col];
                long soiltype = gSoilType.getValue(row,col);
                long idsoilproperty = getInnerIDFromVectorList<long>(l_soiltypes,soiltype);
                /*160809RLN this wouldn't work
                long rottation = gRotationID.getValue(row,col);
                long rotoarameter_index = getInnerIDFromVectorList<long>(l_rotationtypes,rottation);
                */
                /*
                #pragma omp critical
                {
                std::clog<<"\tinnerid:"<<idindex
                         <<"\tID#:"<<gGridID.getValue(row,col)
                         <<"\tsoiltype:"<<soiltype
                         <<"\tidsoilproperty:"<<idsoilproperty
                         <<"\trottype:"<<rottation
                         <<"\trotation_index:"<<rotoarameter_index
                         <<"\tmask:"<<gGridMask.getValue(row,col)
                         <<std::endl;
                }*/
                if (idsoilproperty < 0) {
                    std::cerr<<"ERROR!!!\trow:"<<row<<"\tcol:"<<col<<"\t has wrong soil ID."<<std::endl;
                    exit(1);
                }
                SoilProfileClass *pSoilProfileMutable = new SoilProfileClass(ControlRef);
                pSoilProfileMutable->copy_soilprofile(*parrSoilProfile[idsoilproperty]);

                basin_cells[idindex] = new BasinCellClass(
                            *this
                            ,ControlRef                                          //160301RLN
                            ,today//.ref_date32()                                  //150630 170615LML use ref_date
                            #ifdef CROPSYST_VERSION
                            ,*project_database_directory                         //160301_150723RLN
                            #ifdef CELL_METEOROLOGY
                               //160808 becoming obsolete eventually delete
                            ,sun
                            ,extraterrestrial_solar_irradiance                   //150708RLN
                            #else
                            ,*meteorology                                         //160808
                            #endif
                            //160801 ,sun.ref_day_length_hours_today()                    //150730RLN
                            #endif
                            #ifdef MBVB_INFILTRATION
                            ,pSoilProfileMutable
                            ,parrSoilProfile[idsoilproperty]
                            #endif
                            ,gLatitude.getValue(row,col)                         //150817
                            ,gLongitude.getValue(row,col)                        //150817
                            ,gElev.getValue(row,col)                             //150817
                            ,parrInitSoilState                                    //160317
                            ,idsoilproperty
                            /*160808RLN this wouldn't work
                            #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
                            ,*parrRotation_params[rotoarameter_index]            //160317LML
                            #endif
                            */
                            );
            }
        }
    }
    const int MaxLayers = ControlRef.getMaxSoilLayers();
    //160317LML inner_id.resize(gGridID.getNrows());
    //160317LML for (int i = 0; i < gGridID.getNrows(); i++) inner_id[i].resize(gGridID.getNcols());
    
    Theta.resize(num_cells);
    Theta_s.resize(num_cells);
    K_Theta.resize(num_cells);
    L_thickness.resize(num_cells);
    Hydro_Standard_Slope.resize(num_cells);
    InFlow_m.resize(num_cells);
    OutFlow_m.resize(num_cells);
    TempInFlow_m.resize(num_cells);
    TempOutFlow_m.resize(num_cells);
    UpFlow_m.resize(num_cells);
    Unused_store_m.resize(num_cells);
    Temp_Cell_Layer_Var.resize(num_cells);
    TotalDownhillflow.resize(num_cells);
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (long i = 0; i < num_cells; i++){
        Theta[i].resize(MaxLayers);
        Theta_s[i].resize(MaxLayers);
        K_Theta[i].resize(MaxLayers);
        L_thickness[i].resize(MaxLayers);
        Hydro_Standard_Slope[i].resize(MaxLayers);
        InFlow_m[i].resize(MaxLayers);
        OutFlow_m[i].resize(MaxLayers);
        TempInFlow_m[i].resize(MaxLayers);
        TempOutFlow_m[i].resize(MaxLayers);
        UpFlow_m[i].resize(MaxLayers);
        Unused_store_m[i].resize(MaxLayers);
        Temp_Cell_Layer_Var[i].resize(MaxLayers);
        TotalDownhillflow[i].resize(MaxLayers);
    }
    //Need seperate state variables from flux variables
    Ponded_m.resize(num_cells,0);
    //(mm) [innerid] Ponded from local grid
    Runoff_m.resize(num_cells,0);
    OutFlowSoluteEachDir.resize(num_cells);// = alloc_4d_array<double>(num_cells,MaxLayers,8,ControlRef.getSoluteSpecies(),"BasinClass::OutFlowSoluteEachDir");
    TempOutFlowSoluteEachDir.resize(num_cells);// = alloc_4d_array<double>(num_cells,MaxLayers,8,ControlRef.getSoluteSpecies(),"BasinClass::TempOutFlowSoluteEachDir");
    //151028LML SoluteConc.resize(num_cells);
    SoluteAmount.resize(num_cells);
    TempSoluteConc.resize(num_cells);
    TempSoluteAmount.resize(num_cells);
    OutFlowEachDir_m.resize(num_cells);
    TempOutFlowEachDir_m.resize(num_cells);
    InFlowSolute.resize(num_cells);
    UpFlowSolute.resize(num_cells);
    UpFlowSoluteConc.resize(num_cells);                                          //160324LML
    BalanceFlowSolute.resize(num_cells);
    OutFlowSolute.resize(num_cells);
    TempInFlowSolute.resize(num_cells);
    TempOutFlowSolute.resize(num_cells);
    UpFlowSoluteRate.resize(num_cells);
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (long i = 0; i < num_cells; ++i) {
        OutFlowSoluteEachDir[i].resize(MaxLayers);
        TempOutFlowSoluteEachDir[i].resize(MaxLayers);
        //151028LML SoluteConc[i].resize(MaxLayers);
        SoluteAmount[i].resize(MaxLayers);
        TempSoluteConc[i].resize(MaxLayers);
        TempSoluteAmount[i].resize(MaxLayers);
        OutFlowEachDir_m[i].resize(MaxLayers);
        TempOutFlowEachDir_m[i].resize(MaxLayers);
        InFlowSolute[i].resize(MaxLayers);
        UpFlowSolute[i].resize(MaxLayers);
        UpFlowSoluteConc[i].resize(MaxLayers);                                   //160324LML
        BalanceFlowSolute[i].resize(MaxLayers);
        OutFlowSolute[i].resize(MaxLayers);
        TempInFlowSolute[i].resize(MaxLayers);
        TempOutFlowSolute[i].resize(MaxLayers);
        UpFlowSoluteRate[i].resize(MaxLayers);
        for (int j = 0; j < MaxLayers; j++)
        {   const int numspecis = ControlRef.getSoluteSpecies();
            OutFlowSoluteEachDir    [i][j].resize(8);
            TempOutFlowSoluteEachDir[i][j].resize(8);
            //151028LML SoluteConc[i][j].resize(numspecis);
            SoluteAmount            [i][j].resize(numspecis);
            TempSoluteConc          [i][j].resize(numspecis);
            TempSoluteAmount        [i][j].resize(numspecis);
            OutFlowEachDir_m        [i][j].resize(8);
            TempOutFlowEachDir_m    [i][j].resize(8);
            InFlowSolute            [i][j].resize(numspecis);
            UpFlowSolute            [i][j].resize(numspecis);
            UpFlowSoluteConc        [i][j].resize(numspecis);                    //160324LML
            BalanceFlowSolute       [i][j].resize(numspecis);
            OutFlowSolute           [i][j].resize(numspecis);
            TempInFlowSolute        [i][j].resize(numspecis);
            TempOutFlowSolute       [i][j].resize(numspecis);
            UpFlowSoluteRate        [i][j].resize(numspecis);
            for (int dir = 0; dir < 8; dir ++) {
                OutFlowSoluteEachDir    [i][j][dir].resize(numspecis);
                TempOutFlowSoluteEachDir[i][j][dir].resize(numspecis);
            }
        }
    }
    
    KS.resize(MaxLayers);
    vHydroElevation.resize(MaxLayers);
    vSum_Downhillslopes.resize(MaxLayers);
    vHydroStandardslope.resize(MaxLayers);
    comb_Share_flow.resize(MaxLayers);
    v_Share_flow.resize(MaxLayers);
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (int i = 0; i < MaxLayers; ++i) {
        int nrows = gGridMask.getNrows();
        int ncols = gGridMask.getNcols();
        KS[i].resize(nrows);
        vHydroElevation[i].resize(nrows);
        vSum_Downhillslopes[i].resize(nrows);
        vHydroStandardslope[i].resize(nrows);
        comb_Share_flow[i].resize(nrows);
        v_Share_flow[i].resize(nrows);
        for (int j = 0; j < nrows; j++) {
            KS[i][j].resize(ncols);
            vHydroElevation[i][j].resize(ncols);
            vSum_Downhillslopes[i][j].resize(ncols);
            vHydroStandardslope[i][j].resize(ncols);
            comb_Share_flow[i][j].resize(ncols);
            v_Share_flow[i][j].resize(ncols);
            for (int k = 0; k < ncols; k++) {
                comb_Share_flow[i][j][k].resize(9);
                v_Share_flow[i][j][k].resize(9);
            }
        }
    }
    CellFrictionSlope_X.resize(num_cells,0);       
    CellFrictionSlope_Y.resize(num_cells,0);       
    CellFlowIn_X.resize(num_cells,0);              
    CellFlowIn_Y.resize(num_cells,0);              
    CellFlowOut_X.resize(num_cells,0);             
    CellFlowOut_Y.resize(num_cells,0);             
    ManningCoef.resize(num_cells,0);               
    CellWaterDepth.resize(num_cells,0);            
    InitialCellWaterDepth.resize(num_cells,0);     
    OldCellWaterDepth.resize(num_cells,0);         
    const int basin_out_hours = 24 * ControlRef.getStartDate().days_between(/*(const Date_time &)*/ControlRef.getEndDate(),true);
    hourlyBasinSurfaceOutFlow_m3.resize(basin_out_hours,0);
    hourlyBasinDrainage_m3.resize(basin_out_hours,0);                 
    hourlyBasinDrainage_DIN_kg.resize(basin_out_hours,0);                        //170417LML
    hourlyBasinLateralOutFlow_m3.resize(basin_out_hours,0);           
    const int num_species = ControlRef.getSoluteSpecies();
    //hourlyBasinDrainageSolute_kg.resize(basin_out_hours);                        //150921LML
    hourlyBasinLateralOutFlowSolute_kg.resize(basin_out_hours);
    hourlyBasinSurfaceOutFlowSolute_kg.resize(basin_out_hours);
    for (int i = 0; i < basin_out_hours; i++) {
        //hourlyBasinDrainageSolute_kg[i].resize(num_species);                     //150921LML
        hourlyBasinLateralOutFlowSolute_kg[i].resize(num_species);
        hourlyBasinSurfaceOutFlowSolute_kg[i].resize(num_species);
    }
    //150519
    int crop_management_zones = l_crop_management_zones.size();
    Nitrate_Apply_By_Crop_Management_Zones.resize(crop_management_zones);
    Nitrate_Content_In_Crop_Management.resize(crop_management_zones);
    Ammounium_Apply_By_Crop_Management_Zones.resize(crop_management_zones);
    Ammonium_Content_In_Crop_Management.resize(crop_management_zones);
    Number_Crop_Management_Zones.resize(crop_management_zones);
}
//______________________________________________________________________________
void BasinClass::clearMem()
{
    int d_soil_layer = ControlRef.getMaxSoilLayers();
	#ifndef CROPSYST_WEATHER
    for (int i = 0; i < num_weather_stations; i++) {
        delete weather_station_annual_hourly_data[i];
    }
	#endif
    for (long i = 0; i < num_cells; i++) {
        delete basin_cells[i];
    }
    for (int i = 0;i < l_soiltypes.size(); i++) {
        delete parrSoilProfile[i];
    }
}
//______________________________________________________________________________
long BasinClass::NumCells()
{  return(num_cells);
}
//______________________________________________________________________________
bool BasinClass::initialize()                                    initialization_ //141221
{   bool initialized = true;                                                     //141221


   //160301RLN Moved from main()
   context_discovery->know_leaf(scenario_directory_name);                         //160301RLN
    /*161205RLN
   project_directory_name
      = context_discovery.set_level_as_root(CS::File_discovery::project_level);     //160301RLN
   assert(project_directory_name);
   // if the project level directory is not being found tell Roger!              //160307RLN

   project_directory = new CropSyst::Project_directory(*project_directory_name,false);
   */
/*
   CORN::OS::Directory_name *project_database_directory =                       //161004RLN
      CORN::OS::file_system_engine.find_file_name
        (L"Database",*project_directory,CORN::OS::File_system::subdirectory_recursion_inclusive);
*/

   //161205 CORN::OS::Directory_entry_name_concrete *database_dir_name = new CORN::OS::Directory_entry_name_concrete(*project_directory, L"Database");

   // This is just a hack as this version of basinclass assumes there is
   // only one project Database directory
   CORN::Unidirectional_list database_dirs;
   CORN::OS::file_system_engine.list_DENs
         (scenario_directory_name,0,&database_dirs
         ,CORN::Inclusion("Database",true)
         ,CORN::OS::File_system::superdirectory_recursion_exclusive);
   CORN::OS::Directory_entry_name_concrete *database_dir_name
      = dynamic_cast<CORN::OS::Directory_entry_name_concrete *>(database_dirs.pop_first());

   //if (argument.verbose)
   std::clog << "scenario_directory_name:"    << scenario_directory_name.c_str() << std::endl;

   if (!database_dir_name)
   {  std::cerr << "Unable to find Database directory" << std::endl;
      return 1;
   }
   project_database_directory = new CS::Database_directory
           (database_dir_name);
           //(*project_directory,false, L"Database");

    // BasinClass (CS_engine now already has its own discovery CS::File_discovery discovery; //CWD is leaf

       // The centroid geolocation isn't necessarily in the project directory
       // It will typically be in the Scenarios directory

    //160301 now full member instance Geolocation centroid;                                                        //151206RLN
    std::string ISO_6709_unused;
    if (!context_discovery->get_geolocation(scenario_directory_name,"location",centroid,ISO_6709_unused))     //151206RLN
    {  initialized = false;                                                      //151206RLN
       std::cerr << "Unable to find/load centroid geolocation (add a CS_geocoordinate CS_geolocation file to the scenario directory." << std::endl;     //151206RLN
       return EXIT_FAILURE;
    }

    //gridid_name: ID for each grid cell; also functions as basin mask
    //int idir;
    //int down_inner_id,up_inner_id;
    //gFlowDir.readAsciiGridFile(ControlRef.flowdir_name);

    //150629 RLN initializeWeatherStations moved from main()
    // inorder to accomodate Simulation_engine
    #ifdef CROPSYST_WEATHER
    #else
    //Initializing Weather Stations
    initializeWeatherStations();
    #endif
    #ifdef LIU_DEBUG
    std::clog<<"Weather Stations is initialized!\n";
    #endif

#ifdef LIU_DEBUG
    std::clog<<"InitializeBasin ..."<<std::endl;
    std::clog<<"gGridMask:"<<ControlRef.gridmask_name<<std::endl;
#endif

    gGridMask           .readAsciiGridFile(ControlRef.gridmask_name           .c_str());  //150708RLN
    gGridOutputMask     .readAsciiGridFile(ControlRef.gridoutputmask_name     .c_str());  //151007LML
    gLatitude           .readAsciiGridFile(ControlRef.latitude_name           .c_str());  //150708RLN
    gLongitude          .readAsciiGridFile(ControlRef.longitude_name          .c_str());  //150708RLN
    gGridID             .readAsciiGridFile(ControlRef.gridid_name             .c_str());  //150708RLN
    gOutlets            .readAsciiGridFile(ControlRef.outlets_name            .c_str());  //150708RLN
    gElev               .readAsciiGridFile(ControlRef.elev_name               .c_str());  //150708RLN
    gSlop               .readAsciiGridFile(ControlRef.slop_name               .c_str());  //150708RLN
    gAspect             .readAsciiGridFile(ControlRef.aspect_name             .c_str());  //150708RLN
    gArea               .readAsciiGridFile(ControlRef.area_name               .c_str());  //150708RLN
    gSoilType           .readAsciiGridFile(ControlRef.soiltype_name           .c_str());  //150708RLN
    gRotationID         .readAsciiGridFile(ControlRef.croprotation_name       .c_str());  //150708RLN
    gCropManagementZone .readAsciiGridFile(ControlRef.cropmanagementzone_name .c_str());  //150708RLN   //LML 150515
    //gAnnualTavg.readAsciiGridFile(ControlRef.annualtavg_name);
    #ifdef MACA_V1_MBMET
    gWeatherStationID   .readAsciiGridFile(ControlRef.weatherstationID_name   .c_str());  //150708RLN
    #endif
    num_cells = gGridMask.getCellNumValid();
#ifdef LIU_DEBUG
    std::clog<<"Basin Cells:"<<num_cells<<std::endl;
#endif
    //Initilize soil properties (soil)


    //08032022LML moved to here
    if (ControlRef.use_even_soil_N_and_FC) {
        if (ControlRef.readInitialSoilState() != 0) {
            std::cerr << "Initialization of soil state failed!\n";
            exit(-1);
        }
    }

    initializeSoilProperties();



    /*160808RLN this would not work
    #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
    initializeRotationParameters();                                              //160317LML
    #endif
    */
    initializeCropManagementZones();                                             //150519

    #ifndef CELL_METEOROLOGY
    // Meteorology must be setup before calling initMem
       //160808 becoming permanent eventually delete the #ifndef lines
    meteorology = new CS::Land_unit_meteorological                               //160808
        (today.ref_date32()                                                      //170615LML replaced with ref_date32
        ,centroid
        ,ControlRef.snow_pack_model_labeled.get());
   // There is now one weather for the entire basin
   // There is no need for each cell to have its own weather
   sub_elements.append(meteorology); // submit?                                 //160817
    #ifdef CROPSYST_WEATHER
    // NYI need weather database daily and hourly
    meteorology->know_weather_spanning(XXXX);                                    //160810RLN
    meteorology->know_weather_provider(XXXX);                                    //160811RLN
    #else
    pWeatherDaily = new WeatherStateDailyClass                                   //160810RLN
        #ifdef CROPSYST_VERSION
        (today,centroid
        #ifdef CELL_METEOROLOGY
        //160808 becoming obsolete eventually delete,
        ,extraterrestrial_solar_irradiance_basin                                 //151222
        ,sun_basin_.ref_day_length_hours_today()
        #else
        ,meteorology->provide_solar_irradiance_extraterrestrial()
        ,meteorology->provide_sun().ref_day_length_hours_today()
        #endif
        );                                                                       //151206_150730RLN
        #else
        ();
        #endif
    meteorology->know_weather_spanning(*pWeatherDaily);                          //160810RLN
    meteorology->know_weather_provider(&(pWeatherDaily->daily_provider));        //160811RLN
    meteorology->provide_ET_reference();                                         //160811RLN
    #endif
//    initialized &= meteorology->provide_everything();                                           //160811
   /*160811 continue meteorology should provide as needed.
   extraterrestrial_solar_irradiance = new xxxxx
       (centroid                                                                     //151206RLN
       ,sun_days
       ,sun_hours
       ,today_driving)
    meteorology->know_extraterrestrial_solar_irradiance(*extraterrestrial_solar_irradiance); //160808
    sub_elements.append(meteorology);                                            //160808
    */
    #endif

    initMem();
    int trows = gGridMask.getNrows();
    int tcols = gGridMask.getNcols();

#ifdef LIU_DEBUG
    std::clog<<"Spatial data reading...\n";
#endif
    //Set basin information
    //inner id is from upper-left to lower-right
    #ifdef MACA_V1_MBMET
    weather_station_list_in_study_domain.clear();
    #endif
    //160317LML long gridcell(-1L);
    int total_outlets(0);
    double basinareakm2(0.0);                                                    //160317LML
    #pragma omp parallel for /*170713 num_threads(NUMCORES_TO_USE)*/ reduction(+:total_outlets,basinareakm2)
    for (int row = 0; row < trows; row++) {
        for (int col = 0; col < tcols; col++) {
            //160317LML inner_id[row][col] = -1L;
            if (gGridMask.IsValidCell(row,col)) {
                //160317LML gridcell++;
                long idindex = inner_id[row][col];
                BasinCellClass *cell = basin_cells[idindex];
                int outlet = gOutlets.IsValidCell(row,col) ? gOutlets.getValue(row,col) : 0;
                long soiltype = gSoilType.getValue(row,col);
                cell->setCol(col);
                cell->setRow(row);
                cell->setInnerId(idindex);
                cell->setCellId(gGridID.getValue(row,col));
                cell->setGridType(outlet);
                if (cell->isOutlet()) total_outlets++;
                //basin_cells[gridcell].setFlowDir(gFlowDir.getValue(row,col));
                //150817LML cell->setElev(gElev.getValue(row,col));
                cell->setSlop(gSlop.getValue(row,col));
                cell->setAspect(gAspect.getValue(row,col));
                cell->setArea(gArea.getValue(row,col));
                basinareakm2 += cell->getArea() * 1.0e-6;                      //150921LML
                //150817LML cell->setLatitude(gLatitude.getValue(row,col));
                //150817LML cell->setLongitude(gLongitude.getValue(row,col));
                //150813LML #ifndef CROPSYST_VERSION
                cell->setCropRotationID(gRotationID.getValue(row,col));
                //150813LML #endif
                cell->setCropManagementZone(gCropManagementZone.getValue(row,col)); //LML 150515
                long innerid = getInnerIDFromVectorList<long>(l_crop_management_zones,cell->getCropManagementZone());
                cell->setCropManagementZoneInnerID(innerid);                     //150519
                #ifdef MACA_V1_MBMET
                cell->setWeatherStationID(gWeatherStationID.getValue(row,col));
                weather_station_list_in_study_domain.push_back(gWeatherStationID.getValue(row,col));
                #endif
                //basin_cells[gridcell]->setAnnualMeanTemp(gAnnualTavg.getValue(row,col));
                cell->setLength(gArea.getCellsize());  //Assume cell length is cell size
                //basin_cells[gridcell].setNumUpgrids(0);
                cell->setSoilID(soiltype);   //
                //Initilize soil profile properties
                #ifdef MBVB_INFILTRATION
                cell->pSoilProfile->setSoilID(soiltype);
                #endif
                //basin_cells[gridcell]->pSoilProfile->assignParametersValues(0);  //Need Check
                cell->upGrids.clear();      //Initialize the upstream grid cell list
                cell->downGrid = NULL;
                cell->set_debug_output(gGridOutputMask.getValue(row,col) == 1 ? true : false); //151007LML
                //cell->scenario_directory = provide_scenario_directory_name();   //150730LML
                #ifdef MBVB_SOIL
                cell->pSoilState->ClearStateVariables();                         //160317LML
                #else
                // CropSyst soil has is own initialization
                #endif
                #ifdef CELL_METEOROLOGY
                // meteorology_site should be initialized by basin               //160808RLN
                //160808 becoming obsolete eventually delete
                cell->meteorology_site.initialize();                             //160317LML
                #endif
                //160317LML initialized &= cell->initialize();                               //141221RLN
                //160317LML std::clog<<"Initialized Cell#"<<cell->getInnerID()<<std::endl;
            }
        }
    }
    basin_area_km2 = basinareakm2;                                               //160317LML
    //#pragma omp parallel for num_threads(NUMCORES_TO_USE)
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        cell->initialize();                               //141221RLN
        std::clog<<"Initialized Cell#"<<cell->getInnerID()<<std::endl;
    }
//170404LML #ifdef PREDEFINE_N_APPLICATION_PER_CELL
    if (ControlRef.auto_N_grid_option.get() != AUTO_N_DEFAULT)
        readPredefinedNFertilization();                                          //170320LML
//170404LML #endif
    #ifdef MACA_V1_MBMET
    weather_station_list_in_study_domain.sort();
    weather_station_list_in_study_domain.unique();
    num_weather_stations_over_study_domain = weather_station_list_in_study_domain.size();
    for (long i = 0; i < num_cells; i++) {
        int weatherid = basin_cells[i]->getWeatherStationID();
        std::list<int>::iterator p = std::find(weather_station_list_in_study_domain.begin()
                                               ,weather_station_list_in_study_domain.end()
                                               ,weatherid);
        basin_cells[i]->index_weather_station_data = std::distance(weather_station_list_in_study_domain.begin(),p);

        basin_cells[i]->index_weather_station_info = getInnerIDWeatherStation(weatherid);
    }
    #else
    num_weather_stations_over_study_domain = num_weather_stations;
    #endif


    #ifdef VBBASIN_STRUCTURE
    double **tempelev = alloc_2d_array<double>(trows,tcols,"tempelev");
    double **tempelevout = alloc_2d_array<double>(trows,tcols,"tempelev");
    copy_2d_array<double>(gElev.getValueArray(),tempelev,trows,tcols);
    calcSurroundingElevations(tempelev,tempelevout);
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)//schedule(dynamic,1)
    for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
            #ifdef MVBV_SOIL
            cell->pSoilProcess->initialize();                                    //160317LML
            #endif
            double aspect,slope;
            calcMainSlopesAndAspect(tempelevout,
                                    cell->getRow(),
                                    cell->getCol(),
                                    cell->getLength(),
                                    aspect,slope);
            cell->setSlop(slope);
            cell->setAspect(aspect);
            double min_elev = getMinElevAround(cell->getRow(),cell->getCol());   //150526
            cell->setMinElevNeighbors(min_elev);                                 //150526
//170404LML #ifdef PREDEFINE_N_APPLICATION_PER_CELL
            if (predefined_N_fertilization_kgN_per_ha.size() > 0)
               cell->setPredefinedNFertilization(predefined_N_fertilization_kgN_per_ha[i],predefined_N_fertilization_crop_name);
//170404LML #endif
    }
    delete_2d_array(tempelev,trows);
    delete_2d_array(tempelevout,trows);
    #endif
    
    
    //LML 140904 handling outlets
    //if (total_outlets > 0) {
    //    parr_outlet_inner_id_list = alloc_1d_array<long>(total_outlets,"parr_outlet_inner_id_list");    //LML 140904
    //}
    int max_rotation_years = 0;                                                  //150621LML
    num_outlets = total_outlets;
    total_outlets = 0;
    parr_outlet_inner_id_list.clear();
    for (long i = 0; i < num_cells; i++) {
        //Initialize outlets lists
        BasinCellClass *cell = basin_cells[i];
        if (cell->isOutlet()) {
            parr_outlet_inner_id_list.push_back(i);
            total_outlets++;
        }
        for (int d = 0; d < 8; d++) {
            long nb_cell = getNeighborInnerID(i,d);
            cell->setNeighborIndex(d,nb_cell);
        }
        long left_cell = cell->getNeighborIndex(NB_W);//getNeighborInnerID(i,NB_W);
        long upper_cell = cell->getNeighborIndex(NB_N);
        if (left_cell >= 0)
            cell->setCellBedslopeX((basin_cells[left_cell]->getElev() - cell->getElev())
                                    / cell->getLength());
        else cell->setCellBedslopeX(0.0);
        if (upper_cell >= 0)
            cell->setCellBedslopeY((basin_cells[upper_cell]->getElev() - cell->getElev())
                                    / cell->getLength());
        else cell->setCellBedslopeY(0.0);
        //Initialize properties for lateral flows
        ManningCoef[i]= cell->pSoilProfile->Manning_coef;
        int layers = cell->pSoilProfile->NumberOfLayers();
        for (int layer = 1; layer <= layers; layer++) {
            //LML 140905 Since the Theta_s is changing because of various ice content, it will initialized in every hourly loop.
            //LML 140905 Theta_s[i][layer] = basin_cells[i]->pSoilProfile->get_saturation_water_content_volumetric(layer,ICE_WATER_CONTENT_RELEVENCE_UNKNOWN_140822)/*LML 140820 Saturation_Water_Content[layer]*/;
            L_thickness[i][layer] = cell->pSoilProfile->get_thickness_m(layer);
        }
        #ifdef CROPSYST_VERSION
        max_rotation_years = 2; //150629 RLN
           //NYI hook up CropSyst engine spinup
        #else
        //Identify max crop rotation years 150621LML
        int rotation_length = cell->pSimulation->pSimulationRotation->getRotationCycleLength();
        if (rotation_length > max_rotation_years)
            max_rotation_years = rotation_length;
        #endif
        if (i == 0)
            centroid/*151206 ControlRef.geolocation*/.copy_from_geocoordinate(cell->geocoordinate); //151206_150814RLN
    }

#ifdef LIU_DEBUG
    std::clog<<"Spatial data reading finished.\n";
#endif
    //Identify downstream and upstream gridcells
    //Would be used later
    //12062013 M. Liu
    /*
    for (int i = 0; i < num_cells; i++) {
        irow = basin_cells[i].getRow();
        icol = basin_cells[i].getCol();
        idir = basin_cells[i].getFlowDir();
        down_inner_id = -1;

        if (idir == 1) {                  //east
            if (icol<(tcols-1)) down_inner_id = inner_id[irow][icol+1];
        }
        else if (idir == 2) {             //southeast
            if ((icol<(tcols-1)) && (irow<(trows-1))) down_inner_id = inner_id[irow+1][icol+1];
        }
        else if (idir == 4) {             //south
            if (irow<(trows-1)) down_inner_id = inner_id[irow+1][icol];
        }
        else if (idir == 8) {             //southwest
            if ((icol>0) && (irow<(trows-1))) down_inner_id = inner_id[irow+1][icol-1];
        }
        else if (idir == 16) {            //west
            if (icol>0) down_inner_id = inner_id[irow][icol-1];
        }
        else if (idir == 32) {            //northwest
            if ((icol>0) && (irow>0)) down_inner_id = inner_id[irow-1][icol-1];
        }
        else if (idir == 64) {            //north
            if (irow>0) down_inner_id = inner_id[irow-1][icol];
        }
        else if (idir == 128) {           //northeast
            if ((irow>0) && (icol<(tcols-1))) down_inner_id = inner_id[irow-1][icol+1];
        }
        else down_inner_id = i;         //Consider it later 10/22/2013 Liu.M.

        //Update upstream & downstream grid cells
        if (down_inner_id != -1) {
            basin_cells[i].downGrid = &basin_cells[down_inner_id];
            basin_cells[down_inner_id].upGrids.push_back(&basin_cells[i]);
        }
    }
    */
    int crop_management_zones = l_crop_management_zones.size();
    for (int i = 0; i < crop_management_zones; i++) {
        Nitrate_Apply_By_Crop_Management_Zones[i]   = 0.0;
        Nitrate_Content_In_Crop_Management[i]       = 0.0;
        Ammounium_Apply_By_Crop_Management_Zones[i] = 0.0;
        Ammonium_Content_In_Crop_Management[i]      = 0.0;
        Number_Crop_Management_Zones[i]             = 0.0;
    }

    //150629 initializeWeatherStationsDataVector RLN moved from main() to accomodate Simulation_engine
    #ifndef CROPSYST_WEATHER
    initializeWeatherStationsDataVector();    //Initilize weather station vector
    #endif
    #ifdef LIU_DEBUG
    std::clog<<"Basin is initialized!\n";
    #endif
    #ifdef CROPSYST_VERSION
    #ifdef CELL_METEOROLOGY
       //160808 becoming obsolete eventually delete
    initialized &= extraterrestrial_solar_irradiance.start();                    //150814RLN
    #endif
    initialized &= CS::Simulation_engine::initialize();                          //150919RLN
#ifdef REDO_RLN
    // These reporting outputs are be optional (specified in control file)
    reporting[CS::continuous_inspection]                                         //150919
       =
       /*160606RLN to be redone
        (inspection.inspectors[CS::continuous_inspection])
       ? new CS::Reporting
            (CS::daily_aggregation
            //160606 ,*inspection.inspectors[CS::continuous_inspection]
            ,*(inspection->inspectors_simple)                                    //160606
            ,get_output_directory_name(), project_database_directory->Format(),today) //160307
       : */
       0;
    if (reporting[CS::continuous_inspection]) reporting[CS::continuous_inspection]->initialize(); //150919
    reporting[CS::annual_inspection] =                                           //150919
       /*160606RLN to be redone
        (inspection.inspectors[CS::annual_inspection])
       ? new CS::Reporting
         (CS::annual_aggregation
         //160606 ,*inspection.inspectors[CS::annual_inspection]
         ,*(inspection.inspector_tallies[CS::annual_inspection])                 //160606
         ,get_output_directory_name(), project_database_directory->Format(),today) //160307
       : */
        0;
    if (reporting[CS::continuous_inspection]) reporting[CS::continuous_inspection]->initialize(); //150919
     #endif
#endif
    return initialized;                                                          //141221
}
//______________________________________________________________________________
double BasinClass::getBasinTotalWaterStorage_m3()
{
    double totalwater = getBasinPond_m3() 
                        + getBasinSoilWaterStorage_m3() 
                        + getBasinSWE_m3();
    return totalwater;
}
//______________________________________________________________________________
double BasinClass::getBasinSWE_m3()
{
    double totalwater(0.0);   //(m3)
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:totalwater)
    int cells = NumCells();
    for (int i = 0; i < cells; i++) {
        BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        double water_m =
        #ifdef MBVB_SNOW
           mm_to_m(cell->pSnow->Current_Snow_Pack_SWE_mm);
        #else
           cell->meteorology_site.get_snow_water_equivelent_depth();             //160702RLN 161108LML replaced with _site
        #endif
        totalwater += cell->get_m3_from_m(water_m);
    }
    return totalwater;
}
//______________________________________________________________________________
double BasinClass::getBasinSoilWaterStorage_m3()
{
    double totalwater(0);   //(m3)
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:totalwater)
    int cells = NumCells();
    for (int i = 0; i < cells; i++) {
        BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        double water_m =
           #ifdef MBVB_SOIL
              cell->pSoilState->getTotalSoilWaterContent_m();
           #else
              cell->ref_soil()->ref_hydrology()->provide_water_depth_profile(true);  //160722RLN
           #endif
        totalwater += cell->get_m3_from_m(water_m);
    }
    return totalwater;
}
//______________________________________________________________________________
double BasinClass::getBasinPond_m3()
{
    double totalwater(0.0);   //(m3)
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:totalwater)
    int cells = NumCells();
    for (long i = 0; i < cells; i++) {
        BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        double water_m = cell->
           #ifdef MBVB_SOIL
           pSoilState->
           #endif
           pond.get_depth();
        totalwater += cell->get_m3_from_m(water_m);
    }
    return totalwater;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinTotalDrainage_DIN()
{
    double total(0.0);   //(kgN)
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:total)
    int cells = NumCells();
    for (long i = 0; i < cells; i++) {
        BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        total += cell->hourly_flow_solute_kg[SL_Ammonia].Drainage * NH4_to_N_conv
                 + cell->hourly_flow_solute_kg[SL_Nitrate].Drainage * NO3_to_N_conv;
    }
    return total;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinTotalDrainage_m3()
{
    double total(0.0);   //(m3)
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:total)
    int cells = NumCells();
    for (long i = 0; i < cells; i++) {
        BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        total += cell->hourly_flow_m3.Drainage;
    }
    return total;
}
/*170501LML
//______________________________________________________________________________
double BasinClass::getBasinTotalSoilInorganicNmass_kg()
{
    //double total = getBasinTotalSoilNO3_kg() * NO3_to_N_conv + getBasinTotalSoilNH4_kg() * NH4_to_N_conv;
    double total = 0.0;
    assert(false);
    return total;
}
//______________________________________________________________________________
double BasinClass::xgetBasinTotalSoilNO3_kg()
{
    double total(0.0);
    //#pragma omp parallel for reduction(+:total)
    int cells = NumCells();
    for (long i = 0; i < cells; i++)
    {
        BasinCellClass *cell = basin_cells[i];
        #ifdef CROPSYST_VERSION
        Soil_chemicals_profile     *soil_chemicals                               //160722RLN
        #ifdef MBVB_SOIL
           = cell->pSoil->chemicals;                                             //160722RLN
        #else
           = cell->ref_soil()->chemicals;                                        //160722RLN
        #endif
        if (soil_chemicals)
        total +=
          (soil_chemicals->NO3->mass->sum_profile()                              //150812RLN
           + soil_chemicals->NO3->get_surface_mass()             //150915LML
             // CropSyst proper doesn't have surface nitrate? RLN (currently index 0 is unused so it could be stored there)
          ) * cell->getArea();
        #else
        total +=
          (cell->pSoilState->getProfileNO3NMass()
          + cell->pSoilState->Layer_Nitrate_N_Mass[0]
          ) * cell->getArea();
        #endif
    }
    return total;
}
*/
//______________________________________________________________________________
double BasinClass::getBasinTotalSoilChemicalMass_kg(const Solute solute)
{
    double total(0.0);
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:total)
    int cells = NumCells();
    for (long i = 0; i < cells; i++)
    {
        BasinCellClass *cell = basin_cells[i];
        #ifdef CROPSYST_VERSION
        Soil_chemicals_profile     *soil_chemicals                               //160722RLN
        #ifdef MBVB_SOIL
           = cell->pSoil->chemicals;                                             //160722RLN
        #else
           = cell->ref_soil()->chemicals;                                        //160722RLN
        #endif
        if (soil_chemicals)
            if (solute == SL_Ammonia)
              total += soil_chemicals->NH4->mass->sum_profile() * cell->getArea();
            else if (solute == SL_Nitrate)
              total += soil_chemicals->NO3->mass->sum_profile() * cell->getArea();
        #else
        if (solute == SL_Ammonia)
          total +=
            (cell->pSoilState->getProfileNH4NMass()
            +cell->pSoilState->Layer_Ammonium_N_Mass[0])
            * cell->getArea();
        else if (solute == SL_Nitrate)
          total +=
              (cell->pSoilState->getProfileNO3NMass()
              + cell->pSoilState->Layer_Nitrate_N_Mass[0]
              ) * cell->getArea();
        #endif
    }
    return total;
}
/*170501LML
//______________________________________________________________________________
double BasinClass::xgetBasinTotalSoilNH4_kg()
{
    double total(0.0);
    //#pragma omp parallel for reduction(+:total)
    int cells = NumCells();
    for (long i = 0; i < cells; i++)
    {
        BasinCellClass *cell = basin_cells[i];
        #ifdef CROPSYST_VERSION
        Soil_chemicals_profile     *soil_chemicals                               //160722RLN
        #ifdef MBVB_SOIL
           = cell->pSoil->chemicals;                                             //160722RLN
        #else
           = cell->ref_soil()->chemicals;                                        //160722RLN
        #endif
        if (soil_chemicals) //160724 (cell->pSoil->chemicals)
            total +=
            (soil_chemicals->NH4->mass->sum_profile()                            //160722RLN_150812RLN
             //170501LML + soil_chemicals->get_NH4_molecular_mass_kg_m2(0)       //160722RLN_150915LML
             + soil_chemicals->NH4->get_surface_mass()                           //170501LML
             // CropSyst proper doesn't have surface ammonium? RLN (currently index 0 is unused so it could be stored there)
            ) * cell->getArea();
        #else
        total +=
            (cell->pSoilState->getProfileNH4NMass()
            +cell->pSoilState->Layer_Ammonium_N_Mass[0])
            * cell->getArea();
        #endif
    }
    return total;
}
*/
//______________________________________________________________________________
double BasinClass::getBasinSurfaceChemicalMass_kg(const Solute solute, bool reported)
{
    double total(0.0);
    int cells = NumCells();
    for (long i = 0; i < cells; i++)
    {
        BasinCellClass *cell = basin_cells[i];
        #ifdef CROPSYST_VERSION
        Soil_chemicals_profile     *soil_chemicals                               //160722RLN
        #ifdef MBVB_SOIL
           = cell->pSoil->chemicals;                                             //160722RLN
        #else
           = cell->ref_soil()->chemicals;                                        //160722RLN
        #endif

        if (soil_chemicals)                                                      //160722RLN
        {   if (solute == SL_Nitrate) {
                if (!reported)  total += soil_chemicals->NO3->get_surface_mass() /*170501LML get_NO3_molecular_mass_kg_m2(0)*/ * cell->getArea(); //160722RLN
                else            total += cell->report_surface_NO3_kg_m2 * cell->getArea();
            } else if (solute == SL_Ammonia) {
                if (!reported)  total += soil_chemicals->NH4->get_surface_mass() /*170501LML get_NH4_molecular_mass_kg_m2(0)*/ * cell->getArea(); //160722RLN
                else            total += cell->report_surface_NH4_kg_m2 * cell->getArea();
            }
        }
        #else
        if (solute == SL_Nitrate)
          total += cell->pSoilState->Layer_Nitrate_N_Mass[0] * cell->getArea();
        else if (solute == SL_Ammonia)
          total += cell->pSoilState->Layer_Ammonium_N_Mass[0] * cell->getArea();
        #endif
    }
    return total;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinTotalFlowOut_m3()
{
    double totalflux = getHourlyBasinOverlandFlowOut_m3() + getHourlyBasinLaterFlowOut_m3();
    return totalflux;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinOverlandFlowOut_m3()
{
    double totalflux(0.0);   //(m3)
    if (num_outlets > 0) {
        //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:totalflux)
        for (long i = 0; i < num_outlets; i++) {
            long outlet_inner_id = parr_outlet_inner_id_list[i];
            BasinCellClass *cell = basin_cells[outlet_inner_id];
            totalflux += cell->hourly_flow_m3.SurfaceOut
                         * cell->hourly_fraction_leaving_watershed[0];
        }
    }
    return totalflux;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinLaterFlowOut_m3()
{
    double totalflux(0.0);   //(m3)
    //long outlet_inner_id;
    //LML 150127 resumed soillateral flow leaving watershed
    if (num_outlets > 0) {
        //#pragma omp parallel for private(outlet_inner_id) reduction(+:totalflux)
        for (int i = 0; i < num_outlets; i++) {
            long outlet_inner_id = parr_outlet_inner_id_list[i];
            BasinCellClass* cell = basin_cells[outlet_inner_id];
            for(int layer = 1; layer <= cell->pSoilProfile->NumberOfLayers(); ++layer) {
                totalflux += cell->hourly_LateralOutFlowLayer_m3[layer]
                             * cell->hourly_fraction_leaving_watershed[layer];
                /*std::clog<<"cell#"<<cell->getCellId()
                         <<"\toutlet_in_id:"<<outlet_inner_id
                         <<"\thour:"<<ControlRef.hour
                         <<"\tlayer:"<<layer
                         <<"\tLOutFlowLayer_m3:"<<cell->hourly_LateralOutFlowLayer_m3[layer]
                         <<"\tf_leav_ws:"<<cell->hourly_fraction_leaving_watershed[layer]
                         <<"\taccum_tf(m3):"<<totalflux
                         <<std::endl;*/
            }
        }
    }
    return totalflux;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinFlowOutInorganicN_kg()
{
    double totalflux(0.0);   //(m3)
    totalflux += getHourlyBasinLaterFlowOutSolute_kg(SL_Ammonia);
    totalflux += getHourlyBasinLaterFlowOutSolute_kg(SL_Nitrate);
    totalflux += getHourlyBasinOverlandFlowOutSolute_kg(SL_Ammonia);
    totalflux += getHourlyBasinOverlandFlowOutSolute_kg(SL_Nitrate);
    return totalflux;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinOverlandFlowOutSolute_kg(Solute solute_name_index)
{
    double totalflux(0.0);   //(kg)
    if (num_outlets > 0) {
        //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:totalflux)
        for (int i = 0;i < num_outlets; i++) {
            long outlet_inner_id = parr_outlet_inner_id_list[i];
            BasinCellClass* cell = basin_cells[outlet_inner_id];
            totalflux += cell->hourly_flow_solute_kg[solute_name_index].SurfaceOut
                       * cell->hourly_fraction_leaving_watershed[0];
            //#pragma omp critical
            //std::cout<<i<<" th outlet has ID:"<<basin_cells[outlet_inner_id]->getCellId()
            //         <<" fraction_leaving_watershed:"<<basin_cells[outlet_inner_id]->fraction_leaving_watershed[0]
            //         <<std::endl;
        }
    }
    return totalflux;
}
//______________________________________________________________________________
double BasinClass::getHourlyBasinLaterFlowOutSolute_kg(Solute solute_name_index)
{
    double totalflux = 0;   //(kg)
    //long outlet_inner_id;
    //LML 150127 soillateralflow leaving watershed
    if (num_outlets > 0) {
        //#pragma omp parallel for private(outlet_inner_id) reduction(+:totalflux)
        for (int i = 0; i < num_outlets; i++) {
            long outlet_inner_id = parr_outlet_inner_id_list[i];
            BasinCellClass* cell = basin_cells[outlet_inner_id];
            int layers = cell->getSoilLayers();
            for(int layer = 1; layer <= layers; ++layer) {
                totalflux += cell->hourly_LateralOutFlowSoluteLayer_kg[layer][solute_name_index]
                             * cell->hourly_fraction_leaving_watershed[layer];
            }
        }
    }
    return totalflux;
}
//______________________________________________________________________________
void BasinClass::saveHourlyBasinOutFLow(int hourth)
{
    hourlyBasinSurfaceOutFlow_m3[hourth] = getHourlyBasinOverlandFlowOut_m3();
    hourlyBasinDrainage_DIN_kg[hourth] = getHourlyBasinTotalDrainage_DIN();
    hourlyBasinDrainage_m3[hourth] = getHourlyBasinTotalDrainage_m3();
    hourlyBasinLateralOutFlow_m3[hourth] = getHourlyBasinLaterFlowOut_m3();
    std::list<Solute> s;
    s.push_back(SL_Ammonia);
    s.push_back(SL_Nitrate);  //LML 150127
    for (std::list<Solute>::iterator i = s.begin(); i != s.end(); ++i) {
        hourlyBasinLateralOutFlowSolute_kg[hourth][*i] = getHourlyBasinLaterFlowOutSolute_kg(*i);
        hourlyBasinSurfaceOutFlowSolute_kg[hourth][*i] = getHourlyBasinOverlandFlowOutSolute_kg(*i);
    }
}
//______________________________________________________________________________
#ifdef MBVB_SOIL
//160722 This is actually never used
double BasinClass::getHourlyTotalWaterFluxToSoil_m3()
{
    //This is for checking basin hourly water balance (soil + pond only)
    //Current_Hour_Index: 0 - 23
    //Only account to soil layers M.Liu !!!

    double totalflux(0.0);   //(m3)
    int cells = NumCells();
    for (int i = 0; i < cells; i++) {
        BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        double water_m = cell->pSoilProcess->Hourly_Non_Intercepted_Rain_m; //basin_cells[i]->pWeatherDaily->getHourlyPrecipitation(Current_Hour_Index);
        water_m += cell->pSoilProcess->Hourly_Snow_Melt_m;
        water_m += cell->pSoilState->Hourly_Irrigation_m;
        water_m -= cell->pSoilState->Hourly_Drainage_m;
        //water_mm -= basin_cells[i]->pSnow->Hourly_Sublimation_mm[Current_Hour_Index+1];

        totalflux += cell->get_m3_from_m(water_m);
        if (cell->isOutlet()) {
            totalflux -= cell->hourly_flow_m3.SurfaceOut *
                         cell->hourly_fraction_leaving_watershed[0];
            //LML 141203 totalflux -= basin_cells[i]->hourlyLateralOutFlow_m3;
        }
    }
    return totalflux;
}
#endif
//______________________________________________________________________________
bool BasinClass::start()                                           modification_
{  bool started = true;
   #ifdef CROPSYST_VERSION
   started &= CS::Simulation_engine::start();
   /*106023RLN redo
   for (nat8 r = 0; r < CS::COUNT_inspection; r++)
      if (reporting[r]) started &= reporting[r]->start();
   */
   #ifdef CELL_METEOROLOGY
      //160808 becoming obsolete eventually delete
   extraterrestrial_solar_irradiance.start();                                    //160218LML
   #endif
   int cells = NumCells();
   for (long i = 0; i < cells; i++)                                         //160118RLN
   {
       BasinCellClass *cell = basin_cells[i];
       started &= cell->start();
   }
   #endif
   return started;
}
//_2015-06-20_RLN_____________________________________________________start()__/
bool BasinClass::start_day()
{
   // Weather must be started before anything else                               //160608
   #ifdef CROPSYST_WEATHER
        //NYN weather_database.get_to(weather_provider);                         //140219
        // ROGER continue here need to setup hourly weather provider
        #else
        //Initlize daily weather
        #ifdef CROPSYST_VERSION
        setDailyWeather(weather_stations[0].get_ID());                           //141222
        #else
        setDailyWeather(today
            #ifndef MACA_V1_MBMET
            ,weather_stations[0].getStationID()
            #endif
        );
        #endif
  #endif

   bool started = CS::Simulation_engine::start_day();
   //160225RLN  CS::Simulation_engine:: already prints today std::clog<<today.as_string()<<std::endl;
   #ifdef CROPSYST_VERSION
   #ifdef CELL_METEOROLOGY
   //160808 becoming obsolete eventually delete
   sun.update();                                                                 //150730
   #endif
   #endif
   output_dailyBasinSurfaceOutFlow_m3   = 0;
   output_dailyBasinDrainage_m3         = 0;
   output_dailyBasinLateralOutFlow_m3   = 0;
   for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
      output_dailyBasinLateralOutFlowSolute_kg[s] = 0;
      output_dailyBasinSurfaceOutFlowSolute_kg[s] = 0;
      output_dailyBasinDrainageSolute_kg[s]       = 0;                           //150921LML
   }
   return started;
}
//_2015-06-20_RLN_________________________________________________start_day()__/
bool BasinClass::process_day()                                     modification_
{
   bool processed = true;                                                        //160724RLN
/* process_day already output date when VERBOSE is defined
   //#ifdef LIU_DEBUG
   //std::clog<<today.as_string()<<std::endl;
   //#endif
*/
   //if (verbose) std::clog<<std::endl;                                            //160406RLN
   std::clog << today.as_string() << "\r";                                            //161108LML verbose didn't hooked up to CS_simulation engine yet!
/*160606 RLN weather must be setup in start_day before starting anything else
        #ifdef CROPSYST_WEATHER
        //NYN weather_database.get_to(weather_provider);                         //140219
        // ROGER continue here need to setup hourly weather provider
        #else
        //Initlize daily weather
        #ifdef CROPSYST_VERSION
        setDailyWeather(weather_stations[0].get_ID());                           //141222
        #else
        setDailyWeather(today
            #ifndef MACA_V1_MBMET
            ,weather_stations[0].getStationID()
            #endif
        );
        #endif
        #endif
*/

        //CORN::Date dy;dy.set_DOY(247);dy.set_year(2012);
        //if (today == dy) {
        //    int debug = 1;
        //    std::clog<<"DEBUG 2012,243\n";
        //}
        //#ifdef LIU_DEBUG
        //std::clog<<"Basin Daily weather is initialized. "<<std::endl;
        //#endif
        //150921LML if (today == ControlRef.getStartDate()) initializeBasinOutputs();  //LML 14/04/20
        //omp_set_num_threads(4);
        int cells = NumCells();
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE) /*schedule(dynamic,1)*/
        for (long i = 0; i < cells; i++)
        {
            BasinCellClass *cell = basin_cells[i];                               //140303RLN
            //#ifdef LIU_DEBUG
            //#pragma omp critical
            //std::clog<<"Before start_day...cell_id:"<<cell->getCellId()<<std::endl;
            //#endif
            if (today == ControlRef.getStartDate()) {         //Initlize soil state
               #ifdef MBVB_SOIL_TEMPERATURE
                cell->pSoil->pSoilTemperature->initialize();                     //150810RLN was InitializeSoilTemperature();
               #else
               //160721RLN land unit simulation soil maintains soil temperature.
               #endif

                    // Actually soil temperature initialize() should be called in by cell initialize()
                    // but need to check if everything soil temperature needs has been initialized
                    // 150810RLN

            /* RLN disabled so I can compile without OMP
                #ifdef LIU_DEBUG
                #pragma omp critical
                std::clog<<"\tNumber of :"<<omp_get_num_procs()
                         <<"\tThread#:"   <<omp_get_thread_num()
                         <<"\tCell#:"     <<i
                         <<std::endl;
                #endif
            */
            }
            bool temp = cell->start_day();                                       //141221RLN
            #pragma omp critical
            processed &= temp;
        }
        if (today == ControlRef.getStartDate()) {
            initializeBasinOutputs();                                            //LML 14/04/20
            #ifdef LIU_DEBUG
            //std::clog<<"Basin outputs are initialized."<<std::endl;
            #endif
        }
        for (int hour = 0; hour < 24; hour++) {
            total_hourth++;
            ControlRef.hour = hour;                                              //140221RLN

            #ifdef LIU_DEBUG
            //std::clog<<"hour:"<<hour<<std::endl;
            #endif
            #ifndef QUICK_DIRTY_RUN_FOR_DEBUG_MEM_USE
            if (ControlRef.PerchedWT_Enabled || (!ControlRef.PerchedWT_Enabled && !ControlRef.PerchedWT_Disabled_Watershed_Property_Calculated)) {
                WatershedPropertiesCalculation(hour);       //Calculate hydrological properties
                //#ifdef LIU_DEBUG
                //std::clog<<"Watershed Properties Calculated."<<std::endl;
                //#endif
            }
            #endif
            //160724RLN renamed to start_hour initializeHourlyFluxesForAllGridCells();    //LML 14/04/18
            processed &= start_hour();                                             //160724RLN
            #pragma omp parallel for                                             //170713 num_threads(NUMCORES_TO_USE)                /*schedule(dynamic,1)*/
            for (long i = 0; i < cells; i++) {
                BasinCellClass* cell = basin_cells[i];
                #ifndef QUICK_DIRTY_RUN_FOR_DEBUG_MEM_USE
                cell->runHourlyGridCellProcess(hour);
                #endif

                Soil_chemicals_profile *soil_chemicals = cell->get_soil_chemicals();                                //170501LML
                cell->report_surface_NH4_kg_m2 = soil_chemicals ? soil_chemicals->NH4->get_surface_mass() : 0.0;    //170501LML
                cell->report_surface_NO3_kg_m2 = soil_chemicals ? soil_chemicals->NO3->get_surface_mass() : 0.0;    //170501LML


                #ifdef CHECK_OVERLANDFLOW_WATER_AND_NITROGEN_FOR_DEBUG
                Soil_chemicals_profile *soil_chemicals = cell->get_soil_chemicals(); //151212RLN
                if (soil_chemicals && hour == 0 && today.get_DOY() == ControlRef.start_date.get_DOY()
                              && today.get_year() == ControlRef.start_date.get_year()) {
                    soil_chemicals->set_NH4_molecular_mass_kg_m2(0,1.0);
                    soil_chemicals->set_NO3_molecular_mass_kg_m2(0,1.0);
                }
                #endif

                #ifndef CROPSYST_VERSION
                for (int layer = 0; layer <= cell->pSoilProfile->NumberOfLayers(); layer++)
                {
                    if (cell->pSoilState->Layer_Nitrate_N_Mass[layer] < 0.0 ||
                        cell->pSoilState->Layer_Ammonium_N_Mass[layer] < 0.0) {
                        #pragma omp critical
                        {
                        std::clog<<"Cell:"      <<cell->getCellId()
                                 <<" L:"        <<layer
                                 <<" (NO3):"    <<cell->pSoilState->Layer_Nitrate_N_Mass[layer]
                                 <<" (NH4):"    <<cell->pSoilState->Layer_Ammonium_N_Mass[layer]
                                 <<std::endl;
                        //exit(1);
                        }
                    }
                }
                #endif
            }
            #ifdef CHECK_MASS_BALANCE
            BalanceItem bal_water;
            //150914LML BalanceItem bal_DIN;
            BalanceItem bal_NO3;
            BalanceItem bal_NH4;
            bal_water.SetInitPool(getBasinTotalWaterStorage_m3());
            //150914LML bal_DIN.SetInitPool(getBasinTotalSoilInorganicNmass_kg());              //SoilState
            bal_NO3.SetInitPool(getBasinTotalSoilChemicalMass_kg(SL_Nitrate) + getBasinSurfaceChemicalMass_kg(SL_Nitrate, true));
            bal_NH4.SetInitPool(getBasinTotalSoilChemicalMass_kg(SL_Ammonia) + getBasinSurfaceChemicalMass_kg(SL_Ammonia, true));
            double old_surface_NO3 = getBasinSurfaceChemicalMass_kg(SL_Nitrate, true);
            double old_surface_NH4 = getBasinSurfaceChemicalMass_kg(SL_Ammonia, true);
            double oldpond = getBasinPond_m3();
            #endif
            #ifndef QUICK_DIRTY_RUN_FOR_DEBUG_MEM_USE
            runLateralFlow((double)hour,1.0);
            //#ifdef LIU_DEBUG
            //std::clog<<"runLateralFlow done."<<std::endl;
            //#endif
            #pragma omp parallel for                                             //170713 num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)                         //150910LML
            for (long i = 0; i < cells; i++) {                              //150910LML
                BasinCellClass* cell = basin_cells[i];                           //150910LML
                cell->accum_hourly_outflow();                                    //150910LML
                /*std::clog<<"AFTER LATERALFLOW:"
                         <<"\thour:"<<hour
                         <<"\tcell:"<<cell->getCellId()
                         <<"\tdrainage:"<<cell->hourly_flow_m3.Drainage
                         //<<"\tamount[NH4][layer=0]:"<<cell->get_soil_chemicals()->get_NH4_molecular_mass_kg_m2(0)
                         //<<"\tamount[NO3][layer=0]:"<<cell->get_soil_chemicals()->get_NO3_molecular_mass_kg_m2(0)
                         <<std::endl;*/
            }                                                                    //150910LML
            #endif                                                               //150910LML

            #ifdef CHECK_MASS_BALANCE
            bal_water.SetFinalPool(getBasinTotalWaterStorage_m3());
            bal_water.SetFluxOut(getHourlyBasinTotalFlowOut_m3());
            bal_NO3.SetFluxOut(getHourlyBasinOverlandFlowOutSolute_kg(SL_Nitrate)
                               + getHourlyBasinLaterFlowOutSolute_kg(SL_Nitrate));  //LML 150127
            bal_NH4.SetFluxOut(getHourlyBasinOverlandFlowOutSolute_kg(SL_Ammonia)
                               + getHourlyBasinLaterFlowOutSolute_kg(SL_Ammonia));   //LML 150127
            bal_NO3.SetFinalPool(getBasinTotalSoilChemicalMass_kg(SL_Nitrate) + getBasinSurfaceChemicalMass_kg(SL_Nitrate, true));
            bal_NH4.SetFinalPool(getBasinTotalSoilChemicalMass_kg(SL_Ammonia) + getBasinSurfaceChemicalMass_kg(SL_Ammonia, true));
            if (!bal_water.IsMassBalance(MASS_BALANCE_WATER_MM * basin_area_km2 * 1e3)) {
                std::clog<<"Hour:"<<hour<<std::endl;
                bal_water.PrintMassBalanceTerms("Water in runSimulation");
                std::clog<<" old_pond:"<<oldpond<<" new_pond:"<<getBasinPond_m3()<<" dif:"<<getBasinPond_m3()-oldpond<<std::endl<<std::endl;
            }
            if (!bal_NO3.IsMassBalance(0.005) || !bal_NH4.IsMassBalance(0.005)) {
                std::clog<<"\tLater_flow_NO3_kg:"   <<getHourlyBasinLaterFlowOutSolute_kg(SL_Nitrate)
                         <<"\tLater_flow_NH4_kg:"   <<getHourlyBasinLaterFlowOutSolute_kg(SL_Ammonia)
                         <<std::endl
                         <<"\tOverland_flow_NO3_kg:"<<getHourlyBasinOverlandFlowOutSolute_kg(SL_Nitrate)
                         <<"\tOverland_flow_NH4_kg:"<<getHourlyBasinOverlandFlowOutSolute_kg(SL_Ammonia)
                         <<std::endl
                         << "\told_surface_NO3:" << old_surface_NO3
                         << "\told_surface_NH4:" << old_surface_NH4
                         <<"\tSurface_NO3_kg:"<< getBasinSurfaceChemicalMass_kg(SL_Nitrate, true)
                         <<"\tSurface_NH4_kg:"<< getBasinSurfaceChemicalMass_kg(SL_Ammonia, true)
                         <<std::endl;
                if (!bal_NO3.IsMassBalance(0.005)) bal_NO3.PrintMassBalanceTerms("NO3 in runSimulation");
                if (!bal_NH4.IsMassBalance(0.005)) bal_NH4.PrintMassBalanceTerms("NH4 in runSimulation");
            }
            #endif
            #ifdef VB_SAME_CSV_OUTPUT
            if (ControlRef.bWrite_Hourly_Output &&
                    today >= ControlRef.Start_Date_Hourly_Output &&
                    today <= ControlRef.End_Date_Hourly_Output) {
                #pragma omp parallel for                                         //170713 num_threads(NUMCORES_TO_USE)            //schedule(dynamic,1)
                for (long i = 0; i < cells; i++) {
                    BasinCellClass *cell = basin_cells[i];
                    if (cell->get_debug_output())
                      cell->
                      #ifdef CROPSYST_VERSION
                      pOutput->WriteHourlyOutput(hour);
                      #else
                      pSimulation->pOutput->WriteHourlyOutput(basin_cells[i]);
                      #endif
                }
            }
            #endif

            #ifndef QUICK_DIRTY_RUN_FOR_DEBUG_MEM_USE
            cumBasinOutputsFromHourly(hour,total_hourth);  //LML 14/04/20 accumulate fluxes for basin outputs
            #endif
        }//hour
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < cells; i++)
        {
            BasinCellClass *cell = basin_cells[i];                               //140303RLN
            //#ifdef LIU_DEBUG
            //#pragma omp critical
            //std::clog<<"In process_day... cell_id:"<<cell->getCellId()<<std::endl;
            //#endif
            //cell->sumDailyFlow();                        //LML 141013 NIY
            bool temp(true);

            #ifndef QUICK_DIRTY_RUN_FOR_DEBUG_MEM_USE
            temp &= cell->process_day();                                          //150709_141221RLN
            #endif

            /*151013LML disabled temporaly
            #ifdef DEBUG_LIU_OUT_CSV
            #pragma omp critical
            if (!cell_output_head_printed)
                print_cell_daily_for_debug_head(fstm_daily_cell_out,cell);
            print_cell_daily_for_debug(fstm_daily_cell_out,today,cell);
            #endif
            */
            if (today.is_last_DOY()) {                                           //141221
                temp &= cell->end_year();                                         //141221
            }
            #pragma omp critical
            processed &= temp;
        }//end cell
    return processed;
}
//_2015-06-29_RLN_________________________________________________process_day__/
bool BasinClass::end_day()                                         modification_
{   bool ended = true;
    //150921LML
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        ended &= cell->end_day();
    }
   cumBasinOutputsFromDaily();
   #ifdef DEBUG_LIU_OUT_CSV
        if (!basin_output_head_printed)
            print_basin_daily_for_debug_head(fstm_daily_basin_out);
        print_basin_daily_for_debug(fstm_daily_basin_out,today,*this);
   #endif
   #ifdef CROPSYST_VERSION
   ended &= CS::Simulation_engine::end_day();                               //150919
   /*
        for (nat8 r = 0; r < CS::COUNT_inspection; r++)                          //150919
            if (reporting[r]) ended &= reporting[r]->end_day();                  //150919
   */
   #endif
   #ifdef VB_SAME_CSV_OUTPUT
        //LML 150205 print out hourly output for researving memory
        if (ControlRef.bWrite_Hourly_Output && (today.is_last_DOM() || today == ControlRef.end_date))
        {   PrintTextHourlyOutputForAllGrids();
            if (ControlRef.bOutput_Format_Esri_Grid)
                PrintEsriGridHourlyOutput();
        }
        if (ControlRef.bWrite_Daily_Output && (today.is_last_DOM() || today == ControlRef.end_date))
        {   PrintTextDailyOutputForAllGrids();
            if (ControlRef.bOutput_Format_Esri_Grid)
                PrintEsriGridDailyOutput();
        }
        if (ControlRef.bWrite_Growth_Daily_Output && (today.is_last_DOM() || today == ControlRef.end_date))
            PrintTextGrowthDailyOutputForAllGrids();

        if (ControlRef.bWrite_Growth_Season_Output && today == ControlRef.end_date)
            PrintTextGrowthSeasonOutputForAllGrids();
        if (ControlRef.bWrite_Annual_Output && (today == ControlRef.end_date))
            PrintTextAnnualOutputForAllGrids();
   #endif
   return ended;
}
//_2015-06-29_RLN_________________________________________________process_day__/
bool BasinClass::stop()                                            modification_
{   bool stopped = true;
    #ifdef CROPSYST_VERSION
    int cells = NumCells();
    for (long c = 0; c < cells; c++)
       stopped &= basin_cells[c]->LAND_UNIT_SIM_ stop();
/*160623RLN
    // This is just to display inspectors (EVENTUALLY REMOVE THIS AFTER THE MODEL HAS BEEN DEVELOPED) RLN
    dump_inspectors(std::cout,CS::continuous_inspection);                        //151002
*/
    stopped &= CS::Simulation_engine::stop();
/*160623RLN
    for (nat8 r = 0; r < CS::COUNT_inspection; r++)
       if (reporting[r]) stopped &= reporting[r]->stop();
*/
    #else
    #endif
    #ifdef VB_SAME_CSV_OUTPUT
    finalizeBasinOutputs();                                                      //140420LML
    PrintBasinOutputs();
    std::clog<<"Printing outputs...\n";
    #endif



    //150918lml this should be end_of_day event PrintTextAllOutputForAllGrids();
    //std::clog<<"Done!\n";




    #ifdef LIU_DEBUG
    //CORN::Time now;
    //std::clog<<"Finished at "<<
    //   now.as_string()
               //150919RLN currentDateTime()
    //<<std::endl;
    #endif

    return stopped;
}
//_2015-06-29_RLN________________________________________________________stop__/
int BasinClass::runLateralFlow(const double t_start,const double t_length)
{
    //It includes soil lateral flow and overland flow
    //t_start: (h) start time
    //t_length: (h) duration
    //read soil state of each grid cell into basin variables
    double Sum_Ponded_MB_m(0.0);       //(m)
    #ifdef MBVB_SOIL
    // Doesn't appear to be used 160722RLN
    double sumVertical_flow_balance(Vertical_flow_balance_allCells);
    #endif
    int solutes = ControlRef.getSoluteSpecies();
    //#pragma omp parallel for /*schedule(dynamic,1)*/ reduction(+:Sum_Ponded_MB_m,sumVertical_flow_balance)
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        Ponded_m[i] = cell->pond.get_depth();
        double storage_capacity = mm_to_m(cell->pSoilProfile->SurfaceStorage);
        #ifdef MBVB_SOIL
        //160722 This doesn't appear to be used
        sumVertical_flow_balance += cell->soil_tallies/*160722 pSoilState*/->Vertical_flow_balance_allLayers;     //(m)
        #endif
        Sum_Ponded_MB_m += Ponded_m[i] > storage_capacity ?
                           Ponded_m[i] - storage_capacity :
                           0;
        int layers = cell->getSoilLayers();
        Soil_chemicals_profile *soil_chemicals =  cell->LAND_UNIT_SIM_ get_soil_chemicals(); //151212RLN

        for (int layer = 0; layer <= layers; layer++) {
            if (layer >= 1) {
                Theta[i][layer] = cell->
                    #ifdef MBVB_SOIL
                    pSoilState->
                    #else
                    ref_soil()->ref_hydrology()->
                    #endif
                    get_liquid_water_content_volumetric(layer);//Water_Content[layer];
                Theta_s[i][layer] = 
                    cell->pSoilProfile->get_saturation_water_content_volumetric(
                            layer,
                            cell->
                            #ifdef MBVB_SOIL
                            pSoilState->
                            #else
                            ref_soil()->ref_hydrology()->
                            #endif
                            get_ice_content_volumetric(layer));//141005RLN

                if (Theta[i][layer] > Theta_s[i][layer])
                    std::cerr << "cell#:" << cell->getCellId() << "\tL:" << layer << "\tTheta[i][layer]:" << Theta[i][layer] << " > (Theta_s[i][layer]:" << Theta_s[i][layer] << "!!!\n";


                //std::clog << "Layer:" << layer << "\tTheta[i][layer]:" << Theta[i][layer] << std::endl;
#ifdef CROPSYST_VERSION
                // In CropSyst proper N cannot be negative.
                if (soil_chemicals)                                                  //151212RLN

                {  SoluteAmount[i][layer][SL_Ammonia] = soil_chemicals->get_NH4_molecular_mass_kg_m2(layer);   //150914LML get_NH4_N_mass_kg_m2(layer);
                   SoluteAmount[i][layer][SL_Nitrate] = soil_chemicals->get_NO3_molecular_mass_kg_m2(layer);   //150914LML get_NO3_N_mass_kg_m2(layer);
                }
#endif
            } else {
                SoluteAmount[i][0][SL_Ammonia] = soil_chemicals->NH4->deduct_surface_mass(9999998); //surface_mass_pending_infiltration_M;  //170424RLN need to work on it!!! should be from the pond chemicals.
                SoluteAmount[i][0][SL_Nitrate] = soil_chemicals->NO3->deduct_surface_mass(9999998); //surface_mass_pending_infiltration_M;  //170424RLN need to work on it!!! should be from the pond chemicals.
                //soil_chemicals->NH4->surface_mass_pending_infiltration_M = 0;    //170424RLN need to work on it!!! should be from the pond chemicals.
                //soil_chemicals->NO3->surface_mass_pending_infiltration_M = 0;    //170424RLN need to work on it!!! should be from the pond chemicals.
                /*std::clog << "grid#:" << cell->getCellId()
                          << "\tNH4:" << SoluteAmount[i][0][SL_Ammonia]
                          << "\tNO3:" << SoluteAmount[i][0][SL_Nitrate]
                          << std::endl;*/
            }
            Hydro_Standard_Slope[i][layer] = cell->
               soil_tallies/*160722 pSoilState*/->Hydro_Standard_Slope[layer];
            /*std::clog<<"\nrunLateralFlow::Cell#:"   <<cell->getCellId()
                     <<"\tL:"                       <<layer
                     <<"\tH_Slop:"                  <<Hydro_Standard_Slope[i][layer];*/

            #ifdef CROPSYST_VERSION

            #else
            SoluteAmount[i][layer][SL_Ammonia] = cell->pSoilState->Layer_Ammonium_N_Mass[layer];
            //150911LML SoluteConc[i][layer][SL_Ammonia] = cell->pSoilState->Layer_Ammonium_N_Conc[layer];
            SoluteAmount[i][layer][SL_Nitrate] = cell->pSoilState->Layer_Nitrate_N_Mass[layer];
            //150911LML SoluteConc[i][layer][SL_Nitrate] = cell->pSoilState->Layer_Nitrate_N_Conc[layer];
            #endif
            SoluteAmount[i][layer][SL_Phosphate] = 0;                            //141204LML NIY

            //150911LML SoluteConc[i][layer][SL_Phosphate] = 0;                              //141204LML NIY
            for (int s = 0; s < solutes; s++) {
                //LML 150203 
                if(SoluteAmount[i][layer][s] < 0 && 
                   fabs(SoluteAmount[i][layer][s]) < PERMITTED_ERROR_NUTRIENTS_KG_PER_KM2)
                {    //LML 150206 TODO this adjustment should be taken after daily N processes
                    SoluteAmount[i][layer][s] = 0.0;
                }
                //LML 150203 recalculate the concentration
                //LML 150203 TODO check consistancy of concentration & mass amount
                //151028LML if(layer >= 1) SoluteConc[i][layer][s] =
                //151028LML         SoluteAmount[i][layer][s] / Theta[i][layer];
                //151028LML else if (!CORN::is_approximately<double>(Ponded_m[i],0.0))
                //151028LML     SoluteConc[i][layer][s] = SoluteAmount[i][layer][s] / Ponded_m[i];
                //151028LML else SoluteConc[i][layer][s] = 0.0;
                
                if(SoluteAmount[i][layer][s] < 0.0){
                    #pragma omp critical
                    std::cerr<<"Warning:\n"
                             <<"\tCell "          <<cell->getCellId()
                             <<"@layer "          <<layer
                             <<" has negtive "    <<Solute_Name[s]
                             <<" Amount:"         <<SoluteAmount[i][layer][s]<<" (kg/m2)"
                             << "\n. It has been set ZERO!!!\n";
                    //170417LML exit(1);
                    SoluteAmount[i][layer][s] = 0;                               //170417LML
                }
            }
        }
    }
    cum_Update_PWT = Update_PWT;    // //Time when perched water table conditions are updated (h)
    //run time loops -----------------------------------------------------------------------------
    double soillt_start = t_start;
    double soillt_length = ControlRef.getTSLateralFlow();
    const int loops_lateralflow = (int)floor(t_length/soillt_length + 0.5);
    for (int Laterloop = 0; Laterloop < loops_lateralflow; Laterloop++) {
        if (Sum_Ponded_MB_m > 0) {
            if (ControlRef.Overlandflow_Method == 1) {
                //OverlandflowTimeloop8D(today,soillt_start, soillt_length);  //8-direction
                OverlandflowTimeloop8D_Simple(soillt_start, soillt_length);
                #ifdef LIU_DEBUG
                //std::clog<<"OverlandflowTimeloop8D_Simple done."<<std::endl;
                #endif
            } else if (ControlRef.Overlandflow_Method == 2) {
                std::cerr<<"4-direction flow has not been implemented yet!!!\n";
                assert(false);
                //OverlandflowTimeloop4D(today,soillt_start, soillt_length);  //4-direction LML 141001 didn't check yet!
            }
        }
        /*Lateral flow through soil layers*/
        SoilLateralflowTimeloop(soillt_start, soillt_length);
        //#ifdef LIU_DEBUG
        //std::clog<<"SoilLaterflowTimeloop done."<<std::endl;
        //#endif
        soillt_start += ControlRef.getTSLateralFlow();
    }
    //forward results ----------------------------------------------------------------------------
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        //#ifdef LIU_DEBUG
        //#pragma omp critical
        //std::clog<<"In runLateralFlow forward result... cell_id:"<<cell->getCellId()<<std::endl;
        //#endif
        cell->pond.set_depth(Ponded_m[i]);
        //170418LML transfer all surface chemicals to the first soil layer
        //if (cell->pond.get_depth() <= 1e-12 && (SoluteAmount[i][0][SL_Nitrate] > 1e-12 || SoluteAmount[i][0][SL_Ammonia] > 1e-12)) {
        //    cell->pond.set_depth(0);
        //    SoluteAmount[i][1][SL_Nitrate] += SoluteAmount[i][0][SL_Nitrate];
        //    SoluteAmount[i][1][SL_Ammonia] += SoluteAmount[i][0][SL_Ammonia];
        //    SoluteAmount[i][0][SL_Nitrate]  = 0;
        //    SoluteAmount[i][0][SL_Ammonia]  = 0;
        //}
        //150911 LML #ifdef CROPSYST_VERSION
        //CropSyst proper maintains mass (and concentration)
        //150911 LML #else
        int layers = cell->getSoilLayers();

        Soil_chemicals_profile *soil_chemicals =cell->LAND_UNIT_SIM_ get_soil_chemicals();
        if (soil_chemicals) {
            //soil_chemicals->NH4->inc_applied_and_applied_irrig_soil_surface(SoluteAmount[i][0][SL_Ammonia],t_start, t_length);
            //soil_chemicals->NO3->inc_applied_and_applied_irrig_soil_surface(SoluteAmount[i][0][SL_Nitrate],t_start, t_length);
            CORN::Date_time_64_clad next_hour(today.get_date32(),t_start * 3600);
            //std::cerr << "cell#:" << (int)cell->getCellId() << std::endl;
            //std::cerr << "t_start:" << t_start << std::endl;
            //std::cerr << "current_hour's DOY:" << (int) next_hour.get_DOY() <<"\tcurrent hour:" << (int)next_hour.get_hour() << std::endl;
            next_hour.inc_hours(1);                                              //170503LML
            //std::cerr << "next_hour's DOY:"    << (int) next_hour.get_DOY() <<"\tnext hour:" << (int)next_hour.get_hour() << std::endl;

            /*if (SoluteAmount[i][0][SL_Ammonia] > 0)
            std::clog << "Cell#:" << cell->getCellId()
                      << "\tSL_Ammonia:" << SoluteAmount[i][0][SL_Ammonia]
                      << "\tSL_Nitrate:" << SoluteAmount[i][0][SL_Nitrate]
                      << "\tt_start:" << t_start
                      << "\tnew_next_hour:" << (int)next_hour.get_hour()
                      << std::endl;*/

            soil_chemicals->NH4->apply_surface_mass(
                    SoluteAmount[i][0][SL_Ammonia] //kg chem / m^2 soil molecular
                    ,next_hour.get_datetime64()
                    ,3600
                    ,3600);
            soil_chemicals->NO3->apply_surface_mass(
                    SoluteAmount[i][0][SL_Nitrate] //kg chem / m^2 soil molecular
                    ,next_hour.get_datetime64()
                    ,3600
                    ,3600);

            cell->report_surface_NH4_kg_m2 = SoluteAmount[i][0][SL_Ammonia];     //170501LML
            cell->report_surface_NO3_kg_m2 = SoluteAmount[i][0][SL_Nitrate];     //170501LML

            SoluteAmount[i][0][SL_Ammonia] = 0;
            SoluteAmount[i][0][SL_Nitrate] = 0;
        }

        for (int layer = 1; layer <= layers; layer++) {
            //hand over soil water
            /*170424 if (layer >= 1) */cell->
               #ifdef MBVB_SOIL
                  pSoilState->set_liquid_water_content_volumetric_layer(layer,Theta[i][layer]);  //150911LML set_water_content_volumetric_layer(layer,Theta[i][layer]);
               #else
                  ref_soil()->mod_hydrology()->set_water_content_volumetric_layer(layer,Theta[i][layer]); //160722RLN
               #endif

            if (Theta[i][layer] > Theta_s[i][layer])
                std::cerr << "Out: Theta[i][layer] > (Theta_s[i][layer]!!!\n";

            //std::clog << "layer:" << layer <<"\tset_liquid_water Theta[i][layer]:" << Theta[i][layer] << std::endl;

            #ifdef CROPSYST_VERSION
            if (cell->hourly_LateralOutFlowLayer_m3[layer] > 100 && layer != 0)
                std::clog<<"AFTER LATERALFLOW:"
                     <<"\thour:"<<ControlRef.hour
                     <<"\tcell:"<<cell->getCellId()
                     <<"\tlayer:"<<layer
                     <<"\tamount[NH4]:"<<SoluteAmount[i][layer][SL_Ammonia]
                     <<"\tamount[NO3]:"<<SoluteAmount[i][layer][SL_Nitrate]
                     <<"\tlateralflow_m3:"<<cell->hourly_LateralOutFlowLayer_m3[layer]
                     <<std::endl;
            if (soil_chemicals)                                                  //151212RLN
            {   soil_chemicals->set_NH4_molecular_mass_kg_m2(layer, SoluteAmount[i][layer][SL_Ammonia]);   //151212RLN_150911LML
                soil_chemicals->set_NO3_molecular_mass_kg_m2(layer, SoluteAmount[i][layer][SL_Nitrate]);  //151212RLN_150911LML
            }
            #else
            //Solute
            cell->pSoilState->Layer_Ammonium_N_Mass[layer] = SoluteAmount[i][layer][SL_Ammonia];
            cell->pSoilState->Layer_Nitrate_N_Mass[layer] = SoluteAmount[i][layer][SL_Nitrate];
            #endif
            SoluteAmount[i][layer][SL_Ammonia] = 0;
            SoluteAmount[i][layer][SL_Nitrate] = 0;
            /*151029LML moved before infiltration process
            //151027LML the following concentration is used for cascade_chemical transport.
            if (layer >= 1) {
               cell->pSoilState->Layer_Ammonium_N_Conc[layer] = NH4_to_N_conv * SoluteAmount[i][layer][SL_Ammonia] / (Theta[i][layer] * L_thickness[i][layer]);
               cell->pSoilState->Layer_Nitrate_N_Conc[layer] = NO3_to_N_conv * SoluteAmount[i][layer][SL_Nitrate] / (Theta[i][layer] * L_thickness[i][layer]);
            } else {
                if (!is_approximately(Ponded_m[i],0.0)) {
                    cell->pSoilState->Layer_Ammonium_N_Conc[layer] = NH4_to_N_conv * SoluteAmount[i][layer][SL_Ammonia] / Ponded_m[i];
                    cell->pSoilState->Layer_Nitrate_N_Conc[layer] = NO3_to_N_conv * SoluteAmount[i][layer][SL_Nitrate] / Ponded_m[i];
                } else {
                    cell->get_soil_chemicals()->add_NH4_molecular_mass(1,SoluteAmount[i][layer][SL_Ammonia]);
                    cell->get_soil_chemicals()->add_NO3_molecular_mass(1,SoluteAmount[i][layer][SL_Nitrate]);
                    cell->pSoilState->Layer_Ammonium_N_Conc[layer] = 0.0;
                    cell->pSoilState->Layer_Nitrate_N_Conc[layer]  = 0.0;
                    cell->get_soil_chemicals()->set_NH4_molecular_mass_kg_m2(0,0.0);
                    cell->get_soil_chemicals()->set_NO3_molecular_mass_kg_m2(0,0.0);
                }
            }
            */
            //if (layer == 0) std::clog<<"Layer_Ammonium_N_Conc[0][SL_Ammonia]:"<<SoluteConc[i][layer][SL_Ammonia]
            //         <<std::endl;
            //151027LML #endif
        } //layer
        //150911 LML #endif
        #if (defined(MBVB_FD) || defined(MSVB_CASCADE_INFILTRATION_HOUR))
        //set new upper and lower layer water conents
        basin_cells[i]->pSoilState->setallSoilWater();
        #endif
    }   //end i

    //if (OutletflowLayer0 < 0) return(0);
    //cum_Outlet_flow += Outletflow + OutletflowLayer0;
    //cum_Solute_Outlet_flow += SoluteOutletflow + SoluteOutletflowLayer0;
    //cum_Outlet_Lateral_Flow += Outletflow;
    //cum_Outlet_Runoff += OutletflowLayer0;
    #ifdef MBVB_SOIL
    // Doesn't appear to be used 160722RLN
    Vertical_flow_balance_allCells = sumVertical_flow_balance;
    #endif
    return 1; //131121 RLN must return a value
}
//______________________________________________________________________________
BasinCellClass* BasinClass::getCellPointer(int row,int col)
{
    long id = inner_id[row][col];
    if (id != -1) return basin_cells[id];
    else return NULL;
}
//______________________________________________________________________________
#ifdef LIU_OLD_OVERLANDFLOW
void BasinClass::OverlandflowTimeloop8D(const double t_start,const double t_length)
{
    //LML 141201 instant flow has a problem
#ifdef CHECK_MASS_BALANCE
    BalanceItem bal_mass[3];
#endif
    //M.Liu added iterations for Heun solution
    /************************************
     *For spatial overland flow:
     *Temp_Cell_Layer_Var[i][0]: temporary pond (m)
     *Temp_Cell_Layer_Var[i][1]: k1 : m2/s
     *Temp_Cell_Layer_Var[i][2]: k2 : m2/2
     *Temp_Cell_Layer_Var[i][3]: (k1 + k2)/2
     ************************************/
    int loops_overlandflow = (int)floor(t_length/ControlRef.getTSOverlandFlow() + 0.5);
    double time_hr(t_start);
    bool instant_runoff(ControlRef.isInstantOverlandFLow());
    for (int T = 0; T < loops_overlandflow; T++) {
        long maxiteration(0); 
        const int layer(0);
        int n(0);
        double totalwater_to_be_routed(0.0);
        initializeBasinLateralFluxesAtLayer(layer);
        if (instant_runoff) {
            maxiteration = num_cells;
            totalwater_to_be_routed = 0;
        } else {
            maxiteration = 3; //0: k1 1: k2: 2: (k1+k2)/2 LML: must be 3
        }
        while (n < maxiteration) {    //Iteration loops
            #pragma omp parallel for num_threads(NUMCORES_TO_USE) //schedule(dynamic,1)
            for (long i = 0;i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
                if (n == 0) {
                    Temp_Cell_Layer_Var[i][layer] = Ponded_m[i];
                    if (instant_runoff) {
                        OutFlow_m[i][layer] = 0;
                        InFlow_m[i][layer] = 0;
                        for (int d = 0; d < 8; d++) OutFlowEachDir_m[i][layer][d] = 0;
                    }
                }
                if (Temp_Cell_Layer_Var[i][layer] > cell->pSoilProfile->SurfaceStorage/1000.0) {
                    if (!instant_runoff) {
                        double hydroslop = Hydro_Standard_Slope[i][layer];
                        if (n < 2) {
                            double flowrate = calcRunoff(cell->pSoilProfile->Manning_coef
                                               ,hydroslop,Temp_Cell_Layer_Var[i][layer]);   //(m2/s)
                            Temp_Cell_Layer_Var[i][n+1] = flowrate; //k1 & k2
                        } else {
                            Temp_Cell_Layer_Var[i][n+1] = (Temp_Cell_Layer_Var[i][1] 
                                                           + Temp_Cell_Layer_Var[i][2]) 
                                                          / 2.0;
                        }
                        //convert (m2/s) into (m); 3600 (s/h); TimeStep_Overlandflow in (h)
                        OutFlow_m[i][layer] = Temp_Cell_Layer_Var[i][n+1] 
                                              * 3600.0 
                                              * ControlRef.getTSOverlandFlow()
                                              / cell->getLength();   //(m)
                        if (OutFlow_m[i][layer] < 0) OutFlow_m[i][layer] = 0;

                        //surface runoff should not be bigger than water available for runoff
                        OutFlow_m[i][layer] = 
                            std::max<double>(Temp_Cell_Layer_Var[i][layer] - cell->pSoilProfile->SurfaceStorage/1000.0,0.0);
                    } else {
                        TempOutFlow_m[i][layer] = 
                            std::max<double>(Temp_Cell_Layer_Var[i][layer] - cell->pSoilProfile->SurfaceStorage/1000.0,0.0);
                        OutFlow_m[i][layer] += TempOutFlow_m[i][layer];
                        Temp_Cell_Layer_Var[i][layer] = 0;
                    }
                }
                //sumout += OutFlow_m[i][layer] * 1000.0;
            } //end i
            //Flow
            #pragma omp parallel for num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0;i < num_cells; i++)
            {   BasinCellClass *cell = basin_cells[i];
                for (int d = 0; d < 8; d++) {             //direction
                    if (!instant_runoff) 
                        OutFlowEachDir_m[i][layer][d] = OutFlow_m[i][layer] 
                                                        * cell->pSoilState->comb_Share_Flow[layer][d];//getFlowPortion(d);
                    else 
                        OutFlowEachDir_m[i][layer][d] += 
                            TempOutFlow_m[i][layer] * cell->pSoilState->comb_Share_Flow[layer][d];//getFlowPortion(d);
                }
            }
            //Fluxes from each grid cell
            #pragma omp parallel for num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0;i < num_cells; i++)
            {   BasinCellClass *cell = basin_cells[i];
                if ((!instant_runoff) || (instant_runoff && n == 0)) 
                    InFlow_m[i][layer] = 0;
                TempInFlow_m[i][layer] = 0;
                for (int d = 0; d < 8; d++) {           //from neighboring grid cells
                    int inflowdir(-1);
                    if (d <= 3) inflowdir = d + 4;
                    else inflowdir = d - 4;
                    long nb_id = cell->getNeighborIndex(d);//getNeighborInnerID(i,d);
                    if (nb_id != -1) {
                        BasinCellClass *cell_nb_id = basin_cells[nb_id];
                        if (!cell_nb_id/*150919RLN basin_cells[nb_id]*/->isOutlet()) {
                            TempInFlow_m[i][layer]
                                += OutFlowEachDir_m[nb_id][layer][inflowdir]
                                   * cell_nb_id/*150919RLN basin_cells[nb_id]*/->getArea()
                                    /cell->getArea();
                        }
                    }
                }//end of d
                if (instant_runoff) InFlow_m[i][layer] += TempInFlow_m[i][layer];
                else InFlow_m[i][layer] = TempInFlow_m[i][layer];
            }//end of i
            //update ponded water
            #pragma omp parallel for num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0; i < num_cells; i++) {
                if (!instant_runoff) {
                    Temp_Cell_Layer_Var[i][layer] += InFlow_m[i][layer] - OutFlow_m[i][layer];   //(mm)
                } else {
                    Temp_Cell_Layer_Var[i][layer] += TempInFlow_m[i][layer];
                    totalwater_to_be_routed += Temp_Cell_Layer_Var[i][layer];
                }
            }//end of i
             n++;
            if (instant_runoff && CORN::is_approximately<double>(totalwater_to_be_routed,0)) 
                n = maxiteration;
        }//Iteration loop
        //Update and check mass balance
#ifdef CHECK_MASS_BALANCE
        #pragma omp parallel for num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (int mass = 0;mass < ControlRef.getSoluteSpecies(); mass++) {
            bal_mass[mass].ClearPoolAndFluxes();
        }
#endif
        #pragma omp parallel for num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++)
        {   BasinCellClass *cell = basin_cells[i];
#ifdef CHECK_MASS_BALANCE
            #pragma omp critical
            {
            bal_mass[MASS_WATER].AddInitPool(Ponded_m[i]);
            bal_mass[MASS_WATER].AddFluxIn(InFlow_m[i][layer]);
            bal_mass[MASS_WATER].AddFluxOut(OutFlow_m[i][layer]);
            bal_mass[MASS_NITRATE].AddInitPool(SoluteAmount[i][0][SL_Nitrate] 
                                               * cell/*150919RLN basin_cells[i]*/->getArea());
            bal_mass[MASS_AMONIA].AddInitPool(SoluteAmount[i][0][SL_Ammonia]
                                              * cell/*150919RLNbasin_cells[i]*/->getArea());
            }
#endif
            Ponded_m[i] += (InFlow_m[i][layer] - OutFlow_m[i][layer]); //(m)
            assert(Ponded_m[i]>=0);                                              //140911LML
            for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
                OutFlowSolute[i][layer][s] = 
                        std::min<double>
                           (OutFlow_m[i][layer] * SoluteConc[i][layer][s]
                           ,SoluteAmount[i][layer][s]) * cell->getArea();        //140911LML  make sure during each time loop not more than itself flowed out
                InFlowSolute[i][layer][s] = 0;
                for (int d = 0; d < 8; d++) {
                    int inflowdir(-1);
                    if (d <= 3) inflowdir = d + 4;
                    else inflowdir = d - 4;
                    long nb_id = cell->getNeighborIndex(d);//getNeighborInnerID(i,d);
                    if (nb_id != -1)
                    {   BasinCellClass *cell_nb = basin_cells[nb_id];
                        if (!cell_nb->isOutlet()) {
                            InFlowSolute[i][layer][s] += 
                                    std::min<double>(OutFlowEachDir_m[nb_id][layer][inflowdir] 
                                                     * SoluteConc[nb_id][layer][s],
                                                     SoluteAmount[nb_id][layer][s])
                                                     * cell_nb->getArea();
                        }
                    }
                }
                SoluteAmount[i][layer][s] += 
                    (InFlowSolute[i][layer][s] - OutFlowSolute[i][layer][s]) / cell->getArea();
                if (SoluteAmount[i][layer][s] < 0 && 
                  CORN::is_approximately<double>(SoluteAmount[i][layer][s],0)) 
                    SoluteAmount[i][layer][s] = 0;
                
                assert(SoluteAmount[i][layer][s] >=0);    //LML 140911
                
            }
#ifdef CHECK_MASS_BALANCE
            #pragma omp critical
            {
            bal_mass[MASS_NITRATE].AddFluxIn(InFlowSolute[i][0][SL_Nitrate]);
            bal_mass[MASS_NITRATE].AddFluxOut(OutFlowSolute[i][0][SL_Nitrate]);
            bal_mass[MASS_AMONIA].AddFluxIn(InFlowSolute[i][0][SL_Ammonia]);
            bal_mass[MASS_AMONIA].AddFluxOut(OutFlowSolute[i][0][SL_Ammonia]);

            bal_mass[MASS_WATER].AddFinalPool(Ponded_m[i]);
            bal_mass[MASS_NITRATE].AddFinalPool(SoluteAmount[i][0][SL_Nitrate] * cell->getArea());
            bal_mass[MASS_AMONIA].AddFinalPool(SoluteAmount[i][0][SL_Ammonia] * cell->getArea());
            }
#endif
            cell->pSoilState->Hourly_Runoff_m += OutFlow_m[i][layer];
            cell->pSoilState->Hourly_Runon_m += InFlow_m[i][layer];
            cell->pSoilState->Daily_Runoff_m += OutFlow_m[i][layer];
            cell->pSoilState->Daily_Runon_m += InFlow_m[i][layer];
            cell->hourly_flow_m3.SurfaceOut += cell->get_m3_from_m(OutFlow_m[i][layer]);
            cell->hourly_flow_m3.SurfaceIn += cell->get_m3_from_m(InFlow_m[i][layer]);
            //Add chemical outputs LML 04/03/2014
            for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
                cell->hourly_flow_solute_kg[s].SurfaceIn += InFlowSolute[i][layer][s];
                cell->hourly_flow_solute_kg[s].SurfaceOut += OutFlowSolute[i][layer][s];
            }

            //std::clog<<" T:"<<T<<" oldpond:"<<oldpond*1000.0<<" new pond:"<<newpond*1000<<" runoff:"<<OutFlow_m[i][layer]*1000.0<<std::endl;
        }   //end i

        //Update concentration now
        #pragma omp parallel for num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++) {
            for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
                if (!CORN::is_approximately<double>(Ponded_m[i],0.0)) 
                    SoluteConc[i][layer][s] = SoluteAmount[i][layer][s] / Ponded_m[i];
                else SoluteConc[i][layer][s] = 0;
            }
        }
#ifdef CHECK_MASS_BALANCE
        std::string massname[] = {"Overland_Flow_Water","Overland_Flow_Nitrate","Overland_Flow_Amonia"};
        for (int mass = 0; mass < ControlRef.getSoluteSpecies(); mass++) {
            if (!bal_mass[mass].IsMassBalance()) {
                bal_mass[mass].PrintMassBalanceTerms(massname[mass]);
            }
        }   //mass
#endif
        time_hr += ControlRef.getTSOverlandFlow();
    }//end of T
}
#endif
//______________________________________________________________________________
void BasinClass::OverlandflowTimeloop8D_Simple(const double t_start,const double t_length)
{
    //LML 141201 same approach with VB version except the instant flow.
    int loops_overlandflow = (int)floor(t_length/ControlRef.getTSOverlandFlow() + 0.5);
    double time_hr = t_start;
    bool instant_runoff = ControlRef.isInstantOverlandFLow();
    int solutes = ControlRef.getSoluteSpecies();
    for (int T = 0; T < loops_overlandflow; T++) {
        const int layer(0);
        long n(0L);
        initializeBasinLateralFluxesAtLayer(layer);
        ////LML 150216 double totalwater_to_be_routed(0.0);
        long maxiteration(0);
        if (instant_runoff) maxiteration = num_cells;
        else maxiteration = 1L;             
        while (n < maxiteration) {    //Iteration loops
            #pragma omp parallel for                                             //170713 num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0; i < num_cells; i++) {
                BasinCellClass *cell = basin_cells[i];
                if (n == 0) {
                    Temp_Cell_Layer_Var[i][layer] = Ponded_m[i];
                    assert(Temp_Cell_Layer_Var[i][layer] >= 0.0);
                    OutFlow_m[i][layer] = 0;
                    InFlow_m[i][layer] = 0;
                    for (int d = 0; d < 8; d++) OutFlowEachDir_m[i][layer][d] = 0;
                    for (int s = 0; s < solutes; s++) {
                        OutFlowSolute[i][layer][s] = 0;
                        InFlowSolute[i][layer][s] = 0;
                        TempSoluteAmount[i][layer][s] = SoluteAmount[i][layer][s];
                        TempSoluteConc[i][layer][s] = !is_approximately(Ponded_m[i],0.0) ? SoluteAmount[i][layer][s] / Ponded_m[i] : 0.0;
                        /*std::clog<<"OVERLANDFLOW:"
                                 <<"\thour:"<<ControlRef.hour
                                 <<"\tcell:"<<cell->getCellId()
                                 <<"\tlayer:"<<layer
                                 <<"\ts:"<<(s == SL_Ammonia ? "NH4" : (s == SL_Nitrate ? "NO3" : "PO4"))
                                 <<"\tamount:"<<TempSoluteAmount[i][layer][s]
                                 <<"\tConc:"<<TempSoluteConc[i][layer][s]
                                 <<std::endl;*/
                        assert(TempSoluteAmount[i][layer][s] >= 0.0);
                        assert(TempSoluteConc[i][layer][s] >= 0.0);
                    }
                }
                if (Temp_Cell_Layer_Var[i][layer] > mm_to_m(cell->pSoilProfile->SurfaceStorage)) {
                    double flowrate(0.0);
                    //if (ControlRef.hour == 14 && cell->getCellId() == 1) {
                    //    double test = Temp_Cell_Layer_Var[i][layer];
                    //}
                    if (!instant_runoff && !cell->isOutlet()) {                  //161115LML if it is outlet, let it go.
                        double hydroslop = cell->soil_tallies->Hydro_Standard_Slope[layer];
                        flowrate = std::min<double>(calcRunoff(cell->pSoilProfile->Manning_coef,
                                                    hydroslop,Temp_Cell_Layer_Var[i][layer])      /*(m2/s)*/
                                                    * 3600.0 * ControlRef.getTSOverlandFlow() 
                                                    / cell->getLength(),
                                                    Temp_Cell_Layer_Var[i][layer]);   //(m/T)
                    }
                    else{
                        flowrate = Temp_Cell_Layer_Var[i][layer];
                    }

                    #ifdef CHECK_HOURLY_CASCADE_FOR_DEBUG
                    flowrate = 0.0;
                    std::clog<<"OVERLANDFLOW IS SETTING ZERO!!!\n";
                    #endif

                    //surface runoff should not be bigger than water available for runoff
                    TempOutFlow_m[i][layer] = 
                        std::max<double>(flowrate - mm_to_m(cell->pSoilProfile->SurfaceStorage),0.0);
                    //double temp = TempOutFlow_m[i][layer] * cell->getArea();
                    TempOutFlow_m[i][layer] = CORN::must_be_less_or_equal_to<double>(
                                                TempOutFlow_m[i][layer],
                                                Temp_Cell_Layer_Var[i][layer]); 
                    TempOutFlow_m[i][layer] *= cell->soil_tallies/* pSoilState*/->comb_Share_Flow[layer][8];         //160722RLN_141204LML
                       // check if there is outflow


                    /*if (cell->isOutlet())
                    std::clog   << "\tn:"               << n
                                << "\tmaxiteration:"    << maxiteration
                                << "\tflowrate (m/T):"  << flowrate
                                << "\tpond_m:"          << Temp_Cell_Layer_Var[i][layer]
                                << "\thour:"            << ControlRef.hour
                                << "\tcell:"            << cell->getCellId()
                                << "\tFlowOut_m3:"      << (TempOutFlow_m[i][layer] * cell->getArea())
                                << "\tTempOutFlow_m:"   << TempOutFlow_m[i][layer]
                                << "\thydro_slope:"     << cell->soil_tallies->Hydro_Standard_Slope[layer] //Hydro_Standard_Slope[i][layer]
                                << "\tmanning:"         << cell->pSoilProfile->Manning_coef
                                << "\tLength:"          << cell->getLength()
                                << std::endl;*/
                    
                    for (int s = 0; s < solutes; s++) {
                        TempOutFlowSolute[i][layer][s] = 
                                std::min<double>(TempOutFlow_m[i][layer] * TempSoluteConc[i][layer][s],
                                                 TempSoluteAmount[i][layer][s]) * cell->getArea();
                        /*std::clog<<"cell:"<<cell->getCellId()
                                <<"\ts : "<<(s == SL_Ammonia ? "NH4" : (s == SL_Nitrate ? "NO3" : "PO4"))
                                <<"\tTempOutFlowSolute : "<<TempOutFlowSolute[i][layer][s]
                                <<"\tTempOutFlow_m : "<<TempOutFlow_m[i][layer]
                                <<"\tSoluteConc : "<<TempSoluteConc[i][layer][s]
                                <<"\tSoluteAmount:"<<TempSoluteAmount[i][layer][s]
                                <<std::endl;*/
                    }
                }
                else{
                    TempOutFlow_m[i][layer] = 0.0;
                    for (int s = 0; s < solutes; s++)
                        TempOutFlowSolute[i][layer][s] = 0.0;
                }
                assert(TempOutFlow_m[i][layer] >= 0.0);
            }//end cells

            //Flow to each direction
            #pragma omp parallel for                                             //170713 num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0; i < num_cells; i++)
            {   BasinCellClass *cell = basin_cells[i];
                for (int d = 0; d < 8; d++) {             //direction
                    TempOutFlowEachDir_m[i][layer][d] = 
                        TempOutFlow_m[i][layer] * cell->soil_tallies/*160722RLN pSoilState*/ ->comb_Share_Flow[layer][d]; //160722RLN
                    /*if (i == 0)
                    std::clog<<"CELL[0] direction:"<<d
                            <<"\tFlowOut_dir_m3: "<<TempOutFlowEachDir_m[i][layer][d] * cell->getArea()
                            <<std::endl;*/
                }
            }
            //Inflows from upstream gridcell
            #pragma omp parallel for                                             //170713 num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0; i < num_cells; i++)
            {   BasinCellClass *cell = basin_cells[i];
                TempInFlow_m[i][layer] = 0;
                for (int s = 0; s < solutes; s++)
                    TempInFlowSolute[i][layer][s] = 0;
                for (int d = 0; d < 8; d++) {           //from neighboring grid cells
                    int inflowdir(-1);
                    if (d <= 3) inflowdir = d + 4;
                    else inflowdir = d - 4;
                    long nb_id = cell->getNeighborIndex(d);//getNeighborInnerID(i,d);
                    if (nb_id != -1)
                    {   BasinCellClass *cell_nb_id = basin_cells[nb_id];
                        //if (basin_cells[nb_id]->getGridType() != 1) {
                            TempInFlow_m[i][layer] += TempOutFlowEachDir_m[nb_id][layer][inflowdir]
                                                     * cell_nb_id->getArea()
                                                     / cell->getArea();
                            for (int s = 0; s < solutes; s++) {
                                TempInFlowSolute[i][layer][s] += 
                                    std::min<double>(TempOutFlowEachDir_m[nb_id][layer][inflowdir] 
                                                     * TempSoluteConc[nb_id][layer][s],
                                                     TempSoluteAmount[nb_id][layer][s]) 
                                                     * cell_nb_id->getArea();
                            }
                        //}
                    }
                }//end of d
                assert(TempInFlow_m[i][layer] >= 0.0);
            }//end of i
            //update ponded water & solute
            double totalwater_to_be_routed(0.0);    //LML 150216 moved here
            //#pragma omp parallel for  /*schedule(dynamic,1)*/ reduction(+:totalwater_to_be_routed)
            for (long i = 0;i < num_cells; i++) {
                BasinCellClass *cell = basin_cells[i];
                //double test = TempInFlow_m[i][layer] * cell->getArea(); //m3
                /*if (i == 0)
                std::clog<<"hour:"<<ControlRef.hour
                        <<" cell:"<<cell->getCellId()
                        <<" FlowIn_m3: "<<test
                        <<std::endl;*/

                Temp_Cell_Layer_Var[i][layer] += 
                    TempInFlow_m[i][layer] - TempOutFlow_m[i][layer];
                if (Temp_Cell_Layer_Var[i][layer] < 0 && 
                   CORN::is_approximately<double>(Temp_Cell_Layer_Var[i][layer],0.0)) 
                    Temp_Cell_Layer_Var[i][layer] = 0.0;
                
                //assert(Temp_Cell_Layer_Var[i][layer] >= 0.0);
                if (instant_runoff) {
                    totalwater_to_be_routed += CORN::must_be_greater_or_equal_to<double>(
                        Temp_Cell_Layer_Var[i][layer] - mm_to_m(cell->pSoilProfile->SurfaceStorage),
                        0.0);
                }
                
                for (int s = 0; s < solutes; s++) {
                    TempSoluteAmount[i][layer][s] += (TempInFlowSolute[i][layer][s] 
                                                      - TempOutFlowSolute[i][layer][s]) 
                                                      / cell->getArea();
                    TempSoluteConc[i][layer][s] = !is_approximately(Temp_Cell_Layer_Var[i][layer],0.0)
                                                  ? TempSoluteAmount[i][layer][s] / Temp_Cell_Layer_Var[i][layer]
                                                  : 0.0;                         //160321LML

                    if (TempSoluteAmount[i][layer][s] < 0 && 
                        CORN::is_approximately<double>(TempSoluteAmount[i][layer][s],0)) 
                        TempSoluteAmount[i][layer][s] = 0;
                    if (TempSoluteAmount[i][layer][s] < 0.0) {
                        printf("Cell-ID:%d s:%s L:%d,TempSoluteAmount:%lf TempInFlowSolute:%lf TempOutFlowSolute:%lf\n",
                               cell->getCellId(),
                               Solute_Name[s].c_str(),
                               layer,TempSoluteAmount[i][layer][s],
                               TempInFlowSolute[i][layer][s],
                               TempOutFlowSolute[i][layer][s]);
                        assert(false);
                    }
                }
            }//end of i
            #pragma omp parallel for                                             //170713 num_threads(NUMCORES_TO_USE)                //schedule(dynamic,1)
            for (long i = 0; i < num_cells; i++) {
                BasinCellClass *cell = basin_cells[i];
                OutFlow_m[i][layer] += TempOutFlow_m[i][layer];
                InFlow_m[i][layer] += TempInFlow_m[i][layer];
                //double tempOut = OutFlow_m[i][layer] * cell->getArea();
                //double tempIn = InFlow_m[i][layer] * cell->getArea();
                for (int s = 0; s < solutes; s++) {
                    OutFlowSolute[i][layer][s] += TempOutFlowSolute[i][layer][s];
                    InFlowSolute[i][layer][s] += TempInFlowSolute[i][layer][s];
                }
            }
            n++;
            if (instant_runoff && CORN::is_approximately<double>(totalwater_to_be_routed,0)) {
                #ifdef LIU_DEBUG
                //printf("Loop num for routing instant runoff:%d\n",n);
                #endif
                n = maxiteration;
            }
        }//Iteration loop

        //Update and check mass balance
#ifdef CHECK_MASS_BALANCE
        BalanceItem bal_mass[3];
#endif
        //#pragma omp parallel for num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
#ifdef CHECK_MASS_BALANCE
            #pragma omp critical
            {
            bal_mass[MASS_WATER].AddInitPool(Ponded_m[i]);
            bal_mass[MASS_WATER].AddFluxIn(InFlow_m[i][layer]);
            bal_mass[MASS_WATER].AddFluxOut(OutFlow_m[i][layer]);
            bal_mass[MASS_NITRATE].AddInitPool
                (SoluteAmount[i][0][SL_Nitrate] * cell->getArea());
            bal_mass[MASS_AMONIA].AddInitPool
                (SoluteAmount[i][0][SL_Ammonia] * cell->getArea());
            }
#endif
            Ponded_m[i] = Temp_Cell_Layer_Var[i][0];
            SoluteAmount[i][0][SL_Nitrate] = TempSoluteAmount[i][0][SL_Nitrate];
            SoluteAmount[i][0][SL_Ammonia] = TempSoluteAmount[i][0][SL_Ammonia];

            /*if (cell->isOutlet())
            std::clog << "\tEND T step:"<<T
                      << "\tcell:"<<cell->getCellId()
                      << "\thour:"<<ControlRef.hour
                      << "\tpond_m:" << Ponded_m[i]
                      //<<"\tSoluteAmount[SL_Nitrate]:"<<SoluteAmount[i][layer][SL_Nitrate]
                      //<<"\tSoluteAmount[SL_Ammonia]:"<<SoluteAmount[i][layer][SL_Ammonia]
                      << std::endl;*/

            assert(Ponded_m[i]>=0.0);                                         //LML 140911
            assert(SoluteAmount[i][0][SL_Nitrate] >= 0.0);
            assert(SoluteAmount[i][0][SL_Ammonia] >= 0.0);
#ifdef CHECK_MASS_BALANCE
            #pragma omp critical
            {
            bal_mass[MASS_NITRATE].AddFluxIn(InFlowSolute[i][0][SL_Nitrate]);
            bal_mass[MASS_NITRATE].AddFluxOut(OutFlowSolute[i][0][SL_Nitrate]);
            bal_mass[MASS_AMONIA].AddFluxIn(InFlowSolute[i][0][SL_Ammonia]);
            bal_mass[MASS_AMONIA].AddFluxOut(OutFlowSolute[i][0][SL_Ammonia]);

            bal_mass[MASS_WATER].AddFinalPool(Ponded_m[i]);
            bal_mass[MASS_NITRATE].AddFinalPool(SoluteAmount[i][0][SL_Nitrate] 
                                                * cell->getArea());
            bal_mass[MASS_AMONIA].AddFinalPool(SoluteAmount[i][0][SL_Ammonia]
                                                * cell->getArea());
            }
#endif
            cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Runoff_m += OutFlow_m[i][layer];
            cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Runon_m += InFlow_m[i][layer];
            cell->soil_tallies/*160722RLN pSoilState*/->Daily_Runoff_m += OutFlow_m[i][layer];
            cell->soil_tallies/*160722RLN pSoilState*/->Daily_Runon_m += InFlow_m[i][layer];
            cell->hourly_flow_m3.SurfaceOut += cell->get_m3_from_m(OutFlow_m[i][layer]);
            cell->hourly_flow_m3.SurfaceIn += cell->get_m3_from_m(InFlow_m[i][layer]);
            //Add chemical outputs LML 04/03/2014
            for (int s = 0; s < solutes; s++) {
                cell->hourly_flow_solute_kg[s].SurfaceIn += InFlowSolute[i][layer][s];
                cell->hourly_flow_solute_kg[s].SurfaceOut += OutFlowSolute[i][layer][s];
            }
            //std::clog<<" T:"<<T<<" oldpond:"<<oldpond*1000.0<<" new pond:"<<newpond*1000<<" runoff:"<<OutFlow_m[i][layer]*1000.0<<std::endl;
        }   //end i

        //Update concentration now
        //151028LML #pragma omp parallel for schedule(dynamic,1)
        //151028LML for (long i = 0; i < num_cells; i++) {
        //151028LML     for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
        //151028LML         if (!CORN::is_approximately<double>(Ponded_m[i],0.0,1e-12))
        //151028LML             SoluteConc[i][layer][s] = SoluteAmount[i][layer][s] / Ponded_m[i];
        //151028LML         else SoluteConc[i][layer][s] = 0;
        //151028LML     }
        //151028LML }
#ifdef CHECK_MASS_BALANCE
        std::string massname[] = {"Overland_Flow_Water","Overland_Flow_Nitrate","Overland_Flow_Amonia"};
        for (int mass = 0; mass < solutes; mass++) {
            if (!bal_mass[mass].IsMassBalance(1e-5)) {
                bal_mass[mass].PrintMassBalanceTerms(massname[mass]);
            }
        }   //mass
#endif
        time_hr += ControlRef.getTSOverlandFlow();
    }//end of T
}
//______________________________________________________________________________
//LML 150110 obsolete
/*
void BasinClass::OverlandflowTimeloop4D(const CORN::Date& today,const double t_start,const double t_length)
{
    //New code from FMS Mar.7, 2014
    //New Sub FMS 12/16/2013
    //M.Liu did't check the code yet!!! March 14, 2014

    double Cell_InOutFlow_X;    //net
    double Cell_InOutFlow_Y;
    int i,layer;

    double TimeAveragedWaterDepth; //New 1/25/2014
    double TimeAveragedWaterDepth_JminusOne; //New 1/25/2014
    double TimeAveragedWaterDepth_IminusOne; //New 1/25/2014
    int MaximumNumberOfIterations; //New 1/25/2014
    int n; //New 1/25/2014
    double Error; //New 1/25/2014
    double OldError; //New 1/25/2014
    double Overland_Budget;
    double AcceptableErrorChange;  //New 1/25/2014
    //double Saved_Time_Step; //New 1/25/2014
    int left_cell,right_cell,upper_cell,lower_cell; //left:West right: East upper: North Lower: South
    double Element_Length;
    int hour;

    double ExcessOutflow;
    //double OutFlow_X;
    //double OutFlow_Y;
    double TotalOutFlow;
    double OutFlowReductionFactor;

    int loops_overlandflow = (int)floor(t_length/ControlRef.getTSOverlandFlow() + 0.5);
    double TimeStep_Overlandflow = ControlRef.getTSOverlandFlow();

    MaximumNumberOfIterations = 4; // FMS Jan 27, 2014
    AcceptableErrorChange = 0.001; // FMS Jan 27, 2014
    layer = 0;

    #pragma omp parallel for
    for (i = 0; i < num_cells;i++) {
        TotalDownhillflow[i][layer] = Ponded_m[i]; //(m)
        InitialCellWaterDepth[i] = TotalDownhillflow[i][layer];    //(m)
    }

    Error = 0;
    Overland_Budget = 0;

    for (int T = 0; T < loops_overlandflow; T++) {
        n = 0;
        hour = (int)floor(t_start + T * TimeStep_Overlandflow);
        while(n < MaximumNumberOfIterations) {
            #pragma omp parallel for private(Element_Length,left_cell,upper_cell,TimeAveragedWaterDepth,TimeAveragedWaterDepth_JminusOne,TimeAveragedWaterDepth_IminusOne)
            for (i = 0;i < num_cells; i++) {
                Element_Length = basin_cells[i]->getLength();
                left_cell = basin_cells[i]->getNeighborIndex(NB_W);//getNeighborInnerID(cell,NB_W);
                upper_cell = basin_cells[i]->getNeighborIndex(NB_N);

                TimeAveragedWaterDepth = (InitialCellWaterDepth[i] + TotalDownhillflow[i][layer]) / 2.0;

                if (left_cell >= 0) {
                    TimeAveragedWaterDepth_JminusOne = (InitialCellWaterDepth[left_cell] + TotalDownhillflow[left_cell][layer]) / 2.0;
                    CellFrictionSlope_X[i] = basin_cells[i]->getCellBedslopeX() +
                                                 (TimeAveragedWaterDepth_JminusOne - TimeAveragedWaterDepth) / Element_Length;
                    if (CellFrictionSlope_X[i] >= 0)
                        CellFlowIn_X[i] = calcRunoff(ManningCoef[left_cell],CellFrictionSlope_X[i],TimeAveragedWaterDepth_JminusOne,-9999.0);
                    else
                        CellFlowIn_X[i] = -calcRunoff(ManningCoef[i],CellFrictionSlope_X[i],TimeAveragedWaterDepth_JminusOne,-9999.0);
                }
                else CellFlowIn_X[i] = 0;

                if (upper_cell >= 0) {
                    TimeAveragedWaterDepth_IminusOne = (InitialCellWaterDepth[upper_cell] + TotalDownhillflow[left_cell][layer]) / 2.0; // COS New 1/25/2014
                    CellFrictionSlope_Y[i] = basin_cells[i]->getCellBedslopeY() +
                                                 (TimeAveragedWaterDepth_IminusOne - TimeAveragedWaterDepth) / Element_Length;
                    if (CellFrictionSlope_Y[i] >= 0)
                        CellFlowIn_Y[i] = calcRunoff(ManningCoef[upper_cell],CellFrictionSlope_Y[i],TimeAveragedWaterDepth_IminusOne,-9999.0);
                    else
                        CellFlowIn_Y[i] = -calcRunoff(ManningCoef[i],CellFrictionSlope_Y[i],TimeAveragedWaterDepth_IminusOne,-9999.0);
                }
                else CellFlowIn_Y[i] = 0;
            }//end cell

            //Calculate change in water depth

            for (i = 0;i < num_cells; i++) {
                //new lines add COS Jan 25, 2014
                Element_Length = basin_cells[i]->getLength();
                left_cell = basin_cells[i]->getNeighborIndex(NB_W);
                upper_cell = basin_cells[i]->getNeighborIndex(NB_N);
                right_cell = basin_cells[i]->getNeighborIndex(NB_E);
                lower_cell = basin_cells[i]->getNeighborIndex(NB_S);

                Cell_InOutFlow_X = (CellFlowIn_X[right_cell] - CellFlowIn_X[i]) / (Element_Length); // (m/s) depth of water +:outflow -:inflow
                Cell_InOutFlow_Y = (CellFlowIn_Y[lower_cell] - CellFlowIn_Y[i]) / (Element_Length); // (m/s)
                double Previus_Depth; //COS Jan 25, 2014
                Previus_Depth = TotalDownhillflow[i][layer];

                TotalDownhillflow[i][layer] = InitialCellWaterDepth[i] -
                                                   (Cell_InOutFlow_X + Cell_InOutFlow_Y) * TimeStep_Overlandflow * 3600; //(m) Time step is in hours
                Error += fabs(OldCellWaterDepth[i] - TotalDownhillflow[i][layer]);
                OldCellWaterDepth[i] = TotalDownhillflow[i][layer];
                //Recalculate to ensure that cell water depth is not negative (reducing outflow proportionally)
                if (TotalDownhillflow[i][layer] < -1.0e-10) {

                    ExcessOutflow = -TotalDownhillflow[i][layer] / (TimeStep_Overlandflow * 3600);  //m/s
                    //Check amount of out flow
                    if (CellFlowIn_X[right_cell] > 0) TotalOutFlow = TotalOutFlow + CellFlowIn_X[right_cell];
                    if (CellFlowIn_Y[lower_cell] > 0) TotalOutFlow = TotalOutFlow + CellFlowIn_Y[lower_cell];
                    //Also check negative inflow
                    if (CellFlowIn_X[i] < 0) TotalOutFlow = TotalOutFlow + CellFlowIn_X[i];
                    if (CellFlowIn_Y[i] < 0) TotalOutFlow = TotalOutFlow + CellFlowIn_Y[i];
                    //if (TotalOutFlow < 0.000000000001 Then TotalOutFlow = 0.000000000001
                    OutFlowReductionFactor = 1 - ExcessOutflow / TotalOutFlow;
                    if (CellFlowIn_X[right_cell] > 0) CellFlowIn_X[right_cell] = CellFlowIn_X[right_cell] * OutFlowReductionFactor;
                    if (CellFlowIn_Y[lower_cell] > 0) CellFlowIn_Y[lower_cell] = CellFlowIn_Y[lower_cell] * OutFlowReductionFactor;
                    if (CellFlowIn_X[i] < 0) CellFlowIn_X[i] = CellFlowIn_X[i] * OutFlowReductionFactor;
                    if (CellFlowIn_Y[i] < 0) CellFlowIn_Y[i] = CellFlowIn_Y[i] * OutFlowReductionFactor;
                    TotalDownhillflow[i][layer] = 0;
                }
            }
            //OverralErrorChange = Abs(OldError - Error)
            Overland_Budget = fabs(OldError - Error);
            n++;
        }   //n

        #pragma omp parallel for
        for (i = 0;i < num_cells; i++) {
            basin_cells[i]->hourlySurfaceOutFlow_m3 += basin_cells[i]->get_m3_from_m(TotalDownhillflow[i][layer]);
            InitialCellWaterDepth[i] = TotalDownhillflow[i][layer];
            if (basin_cells[i]->isOutlet()) TotalDownhillflow[i][layer] = 0;
        }
    }//T

    //end lines added
    #pragma omp parallel for
    for (i = 0;i < num_cells; i++) {
        Ponded_m[i] = TotalDownhillflow[i][layer];
    }
}
*/
//______________________________________________________________________________
void BasinClass::initializeBasinLateralFluxes()
{
    for (int layer = 0; layer <= basin_cells[0]->pSoilProfile->NumberOfLayers() + 1; layer++)
        initializeBasinLateralFluxesAtLayer(layer);
}
//______________________________________________________________________________
void BasinClass::initializeBasinLateralFluxesAtLayer(const int layer)
{
    int solutes = ControlRef.getSoluteSpecies();
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long i = 0; i < num_cells; i++) {
        InFlow_m[i][layer] = 0;
        UpFlow_m[i][layer] = 0;
        OutFlow_m[i][layer] = 0;
        for (int s = 0; s < solutes; s++) {
            UpFlowSolute[i][layer][s] = 0;
            OutFlowSolute[i][layer][s] = 0;
            InFlowSolute[i][layer][s] = 0;
        }
    }
}
//______________________________________________________________________________
void BasinClass::SoilLateralflowTimeloop(const double t_start,const double t_length)
{
    #ifdef MBVB_FD
    float64 K_sat_pedotransfer_L; //(m/h)
    #endif
    double time_hr = t_start;
    int loops_soillateralflow = (int)floor(t_length / ControlRef.getTSSoilLateralFlow() + 0.5);
    for (int T = 0; T < loops_soillateralflow; T++) {
        //Initialize fluxes
        initializeBasinLateralFluxes();
        //Calculate outflow and initilize upflow from each grid cell
        int cells = NumCells();
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < cells; i++) {
         BasinCellClass *cell = basin_cells[i];
			int number_of_layers = cell->pSoilProfile->NumberOfLayers();
            for (int layer = 1; layer <= number_of_layers; layer++) {
                //calculate unused store (m)
                Unused_store_m[i][layer] = std::max<double>(
                            (Theta_s[i][layer] - Theta[i][layer]) * L_thickness[i][layer],0);
                #ifdef MBVB_FD
                double K_sat_pedotransfer_L = 
                        basin_cells[i]->pSoilProfile->K_Sat[layer] * m_h_P_KgS_m3; //(m/h) converted from (kg/s/m3)
                #endif

                //131121 RLN Warning I need to check which K_sat to use!!!!
                #ifndef MBVB_FD
                //LML 150518 for calculating K_Theta for Lateralflow
                double Ksat       = cell->pSoilProfile->K_Sat_Lateral_Flow[layer] * m_h_P_KgS_m3;
                double Campbell_b = cell->pSoilProfile->get_Campbell_b(layer,false);
                Soil_hydrology_abstract *hydrology =
                   #ifdef MBVB_SOIL
                      (Soil_hydrology_abstract *) cell->pSoilState->hydrology;
                   #else
                      cell->ref_soil()->ref_hydrology();                         //160722RLN
                   #endif
                double Theta_b    = hydrology->calc_Theta_b(layer,Campbell_b);
                #endif

                K_Theta[i][layer] =
                #ifdef MBVB_FD
                    calc_K_Theta(Theta[i][layer], Theta_s[i][layer]
                                             ,K_sat_pedotransfer_L
                                             ,cell->pSoilProfile->b_Value[layer]//Soil_Complete.properties.hydraulics.get_Campbell_b(L,false) // need to check this
                                             ,cell->pSoilProfile->Theta_b[layer])
                    * cell->pSoilState->getFactorCalibrationLaterFlow(layer);
                #else
                    //LML 150518 cell->pSoilState->hydrology->
                    //LML 150518     get_K_Theta(layer,Theta[i][layer], Theta_s[i][layer]);
                    cell->pSoilState->get_K_Theta_Lateralflow(layer
                                                              ,Theta[i][layer]
                                                              ,Theta_s[i][layer]
                                                              ,Ksat
                                                              ,Theta_b);
                #endif
                /*std::clog<<"\ni:"<<i<<"\tlayer:"<<layer
                         <<"\nTheta:"           <<Theta[i][layer]
                         <<"\tTheta_s:"         <<Theta_s[i][layer]
                         <<"\tKsat:"            <<Ksat
                         <<"\tTheta_b:"         <<Theta_b
                         <<"\tTheta:"       <<Theta[i][layer]
                         <<"\tTheta_b:"     <<Theta_b
                         <<"\tK_Theta:"     <<K_Theta[i][layer]
                         <<std::endl;*/

                //LML 150518 K_Theta[i][layer] *= cell->pSoilState->getFactorCalibrationLaterFlow(layer);        //FMS Mar 12, 2014
                
                //calculate total lateral downhill-flow (m)
                if (cell->isOutlet() && ControlRef.isDoSoilLaterFlow())          //161115LML
                    OutFlow_m[i][layer] = CORN::must_be_greater_or_equal_to(Theta[i][layer] - cell->pSoilProfile->get_field_capacity_volumetric(layer),0.0) * L_thickness[i][layer];
                else
                OutFlow_m[i][layer] = std::min<double>((K_Theta[i][layer] 
                                                        * Hydro_Standard_Slope[i][layer] 
                                                        * ControlRef.getTSSoilLateralFlow() 
                                                        * L_thickness[i][layer] 
                                                        / cell->getLength())
                                                       ,(Theta[i][layer] * L_thickness[i][layer]));                                          //FMS Apr 18, 2014


                //if (t_start == 0 && T == 0) std::clog<<"Debug:0.10 SPEED FOR LATERAL FLOW!\n";
                //OutFlow_m[i][layer] *= 0.1;



                OutFlow_m[i][layer] *= cell->soil_tallies/*160722 pSoilState*/->comb_Share_Flow[layer][8];         //LML 141204 check if there is any kinds of outflow

                if (OutFlow_m[i][layer] < 0.0) OutFlow_m[i][layer] = 0.0;
                /*std::clog<<"\nT:"           <<T
                         <<"\thour:"        <<ControlRef.hour
                         <<"\tCell#:"       <<cell->getCellId()
                         <<"\tL:"           <<layer
                         <<"\tH_Slop:"      <<Hydro_Standard_Slope[i][layer]
                         <<"\tTheta:"       <<Theta[i][layer]
                         <<"\tTheta_b:"     <<Theta_b
                         <<"\tNO3_N_kg/ha:"    <<per_m2_to_per_ha(NO3_to_N_conv * SoluteAmount[i][layer][SL_Nitrate])
                         <<"\tNH4_N_kg/ha:"    <<per_m2_to_per_ha(NH4_to_N_conv * SoluteAmount[i][layer][SL_Ammonia])
                         <<"\tK_Theta:"     <<K_Theta[i][layer]
                         <<"\tOutFlow_mm:"  <<m_to_mm(OutFlow_m[i][layer])
                         <<std::endl;*/
            }
        }

        //Calculate downhill-flow in each directions
        int solutes = ControlRef.getSoluteSpecies();
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
            int number_of_layers = cell->pSoilProfile->NumberOfLayers();
            for (int layer = 1; layer <= number_of_layers; layer++) {
                for (int d = 0; d < 8; d++) {                                    //direction
                    OutFlowEachDir_m[i][layer][d] = 
                        OutFlow_m[i][layer] * cell->soil_tallies /*160722RLN pSoilState*/->comb_Share_Flow[layer][d]; //160722RLN
                    for (int s = 0; s < solutes; s++) {
                        if (s != SL_Ammonia) {                                   //170425LML_COS: assume NH4 will not move
                            OutFlowSoluteEachDir[i][layer][d][s] =
                                std::max<double>(SoluteAmount[i][layer][s],0.0)
                                * OutFlowEachDir_m[i][layer][d] / (Theta[i][layer] * L_thickness[i][layer])
                                * cell->getArea();                                   //(kg)
                            OutFlowSolute[i][layer][s] += OutFlowSoluteEachDir[i][layer][d][s];
                        } else {
                            OutFlowSoluteEachDir[i][layer][d][s] = 0;
                            OutFlowSolute[i][layer][s]           = 0;
                        }
                    }
                }
            }
        }
        //Inflow & Upflow
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++)
        {   BasinCellClass *cell = basin_cells[i];
			int Bottom_Layer = cell->pSoilProfile->NumberOfLayers();
            for (int layer = Bottom_Layer; layer >= 1; layer--) {
                for (int d = 0; d < 8; d++) {           //from neighboring grid cells
                    int inflowdir(-1);
                    if ( d <= 3) inflowdir = d + 4;
                    else inflowdir = d - 4;
                    long nb_id = cell->getNeighborIndex(d);
                    if (nb_id != -1)
                    {   BasinCellClass *cell_nb = basin_cells[nb_id];            //150919RLN
                        InFlow_m[i][layer] += OutFlowEachDir_m[nb_id][layer][inflowdir]
                                              * cell_nb->getArea()
                                              / cell->getArea();    //LML be careful whether cells have same area
                        for (int s = 0; s < solutes; s++) {
                            InFlowSolute[i][layer][s] += 
                                OutFlowSoluteEachDir[nb_id][layer][inflowdir][s];
                        }
                    }
                }//end of d
                //calculate upward flow of water LML 04/03/2014
                UpFlow_m[i][layer] = std::max<double>(InFlow_m[i][layer] 
                                                      + UpFlow_m[i][layer+1] 
                                                      - OutFlow_m[i][layer] 
                                                      - Unused_store_m[i][layer],
                                                      0.0);    //LML 04/03/2014
                //upward flow of solute. Flowout at first, then flowin, upflow at last. LML 04/03/2014
                for (int s = 0; s < solutes; s++) {
                    double flow_solute = (InFlowSolute[i][layer][s] 
                                          - OutFlowSolute[i][layer][s] 
                                          + UpFlowSolute[i][layer+1][s]) 
                                         / cell->getArea();                      //(kg/m2)
                    double upflow_conc = (SoluteAmount[i][layer][s] + flow_solute)
                                         / (Theta[i][layer]*L_thickness[i][layer] 
                                            + InFlow_m[i][layer] 
                                            + UpFlow_m[i][layer+1] 
                                            - OutFlow_m[i][layer]);   //(kg/m3)
                    UpFlowSoluteConc[i][layer][s] = upflow_conc;                 //160324LML
                    UpFlowSolute[i][layer][s] = UpFlow_m[i][layer] 
                                                * std::max<double>(upflow_conc,0.0) 
                                                * cell->getArea();                       //(kg/cell)
                    //assert(UpFlowSolute[i][layer][s] >= 0.0);
                    if (UpFlowSolute[i][layer][s] < 0.0) {
                        std::cerr<<"Error: UpFlowSolute: "<<UpFlowSolute[i][layer][s]<<" is negtive!\n";
                        assert(false);
                    }
                }
                //checkMassBalance();
            }//end of L
        }//end of i

        //Update state variables
        #ifdef CHECK_MASS_BALANCE
        std::string massname[] = {"SoilLateralflow_Water","SoilLateralflow_Nitrate","SoilLateralflow_Amonia"};
        #endif
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
            double cell_area_m2 = cell->getArea();
            int layers = cell->pSoilProfile->NumberOfLayers();
            //for checking mass balance
#ifdef CHECK_MASS_BALANCE
            BalanceItem bal_mass[3];
            for (int s = 0; s < solutes; s++) {
                bal_mass[s].ClearPoolAndFluxes();
            }
            bal_mass[MASS_WATER].SetInitPool(getGridSoilWater_m(i) + Ponded_m[i]);
            bal_mass[MASS_NITRATE].SetInitPool((getGridSoilNitrate_kg_m2(i) 
                                                + SoluteAmount[i][0][SL_Nitrate]) 
                                                * cell_area_m2);                 //(kg)
            bal_mass[MASS_AMONIA].SetInitPool((getGridSoilAmonia_kg_m2(i) 
                                               + SoluteAmount[i][0][SL_Ammonia])
                                               * cell_area_m2);                  //(kg)
#endif
            //150914LML for (int layer = 1; layer <= cell->pSoilProfile->NumberOfLayers(); layer++) {
            for (int layer = layers; layer >= 1; layer--) {
#ifdef CHECK_MASS_BALANCE
                bal_mass[MASS_WATER].AddFluxIn(InFlow_m[i][layer]);
                bal_mass[MASS_WATER].AddFluxOut(OutFlow_m[i][layer]);
                bal_mass[MASS_NITRATE].AddFluxIn(InFlowSolute[i][layer][SL_Nitrate]);
                bal_mass[MASS_NITRATE].AddFluxOut(OutFlowSolute[i][layer][SL_Nitrate]);
                bal_mass[MASS_AMONIA].AddFluxIn(InFlowSolute[i][layer][SL_Ammonia]);
                bal_mass[MASS_AMONIA].AddFluxOut(OutFlowSolute[i][layer][SL_Ammonia]);
#endif
                double netflow_m = InFlow_m[i][layer]
                                   + UpFlow_m[i][layer+1] 
                                   - OutFlow_m[i][layer]  
                                   - UpFlow_m[i][layer];

                /*if (layer == 1)
                std::clog<<"cell#"<<cell->getCellId()
                         <<"\tL:"<<layer
                         <<"\thour:"<<ControlRef.hour
                         <<"\tnetflow:"<<netflow_m
                         <<"\tInflow:"<<InFlow_m[i][layer]
                         <<"\tUpflow[layer+1]:"<<UpFlow_m[i][layer+1]
                         <<"\tOutflow:"<<OutFlow_m[i][layer]
                         <<"\tUpflow:"<<UpFlow_m[i][layer]
                         <<"\tInflow_NO3:"<<InFlowSolute[i][layer][SL_Nitrate]
                         <<"\tUpflow_NO3[layer+1]:"<<UpFlowSolute[i][layer+1][SL_Nitrate]
                         <<"\tOutflow_NO3:"<<OutFlowSolute[i][layer][SL_Nitrate]
                         <<"\tUpflow_NO3:"<<UpFlowSolute[i][layer][SL_Nitrate]
                         <<std::endl;*/

                Theta[i][layer] += netflow_m / L_thickness[i][layer];
                if (Theta[i][layer] > Theta_s[i][layer]) {
                    double extra_water_m = (Theta[i][layer] - Theta_s[i][layer]) * L_thickness[i][layer]; //150914LML temporary solution for the mass balance problem.
                    Theta[i][layer] = Theta_s[i][layer];
                    //150914assert(false);                                       //150914LML potential risk of mass balance error!!!
                    UpFlow_m[i][layer] += extra_water_m;                         //150914LML
                    //160324LML
                    for (int s = 0; s < solutes; s++) {
                        UpFlowSolute[i][layer][s] += UpFlowSoluteConc[i][layer][s] * extra_water_m * cell_area_m2;
                    }
                }

                for (int s = 0; s < solutes; s++) {
                    double netflow_solute = InFlowSolute[i][layer][s] 
                                            - OutFlowSolute[i][layer][s]
                                            + UpFlowSolute[i][layer+1][s] 
                                            - UpFlowSolute[i][layer][s];         //(kg/cell)
                    SoluteAmount[i][layer][s] += netflow_solute/cell_area_m2;
                    if(SoluteAmount[i][layer][s] < 0 && 
                       abs(SoluteAmount[i][layer][s]) < PERMITTED_ERROR_NUTRIENTS_KG_PER_KM2) 
                        SoluteAmount[i][layer][s] = 0.0;
                    if(SoluteAmount[i][layer][s] < 0){
                        #pragma omp critical
                        std::clog<<"Cell "
                                 <<cell->getCellId()
                                 <<"@layer "
                                 <<layer
                                 <<" produces negtive "
                                 <<Solute_Name[s]
                                 <<" during SoilLateralflowTimeloop!"
                                 <<std::endl;
                        exit(-1);
                    }
                }
                if (layer == 1) {     //LML handle the surface solute and pond
                    if (UpFlow_m[i][layer] > 0) {
                        Ponded_m[i] += UpFlow_m[i][layer]; //(m)
                        for (int s = 0; s < solutes; s++) {
                            SoluteAmount[i][0][s] += UpFlowSolute[i][layer][s] / cell_area_m2;
                            //151028LML SoluteConc[i][0][s] = SoluteAmount[i][0][s] / Ponded_m[i];
                        }
                    }
                }
            }//L
            #ifdef CHECK_MASS_BALANCE
            bal_mass[MASS_WATER].SetFinalPool(getGridSoilWater_m(i) + Ponded_m[i]);
            bal_mass[MASS_NITRATE].SetFinalPool((getGridSoilNitrate_kg_m2(i) 
                                                 + SoluteAmount[i][0][SL_Nitrate]) 
                                                * cell_area_m2);                 //(kg/cell)
            bal_mass[MASS_AMONIA].SetFinalPool((getGridSoilAmonia_kg_m2(i) 
                                                + SoluteAmount[i][0][SL_Ammonia])
                                               * cell_area_m2);                  //(kg/cell)
            #endif

            #ifdef CHECK_MASS_BALANCE
            for (int mass = 0; mass < solutes; mass++) {
                if (!bal_mass[mass].IsMassBalance(1e-5)) {
                    #pragma omp critical
                    {
                        std::clog<<"Grid ID:"<<cell->getCellId()<<std::endl;
                        bal_mass[mass].PrintMassBalanceTerms(massname[mass]);
                        if (mass == MASS_WATER)
                            std::clog<<"\tpond_m:"<<Ponded_m[i]
                                     <<"\tUpFlow:"<<UpFlow_m[i][1];
                        if (mass == MASS_NITRATE)
                            std::clog<<"\tsurface_chemical[NO3]:"<<(SoluteAmount[i][0][SL_Nitrate] * cell_area_m2)
                                     <<"\tUpFlowSolute(kg):"<<UpFlowSolute[i][1][SL_Nitrate];
                        if (mass == MASS_AMONIA)
                            std::clog<<"\tsurface_chemical[NH4]:"<<(SoluteAmount[i][0][SL_Ammonia] * cell_area_m2)
                                     <<"\tUpFlowSolute(kg):"<<UpFlowSolute[i][1][SL_Ammonia];
                        std::clog<<std::endl;
                    }
                }
            }
            #endif
        }//cell

        //Outputs
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
            int layers = cell->getSoilLayers();
            for (int layer = 1; layer <= layers; layer++) {
                cell->hourly_LateralOutFlowLayer_m3[layer] += cell->get_m3_from_m(OutFlow_m[i][layer]);                   //LML 150127
                cell->hourly_LateralOutFlowSoluteLayer_kg[layer][SL_Ammonia] += OutFlowSolute[i][layer][SL_Ammonia];        //LML 150127
                cell->hourly_LateralOutFlowSoluteLayer_kg[layer][SL_Nitrate] += OutFlowSolute[i][layer][SL_Nitrate];      //LML 150127
                cell->hourly_flow_m3.LateralIn += cell->get_m3_from_m(InFlow_m[i][layer]);
                cell->hourly_flow_m3.LateralOut += cell->get_m3_from_m(OutFlow_m[i][layer]);
                if (layer == 1) 
                    cell->hourly_flow_m3.LateralUp += cell->get_m3_from_m(UpFlow_m[i][layer]);
                //Solute flows
                cell->hourly_flow_solute_kg[SL_Ammonia].LateralIn += InFlowSolute[i][layer][SL_Ammonia];
                cell->hourly_flow_solute_kg[SL_Nitrate].LateralIn += InFlowSolute[i][layer][SL_Nitrate];
                cell->hourly_flow_solute_kg[SL_Ammonia].LateralOut += OutFlowSolute[i][layer][SL_Ammonia];
                cell->hourly_flow_solute_kg[SL_Nitrate].LateralOut += OutFlowSolute[i][layer][SL_Nitrate];

                cell->soil_tallies/*160722RLN pSoilState*/->Daily_LaterFlowIn_m += InFlow_m[i][layer];
                cell->soil_tallies/*160722RLN pSoilState*/->Daily_LaterFlowOut_m += OutFlow_m[i][layer];
            } //layer
            //cell->hourlyDrainage_m3 += cell->get_m3_from_m(cell->pSoilState->Hourly_Drainage_m);
        } //i
        time_hr += ControlRef.getTSSoilLateralFlow();
    }//end of T
}
//______________________________________________________________________________
#ifdef MBVB_INFILTRATION
void BasinClass::CalculateInstantRunoff()
{
    //Obsolete LML 140923
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        double instant_Runoff = std::max<double>(Ponded_m[i] 
                                                 - cell->pSoilProfile->SurfaceStorage/1000.0,
                                                 0.0);
        Ponded_m[i] -= instant_Runoff;
        cell->soil_tallies/*160722RLN pSoilState*/->Daily_Runoff_m += instant_Runoff;
        cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Runoff_m = instant_Runoff;
        InFlow_m[i][0] = 0;
        OutFlow_m[i][0] = instant_Runoff;
        cell->hourly_flow_m3.SurfaceOut += cell->get_m3_from_m(instant_Runoff);
    }
}
//______________________________________________________________________________
#endif
//______________________________________________________________________________
long BasinClass::getNeighborInnerID(long itself_inner_id,int nb)
{
    //nb: Neighbor 0-7
    long outid(-1L);
    int nrows = gGridID.getNrows();
    int ncols = gGridID.getNcols();
    BasinCellClass *cell_itself_inner = basin_cells[itself_inner_id];            //150919RLN
    int row = cell_itself_inner->getRow();                                       //150919RLN
    int col = cell_itself_inner->getCol();                                       //150919RLN
    if ((row != -1) && (col != -1)) {
        switch (nb) {
        case NB_E:
            if (col < (ncols-1)) outid = inner_id[row][col+1];
            break;
        case NB_SE:
            if ((row < (nrows-1)) && (col < (ncols-1))) outid = inner_id[row+1][col+1];
            break;
        case NB_S:
            if (row < (nrows-1)) outid = inner_id[row+1][col];
            break;
        case NB_SW:
            if ((row < (nrows-1)) && (col > 0)) outid = inner_id[row+1][col-1];
            break;
        case NB_W:
            if (col > 0)outid = inner_id[row][col-1];
            break;
        case NB_NW:
            if ((row > 0) && (col > 0)) outid = inner_id[row-1][col-1];
            break;
        case NB_N:
            if (row > 0) outid = inner_id[row-1][col];
            break;
        case NB_NE:
            if ((row > 0) && (col < (ncols-1))) outid = inner_id[row-1][col+1];
            break;
        default:
            outid = -1;
            break;
        }
    }
    return outid;
}
//______________________________________________________________________________
/*
void BasinClass::PrintBasinHourlyOutputsHead()
{
    std::clog<<"Year,"
            <<"Month,"
            <<"Day,"
            <<"DOY,"
            <<"Hour,"
            <<"hourlySurfaceInFlow_m3,"
            <<"hourlySurfaceOutFlow_m3,"
            <<"hourlyDrainage_m3,"
            <<"hourlyLateralInFlow_m3,"
            <<"hourlyLateralOutFlow_m3,"
            <<"hourlyLateralUpFlow_m3\n";
}
//______________________________________________________________________________
void BasinClass::PrintBasinHourlyOutputs(const CORN::Date& today,int hour)
{
    int outlet = getOutletInnerID();
    int dayofyear = outday.get_DOY()-1;
	BasinCellClass *cell = basin_cells[outlet];
    std::clog<<outday.get_year()<<","
            <<outday.get_month()<<","
            <<outday.get_DOM()<<","
            <<dayofyear<<","
            <<hour<<","
            <<cell->hourlySurfaceInFlow_m3<<","
            <<cell->hourlySurfaceOutFlow_m3<<","
            <<cell->hourlyDrainage_m3<<","
            <<cell->hourlyLateralInFlow_m3<<","
            <<cell->hourlyLateralOutFlow_m3<<","
            <<cell->hourlyLateralUpFlow_m3<<"\n";
}
*/
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
void BasinClass::PrintBasinOutputs()
{
    //LML not finished yet. Add basin outputs later. 14/04/20
#ifdef LIU_DEBUG
    std::clog<<" PrintBasinOutputs ..."<<std::endl;
#endif
    //LML 14/04/22 Printout initial and final states and accumulated fluxes during simulation period
    std::ofstream of_file(ControlRef.basin_hour_output_filename.c_str(),std::ios::out);//150709RLN
    if (of_file.fail()) {
        char errormessage[200];
        sprintf(errormessage,"Cannot open output file: %s",ControlRef.basin_hour_output_filename.c_str());
        nrerror(errormessage);
    }
    double total_basin_water_storage_change = ((
                                  //final_residue_intercept_m3 +
                                  final_soil_water_m3
                                  + final_soil_ice_m3
                                  #ifdef MBVB_SNOW
                                  + final_snowpack_water_m3
                                  + final_snowpack_ice_m3
                                  #else
                                  + final_snowpack_swe_m3
                                  #endif
                                  + final_pond_m3)
                                 - (//161110LML initial_residue_intercept_m3
                                  + initial_soil_water_m3
                                  + initial_soil_ice_m3
                                  #ifdef MBVB_SNOW
                                  + initial_snowpack_water_m3
                                  + initial_snowpack_ice_m3
                                  #else
                                  + initial_snowpack_swe_m3
                                  #endif
                                  + initial_pond_m3));
    double total_basin_water_netflux = ((cum_precipitation_m3
                                         //161014LML cum_nonintercepted_ppt_m3*/
                                         + cum_irrigation_m3)
                                        - (cum_outlet_lateralflow_m3
                                           + cum_outlet_runoff_m3
                                           + cum_vertical_drainage_m3
                                           + cum_actual_crop_transpiration_m3
                                           + cum_actual_soil_evaporation_m3
                                           + cum_net_sublimation_m3
                                           ));
    
    
    of_file<<"Basin Outputs (cells),"         <<num_cells<<std::endl
            <<"Basin_area(km2),"              <<getBasinAreakm2()                               <<std::endl
            <<"Start_date,"                   <<ControlRef.start_date.as_string()               <<std::endl
            <<"End_date,"                     <<ControlRef.end_date.as_string()                 <<std::endl
            <<"precipitation_m3,"             <<cum_precipitation_m3                            <<std::endl
            <<"nonintercepted_ppt_m3,"        <<cum_nonintercepted_ppt_m3                       <<std::endl
            <<"irrigation_m3,"                <<cum_irrigation_m3                               <<std::endl
            <<"ppt+irrig_m3,"                 <<(cum_precipitation_m3+cum_irrigation_m3)        <<std::endl
            <<"nonintcep_ppt+irrig_m3,"       <<(cum_nonintercepted_ppt_m3+cum_irrigation_m3)   <<std::endl
            <<"outlet_lateralflow_m3,"        <<cum_outlet_lateralflow_m3                       <<std::endl
            <<"outlet_runoff_m3,"             <<cum_outlet_runoff_m3                            <<std::endl
            <<"vertical_drainage_m3,"         <<cum_vertical_drainage_m3                        <<std::endl
            <<"actual_crop_transpiration_m3," <<cum_actual_crop_transpiration_m3                <<std::endl
            <<"actual_total_evaporation_m3,"  <<cum_actual_soil_evaporation_m3                  <<std::endl

            <<"net_sublimation_m3,"           <<cum_net_sublimation_m3                          <<std::endl
            <<"N_movein_basin_kg,"            <<cum_N_movein_basin_kg                           <<std::endl
            <<"N_movein_soil_kg,"             <<cum_N_movein_soil_kg                            <<std::endl
            <<"N_runoff_kg,"                  <<(cum_NO3_N_flowout_basin_kg + cum_NH4_N_flowout_basin_kg)
            <<",NO3_N_flowout_basin_kg,"      <<cum_NO3_N_flowout_basin_kg
            <<",NH4_N_flowout_basin_kg,"      <<cum_NH4_N_flowout_basin_kg                      <<std::endl
            <<"N_leach_kg,"                   <<(cum_NO3_N_drainage_kg + cum_NH4_N_drainage_kg)
            <<",NO3_N_Leach_kg,"              <<cum_NO3_N_drainage_kg
            <<",NH4_N_Leach_kg,"              <<cum_NH4_N_drainage_kg                           <<std::endl
            <<"N_volatization_kg,"            <<cum_N_volatization_kg                           <<std::endl
            <<"crop_N_uptake_kg,"             <<cum_crop_N_uptake_kg                            <<std::endl

            <<"C_residue_to_soil_kg,"         <<cum_C_residue_to_soil_kg                        <<std::endl
            <<"CO2_emission_from_residue_kg," <<cum_CO2_emission_from_residue_kg                <<std::endl
            <<"CO2_emission_from_soil_kg,"    <<cum_CO2_emission_from_soil_kg                   <<std::endl

            <<"initial_soil_water_m3,"            <<initial_soil_water_m3<<","
            <<"final_soil_water_m3,"              <<final_soil_water_m3                         <<std::endl

            <<"initial_soil_ice_m3,"              <<initial_soil_ice_m3<<","
            <<"final_soil_ice_m3,"                <<final_soil_ice_m3                           <<std::endl
            <<"initial_residue_intercept_m3,"     <<-9999/*161110LML initial_residue_intercept_m3*/<<","
            <<"final_residue_intercept_m3,"       <<-9999/*161110LML final_residue_intercept_m3*/                  <<std::endl
            #ifdef MBVB_SNOW
            <<"initial_snowpack_water_m3,"        <<initial_snowpack_water_m3<<","
            <<"final_snowpack_water_m3,"          <<final_snowpack_water_m3                     <<std::endl
              
            <<"initial_snowpack_ice_m3,"          <<initial_snowpack_ice_m3<<","
            <<"final_snowpack_ice_m3,"            <<final_snowpack_ice_m3                       <<std::endl
            #endif
            #ifdef MBVB_SNOW
            <<"initial_SWE_m3,"                   <<(initial_snowpack_water_m3 + initial_snowpack_ice_m3)<<","
            <<"final_SWE_m3,"                     <<(final_snowpack_water_m3 + final_snowpack_ice_m3)<<std::endl
            #else
            <<"initial_SWE_m3,"                   <<initial_snowpack_swe_m3<<","
            <<"final_SWE_m3,"                     <<final_snowpack_swe_m3  <<std::endl
            #endif
                
            <<"initial_pond_m3,"                  <<initial_pond_m3<<","
            <<"final_pond_m3,"                    <<final_pond_m3                               <<std::endl

            <<"initial_soil_C_kg,"                <<initial_soil_C_kg<<","
            <<"final_soil_C_kg,"                  <<final_soil_C_kg<<","
            <<"Change_C_at_Soil,"                 <<(final_soil_C_kg - initial_soil_C_kg)         <<std::endl

            <<"initial_soil_mineral_N_kg,"        <<initial_soil_profile_mineral_N<<","
            <<"final_soil_mineral_N_kg,"          <<final_soil_profile_mineral_N<<","
            <<"Change_soil_mineral_N,"            <<(final_soil_profile_mineral_N - initial_soil_profile_mineral_N)  <<std::endl


            <<"initial_residue_C_kg,"             <<initial_residue_C_kg<<","
            <<"final_residue_C_kg,"               <<final_residue_C_kg<<","
            <<"Change_C_at_Residue,"              <<final_residue_C_kg-initial_residue_C_kg     <<std::endl
              
            <<"----------------------"              <<std::endl
            <<"Cell_Total_Water_Storage_Change_m3," <<total_basin_water_storage_change          <<std::endl
            <<"Cell_Total_Water_Flux(net_in)_m3,"   <<total_basin_water_netflux                 <<std::endl
            <<"----------------------"              <<std::endl;
    //LML 141013 NYI double check!!!
    of_file<<"Year,"
            <<"Month,"
            <<"Monthday,"
            <<"DOY,"
            <<"Hour,"
            <<"Total_Water_Runoff_m3,"
            <<"Total_DIN_Runoff_kg,"
            <<"Basin_Drainage_m3,"
            <<"Basin_Drainage_DIN_kg,"
            <<"OverlandFlow_m3,"
            <<"SoilLaterFLow_m3,"
            <<"OverlandFlow_NO3_kg,"
            <<"OverlandFlow_NH4_kg,"
            <<"OverlandFlow_PO4_kg,"
            <<"SoilLaterFLow_NO3_kg,"
            <<"SoilLaterFLow_NH4_kg,"
            <<"SoilLaterFLow_PO4_kg\n";
    int hourth = 0;
    for (CORN::Date_32_clad today = ControlRef.start_date; today <= ControlRef.end_date;today.inc_day()) {
        for (int hour = 0; hour < 24; hour++) {
            of_file<<(int)today.get_year()<<","
                    <<(int)today.get_month()<<","
                    <<(int)today.get_DOM()<<","
                    <<(int)today.get_DOY()<<","
                    <<hour<<","
                    <<hourlyBasinSurfaceOutFlow_m3[hourth]+hourlyBasinLateralOutFlow_m3[hourth]<<","
                    <<hourlyBasinSurfaceOutFlowSolute_kg[hourth][SL_Nitrate] 
                      + hourlyBasinSurfaceOutFlowSolute_kg[hourth][SL_Ammonia]
                      + hourlyBasinLateralOutFlowSolute_kg[hourth][SL_Nitrate]
                      + hourlyBasinLateralOutFlowSolute_kg[hourth][SL_Ammonia]<<","
                    <<hourlyBasinDrainage_m3[hourth]<<","
                    <<hourlyBasinDrainage_DIN_kg[hourth]<<","
                    <<hourlyBasinSurfaceOutFlow_m3[hourth]<<","
                    <<hourlyBasinLateralOutFlow_m3[hourth]<<","
                    <<hourlyBasinSurfaceOutFlowSolute_kg[hourth][SL_Nitrate]<<","
                    <<hourlyBasinSurfaceOutFlowSolute_kg[hourth][SL_Ammonia]<<","
                    <<hourlyBasinSurfaceOutFlowSolute_kg[hourth][SL_Phosphate]<<","
                    <<hourlyBasinLateralOutFlowSolute_kg[hourth][SL_Nitrate]<<","
                    <<hourlyBasinLateralOutFlowSolute_kg[hourth][SL_Ammonia]<<","
                    <<hourlyBasinLateralOutFlowSolute_kg[hourth][SL_Phosphate]<<"\n";
            hourth++;
        }
    } 
    of_file.close();
    #ifdef LIU_DEBUG
    std::clog<<" PrintBasinOutputs done."<<std::endl;
    #endif
}
//______________________________________________________________________________
#endif

#ifdef CROPSYST_WEATHER
#else
void BasinClass::initializeWeatherStations()
{

    int num_stations(0);
    std::clog<<"ControlRef.weathercontrol_name:"<<ControlRef.weathercontrol_name<<":"<<std::endl;
    std::ifstream ifile(ControlRef.weathercontrol_name.c_str());
    if (ifile.is_open()) {
        //Read the head (number of stations)
        //std::clog<<"weathercontrol_name:"<<ControlRef.weathercontrol_name<<std::endl;
        std::string nameline("");
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            if (record_key.compare("Num_Stations") == 0) {
                std::string dataline("");
                std::getline(ifile,dataline);
                std::stringstream ss(dataline);
                ss>>num_stations;
                ifile.clear();
                ifile.seekg(0,ifile.end);
            }
        }



        if (num_stations >= 1) {
            while (weather_stations.size() < num_stations) {
               #ifndef __BCPLUSPLUS__
               //150317 RLN Not sure why this is not compiling with BC++
                WeatherLocationInputClass temp;
                weather_stations.push_back(temp);
               #endif
            }
        }
         else {
            nrerror("Weather stations file has errors in the number of stations");
        }
#ifdef LIU_DEBUG
        std::clog<<"Number of stations:"<<num_stations<<std::endl;
#endif
        num_weather_stations = num_stations;
        ifile.clear();
        ifile.seekg(0);
        int current_station(-1);
        nameline.clear();
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            if (! record_key.empty()) {
                //read the data line
                std::string dataline("");
                std::getline(ifile,dataline);
                std::stringstream ss(dataline);
                if (dataline.empty() || ! getKeyWord(dataline).empty()) {
                    char errormessage[200];
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    double fdata(0.0);
                    if (record_key.compare("station_id") == 0) {
                        current_station++;
                        //std::clog<<"current_station:"<<current_station<<std::endl;
                        ss>>fdata;
                        #ifdef CROPSYST_VERSION
                        weather_stations[current_station].set_ID((int)fdata);          //141222
                        #else
                        weather_stations[current_station].setStationID((int)fdata);
                        #endif
                        weather_stations[current_station].setInnerID(current_station);
                    }
                    else if (record_key.compare("Latitude") == 0) {
                        ss>>fdata;
                        #ifdef CROPSYST_VERSION
                        weather_stations[current_station].set_latitude_dec_deg_f64(fdata); //151206RLN
                        #else
                        weather_stations[current_station].setLatitude(fdata);
                        #ifdef MACA_V1_MBMET
                        weather_stations[current_station].SnapToGridCenter_Lat(31.020833,0.04166667);
                        #endif
                        #endif
                    }
                    else if (record_key.compare("Longitude") == 0) {
                        ss>>fdata;
                        #ifdef CROPSYST_VERSION
                        weather_stations[current_station].set_longitude_dec_deg_f64(fdata); //151206RLN
                        #else
                        weather_stations[current_station].setLongitude(fdata);
						#ifdef MACA_V1_MBMET
                        weather_stations[current_station].SnapToGridCenter_Lon(-124.770833,0.04166667);
                        #endif
                        #endif
                    }
                    else if (record_key.compare("Altitude") == 0) {
                        ss>>fdata;
                        #ifdef CROPSYST_VERSION
                        weather_stations[current_station].set_elevation_meter((float32)fdata); //141222RLN
                        #else
                        weather_stations[current_station].setAltitude(fdata);
                        #endif
                    }
                    else if (record_key.compare("proj_x") == 0) {
                        ss>>fdata;
                        weather_stations[current_station].setProjX(fdata);
                    }
                    else if (record_key.compare("proj_y") == 0) {
                        ss>>fdata;
                        weather_stations[current_station].setProjY(fdata);
                    }
                    else if (record_key.compare("Screening_Height") == 0) {
                        ss>>fdata;
                        #ifdef CROPSYST_VERSION
                        weather_stations[current_station].set_screening_height((float32)fdata); //141222RLN
                        #else
                        weather_stations[current_station].setScreeningHeight(fdata);
                        #endif
                    }
                    else if (record_key.compare("Weather_File_Path") == 0) {
                        removeWhitespace(dataline);
                        //170110LML TODO: enable to handle relative path
                        const CORN::OS::Directory_entry_name &parent_dir = ControlRef.weathercontrol_name.get_parent_directory_name_qualified(); //170111RLN
                        CORN::OS::Directory_name_concrete weather_file_path_relative(dataline); //170111RLN
                        CORN::OS::Directory_entry_name *weather_file_path_resolved = //170111RLN
                           CORN::OS::file_system_engine.render_resolved_absolute_DEN //170111RLN
                              (weather_file_path_relative,parent_dir);           //170111RLN
                        // Note in the following the WeatherFilePath
                        // could not be a pointer to Directory_entry_name
                        // rather than string so we could just
                        // give weather_file_path_resolved to
                        // that wather station object.  170111RLN
                        weather_stations[current_station].setWeatherFilePath(weather_file_path_resolved->c_str());
                        delete weather_file_path_resolved;
                        //170111RLN weather_stations[current_station].setWeatherFilePath(dataline);
                    }
                    else if (record_key.compare("Weather_File_Prefix") == 0) {
                        removeWhitespace(dataline);
                        weather_stations[current_station].setWeatherFilePrefix(dataline);
                    }
                    else if (record_key.compare("Time_Step_Hours") == 0) {
                        ss>>fdata;
                        weather_stations[current_station].setTimeStepHours((int)fdata);
                    }
                    else if (record_key.compare("Start_Hour_Format") == 0) {
                        ss>>fdata;
                        weather_stations[current_station].setStartHourFormat((int)fdata);
                    }
                    else{
                        char errormessage[200];
                        sprintf(errormessage,"Warning: Can't find keyword %s",record_key.c_str());
                        //nrerror(errormessage);
                    }
                }
            }
        }
    }
    else{
        char errormessage[200];
        sprintf(errormessage,"Cann't open weather control file %s",
                ControlRef.weathercontrol_name
                #ifdef __GNUC__
                .c_str()
                #endif
                );
        nrerror(errormessage);
    }
    ifile.close();
}
#endif
//___150519_____________________________________________________________________
void BasinClass::initializeCropManagementZones()
{
    //Get the crop management type list
    l_crop_management_zones.clear();
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (gGridMask.getValue(i,j) != gGridMask.getNodataValue()) {
                long cropmanagement = gCropManagementZone.getValue(i,j);
                if (cropmanagement != gCropManagementZone.getNodataValue()) {
                    std::vector<long>::iterator iter = std::find(l_crop_management_zones.begin(), l_crop_management_zones.end(), cropmanagement);
                    if (iter == l_crop_management_zones.end()) {
                        l_crop_management_zones.push_back(cropmanagement);
                    }
                }
            }
        }
    }
}
//______________________________________________________________________________
void BasinClass::initializeSoilProperties()
{
#if (defined(TRIVIAL_TEST) && defined(CROPSYST_SOIL))
   std::string soilfilename(ControlRef.soilproperty_prefix_name);
   soilfilename.append("1.CS_soil");
   CORN::VV_File soil_file(soilfilename.c_str());                                //141221
   soil_file.get(single_soil_parameters);
   single_soil_properties = new Soil_properties_sublayers(&single_soil_parameters,false);//141221
   single_soil_properties->reinitialize                                          //141221
               (true    // beginning_of_simulation
               ,false   // not subdivide_horizons                                                         //060229
               ,false);  // not finite_diff
#else
    std::string soilfilename;
    #ifndef __BCPLUSPLUS__
    l_soiltypes.clear();
    #endif
    //Get the soil type list
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    inner_id.resize(nrows);                                                      //160317LML
    for (int i = 0; i < nrows; i++)
        inner_id[i].resize(ncols);                                               //160317LML

    int gridcell = 0;                                                            //160317LML
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            inner_id[i][j] = -1L;                                                //160317LML
            if (gGridMask.IsValidCell(i,j)) {
                inner_id[i][j] = gridcell;                                       //160317LML
                long soiltype = gSoilType.IsValidCell(i,j) ? gSoilType.getValue(i,j) : -1L;
                if (soiltype != -1L) {
                    std::vector<long>::iterator iter = std::find(l_soiltypes.begin(), l_soiltypes.end(), soiltype);
                    if (iter == l_soiltypes.end()) {
                        l_soiltypes.push_back(soiltype);
                    }
                } else {
                    std::cerr<<"\nRow:"<<i<<"\tcol:"<<j<<"\thas no valid soil type!!!\n";
                    exit(1);
                }
                gridcell++;                                                      //160317LML
            }
        }
    }
#ifdef LIU_DEBUG
    std::clog<<"\nSoil type list finished.\n";
#endif
    //Initilize the soil parameter array
    if (l_soiltypes.size() > 0) {
        size_t num_soil_types = l_soiltypes.size();
        //parrSoilProfile = new SoilProfileClass *[num_soil_types];
        parrSoilProfile.resize(num_soil_types,NULL);
        parrInitSoilState.resize(num_soil_types,NULL);                           //160317LML
        int soilindex(0);
        for (std::vector<long>::iterator iter = l_soiltypes.begin(); iter != l_soiltypes.end(); iter++)
        {
#ifdef LIU_DEBUG
            //std::clog<<"Soil type:"<<*iter<<std::endl;
#endif
            parrSoilProfile[soilindex] = new SoilProfileClass(ControlRef);
            parrSoilProfile[soilindex]->setSoilID(*iter);
            parrInitSoilState[soilindex] = new InitialSoilStateClass(*parrSoilProfile[soilindex],ControlRef); //160317LML
            parrInitSoilState[soilindex]->soil_type_id = *iter;                   //160317LML
            #ifdef CROPSYST_SOILFILE
            {
               Soil_parameters_class soil_parameters;                               //141209RLN
               std::string filename = "P:\\REACCH\\Simulation\\Database\\Soil\\675836.CS_soil";

               VV_File soilfile(filename.c_str());
               soilfile.get(soil_parameters);
               parrSoilProfile[soilindex]->initialize_soil_parameters(soil_parameters); //141209RLN
            }
            #else
            std::string soil_profile_ID;
            CORN::append_nat16_to_string((nat16)(*iter), soil_profile_ID);
            CORN::OS::File_name_concrete soil_filename
               (
               //160829LML if the Scenario contril file set the directory, use it; otherwise, use the default soil directory
               ControlRef.soilstate_filename.get_name().find_first_of(L".Soilstate") == 0 ?
               ControlRef.soilstate_filename.get_parent_directory_name_qualified() :
               project_database_directory->Soil()
               ,soil_profile_ID,"Soilstate");

            std::clog  << "\nsoil_filename:" << soil_filename.c_str()
                       << std::endl; 
            parrSoilProfile[soilindex]->ReadSoilProfileParameters
               (soil_filename);                                                  //160307RLN


            if ((soilindex == 0) && ControlRef.use_even_soil_N_and_FC)
                std::clog << "Even soil initial N and Field Capacity soil moisture has been set!\n";


            parrInitSoilState[soilindex]->ReadSoilStateParameters(soil_filename);
               //160307RLN   (*iter);
            #endif
            //LML 141208 parrSoilProfile[soilindex]->estimateSoilProfileProperties();
            soilindex++;
        }
    } else {
        nrerror("Soil types are wrong (less than 1 valid types)!");
    }
#endif //Trivel test
}
//______________________________________________________________________________
/*160808RLN this would not work
#ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
void BasinClass::initializeRotationParameters()
{
    std::string rotfilename;
    #ifndef __BCPLUSPLUS__
    l_rotationtypes.clear();                                                     //160317LML
    #endif
    //Get the soil type list
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (gGridMask.IsValidCell(i,j)) {
                long rotationtype = gRotationID.IsValidCell(i,j) ? gRotationID.getValue(i,j) : -1L;
                if (rotationtype != -1L) {
                    std::vector<long>::iterator iter = std::find(l_rotationtypes.begin(), l_rotationtypes.end(), rotationtype);
                    if (iter == l_rotationtypes.end()) {
                        l_rotationtypes.push_back(rotationtype);
                    }
                } else {
                    std::cerr<<"\nRow:"<<i<<"\tcol:"<<j<<"\thas no valid rotation type!!!\n";
                    exit(1);
                }
            }
        }
    }
#ifdef LIU_DEBUG
    std::clog<<"\nRotation type list finished.\n";
#endif
    //Initilize the rotation parameter array
    if (l_rotationtypes.size() > 0) {
        size_t num_rot_types = l_rotationtypes.size();
        //parrSoilProfile = new SoilProfileClass *[num_soil_types];
        #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
        parrRotation_params.resize(num_rot_types,NULL);
        #endif
        int rotindex(0);
        for (std::vector<long>::iterator iter = l_rotationtypes.begin(); iter != l_rotationtypes.end(); iter++)
        {
#ifdef LIU_DEBUG
            //std::clog<<Rotation type:"<<*iter<<std::endl;
#endif
            char rot_ID_string[20];
            CORN::int32_to_cstr((int32)*iter,rot_ID_string,10);
            CORN::OS::File_name_concrete composed_rotation_filename
                (project_database_directory->Rotation(),rot_ID_string,"rot");
            CORN::OS::File_name_concrete rotation_filename;
            rotation_filename.set_DEN(composed_rotation_filename);
            parrRotation_params[rotindex] = new CropSyst::Rotation_parameters();
            VV_File rotation_file(rotation_filename.c_str());//130827
            std::clog<<"Rotation:"<<*iter
                     <<"Index:"<<rotindex
                     <<"Rotation file name:"<<rotation_filename.c_str()
                     <<std::endl;
            rotation_file.get(*parrRotation_params[rotindex]);
            rotindex++;
        }
    } else {
        nrerror("Rotation types are wrong (less than 1 valid types)!");
    }
}
#endif
*/
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
std::string BasinClass::getSoilPropertyFileName(int soiltype_id)
{
    std::wstring filename_with_ID(ControlRef.soilproperty_filename.get_name());
    append_nat32_to_wstring((nat32)soiltype_id,filename_with_ID);
    CORN::OS::File_name_concrete soilproperty_filename_with_ID
       (ControlRef.soilproperty_filename.get_parent_directory_name_qualified()
       ,soilproperty_filename_with_ID,ControlRef.soilproperty_filename.get_extension());
}
//______________________________________________________________________________
#endif
long BasinClass::getNumSoiltypes()
{
    //Total number of soil types within basin boundary
    return (long)l_soiltypes.size();
}
/* 150519
//______________________________________________________________________________
long BasinClass::getInnerIDSoiltypes(long soiltype)
{
    long sid(-1L);
    std::vector<long>::iterator iter = std::find(l_soiltypes.begin(),l_soiltypes.end(),soiltype);
    if (iter != l_soiltypes.end()) sid = (long)std::distance(l_soiltypes.begin(),iter);
    //std::clog<<"sid:"<<sid<<std::endl;
    return sid;
}
*/
//______________________________________________________________________________
template <class Type> long BasinClass::getInnerIDFromVectorList(std::vector<Type> &vector_list, Type target)
{
    long sid(-1);
    std::vector<long>::iterator iter = std::find(vector_list.begin(),vector_list.end(),target);
    if (iter != vector_list.end()) sid = (long)std::distance(vector_list.begin(),iter);
    return sid;
}
//______________________________________________________________________________
int BasinClass::getNeighborRow(int irow,int nb)
{
    int nbrow(-1);
    if (nb == NB_N || nb == NB_NW || nb == NB_NE) nbrow = irow - 1;
    else if (nb == NB_E || nb == NB_W) nbrow = irow;
    else if (nb == NB_SE || nb == NB_S || nb == NB_SW) nbrow = irow + 1;

    if (nbrow >= gGridMask.getNrows() || nbrow < 0) nbrow = -1;
    return nbrow;
}
//______________________________________________________________________________
int BasinClass::getNeighborCol(int icol,int nb)
{
    int nbcol(-1);
    if (nb == NB_NW || nb == NB_W || nb == NB_SW) nbcol = icol - 1;
    else if (nb == NB_N || nb == NB_S) nbcol = icol;
    else if (nb == NB_NE || nb == NB_E || nb == NB_SE) nbcol = icol + 1;
    if (nbcol >= gGridMask.getNcols() || nbcol < 0) nbcol = -1;
    return nbcol;
}
//______________________________________________________________________________
#ifndef CROPSYST_WEATHER
void BasinClass::initializeWeatherStationsDataVector()
{
    //Allocate memory and initialize weather station information for each station
    weather_station_annual_hourly_data.resize(num_weather_stations_over_study_domain,NULL);
    for (int i = 0; i < num_weather_stations_over_study_domain; i++) {
        #ifdef MACA_V1_MBMET
        auto p = weather_station_list_in_study_domain.begin();
        std::advance(p,i);
        int stationindex = getInnerIDWeatherStation(*p);
        #else
        int stationindex = i;
        #endif
        assert(stationindex >= 0);
        weather_station_annual_hourly_data[i] = 
            new WeatherSingleYearHourlyClass
               (
               /*RLN NYI
                #ifndef MBVB_WEATHER_HOURLY
                weather_stations[stationindex]
               ,extraterrestrial_solar_irradiance // common for the entire basin
               ,sun_hours
               ,
               #endif
               */
               weather_stations[stationindex],366
               ,ControlRef.getInvalidMetLabel()
               );                                //160308RLN
    }
}
//______________________________________________________________________________
void BasinClass::readWeatherStationAnnualHourlyData(const int year)
{
    //Read all weather station data for one year
    for (int i = 0; i < num_weather_stations; i++) {
        weather_station_annual_hourly_data[i]->Read_Weather_File(year);
    }
}
#endif
//______________________________________________________________________________
bool BasinClass::start_year()                                                    //141221RLN
{   bool started = true;                                                         //141221RLN
    //Preparation for new year simulation
	#ifndef CROPSYST_WEATHER
    int year = today.get_year();                                                 //141221RLN
    readWeatherStationAnnualHourlyData(year);
	#endif
    int cells = NumCells();
    for (long i = 0; i < cells; i++)
    {   BasinCellClass *cell = basin_cells[i];                                   //150919RLN
        started &= cell->start_year();                                           //150919RLN_141221RLN
    }
    return started;                                                              //141211RLN
}
// ______________________________________________________________________________
#ifndef CROPSYST_WEATHER
void BasinClass::setDailyWeather
(
//160308RLN now member const CORN::Date& today,
#ifndef MACA_V1_MBMET
int stationid
#endif
)
{
#ifdef CELL_METEOROLOGY
    //Set daily weather data for each grid cell
	#ifndef MACA_V1_MBMET
    int weatherstation = getInnerIDWeatherStation(stationid);
    if (weatherstation == -1) {
        nrerror("Cannot find weather station!");
    } else {
	#endif
        int cells = NumCells();
        #pragma omp parallel for num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long i = 0; i < cells; i++) {
            BasinCellClass *cell = basin_cells[i];
#ifdef MACA_V1_MBMET
            int weatherstation = cell->index_weather_station_data;
#endif
            cell->pWeatherDaily->copyHourlyWeatherFromStation
               (weather_station_annual_hourly_data[weatherstation]);
            cell->weather_station_elev =
                weather_station_annual_hourly_data[weatherstation]->weather_station.
                    #ifdef CROPSYST_VERSION
                    get_elevation();                                             //141222
                    #else
                    getAltitude();
                    #endif
        }
#ifndef MACA_V1_MBMET
    }
#endif
#else
   // There is now one weather for the entire basin
   // There is no need for each cell to have its own weather

   meteorology->know_weather_spanning(*pWeatherDaily);                           //160810RLN
   pWeatherDaily->copyHourlyWeatherFromStation                                   //160810RLN
      (weather_station_annual_hourly_data[0 /*weatherstation*/]);                //160810RLN
#endif
}
#endif
// ______________________________________________________________________________
#ifndef CROPSYST_WEATHER
int BasinClass::getInnerIDWeatherStation(const int stationid)
{
    int innerid(-1);
    for (long i = 0; i < num_weather_stations; i++) {
        if (weather_stations[i].
            #ifdef CROPSYST_VERSION
            get_ID()                                                             //141222
            #else
            getStationID()
            #endif
            == stationid) {
            innerid = i;
            i = num_weather_stations;
        }
    }
    return innerid;
}
#endif
//______________________________________________________________________________
void BasinClass::WatershedPropertiesCalculation(const int hour)
{
    int layers = ControlRef.getMaxSoilLayers();
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    for (int layer = 0; layer < layers; layer++) {
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long ij = 0; ij < nrows * ncols ; ij++) {
            long i = (long) (ij / ncols);
            long j = ij % ncols;
            long cellid = inner_id[i][j];
            int numlayers = 0;
            BasinCellClass *cell = NULL;
            if (cellid >= 0) {
                cell = basin_cells[cellid];
                numlayers = cell->getSoilLayers();
            }
            //bool bt = ControlRef.PerchedWT_Enabled;
            if (cellid >= 0 &&
              layer <= numlayers &&
              ControlRef.PerchedWT_Enabled) {
                if (layer == 0) {
                    vHydroElevation[layer][i][j] =
                        gElev.getValue(i,j) + cell->pond.get_depth();
                } else {
                    vHydroElevation[layer][i][j] = cell->getElev();
                }
            } else {
                vHydroElevation[layer][i][j] = gElev.getValue(i,j);
            }
        }//ij

        calcSum_Downhillslopes(vHydroElevation[layer],vSum_Downhillslopes[layer]);
        calcFlow_share(vHydroElevation[layer],
                       vSum_Downhillslopes[layer],
                       v_Share_flow[layer]);
        calcStandardslope(vHydroElevation[layer],
                          inner_id,
                          vHydroStandardslope[layer]);
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long ij = 0; ij < nrows * ncols; ij++) {
            long i = (long) (ij / ncols);
            long j = ij % ncols;
            long cellid = inner_id[i][j];
            int numlayers = 0;
            BasinCellClass *cell = NULL;
            if (cellid >= 0) {
                cell = basin_cells[cellid];
                /*std::clog<<"layer:"<<layer
                         <<"\tvHydro:"<<vHydroElevation[layer][i][j]
                         <<"\tvSum_Downhillslopes:"<<vSum_Downhillslopes[layer][i][j]
                         <<"\vHydroStandardslope:"<<vHydroStandardslope[layer][i][j]
                         <<std::endl;*/
                numlayers = cell->getSoilLayers();
            }
            KS[layer][i][j] = 0;
            if (cellid >= 0 && layer <= numlayers) {
                if (layer > 0) {
                    KS[layer][i][j] =
//140527RLN							#ifdef MBVB_INFILTRATION
                            cell->pSoilProfile->K_Sat[layer] * m_h_P_KgS_m3; //(m/h)
//140527RLN							#else
//140527RLN                            cell->pSoilProfile->soil_properties_ref.get_hydraulic_properties_constant()->get_sat_hydraul_cond_m_hr(layer);
//140527RLN							#endif
                }
                if (CORN::is_approximately<double>(vSum_Downhillslopes[layer][i][j],0.0))
                    cell->soil_tallies/*160722RLN pSoilState*/->Hydro_Standard_Slope[layer] = 0.0;
                else cell->soil_tallies/*160722RLN pSoilState*/->Hydro_Standard_Slope[layer] = vHydroStandardslope[layer][i][j];

                if (! ControlRef.isDoSoilLaterFlow() && layer > 0)
                    cell->soil_tallies/*160722RLN pSoilState*/->Hydro_Standard_Slope[layer] = 0;           //LML 140813

                Hydro_Standard_Slope[cellid][layer] = cell->soil_tallies->Hydro_Standard_Slope[layer]; //160930LML
                //LML 14/04/25 added the same method as FMS
                //'calculate "drop" at outlet using user-defined elevation of cell below outlet-cell (subOLC),
                // i.e. user can define the flow-velocity of the outlet cell
                /*151015LML disabled
                if (cell->isOutlet()) {
                    if (!ControlRef.isDoSoilLaterFlow() && layer > 0) {
                        cell->pSoilState->Hydro_Standard_Slope[layer] = 0;       //LML 140813
                    } else {
                        if (ControlRef.method_outlet_flowrate == OUTLET_CONSTANT_SLOP) {//constant slop)
                            cell->pSoilState->Hydro_Standard_Slope[layer] = ControlRef.constant_outlet_slop_or_elevation;
                        } else {
                            double outlet_elev;
                            if (ControlRef.method_outlet_flowrate == OUTLET_CONSTANT_ELEV)
                                outlet_elev = ControlRef.constant_outlet_slop_or_elevation;
                            else
                                outlet_elev = cell->getMinElevNeighbors();
                            if (layer == 0) {
                                cell->pSoilState->Hydro_Standard_Slope[layer] =
                                  (gElev.getValue(i,j)
                                   //#ifdef CROPSYST_FD
                                   + cell->pond.get_depth()
                                   //#else
                                   //+ cell->pSoilState->Hourly_Ponded_Water_m
                                   //#endif
                                   - outlet_elev)
                                  / cell->getLength();
                            } else {
                                if (cell->pSoilState->get_liquid_water_content_volumetric(layer) >
                                        (0.99 * cell->pSoilProfile->get_saturation_water_content_volumetric(layer,cell->pSoilState->Ice_Content[layer]))) {
                                    cell->pSoilState->Hydro_Standard_Slope[layer] =
                                      (gElev.getValue(i,j)
                                       + cell->pSoilProfile->get_thickness_m(layer)
                                       - outlet_elev)
                                      / cell->getLength();
                                } else {
                                    cell->pSoilState->Hydro_Standard_Slope[layer] =
                                      (gElev.getValue(i,j)
                                       - outlet_elev)
                                      / cell->getLength();
                                }
                            }
                        }//end of constant elevation
                    }//end of isDoSpatialSimulation

                    if (cell->pSoilState->Hydro_Standard_Slope[layer] < 0.0)
                        nrerror("Outletslope must be greater than 0, otherwise water will not flow out.");
                }//end of outlet
                */
                /*std::clog<<"\nCell#:"   <<cell->getCellId()
                         <<"\tL:"       <<layer
                         <<"\tH_slope:" <<cell->pSoilState->Hydro_Standard_Slope[layer];*/
            }
        }  //ij
    }  //L
    //Create 8 arrays which contains the combined shareflow of slope and KS; Note: this is not in the orig. SMR model!
    //this is the product of {KS * (share of dowhillslope_CardinalPoint)} / {all such eight products}
    for (int layer = 0; layer < layers; layer++) {
        #pragma omp parallel for                                                 //170713 num_threads(NUMCORES_TO_USE)                    //schedule(dynamic,1)
        for (long ij = 0; ij < nrows * ncols ; ij++) {
            long i = (long) (ij / ncols);
            long j = ij % ncols;
            for (int d = 0; d < 9; d++) {
                comb_Share_flow[layer][i][j][d] = 0;
            }
            if (inner_id[i][j]>=0) {
                long cellid = inner_id[i][j];
                BasinCellClass* cell = basin_cells[cellid];
                if (layer > 0) {
                    std::vector<double> KS_nb(8,0.0);   //LML 150127
                    bool cell_is_outlet = cell->isOutlet();
                    for(int d = 0; d < 8; d++){
                        long nb_inner_index = cell->getNeighborIndex(d);
                        bool nb_cell_exist = (nb_inner_index >= 0) ? true:false;

                        bool nb_is_outlet = nb_cell_exist ?
                                            basin_cells[nb_inner_index]->isOutlet()
                                            : false;
                        if (cell_is_outlet && !nb_cell_exist) {
                            KS_nb[d] = KS[layer][i][j];
                        } else if (cell_is_outlet &&
                                   nb_cell_exist &&
                                   !nb_is_outlet) {
                            KS_nb[d] = 0;
                            //LML & Fidel 150213 no flows from outlets to neighbpring grid cells
                        } else {
                            switch(d){
                            case NB_NW:
                                KS_nb[d] = KS[layer][i - 1][j - 1];
                                break;
                            case NB_N:
                               KS_nb[d] = KS[layer][i - 1][j];
                               break;
                            case NB_NE:
                                KS_nb[d] = KS[layer][i - 1][j + 1];
                                break;
                            case NB_E:
                                KS_nb[d] = KS[layer][i][j + 1];
                                break;
                            case NB_SE:
                                KS_nb[d] = KS[layer][i + 1][j + 1];
                                break;
                            case NB_S:
                                KS_nb[d] = KS[layer][i + 1][j];
                                break;
                            case NB_SW:
                                KS_nb[d] = KS[layer][i + 1][j - 1];
                                break;
                            case NB_W:
                                KS_nb[d] = KS[layer][i][j - 1];
                                break;
                            default:
                                KS_nb[d] = 0.0;
                            } //end switch
                        } //end if
                    } //end d
                    double tmpDenominator(0);
                    for (int d = 0; d < 8; ++d){
                        tmpDenominator += v_Share_flow[layer][i][j][d] * KS_nb[d];
                    }
                    if (!CORN::is_approximately<double>(tmpDenominator,0)) {
                        for (int d = 0; d < 8; ++d){
                            comb_Share_flow[layer][i][j][d] = v_Share_flow[layer][i][j][d] * KS_nb[d] / tmpDenominator;
                        }
                    }
                } else {   //L=0 no correction of comb_Share_flow with saturated hydraulic conductivity for surface flow!
                    for (int d = 0; d < 8; d++)
                        comb_Share_flow[layer][i][j][d] = v_Share_flow[layer][i][j][d];
                }
                for (int d = 0; d < 8; d++)
                    comb_Share_flow[layer][i][j][8] += comb_Share_flow[layer][i][j][d]; //LML 141204 total fraction
                assert(CORN::is_approximately<double>(comb_Share_flow[layer][i][j][8],0.0) ||
                       CORN::is_approximately<double>(comb_Share_flow[layer][i][j][8],1.0));
                /*for (int d = 0; d<8;d++) {
                    std::clog<<"Cell_ID:"<<basin_cells[cellid]->getCellId()
                                <<" L:"<<layer
                                <<" comb_f["<<d<<"]:"<<comb_Share_flow[layer][i][j][d]
                                <<" sum:"<<comb_Share_flow[layer][i][j][8]
                                <<std::endl;
                }*/
                //Write data to soil state
                if (layer <= cell->getSoilLayers()) {
                    //LML 150127 if (layer == 0) {
                        cell->hourly_fraction_leaving_watershed[layer] = 0.0;
                    //}
                    for (int d = 0; d < 8; d++) {
                        cell->soil_tallies/*160722RLN pSoilState*/->comb_Share_Flow[layer][d] =
                            comb_Share_flow[layer][i][j][d];
                        if (cell->isOutlet()) {
                            //Fraction that leaving WS
                            if (cell->getNeighborIndex(d) < 0)
                                cell->hourly_fraction_leaving_watershed[layer] +=
                                    comb_Share_flow[layer][i][j][d];
                        }
                        /*std::clog<<"\nCell#:"           <<cell->getCellId()
                                 <<"\tdirection:"       <<d
                                 <<"\tcomb_Share_flow:" <<comb_Share_flow[layer][i][j][d];*/
                    }
                    cell->soil_tallies/*160722RLN pSoilState*/->comb_Share_Flow[layer][8] =
                        comb_Share_flow[layer][i][j][8];   //LML 141204 total fraction
                    /*if (cell->hourly_fraction_leaving_watershed[layer] > 1.e-6)
                        std::clog<<"\nCell_ID:"          <<cell->getCellId()
                                 <<"\tL:"                <<layer
                                 <<"\ttotal_FFrac:"      <<comb_Share_flow[layer][i][j][8]
                                 <<"\tfrac_LeavingWS:"   <<cell->hourly_fraction_leaving_watershed[layer]
                                 <<std::endl;*/
                    //Initialize hourly fluxes
                    cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Runoff_m = 0;
                    cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Runon_m = 0;
                }
            }  //if
        }  //ij
    }
    if (!ControlRef.PerchedWT_Enabled)
       ControlRef.PerchedWT_Disabled_Watershed_Property_Calculated = true;          //151019
}
// ______________________________________________________________________________
void BasinClass::calcSum_Downhillslopes(const std::vector<std::vector<double> > &elev,
                                        std::vector<std::vector<double> > &output)
{
    double r = 1.0/sqrt(2.0);
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long ij = 0; ij < nrows * ncols ; ij++) {
        long i = (long) (ij / ncols);
        long j = ij % ncols;
        long cell_index = inner_id[i][j];
        if (cell_index >= 0) {
            double sumslop = 0;
            for (int d = 0; d < 8; d++) {
                const BasinCellClass *cell = basin_cells[cell_index];            //150919RLN
                long neighbor_index = cell->getNeighborIndex(d);                 //150919RLN
                double slop(0);
                if (neighbor_index < 0 && !cell->isOutlet())                     //150919RLN
                    slop = 0;   // if outlet, using all around elevation         //141202LML
                else {
                    if (d == NB_NW) slop = std::max<double>(elev[i][j]-elev[i-1][j-1],0) * r;
                    else if (d == NB_N) slop = std::max<double>(elev[i][j]-elev[i-1][j],0);
                    else if (d == NB_NE) slop = std::max<double>(elev[i][j]-elev[i-1][j+1],0) * r;
                    else if (d == NB_E) slop = std::max<double>(elev[i][j]-elev[i][j+1],0);
                    else if (d == NB_SE) slop = std::max<double>(elev[i][j]-elev[i+1][j+1],0) * r;
                    else if (d == NB_S) slop = std::max<double>(elev[i][j]-elev[i+1][j],0);
                    else if (d == NB_SW) slop = std::max<double>(elev[i][j]-elev[i+1][j-1],0) * r;
                    else slop = std::max<double>(elev[i][j]-elev[i][j-1],0);
                }
                sumslop += slop;
                //std::clog<<"KKK i:"<<i<<" j:"<<j<<" d:"<<d<<" slop:"<<slop<<" sumslop:"<<sumslop<<std::endl;
            }
            output[i][j] = sumslop;
        } else {
            output[i][j] = 0;
        }
    }
}
// ______________________________________________________________________________
void BasinClass::calcFlow_share(const std::vector<std::vector<double> > &elev,
                                const std::vector<std::vector<double> > &sumslop,
                                std::vector<std::vector<std::vector<double> > > &output)
{
    double r = 1.0/sqrt(2.0);
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long ij = 0; ij < nrows * ncols ; ij++) {
        long i = (long) (ij / ncols);
        long j = ij % ncols;
        //for (int j = 0; j<ncols; j++) {
            long cell_index = inner_id[i][j];
            if (cell_index >= 0) {
                for (int d = 0; d < 8; d++) {
                    const BasinCellClass *cell = basin_cells[cell_index];        //150919RLN
                    long neighbor_index = cell->getNeighborIndex(d);             //150919RLN
                    double slop(0.0);
                    if (neighbor_index < 0 && !cell->isOutlet()) {
                        slop = 0;
                    } else {
                        if (d == NB_NW)      slop = std::max<double>(elev[i][j]-elev[i-1][j-1],0) * r;
                        else if (d == NB_N)  slop = std::max<double>(elev[i][j]-elev[i-1][j],0);
                        else if (d == NB_NE) slop = std::max<double>(elev[i][j]-elev[i-1][j+1],0) * r;
                        else if (d == NB_E)  slop = std::max<double>(elev[i][j]-elev[i][j+1],0);
                        else if (d == NB_SE) slop = std::max<double>(elev[i][j]-elev[i+1][j+1],0) * r;
                        else if (d == NB_S)  slop = std::max<double>(elev[i][j]-elev[i+1][j],0);
                        else if (d == NB_SW) slop = std::max<double>(elev[i][j]-elev[i+1][j-1],0) * r;
                        else slop = std::max<double>(elev[i][j]-elev[i][j-1],0);
                        /*std::clog<<"Direction:"<<d
                                 <<"Slop:"<<slop
                                 <<"i:"<<i
                                 <<"j:"<<j
                                 <<std::endl;*/
                    }
                    if (!CORN::is_approximately<double>(sumslop[i][j],0.0)) 
                        output[i][j][d] = slop/sumslop[i][j];
                    else output[i][j][d] = 0;
                    //std::clog<<"cellid:"<<basin_cells[cell_index]->getCellId()<<" d:"<<d<<" slop:"<<slop<<" sumslop:"<<sumslop[i][j]<<std::endl;
                }
            }
            //else output[i][j] = 0;
        //}
    }
}
// ______________________________________________________________________________
void BasinClass::calcStandardslope(const std::vector<std::vector<double> > &elev,
                                   const std::vector<std::vector<long> > &mask,
                                   std::vector<std::vector<double> > &output)
{
    int nrows = gGridMask.getNrows();
    int ncols = gGridMask.getNcols();
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long ij = 0; ij < nrows * ncols ; ij++) {
        long irow = (long) (ij / ncols);
        long icol = ij % ncols;
        if (mask[irow][icol] >= 0) {
            long cellid = inner_id[irow][icol];
            BasinCellClass *cell = basin_cells[cellid];                          //150915
            std::vector<double> temp_neighbor_hydro_elev(8);  //(m) M.Liu
            for (int d = 0; d < 8;  d++) {
                long neighbor_index = cell->getNeighborIndex(d);                 //150919RLN
                //151015LML if (neighbor_index >= 0) {
                    switch(d) {
                    case NB_NW:
                        temp_neighbor_hydro_elev[d] = elev[irow-1][icol-1];
                        break;
                    case NB_N:
                        temp_neighbor_hydro_elev[d] = elev[irow-1][icol];
                        break;
                    case NB_NE:
                        temp_neighbor_hydro_elev[d] = elev[irow-1][icol+1];
                        break;
                    case NB_W:
                        temp_neighbor_hydro_elev[d] = elev[irow][icol-1];
                        break;
                    case NB_E:
                        temp_neighbor_hydro_elev[d] = elev[irow][icol+1];
                        break;
                    case NB_SW:
                        temp_neighbor_hydro_elev[d] = elev[irow+1][icol-1];
                        break;
                    case NB_S:
                        temp_neighbor_hydro_elev[d] = elev[irow+1][icol];
                        break;
                    case NB_SE:
                        temp_neighbor_hydro_elev[d] = elev[irow+1][icol+1];
                        break;
                    }
                //151015LML } else {
                //151015LML    temp_neighbor_hydro_elev[d] = elev[irow][icol];
                //151015LML}
            }

            double a = temp_neighbor_hydro_elev[NB_NW] +
                    2 * temp_neighbor_hydro_elev[NB_W] +
                    temp_neighbor_hydro_elev[NB_SW];
            double b = temp_neighbor_hydro_elev[NB_NE] +
                    2 * temp_neighbor_hydro_elev[NB_E] +
                    temp_neighbor_hydro_elev[NB_SE];
            double c = temp_neighbor_hydro_elev[NB_NW] +
                    2 * temp_neighbor_hydro_elev[NB_N] +
                    temp_neighbor_hydro_elev[NB_NE];
            double dd = temp_neighbor_hydro_elev[NB_SW] +
                    2 * temp_neighbor_hydro_elev[NB_S] +
                    temp_neighbor_hydro_elev[NB_SE];
            //a = elev[irow-1][icol-1] + 2 * elev[irow][icol-1] + elev[irow+1][icol-1];
            //b = elev[irow-1][icol+1] + 2 * elev[irow][icol+1] + elev[irow+1][icol+1];
            //c = elev[irow-1][icol-1] + 2 * elev[irow-1][icol] + elev[irow-1][icol+1];
            //d = elev[irow+1][icol-1] + 2 * elev[irow+1][icol] + elev[irow+1][icol+1];
            output[irow][icol] = sqrt(pow(a-b,2.0) + pow(c-dd,2.0))
                                 / (8.0 * cell->getLength());                    //150919RLN
        } else {
            output[irow][icol] = 0;
        }
    }
}
//______________________________________________________________________________
double BasinClass::getAvgUpperHydroSlop(int Cell_Index,int layer)
{
    //M.Liu assume the outlet is the average hydroslop with its upper stream
    double avgslop(0.0);
    int uppercells(0);
    for (int d = 0;d < 8; d++) {
        long neighbor_index = basin_cells[Cell_Index]->getNeighborIndex(d);
        if (neighbor_index > 0) {
            avgslop += Hydro_Standard_Slope[neighbor_index][layer];
            uppercells++;
        }
    }
    if (uppercells > 0) avgslop /= uppercells;
    else nrerror("Upstream cells of outlet cannot be zero!");
    return avgslop;
}
// ______________________________________________________________________________
double BasinClass::getGridSoilWater_m(const int innerid)
{
    double total(0.0);
    int layers = basin_cells[innerid]->getSoilLayers();
    for (int layer = 1; layer <= layers; layer++)
        total += Theta[innerid][layer] * L_thickness[innerid][layer];
    return total;
}
//______________________________________________________________________________
double BasinClass::getGridSoilNitrate_kg_m2(const int innerid)
{
    double total(0.0);
    int layers = basin_cells[innerid]->getSoilLayers();
    for (int layer = 1; layer <= layers; layer++)
        total += SoluteAmount[innerid][layer][SL_Nitrate];
    return total;
}
//______________________________________________________________________________
double BasinClass::getGridSoilAmonia_kg_m2(int innerid)
{
    double total(0.0);
    int layers = basin_cells[innerid]->getSoilLayers();
    for (int layer = 1; layer <= layers;layer++)
        total += SoluteAmount[innerid][layer][SL_Ammonia];
    return total;
}
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
// This is temporarily disabled in CropSyst version
void BasinClass::PrintTextAllOutputForAllGrids()
{
    if (ControlRef.bWrite_Annual_Output) {
        PrintTextAnnualOutputForAllGrids();
        #ifdef LIU_DEBUG
        std::clog<<"PrintTextAnnualOutputForAllGrids done."<<std::endl;
        #endif
    }
    if (ControlRef.bWrite_Daily_Output) {
        PrintTextDailyOutputForAllGrids();
        if (ControlRef.bOutput_Format_Esri_Grid) {
            PrintEsriGridDailyOutput();
        }
        #ifdef LIU_DEBUG
        std::clog<<"PrintTextDailyOutputForAllGrids done."<<std::endl;
        #endif
    }
    if (ControlRef.bWrite_Growth_Daily_Output) {
        PrintTextGrowthDailyOutputForAllGrids();
        #ifdef LIU_DEBUG
        std::clog<<"PrintTextGrowthDailyOutputForAllGrids done."<<std::endl;
        #endif
    }
    if (ControlRef.bWrite_Growth_Season_Output) {
        PrintTextGrowthSeasonOutputForAllGrids();
        if (ControlRef.bOutput_Format_Esri_Grid) {
            PrintEsriGridGrowthSeasonOutput();
        }
        #ifdef LIU_DEBUG
        std::clog<<"PrintTextGrowthSeasonOutputForAllGrids done."<<std::endl;
        #endif
    }
    if (ControlRef.bWrite_Hourly_Output) {
        PrintTextHourlyOutputForAllGrids();
        if (ControlRef.bOutput_Format_Esri_Grid) {
            PrintEsriGridHourlyOutput();
        }
        #ifdef LIU_DEBUG
        std::clog<<"PrintTextHourlyOutputForAllGrids done."<<std::endl;
        #endif
    }
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
// This is temporarily disabled in CropSyst version
void BasinClass::PrintTextAnnualOutputForAllGrids()
{
    std::ofstream of_file(ControlRef.annual_output_filename.c_str(),std::ios::out);//150709RLN
    const CORN::OS::File_name_concrete &outfilename = ControlRef.annual_output_filename;
    if (of_file.fail()) {
        char errormessage[200];
        sprintf(errormessage,"Cannot create output file: %s",outfilename.c_str());
        nrerror(errormessage);
    }
    else {
        int soil_layers = basin_cells[0]->pSoilProfile->NumberOfLayers();        //Assume all gridcell has same layers
        of_file<<"Cell_ID,"
               <<"xcol_from_upleft,"                                             //160415LML
               <<"yrow_from_upleft,"                                             //160415LML
               <<"Current_Year,"
               <<"Nitrate_N_Fertilization,"
               <<"Ammonium_N_Fertilization,"
               <<"Organic_N_Fertilization,"
               //<<"Nitrate_N_Fertigation,"
               //<<"Ammonium_N_Fertigation,"
               <<"Nitrate_Leaching,"
               <<"Ammonium_Leaching,"
               //<<"Drainage,"
               <<"Precipitation_mm,"
               <<"Potential_ET_mm,"
               <<"Actual_ET_mm,"
               <<"Soil_Residue_Evap_mm,"
               <<"Transpiration_mm,"
               <<"Irrigation_mm,"
               <<"Drainage_mm,"
               //<<"Water_Balance,"
               //<<"Nitrate_Balance,"
               //<<"Ammonium_Balance,"
               //<<"Organic_Matter_Carbon_Balance,"
               //<<"Organic_Matter_Nitrogen_Balance,"
               //<<"Residue_Carbon_Balance,"
               //<<"Residue_Nitrogen_Balance,"
               <<"Profile_SOM_Carbon_Mass,"
               <<"Profile_SOM_NitrogenMass,"
               <<"Profile_NO3_Nitrogen_Mass,"
               <<"Profile_NH4_Nitrogen_Mass,"
               //<<"Top5cm_SOM_Carbon_Mass,"
               //<<"Top30cm_Soil_Carbon_Mass,"
               <<"Total_Aboveground_Residue_Carbon_Mass,"
               <<"Total_Aboveground_Residue_Nitrogen_Mass,"
               <<"Profile_Residue_Carbon_Mass,"
               <<"Profile_Residue_Nitrogen_Mass,"
               //<<"OM_Mineralization,"
               //<<"Residue_Mineralization,"
               //<<"N_Mineralized,"
               //<<"N_Immobilization,"
               <<"Nitrification,"
               //<<"Denitrification,"
               <<"N2O_Loss_denitrification,"
               <<"N2O_Loss_nitrification,"
               <<"N2O_Loss,"
               //<<"Ammonia_N_Mass_Volatilization,"
               //<<"Standing_Stubble_Carbon_Mass,"
               //<<"Surface_Residue_Carbon_Mass,"
               //<<"Soil_Residue_Carbon_Mass,"
               //<<"Cumulative_Decomposed_Standing_Stubble_Carbon_Mass,"
               //<<"Cumulative_Decomposed_Surface_Residue_Carbon_Mass,"
               //<<"Cumulative_Decomposed_Soil_Residue_Carbon_Mass,"
               <<"SOM_Carbon_Lost_As_CO2,"
               <<"Residue_Carbon_Lost_As_CO2,"
               <<"Surface_Runon_m3,"
               <<"Lateral_Runon_m3,"
               <<"Total_Runon_m3,"
               <<"Surface_Runon_NO3_kgN_ha,"
               <<"Surface_Runon_NH4_kgN_ha,"
               <<"Lateral_Runon_NO3_kgN_ha,"
               <<"Lateral_Runon_NH4_kgN_ha,"
               <<"Total_Runon_NO3_kgN_ha,"
               <<"Total_Runon_NH4_kgN_ha,"
               <<"Surface_Runoff_m3,"
               <<"Lateral_Runoff_m3,"
               <<"Total_Runoff_m3,"
               <<"Surface_Runoff_NO3_kgN_ha,"
               <<"Surface_Runoff_NH4_kgN_ha,"
               <<"Lateral_Runoff_NO3_kgN_ha,"
               <<"Lateral_Runoff_NH4_kgN_ha,"
               <<"Total_Runoff_NO3_kgN_ha,"
               <<"Total_Runoff_NH4_kgN_ha,"
               <<"Drainage_m3,"
               //170414LML <<"Drainage_NO3_kgN,"
               //170414LML <<"Darinage_NH4_kgN,"
               <<"Initial_Profile_inorganic_N,"                                  //170413LML
               <<"N_Mineralized,"
               <<"N_Fertilized,"
               <<"N_runon,"
               <<"Final_Profile_inorganic_N,"                                    //170413LML
               <<"N_uptake,"
               <<"Denitrification,"
               <<"N_Immobilization,"
               <<"Ammonia_N_Mass_Volatilization,"
               <<"N2O_N_Loss_nitrification,"
               <<"N_runoff,"
               <<"N_leaching,"
               <<"Nin,"                                                          //170413LML
               <<"Nout,"                                                         //170413LML
               <<"Annual_N_Balance,";                                            //170413LML
        for (int layer = 1; layer <= soil_layers; layer++)
            of_file<<"L"<<layer<<"_LiqW,";
        for (int layer = 1; layer <= soil_layers; layer++)
            of_file<<"L"<<layer<<"_ICE,";
        for (int layer = 1; layer <= soil_layers; layer++)
            of_file<<"L"<<layer<<"_NO3_N_kg_ha,";
        for (int layer = 1; layer <= soil_layers; layer++)
            of_file<<"L"<<layer<<"_NH4_N_kg_ha,";
        of_file<<std::endl;
        for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
            OutputMainClass *pOutput =
                    #ifdef CROPSYST_VERSION
                    cell->
                    #else
                    cell->pSimulation->
                    #endif
                      pOutput;
            for (int timeseq = 0; 
                 timeseq < pOutput->pAnnual.size();
                 timeseq++) {
                OutputAnnualClass *pAnnual_out = &(pOutput->pAnnual[timeseq]);
                double init_N = pAnnual_out->Initial_Profile_NH4_N
                                + pAnnual_out->Initial_Profile_NO3_N
                                + pAnnual_out->Initial_Surface_NH4_N
                                + pAnnual_out->Initial_Surface_NO3_N;
                double final_N = pAnnual_out->Profile_NH4_Nitrogen_Mass
                                 + pAnnual_out->Profile_NO3_Nitrogen_Mass
                                 + pAnnual_out->Surface_NH4_N_Mass
                                 + pAnnual_out->Surface_NO3_N_Mass;
                double total_N_runon = pAnnual_out->Lateral_Runon_NH4_kgN_ha
                                        + pAnnual_out->Lateral_Runon_NO3_kgN_ha
                                        + pAnnual_out->Surface_Runon_NH4_kgN_ha
                                        + pAnnual_out->Surface_Runon_NO3_kgN_ha;
                double total_N_runoff = pAnnual_out->Lateral_Runoff_NH4_kgN_ha
                                        + pAnnual_out->Lateral_Runoff_NO3_kgN_ha
                                        + pAnnual_out->Surface_Runoff_NH4_kgN_ha
                                        + pAnnual_out->Surface_Runoff_NO3_kgN_ha;
                double total_Nin = init_N
                                    + pAnnual_out->Nitrate_N_Fertilization
                                    + pAnnual_out->Ammonium_N_Fertilization
                                    + pAnnual_out->N_Mineralization
                                    + total_N_runon;
                double total_Nout= final_N
                                    + pAnnual_out->Nuptake
                                    //+ per_m2_to_per_ha(cell->pSoilState->Annual_N_uptake)
                                    + pAnnual_out->Ammonia_N_Mass_Volatilization
                                    + pAnnual_out->Denitrification
                                    + pAnnual_out->N_Immobilization
                                    + pAnnual_out->N2O_Loss_nitrification
                                    + total_N_runoff
                                    + pAnnual_out->Nitrate_N_Leaching
                                    + pAnnual_out->Ammonium_N_Leaching;
                of_file<<cell->getCellId()<<","
                   <<cell->getCol()<<","                                         //160415LML
                   <<cell->getRow()<<","                                         //160415LML
                   <<pAnnual_out->Current_Year<<","
                   <<pAnnual_out->Nitrate_N_Fertilization<<","
                   <<pAnnual_out->Ammonium_N_Fertilization<<","
                   <<pAnnual_out->Organic_N_Fertilization<<","
                   <<pAnnual_out->Nitrate_N_Leaching<<","
                   <<pAnnual_out->Ammonium_N_Leaching<<","
                   //<<pAnnual_out->Drainage<<","
                   <<m_to_mm(pAnnual_out->Precipitation)<<","
                   <<m_to_mm(pAnnual_out->Potential_ET)<<","
                   <<m_to_mm(pAnnual_out->Actual_ET)<<","
                   <<m_to_mm(pAnnual_out->Soil_Residue_Evap)<<","
                   <<m_to_mm(pAnnual_out->Transpiration)<<","
                   <<m_to_mm(pAnnual_out->Irrigation)<<","
                   <<m_to_mm(pAnnual_out->Drainage)<<","
                   //<<pAnnual_out->Water_Balance<<","
                   //<<pAnnual_out->Nitrate_Balance<<","
                   //<<pAnnual_out->Ammonium_Balance<<","
                   //<<pAnnual_out->Organic_Matter_Carbon_Balance<<","
                   //<<pAnnual_out->Organic_Matter_Nitrogen_Balance<<","
                   //<<pAnnual_out->Residue_Carbon_Balance<<","
                   //<<pAnnual_out->Residue_Nitrogen_Balance<<","
                   <<pAnnual_out->Profile_SOM_Carbon_Mass<<","
                   <<pAnnual_out->Profile_SOM_Nitrogen_Mass<<","
                   <<pAnnual_out->Profile_NO3_Nitrogen_Mass<<","
                   <<pAnnual_out->Profile_NH4_Nitrogen_Mass<<","
                   //150521 <<pAnnual_out->Top5cm_SOM_Carbon_Mass<<","
                   //150521 <<pAnnual_out->Top30cm_Soil_Carbon_Mass<<","
                   <<pAnnual_out->Last_Day_Of_Year_Total_Aboveground_Residue_Carbon_Mass<<","
                   <<pAnnual_out->Last_Day_Of_Year_Total_Aboveground_Residue_Nitrogen_Mass<<","
                   <<pAnnual_out->Profile_Residue_Carbon_Mass<<","
                   <<pAnnual_out->Profile_Residue_Nitrogen_Mass<<","
                   //<<pAnnual_out->OM_Mineralization<<","
                   //<<pAnnual_out->Residue_Mineralization<<","
                   //<<pAnnual_out->N_Mineralization<<","
                   //<<pAnnual_out->N_Immobilization<<","
                   <<pAnnual_out->Nitrification<<","
                   //<<pAnnual_out->Denitrification<<","
                   <<pAnnual_out->N2O_Loss_denitrification<<","
                   <<pAnnual_out->N2O_Loss_nitrification<<","
                   <<pAnnual_out->N2O_Loss<<","
                   //<<pAnnual_out->Ammonia_N_Mass_Volatilization<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Standing_Stubble_Carbon_Mass<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Surface_Residue_Carbon_Mass<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Total_Aboveground_Residue_Carbon_Mass<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Soil_Residue_Carbon_Mass<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Cumulative_Decomposed_Standing_Stubble_Carbon_Mass<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Cumulative_Decomposed_Surface_Residue_Carbon_Mass<<","
                   //<<pAnnual_out->Last_Day_Of_Year_Cumulative_Decomposed_Soil_Residue_Carbon_Mass<<","
                   <<pAnnual_out->SOM_Carbon_Lost_As_CO2<<","
                   <<pAnnual_out->Residue_Carbon_Lost_As_CO2<<","
                   <<pAnnual_out->Surface_Runon_m3<<","
                   <<pAnnual_out->Lateral_Runon_m3<<","
                   <<pAnnual_out->Total_Runon_m3<<","
                   <<pAnnual_out->Surface_Runon_NO3_kgN_ha<<","
                   <<pAnnual_out->Surface_Runon_NH4_kgN_ha<<","
                   <<pAnnual_out->Lateral_Runon_NO3_kgN_ha<<","
                   <<pAnnual_out->Lateral_Runon_NH4_kgN_ha<<","
                   <<pAnnual_out->Total_Runon_NO3_kgN_ha<<","
                   <<pAnnual_out->Total_Runon_NH4_kgN_ha<<","
                   <<pAnnual_out->Surface_Runoff_m3<<","
                   <<pAnnual_out->Lateral_Runoff_m3<<","
                   <<pAnnual_out->Total_Runoff_m3<<","
                   <<pAnnual_out->Surface_Runoff_NO3_kgN_ha<<","
                   <<pAnnual_out->Surface_Runoff_NH4_kgN_ha<<","
                   <<pAnnual_out->Lateral_Runoff_NO3_kgN_ha<<","
                   <<pAnnual_out->Lateral_Runoff_NH4_kgN_ha<<","
                   <<pAnnual_out->Total_Runoff_NO3_kgN_ha<<","
                   <<pAnnual_out->Total_Runoff_NH4_kgN_ha<<","
                   <<pAnnual_out->Drainage_m3<<","
                   //170414LML <<pAnnual_out->Drainage_NO3_kgN<<","
                   //170414LML <<pAnnual_out->Darinage_NH4_kgN<<","
                   <<init_N<<","                                                 //170413LML
                   <<pAnnual_out->N_Mineralization<<","
                   <<(pAnnual_out->Nitrate_N_Fertilization + pAnnual_out->Ammonium_N_Fertilization)<<","
                   <<total_N_runon<<","
                   <<final_N<<","                                                //170413LML
                   <<pAnnual_out->Nuptake<<","                                   //per_m2_to_per_ha(cell->pSoilState->Annual_N_uptake)         //per_m2_to_per_ha(cell->ANNL_accumulators_active->N_uptake)<<","
                   <<pAnnual_out->Denitrification<<","
                   <<pAnnual_out->N_Immobilization<<","
                   <<pAnnual_out->Ammonia_N_Mass_Volatilization<<","
                   <<pAnnual_out->N2O_Loss_nitrification<<","
                   <<total_N_runoff<<","
                   //170413LML <<(pAnnual_out->Darinage_NH4_kgN + pAnnual_out->Drainage_NO3_kgN)<<","
                   <<(pAnnual_out->Nitrate_N_Leaching + pAnnual_out->Ammonium_N_Leaching) <<","
                   <<total_Nin<<","                                              //170413LML
                   <<total_Nout<<","                                             //170413LML
                   <<(total_Nin - total_Nout)<<",";                              //170413LML
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pAnnual_out->Last_Day_Of_Year_Layer_Water_Content[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pAnnual_out->Last_Day_Of_Year_Layer_Ice_Content[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pAnnual_out->Last_Day_Of_Year_Layer_Nitrate_N_Mass[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pAnnual_out->Last_Day_Of_Year_Layer_Ammonium_N_Mass[layer]<<",";
                of_file<<std::endl;
            }
            pOutput->pAnnual.clear();
        }
    }
    of_file.close();
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
// This is temporarily disabled in CropSyst version
void BasinClass::PrintTextDailyOutputForAllGrids()
{
    std::ofstream of_file                                                        //150709RLN
       (ControlRef.daily_output_filename.c_str()
       ,Daily_Head_Printed?std::ios::app : std::ios::out);
    const CORN::OS::File_name_concrete & outfilename = ControlRef.daily_output_filename;
    if (of_file.fail())
    {   char errormessage[200];
        sprintf(errormessage,"Cannot create output file: %s",outfilename.c_str());
        nrerror(errormessage);
    }
    else {
        int soil_layers = basin_cells[0]->pSoilProfile->NumberOfLayers();   //Assume all gridcell has same layers
        of_file.seekp(0,std::ios_base::end);
        if (!Daily_Head_Printed) {
            of_file<<"Cell_ID,"
               <<"xcol_from_upleft,"                                             //160415LML
               <<"yrow_from_upleft,"                                             //160415LML
               //160415LML <<"Current_Year,"
               //160415LML <<"Current_Month,"
               //160415LML <<"Current_DOM,"
               //160415LML <<"Current_DOY,"
               <<"Current_Date,"                                                 //160415LML
               <<"Crop_Name,"
               <<"Phenology,"
               <<"Total_LAI,"
               //150522 <<"Management_Name,"
               <<"Soil_Evap_mm,"
               <<"Pond_Evap_mm,"
               <<"Residue_Evap_mm,"
               <<"Snow_Subl_mm_h2o,"
               <<"Total_Evap_mm,"
               <<"Plant_Transpiration_mm,"
               <<"Canopy_Intercepted_mm,"
               <<"Total_act_ET_mm,"
               <<"PET_mm,"
               <<"Runoff_Excess_Infiltration_mm,"
               <<"Sf_Runoff_mm,"                                                 //Surface
               <<"Sf_Runon_mm,"
               <<"Lt_Runoff_mm,"                                                 //Lateral flow
               <<"Lt_Runon_mm,"
               <<"Lt_Up_mm,"
               <<"Sf_In_NH4_kg,"
               <<"Sf_Out_NH4_kg,"
               <<"Sf_In_NO3_kg,"
               <<"Sf_Out_NO3_kg,"
               <<"Lt_In_NH4_kg,"
               <<"Lt_Out_NH4_kg,"
               <<"Lt_In_NO3_kg,"
               <<"Lt_Out_NO3_kg,"
               <<"NO3_N_Fert_kg_ha,"
               <<"NH4_N_Fert_kg_ha,"
               <<"org_N_Fert_kg_ha,"
               <<"NO3_Leaching_kg_ha,"
               <<"NH4_Leaching_kg_ha,"
               <<"Drainage_m,"
               <<"f_Cover_Snow,"
               <<"Snow_Depth_m_snow,"
               <<"Snow_Melt_Amount_mm_h2o,"
               //<<"Tot_Snow_Amount_m_h2o,"
               <<"Avg_Snow_Surface_T,"
               //<<"Avg_Snow_Below_Surface_T,"
               <<"Precipitation_m,"
               <<"Mean_Temperature,"
               <<"Pond_m,"
               <<"Total_SWE_mm,"
               <<"Peak_SWE_mm,"
               <<"Total_LiqW_mm,"
               <<"Total_Ice_mm,"
               <<"AG_Residue_kgC_per_ha,"
               <<"BG_Residue_kgC_per_ha,"
               <<"SOM_kgC_per_ha,"
               <<"AG_Residue_kgN_per_ha,"
               <<"BG_Residue_kgN_per_ha,"
               <<"SOM_kgN_per_ha,"
               <<"NO3_kgN_per_ha,"
               <<"NH4_kgN_per_ha,"
               <<"Profile_Mineral_N_Mass_kgN_per_ha,"
               <<"Top_One_Meter_Mineral_N_Mass_kgN_per_ha,"
               <<"SOM_Resp_gC_per_m2,"
               <<"Residue_Resp_gC_per_m2,"
               //<<"Maintenance_Resp_gGlucode_per_m2,"
               //<<"Biosynthesi_Efficiency_gDM_per_gGlucose,"
               //<<"Gross_Canopy_Photosyn_gC_per_m2,"
               //<<"Plant_Resp_gC_per_m2,"
               <<"Root_Biomass_kgDM_per_m2,"
               <<"Canopy_Biomass_kgDM_per_m2,"
               <<"Cumulative_Thermal_Time,"
               //<<"Potential_Cumulative_Biomass_kg_per_ha,"
               //<<"Actual_Cumulative_Biomass_kg_per_ha,"
               //<<"Actual_Cumulative_Root_Biomass_kg_per_ha,"
               <<"Fraction_Solar_Rad_Intercepted_Green_Canopy,"
               <<"Intercepted_Solar_Rad_MJ_m2,"
               <<"Green_Area_Index,"
               <<"Crop_Potential_Transpiration_mm,"
               <<"Actual_Nitrogen_Uptake_kg_per_ha,"
               <<"Water_Stress_Index,"
               <<"Nitrogen_Stress_Index,"
               <<"Temperature_Stress_Index,"
               <<"Temperature_Stress_Index_Mean,"
               <<"Temperature_Stress_Current,"
               <<"Root_Depth,"
               <<"yield_ton_per_ha,"
               <<"nitrification_kgN_per_ha,"
               <<"denitrification_kgN_per_ha,"
               <<"mineralization_kgN_per_ha,"
               <<"volatilization_kgN_per_ha,"
               <<"N_N2O_loss_kgN_per_ha,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_LiqW,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_ICE,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_NO3_N_kg_ha,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_NH4_N_kg_ha,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_Temp,";
            of_file<<std::endl;
            Daily_Head_Printed = true;
        }
        //151006LML #ifndef CROPSYST_VERSION
        for (long i = 0; i < num_cells; i++) {
            BasinCellClass *cell = basin_cells[i];
            OutputMainClass *pOutput =
                #ifdef CROPSYST_VERSION
                cell->pOutput;
                #else
                cell->pSimulation->pOutput;
                #endif
            for (int timeseq = 0; timeseq < pOutput->pDaily_Soil.size(); timeseq++) {
                OutputDailySoilClass *pDaily_Soil_out = 
                    &pOutput->pDaily_Soil[timeseq];
                //pDaily_Soil_out->Current_Date.format.set_ordering_styles_separator();



                //assert(false);
                //set day format





                double total_evap_mm = m_to_mm(pDaily_Soil_out->soil_evaporation
                                          + pDaily_Soil_out->pond_evaporation
                                          + pDaily_Soil_out->residue_evaporation
                                          + pDaily_Soil_out->Snow_Evaporation);
                double total_et_mm = total_evap_mm + m_to_mm(pDaily_Soil_out->Plant_Transpiration);
                of_file<<cell->getCellId()<<","
                      <<cell->getCol()<<","                                      //160415LML
                      <<cell->getRow()<<","                                      //160415LML
                      //160415LML <<pDaily_Soil_out->Current_Year<<","
                      //160415LML <<pDaily_Soil_out->Current_Month<<","
                      //160415LML <<pDaily_Soil_out->Current_DOM<<","
                      //160415LML <<pDaily_Soil_out->Current_DOY<<","
                      <<pDaily_Soil_out->Current_Date.as_string()<<","
                      <<pDaily_Soil_out->Crop_Name<<","
                      <<pDaily_Soil_out->Development_Stage<<","
                      <<pDaily_Soil_out->Leaf_Area_Index<<","
                      //160616LML <<m_to_mm(pDaily_Soil_out->Soil_Water_Actual_Evaporation)<<","
                      <<m_to_mm(pDaily_Soil_out->soil_evaporation)<<","
                      <<m_to_mm(pDaily_Soil_out->pond_evaporation)<<","
                      <<m_to_mm(pDaily_Soil_out->residue_evaporation)<<","
                      <<m_to_mm(pDaily_Soil_out->Snow_Evaporation)<<","
                      <<total_evap_mm<<","
                      <<m_to_mm(pDaily_Soil_out->Plant_Transpiration)<<","
                      <<m_to_mm(pDaily_Soil_out->Canopy_Interception)<<","
                      <<total_et_mm<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_PET_MB)<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_Runoff_Excess_Infiltration)<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_Surface_Runoff)<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_Surface_Runon)<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_Lateral_Runoff)<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_Lateral_Runon)<<","
                      <<m_to_mm(pDaily_Soil_out->Daily_Lateral_Up)<<","
                      <<pDaily_Soil_out->dailySurfaceInFlowSolute_kg[SL_Ammonia]<<","
                      <<pDaily_Soil_out->dailySurfaceOutFlowSolute_kg[SL_Ammonia]<<","
                      <<pDaily_Soil_out->dailySurfaceInFlowSolute_kg[SL_Nitrate]<<","
                      <<pDaily_Soil_out->dailySurfaceOutFlowSolute_kg[SL_Nitrate]<<","
                      <<pDaily_Soil_out->dailyLateralInFlowSolute_kg[SL_Ammonia]<<","
                      <<pDaily_Soil_out->dailyLateralOutFlowSolute_kg[SL_Ammonia]<<","
                      <<pDaily_Soil_out->dailyLateralInFlowSolute_kg[SL_Nitrate]<<","
                      <<pDaily_Soil_out->dailyLateralOutFlowSolute_kg[SL_Nitrate]<<","
                      <<pDaily_Soil_out->NO3_N_Fertilization<<","
                      <<pDaily_Soil_out->NH4_N_Fertilization<<","
                      <<pDaily_Soil_out->org_N_Fertilization<<","
                      <<pDaily_Soil_out->Nitrate_Leaching<<","
                      <<pDaily_Soil_out->Ammonium_Leaching<<","
                      <<pDaily_Soil_out->Drainage<<","
                      <<pDaily_Soil_out->Fraction_Cover_Snow<<","
                      <<pDaily_Soil_out->Daily_Snow_Depth<<","
                      <<m_to_mm(pDaily_Soil_out->Snow_Melt_Amount)<<","
                      //<<pDaily_Soil_out->Total_Snow_Amount<<","
                      <<pDaily_Soil_out->Avg_Snow_Surface_T<<","
                      //<<pDaily_Soil_out->Avg_Snow_Below_Surface_T<<","
                      <<pDaily_Soil_out->Precipitation_m<<","
                      <<pDaily_Soil_out->Mean_Temperature<<","
                      <<pDaily_Soil_out->Pond_m<<","
                      <<m_to_mm(pDaily_Soil_out->Total_SWE)<<","
                      <<m_to_mm(pDaily_Soil_out->Peak_SWE)<<","
                      <<m_to_mm(pDaily_Soil_out->Total_LiqW_m)<<","
                      <<m_to_mm(pDaily_Soil_out->Total_Ice_m)<<","
                      <<pDaily_Soil_out->AG_Residue_C_Mass<<","
                      <<pDaily_Soil_out->BG_Residue_C_Mass<<","
                      <<pDaily_Soil_out->SOM_C_Mass<<","
                      <<pDaily_Soil_out->AG_Residue_N_Mass<<","
                      <<pDaily_Soil_out->BG_Residue_N_Mass<<","
                      <<pDaily_Soil_out->SOM_N_Mass<<","
                      <<pDaily_Soil_out->NO3_N_Mass<<","
                      <<pDaily_Soil_out->NH4_N_Mass<<","
                      <<pDaily_Soil_out->Profile_Mineral_N_Mass<<","
                      <<pDaily_Soil_out->Top_One_Meter_Mineral_N_Mass<<","
                      <<pDaily_Soil_out->Profile_SOM_Carbon_Lost_As_CO2<<","
                      <<pDaily_Soil_out->Profile_Residue_Carbon_Lost_As_CO2<<","
                      //<<pDaily_Soil_out->Maintenance_Respiration<<","
                      //<<pDaily_Soil_out->Biosynthesis_Efficiency<<","
                      //<<pDaily_Soil_out->Gross_Canopy_Photosynthesis<<","
                      //<<pDaily_Soil_out->CO2_by_Plant_Respiration<<","
                      <<pDaily_Soil_out->Biomass_Root_Today<<","
                      <<pDaily_Soil_out->Biomass_Top_Today<<","
                      <<pDaily_Soil_out->Cumulative_Thermal_Time<<","
                      //<<tonne_to_kg(pDaily_Soil_out->Potential_Cumulative_Biomass)<<","
                      //<<tonne_to_kg(pDaily_Soil_out->Actual_Cumulative_Biomass)<<","
                      //<<tonne_to_kg(pDaily_Soil_out->Actual_Cumulative_Root_Biomass)<<","
                      <<pDaily_Soil_out->Fraction_Solar_Rad_Intercepted_Green_Canopy<<","
                      <<pDaily_Soil_out->Intercepted_Solar_Rad_MJ_m2<<","
                      <<pDaily_Soil_out->Green_Area_Index<<","
                      <<m_to_mm(pDaily_Soil_out->Crop_Potential_Transpiration)<<","
                      <<pDaily_Soil_out->Actual_Nitrogen_Uptake<<","
                      <<pDaily_Soil_out->Water_Stress_Index<<","
                      <<pDaily_Soil_out->Temperature_Stress_Index<<","
                      <<pDaily_Soil_out->Temperature_Stress_Index_Mean<<","
                      <<pDaily_Soil_out->Temperature_Stress_Current<<","
                      <<pDaily_Soil_out->Nitrogen_Stress_Index<<","
                      <<pDaily_Soil_out->Root_Depth<<","
                      <<pDaily_Soil_out->yield<<","
                      <<pDaily_Soil_out->nitrification<<","
                      <<pDaily_Soil_out->denitrification<<","
                      <<pDaily_Soil_out->mineralization<<","
                      <<pDaily_Soil_out->volatilization<<","
                      <<pDaily_Soil_out->N_N2O_loss<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pDaily_Soil_out->Layer_Water_Content[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pDaily_Soil_out->Layer_Ice_Content[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pDaily_Soil_out->Layer_Nitrate_N_Mass[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pDaily_Soil_out->Layer_Ammonium_N_Mass[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pDaily_Soil_out->Layer_Avg_Daily_Soil_T[layer]<<",";
                of_file<<std::endl;
            }
            pOutput->pDaily_Soil.clear();
        }  //end cell
        //151006LML #endif
    }
    of_file.close();
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
// Simply use CropSyst outputs for crop model output
void BasinClass::PrintTextGrowthDailyOutputForAllGrids()
{
    std::ofstream of_file
       (ControlRef.growth_daily_output_filename.c_str()
       ,Daily_Growth_Head_Printed ? std::ios::app : std::ios::out);
     const CORN::OS::File_name_concrete &outfilename = ControlRef.growth_daily_output_filename;
    if (of_file.fail())
    {   char errormessage[200];
        sprintf(errormessage,"Cannot create output file: %s",outfilename.c_str());
        nrerror(errormessage);
    } else
    {   of_file.seekp(0,std::ios_base::end);
        if (!Daily_Growth_Head_Printed) {
        of_file<<"Cell_ID,"
               <<"Current_Year,"
               <<"CurrentDOY,"
               <<"Crop_Name,"
               <<"Days_After_Crop_Planting,"
               <<"Development_Stage,"
               <<"Cum_Thermal_Time,"
               <<"Pot_Cum_BM_t_ha,"
               <<"Act_Cum_BM_t_ha,"
               <<"F_Solar_Rad_Int_Green_Canopy,"
               <<"LAI,"
               <<"GAI,"
               <<"Pot_Crop_Pot_Transp_mm,"
               <<"Crop_Pot_Transp_mm,"
               <<"Act_Crop_Transp_mm,"
               <<"Act_N_Uptake_kg_ha,"
               <<"Water_Stress_Index,"
               <<"Top_N_Stress_Index,"
               <<"Root_N_Stress_Index,"
               <<"Root_Depth_m,"
               <<std::endl;
            Daily_Growth_Head_Printed = true;
        }
        for (long i = 0; i < num_cells; i++) {
			BasinCellClass *cell = basin_cells[i];
            OutputMainClass *pOutput =
                    #ifdef CROPSYST_VERSION
                    cell->
                    #else
                    cell->pSimulation->
                    #endif
                      pOutput;
            for (int timeseq = 0; 
                //timeseq < cell->pSimulation->pOutput->getGrowthDaySequence(); 
                timeseq < pOutput->pGrowth.size();
                timeseq++) {
                OutputGrowthClass *pGrowth_out = &pOutput->pGrowth[timeseq];
                of_file<<cell->getCellId()<<","
                      <<pGrowth_out->Current_Year<<","
                      <<pGrowth_out->Current_DOY<<","
                      <<pGrowth_out->Crop_Name<<","
                      <<pGrowth_out->Days_After_Crop_Planting<<","
                      <<pGrowth_out->Development_Stage<<","
                      <<pGrowth_out->Cumulative_Thermal_Time<<","
                      <<pGrowth_out->Potential_Cumulative_Biomass<<","
                      <<pGrowth_out->Actual_Cumulative_Biomass<<","
                      <<pGrowth_out->Fraction_Solar_Rad_Intercepted_Green_Canopy<<","
                      <<pGrowth_out->Leaf_Area_Index<<","
                      <<pGrowth_out->Green_Area_Index<<","
                      <<pGrowth_out->Potential_Crop_Potential_Transpiration<<","
                      <<pGrowth_out->Crop_Potential_Transpiration<<","
                      <<pGrowth_out->Actual_Crop_Transpiration<<","
                      <<pGrowth_out->Actual_Nitrogen_Uptake<<","
                      <<pGrowth_out->Water_Stress_Index<<","
                      <<pGrowth_out->Top_Nitrogen_Stress_Index<<","
                      <<pGrowth_out->Root_Nitrogen_Stress_Index<<","
                      <<pGrowth_out->Root_Depth<<","
                      <<std::endl;
            }
            pOutput->pGrowth.clear();
        } //end cell
    }
    of_file.close();
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
// Simply use CropSyst outputs for crop model output
void BasinClass::PrintTextGrowthSeasonOutputForAllGrids()
{
    std::ofstream of_file(ControlRef.growth_season_output_filename.c_str(),std::ios::out);
    const CORN::OS::File_name_concrete &outfilename = ControlRef.growth_season_output_filename;
    if (of_file.fail())
    {   char errormessage[200];
        sprintf(errormessage,"Cannot create output file: %s",outfilename.c_str());
        nrerror(errormessage);
    }
    else {
        int soil_layers = basin_cells[0]->pSoilProfile->NumberOfLayers();   //Assume all gridcell has same layers
        of_file<<"Cell_ID,"
               <<"xcol_from_upleft,"                                             //160415LML
               <<"yrow_from_upleft,"                                             //160415LML
               <<"Crop_Name,"
               //160415LML <<"Year_Planting,"
               //160415LML <<"DOY_Planting,"
               //160415LML <<"DOY_Emergence,"
               //160415LML <<"DOY_Flowering,"
               //160415LML <<"DOY_Begin_Yield_Formation,"
               //160415LML <<"DOY_Physiological_Maturity,"
               //160415LML <<"Year_Harvest,"
               //160415LML <<"DOY_Harvest,"
               <<"planting_date,"
               <<"emergence_date,"
               <<"flowering_date,"
               <<"begin_yield_formation_date,"
               <<"physiological_maturity_date,"
               <<"harvest_date,"
               //<<"Pot_Cum_BM_At_Mat_kg_ha,"
               <<"Cum_BM_At_Mat_kg_ha,"
               <<"Cum_Root_BM_At_Mat_kg_ha,"
               //<<"Pot_Crop_Yield_kg_ha,"
               <<"Crop_Yield_kg_ha,"
               <<"Water_Stress,"
               <<"Nitrogen_Stress,"
               <<"Precipitation_mm,"
               <<"Actual_Transpiration_mm,"
               <<"Actual_ET_mm,"
               //<<"N_uptake_kgN_ha,"
               <<"N_Fixation_kgN_ha,"
               //<<"N_Applied_kgN_ha,"
               //<<"N_Mineralized_kgN_ha,"
               //<<"N_Volatilized_kgN_ha,"
               //<<"N_Immobilized_kgN_ha,"
               <<"N_Nitrified_kg_ha,"
               //<<"N_Denitrified_kg_ha,"
               <<"N_N2O_loss_denitrification_kg_ha,"
               <<"N_N2O_loss_nitrification_kg_ha,"
               <<"N_N2O_loss_kg_ha,"
               //<<"N_Leached_kg_ha,"
               <<"NH4_N_on_planting_date_kg_ha,"
               <<"NO3_N_on_planting_date_kg_ha,"
               <<"inorg_N_on_planting_date_kg_ha,"
               <<"N_Mineralized_kgN_ha,"
               <<"N_Applied_kgN_ha,"
               <<"N_runon_kgN_ha,"
               <<"NH4_N_on_harvest_date_kg_ha,"
               <<"NO3_N_on_harvest_date_kg_ha,"
               <<"inorg_N_on_harvest_date_kg_ha,"
               <<"N_uptake_kgN_ha,"
               <<"N_Denitrified_kg_ha,"
               <<"N_Immobilized_kgN_ha,"
               <<"N_Volatilized_kgN_ha,"
               <<"N_N2O_loss_nitrification_kg_ha_duplicate_for_shown_only,"
               <<"N_runoff,"
               <<"N_Leached_kg_ha,"
               <<"Nin_kg_ha,"
               <<"Nout_kg_ha,"
               <<"Growthseason_N_Balance,"


               /*NYI LML 160115
               <<"Cum_Crop_Pot_Transp_At_Mat_m,"
               <<"Cum_Act_Crop_Transp_At_Maturity_m,"
               <<"Cum_N_Uptake_At_Mat_kg_ha,"
               <<"Top_N_At_Mat_kg_ha,"
               <<"Root_N_At_Mat_kg_ha,"
               <<"Top_N_At_Emergence_kg_ha,"
               <<"Root_N_At_Emergence_kg_ha,"
               <<"Crop_N_Balance_At_Mat_kg_ha,"
               <<"Soil_Nitrate_N_At_Planting_kg_ha,"
               <<"Soil_Nitrate_N_At_Mat_kg_ha,"
               <<"Soil_Ammonium_N_At_Planting_kg_ha,"
               <<"Soil_Ammonium_N_At_Mat_kg_ha,"
               <<"N_Applied_kg_ha,"
               <<"N_Mineralized_kg_ha,"
               <<"N_Immobilized_kg_ha,"
               <<"N_Leached_kg_ha,"
               <<"N_Volatilized_kg_ha,"
               <<"N_Nitrification_kg_ha,"
               <<"N_Denitrified_kg_ha,"
               <<"Soil_Growing_Season_N_Bal_kg_ha,"
               <<"Crop_Avg_Water_Stress_Index,"
               <<"Crop_Avg_Top_N_Stress_Index,"
               <<"Crop_Avg_Root_N_Stress_Index,"
               <<"Overall_Crop_N_Bal_kg_ha,"
               */
               <<std::endl;
        for (long i = 0; i < num_cells; i++) {
			BasinCellClass *cell = basin_cells[i];
            OutputMainClass *pOutput =
                    #ifdef CROPSYST_VERSION
                    cell->
                    #else
                    cell->pSimulation->
                    #endif
                      pOutput;
            for (int timeseq = 0; 
                //timeseq < cell->pSimulation->pOutput->getGrowthSeasonSequence(); 
                timeseq < pOutput->pGrowth_Season.size();
                timeseq++) {
                OutputGrowthSeasonClass *pGrowth_Season_out = 
                    &(pOutput->pGrowth_Season[timeseq]);
                int growing_days = pGrowth_Season_out->harvest_date.days_between(/*(const Date_time &)*/pGrowth_Season_out->planting_date,true);
                double init_N = pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting
                                + pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting
                                + pGrowth_Season_out->Surface_Ammonium_N_Mass_At_Planting
                                + pGrowth_Season_out->Surface_Nitrate_N_Mass_At_Planting;
                double final_N = pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Harvest
                                 + pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Harvest
                                 + pGrowth_Season_out->Surface_Ammonium_N_Mass_At_Harvest
                                 + pGrowth_Season_out->Surface_Nitrate_N_Mass_At_Harvest;
                double total_Nin = init_N
                                    + pGrowth_Season_out->N_Applied
                                    + pGrowth_Season_out->N_Mineralized
                                    + pGrowth_Season_out->N_runon;
                double total_Nout= final_N
                                    + pGrowth_Season_out->N_Updake
                                    + pGrowth_Season_out->N_Volatilized
                                    + pGrowth_Season_out->N_Denitrified
                                    + pGrowth_Season_out->N_Immobilized
                                    + pGrowth_Season_out->N_N2O_loss_nitrification
                                    + pGrowth_Season_out->N_Leached
                                    + pGrowth_Season_out->N_runoff;


                of_file<<cell->getCellId()<<","
                      <<cell->getCol()<<","                                      //160415LML
                      <<cell->getRow()<<","                                      //160415LML
                      <<pGrowth_Season_out->Crop_Name<<","
                      //160415LML <<pGrowth_Season_out->Year_Planting<<","
                      //160415LML <<pGrowth_Season_out->DOY_Planting<<","
                      //160415LML <<pGrowth_Season_out->DOY_Emergence<<","
                      //160415LML <<pGrowth_Season_out->DOY_Flowering<<","
                      //160415LML <<pGrowth_Season_out->DOY_Begin_Yield_Formation<<","
                      //160415LML <<pGrowth_Season_out->DOY_Physiological_Maturity<<","
                      //160415LML <<pGrowth_Season_out->Year_Harvest<<","
                      //160415LML <<pGrowth_Season_out->DOY_Harvest<<","
                      <<pGrowth_Season_out->planting_date.as_string()<<","
                      <<pGrowth_Season_out->emergence_date.as_string()<<","
                      <<pGrowth_Season_out->flowering_date.as_string()<<","
                      <<pGrowth_Season_out->begin_yield_formation_date.as_string()<<","
                      <<pGrowth_Season_out->physiological_maturity_date.as_string()<<","
                      <<pGrowth_Season_out->harvest_date.as_string()<<","
                      //<<pGrowth_Season_out->Potential_Cumulative_Biomass_At_Maturity<<","
                      <<pGrowth_Season_out->Cumulative_Biomass_At_Maturity<<","
                      <<pGrowth_Season_out->Cumulative_Root_Biomass_At_Maturity<<","
                      //<<pGrowth_Season_out->Potential_Crop_Yield<<","
                      <<pGrowth_Season_out->Crop_Yield<<","
                      <<pGrowth_Season_out->Water_Stress_Index/(double)growing_days<<","
                      <<pGrowth_Season_out->Nitrogen_Stress_Index/(double)growing_days<<","
                      <<pGrowth_Season_out->Precipitation_mm<<","
                      <<pGrowth_Season_out->Actual_Transpiration_mm<<","
                      <<pGrowth_Season_out->Actual_ET_mm<<","
                      //<<pGrowth_Season_out->N_Updake<<","
                      <<pGrowth_Season_out->N_Fixation<<","
                      //<<pGrowth_Season_out->N_Applied<<","
                      //<<pGrowth_Season_out->N_Mineralized<<","
                      //<<pGrowth_Season_out->N_Volatilized<<","
                      //<<pGrowth_Season_out->N_Immobilized<<","
                      <<pGrowth_Season_out->N_Nitrfication<<","
                      //<<pGrowth_Season_out->N_Denitrified<<","
                      <<pGrowth_Season_out->N_N2O_loss_denitrification<<","
                      <<pGrowth_Season_out->N_N2O_loss_nitrification<<","
                      <<pGrowth_Season_out->N_N2O_loss<<","
                      //<<pGrowth_Season_out->N_Leached<<","
                      <<pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting <<","
                      <<pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting <<","
                      <<(pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting + pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting) << ","
                      <<pGrowth_Season_out->N_Mineralized<<","
                      <<pGrowth_Season_out->N_Applied<<","
                      <<pGrowth_Season_out->N_runon<<","
                      <<pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Harvest <<","
                      <<pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Harvest <<","
                      <<(pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Harvest + pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Harvest) << ","
                      <<pGrowth_Season_out->N_Updake<<","
                      <<pGrowth_Season_out->N_Denitrified<<","
                      <<pGrowth_Season_out->N_Immobilized<<","
                      <<pGrowth_Season_out->N_Volatilized<<","
                      <<pGrowth_Season_out->N_N2O_loss_nitrification<<","
                      <<pGrowth_Season_out->N_runoff<<","
                      <<pGrowth_Season_out->N_Leached<<","
                      <<total_Nin<<","
                      <<total_Nout<<","
                      <<(total_Nin - total_Nout) <<","



                      /*NYI LML 160115
                      <<pGrowth_Season_out->Cumulative_Crop_Potential_Transpiration_At_Maturity<<","
                      <<pGrowth_Season_out->Cumulative_Actual_Crop_Transpiration_At_Maturity<<","
                      <<pGrowth_Season_out->Cumulative_Nitrogen_Uptake_At_Maturity<<","
                      <<pGrowth_Season_out->Top_N_Mass_At_Maturity<<","
                      <<pGrowth_Season_out->Root_N_Mass_At_Maturity<<","
                      <<pGrowth_Season_out->Top_N_Mass_At_Emergence<<","
                      <<pGrowth_Season_out->Root_N_Mass_At_Emergence<<","
                      <<pGrowth_Season_out->Crop_N_Balance_At_Maturity<<","
                      <<pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Planting<<","
                      <<pGrowth_Season_out->Soil_Total_Nitrate_N_Mass_At_Maturity<<","
                      <<pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Planting<<","
                      <<pGrowth_Season_out->Soil_Total_Ammonium_N_Mass_At_Maturity<<","
                      <<pGrowth_Season_out->N_Applied<<","
                      <<pGrowth_Season_out->N_Mineralized<<","
                      <<pGrowth_Season_out->N_Immobilized<<","
                      <<pGrowth_Season_out->N_Leached<<","
                      <<pGrowth_Season_out->N_Volatilized<<","
                      <<pGrowth_Season_out->N_Denitrified<<","
                      <<pGrowth_Season_out->Soil_Growing_Season_N_Balance<<","
                      <<pGrowth_Season_out->Crop_Avg_Water_Stress_Index<<","
                      <<pGrowth_Season_out->Crop_Avg_Top_Nitrogen_Stress_Index<<","
                      <<pGrowth_Season_out->Crop_Avg_Root_Nitrogen_Stress_Index<<","
                      <<pGrowth_Season_out->Overall_Crop_Nitrogen_Balance<<","
                      */
                      <<std::endl;
            }
            pOutput->pGrowth_Season.clear();
        }
    }
    of_file.close();

}
#endif
//______________________________________________________________________________
//151002LML #ifndef CROPSYST_VERSION
#ifdef VB_SAME_CSV_OUTPUT
void BasinClass::PrintTextHourlyOutputForAllGrids()
{
    bool out_file_created = Hour_Head_Printed;
    const CORN::OS::File_name_concrete &outfilename = ControlRef.hourly_output_filename;
    std::ofstream of_file
       (ControlRef.hourly_output_filename.c_str()
       ,Hour_Head_Printed ? std::ios::app : std::ios::out);
    if (of_file.fail()) {
        char errormessage[200];
        sprintf(errormessage,"Cannot create output file: %s",outfilename.c_str());
        nrerror(errormessage);
    }
    else {
        of_file.seekp(0,std::ios_base::end);
        int soil_layers = basin_cells[0]->pSoilProfile->NumberOfLayers();   //Assume all gridcell has same layers
        if (!out_file_created) {
            of_file<<"Cell_ID,"
               <<"Cell_Type,"
               <<"Current_Year,"
               <<"Current_DOY,"
               <<"Current_Hour,"
               <<"Prec_Irrig_SnowMelt_m,"
               <<"Pond_m,"
               <<"Runoff_m,"
               <<"Drainage_m,"
               <<"Soil_Evap_m,"
               <<"T_air,"
               <<"PPT_m,"
               <<"Fraction_Cover_Snow,"
               <<"SWE_m,"
               <<"Snow_Melt_m,"
               <<"Sublimation_m,"
               <<"FD_Water_Balance,"
               <<"Sat_Boundary,"
               <<"hourlySurfaceInFlow_m3,"
               <<"hourlySurfaceOutFlow_m3,"
               <<"hourlyDrainage_m3,"
               <<"hourlyLateralInFlow_m3,"
               <<"hourlyLateralOutFlow_m3,"
               <<"hourlyLateralUpFlow_m3,"
               <<"hourlySurfaceInFlowNH4_kg,"
               <<"hourlySurfaceOutFlowNH4_kg,"
               <<"hourlySurfaceInFlowNO3_kg,"
               <<"hourlySurfaceOutFlowNO3_kg,"
               <<"hourlyLateralInFlowNH4_kg,"
               <<"hourlyLateralOutFlowNH4_kg,"
               <<"hourlyLateralInFlowNO3_kg,"
               <<"hourlyLateralOutFlowNO3_kg,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_LiqW,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_ICE,";                     //LML 140814
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_Temp,";                    //LML 140814
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_NO3_N_kg_m2,";
            for (int layer = 1; layer <= soil_layers; layer++)
                of_file<<"L"<<layer<<"_NH4_N_kg_m2";
            of_file<<std::endl;
            Hour_Head_Printed = true;
        }
        for (long i = 0; i < num_cells; i++) {
			BasinCellClass *cell = basin_cells[i];
            OutputMainClass *output =
              #ifdef CROPSYST_VERSION
              cell->pOutput;
              #else
              cell->pSimulation->pOutput;
              #endif
            for (int timeseq = 0; 
              timeseq < output->pHour.size();
              timeseq++) {
                OutputHourClass *pHour_out = &(output->pHour[timeseq]);
                int dayofyear = pHour_out->Current_DOY;
                int hour = pHour_out->Current_Hour;
                of_file<<cell->getCellId()<<","
                       <<cell->getGridType()<<","
                       <<pHour_out->Current_Year<<","
                       <<dayofyear<<","
                       <<hour<<","
                       <<pHour_out->Prec_Irrig_SnowMelt_m<<","
                       <<pHour_out->Ponded_Water<<","
                       <<pHour_out->Runoff<<","
                       <<pHour_out->Drainage<<","
                       <<pHour_out->Evaporation<<","
                       <<pHour_out->Temperature<<","
                       <<pHour_out->Precipitation<<","
                       <<pHour_out->Fraction_Cover_Snow<<","
                       <<pHour_out->Snow_Water_Equavalent<<","
                       <<pHour_out->Snow_Melt<<","
                       <<pHour_out->Sublimation<<","
                       <<pHour_out->FD_Water_Balance<<","
                       <<pHour_out->Sat_Boundary<<","
                       <<pHour_out->hourlySurfaceInFlow_m3<<","
                       <<pHour_out->hourlySurfaceOutFlow_m3<<","
                       <<pHour_out->hourlyDrainage_m3<<","
                       <<pHour_out->hourlyLateralInFlow_m3<<","
                       <<pHour_out->hourlyLateralOutFlow_m3<<","
                       <<pHour_out->hourlyLateralUpFlow_m3<<","
                       <<pHour_out->hourlySurfaceInFlowSolute_kg[SL_Ammonia]<<","
                       <<pHour_out->hourlySurfaceOutFlowSolute_kg[SL_Ammonia]<<","
                       <<pHour_out->hourlySurfaceInFlowSolute_kg[SL_Nitrate]<<","
                       <<pHour_out->hourlySurfaceOutFlowSolute_kg[SL_Nitrate]<<","
                       <<pHour_out->hourlyLateralInFlowSolute_kg[SL_Ammonia]<<","
                       <<pHour_out->hourlyLateralOutFlowSolute_kg[SL_Ammonia]<<","
                       <<pHour_out->hourlyLateralInFlowSolute_kg[SL_Nitrate]<<","
                       <<pHour_out->hourlyLateralOutFlowSolute_kg[SL_Nitrate]<<",";
                //for (int layer = 1; layer <= soil_layers; layer++)
                    //of_file<<pHour_out->Node_Depth[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pHour_out->Layer_Water_Content[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pHour_out->Layer_Ice_Content[layer]<<",";      //LML 140814
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pHour_out->Layer_Temperature[layer]<<",";      //LML 140814
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pHour_out->Layer_Nitrate_N_Mass[layer]<<",";
                //for (int layer = 1; layer <= soil_layers; layer++)
                    //of_file<<pHour_out->Layer_Nitrate_N_Conc[layer]<<",";
                for (int layer = 1; layer <= soil_layers; layer++)
                    of_file<<pHour_out->Layer_Ammonium_N_Mass[layer]<<",";
                of_file<<std::endl;
            }
            output->pHour.clear();
        }  //end cell
    }
    of_file.close();
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
// This is temporarily disabled in CropSyst version
void BasinClass::PrintEsriGridOutputVariable(int timeseq,std::string varname
                                      ,int soil_layer,std::string timestep)
{
    CORN::OS::Directory_name *outfile_path = 0;
    std::wstring outfile_name;
    std::wstring outfile_ext;
       // the path could be 0 if CWD, but usually will be subdirectory or fully qualified.
    EsriGridClass<double> fout;
    fout.CopyHeadInformation(gElev);
    fout.AllocateMem();
    fout.InitAllNovalue();
    OutputMainClass *pOutput =
            #ifdef CROPSYST_VERSION
            basin_cells[0]->
            #else
            basin_cells[0]->pSimulation->
            #endif
              pOutput;

    if (timestep.compare("Hourly") == 0) {
        int year = pOutput->pHour[timeseq].Current_Year;
        int doy = pOutput->pHour[timeseq].Current_DOY;
        int hour = pOutput->pHour[timeseq].Current_Hour;
        //150709RLN
        CORN::OS::Directory_name *outfile_path =  ControlRef.hourly_output_filename.get_path_directory_name();
        outfile_name = ControlRef.hourly_output_filename.get_name();
        outfile_ext  = ControlRef.hourly_output_filename.get_extension();
        CORN::ASCIIZ_to_wstring("_ESRI"   ,outfile_name);
        CORN::ASCIIZ_to_wstring("_Var_"   ,outfile_name); CORN::string_to_wstring(varname                ,outfile_name);
        if (soil_layer >= 0)
        {
        CORN::ASCIIZ_to_wstring("_Layer_" ,outfile_name); CORN::append_nat32_to_wstring((nat32)soil_layer,outfile_name);
        }
        CORN::ASCIIZ_to_wstring("_year_"  ,outfile_name); CORN::append_nat32_to_wstring((nat32)year      ,outfile_name);
        CORN::ASCIIZ_to_wstring("_doy_"   ,outfile_name); CORN::append_nat32_to_wstring((nat32)doy       ,outfile_name);
        CORN::ASCIIZ_to_wstring("_hour_"  ,outfile_name); CORN::append_nat32_to_wstring((nat32)hour      ,outfile_name);
    } else if (timestep.compare("Daily") == 0)
    {
        int year = pOutput->pDaily_Soil[timeseq].Current_Date.get_year();        //160415LML Current_Year;
        int doy = pOutput->pDaily_Soil[timeseq].Current_Date.get_DOY();          //160415LML .Current_DOY;
        CORN::OS::Directory_name *outfile_path = ControlRef.daily_output_filename.get_path_directory_name();
        outfile_name = ControlRef.daily_output_filename.get_name();
        outfile_ext = ControlRef.daily_output_filename.get_extension();
        CORN::ASCIIZ_to_wstring("_ESRI"   ,outfile_name);
        CORN::ASCIIZ_to_wstring("_Var_"   ,outfile_name); CORN::string_to_wstring(varname                ,outfile_name);
        if (soil_layer >= 0)
        {
        CORN::ASCIIZ_to_wstring("_Layer_" ,outfile_name); CORN::append_nat32_to_wstring((nat32)soil_layer,outfile_name);
        }
        CORN::ASCIIZ_to_wstring("_year_"  ,outfile_name); CORN::append_nat32_to_wstring((nat32)year      ,outfile_name);
        CORN::ASCIIZ_to_wstring("_doy_"   ,outfile_name); CORN::append_nat32_to_wstring((nat32)doy       ,outfile_name);
    } else if (timestep.compare("GrowthSeason") == 0)
    {
        int year = pOutput->pGrowth_Season[timeseq].planting_date.get_year();    //160415LML .Year_Planting;
        int doy = pOutput->pGrowth_Season[timeseq].planting_date.get_DOY();      //160415LML DOY_Planting;
        {
        CORN::OS::Directory_name *outfile_path = ControlRef.growth_season_output_filename.get_path_directory_name();
        outfile_name = ControlRef.growth_season_output_filename.get_name();
        outfile_ext = ControlRef.growth_season_output_filename.get_extension();
        CORN::ASCIIZ_to_wstring("_ESRI",outfile_name);
        CORN::ASCIIZ_to_wstring("_Var_",outfile_name);   CORN::string_to_wstring(varname,outfile_name);
        if (soil_layer >= 0)
           {  CORN::ASCIIZ_to_wstring("_Layer_" ,outfile_name); CORN::append_nat32_to_wstring((nat32)soil_layer,outfile_name); }
        CORN::ASCIIZ_to_wstring("_year_"     ,outfile_name); CORN::append_nat32_to_wstring((nat32)year      ,outfile_name);
        CORN::ASCIIZ_to_wstring("_doy_"      ,outfile_name); CORN::append_nat32_to_wstring((nat32)doy       ,outfile_name);
        }
    }
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        OutputMainClass *pOutput =
                #ifdef CROPSYST_VERSION
                cell->
                #else
                cell->pSimulation->
                #endif
                  pOutput;
        double outvalue(-9999.0);
        if (timestep.compare("Hourly") == 0) {
            OutputHourClass *pHour_out = &(pOutput->pHour[timeseq]);
            if (varname.compare("Layer_Water_Content") == 0) {
                outvalue = pHour_out->Layer_Water_Content[soil_layer];
            }
            else if (varname.compare("hourlySurfaceInFlow_m3") == 0) {
                outvalue = pHour_out->hourlySurfaceInFlow_m3;
            }
            else if (varname.compare("hourlySurfaceOutFlow_m3") == 0) {
                outvalue = pHour_out->hourlySurfaceOutFlow_m3;
            }
            else if (varname.compare("hourlyDrainage_m3") == 0) {
                outvalue = pHour_out->hourlyDrainage_m3;
            }
            else if (varname.compare("hourlyLateralInFlow_m3") == 0) {
                outvalue = pHour_out->hourlyLateralInFlow_m3;
            }
            else if (varname.compare("hourlyLateralOutFlow_m3") == 0) {
                outvalue = pHour_out->hourlyLateralOutFlow_m3;
            }
            else if (varname.compare("hourlyLateralUpFlow_m3") == 0) {
                outvalue = pHour_out->hourlyLateralUpFlow_m3;
            }
            else if (varname.compare("Ponded_Water") == 0) {
                outvalue = pHour_out->Ponded_Water;
            }
        } else if (timestep.compare("Daily") == 0) {
            OutputDailySoilClass *pDaily_Soil_out = &pOutput->pDaily_Soil[timeseq];
            if (pDaily_Soil_out)                                                 //150722RLN
            {
            if (varname.compare("Soil_Water_Actual_Evaporation") == 0) {
                outvalue = pDaily_Soil_out->Soil_Water_Actual_Evaporation;
            } else if (varname.compare("Daily_Runoff") == 0) {
                outvalue = pDaily_Soil_out->Daily_Surface_Runoff +
                           pDaily_Soil_out->Daily_Lateral_Runoff;
            } else if (varname.compare("Profile_Soil_Water") == 0) {
                outvalue = pDaily_Soil_out->ProfileSoilWater(cell->pSoilProfile);
            }
            }
            //Implement others M.Liu Feb. 28, 2013
        } else if (timestep.compare("GrowthSeason") == 0) {
            OutputGrowthSeasonClass *pGrowth_Season_out = 
                &pOutput->pGrowth_Season[timeseq];
            if (varname.compare("Crop_Yield") == 0) {
                outvalue = pGrowth_Season_out->Crop_Yield;
            }
            //NIY LML 140904
        }
        fout.setValue(cell->getRow(),cell->getCol(),outvalue);
    }
    if (!outfile_path) outfile_path = new CORN::OS::Directory_name_concrete; //CWD
    CORN::OS::File_name_concrete outfile_name_qual
       (*outfile_path,outfile_name,outfile_ext);
    fout.writeAsciiGridFile(outfile_name_qual.c_str());
    delete outfile_path;
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
void BasinClass::PrintEsriGridHourlyOutput()
{
    OutputMainClass *pOutput =
          #ifdef CROPSYST_VERSION
          basin_cells[0]->
          #else
          basin_cells[0]->pSimulation->
          #endif
            pOutput;
    for (int timeseq = 0; 
         timeseq < pOutput->pHour.size();
         timeseq++) {
        OutputHourClass *p_tempHour = &(pOutput->pHour[timeseq]);
        int year = p_tempHour->Current_Year;
        int doy = p_tempHour->Current_DOY;
        if ((year >= ControlRef.Start_Date_Hourly_Esri_Grid_Output.get_year()) &&
            (year <= ControlRef.End_Date_Hourly_Esri_Grid_Output.get_year()) &&
            (doy >= ControlRef.Start_Date_Hourly_Esri_Grid_Output.get_DOY()) &&
            (doy <= ControlRef.End_Date_Hourly_Esri_Grid_Output.get_DOY())
            ) {
            for (int layer = 1; layer <= basin_cells[0]->pSoilProfile->NumberOfLayers(); layer++) {
                PrintEsriGridOutputVariable(timeseq,"Layer_Water_Content",layer,"Hourly");
            }
            PrintEsriGridOutputVariable(timeseq,"hourlySurfaceInFlow_m3",-9999,"Hourly");
            PrintEsriGridOutputVariable(timeseq,"hourlySurfaceOutFlow_m3",-9999,"Hourly");
            PrintEsriGridOutputVariable(timeseq,"hourlyDrainage_m3",-9999,"Hourly");
            PrintEsriGridOutputVariable(timeseq,"hourlyLateralInFlow_m3",-9999,"Hourly");
            PrintEsriGridOutputVariable(timeseq,"hourlyLateralOutFlow_m3",-9999,"Hourly");
            PrintEsriGridOutputVariable(timeseq,"hourlyLateralUpFlow_m3",-9999,"Hourly");
            PrintEsriGridOutputVariable(timeseq,"Ponded_Water",-9999,"Hourly");
        }
    }
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
void BasinClass::PrintEsriGridDailyOutput()
{
  OutputMainClass *pOutput =
        #ifdef CROPSYST_VERSION
        basin_cells[0]->
        #else
        basin_cells[0]->pSimulation->
        #endif
          pOutput;
    for (int timeseq = 0; 
      timeseq < pOutput->getSoilDaySequence();
      timeseq++) {
        PrintEsriGridOutputVariable(timeseq,"Soil_Water_Actual_Evaporation",-9999,"Daily");
        PrintEsriGridOutputVariable(timeseq,"Daily_Runoff",-9999,"Daily");
        PrintEsriGridOutputVariable(timeseq,"Profile_Soil_Water",-9999,"Daily");
    }
}
#endif
//______________________________________________________________________________
#ifdef VB_SAME_CSV_OUTPUT
void BasinClass::PrintEsriGridGrowthSeasonOutput()
{
    OutputMainClass *pOutput =
        #ifdef CROPSYST_VERSION
        basin_cells[0]->
        #else
        basin_cells[0]->pSimulation->
        #endif
          pOutput;
    for (int timeseq = 0; 
      timeseq < pOutput->getGrowthSeasonSequence();
      timeseq++) {
        PrintEsriGridOutputVariable(timeseq,"Crop_Yield",-9999,"GrowthSeason");
    }
}
#endif
//______________________________________________________________________________
bool BasinClass::start_hour()                                      modification_ //160724
//160724 initializeHourlyFluxesForAllGridCells() // rename to start_hour
{
   bool processed = true;
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        cell->start_hour();  //160724RLN initFluxes();
        #ifdef MBVB_SOIL
        #ifdef MBVB_INFILTRATION
        cell->pSoilProcess->initHourlyFluxes();
        cell->pSoilState->InitHourlyFluxes();
        #else
        // moved to cell::start_hour()
        #endif
        #endif
    }
    return processed;
}
//______________________________________________________________________________
void BasinClass::initializeBasinOutputs()
{
    cum_precipitation_m3 = 0;
    cum_nonintercepted_ppt_m3 = 0;
    cum_irrigation_m3 = 0;
    cum_outlet_lateralflow_m3 = 0;
    cum_outlet_runoff_m3 = 0;
    cum_vertical_drainage_m3 = 0;
    cum_actual_crop_transpiration_m3 = 0;
    cum_actual_soil_evaporation_m3 = 0;
    cum_net_sublimation_m3 = 0;
    cum_N_movein_basin_kg = 0;
    cum_N_movein_soil_kg = 0;
    cum_NO3_N_flowout_basin_kg = 0;
    cum_NH4_N_flowout_basin_kg = 0;
    cum_NO3_N_drainage_kg = 0;                                                   //150921LML
    cum_NH4_N_drainage_kg = 0;                                                   //150921LML
    cum_N_volatization_kg = 0;
    cum_crop_N_uptake_kg = 0;
    cum_C_residue_to_soil_kg = 0;
    cum_CO2_emission_from_residue_kg = 0;
    cum_CO2_emission_from_soil_kg = 0;
    initial_residue_intercept_m3 = 0;                                            //161011LML
    initial_soil_water_m3 = 0;
    initial_soil_ice_m3 = 0;
    initial_soil_profile_mineral_N = 0;                                          //170417LML
    final_soil_profile_mineral_N   = 0;                                          //170417LML
    #ifdef MBVB_SNOW
    initial_snowpack_water_m3 = 0;
    initial_snowpack_ice_m3 = 0;
    #else
    initial_snowpack_swe_m3 = 0;
    #endif
    initial_pond_m3 = 0;
    initial_soil_C_kg = 0;
    initial_residue_C_kg = 0;
    //#pragma omp parallel for private(cell),reduction(+:initial_soil_water_m3,initial_soil_ice_m3,initial_snowpack_water_m3,initial_snowpack_ice_m3,initial_pond_m3,initial_soil_C_kg,initial_residue_C_kg)

    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        Soil_chemicals_profile *soil_chemicals = cell->LAND_UNIT_SIM_ get_soil_chemicals();  //170417LML
        Organic_matter_residues_profile_abstract *organic_matter_residues_profile_kg_m2
             = cell->LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;                   //161011LML
        double cell_area = cell->getArea();

        if (soil_chemicals) {
            initial_soil_profile_mineral_N += (soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)
                                              + soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)) * cell_area;
        }

        #ifdef MBVB_SOIL
        //161110LML initial_residue_intercept_m3 +=
        //161110LML     (organic_matter_residues_profile_kg_m2 ? organic_matter_residues_profile_kg_m2->ref_residues()->get_interception() : 0) * cell_area;  //161011LML
        initial_soil_water_m3 +=
            cell->pSoilState->getTotalSoilLiqWaterContent_m() * cell_area;
        initial_soil_ice_m3 += 
            cell->pSoilState->getTotalSoilIceContent_m() * cell_area;
        #else
        initial_soil_water_m3 += cell_area *
           cell->ref_soil()->ref_hydrology()->calc_available_water_depth_to(9999); //getTotalSoilLiqWaterContent_m
        initial_soil_ice_m3 += cell_area *
            cell->ref_soil()->ref_hydrology()->calc_ice_depth_to();              //160724
        #endif
        #ifdef MBVB_SNOW
        initial_snowpack_water_m3 +=
            mm_to_m(cell->pSnow->Hourly_Water_In_Snow_Amount[23]) * cell_area;
        initial_snowpack_ice_m3 +=
            mm_to_m(cell->pSnow->Hourly_Ice_In_Snow_Amount[23]) * cell_area;
        #else
        //160720  I don't know what these are (liquid water equiv?)
        // Or melted and unmelted water.
        //initial_snowpack_water_m3 = 0.0;
            // cell->meteorology.get_snow_water_equivelent_depth() * cell_area; //160720
        initial_snowpack_swe_m3 +=
            cell->meteorology.get_snow_water_equivelent_depth() * cell_area;    //160720
        #endif
        initial_pond_m3 += 
            cell->pond.get_depth() * cell_area;
        #ifndef CROPSYST_VERSION
        initial_soil_C_kg += cell->pSoilState->getTotalSOMCarbonMass() * cell_area; 
        initial_residue_C_kg += (cell->pSoil->pOrganicResidueState->Standing_Stubble_Carbon_Mass
                                + cell->pSoil->pOrganicResidueState->Surface_Residue_Carbon_Mass
                                + cell->pSoil->pOrganicResidueState->Soil_Residue_Carbon_Mass) 
                                  * cell_area;
        #else
        Organic_matter_residues_profile_abstract *OM_residues_profile_kg_m2
            = cell->LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;
        if (OM_residues_profile_kg_m2)
        {  initial_soil_C_kg    += OM_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_SOM_AND_MICROBIAL,ENTIRE_PROFILE_DEPTH_as_9999,false)  * cell_area;
           initial_residue_C_kg += OM_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,ENTIRE_PROFILE_DEPTH_as_9999,true) * cell_area;
        }
        #endif
    }
}
//______________________________________________________________________________
void BasinClass::cumBasinOutputsFromHourly(int hour,int total_hourth)
{
    //LML NIY
    //#pragma omp parallel for private(cell,cell_area) reduction(+:cum_precipitation_m3,cum_nonintercepted_ppt_m3,cum_irrigation_m3,cum_outlet_runoff_m3,cum_vertical_drainage_m3,cum_net_sublimation_m3,cum_nitrate_flowout_basin_kg,cum_amonia_flowout_basin_kg)
    int solutes = ControlRef.getSoluteSpecies();
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        double cell_area = cell->getArea();
        #ifndef CROPSYST_VERSION
        cum_precipitation_m3 += 
            mm_to_m(cell->pWeatherDaily->getHourlyPrecipitation(hour)) * cell_area;
        cum_nonintercepted_ppt_m3 += 
            mm_to_m(cell->pSnow->Hourly_Non_Intercepted_Precipitation_mm[hour]) * cell_area;
        cum_irrigation_m3 += cell->pSoilProcess->Hourly_Irrigation_m * cell_area;
        #endif
        if (cell->isOutlet()) {
            if (cell->hourly_flow_m3.LateralOut > 1.e-12) {
                for (int layer = 1; layer <= cell->pSoilProfile->NumberOfLayers(); ++layer) {
                    double tmp_out_m3 = cell->hourly_LateralOutFlowLayer_m3[layer] * cell->hourly_fraction_leaving_watershed[layer];
                    cum_outlet_lateralflow_m3          += tmp_out_m3;
                    output_dailyBasinLateralOutFlow_m3 += tmp_out_m3;            //150917LML
                    for (int s = 0; s < solutes; s++) {
                       output_dailyBasinLateralOutFlowSolute_kg[s] += cell->hourly_LateralOutFlowSoluteLayer_kg[layer][s] * cell->hourly_fraction_leaving_watershed[layer];
                    }
                }
            }
            double tmp_out_m3 = cell->hourly_flow_m3.SurfaceOut * cell->hourly_fraction_leaving_watershed[0];
            cum_outlet_runoff_m3               += tmp_out_m3;
            output_dailyBasinSurfaceOutFlow_m3 += tmp_out_m3;                    //150917LML
            for (int s = 0; s < solutes; s++) {
                output_dailyBasinSurfaceOutFlowSolute_kg[s] += cell->hourly_flow_solute_kg[s].SurfaceOut * cell->hourly_fraction_leaving_watershed[0];
            }
        }
        cum_vertical_drainage_m3     += cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Drainage_m * cell_area;
        output_dailyBasinDrainage_m3 += cell->soil_tallies/*160722RLN pSoilState*/->Hourly_Drainage_m * cell_area; //150917LML
        //150921LML cum_net_sublimation_m3       += mm_to_m(cell->pSnow->Hourly_Sublimation_mm[hour]) * cell_area;
        //150917LML cum_nitrate_flowout_basin_kg += cell->hourly_flow_solute_kg[SL_Nitrate].LateralOut
        //150917LML                                 + cell->hourly_flow_solute_kg[SL_Nitrate].SurfaceOut;
        //150917LML cum_amonia_flowout_basin_kg  += cell->hourly_flow_solute_kg[SL_Ammonia].LateralOut
        //150917LML                                + cell->hourly_flow_solute_kg[SL_Ammonia].SurfaceOut;
        //LML NIY 14/04/22
        /*
        cum_N_movein_basin_kg;
        cum_N_movein_soil_kg;
        cum_N_volatization_kg;
        cum_crop_N_uptake_kg;

        cum_C_residue_to_soil_kg;
        cum_CO2_emission_from_residue_kg;
        cum_CO2_emission_from_soil_kg;
        */
        /*if (cell->getCellId() == 1)
        std::clog<<"Before saveHourlyBasinOutFLow:"
                 <<"\tcell#"<<cell->getCellId()
                 <<"\thour:"<<ControlRef.hour
                 <<"\tlayer:"<<5
                 <<"\tLOutFlowLayer_m3:"<<cell->hourly_LateralOutFlowLayer_m3[5]
                 <<std::endl;*/
    }
    #ifdef HOURLY_BASIN_OUTPUT
    saveHourlyBasinOutFLow(total_hourth);       //LML 141013
    #endif
}
//______________________________________________________________________________
void BasinClass::cumBasinOutputsFromDaily()                  //LML 141017
{
    for (long i = 0; i < num_cells; i++) {
        BasinCellClass *cell = basin_cells[i];
        double cell_area = cell->getArea();
        #ifndef CROPSYST_VERSION
        cum_C_residue_to_soil_kg += 
            cell->pSoilState->Profile_Carbon_Transferred_From_Residue_To_SOM * cell_area;
        cum_CO2_emission_from_residue_kg += 
            cell->pSoilState->Profile_Residue_Carbon_Lost_As_CO2 * cell_area;
        cum_CO2_emission_from_soil_kg += 
            cell->pSoilState->Profile_SOM_Carbon_Lost_As_CO2 * cell_area;
        #else
        cum_precipitation_m3        +=
            cell->LAND_UNIT_SIM_ meteorology.ref_precipitation_actual().get_m() * cell_area; //160414RLN
        cum_nonintercepted_ppt_m3   +=
            #ifdef MBVB_SOIL
            mm_to_m(cell->pSoilState->Non_Intercepted_Precipitation_mm) * cell_area;
            #else
            cell->LAND_UNIT_SIM_ meteorology.ref_precipitation_effective().get_m() * cell_area; //160414RLN
            #endif
        cum_net_sublimation_m3      +=
            #ifdef MBVB_SNOW
            mm_to_m(cell->pSnow->Daily_Sublimation_Or_Desublimation_mm) * cell_area;
            #else
            0.0;  // No sublimation
            #endif
        cum_crop_N_uptake_kg        += (cell->crop_active_or_intercrop ? (cell->crop_active_or_intercrop->get_nitrogen()->get_daily_uptake()) : 0) * cell_area;  //170417LML

        #ifdef CROPSYST_CHEMICAL_TRANSPORT
        #ifdef MBVB_SOIL
        Soil_chemicals_profile *soil_chemicals = cell->get_soil_chemicals();     //160323RLN
        if (soil_chemicals)                                                      //160323RLN
        {
        cum_NO3_N_drainage_kg       += soil_chemicals->NO3->balance_leached_molecular * NO3_to_N_conv * cell_area;//160323RLN
        cum_NH4_N_drainage_kg       += soil_chemicals->NH4->balance_leached_molecular * NH4_to_N_conv * cell_area;//160323RLN
        output_dailyBasinDrainageSolute_kg[SL_Ammonia] += soil_chemicals->NO3->balance_leached_molecular * cell_area;//160323RLN
        output_dailyBasinDrainageSolute_kg[SL_Nitrate] += soil_chemicals->NH4->balance_leached_molecular * cell_area;//160323RLN
        }
        #else

        NO3_Profile *NO3 = 0;
        NH4_Profile *NH4 = 0;
        if (cell->soil && cell->soil->chemicals)
        {
           NO3 = cell->soil->chemicals->NO3;
           NH4 = cell->soil->chemicals->NH4;
           Chemical_balance_accumulators *NO3_CONT_bal_accums = NO3 ? NO3->CONT_bal_accums : 0;
           Chemical_balance_accumulators *NH4_CONT_bal_accums = NH4 ? NH4->CONT_bal_accums : 0;

           cum_NO3_N_drainage_kg       += cell_area * NO3_CONT_bal_accums->get_reported_leached(true);
           cum_NH4_N_drainage_kg       += cell_area * NH4_CONT_bal_accums->get_reported_leached(true);
           output_dailyBasinDrainageSolute_kg[SL_Nitrate] = cum_NO3_N_drainage_kg * N_to_NO3_conv;
           output_dailyBasinDrainageSolute_kg[SL_Ammonia] = cum_NH4_N_drainage_kg * N_to_NH4_conv;
        }
        #endif
        #endif



        //150921LML NYI!!! cum_irrigation_m3 += cell->pSoilProcess->Hourly_Irrigation_m * cell_area;


        //150921LML NYI!!!
        //cum_C_residue_to_soil_kg +=
        //cum_CO2_emission_from_residue_kg +=
        //cum_CO2_emission_from_soil_kg +=


        #endif
    }    
    cum_NO3_N_flowout_basin_kg += (output_dailyBasinLateralOutFlowSolute_kg[SL_Nitrate]
                                   + output_dailyBasinSurfaceOutFlowSolute_kg[SL_Nitrate]
                                  ) * NO3_to_N_conv;
    cum_NH4_N_flowout_basin_kg += (output_dailyBasinLateralOutFlowSolute_kg[SL_Ammonia]
                                   + output_dailyBasinSurfaceOutFlowSolute_kg[SL_Ammonia]
                                  ) * NH4_to_N_conv;
}
//______________________________________________________________________________
void BasinClass::finalizeBasinOutputs()
{
   #ifdef LIU_DEBUG
    std::clog<<"Summarize for Basin output..."<<std::endl;
   #endif
    final_residue_intercept_m3 = 0;
    final_soil_water_m3 = 0;
    final_soil_ice_m3 = 0;
    #ifdef MBVB_SNOW
    final_snowpack_water_m3 = 0;
    final_snowpack_ice_m3 = 0;
    #else
    final_snowpack_swe_m3 = 0;
    #endif
    final_pond_m3 = 0;
    final_soil_C_kg = 0;
    final_residue_C_kg = 0;
    //#pragma omp parallel for private(cell),reduction(+:final_soil_water_m3,final_soil_ice_m3,final_snowpack_water_m3,final_snowpack_ice_m3,final_pond_m3,final_soil_C_kg,final_residue_C_kg)
    for (long i = 0; i < num_cells; i++)
    {   BasinCellClass *cell = basin_cells[i];
        Soil_chemicals_profile *soil_chemicals = cell->LAND_UNIT_SIM_ get_soil_chemicals();  //170417LML
        Organic_matter_residues_profile_abstract *organic_matter_residues_profile_kg_m2
             = cell->LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;                   //161011LML
        double cell_area = cell->getArea();
        if (soil_chemicals) {
            final_soil_profile_mineral_N += (soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)
                                             + soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)) * cell_area;
        }
        #ifdef MBVB_SOIL
        const SoilStateClass &cell_soil_state = *cell->pSoilState;                //160411RLN
        cum_actual_crop_transpiration_m3 +=
            cell_soil_state.Cumulative_Actual_Crop_Transpiration_m * cell_area;
        cum_actual_soil_evaporation_m3 += 
            (//161014LML cell_soil_state.Cumulative_Actual_Soil_Evaporation_m
             //160412 WARNING, it is unclear if Cumulative_Actual_Soil_Evaporation_m is
             // a cumulation for the daily or cumulation for the simulation period.
             // need more distiguishing variable names.
             //161014LML + cell->pond.get_evaporation_actual_day()                           //160808_160411RLN
             cell_soil_state.Cumulative_Actual_Soil_Evaporation_m
            ) * cell_area;
        //final_residue_intercept_m3 +=
        //    (organic_matter_residues_profile_kg_m2 ? organic_matter_residues_profile_kg_m2->ref_residues()->get_interception() : 0) * cell_area;  //161011LML
        final_soil_water_m3 += 
            cell_soil_state.getTotalSoilLiqWaterContent_m() * cell_area;
        final_soil_ice_m3 += 
            cell_soil_state.getTotalSoilIceContent_m() * cell_area;
        #else
        cum_actual_crop_transpiration_m3 = cell_area * cell->CONTINUOUS_accumulators_active->act_transpiration;
        cum_actual_soil_evaporation_m3   = cell_area *
            (cell->CONTINUOUS_accumulators_active->act_soil_evaporation
            +cell->CONTINUOUS_accumulators_active->act_pond_evaporation);
        final_soil_water_m3 += cell_area * cell->ref_soil()->ref_hydrology()->calc_available_water_depth_to(9999);
        final_soil_ice_m3   += cell_area * cell->ref_soil()->ref_hydrology()->calc_ice_depth_to(9999);
        #endif
        #ifdef MBVB_SNOW
        final_snowpack_water_m3 += 
            mm_to_m(cell->pSnow->Hourly_Water_In_Snow_Amount[23]) * cell_area;
        final_snowpack_ice_m3 += 
            mm_to_m(cell->pSnow->Hourly_Ice_In_Snow_Amount[23]) * cell_area;
        #else
        //161011LML final_snowpack_water_m3 += 0;
            //160720 mm_to_m(cell->pSnow->Hourly_Water_In_Snow_Amount[23]) * cell_area;
        final_snowpack_swe_m3 +=
            cell->meteorology.get_snow_water_equivelent_depth() * cell_area;     //160720RLN
        #endif
        final_pond_m3 +=
            cell->pond.get_depth() * cell_area;
        #ifndef CROPSYST_VERSION
        final_soil_C_kg += cell->pSoilState->getTotalSOMCarbonMass() * cell_area; 
        final_residue_C_kg += (cell->pSoil->pOrganicResidueState->Standing_Stubble_Carbon_Mass
                                + cell->pSoil->pOrganicResidueState->Surface_Residue_Carbon_Mass
                                + cell->pSoil->pOrganicResidueState->Soil_Residue_Carbon_Mass)  * cell_area;
        #else
        //161014LML Organic_matter_residues_profile_abstract *OM_residues_profile_kg_m2      //160225RLN
        //161014LML    = cell->LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2;
        if (organic_matter_residues_profile_kg_m2)                                           //160225RLN
        {  final_soil_C_kg    += organic_matter_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_SOM_AND_MICROBIAL,ENTIRE_PROFILE_DEPTH_as_9999,false)  * cell_area;
           final_residue_C_kg += organic_matter_residues_profile_kg_m2->sum_carbon_to_depth_kg_m2(INCLUDE_RESIDUE_OM,ENTIRE_PROFILE_DEPTH_as_9999,true) * cell_area;
        }
        #endif
    }
   #ifdef LIU_DEBUG
    std::clog<<"completed."<<std::endl;                                          //160225RLN
   #endif
}
//______________________________________________________________________________
//void BasinClass::OverlandflowSpaceloop(CORN::Date today,const double t_start,const double t_length)
//{
    //Implementation
//}
//______________________________________________________________________________
#ifdef VBBASIN_STRUCTURE
void BasinClass::calcMainSlopesAndAspect(double **Elevation_array,int center_i,int center_j, 
  double center_length,double &Aspect,double &Slope)
{
    double Elevation_Max(-9999.0);
    double Elevation_min(10000000.0);
    int Position_Min_i(-1);
    int Position_Min_j(-1);
    int Position_Max_i(-1);        
    int Position_Max_j(-1);       
    for (int h = center_i - 1;h <= center_i + 1; h++) {
        for (int k = center_j - 1;k <= center_j + 1; k++) {
            if (Elevation_array[h][k] < Elevation_min) {
                Elevation_min = Elevation_array[h][k];
                Position_Min_i = h;
                Position_Min_j = k;
            }
            if (Elevation_array[h][k] > Elevation_Max) {
                Elevation_Max = Elevation_array[h][k];
                Position_Max_i = h;
                Position_Max_j = k;
            }
        }
    }
    //Slope
    double OppositeSlide = (Position_Max_j - Position_Min_j) * center_length;  //m
    double AdjacentSlide = (Position_Max_i - Position_Min_i) * center_length;  //m
    double Hypotenuse = sqrt(pow(OppositeSlide,2) + pow(AdjacentSlide,2)); //m
    Slope = ((Elevation_Max - Elevation_min) / Hypotenuse) * 100.0;  //%
    //Aspect
    if (fabs(AdjacentSlide) > 0)
        Aspect = atan(OppositeSlide / AdjacentSlide) * 180. / Pi;
    else
        Aspect = 90. - atan(AdjacentSlide / OppositeSlide) * 180. / Pi;
}
//______________________________________________________________________________
void BasinClass::calcSurroundingElevations(double **Elevation_array,double **outarray)
{
    //LML 141002 Bad design, will be replaced later!!!
    int nrow = gGridMask.getNrows();
    int ncol = gGridMask.getNcols();
    std::vector<std::vector<double> > temp_out;
    temp_out.resize(nrow);
    for (int i = 0; i < nrow; i++) temp_out[i].resize(ncol);
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long ij = 0; ij < nrow * ncol ; ij++) {
        long i = (long) (ij / ncol);
        long j = ij % ncol;
        if (inner_id[i][j]<0) {//Non-member
            double testmax[8];
            testmax[0] = ((i==0) || (j==0))?0:Elevation_array[i-1][j-1];
            testmax[1] = (i==0)?0:Elevation_array[i-1][j];
            testmax[2] = ((i==0) || (j==(ncol-1)))?0:Elevation_array[i-1][j+1];
            testmax[3] = (j==0)?0:Elevation_array[i][j-1];
            testmax[4] = (j==(ncol-1))?0:Elevation_array[i][j+1];
            testmax[5] = ((i==(nrow-1)) || (j==0))?0:Elevation_array[i+1][j-1];
            testmax[6] = (i==(nrow-1))?0:Elevation_array[i+1][j];
            testmax[7] = ((i==(nrow-1)) || (j==(ncol-1)))?0:Elevation_array[i+1][j+1];
            temp_out[i][j] = MaxOfArray(testmax,-9999,8);
        } else {
            temp_out[i][j] = Elevation_array[i][j];
        }
    }
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)                        //schedule(dynamic,1)
    for (long ij = 0; ij < nrow * ncol ; ij++) {
        long i = (long) (ij / ncol);
        long j = ij % ncol;
            outarray[i][j] = temp_out[i][j];
    }
}
//______________________________________________________________________________
#endif
//_150526_______________________________________________________________________
double BasinClass::getMinElevAround(int row,int col)
{
    //LML 141002 Bad design, will be replaced later!!!
    int nrow = gElev.getNrows();
    int ncol = gElev.getNcols();
    double minvalue = 999999;
    for (int i = -1; i <= 1; i++) {
        int cur_row = row + i;
        for (int j = -1; j <= 1; j++) {
            int cur_col = col + j;
            if (gElev.IsValidCell(cur_row,cur_col)) {
                double value = gElev.getValue(cur_row,cur_col);
                minvalue = CORN::must_be_less_or_equal_to(value,minvalue);
            }
        }
    }
    return minvalue;
}
//______________________________________________________________________________
#ifdef CROPSYST_VERSION
RENDER_INSPECTORS_DEFINITION(BasinClass)
{
/*160623RLN
    KNOW_EMANATOR(false); // At this time we don't need to the inspection instance.
    for (long i = 0; i < num_cells; i++)
    {  BasinCellClass *cell = basin_cells[i];
       cell->LAND_UNIT_SIM_ render_inspectors
          (inspectors,&emanator
          ,""
          // This should be the cell ID I think Land_unit_simulation_VX
          // will assign the cell ID but I need to check 150919RLN
          ,statistic);
    }
    return &emanator;
*/
}
//_____________________________________________________________________________/
nat32 BasinClass::dump_inspectors(std::ostream &strm, CS::Inspection_level level)
{
/*160606RLN to be redone
   CORN::Text_list inspector_labels_unique; inspector_labels_unique.set_unique_keys(true);
   // Every crop and every cell will have its own set of inspectors
   // Here we only want to output one set of unique inspector labels
   if (inspection.inspectors[level])
   FOR_EACH_IN(inspector,CS::Inspector,*(inspection.inspectors[level]),each_inspector)
      inspector_labels_unique.add_string(inspector->provide_qualified_string());
   FOR_EACH_END(each_inspector);
   return inspector_labels_unique.write(strm);
   // return inspection.inspectors[level]->write(strm);
*/
}
//_2015-10-02__________________________________________________________________/
#endif
//170404LML #ifdef PREDEFINE_N_APPLICATION_PER_CELL
bool BasinClass::readPredefinedNFertilization()
{   //read predefined N fertilization csv format input.
    //The file head is: Cell_ID, [crop1_name_consistent_with_crop_parameter_file_name], [crop2] ...
    //unit: kgN/ha for entire growth season
    std::ifstream ifile(ControlRef.predefined_N_fertilization_name.c_str());
    if (ifile.is_open()) {
        std::string line("");
        std::getline(ifile,line);
        std::stringstream ss(line);
        size_t crop_counts = std::count(line.begin(), line.end(), ',');
        predefined_N_fertilization_crop_name.resize(crop_counts);
        predefined_N_fertilization_kgN_per_ha.resize(num_cells);
        for (int i = 0; i < num_cells; i++) {
            predefined_N_fertilization_kgN_per_ha[i].resize(crop_counts);
            for (int j = 0; j < crop_counts; j++)
                predefined_N_fertilization_kgN_per_ha[i][j] = 0;
        }
        int i = 0;
        std::string token;
        while(std::getline(ss, token, ',')) {
            if (i >= 1) {
                if (token[token.size() - 1] == '\r') token.erase(token.size() - 1);
                predefined_N_fertilization_crop_name[i - 1] = token;
            }
            i++;
        }
        while (std::getline(ifile,line)) {
            std::stringstream ss_data(line);
            i = 0;
            int cell_index = -1;
            while (std::getline(ss_data, token, ',')) {
                if (i == 0) cell_index = getGridIndex(std::stoi(token));
                if (i >= 1 && cell_index >= 0)
                    predefined_N_fertilization_kgN_per_ha[cell_index][i - 1] = std::stod(token);
                i++;
            }
        }
        ifile.close();
    } else {
        std::clog << "Warning: cannot open the predefined_N_fertilization_name:\"" << ControlRef.predefined_N_fertilization_name.c_str()
                  << "\"!!!\n";
        return false;
    }
    return true;
}
//_2017-03-20LML_______________________________________________________________/
int BasinClass::getGridIndex(const int grid_id)
{
    int index = -1;
    for (int i = 0; i < num_cells; i++) {
        if (basin_cells[i]->getCellId() == grid_id) {
            index = i;
            break;
        }
    }
    return index;
}
//_2017-03-20LML_______________________________________________________________/
//170404LML #endif
//______________________________________________________________________________
#ifdef DEBUG_LIU_OUT_CSV
void print_basin_daily_for_debug_head(std::ofstream &outf)
{
    outf<<"Year,"
        <<"Month,"
        <<"Day,"
        <<"DOY,"
        <<"Drainage_m3,"
        <<"Surface_runoff_m3,"
        <<"Lateral_runoff_m3,"
        <<"NO3_N_Runoff_kg,"
        <<"NH4_N_Runoff_kg,"
        <<"total_N_Runoff_kg,"
        <<"NO3_N_Leach_kg,"
        <<"NH4_N_Leach_kg,"
        <<"total_N_Leach_kg"
        <<std::endl;
        basin_output_head_printed = true;
}
//______________________________________________________________________________
void print_basin_daily_for_debug(std::ofstream &outf,const CORN::Date &day,const BasinClass &basin)
{
    double NO3_N_runoff_kg = (basin.output_dailyBasinLateralOutFlowSolute_kg[SL_Nitrate] + basin.output_dailyBasinSurfaceOutFlowSolute_kg[SL_Nitrate]) * NO3_to_N_conv;
    double NH4_N_runoff_kg = (basin.output_dailyBasinLateralOutFlowSolute_kg[SL_Ammonia] + basin.output_dailyBasinSurfaceOutFlowSolute_kg[SL_Ammonia]) * NH4_to_N_conv;
    double NO3_N_drainage_kg= basin.output_dailyBasinDrainageSolute_kg[SL_Nitrate] * NO3_to_N_conv;
    double NH4_N_drainage_kg= basin.output_dailyBasinDrainageSolute_kg[SL_Ammonia] * NH4_to_N_conv;
    outf<<(int)day.get_year()
        <<","<<(int)day.get_month()
        <<","<<(int)day.get_DOM()
        <<","<<(int)day.get_DOY()
        <<","<<basin.output_dailyBasinDrainage_m3
        <<","<<basin.output_dailyBasinSurfaceOutFlow_m3
        <<","<<basin.output_dailyBasinLateralOutFlow_m3
        <<","<<NO3_N_runoff_kg
        <<","<<NH4_N_runoff_kg
        <<","<<NO3_N_runoff_kg + NH4_N_runoff_kg
        <<","<<NO3_N_drainage_kg
        <<","<<NH4_N_drainage_kg
        <<","<<NO3_N_drainage_kg + NH4_N_drainage_kg
        <<std::endl;
}
//______________________________________________________________________________
void print_cell_daily_for_debug_head(std::ofstream &outf,BasinCellClass *cell)
{
    int soil_layers = cell->pSoilProfile->NumberOfLayers();
    outf<<"Year,"
        <<"Month,"
        <<"Day,"
        <<"DOY,"
        <<"CELL_ID,"
        <<"ppt,"
        <<"tmax,"
        <<"tmin,"
        <<"tavg,"
        <<"Crop_Name,"
        <<"Phenology,"
        <<"Cum_Thermal_Time,"
        <<"Canopy_Biomass_kg_m2,"
        <<"Canopy_Cover,"
        <<"LAI,"
        <<"GAI,"
        //<<"NetRad_MJ_day,"
        <<"RefET_mm,"
        <<"Pot_Transp_mm,"
        <<"Act_Transp_mm,"
        <<"Soil_Evap_mm,"
        <<"Snow_Sub_Desub_mm,"
        <<"Pond_Evap_mm,"
        <<"Canopy_intercepted_mm,"
        <<"ET_mm,"
        <<"Drainage_mm,"
        <<"Surface_runon_mm,"
        <<"Surface_runoff_mm,"
        <<"Lateral_runon_mm,"
        <<"Lateral_runoff_mm,"
        <<"Snowfall_daily_on_ground_mm,"
        <<"Non-intercepted_ppt_mm,"
        <<"Snow_melt_SWE_mm,"
        <<"Act_N_Uptake_kg_m2,"
        <<"Water_Stress_Index,"
        <<"N_Stress_Index,"
        <<"Root_Length_m,"
        <<"Pond_mm,"
        <<"Snow_SWE_mm,"
        <<"Soil_water_mm,"
        <<"Soil_Profile_VWC,"
        <<"NO3_N_Leach_kg_m2,"
        <<"NH4_N_Leach_kg_m2,"
        <<"NO3_N_Net_Lateral_flowin_kg,"
        <<"NH4_N_Net_Lateral_flowin_kg,"
        <<"NO3_N_Net_surface_flowin_kg,"
        <<"NH4_N_Net_surface_flowin_kg,";
        for (int layer = 1; layer <= soil_layers; layer++)
          outf<<"liq_vwc["<<layer<<"],";
        //for (int layer = 1; layer <= soil_layers; layer++)
        //  outf<<"water_pot["<<layer<<"],";
        for (int layer = 1; layer <= soil_layers; layer++)
          outf<<"ice_vwc["<<layer<<"],";
        for (int layer = 1; layer <= soil_layers; layer++)
          outf<<"NH4_kg_m2["<<layer<<"],";
        for (int layer = 1; layer <= soil_layers; layer++)
          outf<<"NO3_kg_m2["<<layer<<"],";
        outf<<std::endl;
        cell_output_head_printed = true;
}
//______________________________________________________________________________
void print_cell_daily_for_debug(std::ofstream &outf,const CORN::Date &day,const BasinCellClass *cell)
{
    std::wstring wactive_crop_name(L"NOCROP");
    const CropSyst::Crop_interfaced *crop = cell->LAND_UNIT_SIM_ crop_active_or_intercrop;
    const Weather_provider &weather = cell->meteorology_cell.ref_weather_provider();
    bool cropnum = crop ?
                   crop->get_name(wactive_crop_name)
                   : false;
    std::string active_crop_name(wactive_crop_name.begin(),wactive_crop_name.end());
    int soil_layers         = cell->pSoilProfile->NumberOfLayers();
    double transpiration_mm = crop ? m_to_mm(crop->get_act_transpiration_m()) : 0;
    double soilevap_mm      = m_to_mm(cell->pSoilState->Daily_Soil_Water_Actual_Evaporation_m);
    double snow_sub_desub_mm= cell->pSnow->Daily_Sublimation_Or_Desublimation_mm;
    double pond_evap_mm     = cell->output_daily_pond_evaporation_mm;
    double canopy_intcpt_mm = cell->pSoilState->output_daily_canopy_interception_water_mm;
    double total_et_mm      = transpiration_mm
                              + soilevap_mm
                              + snow_sub_desub_mm
                              + pond_evap_mm
                              + canopy_intcpt_mm;
    BasinCellClass::Flows *daily_flow = &(cell->output_flow_m3[TACUM_DAILY]);
    outf<<(int)day.get_year()
        <<","<<(int)day.get_month()
        <<","<<(int)day.get_DOM()
        <<","<<(int)day.get_DOY()
        <<","<<(int)cell->LAND_UNIT_SIM_ ID.number
        <<","<<weather.precipitation.get_mm()
        <<","<<weather.air_temperature_max.Celcius()
        <<","<<weather.air_temperature_min.Celcius()
        <<","<<weather.air_temperature_avg.Celcius()
        <<","<<active_crop_name
        <<","<<(crop ? crop->describe_growth_stage() : "NONE")
        <<","<<(crop ? crop->get_accum_degree_days(false) : 0)
        <<","<<(crop ? crop->get_canopy_biomass_kg_m2() : 0)
        <<","<<(crop ? crop->get_fract_canopy_cover() : 0)
        <<","<<(crop ? crop->get_LAI(true) : 0)
        <<","<<(crop ? crop->get_GAI(true) : 0)
        //<<","<<weather.//(crop ? cell->LAND_UNIT_SIM_ ET_ref->curr_net_radiation : 0)
        <<","<<(crop ? cell->LAND_UNIT_SIM_ ET_ref->get_mm(ET_FAO_56_Penman_Monteith_CropSyst) : 0)
        <<","<<(crop ? m_to_mm(crop->get_pot_transpiration_m(true)) : 0)
        <<","<<transpiration_mm
        <<","<<soilevap_mm
        <<","<<snow_sub_desub_mm
        <<","<<pond_evap_mm
        <<","<<canopy_intcpt_mm
        <<","<<total_et_mm
        <<","<<m_to_mm(cell->get_m_from_m3(daily_flow->Drainage))
        <<","<<m_to_mm(cell->get_m_from_m3(daily_flow->SurfaceIn))
        <<","<<m_to_mm(cell->get_m_from_m3(daily_flow->SurfaceOut))
        <<","<<m_to_mm(cell->get_m_from_m3(daily_flow->LateralIn))
        <<","<<m_to_mm(cell->get_m_from_m3(daily_flow->LateralOut))
        <<","<<cell->pSnow->output_daily_snowfall_on_ground_SWE_mm
        <<","<<cell->pSoilState->Non_Intercepted_Precipitation_mm
        <<","<<cell->pSnow->Daily_Snow_Melt_Amount_mm
        <<","<<(crop ? crop->get_nitrogen()->get_daily_uptake(): 0)
        <<","<<(crop ? crop->get_water_stress_index() : 0)
        <<","<<(crop ? crop->get_nitrogen()->get_stress_index() : 0)
        <<","<<(crop ? crop->get_root_length_m() : 0)
        <<","<<m_to_mm(cell->pond.get_depth())
        <<","<<cell->pSnow->Current_Snow_Pack_SWE_mm
        <<","<<m_to_mm(cell->pSoilState->getTotalSoilWaterContent_m())
        <<","<<cell->pSoilState->getProfileSoilVWC()
        <<","<<cell->pSoilState->Daily_Nitrate_Leaching                          //150921LML
        <<","<<cell->pSoilState->Daily_Ammonium_Leaching                         //150921LML
        <<","<<(cell->output_flow_solute_kg[SL_Nitrate][TACUM_DAILY].LateralIn - cell->output_flow_solute_kg[SL_Nitrate][TACUM_DAILY].LateralOut) * NO3_to_N_conv   //150921LML
        <<","<<(cell->output_flow_solute_kg[SL_Ammonia] [TACUM_DAILY].LateralIn - cell->output_flow_solute_kg[SL_Ammonia][TACUM_DAILY].LateralOut) * NH4_to_N_conv     //NO3_to_N_conv
        <<","<<(cell->output_flow_solute_kg[SL_Nitrate][TACUM_DAILY].SurfaceIn - cell->output_flow_solute_kg[SL_Nitrate][TACUM_DAILY].SurfaceOut) * NO3_to_N_conv   //NO3_to_N_conv
        <<","<<(cell->output_flow_solute_kg[SL_Ammonia] [TACUM_DAILY].SurfaceIn - cell->output_flow_solute_kg[SL_Ammonia][TACUM_DAILY].SurfaceOut) * NH4_to_N_conv;    //NO3_to_N_conv
        for (int layer = 1; layer <= soil_layers; layer++)
          outf<<","<<cell->pSoilState->get_liquid_water_content_volumetric(layer);
        //for (int layer = 1; layer <= soil_layers; layer++)
        //  outf<<","<<cell->pSoilState->hydrology->get_water_potential(layer);
        for (int layer = 1; layer <= soil_layers; layer++)
          outf<<","<<cell->pSoilState->get_ice_content_volumetric(layer);
        const Soil_chemicals_profile *soil_chemicals = cell->LAND_UNIT_SIM_ get_soil_chemicals();//151212RLN
        if (soil_chemicals)
        {  for (int layer = 1; layer <= soil_layers; layer++)
              outf<<","<< soil_chemicals->get_NH4_N_mass_kg_m2(layer);
           for (int layer = 1; layer <= soil_layers; layer++)
              outf<<","<< soil_chemicals->get_NO3_N_mass_kg_m2(layer);
        } else
        {  for (int layer = 1; layer <= soil_layers; layer++) outf<<","<< 0;
           for (int layer = 1; layer <= soil_layers; layer++) outf<<","<< 0;
        }
        outf<<std::endl;
}
#endif

//was 5300 lines
