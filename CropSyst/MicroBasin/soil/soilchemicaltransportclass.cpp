#ifndef CROPSYST_CHEMICAL_TRANSPORT
#ifdef CHEMICAL_TRANSPORT
#include "soilchemicaltransportclass.h"
#include "util/pubtools.h"
#include "util/constants.h"
#include <iostream>
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif
#ifdef CROPSYST_VERSION
#include "soil/chemicals_profile.h"
#endif
SoilChemicalTransportClass::SoilChemicalTransportClass(SoilStateClass &_SoilStateRef,
  SoilProfileClass &_SoilProfileRef,SoilProcessesClass &_SoilProcessesRef,
  AllControlClass &_ControlRef)
    :SoilStateRef(_SoilStateRef)
    ,SoilProfileRef(_SoilProfileRef)
    ,SoilProcessesRef(_SoilProcessesRef)
    ,ControlRef(_ControlRef)
    ,Chemical_Mass_Leaching_NO3(0)
    ,Chemical_Mass_Leaching_NH4(0)
    ,Chemical_Mass_Leaching_Phosphorus(0)
{
    const int nmax = SoilProfileRef.NumberOfLayers() + 5;                        //150205LML
    //const int Number_Of_Effective_Layers = nmax;
    //const int Number_Of_Nodes = nmax;
    Layer_Chemical_Concentration.resize(nmax,0);    
    Layer_Chemical_Mass.resize(nmax,0);             
    Node_Ammonium_Mass.resize(nmax,0);              
    Node_Chemical_Mass.resize(nmax,0);              
    Node_Concentration.resize(nmax,0);              
    Node_Nitrate_Mass.resize(nmax,0);               
    Node_Phosphorus_Mass.resize(nmax,0);            
    Node_Salt_Mass.resize(nmax,0);                  
    Range_NodeChemMass.resize(nmax,0);              
    Range_Node_depth.resize(nmax,0);                
    Range_LayerChemMass.resize(nmax,0);             
    Range_Layer_depth.resize(nmax,0);               
    Layer_Depth.resize(nmax,0);                     
    Node_Depth.resize(nmax,0);                      
    U.resize(nmax,0);                               
    yt.resize(nmax,0);                              
    FDFlow.resize(nmax,0);                          
    Lower_Water_Content.resize(nmax,0);             
    New_Node_Concentration.resize(nmax,0);          
    Upper_Water_Content.resize(nmax,0);             
    New_Layer_Concentration.resize(nmax,0);         
    counterFDChemicalTrans = 0;                     
    Chemical_Mass.resize(nmax,0);
    CascadeFlow.resize(nmax,0);
    A_Term.resize(nmax,0);
    B_Term.resize(nmax,0);
    C_Term.resize(nmax,0);
    D_Term.resize(nmax,0);
    Layer_Concentration.resize(nmax,0);
    Sorbed_Chemical_Mass.resize(nmax,0);
    New_Water_Depth.resize(nmax,0);
    Old_Water_Depth.resize(nmax,0);
}
//______________________________________________________________________________
SoilChemicalTransportClass::~SoilChemicalTransportClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~SoilChemicalTransportClass:"<<std::endl;
#endif
#ifdef Destruct_Monitor
    std::cout<<"~SoilChemicalTransportClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void SoilChemicalTransportClass::CascadeChemicalTransport
(const int hour,const Solute Nutrient_Label)
{
    //150914LML note:
    //Need make sure before this call, the surface water chemical concentrations are recalculated!!
    const double nu = 0.6;
    const double Mixing_Efficiency = 0.8;                                        //150528
    std::string nutrient_name = (Nutrient_Label == SL_Ammonia ? "NH4" : (Nutrient_Label == SL_Nitrate ? "NO3" : "PO4"));
    const int Number_Of_Soil_Layers = SoilProfileRef.NumberOfLayers();
    if (hour == 0) {
        switch(Nutrient_Label){
        case SL_Nitrate:
            SoilStateRef.Daily_Nitrate_Leaching = 0;
            break;
        case SL_Ammonia:
            SoilStateRef.Daily_Ammonium_Leaching = 0;
            break;
        case SL_Phosphate:
            SoilStateRef.Daily_Phosphorus_Leaching = 0;
            break;
        default:
            std::clog<<"Nutrient not exist!";
            assert(false);
        }
    }
    //Initiate chemical mass per layer for the current chemical species
    double Step_Initial_Chemical_Mass(0.0);                                      //131028FMS
    double Step_Final_Chemical_Mass(0.0);
    #ifdef DISABLED
    //150630 I disabled this debug, probably obsolete
    if (Nutrient_Label == SL_Nitrate && ControlRef.today.get_DOY() == 65 && hour == 15) {
        int debug = 1;
        /*
        SoilStateRef.Layer_Nitrate_N_Mass[1] = 2.2948e-8;
        SoilStateRef.Layer_Nitrate_N_Mass[2] = 4.5448e-5;
        SoilStateRef.Layer_Nitrate_N_Mass[3] = 3.4795e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[4] = 6.7996e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[5] = 9.7509e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[6] = 1.147e-3;
        SoilStateRef.Layer_Nitrate_N_Mass[7] = 1.115e-3;
        SoilStateRef.Layer_Nitrate_N_Mass[8] = 1.039e-3;
        SoilStateRef.Layer_Nitrate_N_Mass[9] = 9.884e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[10] = 9.648e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[11] = 9.672e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[12] = 1.905e-3;
        SoilStateRef.Layer_Nitrate_N_Mass[13] = 9.224e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[14] = 1.828e-4;
        SoilStateRef.Layer_Nitrate_N_Mass[15] = 1.701e-4;
        SoilStateRef.Water_Flow[0]            = 0;
        SoilStateRef.Water_Flow[1]            = 8.59031081422434e-06;
        SoilStateRef.Water_Flow[2]            = 2.69891472318262e-05;
        SoilStateRef.Water_Flow[3]            = 5.62738312637867e-05;
        SoilStateRef.Water_Flow[4]            = 8.70111085328362e-05;
        SoilStateRef.Water_Flow[5]            = 1.16753194044711e-04;
        SoilStateRef.Water_Flow[6]            = 1.41912811228401e-04;
        SoilStateRef.Water_Flow[7]            = 1.64947781536406e-04;
        SoilStateRef.Water_Flow[8]            = 1.88449046198752e-04;
        SoilStateRef.Water_Flow[9]            = 2.11950310861098e-04;
        SoilStateRef.Water_Flow[10]            = 2.35451575523443e-04;
        SoilStateRef.Water_Flow[11]            = 2.58952840185789e-04;
        SoilStateRef.Water_Flow[12]            = 3.29456634172826e-04;
        SoilStateRef.Water_Flow[13]            = 7.42228136900967e-06;
        SoilStateRef.Water_Flow[14]            = 7.42228136900967e-06;
        SoilStateRef.Water_Flow[15]            = 7.42228136900967e-06;

        SoilStateRef.New_Water_Content[1]  = 0.341159083536329;
        SoilStateRef.New_Water_Content[2]  = 0.341159083536329;
        SoilStateRef.New_Water_Content[3]  = 0.343533912476371;
        SoilStateRef.New_Water_Content[4]  = 0.343574949542372;
        SoilStateRef.New_Water_Content[5]  = 0.348103520814909;
        SoilStateRef.New_Water_Content[6]  = 0.372148061821773;
        SoilStateRef.New_Water_Content[7]  = 0.382698660118295;
        SoilStateRef.New_Water_Content[8]  = 0.390022112550159;
        SoilStateRef.New_Water_Content[9]  = 0.390022112550159;
        SoilStateRef.New_Water_Content[10]  = 0.390022112550159;
        SoilStateRef.New_Water_Content[11]  = 0.390022112550159;
        SoilStateRef.New_Water_Content[12]  = 0.390022112550159;
        SoilStateRef.New_Water_Content[13]  = 0.422496314912286;
        SoilStateRef.New_Water_Content[14]  = 0.328502936506684;
        SoilStateRef.New_Water_Content[15]  = 0.328490566037736;
        SoilStateRef.Old_Water_Content[1]  = 0.341330889752614;
        SoilStateRef.Old_Water_Content[2]  = 0.341527060264681;
        SoilStateRef.Old_Water_Content[3]  = 0.343826759316691;
        SoilStateRef.Old_Water_Content[4]  = 0.343882322315063;
        SoilStateRef.Old_Water_Content[5]  = 0.348400941670028;
        SoilStateRef.Old_Water_Content[6]  = 0.37239965799361;
        SoilStateRef.Old_Water_Content[7]  = 0.382929009821375;
        SoilStateRef.Old_Water_Content[8]  = 0.390257125196782;
        SoilStateRef.Old_Water_Content[9]  = 0.390257125196782;
        SoilStateRef.Old_Water_Content[10]  = 0.390257125196782;
        SoilStateRef.Old_Water_Content[11]  = 0.390257125196782;
        SoilStateRef.Old_Water_Content[12]  = 0.390257125196782;
        SoilStateRef.Old_Water_Content[13]  = 0.421422867069607;
        SoilStateRef.Old_Water_Content[14]  = 0.328502936506684;
        SoilStateRef.Old_Water_Content[15]  = 0.328490566037736;
        SoilStateRef.Layer_Nitrate_N_Conc[0]= 0.0;
        */
    }
    #endif
    Soil_chemicals_profile *chemicals = SoilStateRef.chemicals_optional;         //151212
    for (int layer = 0; layer <= Number_Of_Soil_Layers; layer++) {
        switch(Nutrient_Label){
        #ifdef CROPSYST_VERSION
        case SL_Nitrate:
            Chemical_Mass[layer] = chemicals->get_NO3_N_mass_kg_m2(layer);
            break;
        case SL_Ammonia:
            Chemical_Mass[layer] = chemicals->get_NH4_N_mass_kg_m2(layer);
            break;
        #else
        case SL_Nitrate:
            Chemical_Mass[layer] = SoilStateRef.Layer_Nitrate_N_Mass[layer];
            break;
        case SL_Ammonia:
            Chemical_Mass[layer] = SoilStateRef.Layer_Ammonium_N_Mass[layer];
            break;
        #endif
        case SL_Phosphate:
            Chemical_Mass[layer] = SoilStateRef.Layer_Phosphorus_Mass[layer];
            break;
        default:
            std::clog<<"Nutrient not exist!";
            assert(false);
        }
        if (layer >= 0)                                                          //160325LML > 0)
            Step_Initial_Chemical_Mass += Chemical_Mass[layer];
        /*if (Nutrient_Label == SL_Nitrate) {
            std::clog<<"Initial Chemical Mass:"
                     <<"\t"<<Solute_Name[Nutrient_Label]
                     <<"\tL:"<<layer
                     <<"\tC_M:"     <<Chemical_Mass[layer]
                     <<std::endl;
        }*/
    }
    CascadeFlow[0] = SoilStateRef.Water_Flow[0]; //Flow is in m/h (m3H2O/m2area/h) 
    //RS: this is the amount of water that infiltrates into the soil, runoff already discounted
    //RS added/changed; unit (kg solute element /m3 water)
    //Layer_Concentration[0] = Fertigation
    switch(Nutrient_Label){
    //150914LML still use old version
    //150914LML#ifdef CROPSYST_VERSION
    //150914LMLcase SL_Nitrate:
    //150914LML    Layer_Concentration[0] = std::max<double>(SoilProcessesRef.chemicals->get_NO3_N_mass_kg_m2(0) / SoilStateRef.pond.get_depth(),0.0);
    //150914LML    break;
    //150914LMLcase SL_Ammonia:
    //150914LML    Layer_Concentration[0] = std::max<double>(SoilProcessesRef.chemicals->get_NH4_N_mass_kg_m2(0) / SoilStateRef.pond.get_depth(),0.0);
    //150914LML    break;
    //NYI case SL_Phosphate:
    //NYI    Layer_Concentration[0] = std::max<double>(SoilStateRef.Layer_Phosphorus_Conc[0],0.0);
    //NYI    break;
    //150914LML#else
    case SL_Nitrate:
        Layer_Concentration[0] = CORN::must_be_0_or_greater<float64>(SoilStateRef.Layer_Nitrate_N_Conc[0]);
        break;
    case SL_Ammonia:
        Layer_Concentration[0] = CORN::must_be_0_or_greater<float64>(SoilStateRef.Layer_Ammonium_N_Conc[0]);
        break;
    case SL_Phosphate:
        Layer_Concentration[0] = CORN::must_be_0_or_greater<float64>(SoilStateRef.Layer_Phosphorus_Conc[0]);
        break;
    //150914LML#endif
    default:
        std::clog<<"Nutrient not exist!";
        assert(false);
    }

    /*std::clog<<"CascadeFlow[0]:"<<CascadeFlow[0]
             <<"\tChemical_Mass["<<nutrient_name<<"]:"<<Chemical_Mass[0]
             <<"\tLayer_Concentration[0]:"<<Layer_Concentration[0]
             <<std::endl;*/


    if (Layer_Concentration[0] * CascadeFlow[0] > (Chemical_Mass[0] + 1.e-8)) {
        std::clog<<"Warning:"
                <<"\tLayer_Concentration[0] * CascadeFlow[0] > (Chemical_Mass[0]!!!\n"
                <<"\t"<<nutrient_name
                <<"\tLayer_Concentration[0]:"<<Layer_Concentration[0]
                <<"\tCascadeFlow[0]:"<<CascadeFlow[0]
                <<"\ttotal_infiltrated:"<<Layer_Concentration[0] * CascadeFlow[0]
                <<"\tChemical_Mass[0]:"<<Chemical_Mass[0]
                <<std::endl;
        //assert(false);
    }
    for (int layer = 1; layer <= Number_Of_Soil_Layers; layer++) {
        double Layer_Thickness = SoilProfileRef.get_thickness_m(layer);
        double Layer_Domain_Thickness = Layer_Thickness;
        //This next two lines yield units of meter (m3 water/m2 soil)
        //140603         #ifndef CROPSYST_HYDROLOGY
        //LML 140618 #ifdef MBVB_FD
        New_Water_Depth[layer] = SoilStateRef.New_Water_Content[layer] * Layer_Domain_Thickness;
        Old_Water_Depth[layer] = SoilStateRef.Old_Water_Content[layer] * Layer_Domain_Thickness;
        //water content for the node domain at the beginning of the current time step, before FD solution for the current time step
        double Old_Water_Content_Layer = SoilStateRef.Old_Water_Content[layer];
        //LML 140618 #endif
        double Chemical_Mass_In_Layer = Chemical_Mass[layer];
        if (Chemical_Mass_In_Layer > 0) {
            if ((Nutrient_Label == SL_Ammonia) || (Nutrient_Label == SL_Phosphate)) {
                double Bulk_Density = SoilProfileRef.get_bulk_density_g_cm3(layer);
                //Layer concentration in kg Chem/m3 water
                double Chem_Mass_Fraction_In_Solution(0.0);
                Layer_Concentration[layer] = 
                        LangmuirSoluteEquilibriumConcentration(Nutrient_Label, 
                                                               Chemical_Mass_In_Layer,
                                                               Bulk_Density, 
                                                               Layer_Domain_Thickness, 
                                                               Old_Water_Content_Layer, 
                                                               Chem_Mass_Fraction_In_Solution);
                Sorbed_Chemical_Mass[layer] = Chemical_Mass_In_Layer * (1 - Chem_Mass_Fraction_In_Solution);
            } else {
                if (!CORN::is_approximately<double>(Old_Water_Content_Layer,0))  //151113LML added this condition
                  Layer_Concentration[layer] = Mixing_Efficiency                 //COS May 29, 2015 Only could move Mixing_Efficiency
                                             * Chemical_Mass_In_Layer
                                             / (Layer_Domain_Thickness 
                                             * Old_Water_Content_Layer);
                else
                  Layer_Concentration[layer] = 0.;
                //if (Nutrient_Label == SL_Nitrate) {
                    /*std::clog<<"CHECKING Layer_Concentration:"
                             <<"\t"         <<Solute_Name[Nutrient_Label]
                             <<"\tL:"       <<layer
                             <<"\tM_E:"     <<Mixing_Efficiency
                             <<"\tCM:"      <<Chemical_Mass_In_Layer
                             <<"\tLDT:"     <<Layer_Domain_Thickness
                             <<"\tOWCL:"    <<Old_Water_Content_Layer
                             <<"\tL_C[L]:"  <<Layer_Concentration[layer]
                             <<std::endl;*/
                //}
                Sorbed_Chemical_Mass[layer] = Chemical_Mass_In_Layer * (1. - Mixing_Efficiency); //150529 0;
            }
        } else {
            Layer_Concentration[layer] = 0;
            Sorbed_Chemical_Mass[layer] = 0;
        }
        //Flow is in m/h (m3H2O/m2area/h)
        CascadeFlow[layer] = SoilStateRef.Water_Flow[layer];
        //151217LML if (CascadeFlow[layer] < 0) {
        //151217LML    CascadeFlow[layer] = 0;                                              //LML 150216 TODO DEBUG only!!!
        //151217LML    std::clog<<"Reseting negtive cascade to zero!!!\n";
        //151217LML}
    }// Next Layer
    for (int layer = 1; layer <= Number_Of_Soil_Layers; layer++) {
        A_Term[layer] = CascadeFlow[layer - 1] * nu;
        B_Term[layer] = -New_Water_Depth[layer] - CascadeFlow[layer] * nu;
        C_Term[layer] = 0;
        if (layer == 1) {
            D_Term[layer] = -Old_Water_Depth[layer] * Layer_Concentration[layer]
                            + CascadeFlow[layer] * (1. - nu) * Layer_Concentration[layer]
                            - CascadeFlow[layer - 1] * Layer_Concentration[layer - 1];
        } else {
            D_Term[layer] = -Old_Water_Depth[layer] * Layer_Concentration[layer]
                            + CascadeFlow[layer] * (1. - nu) * Layer_Concentration[layer]
                            - CascadeFlow[layer - 1] * (1. - nu) * Layer_Concentration[layer - 1];
        }
        if (D_Term[layer] > 0 && 
            !CORN::is_approximately<double>(CascadeFlow[layer],0.0,1e-12)) {     //M.Liu in case CascadeFlow = 0 Need Check!!!
            double temp = D_Term[layer] / (CascadeFlow[layer] * (1. - nu));
            if (Layer_Concentration[layer] >= temp) {                            //141014FMS  add condition
                Layer_Concentration[layer] -= temp;
                D_Term[layer] = 0;
            }
        }
        /*if (Nutrient_Label == SL_Nitrate) {
            std::clog<<"CHECKING ABCD terms:"
                     <<"\t"         <<Solute_Name[Nutrient_Label]
                     <<"\tL:"       <<layer
                     <<"\tA:"       <<A_Term[layer]
                     <<"\tB:"       <<B_Term[layer]
                     <<"\tC:"       <<C_Term[layer]
                     <<"\tD:"       <<D_Term[layer]
                     <<"\tO_WD:"    <<Old_Water_Depth[layer]
                     <<"\tL_C[L]:"  <<Layer_Concentration[layer]
                     <<"\tCF[L]:"   <<CascadeFlow[layer]
                     <<"\tL_C[L-1]:"<<Layer_Concentration[layer-1]
                     <<"\tCF[L-1]:" <<CascadeFlow[layer-1]
                     <<std::endl;
        }*/
    }
    //Resolution of the system by Thomas algorithm. Compute new concentration
    for (int layer = 1; layer <= (Number_Of_Soil_Layers - 1); layer++) {
        // Condition added to avoid division by 0
        if (CORN::is_approximately<double>(B_Term[layer],0.0,1e-12)) B_Term[layer] = 1e-12;
        C_Term[layer] /= B_Term[layer];
        D_Term[layer] /= B_Term[layer];
        B_Term[layer + 1] -= A_Term[layer + 1] * C_Term[layer];
        D_Term[layer + 1] -= A_Term[layer + 1] * D_Term[layer];
    }//Next Layer
    // Condition added to avoid division by 0
    if (CORN::is_approximately<double>(B_Term[Number_Of_Soil_Layers],0.0,1e-12)) 
        B_Term[Number_Of_Soil_Layers] = 1e-10;//New_Layer_Concentration[Number_Of_Soil_Layers] = 0;   //LML 140911
    New_Layer_Concentration[Number_Of_Soil_Layers] = 
        D_Term[Number_Of_Soil_Layers] / B_Term[Number_Of_Soil_Layers];
    Chemical_Mass[Number_Of_Soil_Layers] =
                Sorbed_Chemical_Mass[Number_Of_Soil_Layers]
                + New_Layer_Concentration[Number_Of_Soil_Layers] 
                  * New_Water_Depth[Number_Of_Soil_Layers];
    /*if (Nutrient_Label == SL_Nitrate) {
        std::clog<<"CHECKING last layer:\n"
                 <<"\t"<<Solute_Name[Nutrient_Label]
                 <<"\tC_M:"     <<Chemical_Mass[Number_Of_Soil_Layers]
                 <<"\tS_C_M:"   <<Sorbed_Chemical_Mass[Number_Of_Soil_Layers]
                 <<"\tN_L_C:"   <<New_Layer_Concentration[Number_Of_Soil_Layers]
                 <<"\tB:"       <<B_Term[Number_Of_Soil_Layers]
                 <<"\tB[L-1]:"  <<B_Term[Number_Of_Soil_Layers-1]
                 <<"\tD:"       <<D_Term[Number_Of_Soil_Layers]
                 <<"\tD[L-1]:"  <<D_Term[Number_Of_Soil_Layers-1]
                 <<"\tA:"       <<A_Term[Number_Of_Soil_Layers]
                 <<"\tN_W_D:"   <<New_Water_Depth[Number_Of_Soil_Layers]
                 <<std::endl;
    }*/
    if(Chemical_Mass[Number_Of_Soil_Layers] < 0.0 &&
            CORN::is_approximately<double>(Chemical_Mass[Number_Of_Soil_Layers],0,1e-12))
        Chemical_Mass[Number_Of_Soil_Layers] = 0.0;                              //150204LML
    
    if (Chemical_Mass[Number_Of_Soil_Layers] < 0.0) {
        #pragma omp critical
        std::clog<<Solute_Name[Nutrient_Label]
                 <<" has negtive mass "
                 <<Chemical_Mass[Number_Of_Soil_Layers]
                 <<" at bottom layer!"
                 <<" Sorbed_Chemical_Mass:"<<Sorbed_Chemical_Mass[Number_Of_Soil_Layers]
                 <<" New_Layer_Concentration:"<<New_Layer_Concentration[Number_Of_Soil_Layers] 
                 <<" New_Water_Depth:"<<New_Water_Depth[Number_Of_Soil_Layers]
                 <<std::endl;
        //exit(1);
    }
    for (int layer = (Number_Of_Soil_Layers - 1); layer >= 1; layer--) {
        New_Layer_Concentration[layer] = 
            D_Term[layer] - C_Term[layer] * New_Layer_Concentration[layer + 1];
        Layer_Concentration[layer] = New_Layer_Concentration[layer];
        double old_mass = Chemical_Mass[layer];
        Chemical_Mass[layer] =
            std::max<double>(Sorbed_Chemical_Mass[layer]
                             + New_Layer_Concentration[layer] 
                               * New_Water_Depth[layer],0.0);                    //141014FMS
        //*double change = Chemical_Mass[layer] - old_mass;
        /*if (Nutrient_Label == SL_Nitrate) {
            std::clog<<"CHECKING hour:"<<hour
                     <<"\tNum_S_L:"<<Number_Of_Soil_Layers
                     <<"\tL:"<<layer
                     <<"\t"<<Solute_Name[Nutrient_Label]
                     <<"\tC_M:"     <<Chemical_Mass[layer]
                     <<"\tS_C_M:"   <<Sorbed_Chemical_Mass[layer]
                     <<"\tN_L_C:"   <<New_Layer_Concentration[layer]
                     <<"\tD:"       <<D_Term[layer]
                     <<"\tC:"       <<C_Term[layer]
                     <<"\tN_L+1_C:" <<New_Layer_Concentration[layer+1]
                     <<"\tN_W_D:"   <<New_Water_Depth[layer]
                     <<std::endl;
        }*/
    }
    //Update and save chemical mass per node and chemical species for next hour
    //160325LML Soil_chemicals_profile *chemicals_prof = SoilProcessesRef.chemicals_optional;//151212
    for (int layer = 1; layer <= Number_Of_Soil_Layers; layer++) {
        switch(Nutrient_Label){
        #ifdef CROPSYST_VERSION
        case SL_Nitrate:
            chemicals/*160325LML_prof*/->set_NO3_N_mass_kg_m2(layer,Chemical_Mass[layer]);   //150915LML NEED CHECK!!!
            break;
        case SL_Ammonia:
            chemicals/*160325LML_prof*/->set_NH4_N_mass_kg_m2(layer,Chemical_Mass[layer]);    //150915LML NEED CHECK!!!
            break;
        //NYI case SL_Phosphate:
        //NYI    SoilStateRef.Layer_Phosphorus_Mass[layer] = Chemical_Mass[layer];
        //NYI    break;
        #else
        case SL_Nitrate:
            SoilStateRef.Layer_Nitrate_N_Mass[layer] = Chemical_Mass[layer];
            break;
        case SL_Ammonia:
            SoilStateRef.Layer_Ammonium_N_Mass[layer] = Chemical_Mass[layer];
            break;
        case SL_Phosphate:
            SoilStateRef.Layer_Phosphorus_Mass[layer] = Chemical_Mass[layer];
            break;
        #endif
        }
        Step_Final_Chemical_Mass += Chemical_Mass[layer];
        //RS added
        #ifndef CROPSYST_VERSION
        switch(Nutrient_Label){
        case SL_Nitrate  : SoilStateRef.Layer_Nitrate_N_Conc[layer] = New_Layer_Concentration[layer]; break;
        case SL_Ammonia   : SoilStateRef.Layer_Ammonium_N_Conc[layer] = New_Layer_Concentration[layer];break;
        case SL_Phosphate: SoilStateRef.Layer_Phosphorus_Conc[layer] = New_Layer_Concentration[layer];break;
        }
        #endif
        //end added
        if ( (Nutrient_Label == SL_Nitrate)
           ||(Nutrient_Label == SL_Ammonia))
             SoilStateRef.Count_For_Average_Concentration++;                     //151212RLN
                //151212RLN 1.0 + SoilStateRef.Count_For_Average_Concentration;
    }//Next Layer
    double Step_Chemical_Mass_Inflow = 
        std::max<double>(CascadeFlow[0] * Layer_Concentration[0],Chemical_Mass[0]); //(kg/m2/h)    //141126LML  added condition
    switch(Nutrient_Label) {
        case SL_Nitrate:
            chemicals->subtract_NO3_molecular_mass(0,Step_Chemical_Mass_Inflow * N_to_NO3_conv);
            Step_Final_Chemical_Mass += chemicals->get_NO3_N_mass_kg_m2(0);
            break;
        case SL_Ammonia:
            chemicals->subtract_NH4_molecular_mass(0,Step_Chemical_Mass_Inflow * N_to_NH4_conv);
            Step_Final_Chemical_Mass += chemicals->get_NH4_N_mass_kg_m2(0);
            break;
    }
    double Step_Chemical_Mass_Leaching = 
        Step_Initial_Chemical_Mass - Step_Final_Chemical_Mass;                   //160325LML + Step_Chemical_Mass_Inflow;
    //Step_Chemical_Mass_Leaching = std::max<double>(Step_Initial_Chemical_Mass - Step_Final_Chemical_Mass + Step_Chemical_Mass_Inflow,0.0);
    //assert(Step_Chemical_Mass_Inflow >= 0);
    /*FMS 141014
    if (!SoilProfileRef.Free_Drainage_Boundary) {
        if (Nutrient_Label.compare("NO3") == 0) SoilStateRef.Layer_Nitrate_N_Mass[Number_Of_Soil_Layers] += Step_Chemical_Mass_Leaching;
        else if (Nutrient_Label.compare("NH4") == 0) SoilStateRef.Layer_Ammonium_N_Mass[Number_Of_Soil_Layers] += Step_Chemical_Mass_Leaching;
        else if (Nutrient_Label.compare("Phosp") == 0) SoilStateRef.Layer_Phosphorus_Mass[Number_Of_Soil_Layers] += Step_Chemical_Mass_Leaching;
        Step_Final_Chemical_Mass += Step_Chemical_Mass_Leaching;
        Step_Chemical_Mass_Leaching = 0;
    }
    */
    if (Nutrient_Label == SL_Nitrate) {
        SoilStateRef.Daily_Nitrate_Leaching += Step_Chemical_Mass_Leaching;
        //150921LML SoilStateRef.Cumulative_Nitrate_Leaching += Step_Chemical_Mass_Leaching;
    }
    else if (Nutrient_Label == SL_Ammonia) {
        SoilStateRef.Daily_Ammonium_Leaching += Step_Chemical_Mass_Leaching;
        //150921LML SoilStateRef.Cumulative_Ammonium_Leaching += Step_Chemical_Mass_Leaching;
    }
    else if (Nutrient_Label == SL_Phosphate) {
        SoilStateRef.Daily_Phosphorus_Leaching += Step_Chemical_Mass_Leaching;
        //150921LML SoilStateRef.Cumulative_Phosphorus_Leaching += Step_Chemical_Mass_Leaching;
    }
    //150529 RS added
    //150529 if ((Nutrient_Label == SL_Nitrate) || (Nutrient_Label == SL_Ammonia)) {
    //150529     //kg/m2
    //150529     Sum_Solute_N_Into_Soil += Step_Chemical_Mass_Inflow;
    //150529 }


    //LML 141126 update aboveground nutrients concentration
    /*disabled 151027LML
    double tempmass = -9999.0;
    if (Nutrient_Label == SL_Nitrate) {
        tempmass =
                #ifdef CROPSYST_VERSION
                SoilStateRef.chemical->get_NO3_N_mass_kg_m2(0);
                #else
                SoilStateRef.Layer_Nitrate_N_Mass[0];
                #endif
        Chemical_Mass_Leaching_NO3 = Step_Chemical_Mass_Leaching;
    } else if (Nutrient_Label == SL_Ammonia) {
        tempmass =
                #ifdef CROPSYST_VERSION
                SoilStateRef.chemical->get_NH4_N_mass_kg_m2(0);
                #else
                SoilStateRef.Layer_Ammonium_N_Mass[0];
                #endif
        Chemical_Mass_Leaching_NH4 = Step_Chemical_Mass_Leaching;
    } else if (Nutrient_Label == SL_Phosphate) {
        tempmass =
                SoilStateRef.Layer_Phosphorus_Mass[0];
        Chemical_Mass_Leaching_Phosphorus = Step_Chemical_Mass_Leaching;
    }
    tempmass -= Step_Chemical_Mass_Inflow;
    if (tempmass < 0 && CORN::is_approximately<double>(tempmass,0.0,1e-12))
       tempmass = 0;
    assert(tempmass >= 0.0);
    if (Nutrient_Label == SL_Nitrate) {
       #ifdef CROPSYST_VERSION
       SoilStateRef.chemical->set_NO3_N_mass_kg_m2(0,tempmass);
       #else
       SoilStateRef.Layer_Nitrate_N_Mass[0] = tempmass;
       #endif
    } else if (Nutrient_Label == SL_Ammonia) {
       #ifdef CROPSYST_VERSION
       SoilStateRef.chemical->set_NH4_N_mass_kg_m2(0,tempmass);
       #else
       SoilStateRef.Layer_Ammonium_N_Mass[0] = tempmass;
       #endif
    } else if (Nutrient_Label == SL_Phosphate) {
       SoilStateRef.Layer_Phosphorus_Mass[0] = tempmass;
    }

    //end added
    */
    #ifdef CHECK_MASS_BALANCE
    BalanceItem Chemical_Balance;                                                //131002FMS
    Chemical_Balance.SetInitPool(Step_Initial_Chemical_Mass);
    Chemical_Balance.SetFinalPool(Step_Final_Chemical_Mass);
    Chemical_Balance.SetFluxIn(0);                                               //160325LML Step_Chemical_Mass_Inflow);
    Chemical_Balance.SetFluxOut(Step_Chemical_Mass_Leaching);
    if (!Chemical_Balance.IsMassBalance(1e-3)) {
        std::clog<<Solute_Name[Nutrient_Label]<<":\n";
        std::clog<<"Step_Chemical_Mass_Leaching:"   <<Step_Chemical_Mass_Leaching
                 <<"\tStep_Initial_Chemical_Mass:"  <<Step_Initial_Chemical_Mass
                 <<"\tStep_Final_Chemical_Mass:"    <<Step_Final_Chemical_Mass
                 <<"\tStep_Chemical_Mass_Inflow:"   <<Step_Chemical_Mass_Inflow
                 <<std::endl;
        Chemical_Balance.PrintMassBalanceTerms("Mass during cascade transport");
    }
    #endif
}
//______________________________________________________________________________
#ifdef MBVB_FD
void SoilChemicalTransportClass::FDChemicalTransport
(double Time_Step,std::string Nutrient_Label
#ifndef CROPSYST_VERSION
,clsManagement &Management
,clsSimulation &Simulation
#endif
)
{
    const double nu = 0.6;
    const double Water_Density = 1000; //kg/m3
    double Bulk_Density;
    double Chem_Mass_Fraction_In_Solution;
    double Chemical_Leaching;
    double Chemical_Mass_End;
    double Chemical_Mass_In_Node;
    double Chemical_Mass_Inflow_End;
    double Chemical_Mass_Start;
    double Fertigation;
    double Hourly_Prec_Irr_SnowMelt;
    double Hourly_Runoff;
    double Hourly_Ponded;
    int layer;
    double Layer_Thickness;
    double Leaching_Chem_Mass_End;
    int Node;
    //double Node_Chemical_Mass(nmax)
    //double Node_Concentration(nmax)
    double Node_Domain_Thickness;
    int Number_Of_Effective_Layers;
    int Number_Of_Nodes;
    double Old_Water_Content_Node;
    double Previous_Layer_Thickness;
    double TimeStep_Solute_Inflow;
    double TimeStep_Solute_Leaching;
    double Water_Table_Concentration;

    Number_Of_Effective_Layers = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    Number_Of_Nodes = SoilProfileRef.Number_Of_Effective_Soil_Nodes;
    Water_Table_Concentration = SoilStateRef.WT_Solute_Conc;
    Hourly_Prec_Irr_SnowMelt = SoilProcessesRef.Hourly_Prec_Irrig_SnowMelt_m * 1000.0;
    Hourly_Runoff = SoilStateRef.Hourly_Runoff_m * 1000.0;
    Hourly_Ponded = SoilStateRef.pond.get_depth()/*Hourly_Ponded_Water_m*/ * 1000.0;
    counterFDChemicalTrans ++;  //= 1 + counterFDChemicalTrans                   //140307FMS
    //hand over layer species amount to layer chemical amount
    Handover_Solute_2_Chem(Enum_Node_Or_Layer::LAYER, Nutrient_Label);

    if (ControlRef.doSpatialSimulation() 
		#ifndef CROPSYST_VERSION
		|| (Simulation.pTimeState->getFDHourlyCounter() == 0)
		#endif
		) {
        //initialize Node chemical mass, but only if (lateral-flow is simulated or at simulation start-up

        RLN this should be moved to start()
        LayerChemMass_2_NodeChemMass();
    } else {
        //if (only one cell (1D) is simulated, after the first hour node masses are used (not layer mass!)
        for (Node = 1; Node <= Number_Of_Nodes; Node++) {
                if (Nutrient_Label.compare("NO3") == 0) Node_Chemical_Mass[Node] = Node_Nitrate_Mass[Node];
                if (Nutrient_Label.compare("NH4") == 0) Node_Chemical_Mass[Node] = Node_Ammonium_Mass[Node];
                if (Nutrient_Label.compare("Phosp") == 0) Node_Chemical_Mass[Node] = Node_Phosphorus_Mass[Node];
                //if (Nutrient_Label = "Salt") { Node_Salt_Mass(Node) = Node_Chemical_Mass(Node)
        }
    }
    //calculate initial chemical mass
    Chemical_Mass_Start = calcFDChemicalMass("Node");
    //Initial chemical mass should consider only the mass of the real soil layers
    Chemical_Mass_Start -= (Node_Chemical_Mass[Number_Of_Nodes] + Node_Chemical_Mass[Number_Of_Nodes - 1]
                                            + Node_Chemical_Mass[Number_Of_Nodes - 2] / 2.0);
    #ifndef CROPSYST_VERSION
    //Fertigation (kg/m3)
    if (Nutrient_Label.compare("NO3") == 0) Fertigation = Management.pManagementState->Irrigation_NO3_Conc;
    if (Nutrient_Label.compare("NH4") == 0) Fertigation = Management.pManagementState->Irrigation_NH4_Conc;
    #endif
    //for reporting
    Initial_Chemical_Mass = Chemical_Mass_Start;
    FDFlow[0] = -SoilProcessesRef.getFlow(0) * Time_Step / Water_Density; //Flow is converted from kg/m2/s to m/h (m3H2O/m2area/h)
    if (CORN::is_approximately<double>(Hourly_Ponded,0) && CORN::is_approximately<double>(Hourly_Prec_Irr_SnowMelt,0)) {
        Node_Concentration[0] = 0;
    } else {
        //new node(0) (=surface water) concentration will be a "mix" of the old one and the incoming new water (potentially containing solutes)
        Node_Concentration[0] = (Node_Concentration[0] * (Hourly_Ponded + Hourly_Runoff)
                                 + Fertigation * Hourly_Prec_Irr_SnowMelt)
                                / (Hourly_Ponded + Hourly_Runoff + Hourly_Prec_Irr_SnowMelt);
    }
    if (SoilProfileRef.Free_Drainage_Boundary == false) {
        Node_Concentration[Number_Of_Nodes + 1] = Water_Table_Concentration;
        Node_Chemical_Mass[Number_Of_Nodes + 1] = Water_Table_Concentration * SoilProfileRef.Saturation_Water_Content[Number_Of_Nodes]
                                                  * (SoilProfileRef.Layer_Thickness_m[Number_Of_Nodes - 1] + SoilProfileRef.Layer_Thickness_m[Number_Of_Nodes]) / 2.;
    }
    for (Node = 1; Node <= Number_Of_Nodes - 2; Node++) {                        //140306FMS
        layer = Node;
        Layer_Thickness = SoilProfileRef.Layer_Thickness_m[layer];
        Previous_Layer_Thickness = SoilProfileRef.Layer_Thickness_m[layer-1];
        Node_Domain_Thickness = (Layer_Thickness + Previous_Layer_Thickness) / 2.;
        //This next two lines yield units of meter (m3 water/m2 soil)
        New_Water_Depth[Node] = (SoilStateRef.New_Upper_Water_Content[Node] * Layer_Thickness / 2.0
                                 + SoilStateRef.New_Lower_Water_Content[Node - 1] * Previous_Layer_Thickness / 2.0);
        Old_Water_Depth[Node] = (SoilStateRef.Old_Upper_Water_Content[Node] * Layer_Thickness / 2.0
                                 + SoilStateRef.Old_Lower_Water_Content[Node - 1] * Previous_Layer_Thickness / 2.0);
        //water content for the node domain at the beginning of the current time step, before FD solution for the current time step
        Old_Water_Content_Node = Old_Water_Depth[Node] / Node_Domain_Thickness;
        //NOTE!!! - Node_Chemical_Mass is the input required for this routine
        Chemical_Mass_In_Node = Node_Chemical_Mass[Node];
        if (Chemical_Mass_In_Node > 0) {
            if ((Nutrient_Label.compare("NH4") == 0) || (Nutrient_Label.compare("Phosp") == 0)) {

                //Set bulk density for Langmuir
                if (Node == 1) {
                    Bulk_Density = SoilProfileRef.get_bulk_density_g_cm3(1);
                }
                else if (Node == Number_Of_Nodes) {
                    Bulk_Density = SoilProfileRef.get_bulk_density_g_cm3(Number_Of_Effective_Layers);
                } else {
                    Bulk_Density = (SoilProfileRef.get_bulk_density_g_cm3(Node - 1) * Previous_Layer_Thickness
                                    + SoilProfileRef.get_bulk_density_g_cm3(Node) * Layer_Thickness)
                                    / (Layer_Thickness + Previous_Layer_Thickness);
                }
                //Node concentration in kg Chem/m3 water
                Node_Concentration[Node] = LangmuirSoluteEquilibriumConcentration(Nutrient_Label, Chemical_Mass_In_Node, Bulk_Density,
                                                                                  Node_Domain_Thickness, Old_Water_Content_Node,
                                                                                  Chem_Mass_Fraction_In_Solution);
                Sorbed_Chemical_Mass[Node] = Chemical_Mass_In_Node * (1 - Chem_Mass_Fraction_In_Solution);
            } else {
                Node_Concentration[Node] = Chemical_Mass_In_Node / (Node_Domain_Thickness * Old_Water_Content_Node);
                Sorbed_Chemical_Mass[Node] = 0;
            }
        } else {
            Node_Concentration[Node] = 0;
            Sorbed_Chemical_Mass[Node] = 0;
        }
        //Converted from kg/m2/s to water depth (m) equivalent (m3H2O/m2area) for the time step
        FDFlow[Node] = -SoilProcessesRef.getFlow(Node) * Time_Step / Water_Density;
    }//Next Node

    for (Node = 1; Node <= Number_Of_Nodes - 2; Node ++) {                       //140306FMS
        //Case 1: flow from current layer is downward and flow from upper layer is downward or zero
        if ((FDFlow[Node] > 0) && (FDFlow[Node - 1] > 0)) { //Roger
            A_Term[Node] = FDFlow[Node - 1] * nu;
            B_Term[Node] = -New_Water_Depth[Node] - FDFlow[Node] * nu;
            C_Term[Node] = 0.;
            //Roger
            if (Node == 1) {
                D_Term[Node] = -Old_Water_Depth[Node] * Node_Concentration[Node]
                            + FDFlow[Node] * (1. - nu) * Node_Concentration[Node]
                            - FDFlow[Node - 1] * Node_Concentration[Node - 1];
            } else {
                D_Term[Node] = -Old_Water_Depth[Node] * Node_Concentration[Node]
                           + FDFlow[Node] * (1. - nu) * Node_Concentration[Node]
                           - FDFlow[Node - 1] * (1. - nu) * Node_Concentration[Node - 1];
            }
            //This is to avoid a negative chemical mass
            if (D_Term[Node] > 0) {
                Node_Concentration[Node] = Node_Concentration[Node] - D_Term[Node] / (FDFlow[Node] * (1. - nu));
                D_Term[Node] = 0;
            }
        }
        //Case 2: flow from current layer is downward and flow from upper layer is upward
        if ((FDFlow[Node] > 0) && (FDFlow[Node - 1] <= 0)) { //Roger
            A_Term[Node] = 0.;
            B_Term[Node] = -New_Water_Depth[Node] + nu * (FDFlow[Node - 1] - FDFlow[Node]);
            C_Term[Node] = 0.;
            D_Term[Node] = -Old_Water_Depth[Node] * Node_Concentration[Node]
                           + FDFlow[Node] * (1. - nu) * Node_Concentration[Node]
                           - FDFlow[Node - 1] * (1. - nu) * Node_Concentration[Node];
            //This is to avoid a negative chemical mass
            if (D_Term[Node] > 0) {
                Node_Concentration[Node] -= D_Term[Node] / (FDFlow[Node] * (1. - nu));
                D_Term[Node] = 0;
            }
        }
        //Case 3: flow from current layer is upward and flow from upper layer is downward or zero
        if ((FDFlow[Node] < 0) && (FDFlow[Node - 1] > 0)) { //Roger
            A_Term[Node] = FDFlow[Node - 1] * nu;
            B_Term[Node] = -New_Water_Depth[Node];
            C_Term[Node] = -FDFlow[Node] * nu;
            //Roger
            if (Node == 1) {
                D_Term[Node] = -Old_Water_Depth[Node] * Node_Concentration[Node]
                               + FDFlow[Node] * (1. - nu) * Node_Concentration[Node + 1]
                               - FDFlow[Node - 1] * Node_Concentration[Node - 1];
            } else {
                D_Term[Node] = -Old_Water_Depth[Node] * Node_Concentration[Node]
                               + FDFlow[Node] * (1. - nu) * Node_Concentration[Node + 1]
                               - FDFlow[Node - 1] * (1. - nu) * Node_Concentration[Node - 1];
            }

            //This is to avoid a negative chemical mass
            if (D_Term[Node] > 0) {
                Node_Concentration[Node + 1] -= D_Term[Node] / (FDFlow[Node] * (1. - nu));
                D_Term[Node] = 0;
            }
        }
        //Case 4: flow from current layer is upward and flow from upper layer is upward
        if ((FDFlow[Node] < 0) && (FDFlow[Node - 1] <= 0)) { //Roger
            A_Term[Node] = 0;
            B_Term[Node] = -New_Water_Depth[Node] + FDFlow[Node - 1] * nu;
            C_Term[Node] = -FDFlow[Node] * nu;
            D_Term[Node] = -Old_Water_Depth[Node] * Node_Concentration[Node]
                           + FDFlow[Node] * (1. - nu) * Node_Concentration[Node + 1]
                           - FDFlow[Node - 1] * (1. - nu) * Node_Concentration[Node];

            //This is to avoid a negative chemical mass
            if (D_Term[Node] > 0) {
                Node_Concentration[Node + 1] -= D_Term[Node] / (FDFlow[Node] * (1. - nu));
                D_Term[Node] = 0;
            }
        }
    }//Next Node
    //Resolution of the system by Thomas algorithm. Compute new concentration
    for (Node = 1; Node <= (Number_Of_Nodes - 2/*1*/); Node++) {                 //140306FMS

        // Condition added to avoid division by 0
        if (B_Term[Node] < 1.0e-10) B_Term[Node] = 1.0e-10;
        C_Term[Node] /= B_Term[Node];
        D_Term[Node] /= B_Term[Node];
        B_Term[Node + 1] -= A_Term[Node + 1] * C_Term[Node];
        D_Term[Node + 1] -= A_Term[Node + 1] * D_Term[Node];
    }

    // Condition added to avoid division by 0
    if (CORN::is_approximately<double>(B_Term[Number_Of_Nodes],0)) B_Term[Number_Of_Nodes] = 1e-12;

    New_Node_Concentration[Number_Of_Nodes] = D_Term[Number_Of_Nodes] / B_Term[Number_Of_Nodes];

    Node_Chemical_Mass[Number_Of_Nodes] = Sorbed_Chemical_Mass[Number_Of_Nodes]
                    + New_Node_Concentration[Number_Of_Nodes] * New_Water_Depth[Number_Of_Nodes];

    for (Node = (Number_Of_Nodes - 2/*1*/);Node >= 1; Node--) {                  //140306
        New_Node_Concentration[Node] = D_Term[Node] - C_Term[Node] * New_Node_Concentration[Node + 1];
        Node_Concentration[Node] = New_Node_Concentration[Node];
        Node_Chemical_Mass[Node] = Sorbed_Chemical_Mass[Node] + Node_Concentration[Node] * New_Water_Depth[Node];
        //Sorbed_Chemical_Mass (kg(m2), Node_Concentration (kg/m3), Node New_Water_Depth (m)
    }

    //Update and save chemical mass per node and chemical species for next hour
    Handover_Chem_2_Solute(Enum_Node_Or_Layer::NODE, Nutrient_Label);
    //calculate final chemical mass
    Chemical_Mass_End = calcFDChemicalMass("Node");
    //chemical mass should consider only real soil layers
    Chemical_Mass_End -= (Node_Chemical_Mass[Number_Of_Nodes]
                        + Node_Chemical_Mass[Number_Of_Nodes - 1]
                        + Node_Chemical_Mass[Number_Of_Nodes - 2] / 2.);

    //flow in m/h, Node concentration in kg/m3 water, chemical mass inflow kg/m2
    Chemical_Mass_Inflow_End = FDFlow[0] * Node_Concentration[0];
    Leaching_Chem_Mass_End = Chemical_Mass_Start - Chemical_Mass_End + Chemical_Mass_Inflow_End;

    //Different chemical masses for reporting
    TimeStep_Solute_Inflow = Chemical_Mass_Inflow_End;
    TimeStep_Solute_Leaching = Leaching_Chem_Mass_End;
    Final_Chemical_Mass = Chemical_Mass_End;

    //update chemicals for lateral flow routine (and for outputs!), i.e. convert node mass to layer mass
    NodeChemMass_2_LayerChemMass();
    //lateral flow needs LayerChemicalConcentration - here it will be handed over and sorted by species
    LayerChemMass_2_LayerChemConc(Nutrient_Label);

    //turn layer chemical mass into respective species properties
    Handover_Chem_2_Solute(Enum_Node_Or_Layer::LAYER, Nutrient_Label);

    if (Nutrient_Label.compare("NO3") == 0) {
        SoilStateRef.Daily_Nitrate_Leaching += TimeStep_Solute_Leaching;
        SoilStateRef.Daily_Nitrate_N_Fertigation += TimeStep_Solute_Inflow;
        //for balancing only
        TimeStep_Initial_Nitrate_In_Profile = Chemical_Mass_Start;
        TimeStep_End_Nitrate_In_Profile = Chemical_Mass_End;
    }

    if (Nutrient_Label.compare("NH4") == 0) {
        SoilStateRef.Daily_Ammonium_Leaching += TimeStep_Solute_Leaching;
        SoilStateRef.Daily_Ammonium_N_Fertigation += TimeStep_Solute_Inflow;
    }

    if (Nutrient_Label.compare("Phosp") == 0) {
        SoilStateRef.Daily_Phosphorus_Leaching += TimeStep_Solute_Leaching;
        //add phosphorous fertigation, if (needed here
    }
}
#endif
//______________________________________________________________________________
//Purpose:   Given a data set consisting of a list of x values
//           and y values, this function will smoothly interpolate
//           a resulting output (y) value from a given input (x) value
double SoilChemicalTransportClass::CubicSpline(int doubles,
  std::vector<double> &xin,std::vector<double> &yin,double X_for_which_2find_Y)
{
    //doubles is the Ubound of array xin
    //////////////////////////////////////////////////////////////////////////////
    // values are populated
    //////////////////////////////////////////////////////////////////////////////
    int N = doubles;
    yt[1] = 0;
    U[1] = 0;
    for (int i = 2; i <= N - 1; i++) {
        double sig = (xin[i] - xin[i-1]) / (xin[i+1] - xin[i-1]);
        double p = sig * yt[i-1] + 2;
        yt[i] = (sig - 1) / p;
        U[i] = (yin[i+1] - yin[i]) / (xin[i+1] - xin[i]) - (yin[i] - yin[i-1]) / (xin[i] - xin[i-1]);
        U[i] = (6.0 * U[i] / (xin[i+1] - xin[i-1]) - sig * U[i-1]) / p;
    }
    double qn = 0;
    double un = 0;
    yt[N] = (un - qn * U[N-1]) / (qn * yt[N-1] + 1);
    for (int k = N - 1; k >= 1; k--) {
        yt[k] = yt[k] * yt[k + 1] + U[k];
    }
    ////////////////////////////////////////
    //now eval spline at one point
    //////////////////////////////////////////
    // first find correct interval
    int klo(1);
    int khi(N);
    int k(N);
    while (k > 1) {
        k = khi - klo;
        if (xin[k] > X_for_which_2find_Y) khi = k;
        else klo = k;
        k = khi - klo;
    };
    //RS added - preventing negative or possitive values in-between two y-values equal zero
    double cubic_spline(0.0);
    if (CORN::is_approximately<double>(yin[khi],0.0,1e-12) && 
        CORN::is_approximately<double>(yin[klo],0.0,1e-12)) 
        cubic_spline = 0;
    else {
        double h = xin[khi] - xin[klo];
        double a = (xin[khi] - X_for_which_2find_Y) / h;
        double b = (X_for_which_2find_Y - xin[klo]) / h;
        cubic_spline = a * yin[klo] + b * yin[khi]
                + ((a * a * a - a) * yt[klo] + (b *b * b - b) * yt[khi]) * (h * h) / 6.;
    }
    //RS added to avoid negative values
    if (cubic_spline < 0.0) cubic_spline = 0.0;
    return cubic_spline;
}
//______________________________________________________________________________
void SoilChemicalTransportClass::LayerChemMass_2_LayerChemConc(Solute Nutrient_Label)
{
    const int Number_Of_Effective_Layers = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    for (int L = 1; L <= Number_Of_Effective_Layers - 2; L++) {                  //140306FMS
        //140606LML  Layer_Chemical_Concentration[L] = Layer_Chemical_Mass[L] / (SoilProfileRef.Layer_Thickness_m[L] * SoilStateRef.xHourly_Water_Content[L]);
        Layer_Chemical_Concentration[L] = 
                Layer_Chemical_Mass[L] 
                / (SoilProfileRef.get_thickness_m(L) * SoilStateRef.get_liquid_water_content_volumetric(L)); // .xHourly_Water_Content[L]);
        /*std::cout<<Nutrient_Label<<" L:"<<L
                <<" Layer_Chemical_Concentration:"<<Layer_Chemical_Concentration[L]
                   <<std::endl;*/
        switch(Nutrient_Label){
        case SL_Nitrate:
            SoilStateRef.Layer_Nitrate_N_Conc[L] = Layer_Chemical_Concentration[L];
            break;
        case SL_Ammonia:
            SoilStateRef.Layer_Ammonium_N_Conc[L] = Layer_Chemical_Concentration[L];
            break;
        case SL_Phosphate:
            SoilStateRef.Layer_Phosphorus_Conc[L] = Layer_Chemical_Concentration[L];
            break;
        default:
            std::clog<<"Nutrient not exist!";
            assert(false);
        }
    }
    Layer_Chemical_Concentration[0] = Node_Concentration[0];
    switch(Nutrient_Label){
    case SL_Nitrate:
        SoilStateRef.Layer_Nitrate_N_Conc[0] = Layer_Chemical_Concentration[0];
        break;
    case SL_Ammonia:
        SoilStateRef.Layer_Ammonium_N_Conc[0] = Layer_Chemical_Concentration[0];
        break;
    case SL_Phosphate:
        SoilStateRef.Layer_Phosphorus_Conc[0] = Layer_Chemical_Concentration[0];
        break;
    }
}
//______________________________________________________________________________
void SoilChemicalTransportClass::LayerChemMass_2_NodeChemMass()
{
    //this is the latest attempt to convert from layer to nodes,
    //this time using cubic spline function to interpolate
    const int Number_Of_Effective_Layers = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    const int Number_Of_Nodes = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    double cum_SoilLayerThickness(0.0);
    double Total_LayerChemMass(0.0);
    for (int L = 1;L <= Number_Of_Effective_Layers - 2; L++) {
        Range_LayerChemMass[L] = Layer_Chemical_Mass[L];
        Total_LayerChemMass += Layer_Chemical_Mass[L];
        Range_Layer_depth[L] = cum_SoilLayerThickness + SoilProfileRef.get_thickness_m(L) / 2.0;
        cum_SoilLayerThickness += SoilProfileRef.get_thickness_m(L);
    }
    double Total_NodeChemMass(0.0);
    for (int N = 1; N <= Number_Of_Nodes - 2; N++) {
        int L = N;
        if (N == 1) Node_Depth[N] = 0;
        else Node_Depth[N] = Range_Layer_depth[L-1] + SoilProfileRef.get_thickness_m(L-1) / 2.0;
        //use cubic spline to calculate Node Chemical mass
        Node_Chemical_Mass[N] = CubicSpline(Number_Of_Effective_Layers - 2, 
                                            Range_Layer_depth, 
                                            Range_LayerChemMass, 
                                            Node_Depth[N]);
        //No longer required - is taken care of directly in the spline function:
        //    mass should not be negative
        //    Node_Chemical_Mass[N] = WorksheetFunction.Max(0, Node_Chemical_Mass[N])
        if ((N == 1) || (N == Number_Of_Nodes - 2)) 
            Node_Chemical_Mass[N] = Node_Chemical_Mass[N] / 2.0;
        //add up mass
        Total_NodeChemMass += Node_Chemical_Mass[N];
    }
    if (CORN::is_approximately<double>(Total_NodeChemMass,0.0,1e-12)) 
        Total_NodeChemMass = 0.001;                                              //140226FMS
    if (CORN::is_approximately<double>(Total_LayerChemMass,0.0,1e-12)) 
        Total_LayerChemMass = 0.001;                                             //140226FMS
    //calculate difference between cubic-spline-derived node mass and layer mass
    double Diff_Layer_Node_Mass = Total_LayerChemMass - Total_NodeChemMass;
    double Total_NodeChemMass_w(0.0);                                            //140306FMS
    //adjust node mass (for mass balance accuracy)
    for (int N = 1;N <= Number_Of_Nodes - 2; N++) {
        Node_Chemical_Mass[N] += Diff_Layer_Node_Mass * (Node_Chemical_Mass[N] / Total_NodeChemMass);
        if (Node_Chemical_Mass[N] / Total_LayerChemMass * 100 < -0.01) {
            nrerror("Node_Chemical_Mass cannot be negnitive");
        }
        Node_Chemical_Mass[N] = std::max<double>(0, Node_Chemical_Mass[N]);
        Total_NodeChemMass_w += Node_Chemical_Mass[N];                           //140306FMS
    }
    Node_Chemical_Mass[Number_Of_Nodes - 2] = 
            Node_Chemical_Mass[Number_Of_Nodes - 2] * 2.0;
    Diff_Layer_Node_Mass = Total_LayerChemMass - Total_NodeChemMass_w;           //140306FMS
    //TODO LML 150112 test only?
    //'If Abs(Diff_Layer_Node_Mass) > 0.0000001 Then Stop '                      //140306FMS
}
//______________________________________________________________________________
void SoilChemicalTransportClass::NodeChemMass_2_LayerChemMass()
{
    //this is the latest attempt to convert from nodes to layer, this time using cubic spline function to interpolate
    const int Number_Of_Effective_Layers = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    const int Number_Of_Nodes = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    double cum_SoilLayerThickness(0.0);
    double Total_LayerChemMass(0.0);
    Range_Node_depth[1] = 0;
    double Total_NodeChemMass = Node_Chemical_Mass[1];
    //for smoother spline function, use double the mass for first and "last" (=real layer +1) node
    Range_NodeChemMass[1] = Node_Chemical_Mass[1] * 2;
    for (int N = 2;N <= Number_Of_Nodes - 2; N++) {
        int L = N;
        if (N == Number_Of_Nodes)
            Range_NodeChemMass[N] = Node_Chemical_Mass[N] * 2.0;
        else
            Range_NodeChemMass[N] = Node_Chemical_Mass[N];
        cum_SoilLayerThickness += SoilProfileRef.get_thickness_m(L);
        Range_Node_depth[N] = cum_SoilLayerThickness;
        Total_NodeChemMass += Node_Chemical_Mass[N]; //this is the true node mass (first and last layer not doubled!)
    }
    //reduce total Node chemical mass by half the amount of chemicals in last considered node
    Total_NodeChemMass -= Node_Chemical_Mass[Number_Of_Nodes - 2] / 2.0;
    for (int L = 1; L <= Number_Of_Effective_Layers - 2; L++) {
        //define depth of layers
        Layer_Depth[L] = Range_Node_depth[L + 1] - SoilProfileRef.get_thickness_m(L) / 2.0;
        //use cubic spline to calculate Layer Chemical mass
        Layer_Chemical_Mass[L] = CubicSpline(Number_Of_Nodes - 2,Range_Node_depth, Range_NodeChemMass, Layer_Depth[L]);
        //add up mass
        Total_LayerChemMass += Layer_Chemical_Mass[L];
    }
    if (CORN::is_approximately<double>(Total_NodeChemMass,0.0,1e-12)) 
        Total_NodeChemMass = 0.001;                                              //140226FMS
    if (CORN::is_approximately<double>(Total_LayerChemMass,0.0,1e-12)) 
        Total_LayerChemMass = 0.001;                                             //140226FMS
    //calculate difference between cubic-spline-derived layer mass and node mass
    double Diff_Node_Layer_Mass = (Total_NodeChemMass - Total_LayerChemMass);
    double Total_LayerChemMass_w = 0.0;                                          //140306FMS
    for (int L = 1; L <= Number_Of_Effective_Layers - 2; L++) {
        Layer_Chemical_Mass[L] += Diff_Node_Layer_Mass * (Layer_Chemical_Mass[L] / Total_LayerChemMass);
        if (Layer_Chemical_Mass[L] / Total_NodeChemMass * 100 < -0.01) {
             nrerror("Layer_Chemical_Mass cannot be negnitive");
        }
        Layer_Chemical_Mass[L] = std::max<double>(0, Layer_Chemical_Mass[L]);
        Total_LayerChemMass_w += Layer_Chemical_Mass[L];                         //140306FMS
    }
    Diff_Node_Layer_Mass = (Total_NodeChemMass - Total_LayerChemMass_w);         //140306FMS
    //TODO 150112LML  test only?
}
//______________________________________________________________________________
void SoilChemicalTransportClass::Handover_Chem_2_Solute(Enum_Node_Or_Layer Node_or_Layer,Solute Nutrient_Label)
{
    //use String "Node", "Layer" or "Both" to identify which handover to initiate
    //const int Number_Of_Layers = SoilProfileRef.NumberOfLayers();
    const int Number_Of_Nodes = SoilProfileRef.Number_Of_Effective_Soil_Nodes;
    if ((Node_or_Layer == /*Enum_Node_Or_Layer::*/NODE) ||
        (Node_or_Layer == /*Enum_Node_Or_Layer::*/LAYER)) {
        for (int Node = 1; Node <= Number_Of_Nodes - 2; Node++)                  //140306FMS
        {   float64 chemical_mass_node =  Node_Chemical_Mass[Node];              //151212RLN
            switch(Nutrient_Label){
            case SL_Nitrate:  Node_Nitrate_Mass   [Node] = chemical_mass_node; break;
            case SL_Ammonia:   Node_Ammonium_Mass  [Node] = chemical_mass_node; break;
            case SL_Phosphate:Node_Phosphorus_Mass[Node] = chemical_mass_node; break;
            case SL_Salt:     Node_Salt_Mass      [Node] = chemical_mass_node; break;
            default:
                std::clog<<"Nutrient type doesn't exist!";
                assert(false);
            }
        }
    }
    //FMS Mar 7, 2014
    //if ((Node_or_Layer.compare("Layer") == 0) || (Node_or_Layer.compare("Both") == 0)) {
    //    for (L = 1; L <= Number_Of_Layers; L++) {
    //        if (Nutrient_Label.compare("NO3") == 0) SoilStateRef.Layer_Nitrate_N_Mass[L] = Layer_Chemical_Mass[L];
    //        if (Nutrient_Label.compare("NH4") == 0) SoilStateRef.Layer_Ammonium_N_Mass[L] = Layer_Chemical_Mass[L];
    //        if (Nutrient_Label.compare("Phosp") == 0) SoilStateRef.Layer_Phosphorus_Mass[L] = Layer_Chemical_Mass[L];
    //        if (Nutrient_Label.compare("Salt") == 0) Layer_Salt_Mass[L] = Layer_Chemical_Mass[L];
    //    }
    //}
}
//______________________________________________________________________________
void SoilChemicalTransportClass::Handover_Solute_2_Chem(Enum_Node_Or_Layer Node_or_Layer,
  Solute Nutrient_Label)
{
    //use String "Node", "Layer" or "Both" to identify which handover to initiate
    const int Number_Of_Layers = SoilProfileRef.NumberOfLayers();
    const int Number_Of_Nodes = SoilProfileRef.Number_Of_Effective_Soil_Nodes;
    if ((Node_or_Layer == /*Enum_Node_Or_Layer::*/NODE) ||
        (Node_or_Layer == /*Enum_Node_Or_Layer::*/BOTH)) {
        for (int Node = 1; Node <= Number_Of_Nodes; Node++) {
            switch(Nutrient_Label){
            case SL_Nitrate:  Node_Chemical_Mass[Node] = Node_Nitrate_Mass[Node];   break;
            case SL_Ammonia:   Node_Chemical_Mass[Node] = Node_Ammonium_Mass[Node];  break;
            case SL_Phosphate:Node_Chemical_Mass[Node] = Node_Phosphorus_Mass[Node];break;
            default:
                std::clog<<"Nutrient doesn't exist!"
                         <<__FILE__
                         <<__LINE__
                         <<std::endl;
                assert(false);
            }
        }
    }
    if ((Node_or_Layer == /*Enum_Node_Or_Layer::*/LAYER) ||
        (Node_or_Layer == /*Enum_Node_Or_Layer::*/BOTH))
    {
        Soil_chemicals_profile *chemical = SoilStateRef.chemicals_optional;      //151212RLN
        for (int L = 1; L <= Number_Of_Layers; L++) {
            switch(Nutrient_Label){
            #ifdef CROPSYST_VERSION
            case SL_Nitrate:  Layer_Chemical_Mass[L] = chemical->get_NO3_N_mass_kg_m2(L);    break; //151212RLN
            case SL_Ammonia:   Layer_Chemical_Mass[L] = chemical->get_NH4_N_mass_kg_m2(L);    break; //151212RLN
            #else
            case SL_Nitrate:  Layer_Chemical_Mass[L] = SoilStateRef.Layer_Nitrate_N_Mass[L]; break;
            case SL_Ammonia:   Layer_Chemical_Mass[L] = SoilStateRef.Layer_Ammonium_N_Mass[L];break;
            #endif
            case SL_Phosphate:Layer_Chemical_Mass[L] = SoilStateRef.Layer_Phosphorus_Mass[L];break;
            default:
                std::clog<<"Nutrient doesn't exist!"
                        <<__FILE__
                        <<__LINE__
                        <<std::endl;
                assert(false);                
            }
            //Step_Initial_Chemical_Mass = Step_Initial_Chemical_Mass + Layer_Chemical_Mass(Layer)
        }
    }
}
//______________________________________________________________________________
void SoilChemicalTransportClass::LayerChemicalConc_2_Mass()
{
    //converts solutes in water (kg/m3 water; = Layer_Chemical_Concentration) to solutes in layer (kg/m2; = Layer_Chemical_Mass)
    //water content (m/m), soil layer thickness (m)
    const int Number_Of_Effective_Layers = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    for (int L = 1; L <= Number_Of_Effective_Layers; L++) {
        Layer_Chemical_Mass[L] = 
                Layer_Chemical_Concentration[L] 
                * SoilStateRef.get_liquid_water_content_volumetric(L) 
                * SoilProfileRef.get_thickness_m(L);
    }

}
//______________________________________________________________________________
double SoilChemicalTransportClass::calcFDChemicalMass(Enum_Node_Or_Layer Node_or_Layer)
{
    const int Number_Of_Nodes = SoilProfileRef.Number_Of_Effective_Soil_Nodes;
    const int Number_Of_Effective_Layers = SoilProfileRef.Number_Of_Effective_Soil_Layers;
    double Chemical_Mass(0.0);
    if (Node_or_Layer == /*Enum_Node_Or_Layer::*/NODE) {
        for (int Node = 1;Node <= Number_Of_Nodes - 2; Node++) {                 //140306FMS
            Chemical_Mass += Node_Chemical_Mass[Node];
        }
    } else if (Node_or_Layer == /*Enum_Node_Or_Layer::*/LAYER) {
        for (int L = 1; L <= Number_Of_Effective_Layers - 2; L++) {              //140306FMS
            Chemical_Mass += Layer_Chemical_Mass[L];
        }
    }
    return Chemical_Mass;
}
//______________________________________________________________________________
double SoilChemicalTransportClass::LangmuirSoluteEquilibriumConcentration(Solute Nutrient_Label,
  double Chemical_Mass, double Soil_Bulk_Density, double Layer_Thickness,
  double Volumetric_Water_Content, double &Chem_Mass_Fraction_In_Solution)
{
    const double Water_Density = 1000.0; //kg/m3
    //Units
    //Soil_Bulk_Density (g soil / cm3 soil)
    //Volumetric_Water_Content (m3 water / m3 soil)
    //K (kg water/kg solute)
    //Q (kg solute/kg soil)
    //w is the gravimetric water content (kg water/kg soil).
    //[S] is salt in solution (kg salt/kg water)
    //XS is sorbed salt(kg salt/kg soil)
    //S is total salt mass, sorbed and in solution (kg salt/kg soil)  S=XS + w[S]
    double k(0.0);
    double Q(0.0);
    switch(Nutrient_Label){
    case SL_Ammonia:
        k = 2000.;
        Q = 0.003;
        break;
    case SL_Phosphate:
        k = 300000.;
        Q = 0.0002;
        break;
    default:
        std::clog<<"Nutrient not exist!";
        assert(false);
    }

    //1000 converts g/cm3 to kg/m3
    double w = Volumetric_Water_Content 
               * Water_Density 
               / (Soil_Bulk_Density * 1000.0); //(kg-H2O/kg-soil) 1000 converts g/cm3 to kg/m3
    double s = std::max<double>(Chemical_Mass 
                                / (Soil_Bulk_Density * 1000.0 * Layer_Thickness),
                                1.e-12); //(kg-chemical/kg-soil) 1000 converts g/cm3 to kg/m3
    double a = w * k;
    double b = k * Q + w - k * s;
    double c = -s;
    //Units: kg chemical/kg water
    double Concentration_kgChem_per_kgH2O(0.0);
    if (a > 1.e-12)                                                              //140911LML
        Concentration_kgChem_per_kgH2O = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    else Concentration_kgChem_per_kgH2O = 0.0;                                   //140911LML
    assert(Concentration_kgChem_per_kgH2O >= 0.0);                               //140911LML
    Chem_Mass_Fraction_In_Solution = Concentration_kgChem_per_kgH2O * w / s;
    //Converted from kgChem/kg Soil to kgChem/m3 water
    return Concentration_kgChem_per_kgH2O * Water_Density;
}
//______________________________________________________________________________
#endif
#endif
