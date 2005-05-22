#include "scanner.ih"

int Scanner::setNumber() 
{
    d_number = atoi(yytext);
    return NUMBER;
}
