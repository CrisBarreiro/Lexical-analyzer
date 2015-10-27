/*Sistema de entrada*/

#include "SEnt.h"
#include <stdio.h>
#include <stdlib.h>

FILE* file;

char SIG_CHAR() {
	char sigChar;
	sigChar = fgetc(file);
	return sigChar;
};

void RETROCEDER() {
	fseek(file, -1, SEEK_CUR);
}

FILE* ABRIR(char* ruta) {

	file = fopen(ruta, "rt");

	return file;
}

int CERRAR() {

	return 0;
}
