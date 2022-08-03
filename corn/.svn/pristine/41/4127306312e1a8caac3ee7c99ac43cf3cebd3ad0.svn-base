#ifndef CORN_ESCSEQ_H
#define CORN_ESCSEQ_H
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

#define ANSI_ES         0
#define HPLASERJET_ES   1
#define HPDESKJET_ES    2
#define HPTHINKJET_ES   3
#define GEMINI_ES       4
#define EPSON9_ES       5
#define EPSON24_ES      6
#define TRIBUTE_ES      7
#define DIABLO_ES       8

#define UNKNOWN  ""
#define NA       0


#define  ES_17CPION       0
#define  ES_17CPIOFF      1
#define  ES_12CPION       2
#define  ES_12CPIOFF      3
#define  ES_10CPION       4
#define  ES_10CPIOFF      5
#define  ES_8CPION        6
#define  ES_8CPIOFF       7
#define  ES_6CPION        8
#define  ES_6CPIOFF       9
#define  ES_5CPION       10
#define  ES_5CPIOFF      11
#define  ES_PropSpaceON  12
#define  ES_PropSpaceOFF 13
#define  ES_Portrait     14
#define  ES_Landscape    15
#define  ES_SubSON       16
#define  ES_SubSOFF      17
#define  ES_SupSON       18
#define  ES_SupSOFF      19
#define  ES_boldON       20
#define  ES_boldOFF      21
#define  ES_italicsON    22
#define  ES_italicsOFF   23
#define  ES_underON      24
#define  ES_underOFF     25


/*
  17 CPI = compressed
  12 CPI = Elite
  10 CPI = Pica
  8.5CPI = DW Compressed
  6  CPI = DW Elite
  5  CPI = DW Pica
*/

  char  *ES_attributes[][9] =
  {               /*   ANSI   HPLASERJET     HPDESKJET      HPTHINKJET  GEMINI        EPSON9           EPSON24     TRIBUTE        DIABLO
/* ES_17CPION     */{UNKNOWN ,"\033(s16.66H","\033(s16.66H","\033&k2S" ,"\017"       ,"\017"          ,""         ,"\033\133"    ,""            },
/* ES_17CPIOFF    */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,"\022"       ,"\022"          ,""         ,"\033\135"    ,""            },

/* ES_12CPION     */{UNKNOWN ,"\033(s12H"   ,"\033(s12H"   ,"\033&k0S" ,"\033M"      ,"\033M"         ,""         ,""            ,""            },
/* ES_12CPIOFF    */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,"\033P"      ,"\033P"         ,""         ,""            ,""            },

/* ES_10CPION     */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,"\033P"      ,"\033P"         ,""         ,""            ,""            },
/* ES_10CPIOFF    */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,"\033P"      ,"\033P"         ,""         ,""            ,""            },

/* ES_8CPION      */{UNKNOWN ,"\033(s8H"    ,"\033(s8H"    ,NA         ,"\017\033W1" ,"\017\033W1"    ,""         ,"\033!\033\133"   ,""        },
/* ES_8CPIOFF     */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,NA         ,"\022\033W0" ,"\022\033W0"    ,""         ,"\033\042\033\135",""        },

/* ES_6CPION      */{UNKNOWN ,"\033(s6H"    ,"\033(s6H"    ,"\033&k1S" ,"\033M\033W1","\033M\033W1"   ,""         ,""            ,""            },
/* ES_6CPIOFF     */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,"\033&k3S" ,"\033P\033W0","\033P\033W0"   ,""         ,""            ,""            },

/* ES_5CPION      */{UNKNOWN ,"\033(s5H"    ,"\033(s5H"    ,NA         ,"\033P\033W1","\033P\033W1"   ,""         ,""            ,""            },
/* ES_5CPIOFF     */{UNKNOWN ,"\033(s10H"   ,"\033(s10H"   ,NA         ,"\033P\033W0","\033P\033W0"   ,""         ,""            ,""            },

/* ES_PropSpaceON */{UNKNOWN ,"\033(s1P"    ,"\033(s1P"    ,NA         ,"\033p1"     ,"\033p1"        ,""         ,"\033\044"    ,"\033P"       },
/* ES_PropSpaceOFF*/{UNKNOWN ,"\033(s0P"    ,"\033(s0P}"   ,NA         ,"\033p0"     ,"\033p0"        ,""         ,"\033\045"    ,"\033Q"       },

/* ES_Portrait    */{UNKNOWN ,"\033&l0O"    ,"\033&l0O"    ,NA         ,NA           ,NA              ,NA         ,NA            ,NA            },
/* ES_Landscape   */{UNKNOWN ,"\033&l1O"    ,"\033&l1O"    ,NA         ,NA           ,NA              ,NA         ,NA            ,NA            },

/* ES_SubSON      */{UNKNOWN ,NA            ,NA            ,NA         ,"\033S1"     ,"\033S1"        ,""         ,"\033D"       ,"\033D"       },
/* ES_SubSOFF     */{UNKNOWN ,NA            ,NA            ,NA         ,"\033T"      ,"\033T"         ,""         ,"\033U"       ,"\033U"       },

/* ES_SupSON      */{UNKNOWN ,NA            ,NA            ,NA         ,"\033S0"     ,"\033S0"        ,""         ,"\033U"       ,"\033U"       },
/* ES_SupSOFF     */{UNKNOWN ,NA            ,NA            ,NA         ,"\033T"      ,"\033T"         ,""         ,"\033D"       ,"\033D"       },

/* ES_boldON      */{UNKNOWN ,"\033(s3B"    ,"\033(s3B"    ,"\016"     ,"\033G"      ,"\033G"         ,""         ,"\033K2"      ,"\033O"       },
/* ES_boldOFF     */{UNKNOWN ,"\033(s-3B"   ,"\033(s0B"    ,"\017"     ,"\033H"      ,"\033H"         ,""         ,"\033K1"      ,"\033\046"    },

/* ES_italicsON   */{UNKNOWN ,"\033(s1S"    ,"\033(s1S"    ,NA         ,"\0334"      ,"\0334"         ,""         ,"\033\022"    ,NA            },
/* ES_italicsOFF  */{UNKNOWN ,"\033(s0S"    ,"\033(s0S"    ,NA         ,"\0335"      ,"\0335"         ,""         ,"\033\024"    ,NA            },

/* ES_underON     */{UNKNOWN ,"\033&d0D"    ,"\033&d0D"    ,"\033&dD"  ,"\0330"      ,"\0331"         ,""         ,"\033I"       ,"\033E"       },
/* ES_underOFF    */{UNKNOWN ,"\033&d@"     ,"\033&d@"     ,"\033&d@"  ,"\0331"      ,"\0330"         ,""         ,"\033J"       ,"\o33R"       }
  };

#define ES_print_attribute(file,attr,dev) fprintf(file,"%s",ES_attributes[attr][dev])
#define ES_attribute(attr,dev) ES_attributes[attr][dev]

/* ES_PageLen_Ms  /{""      ,"\033&l%dP"   ,"\033&l%dP"  ,""         ,""

* ES_CS_PC8     /{""      ,"\033(10U"    ,""           ,""         ,""
* ES_CS_Roman8  /{""      ,"\033(8U"     ,""           ,""         ,""
* ES_CS_ECMA94  /{""      ,"\033(0N"     ,""           ,""         ,""
*/


/* Proportional spacing chart
/*                             HP HP HP SM EP EP CT     */
/* Symbol                 ANSI LJ DJ TJ GM 9  24 TR DB  */
/*
  0 * Max Width -> *
 32,                      ,   ,  ,  ,  ,  ,  ,  ,  ,  },
 33,                      ,   ,  ,  ,  ,  ,  ,  ,  ,  },
 34,
 35,
 36,
 37,
 38,
 39,
 40,
 41,
 42,
 43,
 44,
 45,
 46,
 47,
 48,
 49,
 50,
 51,
 52,
 53,
 54,
 55,
 56,
 57,
 58,
 59,
 60,
 61,
 62,
 63,
 64,
 65,
 66,
 67,
 68,
 69,
 70,
 71,
 72,
 73,
 74,
 75,
 76,
 77,
 78,
 79,
 80,
 81,
 82,
 83,
 84,
 85,
 86,
 87,
 88,
 89,
 90,
 91,
 92,
 93,
 94,
 95,
 96,
 97,
 98,
 99,
100,
101,
102,
103,
104,
105,
106,
107,
108,
109,
110,
111,
112,
113,
114,
115,
116,
117,
118,
119,
120,
121,
122,
123,
124,
125,
126,
127,
,
257
A_acute,
a_acute,
A_breve,
a_breve,
A_tail,
a_tail,
A_circle,
a_circle,
A_circumflex,
a_circumflex,
A_diaeresis,
a_diaeresis,
A_E,
a_e,
A_grave,
a_grave,
A_macron,
a_macron,
A_tilde,
a_tilde,
a_underlined,

B_german_S,

C_acute,
c_acute,
C_backwards,
C_chz,
c_chz,
C_cedilla,
c_cedilla,

D_bar,
d_bar,
D_chz,
d_chz,

E_acute,
e_acute,
E_breve,
e_breve,
E_chz,
e_chz,
E_tail,
e_tail,
E_circumflex,
e_circumflex,
E_diaeresis,
e_diaeresis,
E_grave,
e_grave,
E_macron,
e_macron,

I_acute,
i_acute,
I_circumflex,
i_circumflex,
I_diaeresis,
i_diaeresis,
I_grave,
i_grave,

I_P,
I_p,
i_j,

J_circumflex,
j_circumflex,

H_circumflex,
h_circumflex,

L_acute,
l_acute,
L_chz,
l_chz,
L_slash,
l_slash,
L_dot,
l_dot,

N_acute,
n_acute,
N_chz,
n_chz,
N_tilde,
n_tilde,


O_acuteacute,
o_acuteacute,
O_acute,
o_acute,
O_circumflex,
o_circumflex,
O_diaeresis,
o_diaeresis,
O_E,
o_e,
O_grave,
o_grave,
O_slash,
o_slash,
O_tilde,
o_tilde,
o_underlined,

R_acute,
r_acute,
R_chz,
r_chz,

S_acute,
s_acute,
S_cedilla,
s_cedilla,
S_tail,
s_tail,
S_circumflex,
s_circumflex,
S_breve,
s_breve,
S_chz,
s_chz,

T_cedilla,
t_cedilla,
T_chz,
t_chz,

U_acute,
u_acute,
U_acuteacute,
u_acuteacute,
U_breve,
u_breve,
U_circle,
u_circle,
U_circumflex,
u_circumflex,
U_diaeresis,
u_diaeresis,
U_grave,
u_grave,

Y_acute,
y_acute,
Y_diaeresis,
y_diaeresis,

Z_acute,
z_acute,
Z_chz,
z_chz,
Z_plus,
z_plus,

* Diacritical marks *

DM_macron,
DM_center_bar,
DM_under_bar,
DM_circumflex,
DM_breve,
DM_chz,
DM_tilde,
DM_diaeresis,
DM_cedilla,
DM_tail,
DM_acute,
DM_grave,
DM_virgule,
DM_parallels,
DM_circle,
DM_plus,
DM_acuteacute,

* Text symbols *
SYM_daggar,
SYM_double_daggar,
SYM_paragraph,
SYM_section,
SYM_big_asterisk,
SYM_house,

* Buisness *
SYM_copyright,
SYM_registered,
SYM_pounds,
SYM_yen,
SYM_cents,
SYM_trade_mark,
SYM_francs,
SYM_Tx,
SYM_Pt,
SYM_degrees_C,
SYM_degrees_F,
SYM_degrees,
SYM_X_circle,

* Punctuation *
SYM_UD_question,
SYM_UD_exclamation,
SYM_double_exclamation,
SYM_french_begin_quote,
SYM_french_end_quote,
SYM_bar_left,
SYM_bar_right,
SYM_split_vert_bar,
SYM_vert_bar,

* directional *

SYM_arrow_left,
SYM_arrow_right,
SYM_arrow_leftright,
SYM_arrow_down,
SYM_arrow_up,
SYM_arrow_updown,
SYM_arrow_updown_under,
SYM_triangle_left,
SYM_triangle_right,
SYM_triangle_up,
SYM_triangle_down,
SYM_triangle_left_solid,
SYM_triangle_right_solid,
SYM_triangle_up_solid,
SYM_triangle_down_solid,

TRIANGLE_ULC,
TRIANGLE_LLC,
TRIANGLE_URC,
TRIANGLE_LRC,

* Graphics *

SYM_bar,
SYM_diamond_open,
SYM_square,
SYM_filled_square,
SYM_small_circle,
SYM_small_circle_rvrsd,
SYM_circle,
SYM_filled_circle,
SYM_largedot_rvrsd,
SYM_largedot,
SYM_cdot,
SYM_cpoint,

SYM_smiley_white,
SYM_smiley_black,
SYM_heart,
SYM_diamond,
SYM_club,
SYM_spade,
SYM_male,
SYM_female,

* 12  Quarter Block graphics,
   34                         *

QBG_1,
QBG_2,
QBG_3,
QBG_4,
QBG_12,
QBG_13,
QBG_14,
QBG_23,
QBG_24,
QBG_34,
QBG_123,
QBG_134,
QBG_124,
QBG_234,
QBG_1234,

* circle quarters *

CQ_1,
CQ_2,
CQ_3,
CQ_4,

* checker board *

CB_low,
CB_med,
CB_high,

LG_sVB,
LG_sLT,
LG_dLsT,
LG_sLdT,
LG_sLdDC,
LG_dLsDC,
LG_dLT,
LG_dVB,
LG_dLDC,
LG_dLUC,
LG_sLdUC,
LG_dLsUC,
LG_sLDC,
LG_sUsRC,
LG_sUT,
LG_sDT,
LG_sRT,
LG_sHB,
LG_sUDLRI,
LG_dRsT,
LG_sRdT,
LG_dURC,
LG_dDRC,
LG_dUT,  
LG_dDT,
LG_dRT,
LG_dHB,
LG_dUDLRI,
LG_sUdT,
LG_dUsT,
LG_sDdT,
LG_dDsT,
LG_dUsRC,
LG_sUdRC,
LG_sDdRC,
LG_dDsRC,
LG_dUDsLRI,
LG_sUDdLRI,
LG_sULC,
LG_sDRC,


SYM_one_half,
SYM_one_quarter,
SYM_three_quarters,
SYM_exponent_1,
SYM_exponent_2,
SYM_exponent_3,
SYM_exponent_n,
SYM_GTE,
SYM_LTE,
SYM_plus_minus,
SYM_infinity,
SYM_equivelence,
SYM_intersection,
SYM_union,
SYM_approximate,
SYM_root,
SYM_times,
SYM_overline_x,
SYM_division,


SYM_quaver,
SYM_quaverquaver,

* Greek *

GRK_alpha,
GRK_beta,
GRK_gamma,
GRK_delta,
GRK_epsilon,
GRK_zeta,
GRK_eta,
GRK_theta,
GRK_iota,
GRK_kappa,
GRK_lambda,
GRK_mu,
GRK_nu,
GRK_xi,
GRK_pi,
GRK_omicron,
GRK_rho,
GRK_sigma,
GRK_tau,
GRK_upsilon,
GRK_phi,
GRK_chi,
GRK_psi,
GRK_omega,

GRK_Alpha,
GRK_Beta,
GRK_Gamma,
GRK_Delta,
GRK_Epsilon,
GRK_Zeta,
GRK_Eta,
GRK_Theta,
GRK_Iota,
GRK_Kappa,
GRK_Lambda,
GRK_Mu,
GRK_Nu,
GRK_Xi,
GRK_Pi,
GRK_Omicron,
GRK_Rho,
GRK_Sigma,
GRK_Tau,
GRK_Upsilon,
GRK_Phi,
GRK_Chi,
GRK_Psi,
GRK_Omega,

GRK_UDOmega,
*/
#endif
//escseq