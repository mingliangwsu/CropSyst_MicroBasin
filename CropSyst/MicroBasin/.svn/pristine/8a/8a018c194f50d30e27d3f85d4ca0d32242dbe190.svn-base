#include "management/clsmanagement.h"
/*160606RLN
these used to be in soilprocessclass.h
*/
namespace MSVB
{
//_____________________________________________________________________________
class SoilProcessesClass
{

   double CalculateSurfaceStorage(double Curve_Number);
   double SDRDecay(double Water_Filled_Porosity);
   double TillageIntensity(double Clay, double SDR);

   #ifdef MBVB_FD
   double calcWaterContent(int i, double p, double&dwdp);
   double elementflux(int i, double&djdpu, double&djdpl);
   void setSoilWater(int NLmax);
   #endif

#ifndef CROPSYST_VERSION
      , clsManagement & Management
#endif

#ifdef MSVB_CASCADE_INFILTRATION_HOUR
   std::vector<double> Hours_To_Field_Capacity;
#endif

#ifdef MBVB_FD
   // For solve_layer_inf
   std::vector<double> a; // lower diagonal of tridiag matrix
   std::vector<double> bx; // main diagonal of tridiag matrix
   std::vector<double> C; // upper diagonal of tridiag matrix
   std::vector<double> f; // vector of known values
   std::vector<double> dp;
   std::vector<double> cpu; // upper node water capacity
   std::vector<double> cpl; // lower node water capacity
   std::vector<double> DZ; // Layer thickness
   std::vector<double> djdpu;
   std::vector<double> djdpl;
   std::vector<double> V_Lower;
   std::vector<double> V_Upper;
   std::vector<double> v;

   std::vector<double> SAT;
   std::vector<double> HalfLayer_Thickness;
   std::vector<double> Minimum_K_sat;

   std::vector<double> Initial_SavePot; // Beginning of day node water potential
   std::vector<double> Initial_Save_wu; // Beginning of day node upper water content
   std::vector<double> Initial_Save_wl; // Beginning of day node lower water content
#endif
#ifdef LIU_FD_RICHARD
   // M.Liu's method for FD soil moisture flow
   bool bFirst_FD;

   double fd_delx; // (m) 0.02
   int fd_delt; // (seconds) 300
   double fd_f1;
   double fd_f2;
   double fd_f3;
   double fd_f4;
   int fd_nodes; // number of nodes

   std::vector<double> fd_a;
   std::vector<double> fd_b;
   std::vector<double> fd_c;
   std::vector<double> fd_d;
   std::vector<double> fd_v;
   std::vector<double> fd_tempa;
   std::vector<double> fd_tempb;
   std::vector<double> fd_u; // (m)
   std::vector<double> fd_pu; // (m)
   std::vector<double> fd_K; // (m/s)
   std::vector<double> fd_CC; // specific moisture capacity
   std::vector<double> fd_theta;
   std::vector<double> fd_theta_b;
   std::vector<double> fd_pe; // (m)
   std::vector<double> fd_WS;
   std::vector<double> fd_WPW; // permanent wilt point vwc
   std::vector<double> fd_KS; // (m/s)
   std::vector<double> fd_b_value;
   std::vector<double> fd_thick;
   double **fd_fraction; // [node][soil_layer] Each node's domain fraction in each soil layer
   int *fd_soil_layer_index; // The soil layer holds the majority of node's domain or the toppart
#endif
#ifndef MBVB_INFILTRATION
   bool First_Hour_Of_Watering;
   CropSyst::Soil_runoff *p_runoff;
   CropSyst::Pond *p_pond;
#endif

   #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_MANAGEMENT))
   #else
   void TillageEffectOnSoilProperties(clsManagement & Management);
   void DetermineSCSRunoff(
   #ifdef CROPSYST_PROPER_CROP
      const CropSyst::Crop_interfaced & crop                                     //140502
   #else
      clsCrop & crop
   #endif
      , clsSimulation & Simulation, clsManagement & Management);
   #ifndef CROPSYST_PROPER_MANAGEMENT
   void DecompositionRateAdjustmentByTillage(clsManagement & Management);
   #endif
   #endif

   #ifndef CROPSYST_FD
   #ifdef MBVB_FD
   void Adjust_FD_Drainage_Error(double Drainage_Error_mm, double Drainage,
      double Flux);

   bool SolveLayerInf(int hour, double dt, double&Flux, double&Drainage,
      double Actual_Evaporation, bool&Sat_BC,
      double &Finite_Difference_Error);
   void SaveSoilWaterStatus();
   #endif
   #endif

#ifdef LIU_FD_RICHARD
   void setFDLayerIndex();
   void setFDNodesFraction();
   int getSoilLayerIndex(double bottom_depth_m);
   void InitializeFDRichard();
   void performFDRichard(clsSimulation & Simulation,
      clsManagement & Management);
   double calcWaterContentFDRichard(int node_index, double p, double&dwdp);
   double calcConductFDRichard(int node_index, double theta); // (m/s)
   void RemoveExtraWaterFromNodes(double extra_infiltrated);
   double AddExtraWaterToNodes(double water_to_add);
   double getTotalSoilWaterFromNodes();
   void WaterFromNodesToSoilLayer();
   void WaterFromSoilLayerToNodes();
   void SetNodesThetaFromPressure(double*parrNodePressure);
#endif
 public:
   void UpdateHourlySoilWaterContentByDailyTranspiration
      (WeatherStateDailyClass &Weather
      #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
      ,double Total_Canopy_Solar_Radiation_Interception_Fraction                 //150317
      #else
      , clsCrop &Crop
      #endif
      , double &hourly_transpiration_m); //New Sub rootine FMS Aug 18, 2014
   double calcPotSoilWaterEvaporationHourly
      (int hour_of_day
      ,WeatherStateDailyClass & Weather
      ,clsSnow & Snow
      #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
      ,double Total_Canopy_Solar_Radiation_Interception_Fraction
      #else
      ,clsSimulation & Simulation
      ,clsCrop & Crop
      #endif
      );
	double DetermineSoilWaterEvaporationHourly(double Pot_Soil_Evap_mm);
   void DetermineSoilWaterEvaporation
      ( WeatherStateDailyClass & Weather
      , clsSnow & Snow
      #if (defined(CROPSYST_VERSION) || defined(CROPSYST_PROPER_CROP))
      , double Total_Canopy_Solar_Radiation_Interception_Fraction                //141204RLN
      #else
      , clsSimulation & Simulation
      , clsCrop & Crop
      #endif
      );	
	  
     void TillageEffectOnWCHourly(clsManagement &Management); //FMS Aug 20, 2014	  
};
//_____________________________________________________________________________
}