/*Sistema de entrada*/

#include "SEnt.h"
#include "Error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 129

FILE* file;
char buffer1[BUFFERSIZE];
char buffer2[BUFFERSIZE];
int lastBuffer; //último buffer cargado, se inicializa a 2 para cargar primero el buffer1
//int BUFFER_INICIO = 1;
//int BUFFER_DELANTERO() = 1;
char *inicio = 0;
char *delantero = 0;
int flag = 0;

void CARGAR_BUFFER() {
	int count;
	if (lastBuffer == 2) {
		count = fread(buffer1, sizeof(char), BUFFERSIZE - 1, file);
		if (count < BUFFERSIZE - 1) {
			buffer1[count] = EOF;
		}
		delantero = buffer1;
		lastBuffer = 1;
	} else if (lastBuffer == 1) {
		count = fread(buffer2, sizeof(char), BUFFERSIZE - 1, file);
		if (count < BUFFERSIZE - 1) {
			buffer2[count] = EOF;
		}
		delantero = buffer2;
		lastBuffer = 2;
	}
}

void INICIALIZAR() {
    lastBuffer = 2;
    inicio = buffer1;
    buffer1[BUFFERSIZE - 1] = EOF;
    buffer2[BUFFERSIZE - 1] = EOF;
    CARGAR_BUFFER();
}

/*Devuelve el número de buffer en el que se encuentra inicio*/
int BUFFER_INICIO() {
	int buffer;
	if (inicio >= buffer1 && inicio <= (buffer1 + BUFFERSIZE - 1)) {
		buffer = 1;
	} else if (inicio >= buffer2 && inicio <= (buffer2 + BUFFERSIZE - 1))
		buffer = 2;
	return buffer;
}

/*Devuelve el número de buffer en el que se encuentra delantero*/
int BUFFER_DELANTERO() {
	int buffer;
	if (delantero >= buffer1 && delantero <= (buffer1 + BUFFERSIZE - 1)) {
		buffer = 1;
	} else if (delantero >= buffer2
			&& delantero <= (buffer2 + BUFFERSIZE - 1)) {
		buffer = 2;
	}
	return buffer;
}

/*Devuelve 1 si inicio y delantero están en el mismo buffer
 * y 0 en caso contrario*/
int MISMO_BUFFER() {
	int ret;
	if (BUFFER_INICIO() == BUFFER_DELANTERO()) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

	char SIG_CHAR() {
		char ret;
		if (lastBuffer == 2) {
			if (*delantero == EOF) {
				if (delantero == (buffer2 + BUFFERSIZE - 1)) {
					if (MISMO_BUFFER()) {
						if (BUFFER_DELANTERO() == 2) {
							CARGAR_BUFFER();
						} else {
							delantero = buffer2;
						}
					} else {
						ERROR(1, 0);
					}
				} else {
					ret = EOF;
				}
			}
		} else if (lastBuffer == 1) {
			if (*delantero == EOF) {
				if (delantero == (buffer1 + BUFFERSIZE - 1)) {
					if (MISMO_BUFFER()) {
						if (BUFFER_DELANTERO() == 1) {
							CARGAR_BUFFER();
						} else {
							delantero = buffer1;
						}
					} else {
						ERROR(1, 0);
					}
				} else {
					ret = EOF;
				}
			}
		}
		ret = *delantero;
		/*Mover Inicio después de haber leído un componente léxico*/
		if (flag == 1) {
			flag = 0;
			inicio = delantero;
		}
                delantero = delantero + 1;

		return ret;
	}

	void RETROCEDER_TODO() {
		delantero = inicio;
	}

	void RETROCEDER() {
		if (delantero != &buffer1[0] && delantero != &buffer2[0]) {
			delantero = delantero - 1;
		} else if (lastBuffer == 1) {
			delantero = &buffer2[BUFFERSIZE - 1];
		} else if (lastBuffer == 2) {
			delantero = &buffer1[BUFFERSIZE - 1];
		}
                flag = 1;
	}

	FILE* ABRIR(char* ruta) {

		file = fopen(ruta, "rt");

		return file;
	}

	char* DEVOLVER_COMPONENTE() {
		char *ret, *tmp;
		int i;
                int longitud;
		tmp = inicio;
		if (MISMO_BUFFER()) {
			ret = (char*) malloc(sizeof(delantero - inicio + 1) * sizeof(char));
                        //FIXME: antes había un <=
			for (i = 0; tmp < delantero; i++) {
				ret[i] = *tmp;
                                tmp ++;
			}
                        ret[i + 1] = '\0';
		} else {
			ret = (char*) malloc((BUFFERSIZE - 1) * sizeof(char));
			for (i = 0; tmp != (delantero + 1); i++) {
				if (*tmp != EOF) {
					ret[i] = *tmp;
				} else if (BUFFER_INICIO() == 1) {
					tmp = buffer2;
					ret[i] = *tmp;
				} else {
					tmp = buffer1;
					ret[i] = *tmp;
				}
                                tmp ++;
                                ret[i+1] = '\0';
			}
		}

		flag = 1;
		return ret;
	}

	int CERRAR() {

		return 0;
	}

