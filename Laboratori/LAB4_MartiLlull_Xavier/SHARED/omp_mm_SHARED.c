#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NRA 62                 /* number of rows in matrix A */
#define NCA 15                 /* number of columns in matrix A */
#define NCB 7                  /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB];           /* result matrix C */
FILE *fp;
chunk = 5;                    /* set loop iteration chunk size */
char resultado[NRA][100];

/*** Spawn a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads,chunk,resultado) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;
  #pragma omp barrier
  fp = fopen("salidaSHARED", "w");
  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  fp = fopen("salidaSHARED", "w");
  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (static, chunk) 
  for (i=0; i<NRA; i++) {
    char linia[100] = "";
     
    for(j=0; j<NCB; j++) {
      
      for (k=0; k<NCA; k++) c[i][j] += a[i][k] * b[k][j];
      char cadena[20];   
      sprintf(cadena, "%6.2f ", c[i][j]); 
      strcat(linia, cadena);
    }
    
    while (i != 0 && resultado[i-1][0] == '\0');
    strcat(resultado[i], linia);
    fprintf(fp, "%s\n", linia);
  }
  fclose(fp);
   /*** End of parallel region ***/
  }
  
  printf ("Done.\n");
}

