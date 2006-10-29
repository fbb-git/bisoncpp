#include "parser.ih"

size_t Parser::extractIndex(int *idx, size_t pos) const
{
    istringstream is(d_block.substr(pos));


    is >> *idx;
    return is.tellg();
}
