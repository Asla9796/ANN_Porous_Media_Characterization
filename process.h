#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>

#define HDR 1024
#define FNAMESIZE 64
#define epochmax 2000

/* define a structure to hold 2D slice info */
typedef struct {
   double **var;
   int nx;
   int ny;
} slice;

/*program functions*/
void initialization(void);
void trainann(void);
void predict(void);
void printoutput(int epoch, double error);
void printfinal(void);
void freememory(void);

/*external utilities*/
extern double ***alloc3Ddouble (int nx, int ny, int nz);
extern double **alloc2Ddouble (int nx, int ny);
extern double ****alloc4Ddouble (int nx, int ny, int np, int ni);
extern void rawread3d(double ***f, int l1, int m1, int n1, FILE *fp);
extern void rawread1d(double *f, int l1, FILE *fp);
extern void fwrite3d(double ***f, int L1, int M1, int N1, FILE *fp);
extern void fwrite1d(double *f, int L1, FILE *fp);
extern void readdata(char *filename, int numpat);
extern slice slice2Ddouble (double ***f, int dir, int n);
extern void print2Dslice (FILE * fp, slice sec, int form);
void extractdata(int numpat);

/*program variables*/
double ****t_input, ***t_target; 
double **output;
int nx=64, ny=64, np=5, ni=2, nh=1;
double inputh, ****weightih, ***hidden;
double inputo, ***weightho;
double sumdow, **deltao, ***deltah;
double ***deltawho, ****deltawih, **error;
double *errorepoch;
double smallweight, errormax;
double alpha, eta;

char datafile[FNAMESIZE];

int L1;
int M1;
int N1;

double ***u;
double ***v;
double ***w;
double ***epsi;
double ***phi;

char *fbase;