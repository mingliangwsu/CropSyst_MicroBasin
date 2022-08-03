#ifndef SOILCHEMICALTRANSPORTCLASS_H
#define SOILCHEMICALTRANSPORTCLASS_H
#ifndef CROPSYST_CHEMICAL_TRANSPORT
#ifdef CHEMICAL_TRANSPORT

#include "soil/soilprocessesclass.h"
#include "soil/soilprofileclass2.h"
#include "soil/soilstateclass.h"
#include "util/constants.h"
#ifdef CROPSYST_VERSION
#else
#  include "management/clsmanagement.h"
   class clsManagement;
#endif
#include <vector>
class SoilProcessesClass;
//class SoilStateClass;
class SoilProfileClass;

class SoilChemicalTransportClass
{
    double Final_Chemical_Mass;
    double Initial_Chemical_Mass;
    //double Layer_Ammonium_Mass;               //(nmax);
    std::vector<double> Layer_Chemical_Concentration;         //(nmax);
    std::vector<double> Layer_Chemical_Mass;    //(nmax);
    //double *Layer_Initial_Ammonium_Mass;      //(nmax);
    //double *Layer_Initial_Nitrate_Mass;       //(nmax);
    //double *Layer_Initial_Phosphorus_Mass;    //(nmax);
    //double *Layer_Initial_Salt_Mass;          //(nmax);
    //double Layer_Nitrate_Mass;                //(nmax);
    //double Layer_Phosphorus_Mass;             //(nmax);
    //double *Layer_Plant_Available_Ammonium_Mass;    //(nmax);
    //double *Layer_Plant_Available_Phosphorus_Mass;  //(nmax);
    //double *Layer_Salt_Mass;                  //(nmax);
    std::vector<double> Node_Ammonium_Mass;     //(nmax);
    std::vector<double> Node_Chemical_Mass;     //(nmax);
    std::vector<double> Node_Concentration;     //(nmax);
    std::vector<double> Node_Nitrate_Mass;      //(nmax);
    std::vector<double> Node_Phosphorus_Mass;   //(nmax);
    std::vector<double> Node_Salt_Mass;         //(nmax);
    double Sum_Solute_Leaching;
    double TimeStep_Initial_Nitrate_In_Profile;
    double TimeStep_End_Nitrate_In_Profile;
    double Water_Table_Concentration;
    //Temporal variables
    std::vector<double> Range_NodeChemMass;
    std::vector<double> Range_Node_depth;
    std::vector<double> Range_LayerChemMass;
    std::vector<double> Range_Layer_depth;
    std::vector<double> Layer_Depth;
    std::vector<double> Node_Depth;
    std::vector<double> U;
    std::vector<double> yt;
    std::vector<double> A_Term;
    std::vector<double> B_Term;
    std::vector<double> C_Term;
    std::vector<double> D_Term;
    std::vector<double> FDFlow;
    std::vector<double> Lower_Water_Content;
    std::vector<double> New_Node_Concentration;
    std::vector<double> New_Water_Depth;    //For cascade chemical transport
    std::vector<double> Old_Water_Depth;    //For cascade chemical transport
    std::vector<double> Sorbed_Chemical_Mass;
    std::vector<double> Upper_Water_Content;
    std::vector<double> CascadeFlow;
    std::vector<double> Chemical_Mass;
    std::vector<double> Layer_Concentration;
    std::vector<double> New_Layer_Concentration;
    double CubicSpline(int dims, std::vector<double> &xin, std::vector<double> &yin, double X_for_which_2find_Y);
    void LayerChemMass_2_LayerChemConc(Solute Nutrient_Label);
    void LayerChemMass_2_NodeChemMass();
    void NodeChemMass_2_LayerChemMass();
    void Handover_Chem_2_Solute(Enum_Node_Or_Layer Node_or_Layer,Solute Nutrient_Label);
    void Handover_Solute_2_Chem(Enum_Node_Or_Layer Node_or_Layer,Solute Nutrient_Label);
    void LayerChemicalConc_2_Mass();
    double calcFDChemicalMass(Enum_Node_Or_Layer Node_or_Layer);
    double LangmuirSoluteEquilibriumConcentration(Solute Nutrient_Label,double Chemical_Mass
                 ,double Soil_Bulk_Density, double Layer_Thickness,double Volumetric_Water_Content
                 ,double &Chem_Mass_Fraction_In_Solution);
public:
    double Chemical_Mass_Leaching_NO3;                                           //141126LML
    double Chemical_Mass_Leaching_NH4;                                           //141126LML
    double Chemical_Mass_Leaching_Phosphorus;                                    //141126LML
public:
    SoilStateClass &SoilStateRef;
    SoilProfileClass &SoilProfileRef;
    SoilProcessesClass &SoilProcessesRef;
    AllControlClass &ControlRef;
    int counterFDChemicalTrans;                                                  //140307FMS
public:
    SoilChemicalTransportClass(SoilStateClass &_SoilStateRef,SoilProfileClass &_SoilProfileRef
                               ,SoilProcessesClass &_SoilProcessesRef,AllControlClass &_ControlRef);
    ~SoilChemicalTransportClass();
    void FDChemicalTransport(
		double Time_Step,std::string Nutrient_Label
		#ifndef CROPSYST_VERSION
		,clsManagement &Management,clsSimulation &Simulation
		#endif
		);
    void CascadeChemicalTransport(const int hour, const Solute Nutrient_Label);

};
#endif
#endif
#endif // SOILCHEMICALTRANSPORTCLASS_H
