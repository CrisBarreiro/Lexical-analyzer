/*Implementación del analizador léxico*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ALex.h"
#include "SEnt.h"
#include "Defs.h"
#include "Tsim.h"
#include <string.h>

char sig = '0';
char anterior;
componenteLexico sigComp;
int numChar; //número de caracteres leídos

void SIGUIENTE() {
    anterior = sig;
    sig = SIG_CHAR();
    numChar++;
}

void DESCARTAR_COMENTARIOS() {
    sig = SIG_CHAR();
    while (sig != '\n') {
        sig = SIG_CHAR();
    }
    RETROCEDER();
}

void DESCARTAR_ESPACIOS() {
    sig = SIG_CHAR();
    while(sig == ' ') {
        sig = SIG_CHAR();
    }
    RETROCEDER();
}

void STR() {
    char primero;
    SIGUIENTE();
    primero = sig;
    if (primero == '"' || primero == '\'') {
        do {
            SIGUIENTE();
        } while (sig != primero && (anterior != '\'' || anterior != '\\'));
        sigComp.id = STRING;
        sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    }
}

void STRING_MULTILINEA() {
    int number = 0;
    SIGUIENTE();
    if (sig == '\"') {
        SIGUIENTE();
        if (sig == '\"') {
            while (number < 3) {
                SIGUIENTE();
                if (sig != '\"' && sig != EOF) {
                } else if (sig == '\"') {
                    if (anterior == sig) {
                        number += 1;
                    } else {
                        number = 1;
                    }
                }
            }
            if (number == 3) {
                sigComp.id = MULTILINE_STRING;
                sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
            }
        } else {
            RETROCEDER_TODO();
            numChar = 0;
            STR();
        }
    } else {
        RETROCEDER_TODO();
        numChar = 0;
        STR();
    }
}

void ALPHANUM() {
    do {
        SIGUIENTE();
    } while (isalpha(sig) || isdigit(sig) || sig == '_');
    RETROCEDER();
    sigComp.lexema = (char*) malloc((numChar) * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    sigComp.id = NUEVA_ENTRADA(sigComp.lexema);
}

void FL() {
    do {
        SIGUIENTE();
    } while (isdigit(sig));
    RETROCEDER();
    sigComp.lexema = (char*) malloc(numChar * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    sigComp.id = FLOAT;
}

void EXP() {
    SIGUIENTE();
    if (sig == '-' || isdigit(sig)) {
        do {
            SIGUIENTE();
        } while (isdigit(sig));
        RETROCEDER();
        sigComp.lexema = (char*) malloc(numChar * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
        sigComp.id = EXPONENTIAL;
    }
}

void INT() {
    do {
        SIGUIENTE();
    } while (isdigit(sig));
    if (sig == '.') {
        FL();
    } else if (sig == 'e') {
        EXP();
    } else {
        RETROCEDER();
        sigComp.lexema = (char*) malloc(numChar * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
        sigComp.id = INTEGER;
    }
}

int A_F() {
    if (sig == 'a' || sig == 'b' || sig == 'c' || sig == 'd' || sig == 'e' || sig == 'f') {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

void HEX() {
    SIGUIENTE();
    if (sig == 'x') {
        do {
            SIGUIENTE();
        } while (isdigit(sig) || A_F());
        RETROCEDER();
        sigComp.lexema = (char*) malloc(numChar * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
        sigComp.id = HEXADECIMAL;
    } else if (isdigit(sig)) {
        INT();
    } else if (sig == '.') {
        FL();
    } else if (sig == 'e') {
        EXP();
    } else {
        RETROCEDER();
        numChar--;
        sigComp.lexema = (char*) malloc(numChar * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
        sigComp.id = INTEGER;
    }
}

void NUM() {
    if (sig == '0') {
        HEX();
    } else if (sig == '.') {
        FL();
    } else {
        INT();
    }
}

int CHECK(char* input) {
    int retorno = 0;

    return retorno;
}

/*Función que prepara la estructura para devolver un símbolo*/
void SYM() {
    sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    sigComp.id = sigComp.lexema[0];
}

componenteLexico SIG_COMP_LEX() {
    int control = 0;
    while (control == 0) {
        numChar = 0;
        SIGUIENTE();
        if (sig == '#') {
            DESCARTAR_COMENTARIOS();
        } else if (sig == '\"') {
            STRING_MULTILINEA();
            return sigComp;
        } else if (sig == '\'') {
            RETROCEDER();
            STR();
            return sigComp;
        } else if (sig == '*') {
            SIGUIENTE();
            if (sig == '*') {
                sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = POWER;
                return sigComp;
            } else {
                RETROCEDER();
                SIGUIENTE();
                SYM();
            }
        } else if (sig == '=') {
            SIGUIENTE();
            if (sig == '=') {
                sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = EQUALS;
                return sigComp;
            } else {
                RETROCEDER();
                SIGUIENTE();
                SYM();
            }
        } else if (sig == '+') {
            SIGUIENTE();
            if (sig == '+') {
                sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = PLUSPLUS;
                return sigComp;
            } else if (sig == '=') {
                sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = MORE_EQUALS;
                return sigComp;
            } else {
                RETROCEDER();
                SIGUIENTE();
                SYM();
            }
        } else if (sig == '\n') {
            SYM();
            return sigComp;
        } else if (isdigit(sig)) {
            NUM();
            return sigComp;
        } else if (isalpha(sig) || sig == '_') {
            ALPHANUM();
            return sigComp;
        } else if (ispunct(sig)) {
            if (sig == '.') {
                SIGUIENTE();
                if (isdigit(sig)) {
                    RETROCEDER_TODO();
                    numChar = 0;
                    SIGUIENTE();
                    NUM();
                    return sigComp;
                } else {
                    RETROCEDER();
                    numChar--;
                }
            }
            SYM();
            return sigComp;
        } else if (sig == ' ') {
            if (anterior == '\n') {
                do {
                    SIGUIENTE();
                } while (sig == ' ');
                RETROCEDER();
                sigComp.lexema = (char*) malloc(numChar * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = INDENTATION;
                return sigComp;
            } else {
                DESCARTAR_ESPACIOS();
            }
        }
    }

    return sigComp;
}

