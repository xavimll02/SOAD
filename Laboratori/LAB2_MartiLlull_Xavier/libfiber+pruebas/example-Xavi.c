#include "libfiber.h"
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int suma = 0;

void uno()
{
	printf("Residuo 3 doy 0\n");
	suma = suma + 1;
}

void dos()
{
	printf("Residuo 3 doy 1\n");
	suma = suma + 1;
}

void tres()
{
	printf("Residuo 3 doy 2\n");
	suma = suma + 1;
}

void ultimo()
{
	printf("Soy el que han creado tras la muerte de los demas y vengo a decir la suma total que han realizado: %d", suma);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
        printf("Usage: %s <number of threads>\n", argv[0]);
        return 1;
   	}
   	
   	if (atoi(argv[1]) > 10) {
   	printf("Number of threads cannot be greater than 10\n");
   	return 1;
   	}
   	
   	int num_threads = atoi(argv[1]);
   	/* Initialize the fiber library */
   	initFibers();
   	
   	for (int i = 0; i < num_threads; i++) {
		
	   if (i % 3 == 0) {spawnFiber( &uno );}
	   else if (i % 3 == 1) {spawnFiber(&dos);}
	   else if (i % 3 == 2) {spawnFiber(&tres);}
	}
	
	/* Since these are nonpre-emptive, we must allow them to run */
	waitForAllFibers();
	spawnFiber( &ultimo);
	waitForAllFibers();
	
	
	/* The program quits */
	return 0;
}
