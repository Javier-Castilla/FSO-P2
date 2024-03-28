#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sala.h"

void crea_sucursal(const char* ciudad, int capacidad) {
    pid_t pid = fork();

    if (pid == -1) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso hijo");
        exit(-1);
    } else if (pid == 0) {
        // Estamos en el proceso hijo
        // Ejecutar el programa sala.c en una nueva terminal
        execl("/usr/bin/gnome-terminal", "gnome-terminal", "--", "./sala", NULL);
        // Si execl() retorna, hubo un error
        perror("Error al ejecutar el programa sala");
        exit(-1);
    } else {
        // Estamos en el proceso padre
        // Esperar a que el hijo termine
        wait(NULL);
        printf("El programa sala terminó de ejecutarse en la otra terminal.\n");
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
