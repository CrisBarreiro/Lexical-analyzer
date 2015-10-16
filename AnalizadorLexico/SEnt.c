/*Sistema de entrada*/

#include "SEnt.h"
#include <stdio.h>
#include <stdlib.h>


char SIG_CHAR() {
	char sigChar = " ";

	return sigChar;
};

void RETROCEDER() {
	/*seek(fp, -1, SEEK_CUR);*/
}

FILE* ABRIR(char* ruta) {
	FILE *file;

	file = fopen(ruta, "rt");

	return file;
}

int CERRAR() {

	return 0;
}
