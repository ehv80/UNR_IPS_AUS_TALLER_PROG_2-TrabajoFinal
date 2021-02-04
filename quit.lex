%{
#include <stdio.h>
%}

%%

"quit"		return 0;
"QUIT"		return 0;
.		;

%%

int yywrap(){ return 1; }

int main(){ yylex(); return 0; }
