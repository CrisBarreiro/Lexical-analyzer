/*Fichero de definición de la tabla de símbolos*/

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "Defs.h"
#include "ALex.h"

typedef struct {
	int id;
	char* lexema;
	UT_hash_handle hh;
} entry;

entry *tabla = NULL;

entry * BUSCAR_ENTRADA(char *lex) {
	entry *s;
	HASH_FIND_STR(tabla, lex, s);
	return s;
}

//función privada de manejo de la tabla
void ANHADIR(int id, char *lexema) {
	entry *s = NULL;
	s = (entry*) malloc (sizeof(entry));
	s->lexema = (char*) malloc((strlen(lexema) + 1) * sizeof(char));
	strcpy(s->lexema, lexema);
	s->id = id;
	HASH_ADD_KEYPTR(hh, tabla, s->lexema, strlen(s->lexema), s);
}

int NUEVA_ENTRADA(char *lexema) {
	entry *s = BUSCAR_ENTRADA(lexema);
	if (s == NULL) {
		ANHADIR(IDENTIFIER, lexema);
		return IDENTIFIER;
	} else {
		return s->id;
	}
}

int BORRAR_ENTRADA(int id) {
	int flag = 0;

	return flag;
}

void IMPRIMIR() {
    entry *s, *tmp;
    componenteLexico cl;
    int i;
    printf("--------------------Tabla de símbolos--------------------\n");
    printf("%-8s\t%-20s%-20s\n", "Indice", "Lexema", "Tipo");
    printf("---------------------------------------------------------\n");
    HASH_ITER(hh, tabla, s, tmp) {
        printf("\n%10d\t%-20s%-20d", i, s->lexema, s->id);
	i++;
    }
    
}

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
