#include "scanner.ih"

std::ostream &Scanner::lineMsg(Mstream &mstream)
{
    mstream.setLineNr(yylineno);
    return mstream << "(" << d_fileInfo.back().d_name << ") ";
}
