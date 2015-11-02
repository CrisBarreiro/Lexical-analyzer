/*Implementación del analizador léxico*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ALex.h"
#include "SEnt.h"
#include "Defs.h"
#include "Tsim.h"
#include "Error.h"
#include <string.h>

char sig = '0';
char anterior;
componenteLexico sigComp;
int numChar; //número de caracteres leídos
int linea = 1; //número de línea

/*Función que almacena el valor del caracter anterior, pide un nuevo caracter 
 al sistema de entrada y aumenta el contador de caracteres*/
void SIGUIENTE() {
    anterior = sig;
    sig = SIG_CHAR();
    numChar++;
}

/*Función que descarta los comentarios*/
void DESCARTAR_COMENTARIOS() {
    /*Se piden caracteres hasta que se encuentra el salto de línea, que
     se corresponde con el final de un comentario*/
    sig = SIG_CHAR();
    while (sig != '\n') {
        sig = SIG_CHAR();
    }
    linea++;
    RETROCEDER();
    numChar = 0;
}

/*Función que devuelve el número de línea actual*/
int LINEA() {
    return linea;
}

/*Función que descarta los espacios que no están al principio de una línea*/
void DESCARTAR_ESPACIOS() {
    /*Se piden caracteres hasta que se encuentre algo distinto de un espacio*/
    sig = SIG_CHAR();
    while (sig == ' ') {
        sig = SIG_CHAR();
    }
    RETROCEDER();
    numChar = 0;
}

/*Construye el struct de retorno para los componentes léxicos que no sean
 símbolos de un sólo caracter. Se reserva un caracter más que los leídos para
 poder añadir el fin de cadena*/
void CONSTRUIR(int tipo) {
    sigComp.id = tipo;
    sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
}

/*Función que reconoce Strings*/
void STR() {
    char primero;
    SIGUIENTE();
    primero = sig;
    if (primero == '"' || primero == '\'') {
        do {
            /*Se piden caracteres hasta encontrar un caracter que coincida con
             el primer caracter del componente, que puede ser una comilla simple
             o una comilla doble. Se contempla la posibilidad de que se hayan
             insertado comillas escapadas dentro del string*/
            SIGUIENTE();
            if (sig == EOF) {
                ERROR(STRING_NOT_CLOSED, LINEA());
            }
        } while (sig != primero && (anterior != '\'' || anterior != '\\'));
        CONSTRUIR(STRING);
    }
}

/*Función que reconoce Strings multilínea*/
void STRING_MULTILINEA() {
    int number = 0;
    SIGUIENTE();
    /*Una vez sabemos que el primer elemento es una comilla doble, se comprueba
     que los dos siguientes también lo sean*/
    if (sig == '\"') {
        SIGUIENTE();
        if (sig == '\"') {
            while (number < 3) {
                /*Se continúan pidiendo caracteres hasta que se encuentren 3
                 comillas dobles seguidas*/
                SIGUIENTE();
                if (sig == '\"') {
                    if (anterior == sig) {
                        number += 1;
                    } else {
                        number = 1;
                    }
                } else if (sig == EOF) {
                    ERROR(STRING_NOT_CLOSED, LINEA());
                }
            }
            if (number == 3) {
                CONSTRUIR(MULTILINE_STRING);
            }
            /*En caso de no ser un String multilínea, se retrocede hasta el
             * inicio del componente y se intenta reconocer como String*/
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

/*Función que reconoce secuencias alfanuméricas (Palabras reservadas o
 Identificadores)*/
void ALPHANUM() {
    do {
        SIGUIENTE();
    } while (isalpha(sig) || isdigit(sig) || sig == '_');
    RETROCEDER();
    sigComp.lexema = (char*) malloc((numChar) * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    /*Siempre se intenta insertar en la tabla de símbolos, que nos devolverá 
     si el componente léxico es una palabra reservada o un identificador*/
    sigComp.id = NUEVA_ENTRADA(sigComp.lexema);
}

/*Función que reconoce números en notación científica. Siempre se llama después
 de haber leído una secuencia de números terminada por una letra 'e'. Se
 conservan los caracteres pertenecientes al número leídos antes de la 'e'*/
void EXP() {
    SIGUIENTE();
    /*Se comprueba si el siguiente caracter es un dígito o un signo '-'*/
    if (sig == '-' || isdigit(sig)) {
        /*Se piden caracteres hasta que se encuentre algo distinto de un dígito*/
        do {
            SIGUIENTE();
        } while (isdigit(sig));
    }
    /*Se retrocede una posición y se construye un componente de tipo 
     * EXPONENCIAL*/
    RETROCEDER();
    CONSTRUIR(EXPONENTIAL);
}

/*Función que reconoce números en punto flotante. Siempre se llama después de
 haber leído un punto o una secuencia de números terminada en punto. Se
 conservan los caracteres pertenecientes al número leídos antes del punto.*/
void FL() {
    int tmp = numChar;
    do {
        SIGUIENTE();
    } while (isdigit(sig));
    /*Se llama a la función exponencial siempre que se lea una 'e' que no
     aparezca inmediatamente después del punto*/
    if (numChar > tmp + 1) {
        if (sig == 'e') {
            EXP();
        } else {
            /*Si la 'e' aparece justo después del punto, se devuelve un float
             y un identificador*/
        RETROCEDER();
        numChar--;
        CONSTRUIR(FLOAT);
        }
    } else {
        RETROCEDER();
        numChar--;
        CONSTRUIR(FLOAT);
    }
    
}

/*Función que reconoce secuencias de números*/
void INT() {
    do {
        SIGUIENTE();
    } while (isdigit(sig));
    /*Si se encuentra un punto, se llama a la función de reconocimiento 
     de floats*/
    if (sig == '.') {
        FL();
        /*Si se encuentra una 'e', se llama a la función de reconocimiento
         de números en notación científica*/
    } else if (sig == 'e') {
        EXP();
        /*Si se en cuentra cualquier otra cosa, se retrocede una posición y se
         devuelve un componente de tipo entero*/
    } else {
        RETROCEDER();
        CONSTRUIR(INTEGER);
    }
}

/*Función que reconoce letras minúsculas entre la 'a' y ñla 'f' Se usa para
 reconocer números en hexadecimal*/
int A_F() {
    if (sig == 'a' || sig == 'b' || sig == 'c' || sig == 'd' || sig == 'e' || sig == 'f') {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

/*Función que reconoce números en formato hexadecimal. Se llama a esta función
 después de haber leído un '0'*/
void HEX() {
    SIGUIENTE();
    /*Si al cero leído le sigue una 'x', se procede a leer caracteres hasta que
     se encuentre algo distinto de un número o una letra minúscila entre la 'a'
     y la 'f'*/
    if (sig == 'x') {
        do {
            SIGUIENTE();
        } while (isdigit(sig) || A_F());
        RETROCEDER();
        if (strcmp(DEVOLVER_COMPONENTE(), "0x") == 0) {
            ERROR(MALFORMED_HEXADECIMAL, LINEA());
        } else {
            CONSTRUIR(HEXADECIMAL);
        }
        /*Si al cero leído le sigue otro dígito, se llama a la función de
         reconocimiento de números enteros.*/
    } else if (isdigit(sig)) {
        INT();
        /*Si al cero leído le sigue un punto, se llama a la función de
         reconocimiento de números decimales.*/
    } else if (sig == '.') {
        FL();
        /*Si al cero leído le sigue una 'e', se llama a la función de
         reconocimiento de números en notación científica.*/
    } else if (sig == 'e') {
        EXP();
    } else {
        RETROCEDER();
        CONSTRUIR(INTEGER);
    }
}

/*Función que reconoce números. LLama a la función correspondiente en función
 del primer caracter de la cadena*/
void NUM() {
    /*Si el primer caracter es un cero, se llama a la función de reconocimiento
     de hexadecimales*/
    if (sig == '0') {
        HEX();
        /*Si el primer caracter es un punto, se llama a la función de reconocimiento
         de números en punto flotante*/
    } else if (sig == '.') {
        FL();
        /*En otro caso, se llama a la función de reconocimiento de números enteros*/
    } else {
        INT();
    }
}

/*Función que prepara la estructura para devolver un símbolo*/
void SYM() {
    /*En este caso, sólo se ha leído un caracter, pero se reservan 2 porque
     la función DEVOLVER_COMPONENTE() coloca el caracter de fin de cadena
     ('\0') al final de la misma*/
    sigComp.lexema = (char*) malloc((numChar + 1) * sizeof (char));
    strcpy(sigComp.lexema, DEVOLVER_COMPONENTE());
    /*Al tratarse de símbolos ASCII, se coloca como id el número que corresponde
     a la codificación ASCII del caracter*/
    sigComp.id = sigComp.lexema[0];
}

/*Función que devuelve un componente léxico*/
componenteLexico SIG_COMP_LEX() {
    int control = 0;
    /*Se hace un buble para poder continuar identificando componentes en caso
     de haber detectado un comentario o un espacio, que no constituyen
     componentes léxicos*/
    while (control == 0) {
        numChar = 0;
        SIGUIENTE();
        /*Si el primer caracter leído es un comentario, se descarta*/
        if (sig == '#') {
            DESCARTAR_COMENTARIOS();
            /*Si el primer caracter es el fin de fichero, se devuelve*/
        } else if (sig == EOF) {
            SYM();
            return sigComp;
            /*Si el primer caracter es una comilla doble, se llama a la función de
             reconocimiento de Strings multilínea*/
        } else if (sig == '\"') {
            STRING_MULTILINEA();
            return sigComp;
            /*Si el primer caracter es una comilla simple, se retrocede una posición
             y se llama a la función de reconocimiento de Strings*/
        } else if (sig == '\'') {
            RETROCEDER();
            STR();
            return sigComp;
            /*Si el primer caracter es un '*', se comprueba si el siguiente también
             lo es. En ese caso, se devuelve un componente de tipo 'POWER'*/
        } else if (sig == '*') {
            SIGUIENTE();
            if (sig == '*') {
                CONSTRUIR(POWER);
                return sigComp;
                /*Si el siguiente caracter no es un '*', se retrocede una posición
                 y se devuelve sólo el '*'.*/
            } else {
                RETROCEDER();
                numChar--;
                SYM();
                return sigComp;
            }
            /*Si el primer caracter es un '='*/
        } else if (sig == '=') {
            SIGUIENTE();
            /*Se comprueba si el siguiente caracter también lo es y, en caso de
             serlo, se devuelve un componente de tipo 'EQUALS'*/
            if (sig == '=') {
                CONSTRUIR(EQUALS);
                return sigComp;
                /*Si el siguiente caracter no es un '=', se retrocede una posición
                 y se devuelve sólo el '='.*/
            } else {
                RETROCEDER();
                numChar--;
                SYM();
                return sigComp;
            }
            /*Si el primer caracter es un '+'*/
        } else if (sig == '+') {
            SIGUIENTE();
            /*Se comprueba si el siguiente caracter también es un '+'. En caso
             afirmativo, se devuelve un componente de tipo 'PLUSPLUS'*/
            if (sig == '+') {
                CONSTRUIR(PLUSPLUS);
                return sigComp;
                /*En caso contrario, se comprueba si el siguiente caracter es un
                 '='. En caso afirmativo, se devuelve un componente de tipo
                 'MORE_EQUALS'.*/
            } else if (sig == '=') {
                CONSTRUIR(MORE_EQUALS);
                return sigComp;
                /*En otro caso, se retrocede una posición y se devuelve sólo el
                 '+'*/
            } else {
                RETROCEDER();
                numChar--;
                SYM();
                return sigComp;
            }
        } else if (sig == '-') {
            SIGUIENTE();
            /*Se comprueba si el siguiente caracter también es un '-'. En caso
             afirmativo, se devuelve un componente de tipo 'MINUSMINUS'*/
            if (sig == '-') {
                CONSTRUIR(MINUSMINUS);
                return sigComp;
                /*En caso contrario, se comprueba si el siguiente caracter es un
                 '='. En caso afirmativo, se devuelve un componente de tipo
                 'MINUS_EQUALS'.*/
            } else if (sig == '=') {
                CONSTRUIR(MINUS_EQUALS);
                return sigComp;
                /*En otro caso, se retrocede una posición y se devuelve sólo el
                 '-'*/
            } else {
                RETROCEDER();
                numChar--;
                SYM();
                return sigComp;
            }
            /*Si el primer caracter es un salto de línea, se aumenta el contador de
             líneas y se devuelve el componente salto de línea*/
        } else if (sig == '\n') {
            linea++;
            SYM();
            return sigComp;
            /*Si el primer componente es un dígito, se llama a la función de
             reconocimiento de números*/
        } else if (isdigit(sig)) {
            NUM();
            return sigComp;
            /*Si el primer componente es una letra o una '_', se llama a la función
             de reconocimiento de palabras reservadas e identificadores*/
        } else if (isalpha(sig) || sig == '_') {
            ALPHANUM();
            return sigComp;
            /*Si el primer componente es un símbolo*/
        } else if (ispunct(sig)) {
            /*Si es un punto seguido de un dígito, se retrocede hasta el inicio
             del componente y se llama a la función de reconocimiento de
             números*/
            if (sig == '.') {
                SIGUIENTE();
                if (isdigit(sig)) {
                    RETROCEDER_TODO();
                    numChar = 0;
                    SIGUIENTE();
                    NUM();
                    return sigComp;
                    /*En caso contrario, se retrocede y se devuelve un símbolo*/
                } else {
                    RETROCEDER();
                    numChar--;
                }
            }
            SYM();
            return sigComp;
            /*Si el primer caracter es un espacio*/
        } else if (sig == ' ') {
            /*Se comprueba si el caracter anterior es un salto de línea*/
            if (anterior == '\n') {
                /*En caso afirmativo se piden componentes hasta encontrar algo
                 distinto de un espacio.*/
                do {
                    SIGUIENTE();
                } while (sig == ' ');
                /*Se retrocede y se devuelve un componente de tipo
                 INDENTATION*/
                RETROCEDER();
                numChar--;
                CONSTRUIR(INDENTATION);
                return sigComp;
                /*En otro caso, se trata de simples espacios que no constituyen
                 componentes léxicos y se descartan*/
            } else {
                DESCARTAR_ESPACIOS();
            }
        } else {
            ERROR(NOT_RECOGNIZED, LINEA());
        }
    }

    return sigComp;
}

