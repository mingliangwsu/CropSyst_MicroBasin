#include <UED/convert/IRIMO/IRIMO_convertor.h>

int main(int argc,const char *argv[])
{
   IRIMO_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
};
