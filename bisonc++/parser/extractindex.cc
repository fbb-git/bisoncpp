#include "parser.ih"

unsigned Parser::extractIndex(int *idx, unsigned pos) const
{
    istringstream is(d_block.substr(pos));


    is >> *idx;
    return is.tellg();
}
