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
	while (*(comp.lexema) != EOF) {
		comp = SIG_COMP_LEX();
                //imprime un espacio de más por motivos desconocidos
		printf("%d\t#%s#\n", comp.id, comp.lexema);
	}
}

int main() {
	char k;
	int i = 0;
	FILE *file = ABRIR(ruta);
	if (!file) {
		ERROR(0, 0);
	}
        INICIALIZAR();
//	 while (k != EOF) {
//	 k = SIG_CHAR();
//	 fflush(stdout);
//	 printf("%c", k);
//	 if (i % 20 == 0)
//	 DEVOLVER_COMPONENTE();
//	 i++;
//	 }
	CREAR_TABLA();

	PEDIR_COMP_LEX();

	return 0;
}
