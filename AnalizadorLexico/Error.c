#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

void ERROR(int id, int linea) {

    switch (id) {
        case NOT_FOUND:
            printf("\nError al abrir el código fuente\n");
            exit(0);
            break;
        case TOO_LONG:
            printf("\nError: El lexema supera el tamaño permitido. Línea: %d\n", linea);
            exit(0);
            break;
        case NOT_RECOGNIZED:
            printf("\nError: Lexema no reconocido. Línea: %d\n", linea);
            exit(0);
            break;
        case STRING_NOT_CLOSED:
            printf("\nError: String no cerrado. Línea: %d\n", linea);
            break;
    }
}
