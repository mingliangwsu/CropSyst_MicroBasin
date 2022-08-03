
#include <fstream>
#include "crop/crop_param_configured.h"
//#include "crop/crop_param_YAML.h"
#include "corn/format/YAML/YAML_stream.h"

int main(int argc, char *argv[])
{

   CropSyst::Crop_parameters crop_parameters;
   CropSyst::Crop_parameters_configured crop_param_YAML(crop_parameters);
   crop_param_YAML.initialize();
   //CropSyst::Crop_parameters_YAML_structured crop_param_YAML;

   {
   std::ofstream configure_test
      ("C:\\dev\\CS_suite\\CropSyst\\convert\\crop\\test.CS_crop.yaml");
   crop_param_YAML.write(configure_test);
   }
   // For this test, I am setting up to read the YAML document
   // not doing the conversion or writing it.

   YAML::Stream YAML_stream;

   std::wifstream YAML_file
      #ifdef __linux__
      ("/home/rnelson/dev/CS_suite/CropSyst/convert/crop/test.CS_crop.yaml");
      #else
      ("C:\\dev\\CS_suite\\CropSyst\\convert\\crop\\test.CS_crop.yaml");
      #endif

   YAML::Parse_error_code error = YAML_stream.parse_document_known(YAML_file,crop_param_YAML);

   return error == YAML::ERROR_none
      ? EXIT_SUCCESS
      : EXIT_FAILURE;
}
