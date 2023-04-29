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

int main()
{
   	
   	/* Initialize the fiber library */
   	initFibers();
   	for (int i = 0; i < 10; i++) {
		
	   if (i % 3 == 0) {spawnFiber( &uno );}
	   else if (i % 3 == 1) {spawnFiber(&dos);}
	   else if (i % 3 == 2) {spawnFiber(&tres);}
	}
   	
   	int prioritat_anterior1 = sched_nice(1, 2);
   	int prioritat_anterior2 = sched_nice(21, 3);
   	printf("Primer cambio hecho al thread 2, antes tenia prioridad: %d\n", prioritat_anterior1);
   	printf("Primer cambio hecho al thread 3, antes tenia prioridad: %d\n", prioritat_anterior2);
	int prioritat_actual1 = sched_nice(0, 2);
	printf("Prioridad del thread 2: %d\n", prioritat_actual1);
	int prioritat_actual2 = sched_nice(0, 3);
	printf("Prioridad del thread 3: %d\n", prioritat_actual2);
	
	int error = sched_nice(-1,1);
	printf("Error por prioridad no valida: %d\n", error);
	getinfo();
	sched_handoff(1);
	sched_yield();
	
	/* Since these are nonpre-emptive, we must allow them to run */
	
	
	/* The program quits */
	return 0;
}
