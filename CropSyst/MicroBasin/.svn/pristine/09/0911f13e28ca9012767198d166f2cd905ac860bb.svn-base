// Not used in CropSyst proper version                                           //150723RLN
#include "organicresidueparameterclass.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "util/pubtools.h"

//______________________________________________________________________________
OrganicResidueParameterClass::OrganicResidueParameterClass(AllControlClass &_ControlRef)
    :ControlRef(_ControlRef)
{
    parrCrop_Residue_Parameter = new CropResidueParameterClass[20];
    parrManure_Parameter = new ManureParameterClass[20];
}
//______________________________________________________________________________
OrganicResidueParameterClass::~OrganicResidueParameterClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~OrganicResidueParameterClass:"<<std::endl;
#endif

    delete[] parrCrop_Residue_Parameter;
    delete[] parrManure_Parameter;
#ifdef Destruct_Monitor
    std::cout<<"~OrganicResidueParameterClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
#ifdef LIU_ENGINE
const std::string &OrganicResidueParameterClass::getOrganicResidueParameterFileName()
{

    return ControlRef.organic_residue_parameter_name;
}
#endif
//______________________________________________________________________________
void OrganicResidueParameterClass::ReadInputParameters()
{
    //Implement later
    //M.Liu Jan. 22, 2014
    char errormessage[200];
    crop_residue_numbers = -1;
    manure_numbers = -1;
    #ifdef LIU_ENGINE
    std::string filename(getOrganicResidueParameterFileName());
    std::ifstream ifile(filename.c_str());
    #else
    std::ifstream ifile(ControlRef.organic_residue_filename.c_str()    );
    #endif
    if (ifile.is_open()) {
        std::string nameline("");
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            if (!record_key.empty()) {
                //read the data line
                std::string dataline("");
                std::getline(ifile,dataline);
                std::stringstream ss("");
                double ftemp(0.0);
                ss.str(dataline);
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Crop_Residues") == 0) {
                        crop_residue_numbers++;
                        ss>>parrCrop_Residue_Parameter[crop_residue_numbers].Label
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fraction_Of_Fast_Cycling_Biomass
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fraction_Of_Slow_Cycling_Biomass
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fraction_Of_Lignified_Biomass
                            >>ftemp  
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fraction_Of_Fast_Cycling_Crop_Root_Biomass
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fraction_Of_Slow_Cycling_Crop_Root_Biomass
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fraction_Of_Lignified_Crop_Root_Biomass
                            >>ftemp
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Fast_Cycling_Residue_Default_CN_Ratio
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Slow_Cycling_Residue_Default_CN_Ratio
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Lignified_Residue_Default_CN_Ratio
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Residue_Carbon_Fraction
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Area_To_Mass_Ratio_As_Standing_Residue
                            >>parrCrop_Residue_Parameter[crop_residue_numbers].Area_To_Mass_Ratio_As_Surface_Residue;

                    } else if (record_key.compare("Organic_Fertilizers") == 0) {
                        manure_numbers++;
                        ss>>parrManure_Parameter[manure_numbers].Label
                            >>parrManure_Parameter[manure_numbers].Fraction_Of_Fast_Cycling_Biomass
                            >>parrManure_Parameter[manure_numbers].Fraction_Of_Slow_Cycling_Biomass
                            >>parrManure_Parameter[manure_numbers].Fraction_Of_Lignified_Biomass
                            >>ftemp
                            >>parrManure_Parameter[manure_numbers].Fast_Cycling_Residue_Default_CN_Ratio
                            >>parrManure_Parameter[manure_numbers].Slow_Cycling_Residue_Default_CN_Ratio
                            >>parrManure_Parameter[manure_numbers].Lignified_Residue_Default_CN_Ratio
                            >>parrManure_Parameter[manure_numbers].Residue_Carbon_Fraction
                            >>parrManure_Parameter[manure_numbers].Ammonium_Content
                            >>parrManure_Parameter[manure_numbers].Water_Content
                            >>parrManure_Parameter[manure_numbers].Area_To_Mass_Ratio_As_After_Application;

                    } else if (record_key.compare("Half_Decomposition_Days") == 0) {
                        double half_decomposition_fast(0.0);     //days
                        double half_decomposition_slow(0.0);     //days
                        double half_decomposition_lignifed(0.0); //days
                        ss>>half_decomposition_fast>>half_decomposition_slow>>half_decomposition_lignifed;
                        Default_Fast_Cycling_Residues_Decomposition_Constant = -log(0.5)/half_decomposition_fast;
                        Default_Slow_Cycling_Residues_Decomposition_Constant = -log(0.5)/half_decomposition_slow;
                        Default_Lignified_Residues_Decomposition_Constant = -log(0.5)/half_decomposition_lignifed;
                    } else {
                        sprintf(errormessage,"Warning: Cann't find keyword %s",record_key.c_str());
                        nrerror(errormessage);
                    }
                }
            }
        }
    } else {
        sprintf(errormessage,"Cann't open parameter file %s"
           #ifdef LIU_ENGINE
           ,filename.c_str()
           #else
           ,ControlRef.organic_residue_filename.c_str()
           #endif
           );
        nrerror(errormessage);
    }
    crop_residue_numbers++;
    manure_numbers++;
    ifile.close();
}
//______________________________________________________________________________
int OrganicResidueParameterClass::FindCropResidueParameterIndex(std::string Crop_Residue_Name)
{
    int index = -9999;
    for (int i = 0; i < crop_residue_numbers; i++) {
        if (parrCrop_Residue_Parameter[i].Label.compare(Crop_Residue_Name) == 0) {
            index = i;
            i = crop_residue_numbers;
        }
    }
    return index;
}
//______________________________________________________________________________
int OrganicResidueParameterClass::FindManureParameterIndex(std::string Manure_Name)
{
    int index = -9999;
    for (int i = 0; i < manure_numbers; i++) {
        if (parrManure_Parameter[i].Label.compare(Manure_Name) == 0) {
            index = i;
            i = manure_numbers;
        }
    }
    return index;
}
//______________________________________________________________________________
int OrganicResidueParameterClass::getCropResidueNumbers()
{
    return crop_residue_numbers;
}
//______________________________________________________________________________
