/*
 * Defs.h
 * Fichero de definiciones
 *
 *  Created on: 9 de oct. de 2015
 *      Author: cristina
 */

#ifndef DEFS_H_
#define DEFS_H_

/*Keywords*/
#define IMPORT 300
#define AS 301
#define DEF 302
#define FOR 303
#define IN 304
#define IF 305
#define ELIF 306
#define ELSE 307
#define NOT 308
#define PRINT 309
#define RETURN 310

/*Tipos de componente léxico*/
#define IDENTIFIER 350
#define MULTILINE_STRING 351
#define INTEGER 352
#define FLOAT 353
#define HEXADECIMAL 354
#define EXPONENTIAL 355
#define STRING 356
#define INDENTATION 357
#define POWER 358
#define PLUSPLUS 959
#define MORE_EQUALS 360
#define EQUALS 361
#define MINUSMINUS 362
#define MINUS_EQUALS 363

/*Función que devuelve el tipo de componente léxico en formato String*/
char* IDTOSTRING (int id);
#endif /* DEFS_H_ */
