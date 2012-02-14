#include "scanner.ih"

int Scanner::eoln()
{
    begin(StartCondition__::INITIAL);
    setLineNrs();
    return '\n';
}
