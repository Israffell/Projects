%{
#include <stdio.h>
%}

LETTRES_MIN [a-z]
O_CONST     O
E_CONST     E
CHAINE      {LETTRES_MIN}({LETTRES_MIN})*

%%

{LETTRES_MIN}   { printf("LETTRES_MIN: %s\n", yytext); }
{O_CONST}       { printf("O_CONST\n"); }
{E_CONST}       { printf("E_CONST\n"); }
{CHAINE}        { printf("CHAINE: %s\n", yytext); }
"."             { printf("POINT\n"); }
"*"             { printf("FOIS\n"); }
"+"             { printf("PLUS\n"); }
"("             { printf("PAR_OUVRANTE\n"); }
")"             { printf("PAR_FERMANTE\n"); }
[ \t\n]  ;  //Ignore les espaces et les sauts de ligne

.   { printf("Ce caractère est inconnu: %s\n", yytext); }