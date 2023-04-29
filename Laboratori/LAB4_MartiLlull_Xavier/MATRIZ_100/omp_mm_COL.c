#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NRA 100                 /* number of rows in matrix A */
#define NCA 15                 /* number of columns in matrix A */
#define NCB 100                  /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
clock_t inicio, fin;
double tiempo;
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB];           /* result matrix C */
FILE *fp;
chunk = 5;                    /* set loop iteration chunk size */

/*** Spawn a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads,chunk, inicio) private(tid,i,j,k)
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

  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  
  printf("Thread %d starting matrix multiply...\n",tid);
  if (tid == 0) inicio = clock();
  #pragma omp for schedule (static, chunk) 
  for (j=0; j<NCB; j++) {
    char columna[2000] = "";
     
    for(i=0; i<NRA; i++) {
      
      for (k=0; k<NCA; k++) c[i][j] += a[i][k] * b[k][j];
      char cadena[20];   
      sprintf(cadena, "%6.2f\n", c[i][j]); 
      strcat(columna, cadena);
    }
    
    char archivo[20];
    int num = j;
    sprintf(archivo, "COL%d", num);
    fp = fopen(archivo, "w");
    fprintf(fp, "%s", columna);
  }
   /*** End of parallel region ***/
  }
  fin = clock();
  tiempo = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
  
  fclose(fp);
  printf ("Done: Tiempo total = %f\n", tiempo);
}

