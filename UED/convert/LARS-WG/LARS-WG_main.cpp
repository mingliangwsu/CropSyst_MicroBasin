#include "LARS_WG_convertor.h"

int main(int argc,const char *argv[])
{
   LARS_WG_format_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
}


