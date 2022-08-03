#ifndef ANSI_LIB
#define ANSI_LIB


int ANSI_read_keyboard();

#define TI   "\033["
#define TERM_BELL              '\07'
#define TERM_BACKSPACE         '\010'
#define TERM_HORIZONTAL_TAB    '\011'
#define TERM_LINE_FEED         '\012'
#define TERM_VERTICAL_TAB      '\013'
#define TERM_FORM_FEED         '\014'
#define TERM_CARRIAGE_RETURN   '\015'
#define TERM_SHIFT_IN          '\016'
#define TERM_SHIFT_OUT         '\017'

#define TERM_INDEX             "\033D"
#define TERM_NEXT_LINE         "\033E"
#define TERM_HORIZ_TAB_SET     "\033H"
#define TERM_REVERSE_INDEX     "\033M"

#define TERM_RESET             "\033c"
/*
	Control Sequences, with the number of indicated parameters.
	i.e. <CSI><parameters><control sequence letter(s)>.  Note the
	last entries consist of a space and a letter.  CSI is either
	9B or Esc[.  A minus after the number of parameters (#p)
	indicates less is valid.  Parameters are seperated by
	semicolins, e.g. Esc[14;80H sets the cursor position to row
	14, column 80.
*/

#define TERM_ERASE_TO_END 0
#define TERM_ERASE_TO_CURSOR 1
#define TERM_ERASE_COMPLETELY 2

#define TERM_INSERT_REPLACE_MODE "4"

#define TERM_KEYBOARD_ACTION_MODE "2"
#define TERM_LF_NL_MODE  "20"
#define TERM_SCROLL_MODE ">1"
#define TERM_CURSOR_KEY_MODE "?1"
#ifndef AMIGA
#define TERM_SEND_RECEIVE_MODE "12"
#define TERM_COLUMN_MODE "?3"
#define TERM_SCREEN_MODE "?5"
#endif
#define TERM_WRAP_MODE   "?7"
#define TERM_AUTO_REPEAT_MODE "?8"

/* The following are graphics renditions */
#define TERM_NORMAL        0
#define TERM_BOLD          1
#define TERM_ITALICS       3
#define TERM_UNDERLINE     4
#define TERM_BLINK         5  /* Not implement on the Amiga */
#define TERM_REVERSE       7
#define TERM_NO_BOLD      21  /* ? */
#define TERM_NO_ATTRIBUTE 22	/* default foreground color, not bold */
#define TERM_NO_ITALICS   23
#define TERM_NO_UNDERLINE 24
#define TERM_NO_BLINK     25  /* Not implemented on amiga */
#define TERM_NO_REVERSE   27

/* these names refer to the ANSI standard, not the implementation */
#define TERM_BLACK	30
#define TERM_RED	31
#define TERM_GREEN	32
#define TERM_YELLOW	33
#define TERM_BLUE	34
#define TERM_MAGENTA	35
#define TERM_CYAN	36
#define TERM_WHITE	37
#define TERM_DEFAULT	39

#define TERM_BLACKBG	40
#define TERM_REDBG	41
#define TERM_GREENBG	42
#define TERM_YELLOWBG	43
#define TERM_BLUEBG	44
#define TERM_MAGENTABG	45
#define TERM_CYANBG	46
#define TERM_WHITEBG	47
#define TERM_DEFAULTBG	49

/* these names refer to the implementation, they are the preferred */
/* names for use with the Amiga console device. */
#define TERM_CLR0	30
#define TERM_CLR1	31
#define TERM_CLR2	32
#define TERM_CLR3	33
#define TERM_CLR4	34
#define TERM_CLR5	35
#define TERM_CLR6	36
#define TERM_CLR7	37

#define TERM_CLR0BG	40
#define TERM_CLR1BG	41
#define TERM_CLR2BG	42
#define TERM_CLR3BG	43
#define TERM_CLR4BG	44
#define TERM_CLR5BG	45
#define TERM_CLR6BG	46
#define TERM_CLR7BG	47



/*The following are character sizes */
/*      TERM_NORMAL         0 */
#define TERM_ELITE_ON       2
#define TERM_ELITE_OFF      1
#define TERM_CONDENSED_ON   4
#define TERM_CONDENSED_OFF  3
#define TERM_ENLARGED_ON    6
#define TERM_ENLARGED_OFF   5

#define TERM_ELITE          TERM_ELITE_ON
#define TERM_CONDENSED      TERM_CONDENSED_ON
#define TERM_ENLARGED       TERM_ENLARGED_ON


/* The following a print qualities */
#define TERM_SHADOW_ON          6
#define TERM_SHADOW_OFF         5
#define TERM_DOUBLESTRIKE_ON    4
#define TERM_DOUBLESTRIKE_OFF   3
#define TERM_LETTER_QUALITY_ON  2
#define TERM_LETTER_QUALITY_OFF 1


#define TERM_GENERAL_STATUS  "5"
#define TERM_PRINTER_STATUS  "?15"

#ifdef AMIGA
#define TERM_CURSOR_RENDITION_ON  " "
#define TERM_CURSOR_RENDITION_OFF "0 "
#define TERM_0

#endif AMIGA



/****** DSR parameters ******

#define DSR_CPR		6

****** CTC parameters ******
#define CTC_HSETTAB	0
#define CTC_HCLRTAB	2
#define CTC_HCLRTABSALL	5

******	TBC parameters ******
#define TBC_HCLRTAB	0
#define TBC_HCLRTABSALL	3

*/

#define TERM_KEY_UP          400
#define TERM_KEY_DOWN        401
#define TERM_KEY_RIGHT       402
#define TERM_KEY_LEFT        403
#define TERM_KP_ENTER        404
#define TERM_KP_PF1          405
#define TERM_KP_PF2          406
#define TERM_KP_PF3          407
#define TERM_KEY_SHIFT_DOWN  408
#define TERM_KP_PF4          409
#define TERM_KEY_SHIFT_UP    410
#define TERM_KP_COMMA        411
#define TERM_KP_MINUS        412
#define TERM_KP_PERIOD       413
#define TERM_KP_0            414
#define TERM_KP_1            415
#define TERM_KP_2            416
#define TERM_KP_3            417
#define TERM_KP_4            418
#define TERM_KP_5            419
#define TERM_KP_6            420
#define TERM_KP_7            421
#define TERM_KP_8            422
#define TERM_KP_9            423
#define TERM_KEY_SHIFT_LEFT  424
#define TERM_KEY_SHIFT_RIGHT 425
#define TERM_KEY_SHIFT_F1       427
#define TERM_KEY_SHIFT_F2       428
#define TERM_KEY_SHIFT_F3       429
#define TERM_KEY_SHIFT_F4       430
#define TERM_KEY_SHIFT_F5       431
#define TERM_KEY_SHIFT_F6       432
#define TERM_KEY_SHIFT_F7       433
#define TERM_KEY_SHIFT_F8       434
#define TERM_KEY_SHIFT_F9       435
#define TERM_KEY_SHIFT_F10       436
#define TERM_KEY_F1              426
#define TERM_KEY_F2              437
#define TERM_KEY_F3              438
#define TERM_KEY_F4              439
#define TERM_KEY_F5              440
#define TERM_KEY_F6              441
#define TERM_KEY_F7              442
#define TERM_KEY_F8              443
#define TERM_KEY_F9              444
#define TERM_KEY_F10             445
#define TERM_KEY_HELP            446
#define TERM_KEY_APPL_UP          447
#define TERM_KEY_APPL_DOWN        448
#define TERM_KEY_APPL_RIGHT       449
#define TERM_KEY_APPL_LEFT        450
#define TERM_KEY_SHIFT_APPL_DOWN  451
#define TERM_KEY_SHIFT_APPL_UP    452


#else  // obsolete:

#define ANSI_BELL(outfile)              fputc(7,outfile)
#define ANSI_BACKSPACE(outfile)         fputc(8,outfile)
#define ANSI_HORIZONTAL_TAB(outfile)    fputc(9,outfile)
#define ANSI_LINE_FEED(outfile)         fputc(10,outfile)
#define ANSI_VERTICAL_TAB(outfile)      fputc(11,outfile)
#define ANSI_FORM_FEED(outfile)         fputc(12,outfile)
#define ANSI_CARRIAGE_RETURN(outfile)   fputc(13,outfile)
#define ANSI_SHIFT_IN(outfile)          fputc(14,outfile)
#define ANSI_SHIFT_OUT(outfile)         fputc(15,outfile)
#define ANSI_ESC(outfile)               fputc(16,outfile)

#define ANSI_INDEX(outfile)             fputc('\033',outfile);fputc('D',outfile)
#define ANSI_NEXT_LINE(outfile)         fputc('\033',outfile);fputc('E',outfile)
#define ANSI_HORIZ_TAB_SET(outfile)     fputc('\033',outfile);fputc('H',outfile)
#define ANSI_REVERSE_INDEX(outfile)     fputc('\033',outfile);fputc('M',outfile)

#define ANSI_RESET(outfile)             fputc('\033',outfile);fputc('c',outfile)
/*
	Control Sequences, with the number of indicated parameters.
	i.e. <CSI><parameters><control sequence letter(s)>.  Note the
	last entries consist of a space and a letter.  CSI is either
	9B or Esc[.  A minus after the number of parameters (#p)
	indicates less is valid.  Parameters are seperated by
	semicolins, e.g. Esc[14;80H sets the cursor position to row
	14, column 80.
*/
#define ANSI_INSERT_CHAR(outfile,count)            fprintf(outfile,"\033[%d@",count)
#define ANSI_CURSOR_UP(outfile,count)              fprintf(outfile,"\033[%dA",count)
#define ANSI_CURSOR_DOWN(outfile,count)            fprintf(outfile,"\033[%dB",count)
#define ANSI_CURSOR_FORWARD(outfile,count)         fprintf(outfile,"\033[%dC",count)
#define ANSI_CURSOR_BACKWARD(outfile,count)        fprintf(outfile,"\033[%dD",count)
#define ANSI_CURSOR_NEXT_LINE(outfile,count)       fprintf(outfile,"\033[%dE",count)
#define ANSI_CURSOR_PREV_LINE(outfile,count)       fprintf(outfile,"\033[%dF",count)
#define ANSI_CURSOR_POSITION(outfile,row,col)      fprintf(outfile,"\033[%d;%dH",(int)row,(int)col)
#define ANSI_CURSOR_HORIZ_TAB(outfile,count)       fprintf(outfile,"\033[%dI",count)

#define ANSI_ERASE_TO_END 0
#define ANSI_ERASE_TO_CURSOR 1
#define ANSI_ERASE_COMPLETELY 2
#define ANSI_ERASE_IN_DISPLAY(outfile,erase_mode)  fprintf(outfile,"\033[%dJ",(int)erase_mode)
#define ANSI_ERASE_DISPLAY(outfile)                fprintf(outfile,"\033[f\033[J")
#define ANSI_ERASE_IN_LINE(outfile,erase_mode)     fprintf(outfile,"\033[%dK",erase_mode)
#define ANSI_ERASE_LINE(outfile)                   fprintf(outfile,"\033[K")

#define ANSI_INSERT_LINE(outfile,count)            fprintf(outfile,"\033[%dL",count)
#define ANSI_DELETE_LINE(outfile,count)            fprintf(outfile,"\033[%dM",count)
#define ANSI_DELETE_CHAR(outfile,count)            fprintf(outfile,"\033[%dP",count)

#define ANSI_CURSOR_POSITION_REPORT(outfile,arg1,arg2)  fprintf(outfile,"\033[%d;%dR",arg1,arg2)
/* Replys with

   Esc [ Pl ; Pc R
*/


#define ANSI_SCROLL_UP(outfile,count)              fprintf(outfile,"\033[%dS",count)
#define ANSI_SCROLL_DOWN(outfile,count)            fprintf(outfile,"\033[%dT",count)
#define ANSI_CURSOR_TAB_CONTROL(outfile,arg)       fprintf(outfile,"\033[%dW",arg)
#define ANSI_CURSOR_HORIZ_VERT_POSITION(outfile,row,col)  fprintf(outfile,"\033[%d;%df",row,col)
#define ANSI_CURSOR_BACKWARD_TAB(outfile,count)    fprintf(outfile,"\033[%dZ",count)
#define ANSI_TAB_CLEAR(outfile,count)              fprintf(outfile,"\033[%dg",count)

#define ANSI_INSERT_REPLACE_MODE "4"

#define ANSI_KEYBOARD_ACTION_MODE "2"
#define ANSI_LF_NL_MODE  "20"
#define ANSI_SCROLL_MODE ">1"
#define ANSI_CURSOR_KEY_MODE "?1"
#ifndef AMIGA
#define ANSI_SEND_RECEIVE_MODE "12"
#define ANSI_COLUMN_MODE "?3"
#define ANSI_SCREEN_MODE "?5"
#endif
#define ANSI_WRAP_MODE   "?7"
#define ANSI_AUTO_REPEAT_MODE "?8"
#define ANSI_SET_MODE(outfile,mode)    fprintf(outfile,"\033[%sh",mode)
#define ANSI_RESET_MODE(outfile,mode)  fprintf(outfile,"\033[%sl",mode)

#define ANSI_SET_APPLICATION_KEYPAD_MODE(outfile) fprintf(outfile,"\033=");
#define ANSI_SET_NUMERIC_KEYPAD_MODE(outfile) fprintf(outfile,"\033>");

/* The following are graphics renditions */
#define ANSI_NORMAL        0
#define ANSI_BOLD          1
#define ANSI_ITALICS       3
#define ANSI_UNDERLINE     4
#define ANSI_BLINK         5  /* Not implement on the Amiga */
#define ANSI_REVERSE       7
#define ANSI_NO_BOLD      21  /* ? */
#define	ANSI_NO_ATTRIBUTE 22	/* default foreground color, not bold */
#define	ANSI_NO_ITALICS   23
#define	ANSI_NO_UNDERLINE 24
#define ANSI_NO_BLINK     25  /* Not implemented on amiga */
#define	ANSI_NO_REVERSE   27

/* these names refer to the ANSI standard, not the implementation */
#define ANSI_BLACK	30
#define ANSI_RED	31
#define ANSI_GREEN	32
#define ANSI_YELLOW	33
#define ANSI_BLUE	34
#define ANSI_MAGENTA	35
#define ANSI_CYAN	36
#define ANSI_WHITE	37
#define ANSI_DEFAULT	39

#define ANSI_BLACKBG	40
#define ANSI_REDBG	41
#define ANSI_GREENBG	42
#define ANSI_YELLOWBG	43
#define ANSI_BLUEBG	44
#define ANSI_MAGENTABG	45
#define ANSI_CYANBG	46
#define ANSI_WHITEBG	47
#define ANSI_DEFAULTBG	49

/* these names refer to the implementation, they are the preferred */
/* names for use with the Amiga console device. */
#define ANSI_CLR0	30
#define ANSI_CLR1	31
#define ANSI_CLR2	32
#define ANSI_CLR3	33
#define ANSI_CLR4	34
#define ANSI_CLR5	35
#define ANSI_CLR6	36
#define ANSI_CLR7	37

#define ANSI_CLR0BG	40
#define ANSI_CLR1BG	41
#define ANSI_CLR2BG	42
#define ANSI_CLR3BG	43
#define ANSI_CLR4BG	44
#define ANSI_CLR5BG	45
#define ANSI_CLR6BG	46
#define ANSI_CLR7BG	47

#define ANSI_SELECT_GRAPHIC_RENDITION(outfile,rendition) fprintf(outfile,"\033[%dm",rendition)


/*The following are character sizes */
/*      ANSI_NORMAL         0 */
#define ANSI_ELITE_ON       2
#define ANSI_ELITE_OFF      1
#define ANSI_CONDENSED_ON   4
#define ANSI_CONDENSED_OFF  3
#define ANSI_ENLARGED_ON    6
#define ANSI_ENLARGED_OFF   5

#define ANSI_ELITE          ANSI_ELITE_ON
#define ANSI_CONDENSED      ANSI_CONDENSED_ON
#define ANSI_ENLARGED       ANSI_ENLARGED_ON

#define ANSI_SELECT_CHARACTER_SIZE(outfile,rendition) fprintf(outfile,"\033[%dw",rendition)

/* The following a print qualities */
#define ANSI_SHADOW_ON          6
#define ANSI_SHADOW_OFF         5
#define ANSI_DOUBLESTRIKE_ON    4
#define ANSI_DOUBLESTRIKE_OFF   3
#define ANSI_LETTER_QUALITY_ON  2
#define ANSI_LETTER_QUALITY_OFF 1

#define ANSI_SELECT_PRINT_QUALITY(outfile,rendition) fprintf(outfile,"\033[%d\"z",rendition)

#define ANSI_GENERAL_STATUS  "5"
#define ANSI_PRINTER_STATUS  "?15"
#define ANSI_DEVICE_STATUS_REPORT(outfile,status)  fprintf(outfile,"\033[%sn",status)
/*
   Replys with :

    Esc [ 0 n        Ready, no malfunction.

    For ANSI terminals

    Esc [ ? 1 3 n    Printer not connected (Hasn't signaled ready).
    Esc [ ? 1 1 n    Printer not ready to print.
    Esc [ ? 1 0 n    Printer ready signal on.

*/

#ifdef AMIGA
#define ANSI_SET_PAGE_LENGTH(outfile,length)  fprintf(outfile,"\033[%dt",length)
#define ANSI_SET_LINE_LENGTH(outfile,length)  fprintf(outfile,"\033[%du",length)
#define ANSI_SET_LEFT_OFFSET(outfile,offset)  fprintf(outfile,"\033[%dx",offset)
#define ANSI_SET_TOP_OFFSET(outfile,offset)   fprintf(outfile,"\033[%dy",offset)
#define ANSI_SET_RAW_EVENTS(outfile,events)   fprintf(outfile,"\033[%s{",events)
#define ANSI_RESET_RAW_EVENTS(outfile,events) fprintf(outfile,"\033[%s}",events)

#define ANSI_CURSOR_RENDITION_ON  " "
#define ANSI_CURSOR_RENDITION_OFF "0 "
#define ANSI_SET_CURSOR_RENDITION(outfile,rendition) fprintf(outfile,"\033[%sp",rendition)

#define ANSI_0

#define ANSI_WINDOW_STATUS_REQUEST(outfile)    fprintf(outfile,"\033[q")
/*
	~   1	aSKR SPECIAL KEY REPORT (private Amiga Read sequence)
	|   8	aIER INPUT EVENT REPORT (private Amiga Read sequence)
	 r  4	aWBR WINDOW BOUNDS REPORT (private Amiga Read sequence)
*/
#endif AMIGA



/****** DSR parameters ******

#define DSR_CPR		6

****** CTC parameters ******
#define CTC_HSETTAB	0
#define CTC_HCLRTAB	2
#define CTC_HCLRTABSALL	5

******	TBC parameters ******
#define TBC_HCLRTAB	0
#define TBC_HCLRTABSALL	3

*/

#define ANSI_KEY_UP          400
#define ANSI_KEY_DOWN        401
#define ANSI_KEY_RIGHT       402
#define ANSI_KEY_LEFT        403
#define ANSI_KP_ENTER        404
#define ANSI_KP_PF1          405
#define ANSI_KP_PF2          406
#define ANSI_KP_PF3          407
#define ANSI_KEY_SHIFT_DOWN  408
#define ANSI_KP_PF4          409
#define ANSI_KEY_SHIFT_UP    410
#define ANSI_KP_COMMA        411
#define ANSI_KP_MINUS        412
#define ANSI_KP_PERIOD       413
#define ANSI_KP_0            414
#define ANSI_KP_1            415
#define ANSI_KP_2            416
#define ANSI_KP_3            417
#define ANSI_KP_4            418
#define ANSI_KP_5            419
#define ANSI_KP_6            420
#define ANSI_KP_7            421
#define ANSI_KP_8            422
#define ANSI_KP_9            423
#define ANSI_KEY_SHIFT_LEFT  424
#define ANSI_KEY_SHIFT_RIGHT 425
#define ANSI_KEY_SHIFT_F1       427
#define ANSI_KEY_SHIFT_F2       428
#define ANSI_KEY_SHIFT_F3       429
#define ANSI_KEY_SHIFT_F4       430
#define ANSI_KEY_SHIFT_F5       431
#define ANSI_KEY_SHIFT_F6       432
#define ANSI_KEY_SHIFT_F7       433
#define ANSI_KEY_SHIFT_F8       434
#define ANSI_KEY_SHIFT_F9       435
#define ANSI_KEY_SHIFT_F10       436
#define ANSI_KEY_F1              426
#define ANSI_KEY_F2              437
#define ANSI_KEY_F3              438
#define ANSI_KEY_F4              439
#define ANSI_KEY_F5              440
#define ANSI_KEY_F6              441
#define ANSI_KEY_F7              442
#define ANSI_KEY_F8              443
#define ANSI_KEY_F9              444
#define ANSI_KEY_F10             445
#define ANSI_KEY_HELP            446
#define ANSI_KEY_APPL_UP          447
#define ANSI_KEY_APPL_DOWN        448
#define ANSI_KEY_APPL_RIGHT       449
#define ANSI_KEY_APPL_LEFT        450
#define ANSI_KEY_SHIFT_APPL_DOWN  451
#define ANSI_KEY_SHIFT_APPL_UP    452

extern int ANSI_read_keyboard();

#endif 
