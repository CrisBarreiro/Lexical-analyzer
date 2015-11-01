#ifndef TSIM_H_
#define TSIM_H_

/*Inserta una entrada en la tabla de símbolos y
 * devuelve el tipo de componente
 */
int NUEVA_ENTRADA (char *lexema);

/*Crea la tabla de símbolos con las palabras reservadas del lenguaje*/
void CREAR_TABLA();

/*Imprime el contenido de la tabla de símbolos*/
void IMPRIMIR();

#endif
