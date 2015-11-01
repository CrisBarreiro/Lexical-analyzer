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

/*Carga el primer buffer*/
void INICIALIZAR();

/*Devuelve el siguiente caracter del fichero a leer*/
char SIG_CHAR();

/*Mueve delantero una posición hacia atrás*/
void RETROCEDER();

/*Retrocede hasta el inicio del componente léxico*/
void RETROCEDER_TODO();

/*Devuelve un componente léxico*/
char* DEVOLVER_COMPONENTE();

/*Cierra el fichero*/
int CERRAR();
#endif /* SENT_H_ */
