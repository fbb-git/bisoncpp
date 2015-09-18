#include "scanner.hh"

int Scanner::eoln()
{
    begin(StartCondition__::INITIAL);
    setLineNrs();
    return '\n';
}
