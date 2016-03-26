#include "parser.ih"

bool Parser::errNoRef(int nElements, Block &block, AtDollar const &atd)
{
    stdEmsg(atd) << "dereferencing (`" << atd.text() << 
            "') not supported for the STYPE__ semantic value type" << endl;

    return false;
}
