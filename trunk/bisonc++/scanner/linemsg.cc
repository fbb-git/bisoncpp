#include "scanner.ih"

std::ostream &Scanner::lineMsg(Mstream &mstream)
{
    cerr << "Scanner::lineMsg(): yylineno = " << yylineno << endl;

    mstream.setLineNr(yylineno);
    return mstream << "(" << d_fileInfo.back().d_name << ") ";
}
