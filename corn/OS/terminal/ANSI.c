#include <rlib/rui/terminal/ansi.h>
#include <stdio.h>

#ifndef AMIGADOS
/* If this is amiga DOS then we use GetCharater defined in amigacon */
#define GetCharacter getchar
#ifdef __MSDOS__
#include <conio.h>
#define GetCharacter getch
#endif
#endif

struct ANSI_function_key_layout 
{
   char sequence[6];
   int  key_code;
};

/* The following list must be sorted by sequence */

struct ANSI_function_key_layout ANSI_function_keys[] =
{
   {"\033OA",TERM_KEY_UP}
  ,{"\033OB",TERM_KEY_DOWN}
  ,{"\033OC",TERM_KEY_RIGHT}
  ,{"\033OD",TERM_KEY_LEFT}
  ,{"\033OM",TERM_KP_ENTER}
  ,{"\033OP",TERM_KP_PF1}
  ,{"\033OQ",TERM_KP_PF2}
  ,{"\033OR",TERM_KP_PF3}
                               /*,{"\033OS",TERM_KEY_SHIFT_DOWN} */
  ,{"\033OS",TERM_KP_PF4}
  ,{"\033OT",TERM_KEY_SHIFT_UP}
  ,{"\033Ol",TERM_KP_COMMA}
  ,{"\033Om",TERM_KP_MINUS}
  ,{"\033On",TERM_KP_PERIOD}
  ,{"\033Op",TERM_KP_0}
  ,{"\033Oq",TERM_KP_1}
  ,{"\033Or",TERM_KP_2}
  ,{"\033Os",TERM_KP_3}
  ,{"\033Ot",TERM_KP_4}
  ,{"\033Ou",TERM_KP_5}
  ,{"\033Ov",TERM_KP_6}
  ,{"\033Ow",TERM_KP_7}
  ,{"\033Ox",TERM_KP_8}
  ,{"\033Oy",TERM_KP_9}
#ifdef AMIGADOS
  ,{"\033[ @",TERM_KEY_SHIFT_LEFT} /* Amiga */
  ,{"\033[ A",TERM_KEY_SHIFT_RIGHT}/* Amiga */
  ,{"\033[0~",TERM_KEY_F1}             /* Amiga */
  ,{"\033[10~",TERM_KEY_SHIFT_F1}     /* Amiga */
  ,{"\033[11~",TERM_KEY_SHIFT_F2}     /* Amiga */
  ,{"\033[12~",TERM_KEY_SHIFT_F3}     /* Amiga */
  ,{"\033[13~",TERM_KEY_SHIFT_F4}     /* Amiga */
  ,{"\033[14~",TERM_KEY_SHIFT_F5}     /* Amiga */
  ,{"\033[15~",TERM_KEY_SHIFT_F6}     /* Amiga */
  ,{"\033[16~",TERM_KEY_SHIFT_F7}     /* Amiga */
  ,{"\033[17~",TERM_KEY_SHIFT_F8}     /* Amiga */
  ,{"\033[18~",TERM_KEY_SHIFT_F9}     /* Amiga */
  ,{"\033[19~",TERM_KEY_SHIFT_F10}     /* Amiga */
  ,{"\033[1~",TERM_KEY_F2}   /* Amiga */
  ,{"\033[2~",TERM_KEY_F3}   /* Amiga */
  ,{"\033[3~",TERM_KEY_F4}   /* Amiga */
  ,{"\033[4~",TERM_KEY_F5}   /* Amiga */
  ,{"\033[5~",TERM_KEY_F6}   /* Amiga */
  ,{"\033[6~",TERM_KEY_F7}   /* Amiga */
  ,{"\033[7~",TERM_KEY_F8}   /* Amiga */
  ,{"\033[8~",TERM_KEY_F9}   /* Amiga */
  ,{"\033[9~",TERM_KEY_F10}  /* Amiga */
  ,{"\033[?~",TERM_KEY_HELP}  /* Amiga */
#endif /* AMIGADOS */
  ,{"\033[A",TERM_KEY_UP}
  ,{"\033[B",TERM_KEY_DOWN}
  ,{"\033[C",TERM_KEY_RIGHT}
  ,{"\033[D",TERM_KEY_LEFT}
#ifdef AMIGADOS
  ,{"\033[S",TERM_KEY_SHIFT_DOWN}       /* Amiga */
  ,{"\033[T",TERM_KEY_SHIFT_UP}         /* Amiga */
#endif /* AMIGADOS */
};

#ifdef AMIGADOS
extern long raw_in;
#endif

/* Reads char from keyboard buffer returns uniquely identifying keycode */
int ANSI_read_keyboard()
{
   int inkey;
   int found = 0;
   int index = 0;
   int pos = 0;

   /* Enter C-Break / Canon mode */

   inkey = GetCharacter();

   if ((inkey == 0x9b) || (inkey == 27))  /* Escape sequence */
   { 
     if (inkey == 0x9b)  
     {
       while (ANSI_function_keys[index].sequence[0] < 27)
         index += 1;
       while (ANSI_function_keys[index].sequence[1] < '[')
         index += 1;
       pos = 1; 
     };
     while (!found)
     { 
       if (pos)
         inkey = GetCharacter();
       else
#ifdef AMIGADOS
         /* We time out on the escape if not an escape sequence 
            and return a lone escape */
         if (!(inkey = WaitForChar(raw_in,500L))) return(27);
#else
         inkey = GetCharacter();
#endif
       pos += 1;
       while (ANSI_function_keys[index].sequence[pos] < inkey)
         index += 1;
       if ( ANSI_function_keys[index].sequence[pos] > inkey)
          return(0);
       if ((inkey == ANSI_function_keys[index].sequence[pos]) &&
           (ANSI_function_keys[index].sequence[pos+1] == 0))
          return(ANSI_function_keys[index].key_code);
     };
   }
   else
   {
      if (inkey == '\n') inkey = 13;
      return((int) inkey);
   }
};
