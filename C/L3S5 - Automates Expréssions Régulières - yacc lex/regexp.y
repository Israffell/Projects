%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);

extern int yylex();
%}

%token LETTRES_MIN
%token PAR_OUVRANTE
%token PAR_FERMANTE
%token E_CONST
%token O_CONST
%token PLUS
%token POINT
%token FOIS

%%

expressions: expression { printf("Expression régulière valide!\n"); }
          ;

expression: term
          | expression PLUS term
          ;

term: factor
    | term POINT factor
    ;

factor: primary
      | factor FOIS primary
      ;

primary: LETTRES_MIN
       | E_CONST
       | O_CONST
       | PAR_OUVRANTE expression PAR_FERMANTE
       ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique: %s\n", s);
    exit(Erreur);
}
