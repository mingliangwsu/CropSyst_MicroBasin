/*  ANSI user interface procedures */
// This C_version has been replaced with the new C++ version

#include <rlib/language.h>
#include <rlib/rui/ui.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __MSDOS__
#include <conio.h>
#endif
#ifdef _Windows
#include  <windows.h>
#else
#include <rlib/rui/ansi.h>
#endif

#define MAXNAME 128

#ifdef AMIGADOS
extern int UI_num_rows;
extern int UI_num_cols;
#else
int UI_num_rows     = 24;
int UI_num_cols     = 79;
#endif
//int UI_MESSAGE_LINE = 23;  moved to RUI
int UI_STATUS_LINE  =  1;
int UI_PROMPT_LINE  = 23;
#ifdef __MSDOS__
int UI_SCREEN_ROWS  = 25;
#else
int UI_SCREEN_ROWS  = 24;
#endif
int UI_SCREEN_COLS  = 79;
int UI_WINDOW_ROWS  = 24;
int UI_WINDOW_COLS  = 80;

/* not needed in ANSI version (console maintains)
UI_char ui_background_color;
UI_char ui_foreground_color;
UI_char ui_attribute;
*/

#define ui_screen_rows UI_num_rows

#ifdef UNIX
#if	defined(SYSV) || defined(IRIX) /* || defined(AIX) */
#include	<termio.h>
struct termio ANSI_old_state;
struct termio ANSI_new_state;
#else
#include <sgtty.h>
static struct sgttyb ANSI_old_state;
static struct sgttyb ANSI_new_state;
#endif
#endif

void UI_initialize()
{
  term = new terminal();

#ifdef AMIGADOS
   /* For the Amiga, we can bind the output to the current CLI window
      so that we can work from a terminal on AUX: */
   windinit();
#endif /* AMIGADOS */

#ifdef UNIX
   /* For UNIX, we need to put the tty port in CBREAK/CANON mode */
#  ifdef	POSIX
      tcgetattr (0, &ANSI_old_state);
      tcgetattr (0, &ANSI_new_state);
      /* ANSI_new_state.c_lflag &= ~(ISIG | ICANON | ECHO); */
      ANSI_new_state.c_lflag &= ~(ICANON | ECHO);
      /* ANSI_new_state.c_iflag &= ~ICRNL;
	   ANSI_new_state.c_oflag &= ~(ONLCR | OPOST);
      */
      ANSI_new_state.c_cc[VMIN] = 1;
      ANSI_new_state.c_cc[VTIME] = 0;
      tcsetattr (0, TCSADRAIN, &ANSI_new_state);
#  else
#    if defined(SYSV) || defined(IRIX) /* || defined(AIX)  */
	(void) ioctl(0, TCGETA, &ANSI_old_state);
	(void) ioctl(0, TCGETA, &ANSI_new_state);

	/* ANSI_new_state.c_lflag &= ~(ICANON | ISIG | ECHO); */
	/* ANSI_new_state.c_lflag &= ~(ICANON | ECHO);  */
	ANSI_new_state.c_lflag &=
                  ~(ICANON | ECHO | ECHOE | ECHOK |ECHONL);
	ANSI_new_state.c_oflag &= ~(OPOST | ONLCR);
	/* ANSI_new_state.c_iflag &= ~ICRNL; */
	ANSI_new_state.c_iflag |= IGNCR;

	ANSI_new_state.c_cc[VMIN] = '\01';
	ANSI_new_state.c_cc[VTIME] = '\0';
	(void) ioctl(0, TCSETA, &ANSI_new_state);
#    else
	ioctl(0, TIOCGETP, &ANSI_old_state);
	ioctl(0, TIOCGETP, &ANSI_new_state);
	/*ANSI_new_state.sg_flags |= ISIG;  | RAW */
	ANSI_new_state.sg_flags = ANSI_new_state.sg_flags &
                        ~(ECHO ) | CBREAK;
	ioctl(0, TIOCSETP, &ANSI_new_state);
#    endif
#  endif
#endif

  ANSI_RESET(stdout);
  /* ANSI_SET_MODE(ANSI_LF_NL_MODE); */
  ANSI_RESET_MODE(stdout,ANSI_WRAP_MODE);
  ui_screen_rows = UI_num_rows;  /* Actually we want the terminal supply this */
  ANSI_ERASE_DISPLAY(stdout);

#ifdef __MSDOS__
   fprintf(stdout,"\033[=3h");  // Enable color text mode
#endif
};

/*  Expression window routines *******************************************/

void UI_clear()
{
#  ifdef __MSDOS__
     clrscr();
#  else
     ANSI_ERASE_IN_DISPLAY(ANSI_ERASE_COMPLETELY);
#  endif
};

#if defined(__STDC__) || defined(__cplusplus)
void UI_writeat(
  UI_row print_row, UI_col print_col,
  unsigned char fore_color, unsigned char back_color, /* not used */
  unsigned int attrs,  /* not used */
  unsigned char *printstr)
#else
void UI_writeat( print_row, print_col, fore_color, back_color, attrs, printstr)
UI_row print_row; UI_col print_col;
unsigned char fore_color; unsigned char back_color;
unsigned int attrs;
unsigned char *printstr;
#endif
{
   int col,row;
   char outtext[255];
   row = print_row;
   col = print_col;
   ANSI_RESET_MODE(stdout,ANSI_SCROLL_MODE);
   ANSI_CURSOR_POSITION(stdout,row,col);

   strcpy(outtext, &printstr[0]);
   puts(outtext);
};
void UI_stop()
{
   ANSI_RESET(stdout);
#ifdef AMIGADOS
   /* For the Amiga, we can bind the output to the current CLI window
      so that we can work from a terminal on AUX: */
   windexit();
#endif /* AMIGADOS */

#ifdef UNIX
#  ifdef POSIX
	tcsetattr (0, TCSADRAIN, &ANSI_old_state);
#  else
#    if	defined(SYSV) || defined(IRIS) /* || defined(AIX) */
        ioctl(0, TCSETA, &ANSI_old_state);
#    else
	ioctl(0, TIOCSETP, &ANSI_old_state);
#    endif
#  endif
#endif
};
/* move to status RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
void UI_status(UI_char *status_str1,UI_char *status_str2)
#else
void UI_status(status_str1,status_str2)
UI_char *status_str1;UI_char *status_str2;
#endif
{
    char status_str[160];

    strcpy(status_str,status_str1);
    strcat(status_str,status_str2);

    ANSI_CURSOR_POSITION(stdout,ui_screen_rows-1,1);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_CLR3);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_REVERSE);
    ANSI_ERASE_LINE(stdout);
    ANSI_CURSOR_FORWARD(stdout,(80-strlen(status_str))/2);
    printf("%s",status_str);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_NORMAL);
    printf("\r");
};
*/
/* moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
void UI_prompt(UI_char *prompt_str)
#else
void UI_prompt(prompt_str)
UI_char *prompt_str;
#endif
{
    ANSI_CURSOR_POSITION(stdout,UI_PROMPT_LINE,1);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_NORMAL);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_CLR2);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_REVERSE);
    ANSI_ERASE_LINE(stdout);
    ANSI_CURSOR_FORWARD(stdout,(80-strlen(prompt_str))/2);
    printf("%s\n",prompt_str);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_NORMAL);
};
*/
/*
int UI_handle_events(UI_char *main_prompt)
{
   int command;

   UI_prompt(main_prompt);
   process_command(command);
   return((command == UI_QUIT) ? 0 : 1);
};
*/
/*
#if defined(__STDC__) || defined(__cplusplus)
void UI_message1(UI_char *text1)
#else
void UI_message1(text1)
UI_char *text1;
#endif
{
   ANSI_CURSOR_POSITION(stdout,UI_MESSAGE_LINE,1);
   ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_REVERSE);
   ANSI_ERASE_LINE(stdout);
   ANSI_CURSOR_FORWARD(stdout,(80-strlen(text1))/2);
   puts(text1); putchar('\r');
   ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_NORMAL);
};
*/
/*
#if defined(__STDC__) || defined(__cplusplus)
void UI_message2(UI_char *text1, UI_char *text2)
#else
void UI_message2(text1, text2)
UI_char *text1; UI_char *text2;
#endif
{ 
   char message[255];

   sprintf(message,"%s|%s",text1,text2);
   ANSI_CURSOR_POSITION(stdout,UI_MESSAGE_LINE,1);
   ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_REVERSE);
   ANSI_ERASE_LINE(stdout);
   ANSI_CURSOR_FORWARD(stdout,(80-strlen(message))/2);
   puts(message); putchar('\r');
   ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_NORMAL);
};
*/
/* moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
void UI_message_wait(UI_char *text1,char *text2)
#else
void UI_message_wait(text1,text2)
UI_char *text1;char *text2;
#endif
{
    int inkey;
    ANSI_CURSOR_POSITION(stdout,5,1);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_REVERSE);
    ANSI_ERASE_LINE(stdout);
    putchar('\n');
    ANSI_ERASE_LINE(stdout);
    ANSI_CURSOR_FORWARD(stdout,(80-strlen(text1))/2);
    puts(text1);
    putchar('\n');
    ANSI_ERASE_LINE(stdout);
    putchar('\n');
    ANSI_ERASE_LINE(stdout);
    ANSI_CURSOR_FORWARD(stdout,(80-strlen(text2))/2);
    puts(text2);
    putchar('\n');
    ANSI_ERASE_LINE(stdout);
    ANSI_SELECT_GRAPHIC_RENDITION(stdout,ANSI_NORMAL);
    inkey = ANSI_read_keyboard();
};
*/
/*
Moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
char UI_prompt_key(UI_char *prompt_str,UI_char *allowable)
#else
char UI_prompt_key(prompt_str,allowable)
UI_char *prompt_str;UI_char *allowable;
#endif
{
    int inkey;

    UI_prompt(prompt_str);
    inkey = ANSI_read_keyboard();
    UI_prompt("");
    ANSI_ERASE_LINE(stdout);
    if (strchr(allowable,inkey)) return(inkey);
    return(0);
};
*/
/* Moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
int UI_prompt_yes_no(UI_char *prompt_str)
#else
int UI_prompt_yes_no(prompt_str)
UI_char *prompt_str;
#endif
{
   switch(UI_prompt_key(prompt_str,"YN"))
   { case 'Y' : return(1); break;
     case 'N' : return(0); break;
   };
};
*/
/* Moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
void UI_read_string(UI_char *buffer)
#else
void UI_read_string(buffer)
UI_char *buffer;
#endif
{
  char input_buffer[80];
  int inkey;
  int buffer_pos = 0;
  input_buffer[0] = 0;
  while ((inkey = ANSI_read_keyboard()) != 13)
  {
     if (inkey == 8)
     {
        input_buffer[buffer_pos] = 0;
        if (buffer_pos)
           input_buffer[--buffer_pos] = 0;
     }
     else
     {
        input_buffer[buffer_pos] = (char)inkey;
        buffer_pos += 1;
        input_buffer[buffer_pos] = 0;
     };
     putchar(inkey);
     fflush(stdout);
   };
   strcpy(buffer,input_buffer);
};
*/
/* Moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
UI_char *UI_prompt_string(UI_char *prompt_str,UI_char *answer)
#else
UI_char *UI_prompt_string(prompt_str,answer)
UI_char *prompt_str;UI_char *answer;
#endif
{
    UI_prompt(prompt_str);
    ANSI_ERASE_LINE(stdout);
    UI_read_string(answer);
    UI_prompt("");
    ANSI_ERASE_LINE(stdout);
    return(answer);
};
*/
/* Move to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
long int UI_prompt_integer(UI_char *prompt_str,int default_number)
#else
long int UI_prompt_integer(prompt_str,default_number)
UI_char *prompt_str;int default_number;
#endif
{
    char answer_str[80];
    int answer;
    answer = default_number;
    UI_prompt_string(prompt_str,answer_str);
    sscanf(answer_str,"%d",&answer);
    UI_prompt("");
    ANSI_ERASE_LINE(stdout);

    return(answer);
};
*/
/* Moved to RUI.CPP
#if defined(__STDC__) || defined(__cplusplus)
void UI_error_help(char *error_file,UI_char *error_string)
#else
void UI_error_help(error_file,error_string)
char *error_file;UI_char *error_string;
#endif
{
   char sys_command[80];

   //actually join error_string and error_file as a temp file and
   //   display the temp file.

   strcpy(sys_command,"c:muchmore ");
   strcat(sys_command,"fitb:help/");
   strcat(sys_command,error_file);

#ifdef _Windows
   //   EasyWin
   WinExec(sys_command,SW_SHOWNORMAL);
#else
   system(sys_command);
#endif
};
*/
/*******************************************************************/
/* The file requester will eventually become a real file requestor,
   for now, we will just prompt for the filename
moved to rui.cpp
#if defined(__STDC__) || defined(__cplusplus)
char *UI_request_filename(char *default_filename,int must_exist)
#else
char *UI_request_filename(default_filename,must_exist)
char *default_filename;
int must_exist;
#endif
{
  int exit_ok=0;
  do
  {                  //  translate(L_Enter_filename)
    UI_prompt_string("Enter filename",default_filename);
    exit_ok = (must_exist) ? 1 / *file_exists(default_filename)* / : 1;
  } while (!exit_ok);
  return(default_filename);
};
*/
int key_lookup_table[][3] =
{
   {ANSI_KEY_UP,     0, UI_KEY_UP},
   {ANSI_KEY_DOWN,   0, UI_KEY_DOWN},
   {ANSI_KEY_RIGHT,  0, UI_KEY_RIGHT},
   {ANSI_KEY_LEFT,   0, UI_KEY_LEFT},
   {ANSI_KP_ENTER,   0, UI_KP_ENTER},
   {ANSI_KP_PF1,     0, UI_KEY_PF1},
   {ANSI_KP_PF2,     0, UI_KEY_PF2},
   {ANSI_KP_PF3,     0, UI_KEY_PF3},
   {ANSI_KP_PF4,     0, UI_KEY_PF4},
   {ANSI_KP_COMMA,   0, UI_KP_COMMA},
   {ANSI_KP_MINUS,   0, UI_KP_MINUS},
   {ANSI_KP_PERIOD,  0, UI_KP_PERIOD},
   {ANSI_KP_0,  0, UI_KP_0},
   {ANSI_KP_1,  0, UI_KP_1},
   {ANSI_KP_2,  0, UI_KP_2},
   {ANSI_KP_3,  0, UI_KP_3},
   {ANSI_KP_4,  0, UI_KP_4},
   {ANSI_KP_5,  0, UI_KP_5},
   {ANSI_KP_6,  0, UI_KP_6},
   {ANSI_KP_7,  0, UI_KP_7},
   {ANSI_KP_8,  0, UI_KP_8},
   {ANSI_KP_9,  0, UI_KP_9},
   {ANSI_KEY_F1, 0,UI_KEY_F1},
   {ANSI_KEY_F2, 0,UI_KEY_F2},
   {ANSI_KEY_F3, 0,UI_KEY_F3},
   {ANSI_KEY_F4, 0,UI_KEY_F4},
   {ANSI_KEY_F5, 0,UI_KEY_F5},
   {ANSI_KEY_F6, 0,UI_KEY_F6},
   {ANSI_KEY_F7, 0,UI_KEY_F7},
   {ANSI_KEY_F8, 0,UI_KEY_F8},
   {ANSI_KEY_F9, 0,UI_KEY_F9},
   {ANSI_KEY_F10, 0,UI_KEY_F10},
   {ANSI_KEY_SHIFT_DOWN, 1,ANSI_KEY_DOWN},
   {ANSI_KEY_SHIFT_UP  , 1,ANSI_KEY_UP},
   {ANSI_KEY_SHIFT_LEFT  , 1,ANSI_KEY_LEFT},
   {ANSI_KEY_SHIFT_RIGHT  , 1,ANSI_KEY_RIGHT},
   {ANSI_KEY_F1, 1,UI_KEY_F1},
   {ANSI_KEY_F2, 1,UI_KEY_F2},
   {ANSI_KEY_F3, 1,UI_KEY_F3},
   {ANSI_KEY_F4, 1,UI_KEY_F4},
   {ANSI_KEY_F5, 1,UI_KEY_F5},
   {ANSI_KEY_F6, 1,UI_KEY_F6},
   {ANSI_KEY_F7, 1,UI_KEY_F7},
   {ANSI_KEY_F8, 1,UI_KEY_F8},
   {ANSI_KEY_F9, 1,UI_KEY_F9},
   {ANSI_KEY_F10, 1,UI_KEY_F10},
   {ANSI_KEY_APPL_UP,     0, UI_KEY_UP},
   {ANSI_KEY_APPL_DOWN,   0, UI_KEY_DOWN},
   {ANSI_KEY_APPL_RIGHT,  0, UI_KEY_RIGHT},
   {ANSI_KEY_APPL_LEFT,   0, UI_KEY_LEFT},
   {ANSI_KEY_SHIFT_APPL_UP,     1, UI_KEY_UP},
   {ANSI_KEY_SHIFT_APPL_DOWN,   1, UI_KEY_DOWN},
   {0,0,0}
};

UI_keycode UI_read_key()
{
   int keyread;
   keyread = ANSI_read_keyboard();
   return(keyread);
};
/*
struct UI_key_translation UI_key_translation_table[] =
{
{ANSI_KEY_UP          ,KN_UP},
{ANSI_KEY_DOWN        ,KN_DOWN},
{ANSI_KEY_RIGHT       ,KN_RIGHT},
{ANSI_KEY_LEFT        ,KN_LEFT},
{ANSI_KP_ENTER        ,KN_ENTER},
{ANSI_KP_PF1          ,KN_PF1},
{ANSI_KP_PF2          ,KN_PF2},
{ANSI_KP_PF3          ,KN_PF3},
{ANSI_KEY_SHIFT_DOWN  ,KN_S_DOWN},
{ANSI_KP_PF4          ,KN_PF4},
{ANSI_KEY_SHIFT_UP    ,KN_S_UP},
{ANSI_KP_COMMA        ,KN_KP_COMMA},
{ANSI_KP_MINUS        ,KN_KP_MINUS},
{ANSI_KP_PERIOD       ,KN_KP_PERIOD},
{ANSI_KP_0            ,KN_KP_0},
{ANSI_KP_1            ,KN_KP_1},
{ANSI_KP_2            ,KN_KP_2},
{ANSI_KP_3            ,KN_KP_3},
{ANSI_KP_4            ,KN_KP_4},
{ANSI_KP_5            ,KN_KP_5},
{ANSI_KP_6            ,KN_KP_6},
{ANSI_KP_7            ,KN_KP_7},
{ANSI_KP_8            ,KN_KP_8},
{ANSI_KP_9            ,KN_KP_9},
{ANSI_KEY_SHIFT_LEFT  ,KN_S_LEFT},
{ANSI_KEY_SHIFT_RIGHT ,KN_S_RIGHT},
{ANSI_KEY_SHIFT_F1    ,KN_S_F1},
{ANSI_KEY_SHIFT_F2    ,KN_S_F2},
{ANSI_KEY_SHIFT_F3    ,KN_S_F3},
{ANSI_KEY_SHIFT_F4    ,KN_S_F4},
{ANSI_KEY_SHIFT_F5    ,KN_S_F5},
{ANSI_KEY_SHIFT_F6    ,KN_S_F6},
{ANSI_KEY_SHIFT_F7    ,KN_S_F7},
{ANSI_KEY_SHIFT_F8    ,KN_S_F8},
{ANSI_KEY_SHIFT_F9    ,KN_S_F9},
{ANSI_KEY_SHIFT_F10   ,KN_S_F10},
{ANSI_KEY_F1          ,KN_F1},
{ANSI_KEY_F2          ,KN_F2},
{ANSI_KEY_F3          ,KN_F3},
{ANSI_KEY_F4          ,KN_F4},
{ANSI_KEY_F5          ,KN_F5},
{ANSI_KEY_F6          ,KN_F6},
{ANSI_KEY_F7          ,KN_F7},
{ANSI_KEY_F8          ,KN_F8},
{ANSI_KEY_F9          ,KN_F9},
{ANSI_KEY_F10         ,KN_F10},
{ANSI_KEY_HELP        ,KN_HELP},
{ANSI_KEY_APPL_UP     ,KN_APPL_UP},
{ANSI_KEY_APPL_DOWN   ,KN_APPL_DOWN},
{ANSI_KEY_APPL_RIGHT  ,KN_APPL_RIGHT},
{ANSI_KEY_APPL_LEFT   ,KN_APPL_LEFT},
{ANSI_KEY_SHIFT_APPL_DOWN  ,KN_APPL_S_DOWN},
{ANSI_KEY_SHIFT_APPL_UP    ,KN_APPL_S_UP},
{END_KEY_TABLE, ""}
};
*/


