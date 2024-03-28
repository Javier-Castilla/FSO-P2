#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sala.h"
#include <sys/wait.h>

pid_t sucursales[10] = {0};

void crea_sucursal(const char* ciudad, int capacidad) {
    pid_t pid = fork();

    if (pid == 0) {
        char *argv2[] = {"gnome-terminal", "--", "bash", "-c", "./sala; exec bash", "500", NULL};
        execvp("gnome-terminal", argv2);
        perror("execvp");
        exit(1);
    }
}
    

int main() {
    char nombresala[100];
    int capacidad;
    int num_salas = 0; // Número actual de salas creadas

    while (1) {
        printf("Introduzca el nombre de la sala o 'salir' para terminar: \n");
        scanf("%s", nombresala);

        if (!strcmp("salir", nombresala)) break;
        
        printf("Introduzca la capacidad de la sala: \n");
        scanf("%d", &capacidad);

        crea_sucursal(nombresala, capacidad);
        num_salas++;

        for (int i = 0; i < num_salas; ++i) {
            int status;
            pid_t pid = waitpid(sucursales[i], &status, WNOHANG);
                
            if (pid > 0) {
                printf("La sala con PID %d ha finalizado su ejecución.\n", pid);
                sucursales[i] = 0;
            }
        }
    }
}
