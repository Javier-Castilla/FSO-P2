#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sala.h"
#include <sys/wait.h>
#include <signal.h>

pid_t pidSucursales[10] = {0};
char names[10][50];
int status;

int num_salas = 0;

void crea_sucursal(const char* ciudad, int capacidad) {
    char capacity[10];
    sprintf(capacity, "%d", capacidad);
    pid_t pid = fork();

    if (pid == 0) {
        printf("Sucursal de %s creada\n", ciudad);
        char *argv2[] = {"xterm", "-e", "./sala", capacity, NULL};
        execvp("xterm", argv2);
        exit(1);
    } else {
        pidSucursales[num_salas] = pid;
        sprintf(names[num_salas++], ciudad);
        sleep(0.3);
    }
}
    

int main() {
    char nombresala[100];
    int capacidad;
    
    while (1) {
        int available = 1;
        printf("Introduzca el nombre de la sala o 'salir' para terminar: \n");
        fgets(nombresala, 100, stdin);

        int i = 0;

        for (i = 0; nombresala[i] != '\0'; i++);

        nombresala[i - 1] = '\0'; 

        if (!strcmp("salir", nombresala)) break;

        for (int i = 0; i < num_salas; i++) {
            if (!strcmp(names[i], nombresala)) {
                printf("* ERROR * El nombre introducido ya pertenece a una sucursal\n");
                available = 0;
                break;
            }
        }

        if (!available) {
            continue;
        } else {
            printf("Introduzca la capacidad de la sala: \n");
        }

        scanf("%d", &capacidad);

        while (getchar() != '\n');
        
        crea_sucursal(nombresala, capacidad);

        for (int i = 0; i < num_salas; i++) {
            pid_t pid = waitpid(pidSucursales[i], &status, WNOHANG);

            if (pid != 0) printf("Se ha cerrado la sucursal de %s\n", names[i]);
        }
    }

    for (int i = 0; i < num_salas; i++) {
        kill(pidSucursales[i], SIGINT);
    }

    exit(1);
}
