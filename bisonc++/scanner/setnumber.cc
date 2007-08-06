#include "scanner.ih"

int Scanner::setNumber() 
{
    d_number = A2x(yytext);
    return Parser::NUMBER;
}
