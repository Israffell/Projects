%{
#include <stdarg.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if YYBISON
int yylex();
int yyerror();
#endif


// Création d'un Struct s'occupant d'actualiser la taille du string
typedef struct {    
    size_t size;
    char* data;
} StringBuffer;


// Initialisation de la struct
void initBuffer(StringBuffer* buffer) {    
    buffer->size = 0;
    buffer->data = NULL;
}


// Création d'une fonction void pour modifier et additioner un string au buffer
void appendString(StringBuffer* buffer, const char* str) {
    size_t size = strlen(str);
    buffer->data = realloc(buffer->data, buffer->size + size + 1);
    if (buffer->data == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(buffer->data + buffer->size, str);
    buffer->size += size;
}


// Création d'une fonction char(=string) qui fusionne/concatène les strings déjà créer
char* conc(int temp, ...) {
    va_list args;
    int finalSize = 0;

    //Calcul la longeur nécessaire à l'allocation de mémoire du malloc
    va_start(args, temp);
    for (int i = 0; i < temp; i++) {
        const char* str = va_arg(args, const char*);
        finalSize += strlen(str);
    }
    va_end(args);

    //On alloue la mémoire (fixe) via le malloc
    char* result = (char*) malloc( sizeof(char) * (finalSize + 1) );     
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    //Forme finale des char* (string)
    va_start(args, temp);
    for (int i = 0; i < temp; i++) {
        const char* str = va_arg( args, const char* );
        strcat(result, str);
    }
    va_end(args);

    return result;
}


// Fonction d'écriture d'un buffer dans le fichier main.py
void write(const StringBuffer* buffer) {
    FILE *f = fopen("main.py", "w");
    if (f == NULL) {
        perror("Error, file not reachable, impossible to open");
        exit(EXIT_FAILURE);
    }
    fprintf(f, "%s", buffer->data);
    fclose(f);
}

int temp;
StringBuffer start;
StringBuffer end;
%}


%union{char *symbol;}           /*Yacc definitions*/

%token INSTRUCTION
%token NUMBER
%token COMMA
%token EOL
%left EOL

%type <symbol> INSTRUCTION projet input NUMBER

%%

// Descriptions des entrées utilisateur attendu

contenu:
        input EOL projet      { ; }
    ;
input:
        INSTRUCTION           {appendString(&start, conc(3, "input = [", $1, "]\n\nprojet = [\n"));}
    ;
projet:
        INSTRUCTION           {appendString(&start, conc(3, "'", $1, "',\n"));}
    |   projet EOL projet     {;}
    |   EOL projet            {;}
    |   YYEOF                 {;}
    ;
%%

// Le 'corps' du fichier regecp.y permettant l'execution du programme

int main() {
    appendString(&start, "from RamProject import *\n\n");
    appendString(&end, "]\n\nram = RamProject(projet, input)\n\nram.executeProject()\n");

    yyparse();

    start.data = realloc(start.data, start.size + end.size + 1);
    strcat(start.data, end.data);
    start.size += end.size;

    write(&start);

    free(start.data);
    free(end.data);
}