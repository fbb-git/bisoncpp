#include "scanner.ih"

int Scanner::eoln()
{
    begin(StartCondition_::INITIAL);
    setLineNrs();
    return '\n';
}
