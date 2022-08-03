#ifndef CORN_NUMERIC_H
#define CORN_NUMERIC_H
/*140118
//#ifdef CHECK_USED
#include <corn/std/std_iostream.h>
//#endif
*/
#include <ostream>
/* Some numerical analysis functions */
//_____________________________________________________________________________
#ifdef BIGMATRIX
extern void mat_file_set(FILE *matfile,int i, int j, int n,float v);
extern float mat_file_get(FILE *matfile,int i, int j,int n);
#endif
//_____________________________________________________________________________
float *vector
#if defined(__STDC__) || defined(__cplusplus)
(int nl,int nh);
#else
(int,int);
#endif
//_____________________________________________________________________________
void free_vector
#if defined(__STDC__) || defined(__cplusplus)
(float *v,int nl,int nh);
#else
(float *,int,int);
#endif
//_____________________________________________________________________________
extern float **matrix
#if defined(__STDC__) || defined(__cplusplus)
(int nrl,int nrh,int ncl,int nch);
#else
(int,int,int,int);
#endif
//_____________________________________________________________________________
extern void free_matrix
#if defined(__STDC__) || defined(__cplusplus)
(float **m,int nrl, int nrh, int ncl, int nch);
#else
(float **,int,int,int,int);
#endif
//_____________________________________________________________________________
void squarematmult
#if defined(__STDC__) || defined(__cplusplus)
(float **x,float **y,float **z,int n);
#else
(float **,float **,float **,int);
#endif
//_____________________________________________________________________________
extern void squarematminus
#if defined(__STDC__) || defined(__cplusplus)
(float **x, float **y, float **z, int n);
#else
/* (x,y,z,n) */
(float **,float **,float **,int);
#endif
//_____________________________________________________________________________
extern void inverse
#if defined(__STDC__) || defined(__cplusplus)
(float **a, float **y, int n);
#else
(float **,float **,int);
#endif
//_____________________________________________________________________________

//#ifdef CHECK_USED
#ifdef __cplusplus
extern void squarematstream(std::ostream &outstrm,float **x, int n);
#else
extern void squarematprint
#if defined(__STDC__) || defined(__cplusplus)
(FILE *outfile,float **x, int n);
#else
(FILE *,float **,int);
#endif
//_____________________________________________________________________________
#endif
//#endif
void squarematrix_copy
#if defined(__STDC__) || defined(__cplusplus)
(float **x, float **y, int n);
#else
(float **,float **,int);
#endif
//_____________________________________________________________________________
void transpose
#if defined(__STDC__) || defined(__cplusplus)
(float **x, float **y, int n);
#else
(float **,float **,int);
#endif
//_____________________________________________________________________________
void ludcmp
(
#ifdef BIGMATRIX
 FILE *a
#else
 float **a
#endif
,int n
,int *indx
,float *d);
//_____________________________________________________________________________
void lubksb(
#ifdef BIGMATRIX
FILE *a
#else
float **a
#endif
,int n
,int *indx
,float b[]);
//_____________________________________________________________________________
#endif

