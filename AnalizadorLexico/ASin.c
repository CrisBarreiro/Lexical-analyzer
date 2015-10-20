/*Fichero de implementación del analizador sintáctico*/

#include <stdio.h>
#include <stdlib.h>
#include "ALex.h"
#include "SEnt.h"
#include "Error.h"

#define ruta "entrada/codigo.py"

/*Función que pide un componente léxico al analizador léxico*/
void PEDIR_COMP_LEX() {
	componenteLexico comp = SIG_COMP_LEX();
}

int main () {

	FILE *file = ABRIR(ruta);
	if (!file) {
		ERROR (0, 0);
	}

	PEDIR_COMP_LEX();

	return 0;
}
