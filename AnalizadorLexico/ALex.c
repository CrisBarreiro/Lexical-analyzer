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
    numChar--;
}

void STR() {
    char primero, anterior;
    sig = SIG_CHAR();
    primero = sig;
    if (primero == '"' || primero == '\'') {
        do {
            anterior = sig;
            sig = SIG_CHAR();
            numChar++;
        } while (sig != primero && (anterior != '\'' || anterior != '\\'));
        sigComp.id = STRING;
        sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
        strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    }
}

void STRING_MULTILINEA() {
    char anterior;
    int number = 0;
    sig = SIG_CHAR();
    numChar++;
    if (sig == '\"') {
        sig = SIG_CHAR();
        numChar++;
        if (sig == '\"') {
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

void INT() {
    do {
        sig = SIG_CHAR();
        numChar++;
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
    char anterior;
    while (control == 0) {
        numChar = 0;
        sig = SIG_CHAR();
        numChar++;
        if (sig == '#') {
            DESCARTAR_COMENTARIOS();
        } else if (sig == '\"') {
            STRING_MULTILINEA();
            return sigComp;
        } else if (sig == '\''){
            RETROCEDER();
            STR();
            return sigComp;
        } else if (sig == '*') {
            sig = SIG_CHAR();
            numChar++;
            if (sig == '*') {
                sigComp.lexema = (char*) malloc ((numChar+1) * sizeof(char));
                strcpy (sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = POWER;
                return sigComp;
            } else {
                RETROCEDER();
                sig = SIG_CHAR();
                numChar++;
                SYM();
            }
        } else if (sig == '+') {
            sig = SIG_CHAR();
            if (sig == '+') {
                sigComp.lexema = (char*) malloc ((numChar+1) * sizeof(char));
                strcpy (sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = PLUSPLUS;
                return sigComp;
            } else if (sig == '='){
                sigComp.lexema = (char*) malloc ((numChar+1) * sizeof(char));
                strcpy (sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = MORE_EQUALS;
                return sigComp;
            } else {
                RETROCEDER();
                sig = SIG_CHAR();
                numChar++;
                SYM();
            } 
        }
        else if (sig == '\n') {
            /*TODO: contar espacios después de un \n, indentación*/
            anterior = sig;
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
                    numChar = 0;
                    sig = SIG_CHAR();
                    numChar++;
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
                    sig = SIG_CHAR();
                    numChar++;
                } while (sig == ' ');
                anterior = '0'; /*Ponemos un valor cualquiera en anterior*/
                RETROCEDER();
                sigComp.lexema = (char*) malloc (numChar * sizeof(char));
                strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
                sigComp.id = INDENTATION;
            } else {
                SYM();
            }
            return sigComp;
        }
    }

    return sigComp;
}

