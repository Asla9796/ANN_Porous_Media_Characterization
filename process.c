#include "process.h"

/***************************************************************/
int main()
{
    t_input = alloc4Ddouble(nx, ny, np, ni);
    t_target = alloc3Ddouble(nx, ny, np);
    
    strncpy(datafile, "p1000.dat", sizeof(datafile));
    readdata(datafile, 0);
    strncpy(datafile, "p2000.dat", sizeof(datafile));
    readdata(datafile, 1);
    strncpy(datafile, "p3000.dat", sizeof(datafile));
    readdata(datafile, 2);
    strncpy(datafile, "p4000.dat", sizeof(datafile));
    readdata(datafile, 3);
    strncpy(datafile, "p5000.dat", sizeof(datafile));
    readdata(datafile, 4);
    
    initialization();
    trainann();
    printfinal();
    
    freememory();
    printf("\nProgram over. Memory freed. Exiting now.\n");
    return 0;
}

/***************************************************************/

void readdata(char *datafile, int numpat) 
{
    printf("\bReading input file");
    FILE *fp;
    char header[HDR];
    char field[5];
    int n;
    
    fp = fopen(datafile,"r");
    
    printf("file %s opened for reading\n", datafile);
    fflush(stdout);

    n = fread(header, sizeof(char), (size_t) HDR, fp);
    if (n != HDR) printf("error reading header\n");
    printf("header: %s\n",header);

    sscanf(header,"%s %d %d %d", field, &L1, &M1, &N1);
    
    u = alloc3Ddouble(L1, M1, N1);
    v = alloc3Ddouble(L1, M1, N1);
    w = alloc3Ddouble(L1, M1, N1);
    epsi = alloc3Ddouble(L1, M1, N1);
    phi = alloc3Ddouble(L1, M1, N1);
    
    rawread3d(u, L1, M1, N1, fp);
    rawread3d(v, L1, M1, N1, fp);
    rawread3d(w, L1, M1, N1, fp);
    rawread3d(epsi, L1, M1, N1, fp);
    rawread3d(phi, L1, M1, N1, fp);

    fclose(fp);

    printf("File %s closed.\n", datafile);
    extractdata(numpat);
    
    return;
}

/***************************************************************/

void rawread3d(double ***f, int l1, int m1, int n1, FILE *fp) {

    int i;
    int j;
    int k;
    int n;

/*    printf("debug: rawread3d ..."); */

    for (i = 0; i < l1; i++) {
    for (j = 0; j < m1; j++) {
    for (k = 0; k < n1; k++) {
       n = fread(&f[i][j][k], sizeof(double), (size_t) 1, fp);
       if(n != 1) printf("error ");
       fflush(stdout);
    }
    }
    }
    
/*    printf("done.\n"); */

    return;
}

/***************************************************************/

void rawread1d(double *f, int l1, FILE *fp) {

    int i;
    int n;

/*    printf("debug: rawread1d ..."); */

    for (i = 0; i < l1; i++) {
       n = fread(&f[i], sizeof(double), (size_t) 1, fp);
       if(n != 1) printf("error ");
       fflush(stdout);
    }

/*    printf("done.\n"); */

    return;
}

/***************************************************************/

slice slice2Ddouble (double ***f, int dir, int n)
{
  int i;
  int j;
  int k;

  slice sec;

  switch (dir) {
  case (1):
    sec.var = alloc2Ddouble (M1, N1);
    sec.nx = M1;
    sec.ny = N1;
    if (n > L1-1)
      n = L1-1;
    if (n < 0)
      n = 0;
    for (j = 0; j < M1; j++) {
      for (k = 0; k < N1; k++) {
        sec.var[j][k] = f[n][j][k];
      }
    }
    break;
  case (2):
    sec.var = alloc2Ddouble (L1, N1);
    sec.nx = L1;
    sec.ny = N1;
    if (n > M1-1)
      n = M1-1;
    if (n < 0)
      n = 0;
    for (i = 0; i < L1; i++) {
      for (k = 0; k < N1; k++) {
        sec.var[i][k] = f[i][n][k];
      }
    }
    break;
  case (3):
    sec.var = alloc2Ddouble (L1, M1);
    sec.nx = L1;
    sec.ny = M1;
    if (n > N1-1)
      n = N1-1;
    if (n < 0)
      n = 0;
    for (i = 0; i < L1; i++) {
      for (j = 0; j < M1; j++) {
        sec.var[i][j] = f[i][j][n];
      }
    }
    break;
  default:
    printf ("Invalid direction.\n");
    break;
  }

  return (sec);
}

/***************************************************************/

void extractdata(int numpat)
{
    int i, j;
    slice sec;
    
    printf("\nExtracting required 2D data");
    sec = slice2Ddouble (u, 2, 31);
    for(i=0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
            t_input[i][j][numpat][0] = sec.var[i][j]; 
    }

    sec = slice2Ddouble (w, 2, 31);
    for(i=0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
            t_input[i][j][numpat][1] = sec.var[i][j]; 
    }
    
    sec = slice2Ddouble (phi, 2, 31);
    for(i=0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
            t_target[i][j][numpat] = sec.var[i][j]; 
    }
    return;
}

/***************************************************************/

void initialization()
{
    printf("\nInitialiazing variables and arrays");
    /*initialize arrays and variables*/
    output = alloc2Ddouble(nx, ny);
    weightih = alloc4Ddouble(nx, ny, ni, nh);
    hidden = alloc3Ddouble(nx, ny, nh);
    weightho = alloc3Ddouble(nx, ny, nh);
    deltao = alloc2Ddouble(nx, ny);
    deltah = alloc3Ddouble(nx, ny, nh);
    deltawho = alloc3Ddouble(nx, ny, nh);
    deltawih = alloc4Ddouble(nx, ny, ni, nh);
    error = alloc2Ddouble(nx, ny);
    errorepoch = alloc1Ddouble(epochmax);
    
    smallweight = 1.0;
    alpha = 0.9;
    eta = 0.5;
    errormax = 0.0004; /*numerical zero*/
    return;
}

/***************************************************************/

void trainann()
{
    int i, j, p, k, h, epoch;
    double toterror=0, errorm;
    int *ranpat;
    int pi, pn, pindex;
    
    printf("\n%d", epochmax);
    
    ranpat = (int)alloc1Ddouble(np);
    srand(1234567);
    /*initialize weightih and deltawih*/
    for (h=0; h<nh; h++)
    {
        for(i=0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
            {
                for(k=0; k<ni; k++)
                {
                    deltawih[i][j][k][h] = 0.0;
                    weightih[i][j][k][h] = smallweight*(double)rand()/((double)RAND_MAX+1.0);
                }
            }
        }
    }
    
    /*initialize weightho and deltawho*/
    for (h=0; h<nh; h++)
    {
        for(i=0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
            {
                deltawho[i][j][h] = 0.0;
                weightho[i][j][h] = smallweight*(double)rand()/((double)RAND_MAX+1.0);
            }
        }
    }
    
    printf("\nStarting epoch");
    for(epoch=0; epoch<2000; epoch++)
    {
        /*randomization of input parameters*/
        for(p=0; p<np; p++)
        {
            ranpat[p] = p;
        }
        
        for(p=0; p<np; p++)
        {
            pn = p+(double)rand()/((double)RAND_MAX+1.0)*(np+1-p);
            pi = ranpat[p];
            ranpat[p] = ranpat[pn];
            ranpat[pn] = ranpat[pi];
        }
        
        printf("\nPattern: ");
        for(p=0; p<np; p++)
        {
            printf(" %d", ranpat[p]);
        }
    
        toterror = 0.0;
        errorm = 0.0;
        
        for(i=0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
                error[i][j] = 0.0;
        }
        
        for(p=0; p<np; p++)
        {
            /*compute unit activations for hidden layer*/
            pindex=ranpat[p];
            for (h=0; h<nh; h++)
            {
                for(i=0; i<nx; i++)
                {
                    for(j=0; j<ny; j++)
                    {
                        inputh = weightih[i][j][0][0];
                        for(k=0; k<ni; k++)
                        {
                            inputh += t_input[i][j][pindex][k]*weightih[i][j][k][h];
                        }
                        hidden[i][j][h] = 1.0/(1.0+exp(-inputh));
                    }
                }
            }
            
            /*compute unit activations for output layer*/            
            for(i=0; i<nx; i++)
            {
                for(j=0; j<ny; j++)
                {
                    inputo = weightho[i][j][0];
                    for (h=0; h<nh; h++)
                    {
                        inputo += hidden[i][j][h]*weightho[i][j][h];
                    }
                    output[i][j] = 1.0/(1.0+exp(-inputo));
                    error[i][j] += 0.5*(t_target[i][j][p]-output[i][j])*(t_target[i][j][p]-output[i][j]);
                    deltao[i][j] = (t_target[i][j][p]-output[i][j])*output[i][j]*(1.0-output[i][j]);
                }
            }
            
            /*backpropagate errors to hidden layer*/
            for (h=0; h<nh; h++)
            {
                sumdow = 0.0;
                for(i=0; i<nx; i++)
                {
                    for(j=0; j<ny; j++)
                    {
                        sumdow = weightho[i][j][h]*deltao[i][j];
                        deltah[i][j][h] = sumdow*hidden[i][j][h]*(1.0-hidden[i][j][h]);
                    }
                }
            }
            
            /*update weightih*/
            for (h=0; h<nh; h++)
            {
                for(i=0; i<nx; i++)
                {
                    for(j=0; j<ny; j++)
                    {
                        
                        for(k=0; k<ni; k++)
                        {
                            deltawih[i][j][k][h] = eta*t_input[i][j][pindex][k]*deltah[i][j][h]+alpha*deltawih[i][j][k][h];
                            weightih[i][j][k][h] += deltawih[i][j][k][h];
                        }
                    }
                } 
            }
            
            /*update weightho*/
            for(i=0; i<nx; i++)
            {
                for(j=0; j<ny; j++)
                {
                    for (h=0; h<nh; h++)
                    {
                        deltawho[i][j][h] = eta*hidden[i][j][h]*deltao[i][j]+alpha*deltawho[i][j][h];
                        weightho[i][j][h] += deltawho[i][j][h];
                    }
                }
            }            
        }
        
        for(i=0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
            {
                toterror+= error[i][j];
                if(errorm<error[i][j])
                    errorm = error[i][j];
            }
        }
        
        printf("\nEpoch: %d, Max Error: %lf, Total Error: %lf", epoch, errorm, toterror);
        if( epoch%100000 == 0 ) 
        {
            printoutput(epoch, toterror);
        }
        
        errorepoch[epoch] = toterror;
        if(toterror<errormax)
            break;
    }
    
    return;
}

/***************************************************************/

void printoutput(int epoch, double error)
{
    int i, j, k, h;
    FILE *fp;
    char filename[100];
  
    sprintf (filename, "output%d.dat", epoch);
    printf("\nStarting output to %s \n",filename);

    fp=fopen(filename,"w");
    
    fprintf(fp, "weightih=[");  
    for(h=0; h<nh; h++)
    {
        for(i = 0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
            {
                for(k=0; k<ni; k++)
                {
                    fprintf(fp, "%lf  ", weightih[i][j][k][h]);
                }
                fprintf(fp,"\n");
            }
            fprintf(fp,"\n");
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "];\n");
    
    fprintf(fp, "weightho=[");
    for(h=0; h<nh; h++)
    {
        for(i = 0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
            {
                fprintf(fp, "%lf  ", weightho[i][j][h]);
            }
            fprintf(fp,"\n");
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "];");
    
    fprintf(fp, "\nerror=%lf", error);
    
    fprintf(fp, "output=[");  
    for(i = 0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
        {

            fprintf(fp, "%lf  ", output[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "];\n");
    fclose(fp);
  	
    return;
}

/***************************************************************/

void predict()
{
    int i, j;
    FILE *fp;
    char filename[100];
    
    sprintf (filename, "finaloutdata.dat");
    printf("\nStarting output to %s \n",filename);
    
    fp=fopen(filename,"w");
    for(i=0; i<nx; i++)
    {
        for(j=0 ;j<ny; j++)
        {
            /**/
        }
    }
    
    fclose(fp);
    return;
}

/***************************************************************/

void printfinal(void)
{
    FILE *fp;
    int i;
    char filename[100];
    
    sprintf (filename, "final.dat");
    printf("\nStarting output to %s \n",filename);
    
    fp=fopen(filename,"w");
    fprintf(fp, "errorepoch=[");
    for(i=0; i<epochmax; i++)
    {
        fprintf(fp, "%lf ", errorepoch[i]);
    }
    fprintf(fp, "];");
    fclose(fp);
    
    return;
}

/***************************************************************/

void freememory()
{
    free(t_input);
    free(t_target);
    free(output);
    free(weightih);
    free(hidden);
    free(weightho);
    free(deltao);
    free(deltah);
    free(deltawho);
    free(deltawih);

    return;
}

/***************************************************************/
