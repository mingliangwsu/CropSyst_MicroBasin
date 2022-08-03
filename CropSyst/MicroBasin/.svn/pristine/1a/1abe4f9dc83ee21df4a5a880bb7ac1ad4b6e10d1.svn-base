#error obsolete
#include "organicresiduestateclass.h"
#include "util/pubtools.h"
#include <iostream>
//______________________________________________________________________________
OrganicResidueStateClass::OrganicResidueStateClass()
    :b_set_vector_size(false)
{
    Standing_Stubble_Carbon_Mass = 0;
    Surface_Residue_Carbon_Mass = 0;
    Soil_Residue_Carbon_Mass = 0;
    Standing_Stubble_Nitrogen_Mass = 0;
    Surface_Residue_Nitrogen_Mass = 0;
    Soil_Residue_Nitrogen_Mass = 0;
    New_Standing_Stubble_Carbon_Mass = 0;   
    New_Surface_Residue_Carbon_Mass = 0;    
    New_Soil_Residue_Carbon_Mass = 0;       
    New_Standing_Stubble_Nitrogen_Mass = 0; 
    New_Surface_Residue_Nitrogen_Mass = 0;  
    New_Soil_Residue_Nitrogen_Mass = 0;     
}
//______________________________________________________________________________
OrganicResidueStateClass::~OrganicResidueStateClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~OrganicResidueStateClass:"<<std::endl;
#endif
    //delete[] Standing_Stubble_Hourly_Temperature;    //(25);
    //delete[] Surface_Residues_Hourly_Temperature;    //(25);
#ifdef Destruct_Monitor
    std::cout<<"~OrganicResidueStateClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
void OrganicResidueStateClass::LastDayOfYearState(clsSimulation &Simulation)
{
    int doy = Simulation.pTimeState->getToday().get_DOY();
    //FMS Apr 21, 2015 if (doy == 1) {   // Then ' the first day of year is equal to last day of before year
        LastDayOfYear_Standing_Stubble_Carbon_Mass = Standing_Stubble_Carbon_Mass;
        LastDayOfYear_Surface_Residue_Carbon_Mass = Surface_Residue_Carbon_Mass;
        LastDayOfYear_Soil_Residue_Carbon_Mass = Soil_Residue_Carbon_Mass;
        LastDayOfYear_Cumulative_Decomposed_Standing_Stubble_Carbon_Mass = Cumulative_Decomposed_Standing_Stubble_Carbon_Mass;
        LastDayOfYear_Cumulative_Decomposed_Surface_Residue_Carbon_Mass = Cumulative_Decomposed_Surface_Residue_Carbon_Mass;
        LastDayOfYear_Cumulative_Decomposed_Soil_Residue_Carbon_Mass = Cumulative_Decomposed_Soil_Residue_Carbon_Mass;
    //}
}

