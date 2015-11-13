/*Fichero de implementación del analizador sintáctico*/

#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#include "ALex.h"
#include "Error.h"
#include "Tsim.h"
#include "flex.h"

#define ruta "entrada/codigo.py"

/*Función que pide un componente léxico al analizador léxico*/
void PEDIR_COMP_LEX() {
    componenteLexico comp;
    int i = 0;
    /*Se piden componentes léxicos hasta que se encuentra el final de
     fichero*/
    do {
        comp = SIG_COMP_LEX();
        i++;
        fflush(stdout);
        printf("%d\t%-20s\t#%s#\n", i, IDTOSTRING(comp.id), comp.lexema);
    } while (comp.id != EOF);
    printf("\n\n\n----------Fin del reconocimiento de componentes----------\n\n\n");
}

int main() {
    /*Se abre el archivo*/
    FILE *file = fopen(ruta, "r");
    if (!file) {
        ERROR(NOT_FOUND, 0);
    }
    yyset_in(file);

    /*Se inicializa la tabla de símbolos con las palabras reservadas del 
     lenguaje*/
    CREAR_TABLA();

    /*Se llama a la función que pide componentes léxicos*/
    PEDIR_COMP_LEX();

    /*Se imprime la tabla de símbolos*/
    IMPRIMIR();

    fclose(file);
    printf("\n\n\n----------Fin de la ejecución----------\n\n\n");
    return 0;
}
