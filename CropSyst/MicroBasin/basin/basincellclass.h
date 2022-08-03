#ifndef basincellclassH
#define basincellclassH
#define LAND_UNIT_SIM_AS_SUPERCLASS
//#include "datetime/date.hpp"
#ifdef MBVB_SOIL
#  include "soil/soilprocessesclass.h"
#  ifdef MBVB_INFILTRATION
#     include "soil/soilprofileclass2.h"
#  endif
#else
#  include "soil/soil_MicroBasin.h"
#  include "soil/soil_properties_sublayers.h"
#endif
#  include "soil/soilstateclass.h"
#ifdef CROPSYST_VERSION
#  include "pond.h"
#  include "solar/irradiance_extraterrestrial.h"
#  include "CS_suite/file_system/CS_database_directory.h"
#  include "crop/crop_interfaced.h"
#  include "CropSyst/source/rot_param.h"
#endif
#ifdef CHEMICAL_TRANSPORT
# ifdef MBVB_SOIL
#  include "soil/soilchemicaltransportclass.h"
# endif
#endif
#ifdef CROPSYST_WEATHER
//160808 class Weather;
#else
#   include "weather/weatherstatedailyclass.h"
#ifndef CROPSYST_VERSION
#   include "snow/clssnow.h"
#endif
#endif
#include <list>
#ifdef CROPSYST_VERSION
//#include "land_unit_sim.h"
#include "land_unit_output.h"
#else
#include "management/clsmanagement.h"
#ifndef CROPSYST_PROPER_CROP
#include "crop/clscrop.h"
#endif
#include "control/debugstateclass.h"
#endif
#ifdef MBVB_SOIL
#  include "soil/clssoil.h"
#endif
#include "pond.h"
#include "soil/runoff.h"
#include <vector>
//______________________________________________________________________________
class WeatherStateDailyClass;
class clsSnow;
class SoilProcessesClass;
class OutputMainClass;                                                           //151002LML
#ifdef CROPSYST_PROPER_CROP
namespace CropSyst
{
   interface_ Crop_interfaced;
}
#else
class clsCrop;
#endif
//______________________________________________________________________________
#ifdef CELL_METEOROLOGY
#include "solar/irradiance_extraterrestrial.h"
#endif
class WeatherPMETClass;
class DebugStateClass;
class BasinClass;                                                                //150519
class clsSoil;                                                                   //140218
class clsManagement;                                                             //150529
//______________________________________________________________________________
class BasinCellClass
#ifdef CROPSYST_VERSION
#ifdef LAND_UNIT_SIM_AS_SUPERCLASS
: public extends_ CropSyst::Land_unit_simulation
#define LAND_UNIT_SIM_ CropSyst::Land_unit_simulation::
#endif
#endif
{
   #ifndef LAND_UNIT_SIM_AS_SUPERCLASS
   public: CropSyst::Land_unit_simulation *land_unit_sim;                        //151208
   #define LAND_UNIT_SIM_ land_unit_sim->
   #endif

   const CS::Database_directory &database_directory;                             //150723RLN
   CORN::OS::Directory_entry_name_concrete output_directory_name;                //141212RLN
      // RLN not sure if we need an output directory for each cell
      // or use one for the entire basin, need to check with Mingliang

    int soilID;
    int soilID_index;                                                            //160317LML
    int crop_rotation_id;
    std::string Soil_String_ID;
    //int num_upgrids;        //number of upstream gridcells
    long inner_id_basin;     //inner ID in basin array
    long inner_id_crop_management_zone;                                          //150519
    CS::Identification cell_ID;                                                  //151206
    #define cell_id cell_ID.number                                               //151206

    int  gridtype;           //1: Basin outlet 2: gauges 3 streams 0: Others
    bool debug_output;                                                           //151007LML
      // I presume this is the centroid of the cell, need to verify with
      // Minglian/Fidel  - 150708RLN

    #ifdef CELL_METEOROLOGY
    //160808 Now provided through meteorology
   //160808 becoming obsolete eventually delete
    const CS::Solar_irradiance_extraterrestrial_hourly &solar_irradiance_extraterrestrial_basin; //150708RLN
    #endif

    double elev_min_neighbors; //(m) 150526
    double slop;                                                                 //(%) 151221LML note: should be %, not degree
    double aspect;          //Implement later M.Liu Feb. 5, 2014 Degree from North
    double area_m2;         //(m2)
    double length;          //(m)
    int    Crop_Management_Zone; //FMS Mar 19, 2015

//170404LML #ifdef PREDEFINE_N_APPLICATION_PER_CELL
    std::vector<double> N_applied_predefined_kgN_per_ha;                         //170320LML
    std::vector<std::string> N_applied_predefined_crop_name;                     //170320LML
//170404LML #endif

    //double annual_mean_temp;//annual mean temperature (for initialize soil temperature)
    int col;                //upper-left:(0,0)
    int row;                //
    int fdir;               //flow direction (from ESRI ArcInfo flowdirection)
                            //1:E 2:SE 4:S 8:SW 16:W 32:NW 64:N 128:NE
    double flow_portion[8]; //ShareFlow in all directions
                            //enum Neighbor {NB_E,NB_SE,NB_S,NB_SW,NB_W,NB_NW,NB_N,NB_NE};
    double slop_nb[8];      //Slop (elevation differences in all directions)
                            //if neigher elev is equal or greater than this grid cell, slop=0
    int neighbor_idindex[8];    //inner ID, not Cell_ID
    double sum_downhill_slop;
    //double **comb_Share_flow;   //[direction][layer] adjusted shareflow
    double vHydroStandardslope; //(m/m)
    double CellBedslope_X;
    double CellBedslope_Y;
    //enum Neighbor {NB_E,NB_SE,NB_S,NB_SW,NB_W,NB_NW,NB_N,NB_NE};
    std::vector<InitialSoilStateClass *> &parrInitSoilStateRef;                     //160317
private:
    void NewCrop();
public:
    Geocoordinate geocoordinate;                                                 //150630RLN

    #ifdef CROPSYST_SOIL
    Soil_properties_sublayers &soil_properties_ref;    //soil;                                                            //131126
    #endif
    // This is owned by the Basin which will either have a database
    AllControlClass &ControlRef;
    BasinClass      &BasinRef;                                                   //150519
    #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
    CropSyst::Rotation_parameters &rotationParameterRef;                         //160317LML
    #endif
public:
    BasinCellClass *downGrid;                                                    //a pointer to downstream grid cell
    std::list<BasinCellClass *> upGrids;                                         //array of pointers to upstream grid cells
    #ifdef MBVB_SOIL
    SoilProcessesClass *pSoilProcess;
    SoilStateClass *pSoilState;
    clsSoil *pSoil;
    SoilStateClass *soil_tallies; //The SoilStateClass currently stores tallies  //160722
    #else
    MicroBasin::Soil_tallies *soil_tallies;                                                  //160722
    MicroBasin::Soil *soil_MicroBasin;
        // Note that soil_hourly is derived class of CropSyst::soil
        // The pointer is the same as Land_Unit_Simulation::soil
        // so don't delete this
    #endif
    #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
    CropSyst::Crop_interfaced *pCrop;                                            //140502
    #else
    clsCrop *pCrop;
    #endif
    CropSyst::Soil_runoff_common  runoff;                                        //141201LML&RNL
    SoilProfileClass *pSoilProfile;                                              //LML 140814 its own soil profile & some of its parameters are mutable, such as Ksat etc
    SoilProfileClass *pSoilProfileUnmutable;                                     //LML 140814 original SoilProfile from parameter file, i.e. one pointer for each soil type
    #ifndef CROPSYST_WEATHER
    #ifdef CELL_METEOROLOGY
    WeatherStateDailyClass *pWeatherDaily;
    #endif
    #ifndef CROPSYST_VERSION
    WeatherPMETClass *pWeatherPMET;
    #endif
    #ifdef MBVB_SNOW
    clsSnow *pSnow;
    #endif
    #ifdef CELL_METEOROLOGY
    double weather_station_elev;                                                 //LML 141008 for calculate pet of weather station
    #endif
    int index_weather_station_info;                                              //LML 141211 index for getting station information
    int index_weather_station_data;                                              //LML 141211 index for getting the weather data
    #endif
    #ifdef CROPSYST_VERSION
    #ifdef CELL_METEOROLOGY
       //160808 becoming obsolete eventually delete
    CS::Land_unit_meteorological meteorology_site;                               //151022
    #else
    const CS::Land_unit_meteorological &meteorology_site;                        //160808RLN
    double none_intercepted_liq_water_m;                                         //161110LML through flow from canopy (i.e. none intercepted librated water (rain + snowmelt)
    #endif
    #else
    clsSimulation *pSimulation; //*psimulation;
    #endif
    #ifdef VB_SAME_CSV_OUTPUT
    OutputMainClass *pOutput;                                                    //151002LML
    #endif
    #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
    #else
    clsManagement *pManagement;
    #endif
    DebugStateClass *pDebugState;
    //Outputs
    //Fluxes
    class Flows{
    public:
        double SurfaceOut;
        double SurfaceIn;
        double Drainage;
        double LateralIn;
        double LateralOut;
        double LateralUp;
    public:
        Flows()
            :SurfaceOut(0)
            ,SurfaceIn(0)
            ,Drainage(0)
            ,LateralIn(0)
            ,LateralOut(0)
            ,LateralUp(0)
            {};
        void initialize();
        void add(const Flows &flow);
        inline double get_total_In() const   {return SurfaceIn+LateralIn;};
        inline double get_total_Out() const  {return SurfaceOut+LateralOut;}
        ~Flows(){};
    } ;
    Flows hourly_flow_m3;
    Flows hourly_flow_solute_kg[SL_COUNT];
    Flows output_flow_m3[TACUM_COUNT];
    Flows output_flow_solute_kg[SL_COUNT][TACUM_COUNT];
    /*160411 this is simply pond.act_evaporation
    double output_daily_pond_evaporation_mm;                                     //150909LML
    */
    double output_harvested_yield;                                               //(ton/ha) 160322LML for daily output
    double report_planting_date_soil_profile_NH4_N;                              //(kgN/ha) 170410LML
    double report_planting_date_soil_profile_NO3_N;                              //(kgN/ha) 170410LML
    double report_planting_date_surface_NH4_N;                                   //(kgN/ha) 170510LML
    double report_planting_date_surface_NO3_N;                                   //(kgN/ha) 170510LML

    double report_Initial_Profile_NO3_N;                                         //(kgN/ha) 170413LML at the first day of year
    double report_Initial_Profile_NH4_N;                                         //(kgN/ha) 170413LML at the first day of year
    double report_Initial_Surface_NO3_N;                                         //(kgN/ha) 170510LML at the first day of year
    double report_Initial_Surface_NH4_N;                                         //(kgN/ha) 170510LML at the first day of year


    double report_surface_NH4_kg_m2;                                             //170501LML report only; for checking hourly balance
    double report_surface_NO3_kg_m2;                                             //170501LML report only; for checking hourly balance
                                                                                 //after the overland flow, the surface N is just pended to next hour infiltration,
                                                                                 //and it doesn't update the suface mass.

    /*150825LML obs.
    double SurfaceOutFlow_m3  [TACUM_COUNT];                                     //(m3)
    double SurfaceInFlow_m3   [TACUM_COUNT];                                     //(m3)
    double Drainage_m3        [TACUM_COUNT];                                     //(m3)
    double LateralInFlow_m3   [TACUM_COUNT];                                     //(m3)
    double LateralOutFlow_m3  [TACUM_COUNT];                                     //(m3)
    double LateralUpFlow_m3   [TACUM_COUNT];                                     //(m3)  become ponded water
    double LateralInFlowSolute_kg      [SL_COUNT][TACUM_COUNT];                  //(kg) [solute]
    double LateralOutFlowSolute_kg     [SL_COUNT][TACUM_COUNT];                  //(kg) [solute]
    double SurfaceInFlowSolute_kg      [SL_COUNT][TACUM_COUNT];                  //(kg) [solute]
    double SurfaceOutFlowSolute_kg     [SL_COUNT][TACUM_COUNT];                  //(kg) [solute]
    */
    double hourly_LateralOutFlowLayer_m3      [MAX_soil_layers];                 //LML 150127 (m3)
    double hourly_LateralOutFlowSoluteLayer_kg[MAX_soil_layers][SL_COUNT];       //LML 150127 (kg) [layer][solute]
    double hourly_fraction_leaving_watershed[MAX_soil_layers];                   //LML 150127 fraction of outflow from each soil layer that leaves watershed

 public: // structors
    BasinCellClass
       (BasinClass &_BasinRef
       ,AllControlClass &_ControlRef
       ,const CORN::Date_const/*170615LML _const_interface*/ &_today                                                 //150630RLN
       #ifdef CROPSYST_VERSION
          ,const CS::Database_directory &database_directory
          #ifdef CELL_METEOROLOGY
             //160808 becoming obsolete eventually delete
          ,Sun &sun_                                                             //160801
          ,const CS::Solar_irradiance_extraterrestrial_hourly &_solar_irradiance_extraterrestrial_basin //150708RLN
          //160801 provided by sun ,const float64 &_day_length_hours_today                                //150730RLN
          #else
          ,const CS::Land_unit_meteorological &meteorology_site_                 //160808
          #endif
       #endif
       #ifdef MBVB_INFILTRATION
       ,SoilProfileClass *_pSoilProfile
       ,SoilProfileClass *_pSoilProfileUnmutable                                 //140814LML
       #endif
       ,double _lat_dec_degree                                                   //150817LML
       ,double _lon_dec_degree                                                   //150817LML
       ,double _elev_m                                                           //150817LML
       ,std::vector<InitialSoilStateClass *> &parrInitSoilStateRef_              //160317LML
       ,long soilID_index_                                                        //160317LML
       /*160808RLN this would not work
       #ifdef MICROBASIN_VERSION_SINGLE_ROTATION_READING_WORKING
       ,CropSyst::Rotation_parameters &rotationParameterRef_                     //160317LML
       #endif
       */
       );
    virtual ~BasinCellClass();                                                   //141212RLN
 public: // CS::Simulation_unit method reimplementations
    virtual bool initialize()                                      modification_;//141221RLN
    virtual bool start()                                           modification_;//151212RLN
    virtual bool start_year()                                      modification_;//141221RLN
    virtual bool start_day()                                       modification_;//141221RLN
    virtual bool process_day()                                     modification_;//150708_141221RLN
    virtual bool end_day()                                         modification_;//141221RLN 150921LML
    virtual bool end_year()                                        modification_;//141221RLN
    #ifndef CROPSYST_VERSION
    virtual float64 get_snow_pack_thickness()                             const {return mm_to_m(pSnow->Daily_Snow_Peak_Depth_mm);}; //(m) 150813LML
    #endif
    virtual bool end_growing_season
       #if ((REACCH_VERSION==2) || (CS_VERSION >= 5) || defined(INTERCROPPING)|| defined(OFOOT_VERSION))
       (CropSyst::Crop_interfaced &active_crop);  // when this becomes permanent rename to crop_ending_its_season //130716
       #else
       ();                                                                        //070227
       #endif
   /*160606
   virtual bool evaporate_pond()                                   modification_ //160408RLN
       { return true; }                                                          //160408RLN
       // Evaporation is already handled by land unit simulation but in MicroBasin version call at beginning of day?
   virtual bool evaporate_soil()                                   modification_ //160408RLN
       { return true; }                                                          //160408RLN
    // Evaporation is handled by MicroBasin version.
    */
 public: // member methods
    double calAlbedo();
    void setInnerId(long innerID);
    int getSoilLayers();
    long getInnerID();
    long getCellId();
    void setCellId(long _cell_id);
    int getSoilID();
    void setSoilID(int _soilID);
    void setCol(int _col);
    int getCol();
    void setRow(int _row);
    int getRow();
    int getGridType();
    void setGridType(int _b_outlet);
    void setFlowDir(int flowdir);
    int getFlowDir();
    void setElev(double _elev);
    double getElev();
    void setSlop(double _slop);
    double getSlop();
    double getCellBedslopeX();
    double getCellBedslopeY();
    void setCellBedslopeX(double X);
    void setCellBedslopeY(double X);
    bool isOutlet() {return (gridtype == 1) ? true : false;};                    //140904LML
    void setArea(double _area);
    double getArea();
    void setSumDownhillSlop(double _sum_downhill_slop);
    double getSumDownhillSlop();
    void setLength(double _length);
    double getLength();
    double getLatitude();
    double getLongitude();
    void setLatitude(double _latitude);
    void setLongitude(double _longitude);
    double getAspect();
    void setAspect(double _aspect);
    int getNeighborIndex(int nb);
    void setNeighborIndex(int nb, int index);
    void setCropRotationID(int _crop_rotation_id);
    int getCropRotationID();
    #ifdef MACA_V1_MBMET
    void setWeatherStationID(int id);
    int getWeatherStationID();
    #endif
    std::string getSoilStringID();
    bool runHourlyGridCellProcess(const int hour);
    void setFlowPortion(int nb,double portion);
    double getFlowPortion(int nb);  //nb:0-7 from E to NE
    void setHydroStandardslope(double _hydroslop);
    double getHydroStandardslope();
    double getSlopNB(int nb);
    void setSlopNB(int nb,double _slop);
    void setCropManagementZone(int zone)        {Crop_Management_Zone = zone;};  //150515LML
    int  getCropManagementZone()                {return Crop_Management_Zone;};  //150515LML
    void setCropManagementZoneInnerID(long zone){inner_id_crop_management_zone = zone;};  //150519LML
    int  getCropManagementZoneInnerID()         {return inner_id_crop_management_zone;};  //150519LML
    int get_soilID_index()                      {return soilID_index;}           //160317LML
    void set_soilID_index(const int index)      {soilID_index = index;}          //160317LML

    double get_m3_from_m(const double flow_m);      //get water column from depth
    double get_m_from_m3(const double flow_m3)  {return flow_m3 / area_m2;};     //150911 get water depth from column
    inline double get_kg_per_m2_from_total_kg (const double amount_kg) {return amount_kg / area_m2;};  //170417LML

    double getTotalMassFromMassPerSquireMeter(const double mass_per_m2) 
       {return (mass_per_m2 * area_m2);}                                         //140910LML
    virtual bool start_hour()                                     modification_; //160724RLN
    //160724RLN renamed void initFluxes();                                                           //140418LML
    //void recordingHourlyState(const BAO::Date date, int hour);
    void sumDailyFlow();
    double getMinElevNeighbors()                {return elev_min_neighbors;};    //150526
    void   setMinElevNeighbors(double min_elev) {elev_min_neighbors = min_elev;};//150526
    void accum_hourly_outflow();                                                 //150910LML
    void init_accumulater_outflow(const TIME_ACCUMULATOR time_acum);             //150910LML
    inline bool get_debug_output()              {return debug_output;}           //151007LML
    inline bool set_debug_output(bool setvalue) {return debug_output = setvalue;}//151007LML
//170404LML #ifdef PREDEFINE_N_APPLICATION_PER_CELL
    bool setPredefinedNFertilization(const std::vector<double> &N_applied, const std::vector<std::string> &crop_name); //170320LML
    int getPredefinedNFertilizationCropIndex(const std::string &cropname);
    virtual Event_status_indicator perform_start_automatic_N_application_mode
       (CropSyst::N_application_soil_observation_mode_class  &auto_N_mode_op);   //170321LML
//170404LML #endif
 #ifdef CROPSYST_VERSION
 public: // Land unit simulation reimplementations
   virtual bool setup_soil();                                                    //141212RLN
   virtual bool load_soil();                                                     //160724RLN
   virtual const OS::Directory_name &get_output_directory_name()          const;//141212RLN
   virtual Common_operation *get_operation
      (const char                   *operation_type_str
      ,const std::string            &operation_ID  // filename may be updated with qualification so not const
      ,modifiable_ CORN::OS::File_name    &operation_filename
         // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32       resource_set_ID,  bool &relinquish_op_to_event);
   virtual const Air_temperature_average &ref_air_temperature_avg()        const; //150724
   virtual const Wind_speed              &ref_wind_speed()                 const; //150724
 #else
    void DestroyCrop();
 #endif
};
//______________________________________________________________________________
#endif // BASINCELLCLASS_H
