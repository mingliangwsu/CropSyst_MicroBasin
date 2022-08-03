#ifndef TERMANSI_H
#define TERMANSI_H

#include <corn/std/std_iostream.h>

#include <rlib/rui/terminal.h>
#include <rlib/rui/ansi.h>
/* This is the basic terminal class
   Other terminal classes can be derived from this
    termansi   // The default
    termcon    // EasyWin  MS-DOS CON
*/

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

#ifndef VV
#define VV virtual void
#endif

class ANSI_terminal : public terminal
{
public:

   VV reset()                            { tout << "\033c";};
   VV next_line()                        { tout << "\033E";};
   VV horiz_tab_set()                    { tout << "\033H";};
   VV reverse_index()                    { tout << "\033M";};
   VV set_application_keypad_mode()      { tout << "\033=";};
   VV set_numeric_keypad_mode()          { tout << "\033>";};
   VV insert_char(int count)            { tout << TI << count <<  '@';};
   VV cursor_up(int count)              { tout << TI << count <<  'A';};
   VV cursor_down(int count)            { tout << TI << count <<  'B';};
   VV cursor_forward(int count)         { tout << TI << count <<  'C';};
   VV cursor_backward(int count)        { tout << TI << count <<  'D';};
   VV cursor_next_line(int count)       { tout << TI << count <<  'E';};
   VV cursor_prev_line(int count)       { tout << TI << count <<  'F';};
   VV cursor_position(int row,int col)  { tout << TI << row << ';' << col << 'H'; };
   VV cursor_horiz_tab(int count)       { tout << TI << count <<  'I';};

   VV erase_in_display(int erase_mode)  { tout << TI << erase_mode << 'J';};
   VV erase_display()               { tout << "\033[f\033[J";};
   VV erase_in_line(int erase_mode)     { tout << TI << erase_mode << 'K';};
   VV erase_line()                    { tout << "\033[K"; };

   VV insert_line(int count)            { tout << TI << count <<  'L';};
   VV delete_line(int count)            { tout << TI << count <<  'M';};
   VV delete_char(int count)            { tout << TI << count <<  'P';};

   VV cursor_position_report(int arg1,int arg2)  { tout << TI << arg1 << ';' <<arg2 << 'R';};
/* Replys with
   Esc [ Pl ; Pc R
*/
   VV scroll_up(int count)              { tout << TI << count <<  'S';};
   VV scroll_down(int count)            { tout << TI << count <<  'T';};
   VV cursor_tab_control(int arg)       { tout << TI << arg << 'W';};
   VV cursor_horiz_vert_position(int row,int col)  { tout << TI << row << ';' << col << 'f';};
   VV cursor_backward_tab(int count)    { tout << TI << count <<  'Z';};
   VV tab_clear(int count)              { tout << TI << count <<  'g';};
   VV set_mode(char *mode)    { tout << TI << mode << 'h';};
   VV reset_mode(char *mode)  { tout << TI << mode << 'l';};

   VV select_graphic_rendition(int rendition)  { tout << TI << rendition << 'm';};
   VV select_character_size(int rendition)     { tout << TI << rendition << 'w';};
   VV select_print_quality(int rendition)      { tout << TI << rendition << 'z';};
   VV device_status_report(char *status)         { tout << TI << status << 'n';};
/*
   Replys with :

    Esc [ 0 n        Ready, no malfunction.

    For ANSI terminals

    Esc [ ? 1 3 n    Printer not connected (Hasn't signaled ready).
    Esc [ ? 1 1 n    Printer not ready to print.
    Esc [ ? 1 0 n    Printer ready signal on.

*/

#ifdef AMIGA

   VV set_page_length(int length)  { tout << TI << length << 't';};
   VV set_line_length(int length)  { tout << TI << length << 'u';};
   VV set_left_offset(int offset)  { tout << TI << offset << 'x';};
   VV set_top_offset(int offset)   { tout << TI << offset << 'y';};
   VV set_raw_events(events)   { tout << TI << events << '{';};
   VV reset_raw_events(events) { tout << TI << events << '}';};
   VV set_cursor_rendition(char *rendition) { tout << TI << rendition << 'p';};

   VV window_status_request()    { tout << "\033[q";};
/*
	~   1	aSKR SPECIAL KEY REPORT (private Amiga Read sequence)
	|   8	aIER INPUT EVENT REPORT (private Amiga Read sequence)
	 r  4	aWBR WINDOW BOUNDS REPORT (private Amiga Read sequence)
*/

#endif


   ANSI_terminal(STD_NS ostream &i_tout = cout,istream  &i_tin = cin):
      terminal(i_tout,i_tin)
   { //reset();
     //set unbuffered mode
     // set no echo mode
#ifdef UNIX
  term = new ANSI_terminal();
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

#ifdef __MSDOS__
//     tout << "\033[=3h";  // Enable color text mode
#endif
   };

   virtual unsigned int read_keyboard() {ANSI_read_keyboard();};

};

#endif