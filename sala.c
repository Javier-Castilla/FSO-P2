#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 2000000 // Capacidas máxima permitida.
#define MAX_LENGTH 34
int capacity = -1;           // Capacidad de la sala actual. -1 indica que no existe sala.
int occupied = 0;            // Número de asientos ocupados.
int* room;                   // Representación de la sala.

/**
 * Se crea una sala con la capacidad indicada.
 * 
 * @param capacidad de la nueva sala
 * @return -1 si ha ocurrido algún error.
 * Se retorna la capacidad si se ha creado correctamente
*/
int crea_sala(int capacidad)
{
    if (capacidad < 1 || capacidad > MAX_CAPACITY || capacity != -1) {
        return -1;
    }

    room = malloc(capacidad*(sizeof(int)));

    for (int i=0; i < capacidad; i++){
        room[i] = -1;
    }

    capacity = capacidad;
    return capacity;

}

/**
 * Se elimina la sala actual.
 * 
 * @return -1 si ha ocurrido algún error.
 * Se retorna 0 si se ha eliminado correctamente
*/
int elimina_sala()
{
    if (capacity == -1) return -1;
    free(room);
    capacity = -1;
    occupied = 0;
    return 0;

}

/**
 * Reserva el asiento y le asigna la id de la persona indicada.
 * 
 * @param id_persona que reserva el asiento
 * @return -1 si ha ocurrido algún error.
 * Se retorna el id del asiento que se ha podido reservar
 * si no ha ocurrido ningún error
*/
int reserva_asiento(int id_persona)
{

    if (capacity - occupied <= 0 || id_persona < 1) return -1;

    for (int i = 0; i < capacity; i++) {
        if (room[i] == -1) {
            room[i] = id_persona;
            occupied++;
            return i;
        }    
    }

    return -1;
}

/**
 * Función que retorna el id de la persona que reservó el asiento
 * 
 * @param id_asiento a liberar
 * @return -1 si ha ocurrido algún error.
 * Se retorna la id de la persona que estaba sentada
 * en el asiento si no hay errores
*/ 
int libera_asiento(int id_asiento)
{
    if (room[id_asiento] != -1 && occupied != 0){
        int temp = room[id_asiento];
        room[id_asiento] = -1;
        occupied--;
        return temp;
    }

    return -1;
}

/**
 * Función que retorna el estado de un asiento 
 * 
 * @param id_asiento a comprobar
 * @return -1 si ha ocurrido algún error.
 * Se retorna 0 si el asiento está libre, y la id
 * de la persona si no lo está
*/ 
int estado_asiento(int id_asiento) 
{
    if (room[id_asiento] > 0){
        return room[id_asiento];
    } else if (room[id_asiento] == -1) {
        return 0;
    }
    return -1;
}

/**
 * Función que retorna la cantidad de asientos libres 
 *
 * @return la cantidad de asientos libres en la sala.
 * Se retorna -1 si no existe la sala
*/ 
int asientos_libres()
{
    return capacity - occupied;
}

/** 
 * Función que retorna la cantidad de asientos ocupados
 *
 * @return el número de asientos ocupados
*/ 
int asientos_ocupados()
{
    return occupied;
}

/** 
 * Función que retorna la capacidad actual de la sala
 *
 * @return la capacidad de la sala.
*/ 
int capacidad_sala()
{
    return capacity;
}

void clear()
{
    while (getchar() != '\n');
}

#define MAX_LENGTH 34

int main(int argc, char *argv[]) {
    crea_sala(atoi(argv[1]));
    char commands[7][50] = {"reserva\n", "libera\n", "estado_asiento\n", "estado_sala\n", "cerrar_sala\n", "clear\n", "man\n"};
    int commandsLength = 5;
    char command[50];
    char *commandStr, *arg;
    char helpstr[7][200] = {
        "Reserva el primer asiento libre y le asigna la ID pasada. Se retorna -1 si ha ocurrido algún error",
        "Se libera el asiento con la ID pasada. Se retorna la ID de la persona que ocupaba el asiento o -1 si ha ocurrido algún error",
        "Pasada la ID de un asiento, se devuelve 0 si está libre, 1 si está ocupado o -1 si ha ocurrido algún error",
        "Se muestra el estado de la sala (capacidad, asientos ocupados y libres)",
        "Elimina la sala actual"
        "Limpia la terminal de cualquier texto",
        "Pasado un comando como argumento, muestra la descripción sobre dicho comando"
    };

    while (1) {
        fgets(command, MAX_LENGTH, stdin);

        commandStr = strtok(command, " ");

        if (commandStr) {
            arg = strtok(NULL, " ");
            if (strtok(NULL, " ")) printf("%s\n", "Comando no reconocido");

            if (!strcmp(commandStr, "reserva")) {
                printf("Reservar el asiento: %d\nResultado de la reserva: %d\n", atoi(arg), reserva_asiento(atoi(arg)));
            } else if (!strcmp(commandStr, "libera")) {
                printf("Liberar el asiento: %d\nResultado de la liberación: %d\n", atoi(arg), libera_asiento(atoi(arg)));
            } else if (!strcmp(commandStr, "estado_asiento")) {
                printf(
                    "Estado del asiento: %d\nResultado de la operación (0 es libre, ID de la persona si está ocupado): %d\n",
                    atoi(arg), estado_asiento(atoi(arg))
                );
            } else if (!strcmp(commandStr, "estado_sala\n")) {
                printf(
                    "Capacidad de la sala: %d\nAsientos ocupados: %d\nAsientos libres: %d\n",
                    capacidad_sala(), asientos_ocupados(), asientos_libres()
                );
            } else if (!strcmp(commandStr, "cerrar_sala\n")) {
                printf("%s\n", "Cerrando sala...\n");
                elimina_sala();
                break;
            } else if (!strcmp(commandStr, "help\n")) {
                for (int i = 0; i < commandsLength; i++) {
                    printf("----- %s", commands[i]);
                }
            } else if (!strcmp(commandStr, "clear\n")) {
                printf("\e[1;1H\e[2J");
            } else if (!strcmp(commandStr, "man")) {
                for (int i = 0; i < 7; i++) {
                    if (!strcmp(commands[i], arg)) {
                        printf("%s\n", helpstr[i]);
                        break;
                    }
                }
            } else {
                printf("Comando no reconocido\n");
            }
        }
    }
    exit(1);
}
