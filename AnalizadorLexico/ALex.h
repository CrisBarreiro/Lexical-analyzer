#ifndef ALEX_H_
#define ALEX_H_

#include "uthash.h"

typedef struct {
	int id;
	char* lexema;
} componenteLexico;

/*Devuelve un componente léxico*/
componenteLexico SIG_COMP_LEX();

/*Devuelve el número de línea actual*/
int LINEA();

#endif

