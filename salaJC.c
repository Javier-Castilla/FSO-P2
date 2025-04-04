#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CAPACITY 2000000 // Capacidas máxima permitida.
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

int main() {
    crea_sala(100);
    char comando[50];
    char *pointer, *pointer2, *token;
    char *keywords[5] = {"reserva", "libera", "estado_asiento", "estado_sala", "cerrar_sala"};


    while (1) {
        fgets(comando, 50, stdin);

        pointer = strtok(comando, " ");

        while (pointer != NULL) {
            if (strcmp(pointer, "reserva") == 0) {
                printf("Reservar el asiento: ");
                printf("%d\n", atoi(pointer2));
                printf("%s", "Resultado de la operación: ");
                printf("%d\n", reserva_asiento(atoi(pointer2)));

            } else if (strcmp(pointer, "libera") == 0) {
                printf("Liberar el asiento: ");
                printf("%d\n", atoi(pointer2));
                printf("%s", "Resultado de la operación: ");
                printf("%d\n", libera_asiento(atoi(pointer2)));

            } else if (strcmp(pointer, "estado_asiento") == 0) {
                printf("Estado de un asiento: estado_asiento <id-asiento>\n");
                pointer = strtok(NULL, " ");
                if (pointer == NULL) break;
                estado_asiento(atoi(pointer));
            } else if (strcmp(pointer, "estado_sala") == 0) {
                printf("Estado de la sala: estado_sala\n");
            } else if (strcmp(pointer, "cerrar_sala") == 0) {
                printf("Cerrar sala: cerrar_sala\n");
            } else {
                printf("Comando no reconocido\n");
            }
            pointer = strtok(NULL, " ");
        }
    exit(0);
    }
}

