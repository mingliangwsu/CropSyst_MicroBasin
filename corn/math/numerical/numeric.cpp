#include "corn/math/numerical/numeric.h"
#include <math.h>
#define TINY 1.0e-20
#include <stdio.h>
#include <stdlib.h>
//______________________________________________________________________________
void nrerror
#if defined(__STDC__) || defined(__cplusplus)
(const char *error_text)                                                          //030201
#else
(error_text)
char error_text[];
#endif
{
   fprintf(stderr,"Numerical Recipes run-time error ... \n");
   fprintf(stderr,"%s\n", error_text);
   fprintf(stderr,"...now exiting to system...\n");
   exit(1);
}
//______________________________________________________________________________
/* Common functions */
float *vector
#if defined(__STDC__) || defined(__cplusplus)
(int nl,int nh)
#else
(nl,nh)
int nl,nh;
#endif
{  float *v;
   v =(float *)malloc((unsigned) (nh-nl+1)*sizeof(float));
   if (!v) nrerror("allocation failure in vector()");
   return v-nl;
}
//______________________________________________________________________________
void free_vector
#if defined(__STDC__) || defined(__cplusplus)
(float *v,int nl,int nh)
#else
(v,nl,nh)
float *v;
int nl , nh;
#endif
{  free((char *) (v+nl));
}
//______________________________________________________________________________
int *ivector
#if defined(__STDC__) || defined(__cplusplus)
(int nl,int nh)
#else
(nl,nh)
int nl,nh;
#endif
{  int *v;
   v = (int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
   if (!v) nrerror("allocation failure in ivector()");
   return v-nl;
}
//______________________________________________________________________________
void free_ivector
#if defined(__STDC__) || defined(__cplusplus)
(int *v,int nl,int nh)
#else
(v, nl, nh)
int *v;
int nl, nh;
#endif
{  free((char *) (v+nl));
}
//______________________________________________________________________________
#ifdef BIGMATRIX
void mat_file_set(FILE *matfile,int i, int j, int n,float v)
{
  Seek(matfile,(i-1)*n + j,0);  /*OFFSET_BEGINNING);*/
  write(&v,sizeof(float),1,matfile);
}
//______________________________________________________________________________
float mat_file_get(FILE *matfile,int i, int j,int n)
{ float v;
  Seek(matfile,(i-1)*n + j,0);  /*OFFSET_BEGINNING);*/
  read(&v,sizeof(float),1,matfile);
  return(v);
}
//______________________________________________________________________________
#define x_set(i,j,n,v)    mat_file_set(x,i,j,n,v)
#define x_get(i,j,n)      mat_file_get(x,i,j,n)
//______________________________________________________________________________
#define y_set(i,j,n,v)    mat_file_set(y,i,j,n,v)
#define y_get(i,j,n)      mat_file_get(y,i,j,n)
//______________________________________________________________________________
#define z_set(i,j,n,v)    mat_file_set(z,i,j,n,v)
//______________________________________________________________________________
#define a_set(i,j,n,v)    mat_file_set(a,i,j,n,v)
#define a_get(i,j,n)      mat_file_get(a,i,j,n)
//______________________________________________________________________________
#define b_set(i,j,n,v)    mat_file_set(b,i,j,n,v)
#define b_get(i,j,n)      mat_file_get(b,i,j,n)
//______________________________________________________________________________
//______________________________________________________________________________

           /* given an nxn matrix a[n][n], this routine replaces it by the LU
              decomposition  of a rowwise permutation of itself, a and n are input, a
              is output; indx[1..n] is an output vector which records the row
              permutation effected by the partial pivoting; di output as +-1
              depending on whether the number of row interchanges was even or odd,
              respectively. This routine is used in combination with lubkasb to solve
              linear equations or invert a matrix.
           */
void ludcmp(a,n,indx,d)
int n,*indx;
#ifdef BIGMATRIX
FILE *a;
#else
float **a;
#endif
float *d;
{
  int i, imax,j,k;
  float big,dum,sum,temp;
  float *vv;
  vv = vector(1,n);
  *d = 1.0;
  for (i = 1 ; i <= n; i++)
  {
    big = 0.0;
    for (j = 1; j <= n; j++)
        if ((temp=fabs(a_get(i,j,n))) > big) big = temp;
    if (big == 0.0) nrerror("Singular matrix not valid in LU decomposition");
    vv[i] = 1.0/big;
  }
  for (j= 1;j <=n;j++)
  {  for (i = 1; i<j;i++)
     { sum = a_get(i,j,n);
       for (k = 1;k < i;k++) sum -= a_get(i,k,n) * a_get(k,j,n);
       a_set(i,j,n,sum);
     }
     big = 0.0;
     for (i = j; i <= n;i++)
     {
        sum = a_get(i,j,n);
        for (k = 1; k< j;k++) sum -= a_get(i,k,n) * a_get(k,j,n);
        a_set(i,j,n,sum);
        if ((dum =vv[i]*fabs(sum)) >= big)
        {
          big =dum;
          imax =i;
        }
     }
     if (j != imax)
     { for (k = 1; k<=n;k++)
       { dum = a_get(imax,k,n);
         a_set(imax,k,n, a_get(j,k,n));
         a_set(j,k,n,dum);
       }
       *d = -(*d);
       vv[imax] = vv[j];
     }
     indx[j] = imax;
     if (a_get(j,j,n) == 0.0) a_set(j,j,n,TINY);
     if (j != n)
     { dum = 1.0 / a_get(j,j,n);
       for (i =j+1;i <=n;i++) a_set(i,j,n,a_get(i,j,n) * dum);
     }
  }
  free_vector(vv,1,n);
}
//______________________________________________________________________________
void lubksb(a,n,indx,b)
#ifdef BIGMATRIX
FILE *a;
#else
float **a;
#endif
b[];
int n,*indx;
{
   int i,ii=0,ip,j;
   float sum;
   for (i = 1;i<=n;i++)
   {  ip = indx[i];
      sum=b[ip];
      b[ip] = b[i];
      if (ii)
         for (j =ii; j<=i-1;j++) sum -= a_get(i,j,n) * b[j];
      else
         if (sum != 0) ii =i;
      b[i] = sum;
    }
    for (i = n ; i>= 1;i--)
    {
       sum =b[i];
       for (j = i+1;j<=n; j++) sum -= a_get(i,j,n) * b[j];
       b[i] = sum / a_get(i,i,n);  /* why not a[i][j]; */
    }
}
//______________________________________________________________________________
void inverse(a,y,n)
#ifdef BIGMATRIX
FILE *a; FILE *y;
#else
float **a; **y;
#endif
int   n;
{
   int   *indx;
   float *col;
   float d;
   int i,j;
/*  float **b;  */
   indx = ivector(1,n);
   col  = vector(1,n);
   ludcmp(a,n,indx,&d);
   for (j = 1; j<= n;j++)
   {  for (i = 1; i<= n; i++) col[i] = 0.0;
      col[j] = 1.0;
      lubksb(a,n,indx,col);
      for(i = 1; i<=n;i++) y_set(i,j,n, col[i]);
   }
   free_vector(col,1,n);
   free_ivector(indx,1,n);
}
//______________________________________________________________________________
void squarematmult(x,y,z,n)
#ifdef BIGMATRIX
FILE *x;
FILE *y;
FILE *z;
#else
float **x;
float **y;
float **z;
#endif
int n;
{
   int i,j,k;
   float sum;
   for (k = 1; k <= n; k++)
   { for (j = 1; j <= n; j++)
      { sum = 0.0;
        for (i = 1; i <= n; i++)
             sum += (x_get(k,i,n) * y_get(i,j,n));
        z_set(k,j,n,sum);
      }
   }
}
//______________________________________________________________________________
void squarematprint(outfile,x,n)
FILE *outfile
#ifdef BIGMATRIX
FILE *x;
#else
float **x;
#endif
int n;
{
   int i,j;
   for (i = 1 ; i <= n ; i++)
   {
      for (j = 1; j<=n; j++)
          fprintf(outfile,"%4.2f ",x_get(i,j,n));
      fprintf(outfile,"\n");
   }
}
//______________________________________________________________________________
void homogeneous_mat(x,n)
#ifdef BIGMATRIX
FILE *x;
#else
float **x;
#endif
int n;
{
   int i,j;
   for (i = 1; i <= n;i++)
      for (j = 1 ; j<= n;j++)
          x_set(i,j,n,1.0);
}
#else

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//______________________________________________________________________________
// In memory model
//______________________________________________________________________________
float **matrix
#if defined(__STDC__) || defined(__cplusplus)
(int nrl,int nrh,int ncl,int nch)
#else
(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
#endif
{
   int i;
   float **m;

   m = (float **) malloc((unsigned) (nrh-nrl+1)* sizeof(float *));
   if (!m) nrerror("allocation failure in matrix()");
   m -= nrl;

   for (i= nrl; i <= nrh; i++)
   { m[i] = (float *) malloc ((unsigned) (nch -ncl +1) * sizeof (float));
     if (!m[i]) nrerror("allocation failure 2 in matrix()");
     m[i] -= ncl;
   }
   return m;
}
//______________________________________________________________________________
void free_matrix
#if defined(__STDC__) || defined(__cplusplus)
(float **m,int nrl, int nrh, int ncl, int nch)
#else
(m,nrl,nrh,ncl,nch)
float **m;
int nrl,nrh,ncl,nch;
#endif
{
   int i;
   for (i = nrh; i >= nrl; i--) free((char *) (m[i]+ncl));
   free((char *) (m+nrl));
}
//______________________________________________________________________________

           /* given an nxn matrix a[n][n], this routine replaces it by the LU
              decomposition  of a rowwise permutation of itself, a and n are input, a
              is output; indx[1..n] is an output vector which records the row
              permutation effected by the partial pivoting; di output as +-1
              depending on whether the number of row interchanges was even or odd,
              respectively. This routine is used in combination with lubkasb to solve
              linear equations or invert a matrix.
           */
#if defined(__STDC__) || defined(__cplusplus)
void ludcmp(float **a,int n,int *indx,float *d)
#else
void ludcmp(a,n,indx,d)
int n,*indx;
float **a;
float *d;

#endif
{
  int i, imax,j,k;
  float big,dum,sum,temp;
  float *vv;

  vv = vector(1,n);
  *d = 1.0;
  for (i = 1 ; i <= n; i++)
  {
    big = 0.0;
    for (j = 1; j <= n; j++)
    {  temp=fabs(a[i][j]);
        if (temp > big)
          big = temp;
    }
    if (big == 0.0)
       nrerror("Singular matrix not valid in LU decomposition");
    vv[i] = 1.0/big;
  }
  for (j= 1;j <=n;j++)
  {  for (i = 1; i<j;i++)
     { sum = a[i][j];
       for (k = 1;k < i;k++) sum -= a[i][k] * a[k][j];
       a[i][j] = sum;
     }
     big = 0.0;
     for (i = j; i <= n;i++)
     {
        sum = a[i][j];
        for (k = 1; k< j;k++) sum -= a[i][k] * a[k][j];
        a[i][j] = sum;
        if ((dum =vv[i]*fabs(sum)) >= big)
        {
          big =dum;
          imax =i;
        }
     }
     if (j != imax)
     { for (k = 1; k<=n;k++)
       { dum = a[imax][k];
         a[imax][k] =  a[j][k];
         a[j][k] = dum;
       }
       *d = -(*d);
       vv[imax] = vv[j];
     }
     indx[j] = imax;
     if (a[j][j] == 0.0) a[j][j] =TINY;
     if (j != n)
     { dum = 1.0 / a[j][j];
       for (i =j+1;i <=n;i++) a[i][j] *= dum;
     }
  }
  free_vector(vv,1,n);
}
//______________________________________________________________________________
#if defined(__STDC__) || defined(__cplusplus)
void lubksb( float **a,int n,int *indx,float b[])
#else
void lubksb(a,n,indx,b)
float **a;
float b[];
int n,*indx;
#endif
{
   int i,ii=0,ip,j;
   float sum;
   for (i = 1;i<=n;i++)
   {  ip = indx[i];
      sum=b[ip];
      b[ip] = b[i];
      if (ii)
         for (j =ii; j<=i-1;j++) sum -= a[i][j] * b[j];
      else
         if (sum != 0) ii =i;
      b[i] = sum;
    }
    for (i = n ; i>= 1;i--)
    {
       sum =b[i];
       for (j = i+1;j<=n; j++) sum -= a[i][j] * b[j];
       b[i] = sum / a[i][i];  /* why not a[i][j]; */
    }
}
//______________________________________________________________________________
void inverse
#if defined(__STDC__) || defined(__cplusplus)
(float **a, float **y, int n)
#else
(a,y,n)
float **a;
float **y;
int   n;
#endif
{
   int   *indx;
   float *col;
   float d;
   int i,j;
/*  float **b;  */

   indx = ivector(1,n);
   col  = vector(1,n);

   ludcmp(a,n,indx,&d);
   for (j = 1; j<= n;j++)
   {  for (i = 1; i<= n; i++) col[i] = 0.0;
      col[j] = 1.0;
      lubksb(a,n,indx,col);
      for(i = 1; i<=n;i++) y[i][j] =  col[i];
   }
   free_vector(col,1,n);
   free_ivector(indx,1,n);
}
//______________________________________________________________________________
void squarematmult
#if defined(__STDC__) || defined(__cplusplus)
(float **x,float **y,float **z,int n)
#else
(x,y,z,n)
float **x;
float **y;
float **z;
int n;
#endif
{
   int i,j,k;
   float sum;
   for (k = 1; k <= n; k++)
   { for (j = 1; j <= n; j++)
      { sum = 0.0;
        for (i = 1; i <= n; i++)
             sum += (x[k][i] * y[i][j]);
        z[k][j] = sum;
      }
   }
}
//______________________________________________________________________________
void squarematminus
#if defined(__STDC__) || defined(__cplusplus)
(float **x, float **y, float **z, int n)
#else
(x,y,z,n)
float **x;
float **y;
float **z;
int n;
#endif
{
  int i,j;
  for (i = 1; i <= n; i++)
     for (j = 1; j <= n; j++)
         z[i][j] = x[i][j] - y[i][j];
}
//______________________________________________________________________________
void squarematrix_copy
#if defined(__STDC__) || defined(__cplusplus)
(float **x, float **y, int n)
#else
(x,y,n)
float **x;
float **y;
int n;
#endif
{
  int i,j;
  for (i = 1; i <= n; i++)
     for (j = 1; j <= n; j++)
         y[i][j] = x[i][j];
}
//______________________________________________________________________________
void squarematprint
#if defined(__STDC__) || defined(__cplusplus)
(FILE *outfile,float **x, int n)
#else
(outfile,x,n)
FILE *outfile;
float **x;
int n;
#endif
{
   int i,j;
   for (i = 1 ; i <= n ; i++)
   {
      for (j = 1; j<=n; j++)
          fprintf(outfile,"%5.3f ",x[i][j]);
      fprintf(outfile,"\n");
   }
}
//______________________________________________________________________________
//#ifdef CHECK_USED
//// I think this was used in matgen, but I don't think any more
#ifdef __BCPLUSPLUS__
//#  ifndef BUILDER_API
void squarematstream(std::ostream &outstrm
#ifdef BIGMATRIX
,FILE *x
#else
,float **x
#endif
, int n)
{  int i,j;
   outstrm.width(4);
   outstrm.precision(2);
   for (i = 1 ; i <= n ; i++)
   {  for (j = 1; j<=n; j++)
          outstrm << x[i][j] << ' ';
      outstrm << std::endl;
   }
}
//#  endif
#endif
//#endif
//______________________________________________________________________________
#if defined(__STDC__) || defined(__cplusplus)
void homogeneous_mat
(float **x,int n)
#else
void homogeneous_mat
(x,n)
float **x;
int n;
#endif
{
   int i,j;
   for (i = 1; i <= n;i++)
      for (j = 1 ; j<= n;j++)
          x[i][j] = 1.0;
}
//______________________________________________________________________________
void transpose
#if defined(__STDC__) || defined(__cplusplus)
(float **x, float **y, int n)
#else
(x,y,n)
float **x;
float **y;
int n;
#endif
{ int i,j;
  for (i = 1; i <= n; i++)
     for (j = 1; j <= n; j++)
        y[j][i] = x[i][j];
}
//______________________________________________________________________________
#endif


