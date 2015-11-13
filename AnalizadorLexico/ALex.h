/*
 * ALex.h
 *
 *  Created on: 13 de nov. de 2015
 *      Author: cristina
 */

#ifndef ALEX_H_
#define ALEX_H_

typedef struct {
	int id;
	char* lexema;
} componenteLexico;

/*Devuelve un componente léxico*/
componenteLexico SIG_COMP_LEX();

#endif /* ALEX_H_ */
