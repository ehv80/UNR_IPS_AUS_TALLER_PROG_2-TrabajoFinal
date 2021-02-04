%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
extern char*yytext;
%}

%token NRO SEN
%union{
	double d;
};
%type<d> expr
%left '+''-'
%left '*'
%right UMINUS

%%
linea: expr ';' 		{printf("%f\n",$1);YYACCEPT;}
     ;
expr: NRO      			{$$=atof(yytext);}
    |expr '+' expr		{$$=$1+$3;}
    |expr '*' expr		{$$=$1*$3;}
    |expr '-' expr		{$$=$1-$3;}
    |'-' expr %prec UMINUS 	{$$=-$2;}
    |'(' expr ')' 		{$$=$2;}
    |SEN '(' expr ')' 		{$$=sin($3);}
;
%%

int main()
{
	while (yyparse())
		;
	return o;
}
