#include "parser.ih"

size_t/*unsigned*/ Parser::extractIndex(int *idx, size_t/*unsigned*/ pos) const
{
    istringstream is(d_block.substr(pos));


    is >> *idx;
    return is.tellg();
}
