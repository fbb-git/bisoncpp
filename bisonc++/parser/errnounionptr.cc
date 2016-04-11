#include "parser.ih"

void Parser::errNoUnionPtr(AtDollar const &atd)
{
    stdEmsg(atd) << "cannot use -> " "with plain union types" << endl;
}
