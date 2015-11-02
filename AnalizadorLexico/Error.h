/*
 * Error.h
 *
 *  Created on: 9 de oct. de 2015
 *      Author: cristina
 */

#ifndef ERROR_H_
#define ERROR_H_

/*Imprime por pantalla un error*/
void ERROR(int id, int linea);

/*Tipos de error*/
#define NOT_FOUND 0
#define TOO_LONG 1
#define NOT_RECOGNIZED 2
#define STRING_NOT_CLOSED 3
#define MALFORMED_HEXADECIMAL 4

#endif /* ERROR_H_ */
