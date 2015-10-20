/*Implementación del analizador léxico*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ALex.h"
#include "SEnt.h"
#include "Defs.h"
#include <string.h>

char* comp;

void DESCARTAR_COMENTARIOS() {
	char sig;
	sig = SIG_CHAR();
	while (sig != '\n') {
		sig = SIG_CHAR();
	}
	printf("%c", sig);
	RETROCEDER();
}

componenteLexico SIG_COMP_LEX() {
	componenteLexico sigComp;
	int control, number = 0;
	int i = 0;
	char sig;
	while (control == 0) {
		comp = malloc(2*sizeof(char));
		sig = SIG_CHAR();
		comp[0] = sig;
		if (comp[0] == '#') {
			DESCARTAR_COMENTARIOS();
		} else if (comp[0] == '\"') {
			comp = (char*) realloc(comp, 4*sizeof(char));
			sig = SIG_CHAR();
			if (sig == '\"') {
				comp[1] = sig;
				sig = SIG_CHAR();
				if (sig == '\"') {
					comp[2] = sig;
					i = 3;
					while (number < 3) {
						comp = (char*) realloc (comp, (strlen(comp) + 2) * sizeof(char));
						sig = SIG_CHAR();
						if (sig != '\"' && sig != EOF) {
							comp[i] = sig;
							i ++;
						} else if (sig == '\"') {
							comp[i] = sig;
							if (comp[i-1] == comp[i]){
								number += 1;
							}
							else {
								number = 1;
							}
							i++;
						}
					}
					if (number == 3) {
						sigComp.id = MULTILINE_STRING;
						sigComp.lexema = (char*) malloc(sizeof (char) * (strlen(comp) + 1));
						strcpy(sigComp.lexema, comp);
						return sigComp;
					}
				}
			}
		} else if (comp[0] == '\n') {
			sigComp.id = comp[0];
			sigComp.lexema = comp[0];
			return sigComp;
		}
	}

	return sigComp;
}

