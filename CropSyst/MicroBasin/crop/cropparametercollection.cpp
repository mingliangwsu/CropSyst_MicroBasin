
#include "cropparametercollection.h"
#include "control/allcontrolclass.h"
#include <iostream>
//______________________________________________________________________________
CropParameterCollection::CropParameterCollection(AllControlClass &_ControlRef)
    :ControlRef(_ControlRef)
{
    parrCropParameter = new CropInputClass[ControlRef.getTotalCropTypes()];
}
//______________________________________________________________________________
CropParameterCollection::~CropParameterCollection()
{
#ifdef Destruct_Monitor
    std::cout<<"~CropParameterCollection:"<<std::endl;
#endif
    delete[] parrCropParameter;
#ifdef Destruct_Monitor
    std::cout<<"~CropParameterCollection done."<<std::endl;
#endif
}
//______________________________________________________________________________
void CropParameterCollection::ReadCropParameterFiles()
{
    for (int i = 0; i < ControlRef.getTotalCropTypes(); i++) {
        parrCropParameter[i].ReadCropParameters(ControlRef.Crop_Name_Lists[i],ControlRef);
    }
#ifdef LIU_DEBUG
    std::cout<<"Total crop types:"<<ControlRef.getTotalCropTypes()
             <<"    All crop parameter files are read."<<std::endl;
#endif
}
//______________________________________________________________________________
int CropParameterCollection::FindInnerID(std::string Crop_Name)
{   int innerid(-1);
    for (int i = 0; i < ControlRef.getTotalCropTypes(); i++) {
        if (Crop_Name.compare(ControlRef.Crop_Name_Lists[i]) == 0) {
            innerid = i;
            i = ControlRef.getTotalCropTypes();
        }
    }
    return innerid;
}
//______________________________________________________________________________
