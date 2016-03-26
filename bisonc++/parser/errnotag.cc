#include "parser.ih"

bool Parser::errNoTag(int nElements, Block &block, AtDollar const &atd)
{
    stdEmsg(atd) << "the STYPE__ semantic value type does not support "
                    "tags (`" << atd.text() << "')" << endl;

    return false;
}
