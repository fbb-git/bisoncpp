#include "scanner.ih"

int Scanner::setNumber() 
{
    d_number = A2x(d_matched);
    return Parser::NUMBER;
}
