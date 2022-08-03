#ifndef ORGANICRESIDUECLASS_H
#define ORGANICRESIDUECLASS_H
#include "organicresiduepoolclass.h"
#include <string>
#include "organicresiduestateclass.h"
#include "control/clssimulation.h"
#include "control/debugstateclass.h"
#include "weather/weatherstatedailyclass.h"
#include "management/clsmanagement.h"
#ifdef CROPSYST_PROPER_CROP
#  include "crop/crop_interfaced.h"
#  define clsCrop CropSyst::Crop_interfaced
#endif

class clsSoil;
class SoilStateClass;
class OrganicResidueStateClass;
class SoilProfileClass;
class OrganicResiduePoolClass;
class WeatherStateDailyClass;
class clsSimulation;
class clsManagement;
//______________________________________________________________________________
class OrganicResidueClass
{
private:
    int FindResiduePoolIndex(int Number_Of_Pools);
    double CumulativeResidueIncorporationFraction(double Layer_Bottom_Depth,double Tillage_Depth);
public:
    std::vector<OrganicResiduePoolClass> parrResidue_Pool;   //(3000);
        //Indices 1 to 50 slow residues
        //Index 51 slow standing residues
        //Index 52 slow surface residues
        
        //Indices 61 to 110 lignified residues
        //Index 111 lignified standing residues
        //Index 112 lignified surface residues
        
        //Index > 121 - 170 Fast Residues
        //Indices 171 fast standing residues
        //Indices 172 fast surface residues 
        //double **Default_Residue_Parameters;  //(20, 16);

    std::string Default_Residue_Labels[20];
    std::vector<bool> Pool_Exist;    //(3000) As Boolean
    int Number_Of_Pools;  // = 3000;
    int Number_Of_Entries;
    double Total_Surface_Residue_Mass;
    double Total_Standing_Stubble_Mass;
    double Total_Soil_Residue_Mass;
    double Total_Standing_Stubble_Water_Retention;
    double Total_Surface_Residue_Water_Retention;
    double Surface_Residue_Relative_Water_Content;
    double Standing_Stubble_Relative_Water_Content;
    double Surface_Residue_Temperature;
    double Standing_Stubble_Temperature;
    double Fast_Cycling_Residues_Decomposition_Constant;
    double Slow_Cycling_Residues_Decomposition_Constant;
    double Lignified_Residues_Decomposition_Constant;
    //'referencing
    SoilStateClass &SoilStateRef;
    OrganicResidueStateClass &OrganicResidueStateRef;
    SoilProfileClass &SoilProfileRef;
    clsSoil &SoilRef;
    AllControlClass &ControlRef;
 private:
    const CORN::Date &today;                                                     //150630RLN
public:
    OrganicResidueClass
       (SoilProfileClass &_SoilProfileRef
       ,SoilStateClass &_SoilStateRef
       ,OrganicResidueStateClass &_OrganicResidueStateRef
       ,clsSoil &_SoilRef
       ,AllControlClass &_ControlRef
       ,const CORN::Date &_today);                                               //150630RLN
    ~OrganicResidueClass();
    void AddResiduePool(int Position, double Mass, double Decomposition_Constant,
                       double CN_Ratio, double C_Fraction, double Area_To_Mass_Ratio,
                       bool Fixed_Index, int Index, 
                       double Standing_Stubble_Contact_Fraction, double Surface_Residue_Contact_Fraction);

    void initialize(clsSimulation &Simulation);
    void PotentialResidueDecomposition(clsSimulation &Simulation);
    void UpdateResiduePoolsAfterDecomposition();
    void RedistributeResiduesAfterTillage(clsManagement &Management);
    void AddMassToExistingResiduePool(int Index,double Added_Residue_Mass,double Carbon_Fraction,
                                     double CN_Ratio_Of_Added_Residue,double Area_To_Mass_Ratio_Of_Added_Residue);
    void AddResiduePool(int Position,double Mass,double Decomposition_Constant,
                       double CN_Ratio,double C_Fraction,double Area_To_Mass_Ratio,
                       bool Fixed_Index,int Index);
    double getAboveGroungResidueCarbonMass();
    double getBellowGroungResidueCarbonMass();
    double getAboveGroungResidueNitrogenMass();
    double getBellowGroungResidueNitrogenMass();
    void IncorporatedSurfaceResiduesintoSoilLayers(clsManagement &Management, 
                        double Residue_Fraction_Not_Incorporated, int Operation_Soil_Disturbance_Effect); //FMS Subdivided the original RedistributeResiduesAfterTillage FMS Sep 16, 2014
    void SiftingOfResidues(clsManagement &Management, 
                        int Operation_Soil_Disturbance_Effect);                                           //FMS Subdivided the original RedistributeResiduesAfterTillage FMS Sep 16, 2014
    
    void CropBiomassToResidue(clsSimulation &Simulation,clsManagement &Management,clsCrop &Crop);   //FMS Jul 11, 2014


};
//______________________________________________________________________________
#endif // ORGANICRESIDUECLASS_H
