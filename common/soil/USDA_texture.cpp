#include "soil/USDA_texture.h"

namespace USDA_texture
{

// In the following, by 'matric' I mean of the fine earth matrix,
// since these terms may be applied together with rock in with a fine earth matrix.
//______________________________________________________________________________
Label_description texture_code_label_table[] =
{{"UNK", "unknown"}                 // .
,{"APUM","ashy-pumiceous"}          //                matric-like                               pedogenesis
,{"ASHY","ashy"}                    //                matric-like                               pedogenesis
,{"ASK", "ashy-skeletal"}           //                matric-like                               pedogenesis
,{"BM",  "bouldery mucky"}          // rock  organic                                saturated?.
,{"BVM", "very bouldery mucky"}     // rock  organic                                saturated?.
,{"BXM", "extremely bouldery mucky"}// rock  organic                                saturated?.
,{"BY",  "bouldery"}                // rock. 
,{"BYV", "very bouldery"}           // rock. 
,{"BYX", "extremely bouldery"}      // rock. 
,{"C",   "clay"}                    //                 matric.
,{"CAM", "angular cobbly mucky"}    // rock  organic                                saturated?.
,{"CB",  "cobbly"}                  // rock. 
,{"CBA", "angular cobbly"}          // rock.
,{"CBV", "very cobbly"}             // rock. 
,{"CBX", "extremely cobbly"}        // rock. 
,{"CE",  "coprogenous earth"}       //       organic.
,{"CEM", "cemented"}                //                          cemented.
,{"CIND","cinders"}                 //                                                          pedogenesis
,{"CL",  "clay loam"}               //                 matric.
,{"CM",  "cobbly mucky"}            // rock  organic                                saturated?.
,{"CN",  "channery"}                // rock. 
,{"CNDY","cindery"}                 //
,{"CNV", "very channery"}           // rock.
,{"CNX", "extremely channery"}      // rock.
,{"COS", "coarse sand"}             //                 matric.
,{"COSL","coarse sandy loam"}       //                 matric.
,{"CR",  "cherty"}                  // rock.
,{"CRC", "coarse cherty"}           // rock.
,{"CRV", "very cherty"}             // rock.
,{"CRX", "extremely cherty"}        // rock.
,{"CVM", "very cobbly mucky"}       // rock  organic                                saturated?.
,{"CXM", "extremely cobbly mucky"}  // rock  organic                                saturated?.
,{"DE",  "diatomaceous earth"}      //                                                          pedogenesis.
,{"FB",  "fibric material"}         //       organic.
,{"FL",  "flaggy"}                  // rock.
,{"FLV", "very flaggy"}             // rock.
,{"FLX", "extremely flaggy"}        // rock.
,{"FRAG","fragmental material"}     // stone?                                                               condition?
,{"FS",  "fine sand"}               //                 matric.
,{"FSL", "fine sandy loam"}         //                 matric.
,{"G",   "gravel"}                  // rock.
,{"GCM", "coarse gravelly mucky"}   // rock  organic                                saturated?.
,{"GFM", "fine gravelly mucky"}     // rock  organic                                saturated?.
,{"GM",  "gravelly mucky"}          // rock  organic                                saturated?.
,{"GR",  "gravelly"}                // rock.
,{"GRC", "coarse gravelly"}         // rock.
,{"GRF", "fine gravelly"}           // rock.
,{"GRV", "very gravelly"}           // rock.
,{"GRX", "extremely gravelly"}      // rock.
,{"GSL", "gravelly sand loam" }     // rock            matric.
,{"GVM", "very gravelly mucky"}     // rock  organic                                saturated?.
,{"GXM", "extremely gravelly mucky"}// rock  organic                                saturated?.
,{"GYP", "gypsiferous material"}    //                                                          pedogenesis       specific_mineral
,{"HM",  "hemic material"}          //        organic.
,{"HPUM","hydrous-pumiceous"}       //                                               saturated? pedogenesis.
,{"HSK", "hydrous-skeletal"}        //                                               saturated? pedogenesis.
,{"HYDR","hydrous"}                 //                                               saturated?
,{"ICE", "ice or frozen soil"}      //                                               saturated?
,{"IND", "indurated"}               //                          cemented
,{"L",   "loam"}                    //                 matric.
,{"LCOS","loamy coarse sand"}       //                 matric.
,{"LFS", "loamy fine sand"}         //                 matric.
,{"LS",  "loamy sand"}              //                 matric.
,{"LVFS","loamy very fine sand"}    //                 matric.
,{"MARL","marl"}                    //                                   compaction?
,{"MEDL","medial"}                  //                 matric-like                                                   condition?
,{"MK",  "mucky"}                   //        organic                                saturated?.
,{"MPT", "mucky-peat"}              //        organic                                saturated?.
,{"MPUM","medial-pumiceous"}        //                 matric-like                              pedogenesis
,{"MSK", "medial-skeletal"}         //                 matric-like                              pedogenesis
,{"MUCK","muck"}                    //        organic.
,{"PEAT","peat"}                    //        organic.
,{"PT",  "peaty"}                   //        organic.
,{"PUM", "pumiceous"}               //                                                          pedogenesis.
,{"RB",  "rubbly"}                  // rock.   (also called brash)
,{"S",   "sand"}                    //                 matric.
,{"SC",  "sandy clay"}              //                 matric.
,{"SCL", "sandy clay loam"}         //                 matric.
,{"SG",  "sand and gravel"}         // rock            matric.
,{"SH",  "shaly"}                   // rock.
,{"SHV", "very shaly"}              // rock.
,{"SHX", "extremely shaly"}         // rock.
,{"SI",  "silt"}                    //                 matric.
,{"SIC", "silty clay"}              //                 matric.
,{"SICL","silty clay loam"}         //                 matric.
,{"SIL", "silt loam"}               //                 matric.
,{"SL",  "sandy loam"}              //                 matric.
,{"SM",  "stony mucky"}             // rock   organic                                saturated?.
,{"SP",  "sapric material"}         //        organic.
,{"SR",  "stratified"}              //                                                                      condition?
,{"ST",  "stony"}                   // rock.
,{"STL", "stony loam"}              // rock            matric.
,{"STV", "very stony"}              // rock.
,{"STX", "extremely stony"}         // rock.
,{"SVM", "very stony mucky"}        // rock   organic                                saturated?.
,{"SXM", "extremely stony mucky"}   // rock   organic                                saturated?.
,{"SY",  "slaty"}                   // rock.
,{"SYV", "very slaty"}              // rock.
,{"SYX", "extremely slaty"}         // rock.
// moved to first,{"UNK", "unknown"}                 // .
,{"UWB", "unweathered bedrock"}     // rock.
,{"VAR", "variable"}                //                matric.
,{"VCOS","very_coarse_sand"}
,{"VFS", "very fine sand"}          //                matric.
,{"VFSL","very fine sandy loam"}    //                matric.
,{"WB",  "weathered bedrock"}       // rock.
,{0,0}};
//______________________________________________________________________________
// This the following texture specification
//

#ifdef NYI
080428 I am still in the process of coding these specifications
this is not critical, just for completeness.

struct Texture_specification texture_specification [] =
{//                                         Modifier      Other      Coarseness              Range    Rock frag  Shape       Origanic    Pedogenesis          ,secondary text. Earth
 { /*unk    Q*/  unknown                   ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*APUM   Q*/  ashy_pumiceous            ,not_modified ,ashy    ,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,pumiceous            ,unknown_texture,undenoted}
,{ /*ASHY   Q*/  ashy                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*ASK    Q*/  ashy_skeletal             ,not_modified ,ashy    ,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,skeletal             ,unknown_texture,undenoted}
,{ /*BM     Q*/  bouldery_mucky            ,not_modified ,no_other,  unspecified_coarseness ,no_range,bouldery  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*BVM    Q*/  very_bouldery_mucky       ,very         ,no_other,  unspecified_coarseness ,no_range,bouldery  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*BXM    Q*/  extremely_bouldery_mucky  ,extremely    ,no_other,  unspecified_coarseness ,no_range,bouldery  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*BY     Q*/  bouldery                  ,not_modified ,no_other,  unspecified_coarseness ,no_range,bouldery  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*BYV    Q*/  very_bouldery             ,very         ,no_other,  unspecified_coarseness ,no_range,bouldery  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*BYX    Q*/  extremely_bouldery        ,extremely    ,no_other,  unspecified_coarseness ,no_range,bouldery  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*C      T*/  clay                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CAM    Q*/  angular_cobbly_mucky      ,not_modified ,angular ,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*CB     Q*/  cobbly                    ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CBA    Q*/  angular_cobbly            ,not_modified ,angular ,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CBV    Q*/  very_cobbly               ,very         ,no_other,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CBX    Q*/  extremely_cobbly          ,extremely    ,no_other,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CE     Q*/  coprogenous_earth         ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,earth    }x
,{ /*CEM    Q*/  cemented                  ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CIND   Q*/  cinders                   ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,cindery              ,unknown_texture,undenoted}x
,{ /*CL     T*/  clay_loam                 ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CM     Q*/  cobbly_mucky              ,not_modified ,no_other,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*CN     Q*/  channery                  ,not_modified ,no_other,  unspecified_coarseness ,no_range,channery  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*CNDY   Q*/  cindery                   ,not_modified ,no_other,  unspecified_coarseness ,no_range,channery  ,not_rocky  ,not_organic,cindery              ,unknown_texture,undenoted}
,{ /*CNV    Q*/  very_channery             ,very         ,no_other,  unspecified_coarseness ,no_range,channery  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*CNX    Q*/  extremely_channery        ,extremely    ,no_other,  unspecified_coarseness ,no_range,channery  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*COS    T*/  coarse_sand               ,not_modified ,no_other,  coarse_coarseness      ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,sand           ,undenoted}
,{ /*COSL   T*/  coarse_sandy_loam         ,not_modified ,no_other,  coarse_coarseness      ,sandy   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,loam           ,undenoted}
,{ /*CR     Q*/  cherty                    ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,cherty               ,unknown_texture,undenoted}
,{ /*CRC    Q*/  coarse_cherty             ,not_modified ,no_other,  coarse_coarseness      ,no_range,fine_earth,not_rocky  ,not_organic,cherty               ,unknown_texture,undenoted}
,{ /*CRV    Q*/  very_cherty               ,very         ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,cherty               ,unknown_texture,undenoted}
,{ /*CRX    Q*/  extremely_cherty          ,extremely    ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*CVM    Q*/  very_cobbly_mucky         ,very         ,no_other,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*CXM    Q*/  extremely_cobbly_mucky    ,extremely    ,no_other,  unspecified_coarseness ,no_range,cobbly    ,spherical  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*DE     Q*/  diatomaceous_earth        ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,diatomaceous         ,unknown_texture,earth    }
,{ /*FB     Q*/  fibric_material           ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,fibric     ,unspecified_pedogenis,unknown_texture,material }
,{ /*FL     Q*/  flaggy                    ,not_modified ,no_other,  unspecified_coarseness ,no_range,flaggy    ,flat       ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*FLV    Q*/  very_flaggy               ,very         ,no_other,  unspecified_coarseness ,no_range,flaggy    ,flat       ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*FLX    Q*/  extremely_flaggy          ,extremely    ,no_other,  unspecified_coarseness ,no_range,flaggy    ,flat       ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*FRAG   Q*/  fragmental_material       ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*FS     T*/  fine_sand                 ,not_modified ,no_other,  fine_coarseness        ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,loam           ,undenoted}
,{ /*FSL    T*/  fine_sandy_loam           ,not_modified ,no_other,  fine_coarseness        ,sandy   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*G      Q*/  gravel                    ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GCM    Q*/  coarse_gravelly_mucky     ,not_modified ,no_other,  coarse_coarseness      ,no_range,gravelly  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*GFM    Q*/  fine_gravelly_mucky       ,not_modified ,no_other,  fine_coarseness        ,no_range,gravelly  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*GM     Q*/  gravelly_mucky            ,not_modified ,no_other,  unspecified_coarseness ,no_range,gravelly  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GR     Q*/  gravelly                  ,not_modified ,no_other,  unspecified_coarseness ,no_range,gravelly  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GRC    Q*/  coarse_gravelly           ,not_modified ,no_other,  coarse_coarseness      ,no_range,gravelly  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GRF    Q*/  fine_gravelly             ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GRV    Q*/  very_gravelly             ,very         ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GRX    Q*/  extremely_gravelly        ,extremely    ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GSL    T*/  gravelly_sand_loam        ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*GVM    Q*/  very_gravelly_mucky       ,very         ,no_other,  unspecified_coarseness ,no_range,gravelly  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*GXM    Q*/  extremely_gravelly_mucky  ,extremely    ,no_other,  unspecified_coarseness ,no_range,gravelly  ,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*GYP    Q*/  gypsiferous_material      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*HM     Q*/  hemic_material            ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*HPUM   Q*/  hydrous_pumiceous         ,not_modified ,hydrous ,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,pumiceous            ,unknown_texture,undenoted}x
,{ /*HSK    Q*/  hydrous_skeletal          ,not_modified ,hydrous ,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,skeletal             ,unknown_texture,undenoted}x
,{ /*HYDR   Q*/  hydrous                   ,not_modified ,hydrous ,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*ICE    Q*/  ice_or_frozen_soil        ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*IND    Q*/  indurated                 ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*L      T*/  loam                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*LCOS   T*/  loamy_coarse_sand         ,not_modified ,no_other,  coarse_coarseness      ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*LFS    T*/  loamy_fine_sand           ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*LS     T*/  loamy_sand                ,not_modified ,no_other,  unspecified_coarseness ,loamy   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,sand           ,undenoted}x
,{ /*LVFS   T*/  loamy_very_fine_sand      ,very         ,no_other,  fine                   ,loamy   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,sand           ,undenoted}x
,{ /*MARL   ?*/  marl                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*MEDL   Q*/  medial                    ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*MK     Q*/  mucky                     ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*MPT    ?*/  mucky_peat                ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*MPUM   Q*/  medial_pumiceous          ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,pumiceous            ,unknown_texture,undenoted}x
,{ /*MSK    Q*/  medial_skeletal           ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,skeletal             ,unknown_texture,undenoted}x
,{ /*MUCK   ?*/  muck                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*PEAT   ?*/  peat                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*PT     Q*/  peaty                     ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*PUM    Q*/  pumiceous                 ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,pumiceous            ,unknown_texture,undenoted}x
,{ /*RB     Q*/  rubbly                    ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*S      T*/  sand                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SC     T*/  sandy_clay                ,not_modified ,no_other,  unspecified_coarseness ,sandy   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SCL    T*/  sandy_clay_loam           ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SG     T*/  sand_and_gravel           ,not_modified ,no_other,  unspecified_coarseness ,no_range,gravelly  ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SH     Q*/  shaly                     ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,shaly                ,unknown_texture,undenoted}x
,{ /*SHV    Q*/  very_shaly                ,very         ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,shaly                ,unknown_texture,undenoted}x
,{ /*SHX    Q*/  extremely_shaly           ,extremely    ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,shaly                ,unknown_texture,undenoted}
,{ /*SI     T*/  silt                      ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SIC    T*/  silty_clay                ,not_modified ,no_other,  unspecified_coarseness ,silty   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SICL   T*/  silty_clay_loam           ,not_modified ,no_other,  unspecified_coarseness ,silty   ,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SIL    T*/  silt_loam                 ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SL     T*/  sandy_loam                ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SM     Q*/  stony_mucky               ,not_modified ,no_other,  unspecified_coarseness ,no_range,stony     ,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SP     Q*/  sapric_material           ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*SR     Q*/  stratified                ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}x
,{ /*ST     Q*/  stony                     ,not_modified ,no_other,  unspecified_coarseness ,no_range,stony     ,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*STL     */  stony_loam                ,not_modified ,no_other,  unspecified_coarseness ,no_range,stony     ,spherical  ,not_organic,unspecified_pedogenis,loam           ,undenoted}
,{ /*STV    Q*/  very_stony                ,very         ,no_other,  unspecified_coarseness ,no_range,stony     ,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*STX    Q*/  extremely_stony           ,extremely    ,no_other,  unspecified_coarseness ,no_range,stony     ,spherical  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*SVM    Q*/  very_stony_mucky          ,very         ,no_other,  unspecified_coarseness ,no_range,stony     ,spherical  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*SXM    Q*/  extremely_stony_mucky     ,extremely    ,no_other,  unspecified_coarseness ,no_range,stony     ,spherical  ,mucky      ,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*SY     Q*/  slaty                     ,not_modified ,no_other,  unspecified_coarseness ,no_range,IRRELEVENT,flat       ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*SYV    Q*/  very_slaty                ,very         ,no_other,  unspecified_coarseness ,no_range,IRRELEVENT,flat       ,not_organic,slaty                ,unknown_texture,undenoted}
,{ /*SYX    Q*/  extremely_slaty           ,extremely    ,no_other,  unspecified_coarseness ,no_range,IRRELEVENT,flat       ,not_organic,slaty                ,unknown_texture,undenoted}
// ,{ /*UNK    -*/  unknown                   ,not_modified ,no_other,  unspecified_coarseness ,no_range,fine_earth,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*UWB    T*/  unweathered_bedrock       ,un           ,weathered, unspecified_coarseness ,no_range,IRRELEVENT,not_rocky  ,not_organic,bedrock              ,unknown_texture,undenoted}
,{ /*VAR    -*/  variable                  ,not_modified ,no_other,  unspecified_coarseness ,no_range,IRRELEVENT,not_rocky  ,not_organic,unspecified_pedogenis,unknown_texture,undenoted}
,{ /*VCOS   T*/  very_coarse_sand          ,very         ,no_other,  coarse_coarseness      ,no_range,IRRELEVENT,not_rocky  ,not_organic,unspecified_pedogenis,sand           ,undenoted}
,{ /*VFS    T*/  very_fine_sand            ,very         ,no_other,  fine_coarseness        ,no_range,IRRELEVENT,not_rocky  ,not_organic,unspecified_pedogenis,sand           ,undenoted}
,{ /*VFSL   T*/  very_fine_sandy_loam      ,very         ,no_other,  fine_coarseness        ,sandy   ,IRRELEVENT,not_rocky  ,not_organic,unspecified_pedogenis,loam           ,undenoted}
,{ /*WB     T*/  weathered_bedrock         ,not_modified ,weathered, unspecified_coarseness ,no_range,IRRELEVENT,not_rocky  ,not_organic,bedrock              ,unknown_texture,undenoted}
};
//______________________________________________________________________________
/* Peats (http://en.wikipedia.org/wiki/Peat)
Fibric peats are the least decomposed, and comprise intact fiber.
Hemic peats are somewhat decomposed.
sapric are the most decomposed.

Muck (http://en.wikipedia.org/wiki/Muck_%28soil%29)
Muck is a soil made up primarily of humus from drained swampland
  (I assume much is more decomposed than sapric, but less than humus/humic)

The soil qualifiers have matric like texture
Ashy is sand like
Medial is loam like



Spherical and cubelike:
2 - 75      gravelly
2 - 5       fine gravelly
5 - 20      medium gravelly
20 - 75     coarse gravelly
75 - 250    cobbly
250 - 600   stony
> 600       bouldery
very boldery
extremely boldery

Flat:
2 - 150     channery
150 - 380   flaggy
380 - 600   stony
> 600       bouldery


 Modifier for rock fragments.

  Rock fragments by volume [%]
 Adjectival modifier

< 15  no modifier
15 - 30  gravelly loam
30 - 60  very flaggy loam
> 60     extremely bouldery loam
*/

/*
enum Rock_fragment_code
{  fine_earth  // Not a USDA code, used as a place holder
,  gravelly    // spherical
,  cobbly      // spherical
,  channery    // flat
,  flaggy      // flat
,  stony       // spherical or flat
,  bouldery    // spherical or flat
};
*/

#endif
}; //  namespace USDA texture

