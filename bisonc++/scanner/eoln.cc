#include "scanner.ih"

int Scanner::eoln()
{
    begin(StartCondition__::INITIAL);
    return '\n';
}
