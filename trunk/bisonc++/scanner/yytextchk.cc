#include "scanner.ih"

    // called from lexer's action when the xstring mini scanner terminates.
    // if nKept != 0, determine *nKept as the number of trailing blanks

int Scanner::yytextChk(int *nKept, int minLength, int ret)
{
    int idx = yyleng;

    while (idx-- && (yytext[idx] == ' ' || yytext[idx] == '\t'))
        ;

    if (idx > 0 || yytext[0] != ' ' && yytext[0] != '\t')
        ++idx;
    
    *nKept = idx;

    if (d_include)
        return 0;                       // from an %include: yylex doesn't ret

    return idx < minLength ? ' ' : ret;
}


