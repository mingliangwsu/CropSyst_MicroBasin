#ifndef CONSTANTS_H
#define CONSTANTS_H
#define FILENAMELENGTH 200
#define PERMITTED_ERROR_NUTRIENTS_KG_PER_KM2 1e-6
#include <string>
extern const double Pi;
extern const double Solar_Const_W;
extern const double Solar_Constant_MJ;
extern const double CP;
//131121 RLN extern const double standard_gravity;
extern const double WaterDensity_kg_m3;
//131121 RLN extern const double Gravity;
extern const double m_P_kPa;
extern const double m_h_P_KgS_m3;
extern const double Latent_Heat_of_Fusion_J_kg;
extern const double Latent_Heat_of_Vaporization_J_kg;
extern const double Seconds_Per_Day;
extern const double Seconds_Per_Hour;
extern const double Hours_Per_Day;
extern const double StefBoltz_W_m2K4;
extern const double Grams_Per_Mol_NH3;
extern std::string Neighbor_Name[];
extern std::string Solute_Name[];
extern std::string MASS_Name[];
enum Neighbor {NB_E = 0,NB_SE = 1,NB_S = 2,NB_SW = 3,NB_W = 4,NB_NW = 5,NB_N = 6,NB_NE = 7};
enum FD_bc_top {FD_BC_TOP_VIRTUALSAT = 1,FD_BC_TOP_WET = 2};
enum FD_bc_bottom {FD_BC_BOTTOM_WATERTABLE = 1,FD_BC_BOTTOM_NOFLOW = 2,FD_BC_BOTTOM_FREEDRAIN = 3};
enum Solute {SL_Nitrate,SL_Ammonia,SL_Phosphate,SL_Salt,SL_COUNT};
enum /*class*/ Enum_Node_Or_Layer {NODE,LAYER,BOTH};
enum MASS {MASS_WATER = 0,MASS_NITRATE = 1,MASS_AMONIA = 2,MASS_SALT = 3};
enum Surface_Soil_Cover_Type {SSC_Snow,SSC_PerennialCrop,SSC_Orchard,SSC_TreeCrop,SSC_SmallCrop,SSC_TallCrop,SSC_BareSoil,SSC_Residue,SSC_Default};   //LML 140902
enum Fertilization_TYPE {SCHEDULED_FERTILIZATION,AUTO_FERTILIZATION,FERTIGATION,FERTILIZATION_TYPE_NUMS}; //LML 150519
enum Option_Outlet_Flow {OUTLET_MINIMUM_ELEV,OUTLET_CONSTANT_ELEV,OUTLET_CONSTANT_SLOP}; //150526
enum TIME_ACCUMULATOR {TACUM_HOURLY,TACUM_DAILY,TACUM_MONTH,TACUM_GROWTHSEASON,TACUM_ANNUAL,TACUM_COUNT}; //150812LML
#endif // CONSTANTS_H
