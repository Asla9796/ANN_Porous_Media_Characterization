#include <stdio.h>
#include <stdlib.h> 
#define MAXCHAR 10

char *create1Dchar(int length)
{

    char *space;
    int i;

    space = (char *) malloc (length * sizeof (char));

    /*  initialising all elements to 0.0 to be on safer side */
    for (i = 0; i < length; i++)
    {
        space[i] = 0.0;
    }

    return (space);
}

double **create2Darray(int nx, int ny)
{

  double *space;
  double **arr2d;
  int i, j;

  space = (double *) malloc (nx * ny * sizeof (double));

  arr2d = (double **) malloc (nx * sizeof (double *));
  for (i = 0; i < nx; i++) {
      arr2d[i] = space + i * ny;
    }

  for (i = 0; i < nx; i++) {
      for (j = 0; j < ny; j++) {
	  arr2d[i][j] = 0.0;
	}
    }

  return (arr2d);
}

int main()
{
    FILE *fp;
    char filename[100];
    char *buffer;
    double **u;
    
    buffer = create1Dchar(MAXCHAR);
    sprintf(filename, "p1000.m");
    
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s", filename);
        return 1;
    }
    
    while (fgets(buffer, MAXCHAR, fp) != NULL)
    {
        if
    }
        printf("%s", buffer);
    fclose(fp);
    
    return 0;
}