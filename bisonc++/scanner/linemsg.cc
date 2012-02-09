#include "scanner.ih"

std::ostream &Scanner::lineMsg(Mstream &mstream)
{
    cerr << "Scanner::lineMsg(): lineNr = " << lineNr() << endl;

    mstream.setLineNr(lineNr());
    return mstream << "(" << filename() << ") ";
}
