#ifndef BIFFcodeH
#define BIFFcodeH

#define BINREC_VARIABLE_LENGTH 0XFFFFFFFF

enum BIFF_Format {BIFF0,BIFF1,BIFF2,BIFF3,BIFF4,BIFF5,BIFF6,BIFF7,BIFF8};
   //Note the BIFF_version does not correspond to the version code stored in the file.

/* Naming convetions

   Prefix
   BIFF_    indicates implemented in all known versions
   BIFF9_   indicates implemented in the specified version and successive versions
   BIFFx_   known to be implemented in a version but I don't know what it is yet.
   BIFF12345678_  known to be applicable only in the specified versions.
                  Omitted digits indicate the versions the code is not applicable.

   It looks like BIFF6 or BIFF7 were the first version with multiple worksheets

 The Microsoft Excel 2000 file format and the Excel 2002 file format
are the same as the Excel 97 file format with minor exceptions.
One of the new additions to the Excel 2000 file format
and to the Excel 2002 file format is a record that lets you detect
when a file is saved with Excel 2000 or with Excel 2002 instead of with Excel 97.
You use Microsoft Visual C++ 6.0 to detect the version of Excel that the file is saved with.

The record ID is 0x1C0. If this record is found in the Workbook stream,
then the file is written by Excel 2000 or by Excel 2002.
This is true unless the files is saved down for compatibility.
see: http://support.microsoft.com/kb/178605/


1985 BIFF1? The first version of Excel was released on Mac. Till today, this version of Excel
file format remains undocumented.
1987 BIFF2 - Excel 2.x. It uses a simple stream file to store the entire worksheet stream.
1990 BIFF3 - Excel 3.0. It introduces the concept of workspace stream and store it in a simple stream file.
1992 BIFF4 - Excel 4.0
1993 BIFF5 - Excel 5.0 and Excel 7.0 (Excel 95).
BIFF5 initiates the use of OLE2 compound document format to store the entire workbook.
Additionally, it allows the encoding of Visual Basic for Applications (VBA) in the worksheet
to automate tasks and define user functions.
BIFF6 Does not exist because of version alignment with Word, PowerPoint etc...
1995 BIFF7 - Excel 7.0 (Excel 95).
1997 BIFF8 - Excel 8.0 (Excel 97 - XL8) and Excel 9.0 (Excel2000 - XL9)
      Excel2002(XL10), Excel2003(XL11), Excel2007(XL12).
      In BIFF8, strings are stored using the UTF-16 encoding.

http://www.fcla.edu/digitalArchive/pdfs/action_plan_bgrounds/BIFF8_apb.pdf
*/

//090618 #define    BIFF_CODE_DIMENSIONS                   0x00
#define    BIFF2_CODE_DIMENSIONS                0x00
#define    BIFF34578_CODE_DIMENSIONS          0x0200  /* DIMENSIONS - Cell Table Size */
//#define  BIFF4_CODE_DIMENSIONS                   0x200

#define    BIFF2_CODE_BLANK                     0x01
#define    BIFF2_CODE_INTEGER                   0x02
#define    BIFF2_CODE_NUMBER                    0x03
#define    BIFF2_CODE_LABEL                     0x04

#define    BIFF2_CODE_BOOLERR                   0x05
#define    BIFF2578_CODE_FORMULA                 0x06
#define    BIFF2_CODE_STRING                    0x07
#define    BIFF2_CODE_ROW                       0x08
#define    BIFF2_CODE_BOF                       0x09

#define    BIFF234578_CODE_EOF                  0x0A
#define    BIFF2_CODE_INDEX                     0x0B
#define    BIFF234578_CODE_CALCCOUNT            0x0C
#define    BIFF234578_CODE_CALCMODE             0x0D
#define    BIFF234578_CODE_PRECISION            0x0E
#define    BIFF234578_CODE_REFMODE              0x0F
#define    BIFF234578_CODE_DELTA                0x10
#define    BIFF234578_CODE_ITERATION            0x11
#define    BIFF234578_CODE_PROTECT              0x12
#define    BIFF234578_CODE_PASSWORD             0x13
#define    BIFF234578_CODE_HEADER               0x14
#define    BIFF234578_CODE_FOOTER               0x15
#define    BIFF2345_CODE_EXTERNCOUNT            0x16
#define    BIFF234578_CODE_EXTERNSHEET          0x17
#define    BIFF2578_CODE_NAME                   0x18
                 // rename NAME to DEFINED_NAME
#define    BIFF234578_CODE_WINDOW_PROTECT       0x19
#define    BIFF234578_CODE_VERTICAL_PAGE_BREAKS 0x1A  /* VERTICALPAGEBREAKS - Explicit Column Page Breaks */
#define    BIFF234578_CODE_HORIZONTAL_PAGE_BREAKS     0x1B /* HORIZONTALPAGEBREAKS - Explicit Row Page Breaks */
#define    BIFF234578_CODE_NOTE                 0x1C
#define    BIFF234578_CODE_SELECTION            0x1D
#define    BIFF23_CODE_FORMAT                   0x1E
#define    BIFF2_CODE_FORMATCOUNT               0x1F
                   // BUILTINFMTCOUNT

#define    BIFF2_CODE_COLUMN_DEFAULT            0x20
#define    BIFF2_CODE_ARRAY                     0x21
#define    BIFF234578_CODE_1904                 0x22  /* 1904 - AKA DATEMODE */
#define    BIFF234578_CODE_DATEMODE             0x22  /* DATEMODE - AKA 1904 */
                   // rename DATEMODE
#define    BIFF2578_CODE_EXTERNNAME             0x23
#define    BIFF2_CODE_COLWIDTH                  0x24
#define    BIFF2_CODE_DEFAULT_ROW_HEIGHT        0x25
#define    BIFF234578_CODE_LEFT_MARGIN          0x26
#define    BIFF234578_CODE_RIGHT_MARGIN         0x27
#define    BIFF234578_CODE_TOP_MARGIN           0x28
#define    BIFF234578_CODE_BOTTOM_MARGIN        0x29
#define    BIFF234578_CODE_PRINT_ROW_HEADERS    0x2A
#define    BIFF234578_CODE_PRINT_GRIDLINES      0x2B
#define    BIFF234578_CODE_FILEPASS             0x2F
#define    BIFF2578_CODE_FONT                   0x31 /* @ FONT - Font Description */
// #define    BIFF7_CODE_FONT                   0x31 /* BIFF7 appears to use 0x31 now */

#define    BIFF2_CODE_FONT2                     0x32
#define    BIFF2_CODE_TABLE                     0x36
#define    BIFF2_CODE_TABLE2                    0x37
#define    BIFF234578_CODE_CONTINUE             0x3C /* CONTINUE - Continues Long Records */
#define    BIFF234578_CODE_WINDOW1              0x3D /* WINDOW1 - Window Information */
#define    BIFF2_CODE_WINDOW2                   0x3E
#define    BIFF234578_CODE_BACKUP               0x40 /* BACKUP - Save Backup Version of the File */
#define    BIFF234578_CODE_PANE                 0x41  /* PANE - Number of Panes and Their Position */

// The following are BIFF3 or later   @ indicates I could probably implement this record

/* The following records are required for BIFF5 files
Required Records
BOF - Set the 6 byte offset to 0x0005 (workbook globals)
Window1
FONT - At least five of these records must be included
XF - At least 15 Style XF records and 1 Cell XF record must be included
STYLE
BOUNDSHEET - Include one BOUNDSHEET record per worksheet
EOF
BOF - Set the 6 byte offset to 0x0010 (worksheet)
INDEX
DIMENSIONS
WINDOW2
EOF
*/

#define BIFF234578_CODE_CODEPAGE                0x42 /* @ CODEPAGE - Default Code Page */
#define BIFF2_CODE_XF                           0x43
#define BIFF2_CODE_IXFE                         0x44
#define BIFF2_CODE_FONTCOLOR                    0x45
// 0x46-0x4C not used
#define  BIFF234578_CODE_PLS                    0x4D /* PLS - Environment-Specific Print Record */
// 0x4E-0x4F not used
#define  BIFFX_CODE_DCON                        0x50 /* DCON - Data Consolidation Information */
#define  BIFF234578_CODE_DCONREF                0x51     /* DCONREF - Data Consolidation References */
#define  BIFF_CODE_DCONNAME                     0x52 /* DCONNAME - Data Consolidation Named References */
// 0x53-0x54 not used
#define  BIFF234578_CODE_DEFCOLWIDTH            0x55 /* DEFCOLWIDTH - Default Width for Columns */
#define  BIFF34_CODE_BUILTINFMTCOUNT            0x56
// 0x57-0x58 not used
#define  BIFF34578_CODE_XCT                     0x59 /* XCT - CRN Record Count */
#define  BIFF34578_CODE_CRN                     0x5A /* CRN - Nonresident Operands */
#define  BIFF34578_CODE_FILESHARING             0x5B  /* FILESHARING - File-Sharing Information */
#define  BIFF34578_CODE_WRITEACCESS             0x5C  /* @ WRITEACCESS - Write Access User Name */
#define  BIFFX_CODE_OBJ                         0x5D  /* OBJ - Describes a Graphic Object */
#define  BIFF34578_CODE_UNCALCED                0x5E /* UNCALCED - Recalculation Status */
#define  BIFF34578_CODE_SAVERECALC              0x5F /* SAVERECALC - Recalculate Before Save */
#define  BIFFX_CODE_TEMPLATE                    0x60 /* TEMPLATE - Workbook Is a Template */
// 0x61-0x62 not used
#define  BIFF34578_CODE_OBJPROTECT              0x63 /* OBJPROTECT - Objects Are Protected */
// 0x64-0x7C not used
#define  BIFF34578_CODE_COLINFO                 0x7D /* COLINFO - Column Formatting Information */
#define  BIFF2_CODE_RK                          0x7E  /* RK - Cell values in RK format */
#define  BIFFx_CODE_IMDATA                      0x7F /* IMDATA - Image Data */
#define  BIFF34578_CODE_GUTS                    0x80    /* GUTS - Size of Row and Column Gutters */
#define  BIFF34578_CODE_SHEETPR                 0x81 /* WSBOOL - Additional Workspace Information */
           // WSBOOL
#define  BIFF34578_CODE_GRIDSET                 0x82 /* GRIDSET - State Change of Gridlines Option */
#define  BIFF34578_CODE_HCENTER                 0x83 /* HCENTER - Center Between Horizontal Margins */
#define  BIFF34578_CODE_VCENTER                 0x84 /* VCENTER - Center Between Vertical Margins */
#define  BIFF578_CODE_BOUNDSHEET                0x85   /* @ BOUNDSHEET - Sheet Information   5,7  changed in 8  */
               // also know as SHEET

#define  BIFF34578_CODE_WRITEPROT               0x86 /* WRITEPROT - Workbook Is Write-Protected */
#define  BIFFx_CODE_ADDIN                       0x87  /* ADDIN - Workbook Is an Add-in Macro */
#define  BIFFx_CODE_EDG                         0x88 /* EDG - Edition Globals */
#define  BIFFx_CODE_PUB                         0x89  /* PUB - Publisher */
// 0x8A-0x8B not used
#define  BIFF34578_CODE_COUNTRY                 0x8C /* COUNTRY - Default Country and WIN.INI Country */
#define  BIFF34578_CODE_HIDEOBJ                 0x8D /* @ HIDEOBJ - Object Display Options */
// 0x8E-0x8F not used
#define  BIFF578_CODE_SORT                      0x90  /* SORT - Sorting Options */
#define  BIFFx_CODE_SUB                         0x91  /* SUB - Subscriber */
#define  BIFF34578_CODE_PALETTE                 0x92  /* PALETTE - Color Palette Definition */


#define  BIFFx_CODE_LHRECORD                    0x94    /* LHRECORD - .WK? File Conversion Information */
#define  BIFFx_CODE_LHNGRAPH                    0x95 /* LHNGRAPH - Named Graph Information */
#define  BIFFx_CODE_SOUND                       0x96    /* SOUND - Sound Note */
#define  BIFFx_CODE_LPR                         0x98   /* LPR - Sheet Was Printed Using LINE.PRINT */
#define  BIFF4578_CODE_STANDARDWIDTH            0x99  /* STANDARDWIDTH - Standard Column Width */
#define  BIFFx_CODE_FNGROUPNAME                 0x9A  /* FNGROUPNAME - Function Group Name */
#define  BIFFx_CODE_FILTERMODE                  0x9B   /* FILTERMODE - Sheet Contains Filtered List */
#define  BIFFx_CODE_FNGROUPCOUNT                0x9C /* FNGROUPCOUNT - Built-in Function Group Count */
#define  BIFFx_CODE_AUTOFILTERINFO              0x9D  /* AUTOFILTERINFO - Drop-Down Arrow Count */
#define  BIFFx_CODE_AUTOFILTER                  0x9E /* AUTOFILTER - AutoFilter Data */

// 0x9F - 0xFE

#define  BIFF4578_CODE_SCL                      0xA0 /* SCL - Window Zoom Magnification */
#define  BIFF4578_CODE_SETUP                    0xA1  /* SETUP - Page Setup */
               // AKA PAGESETUP
#define  BIFFx_CODE_COORDLIST                   0xA9  /* COORDLIST - Polygon Object Vertex Coordinates */

#define  BIFF45x_CODE_GCW                        0xAB  /* GCW - Global Column-Width Flags */
            // in BIFF7?

#define  BIFFx_CODE_SCENMAN                     0xAE  /* SCENMAN - Scenario Output Data */
#define  BIFFx_CODE_SCENARIO                    0xAF  /* SCENARIO - Scenario Dataç */
#define  BIFFx_CODE_SXVIEW                      0xB0  /* SXVIEW - View Definition */
#define  BIFFx_CODE_SXVD                        0xB1  /* SXVD - View Fields */
#define  BIFFx_CODE_SXVI                        0xB2   /* SXVI - View Item */

#define  BIFFx_CODE_SXIVD                       0xB4  /* SXIVD - Row/Column Field IDs */
#define  BIFFx_CODE_SXLI                        0xB5 /* SXLI - Line Item Array */
#define  BIFFx_CODE_SXPI                        0xB6  /* SXPI - Page Item */

#define  BIFFx_CODE_DOCROUTE                    0xB8  /* DOCROUTE - Routing Slip Information */
#define  BIFFx_CODE_RECIPNAME                   0xB9 /* RECIPNAME - Recipient Name */

#define  BIFF578_CODE_SHRFMLA                   0xBC   /* SHRFMLA - AKA SHAREDFMLA Shared Formula */
#define  BIFF578_CODE_SHAREDFMLA                0xBC  /* SHAREDFMLA - AKA SHRFMLA  - Shared Formula */
#define  BIFF578_CODE_MULRK                     0xBD    /* @ MULRK - Multiple RK Cells */
#define  BIFF578_CODE_MULBLANK                  0xBE    /* * MULBLANK - Multiple Blank Cells */


#define  BIFFx_CODE_MMS                         0xC1   /* MMS - ADDMENU/DELMENU Record Group Count */
#define  BIFFx_CODE_ADDMENU                     0xC2   /* ADDMENU - Menu Addition */
#define  BIFFx_CODE_DELMENU                     0xC3  /* DELMENU - Menu Deletion */
//#define  BIFFx_CODE_                          0xC4
#define  BIFFx_CODE_SXDI                        0xC5 /* SXDI - Data Item */
#define  BIFF8_CODE_SXDB                        0xC6 /* SXDB - PivotTable Cache Data (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0xC7
//#define  BIFFx_CODE_                   0xC8
//#define  BIFFx_CODE_                   0xC9
//#define  BIFFx_CODE_                   0xCA
//#define  BIFFx_CODE_                   0xCB
//#define  BIFFx_CODE_                   0xCC
#define  BIFF4_CODE_SXSTRING                    0xCD /* SXSTRING - String */
//#define  BIFFx_CODE_                   0xCE
//#define  BIFFx_CODE_                   0xCF
#define  BIFFx_CODE_SXTBL                       0xD0  /* SXTBL - Multiple Consolidation Source Info */
#define  BIFFx_CODE_SXTBRGIITM                  0xD1   /* SXTBRGIITM - Page Item Name Count */
#define  BIFFx_CODE_SXTBPG                      0xD2    /* SXTBPG - Page Item Indexes */
#define  BIFFx_CODE_OBPROJ                      0xD3    /* OBPROJ - Visual Basic Project */
//#define  BIFFx_CODE_                   0xD4
#define  BIFFx_CODE_SXIDSTM                     0xD5   /* SXIDSTM - Stream ID */
#define  BIFF578_CODE_RSTRING                   0xD6   /* @ RSTRING - Cell with Character Formatting */
#define  BIFF578_CODE_DBCELL                    0xD7  /* DBCELL - Stream Offsets */
//#define  BIFFx_CODE_                   0xD8
//#define  BIFFx_CODE_                   0xD9
#define  BIFF578_CODE_BOOKBOOL                  0xDA /* BOOKBOOL - Workbook Option Flag */
//#define  BIFFx_CODE_                   0xDB
#define  BIFFx_CODE_SXEXT                       0xDC /* PARAMQRY-SXEXT - Query Parameters-External Source Information (May have been in BIFF4)*/
#define  BIFF578_CODE_SCENPROTECT               0xDD  /* SCENPROTECT - Scenario Protection */
#define  BIFFx_CODE_OLESIZE                     0xDE  /* OLESIZE - Size of OLE Object */
#define  BIFFx_CODE_UDDESC                      0xDF   /* UDDESC - Description String for Chart Autoformat */
//#define  BIFFx_CODE_                   0x
//#define  BIFFx_CODE_                   0x
#define  BIFF578_CODE_XF                        0xE0  /* XF - Extended Format */
#define  BIFFx_CODE_INTERFACEHDR                0xE1    /* @ INTERFACEHDR - Beginning of User Interface Records */
#define  BIFFx_CODE_INTERFACEEND                0xE2   /* INTERFACEEND - End of User Interface Records */
#define  BIFFx_CODE_SXVS                        0xE3     /* SXVS - View Source */
//#define  BIFFx_CODE_                   0xE4
#define  BIFF8_CODE_MERGEDCELLS                 0xE5  /* ?UNKNOWN1 - Guessing */
//#define  BIFFx_CODE_                   0xE6
//#define  BIFFx_CODE_                   0xE7
//#define  BIFFx_CODE_                   0xE8
#define  BIFF8_CODE_BITMAP                      0xE9
#define  BIFFx_CODE_TABIDCONF                   0xEA  /* TABIDCONF - Sheet Tab ID of Conflict History */
#define  BIFFx_CODE_MSODRAWINGGROUP             0xEB  /* MSODRAWINGGROUP - Microsoft Office Drawing Group (May have been in BIFF4)*/
#define  BIFFx_CODE_MSODRAWING                  0xEC  /* MSODRAWING - Microsoft Office Drawing (May have been in BIFF4)*/
#define  BIFFx_CODE_MSODRAWINGSELECTION         0xED  /* MSODRAWINGSELECTION - Microsoft Office Drawing Selection (May have been in BIFF4)*/
#define  BIFF8_CODE_PHONETICPR                  0xEF
#define  BIFF8_CODE_SXRULE                      0xF0  /* SXRULE - PivotTable Rule Data (May have been in BIFF4)*/
#define  BIFF8_CODE_SXEX                        0xF1  /* SXEX - PivotTable View Extended Information (May have been in BIFF4)*/
#define  BIFF8_CODE_SXFILT                      0xF2  /* SXFILT - PivotTable Rule Filter (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0xF3
//#define  BIFFx_CODE_                   0xF4
//#define  BIFFx_CODE_                   0xF5
#define  BIFF8_CODE_SXNAME                      0xF6 /* SXNAME - PivotTable Name (May have been in BIFF4)*/
#define  BIFF8_CODE_SXSELECT                    0xF7 /* SXSELECT - PivotTable Selection Information (May have been in BIFF4)*/
#define  BIFF8_CODE_SXPAIR                      0xF8  /* SXPAIR - PivotTable Name Pair (May have been in BIFF4)*/
#define  BIFF8_CODE_SXFMLA                      0xF9    /* SXFMLA - PivotTable Parsed Expression (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0xFA
#define  BIFF8_CODE_SXFORMAT                    0xFB    /* SXFORMAT - PivotTable Format Record (May have been in BIFF4)*/
#define  BIFF8_CODE_SST                         0xFC /* @ SST - Shared String Table */
#define  BIFF8_CODE_LABELSST                    0xFD /* @ LABELSST - Cell Value, String Constant/SST */
//#define  BIFFx_CODE_                   0xFE
#define  BIFF8_CODE_EXTSST                      0xFF  /* EXTSST - Extended Shared String Table */

#define  BIFF8_CODE_SXVDEX                     0x100  /* SXVDEX - Extended PivotTable View Fields (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0x101
//#define  BIFFx_CODE_                   0x102
#define  BIFF8_CODE_SXFORMULA                  0x103 /* SXFORMULA - PivotTable Formula Record (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0x
#define  BIFF8_CODE_SXDBEX                     0x122 /* SXDBEX - PivotTable Cache Data (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0x
#define  BIFF4_CODE_TABID                      0x13D
//#define  BIFFx_CODE_                   0x
#define  BIFF8_CODE_LABELRAGNES                0x15F
#define  BIFF8_CODE_USESELFS                   0x160  /* USESELFS - Natural Language Formulas Flag (May have been in BIFF4)*/
#define  BIFF8_CODE_DSF                        0x161       /* DSF - Double Stream File (May have been in BIFF4)*/
#define  BIFF8_CODE_XL5MODIFY                  0x162  /* XL5MODIFY - Flag for DSF (May have been in BIFF4)*/
//#define  BIFFx_CODE_                   0x
#define  BIFF4_CODE_FILESHARING2               0x1A5 /* FILESHARING2 - File-Sharing Information for Shared Lists */
//#define  BIFFx_CODE_                   0x1A6
//#define  BIFFx_CODE_                   0x1A7
//#define  BIFFx_CODE_                   0x1A8
#define  BIFF8_CODE_USERBVIEW                  0x1A9 /* USERBVIEW - Workbook Custom View Settings (May have been in BIFF4)*/
#define  BIFF8_CODE_USERSVIEWBEGIN             0x1AA /* USERSVIEWBEGIN - Custom View Settings (May have been in BIFF4)*/
#define  BIFF8_CODE_USERSVIEWEND               0x1AB /* USERSVIEWEND - End of Custom View Records (May have been in BIFF4)*/
//#define  BIFF_CODE_                    0x1AC
#define  BIFF8_CODE_QSI                        0x1AD /* QSI - External Data Range */
#define  BIFF8_CODE_SUPBOOK                    0x1AE /* SUPBOOK - AKA EXTERNALBOOK - Supporting Workbook */
#define  BIFF8_CODE_EXTERNALBOOK               0x1AE /* EXTERNALBOOK - AKA SUPBOOK - Supporting Workbook */
#define  BIFFx_CODE_PROT4REV                   0x1AF /* Shared Workbook Protection Flag */
#define  BIFF8_CODE_CONDFMT                    0x1B0 /* CONDFMT - AKA CFHEADER - Conditional Formatting Range Information */
#define  BIFF8_CODE_CFHEADER                   0x1B0 /* CFHEADER - AKA CONDFMT - Conditional Formatting Range Information */*/
#define  BIFF8_CODE_CF                         0x1B1 /* CF - Conditional Formatting Conditions (May have been in BIFF4) */
#define  BIFF8_CODE_DVAL                       0x1B2 /* DVAL - AKA DATAVALIDATIONS - Data Validation Information (May have been in BIFF4)*/
#define  BIFF8_CODE_DATAVALIDATIONS            0x1B2 /* DATAVALIDATIONS - AKA DVAL - Data Validation Information (May have been in BIFF4)*/

#define  BIFF8_CODE_DCONBIN                    0x1B5 /* DCONBIN - Data Consolidation Information (May have been in BIFF4)*/
#define  BIFF8_CODE_TXO                        0x1B6 /* TXO - Text Object (May have been in BIFF4)*/
#define  BIFF8_CODE_REFRESHALL                 0x1B7 /* REFRESHALL - Refresh Flag (May have been in BIFF4)*/
#define  BIFF8_CODE_HYPERLINK                  0x1B8 /* HLINK - Hyperlink (May have been in BIFF4)*/
#define  BIFF8_CODE_CODENAME                   0x1BA /* CODENAME - xxx*/
#define  BIFF8_CODE_SXFDBTYPE                  0x1BB /* SXFDBTYPE - SQL Datatype Identifier (May have been in BIFF4)*/
#define  BIFF8_CODE_PROT4REVPASS               0x1BC /* PROT4REVPASS - Shared Workbook Protection Password (May have been in BIFF4)*/
////#define  BIFFx_CODE_                   0x1BD
#define  BIFF8_CODE_DATAVALIDATION             0x1BE /* DATAVALIDATION - AKA DV - Data Validation Criteria (May have been in BIFF4)*/

// 0x1BF - 1FF not yet defined

#define  BIFF34578_CODE_BLANK                  0x201 /* BLANK - Cell Value, Blank Cell */
//#define  BIFFx_CODE_                   0x202
#define  BIFF34578_CODE_NUMBER                 0x203 /* NUMBER - Cell Value, Floating-Point Number */
#define  BIFF34578_CODE_LABEL                  0x204 /* LABEL - Cell Value, String Constant */
#define  BIFF34578_CODE_BOOLERR                0x205 /* BOOLERR - Cell Value, Boolean or Error */
#define  BIFF34_CODE_FORMULA                   0x206
#define  BIFF34578_CODE_STRING                 0x207  /* STRING - String Value of a Formula */
#define  BIFF34578_CODE_ROW                    0x208 /* ROW - Describes a Row */
#define  BIFF3_CODE_BOF                       0x0209

//#define  BIFFx_CODE_                   0x20A
#define  BIFF34578_CODE_INDEX                  0x20B /* INDEX - Index Record */
#define  BIFF34_CODE_DEFINEDNAME               0x218  /* DEFINEDNAME - AKA NAME - Defined Name */
////#define  BIFFx_CODE_                   0x
////#define  BIFFx_CODE_                   0x
////#define  BIFFx_CODE_                   0x
////#define  BIFFx_CODE_                   0x
#define  BIFF34578_CODE_ARRAY                  0x221  /* ARRAY - Array-Entered Formula */
////#define  BIFFx_CODE_                   0x222
#define  BIFF34_CODE_EXTERNNAME                0x223 /* EXTERNNAME - Externally Referenced Name */
////#define  BIFFx_CODE_                   0x224
#define  BIFF34578_CODE_DEFAULTROWHEIGHT       0x225 /* DEFAULTROWHEIGHT - Default Row Height */
#define  BIFF34_CODE_FONT                      0x231
#define  BIFF34578_CODE_TABLE                  0x236 /* TABLE - Data Table (enchanced)*/

#define  BIFF34578_CODE_WINDOW2                0x23E /* WINDOW2 - Sheet Window Information (enhanced WINDOW2)*/

#define  BIFF3_CODE_XF                         0x243
#define  BIFF34578_CODE_RK                     0x27E /* RK - Cell Value, RK Number */

#define  BIFF34578_CODE_STYLE                  0x293 /* STYLE - Style Information */

#define  BIFF4_CODE_FORMULA                    0x406 /* FORMULA - Cell formula */

#define  BIFF4_CODE_BOF                       0x0409

#define  BIFF4578_CODE_FORMAT                  0x41E  /* FORMAT - Number Format */

#define  BIFF4_CODE_XF                         0x443
#define  BIFF578_CODE_SHARED_FORMULA           0x4BC /* Formula related, always before there are 0x06 (FORMULA) */

#define  BIFF8_CODE_QUICKTIP                  0x0800
#define  BIFF578_CODE_BOF                     0x0809 /* @ 5 7 8 */
#define  BIFF8_SHEETLAYOUT                    0x0862
#define  BIFF8_SHEEPROTECTION                 0x0867
#define  BIFF8_RANGEROTECTION                 0x0868

/*
Byte Offset     Bit   Description                     Contents
     0          7     Cell is not hidden              0b
                      Cell is hidden                  1b
                6     Cell is not locked              0b
                      Cell is locked                  1b
                5-0   Reserved, must be 0             000000b
*/
#define    BIFF_ATTR0_DEFAULT          0x00
#define    BIFF_ATTR0_HIDDEN           0x80
#define    BIFF_ATTR0_LOCKED           0x40
/*
                7-6   Font number (4 possible)
                5-0   Cell format code
*/
#define    BIFF_ATTR1_DEFAULT          0x00
/*
     2          7     Cell is not shaded              0b
                      Cell is shaded                  1b
                6     Cell has no bottom border       0b
                      Cell has a bottom border        1b
                5     Cell has no top border          0b
                      Cell has a top border           1b
                4     Cell has no right border        0b
                      Cell has a right border         1b
                3     Cell has no left border         0b
                      Cell has a left border          1b
                2-0   Cell alignment code
                           general                    000b
                           left                       001b
                           center                     010b
                           right                      011b
                           fill                       100b
                           Multiplan default align.   111b
*/
#define    BIFF_ATTR2_DEFAULT          0x00
#define    BIFF_ATTR2_SHADED           0x80
#define    BIFF_ATTR2_BOTTOM_BORDER    0x40
#define    BIFF_ATTR2_TOP_BORDER       0x20
#define    BIFF_ATTR2_RIGHT_BORDER     0x10
#define    BIFF_ATTR2_LEFT_BORDER      0x08
#define    BIFF_ATTR2_ALIGN_LEFT       0x01
#define    BIFF_ATTR2_ALIGN_CENTER     0x02
#define    BIFF_ATTR2_ALIGN_RIGHT      0x03
#define    BIFF_ATTR2_ALIGN_FILL       0x04
#define    BIFF_ATTR2_ALIGN_MULTIPLAN  0x07

// The following are fixed lengths of record

// _LEN_ indicates a fixed length
// _VLEN_ indicates a variable length


//090618 #define  BIFF_LEN_DIMENSIONS     8 /*obsolete*/
#define  BIFF2_LEN_DIMENSIONS    8
#define  BIFF345_LEN_DIMENSIONS 10
#define  BIFF8_LEN_DIMENSIONS   14
#define  BIFF_LEN_BLANK          ?
#define  BIFF_LEN_INTEGER        9
#define  BIFF2_LEN_NUMBER        15
#define  BIFF34578_LEN_NUMBER    14
//#define  BIFF2_LEN_LABEL         BINREC_VARIABLE_LENGTH
//#define  BIFF34578_LEN_LABEL     BINREC_VARIABLE_LENGTH
#define  BIFF_LEN_BOOLERR        ?
#define  BIFF_LEN_FORMULA        BINREC_VARIABLE_LENGTH
#define  BIFF8_LEN_LABELSST      10
#define  BIFF_VLEN_STRING        BINREC_VARIABLE_LENGTH
#define  BIFF2_LEN_BOF           4
#define  BIFF34_LEN_BOF           6
//#define  BIFF4_LEN_BOF           6
#define  BIFF57_LEN_BOF           8
//#define  BIFF7_LEN_BOF           8
#define  BIFF8_LEN_BOF          16

#define  BIFF_LEN_ROW           16

#define  BIFF_LEN_EOF            0

#define  BIFF_LEN_COLWIDTH 0

#define  BIFF_LEN_WINDOW1  9
#define  BIFF2_LEN_WINDOW2   14
#define  BIFF345_LEN_WINDOW2   10
#define  BIFF8_LEN_WINDOW2   18

#define  BIFF_LEN_PANE   10


#define  BIFF5_VLEN_BOUNDSHEET BINREC_VARIABLE_LENGTH
#define  BIFF8_VLEN_BOUNDSHEET BINREC_VARIABLE_LENGTH

#define  BIFFx_LEN_RK         10
#define BIFF_VLEN_SELECTION      BINREC_VARIABLE_LENGTH

#endif

