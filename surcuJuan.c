//Librerías	
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sala.h"
#include <signal.h>
#include <sys/types.h> // Include the header file that defines pid_t
#include <sys/wait.h> // Include the header file that defines the wait() function

void	crea_sucursal	(const	char*	ciudad,	int	capacidad);	
	
void	crea_sucursal	(const	char*	ciudad,	int	capacidad)	{	
	
    //	Crear	un	proceso	hijo	que	lance	una	terminal	donde	se	
    //	ejecute	el	mini-shell	añadido	a	la	práctica	1	
    //	Deberás	emplear	las	llamadas	al	sistema	fork()	y	exec()	

    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {"gnome-terminal", NULL};
        execvp(args[0], args);
        printf("Sucursal de %s creada\n", ciudad);
    }
    else {
        wait(NULL);
        printf("Sucursal de %s eliminada\n", ciudad);
    }
	
}	
	
	
int	main()	{	
char nombresala[50];	
int	capacidad;	
		while (1) {	
				//	Pedir	nombre	de	nueva	sala	y	capacidad	
                printf("Introduzca el nombre de la sala o 'salir' para terminar: \n");
                scanf("%s", nombresala);
				if (!strcmp("salir",nombresala)) break;	
	
			crea_sucursal (nombresala, capacidad);	
		}	//	termina	el	bucle	principal	
}	