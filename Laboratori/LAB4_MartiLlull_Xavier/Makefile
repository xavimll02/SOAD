##############################################################################
# FILE: Makefile
# DESCRIPTION: 
#   Makefile for OpenMP and Serial C Language Matrix Multiply codes
# AUTHOR: Blaise Barney
# MODIFIED: Marisa Gil
# LAST REVISED:  09/26/11
###############################################################################

#Uncomment your choice of compiler
#CC    =   icc
CC    =   gcc
#CC    =   pathcc
#CC    =   pgcc

#Add your choice of flags
FLAGS   =   -O1

all:	mm		\
	ser_mm          \
	mm_mejorado	\
	mm_salidaFichero \
	ser_mm_salidaFichero \
	mm_SHARED	\
	mm_ROW		\
	mm_COL	
	

clean:	
	/bin/rm  -rf    \
	initial.dat     \
	final.dat       \
	mm		\
	ser_mm          \
	mm_mejorado	\
	mm_salidaFichero \
	ser_mm_salidaFichero \
	mm_SHARED	\
	mm_ROW		\
	mm_COL		\
        *.o

mm_COL:
	$(CC) -fopenmp omp_mm_COL.c -o mm_COL

mm_ROW:
	$(CC) -fopenmp omp_mm_ROW.c -o mm_ROW

mm_SHARED:
	$(CC) -fopenmp omp_mm_SHARED.c -o mm_SHARED

ser_mm_salidaFichero:
	${CC} ${FLAGS} ser_mm_salidaFichero.c -o ser_mm_salidaFichero

mm_salidaFichero:
	$(CC) -fopenmp omp_mm_salidaFichero.c -o mm_salidaFichero

mm_mejorado: omp_mm_mejorado.c
	$(CC) -fopenmp omp_mm_mejorado.c -o mm_mejorado

mm: omp_mm.c
	$(CC) -fopenmp omp_mm.c -o mm

ser_mm: ser_mm.c
	${CC} ${FLAGS} ser_mm.c -o ser_mm 

