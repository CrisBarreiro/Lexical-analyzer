#include <stdio.h>
#include <stdlib.h>
#include "flex.h"
#include "ALex.h"

componenteLexico SIG_COMP_LEX() {
	componenteLexico comp;
	comp.id = yylex();
	comp.lexema = strdup(yytext);
	return comp;
}
