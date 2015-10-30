/*Implementación del analizador léxico*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ALex.h"
#include "SEnt.h"
#include "Defs.h"
#include "Tsim.h"
#include <string.h>

char sig;
componenteLexico sigComp;
int numChar; //número de caracteres leídos

void DESCARTAR_COMENTARIOS() {
    char sig;
    sig = SIG_CHAR();
    numChar++;
    while (sig != '\n') {
        sig = SIG_CHAR();
        numChar++;
    }
    printf("%c", sig);
    RETROCEDER();
}

int STRING_MULTILINEA() {
    char anterior;
    int number = 0;
    int i = 0;
    int retorno = 0;
    sig = SIG_CHAR();
    numChar++;
    if (sig == '\"') {
        sig = SIG_CHAR();
        numChar++;
        if (sig == '\"') {
            i = 3;
            while (number < 3) {
                anterior = sig;
                sig = SIG_CHAR();
                numChar++;
                if (sig != '\"' && sig != EOF) {
                } else if (sig == '\"') {
                    if (anterior == sig) {
                        number += 1;
                    } else {
                        number = 1;
                    }
                }
                i++;
            }
            if (number == 3) {
                sigComp.id = MULTILINE_STRING;
                sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                retorno = 1;
            }
        }
    }
    return retorno;
}

void ALPHANUM() {
    do {
        sig = SIG_CHAR();
        numChar++;
    } while (isalpha(sig) || isdigit(sig) || sig == '_');
    RETROCEDER();
    sigComp.lexema = (char*) malloc((numChar) * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    sigComp.id = NUEVA_ENTRADA(sigComp.lexema);
}

void FL() {
    do {
        sig = SIG_CHAR();
        numChar++;
    } while (isdigit(sig));
    RETROCEDER();
    sigComp.lexema = (char*) malloc(numChar * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    sigComp.id = FLOAT;
}

void INT() {
    do {
        sig = SIG_CHAR();
        numChar++;
    } while (isdigit(sig));
    if (sig == '.') {
        FL();
    } else if (sig == 'e') {
        EXP();
    }else {
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
    sig = SIG_CHAR();
    numChar++;
    if (sig == 'x') {
        do {
            sig = SIG_CHAR();
            numChar++;
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
    }
}

void EXP() {
    sig = SIG_CHAR();
    numChar++;
    if (sig == '-' || isdigit(sig)) {
        do {
            sig = SIG_CHAR();
            numChar++;
        } while (isdigit(sig));
        RETROCEDER();
        sigComp.lexema = (char*) malloc(numChar * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
        sigComp.id = EXPONENTIAL;
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
    char anterior;
    while (control == 0) {
        numChar = 0;
        sig = SIG_CHAR();
        numChar++;
        if (sig == '#') {
            DESCARTAR_COMENTARIOS();
        } else if (sig == '\"') {
            if (STRING_MULTILINEA() == 1) {
                return sigComp;
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
                sig = SIG_CHAR();
                if (isdigit(sig)) {
                    RETROCEDER_TODO();
                    sig = SIG_CHAR();
                    numChar++;
                    NUM();
                    return sigComp;
                }
            }
            sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
            SYM();
            return sigComp;
        } else if (sig == ' ') {
            SYM();
            return sigComp;
        }
    }

    return sigComp;
}

