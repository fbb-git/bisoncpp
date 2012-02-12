#include "scanner.ih"

std::ostream &Scanner::lineMsg(Mstream &mstream)
{
    mstream.setLineNr(lineNr());
    return mstream << "(" << filename() << ") ";
}
