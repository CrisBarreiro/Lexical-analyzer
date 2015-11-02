#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>

/*Función que devuelve el tipo de componente léxico en formato String en
 función de su identificador*/
char* IDTOSTRING (int id){
    char * ret = (char*) malloc (20* sizeof(char));
    switch(id) {
        case 10:
            ret = "LINE_END";
            break;
        case 44:
            ret = "COMMA";
            break;
        case MULTILINE_STRING:
            ret = "MULTILINE_STRING";
            break;
        case IMPORT:
            ret = "IMPORT";
            break;
        case 46:
            ret = "DOT";
            break;
        case IDENTIFIER:
            ret = "IDENTIFIER";
            break;
        case 61:
            ret = "EQUALS";
            break;
        case 123:
            ret = "RIGHT_BRACE";
            break;
        case 58:
            ret = "COLON";
            break;
        case 125:
            ret = "LEFT_BRACE";
            break;
        case DEF:
            ret = "DEF";
            break;
        case 40:
            ret = "RIGH_PARENTHESIS";
            break;
        case 41:
            ret = "LEFT_PARENTHESIS";
            break;
        case INDENTATION:
            ret = "INDENTATION";
            break;
        case 91:
            ret = "RIGHT_BRACKET";
            break;
        case 93:
            ret = "LEFT_BRACKET";
            break;
        case 45:
            ret = "MINUS";
            break;
        case FOR:
            ret = "FOR";
            break;
        case IN:
            ret = "IN";
            break;
        case IF:
            ret = "IF";
            break;
        case ELIF:
            ret = "ELIF";
            break;
        case 43:
            ret = "PLUS";
            break;
        case 42:
            ret = "ASTERISK";
            break;
        case INTEGER:
            ret = "INTEGER";
            break;
        case FLOAT:
            ret = "FLOAT";
            break;
        case STRING:
            ret = "STRING";
            break;
        case 47:
            ret = "SLASH";
            break;
        case 60:
            ret = "LESS_THAN";
            break;
        case MORE_EQUALS:
            ret = "MORE_EQUALS";
            break;
        case MINUS_EQUALS:
            ret = "MINUS_EQUALS";
            break;
        case 62:
            ret = "GREATER_THAN";
            break;
        case POWER:
            ret = "POWER";
            break;
        case RETURN:
            ret = "RETURN";
            break;
        case EOF:
            ret = "EOF";
            break;
        case AS:
            ret = "AS";
            break;
        case NOT:
            ret = "NOT";
            break;
        case ELSE:
            ret = "ELSE";
            break;
        case PRINT:
            ret = "PRINT";
            break;
        case EQUALS:
            ret = "EQUALS_EQUALS";
            break;
    }
    return ret;
}
