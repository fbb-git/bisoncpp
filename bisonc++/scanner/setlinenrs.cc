#include "scanner.ih"

void Scanner::setLineNrs() const
{
    emsg.setLineNr(lineNr());
    fmsg.setLineNr(lineNr());
    imsg.setLineNr(lineNr());
    wmsg.setLineNr(lineNr());
}
