/*Fichero de implementación del analizador sintáctico*/

#include <stdio.h>
#include <stdlib.h>
#include "ALex.h"
#include "SEnt.h"
#include "Error.h"
#include "Tsim.h"

#define ruta "entrada/codigo.py"
#define cosas 30

/*Función que pide un componente léxico al analizador léxico*/
void PEDIR_COMP_LEX() {
	componenteLexico comp;
	int i;
	for (i = 0; i < cosas; i++) {
		comp = SIG_COMP_LEX();
		printf("%d\t#%s#\n", comp.id, comp.lexema);
	}
}

int main() {

	FILE *file = ABRIR(ruta);
	if (!file) {
		ERROR(0, 0);
	}

	CREAR_TABLA();

	PEDIR_COMP_LEX();

	return 0;
}
