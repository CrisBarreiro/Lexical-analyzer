/*Implementación del analizador léxico*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ALex.h"
#include "SEnt.h"
#include "Defs.h"
#include <string.h>


char* comp;
int sig;
componenteLexico sigComp;

void DESCARTAR_COMENTARIOS() {
	char sig;
	sig = SIG_CHAR();
	while (sig != '\n') {
		sig = SIG_CHAR();
	}
	printf("%c", sig);
	RETROCEDER();
}

int STRING_MULTILINEA() {
	comp = (char*) realloc(comp, 4 * sizeof(char));
	int number = 0;
	int i = 0;
	int retorno = 0;
	sig = SIG_CHAR();
	if (sig == '\"') {
		comp[1] = sig;
		sig = SIG_CHAR();
		if (sig == '\"') {
			comp[2] = sig;
			i = 3;
			while (number < 3) {
				comp = (char*) realloc(comp, (strlen(comp) + 2) * sizeof(char));
				sig = SIG_CHAR();
				if (sig != '\"' && sig != EOF) {
					comp[i] = sig;
					i++;
				} else if (sig == '\"') {
					comp[i] = sig;
					if (comp[i - 1] == comp[i]) {
						number += 1;
					} else {
						number = 1;
					}
					i++;
				}
			}
			if (number == 3) {
				sigComp.id = MULTILINE_STRING;
				sigComp.lexema = (char*) malloc(
						sizeof(char) * (strlen(comp) + 1));
				strcpy(sigComp.lexema, comp);
				retorno = 1;
			}
		}
	}
	return retorno;
}

void ALPHANUM() {
	int i = 1;
	do {
		comp = (char*) realloc(comp, (strlen(comp) + 2) * sizeof(char));
		sig = SIG_CHAR();
		comp[i] = sig;
		i++;
	} while (isalpha(sig) || isdigit(sig) || sig == '_');
	RETROCEDER();
	comp[i - 1] = '\0'; //Eliminamos el último caracter que hemos leído y que no forma parte de la cadena
	sigComp.lexema = (char*) malloc((strlen(comp) + 2) * sizeof(char));
	strcpy(sigComp.lexema, comp);
	sigComp.id = NUEVA_ENTRADA(sigComp.lexema);
}
char* CHARTOSTRING(char input) {
	char* output = (char*) malloc(2 * sizeof(char));
	output[0] = input;
	output[1] = '\0';
	return output;
}

int CHECK (char* input) {
	int retorno = 0;

	return retorno;
}

componenteLexico SIG_COMP_LEX() {
	int control = 0;
	char sig;
	while (control == 0) {
		comp = malloc(2 * sizeof(char));
		sig = SIG_CHAR();
		comp[0] = sig;
		//TODO usar un switch case
		if (comp[0] == '#') {
			DESCARTAR_COMENTARIOS();
		} else if (comp[0] == '\"') {
			if (STRING_MULTILINEA() == 1) {
				return sigComp;
			}

		} else if (comp[0] == '\n') {
			sigComp.id = comp[0];
			sigComp.lexema = CHARTOSTRING(comp[0]);
			return sigComp;
		} else if (isalpha(comp[0]) || comp[0] == '_') {
			ALPHANUM();
			return sigComp;
		} else if (ispunct(comp[0])) {
			sigComp.id = comp[0];
			sigComp.lexema = CHARTOSTRING(comp[0]);
			return sigComp;
		} else if (comp[0] == ' ') {
			sigComp.id = comp[0];
			sigComp.lexema = CHARTOSTRING(comp[0]);
			return sigComp;
		}
	}

	return sigComp;
}

