/*Fichero de definición de la tabla de símbolos*/

#include <stdio.h>
#include <stdlib.h>

typedef struct entrada {
	struct entrada* anterior;
	int id;
	int* linea;
	struct entrada* siguiente;
}entradaTabla;

entradaTabla* tablaSimbolos;

int NUEVA_ENTRADA (int id, int linea) {
	int indice;

	/*Devolver dónde estaba o dónde se ha metido*/

	return indice;
}

int BORRAR_ENTRADA (int id) {
	int exito;

	/*Devuelve 0 si falla, y 1 si se borra*/

	return exito;
}

int BUSCAR_ENTRADA (int id) {
	int exito;

	/*Devuelve 0 si encuentra coincidencias y 1 si las encuentra*/

	return exito;
}

void CREAR_TABLA () {

}
