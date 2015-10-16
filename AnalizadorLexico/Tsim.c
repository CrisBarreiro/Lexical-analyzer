/*Fichero de definición de la tabla de símbolos*/

#include <stdio.h>
#include <stdlib.h>

/*Estructura que representa cada entrada de la tabla de símbolos*/
typedef struct entrada {
	struct entrada* anterior;
	int id;
	int* linea;
	struct entrada* siguiente;
}entradaTabla;

entradaTabla* tablaSimbolos;

int NUEVA_ENTRADA (int id, int linea) {
	int indice;


	return indice;
}

int BORRAR_ENTRADA (int id) {
	int exito;



	return exito;
}

int BUSCAR_ENTRADA (int id) {
	int exito;


	return exito;
}

void CREAR_TABLA () {

}
