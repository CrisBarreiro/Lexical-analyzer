/*Fichero de implementación del analizador sintáctico*/

#include <stdio.h>
#include <stdlib.h>
#include "ALex.h"
#include "SEnt.h"
#include "Error.h"
#include "Tsim.h"

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
        printf("%d\t%d\t#%s#\n", i, comp.id, comp.lexema);
    } while (*(comp.lexema) != EOF);
    printf("\n\n\n----------Fin del reconocimiento de componentes----------\n\n\n");
}

int main() {
    /*Se abre el archivo*/
    FILE *file = ABRIR(ruta);
    if (!file) {
        ERROR(NOT_FOUND, 0);
    }
    /*Se carga el primer buffer*/
    INICIALIZAR();

    /*Se inicializa la tabla de símbolos con las palabras reservadas del 
     lenguaje*/
    CREAR_TABLA();

    /*Se llama a la función que pide componentes léxicos*/
    PEDIR_COMP_LEX();

    /*Se imprime la tabla de símbolos*/
    IMPRIMIR();

    CERRAR();
    printf("\n\n\n----------Fin de la ejecución----------");
    return 0;
}
