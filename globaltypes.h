/* define structure coeffs for storing the coefficients */

typedef struct {
	double ip;
	double im;
	double jp;
	double jm;
	double kp;
	double km;
	double ap;
	double con;
} coeffs;

/* define a structure to hold extreme info */
typedef struct {
   double value;
   int i;
   int j;
   int k;
} extreme;

/* define a structure to hold all convergence related parameters at one place */

typedef struct {
   int iter;
   int maxiter;
   int timestep;
   int iconv;
   int iconvvels;
   int iconvtemp;
   int iconvcomp;
   float dt;
   float time;
   float tlast;
   int istop;
} convergetype;

/* define a structure to hold all residuals at one place */

typedef struct {
   double umx;
   double delumx;
   double epsu;
   double vmx;
   double delvmx;
   double epsv;
   double wmx;
   double delwmx;
   double epsw;
   double tmx;
   double deltmx;
   double epst;
   double cmx;
   double delcmx;
   double epsc;
} residualtype;

/* define a structure to hold all relaxation parameters at one place */
typedef struct {
   double u;
   double v;
   double w;
   double t;
   double pc;
   double p;
   double c;
} relaxtype;

/* define a structure to hold all physical properties at one place */
typedef struct {
    double rhocon;
    double conductivity;
    double specificheat;
    double alatent;
    double tmelt;
    double tgref;
    double compressibility;
    double viscosity;
    double stcof;
    double diffusivity;
} physproptype;


