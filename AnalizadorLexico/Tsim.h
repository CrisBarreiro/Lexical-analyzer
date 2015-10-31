#ifndef TSIM_H_
#define TSIM_H_

/*Inserta una entrada en la tabla de símbolos y
 * devuelve el tipo de componente
 */
int NUEVA_ENTRADA (char *lexema);

/*Borra una entrada de la tabla de símbolos.
 * Devuelve 0 si falla, y 1 si se borra*/
int BORRAR_ENTRADA (int id);

void CREAR_TABLA();

void IMPRIMIR();

#endif
