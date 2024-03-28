#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t childExited = 0;

void sigchld_handler(int signum) {
    childExited = 1;
}

int main() {
    signal(SIGCHLD, sigchld_handler);

    pid_t pid = fork();

    if (pid == 0) {
        char *argv2[] = {"gnome-terminal", "--", "bash", "-c", "./sala; exec bash", "500", NULL};
        execvp("gnome-terminal", argv2);
        perror("execvp");
        exit(1); // exit if execvp fails
    } else if (pid > 0) {
        printf("Esperando a que el proceso hijo termine...\n");

        while (!childExited) {
            // Aquí el proceso padre puede hacer otras tareas mientras espera
        }

        printf("El proceso hijo ha terminado.\n");
    }

    exit(0);
}
