/*Fichero de implementación del analizador sintáctico*/

#include <stdio.h>
#include <stdlib.h>
#include "SEnt.h"

#define ruta "entrada/codigo.py"

/*Función que pide un componente léxico al analizador léxico*/
void PEDIR_COMP_LEX() {

}

int main () {

	FILE *file = ABRIR(ruta);
	if (!file) {
		ERROR (0, 0);
	}

	return 0;
}
