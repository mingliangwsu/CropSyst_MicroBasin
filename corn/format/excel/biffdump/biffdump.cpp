#include <corn/format/binfstrm.h>
#include <corn/format/biffcode.h>
//______________________________________________________________________________
struct Biff_code_labels
{  uint16 code;
   char  *label;
};
//______________________________________________________________________________
Biff_code_labels biff_code_labels_00_9F[] =
{
// The following are in sequence
 {BIFF2_CODE_DIMENSIONS           ,"2_DIMENSIONS"}    //       0x00
,{BIFF_CODE_BLANK                 ,"BLANK"}    //       0x01
,{BIFF_CODE_INTEGER               ,"INTEGER"}    //       0x02
,{BIFF_CODE_NUMBER                ,"NUMBER"}    //       0x03
,{BIFF_CODE_LABEL                 ,"LABEL"}    //       0x04
,{BIFF_CODE_BOOLERR               ,"BOOLERR"}    //       0x05
,{BIFF_CODE_FORMULA               ,"FORMULA"}    //       0x06
,{0x07                            ,"n/a"}    //
,{BIFF_CODE_STRING                ,"STRING"}    //       0x08
,{BIFF2_CODE_BOF                  ,"2_BOF"}    //       0x09
,{BIFF_CODE_EOF                   ,"EOF"}    //     0x0A
,{BIFF_CODE_INDEX                 ,"INDEX"}    //     0x0B
,{BIFF_CODE_CALCCOUNT             ,"CALCCOUNT"}    //     0x0C
,{BIFF_CODE_CALCMODE              ,"CALCMODE"}    //     0x0D
,{BIFF_CODE_PRECISION             ,"PRECISION"}    //     0x0E
,{BIFF_CODE_REFMODE               ,"REFMODE"}    //     0x0F
,{BIFF_CODE_DELTA                 ,"DELTA"}    //     0x10
,{BIFF_CODE_ITERATION             ,"ITERATION"}    //     0x11
,{BIFF_CODE_PROTECT               ,"PROTECT"}    //     0x12
,{BIFF_CODE_PASSWORD              ,"PASSWORD"}    //     0x13
,{BIFF_CODE_HEADER                ,"HEADER"}    //     0x14
,{BIFF_CODE_FOOTER                ,"FOOTER"}    //     0x15
,{BIFF_CODE_EXTERNCOUNT           ,"EXTERNCOUNT"}    //     0x16
,{BIFF_CODE_EXTERNSHEET           ,"EXTERNSHEET"}    //     0x17
,{BIFF_CODE_NAME                  ,"NAME"}    //     0x18
,{BIFF_CODE_WINDOW_PROTECT        ,"WINDOW_PROTECT"}    //     0x19
,{BIFF_CODE_VERTICAL_PAGE_BREAKS  ,"VERTICAL_PAGE_BREAKS"}    //    ,""}    //   0x1A  /* VERTICALPAGEBREAKS - Explicit Column Page Breaks */
,{BIFF_CODE_HORIZONTAL_PAGE_BREAKS,"HORIZONTAL_PAGE_BREAKS"}    //    ,""}    //   0x1B /* HORIZONTALPAGEBREAKS - Explicit Row Page Breaks */
,{BIFF_CODE_NOTE                  ,"NOTE"}    //   0x1C
,{BIFF_CODE_SELECTION             ,"SELECTION"}    //   0x1D
,{BIFF_CODE_FORMAT                ,"FORMAT"}    //   0x1E
,{BIFF_CODE_FORMATCOUNT           ,"FORMATCOUNT"}    //   0x1F
,{BIFF_CODE_COLUMN_DEFAULT        ,"COLUMN_DEFAULT"}    //   0x20
,{BIFF_CODE_ARRAY                 ,"ARRAY"}    //   0x21
,{BIFF_CODE_1904                  ,"1904"}    //   0x22
,{BIFF_CODE_EXTERNNAME            ,"EXTERNNAME"}    //   0x23
,{BIFF_CODE_COLWIDTH              ,"COLWIDTH"}    //   0x24
,{BIFF_CODE_DEFAULT_ROW_HEIGHT    ,"DEFAULT_ROW_HEIGHT"}    //   0x25
,{BIFF_CODE_LEFT_MARGIN           ,"LEFT_MARGIN"}    //   0x26
,{BIFF_CODE_RIGHT_MARGIN          ,"RIGHT_MARGIN"}    //   0x27
,{BIFF_CODE_TOP_MARGIN            ,"TOP_MARGIN"}    //   0x28
,{BIFF_CODE_BOTTOM_MARGIN         ,"BOTTOM_MARGIN"}    //   0x29
,{BIFF_CODE_PRINT_ROW_HEADERS     ,"PRINT_ROW_HEADERS"}    //   0x2A
,{BIFF_CODE_PRINT_GRIDLINES       ,"PRINT_GRIDLINES"}    //   0x2B
,{0x2C                            ,"n/a"}
,{0x2D                            ,"n/a"}
,{0x2E                            ,"n/a"}
,{BIFF_CODE_FILEPASS              ,"FILEPASS"}    //   0x2F
,{0x30                            ,"n/a"}
,{BIFF_CODE_FONT                  ,"FONT"}    //   0x31 /* @ FONT - Font Description */
,{BIFF_CODE_FONT2                 ,"FONT2"}    //   0x32
,{0x33                            ,"n/a"}
,{0x34                            ,"n/a"}
,{0x35                            ,"n/a"}
,{BIFF_CODE_TABLE                 ,"TABLE"}    //   0x36
,{BIFF_CODE_TABLE2                ,"TABLE2"}    //   0x37
,{0x38                            ,"n/a"}
,{0x39                            ,"n/a"}
,{0x3A                            ,"n/a"}
,{0x3B                            ,"n/a"}
,{BIFF_CODE_CONTINUE              ,"CONTINUE"}    //   0x3C /* CONTINUE - Continues Long Records */
,{BIFF_CODE_WINDOW1               ,"WINDOW1"}    //   0x3D /* WINDOW1 - Window Information */
,{BIFF_CODE_WINDOW2               ,"WINDOW2"}    //   0x3E
,{0x3F                            ,"n/a"}
,{BIFF_CODE_BACKUP                ,"BACKUP"}    //   0x40 /* BACKUP - Save Backup Version of the File */
,{BIFF_CODE_PANE                  ,"PANE"}    //   0x41  /* PANE - Number of Panes and Their Position */
,{BIFF4_CODE_CODEPAGE             ,"4_CODEPAGE"}    //   0x42 /* @ CODEPAGE - Default Code Page */
,{0x43                            ,"n/a"}
,{0x44                            ,"n/a"}
,{0x45                            ,"n/a"}
,{0x46                            ,"n/a"}
,{0x47                            ,"n/a"}
,{0x48                            ,"n/a"}
,{0x49                            ,"n/a"}
,{0x4A                            ,"n/a"}
,{0x4B                            ,"n/a"}
,{0x4c                            ,"n/a"}
,{BIFF4_CODE_PLS                  ,"4_PLS"}    //   0x4D /* PLS - Environment-Specific Print Record */
,{0x4E                            ,"n/a"}
,{0x4F                            ,"n/a"}
,{BIFF4_CODE_DCON                 ,"4_DCON"}    //   0x50 /* DCON - Data Consolidation Information */
,{BIFF4_CODE_DCONREF              ,"4_DCONREF"}    //   0x51     /* DCONREF - Data Consolidation References */
,{BIFF4_CODE_DCONNAME             ,"4_DCONNAME"}    //   0x52 /* DCONNAME - Data Consolidation Named References */
,{0x53                            ,"n/a"}
,{0x54                            ,"n/a"}
,{BIFF4_CODE_DEFCOLWIDTH          ,"4_DEFCOLWIDTH"}    //   0x55 /* DEFCOLWIDTH - Default Width for Columns */
,{0x56                            ,"n/a"}
,{0x57                            ,"n/a"}
,{0x58                            ,"n/a"}
,{BIFF4_CODE_XCT                  ,"4_XCT"}    //   0x59 /* XCT - CRN Record Count */
,{BIFF4_CODE_CRN                  ,"4_CRN"}    //   0x5A /* CRN - Nonresident Operands */
,{BIFF4_CODE_FILESHARING          ,"4_FILESHARING"}    //   0x5B  /* FILESHARING - File-Sharing Information */
,{BIFF4_CODE_WRITEACCESS          ,"4_WRITEACCESS"}    //   0x5C  /* @ WRITEACCESS - Write Access User Name */
,{BIFF4_CODE_OBJ                  ,"4_OBJ"}    //   0x5D  /* OBJ - Describes a Graphic Object */
,{BIFF4_CODE_UNCALCED             ,"4_UNCALCED"}    //   0x5E /* UNCALCED - Recalculation Status */
,{BIFF4_CODE_SAVERECALC           ,"4_SAVERECALC"}    //   0x5F /* SAVERECALC - Recalculate Before Save */
,{BIFF4_CODE_TEMPLATE             ,"4_TEMPLATE"}    //   0x60 /* TEMPLATE - Workbook Is a Template */
,{0x61                            ,"n/a"}
,{0x62                            ,"n/a"}
,{BIFF4_CODE_OBJPROTECT           ,"4_OBJPROTECT"}    //   0x63 /* OBJPROTECT - Objects Are Protected */
,{0x64                            ,"n/a"}
,{0x65                            ,"n/a"}
,{0x66                            ,"n/a"}
,{0x67                            ,"n/a"}
,{0x68                            ,"n/a"}
,{0x69                            ,"n/a"}
,{0x6A                            ,"n/a"}
,{0x6B                            ,"n/a"}
,{0x6C                            ,"n/a"}
,{0x6D                            ,"n/a"}
,{0x6E                            ,"n/a"}
,{0x6F                            ,"n/a"}
,{0x70                            ,"n/a"}
,{0x71                            ,"n/a"}
,{0x72                            ,"n/a"}
,{0x73                            ,"n/a"}
,{0x74                            ,"n/a"}
,{0x75                            ,"n/a"}
,{0x76                            ,"n/a"}
,{0x77                            ,"n/a"}
,{0x78                            ,"n/a"}
,{0x79                            ,"n/a"}
,{0x7A                            ,"n/a"}
,{0x7B                            ,"n/a"}
,{0x7C                            ,"n/a"}
,{BIFF4_CODE_COLINFO              ,"4_COLINFO"}    //   0x7D /* COLINFO - Column Formatting Information */
,{BIFFx_CODE_RK                   ,"x_RK"}    //   0x7E  /* RK - Cell values in RK format */
,{BIFF4_CODE_IMDATA               ,"4_IMDATA"}    //   0x7F /* IMDATA - Image Data */
,{BIFF4_CODE_GUTS                 ,"4_GUTS"}    //   0x80    /* GUTS - Size of Row and Column Gutters */
,{BIFF4_CODE_WSBOOL               ,"4_WSBOOL"}    //   0x81 /* WSBOOL - Additional Workspace Information */
,{BIFF4_CODE_GRIDSET              ,"4_GRIDSET"}    //   0x82 /* GRIDSET - State Change of Gridlines Option */
,{BIFF4_CODE_HCENTER              ,"4_HCENTER"}    //   0x83 /* HCENTER - Center Between Horizontal Margins */
,{BIFF4_CODE_VCENTER              ,"4_VCENTER"}    //   0x84 /* VCENTER - Center Between Vertical Margins */
,{BIFF5_CODE_BOUNDSHEET           ,"5_BOUNDSHEET"}    //   0x85   /* @ BOUNDSHEET - Sheet Information */
,{BIFF4_CODE_WRITEPROT            ,"4_WRITEPROT"}    //   0x86 /* WRITEPROT - Workbook Is Write-Protected */
,{BIFF4_CODE_ADDIN                ,"4_ADDIN"}    //   0x87  /* ADDIN - Workbook Is an Add-in Macro */
,{BIFF4_CODE_EDG                  ,"4_EDG"}    //   0x88 /* EDG - Edition Globals */
,{BIFF4_CODE_PUB                  ,"4_PUB"}    //   0x89  /* PUB - Publisher */
,{0x8A                            ,"n/a"}
,{0x8B                            ,"n/a"}
,{BIFF4_CODE_COUNTRY              ,"4_COUNTRY"}    //   0x8C /* COUNTRY - Default Country and WIN.INI Country */
,{BIFF4_CODE_HIDEOBJ              ,"4_HIDEOBJ"}    //   0x8D /* @ HIDEOBJ - Object Display Options */
,{0x8E                            ,"n/a"}
,{0x8F                            ,"n/a"}
,{BIFF4_CODE_SORT                 ,"4_SORT"}    //   0x90  /* SORT - Sorting Options */
,{BIFF4_CODE_SUB                  ,"4_SUB"}    //   0x91  /* SUB - Subscriber */
,{BIFF4_CODE_PALETTE              ,"4_PALETTE"}    //   0x92  /* PALETTE - Color Palette Definition */
,{0x93                            ,"n/a"}
,{BIFF4_CODE_LHRECORD             ,"4_LHRECORD"}    //   0x94    /* LHRECORD - .WK? File Conversion Information */
,{BIFF4_CODE_LHNGRAPH             ,"4_LHNGRAPH"}    //   0x95 /* LHNGRAPH - Named Graph Information */
,{BIFF4_CODE_SOUND                ,"4_SOUND"}    //   0x96    /* SOUND - Sound Note */
,{0x97                            ,"n/a"}
,{BIFF4_CODE_LPR                  ,"4_LPR"}    //   0x98   /* LPR - Sheet Was Printed Using LINE.PRINT */
,{BIFF4_CODE_STANDARDWIDTH        ,"4_STANDARDWIDTH"}    //   0x99  /* STANDARDWIDTH - Standard Column Width */
,{BIFF4_CODE_FNGROUPNAME          ,"4_FNGROUPNAME"}    //   0x9A  /* FNGROUPNAME - Function Group Name */
,{BIFF4_CODE_FILTERMODE           ,"4_FILTERMODE"}    //   0x9B   /* FILTERMODE - Sheet Contains Filtered List */
,{BIFF4_CODE_FNGROUPCOUNT         ,"4_FNGROUPCOUNT"}    //   0x9C /* FNGROUPCOUNT - Built-in Function Group Count */
,{BIFF4_CODE_AUTOFILTERINFO       ,"4_AUTOFILTERINFO"}    //   0x9D  /* AUTOFILTERINFO - Drop-Down Arrow Count */
,{BIFF4_CODE_AUTOFILTER           ,"4_AUTOFILTER"}    //   0x9E /* AUTOFILTER - AutoFilter Data */
,{0x9F                            ,"n/a"}
};

Biff_code_labels biff_code_labels_A0_FF[] =
{
 {BIFF4_CODE_SCL                  ,"4_SCL"}    //   0xA0 /* SCL - Window Zoom Magnification */
,{BIFF4_CODE_SETUP                ,"4_SETUP"}    //   0xA1  /* SETUP - Page Setup */
,{0xA2                            ,"n/a"}
,{0xA3                            ,"n/a"}
,{0xA4                            ,"n/a"}
,{0xA5                            ,"n/a"}
,{0xA6                            ,"n/a"}
,{0xA7                            ,"n/a"}
,{0xA8                            ,"n/a"}
,{BIFF4_CODE_COORDLIST            ,"4_COORDLIST"}    //   0xA9  /* COORDLIST - Polygon Object Vertex Coordinates */
,{0xAA                            ,"n/a"}
,{BIFF4_CODE_GCW                  ,"4_GCW"}    //   0xAB  /* GCW - Global Column-Width Flags */
,{0xAC                            ,"n/a"}
,{0xAD                            ,"n/a"}
,{BIFF4_CODE_SCENMAN              ,"4_SCENMAN"}    //   0xAE  /* SCENMAN - Scenario Output Data */
,{BIFF4_CODE_SCENARIO             ,"4_SCENARIO"}    //   0xAF  /* SCENARIO - Scenario Dataç */
,{BIFF4_CODE_SXVIEW               ,"4_SXVIEW"}    //   0xB0  /* SXVIEW - View Definition */
,{BIFF4_CODE_SXVD                 ,"4_SXVD"}    //   0xB1  /* SXVD - View Fields */
,{BIFF4_CODE_SXVI                 ,"4_SXVI"}    //   0xB2   /* SXVI - View Item */
,{0XB3                            ,"n/a"}
,{BIFF4_CODE_SXIVD                ,"4_SXIVD"}    //   0xB4  /* SXIVD - Row/Column Field IDs */
,{BIFF4_CODE_SXLI                 ,"4_SXLI"}    //   0xB5 /* SXLI - Line Item Array */
,{BIFF4_CODE_SXPI                 ,"4_SXPI"}    //   0xB6  /* SXPI - Page Item */
,{0xB7                            ,"n/a"}
,{BIFF4_CODE_DOCROUTE             ,"4_DOCROUTE"}    //   0xB8  /* DOCROUTE - Routing Slip Information */
,{BIFF4_CODE_RECIPNAME            ,"4_RECIPNAME"}    //   0xB9 /* RECIPNAME - Recipient Name */
,{0xBA                            ,"n/a"}
,{0xBB                            ,"n/a"}
,{BIFF4_CODE_SHRFMLA              ,"4_SHRFMLA"}    //   0xBC   /* SHRFMLA - Shared Formula */
,{BIFF4_CODE_MULRK                ,"4_MULRK"}    //   0xBD    /* @ MULRK - Multiple RK Cells */
,{BIFF4_CODE_MULBLANK             ,"4_MULBLANK"}    //   0xBE    /* * MULBLANK - Multiple Blank Cells */
,{0xBF                            ,"n/a"}
,{0xC0                            ,"n/a"}
,{BIFF4_CODE_MMS                  ,"4_MMS"}    //   0xC1   /* MMS - ADDMENU/DELMENU Record Group Count */
,{BIFF4_CODE_ADDMENU              ,"4_ADDMENU"}    //   0xC2   /* ADDMENU - Menu Addition */
,{BIFF4_CODE_DELMENU              ,"4_DELMENU"}    //   0xC3  /* DELMENU - Menu Deletion */
,{0xC4                            ,"n/a"}
,{BIFF4_CODE_SXDI                 ,"4_SXDI"}    //   0xC5 /* SXDI - Data Item */
,{BIFF8_CODE_SXDB                 ,"8_SXDB"}    //   0xC6 /* SXDB - PivotTable Cache Data (May have been in BIFF4)*/
,{0xC7                            ,"n/a"}
,{0xC8                            ,"n/a"}
,{0xC9                            ,"n/a"}
,{0xCA                            ,"n/a"}
,{0xCB                            ,"n/a"}
,{0xCC                            ,"n/a"}
,{BIFF4_CODE_SXSTRING            ,"4_SXSTRING"}    //   0xCD /* SXSTRING - String */
,{0xCE                           ,"n/a"}
,{0xCF                           ,"n/a"}
,{BIFF4_CODE_SXTBL               ,"4_SXTBL"}    //   0xD0  /* SXTBL - Multiple Consolidation Source Info */
,{BIFF4_CODE_SXTBRGIITM          ,"4_SXTBRGIITM"}    //   0xD1   /* SXTBRGIITM - Page Item Name Count */
,{BIFF4_CODE_SXTBPG              ,"4_SXTBPG"}    //   0xD2    /* SXTBPG - Page Item Indexes */
,{BIFF4_CODE_OBPROJ              ,"4_OBPROJ"}    //   0xD3    /* OBPROJ - Visual Basic Project */
,{0xD4                           ,"n/a"}
,{BIFF4_CODE_SXIDSTM             ,"4_SXIDSTM"}    //   0xD5   /* SXIDSTM - Stream ID */
,{BIFF4_CODE_RSTRING             ,"4_RSTRING"}    //   0xD6   /* @ RSTRING - Cell with Character Formatting */
,{BIFF4_CODE_DBCELL              ,"4_DBCELL"}    //   0xD7  /* DBCELL - Stream Offsets */
,{0xD8                           ,"n/a"}
,{0xD9                           ,"n/a"}
,{BIFF4_CODE_BOOKBOOL            ,"4_BOOKBOOL"}    //   0xDA /* BOOKBOOL - Workbook Option Flag */
,{0xDB                           ,"n/a"}
,{BIFF8_CODE_SXEXT               ,"8_SXEXT"}    //   0xDC /* PARAMQRY-SXEXT - Query Parameters-External Source Information (May have been in BIFF4)*/
,{BIFF4_CODE_SCENPROTECT         ,"4_SCENPROTECT"}    //   0xDD  /* SCENPROTECT - Scenario Protection */
,{BIFF4_CODE_OLESIZE             ,"4_OLESIZE"}    //   0xDE  /* OLESIZE - Size of OLE Object */
,{BIFF4_CODE_UDDESC              ,"4_UDDESC"}    //   0xDF   /* UDDESC - Description String for Chart Autoformat */
,{BIFFX_CODE_XF                  ,"4_XF"}    //   0xE0  /* XF - Extended Format */
,{BIFF4_CODE_INTERFACEHDR        ,"4_INTERFACEHDR"}    //   0xE1    /* @ INTERFACEHDR - Beginning of User Interface Records */
,{BIFF4_CODE_INTERFACEEND        ,"4_INTERFACEEND"}    //   0xE2   /* INTERFACEEND - End of User Interface Records */
,{BIFF4_CODE_SXVS                ,"4_SXVS"}    //   0xE3     /* SXVS - View Source */
,{0xE4                           ,"n/a"}
,{BIFF4_CODE_UNKNOWN_E5          ,"4_UNKNOWN_E5"}    //   0xE5  /* ?UNKNOWN1 - Guessing */
,{0xE6                           ,"n/a"}
,{0xE7                           ,"n/a"}
,{0xE8                           ,"n/a"}
,{0xE9                           ,"n/a"}
,{BIFF4_CODE_TABIDCONF           ,"4_TABIDCONF"}    //   0xEA /* TABIDCONF - Sheet Tab ID of Conflict History */
,{BIFF8_CODE_MSODRAWINGGROUP     ,"8_MSODRAWINGGROUP"}    //   0xEB   /* MSODRAWINGGROUP - Microsoft Office Drawing Group (May have been in BIFF4)*/
,{BIFF8_CODE_MSODRAWING          ,"8_MSODRAWING"}    //   0xEC /* MSODRAWING - Microsoft Office Drawing (May have been in BIFF4)*/
,{BIFF8_CODE_MSODRAWINGSELECTION ,"8_MSODRAWINGSELECTION"}    //   0xED /* MSODRAWINGSELECTION - Microsoft Office Drawing Selection (May have been in BIFF4)*/
,{0xEF                           ,"n/a"}
,{BIFF8_CODE_SXRULE              ,"8_SXRULE"}    //   0xF0  /* SXRULE - PivotTable Rule Data (May have been in BIFF4)*/
,{BIFF8_CODE_SXEX                ,"8_SXEX"}    //   0xF1 /* SXEX - PivotTable View Extended Information (May have been in BIFF4)*/
,{BIFF8_CODE_SXFILT              ,"8_SXFILT"}    //   0xF2  /* SXFILT - PivotTable Rule Filter (May have been in BIFF4)*/
,{0xF3                           ,"n/a"}
,{0xF4                           ,"n/a"}
,{0xF5                           ,"n/a"}
,{BIFF8_CODE_SXNAME              ,"8_SXNAME"}    //   0xF6 /* SXNAME - PivotTable Name (May have been in BIFF4)*/
,{BIFF8_CODE_SXSELECT            ,"8_SXSELECT"}    //   0xF7 /* SXSELECT - PivotTable Selection Information (May have been in BIFF4)*/
,{BIFF8_CODE_SXPAIR              ,"8_SXPAIR"}    //   0xF8  /* SXPAIR - PivotTable Name Pair (May have been in BIFF4)*/
,{BIFF8_CODE_SXFMLA              ,"8_SXFMLA"}    //   0xF9    /* SXFMLA - PivotTable Parsed Expression (May have been in BIFF4)*/
,{0xFA                           ,"n/a"}
,{BIFF8_CODE_SXFORMAT            ,"8_SXFORMAT"}    //   0xFB    /* SXFORMAT - PivotTable Format Record (May have been in BIFF4)*/
,{BIFF8_CODE_SST                 ,"8_SST"}    //   0xFC /* @ SST - Shared String Table (May have been in BIFF4)*/
,{BIFF8_CODE_LABELSST            ,"8_LABELSST"}    //   0xFD /* @ LABELSST - Cell Value, String Constant/SST (May have been in BIFF4)*/
,{0xFE                           ,"n/a"}
,{BIFF8_CODE_EXTSST              ,"8_EXTSST"}    //   0xFF  /* EXTSST - Extended Shared String Table (May have been in BIFF4)*/
};

Biff_code_labels biff_code_labels_misc[] =
{
 {BIFF8_CODE_SXVDEX              ,"8_SXVDEX"}    //   0x100  /* SXVDEX - Extended PivotTable View Fields (May have been in BIFF4)*/

,{BIFF8_CODE_SXFORMULA           ,"8_SXFORMULA"}    //   0x103 /* SXFORMULA - PivotTable Formula Record (May have been in BIFF4)*/

,{BIFF8_CODE_SXDBEX              ,"8_SXDBEX"}    //   0x122 /* SXDBEX - PivotTable Cache Data (May have been in BIFF4)*/

,{BIFF4_CODE_TABID               ,"4_TABID"}    //   0x13D

,{BIFF8_CODE_USESELFS            ,"8_USESELFS"}    //   0x160  /* USESELFS - Natural Language Formulas Flag (May have been in BIFF4)*/
,{BIFF8_CODE_DSF                 ,"8_DSF"}    //   0x161       /* DSF - Double Stream File (May have been in BIFF4)*/
,{BIFF8_CODE_XL5MODIFY           ,"8_XL5MODIFY"}    //   0x162  /* XL5MODIFY - Flag for DSF (May have been in BIFF4)*/

,{BIFF4_CODE_FILESHARING2        ,"4_FILESHARING2"}    //   0x1A5 /* FILESHARING2 - File-Sharing Information for Shared Lists */

,{BIFF8_CODE_USERBVIEW           ,"8_USERBVIEW"}    //   0x1A9 /* USERBVIEW - Workbook Custom View Settings (May have been in BIFF4)*/
,{BIFF8_CODE_USERSVIEWBEGIN      ,"8_USERSVIEWBEGIN"}    //   0x1AA   /* USERSVIEWBEGIN - Custom View Settings (May have been in BIFF4)*/
,{BIFF8_CODE_USERSVIEWEND        ,"8_USERSVIEWEND"}    //   0x1AB     /* USERSVIEWEND - End of Custom View Records (May have been in BIFF4)*/
,{0x1AC                          ,"n/a"}    //
,{BIFF8_CODE_QSI                 ,"8_QSI"}    //   0x1AD    /* QSI - External Data Range (May have been in BIFF4)*/
,{BIFF8_CODE_SUPBOOK             ,"8_SUPBOOK"}    //   0x1AE   /* SUPBOOK - Supporting Workbook (May have been in BIFF4)*/
,{BIFF4_CODE_PROT4REV            ,"4_PROT4REV"}    //   0x1AF /* Shared Workbook Protection Flag */
,{BIFF8_CODE_CONDFMT             ,"8_CONDFMT"}    //   0x1B0 /* CONDFMT - Conditional Formatting Range Information (May have been in BIFF4)*/
,{BIFF8_CODE_CF                  ,"8_CF"}    //   0x1B1 /* CF - Conditional Formatting Conditions (May have been in BIFF4) */
,{BIFF8_CODE_DVAL                ,"8_DVAL"}    //   0x1B2 /* DVAL - Data Validation Information (May have been in BIFF4)*/

,{BIFF8_CODE_DCONBIN             ,"8_DCONBIN"}    //   0x1B5 /* DCONBIN - Data Consolidation Information (May have been in BIFF4)*/
,{BIFF8_CODE_TXO                 ,"8_TXO"}    //   0x1B6 /* TXO - Text Object (May have been in BIFF4)*/
,{BIFF8_CODE_REFRESHALL          ,"8_REFRESHALL"}    //   0x1B7   /* REFRESHALL - Refresh Flag (May have been in BIFF4)*/
,{BIFF8_CODE_HLINK               ,"8_HLINK"}    //   0x1B8 /* HLINK - Hyperlink (May have been in BIFF4)*/
,{BIFF8_CODE_CODENAME            ,"8_CODENAME"}    //   0x1BA /* CODENAME - xxx*/
,{BIFF8_CODE_SXFDBTYPE           ,"8_SXFDBTYPE"}    //   0x1BB          /* SXFDBTYPE - SQL Datatype Identifier (May have been in BIFF4)*/
,{BIFF8_CODE_PROT4REVPASS        ,"8_PROT4REVPASS"}    //   0x1BC  /* PROT4REVPASS - Shared Workbook Protection Password (May have been in BIFF4)*/
,{0x1BD                          ,"n/a"}
,{BIFF8_CODE_DV                  ,"8_DV"}    //   0x1BE /* DV - Data Validation Criteria (May have been in BIFF4)*/

//,""}    //   0x1BF - 1FF not yet defined
,{BIFF3_CODE_DIMENSIONS          ,"3_DIMENSIONS"}    //   0x0200   /* DIMENSIONS - Cell Table Size */
,{BIFF4_CODE_BLANK               ,"4_BLANK"}  //,""}    //   0x201
,{0x202                          ,"n/a"}
,{BIFF4_CODE_NUMBER              ,"4_NUMBER"}    //   0x203 /* NUMBER - Cell Value, Floating-Point Number */
,{BIFF4_CODE_LABEL               ,"4_LABEL"}    //   0x204 /* LABEL - Cell Value, String Constant */
,{BIFF4_CODE_BOOLERR             ,"4_BOOLERR"}    //   0x205 /* BOOLERR - Cell Value, Boolean or Error */
,{0x206                          ,"n/a"}
,{BIFF4_CODE_STRING              ,"4_STRING"}    //   0x207  /* STRING - String Value of a Formula */
,{BIFF4_CODE_ROW                 ,"4_ROW"}    //   0x208 /* ROW - Describes a Row */
,{BIFF3_CODE_BOF                 ,"3_BOF"}    //   0x0209
,{0x20A                          ,"n/a"}
,{BIFF4_CODE_INDEX               ,"4_INDEX"}    //   0x20B /* INDEX - Index Record */
,{BIFF4_CODE_NAME                ,"4_NAME"}    //   0x218  /* NAME - Defined Name */
,{BIFF4_CODE_ARRAY               ,"4_ARRAY"}    //   0x221  /* ARRAY - Array-Entered Formula */
,{0x222                          ,"n/a"}
,{BIFF4_CODE_EXTERNNAME          ,"4_EXTERNNAME"}    //   0x223 /* EXTERNNAME - Externally Referenced Name */

,{BIFF4_CODE_DEFAULTROWHEIGHT    ,"4_DEFAULTROWHEIGHT"}    //   0x225 /* DEFAULTROWHEIGHT - Default Row Height */

,{BIFF4_CODE_FONT                ,"4_FONT"}    //   0x231

,{BIFF4_CODE_TABLE               ,"4_TABLE"}    //   0x236 /* TABLE - Data Table (enchanced)*/

,{BIFF4_CODE_WINDOW2             ,"4_WINDOW2"}    //   0x23E /* WINDOW2 - Sheet Window Information (enhanced WINDOW2)*/

,{BIFF4_CODE_RK                  ,"4_RK"}    //   0x27E /* RK - Cell Value, RK Number */

,{BIFF4_CODE_STYLE               ,"4_STYLE"}    //   0x293     /* STYLE - Style Information */

,{BIFFx_CODE_FORMULA             ,"X_FORMULA"}    //   0x406 /* FORMULA - Cell formula */

,{BIFF4_CODE_BOF                 ,"4_BOF"}    //   0x0409

,{BIFF4_CODE_FORMAT              ,"4_FORMAT"}    //   0x41E  /* FORMAT - Number Format */

,{BIFF5_CODE_BOF                 ,"5_BOF"}    //   0x0809 /* @ 5 7 8 */
,{0,0}
};
//______________________________________________________________________________
static char n_a[] = "n/a";
char *lookup_BIFF_code_label(uint16 rec_code)
{
   char *result = n_a;

   if (rec_code <= 0x9F)
   {
      if (biff_code_labels_00_9F[rec_code].code == rec_code)
         result =  biff_code_labels_00_9F[rec_code].label;
      else
         cout << "Error BIFF codes 00-9F labels out of sequence!" << (rec_code) << endl;
   }
   else if ((rec_code >= 0xA0) &&(rec_code < 0xFF))
   {
      if (biff_code_labels_A0_FF[rec_code-0xA0].code == rec_code)
         result =  biff_code_labels_A0_FF[rec_code-0xA0].label;
      else
         cout << "Error BIFF codes A0-FF labels out of sequence! " << (rec_code-0xA0)<< endl;
   }
   else
   { //       search_misc
      for (int i = 0 ; biff_code_labels_misc[i].label; i++)
         if (biff_code_labels_misc[i].code == rec_code)
            result = biff_code_labels_misc[i].label;
   };
   return result;
};
//______________________________________________________________________________
int main(int argc, char *argv[])
{
   CORN::File_name xls_file(argv[1]);
   CORN::File_name dmp_file(xls_file,"dmp");

   Binary_fstream xls_strm(xls_file.c_str(),false);
   ofstream dmp_strm(dmp_file.c_str());
   while (!xls_strm.eof())
   {
      uint32 rec_pos = xls_strm.tell();

      char hex[10];
      CORN_uint32_to_str(rec_pos,hex,16);

      uint8 padding_len = 8-strlen(hex);
      CORN_string padding('0',padding_len);
      dmp_strm << padding << hex << ":";


      uint16 rec_head_code = xls_strm.read_uint16();
      uint16 rec_len = xls_strm.read_uint16();
      CORN_int16_to_str(rec_head_code,hex,16);


      dmp_strm << '[' << lookup_BIFF_code_label(rec_head_code) << ']'
      << " (" << hex << ") len:" << rec_len << endl;

      uint8 col = 0;
      for (uint32 i = 0; i < rec_len; i++)
      {
         if (col == 0)
         {
            CORN_uint32_to_str(i,hex,16);
            uint8 padding_len = 8-strlen(hex);
            CORN_string padding('0',padding_len);

            dmp_strm << padding<< hex << "  ";
         };
         uint8 data =  xls_strm.read_uint8();
         CORN_uint32_to_str((uint32)data,hex,16);

         uint8 padding_len = 2-strlen(hex);
         CORN_string padding('0',padding_len);

         dmp_strm << padding << hex << ' ';

         col++;
         if (col >= 16)
         {
            col = 0;
            dmp_strm << endl;
         };
      };

      if (col)
      while (col < 16)
      {
         dmp_strm << "-- ";
         col ++;
      };
      dmp_strm << endl;
   };
};
//______________________________________________________________________________
