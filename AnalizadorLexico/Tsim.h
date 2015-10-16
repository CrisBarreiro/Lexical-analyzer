#ifndef TSIM_H_
#define TSIM_H_

/*Inserta una entrada en la tabla de símbolos.
 * Devuelve la posición donde estaba o donde se ha metido*/
int NUEVA_ENTRADA (int id, int linea);

/*Borra una entrada de la tabla de símbolos.
 * Devuelve 0 si falla, y 1 si se borra*/
int BORRAR_ENTRADA (int id);

/*Combprueba si un identificador se encuentra en la tabla de símbolos.
 * Devuelve 0 si encuentra coincidencias y 1 si las encuentra*/
int CREAR_TABLA();

#endif
