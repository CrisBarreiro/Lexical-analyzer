#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

void ERROR(int id, int linea) {

	switch (id) {
		case 0:
		printf("%s", "Error al abrir el código fuente");
		exit(0);
	}
}
