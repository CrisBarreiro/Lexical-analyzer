/*Sistema de entrada*/

#include "SEnt.h"
#include "Error.h"
#include "ALex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 129

FILE* file;
char* buffer1;
char* buffer2;
int lastBuffer; //último buffer cargado
char *inicio = 0;
char *delantero = 0;
int flag = 0;

void CARGAR_BUFFER() {
    int count;
    /*Si el último buffer cargado fue el 2, se carga el buffer 1*/
    if (lastBuffer == 2) {
        count = fread(buffer1, sizeof (char), BUFFERSIZE - 1, file);
        /*Si el número de caracteres leídos es menor que el tamaño de buffer
         menos uno, se pone el fin de fichero en la posición count del buffer*/
        if (count < BUFFERSIZE - 1) {
            *(buffer1 + count) = EOF;
        }
        /*Se mueve delantero al inicio de buffer y se marca el buffer 1 como 
         el último buffer cargado*/
        delantero = buffer1;
        lastBuffer = 1;
    /*Procedimiento análogo al anterior, utilizando el buffer 2 para cargar*/
    } else if (lastBuffer == 1) {
        count = fread(buffer2, sizeof (char), BUFFERSIZE - 1, file);
        if (count < BUFFERSIZE - 1) {
            buffer2[count] = EOF;
        }
        delantero = buffer2;
        lastBuffer = 2;
    }
}

/*Función de inicialización*/
void INICIALIZAR() {
    /*Se marca el buffer 2 como último buffer cargado para cargar el buffer 1 
     en primer lugar*/
    lastBuffer = 2;
    /*Se reserva memoria para ambos buffers*/
    buffer1 = (char*) malloc(BUFFERSIZE * sizeof (char));
    buffer2 = (char*) malloc(BUFFERSIZE * sizeof (char));
    /*Se apunta inicio a buffer 1*/
    inicio = buffer1;
    /*Se coloca el final de fichero en la última posición de ambos buffers*/
    *(buffer1 + BUFFERSIZE - 1) = EOF;
    *(buffer2 + BUFFERSIZE - 1) = EOF;
    /*Se llama a la función de carga de buffers*/
    CARGAR_BUFFER();
}

/*Devuelve el número de buffer en el que se encuentra inicio*/
int BUFFER_INICIO() {
    int buffer;
    /*Si la posición de memoria a la que apunta inicio se encuentra entre el 
     principio y el final de buffer1, entonces está en el buffer1*/
    if (inicio >= buffer1 && inicio <= (buffer1 + BUFFERSIZE - 1)) {
        buffer = 1;
    } else if (inicio >= buffer2 && inicio <= (buffer2 + BUFFERSIZE - 1))
        buffer = 2;
    return buffer;
}

/*Devuelve el número de buffer en el que se encuentra delantero. Análoga a
 BUFFER_INICIO()*/
int BUFFER_DELANTERO() {
    int buffer;
    if (delantero >= buffer1 && delantero <= (buffer1 + BUFFERSIZE - 1)) {
        buffer = 1;
    } else if (delantero >= buffer2
            && delantero <= (buffer2 + BUFFERSIZE - 1)) {
        buffer = 2;
    }
    return buffer;
}

/*Devuelve 1 si inicio y delantero están en el mismo buffer
 * y 0 en caso contrario*/
int MISMO_BUFFER() {
    int ret;
    if (BUFFER_INICIO() == BUFFER_DELANTERO()) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

/*Función que devuelve el siguiente caracter en el flujo de entrada*/
char SIG_CHAR() {
    char ret;
    if (lastBuffer == 2) {
        if (*delantero == EOF) {
            /*Si delantero apunta al fin de fichero y está en la última
             posición del buffer*/
            if (delantero == (buffer2 + BUFFERSIZE - 1)) {
                if (MISMO_BUFFER()) {
                    /*Si inicio y delantero están en el mismo buffer*/
                    if (BUFFER_DELANTERO() == 2) {
                        /*Si delantero está en el buffer2, se carga un nuevo
                         buffer, que en este caso será el 1*/
                        CARGAR_BUFFER();
                    } else {
                        /*Si delantero apunta al buffer1, se mueve delantero
                         al buffer2*/
                        delantero = buffer2;
                    }
                } else {
                    /*El lexema supera el tamaño máximo permitido*/
                    ERROR(TOO_LONG, LINEA());
                }
            } else {
                /*Si delantero apunta al fin de fichero y no se encuentra en
                 la última posición del buffer, quiere decir que hemos
                 encontrado el final del fichero de entrada*/
                ret = EOF;
            }
        }
    /*Procedimiento análogo al descrito cuando lastBuffer == 2*/
    } else if (lastBuffer == 1) {
        if (*delantero == EOF) {
            if (delantero == (buffer1 + BUFFERSIZE - 1)) {
                if (MISMO_BUFFER()) {
                    if (BUFFER_DELANTERO() == 1) {
                        CARGAR_BUFFER();
                    } else {
                        delantero = buffer1;
                    }
                } else {
                    ERROR(TOO_LONG, LINEA());
                }
            } else {
                ret = EOF;
            }
        }
    }
    /*Se devuelve el valor almacenado en la posición apuntada por delantero*/
    ret = *delantero;
    /*Mover Inicio después de haber leído un componente léxico*/
    if (flag == 1) {
        flag = 0;
        inicio = delantero;
    }
    /*Se mueve en una posición el puntero delantero*/
    delantero = delantero + 1;

    return ret;
}

/*Función de retroceso. El puntero delantero se mueve a la posición apuntada
 por inicio. Se utiliza cuando una función falla al reconocer un componente
 léxico*/
void RETROCEDER_TODO() {
    delantero = inicio;
}

/*Función que mueve una posición hacia atrás el puntero delantero*/
void RETROCEDER() {
    /*Si delantero no es la primera posición de un buffer, se mueve el puntero
     una posición hacia atrás*/
    if (delantero != buffer1 && delantero != buffer2) {
        delantero = delantero - 1;
    /*Si delantero es la primera posición de un buffer, se mueve delantero a la 
     * última posición del otro buffer*/
    } else if (lastBuffer == 1) {
        delantero = buffer2 + BUFFERSIZE - 1;
    } else if (lastBuffer == 2) {
        delantero = buffer1 + BUFFERSIZE - 1;
    }
    /*Se pone la flag a 1, lo que quiere decir que se ha de mover inicio en la siguiente iteración*/
    flag = 1;
}

/*Función de apertura del fichero de entrada*/
FILE* ABRIR(char* ruta) {

    file = fopen(ruta, "rt");

    return file;
}

/*Función que devuelve un componente léxico al analizador léxico*/
char* DEVOLVER_COMPONENTE() {
    char *ret, *tmp;
    int i;
    tmp = inicio;
    /*Si inicio y delantero se encuentran en el mismo buffer*/
    if (MISMO_BUFFER()) {
        /*Se reserva memoria para el string de retorno*/
        ret = (char*) malloc(sizeof (delantero - inicio + 1) * sizeof (char));
        /*Se recorre el buffer desde inicio hasta delantero*/
        for (i = 0; tmp < delantero; i++) {
            ret[i] = *tmp;
            tmp++;
        }
        /*Se añade el caracter de fin de cadena al final del string de retorno*/
        ret[i] = '\0';
    } else {
        /*Si inicio y delantero no están en el mismo buffer, se reserva un
         string de tamaño máximo*/
        ret = (char*) malloc((BUFFERSIZE - 1) * sizeof (char));
        for (i = 0; tmp != (delantero); i++) {
            /*Si tmp no apunta a una posición que contenga el fin de fichero,
             se recorre el buffer donde se encuentre inicio hasta encontrarse
             con el final de fichero*/
            if (*tmp != EOF) {
                ret[i] = *tmp;
                tmp++;
                /*Al encontrarse el final de fichero, se apunta tmp al
                 principio del buffer donde se encuentra delantero*/
            } else if (BUFFER_INICIO() == 1) {
                tmp = buffer2;
                /*Decrementamos i para poder insertar el primer elemento del 
                 * buffer en la posición que corresponde en la siguiente 
                 * iteración*/
                i --;
            } else {
                tmp = buffer1;
                i--;
            }
            
        }
        /*Añadimos el caracter de fin de cadena al final del String*/
        ret[i + 1] = '\0';
    }

    /*Ponemos la flag a 1 para indicar que moveremos inicio en la siguiente
     iteración*/
    flag = 1;
    return ret;
}

/*Función que cierra el fichero*/
int CERRAR() {
    fclose(file);
    return 0;
}

