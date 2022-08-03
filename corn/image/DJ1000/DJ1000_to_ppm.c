/*
 * Convert Mitsubishi dj1000's file into ppm format.
 * You'll need to resize the output into proper aspect ratio. (x:y = 4:3)
 *
 * NOTE:
 * This code is fairly incomplete due to the following reasons:
 * - dj1000 uses Sanyo CCD.  The code is for Sony CCD.
 * - color calcuration method is incompatible.
 *
 * by Jun-ichiro itojun Itoh <itojun@itojun@itojun.org>
 * Freely redistributable.  Absolutely no warranty.
 * $Id: dj1000toppm.c,v 1.2 1997/08/26 04:34:34 itojun Exp $
 *
 * based on...
 */
/*
 *
 * Converts CMT file of Chinon ES-1000 or IMG file of LXDC to PPM file.
 *
 *	written by YOSHIDA Hideki <hideki@yk.rim.or.jp>
 *	In public domain; you can do whatever you want to this program
 *	as long as you admit that the original code is written by me.
 *
 * Id: cmttoppm.c,v 1.10 1996/09/28 03:01:57 hideki Exp hideki 
 *
 */

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __BORLANDC__
// RLN apparently a Unix library use for handling command line args
#include <unistd.h>
#endif
#include <sys/types.h>

/* initial values are for high mode */
static int columns = 512;
static int lines = 243;
static int left_margin = 2;
static int right_margin = 10;
static int top_margin = 1;
static int bottom_margin = 1;

#define COLUMNS		(columns)
#define LINES		(lines)
#define LEFT_MARGIN	(left_margin)
#define RIGHT_MARGIN	(right_margin)
#define TOP_MARGIN	(top_margin)
#define BOTTOM_MARGIN	(bottom_margin)
#define NET_COLUMNS	(COLUMNS - LEFT_MARGIN - RIGHT_MARGIN)
#define NET_LINES	(LINES - TOP_MARGIN - BOTTOM_MARGIN)
#define NET_PIXELS	(NET_COLUMNS * NET_LINES)

#define SCALE 64
#define SMAX (256 * SCALE - 1)
#define HORIZONTAL_INTERPOLATIONS 3
#define HISTOGRAM_STEPS 4096

#define RFACTOR 0.64
#define GFACTOR 0.58
#define BFACTOR 1.00
#define RINTENSITY 0.476
#define GINTENSITY 0.299
#define BINTENSITY 0.175

#define SATURATION 1.5
#define NORM_PERCENTAGE 3
#define GAMMA 0.5

const char *progname;
int verbose_flag = 0;
int low_i = -1, high_i = -1;
float gamma_value = GAMMA;
float saturation = SATURATION;
float rfactor = RFACTOR, gfactor = GFACTOR, bfactor = BFACTOR;
int norm_percentage = NORM_PERCENTAGE;

void check_dj1000_file(int infd)
{
  return 1;
}

void set_initial_interpolation(const unsigned char *ccd,
			       short *horizontal_interpolation)
{
  int column, line;
  for (line = 0; line < LINES; line++) {
    horizontal_interpolation[line * COLUMNS + LEFT_MARGIN] =
      ccd[line * COLUMNS + LEFT_MARGIN + 1] * SCALE;
    horizontal_interpolation[line * COLUMNS + COLUMNS - RIGHT_MARGIN - 1] =
      ccd[line * COLUMNS + COLUMNS - RIGHT_MARGIN - 2] * SCALE;
    for (column = LEFT_MARGIN + 1; column < COLUMNS - RIGHT_MARGIN - 1;
	 column++) {
      horizontal_interpolation[line * COLUMNS + column] =
	(ccd[line * COLUMNS + column - 1] + ccd[line * COLUMNS + column + 1]) * (SCALE / 2);
    }
  }
}

void interpolate_horizontally(const unsigned char *ccd,
			      short *horizontal_interpolation)
{
  int column, line, i, initial_column;
  for (line = TOP_MARGIN - 1; line < LINES - BOTTOM_MARGIN + 1; line++) {
    for (i = 0; i < HORIZONTAL_INTERPOLATIONS; i++) {
      for (initial_column = LEFT_MARGIN + 1; initial_column <= LEFT_MARGIN + 2;
	   initial_column++) {
	for (column = initial_column; column < COLUMNS - RIGHT_MARGIN - 1;
	     column += 2) {
	  horizontal_interpolation[line * COLUMNS + column] =
	    ((float)ccd[line * COLUMNS + column - 1] /
	     horizontal_interpolation[line * COLUMNS + column - 1] +
	     (float)ccd[line * COLUMNS + column + 1] /
	     horizontal_interpolation[line * COLUMNS + column + 1]) *
	       ccd[line * COLUMNS + column] * (SCALE * SCALE / 2) + 0.5;
	}
      }
    }
  }
}

void
interpolate_vertically(const unsigned char *ccd,
		       const short *horizontal_interpolation,
		       short *red, short *green, short *blue)
{
  int column, line;
  for (line = TOP_MARGIN; line < LINES - BOTTOM_MARGIN; line++) {
    for (column = LEFT_MARGIN; column < COLUMNS - RIGHT_MARGIN; column++) {
      int r2gb, g2b, rg2, rgb2, r, g, b;
      int this_ccd = ccd[line * COLUMNS + column] * SCALE;
      int up_ccd   = ccd[(line - 1) * COLUMNS + column] * SCALE;
      int down_ccd = ccd[(line + 1) * COLUMNS + column] * SCALE;
      int this_horizontal_interpolation =
	horizontal_interpolation[line * COLUMNS + column];
      int this_intensity = this_ccd + this_horizontal_interpolation;
      int up_intensity = horizontal_interpolation[(line - 1) * COLUMNS + column] + up_ccd;
      int down_intensity = horizontal_interpolation[(line + 1) * COLUMNS + column] + down_ccd;
      int this_vertical_interpolation;
      if (line == TOP_MARGIN) {
	this_vertical_interpolation =
	  (float)down_ccd / down_intensity * this_intensity + 0.5;
      } else if (line == LINES - BOTTOM_MARGIN - 1) {
	this_vertical_interpolation =
	  (float)up_ccd / up_intensity * this_intensity + 0.5;
      } else {
	this_vertical_interpolation =
	  ((float)up_ccd / up_intensity + (float)down_ccd / down_intensity) *
	    this_intensity / 2.0 + 0.5;
      }
      if (!(line & 1)) {
	if (!(column & 1)) {
	  r2gb = this_ccd;
	  g2b = this_horizontal_interpolation;
	  rg2 = this_vertical_interpolation;
	  r = (2 * (r2gb - g2b) + rg2) / 5;
	  g = (rg2 - r) / 2;
	  b = g2b - 2 * g;
	} else {
	  g2b = this_ccd;
	  r2gb = this_horizontal_interpolation;
	  rgb2 = this_vertical_interpolation;
	  r = (3 * r2gb - g2b - rgb2) / 5;
	  g = 2 * r - r2gb + g2b;
	  b = g2b - 2 * g;
	}
      } else {
	if (!(column & 1)) {
	  rg2 = this_ccd;
	  rgb2 = this_horizontal_interpolation;
	  r2gb = this_vertical_interpolation;
	  b = (3 * rgb2 - r2gb - rg2) / 5;
	  g = (rgb2 - r2gb + rg2 - b) / 2;
	  r = rg2 - 2 * g;
	} else {
	  rgb2 = this_ccd;
	  rg2 = this_horizontal_interpolation;
	  g2b = this_vertical_interpolation;
	  b = (g2b - 2 * (rg2 - rgb2)) / 5;
	  g = (g2b - b) / 2;
	  r = rg2 - 2 * g;
	}
      }
      if (r < 0) r = 0;
      if (g < 0) g = 0;
      if (b < 0) b = 0;
      red  [line * COLUMNS + column] = r;
      green[line * COLUMNS + column] = g;
      blue [line * COLUMNS + column] = b;
    }
  }
}

void adjust_color_and_saturation(short *red, short *green, short *blue)
{
  int line, column;
  int r_min = SMAX, g_min = SMAX, b_min = SMAX;
  int r_max =    0, g_max =    0, b_max =    0;
  int r_sum =    0, g_sum =    0, b_sum =    0;
  float sqr_saturation = sqrt(saturation);
  for (line = TOP_MARGIN; line < LINES - BOTTOM_MARGIN; line++) {
    for (column = LEFT_MARGIN; column < COLUMNS - RIGHT_MARGIN; column++) {
      float r = red  [line * COLUMNS + column] * rfactor;
      float g = green[line * COLUMNS + column] * gfactor;
      float b = blue [line * COLUMNS + column] * bfactor;
      if (saturation != 1.0) {
	float *min, *mid, *max, new_intensity;
	float intensity = r * RINTENSITY + g * GINTENSITY + b * BINTENSITY;
	if (r > g) {
	  if (r > b) {
	    max = &r;
	    if (g > b) {
	      min = &b;
	      mid = &g;
	    } else {
	      min = &g;
	      mid = &b;
	    }
	  } else {
	    min = &g;
	    mid = &r;
	    max = &b;
	  }
	} else {
	  if (g > b) {
	    max = &g;
	    if (r > b) {
	      min = &b;
	      mid = &r;
	    } else {
	      min = &r;
	      mid = &b;
	    }
	  } else {
	    min = &r;
	    mid = &g;
	    max = &b;
	  }
	}
	*mid = *min + sqr_saturation * (*mid - *min);
	*max = *min + saturation * (*max - *min);
	new_intensity = r * RINTENSITY + g * GINTENSITY + b * BINTENSITY;
	r *= intensity / new_intensity;
	g *= intensity / new_intensity;
	b *= intensity / new_intensity;
      }
      r += 0.5;
      g += 0.5;
      b += 0.5;
      if (r_min > r) r_min = r;
      if (g_min > g) g_min = g;
      if (b_min > b) b_min = b;
      if (r_max < r) r_max = r;
      if (g_max < g) g_max = g;
      if (b_max < b) b_max = b;
      r_sum += r;
      g_sum += g;
      b_sum += b;
      red  [line * COLUMNS + column] = r;
      green[line * COLUMNS + column] = g;
      blue [line * COLUMNS + column] = b;
    }
  }
}

int min3(int x, int y, int z)
{
  return (x < y ? (x < z ? x : z) : (y < z ? y : z));
}

int max3(int x, int y, int z)
{
  return (x > y ? (x > z ? x : z) : (y > z ? y : z));
}

void determine_limits(const short *red, const short *green, const short *blue,
		      int *low_i_ptr, int *high_i_ptr)
{
  unsigned int histogram[HISTOGRAM_STEPS + 1];
  int column, line, i, s;
  int low_i = *low_i_ptr, high_i = *high_i_ptr;
  int max_i = 0;
  for (line = TOP_MARGIN; line < LINES - BOTTOM_MARGIN; line++) {
    for (column = LEFT_MARGIN; column < COLUMNS - RIGHT_MARGIN; column++) {
      i = max3(red[line * COLUMNS + column], green[line * COLUMNS + column], blue[line * COLUMNS + column]);
      if (i > max_i) max_i = i;
    }
  }
  if (low_i == -1) {
    for (i = 0; i <= HISTOGRAM_STEPS; i++) histogram[i] = 0;
    for (line = TOP_MARGIN; line < LINES - BOTTOM_MARGIN; line++) {
      for (column = LEFT_MARGIN; column < COLUMNS - RIGHT_MARGIN; column++) {
	i = min3(red[line * COLUMNS + column], green[line * COLUMNS + column], blue[line * COLUMNS + column]);
	histogram[i * HISTOGRAM_STEPS / max_i]++;
      }
    }
    for (low_i = 0, s = 0;
	 low_i <= HISTOGRAM_STEPS && s < NET_PIXELS * norm_percentage / 100;
	 low_i++) {
      s += histogram[low_i];
    }
    low_i = (low_i * max_i + HISTOGRAM_STEPS / 2) / HISTOGRAM_STEPS;
    *low_i_ptr = low_i;
  }
  if (high_i == -1) {
    for (i = 0; i <= HISTOGRAM_STEPS; i++) histogram[i] = 0;
    for (line = TOP_MARGIN; line < LINES - BOTTOM_MARGIN; line++) {
      for (column = LEFT_MARGIN; column < COLUMNS - RIGHT_MARGIN; column++) {
	i = max3(red[line * COLUMNS + column], green[line * COLUMNS + column], blue [line * COLUMNS + column]);
	histogram[i * HISTOGRAM_STEPS / max_i]++;
      }
    }
    for (high_i = HISTOGRAM_STEPS, s = 0;
	 high_i >= 0 && s < NET_PIXELS * norm_percentage / 100; high_i--) {
      s += histogram[high_i];
    }
    high_i = (high_i * max_i + HISTOGRAM_STEPS / 2) / HISTOGRAM_STEPS;
    *high_i_ptr = high_i;
  }
  fprintf(stderr, "low_i = %d, high_i = %d\n", low_i, high_i);
}

unsigned char *make_gamma_table(int range)
{
  int i;
  double factor = pow(256.0, 1.0 / gamma_value) / range;
  unsigned char *gamma_table;
  if ((gamma_table = malloc(range * sizeof(unsigned char))) == NULL) {
    fprintf(stderr, "%s: can't allocate memory for gamma table\n", progname);
    exit(1);
  }
  for (i = 0; i < range; i++) {
    int g = pow((double)i * factor, gamma_value) + 0.5;
#ifdef DEBUG
    fprintf(stderr, "gamma[%4d] = %3d\n", i, g);
#endif
    if (g > 255) g = 255;
    gamma_table[i] = g;
  }
  return gamma_table;
}

int lookup_gamma_table(int i, int low_i, int high_i,
		       const unsigned char gamma_table[])
{
  if (i <= low_i)  return   0;
  if (i >= high_i) return 255;
  return gamma_table[i - low_i];
}

void output_rgb(const short *red, const short *green, const short *blue,
		int low_i, int high_i, FILE *outfp)
{
  int r_min = 255, g_min = 255, b_min = 255;
  int r_max =   0, g_max =   0, b_max =   0;
  int r_sum =   0, g_sum =   0, b_sum =   0;
  int column, line;
  unsigned char *gamma_table = make_gamma_table(high_i - low_i);

  for (line = TOP_MARGIN; line < LINES - BOTTOM_MARGIN; line++) {
    for (column = LEFT_MARGIN; column < COLUMNS - RIGHT_MARGIN; column++) {
      int r =
	lookup_gamma_table(red  [line * COLUMNS + column], low_i, high_i, gamma_table);
      int g =
	lookup_gamma_table(green[line * COLUMNS + column], low_i, high_i, gamma_table);
      int b =
	lookup_gamma_table(blue [line * COLUMNS + column], low_i, high_i, gamma_table);
      if (r > 255) r = 255; else if (r < 0) r = 0;
      if (g > 255) g = 255; else if (g < 0) g = 0;
      if (b > 255) b = 255; else if (b < 0) b = 0;
      putc(r, outfp);
      putc(g, outfp);
      putc(b, outfp);
      if (r_min > r) r_min = r;
      if (g_min > g) g_min = g;
      if (b_min > b) b_min = b;
      if (r_max < r) r_max = r;
      if (g_max < g) g_max = g;
      if (b_max < b) b_max = b;
      r_sum += r;
      g_sum += g;
      b_sum += b;
    }
  }
  free(gamma_table);
  fprintf(stderr, "r: min = %d, max = %d, ave = %d\n",
	  r_min, r_max, r_sum / NET_PIXELS);
  fprintf(stderr, "g: min = %d, max = %d, ave = %d\n",
	  g_min, g_max, g_sum / NET_PIXELS);
  fprintf(stderr, "b: min = %d, max = %d, ave = %d\n",
	  b_min, b_max, b_sum / NET_PIXELS);
}

void dj1000toppm(int infd, FILE *outfp)
{
  int pgm_p = 0;
  unsigned char *ccd;
  short *horizontal_interpolation;
  short *red, *green, *blue;

  check_dj1000_file(infd);

  /* allocate */
  ccd = (unsigned char *)malloc(LINES * COLUMNS * sizeof(unsigned char));
  horizontal_interpolation = (short *)malloc(LINES * COLUMNS * sizeof(short));
  red = (short *)malloc(LINES * COLUMNS * sizeof(short));
  green = (short *)malloc(LINES * COLUMNS * sizeof(short));
  blue = (short *)malloc(LINES * COLUMNS * sizeof(short));
  if (ccd && horizontal_interpolation && red && green && blue) { 
    /* okey */
  } else {
    fprintf(stderr, "%s: no core left\n", progname);
    exit(1);
  }

  read(infd, ccd, COLUMNS * LINES);

  /* Decode raw CCD data to RGB */
  set_initial_interpolation(ccd, horizontal_interpolation);
  interpolate_horizontally(ccd, horizontal_interpolation);
  interpolate_vertically(ccd, horizontal_interpolation, red, green, blue);

  adjust_color_and_saturation(red, green, blue);

  /* Determine lower and upper limit using histogram */
  if (low_i == -1 || high_i == -1) {
    determine_limits(red, green, blue, &low_i, &high_i);
  }

  /* Output PPM file */
  fprintf(outfp, "P%d\n%d %d\n%d\n", pgm_p ? 5 : 6,
	  NET_COLUMNS, NET_LINES, 255);
  output_rgb(red, green, blue, low_i, high_i, outfp);
}

void usage(void)
{
  fprintf(stderr, "usage: %s [options] [dj1000_file [ppm_file]]\n", progname);
  exit(1);
}

void main(int argc, char *const *argv)
{
  int infd, c;
  FILE *outfp;
  progname = argv[0];
  while ((c = getopt(argc, argv, "vr:g:b:s:G:n:l:h:")) != -1) {
    switch (c) {
    case 'v':
      verbose_flag = 1;
      break;
#ifndef __BORLANDC__
// RLN optarg apparently a Unix library constant use for handling command line args
    case 'r':
      rfactor = atof(optarg);
      break;
    case 'g':
      gfactor = atof(optarg);
      break;
    case 'b':
      bfactor = atof(optarg);
      break;
    case 's':
      saturation = atof(optarg);
      break;
    case 'G':
      gamma_value = atof(optarg);
      break;
    case 'n':
      norm_percentage = atoi(optarg);
      break;
    case 'l':
      low_i = atoi(optarg);
      break;
    case 'h':
      high_i = atoi(optarg);
      break;
#endif
    default:
      usage();
    }
  }
#ifndef __BORLANDC__
    if ((infd = open(argv[1], O_RDONLY)) < 0) {
      perror(argv[1]);
      exit(1);
    }
    if ((outfp = fopen(argv[2], "wb")) == NULL) {
      perror(argv[2]);
      exit(1);

#else
// RLN apparently a Unix library use for handling command line args
  if (optind + 2 < argc) usage();
  if (optind >= argc) {
    infd = 0;
  } else
  {
    if ((infd = open(argv[optind], O_RDONLY)) < 0) {
      perror(argv[optind]);
      exit(1);
    }
  }
  optind++;

  if (optind >= argc) {
    outfp = stdout;
  } else {
    if ((outfp = fopen(argv[optind], "wb")) == NULL) {
      perror(argv[optind]);
      exit(1);
    }
  }
#endif

  dj1000toppm(infd, outfp);
  fclose(outfp);
}
