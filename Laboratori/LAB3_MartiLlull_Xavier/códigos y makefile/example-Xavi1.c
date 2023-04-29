#include "libfiber.h"
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

void inicioSesion()
{
	printf("Soy inicio de sesion\n");
}

void compra()
{
	printf("Soy compra\n");
}

int main()
{
   	
   	/* Initialize the fiber library */
   	initFibers();
   	spawnFiber(&inicioSesion);
   	spawnFiber(&inicioSesion);
   	spawnFiber(&inicioSesion);
	   
	getinfo();
   	int prioritat_anterior = sched_nice(1, 2);
   	printf("(Thread2) Me convierto en compra, prioridad anterior %d\n", prioritat_anterior);
	int prioritat_actual = sched_nice(0, 2);
	printf("(Thread2) Me convierto en compra, prioridad actual: %d\n", prioritat_actual);
	getinfo();
	
	int prioritat_anterior1 = sched_nice(1, 3);
   	printf("(Thread3) Me convierto en compra, prioridad anterior %d\n", prioritat_anterior1);
	int prioritat_actual1 = sched_nice(0, 3);
	printf("(Thread3) Me convierto en compra, prioridad actual: %d\n", prioritat_actual1);
	getinfo();
	
	changeFunc(1,&compra);
	changeFunc(2,&compra);
	sched_handoff(3);
	sched_yield();
	getinfo();
	
	/* Since these are nonpre-emptive, we must allow them to run */
	
	
	/* The program quits */
	return 0;
}
