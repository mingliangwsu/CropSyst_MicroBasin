#include "organicresidueclass.h"
#include "parameters/organicresidueparameterclass.h"
#include "util/pubtools.h"
#include <iostream>
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif
//______________________________________________________________________________
OrganicResidueClass::OrganicResidueClass(SoilProfileClass &_SoilProfileRef,SoilStateClass &_SoilStateRef,
  OrganicResidueStateClass &_OrganicResidueStateRef, clsSoil &_SoilRef
,AllControlClass &_ControlRef
,const CORN::Date &_today)                                                       //150630RLN
:SoilProfileRef(_SoilProfileRef)
,SoilStateRef(_SoilStateRef)
,OrganicResidueStateRef(_OrganicResidueStateRef)
,SoilRef(_SoilRef)
,ControlRef(_ControlRef)
,today(_today)                                                                   //150630RLN
,Number_Of_Pools(3000)
{
    //parrResidue_Pool = new OrganicResiduePoolClass[Number_Of_Pools];
    Pool_Exist.clear();
    Pool_Exist.resize(Number_Of_Pools + 1,false);
}
//______________________________________________________________________________
OrganicResidueClass::~OrganicResidueClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~OrganicResidueClass:"<<std::endl;
#endif
    //delete[] parrResidue_Pool;
    //delete[] Pool_Exist;
#ifdef Destruct_Monitor
    std::cout<<"~OrganicResidueClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void OrganicResidueClass::AddResiduePool(int Position, double Mass, double Decomposition_Constant,
  double CN_Ratio, double C_Fraction, double Area_To_Mass_Ratio,
  bool Fixed_Index, int Index, 
double Standing_Stubble_Contact_Fraction, double Surface_Residue_Contact_Fraction)
{
    /*
    //First 60 residue pool indices (1 to 60) are dedicated to slow-cycling residues
    //(standing, surface, and root per soil layer residues)
    //Indices 1 to 39: Roots in soil layers (Index 1 is for soil layer one and so on)
    //Indices 41 to 50: Incorporated residue pools (Index 41 is for soil layer one and so on)
    //Indices 51 and 52: Standing stubble and surface residues, respectively

    //Next 60 residue pool indices (61 to 120) are dedicated to lignified residues
    //(standing, surface, and root per soil layer residues)
    //Indices 61 to 99: Roots in soil layers (Index 61 is for soil layer one and so on)
    //Indices 101 to 110: Incorporated residue pools (Index 101 is for soil layer one and so on)
    //Indices 111 and 112: Standing stubble and surface residues, respectively

    //Indices 121 and above are available for fast-cycling pools
    */
    int pool_index(-1);
    if (Fixed_Index) {
        pool_index = Index;
        Pool_Exist[pool_index] = true;
    }
    else pool_index = FindResiduePoolIndex(Number_Of_Pools);
    //pparrResidue_Pool[Index] = New OrganicResiduePoolClass;
    while (parrResidue_Pool.size() < (pool_index + 1)) {
        OrganicResiduePoolClass temp;
        parrResidue_Pool.push_back(temp);
    }
    parrResidue_Pool[pool_index].initialize(Position, Mass, 
        Decomposition_Constant, C_Fraction, CN_Ratio, Area_To_Mass_Ratio,
        Standing_Stubble_Contact_Fraction, Surface_Residue_Contact_Fraction);

}
//______________________________________________________________________________
void OrganicResidueClass::initialize(clsSimulation &Simulation)
{
    /*
    //This subroutine accounts for initial residues at the beginning of the simulation

    //First 60 residue pool indices (1 to 60) are dedicated to slow-cycling residues
    //(standing, surface, and root and incorporated residues per soil layer)
    //Indices 1 to 39: Roots in soil layers (Index 1 is for soil layer one and so on)
    //Indices 41 to 50: Incorporated residue pools (Index 41 is for soil layer one and so on)
    //Indices 51 and 52: Standing stubble and surface residues, respectively

    //Next 60 residue pool indices (61 to 120) are dedicated to lignified residues
    //(standing, surface, and root and incorporated residues per soil layer)
    //Indices 61 to 99: Roots in soil layers (Index 61 is for soil layer one and so on)
    //Indices 101 to 110: Incorporated residue pools (Index 101 is for soil layer one and so on)
    //Indices 111 and 112: Standing stubble and surface residues, respectively

    //Next 60 residue pool indices (121 to 180) are dedicated to fast-cycling residues
    //(standing, surface, and root and incorporated residues per soil layer)
    //Indices 121 to 159: Roots in soil layers (Index 121 is for soil layer one and so on)
    //Indices 161 to 170: Incorporated residue pools (Index 161 is for soil layer one and so on)
    //Indices 171 and 172: Standing stubble and surface residues, respectively
    */
	int Number_Of_Layers = SoilProfileRef.NumberOfLayers();
    if (!OrganicResidueStateRef.b_set_vector_size){ //LML 150205
        OrganicResidueStateRef.Residue_Nitrogen_Immobilization_Demand.resize(Number_Of_Layers + 1);
        OrganicResidueStateRef.Residue_Nitrogen_Mineralization.resize(Number_Of_Layers + 1);
        OrganicResidueStateRef.Potential_Fast_Cycling_Residue_Carbon_Decomposition.resize(Number_Of_Layers + 1);
        OrganicResidueStateRef.Potential_Slow_Cycling_Residue_Carbon_Decomposition.resize(Number_Of_Layers + 1);
        OrganicResidueStateRef.Potential_Lignified_Residue_Carbon_Decomposition.resize(Number_Of_Layers + 1);
        OrganicResidueStateRef.Decomposition_Reduction_Factor.resize(Number_Of_Layers + 1);
        OrganicResidueStateRef.b_set_vector_size = true;
    }
    
    std::string Initial_Standing_Stubble_Residue_Label = SoilStateRef.Initial_Standing_Stubble_Residue_Label;
    double Initial_Standing_Stubble_Residue_Mass = SoilStateRef.Initial_Standing_Stubble_Residue_Mass;
    std::string Initial_Surface_Residue_Label = SoilStateRef.Initial_Surface_Residue_Label;
    double Initial_Surface_Residue_Mass = SoilStateRef.Initial_Surface_Residue_Mass;
    std::string Initial_Soil_Residue_Label = SoilStateRef.Initial_Soil_Residue_Label;
    Fast_Cycling_Residues_Decomposition_Constant = 
        ControlRef.pOrganic_Residue_Parameters->Default_Fast_Cycling_Residues_Decomposition_Constant;
    Slow_Cycling_Residues_Decomposition_Constant = 
        ControlRef.pOrganic_Residue_Parameters->Default_Slow_Cycling_Residues_Decomposition_Constant;
    Lignified_Residues_Decomposition_Constant = 
        ControlRef.pOrganic_Residue_Parameters->Default_Lignified_Residues_Decomposition_Constant;
    ////Initialize values for contact fraction. Contact fraction for flat surface residues will change with changes
    //// in residue mass while the contact fraction for standing residues remains constant
    OrganicResidueStateRef.Standing_Stubble_Contact_Fraction = 
        Simulation.pSimConstants->Standing_Stubble_Contact_Fraction;
    OrganicResidueStateRef.Surface_Residue_Contact_Fraction = 
        Simulation.pSimConstants->Surface_Organic_Residue_Contact_Fraction;
    ////Initialize standing stuble residues
    bool Label_Found = false;
    double Top_Residue_Fast_Cycling_Fraction(0.0);
    double Top_Residue_Slow_Cycling_Fraction(0.0);
    double Top_Residue_Lignin_Fraction(0.0);
    double Fast_Cycling_Residue_CN_Ratio(0.0);
    double Slow_Cycling_Residue_CN_Ratio(0.0);
    double Lignin_Residue_CN_Ratio(0.0);
    double Residue_Carbon_Fraction(0.0);
    double Area_To_Mass_Ratio_Standing(0.0);
    double Area_To_Mass_Ratio_Surface(0.0);
    if (Initial_Standing_Stubble_Residue_Label.size() > 0) {
        //Find label
        int index_crop_residue = ControlRef.pOrganic_Residue_Parameters->
            FindCropResidueParameterIndex(Initial_Standing_Stubble_Residue_Label);
        CropResidueParameterClass *pTempCropResidueParameter =
            &(ControlRef.pOrganic_Residue_Parameters->parrCrop_Residue_Parameter[index_crop_residue]);
        if (index_crop_residue != -9999) {
            Top_Residue_Fast_Cycling_Fraction = pTempCropResidueParameter->Fraction_Of_Fast_Cycling_Biomass;
            Top_Residue_Slow_Cycling_Fraction = pTempCropResidueParameter->Fraction_Of_Slow_Cycling_Biomass;
            Top_Residue_Lignin_Fraction = pTempCropResidueParameter->Fraction_Of_Lignified_Biomass;
            Fast_Cycling_Residue_CN_Ratio = pTempCropResidueParameter->Fast_Cycling_Residue_Default_CN_Ratio;
            Slow_Cycling_Residue_CN_Ratio = pTempCropResidueParameter->Slow_Cycling_Residue_Default_CN_Ratio;
            Lignin_Residue_CN_Ratio = pTempCropResidueParameter->Lignified_Residue_Default_CN_Ratio;
            Residue_Carbon_Fraction = pTempCropResidueParameter->Residue_Carbon_Fraction;
            Area_To_Mass_Ratio_Standing = pTempCropResidueParameter->Area_To_Mass_Ratio_As_Standing_Residue;
            Label_Found = true;
        } else { 
            std::string message = "Can not find residue parameters for " + Initial_Standing_Stubble_Residue_Label;
            nrerror(message.c_str());
        }
    }
    double Composite_Top_Residue_CN_Ratio = 
            Top_Residue_Fast_Cycling_Fraction 
            * Fast_Cycling_Residue_CN_Ratio
            + Top_Residue_Slow_Cycling_Fraction * Slow_Cycling_Residue_CN_Ratio
            + Top_Residue_Lignin_Fraction * Lignin_Residue_CN_Ratio;
    ////Separate fast cycling, slow cycling, and lignified materials
    if (Initial_Standing_Stubble_Residue_Mass > 0) {
        ////OJO Fidel change matriz by variable OrganicResidueStateRef._Standing_Stubble_Carbon_Mass(year, doy)
        OrganicResidueStateRef.Standing_Stubble_Carbon_Mass = 
            Initial_Standing_Stubble_Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef.Standing_Stubble_Nitrogen_Mass = 
            Initial_Standing_Stubble_Residue_Mass * Residue_Carbon_Fraction / Composite_Top_Residue_CN_Ratio;
        if (Top_Residue_Slow_Cycling_Fraction > 0) {
            ////Create just one pool for slow cycling standing residue (index = 51)
            AddResiduePool(-1, Initial_Standing_Stubble_Residue_Mass * Top_Residue_Slow_Cycling_Fraction,
                Slow_Cycling_Residues_Decomposition_Constant, Slow_Cycling_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 51);//,
                //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
        }
        if (Top_Residue_Lignin_Fraction > 0) {
            ////Create just one pool for lignified standing residue (index = 111)
            AddResiduePool(-1, Initial_Standing_Stubble_Residue_Mass * Top_Residue_Lignin_Fraction,
                Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 111);//,
                //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
        }
        if (Top_Residue_Fast_Cycling_Fraction > 0) {
            ////Create just one pool for fast cycling standing residue (index = 171)
            AddResiduePool(-1, Initial_Standing_Stubble_Residue_Mass * Top_Residue_Fast_Cycling_Fraction,
                Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 171);//,
                //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
        }
    } else { //FMS Apr 17, 2015
        //Create just one pool for slow cycling standing residue (index = 51)
        AddResiduePool(-1, 0.0,
                Slow_Cycling_Residues_Decomposition_Constant, Slow_Cycling_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 51);
        //Create just one pool for lignified standing residue (index = 111)
        AddResiduePool(-1, 0.0,
                Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 111);
        //Create just one pool for fast cycling standing residue (index = 171)

        AddResiduePool(-1, 0.0,
                Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 171);
    }
    ////Initialize flat surface residues
    Label_Found = false;
    if (Initial_Surface_Residue_Label.size() > 0) {
        int index_crop_residue = ControlRef.pOrganic_Residue_Parameters->
            FindCropResidueParameterIndex(Initial_Surface_Residue_Label);
        CropResidueParameterClass *pTempCropResidueParameter =
            &(ControlRef.pOrganic_Residue_Parameters->parrCrop_Residue_Parameter[index_crop_residue]);
        if (index_crop_residue != -9999) {
            Top_Residue_Fast_Cycling_Fraction = pTempCropResidueParameter->Fraction_Of_Fast_Cycling_Biomass;
            Top_Residue_Slow_Cycling_Fraction = pTempCropResidueParameter->Fraction_Of_Slow_Cycling_Biomass;
            Top_Residue_Lignin_Fraction = pTempCropResidueParameter->Fraction_Of_Lignified_Biomass;
            Fast_Cycling_Residue_CN_Ratio = pTempCropResidueParameter->Fast_Cycling_Residue_Default_CN_Ratio;
            Slow_Cycling_Residue_CN_Ratio = pTempCropResidueParameter->Slow_Cycling_Residue_Default_CN_Ratio;
            Lignin_Residue_CN_Ratio = pTempCropResidueParameter->Lignified_Residue_Default_CN_Ratio;
            Residue_Carbon_Fraction = pTempCropResidueParameter->Residue_Carbon_Fraction;
            Area_To_Mass_Ratio_Surface = pTempCropResidueParameter->Area_To_Mass_Ratio_As_Surface_Residue;
            Label_Found = true;
        }
    }
    ////Separate fast cycling, slow cycling, and lignified materials
    if (Initial_Surface_Residue_Mass > 0) {
        OrganicResidueStateRef.Surface_Residue_Carbon_Mass = 
            Initial_Surface_Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef.Surface_Residue_Nitrogen_Mass = 
            Initial_Surface_Residue_Mass * Residue_Carbon_Fraction / Composite_Top_Residue_CN_Ratio;
        if (Top_Residue_Slow_Cycling_Fraction > 0) {
            ////Create just one pool for slow cycling surface flat residues (index = 52)
            AddResiduePool(0, Initial_Surface_Residue_Mass * Top_Residue_Slow_Cycling_Fraction,
                Slow_Cycling_Residues_Decomposition_Constant, Slow_Cycling_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Surface, true, 52);//,
                //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
        }
        if (Top_Residue_Lignin_Fraction > 0) {
            ////Create just one pool for lignified surface flat residues(index = 112)
            AddResiduePool(0, Initial_Surface_Residue_Mass * Top_Residue_Lignin_Fraction,
                Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Surface, true, 112);//,
                //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
        }
        if (Top_Residue_Fast_Cycling_Fraction > 0) {
            ////Create just one pool for fast cycling surface flat residues (index = 172)
            AddResiduePool(0, Initial_Surface_Residue_Mass * Top_Residue_Fast_Cycling_Fraction,
                Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio,
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Surface, true, 172);//,
                //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
        }
    }
    ////Initialize root residues
    Label_Found = false;
    double Root_Residue_Fast_Cycling_Fraction(0.0);
    double Root_Residue_Slow_Cycling_Fraction(0.0);
    double Root_Residue_Lignin_Fraction(0.0);
    if (Initial_Soil_Residue_Label.size() > 0) {
        int index_crop_residue = ControlRef.pOrganic_Residue_Parameters->
            FindCropResidueParameterIndex(Initial_Soil_Residue_Label);
        CropResidueParameterClass *pTempCropResidueParameter =
            &(ControlRef.pOrganic_Residue_Parameters->parrCrop_Residue_Parameter[index_crop_residue]);
        if (index_crop_residue != -9999) {
            Root_Residue_Fast_Cycling_Fraction = pTempCropResidueParameter->Fraction_Of_Fast_Cycling_Crop_Root_Biomass;
            Root_Residue_Slow_Cycling_Fraction = pTempCropResidueParameter->Fraction_Of_Slow_Cycling_Crop_Root_Biomass;
            Root_Residue_Lignin_Fraction = pTempCropResidueParameter->Fraction_Of_Lignified_Crop_Root_Biomass;
            Fast_Cycling_Residue_CN_Ratio = pTempCropResidueParameter->Fast_Cycling_Residue_Default_CN_Ratio;
            Slow_Cycling_Residue_CN_Ratio = pTempCropResidueParameter->Slow_Cycling_Residue_Default_CN_Ratio;
            Lignin_Residue_CN_Ratio = pTempCropResidueParameter->Lignified_Residue_Default_CN_Ratio;
            Residue_Carbon_Fraction = pTempCropResidueParameter->Residue_Carbon_Fraction;
            Label_Found = true;
        }
    }
    double Composite_Root_Residue_CN_Ratio = 
        Root_Residue_Fast_Cycling_Fraction * Fast_Cycling_Residue_CN_Ratio
        + Root_Residue_Slow_Cycling_Fraction * Slow_Cycling_Residue_CN_Ratio
        + Root_Residue_Lignin_Fraction * Lignin_Residue_CN_Ratio;
//   Composite_Root_Residue_CN_Ratio = 8.0; // RLN
    for (int i = 1; i <= Number_Of_Layers; i++) { // //This assumes a maximum of 39 soil layers
        double Residue_Mass = SoilStateRef.Initial_Soil_Residue_Mass[i];
        OrganicResidueStateRef.Soil_Residue_Carbon_Mass += 
            Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef.Soil_Residue_Nitrogen_Mass += 
            Residue_Mass * Residue_Carbon_Fraction / Composite_Root_Residue_CN_Ratio;
        ////Separate fast cycling, slow cycling, and lignified materials
        if (Residue_Mass > 0) {
            if (Root_Residue_Slow_Cycling_Fraction > 0) {
                ////Create pools for slow cycling fraction of root residues
                ////Pool indices 1 to 39 are reserved for slow cycling root biomass
                AddResiduePool(i, Residue_Mass * Root_Residue_Slow_Cycling_Fraction,
                    Slow_Cycling_Residues_Decomposition_Constant, Slow_Cycling_Residue_CN_Ratio,
                    Residue_Carbon_Fraction, 999.9, true, i);//,
                    //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
                    ////999.9 indicates irrelevant area to mass ratio
            }
            if (Root_Residue_Lignin_Fraction > 0) {
                ////Create pools for lignified fraction of root residues
                ////Pool indices 61 to 99 are reserved for lignified root biomass
                AddResiduePool(i, Residue_Mass * Root_Residue_Lignin_Fraction,
                    Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio,
                    Residue_Carbon_Fraction, 999.9, true, i + 60);//,
                    //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
                    ////999.9 indicates irrelevant area to mass ratio
            }
            if (Root_Residue_Fast_Cycling_Fraction > 0) {
                ////Create pools for fast cycling fraction of root residues
                ////Pool indices 121 to 159 are reserved for fast cycling root biomass
                AddResiduePool(i, Residue_Mass * Root_Residue_Fast_Cycling_Fraction,
                    Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio,
                    Residue_Carbon_Fraction, 999.9, true, i + 120);//,
                    //Standing_Stubble_Contact_Fraction,Surface_Residue_Contact_Fraction);
                    ////999.9 indicates irrelevant area to mass ratio
            }
        }
    }
}
//______________________________________________________________________________
int OrganicResidueClass::FindResiduePoolIndex(int Number_Of_Pools)
{
    int Available_Index(-1);
    bool Index_Found(false);
    int i(181);            // //First index available for general assignment
    ////Find available slot in the array
    while ((Index_Found == false) && (i <= Number_Of_Pools)){
        if (Pool_Exist[i] == false) {
            Index_Found = true;
            Pool_Exist[i] = true;
            Available_Index = i;
        }
        i++;
    };
    if (i > Number_Of_Pools) Available_Index = -9999;
    return Available_Index;
}
//______________________________________________________________________________
void OrganicResidueClass::PotentialResidueDecomposition(clsSimulation &Simulation)
{
    //double OM_C_Fraction = Simulation.pSimConstants->Carbon_Fraction_In_Organic_Matter;
    const int Number_Of_Layers = SoilProfileRef.NumberOfLayers();
    for (int layer = 1; layer <=Number_Of_Layers; layer++) {
        OrganicResidueStateRef.Residue_Nitrogen_Immobilization_Demand[layer] = 0;
        OrganicResidueStateRef.Residue_Nitrogen_Mineralization[layer] = 0;
        OrganicResidueStateRef.Potential_Fast_Cycling_Residue_Carbon_Decomposition[layer] = 0;
        OrganicResidueStateRef.Potential_Slow_Cycling_Residue_Carbon_Decomposition[layer] = 0;
        OrganicResidueStateRef.Potential_Lignified_Residue_Carbon_Decomposition[layer] = 0;
    }
    OrganicResidueStateRef.Potential_Fast_Cycling_Standing_Stubble_Carbon_Decomposition = 0;
    OrganicResidueStateRef.Potential_Fast_Cycling_Surface_Residue_Carbon_Decomposition = 0;
    OrganicResidueStateRef.Potential_Slow_Cycling_Standing_Stubble_Carbon_Decomposition = 0;
    OrganicResidueStateRef.Potential_Slow_Cycling_Surface_Residue_Carbon_Decomposition = 0;
    OrganicResidueStateRef.Potential_Lignified_Standing_Stubble_Carbon_Decomposition = 0;
    OrganicResidueStateRef.Potential_Lignified_Surface_Residue_Carbon_Decomposition = 0;
    for (int Index = 1; Index <= Number_Of_Pools; Index++) {
        if (Pool_Exist[Index] == true) {
            double Residue_CN_Ratio = parrResidue_Pool[Index].CN_Ratio;
            parrResidue_Pool[Index].PotentialDecompositionAndImmobilization(Index, 
                Residue_CN_Ratio, Simulation, SoilRef);
            int Position = parrResidue_Pool[Index].Position;
            int layer(0);
            if (Position > 0) layer = Position;
            else layer = 1;
            double Nitrogen_Immobilization_Demand = parrResidue_Pool[Index].Nitrogen_Immobilization_Demand;
            double Nitrogen_Mineralization = parrResidue_Pool[Index].Nitrogen_Mineralization;
            double Potential_Residue_Carbon_Decomposition = 
                parrResidue_Pool[Index].Potential_Residue_Carbon_Decomposition;
            OrganicResidueStateRef.Residue_Nitrogen_Immobilization_Demand[layer] += Nitrogen_Immobilization_Demand;
            OrganicResidueStateRef.Residue_Nitrogen_Mineralization[layer] += Nitrogen_Mineralization;
            if (Index >= 1 && Index <= 50) {
                //Indices 1 to 50 are reserved for slow cycling materials in roots and incorporated residues per soil layer
                OrganicResidueStateRef.Potential_Slow_Cycling_Residue_Carbon_Decomposition[layer] += 
                    Potential_Residue_Carbon_Decomposition;
            }
            else if (Index == 51) {
                //Index 51 is reserved for slow cycling materials in standing residues
                OrganicResidueStateRef.Potential_Slow_Cycling_Standing_Stubble_Carbon_Decomposition += 
                    Potential_Residue_Carbon_Decomposition;
            }
            else if (Index == 52) {
                //Index 52 is reserved for slow cycling materials in surface residues
                OrganicResidueStateRef.Potential_Slow_Cycling_Surface_Residue_Carbon_Decomposition += 
                    Potential_Residue_Carbon_Decomposition;
            }
            else if (Index >= 61 && Index <= 110) {
                //Indices 61 to 110 are reserved for lignified materials in roots and incorporated residues per soil layer
                OrganicResidueStateRef.Potential_Lignified_Residue_Carbon_Decomposition[layer] += 
                    Potential_Residue_Carbon_Decomposition;
            }
            else if (Index == 111) {
                //Index 111 is reserved for lignified materials in standing residues
                OrganicResidueStateRef.Potential_Lignified_Standing_Stubble_Carbon_Decomposition += 
                    Potential_Residue_Carbon_Decomposition;
            }
            else if (Index == 112) {
                //Index 112 is reserved for lignified materials in surface residues
                OrganicResidueStateRef.Potential_Lignified_Surface_Residue_Carbon_Decomposition += 
                    Potential_Residue_Carbon_Decomposition;
            }
            else if (Index > 120) {
                if (Position > 0) {
                    OrganicResidueStateRef.Potential_Fast_Cycling_Residue_Carbon_Decomposition[layer] += 
                        Potential_Residue_Carbon_Decomposition;
                } else {
                    if (Position == -1)
                        OrganicResidueStateRef.Potential_Fast_Cycling_Standing_Stubble_Carbon_Decomposition += 
                            Potential_Residue_Carbon_Decomposition;
                    else
                        OrganicResidueStateRef.Potential_Fast_Cycling_Surface_Residue_Carbon_Decomposition += 
                            Potential_Residue_Carbon_Decomposition;
                }
            }
        }
    }//Next Index
}
//______________________________________________________________________________
void OrganicResidueClass::UpdateResiduePoolsAfterDecomposition()
{
    Total_Surface_Residue_Mass = 0;
    Total_Standing_Stubble_Mass = 0;
    Total_Soil_Residue_Mass = 0;
    OrganicResidueStateRef.Decomposed_Standing_Stubble_Carbon_Mass = 0;
    OrganicResidueStateRef.Decomposed_Surface_Residue_Carbon_Mass = 0;
    OrganicResidueStateRef.Decomposed_Soil_Residue_Carbon_Mass = 0;
    OrganicResidueStateRef.Decomposed_Standing_Stubble_Nitrogen_Mass = 0;
    OrganicResidueStateRef.Decomposed_Surface_Residue_Nitrogen_Mass = 0;
    OrganicResidueStateRef.Decomposed_Soil_Residue_Nitrogen_Mass = 0;
    OrganicResidueStateRef.Standing_Stubble_Carbon_Mass = 0;
    OrganicResidueStateRef.Surface_Residue_Carbon_Mass = 0;
    OrganicResidueStateRef.Soil_Residue_Carbon_Mass = 0;
    OrganicResidueStateRef.Standing_Stubble_Nitrogen_Mass = 0;
    OrganicResidueStateRef.Surface_Residue_Nitrogen_Mass = 0;
    OrganicResidueStateRef.Soil_Residue_Nitrogen_Mass = 0;
    if (/*150630RLN ControlRef.*/today.get_DOY() == 1 || (/*150630RLN ControlRef.*/today == ControlRef.start_date)) {                                         //140218 RLN
        OrganicResidueStateRef.Cumulative_Decomposed_Standing_Stubble_Carbon_Mass = 0;
        OrganicResidueStateRef.Cumulative_Decomposed_Surface_Residue_Carbon_Mass = 0;
        OrganicResidueStateRef.Cumulative_Decomposed_Soil_Residue_Carbon_Mass = 0;
    }
    double Total_Standing_Stubble_Area_Index(0.0);
    double Total_Surface_Residue_Area_Index(0.0);
    for (int Index = 1; Index <= Number_Of_Pools; Index++) {
        if (Pool_Exist[Index] == true) {
            parrResidue_Pool[Index].ActualResidueDecomposition(SoilRef);
            //Update residue mass
            double Residue_Mass = parrResidue_Pool[Index].Residue_Mass;
            if (CORN::is_approximately<double>(Residue_Mass,0.0,1e-12)) {
                Pool_Exist[Index] = false;
                //parrResidue_Pool[Index] = null;   //Implement later M.Liu Jan 29, 2014
            }
            double Residue_Area_To_Mass = parrResidue_Pool[Index].Area_To_Mass_Ratio;
            int Position = parrResidue_Pool[Index].Position;
            double Carbon_Mass_In_Organic_Residue = 
                parrResidue_Pool[Index].Carbon_Mass_In_Organic_Residue;
            double Nitrogen_Mass_In_Organic_Residue = 
                parrResidue_Pool[Index].Nitrogen_Mass_In_Organic_Residue;
            double Actual_Residue_Carbon_Decomposition = 
                parrResidue_Pool[Index].Actual_Residue_Carbon_Decomposition;
            double Actual_Residue_Nitrogen_Decomposition = 
                parrResidue_Pool[Index].Actual_Residue_Nitrogen_Decomposition;
            //Calculate total mass and projected area of residue standing on the field or that lies down on the surface
            if (Position == -1) {
                Total_Standing_Stubble_Mass += Residue_Mass;
                Total_Standing_Stubble_Area_Index += Residue_Mass * Residue_Area_To_Mass;
            }
            else if (Position == 0) {
                Total_Surface_Residue_Mass += Residue_Mass;
                Total_Surface_Residue_Area_Index += Residue_Mass * Residue_Area_To_Mass;
            }
            else Total_Soil_Residue_Mass += Residue_Mass;
            if (Position == -1) {
                OrganicResidueStateRef.Decomposed_Standing_Stubble_Carbon_Mass += 
                    Actual_Residue_Carbon_Decomposition;
                OrganicResidueStateRef.Decomposed_Standing_Stubble_Nitrogen_Mass += 
                    Actual_Residue_Nitrogen_Decomposition;
                OrganicResidueStateRef.Standing_Stubble_Carbon_Mass += 
                    Carbon_Mass_In_Organic_Residue;
                OrganicResidueStateRef.Standing_Stubble_Nitrogen_Mass += 
                    Nitrogen_Mass_In_Organic_Residue;
                OrganicResidueStateRef.Cumulative_Decomposed_Standing_Stubble_Carbon_Mass += 
                    Actual_Residue_Carbon_Decomposition;
            }
            else if (Position == 0) {                                              //140214 RLN
                OrganicResidueStateRef.Decomposed_Surface_Residue_Carbon_Mass += 
                    Actual_Residue_Carbon_Decomposition;
                OrganicResidueStateRef.Decomposed_Surface_Residue_Nitrogen_Mass += 
                    Actual_Residue_Nitrogen_Decomposition;
                OrganicResidueStateRef.Surface_Residue_Carbon_Mass += 
                    Carbon_Mass_In_Organic_Residue;
                OrganicResidueStateRef.Surface_Residue_Nitrogen_Mass += 
                    Nitrogen_Mass_In_Organic_Residue;
                OrganicResidueStateRef.Cumulative_Decomposed_Surface_Residue_Carbon_Mass += 
                    Actual_Residue_Carbon_Decomposition;
            } else {
                OrganicResidueStateRef.Decomposed_Soil_Residue_Carbon_Mass += 
                    Actual_Residue_Carbon_Decomposition;
                OrganicResidueStateRef.Decomposed_Soil_Residue_Nitrogen_Mass += 
                    Actual_Residue_Nitrogen_Decomposition;
                OrganicResidueStateRef.Soil_Residue_Carbon_Mass += 
                    Carbon_Mass_In_Organic_Residue;
                OrganicResidueStateRef.Soil_Residue_Nitrogen_Mass += 
                    Nitrogen_Mass_In_Organic_Residue;
                OrganicResidueStateRef.Cumulative_Decomposed_Soil_Residue_Carbon_Mass += 
                    Actual_Residue_Carbon_Decomposition;
            }
        }
    }//Next Index
    double Surface_Residue_Ground_Cover = 1.0 - exp(-1.5 * Total_Surface_Residue_Area_Index);
    double Surface_Residue_Contact_Fraction(0.0);
    if (Total_Surface_Residue_Area_Index > 0)
        Surface_Residue_Contact_Fraction = 
            std::min<double>(1.0, pow(Surface_Residue_Ground_Cover,0.75) 
                                      / Total_Surface_Residue_Area_Index);
    else
        Surface_Residue_Contact_Fraction = 0.2;
    double Standing_Residue_Ground_Cover = 1.0 - exp(-0.3 * Total_Standing_Stubble_Area_Index);
    OrganicResidueStateRef.Surface_Residue_Contact_Fraction = Surface_Residue_Contact_Fraction;
    OrganicResidueStateRef.Surface_Residue_Ground_Cover = Surface_Residue_Ground_Cover;
    OrganicResidueStateRef.Standing_Residue_Ground_Cover = Standing_Residue_Ground_Cover;
    OrganicResidueStateRef.Surface_Residue_Area_Index = Total_Surface_Residue_Area_Index;
    OrganicResidueStateRef.Standing_Residue_Area_Index = Total_Standing_Stubble_Area_Index;
    OrganicResidueStateRef.Surface_Residue_Mass = Total_Surface_Residue_Mass;
    OrganicResidueStateRef.Standing_Stubble_Mass = Total_Standing_Stubble_Mass;
    OrganicResidueStateRef.Total_Top_Residue_Mass = Total_Standing_Stubble_Mass + Total_Surface_Residue_Mass;
}
//______________________________________________________________________________
#ifndef CROPSYST_PROPER_MANAGEMENT
void OrganicResidueClass::RedistributeResiduesAfterTillage(clsManagement &Management)
{
    //ROGER: Think about including separate indices for manure
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_residue_C,bal_residue_N;
    bal_residue_C.SetInitPool(getAboveGroungResidueCarbonMass() + getBellowGroungResidueCarbonMass());
    bal_residue_N.SetInitPool(getAboveGroungResidueNitrogenMass() + getBellowGroungResidueNitrogenMass());
    #endif
    bool Tillage_Application = Management.pManagementState->Tillage_Event;
    if (Tillage_Application == true) {
        double Residue_Fraction_Not_Incorporated = 
            Management.pManagementState->Surface_Residue_Fraction_Remaining_After_Tillage;
        double Standing_To_Flat_Residue_Fraction = 
            Management.pManagementState->Standing_To_Flat_Residue_Fraction;
        int Operation_Soil_Disturbance_Effect = 
            Management.pManagementState->Type_Of_Disturbance;
        //Overall adjustments of residue types (individual residue pools are adjusted below)
        double Initial_Carbon_Mass = OrganicResidueStateRef.Standing_Stubble_Carbon_Mass 
                                     + OrganicResidueStateRef.Surface_Residue_Carbon_Mass 
                                     + OrganicResidueStateRef.Soil_Residue_Carbon_Mass;  //FMS Jul 21/2014
        double Mass_Transferred_From_Standing_To_Surface_Residues = 
            OrganicResidueStateRef.Standing_Stubble_Carbon_Mass * Standing_To_Flat_Residue_Fraction;
        OrganicResidueStateRef.Standing_Stubble_Carbon_Mass -= 
            Mass_Transferred_From_Standing_To_Surface_Residues;
        OrganicResidueStateRef.Surface_Residue_Carbon_Mass += 
            Mass_Transferred_From_Standing_To_Surface_Residues;
        double Mass_Transferred_From_Surface_To_Soil_Residues = 
            (1 - Residue_Fraction_Not_Incorporated) * OrganicResidueStateRef.Surface_Residue_Carbon_Mass;
        OrganicResidueStateRef.Surface_Residue_Carbon_Mass -= 
            Mass_Transferred_From_Surface_To_Soil_Residues;
        OrganicResidueStateRef.Soil_Residue_Carbon_Mass += 
            Mass_Transferred_From_Surface_To_Soil_Residues;
        double Final_Carbon_Mass = OrganicResidueStateRef.Standing_Stubble_Carbon_Mass 
                                   + OrganicResidueStateRef.Surface_Residue_Carbon_Mass 
                                   + OrganicResidueStateRef.Soil_Residue_Carbon_Mass;  //FMS Jul 21/2014
        if (fabs(Final_Carbon_Mass - Initial_Carbon_Mass) > 1e-4) 
            nrerror("Carbon mass balance error during tilliage!!");     
        //Determine the mass of residues transfer from standing to flat surface residue as a result of the tillage operation
        //Transfer is from Index 51 to 52 in the case of slow cycling residues, 111 to 112 in the case of lignified residues,
        //and from 171 to 172 in the case of fast-cycling residues
        //Roger: The way I deal with area to mass ratio was changed from previous version
        //Note that area to mass ratio doubles when standing residues are flattened
        //#ifdef CHECK_MASS_BALANCE
        //bal_residue_C.SetInitPool(getAboveGroungResidueCarbonMass() + getBellowGroungResidueCarbonMass());      //FMS Sep 14, 2014
        //bal_residue_N.SetInitPool(getAboveGroungResidueNitrogenMass() + getBellowGroungResidueNitrogenMass());
        //#endif
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        int pools = 0;
        int current_pool_stand(-1);
        int current_pool_surface(-1);
        double decomp_constant(0.0);
        while (pools < 3) {
            if (pools == 0) {
                current_pool_stand = 51;
                decomp_constant = Slow_Cycling_Residues_Decomposition_Constant;
            }
            else if (pools == 1) {
                current_pool_stand = 111;
                decomp_constant = Lignified_Residues_Decomposition_Constant;
            } else {
                current_pool_stand = 171;
                decomp_constant = Fast_Cycling_Residues_Decomposition_Constant;
            }
            current_pool_surface = current_pool_stand + 1;
            if (Pool_Exist[current_pool_stand] == true) {
                OrganicResiduePoolClass &current_residue = parrResidue_Pool[current_pool_stand];
                double Mass_To_Transfer = current_residue.Residue_Mass
                                          * Standing_To_Flat_Residue_Fraction;
                //Negative mass transfer on next statement indicates mass substraction from the pool
                AddMassToExistingResiduePool(current_pool_stand, 
                                             -Mass_To_Transfer, 
                                             current_residue.Carbon_Fraction,
                                             current_residue.CN_Ratio,
                                             999.9);
                double Area_To_Mass_Ratio_Surface = 
                    current_residue.Area_To_Mass_Ratio * 2.0; //ROGER Note that area to mass ratio doubles when standing residues are flattened
                if (Pool_Exist[current_pool_surface] == true) {
                    AddMassToExistingResiduePool(current_pool_surface, 
                                                 Mass_To_Transfer, 
                                                 current_residue.Carbon_Fraction,
                                                 current_residue.CN_Ratio,
                                                 Area_To_Mass_Ratio_Surface);
                } else {
                    AddResiduePool(0, Mass_To_Transfer, decomp_constant, 
                                   current_residue.CN_Ratio,
                                   current_residue.Carbon_Fraction,
                                   Area_To_Mass_Ratio_Surface, true, current_pool_surface);
                }
            }
            pools++;
        }
        if (Operation_Soil_Disturbance_Effect < 4) { //4 is for operations that do not incorporate residues
            //This section calculates the "sifting" of residues (push down existing residues) by tillage
            IncorporatedSurfaceResiduesintoSoilLayers(Management,
                                                      Residue_Fraction_Not_Incorporated,
                                                      Operation_Soil_Disturbance_Effect); //FMs sep 16, 2014
            SiftingOfResidues(Management,
                              Operation_Soil_Disturbance_Effect); //FMs sep 16, 2014
        }   //end if
        //free(Surface_Pool_Index);    
    }//
    #ifdef CHECK_MASS_BALANCE
    bal_residue_C.SetFinalPool(getAboveGroungResidueCarbonMass() + getBellowGroungResidueCarbonMass());
    bal_residue_N.SetFinalPool(getAboveGroungResidueNitrogenMass() + getBellowGroungResidueNitrogenMass());
    if (!bal_residue_C.IsMassBalance()) bal_residue_C.PrintMassBalanceTerms("Residue C during RedistributeResiduesAfterTillage");
    if (!bal_residue_N.IsMassBalance()) bal_residue_N.PrintMassBalanceTerms("Residue N during RedistributeResiduesAfterTillage");
    #endif
}
#endif
//______________________________________________________________________________
void OrganicResidueClass::AddMassToExistingResiduePool(int Index,double Added_Residue_Mass,double Carbon_Fraction,
  double CN_Ratio_Of_Added_Residue,double Area_To_Mass_Ratio_Of_Added_Residue)
{
    OrganicResiduePoolClass *residue_pool = &(parrResidue_Pool[Index]);
    double Existing_Residue_Mass = residue_pool->Residue_Mass;
    residue_pool->Residue_Mass += Added_Residue_Mass;
    residue_pool->Carbon_Mass_In_Organic_Residue += Added_Residue_Mass * Carbon_Fraction;
    residue_pool->Nitrogen_Mass_In_Organic_Residue += Added_Residue_Mass * Carbon_Fraction / CN_Ratio_Of_Added_Residue;
    residue_pool->CN_Ratio = residue_pool->Carbon_Mass_In_Organic_Residue / residue_pool->Nitrogen_Mass_In_Organic_Residue;
    if (!CORN::is_approximately<double>(residue_pool->Residue_Mass,0.0,1e-12))
        residue_pool->Carbon_Fraction = residue_pool->Carbon_Mass_In_Organic_Residue / residue_pool->Residue_Mass;
    //Roger
    //Determine new area to mass ratio weighted by mass
    if (!CORN::is_approximately<double>(Area_To_Mass_Ratio_Of_Added_Residue,999.9,1e-12)) {
        double Area_To_Mass_Ratio_Of_Existing_Residue = residue_pool->Area_To_Mass_Ratio;
        residue_pool->Area_To_Mass_Ratio = (Existing_Residue_Mass * Area_To_Mass_Ratio_Of_Existing_Residue
            + Added_Residue_Mass * Area_To_Mass_Ratio_Of_Added_Residue)
            / (Existing_Residue_Mass + Added_Residue_Mass);
    }
}
//______________________________________________________________________________
void OrganicResidueClass::AddResiduePool(int Position,double Mass,double Decomposition_Constant,
  double CN_Ratio,double C_Fraction,double Area_To_Mass_Ratio,
  bool Fixed_Index,int Index)
{
    int newindex(-1);
    if (Fixed_Index) {
        newindex = Index;
        Pool_Exist[newindex] = true;
    }
    else newindex = FindResiduePoolIndex(Number_Of_Pools);
    //Set Residue_Pool(Index) = New OrganicResiduePoolClass //M.Liu assume all residue exist
    //If Index = 172 Then Stop
    while (parrResidue_Pool.size() < (newindex + 1)) {
        OrganicResiduePoolClass temp;
        parrResidue_Pool.push_back(temp);
    }
    parrResidue_Pool[newindex].initialize(Position, Mass, Decomposition_Constant, C_Fraction, CN_Ratio,
        Area_To_Mass_Ratio, SoilRef.pOrganicResidueState->Standing_Stubble_Contact_Fraction,
        SoilRef.pOrganicResidueState->Surface_Residue_Contact_Fraction);
}
//______________________________________________________________________________
double OrganicResidueClass::CumulativeResidueIncorporationFraction(double Layer_Bottom_Depth,double Tillage_Depth)
{
    double Cumulative_Residue_Incorporation_Fraction(0.0);
    double Ratio = Layer_Bottom_Depth / Tillage_Depth;
    if (Ratio <= 0.6) Cumulative_Residue_Incorporation_Fraction = 0.28 * exp(1.83 * Ratio - 1);
    else Cumulative_Residue_Incorporation_Fraction = 1 - 0.441 * pow(((1.0 - Ratio) / 0.4), 1.4);
    return Cumulative_Residue_Incorporation_Fraction;
}
//______________________________________________________________________________
void OrganicResidueClass::CropBiomassToResidue(clsSimulation &Simulation,clsManagement &Management,clsCrop &Crop)
{
   #ifdef CROPSYST_PROPER_CROP
   assert(false);
      // Residue handling would need to be reimplemented using CropSyst biomass fate classes
      // Probably wont be needed because when using CropSyst proper
      // will be using CropSyst proper's residue classes.
   #else
    //Sub CropBiomassToResidue(Crop As clsCrop, Simulation As clsSimulation, Management As clsManagement)
    //First 60 residue pool indices (1 to 60) are dedicated to slow-cycling residues
    //(standing, surface, and root and incorporated residues per soil layer)
    //Indices 1 to 39: Roots in soil layers (Index 1 is for soil layer one and so on)
    //Indices 41 to 50: Incorporated residue pools (Index 41 is for soil layer one and so on)
    //Indices 51 and 52: Standing stubble and surface residues, respectively
    
    //Next 60 residue pool indices (61 to 120) are dedicated to lignified residues
    //(standing, surface, and root and incorporated residues per soil layer)
    //Indices 61 to 99: Roots in soil layers (Index 61 is for soil layer one and so on)
    //Indices 101 to 110: Incorporated residue pools (Index 101 is for soil layer one and so on)
    //Indices 111 and 112: Standing stubble and surface residues, respectively
    
    //Next 60 residue pool indices (121 to 180) are dedicated to fast-cycling residues
    //(standing, surface, and root and incorporated residues per soil layer)
    //Indices 121 to 159: Roots in soil layers (Index 121 is for soil layer one and so on)
    //Indices 161 to 170: Incorporated residue pools (Index 161 is for soil layer one and so on)
    //Indices 171 and 172: Standing stubble and surface residues, respectively
    
    //int Planting_Year = Crop.pCropState->Year_Planting;
    int Planting_DOY = Crop.pCropState->DOY_Planting;
    Management.FindBiomassToStandingResidue(Simulation);
    double Fraction_Surface_Residue = Management.Fraction_Of_Biomass_To_Surface_Residue;
    double Fraction_Standing_Residue = Management.Fraction_Of_Biomass_To_Standing_Residue;
    //RS edited
    //was: DAP_At_Maturity = Crop.CropState.DaysAfterPlantingAtMaturity
    //now:
    //DAP_At_Maturity = Crop.CropState.DaysAfterCropExistsAtMaturity
    //end
    double Aboveground_Biomass = Crop.pCropState->Cumulative_Biomass;
    double Yield = Crop.pCropState->Yield;
    //double Top_N_Concentration = Crop.pCropState->Top_Crop_N_Concentration;
    double Standing_Residue_Mass = (Aboveground_Biomass - Yield) * Fraction_Standing_Residue;
    double Surface_Residue_Mass = (Aboveground_Biomass - Yield) * Fraction_Surface_Residue;
    if (Standing_Residue_Mass < 0) Standing_Residue_Mass = 0;
    if (Surface_Residue_Mass < 0) Surface_Residue_Mass = 0;
    //double Aboveground_Residue_Mass = Standing_Residue_Mass + Surface_Residue_Mass;
    //Get organic residue parameters
    std::string Organic_Residue_Label = Crop.pCropState->Crop_Name;
    //bool Label_Found(false);
    Number_Of_Entries = ControlRef.pOrganic_Residue_Parameters->getCropResidueNumbers();//OrganicResidueStateRef.Number_Of_Entries; // FMS Jul 11, 2014
    double Top_Residue_Fast_Cycling_Fraction(0.0);
    double Top_Residue_Slow_Cycling_Fraction(0.0);
    double Top_Residue_Lignin_Fraction(0.0);
    double Root_Residue_Fast_Cycling_Fraction(0.0);
    double Root_Residue_Slow_Cycling_Fraction(0.0);
    double Root_Residue_Lignin_Fraction(0.0);
    double Fast_Cycling_Residue_CN_Ratio(0.0);
    double Slow_Cycling_Residue_CN_Ratio(0.0);
    double Lignin_Residue_CN_Ratio(0.0);
    double Residue_Carbon_Fraction(0.0);
    double Area_To_Mass_Ratio_Standing(0.0);
    double Area_To_Mass_Ratio_Surface(0.0);
    bool Label_Found(false);                                                     //150520
    if ((Number_Of_Entries > 0) && (Organic_Residue_Label.size() > 0)) {
        //Find label
        int index_crop_residue = ControlRef.pOrganic_Residue_Parameters->
            FindCropResidueParameterIndex(Organic_Residue_Label);
        if (index_crop_residue >= 0) {
            Label_Found = true;
            CropResidueParameterClass *pCropResidueParameter = &(ControlRef.pOrganic_Residue_Parameters->parrCrop_Residue_Parameter[index_crop_residue]);
            Top_Residue_Fast_Cycling_Fraction = pCropResidueParameter->Fraction_Of_Fast_Cycling_Biomass;
            Top_Residue_Slow_Cycling_Fraction = pCropResidueParameter->Fraction_Of_Slow_Cycling_Biomass;
            Top_Residue_Lignin_Fraction = pCropResidueParameter->Fraction_Of_Lignified_Biomass;
            Root_Residue_Fast_Cycling_Fraction = pCropResidueParameter->Fraction_Of_Fast_Cycling_Crop_Root_Biomass;
            Root_Residue_Slow_Cycling_Fraction = pCropResidueParameter->Fraction_Of_Slow_Cycling_Crop_Root_Biomass;
            Root_Residue_Lignin_Fraction = pCropResidueParameter->Fraction_Of_Lignified_Crop_Root_Biomass;
            Fast_Cycling_Residue_CN_Ratio = pCropResidueParameter->Fast_Cycling_Residue_Default_CN_Ratio;
            Slow_Cycling_Residue_CN_Ratio = pCropResidueParameter->Slow_Cycling_Residue_Default_CN_Ratio;
            Lignin_Residue_CN_Ratio = pCropResidueParameter->Lignified_Residue_Default_CN_Ratio;
            Residue_Carbon_Fraction = pCropResidueParameter->Residue_Carbon_Fraction;
            Area_To_Mass_Ratio_Standing = pCropResidueParameter->Area_To_Mass_Ratio_As_Standing_Residue;
            Area_To_Mass_Ratio_Surface = pCropResidueParameter->Area_To_Mass_Ratio_As_Surface_Residue;
        }
    }
    //double Straw_Biomass = Aboveground_Biomass - Yield;
    double Straw_Nitrogen_Concentration = Crop.pCropState->Straw_Nitrogen_Concentration;
    //Straw_Nitrogen_Concentration = Top_N_Concentration // FMS Jul 11,2014
    double Composite_Top_Residue_CN_Ratio = Residue_Carbon_Fraction / Straw_Nitrogen_Concentration;
    //OJO: Top CN ratio for each cycling fraction should be different, but we need a criteria to do so
    Fast_Cycling_Residue_CN_Ratio = Composite_Top_Residue_CN_Ratio; //LML 150111 TODO (LML) In one situation it's already asigned a value
    Slow_Cycling_Residue_CN_Ratio = Composite_Top_Residue_CN_Ratio;
    Lignin_Residue_CN_Ratio = Composite_Top_Residue_CN_Ratio;
    //Initialize new standing stubble pool
    if (Standing_Residue_Mass > 0 && Label_Found /*FMS Mar 11, 2015*/) {
        SoilStateRef.Surface_Soil_Cover = SSC_Residue;          //FMS Aug 26, 2014
        OrganicResidueStateRef.Standing_Stubble_Carbon_Mass += Standing_Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef.Standing_Stubble_Nitrogen_Mass += Standing_Residue_Mass * Residue_Carbon_Fraction / Composite_Top_Residue_CN_Ratio;
        OrganicResidueStateRef.New_Standing_Stubble_Carbon_Mass += Standing_Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef.New_Standing_Stubble_Nitrogen_Mass += Standing_Residue_Mass * Residue_Carbon_Fraction / Composite_Top_Residue_CN_Ratio;
        //Separate fast cycling, slow cycling, and lignified materials
        if (Top_Residue_Slow_Cycling_Fraction > 0) {
        //If pool does not exist, create a new pool for slow cycling fraction of new standing residue mass,
        //otherwise, just add to the existing pool (index=51)
            if (Pool_Exist[51]) {
                AddMassToExistingResiduePool(51, Standing_Residue_Mass * Top_Residue_Slow_Cycling_Fraction,
                                             Residue_Carbon_Fraction, 
                                             Slow_Cycling_Residue_CN_Ratio, 
                                             Area_To_Mass_Ratio_Standing);
            } else {
                AddResiduePool(-1, Standing_Residue_Mass * Top_Residue_Slow_Cycling_Fraction, 
                    Slow_Cycling_Residues_Decomposition_Constant, Slow_Cycling_Residue_CN_Ratio, 
                    Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 51);
            }
        }
         if (Top_Residue_Lignin_Fraction > 0) {
            //If pool does not exist, create a new pool for lignified fraction of new standing residue mass,
            //otherwise, just add to the existing pool (index=111)
            if (Pool_Exist[111]) {
                AddMassToExistingResiduePool(111, Standing_Residue_Mass * Top_Residue_Lignin_Fraction, 
                                                  Residue_Carbon_Fraction, Lignin_Residue_CN_Ratio, 
                                                  Area_To_Mass_Ratio_Standing);
            } else {
                AddResiduePool(-1, Standing_Residue_Mass * Top_Residue_Lignin_Fraction, 
                                    Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio, 
                                    Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 111);
            }
        }
        if (Top_Residue_Fast_Cycling_Fraction > 0) {
        //If pool does not exist, create a new pool for fast-cycling fraction of new standing residue mass,
        //otherwise, just add to the existing pool (index=171)
            
            if (Pool_Exist[171]) {
                AddMassToExistingResiduePool(171, Standing_Residue_Mass * Top_Residue_Fast_Cycling_Fraction, 
                                              Residue_Carbon_Fraction, Fast_Cycling_Residue_CN_Ratio, 
                                              Area_To_Mass_Ratio_Standing);
            } else {
                AddResiduePool(-1, Standing_Residue_Mass * Top_Residue_Fast_Cycling_Fraction, 
                Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio, 
                Residue_Carbon_Fraction, Area_To_Mass_Ratio_Standing, true, 171);
            }
        }
    }
    //Initialize new surface residue pool
    if (Surface_Residue_Mass > 0 && Label_Found /*FMS May 1, 2015*/) {
        OrganicResidueStateRef.New_Surface_Residue_Carbon_Mass = 
                OrganicResidueStateRef.New_Surface_Residue_Carbon_Mass 
                + Surface_Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef. New_Surface_Residue_Nitrogen_Mass = 
                OrganicResidueStateRef. New_Surface_Residue_Nitrogen_Mass 
                + Surface_Residue_Mass * Residue_Carbon_Fraction / Composite_Top_Residue_CN_Ratio;
        OrganicResidueStateRef.Surface_Residue_Carbon_Mass = 
                OrganicResidueStateRef.Surface_Residue_Carbon_Mass 
                + Surface_Residue_Mass * Residue_Carbon_Fraction;
        OrganicResidueStateRef.Surface_Residue_Nitrogen_Mass = 
                OrganicResidueStateRef.Surface_Residue_Nitrogen_Mass 
                + Surface_Residue_Mass * Residue_Carbon_Fraction / Composite_Top_Residue_CN_Ratio;
        //Separate fast cycling, slow cycling, and lignified materials
        if (Top_Residue_Slow_Cycling_Fraction > 0) {
        //If pool does not exist, create a new pool for slow cycling fraction of new surface residue mass,
        //otherwise, just add to the existing pool (index=52)
            if (Pool_Exist[52]) {
                AddMassToExistingResiduePool(52, Surface_Residue_Mass * Top_Residue_Slow_Cycling_Fraction, 
                                                Residue_Carbon_Fraction, 
                                                Slow_Cycling_Residue_CN_Ratio, 
                                                Area_To_Mass_Ratio_Surface);
            } else {
                AddResiduePool(0, Surface_Residue_Mass * Top_Residue_Slow_Cycling_Fraction, 
                                  Slow_Cycling_Residues_Decomposition_Constant, 
                                  Slow_Cycling_Residue_CN_Ratio, 
                                  Residue_Carbon_Fraction, 
                                  Area_To_Mass_Ratio_Surface, 
                                  true, 
                                  52);
            }
        }
        if (Top_Residue_Lignin_Fraction > 0) {
        //If pool does not exist, create a new pool for lignified fraction of new surface residue mass,
        //otherwise, just add to the existing pool (index=112)
            if (Pool_Exist[112]) {
                AddMassToExistingResiduePool(112, Surface_Residue_Mass * Top_Residue_Lignin_Fraction, 
                                                  Residue_Carbon_Fraction, Lignin_Residue_CN_Ratio,
                                                  Area_To_Mass_Ratio_Surface);
            } else {
                AddResiduePool(0, Surface_Residue_Mass * Top_Residue_Lignin_Fraction, 
                                    Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio, 
                                    Residue_Carbon_Fraction, Area_To_Mass_Ratio_Surface, true, 112);
            }
        }
        if (Top_Residue_Fast_Cycling_Fraction > 0) {
        //If pool does not exist, create a new pool for fast-cycling fraction of new surface residue mass,
        //otherwise, just add to the existing pool (index=172)
            if (Pool_Exist[172]) {
                AddMassToExistingResiduePool(172, Surface_Residue_Mass * Top_Residue_Fast_Cycling_Fraction, 
                                                Residue_Carbon_Fraction, Fast_Cycling_Residue_CN_Ratio, 
                                                Area_To_Mass_Ratio_Surface);
            } else {
                AddResiduePool(0, Surface_Residue_Mass * Top_Residue_Fast_Cycling_Fraction, 
                                  Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio, 
                                  Residue_Carbon_Fraction, Area_To_Mass_Ratio_Surface, true, 172);
            }
        }
    }
    //Add root mass to residue pools
    int Number_Of_Soil_Layers = SoilProfileRef.NumberOfLayers();
    for (int i = 1; i <= Number_Of_Soil_Layers; i++) {
        //    Composite_Root_Residue_CN_Ratio = (Profile_Root_Biomass * Residue_Carbon_Fraction) _
        //                                       / 1 //Profile_Root_N_Mass
        double Profile_Root_Biomass = Crop.pCropState->Cumulative_Root_Biomass;
        double Residue_Mass = Crop.pCropState->Layer_Root_Mass[i];
        double Profile_Root_N_Mass = Crop.pCropState->Root_N_Mass;
        double Composite_Root_Residue_CN_Ratio = (Profile_Root_Biomass * Residue_Carbon_Fraction) / Profile_Root_N_Mass;
        //OJO: Root CN ratio for each cycling fraction should be different, but we need a criteria to do so
        Fast_Cycling_Residue_CN_Ratio = Composite_Root_Residue_CN_Ratio;
        Slow_Cycling_Residue_CN_Ratio = Composite_Root_Residue_CN_Ratio;
        Lignin_Residue_CN_Ratio = Composite_Root_Residue_CN_Ratio;
        if (Residue_Mass > 0) {
            OrganicResidueStateRef.New_Soil_Residue_Carbon_Mass += 
                Residue_Mass * Residue_Carbon_Fraction;
            OrganicResidueStateRef.New_Soil_Residue_Nitrogen_Mass += 
                Residue_Mass * Residue_Carbon_Fraction / Composite_Root_Residue_CN_Ratio;
            OrganicResidueStateRef.Soil_Residue_Carbon_Mass += 
                Residue_Mass * Residue_Carbon_Fraction;
            OrganicResidueStateRef.Soil_Residue_Nitrogen_Mass += 
                Residue_Mass * Residue_Carbon_Fraction / Composite_Root_Residue_CN_Ratio;
        //Separate fast cycling, slow cycling, and lignified materials
            if (Root_Residue_Slow_Cycling_Fraction > 0) {
            //If pool does not exist, create a new pool for slow cycling fraction of new roots residue mass,
            //otherwise, just add to the existing pool (index=i; it follows soil layer index)
                if (Pool_Exist[i]) {
                    AddMassToExistingResiduePool(i, Residue_Mass * Root_Residue_Slow_Cycling_Fraction, 
                                                      Residue_Carbon_Fraction, 
                                                      Slow_Cycling_Residue_CN_Ratio, 
                                                      999.9);
                } else {
                    AddResiduePool(i, Residue_Mass * Root_Residue_Slow_Cycling_Fraction, 
                        Slow_Cycling_Residues_Decomposition_Constant, 
                        Slow_Cycling_Residue_CN_Ratio, 
                        Residue_Carbon_Fraction, 999.9, true, i);
                        //999.9 indicates irrelevant area to mass ratio
                }
            }
             if (Root_Residue_Lignin_Fraction > 0) {
                //If pool does not exist, create a new pool for Lignin fraction of new roots residue mass,
                //otherwise, just add to the existing pool (index= i + 60)
            
                if (Pool_Exist[i + 60]) {
                    AddMassToExistingResiduePool(i + 60, Residue_Mass * Root_Residue_Lignin_Fraction, 
                                        Residue_Carbon_Fraction, Lignin_Residue_CN_Ratio, 999.9);
                } else {
                    AddResiduePool(i, Residue_Mass * Root_Residue_Lignin_Fraction, 
                        Lignified_Residues_Decomposition_Constant, Lignin_Residue_CN_Ratio, 
                        Residue_Carbon_Fraction, 999.9, true, i + 60);
                        //999.9 indicates irrelevant area to mass ratio
                }
            }
            if (Root_Residue_Fast_Cycling_Fraction > 0) {
            //If pool does not exist, create a new pool for fast cycling fraction of new roots residue mass,
            //otherwise, just add to the existing pool (index= i + 120)
                if (Pool_Exist[i + 120]) {
                    AddMassToExistingResiduePool(i + 120, Residue_Mass * Root_Residue_Fast_Cycling_Fraction, 
                                                    Residue_Carbon_Fraction, Fast_Cycling_Residue_CN_Ratio, 999.9);
                } else {
                    AddResiduePool(i, Residue_Mass * Root_Residue_Fast_Cycling_Fraction, 
                        Fast_Cycling_Residues_Decomposition_Constant, Fast_Cycling_Residue_CN_Ratio, 
                        Residue_Carbon_Fraction, 999.9, true, i + 120);
                        //999.9 indicates irrelevant area to mass ratio
                }
            }
        }
    }
    #endif
}
//______________________________________________________________________________
double OrganicResidueClass::getAboveGroungResidueCarbonMass()
{
    double total(0.0);
    for (int i = 1; i<=Number_Of_Pools; i++) {
        if (Pool_Exist[i] && parrResidue_Pool[i].Position <= 0) {
            total += parrResidue_Pool[i].Carbon_Mass_In_Organic_Residue;
        }
    }
    return total;
}
//______________________________________________________________________________
double OrganicResidueClass::getBellowGroungResidueCarbonMass()
{
    double total(0.0);
    for (int i = 1; i<=Number_Of_Pools; i++) {
        if (Pool_Exist[i] && parrResidue_Pool[i].Position >= 1) {
            total += parrResidue_Pool[i].Carbon_Mass_In_Organic_Residue;
        }
    }
    return total;
}
//______________________________________________________________________________
double OrganicResidueClass::getAboveGroungResidueNitrogenMass()
{
    double total(0.0);
    for (int i = 1; i<=180; i++) {
        if (Pool_Exist[i] && parrResidue_Pool[i].Position <= 0) {
            total += parrResidue_Pool[i].Nitrogen_Mass_In_Organic_Residue;
        }
    }
    return total;
}
//______________________________________________________________________________
double OrganicResidueClass::getBellowGroungResidueNitrogenMass()
{
    double total(0.0);
    for (int i = 1; i <= 180; i++) {
        if (Pool_Exist[i] && parrResidue_Pool[i].Position >= 1) {
            total += parrResidue_Pool[i].Nitrogen_Mass_In_Organic_Residue;
        }
    }
    return total;
}
//______________________________________________________________________________
void OrganicResidueClass::IncorporatedSurfaceResiduesintoSoilLayers(clsManagement &Management, 
  double Residue_Fraction_Not_Incorporated, 
  int Operation_Soil_Disturbance_Effect)
{
    //FMS Subdivided the original RedistributeResiduesAfterTillage FMS Sep 16, 2014
    // This section calculates how much of the incorporated surface (flat) residues 
    //go into different soil layers affected by tillage
    //Calculate transfer coefficient
    double Tillage_Depth = Management.pManagementState->Tillage_Depth;         //FMS Sep 16, 2014
    int Last_Tilled_Layer = Management.pManagementState->Last_Layer_Tilled; //FMS Sep 16, 2014
    double Surface_Residue_Mass_Fraction_Into_Layer[10];    //FMS Sep 16, 2014
    double factor(0.0);
    switch(Operation_Soil_Disturbance_Effect) {
        case 1: //Inversion with some mixing
        {
            double Layer_Top_Accumulation(0.0);
            double Sum_Surface_Residue_Into_Layer(0.0);
            for (int i = 1; i <= Last_Tilled_Layer; i++) {
                if (i == Last_Tilled_Layer) {
                    Surface_Residue_Mass_Fraction_Into_Layer[i] = 1.0 - Layer_Top_Accumulation;
                } else {
                    double Layer_Bottom_Accumulation = 
                        CumulativeResidueIncorporationFraction(SoilProfileRef.Layer_Bottom_Depth_m[i],Tillage_Depth);
                    Surface_Residue_Mass_Fraction_Into_Layer[i] = 
                        Layer_Bottom_Accumulation - Layer_Top_Accumulation;
                    Layer_Top_Accumulation = Layer_Bottom_Accumulation;
                }
                Sum_Surface_Residue_Into_Layer += Surface_Residue_Mass_Fraction_Into_Layer[i];  
                //TODO (LML) 150111 check its usage
            }
        }
            break;
        case 2: //Mixing with some inversion
        case 3: //Mixing
        {
            if (Operation_Soil_Disturbance_Effect == 2) factor = 0.5;
            else factor = 0.3;
            for (int i = 1; i <= Last_Tilled_Layer; i++) {
                if (i == Last_Tilled_Layer) {
                    Surface_Residue_Mass_Fraction_Into_Layer[i] = 
                        1.0 - pow(SoilProfileRef.Layer_Bottom_Depth_m[i-1] / Tillage_Depth, factor);
                } else {
                    Surface_Residue_Mass_Fraction_Into_Layer[i] = 
                        pow(SoilProfileRef.Layer_Bottom_Depth_m[i] / Tillage_Depth,factor)
                        - pow(SoilProfileRef.Layer_Bottom_Depth_m[i-1] / Tillage_Depth, factor);
                }
            }
        }
    }
    double total_Pool_Residue_Mass_To_Soil(0.0);
    for (int i = 1; i <= Last_Tilled_Layer; i++) {
        if (Surface_Residue_Mass_Fraction_Into_Layer[i] > 0) {
            int current_pool(-1);
            int pools = 0;
            int pool_shift(0);
            while (pools < 3) {
                if (pools == 0) {
                    //Slow-cycling aboveground surface (flat) residue pool
                    current_pool = 52;
                    pool_shift = 40;
                } else if (pools == 1) {
                    //Lignified aboveground surface (flat) residue pool
                    current_pool = 112;
                    pool_shift = 100;
                } else {
                    //Fast-cycling aboveground surface (flat) residue pool
                    current_pool = 172;
                    pool_shift = 160;
                }
                OrganicResiduePoolClass &current_residue = parrResidue_Pool[current_pool];
                double Pool_Mass = current_residue.Residue_Mass;
                double Pool_CN_Ratio = current_residue.CN_Ratio;
                double Pool_Carbon_Fraction = current_residue.Carbon_Fraction;
                double Pool_Decomposition_Constant = current_residue.Decomposition_Constant;
                double Pool_Residue_Mass_Remaining = Pool_Mass * Residue_Fraction_Not_Incorporated;
                double Pool_Residue_Mass_To_Soil_Layer = 
                    Pool_Mass * (1 - Residue_Fraction_Not_Incorporated) * Surface_Residue_Mass_Fraction_Into_Layer[i];
                total_Pool_Residue_Mass_To_Soil += Pool_Residue_Mass_To_Soil_Layer;   //FMS Sep 16, 2014 LML 141013 what this for?
                if (Pool_Exist[pool_shift + i]) {
                    AddMassToExistingResiduePool(pool_shift + i, 
                                                 Pool_Residue_Mass_To_Soil_Layer, 
                                                 Pool_Carbon_Fraction, 
                                                 Pool_CN_Ratio, 
                                                 999.9);
                }  else {
                    AddResiduePool(i, Pool_Residue_Mass_To_Soil_Layer,
                        Pool_Decomposition_Constant, Pool_CN_Ratio,
                        Pool_Carbon_Fraction, 999.9, true, pool_shift + i);
                }
                if (i == Last_Tilled_Layer && Pool_Exist[current_pool]) {        //FMS Apr 17, 2015 added Pool_Exist
                //Reduce giving pools to remaining residue amount
                    current_residue.Residue_Mass = Pool_Residue_Mass_Remaining;
                    current_residue.Carbon_Mass_In_Organic_Residue =
                        Pool_Residue_Mass_Remaining * Pool_Carbon_Fraction;
                    current_residue.Nitrogen_Mass_In_Organic_Residue =
                        Pool_Residue_Mass_Remaining * Pool_Carbon_Fraction / Pool_CN_Ratio;
                }
                pools++;
            }//while
        }//if
    }//for
}
//______________________________________________________________________________
void OrganicResidueClass::SiftingOfResidues(clsManagement &Management, 
  int Operation_Soil_Disturbance_Effect)
{
    //FMS Subdivided the original RedistributeResiduesAfterTillage FMS Sep 16, 2014
    double Tillage_Depth = Management.pManagementState->Tillage_Depth;         //FMS Sep 16, 2014
    int Last_Tilled_Layer = Management.pManagementState->Last_Layer_Tilled; //FMS Sep 16, 2014
    //This section calculates the "sifting" of residues (push down existing residues) by tillage
    //Calculate transfer coefficient
    double Transfer_Coefficient[10];
    switch(Operation_Soil_Disturbance_Effect) {
        case 1: //Inversion with some mixing
            for (int i = 1; i <= Last_Tilled_Layer; i++) {
                if (i == Last_Tilled_Layer) Transfer_Coefficient[i] = 0;
                else Transfer_Coefficient[i] = 0.6;
            }
            break;
        case 2: //Mixing with some inversion
            for (int i = 1; i <= Last_Tilled_Layer; i++) {
                if (i == Last_Tilled_Layer) {
                    Transfer_Coefficient[i] = 0;
                } else {
                    double Ratio = ((SoilProfileRef.Layer_Bottom_Depth_m[i] 
                                     + SoilProfileRef.Layer_Bottom_Depth_m[i-1]) / 2.0) 
                                   / Tillage_Depth;
                    Transfer_Coefficient[i] = 1 - (0.7539 * Ratio + 0.2413);
                }
            }
            break;
        case 3: //Mixing
            for (int i = 1; i <= Last_Tilled_Layer; i++) {
                if (i == Last_Tilled_Layer) {
                    Transfer_Coefficient[i] = 0;
                } else {
                    double Ratio = ((SoilProfileRef.Layer_Bottom_Depth_m[i] 
                                     + SoilProfileRef.Layer_Bottom_Depth_m[i-1]) / 2.0) 
                                   / Tillage_Depth;
                    Transfer_Coefficient[i] = 1 - (0.55152 * Ratio + 0.44667);
                }
            }
    }
    //Calculate residue mass transfer during "sifting"
    int pools = 0;
    int pool_shift(0);
    while (pools < 3) {
        if (pools == 0) pool_shift = 40;         //Transfer Slow-cycling residues
        else if (pools == 1) pool_shift = 100;   //Transfer Lignified residues
        else pool_shift = 160;                   //Transfer Fast-cycling residues
        double Residue_Mass_In = 0;
        for (int i = 1; i <= Last_Tilled_Layer; i++) {
            double Residue_Mass_Out(0.0);   //TODO (LML) 150111 check its usage
            if (Pool_Exist[pool_shift + i]) {
                double Current_Pool_Residue_Mass = parrResidue_Pool[pool_shift + i].Residue_Mass;
                Residue_Mass_Out = Current_Pool_Residue_Mass * Transfer_Coefficient[i];
                if (Residue_Mass_In > 0) AddMassToExistingResiduePool(pool_shift + i, Residue_Mass_In, 
                        parrResidue_Pool[pool_shift + i - 1].Carbon_Fraction,
                        parrResidue_Pool[pool_shift + i - 1].CN_Ratio, 
                        parrResidue_Pool[pool_shift + i - 1].Area_To_Mass_Ratio);
                //negative sign for mass implies substraction
                if (Residue_Mass_Out > 0) AddMassToExistingResiduePool(pool_shift + i, -Residue_Mass_Out, 
                        parrResidue_Pool[pool_shift + i].Carbon_Fraction,
                        parrResidue_Pool[pool_shift + i].CN_Ratio, 999.9);
                Residue_Mass_In = Residue_Mass_Out;
            } else if (Residue_Mass_In > 0) {
                AddResiduePool(i, Residue_Mass_In,
                    parrResidue_Pool[pool_shift + i - 1].Decomposition_Constant, 
                    parrResidue_Pool[pool_shift + i - 1].CN_Ratio,
                    parrResidue_Pool[pool_shift + i - 1].Carbon_Fraction, 999.9, true, pool_shift + i);
                Residue_Mass_Out = 0;
                Residue_Mass_In = Residue_Mass_Out;
            } else {
                Residue_Mass_Out = 0;
                Residue_Mass_In = Residue_Mass_Out;
            }
        }
        pools++;
    }//while
}
//______________________________________________________________________________



