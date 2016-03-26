#include "parser.ih"

bool Parser::dval(int nElements, Block &block,AtDollar const &atd)
{
    block.replace(atd.pos(), atd.length(), s_semanticValue);
    return true;
}
