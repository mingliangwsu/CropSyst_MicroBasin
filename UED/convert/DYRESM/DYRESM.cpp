#include <UED/convert/DYRESM/DYRESM_convertor.h>

int main(int argc,const char *argv[])
{
   DYRESM_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
};

