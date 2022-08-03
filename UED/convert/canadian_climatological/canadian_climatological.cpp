
#include <UED/convert/canadian_climatological/canadian_climatological_convertor.h>

#include <climgen/source/options.h>
#include <common/simulation/paths.h>

/*_______*/
/*_______*/ int main(int argc, char *argv[])
/*_______*/ {
//031212_//    Example import command line
//031212_//    import "c:\temp\climgen_assist\marquez\6034075.ued" "c:\temp\climgen_assist\marquez\6034075Dly.txt"
//031212_//    import "c:\temp\climgen_assist\marquez\6034075.ued" "c:\temp\climgen_assist\marquez\6034075HLY.txt"
//031212_//    Example export command line
//031212_//    export "c:\temp\climgen_assist\marquez\6034075.ued"
/*_______*/    canadian_climatological_convertor_NS::Canadian_climatological_format_convertor  convertor(argc,argv);
/*_______*/    int result =  convertor.convert();
/*_______*/    convertor.notify_climgen();
/*_______*/    return result;
/*_______*/ };
/*_______*/
/*_______*/
/*_______*/ // 070422 134 lines

