#ifndef CROPPARAMETERCOLLECTION_H
#define CROPPARAMETERCOLLECTION_H

#include "crop/cropinputclass.h"
//#include "control/allcontrolclass.h"

class CropInputClass;
class AllControlClass;
//______________________________________________________________________________
class CropParameterCollection
{
public:
    AllControlClass &ControlRef;
    CropInputClass *parrCropParameter;
    int FindInnerID(std::string Crop_Name);
    CropParameterCollection(AllControlClass &_ControlRef);
    ~CropParameterCollection();
    void ReadCropParameterFiles();
};
//_2014-02-??___________________________________________________________________
#endif // CROPPARAMETERCOLLECTION_H
