#include <UED/convert/AgWeatherNet/AgWeatherNet_convertor.h>

int main(int argc, const char *argv[])
{
   AgWeatherNet_format_convertor convertor(argc,argv);
   int result =  convertor.convert();
   convertor.notify_climgen();
   return result;
};
