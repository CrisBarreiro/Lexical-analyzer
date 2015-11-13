/*Analizador léxico para python. Debe reconocer el archivo wilcoxon.py*/
%option noyywrap

%{
/*Biblotecas o variables que se pasarán al archivo .c*/
#include "Defs.h"
int linea = 0;
%}
DIGITO	[[:digit:]]
HEX 	[[:xdigit:]]
ALPHA	[[:alpha:]]
ID		[_[:alpha:]][_[:alnum:]]*
EXP		e-?{DIGITO}+

%%
\"\"\"
{DIGITO}+{EXP}	return FLOAT;
{DIGITO}*	return INTEGER;
"0x"{HEX}*	return INTEGER;
{DIGITO}*"."{DIGITO}+{EXP}?	return FLOAT;
{DIGITO}+"."{DIGITO}*{EXP}?	return FLOAT;
<<EOF>>	return EOF;
.

%%