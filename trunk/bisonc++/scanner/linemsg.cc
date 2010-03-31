#include "scanner.ih"

std::ostream &Scanner::lineMsg()
{
    Msg::setLine(yylineno);
    return FBB::lineMsg() << "(" << d_fileInfo.back().d_name << ") ";
}
