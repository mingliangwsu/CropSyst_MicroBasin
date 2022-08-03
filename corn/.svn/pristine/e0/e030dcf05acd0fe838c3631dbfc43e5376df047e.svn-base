
/*  escseq.c    Escape sequences for a number of terminals and printers */

/* Abreviations:
   CPI  = Chars per inch
   LPI  = Lines per inch
   VMI  = Vertical motion index
   HMI  = Horizontal motion index
   LM   = Left margin
   RM   = Right margin
   TM   = Top margin
   BM   = bottom margin
   VT   = Vertical Tab
   HT   = Horizontal Tab
   PerfSkip = Perforation skip
   ORIENT   = Orientation
   HALFLF   = Half line feed
   VERT = Vertical
   HORZ = Horizontal
   Ms   = Character widths/heights (The size of one character in the current
          character set.
   Dots = the number of dots.
   SubS = Subscript
   SupS = SuperScript
   PropSpace = Proportional spacing.
   Emf  = Emphasised
   Exp  = Expanded mode
   Cond = Condense mode (17cpi)



*/

#define ANSI_ES      0
#define HPLASERJET_ES   1
#define HPDESKJET_ES    2
#define HPTHINKJET_ES   3
#define DIABLO_ES    4
#define EPSON9_ES    5
#define EPSON24_ES   6

/*

  17 CPI = compressed
  12 CPI = Elite
  10 CPI = Pica
  8.5CPI = DW Compressed
  6  CPI = DW Elite
  5  CPI = DW Pica


*/

  char  *ES_attributes[][]
  {               /*   ANSI   HPLASERJET     HPDESKJET      HPTHINKJET  DIABLO EPSON9           EPSON24
/* ES_17CPIon     */{""      ,"\033(s16.66H","\033(s16.66H","\033&k2S" ,""    ,"\017"          ,""
/* ES_17CPIoff    */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\022"          ,""

/* ES_12CPIon     */{""      ,"\033(s12H"   ,"\033(s12H"   ,"\033&k0S" ,""    ,"\033M"         ,""
/* ES_12CPIoff    */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\033P"         ,""

/* ES_10CPIon     */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\033P"         ,""
/* ES_10CPIoff    */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\033P"         ,""

/* ES_8CPIon      */{""      ,"\033(s8H"    ,"\033(s8H"    ,""         ,""    ,"\017\033W1"    ,""
/* ES_8CPIoff     */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\022\033W0"    ,""

/* ES_6CPIon      */{""      ,"\033(s6H"    ,"\033(s6H"    ,"\033&k1S" ,""    ,"\033M\033W1"   ,""
/* ES_6CPIoff     */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\033P\033W0"   ,""

/* ES_5CPIon      */{""      ,"\033(s5H"    ,"\033(s5H"    ,""         ,""    ,"\033P\033W1"   ,""
/* ES_5CPIoff     */{""      ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,""    ,"\033P\033W0"   ,""

/* ES_PropSpaceon */{""      ,"\033(s1P"    ,"\033(s1P"    ,""         ,""    ,"\033p1"        ,""
/* ES_PropSpaceoff*/{""      ,"\033(s0P"    ,"\033(s0P}    ,""         ,""    ,"\033p0"        ,""

/* ES_Portrait    */{""      ,"\033&l0O"    ,"\033&l0O"    ,""         ,""
/* ES_Landscape   */{""      ,"\033&l1O"    ,"\033&l1O"    ,""         ,""
  }



/* ES_PageLen_Ms  /{""      ,"\033&l%dP"   ,"\033&l%dP"  ,""         ,""

* ES_CS_PC8     /{""      ,"\033(10U"    ,""           ,""         ,""
* ES_CS_Roman8  /{""      ,"\033(8U"     ,""           ,""         ,""
* ES_CS_ECMA94  /{""      ,"\033(0N"     ,""           ,""         ,""
*/