/*
 * Program to convert .dat files from the Mitsubishi DJ1000 digital
 * camera to PBM format.
 *
 * Interprets data in the .dat file (the CCD data), compensates the
 * color sensitivity, enhances color saturation, normalizes, sharpens,
 * adjusts gamma, and resamples the image to a 4x3 aspect ratio.
 *
 * Run with option -? to get a list of command line options.
 *
 * Some useful links:
 *   http://www.globaldialog.com/~biggers/html/body_dj-1000.html
 *   http://www.itojun.org/diary/19970730/
 *   http://www.thok.org/rtest/djcam/djcam.html
 *   ftp://ftp.ado.co.jp/pub/dj1000/
 *
 * Author: Bert Bos <bert@w3.org>
 * Created: January 2000
 * Version: $Id: dj1000toppm.c,v 1.3 2000/08/22 12:13:33 bbos Exp $ */

#include <stdio.h>
#ifndef __BORLANDC__
#include <unistd.h>
#endif
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <values.h>
#include <errno.h>
#include <assert.h>

#define VERSION "$Revision: 1.3 $"

#define LINES 246				/* Useful lines in DAT file */
#define COLUMNS 505				/* Useful columns */
#define OUTPUTLINES (LINES - 2)			/* Lines in output */
#define OUTPUTCOLUMNS (4 * (LINES - 2) / 3)	/* Columns in output */
#define INPUTCOLUMNS 512			/* Columns in DAT file */
enum {Red, Green, Blue} _RGB;			/* Index into image array */

typedef unsigned char byte;			/* [0,255] */

#if 0
#define RI 0.299				/* Convert color->gray */
#define GI 0.587				/* ... using NTSC */
#define BI 0.114				/* ... convention */
#define intensity(r, g, b) ((r) * RI + (g) * GI + (b) * BI)
#endif

#define GAMMABITS 14
#define GAMMASIZE (1 << GAMMABITS)		/* Steps in gamma function */

#define HISTBITS 12
#define HISTSIZE (1 << HISTBITS)		/* # steps in histogram */

#define EPS 0.0001

static char *progname;				/* Name of program */
static int verbose_flag = 0;			/* Whether to print info */
static int iterations = 2;			/* Horizontal interpolations */
static float white[3] = {0.78, 1.48, 0.74};	/* White balance daylight */
static float yellow[3] = {0.64, 1.50, 0.86};	/* White balance lightbulb */
static float saturation = 1.3;			/* Adjust color saturation */
static float sharpval = 0.5;			/* Adjust sharpness */
static float gammaval = 0.5;			/* Adjust gamma */
static float normalization = 3;			/* 3% normalization */
static float low = -1.0, high = -1.0;		/* By default not used */


/* syserr -- print s + system error message and exit */
static void syserr(const char *s) {perror(s); exit(1);}


/* min3 -- return minimum of 3 values */
#define min3(a, b, c) ((a)<(b) ? ((a)<(c) ? (a) : (c)) : ((b)<(c) ? (b) : (c)))


/* max3 -- return maximum of 3 values */
#define max3(a, b, c) ((a)>(b) ? ((a)>(c) ? (a) : (c)) : ((b)>(c) ? (b) : (c)))


/* rgb2hsv -- convert RGB to HSV */
static void rgb2hsv(float r, float g, float b, float *hr, float *sr, float *vr)
{
  double h, s, v, max, min, del, rc, gc, bc;

  max = max3(r, g, b);
  min = min3(r, g, b);

  del = max - min;
  v = max;
  s = max == 0.0 ? 0.0 : del / max;

  h = -1;					/* No hue */
  if (s != 0.0) {
    rc = (max - r) / del;
    gc = (max - g) / del;
    bc = (max - b) / del;

    if (r == max) h = bc - gc;
    else if (g == max) h = 2 + rc - bc;
    else /* if (b == max) */ h = 4 + gc - rc;

    h = h * 60;
    if (h < 0) h += 360;
  }

  *hr = h;  *sr = s;  *vr = v;
}


/* hsv2rgb -- convert HSV to RGB */
static void hsv2rgb(float h, float s, float v, float *rr, float *gr, float *br)
{
  int j;
  double rd, gd, bd;
  double f, p, q, t;

  /* convert HSV back to RGB */
  if (h < 0 || s == 0.0) {			/* Gray */
    rd = v;
    gd = v;
    bd = v;
  } else {					/* Not gray */
    if (h == 360.0) h = 0.0;
    h = h / 60.0;
    j = h;					/* = floor(h) */
    f = h - j;
    p = v * (1 - s);
    q = v * (1 - (s * f));
    t = v * (1 - (s * (1 - f)));

    switch (j) {
      case 0:  rd = v;  gd = t;  bd = p;  break; /* Between red and yellow */
      case 1:  rd = q;  gd = v;  bd = p;  break; /* Between yellow and green */
      case 2:  rd = p;  gd = v;  bd = t;  break; /* Between green and cyan */
      case 3:  rd = p;  gd = q;  bd = v;  break; /* Between cyan and blue */
      case 4:  rd = t;  gd = p;  bd = v;  break; /* Between blue and magenta */
      case 5:  rd = v;  gd = p;  bd = q;  break; /* Between magenta and red */
      default: assert(! "Cannot happen"); rd = gd = bd = 0;
    }
  }

  *rr = rd;
  *gr = gd;
  *br = bd;
}


/* convert2rgb -- convert HSV image to RGB image */
static void convert2rgb(float hsv[LINES][COLUMNS][3],
			float rgb[LINES][COLUMNS][3])
{
  int i, j;

  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++)
      hsv2rgb(hsv[i][j][0], hsv[i][j][1], hsv[i][j][2],
	      &rgb[i][j][0], &rgb[i][j][1], &rgb[i][j][2]);
}


/* convert2hsv -- convert RGB image to HSV image */
static void convert2hsv(float rgb[LINES][COLUMNS][3],
			float hsv[LINES][COLUMNS][3])
{
  int i, j;

  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++)
      rgb2hsv(rgb[i][j][0], rgb[i][j][1], rgb[i][j][2],
	      &hsv[i][j][0], &hsv[i][j][1], &hsv[i][j][2]);
}


#ifdef DEBUG
/* dump_gray -- dump an intermediate gray file (for debugging) */
static void dump_gray(float gray[LINES][COLUMNS], int seqno)
{
  int i, j;
  char s[20];
  FILE *tmpfile;

  sprintf(s, "tmp%03d.pgm", seqno);
  tmpfile = fopen(s, "w");
  fprintf(tmpfile, "P5 %d %d 255\n", COLUMNS, LINES);
  for (i = 0; i < LINES; i++)
    for (j = 0; j < COLUMNS; j++)
      putc(gray[i][j] * 255 + 0.5, tmpfile);
  fclose(tmpfile);
}


/* dump -- dump an intermediate image file (for debugging) */
static void dump(float image[LINES][COLUMNS][3], int seqno)
{
  int i, j, k;
  char s[20];
  FILE *tmpfile;

  sprintf(s, "tmp%03d.ppm", seqno);
  tmpfile = fopen(s, "w");
  fprintf(tmpfile, "P6 %d %d 255\n", COLUMNS, LINES);
  for (i = 0; i < LINES; i++)
    for (j = 0; j < COLUMNS; j++) {
      for (k = 0; k < 3; k++) {
	int c = image[i][j][k] * 255 + 0.5;
	putc(c < 0 ? 0 : c > 255 ? 255 : c, tmpfile);
      }
    }
  fclose(tmpfile);
}


/* dumphsv -- dump an intermediate HSV image file (for debugging) */
static void dumphsv(float hsv[LINES][COLUMNS][3], int seqno)
{
  int i, j, c;
  char s[20];
  FILE *tmpfile;
  float r, g, b;

  sprintf(s, "tmp%03d.ppm", seqno);
  tmpfile = fopen(s, "w");
  fprintf(tmpfile, "P6 %d %d 255\n", COLUMNS, LINES);
  for (i = 0; i < LINES; i++)
    for (j = 0; j < COLUMNS; j++) {
      hsv2rgb(hsv[i][j][0], hsv[i][j][1], hsv[i][j][2], &r, &g, &b);
      c = r * 255 + 0.5;
      putc(c < 0 ? 0 : c > 255 ? 255 : c, tmpfile);
      c = g * 255 + 0.5;
      putc(c < 0 ? 0 : c > 255 ? 255 : c, tmpfile);
      c = b * 255 + 0.5;
      putc(c < 0 ? 0 : c > 255 ? 255 : c, tmpfile);
    }
  fclose(tmpfile);
}
#endif


/* fill_gamma_table -- fill a table with precomputed gamma values */
static void fill_gamma_table(float table[GAMMASIZE], float gamma)
{
  unsigned int i;

  for (i = 0; i < GAMMASIZE; i++)
    table[i] = pow((double)i / GAMMASIZE, gamma);
}


/* interpolate_horizontally -- compute luminosity by adding horizontal pairs */
static void interpolate_horizontally(byte ccd[LINES][INPUTCOLUMNS],
				     float gray[LINES][COLUMNS])
{
  /*
   * We assume that the pixels in the CCD array represents this information
   * in patterns of 2x2:
   *
   * (Cyan+Green)   | (Yellow+Magenta)
   * ---------------+-----------------
   * (Cyan+Magenta) | (Yellow+Green)
   *
   * Assuming that Cyan = Blue+Green, Yellow = Red+Green, Magenta = Red+Blue
   * we can get an approximation of luminosity by adding horizontal pairs.
   * Each pair then represents Cyan+Green+Yellow+Magenta = 2R+3G+2B.
   */
     
  unsigned int i, j;

  for (i = 0; i < LINES; i++) {
    gray[i][COLUMNS-1] = ccd[i][COLUMNS-1] / 255.0;
    for (j = 0; j < COLUMNS - 1; j++)
      gray[i][j] = (ccd[i][j] + ccd[i][j+1]) / 255.0 / 2;
  }
#ifdef DEBUG
  dump_gray(gray, 0);
#endif
}


/* interpolate_color -- get colors from the differences between pixels */
static void interpolate_color(byte ccd[LINES][INPUTCOLUMNS],
			      float gray[LINES][COLUMNS],
			      float image[LINES][COLUMNS][3])
{
  /*
   * The CCD contains (we assume) patterns of 2x2 pixels encoding this
   * information:
   *
   * Cyan+Green=   | Yellow+Magenta=
   * 2G+B          | 2R+G+B
   * --------------+----------------
   * Cyan+Magenta= | Yellow+Green=
   * R+G+2B        | R+2G
   *
   * To get each pixel's interpolated RGB, we need to subtract it's
   * neighbours. But if the neighbours have a very different luminosity,
   * we need to compensate for that.
   */

  float a, b, c, R, G, B;
  float min[3] = {2, 2, 2}, max[3] = {-1, -1, -1};
  unsigned int i, j;

  for (i = 1; i < LINES - 1; i++) {
    for (j = 1; j < COLUMNS - 1; j++) {
      /* a = this pixel, b = horiz. neighbours, c = vert. neighbours */
      a = ccd[i][j]/255.0;
      b = (ccd[i][j-1]/255.0 + ccd[i][j+1]/255.0)/2;
      if (gray[i][j-1] + gray[i][j+1] > EPS)
	b *= 2 * gray[i][j]/(gray[i][j-1] + gray[i][j+1]);
      c = (ccd[i-1][j]/255.0 + ccd[i+1][j]/255.0)/2;
      if (gray[i-1][j] + gray[i+1][j] > EPS)
	c *= 2 * gray[i][j]/(gray[i-1][j] + gray[i+1][j]);
      if (! (i & 1)) {				/* Even rows */
	if (! (j & 1)) {			/* Even columns */
	  R = (2 * a - 2 * b + c)/5;
	  G = (c - R)/2;
	  B = b - 2 * G;
	} else {				/* Odd columns */
	  R = (3 * b - a - c)/5;
	  G = 2 * R + a - b;
	  B = a - 2 * G;
	}
      } else {					/* Odd rows */
	if (! (j & 1)) {			/* Even columns */
	  R = (4 * c - 2 * b - a)/5;
	  G = (a - R)/2;
	  B = c - 2 * R - G;
	} else {				/* Odd columns */
	  R = (2 * a - 4 * c + 3 * b)/5;
	  G = (b - R)/2;
	  B = c - 2 * G;
	}
      }
      if (verbose_flag) {
	if (R < min[Red]) min[Red] = R;
	if (G < min[Green]) min[Green] = G;
	if (B < min[Blue]) min[Blue] = B;
	if (R > max[Red]) max[Red] = R;
	if (G > max[Green]) max[Green] = G;
	if (B > max[Blue]) max[Blue] = B;
      }
      image[i][j][Red] = R < 0 ? 0 : R;
      image[i][j][Green] = G < 0 ? 0 : G;
      image[i][j][Blue] = B < 0 ? 0 : B;
    }
  }
  if (verbose_flag) {
    fprintf(stderr,
	    "Interpolated colors: %5.3f-%5.3f, %5.3f-%5.3f, %5.3f-%5.3f\n",
	    (float)min[Red], (float)max[Red],
	    (float)min[Green], (float)max[Green],
	    (float)min[Blue], (float)max[Blue]);
  }
#ifdef DEBUG
  dump(image, 0);
#endif
}


/* balance_white -- do some magic to balance the colors */
static void balance_white(float image[LINES][COLUMNS][3], float factor[3],
			  float gray[LINES][COLUMNS])
{
  unsigned int i, j, k;
  float sum[3] = {0, 0, 0};
  float m;

  /* See if we should use heuristics to determine the white balance */
  if (factor[0] < 0 || factor[1] < 0 || factor[2] < 0) {

    /* Compute energy of each color */
    for (i = 1; i < LINES - 1; i++)
      for (j = 1; j < COLUMNS - 1; j++)
	for (k = 0; k < 3; k++)
	  sum[k] += image[i][j][k];

    /* Calculate factors so that energy in the three colors is the same */
    for (k = 0; k < 3; k++) factor[k] = 1.0 / sum[k];
  }

  /* Normalize */
  m = factor[0] + factor[1] + factor[2];
  for (k = 0; k < 3; k++) factor[k] *= 3.0 / m;

  /* Multiply all values by the given factor */
  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++) {
      for (k = 0; k < 3; k++)
	image[i][j][k] = factor[k] * image[i][j][k];
    }

#if 1
  /* Try to get rid of green where it should be white... */
  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++) {
      float v = max3(image[i][j][0], image[i][j][1], image[i][j][2]);
      if (v >= 0.3) image[i][j][0] = image[i][j][1] = image[i][j][2] = 0.3;
    }
#endif

  if (verbose_flag)
    fprintf(stderr,
	    "Color adjustment:    %5.3f        %5.3f        %5.3f\n",
	    factor[0], factor[1], factor[2]);

#ifdef DEBUG
  dump(image, 1);
#endif /* DEBUG */
}


/* adjust_saturation -- multiply each pixel's saturation */
static void adjust_saturation(float hsv[LINES][COLUMNS][3], float saturation)
{
  unsigned int i, j;

  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++) {
      hsv[i][j][1] *= saturation;
      if (hsv[i][j][1] > 1.0) hsv[i][j][1] = 1.0;
    }
#ifdef DEBUG
  dumphsv(hsv, 2);
#endif
}


/* adjust_gamma -- apply gamma function */
static void adjust_gamma(float image[LINES][COLUMNS][3], float gammaval)
{
  unsigned int i, j, k;
  float gamma[GAMMASIZE];

  if (gammaval == 1.0) return;			/* Nothing to do */
  fill_gamma_table(gamma, gammaval);
  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++)
      for (k = 0; k < 3; k++)
	if (image[i][j][k] >= 1.0)
	  image[i][j][k] = 1.0;
	else if (image[i][j][k] > 0.0)
	  image[i][j][k] = gamma[(int)(image[i][j][k] * GAMMASIZE + 0.5)];
	else
	  image[i][j][k] = 0.0;			/* NaN */
#ifdef DEBUG
  dump(image, 3);
#endif
}


/* adjust_range -- ignore lowest and highest norm percent of pixel values */
static void adjust_range(float hsv[LINES][COLUMNS][3],
			 float norm, float lo, float hi)
{
  unsigned int histogram[HISTSIZE];
  unsigned int i, j;
  unsigned int s, ignored = norm * (LINES - 2) * (COLUMNS - 2) / 100;
  int h;

  if (lo < 0 && hi < 0 && norm < 0) return;	/* Don't do anything */

  /* Make histogram of values, if needed */
  if (lo < 0 || hi < 0) {

    for (i = 0; i < HISTSIZE; i++) histogram[i] = 0;

    for (i = 1; i < LINES - 1; i++)
      for (j = 1; j < COLUMNS - 1; j++) {
	h = hsv[i][j][2] * (HISTSIZE - 1);
	histogram[h]++;
      }
  
    if (lo < 0) {
      /* Find value lo such that norm percent of the pixels is below it */
      for (s = 0, i = 0; i < HISTSIZE && s <= ignored; i++) s += histogram[i];
      lo = (float)i / HISTSIZE;
    }

    if (hi < 0) {
      /* Find value hi such that norm percent of the pixels is above it */
      for (s = 0, i = HISTSIZE-1; i > 0 && s <= ignored; i--) s+= histogram[i];
      hi = (float)i / HISTSIZE;
    }
  }

  if (lo > hi) { float h = lo; lo = hi; hi = h; }

  /* Redistribute all pixels' value such that lo maps to 0 and hi to 1 */
  for (i = 1; i < LINES - 1; i++) {
    for (j = 1; j < COLUMNS - 1; j++) {
      if (hsv[i][j][2] <= lo) hsv[i][j][2] = 0.0;
      else if (hsv[i][j][2] >= hi) hsv[i][j][2] = 1.0;
      else hsv[i][j][2] = (hsv[i][j][2] - lo)/(hi - lo);
    }
  }

#ifdef DEBUG
  dumphsv(hsv, 4);
#endif

  if (verbose_flag) {
    fprintf(stderr, "Normalize range:     %5.3f-%5.3f\n", lo, hi);
  }
}


/* sharpen -- sharpen the image by a factor between 0.0 and 1.0 */
static void sharpen(float hsv[LINES][COLUMNS][3], float sharpval)
{
  unsigned int i, j;
  float val[LINES][COLUMNS], avg;

  if (sharpval <= 0.0) return;			/* Nothing to do */

  /* Make new values in val */
  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++) {
      avg = (hsv[i-1][j-1][2] + hsv[i-1][j][2] + hsv[i-1][j+1][2]
	+ hsv[i][j-1][2] + hsv[i][j][2] + hsv[i][j+1][2]
	+ hsv[i+1][j-1][2] + hsv[i+1][j][2] + hsv[i+1][j+1][2])/9;
      val[i][j] = (hsv[i][j][2] - sharpval * avg)/(1.0 - sharpval);
      if (val[i][j] < 0.0) val[i][j] = 0.0;
      else if (val[i][j] > 1.0) val[i][j] = 1.0;
    }

  /* Copy hsv1 back to hsv */
  for (i = 1; i < LINES - 1; i++)
    for (j = 1; j < COLUMNS - 1; j++)
      hsv[i][j][2] = val[i][j];

#ifdef DEBUG
  dumphsv(hsv, 5);
#endif

  if (verbose_flag) {
    fprintf(stderr, "Sharpened:        %5d%%\n", (int)(sharpval * 100 + 0.5));
  }
}


/* adjust_size -- give the image a 4x3 aspect ratio */
static void adjust_size(float image[LINES][COLUMNS][3])
{
  const int newwidth = 4 * (LINES - 2) / 3;
  const float f = (float)(COLUMNS - 2) / newwidth;
  unsigned int i, j, k;

  for (i = 1; i < LINES - 1; i++) {
    for (j = 1; j <= newwidth; j++) {
      int h = j * f;
      float p = (j * f) - h;
      for (k = 0; k < 3; k++)
	image[i][j][k] = (1.0 - p) * image[i][h][k] + p * image[i][h+1][k];
    }
  }
#ifdef DEBUG
  dump(image, 6);
#endif
}


/* quantize -- reduce to 3 x 8 bits/pixel */
static void quantize(float image[LINES][COLUMNS][3],
		     byte ppm[OUTPUTLINES][OUTPUTCOLUMNS][3])
{
  unsigned int i, j, k;

  for (i = 1; i <= OUTPUTLINES; i++)
    for (j = 1; j <= OUTPUTCOLUMNS; j++)
      for (k = 0; k < 3; k++)
	ppm[i-1][j-1][k] = image[i][j][k] * 255;
}


/* dj1000toppm -- read data in DJ-1000 format and write it in PPM format */
static void dj1000toppm(char *inname, int in, char *outname, int out)
{
  byte ccd[LINES][INPUTCOLUMNS];		/* 8 bits/pixel */
  float gray[LINES][COLUMNS];			/* Horizontal interpolation */
  float image[LINES][COLUMNS][3];		/* Working copy */
  float hsv[LINES][COLUMNS][3];			/* Working copy */
  byte ppm[OUTPUTLINES][OUTPUTCOLUMNS][3], *p;	/* 3 x 8 bits/pixel */
  int n, result;
  char s[30], *q;

  /* Read the image data; no checks, just assume it is DJ-1000 file... */
  if (read(in, ccd, LINES * INPUTCOLUMNS) < 0) syserr(inname);

  /* Extract colors, adjust gamma, saturation, etc. */
  interpolate_horizontally(ccd, gray);
  interpolate_color(ccd, gray, image);
  balance_white(image, white, gray);
  convert2hsv(image, hsv);
  adjust_saturation(hsv, saturation);
  adjust_range(hsv, normalization, low, high);
  sharpen(hsv, sharpval);
  convert2rgb(hsv, image);
  adjust_gamma(image, gammaval);
  adjust_size(image);
  quantize(image, ppm);

  /* Write as a raw PPM file */
  n = sprintf(s, "P6 %d %d 255\n", OUTPUTCOLUMNS, OUTPUTLINES);
  q = s;
  while (n != 0) {
    result = write(out, q, n);
    if (result < n && errno != 0) syserr(outname);
    q += result;
    n -= result;
  }
  n = 3 * OUTPUTLINES * OUTPUTCOLUMNS;
  p = &ppm[0][0][0];
  while (n != 0) {
    result = write(out, p, n);
    if (result < n && errno != 0) syserr(outname);
    p += result;
    n -= result;
  }
}


/* usage -- print usage message and exit with an error */
static void usage(void)
{
  fprintf(stderr, "Usage: %s [options] [dj1000file [ppmfile]]\n", progname);
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "  -V         print \"%s\" and exit\n", VERSION);
  fprintf(stderr, "  -v         verbose, print info about the calculations\n");
  fprintf(stderr, "  -?         this help text\n");
  fprintf(stderr, "  -i         indoor (artificial light, equiv. to -r %g -g %g -b %g)\n", yellow[Red], yellow[Green], yellow[Blue]);
  fprintf(stderr, "  -I number  horizontal interpolations before extracting colors [%d]\n", iterations);
  fprintf(stderr, "  -r number  relative multiplier for red, <0 = use heuristic [%g]\n", white[Red]);
  fprintf(stderr, "  -g number  relative multiplier for green, <0 = use heuristic [%g]\n", white[Green]);
  fprintf(stderr, "  -b number  relative multiplier for blue, <0 = use heuristic [%g]\n", white[Blue]);
  fprintf(stderr, "  -s number  saturation [%f]\n", saturation);
  fprintf(stderr, "  -S number  sharpen (0.0-1.0) [%g]\n", sharpval);
  fprintf(stderr, "  -G number  gamma correction [%g]\n", gammaval);
  fprintf(stderr, "  -n number  normalize, discard lightest & darkest percent [%g]\n", normalization);
  fprintf(stderr, "  -l number  discard values lower than this, <0 = not used\n");
  fprintf(stderr, "  -h number  discard values higher than this, <0 = not used\n");
  exit(2);
}


int main(int argc, char *argv[])
{
  int k, c, infile, outfile;
  char *inname, *outname;

  progname = argv[0];
#ifdef __BORLANDC__
   inname = argv[1];
   outname= argv[2];
    if ((infile = open(inname, O_RDONLY)) < 0) syserr(inname);
    if ((outfile = creat(outname, 0666)) < 0) syserr(outname);
#else
  while ((c = getopt(argc, argv, "VviI:r:g:b:s:S:G:n:l:h:")) != -1) {
    switch (c) {
      case 'V': printf("%s\n", VERSION); exit(0); break;
      case 'v': verbose_flag = 1; break;
      case 'i': for (k = 0; k < 3; k++) white[k] = yellow[k]; break;
      case 'I': iterations = atoi(optarg); break;
      case 'r': white[Red] = atof(optarg); break;
      case 'g': white[Green] = atof(optarg); break;
      case 'b': white[Blue] = atof(optarg); break;
      case 's': saturation = atof(optarg); break;
      case 'S': sharpval = atof(optarg); break;
      case 'G': gammaval = atof(optarg); break;
      case 'n': normalization = atof(optarg); break;
      case 'l': low = atof(optarg); break;
      case 'h': high = atof(optarg); break;
      default: usage();
    }
  }
  if (optind + 2 < argc) usage();
  if (optind >= argc) {
    inname = "<stdin>";
    infile = 0;
  } else {
    inname = argv[optind];
    if ((infile = open(inname, O_RDONLY)) < 0) syserr(inname);
  }
  optind++;
  if (optind >= argc) {
    outname = "<stdout>";
    outfile = 1;
  } else {
    outname = argv[optind];
    if ((outfile = creat(outname, 0666)) < 0) syserr(outname);
  }
#endif
  dj1000toppm(inname, infile, outname, outfile);

  if (close(infile) < 0) syserr(inname);
  if (close(outfile) < 0) syserr(outname);
  return 0;}

