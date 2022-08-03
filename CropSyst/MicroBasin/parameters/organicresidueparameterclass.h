#ifndef ORGANICRESIDUEPARAMETERCLASS_H
#define ORGANICRESIDUEPARAMETERCLASS_H
#include "cropresidueparameterclass.h"
#include "manureparameterclass.h"
#include "control/allcontrolclass.h"

class CropResidueParameterClass;
class AllControlClass;
class ManureParameterClass;

class OrganicResidueParameterClass
{
private:
   #ifdef LIU_ENGINE
    const std::string &getOrganicResidueParameterFileName();
   #endif
    int crop_residue_numbers;
    int manure_numbers;
public:
    AllControlClass &ControlRef;
    CropResidueParameterClass *parrCrop_Residue_Parameter;
    ManureParameterClass *parrManure_Parameter;

    double Default_Fast_Cycling_Residues_Decomposition_Constant;
    double Default_Slow_Cycling_Residues_Decomposition_Constant;
    double Default_Lignified_Residues_Decomposition_Constant;
public:
    OrganicResidueParameterClass(AllControlClass &_ControlRef);
    ~OrganicResidueParameterClass();
    void ReadInputParameters();
    int getCropResidueNumbers();
    int getManureNumbers();
    int FindCropResidueParameterIndex(std::string Crop_Residue_Name);
    int FindManureParameterIndex(std::string Manure_Name);
};

#endif // ORGANICRESIDUEPARAMETERCLASS_H
