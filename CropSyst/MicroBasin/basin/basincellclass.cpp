#include "basincellclass.h"
//#include "corn/datetime/date.hpp"
#ifdef CROPSYST_WEATHER
//160808#include "weather_provider_temporary.h"
#else
#  ifdef MBVB_SNOW
#     include "snow/clssnow.h"
#  endif
#endif
#include "util/pubtools.h"
#ifdef CROPSYST_VERSION
#  include "corn/OS/file_system_engine.h"
#  include "common/biometeorology/ET_reference_FAO.h"
#  include "soil/chemicals_profile.h"
#  include "CropSyst/source/organic_matter/OM_residues_profile_abstract.h"
#  include "CS_suite/simulation/CS_land_unit_meteorological.h"
#  include "common/residue/residues_interface.h"                                 //160616LML
#  include "common/residue/residues_common.h"                                    //161108LML
#  include "CropSyst/source/crop/phenology_interface.h"                          //170410LML
#else
#  ifndef CROPSYST_PROPER_CROP
#     include "crop/clscrop.h"
#  endif
#endif
#ifdef VB_SAME_CSV_OUTPUT
#include "CropSyst/MicroBasin/output/outputmainclass.h"
#endif
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif

//______________________________________________________________________________
BasinCellClass::BasinCellClass
   (BasinClass                   &BasinRef_
   ,AllControlClass              &ControlRef_
   ,const CORN::Date_const/*170615LML _const_interface*/             &today_                                         //150630RLN
   #ifdef CROPSYST_VERSION
   ,const CS::Database_directory &database_directory_                            //150723RLN
   #ifdef CELL_METEOROLOGY
      //160808 becoming obsolete eventually delete
   ,Sun                          &sun_basin_                                     //160801RLN
   ,const CS::Solar_irradiance_extraterrestrial_hourly &solar_irradiance_extraterrestrial_basin_ //150708RLN
   #else
   ,const CS::Land_unit_meteorological &meteorology_site_                        //160808
   #endif
  //160801RLN  ,const float64 &_day_length_hours_today_basin                                 //150730RLN
   //150811 ,Common_simulation_log  &_event_log
   #endif
   #ifdef MBVB_INFILTRATION
   ,SoilProfileClass             *pSoilProfile_
   ,SoilProfileClass             *pSoilProfileUnmutable_                         //140814LML
   #endif
   ,double                        lat_dec_degree_                                //150817LML
   ,double                        lon_dec_degree_                                //150817LML
   ,double                        elev_m_                                        //150817LML
   ,std::vector<InitialSoilStateClass *> &parrInitSoilStateRef_                  //160317LML
   ,long                           soilID_index_                                  //160317LML
   /*160808RLN this would not work
   #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
   ,CropSyst::Rotation_parameters &rotationParameterRef_                         //160317LML
   #endif
   */
)
#ifdef CROPSYST_VERSION
#ifdef LAND_UNIT_SIM_AS_SUPERCLASS
: CropSyst::Land_unit_simulation                                                 //141212
   (cell_ID
   ,0 // no cylcing                                                              //141206
   ,ControlRef_ //scenario_control_and_model_options //*this //_scenario_control_and_model_options
   ,today_.get_date32()                                                                       //170615LML
   ,geocoordinate
   ,meteorology_site_
   ,0//scenario_directory should be current working directory
   /*160808RLN this would not work
   #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
   ,rotationParameterRef_
   #endif
   */
   )
//CropSyst::Land_unit_with_output                                                //141212
//   (0 //141212 not currently used, but should pass some sort of basin cell ID sint32                  _LBF_ID                                           //020504
//   ,_ControlRef //scenario_control_and_model_options //*this //_scenario_control_and_model_options
//   ,_today // _ControlRef.today
//   ,_event_log
//   ,0//scenario_directory should be current working directory
//   )
,cell_ID(0)                                                                     //151206RLN

#else
: land_unit_sim(new
   CropSyst::Land_unit_simulation                                                 //141212
   (cell_ID //1512060 //141212 not currently used, but should pass some sort of basin cell ID sint32                  _LBF_ID                                           //020504
   ,0 // no cylcing                                                              //141206
   ,_ControlRef //scenario_control_and_model_options //*this //_scenario_control_and_model_options
   ,_today // _ControlRef.today
   ,geocoordinate
   ,meteorology_site
   //150811 ,_event_log
   ,0//scenario_directory should be current working directory
   ))
,cell_ID(0)                                                                      //151206RLN
#endif
#ifdef CELL_METEOROLOGY
      //160808 becoming obsolete eventually delete
, meteorology_site(today_,geocoordinate,ControlRef_.snow_pack_model_labeled.get())    //151207
#else
, meteorology_site(meteorology_site_)                                            //160808
#endif
   // we should implement MicroBasin's current snowpack model as an option for CropSyst
,database_directory                     (database_directory_)                    //150723RLN
#ifdef CELL_METEOROLOGY
   //160808 becoming obsolete eventually delete
,solar_irradiance_extraterrestrial_basin(solar_irradiance_extraterrestrial_basin_) //150708RLN
#endif
, output_directory_name() //141212RLN not yet decided how to handle output directories
,pCrop(0)                                                                        //150804LML
#else
:
today                   (today_)
,cell_id                (-1L)
,pSnow                  (0)                                                                        //160224
#endif
,slop                   (0)                                                                         //160224
,aspect                 (0)                                                                       //160224
,BasinRef               (BasinRef_)
,ControlRef             (ControlRef_)
//160706 #ifdef WEATHER_PROVIDER_VERSION
,geocoordinate(lat_dec_degree_,lon_dec_degree_,elev_m_)                          //141222 150817LML added initial value
//160706 #endif
,gridtype               (0)
#ifdef MBVB_INFILTRATION
,pSoilProfile           (pSoilProfile_)
,pSoilProfileUnmutable  (pSoilProfileUnmutable_)
//,fraction_leaving_watershed(_pSoilProfile->NumberOfLayers() + 1,0.0)             //150127LML
//,hourlyLateralOutFlowLayer_m3(_pSoilProfile->NumberOfLayers() + 1,0.0)           //150127LML
//,hourlyLateralOutFlowSoluteLayer_kg
//   (_pSoilProfile->NumberOfLayers() + 1
//   ,std::vector<double>(_ControlRef.getSoluteSpecies()))                         //150127LML
#endif
,debug_output(false)                                                             //151007LML
,parrInitSoilStateRef(parrInitSoilStateRef_)                                     //160317LML
,soilID_index(soilID_index_)                                                     //160317LML
/*160808RLN this would not work
#ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
,rotationParameterRef(rotationParameterRef_)                                     //160317LML
#endif
*/
,output_harvested_yield(0)                                                       //160322LML
,report_planting_date_soil_profile_NH4_N(0)                                      //170410LML
,report_planting_date_soil_profile_NO3_N(0)                                      //170410LML
,report_Initial_Profile_NO3_N(0)                                                 //170413LML
,report_Initial_Profile_NH4_N(0)                                                 //170413LML
,report_planting_date_surface_NH4_N(0)                                           //170510LML
,report_planting_date_surface_NO3_N(0)                                           //170510LML
,report_Initial_Surface_NH4_N(0)                                                 //170510LML
,report_Initial_Surface_NO3_N(0)                                                 //170510LML
{

//std::cout << "today:" << simulation_today.as_string() << std::endl;

    #ifdef CROPSYST_VERSION

    // Actually weather should be for each station, not each cell.
    // cell specific weather is not necessary.
    // Mingliang has said that there would be micro climate
    // at least for solar radiation due to hill slope, but this
    // should be applied using a separate mechanism.
    #ifdef CROPSYST_WEATHER
    #else
    #ifdef CELL_METEOROLOGY
    pWeatherDaily = new WeatherStateDailyClass
        #ifdef CROPSYST_VERSION
        (today_,geocoordinate
        #ifdef CELL_METEOROLOGY
        //160808 becoming obsolete eventually delete,
        ,solar_irradiance_extraterrestrial_basin           //151222
        ,sun_basin_.ref_day_length_hours_today() //160801RLN day_length_hours_today_basin_
        #else
        ,meteorology_site.ref_solar_irradiance_extraterrestrial()
        ,meteorology_site.ref_sun().ref_day_length_hours_today()
        #endif
        );                                         //151206_150730RLN
        #else
        ();
        #endif
    #endif
    #endif
    #ifdef CELL_METEOROLOGY
          //160808 becoming obsolete eventually delete
    meteorology_site.know_sun(&sun_basin_);                                           //160801
    // Currently each cell can have its own weather
    // so sky would be specific to each cell.
    // When there is a common weather for the basin
    // then there would be a single sky for the basin.
    // (actually we could probably getby using a sky for the centroid).
    meteorology_site.know_weather_provider(&pWeatherDaily->daily_provider);           //151222
    /*160801 meteorology now provides ET_ref
    LAND_UNIT_SIM_ ET_ref = new ET_Reference_FAO                                 //150804
         (pWeatherDaily->daily_provider                                          //151222_151206RLN
         ,geocoordinate                                                          //151206RLN
         ,_day_length_hours_today_basin
          //NYN      , Aerodynamics &_aerodynamics                               //150601
         ,ET_FAO_56_Penman_Monteith_CropSyst);
    */
    #else
    // meteorology is now setup by basin
    #endif
    #endif

   #ifdef CROPSYST_VERSION
    #ifndef CROPSYST_WEATHER
    #ifdef CELL_METEOROLOGY
    meteorology_site.know_weather_spanning(*pWeatherDaily);                      //151223
    // now using site meteorology
          //160808 becoming obsolete eventually delete
    meteorology_site.know_solar_irradiance_extraterrestrial(solar_irradiance_extraterrestrial_basin);
    #endif
    #endif
    cell_ID.set_number(-1);                                                      //151206RLN
   #else
    #ifndef CROPSYST_PROPER_CROP
    pCrop = new clsCrop(ControlRef,today);
    #endif
    #ifndef CROPSYST_PROPER_MANAGEMENT
    pManagement = new clsManagement(ControlRef,today,BasinRef);                  //140207LML
    pManagement->instantiateManagement();                                        //140207LML
    #endif
	#endif

    #ifdef MBVB_SOIL
    pSoilState = new SoilStateClass(ControlRef,*pSoilProfile,pond
                                    #ifdef CROPSYST_VERSION
                                    ,0
                                    #endif
                                    ,*parrInitSoilStateRef[soilID_index]
                                    );
    soil_tallies = pSoilState;                                                   //160722RLN
    #else
    soil_tallies = new MicroBasin::Soil_tallies;
    #endif
    #ifdef MBVB_SNOW
    pSnow = new clsSnow
       (*pSoilState
       #ifdef CROPSYST_VERSION
       ,solar_irradiance_extraterrestrial_basin                                  //151214RLN
       #endif
       ,*pWeatherDaily                                                           //160224RLN
       ,geocoordinate.get_latitude_dec_deg()                                     //160224RLN
       ,slop // need reference getSlop()                                         //160224RLN
       ,aspect // need reference getAspect()                                     //160224RLN
       ,today_                                                                   //150721RLN
       ,cell_id);
    #endif
    #ifdef MBVB_SOIL
    pSoilProcess = new SoilProcessesClass
       (*pSoilState,ControlRef
       ,today_
       ,*pSoilProfile
       ,LAND_UNIT_SIM_ evaporation_potential_remaining                           //160414
       #ifdef MBVB_SNOW
       ,*pSnow
       #endif
       ,pond,&runoff                                                      //150930RLN_150709
       #if (defined(CHEMICAL_TRANSPORT) && defined(CROPSYST_VERSION))
       ,0 // pSoil->chemicals                                                    //150812
       #endif
       #ifdef CROPSYST_VERSION
       //160801RLN ,LAND_UNIT_SIM_ ET_ref
       //160801 ,meteorology_site.provide_ET_reference()                                  //160801RLN
       ,meteorology_site.provide_solar_irradiance_extraterrestrial()                      //160808
       ,meteorology_site.ref_relative_humidity_min()                                  //151222
       #endif
       );
    #if (defined(MBVB_INFILTRATION) && defined(FROZEN_SOIL))
    pSoilProfile->setIceContentRef(pSoilState->Ice_Content);                     //140820LML
    pSoilProfileUnmutable->setIceContentRef(pSoilState->Ice_Content);            //140820LML
    #endif
    pSoil = new clsSoil
      (ControlRef
      //160721 #ifdef OLD_EVAPORATE
      //160721 ,LAND_UNIT_SIM_ evaporation_potential_remaining                            //160412RLN
      //160721 #endif
      ,today_                                                                   //151222RLN
      //160721 #ifdef CROPSYST_WEATHER
      //160721 #else
      #ifdef MBVB_SNOW
      ,*pSnow
      #endif
      #ifdef CROPSYST_WEATHER
      //RLN NYI need to determine exactly what soil needs of weather
      #else
      #ifdef MBVB_SOIL_TEMPERATURE
      ,*pWeatherDaily
      #endif
      #endif
      //160721 #endif
      #ifdef CROPSYST_VERSION
      ,ControlRef.annual_temperature                                             //141222
      #endif
      #ifdef PROVIDES_SOIL_TEMPERATURE_PROFILE
      ,meteorology_site                                                               //160721RLN
      #endif
      ,LAND_UNIT_SIM_ organic_matter_residues_profile_kg_m2                      //160224
      );
    /*160324LML
    pSoil->instantiateSoil
        (pSoilProfile,pSoilState,pSoilProcess
      //160224#ifndef CROPSYST_VERSION
      //160224,ControlRef.annual_temperature                                             //141222
      //160224#endif
         );
     */
   pSoil->submit_evaporator(pSoilProcess->evaporator);                            //160608RLN
   pSoil->instantiateSoilReferenceAndTemperature(pSoilProfile,pSoilState,pSoilProcess); //160324LML
   #endif

   #ifdef CROPSYST_VERSION
   #ifdef MBVB_SOIL
   if (LAND_UNIT_SIM_ scenario_control_and_model_options.run_chemical)           //151212RLN
   {
      pSoilState->chemicals_optional = pSoilProcess->chemicals_optional = pSoil->provide_chemicals(); //151212RLN_150914LML
      pSoil->instantiateSoilChemicalTransport();                                 //160324LML
   }
   #endif
   pOutput = new OutputMainClass(today,this);                                    //160225RLN_151005LML
   //pOutput->Set_Gridcell_ref(this);                                            //151005LML
   #else
    pSimulation = new clsSimulation
       (ControlRef,today,*pSoil,*pManagement);
    pSimulation->pOutput->pSnowRef = pSnow;
    pSimulation->pGridCellRef = this;
    pWeatherPMET = new WeatherPMETClass;
    pDebugState = new DebugStateClass;

	#endif
    //int num_solute = ControlRef.getSoluteSpecies();
    //hourlyLateralInFlowSolute_kg.resize(num_solute,0);
    //hourlyLateralOutFlowSolute_kg.resize(num_solute,0);
    //hourlySurfaceInFlowSolute_kg.resize(num_solute,0);
    //hourlySurfaceOutFlowSolute_kg.resize(num_solute,0);
}
//______________________________________________________________________________
long BasinCellClass::getCellId() {return cell_id;}
void BasinCellClass::setCellId(long _cell_id)
   #ifdef CROPSYST_VERSION
   {  cell_ID.set_number(_cell_id); }                                              //151206
   #else
   {cell_id = _cell_id;}
   #endif
int BasinCellClass::getGridType() {return gridtype;}
void BasinCellClass::setGridType(int _gridtype) {gridtype = _gridtype;}
void BasinCellClass::setLatitude(double _latitude) { geocoordinate.set_latitude_dec_deg_f64(_latitude);}
void BasinCellClass::setLongitude(double _longitude){ geocoordinate.set_longitude_dec_deg_f64(_longitude);}
void BasinCellClass::setSumDownhillSlop(double _sum_downhill_slop) {
    sum_downhill_slop = _sum_downhill_slop;
}
//______________________________________________________________________________
double BasinCellClass::getSumDownhillSlop() {return sum_downhill_slop;}
//______________________________________________________________________________
void BasinCellClass::setCropRotationID(int _crop_rotation_id)
{  crop_rotation_id = _crop_rotation_id;
}
//______________________________________________________________________________
int BasinCellClass::getCropRotationID() {return crop_rotation_id;}
//______________________________________________________________________________
#ifdef MACA_V1_MBMET
void BasinCellClass::setWeatherStationID(int id) {weather_station_id = id;}
int BasinCellClass::getWeatherStationID() {return weather_station_id;}
#endif
//______________________________________________________________________________
bool BasinCellClass::start_day()                                                 //141221
{
    bool started(true);
    //160722RLN #ifdef MBVB_SOIL
    //160722RLN pSoilState->InitDailyFluxes();
    //160722RLN #else
    soil_tallies->start_day();                                                   //160722RLN
    //160722RLN #endif
    init_accumulater_outflow(TACUM_DAILY);
    if ((today == ControlRef.start_date) || (today.get_DOY() == 1))
        init_accumulater_outflow(TACUM_ANNUAL);
    if ((today == ControlRef.start_date) || (today.get_DOM() == 1))
        init_accumulater_outflow(TACUM_MONTH);

    //170417LML added for growth_season accumulation
    CORN::Date_32_clad planting_date(0);
    if (crop_active_or_intercrop) planting_date.set_date32(crop_active_or_intercrop->get_planting_date().get_date32());
    if (crop_active_or_intercrop && (today.get_datetime64() == planting_date.inc_days(1)))
        init_accumulater_outflow(TACUM_GROWTHSEASON);

    #ifdef CROPSYST_VERSION
    #ifdef CELL_METEOROLOGY
          //160808 becoming obsolete eventually delete, meteorology_site is now owned and started by basin                            //160808
    started &= meteorology_cell.start_day();                                     //161212
    #endif
    // We must have weather available at this point (to enable_evaporation_hourly) //160606RLN


    /*160720 obsolete hourly evaporation is now specified in scenario model options
    // optional enabling of hourly evaportion  soil pond residue.
    // Using false will use daily evaporation for the respective elements.
    // Will eventually be loaded from simulation scenario options
    // (CropSyst proper)
    // For now MicroBasin controls these options with this hard coded line.
    // Roger will implement loading these scenario options when needed.


    // enable_evaporation_hourly is called/reset every day because the specific
    // evaporators in any given day may turn off daily evaporation when
    // there is no potential for evaporation that day.

    // Note that one could potentially have the option to switch between daily
    // and hourly evaporation mode during the run.
    // I.e. fall back to daily during winter time.
    #ifndef DAILY_ET
    started &= enable_evaporation_hourly(true,true,true);                    //160523
    #else
    // The following line would be used to simulate daily  evaporation
    started &= enable_evaporation_hourly(false,false,false);                    //160523
    #endif
    */

    started &= LAND_UNIT_SIM_  start_day();                                       //151208
    #else
    pWeatherPMET->DeterminePMET
       (*pWeatherDaily
       ,geocoordinate.get_latitude_dec_deg()
       ,weather_station_elev                                                     //141008LML
        //RLN why is this not the site elevation? 150630
       ,0.23);
    pSimulation->initializeNewDay();
    if (pSimulation->pSimulationRotation->getNewCropFound()) {
        DestroyCrop();
        NewCrop();                              //M.Liu added Feb 7, 2014
    }
	#endif
   #ifdef MBVB_SNOW
    //calculate snow build-up and melt
    pSoil->pSoilProcesses->DetermineEffectivePrecipitation                       //131210FMS
        (*pWeatherDaily
        #ifdef CROPSYST_VERSION
        ,LAND_UNIT_SIM_ crop_active_or_intercrop ? LAND_UNIT_SIM_ crop_active_or_intercrop->get_fract_canopy_cover() : 0 //150909LML NEED check with Roger!!!
        #else
        ,*pSimulation, *pCrop
        #endif
        );
    #endif
    #ifndef CROPSYST_VERSION
    pWeatherDaily->DetermineRadiationInterceptedbyCropandResidues                //141009FMS
        (
        #ifdef CROPSYST_PROPER_CROP
         pCrop->get_fract_canopy_cover()                                         //131204RLN
        #else
         *pCrop
        #endif
        );                                                                       //141009FMS
    #endif




    //160211LML pSnow->HourlySnowRoutine(*pWeatherDaily,*this,120/*150921LML scenario_control_and_model_options.annual_temperature.phase*/); //131210FMS_150921LML need ask Roger!!!



    //calculate effective precipitation, daily runoff, soil evaporation, and initialize soil temperature profile
    //160623LML #ifdef CROPSYST_VERSION
    //160623LML started &= pSoil->start_day();                                               //141221RLN
    //160623LML #else
    //160623LML pSoil->initializeNewDay(*pSimulation,*pCrop,*pManagement);
    //160623LML #endif

    //160411RLN simply use the pond.get_evaporation_actual() at end of day for output_daily_pond_evaporation_mm =
    //       m_to_mm(pond.evaporate(pSoilProcess->Daily_Soil_Water_Potential_Evaporation_m));

       // WARNING this daily evaporation, Mingliang said evaporation is
       // processed hourly so I this this is redundent don't think this goes here RLN
       // also evaporation should be handled toward end of day?

    //160505LML LAND_UNIT_SIM_ evaporate_pond();                                             //160414

    /*160411RLN obsolete
    #if (defined(CHECK_OVERLANDFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG) || defined(CHECK_HOURLY_CASCADE_FOR_DEBUG))
    double pondevap=0.0;
    output_daily_pond_evaporation_mm = m_to_mm(pond.evaporate(pondevap));
    std::clog<<"POND EVAPERATION IS SET ZERO!!!\n";
    #endif
    */

    #ifndef CROPSYST_VERSION
    #ifndef CROPSYST_PROPER_MANAGEMENT
    pManagement->initializeNewDay(*pSimulation, *pCrop, *pSoil, *pWeatherDaily, Crop_Management_Zone);
    #endif
    #endif


    //161108LML do canopy interception, which happens at daily bases
    float64 non_crop_intercept_precip = meteorology_site.ref_precipitation_liberated().get_m();
    double before_canopy_intercept = non_crop_intercept_precip;
    float64 canopy_intercepted_precipitation_m_today = 0;
    if (crop_active_or_intercrop)
    {  non_crop_intercept_precip = crop_active_or_intercrop->intercept_precipitation(non_crop_intercept_precip);
       canopy_intercepted_precipitation_m_today = crop_active_or_intercrop->
          get_intercepted_precipitation_m();
       //161110LML meteorology_site.ref_precipitation_effective().set_m(non_crop_intercept_precip,simulated_quality);
    }
    none_intercepted_liq_water_m = non_crop_intercept_precip;

    /*if (canopy_intercepted_precipitation_m_today > 1e-6)
    std::clog << "\ttotal_ppt_mm:" << meteorology_site.ref_precipitation_actual().get_mm()
              << "\tbefore_canopy_intercept_liq_water:" << m_to_mm(before_canopy_intercept)
              << "\tcanopy_intercepted_mm:" << m_to_mm(canopy_intercepted_precipitation_m_today)
              << "\tafter_canopy_interception_mm:" << meteorology_site.ref_precipitation_effective().get_mm()
              << std::endl;*/

    return started;                                                              //141221RLN
}
//______________________________________________________________________________
double BasinCellClass::calAlbedo()
{
    return 0.15;       //Implementing later M.Liu
}
//______________________________________________________________________________
bool BasinCellClass::start()                                       modification_
{  bool started = true;
   #ifdef CROPSYST_VERSION
   #ifdef CELL_METEOROLOGY
   //160808 becoming obsolete eventually delete, meterology_site is now owned and started by basin                          //160809
   started &= meteorology_site.start();
   #endif
   started &= LAND_UNIT_SIM_ start();
   #endif
   return started;
}
//_2015-12-12___________________________________________________________________
bool BasinCellClass::start_year()                                                //141221RLN
{   bool started = true;
    #ifdef MBVB_SOIL
    started &= pSoilState->start_year();                                         //160404LML
    #endif
    #ifdef CROPSYST_VERSION
    #ifdef CELL_METEOROLOGY
    //160808 becoming obsolete eventually delete, meteorology_site is owned and started by basin                            //160808
    started &= meteorology_site.start_year();                                    //151212RLN
    #endif
    started &=
       LAND_UNIT_SIM_
       start_year();                                                             //141221RLN
    #endif
    return started;
}
//______________________________________________________________________________
//double BasinCellClass::getSumDownhillSlop() {return sum_downhill_slop;}
//______________________________________________________________________________
bool BasinCellClass::start_hour()                                  modification_
//160724 was initFluxes()
{  bool started = true;
   #ifndef MBVB_SOIL
   started &= soil_MicroBasin->start_hour();                                     //160724RLN
   #endif
    int num_layers = pSoilProfile->NumberOfLayers();
    hourly_flow_m3.initialize();
    for (int layer = 1; layer <= num_layers; ++layer)
        hourly_LateralOutFlowLayer_m3[layer] = 0.0;                              //150127LML
    for (int i = 0; i < ControlRef.getSoluteSpecies(); i++) {
        hourly_flow_solute_kg[i].initialize();
        for (int layer = 1; layer <= num_layers; ++layer){
            hourly_LateralOutFlowSoluteLayer_kg[layer][i] = 0.0;                 //150127LML
        }
    }
   return started;                                                               //160724RLN
}
//_2014-04-18___________________________________________________________________
bool BasinCellClass::runHourlyGridCellProcess(const int hour)
{  bool processed = true;
    //runHourlySoilProcess(today,hour);
    #ifdef CROPSYST_VERSION
    #else
    pSimulation->pTimeState->setHourOfDay(hour);
    #endif
    #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
    float64 fract_canopy_cover = pCrop ? pCrop->get_fract_canopy_cover_total() : 0.0;
    float64 crop_height        = pCrop ? pCrop->get_plant_height_m() : 0.0;//pCrop ? pCrop-> 0.0;   //160217LML talk with roger!!!
    #endif

    // Note that hourly evaporation is optional.
    // If disabled, the following evaporate methods do nothing.
    // Eventually these may moved to CropSyst proper.                            //160523RLN

    // I am not sure if it would make more sense to evaporate
    // before or after HourlySoilProcesses. RLN

    //160616LML calculate residue interception
    double irrig_m = 0.0;                                                        //160616LML check with Roger

    double ponded_water = pond.relinquish_depth();
    double total_available_water_m =
        #ifdef MBVB_SNOW
        mm_to_m(pSnow->Hourly_Rain_mm[hour] + pSnow->Hourly_Snow_Melt_Amount[hour])
        // Snow water is stored and does not become water available
        // for residue and pond storage
        #else
        none_intercepted_liq_water_m / 24.0 //161110LML meteorology_site.ref_precipitation_effective().get_m() / 24.0                 //160728RLN-LML temporal solution!!!
        #endif
          + irrig_m + ponded_water;

    double intercepted_residue = 0;
    if (organic_matter_residues_profile_kg_m2) {
      Residues_interface *local_residue_pools_kg_m2 = organic_matter_residues_profile_kg_m2->mod_residues();
      intercepted_residue = local_residue_pools_kg_m2->water_interception(total_available_water_m);
    }
    total_available_water_m -= intercepted_residue;
    pond.set_depth(total_available_water_m);

    #ifdef CHECK_MASS_BALANCE
    BalanceItem soil_water;
    soil_water.SetInitPool(pond.get_depth() + pSoilState->getTotalSoilWaterContent_m());
    #endif

    //160616LML end
    //160729LML moved after infiltration
    //evaporate_pond_hour(hour);                                                   //160505RLN
    //evaporate_residues_hour(hour);                                               //160505RLN
    //evaporate_soil_hour(hour);                                                   //160505RLN

    //160616LML all rain and snow melt goes to pond and residue. The pond water will be treated for infiltration
    #ifdef MBVB_SOIL
    pSoil->HourlySoilProcesses(
			#ifndef CROPSYST_VERSION
			*pSimulation,
         #endif
         #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
         /*160606RLN  CropSyst handles transipration
         fract_canopy_cover,                                                     //141212
         */
         #ifdef MBVB_SOIL_TEMPERATURE
         crop_height,                                                            //160217LML
         #endif
         #else
			*pCrop,
         #endif
         #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
         #else
			*pManagement,
			#endif
			#ifndef CROPSYST_WEATHER
         //160808 *pWeatherDaily,
         #ifndef CROPSYST_VERSION
         *pSnow,
         #endif
			#endif
         //160812RLN for debugging cell_id
			);
    hourly_flow_m3.Drainage = get_m3_from_m(pSoilState->Hourly_Drainage_m);
    //170417LML added for hourly outputs on leached N
#if (defined(CROPSYST_CHEMICAL_TRANSPORT) && defined(CROPSYST_VERSION))
    hourly_flow_solute_kg[SL_Ammonia].Drainage = getTotalMassFromMassPerSquireMeter(pSoilState->Hourly_balance_leached_NH4_N * N_to_NH4_conv);
    hourly_flow_solute_kg[SL_Nitrate].Drainage = getTotalMassFromMassPerSquireMeter(pSoilState->Hourly_balance_leached_NO3_N * N_to_NO3_conv);
#endif

    //160729LML moved after infiltration
    double pond_evap = evaporate_pond_hour(hour);                                                   //160505RLN
    double resid_evap = evaporate_residues_hour(hour);                                               //160505RLN
    double soil_evap = evaporate_soil_hour(hour);                                                   //160505RLN

    /*if ((pond_evap + resid_evap + soil_evap ) > 1e-5) {
        std::clog   << "cell:" << cell_ID.code
                    << "\thour:" << (int)hour
                    << "\tintercep_residue_mm:" << m_to_mm(intercepted_residue)
                    << "\tpond_evap_mm:" << pond_evap
                    << "\tresid_evap_mm:" << resid_evap
                    << "\tsoil_evap_mm:" << soil_evap
                    << "\n";
    }*/


   #else
    processed &= soil_MicroBasin->process_hour();                                //160724
    hourly_flow_m3.Drainage = get_m3_from_m(soil_MicroBasin->drainage_hourly);   //160724
   #endif

    #ifdef CHECK_MASS_BALANCE
    soil_water.AddFluxOut(pond_evap);
    soil_water.AddFluxOut(soil_evap);
    soil_water.AddFluxOut(pSoilState->Hourly_Drainage_m);
    soil_water.SetFinalPool(pond.get_depth() + pSoilState->getTotalSoilWaterContent_m());
    if (!soil_water.IsMassBalance(1e-4)) {
        soil_water.PrintMassBalanceTerms("Soilbalance error in runHourlyGridCellProcess!!!");
        //exit(0);
    }
    #endif

   //return processed;
}
//______________________________________________________________________________
bool BasinCellClass::process_day()                                 modification_ //150611RLN
{  bool processed = true;                                                        //141221
    //run daily soil processes
    /*std::clog<<"(before DailySoilProcesses) "
            <<" Layer_Nitrate_N_Mass:"<<pSoilState->Layer_Nitrate_N_Mass[1]
               <<std::endl;*/
   #ifdef MBVB_SOIL
    pSoil->DailySoilProcesses
					#ifdef CROPSYST_VERSION
					();
					#else
					(*pWeatherDaily, *pSimulation, *pCrop, *pDebugState);
					#endif
   #else
     // LBF::process_day handles soil processing                                 //160724
   #endif
    #if defined(CROPSYST_VERSION)
    /*170424LML has water balance error at the harvest day (might be related to crop_active_or_intercrop)
    #ifdef CHECK_MASS_BALANCE
    BalanceItem soilwater;                                                       //and canopy water storage
    soilwater.SetInitPool(pSoilState->getTotalSoilWaterContent_m());
    #endif */

    #ifndef CLOSE_CROPSYST_CROP_AND_SOIL_BIOGEOCHEMICAL_PROCESS_FOR_DEBUG
    processed &=
       LAND_UNIT_SIM_
          process_day();                                                         //150611RLN_141221

    /*170424LML has water balance error at the harvest day (might be related to crop_active_or_intercrop)
    #ifdef CHECK_MASS_BALANCE
    soilwater.SetFinalPool(pSoilState->getTotalSoilWaterContent_m());
    double wateruptake = crop_active_or_intercrop ? crop_active_or_intercrop->get_act_uptake_m() : 0; //only water uptake from soil
    soilwater.AddFluxOut(wateruptake);
    if (!soilwater.IsMassBalance(1e-6)) {
        soilwater.PrintMassBalanceTerms("BasinCellClass::process_day() water balance errpr");
        //exit(0);
    }
    #endif */
    LAND_UNIT_SIM_ perform_triggered_synchronizations_today();                   //150818RLN
    //150812 UpdateSoilState was only copying soil chemicals which CropSyst proper maintains
    // pSoil->pSoilState->UpdateSoilState();
    /*160115LML should not be here. Talk to Roger!!!
    processed &=
          //151208 CropSyst::Land_unit_simulation::
          LAND_UNIT_SIM_
          end_day();                                                             //141221
    */
    #endif
    #else
    //Start or continue with crop
    if (pSimulation->pSimulationRotation->getCropExist()) {
        #ifndef CROPSYST_PROPER_CROP
        pCrop->PerformDailyProcesses(*pSoil, *pWeatherDaily, *pSimulation, *pManagement);
        #endif
        //LML 140822 pSimulation->pTimeState->setDaysAfterPlanting(pSimulation->pTimeState->getDaysAfterPlanting() + 1);
    } else {
        pSoilState->Surface_Soil_Cover = SSC_Default;                            //141014LML
    }
    #ifndef CROPSYST_VERSION
    //150812 UpdateSoilState was only copying soil chemicals which CropSyst proper maintains
    pSoil->pSoilState->UpdateSoilState();
    #endif
    //RLN The following is actually end_day() processing
    pSimulation->pBalance->CalculateDailySoilBalances();
    pSimulation->pBalance->CalculateDailyOrganicResidueBalance();
    //Write soil outputs
    if (ControlRef.bWrite_Daily_Output) {
        pSimulation->pOutput->WriteDailySoilCropOutput(*pSimulation,*pSoil,*pWeatherDaily,*pCrop);
    }
    if (ControlRef.bWrite_Growth_Daily_Output && pSimulation->pSimulationRotation->getCropExist()) {
        pSimulation->pOutput->WriteDailyGrowthOutput(*pSimulation,*pCrop);
    }
    /* 141221RLN moved to end_year()
    //Check if new year, if yes write annual output
    if (rdate.is_last_DOY() || (rdate == ControlRef.getEndDate())) {
        if (ControlRef.bWrite_Annual_Output) pSimulation->pOutput->WriteAnnualSoilOutput(*pSimulation,*pSoil);
    }
    */
    //LML 140822 moved to the end of day
    if (pSimulation->pSimulationRotation->getCropExist()) {
        pSimulation->pTimeState->setDaysAfterPlanting(pSimulation->pTimeState->getDaysAfterPlanting() + 1);
    }
    //M.Liu moved to the last
    if (pSimulation->pSimulationRotation->getCropTerminated()) {
        //Destroy crop object when harvest is reached
        DestroyCrop();
        pSimulation->pSimulationRotation->setCropExist(false);
        pSimulation->pSimulationRotation->setCropTerminated(false);
        pSimulation->pTimeState->setDaysAfterCropExists(0);
    }
    #endif
    #ifdef VB_SAME_CSV_OUTPUT
    /*160322LML moved to end_day()
    //Write soil outputs
    if (ControlRef.bWrite_Daily_Output && debug_output) {
        #ifndef CROPSYST_VERSION
        pSimulation->
        #endif
        pOutput->WriteDailySoilCropOutput(LAND_UNIT_SIM_ ref_today());           //151208RLN
    }
    */
    //output_harvested_yield = per_m2_to_per_ha (kg_to_tonne(crop_active_or_intercrop ? crop_active_or_intercrop->get_latest_yield_kg_m2() : 0.0));  //160322LML

    if (ControlRef.bWrite_Growth_Daily_Output && debug_output &&
        #ifdef CROPSYST_VERSION
        LAND_UNIT_SIM_ crop_active_or_intercrop
        #else
        pSimulation->pSimulationRotation->getCropExist()
        #endif
        ) {
        #ifndef CROPSYST_VERSION
        pSimulation->
        #endif
        pOutput->WriteDailyGrowthOutput();
    }
    #endif
    return processed;
}
//150921LML_____________________________________________________________________
bool BasinCellClass::end_day()                                     modification_
{
    //soil->act_evaporation = pSoilState->Daily_Soil_Water_Actual_Evaporation_m;   //160119LML
    bool ended = LAND_UNIT_SIM_ end_day();                                       //150921
    double transpiration = LAND_UNIT_SIM_ crop_active_or_intercrop ? LAND_UNIT_SIM_ crop_active_or_intercrop->get_act_transpiration_m() : 0;
    #ifdef MBVB_SOIL
    double evaporation_m = ref_soil()->get_act_evaporation() + pond.get_evaporation_actual_day() + (organic_matter_residues_profile_kg_m2 ? organic_matter_residues_profile_kg_m2->ref_residues()->get_act_evaporation() : 0.0); //161014LML
    pSoilState->Cumulative_Actual_Crop_Transpiration_m += transpiration;
    pSoilState->Cumulative_Actual_Soil_Evaporation_m   +=  evaporation_m;//161014LML pSoilState->Daily_Soil_Water_Actual_Evaporation_m;
    pSoilState->Cumulative_Drainage_m                  += pSoilState->Daily_Drainage_m;
    pSoilState->Cumulative_Irrigation_m                += pSoilState->Daily_Irrigation_m;
    pSoilState->Annual_Actual_Crop_Transpiration_m     += transpiration;
    pSoilState->Annual_Actual_Soil_Evaporation_m       += evaporation_m;
    pSoilState->Annual_Precipitation_m                 += LAND_UNIT_SIM_ meteorology.ref_precipitation_actual().get_m(); //161101LML
    pSoilState->Annual_Drainage_m                      += pSoilState->Daily_Drainage_m;
    pSoilState->Annual_Irrigation_m                    += pSoilState->Daily_Irrigation_m;
    pSoilState->Annual_Ammonium_N_Fertilization        += nitrogen_daily_output.applied_inorganic_NH4_N;
    pSoilState->Annual_Nitrate_N_Fertilization         += nitrogen_daily_output.applied_inorganic_NO3_N;
    pSoilState->Annual_Organic_N_Fertilization         += nitrogen_daily_output.applied_organic;

    Soil_chemicals_profile *soil_chemicals = LAND_UNIT_SIM_ get_soil_chemicals();
    double NH4_N_leached = 0;
    double NO3_N_leached = 0;
    if (soil_chemicals)                                                          //151208RLN
    {
#ifndef CROPSYST_CHEMICAL_TRANSPORT
        pSoilState->Annual_Ammonium_Leaching               += pSoilState->Daily_Ammonium_Leaching;
        pSoilState->Annual_Nitrate_Leaching                += pSoilState->Daily_Nitrate_Leaching;
        if (crop_active_or_intercrop)
          pSoilState->growth_season_N_leached += pSoilState->Daily_Ammonium_Leaching + pSoilState->Daily_Nitrate_Leaching;  //170207LML
#else
        NH4_N_leached = soil_chemicals->NH4->balance_leached_molecular * NH4_to_N_conv;
        NO3_N_leached = soil_chemicals->NO3->balance_leached_molecular * NO3_to_N_conv;
        pSoilState->Annual_Ammonium_Leaching               += NH4_N_leached;
        pSoilState->Annual_Nitrate_Leaching                += NO3_N_leached;
        if (crop_active_or_intercrop) {
          //pSoilState->growth_season_N_leached += NH4_N_leached + NO3_N_leached;
          pSoilState->growth_season_N_uptake  += crop_active_or_intercrop->get_nitrogen()->get_daily_uptake();
        }
#endif
        pSoilState->Annual_Nitrification   += soil_chemicals->nitrification_N_E_output[0];   //(kgN/ha)
        pSoilState->Annual_Denitrification += soil_chemicals->denitrification_N_E_output[0]; //(kgN/ha)
        if (crop_active_or_intercrop) {
            pSoilState->Annual_N_uptake += crop_active_or_intercrop->get_nitrogen()->get_daily_uptake();
            if (crop_active_or_intercrop->ref_phenology().get_initiation_date(NGS_PLANTING) == today) {
                report_planting_date_soil_profile_NH4_N = per_m2_to_per_ha (soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //170410LML
                report_planting_date_soil_profile_NO3_N = per_m2_to_per_ha (soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true)); //170410LML
                report_planting_date_surface_NH4_N      = per_m2_to_per_ha (soil_chemicals->NH4->get_surface_mass() * NH4_to_N_conv); //170510LML
                report_planting_date_surface_NO3_N      = per_m2_to_per_ha (soil_chemicals->NO3->get_surface_mass() * NO3_to_N_conv); //170510LML
            }
        }
        if (today.get_DOY() == 1) {
          report_Initial_Profile_NO3_N = per_m2_to_per_ha (soil_chemicals->sum_NO3_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true));
          report_Initial_Profile_NH4_N = per_m2_to_per_ha (soil_chemicals->sum_NH4_to_depth(ENTIRE_PROFILE_DEPTH_as_9999,true));
          report_Initial_Surface_NH4_N = per_m2_to_per_ha (soil_chemicals->NH4->get_surface_mass() * NH4_to_N_conv); //170510LML
          report_Initial_Surface_NO3_N = per_m2_to_per_ha (soil_chemicals->NO3->get_surface_mass() * NO3_to_N_conv); //170510LML
        }
    }
    #ifdef CROPSYST_CHEMICAL_TRANSPORT
    //170413LML Soil_chemicals_profile *soil_chemicals = get_soil_chemicals();               //160323RLN
    if (soil_chemicals)
    {
        pSoilState->Cumulative_Nitrate_Leaching            += NO3_N_leached; //160323RLN
        pSoilState->Cumulative_Ammonium_Leaching           += NH4_N_leached; //160323RLN
    // NYI pSoilState->Cumulative_Phosphorus_Leaching         += soil_chemicals->NH4->balance_leached_molecular * NH4_to_N_conv;
    }
    #else
    pSoilState->Cumulative_Nitrate_Leaching            += pSoilState->Daily_Nitrate_Leaching;
    pSoilState->Cumulative_Ammonium_Leaching           += pSoilState->Daily_Ammonium_Leaching;
    pSoilState->Cumulative_Phosphorus_Leaching         += pSoilState->Daily_Phosphorus_Leaching;
    #endif
    //std::clog<<"BasinCell::end_day::drainage:"<<output_flow_m3[TACUM_DAILY].Drainage<<std::endl;
    //150921LML Need talk with Roger ...
    //160322LML moved from process_day()
    //Write soil outputs
    #else
    // CropSyst already provides accumulators
    #endif

    if (ControlRef.bWrite_Daily_Output && debug_output) {
        #ifndef CROPSYST_VERSION
        pSimulation->
        #endif
        pOutput->WriteDailySoilCropOutput(LAND_UNIT_SIM_ ref_today());           //151208RLN
    }
    return ended;
}
//______________________________________________________________________________
bool BasinCellClass::end_year()                                    modification_
{   bool ended = true;                                                           //151212RLN
    #ifdef VB_SAME_CSV_OUTPUT
    if(ControlRef.bWrite_Annual_Output)
      #ifndef CROPSYST_VERSION
      pSimulation->
      #endif
      pOutput->WriteAnnualSoilOutput();
    #endif
    #ifdef CROPSYST_VERSION
    #ifdef CELL_METEOROLOGY
    //160808 becoming obsolete eventually delete, meteorology_site is now owned and ended by basin                              //160808
    ended &= meteorology_site.end_year();                                        //151212
    #endif
    ended &= //151208 CropSyst::Land_unit_simulation::
          LAND_UNIT_SIM_ end_year();
    #endif
    return ended;                                                                //151212RLN
}
//_2014-12-21_RLN______________________________________________________________/
bool BasinCellClass::end_growing_season
   #if ((REACCH_VERSION==2) || (CS_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
   (CropSyst::Crop_interfaced &active_crop)  // when this becomes permanent rename to crop_ending_its_season //130716
   #else
   ()                                                                            //070227
   #endif
{
    output_harvested_yield = per_m2_to_per_ha(kg_to_tonne(crop_at_end_season ? crop_at_end_season->get_latest_yield_kg_m2() : 0)); //160322LML
    if(ControlRef.bWrite_Growth_Season_Output && debug_output) {
        pOutput->WriteGrowingSeasonOutput();
        //std::clog<<"Write growing season outputs ID:"<<getCellId()<<std::endl;
    }
    report_planting_date_soil_profile_NH4_N = 0;                                 //170410LML
    report_planting_date_soil_profile_NO3_N = 0;                                 //170410LML
    return LAND_UNIT_SIM_ end_growing_season
            #if ((REACCH_VERSION==2) || (CS_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
            (active_crop);  // when this becomes permanent rename to crop_ending_its_season //130716
            #else
            ();                                                                  //070227
            #endif
}
//_2016-01-13_RLN______________________________________________________________/
void BasinCellClass::setInnerId(long innerID){inner_id_basin = innerID;}
long BasinCellClass::getInnerID(){return(inner_id_basin);}
void BasinCellClass::setFlowDir(int flowdir) {fdir = flowdir;}
int BasinCellClass::getFlowDir() {return fdir;}
void BasinCellClass::setCol(int _col) {col = _col;}
int BasinCellClass::getCol() {return col;}
void BasinCellClass::setRow(int _row) {row = _row;}
int BasinCellClass::getRow() {return row;}
/*150630
void BasinCellClass::setElev(double _elev) {elev = _elev;}
double BasinCellClass::getElev() {return elev;}
*/
void BasinCellClass::setElev(double _elev) { geocoordinate.set_elevation_meter(_elev);} //150630RLN
double BasinCellClass::getElev() {return geocoordinate.get_elevation();}         //150630RLN

void BasinCellClass::setSlop(double _slop) {slop = _slop;}
double BasinCellClass::getSlop() {return slop;}
void BasinCellClass::setArea(double _area) {area_m2 = _area;}
double BasinCellClass::getArea() {return area_m2;}
void BasinCellClass::setLength(double _length) {length = _length;}
double BasinCellClass::getLength() {return length;}
double BasinCellClass::getFlowPortion(int nb) {return flow_portion[nb];}
void BasinCellClass::setFlowPortion(int nb,double portion) {
    flow_portion[nb] = portion;
}
void BasinCellClass::setHydroStandardslope(double _hydroslop) {
    vHydroStandardslope = _hydroslop;
}
double BasinCellClass::getHydroStandardslope() {return vHydroStandardslope;}
//______________________________________________________________________________
int BasinCellClass::getSoilLayers()
{return
   pSoilProfile->NumberOfLayers();                                               //140526
}
//______________________________________________________________________________
double BasinCellClass::getSlopNB(int nb) {return slop_nb[nb];}
void BasinCellClass::setSlopNB(int nb,double _slop) {slop_nb[nb] = _slop;}

double BasinCellClass::getCellBedslopeX() {return CellBedslope_X;}
double BasinCellClass::getCellBedslopeY() {return CellBedslope_Y;}
void BasinCellClass::setCellBedslopeX(double X) {CellBedslope_X = X;}
void BasinCellClass::setCellBedslopeY(double X) {CellBedslope_Y = X;}
//______________________________________________________________________________
BasinCellClass::~BasinCellClass()
{
#ifdef Destruct_Monitor
    std::clog<<"~BasinCellClass:"<<cell_id<<std::endl;
#endif
    #ifdef CROPSYST_WEATHER
    // There is now no weather specific to cell (meteorology_site is now provided by Basin)
    #else
    #ifdef CELL_METEOROLOGY
    delete pWeatherDaily;
    #endif
    #endif
    #ifdef CROPSYST_VERSION
    //151222 now given delete LAND_UNIT_SIM_ meteorology_site.weather_provider;       //151206_150730RLN
    #else
    delete pWeatherPMET;
    delete pDebugState;
    delete pCrop;
	#endif
   #ifdef MBVB_SOIL
    delete pSoil;
    delete pSoilProcess;
   #endif
    #ifndef CROPSYST_VERSION
    delete pSimulation;
    #endif
   #ifdef MBVB_SNOW
    delete pSnow;
   #endif
	#ifndef CROPSYST_VERSION
    delete pManagement; //M.Liu
	#endif
   #ifdef MBVB_SOIL
    delete pSoilState;
   #else
    delete soil_tallies;                                                         //160722RLN
   #endif
   #ifdef Destruct_Monitor
    std::clog<<"~BasinCellClass done "<<cell_id<<std::endl;
   #endif
}
//______________________________________________________________________________
int BasinCellClass::getSoilID() {return soilID;}
void BasinCellClass::setSoilID(int _soilID) {soilID = _soilID;}
double BasinCellClass::get_m3_from_m(const double flow_m)
{
    return flow_m * area_m2;
}
//______________________________________________________________________________
void BasinCellClass::sumDailyFlow()
{
    //Summarize daily flow from hourly data
    /*
    int dayofyear = date.get_DOY() - 1;    //0-365

    for (int hour = 0; hour < 24; hour ++) {
        if (hour == 0) {
            hourlySurfaceInFlow_m3[dayofyear][24] = 0;
            hourlySurfaceOutFlow_m3[dayofyear][24] = 0;
            hourlyDrainage_m3[dayofyear][24] = 0;
            hourlyLateralInFlow_m3[dayofyear][24] = 0;
            hourlyLateralOutFlow_m3[dayofyear][24] = 0;
            hourlyLateralUpFlow_m3[dayofyear][24] = 0;
            //totalSoilWaterContent_mm[dayofyear][24] = 0;
        }
        hourlySurfaceInFlow_m3[dayofyear][24] +=
                hourlySurfaceInFlow_m3[dayofyear][hour];
        hourlySurfaceOutFlow_m3[dayofyear][24] +=
                hourlySurfaceOutFlow_m3[dayofyear][hour];
        hourlyDrainage_m3[dayofyear][24] +=
                hourlyDrainage_m3[dayofyear][hour];
        hourlyLateralInFlow_m3[dayofyear][24] +=
                hourlyLateralInFlow_m3[dayofyear][hour];
        hourlyLateralOutFlow_m3[dayofyear][24] +=
                hourlyLateralOutFlow_m3[dayofyear][hour];
        hourlyLateralUpFlow_m3[dayofyear][24] +=
                hourlyLateralUpFlow_m3[dayofyear][hour];
        //totalSoilWaterContent_mm[dayofyear][24] +=
                //totalSoilWaterContent_mm[dayofyear][hour]/24;
    }
    */
}
//______________________________________________________________________________
double BasinCellClass::getLatitude() {return geocoordinate.get_latitude_dec_deg();}   //141222RLN
double BasinCellClass::getLongitude(){return geocoordinate.get_longitude_dec_deg();}  //141222RLN
double BasinCellClass::getAspect(){return(aspect);}
void BasinCellClass::setAspect(double _aspect){aspect = _aspect;}

int BasinCellClass::getNeighborIndex(int nb) {return neighbor_idindex[nb];}
void BasinCellClass::setNeighborIndex(int nb, int index) {neighbor_idindex[nb] = index;}
//______________________________________________________________________________
#ifndef CROPSYST_VERSION
void BasinCellClass::NewCrop()
{
    #ifndef CROPSYST_PROPER_CROP
    //pCrop = new clsCrop(ControlRef);
    pCrop->NewCrop(*pSimulation);
    pCrop->initialize(*pSimulation,*pWeatherDaily,*pSoil);
    pSoilState->ClearMaintenanceFluxes();                       //LML 140903
    #endif
}
#endif
//______________________________________________________________________________
bool BasinCellClass::initialize()                                  modification_ //141221RLN
{   bool initialized = true;                                                     //141221RLN
    #ifdef CROPSYST_VERSION
    std::wstring soil_state_ID;
    //#pragma omp critical
    //{
    CORN::append_nat32_to_wstring((nat32)soilID, soil_state_ID);
    CORN::OS::File_name_concrete soil_state_filename(database_directory.Soil(),soil_state_ID,L"SoilState");

    CropSyst::Scenario &scenario_control_and_model_options =                     //160406
          LAND_UNIT_SIM_ scenario_control_and_model_options;
    #ifdef MBVB_SOIL
    pSoil->initialize_parameters(soil_state_filename
        #ifdef CROPSYST_VERSION
        ,scenario_control_and_model_options                                      //160406
        //160406 ,LAND_UNIT_SIM_ scenario_control_and_model_options
        #endif
        );                                                                       //150724RLN
    LAND_UNIT_SIM_ soil = pSoil;                                                 //150724RLN
    #endif
    //160113LML initialized &= /*150811LML CropSyst::Land_unit_simulation::*/setup_soil();   //151208_141221RLN
    //160113RLN   LAND_UNIT_SIM_ initialize_soil();                                          //151208
    // continue here need to set CropSyst::Land_unit_simulation:: to soil
    char rot_ID_string[20];                                                      //150812RLN
    CORN::int32_to_cstr((int32)crop_rotation_id,rot_ID_string,10);               //150812RLN
    CORN::OS::File_name_concrete composed_rotation_filename                      //150812RLN
        (database_directory.Rotation(),rot_ID_string,"rot");                     //150812RLN
    //160317LML #pragma omp critical
    //160317LML {
    LAND_UNIT_SIM_ scenario_control_and_model_options.rotation_filename.set_DEN(composed_rotation_filename); //150812RLN
    LAND_UNIT_SIM_ scenario_control_and_model_options.cropping_system_mode_labeled.set(rotation_cropping_system); //150812RLN
    /*160317LML
    for (int layer = 0; layer <= pSoilProfile->NumberOfLayers(); layer++)
    {
        #ifndef CROPSYST_VERSION
      LAND_UNIT_SIM_ scenario_control_and_model_options.horizon_N_NO3[layer] =
              pSoilState->Layer_Nitrate_N_Mass[layer];
      LAND_UNIT_SIM_ scenario_control_and_model_options.horizon_N_NH4[layer] =
              pSoilState->Layer_Ammonium_N_Mass[layer];
        #endif
    }
    */
    //160317LML initialized &= meteorology_site.initialize();                                //151212
//    #ifdef __linux__
//    initialized = /*CropSyst::Land_unit_simulation::*/initialize_linux();
//    #else
    initialized &= CropSyst::Land_unit_simulation::initialize();                 //141221RLN
//    #endif

      // Actually solar_irradiance_extraterrestrial_day.start should go
      // in a start() method.

    #else
    initialized &= pSimulation->initialize();                                    //141221RLN
    pSoil->initialize_parameters(soilID,*pSimulation);                           //150724RLN
    #endif

   #ifdef LIU_DEBUG
    //std::clog<<"psoil initialized."<<std::endl;
   #endif
   #ifndef CROPSYST_VERSION
   initialized &= pSnow->initialize();                                           //141221RLN
   #endif
   #ifdef LIU_DEBUG
    //std::clog<<"pSnow initialized."<<std::endl;
   #endif
   return initialized;                                                           //141221RLN
}
//______________________________________________________________________________
std::string BasinCellClass::getSoilStringID()
{
    return "soilid";   //Implement later M.Liu Feb 5, 2014
}
//______________________________________________________________________________
void BasinCellClass::Flows::initialize()
{
    SurfaceOut  = 0;
    SurfaceIn   = 0;
    Drainage    = 0;
    LateralIn   = 0;
    LateralOut  = 0;
    LateralUp   = 0;
}
//______________________________________________________________________________
void BasinCellClass::Flows::add(const Flows &flow)
{
    SurfaceOut  += flow.SurfaceOut;
    SurfaceIn   += flow.SurfaceIn;
    Drainage    += flow.Drainage;
    LateralIn   += flow.LateralIn;
    LateralOut  += flow.LateralOut;
    LateralUp   += flow.LateralUp;
}
//_150910LML____________________________________________________________________
void BasinCellClass::accum_hourly_outflow()
{
    //Accumulate outflow from hourly data
    for (int accum = 0; accum < TACUM_COUNT; accum++) {
        output_flow_m3[accum].add(hourly_flow_m3);
        for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
            output_flow_solute_kg[s][accum].add(hourly_flow_solute_kg[s]);
        }
    }
}
//_150910LML____________________________________________________________________
void BasinCellClass::init_accumulater_outflow(const TIME_ACCUMULATOR time_acum)
{
    output_flow_m3[time_acum].initialize();
    for (int s = 0; s < ControlRef.getSoluteSpecies(); s++) {
        output_flow_solute_kg[s][time_acum].initialize();
    }
}
//______________________________________________________________________________
#ifdef CROPSYST_VERSION
bool BasinCellClass::load_soil()
{
   #ifndef MBVB_SOIL
   soil = soil_MicroBasin = new MicroBasin::Soil;
   #endif
   return true;
}
//_2016-07-24___________________________________________________________________
bool BasinCellClass::setup_soil()  //obs 160113LML
{
   // NYI
   return true;
}
//_2014-12-12_RLN______________________________________________________________/
const OS::Directory_name &BasinCellClass::get_output_directory_name()      const
{
   return output_directory_name;
}
//_2014-12-12_RLN______________________________________________________________/
Common_operation *BasinCellClass::get_operation
      (const char                   *operation_type_str
      ,const std::string            &operation_ID  // filename may be updated with qualification so not const
      ,modifiable_ CORN::OS::File_name   &operation_filename    // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32       resource_set_ID,  bool &relinquish_op_to_event)
{   return 0;  //NYI
}
//_2014-12-12_RLN______________________________________________________________/
const Air_temperature_average &BasinCellClass::ref_air_temperature_avg()   const
{
   #ifdef CROPSYST_VERSION
   assert(false); // NYI WARNING need to get from meteorology_site
   #else
   return pWeatherDaily->daily_provider.air_temperature_avg;
   #endif
}
const Wind_speed              &BasinCellClass::ref_wind_speed()            const
{
   #ifdef CROPSYST_VERSION
   assert(false); // NYI WARNING need to get from meteorology_site
   #else
   return pWeatherDaily->daily_provider.wind_speed;
   #endif
}
//_2015-07-24__________________________________________________________________/
#else
void BasinCellClass::DestroyCrop()
{
    //When new crop is found, the old crop object will be destroyed ::
    //M.Liu: Implement Later Feb 7, 2014
    #ifndef CROPSYST_PROPER_CROP
    pCrop->ClearStateForNextCropSeason();
    #endif
}
//_____________________________________________________________________________/
#endif
//170404LML #ifdef PREDEFINE_N_APPLICATION_PER_CELL
Event_status_indicator BasinCellClass::perform_start_automatic_N_application_mode
   (CropSyst::N_application_soil_observation_mode_class  &auto_N_mode_op)
{  //170321LML revised from its parent class
    Soil_chemicals_profile  *soil_chemicals = get_soil_chemicals();  // may return 0 if not soil and/or no soil chemicals. //060803
    std::string active_management_name = auto_N_mode_op.common_operation_filename;
    const std::string varname_targetN("target_yield_N_uptake");                  //170403LML
    const std::string varname_mineralization("estimated_mineralization");        //170403LML
       total_N_application_kg_m2 = 0.0;
       if (soil_chemicals)
       {
          //default situation (if auto_N_grid_option not defined, or the crop auto N gridded data is not set):
          float64 sampling_depth = auto_N_mode_op.soil_N_sampling_depth;
          total_N_application_kg_m2
                   = auto_N_mode_op.determine_total_automatic_N_application
                       ( soil_chemicals->sum_NO3_to_depth(sampling_depth,true)
                        +soil_chemicals->sum_NH4_to_depth(sampling_depth,true)
                       ,auto_N_mode_op.estimated_mineralization_kg_ha);

          Auto_N_grid_option auto_N_option = ControlRef.auto_N_grid_option.get();
          switch (auto_N_option) {
            case AUTO_N_GRID_FIXED:
              {
                int crop_index = getPredefinedNFertilizationCropIndex(active_management_name);
                //if (crop_index != -1)
                //  total_N_application_kg_m2 = per_ha_to_per_m2(N_applied_predefined_kgN_per_ha[crop_index]);


                /*std::clog << "fixed_cellid:" << cell_ID.code << "\ttarget_yieldN:" << auto_N_mode_op.target_yield_N_uptake_kg_ha
                          << "\tminN:" << auto_N_mode_op.estimated_mineralization_kg_ha
                          << "\tapplied:" << total_N_application_kg_m2 * 10000.0
                          << "\teff:"  << auto_N_mode_op.fertilizer_use_efficiency
                          << "\tinitN:" << (soil_chemicals->sum_NO3_to_depth(sampling_depth,true)
                             +soil_chemicals->sum_NH4_to_depth(sampling_depth,true)) * 10000.0
                          << std::endl;*/


              }
              break;
            case AUTO_N_GRID_VARIED:
              {
                const std::string targetN_head_name = active_management_name + ":" + varname_targetN;
                const std::string mineralization_head_name = active_management_name + ":" + varname_mineralization;
                int targetN_index = getPredefinedNFertilizationCropIndex(targetN_head_name);
                int mineralization_index = getPredefinedNFertilizationCropIndex(mineralization_head_name);
                if ((targetN_index != -1) && (mineralization_index != -1)) {
                  #pragma omp critical
                  {
                  double original_target_yield_N = auto_N_mode_op.target_yield_N_uptake_kg_ha;
                  auto_N_mode_op.target_yield_N_uptake_kg_ha = N_applied_predefined_kgN_per_ha[targetN_index];
                  total_N_application_kg_m2
                           = auto_N_mode_op.determine_total_automatic_N_application
                               ( soil_chemicals->sum_NO3_to_depth(sampling_depth,true)
                                +soil_chemicals->sum_NH4_to_depth(sampling_depth,true)
                               ,N_applied_predefined_kgN_per_ha[mineralization_index]);


                  /*std::clog << "cellid:" << cell_ID.code << "\ttarget_yieldN:" << auto_N_mode_op.target_yield_N_uptake_kg_ha
                            << "\tminN:" << N_applied_predefined_kgN_per_ha[mineralization_index]
                            << "\tapplied:" << total_N_application_kg_m2 * 10000.0
                            << "\teff:"  << auto_N_mode_op.fertilizer_use_efficiency
                            << "\tinitN:" << (soil_chemicals->sum_NO3_to_depth(sampling_depth,true)
                               +soil_chemicals->sum_NH4_to_depth(sampling_depth,true)) * 10000.0
                            << std::endl;*/

                  auto_N_mode_op.target_yield_N_uptake_kg_ha = original_target_yield_N;
                  }
                }
              }  //AUTO_N_GRID_VARIED
              break;
          } //auto_N_option
          auto_N_mode_op.total_N_application_kg_m2 = total_N_application_kg_m2;
       }

       // we now also allow user to split application in local calib mode|| (automatic_nitrogen_mode == AUTO_NITRO_LOCAL_CALIBRATION) //011119
       if (!auto_N_mode_op.split_applications)                                       //020511
       {  // Apply everything now (sampling date or planting)
          // just make the application (we can't schedule it for today)
          // because we've already queued up today's events.                         //160328

          // actually just make the application without queue the event.
          CropSyst::N_application_soil_observation_mode::Split_application auto_N_appl         //160328
          =  CropSyst::N_application_soil_observation_mode::Split_application(total_N_application_kg_m2 ); //160328
          curr_N_application_soil_observation_mode = &auto_N_mode_op;                //161009
          //170217 unused Event_status_indicator status =
          perform_automatic_N_application(auto_N_appl); //160328
       }
       curr_N_application_soil_observation_mode = &auto_N_mode_op;                   //060804
       return ES_START;                                                              //000526
}
//_17-03-21LML_________________________________________________________________/
int BasinCellClass::getPredefinedNFertilizationCropIndex(const std::string &cropname)
{
    int index = -1;
    for (int i = 0; i < N_applied_predefined_crop_name.size(); i++) {
        if (cropname == N_applied_predefined_crop_name[i]) {
            index = i;
            break;
        }
    }
    return index;
}
//_17-03-21LML_________________________________________________________________/
bool BasinCellClass::setPredefinedNFertilization(const std::vector<double> &N_applied, const std::vector<std::string> &crop_name)
{
    N_applied_predefined_kgN_per_ha = N_applied;
    N_applied_predefined_crop_name = crop_name;
    return true;
}
//_17-03-21LML_________________________________________________________________/
//170404LML #endif
