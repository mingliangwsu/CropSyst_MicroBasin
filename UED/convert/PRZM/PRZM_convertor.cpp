//---------------------------------------------------------------------------

#pragma hdrstop

#include "PRZM_convertor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


PRZM_convertor::PRZM_convertor(int argc, const char *argv[])
:  UED_convertor(argc, argv)
{
};
//______________________________________________________________________________
uint32 PRZM_convertor::perform_import()
{
/* Not yet implemented
*/
   cerr << "Import for UED -> PRZM is not currently implemented." << endl;
   press_return_before_exit = true;
   return 0;


};
//______________________________________________________________________________
uint32 PRZM_convertor::perform_export()
{
/*060616_*/    uint32 records_exported = 0;
/*_______*/    cout << "Openning and indexing database..." << '\r';

/*_______*/    UED_indexed_database ued_file(parameters.ued_filename.c_str()/*060616 UED_filename*/,true);
   
};
