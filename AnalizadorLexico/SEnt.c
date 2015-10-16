/*Sistema de entrada*/

#include "SEnt.h"
#include <stdio.h>
#include <stdlib.h>

FILE* file;

char SIG_CHAR() {
	char sigChar;
	sigChar = fgetc(file);
	printf ("%c", sigChar);
	return sigChar;
};

void RETROCEDER() {
	/*seek(fp, -1, SEEK_CUR);*/
}

FILE* ABRIR(char* ruta) {

	file = fopen(ruta, "rt");

	return file;
}

int CERRAR() {

	return 0;
}
