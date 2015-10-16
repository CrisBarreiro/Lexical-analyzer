/*
 * SEnt.h
 *
 *  Created on: 9 de oct. de 2015
 *      Author: cristina
 */

#ifndef SENT_H_
#define SENT_H_

#include <stdio.h>
#include <stdlib.h>

/*Abre el archivo*/
FILE* ABRIR(char* ruta);

/*Devuelve el siguiente caracter del fichero a leer*/
char SIG_CHAR();

/*Mueve el cursor del fichero una posición hacia atrás*/
void RETROCEDER();

#endif /* SENT_H_ */
