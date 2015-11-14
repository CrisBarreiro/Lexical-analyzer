#include <stdio.h>
#include <stdlib.h>
#include "flex.h"
#include "Defs.h"
#include "Error.h"
#include "Tsim.h"
#include "ALex.h"

componenteLexico SIG_COMP_LEX() {
	componenteLexico comp;
	comp.id = yylex();
	comp.lexema = strdup(yytext);
	if (comp.id == IDENTIFIER) {
		/*Si el lexema es una secuencia alfanumérica, comprobamos si efectivamente es un identificador
		 * o si es una palabra reservada del lenguaje*/
		comp.id = NUEVA_ENTRADA(comp.lexema);
	}
	return comp;
}
