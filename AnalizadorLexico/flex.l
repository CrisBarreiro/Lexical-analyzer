/*Analizador léxico para python. Debe reconocer el archivo wilcoxon.py*/
%option noyywrap

%{
/*Biblotecas o variables que se pasarán al archivo .c*/
#include "Defs.h"
#include "Error.h"
int linea = 0;
%}
DIGITO	[[:digit:]]
HEX 	[[:xdigit:]]
ALPHA	[[:alpha:]]
ID		[_[:alpha:]][_[:alnum:]]*
EXP		e-?{DIGITO}+
SYM		"("|")"|";"|","|"="|"+"|">"|"<"|"-"|"*"|"/"|"^"|"."|"{"|"}"|":"|"["|"]"

%x multiline_string
%x string1
%x string2
%%
#[^\n]*$
\"\"\" {
			yymore();
			BEGIN(multiline_string);
		}
\"		{
			yymore();
			BEGIN(string2);
		}
\'		{
			yymore();
			BEGIN(string1);
		}
{DIGITO}+{EXP}	return FLOAT;
{DIGITO}*	return INTEGER;
"0x"{HEX}*	return INTEGER;
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
.


<multiline_string>\"\"\"	{
								BEGIN(INITIAL);
								return MULTILINE_STRING;
							}
<multiline_string>.		yymore();

<multiline_string>\n	{
							++linea;
							yymore();
						}
<string2>\"	{
				BEGIN(INITIAL);
				return STRING;
			}
			
			
<string2>.	{
				yymore();
			}

<string2>\n	return LINE_END_ON_STRING;


<string1>\'	{
				BEGIN(INITIAL);
				return STRING;
			}
			
			
<string1>.	{
				yymore();
			}

<string1>\n	return LINE_END_ON_STRING;


%%