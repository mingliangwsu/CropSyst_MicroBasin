#include "soilomandresiduemasterclass.h"
#include "util/pubtools.h"
#include <iostream>
#ifdef CHECK_MASS_BALANCE
#include "control/balanceitem.h"
#endif
//______________________________________________________________________________
SoilOMAndResidueMasterClass::SoilOMAndResidueMasterClass
(SoilProfileClass          &_SoilProfileRef
,SoilStateClass            &_SoilStateRef
,OrganicResidueClass       &_OrganicResidueRef
,OrganicResidueStateClass  &_OrganicResidueStateRef
,clsSoil                   &_SoilRef
,const CORN::Date          &_today)                                              //150630RLN
:SoilProfileRef(_SoilProfileRef)
,SoilStateRef(_SoilStateRef)
,OrganicResidueRef(_OrganicResidueRef)
,OrganicResidueStateRef(_OrganicResidueStateRef)
,SoilRef(_SoilRef)
,today(_today)                                                                   //150630RLN
{
    const int maxlayer = SoilProfileRef.NumberOfLayers() + 5;
    parrLayer_SOM_Pools = new SoilOrganicCarbonClass[maxlayer];
}
//______________________________________________________________________________
SoilOMAndResidueMasterClass::~SoilOMAndResidueMasterClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~SoilOMAndResidueMasterClass:"<<std::endl;
#endif
    delete[] parrLayer_SOM_Pools;
#ifdef Destruct_Monitor
    std::cout<<"~SoilOMAndResidueMasterClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void SoilOMAndResidueMasterClass::DailyProcess(clsSimulation &Simulation, 
DebugStateClass &DebugState)
{
    const int NL = SoilProfileRef.NumberOfLayers();
    const int doy = Simulation.pTimeState->getToday().get_DOY();
    //Last_DOY_Of_Previous_Year = OverallControl.LastDOYOfPreviousYear
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_TotalC,bal_OrgN,bal_InorgN;
    bal_TotalC.SetInitPool(getTotalOrganicCarbonMass());
    bal_OrgN.SetInitPool(getTotalOrganicNitrogenMass());
    bal_InorgN.SetInitPool(SoilStateRef.getProfileNH4NMass() + SoilStateRef.getProfileNO3NMass());
    #endif
    double Profile_SOM_Nitrogen_Mineralization = 0;
    double Profile_SOM_Carbon_Balance = 0;
    double Profile_SOM_Nitrogen_Balance = 0;
    double Profile_SOM_Carbon_Mass = 0;
    double Profile_SOM_Nitrogen_Mass = 0;
    //double Profile_Decomposed_SOM_Carbon = 0;
    //double Profile_Decomposed_SOM_Nitrogen = 0;
    double Profile_SOM_Lost_As_CO2 = 0;     //(kgC/m2)
    double Profile_Residue_Lost_As_CO2 = 0; //(kgC/m2)
    double Profile_Ammonium_N_Mass_Immobilization = 0;
    double Profile_Nitrate_N_Mass_Immobilization = 0;
    double Profile_SOM_N_Mineralized_Mass = 0;
    double Profile_Residue_N_Mineralized_Mass = 0;
    /*FMS Apr 17, 2015 Deleted those variables
    double Top_5cm_Soil_Carbon_Mass = 0;
    double Top_30cm_Soil_Carbon_Mass = 0;
    double Top_60cm_Soil_Carbon_Mass = 0;
    double Top_5cm_Microbial_Carbon_Mass = 0;
    double Top_30cm_Microbial_Carbon_Mass = 0;
    double Top_60cm_Microbial_Carbon_Mass = 0;
    */
    double Profile_Microbial_Carbon_Mass = 0;
    /*FMS Apr 17, 2015 Deleted those variables
    double Top_5cm_Labile_Carbon_Mass = 0;
    double Top_30cm_Labile_Carbon_Mass = 0;
    double Top_60cm_Labile_Carbon_Mass = 0;
    */
    double Profile_Labile_Carbon_Mass = 0;
    /*FMS Apr 17, 2015 Deleted those variables
    double Top_5cm_Metastable_Carbon_Mass = 0;
    double Top_30cm_Metastable_Carbon_Mass = 0;
    double Top_60cm_Metastable_Carbon_Mass = 0;
    */
    double Profile_Metastable_Carbon_Mass = 0;
    /*FMS Apr 17, 2015 Deleted those variables
    double Top_5cm_Passive_Carbon_Mass = 0;
    double Top_30cm_Passive_Carbon_Mass = 0;
    double Top_60cm_Passive_Carbon_Mass = 0;
    */
    double Profile_Passive_Carbon_Mass = 0;
    /*FMS Apr 17, 2015 Deleted those variables
    double Top_5cm_N_Immobilization_Mass = 0;
    double Top_30cm_N_Immobilization_Mass = 0;
    double Top_60cm_N_Immobilization_Mass = 0;
    double Top_5cm_N_Mineralization_Mass = 0;
    double Top_30cm_N_Mineralization_Mass = 0;
    double Top_60cm_N_Mineralization_Mass = 0;
    */
    ////Determine any pool mixing due to tillage
    ////Call OrganicCarbonMixingDueToTillage(SoilParameters, ManagementState, SoilProfile, SoilState)
    ////Calculate potential decomposition and nitrogen immobilization demand for all organic residue pools
    OrganicResidueRef.PotentialResidueDecomposition(Simulation);
    double Soil_Depth(0);
    for (int layer = 1; layer <= NL; layer++) {
        double Layer_Thickness = SoilProfileRef.get_thickness_m(layer);
        Soil_Depth += Layer_Thickness;
        double Total_N_Immobilization_Demand = 0;
        double Profile_Residue_N_Mineralization = 0;
        ////Calculate potential decomposition, nitrogen mineralization, and nitrogen immobilization demand for all soil organic matter pools
        double SOM_Nitrogen_Immobilization_Demand = 0;
        double SOM_Nitrogen_Mineralization = 0;
        parrLayer_SOM_Pools[layer].PotentialDecompositionAndMineralization(layer,
                                        SOM_Nitrogen_Immobilization_Demand, SOM_Nitrogen_Mineralization,
                                        Simulation, SoilRef);
        Total_N_Immobilization_Demand += SOM_Nitrogen_Immobilization_Demand;
        Profile_SOM_Nitrogen_Mineralization += SOM_Nitrogen_Mineralization;
        ////Add residue pools nitrogen mineralization and immobilization demand
        Total_N_Immobilization_Demand += OrganicResidueStateRef.Residue_Nitrogen_Immobilization_Demand[layer];
        double Residue_Nitrogen_Mineralization = OrganicResidueStateRef.Residue_Nitrogen_Mineralization[layer];
        Profile_Residue_N_Mineralization += Residue_Nitrogen_Mineralization;
        //Calculate immobilization of soil mineral nitrogen
        double Nitrate_N_Mass_Immobilized(0);
        double Ammonium_N_Mass_Immobilized(0);
        double Total_Nitrogen_Immobilization(0);
        double Decomposition_Reduction_Factor(1);
        if (/*150630 SoilRef.ControlRef.*/today.get_DOY() == 290) {
            int debug = 1;
        }
        if (Total_N_Immobilization_Demand > 0) {
            double Nitrogen_Deficit_For_Immobilization = Total_N_Immobilization_Demand;
            //Check if enough soil NH4 is available for immobilization
            if (Nitrogen_Deficit_For_Immobilization < SoilStateRef.Layer_Ammonium_N_Mass[layer]) {
                Ammonium_N_Mass_Immobilized = Nitrogen_Deficit_For_Immobilization;
                Nitrogen_Deficit_For_Immobilization = 0;
            } else {
                Ammonium_N_Mass_Immobilized = SoilStateRef.Layer_Ammonium_N_Mass[layer];
                Nitrogen_Deficit_For_Immobilization -= Ammonium_N_Mass_Immobilized;
            }
            //If nitrogen immobilization demand remains positive, check if enough soil NO3 is available for immobilization
            if (Nitrogen_Deficit_For_Immobilization > 0) {
                if (Nitrogen_Deficit_For_Immobilization < SoilStateRef.Layer_Nitrate_N_Mass[layer]) {
                    Nitrate_N_Mass_Immobilized = Nitrogen_Deficit_For_Immobilization;
                    Nitrogen_Deficit_For_Immobilization = 0;
                } else {
                    Nitrate_N_Mass_Immobilized = SoilStateRef.Layer_Nitrate_N_Mass[layer];
                    Nitrogen_Deficit_For_Immobilization -= Nitrate_N_Mass_Immobilized;
                }
            }
            //If not enough soil mineral nitrogen is available to support immobilization demand,
            //then reduce the amount of decomposition
            Decomposition_Reduction_Factor = (Total_N_Immobilization_Demand
                    - Nitrogen_Deficit_For_Immobilization) / Total_N_Immobilization_Demand;
            Total_Nitrogen_Immobilization = Nitrate_N_Mass_Immobilized + Ammonium_N_Mass_Immobilized;

        } else {
            Nitrate_N_Mass_Immobilized = 0;
            Ammonium_N_Mass_Immobilized = 0;
            Total_Nitrogen_Immobilization = 0;
            Decomposition_Reduction_Factor = 1;
        }
        //Register decomposition reduction factor to update organic residue pools
        OrganicResidueStateRef.Decomposition_Reduction_Factor[layer] = Decomposition_Reduction_Factor;
        //Calculate actual decomposition of soil organic matter pools
        double Actual_Carbon_Mass_Decomposed(0);
        parrLayer_SOM_Pools[layer].ActualCarbonDecomposition(Decomposition_Reduction_Factor,
                                                              Actual_Carbon_Mass_Decomposed);
        //Calculate carbon transfer and update soil organic matter pools
        //Determine carbon decomposition in each residue carbon pool: fast cycling, slow cycling, and lignified
        double Decomposed_Fast_Cycling_Materials_Carbon = OrganicResidueStateRef.Potential_Fast_Cycling_Residue_Carbon_Decomposition[layer]
            * Decomposition_Reduction_Factor;
        double Decomposed_Slow_Cycling_Materials_Carbon = OrganicResidueStateRef.Potential_Slow_Cycling_Residue_Carbon_Decomposition[layer]
            * Decomposition_Reduction_Factor;
        double Decomposed_Lignified_Materials_Carbon = OrganicResidueStateRef.Potential_Lignified_Residue_Carbon_Decomposition[layer]
            * Decomposition_Reduction_Factor;
        if (layer == 1) {
            Decomposed_Fast_Cycling_Materials_Carbon +=
                (OrganicResidueStateRef.Potential_Fast_Cycling_Standing_Stubble_Carbon_Decomposition
                 + OrganicResidueStateRef.Potential_Fast_Cycling_Surface_Residue_Carbon_Decomposition)
                 * Decomposition_Reduction_Factor;
            Decomposed_Slow_Cycling_Materials_Carbon +=
                (OrganicResidueStateRef.Potential_Slow_Cycling_Standing_Stubble_Carbon_Decomposition
                 + OrganicResidueStateRef.Potential_Slow_Cycling_Surface_Residue_Carbon_Decomposition)
                 * Decomposition_Reduction_Factor;
            Decomposed_Lignified_Materials_Carbon +=
                (OrganicResidueStateRef.Potential_Lignified_Standing_Stubble_Carbon_Decomposition
                 + OrganicResidueStateRef.Potential_Lignified_Surface_Residue_Carbon_Decomposition)
                 * Decomposition_Reduction_Factor;
        }
        double SOM_Lost_As_CO2 = 0;
        double Residue_Lost_As_CO2 = 0;
        parrLayer_SOM_Pools[layer].CarbonTransferAndSOMPoolsUpdate(layer, SOM_Lost_As_CO2, Residue_Lost_As_CO2,
                            Decomposed_Fast_Cycling_Materials_Carbon, Decomposed_Slow_Cycling_Materials_Carbon,
                            Decomposed_Lignified_Materials_Carbon, Simulation, SoilRef);
        double Layer_Ammonium_Mass_Change = SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization - Ammonium_N_Mass_Immobilized;
        double Layer_Nitrate_Mass_Change = -Nitrate_N_Mass_Immobilized;
        SoilStateRef.Ammonium_Mass_Into_OM_Mineralization                        //150915RLN
              // 150915RLN Ammonium_Mass_Into_Soil_SOM_Mineralization
                += Layer_Ammonium_Mass_Change;     //  //FMS 10/31/2013

        SoilStateRef.Nitrate_Mass_Into_Soil_SOM_Mineralization += Layer_Nitrate_Mass_Change;      //  //FMS 10/31/2013
        //double oldNH4 = SoilStateRef.Layer_Ammonium_N_Mass[layer];
        //double oldNO3 = SoilStateRef.Layer_Nitrate_N_Mass[layer];
        SoilStateRef.Layer_Ammonium_N_Mass[layer] += Layer_Ammonium_Mass_Change;
        SoilStateRef.Layer_Nitrate_N_Mass[layer] += Layer_Nitrate_Mass_Change;
        assert(SoilStateRef.Layer_Ammonium_N_Mass[layer] >= 0.0);
        assert(SoilStateRef.Layer_Nitrate_N_Mass[layer] >= 0.0);
        //double newNH4 = SoilStateRef.Layer_Ammonium_N_Mass[layer];
        //double newNO3 = SoilStateRef.Layer_Nitrate_N_Mass[layer];
        Profile_SOM_Lost_As_CO2 += SOM_Lost_As_CO2;
        Profile_Residue_Lost_As_CO2 += Residue_Lost_As_CO2;
        ////Store layer daily and cumulative nitrogen mineralization from organic matter and residues
        SoilStateRef.Layer_Mineralized_N_Mass_From_Organic_Matter[layer] = SOM_Nitrogen_Mineralization;
        SoilStateRef.Layer_Mineralized_N_Mass_From_Organic_Residues[layer] = Residue_Nitrogen_Mineralization;
        ////Store soil profile carbon and nitrogen mass
        Profile_SOM_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer];
        Profile_SOM_Nitrogen_Mass += SoilStateRef.Layer_Nitrogen_Mass_In_Organic_Matter[layer];

        SoilStateRef.Soil_Microbial_Carbon_Mass[layer]  = parrLayer_SOM_Pools[layer].MB_C_Mass;             //FMS Apr 17, 2015
        SoilStateRef.Soil_Labile_Carbon_Mass[layer]     = parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass;     //FMS Apr 17, 2015
        SoilStateRef.Soil_Metastable_Carbon_Mass[layer] = parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass; //FMS Apr 17, 2015
        SoilStateRef.Soil_Passive_Carbon_Mass[layer]    = parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass;    //FMS Apr 17, 2015
        /*FMS Apr 17, 2015
        ////SOM carbon storage and mineralization in top soil layer (0-5 cm)
        if (Soil_Depth <= 0.05) {
            Top_5cm_Soil_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer];
            Top_5cm_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass;
            Top_5cm_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass;
            Top_5cm_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass;
            Top_5cm_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass;
            Top_5cm_N_Mineralization_Mass += SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization;
            Top_5cm_N_Immobilization_Mass += Ammonium_N_Mass_Immobilized + Nitrate_N_Mass_Immobilized;
         }
         else if ((Soil_Depth - Layer_Thickness) < 0.05) {
            Top_5cm_Soil_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer] * (Soil_Depth - 0.05) / Layer_Thickness;
            Top_5cm_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass * (Soil_Depth - 0.05) / Layer_Thickness;
            Top_5cm_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass * (Soil_Depth - 0.05) / Layer_Thickness;
            Top_5cm_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass * (Soil_Depth - 0.05) / Layer_Thickness;
            Top_5cm_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass * (Soil_Depth - 0.05) / Layer_Thickness;
            Top_5cm_N_Mineralization_Mass += (SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization) * (Soil_Depth - 0.05) / Layer_Thickness;
            Top_5cm_N_Immobilization_Mass += (Ammonium_N_Mass_Immobilized + Nitrate_N_Mass_Immobilized) * (Soil_Depth - 0.05) / Layer_Thickness;
        }
        ////SOM carbon storage and mineralization in top soil (0-30 cm)
        if (Soil_Depth <= 0.3) {
            Top_30cm_Soil_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer];
            Top_30cm_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass;
            Top_30cm_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass;
            Top_30cm_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass;
            Top_30cm_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass;
            Top_30cm_N_Mineralization_Mass += SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization;
            Top_30cm_N_Immobilization_Mass += Ammonium_N_Mass_Immobilized + Nitrate_N_Mass_Immobilized;
         }
        else if ((Soil_Depth - Layer_Thickness) < 0.3) {
            Top_30cm_Soil_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer] * (Soil_Depth - 0.3) / Layer_Thickness;
            Top_30cm_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass * (Soil_Depth - 0.3) / Layer_Thickness;
            Top_30cm_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass * (Soil_Depth - 0.3) / Layer_Thickness;
            Top_30cm_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass * (Soil_Depth - 0.3) / Layer_Thickness;
            Top_30cm_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass * (Soil_Depth - 0.3) / Layer_Thickness;
            Top_30cm_N_Mineralization_Mass += (SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization) * (Soil_Depth - 0.3) / Layer_Thickness;
            Top_30cm_N_Immobilization_Mass += (Ammonium_N_Mass_Immobilized + Nitrate_N_Mass_Immobilized) * (Soil_Depth - 0.3) / Layer_Thickness;
        }
        // //SOM carbon storage and mineralization in top soil (0-60 cm)
        if (Soil_Depth <= 0.6) {
            Top_60cm_Soil_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer];
            Top_60cm_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass;
            Top_60cm_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass;
            Top_60cm_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass;
            Top_60cm_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass;
            Top_60cm_N_Mineralization_Mass += SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization;
            Top_60cm_N_Immobilization_Mass += Ammonium_N_Mass_Immobilized + Nitrate_N_Mass_Immobilized;
        }
        else if ((Soil_Depth - Layer_Thickness) < 0.6) {
            Top_60cm_Soil_Carbon_Mass += SoilStateRef.Layer_Carbon_Mass_In_Organic_Matter[layer] * (Soil_Depth - 0.6) / Layer_Thickness;
            Top_60cm_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass * (Soil_Depth - 0.6) / Layer_Thickness;
            Top_60cm_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass * (Soil_Depth - 0.6) / Layer_Thickness;
            Top_60cm_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass * (Soil_Depth - 0.6) / Layer_Thickness;
            Top_60cm_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass * (Soil_Depth - 0.6) / Layer_Thickness;
            Top_60cm_N_Mineralization_Mass += (SOM_Nitrogen_Mineralization + Residue_Nitrogen_Mineralization) * (Soil_Depth - 0.6) / Layer_Thickness;
            Top_60cm_N_Immobilization_Mass += (Ammonium_N_Mass_Immobilized + Nitrate_N_Mass_Immobilized) * (Soil_Depth - 0.6) / Layer_Thickness;
        }
        */   //Ended deleted FMS Apr 17, 2015
        ////Calculate soil profile carbon and nitrogen balance for soil organic matter
        Profile_SOM_Carbon_Balance += SoilStateRef.Layer_SOM_C_Balance[layer];
        Profile_SOM_Nitrogen_Balance += SoilStateRef.Layer_SOM_N_Balance[layer];
        Profile_Ammonium_N_Mass_Immobilization += Ammonium_N_Mass_Immobilized;
        Profile_Nitrate_N_Mass_Immobilization += Nitrate_N_Mass_Immobilized;
        Profile_SOM_N_Mineralized_Mass += SOM_Nitrogen_Mineralization;
        Profile_Residue_N_Mineralized_Mass += Residue_Nitrogen_Mineralization;
        Profile_Microbial_Carbon_Mass += parrLayer_SOM_Pools[layer].MB_C_Mass;
        Profile_Labile_Carbon_Mass += parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass;
        Profile_Metastable_Carbon_Mass += parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass;
        Profile_Passive_Carbon_Mass += parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass;

    }//next layer

    ////Calculate actual decomposition of organic residue pools
    OrganicResidueRef.UpdateResiduePoolsAfterDecomposition();
    ////Report meaningful presence of standing stubble and surface residue to the simulation control
    if (OrganicResidueStateRef.Standing_Stubble_Carbon_Mass > 0.1) Simulation.pSimulationRotation->setCropStubblePresent(true);
    if (OrganicResidueStateRef.Surface_Residue_Carbon_Mass > 0.1) Simulation.pSimulationRotation->setSurfaceResiduePresent(true);
    double Final_Profile_Residue_Carbon = OrganicResidueStateRef.Standing_Stubble_Carbon_Mass
        + OrganicResidueStateRef.Surface_Residue_Carbon_Mass
        + OrganicResidueStateRef.Soil_Residue_Carbon_Mass;
    double Final_Profile_Residue_Nitrogen = OrganicResidueStateRef.Standing_Stubble_Nitrogen_Mass
        + OrganicResidueStateRef.Surface_Residue_Nitrogen_Mass
        + OrganicResidueStateRef.Soil_Residue_Nitrogen_Mass;
    //double Profile_Decomposed_Organic_Residue_Carbon = OrganicResidueStateRef.Decomposed_Standing_Stubble_Carbon_Mass
    //    + OrganicResidueStateRef.Decomposed_Surface_Residue_Carbon_Mass
    //    + OrganicResidueStateRef.Decomposed_Soil_Residue_Carbon_Mass;
    //double Profile_Decomposed_Organic_Residue_Nitrogen = OrganicResidueStateRef.Decomposed_Standing_Stubble_Nitrogen_Mass
    //    + OrganicResidueStateRef.Decomposed_Surface_Residue_Nitrogen_Mass
    //    + OrganicResidueStateRef.Decomposed_Soil_Residue_Nitrogen_Mass;
    //Carbon_Balance = Carbon_Balance + (Final_Profile_Residue_Carbon - OrganicResidueStateRef.CumulativeInitialOrganicResidue_CarbonMass)
    //                                - Profile_Decomposed_Organic_Residue_Carbon
    //                + Profile_Residue_Lost_As_CO2 //
    //                - OrganicResidueStateRef.CumulativeNewResidueOrganicResidue_CarbonMass //FMS 11/06/2013

    ////OrganicResidueStateRef.CumulativeInitialOrganicResidue_CarbonMass
    ////Store daily carbon and nitrogen mass
    SoilStateRef.Profile_Residue_Carbon_Mass = Final_Profile_Residue_Carbon;
    SoilStateRef.Profile_Residue_Nitrogen_Mass = Final_Profile_Residue_Nitrogen;
    SoilStateRef.Profile_SOM_Carbon_Mass = Profile_SOM_Carbon_Mass;
    SoilStateRef.Profile_SOM_Nitrogen_Mass = Profile_SOM_Nitrogen_Mass;
    /*FMS Apr 17, 2015
    SoilStateRef.Top_5cm_SOM_Carbon_Mass = Top_5cm_Soil_Carbon_Mass;
    SoilStateRef.Top_30cm_Soil_Carbon_Mass = Top_30cm_Soil_Carbon_Mass;
    SoilStateRef.Top_60cm_Soil_Carbon_Mass = Top_60cm_Soil_Carbon_Mass;
    */
    SoilStateRef.Profile_Ammonium_Immobilization = Profile_Ammonium_N_Mass_Immobilization;
    SoilStateRef.Profile_Nitrate_Immobilization = Profile_Nitrate_N_Mass_Immobilization;
    SoilStateRef.Profile_OM_Mineralization = Profile_SOM_N_Mineralized_Mass;
    SoilStateRef.Profile_Residue_Mineralization = Profile_Residue_N_Mineralized_Mass;
    SoilStateRef.Profile_SOM_Carbon_Lost_As_CO2 = Profile_SOM_Lost_As_CO2;
    SoilStateRef.Profile_Residue_Carbon_Lost_As_CO2 = Profile_Residue_Lost_As_CO2;
    /*FMS Apr 17, 2015
    SoilStateRef.Top_5cm_Microbial_Carbon_Mass = Top_5cm_Microbial_Carbon_Mass;
    SoilStateRef.Top_30cm_Microbial_Carbon_Mass = Top_30cm_Microbial_Carbon_Mass;
    SoilStateRef.Top_60cm_Microbial_Carbon_Mass = Top_60cm_Microbial_Carbon_Mass;
    */
    SoilStateRef.Profile_Microbial_Carbon_Mass = Profile_Microbial_Carbon_Mass;
    /*FMS Apr 17, 2015
    SoilStateRef.Top_5cm_Labile_Carbon_Mass = Top_5cm_Labile_Carbon_Mass;
    SoilStateRef.Top_30cm_Labile_Carbon_Mass = Top_30cm_Labile_Carbon_Mass;
    SoilStateRef.Top_60cm_Labile_Carbon_Mass = Top_60cm_Labile_Carbon_Mass;
    */
    SoilStateRef.Profile_Labile_Carbon_Mass = Profile_Labile_Carbon_Mass;
    /*FMS Apr 17, 2015
    SoilStateRef.Top_5cm_Metastable_Carbon_Mass = Top_5cm_Metastable_Carbon_Mass;
    SoilStateRef.Top_30cm_Metastable_Carbon_Mass = Top_30cm_Metastable_Carbon_Mass;
    SoilStateRef.Top_60cm_Metastable_Carbon_Mass = Top_60cm_Metastable_Carbon_Mass;
    */
    SoilStateRef.Profile_Metastable_Carbon_Mass = Profile_Metastable_Carbon_Mass;
    /*FMS Apr 17, 2015
    SoilStateRef.Top_5cm_Passive_Carbon_Mass = Top_5cm_Passive_Carbon_Mass;
    SoilStateRef.Top_30cm_Passive_Carbon_Mass = Top_30cm_Passive_Carbon_Mass;
    SoilStateRef.Top_60cm_Passive_Carbon_Mass = Top_60cm_Passive_Carbon_Mass;
    */
    SoilStateRef.Profile_Passive_Carbon_Mass = Profile_Passive_Carbon_Mass;
    SoilStateRef.Profile_Net_N_Mineralization_Mass = Profile_SOM_N_Mineralized_Mass
                                                     + Profile_Residue_N_Mineralized_Mass
                                                     - Profile_Ammonium_N_Mass_Immobilization
                                                     - Profile_Nitrate_N_Mass_Immobilization; //FMS Apr 2, 2015
    if (doy == 1) {
        /*FMS Apr 17, 2015 Deleted those variables
        SoilStateRef.Cumulative_Top_5cm_Mineralized_N_Mass = Top_5cm_N_Mineralization_Mass;
        SoilStateRef.Cumulative_Top_30cm_Mineralized_N_Mass = Top_30cm_N_Mineralization_Mass;
        SoilStateRef.Cumulative_Top_60cm_Mineralized_N_Mass = Top_60cm_N_Mineralization_Mass;
        SoilStateRef.Cumulative_Top_5cm_Immobilized_N_Mass = Top_5cm_N_Immobilization_Mass;
        SoilStateRef.Cumulative_Top_30cm_Immobilized_N_Mass = Top_30cm_N_Immobilization_Mass;
        SoilStateRef.Cumulative_Top_60cm_Immobilized_N_Mass = Top_60cm_N_Immobilization_Mass;
        */
        SoilStateRef.Cumulative_Profile_OM_Mineralization = Profile_SOM_N_Mineralized_Mass;
        SoilStateRef.Cumulative_Profile_Residue_Mineralization = Profile_Residue_N_Mineralized_Mass;
        SoilStateRef.Cumulative_Profile_Nitrogen_Immobilization = Profile_Ammonium_N_Mass_Immobilization + Profile_Nitrate_N_Mass_Immobilization;
        SoilStateRef.Cumulative_Profile_SOM_Carbon_Lost_As_CO2 = Profile_SOM_Lost_As_CO2;
        SoilStateRef.Cumulative_Profile_Residue_Carbon_Lost_As_CO2 = Profile_Residue_Lost_As_CO2;
    } else {
        /*FMS Apr 17, 2015 Deleted those variables
        SoilStateRef.Cumulative_Top_5cm_Mineralized_N_Mass += Top_5cm_N_Mineralization_Mass;
        SoilStateRef.Cumulative_Top_30cm_Mineralized_N_Mass += Top_30cm_N_Mineralization_Mass;
        SoilStateRef.Cumulative_Top_60cm_Mineralized_N_Mass += Top_60cm_N_Mineralization_Mass;
        SoilStateRef.Cumulative_Top_5cm_Immobilized_N_Mass += Top_5cm_N_Immobilization_Mass;
        SoilStateRef.Cumulative_Top_30cm_Immobilized_N_Mass += Top_30cm_N_Immobilization_Mass;
        SoilStateRef.Cumulative_Top_60cm_Immobilized_N_Mass += Top_60cm_N_Immobilization_Mass;
        */
        SoilStateRef.Cumulative_Profile_OM_Mineralization += Profile_SOM_N_Mineralized_Mass;
        SoilStateRef.Cumulative_Profile_Residue_Mineralization += Profile_Residue_N_Mineralized_Mass;
        SoilStateRef.Cumulative_Profile_Nitrogen_Immobilization += Profile_Ammonium_N_Mass_Immobilization + Profile_Nitrate_N_Mass_Immobilization;
        SoilStateRef.Cumulative_Profile_SOM_Carbon_Lost_As_CO2 += Profile_SOM_Lost_As_CO2;
        SoilStateRef.Cumulative_Profile_Residue_Carbon_Lost_As_CO2 += Profile_Residue_Lost_As_CO2;
    }
    //SoilStateRef.Cumulative_Profile_SOM_Carbon_Lost_As_CO2 += Profile_SOM_Lost_As_CO2;  // // FMS 11/19/2013
    //SoilStateRef.Cumulative_Profile_Residue_Carbon_Lost_As_CO2 += Profile_Residue_Lost_As_CO2;  // // FMS 11/19/2013
    #ifdef CHECK_MASS_BALANCE
    bal_TotalC.SetFinalPool(getTotalOrganicCarbonMass());
    bal_OrgN.SetFinalPool(getTotalOrganicNitrogenMass());
    bal_InorgN.SetFinalPool(SoilStateRef.getProfileNH4NMass() + SoilStateRef.getProfileNO3NMass());
    //std::cout<<"Profile_SOM_Lost_As_CO2:"<<Profile_SOM_Lost_As_CO2<<" Profile_Residue_Lost_As_CO2:"<<Profile_Residue_Lost_As_CO2<<std::endl;
    bal_TotalC.SetFluxOut(Profile_SOM_Lost_As_CO2 + Profile_Residue_Lost_As_CO2);       //CO2 emission
    double net_imobilized_N = Profile_Ammonium_N_Mass_Immobilization + Profile_Nitrate_N_Mass_Immobilization;
    double net_minalized_N = Profile_Residue_N_Mineralized_Mass + Profile_SOM_N_Mineralized_Mass;
    bal_OrgN.SetFluxOut(net_minalized_N);
    bal_OrgN.SetFluxIn(net_imobilized_N);
    bal_InorgN.SetFluxIn(net_minalized_N);
    bal_InorgN.SetFluxOut(net_imobilized_N);
    if (!bal_TotalC.IsMassBalance(1e-6))
        bal_TotalC.PrintMassBalanceTerms("Total C in DailyProcess");
    if (!bal_OrgN.IsMassBalance(1e-6))
        bal_OrgN.PrintMassBalanceTerms("OrgN in DailyProcess");
    if (!bal_InorgN.IsMassBalance(1e-6))
        bal_InorgN.PrintMassBalanceTerms("InOrgN in DailyProcess");
    #endif
}
//______________________________________________________________________________
#ifndef CROPSYST_PROPER_MANAGEMENT
void SoilOMAndResidueMasterClass::OrganicCarbonMixingDueToTillage(clsManagement &Management,clsSimulation &Simulation)
{
    //ROGER
    bool Tillage_Application = Management.pManagementState->Tillage_Event;
    #ifdef CHECK_MASS_BALANCE
    BalanceItem bal_totalC,bal_totalN;
    bal_totalC.SetInitPool(getTotalOrganicCarbonMass());
    bal_totalN.SetInitPool(getTotalOrganicNitrogenMass());
    #endif
    if (Tillage_Application) {
        //Load tillage depth and mixing fraction
        double T_Mix = Management.pManagementState->Tillage_Mixing_Fraction;
        double T_Depth = Management.pManagementState->Tillage_Depth;
        //Load C/N ratios
        double MB_CN_Ratio = Simulation.pSimConstants-> Microbial_Biomass_CN_Ratio;
        double LabileSOM_CN_Ratio = Simulation.pSimConstants->Labile_Active_SOM_CN_Ratio;
        double MetastableSOM_CN_Ratio = Simulation.pSimConstants->Metastable_Active_SOM_CN_Ratio;
        double PassiveSOM_CN_Ratio = Simulation.pSimConstants->Passive_SOM_CN_Ratio;
        int Last_Tilled_Layer = Management.pManagementState->Last_Layer_Tilled;
        //    //Retrieve mass-base contents.  All in unit of kg per kg of soil
        double Soil_Layer_Thickness[7];
        double Layer_Soil_Mass[7];
        double Layer_Bottom_Depth[7];
        double Microbial_SOM_C_Mass_Fraction[7];
        double Labile_SOM_C_Mass_Fraction[7];
        double Metastable_SOM_C_Mass_Fraction[7];
        double Passive_SOM_C_Mass_Fraction[7];
        for (int i = 1; i <= Last_Tilled_Layer; i++) {
            Layer_Soil_Mass[i] = SoilProfileRef.get_bulk_density_g_cm3(i) 
                                 * SoilProfileRef.get_thickness_m(i) 
                                 * 1000; //in kg/m2. 1000 converts g/cm3 to kg/m3
            Microbial_SOM_C_Mass_Fraction[i] = parrLayer_SOM_Pools[i].MB_C_Mass / Layer_Soil_Mass[i];
            Labile_SOM_C_Mass_Fraction[i] = parrLayer_SOM_Pools[i].Labile_SOM_C_Mass / Layer_Soil_Mass[i];
            Metastable_SOM_C_Mass_Fraction[i] = parrLayer_SOM_Pools[i].Metastable_SOM_C_Mass / Layer_Soil_Mass[i];
            Passive_SOM_C_Mass_Fraction[i] = parrLayer_SOM_Pools[i].Passive_SOM_C_Mass / Layer_Soil_Mass[i];
            Layer_Bottom_Depth[i] = SoilProfileRef.get_depth_m(i);                  //M.Liu Added Feb 3, 2014
            Soil_Layer_Thickness[i] = SoilProfileRef.get_thickness_m(i);            //LML 140828
        }
        double Total_Soil_Mass_Mixed(0.0);
        double Microbial_SOM_Mixed(0.0);
        double Labile_SOM_Mixed(0.0);
        double Metastable_SOM_Mixed(0.0);
        double Passive_SOM_Mixed(0.0);
        double Layer_Soil_Mass_Remaining_After_Tillage[7];
        double Layer_Soil_Mass_Mixed_After_Tillage[7];
        for (int i = 1; i <= Last_Tilled_Layer; i++) {
            if (Layer_Bottom_Depth[i] <= T_Depth) { // tillage apply for the full depth of the layer
                Layer_Soil_Mass_Remaining_After_Tillage[i] = (1 - T_Mix) * Layer_Soil_Mass[i];
                Layer_Soil_Mass_Mixed_After_Tillage[i] = Layer_Soil_Mass[i] * T_Mix;
            }
            else if (Layer_Bottom_Depth[i] > T_Depth && Layer_Bottom_Depth[i - 1] < T_Depth) {
                Layer_Soil_Mass_Mixed_After_Tillage[i] = 
                    T_Mix * Layer_Soil_Mass[i] * (T_Depth - Layer_Bottom_Depth[i - 1]) 
                    / Soil_Layer_Thickness[i]; // weights the mixing by the fraction of the layer affected by tillage
                Layer_Soil_Mass_Remaining_After_Tillage[i] = 
                    Layer_Soil_Mass[i] - Layer_Soil_Mass_Mixed_After_Tillage[i];
            } else { // this else is redundant, as if there is no tillage there is no mixing, keep it here for clarity
                Layer_Soil_Mass_Remaining_After_Tillage[i] = Layer_Soil_Mass[i];
                Layer_Soil_Mass_Mixed_After_Tillage[i] = 0;
            }
            if (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[i] > 0.0) {
                Microbial_SOM_Mixed = (Total_Soil_Mass_Mixed * Microbial_SOM_Mixed 
                                       + Layer_Soil_Mass_Mixed_After_Tillage[i] * Microbial_SOM_C_Mass_Fraction[i])
                                      / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[i]);
                Labile_SOM_Mixed = (Total_Soil_Mass_Mixed * Labile_SOM_Mixed 
                                    + Layer_Soil_Mass_Mixed_After_Tillage[i] * Labile_SOM_C_Mass_Fraction[i])
                                   / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[i]);
                Metastable_SOM_Mixed = (Total_Soil_Mass_Mixed * Metastable_SOM_Mixed 
                                        + Layer_Soil_Mass_Mixed_After_Tillage[i] * Metastable_SOM_C_Mass_Fraction[i])
                                        / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[i]);
                Passive_SOM_Mixed = (Total_Soil_Mass_Mixed * Passive_SOM_Mixed 
                                     + Layer_Soil_Mass_Mixed_After_Tillage[i] * Passive_SOM_C_Mass_Fraction[i])
                                    / (Total_Soil_Mass_Mixed + Layer_Soil_Mass_Mixed_After_Tillage[i]);
            } else {
                Microbial_SOM_Mixed = 0.0;
                Labile_SOM_Mixed = 0.0;   
                Metastable_SOM_Mixed = 0.0;
                Passive_SOM_Mixed = 0.0;
            }
            Total_Soil_Mass_Mixed += Layer_Soil_Mass_Mixed_After_Tillage[i];
        }//next i
        for (int i = 1; i <= Last_Tilled_Layer; i++) {
                double New_Microbial_SOM_C_Mass_Fraction = 
                    (Microbial_SOM_C_Mass_Fraction[i] * Layer_Soil_Mass_Remaining_After_Tillage[i] 
                     + Microbial_SOM_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[i])
                     / Layer_Soil_Mass[i];
                parrLayer_SOM_Pools[i].MB_C_Mass = 
                    New_Microbial_SOM_C_Mass_Fraction * Layer_Soil_Mass[i];
                double New_Labile_SOM_C_Mass_Fraction = 
                    (Labile_SOM_C_Mass_Fraction[i] * Layer_Soil_Mass_Remaining_After_Tillage[i] 
                     + Labile_SOM_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[i])
                    / Layer_Soil_Mass[i];
                parrLayer_SOM_Pools[i].Labile_SOM_C_Mass = 
                    New_Labile_SOM_C_Mass_Fraction * Layer_Soil_Mass[i];
                double New_Metastable_SOM_C_Mass_Fraction = 
                    (Metastable_SOM_C_Mass_Fraction[i] * Layer_Soil_Mass_Remaining_After_Tillage[i] 
                     + Metastable_SOM_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[i])
                     / Layer_Soil_Mass[i];
                parrLayer_SOM_Pools[i].Metastable_SOM_C_Mass = 
                    New_Metastable_SOM_C_Mass_Fraction * Layer_Soil_Mass[i];
                double New_Passive_SOM_C_Mass_Fraction = 
                    (Passive_SOM_C_Mass_Fraction[i] * Layer_Soil_Mass_Remaining_After_Tillage[i] 
                     + Passive_SOM_Mixed * Layer_Soil_Mass_Mixed_After_Tillage[i])
                     / Layer_Soil_Mass[i];
                parrLayer_SOM_Pools[i].Passive_SOM_C_Mass = 
                    New_Passive_SOM_C_Mass_Fraction * Layer_Soil_Mass[i];
                //Also update SOM N mass
                parrLayer_SOM_Pools[i].MB_N_Mass = 
                    parrLayer_SOM_Pools[i].MB_C_Mass / MB_CN_Ratio;
                parrLayer_SOM_Pools[i].Labile_SOM_N_Mass = 
                    parrLayer_SOM_Pools[i].Labile_SOM_C_Mass / LabileSOM_CN_Ratio;
                parrLayer_SOM_Pools[i].Metastable_SOM_N_Mass = 
                    parrLayer_SOM_Pools[i].Metastable_SOM_C_Mass / MetastableSOM_CN_Ratio;
                parrLayer_SOM_Pools[i].Passive_SOM_N_Mass = 
                    parrLayer_SOM_Pools[i].Passive_SOM_C_Mass / PassiveSOM_CN_Ratio;
        }//Next i
    }
    #ifdef CHECK_MASS_BALANCE
    bal_totalC.SetFinalPool(getTotalOrganicCarbonMass());
    bal_totalN.SetFinalPool(getTotalOrganicNitrogenMass());
    if (!bal_totalC.IsMassBalance()) 
        bal_totalC.PrintMassBalanceTerms("Total C during OrganicCarbonMixingDueToTillage");
    if (!bal_totalN.IsMassBalance()) 
        bal_totalN.PrintMassBalanceTerms("Total N during OrganicCarbonMixingDueToTillage");
    #endif
}
#endif
//______________________________________________________________________________
void SoilOMAndResidueMasterClass::InitializeSoilOrganicMatter(clsSimulation &Simulation)
{
    int NL = SoilProfileRef.NumberOfLayers();
    for (int layer = 1; layer <= NL; layer++) {
        parrLayer_SOM_Pools[layer].initialize(layer, SoilRef, Simulation);
    }
}
//______________________________________________________________________________
double SoilOMAndResidueMasterClass::getProfileSOMCarbonMass()
{
    double total(0.0);
    for (int layer = 1; layer <= SoilProfileRef.NumberOfLayers(); layer++) {
        total += parrLayer_SOM_Pools[layer].MB_C_Mass
                 + parrLayer_SOM_Pools[layer].Labile_SOM_C_Mass
                 + parrLayer_SOM_Pools[layer].Metastable_SOM_C_Mass    
                 + parrLayer_SOM_Pools[layer].Passive_SOM_C_Mass;
    }
    return total;
}
//______________________________________________________________________________
double SoilOMAndResidueMasterClass::getProfileSOMNitrogenMass()
{
    double total = 0;
    for (int layer = 1; layer <= SoilProfileRef.NumberOfLayers(); layer++) {
        total += parrLayer_SOM_Pools[layer].MB_N_Mass
                 + parrLayer_SOM_Pools[layer].Labile_SOM_N_Mass
                 + parrLayer_SOM_Pools[layer].Metastable_SOM_N_Mass    
                 + parrLayer_SOM_Pools[layer].Passive_SOM_N_Mass;
    }
    return total;
}
//______________________________________________________________________________
double SoilOMAndResidueMasterClass::getTotalOrganicCarbonMass()
{
    double total = getProfileSOMCarbonMass() 
            + OrganicResidueRef.getAboveGroungResidueCarbonMass()
            + OrganicResidueRef.getBellowGroungResidueCarbonMass();
    return total;
}
//______________________________________________________________________________
double SoilOMAndResidueMasterClass::getTotalOrganicNitrogenMass()
{
    double total = getProfileSOMNitrogenMass() 
            + OrganicResidueRef.getAboveGroungResidueNitrogenMass()
            + OrganicResidueRef.getBellowGroungResidueNitrogenMass();
    return total;
}
//______________________________________________________________________________
