#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "globaltypes.h"
#include "globalvars.h"

double ****alloc4Ddouble (int nx, int ny, int np, int ni);
double ***alloc3Ddouble (int nx, int ny, int nz);
double **alloc2Ddouble (int nx, int ny);
double *alloc1Ddouble (int nx);
coeffs ***alloc3Dcoeffs (int nx, int ny, int nz);

float ***alloc3Dfloat (int nx, int ny, int nz);
float *alloc1Dfloat (int nx);
/*************************************************************************/
