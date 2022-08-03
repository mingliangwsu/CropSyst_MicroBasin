#include "outputhourclass.h"
#include "util/pubtools.h"
#include "soil/layering.h"
//______________________________________________________________________________
OutputHourClass::OutputHourClass()
:b_set_vector_size(false)
,Current_Year(-9999)
,Current_DOY(-9999)
,Current_Hour(-9999)
,Prec_Irrig_SnowMelt_m(-9999)
,Ponded_Water(-9999)
,Runoff(-9999)
,Drainage(-9999)
,Evaporation(-9999)
,Temperature(-9999)
,Precipitation(-9999)
,Fraction_Cover_Snow(-9999)
,Snow_Water_Equavalent(-9999)
,Snow_Melt(-9999)
,Sublimation(-9999)
,FD_Water_Balance(-9999)
,Sat_Boundary(false)
,hourlySurfaceOutFlow_m3(-9999)
,hourlySurfaceInFlow_m3(-9999)
,hourlyDrainage_m3(-9999)
,hourlyLateralInFlow_m3(-9999)
,hourlyLateralOutFlow_m3(-9999)
,hourlyLateralUpFlow_m3(-9999)
{
    const int num_solute_species = SL_COUNT;
    hourlyLateralInFlowSolute_kg.resize(num_solute_species,0);  
    hourlyLateralOutFlowSolute_kg.resize(num_solute_species,0); 
    hourlySurfaceInFlowSolute_kg.resize(num_solute_species,0);  
    hourlySurfaceOutFlowSolute_kg.resize(num_solute_species,0); 
}
//______________________________________________________________________________
OutputHourClass::~OutputHourClass()
{
}
//______________________________________________________________________________
