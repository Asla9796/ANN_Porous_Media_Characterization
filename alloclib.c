#include "alloclib.h"

double ****
alloc4Ddouble (int nx, int ny, int np, int ni)
{

  double *space;
  double ****arr4d;
  int i, j, k, l;

  /* first we set aside space for the array itself */

  space = (double *) malloc (nx * ny * np * ni * sizeof (double));

  /* next we allocate space of an array of pointers, each
     to eventually point to the first element of a
     2 dimensional array of pointers to pointers */

  arr4d = (double ****) malloc (nx * sizeof (double ***));

  /* and for each of these we assign a pointer to a newly
     allocated array of pointers to a row */

  for (i = 0; i < nx; i++) {
      arr4d[i] = (double ***) malloc (ny * sizeof (double **));

      /* and for each space in this array we put a pointer to
         the first element of each row in the array space
         originally allocated */

      for (j = 0; j < ny; j++) {
          arr4d[i][j] = (double **) malloc (np * sizeof (double *));
          for(k=0; k<np; k++) {
            arr4d[i][j][k] = space + (i * (ny * np * ni) + j * (np * ni) + k * ni);
          }
	}
    }

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++) {
      for (j = 0; j < ny; j++) {
	  for (k = 0; k < np; k++) {
              for(l=0; l<ni; l++) {
                  arr4d[i][j][k][l] = 0.0;
              }
	    }
	}
    }

  return (arr4d);
}

/*************************************************************************/

double ***
alloc3Ddouble (int nx, int ny, int nz)
{

  double *space;
  double ***arr3d;
  int i, j, k;

  /* first we set aside space for the array itself */

  space = (double *) malloc (nx * ny * nz * sizeof (double));

  /* next we allocate space of an array of pointers, each
     to eventually point to the first element of a
     2 dimensional array of pointers to pointers */

  arr3d = (double ***) malloc (nx * sizeof (double **));

  /* and for each of these we assign a pointer to a newly
     allocated array of pointers to a row */

  for (i = 0; i < nx; i++) {
      arr3d[i] = (double **) malloc (ny * sizeof (double *));

      /* and for each space in this array we put a pointer to
         the first element of each row in the array space
         originally allocated */

      for (j = 0; j < ny; j++) {
	  arr3d[i][j] = space + (i * (ny * nz) + j * nz);
	}
    }

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++) {
      for (j = 0; j < ny; j++) {
	  for (k = 0; k < nz; k++) {
	      arr3d[i][j][k] = 0.0;
	    }
	}
    }

  return (arr3d);
}

/*************************************************************************/

double **
alloc2Ddouble (int nx, int ny)
{

  double *space;
  double **arr2d;
  int i, j;

  /* first we set aside space for the array itself */

  space = (double *) malloc (nx * ny * sizeof (double));

  /* next we allocate space of an array of pointers, each
     to eventually point to the first element of a
     2 dimensional array of pointers to pointers */

  arr2d = (double **) malloc (nx * sizeof (double *));

  /* and for each of these we assign a pointer to a newly
     allocated array of pointers to a row */

  for (i = 0; i < nx; i++) {
      arr2d[i] = space + i * ny;
    }

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++) {
      for (j = 0; j < ny; j++) {
	  arr2d[i][j] = 0.0;
	}
    }

  return (arr2d);
}

/*************************************************************************/

double *
alloc1Ddouble (int nx)
{

  double *space;
  int i;

  space = (double *) malloc (nx * sizeof (double));

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++)
    {
      space[i] = 0.0;
    }

  return (space);
}

/*************************************************************************/

coeffs ***
alloc3Dcoeffs (int nx, int ny, int nz)
{

  coeffs *space;
  coeffs ***arr3d;
  int i, j, k;

  /* first we set aside space for the array itself */

  space = (coeffs *) malloc (nx * ny * nz * sizeof (coeffs));

  /* next we allocate space of an array of pointers, each
     to eventually point to the first element of a
     2 dimensional array of pointers to pointers */

  arr3d = (coeffs ***) malloc (nx * sizeof (coeffs **));

  /* and for each of these we assign a pointer to a newly
     allocated array of pointers to a row */

  for (i = 0; i < nx; i++) {
      arr3d[i] = (coeffs **) malloc (ny * sizeof (coeffs *));

      /* and for each space in this array we put a pointer to
         the first element of each row in the array space
         originally allocated */

      for (j = 0; j < ny; j++) {
	  arr3d[i][j] = space + (i * (nz * ny) + j * nz);
	}
    }

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++) {
      for (j = 0; j < ny; j++) {
	  for (k = 0; k < nz; k++) {
	      arr3d[i][j][k].ip = 0.0;
	      arr3d[i][j][k].jp = 0.0;
	      arr3d[i][j][k].kp = 0.0;
	      arr3d[i][j][k].im = 0.0;
	      arr3d[i][j][k].jm = 0.0;
	      arr3d[i][j][k].km = 0.0;
	      arr3d[i][j][k].con = 0.0;
	      arr3d[i][j][k].ap = 0.0;
	    }
	}
    }

  return (arr3d);
}

/*************************************************************************/

float *** alloc3Dfloat (int nx, int ny, int nz)
{

  float *space;
  float ***arr3d;
  int i, j, k;

  /* first we set aside space for the array itself */

  space = (float *) malloc (nx * ny * nz * sizeof (float));

  /* next we allocate space of an array of pointers, each
     to eventually point to the first element of a
     2 dimensional array of pointers to pointers */

  arr3d = (float ***) malloc (nx * sizeof (float **));

  /* and for each of these we assign a pointer to a newly
     allocated array of pointers to a row */

  for (i = 0; i < nx; i++) {
      arr3d[i] = (float **) malloc (ny * sizeof (float *));

      /* and for each space in this array we put a pointer to
         the first element of each row in the array space
         originally allocated */

      for (j = 0; j < ny; j++) {
	  arr3d[i][j] = space + (i * (ny * nz) + j * nz);
	}
    }

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++) {
      for (j = 0; j < ny; j++) {
	  for (k = 0; k < nz; k++) {
	      arr3d[i][j][k] = 0.0;
	    }
	}
    }

  return (arr3d);
}

/*************************************************************************/

float * alloc1Dfloat (int nx)
{

  float *space;
  int i;

  space = (float *) malloc (nx * sizeof (float));

  /*  initialising all elements to 0.0 to be on safer side */
  for (i = 0; i < nx; i++)
    {
      space[i] = 0.0;
    }

  return (space);
}

/*************************************************************************/

