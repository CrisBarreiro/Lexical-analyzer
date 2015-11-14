/*Analizador léxico para python. Debe reconocer el archivo wilcoxon.py*/
%option noyywrap

%{
/*Biblotecas y variables*/
#include "Defs.h"
#include "Error.h"
int linea = 1;
%}
DIGITO	[[:digit:]]
HEX 	[[:xdigit:]]
ALPHA	[[:alpha:]]
ID		[_[:alpha:]][_[:alnum:]]*
EXP		e-?{DIGITO}+
SYM		"("|")"|";"|","|"="|"+"|">"|"<"|"-"|"*"|"/"|"^"|"."|"{"|"}"|":"|"["|"]"
%{
/*Condiciones de arranque*/
%}
%x multiline_string
%%
%{
/*Se lanza un error si se encuentra un salto de línea en
*mitad de un string*/
%}
\"([^\"]*\n[^\"]*)*\"	ERROR(LINE_END_ON_STRING, linea);
\'([^\']*\n[^\']*)*\'	ERROR(LINE_END_ON_STRING, linea);
\'[^\n\']*\'	return STRING;
\"[^\n\"]*\"	return STRING;
%{
/*Se ejecuta la condición de arranque "multiline_string" después
*de haber leído 3 comillas*/
%}
\"\"\" {
			yymore();
			BEGIN(multiline_string);
		}
%{
/*Se ignoran los comentarios*/
%}
#[^\n]*$
{DIGITO}+{EXP}	return FLOAT;
{DIGITO}*	return INTEGER;
"0x"{HEX}+	return INTEGER;
"0x"		ERROR(MALFORMED_HEXADECIMAL, linea);
{DIGITO}*"."{DIGITO}+{EXP}?	return FLOAT;
{DIGITO}+"."{DIGITO}*{EXP}?	return FLOAT;
%{
/*Toda secuencia alfanumérica que empiece por '_' o por una letra
*se devuelve como IDENTIFIER, y luego se comprueba en ALex.c si efectivamente
*se trata de una palabra reservada o de un identificador*/
%}
{ID} return IDENTIFIER;
%{
/*Al leer un salto de línea se aumenta el contador de líneas y se devuelde el
*componente \n*/
%}
\n	{
		++linea;
		return yytext[0];
	}
%{
/*Se devuelven los espacios que aparecen al principio de una línea*/
%}
^\ +	return INDENTATION;
{SYM} 	return yytext[0];
"**"	return POWER;
"+="	return MORE_EQUALS;
"=="	return EQUALS;
<<EOF>>	return EOF;
%{
/*Se ignoran los espacios que no aparecen al principio de una línea*/
%}
\ +
%{
/*Cualquier secuencia de caracteres que no haya sido reconocida por
*las reglas definidas anteriormente produce un error*/
%}
.		ERROR(NOT_RECOGNIZED, linea);

%{
/*Al reconocer 3 comillas que cierran un string multilínea, se vuelve
*a la condición de arranque por defecto*/
%}
<multiline_string>\"\"\"	{
								BEGIN(INITIAL);
								return MULTILINE_STRING;
							}
%{
/*Cualquier caracter distinto del salto de línea se añade
al lexema actual*/
%}
<multiline_string>.		yymore();

%{
/*Al leer un salto de línea, se aumenta el contador de líneas
*y se añade al lexema actual*/
%}
<multiline_string>\n	{
							++linea;
							yymore();
						}

%%
