#ifndef CORN_INITGRPH_H
#define CORN_INITGRPH_H

// These functions setup DOS graphics mode

void CORN_exit_graphics(void);
int  CORN_enter_graphics(void);
void CORN_graphics_error(char error_string[],char extra[]);

#endif
//initgrph.h
