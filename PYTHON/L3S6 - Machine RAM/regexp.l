%{

#include "regexp.tab.h"

%}

%%

\n                 { return EOL; }
\r                 { return EOL; }
[0-9]+             { yylval.symbol = yytext; return NUMBER; }
[A-Z0-9(),#-]+     { yylval.symbol = yytext; return INSTRUCTION; }
","                { return COMMA; }
.        		   { return yytext[0]; }
"<<EOF>>"          { return YYEOF; }

%%