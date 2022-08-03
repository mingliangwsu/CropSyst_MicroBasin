#include "soil/texture.h"
#include "corn/primitive.h"
#include <string>
#include <ctype.h>
namespace CS {
extern const char *texture_triangle_data[];

// These are fine earth textures where gravels (> 2mm) have been excluded
// http://www.cartage.org.lb/en/themes/sciences/earthscience/Geology/Soils/SoilMorphology/SoilMorphology/SoilTexture/SoilTexture.htm
//______________________________________________________________________________
struct Texture_percentage_range
{  USDA_texture::Texture_code    texture_code
;  nat8                 sand_centroid
;  nat8                 clay_centroid
;  nat8                 sand_min
;  nat8                 sand_max
;  nat8                 clay_min
;  nat8                 clay_max
;};
using namespace USDA_texture;
//______________________________________________________________________________
Texture_percentage_range texture_percentage_ranges[] =
{//texture code        sand clay sand      clay
 //                   centroid min max    min max
 { clay                 ,25,50,  0, 45   , 45,100}
,{ clay_loam            ,30,34, 20, 45   , 25, 40}
,{ coarse_sand          ,90, 8, 90,100   ,  0, 10}
,{ coarse_sandy_loam    ,70, 7, 45, 85   ,  0, 15}   // coarseness accounted for in clay
,{ fine_sand            ,83, 2, 85,100   ,  0, 10}   // fine not accounted for
,{ fine_sandy_loam      ,47, 4, 45, 85   , 15, 20}
,{ loam                 ,42,20, 25, 52   ,  8, 28}
,{ loamy_coarse_sand    ,80, 4, 70, 95   ,  0, 25}  // just loamy sand
,{ loamy_fine_sand      ,83,15, 70, 95   ,  0, 25}  // just loamy sand
,{ loamy_sand           ,81,10, 70, 95   ,  0, 25}  // just loamy sand
,{ loamy_very_fine_sand ,18,17, 70, 95   ,  0, 25}  // just loamy sand
,{ sand                 ,90, 8, 85,100   ,  0, 10}
,{ sandy_clay           ,50,42, 45, 65   , 35, 55}
,{ sandy_clay_loam      ,60,28, 45, 80   , 20, 35}
,{ sand_and_gravel      ,89, 2, 85,100   ,  0, 10} // just sand
,{ silt                 , 7,11,  0, 20   ,  0, 12}
,{ silty_clay           , 8,45,  0, 20   , 40, 50}
,{ silty_clay_loam      ,10,35,  0, 20   , 28, 40}
,{ silt_loam            ,20,16,  0, 50   ,  0, 28}
,{ sandy_loam           ,64,12, 45, 90   ,  0, 20}
,{ unweathered_bedrock  ,97, 3, 95,100   ,  0,  5} // Not a real texture but superimposes a texture
,{ very_fine_sand       ,93, 7, 85,100   ,  0, 10} // just sand
,{ very_fine_sandy_loam ,66,18, 45, 85   , 15, 20}
// NYI very coarse sand
,{ weathered_bedrock    ,97, 3, 95,100   ,  0,  5} // Not a real texture but superimposes a texture
,{ unknown ,0,0,0,0,0,0} // to end list
};
//______________________________________________________________________________
Soil_texture::Soil_texture
(float32 _sand, float32 _clay, float32 _silt)
:percent_sand(_sand)
,percent_clay(_clay)
,percent_silt(_silt == 0 ? 100 - (_sand + _clay) : _silt)
,texture_code(unknown) // unknown_USDA_texture
,texture_qualifier(unknown) // unknown_USDA_texture
{  determine_texture();
}
//______________________________________________________________________________
Soil_texture::Soil_texture
( USDA_texture::Texture_code    _texture_code
, USDA_texture::Texture_code    _texture_qualifier
, nat8                 low_clay
, nat8                 high_clay
)
:percent_sand(1)
,percent_clay(1)
,percent_silt(1)
,texture_code(_texture_code)
,texture_qualifier(_texture_qualifier)
{  determine_percentages(low_clay,high_clay);
}
//______________________________________________________________________________
Soil_texture::Soil_texture
(const char *texture_code_label)
:percent_sand(1)
,percent_clay(1)
,percent_silt(1)
,texture_code(unknown) //(unknown_USDA_texture) // Setup below
,texture_qualifier(unknown) //(unknown_USDA_texture)
{
//             The texture code label may have a qualifier texture code and primary texture code separated by -
//             these will be extracted and the codes set accordingly followed by percentages

//             WARNING: make sure these are sorted descending by length!
   std::string texture_code_str(texture_code_label);    //001117

// secondary texture codes
        if (texture_code_str.find("-COSL") != std::string::npos) texture_code = coarse_sandy_loam;     // 070424 these may need to be find_substring
   else if (texture_code_str.find("-LCOS") != std::string::npos) texture_code = loamy_coarse_sand;
   else if (texture_code_str.find("-LVFS") != std::string::npos) texture_code = loamy_very_fine_sand;
   else if (texture_code_str.find("-SICL") != std::string::npos) texture_code = silty_clay_loam;
   else if (texture_code_str.find("-VFSL") != std::string::npos) texture_code = very_fine_sandy_loam;

   else if (texture_code_str.find("-COS") != std::string::npos) texture_code = coarse_sand;
   else if (texture_code_str.find("-FSL") != std::string::npos) texture_code = fine_sandy_loam;
   else if (texture_code_str.find("-LFS") != std::string::npos) texture_code = loamy_fine_sand;
   else if (texture_code_str.find("-SCL") != std::string::npos) texture_code = sandy_clay_loam;
   else if (texture_code_str.find("-SIC") != std::string::npos) texture_code = silty_clay;
   else if (texture_code_str.find("-SIL") != std::string::npos) texture_code = silt_loam;
   else if (texture_code_str.find("-UWB") != std::string::npos) texture_code = unweathered_bedrock;
   else if (texture_code_str.find("-VFS") != std::string::npos) texture_code = very_fine_sand;

   else if (texture_code_str.find("-CL") != std::string::npos) texture_code = clay_loam;
   else if (texture_code_str.find("-FS") != std::string::npos) texture_code = fine_sand;
   else if (texture_code_str.find("-LS") != std::string::npos) texture_code = loamy_sand;
   else if (texture_code_str.find("-SC") != std::string::npos) texture_code = sandy_clay;
   else if (texture_code_str.find("-SG") != std::string::npos) texture_code = sand_and_gravel;
   else if (texture_code_str.find("-SI") != std::string::npos) texture_code = silt;
   else if (texture_code_str.find("-SL") != std::string::npos) texture_code = sandy_loam;
   else if (texture_code_str.find("-WB") != std::string::npos) texture_code = weathered_bedrock;

   else if (texture_code_str.find("-C") != std::string::npos) texture_code =  clay;
   else if (texture_code_str.find("-L") != std::string::npos) texture_code = loam;
   else if (texture_code_str.find("-S") != std::string::npos) texture_code = sand;

// Primary texture codess
   else if (texture_code_str.find("COSL") != std::string::npos) texture_code = coarse_sandy_loam;
   else if (texture_code_str.find("LCOS") != std::string::npos) texture_code = loamy_coarse_sand;
   else if (texture_code_str.find("LVFS") != std::string::npos) texture_code = loamy_very_fine_sand;
   else if (texture_code_str.find("SICL") != std::string::npos) texture_code = silty_clay_loam;
   else if (texture_code_str.find("VFSL") != std::string::npos) texture_code = very_fine_sandy_loam;

   else if (texture_code_str.find("COS") != std::string::npos) texture_code = coarse_sand;
   else if (texture_code_str.find("FSL") != std::string::npos) texture_code = fine_sandy_loam;
   else if (texture_code_str.find("LFS") != std::string::npos) texture_code = loamy_fine_sand;
   else if (texture_code_str.find("SCL") != std::string::npos) texture_code = sandy_clay_loam;
   else if (texture_code_str.find("SIC") != std::string::npos) texture_code = silty_clay;
   else if (texture_code_str.find("SIL") != std::string::npos) texture_code = silt_loam;
   else if (texture_code_str.find("UWB") != std::string::npos) texture_code = unweathered_bedrock;
   else if (texture_code_str.find("VFS") != std::string::npos) texture_code = very_fine_sand;

   else if (texture_code_str.find("CL") != std::string::npos) texture_code = clay_loam;
   else if (texture_code_str.find("FS") != std::string::npos) texture_code = fine_sand;
   else if (texture_code_str.find("LS") != std::string::npos) texture_code = loamy_sand;
   else if (texture_code_str.find("SC") != std::string::npos) texture_code = sandy_clay;
   else if (texture_code_str.find("SG") != std::string::npos) texture_code = sand_and_gravel;
   else if (texture_code_str.find("SI") != std::string::npos) texture_code = silt;
   else if (texture_code_str.find("SL") != std::string::npos) texture_code = sandy_loam;
   else if (texture_code_str.find("WB") != std::string::npos) texture_code = weathered_bedrock;

   else if (texture_code_str.find("C") != std::string::npos) texture_code = clay;
   else if (texture_code_str.find("L") != std::string::npos) texture_code = loam;
   else if (texture_code_str.find("S") != std::string::npos) texture_code = sand;
   determine_percentages(0,0);
}
//______________________________________________________________________________
void Soil_texture::determine_percentages
( nat8   /*NYI low_clay*/
, nat8 ) /*NYI high_clay*/
{  // Currently the texture qualifier code is not used
   // but Saxton's equations can be used to adjust
   // hydraulic properties based on percent gravel
   for (int index = 0; texture_percentage_ranges[index].texture_code;index++)
   {  if (texture_percentage_ranges[index].texture_code == texture_code)
      {  percent_sand = texture_percentage_ranges[index].sand_centroid;
         percent_clay = texture_percentage_ranges[index].clay_centroid;
         percent_silt = 100 - (percent_sand + percent_clay);
         return;
      }
   }
}
//______________________________________________________________________________
void Soil_texture::determine_texture()
{  nat8  sand_index = 100 - percent_sand;
   nat8  clay_index = percent_clay;
   char texture_label = toupper(texture_triangle_data[sand_index][clay_index]);
   switch (texture_label)
   {  case 'A' : texture_code = sand; break;
      case 'B' : texture_code = loamy_sand; break;
      case 'C' : texture_code = sandy_loam; break;
      case 'D' : texture_code = sandy_clay_loam; break;
      case 'E' : texture_code = loam; break;
      case 'F' : texture_code = silt_loam; break;
      case 'G' : texture_code = clay_loam; break;
      case 'H' : texture_code = silty_clay_loam; break;
      case 'I' : texture_code = silty_clay; break;
      case 'J' : texture_code = clay; break;
   }
   // texture_qualifier not yet implemented
}
//______________________________________________________________________________
bool Soil_texture::is_root_penetratable() const
{  return (texture_code != weathered_bedrock)
       && (texture_code != unweathered_bedrock);
}
//______________________________________________________________________________
} // namespace CS

