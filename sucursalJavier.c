#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sala.h"

void crea_sucursal(const char* ciudad, int capacidad) {
    pid_t pid = fork(); 

    if (pid == 0) {
        char *args[] = {"gnome-terminal", NULL};
        execvp(args[0], args);
        printf("Sucursal de %s creada\n", ciudad);
        }       
    }
    

int main() {
    char nombresala[100];
    int capacidad;

    while (1) {
        printf("Introduzca el nombre de la sala o 'salir' para terminar: \n");
        scanf("%s", nombresala);

        if (!strcmp("salir", nombresala)) break;
        
        printf("Introduzca la capacidad de la sala: \n");
        scanf("%d", &capacidad);

        crea_sucursal(nombresala, capacidad);

        waitpid();
    }
}