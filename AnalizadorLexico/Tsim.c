/*Fichero de definición de la tabla de símbolos*/

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "Defs.h"
#include "ALex.h"

/*Estructura que define cada entrada de la tabla*/
typedef struct {
    int id;
    char* lexema;
    UT_hash_handle hh;
} entry;

/*Tabla de símbolos*/
entry *tabla = NULL;

/*Función que busca una entrada en la tabla utilizando el lexema como
 campo de búsqueda*/
entry * BUSCAR_ENTRADA(char *lex) {
    entry *s;
    HASH_FIND_STR(tabla, lex, s);
    return s;
}

/*Función privada de manejo de la tabla que añade un componente a la misma*/
void ANHADIR(int id, char *lexema) {
    entry *s = NULL;
    s = (entry*) malloc(sizeof (entry));
    s->lexema = (char*) malloc((strlen(lexema) + 1) * sizeof (char));
    strcpy(s->lexema, lexema);
    s->id = id;
    HASH_ADD_KEYPTR(hh, tabla, s->lexema, strlen(s->lexema), s);
}

/*Función que añade una nueva entrada a la tabla*/
int NUEVA_ENTRADA(char *lexema) {
    /*Antes de realizar la inserción, se busca en la tabla para saber si
     el lexema a insertar ya forma parte de la tabla*/
    entry *s = BUSCAR_ENTRADA(lexema);
    if (s == NULL) {
        /*Como las palabras reservadas ya están en la tabla, si no se
         encuentra el lexema buscado, se asume que es un identificador, se
         inserta como tal y se devuelve el tipo de componente IDENTIFIER*/
        ANHADIR(IDENTIFIER, lexema);
        return IDENTIFIER;
    } else {
        /*En caso de estar en la tabla ya con anterioridad, se devuelve su 
         tipo*/
        return s->id;
    }
}

/*Función que imprime el contenido de la tabla de símbolos*/
void IMPRIMIR() {
    entry *s, *tmp;
    int i;
    printf("--------------------Tabla de símbolos--------------------\n");
    printf("%-8s\t%-20s%-20s\n", "Indice", "Lexema", "Tipo");
    printf("---------------------------------------------------------\n");

    HASH_ITER(hh, tabla, s, tmp) {
        printf("\n%10d\t%-20s%-20d", i, s->lexema, s->id);
        i++;
    }
}

/*Función que inicializa la tabla de símbolos con las palabras reservadas del
 lenguaje*/
void CREAR_TABLA() {
    ANHADIR(IMPORT, "import");
    ANHADIR(AS, "as");
    ANHADIR(DEF, "def");
    ANHADIR(FOR, "for");
    ANHADIR(IN, "in");
    ANHADIR(IF, "if");
    ANHADIR(ELIF, "elif");
    ANHADIR(ELSE, "else");
    ANHADIR(NOT, "not");
    ANHADIR(PRINT, "print");
}
