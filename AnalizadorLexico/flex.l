/*Analizador léxico para python. Debe reconocer el archivo wilcoxon.py*/
%option noyywrap

%{
/*Biblotecas o variables que se pasarán al archivo .c*/
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

%x multiline_string
%%
\"([^\"]*\n[^\"]*)*\"	ERROR(LINE_END_ON_STRING, linea);
\'([^\']*\n[^\']*)*\'	ERROR(LINE_END_ON_STRING, linea);
\'[^\n\']*\'	return STRING;
\"[^\n\"]*\"	return STRING;
\"\"\" {
			yymore();
			BEGIN(multiline_string);
		}
#[^\n]*$
{DIGITO}+{EXP}	return FLOAT;
{DIGITO}*	return INTEGER;
"0x"{HEX}+	return INTEGER;
"0x"		ERROR(MALFORMED_HEXADECIMAL, linea);
{DIGITO}*"."{DIGITO}+{EXP}?	return FLOAT;
{DIGITO}+"."{DIGITO}*{EXP}?	return FLOAT;
{ID} return IDENTIFIER;
\n	{
		++linea;
		return yytext[0];
	}
^\ +	return INDENTATION;
{SYM} 	return yytext[0];
"**"	return POWER;
"+="	return MORE_EQUALS;
"=="	return EQUALS;
<<EOF>>	return EOF;
\ +
.		ERROR(NOT_RECOGNIZED, linea);


<multiline_string>\"\"\"	{
								BEGIN(INITIAL);
								return MULTILINE_STRING;
							}
<multiline_string>.		yymore();

<multiline_string>\n	{
							++linea;
							yymore();
						}

%%

int getLinea() {

	return linea;
}


