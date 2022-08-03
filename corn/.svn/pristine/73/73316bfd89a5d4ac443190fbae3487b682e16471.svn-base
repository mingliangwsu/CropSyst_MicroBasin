/* port of panelhack.pl for speed (on a 486/50, I need it...) */
/* Copyright 1998 Mark W. Eichin, The Herd Of Kittens */

/* takes a foo.dat as argv, writes a foo.p1..p4 */
/* exact match to perl script (except for better signature check) for
   simple validation */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>		/* for malloc */

char p3hdr[] = "P3\n256 124\n256\n";
char djext[] = ".dat";
char pext[] = ".p1";
char sigext[] = ".psig";

void die(char *s) {
  fprintf(stderr, "error: %s\n", s);
  exit(1);
}

void pdie(char *text, char *arg) {
  fprintf(stderr, "error: %s ", text);
  perror(arg);
  exit(1);
}

char decs[256][5];		/* "255 \0" */
void makedecs() {
  int i;
  for (i=0; i<256; i++) {
    sprintf(decs[i], "%d ", i);
  }
}

void putpixel(FILE* F, int value) {
  fputs(decs[value], F);
  fputs(decs[value], F);
  fputs(decs[value], F);
}

#ifdef ATTEMPT_COLOR_HACK
void putpixel3(FILE* F, int r, int g, int b) {
  fprintf(F, "%d ", r);
  fprintf(F, "%d ", g);
  fprintf(F, "%d ", b);
}
#endif

int main(int argc, char **argv) {
    char *thisname;
    makedecs();
    if (argc <= 1
	|| (argc == 2
	    && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")))) {
	fprintf(stderr, "Usage: %s filename.dat\n"
		"Generates filename.p1..p4 and filename.psig\n"
		"(experimental tool for DJ-1000 camera. <eichin@thok.org>\n",
		argv[0]);
	exit(1);
    }
    while(thisname = *(++argv)) {
	int i, lnum;
	char *namebase, *nameout[4], *namesig;
	FILE *IN, *OUT[4], *SIG;
	
	namebase = malloc(strlen(thisname)+1);
	if(!namebase) die("malloc namebase");
	strcpy(namebase, thisname);
	if (!strcasecmp(&namebase[strlen(namebase)-strlen(djext)], djext)) {
	    namebase[strlen(namebase)-strlen(djext)] = 0;
	}
	printf("Cooking %s\n", thisname);
	IN = fopen(thisname, "rb");
	if(!IN) pdie("fopen/read", thisname);
	for (i=0; i<4; i++) {
	    nameout[i] = malloc(strlen(namebase)+strlen(pext)+1);
	    if (!nameout[i]) die("malloc nameout");
	    strcpy(nameout[i], namebase);
	    strcat(nameout[i], pext);
	    nameout[i][strlen(nameout[i])-1] += i;
	    OUT[i] = fopen(nameout[i], "wb");
	    if (!OUT[i]) pdie("fopen/write", nameout[i]);
	}
	namesig = malloc(strlen(namebase)+strlen(sigext)+1);
	if (!namesig) die("malloc namesig");
	strcpy(namesig, namebase);
	strcat(namesig, sigext);
	SIG = fopen(namesig, "wb");
	if (!SIG) pdie("fopen/write", namesig);

	for (i=0; i<4; i++) {
	    fprintf(OUT[i], p3hdr);
	}

	lnum = 0;
	/* while(!feof(IN))  doesn't really work... */
	while(lnum < 255) {
	    unsigned char thisline[512];
	    size_t st;
	    st = fread(thisline, 1, 512, IN);
	    if (st != 512) die("short read odd line");
	    lnum++;
	    if (lnum > 248) {
	      unsigned char const sigbase[] =
		{ 196, 178, 227, 34, 0, 1, 0, 1, 1 };
	      st = fread(thisline, 1, 512, IN);
	      if (st != 512) die("short read extra line");
	      lnum++;
	      if (lnum == 252) {
		if (memcmp(sigbase, thisline, sizeof sigbase)) {
		  fprintf(stderr, "SIGNATURE MATCH FAILED: "
			  "%d %d %d %d %d %d %d %d %d",
			  thisline[0],
			  thisline[1],
			  thisline[2],
			  thisline[3],
			  thisline[4],
			  thisline[5],
			  thisline[6],
			  thisline[7],
			  thisline[8]);
		  die("bad signature");
		}
		fprintf(SIG, "%d %d %d %d\n",
			thisline[9],
			thisline[10],
			thisline[11],
			thisline[12]);
		/* could just do "break" for that case, oh well... */
	      }
	      continue;
	    }
	    i = 0;
	    while(i<sizeof thisline) {
	      putpixel(OUT[0], thisline[i]);
	      i++;
#ifdef ATTEMPT_COLOR_HACK
	      putpixel3(OUT[1], 
			(-3.88)*thisline[i],
			(2.41)*thisline[i],
			(0.26)*thisline[i]);
#else
	      putpixel(OUT[1], thisline[i]);
#endif
	      i++;
	    }
	    fputc('\n', OUT[0]);
	    fputc('\n', OUT[1]);

	    st = fread(thisline, 1, 512, IN);
	    if (st != 512) die("short read even line");
	    lnum++;
	    i = 0;
	    while(i<sizeof thisline) {
#ifdef ATTEMPT_COLOR_HACK
	      putpixel3(OUT[2], 
			(0.90)*thisline[i],
			(1.33)*thisline[i],
			(-1.48)*thisline[i]);
#else
	      putpixel(OUT[2], thisline[i]);
#endif
	      i++;
#ifdef ATTEMPT_COLOR_HACK
	      putpixel3(OUT[3], 
			(2.08)*thisline[i],
			(-1.59)*thisline[i],
			(1.09)*thisline[i]);
#else
	      putpixel(OUT[3], thisline[i]);
#endif
	      i++;
	    }
	    fputc('\n', OUT[2]);
	    fputc('\n', OUT[3]);
	}
    }
    return 0;
}



