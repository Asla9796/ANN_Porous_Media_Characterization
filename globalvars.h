
/* define the domain grid sizes by LL.MM.NN and associated variables */

extern int LL;
extern int MM;
extern int NN;

extern int L1;
extern int M1;
extern int N1;

extern int L2;
extern int M2;
extern int N2;

extern int L3;
extern int M3;
extern int N3;

/* define the scalar variables used globally */

extern int nf;
extern int ipref;
extern int jpref;
extern int kpref;


/* define the three dimensional parameters as pointers */

extern double ***u;
extern double ***v;
extern double ***w;
extern double ***t;
extern double ***c;

/* define the three dimensional parameters for previous timestep */

extern double ***u0;
extern double ***v0;
extern double ***w0;
extern double ***t0;
extern double ***c0;

/* define the three dimensional parameters for previous iteration */

extern double ***uold;
extern double ***vold;
extern double ***wold;
extern double ***told;
extern double ***cold;

/* define the three dimensional pressure related parameters */

extern double ***p;
extern double ***pc;
extern double ***du;
extern double ***dv;
extern double ***dw;

/* define two dimensional phase field parameters and constants*/
extern double **phi;
extern double **phiold;
extern double **cm;
extern double **czero;
extern double **phisquare;
extern double **phicube;

/* define other three dimensional parameters */

extern double ***gam;
extern double ***rho;
extern double ***epsi;
extern double ***delh;
extern double ***delh0;

/* define 3D array to store the coeffs structure */

extern coeffs ***cof;
extern coeffs ***u0cof;
extern coeffs ***v0cof;
extern coeffs ***w0cof;

/* define 2D array to store the top heat flux */

extern double **qflux;

/* define 1D arrays to store the grid parameters */

extern double *x;
extern double *xu;
extern double *xcv;
extern double *xcvs;
extern double *xcvi;
extern double *xcvip;
extern double *xdif;
extern double *fx;
extern double *fxm;

extern double *y;
extern double *yv;
extern double *ycv;
extern double *ycvs;
extern double *ycvj;
extern double *ycvjp;
extern double *ydif;
extern double *fy;
extern double *fym;

extern double *z;
extern double *zw;
extern double *zcv;
extern double *zcvs;
extern double *zcvk;
extern double *zcvkp;
extern double *zdif;
extern double *fz;
extern double *fzm;

extern physproptype physprop;
extern relaxtype relax;
extern residualtype residual;
extern convergetype converge;

/* define systemwide constants here */
#define ZERO 0.0
#define SMALL 1.0e-30
#define ESMALL 1.0e-3
#define USMALL 1.0e-30
#define VSMALL 1.0e-8
#define PERMCONST 1.0e9
#define GRAVITY 9.81
#define SIGMA 5.669e-8
#define EMISSIVITY 0.5
#define FNAMESIZE 64

#define TRUE 1
#define FALSE 0

/* define systemwide variables here */
extern double xl;
extern double yl;
extern double zl;

extern double wscan;
extern double tamb;
extern double htcoef;

extern char iconvection;
extern char iconvsolve;
extern char itemp;
extern char icomp;
extern char iphi;

extern char gridfile[FNAMESIZE];
extern char parfile[FNAMESIZE];

/* define systemwide macros here */
#define amax1(A,B) ((A) > (B) ? (A) : (B))

